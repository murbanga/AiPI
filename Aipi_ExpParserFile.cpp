// Aipi_ExpParserFile.cpp: implementation of the CAipi_ExpParserFileFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_ExpParserFile.h"

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

CAipi_ExpParserFile::CAipi_ExpParserFile()
:m_query(GetSession())
{
	m_index = 0;
	//Data Base 
	m_bFlagConnDlg = false; //Database is needed
	g_iDBProvider = UNDEFINE;
	m_dbProvider = _T("");
	m_dbDNS = _T("");
	m_dbUser = _T("");
	m_dbPassword = _T("");
	m_dbName = _T("");
	

	g_bStopFlag = false; //Stop interpreter flag
	//g_currentVarLoc = UNDEFINE;
	//g_currentParserClass = EXP_PARSER_FILE;
	
	
}

CAipi_ExpParserFile::~CAipi_ExpParserFile()
{

}


void CAipi_ExpParserFile::ExecCmdSearch(long pm, int i1, int i2)
{ 
	/*
	CString str;
	str.Format(_T("Cmd Search PM...%d  " ), pm);
	AfxMessageBox(str);
	*/

	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmCmdLocation::iterator iterCmd;
	pair <CMainFrame::g_mmCmdLocation::iterator, CMainFrame::g_mmCmdLocation::iterator>  pCmd;

	//Search for Commands in the production
	pCmd = pMainFrame->gmmCmdLocation.equal_range(pm);
	for(iterCmd = pCmd.first; iterCmd != pCmd.second; ++iterCmd)
	{	
		  
		//AfxMessageBox(_T("Exp Parser File: Entro a buscar command"));
		CAipi_CmdLocation cloc = (CAipi_CmdLocation)iterCmd->second;
		long index1  = cloc.getStartIndex();
		long index2 = cloc.getEndIndex();
				 
		if( i2 > index1  )
		{
			continue;
		}
		
		m_index = index1;
		m_endIndex = index2;
		
		callExpParserFile();
				
	}

 
	//AfxMessageBox(_T("END ExpParserFILE CONFLIC_SET"));
}

CString CAipi_ExpParserFile::LiteralVarSearch(long iform)
{
	//Search global literal variables first
	CAipi_STableGlobalLiteral lit;
	int f = lit.findSTableLiteralMembers( iform);
	if( f == NOT_FOUND )
	{
		//Search local literal variables
		CAipi_STableLocalLiteral lit;
		int f = lit.findSTableLiteralMembers( iform);
		if( f == NOT_FOUND )
		{
			return _T("NOT_FOUND");
		}
		else
		{
			g_currentVarLoc = VAR_LOCAL;
			CString str = lit.m_STLitValue.data();
			//AfxMessageBox(str);
			return str; 
		}
	}
	else
	{
		g_currentVarLoc = VAR_GLOBAL;
		CString str = lit.m_STGLitValue.data();
		//AfxMessageBox(str);
		return str;
	}

return _T("NOT_FOUND");
	
}



double CAipi_ExpParserFile::NumericVarSearch(long iform)
{
	//Search global numeric variables first
	CAipi_STableGlobalNumeric num;
	double f = num.findSTableNumericMembers(iform);
	if( f == NOT_FOUND )
	{
		//Search local numeric variables
		CAipi_STableLocalNumeric num;
		double f = num.findSTableNumericMembers(iform);
		if( f == NOT_FOUND )
		{
			return NOT_FOUND;			
		}
		else
		{
			//AfxMessageBox(_T("Encontro Variable"));
			g_currentVarLoc = VAR_LOCAL;
			double val = num.m_STLNumValue;
			/*
			CString str;
			str.Format(_T("%f"), val);
			AfxMessageBox(str);
			*/
			return val;
		}
	}
	else
	{
		//AfxMessageBox(_T("Encontro Variable"));
		g_currentVarLoc = VAR_GLOBAL;
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

//////////////////////////////////////////////////////////////////////////////////////////////
//// Script ////
///////////////////////////////////////////////////////////////////////////////////////////////
void CAipi_ExpParserFile::ScriptSearch(long iform, tstring sId)
{
	CAipi_ScriptCode script;
	int f = script.findScriptMembers(iform);
	if( f != NOT_FOUND )
	{
		CString	lang = script.m_ScriptLanguage;
		CString code = script.m_ScriptDefinition;
		tstring	name = script.m_ScriptName;
		CString strName = name.data();
					
		if( lang == _T("JScript") || lang == _T("VBScript") )
		{
			//AfxMessageBox(_T("EXECUTE SCRIPT"));
						
			long index1 = script.m_StartIndex;
			long pos1 = script.m_StartPos;
			int nParam = script.m_nParameters;
						
			/*
			CString str;
			str.Format(_T("m_index %d"), m_index);
			AfxMessageBox(str);
			str.Format(_T("m_endIndex %d"), m_endIndex);
			AfxMessageBox(str);
			*/
			long indexEndScript = ScriptSaveParam(m_index, m_endIndex);
			if( indexEndScript != P_UNSUCCESS )
			{
				//CString str;
				//str.Format(_T("End call Script %d"), indexEndScript);
				//AfxMessageBox(str);
							
				CString szResult = ScriptExecute(pos1, index1, nParam, strName, lang, code);
				double result = isDigitOpt(szResult);
				if( result != 0 )
				{
					m_stackNumeric.push(result);
				}
				else
				{
					tstring strResult =  (LPCTSTR)szResult;
					m_stackLiteral.push(strResult);
				}
							
				m_vParameters.clear();
				m_index = indexEndScript;
			}
			else
			{
				CAipi_Error err;
				err.displayFileError(JSCRIPT_PARAM, JSCRIPT_ERROR, _T("The function parameters syntax is incorrect or not permited."));
				return;
			}
		}
		else if ( lang == _T("SQL") )
		{
			/*
			AfxMessageBox(_T("Encontro Script SQL"));
			AfxMessageBox(code);
			*/
			CString szResult = _T("");
		
			int nParam = script.m_nParameters;
			
			if( nParam == 0 )
			{
				m_query << code;
				if( !m_query.ExecuteSQL())
				{
					return;
				}
				int nCol = m_query.GetColumnsCount();
				int nRow = m_query.GetDataCount();
				/*
				CString str;
				str.Format(_T("nCol... %d"), nCol);
				AfxMessageBox(str);
				str.Format(_T("nRow... %d"), nRow);
				AfxMessageBox(str);
				*/

				if( nCol == 1 && nRow == 1 )
				{
					m_query > szResult; 
					double result = isDigitOpt(szResult);
					if( result != 0 )
					{
						m_stackNumeric.push(result);
					}
					else
					{
						tstring strResult =  (LPCTSTR)szResult;
						m_stackLiteral.push(strResult);
					}
				}
				else
				{
					SqlRunQuery(code);
				}
			}
			else
			{
				long index1 = script.m_StartIndex;
				long index2 = script.m_EndIndex;
				SqlRunQueryVars(code, index1, index2);
			}
		}
	}
	else
	{					
		CAipi_Error err;
		CString  strId = sId.data();
		CString  strDesc = _T("No type was found for script identifier [") + strId + _T("]."); 
		err.displayFileError(UNKNOW_TYPE, SEMANT_ERROR, strDesc);
	}


}

long CAipi_ExpParserFile::ScriptSaveParam(long i1, long i2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_Tokenizer tkz;
	int nParam = 0;
	long pos = 0;
	long posOpenParenthesis = pMainFrame->gvTokenizer[i2].getPos1();
	long posCloseParenthesis = pMainFrame->gvTokenizer[i2].getPos1();
	long indexCloseParenthesis = 0;
	long iForm = 0;
	tstring sToken = _T("");

	/*
	CString str;
	str.Format(_T("Index1...%d  " ), i1);
	AfxMessageBox(str);
	str.Format(_T("Index2...%d  " ), i2);
	AfxMessageBox(str);
	*/
	

	for( long i = i1; i< i2; ++i )
	{
		sToken	= pMainFrame->gvTokenizer[i].getToken();
		iForm	= pMainFrame->gvTokenizer[i].getIntForm();
		pos		= pMainFrame->gvTokenizer[i].getPos1();
 		
		//Open parenthesis after the script function name
		if( iForm == OPEN_PARENTHESIS )
		{
			posOpenParenthesis   = pMainFrame->gvTokenizer[i].getPos1();
			/*
			CString str;
			str.Format(_T("pos open parenthesis...%d  " ), pos);
			AfxMessageBox(str);
			*/
		}
		//Close parenthesis after the script function name
		if( iForm == CLOSE_PARENTHESIS )
		{
			posCloseParenthesis   = pMainFrame->gvTokenizer[i].getPos1();
			
			/*
			CString str;
			str.Format(_T("pos close parenthesis...%d  " ), pos);
			AfxMessageBox(str);
			*/
		}
		/*
		CString str;
		str.Format(_T("pos...%d  " ), pos);
		AfxMessageBox(str);
		AfxMessageBox(sToken.data());
		*/
		if( pos >  posOpenParenthesis && pos < posCloseParenthesis )
		{
			//AfxMessageBox(_T("GetIn"));
			if( iForm != COMMA )
			{
				CString strParam = sToken.data();
				m_vParameters.push_back(strParam);
				++nParam;

				/*
				CString str;
				str.Format(_T("nParam %d"), nParam);
				AfxMessageBox(str);
				AfxMessageBox(strParam);
				*/
			}
		}
		if( pos > posCloseParenthesis )
		{
			indexCloseParenthesis = i;
			return indexCloseParenthesis;
		}
		
		
		
	}

	return P_UNSUCCESS;
}


CString CAipi_ExpParserFile::ScriptExecute(long pos1, long index1, int nParam, CString name, CString lang, CString code)
{
	m_ScriptObj.Reset();
	m_ScriptObj.SetLanguage(lang);

	if (!m_ScriptObj.AddScript( code ))
	{
		//AfxMessageBox(_T("Error Sale"));
		CAipi_Tokenizer tkz;
		int  line = tkz.v_getLineByIndex(index1);
		ScriptDisplayError(pos1, line, name);
		return _T("ERROR");;
	}
	else
	{
		//AfxMessageBox(code);	
	}


	CString sResult = _T("");
	CSafeArrayHelper sfHelper;
	
	try
	{
		_variant_t var;
		
		sfHelper.Create(VT_VARIANT, 1, 0, nParam);

		int v_size = m_vParameters.size();
		/*
		CString str;
		str.Format(_T("nElements %d"), v_size);
		AfxMessageBox(str);
		*/
		for(int i=0; i< nParam; ++i)
		{
			
			CString sParam = m_vParameters.at(i);
			//AfxMessageBox(sParam);

			var = _bstr_t(sParam);
			sfHelper.PutElement(i, (void*)&var);
		}
		
		//AfxMessageBox(_T("Try"));
		LPSAFEARRAY sa = sfHelper.GetArray();
		_variant_t varRet;
		
		if( m_ScriptObj.RunProcedure(name, &sa, &varRet))
		{
			//AfxMessageBox(_T("Run"));
			sResult = (LPCTSTR)_bstr_t(varRet);
			//AfxMessageBox(_T("SCRIP RESULT"));
			//AfxMessageBox(sResult);
		}
		else
		{
			//AfxMessageBox(_T("Error"));
			CAipi_Tokenizer tkz;
			int  line = tkz.v_getLineByIndex(index1);
			/*
			CString str;
			str.Format(_T("line %d"), line);
			AfxMessageBox(str);
			str.Format(_T("position1 %d"), pos1);
			AfxMessageBox(str);
			*/

			ScriptDisplayError(pos1, line, name);
			sResult = _T("ERROR");
			//CString sError = m_ScriptObj.GetErrorString();
			//ScriptDisplayError(posStartProc);
			//AfxMessageBox(sError);
		}
	}
	catch(...)
	{
		//AfxMessageBox(_T("Catch"));
		CAipi_Tokenizer tkz;
		int  line = tkz.v_getLineByIndex(index1);
		ScriptDisplayError(pos1, line, name);
		sResult = _T("ERROR");
		//ScriptDisplayError(pos1, line, strName); 
		//CString sError = m_ScriptObj.GetErrorString();
		//AfxMessageBox(sError);
	}

	
return sResult;	

}

void CAipi_ExpParserFile::ScriptDisplayError(long nStartSel, int line, CString name)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	//_bstr_t line = _T("");

	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	
	LPTSTR lpsErrLine =_T("0");
	//LPTSTR lpsLine =_T("0");

	LPTSTR lpsErrPos = _T("0");
	LPTSTR lpsErrCode = _T("0");
	LPTSTR lpsErrDesc = _T("No description has found for this error");
	LPTSTR lpsErrFile = _T("");
	
	int type = JSCRIPT_ERROR;
	
	//Handle Internationational
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();

	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		//errLine = _bstr_t(_T("Línea: "))  +  _itot( g_currentLine, buff, 10 );
		//errPos = _bstr_t(_T("Pos. "))  +  _itot(g_currentPos, buff, 10);
		break;
	default:
		//errLine = _bstr_t(_T("Line: "))  +  _itot( g_currentLine, buff, 10 );
		//errPos = _bstr_t(_T("Pos. "))  +  _itot(g_currentPos, buff, 10);
		break;
	}

	
	//LPTSTR strErrorLineNumber = (LPTSTR)line;
	CString strErrScriptLine = m_ScriptObj.GetErrorLineNumber();
	int nErrScriptLine = _ttoi(strErrScriptLine);
	int nStartScriptLine = rCtrl.LineFromPosition(nStartSel);
	int nErrLine = nStartScriptLine + nErrScriptLine + 1;
	TCHAR buffer[8];
	CString strErrLine = _itot( nErrLine, buffer, 10 );
	lpsErrLine = strErrLine.GetBuffer(0);  
	strErrLine.ReleaseBuffer();

	/*
	CString strLine = _itot( line, buffer, 10 );
	lpsLine = strErrLine.GetBuffer(0);  
	strLine.ReleaseBuffer();
	*/
	//AfxMessageBox(strErrLine);
	//AfxMessageBox(strLine);
	
	
	CString strErrCode = m_ScriptObj.GetErrorNumber();
	lpsErrCode = strErrCode.GetBuffer(0);
	strErrCode.ReleaseBuffer();
	

	CString strErrDesc = m_ScriptObj.GetErrorDescription();
	strErrDesc += _T(" Method: ") + name + _T(".");
	lpsErrDesc = strErrDesc.GetBuffer(0);
	strErrDesc.ReleaseBuffer();

	CString strErrScriptCol = m_ScriptObj.GetErrorColumn();
	int nErrScriptCol = _ttoi(strErrScriptCol);
	int nStartScriptPos = rCtrl.PositionFromLine(nErrLine -1);
	int nErrCol = nErrScriptCol + nStartScriptPos;
	CString strErrCol = _itot( nErrCol, buffer, 10 );
	lpsErrPos = strErrCol.GetBuffer(0);
	strErrCol.ReleaseBuffer();

	CString strErrFile = g_currentFile;
	lpsErrFile = strErrFile.GetBuffer(0);
	strErrFile.ReleaseBuffer();

	/*
	AfxMessageBox(strErrScriptLine);
	AfxMessageBox(strErrCode);
	AfxMessageBox(strErrDesc);
	AfxMessageBox(strErrScriptCol);
	*/		

	if ( pMainFrame->m_wndOutputTabView.IsVisible())
    {
		
		pMainFrame->m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(1);
		LVITEM  Item = pMainFrame->m_wndOutputTabView.AddListItem2(0, 0, _T(""), type);
		pMainFrame->m_wndOutputTabView.AddListSubItem2(Item, 0, 1, lpsErrLine);
		pMainFrame->m_wndOutputTabView.AddListSubItem2(Item, 0, 2, lpsErrPos);
		pMainFrame->m_wndOutputTabView.AddListSubItem2(Item, 0, 3, lpsErrDesc);
		pMainFrame->m_wndOutputTabView.AddListSubItem2(Item, 0, 4, lpsErrFile);
		pMainFrame->m_wndOutputTabView.AddListSubItem2(Item, 0, 5, lpsErrCode);
	}
	
	m_ScriptObj.ClearError();


}

