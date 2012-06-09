// Aipi_ExpParserFileGlobal.cpp: implementation of the CAipi_ExpParserFileGlobal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_ExpParserFileGlobal.h"

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

CAipi_ExpParserFileGlobal::CAipi_ExpParserFileGlobal()
{
	//Data Base 
	m_bFlagConnDlg = false; //Database is needed
	
	g_iDBProvider = UNDEFINE;
	m_dbProvider = _T("");
	m_dbDNS = _T("");
	m_dbUser = _T("");
	m_dbPassword = _T("");
	m_dbName = _T("");

	g_bStopFlag = false; //Stop interpreter flag
	//g_currentParserClass = EXP_PARSER_FILE_GLOBAL;
	
}

CAipi_ExpParserFileGlobal::~CAipi_ExpParserFileGlobal()
{

}


////////////////////////////////////////////////////////////////////////////////////
//// SQL OleDB DataBase /////
///////////////////////////////////////////////////////////////////////////////////
int CAipi_ExpParserFileGlobal::SqlSelectDB(tstring db)
{
	if( db == _T("Ms_Access") || db == _T("MS_ACCESS") )
	{		
		g_iDBProvider = MS_ACCESS;
		return g_iDBProvider;
	}
	else if ( db == _T("Ms_SqlServer") || db == _T("MS_SQLSERVER") )
	{
		g_iDBProvider = MS_SQLSERVER;
		return g_iDBProvider;
	}
	else if ( m_dbProvider == _T("Ms_Oracle") || _T("MS_ORACLE") )
	{
		g_iDBProvider = MS_ORACLE;
		return g_iDBProvider;
	}
	else if( m_dbProvider == _T("Oracle") || _T("MS_ORACLE") )
	{
		g_iDBProvider = ORACLE;
		return g_iDBProvider;
	}
	else if( m_dbProvider == _T("MySql") || _T("MYSQL") )
	{
		g_iDBProvider = MYSQL;
		return g_iDBProvider;
	}
	else if( m_dbProvider == _T("db2") || _T("DB2")  )
	{
		g_iDBProvider = DB2;
		return g_iDBProvider;
	}
	else
	{
		g_iDBProvider = UNDEFINE;
		//WARNNING Provider incorrect not idnetifcated
		//CAipi_Error err;
		//err.displayGUIError();
		
	}

	
return g_iDBProvider;

}


void CAipi_ExpParserFileGlobal::SqlShowDBDlg()
{

	
	if( g_iDBProvider != UNDEFINE && m_dbName == _T("") && m_dbUser == _T("") && m_dbPassword == _T("") && m_dbDNS == _T("") )
	{
		SqlOpenConnectionDlg();
	}
	 
	else if ( g_iDBProvider == UNDEFINE && m_dbName == _T("") && m_dbUser == _T("") && m_dbPassword == _T("") && m_dbDNS == _T("") )
	{
		//If no provider is reconized then select MsAccess by default
		g_iDBProvider = MS_ACCESS;
		SqlOpenConnectionDlg();
	}
	else
	{

		//SqlOpenConnectionDlg();
		//AfxMessageBox(_T("OPEN OLE CTRL"));
		SqlOpenOleDB();
						
	}

}



void CAipi_ExpParserFileGlobal::SqlOpenConnectionDlg()
{
	//AfxMessageBox(_T("SqlOpen"));
	
	if( g_iDBProvider != UNDEFINE )
	{
			//AfxMessageBox(_T("Open Connection Dlg"));
		
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->m_wndOleDBDlg.OnOpenDatabaseConnection(g_iDBProvider);
		if ( !pMainFrame->m_wndOleDBDlg.IsVisible())
		{
			pMainFrame->ShowControlBar(&pMainFrame->m_wndOleDBDlg, !pMainFrame->m_wndOleDBDlg.IsVisible(), FALSE);	
	
		}
	}

}




void CAipi_ExpParserFileGlobal::SqlOpenOleDB()
{
	//AfxMessageBox(_T("OPEN DB"));
	if( g_iDBProvider != UNDEFINE )
	{
			//AfxMessageBox(_T("Open Connection Dlg"));
		
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->m_wndOleDBDlg.OnOpenDatabase(g_iDBProvider);
		if ( !pMainFrame->m_wndOleDBDlg.IsVisible())
		{
			pMainFrame->ShowControlBar(&pMainFrame->m_wndOleDBDlg, !pMainFrame->m_wndOleDBDlg.IsVisible(), FALSE);	
	
		}
	}


	/*
	if( g_iDBProvider != UNDEFINE )
	{

		COleDBConnectionProp	m_props;
		
	
		m_props.Connect(g_iDBProvider);
		m_props.m_strServerName = g_sDBDNS;
		m_props.m_strDSN = g_sDBDNS;
		m_props.m_strPassword = g_sDBPassword;
		m_props.m_strLoginName = g_sDBUser;
		m_props.m_strDatabaseName = g_sDBName;

		

		m_props.LoadSettings();
		m_props.SaveSettings();
		
			
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->ShowControlBar(&pMainFrame->m_wndOleDBDlg, !pMainFrame->m_wndOleDBDlg.IsVisible(), FALSE);
	}
	*/
	
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

CString CAipi_ExpParserFileGlobal::LiteralVarSearch(long iform )
{
	//Search global literal variables first
	CAipi_STableGlobalLiteral lit;
	int f = lit.findSTableLiteralMembers( iform);
	if( f == NOT_FOUND )
	{
			return _T("NOT_FOUND");
	}
	else
	{
		g_currentVarLoc  = VAR_GLOBAL;
		CString str = lit.m_STGLitValue.data();
		//AfxMessageBox(str);
		return str;
	}

return _T("NOT_FOUND");
	
}



double CAipi_ExpParserFileGlobal::NumericVarSearch(long iform)
{
	//Search global numeric variables first
	CAipi_STableGlobalNumeric num;
	double f = num.findSTableNumericMembers(iform);
	if( f == NOT_FOUND )
	{
		return NOT_FOUND;			
		
	}
	else
	{
		//AfxMessageBox(_T("Encontro Variable"));
		g_currentVarLoc  = VAR_GLOBAL;
		double val = num.m_STGNumValue;
		/*
		CString str;
		str.Format(_T("%f"), val);
		AfxMessageBox(str);
		*/
		return val;
	}

return NOT_FOUND;

}


int CAipi_ExpParserFileGlobal::matchToken(int tk )
{
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
		err.displayFileError(SINTAX, SINTAX_ERROR, _T(" Symbol " + strTK + " doesn't match. Expected symbol " + strSymbol + " was not found.") );
		return SINTAX_ERROR;
	}

	
	CAipi_Lexer lex;
	TCHAR symbol =  _gettc(g_fp);
	m_lookahead = lex.addTokenizerFile(symbol);
	m_sToken = lex.m_sToken;
	
	
	//AfxMessageBox(_T("ExpParserFileGlobal LEXER TOKEN......"));
	//AfxMessageBox(lex.m_sToken);
	

	if( m_lookahead == COMMENT )
	{
		do
		{
			TCHAR symbol =  _gettc(g_fp);
			m_lookahead = lex.addTokenizerFile(symbol);
			//str.Format(_T("COMMENT Look Ahead...%d  " ), m_lookahead);
			//AfxMessageBox(str);
		
		}while (m_lookahead == COMMENT && m_lookahead != _TEOF );
	}
		
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, g_fcurrentPos*100/m_fendPos);


	if( m_lookahead == _TEOF )
		return _TEOF;


	
	return P_SUCCESS;
}


