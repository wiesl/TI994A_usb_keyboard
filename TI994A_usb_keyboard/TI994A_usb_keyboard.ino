/*
 * TI994A Usb Keyboard
 *
 * This program reads a (wireless) USB keyboard and converts the
 * user input to a TI994A matrix keyboard output to be used for
 * the Texas Instruments TI994A home computer.
 *
 * This program is designed around a Teensy 3.2 with a Sparkfun
 * Teensy 3.1 Arduino Shield Adapter and a Sparkfun USB host
 * shield.
 *
 * IDE Settings for Teensy:
 *
 * Board     : Teensy 3.2
 * CPU speed : 48Mhz
 * Optimize  : Fast
 */

#include <hidboot.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

/*
 * DEBUG OPTIONS
 */
//#define DEBUG_SERIAL			//Serial debugger over USB

#if defined DEBUG_SERIAL

#define DEBUG_MISC			//Miscelaneous debug
//#define DEBUG_USB_KB_READ		//USB KeayBoard Read
#define DEBUG_USB_TO_TI99		//USB to TI99 conversion
#define DEBUG_USB_CAPSLCK		//Capslock on/ off
#define DEBUG_USB_NUMLCK		//Numlock on /off
#define DEBUG_USB_SP_KM			//SPecial Keyboard Mode
#define DEBUG_TI99_KEY_MATRIX		//Keyboard Matrix set/reset
#endif
//#define TI99_KEY_POLLING		//Poll functions for keyboard (to slow)
#define TI99_KEY_INTERRUPT		//Interrupt functions for keyborad

/*
 * Standard delay functions
 */
#ifndef _delay_us
#define _delay_us(n) delayMicroseconds(n)
#endif

#ifndef _delay_ms
#define _delay_ms(n) delay(n)
#endif

/*
 * TI994A Keyboard includes
 */
#include "TI994A_usb_keyboard.h"
#include "usb_conv_table.h"
#include "ti99_conv_table.h"
#include "basic_table.h"
#include "ti99_keyb_funcs.h"

//Some bit manipulation Macro's
//#define SBO(p)    digitalWrite(p, HIGH)     	//Set Bit One
//#define SBZ(p)    digitalWrite(p, LOW)      	//Set Bit Zero
#define TB(p)     (digitalRead(p) ? HIGH : LOW)	//Test Bit

#define RM_STARTSETUP	0		// Running mode Start Setup
#define RM_ENDSETUP	1		// Running mode End of Setup
#define RM_ACTIVE	2		// Running mode Active

static byte RunningMode	= 0;		// Running mode

static byte UsbModSum   = 0;		// Modifier sum
static bool UsbLftShift = FALSE;	// Left  Shift down
static bool UsbRgtShift = FALSE;	// Right Shift Down
static bool UsbLftCtrl  = FALSE;	// Left  Control down
static bool UsbRgtCtrl  = FALSE;	// Right Control Down
static bool UsbLftAlt   = FALSE;	// Left  Alt down
static bool UsbRgtAlt   = FALSE;	// Right Alt Down
static bool UsbLftGui   = FALSE;	// Left  GUI down
static bool UsbRgtGui   = FALSE;	// Right GUI Down
static bool UsbWfkUp	= FALSE;	// Wait For Key Up
static byte KeybMode    = KBSM_UNDEF;	// Keyboard Special Mode

static byte KeybLeds	= 0x00;		// Keyboard LEDs
static byte KeybLedsCpy	= 0xFF;		// Keyboard LEds copy

#include "ti99_spmod_funcs.h"

#if defined DEBUG_USB_TO_TI99
/* PrintPressedKey - Print pressed key value
 *
 * Input : 
 * Return: 
 * Error : 
 */
static void PrintPressedKey(const char *what, const byte ascii)
{
	Serial.print(what);
	if ((ascii >= ' ') && (ascii <= '~'))
	{
		Serial.print((char)ascii);
	}
	else
	{
		Serial.print("?");
	}
	Serial.print(" (0x");
	Serial.print(ascii, HEX); 
	Serial.print(")");
}