////////////////////////////////////////////////////////////////////////////////////
//// SQL OleDB DataBase /////
///////////////////////////////////////////////////////////////////////////////////
int CAipi_ExpParserFile::SqlSelectDB(tstring db)
{
	if( db == _T("Ms_Access") || db == _T("MS_ACCESS") )
	{		
		//m_idbProvider = MS_ACCESS;
		g_iDBProvider = MS_ACCESS;
		return g_iDBProvider;
	}
	else if ( db == _T("Ms_SqlServer") || db == _T("MS_SQLSERVER") )
	{
		//m_idbProvider = MS_SQLSERVER;
		g_iDBProvider = MS_SQLSERVER;
		return g_iDBProvider;
	}
	else if ( m_dbProvider == _T("Ms_Oracle") || _T("MS_ORACLE") )
	{
		//m_idbProvider = MS_ORACLE;
		g_iDBProvider = MS_ORACLE;
		return g_iDBProvider;
	}
	else if( m_dbProvider == _T("Oracle") || _T("MS_ORACLE") )
	{
		//m_idbProvider = ORACLE;
		g_iDBProvider = ORACLE;
		return g_iDBProvider;
	}
	else if( m_dbProvider == _T("MySql") || _T("MYSQL") )
	{
		//m_idbProvider = MYSQL;
		g_iDBProvider = MYSQL;
		return g_iDBProvider;
	}
	else if( m_dbProvider == _T("db2") || _T("DB2")  )
	{
		//m_idbProvider = DB2;
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


void CAipi_ExpParserFile::SqlShowDBDlg()
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



void CAipi_ExpParserFile::SqlOpenConnectionDlg()
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




void CAipi_ExpParserFile::SqlOpenOleDB()
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

void CAipi_ExpParserFile::SqlRunQuery(CString query)
{
	//AfxMessageBox(_T("SQL Run Query"));
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->m_wndOleDBDlg.m_strQuery = query;
	pMainFrame->m_wndOleDBDlg.RunQuery();
	pMainFrame->m_wndOleDBDlg.m_wndQueryEdit.SetWindowText(query);

}


void CAipi_ExpParserFile::SqlRunQueryVars(CString query, long index1, long index2)
{
	/*
	AfxMessageBox(_T("SQL Run Query VARIABLES"));
	AfxMessageBox(query);
	*/	
	
	CString strToken = _T("");
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	for(long i = index1+1; i<index2; ++i)
	{
		tstring sToken = pMainFrame->gvTokenizer[i].getToken();
		
		int categ = pMainFrame->gvTokenizer[i].getCategory();
		
		if( categ == AIPI_VAR )
		{
			//AfxMessageBox(_T("Aipi Var"));
			int iform = pMainFrame->gvTokenizer[i].getIntForm();
			CAipi_STableGlobalNumeric num;
			double f = num.findSTableNumericMembers(iform);
			if( f == NOT_FOUND )
			{
				CAipi_STableLocalNumeric num;
				double f = num.findSTableNumericMembers(iform);
				if( f == NOT_FOUND )
				{
				
					CAipi_STableGlobalLiteral lit;
					int f = lit.findSTableLiteralMembers( iform);
					if( f == NOT_FOUND )
					{
						CAipi_STableLocalLiteral lit;
						int f = lit.findSTableLiteralMembers( iform);
						if( f == NOT_FOUND )
						{
							g_currentVarLoc = UNDEFINE;
							CAipi_Error er;
							CString strDesc = _T("Identifier [") + strToken + _T("] was not found.");
							er.displayGUIError(NOT_DECLARE, SEMANT_ERROR, strDesc);
						}
						else
						{
							g_currentVarLoc = VAR_LOCAL;
							CString str = lit.m_STLitValue.data();
							//AfxMessageBox(str);
	
							strToken += str + _T(" ");
						}
					}
					else
					{
						g_currentVarLoc = VAR_GLOBAL;
						CString str = lit.m_STGLitValue.data();
						//AfxMessageBox(str);
	
						strToken += str + _T(" ");
					}
				}
				else
				{
					//AfxMessageBox(_T("Encontro Variable"));
					g_currentVarLoc = VAR_LOCAL;
					double val = num.m_STLNumValue;
					
					CString str;
					str.Format(_T("%f"), val);
					//AfxMessageBox(str);
					
					strToken += str + _T(" ");
				}
			}
			else
			{
				//AfxMessageBox(_T("Encontro Variable"));
				g_currentVarLoc = VAR_GLOBAL;
				double val = num.m_STGNumValue;
				
				CString str;
				str.Format(_T("%f"), val);
				strToken += str + _T(" ");
				//AfxMessageBox(str);
				
				
			}
		}
		else
		{
			strToken += sToken.data();
			strToken += _T(" ");
			//AfxMessageBox(strToken);
		}
	}
	 
	

	pMainFrame->m_wndOleDBDlg.m_strQuery = strToken;
	pMainFrame->m_wndOleDBDlg.RunQuery();
	pMainFrame->m_wndOleDBDlg.m_wndQueryEdit.SetWindowText(strToken);

}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////
//// Lexer /////
////////////////////////////////////////////////////////////////////////

bool CAipi_ExpParserFile::isDigit(CString t)
{
	CString first = t[0];
	if( first == _T("0") || first == _T("1") || first == _T("2") || first == _T("3") ||
		first == _T("4") || first == _T("5") || first == _T("6") || first == _T("7") ||
		first == _T("8") || first == _T("9")
	  )
	{
		return true;
	}

return false;	

}

double CAipi_ExpParserFile::isDigitOpt(CString t)
{
	double digit = _tcstod(t, NULL);
	if( digit == 0 )
	{
		//Can not convert to double
		return 0;
	}
	if( digit == HUGE_VAL || digit == -HUGE_VAL )
	{
		//Error value is to long
		return HUGE_VAL; 
	}

return digit;
	
}

bool CAipi_ExpParserFile::isAlphabetic(CString t)
{
	t.MakeLower(); 

	if( t == _T("a") || t == _T("b") || t == _T("c") || t == _T("d") || t == _T("e") || t == _T("f") || 
		t == _T("g") || t == _T("h") || t == _T("i") || t == _T("j") || t == _T("k") || t == _T("l") ||
		t == _T("m") || t == _T("n") || t == _T("o") || t == _T("p") || t == _T("q") || t == _T("r") || 
		t == _T("s") || t == _T("t") || t == _T("u") || t == _T("v") || t == _T("w") || t == _T("x") || 
		t == _T("y") || t == _T("z") )
	{
		return true;
	}
	    
return false;
}




////////////////////////////////////////////////////////////////////////
//// Expression parser ////
//////////////////////////////////////////////////////////////////////////

void CAipi_ExpParserFile::initExpParserFile()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Syntax analyzer..."), RGB(0,0,0), TRUE);


	CAipi_Lexer lex;
	CAipi_Tokenizer tkz;
	
	g_currentId_IForm = 1000;
	m_index = 0;
	m_endIndex = tkz.v_sizeTokenizer();
	m_fendPos = g_currentDocEndPos;

	
	//AfxMessageBox(_T("Expression Parser TOKEN"));
	getTokenizer();

	//AfxMessageBox(_T("Empieza ExParserFile "));
	translation_unit();
	//AfxMessageBox(_T("Termina ExParserFile "));
	
	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	
 
}

void CAipi_ExpParserFile::callExpParserFile()
{
	//AfxMessageBox(_T("****Entro EXP PARSER FILE****"));
	
	getTokenizer();
	translation_unit();

	//AfxMessageBox(_T("****Entro EXP PARSER FILE****"));
}


void CAipi_ExpParserFile::initTokenizer()
{
	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Syntax analyzer..."), RGB(0,0,0), TRUE);
	
	if( pMainFrame->gvTokenizer.empty() )
	{
		//AfxMessageBox(_T("vacio"));
		return;
	}

	
	if( m_index < pMainFrame->gvTokenizer.size() )
	{
		getTokenizer();
	}
	
	if( m_lookahead == COMMENT )
	{
		//AfxMessageBox(_T("Comments"));
		do
		{
			getTokenizer();
				
		}while (m_lookahead == COMMENT || m_lookahead == _TEOF );
	}

	translation_unit();


}


void CAipi_ExpParserFile::getToken()
{
	CAipi_Lexer lex;
	TCHAR symbol =  _gettc(g_fp);
	m_lookahead = lex.getTokenFile(symbol);
	m_sToken = lex.m_sToken;

	

	if( m_lookahead == COMMENT )
	{
		do
		{
			TCHAR symbol =  _gettc(g_fp);
			m_lookahead = lex.getTokenFile(symbol);
			m_sToken = lex.m_sToken;
		
		}while (m_lookahead == COMMENT || m_lookahead == _TEOF );
	}

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, g_fcurrentPos*100/m_fendPos);
	
	
/*
	
	CString str;
	str.Format(_T("Look Ahead...%d  " ), m_lookahead);
	AfxMessageBox(str);
	//str.Format(_T("pos...%d  " ), g_fcurrentPos);
	//AfxMessageBox(str);
	m_sToken = lex.m_sToken;
	AfxMessageBox(m_sToken);
*/

}



