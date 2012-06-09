#if !defined(AFX_PAGEOPTIONSDLG_H__43540AF6_BF43_47D4_ACA9_BCF31D322819__INCLUDED_)
#define AFX_PAGEOPTIONSDLG_H__43540AF6_BF43_47D4_ACA9_BCF31D322819__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageOptionsDlg.h : header file
//
#include "OXCoolCtrl.h"
#include "OXSeparator.h"
/////////////////////////////////////////////////////////////////////////////
// CPageOptionsDlg dialog
class CGridCtrl;

class CPageOptionsDlg : public CDialog
{
// Construction
public:
	CPageOptionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageOptionsDlg)
	enum { IDD = IDD_PAGEOPTIONS_DLG };
	COXSeparator	m_stcSeparator;
	COXSeparator	m_stcFocus;
	COXCoolButton	m_chkToolTips;
	COXCoolButton	m_chkSort;
	COXCoolButton	m_chkCellSelect;
	
	//}}AFX_DATA
	CGridCtrl *m_pGrid;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageOptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	//void SelectGrid();

protected:

	// Generated message map functions
	//{{AFX_MSG(CPageOptionsDlg)
	afx_msg void OnChkToolTips();
	afx_msg void OnChkSort();
	afx_msg void OnCheckCellSelect();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEOPTIONSDLG_H__43540AF6_BF43_47D4_ACA9_BCF31D322819__INCLUDED_)
