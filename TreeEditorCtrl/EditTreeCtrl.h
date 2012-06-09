#if !defined(AFX_EDITTREECTRL_H__73D1D740_1211_4B37_AB0B_93D46A5842EC__INCLUDED_)
#define AFX_EDITTREECTRL_H__73D1D740_1211_4B37_AB0B_93D46A5842EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditTreeCtrl.h : header file
//
#include "Resource.h"
#include "TreeType.h"
#include ".\..\AIPITreeDoc.h"




// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)
#include <vector>
#include <algorithm>
#include <functional>
#include <map>

//using namespace std ;
#pragma warning(disable:4786)

// Fenster CVerticalTree 
#define BUTTON_SIZE 9
#define MAXTEXTLEN  120


typedef struct 
{
	int iLevel;
	CString str;
} TREE_RECORD;

typedef struct 
{
	HTREEITEM hti;
	HTREEITEM *pChildrenOfParent;
	HTREEITEM htiLoadedItem;
	int iSizeChildrenOfParent;
} LOAD_ABOVE;

int SearchLoadAboveItem(LOAD_ABOVE &la, HTREEITEM hti);
int CALLBACK CompareForLoadAbove(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

typedef std::vector<TREE_RECORD> TREE_RECORD_VECTOR;
typedef std::vector<CString> CSTRING_VECTOR;

/////////////////////////////////////////////////////////////////////////////
// CEditTreeCtrl window

// Redifine TVI_ROOT and TVI_FIRST as constants for clarity (when we use these
// constants with a different meaning).
static const HTREEITEM HTI_ENTIRE_TREE = TVI_ROOT;
static const HTREEITEM HTI_SUBTREE = TVI_FIRST;

static const SCROLL_SPEED = 100;
static const MAX_ASCII_RECORD = 256;
static const MAX_LEVELS = 40;

enum SORT_TYPE
{
    ST_ALPHABETIC,
    ST_NUMERIC,
};

enum OUTSIDE_PARAM
{
    OP_NONE,
    OP_ENTIRE_TREE,
    OP_SUBTREE,
};

enum
{
	CUR_COPY_ROOT,
	CUR_COPY_SON,
	CUR_MOVE_ABOVE,
	CUR_COPY_ABOVE,
	CUR_MOVE_ROOT,
	CUR_MOVE_SON,
	CUR_NODROP,
	CUR_COUNT,
};

class CEditTreeCtrl : public CTreeCtrl 
{

struct ItemViewport
{
	ItemViewport(HTREEITEM i) {this->item = i;}
	HTREEITEM item;
	int cx;
	int cy;
	int x;
	int y;
};
typedef std::map<HTREEITEM, ItemViewport*> HTREE2VPMAP;	
	
// Construction
public:
	CEditTreeCtrl();

    typedef void (CEditTreeCtrl::*PARSING_FUNCTION)(HTREEITEM hti, void *pvParam);

// Attributes
public:
	CAIPITreeDoc *m_pted;

    SORT_TYPE m_SortType;
	UINT m_uLimitText;
	BOOL m_bDragging;
	WORD m_wOldKey;
	HTREEITEM m_hitemDrag;
	HTREEITEM m_hitemDrop;
	HTREEITEM m_hItemFound;
	HCURSOR m_hCursor;
	HCURSOR m_ahCursor[CUR_COUNT];
	CTreeType m_ttTransfer;
	CImageList *m_pimagelist;
	BOOL m_bTimerABOVE_Active;
	BOOL m_bTimerBELOW_Active;
	UINT m_uOldFlags;

// Operations
public:

	void InsertLoadItemBeforeHti(LOAD_ABOVE &la);
	void SortSubtree();
	void OnLoadAbove(HTREEITEM hti);
	int  GetLevelTree(HTREEITEM hti);
	void GetFromClipboard(CString &fromClipboard);
	void Add2Clipboard(CString *pstrData, int iSize);
	void SaveCsvTabTreeToClipboard(CTreeType &tt);
	BOOL PasteEntireTreeFromCliboard(CTreeType &tt);
	void pfCollapseAndSort(HTREEITEM hti, void *);
	void CEditTreeCtrl::GenerateFirstDirectoryRecords(const TCHAR *pszFirstRecord,
	CSTRING_VECTOR &cvFirstDirRecords);
	BOOL LoadCsvTreeFromMemory(TREE_RECORD_VECTOR &vtr, CTreeType &tt, int iMaxLevel, FILE_FORMAT ff);
    void FindPath(const TCHAR *lpszPath, CSTRING_VECTOR &cv, BOOL bCalledFromOutside = false);
	BOOL LoadTreeFromDirectory(const TCHAR *pszFileName, CTreeType &tt);
	int CalculateMaxLevel(CTreeType &tt);
	HTREEITEM OnFindItem(LPCTSTR strItem);
	HTREEITEM OnFindDlg(LPCTSTR strItem);
	BOOL SaveCsvTreeToFile(const TCHAR *pszFileName, CTreeType &tt);
	BOOL ValidCsvRecord(TCHAR *psz, int &iMaxLevel, TCHAR *pszDelimiter, int iLevel);
	BOOL LoadCsvTreeFromFile(const TCHAR *pszFileName, CTreeType &tt);
	BOOL DeleteItemM(HTREEITEM hItem);
	BOOL ExpandM(HTREEITEM hItem, UINT nCode);
	BOOL LoadTreeDataR(CTreeType &tt, HTREEITEM hti, OUTSIDE_PARAM op = OP_NONE);
	void RestoreStates(CTreeType &tt);
	int CountSubtree(HTREEITEM hti, OUTSIDE_PARAM op = OP_NONE);
	void CutSubtree();
	BOOL InitializeImageList();
    BOOL SelectVisibleItem(HTREEITEM hti);
	HTREEITEM SelectDropCursor(CPoint *pPoint = NULL);
	int CalculateIndentLevel(TCHAR *psz, TCHAR ch);
    void ParseTree(PARSING_FUNCTION pf, HTREEITEM hti = TVI_ROOT,void *pvParam = NULL);
	void OnButtonUp();
	void pfCollapse(HTREEITEM hti, void *);
    void pfExpand(HTREEITEM hti, void *);
    BOOL SaveTreeData(CTreeType &tt, HTREEITEM hti, OUTSIDE_PARAM op = OP_NONE);
	void SetLimitText(UINT uLimitText);
    void SaveTreeToFile(const TCHAR *pszFileName, CTreeType &tt);
	BOOL SaveIndentTreeToFile(const TCHAR *pszFileName, CTreeType &tt);
    BOOL LoadIndentTreeFromFile(const TCHAR *pszFileName, CTreeType &tt);
    BOOL LoadTreeFromFile(const TCHAR *pszFileName, CTreeType &tt);
    BOOL LoadTreeData(CTreeType &tt, HTREEITEM hti, OUTSIDE_PARAM op = OP_NONE);
	void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	void OnContextMenu(CWnd* pWnd, CPoint point);
	void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	void OnRename();
	void OnAddChild();
	void OnAddSibling();
	void OnAddChildName(LPCTSTR lpszItem); 
	void OnAddSiblingName(LPCTSTR lpszItem);
	void OnDeleteItem();
	void OnDeleteAllItems();
	void OnCollapse();
	void OnLoadEntireTree(FILE_FORMAT ff, CTreeType &tt);
	void OnSaveEntireTree(FILE_FORMAT ff, CTreeType &tt);
	void OnLoadSubtree(HTREEITEM hti);
	void OnSaveSubtree();
	void OnExpandAllLevelsSubtree();
	void OnExpandAllTree();
	void OnExpandOneLevelSubtree();
	void OnExpandOneLevelTree();
	BOOL IsChildNodeOf(HTREEITEM hitemChild, HTREEITEM hitemSuspectedParent);
	HTREEITEM CEditTreeCtrl::InsertItemAndSetImage(LPCTSTR lpszItem, 
		HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
	HTREEITEM CEditTreeCtrl::GetItemByName(HTREEITEM hItem, LPCTSTR szItemName);
	

/**
 * Copyright (C) 2005
 * Doga Arinir
 * 
 * Author: Doga Arinir
 * E-Mail: arinir@gmx.de
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the author or the company be held liable 
 * for any damages arising from the use of this software. EXPECT BUGS!
 * 
 * You may use this software in compiled form in any way you desire PROVIDING it is
 * not sold for profit without the authors written permission, and providing that this
 * notice and the authors name is included. If the source code in this file is used in 
 * any commercial application then acknowledgement must be made to the author of this file.
 */
public:
	BOOL m_bHasLines;
	BOOL m_bHasButtons;
	BOOL m_bCustomDrawn;
	
	
	CRect m_Rect;
	int   m_OffsetX;
	int   m_OffsetY;
	int   m_XMax;
	int   m_YMax; 
public:
	int m_ItemSpaceX;
	int m_ItemSpaceY;
	
	int m_LinkNodeSpaceY;

	COLORREF m_LeafTextColor;
	COLORREF m_LeafBkColor;
	COLORREF m_NodeTextColor;
	COLORREF m_NodeBkColor;
	COLORREF m_LinkTextColor;
	COLORREF m_LinkBkColor;
	
	COLORREF m_clrTopLeft;
	COLORREF m_clrBottomRight;
	COLORREF m_WindowBkColor;

	CFont m_Font;
	CFont m_NodeFont;
	CFont m_LeafFont;
	CFont m_LinkFont;

	CString m_sFontFace;
	LPCTSTR m_sItemFound;
	
	HTREE2VPMAP m_HTree2VP;
	CPen	m_TreeLinePen;
// Operations
public:
	void SetCustomDrawn(BOOL);
	BOOL GetCustomDrawn();

	//These operations are overwritten. The Problem is that those are non-virtual
	//functions...
	HTREEITEM InsertItem(LPTVINSERTSTRUCT lpInsertStruct);
	HTREEITEM InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter);
	HTREEITEM InsertItem(LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
	HTREEITEM InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
	BOOL DeleteItemV(HTREEITEM hItem);
	BOOL DeleteAllItemsV();

// Implementation
public:
	int GetItemSpaceX();
	void SetItemSpaceX(int);
	int GetItemSpaceY();
	void SetItemSpaceY(int);
	virtual ~CEditTreeCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditTreeCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:

	// Generated message map functions
//protected:
public:
	void ResetScrollbars();
	__forceinline ItemViewport* GetViewport(HTREEITEM hItem);
public:
	void DeleteAllViewportItemsV();
	void DrawNodeText(CDC *pDC, HTREEITEM item, CString text, int x, int y, int cx, int cy, COLORREF bkcolor,COLORREF txtcolor, HFONT txttype);
	void DrawLinkText(CDC *pDC, HTREEITEM item, CString text, int x, int y, int cx, int cy, COLORREF bkcolor,COLORREF txtcolor, HFONT txttype);
	void DrawLeafText(CDC *pDC, HTREEITEM item, CString text, int x, int y, int cx, int cy, COLORREF bkcolor,COLORREF txtcolor, HFONT txttype);
	int DrawItem(CDC *pDC, HTREEITEM, int x, int level = 0);
	void OnChangeTextFace(); 
	void OnChangeLinkTextColor(); 
	void OnChangeLeafTextColor(); 
	void OnChangeNodeTextColor(); 
	void OnChangeNodeBkColor(); 
	void OnChangeLinkBkColor();
	void OnChangeLeafBkColor();
	void OnChangeExpandTopLeft();
	void OnChangeExpandBottomRight();
	void OnChangeItemSpaceX(int x);
	void OnChangeItemSpaceY(int y);
	void OnChangeLinkNodeSpaceY(int y);

	void OnZoomIn();
	void OnZoomOut();
	void UpdateDimensions();

	//{{AFX_MSG(CEditTreeCtrl)
	afx_msg void OnCollapseAllEntireTree();
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCountEntireTree();
	afx_msg void OnCountSubtree();
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCalculateLevel();
	afx_msg void OnSortSubtreeAlphabetic();
	afx_msg void OnSortSubtreeNumeric();

	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	BOOL m_bInsertionMode;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTREECTRL_H__73D1D740_1211_4B37_AB0B_93D46A5842EC__INCLUDED_)