long CAipi_ExpParserFile::getTokenizer()
{
	//AfxMessageBox(_T("Tokenizer"));
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	/*
	CString str;
	str.Format(_T("TOKENIZER SIZE...%d  " ), tkzSize);
	AfxMessageBox(str);
	*/

	/*
	CString str;
	str.Format(_T("Index1...%d  " ), m_index);
	AfxMessageBox(str);
	str.Format(_T("Index2...%d  " ), m_endIndex);
	AfxMessageBox(str);
	*/
	
	if( m_index > m_endIndex )
	{
		longjmp(e_buf, 1);
	}
	else if( m_index <  m_endIndex )
	{
		
		m_lookahead = pMainFrame->gvTokenizer[m_index].getCategory();
		//g_currentLookahead = m_lookahead;
		m_sToken = pMainFrame->gvTokenizer[m_index].getToken().data();
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, m_index*100/m_endIndex);
		
				
		++m_index;
		
		
		CString str;
		str.Format(_T("Tokenizer Look Ahead...%d  " ), m_lookahead);
		AfxMessageBox(str);
		AfxMessageBox(m_sToken);
		
		//str.Format(_T("index...%d  " ), m_index);
		//AfxMessageBox(str);
		
		
	}
	else
	{
		AfxMessageBox(_T("Asigno End Of File"));
		m_lookahead = _TEOF;
	}


	if( m_lookahead == COMMENT )
	{
		//AfxMessageBox(_T("COMENTARIO ENCONTRADO"));
		do
		{
			if( m_index < m_endIndex )
			{
				m_lookahead = pMainFrame->gvTokenizer[m_index].getCategory();
				m_sToken = pMainFrame->gvTokenizer[m_index].getToken().data();
				pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, m_index*100/m_endIndex);

				++m_index;
	
				/*
				CString str;
				str.Format(_T("Look Ahead...%d  " ), m_lookahead);
				AfxMessageBox(str);
				AfxMessageBox(m_sToken);
				*/
				//str.Format(_T("index...%d  " ), m_index);
				//AfxMessageBox(str);
				
			}
			else
			{
				m_lookahead = _TEOF;
				break;
			}

		}while (m_lookahead == COMMENT  );
	}


return m_lookahead;
}


void CAipi_ExpParserFile::printStack()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Parser Stack  *******"));
		
	CString str = _T("");

	int size = m_stackNumeric.size();
	for( int i = 0; i< size; ++i )
	{
		double element = m_stackNumeric.top();
		str.Format(_T("Element...%d , %f " ), i, element);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);

	}

}


