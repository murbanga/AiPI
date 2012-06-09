// EditTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include ".\..\AIPI.h"
#include ".\..\AIPITreeDoc.h"
#include ".\..\AIPITreeView.h"
#include "EditTreeCtrl.h"
#include "../MainFrm.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CAIPIApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEditTreeCtrl

CEditTreeCtrl::CEditTreeCtrl(): CTreeCtrl(), m_bCustomDrawn(TRUE), m_ItemSpaceX(10), m_ItemSpaceY(100) 
{
	int aid[] =
	{
		IDC_DROP_COPY_ROOT,
		IDC_DROP_COPY_SON,
		IDC_DROP_MOVE_ABOVE,
		IDC_DROP_COPY_ABOVE,
		IDC_DROP_MOVE_ROOT,
		IDC_DROP_MOVE_SON,
		IDC_NODROP,
	}, k;

	ASSERT(ARRAY_SIZE(aid) == CUR_COUNT);

	m_pted = NULL;
	m_uLimitText = 0;
	m_bDragging = FALSE;
    m_pimagelist = NULL;

	m_bInsertionMode = false;
	m_hCursor = NULL;
	m_sItemFound = _T("");
	m_hItemFound = NULL;
	

	for (k = 0; k < CUR_COUNT; k++)
		m_ahCursor[k] = theApp.LoadCursor(aid[k]);

	//Vertical tree colors 
	m_TreeLinePen.CreatePen(PS_DOT, 1, RGB(192,192,192));

	m_LeafTextColor = RGB(255,255,163);
	m_LeafBkColor = RGB(0, 0, 102);

	m_NodeTextColor = RGB(255, 255, 255);
	m_NodeBkColor = RGB(102, 153, 255);

	m_LinkTextColor = RGB(128, 128, 128);
	m_LinkBkColor = RGB(255, 255, 255);

	m_clrTopLeft = RGB(128, 128, 128);
	m_clrBottomRight = RGB(128, 128, 128);

	m_WindowBkColor = COLOR_3DFACE;

	//Link vertical space from nodes
	m_LinkNodeSpaceY = 15;
	
	m_sFontFace = _T("Arial");
	m_Font.CreateFont(15,0,0,0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH| FF_DONTCARE, m_sFontFace);
	
	
/*	
	m_NodeFont.CreateFont(20,0,0,0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH| FF_DONTCARE, m_sFontFace);
	
	m_LinkFont.CreateFont(20,0,0,0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH| FF_DONTCARE, m_sFontFace);
	
	m_LeafFont.CreateFont(20,0,0,0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH| FF_DONTCARE, m_sFontFace);
*/
	
}


CEditTreeCtrl::~CEditTreeCtrl()
{
	DeleteAllViewportItemsV();
}


BEGIN_MESSAGE_MAP(CEditTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CEditTreeCtrl)
	ON_COMMAND(ID_COLLAPSE_ALL_ENTIRE_TREE, OnCollapseAllEntireTree)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_COMMAND(IDC_COUNT_ENTIRE_TREE, OnCountEntireTree)
	ON_COMMAND(IDC_COUNT_SUBTREE, OnCountSubtree)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_COMMAND(ID_CALCULATE_LEVEL, OnCalculateLevel)
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(ID_RENAME, OnRename)
	ON_COMMAND(ID_ADD_CHILD, OnAddChild)
	ON_COMMAND(ID_ADD_SIBLING, OnAddSibling)
	ON_COMMAND(ID_DELETE_ITEM, OnDeleteItem)
	ON_COMMAND(ID_DELETE_ALL_ITEMS, OnDeleteAllItems)
	ON_COMMAND(IDC_EXPAND_ALL_TREE, OnExpandAllTree)
	ON_COMMAND(ID_SORT_SUBTREE_ALPHABETIC, OnSortSubtreeAlphabetic)
	ON_COMMAND(ID_SORT_SUBTREE_NUMERIC, OnSortSubtreeNumeric)

	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZING()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditTreeCtrl message handlers

/***********************************************************************************
* Keyboard Handling
***********************************************************************************/

BOOL CEditTreeCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// When an item is being edited make sure the edit control
	// receives certain important key strokes

	if (GetEditControl())
	{
		if(pMsg->message == WM_KEYDOWN) 
		{
			if (pMsg->wParam == VK_INSERT)
			{
				// If VK_INSERT was preessed in course of editing, we want to cause
				// the program to add another sibling. Therefore, we simulate pressing of
				// VK_RETURN.
				m_bInsertionMode = true;
				pMsg->wParam = VK_RETURN;
			}
			else
				m_bInsertionMode = false;
		}
		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);
		return TRUE; // DO NOT process further
	}
	if (m_bDragging &&
			(pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP))
	{
		if (pMsg->wParam == VK_ESCAPE)
		{	// Cancel Drag Mode
			m_bDragging = false;
			ReleaseCapture();
			SelectDropTarget(NULL);
   			m_hCursor = NULL;
		}
		POINT pt;
		GetCursorPos(&pt);
		// Cause MouseMove() (and as a result OnSetCursor()) to be called.
		SetCursorPos(pt.x, pt.y);
		return true;
	}
	if (pMsg->message == WM_KEYDOWN) 
	{
		switch(pMsg->wParam)
		{
		case 'C':
			if (GetKeyState(VK_CONTROL) & 0x80000000) 
				OnSaveSubtree();
			break;
		case 'A':
			// Ctrl+A Paste m_ttTransfer above current item
			if (GetKeyState(VK_CONTROL) & 0x80000000) 
				OnLoadAbove(GetSelectedItem());
			break;
		case 'V':
			// Ctrl+V Paste m_ttTransfer as a son of current item
			// Ctrl+Shift+V Paste m_ttTransfer as a new root
			if (GetKeyState(VK_CONTROL) & 0x80000000) 
			{
				if (GetKeyState(VK_SHIFT) & 0x80000000) 
					OnLoadSubtree(TVI_ROOT);
				else
					OnLoadSubtree(GetSelectedItem());
			}
			break;
		case 'X':
			if (GetKeyState(VK_CONTROL) & 0x80000000) 
				CutSubtree();
			break;
		case 'N':
			// Ctrl+N Count Subtree
			// Ctrl+Shift+N Count entire tree
			if (GetKeyState(VK_CONTROL) & 0x80000000) 
			{
				if (GetKeyState(VK_SHIFT) & 0x80000000) 
					OnCountEntireTree();
				else
					OnCountSubtree();
			}
			break;
		case 'T':
			// Ctrl+T Sort Subtree Alphabetic
			// Ctrl+Shift+T Sort Subtree Numeric
			if (GetKeyState(VK_CONTROL) & 0x80000000) 
			{
				if (GetKeyState(VK_SHIFT) & 0x80000000) 
					OnSortSubtreeNumeric();
				else
					OnSortSubtreeAlphabetic();
			}
			break;
		case 'L':
			if (GetKeyState(VK_CONTROL) & 0x80000000) 
				OnCalculateLevel();
			break;
		case VK_SPACE:
		case VK_RETURN: 
			OnAddSibling();
			break;
		case VK_INSERT:
			if (GetKeyState(VK_CONTROL) & 0x80000000) 
				OnSaveEntireTree(FF_CLIPBOARD_TYPE, m_pted->m_tt);
			else if (GetKeyState(VK_SHIFT) & 0x80000000) 
				OnLoadEntireTree(FF_CLIPBOARD_TYPE, m_pted->m_tt);
			else
				OnAddChild();
			break;
		case VK_F2:
			OnRename();
			break;
		case VK_DELETE:
			if (GetKeyState(VK_CONTROL) & 0x80000000) 
				OnDeleteAllItems();
			else
				OnDeleteItem();
			break;
		default:
			// Default behaviour for other keys such as arrows
			return CTreeCtrl::PreTranslateMessage(pMsg);
		}
		return TRUE; // DO NOT process further
	}
	return CTreeCtrl::PreTranslateMessage(pMsg);
}

/***********************************************************************************
* Context-Menu Handling
***********************************************************************************/

void CEditTreeCtrl::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//Work out the position of where the context menu should be
	CPoint p(GetCurrentMessage()->pt);
	CPoint pt(p);
	ScreenToClient(&pt);
	Select(HitTest(pt), TVGN_CARET);
	OnContextMenu(NULL, p);
	*pResult = 0;
}

void CEditTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_MENU));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

/***********************************************************************************
* Functions to handle Drag and drop to Copy/Move/Paste items
***********************************************************************************/

void CEditTreeCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint ptAction;
	NMTREEVIEW *pnmtv;

	GetCursorPos(&ptAction);
	ScreenToClient(&ptAction);
	ASSERT(!m_bDragging);
	m_bDragging = TRUE;
	m_bTimerABOVE_Active = false;
	m_bTimerBELOW_Active = false;
	m_uOldFlags = 0;

	// determine the item being dragged:
	pnmtv = (NMTREEVIEW*)pNMHDR;
	m_hitemDrag = pnmtv->itemNew.hItem;
	m_hitemDrop = NULL;

	    SetCapture();
	    SelectDropCursor();
}

void CEditTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	HTREEITEM	hitem;

	if (m_bDragging || m_bCustomDrawn)
	{
		hitem = SelectDropCursor(&point);
		if (hitem != NULL)
		{
			SelectDropTarget(hitem);
			m_hitemDrop = hitem;
			
		}
	}
	CTreeCtrl::OnMouseMove(nFlags, point);

}

void CEditTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	OnButtonUp();
/////////////////////////////////////////////
		////Vertical Tree Code
//////////////////////////////////////////////
	if (m_bCustomDrawn)
	{
		HTREE2VPMAP::iterator it = m_HTree2VP.begin();

		point.x -= m_OffsetX;
		point.y -= m_OffsetY;
		while (it != m_HTree2VP.end())
		{
			ItemViewport *vp = (*it).second;
			if (vp->x <= point.x && ((vp->x+vp->cx) >= point.x)
				&& vp->y <= point.y && ((vp->y+vp->cy) >= point.y))
			{
				Expand(vp->item, TVE_TOGGLE);
				Invalidate();
				return;
			}
			it++;
		}
	}
	else
		CTreeCtrl::OnLButtonUp(nFlags, point);
	
	
	
}

void CEditTreeCtrl::OnButtonUp()
{
/************************************************************************************
    Ensure m_ttTransfer is always allocated and deallocated correctly:
*************************************************************************************
        1) This function allocates a CTreeType.
        2) The CTreeType is used to save data from the TreeControl. This is done
           in SaveTreeData()
        3) At the end of the function, the CTreeType is deallocated.
************************************************************************************/
    int iCount;

	if (m_bDragging)
	{
		m_bDragging = FALSE;

		if (m_bTimerABOVE_Active)
		{
			KillTimer(TVHT_ABOVE);
			m_bTimerABOVE_Active = false;
		}
		if (m_bTimerBELOW_Active)
		{
			KillTimer(TVHT_BELOW);
			m_bTimerBELOW_Active = false;
		}

		iCount = GetCount();
		if (!m_ttTransfer.AllocateTree(iCount))
		{
			AfxMessageBox(_T("Out of memory"));
			return;
		}
		if (m_hCursor == m_ahCursor[CUR_COPY_ROOT] || 
				m_hCursor == m_ahCursor[CUR_MOVE_ROOT])
		{
			SaveTreeData(m_ttTransfer, m_hitemDrag, OP_SUBTREE);
			if (m_hCursor == m_ahCursor[CUR_MOVE_ROOT])
				DeleteItemM(m_hitemDrag);
			LoadTreeDataR(m_ttTransfer, TVI_ROOT, OP_SUBTREE);
			SelectVisibleItem(m_ttTransfer.m_pnt[1].hti);
		    ExpandM(m_hitemDrop, TVE_EXPAND);
		}
		// Dragging an item to itself or to a node of its subtree is
		// not allowed 
		else if (m_hitemDrag != m_hitemDrop && !IsChildNodeOf(m_hitemDrop, m_hitemDrag))
		{
			if (m_hCursor == m_ahCursor[CUR_MOVE_SON] ||
                    m_hCursor == m_ahCursor[CUR_COPY_SON])
            {
				SaveTreeData(m_ttTransfer, m_hitemDrag, OP_SUBTREE);
    			if (m_hCursor == m_ahCursor[CUR_MOVE_SON])
				    DeleteItemM(m_hitemDrag);
				LoadTreeDataR(m_ttTransfer, m_hitemDrop, OP_SUBTREE);
    			SelectVisibleItem(m_ttTransfer.m_pnt[1].hti);
			    ExpandM(m_hitemDrop, TVE_EXPAND);
            }
			if (m_hCursor == m_ahCursor[CUR_MOVE_ABOVE] ||
					m_hCursor == m_ahCursor[CUR_COPY_ABOVE])
            {
				SaveTreeData(m_ttTransfer, m_hitemDrag, OP_SUBTREE);
    			if (m_hCursor == m_ahCursor[CUR_MOVE_ABOVE])
					DeleteItemM(m_hitemDrag);
				OnLoadAbove(m_hitemDrop);
            }
		}
		else
        {
			MessageBeep(0);
			SelectVisibleItem(m_hitemDrag);
        } 

		ReleaseCapture();
		SelectDropTarget(NULL);
   		m_hCursor = NULL;
        m_ttTransfer.DeAllocateTree();
	}

}

