// WorkspaceTabView.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "WorkspaceTabView.h"
#include "WorkspaceTabDoc.h"
#include "WorkspaceView.h"
#include "WorkspaceLocation.h"
#include "AIPIEditorDoc.h"
#include "AIPIEditorView.h"
#include "MainFrm.h"
#include ".\ScintillaCtrl\ScintillaDocView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTabView

IMPLEMENT_DYNCREATE(CWorkspaceTabView, COXSizeControlBar)

CWorkspaceTabView::CWorkspaceTabView(): 
COXSizeControlBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	
}

CWorkspaceTabView::~CWorkspaceTabView()
{

}


BEGIN_MESSAGE_MAP(CWorkspaceTabView, COXSizeControlBar)
	//{{AFX_MSG_MAP(CWorkspaceTabView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEVIEWCTRL1, OnSelchangedTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEVIEWCTRL2, OnSelchangedTree2)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEVIEWCTRL3, OnSelchangedTree3)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEVIEWCTRL1, OnItemexpandedTree1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEVIEWCTRL2, OnItemexpandedTree2)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEVIEWCTRL3, OnItemexpandedTree3)
	//ON_NOTIFY(TCN_SELCHANGE, IDB_TABTREEIMAGES, OnSelchange)
	ON_NOTIFY_REFLECT_EX(TCN_SELCHANGE, OnSelchange)
		//}}AFX_MSG_MAP

	
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTabView drawing
BOOL CWorkspaceTabView::OnEraseBkgnd(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTabView diagnostics

#ifdef _DEBUG
void CWorkspaceTabView::AssertValid() const
{
	COXSizeControlBar::AssertValid();
}

void CWorkspaceTabView::Dump(CDumpContext& dc) const
{
	COXSizeControlBar::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTabView message handlers

void CWorkspaceTabView::DoDataExchange(CDataExchange* pDX) 
{
	DDX_Control(pDX, IDC_TREEVIEWCTRL1, m_treeCtrl1);
	DDX_Control(pDX, IDC_TREEVIEWCTRL2, m_treeCtrl2);
	DDX_Control(pDX, IDC_TREEVIEWCTRL3, m_treeCtrl3);
	//DDX_Control(pDX, IDB_TABTREEIMAGES, m_TabViewContainer);
	
	COXSizeControlBar::DoDataExchange(pDX);
}

//-------------------------------------------------------------------
void CWorkspaceTabView::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// respond to this event as we need to override it
//-------------------------------------------------------------------
{
//~ /* 	UNREFERENCED_PARAMETER(bFloating);
 //~ * 	UNREFERENCED_PARAMETER(flags);
 //~ * 	UNREFERENCED_PARAMETER(cx);
 //~ * 	UNREFERENCED_PARAMETER(cy);
 //~ */

	CRect rect;
	GetClientRect(rect);
	rect.DeflateRect(0, 0);

	m_TabViewContainer.MoveWindow(&rect);

}


int CWorkspaceTabView::Create3DTabCtrl()
{
	CRect rect;
	GetClientRect(&rect);

	if(!m_TabViewContainer.Create(this,rect))
		return -1;

	VERIFY(m_ilTabImageList.Create(IDB_TABTREEIMAGES,18,1,RGB(192,192,192)));
	m_TabViewContainer.SetImageList(&m_ilTabImageList);

	m_TabViewContainer.SetActivePageIndex(0);
	return 0;
}


int CWorkspaceTabView::CreateTree1()
{

	// Rules View
	if(!m_treeCtrl1.Create(WS_CHILD|TVS_HASLINES|TVS_EDITLABELS|TVS_LINESATROOT|TVS_HASBUTTONS,
		CRect(0,0,0,0),&m_TabViewContainer,IDC_TREEVIEWCTRL1))
		return -1;
	VERIFY(m_ilTreeImageList1.Create(IDB_RULEIMAGES,18,28, RGB(192,192,192)));
	m_treeCtrl1.SetImageList(&m_ilTreeImageList1,TVSIL_NORMAL);

	m_TabViewContainer.AddPage(&m_treeCtrl1,_T("RuleView"),0);
	return 0;
}

int CWorkspaceTabView::CreateTree2()
{
	// Tree View
	if(!m_treeCtrl2.Create(WS_CHILD|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS,
		CRect(0,0,0,0),&m_TabViewContainer,IDC_TREEVIEWCTRL2))
		return -1;
	VERIFY(m_ilTreeImageList2.Create(IDB_FILEIMAGES,16,2,RGB(192,192,192)));
	m_treeCtrl2.SetImageList(&m_ilTreeImageList2,TVSIL_NORMAL);
	
	m_TabViewContainer.AddPage(&m_treeCtrl2,_T("FileView"),1);
	return 0;

}

int CWorkspaceTabView::CreateTree3()
{

	// Resource View
	if(!m_treeCtrl3.Create(WS_CHILD|TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS,
		CRect(0,0,0,0),&m_TabViewContainer,IDC_TREEVIEWCTRL3))
		return -1;
	VERIFY(m_ilTreeImageList3.Create(IDB_RESOURCEIMAGES,18,6, RGB(192,192,192)));
	m_treeCtrl3.SetImageList(&m_ilTreeImageList3,TVSIL_NORMAL);
	
	

	m_TabViewContainer.AddPage(&m_treeCtrl3,_T("ResourceView"),2);
	
	return 0;

}

long CWorkspaceTabView::WSPSearchToken(long posStart, long posEnd, LPSTR szToken)
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	
	rCtrl.SetTargetStart(posStart);
	rCtrl.SetTargetEnd(posEnd);
	rCtrl.SetSearchFlags(SCFIND_MATCHCASE);
	long posTokenStart = rCtrl.SearchInTarget(strlen(szToken), szToken);
	
	/*
	CString str;
	str.Format(_T("TOKEN Start Position .. %d"), posTokenStart);
	AfxMessageBox(str);
	*/
	return posTokenStart;
}

void CWorkspaceTabView::WSPCheckPositionChange( HTREEITEM hItem, CString name, CString file, int categ)
{
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	LPSTR szName = (LPSTR) name.GetBuffer(0);

	long currentPos = rCtrl.GetCurrentPos();
	int currentLine = rCtrl.LineFromPosition(currentPos);
	long docEndPos = rCtrl.GetLength();
	
	long pos = WSPSearchToken(currentPos, docEndPos, szName);
	/*
	CString st;
	AfxMessageBox(name);
	st.Format(_T("Element Position...%d  " ), pos);
	AfxMessageBox(st);
	*/
	if( pos != NOT_FOUND )
	{
		int line = rCtrl.LineFromPosition(pos);
		if( line == currentLine )
		{
			return;
		}
		else
		{
			// Reset Scintilla Markers 
			rCtrl.MarkerDeleteAll(0);
			// Initilaize markers
			rCtrl.MarkerDefine(0, SC_MARK_ARROW);
			rCtrl.MarkerSetFore(0, RGB( 128, 128, 128 ));
			rCtrl.MarkerSetBack(0, RGB( 128, 128, 128 ));
			// Set error marker to proper line
			rCtrl.GotoLine(line );
			rCtrl.MarkerAdd((line), 0);

			CWorkspaceLocation loc;
			loc.eraseLocation(hItem);
			loc.addLocation(hItem, pos, line, name, file, categ);
		}
	}
	else
	{
		pos = WSPSearchToken(currentPos, 0, szName);
		if( pos != NOT_FOUND )
		{
			int line = rCtrl.LineFromPosition(pos);
			if( line == currentLine )
			{
				return;
			}
			else
			{
				// Reset Scintilla Markers 
				rCtrl.MarkerDeleteAll(0);
				// Initilaize markers
				rCtrl.MarkerDefine(0, SC_MARK_ARROW);
				rCtrl.MarkerSetFore(0, RGB( 128, 128, 128 ));
				rCtrl.MarkerSetBack(0, RGB( 128, 128, 128 ));
				// Set error marker to proper line
				rCtrl.GotoLine(line );
				rCtrl.MarkerAdd((line), 0);

				CWorkspaceLocation loc;
				loc.eraseLocation(hItem);
				loc.addLocation(hItem, pos, line, name, file, categ);

			}
		}
		else
		{
			CAipi_Error err;
			err.displayGUIError(ELEMENT_MISSING, WARNING_ERROR, _T("Element doesn't match.") );
		}
	}

}


void CWorkspaceTabView::AddPasteWorkspace(CString keyword)
{
		

	/*
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	const TEXTLENGTH = 1040;
	BOOL bFound = FALSE;
	BOOL bWholeWord = FALSE;
	BOOL bMatchCase = FALSE;
	BOOL bRegExp = FALSE;

	LVITEM Item;
	int iBufferSize = 254;
	int iCount = 0;
	int iLine = 0;
	int iPos = 0;
	int iType = 1;
		
	TCHAR chBuff[16];

	
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);

	
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	int iLastLine = rCtrl.GetLineCount();
	iPos = rCtrl.GetLineEndPosition(iLastLine -1);
	rCtrl.GotoPos(iPos);
	rCtrl.SetCurrentPos(iPos);

	
		bMatchCase = SCFIND_MATCHCASE;
		bWholeWord = SCFIND_WHOLEWORD;
		

	do 
	{
		
		bFound = pView->FindTextSimple(keyword, FALSE ,bMatchCase , bWholeWord ,bRegExp);
		
		if (bFound == FALSE )
			break;

		iPos = rCtrl.GetCurrentPos();
		iLine = rCtrl.LineFromPosition(iPos);
		int iLen = rCtrl.LineLength(iLine);
	
		
		int nStartSel = rCtrl.PositionFromLine(iLine);
		int nEndSel = rCtrl.GetLineEndPosition(iLine);
		int iLength = nEndSel - nStartSel + 1;
		
		
			
			TextRange tr;
			tr.chrg.cpMin = nStartSel;
			tr.chrg.cpMax = nEndSel;
			char sText[TEXTLENGTH];
							
			tr.lpstrText = sText;
			
			if (iLength > TEXTLENGTH )
			{
				rCtrl.GetText(TEXTLENGTH, sText);
			}
			else
				rCtrl.GetTextRange(&tr);
			
			CString strPos = _itot(iPos, chBuff, 10);
			CString strLine = _itot(iLine + 1, chBuff, 10);
			CString strText = (CString)sText;
			strText.Remove('\t');
			
			
			LPTSTR lpszText = (LPTSTR)strText.GetBuffer(iBufferSize);
			LPTSTR lpszLine = strLine.GetBuffer(iBufferSize);
			LPTSTR lpszPos = strPos.GetBuffer(iBufferSize);
			
			///HTREEITEM hTRoot, hTItem, hTItem2;
			///hTRoot = AddTreeItem1((HTREEITEM)NULL, lpszText, (HTREEITEM)TVI_ROOT, 0);
			//hTItem = AddTreeItem1(hTRoot, _T("Item1"), (HTREEITEM)TVI_FIRST, 1);
			
			
			iCount++;
	
	} while( bFound == TRUE);

	
	
	CString strCount = _itot(iCount, chBuff, 10);
	LPTSTR lpszCount = _T("0");

	*/

}

//-------------------------------------------------------------------
int CWorkspaceTabView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
//-------------------------------------------------------------------
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	

    Create3DTabCtrl();

	CreateTree1();
	//PoblateTree1();
	
	CreateTree2();
	//PoblateTree2();
		
	CreateTree3();
	//PoblateTree3();
	
	//SamplePoblateTree1();
	//SamplePoblateTree2();
	//SamplePoblateTree3();


	m_TabViewContainer.SetActivePageIndex(0);


	return 0;					
}


