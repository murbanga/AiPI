// Aipi_CParser.cpp: implementation of the CAipi_CParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_CParser.h"

#include "../MainFrm.h"
#include "../ChildFrm.h"
#include "../OutputTabView.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAipi_CParser::CAipi_CParser()
{
	m_lookahead = UNDEFINE;
	m_currentId_Type = UNDEFINE;
	m_jumpExit = false;
}

CAipi_CParser::~CAipi_CParser()
{

}

int CAipi_CParser::putbackToken(int step)
{
	/* 
	CAipi_Tokenizer tkz;

	int pos1 = UNDEFINE;
	int pos2 = tkz.lastPosition();
	
	tstring currentTk = tkz.findToken(pos2);
	AfxMessageBox(_T("Current TOKEN"));
	AfxMessageBox(currentTk.data());
	
	switch(step)
	{
	case 1:
		pos1 = tkz.stepback_1Pos();
		break;
	case 2:
		pos1 = tkz.stepback_2Pos();
		break;
	case 3:
		pos1 = tkz.stepback_3Pos();
		break;
	}
	
	tstring prevTk = tkz.findToken(pos1);
	AfxMessageBox(_T("Previous TOKEN"));
	AfxMessageBox(prevTk.data());
	
	
	g_currentPos = pos1;
	CAipi_Lexer lex;
	m_lookahead = lex.getTokenGUI();
*/
return m_lookahead;
}


unsigned int CAipi_CParser::getPreviousToken()
{
	/*
	CAipi_Tokenizer tkz;
	int iform = tkz.previousLastIntFormToken();
	*/

	int iform = 0;
	  
return iform;
}


int CAipi_CParser::matchToken(int tk )
{
	CAipi_Lexer lex;
	
	/*
	CString str;
	str.Format(_T("Incomming Token...%d  " ), tk);
	AfxMessageBox(str);
	*/
	
	//wsprintf(buffer, _T("Letra: %c"), tk);
	//AfxMessageBox(buffer);
	/*
	str.Format(_T("Look Ahead...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/	
	if ( m_lookahead != tk)
	{
		CString strSymbol = _T("");
		
		if( tk < 256 )
		{
			strSymbol.Format(_T("( %c )" ), tk);
			//AfxMessageBox(strSymbol);
		}
		else if( tk > 299 && tk < 328)
		{
			CAipi_Symbol sym;
			tstring sOP = sym.findOperator(tk);
			if( sOP != _T("NOT_FOUND"))
			{
				strSymbol = _T("( ");
				strSymbol += sOP.data();
				strSymbol += _T(" )");
				//AfxMessageBox(strSymbol);
			}

		}
		else if ( tk > 399 )
		{
			CAipi_Symbol sym;
			tstring sKW = sym.findIdKeyWord(tk);
			if( sKW != _T("NOT_FOUND"))
			{
				strSymbol = _T("( ");
				strSymbol += sKW.data();
				strSymbol += _T(" )");
				//AfxMessageBox(strSymbol);
			}

		}
		
		CAipi_Tokenizer tkz;
		tstring sTK = tkz.v_lastToken();
		
		CString  strTK = _T("( "); 
		strTK += sTK.data();
		strTK += _T(" )");
		//AfxMessageBox(tk.data());

		CAipi_Error err;
		err.displayGUIError(SINTAX, SINTAX_ERROR, _T(" Symbol " + strTK + " doesn't match. Expected symbol " + strSymbol + " was not found.") );
		//return SINTAX_ERROR;
	}

	
	
	if( g_dataSource == DATA_GUI )
	{
		++g_currentPos;
		m_lookahead = lex.getTokenGUI();
		if( m_lookahead == COMMENT )
		{
			do
			{
				++g_currentPos;
				m_lookahead = lex.getTokenGUI();
		
			}while (m_lookahead == COMMENT );
		}
		

	}
	else
	{
		TCHAR symbol =  _gettc(g_fp);
		m_lookahead = lex.getTokenFile(symbol);
	}

	

	if( m_lookahead == _TEOF )
		return _TEOF;

return 0;
}


int CAipi_CParser::matchTokenGUI(int tk )
{
	CAipi_Lexer lex;

	CString str;
	//TCHAR buffer[8];
	//str.Format(_T("Token entrante...%d  " ), tk);
	//AfxMessageBox(str);
	//wsprintf(buffer, _T("Letra: %c"), tk);
	//AfxMessageBox(buffer);
	
	if (m_lookahead == tk)
	{
		
		++g_currentPos;
		m_lookahead = lex.getTokenGUI();
		/*
		str.Format(_T("Look ahead...%d  " ), m_lookahead);
		AfxMessageBox(str);
		*/
		//wsprintf(buffer, _T("Letra: %c"), tk);
		//AfxMessageBox(buffer);
	
	}
	else 
	{	
		CAipi_Error err;
		err.displayGUIError(SINTAX, SINTAX_ERROR, _T("Symbol doesn't match.") );
		//return SYNTAX_ERROR;
	}

return 0;
}


int CAipi_CParser::matchTokenFile(int tk )
{
	CAipi_Lexer lex;

	CString str;
	TCHAR symbol;

	//TCHAR buffer[8];
	/*
	str.Format(_T("Token entrante...%d  " ), tk);
	AfxMessageBox(str);
	*/
	//wsprintf(buffer, _T("Letra: %c"), tk);
	//AfxMessageBox(buffer);
	
	if (m_lookahead == tk)
	{
		symbol =  _gettc(g_fp);
		m_lookahead = lex.getTokenFile(symbol);
		
		/*
		str.Format(_T("Look ahead...%d  " ), m_lookahead);
		AfxMessageBox(str);
		*/
		//wsprintf(buffer, _T("Letra: %c"), tk);
		//AfxMessageBox(buffer);
	
	}
	else 
	{	
		CAipi_Error err;
		err.displayFileError(SINTAX, SINTAX_ERROR, _T("Symbol doesn't match.") );
		//return SYNTAX_ERROR;
	}

return 0;
}



int CAipi_CParser::checkType()
{
	//CAipi_Tokenizer tkz;
	//int type_name = tkz.previousLastIntFormToken();
	/*
	CString str;
	str.Format(_T("Check_Type TYPE_NAME...%d  " ), m_currentId_Type);
	AfxMessageBox(str);
	AfxMessageBox(_T("IDENTIFIER"));
	*/

	if( 	m_currentId_Type == C_VOID 
		||	m_currentId_Type == C_CHAR
		||	m_currentId_Type == C_SHORT
		||	m_currentId_Type == C_INT
		||	m_currentId_Type == C_LONG
		||	m_currentId_Type == C_FLOAT
		||	m_currentId_Type == C_DOUBLE
		||	m_currentId_Type == C_SIGNED
		||	m_currentId_Type == C_UNSIGNED
		
		||	m_currentId_Type == C_STRUCT
		||	m_currentId_Type == C_UNION
		||	m_currentId_Type == C_ENUM
		
	   ) 
	{
		//CAipi_Symbol sym;
		//sym.addId_Type(g_currentId_IForm, m_currentId_Type);
		return IDENTIFIER;
		
	}


	
	return UNDEFINE;
}