// Timer function to handle scrolling while dragging.
void CEditTreeCtrl::OnTimer(UINT nIDEvent) 
{
	/*
	if (nIDEvent == TVHT_ABOVE )
		SendMessage(WM_VSCROLL, SB_LINEUP, NULL);
	else
		SendMessage(WM_VSCROLL, SB_LINEDOWN, NULL);
	CTreeCtrl::OnTimer(nIDEvent);
	*/
	// Timer function to handle scrolling while dragging.

	if (nIDEvent == TVHT_ABOVE )
		SendMessage(WM_VSCROLL, SB_LINEUP, NULL);
	if (nIDEvent == TVHT_BELOW )
		SendMessage(WM_VSCROLL, SB_LINEDOWN, NULL);

	CTreeCtrl::OnTimer(nIDEvent);


}

// Selects the appropriate cursor in dragging mode
// F3										- MOVE as a new root
// Ctrl+F3									- COPY as a new root
// Cursor on the right of an item			- MOVE as a son to the right of dropped item.
// Ctrl + Cursor on the right of an item	- COPY as a son to the right of dropped item.
// Cursor on an item or to its left			- MOVE above dropped item.
// Ctrl + Cursor on an item or to its left	- COPY above dropped item.

HTREEITEM CEditTreeCtrl::SelectDropCursor(CPoint *pPoint /*= NULL*/)
{
	HCURSOR hOldCursor = m_hCursor;
	UINT uFlags = 0;
	HTREEITEM hitem = NULL;
	CString str;
	int nKey = 0;

	if (m_bDragging)
	{
		if (pPoint != NULL)
		{
			if (GetKeyState(VK_F3) & 0x80000000) 
				nKey = VK_F3;
			hitem = HitTest(*pPoint, &uFlags);

			// Set a Timer to scroll periodically, while dragging, if mouse cursor is 
			// either below or above the control.

			// The timer must be set only if the flags have changed since the last call.
			if (m_uOldFlags != uFlags)
			{
				m_uOldFlags = uFlags;
				if (uFlags & TVHT_ABOVE)
				{
					SetTimer(TVHT_ABOVE, SCROLL_SPEED, NULL);
					m_bTimerABOVE_Active = true;
				}
				else if (uFlags & TVHT_BELOW)
				{
					SetTimer(TVHT_BELOW, SCROLL_SPEED, NULL);
					m_bTimerBELOW_Active = true;
				}
				else
				{
					if (m_bTimerABOVE_Active)
					{
						KillTimer(TVHT_ABOVE);
						m_bTimerABOVE_Active = false;
					}
					if (m_bTimerBELOW_Active)
					{
						KillTimer(TVHT_BELOW);
						m_bTimerBELOW_Active = false;
					}
				}
			}

			// Dragging an item to itself or to a node of its subtree is
			// not allowed 
			if ((m_hitemDrag == hitem || IsChildNodeOf(hitem, m_hitemDrag) 
					|| hitem == NULL) && nKey != VK_F3)
			{
				m_hCursor = m_ahCursor[CUR_NODROP];
				SetCursor(m_hCursor);
				return NULL;
			}
		}
		if (nKey == VK_F3)
		{
			if (GetKeyState(VK_CONTROL) & 0x80000000) 
				m_hCursor = m_ahCursor[CUR_COPY_ROOT];
			else
				m_hCursor = m_ahCursor[CUR_MOVE_ROOT];
		}
		else if (uFlags & (TVHT_ONITEM | TVHT_ONITEMINDENT | TVHT_ONITEMBUTTON))
		{
			if (GetKeyState(VK_CONTROL) & 0x80000000) 
				m_hCursor = m_ahCursor[CUR_COPY_ABOVE];
			else
				m_hCursor = m_ahCursor[CUR_MOVE_ABOVE];
		}
		else if (GetKeyState(VK_CONTROL) & 0x80000000) 
			m_hCursor = m_ahCursor[CUR_COPY_SON];
		else
			m_hCursor = m_ahCursor[CUR_MOVE_SON];
		if (hOldCursor != m_hCursor)
			SetCursor(m_hCursor);
	}
	return hitem;
}

/***********************************************************************************
* Cursor Functions
***********************************************************************************/
BOOL CEditTreeCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (m_hCursor == NULL)
		return CTreeCtrl::OnSetCursor(pWnd, nHitTest, message);
	SelectDropCursor();
	SetCursor(m_hCursor);
	return 0;
}

/***********************************************************************************
* Edit Functions
***********************************************************************************/

void CEditTreeCtrl::OnRename() 
{
	HTREEITEM hti;

	hti = GetSelectedItem();
	EditLabel(hti);
}

// Called when a item is being edited, when  we call the function
// 	EditLabel(hti); (See OnRename())

void CEditTreeCtrl::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	CEdit *pEdit;

	pEdit = GetEditControl();
	pEdit->SetLimitText(m_uLimitText);
	*pResult = 0;
}

void CEditTreeCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO *ptvinfo;

	// Called at exit from Edit Mode
	ptvinfo = (TV_DISPINFO *)pNMHDR;
	if (ptvinfo->item.pszText != NULL)
	{
		ptvinfo->item.mask = TVIF_TEXT;
		SetItem(&ptvinfo->item);
		m_pted->SetModifiedFlag();
	}
	if (m_bInsertionMode) // VK_INSERT was pressed in course of editing
		OnAddSibling();
	else
		m_bInsertionMode = false;
	*pResult = TRUE; // TRUE => Accept the label
}

// Set the maximum size of an edited item.
void CEditTreeCtrl::SetLimitText(UINT uLimitText)
{
	m_uLimitText = uLimitText;
}

/***********************************************************************************
* Add Child, Add Sibling and delete Functions
***********************************************************************************/

void CEditTreeCtrl::OnAddChild() 
{
	HTREEITEM hti, htiChild;
	hti = GetSelectedItem();
	htiChild = InsertItemAndSetImage(_T("New Item"), hti, TVI_LAST);
	EnsureVisible(htiChild);
	EditLabel(htiChild);
	Select(htiChild, TVGN_CARET);
}

void CEditTreeCtrl::OnAddChildName(LPCTSTR lpszItem) 
{
	HTREEITEM hti, htiChild;
	hti = GetSelectedItem();
	htiChild = InsertItemAndSetImage(lpszItem, hti, TVI_LAST);
	EnsureVisible(htiChild);
	EditLabel(htiChild);
	Select(htiChild, TVGN_CARET);
}

void CEditTreeCtrl::OnAddSibling() 
{
	HTREEITEM hti, htiParent, htiChild;
	hti = GetSelectedItem();
	htiParent = GetParentItem(hti);
	htiChild = InsertItemAndSetImage(_T("New Item"), htiParent, TVI_LAST);
	EnsureVisible(htiChild);
	EditLabel(htiChild);
	Select(htiChild, TVGN_CARET);
}

void CEditTreeCtrl::OnAddSiblingName(LPCTSTR lpszItem) 
{
	HTREEITEM hti, htiParent, htiChild;
	hti = GetSelectedItem();
	htiParent = GetParentItem(hti);
	htiChild = InsertItemAndSetImage(lpszItem, htiParent, TVI_LAST);
	EnsureVisible(htiChild);
	EditLabel(htiChild);
	Select(htiChild, TVGN_CARET);
}

void CEditTreeCtrl::OnDeleteItem() 
{
	HTREEITEM hti;

	hti = GetSelectedItem();
    if (hti != NULL)
    	DeleteItemM(hti);
}

void CEditTreeCtrl::OnDeleteAllItems() 
{
	// We don't want to set the modified flag if the tree was NOT modified. However, we
	// cannot rely on the return code of DeleteItem() to check if the tree was empty,
	// since DeleteItem() return success even in this case. So, we use GetCount() for that
	// purpose.

	int iCount = GetCount();

	DeleteItem(TVI_ROOT);
	if (iCount > 0)  
		m_pted->SetModifiedFlag();  
}

/***********************************************************************************
* Functions to handle Ctrl+C, Ctrl+X, Ctrl+V, Ctrl+Shift+V
***********************************************************************************/

// Called when the user presses either Ctrl+C or Ctrl+X
void CEditTreeCtrl::OnSaveSubtree() 
{
   	int iCount;
	
	iCount = GetCount();
	
	try
    {
		if (!m_ttTransfer.AllocateTree(iCount))
            throw TTE_MEMORY;
	    m_hitemDrag = GetSelectedItem();
	    if (!SaveTreeData(m_ttTransfer, m_hitemDrag, OP_SUBTREE))
            throw TTE_MEMORY;
    }
    catch(TREE_TYPE_ERROR fe)
    {
        if (fe == TTE_MEMORY)
		    AfxMessageBox(_T("Out of memory"));
    }
	
}

// Called when the user presses Ctrl+X
void CEditTreeCtrl::CutSubtree()
{
	OnSaveSubtree();
	OnDeleteItem();
}

// Called when the user presses Ctrl+V, Ctrl+Shift+V
void CEditTreeCtrl::OnLoadSubtree(HTREEITEM hti)
{
	if (m_ttTransfer.m_pnt != NULL)
	{
		LoadTreeDataR(m_ttTransfer, hti, OP_SUBTREE);
        hti = m_ttTransfer.m_pnt[1].hti;
		SelectVisibleItem(hti);
	    ExpandM(hti, TVE_EXPAND);
	}
}

/***********************************************************************************
* Functions to handle Load Above 
***********************************************************************************/
// Called when the user presses Ctrl+A or when drop occurs while the above cursor is
// shown (see OnButtonUp())
//
// As far as I know, there is no way to insert an item between siblings, using InsertItem().
// We do this in four phases:
//
//	1) LoadTreeDataR() is called to copy the dragged item (or the item selected when
//		    Ctrl+C or Ctrl+X was pressed), as the LAST child of the PARENT of:
//		- The dropped item in case of Drag and Drop
//		- The Selected item in case of Ctrl+A
//
//	2) A LOAD_ABOVE structure is built. It contains:
//		- The dragged item:										HTREEITEM htiLoadedItem;	
//		- The item above which the MOVE/COPY must be performed:	HTREEITEM hti;
//		- An array containing all the children of the parent	HTREEITEM *pChildrenOfParent;
//		- The size of this array:								int iSizeChildrenOfParent;
//
//	3) InsertLoadItemBeforeHti() is called to change the sibling orders in the array
//	   so that Load item stands above hti.
//	   
//    4) SortChildrenCB(&tvscb) is called to sort the sibling, using the CompareForLoadAbove
//	   callback function. This function sorts the siblings in the order of the indices of
//	   the array.
	
void CEditTreeCtrl::OnLoadAbove(HTREEITEM hti)
{
	
	LOAD_ABOVE la;
	HTREEITEM htiParent;
	int iCount = GetCount();
    TVSORTCB tvscb;

	if (m_ttTransfer.m_pnt != NULL)
	{
		htiParent = GetParentItem(hti);
		LoadTreeDataR(m_ttTransfer, htiParent, OP_SUBTREE);
		SelectVisibleItem(hti);
	    ExpandM(hti, TVE_EXPAND);
	}
/*
	LOAD_ABOVE la;
	HTREEITEM htiParent;
	int iCount=0; 
	TVSORTCB tvscb;

	if (m_ttTransfer.m_pnt != NULL)
	{
		htiParent = GetParentItem(hti);
		LoadTreeDataR(m_ttTransfer, htiParent, OP_SUBTREE);
		SelectVisibleItem(hti);
		ExpandM(hti, TVE_EXPAND);
	}
	iCount= GetCount();
*/
	la.pChildrenOfParent = new HTREEITEM[iCount];
	if (la.pChildrenOfParent == NULL)
	{
	    AfxMessageBox(_T("Out of memory"));
		return;
	}
	la.pChildrenOfParent[0] = GetChildItem(htiParent);
	
	
	for (la.iSizeChildrenOfParent = 1; la.pChildrenOfParent[la.iSizeChildrenOfParent - 1] != NULL; la.iSizeChildrenOfParent++)
		la.pChildrenOfParent[la.iSizeChildrenOfParent] = GetNextSiblingItem(la.pChildrenOfParent[la.iSizeChildrenOfParent-1]);
		la.iSizeChildrenOfParent--;
	
	/*
	for(int i=1;i;)
	{
		la.pChildrenOfParent[i] = GetNextSiblingItem(la.pChildrenOfParent[i-1]); 
		if(NULL==la.pChildrenOfParent[i])
		{
			break;
		}
	}
	la.iSizeChildrenOfParent = i;
	*/
	la.hti = hti;
	la.htiLoadedItem = m_ttTransfer.m_pnt[1].hti;
	InsertLoadItemBeforeHti(la);

    tvscb.hParent = htiParent;
    tvscb.lpfnCompare = CompareForLoadAbove;
    tvscb.lParam = (LPARAM)&la;
    SortChildrenCB(&tvscb);
	SelectVisibleItem(la.htiLoadedItem);
	m_pted->SetModifiedFlag();
	delete [] la.pChildrenOfParent;

}

//	Change the sibling orders in the array so that Load item stands above hti.
void CEditTreeCtrl::InsertLoadItemBeforeHti(LOAD_ABOVE &la)
{
	HTREEITEM htiLoadItem = la.htiLoadedItem;
	int idxLoadItem = SearchLoadAboveItem(la, la.htiLoadedItem);
	int idxHti = SearchLoadAboveItem(la, la.hti);

	if (idxHti < idxLoadItem)
	{
		memmove(la.pChildrenOfParent + idxHti + 1, la.pChildrenOfParent + idxHti,
			(idxLoadItem - idxHti) * sizeof(HTREEITEM));
		la.pChildrenOfParent[idxHti] = htiLoadItem;
	}
	else	// idxHti > idxLoadItem _ Should NOT happen if this function was called
	{		// from OnLoadAbove() since idxLoadItem is the sibling which has the
			// greatest index. 	
		memmove(la.pChildrenOfParent + idxLoadItem, la.pChildrenOfParent + idxLoadItem + 1,
			(idxHti - idxLoadItem - 1) * sizeof(HTREEITEM));
		la.pChildrenOfParent[idxHti - 1] = htiLoadItem;
	}
}

