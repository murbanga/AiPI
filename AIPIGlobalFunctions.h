//------------------------------------------------------------------------------
// File: AIPIGlobalFunctions.h
//
// Desc: 
//
// Copyright (c) MEAP.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef AIPI_GLOBLAL_FUNCTION_H
#define AIPI_GLOBAL_FUNCTION_H


#include "stdafx.h"
#include ".\DataFileCSV\CDataFile.h"


/*
//
// Global data
//

//-----------------------------------------------------------------------------
// External identifiers for current project settings
//-----------------------------------------------------------------------------

extern CString		g_projectName;
extern CString		g_projectAuthor;
extern CString		g_projectDesc;
extern CString		g_projectRoot;
extern CString		g_projectDate;
extern CString		g_projectInference;
extern CString		g_projectResource[4];

//-----------------------------------------------------------------------------
// External flag for notification message CNotificationModified
//-----------------------------------------------------------------------------
extern bool g_bNotificationModified; 


//-----------------------------------------------------------------------------
// External identifiers for Internationalization
//-----------------------------------------------------------------------------
extern LANGID langSystem, langUser, languagePrimaryID;
extern LCID LCIDSystem, LCIDUser, languageLCID;



//-----------------------------------------------------------------------------
// External identifier for files .csv
//-----------------------------------------------------------------------------
extern CDataFile g_df;


//-----------------------------------------------------------------------------
// External identifier for skins
//-----------------------------------------------------------------------------

extern int g_iSkinType;



//-----------------------------------------------------------------------------
// External function-prototypes for Internationalization
//-----------------------------------------------------------------------------
LANGID	GetSystemLanguagePrimaryID(void);
LANGID	GetUserLanguagePrimaryID(void);
LCID	GetSystemLanguageLCID(void);
LCID	GetUserLanguageLCID(void);



//-----------------------------------------------------------------------------
// External constants for Ole DB  Database type manipulation
//-----------------------------------------------------------------------------


#define		MS_ACCESS		200
#define		MS_SQLSERVER	201
#define		MS_ORACLE		202
#define		ORACLE			203
#define		MYSQL			204
#define		DB2				205


extern   int		g_iDBProvider;
extern	 CString 	g_sDBName;
extern   CString	g_sDBUser;
extern   CString    g_sDBPassword;
extern   CString    g_sDBDNS;

//-----------------------------------------------------------------------------
// External constants for grid controls manipulation
//-----------------------------------------------------------------------------

#define GRID_LHS			0
#define GRID_RHS			1
#define GRID_WM				2
#define	GRID_COND_LINK		3
#define GRID_AGENDA			4
#define GRID_AM				5
#define GRID_BM				6
#define GRID_BM_TK			7
#define GRID_RETE			8
#define	GRID_INDUCTION		9

extern	int g_iRow;
extern  int g_iColumn;
extern  int g_iFixRow;
extern  int g_iFixColumn;

//-----------------------------------------------------------------------------
// External string input for Panel CommandWindow
//-----------------------------------------------------------------------------

extern CString	g_currentCmdInput;


//-----------------------------------------------------------------------------
// External flag for CImageList creation in CListOptionCtrl 
//-----------------------------------------------------------------------------
 extern bool g_ImageListFlag;

//-----------------------------------------------------------------------------
// External constants for AIPI Workspace Interface Store Option
//-----------------------------------------------------------------------------
#define		AIPI_REGISTRY		0
#define		AIPI_FILE			1

extern int  g_iWorkspaceStore;
extern CString g_sCurrentDir;

extern		HTREEITEM hTProjectRoot;
extern		HTREEITEM hTProjectRule;
extern		HTREEITEM hTProjectFunction;
extern		HTREEITEM hTProjectQuery;
extern		HTREEITEM hTProjectVariable;
extern		HTREEITEM hTProjectClass;
//-------------------------------------------------------------------------------
// Function Messages from AIPI Engine
//-------------------------------------------------------------------------------


#define		FOUND		 1	
#define		NOT_FOUND	-1
#define		P_SUCCESS	 1
#define		P_UNSUCCESS	-1	

#define		UNDEFINE	-2
#define		EMPTY		-3
#define		REPEATED	-4
#define		ABORT		-5
#define		AIPI_ERROR	-6
#define		AIPI_STOP   -7

//Negated Conditions
#define     POSITIVE	 1
#define		NEGATIVE	-1		
			
/*
	Symbols:
	AIPI_ID		= Identifier (Id)   
	AIPI_AT		= Atribute (Attr)  
	AIPI_VL		= Value (Val)
	AIPI_VAR	= Variable
	AIPI_K		= Constant
	AIPI_RO		= Relational Operator
*/