void CAipi_CParser::initParser()
{
	CAipi_Lexer lex;
	CAipi_Emitter eo;

	
	if( g_dataSource == DATA_GUI )
	{
		m_lookahead = lex.getTokenGUI();
	}
	else
	{
		TCHAR symbol =  _gettc(g_fp);
		m_lookahead = lex.getTokenFile(symbol);
	}

	/*
	CString str;
	str.Format(_T("Look ahead con init ...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	//exec_directive();
	translation_unit();
		
	
	
	
	
 
}


void CAipi_CParser::directive_list()
{
	if( m_lookahead == NUMBER_SIGN )
	{
		directive();
		directive_list();
	}

}



void CAipi_CParser::directive()
{
	if( m_lookahead == NUMBER_SIGN )
	{
		matchToken( NUMBER_SIGN );
		matchToken( AIPI_INCLUDE );
		matchToken(LT);
		matchToken(IDENTIFIER);
		matchToken(PERIOD);
		matchToken( C_EXT );
		matchToken(GT);

	}

	
}



void CAipi_CParser::declaration_list()
{
	/*
	CString str;
	str.Format(_T("DECLARATION LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if(		m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED

		||	m_lookahead == C_STRUCT
		||	m_lookahead == C_UNION
		||	m_lookahead == C_ENUM
		
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER


		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE 
      )
	{
		declaration();
		declaration_list();
	}

	/*
	str.Format(_T("SALE DECLARATION LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
}





void CAipi_CParser::function_definition()
{
	/*
	CString str;
	str.Format(_T("FUNCTION DEFINITION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
		declaration_specifiers();

		if( m_lookahead == SEMICOLON )
		{
			matchToken(SEMICOLON);
			return;
			
		}
		else
		{
			init_declarator_list();
			if( m_lookahead == SEMICOLON )
			{
				matchToken(SEMICOLON);
				return;	
			}
			if( m_jumpExit )
			{
				return;
			}
			
		}

		//declarator();
	
		
		if(		m_lookahead == C_VOID 
			||	m_lookahead == C_CHAR
			||	m_lookahead == C_SHORT
			||	m_lookahead == C_INT
			||	m_lookahead == C_LONG
			||	m_lookahead == C_FLOAT
			||	m_lookahead == C_DOUBLE
			||	m_lookahead == C_SIGNED
			||	m_lookahead == C_UNSIGNED
			||	m_lookahead == C_STRUCT
			||	m_lookahead == C_UNION
			||	m_lookahead == C_ENUM   )
				
		{
			declaration_list();
		}

		compound_statement();
		
/*
	str.Format(_T("FUNCTION DEFINITION...%d  " ), m_lookahead);
	AfxMessageBox(str);
*/
}