BOOL CWorkspaceTabView::Create(CWnd * pParentWnd, 
						   const CString& sTitle/*=_T("3DTabViewBar")*/,
						   const UINT nID/*=ID_3DTABVIEWBAR*/)
{
	// register a window class for the control bar
	static CString strWndClass;
	if (strWndClass.IsEmpty())
	{
		strWndClass = AfxRegisterWndClass(CS_DBLCLKS);
	}
	
	return COXSizeControlBar::Create(strWndClass, sTitle,
		WS_VISIBLE | WS_CHILD | CBRS_BOTTOM | WS_CLIPSIBLINGS,
		CFrameWnd::rectDefault, pParentWnd, nID);
}


HTREEITEM CWorkspaceTabView::AddTreeItem1( HTREEITEM hParent, LPTSTR szText, HTREEITEM hInsAfter,int iImage)
{
	HTREEITEM hItem;
	TVITEM tvI;			// tree control structures
	TVINSERTSTRUCT tvIns;
	//
	//  set mask to text and images
	//	
	tvI.mask = TVIF_TEXT | TVIF_IMAGE;
	tvI.iImage = iImage;  // associate the image
	tvI.pszText = szText; // associate the text
	tvI.cchTextMax = lstrlen(szText);
	//
	tvIns.item = tvI;
	tvIns.hInsertAfter = hInsAfter;	 // where to insert
	tvIns.hParent = hParent;  
	
	//
	// insert this item into the tree
	//
	hItem = m_treeCtrl1.InsertItem(&tvIns);
	//
	//	make selected image index+1 
	//
	m_treeCtrl1.SetItemImage( hItem, iImage, (iImage+1));

	return (hItem);
	// end AddTreeItem1()

}	

HTREEITEM CWorkspaceTabView::AddTreeItem2( HTREEITEM hParent, LPTSTR szText, HTREEITEM hInsAfter,int iImage)
{
	HTREEITEM hItem;
	TVITEM tvI;			// tree control structures
	TVINSERTSTRUCT tvIns;
	//
	//  set mask to text and images
	//	
	tvI.mask = TVIF_TEXT | TVIF_IMAGE;
	tvI.iImage = iImage;  // associate the image
	tvI.pszText = szText; // associate the text
	tvI.cchTextMax = lstrlen(szText);
	//
	tvIns.item = tvI;
	tvIns.hInsertAfter = hInsAfter;	 // where to insert
	tvIns.hParent = hParent;  
	//
	// insert this item into the tree
	//
	hItem = m_treeCtrl2.InsertItem(&tvIns);
	//
	//	make selected image index+1 
	//
	m_treeCtrl2.SetItemImage( hItem, iImage, (iImage+1));


	
	return (hItem);
	// end AddTreeItem2()

}	