/* PrintUsbTi99Key - Print Usb To TI99 conversion Key
 *
 * Input : 
 * Return: 
 * Error : 
 */
static void PrintUsbTi99Key(byte key_stat, byte usb_key, byte usb_asc, TI99KEYCONV *pTI99KeyConv)
{
	byte ti_asc = 0;
	byte ti_chrinp = 0;
	byte ti_chrout = 0;
	
	if (pTI99KeyConv != NULL)
	{
		ti_asc = pTI99KeyConv->Asc_Code;
		ti_chrinp = pTI99KeyConv->Ti99_ChrInp;
		ti_chrout = pTI99KeyConv->Ti99_ChrOut;
	}

	Serial.print(key_stat == KBKEY_DN ? "DOWN" : "UP  ");
	Serial.print(" UsbKey=0x");
	Serial.print(usb_key, HEX); 
	Serial.print(" TiInp=");
	Serial.print(ti_chrinp, DEC);//HEX); 
	Serial.print(" TiOut=");
	Serial.print(ti_chrout, DEC);//HEX); 
	PrintPressedKey(" UsbAscii=", usb_asc);
	PrintPressedKey(" TiAscii=",  ti_asc);
	Serial.println("");
}
#endif


/* ConvUsbToTi99 - Convert Usb Key to TI99 Key
 *
 * Input : key_stat = KBKEY_DN | KBKEY_UP
 *         usb_key  = USB keyboard key code
 * Return:
 * Error :
 */
