#if !defined(AFX_CHARTPOINTPROPDLG_H__FAF80241_8AF1_4494_8D55_F0752CC7E9CD__INCLUDED_)
#define AFX_CHARTPOINTPROPDLG_H__FAF80241_8AF1_4494_8D55_F0752CC7E9CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartPointPropDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChartPointPropDlg dialog

class CChartPointPropDlg : public CDialog
{
// Construction
public:
	CChartPointPropDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChartPointPropDlg)
	enum { IDD = IDD_CHART_POINTPROP_DLG };
	CComboBox	m_CtrlPointsType;
	int		m_iPointsHeight;
	int		m_iPointsWidth;
	int		m_iPointsType;
		
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartPointPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChartPointPropDlg)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTPOINTPROPDLG_H__FAF80241_8AF1_4494_8D55_F0752CC7E9CD__INCLUDED_)
