// Aipi_Init.h: interface for the CAipi_Init class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_INIT_H__368195C7_596A_4EAF_9C3F_1FAA7AED25D1__INCLUDED_)
#define AFX_AIPI_INIT_H__368195C7_596A_4EAF_9C3F_1FAA7AED25D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <iterator>
#include <functional>
#include <stack>



enum AIPI_KEYWORDS 
{
	//AIPI Keywords
	AIPI_ADDRULE = 400,				//ADD_RULE			400
	AIPI_ADDRESS_INDEX,				//ADDRESS_INDEX		401
	AIPI_AND,						//AND				402 
	AIPI_ASSERT,					//ASSERT			403	
	AIPI_BIND,						//BIND				404	
	AIPI_CF,						//CF				405
	AIPI_CHAR,						//CHAR				406	
	AIPI_CLASS,						//CLASS				407
	AIPI_CLOSE_FILE,				//CLOSE_FILE		408
	AIPI_DB_CLOSE,					//DB_CLOSE			409
	AIPI_DB_DNS,					//DB_DNS			410
	AIPI_DB_NAME,					//DB_NAME			411
	AIPI_DB_OPEN,					//DB_OPEN			412
	AIPI_DB_PROVIDER,				//DB_PROVIDER		413
	AIPI_DB_PASSWORD,				//DB_PASSWORD		414
	AIPI_DB_USER,					//DB_USER			415	
	AIPI_DOUBLE,					//DOUBLE			416	
	AIPI_END,						//END				417
	AIPI_EXEC,						//EXEC				418
	AIPI_EXIST,						//EXIST				419
	
	AIPI_FACT_ADDRESS,				//FACT_ADDRESS		420
	AIPI_FLOAT,						//FLOAT				421
	AIPI_FORALL,					//FORALL			422
	AIPI_FUNCTION,					//FUNCTION			
	AIPI_FUZZY,						//FUZZY				423
	AIPI_FUZZY_UNCERT,				//FUZZY_UNCERT		424
	AIPI_GOTO_RULE,					//GOTO_RULE			425
	AIPI_HALT,						//HALT				426
	AIPI_IF,						//IF				427
	AIPI_INCLUDE,					//INCLUDE			428	
	AIPI_INIT,						//INIT				429
	AIPI_INPUT,						//INPUT				430
	AIPI_INT,						//INT				431
	AIPI_LANGUAGE,					//LANGUAGE			431
	AIPI_LONG,						//LONG				432
	AIPI_MODIFY,					//MODIFY			433
	AIPI_NOT,						//NOT				434
	AIPI_QUERY,						//QUERY
	AIPI_OPEN_FILE,					//OPEN_FILE			435
	AIPI_OR,						//OR				436
	AIPI_ORDER,						//ORDER				437
	AIPI_OUTPUT,					//ORDER				437
	AIPI_PRINTOUT,					//PRINTOUT			438
	AIPI_PRIORITY,					//PRIORITY			439
	AIPI_PAUSE,						//PAUSE				440
	
	AIPI_RECENCY,					//RECENCY			441
	AIPI_RETRACT,					//RETRACT			442
	AIPI_RULE,						//RULE				443
	AIPI_SAVE_FILE,					//SAVE_FILE			444
	AIPI_SCRIPT,					//SCRIPT			445
	AIPI_SHORT,						//SHORT				446
	AIPI_SHOW,						//SHOW				447
	AIPI_SQL,						//SQLQUERY			448
	AIPI_SQLQUERY,					//SQLQUERY			448
	AIPI_STRING,					//STRING			449
	AIPI_STRATEGY,				    //STRATEGY		    450
	AIPI_THEN,						//THEN				451
	AIPI_UNCERT,					//UNCERT			452
	AIPI_VARIABLE,					//VARIABLE			
	AIPI_VOID,						//VOID				453
	AIPI_WEIGHT,					//WEIGHT			454
	AIPI_WHEN,						//WHEN				455

	AIPI_CR_PRIORITY,				//CR_PRIORITY
	AIPI_CR_RECENCY,				//CR_RECENCY
	AIPI_CR_SPECIFICITY,			//CR_SPECIFICITY
	AIPI_CR_ORDER,					//CR_ORDER
	AIPI_CR_LEX,					//CR_LEX
	AIPI_CR_MEA						//CR_MEA

	
	
};






