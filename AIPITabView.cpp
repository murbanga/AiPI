// AIPITabView.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "AIPITabView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAIPITabView dialog
IMPLEMENT_DYNAMIC(CAIPITabView, COXSizeDialogBar)


CAIPITabView::CAIPITabView(CWnd* pParent /*=NULL*/)
: COXSizeDialogBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	//{{AFX_DATA_INIT(CAIPITabView)
	m_iMaxRange = 0;
	m_iMinRange = 0;
	//}}AFX_DATA_INIT
	m_iMinRange_LHS = 0;
	m_iMaxRange_LHS = 0;
	m_iMinRange_RHS = 0;
	m_iMaxRange_RHS = 0;
	m_iMinRange_WM = 0;
	m_iMaxRange_WM = 0;
	m_iMinRange_CLink = 0;
	m_iMaxRange_CLink = 0;
	m_iMinRange_Agenda = 0;
	m_iMaxRange_Agenda = 0;
	m_iMinRange_AM = 0;
	m_iMaxRange_AM = 0;
	m_iMinRange_BM = 0;
	m_iMaxRange_BM = 0;
	m_iMinRange_BM_TK = 0;
	m_iMaxRange_BM_TK = 0;
	m_iMinRange_RETE = 0;
	m_iMaxRange_RETE = 0;

	m_bRejectEditAttempts = TRUE;
    m_bRejectEditChanges = TRUE;


}

CAIPITabView::~CAIPITabView()
{
	
	
	//These are deleted on CRollUpCtrl class
/*
	delete pEditPage;
	delete pInsertPage;
	delete pFormatPage;
	delete pOptionsPage;
	delete pCellSizePage;
	*/
}

void CAIPITabView::DoDataExchange(CDataExchange* pDX)
{
	
	COXSizeDialogBar::DoDataExchange(pDX);

	
	//{{AFX_DATA_MAP(CAIPITabView)
	DDX_Control(pDX, IDC_STC_LABEL_RANGE, m_stcLabelRange);
	DDX_Control(pDX, IDC_BTN_RANGE, m_btnViewRange);
	DDX_Control(pDX, IDC_BTN_ALL, m_btnViewAll);
	DDX_Control(pDX, IDC_AIPITAB, m_TabCtrl);
	DDX_Control(pDX, IDC_STC_RANGE, m_Stc_Range);
	DDX_Control(pDX, IDC_STC_AIPI_DATA, m_Stc_Aipi_Data);
	DDX_Text(pDX, IDC_EDIT_MAX_RANGE, m_iMaxRange);
	DDX_Text(pDX, IDC_EDIT_MIN_RANGE, m_iMinRange);
	//}}AFX_DATA_MAP
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	DDX_Control(pDX, IDC_GRID_LHS, pMainFrame->m_GridLHS);
	DDX_Control(pDX, IDC_GRID_RHS, pMainFrame->m_GridRHS);
	DDX_Control(pDX, IDC_GRID_WM, pMainFrame->m_GridWM);
	DDX_Control(pDX, IDC_GRID_COND_LINK, pMainFrame->m_GridCondLink);
	DDX_Control(pDX, IDC_GRID_AGENDA, pMainFrame->m_GridAgenda);
	DDX_Control(pDX, IDC_GRID_AM, pMainFrame->m_GridAM);
	DDX_Control(pDX, IDC_GRID_BM, pMainFrame->m_GridBM);
	DDX_Control(pDX, IDC_GRID_BM_TK, pMainFrame->m_GridBM_TK);
	DDX_Control(pDX, IDC_GRID_RETE, pMainFrame->m_GridRETE);
}


BEGIN_MESSAGE_MAP(CAIPITabView, COXSizeDialogBar)
	//{{AFX_MSG_MAP(CAIPITabView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_AIPITAB, OnSelchangeAipiTab)
	ON_BN_CLICKED(IDC_BTN_RANGE, OnBtnRange)
	ON_BN_CLICKED(IDC_BTN_ALL, OnBtnAll)
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,TabToolTips)
	//GRID_PM	
	ON_NOTIFY(NM_DBLCLK, IDC_GRID_LHS, OnGridDblClick)
    ON_NOTIFY(NM_CLICK, IDC_GRID_LHS, OnGridClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_LHS, OnGridRClick)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID_LHS, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID_LHS, OnGridEndEdit)
	ON_NOTIFY(GVN_SELCHANGING, IDC_GRID_LHS, OnGridStartSelChange)
	ON_NOTIFY(GVN_SELCHANGED, IDC_GRID_LHS, OnGridEndSelChange)
	ON_NOTIFY(GVN_BEGINDRAG, IDC_GRID_LHS, OnGridBeginDrag)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_LHS, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_LHS, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_LHS, OnGridRClick)
	//GRID_WM	
	ON_NOTIFY(NM_DBLCLK, IDC_GRID_WM, OnGridDblClick)
    ON_NOTIFY(NM_CLICK, IDC_GRID_WM, OnGridClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_WM, OnGridRClick)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID_WM, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID_WM, OnGridEndEdit)
	ON_NOTIFY(GVN_SELCHANGING, IDC_GRID_WM, OnGridStartSelChange)
	ON_NOTIFY(GVN_SELCHANGED, IDC_GRID_WM, OnGridEndSelChange)
	ON_NOTIFY(GVN_BEGINDRAG, IDC_GRID_WM, OnGridBeginDrag)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_WM, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_WM, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_WM, OnGridRClick)
	//GRID_AM	
	ON_NOTIFY(NM_DBLCLK, IDC_GRID_AM, OnGridDblClick)
    ON_NOTIFY(NM_CLICK, IDC_GRID_AM, OnGridClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_AM, OnGridRClick)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID_AM, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID_AM, OnGridEndEdit)
	ON_NOTIFY(GVN_SELCHANGING, IDC_GRID_AM, OnGridStartSelChange)
	ON_NOTIFY(GVN_SELCHANGED, IDC_GRID_AM, OnGridEndSelChange)
	ON_NOTIFY(GVN_BEGINDRAG, IDC_GRID_AM, OnGridBeginDrag)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_AM, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_AM, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_AM, OnGridRClick)
	//GRID_BM	
	ON_NOTIFY(NM_DBLCLK, IDC_GRID_BM, OnGridDblClick)
    ON_NOTIFY(NM_CLICK, IDC_GRID_BM, OnGridClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_BM, OnGridRClick)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID_BM, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID_BM, OnGridEndEdit)
	ON_NOTIFY(GVN_SELCHANGING, IDC_GRID_BM, OnGridStartSelChange)
	ON_NOTIFY(GVN_SELCHANGED, IDC_GRID_BM, OnGridEndSelChange)
	ON_NOTIFY(GVN_BEGINDRAG, IDC_GRID_BM, OnGridBeginDrag)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_BM, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_BM, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_BM, OnGridRClick)
	//GRID_BM_TK	
	ON_NOTIFY(NM_DBLCLK, IDC_GRID_BM_TK, OnGridDblClick)
    ON_NOTIFY(NM_CLICK, IDC_GRID_BM_TK, OnGridClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_BM_TK, OnGridRClick)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID_BM_TK, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID_BM_TK, OnGridEndEdit)
	ON_NOTIFY(GVN_SELCHANGING, IDC_GRID_BM_TK, OnGridStartSelChange)
	ON_NOTIFY(GVN_SELCHANGED, IDC_GRID_BM_TK, OnGridEndSelChange)
	ON_NOTIFY(GVN_BEGINDRAG, IDC_GRID_BM_TK, OnGridBeginDrag)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_BM_TK, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_BM_TK, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_BM_TK, OnGridRClick)
	//GRID_RETE	
	ON_NOTIFY(NM_DBLCLK, IDC_GRID_RETE, OnGridDblClick)
    ON_NOTIFY(NM_CLICK, IDC_GRID_RETE, OnGridClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_RETE, OnGridRClick)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID_RETE, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID_RETE, OnGridEndEdit)
	ON_NOTIFY(GVN_SELCHANGING, IDC_GRID_RETE, OnGridStartSelChange)
	ON_NOTIFY(GVN_SELCHANGED, IDC_GRID_RETE, OnGridEndSelChange)
	ON_NOTIFY(GVN_BEGINDRAG, IDC_GRID_RETE, OnGridBeginDrag)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_RETE, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_RETE, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID_RETE, OnGridRClick)


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAIPITabView message handlers
void CAIPITabView::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	COXSizeDialogBar::OnUpdateCmdUI(pTarget,FALSE);
}


BOOL CAIPITabView::InitLayoutManager()
{
	
	BOOL retval = TRUE;

	if(!m_LayoutManager.IsAttached()) 
	{
		m_LayoutManager.Attach(this);

		Init_Page();
		
	}

	return retval;
	
}

void CAIPITabView::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
{
	
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	m_LayoutManager.RedrawLayout();
}


void CAIPITabView::CreateTab()
{
	
	TC_ITEM pTabCtrlItem;	// tab control item structure
	
    pTabCtrlItem.mask = TCIF_TEXT | TCIF_IMAGE;
	pTabCtrlItem.iImage = 0;
	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();

	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		pTabCtrlItem.pszText = _T("LHS");
		break;
	default:
		pTabCtrlItem.pszText = _T("LHS");
		break;
	}
	
	m_TabCtrl.InsertItem( 0, &pTabCtrlItem );	// first tab

	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		pTabCtrlItem.pszText = _T("RHS");
		break;
	default:
		pTabCtrlItem.pszText = _T("RHS");
		break;
	}
	pTabCtrlItem.iImage = 1;
	m_TabCtrl.InsertItem( 1, &pTabCtrlItem );	// first tab
	
	
	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		pTabCtrlItem.pszText = _T("WM");
		break;
	default:
		pTabCtrlItem.pszText = _T("WM");
		break;
	}

	pTabCtrlItem.iImage = 2;
	m_TabCtrl.InsertItem( 2, &pTabCtrlItem );	// second tab

	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		pTabCtrlItem.pszText = _T("Enlaces");
		break;
	default:
		pTabCtrlItem.pszText = _T("Links");
		break;
	}

	pTabCtrlItem.iImage = 3;
	m_TabCtrl.InsertItem( 3, &pTabCtrlItem );	// second tab
	
	
	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		pTabCtrlItem.pszText = _T("Agenda");
		break;
	default:
		pTabCtrlItem.pszText = _T("Agenda");
		break;
	}
	
	pTabCtrlItem.iImage = 4;
	m_TabCtrl.InsertItem( 4, &pTabCtrlItem );	// third tab
	

	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		pTabCtrlItem.pszText = _T("AM");
		break;
	default:
		pTabCtrlItem.pszText = _T("AM");
		break;
	}
		
	pTabCtrlItem.iImage = 5;
	m_TabCtrl.InsertItem( 5, &pTabCtrlItem );	// third tab
	
	
	switch(dwLanguageID)
	{
		case LANG_SPANISH:
		pTabCtrlItem.pszText = _T("BM");
		break;
		default:
		pTabCtrlItem.pszText = _T("BM");
		break;
		}

	pTabCtrlItem.iImage = 6;
	m_TabCtrl.InsertItem( 6, &pTabCtrlItem );	// third tab
	
	
	switch(dwLanguageID)
	{
		case LANG_SPANISH:
		pTabCtrlItem.pszText = _T("BM/TK");
		break;
		default:
		pTabCtrlItem.pszText = _T("BM/TK");
		break;
	}


	pTabCtrlItem.iImage = 7;
	m_TabCtrl.InsertItem( 7, &pTabCtrlItem );	// third tab

	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		pTabCtrlItem.pszText = _T("RETE");
		break;
	default:
		pTabCtrlItem.pszText = _T("RETE");
		break;
	}
		
	pTabCtrlItem.iImage = 8;
	m_TabCtrl.InsertItem( 8, &pTabCtrlItem );	// third tab
	
	


	//	do image list here
	//
	m_TabImageList.Create(IDB_TABAIPIIMAGES, 17, 1, COLORREF(0xc0c0c0));	
	m_TabCtrl.SetImageList(&m_TabImageList);

	//
	//	init the tab control & edit box
	//
	NMHDR nmHDR;
	LRESULT pResult;
	OnSelchangeAipiTab(&nmHDR,  &pResult);	// default to floppy
}



BOOL CAIPITabView::TabToolTips(UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();

	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	UINT nID = pTTT->uFlags;
	//
	if(pTTT->hdr.idFrom == 0)
	{
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
			pTTT->lpszText = _T("Lado Izquierdo Produccción");
			break;
			default:
			pTTT->lpszText = _T("Left Hand Side Production");
			break;
		}
		return TRUE;
	}
	if(pTTT->hdr.idFrom == 1)
	{
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
			pTTT->lpszText = _T("Lado Derecho Produccción");
			break;
			default:
			pTTT->lpszText = _T("Right Hand Side Production");
			break;
		}
		return TRUE;
	}
	if(pTTT->hdr.idFrom == 2)
	{
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
			pTTT->lpszText = _T("Memoria de Trabajo");
			break;
			default:
			pTTT->lpszText = _T("Working Memory");
			break;
		}
		return TRUE;	
	}
	
	if(pTTT->hdr.idFrom == 3)
	{
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
			pTTT->lpszText = _T("Condiciones Enlazadas");
			break;
			default:
			pTTT->lpszText = _T("Linked Conditions");
			break;
		}
		return TRUE;
	}
	
	if(pTTT->hdr.idFrom == 4)
	{
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
			pTTT->lpszText = _T("Agenda Producciones");
			break;
			default:
			pTTT->lpszText = _T("Production Agenda");
			break;
		}
		return TRUE;	
	}

	if(pTTT->hdr.idFrom == 5)
	{
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
			pTTT->lpszText = _T("Memoria Alfa");
			break;
			default:
			pTTT->lpszText = _T("Alpha Memory");
			break;
		}
		return TRUE;
	}
	
	if(pTTT->hdr.idFrom == 6)
	{
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
			pTTT->lpszText = _T("Memoria Beta");
			break;
			default:
			pTTT->lpszText = _T("Beta Memory");
			break;
		}
		return TRUE;	
	}

	if(pTTT->hdr.idFrom == 7)
	{
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
			pTTT->lpszText = _T("Memoria Beta/Ficha ");
			break;
			default:
			pTTT->lpszText = _T("Beta Memory/Token");
			break;
		}
		return TRUE;	
	}
	
	if(pTTT->hdr.idFrom == 8)
	{
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
			pTTT->lpszText = _T("Red RETE");
			break;
			default:
			pTTT->lpszText = _T("RETE Network");
			break;
		}
		return TRUE;	
	}


	
	return FALSE;
}





BOOL CAIPITabView::OnInitDialog() 
{
	COXSizeDialogBar::OnInitDialog();

	
	//  --------------  Setting up Rollup Control  --------------
	
	CRect rect;
	GetClientRect(rect);
	rect.left = rect.right - 100;
	rect.top += 60;
	rect.right -= 0;
	rect.bottom -= 130;

	
	BOOL bSuccess;
	bSuccess = m_RollupCtrl.Create(WS_CHILD | WS_DLGFRAME | WS_VISIBLE, rect, /*&pMainFrame->m_wndInductionTabView*/ this, IDC_ROLLUPCTRL);
	ASSERT(bSuccess);

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			
	//Create CRollupCtrl Pages	

	pEditPage = new CPageEditDlg;
	pEditPage->m_pGrid = &pMainFrame->m_GridLHS;
	bSuccess = pEditPage->Create(IDD_PAGEEDIT_DLG, &m_RollupCtrl);
	m_RollupCtrl.InsertPage(_T("Edit"), pEditPage);
	
	pInsertPage = new CPageInsertDlg;
	pInsertPage->m_pGrid = &pMainFrame->m_GridLHS;
	bSuccess = pInsertPage->Create(IDD_PAGEINSERT_DLG, &m_RollupCtrl);
	m_RollupCtrl.InsertPage(_T("Insert"), pInsertPage);


	pFormatPage = new CPageFormatDlg;
	pFormatPage->m_pGrid = &pMainFrame->m_GridLHS;
	bSuccess = pFormatPage->Create(IDD_PAGEFORMAT_DLG, &m_RollupCtrl);
	m_RollupCtrl.InsertPage(_T("Grid Format"), pFormatPage);

	pOptionsPage = new CPageOptionsDlg;
	pOptionsPage->m_pGrid = &pMainFrame->m_GridLHS;
	bSuccess = pOptionsPage->Create(IDD_PAGEOPTIONS_DLG, &m_RollupCtrl);
	m_RollupCtrl.InsertPage(_T("Grid Options"), pOptionsPage);
	
	pCellSizePage = new CPageCellSizeDlg;
	pCellSizePage->m_pGrid = &pMainFrame->m_GridLHS;
	bSuccess = pCellSizePage->Create(IDD_PAGECELLSIZE_DLG, &m_RollupCtrl);
	m_RollupCtrl.InsertPage(_T("Cell Sizing"), pCellSizePage);


	if(!InitLayoutManager())
	{
		MessageBox(_T("Failed to init layout manager!"));
	}
	
	UpdateData(FALSE);
	CreateTab();
	InitGridCtrls();
	//pInsertPage->UpdateEditControls();
				
		
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAIPITabView::OnSelchangeAipiTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	*pResult = 0;
	int iCurTab = m_TabCtrl.GetCurSel();	// get tab 
	

	switch(iCurTab)
	{
		
		case 0:		// LHS
			//Page Left Hand Side
			pMainFrame->m_CurrentGrid = GRID_LHS;
			
			
			pMainFrame->m_GridLHS.ShowWindow(SW_SHOW);
			pMainFrame->m_GridRHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridWM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridCondLink.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM_TK.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRETE.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAgenda.ShowWindow(SW_HIDE);
			
			
			pEditPage->m_pGrid = &pMainFrame->m_GridLHS;
			pFormatPage->m_pGrid = &pMainFrame->m_GridLHS;
			pOptionsPage->m_pGrid = &pMainFrame->m_GridLHS;
			pInsertPage->m_pGrid = &pMainFrame->m_GridLHS;
			pCellSizePage->m_pGrid = &pMainFrame->m_GridLHS;
			
			
			pInsertPage->UpdateEditControls();
			m_stcLabelRange.SetWindowText(_T("Left Hand Side(LHS) Range:"));
			UpdateMenuUI();
		
			FillGridLHS();

			UpdateData(true);
			m_iMaxRange = m_iMaxRange_LHS;
			m_iMinRange = m_iMinRange_LHS;
			UpdateData(false);
			
			
			
			
			break;
		
		case 1:		// RHS
			//Page Right Hand Side
			pMainFrame->m_CurrentGrid = GRID_RHS;
			
			
			pMainFrame->m_GridLHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRHS.ShowWindow(SW_SHOW);
			pMainFrame->m_GridWM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridCondLink.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM_TK.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRETE.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAgenda.ShowWindow(SW_HIDE);
			
			
			pEditPage->m_pGrid = &pMainFrame->m_GridRHS;
			pFormatPage->m_pGrid = &pMainFrame->m_GridRHS;
			pOptionsPage->m_pGrid = &pMainFrame->m_GridRHS;
			pInsertPage->m_pGrid = &pMainFrame->m_GridRHS;
			pCellSizePage->m_pGrid = &pMainFrame->m_GridRHS;
			
			
			pInsertPage->UpdateEditControls();
			m_stcLabelRange.SetWindowText(_T("Right Hand Side(RHS) Range:"));
			UpdateMenuUI();
		
			FillGridRHS();

			UpdateData(true);
			m_iMaxRange = m_iMaxRange_RHS;
			m_iMinRange = m_iMinRange_RHS;
			UpdateData(false);
			
			
			
			
			break;

		case 2:		// WM
			//Page Working Memory
			
			pMainFrame->m_CurrentGrid = GRID_WM;
			
			pMainFrame->m_GridLHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridWM.ShowWindow(SW_SHOW);
			pMainFrame->m_GridCondLink.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM_TK.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRETE.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAgenda.ShowWindow(SW_HIDE);
			
			
			pEditPage->m_pGrid = &pMainFrame->m_GridWM;
			pFormatPage->m_pGrid = &pMainFrame->m_GridWM;
			pOptionsPage->m_pGrid = &pMainFrame->m_GridWM;
			pInsertPage->m_pGrid = &pMainFrame->m_GridWM;
			pCellSizePage->m_pGrid = &pMainFrame->m_GridWM;
			
			pInsertPage->UpdateEditControls();
			m_stcLabelRange.SetWindowText(_T("Working Memory Range:"));
			UpdateMenuUI();

			FillGridWM();
			

			UpdateData(true);
			m_iMaxRange = m_iMaxRange_WM;
			m_iMinRange = m_iMinRange_WM;
			UpdateData(false);
			
			
			break;

		case 3:		// LIKS
			//Page Condition Links
			pMainFrame->m_CurrentGrid = GRID_COND_LINK;
			
			
			pMainFrame->m_GridLHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridWM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridCondLink.ShowWindow(SW_SHOW);
			pMainFrame->m_GridAM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM_TK.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRETE.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAgenda.ShowWindow(SW_HIDE);
			
			
			pEditPage->m_pGrid = &pMainFrame->m_GridCondLink;
			pFormatPage->m_pGrid = &pMainFrame->m_GridCondLink;
			pOptionsPage->m_pGrid = &pMainFrame->m_GridCondLink;
			pInsertPage->m_pGrid = &pMainFrame->m_GridCondLink;
			pCellSizePage->m_pGrid = &pMainFrame->m_GridCondLink;
			
			
			pInsertPage->UpdateEditControls();
			m_stcLabelRange.SetWindowText(_T("Condition Link Range:"));
			UpdateMenuUI();
		
			FillGridCondLink();

			UpdateData(true);
			m_iMaxRange = m_iMaxRange_CLink;
			m_iMinRange = m_iMinRange_CLink;
			UpdateData(false);
			
			
			
			
			break;


		case 4:		// Agenda
			//Page Production Agenda
			pMainFrame->m_CurrentGrid = GRID_AGENDA;

			pMainFrame->m_GridLHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridWM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridCondLink.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM_TK.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRETE.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAgenda.ShowWindow(SW_SHOW);
			
			
			pEditPage->m_pGrid = &pMainFrame->m_GridAgenda;
			pFormatPage->m_pGrid = &pMainFrame->m_GridAgenda;
			pOptionsPage->m_pGrid = &pMainFrame->m_GridAgenda;
			pInsertPage->m_pGrid = &pMainFrame->m_GridAgenda;
			pCellSizePage->m_pGrid = &pMainFrame->m_GridAgenda;
			
			pInsertPage->UpdateEditControls();
			m_stcLabelRange.SetWindowText(_T("Agenda Rules Range:"));
			UpdateMenuUI();

			UpdateData(true);
			m_iMaxRange = m_iMaxRange_Agenda;
			m_iMinRange = m_iMinRange_Agenda;
			UpdateData(false);
			

			break;
		
		case 5:		// AM
			//Page Alpha Memory
			pMainFrame->m_CurrentGrid = GRID_AM;

			pMainFrame->m_GridLHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridWM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridCondLink.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAM.ShowWindow(SW_SHOW);
			pMainFrame->m_GridBM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM_TK.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRETE.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAgenda.ShowWindow(SW_HIDE);
			
			
			pEditPage->m_pGrid = &pMainFrame->m_GridAM;
			pFormatPage->m_pGrid = &pMainFrame->m_GridAM;
			pOptionsPage->m_pGrid = &pMainFrame->m_GridAM;
			pInsertPage->m_pGrid = &pMainFrame->m_GridAM;
			pCellSizePage->m_pGrid = &pMainFrame->m_GridAM;
			
			pInsertPage->UpdateEditControls();
			m_stcLabelRange.SetWindowText(_T("Alpha Memory Range:"));
			UpdateMenuUI();

			FillGridAM();
			
			UpdateData(true);
			m_iMaxRange = m_iMaxRange_AM;
			m_iMinRange = m_iMinRange_AM;
			UpdateData(false);
	
			break;

		case 6:		// BM
			//Page Beta Memory
			pMainFrame->m_CurrentGrid = GRID_BM;

			pMainFrame->m_GridLHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridWM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridCondLink.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM.ShowWindow(SW_SHOW);
			pMainFrame->m_GridBM_TK.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRETE.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAgenda.ShowWindow(SW_HIDE);
			
			
			pEditPage->m_pGrid = &pMainFrame->m_GridBM;
			pFormatPage->m_pGrid = &pMainFrame->m_GridBM;
			pOptionsPage->m_pGrid = &pMainFrame->m_GridBM;
			pInsertPage->m_pGrid = &pMainFrame->m_GridBM;
			pCellSizePage->m_pGrid = &pMainFrame->m_GridBM;

			pInsertPage->UpdateEditControls();
			m_stcLabelRange.SetWindowText(_T("Beta Memory Range:"));
			UpdateMenuUI();

			FillGridBM();
			
			UpdateData(true);
			m_iMaxRange = m_iMaxRange_BM;
			m_iMinRange = m_iMinRange_BM;
			UpdateData(false);
			
			
			
			
			break;

		case 7:		// BM_TK
			//Page BM_TK Network
			pMainFrame->m_CurrentGrid = GRID_BM_TK;

			pMainFrame->m_GridLHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridWM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridCondLink.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM_TK.ShowWindow(SW_SHOW);
			pMainFrame->m_GridRETE.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAgenda.ShowWindow(SW_HIDE);
			
			
			pEditPage->m_pGrid = &pMainFrame->m_GridBM_TK;
			pFormatPage->m_pGrid = &pMainFrame->m_GridBM_TK;
			pOptionsPage->m_pGrid = &pMainFrame->m_GridBM_TK;
			pInsertPage->m_pGrid = &pMainFrame->m_GridBM_TK;
			pCellSizePage->m_pGrid = &pMainFrame->m_GridBM_TK;

			pInsertPage->UpdateEditControls();
			m_stcLabelRange.SetWindowText(_T("Rete Network Range:"));
			UpdateMenuUI();

			FillGridBM_TK();
			
			
			UpdateData(true);
			m_iMaxRange = m_iMaxRange_BM_TK;
			m_iMinRange = m_iMinRange_BM_TK;
			UpdateData(false);
			
			break;
		
		case 8:		// RETE
			//Page RETE Network
			pMainFrame->m_CurrentGrid = GRID_RETE;

			pMainFrame->m_GridLHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRHS.ShowWindow(SW_HIDE);
			pMainFrame->m_GridWM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridCondLink.ShowWindow(SW_HIDE);
			pMainFrame->m_GridAM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM.ShowWindow(SW_HIDE);
			pMainFrame->m_GridBM_TK.ShowWindow(SW_HIDE);
			pMainFrame->m_GridRETE.ShowWindow(SW_SHOW);
			pMainFrame->m_GridAgenda.ShowWindow(SW_HIDE);
			
			
			pEditPage->m_pGrid = &pMainFrame->m_GridRETE;
			pFormatPage->m_pGrid = &pMainFrame->m_GridRETE;
			pOptionsPage->m_pGrid = &pMainFrame->m_GridRETE;
			pInsertPage->m_pGrid = &pMainFrame->m_GridRETE;
			pCellSizePage->m_pGrid = &pMainFrame->m_GridRETE;

			pInsertPage->UpdateEditControls();
			m_stcLabelRange.SetWindowText(_T("Rete Network Range:"));
			UpdateMenuUI();

			FillGridRETE();
			
			UpdateData(true);
			m_iMaxRange = m_iMaxRange_RETE;
			m_iMinRange = m_iMinRange_RETE;
			UpdateData(false);
			

			
			
			break;
		
		
			
	}	// end switch on tab selection
}