void CAipi_ExpParserFileGlobal::emit_declaration(int tk)
{
	
	if ( tk == IDENTIFIER )
	{
		//AfxMessageBox(_T("EMIT DECLARATION IDENTIFIER"));

		CAipi_Tokenizer tkz;
		double id = tkz.v_lastIntFormToken();
		tstring tk = tkz.v_lastToken();
		//CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		//double id = pMainFrame->gvTokenizer[m_index-1].getIntForm();
		//string tk = pMainFrame->gvTokenizer[m_index-1].getToken();
		m_sCurrentId = tk;
		m_dCurrentId = id;
		/*
		AfxMessageBox(_T("TOKEN"));
		AfxMessageBox(tk.data());
		CString str;
		str.Format(_T("idSymbol...%f  " ), id);
		AfxMessageBox(str);
		*/	
		
		
		if( m_currentType == AIPI_STRING || m_currentType == AIPI_CHAR )
		{
			tstring sToken = (LPCTSTR)m_sToken;

			//Checking repeated identifiers declarations
			CAipi_STableGlobalLiteral lit;
			int found = lit.findSTableLiteralMembers(id);
			if( found == NOT_FOUND )
			{
				CAipi_STableGlobalLiteral lt;
				lt.addSymbol(id, sToken, m_currentType,  _T(""));
			}
			else
			{
				CAipi_Error er;
				CString strDesc = _T("Identifier [") + m_sToken + _T("] was already declare.");
				er.displayGUIError(DUP_VAR, SEMANT_ERROR, strDesc);
			}


		}
		else
		{
			tstring sToken = (LPCTSTR)m_sToken;
			//AfxMessageBox(m_sToken);
			//Checking repeated identifiers declarations
			CAipi_STableGlobalNumeric num;
			int found  = num.findSTableNumericMembers(id);
			/*
			CString str;
			str.Format(_T("idSymbol...%f  " ), id);
			AfxMessageBox(str);
			*/

			//Check if ID were previously declare
			if( found == NOT_FOUND )
			{
				//The ID was not previously declare
				CAipi_STableGlobalNumeric st;
				st.addSymbol(id, sToken, m_currentType,  0);
				
				//AfxMessageBox(_T("Add Numeric Table"));
				//AfxMessageBox(sToken.data());
			}
			else
			{
				//Check if identifier was used in a script definition
				CAipi_ScriptCode script;
				long idsearch = script.findId_Into_ScriptCode(id);
				if(idsearch != NOT_FOUND )
				{
					//The ID was used in a script definition, but was not previously declare
					CAipi_STableGlobalNumeric st;
					st.addSymbol(id, sToken, m_currentType,  0);
					//AfxMessageBox(_T("Add Numeric Table"));
					//AfxMessageBox(sToken.data());
				}
				else
				{
					CAipi_Error er;
					CString strDesc = _T("Identifier [") + m_sToken + _T("] was already declare.");
					er.displayGUIError(DUP_VAR, SEMANT_ERROR, strDesc);
					//AfxMessageBox(_T("ERROR"));
				}
			}
			
		}

		/*
		CString str;
		AfxMessageBox(m_sToken);
		str.Format(_T("ID...%d  " ), id);
		AfxMessageBox(str);
		str.Format(_T("Type...%d  " ), type);
		AfxMessageBox(str);
		*/
	
	}

	else if( tk == EQUAL )
	{
		//AfxMessageBox(_T("EMIT DECLARATION EQUAL"));
		/*
		CString str;
		str.Format(_T("Current Type...%d  " ), m_currentType);
		AfxMessageBox(str);
		*/	
		/*
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		long id = pMainFrame->gvTokenizer[m_index-4].getIntForm();
		string tk = pMainFrame->gvTokenizer[m_index-4].getToken();
		AfxMessageBox(tk.data());
		*/
		
		//AfxMessageBox(m_sCurrentId.data());
		long id = m_dCurrentId;
	
		
		if( m_currentType == AIPI_STRING || m_currentType == AIPI_CHAR)
		{
			if( !m_stackLiteral.empty() )
			{
				tstring value = m_stackLiteral.top();
				m_stackLiteral.pop();
				CAipi_STableGlobalLiteral lt;
				lt.editSTableLiteralValue(id, value);
			/*
				AfxMessageBox(_T("Value:"));
				AfxMessageBox(value.data());
				AfxMessageBox(m_sToken);
			*/	
			
			}
		}
		else
		{
			if( !m_stackNumeric.empty() )
			{
				//AfxMessageBox(_T("entro"));
				
				double value = m_stackNumeric.top();
				m_stackNumeric.pop();
				CAipi_STableGlobalNumeric st;
				st.editSTableNumericValue(id, value);
			
				/*
				CString str;
				str.Format(_T("TOP VALUE...%f  " ), value);
				AfxMessageBox(str);
				AfxMessageBox(m_sToken);
				*/
				
			}
		}
	}

	
	
}


