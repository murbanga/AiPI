// Aipi_ExpParserRTRT.cpp: implementation of the CAipi_ExpParserRTRT class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_ExpParserRT.h"

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

CAipi_ExpParserRT::CAipi_ExpParserRT()
{

}

CAipi_ExpParserRT::~CAipi_ExpParserRT()
{

}


////////////////////////////////////////////////////////////////////////
//// Expression parser ////
//////////////////////////////////////////////////////////////////////////

void CAipi_ExpParserRT::initExpParserRT()
{

	CAipi_Lexer lex;
	//g_currentTimeTag = 0;
	g_currentId_IForm = 1000;
		
	if( g_dataSource == DATA_GUI )
	{
		m_lookahead = lex.getTokenGUI();
	}
	if( g_dataSource == DATA_FILE )
	{
		TCHAR symbol =  _gettc(g_fp);
		m_lookahead = lex.getTokenFile(symbol);
	}

	m_sToken = lex.m_sToken;
	//AfxMessageBox(m_sToken);	


	/*
	CString str;
	str.Format(_T("Look ahead con init ...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	

	translation_unit();

}


int CAipi_ExpParserRT::matchToken(int tk)
{
	//AfxMessageBox(_T("MATCH TOKEN Lexer"));
	
	CAipi_Lexer lex;
	
/*
	CString str;
	str.Format(_T("Incomming Token...%d  " ), tk);
	AfxMessageBox(str);
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
	if( g_dataSource == DATA_FILE )
	{
		TCHAR symbol =  _gettc(g_fp);
		m_lookahead = lex.getTokenFile(symbol);
	}


	m_sToken = lex.m_sToken;
	//AfxMessageBox(m_sToken);
	

	if( m_lookahead == _TEOF )
		return _TEOF;


return P_SUCCESS;

}


void CAipi_ExpParserRT::printStack()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Parser Stack  *******"));
		
	CString str = _T("");

	int size = m_stack.size();
	for( int i = 0; i< size; ++i )
	{
		double element = m_stack.top();
		str.Format(_T("Element...%d , %f " ), i, element);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);

	}

}


void CAipi_ExpParserRT::emit_declaration(int tk)
{


	if ( tk == IDENTIFIER )
	{
		CAipi_Tokenizer tkz;
		long id = tkz.v_lastIntFormToken();
		int type = tkz.v_previousLastIntFormToken();
				
	
		CAipi_STableGlobalNumeric st;
		tstring sToken = (LPCTSTR)m_sToken;
		st.addSymbol(id, sToken, type,  0);
		

		/*
		CString str;
		AfxMessageBox(m_sToken);
		str.Format(_T("ID...%d  " ), id);
		AfxMessageBox(str);
		str.Format(_T("Type...%d  " ), type);
		AfxMessageBox(str);
		*/	
		
		//st.printSTableNumeric();

	}

	if( tk == EQUAL )
	{
		if( !m_stack.empty() )
		{
			double result = m_stack.top();
			m_stack.pop();
			CAipi_STableGlobalNumeric st;
			st.editLastSTableNumericValue(result);
			
			/*
			CString str;
			str.Format(_T("TOP...%f  " ), result);
			AfxMessageBox(str);
			AfxMessageBox(m_sToken);
			*/
			
		}
	}
}


