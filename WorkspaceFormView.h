#if !defined(AFX_WORKSPACEFORMVIEW_H__B39058EC_B8BD_4783_9615_5C03AD2B32B8__INCLUDED_)
#define AFX_WORKSPACEFORMVIEW_H__B39058EC_B8BD_4783_9615_5C03AD2B32B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkspaceFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WorkspaceFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class WorkspaceFormView : public CFormView
{
protected:
	WorkspaceFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(WorkspaceFormView)

// Form Data
public:
	//{{AFX_DATA(WorkspaceFormView)
	enum { IDD = IDD_WORKSPACE_FORMVIEW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WorkspaceFormView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~WorkspaceFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(WorkspaceFormView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKSPACEFORMVIEW_H__B39058EC_B8BD_4783_9615_5C03AD2B32B8__INCLUDED_)
