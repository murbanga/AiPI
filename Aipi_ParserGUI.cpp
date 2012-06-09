// Aipi_ParserGUI.cpp: implementation of the CAipi_ParserGUIGUI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_ParserGUI.h"

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

CAipi_ParserGUI::CAipi_ParserGUI()
{
	
	m_currentCF = 0;
	m_currentWeight = 0;
	m_currentRel = EQ;
	m_currentCmd = UNDEFINE;
	m_currentCateg = K_K_K;
	m_bNewProduction = false;

	g_currentParserClass = PARSER_GUI;
	

}

CAipi_ParserGUI::~CAipi_ParserGUI()
{

}


CString CAipi_ParserGUI::LiteralVarSearch(long iform)
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
			//AfxMessageBox(_T("Encontro Variable Literal Local"));
			m_currentVarLoc  = VAR_LOCAL;
			
			CString strLit = lit.m_STLitValue.data();
			//AfxMessageBox(strLit);
			
			return strLit; 
		}
	}
	else
	{
		//AfxMessageBox(_T("Encontro Variable Literal Global"));
		m_currentVarLoc  = VAR_GLOBAL;
		
		CString strLit = lit.m_STGLitValue.data();
		//AfxMessageBox(strLit);
		
		return strLit;
	}

return _T("NOT_FOUND");
	
}



double CAipi_ParserGUI::NumericVarSearch(long iform)
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
			//AfxMessageBox(_T("Encontro Variable Numerica Local"));
			m_currentVarLoc  = VAR_LOCAL;
			double val = num.m_STLNumValue;
			CString str;
			str.Format(_T("%f"), val);
			AfxMessageBox(str);
			return val;
		}
	}
	else
	{
		//AfxMessageBox(_T("Encontro Variable Numerica Global"));
		m_currentVarLoc  = VAR_GLOBAL;
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



bool CAipi_ParserGUI::ScriptLoadCode(long nStartSel, long nEndSel, int line, CString lang, CString code, CString name) 
{
	
	m_ScriptObj.Reset();
	m_ScriptObj.SetLanguage( lang );
		
	//AfxMessageBox(code);
	bool bError  = m_ScriptObj.AddScript( code );
	
	/*
	CString str;
	str.Format(_T("nStartSel...%d  " ), nStartSel);
	AfxMessageBox(str);
	str.Format(_T("nEndSel...%d  " ), nEndSel);
	AfxMessageBox(str);
	
	str.Format(_T("bError...%d  " ), bError);
	AfxMessageBox(str);
	*/

	if ( bError == false)
	{
		//CString strError = m_ScriptObj.GetErrorString();
		//AfxMessageBox(strError);
		ScriptDisplayError(nStartSel, line, name);
	}
	
return bError;	
}


void CAipi_ParserGUI::ScriptDisplayError(long nStartSel, int line, CString name)
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
	int nErrLine = nStartScriptLine + nErrScriptLine;

		
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
		pMainFrame->m_wndOutputTabView.AddListSubItem2(Item, 0, 5, lpsErrCode);
	}
	
	m_ScriptObj.ClearError();


}


int CAipi_ParserGUI::matchToken(int tk )
{
	CString str;
	//str.Format(_T("Incomming Token...%d  " ), tk);
	//AfxMessageBox(str);
	
	
	//wsprintf(buffer, _T("Letra: %c"), tk);
	//AfxMessageBox(buffer);
	
	//str.Format(_T("Look Ahead...%d  " ), m_lookahead);
	//AfxMessageBox(str);
		
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
		return SINTAX_ERROR;
	}

	
	CAipi_Lexer lex;
	++g_currentPos;
	m_lookahead = lex.addTokenizerGUI();
	//AfxMessageBox(_T("LEXER TOKEN......"));
	//AfxMessageBox(lex.m_sToken);
	
	
	if( m_lookahead == COMMENT )
	{
		do
		{
			++g_currentPos;
			m_lookahead = lex.addTokenizerGUI();
		
		}while (m_lookahead == COMMENT && m_lookahead != NUL  );
	}
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, g_currentPos*100/m_endPos);
	

	if( m_lookahead == NUL )
		return NUL;

return P_SUCCESS;
}



void CAipi_ParserGUI::emit_rule(int tk)
{
	if( tk == AIPI_RULE )
	{
		CAipi_PM pm;
		pm.addPM(m_currentRuleIForm, m_currentRule, m_currentCF, m_currentWeight);
		
	}
	else if ( tk == AIPI_LHS )
	{
		
		//This saves temporarily the elements variables in a set struture
		//this way, the repeated variables in a production are not saved.  
		//gsIVar: Save variables for Identifiers elements
		//gsAVar: Save variables for Attributes elements
		//gsVVar: Save variables for Values elements

		//NOTE: this process can be done in the Alpha Memory class
		//Methods: constantTestEQ, constantTestET, constantTestLT, etc...
		if(	m_categId == AIPI_K && m_categAttr == AIPI_K && m_categVal == AIPI_K )
		{
			m_currentCateg = K_K_K;
		}
		else if( m_categId == AIPI_ID && m_categAttr == AIPI_AT && m_categVal == AIPI_VL )
		{
			m_currentCateg = ID_AT_VL;
			
			CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			
			pMainFrame->gsIVar.insert(m_currentId);
			pMainFrame->gsAVar.insert(m_currentAttr);
			pMainFrame->gsVVar.insert(m_currentVal);
			
			/*
			pm.addPM_IVar(m_currentRuleIForm, m_currentId);
			pm.addPM_AVar(m_currentRuleIForm, m_currentAttr);
			pm.addPM_VVar(m_currentRuleIForm, m_currentVal);
			*/
			/*
			pm.addPM_IVarIForm(m_currentRuleIForm, m_currentIdIForm);
			pm.addPM_AVarIForm(m_currentRuleIForm, m_currentAttrIForm);
			pm.addPM_VVarIForm(m_currentRuleIForm, m_currentValIForm);
			*/

		}
		else if ( m_categId == AIPI_K && m_categAttr == AIPI_AT && m_categVal == AIPI_VL )
		{
			m_currentCateg = K_AT_VL;

			CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			pMainFrame->gsAVar.insert(m_currentAttr);
			pMainFrame->gsVVar.insert(m_currentVal);
			/*
			pm.addPM_AVar(m_currentRuleIForm, m_currentAttr);
			pm.addPM_VVar(m_currentRuleIForm, m_currentVal);
			*/
			/*
			pm.addPM_AVarIForm(m_currentRuleIForm, m_currentAttrIForm);
			pm.addPM_VVarIForm(m_currentRuleIForm, m_currentValIForm);
			*/
		}
		else if ( m_categId == AIPI_ID && m_categAttr == AIPI_K && m_categVal == AIPI_VL )
		{
			m_currentCateg = ID_K_VL;
			CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			pMainFrame->gsIVar.insert(m_currentId);
			pMainFrame->gsVVar.insert(m_currentVal);
			
			/*
			pm.addPM_IVar(m_currentRuleIForm, m_currentId);
			pm.addPM_VVar(m_currentRuleIForm, m_currentVal);
			*/
			/*
			pm.addPM_IVarIForm(m_currentRuleIForm, m_currentIdIForm);
			pm.addPM_VVarIForm(m_currentRuleIForm, m_currentValIForm);
			*/
		}
		else if( m_categId == AIPI_ID &&  m_categAttr == AIPI_AT && m_categVal == AIPI_K )
		{
			m_currentCateg = ID_AT_K;
			CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			pMainFrame->gsIVar.insert(m_currentId);
			pMainFrame->gsAVar.insert(m_currentAttr);
			
			/*
			pm.addPM_IVar(m_currentRuleIForm, m_currentId);
			pm.addPM_AVar(m_currentRuleIForm, m_currentAttr);
			*/
			/*
			pm.addPM_IVarIForm(m_currentRuleIForm, m_currentIdIForm);
			pm.addPM_AVarIForm(m_currentRuleIForm, m_currentAttrIForm);
			*/
			
		}

		else if ( m_categId == AIPI_K && m_categAttr == AIPI_K && m_categVal == AIPI_VL )
		{
			m_currentCateg = K_K_VL;
			CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			pMainFrame->gsVVar.insert(m_currentVal);

			//pm.addPM_VVar(m_currentRuleIForm, m_currentVal);
			
			//pm.addPM_VVarIForm(m_currentRuleIForm, m_currentValIForm);
		}
		else if ( m_categId == AIPI_K && m_categAttr == AIPI_AT && m_categVal == AIPI_K )
		{
			m_currentCateg = K_AT_K;
			CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			pMainFrame->gsAVar.insert(m_currentAttr);
			
			//pm.addPM_AVar(m_currentRuleIForm, m_currentAttr);
			
			//pm.addPM_AVarIForm(m_currentRuleIForm, m_currentAttrIForm);
			
		}
		else if( m_categId == AIPI_ID &&  m_categAttr == AIPI_K && m_categVal == AIPI_K )
		{
			m_currentCateg = ID_K_K;
			CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			pMainFrame->gsIVar.insert(m_currentId);
			
			//pm.addPM_IVar(m_currentRuleIForm, m_currentId);

			//pm.addPM_IVarIForm(m_currentRuleIForm, m_currentIdIForm);
			
		}

		++g_currentLHS;
		
		CAipi_LHS lhs;
		lhs.addLHSIForm(g_currentLHS, m_currentIdIForm, m_currentAttrIForm, m_currentValIForm, m_currentId, m_currentAttr, m_currentVal, m_currentRel, m_currentRuleIForm, m_currentCateg);
			
	}
	else if( tk == AIPI_RHS )
	{
		//Check for a new different production
		if( m_bNewProduction )
		{
			
			/*
			CString str;
			str.Format(_T("CURRENT RULE IFORM...%d  " ), m_currentRuleIForm);
			AfxMessageBox(str);
			*/
			
			//This function saves the variables of each element with his respective production
			//The structure involves are:
			//gmmPM_IVar: Saves the production with the respective variables of Identifiers
			//gmmPM_AVar: Saves the production with the respective variables of Attributes
			//gmmPM_VVar: Saves the production with the respective variables of Values
			//NOTE : This process could be done in Alpha Memory functions:constantTestEQ, constantTestET...

			CAipi_PM pm;
			pm.fillPM_Vars(m_currentRuleIForm);
			m_bNewProduction = false;
		}


		//static int rhsKey;
		
		CAipi_STableClass stclass;
		int type = S_S_S;

		
		/*
		AfxMessageBox(_T("EMIT RULE RHS"));
		AfxMessageBox(m_currentId.data());
		AfxMessageBox(m_currentAttr.data());
		*/

		int attr_type = stclass.findAttrType(m_currentAttrIForm, m_currentIdIForm);
		if( attr_type != NOT_FOUND )
		{
			//AfxMessageBox(_T("Encontrado"));
			switch( attr_type)
			{
			case AIPI_STRING:
				type = S_S_S;
				break;
			case AIPI_INT:
				type = S_S_I;
				break;
            case AIPI_LONG:
				type = S_S_L;
				break;
			case AIPI_FLOAT:
				type = S_S_F;
				break;
			case AIPI_DOUBLE:
				type = S_S_D;
				break;
			}
		}
		else
		{
			//Semantic error
			/*
			CAipi_Error err;
			CString strAttr = m_currentAttr.data();
			CString  strDesc = _T("No class was found for identifier [") + strAttr + _T("]."); 
			err.displayGUIError(UNKNOW_TYPE, SEMANT_ERROR, strDesc);
			*/
		}

		++g_currentRHS;

		CAipi_RHS rhs;
		rhs.addRHSIForm(g_currentRHS, m_currentIdIForm, m_currentAttrIForm, m_currentValIForm, m_currentId, m_currentAttr, m_currentVal, m_currentRuleIForm, m_currentCmd );
		
		
	}

	else if( tk == AIPI_RHSCMD )
	{

		++g_currentRHS;

		CAipi_RHS rhs;
		rhs.addRHSIForm(g_currentRHS, UNDEFINE, UNDEFINE, UNDEFINE, _T(" - "), _T(" - "), _T(" - "), m_currentRuleIForm, m_currentCmd );
		
	}

	else if( tk == AIPI_WM )
	{
		//static int rhsKey;
		//static int timetag;
		CAipi_STableClass stclass;
		int type = S_S_S;

		
		//AfxMessageBox(_T("EMIT RULE"));
		//AfxMessageBox(m_currentId.data());
		//AfxMessageBox(m_currentAttr.data());
		

		int attr_type = stclass.findAttrType(m_currentAttrIForm, m_currentIdIForm);
		if( attr_type != NOT_FOUND )
		{
			//AfxMessageBox(_T("Encontrado"));
			switch( attr_type)
			{
			case AIPI_STRING:
				type = S_S_S;
				break;
			case AIPI_INT:
				type = S_S_I;
				break;
            case AIPI_LONG:
				type = S_S_L;
				break;
			case AIPI_FLOAT:
				type = S_S_F;
				break;
			case AIPI_DOUBLE:
				type = S_S_D;
				break;
			}
		}
		else
		{
			//Semantic error
			/*
			CAipi_Error err;
			CString strAttr = m_currentAttr.data();
			CString  strDesc = _T("No class was found for identifier [") + strAttr + _T("]."); 
			err.displayGUIError(UNKNOW_TYPE, SEMANT_ERROR, strDesc);
			*/
			//return;
		}

		++g_currentWM;
		++g_currentTimeTag;

		CAipi_WM wm;
		wm.addWMIForm(g_currentWM, m_currentIdIForm, m_currentAttrIForm, m_currentValIForm, m_currentId, m_currentAttr, m_currentVal, type, g_currentTimeTag);
	}

	

}