void CAIPITabView::Init_Page()
{
		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);

		m_LayoutManager.SetConstraint(IDC_AIPITAB, OX_LMS_TOP, OX_LMT_SAME, 5);
		//m_LayoutManager.SetConstraint(IDC_AIPITAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STC_RANGE);
		m_LayoutManager.SetConstraint(IDC_AIPITAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_AIPITAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Static Range Control
		m_LayoutManager.SetConstraint(IDC_STC_RANGE, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_AIPITAB);
		//m_LayoutManager.SetConstraint(IDC_STC_RANGE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 5, IDC_EDIT_MIN_RANGE);
		m_LayoutManager.SetConstraint(IDC_STC_RANGE, OX_LMS_LEFT, OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STC_RANGE, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
		//Constrain Label Range Control
		m_LayoutManager.SetConstraint(IDC_STC_LABEL_RANGE, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_RANGE);
		//m_LayoutManager.SetConstraint(IDC_STC_LABEL_RANGE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_BTN_RANGE);
		m_LayoutManager.SetConstraint(IDC_STC_LABEL_RANGE, OX_LMS_LEFT, OX_LMT_SAME, 5  );
		m_LayoutManager.SetConstraint(IDC_STC_LABEL_RANGE, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -5, IDC_EDIT_MIN_RANGE);

	
		//Constrain Edit Min Range Control
		m_LayoutManager.SetConstraint(IDC_EDIT_MIN_RANGE, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_RANGE);
		//m_LayoutManager.SetConstraint(IDC_EDIT_MIN_RANGE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_BTN_RANGE);
		//m_LayoutManager.SetConstraint(IDC_EDIT_MIN_RANGE, OX_LMS_LEFT, OX_LMT_OPPOSITE, , IDC_STC_LABEL_RANGE);
		m_LayoutManager.SetConstraint(IDC_EDIT_MIN_RANGE, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -5, IDC_STATIC_TO);


		m_LayoutManager.SetConstraint(IDC_STATIC_TO, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_RANGE);
		//m_LayoutManager.SetConstraint(IDC_STATIC_TO, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_BTN_RANGE);
		//m_LayoutManager.SetConstraint(IDC_STATIC_TO, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_EDIT_MIN_RANGE );
		m_LayoutManager.SetConstraint(IDC_STATIC_TO, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -5,IDC_EDIT_MAX_RANGE);

		
		//Constrain Edit Max Range Control
		m_LayoutManager.SetConstraint(IDC_EDIT_MAX_RANGE, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_RANGE);
		//m_LayoutManager.SetConstraint(IDC_EDIT_MAX_RANGE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_BTN_RANGE);
		//m_LayoutManager.SetConstraint(IDC_EDIT_MAX_RANGE, OX_LMS_LEFT, OX_LMT_OPPOSITE, 0, IDC_STATIC_TO);
		m_LayoutManager.SetConstraint(IDC_EDIT_MAX_RANGE, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		

		
		//View Range Btn
		m_LayoutManager.SetConstraint(IDC_BTN_ALL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_LABEL_RANGE);
		//m_LayoutManager.SetConstraint(IDC_BTN_ALL, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STC_AIPI_DATA);
		m_LayoutManager.SetConstraint(IDC_BTN_ALL, OX_LMS_LEFT, OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_BTN_ALL, OX_LMS_RIGHT, OX_LMT_POSITION, 50);

		//View All Btn
		m_LayoutManager.SetConstraint(IDC_BTN_RANGE, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_LABEL_RANGE);
		//m_LayoutManager.SetConstraint(IDC_BTN_RANGE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STC_AIPI_DATA);
		m_LayoutManager.SetConstraint(IDC_BTN_RANGE, OX_LMS_LEFT, OX_LMT_POSITION, 50);
		m_LayoutManager.SetConstraint(IDC_BTN_RANGE, OX_LMS_RIGHT, OX_LMT_SAME, -5);



		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_BTN_ALL);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_BTN_ALL);


		
		m_LayoutManager.SetConstraint(IDC_STC_AIPI_DATA, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_BTN_ALL);
		//m_LayoutManager.SetConstraint(IDC_STC_AIPI_DATA, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_AIPI_GRID);
		m_LayoutManager.SetConstraint(IDC_STC_AIPI_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STC_AIPI_DATA, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		

	//GridCtrl LHS
	m_LayoutManager.SetConstraint(IDC_GRID_LHS, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_AIPI_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID_LHS, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID_LHS, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID_LHS, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	//GridCtrl RHS
	m_LayoutManager.SetConstraint(IDC_GRID_RHS, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_AIPI_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID_RHS, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID_RHS, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID_RHS, OX_LMS_RIGHT, OX_LMT_SAME, -5);


	//GridCtrl WM
	m_LayoutManager.SetConstraint(IDC_GRID_WM, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_AIPI_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID_WM, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID_WM, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID_WM, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	//GridCtrl Condition Links
	m_LayoutManager.SetConstraint(IDC_GRID_COND_LINK, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_AIPI_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID_COND_LINK, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID_COND_LINK, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID_COND_LINK, OX_LMS_RIGHT, OX_LMT_SAME, -5);


	//GridCtrl AM
	m_LayoutManager.SetConstraint(IDC_GRID_AM, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_AIPI_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID_AM, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID_AM, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID_AM, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	//GridCtrl BM
	m_LayoutManager.SetConstraint(IDC_GRID_BM, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_AIPI_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID_BM, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID_BM, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID_BM, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	//GridCtrl RETE
	m_LayoutManager.SetConstraint(IDC_GRID_RETE, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_AIPI_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID_RETE, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID_RETE, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID_RETE, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	//GridCtrl Agenda
	m_LayoutManager.SetConstraint(IDC_GRID_AGENDA, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_AIPI_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID_AGENDA, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID_AGENDA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID_AGENDA, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	//GridCtrl BM_TK
	m_LayoutManager.SetConstraint(IDC_GRID_BM_TK, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STC_AIPI_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID_BM_TK, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID_BM_TK, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID_BM_TK, OX_LMS_RIGHT, OX_LMT_SAME, -5);


	m_LayoutManager.RedrawLayout();
	
}


void CAIPITabView::StopTimer(CPerfTimer t, CString msg)
{
	CString str;
	t.Stop();
	str.Format(msg + _T("%0.4f"),t.Elapsed());
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndOutputTabView.IsVisible())
	{
		pMainFrame->m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(0);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
		
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// GridCtrl Functions ////
///////////////////////////////////////////////////////////////////////////////////////////////


void CAIPITabView::InitGridCtrls()
{
	InitGridLHS(10 ,9);
	InitGridRHS(10 ,7);
	InitGridWM(10, 7);
	InitGridCondLink(10 , 7);
	InitGridAgenda(10, 5);
	InitGridAM(10, 4);
	InitGridBM(10, 3);
	InitGridBM_TK(10,9);
	InitGridRETE(10,7);

	m_iMaxRange = 0;
	m_iMinRange = 0;
	UpdateData(false);

}



void CAIPITabView::InitGridLHS(int n_row, int n_col)
{

		m_nFixCols = 1;
	    m_nFixRows = 2;
	    m_nCols = n_col;
	    m_nRows = n_row;
		
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	    pMainFrame->m_GridLHS.SetEditable(pMainFrame->m_bEditable);
        pMainFrame->m_GridLHS.SetAutoSizeStyle();
		pMainFrame->m_GridLHS.EnableDragAndDrop(TRUE);
		pMainFrame->m_GridLHS.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
		pMainFrame->m_GridLHS.SetFixedColumnSelection(TRUE);
		pMainFrame->m_GridLHS.SetFixedRowSelection(TRUE);
	    


	    TRY 
		{
		    pMainFrame->m_GridLHS.SetRowCount(m_nRows);
		    pMainFrame->m_GridLHS.SetColumnCount(m_nCols);
		    pMainFrame->m_GridLHS.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridLHS.SetFixedColumnCount(m_nFixCols);
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

	

		 // Set col/row width and height
	    for (int row = 0; row < pMainFrame->m_GridLHS.GetRowCount(); row++)
        {
	    	for (int col = 0; col < pMainFrame->m_GridLHS.GetColumnCount(); col++)
		    { 
                CString str = _T("");	
				GV_ITEM Item;
				Item.mask = GVIF_TEXT;
	    		Item.row = row;
		    	Item.col = col;

			    if (row < m_nFixRows)
                    str.Format(_T("C%d"),col);
                else if (col < m_nFixCols) 
                    str.Format(_T("R%d"), row-1);
                
				Item.strText = str;
				pMainFrame->m_GridLHS.SetItem(&Item);
				
				pMainFrame->m_GridLHS.SetColumnWidth(col, 80);
				pMainFrame->m_GridLHS.SetRowHeight(row, 18);	
	    	}
        }

		//Fill Column Headers
	pMainFrame->m_GridLHS.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridLHS.SetItemText(1, 1, _T("Condition"));	
	pMainFrame->m_GridLHS.SetItemText(1, 2, _T("Identifier"));		
	pMainFrame->m_GridLHS.SetItemText(1, 3, _T("Attribute"));		
	pMainFrame->m_GridLHS.SetItemText(1, 4, _T("Value"));	
	pMainFrame->m_GridLHS.SetItemText(1, 5, _T("Operator"));	
	pMainFrame->m_GridLHS.SetItemText(1, 6, _T("Production"));
	pMainFrame->m_GridLHS.SetItemText(1, 7, _T("Category"));
	pMainFrame->m_GridLHS.SetItemText(1, 8, _T("AM"));

	
#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
	
		pMainFrame->m_GridLHS.AutoSize();
#endif


   
}


void CAIPITabView::InitGridRHS(int n_row, int n_col)
{

		m_nFixCols = 1;
	    m_nFixRows = 2;
	    m_nCols = n_col;
	    m_nRows = n_row;
		
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	    pMainFrame->m_GridRHS.SetEditable(pMainFrame->m_bEditable);
        pMainFrame->m_GridRHS.SetAutoSizeStyle();
		pMainFrame->m_GridRHS.EnableDragAndDrop(TRUE);
		pMainFrame->m_GridRHS.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
		pMainFrame->m_GridRHS.SetFixedColumnSelection(TRUE);
		pMainFrame->m_GridRHS.SetFixedRowSelection(TRUE);
	    


	    TRY 
		{
		    pMainFrame->m_GridRHS.SetRowCount(m_nRows);
		    pMainFrame->m_GridRHS.SetColumnCount(m_nCols);
		    pMainFrame->m_GridRHS.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridRHS.SetFixedColumnCount(m_nFixCols);
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

	

		 // Set col/row width and height
	    for (int row = 0; row < pMainFrame->m_GridRHS.GetRowCount(); row++)
        {
	    	for (int col = 0; col < pMainFrame->m_GridRHS.GetColumnCount(); col++)
		    { 
                CString str = _T("");	
				GV_ITEM Item;
				Item.mask = GVIF_TEXT;
	    		Item.row = row;
		    	Item.col = col;

			    if (row < m_nFixRows)
                    str.Format(_T("C%d"),col);
                else if (col < m_nFixCols) 
                    str.Format(_T("R%d"), row - 1);
                
				Item.strText = str;
				pMainFrame->m_GridRHS.SetItem(&Item);
				
				pMainFrame->m_GridRHS.SetColumnWidth(col, 80);
				pMainFrame->m_GridRHS.SetRowHeight(row, 18);	
	    	}
        }

		//Fill Column Headers
	pMainFrame->m_GridRHS.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridRHS.SetItemText(1, 1, _T("Action"));
	pMainFrame->m_GridRHS.SetItemText(1, 2, _T("Command"));
	pMainFrame->m_GridRHS.SetItemText(1, 3, _T("Identifier"));		
	pMainFrame->m_GridRHS.SetItemText(1, 4, _T("Attribute"));		
	pMainFrame->m_GridRHS.SetItemText(1, 5, _T("Value"));	
	pMainFrame->m_GridRHS.SetItemText(1, 6, _T("Production"));
	
	
	
#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
	
		pMainFrame->m_GridRHS.AutoSize();
#endif


   
}


void CAIPITabView::InitGridCondLink(int n_row, int n_col)
{

		m_nFixCols = 1;
	    m_nFixRows = 2;
	    m_nCols = n_col;
	    m_nRows = n_row;
		
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	    pMainFrame->m_GridCondLink.SetEditable(pMainFrame->m_bEditable);
        pMainFrame->m_GridCondLink.SetAutoSizeStyle();
		pMainFrame->m_GridCondLink.EnableDragAndDrop(TRUE);
		pMainFrame->m_GridCondLink.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
		pMainFrame->m_GridCondLink.SetFixedColumnSelection(TRUE);
		pMainFrame->m_GridCondLink.SetFixedRowSelection(TRUE);
	    


	    TRY 
		{
		    pMainFrame->m_GridCondLink.SetRowCount(m_nRows);
		    pMainFrame->m_GridCondLink.SetColumnCount(m_nCols);
		    pMainFrame->m_GridCondLink.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridCondLink.SetFixedColumnCount(m_nFixCols);
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

	

		 // Set col/row width and height
	    for (int row = 0; row < pMainFrame->m_GridCondLink.GetRowCount(); row++)
        {
	    	for (int col = 0; col < pMainFrame->m_GridCondLink.GetColumnCount(); col++)
		    { 
                CString str = _T("");	
				GV_ITEM Item;
				Item.mask = GVIF_TEXT;
	    		Item.row = row;
		    	Item.col = col;

			    if (row < m_nFixRows)
                    str.Format(_T("C%d"),col);
                else if (col < m_nFixCols) 
                    str.Format(_T("R%d"), row);
                
				Item.strText = str;
				pMainFrame->m_GridCondLink.SetItem(&Item);
				
				pMainFrame->m_GridCondLink.SetColumnWidth(col, 80);
				pMainFrame->m_GridCondLink.SetRowHeight(row, 18);	
	    	}
        }

		//Fill Column Headers
	pMainFrame->m_GridCondLink.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridCondLink.SetItemText(1, 1, _T("Condition 1"));	
	pMainFrame->m_GridCondLink.SetItemText(1, 2, _T("Condition 2"));		
	pMainFrame->m_GridCondLink.SetItemText(1, 3, _T("Field 1"));		
	pMainFrame->m_GridCondLink.SetItemText(1, 4, _T("Field 2"));	
	pMainFrame->m_GridCondLink.SetItemText(1, 5, _T("Production"));
	pMainFrame->m_GridCondLink.SetItemText(1, 6, _T("Variable"));
	
	
#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
	
		pMainFrame->m_GridCondLink.AutoSize();
#endif


   
}



void CAIPITabView::InitGridWM(int n_row, int n_col)
{

		m_nFixCols = 1;
	    m_nFixRows = 2;
	    m_nCols = n_col;
	    m_nRows = n_row;
		
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	    pMainFrame->m_GridWM.SetEditable(pMainFrame->m_bEditable);
        pMainFrame->m_GridWM.SetAutoSizeStyle();
		pMainFrame->m_GridWM.EnableDragAndDrop(TRUE);
		pMainFrame->m_GridWM.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
		pMainFrame->m_GridWM.SetFixedColumnSelection(TRUE);
		pMainFrame->m_GridWM.SetFixedRowSelection(TRUE);
	    


	    TRY 
		{
		    pMainFrame->m_GridWM.SetRowCount(m_nRows);
		    pMainFrame->m_GridWM.SetColumnCount(m_nCols);
		    pMainFrame->m_GridWM.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridWM.SetFixedColumnCount(m_nFixCols);
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

		 // Set col/row width and height
	    for (int row = 0; row < pMainFrame->m_GridWM.GetRowCount(); row++)
        {
	    	for (int col = 0; col < pMainFrame->m_GridWM.GetColumnCount(); col++)
		    {      
			    CString str = _T("");
				GV_ITEM Item;
    			Item.mask = GVIF_TEXT;
	    		Item.row = row;
		    	Item.col = col;

			    if (row < m_nFixRows)
                    str.Format(_T("C%d"),col);
                else if (col < m_nFixCols) 
                    str.Format(_T("R%d"), row);
                
				//else 
				    //str.Format(_T("%d"),row*col);
                Item.strText = str;
				pMainFrame->m_GridWM.SetItem(&Item);
				
				pMainFrame->m_GridWM.SetColumnWidth(col, 80);
				pMainFrame->m_GridWM.SetRowHeight(row, 18);	
	    	}
        }

	//Fill Column Headers
	pMainFrame->m_GridWM.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridWM.SetItemText(1, 1, _T("WME"));	
	pMainFrame->m_GridWM.SetItemText(1, 2, _T("Identifier"));		
	pMainFrame->m_GridWM.SetItemText(1, 3, _T("Attribute"));		
	pMainFrame->m_GridWM.SetItemText(1, 4, _T("Value"));	
	pMainFrame->m_GridWM.SetItemText(1, 5, _T("Type"));	
	pMainFrame->m_GridWM.SetItemText(1, 6, _T("AM"));

		

#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
	pMainFrame->m_GridWM.AutoSize();
#endif
    

}


void CAIPITabView::InitGridAM(int n_row, int n_col)
{

	m_nFixCols = 1;
	m_nFixRows = 2;
	m_nCols = n_col;
	m_nRows = n_row;
		
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	pMainFrame->m_GridAM.SetEditable(pMainFrame->m_bEditable);
    pMainFrame->m_GridAM.SetAutoSizeStyle();
	pMainFrame->m_GridAM.EnableDragAndDrop(TRUE);
	pMainFrame->m_GridAM.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
	pMainFrame->m_GridAM.SetFixedColumnSelection(TRUE);
	pMainFrame->m_GridAM.SetFixedRowSelection(TRUE);
	    


	    TRY 
		{
		    pMainFrame->m_GridAM.SetRowCount(m_nRows);
		    pMainFrame->m_GridAM.SetColumnCount(m_nCols);
		    pMainFrame->m_GridAM.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridAM.SetFixedColumnCount(m_nFixCols);
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

		 // Set col/row width and height
	    for (int row = 0; row < pMainFrame->m_GridAM.GetRowCount(); row++)
        {
	    	for (int col = 0; col < pMainFrame->m_GridAM.GetColumnCount(); col++)
		    {      
			    CString str = _T("");
				GV_ITEM Item;
    			Item.mask = GVIF_TEXT;
	    		Item.row = row;
		    	Item.col = col;

			    if (row < m_nFixRows)
                    str.Format(_T("C%d"),col);
                else if (col < m_nFixCols) 
                    str.Format(_T("R%d"), row);
                
				//else 
				    //str.Format(_T("%d"),row*col);
                Item.strText = str;
				pMainFrame->m_GridAM.SetItem(&Item);
				
				pMainFrame->m_GridAM.SetColumnWidth(col, 80);
				pMainFrame->m_GridAM.SetRowHeight(row, 18);	
	    	}
        }

	//Fill Column Headers
	pMainFrame->m_GridAM.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridAM.SetItemText(1, 1, _T("AM"));	
	pMainFrame->m_GridAM.SetItemText(1, 2, _T("Condition"));		
	pMainFrame->m_GridAM.SetItemText(1, 3, _T("WM"));		
	
		

#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
	pMainFrame->m_GridAM.AutoSize();
#endif
    


}


void CAIPITabView::InitGridBM(int n_row, int n_col)
{
	m_nFixCols = 1;
	m_nFixRows = 2;
	m_nCols = n_col;
	m_nRows = n_row;
		
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	pMainFrame->m_GridBM.SetEditable(pMainFrame->m_bEditable);
    pMainFrame->m_GridBM.SetAutoSizeStyle();
	pMainFrame->m_GridBM.EnableDragAndDrop(TRUE);
	pMainFrame->m_GridBM.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
	pMainFrame->m_GridBM.SetFixedColumnSelection(TRUE);
	pMainFrame->m_GridBM.SetFixedRowSelection(TRUE);
	    


	    TRY 
		{
		    pMainFrame->m_GridBM.SetRowCount(m_nRows);
		    pMainFrame->m_GridBM.SetColumnCount(m_nCols);
		    pMainFrame->m_GridBM.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridBM.SetFixedColumnCount(m_nFixCols);
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

		 // Set col/row width and height
	    for (int row = 0; row < pMainFrame->m_GridBM.GetRowCount(); row++)
        {
	    	for (int col = 0; col < pMainFrame->m_GridBM.GetColumnCount(); col++)
		    {      
			    CString str = _T("");
				GV_ITEM Item;
    			Item.mask = GVIF_TEXT;
	    		Item.row = row;
		    	Item.col = col;

			    if (row < m_nFixRows)
                    str.Format(_T("C%d"),col);
                else if (col < m_nFixCols) 
                    str.Format(_T("R%d"), row);
                
				//else 
				    //str.Format(_T("%d"),row*col);
                Item.strText = str;
				pMainFrame->m_GridBM.SetItem(&Item);
				
				pMainFrame->m_GridBM.SetColumnWidth(col, 80);
				pMainFrame->m_GridBM.SetRowHeight(row, 18);	
	    	}
        }

	//Fill Column Headers
	pMainFrame->m_GridBM.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridBM.SetItemText(1, 1, _T("BM"));	
	pMainFrame->m_GridBM.SetItemText(1, 2, _T("Linked WMEs"));		
	
		

#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
	pMainFrame->m_GridBM.AutoSize();
#endif
    
		


}


void CAIPITabView::InitGridBM_TK(int n_row, int n_col)
{
	m_nFixCols = 1;
	m_nFixRows = 2;
	m_nCols = n_col;
	m_nRows = n_row;
		
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	pMainFrame->m_GridBM_TK.SetEditable(pMainFrame->m_bEditable);
    pMainFrame->m_GridBM_TK.SetAutoSizeStyle();
	pMainFrame->m_GridBM_TK.EnableDragAndDrop(TRUE);
	pMainFrame->m_GridBM_TK.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
	pMainFrame->m_GridBM_TK.SetFixedColumnSelection(TRUE);
	pMainFrame->m_GridBM_TK.SetFixedRowSelection(TRUE);
	    


	    TRY 
		{
		    pMainFrame->m_GridBM_TK.SetRowCount(m_nRows);
		    pMainFrame->m_GridBM_TK.SetColumnCount(m_nCols);
		    pMainFrame->m_GridBM_TK.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridBM_TK.SetFixedColumnCount(m_nFixCols);
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

		 // Set col/row width and height
	    for (int row = 0; row < pMainFrame->m_GridBM_TK.GetRowCount(); row++)
        {
	    	for (int col = 0; col < pMainFrame->m_GridBM_TK.GetColumnCount(); col++)
		    {      
			    CString str = _T("");
				GV_ITEM Item;
    			Item.mask = GVIF_TEXT;
	    		Item.row = row;
		    	Item.col = col;

			    if (row < m_nFixRows)
                    str.Format(_T("C%d"),col);
                else if (col < m_nFixCols) 
                    str.Format(_T("R%d"), row);
                
				//else 
				    //str.Format(_T("%d"),row*col);
                Item.strText = str;
				pMainFrame->m_GridBM_TK.SetItem(&Item);
				
				pMainFrame->m_GridBM_TK.SetColumnWidth(col, 80);
				pMainFrame->m_GridBM_TK.SetRowHeight(row, 18);	
	    	}
        }

	//Fill Column Headers
	pMainFrame->m_GridBM_TK.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridBM_TK.SetItemText(1, 1, _T("BM"));	
	pMainFrame->m_GridBM_TK.SetItemText(1, 2, _T("WM"));		
	pMainFrame->m_GridBM_TK.SetItemText(1, 3, _T("Parent Tk"));		
	pMainFrame->m_GridBM_TK.SetItemText(1, 4, _T("Child Tk"));
	pMainFrame->m_GridBM_TK.SetItemText(1, 5, _T("Id. Var"));	
	pMainFrame->m_GridBM_TK.SetItemText(1, 6, _T("Id. Data"));		
	pMainFrame->m_GridBM_TK.SetItemText(1, 7, _T("Val. Var"));		
	pMainFrame->m_GridBM_TK.SetItemText(1, 8, _T("Val. Data"));	
		

#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
	pMainFrame->m_GridBM_TK.AutoSize();
#endif
    
		


}

void CAIPITabView::InitGridRETE(int n_row, int n_col)
{

		m_nFixCols = 1;
	    m_nFixRows = 2;
	    m_nCols = n_col;
	    m_nRows = n_row;

		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	    pMainFrame->m_GridRETE.SetEditable(pMainFrame->m_bEditable);
        pMainFrame->m_GridRETE.SetAutoSizeStyle();
		pMainFrame->m_GridRETE.EnableDragAndDrop(TRUE);
		pMainFrame->m_GridRETE.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
		pMainFrame->m_GridRETE.SetFixedColumnSelection(TRUE);
		pMainFrame->m_GridRETE.SetFixedRowSelection(TRUE);
	    


	    TRY {
		    pMainFrame->m_GridRETE.SetRowCount(m_nRows);
		    pMainFrame->m_GridRETE.SetColumnCount(m_nCols);
		    pMainFrame->m_GridRETE.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridRETE.SetFixedColumnCount(m_nFixCols);
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

		 // Set col/row width and height
	    for (int row = 0; row < pMainFrame->m_GridRETE.GetRowCount(); row++)
        {
	    	for (int col = 0; col < pMainFrame->m_GridRETE.GetColumnCount(); col++)
		    { 
                
				CString str;

			    GV_ITEM Item;

    			Item.mask = GVIF_TEXT;
	    		Item.row = row;
		    	Item.col = col;

			    if (row < m_nFixRows)
                    str.Format(_T("C%d"),col);
                else if (col < m_nFixCols) 
                    str.Format(_T("R%d"), row);
                
				//else 
				    //str.Format(_T("%d"),row*col);
                Item.strText = str;
				pMainFrame->m_GridRETE.SetItem(&Item);
				
				pMainFrame->m_GridRETE.SetColumnWidth(col, 80);
				pMainFrame->m_GridRETE.SetRowHeight(row, 18);	
	    	}
        }

				//Fill Column Headers
	pMainFrame->m_GridRETE.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridRETE.SetItemText(1, 1, _T("Node"));	
	pMainFrame->m_GridRETE.SetItemText(1, 2, _T("Type"));		
	pMainFrame->m_GridRETE.SetItemText(1, 3, _T("Parent BM"));		
	pMainFrame->m_GridRETE.SetItemText(1, 4, _T("Child BM"));	
	pMainFrame->m_GridRETE.SetItemText(1, 5, _T("AM"));	
	pMainFrame->m_GridRETE.SetItemText(1, 6, _T("Linked Variable"));
	
#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
	pMainFrame->m_GridRETE.AutoSize();
#endif

}


void CAIPITabView::InitGridAgenda(int n_row, int n_col)
{

		m_nFixCols = 1;
	    m_nFixRows = 2;
	    m_nCols = 2;
	    m_nRows = 10;

		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	    pMainFrame->m_GridAgenda.SetEditable(pMainFrame->m_bEditable);
        pMainFrame->m_GridAgenda.SetAutoSizeStyle();
		pMainFrame->m_GridAgenda.EnableDragAndDrop(TRUE);
		pMainFrame->m_GridAgenda.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
		pMainFrame->m_GridAgenda.SetFixedColumnSelection(TRUE);
		pMainFrame->m_GridAgenda.SetFixedRowSelection(TRUE);
	    


	    TRY {
		    pMainFrame->m_GridAgenda.SetRowCount(m_nRows);
		    pMainFrame->m_GridAgenda.SetColumnCount(m_nCols);
		    pMainFrame->m_GridAgenda.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridAgenda.SetFixedColumnCount(m_nFixCols);
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

		 // Set col/row width and height
	    for (int row = 0; row < pMainFrame->m_GridAgenda.GetRowCount(); row++)
        {
	    	for (int col = 0; col < pMainFrame->m_GridAgenda.GetColumnCount(); col++)
		    { 
                
				CString str;

			    GV_ITEM Item;

    			Item.mask = GVIF_TEXT;
	    		Item.row = row;
		    	Item.col = col;

			    if (row < m_nFixRows)
                    str.Format(_T("C%d"),col);
                else if (col < m_nFixCols) 
                    str.Format(_T("R%d"), row);
                
				//else 
				    //str.Format(_T("%d"),row*col);
                Item.strText = str;
				pMainFrame->m_GridAgenda.SetItem(&Item);
				
				pMainFrame->m_GridAgenda.SetColumnWidth(col, 80);
				pMainFrame->m_GridAgenda.SetRowHeight(row, 18);	
	    	}
        }


	//Fill Column Headers
	pMainFrame->m_GridAgenda.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridAgenda.SetItemText(1, 1, _T("Production"));	
		

#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
	pMainFrame->m_GridAgenda.AutoSize();
#endif


}





int CAIPITabView::FillGridLHS() 
{
	
	CAipi_LHS		lhso;
	CAipi_PM		pmo;
	
	
	TCHAR buffer[24];
	CString strRel = _T("");
	CString strAM = _T("");
	CString strA =_T("AM");
	CString str;
	int nRow =1;
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridLHS.ShowWindow(SW_HIDE);
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading left hand side of production memory(LHS) data to grid control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	
	int gridMaxCols = 9;  
	int gridMaxRows = lhso.sizeLHS();

			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("LHS status: Empty"));
		InitGridLHS(10, gridMaxCols);
		pMainFrame->m_GridLHS.ShowWindow(SW_SHOW);
		return 10;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridPM.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridPM.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridLHS.SetRowCount(gridMaxRows + 2 );
			pMainFrame->m_GridLHS.SetColumnCount(gridMaxCols);
			pMainFrame->m_GridLHS.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridLHS.SetFixedColumnCount(m_nFixCols);
		    
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return -1;
	    }
        END_CATCH

	//Fill Column Headers
	pMainFrame->m_GridLHS.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridLHS.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridLHS.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridLHS.SetItemText(0, 3, _T("C3"));		
	pMainFrame->m_GridLHS.SetItemText(0, 4, _T("C4"));	
	pMainFrame->m_GridLHS.SetItemText(0, 5, _T("C5"));	
	pMainFrame->m_GridLHS.SetItemText(0, 6, _T("C6"));
	pMainFrame->m_GridLHS.SetItemText(0, 7, _T("C7"));
	pMainFrame->m_GridLHS.SetItemText(0, 8, _T("C8"));

	pMainFrame->m_GridLHS.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridLHS.SetItemText(1, 1, _T("Condition"));	
	pMainFrame->m_GridLHS.SetItemText(1, 2, _T("Identifier"));		
	pMainFrame->m_GridLHS.SetItemText(1, 3, _T("Attribute"));		
	pMainFrame->m_GridLHS.SetItemText(1, 4, _T("Value"));	
	pMainFrame->m_GridLHS.SetItemText(1, 5, _T("Operator"));	
	pMainFrame->m_GridLHS.SetItemText(1, 6, _T("Production"));
	pMainFrame->m_GridLHS.SetItemText(1, 7, _T("Category"));
	pMainFrame->m_GridLHS.SetItemText(1, 8, _T("AM"));


	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	CMainFrame::g_mLHS::iterator iter;
	//Print map container Left Hand Side (PM)
	for( iter = pMainFrame->gmLHS.begin(); iter!= pMainFrame->gmLHS.end(); ++iter)
	{
		//AfxMessageBox(_T("Hola pueblo...."));
		CString strRow = _T("R");
		CString strCond =_T("LHS");
		CString strPM =_T("PM");
		CString strCateg =_T("CATEG");

		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
			
		strCond +=  _itot( iter->first, buffer, 10 );
		lhso = (CAipi_LHS)iter->second;
 	
		tstring i = lhso.getId();
		tstring a = lhso.getAttr();
		tstring v = lhso.getVal();
		int	rel	  = lhso.getRel();
		int pm	  = lhso.getPM();
		int categ = lhso.getCategory();
		
		strPM +=  _itot( pm, buffer, 10 );
		strCateg +=  _itot( categ, buffer, 10 );
		strRow +=  _itot( nRow, buffer, 10 );

		switch(rel)
		{
			case 100: 
				strRel =_T("EQ");
			break;
			case 101: 
				strRel =_T("LT");
			break;
			case 102: 
				strRel =_T("LE");
			break;
			case 103: 
				strRel =_T("GT");
			break;
			case 104: 
				strRel =_T("GE");
			break;
			case 105: 
				strRel =_T("ET");
			break;
			case 106: 
				strRel =_T("NE");
			break;
			case 107: 
				strRel =_T("AS");
			break;

		}
		
	
		//Fill Rows
		nRow++;
		
		if( nRow <= gridMaxRows + 1 )
		{
			wsprintf(buffer, strRow);
			wsprintf(buffer, strCond);
			wsprintf(buffer, strRel);
			wsprintf(buffer, strPM);
			wsprintf(buffer, strCateg);

			wsprintf(buffer, i.c_str());
			wsprintf(buffer, a.c_str());
			wsprintf(buffer, v.c_str());
			
			pMainFrame->m_GridLHS.SetItemText(nRow, 0, strRow);
			pMainFrame->m_GridLHS.SetItemText(nRow, 1, strCond);
			pMainFrame->m_GridLHS.SetItemText(nRow, 2, i.c_str());		
			pMainFrame->m_GridLHS.SetItemText(nRow, 3, a.c_str());		
			pMainFrame->m_GridLHS.SetItemText(nRow, 4, v.c_str());	
			pMainFrame->m_GridLHS.SetItemText(nRow, 5, strRel);	
			pMainFrame->m_GridLHS.SetItemText(nRow, 6, strPM);
			pMainFrame->m_GridLHS.SetItemText(nRow, 7, strCateg);
		}	


		
		strRow.ReleaseBuffer();
		strCond.ReleaseBuffer();
		strRel.ReleaseBuffer();
		strPM.ReleaseBuffer();
		strCateg.ReleaseBuffer();

			
		
	}//end for
 	
	
		
		//Print map container Alpha Memory
		nRow = 1;
		CMainFrame::g_mCond_AM::iterator itAM;
		for( itAM = pMainFrame->gmCond_AM.begin(); itAM!= pMainFrame->gmCond_AM.end(); ++itAM)
		{
			//AfxMessageBox(_T("Hola pueblo...."));
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, itAM->first*100/gridMaxRows);
		
			strAM = _T("");
			strAM = strA + _itot( itAM->second, buffer, 10 );
			nRow++;
			

			if( nRow <= gridMaxRows + 1)
			{
				wsprintf(buffer, strAM);
				pMainFrame->m_GridLHS.SetItemText(nRow, 8, strAM);		
			}

			strAM.ReleaseBuffer();
			
		}
	
		
	


		pMainFrame->m_GridLHS.AutoSize();
		StopTimer(T, _T("Production memory process elapsed seconds... "));
			
		
		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		pMainFrame->m_GridLHS.ShowWindow(SW_SHOW);
		str.Format(_T("LHS status: %d elements"), gridMaxRows);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
 			

	m_iMaxRange_LHS = pmo.sizePM();
	m_iMinRange_LHS = 0;
	


	return m_iMaxRange_LHS;
}



int CAIPITabView::FillGridRHS() 
{
	
	CAipi_RHS		rhso;
	CAipi_PM		pmo;
	
	
	TCHAR buffer[24];
	//CString strRel = _T("");
	//CString strAM = _T("");
	//CString strA =_T("A");
	CString str;
	int nRow =1;
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridRHS.ShowWindow(SW_HIDE);
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading right hand side of production memory(RHS) data to grid control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	
	int gridMaxCols = 7;  
	int gridMaxRows = rhso.sizeRHS();

			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("RHS status: Empty"));
		InitGridRHS(10, gridMaxCols);
		pMainFrame->m_GridRHS.ShowWindow(SW_SHOW);
		return 10;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridPM.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridPM.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridRHS.SetRowCount(gridMaxRows + 2 );
			pMainFrame->m_GridRHS.SetColumnCount(gridMaxCols);
			pMainFrame->m_GridRHS.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridRHS.SetFixedColumnCount(m_nFixCols);
		    
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return -1;
	    }
        END_CATCH

	//Fill Column Headers
	pMainFrame->m_GridRHS.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridRHS.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridRHS.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridRHS.SetItemText(0, 3, _T("C3"));		
	pMainFrame->m_GridRHS.SetItemText(0, 4, _T("C4"));	
	pMainFrame->m_GridRHS.SetItemText(0, 5, _T("C5"));	
	pMainFrame->m_GridRHS.SetItemText(0, 6, _T("C6"));
	
	pMainFrame->m_GridRHS.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridRHS.SetItemText(1, 1, _T("Action"));
	pMainFrame->m_GridRHS.SetItemText(1, 2, _T("Command"));
	pMainFrame->m_GridRHS.SetItemText(1, 3, _T("Identifier"));		
	pMainFrame->m_GridRHS.SetItemText(1, 4, _T("Attribute"));		
	pMainFrame->m_GridRHS.SetItemText(1, 5, _T("Value"));	
	pMainFrame->m_GridRHS.SetItemText(1, 6, _T("Production"));
	
	

	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	CMainFrame::g_mRHS::iterator iter;
	//Print map container Right Hand Side (PM)
	for( iter = pMainFrame->gmRHS.begin(); iter!= pMainFrame->gmRHS.end(); ++iter)
	{
		//AfxMessageBox(_T("Hola pueblo...."));
		CString strRow = _T("R");
		CString strFact =_T("RHS");
		CString strPM =_T("PM");
		CString strCmd =_T("CMD");

		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
			
		strFact +=  _itot( iter->first, buffer, 10 );
		rhso = (CAipi_RHS)iter->second;
 	
		tstring i = rhso.getId();
		tstring a = rhso.getAttr();
		tstring v = rhso.getVal();
		int pm	  = rhso.getPM();
		int cmd = rhso.getCommand();
		
		strPM +=  _itot( pm, buffer, 10 );
		strRow +=  _itot( nRow, buffer, 10 );
		
		switch( cmd )
		{
		case AIPI_ASSERT:
			strCmd = _T("ASSERT");
			break;
		case AIPI_RETRACT:
			strCmd = _T("RETRACT");
			break;
		case AIPI_OUTPUT:
			strCmd = _T("OUTPUT");
			break;
		case AIPI_INPUT:
			strCmd = _T("INPUT");
			break;
		case AIPI_CTRL_LISTOPTION:
			strCmd = _T("ListOptionCtrl");
			break;
		case AIPI_CTRL_MEDIAPLAYER:
			strCmd = _T("MediaPlayerDlg");
			break;
		case AIPI_CTRL_JUKEBOX:
			strCmd = _T("JukeBoxDlg");
			break;
		case AIPI_CTRL_IMAGEFILTER:
			strCmd = _T("ImageFilter");
			break;
		case AIPI_CTRL_OLEDB:
			strCmd = _T("OleDBDlg");
			break;

		}
			
		
	
		//Fill Rows
		nRow++;
		
		if( nRow <= gridMaxRows + 1 )
		{
			wsprintf(buffer, strRow);
			wsprintf(buffer, strFact);
			wsprintf(buffer, strPM);
			wsprintf(buffer, strCmd);

			wsprintf(buffer, i.c_str());
			wsprintf(buffer, a.c_str());
			wsprintf(buffer, v.c_str());
			
			pMainFrame->m_GridRHS.SetItemText(nRow, 0, strRow);
			pMainFrame->m_GridRHS.SetItemText(nRow, 1, strFact);
			pMainFrame->m_GridRHS.SetItemText(nRow, 2, strCmd);
			pMainFrame->m_GridRHS.SetItemText(nRow, 3, i.c_str());		
			pMainFrame->m_GridRHS.SetItemText(nRow, 4, a.c_str());		
			pMainFrame->m_GridRHS.SetItemText(nRow, 5, v.c_str());	
			pMainFrame->m_GridRHS.SetItemText(nRow, 6, strPM);
			
		}	


		
		strRow.ReleaseBuffer();
		strFact.ReleaseBuffer();
		strPM.ReleaseBuffer();
		strCmd.ReleaseBuffer();

			
		
	}//end for
 	
	
		/*
		//Print map container Alpha Memory
		nRow = 1;
		CMainFrame::g_mCond_AM::iterator itAM;
		for( itAM = pMainFrame->gmCond_AM.begin(); itAM!= pMainFrame->gmCond_AM.end(); ++itAM)
		{
			//AfxMessageBox(_T("Hola pueblo...."));
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, itAM->first*100/gridMaxRows);
		
			strAM = _T("");
			strAM = strA + _itot( itAM->second, buffer, 10 );
			nRow++;
			

			if( nRow <= gridMaxRows + 1)
			{
				wsprintf(buffer, strAM);
				pMainFrame->m_GridPM.SetItemText(nRow, 8, strAM);		
			}

			strAM.ReleaseBuffer();
			
		}
	
		*/
	


		pMainFrame->m_GridRHS.AutoSize();
		StopTimer(T, _T("Production memory RHS process elapsed seconds... "));
			
		
		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		pMainFrame->m_GridRHS.ShowWindow(SW_SHOW);
		str.Format(_T("RHS status: %d elements"), gridMaxRows);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
 			

	m_iMaxRange_RHS = rhso.sizeRHS();
	m_iMinRange_RHS = 0;
	


	return m_iMaxRange_RHS;
}



int CAIPITabView::FillGridWM() 
{
	
	CAipi_WM  wmo;
	TCHAR buffer[24];
	
	CString strAM = _T("");
	CString strA = _T("AM");
	CString str;
	int nRow = 1;
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	
	pMainFrame->m_GridWM.ShowWindow(SW_HIDE);
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading working memory(WM) data to Grid Control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	
	int gridMaxCols = 7;  
	int gridMaxRows = wmo.sizeWM();
	
	//CString st;
	//st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	//AfxMessageBox(st);
			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Working memory(WM) status: Empty"));
		InitGridWM(10, gridMaxCols);
		pMainFrame->m_GridWM.ShowWindow(SW_SHOW);
		return 10;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridPM.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridPM.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridWM.SetRowCount(gridMaxRows + 2);
			pMainFrame->m_GridWM.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridWM.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridWM.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return -1;
	    }
        END_CATCH

	
		//Fill Column Headers
	pMainFrame->m_GridWM.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridWM.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridWM.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridWM.SetItemText(0, 3, _T("C3"));		
	pMainFrame->m_GridWM.SetItemText(0, 4, _T("C4"));	
	pMainFrame->m_GridWM.SetItemText(0, 5, _T("C5"));
	pMainFrame->m_GridWM.SetItemText(0, 6, _T("C6"));
	
	pMainFrame->m_GridWM.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridWM.SetItemText(1, 1, _T("WM"));	
	pMainFrame->m_GridWM.SetItemText(1, 2, _T("Identifier"));		
	pMainFrame->m_GridWM.SetItemText(1, 3, _T("Attribute"));		
	pMainFrame->m_GridWM.SetItemText(1, 4, _T("Value"));	
	pMainFrame->m_GridWM.SetItemText(1, 5, _T("Type"));	
	pMainFrame->m_GridWM.SetItemText(1, 6, _T("AM"));

	
	
		
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	CMainFrame::g_mWM::iterator iter;
	//Print map container
	for( iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		
		CString strRow = _T("R");
		CString strWM =_T("WM");
		CString strType =_T("TYPE");
		//CString s;
		//s.Format(_T("iter first...%d  " ), iter->first);
		//AfxMessageBox(s);
		

		
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, nRow*100/gridMaxRows);
		
		strWM +=  _itot( iter->first, buffer, 10 );
		wmo = (CAipi_WM)iter->second;
 	
		tstring i = wmo.getId();
		tstring a = wmo.getAttr();
		tstring v = wmo.getVal();
		int	type  = wmo.getType();
		
		strType +=  _itot( type, buffer, 10 );
		strRow +=  _itot( nRow, buffer, 10 );

		
		//Fill Rows
		nRow++;
		
		/*
		CString st;
		st.Format(_T("Number Rows...%d  " ), nRow);
		AfxMessageBox(st);
		st.Format(_T("Max Rows...%d  " ), gridMaxRows);
		AfxMessageBox(st);
		*/
		
		if( nRow <= gridMaxRows + 1 )
		{
			wsprintf(buffer, strRow);
			wsprintf(buffer, strWM);
			wsprintf(buffer, strType);

			wsprintf(buffer, i.data());
			wsprintf(buffer, a.data());
			wsprintf(buffer, v.data());
			
			pMainFrame->m_GridWM.SetItemText(nRow, 0, strRow);
			pMainFrame->m_GridWM.SetItemText(nRow, 1, strWM);
			pMainFrame->m_GridWM.SetItemText(nRow, 2, i.data());		
			pMainFrame->m_GridWM.SetItemText(nRow, 3, a.data());		
			pMainFrame->m_GridWM.SetItemText(nRow, 4, v.data());	
			pMainFrame->m_GridWM.SetItemText(nRow, 5, strType);	
			
			//AfxMessageBox(_T("Hola pueblo...."));
		}	
		
		strRow.ReleaseBuffer();
		strWM.ReleaseBuffer();
		strType.ReleaseBuffer();
					
		
	}//end for
 	

/*
		//Print map container Alpha Memory
		nRow = 1;
		CMainFrame::g_mCond_AM::iterator itAM;
		for( itAM = pMainFrame->gmCond_AM.begin(); itAM!= pMainFrame->gmCond_AM.end(); ++itAM)
		{
			//AfxMessageBox(_T("Hola pueblo...."));
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, itAM->first*100/gridMaxRows);
		
			strAM = _T("");
			strAM = strA + _itot( itAM->second, buffer, 10 );
			nRow++;
			

			if( nRow <= gridMaxRows + 1)
			{
				wsprintf(buffer, strAM);
				pMainFrame->m_GridPM.SetItemText(nRow, 8, strAM);		
			}

			strAM.ReleaseBuffer();
			
		}
	
		*/
//AfxMessageBox(_T("HELP"));

		//Print map container Alpha Memory
		nRow = 1;
		int tempWM = 0;
		int n = 0;
		CMainFrame::g_mmWM_AM::iterator itAM;
		for( itAM = pMainFrame->gmmWM_AM.begin(); itAM!= pMainFrame->gmmWM_AM.end(); ++itAM)
		{
			n++;
			/*
			CString st;
			st.Format(_T("CICLO...%d  " ), n);
			AfxMessageBox(st);
			st.Format(_T("Number Row...%d  " ), nRow);
			AfxMessageBox(st);
			st.Format(_T("Working Memory...%d  " ), itAM->first);
			AfxMessageBox(st);
			st.Format(_T("AM...%d  " ), itAM->second);
			AfxMessageBox(st);
			*/
			
			if( itAM->first == tempWM )
			{
				strAM = strAM + _T(", AM") + _itot( itAM->second, buffer, 10 );
				wsprintf(buffer, strAM);
				pMainFrame->m_GridWM.SetItemText(nRow, 6, strAM);
				/*
				AfxMessageBox(_T("ADD1"));
				st.Format(_T("Number Row...%d  " ), nRow);
				AfxMessageBox(st);
				st.Format(_T("AM...%s  " ), strAM);
				AfxMessageBox(st);
				*/
				continue;
				
			}
			
				
			tempWM = itAM->first;
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, nRow*100/gridMaxRows);
			
			nRow++;

			strAM = _T("");
			strAM = strA + _itot( itAM->second, buffer, 10 );
				
			
			if( nRow <= gridMaxRows + 1)
			{
				wsprintf(buffer, strAM);
				pMainFrame->m_GridWM.SetItemText(itAM->first, 6, strAM);

				/*
				AfxMessageBox(_T("ADD2"));
				st.Format(_T("Number Row...%d  " ), nRow);
				AfxMessageBox(st);
				st.Format(_T("AM...%s  " ), strAM);
				AfxMessageBox(st);
				*/
			
			}

			strAM.ReleaseBuffer();
					
		}

		
		pMainFrame->m_GridWM.AutoSize();
		StopTimer(T, _T("Working memory process elapsed seconds... "));
			
		
		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		pMainFrame->m_GridWM.ShowWindow(SW_SHOW);
		str.Format(_T("Working memory(WM) status: %d elements"), gridMaxRows);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);

		m_iMaxRange_WM = gridMaxRows;
		m_iMinRange_WM = 0;
	

return m_iMaxRange_WM;
 			
}


int CAIPITabView::FillGridCondLink() 
{
	
	CAipi_RETE_Links  lnko;
	TCHAR buffer[24];
	
	//CString strAM = _T("");
	//CString strA = _T("A");
	CString str;
	int nRow = 1;
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	
	pMainFrame->m_GridCondLink.ShowWindow(SW_HIDE);
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading Links data to Grid Control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	
	int gridMaxCols = 7;  
	int gridMaxRows = lnko.sizeLinks();
	
	//CString st;
	//st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	//AfxMessageBox(st);
			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Links status: Empty"));
		InitGridCondLink(10, gridMaxCols);
		pMainFrame->m_GridCondLink.ShowWindow(SW_SHOW);
		return 10;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridPM.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridPM.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridCondLink.SetRowCount(gridMaxRows + 2);
			pMainFrame->m_GridCondLink.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridCondLink.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridCondLink.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return -1;
	    }
        END_CATCH

	
		//Fill Column Headers
	pMainFrame->m_GridCondLink.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridCondLink.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridCondLink.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridCondLink.SetItemText(0, 3, _T("C3"));		
	pMainFrame->m_GridCondLink.SetItemText(0, 4, _T("C4"));	
	pMainFrame->m_GridCondLink.SetItemText(0, 5, _T("C5"));
	pMainFrame->m_GridCondLink.SetItemText(0, 6, _T("C6"));
	
	pMainFrame->m_GridCondLink.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridCondLink.SetItemText(1, 1, _T("Condition 1"));	
	pMainFrame->m_GridCondLink.SetItemText(1, 2, _T("Condition 2"));		
	pMainFrame->m_GridCondLink.SetItemText(1, 3, _T("Field 1"));		
	pMainFrame->m_GridCondLink.SetItemText(1, 4, _T("Field 2"));	
	pMainFrame->m_GridCondLink.SetItemText(1, 5, _T("PM"));	
	pMainFrame->m_GridCondLink.SetItemText(1, 6, _T("Variable"));

	
	
		
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	CMainFrame::g_mmLink::iterator iter;
	//Print map container
	for( iter = pMainFrame->gmmLink.begin(); iter!= pMainFrame->gmmLink.end(); ++iter)
	{
		CString strLink = _T("");
		CString strRow = _T("R");
		CString strCond1 =_T("LHS");
		CString strCond2 = _T("LHS");
		CString strField1 = _T("");
		CString strField2 = _T("");
		CString strPM =_T("PM");
		//CString s;
		//s.Format(_T("iter first...%d  " ), iter->first);
		//AfxMessageBox(s);
		

		
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, nRow*100/gridMaxRows);
		
		strLink +=  _itot( iter->first, buffer, 10 );
		lnko = (CAipi_RETE_Links)iter->second;
 	
		int c1 = iter->first;
		int c2 = lnko.getCond2();
		int f1 = lnko.getField1();
		int f2 = lnko.getField2();
		int pm = lnko.getPM();
		tstring var = lnko.getVar();
		
		strCond1 +=  _itot( c1, buffer, 10 );
		strCond2 +=  _itot( c2, buffer, 10 );
		strPM +=  _itot( pm, buffer, 10 );
		strRow +=  _itot( nRow, buffer, 10 );
		
		/*
		CString st;
		st.Format(_T("f1...%d  " ), f1);
		AfxMessageBox(st);
		st.Format(_T("f2...%d  " ), f2);
		AfxMessageBox(st);
		AfxMessageBox(strCond1);
		AfxMessageBox(strCond2);
		*/
		switch( f1 )
		{
			case AIPI_ID:
				strField1 = _T("Identifier");
				break;
			case AIPI_AT:
				strField1 = _T("Attribute");
				break;
            case AIPI_VL:
				strField1 = _T("Value");
				break;
		}
		switch( f2 )
		{
			case AIPI_ID:
				strField2 = _T("Identifier");
				break;
			case AIPI_AT:
				strField2 = _T("Attribute");
				break;
            case AIPI_VL:
				strField2 = _T("Value");
				break;
		}

		
		//Fill Rows
		nRow++;
		
		/*
		CString st;
		st.Format(_T("Number Rows...%d  " ), nRow);
		AfxMessageBox(st);
		st.Format(_T("Max Rows...%d  " ), gridMaxRows);
		AfxMessageBox(st);
		*/
		
		if( nRow <= gridMaxRows + 1 )
		{
			wsprintf(buffer, strRow);
			wsprintf(buffer, strPM);
			wsprintf(buffer, strCond1);
			wsprintf(buffer, strCond2);
			wsprintf(buffer, strField1);
			wsprintf(buffer, strField2);
			
			pMainFrame->m_GridCondLink.SetItemText(nRow, 0, strRow);
			pMainFrame->m_GridCondLink.SetItemText(nRow, 1, strCond1);
			pMainFrame->m_GridCondLink.SetItemText(nRow, 2, strCond2);		
			pMainFrame->m_GridCondLink.SetItemText(nRow, 3, strField1);		
			pMainFrame->m_GridCondLink.SetItemText(nRow, 4, strField2);	
			pMainFrame->m_GridCondLink.SetItemText(nRow, 5, strPM);	
			pMainFrame->m_GridCondLink.SetItemText(nRow, 6, var.c_str());	
			
			//AfxMessageBox(_T("Hola pueblo...."));
		}	
		
		strRow.ReleaseBuffer();
		strCond1.ReleaseBuffer();
		strCond2.ReleaseBuffer();
		strField1.ReleaseBuffer();
		strField2.ReleaseBuffer();
		strPM.ReleaseBuffer();
		
					
		
	}//end for
 	
//AfxMessageBox(_T("HELP"));

		//Print map container Alpha Memory
		/*
		nRow = 1;
		int tempWM = 0;
		CMainFrame::g_mmWM_AM::iterator itAM;
		for( itAM = pMainFrame->gmmWM_AM.begin(); itAM!= pMainFrame->gmmWM_AM.end(); ++itAM)
		{
			
			CString st;
			st.Format(_T("Number Rows...%d  " ), nRow);
			AfxMessageBox(st);
			st.Format(_T("Working Memory...%d  " ), itAM->first);
			AfxMessageBox(st);
			st.Format(_T("AM...%d  " ), itAM->second);
			AfxMessageBox(st);
			

			if( itAM->first == tempWM )
			{
				strAM = strAM + _T(", A") + _itot( itAM->second, buffer, 10 );
				wsprintf(buffer, strAM);
				pMainFrame->m_GridCondLink.SetItemText(nRow, 6, strAM);
				continue;
				
			}
			
			tempWM = itAM->first;
			
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, nRow*100/gridMaxRows);
			
			nRow++;

				strAM = _T("");
				strAM = strA + _itot( itAM->second, buffer, 10 );
				
			
				if( nRow <= gridMaxRows + 1)
				{
					wsprintf(buffer, strAM);
					pMainFrame->m_GridCondLinks.SetItemText(itAM->first, 6, strAM);
				
				}

				strAM.ReleaseBuffer();
					
		}

		*/
		pMainFrame->m_GridCondLink.AutoSize();
		StopTimer(T, _T("Links process elapsed seconds... "));
			
		
		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		pMainFrame->m_GridCondLink.ShowWindow(SW_SHOW);
		str.Format(_T("Links status: %d elements"), gridMaxRows);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);

		m_iMaxRange_CLink = gridMaxRows;
		m_iMinRange_CLink = 0;
	

return m_iMaxRange_CLink;
 			
}

int CAIPITabView::FillGridAgenda() 
{
	
	CAipi_RETE_BM  bmo;
	
	TCHAR buffer[BUFF_SIZE];
	CString str;
	int nRow =1;
	
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridAgenda.ShowWindow(SW_HIDE);
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading Agenda data to grid control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	int gridMaxCols = 2;  
	int gridMaxRows = pMainFrame->g_vAgendaPM.size();
	
	
	/*
	CString st;
	st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	AfxMessageBox(st);
	*/	

			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Agenda status: Empty"));
		InitGridAgenda(10, gridMaxCols);
		pMainFrame->m_GridAgenda.ShowWindow(SW_SHOW);
		return 10;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridBM.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridBM.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridAgenda.SetRowCount(gridMaxRows + 2 );
			pMainFrame->m_GridAgenda.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridAgenda.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridAgenda.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return -1;
	    }
        END_CATCH

	//Fill Column Headers
	pMainFrame->m_GridAgenda.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridAgenda.SetItemText(0, 1, _T("C1"));	
	
	pMainFrame->m_GridAgenda.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridAgenda.SetItemText(1, 1, _T("PM"));	
	
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	


	
	//Print agenda
	
	for( long i = 0; i < pMainFrame->g_vAgendaPM.size(); ++i)
	{
		CString strRow = _T("R");
		CString strPM =_T("PM");
		
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, i*100/gridMaxRows);
		
		long pm = pMainFrame->g_vAgendaPM.at(i);	
		
		strRow		+=  _itot( nRow, buffer, 10 );
		strPM		+=  _itot( pm, buffer, 10 );
		
		
		nRow++;
		
		/*
		CString st;
		st.Format(_T("Number Rows...%d  " ), nRow);
		AfxMessageBox(st);
		*/			
		
		if( nRow <= gridMaxRows + 1)
		{
			
			wsprintf(buffer, strPM);
			
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 0, strRow);
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 1, strPM);
						
			
		}
				
		strRow.ReleaseBuffer();
		strPM.ReleaseBuffer();
		
	}//end for
 	
	
		

	
	pMainFrame->m_GridAgenda.AutoSize();
	StopTimer(T, _T("Agenda process elapsed seconds... "));
			
		
	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	pMainFrame->m_GridAgenda.ShowWindow(SW_SHOW);

	str.Format(_T("Agenda status: %d elements"), gridMaxRows);
	pMainFrame->m_wndOutputTabView.AddMsg1(str);


	m_iMaxRange_Agenda = pMainFrame->g_vAgendaPM.size();
	m_iMinRange_Agenda = 0;
	
 		

return m_iMaxRange_Agenda;
 			
}



int CAIPITabView::FillGridAM() 
{
	
	CAipi_RETE_AM  amo;
	TCHAR buffer[BUFF_SIZE];
	CString strCond = _T("");
	CString strC = _T("LHS");
	CString strComa = _T(", ");
	CString strWM =_T("");
	CString strW = _T("WM");
	
	CString str;
	int nRow =1;
	int prevAM = 0;

	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridAM.ShowWindow(SW_HIDE);
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading alpha memory(AM) data to grid control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	int gridMaxCols = 4;  
	//AfxMessageBox(_T("Hola pueblo...."));
	int gridMaxRows = amo.lastAM();
	
	
	/*
	CString st;
	st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	AfxMessageBox(st);
	*/	

			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Alpha memory(AM) status: Empty"));
		InitGridAM(10, gridMaxCols);
		pMainFrame->m_GridAM.ShowWindow(SW_SHOW);
		return 10;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridAM.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridAM.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridAM.SetRowCount(gridMaxRows + 2 );
			pMainFrame->m_GridAM.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridAM.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridAM.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return -1;
	    }
        END_CATCH

	//Fill Column Headers
	pMainFrame->m_GridAM.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridAM.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridAM.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridAM.SetItemText(0, 3, _T("C3"));		
	
	pMainFrame->m_GridAM.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridAM.SetItemText(1, 1, _T("AM"));	
	pMainFrame->m_GridAM.SetItemText(1, 2, _T("Conditions"));		
	pMainFrame->m_GridAM.SetItemText(1, 3, _T("WM"));		
	

	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	


	
	//Print map container with Conditions
	CMainFrame::g_mmAM_Cond::iterator iter;
	for( iter = pMainFrame->gmmAM_Cond.begin(); iter!= pMainFrame->gmmAM_Cond.end(); ++iter)
	{
		
		CString strRow = _T("R");
		CString strAM =_T("AM");
		
		
		//pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
			
		if( iter->first != prevAM )
		{
			strCond = _T("");
			int nAM = amo.countAM_Cond(iter->first);
			strAM	+=  _itot( iter->first, buffer, 10 );
			strCond += strC	 + _itot( iter->second, buffer, 10 );
			strRow	+=  _itot( nRow, buffer, 10 );
			nRow++;
			prevAM = iter->first;

			if( nRow <= gridMaxRows + 1)
			{
				wsprintf(buffer, strRow);
				wsprintf(buffer, strAM);
				pMainFrame->m_GridAM.SetItemText(nRow, 0, strRow);
				pMainFrame->m_GridAM.SetItemText(nRow, 1, strAM);
			
				if( nAM <= 1 )
				{
					wsprintf(buffer, strCond);
					pMainFrame->m_GridAM.SetItemText(nRow, 2, strCond);		
				}
			}
			
		}
		else
		{
			strCond +=	strComa + strC + _itot( iter->second, buffer, 10 );
			if( nRow <= gridMaxRows + 1 )
			{
				wsprintf(buffer, strCond);
				pMainFrame->m_GridAM.SetItemText(nRow, 2, strCond);		
			
			}
			
		}
				
		strRow.ReleaseBuffer();
		strAM.ReleaseBuffer();
		strCond.ReleaseBuffer();
		
			
		
	}//end for
 	


	
	//Print map container with Working Memory Elements
	prevAM = 0;
	nRow = 1;
	for( iter = pMainFrame->gmmAM_WM.begin(); iter!= pMainFrame->gmmAM_WM.end(); ++iter)
	{
		
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
		
		if( iter->first != prevAM )
		{
			strWM = _T("");
			int nAM = amo.countAM_WM(iter->first);
			strWM += strW + _itot( iter->second, buffer, 10 );
			nRow++;
			prevAM = iter->first;

			if( nRow <= gridMaxRows + 1)
			{
				if( nAM <= 1 )
				{
					wsprintf(buffer, strWM);
					pMainFrame->m_GridAM.SetItemText(nRow, 3, strWM);		
				}
			}
			
		}
		else
		{
			strWM +=	strComa + strW + _itot( iter->second, buffer, 10 );
			if( nRow <= gridMaxRows + 1 )
			{
				wsprintf(buffer, strWM);
				pMainFrame->m_GridAM.SetItemText(nRow, 3, strWM);		
			
			}
			
		}
		
		strWM.ReleaseBuffer();	

	}
	
	


	pMainFrame->m_GridAM.AutoSize();
	StopTimer(T, _T("Alpha Memory process elapsed seconds... "));
			
		
	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	pMainFrame->m_GridAM.ShowWindow(SW_SHOW);

	str.Format(_T("Alpha memory(AM) status: %d elements"), gridMaxRows);
	pMainFrame->m_wndOutputTabView.AddMsg1(str);


	m_iMaxRange_AM = gridMaxRows;
	m_iMinRange_AM = 0;
	
 		

return m_iMaxRange_AM;
 			
}


