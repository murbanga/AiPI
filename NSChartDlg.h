#if !defined(AFX_NSCHARTDLG_H__A35378F9_A045_47C8_BFD6_A86103930855__INCLUDED_)
#define AFX_NSCHARTDLG_H__A35378F9_A045_47C8_BFD6_A86103930855__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NSChartDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNSChartDlg dialog

class CNSChartDlg : public CDialog
{
// Construction
public:
	CNSChartDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNSChartDlg)
	enum { IDD = IDD_NSCHART_DLG };
	CButton	m_btnCancel;
	CButton	m_btnOK;
	CString	m_sLabel;
	CString	m_sValue;
	CString	m_strTask;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	CString szBtnCaption;
	CString szBtnCancel;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNSChartDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNSChartDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NSCHARTDLG_H__A35378F9_A045_47C8_BFD6_A86103930855__INCLUDED_)