void CAipi_CParser::external_declaration()
{
	/*
	CString str;
	str.Format(_T("EXTERNAL DECLARATION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

		
	if(		m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		
		||	m_lookahead == C_STRUCT
		||	m_lookahead == C_UNION
		||	m_lookahead == C_ENUM
		
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE

		
      )
	{
		function_definition();
		//declaration();
	}
	
	/*	
	str.Format(_T("SALE EXTERNAL DECLARATION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}





void CAipi_CParser::translation_unit()
{
	
	if( m_lookahead != _TEOF )
	{
		if( m_lookahead == COMMENT )
		{
			matchToken(COMMENT);
		}
	
		if( m_lookahead == NUMBER_SIGN )
		{
			directive_list();
		}

			
		if(		m_lookahead == C_VOID 
			||	m_lookahead == C_CHAR
			||	m_lookahead == C_SHORT
			||	m_lookahead == C_INT
			||	m_lookahead == C_LONG
			||	m_lookahead == C_FLOAT
			||	m_lookahead == C_DOUBLE
			||	m_lookahead == C_SIGNED
			||	m_lookahead == C_UNSIGNED
		
			||	m_lookahead == C_STRUCT
			||	m_lookahead == C_UNION
			||	m_lookahead == C_ENUM
		
			||	m_lookahead == C_TYPEDEF 
			||	m_lookahead == C_EXTERN
			||	m_lookahead == C_STATIC
			||	m_lookahead == C_AUTO
			||	m_lookahead == C_REGISTER

			||	m_lookahead == C_CONST
			||	m_lookahead == C_VOLATILE
			

          )
		{
			//external_declaration();
			function_definition();
			translation_unit();
		}
		else
		{
			CAipi_Error err;
			err.displayFileError(ABNORMAL_STOP, WARNING_ERROR, _T("The parser was not able to finish the depuration process. The initialization sintax is incorrect.") );
			
			
		}
	}
	else
	{
		TCHAR buffer[8];
		unsigned int nError = g_LexError + g_SintaxError + g_SemantError;
		unsigned int nWarning = g_WarningError + g_QuestionError;
		CString str_nError	=  _itot( nError, buffer, 10 );
		CString str_nWarning   =  _itot( nWarning, buffer, 10 );
		
		CString strLex		=  _itot( g_LexError, buffer, 10 );
		CString strSintax   =  _itot( g_SintaxError, buffer, 10 );
		CString strSemant	=  _itot( g_SemantError, buffer, 10 );
		CString	strWarning	=  _itot( g_WarningError, buffer, 10);
		CString	strQuestion	=  _itot( g_QuestionError, buffer, 10);
		
		//CString	strInfo		= _itot( g_InfoError, buffer, 10);
		//CString strStop		=  _itot( g_SintaxError, buffer, 10 );
		


		CAipi_Error err;
		err.displayFileError(EMPTY_MSG, -1, _T(" *************************************************************************************************************"));
		err.displayFileError(ERROR_COUNT, INFO_ERROR, _T(" Lexical errors:...") + strLex + _T("   Sintax errors:...") + strSintax + _T("   Semantic errors:...") + strSemant + _T("                    *Total errors:...") + str_nError );
		err.displayFileError(WARNING_COUNT, INFO_ERROR, _T(" Warnings:...") + strWarning + _T("   Warning questions:...") + strQuestion + _T("                    *Total warnings:...") + str_nWarning );
		err.displayFileError(FINISH, INFO_ERROR, _T("   **** Debug Summary:-    ") + str_nError + _T(" error(s),   ") + str_nWarning + _T(" warning(s). ****" ));

		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Debug Summary:-    ") + str_nError + _T(" error(s),   ") + str_nWarning + _T(" warning(s). ****" ));
		

	}
	

}



void CAipi_CParser::jump_statement()
{
	/*
	CString str;
	str.Format(_T("JUMP STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	switch(m_lookahead)
	{
		case C_GOTO:
			matchToken(C_GOTO);
			matchToken(IDENTIFIER);
			matchToken(SEMICOLON);
			break;
		case C_CONTINUE:
			matchToken(C_CONTINUE);
			matchToken(SEMICOLON);
			break;
		case C_BREAK:
			matchToken(C_BREAK);
			matchToken(SEMICOLON);
			break;
		case C_RETURN:
			matchToken(C_RETURN);
			if( m_lookahead != SEMICOLON )
			{
				expression();
			}
			matchToken(SEMICOLON);
			break;

	}
	/*
	str.Format(_T("SALE JUMP STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}




void CAipi_CParser::iteration_statement()
{
	/*
	CString str;
	str.Format(_T("ITERATION STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	CAipi_Tokenizer tkz;
	int tk_close_brace = UNDEFINE; 
	
	
	switch(m_lookahead)
	{
		case C_WHILE:
			tk_close_brace = tkz.v_previousLastIntFormToken();
			matchToken(C_WHILE);
			matchToken(OPEN_PARENTHESIS);
			expression();
			matchToken(CLOSE_PARENTHESIS);
			if( m_lookahead == SEMICOLON && tk_close_brace == CLOSE_BRACE )
			{
				matchToken(SEMICOLON);
				break;
			}
			else if ( m_lookahead != SEMICOLON && tk_close_brace == CLOSE_BRACE )
			{
				CAipi_Error err;
				tstring sTK = tkz.v_lastToken();
				CString  strTK = _T("( "); 
				strTK += sTK.data();
				strTK += _T(" )");
				err.displayGUIError(DO_WHILE_END, SINTAX_ERROR, _T(" Symbol " + strTK + " doesn't match. Expected symbol ( ; ) was not found.") );	
			}
			statement();
			break;
		case C_DO:
			matchToken(C_DO);
			statement();
			
			//matchToken(C_WHILE);
			//matchToken(OPEN_PARENTHESIS);
			//expression();
			//matchToken(CLOSE_PARENTHESIS);
			
			break;
		case C_FOR:
			matchToken(C_FOR);
			matchToken(OPEN_PARENTHESIS);
			//This for C98 
	
			if(		m_lookahead == C_VOID 
				||	m_lookahead == C_CHAR
				||	m_lookahead == C_SHORT
				||	m_lookahead == C_INT
				||	m_lookahead == C_LONG
				||	m_lookahead == C_FLOAT
				||	m_lookahead == C_DOUBLE
				||	m_lookahead == C_SIGNED
				||	m_lookahead == C_UNSIGNED

				||	m_lookahead == C_STRUCT
				||	m_lookahead == C_UNION
				||	m_lookahead == C_ENUM
			/*	
				||	m_lookahead == C_TYPEDEF 
				||	m_lookahead == C_EXTERN
				||	m_lookahead == C_STATIC
				||	m_lookahead == C_AUTO
				||	m_lookahead == C_REGISTER
				||	m_lookahead == C_CONST
				||	m_lookahead == C_VOLATILE
		*/
			   )
			{
				declaration();
				expression_statement();
				expression();
		
			}
			else
			{
				expression_statement();
				expression_statement();
				expression();
			}
	
	
			//This is for C95
			
				//expression_statement();
				//expression_statement();
				//expression();
			
			matchToken(CLOSE_PARENTHESIS);
			statement();
			break;

	}
	
	/*
	str.Format(_T("SALE ITERATION STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::selection_statement()
{
	/*
	CString str;
	str.Format(_T("SELECTION  STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	if( m_lookahead == C_IF )
	{
		matchToken(C_IF);
		matchToken(OPEN_PARENTHESIS);
		expression();
		matchToken(CLOSE_PARENTHESIS);
		statement();
		if( m_lookahead == C_ELSE)
		{
			matchToken(C_ELSE);
			statement();
		}

	}
	if( m_lookahead == C_SWITCH )
	{
		matchToken(C_SWITCH);
		matchToken(OPEN_PARENTHESIS);
		expression();
		matchToken(CLOSE_PARENTHESIS);
		statement();
	}

	/*
	str.Format(_T("SALE SELECTION  STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}


void CAipi_CParser::expression_statement()
{
	/*
	CString str;
	str.Format(_T("EXPRESSION  STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	if( m_lookahead == SEMICOLON) 
	{
		matchToken(SEMICOLON);
		return;
	}
	
	expression();
	matchToken(SEMICOLON);

	/*
	str.Format(_T("SALE EXPRESSION  STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::block_item()
{
	/*
	CString str;
	str.Format(_T("COMPOUND STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if(			m_lookahead == C_VOID 
			||	m_lookahead == C_CHAR
			||	m_lookahead == C_SHORT
			||	m_lookahead == C_INT
			||	m_lookahead == C_LONG
			||	m_lookahead == C_FLOAT
			||	m_lookahead == C_DOUBLE
			||	m_lookahead == C_SIGNED
			||	m_lookahead == C_UNSIGNED

			||	m_lookahead == C_STRUCT
			||	m_lookahead == C_UNION
			||	m_lookahead == C_ENUM
			
			
			||	m_lookahead == C_TYPEDEF 
			||	m_lookahead == C_EXTERN
			||	m_lookahead == C_STATIC
			||	m_lookahead == C_AUTO
			||	m_lookahead == C_REGISTER
			
			||	m_lookahead == C_CONST
			||	m_lookahead == C_VOLATILE 
	  )
	{
		declaration();
	}
	
	if(	 		m_lookahead == IDENTIFIER
			
			||  m_lookahead == C_CASE
			||	m_lookahead == C_DEFAULT
			||	m_lookahead == OPEN_BRACE
			||	m_lookahead == C_IF
			||	m_lookahead == C_SWITCH
			||	m_lookahead == C_WHILE
			||	m_lookahead == C_DO
			||	m_lookahead == C_FOR
			||	m_lookahead == C_GOTO
			||	m_lookahead == C_CONTINUE
			||	m_lookahead == C_BREAK
			||	m_lookahead == C_RETURN
			||	m_lookahead == INC_OP
			||	m_lookahead == DEC_OP
		)
	{
		
		statement();
	}

	/*
	str.Format(_T("SALE BLOCK ITEM...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}

void CAipi_CParser::block_item_list()
{
	/*
	CString str;
	str.Format(_T("BLOCK ITEM LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	
	if(			m_lookahead == IDENTIFIER
			||  m_lookahead == C_CASE
			||	m_lookahead == C_DEFAULT
			||	m_lookahead == OPEN_BRACE
			||	m_lookahead == C_IF
			||	m_lookahead == C_SWITCH
			||	m_lookahead == C_WHILE
			||	m_lookahead == C_DO
			||	m_lookahead == C_FOR
			||	m_lookahead == C_GOTO
			||	m_lookahead == C_CONTINUE
			||	m_lookahead == C_BREAK
			||	m_lookahead == C_RETURN
			||	m_lookahead == INC_OP
			||	m_lookahead == DEC_OP

			||	m_lookahead == C_VOID 
			||	m_lookahead == C_CHAR
			||	m_lookahead == C_SHORT
			||	m_lookahead == C_INT
			||	m_lookahead == C_LONG
			||	m_lookahead == C_FLOAT
			||	m_lookahead == C_DOUBLE
			||	m_lookahead == C_SIGNED
			||	m_lookahead == C_UNSIGNED

			||	m_lookahead == C_STRUCT
			||	m_lookahead == C_UNION
			||	m_lookahead == C_ENUM
			
			||	m_lookahead == C_TYPEDEF 
			||	m_lookahead == C_EXTERN
			||	m_lookahead == C_STATIC
			||	m_lookahead == C_AUTO
			||	m_lookahead == C_REGISTER
			
			||	m_lookahead == C_CONST
			||	m_lookahead == C_VOLATILE
			
	  )
	{
		block_item();
		block_item_list();
	}

	/*
	str.Format(_T("SALE BLOCK ITEM LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}


void CAipi_CParser::compound_statement()
{
	/*
	CString str;
	str.Format(_T("COMPOUND STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	matchToken(OPEN_BRACE);
		
		/*
		//version C89
	  	
		if(		m_lookahead == IDENTIFIER
			||  m_lookahead == C_CASE
			||	m_lookahead == C_DEFAULT
			||	m_lookahead == OPEN_BRACE
			||	m_lookahead == C_IF
			||	m_lookahead == C_SWITCH
			||	m_lookahead == C_WHILE
			||	m_lookahead == C_DO
			||	m_lookahead == C_FOR
			||	m_lookahead == C_GOTO
			||	m_lookahead == C_CONTINUE
			||	m_lookahead == C_BREAK
			||	m_lookahead == C_RETURN
			||	m_lookahead == INC_OP
			||	m_lookahead == DEC_OP
		  )
		{
			statement_list();
		}
		if(		m_lookahead == C_VOID 
			||	m_lookahead == C_CHAR
			||	m_lookahead == C_SHORT
			||	m_lookahead == C_INT
			||	m_lookahead == C_LONG
			||	m_lookahead == C_FLOAT
			||	m_lookahead == C_DOUBLE
			||	m_lookahead == C_SIGNED
			||	m_lookahead == C_UNSIGNED
			||	m_lookahead == C_TYPEDEF 
			||	m_lookahead == C_EXTERN
			||	m_lookahead == C_STATIC
			||	m_lookahead == C_AUTO
			||	m_lookahead == C_REGISTER
			||	m_lookahead == C_CONST
			||	m_lookahead == C_VOLATILE
		  )
		{
			declaration_list();
		}
		*/
		
		//version C98
	block_item_list();
	matchToken(CLOSE_BRACE);
	
	/*
	str.Format(_T("SALE COMPOUND STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}



void CAipi_CParser::labeled_statement()
{
	/*
	CString str;
	str.Format(_T("LABELED STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	switch(m_lookahead)
	{
		case IDENTIFIER:
			matchToken(IDENTIFIER);
			if( m_lookahead == COLON )
			{
				matchToken(COLON);
			}
			else
			{
				putbackToken(1);
				expression_statement();
				return;
			}
			statement();
			break;
		case C_CASE:
			matchToken(C_CASE);
			constant_expression();
			matchToken(COLON);
			statement();
			break;
		case C_DEFAULT:
			matchToken(C_DEFAULT);
			matchToken(COLON);
			statement();
			break;
	}

	/*
	str.Format(_T("SALE LABELED STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}






void CAipi_CParser::statement()
{
	/*
	CString str;
	str.Format(_T("STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if(		m_lookahead == IDENTIFIER
		||	m_lookahead == C_CASE
		||	m_lookahead == C_DEFAULT
	  )
	{
		labeled_statement();
	}
	
	if( m_lookahead == OPEN_BRACE )
	{
		compound_statement();
	}
	
	
	if( m_lookahead == C_IF || m_lookahead == C_SWITCH )
	{
		selection_statement();
	}
	
	if(		m_lookahead == C_WHILE 
		||	m_lookahead == C_DO
		||	m_lookahead == C_FOR
	  )
	{
		iteration_statement();
	}
	
	if(		m_lookahead == C_GOTO 
		||	m_lookahead == C_CONTINUE
		||	m_lookahead == C_BREAK
		||	m_lookahead == C_RETURN
	  )
	{
		jump_statement();
	}

		
	if(		
			m_lookahead == SEMICOLON
		
		||	m_lookahead == AMPERSAND 
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_PARENTHESIS	
		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PTR_OP
			
	  )
	{     
		expression_statement();
	}

	/*
	str.Format(_T("SALE STATEMENT...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}




void CAipi_CParser::statement_list()
{
	/*
	CString str;
	str.Format(_T("STATEMENT LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if(		m_lookahead == IDENTIFIER
		||	m_lookahead == C_CASE
		||	m_lookahead == C_DEFAULT
		||	m_lookahead == OPEN_BRACE
		||	m_lookahead	== C_IF
		||	m_lookahead == C_SWITCH
		||	m_lookahead == C_WHILE
		||	m_lookahead == C_DO
		||	m_lookahead == C_FOR
		||	m_lookahead == C_GOTO 
		||	m_lookahead == C_CONTINUE
		||	m_lookahead == C_BREAK
		||	m_lookahead == C_RETURN
		
		||	m_lookahead == SEMICOLON
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
	  )
	{
		statement();	
		statement_list();
	}

	/*
	str.Format(_T("SALE STATEMENT LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}




void CAipi_CParser::designator()
{
	/*
	CString str;
	str.Format(_T("DESIGNATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	if( m_lookahead == OPEN_BRACKET )
	{
		matchToken(OPEN_BRACKET);
		constant_expression();
		matchToken(CLOSE_BRACKET);
	}
	
	if( m_lookahead == PERIOD)
	{
		matchToken(PERIOD);
		matchToken(IDENTIFIER);
	
	}

	/*
	str.Format(_T("SALIR DESIGNATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	

}



void CAipi_CParser::designator_list()
{
	/*
	CString str;
	str.Format(_T("DESIGNATOR  LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	if( m_lookahead == OPEN_BRACKET || m_lookahead == PERIOD)
	{
		designator();
		designator_list();
	}

	/*
	str.Format(_T("SALIR DESIGNATOR  LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}




void CAipi_CParser::designation()
{
	/*
	CString str;
	str.Format(_T("DESIGNATION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	designator_list();
	matchToken(AS);
	
/*
	str.Format(_T("SALIR DESIGNATION...%d  " ), m_lookahead);
	AfxMessageBox(str);
*/	
}