static void ConvUsbToTi99(byte key_stat, byte usb_key)
{
	USBKEYCONV  *pUsbKeyConv;
	TI99KEYCONV *pTI99KeyConv;
	byte       usb_asc;
	byte       cmd_asc;

	//Get USB key
	pUsbKeyConv = GetUsbKeyConv(usb_key);
	if (pUsbKeyConv == NULL)
	{
#if defined DEBUG_USB_TO_TI99
		PrintUsbTi99Key(key_stat, usb_key, 0x00, NULL);
		Serial.println("GetUsbKeyConv returned <NULL>");
#endif
		return;
	}
	usb_asc = pUsbKeyConv->Asc_Code;

	//Convert TAB to F7 (== Alt+7 == Fctn+7)
	if ((usb_asc == SK_TAB) && (KeybMode != KBSM_UNDEF))
	{
		if (key_stat == KBKEY_DN) UsbKbTabMode();
		return;
	}

	//Remove TAB command suggestion
	if ((usb_asc == SK_ESCAPE) && (KeybMode != KBSM_UNDEF))
	{
		if (key_stat == KBKEY_DN) UsbKbEscMode();
		return;
	}

	//Switch to special keyboard mode	
	if (UsbLftGui || UsbRgtGui)
	{
		if (key_stat == KBKEY_DN)
		{
			UsbWfkUp = TRUE;
			UsbKbSpecialMode(usb_asc);
			return;
		}
	}
	if (UsbWfkUp && (key_stat == KBKEY_UP))
	{
		UsbWfkUp = FALSE;
		return;
	}
	
	//Save char to find command with <TAB> key
	if ((KeybMode != KBSM_UNDEF) && (key_stat == KBKEY_DN))
	{
		do
		{
			cmd_asc = 0xFF;
			
			if ((usb_asc == MK_LSHIFT) || (usb_asc == MK_RSHIFT)
			||  (usb_asc == MK_LCTRL ) || (usb_asc == MK_RCTRL )
			||  (usb_asc == MK_LALT  ) || (usb_asc == MK_RALT  ))
			{
				break;
			}

			if (UsbLftCtrl || UsbRgtCtrl || UsbLftAlt || UsbRgtAlt)
			{
				cmd_asc = 0x00; break;
			}

			if ((usb_asc >= 'a') && (usb_asc <= 'z'))
			{
				cmd_asc = usb_asc; break;
			}
			if (isdigit(usb_asc) && !UsbLftShift && !UsbRgtShift)
			{
				cmd_asc = usb_asc; break;
			}
			cmd_asc = 0x00;
		}
		while (0);
		
		switch(cmd_asc)
		{
		case 0xFF: break;
		case 0x00: CmdBufferCnt = 0; break;
		default  : 
			if (CmdBufferCnt < MAXCMDBUFSIZE)
			{
				CmdBuffer[CmdBufferCnt++] = toupper(cmd_asc);
			}
			break;
		}
		CmdBuffer[CmdBufferCnt]   = '\0';
		
#if defined DEBUG_USB_SP_KM
		Serial.print(" CmdBuffer: [");
		Serial.print(CmdBuffer);
		Serial.println("]");
#endif
	}
	
	//Convert SHIFT [,],\,',/,-,` to {,},|,",?,_,~
	if (UsbLftShift || UsbRgtShift)
	{
		switch(usb_asc)
		{
		case '[' : usb_asc = '{'; break;
		case ']' : usb_asc = '}'; break;
		case '\\': usb_asc = '|'; break;
		case '/' : usb_asc = '?'; break;
		case '\'': usb_asc = '"'; break;
		case '-':  usb_asc = '_'; break;
		case '`':  usb_asc = '~'; break;
		}
	}
	
	// Convert num-keys to edit keys if NUMLOCK is OFF
	if (!TI99Numl)
	{
		switch(usb_asc)
		{
		case NK_NMBR1 : usb_asc = EK_END;    break;
		case NK_NMBR2 : usb_asc = EK_LINEDN; break;
		case NK_NMBR3 : usb_asc = EK_PAGEDN; break;
		case NK_NMBR4 : usb_asc = EK_CHARLT; break;
		case NK_NMBR5 : usb_asc = XK_NOTDEF; break;
		case NK_NMBR6 : usb_asc = EK_CHARRT; break;
		case NK_NMBR7 : usb_asc = EK_HOME;   break;
		case NK_NMBR8 : usb_asc = EK_LINEUP; break;
		case NK_NMBR9 : usb_asc = EK_PAGEUP; break;
		case NK_NMBR0 : usb_asc = EK_INSERT; break;
		case NK_DECPNT: usb_asc = EK_DELETE; break;
		}
	}

	//Get TI99 key
	pTI99KeyConv = GetTI99KeyConv(usb_asc);
	if (pTI99KeyConv == NULL)
	{
#if defined DEBUG_USB_TO_TI99
		PrintUsbTi99Key(key_stat, usb_key, 0x00, NULL);
		Serial.println("GetTI99KeyConv returned <NULL>");
#endif
		return;
	}

	//Reset Command List
	AsciiCmdList = 0;
	OldCmd       = NULL;
	CmdBufferIdx = 0;

	if (pTI99KeyConv->Ti99_ChrInp == KBI_NONE)
	{
#if defined DEBUG_USB_TO_TI99
		PrintUsbTi99Key(key_stat, usb_key, 0x00, pTI99KeyConv);
		Serial.println("*** Not a TI99 key!");
#endif
		return;				//Nothing to send
	}

//	usb_asc  = pUsbKeyConv->Asc_Code;
//	ti99_asc = pTI99KeyConv->Asc_Code;
	
	switch(pTI99KeyConv->Asc_Code)
	{
	case SK_CPSLCK:
		if (key_stat == KBKEY_DN)
		{
			TI99Capsl = !TI99Capsl;
#if defined DEBUG_USB_CAPSLCK
			Serial.print("TI99Capslock=");
			Serial.println(TI99Capsl ? "ON" : "OFF");
#endif
			if (TI99Capsl)
			{
				TI99_Write_Key_Down(pTI99KeyConv);
			}
			else
			{
				TI99_Write_Key_Up(pTI99KeyConv);
			}
		}
		return;

	case NK_NUMLCK:
		if (key_stat == KBKEY_DN)
		{
			TI99Numl = !TI99Numl;
#if defined DEBUG_USB_NUMLCK
			Serial.print("TI99Numlock=");
			Serial.println(TI99Numl ? "ON" : "OFF");
#endif
		}
		return;
	
	case MK_LSHIFT: key_stat == KBKEY_DN ? TI99Shift |= 0x01 : TI99Shift &= ~0x01; break;
	case MK_RSHIFT: key_stat == KBKEY_DN ? TI99Shift |= 0x02 : TI99Shift &= ~0x02; break;
	
	case MK_LCTRL:  key_stat == KBKEY_DN ? TI99Cntrl |= 0x01 : TI99Cntrl &= ~0x01; break;
	case MK_RCTRL:  key_stat == KBKEY_DN ? TI99Cntrl |= 0x02 : TI99Cntrl &= ~0x02; break;
	
	case MK_LALT:   key_stat == KBKEY_DN ? TI99Fnct  |= 0x01 : TI99Fnct  &= ~0x01; break;
	case MK_RALT:	key_stat == KBKEY_DN ? TI99Fnct  |= 0x02 : TI99Fnct  &= ~0x02; break;

	default: break;
	}

#if defined DEBUG_USB_TO_TI99
	PrintUsbTi99Key(key_stat, usb_key, usb_asc, pTI99KeyConv);
#endif
	
	//Send the TI99 keyboard code
	if (key_stat == KBKEY_DN)
	{
		TI99_Write_Key_Down(pTI99KeyConv);
	}
	else
	{
		TI99_Write_Key_Up(pTI99KeyConv);
	}
}


