// Aipi_Error.cpp: implementation of the CAipi_Error class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_Error.h"
#include "AIPIEditorDoc.h"
#include "AIPIEditorView.h"

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

CAipi_Error::CAipi_Error()
{

}

CAipi_Error::~CAipi_Error()
{

}


CAipi_Error* CAipi_Error::addError(int index, CString msg, CString lnk, int categ )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_Error *pObject = new CAipi_Error();
    try
	{
		pObject->setMessage(msg);
		pObject->setLink(lnk);
		pObject->setCateg(categ);
		
		pMainFrame->gmError.insert(CMainFrame::g_mError::value_type(index, *pObject));
				
	}
	catch( CMemoryException* pErr)
	{
		AfxMessageBox(_T("Out of memory!!!"), MB_ICONSTOP | MB_OK);

		if(pObject)
		{
			delete pObject;
			pObject = NULL;
		}
		pErr->Delete();
	}
	
	return pObject;
}





int CAipi_Error::findErrorMembers(int e)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mError::iterator iter;
    iter = pMainFrame->gmError.find(e);
	if( iter != pMainFrame->gmError.end())
	{
		CAipi_Error err = (CAipi_Error)iter->second;
 	
		m_ErrorMsg = err.getMessage();
		m_ErrorLink = err.getLink();
		m_ErrorCateg = err.getCateg();
		
		
		return e;
	}
	
return NOT_FOUND;
	
}


int CAipi_Error::openDocFile(LPCTSTR lpszPathName)
{
	
	#define MAX_CHAR_PATH   254

	CString currentDir;
	GetCurrentDirectory( MAX_PATH, currentDir.GetBufferSetLength(MAX_CHAR_PATH) );
	//AfxMessageBox(currentDir);
	currentDir.ReleaseBuffer();

	CString execDir;
	GetModuleFileName( NULL, execDir.GetBufferSetLength(MAX_PATH), MAX_CHAR_PATH );
	//AfxMessageBox(execDir);
	execDir.ReleaseBuffer();
	
	//lpszPathName = _T("D:\\Project AIPI VS6\\AIPI\\Examples\\array_test.txt");
	/*
	if (!CScintillaDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	*/
	
		
	CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
	pApp->UpdateDocumentView(lpszPathName);

		
	if( pApp == NULL )
	{
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("The file was not found. Check the path and the name of the file."));
		//AfxMessageBox( _T("File was not found."));
		return NOT_FOUND;
	}

return FOUND;
}






void CAipi_Error::errorMark(unsigned int nLine)
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	
	//Find file path
	CAIPIEditorDoc* pDoc = (CAIPIEditorDoc*)pView->GetDocument();
	ASSERT_VALID(pDoc);
	CString strPath = pDoc->GetPathName();
	//AfxMessageBox(strPath);


	CScintillaCtrl& rCtrl = pView->GetCtrl();
	
	// Reset Scintilla Markers 
	rCtrl.MarkerDeleteAll(0);

	// Initilaize error markers
	rCtrl.MarkerDefine(0, SC_MARK_ARROW);
	rCtrl.MarkerSetFore(0, RGB( 80, 0, 0 ));
	rCtrl.MarkerSetBack(0, RGB( 255, 0, 0 ));
	
	// Set error marker to proper line
	rCtrl.MarkerAdd((nLine - 1), 0);
	rCtrl.GotoLine(nLine - 1);
	

}


void CAipi_Error::displayGUIError(int e, int type, CString desc)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buff[64];

	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();

	
	LPTSTR lpsErrLine =_T("0");
	LPTSTR lpsErrPos = _T("0");
	LPTSTR lpsErrCode = _T("0");
	LPTSTR lpsErrDesc = _T("No description has found for this error");
	LPTSTR lpsErrFile = _T(" - ");  

	
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

	//errorMark(g_currentLine);


	
	switch(type)
	{
	case LEX_ERROR:
		++g_LexError;
		break;
	case SINTAX_ERROR:
		++g_SintaxError;
		break;
	case SEMANT_ERROR:
		++g_SemantError;
		break;
	case WARNING_ERROR:
		++g_WarningError;
		break;
	case QUESTION_ERROR:
		++g_QuestionError;
		break;
	case STOP_ERROR:
		++g_StopError;
		break;
	case INFO_ERROR:
		++g_InfoError;
		break;
		
	}
	
	

	findErrorMembers(e);
	
	lpsErrCode = _itot( e, buff, 10 );
		
	
	CString strErrPos = _itot(g_currentPos, buff, 10);
	lpsErrPos = strErrPos.GetBuffer(0);  
	strErrPos.ReleaseBuffer();
	
	//CString strErrLine = _itot(g_currentLine, buff, 10);
	CString strErrLine = _itot(rCtrl.LineFromPosition(g_currentPos) + 1, buff, 10);
	lpsErrLine = strErrLine.GetBuffer(0);  
	strErrLine.ReleaseBuffer();
	
	CString strErrDesc = m_ErrorMsg + desc;
	lpsErrDesc = strErrDesc.GetBuffer(0);  
	strErrDesc.ReleaseBuffer();

	CString strErrFile = g_currentFile;
	lpsErrFile = g_currentFile.GetBuffer(0);
	strErrFile.ReleaseBuffer();
	
	
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
	
}


