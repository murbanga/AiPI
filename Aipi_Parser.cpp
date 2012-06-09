// Aipi_Parser.cpp: implementation of the CAipi_Parser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_Parser.h"

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

CAipi_Parser::CAipi_Parser()
{
	
}

CAipi_Parser::~CAipi_Parser()
{


}


int CAipi_Parser::matchToken(int tk )
{
	CAipi_Lexer lex;
	
/*
	CString str;
	str.Format(_T("Incomming Token...%d  " ), tk);
	AfxMessageBox(str);

	str.Format(_T("Current Position...%d  " ), g_currentPos);
	AfxMessageBox(str);
*/	
	
	//wsprintf(buffer, _T("Letra: %c"), tk);
	//AfxMessageBox(buffer);
	
	//str.Format(_T("Look Ahead...%d  " ), m_lookahead);
	//AfxMessageBox(str);
		
	if ( m_lookahead != tk)
	{
		CString strSymbol = _T("");
		
		if( tk < 256 )
		{
			//strSymbol.Format(_T("( %c )" ), tk);
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
		err.displayFileError(SINTAX, SINTAX_ERROR, _T(" Symbol " + strTK + " doesn't match. Expected symbol " + strSymbol + " was not found.") );
		return SINTAX_ERROR;
	}

	
	
	if( g_dataSource == DATA_GUI )
	{
		++g_currentPos;
		m_lookahead = lex.getTokenGUI();
		
		/*
		str.Format(_T("Next Position...%d  " ), g_currentPos);
		AfxMessageBox(str);
		str.Format(_T("Next Look Ahead...%d  " ), m_lookahead);
		AfxMessageBox(str);
	    */
		
		if( m_lookahead == COMMENT )
		{
			//AfxMessageBox(_T("Match Token Comment")); 
			do
			{
				++g_currentPos;
				m_lookahead = lex.getTokenGUI();
				//AfxMessageBox(_T("Match Token While")); 
			
		
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

return P_SUCCESS;
}




void CAipi_Parser::initParser()
{
	CAipi_Lexer lex;
	CAipi_Emitter eo;

	

	g_currentId_IForm = 1000;
	
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
	if( m_lookahead == COMMENT )
	{
		AfxMessageBox(_T("hola comment"));
		do
		{
			++g_currentPos;
			m_lookahead = lex.getTokenGUI();
		AfxMessageBox(_T("hola while"));	
		
		}while (m_lookahead == COMMENT );
	}

	CString str;
	str.Format(_T("Look ahead con init ...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	/*
	directive_list();
	class_element_list();
	rule_element_list();
*/
	//expression();
	
	translation_unit();
		
	
 
}

/////////////////////////////////////////////////////////////////////

	////  AIPI LANGUAGE PARSER ////

//////////////////////////////////////////////////////////////////////

void CAipi_Parser::translation_unit()
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
			translation_unit();
		}
		else if(	m_lookahead == DIGIT
				||	m_lookahead == IDENTIFIER
				)
		{
			expression();
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


//////////////////////////////////////////////////////////////////////
/// Directive functions///
//////////////////////////////////////////////////////////////////////

void CAipi_Parser::directive_list()
{
	if( m_lookahead == NUMBER_SIGN )
	{
		directive();
		directive_list();
	}

}



void CAipi_Parser::directive()
{
	if( m_lookahead == NUMBER_SIGN )
	{
		matchToken( NUMBER_SIGN );
		matchToken( AIPI_INCLUDE );
		matchToken(LT);
		matchToken(IDENTIFIER);
		matchToken(PERIOD);
		
		switch( m_lookahead)
		{
		case TXT_EXT:
			matchToken(TXT_EXT);
			break;
		case KNW_EXT:
			matchToken(KNW_EXT);
			break;
		case JS_EXT:
			matchToken(JS_EXT);
			break;
		case VBS_EXT:
			matchToken(VBS_EXT);
			break;
		case C_EXT:
			matchToken(C_EXT);
			break;
		case SQL_EXT:
			matchToken(C_EXT);
			break;
		
		
		}
		
		
		matchToken(GT);

	}

	
}

////////////////////////////////////////////////////////////////////
/// Class functions ///
////////////////////////////////////////////////////////////////////

int CAipi_Parser::attribute_type()
{
	//CString  str;
	//str.Format(_T("ATTRIBUTE TYPE lookahead...%d  " ), m_lookahead);
	//AfxMessageBox(str);
	
	int type = LITERAL;

	switch(m_lookahead)
	{
		case AIPI_CHAR:
			matchToken(AIPI_CHAR);
			type = LITERAL;
			break;
		case AIPI_STRING:
			matchToken(AIPI_STRING);
			type = LITERAL;
			break;
		case AIPI_INT:
			matchToken(AIPI_INT);
			type = DIGIT;
			break;
		case AIPI_LONG:
			matchToken(AIPI_LONG);
			type = DIGIT;
			break;
		case AIPI_SHORT:
			matchToken(AIPI_SHORT);
			type = DIGIT;
			break;;
		case AIPI_FLOAT:
			matchToken(AIPI_FLOAT);
			type = DIGIT;
			break;
		case AIPI_DOUBLE:
			matchToken(AIPI_DOUBLE);
			type = DIGIT;
			break;

		default:
			type = AIPI_ERROR;


	}

return type;
}


void CAipi_Parser::class_attr_declaration()
{
	int type = attribute_type();
	/*
	CString str;
	str.Format(_T("TYPE...%d  " ), type);
	AfxMessageBox(str);
	*/

	switch(type)
	{
		case LITERAL:
			matchToken(IDENTIFIER);
			if( m_lookahead == EQUAL )
			{
				matchToken(EQUAL);
				matchToken(LITERAL);
			}
			if( m_lookahead == LITERAL)
			{
				matchToken(LITERAL);
			}
			break;
        case DIGIT:
			matchToken(IDENTIFIER);
			if( m_lookahead == EQUAL )
			{
				matchToken(EQUAL);
				matchToken(DIGIT);
			}
			break;
		case AIPI_ERROR:
			//Mensaje error
			break;
	}
		

}


void CAipi_Parser::class_attr_declaration_list()
{
	
	class_attr_declaration();
	
	if( m_lookahead == SEMICOLON )
	{
		while ( m_lookahead == SEMICOLON )
		{
			matchToken(SEMICOLON);
			class_attr_declaration_list();
		}
	}

}

void CAipi_Parser::class_element()
{
	if( m_lookahead == AIPI_CLASS)
	{
	matchToken(AIPI_CLASS);
	matchToken(IDENTIFIER);
	matchToken( OPEN_BRACE);
	class_attr_declaration_list();
	matchToken(CLOSE_BRACE);
	}

}


void CAipi_Parser::class_element_list()
{
	class_element();
	if( m_lookahead == AIPI_CLASS )
	{
		class_element_list();
	}

}



////////////////////////////////////////////////////////////////////
/// Rule functions ///
////////////////////////////////////////////////////////////////////


void CAipi_Parser::rule_element()
{
	if( m_lookahead == AIPI_RULE )
	{
	matchToken(AIPI_RULE);
	matchToken(LITERAL);
	matchToken(OPEN_PARENTHESIS);
	rule_parameter_list();
	matchToken(CLOSE_PARENTHESIS);
	matchToken(OPEN_BRACE);
	lhs_start();
	lhs_element_list();
	rhs_start();
	rhs_element_list();
	matchToken(CLOSE_BRACE);
	}
	
}



void CAipi_Parser::rule_element_list()
{
	rule_element();
	if( m_lookahead == AIPI_RULE )
	{
		rule_element_list();
	}

}


void CAipi_Parser::rule_parameter()
{
		
	if( m_lookahead == AIPI_CF)
	{
		matchToken(AIPI_CF);
		matchToken(COLON);
		matchToken(DIGIT);
	}

	if( m_lookahead == AIPI_WEIGHT)
	{
		matchToken(AIPI_WEIGHT);
		matchToken(COLON);
		matchToken(DIGIT);
	}


}


void CAipi_Parser::rule_parameter_list()
{
	
	rule_parameter();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			rule_parameter();
		}
	}
	


}


////////////////////////////////////////////////////////////////////
/// Left hand side functions ///
////////////////////////////////////////////////////////////////////

void CAipi_Parser::lhs_start()
{
	if( m_lookahead == AIPI_IF )
	{
		matchToken(AIPI_IF);
	}
}

void CAipi_Parser::lhs_connector()
{
	if( m_lookahead == AIPI_AND )
	{
		matchToken(AIPI_AND);
	}
	if( m_lookahead == AIPI_OR )
	{
		matchToken(AIPI_OR);
	}

}

void CAipi_Parser::lhs_element()
{
	if( m_lookahead == IDENTIFIER )
	{
		matchToken(IDENTIFIER);
		lhs_attribute_value_list();
		lhs_connector();
	}

	if( m_lookahead == AIPI_VAR )
	{
		matchToken(AIPI_VAR);
		lhs_attribute_value_list();
		lhs_connector();

	}

	if( m_lookahead == OPEN_PARENTHESIS )
	{
		matchToken(OPEN_PARENTHESIS);
		lhs_element_list();
		matchToken(CLOSE_PARENTHESIS);
		lhs_connector();
	}

	
	 

}

void CAipi_Parser::lhs_element_list()
{
	
   	lhs_element();
	if( m_lookahead == IDENTIFIER || m_lookahead == OPEN_PARENTHESIS || m_lookahead == AIPI_VAR )
	{
		lhs_element_list();
	}

}


void CAipi_Parser::lhs_attribute_value_list()
{

	lhs_attribute_value();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			lhs_attribute_value();
		}
	}

	lhs_fact_address();
	
	


}


void CAipi_Parser::lhs_fact_address()
{
	if( m_lookahead == OPEN_PARENTHESIS )
	{
		matchToken(OPEN_PARENTHESIS);
		matchToken(AIPI_FACT_ADDRESS);
		matchToken(COLON);
		matchToken(AIPI_VAR);
		matchToken(CLOSE_PARENTHESIS);
	}
		
		

}

////////////////////////////////////////////////////////////////////
/// Right hand side functions ///
////////////////////////////////////////////////////////////////////


void CAipi_Parser::rhs_start()
{
	if( m_lookahead == AIPI_THEN )
	{
		matchToken(AIPI_THEN);
	}

}


void CAipi_Parser::rhs_connector()
{
	if( m_lookahead == AIPI_AND )
	{
		matchToken(AIPI_AND);
	}
}


void CAipi_Parser::rhs_element_list()
{
	rhs_element();
	if( m_lookahead == IDENTIFIER || m_lookahead == OPEN_PARENTHESIS )
	{
		rhs_element_list();
	}

}


void CAipi_Parser::rhs_element()
{

	if( m_lookahead == IDENTIFIER )
	{
		matchToken(IDENTIFIER);
		rhs_attribute_value_list();
		rhs_connector();
	}

	if( m_lookahead == OPEN_PARENTHESIS )
	{
		matchToken(OPEN_PARENTHESIS);
		rhs_element_list();
		matchToken(CLOSE_PARENTHESIS);
		rhs_connector();
	}

		
}



void CAipi_Parser::lhs_attribute_value()
{
	
	if( m_lookahead == IDENTIFIER )
	{
		matchToken(IDENTIFIER);
	}
	if( m_lookahead == AIPI_VAR )
	{
		matchToken(AIPI_VAR);
	}

	switch(m_lookahead)
	{
		case AIPI_VAR:
			matchToken(AIPI_VAR);
			lhs_multi_attribute_value();
			break;
			
		case LITERAL:
			matchToken(LITERAL);
			lhs_multi_attribute_value();
			break;
		case EQUAL:
			matchToken(EQUAL);
			if( m_lookahead == DIGIT )
			{
				matchToken(DIGIT);
			}
			if( m_lookahead == AIPI_VAR )
			{
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;
		case NE:
			matchToken(NE);
			if( m_lookahead == DIGIT )
			{
				matchToken(DIGIT);
			}
			if( m_lookahead == AIPI_VAR )
			{
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;
		case LT:
			matchToken(LT);
			if( m_lookahead == DIGIT )
			{
				matchToken(DIGIT);
			}
			if( m_lookahead == AIPI_VAR )
			{
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;
		case LE:
			matchToken(LE);
			if( m_lookahead == DIGIT )
			{
				matchToken(DIGIT);
			}
			if( m_lookahead == AIPI_VAR )
			{
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;
		case GT:
			matchToken(GT);
			if( m_lookahead == DIGIT )
			{
				matchToken(DIGIT);
			}
			if( m_lookahead == AIPI_VAR )
			{
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;
		case GE:
			matchToken(GE);
			if( m_lookahead == DIGIT )
			{
				matchToken(DIGIT);
			}
			if( m_lookahead == AIPI_VAR )
			{
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;

	}

}



void CAipi_Parser::lhs_multi_attribute_value()
{
	if( m_lookahead == AND_OP )
	{
		while( m_lookahead == AND_OP )
		{
			matchToken(AND_OP);
			if( m_lookahead == IDENTIFIER )
			{
				matchToken(IDENTIFIER);
			}
						
			switch(m_lookahead)
			{
				case AIPI_VAR:
					matchToken(AIPI_VAR);
					break;
				case LITERAL:
					matchToken(LITERAL);
					break;
				case EQUAL:
					matchToken(EQUAL);
					if( m_lookahead == DIGIT )
					{
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						matchToken(AIPI_VAR);
					}
					break;
				case NE:
					matchToken(NE);
					if( m_lookahead == DIGIT )
					{
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						matchToken(AIPI_VAR);
					}
					break;
				case LT:
					matchToken(LT);
					if( m_lookahead == DIGIT )
					{
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						matchToken(AIPI_VAR);
					}
					break;
				case LE:
					matchToken(LE);
					if( m_lookahead == DIGIT )
					{
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						matchToken(AIPI_VAR);
					}
					break;
				case GT:
					matchToken(GT);
					if( m_lookahead == DIGIT )
					{
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						matchToken(AIPI_VAR);
					}
					break;
				case GE:
					matchToken(GE);
					if( m_lookahead == DIGIT )
					{
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						matchToken(AIPI_VAR);
					}
					break;
			
			}
		}
	}

	if( m_lookahead == OR_OP )
	{
		while( m_lookahead == OR_OP )
		{
			matchToken(OR_OP);
			if( m_lookahead == IDENTIFIER )
			{
				matchToken(IDENTIFIER);
			}
			
			switch(m_lookahead)
			{
			case LITERAL:
				matchToken(LITERAL);
				break;
			case EQ:
				matchToken(ET);
				if( m_lookahead == DIGIT )
				{
					matchToken(DIGIT);
				}
				if( m_lookahead == AIPI_VAR )
				{
					matchToken(AIPI_VAR);
				}
				break;
			case NE:
				matchToken(NE);
				if( m_lookahead == DIGIT )
				{
					matchToken(DIGIT);
				}
				if( m_lookahead == AIPI_VAR )
				{
					matchToken(AIPI_VAR);
				}
				break;
			case LT:
				matchToken(LT);
				if( m_lookahead == DIGIT )
				{
					matchToken(DIGIT);
				}
				if( m_lookahead == AIPI_VAR )
				{
					matchToken(AIPI_VAR);
				}
				break;
			case LE:
				matchToken(LE);
				if( m_lookahead == DIGIT )
				{
					matchToken(DIGIT);
				}
				if( m_lookahead == AIPI_VAR )
				{
					matchToken(AIPI_VAR);
				}
				break;
			case GT:
				matchToken(GT);
				if( m_lookahead == DIGIT )
				{
					matchToken(DIGIT);
				}
				if( m_lookahead == AIPI_VAR )
				{
					matchToken(AIPI_VAR);
				}
				break;
			case GE:
				matchToken(GE);
				if( m_lookahead == DIGIT )
				{
					matchToken(DIGIT);
				}
				if( m_lookahead == AIPI_VAR )
				{
					matchToken(AIPI_VAR);
				}
				break;
			}
			
		}
	}

}


void CAipi_Parser::rhs_attribute_value_list()
{
	rhs_attribute_value();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			rhs_attribute_value();
		}
	}

	if( m_lookahead == OPEN_PARENTHESIS )
	{
		matchToken(OPEN_PARENTHESIS);
		rhs_parameter_list();
		matchToken(CLOSE_PARENTHESIS);
	}
	

}



void CAipi_Parser::rhs_parameter()
{
	if( m_lookahead == AIPI_CF)
	{
		matchToken(AIPI_CF);
		matchToken(COLON);
		matchToken(DIGIT);
	}


}

void CAipi_Parser::rhs_parameter_list()
{
	rhs_parameter();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			rhs_parameter();
		}
	}


}

void CAipi_Parser::rhs_attribute_value()
{
	
	matchToken(IDENTIFIER);
		
	switch(m_lookahead)
	{
			
		case LITERAL:
			matchToken(LITERAL);
			rhs_multi_attribute_value();
			break;
		case EQUAL:
			matchToken(EQUAL);
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;
		case NE:
			matchToken(NE);
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;
		case LT:
			matchToken(LT);
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;
		case LE:
			matchToken(LE);
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;
		case GT:
			matchToken(GT);
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;
		case GE:
			matchToken(GE);
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;

	}

}


void CAipi_Parser::rhs_multi_attribute_value()
{
	if( m_lookahead == AND_OP )
	{
		while( m_lookahead == AND_OP )
		{
			matchToken(AND_OP);
			if( m_lookahead == IDENTIFIER )
			{
				matchToken(IDENTIFIER);
			}
						
			switch(m_lookahead)
			{
				case LITERAL:
					matchToken(LITERAL);
					break;
				case EQUAL:
					matchToken(EQUAL);
					matchToken(DIGIT);
					break;
				case NE:
					matchToken(NE);
					matchToken(DIGIT);
					break;
				case LT:
					matchToken(LT);
					matchToken(DIGIT);
					break;
				case LE:
					matchToken(LE);
					matchToken(DIGIT);
					break;
				case GT:
					matchToken(GT);
					matchToken(DIGIT);
					break;
				case GE:
					matchToken(GE);
					matchToken(DIGIT);
					break;
			
			}
		}
	}

	if( m_lookahead == OR_OP )
	{
		while( m_lookahead == OR_OP )
		{
			matchToken(OR_OP);
			if( m_lookahead == IDENTIFIER )
			{
				matchToken(IDENTIFIER);
			}
			
			switch(m_lookahead)
			{
			case LITERAL:
				matchToken(LITERAL);
				break;
			case EQ:
				matchToken(ET);
				matchToken(DIGIT);
				break;
			case NE:
				matchToken(NE);
				matchToken(DIGIT);
				break;
			case LT:
				matchToken(LT);
				matchToken(DIGIT);
				break;
			case LE:
				matchToken(LE);
				matchToken(DIGIT);
				break;
			case GT:
				matchToken(GT);
				matchToken(DIGIT);
				break;
			case GE:
				matchToken(GE);
				matchToken(DIGIT);
				break;
			}
			
		}
	}

}

////////////////////////////////////////////////////////

	////   Parser   /////

/////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////////////////
/// Declaration Parser ////
//////////////////////////////////////////////////////////////////////////////////////////////////
void CAipi_Parser::declaration_specifiers()
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


void CAipi_Parser::declaration()
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



void CAipi_Parser::declarator_list_init()
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

void CAipi_Parser::declarator_init()
{
	declarator_direct();
	
	if( m_lookahead == EQUAL )
	{
		matchToken(EQUAL);
		initializer();
		
	}

}




void CAipi_Parser::initializer()
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

void CAipi_Parser::initializer_list()
{
	
	initializer();
		
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			initializer_list();
			
		}
	}

	
}




void CAipi_Parser::declarator_direct()
{
		
	if( m_lookahead == IDENTIFIER )
	{
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




void CAipi_Parser::parameter_declaration()
{
	
	
	declaration_specifiers();
	
	if( m_lookahead == IDENTIFIER || m_lookahead == OPEN_PARENTHESIS || m_lookahead == OPEN_BRACKET)
	{
		declarator_direct();
	}
	
}



void CAipi_Parser::parameter_list()
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



////////////////////////////////////////////////////////////////////////
//// Expression parser ////
//////////////////////////////////////////////////////////////////////////


void CAipi_Parser::expression()
{
	expression_assignment();
	expression_logical_or();

}


void CAipi_Parser::expression_assignment()
{
	if( m_lookahead == EQUAL)
	{
		matchToken(EQUAL);
		expression_logical_or();
	}
	
	expression_logical_or();
	
	
			
}


void CAipi_Parser::expression_logical_or()
{
	expression_logical_and();
		
	while(true)
	{
		if( m_lookahead == OR_OP )
		{
			matchToken(OR_OP);
			expression_logical_and();
			
		}
		else
		{
			return;
		}
	}	

}


void CAipi_Parser::expression_logical_and()
{
	expression_equality();
		
	while(true)
	{
		if( m_lookahead == AND_OP )
		{
			matchToken(AND_OP);
			expression_equality();
		}
		else
		{
			return;
		}
	}

}

void CAipi_Parser::expression_equality()
{
	expression_relational();

	while(true)
	{
		if( m_lookahead == ET || m_lookahead == NE )
		{
			matchToken(m_lookahead);
			expression_relational();
		}
		else
		{
			return;
		}
	}

}


void CAipi_Parser::expression_relational()
{
	expression_aritmetic();

	while(true)
	{
		if( m_lookahead == LT || m_lookahead == LE || m_lookahead == GT || m_lookahead == GE  )
		{
			matchToken(m_lookahead);
			expression_aritmetic();
		}
		else
		{
			return;
		}
	}
}


void CAipi_Parser::expression_aritmetic()
{
	expression_term();
		
	while(true)
	{
		if( m_lookahead == PLUS_SIGN || m_lookahead == MINUS_SIGN )
		{
			matchToken(m_lookahead);
			expression_term();
		}
		else
		{
			return;
		}
	}

}




void CAipi_Parser::expression_term()
{
	expression_factor();
	while(true)
	{
		if( m_lookahead == ASTERIC || m_lookahead == SLASH || m_lookahead == PERCENT )
		{
			matchToken(m_lookahead);
			expression_factor();
		}
		else
		{
			return;
		}
	}


}


void CAipi_Parser::expression_unary_plus()
{
	matchToken(PLUS_SIGN);
	expression_factor();
	
}


void CAipi_Parser::expression_unary_minus()
{
	matchToken(MINUS_SIGN);
	expression_factor();
	
}

void CAipi_Parser::expression_unary_increment()
{
		
	matchToken(INC_OP);
	//It just apply to identifiers
	if( m_lookahead == IDENTIFIER )
	{
		expression_factor();
		
	}	


}

void CAipi_Parser::expression_unary_decrement()
{
	matchToken(DEC_OP);
	//It just apply to identifiers
	if( m_lookahead = IDENTIFIER )
	{
		expression_factor();
	}
}


void CAipi_Parser::expression_factor()
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
		matchToken(LITERAL);
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


void CAipi_Parser::expression_atom_identifier()
{
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


void CAipi_Parser::expression_atom_constant()
{
	matchToken(DIGIT);

}

void CAipi_Parser::expression_atom_literal()
{
	matchToken(LITERAL);
}
	



















































































