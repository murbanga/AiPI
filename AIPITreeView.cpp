// AIPITreeView.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "AIPITreeDoc.h"
#include "AIPITreeView.h"
#include "FindInFilesDlg.h"
#include "MainFrm.h"
#include "PageFileDlg.h"
#include "InductionTabView.h"

#include ".\DataFileCSV\CDataFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAIPITreeView

IMPLEMENT_DYNCREATE(CAIPITreeView, CView)

CAIPITreeView::CAIPITreeView()
{
}

CAIPITreeView::~CAIPITreeView()
{
}


BEGIN_MESSAGE_MAP(CAIPITreeView, CView)
	//{{AFX_MSG_MAP(CAIPITreeView)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_VERTICALTREE, OnViewVerticalTree)
	ON_COMMAND(ID_VIEW_HORIZONTALTREE, OnViewHorizontalTree)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_WM_DROPFILES()
	ON_COMMAND(IDC_EXPAND_ALL_TREE, OnEditExpandAllTree)
	ON_COMMAND(ID_COLLAPSE_ALL_ENTIRE_TREE, OnEditCollapseAllEntireTree)
	ON_COMMAND(ID_EDIT_ADD_CHILD, OnEditAddChild)
	ON_COMMAND(ID_EDIT_ADD_SIBLING, OnEditAddSibling)
	ON_COMMAND(ID_EDIT_RENAME, OnEditRename)
	ON_COMMAND(ID_EDIT_DELETE_ITEM, OnEditDeleteItem)
	ON_COMMAND(ID_EDIT_DELETE_ALL_ITEMS, OnEditDeleteAllItems)
	ON_COMMAND(ID_EDIT_SORT_SUBTREE_ALPHABETIC, OnEditSortSubtreeAlphabetic)
	ON_COMMAND(ID_EDIT_SORT_SUBTREE_NUMERIC, OnEditSortSubtreeNumeric)
	ON_COMMAND(IDC_EDIT_COUNT_SUBTREE, OnEditCountSubtree)
	ON_COMMAND(IDC_EDIT_COUNT_ENTIRE_TREE, OnEditCountEntireTree)
	ON_COMMAND(ID_EDIT_CALCULATE_LEVEL, OnEditCalculateLevel)
	ON_COMMAND(ID_SETTINGS_FONTFACE, OnSettingsFontFace)
	ON_COMMAND(ID_SETTINGS_NODECLR, OnSettingsNodeClr)
	ON_COMMAND(ID_SETTINGS_LINKTEXTCLR, OnSettingsLinkTextClr)
	ON_COMMAND(ID_SETTINGS_NODETEXTCLR, OnSettingsNodeTextClr)
	ON_COMMAND(ID_SETTINGS_LEAFTEXTCLR, OnSettingsLeafTextClr)
	ON_COMMAND(ID_SETTINGS_LINKCLR, OnSettingsLinkClr)
	ON_COMMAND(ID_SETTINGS_LEAFCLR, OnSettingsLeafClr)
	ON_COMMAND(ID_BUILD, OnInductionBuildTree)
	ON_COMMAND(ID_SETTINGS_SKIN_CLASSIC, OnSettingsSkinClassic)
	ON_COMMAND(ID_SETTINGS_SKIN_OFFICEXP, OnSettingsSkinOfficeXP)
	ON_WM_DROPFILES()
	ON_COMMAND(IDC_EDIT_EXPAND_ALL_TREE, OnEditExpandAllTree)
	ON_COMMAND(ID_EDIT_COLLAPSE_ALL_ENTIRE_TREE, OnEditCollapseAllEntireTree)
	ON_COMMAND(ID_SETTINGS_SKIN_OFFICE2003, OnSettingsSkinOffice2003)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAIPITreeView drawing

