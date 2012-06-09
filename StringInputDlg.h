#if !defined(AFX_STRINGINPUTDLG_H__E8EDC517_D1A4_402C_A81E_DA38AD392D20__INCLUDED_)
#define AFX_STRINGINPUTDLG_H__E8EDC517_D1A4_402C_A81E_DA38AD392D20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StringInputDlg.h : header file
//
#include <string>
/////////////////////////////////////////////////////////////////////////////
// CStringInputDlg dialog

class CStringInputDlg : public CDialog
{
// Construction
public:
	CStringInputDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStringInputDlg)
	enum { IDD = IDD_STRINGINPUT_DLG };
	CEdit	m_ctrlEdit;
	CButton	m_btnCancel;
	CButton	m_btnOK;
	CString	m_strPrompt;
	CString	m_strEdit;
	//}}AFX_DATA
	CString szBtnOK;
	CString szBtnCancel;
	CString szDlgCaption;

#ifdef _UNICODE	
	std::wstring m_strTitleName;
#else
	std::string m_strTitleName;
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStringInputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStringInputDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRINGINPUTDLG_H__E8EDC517_D1A4_402C_A81E_DA38AD392D20__INCLUDED_)
