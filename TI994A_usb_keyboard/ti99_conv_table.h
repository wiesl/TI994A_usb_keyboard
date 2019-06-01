/*
 * TI99 Keyboard ASCII to SCANCODE conversion table
 */

/* TI99/4A
 * Keyboard
 * Connector
 *
 * Pin  1 - Int5  <-------------------------------------------------.
 * Pin  2 - Int6  <--------------------------------------------.    |
 * Pin  3 - Int8  <---------------------------------------.    |    |
 * Pin  4 - Int4  <----------------------------------.    |    |    |
 * Pin  5 - Int3  <-----------------------------.    |    |    |    |
 * Pin  6 - P5    --> --[AlphLock]--.           |    |    |    |    |
 * Pin  7 - Int7  <-----------------+------.    |    |    |    |    |
 * Pin  8 - 1Y1   --> -----|               |    |    |    |    |    |
 * Pin  9 - 1Y0   --> -----|               |    |    |    |    |    |
 * Pin 10 - Int9  <-------------------.    |    |    |    |    |    |
 * Pin 11 - Int10 <--------------.    |    |    |    |    |    |    |
 * Pin 12 - 2Y0   --> -----|     |    |    |    |    |    |    |    |
 * Pin 13 - 2Y1   --> -----|     |    |    |    |    |    |    |    |
 * Pin 14 - 2Y2   --> -----|     |    |    |    |    |    |    |    |
 * Pin 15 - 2Y3   --> -----|     |    |    |    |    |    |    |    |
 *                         |     |    |    |    |    |    |    |    |
 *                         |     |    |    |    |    |    |    |    |
 *                    1Y1 -+--->[Zz] [Qq] [!1] [-/] [:;] [Aa] [)0] [Pp] 
 *                         |                                            
 *                    1Y0 -+--->[Bb] [Tt] [%5] [Nn] [Hh] [Gg] [^6] [Yy] 
 *                         |                                            
 *                    2Y0 -+--->[  ] [ct] [fn] [+=] [sp] [sh] [  ] [en] 
 *                         |                                            
 *                    2Y1 -+--->[Xx] [Ww] [@2] [>.] [Ll] [Ss] [(9] [Oo]    
 *                         |                                            
 *                    2Y2 -+--->[Cc] [Ee] [#3] [<,] [Kk] [Dd] [*8] [Ii] 
 *                         |                                            
 *                    2Y3 -+--->[Vv] [Rr] [$4] [Mm] [Jj] [Ff] [&7] [Uu] 
 *                              
 */

/*
 * Usb Host pins
 * max Reset 7
 * max GPX   8
 * INT       9
 * SS        10
 * MOSI      11
 * MISO      12
 * SCK       13
 *
 * A4=SDA    18 is combined with A6 pin 20 on Sparkfun converter for 
 *              Arduino Leonardo compatibility
 * A5=SCL    10 is combined with A7 pin 21 on Sparkfun converter for 
 *              Arduino Leonardo compatibility
 */

//Teensy IO Pin numbers
#define Teensy_PIN01_Int5  0		//Teensy Output (I,O,P,U,Y,Enter)
#define Teensy_PIN02_Int6  1		//Teensy Output (0,6,7,8,9)
#define Teensy_PIN03_Int8  2		//Teensy Output (A,D,F,G,S,Shift)
#define Teensy_PIN04_Int4  3		//Teensy Output (H,J,K,L,Space,;)
#define Teensy_PIN05_Int3  4		//Teensy Output (M,N,/,=,.,,)
#define Teensy_PIN06_P5    5		//Teensy Input  (Alpha lock)
#define Teensy_PIN07_Int7  6		//Teensy Output (1,2,3,4,5,Fnct,Alpha lock)
#define Teensy_PIN08_1Y1   14		//Teensy Input  (0,1,A,P,Q,Z,/,;)
#define Teensy_PIN09_1Y0   15		//Teensy Input  (5,6,B,G,H,N,T,Y)
#define Teensy_PIN10_Int9  16		//Teensy Output (E,Q,R,T,W,Ctrl)
#define Teensy_PIN11_Int10 17		//Teensy Output (B,C,V,X,Z)
#define Teensy_PIN12_2Y0   18		//Teensy Input  (Ctrl,Fnct,Space,Shift,Enter,=)
#define Teensy_PIN13_2Y1   19		//Teensy Input  (2,9,L,O,S,W,Q,.)
#define Teensy_PIN14_2Y2   22 //20	//Teensy Input  (3,8,C,D,E,I,K,,)
#define Teensy_PIN15_2Y3   23 //21	//Teensy Input  (4,7,F,J,M,R,U,V)
/* Pin 20,21 (A6,A7) are not simple accessable on a pin in the
 * Sparkfun converter therefor pin 22,23 (A8/A9) is used instead.
 */

