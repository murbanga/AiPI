// Aipi_Main.cpp: implementation of the CAipi_Main class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_Main.h"



#include "../MainFrm.h"
#include "../ChildFrm.h"
#include "../OutputTabView.h"
#include "../AIPIEditorDoc.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAipi_Main::CAipi_Main()
{

}

CAipi_Main::~CAipi_Main()
{

}

void CAipi_Main::stopTimer(CPerfTimer t, CString msg)
{

	CString str;
	str.Format(msg + _T("%0.4f"),t.Elapsed());
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndOutputTabView.IsVisible())
	{
		pMainFrame->m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(0);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
		
	}
	t.Stop();

}


void CAipi_Main::buildGUI()
{
	g_bExecuteFlag  = false;
	CAipi_ParserGUI gp;
	gp.initParser();
	
}


void CAipi_Main::buildFile()
{
	g_bExecuteFlag  = false;
	
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CAIPIEditorDoc* pDoc = (CAIPIEditorDoc*)pView->GetDocument();
	ASSERT_VALID(pDoc);
	
	CString strFilePath = pDoc->GetPathName();
	g_currentFile = strFilePath;
	//AfxMessageBox(strFilePath);

	CString strExt = strFilePath.Right(3);
	//AfxMessageBox(strExt);

	if( strExt == _T("knw") || strExt == _T("txt") )
	{		
		
		CAipi_ParserFile pf;
		pf.initParser(strFilePath);
		pf.translation_unit();
		pf.endParser();
		
	}
	else
	{
		//Error message
		//Incompatible file extension
	}


		
}

void CAipi_Main::buildProject()
{
	//g_bExecuteFlag  = false;
}



void CAipi_Main::execExpParserGUI()
{
	CAipi_Lexer lex;
	lex.createTokenizerGUI();
	CAipi_ExpParserGUI par;
	par.initExpParserGUI();

	/*
	CAipi_Symbol sym;
	sym.printId_IntForm();
	sym.printId_Pos();
	sym.printId_Type();
	*/

	
	//CAipi_Tokenizer tkz;
	//tkz.v_printTokenizer();
	

	/*
	CAipi_STableNumeric st;
	st.printSTableNumeric();
	*/

	
}

void CAipi_Main::execExpParserFile()
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CAIPIEditorDoc* pDoc = (CAIPIEditorDoc*)pView->GetDocument();
	ASSERT_VALID(pDoc);
	
	CString strFilePath = pDoc->GetPathName();
	//AfxMessageBox(strFilePath);

	CString strExt = strFilePath.Right(3);
	//AfxMessageBox(strExt);

	if( strExt == _T("knw") || strExt == _T("txt") )
	{		
		
		CAipi_Lexer lex;
		lex.createTokenizerFile(strFilePath);
		CAipi_ExpParserFile par;
		par.initExpParserFile();
	}
	else
	{
		//Error message
		//Incompatible file extension
	}


	/*
	CAipi_Symbol sym;
	sym.printId_IntForm();
	sym.printId_Pos();
	sym.printId_Type();
	*/
	/*
	CAipi_Tokenizer tkz;
	tkz.v_printTokenizer();
	*/
	
	/*
	CAipi_STableNumeric st;
	st.printSTableNumeric();
	*/
}