void CAipi_ExpParserFileGlobal::emit_expression(int tk)
{
	CAipi_Lexer lex;

	if( tk == IDENTIFIER )
	{
		//AfxMessageBox(_T("EMIT GLOBAL IDENTIFIER"));
		
		CAipi_Tokenizer tkz;
		double iform = tkz.v_previousLastIntFormToken();
		tstring sId = tkz.v_previousLastToken();
		//CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		//tstring sId = pMainFrame->gvTokenizer[m_index-1].getToken();
		//long iform = pMainFrame->gvTokenizer[m_index-1].getIntForm();

		//AfxMessageBox(_T("TOKEN"));
		//AfxMessageBox(sId.data());
		/*
		CAipi_Symbol sym;
		long iform = sym.findId_IntForm(sId);
		*/
		/*
		CString str;
		str.Format(_T("ID...%d  " ), iform);
		AfxMessageBox(str);
		*/
			
			//AfxMessageBox(_T("FOUND"));
			CAipi_STableGlobalNumeric num;
			double f = num.findSTableNumericMembers(iform);
			if( f != NOT_FOUND )
			{
				//AfxMessageBox(_T("PUSH DIGIT"));
				m_stackNumeric.push(num.m_STNumValue);
				m_currentType = num.m_STGNumType;
			}
			else
			{
				CAipi_STableGlobalLiteral lit;
				int f = lit.findSTableLiteralMembers( iform);
				if( f != NOT_FOUND )
				{
					//AfxMessageBox(_T("PUSH LITERAL"));
					m_stackLiteral.push(lit.m_STLitValue);
					m_currentType = lit.m_STGLitType;
				}
				else
				{					
					CAipi_Error err;
					CString  strId = sId.data();
					CString  strDesc = _T("No type was found for global identifier [") + strId + _T("]."); 
					err.displayGUIError(UNKNOW_TYPE, SEMANT_ERROR, strDesc);
				}
			}	
		
		
	
	}
	
	else if( tk == LITERAL )
	{
		//AfxMessageBox(_T("EMIT LITERAL"));
		m_sToken.TrimLeft('"');
		m_sToken.TrimRight('"');
		m_stackLiteral.push((LPCTSTR)m_sToken);
		//AfxMessageBox(m_sToken);
	}

	else if( tk == DIGIT )
	{
		//AfxMessageBox(_T("EMIT DIGIT"));
		//AfxMessageBox(m_sToken);
		double tk = _tcstod(m_sToken, NULL);
		m_stackNumeric.push(tk);
		/*
		CString str;
		str.Format(_T("Number...%f  " ), tk);
		AfxMessageBox(str);
		*/
	}

	//Assignation
	else if( tk == EQUAL )
	{
		//AfxMessageBox(_T("EMIT EQUAL"));
		/*
		CString str;
		str.Format(_T("Current Type...%d  " ), m_currentType);
		AfxMessageBox(str);
		AfxMessageBox(m_sCurrentId.data());
		*/
		double id = m_dCurrentId;

		/*
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		long id = pMainFrame->gvTokenizer[m_index-4].getIntForm();
		string tk = pMainFrame->gvTokenizer[m_index-4].getToken();
		AfxMessageBox(tk.data());
		*/
		/*
		CAipi_Symbol sym;
		long iform = sym.findId_IntForm(tk);
		if( iform != NOT_FOUND )
		{
			id = iform;
		}
		*/
		
		if( m_currentType == AIPI_STRING || m_currentType == AIPI_CHAR )
		{
			if( !m_stackLiteral.empty() )
			{
				tstring value = m_stackLiteral.top();
				m_stackLiteral.pop();
				CAipi_STableLocalLiteral lt;
				lt.editSTableLiteralValue(id, value);
			
				/*
				AfxMessageBox(value.data());
				AfxMessageBox(m_sToken);
				*/
			
			}
		}
		else
		{
			if( !m_stackNumeric.empty() )
			{
				double value = m_stackNumeric.top();
				m_stackNumeric.pop();
				CAipi_STableGlobalNumeric st;
				st.editSTableNumericValue(id, value);
			
				/*
				CString str;
				str.Format(_T("TOP...%f  " ), result);
				AfxMessageBox(str);
				AfxMessageBox(m_sToken);
				*/
			}
		}
	}

	
	//Add operation 
	else if( tk == PLUS_SIGN )
	{
		//AfxMessageBox(_T("SIGNO MAS"));
		/*
		CString str;
		str.Format(_T("Current Type...%d  " ), m_currentType);
		AfxMessageBox(str);
		*/
		
		if(		m_currentType == AIPI_INT
			||	m_currentType == AIPI_LONG 
			|| 	m_currentType == AIPI_SHORT
			||	m_currentType == AIPI_FLOAT 
			||  m_currentType == AIPI_DOUBLE 
		  )
		{
			double left_op = 0;
			double right_op = 0;
			double result = 0;

			if( !m_stackNumeric.empty() )
			{
				//AfxMessageBox(_T("EMIT SUMA"));
				//AfxMessageBox(m_sToken);
		
				right_op = m_stackNumeric.top();
				m_stackNumeric.pop();
				left_op = m_stackNumeric.top();
				m_stackNumeric.pop();
				result = left_op + right_op;

				m_stackNumeric.push(result);
				/*
				CString str;
				str.Format(_T("Result...%f  " ), result);
				AfxMessageBox(str);
				*/
			}

		}
		else if( m_currentType == AIPI_STRING || m_currentType == AIPI_CHAR )
		{
			tstring left_op = _T("");
			tstring right_op = _T("");
			tstring result = _T("");

			if( !m_stackLiteral.empty() )
			{
				//AfxMessageBox(_T("EMIT SUMA CADENAS"));
				//AfxMessageBox(m_sToken);
		
				right_op = m_stackLiteral.top();
				m_stackLiteral.pop();
				left_op = m_stackLiteral.top();
				m_stackLiteral.pop();
				result = left_op + right_op;

				m_stackLiteral.push(result);
				//AfxMessageBox(result.data());
			
			}

		}
		else
		{
			return;
		}
		
	}
	else if( tk == MINUS_SIGN )
	{
		//AfxMessageBox(_T("EMIT RESTA"));
		//AfxMessageBox(m_sToken);
		
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			result = left_op - right_op;

			m_stackNumeric.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}
	
	else if( tk == ASTERIC )
	{
		//AfxMessageBox(_T("EMIT MULTIPLICATION"));
		//AfxMessageBox(m_sToken);
		
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			result = left_op * right_op;

			m_stackNumeric.push(result);
			
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	else if( tk == SLASH )
	{
		//AfxMessageBox(_T("EMIT DIVISION"));
		//AfxMessageBox(m_sToken);
		
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			result = left_op / right_op;

			m_stackNumeric.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	else if( tk == PERCENT )
	{
		//AfxMessageBox(_T("EMIT MOD"));
		//AfxMessageBox(m_sToken);
		
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			result = (int)left_op % (int)right_op;

			m_stackNumeric.push(result);
			
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}

	}

	else if( tk == UNARY_MINUS )
	{
		//AfxMessageBox(_T("ADD UNARY MINUS"));
		m_stackNumeric.push(-1);
	}

	else if ( tk == UNARY_PLUS )
	{
		//AfxMessageBox(_T("ADD UNARY PLUS"));
		m_stackNumeric.push(1);
	}

	else if( tk == UNARY_OP )
	{
		//AfxMessageBox(_T("EMIT UNARY"));
		
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			result = left_op * right_op;

			m_stackNumeric.push(result);
			
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}

	
	}

	else if( tk == INC_OP )
	{
		//AfxMessageBox(_T("EMIT INC OP"));
		
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			result = m_stackNumeric.top();
			m_stackNumeric.pop();
			++result;

			m_stackNumeric.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
		}
	
	}

	else if( tk == DEC_OP )
	{
		//AfxMessageBox(_T("EMIT DEC OP"));
		
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			result = m_stackNumeric.top();
			m_stackNumeric.pop();
			--result;

			m_stackNumeric.push(result);
			
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	else if( tk == LT )
	{
		//AfxMessageBox(_T("EMIT LESS THAN"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			
			if( left_op < right_op )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stackNumeric.push(result);
			
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	else if( tk == GT )
	{
		//AfxMessageBox(_T("EMIT GREATER THAN"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			
			if( left_op > right_op )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stackNumeric.push(result);
			
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
		}
	}

	else if( tk == LE )
	{
		//AfxMessageBox(_T("EMIT LESS-EQUAL THAN"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			
			if( left_op <= right_op )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stackNumeric.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	else if( tk == GE )
	{
		//AfxMessageBox(_T("EMIT GREATER-EQUAL THAN"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			
			if( left_op >= right_op )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stackNumeric.push(result);
			
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	else if( tk == ET )
	{
		//AfxMessageBox(_T("EMIT EQUAL THAN"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			
			if( left_op == right_op )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stackNumeric.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}
	
	else if( tk == NE )
	{
		//AfxMessageBox(_T("EMIT NO-EQUAL THAN"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			
			if( left_op != right_op )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stackNumeric.push(result);
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	else if( tk == AND_OP )
	{
		//AfxMessageBox(_T("EMIT AND"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			
			if( left_op == 1 && right_op == 1 )
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			
			m_stackNumeric.push(result);
			
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}

	else if( tk == OR_OP )
	{
		//AfxMessageBox(_T("EMIT OR"));
		//AfxMessageBox(m_sToken);
				
		double left_op = 0;
		double right_op = 0;
		double result = 0;

		if( !m_stackNumeric.empty() )
		{
			
			right_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			left_op = m_stackNumeric.top();
			m_stackNumeric.pop();
			
			if( left_op == 0 && right_op == 0 )
			{
				result = 0;
			}
			else
			{
				result = 1;
			}
			
			m_stackNumeric.push(result);
			
			/*
			CString str;
			str.Format(_T("Result...%f  " ), result);
			AfxMessageBox(str);
			*/
			
		}
	}
	else
	{
		//Nothing
	}

	/*
	int size = m_stackNumeric.size();
	CString str;
	str.Format(_T("Size...%d"  ), size);
	AfxMessageBox(str);
	*/

}




////////////////////////////////////////////////////////////////////////
//// Expression parser ////
//////////////////////////////////////////////////////////////////////////

void CAipi_ExpParserFileGlobal::initExpParserFileGlobal()
{
	m_fendPos = g_currentDocEndPos;
	
	//AfxMessageBox(_T("****Entro EXP PARSER FILE GLOBAL ****"));
	
	translation_unit();
	//AfxMessageBox(_T("****Salio EXP PARSER FILE GLOBAL ****"));
	
}

////////////////////////////////////////////////

			/// PARSER ////

///////////////////////////////////////////////

void CAipi_ExpParserFileGlobal::translation_unit()
{
	
	g_currentParserClass = EXP_PARSER_FILE_GLOBAL;
	if( m_lookahead != _TEOF )
	{
		if( m_lookahead == COMMENT )
		{
			matchToken(COMMENT);
			translation_unit();
		}
		
		if(		m_lookahead == AIPI_VOID 
			||	m_lookahead == AIPI_CHAR
			||	m_lookahead == AIPI_SHORT
			||	m_lookahead == AIPI_INT
			||	m_lookahead == AIPI_LONG
			||	m_lookahead == AIPI_FLOAT
			||	m_lookahead == AIPI_DOUBLE
			||	m_lookahead == AIPI_STRING

		  )	
		{
			
			//AfxMessageBox(_T("Entro Declaration File Global"));
			declaration();
			translation_unit();
		}
		else if (		m_lookahead == IDENTIFIER
					||	m_lookahead == DIGIT
				)
		{
			//AfxMessageBox(_T("Entro a Expression File Global"));
			expression();
			translation_unit();
		}
		else if( m_lookahead == AIPI_OUTPUT )
		{
			AfxMessageBox(_T("Global OUTPUT"));
			cmd_output();
			translation_unit();
		}
		else if( m_lookahead == AIPI_INPUT )
		{
			int r = cmd_input();
			
			if( r == AIPI_STOP )
			{
				g_bStopFlag = true;
				return;
			}
			translation_unit();
		}
		else if( m_lookahead == AIPI_DISPLAYCTRL )
		{
			AfxMessageBox(_T("GET IN Gobal de DisplayCtrl"));
			int r = UNDEFINE;
			matchToken(AIPI_DISPLAYCTRL);
			switch( m_lookahead)
			{
			case AIPI_CTRL_MEDIAPLAYER :
				ctrl_mediaplayer();
				break;
			case AIPI_CTRL_JUKEBOX:
				ctrl_jukebox();
				break;
			case AIPI_CTRL_IMAGEFILTER:
				ctrl_imagefilter();
				break;
			case AIPI_CTRL_LISTOPTION:
				r = ctrl_listoption();
				if( r == AIPI_STOP )
				{
					g_bStopFlag = true;
					return;
				}
				break;
			case AIPI_CTRL_OLEDB:
				ctrl_oledb();
				break;
			}
			//AfxMessageBox(_T("EXIT de DisplayCtrl"));
			translation_unit();
		
		}
		else if( m_lookahead == AIPI_DB_OPEN )
		{
			//AfxMessageBox(_T("Entro a OPEN DB GUI Global"));
			cmd_db_open();
			translation_unit();
		}
		
		/*
		else if (		m_lookahead == AIPI_ASSERT 
					||	m_lookahead == AIPI_CLASS
					||	m_lookahead == JS_FUNCTION
					||	m_lookahead == VBS_FUNCTION
					||	m_lookahead == AIPI_RULE
				)
		{
			AfxMessageBox(_T("Sale de ExpParserFileGlobal"));
			CAipi_ParserFile file;
			file.m_lookahead = m_lookahead;
			file.translation_unit();
		}*/
		else
		{
			if( g_bExecuteFlag )
			{
				AfxMessageBox(_T("flag EXEC"));

				CAipi_Main main;
				g_currentLookahead = m_lookahead;
				main.execute_continue();

			}
			else
			{
				AfxMessageBox(_T("FILE Parser"));
				CAipi_ParserFile file;
				file.m_lookahead = m_lookahead;
				file.translation_unit();
				file.endParser();
			}
			
			//AfxMessageBox(_T("Sale de ExpParserFileGlobal"));
			//CAipi_Error err;
			//err.displayFileError(ABNORMAL_STOP, WARNING_ERROR, _T("The parser was not able to finish the depuration process. The initialization sintax is incorrect.") );
			
			
		}
	}
	else
	{
		/*
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
		*/

	}
	

}




//////////////////////////////////////////////////////////////////////////////////////////////////
/// Declaration Parser ////
//////////////////////////////////////////////////////////////////////////////////////////////////

void CAipi_ExpParserFileGlobal::declaration_specifiers()
{
	
	if(		m_lookahead == AIPI_VOID 
		||	m_lookahead == AIPI_CHAR
		||	m_lookahead == AIPI_SHORT
		||	m_lookahead == AIPI_INT
		||	m_lookahead == AIPI_LONG
		||	m_lookahead == AIPI_FLOAT
		||	m_lookahead == AIPI_DOUBLE
		||  m_lookahead == AIPI_STRING
	  )
	{
		m_currentType = m_lookahead;
		matchToken(m_lookahead);
		declaration_specifiers();
		
	}
	
}


void CAipi_ExpParserFileGlobal::declaration()
{
	/*
	CString str;
	str.Format(_T("Global DEclaration Look Ahead...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	
	declaration_specifiers();
	
	if( m_lookahead == SEMICOLON)
	{
		matchToken(SEMICOLON);
		return;
	}
	
	declarator_list_init();
	matchToken(SEMICOLON);	
	
	
	
	
}



void CAipi_ExpParserFileGlobal::declarator_list_init()
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

void CAipi_ExpParserFileGlobal::declarator_init()
{
	declarator_direct();
	
	if( m_lookahead == EQUAL )
	{
		matchToken(EQUAL);
		initializer();
		emit_declaration(EQUAL);
		
	}

}




void CAipi_ExpParserFileGlobal::initializer()
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

void CAipi_ExpParserFileGlobal::initializer_list()
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




void CAipi_ExpParserFileGlobal::declarator_direct()
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
			if(		m_lookahead == AIPI_VOID 
				||	m_lookahead == AIPI_CHAR
				||	m_lookahead == AIPI_SHORT
				||	m_lookahead == AIPI_INT
				||	m_lookahead == AIPI_LONG
				||	m_lookahead == AIPI_FLOAT
				||	m_lookahead == AIPI_DOUBLE
				||	m_lookahead == AIPI_STRING
				 
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




void CAipi_ExpParserFileGlobal::parameter_declaration()
{
	
	
	declaration_specifiers();
	
	if( m_lookahead == IDENTIFIER || m_lookahead == OPEN_PARENTHESIS || m_lookahead == OPEN_BRACKET)
	{
		declarator_direct();
	}
	
}



void CAipi_ExpParserFileGlobal::parameter_list()
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
void CAipi_ExpParserFileGlobal::expression_argument_list()
{
	expression_assignment();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			expression_assignment();
		}
	}

}


void CAipi_ExpParserFileGlobal::expression()
{
	
	expression_assignment();
	expression_logical_or();
}


void CAipi_ExpParserFileGlobal::expression_assignment()
{
	if( m_lookahead == EQUAL)
	{
		matchToken(EQUAL);
		expression_logical_or();
	}
	
	expression_logical_or();	
	
			
}


void CAipi_ExpParserFileGlobal::expression_logical_or()
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


void CAipi_ExpParserFileGlobal::expression_logical_and()
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

void CAipi_ExpParserFileGlobal::expression_equality()
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


void CAipi_ExpParserFileGlobal::expression_relational()
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



void CAipi_ExpParserFileGlobal::expression_aritmetic()
{
	expression_term();
		
	while(true)
	{
		if( m_lookahead == PLUS_SIGN || m_lookahead == MINUS_SIGN )
		{
			int tk = m_lookahead;
			matchToken(tk);
			expression_term();
			emit_expression(tk);
			
		}
		else
		{
			return;
		}
	}

}


void CAipi_ExpParserFileGlobal::expression_term()
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


void CAipi_ExpParserFileGlobal::expression_unary_plus()
{
	//AfxMessageBox(_T("CASE UNARY"));
	emit_expression(UNARY_PLUS);
	matchToken(PLUS_SIGN);
	expression_factor();
	emit_expression(UNARY_OP);
}


void CAipi_ExpParserFileGlobal::expression_unary_minus()
{
	//AfxMessageBox(_T("UNARY MINUS"));
	emit_expression(UNARY_MINUS);
	matchToken(MINUS_SIGN);
	expression_factor();
	emit_expression(UNARY_OP);
}

void CAipi_ExpParserFileGlobal::expression_unary_increment()
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

void CAipi_ExpParserFileGlobal::expression_unary_decrement()
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



void CAipi_ExpParserFileGlobal::expression_factor()
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





void CAipi_ExpParserFileGlobal::expression_atom_identifier()
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
	//Detect function call
	if( m_lookahead == OPEN_PARENTHESIS )
	{
		matchToken(OPEN_PARENTHESIS);
		expression_argument_list();
		matchToken(CLOSE_PARENTHESIS);
	}

}


void CAipi_ExpParserFileGlobal::expression_atom_constant()
{
	emit_expression(DIGIT);
	matchToken(DIGIT);

}

void CAipi_ExpParserFileGlobal::expression_atom_literal()
{
	emit_expression(LITERAL);
	matchToken(LITERAL);
}
		



void CAipi_ExpParserFileGlobal::type_name()
{
	
	switch(m_lookahead)
	{
	case AIPI_CHAR:
		emit_expression(AIPI_CHAR);
		break;
	case AIPI_SHORT:
		emit_expression(AIPI_SHORT);
		break;
	case AIPI_INT:
		emit_expression(AIPI_INT);
		break;
	case AIPI_LONG:
		emit_expression(AIPI_LONG);
		break;
	case AIPI_FLOAT:
		emit_expression(AIPI_FLOAT);
		break;
	case AIPI_DOUBLE:
		emit_expression(AIPI_DOUBLE);
		break;
	}

}


void CAipi_ExpParserFileGlobal::operator_unary()
{
	switch(m_lookahead)
	{
	case PLUS_SIGN:
		emit_expression(PLUS_SIGN);
		break;
	case MINUS_SIGN:
		emit_expression(MINUS_SIGN);
		break;
	
	}

}

void CAipi_ExpParserFileGlobal::operator_assigment()
{
	switch(m_lookahead)
	{
	case EQUAL:
		emit_expression(EQUAL);
		break;
	case MUL_ASSIGN:
		emit_expression(MUL_ASSIGN);
		break;
	case DIV_ASSIGN:
		emit_expression(DIV_ASSIGN);
		break;
	case ADD_ASSIGN:
		emit_expression(ADD_ASSIGN);
		break;
	case SUB_ASSIGN:
		emit_expression(SUB_ASSIGN);
		break;
	
	
	}

}

//////////////////////////////////////////////////////////////////////////
//// AIPI Commands ////
////////////////////////////////////////////////////////////////////////////

void CAipi_ExpParserFileGlobal::cmd_db_open()
{
	matchToken(AIPI_DB_OPEN);
	matchToken(OPEN_PARENTHESIS);
	cmd_db_open_parameter_list();
	matchToken(CLOSE_PARENTHESIS);
	matchToken(SEMICOLON);

	m_bFlagConnDlg = true;
}


void CAipi_ExpParserFileGlobal::cmd_db_open_parameter()
{
	
	CAipi_Tokenizer tkz;
	CString sProvider = _T("");

	switch( m_lookahead )
	{
	case AIPI_DB_DNS:
		matchToken(AIPI_DB_DNS);
		matchToken(EQUAL);
				
		if( m_lookahead == LITERAL )
		{
			m_dbDNS = tkz.v_lastToken();
			g_sDBDNS = m_dbDNS.data();
			//AfxMessageBox(_T("DB_DNS"));
			//AfxMessageBox(m_dbDNS.data());
			g_sDBDNS = m_dbDNS.data();
		
			matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			long dns = tkz.v_lastIntFormToken();
			CAipi_STableGlobalLiteral lit;
			m_dbDNS = lit.findIdValue(dns);
			//AfxMessageBox(_T("DB_DNS"));
			//AfxMessageBox(m_dbDNS.data());
			if( m_dbDNS != _T("NOT_FOUND") )
			{
				g_sDBDNS = m_dbDNS.data();
				
			}
			else
			{
				CAipi_Error er;
				CString strDesc = _T("Identifier [") + m_sToken + _T("] was not found.");
				er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
			}
			matchToken(IDENTIFIER);
		}
		break;
	case AIPI_DB_USER:
		matchToken(AIPI_DB_USER);
		matchToken(EQUAL);
		
		if( m_lookahead == LITERAL )
		{
			m_dbUser = tkz.v_lastToken();
			g_sDBUser = m_dbUser.data();
			//AfxMessageBox(_T("DB_USER"));
			//AfxMessageBox(m_dbUser.data());
			
			g_sDBUser = m_dbUser.data();
		
			matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			long user = tkz.v_lastIntFormToken();
			CAipi_STableGlobalLiteral lit;
			m_dbUser = lit.findIdValue(user);
			//AfxMessageBox(_T("DB_USER"));
			//AfxMessageBox(m_dbUser.data());
			if( m_dbUser != _T("NOT_FOUND") )
			{
				g_sDBUser = m_dbUser.data();
				
			}
			else
			{
				CAipi_Error er;
				CString strDesc = _T("Identifier [") + m_sToken + _T("] was not found.");
				er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
			}
			matchToken(IDENTIFIER);
		}
		break;
	case AIPI_DB_PASSWORD:
		matchToken(AIPI_DB_PASSWORD);
		matchToken(EQUAL);
		
		if( m_lookahead == LITERAL )
		{
			m_dbPassword = tkz.v_lastToken();
			g_sDBPassword = m_dbPassword.data();
			//AfxMessageBox(_T("DB_PASSWORD"));
			//AfxMessageBox(m_dbPassword.data());
			
			g_sDBPassword = m_dbPassword.data();
		
			matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			long password = tkz.v_lastIntFormToken();
			CAipi_STableGlobalLiteral lit;
			m_dbPassword = lit.findIdValue(password);
			//AfxMessageBox(_T("DB_PASSWORD"));
			//AfxMessageBox(m_dbPassword.data());
			if( m_dbPassword != _T("NOT_FOUND") )
			{
				g_sDBPassword = m_dbPassword.data();
				
			}
			else
			{
				CAipi_Error er;
				CString strDesc = _T("Identifier [") + m_sToken + _T("] was not found.");
				er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
			}
			matchToken(IDENTIFIER);
		}
		break;
	case AIPI_DB_NAME:
		matchToken(AIPI_DB_NAME);
		matchToken(EQUAL);
		if( m_lookahead == LITERAL )
		{
			m_dbName = tkz.v_lastToken();
			g_sDBName = m_dbName.data();
			//AfxMessageBox(_T("DB_NAME"));
			//AfxMessageBox(m_dbName.data());
					
			matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			long name = tkz.v_lastIntFormToken();
			CAipi_STableGlobalLiteral lit;
			m_dbName = lit.findIdValue(name);
			//AfxMessageBox(_T("DB_NAME"));
			//AfxMessageBox(m_dbName.data());
			if( m_dbName != _T("NOT_FOUND") )
			{
				g_sDBName = m_dbName.data();
				
			}
			else
			{
				CAipi_Error er;
				CString strDesc = _T("Identifier [") + m_sToken + _T("] was not found.");
				er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
			}
			matchToken(IDENTIFIER);
		}
		break;
	case AIPI_DB_PROVIDER:
		matchToken(AIPI_DB_PROVIDER);
		matchToken(EQUAL);
				
		if( m_lookahead == LITERAL )
		{
			m_dbProvider = tkz.v_lastToken();
			g_iDBProvider = SqlSelectDB(m_dbProvider);
			//AfxMessageBox(_T("DB_PROVIDER"));
			//AfxMessageBox(m_dbProvider.data());
			
			matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			long provider = tkz.v_lastIntFormToken();
			CAipi_STableGlobalLiteral lit;
			m_dbProvider = lit.findIdValue(provider);
			//AfxMessageBox(_T("DB_PROVIDER"));
			//AfxMessageBox(m_dbProvider.data());
			if( m_dbProvider != _T("NOT_FOUND") )
			{
				g_iDBProvider = SqlSelectDB(m_dbProvider);					
			}
			else
			{
				CAipi_Error er;
				CString strDesc = _T("Identifier [") + m_sToken + _T("] was not found.");
				er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
			}
			matchToken(IDENTIFIER);
		}
		break;
    
	}
		


}


void CAipi_ExpParserFileGlobal::cmd_db_open_parameter_list()
{
	cmd_db_open_parameter();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			cmd_db_open_parameter();
		}
	}


}

void CAipi_ExpParserFileGlobal::cmd_db_close()
{
	matchToken(AIPI_DB_CLOSE);

}



void CAipi_ExpParserFileGlobal::cmd_output()
{
	CString currentDocView = _T("");
	CAipi_Tokenizer tkz;
	//AfxMessageBox(_T("ENTRO FILE GLOBAL OUTPUT"));
	matchToken(AIPI_OUTPUT);
	
	
	if ( m_lookahead == LEFT_OP )
	{
		while( m_lookahead != SEMICOLON && m_lookahead != _TEOF)
		{
			matchToken(LEFT_OP);
			//getTokenizer();
					
			if( m_lookahead == LITERAL )
			{
				
				long if_lit = tkz.v_lastIntFormToken();
				tstring s_lit = tkz.v_lastToken();
				CString strLit = s_lit.data(); 
				
				matchToken(LITERAL);
				
				//AfxMessageBox(_T("Antes de escribir"));
	
				CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
				CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
				CRichEditView* pView = (CRichEditView*) pChild->GetActiveView();
				ASSERT(pView);
				//Set output to current document
				pView->GetRichEditCtrl().GetWindowText(currentDocView);
				currentDocView = currentDocView + _T("\r\n") + strLit;
				pView->GetRichEditCtrl().SetWindowText(currentDocView);
				
				//matchToken(LITERAL);
				
				
			}
			else if( m_lookahead == IDENTIFIER )
			{
				long if_ident = tkz.v_lastIntFormToken();
				tstring s_ident = tkz.v_lastToken();
				CString strToken = s_ident.data();
				//AfxMessageBox(_T("OUTPUT ID.............................VAR"));
				//CString str;
				//str.Format(_T("ID IFORM...%d  " ), if_ident);
				//AfxMessageBox(str);
				//AfxMessageBox(strToken);
				
				//Search in global variables
				double dId =  NumericVarSearch(if_ident);
				
				if( dId == NOT_FOUND )
				{
					CString strLit = LiteralVarSearch( if_ident);
					if( strLit != _T("NOT_FOUND") )
					{
						CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
						CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
						CRichEditView* pView = (CRichEditView*) pChild->GetActiveView();
						ASSERT(pView);
						//Set output to current document
						pView->GetRichEditCtrl().GetWindowText(currentDocView);
						currentDocView = currentDocView + _T("\r\n") + strLit;
						pView->GetRichEditCtrl().SetWindowText(currentDocView);
	
	
					}
					else
					{
						CAipi_Error er;
						CString strDesc = _T("Identifier [") + strToken + _T("] was not found.");
						er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
					}
				}
				else
				{
					
					CString strNum;
					strNum.Format(_T("%f"), dId);
					
					CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
					CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
					CRichEditView* pView = (CRichEditView*) pChild->GetActiveView();
					ASSERT(pView);
					//Set output to current document
					pView->GetRichEditCtrl().GetWindowText(currentDocView);
					currentDocView = currentDocView + _T("\r\n") + strNum;
					pView->GetRichEditCtrl().SetWindowText(currentDocView);
	
				}

				matchToken(IDENTIFIER);
				
			}
			else if( m_lookahead == _TEOF )
			{
				return;
			}
			else
			{
				break;
			}

		}

		matchToken(SEMICOLON);
	
	}

	//AfxMessageBox(_T("SALIO FILE GLOBAL OUTPUT"));


}

int CAipi_ExpParserFileGlobal::cmd_input()
{
	//AfxMessageBox(_T("ENTRO FILE GLOBAL INPUT"));
	
	CAipi_Tokenizer tkz;

	matchToken(AIPI_INPUT);
	//getTokenizer();
	
	if ( m_lookahead == RIGHT_OP )
	{
		while( m_lookahead != SEMICOLON && m_lookahead != _TEOF)
		{
			//getTokenizer();
			matchToken(RIGHT_OP);
			
			if( m_lookahead == IDENTIFIER )
			{
				long if_ident = tkz.v_lastIntFormToken();
				tstring s_ident = tkz.v_lastToken();
				long pos = tkz.v_lastPosition();
				CString strToken = s_ident.data();
				
				/*
				AfxMessageBox(_T("INPUT ID.............................VAR"));
				CString str;
				str.Format(_T("ID IFORM...%d  " ), if_ident);
				AfxMessageBox(str);
				AfxMessageBox(strToken);
				*/
				//Search in numeric variables
				double dId =  NumericVarSearch(if_ident);
				
				if( dId == NOT_FOUND )
				{
					//Search in literal variables
					CString strLit = LiteralVarSearch( if_ident);
					if( strLit != _T("NOT_FOUND") )
					{
						CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
						pMainFrame->Cmd_OpenCommandDlgBar();
						g_currentDataCateg = LITERAL;
						g_currentId_IForm = if_ident;
						g_currentLookahead = m_lookahead;
						g_fcurrentPos = pos;

						return AIPI_STOP;
						
					}
					else
					{
						CAipi_Error er;
						CString strDesc = _T("Identifier [") + strToken + _T("] was not found.");
						er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
					}
				}
				else
				{
					//AfxMessageBox(_T("Abre CmdDlg"));
					
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->Cmd_OpenCommandDlgBar();
					g_currentDataCateg = DIGIT;
					g_currentId_IForm = if_ident;
					g_currentLookahead = m_lookahead;
					g_fcurrentPos = pos;


					return AIPI_STOP;
					
				}
				
				
				//getTokenizer();
				matchToken(IDENTIFIER);
			}
			else if( m_lookahead == _TEOF )
			{
				return _TEOF;
			}
			else
			{
				break;
			}

		}

		matchToken(SEMICOLON);
	
	}

	//AfxMessageBox(_T("SALIO FILE GLOBAL INPUT"));

return P_SUCCESS;

}