#define TI99KB_PIN01_Int5  1 		//TI99KB Input  (I,O,P,U,Y,Enter)
#define TI99KB_PIN02_Int6  2 		//TI99KB Input  (0,6,7,8,9)
#define TI99KB_PIN03_Int8  3 		//TI99KB Input  (A,D,F,G,S,Shift)
#define TI99KB_PIN04_Int4  4 		//TI99KB Input  (H,J,K,L,Space,;)
#define TI99KB_PIN05_Int3  5 		//TI99KB Input  (M,N,/,=,.,,)
#define TI99KB_PIN06_P5    6 		//TI99KB Output (Alpha lock)
#define TI99KB_PIN07_Int7  7 		//TI99KB Input  (1,2,3,4,5,Fnct,Alpha lock)
#define TI99KB_PIN08_1Y1   8 		//TI99KB Output (0,1,A,P,Q,Z,/,;)
#define TI99KB_PIN09_1Y0   9 		//TI99KB Output (5,6,B,G,H,N,T,Y)
#define TI99KB_PIN10_Int9  10		//TI99KB Input  (E,Q,R,T,W,Ctrl)
#define TI99KB_PIN11_Int10 11		//TI99KB Input  (B,C,V,X,Z)
#define TI99KB_PIN12_2Y0   12		//TI99KB Output (Ctrl,Fnct,Space,Shift,Enter,=)
#define TI99KB_PIN13_2Y1   13		//TI99KB Output (2,9,L,O,S,W,Q,.)
#define TI99KB_PIN14_2Y2   14		//TI99KB Output (3,8,C,D,E,I,K,,)
#define TI99KB_PIN15_2Y3   15		//TI99KB Output (4,7,F,J,M,R,U,V)

#define TI99MK_NONE	0x00		//Set No modifier key
#define TI99MK_CAPSL	0x01		//Set Modifier key Caps Lock
#define TI99MK_SHIFT	0x02		//Set Modifier key Shift
#define TI99MK_CTRL	0x04		//Set Modifier key Control
#define TI99MK_FNCT	0x08		//Set Modifier key Function

/* Not yet sure how to do it so I create an input and
 * output define for every key on the TI99 keyboard
 * without a shift or other modifier keys involved.
 *
 * Other keys are these defines and some modifier keys
 * added.
 */

////TI99/4A Output is Teensy Input
#define KBI_ALPLCK	TI99KB_PIN06_P5		// Alpha Lock
#define KBI_NUMLCK	TI99KB_PIN06_P5		// Num   Lock (pseuso key)
#define KBI_SHIFT	TI99KB_PIN12_2Y0	// Shift
#define KBI_ENTER	TI99KB_PIN12_2Y0	// Enter
#define KBI_FNCT	TI99KB_PIN12_2Y0	// Function
#define KBI_CTRL	TI99KB_PIN12_2Y0	// Control
#define KBI_SPACE	TI99KB_PIN12_2Y0	// Space

#define KBI_EQUAL	TI99KB_PIN12_2Y0	// =
#define KBI_COMMA	TI99KB_PIN14_2Y2	// ,
#define KBI_PERIOD	TI99KB_PIN13_2Y1	// .
#define KBI_SLASH	TI99KB_PIN08_1Y1	// /
#define KBI_SMCLN	TI99KB_PIN08_1Y1	// ;

#define KBI_CHR_0	TI99KB_PIN08_1Y1
#define KBI_CHR_1	TI99KB_PIN08_1Y1
#define KBI_CHR_2	TI99KB_PIN13_2Y1
#define KBI_CHR_3	TI99KB_PIN14_2Y2
#define KBI_CHR_4	TI99KB_PIN15_2Y3
#define KBI_CHR_5	TI99KB_PIN09_1Y0
#define KBI_CHR_6	TI99KB_PIN09_1Y0
#define KBI_CHR_7	TI99KB_PIN15_2Y3
#define KBI_CHR_8	TI99KB_PIN14_2Y2
#define KBI_CHR_9	TI99KB_PIN13_2Y1

