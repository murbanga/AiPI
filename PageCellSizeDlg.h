#if !defined(AFX_PAGECELLSIZEDLG_H__10AB59F4_2EDE_44E2_A087_6114782CDC64__INCLUDED_)
#define AFX_PAGECELLSIZEDLG_H__10AB59F4_2EDE_44E2_A087_6114782CDC64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageCellSizeDlg.h : header file
//
#include "OXCoolCtrl.h"
#include "OXSeparator.h"
/////////////////////////////////////////////////////////////////////////////
// CPageCellSizeDlg dialog
class CGridCtrl;

class CPageCellSizeDlg : public CDialog
{
// Construction
public:
	CPageCellSizeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageCellSizeDlg)
	enum { IDD = IDD_PAGECELLSIZE_DLG };
	COXCoolButton	m_chkFitGrid;
	COXCoolButton	m_chkColumnResize;
	COXCoolButton	m_chkRowResize;
	COXSeparator	m_stcSeparator;
	COXCoolButton	m_btnExpandCol;
	COXCoolButton	m_btnAutosize;
	COXCoolButton	m_btnAutofill;
	
	//}}AFX_DATA
	CGridCtrl *m_pGrid;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageCellSizeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
//void SelectGrid();

protected:

	// Generated message map functions
	//{{AFX_MSG(CPageCellSizeDlg)
	afx_msg void OnBtnAutoFillGrid();
	afx_msg void OnBtnAutoSize();
	afx_msg void OnBtnExpandColumn();
	afx_msg void OnChkRowResize();
	afx_msg void OnChkColumnResize();
	afx_msg void OnChkFitGrid();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECELLSIZEDLG_H__10AB59F4_2EDE_44E2_A087_6114782CDC64__INCLUDED_)