void CAipi_CParser::initializer_list()
{
	/*
	CString str;
	str.Format(_T("INITIALIZER LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	//designation() is valid for C99
	if( m_lookahead == OPEN_BRACKET || m_lookahead == PERIOD)
	{
		designation();
	}
	
	initializer();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			if( m_lookahead == OPEN_BRACKET || m_lookahead == PERIOD)
			{
				designation();
			}
			initializer();
			
		}
	}
/*
	str.Format(_T("SALE INITIALIZER LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
*/
}



void CAipi_CParser::initializer()
{
	/*
	CString str;
	str.Format(_T("INITIALIZER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	assigment_expression();
	
	if( m_lookahead == OPEN_BRACE )
	{
		matchToken(OPEN_BRACE);
		initializer_list();
		if( m_lookahead == COMMA)
		{
			matchToken(COMMA);
		}
		matchToken(CLOSE_BRACE);

	}
	/*
	str.Format(_T("SALE INITIALIZER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/


}


void CAipi_CParser::direct_abstract_declarator()
{
	/*
	CString str;
	str.Format(_T("DIRECT ABSTRACT DECLARATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if(m_lookahead == OPEN_BRACKET )
	{
		while(m_lookahead == OPEN_BRACKET)
		{
			matchToken(OPEN_BRACKET);
			if( m_lookahead == ASTERIC )
			{
				matchToken(ASTERIC);
				matchToken(CLOSE_BRACKET);
				break;
			}
			assigment_expression();
			matchToken(CLOSE_BRACKET);
		}
	
	
	}
	
	if( m_lookahead == OPEN_PARENTHESIS)
	{
		while( m_lookahead == OPEN_PARENTHESIS)
		{
			matchToken(OPEN_PARENTHESIS);
			parameter_type_list();
			matchToken(CLOSE_PARENTHESIS);
		}
	}
/*
	str.Format(_T("SALE DIRECT ABSTRACT DECLARATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
*/
}