enum C_KEYWORDS 
{
	
	//Keywords ANSI C89
	C_AUTO = 500,					//C_AUTO		500
	C_BREAK,						//C_BREAK		501
	C_CASE,							//C_CASE		502
	C_CHAR,							//C_CHAR		503
	C_CONST,						//C_CONST		504
	C_CONTINUE,						//C_CONTINUE	505
	C_DEFAULT,						//C_DEFAULT		506
	C_DO,							//C_DO			507
	C_DOUBLE,						//C_DOUBLE		508
	C_ELSE,							//C_ELSE		509
	C_ENUM,							//C_ENUM		510
	C_EXTERN,						//C_EXTERN		511
	C_FLOAT,						//C_FLOAT		512
	C_FOR,							//C_FOR			513
	C_GOTO,							//C_GOTO		514
	C_IF,							//C_IF			515
	C_INT,							//C_INT			516
	C_LONG,							//C_LONG		517	
	C_REGISTER,						//C_REGISTER	518
	C_RETURN,						//C_RETURN		519
	C_SHORT,						//C_SHORT		520
	C_SIGNED,						//C_SIGNED		521
	C_SIZEOF,						//C_SIZEOF		522
	C_STATIC,						//C_STATIC		523
	C_STRUCT,						//C_STRUCT		524
	C_SWITCH,						//C_SWITCH		525
	C_TYPEDEF,						//C_TYPEDEF		526
	C_UNION,						//C_UNION		527	
	C_UNSIGNED,						//C_UNSIGNED	528	
	C_VOID,							//C_VOID		529
	C_VOLATILE,						//C_VOLATILE	530
	C_WHILE,						//C_WHILE		531

	
	//Added Keywords ANSI C99			
	C_BOOL,							//C_BOOL		532
	C_COMPLEX,						//C_COMPLEX		533
	C_IMAGINARY,					//C_IMAGINARY	534
	C_INLINE,						//C_INLINE		535
	C_RESTRICT,						//C_RESTRICT	536

	CPP_CLASS						//CPP_CLASS		538

};


enum CTRL_KEYWORDS 
{
	
	AIPI_CTRL_IMAGEFILTER = 900,		//ImageFilterDlg		900
	AIPI_CTRL_JUKEBOX,					//JukeBoxDlg			901
	AIPI_CTRL_LISTOPTION,				//ListOptionCtrl		902
	AIPI_CTRL_MEDIAPLAYER,				//MediaPlayerDlg		903
	AIPI_CTRL_OLEDB,					//OleDBDlg				904

	AIPI_DISPLAYCTRL,
	AIPI_SHOWCTRL,
	AIPI_CTRLNAME,
	AIPI_PLAY,
	AIPI_PATH,
	AIPI_INSERT,
	AIPI_SHOWTABLES,
	AIPI_INPUTVAR

};



enum DB_KEYWORDS 
{
/*
	#define		MS_ACCESS		200
	#define		MS_SQLSERVER	201
	#define		MS_ORACLE		202
	#define		ORACLE			203
	#define		MYSQL			204
	#define		DB2				205
*/
	
	AIPI_MS_ACCESS = 200,				//Microsoft_Access_		200
	AIPI_MS_SQLSERVER,					//Microsoft_Sql_Server	201
	AIPI_MS_ORACLE,						//Microsoft_Oracle		202
	AIPI_ORACLE,						//Oracle				203
	AIPI_MYSQL,							//MySql					204
	AIPI_DB2,							//Db2					205
	AIPI_MS_ACCESS_UPP,					//MS_ACCESS				206
	AIPI_MS_SQLSERVER_UPP,				//MS_SQLSERVER			207
	AIPI_MS_ORACLE_UPP,					//MS_ORACLE				208
	AIPI_ORACLE_UPP,					//ORACLE				209
	AIPI_MYSQL_UPP,						//MYSQL					210
	AIPI_DB2_UPP						//DB2					211
	
};



enum JS_KEYWORDS 
{
	