int CAIPITabView::FillGridBM() 
{
	
	CAipi_RETE_BM  bmo;
	CAipi_RETE_TK  tko;

	TCHAR buffer[BUFF_SIZE];
	CString strComa = _T(", ");
	CString strWM =_T("");
	
	CString str;
	int nRow =1;
	int prevBM = 0;

	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridBM.ShowWindow(SW_HIDE);
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading beta memory(BM) data to grid control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	int gridMaxCols = 3;  
	int gridMaxRows = bmo.lastBM();
	
	
	/*
	CString st;
	st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	AfxMessageBox(st);
	*/	

			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Beta memory(BM) status: Empty"));
		InitGridBM(10, gridMaxCols);
		pMainFrame->m_GridBM.ShowWindow(SW_SHOW);
		return 10;
	}
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridBM.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridBM.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridBM.SetRowCount(gridMaxRows + 2 );
			pMainFrame->m_GridBM.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridBM.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridBM.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return -1;
	    }
        END_CATCH

	//Fill Column Headers
	pMainFrame->m_GridBM.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridBM.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridBM.SetItemText(0, 2, _T("C2"));		
	//pMainFrame->m_GridBM.SetItemText(0, 3, _T("C3"));
	//pMainFrame->m_GridBM.SetItemText(0, 4, _T("C4"));
	//pMainFrame->m_GridBM.SetItemText(0, 5, _T("C5"));
	//pMainFrame->m_GridBM.SetItemText(0, 6, _T("C6"));
	//pMainFrame->m_GridBM.SetItemText(0, 7, _T("C7"));
	//pMainFrame->m_GridBM.SetItemText(0, 8, _T("C8"));

	pMainFrame->m_GridBM.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridBM.SetItemText(1, 1, _T("BM"));	
	pMainFrame->m_GridBM.SetItemText(1, 2, _T("Linked WMEs"));		
	//pMainFrame->m_GridBM.SetItemText(1, 3, _T("Parent Tk"));		
	//pMainFrame->m_GridBM.SetItemText(1, 4, _T("Child Tk"));
	//pMainFrame->m_GridBM.SetItemText(1, 5, _T("Id. Var"));	
	//pMainFrame->m_GridBM.SetItemText(1, 6, _T("Id. Data"));		
	//pMainFrame->m_GridBM.SetItemText(1, 7, _T("Val. Var"));		
	//pMainFrame->m_GridBM.SetItemText(1, 8, _T("Val. Data"));	

	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	


	
	//Print map container with Conditions
	CMainFrame::g_mmBM::iterator iter;
	for( iter = pMainFrame->gmmBM.begin(); iter!= pMainFrame->gmmBM.end(); ++iter)
	{
		
		CString strRow = _T("R");
		CString strBM =_T("BM");
		/*
		CString st;
		st.Format(_T("Number Rows...%d  " ), nRow);
		AfxMessageBox(st);
		*/	
		
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
		bmo = (CAipi_RETE_BM)iter->second;	
		
		if( iter->first != prevBM )
		{
			strWM = _T("");
			int nBM = bmo.countBM(iter->first);
			strBM	+=  _itot( iter->first, buffer, 10 );
			int chld_tk = bmo.getChildTK();
			tstring  sLink =  tko.linkWMEs(chld_tk);	
			strWM += sLink.data();
			strRow	+=  _itot( nRow, buffer, 10 );
			nRow++;
			prevBM = iter->first;
		

			if( nRow <= gridMaxRows + 1)
			{
				wsprintf(buffer, strRow);
				wsprintf(buffer, strBM);
				pMainFrame->m_GridBM.SetItemText(nRow, 0, strRow);
				pMainFrame->m_GridBM.SetItemText(nRow, 1, strBM);
						
				if( nBM <= 1 )
				{
					wsprintf(buffer, strWM);
					pMainFrame->m_GridBM.SetItemText(nRow, 2, strWM);		
				}
			}
			
		}
		else
		{
			int chld_tk = bmo.getChildTK();
			tstring  link_wme	=  tko.linkWMEs(chld_tk);	
			strWM += strComa + link_wme.data();
			
			if( nRow <= gridMaxRows + 1 )
			{
				wsprintf(buffer, strWM);
				pMainFrame->m_GridBM.SetItemText(nRow, 2, strWM);
				
			
			}
			
		}
				
		strRow.ReleaseBuffer();
		strBM.ReleaseBuffer();
		strWM.ReleaseBuffer();
		
			
		
	}//end for
 	


	
	pMainFrame->m_GridBM.AutoSize();
	StopTimer(T, _T("Beta Memory process elapsed seconds... "));
			
		
	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	pMainFrame->m_GridBM.ShowWindow(SW_SHOW);

	str.Format(_T("Beta memory(BM) status: %d elements"), gridMaxRows);
	pMainFrame->m_wndOutputTabView.AddMsg1(str);

	m_iMaxRange_BM = gridMaxRows;
	m_iMinRange_BM = 0;
	
 	
	
