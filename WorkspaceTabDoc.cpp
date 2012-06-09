// WorkspaceTabDoc.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "WorkspaceTabDoc.h"
#include "WorkspaceTabView.h"
#include "WorkspaceView.h"
#include "DocTemplateEx.h"

#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTabDoc

IMPLEMENT_DYNCREATE(CWorkspaceTabDoc, CDocument)

CWorkspaceTabDoc::CWorkspaceTabDoc()
{
}


BOOL CWorkspaceTabDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	
	m_strInfoArray.RemoveAll();
	m_strInfoArray.SetSize(nMaxInfo);

	//AfxMessageBox(_T("OnNewDocument"));
	m_strInfoArray.SetAt(0, g_projectDate);
	m_strInfoArray.SetAt(1, g_projectName);
	m_strInfoArray.SetAt(2, g_projectAuthor);
	m_strInfoArray.SetAt(3, g_projectDesc);
	m_strInfoArray.SetAt(4, g_projectRoot);
	m_strInfoArray.SetAt(5, g_projectInference);
	m_strInfoArray.SetAt(6, g_projectResource[0]);
	m_strInfoArray.SetAt(7, g_projectResource[1]);
	m_strInfoArray.SetAt(8, g_projectResource[2]);
	m_strInfoArray.SetAt(9, g_projectResource[3]);

	/*
	m_mapFunction.ClearMap();
	HTREEITEM hItem = NULL;
	m_mapFunction.AddFunction(_T("Fun11"), hItem, _T("File11"), _T("Path11"), 1, 0);
	m_mapFunction.AddFunction(_T("Fun22"), hItem, _T("File22"), _T("Path22"), 1, 0);
	m_mapFunction.AddFunction(_T("Alfaro"), hItem, _T("File3"), _T("Path3"), 1, 0);
	m_mapFunction.AddFunction(_T("Cienfuegos"), hItem, _T("File4"), _T("Path4"), 1, 0);
	m_mapFunction.AddFunction(_T("Parada"), hItem, _T("File5"), _T("Path5"), 1, 0);
	m_mapFunction.AddFunction(_T("Ernesto"), hItem, _T("File6"), _T("Path6"), 1, 0);
	m_mapFunction.PrintMap();

	
	CFunctionProperties *p;
	p = m_mapFunction.FindbyRef(_T("Alfaro"));
	CString str = p->getFile();
	AfxMessageBox(str);

	str = m_mapFunction.FindFilebyRef(_T("Ernesto"));
	AfxMessageBox(str);
*/

	

	return TRUE;
}


CWorkspaceTabDoc::~CWorkspaceTabDoc()
{

}


BEGIN_MESSAGE_MAP(CWorkspaceTabDoc, CDocument)
	//{{AFX_MSG_MAP(CWorkspaceTabDoc)
	
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTabDoc diagnostics

#ifdef _DEBUG
void CWorkspaceTabDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWorkspaceTabDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTabDoc serialization

void CWorkspaceTabDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		//Add storing code
		//ar << g_projectName << g_projectAuthor << g_projectDesc << g_projectRoot;
			
	}
	else
	{
		//Add loading code here
		//ar >> g_projectName >> g_projectAuthor >> g_projectDesc >> g_projectRoot;
	}

	SerializeTreeCtrl(ar);

	
}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTabDoc commands
void CWorkspaceTabDoc::SerializeTreeCtrl(CArchive& ar)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	POSITION pos = GetFirstViewPosition();
	CWorkspaceView* pView = NULL;

	while (pos != NULL && pView == NULL)
	{
		CView* pTemp = GetNextView(pos);
		pView = DYNAMIC_DOWNCAST(CWorkspaceView, pTemp);
	}

	if (pView == NULL)
	{
		MessageBox(NULL, _T("Couldn't find a view to serialize!"),
			AfxGetAppName(), MB_OK | MB_ICONHAND);
	}
	else
	{
		pView->Serialize(ar);
		m_strInfoArray.Serialize(ar);
		m_mapFunction.Serialize(ar);
		pMainFrame->m_wndWorkspaceTabView.Serialize(ar);
	}
}



void CWorkspaceTabDoc::ProjectSave(CString sFileName) 
{
	OnSaveDocument(sFileName);
	//AfxMessageBox(_T("Project Save"));
	
}



void CWorkspaceTabDoc::ProjectOpen() 
{
	
	const static _TCHAR BASED_CODE szFilter[] = _T("Project Files (*.apj)|*.apj|All Files (*.*)|*.*||");
	CFileDialog openDlg( TRUE, _T("*.apj"), NULL, OFN_HIDEREADONLY | OFN_EXPLORER, szFilter, NULL );
	
	if(openDlg.DoModal()==IDOK)
	{	
		CString szFileName( openDlg.GetPathName() );
		OnOpenDocument(szFileName);
		m_szFileName = szFileName;
			// Add to MRU file list
		AddToRecentFileList(m_szFileName);
		
	
	}
	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if (pMainFrame->m_wndWorkspaceTabView.IsVisible() == FALSE)
	{
		//Set visible at first
		pMainFrame->ShowControlBar(&pMainFrame->m_wndWorkspaceTabView, TRUE ,TRUE);
			
	}
	
	pMainFrame->m_wndWorkspaceTabView.m_TabViewContainer.SetActivePageIndex(0);
	
}