void CAipi_Error::displayFileError(int e, int type, CString desc)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buff[64];

	/*
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	*/
	
	LPTSTR lpsErrLine =_T("0");
	LPTSTR lpsErrPos = _T("0");
	LPTSTR lpsErrCode = _T("0");
	LPTSTR lpsErrDesc = _T("No description has found for this error");
	LPTSTR lpsErrFile = _T(" - ");  
	
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

	//errorMark(g_currentLine);


	
	switch(type)
	{
	case LEX_ERROR:
		++g_LexError;
		break;
	case SINTAX_ERROR:
		++g_SintaxError;
		break;
	case SEMANT_ERROR:
		++g_SemantError;
		break;
	case WARNING_ERROR:
		++g_WarningError;
		break;
	case QUESTION_ERROR:
		++g_QuestionError;
		break;
	case STOP_ERROR:
		++g_StopError;
		break;
	case INFO_ERROR:
		++g_InfoError;
		break;
		
	}
	
	

	findErrorMembers(e);
	
	lpsErrCode = _itot( e, buff, 10 );
		
	
	CString strErrPos = _itot(g_fcurrentPos, buff, 10);
	lpsErrPos = strErrPos.GetBuffer(0);  
	strErrPos.ReleaseBuffer();
	
	CString strErrLine = _itot(g_currentLine, buff, 10);
	//CString strErrLine = _itot(rCtrl.LineFromPosition(g_fcurrentPos) + 1, buff, 10);
	lpsErrLine = strErrLine.GetBuffer(0);  
	strErrLine.ReleaseBuffer();
	
	CString strErrDesc = m_ErrorMsg + desc;
	lpsErrDesc = strErrDesc.GetBuffer(0);  
	strErrDesc.ReleaseBuffer();

	CString strErrFile = g_currentFile;
	lpsErrFile = g_currentFile.GetBuffer(0);
	strErrFile.ReleaseBuffer();
	
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

  
	
}


void CAipi_Error::displayRunTimeFileError(int e, int type, CString path, CString desc)
{
	
	CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
	BOOL alreadyOpen = pApp->UpdateDocumentView(path);
	//if document is not already open then open it
	if( alreadyOpen == FALSE )
	{
		pApp->m_pAIPIEditorDocTemplate->OpenDocumentFile(path);
	}
		
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buff[64];

	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();

	
	LPTSTR lpsErrLine =_T("0");
	LPTSTR lpsErrPos = _T("0");
	LPTSTR lpsErrCode = _T("0");
	LPTSTR lpsErrDesc = _T("No description has found for this error");
	LPTSTR lpsErrFile = _T("");  
	
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

	//errorMark(g_currentLine);


	
	switch(type)
	{
	case LEX_ERROR:
		++g_LexError;
		break;
	case SINTAX_ERROR:
		++g_SintaxError;
		break;
	case SEMANT_ERROR:
		++g_SemantError;
		break;
	case WARNING_ERROR:
		++g_WarningError;
		break;
	case QUESTION_ERROR:
		++g_QuestionError;
		break;
	case STOP_ERROR:
		++g_StopError;
		break;
	case INFO_ERROR:
		++g_InfoError;
		break;
		
	}
	
	

	findErrorMembers(e);
	
	lpsErrCode = _itot( e, buff, 10 );
		
	
	CString strErrPos = _itot(g_fcurrentPos, buff, 10);
	lpsErrPos = strErrPos.GetBuffer(0);  
	strErrPos.ReleaseBuffer();
	
	//CString strErrLine = _itot(g_currentLine, buff, 10);
	CString strErrLine = _itot(rCtrl.LineFromPosition(g_fcurrentPos) + 1, buff, 10);
	lpsErrLine = strErrLine.GetBuffer(0);  
	strErrLine.ReleaseBuffer();
	
	CString strErrDesc = m_ErrorMsg + desc;
	lpsErrDesc = strErrDesc.GetBuffer(0);  
	strErrDesc.ReleaseBuffer();

	CString strErrFile = g_currentFile;
	lpsErrFile = strErrFile.GetBuffer(0);  
	lpsErrFile = strErrFile.GetBuffer(0);
	
	
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

  
	
}






void CAipi_Error::printError()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ERROR MSG  *******"));
	
	//Print map container
	for( CMainFrame::g_mError::const_iterator iter = pMainFrame->gmError.begin(); iter!= pMainFrame->gmError.end(); ++iter)
	{
		CString strIndex =_T("N_ERROR_");
		CString strCateg =_T("CATEG_");
		
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Error Element  *******"));

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("No. Error: "));
		strIndex +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strIndex);
		
		CAipi_Error e = (CAipi_Error)iter->second;
 		
		tstring msg = e.getMessage();
		tstring lnk = e.getLink();
		int categ = e.getCateg();
				
	
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Message: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(msg.data());
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Link: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(lnk.data());
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Category: "));
		strCateg +=  _itot( categ, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCateg);
		
			
	}


}