void CAipi_ExpParserRT::emit_expression(int tk)
{
	CAipi_Lexer lex;

	if( tk == IDENTIFIER )
	{
		/*
		TI_agregar( valcomp );
			
		int posTD = 0;
		int valor = 0;
		
		//Obtiene el valor correspondiente al identificador
		//en la tabla de datos
		posTD = TD_buscar( valcomp );
				
		//Si encuentra el identificador lo apila en la Máquina P
		if ( posTD != -1 )
		{
			valor = TD_getValorId( posTD );
			MP_apilar( valor );
		}
		*/
	}

	if( tk == LITERAL )
	{

	}

	if( tk == DIGIT )
	{
		//AfxMessageBox(_T("EMIT DIGIT"));
		//AfxMessageBox(m_sToken);
		double tk = _tcstod(m_sToken, NULL);
		m_stack.push(tk);
		/*
		CString str;
		str.Format(_T("Number...%f  " ), tk);
		AfxMessageBox(str);
		*/
	}

	//Add operation 
	if( tk == PLUS_SIGN )
	{
		
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			//AfxMessageBox(_T("EMIT SUMA"));
			//AfxMessageBox(m_sToken);
		

			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			result = left_op + right_op;

			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}
	if( tk == MINUS_SIGN )
	{
		//AfxMessageBox(_T("EMIT RESTA"));
		//AfxMessageBox(m_sToken);
		
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			

			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			result = left_op - right_op;

			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
		}
	}
	
	if( tk == ASTERIC )
	{
		//AfxMessageBox(_T("EMIT MULTIPLICATION"));
		//AfxMessageBox(m_sToken);
		
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			
			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			result = left_op * right_op;

			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	if( tk == SLASH )
	{
		//AfxMessageBox(_T("EMIT DIVISION"));
		//AfxMessageBox(m_sToken);
		
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			
			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			result = left_op / right_op;

			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	if( tk == PERCENT )
	{
		//AfxMessageBox(_T("EMIT MOD"));
		//AfxMessageBox(m_sToken);
		
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			
			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			result = (int)left_op % (int)right_op;

			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}

	}

	if( tk == UNARY_MINUS )
	{
		//AfxMessageBox(_T("ADD UNARY MINUS"));
		m_stack.push(-1);
	}

	if ( tk == UNARY_PLUS )
	{
		//AfxMessageBox(_T("ADD UNARY PLUS"));
		m_stack.push(1);
	}

	if( tk == UNARY_OP )
	{
		//AfxMessageBox(_T("EMIT UNARY"));
		
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			
			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			result = left_op * right_op;

			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}

	
	}

	if( tk == INC_OP )
	{
		//AfxMessageBox(_T("EMIT INC OP"));
		
		double result = 0;

		if( !m_stack.empty() )
		{
			
			result = m_stack.top();
			m_stack.pop();
			++result;

			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	
	}

	if( tk == DEC_OP )
	{
		//AfxMessageBox(_T("EMIT DEC OP"));
		
		double result = 0;

		if( !m_stack.empty() )
		{
			
			result = m_stack.top();
			m_stack.pop();
			--result;

			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	if( tk == LT )
	{
		//AfxMessageBox(_T("EMIT LESS THAN"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			
			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			
			if( left_op < right_op )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	if( tk == GT )
	{
		//AfxMessageBox(_T("EMIT GREATER THAN"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			
			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			
			if( left_op > right_op )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stack.push(result);
			/*	
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	if( tk == LE )
	{
		//AfxMessageBox(_T("EMIT LESS-EQUAL THAN"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			
			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			
			if( left_op <= right_op )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	if( tk == GE )
	{
		//AfxMessageBox(_T("EMIT GREATER-EQUAL THAN"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			
			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			
			if( left_op >= right_op )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	if( tk == ET )
	{
		//AfxMessageBox(_T("EMIT EQUAL THAN"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			
			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			
			if( left_op == right_op )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}
	
	if( tk == NE )
	{
		//AfxMessageBox(_T("EMIT NO-EQUAL THAN"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			
			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			
			if( left_op != right_op )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	if( tk == AND_OP )
	{
		//AfxMessageBox(_T("EMIT AND"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			
			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			
			if( left_op == 1 && right_op == 1 )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	if( tk == OR_OP )
	{
		//AfxMessageBox(_T("EMIT OR"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stack.empty() )
		{
			
			right_op = m_stack.top();
			m_stack.pop();
			left_op = m_stack.top();
			m_stack.pop();
			
			if( left_op == 0 && right_op == 0 )
			{
				result = 0;
			}
			else
			{
				result = 1;
			}
			
			m_stack.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	/*
	int size = m_stack.size();
	CString str;
	str.Format(_T("Size...%d"  ), size);
	AfxMessageBox(str);
	*/

}


////////////////////////////////////////////////

			/// PARSER ////

///////////////////////////////////////////////

void CAipi_ExpParserRT::translation_unit()
{
	if( m_lookahead != _TEOF )
	{
		if( m_lookahead == COMMENT )
		{
			matchToken(COMMENT);
		}
		
		if(		m_lookahead == C_VOID 
			||	m_lookahead == C_CHAR
			||	m_lookahead == C_SHORT
			||	m_lookahead == C_INT
			||	m_lookahead == C_LONG
			||	m_lookahead == C_FLOAT
			||	m_lookahead == C_DOUBLE
		  )	
		{
			declaration();
			expression();
			translation_unit();
		}
		else
		{
			CAipi_Error err;
			err.displayGUIError(ABNORMAL_STOP, WARNING_ERROR, _T("The parser was not able to finish the depuration process. The initialization sintax is incorrect.") );
			
			
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
		err.displayGUIError(EMPTY_MSG, -1, _T(" *************************************************************************************************************"));
		err.displayGUIError(ERROR_COUNT, INFO_ERROR, _T(" Lexical errors:...") + strLex + _T("   Sintax errors:...") + strSintax + _T("   Semantic errors:...") + strSemant + _T("                    *Total errors:...") + str_nError );
		err.displayGUIError(WARNING_COUNT, INFO_ERROR, _T(" Warnings:...") + strWarning + _T("   Warning questions:...") + strQuestion + _T("                    *Total warnings:...") + str_nWarning );
		err.displayGUIError(FINISH, INFO_ERROR, _T("   **** Debug Summary:-    ") + str_nError + _T(" error(s),   ") + str_nWarning + _T(" warning(s). ****" ));

		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Debug Summary:-    ") + str_nError + _T(" error(s),   ") + str_nWarning + _T(" warning(s). ****" ));
		

	}
	

}


//////////////////////////////////////////////////////////////////////////////////////////////////
/// Declaration Parser ////
//////////////////////////////////////////////////////////////////////////////////////////////////
void CAipi_ExpParserRT::declaration_specifiers()
{
	
	if(		m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
	  )
	{
		matchToken(m_lookahead);
		declaration_specifiers();
		

	}
	
}


void CAipi_ExpParserRT::declaration()
{
	
	declaration_specifiers();
	
	if( m_lookahead == SEMICOLON)
	{
		matchToken(SEMICOLON);
		return;
	}
	
	declarator_list_init();
	matchToken(SEMICOLON);
	

}



void CAipi_ExpParserRT::declarator_list_init()
{
	declarator_init();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			declarator_init();
		}
	}
	
	//Multidimensional arrays
	if( m_lookahead == OPEN_BRACKET )
	{
		declarator_init();
	}
	

}

void CAipi_ExpParserRT::declarator_init()
{
	declarator_direct();
	
	if( m_lookahead == EQUAL )
	{
		matchToken(EQUAL);
		initializer();
		emit_declaration(EQUAL);
		

	}
	
	

}




void CAipi_ExpParserRT::initializer()
{
	
	expression_assignment();
	

	//initialize an array 
	//Example: int a[] = { 6, 8 }
	if( m_lookahead == OPEN_BRACE )
	{
		
		matchToken(OPEN_BRACE);
		initializer_list();
		
		matchToken(CLOSE_BRACE);
		

		if( m_lookahead == COMMA)
		{
			matchToken(COMMA);
			initializer_list();
			
			//AfxMessageBox(_T("FIN initializer"));
			
			
		}
	}
	

}

void CAipi_ExpParserRT::initializer_list()
{
	
	initializer();
	//matchToken(DIGIT);
	//AfxMessageBox(_T("CLOSE BRACE"));

	//AfxMessageBox(_T("antes de coma"));
	//CString str;
	//str.Format(_T("Antes de coma Look Ahead...%d  " ), m_lookahead);
	//AfxMessageBox(str);
	
	
	if( m_lookahead == COMMA )
	{
		//AfxMessageBox(_T("Entro de coma"));
		while ( m_lookahead == COMMA )
		{
			//AfxMessageBox(_T("while coma"));
			matchToken(COMMA);
			initializer_list();
			
		}
	}

	
}




void CAipi_ExpParserRT::declarator_direct()
{
		
	if( m_lookahead == IDENTIFIER )
	{
		emit_declaration(IDENTIFIER);
		matchToken(IDENTIFIER);
		
	}

	//Function declaration
	if( m_lookahead == OPEN_PARENTHESIS )
	{
		while( m_lookahead == OPEN_PARENTHESIS)
		{
			matchToken(OPEN_PARENTHESIS);

			if(		m_lookahead == IDENTIFIER 
				||	m_lookahead == OPEN_PARENTHESIS 
				||	m_lookahead == OPEN_BRACKET
			  )
			{
				declarator_direct();
			}
			if(		m_lookahead == C_VOID 
				||	m_lookahead == C_CHAR
				||	m_lookahead == C_SHORT
				||	m_lookahead == C_INT
				||	m_lookahead == C_LONG
				||	m_lookahead == C_FLOAT
				||	m_lookahead == C_DOUBLE
				 
			 )
			{
				parameter_list();
			}
			
			
			matchToken(CLOSE_PARENTHESIS);
			
		}
	}


	//CString str;
	//str.Format(_T("Look Ahead...%d  " ), m_lookahead);
	//AfxMessageBox(str);
	
	//Array declaration
	if( m_lookahead == OPEN_BRACKET )
	{
		matchToken(OPEN_BRACKET);
		
		if( m_lookahead == DIGIT )
		{
			expression_atom_constant();
		}
		matchToken(CLOSE_BRACKET);
		
	}
	
	

}




void CAipi_ExpParserRT::parameter_declaration()
{
	
	
	declaration_specifiers();
	
	if( m_lookahead == IDENTIFIER || m_lookahead == OPEN_PARENTHESIS || m_lookahead == OPEN_BRACKET)
	{
		declarator_direct();
	}
	
}



void CAipi_ExpParserRT::parameter_list()
{
		
	parameter_declaration();

	if( m_lookahead == COMMA)
	{
		while(m_lookahead == COMMA)
		{
			matchToken(COMMA);
			parameter_declaration(); 
		}
	}

	

}





//////////////////////////////////////////////////////////////////////////////////////////////
///// Expression Parser /////
/////////////////////////////////////////////////////////////////////////////////////////////


void CAipi_ExpParserRT::expression()
{
	
	expression_assignment();
	expression_logical_or();
}


void CAipi_ExpParserRT::expression_assignment()
{
	/*
	if( m_lookahead == IDENTIFIER )
	{
		AfxMessageBox(_T("IDENTIFICADOR"));
		expression_atom_identifier();
	}
	*/
	///expression_factor();

	if( m_lookahead == EQUAL)
	{
		matchToken(EQUAL);
		expression_logical_or();
	}
	
	expression_logical_or();
	
	
			
}


void CAipi_ExpParserRT::expression_logical_or()
{
	expression_logical_and();
		
	while(true)
	{
		if( m_lookahead == OR_OP )
		{
			matchToken(OR_OP);
			expression_logical_and();
			emit_expression(OR_OP);
		}
		else
		{
			return;
		}
	}	

}


void CAipi_ExpParserRT::expression_logical_and()
{
	expression_equality();
		
	while(true)
	{
		if( m_lookahead == AND_OP )
		{
			matchToken(AND_OP);
			expression_equality();
			emit_expression(AND_OP);
		}
		else
		{
			return;
		}
	}

}

void CAipi_ExpParserRT::expression_equality()
{
	expression_relational();

	while(true)
	{
		if( m_lookahead == ET || m_lookahead == NE )
		{
			int tk = m_lookahead;
			matchToken(tk);
			expression_relational();
			emit_expression(tk);
		}
		else
		{
			return;
		}
	}

}


void CAipi_ExpParserRT::expression_relational()
{
	expression_aritmetic();

	while(true)
	{
		if( m_lookahead == LT || m_lookahead == LE || m_lookahead == GT || m_lookahead == GE  )
		{
			int tk = m_lookahead;
			matchToken(tk);
			expression_aritmetic();
			emit_expression(tk);
		}
		else
		{
			return;
		}
	}
}



void CAipi_ExpParserRT::expression_aritmetic()
{
	expression_term();
		
	while(true)
	{
		if( m_lookahead == PLUS_SIGN || m_lookahead == MINUS_SIGN )
		{
			int tk = m_lookahead;
			//AfxMessageBox(_T("Arit get Token"));
			matchToken(tk);
			//AfxMessageBox(_T("Arit get Term"));
			expression_term();
			//AfxMessageBox(_T("Arit emit_expression"));
			//CString str;
			//str.Format(_T("Look Ahead...%d  " ), m_lookahead);
			//AfxMessageBox(str);
			emit_expression(tk);
			
		}
		else
		{
			return;
		}
	}

}


void CAipi_ExpParserRT::expression_term()
{
	expression_factor();
	while(true)
	{
		if( m_lookahead == ASTERIC || m_lookahead == SLASH || m_lookahead == PERCENT )
		{
			int tk = m_lookahead;
			matchToken(tk);
			expression_factor();
			emit_expression(tk);
		}
		else
		{
			return;
		}
	}

}


void CAipi_ExpParserRT::expression_unary_plus()
{
	//AfxMessageBox(_T("CASE UNARY"));
	emit_expression(UNARY_PLUS);
	matchToken(PLUS_SIGN);
	expression_factor();
	emit_expression(UNARY_OP);
}


void CAipi_ExpParserRT::expression_unary_minus()
{
	//AfxMessageBox(_T("UNARY MINUS"));
	emit_expression(UNARY_MINUS);
	matchToken(MINUS_SIGN);
	expression_factor();
	emit_expression(UNARY_OP);
}

void CAipi_ExpParserRT::expression_unary_increment()
{
		
	//AfxMessageBox(_T("INCREMENT OPERATOR"));
	matchToken(INC_OP);
	//It just apply to identifiers
	if( m_lookahead == IDENTIFIER )
	{
		expression_factor();
		emit_expression(INC_OP);
	}	


}

void CAipi_ExpParserRT::expression_unary_decrement()
{
	//AfxMessageBox(_T("DECREMENT OPERATOR"));
	matchToken(DEC_OP);
	//It just apply to identifiers
	if( m_lookahead = IDENTIFIER )
	{
		expression_factor();
		emit_expression(DEC_OP);
	}
}


/*
void CAipi_ExpParserRT::expression_factor()
{
		
	switch(m_lookahead)
	{
	case IDENTIFIER:
		emit_expression(IDENTIFIER);
		getToken();
		if( m_lookahead == INC_OP )
		{
			expression_unary_increment();	
		}
		if( m_lookahead == DEC_OP )
		{
			expression_unary_decrement();
		}
		break;
	case DIGIT:
		emit_expression(DIGIT);
		getToken();
		break;
	case LITERAL:
		emit_expression(LITERAL);
		getToken();
		break;
	case OPEN_PARENTHESIS:
		getToken();
		expression();
		getToken();
		break;

    case MINUS_SIGN:
		expression_unary_minus();
		break;
	case PLUS_SIGN:
		expression_unary_plus();
		break;
	case INC_OP:
		expression_unary_increment();
		break;
    case DEC_OP:
		expression_unary_decrement();
		break;
	
	}


}

*/


void CAipi_ExpParserRT::expression_factor()
{
	switch(m_lookahead)
	{
	case IDENTIFIER:
		expression_atom_identifier();
		break;
	case DIGIT:
		expression_atom_constant();
		break;
	case LITERAL:
		expression_atom_literal();
		break;
	case OPEN_PARENTHESIS:
		matchToken(OPEN_PARENTHESIS);
		expression();
		matchToken(CLOSE_PARENTHESIS);
		break;
	case MINUS_SIGN:
		expression_unary_minus();
		break;
	case PLUS_SIGN:
		expression_unary_plus();
		break;
	case INC_OP:
		expression_unary_increment();
		break;
    case DEC_OP:
		expression_unary_decrement();
		break;
	}


}





void CAipi_ExpParserRT::expression_atom_identifier()
{
	emit_expression(IDENTIFIER);
	matchToken(IDENTIFIER);

	if( m_lookahead == INC_OP )
	{
		expression_unary_increment();	
	}
	if( m_lookahead == DEC_OP )
	{
		expression_unary_decrement();
	}

}


void CAipi_ExpParserRT::expression_atom_constant()
{
	emit_expression(DIGIT);
	matchToken(DIGIT);

}

void CAipi_ExpParserRT::expression_atom_literal()
{
	emit_expression(LITERAL);
	matchToken(LITERAL);
}
		



int CAipi_ExpParserRT::keyword_type_name()
{
	if(		m_lookahead == C_VOID 
		||	m_lookahead == C_CHAR
		||	m_lookahead == C_SHORT
		||	m_lookahead == C_INT
		||	m_lookahead == C_LONG
		||	m_lookahead == C_FLOAT
		||	m_lookahead == C_DOUBLE
	  )
	{
		return m_lookahead;
	}
	 
return P_UNSUCCESS;
}


int CAipi_ExpParserRT::operator_unary()
{
	if(		m_lookahead == UNARY_MINUS 
		||	m_lookahead == UNARY_PLUS
		||	m_lookahead == INC_OP
		||	m_lookahead == DEC_OP
	  )
	{
		return m_lookahead;
	}
	 
return P_UNSUCCESS;	

}

int CAipi_ExpParserRT::operator_assigment()
{
	
	if(		m_lookahead == EQUAL 
		||	m_lookahead == MUL_ASSIGN
		||	m_lookahead == DIV_ASSIGN
		||	m_lookahead == ADD_ASSIGN
		||	m_lookahead == SUB_ASSIGN
	  )
	{
		return m_lookahead;
	}
	 
return P_UNSUCCESS;

}