	/*
	C_AUTO = 600,					//C_AUTO		500
	C_BREAK,						//C_BREAK		501
	C_CASE,							//C_CASE		502
	C_CHAR,							//C_CHAR		503
	C_CONST,						//C_CONST		504
	C_CONTINUE,						//C_CONTINUE	505
	C_DEFAULT,						//C_DEFAULT		506
	C_DO,							//C_DO			507
	C_DOUBLE,						//C_DOUBLE		508
	C_ELSE,							//C_ELSE		509
	C_ENUM,							//C_ENUM		510
	C_EXTERN,						//C_EXTERN		511
	C_FLOAT,						//C_FLOAT		512
	C_FOR,							//C_FOR			513
	C_GOTO,							//C_GOTO		514
	C_IF,							//C_IF			515
	C_INT,							//C_INT			516
	C_LONG,							//C_LONG		517	
	C_REGISTER,						//C_REGISTER	518
	C_RETURN,						//C_RETURN		519
	C_SHORT,						//C_SHORT		520
	C_SIGNED,						//C_SIGNED		521
	C_SIZEOF,						//C_SIZEOF		522
	C_STATIC,						//C_STATIC		523
	C_STRUCT,						//C_STRUCT		524
	C_SWITCH,						//C_SWITCH		525
	C_TYPEDEF,						//C_TYPEDEF		526
	C_UNION,						//C_UNION		527	
	C_UNSIGNED,						//C_UNSIGNED	528	
	C_VOID,							//C_VOID		529
	C_VOLATILE,						//C_VOLATILE	530
	C_WHILE,						//C_WHILE		531
	C_BOOL,							//C_BOOL		532
	C_COMPLEX,						//C_COMPLEX		533
	C_IMAGINARY,					//C_IMAGINARY	534
	C_INLINE,						//C_INLINE		535
	C_RESTRICT,						//C_RESTRICT	536
	*/
	JS_FUNCTION = 600				//JS_FUNCTION	600

};


enum VBS_KEYWORDS 
{
	/*
	C_AUTO = 700,					//C_AUTO		500
	C_BREAK,						//C_BREAK		501
	C_CASE,							//C_CASE		502
	C_CHAR,							//C_CHAR		503
	C_CONST,						//C_CONST		504
	C_CONTINUE,						//C_CONTINUE	505
	C_DEFAULT,						//C_DEFAULT		506
	C_DO,							//C_DO			507
	C_DOUBLE,						//C_DOUBLE		508
	C_ELSE,							//C_ELSE		509
	C_ENUM,							//C_ENUM		510
	C_EXTERN,						//C_EXTERN		511
	C_FLOAT,						//C_FLOAT		512
	C_FOR,							//C_FOR			513
	C_GOTO,							//C_GOTO		514
	C_IF,							//C_IF			515
	C_INT,							//C_INT			516
	C_LONG,							//C_LONG		517	
	C_REGISTER,						//C_REGISTER	518
	C_RETURN,						//C_RETURN		519
	C_SHORT,						//C_SHORT		520
	C_SIGNED,						//C_SIGNED		521
	C_SIZEOF,						//C_SIZEOF		522
	C_STATIC,						//C_STATIC		523
	C_STRUCT,						//C_STRUCT		524
	C_SWITCH,						//C_SWITCH		525
	C_TYPEDEF,						//C_TYPEDEF		526
	C_UNION,						//C_UNION		527	
	C_UNSIGNED,						//C_UNSIGNED	528	
	C_VOID,							//C_VOID		529
	C_VOLATILE,						//C_VOLATILE	530
	C_WHILE,						//C_WHILE		531
	C_BOOL,							//C_BOOL		532
	C_COMPLEX,						//C_COMPLEX		533
	C_IMAGINARY,					//C_IMAGINARY	534
	C_INLINE,						//C_INLINE		535
	C_RESTRICT,						//C_RESTRICT	536
	*/
	VBS_FUNCTION = 700,				//VBS_FUNCTION	700
	VBS_END							//VBS_END		701
};







enum AIPI_ERROR_MSG 
{
	//Lexical Errors
	LEXICAL = 2000,
	OVER_TK_LENGTH,