void CAipi_ExpParserFile::emit_declaration(int tk)
{
	if ( tk == IDENTIFIER )
	{
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		double id = pMainFrame->gvTokenizer[m_index-1].getIntForm();
		tstring tk = pMainFrame->gvTokenizer[m_index-4].getToken();
		//AfxMessageBox(tk.data());
		m_sCurrentId = tk;
		m_dCurrentId = id;

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
			tstring sToken = (LPCTSTR)m_sToken;
			//Checking repeated identifiers declarations
			CAipi_STableLocalLiteral lit;
			int found = lit.findSTableLiteralMembers(id);      
			if( found == NOT_FOUND )
			{
				CAipi_STableLocalLiteral lt;
				lt.addSymbol(id, sToken, m_currentType,  _T(""));
			}
			else
			{
				CAipi_Error er;
				CString strDesc = _T("Identifier [") + m_sToken + _T("] was already declare.");
				er.displayFileError(DUP_VAR, SEMANT_ERROR, strDesc);
			}


		}
		else
		{
			tstring sToken = (LPCTSTR)m_sToken;
			//AfxMessageBox(m_sToken);
			//Checking repeated identifiers declarations
			CAipi_STableLocalNumeric num;
			int found = num.findSTableNumericMembers(id);
			/*
			CString str;
			str.Format(_T("idSymbol...%d  " ), idSymbol);
			AfxMessageBox(str);
			str.Format(_T("id...%d  " ), id);
			AfxMessageBox(str);
			*/

			//Check if ID were previously declare
			if( found == NOT_FOUND )
			{
				//The ID was not previously declare
				CAipi_STableLocalNumeric st;
				st.addSymbol(id, sToken, m_currentType,  0);
				//AfxMessageBox("Add Numeric Table");
				//AfxMessageBox(sToken.data());
			}
			else
			{
				//Check if identifier was used in a script definition
				CAipi_ScriptCode script;
				long idsearch = script.findId_Into_ScriptCode(id);
				if(idsearch != NOT_FOUND )
				{
					//The id was used in a script definition, but was not previously declare
					CAipi_STableLocalNumeric st;
					st.addSymbol(id, sToken, m_currentType,  0);
					//AfxMessageBox("Add Numeric Table");
					//AfxMessageBox(sToken.data());
				}
				else
				{
					CAipi_Error er;
					CString strDesc = _T("Identifier [") + m_sToken + _T("] was already declare.");
					er.displayFileError(DUP_VAR, SEMANT_ERROR, strDesc);
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

	if( tk == EQUAL )
	{
		/*
		AfxMessageBox(_T("EMIT DECLARATION EQUAL"));
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
		CAipi_Symbol sym;
		double id = m_dCurrentId;
		
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
				CAipi_STableLocalNumeric st;
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


}


void CAipi_ExpParserFile::emit_expression(int tk)
{
	CAipi_Lexer lex;

	if( tk == IDENTIFIER )
	{
		//AfxMessageBox(_T("EMIT IDENTIFIER"));
		
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		tstring sId = pMainFrame->gvTokenizer[m_index-1].getToken();
		long iform = pMainFrame->gvTokenizer[m_index-1].getIntForm();
		
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
			CAipi_STableLocalNumeric num;
			double f = num.findSTableNumericMembers(iform);
			if( f != NOT_FOUND )
			{
				//AfxMessageBox(_T("PUSH DIGIT"));
				m_stackNumeric.push(num.m_STNumValue);
				m_currentType = num.m_STLNumType;
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
					CAipi_STableLocalLiteral lit;
					int f = lit.findSTableLiteralMembers( iform);
					if( f != NOT_FOUND )
					{
						//AfxMessageBox(_T("PUSH LITERAL"));
						m_stackLiteral.push(lit.m_STLitValue);
						m_currentType = lit.m_STLLitType;
					}
					else
					{
						ScriptSearch(iform, sId);
					}
				}
			}	
		
		}
	
	}
	
	if( tk == LITERAL )
	{
		//AfxMessageBox(_T("EMIT LITERAL"));
		m_sToken.TrimLeft('"');
		m_sToken.TrimRight('"');
		m_stackLiteral.push((LPCTSTR)m_sToken);
		//AfxMessageBox(m_sToken);
	}

	if( tk == DIGIT )
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
	if( tk == EQUAL )
	{
		//AfxMessageBox(_T("EMIT EQUAL"));
		/*
		CString str;
		str.Format(_T("Current Type...%d  " ), m_currentType);
		AfxMessageBox(str);
		*/

		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		long id = pMainFrame->gvTokenizer[m_index-4].getIntForm();
		tstring tk = pMainFrame->gvTokenizer[m_index-4].getToken();
		//AfxMessageBox(tk.data());
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
				CAipi_STableLocalNumeric st;
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
	if( tk == PLUS_SIGN )
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
	if( tk == MINUS_SIGN )
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
	
	if( tk == ASTERIC )
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

	if( tk == SLASH )
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

	if( tk == PERCENT )
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

	if( tk == UNARY_MINUS )
	{
		//AfxMessageBox(_T("ADD UNARY MINUS"));
		m_stackNumeric.push(-1);
	}

	if ( tk == UNARY_PLUS )
	{
		//AfxMessageBox(_T("ADD UNARY PLUS"));
		m_stackNumeric.push(1);
	}

	if( tk == UNARY_OP )
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

	if( tk == INC_OP )
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

	if( tk == DEC_OP )
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

	if( tk == LT )
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

	if( tk == GT )
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

	if( tk == LE )
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

	if( tk == GE )
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

	if( tk == ET )
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
	
	if( tk == NE )
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

	if( tk == AND_OP )
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

	if( tk == OR_OP )
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

	/*
	int size = m_stackNumeric.size();
	CString str;
	str.Format(_T("Size...%d"  ), size);
	AfxMessageBox(str);
	*/

}


////////////////////////////////////////////////

			/// PARSER ////

///////////////////////////////////////////////

void CAipi_ExpParserFile::translation_unit()
{
	AfxMessageBox(_T("ENtro a ExpParserFile"));
	g_currentParserClass = EXP_PARSER_FILE;
	if( m_lookahead != _TEOF )
	{
		if( m_lookahead == COMMENT )
		{
			getTokenizer();
		}
		
		if(		m_lookahead == AIPI_VOID 
			||	m_lookahead == AIPI_CHAR
			||	m_lookahead == AIPI_STRING
			||	m_lookahead == AIPI_SHORT
			||	m_lookahead == AIPI_INT
			||	m_lookahead == AIPI_LONG
			||	m_lookahead == AIPI_FLOAT
			||	m_lookahead == AIPI_DOUBLE
		  )	
		{
			//AfxMessageBox(_T("Entro a declaration"));
			declaration();
			//AfxMessageBox(_T("Salio de declaration"));
			translation_unit();
		}
		else if (		m_lookahead == IDENTIFIER
					||	m_lookahead == DIGIT
				)
		{
			//AfxMessageBox(_T("Entro a expresion"));
			expression_statement();
			/*
			AfxMessageBox(_T("Salio de expresion"));
			CString str;
			str.Format(_T("Look Ahead...%d  " ), m_lookahead);
			AfxMessageBox(str);
			*/
			translation_unit();
		}
		else if( m_lookahead == AIPI_OUTPUT )
		{
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
			int r = UNDEFINE;
			//matchToken(AIPI_DISPLAYCTRL);
			getTokenizer();
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
					AfxMessageBox(_T("Aipi Stop"));
					g_bStopFlag = true;
					return;
				}
				break;
			case AIPI_CTRL_OLEDB:
				ctrl_oledb();
				break;
			}

			translation_unit();
		
		}
		else if ( m_lookahead == AIPI_DB_OPEN ||
				  m_lookahead == AIPI_DB_CLOSE 
				  
				  )
		{
			//AfxMessageBox(_T("Entro a OPEN DB"));
			cmd_db_open();
			translation_unit();
		}
		else
		{
			//AfxMessageBox(_T("Sale de ExpParserFile"));
			
			if( g_bExecuteFlag )
			{
				CAipi_Main main;
				main.execute_continue();

			}
			else
			{
				CAipi_ParserFile file;
				file.m_lookahead = m_lookahead;
				file.translation_unit();
				file.endParser();
			}

			/*
			CString str;
			str.Format(_T("ERROR FINAL::: Look Ahead...%d  " ), m_lookahead);
			AfxMessageBox(str);
			
			CAipi_Error err;
			err.displayFileError(ABNORMAL_STOP, WARNING_ERROR, _T("The parser was not able to finish the depuration process. The initialization sintax is incorrect.") );
			*/
			
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
	

	//Save place to jump
	int jump = setjmp(e_buf);
	if( jump == 1 )
	{
		//AfxMessageBox(_T("JUMP"));
		return;
	}

}




//////////////////////////////////////////////////////////////////////////////////////////////////
/// Declaration Parser ////
//////////////////////////////////////////////////////////////////////////////////////////////////
void CAipi_ExpParserFile::declaration_specifiers()
{
	
	if(		m_lookahead == AIPI_VOID 
		||	m_lookahead == AIPI_STRING
		||	m_lookahead == AIPI_CHAR
		||	m_lookahead == AIPI_SHORT
		||	m_lookahead == AIPI_INT
		||	m_lookahead == AIPI_LONG
		||	m_lookahead == AIPI_FLOAT
		||	m_lookahead == AIPI_DOUBLE
	  )
	{
		m_currentType = m_lookahead;
		getTokenizer();
		declaration_specifiers();
		

	}
	
}


void CAipi_ExpParserFile::declaration()
{
	
	declaration_specifiers();
	
	if( m_lookahead == SEMICOLON)
	{
		getTokenizer();
		//AfxMessageBox(_T("SEMICOLON"));
		return;
	}
	
	declarator_list_init();
	getTokenizer();
	
	
	
}



void CAipi_ExpParserFile::declarator_list_init()
{
	declarator_init();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			getTokenizer();
			declarator_init();
		}
	}
	
	//Multidimensional arrays
	if( m_lookahead == OPEN_BRACKET )
	{
		declarator_init();
	}
	

}

void CAipi_ExpParserFile::declarator_init()
{
	declarator_direct();
	
	if( m_lookahead == EQUAL )
	{
		getTokenizer();
		initializer();
		emit_declaration(EQUAL);
	}
	
	

}




void CAipi_ExpParserFile::initializer()
{
	
	expression_assignment();


	//initialize an array 
	//Example: int a[] = { 6, 8 }
	if( m_lookahead == OPEN_BRACE )
	{
		//AfxMessageBox(_T("OPEN BRACE"));
		getTokenizer();
		initializer_list();
		
		getTokenizer();
		

		if( m_lookahead == COMMA)
		{
			//AfxMessageBox(_T("Entro a COMA"));
			getTokenizer();
			initializer_list();
			
			//AfxMessageBox(_T("FIN initializer"));
			
			
		}
	}
	

}

void CAipi_ExpParserFile::initializer_list()
{
	
	initializer();
	//getTokenizer();
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
			getTokenizer();
			initializer_list();
			
		}
	}

	
}




