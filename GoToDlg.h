#if !defined(AFX_GOTODLG_H__3207C616_F967_4AF8_96F5_BB6146F4B3B0__INCLUDED_)
#define AFX_GOTODLG_H__3207C616_F967_4AF8_96F5_BB6146F4B3B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GoToDlg.h : header file
//
#include "OXCoolCtrl.h"
#include "OXSeparator.h"
#include "OXEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CGoToDlg dialog

class CGoToDlg : public CDialog
{
// Construction
public:
	CGoToDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGoToDlg)
	enum { IDD = IDD_GOTO_DLG };
	CStatic	m_labelGoTo;
	COXNumericEdit	m_editGoTo;
	COXCoolButton	m_radioChar;
	COXCoolButton	m_radioLine;
	COXCoolButton	m_btnCancel;
	COXCoolButton	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGoToDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void	GoToChar();
	void	GoToLine();

	// Generated message map functions
	//{{AFX_MSG(CGoToDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioChar();
	afx_msg void OnRadioLine();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GOTODLG_H__3207C616_F967_4AF8_96F5_BB6146F4B3B0__INCLUDED_)