HTREEITEM CWorkspaceTabView::AddTreeItem3( HTREEITEM hParent, LPTSTR szText, HTREEITEM hInsAfter,int iImage)
{
	HTREEITEM hItem;
	TVITEM tvI;			// tree control structures
	TVINSERTSTRUCT tvIns;
	//
	//  set mask to text and images
	//	
	tvI.mask = TVIF_TEXT | TVIF_IMAGE;
	tvI.iImage = iImage;  // associate the image
	tvI.pszText = szText; // associate the text
	tvI.cchTextMax = lstrlen(szText);
	//
	tvIns.item = tvI;
	tvIns.hInsertAfter = hInsAfter;	 // where to insert
	tvIns.hParent = hParent;  
	//
	// insert this item into the tree
	//
	hItem = m_treeCtrl3.InsertItem(&tvIns);
	//
	//	make selected image index+1 
	//
	m_treeCtrl3.SetItemImage( hItem, iImage, (iImage+1));

	

	return (hItem);
	// end AddTreeItem3()

}


CString CWorkspaceTabView::GetTreeItem1(HTREEITEM hItem)
{
	return m_treeCtrl1.GetItemText(hItem );

}

void CWorkspaceTabView::EditTreeItem1(CString label, HTREEITEM hItem )
{
	//AfxMessageBox(_T("Edit tree"));
	//AfxMessageBox(label);
	
	
	m_treeCtrl1.SetItemText(hItem, label);
	
}

void CWorkspaceTabView::RenameTreeItem1(CString label, HTREEITEM hItem )
{


	
	m_treeCtrl1.SetFocus();
	CEdit* pEdit = m_treeCtrl1.EditLabel(hItem);
	if(pEdit != NULL)
	{
		pEdit->SetWindowText(label);
		pEdit->SetSel(1, 1);
		m_treeCtrl1.SetItemText(hItem, m_treeCtrl1.GetItemText(hItem));
	}

	

}

void CWorkspaceTabView::PoblateTree1()
{

	int BufSize = 254;

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CString sProject = _T("Project ") + g_projectName;
	LPTSTR lpszProjectName = sProject.GetBuffer(BufSize);
	hTProjectRoot = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1((HTREEITEM)NULL, lpszProjectName, (HTREEITEM)TVI_ROOT, 0);

	CString sClasses = g_projectName + _T(" Classes");
	LPTSTR lpszProjectClasses = sClasses.GetBuffer(BufSize);
	hTProjectClass = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1(hTProjectRoot, lpszProjectClasses, (HTREEITEM)TVI_SORT, 20);

	CString sFunctions = g_projectName + _T(" Functions");
	LPTSTR lpszProjectFunctions = sFunctions.GetBuffer(BufSize);
	hTProjectFunction = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1(hTProjectRoot, lpszProjectFunctions, (HTREEITEM)TVI_SORT, 16);
	
	CString sQuerys = g_projectName + _T(" Querys");
	LPTSTR lpszProjectQuerys = sQuerys.GetBuffer(BufSize);
	hTProjectQuery = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1(hTProjectRoot, lpszProjectQuerys, (HTREEITEM)TVI_SORT, 18);

	CString sRules = g_projectName + _T(" Rules");
	LPTSTR lpszProjectRules = sRules.GetBuffer(BufSize);
	hTProjectRule = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1(hTProjectRoot, lpszProjectRules, (HTREEITEM)TVI_SORT, 22);

	
	CString sVariables = g_projectName + _T(" Variables");
	LPTSTR lpszProjectVariables = sVariables.GetBuffer(BufSize);
	hTProjectVariable = pMainFrame->m_wndWorkspaceTabView.AddTreeItem1(hTProjectRoot, lpszProjectVariables, (HTREEITEM)TVI_SORT, 24);

	pMainFrame->m_wndWorkspaceTabView.m_treeCtrl1.Expand(hTProjectRoot ,TVE_EXPAND);

	


}




void CWorkspaceTabView::SamplePoblateTree1()
{
		
	HTREEITEM hTRoot, hTItem, hTItem2;
	HTREEITEM hTAlfaro;
	
	hTRoot = AddTreeItem1((HTREEITEM)NULL, _T("Project Rules"), (HTREEITEM)TVI_ROOT, 0);
	
	hTItem = AddTreeItem1(hTRoot, _T("Batolo"), (HTREEITEM)TVI_SORT, 2);
	hTItem = AddTreeItem1(hTRoot, _T("Pedro"), (HTREEITEM)TVI_SORT,4);
	hTAlfaro = AddTreeItem1(hTRoot, _T("Alfaro"), (HTREEITEM)TVI_SORT,4); 
	//m_treeCtrl1.Expand(hTRoot ,TVE_EXPAND);
	hTRoot = AddTreeItem1((HTREEITEM)NULL, _T("RA"), (HTREEITEM)TVI_SORT, 0);
	hTItem = AddTreeItem1(hTRoot, _T("Item1"), (HTREEITEM)TVI_FIRST, 2);
	hTItem = AddTreeItem1(hTRoot, _T("Item2"), (HTREEITEM)TVI_LAST,4);
	hTItem = AddTreeItem1(hTRoot, _T("Item3"), (HTREEITEM)TVI_LAST,0);
	
	hTItem = AddTreeItem1(hTAlfaro, _T("SubItem1"), (HTREEITEM)TVI_SORT,2);
	hTItem = AddTreeItem1(hTAlfaro, _T("SubSubItem2"), (HTREEITEM)TVI_SORT, 4);
	hTItem = AddTreeItem1(hTAlfaro, _T("SubSubSubItem3"), (HTREEITEM)TVI_SORT,0);
	hTItem = AddTreeItem1(hTAlfaro, _T("SubSubSubSubItem4"), (HTREEITEM)TVI_SORT,2);
	
	//m_treeCtrl1.Expand(hTRoot ,TVE_EXPAND);
	hTRoot = AddTreeItem1((HTREEITEM)NULL, _T("RB"), (HTREEITEM)TVI_SORT, 0);
	hTItem = AddTreeItem1(hTRoot, _T("Item1"), (HTREEITEM)TVI_FIRST, 2);
	hTItem = AddTreeItem1(hTRoot, _T("Item2"), (HTREEITEM)TVI_LAST,4);
	hTItem = AddTreeItem1(hTRoot, _T("Item3"), (HTREEITEM)TVI_LAST,0); 

	hTItem2 = AddTreeItem1(hTItem, _T("SubItem1"), (HTREEITEM)TVI_LAST,2);
	hTItem2 = AddTreeItem1(hTItem, _T("SubItem2"), (HTREEITEM)TVI_LAST, 4);
	hTItem2 = AddTreeItem1(hTItem, _T("SubItem3"), (HTREEITEM)TVI_LAST,2);
	hTItem2 = AddTreeItem1(hTItem, _T("SubItem4"), (HTREEITEM)TVI_LAST,2);
	m_treeCtrl1.InsertItem(_T("Prueba"));
	
	//m_treeCtrl1.Expand(hTRoot ,TVE_EXPAND);
	hTRoot = AddTreeItem1((HTREEITEM)NULL, _T("RD"), (HTREEITEM)TVI_SORT, 0);
	hTItem = AddTreeItem1(hTRoot, _T("Item1"), (HTREEITEM)TVI_FIRST, 2);
	hTItem = AddTreeItem1(hTRoot, _T("Item2"), (HTREEITEM)TVI_LAST,4);
	
	hTItem2 = AddTreeItem1(hTItem, _T("SubItem1"), (HTREEITEM)TVI_LAST,2);
	hTItem2 = AddTreeItem1(hTItem, _T("SubItem2"), (HTREEITEM)TVI_FIRST, 4);
	hTItem2 = AddTreeItem1(hTItem, _T("SubItem3"), (HTREEITEM)TVI_LAST,0);
	hTItem2 = AddTreeItem1(hTItem, _T("SubItem4"), (HTREEITEM)TVI_LAST,2);
	

	//m_treeCtrl1.Expand(hTRoot ,TVE_EXPAND);
	


}


