#if !defined(AFX_ZOOMVIEWDLG_H__9C66CBCE_47CC_40DC_936A_48D98AC0D3D2__INCLUDED_)
#define AFX_ZOOMVIEWDLG_H__9C66CBCE_47CC_40DC_936A_48D98AC0D3D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomViewDlg.h : header file
//
#include   "OXEdit.h"
#include	"OXSeparator.h"
#include	"OXSpinCtrl.h"
#include	"OXCoolCtrl.h"	 
/////////////////////////////////////////////////////////////////////////////
// CZoomViewDlg dialog

class CZoomViewDlg : public CDialog
{
// Construction
public:
	CZoomViewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZoomViewDlg)
	enum { IDD = IDD_ZOOMVIEW_DLG };
	COXSeparator	m_stcExpansion;
	COXSpinCtrl	m_spinCustom;
	COXNumericEdit	m_editCustom;
	COXCoolButton m_radio200;
	COXCoolButton m_radio100;
	COXCoolButton m_radio75;
	COXCoolButton m_radio50;
	COXCoolButton m_radio25;
	COXCoolButton m_radioCustom;
	//}}AFX_DATA
	int m_iValue;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZoomViewDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinCustom(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadio200();
	afx_msg void OnRadio100();
	afx_msg void OnRadio75();
	afx_msg void OnRadio50();
	afx_msg void OnRadio25();
	afx_msg void OnRadioCustom();
	afx_msg void OnChangeEditCustom();
	afx_msg void OnSetfocusEditCustom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMVIEWDLG_H__9C66CBCE_47CC_40DC_936A_48D98AC0D3D2__INCLUDED_)
