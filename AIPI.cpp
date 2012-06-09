// AIPI.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AIPI.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "DocTemplateEx.h"

#include "AIPIDoc.h"
#include "AIPIView.h"
#include "AIPIEditorDoc.h"
#include "AIPIEditorView.h"
#include "AIPITreeDoc.h"
#include "AIPITreeView.h"
#include "WorkspaceTabDoc.h"
#include "WorkspaceTabView.h"
#include "WorkspaceView.h"

#include <afxole.h>
#include <initguid.h>
#include "Query_i.c"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAIPIApp

BEGIN_MESSAGE_MAP(CAIPIApp, CWinApp)
	//{{AFX_MSG_MAP(CAIPIApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAIPIApp construction

CAIPIApp::CAIPIApp():
m_pAIPIDocTemplate(NULL),
m_pAIPIEditorDocTemplate(NULL),
m_pAIPITreeDocTemplate(NULL)
{
	
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


CAIPIApp::~CAIPIApp()
{
	/*
	delete m_pAIPIDocTemplate;
	delete m_pAIPIEditorDocTemplate;
	delete m_pAIPITreeDocTemplate;
	delete m_pAIPIProjDocTemplate;
	*/

}
/////////////////////////////////////////////////////////////////////////////
// The one and only CAIPIApp object
CAIPIApp theApp;

ATL::CSession* GetSession()
	{ return &theApp.m_Session; }

ATL::CDataSource* GetDataSource()
	{ return &theApp.m_DataSource; }


COXRegistryItem g_Registry;

////////////////////////////////////////////////////////////////////////////////
/// CAIPIApp Set software register

CQueryModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

LONG CQueryModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CQueryModule::Lock()
{
	AfxOleLockApp();
	return 1;
}

LPCTSTR CQueryModule::FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (*p1 != NULL)
	{
		LPCTSTR p = p2;
		while (*p != NULL)
		{
			if (*p1 == *p)
				return CharNext(p1);
			p = CharNext(p);
		}
		p1++;
	}
	return NULL;
}


BOOL CAIPIApp::OpenDBConnDlg(int iProvider)
{
		
	LPCTSTR lpszAppSection = _T("Connection");
	m_props.LoadSettings();
	COleDBConnectionDlg dlg;
	dlg.m_props = m_props;
	
	//Enables or disable edit controls in COleDBConnectionDlg
	switch(iProvider)
	{
	case MS_ACCESS:
		g_iDBProvider = MS_ACCESS;
		break;
	case MS_SQLSERVER:
		g_iDBProvider = MS_SQLSERVER;
		break;
	case MS_ORACLE:
		g_iDBProvider = MS_ORACLE;
		break;
	case ORACLE:
		g_iDBProvider = ORACLE;
		break;
	case MYSQL:
		g_iDBProvider = MYSQL;
		break;
	case DB2:
		g_iDBProvider = DB2;
		break;
	default:
		g_iDBProvider = UNDEFINE;
	}
	

	
	//Control the database type of connection 
	if(dlg.DoModal() == IDOK)
	{
		m_props = dlg.m_props;
		m_props.SaveSettings();
		switch(iProvider)
		{
			case MS_ACCESS:
				
				if(!m_props.ConnectMSAccess(&theApp.m_DataSource,&m_Session))
					return false;
				return true;
				
			case MS_SQLSERVER:
				
				if(!m_props.ConnectMSSQLServer(&theApp.m_DataSource,&m_Session))
					return false;
				return true;
				
			case MS_ORACLE:
				
				if(!m_props.ConnectMSOracle(&theApp.m_DataSource,&m_Session))
					return false;
				return true;
				
			case ORACLE:
				
				if(!m_props.ConnectOracle(&theApp.m_DataSource,&m_Session))
					return false;
				return true;
				
			case MYSQL:
				
				if(!m_props.ConnectMySQL(&theApp.m_DataSource,&m_Session))
					return false;
				return true;
				
			case DB2:
				
				if(!m_props.ConnectDB2(&theApp.m_DataSource,&m_Session))
					return false;
				return true;
				
		}


	}
	
	return false;
}

