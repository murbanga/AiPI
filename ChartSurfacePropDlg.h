#if !defined(AFX_CHARTSURFACEPROPDLG_H__07D83031_2624_4117_B33B_290C48D229E8__INCLUDED_)
#define AFX_CHARTSURFACEPROPDLG_H__07D83031_2624_4117_B33B_290C48D229E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartSurfacePropDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChartSurfacePropDlg dialog

class CChartSurfacePropDlg : public CDialog
{
// Construction
public:
	CChartSurfacePropDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChartSurfacePropDlg)
	enum { IDD = IDD_CHART_SURFACEPROP_DLG };
	CComboBox	m_CtrlFillStyle;
	int		m_iHorizSurf;
	int		m_FillStyle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartSurfacePropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChartSurfacePropDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTSURFACEPROPDLG_H__07D83031_2624_4117_B33B_290C48D229E8__INCLUDED_)
