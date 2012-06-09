#if !defined(AFX_FINDINFILESEXTDLG_H__18C49CB7_A918_4FED_A029_177A04DC9B96__INCLUDED_)
#define AFX_FINDINFILESEXTDLG_H__18C49CB7_A918_4FED_A029_177A04DC9B96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindInFilesExtDlg.h : header file
//
#include "OXFolderPickerDlg.h"
#include "OXEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CFindInFilesExtDlg dialog

class CFindInFilesExtDlg : public CDialog
{
// Construction
public:
	CFindInFilesExtDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindInFilesExtDlg)
	enum { IDD = IDD_FINDINFILES_EXT_DLG };
	CString				m_sFindText;
	BOOL				m_bSize;
	BOOL				m_bSubFolders;
	CString				m_sFileMask;
	COXNumericEdit		m_editMaxSize;
	COXNumericEdit		m_editMinSize;
	CString				m_sBaseFolder;
	//}}AFX_DATA
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindInFilesExtDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	 
	// Generated message map functions
	//{{AFX_MSG(CFindInFilesExtDlg)
		afx_msg void OnCheckSize();
		afx_msg void OnBrowse();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDINFILESEXTDLG_H__18C49CB7_A918_4FED_A029_177A04DC9B96__INCLUDED_)
