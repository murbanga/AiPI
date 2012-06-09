#if !defined(AFX_PAGEFORMATDLG_H__40737595_1E81_44A6_90BA_8161E715047A__INCLUDED_)
#define AFX_PAGEFORMATDLG_H__40737595_1E81_44A6_90BA_8161E715047A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageFormatDlg.h : header file
//
#include "OXCoolCtrl.h"
#include "OXSeparator.h"
//#include "InductionTabView.h"
/////////////////////////////////////////////////////////////////////////////
// CPageFormatDlg dialog
class CGridCtrl;

class CPageFormatDlg : public CDialog
{
// Construction
public:
	CPageFormatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageFormatDlg)
	enum { IDD = IDD_PAGEFORMAT_DLG };
	COXSeparator	m_stcGridLines;
	COXSeparator	m_stcFont;
	COXCoolButton	m_chkVertical;
	COXCoolButton	m_chkHorizontal;
	COXCoolButton	m_btnCellFont;
	COXCoolButton	m_radioItalic;
	COXCoolButton	m_radioBold;
	COXCoolButton	m_radioNormal;
	COXCoolButton	m_radioVerticalHeader;
	COXCoolButton	m_btnPrint;
	COXSeparator	m_stcSeparator01;
	
	
	//}}AFX_DATA
	CGridCtrl *m_pGrid;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageFormatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	//void SelectGrid();

public:
	void OnGridLines();

	
	
	// Generated message map functions
	//{{AFX_MSG(CPageFormatDlg)
	afx_msg void OnChkHorizontal();
	afx_msg void OnChkVertical();
	afx_msg void OnBtnFont();
	afx_msg void OnRadioFixedItalic();
	afx_msg void OnRadioFixedBold();
	afx_msg void OnRadioFixedVertical();
	afx_msg void OnRadioFixedNormal();
	afx_msg void OnBtnPrint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEFORMATDLG_H__40737595_1E81_44A6_90BA_8161E715047A__INCLUDED_)