#define KBI_CHR_A	TI99KB_PIN08_1Y1
#define KBI_CHR_B	TI99KB_PIN09_1Y0
#define KBI_CHR_C	TI99KB_PIN14_2Y2
#define KBI_CHR_D	TI99KB_PIN14_2Y2
#define KBI_CHR_E	TI99KB_PIN14_2Y2
#define KBI_CHR_F	TI99KB_PIN15_2Y3
#define KBI_CHR_G	TI99KB_PIN09_1Y0
#define KBI_CHR_H	TI99KB_PIN09_1Y0
#define KBI_CHR_I	TI99KB_PIN14_2Y2
#define KBI_CHR_J	TI99KB_PIN15_2Y3
#define KBI_CHR_K	TI99KB_PIN14_2Y2
#define KBI_CHR_L	TI99KB_PIN13_2Y1
#define KBI_CHR_M	TI99KB_PIN15_2Y3
#define KBI_CHR_N	TI99KB_PIN09_1Y0
#define KBI_CHR_O	TI99KB_PIN13_2Y1
#define KBI_CHR_P	TI99KB_PIN08_1Y1
#define KBI_CHR_Q	TI99KB_PIN08_1Y1
#define KBI_CHR_R	TI99KB_PIN15_2Y3
#define KBI_CHR_S	TI99KB_PIN13_2Y1
#define KBI_CHR_T	TI99KB_PIN09_1Y0
#define KBI_CHR_U	TI99KB_PIN15_2Y3
#define KBI_CHR_V	TI99KB_PIN15_2Y3
#define KBI_CHR_W	TI99KB_PIN13_2Y1
#define KBI_CHR_X	TI99KB_PIN13_2Y1
#define KBI_CHR_Y	TI99KB_PIN09_1Y0
#define KBI_CHR_Z	TI99KB_PIN08_1Y1

//TI99/4A Input is Teensy Output
#define KBO_ALPLCK	TI99KB_PIN07_Int7	// Alpha Lock
#define KBO_SHIFT	TI99KB_PIN03_Int8	// Shift
#define KBO_ENTER	TI99KB_PIN01_Int5	// Enter
#define KBO_FNCT	TI99KB_PIN07_Int7	// Function
#define KBO_CTRL	TI99KB_PIN10_Int9	// Control
#define KBO_SPACE	TI99KB_PIN04_Int4	// Space

#define KBO_EQUAL	TI99KB_PIN05_Int3	// =
#define KBO_COMMA	TI99KB_PIN05_Int3	// ,
#define KBO_PERIOD	TI99KB_PIN05_Int3	// .
#define KBO_SLASH	TI99KB_PIN05_Int3	// /
#define KBO_SMCLN	TI99KB_PIN04_Int4	// ;

#define KBO_CHR_0	TI99KB_PIN02_Int6
#define KBO_CHR_1	TI99KB_PIN07_Int7
#define KBO_CHR_2	TI99KB_PIN07_Int7
#define KBO_CHR_3	TI99KB_PIN07_Int7
#define KBO_CHR_4	TI99KB_PIN07_Int7
#define KBO_CHR_5	TI99KB_PIN07_Int7
#define KBO_CHR_6	TI99KB_PIN02_Int6
#define KBO_CHR_7	TI99KB_PIN02_Int6
#define KBO_CHR_8	TI99KB_PIN02_Int6
#define KBO_CHR_9	TI99KB_PIN02_Int6

#define KBO_CHR_A	TI99KB_PIN03_Int8
#define KBO_CHR_B	TI99KB_PIN11_Int10
#define KBO_CHR_C	TI99KB_PIN11_Int10
#define KBO_CHR_D	TI99KB_PIN03_Int8
#define KBO_CHR_E	TI99KB_PIN10_Int9
#define KBO_CHR_F	TI99KB_PIN03_Int8
#define KBO_CHR_G	TI99KB_PIN03_Int8
#define KBO_CHR_H	TI99KB_PIN04_Int4
#define KBO_CHR_I	TI99KB_PIN01_Int5
#define KBO_CHR_J	TI99KB_PIN04_Int4
#define KBO_CHR_K	TI99KB_PIN04_Int4
#define KBO_CHR_L	TI99KB_PIN04_Int4
#define KBO_CHR_M	TI99KB_PIN05_Int3
#define KBO_CHR_N	TI99KB_PIN05_Int3
#define KBO_CHR_O	TI99KB_PIN01_Int5
#define KBO_CHR_P	TI99KB_PIN01_Int5
#define KBO_CHR_Q	TI99KB_PIN10_Int9
#define KBO_CHR_R	TI99KB_PIN10_Int9
#define KBO_CHR_S	TI99KB_PIN03_Int8
#define KBO_CHR_T	TI99KB_PIN10_Int9
#define KBO_CHR_U	TI99KB_PIN01_Int5
#define KBO_CHR_V	TI99KB_PIN11_Int10
#define KBO_CHR_W	TI99KB_PIN10_Int9
#define KBO_CHR_X	TI99KB_PIN11_Int10
#define KBO_CHR_Y	TI99KB_PIN01_Int5
#define KBO_CHR_Z	TI99KB_PIN11_Int10