void CWorkspaceTabDoc::ProjectClose() 
{
	OnCloseDocument();
	
	
}

void CWorkspaceTabDoc::ProjectSaveAs() 
{
	const static _TCHAR BASED_CODE szFilter[] = _T("Project Files (*.apj)|*.apj|All Files (*.*)|*.*||");
	CFileDialog fileDlg( FALSE, _T("*.apj"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER , szFilter, NULL );
	

	if(fileDlg.DoModal()==IDOK)
	{	
		//CString szfileName( openDlg.GetFileName() );
		CString szFileName( fileDlg.GetPathName() );
		
		OnSaveDocument(szFileName);

	}	
	

}


void CWorkspaceTabDoc::ProjectNew() 
{
	OnNewDocument();
	
	
}


CWorkspaceTabDoc * CWorkspaceTabDoc::GetWorkspaceDoc()
{
      CMDIChildWnd * pChild =
          ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();

      if ( !pChild )
          return NULL;

      CDocument * pDoc = pChild->GetActiveDocument();

      if ( !pDoc )
         return NULL;

      // Fail if doc is of wrong kind
      if ( ! pDoc->IsKindOf( RUNTIME_CLASS(CWorkspaceTabDoc) ) )
         return NULL;

      return (CWorkspaceTabDoc *) pDoc;
}




void CWorkspaceTabDoc::AddToRecentFileList(LPCTSTR lpszPathName)
{
	((CAIPIApp*)AfxGetApp())->AddToRecentFileList(lpszPathName);
}




void CWorkspaceTabDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDocument::SetPathName(lpszPathName, FALSE);
	CDocTemplateEx* pDocTemplate = (CDocTemplateEx *)GetDocTemplate();
	pDocTemplate->AddToRecentFileList(lpszPathName);


}


/*
CFunctionProperties* CWorkspaceTabDoc::AddFunction( const TCHAR *szName, HTREEITEM item, const TCHAR *szFile, const TCHAR *szPath, int lang, int rtype)
{
	
	CFunctionProperties *pObject = new CFunctionProperties();
    try
	{
		pObject->setName(szName);
		pObject->setItem(item);
		pObject->setFile(szFile);
		pObject->setPath(szPath);
		pObject->setLanguaje(lang);
		pObject->setReturnType(rtype);

		m_mapFunction.SetAt(szName, pObject);
	
				
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
*/

/*
void CWorkspaceTabDoc::PrintMap()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CObject *pNext;
	CString ref;
	CFunctionProperties *pCurrent;
	POSITION pos;
	TCHAR buffer[8];

	

	if( m_mapFunction.GetCount() == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("FunctionProperties Map is Empty"));	
	}
	else
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*** FUNCTION PROPERTIES MAP ***"));
		
		pos = m_mapFunction.GetStartPosition();
		while( pos != NULL )
		{
			
			CString strItem = _T("ITEM_");
			CString strFile = _T("FILE_");
			CString strPath = _T("PATH_");
			CString strLang = _T("LANG");
			CString strRType = _T("RETURN_TYPE");

			m_mapFunction.GetNextAssoc(pos, ref, pNext);
			
			pCurrent = (CFunctionProperties *) pNext;
			
			
			pMainFrame->m_wndOutputTabView.AddMsg1(ref);
			//AfxMessageBox(ref);
			HTREEITEM hItem = pCurrent->getItem();
			int item = (int )hItem;
			strItem =  _itot( item, buffer, 10 );
			//AfxMessageBox(strItem);
			pMainFrame->m_wndOutputTabView.AddMsg1(strItem);
			strFile += (const TCHAR *)pCurrent->getFile();
			//AfxMessageBox(strFile);
			pMainFrame->m_wndOutputTabView.AddMsg1(strFile);
			strPath += (const TCHAR *)pCurrent->getPath();
			//AfxMessageBox(strPath);
			pMainFrame->m_wndOutputTabView.AddMsg1(strPath);
			int lang = pCurrent->getLanguage();
			strLang +=  _itot( lang, buffer, 10 );
			//AfxMessageBox(strLang);
			pMainFrame->m_wndOutputTabView.AddMsg1(strLang);
			int rtype = pCurrent->getReturnType();
			strRType += _itot( rtype, buffer, 10 );
			//AfxMessageBox(strRType);
			pMainFrame->m_wndOutputTabView.AddMsg1(strRType);
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("************************"));
				
		}

	}
	


}
*/
