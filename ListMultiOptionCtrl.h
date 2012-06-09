#if !defined(AFX_LISTMULTIOPTIONCTRL_H__06F46FA1_4ABC_4E9C_9BA5_A0296697D2E1__INCLUDED_)
#define AFX_LISTMULTIOPTIONCTRL_H__06F46FA1_4ABC_4E9C_9BA5_A0296697D2E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListMultiOptionCtrl.h : header file
//
#include "OXSizeCtrlBar.h"
#include "OxGridList.h"
#include "OXGridEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CListMultiOptionCtrl window

class CListMultiOptionCtrl : public COXSizeControlBar
{

	DECLARE_DYNAMIC(CListMultiOptionCtrl);	
	
public:
	BOOL Create(CWnd * pParentWnd, const CString& sTitle = _T("ListMultiOptionCtrl"),
		const UINT nID=IDC_LISTCTRL_EX);
// Construction
	CListMultiOptionCtrl();

// Attributes
public:
	COXGridList	m_gridCtrl;

	//CSpinButtonCtrl	m_wndImageColumnSpin;
	//CSpinButtonCtrl	m_wndNumRowsSpin;
	
	BOOL		m_bGridLines;
	BOOL		m_bNormalGridLines;
	BOOL		m_bEditCheck;
	BOOL		m_bMulti;
	BOOL		m_bSort;
	BOOL		m_bCheckable;
	BOOL		m_bNormalCheckBox;
	BOOL		m_bAutoEdit;
	BOOL		m_bShowSel;
	BOOL		m_bHorizontal;
	BOOL		m_bVertical;
	BOOL		m_bResize;
	int			m_nRegion;
	int			m_iNumberOfRows;
	int			m_iImageColumn;

protected:
	BOOL m_bInitialized;
	CImageList m_ImageSmall;
	COXGridEdit m_gridEdit;
	CImageList m_stateImages;
// Operations
public:
	void InitListCtrl();
	
	void SetFont();
	void ResetFont();
	void SetColor();
	void SetTextColor();
	void SetTextBkColor();
	void SetBkColor();
	void SetGridLinesColor();
	void Clear();
	void DeleteItem();
	void InsertItems();
	void Sortable();
	void SetMulCheck();
	void SetEditable();
	void SetGridLines();
	void SetNormalGridLines();
	void SetCheckable();
	void SetNormalCheckBox();
	void SetAutoEdit();
	void ShowSelection();
	void ChangeImageColumn();
	void SetHorizontalGrid();
	void SetVerticalGrid();
	void SetGridColResize();
	void SetRadioCenter();
	void SetRadioLeft();
	void SetRadioRight();
	

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListMultiOptionCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListMultiOptionCtrl();

	// Generated message map functions
		virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
protected:
	//{{AFX_MSG(CListMultiOptionCtrl)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
		afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnTraceNotification(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void SingleCheck(NMHDR* pNMHDR, LRESULT* pResult); 

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTMULTIOPTIONCTRL_H__06F46FA1_4ABC_4E9C_9BA5_A0296697D2E1__INCLUDED_)
