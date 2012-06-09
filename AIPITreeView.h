#if !defined(AFX_AIPITREEVIEW_H__325E897D_0B74_4F0E_BAB9_5F247FCA084B__INCLUDED_)
#define AFX_AIPITREEVIEW_H__325E897D_0B74_4F0E_BAB9_5F247FCA084B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AIPITreeView.h : header file
//
#include ".\TreeEditorCtrl\EditTreeCtrl.h"

#include "AIPI_DecisionTree/Aipi_DT_ID3.h"


#include "OXSkinnedView.h"

/////////////////////////////////////////////////////////////////////////////
// CAIPITreeView view
class CDataFile;

#define TREEBASEVIEW CView

class CAIPITreeView : public COXSkinnedView<TREEBASEVIEW>
{
public:
struct ItemViewport
{
	ItemViewport(HTREEITEM i) {this->item = i;}
	HTREEITEM item;
	int cx;
	int cy;
	int x;
	int y;
};

protected:
	CAIPITreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAIPITreeView)

// Attributes
public:
	void DrawNodeText(CDC *pDC, HTREEITEM item, CString text, int x, int y, int cx, int cy, COLORREF bkcolor,COLORREF txtcolor);
	void DrawLinkText(CDC *pDC, HTREEITEM item, CString text, int x, int y, int cx, int cy, COLORREF bkcolor,COLORREF txtcolor);
	void DrawLeafText(CDC *pDC, HTREEITEM item, CString text, int x, int y, int cx, int cy, COLORREF bkcolor,COLORREF txtcolor);
	int DrawItem(CDC *pDC, HTREEITEM, int x, int level = 0);
	void UpdateSkinMenus();
// Operations
public:
	CAIPITreeDoc* GetDocument();
	CEditTreeCtrl m_etc;
	
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAIPITreeView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAIPITreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAIPITreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewVerticalTree();
	afx_msg void OnViewHorizontalTree();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditFind();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnEditExpandAllTree();
	afx_msg void OnEditCollapseAllEntireTree();
	afx_msg void OnEditAddChild();
	afx_msg void OnEditAddSibling();
	afx_msg void OnEditRename();
	afx_msg void OnEditDeleteItem();
	afx_msg void OnEditDeleteAllItems();
	afx_msg void OnEditSortSubtreeAlphabetic();
	afx_msg void OnEditSortSubtreeNumeric();
	afx_msg void OnEditCountSubtree();
	afx_msg void OnEditCountEntireTree();
	afx_msg void OnEditCalculateLevel();
	afx_msg void OnSettingsFontFace();
	afx_msg void OnSettingsNodeClr();
	afx_msg void OnSettingsLinkTextClr();
	afx_msg void OnSettingsNodeTextClr();
	afx_msg void OnSettingsLeafTextClr();
	afx_msg void OnSettingsLinkClr();
	afx_msg void OnSettingsLeafClr();
	afx_msg void OnInductionBuildTree();
	afx_msg void OnSettingsSkinClassic();
	afx_msg void OnSettingsSkinOfficeXP();
	afx_msg void OnSettingsSkinOffice2003();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TreeEditorView.cpp
inline CAIPITreeDoc* CAIPITreeView::GetDocument()
   { return (CAIPITreeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIPITREEVIEW_H__325E897D_0B74_4F0E_BAB9_5F247FCA084B__INCLUDED_)