void CAipi_Main::init()
{
	g_fcurrentPos = 0;
	g_currentPos = 0;
	g_currentLine = 1;
	g_TkzCurrentIndex = -1;

	g_currentAM = 0;
	g_currentBM = 0;
	g_currentJNode = 0;
	g_currentTK = 0;
	g_currentWM = 0;
	g_currentLHS = 0;
	g_currentRHS = 0;

	
	
		

//Clear interpreter data structures
	CAipi_Tokenizer tkz;
	tkz.v_clearTokenizer();
	
	CAipi_Symbol sym;
	sym.clearId_IntForm();
	

	CAipi_STableGlobalNumeric gnum;
	gnum.clearSTableNumeric();

	CAipi_STableGlobalLiteral glit;
	glit.clearSTableLiteral();

	CAipi_STableLocalNumeric lnum;
	lnum.clearSTableNumeric();

	CAipi_STableLocalLiteral llit;
	llit.clearSTableLiteral();


	CAipi_STableClass cl;
	cl.clearSTableClass();

	CAipi_ScriptCode scrt;
	scrt.clearScriptCode();

	CAipi_ScriptLocation sloc;
	sloc.clearScriptLocation();

	CAipi_CmdLocation cloc;
	cloc.clearCmdLocation();

///Clear RETE data structures
	CAipi_PM	pm;
	pm.clearPMStructs();

	CAipi_LHS lhs;
	lhs.clearLHS();

	CAipi_RHS rhs;
	rhs.clearRHS();

	CAipi_RHSCmd cmd;
	cmd.clearRHSCmd();

	CAipi_RETE_Cond co;
	co.clearCondStructs();

	CAipi_RepCond rco;
	rco.clearRepCondStructs();

	CAipi_RETE_Links lkn;
	lkn.clearLinks();

	CAipi_RETE_Operations op;
	op.clearOperation();
		

	
	CAipi_WM wm;
	wm.clearWM();
	wm.clearWMCondStructs();
	wm.clearCondWMStructs();

	CAipi_RETE_AM  am;
	am.clearAMStructs();
	am.clearLogicStructs();
	
	CAipi_RETE_BM  bm;
	bm.clearBM();

	CAipi_RETE_BME bme;
	bme.clearBME();

	CAipi_RETE_BMCond bmc;
	bmc.clearBMCond();

	CAipi_RETE_TK tk;
	tk.clearTKStructs();
	
	CAipi_RETE_NumVars nvar;
	nvar.clearNumVarStructs();

    CAipi_RETE_Vars var;
	var.clearVarsStructs();

	CAipi_RETE_TypeInt tint;
	tint.clearTypeInt();
	CAipi_RETE_TypeLong tlong;
	tlong.clearTypeLong();
	CAipi_RETE_TypeFloat tfloat;
	tfloat.clearTypeFloat();
	CAipi_RETE_TypeDouble tdouble;
	tdouble.clearTypeDouble();
	CAipi_RETE_TypeString tstr;
	tstr.clearTypeString(); 


	CAipi_RETE_DNode dn;
	dn.clearDNode();

	
	CAipi_RETE_JNode jn;
	jn.clearJNStructs();
	
		
	CAipi_RETE_NNode nn;
	nn.clearNNStructs();

	CAipi_RETE_NodeCond nc;
	nc.clearNodeCond();
	
	CAipi_RETE_PNode pn;
	pn.clearPNStructs();

	


	CAipi_CR_Priority pri;
	pri.clearCR_Priority();

	CAipi_CR_Recency rec;
	rec.clearCR_Recency();

	CAipi_CR_RecencyTags rectag;
	rectag.clearCR_RecencyTags();

	CAipi_CR_Specificity spe;
	spe.clearCR_Specificity();


}



int CAipi_Main::runInterp()
{
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Prescanning data..."), RGB(0,0,0), TRUE);

	init();

	//Clear listCtrl1
	pMainFrame->m_wndOutputTabView.m_listCtrl2.DeleteAllItems();
	//Clear editCtrl1
	pMainFrame->m_wndOutputTabView.DeleteAllEdit1(); 
	
	
	
	
	switch(g_dataSource)
	{
	case DATA_GUI:
		buildGUI();
		//execExpParserGUI();
		break;
	case DATA_FILE:
		buildFile();
		//execExpParserFile();
		break;
	case DATA_PROJECT:
		buildProject();
		break;
	}
	
	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);

	
	//test();
	
	
return 1;
}



void CAipi_Main::createNetRETE()
{
	CAipi_RETE_Net  net;  
	net.createAM();
	net.preAnalysis();
	net.createNet();
	
}