/* 
 * USB Host Keyboard functions
 */
//#include "Usb_Keyboard.h"

class KbdRptParser : public KeyboardReportParser
{
    void PrintKey(uint8_t mod, uint8_t key);

  protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);

    void OnKeyDown   (uint8_t mod, uint8_t key);
    void OnKeyUp     (uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
};

#if defined DEBUG_USB_KB_READ
void KbdRptParser::PrintKey(uint8_t m, uint8_t key)
{
	MODIFIERKEYS mod;
	*((uint8_t*)&mod) = m;
	Serial.print((mod.bmLeftCtrl   == 1) ? "C" : " ");
	Serial.print((mod.bmLeftShift  == 1) ? "S" : " ");
	Serial.print((mod.bmLeftAlt    == 1) ? "A" : " ");
	Serial.print((mod.bmLeftGUI    == 1) ? "G" : " ");
	
	Serial.print(" >");
	Serial.print(key, HEX); 
	Serial.print("< ");
	
	Serial.print((mod.bmRightCtrl   == 1) ? "C" : " ");
	Serial.print((mod.bmRightShift  == 1) ? "S" : " ");
	Serial.print((mod.bmRightAlt    == 1) ? "A" : " ");
	Serial.println((mod.bmRightGUI  == 1) ? "G" : " ");
};
#endif

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
#if defined DEBUG_USB_KB_READ
	Serial.print("DN ");
	PrintKey(mod, key);
	uint8_t c = OemToAscii(mod, key);

	if (c) OnKeyPressed(c);
#endif
	ConvUsbToTi99(KBKEY_DN, key);
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
#if defined DEBUG_USB_KB_READ
	Serial.print("UP ");
	PrintKey(mod, key);
#endif
	ConvUsbToTi99(KBKEY_UP, key);
}

#if defined DEBUG_USB_KB_READ
void KbdRptParser::OnKeyPressed(uint8_t key)
{
	Serial.print("ASCII: ");
	Serial.println((char)key);
};
#endif

#if defined DEBUG_USB_KB_READ
void printUpDn(const char *what, uint8_t state)
{
	Serial.print(what);
	Serial.println(state ? " DN" : " UP");
}
#endif