void CAipi_ParserGUI::initParser()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Syntax analyzer..."), RGB(0,0,0), TRUE);

		
	g_currentTimeTag = 0;
	g_currentId_IForm = 1000;

	CAipi_Lexer lex;
	m_lookahead = lex.addTokenizerGUI();
	m_endPos = lex.getGUIDocumentLen();
	g_currentDocEndPos = m_endPos;
	
	if( m_lookahead == COMMENT )
	{
		do
		{
			++g_currentPos;
			m_lookahead = lex.addTokenizerGUI();
		
		}while (m_lookahead == COMMENT && m_lookahead != NUL );
	}

	
	translation_unit();


	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);


	
	for( int i = 0; i < pMainFrame->g_vDirectives.size(); ++i )
	{
		CString filePath = pMainFrame->g_vDirectives.at(i);
		//AfxMessageBox(filePath);
		CAipi_ParserFile fp;
		fp.initParser(filePath);
		
	}

	pMainFrame->g_vDirectives.clear();
	

}

/////////////////////////////////////////////////////////////////////

	////  AIPI LANGUAGE PARSER ////

//////////////////////////////////////////////////////////////////////

void CAipi_ParserGUI::translation_unit()
{
	/*
	AfxMessageBox(_T("Translation Unit"));
	CString str;
	str.Format(_T("Look Ahead...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if( m_lookahead != NUL )
	{
		if( m_lookahead == COMMENT )
		{
			
			matchToken(COMMENT);
			translation_unit();
		}
		else if( m_lookahead == AIPI_CLASS )
		{
			class_element_list();
			translation_unit();
		}
		else if( m_lookahead == AIPI_ASSERT || m_lookahead == AIPI_RETRACT || m_lookahead == AIPI_MODIFY )
		{
			wm_element_list();
			translation_unit();

		}
		else if(	m_lookahead == AIPI_VOID 
				||	m_lookahead == AIPI_CHAR
				||	m_lookahead == AIPI_STRING
				||	m_lookahead == AIPI_SHORT
				||	m_lookahead == AIPI_INT
				||	m_lookahead == AIPI_LONG
				||	m_lookahead == AIPI_FLOAT
				||	m_lookahead == AIPI_DOUBLE
			  )	
		{
			
			CAipi_ExpParserGUIGlobal glob;
			glob.m_lookahead =  m_lookahead;
			glob.initExpParser();

			//declaration();
			//translation_unit();
		}
		
		else if ( m_lookahead == AIPI_OUTPUT)
		{
			
			CAipi_ExpParserGUIGlobal glob;
			glob.m_lookahead = m_lookahead;
			glob.initExpParser();
			
			//cmd_output();
			//translation_unit();
		}
		else if ( m_lookahead == AIPI_INPUT)
		{
			
			CAipi_ExpParserGUIGlobal glob;
			glob.m_lookahead = m_lookahead;
			glob.initExpParser();
			
			//cmd_input();
			//translation_unit();
		}

		else if( m_lookahead == AIPI_DISPLAYCTRL )
		{
			CAipi_ExpParserGUIGlobal glob;
			glob.m_lookahead =  m_lookahead;
			glob.initExpParser();


		}
		else if( m_lookahead == AIPI_DB_OPEN )
		{
			CAipi_ExpParserGUIGlobal glob;
			glob.m_lookahead = m_lookahead;
			glob.initExpParser();
			//cmd_db_open();
			//translation_unit();
		}
		else if( m_lookahead == AIPI_DB_CLOSE )
		{
			cmd_db_close();
			translation_unit();
		}
		else if( m_lookahead == AIPI_SQLQUERY )
		{
			script_sql();
			translation_unit();
		}
		else if( m_lookahead == JS_FUNCTION )
		{
			script_js_function_definition();
			translation_unit();
		}
		else if( m_lookahead == VBS_FUNCTION )
		{
			script_vbs_function_definition();
			translation_unit();
		}
		else if( m_lookahead == LT )
		{
			script_definition();
			translation_unit();
		}
		else if (		m_lookahead == IDENTIFIER
					||	m_lookahead == DIGIT
				)
		{
			//AfxMessageBox(_T("Expression"));
			expression_statement();
			translation_unit();
		}
		else if( m_lookahead == AIPI_RULE )
		{
			rule_element_list();
			translation_unit();
		}
		else if( m_lookahead == NUMBER_SIGN )
		{
			directive_list();
			translation_unit();
		}
		else if( m_lookahead == AIPI_STRATEGY )
		{
			cr_strategy();
			translation_unit();
		}
		else
		{
			//CAipi_Error err;
			//err.displayGUIError(ABNORMAL_STOP, WARNING_ERROR, _T("The parser was not able to finish the depuration process. The initialization sintax is incorrect.") );
			
			
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


void CAipi_ParserGUI::script_translation_unit()
{
	/*
	AfxMessageBox(_T("Translation Unit"));
	CString str;
	str.Format(_T("Look Ahead...%d  " ), m_lookahead);
	AfxMessageBox(str);
	*/

	if( m_lookahead != NUL )
	{
		if( m_lookahead == COMMENT )
		{
			
			matchToken(COMMENT);
			script_translation_unit();
		}
		else if(	m_lookahead == AIPI_VOID 
				||	m_lookahead == AIPI_CHAR
				||	m_lookahead == AIPI_STRING
				||	m_lookahead == AIPI_SHORT
				||	m_lookahead == AIPI_INT
				||	m_lookahead == AIPI_LONG
				||	m_lookahead == AIPI_FLOAT
				||	m_lookahead == AIPI_DOUBLE
			  )	
		{
			
			declaration();
			script_translation_unit();
		}
		else if ( m_lookahead == AIPI_OUTPUT )
		{
			cmd_output();
			script_translation_unit();

		}
			else if ( m_lookahead == AIPI_INPUT )
		{
			cmd_input();
			script_translation_unit();

		}
		else if( m_lookahead == AIPI_DB_OPEN )
		{
			cmd_db_open();
			script_translation_unit();
		}
		else if( m_lookahead == AIPI_DB_CLOSE )
		{
			cmd_db_close();
			script_translation_unit();
		}
		else if( m_lookahead == AIPI_SQLQUERY )
		{
			script_sql();
			script_translation_unit();
		}
		else if( m_lookahead == JS_FUNCTION )
		{
			script_js_function_definition();
			script_translation_unit();
		}
		else if( m_lookahead == VBS_FUNCTION )
		{
			script_vbs_function_definition();
			script_translation_unit();
		}
		else if( m_lookahead == LT )
		{
			script_definition();
			script_translation_unit();
		}
		else if (		m_lookahead == IDENTIFIER
					||	m_lookahead == DIGIT
				)
		{
			//AfxMessageBox(_T("Expression"));
			expression_statement();
			script_translation_unit();
		}
		else
		{
			translation_unit();
			//CAipi_Error err;
			//err.displayGUIError(ABNORMAL_STOP, WARNING_ERROR, _T("The parser was not able to finish the depuration process. The initialization sintax is incorrect.") );
			
			
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




//////////////////////////////////////////////////////////////////////
/// Directive functions///
//////////////////////////////////////////////////////////////////////

void CAipi_ParserGUI::directive_list()
{
	if( m_lookahead == NUMBER_SIGN )
	{
		directive();
		directive_list();
	}

}



void CAipi_ParserGUI::directive()
{
	if( m_lookahead == NUMBER_SIGN )
	{
		matchToken( NUMBER_SIGN );
		matchToken( AIPI_INCLUDE );
		//matchToken(LT);
		
		CAipi_Tokenizer tkz;
		CString strFileName =  tkz.v_lastToken().data();
		CString strExt = strFileName.Right(3);
		
		
		//AfxMessageBox(strFileName);
		//AfxMessageBox(strFileName);
		//AfxMessageBox(strExt);
		if( strExt != _T("knw"))
		{
			CAipi_Error err;
			err.displayGUIError(FILE_READ, STOP_ERROR,_T("ERROR: The file  (") + strFileName + _T(") could not be linked. Check if the file extension in correct."));
			return;
		}
		else
		{
			if( g_includeDirective)
			{
				CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
				pMainFrame->g_vDirectives.push_back(strFileName);
			}
		}
		
		
		matchToken(LITERAL);
		//matchToken(GT);
	}

		/*
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
			matchToken(SQL_EXT);
			break;
		
		
		}
		*/
		
		

	
	
}


void CAipi_ParserGUI::cr_strategy()
{
	matchToken(AIPI_STRATEGY);
	matchToken(COLON);
	switch( m_lookahead )
	{
	case AIPI_CR_PRIORITY:
		matchToken(AIPI_CR_PRIORITY);
		g_CRStrategy = AIPI_CR_PRIORITY;
		break;
	case AIPI_CR_RECENCY:
		matchToken(AIPI_CR_RECENCY);
		g_CRStrategy = AIPI_CR_RECENCY;
		break;
	case AIPI_CR_SPECIFICITY:
		matchToken(AIPI_CR_SPECIFICITY);
		g_CRStrategy = AIPI_CR_SPECIFICITY;
		break;
	case AIPI_CR_ORDER:
		matchToken(AIPI_CR_ORDER);
		g_CRStrategy = AIPI_CR_ORDER;
		break;
    case AIPI_CR_LEX:
		matchToken(AIPI_CR_LEX);
		g_CRStrategy = AIPI_CR_LEX;
		break;
    case AIPI_CR_MEA:
		matchToken(AIPI_CR_MEA);
		g_CRStrategy = AIPI_CR_MEA;
		break;
	}


}

////////////////////////////////////////////////////////////////////
/// Class functions ///
////////////////////////////////////////////////////////////////////

int CAipi_ParserGUI::attribute_type()
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


void CAipi_ParserGUI::class_attr_declaration(long class_iform, tstring class_name)
{

	
	if(		m_lookahead == AIPI_CHAR
		||	m_lookahead == AIPI_STRING
		||	m_lookahead == AIPI_SHORT
		||	m_lookahead == AIPI_INT
		||	m_lookahead == AIPI_LONG
		||	m_lookahead == AIPI_FLOAT
		||	m_lookahead == AIPI_DOUBLE
	  )
	{
		int attr_type = m_lookahead;
		matchToken(m_lookahead);

		CAipi_Tokenizer tkz;
		tstring attr_name = tkz.v_lastToken();
		long attr_iform = tkz.v_lastIntFormToken();
		/*
		CAipi_Symbol sym;
		long attr_iform = sym.findId_IntForm(attr_name);
		if( attr_iform == NOT_FOUND )
		{
			attr_iform = tkz.v_lastIntFormToken();
		}
		*/
		//AfxMessageBox(_T("ATTRIBUTE NAME"));
		//AfxMessageBox(attr_name.data());
		
		matchToken(IDENTIFIER);
				
		CAipi_STableClass stclass;
		stclass.addSymbol(attr_iform, attr_name, attr_type, class_iform, class_name);
	}



	/*
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
	*/	

}


void CAipi_ParserGUI::class_attr_declaration_list(long class_iform, tstring class_name)
{
	
	class_attr_declaration(class_iform, class_name);
	
	if( m_lookahead == SEMICOLON )
	{
		while ( m_lookahead == SEMICOLON )
		{
			matchToken(SEMICOLON);
			class_attr_declaration_list(class_iform, class_name);
		}
	}

}

void CAipi_ParserGUI::class_element()
{
	if( m_lookahead == AIPI_CLASS)
	{
		matchToken(AIPI_CLASS);

		CAipi_Tokenizer tkz;
		tstring class_name = tkz.v_lastToken();
		long class_iform = tkz.v_lastIntFormToken();
		
		//AfxMessageBox(_T("CLASS NAME"));
		//AfxMessageBox(class_name.data());

		matchToken(IDENTIFIER);
		matchToken( OPEN_BRACE);
		class_attr_declaration_list(class_iform, class_name);
		matchToken(CLOSE_BRACE);
	}

}


void CAipi_ParserGUI::class_element_list()
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


void CAipi_ParserGUI::rule_element()
{
	CAipi_Tokenizer tkz;

	matchToken(AIPI_RULE);

	m_currentRule = tkz.v_lastToken();
	m_currentRuleIForm = tkz.v_lastIntFormToken();
	
	//AfxMessageBox(_T("RULE NAME"));
	//AfxMessageBox(m_currentRule.data());

	matchToken(LITERAL);
	matchToken(OPEN_PARENTHESIS);
	rule_parameter_list();
	matchToken(CLOSE_PARENTHESIS);
	
	emit_rule(AIPI_RULE);

	matchToken(OPEN_BRACE);
	
	lhs_start();
	lhs_element_list();
	m_bNewProduction = true;
	rhs_start();
	
	rhs_element_list();
	matchToken(CLOSE_BRACE);
	
	
	
}



void CAipi_ParserGUI::rule_element_list()
{
	rule_element();
	if( m_lookahead == AIPI_RULE )
	{
		rule_element_list();
	}

}


void CAipi_ParserGUI::rule_parameter()
{
		
	if( m_lookahead == AIPI_CF)
	{
		matchToken(AIPI_CF);
		matchToken(COLON);
		
		CAipi_Tokenizer tkz;
		tstring cf = tkz.v_lastToken();
		m_currentCF =_tcstod(cf.data(), NULL);
		
		//AfxMessageBox(_T("RULE CF"));
		//AfxMessageBox(cf.data());

		matchToken(DIGIT);
	}

	if( m_lookahead == AIPI_WEIGHT)
	{
		matchToken(AIPI_WEIGHT);
		matchToken(COLON);
		
		CAipi_Tokenizer tkz;
		tstring w = tkz.v_lastToken();
		m_currentWeight = _ttoi(w.data());
		
		//AfxMessageBox(_T("RULE WEIGHT"));
		//AfxMessageBox(w.data());

		matchToken(DIGIT);
	}


}


void CAipi_ParserGUI::rule_parameter_list()
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

void CAipi_ParserGUI::lhs_start()
{
	if( m_lookahead == AIPI_IF )
	{
		matchToken(AIPI_IF);
	}
}

void CAipi_ParserGUI::lhs_connector()
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

void CAipi_ParserGUI::lhs_element()
{
	
	if( m_lookahead == OPEN_PARENTHESIS )
	{
		matchToken(OPEN_PARENTHESIS);
		lhs_element_list();
		matchToken(CLOSE_PARENTHESIS);
		lhs_connector();
	}
	
	////This is for variables taken with the CListOptionCtrl or CCmdInput
	if( m_lookahead == OR_BIT )
	{
		matchToken(OR_BIT);
		
		CAipi_Tokenizer tkz;

		m_categId = AIPI_K;
		m_currentId =  tkz.v_lastToken();
		m_currentIdIForm = tkz.v_lastIntFormToken();
		
		CString sID = LiteralVarSearch(m_currentIdIForm);
		if( sID != _T("NOT_FOUND") )
		{
			m_currentId = sID.GetBuffer(0);
		}
		else
		{
			g_currentVarLoc = UNDEFINE;
			CAipi_Error er;
			CString strDesc = _T("Identifier [")+ sID + _T("] was not found.");
			er.displayGUIError(NOT_DECLARE, SEMANT_ERROR, strDesc);
		}
		//CAipi_Symbol sym;
		//m_currentIdIForm = sym.findId_IntForm(m_currentId);


		
		//AfxMessageBox(_T("CLASS ID"));
		//AfxMessageBox(m_currentId.data());

		matchToken(IDENTIFIER);
		matchToken(OR_BIT);
		lhs_attribute_value_list();
		lhs_connector();
		matchToken(IDENTIFIER);
	}


	if( m_lookahead == IDENTIFIER )
	{
		CAipi_Tokenizer tkz;
		
		m_categId = AIPI_K;
		m_currentId =  tkz.v_lastToken();
		m_currentIdIForm = tkz.v_lastIntFormToken();
		//CAipi_Symbol sym;
		//m_currentIdIForm = sym.findId_IntForm(m_currentId);
		
		//AfxMessageBox(_T("CLASS ID"));
		//AfxMessageBox(m_currentId.data());
		
		
		matchToken(IDENTIFIER);
		lhs_attribute_value_list();
		lhs_connector();
	}

	else if( m_lookahead == AIPI_VAR )
	{
		CAipi_Tokenizer tkz;
		
		m_categId = AIPI_ID;
		m_currentId =  tkz.v_lastToken();
		m_currentIdIForm = tkz.v_lastIntFormToken();
		//CAipi_Symbol sym;
		//m_currentIdIForm = sym.findId_IntForm(m_currentId);

		//AfxMessageBox(_T("CLASS ID VARIABLE"));
		//AfxMessageBox(m_currentId.data());

		
		matchToken(AIPI_VAR);
		lhs_attribute_value_list();
		lhs_connector();

	}
	else
	{
		///Error Message
	}

	


	
	 

}

void CAipi_ParserGUI::lhs_element_list()
{
	
   	lhs_element();
	if( m_lookahead == IDENTIFIER || m_lookahead == OPEN_PARENTHESIS || m_lookahead == AIPI_VAR )
	{
		lhs_element_list();
	}

}


void CAipi_ParserGUI::lhs_attribute_value_list()
{
	

	lhs_attribute_value();
	emit_rule(AIPI_LHS);
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			lhs_attribute_value();
			emit_rule(AIPI_LHS);
		}
	}

	lhs_fact_address();
	
	


}


void CAipi_ParserGUI::lhs_fact_address()
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


void CAipi_ParserGUI::rhs_start()
{
	if( m_lookahead == AIPI_THEN )
	{
		matchToken(AIPI_THEN);
	}

}


void CAipi_ParserGUI::rhs_connector()
{
	if( m_lookahead == AIPI_AND )
	{
		matchToken(AIPI_AND);
	}
}


void CAipi_ParserGUI::rhs_element_list()
{
	rhs_element();
	if(		m_lookahead == IDENTIFIER 
		||	m_lookahead == OPEN_PARENTHESIS 
		||  m_lookahead == AIPI_ASSERT
		||  m_lookahead == AIPI_RETRACT
		||  m_lookahead == AIPI_MODIFY
		||  m_lookahead == AIPI_EXEC
		||	m_lookahead == AIPI_DB_OPEN 
		|| 	m_lookahead == AIPI_DB_CLOSE 
		||  m_lookahead == AIPI_PRINTOUT 
		||  m_lookahead == AIPI_OUTPUT 
		||  m_lookahead == AIPI_INPUT
		||  m_lookahead == AIPI_DISPLAYCTRL
	  )
	{
		rhs_element_list();
	}

}


void CAipi_ParserGUI::rhs_element()
{

	if( m_lookahead == IDENTIFIER )
	{
		
		CAipi_Tokenizer tkz;
		m_currentId =  tkz.v_lastToken();
		m_currentIdIForm = tkz.v_lastIntFormToken();
		//CAipi_Symbol sym;
		//m_currentIdIForm = sym.findId_IntForm(m_currentId);
	
		//AfxMessageBox(_T("FACT ID"));
		//AfxMessageBox(m_currentId.data());
		m_currentCmd = AIPI_ASSERT;
		
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
	if( m_lookahead == AIPI_ASSERT || m_lookahead == AIPI_RETRACT || m_lookahead == AIPI_MODIFY )
	{
		//matchToken(m_lookahead);
		rhs_action_fact();
		rhs_connector();
	}
	
	if( m_lookahead == AIPI_EXEC )
	{
		CAipi_Tokenizer tkz;
		
		m_currentCmd = AIPI_EXEC;
		matchToken(AIPI_EXEC);
		
		tstring key1 =  tkz.v_lastToken();
		//AfxMessageBox(key1.data());
		long pos1 = tkz.v_lastPosition();
		long index1 = tkz.v_sizeTokenizer()-1;
	
		/*
		CString str;
		str.Format(_T("Script Pos1...%d  " ), pos1);
		AfxMessageBox(str);
		str.Format(_T("Script Index1...%d  " ), index1);
		AfxMessageBox(str);
		*/

		
		matchToken(OPEN_PARENTHESIS);
		emit_rule(AIPI_RHSCMD);
		rhs_action_script();
		
		tstring key2 =  tkz.v_lastToken();
		//AfxMessageBox(key2.data());
		long pos2 = tkz.v_lastPosition();
		long index2 = tkz.v_sizeTokenizer()-1;

		/*
		str.Format(_T("Script Pos2...%d  " ), pos2);
		AfxMessageBox(str);
		str.Format(_T("Script Index2...%d  " ), index2);
		AfxMessageBox(str);
		*/
		
		matchToken(CLOSE_PARENTHESIS);
		rhs_connector();

		CAipi_CmdLocation sloc;
		sloc.addCmdLocation(m_currentRuleIForm, index1+1, index2-1, pos1, pos2, AIPI_EXEC);

		
	}
	if( m_lookahead == AIPI_DB_OPEN || 
		m_lookahead == AIPI_DB_CLOSE ||
		m_lookahead == AIPI_PRINTOUT ||
		m_lookahead == AIPI_OUTPUT  ||
		m_lookahead == AIPI_INPUT
	  )
	{
		CAipi_Tokenizer tkz;
		tstring key1 =  tkz.v_lastToken();
		//AfxMessageBox(key1.data());
		long pos1 = tkz.v_lastPosition();
		long index1 = tkz.v_sizeTokenizer()-1;
		int cmd = m_lookahead;

		
	
		/*
		CString str;
		str.Format(_T("Script Pos1...%d  " ), pos1);
		AfxMessageBox(str);
		str.Format(_T("Script Index1...%d  " ), index1);
		AfxMessageBox(str);
		*/
		rhs_action_command();

		tstring key2 =  tkz.v_lastToken();
		//AfxMessageBox(key2.data());
		long pos2 = tkz.v_lastPosition();
		long index2 = tkz.v_sizeTokenizer()-1;

		/*
		str.Format(_T("Script Pos2...%d  " ), pos2);
		AfxMessageBox(str);
		str.Format(_T("Script Index2...%d  " ), index2);
		AfxMessageBox(str);
		*/
		
		matchToken(SEMICOLON);
		rhs_connector();

		CAipi_CmdLocation cloc;
		cloc.addCmdLocation(m_currentRuleIForm, index1, index2, pos1, pos2, cmd);
	}
	
	if( m_lookahead == AIPI_DISPLAYCTRL )
	{
		CAipi_Tokenizer tkz;
		tstring key1 =  tkz.v_lastToken();
		//AfxMessageBox(key1.data());
		long pos1 = tkz.v_lastPosition();
		long index1 = tkz.v_sizeTokenizer()-1;
		
	
		/*
		CString str;
		str.Format(_T("Script Pos1...%d  " ), pos1);
		AfxMessageBox(str);
		str.Format(_T("Script Index1...%d  " ), index1);
		AfxMessageBox(str);
		*/
		rhs_action_ctrl();
		int ctrl = m_currentCmd;

		tstring key2 =  tkz.v_lastToken();
		//AfxMessageBox(key2.data());
		long pos2 = tkz.v_lastPosition();
		long index2 = tkz.v_sizeTokenizer()-1;

		/*
		str.Format(_T("Script Pos2...%d  " ), pos2);
		AfxMessageBox(str);
		str.Format(_T("Script Index2...%d  " ), index2);
		AfxMessageBox(str);
		*/
		
		matchToken(SEMICOLON);
		rhs_connector();

		CAipi_CmdLocation cloc;
		cloc.addCmdLocation(m_currentRuleIForm, index1, index2, pos1, pos2, ctrl);
	}



}

/*
void CAipi_ParserGUI::rhs_actions()
{
	
	rhs_action_fact();
	rhs_action_ctrl();
	rhs_action_engine();
	rhs_action_gui();
	
	
}
*/

void CAipi_ParserGUI::rhs_action_fact()
{
	switch(m_lookahead)
	{
		case AIPI_ASSERT:
			m_currentCmd = AIPI_ASSERT;
			matchToken(AIPI_ASSERT);
			matchToken(OPEN_PARENTHESIS);
			if( m_lookahead == IDENTIFIER )
			{
				CAipi_Tokenizer tkz;
				m_currentId =  tkz.v_lastToken();
				m_currentIdIForm = tkz.v_lastIntFormToken();
				//CAipi_Symbol sym;
				//m_currentIdIForm = sym.findId_IntForm(m_currentId);
	
				//AfxMessageBox(_T("FACT ID"));
				//AfxMessageBox(m_currentId.data());
				
				matchToken(IDENTIFIER);
				rhs_attribute_value_list();
			}
			if( m_lookahead == AIPI_VAR )
			{
				CAipi_Tokenizer tkz;
				m_currentId =  tkz.v_lastToken();
				m_currentIdIForm = tkz.v_lastIntFormToken();
				//CAipi_Symbol sym;
				//m_currentIdIForm = sym.findId_IntForm(m_currentId);
	
				//AfxMessageBox(_T("FACT ID"));
				//AfxMessageBox(m_currentId.data());
				
				matchToken(AIPI_VAR);
				rhs_attribute_value_list();
			}
			matchToken(CLOSE_PARENTHESIS);
		break;
		case AIPI_RETRACT:
			m_currentCmd = AIPI_RETRACT;
			matchToken(AIPI_RETRACT);
			matchToken(OPEN_PARENTHESIS);
			if( m_lookahead == IDENTIFIER )
			{
				CAipi_Tokenizer tkz;
				m_currentId =  tkz.v_lastToken();
				m_currentIdIForm = tkz.v_lastIntFormToken();
				//CAipi_Symbol sym;
				//m_currentIdIForm = sym.findId_IntForm(m_currentId);
	
				//AfxMessageBox(_T("FACT ID"));
				//AfxMessageBox(m_currentId.data());
				
				matchToken(IDENTIFIER);
				rhs_attribute_value_list();
			}
			if( m_lookahead == AIPI_VAR )
			{
				CAipi_Tokenizer tkz;
				m_currentId =  tkz.v_lastToken();
				m_currentIdIForm = tkz.v_lastIntFormToken();
				//CAipi_Symbol sym;
				//m_currentIdIForm = sym.findId_IntForm(m_currentId);
	
				//AfxMessageBox(_T("FACT ID"));
				//AfxMessageBox(m_currentId.data());
				matchToken(AIPI_VAR);
				rhs_attribute_value_list();
			}
			matchToken(CLOSE_PARENTHESIS);
		break;
	}


}

void CAipi_ParserGUI::rhs_action_command()
{
	if( m_lookahead == AIPI_DB_OPEN )
	{
		cmd_db_open();	
	}
	if( m_lookahead == AIPI_DB_CLOSE )
	{
		cmd_db_close();
	}
	if ( m_lookahead == AIPI_PRINTOUT )
	{
		cmd_printout();
	}
	if ( m_lookahead == AIPI_OUTPUT )
	{
		cmd_output();
	}
	if ( m_lookahead == AIPI_INPUT )
	{
		cmd_input();
	}

}



void CAipi_ParserGUI::rhs_action_ctrl()
{
	
	if( m_lookahead == AIPI_DISPLAYCTRL )
	{
		matchToken(AIPI_DISPLAYCTRL);
		
		if( m_lookahead == AIPI_CTRL_MEDIAPLAYER)
		{
			m_currentCmd = AIPI_CTRL_MEDIAPLAYER;
			ctrl_mediaplayer();
		}
		
		if( m_lookahead == AIPI_CTRL_JUKEBOX )
		{
			m_currentCmd = AIPI_CTRL_JUKEBOX;
			ctrl_jukebox();	
		}
		if( m_lookahead == AIPI_CTRL_IMAGEFILTER )
		{
			m_currentCmd = AIPI_CTRL_IMAGEFILTER;
			ctrl_imagefilter();
		}
		if( m_lookahead == AIPI_CTRL_LISTOPTION )
		{
			m_currentCmd = AIPI_CTRL_LISTOPTION;
			ctrl_listoption();
		}
		if( m_lookahead == AIPI_CTRL_OLEDB )
		{
			m_currentCmd = AIPI_CTRL_OLEDB;
			ctrl_oledb();
		}
		
	}
  
}

void CAipi_ParserGUI::rhs_action_script()
{
	if(	m_lookahead == AIPI_VOID 
				||	m_lookahead == AIPI_CHAR
				||	m_lookahead == AIPI_STRING
				||	m_lookahead == AIPI_SHORT
				||	m_lookahead == AIPI_INT
				||	m_lookahead == AIPI_LONG
				||	m_lookahead == AIPI_FLOAT
				||	m_lookahead == AIPI_DOUBLE
	  )	
	{   
		//AfxMessageBox(_T("Declaration"));
		declaration();
		script_translation_unit();
	} 
	else if (		m_lookahead == IDENTIFIER
				||	m_lookahead == DIGIT
			)
			{
				//AfxMessageBox(_T("Expression"));
				expression_statement();
				script_translation_unit();
			}
	

}




void CAipi_ParserGUI::wm_element()
{
	if( m_lookahead == AIPI_ASSERT )
	{
		matchToken(AIPI_ASSERT);
	}
	if( m_lookahead == AIPI_RETRACT )
	{
		matchToken(AIPI_RETRACT );
	}
	if( m_lookahead == AIPI_MODIFY )
	{
		matchToken(AIPI_MODIFY);
	}

	matchToken(OPEN_PARENTHESIS);
	
	CAipi_Tokenizer tkz;
	m_currentId =  tkz.v_lastToken();
	m_currentIdIForm = tkz.v_lastIntFormToken();

		////This is for variables taken with the CListOptionCtrl or CCmdInput
	if( m_lookahead == OR_BIT )
	{
		matchToken(OR_BIT);
		
		CAipi_Tokenizer tkz;

		m_categId = AIPI_K;
		m_currentId =  tkz.v_lastToken();
		m_currentIdIForm = tkz.v_lastIntFormToken();
		
		CString sID = LiteralVarSearch(m_currentIdIForm);
		if( sID != _T("NOT_FOUND") )
		{
			m_currentId = sID.GetBuffer(NULL);
		}
		else
		{
			g_currentVarLoc = UNDEFINE;
			CAipi_Error er;
			CString strDesc = _T("Identifier [")+ sID + _T("] was not found.");
			er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
		}
	//CAipi_Symbol sym;
	//m_currentIdIForm = sym.findId_IntForm(m_currentId);
		matchToken(IDENTIFIER);
		matchToken(OR_BIT);
		wm_attribute_value_list();
		matchToken(CLOSE_PARENTHESIS);
		matchToken(SEMICOLON);
	}
	else if( m_lookahead == IDENTIFIER) 
	{
		//AfxMessageBox(_T("FACT ID"));
		//AfxMessageBox(m_currentId.data());

		matchToken(IDENTIFIER);
		wm_attribute_value_list();
		matchToken(CLOSE_PARENTHESIS);
		matchToken(SEMICOLON);
	}
	else
	{
			///Error
	}
}


void CAipi_ParserGUI::wm_element_list()
{
	wm_element();
	if( m_lookahead == AIPI_ASSERT || m_lookahead == AIPI_RETRACT || m_lookahead == AIPI_MODIFY )
	{
		wm_element_list();
	}

}

void CAipi_ParserGUI::wm_attribute_value_list()
{
	wm_attribute_value();
	emit_rule(AIPI_WM);
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			wm_attribute_value();
			emit_rule(AIPI_WM);
		}
	}

	if( m_lookahead == OPEN_PARENTHESIS )
	{
		matchToken(OPEN_PARENTHESIS);
		wm_parameter_list();
		matchToken(CLOSE_PARENTHESIS);
	}
	

}