void CAipi_CParser::abstract_declarator()
{
	/*
	CString str;
	str.Format(_T("ABSTRACT DECLARATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	if( m_lookahead == ASTERIC )
	{
		pointer();
	}
	if( m_lookahead == OPEN_BRACKET || m_lookahead == OPEN_PARENTHESIS )
	{
		direct_abstract_declarator();
	}
	/*
	str.Format(_T("SALE ABSTRACT DECLARATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}


void CAipi_CParser::type_name()
{
	/*
	CString str;
	str.Format(_T("TYPE_NAME...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	specifier_qualifier_list();
	abstract_declarator();

	/*
	str.Format(_T("SALE TYPE_NAME...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/


}


void CAipi_CParser::identifier_list()
{
	/*
	CString str;
	str.Format(_T("IDENTIFIER LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if( m_lookahead == IDENTIFIER )
	{
		matchToken(IDENTIFIER);

		if( m_lookahead == COMMA)
		{
			matchToken(COMMA);
			matchToken(IDENTIFIER);
		}
	}

	/*
	str.Format(_T("SALE IDENTIFIER LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}


void CAipi_CParser::parameter_declaration()
{
	/*
	CString str;
	str.Format(_T("PARAMETER DECLARATION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	declaration_specifiers();

	if( m_lookahead == ASTERIC )
	{
		matchToken(ASTERIC );
		if( m_lookahead == IDENTIFIER || m_lookahead == OPEN_PARENTHESIS || m_lookahead == OPEN_BRACKET )
		{
			putbackToken(2);
			declarator();
			return;
		}
		else
		{
			putbackToken(2);
			abstract_declarator();
			return;
		}
	}

	if( m_lookahead == IDENTIFIER || m_lookahead == OPEN_PARENTHESIS || m_lookahead == OPEN_BRACKET)
	{
		declarator();
	}
	if( m_lookahead == OPEN_PARENTHESIS || m_lookahead == OPEN_BRACKET)
	{
		abstract_declarator();
	}

	/*
	str.Format(_T("SALE PARAMETER DECLARATION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::parameter_list()
{
	/*
	CString str;
	str.Format(_T("PARAMETER LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	parameter_declaration();

	if( m_lookahead == COMMA)
	{
		while(m_lookahead == COMMA)
		{
			matchToken(COMMA);
			parameter_declaration(); 
		}
	}

	/*
	str.Format(_T("SALE PARAMETER LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}



void CAipi_CParser::parameter_type_list()
{
	/*
	CString str;
	str.Format(_T("PARAMETER TYPE LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	parameter_list();
	if( m_lookahead == COMMA)
	{
		matchToken(COMMA);
		matchToken(ELLIPSIS);
	}
	
	/*
	str.Format(_T("SALE PARAMETER TYPE LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::type_qualifier_list()
{
	/*
	CString str;
	str.Format(_T("TYPE QUALIFIER LIST ...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	if( m_lookahead == C_CONST || m_lookahead == C_VOLATILE)
	{
		type_qualifier();
		type_qualifier_list();
	}
	/*
	str.Format(_T("SALE TYPE QUALIFIER LIST ...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}


void CAipi_CParser::pointer()
{
	/*
	CString str;
	str.Format(_T("POINTER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	if( m_lookahead == ASTERIC)
	{
		matchToken(ASTERIC);
		type_qualifier_list();
		pointer();
	}

	/*
	str.Format(_T("SALE POINTER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::direct_declarator()
{
	/*
	CString str;
	str.Format(_T("DIRECT_DECLARATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
		
	if( m_lookahead == IDENTIFIER )
	{
		matchToken(IDENTIFIER);
		
	}

	else if( m_lookahead == OPEN_PARENTHESIS )
	{
		while( m_lookahead == OPEN_PARENTHESIS)
		{
			matchToken(OPEN_PARENTHESIS);

			if(		m_lookahead == ASTERIC 
				||	m_lookahead == IDENTIFIER 
				||	m_lookahead == OPEN_PARENTHESIS 
				||	m_lookahead == OPEN_BRACKET
			  )
			{
				declarator();
			}
			if(		m_lookahead == C_TYPEDEF 
				||	m_lookahead == C_EXTERN
				||	m_lookahead == C_STATIC
				||	m_lookahead == C_AUTO
				||	m_lookahead == C_REGISTER
				||	m_lookahead == C_VOID 
				
				||	m_lookahead == C_CHAR
				||	m_lookahead == C_SHORT
				||	m_lookahead == C_INT
				||	m_lookahead == C_LONG
				||	m_lookahead == C_FLOAT
				||	m_lookahead == C_DOUBLE
				||	m_lookahead == C_SIGNED
				||	m_lookahead == C_UNSIGNED
		
				||  m_lookahead == C_STRUCT
				||	m_lookahead == C_UNION
				||	m_lookahead == C_ENUM
				|| m_lookahead == C_CONST 
				|| m_lookahead == C_VOLATILE 
			 )
			{
				parameter_type_list();
			}
			
			if( m_lookahead == IDENTIFIER )
			{
				identifier_list();
			}
			matchToken(CLOSE_PARENTHESIS);
		}
	}

	//C98 version
	else if( m_lookahead == OPEN_BRACKET )
	{
		while( m_lookahead == OPEN_BRACKET )
		{
			matchToken(OPEN_BRACKET);
			if( m_lookahead == ASTERIC )
			{
				matchToken(ASTERIC);
				matchToken(CLOSE_BRACKET);
				break;
			}
			if( m_lookahead == C_STATIC )
			{
				matchToken(C_STATIC);
				type_qualifier_list();
				assigment_expression();
				matchToken(CLOSE_BRACKET);
				break;
			}
			if( m_lookahead == C_CONST || m_lookahead == C_VOLATILE )
			{
				type_qualifier_list();
				if( m_lookahead == C_STATIC )
				{
					matchToken(C_STATIC);
					assigment_expression();
					matchToken(CLOSE_BRACKET);
					break;
				}
				else if( m_lookahead == ASTERIC )
				{
					matchToken(ASTERIC);
					matchToken(CLOSE_BRACKET);
					break;
				}
			}
			
			assigment_expression();
			matchToken(CLOSE_BRACKET);
		}
	}

	
	
	
	if( m_lookahead == -1 )
	{
		CAipi_Tokenizer tkz;
		tstring sTK = tkz.v_lastToken();
		
		CString  strTK = _T("( "); 
		strTK += sTK.data();
		strTK += _T(" )");
		//AfxMessageBox(tk.data());

		CAipi_Error err;
		err.displayGUIError(DIRECT_DECLARATOR, SINTAX_ERROR, _T(" Symbol " + strTK + " doesn't match. Expected symbols ( [ ) or ( ( ) or identifier were not found.") );
		m_jumpExit = true;
	}

	if( m_lookahead > 399 && m_lookahead < 470 )
	{
			CAipi_Symbol sym;
			tstring sKW = sym.findIdKeyWord(m_lookahead);
			if( sKW != _T("NOT_FOUND"))
			{
				CString strSymbol = _T("( ");
				strSymbol += sKW.data();
				strSymbol += _T(" )");
				CAipi_Error err;
				err.displayGUIError(SEMANT, SEMANT_ERROR, _T(" Symbol " + strSymbol + " is a keyword of AIPI sintax. Keywords are not allowed in enumerations elements.") );
				
			}
			
	}	

/*
	//C95 version
	if( m_lookahead == OPEN_BRACKET )
	{
		while( m_lookahead == OPEN_BRACKET )
		{
			matchToken(OPEN_BRACKET);
			constant_expression();
			matchToken(CLOSE_BRACKET);
		}
	}
*/	

	/*
	str.Format(_T("SALE DIRECT_DECLARATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}






void CAipi_CParser::declarator()
{
	/*
	CString str;
	str.Format(_T("DECLARATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if( m_lookahead == ASTERIC )
	{
		pointer();
		direct_declarator();
	}
	
	direct_declarator();
	
	/*
	str.Format(_T("SALE DECLARATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::type_qualifier()
{
	/*
	CString str;
	str.Format(_T("TYPE_QUALIFIER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	if( m_lookahead == C_CONST || m_lookahead == C_VOLATILE )
	{
		matchToken(m_lookahead);
	}
	/*
	str.Format(_T("SALE TYPE_QUALIFIER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::enumerator()
{
	/*
	CString str;
	str.Format(_T("ENUMERATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if( m_lookahead > 399 && m_lookahead < 470 )
	{
			CAipi_Symbol sym;
			tstring sKW = sym.findIdKeyWord(m_lookahead);
			if( sKW != _T("NOT_FOUND"))
			{
				CString strSymbol = _T("( ");
				strSymbol += sKW.data();
				strSymbol += _T(" )");
				CAipi_Error err;
				err.displayGUIError(SEMANT, SEMANT_ERROR, _T(" Symbol " + strSymbol + " is a keyword of AIPI sintax. Keywords are not allowed in enumerations elements.") );
				
			}
			
	}
	
	//if( m_lookahead == IDENTIFIER )
	//{
		matchToken(IDENTIFIER);
		if( m_lookahead == AS )
		{
			matchToken(AS);
			constant_expression();
		}

	//}


	/*
	str.Format(_T("SALE ENUMERATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::enumerator_list()
{
	/*
	CString str;
	str.Format(_T("ENUMERATOR LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	enumerator();
	if( m_lookahead == COMMA)
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			enumerator_list();
		}
	}

	/*
	str.Format(_T("SALE ENUMERATOR LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}


void CAipi_CParser::enum_specifier()
{
	/*
	CString str;
	str.Format(_T("ENUM SPECIFIER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	if( m_lookahead == C_ENUM )
	{
		matchToken(C_ENUM);
		if( m_lookahead == IDENTIFIER )
		{
			matchToken(IDENTIFIER);
		}

		if( m_lookahead == OPEN_BRACE )
		{
			matchToken(OPEN_BRACE);
			enumerator_list();
			/*
			if( m_lookahead == COMMA )
			{
				matchToken(COMMMA);
			}
			*/
			matchToken(CLOSE_BRACE);
		}
	}

	/*
	str.Format(_T("SALE ENUM SPECIFIER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::struct_declarator()
{
	/*
	CString str;
	str.Format(_T("STRUCT DECLARATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	if(		m_lookahead == ASTERIC 
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == OPEN_BRACKET 
		||	m_lookahead == OPEN_PARENTHESIS
	  )
	{
		declarator();
		if( m_lookahead == COLON )
		{
			matchToken(COLON);
			constant_expression();
		}
	}

	

}



void CAipi_CParser::struct_declarator_list()
{
	/*
	CString str;
	str.Format(_T("STRUCT DECLARATOR LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	struct_declarator();
	
	if( m_lookahead == COMMA)
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			struct_declarator();
		}
	}

	/*
	str.Format(_T("SALE STRUCT DECLARATOR LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}


void CAipi_CParser::specifier_qualifier_list()
{
	/*
	CString str;
	str.Format(_T("SPECIFIER_QUALIFIER_LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if(		m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED

		||	m_lookahead == C_STRUCT
		||	m_lookahead == C_UNION
		||	m_lookahead == C_ENUM
		
			
	   )
	   {
			type_specifier();
			specifier_qualifier_list();
	   }

	if( m_lookahead == C_CONST || m_lookahead == C_VOLATILE )
	{
		type_qualifier();
		specifier_qualifier_list();
	}

	/*
	str.Format(_T("SALE SPECIFIER_QUALIFIER_LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::struct_declaration()
{
	/*	
	CString str;
	str.Format(_T("STRUCT DECLARATION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	specifier_qualifier_list();
	struct_declarator_list();
	matchToken(SEMICOLON);

	/*
	str.Format(_T("SALE STRUCT DECLARATION LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}


void CAipi_CParser::struct_declaration_list()
{
	/*
	CString str;
	str.Format(_T("STRUCT DECLARATION LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	if(		m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED

		||	m_lookahead == C_STRUCT
		||	m_lookahead == C_UNION
		||	m_lookahead == C_ENUM
					
	)
	{
		struct_declaration();
		struct_declaration_list();
	}

	/*
	str.Format(_T("SALE STRUCT DECLARATION LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::struct_or_union()
{
	/*
	CString str;
	str.Format(_T("STRUCT OR UNION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	if( m_lookahead == C_STRUCT )
	{
		matchToken(C_STRUCT);
	}

	if( m_lookahead == C_UNION )
	{
		matchToken(C_UNION);
	}

	/*
	str.Format(_T("SALE STRUCT OR UNION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::struct_or_union_specifier()
{
	/*
	CString str;
	str.Format(_T("STRUCT OR UNION SPECIFIER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
			
		if( m_lookahead == C_STRUCT )
		{
			matchToken(C_STRUCT);
		}

		if( m_lookahead == C_UNION )
		{
			matchToken(C_UNION);
		}
		
		//struct_or_union();

		if( m_lookahead == IDENTIFIER )
		{
			matchToken(IDENTIFIER);
		}
		
		if ( m_lookahead == OPEN_BRACE )
		{
			matchToken(OPEN_BRACE);
			struct_declaration_list();
			matchToken(CLOSE_BRACE);
		}
		
		
	/*
	str.Format(_T("SALE STRUCT OR UNION SPECIFIER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/	
}



void CAipi_CParser::type_specifier()
{	
	/*
	CString str;
	str.Format(_T("TYPE_SPECIFIER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	m_currentId_Type = m_lookahead;

	if(		m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED

	   )
	{
		matchToken(m_lookahead);
	}
		
	if (  m_lookahead == C_STRUCT || m_lookahead == C_UNION )
	{	
		struct_or_union_specifier();
	}
	if( m_lookahead == C_ENUM )
	{
		enum_specifier();
	}
	
	if( m_lookahead == IDENTIFIER )
	{
		matchToken(checkType());
	}
	/*	 
	str.Format(_T("SALE TYPE_SPECIFIER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::storage_class_specifier()
{
	/*
	CString str;
	str.Format(_T("STORAGE CLASS SPECIFIER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if(		m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		
	   )
	{
		matchToken(m_lookahead);
	}

	/*
	str.Format(_T("SALE STORAGE CLASS SPECIFIER...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}


void CAipi_CParser::init_declarator()
{
	/*
	CString str;
	str.Format(_T("INIT_DECLARATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	declarator();
	
	if( m_lookahead == AS )
	{
		matchToken(AS);
		initializer();
	}

	/*
	str.Format(_T("SALE INIT_DECLARATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}



void CAipi_CParser::init_declarator_list()
{
	/*
	CString str;
	str.Format(_T("INIT_DECLARATION_LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	init_declarator();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			init_declarator();
		}
	}

	/*
	str.Format(_T("SALE INIT_DECLARATION_LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}


void CAipi_CParser::declaration_specifiers()
{
	/*
	CString str;
	str.Format(_T("DECLARATION_SPECIFIERS...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	if(		m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		
	   )
	{
		matchToken(m_lookahead);
		//storage_class_specifier();
		declaration_specifiers();
	}
	
	if(		m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		
		||  m_lookahead == C_STRUCT
		||	m_lookahead == C_UNION
		||	m_lookahead == C_ENUM
      )
	{
		type_specifier();
		declaration_specifiers();
		
	}
	
	if( m_lookahead == C_CONST || m_lookahead == C_VOLATILE )
	{
		type_qualifier();
		declaration_specifiers();
	}

	/*
	str.Format(_T("SALE DECLARATION_SPECIFIERS...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}


void CAipi_CParser::declaration()
{
	/*
	CString str;
	str.Format(_T("DECLARATION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	declaration_specifiers();
	if( m_lookahead == SEMICOLON)
	{
		matchToken(SEMICOLON);
		return;
	}
	else
	{
		init_declarator_list();
		matchToken(SEMICOLON);
	}
	
	/*
	str.Format(_T("SALE DECLARATION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::constant_expression()
{
	/*
	CString str;
	str.Format(_T("CONSTANT_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	conditional_expression();

	/*
	str.Format(_T("SALE CONSTANT_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}



void CAipi_CParser::expression()
{
	/*
	CString str;
	str.Format(_T("EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	assigment_expression();
	
	while ( m_lookahead == COMMA )
	{
		matchToken( COMMA );
		assigment_expression();
	}

	/*
	str.Format(_T("SALE EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::assigment_operator()
{
	/*
	CString str;
	str.Format(_T("ASSIGMENT_OP...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if(		m_lookahead == AS	
		||	m_lookahead == MUL_ASSIGN 
		||	m_lookahead == DIV_ASSIGN
		||	m_lookahead == MOD_ASSIGN
		||	m_lookahead == ADD_ASSIGN
		||	m_lookahead == SUB_ASSIGN
		||	m_lookahead == LEFT_ASSIGN
		||	m_lookahead == RIGHT_ASSIGN
		||	m_lookahead == ADD_ASSIGN
		||	m_lookahead == XOR_ASSIGN
		||	m_lookahead == OR_ASSIGN
		
	  )
	{
		matchToken(m_lookahead);
	}
	
	/*
	str.Format(_T("SALE ASSIGMENT_OP...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
		
}



void CAipi_CParser::assigment_expression()
{
	/*
	CString str;
	str.Format(_T("ASSIGMENT_EXP...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/	
	
	if(		m_lookahead == AMPERSAND 
		||	m_lookahead == ASTERIC
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_PARENTHESIS 
		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PTR_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
		
	  )
	{
		unary_expression();
		assigment_operator();
		assigment_expression();
	}

	conditional_expression();
		
	
	/*
	str.Format(_T("SALE ASSIGMENT_EXP...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/	
}



void CAipi_CParser::conditional_expression()
{
	/*
	CString str;
	str.Format(_T("CONDITIONAL_EXP...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	/*	
	if(		m_lookahead == AND_OP
	
		||	m_lookahead == VERTICAL_BAR

		||	m_lookahead == CARET

		||	m_lookahead == ET
		||	m_lookahead == NE
		
		||	m_lookahead == LEFT_OP 
		||	m_lookahead == RIGHT_OP 
		||	m_lookahead == PLUS_SIGN 
		||	m_lookahead == MINUS_SIGN

		||  m_lookahead == ASTERIC 
		||	m_lookahead == SLASH 
		||	m_lookahead == PERCENT

		||	m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE
		||	m_lookahead == OPEN_PARENTHESIS	
		
		||	m_lookahead == AMPERSAND 
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PRT_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
	  )
	{ */
		logical_or_expression();
	
		if ( m_lookahead == QUESTION )
		{
			matchToken( QUESTION);
			expression();
			matchToken(COLON);
			conditional_expression();
		}
	//}
	