void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after)
{

	MODIFIERKEYS beforeMod;
	*((uint8_t*)&beforeMod) = before;

	MODIFIERKEYS afterMod;
	*((uint8_t*)&afterMod) = after;
	
	UsbModSum = (byte) after;

/*
 *          Left  Right
 * Control  0x01  0x10
 * Shift    0x02  0x20
 * Alt      0x04  0x40
 * Gui      0x08  0x80
 */
#if defined DEBUG_USB_KB_READ
	Serial.print("B=");
	Serial.print(before, HEX); 
	Serial.print(" A=");
	Serial.print(after, HEX); 
	Serial.print(" ");
#endif

	if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) {
#if defined DEBUG_USB_KB_READ
		printUpDn("LeftCtrl", afterMod.bmLeftCtrl);
#endif
		UsbLftCtrl = afterMod.bmLeftCtrl;
		ConvUsbToTi99(afterMod.bmLeftCtrl ? KBKEY_DN : KBKEY_UP, USB_LCTRL);
	}
	if (beforeMod.bmLeftShift != afterMod.bmLeftShift) {
#if defined DEBUG_USB_KB_READ
		printUpDn("LeftShift", afterMod.bmLeftShift);
#endif
		UsbLftShift = afterMod.bmLeftShift;
		ConvUsbToTi99(afterMod.bmLeftShift ? KBKEY_DN : KBKEY_UP, USB_LSHIFT);
	}
	if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) {
#if defined DEBUG_USB_KB_READ
		printUpDn("LeftAlt", afterMod.bmLeftAlt);
#endif
		UsbLftAlt = afterMod.bmLeftAlt;
		ConvUsbToTi99(afterMod.bmLeftAlt ? KBKEY_DN : KBKEY_UP, USB_LALT);
	}
	if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) {
#if defined DEBUG_USB_KB_READ
		printUpDn("LeftGUI", afterMod.bmLeftGUI);
#endif
		UsbLftGui = afterMod.bmLeftGUI;
		ConvUsbToTi99(afterMod.bmLeftGUI ? KBKEY_DN : KBKEY_UP, USB_LGUI);
	}

	if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) {
#if defined DEBUG_USB_KB_READ
		printUpDn("RightCtrl", afterMod.bmRightCtrl);
#endif
		UsbRgtCtrl = afterMod.bmRightCtrl;
		ConvUsbToTi99(afterMod.bmRightCtrl ? KBKEY_DN : KBKEY_UP, USB_RCTRL);
	}
	if (beforeMod.bmRightShift != afterMod.bmRightShift) {
#if defined DEBUG_USB_KB_READ
		printUpDn("RightShift", afterMod.bmRightShift);
#endif
		UsbRgtShift = afterMod.bmRightShift;
		ConvUsbToTi99(afterMod.bmRightShift ? KBKEY_DN : KBKEY_UP, USB_RSHIFT);
	}
	if (beforeMod.bmRightAlt != afterMod.bmRightAlt) {
#if defined DEBUG_USB_KB_READ
		printUpDn("RightAlt", afterMod.bmRightAlt);
#endif
		UsbRgtAlt = afterMod.bmRightAlt;
		ConvUsbToTi99(afterMod.bmRightAlt ? KBKEY_DN : KBKEY_UP, USB_RALT);
	}
	if (beforeMod.bmRightGUI != afterMod.bmRightGUI) {
#if defined DEBUG_USB_KB_READ
		printUpDn("RightGUI", afterMod.bmRightGUI);
#endif
		UsbRgtGui = afterMod.bmRightGUI;
		ConvUsbToTi99(afterMod.bmRightGUI ? KBKEY_DN : KBKEY_UP, USB_RGUI);
	}
}

/*
 * MAIN PROGRAM
 */
USB     Usb;
//USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

KbdRptParser Prs;

/*
 * For Teensy3 with Sparkfun hub
 */
#define MAX_RESET 7 //MAX3421E pin 12
#define MAX_GPX   8 //MAX3421E pin 17

/*
 * Initialisation
 */
void setup()
{
	RunningMode = RM_STARTSETUP;
	
#if defined DEBUG_SERIAL
 	Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  	while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
	Serial.println("Start setup");
#endif
	
	pinMode(MAX_GPX, INPUT);
	pinMode(MAX_RESET, OUTPUT);
	
	digitalWrite(MAX_RESET, LOW);
	_delay_ms(20);
	digitalWrite(MAX_RESET, HIGH);
	_delay_ms(20);

	Ti99_Init_IO();
	TI99_Clear_Kb_Output_Rows();
#if defined TI99_KEY_INTERRUPT
	TI99_Set_Keyboard_Interrupts();
#endif
	
	_delay_ms(500);

#if defined DEBUG_SERIAL
	Serial.println("Usb.Init");
#endif
	if (Usb.Init() == -1)
	{
#if defined DEBUG_MISC
		Serial.println("OSC did not start.");
#endif
	}
	_delay_ms(200);

#if defined DEBUG_SERIAL
	Serial.println("SetReportParser");
#endif
	HidKeyboard.SetReportParser(0, (HIDReportParser*)&Prs);

#if defined DEBUG_SERIAL
	Serial.println("End setup");
#endif

	RunningMode = RM_ENDSETUP;
}