BOOL CAIPIApp::OpenDB(int iProvider)
{
		
	LPCTSTR lpszAppSection = _T("Connection");
	m_props.LoadSettings();
	
	//Enables or disable edit controls in COleDBConnectionDlg
	switch(iProvider)
	{
	case MS_ACCESS:
		g_iDBProvider = MS_ACCESS;
		break;
	case MS_SQLSERVER:
		g_iDBProvider = MS_SQLSERVER;
		break;
	case MS_ORACLE:
		g_iDBProvider = MS_ORACLE;
		break;
	case ORACLE:
		g_iDBProvider = ORACLE;
		break;
	case MYSQL:
		g_iDBProvider = MYSQL;
		break;
	case DB2:
		g_iDBProvider = DB2;
		break;
	default:
		g_iDBProvider = UNDEFINE;
	}
	

	
	//Control the database type of connection 
		m_props.SaveSettings();
		switch(iProvider)
		{
			case MS_ACCESS:
				
				if(!m_props.ConnectMSAccess(&theApp.m_DataSource,&m_Session))
					return false;
				return true;
				
			case MS_SQLSERVER:
				
				if(!m_props.ConnectMSSQLServer(&theApp.m_DataSource,&m_Session))
					return false;
				return true;
				
			case MS_ORACLE:
				
				if(!m_props.ConnectMSOracle(&theApp.m_DataSource,&m_Session))
					return false;
				return true;
				
			case ORACLE:
				
				if(!m_props.ConnectOracle(&theApp.m_DataSource,&m_Session))
					return false;
				return true;
				
			case MYSQL:
				
				if(!m_props.ConnectMySQL(&theApp.m_DataSource,&m_Session))
					return false;
				return true;
				
			case DB2:
				
				if(!m_props.ConnectDB2(&theApp.m_DataSource,&m_Session))
					return false;
				return true;
				
		}


	
	
	return false;
}
	


void CAIPIApp::ExitSQLQuery()
{
	/*
	if(m_Session.m_spOpenRowset)
		m_Session.Close();
	if(m_DataSource.m_spInit)
		m_DataSource.Close();
	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
		CoUninitialize();
	}
	*/

}



BOOL CAIPIApp::InitATL()
{
	
	m_bATLInited = TRUE;

#if _WIN32_WINNT >= 0x0400
	HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	HRESULT hRes = CoInitialize(NULL);
#endif

	if (FAILED(hRes))
	{
		m_bATLInited = FALSE;
		return FALSE;
	}

	_Module.Init(ObjectMap, AfxGetInstanceHandle());
	_Module.dwThreadID = GetCurrentThreadId();

	LPTSTR lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
	TCHAR szTokens[] = _T("-/");

	BOOL bRun = TRUE;
	LPCTSTR lpszToken = _Module.FindOneOf(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_QUERY, FALSE);
			_Module.UnregisterServer(TRUE); //TRUE means typelib is unreg'd
			bRun = FALSE;
			break;
		}
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_QUERY, TRUE);
			_Module.RegisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		lpszToken = _Module.FindOneOf(lpszToken, szTokens);
	}

	if (!bRun)
	{
		m_bATLInited = FALSE;
		_Module.Term();
		CoUninitialize();
		return FALSE;
	}

	hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
		REGCLS_MULTIPLEUSE);
	if (FAILED(hRes))
	{
		m_bATLInited = FALSE;
		CoUninitialize();
		return FALSE;
	}	

	return TRUE;

}


void CAIPIApp::SetRegistry()
{
	g_Registry.SetFullRegistryItem(	_T("\\CurrentUser\\Software\\AIPISoft\\AIPI\\"));
	CString sVersion= g_Registry.GetStringValue(_T("Version"));
	if (sVersion!=_T("1.10"))
	{
		while (TRUE)
		{
			CString sSubKey=g_Registry.EnumerateSubkey(0);
			if (!sSubKey.IsEmpty())
			{
				sSubKey=_T("\\CurrentUser\\Software\\AIPISoft\\AIPI\\") + sSubKey +_T("\\");
				COXRegistryItem reg;
				reg.SetFullRegistryItem((LPCTSTR) sSubKey);
				reg.Delete();
			}
			else
				break;
		}
		g_Registry.Delete();
	}

	g_Registry.Close();

	/*
	COXRegistryItem regItem(_T("\\Software\\AipiSoft\\Aipi\\"));
	regItem.SetStringValue(_T("Aipi"), _T("Name"));
	regItem.SetNumberValue(9, _T("Number"));
	*/
}

