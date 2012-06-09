#if !defined(AFX_CHARTLINEPROPDLG_H__E947ED6E_2CA7_45CB_B202_CA1C51A10043__INCLUDED_)
#define AFX_CHARTLINEPROPDLG_H__E947ED6E_2CA7_45CB_B202_CA1C51A10043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartLinePropDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChartLinePropDlg dialog

class CChartLinePropDlg : public CDialog
{
// Construction
public:
	CChartLinePropDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChartLinePropDlg)
	enum { IDD = IDD_CHART_LINEPROP_DLG };
	CComboBox	m_CtrlPenStyle;
	int		m_iLineWidth;
	int		m_iPenStyle;
	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartLinePropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChartLinePropDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTLINEPROPDLG_H__E947ED6E_2CA7_45CB_B202_CA1C51A10043__INCLUDED_)
