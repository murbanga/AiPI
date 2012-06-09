// AIPIEditorDoc.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "AIPIEditorDoc.h"
#include "MainFrm.h"
#include "DocTemplateEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAIPIEditorDoc

IMPLEMENT_DYNCREATE(CAIPIEditorDoc, CScintillaDoc)

CAIPIEditorDoc::CAIPIEditorDoc()
{
}

BOOL CAIPIEditorDoc::OnNewDocument()
{
	/*
	if (!CDocument::OnNewDocument())
		return FALSE;
	*/

	if( !CScintillaDoc::OnNewDocument())
		return FALSE;

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	//Hide CommandDlgBar	
	if (pMainFrame->m_wndCommandDlgBar.IsVisible())
		pMainFrame->ShowControlBar(&(pMainFrame->m_wndCommandDlgBar), FALSE, FALSE);
	

	return TRUE;
}


CAIPIEditorDoc::~CAIPIEditorDoc()
{
}


BEGIN_MESSAGE_MAP(CAIPIEditorDoc, CScintillaDoc)
	//{{AFX_MSG_MAP(CAIPIEditorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAIPIEditorDoc diagnostics

#ifdef _DEBUG
void CAIPIEditorDoc::AssertValid() const
{
	CScintillaDoc::AssertValid();
}

void CAIPIEditorDoc::Dump(CDumpContext& dc) const
{
	CScintillaDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAIPIEditorDoc serialization
/*
void CAIPIEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
*/

/////////////////////////////////////////////////////////////////////////////
// CAIPIEditorDoc commands



BOOL CAIPIEditorDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CScintillaDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	
	
	//Hide CommandDlgBar when the interface is this one
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if (pMainFrame->m_wndCommandDlgBar.IsVisible())
		pMainFrame->ShowControlBar(&(pMainFrame->m_wndCommandDlgBar), FALSE, FALSE);
	
	// Add to MRU file list
	AddToRecentFileList(lpszPathName);
	
	return TRUE;
}


BOOL CAIPIEditorDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// Add to MRU file list
	AddToRecentFileList(lpszPathName);
	
	
	return CScintillaDoc::OnSaveDocument(lpszPathName);
}

void CAIPIEditorDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDocument::SetPathName(lpszPathName, FALSE);
	CDocTemplateEx* pDocTemplate = (CDocTemplateEx *)GetDocTemplate();
	pDocTemplate->AddToRecentFileList(lpszPathName);
	
	
	//CScintillaDoc::SetPathName(lpszPathName, bAddToMRU);
}


void CAIPIEditorDoc::AddToRecentFileList(LPCTSTR lpszPathName)
{
	((CAIPIApp*)AfxGetApp())->AddToRecentFileList(lpszPathName);
}