// Searches an item in the la.pChildrenOfParent array and returns its index.
int SearchLoadAboveItem(LOAD_ABOVE &la, HTREEITEM hti)
{
	int k;

	for (k = 0; k <= la.iSizeChildrenOfParent; k++)
	{
		if (la.pChildrenOfParent[k] == hti)
			return k;
	}
	return -1; // Not found (should not happen)
}

int CALLBACK CompareForLoadAbove(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int i1, i2;
    LOAD_ABOVE *pla = (LOAD_ABOVE *)lParamSort;

	HTREEITEM hti1 = (HTREEITEM)lParam1;
	HTREEITEM hti2 = (HTREEITEM)lParam2;
	i1 = SearchLoadAboveItem(*pla, hti1);
	i2 = SearchLoadAboveItem(*pla, hti2);
	if (i1 > i2)
       return 1;
	if (i1 < i2)
       return -1;
    return 0;
}

/***********************************************************************************
* Functions to handle Expand/Collapse
***********************************************************************************/

/**************************************************************************************
//    ParseTree is a function, that do the folowing:
//        - Parse a SubTree in DFS (Depth First Search) (or parse all the tree if hti = TVI_ROOT)
//        - For every node visited, call the callback function pf.
//    (This is useful in order not to deal each time with the problem of writing a recursive
//     function to scan the tree. Same idea as qsort())
//     
//     This function is used here to handle Expand/Collapse but can be reused for other
//	   purposes.
**************************************************************************************/
void CEditTreeCtrl::ParseTree(PARSING_FUNCTION pf, HTREEITEM hti /* = TVI_ROOT */,
          void *pvParam /* = NULL */)
{
    if (hti == TVI_ROOT)
        hti = GetRootItem(); 
    else
    {
        hti = GetChildItem(hti); 
    }
    while(hti != NULL)
	{
        (this->*pf)(hti, pvParam);
    	ParseTree(pf, hti, pvParam);
        hti = GetNextSiblingItem(hti);
	}
}

// Called when the user selects Expand All from the context menu.
void CEditTreeCtrl::OnExpandAllTree() 
{
   	ParseTree(pfExpand);
}


// Called when the user selects Collapse All from the context menu.
void CEditTreeCtrl::OnCollapseAllEntireTree() 
{
   	ParseTree(pfCollapse);
}

// Note the second parameter must be present to comply with the definition
// of the PARSING_FUNCTION, but there is no need to give it a name as it's not used.
void CEditTreeCtrl::pfExpand(HTREEITEM hti, void *)
{
    ExpandM(hti, TVE_EXPAND);
}

// Note the second parameter must be present to comply with the definition
// of the PARSING_FUNCTION, but there is no need to give it a name as it's not used.
void CEditTreeCtrl::pfCollapse(HTREEITEM hti, void *)
{
    ExpandM(hti, TVE_COLLAPSE);
}

/***********************************************************************************
* Load Functions
***********************************************************************************/

//	1) Loads a tree from:
//		- A Directory to a CTreeType structure.
//		- A TRE file to a CTreeType structure.
//		- A IDT file to a CTreeType structure.
//		- A CSV file to a CTreeType structure.
//		- The Clipboard to a CTreeType structure.
//	2) If the loading ended successfully, LoadTreeDataR() is called then to transfer the tree
//		from the CTreeType structure to the Tree Control.

void CEditTreeCtrl::OnLoadEntireTree(FILE_FORMAT ff, CTreeType &tt)
{
/************************************************************************************
    Ensure tt is always allocated and deallocated correctly:
*************************************************************************************
        1) This function allocates a CTreeType.
            The allocation is done in the functions:
                - LoadTreeFromFile()
		        - LoadIndentTreeFromFile()
				- LoadCsvTreeFromFile()
                (These functions are never called from elsewhere)
        2) The CTreeType is used to load data to the TreeControl. This is done
           in LoadTreeDataR()
        3) At the end of this function, the CTreeType is not neeeded anymore and
           is deallocated.
************************************************************************************/
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	//pMainFrame->m_wndStatusBar.SetPaneInfo( 1, nID, nStyle, 100);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("Loading tree data..."));
	pMainFrame->m_wndOutputTabView.UpdateWindow();
	
	
	CPerfTimer t;
	
	
	WORD wTotalNbItems;
    CString str;
    BOOL rc;

	BeginWaitCursor(); // display the hourglass cursor
	UpdateWindow();

	t.Start();
    try
    {
        switch(ff)
        {
		case FF_DIRECTORY_TYPE:
            rc = LoadTreeFromDirectory(m_pted->m_strFileNamePath, tt);
            break;
        case FF_TREE_TYPE:
            rc = LoadTreeFromFile(m_pted->m_strFileNamePath, tt);
			break;
		case FF_PROJ_TYPE:
            rc = LoadIndentTreeFromFile(m_pted->m_strFileNamePath, tt);
            break;
        case FF_INDENT_TYPE:
		    rc = LoadIndentTreeFromFile(m_pted->m_strFileNamePath, tt);
            break;
        case FF_CSV_TYPE:
		    rc = LoadCsvTreeFromFile(m_pted->m_strFileNamePath, tt);
            break;
		case FF_CLIPBOARD_TYPE:
			rc = PasteEntireTreeFromCliboard(tt);
			break;
        default:
            AfxMessageBox(_T("Unknown file format!"));
            return;
        }
        if (rc)
        {
            wTotalNbItems = tt.m_wTotalNbItems;
            rc = LoadTreeDataR(tt, GetRootItem(), OP_ENTIRE_TREE);
			if (tt.m_wTotalNbItems != wTotalNbItems || !rc)
		 		throw TTE_INVALID_FILE;
			if (ff == FF_DIRECTORY_TYPE)
			{   // Expand only one level, since these trees may be very big.
   				ParseTree(pfCollapseAndSort);
       			Expand(GetRootItem(), TVE_EXPAND);
			}
		}
	}
    catch(TREE_TYPE_ERROR fe)
    {
		if (ff != FF_CLIPBOARD_TYPE)
		{
			// If Pasting from a clipboard, which contains invalid data, do nothing
			// but don't display any error message.
			switch(fe)
			{
			case TTE_EMPTY_FILE:
				str.Format(_T("Input tree file %s is empty"), m_pted->m_strFileNamePath);
				AfxMessageBox(str);
				break;
			case TTE_MEMORY:
				str = _T("Out of memory");
				AfxMessageBox(str);
				break;
			case TTE_INVALID_FILE:
				str.Format(_T("Invalid input file %s"), m_pted->m_strFileNamePath);
				AfxMessageBox(str);
				return;
				break;
			case TTE_INVALID_CSV_FILE:
				str.Format(_T("Invalid CSV file %s"), m_pted->m_strFileNamePath);
				AfxMessageBox(str);
				break;
			case TTE_OPEN:
				str.Format(_T("Cannot open input file %s: %s"), m_pted->m_strFileNamePath,  strerror(errno));
				AfxMessageBox(str);
				break;
			case TTE_READ:
    			str.Format(_T("Cannot read from file %s: %s"), m_pted->m_strFileNamePath,  strerror(errno));
				AfxMessageBox(str);
				break;
			case TTE_CLOSE:
    			str.Format(_T("Cannot close input file %s: %s"), m_pted->m_strFileNamePath,  strerror(errno));
				AfxMessageBox(str);
				break;
			case TTE_INVALID_DIRECTORY:
    			str.Format(_T("Cannot find directory %s: %s"), m_pted->m_strFileNamePath,  strerror(errno));
				AfxMessageBox(str);
				break;
			}
			
			
			pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Deleting items..."), RGB(0,0,0), TRUE);
						
			tt.m_wTotalNbItems = wTotalNbItems;
			OnDeleteAllItems();	
			
			pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
			pMainFrame->m_wndOutputTabView.AddMsg(_T("Process finished"));
			
			
		}
	}
    if (ff == FF_DIRECTORY_TYPE)
	{
// Title is "Untitled"
//		m_pted->m_strFileName is used as the default file name , when the Save 
//		function (Ctrl+S) is called. If Ctrl+D was called, we cannot, of course, 
//		giving the tree name we built, the name of an existing directory. So, we reset
//		m_strFileName to force the user to choose a name, when he saves the tree.
		m_pted->m_strFileNamePath.Empty();
	}
	
    tt.DeAllocateTree();
	if (rc)
		m_pted->SetModifiedFlag(false);  
    EndWaitCursor(); // remove the hourglass cursor
	pMainFrame->StopTimer(t, _T("Loading tree data elapsed seconds ... "));
}

// Load the directory (just the directory paths, not the file names), whose name
// is indicated by the parameter pszFileName, to a CTreeType structure.
BOOL CEditTreeCtrl::LoadTreeFromDirectory(const TCHAR *pszFileName, CTreeType &tt)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading tree data..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);
	

	CSTRING_VECTOR cv, cvFirstDirRecords;
    TREE_RECORD_VECTOR vtr;
    TREE_RECORD tr;
	int iSize, ifrSize, iMaxLevel = -1, j, k, rc;
	TCHAR szRecord[MAX_ASCII_RECORD];
    TCHAR lpszSaveDir[_MAX_PATH];

    GetCurrentDirectory(_MAX_PATH, lpszSaveDir);

	if (SetCurrentDirectory(pszFileName) == -1)
        throw TTE_INVALID_DIRECTORY;

	CFileFind ff;
    CString str;
	k = ff.FindFile(pszFileName);
	if (!k)
		FindPath(NULL, cv, true);
	else
		FindPath(pszFileName, cv, true);

	iSize = cv.size();
	GenerateFirstDirectoryRecords(pszFileName, cvFirstDirRecords);
	ifrSize = cvFirstDirRecords.size();
	for (j = 0, k = 0; k < iSize;)
	{
		if (j < ifrSize)
		{
			_tcscpy(szRecord, LPCTSTR(cvFirstDirRecords[j]));
			j++;
			//Status Bar
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, k*100/ifrSize);
		}
		else
		{
			_tcscpy(szRecord, LPCTSTR(cv[k]));
			k++;
			//Status Bar
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, k*100/iSize);
		}
		tr.iLevel = CalculateIndentLevel(szRecord, '\\');
		ValidCsvRecord(szRecord, iMaxLevel, m_pted->m_szDelimiter, tr.iLevel);
	   // Dynamically allocated vector begins with 0 elements.
		tr.str = szRecord;
		vtr.push_back(tr);
		
		
		
	}
	
	rc = LoadCsvTreeFromMemory(vtr, tt, iMaxLevel, FF_DIRECTORY_TYPE);
	SetCurrentDirectory(lpszSaveDir);

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	return rc;
}

/**************************************************************************************
	Load tree from a TRE file.
	If the tree was successfully read, a CTreeType structure is allocated, containing
	the tree.
	return true if successful
**************************************************************************************/
BOOL CEditTreeCtrl::LoadTreeFromFile(const TCHAR *pszFileName, CTreeType &tt)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading tree data..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	FILE *fp;
    CString str;
    WORD wTotalNbItems;
    int iCount;
	BOOL rc = true;
    NODE_TYPE *pnt;

	//AfxMessageBox(_T("Unicode LoadTreeFormFile"));

	fp = _tfopen(pszFileName, _T("rb"));
	if (fp == NULL)
		throw TTE_OPEN;
	if (fread(&wTotalNbItems, 1, sizeof(WORD), fp) == 0)
		throw TTE_EMPTY_FILE;
	if (wTotalNbItems == 0)
		throw TTE_EMPTY_FILE;
	if (!tt.AllocateTree(wTotalNbItems))
		throw TTE_MEMORY;
	for (iCount = 0; iCount <= wTotalNbItems; iCount++)
    {
		pnt = &tt.m_pnt[iCount];
    	fread(&pnt->wNbItems, 1, sizeof(pnt->wNbItems), fp);
    	if (feof(fp))
            throw TTE_INVALID_FILE; // Unexpected end of file
		if (ferror(fp))
			throw TTE_READ;
    	fread(&pnt->wBufSize, 1, sizeof(pnt->wBufSize), fp);
	    if (feof(fp))
            throw TTE_INVALID_FILE; // Unexpected end of file
		if (ferror(fp))
			throw TTE_READ;
        if (pnt->wBufSize > 0)
        {
    	    //Status Bar
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iCount*100/wTotalNbItems);
			
			pnt->buf = new TCHAR[pnt->wBufSize + 1];
			
    	    if (pnt->buf == NULL)
                throw TTE_MEMORY;
    	    fread(pnt->buf, pnt->wBufSize, sizeof(TCHAR), fp);
			//AfxMessageBox(pnt->buf);
			
    	    
			pnt->buf[pnt->wBufSize] = 0;
	        if (feof(fp))
                throw TTE_INVALID_FILE; // Unexpected end of file
		    if (ferror(fp))
			    throw TTE_READ;

			
        }
    	
		fread(&pnt->uState, 1, sizeof(pnt->uState), fp);
	    if (ferror(fp))
            throw TTE_READ;
    }

	
	fclose(fp);
	if (feof(fp))
		throw TTE_CLOSE;
	tt.m_wTotalNbItems = wTotalNbItems;

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	return true;
}