/*
	str.Format(_T("SALE CONDITIONAL_EXP...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::logical_or_expression()
{
	/*
	CString str;
	str.Format(_T("LOGICAL_OR_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	/*	
	if(		m_lookahead == AND_OP
	
		||	m_lookahead == VERTICAL_BAR

		||	m_lookahead == CARET

		||	m_lookahead == ET
		||	m_lookahead == NE
		
		||	m_lookahead == LEFT_OP 
		||	m_lookahead == RIGHT_OP 
		||	m_lookahead == PLUS_SIGN 
		||	m_lookahead == MINUS_SIGN

		||  m_lookahead == ASTERIC 
		||	m_lookahead == SLASH 
		||	m_lookahead == PERCENT

		||	m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE
		||	m_lookahead == OPEN_PARENTHESIS	
		
		||	m_lookahead == AMPERSAND 
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PRT_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
	  )
	{ */
	
		logical_and_expression();
	//}
	
	if( m_lookahead == OR_OP )
	{
		while ( m_lookahead == OR_OP )
		{
			matchToken( m_lookahead);
			logical_and_expression();
		}
	}

	/*
	str.Format(_T("SALE LOGICAL_OR_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}



void CAipi_CParser::logical_and_expression()
{
	/*
	CString str;
	str.Format(_T("LOGICAL_AND_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	/*	
	if(		m_lookahead == VERTICAL_BAR

		||	m_lookahead == CARET

		||	m_lookahead == ET
		||	m_lookahead == NE
		
		||	m_lookahead == LEFT_OP 
		||	m_lookahead == RIGHT_OP 
		||	m_lookahead == PLUS_SIGN 
		||	m_lookahead == MINUS_SIGN

		||  m_lookahead == ASTERIC 
		||	m_lookahead == SLASH 
		||	m_lookahead == PERCENT

		||	m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE
		||	m_lookahead == OPEN_PARENTHESIS	
		
		||	m_lookahead == AMPERSAND 
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PRT_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
	  )
	{ */
		inclusive_or_expression();
	//}
	
	if( m_lookahead == AND_OP )
	{
		while ( m_lookahead == AND_OP )
		{
			matchToken( m_lookahead);
			inclusive_or_expression();
		}
	}

	/*
	str.Format(_T("SALE LOGICAL_AND_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}




void CAipi_CParser::inclusive_or_expression()
{
	/*
	CString str;
	str.Format(_T("INCLUSIVE_OR_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

/*	
	if(		m_lookahead == CARET

		||	m_lookahead == ET
		||	m_lookahead == NE
		
		||	m_lookahead == LEFT_OP 
		||	m_lookahead == RIGHT_OP 
		||	m_lookahead == PLUS_SIGN 
		||	m_lookahead == MINUS_SIGN

		||  m_lookahead == ASTERIC 
		||	m_lookahead == SLASH 
		||	m_lookahead == PERCENT

		||	m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE
		||	m_lookahead == OPEN_PARENTHESIS	
		
		||	m_lookahead == AMPERSAND 
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PRT_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
	  )
	{ */
		exclusive_or_expression();
	//}
	
	if( m_lookahead == VERTICAL_BAR )
	{
		while ( m_lookahead == VERTICAL_BAR )
		{
			matchToken( m_lookahead);
			exclusive_or_expression();
		}
	}

	/*
	str.Format(_T("SALE INCLUSIVE_OR_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}




void CAipi_CParser::exclusive_or_expression()
{
	/*
	CString str;
	str.Format(_T("EXCLUSIVE_OR_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
/*	
	if(	
			m_lookahead == ET
		||	m_lookahead == NE

		||	m_lookahead == LT
		||	m_lookahead == LE
		||	m_lookahead == GT
		||	m_lookahead == GE
		
		
		||	m_lookahead == LEFT_OP 
		||	m_lookahead == RIGHT_OP 
		||	m_lookahead == PLUS_SIGN 
		||	m_lookahead == MINUS_SIGN

		||  m_lookahead == ASTERIC 
		||	m_lookahead == SLASH 
		||	m_lookahead == PERCENT

		||	m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE
		||	m_lookahead == OPEN_PARENTHESIS	
		
		||	m_lookahead == AMPERSAND 
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PRT_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
	  )
	{ */
		and_expression();