void CAIPIApp::LoadConfig()
{

	COXRegistryValFile regfile(HKEY_CURRENT_USER, _T("AipiConfig"), _T("AipiApp"));
	if (regfile.GetLength() > 0)
	{
		CArchive ar(&regfile, CArchive::load);
		ar >> g_iSkinType;
		ar >> g_projectName;
		ar >> g_projectRoot;

    }

}

void CAIPIApp::SaveConfig()
{
	COXRegistryValFile regfile(HKEY_CURRENT_USER, _T("AipiConfig"), _T("AipiApp"));

	CArchive ar(&regfile, CArchive::store);
	ar << g_iSkinType;
	ar << g_projectName;
	ar << g_projectRoot;
	

}



BOOL CAIPIApp::UpdateDocumentView(CString strPathName)
{
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
		
		CString strDoc;
		BOOL alreadyOpen = FALSE;
		
			
		//no doc manager - no templates
		if (pApp->m_pDocManager)
		{
			//walk all templates
			CDocTemplate* pTemplate;
			POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
			
			while (pos )
			{
				pTemplate = pApp->m_pDocManager->GetNextDocTemplate(pos);
				ASSERT(pTemplate);

				//walk all documents in the template
				POSITION pos2 = pTemplate->GetFirstDocPosition();
				pTemplate->GetDocString(strDoc, CDocTemplate::docName);
				
				while (pos2 )
				{
					CDocument* pDoc = pTemplate->GetNextDoc(pos2);
					ASSERT(pDoc);
					CString strDocPath = pDoc->GetPathName();
					
					if( strDocPath == strPathName)
					{
						alreadyOpen = TRUE;
						pDoc->SetPathName(strPathName);
						POSITION pos = pDoc->GetFirstViewPosition();
						CView* pView = pDoc->GetNextView(pos);
						CFrameWnd* pFrame = pView->GetParentFrame();
						pTemplate->InitialUpdateFrame(pFrame, pDoc);
						pView->UpdateWindow();
						//pDoc->OnOpenDocument(strPathName);
							
						
					}
				
				}
			}
		}
		
	
return alreadyOpen;		
		
}



int CAIPIApp::CountOpenDocuments()
{
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
		
		//Count up the number of CScintillaView's we have (excluding this one)
		int nDoc = 0;
		CString strDoc = _T("");
		
		//no doc manager - no templates
		if (pApp->m_pDocManager)
		{
			//walk all templates
			CDocTemplate* pTemplate;
			POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
			
			while (pos )
			{
				pTemplate = pApp->m_pDocManager->GetNextDocTemplate(pos);
				ASSERT(pTemplate);

				//walk all documents in the template
				POSITION pos2 = pTemplate->GetFirstDocPosition();
				pTemplate->GetDocString(strDoc, CDocTemplate::docName);
				//AfxMessageBox(strDoc);

				while (pos2 )
				{
					CDocument* pDoc = pTemplate->GetNextDoc(pos2);
					ASSERT(pDoc);
					CString name = pDoc->GetPathName();
					//AfxMessageBox(name);
					++nDoc;
										
				}
			}
		}

		
return nDoc;		 
}


int CAIPIApp::SaveAllOpenDocs()
{
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
		
		//Count up the number of CScintillaView's we have (excluding this one)
		int nDoc = 0;
		CString strDoc = _T("");
		
		//no doc manager - no templates
		if (pApp->m_pDocManager)
		{
			//walk all templates
			CDocTemplate* pTemplate;
			POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
			
			while (pos )
			{
				pTemplate = pApp->m_pDocManager->GetNextDocTemplate(pos);
				ASSERT(pTemplate);

				//walk all documents in the template
				POSITION pos2 = pTemplate->GetFirstDocPosition();
				pTemplate->GetDocString(strDoc, CDocTemplate::docName);
				//AfxMessageBox(strDoc);

				while (pos2 )
				{
					CString fileExt = _T("");
					CDocument* pDoc = pTemplate->GetNextDoc(pos2);
					ASSERT(pDoc);
					if( strDoc == _T("AipiSes") )
						fileExt = _T(".ssn");
					else if ( strDoc == _T("AipiRul") )
						fileExt = _T(".knw");
					else if ( strDoc == _T("AipiTree") )
						fileExt = _T(".idt");
					else if ( strDoc == _T("AipiProj") )
						fileExt = _T(".apj");
					
					else
					{
						//AfxMessageBox(_T("No valid file extension were found. No documents were saved."));
						return -1;
					}


					CString fileName = pDoc->GetTitle() + fileExt;
					//AfxMessageBox(fileName);
					CString currentDir;
					GetCurrentDirectory( MAX_SIZE_PATH, currentDir.GetBufferSetLength(MAX_SIZE_PATH) );
					//AfxMessageBox(currentDir);
					currentDir.ReleaseBuffer();

					CString filePathName = currentDir + _T("\\") + fileName;
					//AfxMessageBox(filePathName);
					pDoc->OnSaveDocument(filePathName);
					
					
					++nDoc;
										
				}
			}
		}

		
return nDoc;		 
}






