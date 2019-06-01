/*
 * TI99 Keyboard Special Mode Functions
 */
 

static void UsbKbSpecialMode(byte ascii);
static void UsbKbEsc(const CMDLIST *CmdList);
static void UsbKbEscMode(void);
static void UsbKbTab(const CMDLIST *CmdList);
static void UsbKbTabMode(void);
static const KBSMLIST *NextCmd(const KBSMLIST *ThisCmd);
static const KBSMLIST *PrevCmd(const KBSMLIST *ThisCmd);
static const KBSMLIST *NextAltCmd(const KBSMLIST *ThisCmd);
static const KBSMLIST *PrevAltCmd(const KBSMLIST *ThisCmd);
static void UsbKbMode(byte ascii, const KBSMLIST *NewCmd);
static void UsbKbModeBasic(byte ascii);


static byte  AsciiCmdList = 0;		// Previous Ascii code command list
static const KBSMLIST *OldCmd = NULL;	// Old (Previous) Command

static byte  CmdBufferCnt = 0;		// Command to find with <TAB> key
static byte  CmdBufferIdx = 0;		// Last command send with <TAB> key
static char  CmdBuffer[MAXCMDBUFSIZE+1];


/*
 * NextCmd - Find next command
 */
static const KBSMLIST *NextCmd(const KBSMLIST *ThisCmd)
{
	byte  old_cmdnmb = ThisCmd->cmdnmb;
	
	if (ThisCmd != NULL)
	{
		while (ThisCmd->cmdnmb == old_cmdnmb)
		{
			ThisCmd += 1;
		}
		if (ThisCmd->cmdnmb == 0)	//END: Goto first command and first alternative
		{
			while (ThisCmd->cmdnmb != 1) ThisCmd -= 1;
			if (ThisCmd->altnmb != 0)
			{
				while (ThisCmd->altnmb != 1) ThisCmd -= 1;
			}
		}
	}
	return ThisCmd;
}

/*
 * PrevCmd - Find previous command
 */
static const KBSMLIST *PrevCmd(const KBSMLIST *ThisCmd)
{
	byte  old_cmdnmb = ThisCmd->cmdnmb;
	
	if (ThisCmd != NULL)
	{
		if (ThisCmd->cmdnmb == 1)	//BEGIN: Goto last and first alternative
		{
			while (ThisCmd->cmdnmb != 0) ThisCmd += 1;
			ThisCmd -= 1;
		}
		else
		{
			while (ThisCmd->cmdnmb == old_cmdnmb) ThisCmd -= 1;
		}
		if (ThisCmd->altnmb != 0)	// Goto first alternative
		{
			while (ThisCmd->altnmb != 1) ThisCmd -= 1;
		}			
	}
	return ThisCmd;
}

/*
 * NextAltCmd - Find next alternative command (if any)
 */
static const KBSMLIST *NextAltCmd(const KBSMLIST *ThisCmd)
{
	if (ThisCmd != NULL)
	{
		if (ThisCmd->altnmb == 0) return NextCmd(ThisCmd); 

		if (ThisCmd->altnmb == 255)	// Goto first alternative
		{
			while (ThisCmd->altnmb != 1) ThisCmd -= 1;
		}
		else
		{
			ThisCmd += 1;		// Goto next alternative
		}
	}
	return ThisCmd;
}

/*
 * PrevAltCmd - Find previous command (if any)
 */
static const KBSMLIST *PrevAltCmd(const KBSMLIST *ThisCmd)
{
	if (ThisCmd != NULL)
	{
		if (ThisCmd->altnmb == 0) return PrevCmd(ThisCmd);

		if (ThisCmd->altnmb == 1)	// Goto last alternative
		{
			while (ThisCmd->altnmb != 255) ThisCmd += 1;
		}
		else
		{
			ThisCmd -= 1;		// Goto previous alternative
		}
	}
	return ThisCmd;
}

/* UsbKbMode - Handle Special Keyboard Mode
 *
 * Input :  ascii code off function
 *          a-z : Sends command
 *          up  : Sends previous command
 *          dn  : Sends next command
 *          lft : Sends previous alternative
 *          rgt : Sends next alternative
 * Return: 
 * Error : 
 */