/**************************************************************************************
	Load tree from a IDT file.
	If the tree was successfully read, a CTreeType structure is allocated, containing
	the tree.
	return true if successful
**************************************************************************************/
BOOL CEditTreeCtrl::LoadIndentTreeFromFile(const TCHAR *pszFileName, CTreeType &tt)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading tree data..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	FILE *fp;
    CString str;
    WORD wTotalNbItems = 0;
    BOOL rc = true;
    TCHAR seps[] = _T("\t\n");
    TCHAR *token;
    int n, j, iMaxLevel;
    TREE_RECORD_VECTOR vtr;
    TREE_RECORD tr;
	int *piLastAtLevel = NULL;
    NODE_TYPE *pnt;
    TCHAR szRecord[MAX_ASCII_RECORD];


	//AfxMessageBox(_T("Unicode LoadIdentTreeFormFile"));

    try
    {
	    fp = _tfopen(pszFileName, _T("rt"));
	    if (fp == NULL)
		    throw TTE_OPEN;
        for (;;)
        {
	        token = _fgetts(szRecord, MAX_ASCII_RECORD, fp);
    	    if (token == NULL && feof(fp))
                break;
	        if (ferror(fp))
				throw TTE_READ;
            // Ignore first record (title)  blank lines
           for (n=0, token = _tcstok(szRecord, seps); token != NULL; 
                token = _tcstok(NULL, seps), n++)
           {
				// Dynamically allocated vector begins with 0 elements.
				switch(n)
				{
				case 0:
					tr.iLevel = CalculateIndentLevel(token, '.');
					break;
				case 1:
					tr.str = token;
					vtr.push_back(tr);
					break;
				}
           }
        }
		wTotalNbItems = vtr.size();
		if (wTotalNbItems == 0)
			throw TTE_INVALID_FILE;
		if (!tt.AllocateTree(wTotalNbItems))
			throw TTE_MEMORY;
		for (n = 0, iMaxLevel = 0; n < wTotalNbItems; n++)
			iMaxLevel = max(vtr[n].iLevel, iMaxLevel);
		piLastAtLevel = new int[iMaxLevel + 1];
		if (piLastAtLevel == NULL)
			throw TTE_MEMORY;

		tt.m_wTotalNbItems = wTotalNbItems;
		for (n = 0, piLastAtLevel[0] = 0; n < wTotalNbItems; n++)
		{
			//Status Bar
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, n*100/wTotalNbItems);

			j = vtr[n].iLevel;
			tt.m_pnt[piLastAtLevel[j - 1]].wNbItems++;				
			piLastAtLevel[j] = n + 1;
            pnt = &tt.m_pnt[n + 1];
			
            pnt->wBufSize = vtr[n].str.GetLength();
            pnt->buf = new TCHAR[pnt->wBufSize + 1];
            if (pnt->buf == NULL)
                throw TTE_MEMORY;
            if (pnt->wBufSize > 0)
			    _tcscpy(pnt->buf, (LPCTSTR)vtr[n].str);
            else
                *pnt->buf = 0;

		
		
		}

    }
    catch(TREE_TYPE_ERROR fe)
    {
		switch(fe)
		{
		case TTE_EMPTY_FILE:
            str.Format(_T("Input tree file %s is empty"), m_pted->m_strFileNamePath);
			break;
		case TTE_MEMORY:
			str.Format(_T("Out of memory"));
			break;
		case TTE_READ:
		    str.Format(_T("Cannot read from IDT file %s: %s"), pszFileName,  strerror(errno));
			break;
		case TTE_CLOSE:
		    str.Format(_T("Cannot close input IDT file %s: %s"), pszFileName,  strerror(errno));
			break;
		case TTE_INVALID_FILE:
			str.Format(_T("Input tree file: %s is invalid or empty"), pszFileName);
			break;
		case TTE_OPEN:
		    str.Format(_T("Cannot open input IDT file %s: %s"), pszFileName,  strerror(errno));
			break;
		}
	   //AfxMessageBox(str);
        rc = false;
    }
	if (fp != NULL)
	{
		fclose(fp);
		if (feof(fp))
			throw TTE_CLOSE;
	}
	if (piLastAtLevel != NULL)
		delete [] piLastAtLevel;

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	return rc;
}

/**************************************************************************************
	Load tree from a CSV file.
	If the tree was successfully read, a CTreeType structure is allocated, containing
	the tree.
	return true if successful
**************************************************************************************/
BOOL CEditTreeCtrl::LoadCsvTreeFromFile(const TCHAR *pszFileName, CTreeType &tt)
{
    
	FILE *fp;
    TREE_RECORD_VECTOR vtr;
    TREE_RECORD tr;
	TCHAR szRecord[MAX_ASCII_RECORD], *p;
	int iMaxLevel = -1;
	CString str;
	int rc = true;

    try
    {
	    fp = _tfopen(pszFileName, _T("rt"));
	    if (fp == NULL)
		    throw TTE_OPEN;
        for (;;) 
        {
	        p = _fgetts(szRecord, MAX_ASCII_RECORD, fp);
    	    if (p == NULL && feof(fp))
                break;
	        if (ferror(fp))
				throw TTE_READ;

			p = _tcschr(szRecord, '\n');
			if (p != NULL)
				*p = 0;
			if (*szRecord == 0) // Empty lines are ignored
				continue;
			tr.iLevel = _tcsspn(szRecord, m_pted->m_szDelimiter) + 1;
			ValidCsvRecord(szRecord, iMaxLevel, m_pted->m_szDelimiter, tr.iLevel);
  		   // Dynamically allocated vector begins with 0 elements.
			tr.str = szRecord;
			vtr.push_back(tr);
        }
		rc = LoadCsvTreeFromMemory(vtr, tt, iMaxLevel, FF_CSV_TYPE);
    }
    catch(TREE_TYPE_ERROR fe)
    {
		switch(fe)
		{
		case TTE_READ:
		    str.Format(_T("Cannot read from CSV file %s: %s"), pszFileName,  strerror(errno));
			break;
		case TTE_CLOSE:
		    str.Format(_T("Cannot close input CSV file %s: %s"), pszFileName,  strerror(errno));
			break;
		case TTE_INVALID_FILE:
			str.Format(_T("Input CSV file: %s is invalid"), pszFileName);
			break;
		case TTE_INVALID_CSV_FILE:
			str.Format(_T("Invalid CSV File %s"), m_pted->m_strFileNamePath);
			break;
		case TTE_OPEN:
		    str.Format(_T("Cannot open input CSV file %s: %s"), pszFileName,  strerror(errno));
			break;
		}
	   //AfxMessageBox(str);
        rc = false;
    }
	if (fp != NULL)
	{
		fclose(fp);
		if (feof(fp))
			throw TTE_CLOSE;
	}

	return rc;
}

// Called when a tree was pasted from the Clipboard (When the user presses SHIFT+INS)
// We do the same work that is done when a file is opened (Warning if the current file 
// has been modified, deleting all items, copy from the clipboard to the CTreeType structure,
// and finally loading this structure to the Tree Control.

BOOL CEditTreeCtrl::PasteEntireTreeFromCliboard(CTreeType &tt)
{
	CString fromClipboard;
    TCHAR seps[] = _T("\r\n");
    TCHAR *token;
    TREE_RECORD_VECTOR vtr;
    TREE_RECORD tr;
	int iMaxLevel = -1;
	int n;

	if (!m_pted->SaveModified()) // When loading other types, this function is called in
		return false;			 // void CTreeEditorDoc::OnFileOpen().	
	DeleteAllItems();	// When loading other types, this function is called in
						// void CTreeEditorView::OnUpdate()

	GetFromClipboard(fromClipboard);
    try
    {
       for (n=0, token = _tcstok((TCHAR *)(LPCTSTR)fromClipboard, seps); token != NULL; 
                token = _tcstok(NULL, seps), n++)
        {
			tr.iLevel = _tcsspn(token, _T("\t")) + 1;
			ValidCsvRecord(token, iMaxLevel, _T("\t"), tr.iLevel);
  		   // Dynamically allocated vector begins with 0 elements.
			tr.str = token;
			vtr.push_back(tr);
        }
		tt.m_wTotalNbItems = 0;
		tt.m_pnt = NULL;
		LoadCsvTreeFromMemory(vtr, tt, iMaxLevel, FF_CLIPBOARD_TYPE);
    }
    catch(TREE_TYPE_ERROR)
    {
//		We don't give display an error when the clipboard is empty, or doesn't
//		a valid tree, but we do retun false to handle this case correctly.
		return false;			
    }
	if (tt.m_wTotalNbItems == 0 || tt.m_pnt == NULL)
		return false;
	return true;
}

/**************************************************************************************
	Loads a tree from a CTreeType structure to the Tree Control
**************************************************************************************/

BOOL CEditTreeCtrl::LoadTreeDataR(CTreeType &tt, HTREEITEM hti, 
						OUTSIDE_PARAM op /* = OP_NONE */)
{
    SetRedraw(false); // To speed up and avoid flickering
	if (!LoadTreeData(tt, hti, op))
		return false;
	RestoreStates(tt); // Restores the Expand/Item states as it was in the CTreeType structure
    SetRedraw(true); 
	return true;
}

// Restores the Expand/Item states as it was in the CTreeType structure
void CEditTreeCtrl::RestoreStates(CTreeType &tt)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Restoring original states..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	
	int iCount;

	for (iCount = 1; iCount <= tt.m_wTotalNbItems; iCount++)
	{
		ExpandM(tt.m_pnt[iCount].hti, 
			tt.m_pnt[iCount].uState & TVIS_EXPANDED ? TVE_EXPAND :TVE_COLLAPSE);
		
		//Status Bar
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iCount*100/tt.m_wTotalNbItems);
			
	
	}

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);

}

BOOL CEditTreeCtrl::LoadTreeData(CTreeType &tt, HTREEITEM hti, OUTSIDE_PARAM op /* = OP_NONE */)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	
	

	int iCount;
	WORD wCurrentNode;
    HTREEITEM htiSon;
    NODE_TYPE *pnt;
	static HTREEITEM htiSave;
	static wTotalAllocatedtems = 0;
	static rc = true;

			
    // op indicates if the function was called recursively (OP_NONE)
    // or from the outside (OP_ENTIRE_TREE or OP_SUBTREE)
    if (op != OP_NONE)
	{
		wTotalAllocatedtems = tt.m_wTotalNbItems;
        tt.m_wTotalNbItems = 0;
	}
    wCurrentNode = tt.m_wTotalNbItems;

//	tt.m_wTotalNbItems contains the number of items currently loaded. It is initialized 
//  to zero. 
//  At the end of the recursive function, if all run fine, it contains 
//  the total number of items in the tree.

	for (iCount = 0; iCount < tt.m_pnt[wCurrentNode].wNbItems; iCount++)
	{
       		
		//Status Bar
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iCount*100/tt.m_pnt[wCurrentNode].wNbItems);
		//pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		
		if (op == OP_SUBTREE && wTotalAllocatedtems == tt.m_wTotalNbItems)
            return true;
		tt.m_wTotalNbItems++;

		// Ensure, we won't use unallocated space even if the data file contains
		// corrupted data.
		if (tt.m_wTotalNbItems > wTotalAllocatedtems)
		{
			tt.m_wTotalNbItems = wTotalAllocatedtems;
			rc = false;
			return rc;
		}
		pnt = &tt.m_pnt[tt.m_wTotalNbItems];
		htiSon = InsertItemAndSetImage(pnt->buf, hti);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, pnt->buf, RGB(0,0,0), TRUE);
        pnt->hti = htiSon;
		rc = LoadTreeData(tt, htiSon);
		if (!rc) // If an error occurs return from all levels of recursion.
			return false;
	}

		
		
	return true;
}

/***********************************************************************************
* Save Functions
***********************************************************************************/

//	1) Calls SaveTreeData() to transfer the tree from the Tree Control to a CTreeType 
//	   structure
//	2) Saves a tree:
//		- From a CTreeType structure to a TRE file 
//		- From a CTreeType structure to an IDT file 
//		- From a CTreeType structure to a CSV file 
//		- From a CTreeType structure to the Clipboard