int CAIPIApp::SaveAllProjectDocs()
{
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
		
		//Count up the number of CScintillaView's we have (excluding this one)
		int nDoc = 0;
		CString strDoc = _T("");
		
		//no doc manager - no templates
		if (pApp->m_pDocManager)
		{
			//walk all templates
			CDocTemplate* pTemplate;
			POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
			
			while (pos )
			{
				pTemplate = pApp->m_pDocManager->GetNextDocTemplate(pos);
				ASSERT(pTemplate);

				//walk all documents in the template
				POSITION pos2 = pTemplate->GetFirstDocPosition();
				pTemplate->GetDocString(strDoc, CDocTemplate::docName);
				//AfxMessageBox(strDoc);

				while (pos2 )
				{
					CString fileExt = _T("");
					CDocument* pDoc = pTemplate->GetNextDoc(pos2);
					ASSERT(pDoc);
					
					if ( strDoc == _T("AipiProj") )
					{
						fileExt = _T(".apj");
						
					
					
					}
					else
					{
						AfxMessageBox(_T("No valid file extension were found. No documents were saved."));
						return -1;
					}

					CString fileName = pDoc->GetTitle() + fileExt;
					//AfxMessageBox(fileName);
					CString currentDir;
					GetCurrentDirectory( MAX_SIZE_PATH, currentDir.GetBufferSetLength(MAX_SIZE_PATH) );
					//AfxMessageBox(currentDir);
					currentDir.ReleaseBuffer();

					CString filePathName = currentDir + _T("\\") + fileName;
					//AfxMessageBox(filePathName);
					pDoc->OnSaveDocument(filePathName);
					
					
					++nDoc;
										
				}
			}
		}

		
return nDoc;		 
}


int CAIPIApp::SearchProjectExt()
{
	CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
		
	int nDoc = 0;
	CString strExt = _T("");
		
		//no doc manager - no templates
		if (pApp->m_pDocManager)
		{
			//walk all templates
			CDocTemplate* pTemplate;
			POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
			
			while (pos )
			{
				pTemplate = pApp->m_pDocManager->GetNextDocTemplate(pos);
				ASSERT(pTemplate);

				//walk all documents in the template
				POSITION pos2 = pTemplate->GetFirstDocPosition();
				pTemplate->GetDocString(strExt, CDocTemplate::filterExt);
				
				if( strExt == _T("apj"))
				{
					//AfxMessageBox(strExt);
					return FOUND;	
				}
				else
				{
					return NOT_FOUND;
				}
			}
		}

return NOT_FOUND;				
}

int CAIPIApp::SaveAllScintillaDocs()
{
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
		
		//Count up the number of CScintillaView's we have (excluding this one)
		int nDoc = 0;
		CString strDoc = _T("");
		
		//no doc manager - no templates
		if (pApp->m_pDocManager)
		{
			//walk all templates
			CDocTemplate* pTemplate;
			POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
			
			while (pos )
			{
				pTemplate = pApp->m_pDocManager->GetNextDocTemplate(pos);
				ASSERT(pTemplate);

				//walk all documents in the template
				POSITION pos2 = pTemplate->GetFirstDocPosition();
				pTemplate->GetDocString(strDoc, CDocTemplate::docName);
				//AfxMessageBox(strDoc);

				while (pos2 )
				{
					CString fileExt = _T("");
					CDocument* pDoc = pTemplate->GetNextDoc(pos2);
					ASSERT(pDoc);
					if ( strDoc == _T("AipiRul") )
					{
						fileExt = _T(".knw");
						CString fileName = pDoc->GetTitle() + fileExt;
						//AfxMessageBox(fileName);
						CString currentDir;
						GetCurrentDirectory( MAX_SIZE_PATH, currentDir.GetBufferSetLength(MAX_SIZE_PATH) );
						//AfxMessageBox(currentDir);
						currentDir.ReleaseBuffer();

						CString filePathName = currentDir + _T("\\") + fileName;
						//AfxMessageBox(filePathName);
						pDoc->OnSaveDocument(filePathName);
					
					
						++nDoc;
					
					}
					else
					{
						//AfxMessageBox(_T("No valid file extension were found. No documents were saved."));
						return -1;
					}


					
										
				}
			}
		}

		
return nDoc;		 
}


