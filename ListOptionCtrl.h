#if !defined(AFX_LISTOPTIONCTRL_H__C90C1CD5_2974_481B_AC29_298EEC6B0C4F__INCLUDED_)
#define AFX_LISTOPTIONCTRL_H__C90C1CD5_2974_481B_AC29_298EEC6B0C4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListOptionCtrl.h : header file
//
#include "OXSizeCtrlBar.h"
#include "OXListBoxEx.h"
#include "Aipi_ExpParserFileGlobal.h"
#include "Aipi_ExpParserFile.h"
#include "Aipi_ExpParserGUIGlobal.h"
#include "Aipi_ExpParserGUI.h"
/////////////////////////////////////////////////////////////////////////////
// CListOptionCtrl window

class CListOptionCtrl : public COXSizeControlBar
{
		DECLARE_DYNAMIC(CListOptionCtrl);
public:
	BOOL Create(CWnd * pParentWnd, const CString& sTitle = _T("ListOptionCtrl"),
		const UINT nID=IDC_LISTBOX_EX);
// Construction	
	CListOptionCtrl();
	

// Attributes
public:
	COXListBoxEx  m_listBoxEx;

	COLORREF m_clrListBoxBack;
	COLORREF m_clrItemBack;
	COLORREF m_clrItemText;
	CFont	m_fontItem;
	UINT	m_nIndent;
	CFont	g_fontHeader;
	
	
	BOOL	m_bHighlightOnlyText;
	CArray<CFont*,CFont*> m_arrFonts;
	

// Operations
public:
	void ResetListBox();
	void SetImageList();
	void InitListBox();
	void SetItemBkColor();
	void SetItemFont();
	void SetBkColor();
	void SetHighLightOnlyText(); 
	void SetIndent();
	void OnAddItem();
	void DeleteItem();
	int AddItem(LPCTSTR lpszText, int nImageIndex, int nIndent, COLORREF clrText, LPCTSTR lpszTooltipText, CFont* pFont);
	int AddItem(LPCTSTR lpszText);
	void AddItemDirect(LPCTSTR lpcItem, LPCTSTR plcTip );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListOptionCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListOptionCtrl();

	// Generated message map functions
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
protected:
	//{{AFX_MSG(CListOptionCtrl)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
		afx_msg void OnSelChangeListBoxEx();
		afx_msg void OnDblclkListBoxEx();
	
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTOPTIONCTRL_H__C90C1CD5_2974_481B_AC29_298EEC6B0C4F__INCLUDED_)