/*
#define		AIPI_ID			1
#define		AIPI_AT			2
#define		AIPI_VL			3
#define		AIPI_K			4
#define		AIPI_VAR		5
#define		AIPI_COND		6
#define		AIPI_FACT		7
#define		AIPI_LHS		8
#define		AIPI_RHS		9
#define		AIPI_RHSCMD		10
#define		AIPI_WM			11


*/



/*
	Symbols:
	DNode		= Dummy Node   
	JNode		= Join Node  
	NNode		= Negated Join Node
	PNode		= Production Node
	NCCNode		= Negated Conjunction Condition Node
	FPNode		= Fired Production Node
 */

/*
#define		DNode			-100
#define		JNode			-200
#define		NNode			-300
#define		PNode			-400
#define		NCCNode			-500
#define		FPNode			-600
#define		NumNode			-700	


*/



/*
	Data Type Symbols:
	I	= Integer (int)   
	L	= Long Integer(long)  
	F	= Floating-Point (float)
	D	= Double Floating-Point(double)
	S	= String (str)
	
*/

/*
#define		I_S_I		10
#define		I_S_L		11
#define		I_S_F		12
#define		I_S_D		13
#define		I_S_S		14

#define		L_S_I		20
#define		L_S_L		21
#define		L_S_F		22
#define		L_S_D		23
#define		L_S_S		24


#define		F_S_I		30
#define		F_S_L		31
#define		F_S_F		32
#define		F_S_D		33
#define		F_S_S		34


#define		D_S_I		40
#define		D_S_L		41
#define		D_S_F		42
#define		D_S_D		43
#define		D_S_S		44


#define		S_S_I		50
#define		S_S_L		51
#define		S_S_F		52
#define		S_S_D		53
#define		S_S_S		54


#define		I_I_I		60
#define		I_I_L		61
#define		I_I_F		62
#define		I_I_D		63
#define		I_I_S		64

#define		L_I_I		70
#define		L_I_L		71
#define		L_I_F		72
#define		L_I_D		73
#define		L_I_S		74


#define		F_I_I		80
#define		F_I_L		81
#define		F_I_F		82
#define		F_I_D		83
#define		F_I_S		84

#define		D_I_I		90
#define		D_I_L		91
#define		D_I_F		92
#define		D_I_D		93
#define		D_I_S		94
*/

//-----------------------------------------------------------------------------
// External constants for AIPI RETE Network
//-----------------------------------------------------------------------------

extern int  g_currentTimeTag;
extern int  g_currentLHS;
extern int  g_currentRHS;



extern int	g_currentAM;
extern int  g_currentBM;
extern int  g_currentJNode;
extern int  g_currentTK;
extern int  g_currentWM;
extern long g_currentFiredPM;

extern int  g_maxCRCicles; //Max cicles for conflict resolution test
extern int  g_CRStrategy; //Conflict resolution strategy
extern bool g_includeDirective;  //Flag for include files

//-------------------------------------------------------------------------------
// AIPI Conflict Resolution Strategies
//-------------------------------------------------------------------------------
/*
#define		CR_PRIORITY		1
#define		CR_RECENCY		2
#define		CR_SPECIFICITY	3
#define		CR_ORDER		4
#define		CR_LEX			5
#define		CR_MEA			6	
*/


//-------------------------------------------------------------------------------
// AIPI Parser Classes
//-------------------------------------------------------------------------------
#define		PARSER_FILE					9000
#define		EXP_PARSER_FILE				9001
#define     EXP_PARSER_FILE_GLOBAL		9002
#define		PARSER_GUI					9003
#define		EXP_PARSER_GUI				9004
#define		EXP_PARSER_GUI_GLOBAL		9005	

///_____________________________________________________________________________///

//////////////////////////////////////////////////////////////////////////////////
	//// AIPI Interpreter ////
///////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// External identifiers for AIPI Interpreter
//-----------------------------------------------------------------------------

//Interpreter global variables

extern  int     g_TkzCurrentIndex;  //This is the tokenizer index  for structure CAipi_Tokenizer
extern  int     g_TkzIndex1; //Command tokenizer initial index
extern  int     g_TkzIndex2; //Command tokenizer end index 
extern  CString g_currentFile;
extern	int		g_currentLine;
extern	long	g_currentPos;
extern  long	g_currentLookahead;
extern  long    g_currentDocEndPos;
extern  double	g_currentId_IForm;
extern  int		g_currentDataCateg;
extern  int     g_currentVarLoc;
extern	int		g_currentDigit_Type;
extern  int     g_currentParserClass;
extern	bool	g_bStopFlag;
extern	bool	g_bExecuteFlag;  


