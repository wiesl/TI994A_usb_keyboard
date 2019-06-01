#if !defined(__TI994AKB_H__)
#define __TI994AKB_H__

typedef unsigned char   byte;
typedef unsigned char   uchar;
typedef unsigned short  ushort;
typedef unsigned long   ulong;
typedef unsigned int    uint;
//typedef unsigned char   bool;     redefinition

#define FALSE 0x00
#define TRUE  0x01

//Keys with speudo ascii code beyond '~' (0x7E)

//Special keys
#define SK_ENTER	0x7F
#define SK_ESCAPE	0x80
#define SK_BACKSP	0x81
#define SK_TAB		0x82
#define SK_PRTSCR	0x83
#define SK_PAUSE	0x84
#define SK_CPSLCK	0x85
#define SK_SCRLCK	0x86
#define SK_WMENU	0x87

//Function keys
#define FK_F01		0x88
#define FK_F02		0x89
#define FK_F03		0x8A
#define FK_F04		0x8B
#define FK_F05		0x8C
#define FK_F06		0x8D
#define FK_F07		0x8E
#define FK_F08		0x8F
#define FK_F09		0x90
#define FK_F10		0x91
#define FK_F11		0x92
#define FK_F12		0x93

//Edit keys
#define EK_INSERT	0x94
#define EK_DELETE	0x95
#define EK_HOME		0x96
#define EK_END		0x97
#define EK_PAGEUP	0x98
#define EK_PAGEDN	0x99
#define EK_CHARLT	0x9A
#define EK_CHARRT	0x9B
#define EK_LINEDN	0x9C
#define EK_LINEUP	0x9D

//Keypad keys
#define NK_NUMLCK	0x9E
#define NK_DIVIDE	0x9F
#define NK_MLTPLY	0xA0
#define NK_SBTRCT	0xA1
#define NK_ADDTN	0xA2
#define NK_ENTER	0xA3
#define NK_NMBR1	0xA4
#define NK_NMBR2	0xA5
#define NK_NMBR3	0xA6
#define NK_NMBR4	0xA7
#define NK_NMBR5	0xA8
#define NK_NMBR6	0xA9
#define NK_NMBR7	0xAA
#define NK_NMBR8	0xAB
#define NK_NMBR9	0xAC
#define NK_NMBR0	0xAD
#define NK_DECPNT	0xAE

//Modifier keys
#define MK_LSHIFT	0xAF
#define MK_RSHIFT	0xB0
#define MK_LCTRL	0xB1
#define MK_RCTRL	0xB2
#define MK_LALT		0xB3
#define MK_RALT		0xB4
#define MK_LGUI		0xB5	//Used for special Keyboard mode (not XT)
#define MK_RGUI		0xB6	//Used for special Keyboard mode (not XT)

//First and Last TI keyboard code
#define TIKB_FIRST_CODE	0x20		//Space
#define TIKB_LAST_CODE	MK_RALT		//Right Alt

//Undefined keys
#define XK_NOTDEF	0xB7	//ASCII key not defined (must be last definition)

//Pseudo USB modifier keys
//Modifier keys
#define USB_LSHIFT	0x66
#define USB_RSHIFT	0x67
#define USB_LCTRL	0x68
#define USB_RCTRL	0x69
#define USB_LALT	0x6A
#define USB_RALT	0x6B
#define USB_LGUI	0x6C
#define USB_RGUI	0x6D

//First Last USB code
#define USB_FIRST_CODE	0x04		//The A
#define USB_LAST_CODE	USB_RGUI	//Right Alt

//Modifier definitions for sending strings
#define SM_SHIFT 	0x01
#define SM_CTRL  	0x02
#define SM_ALT   	0x04
#define SM_GUI   	0x08
#define SM_BITMSK	0x0F

//Up key definitons
//x#define UP_NOUPCD	0x00	//Send no upcode
//x#define UP_STNDRD	0x10	//Upcode is Dncode | 0x80
//x#define	UP_AACODE	0x20	//Upcode is this code (0xAA)
//x#define UP_BITMSK	0x30	

//Key statuses
#define KBKEY_DN	0x01	//Key is down
#define KBKEY_UP	0x00	//Key is up

#define MAXCMDBUFSIZE	15	//Maximum size of command to find with <TAB> key
//x#define AUTOREPEATDELAY	1000	//Auto repeat delay [ms]
//x#define AUTOREPEATSPEED 80	//Auto repeat speed [ms]

//Special modes
#define KBSM_UNDEF	0	//Undefined
#define KBSM_MDOS	1	//Mdos mode
#define KBSM_BASIC	2	//Basic mode
#define KBSM_ASSM	3	//Assembler mode
#define KBSM_C99	4	//C99 mode

typedef struct _kbsmlist_
{
	byte  cmdnmb;		//Command number (alternatives has the same number)
				// and 0=end, 1=first, 255=last
	byte  altnmb;		//Alternative number, 0=none, 1=first, 255=last alternative
	byte  bsps;		//Backspaces
	const char *cmd;	//Command
} KBSMLIST;

typedef struct _cmdlist_
{
	const char *cmd;	//Command
} CMDLIST;
#endif