void CWorkspaceTabView::SamplePoblateTree2()
{
		
	
	HTREEITEM hTRoot,hTItem, hTItem2;
	
	
	hTRoot = AddTreeItem2((HTREEITEM)NULL, _T("Reglas1"), (HTREEITEM)TVI_ROOT, 0);
	hTItem = AddTreeItem2(hTRoot, _T("Prop1"), (HTREEITEM)TVI_FIRST, 2);
	hTItem = AddTreeItem2(hTRoot, _T("Prop2"), (HTREEITEM)TVI_LAST,4);
	hTItem = AddTreeItem2(hTRoot, _T("Prop3"), (HTREEITEM)TVI_LAST,8); 
	//m_treeCtrl2.Expand(hTRoot ,TVE_EXPAND);
	hTRoot = AddTreeItem2((HTREEITEM)NULL, _T("Reglas2"), (HTREEITEM)TVI_ROOT, 0);
	hTItem = AddTreeItem2(hTRoot, _T("Prop1"), (HTREEITEM)TVI_FIRST, 1);
	hTItem = AddTreeItem2(hTRoot, _T("Prop2"), (HTREEITEM)TVI_LAST,4);
	hTItem = AddTreeItem2(hTRoot, _T("Prop3"), (HTREEITEM)TVI_LAST,6);
	
	hTItem = AddTreeItem2(hTItem, _T("Exp1"), (HTREEITEM)TVI_LAST,2);
	hTItem = AddTreeItem2(hTItem, _T("Exp2"), (HTREEITEM)TVI_LAST, 4);
	hTItem = AddTreeItem2(hTItem, _T("Exp3"), (HTREEITEM)TVI_LAST,6);
	hTItem = AddTreeItem2(hTItem, _T("Exp4"), (HTREEITEM)TVI_LAST,7);
	
	//m_treeCtrl2.Expand(hTRoot ,TVE_EXPAND);
	hTRoot = AddTreeItem2((HTREEITEM)NULL, _T("Reglas3"), (HTREEITEM)TVI_ROOT, 0);
	hTItem = AddTreeItem2(hTRoot, _T("Prop1"), (HTREEITEM)TVI_FIRST, 2);
	hTItem = AddTreeItem2(hTRoot, _T("Prop2"), (HTREEITEM)TVI_LAST,4);
	hTItem = AddTreeItem2(hTRoot, _T("Prop3"), (HTREEITEM)TVI_LAST,6); 

	hTItem2 = AddTreeItem2(hTItem, _T("Var1"), (HTREEITEM)TVI_LAST,2);
	hTItem2 = AddTreeItem2(hTItem, _T("Var2"), (HTREEITEM)TVI_LAST, 3);
	hTItem2 = AddTreeItem2(hTItem, _T("Var3"), (HTREEITEM)TVI_LAST,6);
	hTItem2 = AddTreeItem2(hTItem, _T("Var4"), (HTREEITEM)TVI_LAST,7);
	
	//m_treeCtrl2.Expand(hTRoot ,TVE_EXPAND);
	hTRoot = AddTreeItem2((HTREEITEM)NULL, _T("Reglas4"), (HTREEITEM)TVI_ROOT, 0);
	hTItem = AddTreeItem2(hTRoot, _T("Prop1"), (HTREEITEM)TVI_FIRST, 2);
	hTItem = AddTreeItem2(hTRoot, _T("Prop2"), (HTREEITEM)TVI_LAST,4);
	
	hTItem2 = AddTreeItem2(hTItem, _T("Var1"), (HTREEITEM)TVI_LAST,2);
	DeleteTree2(hTItem2);
	hTItem2 = AddTreeItem2(hTItem, _T("Var2"), (HTREEITEM)TVI_FIRST, 4);
	hTItem2 = AddTreeItem2(hTItem, _T("Var3"), (HTREEITEM)TVI_LAST,7);
	hTItem2 = AddTreeItem2(hTItem, _T("Var4"), (HTREEITEM)TVI_LAST,8);
	
	DeleteTree2(hTItem2);
	
	
	//m_treeCtrl2.Expand(hTRoot ,TVE_EXPAND);
	


}