int CAIPIApp::CountOpenScintillaDoc()
{
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
		
		//Count up the number of CScintillaView's we have (excluding this one)
		int nScintillaViews = 0;
		CString strDoc = _T("");
		
		//no doc manager - no templates
		if (pApp->m_pDocManager)
		{
			//walk all templates
			CDocTemplate* pTemplate;
			POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
			
			while (pos )
			{
				pTemplate = pApp->m_pDocManager->GetNextDocTemplate(pos);
				ASSERT(pTemplate);

				//walk all documents in the template
				POSITION pos2 = pTemplate->GetFirstDocPosition();
				pTemplate->GetDocString(strDoc, CDocTemplate::docName);
				//AfxMessageBox(strDoc);

				while (pos2 )
				{
					CDocument* pDoc = pTemplate->GetNextDoc(pos2);
					ASSERT(pDoc);
					CString name = pDoc->GetPathName();
					//AfxMessageBox(name);
										
					//walk all views in the document
					POSITION pos3 = pDoc->GetFirstViewPosition();
					
					while (pos3 )
					{
						CView* pView = pDoc->GetNextView(pos3);
						ASSERT(pView);
						
						// if we want to count only CScintillaView documents (.knw)
						if (pView->IsKindOf(RUNTIME_CLASS(CScintillaView)) && ::IsWindow(pView->GetSafeHwnd()))
						{
							++nScintillaViews;
							
							//AfxMessageBox(name);
						}
					}
					
					
				}
			}
		}

		
return nScintillaViews;		 
}


BOOL CAIPIApp::SetDocumentView(CString doc)
{
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
		BOOL alreadyOpen = FALSE;
		CString strDoc = _T("");
		
		//no doc manager - no templates
		if (pApp->m_pDocManager)
		{
			//walk all templates
			CDocTemplate* pTemplate;
			POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
			
			while (pos )
			{
				pTemplate = pApp->m_pDocManager->GetNextDocTemplate(pos);
				ASSERT(pTemplate);

				//walk all documents in the template
				POSITION pos2 = pTemplate->GetFirstDocPosition();
				pTemplate->GetDocString(strDoc, CDocTemplate::docName);
				
				//AfxMessageBox(_T("DocName"));
				//AfxMessageBox(strDoc);

				while (pos2 )
				{
					CDocument* pDoc = pTemplate->GetNextDoc(pos2);
					ASSERT(pDoc);
					CString name = pDoc->GetPathName();
					/*					
					AfxMessageBox(_T("DocPath:"));
					AfxMessageBox(name);
					AfxMessageBox(doc);
					*/
										
					//get view position in the document
					POSITION pos3 = pDoc->GetFirstViewPosition();


					if( name == doc )
					{
						alreadyOpen = TRUE;
											
						CView* pView = pDoc->GetNextView(pos3);
						ASSERT(pView);
						
						// if we want to count only CScintillaView documents (.knw)
						if (pView->IsKindOf(RUNTIME_CLASS(CScintillaView)) && ::IsWindow(pView->GetSafeHwnd()))
						{
							/*
							CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
							pFrame->MDIActivate(pView);
							AfxMessageBox(_T("Entro View"));
							return alreadyOpen;		
							*/
							CWnd* pMainWnd = AfxGetMainWnd();
							ASSERT(pMainWnd && pMainWnd->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)));
							CMDIFrameWnd* pMDIMain = static_cast<CMDIFrameWnd*>(pMainWnd);
							ASSERT(pView);
							CWnd* pChildFrame = pView->GetParent();
							ASSERT(pChildFrame && pChildFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd)));
							pMDIMain->MDIActivate(pChildFrame);

						}
						
					
					}
					
				}
			}
		}

		
return alreadyOpen;	 
}