	//Sintax Errors
	SINTAX,
	NO_EXP,
	NO_VAR,
	SEMI_EXPECTED,
	UNBAL_BRACES,
	FUNC_UNDEF,	
	TYPE_EXPECTED,
	DIRECT_DECLARATOR,	
	PAREN_EXPECTED,	
	DO_WHILE_END,	
	QUOTE_EXPECTED,						
	BRACE_EXPECTED,	
	COLON_EXPECTED,
	
	//Semantic Errors
	SEMANT,
	TYPE_ASSIGN,
	TYPE_VERIFY,
	DUP_VAR,
	DUP_FUNC,
	FLOW_VERIFY,
	DIV_BY_ZERO,
	UNKNOW_TYPE,
	UNKNOW_CLASS,
	NOT_DECLARE,

	//Script Errors
	JSCRIPT,
	VBSCRIPT,
	JSCRIPT_PARAM,
	VBSCRIPT_PARAM,
	
	//Other Errors
	FILE_READ,
	DEBUG_STOP,
	ABNORMAL_STOP,
	FINISH,
	ERROR_COUNT,
	WARNING_COUNT,
	EMPTY_MSG,

	//Warnings
	TYPE_CONVERT,
	ELEMENT_MISSING
	
};







/*
	Symbols:
	ID	= Identifier (Id)   
	AT	= Atribute (Attr)  
	VL	= Value (Val)
	K	= Constant
	RO   = Relational Operator
*/


//Variables Categories

enum  AIPI_VAR_CATEGORY
{
	ID_K_K = 800,		//800
	K_AT_K,				//801	
	K_K_VL,				//802
	ID_AT_K,			//803
	ID_K_VL,			//804
	K_AT_VL,			//805
	ID_AT_VL,			//806	
	K_K_K,				//807

//Relational
	ID_RO_K,			//808
	ID_RO_VL,			//809
	K_RO_K,				//810
	K_RO_VL				//811

};

/*
	Data Type Symbols:
	I	= Integer (int)   
	L	= Long Integer(long)  
	F	= Floating-Point (float)
	D	= Double Floating-Point(double)
	S	= String (str)
	
*/

enum  AIPI_IAV_TYPE
{
	I_S_I = 820,	//820
	I_S_L,			//821
	I_S_F,			//822
	I_S_D,			//823
	I_S_S,			//824
		
	L_S_I,			//825
	L_S_L,			//826
	L_S_F,			//827	
	L_S_D,			//828
	L_S_S,			//829


	F_S_I,			//830
	F_S_L,			//831
	F_S_F,			//832
	F_S_D,			//833
	F_S_S,			//834


	D_S_I,			//835
	D_S_L,			//836
	D_S_F,			//837
	D_S_D,			//838
	D_S_S,			//839


	S_S_I,			//840
	S_S_L,			//841
	S_S_F,			//842
	S_S_D,			//843
	S_S_S,			//844


	I_I_I,			//845
	I_I_L,			//846	
	I_I_F,			//847
	I_I_D,			//848	
	I_I_S,			//849	

	L_I_I,			//850
	L_I_L,			//851
	L_I_F,			//852
	L_I_D,			//853
	L_I_S,			//854


	F_I_I,			//855
	F_I_L,			//856
	F_I_F,			//857
	F_I_D,			//858
	F_I_S,			//859

	D_I_I,			//860
	D_I_L,			//861
	D_I_F,			//862
	D_I_D,			//863
	D_I_S			//864

};




class CAipi_Init  
{
public:
	CAipi_Init();
	virtual ~CAipi_Init();



public:
	void	Initialize();

	void	fillAIPIKeyWords();
	void    fillDBKeyWords();
	void    fillCtrlKeyWords();
	void	fillCKeyWords();
	void	fillJScriptKeyWords();
	void	fillVBScriptKeyWords();
	
	void	fillID_AIPIKeyWords();
	void	fillID_DBKeyWords();
	void    fillID_CtrlKeyWords(); 
	void	fillID_CKeyWords();
	void	fillID_JScriptKeyWords();
	void	fillID_VBScriptKeyWords();
	

	void	fillOperator();
	void	fillErrorMsg();

};

#endif // !defined(AFX_AIPI_INIT_H__368195C7_596A_4EAF_9C3F_1FAA7AED25D1__INCLUDED_)