void CEditTreeCtrl::OnSaveEntireTree(FILE_FORMAT ff, CTreeType &tt)
{
/************************************************************************************
    Ensure tt is always allocated and deallocated correctly:
*************************************************************************************
        1) This function allocates a CTreeType.
        2) The CTreeType is used to save data from the TreeControl. This is done
           in SaveTreeData()
        3) At the end of this function, the CTreeType is not neeeded anymore and
           is deallocated.
************************************************************************************/
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	//pMainFrame->m_wndStatusBar.SetPaneInfo( 1, nID, nStyle, 100);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("Saving tree data..."));
	pMainFrame->m_wndOutputTabView.UpdateWindow();
	

    int iCount;
    CString str;
	CPerfTimer t;
	
	BeginWaitCursor(); // display the hourglass cursor
	UpdateWindow();
	t.Start();

	try
	{
		iCount = GetCount();
		if (iCount == 0)
			return;
		if (!tt.AllocateTree(iCount))
			throw TTE_MEMORY;
		if (!SaveTreeData(tt, GetRootItem(), OP_ENTIRE_TREE))
			throw TTE_MEMORY;
		if (tt.m_wTotalNbItems != iCount)
			throw TTE_INVALID_FILE;
		switch(ff)
		{
		case FF_TREE_TYPE:
			SaveTreeToFile(m_pted->m_strFileNamePath, tt);
			break;
		case FF_PROJ_TYPE:
			SaveIndentTreeToFile(m_pted->m_strFileNamePath, tt);
			break;
        case FF_INDENT_TYPE:
		    SaveIndentTreeToFile(m_pted->m_strFileNamePath, tt);
			break;
		case FF_CSV_TYPE:
			SaveCsvTreeToFile(m_pted->m_strFileNamePath, tt);
			break;
		case FF_CLIPBOARD_TYPE:
			SaveCsvTabTreeToClipboard(tt);
			break;
		}
		if (ff != FF_CLIPBOARD_TYPE)
			m_pted->SetModifiedFlag(false);
	}
	catch(TREE_TYPE_ERROR fe)
	{
		switch(fe)
		{
		case TTE_MEMORY:
			str = _T("Out of memory");
			break;
		case TTE_INVALID_FILE:
			str.Format(_T("Nb of items found(%d) is different from GetCount(%d)"),
				tt.m_wTotalNbItems, iCount);
			break;
		case TTE_OPEN:
            str.Format(_T("Cannot open output file %s: %s"), m_pted->m_strFileNamePath,  strerror(errno));
			break;
		case TTE_WRITE:
    		str.Format(_T("Cannot write to file %s: %s"), m_pted->m_strFileNamePath,  strerror(errno));
			break;
        case TTE_CLOSE:
    		str.Format(_T("Cannot close output file %s: %s"), m_pted->m_strFileNamePath,  strerror(errno));
			break;
		}
	    //AfxMessageBox(str);
	}
    tt.DeAllocateTree();

	pMainFrame->StopTimer(t, _T("Saving tree data elapsed seconds ... "));
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	pMainFrame->m_wndOutputTabView.AddMsg(_T("Process finished"));
	

}

/**************************************************************************************
	Save a tree from the Tree Control to a CTreeType structure.
**************************************************************************************/
BOOL CEditTreeCtrl::SaveTreeData(CTreeType &tt, HTREEITEM hti, OUTSIDE_PARAM op /* = OP_NONE */)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	//pMainFrame->m_wndStatusBar.SetPaneInfo( 1, nID, nStyle, 100);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	
	
		
	CString str;
	WORD wCurrentNode = 0;
	NODE_TYPE *pnt;
	int rc = true;
	int iCount = CountSubtree(GetRootItem(), OP_ENTIRE_TREE);
	
	if (op != OP_NONE)
	{
	    tt.m_wTotalNbItems = 0;
		tt.m_pnt[0].hti = 0;
	}
	else
	{
		str = GetItemText(hti);
		if (tt.m_pnt != NULL)
		{
			tt.m_wTotalNbItems++;
			pnt = &tt.m_pnt[tt.m_wTotalNbItems];
            pnt->wBufSize = _tcslen(str);
            pnt->hti = hti;
            pnt->buf = new TCHAR[pnt->wBufSize + 1];
			
            if (pnt->buf == NULL)
                return false;
			_tcscpy(pnt->buf, str);
			pnt->uState = GetItemState(hti, TVIF_STATE);
			wCurrentNode = tt.m_wTotalNbItems;
			tt.m_pnt[wCurrentNode].wNbItems = 0;
		}
		hti = GetChildItem(hti); 
	}

	
    while(hti != NULL)
	{
		
		//Status Bar
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, tt.m_pnt[wCurrentNode].wNbItems*100/iCount);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, GetItemText(hti), RGB(0,0,0), TRUE);
		
		tt.m_pnt[wCurrentNode].wNbItems++;
        SaveTreeData(tt, hti);
		if (!rc) // If an error occurs return from all levels of recursion.
			return false;
		if (op == OP_SUBTREE)
			return true;
		else
			hti = GetNextSiblingItem(hti);
	}

	//pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	//pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finish"), RGB(0,0,0), TRUE);	
	return true;
}

// Save the file from a CTreeType structure to a TRE file.
void CEditTreeCtrl::SaveTreeToFile(const TCHAR *pszFileName, CTreeType &tt)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Saving tree data..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);
	
	
	FILE *fp;
    int iCount;
    CString str;
    NODE_TYPE *pnt;

	fp = _tfopen(pszFileName, _T("wb"));
	if (fp == NULL)
        throw TTE_MEMORY;
	fwrite(&tt.m_wTotalNbItems, 1, sizeof(WORD), fp);
	if (feof(fp))
        throw TTE_WRITE;
    for (iCount = 0; iCount <= tt.m_wTotalNbItems; iCount++)
    {
    	
		//Status Bar
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iCount*100/tt.m_wTotalNbItems);

		pnt = &tt.m_pnt[iCount];
    	fwrite(&pnt->wNbItems, 1, sizeof(pnt->wNbItems), fp);
    	if (ferror(fp))
            throw TTE_WRITE;
    	fwrite(&pnt->wBufSize, 1, sizeof(pnt->wBufSize), fp);
	    if (ferror(fp))
            throw TTE_WRITE;
        if (pnt->wBufSize > 0)
        {
    	    fwrite(pnt->buf, pnt->wBufSize, sizeof(TCHAR), fp);
	        if (ferror(fp))
                throw TTE_WRITE;
        }
    	fwrite(&pnt->uState, 1, sizeof(pnt->uState), fp);
	    if (ferror(fp))
            throw TTE_WRITE;
    }
	fclose(fp);
	if (feof(fp))
        throw TTE_CLOSE;

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
}

// Save a tree from a CTreeType structure to an IDT file
BOOL CEditTreeCtrl::SaveIndentTreeToFile(const TCHAR *pszFileName, CTreeType &tt)
{
    
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Saving tree data..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);
	
	FILE *fp;
    CString str;
    BOOL rc = true;
	int iMaxLevel = CalculateMaxLevel(tt), iLevel, iCount, *piCurrentLevels, k;
	int iPreviousLevel = -1;
	TCHAR szRecord[MAX_ASCII_RECORD];

    try
    {
		if (iMaxLevel > MAX_LEVELS)
			throw TTE_MAX_LEVEL;
		piCurrentLevels = new int[iMaxLevel];
		if (piCurrentLevels == NULL)
			throw TTE_MEMORY;
		for (k = 0; k < iMaxLevel; k++)
			piCurrentLevels[k] = 0;

	    fp = _tfopen(pszFileName, _T("wt"));
	    if (fp == NULL)
		    throw TTE_OPEN;
		for (iCount = 1; iCount <= tt.m_wTotalNbItems; iCount++)
		{
			//Status Bar
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iCount*100/tt.m_wTotalNbItems);
			
			*szRecord = 0;
			iLevel = GetLevelTree(tt.m_pnt[iCount].hti);
			if (iLevel < iPreviousLevel)
			{
				for (k=iLevel; k<iMaxLevel; k++)
					piCurrentLevels[k] = 0;
			}
			piCurrentLevels[iLevel - 1]++;
			iPreviousLevel = iLevel;
			for (k=0; k<iLevel; k++)
			{
				str.Format(_T("%d"), piCurrentLevels[k]);
				_tcscat(szRecord, str);
				_tcscat(szRecord, _T("."));
			}
			if (iLevel != 1)
				szRecord[_tcslen(szRecord) - 1] = 0;
			_tcscat(szRecord, _T("\t"));
			_tcscat(szRecord, tt.m_pnt[iCount].buf);
	        _ftprintf(fp, _T("%s\n"), szRecord);
	        if (ferror(fp))
				throw TTE_WRITE;
		}
		fclose(fp);
		if (feof(fp))
			throw TTE_CLOSE;
    }
    catch(TREE_TYPE_ERROR fe)
    {
		switch(fe)
		{
		case TTE_MAX_LEVEL:
            str.Format(_T("Up to %d levels are supported!"), MAX_LEVELS);
			break;
		case TTE_EMPTY_FILE:
            str.Format(_T("Output tree file %s is empty"), m_pted->m_strFileNamePath);
			break;
		case TTE_MEMORY:
			str.Format(_T("Out of memory"));
			break;
		case TTE_WRITE:
		    str.Format(_T("Cannot write to IDT file %s: %s"), pszFileName,  strerror(errno));
			break;
		case TTE_CLOSE:
		    str.Format(_T("Cannot close output IDT file %s: %s"), pszFileName,  strerror(errno));
			break;
		case TTE_INVALID_FILE:
			str.Format(_T("Output IDT file: %s is invalid"), pszFileName);
			break;
		case TTE_OPEN:
		    str.Format(_T("Cannot open output IDT file %s: %s"), pszFileName,  strerror(errno));
			break;
		}
	    //AfxMessageBox(str);
        rc = false;
    }
	if (piCurrentLevels != NULL)
		delete [] piCurrentLevels;

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	return rc;
}

// Save a file from a CTreeType structure to a CSV file.
BOOL CEditTreeCtrl::SaveCsvTreeToFile(const TCHAR *pszFileName, CTreeType &tt)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Saving tree data..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);
	
	
	
	FILE *fp;
    CString str;
    BOOL rc = true;
	int iMaxLevel = CalculateMaxLevel(tt), iLevel, iCount, k;
	TCHAR szRecord[MAX_ASCII_RECORD];

    try
    {
	    fp = _tfopen(pszFileName, _T("wt"));
	    if (fp == NULL)
		    throw TTE_OPEN;
		for (iCount = 1; iCount <= tt.m_wTotalNbItems; iCount++)
		{
			//Status Bar
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iCount*100/tt.m_wTotalNbItems);
			
			
			*szRecord = 0;
			iLevel = GetLevelTree(tt.m_pnt[iCount].hti);
			for (k=1; k<=iMaxLevel; k++)
			{
				if (k == iLevel)
					_tcscat(szRecord, tt.m_pnt[iCount].buf);
				if (k != iMaxLevel)
					_tcscat(szRecord, m_pted->m_szDelimiter);
			}
	        fprintf(fp, "%s\n", szRecord);
	        if (ferror(fp))
				throw TTE_WRITE;
		}
		fclose(fp);
		if (feof(fp))
			throw TTE_CLOSE;
    }
    catch(TREE_TYPE_ERROR fe)
    {
		switch(fe)
		{
		case TTE_EMPTY_FILE:
            str.Format(_T("Output file %s is empty"), m_pted->m_strFileNamePath);
			break;
		case TTE_MEMORY:
			str.Format(_T("Out of memory"));
			break;
		case TTE_WRITE:
		    str.Format(_T("Cannot write to CSV file %s: %s"), pszFileName,  strerror(errno));
			break;
		case TTE_CLOSE:
		    str.Format(_T("Cannot close output CSV file %s: %s"), pszFileName,  strerror(errno));
			break;
		case TTE_INVALID_FILE:
			str.Format(_T("Output CSV file: %s is invalid"), pszFileName);
			break;
		case TTE_OPEN:
		    str.Format(_T("Cannot open output CSV file %s: %s"), pszFileName,  strerror(errno));
			break;
		}
	    //AfxMessageBox(str);
        rc = false;
    }

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	return rc;
}

// Save a tree from a CTreeType structure to the Clipboard.
void CEditTreeCtrl::SaveCsvTabTreeToClipboard(CTreeType &tt)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Saving tree data..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);
	
	int iCount, iLevel;
    CString *pstrData;
	TCHAR szRecord[MAX_ASCII_RECORD];
	int iMaxLevel = CalculateMaxLevel(tt), k;

    pstrData = new CString[tt.m_wTotalNbItems];
    if (pstrData == NULL)
		throw TTE_MEMORY;
	for (iCount = 1; iCount <= tt.m_wTotalNbItems; iCount++)
	{
		//Status Bar
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iCount*100/tt.m_wTotalNbItems);
			
		
		*szRecord = 0;
		iLevel = GetLevelTree(tt.m_pnt[iCount].hti);
		for (k=1; k<=iMaxLevel; k++)
		{
			if (k == iLevel)
				_tcscat(szRecord, tt.m_pnt[iCount].buf);
			if (k != iMaxLevel)
				_tcscat(szRecord, _T("\t"));
		}
		pstrData[iCount - 1] = szRecord;
	}
    Add2Clipboard(pstrData, tt.m_wTotalNbItems);
    if (pstrData != NULL)
		delete [] pstrData;

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
}

/***********************************************************************************
* Sort Functions
***********************************************************************************/

// Called when the user presses Ctrl+T 
void CEditTreeCtrl::OnSortSubtreeAlphabetic() 
{
    m_SortType = ST_ALPHABETIC;
	SortSubtree();
}

// Called when the user presses Ctrl+Shift+T 
void CEditTreeCtrl::OnSortSubtreeNumeric() 
{
    m_SortType = ST_NUMERIC;
	SortSubtree();
}

// Sort a Subtree using a callback function. (Calling SortChildren(), which is
// the non-callback function for sorting siblings is the same as calling
// SortChildrenCB with m_SortType = ST_ALPHABETIC)

void CEditTreeCtrl::SortSubtree() 
{
    HTREEITEM hti;
    TVSORTCB tvscb;
    BOOL bRc;

	hti = GetSelectedItem();
    if (hti != NULL)
    {
        tvscb.hParent = hti;
        tvscb.lpfnCompare = CompareFunc;
        tvscb.lParam = (LPARAM)this;
        bRc = SortChildrenCB(&tvscb);
		m_pted->SetModifiedFlag();
	}
}