CView* CAIPIApp::GetFirstView(CDocument* pDoc)
{
	// --- In  : pDoc : A valid CDocument object
	// --- Out : 
	// --- Returns : The first view attached to the specified document
	// --- Effect : 

	ASSERT(pDoc != NULL);

	CView * pView = NULL;
	POSITION viewPos = NULL;

	// Get the first view in the collection
	viewPos = pDoc->GetFirstViewPosition();
	if (viewPos != NULL)
		{
		pView = pDoc->GetNextView(viewPos);
		ASSERT(pView != NULL);
		}

#ifdef _DEBUG
	if (pView == NULL)
		TRACE0("CAIPIApp::GetFirstView : No view found\n");
#endif // _DEBUG

	return pView;
}


void CAIPIApp::AipiOpenDocumentFile(CString lpszFileName) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	ASSERT_VALID(m_pAIPIProjDocTemplate);

	POSITION Pos = m_pAIPIProjDocTemplate->GetFirstDocPosition();
	if( Pos == NULL )
		return;

	CDocument *pDoc = m_pAIPIProjDocTemplate->GetNextDoc(Pos);
	if (pDoc == NULL )
		return;

	/*
	Pos == pDoc->GetFirstViewPosition();
	if( Pos == NULL )
		return;

	
	CView *pView = pDoc->GetNextView(Pos);
	if ( pView == NULL )
		return;

	CWnd *pWnd = pView->GetParent();
	if( pWnd == NULL )
		return;
*/
	
	
	

	CString sFileExt = lpszFileName.Right(3);
	//AfxMessageBox(sFileExt);
	
	if(!sFileExt.IsEmpty())
	{
		if( sFileExt == _T("apj"))
		{
			CString sFileName = g_projectName + _T(".apj");
			CString sFilePath = g_projectRoot + _T("\\") + sFileName;
			//AfxMessageBox(sFilePath);
			CWorkspaceTabDoc *pDoc = CWorkspaceTabDoc::GetWorkspaceDoc();
			pDoc->ProjectSave(sFilePath);
			m_pAIPIProjDocTemplate->CloseAllDocuments(TRUE);
			
					
		}
	}

//Show PropertiesBar and WorkspaceTabView when open a odcument .knw	
/*
	if (pMainFrame->m_wndWorkspaceTabView.IsVisible() == FALSE)
	{
		//Set visible at first
		pMainFrame->ShowControlBar(&pMainFrame->m_wndWorkspaceTabView, TRUE ,TRUE);
		pMainFrame->ShowControlBar(&pMainFrame->m_wndPropertiesBar, TRUE ,TRUE);
	}
	
	pMainFrame->m_wndWorkspaceTabView.m_TabViewContainer.SetActivePageIndex(0);
*/
	
}


BOOL CAIPIApp::OpenDocument(CDocTemplate* pDocTemplate, LPCTSTR pszDocPath, 
	CDocument*& pDoc, CFrameWnd*& pFrameWnd, CView*& pView)
{
	// --- In  : pDocTemplate : The document template to use
	//			 pszDocPath : The file path of the document to open
	// --- Out : pDoc : The document that is opened
	//			 pFrameWnd : The associated MDI child frame window
	//			 pView : The associated view (the first one)
	// --- Returns : Whether it succeeded or not
	// --- Effect : Uses the specified doc template the open a document with the
	//				spcified file path
	ASSERT(pDocTemplate != NULL);

	// ... Initialize output parameters
	pDoc = NULL;
	pFrameWnd = NULL;
	pView = NULL;

	//AfxMessageBox(_T("Hola"));
	// ... Check whether the document has already been opened
	pDoc = SearchDocument(pszDocPath);
	if (pDoc != NULL)
	{
		// Document has already been opened, attach a new view to it
		pFrameWnd = pDocTemplate->CreateNewFrame(pDoc, NULL);
		if (pFrameWnd == NULL)
		{
			TRACE0("CAIPIApp::OpenDocument : Failed to create new frame for existing document.\n");
			pDoc = NULL;
			return FALSE;
		}
		
		// ... Frame is initially visible, this is necessary to send
		//     WM_INITIALUPDATE to the view
		pDocTemplate->InitialUpdateFrame(pFrameWnd, pDoc, TRUE);
		pView = GetFirstView(pFrameWnd);
		ASSERT(pView != NULL);
	}
	else
	{
		// Document has not yet been opened, open it now
		// ... Frame is initially visible, this is necessary to send
		//     WM_INITIALUPDATE to the view
		pDoc = pDocTemplate->OpenDocumentFile(pszDocPath, TRUE);
		if (pDoc == NULL)
		{
			TRACE0("COXChildFrameState::OpenDocument : Failed to open document, failing\n");
			return FALSE;
		}

		pView = GetFirstView(pDoc);
		ASSERT(pView != NULL);
		pFrameWnd = pView->GetParentFrame();
		ASSERT(pFrameWnd != NULL);
	}


	return TRUE;
}