//	}
	
	
	if( m_lookahead == CARET )
	{
		while ( m_lookahead == CARET )
		{
			matchToken( m_lookahead);
			and_expression();
		}
	}

	/*
	str.Format(_T("SALE EXCLUSIVE_OR_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}






void CAipi_CParser::and_expression()
{
	/*
	CString str;
	str.Format(_T("AND_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	/*
	if(		m_lookahead == ET
		||	m_lookahead == NE

		||	m_lookahead == LT
		||	m_lookahead == LE
		||	m_lookahead == GT
		||	m_lookahead == GE
		
		
		||	m_lookahead == LEFT_OP 
		||	m_lookahead == RIGHT_OP 
		||	m_lookahead == PLUS_SIGN 
		||	m_lookahead == MINUS_SIGN

		||  m_lookahead == ASTERIC 
		||	m_lookahead == SLASH 
		||	m_lookahead == PERCENT

		||	m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE
		||	m_lookahead == OPEN_PARENTHESIS	
		
		||	m_lookahead == AMPERSAND 
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PRT_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
	  )
	{  */
		equality_expression();
//	}
	
	
	
	
	if( m_lookahead == AMPERSAND )
	{
		while ( m_lookahead == AMPERSAND )
		{
			matchToken( m_lookahead );
			equality_expression();
		}
	}

	/*
	str.Format(_T("SALE AND_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}


void CAipi_CParser::equality_expression()
{
	/*
	CString str;
	str.Format(_T("EQUALITY_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
/*
	if(		m_lookahead == LT
		||	m_lookahead == LE
		||	m_lookahead == GT
		||	m_lookahead == GE
		
		||	m_lookahead == LEFT_OP 
		||	m_lookahead == RIGHT_OP 
		||	m_lookahead == PLUS_SIGN 
		||	m_lookahead == MINUS_SIGN

		||  m_lookahead == ASTERIC 
		||	m_lookahead == SLASH 
		||	m_lookahead == PERCENT

		||	m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE
		||	m_lookahead == OPEN_PARENTHESIS	
		
		||	m_lookahead == AMPERSAND 
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PRT_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
	  )
	{
	*/
		relational_expression();
	//}
	
	if( m_lookahead == ET || m_lookahead == NE )
	{
		while ( m_lookahead == ET || m_lookahead == NE )
		{
			matchToken( m_lookahead );
			relational_expression();
		}
	}

	/*
	str.Format(_T("SALE EQUALITY_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}





void CAipi_CParser::relational_expression()
{
	/*
	CString str;
	str.Format(_T("RELATION_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
/*		
	if(		m_lookahead == LEFT_OP 
		||	m_lookahead == RIGHT_OP 
		
		||	m_lookahead == PLUS_SIGN 
		||	m_lookahead == MINUS_SIGN

		||  m_lookahead == ASTERIC 
		||	m_lookahead == SLASH 
		||	m_lookahead == PERCENT

		||	m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE
		||	m_lookahead == OPEN_PARENTHESIS	
		
		||	m_lookahead == AMPERSAND 
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PRT_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
	  )
	{	*/
		shift_expression();
//	}
	
	if( m_lookahead == LT || m_lookahead == LE || m_lookahead == GT || m_lookahead == GE )
	{
		while ( m_lookahead == LT || m_lookahead == LE || m_lookahead == GT || m_lookahead == GE  )
		{
			matchToken( m_lookahead);
			shift_expression();
		}
	}

	/*
	str.Format(_T("SALE RELATION_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}



void CAipi_CParser::shift_expression()
{
	/*
	CString str;
	str.Format(_T("SHIFT_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
/*	
	if(		m_lookahead == PLUS_SIGN 
		||	m_lookahead == MINUS_SIGN
		
		||  m_lookahead == ASTERIC 
		||	m_lookahead == SLASH 
		||	m_lookahead == PERCENT

		||	m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE
		||	m_lookahead == OPEN_PARENTHESIS	
		
		||	m_lookahead == AMPERSAND 
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PRT_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
	  )	
	{ */
		additive_expression();
	//}
	
	
	if( m_lookahead == LEFT_OP || m_lookahead == RIGHT_OP )
	{
		while ( m_lookahead == LEFT_OP || m_lookahead == RIGHT_OP )
		{
			matchToken( m_lookahead);
			additive_expression();
		}
	}

	/*
	str.Format(_T("SALE SHIFT_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}




void CAipi_CParser::additive_expression()
{
	/*
	CString str;
	str.Format(_T("ADDITIVE_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
/*	
	if(		m_lookahead == ASTERIC 
		||	m_lookahead == SLASH 
		||	m_lookahead == PERCENT

		||	m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE
		||	m_lookahead == OPEN_PARENTHESIS	
		
		||	m_lookahead == AMPERSAND 
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PRT_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
		
	 )
	  
	{ */
		multiplicative_expression();
	//}
	
	if( m_lookahead == PLUS_SIGN || m_lookahead == MINUS_SIGN )
	{
		while ( m_lookahead == PLUS_SIGN || m_lookahead == MINUS_SIGN )
		{
			matchToken( m_lookahead);
			multiplicative_expression();
		}
	}

	/*
	str.Format(_T("SALE ADDITIVE_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}


void CAipi_CParser::multiplicative_expression()
{
	/*
	CString str;
	str.Format(_T("MULTIPLICATIVE_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

/*	
	if(		m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED
		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE
		||	m_lookahead == OPEN_PARENTHESIS	
		
		||	m_lookahead == AMPERSAND 
		||	m_lookahead == ASTERIC
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PRT_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
		
	  )
	   
	{  */		
		cast_expression();
