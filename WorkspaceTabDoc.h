#if !defined(AFX_WORKSPACETABDOC_H__A90B50A0_583C_4B02_A502_5276AC639EF3__INCLUDED_)
#define AFX_WORKSPACETABDOC_H__A90B50A0_583C_4B02_A502_5276AC639EF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkspaceTabDoc.h : header file
//
#include "FunctionProperties.h"

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTabDoc document

class CWorkspaceTabDoc : public CDocument
{
protected:
	CWorkspaceTabDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CWorkspaceTabDoc)

// Attributes
public:
	
	enum { nLinesPerPage = 12 };
	enum { nMaxInfo = 10 };

	CString			m_szFileName;	
	CStringArray	m_strInfoArray;
	CMapFunctionProperties m_mapFunction;
	
// Operations
protected:
	void SerializeTreeCtrl(CArchive& ar);
	void AddToRecentFileList(LPCTSTR lpszPathName);

public:
	void ProjectOpen();
	void ProjectSave(CString sFileName);
	void ProjectSaveAs();
	void ProjectClose();
	void ProjectNew();
	//CFunctionProperties* CWorkspaceTabDoc::AddFunction( const TCHAR *szName, HTREEITEM item, const TCHAR *szFile, const TCHAR *szPath, int lang, int rtype);
	//void PrintMap();

public:
	static CWorkspaceTabDoc *GetWorkspaceDoc();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceTabDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	protected:
	virtual BOOL OnNewDocument();

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWorkspaceTabDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceTabDoc)
	
	
		
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKSPACETABDOC_H__A90B50A0_583C_4B02_A502_5276AC639EF3__INCLUDED_)