int CAipi_Main::parseExpertSystem(CString strFilePath)
{
	//Set progress bar
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	/*
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Prescanning data..."), RGB(0,0,0), TRUE);
	*/
	init();

	//Clear listCtrl1
	pMainFrame->m_wndOutputTabView.m_listCtrl2.DeleteAllItems();
	//Clear editCtrl1
	pMainFrame->m_wndOutputTabView.DeleteAllEdit1(); 
	
	CString strExt = strFilePath.Right(3);
	//AfxMessageBox(strExt);

	if( strExt == _T("knw") || strExt == _T("txt") )
	{		
		CAipi_ParserFile pf;
		pf.initParser(strFilePath);
		pf.translation_unit();
		pf.endParser();

		if( g_bStopFlag )
		{
			//AfxMessageBox(_T("STOP"));
			return AIPI_STOP;
		}
		if( pf.m_nError > 0 )
		{
			//AfxMessageBox(_T("ERROR1"));
			return AIPI_ERROR;
		}
	}
	else
	{
		//Error message
		//AfxMessageBox(_T("ERROR2"));
		//Incompatible file extension
		CAipi_Error err;
		err.displayFileError(FILE_READ, STOP_ERROR, _T("Incompatible file extension.Unable to read file") );
		return AIPI_ERROR;
	}
	/*
	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	*/
	//AfxMessageBox(_T("SUCCESS"));
return P_SUCCESS;	
}

int CAipi_Main::parseExpertSystem_continue()
{
	//Set progress bar
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	/*
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Prescanning data..."), RGB(0,0,0), TRUE);
	*/

	
	CAipi_ParserFile pf;
	pf.m_lookahead = g_currentLookahead;
	pf.translation_unit();
	pf.endParser();

	if( g_bStopFlag )
	{
		//AfxMessageBox(_T("STOP"));
		return AIPI_STOP;
	}
	if( pf.m_nError > 0 )
	{
		//AfxMessageBox(_T("ERROR1"));
		return AIPI_ERROR;
	}
	
	/*
	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	*/
	AfxMessageBox(_T("SUCCESS"));
return P_SUCCESS;	
}


void CAipi_Main::conflictSet(int crtype)
{
	CAipi_RETE_PNode pn;
	

	switch( crtype )
	{
	case AIPI_CR_RECENCY:
		pn.conflictResolution(AIPI_CR_RECENCY);
		break;
	case AIPI_CR_PRIORITY:
		pn.conflictResolution(AIPI_CR_PRIORITY);
		break;
	case AIPI_CR_SPECIFICITY:
		pn.conflictResolution(AIPI_CR_SPECIFICITY);
		break;
	case AIPI_CR_ORDER:
		pn.conflictResolution(AIPI_CR_ORDER);
		break;
    case AIPI_CR_LEX:
		pn.conflictResolution(AIPI_CR_LEX);
		break;
    case AIPI_CR_MEA:
		pn.conflictResolution(AIPI_CR_MEA);
		break;
	default:
		pn.conflictResolution(AIPI_CR_ORDER);
		break;
	}


}


void CAipi_Main::execute() 
{
	const static _TCHAR BASED_CODE szFilter[] = _T("Knowledge Files (*.knw; *.txt)|*.knw;*.txt|All Files (*.*)|*.*||");

	CFileDialog Fdlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if(Fdlg.DoModal() == IDOK)
 	{
 		g_includeDirective = true;

		CString path = Fdlg.GetPathName();
		g_currentFile = path;
 		CAipi_Main main;
		//AfxMessageBox(_T("ENTRA A EXPERT SYSTEM"));
		int r = main.parseExpertSystem(path);
		//AfxMessageBox(_T("SALE DE EXPERT SYSTEM"));
		
		if( r == AIPI_STOP )
		{
			//AfxMessageBox(_T("AIPI_STOP"));
			return;
		}
		if( r != AIPI_ERROR )
		{
			//AfxMessageBox(_T("Crea RETE NET Execute"));
			main.createNetRETE();
			//AfxMessageBox(_T("Termina RETE NET Execute"));
			//AfxMessageBox(_T("Crea CONFLICT SET Execute"));
			main.conflictSet(g_CRStrategy);
			//AfxMessageBox(_T("Termina CONFLICT SET Execute"));
		}
		else
		{
			//AfxMessageBox(_T("ERROR"));
			return;
		}
	}
 	else 
		return;
		
}