// Callback function for SortChildrenCB()
int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CString str1, str2;
    int i1, i2;
    CEditTreeCtrl *petc= (CEditTreeCtrl *)lParamSort;

	str1 = petc->GetItemText((HTREEITEM)lParam1);
	str2 = petc->GetItemText((HTREEITEM)lParam2);
    switch(petc->m_SortType)
    {
    case ST_NUMERIC:
        i1 = _ttoi((LPCTSTR)str1);
        i2 = _ttoi((LPCTSTR)str2);
        if (i1 > i2)
            return 1;
        if (i2 > i1)
            return -1;
        return 0;
    case ST_ALPHABETIC:
        if (str1 > str2)
            return 1;
        if (str2 > str1)
            return -1;
        return 0;
    default:
        return 0;
    }
}

/***********************************************************************************
* Utility Functions
***********************************************************************************/

// Called by LoadTreeFromDirectory() to search a directory
void CEditTreeCtrl::FindPath(const TCHAR *lpszPath, CSTRING_VECTOR &cv, BOOL bCalledFromOutside /* = false */)
{
	CFileFind ff;
	BOOL bRC;
	static CString str;

	for (bRC = ff.FindFile(lpszPath); bRC;)
	{
	    bRC = ff.FindNextFile();
		str = ff.GetFilePath();
		if (ff.IsDirectory() && !ff.IsDots() && !ff.IsHidden()) 
		{
			cv.push_back(str);
			SetCurrentDirectory(str);
			FindPath(NULL, cv);
            if (!bCalledFromOutside)
		        SetCurrentDirectory(_T(".."));
		}
	}
}

// Checks if a CSV record is valid
BOOL CEditTreeCtrl::ValidCsvRecord(TCHAR *psz, int &iMaxLevel, TCHAR *pszDelimiter, int iLevel)
{
	int j;
	const TCHAR *p, *token;
	TCHAR szRecord[MAX_ASCII_RECORD];

//	If the tree is valid, the level can:
//		- decrease to any level down to 1 (the lowest)
//		- stay the same
//		- increase by 1

	static iPreviousLevel;

	if (iMaxLevel == -1) // First time, the function is called for a given tree
		iPreviousLevel = 0;
	if (iPreviousLevel + 1 < iLevel)
		throw TTE_INVALID_CSV_FILE;
	iPreviousLevel = iLevel;

	for (j=0, p=psz;; j++, p++)
	{
		token = p;
		p = _tcschr(p, *pszDelimiter);
		if (p == NULL)
		{
			if (*token != 0)
				_tcscpy(szRecord, token);
			break;
		}
		if (*token != *pszDelimiter)
		{
			_tcscpy(szRecord, token);
			szRecord[p - token] = 0;
		}
	}
	if (j + 1 > iMaxLevel)
		iMaxLevel = j + 1;
    _tcscpy(psz, szRecord);
	return true;
}

int CEditTreeCtrl::CalculateIndentLevel(TCHAR *psz, TCHAR ch)
{
//	The level is the number of tokens separeted by the 'ch' character
//	(independently of their value)
//	Examples:
//		CalculateIndentLevel("1.", '.')		= 1
//		CalculateIndentLevel("3.4", '.')		= 2
//		CalculateIndentLevel("13.24.5.2", '.')	= 4

// This function is called from LoadTreeFromDirectory() with ch == '\\'
//					   and from LoadIndentTreeFromFile() with ch == '.'
	int k, n;

	for (k = 0, n = 1; psz[k] != 0; k++)
	{
		if (psz[k] == ch && psz[k+1] != 0)
			n++;
	}
	return n;
}

// Return true if the second parameter is an ancester of the first one.
BOOL CEditTreeCtrl::IsChildNodeOf(HTREEITEM hitemChild, HTREEITEM hitemSuspectedParent)
{
	do
	{
		if (hitemChild == hitemSuspectedParent)
			break;
	}
	while ((hitemChild = GetParentItem(hitemChild)) != NULL);

	return (hitemChild != NULL);
}

// Called when the user presses Ctrl+Shift+N
void CEditTreeCtrl::OnCountEntireTree() 
{
	int iCount;
	iCount = GetCount();	
	// An alternative is: iCount = CountSubtree(GetRootItem(), OP_ENTIRE_TREE);
	/*
	CString str;
	str.Format(_T("Number of item in Entire Tree: %d"), iCount);
	AfxMessageBox(str);
	*/
}

// Called when the user presses Ctrl+N
void CEditTreeCtrl::OnCountSubtree() 
{
	int iCount;
	HTREEITEM hti;

	hti = GetSelectedItem();
	iCount = CountSubtree(hti, OP_SUBTREE);
	/*
	CString str;
	str.Format(_T("Number of item in Subtree: %d"), iCount);
	AfxMessageBox(str);
	*/
}

// Called when the user presses Ctrl+Shift+N Count entire tree
int CEditTreeCtrl::CountSubtree(HTREEITEM hti, OUTSIDE_PARAM op /* = OP_NONE */)
{
	static int iCount;
	if (op != OP_NONE)
		iCount = 0;
	else
	{
		iCount++;
		hti = GetChildItem(hti); 
	}

    while(hti != NULL)
	{
        CountSubtree(hti);
		if (op == OP_SUBTREE)
			return iCount;
		else
		{
			hti = GetNextSiblingItem(hti);
		}
	}
	return iCount;
}

// Called when the user presses Ctrl+L
void CEditTreeCtrl::OnCalculateLevel()
{
    int iLevel;
	HTREEITEM hti;
    

    hti = GetSelectedItem();
    if (hti != NULL)
    {
        iLevel = GetLevelTree(hti);
		/*
		CString str;
        str.Format(_T("Item Level: %d"), iLevel);
        AfxMessageBox(str);
		*/
    }
}

// Calculates the level from an item (Level = 1, 2, ... = distance from the root)
int CEditTreeCtrl::GetLevelTree(HTREEITEM hti)
{
    int iCount;
    {
        for (iCount = 0; hti != NULL; iCount++)
            hti = GetParentItem(hti);
    }
    return iCount;
}

// Calculates the maximum level in the tree
int CEditTreeCtrl::CalculateMaxLevel(CTreeType &tt)
{
	int iCount, iMaxLevel = 0;

	for (iCount = 1; iCount <= tt.m_wTotalNbItems; iCount++)
		iMaxLevel = max(iMaxLevel, GetLevelTree(tt.m_pnt[iCount].hti));
	return iMaxLevel;
}

HTREEITEM CEditTreeCtrl::OnFindItem(LPCTSTR strItem)
{
    HTREEITEM hItem  = NULL;

	hItem = GetItemByName( NULL, strItem);
	
    if (hItem != NULL)
        SelectItem(hItem);
	
	
	return hItem;
}


HTREEITEM CEditTreeCtrl::OnFindDlg(LPCTSTR strItem)
{
	HTREEITEM hItem  = NULL;
	HTREEITEM hNextItem = NULL;
	//AfxMessageBox(strItem);
	//AfxMessageBox(m_sItemFound);
	CString a = strItem;
	CString b = m_sItemFound;
		
	if( a == b )
	{
			/*
			//Go to next child item
			HTREEITEM hChildItem = (HTREEITEM)SendMessage(TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)m_hItemFound);
			hNextItem = hChildItem;
			hItem = GetItemByName( hNextItem, strItem);
			*/

			// Go to next sibling item.
			HTREEITEM hSiblingItem = (HTREEITEM)SendMessage(TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)m_hItemFound);
			hNextItem = hSiblingItem;
			hItem = GetItemByName( hNextItem, strItem);
		
	}
	else
	{
		hItem = GetItemByName( NULL, strItem);
		//AfxMessageBox(_T("No"));
	}

    if (hItem != NULL)
        SelectItem(hItem);
	
	
	return hItem;

}


/***********************************************************************************
* Wrapper to the basic Tree Control member functions.
***********************************************************************************/

// Wrapper to the InsertItem function
HTREEITEM CEditTreeCtrl::InsertItemAndSetImage(LPCTSTR lpszItem, 
	HTREEITEM hParent /*= TVI_ROOT*/, HTREEITEM hInsertAfter /*= TVI_LAST*/)
{
	
	HTREEITEM htiSon = InsertItem(lpszItem, hParent, hInsertAfter);
	SetItemImage(htiSon, 0, 1);
	SetItemData(htiSon, (DWORD)htiSon);
	m_pted->SetModifiedFlag();
	return htiSon;
}

// Wrapper to the SelectItem function
BOOL CEditTreeCtrl::SelectVisibleItem(HTREEITEM hti)
{
    EnsureVisible(hti);
    return SelectItem(hti);
}

HTREEITEM CEditTreeCtrl::GetItemByName(HTREEITEM hItem, LPCTSTR szItemName)
{
    // If hItem is NULL, start search from root item.
    if (hItem == NULL)
        hItem = (HTREEITEM)SendMessage(TVM_GETNEXTITEM, TVGN_ROOT, 0);
    
	while (hItem != NULL)
    {
        TCHAR szBuffer[MAXTEXTLEN+1];
        TV_ITEM item;

        item.hItem = hItem;
        item.mask = TVIF_TEXT | TVIF_CHILDREN;
        item.pszText = szBuffer;
        item.cchTextMax = MAXTEXTLEN;
        
		SendMessage(TVM_GETITEM, 0, (LPARAM)&item);
        
		// Did we find it?
        if (lstrcmp(szBuffer, szItemName) == 0)
            return hItem;

        // Check whether we have child items.
        if (item.cChildren)
        {
            // Recursively traverse child items.
            HTREEITEM hItemFound, hItemChild;

            hItemChild = (HTREEITEM)SendMessage( TVM_GETNEXTITEM, TVGN_CHILD, (LPARAM)hItem);
            hItemFound = GetItemByName(hItemChild, szItemName);

            // Did we find it?
            if (hItemFound != NULL )
			{
				m_sItemFound = szItemName;
			    m_hItemFound = hItemFound;
                return hItemFound;
			}
        }

        // Go to next sibling item.
        hItem = (HTREEITEM)SendMessage(TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem);
    }

    // Not found.
    return NULL;
}

BOOL CEditTreeCtrl::InitializeImageList()
{
	CBitmap bmap;
	BITMAP bm;

	bmap.LoadBitmap(IDB_TREE);
	bmap.GetBitmap(&bm);
	if (m_pimagelist != NULL)
	    delete m_pimagelist;
	m_pimagelist = new CImageList();
	if (m_pimagelist == NULL)
	{
		AfxMessageBox(_T("Cannot initialize Image List: Not enough memory!"));
		return false;
	}
	m_pimagelist->Create(bm.bmWidth / 3, bm.bmHeight, ILC_COLORDDB, 2, 0);
	m_pimagelist->Add(&bmap, (COLORREF)0);
	bmap.DeleteObject();
	SetImageList(m_pimagelist, TVSIL_NORMAL);

	return true;
}

// Wrapper to the Expand function
BOOL CEditTreeCtrl::ExpandM(HTREEITEM hItem, UINT nCode)
{
	BOOL b;

    b = Expand(hItem, nCode);	// Since we save the expand/collapse state into the file,
	if (b)						// we consider this as a modification;
		m_pted->SetModifiedFlag(); 
	return b;
}

// Wrapper to the DeleteItem function
BOOL CEditTreeCtrl::DeleteItemM(HTREEITEM hItem)
{
	BOOL b;

	b = DeleteItem(hItem);
	if (b)
		m_pted->SetModifiedFlag();  
	return b;
}

// Notification handler called when the user causes an Expand/Collapse
void CEditTreeCtrl::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	m_pted->SetModifiedFlag();	// We consider this as a modification, since we save 
	*pResult = 0;				// the expand/collapse state into the file,
}

// Called by these functions:
//	- PasteEntireTreeFromCliboard()
//	- LoadTreeFromDirectory()
//	- LoadCsvTreeFromMemory()
//
// Load a CSV file from a vector of struct TREE_RECORD to a CTreeType structure
// iMaxLevel is the maximum level of the tree. 
// ff is a flag to allow special processing according to the file type.
//
// A vector is nothing but an array, whose size can changes at running time. (See
// STL documentation about vectors)

BOOL CEditTreeCtrl::LoadCsvTreeFromMemory(TREE_RECORD_VECTOR &vtr, CTreeType &tt, 
	int iMaxLevel, FILE_FORMAT ff)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading tree data..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	CString str;
    WORD wTotalNbItems = 0;
    BOOL rc = true;
    int n, j;
	int *piLastAtLevel = NULL;
    NODE_TYPE *pnt;

	try
	{
		wTotalNbItems = vtr.size();
		if (wTotalNbItems == 0)
			throw TTE_EMPTY_FILE;
		if (!tt.AllocateTree(wTotalNbItems))
			throw TTE_MEMORY;
		piLastAtLevel = new int[iMaxLevel + 1];
		if (piLastAtLevel == NULL)
			throw TTE_MEMORY;  

		tt.m_wTotalNbItems = wTotalNbItems;
		for (n = 0, piLastAtLevel[0] = 0; n < wTotalNbItems; n++)
		{
			j = vtr[n].iLevel;
			tt.m_pnt[piLastAtLevel[j - 1]].wNbItems++;				
			piLastAtLevel[j] = n + 1;
            pnt = &tt.m_pnt[n + 1];
            pnt->wBufSize = vtr[n].str.GetLength();
            pnt->buf = new TCHAR[pnt->wBufSize + 1];
            if (pnt->buf == NULL)
                throw TTE_MEMORY;
            if (pnt->wBufSize > 0)
			    _tcscpy(pnt->buf, (LPCTSTR)vtr[n].str);
            else
                *pnt->buf = 0;
			//Status Bar
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, n*100/wTotalNbItems);
		}
    }
    catch(TREE_TYPE_ERROR fe)
    {
		if (ff != FF_CLIPBOARD_TYPE)
		{
			// If Pasting from a clipboard, which contains invalid data, do nothing
			// but don't display any error message.
			switch(fe)
			{
			case TTE_EMPTY_FILE:
				if (ff == FF_DIRECTORY_TYPE)
					str.Format(_T("Directory %s is empty"), m_pted->m_strFileNamePath);
				else
					str.Format(_T("Input CSV file %s is empty"), m_pted->m_strFileNamePath);
				break;
			case TTE_MEMORY:
				str.Format(_T("Out of memory"));
				break;
			}
			//AfxMessageBox(str);
		}
        rc = false;
    }
	if (piLastAtLevel != NULL)
		delete [] piLastAtLevel;

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	return rc;
}

