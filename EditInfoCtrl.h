#if !defined(AFX_EDITINFOCTRL_H__A7666123_9F0A_4222_921E_FD5C1CF995A8__INCLUDED_)
#define AFX_EDITINFOCTRL_H__A7666123_9F0A_4222_921E_FD5C1CF995A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditInfoCtrl.h : header file
//
#include "OXSizeCtrlBar.h"
#include "OXEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CEditInfoCtrl window

class CEditInfoCtrl : public COXSizeControlBar
{

	DECLARE_DYNAMIC(CEditInfoCtrl);
	
public:
	BOOL Create(CWnd * pParentWnd, const CString& sTitle = _T("EditInfoCtrl"),
		const UINT nID=IDC_EDIT_EX);
// Construction
	CEditInfoCtrl();

// Attributes
public:
	COXEdit m_editCtrl;
	
	COLORREF m_clrBack;
	COLORREF m_clrText;
	CFont m_font;

// Operations
public:
	void SetBackColor();
	void SetFontColor();
	void SetFontStyle();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditInfoCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditInfoCtrl();

		// Generated message map functions
protected:
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
	//{{AFX_MSG(CEditInfoCtrl)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITINFOCTRL_H__A7666123_9F0A_4222_921E_FD5C1CF995A8__INCLUDED_)
