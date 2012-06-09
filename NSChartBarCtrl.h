#if !defined(AFX_NSCHARTBARCTRL_H__48DBEFD1_DBFA_486D_B7A4_9411ECE90E07__INCLUDED_)
#define AFX_NSCHARTBARCTRL_H__48DBEFD1_DBFA_486D_B7A4_9411ECE90E07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NSChartBarCtrl.h : header file
//
#include ".\NSChart\NSChartCtrl.h"
#include "OXSizeCtrlBar.h"
/////////////////////////////////////////////////////////////////////////////
// CNSChartBarCtrl window

class CNSChartBarCtrl : public COXSizeControlBar
{

	DECLARE_DYNAMIC(CNSChartBarCtrl);	

public:
	BOOL Create(CWnd * pParentWnd, const CString& sTitle = _T("NSChartBarCtrl"),
		const UINT nID=IDC_NSCHARTBARCTRL);
// Construction
	CNSChartBarCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNSChartBarCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetChartTitle(CString strTitle);
	void OnPieStyle();
	void OnBarStyle();
	void OnGrayBackground();
	void OnColorBackground();
	void OnLineBackground();
	void OnChartSelectedItem(NMHDR* pNMHDR, LRESULT* pResult);
	void OnAdd();
	void OnDel();
	void OnModify();
	
protected:
	CNSChartCtrl	m_chart;
	int				m_iItem;
	double			m_dValue;
	CString			m_sLabel;
	CString			m_strTitle; 
	CFont			m_font;

protected:
	void OnUpdateModify(CCmdUI* pCmdUI);
	void OnUpdateAdd(CCmdUI* pCmdUI);

public:
	virtual ~CNSChartBarCtrl();

	// Generated message map functions
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
protected:
	//{{AFX_MSG(CNSChartBarCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NSCHARTBARCTRL_H__48DBEFD1_DBFA_486D_B7A4_9411ECE90E07__INCLUDED_)