return m_iMaxRange_BM;
 			
}


int CAIPITabView::FillGridBM_TK() 
{
	
	CAipi_RETE_BM  bmo;
	
	TCHAR buffer[BUFF_SIZE];
	CString str;
	int nRow =1;
	
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridBM_TK.ShowWindow(SW_HIDE);
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading beta memory(BM) data to grid control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	int gridMaxCols = 9;  
	int gridMaxRows = bmo.sizeBM();
	
	
	/*
	CString st;
	st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	AfxMessageBox(st);
	*/	

			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Beta memory(BM) tokens(TK) status: Empty"));
		InitGridBM_TK(10, gridMaxCols);
		pMainFrame->m_GridBM_TK.ShowWindow(SW_SHOW);
		return 10;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridBM.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridBM.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridBM_TK.SetRowCount(gridMaxRows + 2 );
			pMainFrame->m_GridBM_TK.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridBM_TK.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridBM_TK.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return -1;
	    }
        END_CATCH

	//Fill Column Headers
	pMainFrame->m_GridBM_TK.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridBM_TK.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridBM_TK.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridBM_TK.SetItemText(0, 3, _T("C3"));
	pMainFrame->m_GridBM_TK.SetItemText(0, 4, _T("C4"));
	pMainFrame->m_GridBM_TK.SetItemText(0, 5, _T("C5"));
	pMainFrame->m_GridBM_TK.SetItemText(0, 6, _T("C6"));
	pMainFrame->m_GridBM_TK.SetItemText(0, 7, _T("C7"));
	pMainFrame->m_GridBM_TK.SetItemText(0, 8, _T("C8"));

	pMainFrame->m_GridBM_TK.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridBM_TK.SetItemText(1, 1, _T("BM"));	
	pMainFrame->m_GridBM_TK.SetItemText(1, 2, _T("WM"));		
	pMainFrame->m_GridBM_TK.SetItemText(1, 3, _T("Parent Tk"));		
	pMainFrame->m_GridBM_TK.SetItemText(1, 4, _T("Child Tk"));
	pMainFrame->m_GridBM_TK.SetItemText(1, 5, _T("Id. Var"));	
	pMainFrame->m_GridBM_TK.SetItemText(1, 6, _T("Id. Data"));		
	pMainFrame->m_GridBM_TK.SetItemText(1, 7, _T("Val. Var"));		
	pMainFrame->m_GridBM_TK.SetItemText(1, 8, _T("Val. Data"));	

	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	


	
	//Print map container with Conditions
	CMainFrame::g_mmBM::iterator iter;
	for( iter = pMainFrame->gmmBM.begin(); iter!= pMainFrame->gmmBM.end(); ++iter)
	{
		
		CString strRow = _T("R");
		CString strBM =_T("BM");
		CString strWM = _T("WM");
		CString strTKP = _T("TK");
		CString strTKC = _T("TK");
		


		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
		
		bmo = (CAipi_RETE_BM)iter->second;	
		
		strRow		+=  _itot( nRow, buffer, 10 );
		strBM		+=  _itot( iter->first, buffer, 10 );
		
		int		wm		= bmo.getWM();
		int		pnt_tk  = bmo.getParentTK();
		int		chld_tk = bmo.getChildTK();
		tstring var1	= bmo.getVar1();
		tstring data1	= bmo.getData1();
		tstring var2	= bmo.getVar2();
		tstring data2	= bmo.getData2();


		strWM		+=  _itot( wm, buffer, 10 );
		strTKC		+=  _itot( chld_tk, buffer, 10 );
		if( pnt_tk == DNode )
			strTKP = _T("DNode");
		else
			strTKP		+=  _itot( pnt_tk, buffer, 10 );
		
		nRow++;
		
		/*
		CString st;
		st.Format(_T("Number Rows...%d  " ), nRow);
		AfxMessageBox(st);
		*/			
		
		if( nRow <= gridMaxRows + 1)
		{
			
			wsprintf(buffer, strRow);
			wsprintf(buffer, strBM);
			wsprintf(buffer, strWM);
			wsprintf(buffer, strTKP);
			wsprintf(buffer, strTKC);

			wsprintf(buffer, var1.data());
			wsprintf(buffer, data1.data());
			wsprintf(buffer, var2.data());
			wsprintf(buffer, data2.data());

			pMainFrame->m_GridBM_TK.SetItemText(nRow, 0, strRow);
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 1, strBM);
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 2, strWM);
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 3, strTKP);
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 4, strTKC);
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 5, var1.data());
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 6, data1.data());
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 7, var2.data());
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 8, data2.data());
						
			
		}
				
		strRow.ReleaseBuffer();
		strBM.ReleaseBuffer();
		strWM.ReleaseBuffer();
		strTKP.ReleaseBuffer();
		strTKC.ReleaseBuffer();	
		
	}//end for
 	
	
		

	
	pMainFrame->m_GridBM_TK.AutoSize();
	StopTimer(T, _T("Beta Memory Tokens process elapsed seconds... "));
			
		
	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	pMainFrame->m_GridBM_TK.ShowWindow(SW_SHOW);

	str.Format(_T("Beta memory(BM) tokens(TK) status: %d elements"), gridMaxRows);
	pMainFrame->m_wndOutputTabView.AddMsg1(str);


	m_iMaxRange_BM_TK = bmo.lastBM();
	m_iMinRange_BM_TK = 0;
	
 		