void CAipi_ExpParserFile::declarator_direct()
{
	
		
	if( m_lookahead == IDENTIFIER )
	{
		emit_declaration(IDENTIFIER);
		getTokenizer();
		
	}

	//Function declaration
	if( m_lookahead == OPEN_PARENTHESIS )
	{
		//while( m_lookahead == OPEN_PARENTHESIS)
		//{
			getTokenizer();

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
				 
			 )
			{
				parameter_list();
			}
			
			
			getTokenizer();
			
		//}
	}


	//CString str;
	//str.Format(_T("Look Ahead...%d  " ), m_lookahead);
	//AfxMessageBox(str);
	
	//Array declaration
	if( m_lookahead == OPEN_BRACKET )
	{
		getTokenizer();
		//matchToken(OPEN_BRACKET);
		if( m_lookahead == DIGIT )
		{
			expression_atom_constant();
		}
		getTokenizer();
		//matchToken(CLOSE_BRACKET);
		
	}
	
	

}




void CAipi_ExpParserFile::parameter_declaration()
{
	
	
	declaration_specifiers();
	
	if( m_lookahead == IDENTIFIER || m_lookahead == OPEN_PARENTHESIS || m_lookahead == OPEN_BRACKET)
	{
		declarator_direct();
	}
	
}



void CAipi_ExpParserFile::parameter_list()
{
		
	parameter_declaration();

	if( m_lookahead == COMMA)
	{
		while(m_lookahead == COMMA)
		{
			getTokenizer();
			//matchToken(COMMA);
			parameter_declaration(); 
		}
	}

	

}





//////////////////////////////////////////////////////////////////////////////////////////////
///// Expression Parser /////
/////////////////////////////////////////////////////////////////////////////////////////////
void CAipi_ExpParserFile::expression_statement()
{
	
	if( m_lookahead == SEMICOLON )
	{
		getTokenizer();	
	}

	expression();
	getTokenizer();
	
	
}

void CAipi_ExpParserFile::expression()
{
	expression_logical_or();
	expression_assignment();
	
}


void CAipi_ExpParserFile::expression_assignment()
{
	/*
	if( m_lookahead == IDENTIFIER )
	{
		AfxMessageBox(_T("IDENTIFICADOR"));
		expression_atom_identifier();
	}
	*/
	
	
	if( m_lookahead == EQUAL)
	{
		getTokenizer();
		expression_logical_or();
		emit_expression(EQUAL);
	}
	
	expression_logical_or();
	
			
}


void CAipi_ExpParserFile::expression_logical_or()
{
	expression_logical_and();
		
	while(true)
	{
		if( m_lookahead == OR_OP )
		{
			getTokenizer();
			expression_logical_and();
			emit_expression(OR_OP);
		}
		else
		{
			return;
		}
	}	

}


void CAipi_ExpParserFile::expression_logical_and()
{
	expression_equality();
		
	while(true)
	{
		if( m_lookahead == AND_OP )
		{
			getTokenizer();
			expression_equality();
			emit_expression(AND_OP);
		}
		else
		{
			return;
		}
	}

}

void CAipi_ExpParserFile::expression_equality()
{
	expression_relational();

	while(true)
	{
		if( m_lookahead == ET || m_lookahead == NE )
		{
			int tk = m_lookahead;
			getTokenizer();
			expression_relational();
			emit_expression(tk);
		}
		else
		{
			return;
		}
	}

}


void CAipi_ExpParserFile::expression_relational()
{
	expression_aritmetic();

	while(true)
	{
		if( m_lookahead == LT || m_lookahead == LE || m_lookahead == GT || m_lookahead == GE  )
		{
			int tk = m_lookahead;
			getTokenizer();
			expression_aritmetic();
			emit_expression(tk);
		}
		else
		{
			return;
		}
	}
}