void CAipi_Main::execute_continue() 
{
	AfxMessageBox(_T("ENTRA A EXPERT SYSTEM CONTINUE"));
	int r = parseExpertSystem_continue();
	AfxMessageBox(_T("SALE DE EXPERT SYSTEM CONTINUE"));
		
	if( r == AIPI_STOP )
	{
		AfxMessageBox(_T("AIPI_STOP"));
		return;
	}
	if( r != AIPI_ERROR )
	{
		//AfxMessageBox(_T("Crea RETE NET execute continue"));
		createNetRETE();
		//AfxMessageBox(_T("Termina RETE NET execute continue"));
		//AfxMessageBox(_T("Crea CONFLICT SET execute continue"));
		conflictSet(g_CRStrategy);
		//AfxMessageBox(_T("Termina CONFLICT SET execute continue"));
		
		//Stop execute() function
		g_bStopFlag = true;
	}
	else
	{
		AfxMessageBox(_T("ERROR Execute Continue"));
		return;
	}
	
		
}




void CAipi_Main::test()
{

	//CAipi_Lexer lex;
	//lex.testScanGUI();
	//lex.testScanFile();
	//lex.testGetTextFileRange(45, 63);	
	
	/*
	tk.testGetTextFileRange();
	CAipi_Error e;
	e.printError();
	*/
	
//////////////////////////////////////////////
/// Print Results ////
//////////////////////////////////////////////
	
////////////////////////////////////////////////
	/// RETE Network ///
//////////////////////////////////////////////////

	CAipi_WM wmo;
	wmo.printWMIForm();

	
	CAipi_LHS lhso;
	lhso.printLHSIForm();
	lhso.printRepCond();	

	CAipi_RHS rhso;
	rhso.printRHSIForm();
	CAipi_RHSCmd cmdo;
	cmdo.printRHSCmd();


	
	/*	
	amo.printAM_WM();
	amo.printWM_AM();
	amo.printCond_AM();
	amo.printAM_Cond();
	amo.printEQ();
	amo.printET();
	amo.printNE();
	amo.printLT();
	amo.printLE();
	amo.printGT();
	amo.printGE();
	amo.printAS();
*/

/*
	wmo.printEQ_Cond_WM();
	wmo.printNE_Cond_WM();
	wmo.printGE_Cond_WM();
	wmo.printGT_Cond_WM();
	wmo.printLT_Cond_WM();
	wmo.printLE_Cond_WM();
	wmo.printAS_Cond_WM();


	wmo.printEQ_WM_Cond();
	wmo.printNE_WM_Cond();
	wmo.printGE_WM_Cond();
	wmo.printGT_WM_Cond();
	wmo.printLT_WM_Cond();
	wmo.printLE_WM_Cond();
	wmo.printAS_WM_Cond();

*/

/*	
	CAipi_RETE_Vars varo;

	varo.printVar_I();
	varo.printVar_A();
	varo.printVar_V();

*/ 

/*	
	CAipi_PM pmo;
	pmo.printPM_IDVar();
	pmo.printPM_ATTRVar();
	pmo.printPM_VALVar();
	pmo.printPM_RelCond();
	
*/
	
	CAipi_PM pmo;
	pmo.printPM_IDVarIForm();
	pmo.printPM_ATTRVarIForm();
	pmo.printPM_VALVarIForm();
	pmo.printPM_RelCond();
	
	//pmo.printPM_Cond();
	pmo.printPM_Fact();
	

	CAipi_RETE_Net  net;  
	net.createAM();
	net.preAnalysis();
	net.createNet();

	CAipi_RETE_AM amo;
	//amo.createAM();
	amo.printAM_WM();
	amo.printWM_AM();
	amo.printCond_AM();
	amo.printAM_Cond();
	amo.printEQ();
	amo.printET();
	amo.printNE();
	amo.printLT();
	amo.printLE();
	amo.printGT();
	amo.printGE();
	amo.printAS();

	
	
	CAipi_RETE_Links lko;
	lko.printCondLink();
	
	
	
	CAipi_RETE_TK tko;
	tko.printTK();
	//tko.printLinkTK();
	tko.printWM_ParentTK();
	tko.printWM_ChildTK();
	

	//tko.printTKParent_TKChild();
	
	//tko.printTKParent_TKLink();


	CAipi_RETE_BM bmo;
	
	bmo.printLinkBM_TK();
	pmo.printPM_BM();
	//bmo.printBM();
	

	
	CAipi_RETE_BME bmeo;
	//bmeo.printBM_WM();
	//bmeo.printBME();


/*
	CAipi_RepCond rpo;
	rpo.printRepCond();
	rpo.printRepCondEx();
*/
	
	
	CAipi_RETE_Cond co;
	co.printCond1();
	co.printCond2();
	

	
	CAipi_RETE_Node no;
	no.printNode();
	
	/*
	CAipi_RETE_JNode jno;
	jno.printJN();
	*/
	/*
	CAipi_RETE_DNode dno;
	dno.printDNode();
	
	*/


	CAipi_RETE_NodeCond nco;
	//nco.printNodeCond();
	

	/*
	CAipi_RETE_TypeInt		typei;
	CAipi_RETE_TypeLong		typel;
	CAipi_RETE_TypeFloat	typef;
	CAipi_RETE_TypeDouble   typed;
	CAipi_RETE_TypeString   types;

	typei.printTypeInt();
	typel.printTypeLong();
	typef.printTypeFloat();
	typed.printTypeDouble();
	types.printTypeString();
	
	
	CAipi_RETE_Operations op;
	op.printOperation();
	op.printAttr_Type();


	CAipi_RETE_NumVars num;
	num.printTK_LeftV();
	num.printTK_RightV();
	num.printNumVar_BM();

*/

	
	
	pmo.printPM_PNode();

	CAipi_RETE_PNode pn;
	pn.printPN();
	/*
	pn.printAgendaPM();
	pn.printFiredPM();
	*/
	
	//pn.conflictResolution(CR_ORDER);
	//pn.conflictResolution(CR_RECENCY);
	//pn.conflictResolution(CR_PRIORITY);
	
	amo.printAM_WM();
	amo.printWM_AM();
	bmo.printLinkBM_TK();
	pmo.printPM_BM();
	pmo.printPM_PNode();

	pn.printPN();
	pn.printAgendaPM();
	pn.printFiredPM();
	pn.printRefractionPM();
	
	
	tko.printTK();
	tko.printTKParent_TKChild();
	tko.printTKParent_TKLink();
	tko.printWM_ParentTK();
	tko.printWM_ChildTK();
	
	//wmo.printWMIForm();
	
	
	CAipi_CR_Recency ro;
	ro.printCR_Recency();


	
	



/*
	wmo.printWMIForm();
	amo.printAM_WM();
	bmo.printLinkBM_TK();
	bmeo.printBM_WM();

	pn.saveFiredPM();
	pn.printAgendaPM();
	pn.printFiredPM();
*/
	

/*	
	CAipi_CR_Recency ro;
	ro.calcRecencyFiredPM();
	ro.printCR_Recency();

	CAipi_CR_RecencyTags rto;
	rto.calcRecencyTagsFiredPM();
	rto.printCR_RecencyTags();

	CAipi_CR_Priority po;
	po.calcPriorityFiredPM();
	po.printCR_Priority();

	CAipi_CR_Specificity spf;
	spf.calcSpecificityFiredPM();
	spf.printCR_Specificity();
*/
	


//////////////////////////////////////////////
	///Interpreter////
/////////////////////////////////////////////
	
	//CAipi_Tokenizer tk;
	//tk.v_printTokenizer();
		
	//CAipi_Symbol sb;
	//sb.printId_IntForm();
	
	
	/*
	CAipi_STableClass c;
	c.printSTableClass();
	*/


	CAipi_STableGlobalNumeric numg;
	numg.printSTableNumeric();
	CAipi_STableGlobalLiteral litg;
	litg.printSTableLiteral();
	CAipi_STableLocalNumeric numl;
	numl.printSTableNumeric();
	CAipi_STableLocalLiteral litl;
	litl.printSTableLiteral();
	
	
	CAipi_ScriptCode s;
	s.printScriptCode();
	

	CAipi_ScriptLocation loc;
	loc.printScriptLocation();

	CAipi_CmdLocation cmdloc;
	cmdloc.printCmdLocation();


/////////////////////////////////////////////////////

	

}