return m_iMaxRange_BM_TK;
 			
}


int CAIPITabView::FillGridRETE() 
{
	
	CAipi_RETE_Node  no;
	CAipi_RETE_JNode jno;
	
	TCHAR buffer[24];
	
	CString str;
	CString strType = _T("");
	int nRow = 1;
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridRETE.ShowWindow(SW_HIDE);
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading Rete net information to Grid Control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	
	int gridMaxCols = 7;  
	int gridMaxRows = no.sizeNode();
	/*
	CString st;
	st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	AfxMessageBox(st);
	*/		
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("RETE nodes status: Empty"));
		InitGridRETE(10, gridMaxCols);
		pMainFrame->m_GridRETE.ShowWindow(SW_SHOW);
		return 10;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridRETE.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridRETE.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridRETE.SetRowCount(gridMaxRows + 2);
			pMainFrame->m_GridRETE.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridRETE.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridRETE.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return -1;
	    }
        END_CATCH

	
		//Fill Column Headers
	pMainFrame->m_GridRETE.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridRETE.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridRETE.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridRETE.SetItemText(0, 3, _T("C3"));		
	pMainFrame->m_GridRETE.SetItemText(0, 4, _T("C4"));	
	pMainFrame->m_GridRETE.SetItemText(0, 5, _T("C5"));
	pMainFrame->m_GridRETE.SetItemText(0, 6, _T("C6"));
	
	pMainFrame->m_GridRETE.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridRETE.SetItemText(1, 1, _T("Node"));	
	pMainFrame->m_GridRETE.SetItemText(1, 2, _T("Type"));		
	pMainFrame->m_GridRETE.SetItemText(1, 3, _T("Parent BM"));		
	pMainFrame->m_GridRETE.SetItemText(1, 4, _T("Child BM"));	
	pMainFrame->m_GridRETE.SetItemText(1, 5, _T("AM"));	
	pMainFrame->m_GridRETE.SetItemText(1, 6, _T("Linked Variable"));
	
		
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	CMainFrame::g_mNode::iterator iter;
	//Print map container
	for( iter = pMainFrame->gmNode.begin(); iter!= pMainFrame->gmNode.end(); ++iter)
	{
		
		CString strRow = _T("R");
		CString strNode =_T("N");
		CString strBM1 =_T("BM");
		CString strBM2 =_T("BM");
		CString strAM = _T("AM");
	

		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
		
		strNode +=  _itot( iter->first, buffer, 10 );
		no = (CAipi_RETE_Node)iter->second;
 	
		int type	= no.getType();
		int bm1		= no.getParent();
		int bm2		= no.getChild();
		int am		= no.getAM();
		
		switch(type)
		{
		case DNode:
			strType = _T("Dummy Node");
			break;
		case JNode:
			strType = _T("Join Node");
			break;
		case NNode:
			strType = _T("Negated Node");
			break;
		case PNode:
			strType = _T("Production Node");
			break;
		case NCCNode:
			strType = _T("Negated Conjunctive Condition Node");
			break;
		case FPNode:
			strType = _T("Fired Production Node");
			break;
		case NumNode :
			strType = _T("Numeric Node");
			break;

		}
		
		strBM1	+=  _itot( bm1, buffer, 10 );
		strBM2	+=  _itot( bm2, buffer, 10 );
		strAM	+=  _itot( am, buffer, 10 );
		strRow	+=  _itot( nRow, buffer, 10 );
		
		//Fill Rows
		nRow++;
		/*
		CString st;
		st.Format(_T("Number Rows...%d  " ), nRow);
		AfxMessageBox(st);
		*/	
		
		if( nRow <= gridMaxRows + 1 )
		{
			wsprintf(buffer, strRow);
			wsprintf(buffer, strNode);
			wsprintf(buffer, strType);
			wsprintf(buffer, strBM1);
			wsprintf(buffer, strBM2);
			wsprintf(buffer, strAM);
			
			pMainFrame->m_GridRETE.SetItemText(nRow, 0, strRow);
			pMainFrame->m_GridRETE.SetItemText(nRow, 1, strNode);
			pMainFrame->m_GridRETE.SetItemText(nRow, 2, strType);		
			pMainFrame->m_GridRETE.SetItemText(nRow, 3, strBM1);		
			pMainFrame->m_GridRETE.SetItemText(nRow, 4, strBM2);	
			pMainFrame->m_GridRETE.SetItemText(nRow, 5, strAM);	
			
			//AfxMessageBox(_T("Hola pueblo...."));
		}	
		
		strRow.ReleaseBuffer();
		strNode.ReleaseBuffer();
		strType.ReleaseBuffer();
		strBM1.ReleaseBuffer();
		strBM2.ReleaseBuffer();
		strAM.ReleaseBuffer();
					
		
	}//end for
 	

		//Print map container Alpha Memory
		nRow = 1;
		CMainFrame::g_mJNode::iterator itJN;
		for( itJN = pMainFrame->gmJNode.begin(); itJN!= pMainFrame->gmJNode.end(); ++itJN)
		{
			/*
			CString st;
			st.Format(_T("Number Rows...%d  " ), nRow);
			AfxMessageBox(st);
			st.Format(_T("Working Memoery...%d  " ), itJN->first);
			AfxMessageBox(st);
			*/	
		
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, itJN->first*100/gridMaxRows);
			jno = (CAipi_RETE_JNode)itJN->second;
			
			CString strVar = jno.getVar().data();
			
			nRow++;

				if( nRow <= gridMaxRows + 1)
				{
					wsprintf(buffer, strVar);
					pMainFrame->m_GridRETE.SetItemText(nRow, 6, strVar);
				
				}
			strVar.ReleaseBuffer();
					
		}

		
		
		pMainFrame->m_GridRETE.AutoSize();
		StopTimer(T, _T("RETE Nodes process elapsed seconds... "));
			
		
		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		pMainFrame->m_GridRETE.ShowWindow(SW_SHOW);
		str.Format(_T("Rete nodes status: %d elements"), gridMaxRows);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);


	m_iMaxRange_RETE = gridMaxRows;
	m_iMinRange_RETE = 0;
	

return m_iMaxRange_RETE;
 			
}



void CAIPITabView::FillRangeGridLHS() 
{
	
	CAipi_LHS		lhso;
	
	TCHAR buffer[24];
	CString strRel = _T("");
	CString strAM = _T("");
	CString strA =_T("AM");
	CString str;
	int nRow =1;
	int tempMinCond = 0;
	int tempMaxCond = 0;

	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridLHS.ShowWindow(SW_HIDE);
	pMainFrame->m_GridLHS.DeleteAllItems();
	
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading LHS data to grid control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	
	int gridMaxCols = 9;  
	int gridMaxRows = lhso.sizeLHS();
	int maxCond = 0;
	int minCond = gridMaxRows;

	
			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("LHS status: Empty"));
		InitGridLHS(10, gridMaxCols);
		pMainFrame->m_GridLHS.ShowWindow(SW_SHOW);
		return;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridLHS.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridLHS.GetFixedRowCount();
	*/
		
		TRY 
		{
		    pMainFrame->m_GridLHS.SetRowCount(2 );
			pMainFrame->m_GridLHS.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridLHS.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridLHS.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH


	//Fill Column Headers
	pMainFrame->m_GridLHS.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridLHS.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridLHS.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridLHS.SetItemText(0, 3, _T("C3"));		
	pMainFrame->m_GridLHS.SetItemText(0, 4, _T("C4"));	
	pMainFrame->m_GridLHS.SetItemText(0, 5, _T("C5"));	
	pMainFrame->m_GridLHS.SetItemText(0, 6, _T("C6"));
	pMainFrame->m_GridLHS.SetItemText(0, 7, _T("C7"));
	pMainFrame->m_GridLHS.SetItemText(0, 8, _T("C8"));

	pMainFrame->m_GridLHS.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridLHS.SetItemText(1, 1, _T("Condition"));	
	pMainFrame->m_GridLHS.SetItemText(1, 2, _T("Identifier"));		
	pMainFrame->m_GridLHS.SetItemText(1, 3, _T("Attribute"));		
	pMainFrame->m_GridLHS.SetItemText(1, 4, _T("Value"));	
	pMainFrame->m_GridLHS.SetItemText(1, 5, _T("Operator"));	
	pMainFrame->m_GridLHS.SetItemText(1, 6, _T("Production"));
	pMainFrame->m_GridLHS.SetItemText(1, 7, _T("Category"));
	pMainFrame->m_GridLHS.SetItemText(1, 8, _T("AM"));


	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	CMainFrame::g_mLHS::iterator iter;
	//Print map container Left Hand Side (PM)
	for( iter = pMainFrame->gmLHS.begin(); iter!= pMainFrame->gmLHS.end(); ++iter)
	{
		

		//AfxMessageBox(_T("Hola pueblo...."));
		
		CString strRow = _T("R");
		CString strCond =_T("LHS");
		CString strPM =_T("PM");
		CString strCateg =_T("CATEG");

		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
			
		strCond +=  _itot( iter->first, buffer, 10 );
		lhso = (CAipi_LHS)iter->second;
 	
		int pm	  = lhso.getPM();
		
		

		if( pm >= m_iMinRange_LHS  && pm <= m_iMaxRange_LHS )
		{
						
			tempMaxCond = iter->first;
			tempMinCond = iter->first;

			if(tempMaxCond > maxCond)
			{
				maxCond = tempMaxCond;
			}
			if( tempMinCond < minCond )
			{
				minCond = tempMinCond;
			}
		
			/*
			CString st;
			st.Format(_T("PM...%d  " ), pm);
			AfxMessageBox(st);
			*/
			int	rel	  = lhso.getRel();
			int categ = lhso.getCategory();
			tstring i = lhso.getId();
			tstring a = lhso.getAttr();
			tstring v = lhso.getVal();
		
		
		
			strPM +=  _itot( pm, buffer, 10 );
			strCateg +=  _itot( categ, buffer, 10 );
			strRow +=  _itot( nRow, buffer, 10 );

			switch(rel)
			{
				case 100: 
					strRel =_T("EQ");
				break;
				case 101: 
					strRel =_T("LT");
				break;
				case 102: 
					strRel =_T("LE");
				break;
				case 103: 
					strRel =_T("GT");
				break;
				case 104: 
					strRel =_T("GE");
				break;
				case 105: 
					strRel =_T("ET");
				break;
				case 106: 
					strRel =_T("NE");
				break;
				case 107: 
					strRel =_T("AS");
				break;

			}
		
	
			//Fill Rows
			nRow++;
		
			if( nRow <= gridMaxRows + 1 )
			{
				TRY 
				{
					pMainFrame->m_GridLHS.SetRowCount(nRow + 1 );
					pMainFrame->m_GridLHS.SetColumnCount(gridMaxCols);
				}
				CATCH (CMemoryException, e)
				{
	    			e->ReportError();
    				return;
				}
				END_CATCH

				
				
				wsprintf(buffer, strRow);
				wsprintf(buffer, strCond);
				wsprintf(buffer, strRel);
				wsprintf(buffer, strPM);
				wsprintf(buffer, strCateg);

				wsprintf(buffer, i.data());
				wsprintf(buffer, a.data());
				wsprintf(buffer, v.data());
			
				pMainFrame->m_GridLHS.SetItemText(nRow, 0, strRow);
				pMainFrame->m_GridLHS.SetItemText(nRow, 1, strCond);
				pMainFrame->m_GridLHS.SetItemText(nRow, 2, i.data());		
				pMainFrame->m_GridLHS.SetItemText(nRow, 3, a.data());		
				pMainFrame->m_GridLHS.SetItemText(nRow, 4, v.data());	
				pMainFrame->m_GridLHS.SetItemText(nRow, 5, strRel);	
				pMainFrame->m_GridLHS.SetItemText(nRow, 6, strPM);
				pMainFrame->m_GridLHS.SetItemText(nRow, 7, strCateg);
				


		
			strRow.ReleaseBuffer();
			strCond.ReleaseBuffer();
			strRel.ReleaseBuffer();
			strPM.ReleaseBuffer();
			strCateg.ReleaseBuffer();
			
			}
		
		}//end if

			
		
	}//end for
 	
	
		
		//Print map container Alpha Memory
		nRow = 1;
		CMainFrame::g_mCond_AM::iterator itAM;
		for( itAM = pMainFrame->gmCond_AM.begin(); itAM!= pMainFrame->gmCond_AM.end(); ++itAM)
		{
			//AfxMessageBox(_T("Hola pueblo...."));
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, itAM->first*100/gridMaxRows);
		
			if( itAM->first >= minCond && itAM->first <= maxCond)
			{
				strAM = _T("");
				strAM = strA + _itot( itAM->second, buffer, 10 );
				nRow++;
			

				if( nRow <= gridMaxRows + 1)
				{
					wsprintf(buffer, strAM);
					pMainFrame->m_GridLHS.SetItemText(nRow, 8, strAM);		
				}

				strAM.ReleaseBuffer();
				
			}
			
		}
	
		
		pMainFrame->m_GridLHS.AutoSize();
		StopTimer(T, _T("LHS process elapsed seconds... "));
			
		
		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		pMainFrame->m_GridLHS.ShowWindow(SW_SHOW);
		str.Format(_T("LHS status: %d elements"), gridMaxRows);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
			
}


void CAIPITabView::FillRangeGridRHS() 
{
	
	CAipi_RHS		rhso;
	
	TCHAR buffer[24];
	CString strRel = _T("");
	//CString strAM = _T("");
	//CString strA =_T("A");
	CString str;
	int nRow =1;
	int tempMinCond = 0;
	int tempMaxCond = 0;

	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridRHS.ShowWindow(SW_HIDE);
	pMainFrame->m_GridRHS.DeleteAllItems();
	
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading RHS data to grid control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	
	int gridMaxCols = 9;  
	int gridMaxRows = rhso.sizeRHS();
	int maxCond = 0;
	int minCond = gridMaxRows;

	
			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("RHS status: Empty"));
		InitGridRHS(10, gridMaxCols);
		pMainFrame->m_GridRHS.ShowWindow(SW_SHOW);
		return;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridLHS.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridLHS.GetFixedRowCount();
	*/
		
		TRY 
		{
		    pMainFrame->m_GridRHS.SetRowCount(2 );
			pMainFrame->m_GridRHS.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridRHS.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridRHS.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH


	//Fill Column Headers
	pMainFrame->m_GridRHS.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridRHS.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridRHS.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridRHS.SetItemText(0, 3, _T("C3"));		
	pMainFrame->m_GridRHS.SetItemText(0, 4, _T("C4"));	
	pMainFrame->m_GridRHS.SetItemText(0, 5, _T("C5"));	
	pMainFrame->m_GridRHS.SetItemText(0, 6, _T("C6"));
	
	pMainFrame->m_GridRHS.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridRHS.SetItemText(1, 1, _T("Fact"));	
	pMainFrame->m_GridRHS.SetItemText(1, 2, _T("Identifier"));		
	pMainFrame->m_GridRHS.SetItemText(1, 3, _T("Attribute"));		
	pMainFrame->m_GridRHS.SetItemText(1, 4, _T("Value"));	
	pMainFrame->m_GridRHS.SetItemText(1, 5, _T("Production"));
	pMainFrame->m_GridRHS.SetItemText(1, 6, _T("Command"));
	

	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	CMainFrame::g_mRHS::iterator iter;
	//Print map container Left Hand Side (PM)
	for( iter = pMainFrame->gmRHS.begin(); iter!= pMainFrame->gmRHS.end(); ++iter)
	{
		

		//AfxMessageBox(_T("Hola pueblo...."));
		
		CString strRow = _T("R");
		CString strFact =_T("RHS");
		CString strPM =_T("PM");
		CString strCmd =_T("CMD");

		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
			
		strFact +=  _itot( iter->first, buffer, 10 );
		rhso = (CAipi_RHS)iter->second;
 	
		int pm	  = rhso.getPM();
		
		

		if( pm >= m_iMinRange_RHS  && pm <= m_iMaxRange_RHS )
		{
						
			tempMaxCond = iter->first;
			tempMinCond = iter->first;

			if(tempMaxCond > maxCond)
			{
				maxCond = tempMaxCond;
			}
			if( tempMinCond < minCond )
			{
				minCond = tempMinCond;
			}
		
			/*
			CString st;
			st.Format(_T("PM...%d  " ), pm);
			AfxMessageBox(st);
			*/
			//int	rel	  = rhso.getRel();
			int cmd = rhso.getCommand();
			tstring i = rhso.getId();
			tstring a = rhso.getAttr();
			tstring v = rhso.getVal();
		
		
		
			strPM +=  _itot( pm, buffer, 10 );
			strCmd +=  _itot( cmd, buffer, 10 );
			strRow +=  _itot( nRow, buffer, 10 );

			
			switch(cmd)
			{
				case AIPI_CTRL_LISTOPTION: 
					strCmd =_T("ListOptionCtrl");
				break;
				case AIPI_CTRL_IMAGEFILTER: 
					strCmd =_T("ImageFilterDlg");
				break;
				case AIPI_CTRL_MEDIAPLAYER: 
					strCmd =_T("MediaPlayerDlg");
				break;
				case AIPI_CTRL_JUKEBOX: 
					strCmd =_T("JukeBoxDlg");
				break;
				case AIPI_CTRL_OLEDB: 
					strCmd =_T("OleDBDlg");
				break;
				case AIPI_OUTPUT: 
					strCmd =_T("Output");
				break;
				case AIPI_INPUT: 
					strRel =_T("Input");
				break;
				

			}
		
	
			//Fill Rows
			nRow++;
		
			if( nRow <= gridMaxRows + 1 )
			{
				TRY 
				{
					pMainFrame->m_GridRHS.SetRowCount(nRow + 1 );
					pMainFrame->m_GridRHS.SetColumnCount(gridMaxCols);
				}
				CATCH (CMemoryException, e)
				{
	    			e->ReportError();
    				return;
				}
				END_CATCH

				
				
				wsprintf(buffer, strRow);
				wsprintf(buffer, strFact);
				wsprintf(buffer, strRel);
				wsprintf(buffer, strPM);
				wsprintf(buffer, strCmd);

				wsprintf(buffer, i.data());
				wsprintf(buffer, a.data());
				wsprintf(buffer, v.data());
			
				pMainFrame->m_GridRHS.SetItemText(nRow, 0, strRow);
				pMainFrame->m_GridRHS.SetItemText(nRow, 1, strFact);
				pMainFrame->m_GridRHS.SetItemText(nRow, 2, i.data());		
				pMainFrame->m_GridRHS.SetItemText(nRow, 3, a.data());		
				pMainFrame->m_GridRHS.SetItemText(nRow, 4, v.data());	
				pMainFrame->m_GridRHS.SetItemText(nRow, 6, strPM);
				pMainFrame->m_GridRHS.SetItemText(nRow, 7, strCmd);
				


		
			strRow.ReleaseBuffer();
			strFact.ReleaseBuffer();
			strPM.ReleaseBuffer();
			strCmd.ReleaseBuffer();
			
			}
		
		}//end if

			
		
	}//end for
 	
	
	/*	
		//Print map container Alpha Memory
		nRow = 1;
		CMainFrame::g_mCond_AM::iterator itAM;
		for( itAM = pMainFrame->gmCond_AM.begin(); itAM!= pMainFrame->gmCond_AM.end(); ++itAM)
		{
			//AfxMessageBox(_T("Hola pueblo...."));
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, itAM->first*100/gridMaxRows);
		
			if( itAM->first >= minCond && itAM->first <= maxCond)
			{
				strAM = _T("");
				strAM = strA + _itot( itAM->second, buffer, 10 );
				nRow++;
			

				if( nRow <= gridMaxRows + 1)
				{
					wsprintf(buffer, strAM);
					pMainFrame->m_GridRHS.SetItemText(nRow, 8, strAM);		
				}

				strAM.ReleaseBuffer();
				
			}
			
		}
	
	*/	
		pMainFrame->m_GridRHS.AutoSize();
		StopTimer(T, _T("RHS process elapsed seconds... "));
			
		
		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		pMainFrame->m_GridRHS.ShowWindow(SW_SHOW);
		str.Format(_T("RHS status: %d elements"), gridMaxRows);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
			
}