extern	int	g_LexError;
extern	int	g_SintaxError;
extern	int	g_SemantError;
extern	int	g_WarningError;
extern  int	g_StopError;
extern	int	g_QuestionError;
extern	int	g_InfoError; 	

extern	fpos_t			g_fcurrentPos;
extern	int				g_dataSource;
extern	FILE*			g_fp;
extern  CString			g_fText;
extern  CString			g_findText;	 

//Token maximun length
#define		MAX_TK_LEN			1000
#define		PROG_SIZE			10000
#define		MAX_SIZE_PATH		254


//Source code data extract from (Graphical User Interface(GUI) - File )
#define		DATA_GUI			0
#define		DATA_FILE			1 
#define		DATA_PROJECT		2 
#define     KEOF				65535	


////////////////////////////////////////////////////////
	/// AIPI Error Category ///
////////////////////////////////////////////////////////

#define		LEX_ERROR				0
#define		SINTAX_ERROR			1
#define		SEMANT_ERROR			2
#define		WARNING_ERROR			3
#define		QUESTION_ERROR			4
#define		STOP_ERROR				5
#define		INFO_ERROR				6
#define		JSCRIPT_ERROR			7
#define		VBSCRIPT_ERROR			8	



////////////////////////////////////////////////////////
	//// Blachslash Codes ////
////////////////////////////////////////////////////////

#define		NUL					0		/*		*/
#define		ALERT				7		/*	\a	*/
#define		BACKSPACE			8		/*	\b	*/
#define		HORIZONTAL_TAB		9		/*	\t	*/
#define		NEW_LINE			10		/*	\n	*/
#define		VERTICAL_TAB		11		/*	\v	*/
#define		FORWARD_FEED		12		/*	\f	*/
#define		CARRIAGE_RETURN		13		/*	\r	*/
#define		SPACE				32		/*	\0	*/



//////////////////////////////////////////////////////////
	///	Punctuators Symbols	///
//////////////////////////////////////////////////////////

#define		EXCLAMATION			33		/*	!	*/
#define		DOBLE_QUOTATION		34		/*	"	*/
#define		NUMBER_SIGN			35		/*	#	*/
#define		DOLLAR				36		/*	$	*/
#define		PERCENT				37		/*	%	*/
#define		AMPERSAND			38		/*	&	*/
#define		SINGLE_QUOTATION	39		/*	´	*/
#define		OPEN_PARENTHESIS	40		/*	(	*/
#define		CLOSE_PARENTHESIS	41		/*	)	*/
#define		COMMA				44		/*	,	*/
#define		PERIOD				46		/*	.	*/ 
#define		COLON				58		/*	:	*/
#define		SEMICOLON			59		/*	;	*/
#define		QUESTION			63		/*	?	*/
#define		AT_SYMBOL			64		/*	@	*/
#define		OPEN_BRACKET		91		/*	[	*/
#define		BACK_SLASH			92		/*	\	*/
#define		CLOSE_BRACKET		93		/*	]	*/
#define		UNDERSCORE			95		/*	_	*/
#define		OPEN_BRACE			123		/*	{	*/
#define		CLOSE_BRACE			125		/*	}	*/
#define		VERTICAL_BAR		124		/*	|	*/
#define		EQUIVALENCY			126		/*	~	*/




/////////////////////////////////////////////////////////
	/// Operators ///
////////////////////////////////////////////////////////

/// Arimethic Operators Symbols ///

#define		ASTERIC				42		/*	*	*/
#define		PLUS_SIGN			43		/*	+	*/
#define		MINUS_SIGN			45		/*	-	*/
#define		SLASH				47		/*	/	*/
#define		CARET				94		/*	^	*/	

/// Relational Operators Symbols ///

#define		LESS_THAN			60		/*	<	*/
#define		EQUAL				61		/*	=	*/
#define		GREATER_THAN		62		/*	>	*/

/// Boolean Values ///

#define		AIPI_TRUE			1		/*	true	*/
#define		AIPI_FALSE			0		/*	false	*/



/////////////////////////////////////////////////////////////////////
	/// Doble Character Operators ///
/////////////////////////////////////////////////////////////////////
/*
	Two-Character Symbols:

	EQ		= Equality for Strings
	LT		= Lesser than
	LE		= Lesser or Equal than
	GT		= Greater than 
	GE		= Greater or Equal than
	ET		= Equal than
	NE		= Not Equal than (Different)
	AS		= Asignation
	
	INPUT	= String input
	OUTPUT	= String output
	INC_OP	= Increse (++)
	DEC_OP	= Decrease (--)
	AND_BIT	= Exclusive AND (&)
	OR_BIT	= Exclusive OR (|)
	XOR_BIT	= Exclusive XOR (~)
	AND_OP	= AND (&&)
	OR_OP	= OR (||)
	NOT_OP	= NOT (!)
	

*/