#define KBI_NONE	0xFF	//Not used key input
#define KBO_NONE	0xFF	//Not used key output

//TI Keyboard table definition
typedef struct _ti99keyconv_
{
	uchar Asc_Code;		//Ascii code
	uchar Ti99_ChrInp;	//TI99 Character Input  line
	uchar Ti99_ChrOut;	//Ti99 Character Output line
	uchar Ti99_ModKey;	//TI99 Modifier  Key (Control, Shift, Function)
} TI99KEYCONV;

//In order of (pseudo) ASCII code
static TI99KEYCONV Ti99KeyConv[] =
{ //     Kb          ChrInp     ChrOut     ModKey			        Usb
	{' ',        KBI_SPACE, KBO_SPACE, TI99MK_NONE  },	// [ ]         	//0x2C,
	{'!',        KBI_CHR_1, KBO_CHR_1, TI99MK_SHIFT },	// [!] shft-[1] //0x1E,
	{'\"',       KBI_CHR_P, KBO_CHR_P, TI99MK_FNCT  },	// ["] fctn-[p] //0x34,
	{'#',        KBI_CHR_3, KBO_CHR_3, TI99MK_SHIFT },	// [#] shft-[3] //0x20,
	{'$',        KBI_CHR_4, KBO_CHR_4, TI99MK_SHIFT },	// [$] shft-[4] //0x21,
	{'%',        KBI_CHR_5, KBO_CHR_5, TI99MK_SHIFT },	// [%] shft-[5] //0x22,
	{'&',        KBI_CHR_7, KBO_CHR_7, TI99MK_SHIFT },	// [&] shft-[7] //0x24,
	{'\'',       KBI_CHR_O, KBO_CHR_O, TI99MK_FNCT  },	// ['] fctn-[O] //0x34,
	{'(',        KBI_CHR_9, KBO_CHR_9, TI99MK_SHIFT },	// [(] shft-[9] //0x26,
	{')',        KBI_CHR_0, KBO_CHR_0, TI99MK_SHIFT },	// [)] shft-[0] //0x27,
	{'*',        KBI_CHR_8, KBO_CHR_8, TI99MK_SHIFT },	// [*] shft-[8] //0x25,
	{'+',        KBI_EQUAL, KBO_EQUAL, TI99MK_SHIFT },	// [+] shft-[=] //0x2E,
	{',',        KBI_COMMA, KBO_COMMA, TI99MK_NONE  },	// [,]   	//0x36,
	{'-',        KBI_SLASH, KBO_SLASH, TI99MK_SHIFT },	// [-] shft-[/] //0x2D,
	{'.',        KBI_PERIOD,KBO_PERIOD,TI99MK_NONE  },	// [.] 		//0x37,
	{'/',        KBI_SLASH, KBO_SLASH, TI99MK_NONE  },	// [/] 		//0x38,
	{'0',        KBI_CHR_0, KBO_CHR_0, TI99MK_NONE  },	// [0]		//0x27,
	{'1',        KBI_CHR_1, KBO_CHR_1, TI99MK_NONE  },	// [1]		//0x1E,
	{'2',        KBI_CHR_2, KBO_CHR_2, TI99MK_NONE  },	// [2]		//0x1F,
	{'3',        KBI_CHR_3, KBO_CHR_3, TI99MK_NONE  },	// [3]		//0x20,
	{'4',        KBI_CHR_4, KBO_CHR_4, TI99MK_NONE  },	// [4]		//0x21,
	{'5',        KBI_CHR_5, KBO_CHR_5, TI99MK_NONE  },	// [5]		//0x22,
	{'6',        KBI_CHR_6, KBO_CHR_6, TI99MK_NONE  },	// [6]		//0x23,
	{'7',        KBI_CHR_7, KBO_CHR_7, TI99MK_NONE  },	// [7]		//0x24,
	{'8',        KBI_CHR_8, KBO_CHR_8, TI99MK_NONE  },	// [8]		//0x25,
	{'9',        KBI_CHR_9, KBO_CHR_9, TI99MK_NONE  },	// [9]		//0x26,
	{':',        KBI_SMCLN, KBO_SMCLN, TI99MK_SHIFT },	// [:] shft-[;]	//0x33,
	{';',        KBI_SMCLN, KBO_SMCLN, TI99MK_NONE  },	// [;]		//0x33,
	{'<',        KBI_PERIOD,KBO_PERIOD,TI99MK_SHIFT },	// [<] shft-[.]	//0x36,
	{'=',        KBI_EQUAL, KBO_EQUAL, TI99MK_NONE  },	// [=]		//0x2E,
	{'>',        KBI_COMMA, KBO_COMMA, TI99MK_SHIFT },	// [>] shft-[,]	//0x37,
	{'?',        KBI_CHR_I, KBO_CHR_I, TI99MK_FNCT  },	// [?] shft-[i] //0x38,
	{'@',        KBI_CHR_2, KBO_CHR_2, TI99MK_SHIFT },	// [@] shft-[2] //0x1F,
	{'A',        KBI_CHR_A, KBO_CHR_A, TI99MK_SHIFT },	// [A] shft-[a] //0x04,
	{'B',        KBI_CHR_B, KBO_CHR_B, TI99MK_SHIFT },	// [B] shft-[b] //0x05,
	{'C',        KBI_CHR_C, KBO_CHR_C, TI99MK_SHIFT },	// [C] shft-[c] //0x06,
	{'D',        KBI_CHR_D, KBO_CHR_D, TI99MK_SHIFT },	// [D] shft-[d] //0x07,
	{'E',        KBI_CHR_E, KBO_CHR_E, TI99MK_SHIFT },	// [E] shft-[e] //0x08,
	{'F',        KBI_CHR_F, KBO_CHR_F, TI99MK_SHIFT },	// [F] shft-[f] //0x09,
	{'G',        KBI_CHR_G, KBO_CHR_G, TI99MK_SHIFT },	// [G] shft-[g] //0x0A,
	{'H',        KBI_CHR_H, KBO_CHR_H, TI99MK_SHIFT },	// [H] shft-[h] //0x0B,
	{'I',        KBI_CHR_I, KBO_CHR_I, TI99MK_SHIFT },	// [I] shft-[i] //0x0C,
	{'J',        KBI_CHR_J, KBO_CHR_J, TI99MK_SHIFT },	// [J] shft-[j] //0x0D,
	{'K',        KBI_CHR_K, KBO_CHR_K, TI99MK_SHIFT },	// [K] shft-[k] //0x0E,
	{'L',        KBI_CHR_L, KBO_CHR_L, TI99MK_SHIFT },	// [L] shft-[l] //0x0F,
	{'M',        KBI_CHR_M, KBO_CHR_M, TI99MK_SHIFT },	// [M] shft-[m] //0x10,
	{'N',        KBI_CHR_N, KBO_CHR_N, TI99MK_SHIFT },	// [N] shft-[n] //0x11,
	{'O',        KBI_CHR_O, KBO_CHR_O, TI99MK_SHIFT },	// [O] shft-[o] //0x12,
	{'P',        KBI_CHR_P, KBO_CHR_P, TI99MK_SHIFT },	// [P] shft-[p] //0x13,
	{'Q',        KBI_CHR_Q, KBO_CHR_Q, TI99MK_SHIFT },	// [Q] shft-[q] //0x14,
	{'R',        KBI_CHR_R, KBO_CHR_R, TI99MK_SHIFT },	// [R] shft-[r] //0x15,
	{'S',        KBI_CHR_S, KBO_CHR_S, TI99MK_SHIFT },	// [S] shft-[s] //0x16,
	{'T',        KBI_CHR_T, KBO_CHR_T, TI99MK_SHIFT },	// [T] shft-[t] //0x17,
	{'U',        KBI_CHR_U, KBO_CHR_U, TI99MK_SHIFT },	// [U] shft-[u] //0x18,
	{'V',        KBI_CHR_V, KBO_CHR_V, TI99MK_SHIFT },	// [V] shft-[v] //0x19,
	{'W',        KBI_CHR_W, KBO_CHR_W, TI99MK_SHIFT },	// [W] shft-[w] //0x1A,
	{'X',        KBI_CHR_X, KBO_CHR_X, TI99MK_SHIFT },	// [X] shft-[x] //0x1B,
	{'Y',        KBI_CHR_Y, KBO_CHR_Y, TI99MK_SHIFT },	// [Y] shft-[y] //0x1C,
	{'Z',        KBI_CHR_Z, KBO_CHR_Z, TI99MK_SHIFT },	// [Z] shft-[z] //0x1D,
	{'[',        KBI_CHR_R, KBO_CHR_R, TI99MK_FNCT  },	// [[] fctn-[R] //0x2F,
	{'\\',       KBI_CHR_Z, KBO_CHR_Z, TI99MK_FNCT  },	// [\] fctn-[Z] //0x31,
	{']',        KBI_CHR_T, KBO_CHR_T, TI99MK_FNCT  },	// []] fctn-[T] //0x30,
	{'^',        KBI_CHR_6, KBO_CHR_6, TI99MK_SHIFT },	// [^] shft-[6]	//0x23,
	{'_',        KBI_CHR_U, KBO_CHR_U, TI99MK_FNCT  },	// [_] fctn-[u]	//0x2D,
	{'`',        KBI_CHR_C, KBO_CHR_C, TI99MK_FNCT  },	// [`] fctn-[c]	//0x35,
	{'a',        KBI_CHR_A, KBO_CHR_A, TI99MK_NONE  },	// [a]          //0x04,
	{'b',        KBI_CHR_B, KBO_CHR_B, TI99MK_NONE  },	// [b]          //0x05,
	{'c',        KBI_CHR_C, KBO_CHR_C, TI99MK_NONE  },	// [c]          //0x06,
	{'d',        KBI_CHR_D, KBO_CHR_D, TI99MK_NONE  },	// [d]          //0x07,
	{'e',        KBI_CHR_E, KBO_CHR_E, TI99MK_NONE  },	// [e]          //0x08,
	{'f',        KBI_CHR_F, KBO_CHR_F, TI99MK_NONE  },	// [f]          //0x09,
	{'g',        KBI_CHR_G, KBO_CHR_G, TI99MK_NONE  },	// [g]          //0x0A,
	{'h',        KBI_CHR_H, KBO_CHR_H, TI99MK_NONE  },	// [h]          //0x0B,
	{'i',        KBI_CHR_I, KBO_CHR_I, TI99MK_NONE  },	// [i]          //0x0C,
	{'j',        KBI_CHR_J, KBO_CHR_J, TI99MK_NONE  },	// [j]          //0x0D,
	{'k',        KBI_CHR_K, KBO_CHR_K, TI99MK_NONE  },	// [k]          //0x0E,
	{'l',        KBI_CHR_L, KBO_CHR_L, TI99MK_NONE  },	// [l]          //0x0F,
	{'m',        KBI_CHR_M, KBO_CHR_M, TI99MK_NONE  },	// [m]          //0x10,
	{'n',        KBI_CHR_N, KBO_CHR_N, TI99MK_NONE  },	// [n]          //0x11,
	{'o',        KBI_CHR_O, KBO_CHR_O, TI99MK_NONE  },	// [o]          //0x12,
	{'p',        KBI_CHR_P, KBO_CHR_P, TI99MK_NONE  },	// [p]          //0x13,
	{'q',        KBI_CHR_Q, KBO_CHR_Q, TI99MK_NONE  },	// [q]          //0x14,
	{'r',        KBI_CHR_R, KBO_CHR_R, TI99MK_NONE  },	// [r]          //0x15,
	{'s',        KBI_CHR_S, KBO_CHR_S, TI99MK_NONE  },	// [s]          //0x16,
	{'t',        KBI_CHR_T, KBO_CHR_T, TI99MK_NONE  },	// [t]          //0x17,
	{'u',        KBI_CHR_U, KBO_CHR_U, TI99MK_NONE  },	// [u]          //0x18,
	{'v',        KBI_CHR_V, KBO_CHR_V, TI99MK_NONE  },	// [v]          //0x19,
	{'w',        KBI_CHR_W, KBO_CHR_W, TI99MK_NONE  },	// [w]          //0x1A,
	{'x',        KBI_CHR_X, KBO_CHR_X, TI99MK_NONE  },	// [x]          //0x1B,
	{'y',        KBI_CHR_Y, KBO_CHR_Y, TI99MK_NONE  },	// [y]          //0x1C,
	{'z',        KBI_CHR_Z, KBO_CHR_Z, TI99MK_NONE  },	// [z]          //0x1D,
	{'{',        KBI_CHR_F, KBO_CHR_F, TI99MK_FNCT  },	// [{] fctn-[f]	//0x2F,
	{'|',        KBI_CHR_A, KBO_CHR_A, TI99MK_FNCT  },	// [|] fctn-[a]	//0x31,
	{'}',        KBI_CHR_G, KBO_CHR_G, TI99MK_FNCT  },	// [}] fctn-[g]	//0x30,
	{'~',        KBI_CHR_W, KBO_CHR_W, TI99MK_FNCT  },	// [~] fctn-[w]	//0x35,

//Pseudo ASCII special keys
	{ SK_ENTER,  KBI_ENTER, KBO_ENTER, TI99MK_NONE  },	// Enter	//0x28,
	{ SK_ESCAPE, KBI_NONE,  KBO_NONE,  TI99MK_NONE  }, 			//0x29,
	{ SK_BACKSP, KBI_CHR_S, KBO_CHR_S, TI99MK_FNCT  }, 	// BS  fctn-[S]	//0x2A,
	{ SK_TAB,    KBI_CHR_7, KBO_CHR_7, TI99MK_FNCT  },	// TAB fctn-[7] //0x2B,
	{ SK_PRTSCR, KBI_NONE,  KBO_NONE,  TI99MK_NONE  },			//0x46,
	{ SK_PAUSE,  KBI_NONE,  KBO_NONE,  TI99MK_NONE  },			//0x48,
	{ SK_CPSLCK, KBI_ALPLCK,KBO_ALPLCK,TI99MK_NONE  },			//0x39,
	{ SK_SCRLCK, KBI_NONE,  KBO_NONE,  TI99MK_NONE  },			//0x47,
	{ SK_WMENU,  KBI_NONE,  KBO_NONE,  TI99MK_NONE  },			//0x65,

//Pseudo ASCII function keys
	{ FK_F01,    KBI_CHR_1, KBO_CHR_1, TI99MK_FNCT  },	// DELETE  fctn-[1] //0x3A,
	{ FK_F02,    KBI_CHR_2, KBO_CHR_2, TI99MK_FNCT  },	// INSERT  fctn-[2] //0x3B,
	{ FK_F03,    KBI_CHR_3, KBO_CHR_3, TI99MK_FNCT  },	// ERASE   fctn-[3] //0x3C,
	{ FK_F04,    KBI_CHR_4, KBO_CHR_4, TI99MK_FNCT  },	// CLEAR   fctn-[4] //0x3D,
	{ FK_F05,    KBI_CHR_5, KBO_CHR_5, TI99MK_FNCT  },	// BEGIN   fctn-[5] //0x3E,
	{ FK_F06,    KBI_CHR_6, KBO_CHR_6, TI99MK_FNCT  },	// PROCEED fctn-[6] //0x3F,
	{ FK_F07,    KBI_CHR_7, KBO_CHR_7, TI99MK_FNCT  },	// AID     fctn-[7] //0x40,
	{ FK_F08,    KBI_CHR_8, KBO_CHR_8, TI99MK_FNCT  },	// REDO    fctn-[8] //0x41,
	{ FK_F09,    KBI_CHR_9, KBO_CHR_9, TI99MK_FNCT  },	// BACK    fctn-[9] //0x42,
	{ FK_F10,    KBI_CHR_0, KBO_CHR_0, TI99MK_FNCT  },	//         fctn-[0] //0x43,
	{ FK_F11,    KBI_NONE,  KBO_NONE,  TI99MK_NONE  },			//0x44,
	{ FK_F12,    KBI_NONE,  KBO_NONE,  TI99MK_NONE  },			//0x45,

//Pseudo ASCII edit keys
	{ EK_INSERT, KBI_CHR_2, KBO_CHR_2, TI99MK_FNCT  },	// INSERT  fctn-[2] //0x49,
	{ EK_DELETE, KBI_CHR_1, KBO_CHR_1, TI99MK_FNCT  },	// DELETE  fctn-[1] //0x4C,
	{ EK_HOME,   KBI_NONE,  KBO_NONE,  TI99MK_NONE  },	//Edit [Home]	//0x4A,
	{ EK_END,    KBI_NONE,  KBO_NONE,  TI99MK_NONE  },	//Edit [End]	//0x4D,
	{ EK_PAGEUP, KBI_CHR_4, KBO_CHR_4, TI99MK_FNCT  },	//Edit [PageUp] fctn[4]	//0x4B,
	{ EK_PAGEDN, KBI_CHR_6, KBO_CHR_6, TI99MK_FNCT  },	//Edit [PageDwn]fctn[6] //0x4E,
	{ EK_CHARLT, KBI_CHR_S, KBO_CHR_S, TI99MK_FNCT  },	//Edit [<-]	//0x50,
	{ EK_CHARRT, KBI_CHR_D, KBO_CHR_D, TI99MK_FNCT  },	//Edit [->]	//0x4F,
	{ EK_LINEDN, KBI_CHR_X, KBO_CHR_X, TI99MK_FNCT  },	//Edit [|^]	//0x51,
	{ EK_LINEUP, KBI_CHR_E, KBO_CHR_E, TI99MK_FNCT  },	//Edit [|v]	//0x52,

//Pseudo ASCII keypad keys
	{ NK_NUMLCK, KBI_NUMLCK,KBO_NONE,  TI99MK_NONE  },	//Keypad [Numlock]	//0x53,
	{ NK_DIVIDE, KBI_SLASH, KBO_SLASH, TI99MK_NONE  },	//Keypad [/]      	//0x54,
	{ NK_MLTPLY, KBI_CHR_8, KBO_CHR_8, TI99MK_SHIFT },	//Keypad [*] shft-[8]  	//0x55,
	{ NK_SBTRCT, KBI_SLASH, KBO_SLASH, TI99MK_SHIFT },	//Keypad [-] shft-[/]  	//0x56,
	{ NK_ADDTN,  KBI_EQUAL, KBO_EQUAL, TI99MK_SHIFT },	//Keypad [+] shft-[=]  	//0x57,
	{ NK_ENTER,  KBI_ENTER, KBO_ENTER, TI99MK_NONE  },	//Keypad [Enter]  	//0x58,
	{ NK_NMBR1,  KBI_CHR_1, KBO_CHR_1, TI99MK_NONE  },	//Keypad [1]      	//0x59,
	{ NK_NMBR2,  KBI_CHR_2, KBO_CHR_2, TI99MK_NONE  },	//Keypad [2]      	//0x5A,
	{ NK_NMBR3,  KBI_CHR_3, KBO_CHR_3, TI99MK_NONE  },	//Keypad [3]      	//0x5B,
	{ NK_NMBR4,  KBI_CHR_4, KBO_CHR_4, TI99MK_NONE  },	//Keypad [4]      	//0x5C,
	{ NK_NMBR5,  KBI_CHR_5, KBO_CHR_5, TI99MK_NONE  },	//Keypad [5]      	//0x5D,
	{ NK_NMBR6,  KBI_CHR_6, KBO_CHR_6, TI99MK_NONE  },	//Keypad [6]      	//0x5E,
	{ NK_NMBR7,  KBI_CHR_7, KBO_CHR_7, TI99MK_NONE  },	//Keypad [7]      	//0x5F,
	{ NK_NMBR8,  KBI_CHR_8, KBO_CHR_8, TI99MK_NONE  },	//Keypad [8]      	//0x60,
	{ NK_NMBR9,  KBI_CHR_9, KBO_CHR_9, TI99MK_NONE  },	//Keypad [9]      	//0x61,
	{ NK_NMBR0,  KBI_CHR_0, KBO_CHR_0, TI99MK_NONE  },	//Keypad [0]      	//0x62,
	{ NK_DECPNT, KBI_PERIOD,KBO_PERIOD,TI99MK_NONE  },	//Keypad [.]      	//0x63,

//Pseudo ASCII modifier keys
	{ MK_LSHIFT, KBI_SHIFT, KBO_SHIFT, TI99MK_NONE  },	//Modifier [L Shift]
	{ MK_RSHIFT, KBI_SHIFT, KBO_SHIFT, TI99MK_NONE  },	//Modifier [R Shift]
	{ MK_LCTRL,  KBI_CTRL,  KBO_CTRL,  TI99MK_NONE  },	//Modifier [L Control]
	{ MK_RCTRL,  KBI_CTRL,  KBO_CTRL,  TI99MK_NONE  },	//Modifier [R Control]
	{ MK_LALT,   KBI_FNCT,  KBO_FNCT,  TI99MK_NONE  },	//Modifier [L Alt]
	{ MK_RALT,   KBI_FNCT,  KBO_FNCT,  TI99MK_NONE  },	//Modifier [R Alt]
	{ MK_LGUI,   KBI_NONE,  KBO_NONE,  TI99MK_NONE  },	//Modifier [L GUI]
	{ MK_RGUI,   KBI_NONE,  KBO_NONE,  TI99MK_NONE  },	//Modifier [R GUI]

//Not defined key
	{ XK_NOTDEF, KBI_NONE,  KBO_NONE,  TI99MK_NONE  },	//Not defined
};


/* GetTI99KeyConv - Get TI99 Key Conversion struct
 *
 * Input : (pseudo) ascii code
 * Return: Ti99KeyConv
 * Error : NULL
 */
static TI99KEYCONV *GetTI99KeyConv(uchar chr)
{
  if ((chr >= TIKB_FIRST_CODE) && (chr <= TIKB_LAST_CODE))
  {
	return &Ti99KeyConv[chr-' '];
  }
  return NULL;
}