void CAIPITabView::FillRangeGridWM() 
{
	
	CAipi_WM  wmo;
	TCHAR buffer[24];
	
	CString strAM = _T("");
	CString strA = _T("A");
	CString str;
	int nRow = 1;
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridWM.ShowWindow(SW_HIDE);
	pMainFrame->m_GridWM.DeleteAllItems();
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading working memory(WM) data to Grid Control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	
	int gridMaxCols = 7;  
	int gridMaxRows = wmo.sizeWM();
	/*
	CString st;
	st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	AfxMessageBox(st);
	*/		
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Working memory(WM) status: Empty"));
		InitGridWM(10, gridMaxCols);
		pMainFrame->m_GridWM.ShowWindow(SW_SHOW);
		return;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridWM.SetRowCount(2);
			pMainFrame->m_GridWM.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridWM.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridWM.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

	
		//Fill Column Headers
	pMainFrame->m_GridWM.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridWM.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridWM.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridWM.SetItemText(0, 3, _T("C3"));		
	pMainFrame->m_GridWM.SetItemText(0, 4, _T("C4"));	
	pMainFrame->m_GridWM.SetItemText(0, 5, _T("C5"));
	pMainFrame->m_GridWM.SetItemText(0, 6, _T("C6"));
	
	pMainFrame->m_GridWM.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridWM.SetItemText(1, 1, _T("WM"));	
	pMainFrame->m_GridWM.SetItemText(1, 2, _T("Identifier"));		
	pMainFrame->m_GridWM.SetItemText(1, 3, _T("Attribute"));		
	pMainFrame->m_GridWM.SetItemText(1, 4, _T("Value"));	
	pMainFrame->m_GridWM.SetItemText(1, 5, _T("Type"));	
	pMainFrame->m_GridWM.SetItemText(1, 6, _T("AM"));
	
		
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	CMainFrame::g_mWM::iterator iter;
	//Print map container
	for( iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		
		CString strRow = _T("R");
		CString strWM =_T("WM");
		CString strType =_T("TYPE");

		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
		
		strWM +=  _itot( iter->first, buffer, 10 );
		wmo = (CAipi_WM)iter->second;
 	
		tstring i = wmo.getId();
		tstring a = wmo.getAttr();
		tstring v = wmo.getVal();
		int	type  = wmo.getType();
		
		strType +=  _itot( type, buffer, 10 );
		strRow +=  _itot( nRow, buffer, 10 );

		
		/*
		CString st;
		st.Format(_T("Number Rows...%d  " ), nRow);
		AfxMessageBox(st);
		*/	
		
		if( iter->first >= m_iMinRange_WM  &&  iter->first <= m_iMaxRange_WM )
		{
			//Fill Rows
			nRow++;
		
					
			TRY 
			{
				pMainFrame->m_GridWM.SetRowCount(nRow + 1 );
				pMainFrame->m_GridWM.SetColumnCount(gridMaxCols);
			}
			CATCH (CMemoryException, e)
			{
	    		e->ReportError();
    			return;
			}
			END_CATCH

			
			wsprintf(buffer, strRow);
			wsprintf(buffer, strWM);
			wsprintf(buffer, strType);

			wsprintf(buffer, i.data());
			wsprintf(buffer, a.data());
			wsprintf(buffer, v.data());
			
			pMainFrame->m_GridWM.SetItemText(nRow, 0, strRow);
			pMainFrame->m_GridWM.SetItemText(nRow, 1, strWM);
			pMainFrame->m_GridWM.SetItemText(nRow, 2, i.data());		
			pMainFrame->m_GridWM.SetItemText(nRow, 3, a.data());		
			pMainFrame->m_GridWM.SetItemText(nRow, 4, v.data());	
			pMainFrame->m_GridWM.SetItemText(nRow, 5, strType);	
			
			//AfxMessageBox(_T("Hola pueblo...."));
			
		
			strRow.ReleaseBuffer();
			strWM.ReleaseBuffer();
			strType.ReleaseBuffer();
		}
					
		
	}//end for
 	

		//Print map container Alpha Memory
		nRow = 1;
		CMainFrame::g_mmWM_AM::iterator itAM;
		for( itAM = pMainFrame->gmmWM_AM.begin(); itAM!= pMainFrame->gmmWM_AM.end(); ++itAM)
		{
			/*
			CString st;
			st.Format(_T("Number Rows...%d  " ), nRow);
			AfxMessageBox(st);
			st.Format(_T("Working Memoery...%d  " ), itAM->first);
			AfxMessageBox(st);
			*/	
		
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, itAM->first*100/gridMaxRows);
			

				strAM = _T("");
				strAM = strA + _itot( itAM->second, buffer, 10 );
				
			
				if( itAM->first >= m_iMinRange_WM  &&  itAM->first <= m_iMaxRange_WM )
				{
					nRow++;

					wsprintf(buffer, strAM);
					pMainFrame->m_GridWM.SetItemText(nRow, 6, strAM);
				
					strAM.ReleaseBuffer();
				}
					
		}

		
		pMainFrame->m_GridWM.AutoSize();
		StopTimer(T, _T("Working memory process elapsed seconds... "));
			
		
		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		pMainFrame->m_GridWM.ShowWindow(SW_SHOW);
		str.Format(_T("Working memory(WM) status: %d elements"), gridMaxRows);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
 			
}


void CAIPITabView::FillRangeGridCondLink() 
{
	
	CAipi_RETE_Links  lnko;
	TCHAR buffer[24];
	
	//CString strAM = _T("");
	//CString strA = _T("A");
	CString str;
	int nRow = 1;
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridCondLink.ShowWindow(SW_HIDE);
	pMainFrame->m_GridCondLink.DeleteAllItems();
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading conditons links data to Grid Control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	
	int gridMaxCols = 7;  
	int gridMaxRows =  lnko.sizeLinks();
	/*
	CString st;
	st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	AfxMessageBox(st);
	*/		
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Condition links status: Empty"));
		InitGridCondLink(10, gridMaxCols);
		pMainFrame->m_GridCondLink.ShowWindow(SW_SHOW);
		return;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridCondLink.SetRowCount(2);
			pMainFrame->m_GridCondLink.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridCondLink.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridCondLink.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

	
		//Fill Column Headers
	pMainFrame->m_GridCondLink.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridCondLink.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridCondLink.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridCondLink.SetItemText(0, 3, _T("C3"));		
	pMainFrame->m_GridCondLink.SetItemText(0, 4, _T("C4"));	
	pMainFrame->m_GridCondLink.SetItemText(0, 5, _T("C5"));
	pMainFrame->m_GridCondLink.SetItemText(0, 6, _T("C6"));
	
	pMainFrame->m_GridCondLink.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridCondLink.SetItemText(1, 1, _T("Condition 1"));	
	pMainFrame->m_GridCondLink.SetItemText(1, 2, _T("Condition 2"));		
	pMainFrame->m_GridCondLink.SetItemText(1, 3, _T("Field 1"));		
	pMainFrame->m_GridCondLink.SetItemText(1, 4, _T("Field 2"));	
	pMainFrame->m_GridCondLink.SetItemText(1, 5, _T("PM"));	
	pMainFrame->m_GridCondLink.SetItemText(1, 6, _T("Variable"));
	
		
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	CMainFrame::g_mmLink::iterator iter;
	//Print map container
	for( iter = pMainFrame->gmmLink.begin(); iter!= pMainFrame->gmmLink.end(); ++iter)
	{
		CString strCond1 = _T("LHS");
		CString strCond2 = _T("LHS");
		CString strField1 = _T("");
		CString strField2 = _T("");
		CString strPM = _T("PM");
		CString strRow = _T("R");
		
		
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
		
		
		lnko = (CAipi_RETE_Links)iter->second;
 	
		int c1 = iter->first;
		int c2 = lnko.getCond2();
		int f1 = lnko.getField1();
		int f2 = lnko.getField2();
		int pm = lnko.getPM();
		tstring var = lnko.getVar();
		
		strCond1 +=  _itot( c1, buffer, 10 );
		strCond2 +=  _itot( c2, buffer, 10 );
		strPM +=  _itot( pm, buffer, 10 );
		strRow +=  _itot( nRow, buffer, 10 );

		/*
		CString st;
		st.Format(_T("f1...%d  " ), f1);
		AfxMessageBox(st);
		st.Format(_T("f2...%d  " ), f2);
		AfxMessageBox(st);
		AfxMessageBox(strCond1);
		AfxMessageBox(strCond2);
		*/	
		switch( f1 )
		{
			case AIPI_ID:
				strField1 = _T("Identifier");
				break;
			case AIPI_AT:
				strField1 = _T("Attribute");
				break;
            case AIPI_VL:
				strField1 = _T("Value");
				break;
		}
		switch( f2 )
		{
			case AIPI_ID:
				strField2 = _T("Identifier");
				break;
			case AIPI_AT:
				strField2 = _T("Attribute");
				break;
            case AIPI_VL:
				strField2 = _T("Value");
				break;
		}

		/*
		CString st;
		st.Format(_T("Number Rows...%d  " ), nRow);
		AfxMessageBox(st);
		*/	
		
		if( iter->first >= m_iMinRange_CLink  &&  iter->first <= m_iMaxRange_CLink )
		{
			//Fill Rows
			nRow++;
		
					
			TRY 
			{
				pMainFrame->m_GridCondLink.SetRowCount(nRow + 1 );
				pMainFrame->m_GridCondLink.SetColumnCount(gridMaxCols);
			}
			CATCH (CMemoryException, e)
			{
	    		e->ReportError();
    			return;
			}
			END_CATCH

			
			wsprintf(buffer, strRow);
			wsprintf(buffer, strCond1);
			wsprintf(buffer, strCond2);
			wsprintf(buffer, strField1);
			wsprintf(buffer, strField2);
			wsprintf(buffer, strPM);
			
			
			pMainFrame->m_GridCondLink.SetItemText(nRow, 0, strRow);
			pMainFrame->m_GridCondLink.SetItemText(nRow, 1, strCond1);
			pMainFrame->m_GridCondLink.SetItemText(nRow, 2, strCond2);		
			pMainFrame->m_GridCondLink.SetItemText(nRow, 3, strField1);		
			pMainFrame->m_GridCondLink.SetItemText(nRow, 4, strField2);	
			pMainFrame->m_GridCondLink.SetItemText(nRow, 5, strPM);
			pMainFrame->m_GridCondLink.SetItemText(nRow, 6, var.c_str());
			
			//AfxMessageBox(_T("Hola pueblo...."));
			
			strCond1.ReleaseBuffer();
			strCond2.ReleaseBuffer();
			strField1.ReleaseBuffer();
			strField2.ReleaseBuffer();
			strRow.ReleaseBuffer();
			strPM.ReleaseBuffer();
			
		}
					
		
	}//end for
 	

		
		pMainFrame->m_GridCondLink.AutoSize();
		StopTimer(T, _T("Links process elapsed seconds... "));
			
		
		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		pMainFrame->m_GridCondLink.ShowWindow(SW_SHOW);
		str.Format(_T("Links status: %d elements"), gridMaxRows);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
 			
}



void CAIPITabView::FillRangeGridAgenda() 
{
	
	CAipi_RETE_BM  bmo;
	
	TCHAR buffer[BUFF_SIZE];
	CString str;
	int nRow =1;
	
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridAgenda.ShowWindow(SW_HIDE);
	pMainFrame->m_GridAgenda.DeleteAllItems();
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading Agenda data to grid control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	int gridMaxCols = 2;  
	int gridMaxRows = pMainFrame->g_vAgendaPM.size();
	
	
	/*
	CString st;
	st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	AfxMessageBox(st);
	*/	

			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Agenda tokens(TK) status: Empty"));
		InitGridAgenda(10, gridMaxCols);
		pMainFrame->m_GridBM_TK.ShowWindow(SW_SHOW);
		return;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridBM.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridBM.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridAgenda.SetRowCount( 2 );
			pMainFrame->m_GridAgenda.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridAgenda.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridAgenda.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

	//Fill Column Headers
	pMainFrame->m_GridAgenda.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridAgenda.SetItemText(0, 1, _T("C1"));	
	
	pMainFrame->m_GridAgenda.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridAgenda.SetItemText(1, 1, _T("Production"));	
	
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	


	
	//Print agenda
	
	for( long i  = 0; i < pMainFrame->g_vAgendaPM.size(); ++i)
	{
		
		CString strRow = _T("R");
		CString strPM =_T("PM");
		


		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, i*100/gridMaxRows);
		
		long pm = pMainFrame->g_vAgendaPM.at(i);	
		
		strRow		+=  _itot( nRow, buffer, 10 );
		strPM		+=  _itot( pm, buffer, 10 );
		strPM		+=  _itot( pm, buffer, 10 );
		
				
		/*
		CString st;
		st.Format(_T("Number Rows...%d  " ), nRow);
		AfxMessageBox(st);
		*/			
		
		if(i >= m_iMinRange_Agenda  &&  i <= m_iMaxRange_Agenda )
		{
			nRow++;


			TRY 
			{
				pMainFrame->m_GridAgenda.SetRowCount(nRow + 1 );
				pMainFrame->m_GridAgenda.SetColumnCount(gridMaxCols);
			}
			CATCH (CMemoryException, e)
			{
	    		e->ReportError();
    			return;
			}
			END_CATCH
				
			
					
			wsprintf(buffer, strRow);
			wsprintf(buffer, strPM);
			
			pMainFrame->m_GridAgenda.SetItemText(nRow, 0, strRow);
			pMainFrame->m_GridAgenda.SetItemText(nRow, 1, strPM);
					
		strRow.ReleaseBuffer();
		strPM.ReleaseBuffer();
		
		
		}
		
	}//end for
 	
	
		

	
	pMainFrame->m_GridAgenda.AutoSize();
	StopTimer(T, _T("Agenda process elapsed seconds... "));
			
		
	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	pMainFrame->m_GridAgenda.ShowWindow(SW_SHOW);

	str.Format(_T("Agenda status: %d elements"), gridMaxRows);
	pMainFrame->m_wndOutputTabView.AddMsg1(str);
 		
 			
}



void CAIPITabView::FillRangeGridAM() 
{
	
	CAipi_RETE_AM  amo;
	TCHAR buffer[BUFF_SIZE];
	CString strCond = _T("");
	CString strC = _T("C");
	CString strComa = _T(", ");
	CString strWM =_T("");
	CString strW = _T("WM");
	
	CString str;
	int nRow =1;
	int prevAM = 0;

	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridAM.ShowWindow(SW_HIDE);
	pMainFrame->m_GridAM.DeleteAllItems();
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading alpha memory(AM) data to grid control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	int gridMaxCols = 4;  
	//AfxMessageBox(_T("Hola pueblo...."));
	int gridMaxRows = amo.lastAM();
	
	
	/*
	CString st;
	st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	AfxMessageBox(st);
	*/	

			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Alpha memory(AM) status: Empty"));
		InitGridAM(10, gridMaxCols);
		pMainFrame->m_GridAM.ShowWindow(SW_SHOW);
		return;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridAM.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridAM.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridAM.SetRowCount(2 );
			pMainFrame->m_GridAM.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridAM.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridAM.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

	//Fill Column Headers
	pMainFrame->m_GridAM.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridAM.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridAM.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridAM.SetItemText(0, 3, _T("C3"));		
	
	pMainFrame->m_GridAM.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridAM.SetItemText(1, 1, _T("AM"));	
	pMainFrame->m_GridAM.SetItemText(1, 2, _T("Conditions"));		
	pMainFrame->m_GridAM.SetItemText(1, 3, _T("WM"));		
	

	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	


	
	//Print map container with Conditions
	CMainFrame::g_mmAM_Cond::iterator iter;
	for( iter = pMainFrame->gmmAM_Cond.begin(); iter!= pMainFrame->gmmAM_Cond.end(); ++iter)
	{
		
		CString strRow = _T("R");
		CString strAM =_T("AM");
		
		
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
			
		if( iter->first != prevAM )
		{
			strCond = _T("");
			int nAM = amo.countAM_Cond(iter->first);
			strAM	+=  _itot( iter->first, buffer, 10 );
			strCond += strC	 + _itot( iter->second, buffer, 10 );
			strRow	+=  _itot( nRow, buffer, 10 );
			
			prevAM = iter->first;

			if( iter->first >= m_iMinRange_AM  &&  iter->first <= m_iMaxRange_AM )
			{
				nRow++;
				
				TRY 
				{
					pMainFrame->m_GridAM.SetRowCount(nRow + 1 );
					pMainFrame->m_GridAM.SetColumnCount(gridMaxCols);
				}
				CATCH (CMemoryException, e)
				{
	    			e->ReportError();
    				return;
				}
				END_CATCH
				
				
				wsprintf(buffer, strRow);
				wsprintf(buffer, strAM);
				pMainFrame->m_GridAM.SetItemText(nRow, 0, strRow);
				pMainFrame->m_GridAM.SetItemText(nRow, 1, strAM);
			
				if( nAM <= 1 )
				{
					wsprintf(buffer, strCond);
					pMainFrame->m_GridAM.SetItemText(nRow, 2, strCond);		
				}
				
			}
			
		}
		else
		{
			strCond +=	strComa + strC + _itot( iter->second, buffer, 10 );

			if( iter->first >= m_iMinRange_AM  &&  iter->first <= m_iMaxRange_AM )
			{
				wsprintf(buffer, strCond);
				pMainFrame->m_GridAM.SetItemText(nRow, 2, strCond);		
				
			}
			
		}
				
		strRow.ReleaseBuffer();
		strAM.ReleaseBuffer();
		strCond.ReleaseBuffer();
		
			
		
	}//end for
 	


	
	//Print map container with Working Memory Elements
	prevAM = 0;
	nRow = 1;
	for( iter = pMainFrame->gmmAM_WM.begin(); iter!= pMainFrame->gmmAM_WM.end(); ++iter)
	{
		
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
		
		if( iter->first != prevAM )
		{
			strWM = _T("");
			int nAM = amo.countAM_WM(iter->first);
			strWM += strW + _itot( iter->second, buffer, 10 );
			
			prevAM = iter->first;

			if( iter->first >= m_iMinRange_AM  &&  iter->first <= m_iMaxRange_AM )
			{
				nRow++;
				if( nAM <= 1 )
				{
					wsprintf(buffer, strWM);
					pMainFrame->m_GridAM.SetItemText(nRow, 3, strWM);		
				}
			
			}
		}
		else
		{
			strWM +=	strComa + strW + _itot( iter->second, buffer, 10 );
			
			if( iter->first >= m_iMinRange_AM  &&  iter->first <= m_iMaxRange_AM )
			{
				wsprintf(buffer, strWM);
				pMainFrame->m_GridAM.SetItemText(nRow, 3, strWM);		
			
			}
			
		}
		
		strWM.ReleaseBuffer();	

	}
	
	


	pMainFrame->m_GridAM.AutoSize();
	StopTimer(T, _T("Alpha Memory process elapsed seconds... "));
			
		
	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	pMainFrame->m_GridAM.ShowWindow(SW_SHOW);

	str.Format(_T("Alpha memory(AM) status: %d elements"), gridMaxRows);
	pMainFrame->m_wndOutputTabView.AddMsg1(str);
 		
 			
}





void CAIPITabView::FillRangeGridBM() 
{
	
	CAipi_RETE_BM  bmo;
	CAipi_RETE_TK  tko;

	TCHAR buffer[BUFF_SIZE];
	CString strComa = _T(", ");
	CString strWM =_T("");
	
	CString str;
	int nRow =1;
	int prevBM = 0;

	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridBM.ShowWindow(SW_HIDE);
	pMainFrame->m_GridBM.DeleteAllItems();
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading beta memory(BM) data to grid control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	int gridMaxCols = 3;  
	int gridMaxRows = bmo.lastBM();
	
	
	/*
	CString st;
	st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	AfxMessageBox(st);
	*/	

			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Beta memory(BM) status: Empty"));
		InitGridBM(10, gridMaxCols);
		pMainFrame->m_GridBM.ShowWindow(SW_SHOW);
		return;
	}
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridBM.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridBM.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridBM.SetRowCount( 2 );
			pMainFrame->m_GridBM.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridBM.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridBM.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

	//Fill Column Headers
	pMainFrame->m_GridBM.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridBM.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridBM.SetItemText(0, 2, _T("C2"));		
	//pMainFrame->m_GridBM.SetItemText(0, 3, _T("C3"));
	//pMainFrame->m_GridBM.SetItemText(0, 4, _T("C4"));
	//pMainFrame->m_GridBM.SetItemText(0, 5, _T("C5"));
	//pMainFrame->m_GridBM.SetItemText(0, 6, _T("C6"));
	//pMainFrame->m_GridBM.SetItemText(0, 7, _T("C7"));
	//pMainFrame->m_GridBM.SetItemText(0, 8, _T("C8"));

	pMainFrame->m_GridBM.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridBM.SetItemText(1, 1, _T("BM"));	
	pMainFrame->m_GridBM.SetItemText(1, 2, _T("Linked WMEs"));		
	//pMainFrame->m_GridBM.SetItemText(1, 3, _T("Parent Tk"));		
	//pMainFrame->m_GridBM.SetItemText(1, 4, _T("Child Tk"));
	//pMainFrame->m_GridBM.SetItemText(1, 5, _T("Id. Var"));	
	//pMainFrame->m_GridBM.SetItemText(1, 6, _T("Id. Data"));		
	//pMainFrame->m_GridBM.SetItemText(1, 7, _T("Val. Var"));		
	//pMainFrame->m_GridBM.SetItemText(1, 8, _T("Val. Data"));	

	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	


	
	//Print map container with Conditions
	CMainFrame::g_mmBM::iterator iter;
	for( iter = pMainFrame->gmmBM.begin(); iter!= pMainFrame->gmmBM.end(); ++iter)
	{
		
		CString strRow = _T("R");
		CString strBM =_T("BM");
		/*
		CString st;
		st.Format(_T("Number Rows...%d  " ), nRow);
		AfxMessageBox(st);
		*/	
		
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
		bmo = (CAipi_RETE_BM)iter->second;	
		
		if( iter->first != prevBM )
		{
			strWM = _T("");
			int nBM = bmo.countBM(iter->first);
			strBM	+=  _itot( iter->first, buffer, 10 );
			int chld_tk = bmo.getChildTK();
			tstring  sLink =  tko.linkWMEs(chld_tk);	
			strWM += sLink.data();
			strRow	+=  _itot( nRow, buffer, 10 );
			
			prevBM = iter->first;
		
			if(iter->first >= m_iMinRange_BM  &&  iter->first <= m_iMaxRange_BM  )
			{
				nRow++;

				TRY 
				{
					pMainFrame->m_GridBM.SetRowCount(nRow + 1 );
					pMainFrame->m_GridBM.SetColumnCount(gridMaxCols);
				}
				CATCH (CMemoryException, e)
				{
	    			e->ReportError();
    				return;
				}
				END_CATCH
				
				
				wsprintf(buffer, strRow);
				wsprintf(buffer, strBM);

				pMainFrame->m_GridBM.SetItemText(nRow, 0, strRow);
				pMainFrame->m_GridBM.SetItemText(nRow, 1, strBM);
						
				if( nBM <= 1 )
				{
					wsprintf(buffer, strWM);
					pMainFrame->m_GridBM.SetItemText(nRow, 2, strWM);		
				}
				
			}
			
		}
		else
		{
			int chld_tk = bmo.getChildTK();
			tstring  link_wme	=  tko.linkWMEs(chld_tk);	
			strWM += strComa + link_wme.data();
			
			if( iter->first >= m_iMinRange_BM  &&  iter->first <= m_iMaxRange_BM  )
			{
				wsprintf(buffer, strWM);
				pMainFrame->m_GridBM.SetItemText(nRow, 2, strWM);
							
			}
			
		}
				
		strRow.ReleaseBuffer();
		strBM.ReleaseBuffer();
		strWM.ReleaseBuffer();
		
			
		
	}//end for
 	


	
	pMainFrame->m_GridBM.AutoSize();
	StopTimer(T, _T("Beta Memory process elapsed seconds... "));
			
		
	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	pMainFrame->m_GridBM.ShowWindow(SW_SHOW);

	str.Format(_T("Beta memory(BM) status: %d elements"), gridMaxRows);
	pMainFrame->m_wndOutputTabView.AddMsg1(str);
 		
 			
}