#define		RIGHT_OP			300		/*	>>	*/
#define		LEFT_OP				301		/*	<<	*/
#define		INC_OP				302		/*	++	*/
#define		DEC_OP				303		/*	--	*/
#define		PTR_OP				304		/*	->	*/
#define		ADD_ASSIGN			305		/*	+=	*/
#define		SUB_ASSIGN			306		/*	-=  */
#define		MUL_ASSIGN			307		/*	*=	*/
#define		DIV_ASSIGN			308		/*	/=	*/				
#define		MOD_ASSIGN			309		/*	%=	*/
#define		AND_ASSIGN			310		/*  &=	*/
#define		XOR_ASSIGN			311		/*  ^=  */
#define		OR_ASSIGN			312		/*  |=  */




#define		EQ					320				/*		*/
#define		LT					60				/*	<	*/
#define		LE					321				/*	<=	*/
#define		GT					62				/*	>	*/
#define		GE					322				/*	>=	*/
#define		ET					323				/*	==	*/
#define		NE					324				/*	!=	*/
#define		AS					61				/*	=	*/
#define		AND_BIT				38				/*	&	*/
#define		OR_BIT				124				/*	|	*/
#define		XOR_BIT				94				/*	^	*/
#define		NOT_BIT				126				/*	~	*/
#define		AND_OP				325				/*	&&	*/
#define		OR_OP				326				/*	||	*/
#define		NOT_OP				33				/*	!	*/
#define		SCOPE_OP			327				/*  ::  */	


/////////////////////////////////////////////////////////////////////
	/// Triple Character Operators ///
/////////////////////////////////////////////////////////////////////

//   Three-Character Symbols:    

#define		ELLIPSIS			315				/*	...	*/
#define		RIGHT_ASSIGN 		316				/*	>>=	*/
#define		LEFT_ASSIGN			317				/*	<<=	*/
#define		UNARY_MINUS			318				/*  -   */	
#define		UNARY_PLUS			319				/*  +   */ 
#define		UNARY_OP			320				/* -, + */ 	
///////////////////////////////////////////////////////////////////
	///	Keywords ///
////////////////////////////////////////////////////////////////////

//Data Type Symbols:
/*
	AIPI_I	= Integer (int)   
	AIPI_L	= Long Integer(long)  
	AIPI_F	= Floating-Point (float)
	AIPI_D	= Double Floating-Point(double)
	AIPI_S	= String (str)
	AIPI_C	= Char (char)


#define		AIPI_INT				350
#define		AIPI_LONG				351
#define		AIPI_FLOAT				352
#define		AIPI_DOUBLE				353
#define		AIPI_STRING				354
#define		AIPI_CHAR				355
*/


////////////////////////////////////////////////////////////
	/// Token Types ////
///////////////////////////////////////////////////////////
#define		KEYWORD				360
#define		IDENTIFIER			361
#define		IDENTIFIER_SCRIPT	362
#define		IDENTIFIER_TYPE		363
#define		CONSTANT			364
#define		LITERAL				365
#define		OPERATOR			366
#define		PUNCTUATOR			367
#define		DIGIT				368
#define		COMMENT				369


#define		SIMPLE_COMMENT		370		
#define		COMPLEX_COMMENT		371		
#define		NAT_NUMBER			372
#define		REAL_NUMBER			373						
#define		STRING_LITERAL		374
#define		CHAR_LITERAL		375						
#define		BLOCK				376


///		Identifiers Types  ////

#define		CHART_IDENTIFIER		377	
#define		UCHART_IDENTIFIER		378
#define		INT_IDENTIFIER			379
#define		UINT_IDENTIFIER			380
#define		SHORT_INT_IDENTIFIER	381
#define		USHORT_INT_IDENTIFIER	382
#define		LONG_INT_IDENTIFIER		383
#define		ULONG_INT_IDENTIFIER	384	
#define		LONG_IDENTIFIER			385
#define		LONG_LONG_IDENTIFIER	386
#define		ULONG_LONG_IDENTIFIER	387
#define		FLOAT_IDENTIFIER		388
#define		DOUBLE_IDENTIFIER		389
#define		LONG_DOUBLE_IDENTIFIER	390	
#define		VOID_IDENTIFIER			391	


// File Extensions ////
#define TXT_EXT						392		//txt
#define KNW_EXT						393		//knw
#define	JS_EXT						394		//js
#define	VBS_EXT						395		//vbs
#define SQL_EXT						396		//sql
#define C_EXT						397		//c



#endif // !defined(AIPI_GLOBAL_FUNCTION_H)