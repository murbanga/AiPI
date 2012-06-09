// AIPI.h : main header file for the AIPI application
//

#if !defined(AFX_AIPI_H__783CEE5B_C230_402F_A52E_89FD59AA5B4A__INCLUDED_)
#define AFX_AIPI_H__783CEE5B_C230_402F_A52E_89FD59AA5B4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
// main symbols
#include "resource.h"   
#include "OXSkins.h"  
#include "OXRegistryValFile.h"
  
#include ".\ScintillaCtrl\ScintillaResource.h"
#include ".\ScriptObject\ScriptObject.h"

#include "OleDBConnectionProp.h"
#include "OleDBConnectionDlg.h"
#include "Query_i.h"


/////////////////////////////////////////////////////////////////////////////
// CAIPIApp:
// See AIPI.cpp for the implementation of this class
//

class CAIPIApp : public COXSkinnedApp
{
public:
	CAIPIApp();
	virtual ~CAIPIApp();
	void AddToRecentFileList(LPCTSTR lpszPathName);
	void LoadConfig();
	void SaveConfig();
	void AipiOpenDocumentFile(CString lpszFileName);

	BOOL OpenDBConnDlg(int iDatabase);
	BOOL OpenDB(int iDatabase);
	
	BOOL UpdateDocumentView(CString strPathName);
	BOOL SetDocumentView(CString doc);
	int	 CountOpenDocuments();
	int  CountOpenScintillaDoc();
	int	 SaveAllOpenDocs();	
	int  SaveAllScintillaDocs();
	int	 SaveAllProjectDocs(); 	
	int	 SearchProjectExt(); 
	
	

protected:
	BOOL InitATL();
	void ExitSQLQuery();
	void SetRegistry();
	
	
public:
	CView* GetFirstView(CDocument* pDoc);
	CView* GetFirstView(CFrameWnd* pFrameWnd);
	CDocument* SearchDocument(LPCTSTR pszDocPath);
	BOOL OpenDocument(CDocTemplate* pDocTemplate, LPCTSTR pszDocPath, CDocument*& pDoc, CFrameWnd*& pFrameWnd, CView*& pView);

public:
	CMultiDocTemplate* m_pAIPIDocTemplate;
	CMultiDocTemplate* m_pAIPIEditorDocTemplate;
	CMultiDocTemplate* m_pAIPITreeDocTemplate;
	CMultiDocTemplate* m_pAIPIProjDocTemplate;
	
	
	ULONG_PTR m_gdiplusToken;
	HINSTANCE   m_hSciDLL;
	HINSTANCE   m_hDll;
	BOOL m_bATLInited;
	
	
	

	ATL::CSession			m_Session;
	ATL::CDataSource		m_DataSource;
	COleDBConnectionProp	m_props;

	

	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAIPIApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
		//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAIPIApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

ATL::CSession* GetSession();
ATL::CDataSource* GetDataSource();
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIPI_H__783CEE5B_C230_402F_A52E_89FD59AA5B4A__INCLUDED_)