CDocument* CAIPIApp::SearchDocument(LPCTSTR pszDocPath)
{
	// --- In  : pszDocPath : File path of a document
	// --- Out : 
	// --- Returns : The open document with that file path or NULL otherwise
	// --- Effect : 

	if (pszDocPath == NULL)
		// ... Can only search for documents with a non-empty name
		return NULL;

	CDocument* pDoc = NULL;
	POSITION templatePos = NULL;
	CDocTemplate* pDocTemplate = NULL;
	templatePos = AfxGetApp()->GetFirstDocTemplatePosition();
	while((pDoc == NULL) && (templatePos != NULL))
		{
		pDocTemplate = AfxGetApp()->GetNextDocTemplate(templatePos);
		ASSERT(pDocTemplate != NULL);
		if (pDocTemplate->MatchDocType(pszDocPath, pDoc) != CDocTemplate::yesAlreadyOpen)
			pDoc = NULL;
		}

	return pDoc;
}

CView* CAIPIApp::GetFirstView(CFrameWnd* pFrameWnd)
{
	// --- In  : pFrameWnd : The frame window to use
	// --- Out : 
	// --- Returns : The first view that is child of the specified MDI child frame window
	// --- Effect : 
	
	CView* pView = NULL;
	CWnd* pWnd = pFrameWnd->GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);
	pView = DYNAMIC_DOWNCAST(CView, pWnd);
	if (pView == NULL)
		{
		pView = pFrameWnd->GetActiveView();
		}
	return pView;
}



/////////////////////////////////////////////////////////////////////////////
// CAIPIApp Initialization