void CAIPITabView::FillRangeGridBM_TK() 
{
	
	CAipi_RETE_BM  bmo;
	
	TCHAR buffer[BUFF_SIZE];
	CString str;
	int nRow =1;
	
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridBM_TK.ShowWindow(SW_HIDE);
	pMainFrame->m_GridBM_TK.DeleteAllItems();
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading beta memory(BM) data to grid control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	int gridMaxCols = 9;  
	int gridMaxRows = bmo.sizeBM();
	
	
	/*
	CString st;
	st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	AfxMessageBox(st);
	*/	

			
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Beta memory(BM) tokens(TK) status: Empty"));
		InitGridBM_TK(10, gridMaxCols);
		pMainFrame->m_GridBM_TK.ShowWindow(SW_SHOW);
		return;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridBM.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridBM.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridBM_TK.SetRowCount( 2 );
			pMainFrame->m_GridBM_TK.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridBM_TK.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridBM_TK.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

	//Fill Column Headers
	pMainFrame->m_GridBM_TK.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridBM_TK.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridBM_TK.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridBM_TK.SetItemText(0, 3, _T("C3"));
	pMainFrame->m_GridBM_TK.SetItemText(0, 4, _T("C4"));
	pMainFrame->m_GridBM_TK.SetItemText(0, 5, _T("C5"));
	pMainFrame->m_GridBM_TK.SetItemText(0, 6, _T("C6"));
	pMainFrame->m_GridBM_TK.SetItemText(0, 7, _T("C7"));
	pMainFrame->m_GridBM_TK.SetItemText(0, 8, _T("C8"));

	pMainFrame->m_GridBM_TK.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridBM_TK.SetItemText(1, 1, _T("BM"));	
	pMainFrame->m_GridBM_TK.SetItemText(1, 2, _T("WM"));		
	pMainFrame->m_GridBM_TK.SetItemText(1, 3, _T("Parent Tk"));		
	pMainFrame->m_GridBM_TK.SetItemText(1, 4, _T("Child Tk"));
	pMainFrame->m_GridBM_TK.SetItemText(1, 5, _T("Id. Var"));	
	pMainFrame->m_GridBM_TK.SetItemText(1, 6, _T("Id. Data"));		
	pMainFrame->m_GridBM_TK.SetItemText(1, 7, _T("Val. Var"));		
	pMainFrame->m_GridBM_TK.SetItemText(1, 8, _T("Val. Data"));	

	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	


	
	//Print map container with Conditions
	CMainFrame::g_mmBM::iterator iter;
	for( iter = pMainFrame->gmmBM.begin(); iter!= pMainFrame->gmmBM.end(); ++iter)
	{
		
		CString strRow = _T("R");
		CString strBM =_T("BM");
		CString strWM = _T("WM");
		CString strTKP = _T("TK");
		CString strTKC = _T("TK");
		


		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
		
		bmo = (CAipi_RETE_BM)iter->second;	
		
		strRow		+=  _itot( nRow, buffer, 10 );
		strBM		+=  _itot( iter->first, buffer, 10 );
		
		int		wm		= bmo.getWM();
		int		pnt_tk  = bmo.getParentTK();
		int		chld_tk = bmo.getChildTK();
		tstring var1	= bmo.getVar1();
		tstring data1	= bmo.getData1();
		tstring var2	= bmo.getVar2();
		tstring data2	= bmo.getData2();


		strWM		+=  _itot( wm, buffer, 10 );
		strTKC		+=  _itot( chld_tk, buffer, 10 );
		if( pnt_tk == DNode )
			strTKP = _T("DNode");
		else
			strTKP		+=  _itot( pnt_tk, buffer, 10 );
		
				
		/*
		CString st;
		st.Format(_T("Number Rows...%d  " ), nRow);
		AfxMessageBox(st);
		*/			
		
		if(iter->first >= m_iMinRange_BM_TK  &&  iter->first <= m_iMaxRange_BM_TK )
		{
			nRow++;


			TRY 
			{
				pMainFrame->m_GridBM_TK.SetRowCount(nRow + 1 );
				pMainFrame->m_GridBM_TK.SetColumnCount(gridMaxCols);
			}
			CATCH (CMemoryException, e)
			{
	    		e->ReportError();
    			return;
			}
			END_CATCH
				
			
					
			wsprintf(buffer, strRow);
			wsprintf(buffer, strBM);
			wsprintf(buffer, strWM);
			wsprintf(buffer, strTKP);
			wsprintf(buffer, strTKC);

			wsprintf(buffer, var1.data());
			wsprintf(buffer, data1.data());
			wsprintf(buffer, var2.data());
			wsprintf(buffer, data2.data());

			pMainFrame->m_GridBM_TK.SetItemText(nRow, 0, strRow);
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 1, strBM);
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 2, strWM);
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 3, strTKP);
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 4, strTKC);
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 5, var1.data());
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 6, data1.data());
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 7, var2.data());
			pMainFrame->m_GridBM_TK.SetItemText(nRow, 8, data2.data());
						
					
		strRow.ReleaseBuffer();
		strBM.ReleaseBuffer();
		strWM.ReleaseBuffer();
		strTKP.ReleaseBuffer();
		strTKC.ReleaseBuffer();

		
		}
		
	}//end for
 	
	
		

	
	pMainFrame->m_GridBM_TK.AutoSize();
	StopTimer(T, _T("Beta Memory Tokens process elapsed seconds... "));
			
		
	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	pMainFrame->m_GridBM_TK.ShowWindow(SW_SHOW);

	str.Format(_T("Beta memory(BM) tokens(TK) status: %d elements"), gridMaxRows);
	pMainFrame->m_wndOutputTabView.AddMsg1(str);
 		
 			
}




void CAIPITabView::FillRangeGridRETE() 
{
	
	CAipi_RETE_Node  no;
	CAipi_RETE_JNode jno;
	
	TCHAR buffer[24];
	
	CString str;
	CString strType = _T("");
	int nRow = 1;
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
			
	pMainFrame->m_GridRETE.ShowWindow(SW_HIDE);
	pMainFrame->m_GridRETE.DeleteAllItems();
				
	CPerfTimer T;
	T.Start();
			
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading Rete net information to Grid Control..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);

	
	int gridMaxCols = 7;  
	int gridMaxRows = no.sizeNode();
	/*
	CString st;
	st.Format(_T("Rows Size...%d  " ), gridMaxRows);
	AfxMessageBox(st);
	*/		
	if( gridMaxRows == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("RETE nodes status: Empty"));
		InitGridRETE(10, gridMaxCols);
		pMainFrame->m_GridRETE.ShowWindow(SW_SHOW);
		return;
	}
	
	/*
	CPageInsertDlg InsertPage;
	InsertPage.m_nMaxCols = gridMaxCols;
	InsertPage.m_nMaxRows = gridMaxRows+1;
	InsertPage.m_nMaxFixCols = pMainFrame->m_GridRETE.GetFixedColumnCount();
	InsertPage.m_nMaxFixRows = pMainFrame->m_GridRETE.GetFixedRowCount();
	//InsertPage.UpdateData(false);
	*/
		
		TRY 
		{
		    pMainFrame->m_GridRETE.SetRowCount(2);
			pMainFrame->m_GridRETE.SetColumnCount(gridMaxCols);
		    pMainFrame->m_GridRETE.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridRETE.SetFixedColumnCount(m_nFixCols);
	
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

	
		//Fill Column Headers
	pMainFrame->m_GridRETE.SetItemText(0, 0, _T("C0"));
	pMainFrame->m_GridRETE.SetItemText(0, 1, _T("C1"));	
	pMainFrame->m_GridRETE.SetItemText(0, 2, _T("C2"));		
	pMainFrame->m_GridRETE.SetItemText(0, 3, _T("C3"));		
	pMainFrame->m_GridRETE.SetItemText(0, 4, _T("C4"));	
	pMainFrame->m_GridRETE.SetItemText(0, 5, _T("C5"));
	pMainFrame->m_GridRETE.SetItemText(0, 6, _T("C6"));
	
	pMainFrame->m_GridRETE.SetItemText(1, 0, _T("R0"));
	pMainFrame->m_GridRETE.SetItemText(1, 1, _T("Node"));	
	pMainFrame->m_GridRETE.SetItemText(1, 2, _T("Type"));		
	pMainFrame->m_GridRETE.SetItemText(1, 3, _T("Parent BM"));		
	pMainFrame->m_GridRETE.SetItemText(1, 4, _T("Child BM"));	
	pMainFrame->m_GridRETE.SetItemText(1, 5, _T("AM"));	
	pMainFrame->m_GridRETE.SetItemText(1, 6, _T("Linked Variable"));
	
		
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);		
	CMainFrame::g_mNode::iterator iter;
	//Print map container
	for( iter = pMainFrame->gmNode.begin(); iter!= pMainFrame->gmNode.end(); ++iter)
	{
		
		CString strRow = _T("R");
		CString strNode =_T("N");
		CString strBM1 =_T("BM");
		CString strBM2 =_T("BM");
		CString strAM = _T("AM");
	

		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, iter->first*100/gridMaxRows);
		
		strNode +=  _itot( iter->first, buffer, 10 );
		no = (CAipi_RETE_Node)iter->second;
 	
		int type	= no.getType();
		int bm1		= no.getParent();
		int bm2		= no.getChild();
		int am		= no.getAM();
		
		switch(type)
		{
		case DNode:
			strType = _T("Dummy Node");
			break;
		case JNode:
			strType = _T("Join Node");
			break;
		case NNode:
			strType = _T("Negated Node");
			break;
		case PNode:
			strType = _T("Production Node");
			break;
		case NCCNode:
			strType = _T("Negated Conjunctive Condition Node");
			break;
		case FPNode:
			strType = _T("Fired Production Node");
			break;
		case NumNode :
			strType = _T("Numeric Node");
			break;

		}
		
		strBM1	+=  _itot( bm1, buffer, 10 );
		strBM2	+=  _itot( bm2, buffer, 10 );
		strAM	+=  _itot( am, buffer, 10 );
		strRow	+=  _itot( nRow, buffer, 10 );
		
		
		/*
		CString st;
		st.Format(_T("Number Rows...%d  " ), nRow);
		AfxMessageBox(st);
		*/	
		
		if(  iter->first >= m_iMinRange_RETE  &&  iter->first <= m_iMaxRange_RETE )
		{
			
			//Fill Rows
			nRow++;
			
			TRY 
			{
				pMainFrame->m_GridRETE.SetRowCount(nRow + 1 );
				pMainFrame->m_GridRETE.SetColumnCount(gridMaxCols);
			}
			CATCH (CMemoryException, e)
			{
	    		e->ReportError();
    			return;
			}
			END_CATCH


			wsprintf(buffer, strRow);
			wsprintf(buffer, strNode);
			wsprintf(buffer, strType);
			wsprintf(buffer, strBM1);
			wsprintf(buffer, strBM2);
			wsprintf(buffer, strAM);
			
			pMainFrame->m_GridRETE.SetItemText(nRow, 0, strRow);
			pMainFrame->m_GridRETE.SetItemText(nRow, 1, strNode);
			pMainFrame->m_GridRETE.SetItemText(nRow, 2, strType);		
			pMainFrame->m_GridRETE.SetItemText(nRow, 3, strBM1);		
			pMainFrame->m_GridRETE.SetItemText(nRow, 4, strBM2);	
			pMainFrame->m_GridRETE.SetItemText(nRow, 5, strAM);	
			
			//AfxMessageBox(_T("Hola pueblo...."));
		}	
		
		strRow.ReleaseBuffer();
		strNode.ReleaseBuffer();
		strType.ReleaseBuffer();
		strBM1.ReleaseBuffer();
		strBM2.ReleaseBuffer();
		strAM.ReleaseBuffer();
					
		
	}//end for
 	

		//Print map container Alpha Memory
		nRow = 1;
		CMainFrame::g_mJNode::iterator itJN;
		for( itJN = pMainFrame->gmJNode.begin(); itJN!= pMainFrame->gmJNode.end(); ++itJN)
		{
			/*
			CString st;
			st.Format(_T("Number Rows...%d  " ), nRow);
			AfxMessageBox(st);
			st.Format(_T("Working Memoery...%d  " ), itJN->first);
			AfxMessageBox(st);
			*/	
		
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, itJN->first*100/gridMaxRows);
			jno = (CAipi_RETE_JNode)itJN->second;
			
			CString strVar = jno.getVar().data();
			
			
				if(itJN->first >= m_iMinRange_RETE  &&  itJN->first <= m_iMaxRange_RETE )
				{
					nRow++;

					wsprintf(buffer, strVar);
					pMainFrame->m_GridRETE.SetItemText(nRow, 6, strVar);
				
				}
			
				strVar.ReleaseBuffer();
					
		}

		
		
		pMainFrame->m_GridRETE.AutoSize();
		StopTimer(T, _T("RETE Nodes process elapsed seconds... "));
			
		
		pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
		pMainFrame->m_GridRETE.ShowWindow(SW_SHOW);
		str.Format(_T("Rete nodes status: %d elements"), gridMaxRows);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);

 			
}




//////////////////////////////////////////////////////////////////////////////////////////////
/// Page Functions ////
///////////////////////////////////////////////////////////////////////////////////////////////

void CAIPITabView::UpdatePageOptionDlg()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	if (!::IsWindow(pOptionsPage->m_hWnd)) 
	return;
	
	
	if( pMainFrame->m_bSort )
	{
		pOptionsPage->m_chkSort.SetCheck(true);
	}
	else
	{
		pOptionsPage->m_chkSort.SetCheck(false);
	}
	
	if( pMainFrame->m_bToolTips)
	{
		pOptionsPage->m_chkToolTips.SetCheck(true);
	}
	else
	{
		pOptionsPage->m_chkToolTips.SetCheck(false);
	}

	if( pMainFrame->m_bCellSelect)
	{
		pOptionsPage->m_chkCellSelect.SetCheck(true);
		
	}
	else
	{
		pOptionsPage->m_chkCellSelect.SetCheck(false);
		
	}
	
}


void CAIPITabView::UpdatePageFormatDlg()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	if (!::IsWindow(pFormatPage->m_hWnd)) 
	return;
	
	if( pMainFrame->m_bVertical )
	{
		pFormatPage->m_chkVertical.SetCheck(true);
	}
	else
	{
		pFormatPage->m_chkVertical.SetCheck(false);
	}
	
	if( pMainFrame->m_bHorizontal)
	{
		pFormatPage->m_chkHorizontal.SetCheck(true);
	}
	else
	{
		pFormatPage->m_chkHorizontal.SetCheck(false);
	}
	
	if( pMainFrame->m_bItalic)
	{
		pFormatPage->m_radioItalic.SetCheck(true);
	}
	else
	{
		pFormatPage->m_radioItalic.SetCheck(false);
	}
	
	if( pMainFrame->m_bBold)
	{
		pFormatPage->m_radioBold.SetCheck(true);
	}
	else
	{
		pFormatPage->m_radioBold.SetCheck(false);
	}
	
	if( pMainFrame->m_bNormal)
	{
		pFormatPage->m_radioNormal.SetCheck(true);
	}
	else
	{
		pFormatPage->m_radioNormal.SetCheck(false);
	}		
	
	if( pMainFrame->m_bVerticalHeader)
	{
		pFormatPage->m_radioVerticalHeader.SetCheck(true);
	}
	else
	{
		pFormatPage->m_radioVerticalHeader.SetCheck(false);
	}

	
}



void CAIPITabView::UpdatePageCellSizeDlg()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			
	if (!::IsWindow(pCellSizePage->m_hWnd)) 
	return;
	
	
	if( pMainFrame->m_bColumnResize)
	{
		pCellSizePage->m_chkColumnResize.SetCheck(true);
	}
	else
	{
		pCellSizePage->m_chkColumnResize.SetCheck(false);
	}
	
	if( pMainFrame->m_bRowResize)
	{
		pCellSizePage->m_chkRowResize.SetCheck(true);
	}
	else
	{
		pCellSizePage->m_chkRowResize.SetCheck(false);
	}
	
	if( pMainFrame->m_bFitGrid)
	{
		pCellSizePage->m_chkFitGrid.SetCheck(true);
	}
	else
	{
		pCellSizePage->m_chkFitGrid.SetCheck(false);
	}
	
	

}



void CAIPITabView::UpdatePageEditDlg()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	if (!::IsWindow(pEditPage->m_hWnd)) 
	return;
	

	if( pMainFrame->m_bEditable )
	{
		pEditPage->m_radioRead.SetCheck(false);
		pEditPage->m_radioWrite.SetCheck(true);
	}
	else
	{
		pEditPage->m_radioRead.SetCheck(true);
		pEditPage->m_radioWrite.SetCheck(false);	
	}
}	



void CAIPITabView::UpdateMenuUI()
{
	UpdatePageCellSizeDlg();
	UpdatePageEditDlg();
	UpdatePageFormatDlg();
	UpdatePageOptionDlg();
}




void CAIPITabView::Trace(LPCTSTR szFmt, ...)
{    
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CString str;

	// Format the message text
    va_list argptr;
    va_start(argptr, szFmt);
    str.FormatV(szFmt, argptr);
    va_end(argptr);

	str.Replace(_T("\n"), _T("\r\n"));

	

	CString strWndText;
	pMainFrame->m_wndOutputTabView.m_editCtrl1.GetWindowText(strWndText);
	strWndText += str;
	pMainFrame->m_wndOutputTabView.m_editCtrl1.SetWindowText(strWndText);
	
	//	pMainFrame->m_wndOutputTabView.m_editCtrl1.SetSel(str.GetLength()-1, str.GetLength()-2, FALSE);
	pMainFrame->m_wndOutputTabView.m_editCtrl1.LineScroll(-pMainFrame->m_wndOutputTabView.m_editCtrl1.GetLineCount());
	pMainFrame->m_wndOutputTabView.m_editCtrl1.LineScroll(pMainFrame->m_wndOutputTabView.m_editCtrl1.GetLineCount()-4);
}


void CAIPITabView::ClearTrace() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndOutputTabView.m_editCtrl1.SetWindowText(_T(""));
	
}



// NM_RCLICK
void CAIPITabView::OnGridRClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Right button click on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}

// GVN_BEGINLABELEDIT
void CAIPITabView::OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Start Edit on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	*pResult = (m_bRejectEditAttempts)? -1 : 0;
}

// GVN_ENDLABELEDIT
void CAIPITabView::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("End Edit on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	*pResult = (m_bRejectEditChanges)? -1 : 0;
}

// GVN_SELCHANGING
void CAIPITabView::OnGridStartSelChange(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    /*
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Start Selection Change on row %d, col %d (%d Selected)\n"), 
		pItem->iRow, pItem->iColumn, pMainFrame->m_GridInduction.GetSelectedCount());
		*/
}

// GVN_SELCHANGED
void CAIPITabView::OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    /*
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("End Selection Change on row %d, col %d (%d Selected)\n"), 
		pItem->iRow, pItem->iColumn, pMainFrame->m_GridInduction.GetSelectedCount());
		*/
}

// GVN_BEGINDRAG
void CAIPITabView::OnGridBeginDrag(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Begin Drag row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}

void CAIPITabView::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}

void CAIPITabView::OnGridClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    //Trace(_T("Clicked on row %d, col %d\n"), pItem->iRow-1, pItem->iColumn);

	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int currentGrid = pMainFrame->SelectGrid();
	
	switch(currentGrid)
	{
	case GRID_LHS:
		ClickGridLHS(pItem->iRow, pItem->iColumn);
		break;
	case GRID_RHS:
		ClickGridRHS(pItem->iRow, pItem->iColumn);
		break;
	case GRID_WM:
		ClickGridWM(pItem->iRow, pItem->iColumn);
		break;
	case GRID_COND_LINK:
		ClickGridCondLink(pItem->iRow, pItem->iColumn);
		break;
	case GRID_AGENDA:
		ClickGridAgenda(pItem->iRow, pItem->iColumn);
		break;
	case GRID_AM:
		ClickGridAM(pItem->iRow, pItem->iColumn);
		break;	
	case GRID_BM:
		ClickGridBM(pItem->iRow, pItem->iColumn);
		break;	
	case GRID_BM_TK:
		ClickGridBM_TK(pItem->iRow, pItem->iColumn);
		break;
	case GRID_RETE:
		ClickGridRETE(pItem->iRow, pItem->iColumn);
		break;
	case GRID_INDUCTION:
		//str = pMainFrame->m_GridInduction.GetItemText(pItem->iRow, pItem->iColumn);
		//Trace(str);
		break;	

	}//end switch
	
	

}