/*
 * Main loop, do forever
 */
void loop()
{
        union {
                KBDLEDS kbdLeds;
                uint8_t bLeds;
        } kbdLockingKeys;
 
 	if (RunningMode < RM_ACTIVE)
	{
		RunningMode = RM_ACTIVE;

		TI99Capsl = FALSE;
		TI99Numl  = TRUE;
#if 0		
//Teensy sometimes stops functioning after startup
		kbdLockingKeys.bLeds = 0;
		if (TI99Capsl) kbdLockingKeys.kbdLeds.bmCapsLock = 1;
		if (TI99Numl)  kbdLockingKeys.kbdLeds.bmNumLock  = 1;
		HidKeyboard.SetReport(0, 0, 2, 0, 1, &(kbdLockingKeys.bLeds));
#endif
#if 1
		kbdLockingKeys.bLeds = 0;
		HidKeyboard.GetReport(0, 0, 2, 0, 1, &(kbdLockingKeys.bLeds));
		TI99Capsl = kbdLockingKeys.kbdLeds.bmCapsLock == 1;
		TI99Numl  = kbdLockingKeys.kbdLeds.bmNumLock  == 1;
#endif
	}
	
	Usb.Task();
	
	//Write LED output to USB Host GIO pins
	KeybLeds = 0x00;
	if (TI99Capsl) KeybLeds |= 0x01;
	if (TI99Numl)  KeybLeds |= 0x02;
	if (KeybMode == KBSM_BASIC) KeybLeds |= 0x04;
	if (KeybLedsCpy != KeybLeds)
	{
		KeybLedsCpy = KeybLeds;
		Usb.gpioWr(KeybLeds);
#if 0
//Teensy sometimes stops functioning after startup
		kbdLockingKeys.bLeds = 0;
		if (TI99Capsl) kbdLockingKeys.kbdLeds.bmCapsLock = 1;
		if (TI99Numl)  kbdLockingKeys.kbdLeds.bmNumLock  = 1;
		HidKeyboard.SetReport(0, 0, 2, 0, 1, &(kbdLockingKeys.bLeds));
#endif
	}
	
#if 0
	Usb.gpioWr(data);
or ...
        Usb.regWr(rIOPINS1, data);
        data >>= 4;
        Usb.regWr(rIOPINS2, data); 
#endif

#if TI99_KEY_POLLING
	TI99_Read_Output_Pins();
#endif
// Some key combination or other signal from TI
#if 0	
	if ((TB(XT_RESET) == LOW) && TI99Reset)
	{
		TI99Capsl = FALSE;
		TI99Numl  = TRUE;
		TI99Shift = 0x00;
		TI99Cntrl = 0x00;
		TI99Fnct  = 0x00;
		
		UsbModSum   = 0;
		UsbLftShift = FALSE;
		UsbRgtShift = FALSE;
		UsbLftCtrl  = FALSE;
		UsbRgtCtrl  = FALSE;
		UsbLftAlt   = FALSE;
		UsbRgtAlt   = FALSE;
		UsbLftGui   = FALSE;
		UsbRgtGui   = FALSE;
		UsbWfkUp    = FALSE;
		KeybMode    = KBSM_UNDEF;

		AsciiCmdList = 0;
		OldCmd = NULL;

		CmdBufferCnt = 0;
		CmdBufferIdx = 0;

		TI99Reset = FALSE;
	}
	else
	{
		TI99Reset = TRUE;
	}
#endif
}