void CAipi_ExpParserFile::expression_aritmetic()
{
	expression_term();
		
	while(true)
	{
		if( m_lookahead == PLUS_SIGN || m_lookahead == MINUS_SIGN )
		{
			int tk = m_lookahead;
			//AfxMessageBox(_T("Arit get Token"));
			getTokenizer();
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


void CAipi_ExpParserFile::expression_term()
{
	expression_factor();
	while(true)
	{
		if( m_lookahead == ASTERIC || m_lookahead == SLASH || m_lookahead == PERCENT )
		{
			int tk = m_lookahead;
			getTokenizer();
			expression_factor();
			emit_expression(tk);
		}
		else
		{
			return;
		}
	}

}


void CAipi_ExpParserFile::expression_unary_plus()
{
	//AfxMessageBox(_T("CASE UNARY"));
	emit_expression(UNARY_PLUS);
	getTokenizer();
	expression_factor();
	emit_expression(UNARY_OP);
}


void CAipi_ExpParserFile::expression_unary_minus()
{
	//AfxMessageBox(_T("UNARY MINUS"));
	emit_expression(UNARY_MINUS);
	getTokenizer();
	expression_factor();
	emit_expression(UNARY_OP);
}

void CAipi_ExpParserFile::expression_unary_increment()
{
		
	//AfxMessageBox(_T("INCREMENT OPERATOR"));
	getTokenizer();
	//It just apply to identifiers
	if( m_lookahead == IDENTIFIER )
	{
		expression_factor();
		emit_expression(INC_OP);
	}	


}

void CAipi_ExpParserFile::expression_unary_decrement()
{
	//AfxMessageBox(_T("DECREMENT OPERATOR"));
	getTokenizer();
	//It just apply to identifiers
	if( m_lookahead = IDENTIFIER )
	{
		expression_factor();
		emit_expression(DEC_OP);
	}
}


/*
void CAipi_ExpParserFile::expression_factor()
{
		
	switch(m_lookahead)
	{
	case IDENTIFIER:
		emit_expression(IDENTIFIER);
		getTokenizer();
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
		getTokenizer();
		break;
	case LITERAL:
		emit_expression(LITERAL);
		getTokenizer();
		break;
	case OPEN_PARENTHESIS:
		getTokenizer();
		expression();
		getTokenizer();
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


void CAipi_ExpParserFile::expression_factor()
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
		getTokenizer();
		expression();
		getTokenizer();
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





void CAipi_ExpParserFile::expression_atom_identifier()
{
	emit_expression(IDENTIFIER);
	getTokenizer();
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
		getTokenizer();
		expression_argument_list();
		getTokenizer();
		//emit_expression(IDENTIFIER_SCRIPT);
	}

}


void CAipi_ExpParserFile::expression_argument_list()
{
	expression_assignment();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			getTokenizer();
			expression_assignment();
		}
	}

}


void CAipi_ExpParserFile::expression_atom_constant()
{
	emit_expression(DIGIT);
	getTokenizer();

}

void CAipi_ExpParserFile::expression_atom_literal()
{
	emit_expression(LITERAL);
	getTokenizer();
}
		



void CAipi_ExpParserFile::type_name()
{
	//CString str;
	//str.Format(_T("SPECIFIER_QUALIFIER_LIST...%d  " ), m_lookahead);
	//AfxMessageBox(str);
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


void CAipi_ExpParserFile::operator_unary()
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

void CAipi_ExpParserFile::operator_assigment()
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


void CAipi_ExpParserFile::cmd_db_open()
{
	getTokenizer();
	//matchToken(AIPI_DB_OPEN);
	getTokenizer();
	//matchToken(OPEN_PARENTHESIS);
	cmd_db_open_parameter_list();
	getTokenizer();
	//matchToken(CLOSE_PARENTHESIS);
	getTokenizer();
	//matchToken(SEMICOLON);

	m_bFlagConnDlg = true;
}


void CAipi_ExpParserFile::cmd_db_open_parameter()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CString sProvider = _T("");

	switch( m_lookahead )
	{
	case AIPI_DB_DNS:
		getTokenizer();
		getTokenizer();
		//matchToken(AIPI_DB_DNS);
		//matchToken(EQUAL);
				
		if( m_lookahead == LITERAL )
		{
			m_dbDNS = pMainFrame->gvTokenizer[m_index-1].getToken();
			g_sDBDNS = m_dbDNS.data();
			//AfxMessageBox(_T("DB_DNS"));
			//AfxMessageBox(m_dbDNS.data());
			g_sDBDNS = m_dbDNS.data();
		
			getTokenizer();
			//matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			long dns = pMainFrame->gvTokenizer[m_index-1].getIntForm();
			//Search in global variables
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
				//Search in local variables
				CAipi_STableLocalLiteral lit;
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
			}
			getTokenizer();
			//matchToken(IDENTIFIER);
		}
		break;
	case AIPI_DB_USER:
		getTokenizer();
		getTokenizer();
		//matchToken(AIPI_DB_USER);
		//matchToken(EQUAL);
		
		if( m_lookahead == LITERAL )
		{
			m_dbUser = pMainFrame->gvTokenizer[m_index-1].getToken();
			g_sDBUser = m_dbUser.data();
			//AfxMessageBox(_T("DB_USER"));
			//AfxMessageBox(m_dbUser.data());
			
			g_sDBUser = m_dbUser.data();
		
			getTokenizer();
			//matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			long user = pMainFrame->gvTokenizer[m_index-1].getIntForm();
			//Search in global variables
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
				//Search in local variables
				CAipi_STableLocalLiteral lit;
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
			}
			getTokenizer();
			//matchToken(IDENTIFIER);
		}
		break;
	case AIPI_DB_PASSWORD:
		getTokenizer();
		getTokenizer();
		//matchToken(AIPI_DB_PASSWORD);
		//matchToken(EQUAL);
		
		if( m_lookahead == LITERAL )
		{
			m_dbPassword = pMainFrame->gvTokenizer[m_index-1].getToken();
			g_sDBPassword = m_dbPassword.data();
			//AfxMessageBox(_T("DB_PASSWORD"));
			//AfxMessageBox(m_dbPassword.data());
			
			g_sDBPassword = m_dbPassword.data();
		
			getTokenizer();
			//matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			long password = pMainFrame->gvTokenizer[m_index-1].getIntForm();
			//Search in global variables
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
				//Search in local variables
				CAipi_STableLocalLiteral lit;
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
			}
			getTokenizer();
			//matchToken(IDENTIFIER);
		}
		break;
	case AIPI_DB_NAME:
		getTokenizer();
		getTokenizer();
		//matchToken(AIPI_DB_NAME);
		//matchToken(EQUAL);
		if( m_lookahead == LITERAL )
		{
			m_dbName = pMainFrame->gvTokenizer[m_index-1].getToken();
			g_sDBName = m_dbName.data();
			//AfxMessageBox(_T("DB_NAME"));
			//AfxMessageBox(m_dbName.data());
			
			getTokenizer();
			//matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			long name = pMainFrame->gvTokenizer[m_index-1].getIntForm();
			//Search in global variables
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
				//Search in local variables
				CAipi_STableLocalLiteral lit;
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
			}
			getTokenizer();
			//matchToken(IDENTIFIER);
		}
		break;
	case AIPI_DB_PROVIDER:
		getTokenizer();
		getTokenizer();
		//matchToken(AIPI_DB_PROVIDER);
		//matchToken(EQUAL);
				
		if( m_lookahead == LITERAL )
		{
			m_dbProvider = pMainFrame->gvTokenizer[m_index-1].getToken();
			g_iDBProvider = SqlSelectDB(m_dbProvider);
			//AfxMessageBox(_T("DB_PROVIDER"));
			//AfxMessageBox(m_dbProvider.data());
			
			getTokenizer();
			//matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			long provider = pMainFrame->gvTokenizer[m_index-1].getIntForm();
			//Search in global variables
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
				//Search in local variables
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
			}
			getTokenizer();
			//matchToken(IDENTIFIER);
		}
		break;
    
	}
		


}


void CAipi_ExpParserFile::cmd_output()
{
	CString currentDocView = _T("");
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	getTokenizer();
	//matchToken(AIPI_OUTPUT);
	AfxMessageBox(_T("EXP PARSER FILE OUTPUT"));
	
	if ( m_lookahead == LEFT_OP )
	{
		while( m_lookahead != SEMICOLON && m_lookahead != _TEOF)
		{
			getTokenizer();
			//matchToken(LEFT_OP);
				
			if( m_lookahead == LITERAL )
			{
				long if_lit = pMainFrame->gvTokenizer[m_index-1].getIntForm();
				tstring s_lit = pMainFrame->gvTokenizer[m_index-1].getToken();	
				CString strLit = s_lit.data(); 
				//matchToken(LITERAL);
				getTokenizer();

				//AfxMessageBox(_T("Antes de escribir"));
	
				CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
				CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
				CRichEditView* pView = (CRichEditView*) pChild->GetActiveView();
				ASSERT(pView);
				//Set output to current document
				pView->GetRichEditCtrl().GetWindowText(currentDocView);
				currentDocView = currentDocView + _T("\r\n") + strLit;
				pView->GetRichEditCtrl().SetWindowText(currentDocView);
	
				
			}
			else if( m_lookahead == IDENTIFIER )
			{
				long if_ident = pMainFrame->gvTokenizer[m_index-1].getIntForm();
				tstring s_ident = pMainFrame->gvTokenizer[m_index-1].getToken();
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
						g_currentVarLoc = UNDEFINE;
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

				//matchToken(IDENTIFIER);
				getTokenizer();
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

		//matchToken(SEMICOLON);
	
	}



}

int CAipi_ExpParserFile::cmd_input()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	//matchToken(AIPI_INPUT);
	getTokenizer();
	if ( m_lookahead == RIGHT_OP )
	{
		while( m_lookahead != SEMICOLON && m_lookahead != _TEOF)
		{
			
			getTokenizer();
			//matchToken(RIGHT_OP);

			if( m_lookahead == IDENTIFIER )
			{
				long if_ident = pMainFrame->gvTokenizer[m_index-1].getIntForm();
				tstring s_ident = pMainFrame->gvTokenizer[m_index-1].getToken();
				long pos = pMainFrame->gvTokenizer[m_index-1].getPos1();
				CString strToken = s_ident.data();
				//AfxMessageBox(_T("OUTPUT ID.............................VAR"));
				//CString str;
				//str.Format(_T("ID IFORM...%d  " ), if_ident);
				//AfxMessageBox(str);
				//AfxMessageBox(strToken);
				
				//Search in numeric variables
				double dId =  NumericVarSearch(if_ident);
				
				if( dId == NOT_FOUND )
				{
					//Search in literal variables
					CString strLit = LiteralVarSearch( if_ident);
					if( strLit != _T("NOT_FOUND") )
					{
						pMainFrame->Cmd_OpenCommandDlgBar();
						g_currentDataCateg = LITERAL;
						g_currentId_IForm = if_ident;
						g_currentLookahead = m_lookahead;
						g_fcurrentPos = pos;

						return AIPI_STOP;
						
					}
					else
					{
						g_currentVarLoc = UNDEFINE;
						CAipi_Error er;
						CString strDesc = _T("Identifier [") + strToken + _T("] was not found.");
						er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
					}
				}
				else
				{
					pMainFrame->Cmd_OpenCommandDlgBar();
					g_currentDataCateg = DIGIT;
					g_currentId_IForm = if_ident;
					g_currentLookahead = m_lookahead;
					g_fcurrentPos = pos;

					return AIPI_STOP;
					
				}
				
				
				getTokenizer();
				//matchToken(IDENTIFIER);
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

		//matchToken(SEMICOLON);

		//Update current index
		
	}

	
return P_SUCCESS;

}



void CAipi_ExpParserFile::cmd_input_continue()
{
	
	//AfxMessageBox(_T("Input Val"));
	//AfxMessageBox(g_currentCmdInput);
	/*
	CString s;
	s.Format(_T("Data Categ...%d  " ), g_currentDataCateg);
	AfxMessageBox(s);
	s.Format(_T("Var Localization...%d  " ), g_currentVarLoc);
	AfxMessageBox(s);
	*/

	if(g_currentDataCateg == LITERAL )
	{
		m_sCurrentId = g_currentCmdInput;
		
		if( g_currentVarLoc == VAR_GLOBAL )
		{
			CAipi_STableGlobalLiteral lt;
			lt.editSTableLiteralValue(g_currentId_IForm, m_sCurrentId);
			lt.printSTableLiteral();
		}
		if( g_currentVarLoc == VAR_LOCAL )
		{
			CAipi_STableLocalLiteral lt;
			lt.editSTableLiteralValue(g_currentId_IForm, m_sCurrentId);
			lt.printSTableLiteral();
		}
	}
	if( g_currentDataCateg == DIGIT )
	{
		//AfxMessageBox(_T("DIGIT"));
		m_dCurrentId = _tcstod(g_currentCmdInput, NULL); 
		
		if( g_currentVarLoc == VAR_GLOBAL )
		{
			//AfxMessageBox(_T("EDIT DATA GLOBAL"));
			CAipi_STableGlobalNumeric nt;
			nt.editSTableNumericValue(g_currentId_IForm, m_dCurrentId);
			nt.printSTableNumeric();
		}
		if( g_currentVarLoc == VAR_LOCAL )
		{
			//AfxMessageBox(_T("EDIT DATA LOCAL"));
			CAipi_STableLocalNumeric nt;
			nt.editSTableNumericValue(g_currentId_IForm, m_dCurrentId);
			nt.printSTableNumeric();
		}
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
	m_index = g_TkzIndex1 + 1;
	m_endIndex = g_TkzIndex2;

	getTokenizer();
	//matchToken(IDENTIFIER);
	getTokenizer();
	//matchToken(SEMICOLON);

	//AfxMessageBox(_T("Out of Cmd Input Continue"));

	ExecCmdSearch(g_currentFiredPM, m_index, m_endIndex);
	/*
	CAipi_RETE_PNode pnode;
	pnode.conflictResolution(g_CRStrategy);
	*/


	//translation_unit();

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

void CAipi_ExpParserFile::ctrl_jukebox()
{
	//AfxMessageBox(_T("ENTRO JUKEBOXDLG"));
	bool bPlayVideo = false;
	bool bShowWnd = false;
	bool bInput = false;
	bool bPath = false;
	CString szPath = _T("");

	getTokenizer();
	//matchToken(AIPI_CTRL_JUKEBOX);
	getTokenizer();
	//matchToken(OPEN_PARENTHESIS);
	
	while( m_lookahead != CLOSE_PARENTHESIS && m_lookahead != _TEOF )
	{
		
		if (	m_lookahead == AIPI_SHOWCTRL 
			||	m_lookahead == AIPI_PLAY
			||  m_lookahead == AIPI_INPUTVAR
			||  m_lookahead == AIPI_PATH
		   )
		{
			
			if(m_lookahead == AIPI_SHOWCTRL )
			{
				getTokenizer();
				//matchToken(AIPI_SHOWCTRL);
				getTokenizer();
				//matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					getTokenizer();
					//matchToken(AIPI_TRUE);
					bShowWnd = true;

					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						getTokenizer();
						//matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					getTokenizer();
					//matchToken(AIPI_FALSE);
					bShowWnd = false;
					
					
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						getTokenizer();
						//matchToken(COMMA);
					}
				}
			}
			else if( m_lookahead == AIPI_PLAY )
			{
				getTokenizer();
				//matchToken(AIPI_PLAY);
				getTokenizer();
				//matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					getTokenizer();
					//matchToken(AIPI_TRUE);
					bPlayVideo = true;
					
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						getTokenizer();
						//matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					getTokenizer();
					//matchToken(AIPI_FALSE);

					bPlayVideo = false;
					
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						getTokenizer();
						//matchToken(COMMA);
					}
				}
				
			}
			else if( m_lookahead == AIPI_INPUTVAR )
			{
				getTokenizer();
				//matchToken(AIPI_INPUTVAR);
				getTokenizer();
				//matchToken(EQUAL);
				
				if( m_lookahead == AIPI_TRUE )
				{
					getTokenizer();
					//matchToken(AIPI_TRUE);
					bInput = true;
					
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						getTokenizer();
						//matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					getTokenizer();
					//matchToken(AIPI_FALSE);
					bInput = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						getTokenizer();
						//matchToken(COMMA);
					}
				}
				
			}
			else if( m_lookahead == AIPI_PATH )
			{
				getTokenizer();
				//matchToken(AIPI_PATH);
				getTokenizer();
				//matchToken(EQUAL);
				CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
				tstring strPath = pMainFrame->gvTokenizer[m_index-1].getToken();
				szPath = strPath.data();
				
				
				if( szPath != _T("") )
				{
					bPath = true;
				}
				getTokenizer();
				//matchToken(LITERAL);
				if( m_lookahead != CLOSE_PARENTHESIS )
				{
					getTokenizer();
					//matchToken(COMMA);
					
				}
			}
		}
		else
		{
			break;
		}
		
		
	}

	getTokenizer();
	//matchToken(CLOSE_PARENTHESIS);
	getTokenizer();
	//matchToken(SEMICOLON);

	/*
	CString str;
	str.Format(_T("ShowWnd...%d  " ), bShowWnd);
	AfxMessageBox(str);
	*/

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