void CAIPITabView::ClickGridLHS(int row,int col)
{
	CAipi_PM pmo;
	if( pmo.sizePM() == 0 )
		return;
	
	
	CString str =_T("");
	TCHAR buff[16];
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	COLORREF clr1 = RGB(255, 255, 220);
	COLORREF clr2 = RGB(255, 204, 102);
	COLORREF clr3 = RGB(255, 255, 100);

	bool bEditable = pMainFrame->FindGridVarState(_T("EditableLHS"));
	if ( bEditable == true)
		return;
	
	if( col == 1 )
	{
		int nRows = pMainFrame->m_GridLHS.GetRowCount();	
		
		
		for(int i=0; i<m_vTempRepCond.size(); ++i)
		{
			int tc = m_vTempRepCond.at(i);

			if( tc + 1 <= nRows )
			{
				pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 1, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 2, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 3, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 4, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 5, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 6, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 7, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 8, clr1);
			}
		}
		
		pMainFrame->m_GridLHS.Invalidate();

		CString strCond = pMainFrame->m_GridLHS.GetItemText(row, col);
		
		str = _T("*** Condition: ") + strCond + _T(" ***\n");
		Trace(str);
			
		strCond.Delete(0,1);
		int iCond = _ttoi(strCond);
			
		CMainFrame::g_mmRepCond::iterator iterCond;
		pair <CMainFrame::g_mmRepCond::iterator, CMainFrame::g_mmRepCond::iterator>  pCond;
		pCond = pMainFrame->gmmRepCond.equal_range(iCond);
	
		CAipi_RepCond co;
		int nRepCond = co.countRepCond(iCond);

		if(  nRepCond== 0 )
		{
			Trace(_T("0 Repeated condition(s) found.\n"));
			return;
		}
		else
		{
			CString strRepCond = _T("");
			strRepCond.Format(_T("%d Repeated condition(s) found.\n"), nRepCond);
			Trace(strRepCond);
			m_vTempRepCond.clear();
		}

		for(iterCond = pCond.first; iterCond != pCond.second; ++iterCond)
		{	
			co = (CAipi_RepCond)iterCond->second;
 			CString strC2 =_T("C");
			CString strPM2 = _T("P");
			int c2 = co.getRepCond();
			int pm2 = co.getPM2();
				
			m_vTempRepCond.push_back(c2);

			if( c2 + 1 <= nRows )
			{
				
				pMainFrame->m_GridLHS.SetItemBkColour(c2+1, 1, clr2);
				pMainFrame->m_GridLHS.SetItemBkColour(c2+1, 2, clr2);
				pMainFrame->m_GridLHS.SetItemBkColour(c2+1, 3, clr2);
				pMainFrame->m_GridLHS.SetItemBkColour(c2+1, 4, clr2);
				pMainFrame->m_GridLHS.SetItemBkColour(c2+1, 5, clr2);
				pMainFrame->m_GridLHS.SetItemBkColour(c2+1, 6, clr2);
				pMainFrame->m_GridLHS.SetItemBkColour(c2+1, 7, clr2);
				pMainFrame->m_GridLHS.SetItemBkColour(c2+1, 8, clr2);
				
				strC2 += _itot(c2 ,  buff, 10 );
				strPM2 += _itot( pm2 ,  buff, 10 );
				str = _T("Repeated condition:...") + strC2 + _T(",   Production:...") + strPM2 + _T("\n");
				Trace(str);
			}
		}
		
	}
	else
	{
		for(int i=0; i<m_vTempRepCond.size(); ++i)
		{
			int tc = m_vTempRepCond.at(i);
			pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 1, clr1);
			pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 2, clr1);
			pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 3, clr1);
			pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 4, clr1);
			pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 5, clr1);
			pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 6, clr1);
			pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 7, clr1);
			pMainFrame->m_GridLHS.SetItemBkColour(tc+1, 8, clr1);
		}
	
	}
	
	pMainFrame->m_GridLHS.Invalidate();
	


	if( col == 6)
	{
		int iniCond =0;
		int endCond = 0;
		
		
		if( !m_vTempPM.empty())
		{
			iniCond = m_vTempPM.at(0);
			endCond = m_vTempPM.at(1);

			for( int i = iniCond; i <= endCond; ++i)
			{
				pMainFrame->m_GridLHS.SetItemBkColour(i+1, 1, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(i+1, 2, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(i+1, 3, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(i+1, 4, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(i+1, 5, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(i+1, 6, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(i+1, 7, clr1);
				pMainFrame->m_GridLHS.SetItemBkColour(i+1, 8, clr1);
			}
			pMainFrame->m_GridLHS.Invalidate();
			m_vTempPM.clear();
		}

		CString strPM = pMainFrame->m_GridLHS.GetItemText(row, col);
		
		str = _T("*** Production: ") + strPM + _T(" ***\n");
		Trace(str);
			
		strPM.Delete(0,1);
		int iPM = _ttoi(strPM);
		
		CAipi_PM pmo;
		iniCond = pmo.PM_CondLowerBound(iPM);
		endCond = pmo.PM_CondUpperBound(iPM);
		
		m_vTempPM.push_back(iniCond);
		m_vTempPM.push_back(endCond);


		for( int i = iniCond; i<= endCond; ++i)
		{
			pMainFrame->m_GridLHS.SetItemBkColour(i+1, 1, clr3);
			pMainFrame->m_GridLHS.SetItemBkColour(i+1, 2, clr3);
			pMainFrame->m_GridLHS.SetItemBkColour(i+1, 3, clr3);
			pMainFrame->m_GridLHS.SetItemBkColour(i+1, 4, clr3);
			pMainFrame->m_GridLHS.SetItemBkColour(i+1, 5, clr3);
			pMainFrame->m_GridLHS.SetItemBkColour(i+1, 6, clr3);
			pMainFrame->m_GridLHS.SetItemBkColour(i+1, 7, clr3);
			pMainFrame->m_GridLHS.SetItemBkColour(i+1, 8, clr3);
		}
		pMainFrame->m_GridLHS.Invalidate();

	}
	

}


void CAIPITabView::ClickGridRHS(int row,int col)
{
	
}


void CAIPITabView::ClickGridCondLink(int row,int col)
{
	
}

void CAIPITabView::ClickGridAgenda(int row,int col)
{
	
}


void CAIPITabView::ClickGridRETE(int row, int col)
{
	CAipi_RETE_JNode jn;
	if( jn.sizeJNode() == 0 )
		return;

	CString str = _T("");
	TCHAR buff[16];
	CString strF1 = _T("");
	CString strF2 = _T("");

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	if( col == 1)
	{
			CString strNode = pMainFrame->m_GridRETE.GetItemText(row, col);
			str = _T("*** Node: ") + strNode + _T(" ***\n");
			Trace(str);
			
			strNode.Delete(0,1);
			int iNode = _ttoi(strNode);
			

			jn.findJNMembers(iNode);
			
			int f1		= jn.m_Field1;
			int f2		= jn.m_Field2;
			CString var = jn.m_Var.data();
			switch(f1)
			{
				case AIPI_ID:
					strF1 = _T("Identifier");
					break;
				case AIPI_AT:
					strF1 = _T("Attribute");
					break;
				case AIPI_VL:
					strF1 = _T("Value");
					break;
			}
			
			switch(f2)
			{
				case AIPI_ID:
					strF2 = _T("Identifier");
					break;
				case AIPI_AT:
					strF2 = _T("Attribute");
					break;
				case AIPI_VL:
					strF2 = _T("Value");
					break;
			}


			CMainFrame::g_mmNodeCond::iterator iterNode;
			pair <CMainFrame::g_mmNodeCond::iterator, CMainFrame::g_mmNodeCond::iterator>  pNode;
			pNode = pMainFrame->gmmNodeCond.equal_range(iNode);
	
			for(iterNode = pNode.first; iterNode != pNode.second; ++iterNode)
			{	
				CAipi_RETE_NodeCond no = (CAipi_RETE_NodeCond)iterNode->second;
 				CString strC1 =_T("C");
				CString strC2 =_T("C");
				CString strPM = _T("P");
				
				strC1 += _itot( no.getCond1(),  buff, 10 );
				strC2 += _itot( no.getCond2(),  buff, 10 );
				strPM += _itot( no.getPM(),  buff, 10 );
				str = var + _T(",   Parent Condition:...") + strC1 + _T(",   Field:...") + strF1 + _T(",   Child Condition:...") + strC2 + _T(",   Field:...") + strF2 + _T(",   Production:...") + strPM + _T("\n");
				Trace(str);
			}
		
	}

}

void CAIPITabView::ClickGridWM(int row, int col)
{
	
	CAipi_WM  wmo;
	if( wmo.sizeWM() == 0)
		return;
	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	COLORREF clr1 = RGB(255, 255, 220);
	COLORREF clr2 = RGB(255, 255, 100);
	
	int type = wmo.findWMType(row-1);
	
	CString sI	= _T("Int");
	CString sL	= _T("Long");
	CString sF	= _T("Float");
	CString sD	= _T("Double");
	CString sS	= _T("String");

	CString strElement = pMainFrame->m_GridWM.GetItemText(row, col);
	CString strWM = _itot( row-1, buffer, 10 );
	
	
	if( !m_vTempWM.empty() )
	{
		int lastRow = m_vTempWM.at(0);
		pMainFrame->m_GridWM.SetItemBkColour(lastRow, 1, clr1);
		m_vTempWM.clear();
	}
	
	
	
	pMainFrame->m_GridWM.SetItemBkColour(row, 1, clr2);
	pMainFrame->m_GridWM.Invalidate();
	m_vTempWM.push_back(row);
	


	CString str = _T("*** Working Memory: ") + strWM + _T(" ***\n");
	Trace(str);
	

	switch( type)
	{
		
	//Integer
		case I_S_I:
			switch(col)
			{
				case 2:
					Trace( strElement + _T("... Identifier type: ") +  sI + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sI + _T(".-\n"));
					break;
			}
			break;
		case I_S_L:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sI + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sL + _T(".-\n"));
					break;
			}
			break;
		case I_S_F:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sI + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sF + _T(".-\n"));
					break;
			}
			break;
		case I_S_D:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sI + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sD + _T(".-\n"));
					break;
			}
			break;
		case I_S_S:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sI + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));	
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sS + _T(".-\n"));
					break;
			}
			break;
	//Long

		case L_S_I:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sL + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));	
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sI + _T(".-\n"));
					break;
			}
			break;
		case L_S_L:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sL + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sL + _T(".-\n"));
					break;
			}
			break;
		case L_S_F:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sL + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sF + _T(".-\n"));
					break;
			}
			break;
		case L_S_D:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sL + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sD + _T(".-\n"));
					break;
			}
			break;
		case L_S_S:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sL + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sS + _T(".-\n"));
					break;
			}
			break;

	//Float

		case F_S_I:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sF + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sI + _T(".-\n"));
					break;
			}
			break;

		case F_S_L:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sF + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sL + _T(".-\n"));
					break;
			}
			break;
		case F_S_F:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sF + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sF + _T(".-\n"));
					break;
			}
			break;
		case F_S_D:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sF + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sD + _T(".-\n"));
					break;
			}
			break;
		case F_S_S:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sF + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sS + _T(".-\n"));
					break;
			}
			break;
			
	//Double

		case D_S_I:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sD + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sI + _T(".-\n"));
					break;
			}
			break;
		case D_S_L:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sD + _T(".-\n"));	
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sL + _T(".-\n"));
					break;
			}
			break;
		case D_S_F:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sD + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sF + _T(".-\n"));
					break;
			}
			break;
		case D_S_D:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sD + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sD + _T(".-\n"));
					break;
			}
			break;
		case D_S_S:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sD + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sD + _T(".-\n"));
					break;
			}
			break;

	//String

		case S_S_I:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sS + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sI + _T(".-\n"));
					break;
			}
			break;
		case S_S_L:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sS + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sL + _T(".-\n"));
					break;
			}
			break;
		case S_S_F:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sS + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sF + _T(".-\n"));
					break;
			}
			break;
		case S_S_D:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sS + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attributes type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sD + _T(".-\n"));
					break;
			}
			break;
		case S_S_S:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sS + _T(".-\n"));
					//AfxMessageBox(strElement);

					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sS + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sS + _T(".-\n"));
					break;
			}
			break;

	}

	
/*
	switch (type)
	{
		//Integer
		
		case I_I_I:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sI + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sI + _T(".-\n"));
					break;
			}
			break;
		case I_I_L:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sI + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sI + _T(".-\n"));
					break;
			}
			break;
		case I_I_F:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sI + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sF + _T(".-\n"));
					break;
			}
			break;
		case I_I_D:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sI + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sD + _T(".-\n"));
					break;
			}
			break;
		case I_I_S:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sI + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sS + _T(".-\n"));
					break;
			}
			break;

		//Long
		
		case L_I_I:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sL + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sI + _T(".-\n"));
					break;
			}
			break;
		case L_I_L:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sL + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sL + _T(".-\n"));
					break;
			}
			break;
		case L_I_F:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sL + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sF + _T(".-\n"));
					break;
			}
			break;
		case L_I_D:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sL + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sD + _T(".-\n"));
					break;
			}
			break;
		case L_I_S:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sL + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sS + _T(".-\n"));
					break;
			}
			break;


		//Float
		case F_I_I:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sF + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sI + _T(".-\n"));
					break;
			}
			break;
		case F_I_L:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sF + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sL + _T(".-\n"));
					break;
			}
			break;
		case F_I_F:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sF + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sF + _T(".-\n"));
					break;
			}
			break;
		case F_I_D:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sF + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sD + _T(".-\n"));
					break;
			}
			break;
		case F_I_S:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sF + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sS + _T(".-\n"));
					break;
			}
			break;


		//Double
		case D_I_I:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sD + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sI + _T(".-\n"));
					break;
			}
			break;
		case D_I_L:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sD + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sL + _T(".-\n"));
					break;
			}
			break;
		case D_I_F:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sD + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sF + _T(".-\n"));
					break;
			}
			break;
		case D_I_D:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sD + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sD + _T(".-\n"));
					break;
			}
			break;
		case D_I_S:
			switch(col)
			{
				case 2:
					Trace(strElement + _T("... Identifier type: ") + sD + _T(".-\n"));
					break;
				case 3:
					Trace(strElement + _T("... Attribute type: ") + sI + _T(".-\n"));
					break;
				case 4:
					Trace(strElement + _T("... Value type: ") + sS + _T(".-\n"));
					break;
			}
			break;


	}
	*/
	

}



void CAIPITabView::ClickGridAM(int row, int col)
{
	CAipi_RETE_AM	amo;
	if( amo.sizeAM_Cond() == 0 )
		return;

	if( col == 1 )
	{
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
		CAipi_LHS		lhso;
		CString			str		= _T("");
		tstring			strK	= _T("");

		CString strAM = pMainFrame->m_GridAM.GetItemText(row, col);
		str = _T("*** ") + strAM + _T(" ***\n");
		Trace(str);

		strAM.Delete(0,1);
		int iAM		= _ttoi(strAM);
		int iCond	= amo.findAM_Cond(iAM);
		
		int f =lhso.findLHSMembers(iCond);	
	
		if ( f == NOT_FOUND )
			return;
	
		int iRel		= lhso.m_Rel;
		int	iCateg		= lhso.m_Category;
		tstring	sId		= lhso.m_lhsId;
		tstring	sAttr	= lhso.m_lhsAttr;
		tstring	sVal	= lhso.m_lhsVal;
	
		str	= _T("Alpha memory constant test.... ");

		switch(iRel)
		{
			case EQ:
				switch(iCateg)
				{
				case ID_AT_K:
					strK = amo.findAM_EQ_I_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_AT_VL:
					amo.findAM_EQ_I_A_V(iAM);
					strK = amo.findAM_EQ_I_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_K:
					strK = amo.findAM_EQ_I_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_VL:
					strK = amo.findAM_EQ_I_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_K:
					strK = amo.findAM_EQ_K_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_VL:
					strK = amo.findAM_EQ_K_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_K:
					strK = amo.findAM_EQ_K_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_VL:
					strK = amo.findAM_EQ_K_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
			}
			break;
			case ET:
				switch(iCateg)
				{
				case ID_AT_K:
					strK = amo.findAM_ET_I_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_AT_VL:
					strK = amo.findAM_ET_I_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_K:
					strK = amo.findAM_ET_I_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_VL:
					strK = amo.findAM_ET_I_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_K:
					strK = amo.findAM_ET_K_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_VL:
					strK = amo.findAM_ET_K_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_K:
					strK = amo.findAM_ET_K_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_VL:
					strK = amo.findAM_ET_K_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				}
			break;
			case GE:
				switch(iCateg)
				{
				case ID_AT_K:
					strK = amo.findAM_GE_I_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_AT_VL:
					strK = amo.findAM_GE_I_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_K:
					strK = amo.findAM_GE_I_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_VL:
					strK = amo.findAM_GE_I_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_K:
					strK= amo.findAM_GE_K_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_VL:
					strK = amo.findAM_GE_K_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_K:
					strK = amo.findAM_GE_K_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_VL:
					strK = amo.findAM_GE_K_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				}
			break;
			case GT:
				switch(iCateg)
				{
				case ID_AT_K:
					strK = amo.findAM_GT_I_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_AT_VL:
					strK = amo.findAM_GT_I_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_K:
					strK = amo.findAM_GT_I_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_VL:
					strK = amo.findAM_GT_I_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_K:
					strK = amo.findAM_GT_K_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_VL:
					strK = amo.findAM_GT_K_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_K:
					strK = amo.findAM_GT_K_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_VL:
					strK = amo.findAM_GT_K_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				}
			break;	
			case LE:
				switch(iCateg)
				{
				case ID_AT_K:
					strK = amo.findAM_LE_I_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_AT_VL:
					strK= amo.findAM_LE_I_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_K:
					strK = amo.findAM_LE_I_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_VL:
					strK = amo.findAM_LE_I_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_K:
					strK= amo.findAM_LE_K_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_VL:
					strK = amo.findAM_LE_K_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_K:
					strK = amo.findAM_LE_K_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_VL:
					strK = amo.findAM_LE_K_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				}
			break;
			case LT:
				switch(iCateg)
				{
				case ID_AT_K:
					strK = amo.findAM_LT_I_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_AT_VL:
					strK = amo.findAM_LT_I_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_K:
					strK = amo.findAM_LT_I_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_VL:
					strK = amo.findAM_LT_I_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_K:
					strK = amo.findAM_LT_K_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_VL:
					strK = amo.findAM_LT_K_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_K:
					strK = amo.findAM_LT_K_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_VL:
					strK = amo.findAM_LT_K_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				}
			break;	
			case AS:
				switch(iCateg)
				{
				case ID_AT_K:
					strK = amo.findAM_AS_I_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_AT_VL:
					strK = amo.findAM_AS_I_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_K:
					strK = amo.findAM_AS_I_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case ID_K_VL:
					strK = amo.findAM_AS_I_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_K:
					strK = amo.findAM_AS_K_A_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_AT_VL:
					strK = amo.findAM_AS_K_A_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_K:
					strK = amo.findAM_AS_K_K_K(iAM);
					str += strK.data();
					Trace(str);
					break;
				case K_K_VL:
					strK = amo.findAM_AS_K_K_V(iAM);
					str += strK.data();
					Trace(str);
					break;
				}
			break;
	
		
		}//end switch
	
		Trace(_T("\n"));
	
	}//end if

}


void CAIPITabView::ClickGridBM(int row, int col)
{
	CAipi_RETE_BM  bmo;
	if( bmo.sizeBM() == 0 )
		return;

	CString str = _T("");
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	if( col == 1 )
	{
			CString strBM = pMainFrame->m_GridBM.GetItemText(row, col);
			str = _T("*** Beta Memory: ") + strBM + _T(" ***\n");
			Trace(str);
			
			strBM.Delete(0,1);
			int iBM = _ttoi(strBM);
			
			
			int nBM = bmo.countBM(iBM);
			if( nBM == 1)
			{
				bmo.findBMMembers(iBM);
				if( bmo.m_ChildTK == 0 )
					nBM = 0;
			}

			str.Format(_T("Number of elements...%d  " ), nBM);
			Trace(str);
			
		
	}

}


void CAIPITabView::ClickGridBM_TK(int row, int col)
{
	CAipi_RETE_BM bmo;
	if( bmo.sizeBM() == 0 )
		return;

	CString str = _T("");
	COLORREF clr1 = RGB(255, 255, 220);
	COLORREF clr3 = RGB(255, 255, 100);
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();


	if( col == 1 )
	{
		int iniBME =0;
		int endBME = 0;
		
		
		if( !m_vTempBM.empty())
		{
			iniBME = m_vTempBM.at(0);
			endBME = m_vTempBM.at(1);

			for( int i = iniBME; i <= endBME; ++i)
			{
				pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 1, clr1);
				pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 2, clr1);
				pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 3, clr1);
				pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 4, clr1);
				pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 5, clr1);
				pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 6, clr1);
				pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 7, clr1);
				pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 8, clr1);
			}
			pMainFrame->m_GridBM_TK.Invalidate();
			m_vTempBM.clear();
		}

		CString strBM = pMainFrame->m_GridBM_TK.GetItemText(row, col);
		str = _T("*** Beta Memory: ") + strBM + _T(" ***\n");
		Trace(str);
			
		strBM.Delete(0,1);
		int iBM = _ttoi(strBM);
		int r = 0;
		
		
		
		for( CMainFrame::g_mmBM::const_iterator iter = pMainFrame->gmmBM.begin(); iter!= pMainFrame->gmmBM.end(); ++iter)
		{
			r++;
			if( iter->first == iBM)
			{
				iniBME = r; 
				m_vTempBM.push_back(iniBME);
				int n = bmo.countBM(iBM);
				endBME = iniBME + n-1;
				m_vTempBM.push_back(endBME);
				break;
			}
		}

		for( int i = iniBME; i<= endBME; ++i)
		{
			pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 1, clr3);
			pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 2, clr3);
			pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 3, clr3);
			pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 4, clr3);
			pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 5, clr3);
			pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 6, clr3);
			pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 7, clr3);
			pMainFrame->m_GridBM_TK.SetItemBkColour(i+1, 8, clr3);
		}
		
		pMainFrame->m_GridBM_TK.Invalidate();

	
				
			int nBM = bmo.countBM(iBM);
			if( nBM == 1)
			{
				bmo.findBMMembers(iBM);
				if( bmo.m_ChildTK == 0 )
					nBM = 0;
			}

			str.Format(_T("Number of elements...%d  " ), nBM);
			Trace(str);
			
		
	}



}




void CAIPITabView::OnBtnRange() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int grid = pMainFrame->SelectGrid();

	UpdateData(true);

	switch(grid)
	{
	case GRID_LHS:
		m_iMinRange_LHS = m_iMinRange;
		m_iMaxRange_LHS = m_iMaxRange;
		UpdateData(false);
		FillRangeGridLHS();
		break;
	case GRID_RHS:
		m_iMinRange_RHS = m_iMinRange;
		m_iMaxRange_RHS = m_iMaxRange;
		UpdateData(false);
		FillRangeGridRHS();
		break;
	
	case GRID_WM:
		m_iMinRange_WM = m_iMinRange;
		m_iMaxRange_WM = m_iMaxRange;
		UpdateData(false);
		FillRangeGridWM();
		break;
	
	case GRID_COND_LINK:
		m_iMinRange_CLink = m_iMinRange;
		m_iMaxRange_CLink = m_iMaxRange;
		UpdateData(false);
		FillRangeGridCondLink();
		break;
		
	case GRID_AGENDA:
		m_iMinRange_Agenda = m_iMinRange;
		m_iMaxRange_Agenda = m_iMaxRange;
		UpdateData(false);
		break;
	case GRID_AM:
		m_iMinRange_AM = m_iMinRange;
		m_iMaxRange_AM = m_iMaxRange;
		UpdateData(false);
		FillRangeGridAM();
		break;
	case GRID_BM:
		m_iMinRange_BM = m_iMinRange;
		m_iMaxRange_BM = m_iMaxRange;
		UpdateData(false);
		FillRangeGridBM();
		break;
	case GRID_BM_TK:
		m_iMinRange_BM_TK = m_iMinRange;
		m_iMaxRange_BM_TK = m_iMaxRange;
		UpdateData(false);
		FillRangeGridBM_TK();
		break;
	case GRID_RETE:
		m_iMinRange_RETE = m_iMinRange;
		m_iMaxRange_RETE = m_iMaxRange;
		UpdateData(false);
		FillRangeGridRETE();
		break;


	}

	
	
}

void CAIPITabView::OnBtnAll() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	int grid = pMainFrame->SelectGrid();
	
	UpdateData(true);
	m_iMinRange = 0;
	
	switch(grid)
	{
	case GRID_LHS:
		m_iMaxRange = FillGridLHS();
		break;
	case GRID_RHS:
		m_iMaxRange = FillGridRHS();
		break;
	case GRID_WM:
		m_iMaxRange = FillGridWM();
		break;
	case GRID_COND_LINK:
		m_iMaxRange = FillGridCondLink();
		break;
	case GRID_AGENDA:
		break;
	case GRID_AM:
		m_iMaxRange = FillGridAM();
		break;
	case GRID_BM:
		m_iMaxRange = FillGridBM();
		break;
	case GRID_BM_TK:
		m_iMaxRange = FillGridBM_TK();
		break;
	case GRID_RETE:
		m_iMaxRange = FillGridRETE();
		break;


	}
	
	UpdateData(false);

	
}