static void UsbKbMode(byte ascii, const KBSMLIST *NewCmd)
{
	const char *s = NULL;
	byte  bsps = 0;
	byte  size;

	if (NewCmd != NULL)	// New command list
	{
		AsciiCmdList = ascii;
	}
	else	// Same command list, maybe next/prev [alt] command
	{
		switch (ascii)
		{
		case EK_LINEDN:	NewCmd = NextCmd   (OldCmd); break;
		case EK_LINEUP:	NewCmd = PrevCmd   (OldCmd); break;
		case EK_CHARRT:	NewCmd = NextAltCmd(OldCmd); break;
		case EK_CHARLT:	NewCmd = PrevAltCmd(OldCmd); break;
		default: break;
		}
	}
	
	if ((NewCmd != NULL) && (NewCmd != OldCmd))
	{
		if (OldCmd != NULL)	// Remove previous command
		{
			size = strlen(OldCmd->cmd);
			bsps = OldCmd->bsps;
			if (bsps < size) TI99_Write_Chars(EK_CHARLT, size-bsps);
			TI99_Write_Chars(EK_DELETE, size);
		}
		OldCmd = NewCmd;

		s = NewCmd->cmd;
		bsps = NewCmd->bsps;
#if defined DEBUG_USB_SP_KM
		Serial.print("*** FUNC: ");
		Serial.println(s);
#endif
		if (bsps == 0)
		{
			TI99_Write_String(s);
		}
		else
		{
			TI99_Write_String_Bsps(s, bsps);
		}
	}
}


/* UsbKbModeBasic - Handle Special Keyboard Mode BASIC
 *
 * Input :  ascii code off function
 *          a-z : Sends command
 *          up  : Sends previous command
 *          dn  : Sends next command
 *          lft : Sends previous alternative
 *          rgt : Sends next alternative
 * Return: 
 * Error : 
 */
static void UsbKbModeBasic(byte ascii)
{
	const KBSMLIST *NewCmd = NULL;

	if (ascii == AsciiCmdList)
	{
		ascii = EK_LINEDN;
	}
	switch (ascii)
	{
	case 'a': NewCmd = Basic_Cmds_A; break;
	case 'b': NewCmd = Basic_Cmds_B; break;
	case 'c': NewCmd = Basic_Cmds_C; break;
	case 'd': NewCmd = Basic_Cmds_D; break;
	case 'e': NewCmd = Basic_Cmds_E; break;
	case 'f': NewCmd = Basic_Cmds_F; break;
	case 'g': NewCmd = Basic_Cmds_G; break;
	case 'h': NewCmd = Basic_Cmds_H; break;
	case 'i': NewCmd = Basic_Cmds_I; break;
	case 'j': NewCmd = Basic_Cmds_J; break;
	case 'k': NewCmd = Basic_Cmds_K; break;
	case 'l': NewCmd = Basic_Cmds_L; break;
	case 'm': NewCmd = Basic_Cmds_M; break;
	case 'n': NewCmd = Basic_Cmds_N; break;
	case 'o': NewCmd = Basic_Cmds_O; break;
	case 'p': NewCmd = Basic_Cmds_P; break;
	case 'r': NewCmd = Basic_Cmds_R; break;
	case 's': NewCmd = Basic_Cmds_S; break;
	case 't': NewCmd = Basic_Cmds_T; break;
	case 'u': NewCmd = Basic_Cmds_U; break;
	case 'v': NewCmd = Basic_Cmds_V; break;
	default : break;
	}

	UsbKbMode(ascii, NewCmd);
}

/* UsbKbSpecialMode - Handle Special Keyboard modes
 *
 * Input :  ascii code for mode of function
 * Return: 
 * Error : 
 */