BOOL CAIPIApp::InitInstance()
{
	//Initialize ATL libraries
	/*
	if (!InitATL())
		return FALSE;
		*/
	
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// Initialize COM
	CoInitialize(NULL);
	

	AfxEnableControlContainer();

	 //Set application skin style
	 LoadConfig();
	 
   
	 switch(g_iSkinType)
	 {
	 case OXSkinClassic:
		 SetCurrentSkin(_T("Classic"));
		 break;
	 case OXSkinOfficeXP:
		 SetCurrentSkin(_T("Office XP"));
		 break;
	 case OXSkinOffice2003:
		 SetCurrentSkin(_T("Office 2003"));
		 break;
	 case OXSkinNone:
		 SetCurrentSkin(_T("Classic"));
		 break;
	 default:
		SetCurrentSkin(_T("Office XP"));
		 break;
	 
	 }
	
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	_com_error* e = NULL;
	try
	{
		//Load the scintilla dll
		m_hSciDLL = LoadLibrary(_T("SciLexer.dll"));
		if (m_hSciDLL == NULL)
		{ 
			AfxMessageBox(_T("Scintilla DLL is not installed, Please download the SciTE editor and copy the SciLexer.dll into this application's directory"));
			return FALSE;
		}

   	}
	catch(_com_error& e)
	{
		CString strMsg = _T("Apparently you don't have script object installed\nDownload it here at:www.microsoft.com/scripting/");
		AfxMessageBox( strMsg, MB_OK);
		TRACE1("Error: %s\n", (LPSTR) e.ErrorMessage());

	}

	
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	//SetRegistry();
	SetRegistryKey(_T("AIPISoft"));
	
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	
	m_pAIPIDocTemplate = new CDocTemplateEx(
		IDR_AIPITYPE,
		RUNTIME_CLASS(CAIPIDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAIPIView),
		ID_FILE_FILES_MRU1);
	m_pAIPIDocTemplate->SetContainerInfo(IDR_AIPITYPE_CNTR_IP);
	AddDocTemplate(m_pAIPIDocTemplate);


	m_pAIPIEditorDocTemplate = new CDocTemplateEx(
		IDR_SCINTITYPE,
		RUNTIME_CLASS(CAIPIEditorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAIPIEditorView),
		ID_FILE_FILES_MRU1);
	AddDocTemplate(m_pAIPIEditorDocTemplate);

	/*
	m_pAIPIEditorDocTemplate = new CDocTemplateEx(
		IDR_SCINTITYPE1,
		RUNTIME_CLASS(CAIPIEditorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAIPIEditorView),
		ID_FILE_FILES_MRU1);
	AddDocTemplate(m_pAIPIEditorDocTemplate);
	*/

	m_pAIPITreeDocTemplate = new CDocTemplateEx(
		IDR_TREEEDTYPE,
		RUNTIME_CLASS(CAIPITreeDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAIPITreeView),
		ID_FILE_FILES_MRU1);
	AddDocTemplate(m_pAIPITreeDocTemplate);

	
	m_pAIPIProjDocTemplate = new CDocTemplateEx(
		IDR_PROJTYPE,
		RUNTIME_CLASS(CWorkspaceTabDoc),
		RUNTIME_CLASS(CChildFrame), 
		RUNTIME_CLASS(CWorkspaceView),
		ID_FILE_PROJ_MRU1);
	AddDocTemplate(m_pAIPIProjDocTemplate);

	
	
	
	
	/*
	if(!OpenDBConnDlg())
	{
		return FALSE;
	}
	*/
	

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	
	// Do not open a new (empty) doc by default
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;


	
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

    
	
	// Since we allow floating control bars MDI child windows, and these can only be created once
	// we have a main window, we need to restore the bar size state here. (not on CMainFrame::OnCreate())
	g_iWorkspaceStore = AIPI_FILE;

	pMainFrame->LoadWorkspace();
	pMainFrame->RecalcLayout();

	
	CRect rect;
	pMainFrame->GetClientRect(rect);
	rect.DeflateRect(0, 0);
	pMainFrame->m_wndWorkspaceTabView.MoveWindow(&rect);
	pMainFrame->m_wndOutputTabView.MoveWindow(&rect);
	
	//Init GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

	
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CAIPIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAIPIApp message handlers


int CAIPIApp::ExitInstance() 
{
	


	//g_Registry.SetFullRegistryItem(_T("CurrentUser\\Software\\AIPISoft\\AIPI\\"));
	//g_Registry.SetStringValue(_T("1.10"),_T("Version"));
	ExitSQLQuery();
	
	//Save application skin style
	SaveConfig();

/*
	TCHAR buffer[8];
   CString	str =  _itot( g_iSkinType, buffer, 10 );
   AfxMessageBox(_T("Exit CAIPIApp"));
   AfxMessageBox(str);
*/
	
	//Shutdown GDI+
	Gdiplus::GdiplusShutdown(m_gdiplusToken);

	//Free up the Scintilla DLL
	if (m_hSciDLL)
    FreeLibrary(m_hSciDLL);

	//Clear memory data from induction window
	g_df.ClearData();

	
	

	
	return CWinApp::ExitInstance();
}

void CAIPIApp::AddToRecentFileList(LPCTSTR lpszPathName)
{
	
	CDocument *pDoc = SearchDocument(lpszPathName);

	if( pDoc != NULL )
	{
		// lpszPathName will be added to the top of the MRU list. 
		// If lpszPathName already exists in the MRU list, it will be moved to the top
		if (m_pRecentFileList != NULL)	
		{
			m_pRecentFileList->Add(lpszPathName);
			//AfxMessageBox(lpszPathName);
		}
	}
}



BOOL CAIPIApp::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	BOOL bResult = CWinApp::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
	if (bResult)
		return TRUE;
	
	POSITION pos = m_pDocManager->GetFirstDocTemplatePosition();
	while (pos != NULL)	
	{
		CDocTemplate* pTemplate = m_pDocManager->GetNextDocTemplate(pos);
		ASSERT_KINDOF(CDocTemplate, pTemplate);
		if (pTemplate->IsKindOf(RUNTIME_CLASS(CDocTemplateEx)))		
		{
			if ((nID>=((CDocTemplateEx *)pTemplate)->GetMenuID()) &&
					(nID<=((CDocTemplateEx *)pTemplate)->GetMenuID()+MRU_RANGE))	
				bResult |= pTemplate->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);		
		}
	}
	return bResult;		
	
	
	//return CWinApp::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