void CAipi_ExpParserFileGlobal::cmd_input_continue()
{
	/*
	AfxMessageBox(_T("Input Val"));
	AfxMessageBox(g_currentCmdInput);
	CString s;
	s.Format(_T("Data Categ...%d  " ), g_currentDataCateg);
	AfxMessageBox(s);
	*/			


	if(g_currentDataCateg == LITERAL )
	{
		m_sCurrentId = g_currentCmdInput;
		CAipi_STableGlobalLiteral lt;
		lt.editSTableLiteralValue(g_currentId_IForm, m_sCurrentId);
		lt.printSTableLiteral();
	}
	if( g_currentDataCateg == DIGIT )
	{
		//AfxMessageBox(_T("DIGIT"));
		m_dCurrentId = _tcstod(g_currentCmdInput, NULL); 
		CAipi_STableGlobalNumeric nt;
		nt.editSTableNumericValue(g_currentId_IForm, m_dCurrentId);
		nt.printSTableNumeric();
	}

	m_lookahead = g_currentLookahead;
	if( m_lookahead == _TEOF )
	{
		return;
	}
	/*
	CString str;
	str.Format(_T("Look Ahead...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/
	matchToken(IDENTIFIER);
	matchToken(SEMICOLON);


	
	translation_unit();

	if( g_bStopFlag != true )
	{
		fclose(g_fp);
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	}


}



void CAipi_ExpParserFileGlobal::ctrl_jukebox()
{
	//AfxMessageBox(_T("ENTRO JUKEBOXDLG"));
	bool bPlayVideo = false;
	bool bShowWnd = false;
	bool bInput = false;
	bool bPath = false;
	CString szPath = _T("");

	matchToken(AIPI_CTRL_JUKEBOX);
	matchToken(OPEN_PARENTHESIS);
	
	while( m_lookahead != CLOSE_PARENTHESIS && m_lookahead != NUL )
	{
		
		if (	m_lookahead == AIPI_SHOWCTRL 
			||	m_lookahead == AIPI_PLAY
			||  m_lookahead == AIPI_INPUTVAR
			||  m_lookahead == AIPI_PATH
		   )
		{
			
			if(m_lookahead == AIPI_SHOWCTRL )
			{
				matchToken(AIPI_SHOWCTRL);
				matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					matchToken(AIPI_TRUE);
					bShowWnd = true;

					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					matchToken(AIPI_FALSE);
					bShowWnd = false;
					
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
				}
			}
			else if( m_lookahead == AIPI_PLAY )
			{
				matchToken(AIPI_PLAY);
				matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					matchToken(AIPI_TRUE);
					bPlayVideo = true;
					
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					matchToken(AIPI_FALSE);

					bPlayVideo = false;
					
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
				}
				
			}
			else if( m_lookahead == AIPI_INPUTVAR )
			{
				matchToken(AIPI_INPUTVAR);
				matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					matchToken(AIPI_TRUE);
					bInput = true;
					
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					matchToken(AIPI_FALSE);
					bInput = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
				}
				
			}
			else if( m_lookahead == AIPI_PATH )
			{
				matchToken(AIPI_PATH);
				matchToken(EQUAL);

				CAipi_Tokenizer tkz;
				tstring strPath = tkz.v_lastToken();
				szPath = strPath.data();
				
				if( szPath != _T("") )
				{
					bPath = true;
				}
				matchToken(LITERAL);
				if( m_lookahead != CLOSE_PARENTHESIS )
				{
					matchToken(COMMA);
					
				}
			}
		}
		else
		{
			break;
		}
		
		
	}

	matchToken(CLOSE_PARENTHESIS);
	matchToken(SEMICOLON);

	if( bShowWnd )
	{
		//AfxMessageBox(_T("LOOK CTRL"));
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->Cmd_OpenJukeBoxDlg();
		
		if( bPath )
		{
			pMainFrame->Cmd_PathJukeBoxDlg(szPath);
			
			if( bPlayVideo )
			{
				pMainFrame->Cmd_PlayJukeBoxDlg();
				//AfxMessageBox(_T("PLAY CTRL"));

				if( bInput)
				{
					pMainFrame->Cmd_OpenCommandDlgBar();
				}
			}
		}


	}
	else
	{
		//AfxMessageBox(_T("CLOSE CTRL"));
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->Cmd_CloseJukeBoxDlg();
	}		


}

void CAipi_ExpParserFileGlobal::ctrl_mediaplayer()
{
	//AfxMessageBox(_T("ENTRO MEDIAPLAYERDLG"));
	
	bool bPlayVideo = false;
	bool bShowWnd = false;
	bool bInput = false;
	bool bPath = false;
	CString szPath = _T("");
	
	matchToken(AIPI_CTRL_MEDIAPLAYER);
	matchToken(OPEN_PARENTHESIS);
	
	while( m_lookahead != CLOSE_PARENTHESIS && m_lookahead != NUL )
	{
		if (	m_lookahead == AIPI_SHOWCTRL 
			||	m_lookahead == AIPI_PLAY
			||  m_lookahead == AIPI_INPUTVAR
			||  m_lookahead == AIPI_PATH
			)
		{
						
			if(m_lookahead == AIPI_SHOWCTRL )
			{
				matchToken(AIPI_SHOWCTRL);
				matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					matchToken(AIPI_TRUE);
					bShowWnd = true;
	
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					matchToken(AIPI_FALSE);
					bShowWnd = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
				}
			}
			else if( m_lookahead == AIPI_PLAY )
			{
				matchToken(AIPI_PLAY);
				matchToken(EQUAL);
				
				if( m_lookahead == AIPI_TRUE )
				{
					matchToken(AIPI_TRUE);
					bPlayVideo = true;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					matchToken(AIPI_FALSE);
					bPlayVideo = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
				}
				
			}
			else if( m_lookahead == AIPI_INPUTVAR )
			{
				matchToken(AIPI_INPUTVAR);
				matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					matchToken(AIPI_TRUE);
					bInput = true;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{					
					matchToken(AIPI_FALSE);
					bInput = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
				}
				
			}
			else if( m_lookahead == AIPI_PATH )
			{
				matchToken(AIPI_PATH);
				matchToken(EQUAL);

				CAipi_Tokenizer tkz;
				tstring strPath = tkz.v_lastToken();
				szPath = strPath.data();
				
				if( szPath != _T("") )
				{
					bPath = true;
				}

				matchToken(LITERAL);
				if( m_lookahead != CLOSE_PARENTHESIS )
				{
					matchToken(COMMA);
				}
			}
			
		}
		else
		{
			break;
		}
		
		
	}

	matchToken(CLOSE_PARENTHESIS);
	matchToken(SEMICOLON);


	if( bShowWnd )
	{
		//AfxMessageBox(_T("LOOK CTRL"));
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->Cmd_OpenMediaPlayerDlg();
		
		if( bPath )
		{
			pMainFrame->Cmd_PathMediaPlayerDlg(szPath);
			
			if( bPlayVideo )
			{
				pMainFrame->Cmd_PlayMediaPlayerDlg();
				//AfxMessageBox(_T("PLAY CTRL"));

				if( bInput)
				{
					pMainFrame->Cmd_OpenCommandDlgBar();
				}
			}
		}


	}
	else
	{
		//AfxMessageBox(_T("CLOSE CTRL"));
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->Cmd_CloseMediaPlayerDlg();
	}

}

void CAipi_ExpParserFileGlobal::ctrl_imagefilter()
{
	
	//AfxMessageBox(_T("ENTRO IMAGEFILTERDLG"));
	bool bShowWnd = false;
	bool bInput = false;
	bool bPath = false;
	CString szPath = _T("");
	
	matchToken(AIPI_CTRL_IMAGEFILTER);
	matchToken(OPEN_PARENTHESIS);
	
	while( m_lookahead != CLOSE_PARENTHESIS && m_lookahead != NUL )
	{
		if (	m_lookahead == AIPI_SHOWCTRL 
			||	m_lookahead == AIPI_INPUTVAR
			||  m_lookahead == AIPI_PATH
			)
		{
			
			if(m_lookahead == AIPI_SHOWCTRL )
			{
				matchToken(AIPI_SHOWCTRL);
				matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					matchToken(AIPI_TRUE);
					bShowWnd = true;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					matchToken(AIPI_FALSE);
					bShowWnd = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
				}
			}
			else if( m_lookahead == AIPI_INPUTVAR )
			{
				matchToken(AIPI_INPUTVAR);
				matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					matchToken(AIPI_TRUE);
					bInput = true;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					matchToken(AIPI_FALSE);
					bInput = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
				}
				
			}
			else if( m_lookahead == AIPI_PATH )
			{
				matchToken(AIPI_PATH);
				matchToken(EQUAL);

				CAipi_Tokenizer tkz;
				tstring strPath = tkz.v_lastToken();
				szPath = strPath.data();
				
				if( szPath != _T("") )
				{
					bPath = true;
				}

				matchToken(LITERAL);
				if( m_lookahead != CLOSE_PARENTHESIS )
				{
					matchToken(COMMA);
				}
			}
		}
		else
		{
			break;
		}
		
	
	}

	matchToken(CLOSE_PARENTHESIS);
	matchToken(SEMICOLON);


	if( bShowWnd )
	{
		//AfxMessageBox(_T("LOOK CTRL"));
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->Cmd_OpenImageFilterDlg();
		
		if( bPath )
		{
			pMainFrame->Cmd_PathImageFilterDlg(szPath);
			
			if( bInput)
			{
				pMainFrame->Cmd_OpenCommandDlgBar();
			}
			
		}

	}
	else
	{
		//AfxMessageBox(_T("CLOSE CTRL"));
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->Cmd_CloseImageFilterDlg();
		
	}

}

int CAipi_ExpParserFileGlobal::ctrl_listoption()
{
	//AfxMessageBox(_T("ENTRO LISTOPTION CTRL"));
	CAipi_Tokenizer tkz;
	bool bShowWnd = false;
	bool bInput = false;
	bool bInsert = false;
	
	long posTk = 0;
	long iformTk = UNDEFINE;
	tstring strTk = _T("");
	CString szTk = _T("");
	CString szItem = _T("");
	CString szTip = _T("");

	std::vector	<CString> vListItems;
	std::vector	<CString> vListTips;

	vListItems.clear();
	vListTips.clear();


	matchToken(AIPI_CTRL_LISTOPTION);
	matchToken(OPEN_PARENTHESIS);
	

	while( m_lookahead != CLOSE_PARENTHESIS && m_lookahead != _TEOF )
	{
		if (	m_lookahead == AIPI_SHOWCTRL 
			||	m_lookahead == AIPI_INSERT
			||  m_lookahead == AIPI_INPUTVAR
			)
		{
			
			if(m_lookahead == AIPI_SHOWCTRL )
			{
				matchToken(AIPI_SHOWCTRL);
				matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					matchToken(AIPI_TRUE);
					bShowWnd = true;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					matchToken(AIPI_FALSE);
					bShowWnd = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
				}
			}
			else if( m_lookahead == AIPI_INPUTVAR )
			{
				matchToken(AIPI_INPUTVAR);
				matchToken(EQUAL);
				
				iformTk = tkz.v_lastIntFormToken();
				strTk = tkz.v_lastToken();
				szTk = strTk.data();
				posTk = tkz.v_lastPosition();
				
				if( szTk != _T("") )
				{
					bInput = true;
				}
				
				//AfxMessageBox(_T("INPUT ID.............................VAR"));
				/*
				CString str;
				str.Format(_T("ID IFORM...%d  " ), iformTk);
				AfxMessageBox(str);
				AfxMessageBox(szTk);
				*/				

				
				matchToken(IDENTIFIER); 
				
				
			}
			else if( m_lookahead == AIPI_INSERT )
			{
				
				bInsert = true;
				matchToken(AIPI_INSERT);
				matchToken(EQUAL);
				matchToken(OPEN_BRACE);
				while( m_lookahead != CLOSE_BRACE )
				{
					if( m_lookahead == OPEN_PARENTHESIS )
					{
												
						matchToken(OPEN_PARENTHESIS);
						tstring strItem = tkz.v_lastToken();
						szItem = strItem.data();
						if( szItem != _T("") )
						{
							vListItems.push_back(szItem);
						}

						matchToken(LITERAL);
						matchToken(COMMA);

						tstring strTip = tkz.v_lastToken();
						szTip = strTip.data();
						if( szTip != _T("") )
						{
							vListTips.push_back(szTip);
							
						}
						else
						{
							vListTips.push_back(_T(""));
						}

						matchToken(LITERAL);
						matchToken(CLOSE_PARENTHESIS);
						if( m_lookahead != CLOSE_BRACE)
						{
							matchToken(COMMA);
						}

					
					}
					else
					{

						tstring strItem = tkz.v_lastToken();
						szItem = strItem.data();
				
						if( szItem != _T("") )
						{
							vListItems.push_back(szItem);
						}
					
						matchToken(LITERAL);
						if( m_lookahead != CLOSE_BRACE)
						{
							matchToken(COMMA);
						}
					}
				}
				
				matchToken(CLOSE_BRACE);
				
				if( m_lookahead != CLOSE_PARENTHESIS )
				{
					matchToken(COMMA);
				}
			}
			
		}
		else
		{
			break;
		}
		
	
	}

	matchToken(CLOSE_PARENTHESIS);
	matchToken(SEMICOLON);

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndListOptionCtrl.ResetListBox();
	
	//Check if CImageList was already created
	if( g_ImageListFlag != true )
	{
		pMainFrame->m_wndListOptionCtrl.SetImageList();
		g_ImageListFlag = true;
	}

	
	/*
	//print vector
	for(int i = 0; i<vListItems.size(); ++i )
	{
		CString sItem = vListItems.at(i);
		pMainFrame->m_wndOutputTabView.AddMsg1(sItem);
    }
	*/

	


	if( bShowWnd )
	{
		//AfxMessageBox(_T("LOOK CTRL"));
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->Cmd_OpenListOptionCtrl();
		
		if( bInsert )
		{
			CString sItem;
			CString sTip;
			for(int i = 0; i<vListItems.size(); ++i )
			{
				sItem = vListItems.at(i);
				if( !vListTips.empty() )
				{
					sTip = vListTips.at(i);
					
				}
									
				LPCTSTR lpcItem = (LPCTSTR)sItem;
				LPCTSTR lpcTip = (LPCTSTR)sTip;
				pMainFrame->Cmd_InsertListOptionCtrl(lpcItem, lpcTip);
				
			}
			
			if( bInput)
			{
				//Search in numeric variables
				double dId =  NumericVarSearch(iformTk);
				
				if( dId == NOT_FOUND )
				{
					//Search in literal variables
					CString szLit = LiteralVarSearch( iformTk);
					if( szLit != _T("NOT_FOUND") )
					{
						//AfxMessageBox(_T("Found var Literal"));
						g_currentDataCateg = LITERAL;
						g_currentId_IForm = iformTk;
						g_currentLookahead = m_lookahead;
						g_fcurrentPos = posTk;

						return AIPI_STOP;
						
					}
					else
					{
						CAipi_Error er;
						CString strDesc = _T("Identifier [") + szTk + _T("] was not found.");
						er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
					}
				}
				else
				{
					//AfxMessageBox(_T("Found var Numeric"));					
					g_currentDataCateg = DIGIT;
					g_currentId_IForm = iformTk;
					g_currentLookahead = m_lookahead;
					g_fcurrentPos = posTk;


					return AIPI_STOP;
				}

			}
			
		}


	}
	else
	{
		//AfxMessageBox(_T("CLOSE CTRL"));
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->Cmd_CloseListOptionCtrl();
	}