void CAIPITreeView::OnDraw(CDC* pDC)
{
	
	// TODO: add draw code here
	/*
	//pDC->SetMapMode(MM_LOENGLISH);	
	CRect rect = CRect(10, -10, 110, -110);
	pDC->Rectangle(rect);
	*/


	CAIPITreeDoc* pDoc = GetDocument();
	
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (m_etc.m_bCustomDrawn)
	{
		
		//Double Buffering...
		CDC dc_backbuffer;
		CBitmap bb_image;
		

		//Calculate scoll position and control dimensions
		m_etc.UpdateDimensions();

		//Create device context for the backbuffer
		dc_backbuffer.CreateCompatibleDC(pDC);
		//Create the image we are going to draw in
		bb_image.CreateCompatibleBitmap(pDC, m_etc.m_Rect.Width(), m_etc.m_Rect.Height());
		dc_backbuffer.SelectObject(&bb_image);

		//We use the same Font which was configured in the main device context
		
		//dc_backbuffer.SelectObject(GetFont());
		dc_backbuffer.SelectObject(&m_etc.m_NodeFont);
		
		dc_backbuffer.SetBkMode(TRANSPARENT);

		//General Info
		DWORD style = GetStyle();
		m_etc.m_bHasButtons = (style & TVS_HASBUTTONS) != 0;
		m_etc.m_bHasLines = (style & TVS_HASLINES) != 0;

		//Now draw the items...
		m_etc.m_XMax = 0;
		m_etc.m_YMax = 0;
		//dc_backbuffer.FillSolidRect(m_Rect, dc_backbuffer.GetBkColor()); 
		dc_backbuffer.FillSolidRect(m_etc.m_Rect, dc_backbuffer.SetBkColor(RGB(255, 255, 255)));
		int xoffset = 0;
		for (HTREEITEM root = m_etc.GetRootItem(); root != NULL; root = m_etc.GetNextItem(root, TVGN_NEXT))
			xoffset = m_etc.DrawItem(&dc_backbuffer, root, xoffset);

		//Copy the backbuffer to the main device context...
		pDC->BitBlt( m_etc.m_Rect.left, m_etc.m_Rect.top, m_etc.m_Rect.Width(), m_etc.m_Rect.Height(), &dc_backbuffer, 0, 0, SRCCOPY);

		//m_etc.ResetScrollbars();

  
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAIPITreeView diagnostics

#ifdef _DEBUG
void CAIPITreeView::AssertValid() const
{
	CView::AssertValid();
}

void CAIPITreeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAIPITreeDoc* CAIPITreeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAIPITreeDoc)));
	return (CAIPITreeDoc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CAIPITreeView message handlers

BOOL CAIPITreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CAIPITreeView::OnEditCopy() 
{
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window
	CAIPITreeView *ptfv= NULL;

	ptfv = (CAIPITreeView *)pChild->GetActiveView(); 
	ptfv->m_etc.OnSaveSubtree();
	  
}


void CAIPITreeView::OnEditCut() 
{
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window
	
	CAIPITreeView *ptfv = NULL;
	ptfv = (CAIPITreeView *)pChild->GetActiveView();
	ptfv->m_etc.CutSubtree();	
}

void CAIPITreeView::OnEditPaste() 
{
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window
		
	CAIPITreeView *ptfv = NULL;
	ptfv = (CAIPITreeView *)pChild->GetActiveView();
	ptfv->m_etc.OnLoadSubtree(ptfv->m_etc.GetSelectedItem());	
}

void CAIPITreeView::OnEditFind()
{
	
	CFindInFilesDlg m_Find;
	    
	if ( m_Find.DoModal() == IDOK )
	{
	
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pMainFrame->m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(2);

		if (pMainFrame->m_wndOutputTabView.IsVisible() == FALSE)
		//Set visible at first
			pMainFrame->ShowControlBar(&pMainFrame->m_wndOutputTabView, TRUE ,TRUE);
		CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
		// Get the active MDI child window.
		CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
		// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
		// Get the active view attached to the active MDI child window
		CAIPITreeView *ptfv = NULL;
		ptfv = (CAIPITreeView *)pChild->GetActiveView();
		ptfv->m_etc.OnFindDlg(m_Find.m_strFind);
		g_findText = m_Find.m_strFind;
	
	}
	
	
}

void CAIPITreeView::OnDropFiles(HDROP hDropInfo) 
{
    /*
	char path[_MAX_PATH];
	CAIPITreeDoc *pted;
	pted = GetDocument();

	// Called when a file was dropped from Explorer
	DragQueryFile(hDropInfo, 0, path, sizeof(path));
	
	
	pted = (CAIPITreeDoc *)GetActiveDocument();
	if (pted->SaveModified())
	{
		pted->m_strFileName = path;
		pted->OpenFile();
	}
	*/

}

void CAIPITreeView::DrawNodeText(CDC *pDC, HTREEITEM item, CString text, int x, int y, int cx, int cy, COLORREF bkcolor,COLORREF txtcolor)
{
	pDC->FillSolidRect(x+m_etc.m_OffsetX, -y-m_etc.m_OffsetY, cx, cy, bkcolor);
	pDC->SetTextColor(txtcolor);
	pDC->TextOut(x+m_etc.m_OffsetX,-y-m_etc.m_OffsetY,text);
	pDC->SelectObject(&m_etc.m_NodeFont);	
	
/*
	ItemViewport *nvp = reinterpret_cast<CAIPITreeView> (m_etc.GetViewport(item));
	
	nvp->x = x;
	nvp->y = y;
	nvp->cx = cx;
	nvp->cy = cy;
*/
	if (x + cx > m_etc.m_XMax)
		m_etc.m_XMax = x + cx;
	if (y + cy > m_etc.m_YMax)
		m_etc.m_YMax = -(y + cy);

}


void CAIPITreeView::DrawLeafText(CDC *pDC, HTREEITEM item,  CString text, int x, int y, int cx, int cy, COLORREF bkcolor,COLORREF txtcolor)
{
	pDC->FillSolidRect(x+m_etc.m_OffsetX, -y-m_etc.m_OffsetY, cx, cy, bkcolor);
	pDC->SetTextColor(txtcolor);
	pDC->TextOut(x+m_etc.m_OffsetX,-y-m_etc.m_OffsetY,text);
	pDC->SelectObject(&m_etc.m_LeafFont);	
	
	/*
	ItemViewport *nvp = GetViewport(item);
	
	nvp->x = x;
	nvp->y = y;
	nvp->cx = cx;
	nvp->cy = cy;
*/

	if (x + cx > m_etc.m_XMax)
		m_etc.m_XMax = x + cx;
	if (y + cy > m_etc.m_YMax)
		m_etc.m_YMax = -(y + cy);

}

void CAIPITreeView::DrawLinkText(CDC *pDC, HTREEITEM item, CString text, int x, int y, int cx, int cy, COLORREF bkcolor,COLORREF txtcolor)
{
	pDC->FillSolidRect(x+m_etc.m_OffsetX, -y-m_etc.m_OffsetY, cx, cy, bkcolor);
	pDC->SetTextColor(txtcolor);
	pDC->TextOut(x+m_etc.m_OffsetX,-y-m_etc.m_OffsetY,text);
	pDC->SelectObject(&m_etc.m_LinkFont);

/*
	ItemViewport *nvp = GetViewport(item);
	
	nvp->x = x;
	nvp->y = y;
	nvp->cx = cx;
	nvp->cy = cy;
*/
	if (x + cx > m_etc.m_XMax)
		m_etc.m_XMax = x + cx;
	if (y + cy > m_etc.m_YMax)
		m_etc.m_YMax = -(y + cy);

}

int CAIPITreeView::DrawItem(CDC *pDC, HTREEITEM item, int x, int level)
{
	
	CString name = m_etc.GetItemText(item);

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
	
		if( link_name.GetLength() >= node_name.GetLength())
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
	
	
	
	int state = m_etc.GetItemState(item, TVIF_STATE);
	bool selected = (state & TVIS_SELECTED) != 0;

	if (m_etc.ItemHasChildren(item))
	{
		int left = x;
		int right = 0;
		int childcount = 0;

		if (state & TVIS_EXPANDED)
			for (HTREEITEM childitem = m_etc.GetChildItem(item); childitem != NULL; childitem = m_etc.GetNextItem(childitem, TVGN_NEXT))
			{
				right = DrawItem(pDC, childitem, x, level + 1);
				x = right;
				childcount++;
			}

		right = right - m_etc.m_ItemSpaceX;
		int width =  right - left;
		x = left + width / 2 - text_size.cx / 2;

		if (x < left + m_etc.m_ItemSpaceX)
		   x = left;
		

		int y = -level*m_etc.m_ItemSpaceY;
		
		//Draw the link text a little more higher
		if ( link_name.IsEmpty() == 0 )
			DrawLinkText(pDC, item, link_name, x, level*m_etc.m_ItemSpaceY + m_etc.m_LinkNodeSpaceY, text_size.cx, text_size.cy, m_etc.m_LinkBkColor, m_etc.m_LinkTextColor);
		//Draw the node text
		DrawNodeText(pDC, item, node_name, x, -level*m_etc.m_ItemSpaceY, text_size.cx, text_size.cy, m_etc.m_NodeBkColor, m_etc.m_NodeTextColor);
	
		
		//Draw lines...
		if (m_etc.m_bHasLines && (state & TVIS_EXPANDED))
		{
			int xstart = x + text_size.cx / 2;
			int ystart = y - text_size.cy + BUTTON_SIZE;
			CGdiObject *oldPen = pDC->SelectObject(&m_etc.m_TreeLinePen);
			for (HTREEITEM childitem = m_etc.GetChildItem(item); childitem != NULL; childitem = m_etc.GetNextItem(childitem, TVGN_NEXT))
			{
				//ItemViewport *current = (CAIPITreeView*)m_etc.GetViewport(childitem);
				pDC->MoveTo(xstart+m_etc.m_OffsetX,ystart+m_etc.m_OffsetY);
				//pDC->LineTo(current->x +m_etc.m_OffsetX + current->cx / 2 , current->y - m_etc.m_OffsetY);
								
			}
			pDC->SelectObject(oldPen);
		}

		if (m_etc.m_bHasButtons)
		{
			pDC->Draw3dRect(x+m_etc.m_OffsetX+text_size.cx / 2 - BUTTON_SIZE / 2, y-m_etc.m_OffsetY + text_size.cy, BUTTON_SIZE, BUTTON_SIZE, m_etc.m_clrTopLeft, m_etc.m_clrBottomRight);
			pDC->MoveTo(x+m_etc.m_OffsetX+text_size.cx / 2 - BUTTON_SIZE / 2 + 2, y-m_etc.m_OffsetY + text_size.cy + BUTTON_SIZE / 2);
			pDC->LineTo(x+m_etc.m_OffsetX+text_size.cx / 2 + BUTTON_SIZE / 2 - 1, y-m_etc.m_OffsetY + text_size.cy + BUTTON_SIZE / 2);
			
			if ((state & TVIS_EXPANDED) == 0)
			{
				pDC->MoveTo(x+m_etc.m_OffsetX+text_size.cx / 2, y-m_etc.m_OffsetY + text_size.cy + 2);
				pDC->LineTo(x+m_etc.m_OffsetX+text_size.cx / 2, y-m_etc.m_OffsetY + text_size.cy + BUTTON_SIZE - 2);
			}
		}
		
	
		
		
		if (right > x + text_size.cx)
		   return right + m_etc.m_ItemSpaceX;
		else
		   return x + text_size.cx + m_etc.m_ItemSpaceX;
	}
	else
	{
		//Draw the link name from the leaf a little more higher
		if ( link_name.IsEmpty() == 0 )
			DrawLinkText(pDC, item, link_name, x, level*m_etc.m_ItemSpaceY + m_etc.m_LinkNodeSpaceY, text_size.cx, text_size.cy, m_etc.m_LinkBkColor, m_etc.m_LinkTextColor);
		//Draw the node text from the leaf
		DrawLeafText(pDC, item, node_name, x, -level*m_etc.m_ItemSpaceY, text_size.cx, text_size.cy, m_etc.m_LeafBkColor, m_etc.m_LeafTextColor);
	
		return x + text_size.cx + m_etc.m_ItemSpaceX;
	}
	
	
}

void CAIPITreeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	m_etc.SetLimitText(100);
	m_etc.InitializeImageList();
	m_etc.SetCustomDrawn(FALSE);
	
	


	//CID3 dt;
	//dt.AddSiblingName(_T("Hola pueblo"));
	//dt.AddChildName(_T("Hola hijo del pueblo"));
	//dt.AddMsgOutputWnd(_T("Mensaje de prueba del arbol de desición ID3"));

	
/*
	m_etc.OnAddSiblingName("Hombres < 456");
	m_etc.OnAddChildName("Nodo01");
	m_etc.OnAddChildName("Nodo02");
	m_etc.OnAddSiblingName("Mujeres");

	m_etc.OnAddChildName("Nodo03");
	m_etc.OnAddChildName("Nodo04");

	m_etc.OnAddSiblingName("Hombres > 456");


	m_etc.OnAddChildName("Nodo01");
	m_etc.OnAddChildName("Nodo02");
	m_etc.OnAddSiblingName("Mujeres");

	m_etc.OnAddChildName("Nodo03");
	m_etc.OnAddChildName("Nodo04");

*/
	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().

	UpdateSkinMenus();

	
}


void CAIPITreeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (m_etc.m_pted == NULL)
		m_etc.m_pted = (CAIPITreeDoc *)GetDocument();
	
	
	switch(lHint)
	{
	case HINT_NEW:
		m_etc.DeleteAllItems();	
		break;
	case HINT_LOAD_DIRECTORY:
		m_etc.DeleteAllItems();	
		m_etc.OnLoadEntireTree(FF_DIRECTORY_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_LOAD_TREE_TYPE:
		m_etc.DeleteAllItems();	
		m_etc.OnLoadEntireTree(FF_TREE_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_LOAD_PROJ_TYPE:
		m_etc.DeleteAllItems();	
		m_etc.OnLoadEntireTree(FF_PROJ_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_LOAD_INDENT_TYPE:
		m_etc.DeleteAllItems();	
		m_etc.OnLoadEntireTree(FF_INDENT_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_LOAD_CSV_TYPE:
		m_etc.DeleteAllItems();	
		m_etc.OnLoadEntireTree(FF_CSV_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_SAVE_TREE_TYPE:
		m_etc.OnSaveEntireTree(FF_TREE_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_SAVE_PROJ_TYPE:
		m_etc.OnSaveEntireTree(FF_PROJ_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_SAVE_INDENT_TYPE:
		m_etc.OnSaveEntireTree(FF_INDENT_TYPE, m_etc.m_pted->m_tt);
		break;
	case HINT_SAVE_CSV_TYPE:
		m_etc.OnSaveEntireTree(FF_CSV_TYPE, m_etc.m_pted->m_tt);
		break;
	default:
		break;	
	}



}

int CAIPITreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//Create the tree view
	CRect r;
	DWORD newstyle = TVS_SHOWSELALWAYS | TVS_EDITLABELS | TVS_HASBUTTONS | 
		TVS_LINESATROOT | TVS_HASLINES;
	if (!m_etc.Create(WS_VISIBLE | WS_CHILD | newstyle, r, this, 100))
		return -1;	      
	return 0;
}

void CAIPITreeView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	m_etc.SetFocus();
}

void CAIPITreeView::OnSize(UINT nType, int cx, int cy) 
{
	//Let the tree control occupy all the space of the client area
	CRect r;  
	GetClientRect(&r);
	m_etc.MoveWindow(r);
	//m_etc.MoveWindow(0, 30, cx, cy-40);
}

/////////////////////////////////////////////////////////////////////////////
// CAIPITreeView printing

BOOL CAIPITreeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAIPITreeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}


void CAIPITreeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


/////////////////////////////////////////////////////////////////////////////
// CAIPITreeView message handlers

void CAIPITreeView::OnViewVerticalTree() 
{
	m_etc.SetCustomDrawn(TRUE);
	m_etc.Invalidate();

}


void CAIPITreeView::OnViewHorizontalTree() 
{
	
	m_etc.SetCustomDrawn(FALSE);
	m_etc.Invalidate();	

	
	CAIPITreeDoc *pDoc = GetDocument();
		
	CString strTitle = (CString) pDoc->GetTitle();
	CString strExt = strTitle.Right(3);
		
//Open different files extensions
	if (m_etc.m_pted == NULL)
		m_etc.m_pted = (CAIPITreeDoc *)GetDocument();
	
	if(strExt == "tre")
	{
		m_etc.DeleteAllItems();
		m_etc.OnLoadEntireTree(FF_TREE_TYPE, m_etc.m_pted->m_tt);
	}
	else if(strExt == _T("csv"))
	{
		m_etc.DeleteAllItems();	
		m_etc.OnLoadEntireTree(FF_CSV_TYPE, m_etc.m_pted->m_tt);	
		
	}
	else if(strExt == _T("idt"))
	{
		m_etc.DeleteAllItems();	
		m_etc.OnLoadEntireTree(FF_INDENT_TYPE, m_etc.m_pted->m_tt);
	}
	else
	{
		MessageBox(_T("Invalid input file " + pDoc->m_strFileNamePath ));
		
	}
		
}



void CAIPITreeView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	//pDC->SetMapMode(MM_LOENGLISH);
	pDC->SetMapMode(MM_TEXT);
	
	//CView::OnPrepareDC(pDC, pInfo);
}

void CAIPITreeView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{

	//pDC->SetWindowOrg(pInfo->m_rectDraw.left, -pInfo->m_rectDraw.top);

	// Diseño de MM_LOMETRIC con el eje "y" positivo hacia abajo
  /*
	int nTamX = pDC->GetDeviceCaps(HORZSIZE) * 10; // unidades lógicas
  int nTamY = pDC->GetDeviceCaps(VERTSIZE) * 10; // unidades lógicas
  int nResX = pDC->GetDeviceCaps(HORZRES); // unidades físicas
  int nResY = pDC->GetDeviceCaps(VERTRES); // unidades físicas
  pDC->SetMapMode(MM_ANISOTROPIC);
  pDC->SetWindowExt(nTamX, nTamY);
  pDC->SetViewportExt(nResX, nResY);
  /*
  // Convertir coordenadas físicas a lógicas
  pDC->DPtoLP(pInfo->m_rectDraw);

  if ( pInfo->m_nCurPage == 1 ) // si es la página 1
  {
    // Imprimir el título y una posible historia
    PrintTitulo( pDC, pInfo );
    // Imprima aquí su historia
    return;
  }
  
  // Imprimir la cabecera
  CString sCabecera = GetDocument()->GetTitle();
  PrintCabecera( pDC, pInfo, sCabecera );
  
  // Establecer el origen para el cuerpo de la página
  pDC->SetWindowOrg(pInfo->m_rectDraw.left, pInfo->m_rectDraw.top);
*/
	CView::OnPrint(pDC, pInfo);
}

void CAIPITreeView::OnEditExpandAllTree() 
{
	m_etc.OnExpandAllTree();
	
}

void CAIPITreeView::OnEditCollapseAllEntireTree() 
{
	m_etc.OnCollapseAllEntireTree();	
}

void CAIPITreeView::OnEditAddChild() 
{
	m_etc.OnAddChild();	
}

void CAIPITreeView::OnEditAddSibling() 
{
	m_etc.OnAddSibling();	
}

void CAIPITreeView::OnEditRename() 
{
	m_etc.OnRename();	
}

void CAIPITreeView::OnEditDeleteItem() 
{
	m_etc.OnDeleteItem();	
}

void CAIPITreeView::OnEditDeleteAllItems() 
{
	m_etc.OnDeleteAllItems();	
}

void CAIPITreeView::OnEditSortSubtreeAlphabetic() 
{
	m_etc.OnSortSubtreeAlphabetic();	
}

void CAIPITreeView::OnEditSortSubtreeNumeric() 
{
	m_etc.OnSortSubtreeNumeric();	
}

void CAIPITreeView::OnEditCountSubtree() 
{
	m_etc.OnCountSubtree();	
}

void CAIPITreeView::OnEditCountEntireTree() 
{
	m_etc.OnCountEntireTree();	
}


void CAIPITreeView::OnEditCalculateLevel() 
{
	m_etc.OnCalculateLevel();	
}

void CAIPITreeView::OnSettingsFontFace() 
{
	m_etc.OnChangeTextFace();
	m_etc.Invalidate();

}

void CAIPITreeView::OnSettingsLinkTextClr() 
{
	m_etc.OnChangeLinkTextColor();
	m_etc.Invalidate();
}

void CAIPITreeView::OnSettingsNodeTextClr() 
{
	m_etc.OnChangeNodeTextColor();
	m_etc.Invalidate();
		
}

void CAIPITreeView::OnSettingsLeafTextClr() 
{
	m_etc.OnChangeLeafTextColor();
	m_etc.Invalidate();
		
}

void CAIPITreeView::OnSettingsNodeClr() 
{
	m_etc.OnChangeNodeBkColor();
	m_etc.Invalidate();
}


void CAIPITreeView::OnSettingsLinkClr() 
{

	m_etc.OnChangeLinkBkColor();
	m_etc.Invalidate();	
}



void CAIPITreeView::OnSettingsLeafClr() 
{
	
	m_etc.OnChangeLeafBkColor();
	m_etc.Invalidate();	
}








void CAIPITreeView::OnInductionBuildTree() 
{
	/*
	m_etc.m_pted = (CAIPITreeDoc *)GetDocument();
	m_etc.m_pted->m_strFileNamePath = _T("D:\\Project AIPI VS6\\AIPI\\Examples\\Cicuta.idt");
	m_etc.m_pted->OpenFile();
	m_etc.m_pted->m_strFileNamePath = _T("D:\\Project AIPI VS6\\AIPI\\Examples\\MFC_Classes.idt");
	m_etc.m_pted->OpenFile();
	*/

	
	OnEditDeleteAllItems();
	m_etc.SetCustomDrawn(FALSE);

	BeginWaitCursor(); // display the hourglass cursor
	UpdateWindow();

	CAipi_DT_ID3 dt;
	dt.Build();

	EndWaitCursor();
		
	
	//dlg.OnOpenDatabaseConnection(MS_ACCESS);
	/*
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndInductionTabView.IsVisible() )
	{
		pMainFrame->m_wndInductionTabView.OnOpenDatabaseConnection(MS_ACCESS);
	}
	*/

}








void CAIPITreeView::OnSettingsSkinClassic() 
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->OnSettingsSkinClassic();
	pMainFrame->CheckMenuSkinType();

	
	
}

void CAIPITreeView::OnSettingsSkinOfficeXP() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->OnSettingsSkinOfficeXP();
	pMainFrame->CheckMenuSkinType();

	
	
}

void CAIPITreeView::OnSettingsSkinOffice2003() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->OnSettingsSkinOffice2003();
	pMainFrame->CheckMenuSkinType();

	
}


void CAIPITreeView::UpdateSkinMenus()
{
/*
	TCHAR buffer[8];
   CString	str =  _itot( g_iSkinType, buffer, 10 );
   AfxMessageBox(_T("CAIPITreeView"));
   AfxMessageBox(str);
*/
	
	switch(g_iSkinType)
	{
	case OXSkinClassic:
		OnSettingsSkinClassic();
		break;
	case OXSkinOfficeXP:
		OnSettingsSkinOfficeXP();
		break;
	case OXSkinOffice2003:
		OnSettingsSkinOffice2003();
		break;

	}

}
