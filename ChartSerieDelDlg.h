#if !defined(AFX_CHARTSERIEDELDLG_H__8BDE5A67_D7B8_4F56_91BD_10EE33F724CD__INCLUDED_)
#define AFX_CHARTSERIEDELDLG_H__8BDE5A67_D7B8_4F56_91BD_10EE33F724CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartSerieDelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChartSerieDelDlg dialog

class CChartSerieDelDlg : public CDialog
{
// Construction
public:
	CChartSerieDelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChartSerieDelDlg)
	enum { IDD = IDD_CHART_SERIESDEL_DLG };
	CListBox	m_SeriesList;
		
	//}}AFX_DATA

	CStringArray dlgSerieName;
	int dlgIndex;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartSerieDelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChartSerieDelDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTSERIEDELDLG_H__8BDE5A67_D7B8_4F56_91BD_10EE33F724CD__INCLUDED_)