void CWorkspaceTabView::SamplePoblateTree3()
{
	
	
	HTREEITEM hTRoot,hTItem, hTItem2;
	
	
	hTRoot = AddTreeItem3((HTREEITEM)NULL, _T("A"), (HTREEITEM)TVI_ROOT, 0);
	hTItem = AddTreeItem3(hTRoot, _T("a"), (HTREEITEM)TVI_FIRST, 2);
	hTItem = AddTreeItem3(hTRoot, _T("b"), (HTREEITEM)TVI_LAST,1);
	hTItem = AddTreeItem3(hTRoot, _T("c"), (HTREEITEM)TVI_LAST,3); 
	//m_treeCtrl3.Expand(hTRoot ,TVE_EXPAND);
	hTRoot = AddTreeItem3((HTREEITEM)NULL, _T("B"), (HTREEITEM)TVI_ROOT, 0);
	hTItem = AddTreeItem3(hTRoot, _T("b"), (HTREEITEM)TVI_FIRST, 4);
	hTItem = AddTreeItem3(hTRoot, _T("c"), (HTREEITEM)TVI_LAST,5);
	hTItem = AddTreeItem3(hTRoot, _T("d"), (HTREEITEM)TVI_LAST,2);
	
	hTItem = AddTreeItem3(hTItem, _T("f"), (HTREEITEM)TVI_LAST,0);
	hTItem = AddTreeItem3(hTItem, _T("g"), (HTREEITEM)TVI_LAST, 3);
	hTItem = AddTreeItem3(hTItem, _T("h"), (HTREEITEM)TVI_LAST,2);
	hTItem = AddTreeItem3(hTItem, _T("i"), (HTREEITEM)TVI_LAST,4);
	
	//m_treeCtrl3.Expand(hTRoot ,TVE_EXPAND);
	hTRoot = AddTreeItem3((HTREEITEM)NULL, _T("C"), (HTREEITEM)TVI_ROOT, 0);
	hTItem = AddTreeItem3(hTRoot, _T("c"), (HTREEITEM)TVI_FIRST, 5);
	hTItem = AddTreeItem3(hTRoot, _T("d"), (HTREEITEM)TVI_LAST,2);
	hTItem = AddTreeItem3(hTRoot, _T("e"), (HTREEITEM)TVI_LAST,5); 

	hTItem2 = AddTreeItem3(hTItem, _T("e1"), (HTREEITEM)TVI_LAST,1);
	hTItem2 = AddTreeItem3(hTItem, _T("e2"), (HTREEITEM)TVI_LAST,4);
	hTItem2 = AddTreeItem3(hTItem, _T("e3"), (HTREEITEM)TVI_LAST,4);
	hTItem2 = AddTreeItem3(hTItem, _T("e4"), (HTREEITEM)TVI_LAST,4);
	
	//m_treeCtrl3.Expand(hTRoot ,TVE_EXPAND);
	hTRoot = AddTreeItem3((HTREEITEM)NULL, _T("D"), (HTREEITEM)TVI_ROOT, 0);
	hTItem = AddTreeItem3(hTRoot, _T("d"), (HTREEITEM)TVI_FIRST, 4);
	hTItem = AddTreeItem3(hTRoot, _T("f"), (HTREEITEM)TVI_LAST,5);
	
	hTItem2 = AddTreeItem3(hTItem, _T("f1"), (HTREEITEM)TVI_LAST,1);
	hTItem2 = AddTreeItem3(hTItem, _T("f2"), (HTREEITEM)TVI_FIRST, 3);
	hTItem2 = AddTreeItem3(hTItem, _T("f3"), (HTREEITEM)TVI_LAST,2);
	hTItem2 = AddTreeItem3(hTItem, _T("f4"), (HTREEITEM)TVI_LAST,1);
	

	//m_treeCtrl3.Expand(hTRoot ,TVE_EXPAND);
	


}





void CWorkspaceTabView::printWSPTree2()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  WorkspaceTree 2 *******"));
	//Print map container
	for( CMainFrame::g_mWSPTree2::const_iterator iter = pMainFrame->gmWSPTree2.begin(); iter!= pMainFrame->gmWSPTree2.end(); ++iter)
	{
		CString strNode =_T("NODE_");
		CString strItem =_T("Item: ");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Node Name - HTREEITEM  *******"));
		strNode +=  iter->first;
		pMainFrame->m_wndOutputTabView.AddMsg1(strNode);
		int hItem = (int)iter->second;
		strItem +=  _itot( hItem, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strItem);
			
	}

}


void CWorkspaceTabView::printWSPTree3()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  WorkspaceTree 3 *******"));
	//Print map container
	for( CMainFrame::g_mWSPTree3::const_iterator iter = pMainFrame->gmWSPTree3.begin(); iter!= pMainFrame->gmWSPTree3.end(); ++iter)
	{
		CString strNode =_T("NODE_");
		CString strItem =_T("Item: ");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Node Name - HTREEITEM  *******"));
		strNode +=  iter->first;
		pMainFrame->m_wndOutputTabView.AddMsg1(strNode);
		int hItem = (int)iter->second;
		strItem +=  _itot( hItem, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strItem);
			
	}

}


void CWorkspaceTabView::DeleteTree1(HTREEITEM hItem)
{
	m_treeCtrl1.DeleteItem(hItem);

}

void CWorkspaceTabView::DeleteTree2(HTREEITEM hItem)
{
	m_treeCtrl2.DeleteItem(hItem);

}

void CWorkspaceTabView::DeleteAllTree1()
{

	m_treeCtrl1.DeleteAllItems();
}

void CWorkspaceTabView::DeleteAllTree2()
{

	m_treeCtrl2.DeleteAllItems();
}



void CWorkspaceTabView::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	HTREEITEM htreeItemSel = m_treeCtrl1.GetSelectedItem();
	if( htreeItemSel != NULL )
	{
		CWorkspaceLocation loc;
		

		int f = loc.findLocationMembers( htreeItemSel );
		if( f != NOT_FOUND )
		{
			long pos = loc.m_Position;
			int line = loc.m_Line;
			int categ = loc.m_Category;
			CString path = loc.m_FilePath;
			CString name = loc.m_NodeName;

			if( path == _T("") )
			{
				CString csStr =  m_treeCtrl1.GetItemText( htreeItemSel );
				//AfxMessageBox(csStr);
				CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
				pMainFrame->m_wndOutputTabView.AddMsg1(_T("WARNING: The workspace element  (") + csStr + _T(")   do not belong to Aipi knowledge files. Check the code."));
				return;
			}


			//AfxMessageBox(path);
			//AfxMessageBox(name);

			CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
			CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
			CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
			ASSERT(pView);
			
			CAIPIEditorDoc* pDoc = (CAIPIEditorDoc*)pView->GetDocument();
			ASSERT_VALID(pDoc);
			CString filePath = pDoc->GetPathName();
			//CString fileName = pDoc->GetTitle();
			//AfxMessageBox(filePath);
			//AfxMessageBox(strFileName);
			if( filePath == path )
			{
				CScintillaCtrl& rCtrl = pView->GetCtrl();
				// Reset Scintilla Markers 
				rCtrl.MarkerDeleteAll(0);

				// Initilaize markers
				rCtrl.MarkerDefine(0, SC_MARK_ARROW);
				rCtrl.MarkerSetFore(0, RGB( 128, 128, 128 ));
				rCtrl.MarkerSetBack(0, RGB( 128, 128, 128 ));
		
				// Set error marker to proper line
				rCtrl.GotoLine(line );
				rCtrl.MarkerAdd((line), 0);
				
				WSPCheckPositionChange( htreeItemSel, name, path, categ ); 
				//loc.printLocation();
				//Set the cursor position in the GUI
				//int len = name.GetLength();
				//rCtrl.SetFocus();
				//rCtrl.SetSel(pos - len, pos);

				
				return;
			}
			
			CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
			BOOL alreadyOpen = pApp->SetDocumentView(path);
		
			
			if ( alreadyOpen == FALSE )
			{
				//AfxMessageBox(_T("Not Open"));
				
				pApp->m_pAIPIEditorDocTemplate->OpenDocumentFile(path);
				if( pApp == NULL )
				{
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->m_wndOutputTabView.AddMsg1(_T("ERROR: The file  (") + path + _T(")   could not be linked. Check if the file is not corrupted."));
					return;
				}

						
				pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
				pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
				pView = (CScintillaView*) pChild->GetActiveView();
				ASSERT(pView);
			
			
				CScintillaCtrl& rCtrl = pView->GetCtrl();
				// Reset Scintilla Markers 
				rCtrl.MarkerDeleteAll(0);

				// Initilaize markers
				rCtrl.MarkerDefine(0, SC_MARK_ARROW);
				rCtrl.MarkerSetFore(0, RGB( 128, 128, 128 ));
				rCtrl.MarkerSetBack(0, RGB( 128, 128, 128 ));
					
				// Set error marker to proper line
				rCtrl.GotoLine(line );
				rCtrl.MarkerAdd((line), 0);

				WSPCheckPositionChange( htreeItemSel, name, path, categ ); 
				//loc.printLocation();
			
			}
			else
			{
				//AfxMessageBox(_T("Already Open"));
				//AfxMessageBox(path);
				//pApp->SetDocumentView(path);

				
				pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
				pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
				pView = (CScintillaView*) pChild->GetActiveView();
				ASSERT(pView);
			
			
				CScintillaCtrl& rCtrl = pView->GetCtrl();
				// Reset Scintilla Markers 
				rCtrl.MarkerDeleteAll(0);

				// Initilaize markers
				rCtrl.MarkerDefine(0, SC_MARK_ARROW);
				rCtrl.MarkerSetFore(0, RGB( 128, 128, 128 ));
				rCtrl.MarkerSetBack(0, RGB( 128, 128, 128 ));
					
				// Set error marker to proper line
				rCtrl.GotoLine(line );
				rCtrl.MarkerAdd((line), 0);

				WSPCheckPositionChange( htreeItemSel, name, path, categ ); 
				//loc.printLocation();
				
			}
			
			//Set the cursor position in the GUI
			//int len = name.GetLength();
			//rCtrl.SetFocus();
			//rCtrl.SetSel(pos - len, pos);
		

		}
		else
		{
			CString csStr =  m_treeCtrl1.GetItemText( htreeItemSel );
			//AfxMessageBox(csStr);
			CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("WARNING: The workspace element  (") + csStr + _T(")   do not belong to Aipi knowledge files. Check the code."));

		}
		
		
		
		BOOL bFound = FALSE;
	}

	*pResult = 0;

}	