static void UsbKbSpecialMode(byte ascii)
{
	//Define new special mode
	if (UsbLftGui && UsbRgtGui)
	{
		KeybMode = KBSM_UNDEF;
		CmdBufferCnt = 0;
		CmdBufferIdx = 0;
#if defined DEBUG_USB_SP_KM
		Serial.println("*** MODE: OFF");
#endif
		switch(ascii)
		{
		case 'b':		
#if defined DEBUG_USB_SP_KM
			Serial.println("*** MODE: BASIC");
#endif
			KeybMode = KBSM_BASIC;
			break;
		}
		return;
	}	

	switch(KeybMode)
	{
	case KBSM_BASIC: UsbKbModeBasic(ascii); break;
//	case KBSM_ASSM : UsbKbModeAssm(ascii); break;
//	case KBSM_C99  : UsbKbModeC99(ascii); break;
	case KBSM_UNDEF:
	default        : break;
	}
}


/* UsbKbEsc - Remove command suggestion
 *
 * Input :
 * Return: 
 * Error : 
 */
static void UsbKbEsc(const CMDLIST *CmdList)
{
	const CMDLIST *pCmd;
	byte  size;
	byte  bsps;
	
	pCmd = &CmdList[CmdBufferIdx-1];
	size = strlen(pCmd->cmd);
	if (size > CmdBufferCnt)
	{
		bsps = size - CmdBufferCnt;
		TI99_Write_Chars(EK_CHARLT, bsps);
		TI99_Write_Chars(EK_DELETE, bsps);
	}
}

/* UsbKbEscMode - Remove command suggestion
 *
 * Input :
 * Return: 
 * Error : 
 */
static void UsbKbEscMode(void)
{
	if (CmdBufferCnt == 0) return;	//Nothing in buffer
	if (CmdBufferIdx == 0) return;	//No previous suggestion

	switch(KeybMode)
	{
	case KBSM_BASIC: UsbKbEsc(BasicCmds); break;
	case KBSM_UNDEF:
	default        : break;
	}
	CmdBufferIdx = 0;
}

/* UsbKbTab - Find (next) command that looks like command in CmdBuffer
 *
 * Input :
 * Return: 
 * Error : 
 */
static void UsbKbTab(const CMDLIST *CmdList)
{
	const CMDLIST *pCmd;
	byte  startIdx;
//	byte  size;
//	byte  bsps;
	
	if (CmdBufferCnt == 0) return;

	if (CmdBufferIdx == 0)		//Start at beginning of list
	{
		CmdBufferIdx = 1;		
	}
	else				//Remove previous send command suggestion
	{
		UsbKbEsc(CmdList);
#if 0
		pCmd = &CmdList[CmdBufferIdx-1];
		size = strlen(pCmd->cmd);
		if (size > CmdBufferCnt)
		{
			bsps = size - CmdBufferCnt;
			TI99_Write_Chars(EK_CHARLT, bsps);
			TI99_Write_Chars(EK_DELETE, bsps);
		}
#endif
		CmdBufferIdx += 1;	//Next suggestion;
	}
	
	startIdx = CmdBufferIdx;
	
	do
	{
		pCmd = &CmdList[CmdBufferIdx-1];
		if (pCmd->cmd == NULL)
		{
			CmdBufferIdx = 1;
			continue;
		}

		if (strncmp(CmdBuffer, pCmd->cmd, CmdBufferCnt) == 0)
		{
#if defined DEBUG_USB_SP_KM
			Serial.print("Found: ");
			Serial.println(pCmd->cmd);
#endif		
			TI99_Write_String(&pCmd->cmd[CmdBufferCnt]);
			return;
		}
		CmdBufferIdx += 1;
	}
	while (startIdx != CmdBufferIdx);
	CmdBufferIdx = 0;
#if defined DEBUG_USB_SP_KM
	Serial.println("Found: No Match");
#endif		
}

/* UsbKbTabMode - Find command that looks like command in CmdBuffer
 *
 * Input :
 * Return: 
 * Error : 
 */
static void UsbKbTabMode(void)
{
	switch(KeybMode)
	{
	case KBSM_BASIC: UsbKbTab(BasicCmds); break;
	case KBSM_UNDEF:
	default        : break;
	}
}