return P_SUCCESS;
	
}



void CAipi_ExpParserFileGlobal::ctrl_listoption_continue()
{
	AfxMessageBox(_T("List Ctrl ExpParserFileGlobal"));	
/*
	AfxMessageBox(_T("Input Val"));
	AfxMessageBox(g_currentCmdInput);
	CString s;
	s.Format(_T("Data Categ...%d  " ), g_currentDataCateg);
	AfxMessageBox(s);
	*/			


	if(g_currentDataCateg == LITERAL )
	{
		m_sCurrentId = g_currentCmdInput;
		CAipi_STableGlobalLiteral lt;
		lt.editSTableLiteralValue(g_currentId_IForm, m_sCurrentId);
		//lt.printSTableLiteral();
	}
	if( g_currentDataCateg == DIGIT )
	{
		//AfxMessageBox(_T("DIGIT"));
		m_dCurrentId = _tcstod(g_currentCmdInput, NULL); 
		CAipi_STableGlobalNumeric nt;
		nt.editSTableNumericValue(g_currentId_IForm, m_dCurrentId);
		//nt.printSTableNumeric();
	}

	m_lookahead = g_currentLookahead;
	if( m_lookahead == _TEOF )
	{
		return;
	}
	
	CString str;
	str.Format(_T("Look Ahead...%d  " ), m_lookahead);
	AfxMessageBox(str);
	

	
	translation_unit();

	/*
	if( g_bStopFlag != true )
	{
		fclose(g_fp);
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	}
	*/


}