void CWorkspaceTabView::OnSelchangedTree2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	HTREEITEM htreeItemSel = m_treeCtrl2.GetSelectedItem();
	CString csTmp =  m_treeCtrl2.GetItemText( htreeItemSel );
	CString csStr = "Usted seleccionó ";
	csStr += csTmp;
	
	//AfxMessageBox(csStr);
	
	*pResult = 0;

	// end OnSelchangedTree()

}	

void CWorkspaceTabView::OnSelchangedTree3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	HTREEITEM htreeItemSel = m_treeCtrl3.GetSelectedItem();
	CString csTmp =  m_treeCtrl3.GetItemText( htreeItemSel );
	CString csStr = "Usted seleccionó ";
	csStr += csTmp;
	//AfxMessageBox(csStr);
	
	*pResult = 0;

	// end OnSelchangedTree()

}	




void CWorkspaceTabView::OnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    
	//
	// This method just checks the root & sets the image to be an open
	// or closed book, depending on the state of the root item...
	//
	HTREEITEM hTRoot = m_treeCtrl1.GetRootItem();
	UINT uiRet = m_treeCtrl1.GetItemState(hTRoot,TVIS_EXPANDED );
	if(uiRet & TVIS_EXPANDED)
		m_treeCtrl1.SetItemImage( hTRoot, 1, 1);
	else
		m_treeCtrl1.SetItemImage( hTRoot, 0, 0);

		
	*pResult = 0;

}

void CWorkspaceTabView::OnItemexpandedTree2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	//
	// This method just checks the root & sets the image to be an open
	// or closed book, depending on the state of the root item...
	//
	HTREEITEM hTRoot = m_treeCtrl2.GetRootItem();
	UINT uiRet = m_treeCtrl2.GetItemState(hTRoot,TVIS_EXPANDED );
	if(uiRet & TVIS_EXPANDED)
		m_treeCtrl2.SetItemImage( hTRoot, 1, 1);
	else
		m_treeCtrl2.SetItemImage( hTRoot, 0, 0);

		
	*pResult = 0;
}

void CWorkspaceTabView::OnItemexpandedTree3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	//
	// This method just checks the root & sets the image to be an open
	// or closed book, depending on the state of the root item...
	//
	HTREEITEM hTRoot = m_treeCtrl3.GetRootItem();
	UINT uiRet = m_treeCtrl3.GetItemState(hTRoot,TVIS_EXPANDED );
	if(uiRet & TVIS_EXPANDED)
		m_treeCtrl3.SetItemImage( hTRoot, 1, 1);
	else
		m_treeCtrl3.SetItemImage( hTRoot, 0, 0);

		
	*pResult = 0;
}





void CWorkspaceTabView::Serialize(CArchive& ar) 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndOutputTabView.DeleteAllEdit1();
	//AfxMessageBox(_T("Serialize"));
	//pMainFrame->WSPTree1Read(g_projectName, g_projectRoot);

	if (ar.IsStoring())
	{	// storing code
		
		WriteTreeCtrlContent(ar, m_treeCtrl1);
		WriteTreeCtrlContent(ar, m_treeCtrl2);
		WriteTreeCtrlContent(ar, m_treeCtrl2);
	}
	else
	{	
		//AfxMessageBox(_T("entro"));
		//AfxMessageBox(g_projectName);
		//AfxMessageBox(g_projectRoot);
		/*
		int r = CheckProjectFile( g_projectName, g_projectRoot);
		if( r == NOT_FOUND )
		return;
		*/	
		// loading code
		ReadTreeCtrlContent(ar, m_treeCtrl1);
		ReadTreeCtrlContent(ar, m_treeCtrl2);
		ReadTreeCtrlContent(ar, m_treeCtrl3);
	}
	
	//CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	//pMainFrame->m_wndOutputTabView.DeleteAllEdit1();
	//int n = pMainFrame->gmWSPTree1.size();

	//CWorkspaceTree1 wsp1;
	//wsp1.printWSPTree1();
	//printWSPTree2();
	//printWSPTree3();
}


