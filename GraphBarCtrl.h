#if !defined(AFX_GRAPHBARCTRL_H__D3C97EE5_DF2E_4A63_BE3D_E1712CD516F9__INCLUDED_)
#define AFX_GRAPHBARCTRL_H__D3C97EE5_DF2E_4A63_BE3D_E1712CD516F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphBarCtrl.h : header file
//
#include "OXSizeCtrlBar.h"

#include ".\graphbar\graphwnd.h"
#include ".\graphbar\graph_props.h"
#include ".\graphbar\graphcombobox.h"
#include ".\graphbar\graph_props.h"
#include ".\graphbar\gen_prop_dlgs.h"

/////////////////////////////////////////////////////////////////////////////
// CGraphBarCtrl window

class CGraphBarCtrl : public COXSizeControlBar
{

	DECLARE_DYNAMIC(CGraphBarCtrl);
	
public:
	BOOL Create(CWnd * pParentWnd, const CString& sTitle = _T("GraphBarCtrl"),
		const UINT nID=IDC_GRAPHBARCTRL);
// Construction
	CGraphBarCtrl();

// Attributes
public:
	CGraphWnd m_graphCtrl;
	long lGraph_Count;
	long lDyn_Graph_ID;
	long lCurrent_X;

// Operations
public:
	long AddNewDynamicGraph(BOOL bDrawPoints, double x_range);
	void ToggleGraphFlag(unsigned long graph_flag, BOOL bUpdate);
	void AddNewGraph();
	void RemoveGraph(int index);
	void GraphAutoScale();
	void SetToolTipCoordenates();
	void SetSquarePoints();
	void SetGraphAxis();
	void SetGraphScatter();
	void OnGraphAxisProperties();
	void OnGraphCoordinates();
	void OnGraphSetTitle();
	void OnDynamicGraph();
	void QuitDynamicGraph();
	void OnTimer(UINT nIDEvent);
	void OnPrint(CDC* pDC, CPrintInfo* pInfo);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphBarCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphBarCtrl();

protected:
	// Generated message map functions
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
protected:
	//{{AFX_MSG(CGraphBarCtrl)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHBARCTRL_H__D3C97EE5_DF2E_4A63_BE3D_E1712CD516F9__INCLUDED_)
