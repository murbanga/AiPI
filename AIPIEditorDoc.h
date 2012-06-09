#if !defined(AFX_AIPIEDITORDOC_H__E790E564_1C72_468F_BE50_A888B17B464A__INCLUDED_)
#define AFX_AIPIEDITORDOC_H__E790E564_1C72_468F_BE50_A888B17B464A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AIPIEditorDoc.h : header file
//
#include ".\ScintillaCtrl\ScintillaDocView.h"
#include "WorkspaceTabDoc.h"
#include "MainFrm.h"

/////////////////////////////////////////////////////////////////////////////
// CAIPIEditorDoc document

class CAIPIEditorDoc : public CScintillaDoc
{
protected:
	CAIPIEditorDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAIPIEditorDoc)

// Attributes
public:
		void AddToRecentFileList(LPCTSTR lpszPathName);
// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAIPIEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAIPIEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAIPIEditorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIPIEDITORDOC_H__E790E564_1C72_468F_BE50_A888B17B464A__INCLUDED_)
