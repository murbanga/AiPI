#if !defined(AFX_PAGEINSERTDLG_H__AC8C180A_A3E4_406A_B59B_02C5EC7D0223__INCLUDED_)
#define AFX_PAGEINSERTDLG_H__AC8C180A_A3E4_406A_B59B_02C5EC7D0223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageInsertDlg.h : header file
//
#include "OXCoolCtrl.h"
#include "OXSeparator.h"
#include	"OXSpinCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CPageInsertDlg dialog
class CGridCtrl;

class CPageInsertDlg : public CDialog
{
// Construction
public:
	CPageInsertDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageInsertDlg)
	enum { IDD = IDD_PAGEINSERT_DLG };
	
	COXSeparator	m_stcNoCells;
	COXCoolButton	m_btnDeleteRow;
	COXCoolButton	m_btnInsertRow;
	CEdit	m_editRows;
	CEdit	m_editFixedRows;
	CEdit	m_editFixedColumns;
	CEdit	m_editColumns;
	COXSpinCtrl	m_spnRows;
	COXSpinCtrl	m_spnFixedRows;
	COXSpinCtrl	m_spnFixedColumns;
	COXSpinCtrl	m_spnColumns;

	int		m_nMaxCols;
	int		m_nMaxFixCols;
	int		m_nMaxFixRows;
	int		m_nMaxRows;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	CGridCtrl *m_pGrid;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageInsertDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


	

// Implementation
public:
	void UpdateEditControls();
private:
	//void SelectGrid();

protected:

	// Generated message map functions
	//{{AFX_MSG(CPageInsertDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdateEditNRows();
	afx_msg void OnUpdateEditNCols();
	afx_msg void OnUpdateEditNFixRows();
	afx_msg void OnUpdateEditNFixCols();
	afx_msg void OnBtnDeleteRow();
	afx_msg void OnBtnInsertRow();
	afx_msg void OnBtnInsertColumn();
	afx_msg void OnBtnDeleteColumn();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEINSERTDLG_H__AC8C180A_A3E4_406A_B59B_02C5EC7D0223__INCLUDED_)