void CAipi_ExpParserFile::ctrl_mediaplayer()
{
	
	//AfxMessageBox(_T("ENTRO MEDIAPLAYERDLG"));
	bool bPlayVideo = false;
	bool bShowWnd = false;
	bool bInput = false;
	bool bPath = false;
	CString szPath = _T("");
	
	//matchToken(AIPI_CTRL_MEDIAPLAYER);
	getTokenizer();
	//matchToken(OPEN_PARENTHESIS);
	getTokenizer();
	
	while( m_lookahead != CLOSE_PARENTHESIS && m_lookahead != _TEOF )
	{
		if (	m_lookahead == AIPI_SHOWCTRL 
			||	m_lookahead == AIPI_PLAY
			||  m_lookahead == AIPI_INPUTVAR
			||  m_lookahead == AIPI_PATH
			)
		{
						
			if(m_lookahead == AIPI_SHOWCTRL )
			{
				//matchToken(AIPI_SHOWCTRL);
				getTokenizer();
				//matchToken(EQUAL);
				getTokenizer();
				if( m_lookahead == AIPI_TRUE )
				{
					//matchToken(AIPI_TRUE);
					getTokenizer();
					bShowWnd = true;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						//matchToken(COMMA);
						getTokenizer();
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					//matchToken(AIPI_FALSE);
					getTokenizer();
					bShowWnd = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						//matchToken(COMMA);
						getTokenizer();
					}
				}
			}
			else if( m_lookahead == AIPI_PLAY )
			{
				//matchToken(AIPI_PLAY);
				getTokenizer();
				//matchToken(EQUAL);
				getTokenizer();
				
				if( m_lookahead == AIPI_TRUE )
				{
					//matchToken(AIPI_TRUE);
					getTokenizer();
					bPlayVideo = true;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						//matchToken(COMMA);
						getTokenizer();
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					//matchToken(AIPI_FALSE);
					getTokenizer();
					bPlayVideo = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						//matchToken(COMMA);
						getTokenizer();
					}
				}
				
			}
			else if( m_lookahead == AIPI_INPUTVAR )
			{
				//matchToken(AIPI_INPUTVAR);
				getTokenizer();
				//matchToken(EQUAL);
				getTokenizer();

				if( m_lookahead == AIPI_TRUE )
				{
					//matchToken(AIPI_TRUE);
					getTokenizer();
					bInput = true;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						//matchToken(COMMA);
						getTokenizer();
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					//matchToken(AIPI_FALSE);
					getTokenizer();
					bInput = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						//matchToken(COMMA);
						getTokenizer();
					}
				}
				
			}
			else if( m_lookahead == AIPI_PATH )
			{
				//matchToken(AIPI_PATH);
				getTokenizer();
				//matchToken(EQUAL);
				getTokenizer();

				CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
				tstring strPath = pMainFrame->gvTokenizer[m_index-1].getToken();
				szPath = strPath.data();
				
				if( szPath != _T("") )
				{
					bPath = true;
				}

				//matchToken(LITERAL);
				getTokenizer();
				if( m_lookahead != CLOSE_PARENTHESIS )
				{
					//matchToken(COMMA);
					getTokenizer();
				}
			}
			
		}
		else
		{
			break;
		}
		
		
	}

	//matchToken(CLOSE_PARENTHESIS);
	getTokenizer();

	//matchToken(SEMICOLON);
	getTokenizer();

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

void CAipi_ExpParserFile::ctrl_imagefilter()
{
	//AfxMessageBox(_T("ENTRO IMAGEFILTERDLG"));
	bool bShowWnd = false;
	bool bInput = false;
	bool bPath = false;
	CString szPath = _T("");
	
	getTokenizer();
	//matchToken(AIPI_CTRL_IMAGEFILTER);
	getTokenizer();
	//matchToken(OPEN_PARENTHESIS);
	
	while( m_lookahead != CLOSE_PARENTHESIS && m_lookahead != NUL )
	{
		if (	m_lookahead == AIPI_SHOWCTRL 
			||	m_lookahead == AIPI_INPUTVAR
			||  m_lookahead == AIPI_PATH
			)
		{
			
			if(m_lookahead == AIPI_SHOWCTRL )
			{
				getTokenizer();
				//matchToken(AIPI_SHOWCTRL);
				getTokenizer();
				//matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					getTokenizer();
					//matchToken(AIPI_TRUE);
					bShowWnd = true;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						getTokenizer();
						//matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					getTokenizer();
					//matchToken(AIPI_FALSE);
					bShowWnd = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						getTokenizer();
						//matchToken(COMMA);
					}
				}
			}
			else if( m_lookahead == AIPI_INPUTVAR )
			{
				getTokenizer();
				//matchToken(AIPI_INPUTVAR);
				getTokenizer();
				//matchToken(EQUAL);
				
				if( m_lookahead == AIPI_TRUE )
				{
					getTokenizer();
					//matchToken(AIPI_TRUE);
					bInput = true;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						getTokenizer();
						//matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					getTokenizer();
					//matchToken(AIPI_FALSE);
					bInput = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						getTokenizer();
						//matchToken(COMMA);
					}
				}
				
			}
			else if( m_lookahead == AIPI_PATH )
			{
				getTokenizer();
				//matchToken(AIPI_PATH);
				getTokenizer();
				//matchToken(EQUAL);
				CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
				tstring strPath = pMainFrame->gvTokenizer[m_index-1].getToken();
				szPath = strPath.data();
				
				
				if( szPath != _T("") )
				{
					bPath = true;
				}
				getTokenizer();
				//matchToken(LITERAL);
				if( m_lookahead != CLOSE_PARENTHESIS )
				{
					getTokenizer();
					//matchToken(COMMA);
				}
			}
		}
		else
		{
			break;
		}
		
	
	}

	getTokenizer();
	//matchToken(CLOSE_PARENTHESIS);
	getTokenizer();
	//matchToken(SEMICOLON);


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