void CAipi_ExpParserFileGlobal::ctrl_oledb()
{
	matchToken(AIPI_CTRL_OLEDB);
	matchToken(OPEN_PARENTHESIS);
	
	while( m_lookahead != CLOSE_PARENTHESIS && m_lookahead != NUL )
	{
		if (	m_lookahead == AIPI_SHOWCTRL 
			||	m_lookahead == AIPI_INPUTVAR
			||  m_lookahead == AIPI_SHOWTABLES
			)
		{
			
			if(m_lookahead == AIPI_SHOWCTRL )
			{
				matchToken(AIPI_SHOWCTRL);
				matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					matchToken(AIPI_TRUE);
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					matchToken(AIPI_FALSE);
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
				}
			}
			else if( m_lookahead == AIPI_SHOWTABLES )
			{
				matchToken(AIPI_SHOWTABLES);
				matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					matchToken(AIPI_TRUE);
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					matchToken(AIPI_FALSE);
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
				}
				
			}
			else if( m_lookahead == AIPI_INPUTVAR )
			{
				matchToken(AIPI_INPUTVAR);
				matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					matchToken(AIPI_TRUE);
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					matchToken(AIPI_FALSE);
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						matchToken(COMMA);
					}
				}
				
			}
		}
		else
		{
			break;
		}

		
		
	
	}

	matchToken(CLOSE_PARENTHESIS);


}

