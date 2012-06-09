#if !defined(AFX_STATICMETERCTRL_H__AEAAE4F5_2834_41B4_A9CF_89D85C53B86F__INCLUDED_)
#define AFX_STATICMETERCTRL_H__AEAAE4F5_2834_41B4_A9CF_89D85C53B86F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticMeterCtrl.h : header file
//
#include ".\3DMeterCtrl\3DMeterCtrl.h"
#include "OXSizeCtrlBar.h"
/////////////////////////////////////////////////////////////////////////////
// CStaticMeterCtrl window

class CStaticMeterCtrl : public COXSizeControlBar
{
	DECLARE_DYNAMIC(CStaticMeterCtrl);

public:
	BOOL Create(CWnd * pParentWnd, const CString& sTitle = _T("3DMeterCtrl"),
		const UINT nID=IDC_3DMETERCTRL);
	// Construction
	CStaticMeterCtrl();

// Attributes
public:

// Operations
public:
	//void OnTimer(UINT nIDEvent);
	
	void SetNeedleValue(double dValue);
	void SetNeedleDecimalPlaces(int nPlaces);
	void SetNeedleRange(double dMin, double dMax);
	void SetNeedleUnits(CString szUnit);
	void SetRangeDecimalPlaces(int nPlaces);
	void OnMeterDecimals();
	void OnMeterMax();
	void OnMeterMin();
	void OnMeterScaleDecimals();
	void OnMeterUnits();
	void OnMeterNeedleColor();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticMeterCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CStaticMeterCtrl();

protected:
	C3DMeterCtrl	m_3DMeterCtrl;
	CFont			m_font;
	int				m_nTimer ;

	// Generated message map functions
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
protected:
	//{{AFX_MSG(CStaticMeterCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICMETERCTRL_H__AEAAE4F5_2834_41B4_A9CF_89D85C53B86F__INCLUDED_)