//	}

	if( m_lookahead == ASTERIC || m_lookahead == SLASH || m_lookahead == PERCENT )
	{
		while ( m_lookahead == ASTERIC || m_lookahead == SLASH || m_lookahead == PERCENT )
		{
			matchToken( m_lookahead);
			cast_expression();
		}
	}

	/*
	str.Format(_T("SALE MULTIPLICATIVE_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

}



void CAipi_CParser::cast_expression()
{
	/*
	CString str;
	str.Format(_T("CAST_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	/*
	if( m_lookahead > 399 && m_lookahead < 470 )
	{
			CAipi_Symbol sym;
			tstring sKW = sym.findIdKeyWord(m_lookahead);
			if( sKW != _T("NOT_FOUND"))
			{
				CString strSymbol = _T("( ");
				strSymbol += sKW.data();
				strSymbol += _T(" )");
				CAipi_Error err;
				err.displayError(SEMANT, SEMANT_ERROR, _T(" Symbol " + strSymbol + " is a keyword of AIPI sintax. Keywords are not allowed in structs elements.") );
				
			}
			
	}*/
	
	/*
	if(		m_lookahead == AMPERSAND 
		||	m_lookahead == ASTERIC
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		||	m_lookahead == C_SIZEOF

		||	m_lookahead == OPEN_PARENTHESIS 
		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PTR_OP
				
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
		
	  )
	{	*/
		unary_expression();
    //}
	
	//str.Format(_T("EXIT UNARY_EXP...%d  " ), m_lookahead);
	//AfxMessageBox(str);
	
	//C grammar
	if(		m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
		||	m_lookahead == C_SIGNED
		||	m_lookahead == C_UNSIGNED

		||	m_lookahead == C_STRUCT
		||	m_lookahead == C_UNION
		||	m_lookahead == C_ENUM

		||	m_lookahead == C_TYPEDEF 
		||	m_lookahead == C_EXTERN
		||	m_lookahead == C_STATIC
		||	m_lookahead == C_AUTO
		||	m_lookahead == C_REGISTER
		||	m_lookahead == C_CONST
		||	m_lookahead == C_VOLATILE
				
	   )
	{
		type_name();
		matchToken(OPEN_PARENTHESIS);
		cast_expression();
		matchToken(CLOSE_PARENTHESIS );
		
	}


	
	//C++ grammar
	if( m_lookahead == OPEN_PARENTHESIS )
	{
		//AfxMessageBox(_T("Entró al CAST OPEN PARENTHESIS"));
		matchToken(OPEN_PARENTHESIS);
		type_name();
		
	
		matchToken(CLOSE_PARENTHESIS );
		cast_expression();
	}
	

	/*
	str.Format(_T("SALE CAST_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
}


void CAipi_CParser::unary_operator()
{
	/*
	CString str;
	str.Format(_T("UNARY_OPERATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	 
	
	if(		m_lookahead == AMPERSAND 
		||	m_lookahead == ASTERIC
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
	  )
	{
		matchToken(m_lookahead);
	}
	
	/*
	str.Format(_T("SALE UNARY_OPERATOR...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}


void CAipi_CParser::unary_expression()
{
	/*
	CString str;
	str.Format(_T("UNARY_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	/*
	if(		m_lookahead == OPEN_PARENTHESIS 
		||	m_lookahead == OPEN_BRACKET
		||	m_lookahead == PERIOD
		||	m_lookahead == PRT_OP
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
		
		||	m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
		||	m_lookahead == OPEN_PARENTHESIS
	 )
	{ */
		postfix_expression();
	//}
	
	
	if( m_lookahead == INC_OP || m_lookahead == DEC_OP )
	{
		matchToken(m_lookahead);
		unary_expression();
	}
	if(		m_lookahead == AMPERSAND 
		||	m_lookahead == ASTERIC
		||	m_lookahead == PLUS_SIGN
		||	m_lookahead == MINUS_SIGN
		||	m_lookahead == EQUIVALENCY
		||	m_lookahead == EXCLAMATION
	  )
	{
		matchToken(m_lookahead);
		cast_expression();
	}
	if( m_lookahead == C_SIZEOF )
	{
		matchToken(C_SIZEOF);
		if( m_lookahead == OPEN_PARENTHESIS )
		{
			matchToken(OPEN_PARENTHESIS);
			type_name();
			matchToken(CLOSE_PARENTHESIS);
		}
		unary_expression();
	}

	/*
	str.Format(_T("SALE UNARY_EXPRESSION...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}


void CAipi_CParser::argument_expression_list()
{
	/*
	CString str;
	str.Format(_T("ARGUMENT EXPRESSION LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	assigment_expression();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken( COMMA);
			assigment_expression();
		}
	}

	/*
	str.Format(_T("SALE ARGUMENT EXPRESSION LIST...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
}

void CAipi_CParser::postfix_expression()
{
	/*
	CString str;
	str.Format(_T("POSTFIX_EXP...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	/*
	if(		m_lookahead == IDENTIFIER 
		||	m_lookahead == DIGIT
		||	m_lookahead == CONSTANT
		||	m_lookahead == LITERAL
		||	m_lookahead == OPEN_PARENTHESIS
	  )
	{ */
		primary_expression();
	//}
	
	switch( m_lookahead )
	{
		case OPEN_BRACKET:
			matchToken(OPEN_BRACKET);
			expression();
			matchToken( CLOSE_BRACKET);
			break;
		case OPEN_PARENTHESIS:
			matchToken(OPEN_PARENTHESIS);
			argument_expression_list();
			matchToken(CLOSE_PARENTHESIS);
			break;
		case PERIOD:
			matchToken(PERIOD);
			matchToken(IDENTIFIER);
			break;
		case PTR_OP:
			matchToken(PTR_OP);
			matchToken(IDENTIFIER);
			break;
		case INC_OP:
			matchToken(INC_OP);
			break;
		case DEC_OP:
			matchToken(DEC_OP);
			break;
			
		 
	}

/*
	str.Format(_T("SALE POSTFIX_EXP...%d  " ), m_lookahead);
	AfxMessageBox(str);	
*/	

}


void CAipi_CParser::primary_expression()
{
	/*
	CString str;
	str.Format(_T("PRIMARY_EXP...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if( m_lookahead > 399 && m_lookahead < 470 )
	{
			CAipi_Symbol sym;
			tstring sKW = sym.findIdKeyWord(m_lookahead);
			if( sKW != _T("NOT_FOUND"))
			{
				CString strSymbol = _T("( ");
				strSymbol += sKW.data();
				strSymbol += _T(" )");
				CAipi_Error err;
				err.displayGUIError(SEMANT, SEMANT_ERROR, _T(" Symbol " + strSymbol + " is a keyword of AIPI sintax. Keywords are not allowed in structs elements.") );
				
			}
			
	}
	
		
	switch ( m_lookahead )
	{
		case IDENTIFIER:
			matchToken(IDENTIFIER);
			break;
		case DIGIT:
			matchToken(DIGIT);
			if( m_currentId_Type != UNDEFINE )
			{
				if( m_currentId_Type != C_FLOAT || m_currentId_Type != C_DOUBLE )
				{
	
					if( g_currentDigit_Type == REAL_NUMBER )
					{
						CAipi_Tokenizer tkz;
						tstring sTK = tkz.v_previousLastToken();
		
						CString  strTK = _T("( "); 
						strTK += sTK.data();
						strTK += _T(" )");
					
						CAipi_Error err;
						err.displayGUIError(TYPE_ASSIGN, SEMANT_ERROR, _T(" Digit " + strTK + " is not compatible with type declaration.") );
					}
				}
			}
			break;
		case CONSTANT:
			matchToken(CONSTANT);
			break;
		case LITERAL:
			matchToken(LITERAL);
			break;
		case OPEN_PARENTHESIS:
			matchToken(OPEN_PARENTHESIS);
			//Checking for C++ cast style
			if(		m_lookahead == C_VOID 
				||	m_lookahead == C_CHAR
				||	m_lookahead == C_SHORT
				||	m_lookahead == C_INT
				||	m_lookahead == C_LONG
				||	m_lookahead == C_FLOAT
				||	m_lookahead == C_DOUBLE
				||	m_lookahead == C_SIGNED
				||	m_lookahead == C_UNSIGNED

				||	m_lookahead == C_STRUCT
				||	m_lookahead == C_UNION
				||	m_lookahead == C_ENUM
				
				||	m_lookahead == C_TYPEDEF 
				||	m_lookahead == C_EXTERN
				||	m_lookahead == C_STATIC
				||	m_lookahead == C_AUTO
				||	m_lookahead == C_REGISTER
				||	m_lookahead == C_CONST
				||	m_lookahead == C_VOLATILE
				
			   )
			{
				type_name();
				matchToken(CLOSE_PARENTHESIS);
				cast_expression();
				break;
				
			}
			else
			{
				expression();
				matchToken(CLOSE_PARENTHESIS);
				break;
			}

	}

	/*
	str.Format(_T("SALE PRIMARY_EXP...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
}


