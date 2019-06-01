/*
 * TI99 Extended Basic Commands
 */
 
/*
 * When the keyboard is in basic mode ...
 * These lists are used with:
 * GUI+a..z
 * GUI+arrow left
 * GUI+arrow right
 * GUI+arrow up
 * GUI+arrow down
 *
 * ad  Address (-32768 - 32767)
 * al  Argument List
 * bc  Background Color (1-16)
 * bv  Byte Value (0-255)
 * c   Column (1-32)
 * cc  Character Code (ASCII value)
 * cs  Character Set  (0-14)
 * dc  Dot Column (1-256)
 * dl  Data List
 * dn  Device Program Name (DSK1.FILENAME)
 * dr  Dot Row (1-192)
 * dur Duration (1-4250, -1 - -4250
 * ec  Error Code
 * eln End Line Number
 * es  Error Severity
 * et  Error Type
 * ex  Expression
 * fc  Forground Color (1-16)
 * fn  File Number (0-255)
 * fo  File Organization (RELATIVE / SEQUENTIAL)
 * fu  Function Name
 * frq Frequency (110-44733, -1 - -8)
 * fs  Format String
 * ft  File Type (DISPLAY / INTERNAL)
 * inc Increment Value
 * iv  Initial Value
 * ku  Key Unit (0-5)
 * lmt Limit
 * ln  Line Number (1-32767)
 * mf  Magnify Factor (1-4)
 * ne  Nummeric Expression
 * nv  Numeric Variable
 * om  Open Mode (INPUT / UPDATE / OUTPUT / APPEND)
 * pl  Print List (String / Numeric variables, Strings)
 * r   Row (1-24)
 * re  Relation Expression
 * rad Radian Expression
 * rp  Repetition
 * rt  Record Type (VARIABLE / FIXED)
 * rn  Record Number (0-32767)
 * se  String Expression
 * sln Start Line Number
 * sn  Sprite Number (1-28)
 * st  Statement
 * sv  String Variable
 * t   Tolerance (pixels)
 * v   Variable (string / numeric)
 * vl  Variable List
 * vol Volume (0-30)
 * xr  X-return (-4,0,4)
 * yr  Y-return (-4,0,4)
 */
