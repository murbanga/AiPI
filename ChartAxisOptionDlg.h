#if !defined(AFX_CHARTAXISOPTIONDLG_H__A112EEAF_52B1_44B9_8AAF_42E7D2497471__INCLUDED_)
#define AFX_CHARTAXISOPTIONDLG_H__A112EEAF_52B1_44B9_8AAF_42E7D2497471__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartAxisOptionDlg.h : header file
//
#include <string>
#include "ChartBarCtrl.h"
#include ".\ChartCtrl\ChartAxisLabel.h"
/////////////////////////////////////////////////////////////////////////////
// CChartAxisOptionDlg dialog

class CChartAxisOptionDlg : public CDialog
{
// Construction
public:
	CChartAxisOptionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChartAxisOptionDlg)
	enum { IDD = IDD_CHART_AXISOPTIONS_DLG };
	CEdit	m_CEditAxisMinVal;
	CEdit	m_CEditAxisMaxVal;
	int		m_iLeftAxis;
	CString	m_sAxisMaxVal;
	CString	m_sAxisMinVal;
	CString	m_sAxisLabel;
	BOOL	m_bAxisGrid;
	BOOL	m_bAxisAutomatic;
	BOOL	m_bAxisVisible;
	BOOL	m_bAxisInverted;
	BOOL	m_bAxisLogarithmic;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CString szLeftAxisLabel, szBottomAxisLabel, szRightAxisLabel, szTopAxisLabel;
	CString szLeftAxisMax, szBottomAxisMax, szRightAxisMax, szTopAxisMax;
	CString szLeftAxisMin, szBottomAxisMin, szRightAxisMin, szTopAxisMin;

	CChartBarCtrl ctrlBar;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartAxisOptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChartAxisOptionDlg)
		virtual BOOL OnInitDialog();
	afx_msg void OnChangeAxisMin();
	afx_msg void OnChangeAxisMax();
	afx_msg void OnLeftAxisRadio();
	afx_msg void OnBottomAxisRadio();
	afx_msg void OnRightAxisRadio();
	afx_msg void OnTopAxisRadio();
	afx_msg void OnAxisLogarithmicCheck();
	afx_msg void OnAxisAutomaticCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CChartAxis* GetSelectedAxis();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTAXISOPTIONDLG_H__A112EEAF_52B1_44B9_8AAF_42E7D2497471__INCLUDED_)
