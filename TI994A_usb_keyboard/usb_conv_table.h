/*
 * USB Keyboard CODE to ASCII conversion table
 */

//USB Keyboard table definition
typedef struct _usbkeyconv_
{
	uchar Asc_Code;		//Ascii code
	uchar Usb_Code;		//Usb Scan code
} USBKEYCONV;

//In order of USB key code (0x04-0x63)
static USBKEYCONV UsbKeyConv[] =
{ //     Kb          Usb
	{'a',        0x04},
	{'b',        0x05},
	{'c',        0x06},
	{'d',        0x07},
	{'e',        0x08},
	{'f',        0x09},
	{'g',        0x0A},
	{'h',        0x0B},
	{'i',        0x0C},
	{'j',        0x0D},
	{'k',        0x0E},
	{'l',        0x0F},
	{'m',        0x10},
	{'n',        0x11},
	{'o',        0x12},
	{'p',        0x13},
	{'q',        0x14},
	{'r',        0x15},
	{'s',        0x16},
	{'t',        0x17},
	{'u',        0x18},
	{'v',        0x19},
	{'w',        0x1A},
	{'x',        0x1B},
	{'y',        0x1C},
	{'z',        0x1D},
	{'1',        0x1E},		// [1] [!]
	{'2',        0x1F},		// [2] [@]
	{'3',        0x20},		// [3] [#]
	{'4',        0x21},		// [4] [$]
	{'5',        0x22},		// [5] [%]
	{'6',        0x23},		// [6] [^]
	{'7',        0x24},		// [7] [&]
	{'8',        0x25},		// [8] [*]
	{'9',        0x26},		// [9] [(]
	{'0',        0x27},		// [0] [)]
	{ SK_ENTER,  0x28},		// [Enter]
	{ SK_ESCAPE, 0x29},		// [Esc]
	{ SK_BACKSP, 0x2A},		// [<--]
	{ SK_TAB,    0x2B},		// [->|]
	{' ',        0x2C},		// [   ]
	{'-',        0x2D},		// [-] [_]
	{'=',        0x2E},		// [=] [+]
	{'[',        0x2F},		// [[] [{]
	{']',        0x30},		// []] [}]
	{'\\',       0x31},		// [\] [|]
	{ XK_NOTDEF, 0x32},		// Not defined
	{';',        0x33},		// [;] [:]
	{'\'',       0x34},		// ['] ["]
	{'`',        0x35},		// [`] [~]
	{',',        0x36},		// [,] [<]
	{'.',        0x37},		// [.] [>]
	{'/',        0x38},		// [/] [?]
	{ SK_CPSLCK, 0x39},
	{ FK_F01,    0x3A},
	{ FK_F02,    0x3B},
	{ FK_F03,    0x3C},
	{ FK_F04,    0x3D},
	{ FK_F05,    0x3E},
	{ FK_F06,    0x3F},
	{ FK_F07,    0x40},
	{ FK_F08,    0x41},
	{ FK_F09,    0x42},
	{ FK_F10,    0x43},
	{ FK_F11,    0x44},
	{ FK_F12,    0x45},
	{ SK_PRTSCR, 0x46},
	{ SK_SCRLCK, 0x47},
	{ SK_PAUSE,  0x48},
	{ EK_INSERT, 0x49},
	{ EK_HOME,   0x4A},
	{ EK_PAGEUP, 0x4B},
	{ EK_DELETE, 0x4C},
	{ EK_END,    0x4D},
	{ EK_PAGEDN, 0x4E},
	{ EK_CHARRT, 0x4F},
	{ EK_CHARLT, 0x50},
	{ EK_LINEDN, 0x51},
	{ EK_LINEUP, 0x52},
	{ NK_NUMLCK, 0x53},		// Keypad NumLock
	{ NK_DIVIDE, 0x54},		// Keypad [/]
	{ NK_MLTPLY, 0x55},		// Keypad [*]
	{ NK_SBTRCT, 0x56},		// Keypad [-]
	{ NK_ADDTN,  0x57},		// Keypad [+]
	{ NK_ENTER,  0x58},		// Keypad [Enter]
	{ NK_NMBR1,  0x59},		// Keypad [1]
	{ NK_NMBR2,  0x5A},		// Keypad [2]
	{ NK_NMBR3,  0x5B},		// Keypad [3]
	{ NK_NMBR4,  0x5C},		// Keypad [4]
	{ NK_NMBR5,  0x5D},		// Keypad [5]
	{ NK_NMBR6,  0x5E},		// Keypad [6]
	{ NK_NMBR7,  0x5F},		// Keypad [7]
	{ NK_NMBR8,  0x60},		// Keypad [8]
	{ NK_NMBR9,  0x61},		// Keypad [9]
	{ NK_NMBR0,  0x62},		// Keypad [0]
	{ NK_DECPNT, 0x63},		// Keypad [.]
	{ XK_NOTDEF, 0x64},		// Not defined
	{ SK_WMENU,  0x65},		// Menu key

//Pseudo USB modifier keys
	{ MK_LSHIFT, USB_LSHIFT}, 	// Modifier [L Shift]
	{ MK_RSHIFT, USB_RSHIFT},	// Modifier [R Shift]
	{ MK_LCTRL,  USB_LCTRL},	// Modifier [L Control]
	{ MK_RCTRL,  USB_RCTRL},	// Modifier [R Control]
	{ MK_LALT,   USB_LALT},		// Modifier [L Alt]
	{ MK_RALT,   USB_RALT},		// Modifier [R Alt]
	{ MK_LGUI,   USB_LGUI},		// Modifier [L Gui]
	{ MK_RGUI,   USB_RGUI},		// Modifier [R Gui]
};


/* GetUsbKeyConv - Get USB Key Conversion Struct
 *
 * Input : USB key code
 * Return: UsbKeyConv
 * Error : NULL
 */
static USBKEYCONV *GetUsbKeyConv(byte key)
{
  if ((key >= USB_FIRST_CODE) && (key <= USB_LAST_CODE))
  {
	return &UsbKeyConv[key-0x04];
  }
  return NULL;
}