//	When LoadTreeFromDirectory() is called to load a directory, such as:
//	d:\subdir1\...\subdirN, a CSTRING_VECTOR is generated containing all the directories
//	founds, whose path begin by: D:\subdir1\...\subdirN. 
//
//	The following function is used to generate the first records from the root, i.e:
//		- (d:\)
//		- subdir1
//		- ...
//		- subdirN
//
void CEditTreeCtrl::GenerateFirstDirectoryRecords(const TCHAR *pszFirstRecord,
	CSTRING_VECTOR &cvFirstDirRecords)
{
	int k;
	BOOL bFirstTime = true;
	//char szRecord[MAX_ASCII_RECORD];
	//char str[MAX_ASCII_RECORD];
	TCHAR  szRecord[MAX_ASCII_RECORD];
	TCHAR str[MAX_ASCII_RECORD];

	for (k = 0; pszFirstRecord[k] != 0; k++)
	{
		if (pszFirstRecord[k] == '\\')
		{
			memcpy(szRecord, pszFirstRecord, sizeof(k));
			szRecord[k] = 0;
			if (bFirstTime)
			{
				bFirstTime = false;
				_tcscpy(str, szRecord);
				//strcpy(str, szRecord);
				//*str = toupper(*str);
				//sprintf(szRecord, _T("(%s)"), str);
				*str = towupper(*str);
				_stprintf(szRecord, _T("(%s)"), str);
			}
			cvFirstDirRecords.push_back(szRecord);
		}
	}
}

// Called at the end of the process of loading a directory, to collapse the tree and
// to sort the items as Explorer does.
void CEditTreeCtrl::pfCollapseAndSort(HTREEITEM hti, void *)
{
    ExpandM(hti, TVE_COLLAPSE);
	SortChildren(hti);
}

/**************************************************************************************
*	Name:				Add2Clipboard()	 
*	Type:				void
*	Parameter List:		pstrData    - array of strings to copy to the clipboard.
*                       iSize       - size of array
*	Description:		Copy strings to the clipboard.
*	Return value:		none.
/****************************************************************************************/
void CEditTreeCtrl::Add2Clipboard(CString *pstrData, int iSize)
{
    int k, iTotalSize;

    if (OpenClipboard())
    {
	    EmptyClipboard();
	    HGLOBAL hClipboardData;
        for (k = 0, iTotalSize = 0; k < iSize; k++)
            iTotalSize += pstrData[k].GetLength() + 2;
	    hClipboardData = GlobalAlloc(GMEM_DDESHARE, iTotalSize);

	    TCHAR * pchData;
	    pchData = (TCHAR*)GlobalLock(hClipboardData);
		      
        _tcscpy(pchData, LPCTSTR(pstrData[0]));
        for (k = 1; k < iSize; k++)
        {
	        _tcscat(pchData, _T("\r\n"));
	        _tcscat(pchData, LPCTSTR(pstrData[k]));
        }
	    GlobalUnlock(hClipboardData);
	    SetClipboardData(CF_TEXT,hClipboardData);
	    CloseClipboard();
    }
}

// Get the Cipboard content into a CString
void CEditTreeCtrl::GetFromClipboard(CString &fromClipboard)
{
    HGLOBAL hClipboardData;
	char *buffer;

    if (OpenClipboard())
    {
	    hClipboardData = GetClipboardData(CF_TEXT);
	    buffer = (char*)GlobalLock(hClipboardData);
		fromClipboard = buffer;
	    GlobalUnlock(hClipboardData);
	    CloseClipboard();
    }
}

// Clearance tasks when the Tree Control is destroyed.
void CEditTreeCtrl::OnDestroy() 
{
	m_pimagelist = GetImageList(TVSIL_NORMAL);
	m_pimagelist->DeleteImageList();
	if (m_pimagelist != NULL)
	{
		
		delete m_pimagelist;
		m_pimagelist = NULL;
	}
}




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


/////////////////////////////////////////////////////////////////////////////
// CVerticalTree

void CEditTreeCtrl::SetCustomDrawn(BOOL c)
{
	m_bCustomDrawn = c;
}

BOOL CEditTreeCtrl::GetCustomDrawn()
{
	return m_bCustomDrawn;
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CVerticalTree 

void CEditTreeCtrl::OnPaint() 
{
	if (m_bCustomDrawn)
	{
		CPaintDC dc(this);
		//Double Buffering...
		CDC dc_backbuffer;
		CBitmap bb_image;
		

		//Calculate scoll position and control dimensions
		UpdateDimensions();

		//Create device context for the backbuffer
		dc_backbuffer.CreateCompatibleDC(&dc);
		//Create the image we are going to draw in
		bb_image.CreateCompatibleBitmap(&dc, m_Rect.Width(), m_Rect.Height());
		dc_backbuffer.SelectObject(&bb_image);

		//We use the same Font which was configured in the main device context
		
		//dc_backbuffer.SelectObject(GetFont());
		dc_backbuffer.SelectObject(&m_Font);

		
		dc_backbuffer.SetBkMode(TRANSPARENT);

		//General Info
		DWORD style = GetStyle();
		m_bHasButtons = (style & TVS_HASBUTTONS) != 0;
		m_bHasLines = (style & TVS_HASLINES) != 0;

		//Now draw the items...
		m_XMax = 0;
		m_YMax = 0;
		//dc_backbuffer.FillSolidRect(m_Rect, dc_backbuffer.GetBkColor()); 
		dc_backbuffer.FillSolidRect(m_Rect, dc_backbuffer.SetBkColor(m_WindowBkColor));
		int xoffset = 0;
		for (HTREEITEM root = GetRootItem(); root != NULL; root = GetNextItem(root, TVGN_NEXT))
			xoffset = DrawItem(&dc_backbuffer, root, xoffset);

		//Copy the backbuffer to the main device context...
		dc.BitBlt( m_Rect.left, m_Rect.top, m_Rect.Width(), m_Rect.Height(), &dc_backbuffer, 0, 0, SRCCOPY);

		ResetScrollbars();
	}
	else
		CTreeCtrl::OnPaint();
}

BOOL CEditTreeCtrl::OnEraseBkgnd(CDC* pDC) 
{
	if (m_bCustomDrawn)
		return TRUE;
	else
		return CTreeCtrl::OnEraseBkgnd(pDC);
}

void CEditTreeCtrl::UpdateDimensions()
{
	GetClientRect(&m_Rect);
	SCROLLINFO scroll_info;
	if (GetScrollInfo(SB_HORZ, &scroll_info, SIF_POS | SIF_RANGE))
	{
		m_OffsetX = -scroll_info.nPos;
	}
	else
	{
		m_OffsetX = m_Rect.left;
	}
	if (GetScrollInfo(SB_VERT, &scroll_info, SIF_POS | SIF_RANGE))
	{
		if ( scroll_info.nMin == 0 && scroll_info.nMax == 100) 
			scroll_info.nMax = 0;

		m_OffsetY = -scroll_info.nPos;
	}
	else
	{
		m_OffsetY = m_Rect.top;
	}
}


void CEditTreeCtrl::DrawNodeText(CDC *pDC, HTREEITEM item, CString text, int x, int y, int cx, int cy, COLORREF bkcolor,COLORREF txtcolor, HFONT txttype)
{
	pDC->FillSolidRect(x+m_OffsetX, y+m_OffsetY, cx, cy, bkcolor);
	pDC->SetTextColor(txtcolor);
	pDC->TextOut(x+m_OffsetX,y+m_OffsetY,text);
	pDC->SelectObject(&txttype);	
	
	ItemViewport *nvp = GetViewport(item);
	
	nvp->x = x;
	nvp->y = y;
	nvp->cx = cx;
	nvp->cy = cy;

	if (x + cx > m_XMax)
		m_XMax = x + cx;
	if (y + cy > m_YMax)
		m_YMax = y + cy;

}


void CEditTreeCtrl::DrawLeafText(CDC *pDC, HTREEITEM item,  CString text , int x, int y, int cx, int cy, COLORREF bkcolor,COLORREF txtcolor, HFONT txttype)
{
	pDC->FillSolidRect(x+m_OffsetX, y+m_OffsetY, cx, cy, bkcolor);
	pDC->SetTextColor(txtcolor);
	pDC->TextOut(x+m_OffsetX,y+m_OffsetY,text);
	pDC->SelectObject(&txttype);	
	
	ItemViewport *nvp = GetViewport(item);
	
	nvp->x = x;
	nvp->y = y;
	nvp->cx = cx;
	nvp->cy = cy;

	if (x + cx > m_XMax)
		m_XMax = x + cx;
	if (y + cy > m_YMax)
		m_YMax = y + cy;

}

void CEditTreeCtrl::DrawLinkText(CDC *pDC, HTREEITEM item, CString text, int x, int y, int cx, int cy, COLORREF bkcolor,COLORREF txtcolor, HFONT txttype)
{
	pDC->FillSolidRect(x+m_OffsetX, y+m_OffsetY, cx, cy, bkcolor);
	pDC->SetTextColor(txtcolor);
	pDC->TextOut(x+m_OffsetX,y+m_OffsetY,text);
	pDC->SelectObject(&txttype);

	ItemViewport *nvp = GetViewport(item);
	
	nvp->x = x;
	nvp->y = y;
	nvp->cx = cx;
	nvp->cy = cy;

	if (x + cx > m_XMax)
		m_XMax = x + cx;
	if (y + cy > m_YMax)
		m_YMax = y + cy;

}


int CEditTreeCtrl::DrawItem(CDC *pDC, HTREEITEM item, int x, int level)
{
	
	CString name = GetItemText(item);

	CString link_name = _T("");
	CString node_name = _T("");
	CSize text_size = 0;
	
	
	//Separates the nodes text from the link text
	for(int i = 0; i<name.GetLength(); i++)
	{
		if (name[i]== ':')
		{
			link_name = name.Left(i) ;
			node_name = name.Right(name.GetLength() - i -1 );
			break;
		}
		
	}
	
	//Takes the larger text size
	if( node_name != _T("") && link_name != _T(""))
	{
		if ( node_name.GetLength() > link_name.GetLength())
			text_size = pDC->GetTextExtent(node_name);
		else 
			text_size = pDC->GetTextExtent(link_name);

		//Center text 
		int difference = abs(link_name.GetLength() - node_name.GetLength());
		int space = (int)(difference/2);
	
		if( link_name.GetLength() > node_name.GetLength())
		{
			for(int i = 0; i<= space; i++)
				node_name.Insert(i, _T(" "));
		}
		else
		{
			for(int i = 0; i<= space; i++)
				link_name.Insert(i, _T(" "));
		}
	}	
	else
	{
		node_name = name;
		text_size = pDC->GetTextExtent(name);
	}
	
	
	
	
	int state = GetItemState(item, TVIF_STATE);
	bool selected = (state & TVIS_SELECTED) != 0;

	if (ItemHasChildren(item))
	{
		int left = x;
		int right = 0;
		int childcount = 0;

		if (state & TVIS_EXPANDED)
			for (HTREEITEM childitem = GetChildItem(item); childitem != NULL; childitem = GetNextItem(childitem, TVGN_NEXT))
			{
				right = DrawItem(pDC, childitem, x, level + 1);
				x = right;
				childcount++;
			}

		right = right - m_ItemSpaceX;
		int width =  right - left;
		x = left + width / 2 - text_size.cx / 2;

		if (x < left + m_ItemSpaceX)
		   x = left;
		

		int y = level*m_ItemSpaceY;
		
		//Draw the link text a little more higher
		if ( link_name.IsEmpty() == 0 )
			DrawLinkText(pDC, item, link_name, x, level*m_ItemSpaceY - m_LinkNodeSpaceY, text_size.cx, text_size.cy, m_LinkBkColor, m_LinkTextColor, m_LinkFont);
		//Draw the node text
		DrawNodeText(pDC, item, node_name, x, level*m_ItemSpaceY, text_size.cx, text_size.cy, m_NodeBkColor, m_NodeTextColor, m_Font);
	
		
		//Draw lines...
		if (m_bHasLines && (state & TVIS_EXPANDED))
		{
			int xstart = x + text_size.cx / 2;
			int ystart = y + text_size.cy + BUTTON_SIZE;
			CGdiObject *oldPen = pDC->SelectObject(&m_TreeLinePen);
			for (HTREEITEM childitem = GetChildItem(item); childitem != NULL; childitem = GetNextItem(childitem, TVGN_NEXT))
			{
				ItemViewport *current = GetViewport(childitem);
				pDC->MoveTo(xstart+m_OffsetX,ystart+m_OffsetY);
				pDC->LineTo(current->x +m_OffsetX + current->cx / 2 , current->y + m_OffsetY);
								
			}
			pDC->SelectObject(oldPen);
		}

		if (m_bHasButtons)
		{
			pDC->Draw3dRect(x+m_OffsetX+text_size.cx / 2 - BUTTON_SIZE / 2, y+m_OffsetY + text_size.cy, BUTTON_SIZE, BUTTON_SIZE, m_clrTopLeft, m_clrBottomRight);
			pDC->MoveTo(x+m_OffsetX+text_size.cx / 2 - BUTTON_SIZE / 2 + 2, y+m_OffsetY + text_size.cy + BUTTON_SIZE / 2);
			pDC->LineTo(x+m_OffsetX+text_size.cx / 2 + BUTTON_SIZE / 2 - 1, y+m_OffsetY + text_size.cy + BUTTON_SIZE / 2);
			
			if ((state & TVIS_EXPANDED) == 0)
			{
				pDC->MoveTo(x+m_OffsetX+text_size.cx / 2, y+m_OffsetY + text_size.cy + 2);
				pDC->LineTo(x+m_OffsetX+text_size.cx / 2, y+m_OffsetY + text_size.cy + BUTTON_SIZE - 2);
			}
		}
		
	
		
		
		if (right > x + text_size.cx)
		   return right + m_ItemSpaceX;
		else
		   return x + text_size.cx + m_ItemSpaceX;
	}
	else
	{
		//Draw the link name from the leaf a little more higher
		if ( link_name.IsEmpty() == 0 )
			DrawLinkText(pDC, item, link_name, x, level*m_ItemSpaceY -m_LinkNodeSpaceY, text_size.cx, text_size.cy, m_LinkBkColor, m_LinkTextColor, m_LinkFont);
		//Draw the node text from the leaf
		DrawLeafText(pDC, item, node_name, x, level*m_ItemSpaceY, text_size.cx, text_size.cy, m_LeafBkColor, m_LeafTextColor, m_Font);
	
		return x + text_size.cx + m_ItemSpaceX;
	}
	
	
}

void CEditTreeCtrl::SetItemSpaceX(int space)
{
	m_ItemSpaceX = space;
}

int CEditTreeCtrl::GetItemSpaceX()
{
	return m_ItemSpaceX;
}
void CEditTreeCtrl::SetItemSpaceY(int space)
{
	m_ItemSpaceY = space;
}

int CEditTreeCtrl::GetItemSpaceY()
{
	return m_ItemSpaceY;
}

void CEditTreeCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (m_bCustomDrawn)
	{
		int iScrollBarPos = GetScrollPos( SB_HORZ );

		switch( nSBCode )
		{
			case SB_LINEUP:
				iScrollBarPos = max( iScrollBarPos - 1, 0 );
			break;

			case SB_LINEDOWN:
				iScrollBarPos = min( iScrollBarPos + 1, GetScrollLimit( SB_HORZ ) );
			break;

			case SB_PAGEUP:
				iScrollBarPos = max( iScrollBarPos - m_Rect.Width(), 0 );
			break;

			case SB_PAGEDOWN:
				iScrollBarPos = min( iScrollBarPos + m_Rect.Width(), GetScrollLimit( SB_HORZ ) );
			break;

			case SB_THUMBTRACK:
			case SB_THUMBPOSITION:
				iScrollBarPos = nPos;
				break;
		}		

		SetScrollPos( SB_HORZ, iScrollBarPos );
		
		Invalidate();
	}
	else
		CTreeCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}