void CAipi_ParserGUI::wm_attribute_value()
{
	double dId = UNDEFINE;
	CAipi_Tokenizer tkz;
	m_currentAttr =  tkz.v_lastToken();
	m_currentAttrIForm = tkz.v_lastIntFormToken();
		////This is for variables taken with the CListOptionCtrl or CCmdInput

	if( m_lookahead == IDENTIFIER)
	{
		//CAipi_Symbol sym;
		//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);	
		//AfxMessageBox(_T("ATTR NAME"));
		//AfxMessageBox(m_currentAttr.data());

		matchToken(IDENTIFIER);
	}
		
	else if( m_lookahead == OR_BIT )
	{
		matchToken(OR_BIT);
		
		CAipi_Tokenizer tkz;

		m_categId = AIPI_K;
		m_currentAttr =  tkz.v_lastToken();
		m_currentAttrIForm = tkz.v_lastIntFormToken();
		
		CString sID = LiteralVarSearch(m_currentAttrIForm);
		if( sID != _T("NOT_FOUND") )
		{
			m_currentAttr = sID.GetBuffer(0);
		}
		else
		{
			g_currentVarLoc = UNDEFINE;
			CAipi_Error er;
			CString strDesc = _T("Identifier [")+ sID + _T("] was not found.");
			er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
		}
		 matchToken(IDENTIFIER);
		 matchToken(OR_BIT);
	}
	
	switch(m_lookahead)
	{
			
		case LITERAL:
			m_currentRel = EQ;
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			//m_currentValIForm = sym.findId_IntForm(m_currentVal);
			
			//AfxMessageBox(_T("VALUE  LITERAL"));
			//AfxMessageBox(m_currentVal.data());

			matchToken(LITERAL);
			wm_multi_attribute_value();
			break;
        case OR_BIT:
			matchToken(OR_BIT);

			m_categVal = AIPI_K;
			m_currentRel = EQ;
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			//m_currentValIForm = sym.findId_IntForm(m_currentVal);
			
			//Search variable
			dId =  NumericVarSearch(m_currentValIForm);
			if( dId == NOT_FOUND )
			{
				CString strLit = LiteralVarSearch( m_currentValIForm);
				if( strLit != _T("NOT_FOUND") )
				{
					m_currentVal = strLit.GetBuffer(0);		
				}
				else
				{
					g_currentVarLoc = UNDEFINE;
					CAipi_Error er;
					CString strDesc = _T("Identifier [") + strLit + _T("] was not found.");
					er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
				}
			}
			else
			{
				CString strNum;
				strNum.Format(_T("%f"), dId);
				m_currentVal = strNum.GetBuffer(0);
				
			}


			//AfxMessageBox(_T("VALUE  LITERAL"));
			//AfxMessageBox(m_currentVal.data());

			matchToken(IDENTIFIER);
			matchToken(OR_BIT);
			lhs_multi_attribute_value();
			break;
		case AS:
			m_currentRel = AS;
			matchToken(AS);

			if( m_lookahead == OR_BIT )
			{
				matchToken(OR_BIT);

				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();

				//Search variable
				dId =  NumericVarSearch(m_currentValIForm);
				if( dId == NOT_FOUND )
				{
					CString strLit = LiteralVarSearch( m_currentValIForm);
					if( strLit != _T("NOT_FOUND") )
					{
						m_currentVal = strLit.GetBuffer(0);		
					}
					else
					{
						g_currentVarLoc = UNDEFINE;
						CAipi_Error er;
						CString strDesc = _T("Identifier [") + strLit + _T("] was not found.");
						er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
					}
				}
				else
				{
					CString strNum;
					strNum.Format(_T("%f"), dId);
					m_currentVal = strNum.GetBuffer(0);
				
				}

				//AfxMessageBox(_T("AS VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(IDENTIFIER);
				matchToken(OR_BIT);
			}
			else 
			{
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("AS VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
			
				matchToken(DIGIT);
			}
			wm_multi_attribute_value();
			break;
		case ET:
			m_currentRel = ET;
			matchToken(ET);

			if( m_lookahead == OR_BIT )
			{
				matchToken(OR_BIT);

				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();

				//Search variable
				dId =  NumericVarSearch(m_currentValIForm);
				if( dId == NOT_FOUND )
				{
					CString strLit = LiteralVarSearch( m_currentValIForm);
					if( strLit != _T("NOT_FOUND") )
					{
						m_currentVal = strLit.GetBuffer(0);		
					}
					else
					{
						g_currentVarLoc = UNDEFINE;
						CAipi_Error er;
						CString strDesc = _T("Identifier [") + strLit + _T("] was not found.");
						er.displayFileError(NOT_DECLARE, SEMANT_ERROR, strDesc);
					}
				}
				else
				{
					CString strNum;
					strNum.Format(_T("%f"), dId);
					m_currentVal = strNum.GetBuffer(0);
				
				}

				//AfxMessageBox(_T("EQUAL THAN VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(IDENTIFIER);
				matchToken(OR_BIT);
			}
			else
			{
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("EQUAL THAN VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(DIGIT);
				
			}
			wm_multi_attribute_value();
			break;
		case NE:
			m_currentRel = NE;
			matchToken(NE);

			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			
			//AfxMessageBox(_T("NOT EQUAL VALUE DIGIT"));
			//AfxMessageBox(m_currentVal.data());
			
			matchToken(DIGIT);
			wm_multi_attribute_value();
			break;
		case LT:
			m_currentRel = LT;
			matchToken(LT);

			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			
			//AfxMessageBox(_T("LESS THAN VALUE DIGIT"));
			//AfxMessageBox(m_currentVal.data());
			
			matchToken(DIGIT);
			wm_multi_attribute_value();
			break;
		case LE:
			m_currentRel = LE;
			matchToken(LE);
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			
			//AfxMessageBox(_T("LESS OR EQUAL VALUE DIGIT"));
			//AfxMessageBox(m_currentVal.data());
			
			matchToken(DIGIT);
			wm_multi_attribute_value();
			break;
		case GT:
			m_currentRel = GT;
			matchToken(GT);
			
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			
			//AfxMessageBox(_T("GREATER VALUE DIGIT"));
			//AfxMessageBox(m_currentVal.data());
			
			matchToken(DIGIT);
			wm_multi_attribute_value();
			break;
		case GE:
			m_currentRel = GE;
			matchToken(GE);
			
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			
			//AfxMessageBox(_T("GREATER OR  EQUAL VALUE DIGIT"));
			//AfxMessageBox(m_currentVal.data());
			
			matchToken(DIGIT);
			wm_multi_attribute_value();
			break;

	}

}


void CAipi_ParserGUI::wm_multi_attribute_value()
{
	CAipi_Tokenizer tkz;
	CAipi_Symbol sym;
	
	if( m_lookahead == AND_OP )
	{
		while( m_lookahead == AND_OP )
		{
			matchToken(AND_OP);
			if( m_lookahead == IDENTIFIER )
			{
				m_currentAttr =  tkz.v_lastToken();
				m_currentAttrIForm = tkz.v_lastIntFormToken();
				//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);	
				
				//AfxMessageBox(_T("ATTR NAME"));
				//AfxMessageBox(m_currentAttr.data());
				matchToken(IDENTIFIER);
			}
						
			switch(m_lookahead)
			{
				case LITERAL:
					m_currentRel = EQ;
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
					//AfxMessageBox(_T("VALUE  LITERAL"));
					//AfxMessageBox(m_currentVal.data());
					matchToken(LITERAL);
					break;
				case AS:
					m_currentRel = AS;
					matchToken(AS);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					
					//AfxMessageBox(_T("VALUE  AS"));
					//AfxMessageBox(m_currentVal.data());
					matchToken(DIGIT);
					break;
				case ET:
					m_currentRel = ET;
					matchToken(ET);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					//AfxMessageBox(_T("VALUE  ET"));
					//AfxMessageBox(m_currentVal.data());
					matchToken(DIGIT);
					break;
				case NE:
					m_currentRel = NE;
					matchToken(NE);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					//AfxMessageBox(_T("VALUE  NE"));
					//AfxMessageBox(m_currentVal.data());
					matchToken(DIGIT);
					break;
				case LT:
					m_currentRel = LT;
					matchToken(LT);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					//AfxMessageBox(_T("VALUE  LT"));
					//AfxMessageBox(m_currentVal.data());
					matchToken(DIGIT);
					break;
				case LE:
					m_currentRel = LE;
					matchToken(LE);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					//AfxMessageBox(_T("VALUE  LE"));
					//AfxMessageBox(m_currentVal.data());
					matchToken(DIGIT);
					break;
				case GT:
					m_currentRel = GT;
					matchToken(GT);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					//AfxMessageBox(_T("VALUE  GT"));
					//AfxMessageBox(m_currentVal.data());
					matchToken(DIGIT);
					break;
				case GE:
					m_currentRel = GE;
					matchToken(GE);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					//AfxMessageBox(_T("VALUE  GE"));
					//AfxMessageBox(m_currentVal.data());
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
				m_currentAttr =  tkz.v_lastToken();
				m_currentAttrIForm = tkz.v_lastIntFormToken();
				//CAipi_Symbol sym;
				//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);	
				//AfxMessageBox(_T("ATTR NAME"));
				//AfxMessageBox(m_currentAttr.data());
				matchToken(IDENTIFIER);
			}
			
			switch(m_lookahead)
			{
			case LITERAL:
				m_currentRel = EQ;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//m_currentValIForm = sym.findId_IntForm(m_currentVal);
				//AfxMessageBox(_T("VALUE  LITERAL"));
				//AfxMessageBox(m_currentVal.data());
				matchToken(LITERAL);
				break;
			case AS:
				m_currentRel = AS;
				matchToken(AS);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//AfxMessageBox(_T("VALUE  AS"));
				//AfxMessageBox(m_currentVal.data());
				matchToken(DIGIT);
				break;
			case ET:
				m_currentRel = ET;
				matchToken(ET);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//AfxMessageBox(_T("VALUE  ET"));
				//AfxMessageBox(m_currentVal.data());
				matchToken(DIGIT);
				break;
			case NE:
				m_currentRel = NE;
				matchToken(NE);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//AfxMessageBox(_T("VALUE  NE"));
				//AfxMessageBox(m_currentVal.data());
				matchToken(DIGIT);
				break;
			case LT:
				m_currentRel = LT;
				matchToken(LT);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//AfxMessageBox(_T("VALUE  LT"));
				//AfxMessageBox(m_currentVal.data());
				matchToken(DIGIT);
				break;
			case LE:
				m_currentRel = LE;
				matchToken(LE);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//AfxMessageBox(_T("VALUE  LE"));
				//AfxMessageBox(m_currentVal.data());
				matchToken(DIGIT);
				break;
			case GT:
				m_currentRel = GT;
				matchToken(GT);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//AfxMessageBox(_T("VALUE  GT"));
				//AfxMessageBox(m_currentVal.data());
				matchToken(DIGIT);
				break;
			case GE:
				m_currentRel = GE;
				matchToken(GE);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//AfxMessageBox(_T("VALUE  GE"));
				//AfxMessageBox(m_currentVal.data());
				matchToken(DIGIT);
				break;
			}
			
		}
	}

}



void CAipi_ParserGUI::wm_parameter()
{
	if( m_lookahead == AIPI_CF)
	{
		matchToken(AIPI_CF);
		matchToken(COLON);
		matchToken(DIGIT);
	}


}

void CAipi_ParserGUI::wm_parameter_list()
{
	wm_parameter();
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			wm_parameter();
		}
	}


}