void CWorkspaceTabView::RecursiveWriteItems(CArchive& ar, CTreeCtrl& refCtrl, HTREEITEM hItem)
{
	//Loop through each item at the level of hItem (eg,
	// hItem and all of its siblings)
	int nImage = 0;
	int nSelectedImage = 0;
	int	line = 0;
	long pos = 0;	
	CString sFilePath = _T("");
	CString sFileName = _T("");
	//CString strAipiName = _T("");
	CWorkspaceLocation loc;
	
	do
	{
		CString strName = refCtrl.GetItemText(hItem);
		BOOL bExpanded = (refCtrl.GetItemState(hItem, TVIS_EXPANDED) != 0 );
		
		int f = loc.findLocationMembers( hItem);
		if( f != NOT_FOUND )
		{
			line = loc.m_Line;
			pos = loc.m_Position;
			sFilePath = loc.m_FilePath;
			strName = loc.m_NodeName;
			
			//AfxMessageBox(_T("FOUND"));
			//AfxMessageBox(loc.m_NodeName);
			//AfxMessageBox(sFilePath);
			
		}
	
			
		if( bExpanded )
		{
			//CString s;
			//s.Format(_T("bExpanded  %u"), bExpanded);
			//TRACE(str);
			//AfxMessageBox(str);
			//AfxMessageBox(s);
		}
		
		refCtrl.GetItemImage(hItem, nImage, nSelectedImage);

		ar << (BYTE) recordRegular;
		ar << strName;
		ar << nImage;
		ar << nSelectedImage;
		ar << bExpanded;
		ar << sFilePath;
		ar << sFileName;
		ar << line;
		ar << pos;
		
		//AfxMessageBox(strName);
		//AfxMessageBox(sFilePath);

		/*
		CString st;
		st.Format(_T("WRITE RECURSIVE HTREEITEM Item...%d  " ), hItem);
		AfxMessageBox(st);
		*/

		//SAMPLE: if a given item has children, mark a push in the indentation
		// level and recurse to get all those children
		if (refCtrl.ItemHasChildren(hItem))
		{
			ar << (BYTE) recordPush;
			
			RecursiveWriteItems(ar, refCtrl, refCtrl.GetChildItem(hItem));
		}
	}
	
	while ((hItem = refCtrl.GetNextSiblingItem(hItem)) != NULL);

	//SAMPLE: done working at this level--mark a pop and return
	// either to our caller or the next less nested level.
	ar << (BYTE) recordPop;
}


void CWorkspaceTabView::WriteTreeCtrlContent(CArchive& ar, CTreeCtrl& refCtrl)
{
	
	UINT nCount = refCtrl.GetCount();
	ar << nCount;

	// short circuit the zero-element case
	if (nCount == 0)
		return;

	
	//SAMPLE: there's real work to do! Start recursing at the root item
	HTREEITEM hItem = refCtrl.GetRootItem();
	//HTREEITEM hItem = hTProjectRoot;
	/*
	CString str;
	str.Format(_T("Root HTREEITEM...%d  " ), hItem);
	AfxMessageBox(str);
	*/

	RecursiveWriteItems(ar, refCtrl, hItem);

	

	
}