int CAipi_ExpParserFile::ctrl_listoption()
{
	//AfxMessageBox(_T("ENTRO LISTOPTION CTRL"));

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
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

	getTokenizer();
	//matchToken(AIPI_CTRL_LISTOPTION);
	getTokenizer();
	//matchToken(OPEN_PARENTHESIS);
	

	while( m_lookahead != CLOSE_PARENTHESIS && m_lookahead != _TEOF )
	{
		if (	m_lookahead == AIPI_SHOWCTRL 
			||	m_lookahead == AIPI_INSERT
			||  m_lookahead == AIPI_INPUTVAR
			)
		{
			
			if(m_lookahead == AIPI_SHOWCTRL )
			{
				getTokenizer();
				//matchToken(AIPI_SHOWCTRL);
				getTokenizer();
				//matchToken(EQUAL);
				if( m_lookahead == AIPI_TRUE )
				{
					getTokenizer();
					//matchToken(AIPI_TRUE);
					bShowWnd = true;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						getTokenizer();
						//matchToken(COMMA);
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					getTokenizer();						
					//matchToken(AIPI_FALSE);
					bShowWnd = false;
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						getTokenizer();
						//matchToken(COMMA);
					}
				}
			}
			else if( m_lookahead == AIPI_INPUTVAR )
			{
				getTokenizer();
				//matchToken(AIPI_INPUTVAR);
				getTokenizer();
				//matchToken(EQUAL);

				iformTk = pMainFrame->gvTokenizer[m_index-1].getIntForm();
				strTk = pMainFrame->gvTokenizer[m_index-1].getToken();
				szTk = strTk.data();
				posTk = pMainFrame->gvTokenizer[m_index-1].getPos1();
				
								
				if( szTk != _T("") )
				{
					bInput = true;
				}
				
				/*
				//AfxMessageBox(_T("INPUT ID.............................VAR"));
				 CString str;
				str.Format(_T("ID IFORM...%d  " ), iformTk);
				AfxMessageBox(str);
				AfxMessageBox(szTk);
				*/				

				getTokenizer();
				//matchToken(IDENTIFIER); 
				
				
			}
			else if( m_lookahead == AIPI_INSERT )
			{
				
				bInsert = true;

				getTokenizer();
				//matchToken(AIPI_INSERT);
				getTokenizer();
				//matchToken(EQUAL);
				getTokenizer();
				//matchToken(OPEN_BRACE);
				while( m_lookahead != CLOSE_BRACE )
				{
					if( m_lookahead == OPEN_PARENTHESIS )
					{
												
						getTokenizer();
						//matchToken(OPEN_PARENTHESIS);
						
						
						
						
						iformTk = pMainFrame->gvTokenizer[m_index-1].getIntForm();
						tstring strItem = pMainFrame->gvTokenizer[m_index-1].getToken();
						szItem = strItem.data();
						posTk = pMainFrame->gvTokenizer[m_index-1].getPos1();
						
						//AfxMessageBox(_T("AIPI INSERT ITEM:::::::::::::::"));
						//AfxMessageBox(szItem);

						if( szItem != _T("") )
						{
							vListItems.push_back(szItem);
						}
						getTokenizer();
						//matchToken(LITERAL);
						getTokenizer();
						//matchToken(COMMA);

						iformTk = pMainFrame->gvTokenizer[m_index-1].getIntForm();
						tstring strTip = pMainFrame->gvTokenizer[m_index-1].getToken();
						szTip = strTip.data();
						posTk = pMainFrame->gvTokenizer[m_index-1].getPos1();
						
						//AfxMessageBox(_T("AIPI INSERT TIP:::::::::::::::"));
						//AfxMessageBox(szItem);

						if( szTip != _T("") )
						{
							vListTips.push_back(szTip);
							
						}
						else
						{
							vListTips.push_back(_T(""));
						}

						getTokenizer();
						//matchToken(LITERAL);
						getTokenizer();
						//matchToken(CLOSE_PARENTHESIS);
						if( m_lookahead != CLOSE_BRACE)
						{
							getTokenizer();
							//matchToken(COMMA);
						}

					
					}
					else
					{

						iformTk = pMainFrame->gvTokenizer[m_index-1].getIntForm();
						tstring strItem = pMainFrame->gvTokenizer[m_index-1].getToken();
						szItem = strItem.data();
						posTk = pMainFrame->gvTokenizer[m_index-1].getPos1();
						
						//AfxMessageBox(_T("AIPI INSERT ITEM:::::::::::::::"));
						//AfxMessageBox(szItem);

				
						if( szItem != _T("") )
						{
							vListItems.push_back(szItem);
						}
					
						getTokenizer();
						//matchToken(LITERAL);
						if( m_lookahead != CLOSE_BRACE)
						{
							getTokenizer();
							//matchToken(COMMA);
						}
					}
				}
				
				getTokenizer();
				//matchToken(CLOSE_BRACE);
				
				if( m_lookahead != CLOSE_PARENTHESIS )
				{
					getTokenizer();
					//matchToken(COMMA);
				}
			}
			
		}
		else
		{
			break;
		}
		
	
	}


	getTokenizer();
	//matchToken(CLOSE_PARENTHESIS);
	//getTokenizer();
	//matchToken(SEMICOLON);

	
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
				//AfxMessageBox(_T("ITEM:::::::::::::::"));
				//AfxMessageBox(sItem);

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
						//g_currentLookahead = IDENTIFIER;
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
					//g_currentLookahead = IDENTIFIER;
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



void CAipi_ExpParserFile::ctrl_listoption_continue()
{
	
	AfxMessageBox(_T("ListCtrl Continue"));
	CString st;
	st.Format(_T("Lookahead...%d  " ), g_currentLookahead);
	AfxMessageBox(st);
	

	//AxMessageBox(_T("Input Val"));
	//AxMessageBox(g_currentCmdInput);
	/*
	CString s;
	s.Format(_T("Data Categ...%d  " ), g_currentDataCateg);
	AfxMessageBox(s);
	s.Format(_T("Var Localization...%d  " ), g_currentVarLoc);
	AfxMessageBox(s);
	*/
	

	if(g_currentDataCateg == LITERAL )
	{
		m_sCurrentId = g_currentCmdInput;
		
		if( g_currentVarLoc == VAR_GLOBAL )
		{
			CAipi_STableGlobalLiteral lt;
			lt.editSTableLiteralValue(g_currentId_IForm, m_sCurrentId);
			lt.printSTableLiteral();
		}
		if( g_currentVarLoc == VAR_LOCAL )
		{
			CAipi_STableLocalLiteral lt;
			lt.editSTableLiteralValue(g_currentId_IForm, m_sCurrentId);
			//lt.printSTableLiteral();
		}
	}
	if( g_currentDataCateg == DIGIT )
	{
		//AfxMessageBox(_T("DIGIT"));
		m_dCurrentId = _tcstod(g_currentCmdInput, NULL); 
		
		if( g_currentVarLoc == VAR_GLOBAL )
		{
			//AfxMessageBox(_T("EDIT DATA GLOBAL"));
			CAipi_STableGlobalNumeric nt;
			nt.editSTableNumericValue(g_currentId_IForm, m_dCurrentId);
			//nt.printSTableNumeric();
		}
		if( g_currentVarLoc == VAR_LOCAL )
		{
			//AfxMessageBox(_T("EDIT DATA LOCAL"));
			CAipi_STableLocalNumeric nt;
			nt.editSTableNumericValue(g_currentId_IForm, m_dCurrentId);
			//nt.printSTableNumeric();
		}
	}


	getTokenizer();
	//matchToken(SEMICOLON);

	m_lookahead = g_currentLookahead;
	if( m_lookahead == _TEOF )
	{
		AfxMessageBox(_T("Afuera"));
		return;
	}
	

	/*
	CString str;
	str.Format(_T("Look Ahead...%d  " ), m_lookahead);
	AfxMessageBox(str);
	
	
	m_index = g_TkzIndex1 + 1;
	m_endIndex = g_TkzIndex2;

	
	//AfxMessageBox(_T("Out of List Option Input Continue"));
	
	ExecCmdSearch(g_currentFiredPM, m_index, m_endIndex);
	*/
	/*
	CAipi_RETE_PNode pnode;
	pnode.conflictResolution(g_CRStrategy);
	*/
	
	
	//translation_unit();

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

void CAipi_ExpParserFile::ctrl_oledb()
{
	//matchToken(AIPI_CTRL_OLEDB);
	getTokenizer();
	//matchToken(OPEN_PARENTHESIS);
	getTokenizer();
	
	while( m_lookahead != CLOSE_PARENTHESIS && m_lookahead != NUL )
	{
		if (	m_lookahead == AIPI_SHOWCTRL 
			||	m_lookahead == AIPI_INPUTVAR
			||  m_lookahead == AIPI_SHOWTABLES
			)
		{
			
			if(m_lookahead == AIPI_SHOWCTRL )
			{
				//matchToken(AIPI_SHOWCTRL);
				getTokenizer();
				//matchToken(EQUAL);
				getTokenizer();

				if( m_lookahead == AIPI_TRUE )
				{
					//matchToken(AIPI_TRUE);
					getTokenizer();
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						//matchToken(COMMA);
						getTokenizer();
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					//matchToken(AIPI_FALSE);
					getTokenizer();
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						//matchToken(COMMA);
						getTokenizer();
					}
				}
			}
			else if( m_lookahead == AIPI_SHOWTABLES )
			{
				//matchToken(AIPI_SHOWTABLES);
				getTokenizer();
				//matchToken(EQUAL);
				getTokenizer();
				if( m_lookahead == AIPI_TRUE )
				{
					//matchToken(AIPI_TRUE);
					getTokenizer();
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						//matchToken(COMMA);
						getTokenizer();
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					//matchToken(AIPI_FALSE);
					getTokenizer();
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						//matchToken(COMMA);
						getTokenizer();
					}
				}
				
			}
			else if( m_lookahead == AIPI_INPUTVAR )
			{
				//matchToken(AIPI_INPUTVAR);
				getTokenizer();
				//matchToken(EQUAL);
				getTokenizer();

				if( m_lookahead == AIPI_TRUE )
				{
					//matchToken(AIPI_TRUE);
					getTokenizer();
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						//matchToken(COMMA);
						getTokenizer();
					}
					
				}
				else if ( m_lookahead == AIPI_FALSE)
				{
					//matchToken(AIPI_FALSE);
					getTokenizer();
					if( m_lookahead != CLOSE_PARENTHESIS )
					{
						//matchToken(COMMA);
						getTokenizer();
					}
				}
				
			}
		}
		else
		{
			break;
		}

		
		
	
	}

	//matchToken(CLOSE_PARENTHESIS);
	getTokenizer();


}



void CAipi_ExpParserFile::cmd_db_open_parameter_list()
{
	cmd_db_open_parameter();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			getTokenizer();
			//matchToken(COMMA);
			cmd_db_open_parameter();
		}
	}


}

void CAipi_ExpParserFile::cmd_db_close()
{
	getTokenizer();
	//matchToken(AIPI_DB_CLOSE);

}


