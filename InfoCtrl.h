#if !defined(AFX_INFOCTRL_H__52FA5733_7D5E_4752_B2CF_BA3BC8FBE5DD__INCLUDED_)
#define AFX_INFOCTRL_H__52FA5733_7D5E_4752_B2CF_BA3BC8FBE5DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoCtrl.h : header file
//
#include "OXSizeCtrlBar.h"
#include "OXEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CInfoCtrl window

class CInfoCtrl : public COXSizeControlBar
{
	DECLARE_DYNAMIC(CInfoCtrl);
public:
	BOOL Create(CWnd * pParentWnd, const CString& sTitle = _T("InfoCtrl"),
		const UINT nID=IDC_STATIC_EX);
// Construction
	CInfoCtrl();

// Attributes
public:
	COXEdit m_staticCtrl;
	
	COLORREF m_clrBack;
	COLORREF m_clrText;
	CFont m_font;

// Operations
public:
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInfoCtrl();

	// Generated message map functions
protected:
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
protected:
	//{{AFX_MSG(CInfoCtrl)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOCTRL_H__52FA5733_7D5E_4752_B2CF_BA3BC8FBE5DD__INCLUDED_)