void CWorkspaceTabView::ReadTreeCtrlContent(CArchive& ar, CTreeCtrl& refCtrl)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CString sz, s;
	CString sFilePath = _T("");
	CString sFileName = _T(""); 

	CString sCategClass = g_projectName + _T(" Classes");
	CString sCategFunc = g_projectName + _T(" Functions");
	CString sCategQuery = g_projectName + _T(" Queries");
	CString sCategRule = g_projectName + _T(" Rules");
    CString sCategVar = g_projectName + _T(" Variables");
    CString sParentName = _T("");
	
	CWorkspaceTree1 wsp;
	CWorkspaceLocation loc;
	int n = 0;
	//TCHAR buffer[8];
	

	//SAMPLE: start out by deleting all the content from the control
	refCtrl.DeleteAllItems();
	UINT ctrlID = refCtrl.GetDlgCtrlID();
	switch (ctrlID)
	{
		case IDC_TREEVIEWCTRL1:
			wsp.clearWSPTree1();
			loc.clearLocation();
			break;
		case IDC_TREEVIEWCTRL2:
			pMainFrame->gmWSPTree2.clear();
			break;
		case IDC_TREEVIEWCTRL3:
			pMainFrame->gmWSPTree3.clear();
			break;
	}
	
	//SAMPLE: figure out if the control was empty when it was stored
	UINT nCount;
	ar >> nCount;

	//SAMPLE: if so, just short circuit the zero-element case
	if (nCount == 0)
		return;

	//SAMPLE: otherwise, start sucking data in!
	m_nIndex = 0;
	m_hItems[m_nIndex] = (HTREEITEM)TVI_ROOT;
	HTREEITEM hAfter = (HTREEITEM)TVI_FIRST;
	
	CString strName = _T("");
	BOOL bExpanded = false;
	int nImage = 0;
	int nSelectedImage = 0;
	int line = 0;
	long pos = 0;
	int categ = 0;
	CString st;

	
	//SAMPLE: while we're above the root, keep reading
	while (m_nIndex >= 0)
	{
		//SAMPLE: get a record type
		BYTE byteType;
		ar >> byteType;
		
		switch (byteType)
		{
		//SAMPLE: for a regular record, we'll just insert it into
		// the control. Note how we'll insert after the most recently
		// added item, and we'll insert as a child of the item on
		// our hItems stack.
		case recordRegular:
			{
				ar >> strName;
				ar >> nImage;
				ar >> nSelectedImage;
				ar >> bExpanded;
				ar >> sFilePath;
				ar >> sFileName;
				ar >> line;
				ar >> pos;

				

				/*
				AfxMessageBox(_T("REGULAR Name:..."));
				AfxMessageBox(strName);
				*/
				/*
				st.Format(_T("REGULAR Index:...%d" ), m_nIndex);
				AfxMessageBox(st);
				st.Format(_T("REGULAR Parent:...%d  " ), m_hItems[m_nIndex]);
				AfxMessageBox(st);
				st.Format(_T("REGULAR hAfter:...%d  " ), hAfter);
				AfxMessageBox(st);
				*/
				
				//Save text and index of all CTreeCtrl1 items
				UINT ctrlID = refCtrl.GetDlgCtrlID();
				switch (ctrlID)
				{
				case IDC_TREEVIEWCTRL1:
					
					if( m_nIndex < 2 )
					{
						break;
					}
					
					
					//AfxMessageBox(_T("Entro ..."));
					sParentName = refCtrl.GetItemText(m_hItems[m_nIndex]);
					//AfxMessageBox(sParentName);
					//st.Format(_T("hAfter:...%d  " ), hAfter);
					//AfxMessageBox(st);
				
					
					if( sParentName == sCategClass )
					{
						categ = AIPI_CLASS;
					}
					else if ( sParentName == sCategFunc )
					{
						categ = AIPI_FUNCTION;
					}
					else if ( sParentName == sCategQuery )
					{
						categ = AIPI_QUERY;
					}
					else if( sParentName == sCategRule )
					{
						categ = AIPI_RULE; 
					}
					else if ( sParentName == sCategVar )
					{
						categ = AIPI_VARIABLE;
					}
					
				

					//hAfter = refCtrl.InsertItem(strName, nImage, nSelectedImage, m_hItems[m_nIndex], hAfter);
					//st.Format(_T("REGULAR New hAfter:...%d  " ), hAfter);
					//AfxMessageBox(st);
				
					
					break;
				case IDC_TREEVIEWCTRL2:
					//pMainFrame->gmWSPTree2.insert(CMainFrame::g_mWSPTree2::value_type(str, hAfter));
					break;
				case IDC_TREEVIEWCTRL3:
					//pMainFrame->gmWSPTree3.insert(CMainFrame::g_mWSPTree3::value_type(str, hAfter));
					break;
				}

				/*
				AfxMessageBox(_T("REGULAR Name:..."));
				AfxMessageBox(strName);
				st.Format(_T("REGULAR Index:...%d" ), m_nIndex);
				AfxMessageBox(st);
				st.Format(_T("REGULAR Parent:...%d  " ), m_hItems[m_nIndex]);
				AfxMessageBox(st);
				st.Format(_T("REGULAR hAfter:...%d  " ), hAfter);
				AfxMessageBox(st);
				*/

				hAfter = refCtrl.InsertItem(strName, nImage, nSelectedImage, m_hItems[m_nIndex], hAfter);

				if( strName == sCategClass )
				{
					hTProjectClass = hAfter;
					//st.Format(_T("CLASS hAfter:...%d  " ), hAfter);
					//AfxMessageBox(st);
						
				}
				else if ( strName == sCategFunc )
				{
					hTProjectFunction = hAfter;
				}
				else if ( strName == sCategQuery )
				{
					hTProjectQuery = hAfter; 

				}
				else if( strName == sCategRule )
				{
					hTProjectRule = hAfter;
				
				}
				else if( strName == sCategVar )
				{
					hTProjectVariable = hAfter;
				}

				//st.Format(_T("REGULAR New hAfter:...%d  " ), hAfter);
				//AfxMessageBox(st);
				/*
				switch(m_nIndex)
				{
				case 0:
					hTProjectRoot = m_hItems[m_nIndex];
					st.Format(_T("ROOT hAfter:...%d  " ), hAfter);
					AfxMessageBox(st);
					break;
				case 1:
					switch(categ)
					{
					case AIPI_CLASS:
						hTProjectClass = m_hItems[m_nIndex];
						st.Format(_T("CLASS hAfter:...%d  " ), hAfter);
						AfxMessageBox(st);
						break;
					case AIPI_FUNCTION:
						hTProjectFunction = hAfter;
						break;
					case AIPI_QUERY:
						hTProjectQuery = hAfter;
						break;
					case AIPI_RULE:
						hTProjectRule = hAfter;
						break;
					case AIPI_VARIABLE:
						hTProjectVariable = hAfter;
						break;
					
					}
					break;
				}
				
				*/
				
				
				
				if( m_nIndex >= 2 )
				{
					//AfxMessageBox(strName);
					//AfxMessageBox(sFileName);
					//AfxMessageBox(sFilePath);
					loc.addLocation(hAfter, pos, line, strName, sFilePath, categ ); 
					wsp.addElement(strName, hAfter, sFilePath, sFileName);
				}

				
								
				if( bExpanded)
				{
					
					refCtrl.Expand(m_hItems[m_nIndex], TVE_EXPAND);
					
					/*
					CString s;
					s.Format(_T("bExpanded  %u"), bExpanded);
					AfxMessageBox(str);
					AfxMessageBox(s);
					sz =  _itot( m_nIndex, buffer, 10 );
					AfxMessageBox(_T("Index RECORD REGULAR...") + sz);
					*/
				
				}
				
					
			}
			break;

		//SAMPLE: if we're going one deeper, we'll need to bump the stack
		// and reset the insertion flag.  Note that this sample can only
		// handle 10 levels of items in the control. You might want to fix
		// this code to use a dynamic array (eg, a CArray). Whatever you do,
		// the error recovery here needs to be a bit better!
		case recordPush:
			ASSERT( m_nIndex < 10 );
			/*
			if( bExpanded)
			{
				AfxMessageBox(_T("Hola"));
				refCtrl.Expand(m_hItems[m_nIndex+1], TVE_EXPAND);
			}
			*/
			

			m_hItems[++m_nIndex] = hAfter;
			hAfter = TVI_FIRST;
			
			/*
			AfxMessageBox(_T("PUSH Name:,,,"));
			AfxMessageBox(str);
			st.Format(_T("POP Index:...%d" ), m_nIndex);
			AfxMessageBox(st);
			st.Format(_T("PUSH hAfter:...%d  " ), hAfter);
			AfxMessageBox(st);
			*/
			
			//sz =  _itot( m_nIndex, buffer, 10 );
			//AfxMessageBox(_T("Index Record Push...") + sz);
			//s.Format(_T("bExpanded Record Push  %u"), bExpanded);
			//AfxMessageBox(str);
			//AfxMessageBox(s);
			

			break;

		//SAMPLE: if we're going one less deep, we'll pop the stack
		case recordPop:
			
			
			
			m_nIndex--;

			/*
			AfxMessageBox(_T("POP Name:,,,"));
			AfxMessageBox(str);
			st.Format(_T("POP Index:...%d" ), m_nIndex);
			AfxMessageBox(st);
			st.Format(_T("POP hAfter:...%d  " ), hAfter);
			AfxMessageBox(st);
			*/	
			
			break;

		default:
			{
			
			//TODO: pick a better exception type
			AfxMessageBox(_T("Memory problems in Aipi project Workspace serialization."));
			ASSERT(FALSE);
			AfxThrowMemoryException();
			}
		}
	}


//loc.printLocation();
	
}


int CWorkspaceTabView::CheckProjectFile(CString name, CString path)
{
	SetCurrentDirectory(path); 
	
	CFileFind finder;
	bool f = finder.FindFile(name);


	if( f == FOUND )
	{
		/*	
		CString str;
		str.Format(_T("Not Found" ), NOT_FOUND);
		AfxMessageBox(str);
		*/
		return NOT_FOUND;

	}
/*
	CString str;
	str.Format(_T("Found" ), FOUND);
	AfxMessageBox(str);
*/
return FOUND;
	

//BOOL bContinue;
	//CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	/*
	if( bContinue = finder.FindFile(name))
	{
		while(bContinue)
		{
			bContinue = finder.FindNextFile();
			CString strName = finder.GetFileName();
			CString strPath = finder.GetFilePath();
			pMainFrame->m_wndOutputTabView.AddMsg1(strName);		
		}

	}
	*/
  
}




BOOL CWorkspaceTabView::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//m_TabViewContainer.OnSelchange(pNMHDR, pResult);

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	
	*pResult = 0;
	int iCurTab = m_TabViewContainer.GetActivePageIndex();	// get tab 
	//AfxMessageBox(_T("Hello!!!"));			
			
	
	
	switch(iCurTab)
	{
		
		default:
		
		case 0:		
			//Page 1
			//AfxMessageBox(_T("Hello!!!"));			
			
			break;
		case 1:		// Data
			//Page 1
			//AfxMessageBox(_T("2 Hello!!!"));	
			break;
			
	}	// end switch on tab selection
	
	return FALSE;
}



	
	
