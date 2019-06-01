/*
 * TI99 Keyboard functions
 */

/* Clever idea by Jedimatt42
 *
 * These arrays are is used to maintain the state of the TI keyboard
 * switches. When a column (Teensy input) is scanned by the TI, then
 * the rows (Teensy output) are set to match this state.
 * The state is updated by the key down and key up routines handling
 * the USB keyboard input.
 */
 
// PinX_IntY              3  4  5  6  7  8  9  10
byte Row_Pin06_P05[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
byte Row_Pin08_1Y1[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
byte Row_Pin09_1Y0[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
byte Row_Pin12_2Y0[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
byte Row_Pin13_2Y1[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
byte Row_Pin14_2Y2[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
byte Row_Pin15_2Y3[8] = { 0, 0, 0, 0, 0, 0, 0, 0 }; 

//TI keyboard pin to Teensy pin conversion table
const byte Ti_Pin_To_Teensy_Pin[16] = {
	0,			// Not used
	Teensy_PIN01_Int5,	// Ti Keyboard Pin #1  TI99KB_PIN01_Int5 
	Teensy_PIN02_Int6,	// Ti Keyboard Pin #2  TI99KB_PIN02_Int6 
	Teensy_PIN03_Int8,	// Ti Keyboard Pin #3  TI99KB_PIN03_Int8 
	Teensy_PIN04_Int4,	// Ti Keyboard Pin #4  TI99KB_PIN04_Int4 
	Teensy_PIN05_Int3,	// Ti Keyboard Pin #5  TI99KB_PIN05_Int3 
	Teensy_PIN06_P5,	// Ti Keyboard Pin #6  TI99KB_PIN06_P5   
	Teensy_PIN07_Int7,	// Ti Keyboard Pin #7  TI99KB_PIN07_Int7 
	Teensy_PIN08_1Y1,	// Ti Keyboard Pin #8  TI99KB_PIN08_1Y1  
	Teensy_PIN09_1Y0,	// Ti Keyboard Pin #9  TI99KB_PIN09_1Y0  
	Teensy_PIN10_Int9,	// Ti Keyboard Pin #10 TI99KB_PIN10_Int9 
	Teensy_PIN11_Int10,	// Ti Keyboard Pin #11 TI99KB_PIN11_Int10
	Teensy_PIN12_2Y0,  	// Ti Keyboard Pin #12 TI99KB_PIN12_2Y0  
	Teensy_PIN13_2Y1,	// Ti Keyboard Pin #13 TI99KB_PIN13_2Y1  
	Teensy_PIN14_2Y2,	// Ti Keyboard Pin #14 TI99KB_PIN14_2Y2  
	Teensy_PIN15_2Y3  	// Ti Keyboard Pin #15 TI99KB_PIN15_2Y3  
};

//TI keyboard pin to CoLumn pin in ROW conversion table
const byte Ti_Pin_To_Column_Pin[16] = {
	0xFF,			// Not used
	0,			// Ti Keyboard Pin #1  TI99KB_PIN01_Int5 
	1,			// Ti Keyboard Pin #2  TI99KB_PIN02_Int6 
	2,			// Ti Keyboard Pin #3  TI99KB_PIN03_Int8 
	3,			// Ti Keyboard Pin #4  TI99KB_PIN04_Int4 
	4,			// Ti Keyboard Pin #5  TI99KB_PIN05_Int3 
	0xFF,			// Ti Keyboard Pin #6  TI99KB_PIN06_P5   
	5,			// Ti Keyboard Pin #7  TI99KB_PIN07_Int7 
	0xFF,			// Ti Keyboard Pin #8  TI99KB_PIN08_1Y1  
	0xFF,			// Ti Keyboard Pin #9  TI99KB_PIN09_1Y0  
	6,			// Ti Keyboard Pin #10 TI99KB_PIN10_Int9 
	7,			// Ti Keyboard Pin #11 TI99KB_PIN11_Int10
	0xFF,  			// Ti Keyboard Pin #12 TI99KB_PIN12_2Y0  
	0xFF,			// Ti Keyboard Pin #13 TI99KB_PIN13_2Y1  
	0xFF,			// Ti Keyboard Pin #14 TI99KB_PIN14_2Y2  
	0xFF  			// Ti Keyboard Pin #15 TI99KB_PIN15_2Y3  
};


//TI99 Keyboard status
//static byte TI99Reset = FALSE;
static bool TI99Capsl = FALSE;
static bool TI99Numl  = TRUE;
static byte TI99Shift = 0x00;
static byte TI99Cntrl = 0x00;
static byte TI99Fnct  = 0x00;

//Time in ms since last keyboard scan
static ulong lastKeyboardScan = 0;

//Initialize the IO pins
static void Ti99_Init_IO(void)
{
	pinMode(Teensy_PIN06_P5,  INPUT_PULLUP);
	pinMode(Teensy_PIN08_1Y1, INPUT_PULLUP);
	pinMode(Teensy_PIN09_1Y0, INPUT_PULLUP);
	pinMode(Teensy_PIN12_2Y0, INPUT_PULLUP);
	pinMode(Teensy_PIN13_2Y1, INPUT_PULLUP);
	pinMode(Teensy_PIN14_2Y2, INPUT_PULLUP);
	pinMode(Teensy_PIN15_2Y3, INPUT_PULLUP);

	pinMode(Teensy_PIN01_Int5,  OUTPUT_OPENDRAIN);
	pinMode(Teensy_PIN02_Int6,  OUTPUT_OPENDRAIN);
	pinMode(Teensy_PIN03_Int8,  OUTPUT_OPENDRAIN);
	pinMode(Teensy_PIN04_Int4,  OUTPUT_OPENDRAIN);
	pinMode(Teensy_PIN05_Int3,  OUTPUT_OPENDRAIN);
	pinMode(Teensy_PIN07_Int7,  OUTPUT_OPENDRAIN);
	pinMode(Teensy_PIN10_Int9,  OUTPUT_OPENDRAIN);
	pinMode(Teensy_PIN11_Int10, OUTPUT_OPENDRAIN);
	
	digitalWrite(Teensy_PIN01_Int5,  HIGH);
	digitalWrite(Teensy_PIN02_Int6,  HIGH);
	digitalWrite(Teensy_PIN03_Int8,  HIGH);
	digitalWrite(Teensy_PIN04_Int4,  HIGH);
	digitalWrite(Teensy_PIN05_Int3,  HIGH);
	digitalWrite(Teensy_PIN07_Int7,  HIGH);
	digitalWrite(Teensy_PIN10_Int9,  HIGH);
	digitalWrite(Teensy_PIN11_Int10, HIGH);        
}   

/*  TI99_Clear_Kb_Output_Rows - Clear the keyboard output row arrays
 */
static void TI99_Clear_Kb_Output_Rows(void)
{
	memset(Row_Pin06_P05, 0, sizeof(Row_Pin06_P05));
	memset(Row_Pin08_1Y1, 0, sizeof(Row_Pin08_1Y1));
	memset(Row_Pin09_1Y0, 0, sizeof(Row_Pin09_1Y0));
	memset(Row_Pin12_2Y0, 0, sizeof(Row_Pin12_2Y0));
	memset(Row_Pin13_2Y1, 0, sizeof(Row_Pin13_2Y1));
	memset(Row_Pin14_2Y2, 0, sizeof(Row_Pin14_2Y2));
	memset(Row_Pin15_2Y3, 0, sizeof(Row_Pin15_2Y3)); 
}    

#if defined DEBUG_TI99_KEY_MATRIX
static void Debug_Ti99_Key_Matrix_Key(bool State, byte Col_Pin, TI99KEYCONV *pTI99KeyConv)
{
	Serial.print("Matrix: ");
	Serial.print(State ? "DOWN" : "UP");
	Serial.print(" ASC=0x");
	Serial.print(pTI99KeyConv->Asc_Code, HEX); 
	Serial.print(" RowPin=");
	Serial.print(pTI99KeyConv->Ti99_ChrInp, DEC); 
	Serial.print(" ColPin=");
	Serial.print(pTI99KeyConv->Ti99_ChrOut, DEC); 
	Serial.print(" Col#=");
	Serial.println(Col_Pin, DEC);
}

static void Debug_Ti99_Key_Matrix_Mfk(bool State, byte ModKey)
{
	Serial.print("Matrix: ");
	switch(ModKey)
	{
		case KBO_SHIFT: Serial.print("SHIFT"); break;
		case KBO_CTRL : Serial.print("CTRL "); break;
		case KBO_FNCT : Serial.print("FNCT "); break;
		default       : Serial.print("???? "); break;
	}
	Serial.print(" State=");
	Serial.println(State ? "DOWN" : "UP  ");
}
#endif


/* TI99_Write_Key_Down - Write a TI99 keyboard down key
 *
 */
static void TI99_Write_Key_Down(TI99KEYCONV *pTI99KeyConv)
{
	byte *pRow_Pin;
	byte Col_Pin;
	byte ModKey;
	
	Col_Pin = Ti_Pin_To_Column_Pin[pTI99KeyConv->Ti99_ChrOut];
#if defined DEBUG_TI99_KEY_MATRIX
	if (Col_Pin > 7)
	{
		Serial.print("Matrix: ERROR Col_Pin>7");
		return;
	}
#endif	
	
	switch(pTI99KeyConv->Ti99_ChrInp)
	{
	default:
	case TI99KB_PIN06_P5:  pRow_Pin = Row_Pin06_P05; break;
	case TI99KB_PIN08_1Y1: pRow_Pin = Row_Pin08_1Y1; break;
	case TI99KB_PIN09_1Y0: pRow_Pin = Row_Pin09_1Y0; break;
	case TI99KB_PIN12_2Y0: pRow_Pin = Row_Pin12_2Y0; break;
	case TI99KB_PIN13_2Y1: pRow_Pin = Row_Pin13_2Y1; break;
	case TI99KB_PIN14_2Y2: pRow_Pin = Row_Pin14_2Y2; break;
	case TI99KB_PIN15_2Y3: pRow_Pin = Row_Pin15_2Y3; break;
	}
	
	pRow_Pin[Col_Pin] = KBKEY_DN;
#if defined DEBUG_TI99_KEY_MATRIX
	Debug_Ti99_Key_Matrix_Key(KBKEY_DN, Col_Pin, pTI99KeyConv);
#endif

	ModKey = KBKEY_UP;
	if (TI99Shift || pTI99KeyConv->Ti99_ModKey == TI99MK_SHIFT) ModKey = KBKEY_DN;
	Col_Pin = Ti_Pin_To_Column_Pin[KBO_SHIFT];
	Row_Pin12_2Y0[Col_Pin] = ModKey;
#if defined DEBUG_TI99_KEY_MATRIX
	Debug_Ti99_Key_Matrix_Mfk(ModKey==KBKEY_DN, KBO_SHIFT);
#endif	
	ModKey = KBKEY_UP;
	if (TI99Cntrl || pTI99KeyConv->Ti99_ModKey == TI99MK_CTRL) ModKey = KBKEY_DN;
	Col_Pin = Ti_Pin_To_Column_Pin[KBO_CTRL];
	Row_Pin12_2Y0[Col_Pin] = ModKey;
#if defined DEBUG_TI99_KEY_MATRIX
	Debug_Ti99_Key_Matrix_Mfk(ModKey==KBKEY_DN, KBO_CTRL);
#endif	
	ModKey = KBKEY_UP;
	if (TI99Fnct || pTI99KeyConv->Ti99_ModKey == TI99MK_FNCT) ModKey = KBKEY_DN;
	Col_Pin = Ti_Pin_To_Column_Pin[KBO_FNCT];
	Row_Pin12_2Y0[Col_Pin] = ModKey;
#if defined DEBUG_TI99_KEY_MATRIX
	Debug_Ti99_Key_Matrix_Mfk(ModKey==KBKEY_DN, KBO_FNCT);
#endif	
}


/* TI99_Write_Key_Up - Write a TI99 keyboard up key
 *
 */
static void TI99_Write_Key_Up(TI99KEYCONV *pTI99KeyConv)
{
	byte *pRow_Pin;
	byte Col_Pin;
	
	Col_Pin = Ti_Pin_To_Column_Pin[pTI99KeyConv->Ti99_ChrOut];
	
	switch(pTI99KeyConv->Ti99_ChrInp)
	{
	default:
	case TI99KB_PIN06_P5:  pRow_Pin = Row_Pin06_P05; break;
	case TI99KB_PIN08_1Y1: pRow_Pin = Row_Pin08_1Y1; break;
	case TI99KB_PIN09_1Y0: pRow_Pin = Row_Pin09_1Y0; break;
	case TI99KB_PIN12_2Y0: pRow_Pin = Row_Pin12_2Y0; break;
	case TI99KB_PIN13_2Y1: pRow_Pin = Row_Pin13_2Y1; break;
	case TI99KB_PIN14_2Y2: pRow_Pin = Row_Pin14_2Y2; break;
	case TI99KB_PIN15_2Y3: pRow_Pin = Row_Pin15_2Y3; break;
	}
	
	pRow_Pin[Col_Pin] = KBKEY_UP;
#if defined DEBUG_TI99_KEY_MATRIX
	Debug_Ti99_Key_Matrix_Key(KBKEY_UP, Col_Pin, pTI99KeyConv);
#endif
	Col_Pin = Ti_Pin_To_Column_Pin[KBO_SHIFT];
	Row_Pin12_2Y0[Col_Pin] = TI99Shift ? KBKEY_DN : KBKEY_UP;
#if defined DEBUG_TI99_KEY_MATRIX
	Debug_Ti99_Key_Matrix_Mfk(TI99Shift, KBO_SHIFT);
#endif	
	Col_Pin = Ti_Pin_To_Column_Pin[KBO_CTRL];
	Row_Pin12_2Y0[Col_Pin] = TI99Cntrl ? KBKEY_DN : KBKEY_UP;
#if defined DEBUG_TI99_KEY_MATRIX
	Debug_Ti99_Key_Matrix_Mfk(TI99Cntrl, KBO_CTRL);
#endif	
	Col_Pin = Ti_Pin_To_Column_Pin[KBO_FNCT];
	Row_Pin12_2Y0[Col_Pin] = TI99Fnct ? KBKEY_DN : KBKEY_UP;
#if defined DEBUG_TI99_KEY_MATRIX
	Debug_Ti99_Key_Matrix_Mfk(TI99Fnct, KBO_FNCT);
#endif	
}

/* TI99_Write_Output_Pin - Write TI99 keyboard input pins
 *                         according to Row_Pin array
 */
static void TI99_Write_Input_Pins(byte *pRow)
{
	 digitalWrite(Teensy_PIN01_Int5, pRow[0] ? LOW : HIGH); 
	 digitalWrite(Teensy_PIN02_Int6, pRow[1] ? LOW : HIGH); 
	 digitalWrite(Teensy_PIN03_Int8, pRow[2] ? LOW : HIGH); 
	 digitalWrite(Teensy_PIN04_Int4, pRow[3] ? LOW : HIGH); 
	 digitalWrite(Teensy_PIN05_Int3, pRow[4] ? LOW : HIGH); 
	 digitalWrite(Teensy_PIN07_Int7, pRow[5] ? LOW : HIGH); 
	 digitalWrite(Teensy_PIN10_Int9, pRow[6] ? LOW : HIGH); 
	 digitalWrite(Teensy_PIN11_Int10,pRow[7] ? LOW : HIGH); 
};


/* TI99_Read_Output_Pins - Read TI99 keyboard output pins
 *                         and set input pins according to
 *                         Row_Pin array of the corresponding
 *                         output pin found LOW
 */
static void TI99_Read_Output_Pins(void)
{
#if defined TI99_KEY_INTERRUPT
  	// Stop interrupts so I don't get two with each column change.
  	// use Falling edge?
	noInterrupts();
#endif
	lastKeyboardScan = 0;

	//Only one output pin can be low at a time
	if (digitalRead(Teensy_PIN06_P5) == LOW)
	{
		TI99_Write_Input_Pins(Row_Pin06_P05);
	}	
	else if (digitalRead(Teensy_PIN08_1Y1) == LOW)
	{
		TI99_Write_Input_Pins(Row_Pin08_1Y1);
	}
	else if (digitalRead(Teensy_PIN09_1Y0) == LOW)
	{
		TI99_Write_Input_Pins(Row_Pin09_1Y0);
	}
	else if (digitalRead(Teensy_PIN12_2Y0) == LOW)
	{
		TI99_Write_Input_Pins(Row_Pin12_2Y0);
	}
	else if (digitalRead(Teensy_PIN13_2Y1) == LOW)
	{
		TI99_Write_Input_Pins(Row_Pin13_2Y1);
	}
	else if (digitalRead(Teensy_PIN14_2Y2) == LOW)
	{
		TI99_Write_Input_Pins(Row_Pin14_2Y2);
	}
	else if (digitalRead(Teensy_PIN15_2Y3) == LOW)
	{
		TI99_Write_Input_Pins(Row_Pin15_2Y3);
	}
	else
	{
		 digitalWrite(Teensy_PIN01_Int5, HIGH); 
		 digitalWrite(Teensy_PIN02_Int6, HIGH); 
		 digitalWrite(Teensy_PIN03_Int8, HIGH); 
		 digitalWrite(Teensy_PIN04_Int4, HIGH); 
		 digitalWrite(Teensy_PIN05_Int3, HIGH); 
		 digitalWrite(Teensy_PIN07_Int7, HIGH); 
		 digitalWrite(Teensy_PIN10_Int9, HIGH); 
		 digitalWrite(Teensy_PIN11_Int10,HIGH); 
	}

#if defined TI99_KEY_INTERRUPT
//	lastInterrupted = millis();
	interrupts();
#endif
}


#if defined TI99_KEY_INTERRUPT
/* TI99_Set_Keyboard_Interrupts - Set interrupt mode for keyboard input
 *                                signals.
 *
 * Interruptmode can be CHANGE, RISING, FALLING, LOW, HIGH.
 * CHANGE is choosen so that on falling edge a row can be written
 * to the output signals and on the rising edge the output signals can
 * be set high again.
 */
static void TI99_Set_Keyboard_Interrupts()
{
  int interruptMode = CHANGE;
  attachInterrupt(Teensy_PIN06_P5,  TI99_Read_Output_Pins, interruptMode);
  attachInterrupt(Teensy_PIN08_1Y1, TI99_Read_Output_Pins, interruptMode);
  attachInterrupt(Teensy_PIN09_1Y0, TI99_Read_Output_Pins, interruptMode);
  attachInterrupt(Teensy_PIN12_2Y0, TI99_Read_Output_Pins, interruptMode);
  attachInterrupt(Teensy_PIN13_2Y1, TI99_Read_Output_Pins, interruptMode);
  attachInterrupt(Teensy_PIN14_2Y2, TI99_Read_Output_Pins, interruptMode);
  attachInterrupt(Teensy_PIN15_2Y3, TI99_Read_Output_Pins, interruptMode);
}
#endif


/* TI99_Background_Kscan
 *
 * Some keyboard functions are scanned in an alternative way, like
 * fctn-= (Quit) and fctn-4 (Break) and maybe some other methods
 * I don't know about.
 *
 * It seems that Quit waits for the key release with the same output
 * line held low. This will never work properly with the 
 * TI99_Read_Output_Pins() function because there are no changes in the
 * output pins anymore and therefore this function never is called again.
 * The same thing hapens with the Break function if a Basic program
 * never does any input function like INPUT or CALL KEY (10 goto 10)
 *
 * The big idea is to measure the time between calls of the
 * TI99_Read_Output_Pins() function. If this is more then x ms 
 * then that function is called anyway so that the last USB keyboard
 * state is written and can be read by the TI99.
 */
static void TI99_Background_Kscan(void)
{
	static ulong PrevMillis = 0;
	ulong CurMillis = millis();
	ulong PastMillis;
	
	if (PrevMillis == 0)
	{
		PastMillis = 0;
	}
	else
	{
		PastMillis = CurMillis - PrevMillis;
	}
	PrevMillis = CurMillis;
	
	lastKeyboardScan += PastMillis;
	
	if (lastKeyboardScan > 500)
	{
		TI99_Read_Output_Pins();
	}
}


/* TI99_Write_Chars - Write TI99 keyboard N Characters
 *
 */
static void TI99_Write_Chars(byte chr, byte cnt)
{
	byte ix;
	TI99KEYCONV *pTI99KeyConv;
	
	pTI99KeyConv = GetTI99KeyConv(chr);

	for (ix=0; ix<cnt; ix+=1)
	{
		TI99_Write_Key_Down(pTI99KeyConv);
		_delay_ms(25);
		TI99_Write_Key_Up(pTI99KeyConv);
		_delay_ms(25);
	}
}


/* TI99_Write_String - Write an TI99 keyboard string
 *
 */
static void TI99_Write_String(const char *string)
{
	char chr;
	TI99KEYCONV *pTI99KeyConv;

	while(*string != '\0')
	{
		chr = *string++;
		
		pTI99KeyConv = GetTI99KeyConv(chr);
		
		if (pTI99KeyConv != NULL)
		{
			TI99_Write_Key_Down(pTI99KeyConv);
			_delay_ms(20);		//was 40
			TI99_Write_Key_Up(pTI99KeyConv);
			_delay_ms(20);		//was 40
		}
	}
}

/* TI99_Write_String_Bsps - Write an TI99 keyboard string and N backspaces
 *
 */
static void TI99_Write_String_Bsps(const char *string, byte bsps)
{
	TI99_Write_String(string);
	TI99_Write_Chars(EK_CHARLT, bsps);
}