BOOL CEditTreeCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if (m_bCustomDrawn)
	{
		return FALSE;
	}
	else	
		return CTreeCtrl::OnMouseWheel(nFlags, zDelta, pt);
}

void CEditTreeCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (m_bCustomDrawn)
	{
		int iScrollBarPos = GetScrollPos( SB_VERT );

		switch( nSBCode )
		{
			case SB_LINEUP:
				iScrollBarPos = max( iScrollBarPos - 1, 0 );
			break;

			case SB_LINEDOWN:
				iScrollBarPos = min( iScrollBarPos + 1, GetScrollLimit( SB_VERT ) );
			break;

			case SB_PAGEUP:
				iScrollBarPos = max( iScrollBarPos - m_Rect.Height(), 0 );
			break;

			case SB_PAGEDOWN:
				iScrollBarPos = min( iScrollBarPos + m_Rect.Height(), GetScrollLimit( SB_VERT ) );
			break;

			case SB_THUMBTRACK:
			case SB_THUMBPOSITION:
				iScrollBarPos = nPos;
				break;
		}		

		SetScrollPos( SB_VERT, iScrollBarPos );
		
		Invalidate();
	}
	else
		CTreeCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}




void CEditTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_bCustomDrawn)
	{
	}
	else	
		CTreeCtrl::OnLButtonDown(nFlags, point);
}




HTREEITEM CEditTreeCtrl::InsertItem(LPTVINSERTSTRUCT lpInsertStruct)
{
	HTREEITEM htreeitem = CTreeCtrl::InsertItem(lpInsertStruct);
	//I presume that CTreeCtrl::InsertItem won't create same handles,
	//if the key is in use this will lead to memory leaks...
	m_HTree2VP.insert(HTREE2VPMAP::value_type(htreeitem, new ItemViewport(htreeitem)));
	return htreeitem;
}
HTREEITEM CEditTreeCtrl::InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	
	HTREEITEM htreeitem = CTreeCtrl::InsertItem(nMask, lpszItem, nImage, nSelectedImage, nState, nStateMask, lParam, hParent, hInsertAfter);
	//I presume that CTreeCtrl::InsertItem won't create same handles,
	//if the key is in use this will lead to memory leaks...
	m_HTree2VP.insert(HTREE2VPMAP::value_type(htreeitem, new ItemViewport(htreeitem)));
	return htreeitem;
}
HTREEITEM CEditTreeCtrl::InsertItem(LPCTSTR lpszItem, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	
	HTREEITEM htreeitem = CTreeCtrl::InsertItem(lpszItem, hParent, hInsertAfter);
	//I presume that CTreeCtrl::InsertItem won't create same handles,
	//if the key is in use this will lead to memory leaks...
	m_HTree2VP.insert(HTREE2VPMAP::value_type(htreeitem, new ItemViewport(htreeitem)));
	return htreeitem;
}
HTREEITEM CEditTreeCtrl::InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	HTREEITEM htreeitem = CTreeCtrl::InsertItem(lpszItem, nImage, nSelectedImage, hParent, hInsertAfter);
	//I presume that CTreeCtrl::InsertItem won't create same handles,
	//if the key is in use this will lead to memory leaks...
	m_HTree2VP.insert(HTREE2VPMAP::value_type(htreeitem, new ItemViewport(htreeitem)));
	return htreeitem;
}
BOOL CEditTreeCtrl::DeleteItemV(HTREEITEM hItem)
{
	BOOL ret = CTreeCtrl::DeleteItem(hItem);
	HTREE2VPMAP::iterator it = m_HTree2VP.find(hItem);
	if (it != m_HTree2VP.end())
	{
		delete (*it).second;
		m_HTree2VP.erase(it);
	}
	return ret;
}
BOOL CEditTreeCtrl::DeleteAllItemsV()
{
	DeleteAllViewportItemsV();
	return CTreeCtrl::DeleteAllItems();
}

void CEditTreeCtrl::DeleteAllViewportItemsV()
{
	HTREE2VPMAP::iterator it = m_HTree2VP.begin();
	while (it != m_HTree2VP.end())
	{
		delete (*it).second;
		it++;
	}

}

__forceinline CEditTreeCtrl::ItemViewport* CEditTreeCtrl::GetViewport(HTREEITEM hItem)
{
	HTREE2VPMAP::iterator it = m_HTree2VP.find(hItem);
	if (it != m_HTree2VP.end())
		return (*it).second;
	return NULL;
}

void CEditTreeCtrl::ResetScrollbars()
{
	CRect rect;
	GetClientRect(rect);

	if(rect.Height() > m_YMax + 8 )
	{
		ShowScrollBar( SB_VERT, FALSE );	// Hide it
		SetScrollPos( SB_VERT, 0 );
	}
	else
	{
		SCROLLINFO	si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_PAGE | SIF_RANGE;
		si.nPage = rect.Height();
		si.nMax = m_YMax + 8;
		si.nMin = 0 ;

		SetScrollInfo( SB_VERT, &si );
		EnableScrollBarCtrl( SB_VERT, TRUE );
	}


	if(rect.Width() > m_XMax + 8 )
	{
		ShowScrollBar( SB_HORZ, FALSE );	// Hide it
		SetScrollPos( SB_HORZ, 0 );
	}
	else
	{
		SCROLLINFO	si;
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_PAGE | SIF_RANGE;
		si.nPage = rect.Width();
		si.nMax = m_XMax + 8;
		si.nMin = 0 ;

		SetScrollInfo( SB_HORZ, &si );
		EnableScrollBarCtrl( SB_HORZ, TRUE );
	}
}

void CEditTreeCtrl::OnSizing(UINT fwSide, LPRECT pRect) 
{
	if (!m_bCustomDrawn)
		CTreeCtrl::OnSizing(fwSide, pRect);
}

void CEditTreeCtrl::OnSize(UINT nType, int cx, int cy) 
{
	if (!m_bCustomDrawn)
		CTreeCtrl::OnSize(nType, cx, cy);
	else
	{
		ResetScrollbars();
		Invalidate();
	}	
}

void CEditTreeCtrl::OnChangeTextFace() 
{

	LOGFONT lf;
	CFontDialog dlg;
	dlg.m_cf.lpLogFont = &lf;
	
	if( dlg.DoModal() == IDOK)
	{
		
		m_Font.DeleteObject();
		dlg.GetCurrentFont(&lf);
		
		m_Font.CreateFontIndirect(&lf);
	
		/*
		m_NodeTextColor = dlg.GetColor();
		m_LeafTextColor = dlg.GetColor();
		m_LinkTextColor = dlg.GetColor();
		*/
	}
}

void CEditTreeCtrl::OnChangeLinkTextColor() 
{
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_LinkTextColor = dlg.GetColor();
	}

}	

void CEditTreeCtrl::OnChangeLeafTextColor() 
{
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_LeafTextColor = dlg.GetColor();
	}

}	

void CEditTreeCtrl::OnChangeNodeTextColor() 
{
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_NodeTextColor = dlg.GetColor();
	}

}	


void CEditTreeCtrl::OnChangeNodeBkColor() 
{
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_NodeBkColor = dlg.GetColor();
	}
}

void CEditTreeCtrl::OnChangeLeafBkColor() 
{
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_LeafBkColor = dlg.GetColor();
	}	
}



void CEditTreeCtrl::OnChangeLinkBkColor() 
{
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_LinkBkColor = dlg.GetColor();
	}	
}

void CEditTreeCtrl::OnChangeExpandTopLeft() 
{
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_clrTopLeft = dlg.GetColor();
	}	
}

void CEditTreeCtrl::OnChangeExpandBottomRight() 
{
	CColorDialog dlg;
	if( dlg.DoModal() == IDOK )
	{
		m_clrBottomRight = dlg.GetColor();
	}
}

void CEditTreeCtrl::OnChangeItemSpaceX(int x) 
{
	m_ItemSpaceX = x;
}

void CEditTreeCtrl::OnChangeItemSpaceY(int y) 
{
	m_ItemSpaceY = y;
}

void CEditTreeCtrl::OnChangeLinkNodeSpaceY(int y) 
{
	m_LinkNodeSpaceY = y;
}



void CEditTreeCtrl::OnZoomIn()
{
	LOGFONT lf;
	m_Font.GetLogFont(&lf);
	
	int iFontHeight = lf.lfHeight;
	int iFontWeight = lf.lfWeight;
	BYTE lFontItalic = lf.lfItalic;
	BYTE lFontUnderline = lf.lfUnderline;
	BYTE lFontStrikeOut = lf.lfStrikeOut;
	
	

	m_sFontFace = lf.lfFaceName;		

	iFontHeight= abs(iFontHeight+2);
	m_ItemSpaceY = m_ItemSpaceY + iFontHeight;
	m_LinkNodeSpaceY = iFontHeight;

	m_Font.DeleteObject();
	m_Font.CreateFont(iFontHeight,0,0,0, FW_NORMAL, lFontItalic, lFontUnderline, lFontStrikeOut, DEFAULT_CHARSET, 
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, iFontWeight, m_sFontFace);
	

}

void CEditTreeCtrl::OnZoomOut()
{
	LOGFONT lf;
	m_Font.GetLogFont(&lf);
	
	int iFontHeight = lf.lfHeight;
	int iFontWeight = lf.lfWeight;
	BYTE lFontItalic = lf.lfItalic;
	BYTE lFontUnderline = lf.lfUnderline;
	BYTE lFontStrikeOut = lf.lfStrikeOut;
	
	

	m_sFontFace = lf.lfFaceName;		

	iFontHeight= abs(iFontHeight- 2);
	m_ItemSpaceY = m_ItemSpaceY - iFontHeight;
	m_LinkNodeSpaceY = iFontHeight;

	m_Font.DeleteObject();
	m_Font.CreateFont(iFontHeight,0,0,0, FW_NORMAL, lFontItalic, lFontUnderline, lFontStrikeOut, DEFAULT_CHARSET, 
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, iFontWeight, m_sFontFace);
	

}

