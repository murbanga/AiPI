#if !defined(AFX_FINDINFILESDLG_H__3AA875DD_B20E_457E_BA8B_673D14E151F8__INCLUDED_)
#define AFX_FINDINFILESDLG_H__3AA875DD_B20E_457E_BA8B_673D14E151F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindInFilesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindInFilesDlg dialog

class CFindInFilesDlg : public CDialog
{
// Construction
public:
	CFindInFilesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindInFilesDlg)
	enum { IDD = IDD_FINDINFILES_DLG };
	CString	m_strFind;
	BOOL	m_chkMatchCase;
	BOOL	m_chkRegExp;
	BOOL	m_chkWholeWord;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindInFilesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindInFilesDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDINFILESDLG_H__3AA875DD_B20E_457E_BA8B_673D14E151F8__INCLUDED_)
