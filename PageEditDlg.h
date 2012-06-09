#if !defined(AFX_PAGEEDITDLG_H__AA3E0FA1_64BF_4070_B106_CCE4C64DD54A__INCLUDED_)
#define AFX_PAGEEDITDLG_H__AA3E0FA1_64BF_4070_B106_CCE4C64DD54A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageEditDlg.h : header file
//
#include "OXCoolCtrl.h"
#include "OXSeparator.h"


/////////////////////////////////////////////////////////////////////////////
// CPageEditDlg dialog
class CGridCtrl;


class CPageEditDlg : public CDialog
{
// Construction
public:
	CPageEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageEditDlg)
	enum { IDD = IDD_PAGEEDIT_DLG };

	COXSeparator	m_stcSeparator;
	COXCoolButton	m_stcMode;
	COXCoolButton	m_btnSelectAll;
	COXCoolButton	m_btnPaste;
	COXCoolButton	m_btnCut;
	COXCoolButton	m_btnCopy;
	COXCoolButton	m_radioRead;
	COXCoolButton	m_radioWrite;
	//}}AFX_DATA
	CGridCtrl *m_pGrid;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	//void SelectGrid();

protected:
	
	// Generated message map functions
	//{{AFX_MSG(CPageEditDlg)
	
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBtnCopy();
	afx_msg void OnBtnCut();
	afx_msg void OnBtnPaste();
	afx_msg void OnBtnSelectAll();
	afx_msg void OnRadioRead();
	afx_msg void OnRadioWrite();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg	void OnEditSelectAll();
	
#ifndef GRIDCONTROL_NO_CLIPBOARD	
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditCopyOrCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
#endif	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEEDITDLG_H__AA3E0FA1_64BF_4070_B106_CCE4C64DD54A__INCLUDED_)