void CAipi_ParserGUI::lhs_attribute_value()
{
	CAipi_Tokenizer tkz;
	CAipi_Symbol sym;

	if( m_lookahead == IDENTIFIER )
	{
		m_categAttr = AIPI_K;
		m_currentAttr =  tkz.v_lastToken();
		m_currentAttrIForm = tkz.v_lastIntFormToken();
		//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);	

		//AfxMessageBox(_T("ATTR NAME"));
		//AfxMessageBox(m_currentAttr.data());
		
		matchToken(IDENTIFIER);
	}
	else if( m_lookahead == OR_BIT )
	{
		matchToken(OR_BIT);
		m_categAttr = AIPI_K;
		m_currentAttr =  tkz.v_lastToken();
		m_currentAttrIForm = tkz.v_lastIntFormToken();
		//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);
		
		CString sID= LiteralVarSearch(m_currentAttrIForm);
		if( sID != _T("NOT_FOUND") )
		{
			m_currentAttr = sID;
		}
		else
		{
			///Error
		}


		//AfxMessageBox(_T("ATTR NAME"));
		//AfxMessageBox(m_currentAttr.data());
		
		matchToken(IDENTIFIER);
		matchToken(OR_BIT);

	}
	else if( m_lookahead == AIPI_VAR )
	{
		m_categAttr = AIPI_AT;
		m_currentAttr =  tkz.v_lastToken();
		m_currentAttrIForm = tkz.v_lastIntFormToken();
		//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);	

		//AfxMessageBox(_T("ATTR VARIABLE"));
		//AfxMessageBox(m_currentAttr.data());
		
		
		matchToken(AIPI_VAR);
	}
	else
	{
		//Error Message	
	}

	switch(m_lookahead)
	{
		case AIPI_VAR:

			m_categVal = AIPI_VL;
			m_currentRel = EQ;
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			//m_currentValIForm = sym.findId_IntForm(m_currentVal);	

		
			//AfxMessageBox(_T("VALUE VARIABLE"));
			//AfxMessageBox(m_currentVal.data());

			matchToken(AIPI_VAR);
			lhs_multi_attribute_value();
			break;
			
		case LITERAL:

			m_categVal = AIPI_K;
			m_currentRel = EQ;
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			//m_currentValIForm = sym.findId_IntForm(m_currentVal);	

			//AfxMessageBox(_T("VALUE  LITERAL"));
			//AfxMessageBox(m_currentVal.data());

			matchToken(LITERAL);
			lhs_multi_attribute_value();
			break;
        case OR_BIT:
			matchToken(OR_BIT);

			m_categVal = AIPI_K;
			m_currentRel = EQ;
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			//m_currentValIForm = sym.findId_IntForm(m_currentVal);	

			//AfxMessageBox(_T("VALUE  LITERAL"));
			//AfxMessageBox(m_currentVal.data());

			matchToken(IDENTIFIER);
			matchToken(OR_BIT);
			lhs_multi_attribute_value();
			break;

		case AS:
			matchToken(AS);
			m_currentRel = AS;
			
			if( m_lookahead == DIGIT )
			{
				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("AS VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(DIGIT);
			}
			if( m_lookahead == OR_BIT )
			{				
				matchToken(OR_BIT);

				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("AS VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(IDENTIFIER);
				matchToken(OR_BIT);
			}
			if( m_lookahead == AIPI_VAR )
			{
				m_categVal = AIPI_VL;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
				//AfxMessageBox(_T("AS VALUE VARIABLE"));
				//AfxMessageBox(m_currentVal.data());
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;
		case ET:
			matchToken(ET);
			m_currentRel = ET;
			
			if( m_lookahead == DIGIT )
			{
				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("EQUAL THAN VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(DIGIT);
			}
			if( m_lookahead == OR_BIT )
			{
				matchToken(OR_BIT);

				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("EQUAL THAN VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(IDENTIFIER);
				matchToken(OR_BIT);

			}
			if( m_lookahead == AIPI_VAR )
			{
				m_categVal = AIPI_VL;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
				//AfxMessageBox(_T("EQUAL THAN VALUE VARIABLE"));
				//AfxMessageBox(m_currentVal.data());
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;
		case NE:
			matchToken(NE);
			m_currentRel = NE;
			if( m_lookahead == DIGIT )
			{
				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("NOT EQUAL THAN VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
		
				matchToken(DIGIT);
			}
			
			if( m_lookahead == OR_BIT )
			{
				matchToken(OR_BIT);

				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("NOT EQUAL THAN VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
		
				matchToken(IDENTIFIER);
				matchToken(OR_BIT);
			}
			if( m_lookahead == AIPI_VAR )
			{
				m_categVal = AIPI_VL;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
				//AfxMessageBox(_T("NOT EQUAL THAN VALUE VARIABLE"));
				//AfxMessageBox(m_currentVal.data());
		
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;
		case LT:
			matchToken(LT);
			m_currentRel = LT;
			if( m_lookahead == DIGIT )
			{
				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();

				//AfxMessageBox(_T("LESS THAN VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
		
				matchToken(DIGIT);
			}
			if( m_lookahead == OR_BIT )
			{
				matchToken(OR_BIT);
				
				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("LESS THAN VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
		
				matchToken(IDENTIFIER);
				matchToken(OR_BIT);
			}
			if( m_lookahead == AIPI_VAR )
			{
				m_categVal = AIPI_VL;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
				//AfxMessageBox(_T("LESS THAN VALUE VARIABLE"));
				//AfxMessageBox(m_currentVal.data());
		
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;
		case LE:
			matchToken(LE);
			m_currentRel = LE;
			if( m_lookahead == DIGIT )
			{
				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("LESS OR EQUAL VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
		
				matchToken(DIGIT);
			}
			
			if( m_lookahead == OR_BIT )
			{
				matchToken(OR_BIT);

				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("LESS OR EQUAL VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
		
				matchToken(IDENTIFIER);
				matchToken(OR_BIT);
			}
			
			if( m_lookahead == AIPI_VAR )
			{
				m_categVal = AIPI_VL;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
				//AfxMessageBox(_T("LESS OR EQUAL VALUE VARIABLE"));
				//AfxMessageBox(m_currentVal.data());
		
				
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;
		case GT:
			matchToken(GT);
			m_currentRel = GT;
			if( m_lookahead == DIGIT )
			{
				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//m_currentValIForm = tkz.v_lastIntFormToken();
				//AfxMessageBox(_T("GREATER THAN VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
		
				matchToken(DIGIT);
			}
			
			if( m_lookahead == OR_BIT )
			{
				matchToken(OR_BIT);

				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//m_currentValIForm = tkz.v_lastIntFormToken();
				//AfxMessageBox(_T("GREATER THAN VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
		
				matchToken(IDENTIFIER);
				matchToken(OR_BIT);
			}
			if( m_lookahead == AIPI_VAR )
			{
				m_categVal = AIPI_VL;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
				//AfxMessageBox(_T("GREATER THAN VALUE VARIABLE"));
				//AfxMessageBox(m_currentVal.data());
		
				
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;
		case GE:
			matchToken(GE);
			m_currentRel = GE;
			if( m_lookahead == DIGIT )
			{
				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();

				//AfxMessageBox(_T("GREATER OR EQUAL VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
		
				
				matchToken(DIGIT);
			}
			if( m_lookahead == OR_BIT )
			{
				matchToken(OR_BIT);
				
				m_categVal = AIPI_K;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//AfxMessageBox(_T("GREATER OR EQUAL VALUE DIGIT"));
				//AfxMessageBox(m_currentVal.data());
		
				
				matchToken(IDENTIFIER);
				matchToken(OR_BIT);
			}
			if( m_lookahead == AIPI_VAR )
			{
				m_categVal = AIPI_VL;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
				//AfxMessageBox(_T("GREATER OR EQUAL VALUE VARIABLE"));
				//AfxMessageBox(m_currentVal.data());
		
				
				matchToken(AIPI_VAR);
			}
			lhs_multi_attribute_value();
			break;


	}


}



void CAipi_ParserGUI::lhs_multi_attribute_value()
{
	CAipi_Tokenizer tkz;
	CAipi_Symbol sym;
	
	if( m_lookahead == AND_OP )
	{
		while( m_lookahead == AND_OP )
		{
			matchToken(AND_OP);
			if( m_lookahead == IDENTIFIER )
			{
				m_categAttr = AIPI_K;
				m_currentAttr =  tkz.v_lastToken();
				m_currentAttrIForm = tkz.v_lastIntFormToken();
				//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);	
				
				//AfxMessageBox(_T("ATTR NAME"));
				//AfxMessageBox(m_currentAttr.data());
						
				matchToken(IDENTIFIER);
			}
			if( m_lookahead == AIPI_VAR )
			{
				m_categAttr = AIPI_AT;
				m_currentAttr =  tkz.v_lastToken();
				m_currentAttrIForm = tkz.v_lastIntFormToken();
				//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);	
				
				//AfxMessageBox(_T("ATTR VARIABLE"));
				//AfxMessageBox(m_currentAttr.data());

				matchToken(AIPI_VAR);
		
			}
						
			switch(m_lookahead)
			{
				case AIPI_VAR:
					m_categVal = AIPI_VL;
					m_currentRel = EQ;
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
					//AfxMessageBox(_T("VALUE VARIABLE"));
					//AfxMessageBox(m_currentVal.data());
		
					matchToken(AIPI_VAR);
					break;
				case LITERAL:
					m_categVal = AIPI_K;
					m_currentRel = EQ;
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
					//AfxMessageBox(_T("VALUE  LITERAL"));
					//AfxMessageBox(m_currentVal.data());
		
					matchToken(LITERAL);
					break;
				case AS:
					matchToken(AS);
					m_currentRel = AS;

					if( m_lookahead == DIGIT )
					{
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("EQUAL ASSIGN VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
								
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("EQUAL ASSIGN VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
								
						matchToken(AIPI_VAR);
					}
					break;
				case ET:
					matchToken(ET);
					m_currentRel = ET;

					if( m_lookahead == DIGIT )
					{
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("EQUAL THAN VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
								
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("EQUAL THAN VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
								
						matchToken(AIPI_VAR);
					}
					break;
				case NE:
					matchToken(NE);
					if( m_lookahead == DIGIT )
					{
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("NOT EQUAL THAN VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
		
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("NOT EQUAL THAN VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
								
						matchToken(AIPI_VAR);
					}
					break;
				case LT:
					matchToken(LT);
					if( m_lookahead == DIGIT )
					{
						
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("LESS THAN VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
		
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("LESS THAN VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
						
						
						matchToken(AIPI_VAR);
					}
					break;
				case LE:
					matchToken(LE);
					if( m_lookahead == DIGIT )
					{
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("LESS OR EQUAL VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
		
						
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("LESS OR EQUAL VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
												
						matchToken(AIPI_VAR);
					}
					break;
				case GT:
					matchToken(GT);
					if( m_lookahead == DIGIT )
					{
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("GREATER THAN VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
					
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("GREATER THAN VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
												
						matchToken(AIPI_VAR);
					}
					break;
				case GE:
					matchToken(GE);
					if( m_lookahead == DIGIT )
					{
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("GREATER OR EQUAL VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
					
						
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("GREATER OR EQUAL VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
						
						
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
				m_categAttr = AIPI_K;
				m_currentAttr =  tkz.v_lastToken();
				m_currentAttrIForm = tkz.v_lastIntFormToken();

				//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);	
				
				//AfxMessageBox(_T("ATTR NAME"));
				//AfxMessageBox(m_currentAttr.data());
				
				matchToken(IDENTIFIER);
			}
			if( m_lookahead == AIPI_VAR )
			{
				m_categAttr = AIPI_AT;
				m_currentAttr =  tkz.v_lastToken();
				m_currentAttrIForm = tkz.v_lastIntFormToken();
				//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);	
				
				//AfxMessageBox(_T("ATTR VARIABLE"));
				//AfxMessageBox(m_currentAttr.data());

				matchToken(AIPI_VAR);
		
			}

			
			switch(m_lookahead)
			{
				case AIPI_VAR:
					m_categVal = AIPI_VL;
					m_currentRel = EQ;
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
					//AfxMessageBox(_T("VALUE VARIABLE"));
					//AfxMessageBox(m_currentVal.data());
		
					matchToken(AIPI_VAR);
					break;
				case LITERAL:
					m_categVal = AIPI_K;
					m_currentRel = EQ;
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
					//AfxMessageBox(_T("VALUE  LITERAL"));
					//AfxMessageBox(m_currentVal.data());
		
					matchToken(LITERAL);
					break;
				case AS:
					matchToken(AS);
					m_currentRel = AS;

					if( m_lookahead == DIGIT )
					{
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("EQUAL ASSIGN VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
								
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();

						//m_currentValIForm = sym.findId_IntForm(m_currentVal);

					
						//AfxMessageBox(_T("EQUAL ASSIGN VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
								
						matchToken(AIPI_VAR);
					}
					break;
				case ET:
					matchToken(ET);
					m_currentRel = ET;

					if( m_lookahead == DIGIT )
					{
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("EQUAL THAN VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
								
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("EQUAL THAN VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
								
						matchToken(AIPI_VAR);
					}
					break;
				case NE:
					matchToken(NE);
					if( m_lookahead == DIGIT )
					{
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("NOT EQUAL THAN VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
		
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("NOT EQUAL THAN VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
								
						matchToken(AIPI_VAR);
					}
					break;
				case LT:
					matchToken(LT);
					if( m_lookahead == DIGIT )
					{
						
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("LESS THAN VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
		
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("LESS THAN VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
						
						
						matchToken(AIPI_VAR);
					}
					break;
				case LE:
					matchToken(LE);
					if( m_lookahead == DIGIT )
					{
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("LESS OR EQUAL VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
		
						
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("LESS OR EQUAL VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
												
						matchToken(AIPI_VAR);
					}
					break;
				case GT:
					matchToken(GT);
					if( m_lookahead == DIGIT )
					{
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("GREATER THAN VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
					
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("GREATER THAN VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
												
						matchToken(AIPI_VAR);
					}
					break;
				case GE:
					matchToken(GE);
					if( m_lookahead == DIGIT )
					{
						m_categVal = AIPI_K;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						
						//AfxMessageBox(_T("GREATER OR EQUAL VALUE DIGIT"));
						//AfxMessageBox(m_currentVal.data());
					
						
						matchToken(DIGIT);
					}
					if( m_lookahead == AIPI_VAR )
					{
						m_categVal = AIPI_VL;
						m_currentVal =  tkz.v_lastToken();
						m_currentValIForm = tkz.v_lastIntFormToken();
						//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
						//AfxMessageBox(_T("GREATER OR EQUAL VALUE VARIABLE"));
						//AfxMessageBox(m_currentVal.data());
						
						
						matchToken(AIPI_VAR);
					}
					break;
				
			
			}
			
		}
	}



}


void CAipi_ParserGUI::rhs_attribute_value_list()
{
	rhs_attribute_value();
	emit_rule(AIPI_RHS);
	
	if( m_lookahead == COMMA )
	{
		while ( m_lookahead == COMMA )
		{
			matchToken(COMMA);
			rhs_attribute_value();
			emit_rule(AIPI_RHS);
		}
	}

	if( m_lookahead == OPEN_PARENTHESIS )
	{
		matchToken(OPEN_PARENTHESIS);
		rhs_parameter_list();
		matchToken(CLOSE_PARENTHESIS);
	}
	

}




void CAipi_ParserGUI::rhs_parameter()
{
	if( m_lookahead == AIPI_CF)
	{
		matchToken(AIPI_CF);
		matchToken(COLON);
		matchToken(DIGIT);
	}


}

void CAipi_ParserGUI::rhs_parameter_list()
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

void CAipi_ParserGUI::rhs_attribute_value()
{
	CAipi_Tokenizer tkz;
	m_currentAttr =  tkz.v_lastToken();
	m_currentAttrIForm = tkz.v_lastIntFormToken();
	//CAipi_Symbol sym;
	//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);	
	
	//AfxMessageBox(_T("ATTR NAME"));
	//AfxMessageBox(m_currentAttr.data());
	matchToken(IDENTIFIER);
		
	switch(m_lookahead)
	{
			
		case LITERAL:
			m_currentRel = EQ;
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();

			//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
			//AfxMessageBox(_T("VALUE  LITERAL"));
			//AfxMessageBox(m_currentVal.data());

			matchToken(LITERAL);
			rhs_multi_attribute_value();
			break;
		case AS:
			m_currentRel = AS;
			matchToken(AS);
			
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			
			//AfxMessageBox(_T("AS VALUE DIGIT"));
			//AfxMessageBox(m_currentVal.data());
			
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;
		case ET:
			m_currentRel = ET;
			matchToken(ET);

			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();

			//AfxMessageBox(_T("EQUAL THAN VALUE DIGIT"));
			//AfxMessageBox(m_currentVal.data());
			
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;
		case NE:
			m_currentRel = NE;
			matchToken(NE);

			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			
			//AfxMessageBox(_T("NOT EQUAL VALUE DIGIT"));
			//AfxMessageBox(m_currentVal.data());
			
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;
		case LT:
			m_currentRel = LT;
			matchToken(LT);

			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			
			//AfxMessageBox(_T("LESS THAN VALUE DIGIT"));
			//AfxMessageBox(m_currentVal.data());
			
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;
		case LE:
			m_currentRel = LE;
			matchToken(LE);
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			
			//AfxMessageBox(_T("LESS OR EQUAL VALUE DIGIT"));
			//AfxMessageBox(m_currentVal.data());
			
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;
		case GT:
			m_currentRel = GT;
			matchToken(GT);
			
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			
			//AfxMessageBox(_T("GREATER VALUE DIGIT"));
			//AfxMessageBox(m_currentVal.data());
			
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;
		case GE:
			m_currentRel = GE;
			matchToken(GE);
			
			m_currentVal =  tkz.v_lastToken();
			m_currentValIForm = tkz.v_lastIntFormToken();
			
			//AfxMessageBox(_T("GREATER OR  EQUAL VALUE DIGIT"));
			//AfxMessageBox(m_currentVal.data());
			
			matchToken(DIGIT);
			rhs_multi_attribute_value();
			break;

	}

}


void CAipi_ParserGUI::rhs_multi_attribute_value()
{
	CAipi_Tokenizer tkz;
	CAipi_Symbol sym;
	if( m_lookahead == AND_OP )
	{
		while( m_lookahead == AND_OP )
		{
			matchToken(AND_OP);
			if( m_lookahead == IDENTIFIER )
			{
				m_currentAttr =  tkz.v_lastToken();
				m_currentAttrIForm = tkz.v_lastIntFormToken();
				//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);	
				
				//AfxMessageBox(_T("ATTR NAME"));
				//AfxMessageBox(m_currentAttr.data());
				
				matchToken(IDENTIFIER);
			}
						
			switch(m_lookahead)
			{
				case LITERAL:
					m_currentRel = EQ;
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
					//AfxMessageBox(_T("VALUE  LITERAL"));
					//AfxMessageBox(m_currentVal.data());
					
					matchToken(LITERAL);
					break;
				case AS:
					m_currentRel = AS;
					matchToken(AS);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					
					//AfxMessageBox(_T("VALUE  AS"));
					//AfxMessageBox(m_currentVal.data());
					
					matchToken(DIGIT);
					break;
				case ET:
					m_currentRel = ET;
					matchToken(ET);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					
					//AfxMessageBox(_T("VALUE  ET"));
					//AfxMessageBox(m_currentVal.data());
					
					matchToken(DIGIT);
					break;
				case NE:
					m_currentRel = NE;
					matchToken(NE);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					
					//AfxMessageBox(_T("VALUE  NE"));
					//AfxMessageBox(m_currentVal.data());
					
					matchToken(DIGIT);
					break;
				case LT:
					m_currentRel = LT;
					matchToken(LT);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					
					//AfxMessageBox(_T("VALUE  LT"));
					//AfxMessageBox(m_currentVal.data());
					
					matchToken(DIGIT);
					break;
				case LE:
					m_currentRel = LE;
					matchToken(LE);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					
					//AfxMessageBox(_T("VALUE  LE"));
					//AfxMessageBox(m_currentVal.data());
					
					matchToken(DIGIT);
					break;
				case GT:
					m_currentRel = GT;
					matchToken(GT);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					
					//AfxMessageBox(_T("VALUE  GT"));
					//AfxMessageBox(m_currentVal.data());
					
					matchToken(DIGIT);
					break;
				case GE:
					m_currentRel = GE;
					matchToken(GE);
					m_currentVal =  tkz.v_lastToken();
					m_currentValIForm = tkz.v_lastIntFormToken();
					
					//AfxMessageBox(_T("VALUE  GE"));
					//AfxMessageBox(m_currentVal.data());
					
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
				m_currentAttr =  tkz.v_lastToken();
				m_currentAttrIForm = tkz.v_lastIntFormToken();
				//CAipi_Symbol sym;
				//m_currentAttrIForm = sym.findId_IntForm(m_currentAttr);	
				
				//AfxMessageBox(_T("ATTR NAME"));
				//AfxMessageBox(m_currentAttr.data());
				
				matchToken(IDENTIFIER);
			}
			
			switch(m_lookahead)
			{
			case LITERAL:
				m_currentRel = EQ;
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				//m_currentValIForm = sym.findId_IntForm(m_currentVal);
					
				//AfxMessageBox(_T("VALUE  LITERAL"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(LITERAL);
				break;
			case AS:
				m_currentRel = AS;
				matchToken(AS);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("VALUE  AS"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(DIGIT);
				break;
			case ET:
				m_currentRel = ET;
				matchToken(ET);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("VALUE  ET"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(DIGIT);
				break;
			case NE:
				m_currentRel = NE;
				matchToken(NE);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("VALUE  NE"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(DIGIT);
				break;
			case LT:
				m_currentRel = LT;
				matchToken(LT);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("VALUE  LT"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(DIGIT);
				break;
			case LE:
				m_currentRel = LE;
				matchToken(LE);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("VALUE  LE"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(DIGIT);
				break;
			case GT:
				m_currentRel = GT;
				matchToken(GT);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("VALUE  GT"));
				//AfxMessageBox(m_currentVal.data());
				
				matchToken(DIGIT);
				break;
			case GE:
				m_currentRel = GE;
				matchToken(GE);
				m_currentVal =  tkz.v_lastToken();
				m_currentValIForm = tkz.v_lastIntFormToken();
				
				//AfxMessageBox(_T("VALUE  GE"));
				//AfxMessageBox(m_currentVal.data());
				
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
void CAipi_ParserGUI::declaration_specifiers()
{
	
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
		matchToken(m_lookahead);
		declaration_specifiers();
		

	}
	
}


void CAipi_ParserGUI::declaration()
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



void CAipi_ParserGUI::declarator_list_init()
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

void CAipi_ParserGUI::declarator_init()
{
	declarator_direct();
	
	if( m_lookahead == EQUAL )
	{
		matchToken(EQUAL);
		initializer();
		
	}

}




void CAipi_ParserGUI::initializer()
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

void CAipi_ParserGUI::initializer_list()
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




void CAipi_ParserGUI::declarator_direct()
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




void CAipi_ParserGUI::parameter_declaration()
{
	
	
	declaration_specifiers();
	
	if( m_lookahead == IDENTIFIER || m_lookahead == OPEN_PARENTHESIS || m_lookahead == OPEN_BRACKET)
	{
		declarator_direct();
	}
	
}



void CAipi_ParserGUI::parameter_list()
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
void CAipi_ParserGUI::expression_statement()
{
	
	if( m_lookahead == SEMICOLON )
	{
		matchToken(SEMICOLON);	
	}

	expression();
	matchToken(SEMICOLON);
	
	
}


void CAipi_ParserGUI::expression()
{
	expression_logical_or();
	expression_assignment();
	

}


void CAipi_ParserGUI::expression_assignment()
{
	if( m_lookahead == EQUAL)
	{
		matchToken(EQUAL);
		expression_logical_or();
	}
	
	expression_logical_or();
	
	
			
}


void CAipi_ParserGUI::expression_logical_or()
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


void CAipi_ParserGUI::expression_logical_and()
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

void CAipi_ParserGUI::expression_equality()
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


void CAipi_ParserGUI::expression_relational()
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


void CAipi_ParserGUI::expression_aritmetic()
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




void CAipi_ParserGUI::expression_term()
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


void CAipi_ParserGUI::expression_unary_plus()
{
	matchToken(PLUS_SIGN);
	expression_factor();
	
}


void CAipi_ParserGUI::expression_unary_minus()
{
	matchToken(MINUS_SIGN);
	expression_factor();
	
}

void CAipi_ParserGUI::expression_unary_increment()
{
		
	matchToken(INC_OP);
	//It just apply to identifiers
	if( m_lookahead == IDENTIFIER )
	{
		expression_factor();
		
	}	


}

void CAipi_ParserGUI::expression_unary_decrement()
{
	matchToken(DEC_OP);
	//It just apply to identifiers
	if( m_lookahead = IDENTIFIER )
	{
		expression_factor();
	}
}


void CAipi_ParserGUI::expression_factor()
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


void CAipi_ParserGUI::expression_atom_identifier()
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
	//Detect function call
	if( m_lookahead == OPEN_PARENTHESIS )
	{
		matchToken(OPEN_PARENTHESIS);
		expression_argument_list();
		matchToken(CLOSE_PARENTHESIS);
	}

}

void CAipi_ParserGUI::expression_argument_list()
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


void CAipi_ParserGUI::expression_atom_constant()
{
	matchToken(DIGIT);

}

void CAipi_ParserGUI::expression_atom_literal()
{
	matchToken(LITERAL);
}
	

//////////////////////////////////////////////////////////////////////////
//// AIPI Commands ////
////////////////////////////////////////////////////////////////////////////

void CAipi_ParserGUI::cmd_db_open()
{
	m_currentCmd = AIPI_DB_OPEN;
	emit_rule(AIPI_RHSCMD);
	
	matchToken(AIPI_DB_OPEN);
	matchToken(OPEN_PARENTHESIS);
	cmd_db_open_parameter_list();
	matchToken(CLOSE_PARENTHESIS);
	//matchToken(SEMICOLON);

	
}


void CAipi_ParserGUI::cmd_db_open_parameter()
{
	
	CAipi_Tokenizer tkz;
	CAipi_RHSCmd cmdo;
	CString sProvider = _T("");

	switch( m_lookahead )
	{
	case AIPI_DB_DNS:
		
		matchToken(AIPI_DB_DNS);
		matchToken(EQUAL);

		
		if( m_lookahead == LITERAL )
		{
			matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			matchToken(IDENTIFIER);
			
		}
		break;
	case AIPI_DB_USER:
		matchToken(AIPI_DB_USER);
		matchToken(EQUAL);
		
		if( m_lookahead == LITERAL )
		{
			matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			matchToken(IDENTIFIER);
		}
		break;
	case AIPI_DB_PASSWORD:
		matchToken(AIPI_DB_PASSWORD);
		matchToken(EQUAL);
		
		if( m_lookahead == LITERAL )
		{
			matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
				
			matchToken(IDENTIFIER);
						
		}
		break;
	case AIPI_DB_PROVIDER:
		matchToken(AIPI_DB_PROVIDER);
		matchToken(EQUAL);
		if( m_lookahead == LITERAL )
		{
			matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			matchToken(IDENTIFIER);
					
		}
		break;
    case AIPI_DB_NAME:
		matchToken(AIPI_DB_NAME);
		matchToken(EQUAL);
		
		if( m_lookahead == LITERAL )
		{
			matchToken(LITERAL);
		}
		else if ( m_lookahead == IDENTIFIER )
		{
			long idTk = tkz.v_lastIntFormToken();
				
			matchToken(IDENTIFIER);
						
		}
		break;
	}
		


}



void CAipi_ParserGUI::cmd_db_open_parameter_list()
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

void CAipi_ParserGUI::cmd_db_close()
{
	m_currentCmd = AIPI_DB_CLOSE;
	emit_rule(AIPI_RHSCMD);
	matchToken(AIPI_DB_CLOSE);

}


void CAipi_ParserGUI::cmd_printout()
{
	m_currentCmd = AIPI_PRINTOUT;
	emit_rule(AIPI_RHSCMD);
	
	matchToken(AIPI_PRINTOUT);
	if( m_lookahead == OPEN_PARENTHESIS )
	{
		matchToken(OPEN_PARENTHESIS);
		
		while ( m_lookahead != CLOSE_PARENTHESIS && m_lookahead != NUL)
		{
			if( m_lookahead == LITERAL )
			{
				matchToken(LITERAL);
			}
			if( m_lookahead == IDENTIFIER )
			{
				matchToken(IDENTIFIER);
			}
			if( m_lookahead == DIGIT )
			{
				matchToken(DIGIT);
			}
			if( m_lookahead == NUL )
			{
				return;
			}
			
			
		}

		matchToken(CLOSE_PARENTHESIS);
		//matchToken(SEMICOLON);
	}

}


void CAipi_ParserGUI::cmd_output()
{
	
	CAipi_Tokenizer tkz;

	m_currentCmd = AIPI_OUTPUT;
	emit_rule(AIPI_RHSCMD);

	matchToken(AIPI_OUTPUT);

	if ( m_lookahead == LEFT_OP )
	{
		while( m_lookahead != SEMICOLON && m_lookahead != NUL)
		{
			matchToken(LEFT_OP);
			
			if( m_lookahead == LITERAL )
			{
				matchToken(LITERAL);
				
			}
			else if( m_lookahead == IDENTIFIER )
			{
				matchToken(IDENTIFIER);
											
			}
			else if( m_lookahead == NUL )
			{
				return;
			}
			else
			{
				return;
			}

		}
		//matchToken(SEMICOLON);
	}

}

void CAipi_ParserGUI::cmd_input()
{
	m_currentCmd = AIPI_INPUT;
	emit_rule(AIPI_RHSCMD);
	
	matchToken(AIPI_INPUT);
	
	
	if ( m_lookahead == RIGHT_OP )
	{
		while( m_lookahead != SEMICOLON && m_lookahead != NUL)
		{
			matchToken(RIGHT_OP);
			
			if( m_lookahead == IDENTIFIER )
			{
				matchToken(IDENTIFIER);
			}
			else if( m_lookahead == NUL )
			{
				return;
			}
			else
			{
				return;
			}

		}

		//matchToken(SEMICOLON);
	
	}

}


void CAipi_ParserGUI::ctrl_jukebox()
{
	
	m_currentCmd = AIPI_CTRL_JUKEBOX;
	emit_rule(AIPI_RHSCMD);
	
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
				if( m_lookahead = AIPI_TRUE )
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
			else if( m_lookahead == AIPI_PLAY )
			{
				matchToken(AIPI_PLAY);
				matchToken(EQUAL);
				if( m_lookahead = AIPI_TRUE )
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
				if( m_lookahead = AIPI_TRUE )
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
			else if( m_lookahead == AIPI_PATH )
			{
				matchToken(AIPI_PATH);
				matchToken(EQUAL);
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


}

void CAipi_ParserGUI::ctrl_mediaplayer()
{
	
	m_currentCmd = AIPI_CTRL_MEDIAPLAYER;
	emit_rule(AIPI_RHSCMD);
	
	
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
				if( m_lookahead = AIPI_TRUE )
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
			else if( m_lookahead == AIPI_PLAY )
			{
				matchToken(AIPI_PLAY);
				matchToken(EQUAL);
				
				if( m_lookahead = AIPI_TRUE )
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
				if( m_lookahead = AIPI_TRUE )
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
			else if( m_lookahead == AIPI_PATH )
			{
				matchToken(AIPI_PATH);
				matchToken(EQUAL);
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

}

void CAipi_ParserGUI::ctrl_imagefilter()
{
	
	m_currentCmd = AIPI_CTRL_IMAGEFILTER;
	emit_rule(AIPI_RHSCMD);
	
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
				if( m_lookahead = AIPI_TRUE )
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
				if( m_lookahead = AIPI_TRUE )
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
			else if( m_lookahead == AIPI_PATH )
			{
				matchToken(AIPI_PATH);
				matchToken(EQUAL);
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


}

void CAipi_ParserGUI::ctrl_listoption()
{
	
	m_currentCmd = AIPI_CTRL_LISTOPTION;
	emit_rule(AIPI_RHSCMD);
	
	
	matchToken(AIPI_CTRL_LISTOPTION);
	matchToken(OPEN_PARENTHESIS);
	

	while( m_lookahead != CLOSE_PARENTHESIS && m_lookahead != NUL )
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
				if( m_lookahead = AIPI_TRUE )
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
				if( m_lookahead = AIPI_TRUE )
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
			else if( m_lookahead == AIPI_INSERT )
			{
				matchToken(AIPI_INSERT);
				matchToken(EQUAL);
				matchToken(OPEN_BRACE);
				while( m_lookahead != CLOSE_BRACE )
				{
					if( m_lookahead == OPEN_PARENTHESIS )
					{
						matchToken(OPEN_PARENTHESIS);
						matchToken(LITERAL);
						matchToken(COMMA);
						matchToken(LITERAL);
						matchToken(CLOSE_PARENTHESIS);
						if( m_lookahead != CLOSE_BRACE)
						{
							matchToken(COMMA);
						}

					}
					else
					{
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


}

void CAipi_ParserGUI::ctrl_oledb()
{
	
	m_currentCmd = AIPI_CTRL_OLEDB;
	emit_rule(AIPI_RHSCMD);
	
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
				if( m_lookahead = AIPI_TRUE )
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
				if( m_lookahead = AIPI_TRUE )
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
				if( m_lookahead = AIPI_TRUE )
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



////////////////////////////////////////////////////////////////////////
//// Script Parser ////
//////////////////////////////////////////////////////////////////////////


void CAipi_ParserGUI::script_definition()
{
	//AfxMessageBox(_T("Script Definition"));

	CAipi_Lexer lex;
	CAipi_Tokenizer tkz;
	CAipi_ScriptCode scp;

	matchToken(LT);
	matchToken(AIPI_SCRIPT);
	matchToken(AIPI_LANGUAGE);
	matchToken(EQUAL);
	CString strToken = tkz.v_lastToken().data();
	
	//AfxMessageBox(_T("LEXER TOKEN......"));
	//AfxMessageBox(strToken);
	
	matchToken(LITERAL);
	matchToken(GT);
	unsigned int index1 = tkz.v_sizeTokenizer();

	while(m_lookahead != LT && m_lookahead != NUL )
	{
		++g_currentPos;
		m_lookahead = lex.addTokenizerGUI();
		
	}

	matchToken(LT);
	matchToken(SLASH);
	matchToken(AIPI_SCRIPT);
	matchToken(GT);

	unsigned int index2 = tkz.v_sizeTokenizer();
		
	


}

void CAipi_ParserGUI::script_js_function_definition()
{
	//AfxMessageBox(_T("Java Function"));

	CString str;
	CAipi_Tokenizer tkz;

	int openBrace = 0;
	int closeBrace = 0;
	int nParam = 1;
	
	CAipi_Lexer lex;
	long index1 = tkz.v_sizeTokenizer()-1;
	long index2 = 0;
	long pos1 = tkz.v_lastPosition();
	long pos2 = 0;
	int  line = tkz.v_getLineByIndex(index1);

	matchToken(JS_FUNCTION );
	tstring sFuncName =  tkz.v_lastToken();
	CString strFuncName = sFuncName.data();
	//AfxMessageBox(strFuncName);
	long intForm = tkz.v_lastIntFormToken();	
    matchToken(IDENTIFIER);
	matchToken(OPEN_PARENTHESIS);
	//AfxMessageBox(_T("open parentesis"));
	while(m_lookahead != CLOSE_PARENTHESIS && m_lookahead != NUL )
	{
		++g_currentPos;
		m_lookahead = lex.addTokenizerGUI();
		
		//str.Format(_T("WHILE Look ahead...%d  " ), m_lookahead);
		//AfxMessageBox(str);
		//Symbols not allowed between the parenthesis
		switch( m_lookahead)
		{
			case COMMA:
				++nParam;
				break;
			case CLOSE_BRACE:
				return;
			case OPEN_PARENTHESIS:
				return;
			case NUL:
				return;
			
		}
	}

	//AfxMessageBox(_T("Salio del while parentesis"));
	//str.Format(_T("g_currentPos...%d  " ), g_currentPos);
	//AfxMessageBox(str);
	matchToken(CLOSE_PARENTHESIS);
	matchToken(OPEN_BRACE );
	if( m_lookahead == CLOSE_BRACE )
	{
		index2 = tkz.v_sizeTokenizer()-1;
		pos2 = tkz.v_lastPosition() + 1;
		matchToken(CLOSE_BRACE );
	}
	else
	{
	
		openBrace++;
		while (openBrace != closeBrace && m_lookahead != NUL  )
		{
			++g_currentPos;
			m_lookahead = lex.addTokenizerGUI();
		
			if( m_lookahead == OPEN_BRACE )
			{
				++openBrace;
				//CString str;
				//str.Format(_T("Open Brace...%d  " ), openBrace);
				//AfxMessageBox(str);
			}
			if( m_lookahead == CLOSE_BRACE )
			{
				++closeBrace;
				//CString str;
				//str.Format(_T("Close Brace...%d  " ), closeBrace);
				//AfxMessageBox(str);
			}

		}

		//AfxMessageBox(_T("Salio del while llaves"));
		index2 = tkz.v_sizeTokenizer()-1;
		pos2 = tkz.v_lastPosition() + 1;
		matchToken(CLOSE_BRACE );
	}
	
	/*
	str.Format(_T("Pos 2...%d  " ), pos2);
	AfxMessageBox(str);
	CString i1 = tkz.v_getTokenByIndex(index1).data();
	AfxMessageBox(_T("INDEX1"));
	AfxMessageBox(i1);
	CString i2 = tkz.v_getTokenByIndex(index2).data();
	AfxMessageBox(_T("INDEX2"));
	AfxMessageBox(i2);
	*/

	
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	const unsigned int CODE_LENGTH = 100000;
	CString strCode= _T("EMPTY");
	
	long docLength = rCtrl.GetLength();
	if( pos2 > docLength )
	{
		pos2 = docLength;
	}

	int iLength = pos2 - pos1 + 1;
	
	TextRange tr;
	tr.chrg.cpMin = pos1;
	tr.chrg.cpMax = pos2;
	char chCode[CODE_LENGTH];
						
	tr.lpstrText = chCode;
			
	if (iLength > CODE_LENGTH )
	{
		rCtrl.GetText(CODE_LENGTH, chCode);
	}
	else
	{
		//AfxMessageBox(_T("else"));
		rCtrl.GetTextRange(&tr);
	}	

	rCtrl.GetTextRange(&tr);
	strCode = (CString)chCode;
	//AfxMessageBox(strCode);

	//There is no parameters in the function
	if( nParam == 1 )
	{
		nParam = 0;
	}

	bool bLoaded = ScriptLoadCode(pos1, pos2, line, _T("JScript"), strCode, strFuncName);
	
	if( bLoaded )
	{
		CAipi_ScriptCode scpt;
		scpt.addScriptCode(intForm, sFuncName, index1, index2, pos1, pos2, nParam, _T("JScript"), strCode); 
	}
	
	


}



void CAipi_ParserGUI::script_vbs_function_definition()
{
	//AfxMessageBox(_T("Visual Basic Function"));

	CAipi_Lexer lex;
	CAipi_Tokenizer tkz;
	CString str;

	int nParam = 1;
	long index1 = tkz.v_sizeTokenizer()-1;
	long pos1 = tkz.v_lastPosition();
	int  line = tkz.v_getLineByIndex(index1);
	//str.Format(_T("Pos 1...%d  " ), pos1);
	//AfxMessageBox(str);

	matchToken(VBS_FUNCTION );
	tstring sFuncName =  tkz.v_lastToken();
	CString strFuncName = sFuncName.data();
	//AfxMessageBox(strFuncName);
	long intForm = tkz.v_lastIntFormToken();	

    matchToken(IDENTIFIER);
	matchToken(OPEN_PARENTHESIS);
	//AfxMessageBox(_T("open parentesis"));
	while(m_lookahead != CLOSE_PARENTHESIS && m_lookahead != NUL )
	{
		++g_currentPos;
		m_lookahead = lex.addTokenizerGUI();
		
		
		//str.Format(_T("WHILE Look ahead...%d  " ), m_lookahead);
		//AfxMessageBox(str);
		//Symbols not allowed between the parenthesis
		switch( m_lookahead)
		{			
			case COMMA:
				++nParam;
				break;
			case CLOSE_BRACE:
				return;
			case OPEN_PARENTHESIS:
				return;
			case _TEOF:
				return;
			
		}
	}
	//AfxMessageBox(_T("Salio del while parentesis"));
	//str.Format(_T("g_currentPos...%d  " ), g_currentPos);
	//AfxMessageBox(str);
	while(m_lookahead != VBS_END && m_lookahead != NUL )
	{
		++g_currentPos;
		m_lookahead = lex.addTokenizerGUI();
					
	}

	matchToken(VBS_END);
	long index2 = tkz.v_sizeTokenizer()-1;
	long pos2 = tkz.v_lastPosition() + 8;
	matchToken(VBS_FUNCTION);

	

	
	//str.Format(_T("Pos 2...%d  " ), pos2);
	//AfxMessageBox(str);
	CString i1 = tkz.v_getTokenByIndex(index1).data();
	//AfxMessageBox(_T("INDEX1"));
	//AfxMessageBox(i1);
	CString i2 = tkz.v_getTokenByIndex(index2).data();
	//AfxMessageBox(_T("INDEX2"));
	//AfxMessageBox(i2);

	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	const unsigned int CODE_LENGTH = 100000;
	CString strCode= _T("EMPTY");
	
	long docLength = rCtrl.GetLength();
	if( pos2 > docLength )
	{
		pos2 = docLength;
	}

	int iLength = pos2 - pos1 + 1;
	
	TextRange tr;
	tr.chrg.cpMin = pos1;
	tr.chrg.cpMax = pos2;
	char chCode[CODE_LENGTH];
						
	tr.lpstrText = chCode;
			
	if (iLength > CODE_LENGTH )
	{
		rCtrl.GetText(CODE_LENGTH, chCode);
	}
	else
	{
		//AfxMessageBox(_T("else"));
		rCtrl.GetTextRange(&tr);
	}	

	rCtrl.GetTextRange(&tr);
	strCode = (CString)chCode;
	//AfxMessageBox(strCode);

	//There is no parameters in the function
	if( nParam == 1 )
	{
		nParam = 0;
	}

	bool bLoaded = ScriptLoadCode(pos1, pos2, line, _T("VBScript"), strCode, strFuncName);

	if( bLoaded )
	{
		CAipi_ScriptCode scpt;
		scpt.addScriptCode(intForm, sFuncName, index1, index2, pos1, pos2, nParam, _T("VBScript"), strCode); 
	}


		

}


void CAipi_ParserGUI::script_sql()
{
	CString str;
	CAipi_Tokenizer tkz;

	int openBrace = 0;
	int closeBrace = 0;
	int nParam = 0;
	//CString sSQL = _T("");
	
	matchToken(AIPI_SQLQUERY );
	tstring sSQLName =  tkz.v_lastToken();
	CString strSQLName = sSQLName.data();
	//AfxMessageBox(strFuncName);
	long intForm = tkz.v_lastIntFormToken();	
    matchToken(IDENTIFIER);
	matchToken(EQUAL);

	CAipi_Lexer lex;
	long index1 = tkz.v_sizeTokenizer()-1;
	long index2 = 0;
	long pos1 = tkz.v_lastPosition();
	long pos2 = 0;
	int  line = tkz.v_getLineByIndex(index1);
	
	matchToken(VERTICAL_BAR);
	//AfxMessageBox(_T("open parentesis"));
	while(m_lookahead != VERTICAL_BAR && m_lookahead != NUL )
	{
		++g_currentPos;
		m_lookahead = lex.addTokenizerGUI();
		if( m_lookahead == AIPI_VAR )
		{
			
			++nParam;
		}
		
		//sSQL += 	lex.m_sToken;
		
		//str.Format(_T("WHILE Look ahead...%d  " ), m_lookahead);
		//AfxMessageBox(str);
		//Symbols not allowed between the parenthesis
	}

	//AfxMessageBox(_T("Salio del while parentesis"));
	//str.Format(_T("g_currentPos...%d  " ), g_currentPos);
	//AfxMessageBox(str);
	//AfxMessageBox(strSQLName);
	index2 = tkz.v_sizeTokenizer()-1;
	pos2 = tkz.v_lastPosition() + 1;
	matchToken(VERTICAL_BAR );
	
	
	/*
	str.Format(_T("Pos 2...%d  " ), pos2);
	AfxMessageBox(str);
	CString i1 = tkz.v_getTokenByIndex(index1).data();
	AfxMessageBox(_T("INDEX1"));
	AfxMessageBox(i1);
	CString i2 = tkz.v_getTokenByIndex(index2).data();
	AfxMessageBox(_T("INDEX2"));
	AfxMessageBox(i2);
	*/

	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	const unsigned int CODE_LENGTH = 100000;
	CString strCode= _T("EMPTY");
	
	long docLength = rCtrl.GetLength();
	if( pos2 > docLength )
	{
		pos2 = docLength;
	}

	int iLength = pos2 - pos1 + 1;
	
	TextRange tr;
	tr.chrg.cpMin = pos1+1;
	tr.chrg.cpMax = pos2-1;
	char chCode[CODE_LENGTH];
						
	tr.lpstrText = chCode;
			
	if (iLength > CODE_LENGTH )
	{
		rCtrl.GetText(CODE_LENGTH, chCode);
	}
	else
	{
		//AfxMessageBox(_T("else"));
		rCtrl.GetTextRange(&tr);
	}	

	rCtrl.GetTextRange(&tr);
	strCode = (CString)chCode;
	//AfxMessageBox(strCode);
	
	

	CAipi_ScriptCode scpt;
	scpt.addScriptCode(intForm, sSQLName, index1, index2, pos1, pos2, nParam, _T("SQL"), strCode); 
	
	
	
}


