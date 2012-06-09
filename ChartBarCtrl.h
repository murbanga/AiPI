#if !defined(AFX_CHARTBARCTRL_H__04BA1840_D445_4E38_BF94_6BBC9BE844A0__INCLUDED_)
#define AFX_CHARTBARCTRL_H__04BA1840_D445_4E38_BF94_6BBC9BE844A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartBarCtrl.h : header file
//

#include ".\ChartCtrl\ChartCtrl.h"
//#include "ChartCtrl.h"

#include "OXSizeCtrlBar.h"
/////////////////////////////////////////////////////////////////////////////
// CChartBarCtrl window

class CChartBarCtrl : public COXSizeControlBar
{
	DECLARE_DYNAMIC(CChartBarCtrl);
	
public:
	BOOL Create(CWnd * pParentWnd, const CString& sTitle = _T("ChartBarCtrl"),
	const UINT nID=IDC_CHARTBARCTRL);

// Construction
	CChartBarCtrl();

// Attributes
	CStringArray saSerieName;
	CString szLeftLabel, szBottomLabel, szRightLabel, szTopLabel;
	CString szLeftMax, szBottomMax, szRightMax, szTopMax;
	CString szLeftMin, szBottomMin, szRightMin, szTopMin;
	int index;

	

// Operations
public:
	void OnAddSeries();	
	void OnDeleteSeries();
	void OnLegendVisible();
	void OnLegendNotVisible();
	void OnPanChecked() ;
	void OnPanUnChecked();
	void OnZoomChecked();
	void OnZoomUnChecked();
	void OnChangeTitle(); 
	void OnAxisOption();
	LONG OnChangeBckCol();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartBarCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	
	void SetLeftAxisMinMax(double min, double max);
	void SetBottomAxisMinMax(double min, double max);
	void SetRightAxisMinMax(double min, double max);
	void SetTopAxisMinMax(double min, double max);
	
	void SetLeftAxisAutomatic(int flag, double min, double max);
	void SetBottomAxisAutomatic(int flag, double min, double max);
	void SetRightAxisAutomatic(int flag, double min, double max);
	void SetTopAxisAutomatic(int flag, double min, double max);
	
	void SetLeftAxisLogarithmic(int flag, double min, double max);
	void SetBottomAxisLogarithmic(int flag, double min, double max);
	void SetRightAxisLogarithmic(int flag, double min, double max);
	void SetTopAxisLogarithmic(int flag, double min, double max);
	
	void SetLeftAxisVisible(int flag);
	void SetBottomAxisVisible(int flag);
	void SetRightAxisVisible(int flag);
	void SetTopAxisVisible(int flag);
	
	void SetLeftAxisInverted(int flag);
	void SetBottomAxisInverted(int flag);
	void SetRightAxisInverted(int flag);
	void SetTopAxisInverted(int flag);
	
	void SetLeftAxisGrid(int flag);
	void SetBottomAxisGrid(int flag);
	void SetRightAxisGrid(int flag);
	void SetTopAxisGrid(int flag);
	
	
	void SetLeftAxisLabel(CString label);
	void SetBottomAxisLabel(CString label);
	void SetRightAxisLabel(CString label);
	void SetTopAxisLabel(CString label);
	
	
	virtual ~CChartBarCtrl();

public:
	CChartCtrl		m_chartCtrl;
	

	// Generated message map functions
		virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
protected:
	//{{AFX_MSG(CChartBarCtrl)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTBARCTRL_H__04BA1840_D445_4E38_BF94_6BBC9BE844A0__INCLUDED_)