static const KBSMLIST Basic_Cmds_A[] =
{
	{ 1,  0, 3, "ABS(ne)"},
	{ 2,  0, 6, "ACCEPT AT(r,c):v"},
	{ 3,  0, 3, "ASC(se)"},
	{ 4,  0, 3, "ATN(ne)"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_B[] =
{
	{ 1,  0, 0, "BREAK"},
	{ 2,  0, 0, "BYE"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_C[] =
{
	{ 1,  0, 6, "CALL CHAR(cc,pi)"},
	{ 2,  0, 6, "CALL CHARPAT(cc,sv)"},
	{ 3,  0, 0, "CALL CHARSET"},
	{ 4,  0, 3, "CHR$(ne)"},
	{ 5,  0, 0, "CALL CLEAR"},
	{ 6,  0, 2, "CLOSE #fn"},
	{ 7,  1,12, "CALL COINC(#sn,#sn,t,nv)"},
	{ 7,  2,14, "CALL COINC(#sn,dr,dc,t,nv)"},
	{ 7,255, 3, "CALL COINC(ALL,nv)"},
	{ 8,  1, 6, "CALL COLOR(#sn,fc)"},
	{ 8,255, 9, "CALL COLOR(cs,fc,bc)"},
	{ 9,  0, 0, "CONTINUE"},
	{10,  0, 4, "COS(rad)"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_D[] =
{
	{ 1,  0, 2, "DATA dl"},
	{ 2,  0, 5, "DEF fu=ex"},
	{ 3,  0, 3, "DELETE \"dn\""},
	{ 4,  1, 3, "CALL DELSPRITE(#sn)"},
	{ 4,255, 0, "CALL DELSPRITE(ALL)"},
	{ 5,  0,11, "DIM an(i1[,i2...])"},
	{ 6,  1, 4, "DISPLAY AT(r,c)"},
	{ 6,  2,17, "DISPLAY [ol:] USING se:vl"},
	{ 6,255,17, "DISPLAY [ol:] USING ln:vl"},
	{ 7,  1,10, "CALL DISTANCE(#sn,#sn,nv)"},
	{ 7,255,12, "CALL DISTANCE(#sn,dr,dc,nv)"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_E[] =
{
	{ 1,  0, 0, "END"},
	{ 2,  0, 3, "EOF(fn)"},
	{ 3,  1, 6, "CALL ERR(ec,et)"},
	{ 3,255,12, "CALL ERR(ec,et,es,ln)"},
	{ 4,  0, 3, "EXP(ne)"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_F[] =
{
	{ 1,  1,12, "FOR nv=iv TO lmt"},
	{ 1,255,21, "FOR nv=iv TO lmt STEP inc"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_G[] =
{
	{ 1,  0, 7, "CALL GCHAR(r,c,nv)"},
	{ 2,  0, 2, "GOSUB ln"},
	{ 3,  0, 2, "GOTO ln"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_H[] =
{
	{ 1,  1, 7, "CALL HCHAR(r,c,cc)"},
	{ 1,255,10, "CALL HCHAR(r,c,cc,rp)"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_I[] =
{
	{ 1,  1,13, "IF re THEN ln/st"},
	{ 1,255,24, "IF re THEN ln/st ELSE ln/st"},
	{ 2,  0, 2, "IMAGE fs"},
	{ 3,  0, 0, "CALL INIT"},
	{ 4,  1, 2, "INPUT vl"},
	{ 4,  2,11, "INPUT \"prompt\": vl"},
	{ 4,  3, 6, "INPUT #fn: vl"},
	{ 4,255,14, "INPUT #fn, REC rn: vl"},
	{ 5,  0, 3, "INT(ne)"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_J[] =
{
	{ 1,  1, 6, "CALL JOYST(1,xr,yr)"},
	{ 1,255, 6, "CALL JOYST(2,xr,yr)"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_K[] =
{
	{ 1,  0,14, "CALL KEY(ku[0-5],rv,st)"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_L[] =
{
	{ 1,  0, 3, "LEN(se)"},
	{ 2,  0, 5, "LET nv=ne"},
	{ 3,  0, 9, "CALL LINK(\"name\",al)"},
	{ 4,  1, 2, "LINPUT vl"},
	{ 4,  2,11, "LINPUT \"prompt\": vl"},
	{ 4,  3, 6, "LINPUT #fn: vl"},
	{ 4,255,14, "LINPUT #fn, REC rn: vl"},
	{ 5,  1, 7, "LIST [\"dn\":]ln"},
	{ 5,255,12, "LIST [\"dn\":]sln-eln"},
	{ 6,  0,17, "CALL LOAD(\"name\",ad,bv[,...]"},
	{ 7,  0,15, "CALL LOCATE(#sn,dr,dc[,...])"},
	{ 8,  0, 3, "LOG(ne)"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_M[] =
{
	{ 1,  0, 8, "CALL MAGNIFY(mf[1-4])"},
	{ 2,  0, 6, "MAX(ne,ne)"},
	{ 3,  0, 2, "MERGE dn"},
	{ 4,  0, 6, "MIN(ne,ne)"},
	{ 5,  0,15, "CALL MOTION(#sn,rv,cv[,...])"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_N[] =
{
	{ 1,  0, 0, "NEW"},
	{ 2,  0, 2, "NEXT nv"},
	{ 3,  1, 0, "NUM"},
	{ 3,  2, 2, "NUM ln"},
	{ 3,255, 6, "NUM ln,inc"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_O[] =
{
	{ 1,  0, 2, "OLD dn"},
	{ 2,  1, 0, "ON BREAK STOP"},
	{ 2,  2, 0, "ON BREAK NEXT"},
	{ 2,  3, 0, "ON ERROR STOP"},
	{ 2,255, 2, "ON ERROR ln"},
	{ 3,  0,17, "ON ne GOSUB ln[,...]"},
	{ 4,  0,16, "ON ne GOTO ln[,...]"},
	{ 5,  1, 0, "ON WARNING PRINT"},
	{ 5,  2, 0, "ON WARNING STOP"},
	{ 5,255, 0, "ON WARNING NEXT"},
	{ 6,  0,17, "OPEN #fn:dn,fo,ft,om,rt"},
	{ 7,  0, 3, "OPTION BASE 0/1"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_P[] =
{
	{ 1,  0,12, "CALL PATTERN(#sn,cv[,...])"},
	{ 2,  0,12, "CALL PEEK(ad,nv[,...])"},
	{ 3,  0, 0, "PI"},
	{ 4,  0, 9, "POS(sv,sv,ne)"},
	{ 5,  0,15, "CALL POSITION(#sn,dr,dc[,...])"},
	{ 6,  1, 2, "PRINT pl"},
	{ 6,  2, 6, "PRINT TAB(ne);pl"},
	{ 6,  3, 6, "PRINT USING se: pl"},
	{ 6,255, 6, "PRINT USING ln: pl"},
	{ 7,  1, 6, "PRINT #fn: pl"},
	{ 7,  2,14, "PRINT #fn, REC rn: pl"},
	{ 7,  3,15, "PRINT #fn USING se: pl"},
	{ 7,  4,15, "PRINT #fn USING ln: pl"},
	{ 7,  5,23, "PRINT #fn, REC rn USING se: pl"},
	{ 7,255,23, "PRINT #fn, REC rn USING ln: pl"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_R[] =
{
	{ 1,  0, 0, "RANDOMIZE"},
	{ 2,  0, 2, "READ vl"},
	{ 3,  0, 3, "REC(fn)"},
	{ 4,  0, 2, "REM cs"},
	{ 5,  1, 0, "RES"},
	{ 5,  2, 2, "RES ln"},
	{ 5,255, 6, "RES ln,inc"},
	{ 6,  1, 0, "RESTORE"},
	{ 6,  2, 2, "RESTORE ln"},
	{ 6,  3, 2, "RESTORE #fn"},
	{ 6,255,10, "RESTORE #fn, REC rn"},
	{ 7,  1, 0, "RETURN"},
	{ 7,  2, 2, "RETURN ln"},
	{ 7,255, 0, "RETURN NEXT"},
	{ 8,  0, 0, "RND"},
	{ 9,  0, 6, "RPT$(se,ne)"},
	{10,  1, 0, "RUN"},
	{10,  2, 2, "RUN ln"},
	{10,255, 3, "RUN \"dn\""},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_S[] =
{
	{ 1,  1, 2, "SAVE dn"},
	{ 1,  2, 8, "SAVE dn,MERGE"},
	{ 1,255,12, "SAVE dn,PROTECTED"},
	{ 2,  1, 3, "CALL SAY(ws)"},
	{ 2,  2, 3, "CALL SAY(,ds)"},
	{ 2,255, 6, "CALL SAY(ws,ds)"},
	{ 3,  0, 9, "CALL SCREEN(cc[1-16])"},
	{ 4,  0, 9, "SEG$(se,ps,ln)"},
	{ 5,  0, 3, "SIGN(ne)"},
	{ 6,  0, 4, "SIN(rad)"},
	{ 7,  0, 0, "SIZE"},
	{ 8,  0,18, "CALL SOUND(dur,frq,vol[,...])"},
	{ 9,  0, 6, "CALL SPGET(ws,sv)"},
	{10,  1,21, "CALL SPRITE(#sn,cv,sc,dr,dc[,...])"},
	{10,255,27, "CALL SPRITE(#sn,cv,sc,dr,dc,rv,cv[,...])"},
	{11,  0, 3, "SQR(ne)"},
	{12,  0, 0, "STOP"},
	{13,  0, 3, "STR$(ne)"},
	{14,  1, 4, "SUB name"},
	{14,255, 8, "SUB name(pl)"},
	{15,  0, 0, "SUBEND"},
	{16,  0, 0, "SUBEXIT"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_T[] =
{
	{ 1,  0, 4, "TAN(rad)"},
	{ 2,  0, 0, "TRACE"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_U[] =
{
	{ 1,  0, 0, "UNBREAK"},
	{ 2,  0, 0, "UNTRACE"},
	{ 0,  0, 0, NULL},
};

static const KBSMLIST Basic_Cmds_V[] =
{
	{ 1,  0, 3, "VAL(se)"},
	{ 2,  1, 7, "CALL VCHAR(r,c,cc)"},
	{ 2,255,10, "CALL VCHAR(r,c,cc,rp)"},
	{ 3,  0, 3, "CALL VERSION(nv)"},
	{ 0,  0, 0, NULL},
};

/*
 * When the keyboard is in basic mode ...
 * This list is used with the TAB key
 */
static const CMDLIST BasicCmds[] =
{
/* A */
	{ "ABS(" },
	{ "ACCEPT" },
	{ "ALL" },
	{ "ASC(" },
	{ "APPEND," },
	{ "AT(" },
	{ "ATN(" },
/* B */
	{ "BASE" },
	{ "BEEP" },
	{ "BREAK" },
	{ "BYE" },
/* C */
	{ "CALL" },
	{ "CHAR(" },
	{ "CHARPAT(" },
	{ "CHARSET" },
	{ "CHR$(" },
	{ "CLEAR" },
	{ "CLOSE #" },
	{ "COINC(#" },
	{ "COINC(ALL," },
	{ "COLOR(" },
	{ "COLOR(#" },
	{ "CON" },
	{ "CONTINUE" },
	{ "COS(" },
/* D */
	{ "DATA" },
	{ "DEF" },
	{ "DELETE" },
	{ "DELSPRITE(#" },
	{ "DELSPRITE(ALL)" },
	{ "DIM" },
	{ "DISPLAY" },
	{ "DISPLAY," },
	{ "DISTANCE(#" },
	{ "DSK1." },
	{ "DSK2." },
	{ "DSK3." },
	{ "DSK4." },
/* E */
	{ "ELSE" },
	{ "END" },
	{ "EOF(" },
	{ "ERASE ALL" },
	{ "ERR(" },
	{ "ERROR" },
	{ "EXP(" },
/* F */
	{ "FOR" },
	{ "FIXED," },
/* G */
	{ "GCHAR(" },
	{ "GOSUB" },
	{ "GOTO" },
/* H */
	{ "HDS1." },
	{ "HDS2." },
	{ "HDX1." },
	{ "HCHAR(" },
/* I */
	{ "IDE1." },
	{ "IDE2." },
	{ "IDE3." },
	{ "IDE4." },
	{ "IF" },
	{ "IMAGE" },
	{ "INIT" },
	{ "INPUT" },
	{ "INPUT," },
	{ "INT(" },
	{ "INTERNAL," },
/* J */
	{ "JOYST(" },
/* K */
	{ "KEY(" },
/* L */
	{ "LEN(" },
	{ "LET" },
	{ "LINK(" },
	{ "LINPUT" },
	{ "LINPUT #" },
	{ "LIST" },
	{ "LOAD(" },
	{ "LOCATE(#" },
	{ "LOG(" },
/* M */
	{ "MAGNIFY(" },
	{ "MAX(" },
	{ "MERGE" },
	{ "MIN(" },
	{ "MOTION(#" },
/* N */
	{ "NEW" },
	{ "NEXT" },
	{ "NUM" },
/* O */
	{ "OLD" },
	{ "ON" },
	{ "ON BREAK NEXT" },
	{ "ON BREAK STOP" },
	{ "ON ERROR" },
	{ "ON ERROR STOP" },
	{ "ON X GOTO" },
	{ "ON X GOSUB" },
	{ "ON WARNING NEXT" },
	{ "ON WARNING PRINT" },
	{ "ON WARNING STOP" },
	{ "OPEN #" },
	{ "OPTION" },
	{ "OPTION BASE" },
	{ "OUTPUT," },
/* P */
	{ "PATTERN(#" },
	{ "PEEK(" },
	{ "PI" },
	{ "POS(" },
	{ "POSITION(#" },
	{ "PRINT" },
	{ "PROTECTED" },
/* R */
	{ "RANDOM" },
	{ "RANDOMIZE" },
	{ "READ" },
	{ "REC X" },
	{ "REC(" },
	{ "RELATIVE," },
	{ "REM" },
	{ "RES" },
	{ "RESEQUENCE" },
	{ "RESTORE" },
	{ "RESTORE #" },
	{ "RETURN" },
	{ "RETURN NEXT" },
	{ "RND(" },
	{ "RPT$(" },
	{ "RUN" },
/* S */
	{ "SAVE" },
	{ "SAY(" },
	{ "SCS1." },
	{ "SCS2." },
	{ "SCS3." },
	{ "SCS4." },
	{ "SCREEN(" },
	{ "SEG$(" },
	{ "SEQUENTIAL" },
	{ "SIGN(" },
	{ "SIN(" },
	{ "SIZE" },
	{ "SOUND(" },
	{ "SPGET(" },
	{ "SPRITE(#" },
	{ "SQR(" },
	{ "STEP" },
	{ "STOP" },
	{ "STR$(" },
	{ "SUB" },
	{ "SUBEND" },
	{ "SUBEXIT" },
/* T */
	{ "TAB(" },
	{ "TAN(" },
	{ "THEN" },
	{ "TO" },
	{ "TRACE" },
/* U */
	{ "UNBREAK" },
	{ "UNTRACE" },
	{ "UPDATE," },
	{ "USING" }, 
/* V */
	{ "VAL(" },
	{ "VALIDATE(" },
	{ "VARIABLE," },
	{ "VCHAR(" },
	{ "VERSION(" },
/* W */
	{ "WDS1." },
	{ "WDS2." },
	{ "WARNING" },
	
/*END*/
	{ NULL },
};