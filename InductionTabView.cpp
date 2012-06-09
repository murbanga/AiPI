// InductionTabView.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "InductionTabView.h"

#include "MainFrm.h"

#include ".\DataFileCSV\CDataFile.h"
#include ".\BasicExcel\BasicExcelVC6.hpp"
//ComboListCtrl
#include ".\ComboListCtrl\ComboListCtrl.h"
#include ".\ComboListCtrl\InPlaceEditCombo.h"

using namespace std;
using std::string;
using std::vector;
using std::map;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CAIPIApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CInductionTabView dialog
IMPLEMENT_DYNAMIC(CInductionTabView, COXSizeDialogBar)


CInductionTabView::CInductionTabView(CWnd* pParent /*=NULL*/)
: m_query(GetSession()),	m_hSelNodeType(TNode_None),
COXSizeDialogBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	//{{AFX_DATA_INIT(CInductionTabView)
	// GridCtrl initialization
	
	//}}AFX_DATA_INIT
		
	nClasses = 0;
	m_iVTablesPos = 40;
	m_iSizeFactor = 1;
	m_bRejectEditAttempts = TRUE;
    m_bRejectEditChanges = TRUE;

}

CInductionTabView::~CInductionTabView()
{
	//int index = m_TabCtrl.GetPageCount();
	//m_TabCtrl.DeletePage(index, TRUE);
	//m_TabCtrl.OnDestroy();
}

void CInductionTabView::DoDataExchange(CDataExchange* pDX)
{
	COXSizeDialogBar::DoDataExchange(pDX);

	
	//{{AFX_DATA_MAP(CInductionTabView)
	DDX_Control(pDX, IDC_STATIC_GRAPH, m_stcGraph);
	DDX_Control(pDX, IDC_STATIC_SEL_ATRIBUTES, m_stcSelAtributes);
	DDX_Control(pDX, IDC_STATIC_ATRIBUTES, m_stcAtributes);
	DDX_Control(pDX, IDC_INDUCTION_CHECKGRAPH, m_checkGraph);
	DDX_Control(pDX, IDC_INDUCTION_CHECKVALUES, m_checkValues);
	DDX_Control(pDX, IDC_INDUCTION_LIST2, m_ListCtrl2);
	DDX_Control(pDX, IDC_INDUCTION_LIST1, m_ListCtrl1);
	DDX_Control(pDX, IDC_INDUCTIONTAB, m_TabCtrl);
	DDX_Control(pDX, IDC_INDUCTION_TREECTRL, m_treeCtrl);
	DDX_Control(pDX, IDC_STATIC_QUERY, m_stcQuery);
	DDX_Control(pDX, IDC_STATIC_DATA, m_stcData);
	DDX_Control(pDX, IDC_STATIC_TABLES, m_stcTables);
	
	
	DDX_Control(pDX, IDC_INDUCTION_GRAPH, m_Chart);
	DDX_Control(pDX, IDC_INDUCTION_SPIN, m_spinTable);

	DDX_Control(pDX, IDC_SCINCTRL, m_ScinCtrl);
	
	//}}AFX_DATA_MAP
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	DDX_Control(pDX, IDC_GRID, pMainFrame->m_GridInduction);
	
}


BEGIN_MESSAGE_MAP(CInductionTabView, COXSizeDialogBar)
	//{{AFX_MSG_MAP(CInductionTabView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_INDUCTIONTAB, OnSelchangeTabCtrl)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_INDUCTION_LIST1, OnItemchangedList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_INDUCTION_LIST2, OnItemchangedList2)
	ON_BN_CLICKED(IDC_INDUCTION_CHECKGRAPH, OnInductionCheckGraph)
	ON_BN_CLICKED(IDC_INDUCTION_CHECKVALUES, OnInductionCheckValues)
	ON_NOTIFY(TVN_SELCHANGED, IDC_INDUCTION_TREECTRL, OnSelchangedTreeCtrl)
	ON_NOTIFY(NSCS_SELECTEDITEM, IDC_INDUCTION_GRAPH, NSChart_OnChartSelectedItem)
	ON_NOTIFY(UDN_DELTAPOS, IDC_INDUCTION_SPIN, OnDeltaposInductionSpin)
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,TabToolTips)
	//ON_MESSAGE(WM_VALIDATE, OnEndLabelEditVariableCriteria)
	ON_MESSAGE(WM_SET_ITEMS, PopulateComboList)

	ON_NOTIFY(NM_DBLCLK, IDC_GRID, OnGridDblClick)
    ON_NOTIFY(NM_CLICK, IDC_GRID, OnGridClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnGridRClick)
	ON_NOTIFY(GVN_BEGINLABELEDIT, IDC_GRID, OnGridStartEdit)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_NOTIFY(GVN_SELCHANGING, IDC_GRID, OnGridStartSelChange)
	ON_NOTIFY(GVN_SELCHANGED, IDC_GRID, OnGridEndSelChange)
	ON_NOTIFY(GVN_BEGINDRAG, IDC_GRID, OnGridBeginDrag)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnGridRClick)
	ON_NOTIFY(NM_RCLICK, IDC_GRID, OnGridRClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInductionTabView message handlers

BOOL CInductionTabView::OnInitDialog() 
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
	pFilePage = new CPageFileDlg;
	pFilePage->m_pGrid = &pMainFrame->m_GridInduction;
	pFilePage->m_pListCtrl1 = &m_ListCtrl1;
	pFilePage->m_pListCtrl2 = &m_ListCtrl2;
	bSuccess = pFilePage->Create(IDD_PAGEFILE_DLG, &m_RollupCtrl);
	m_RollupCtrl.InsertPage(_T("Load Data"), pFilePage);


	pEditPage = new CPageEditDlg;
	pEditPage->m_pGrid = &pMainFrame->m_GridInduction;
	bSuccess = pEditPage->Create(IDD_PAGEEDIT_DLG, &m_RollupCtrl);
	m_RollupCtrl.InsertPage(_T("Edit"), pEditPage);
	
	pInsertPage = new CPageInsertDlg;
	pInsertPage->m_pGrid = &pMainFrame->m_GridInduction;
	bSuccess = pInsertPage->Create(IDD_PAGEINSERT_DLG, &m_RollupCtrl);
	m_RollupCtrl.InsertPage(_T("Insert"), pInsertPage);


	pFormatPage = new CPageFormatDlg;
	pFormatPage->m_pGrid = &pMainFrame->m_GridInduction;
	bSuccess = pFormatPage->Create(IDD_PAGEFORMAT_DLG, &m_RollupCtrl);
	m_RollupCtrl.InsertPage(_T("Grid Format"), pFormatPage);


	pOptionsPage = new CPageOptionsDlg;
	pOptionsPage->m_pGrid = &pMainFrame->m_GridInduction;
	bSuccess = pOptionsPage->Create(IDD_PAGEOPTIONS_DLG, &m_RollupCtrl);
	m_RollupCtrl.InsertPage(_T("Grid Options"), pOptionsPage);

	pCellSizePage = new CPageCellSizeDlg;
	pCellSizePage->m_pGrid = &pMainFrame->m_GridInduction;
	bSuccess = pCellSizePage->Create(IDD_PAGECELLSIZE_DLG, &m_RollupCtrl);
	m_RollupCtrl.InsertPage(_T("Cell Sizing"), pCellSizePage);

	

	
	if(!InitLayoutManager())
	{
		MessageBox(_T("Failed to init layout manager!"));
	}
	
	
	UpdateData(FALSE);
	CreateTab();
	InitScintilla();
	InitGridCtrl();
	
	
	pInsertPage->UpdateEditControls();
	
	
	CreateList1();
	CreateNominalList2();
	
	
	m_ListCtrl1.SetReadOnlyColumns(0);
	m_ListCtrl1.SetReadOnlyColumns(2);
	m_ListCtrl1.SetReadOnlyColumns(3);
	m_ListCtrl1.SetComboColumns(1);
	

	m_blInited = TRUE;
	m_ListCtrl1.Init();

	m_ListCtrl1.EnableVScroll();
	
	//Set NSChartCtrl style
	m_Chart.PrepareColors(CNSChartCtrl::SimpleColors);
	m_Chart.SetChartStyle(NSCS_BAR);

	
	//TreeCtrl DataBase
	if(!::IsWindow(m_treeCtrl.GetSafeHwnd()))
	return 0;
	
	VERIFY(m_imageList.Create(IDB_IMAGELIST, 16, 0, RGB(255,0,255)));
	m_imageList.SetBkColor(GetSysColor(COLOR_WINDOW));
	m_treeCtrl.SetImageList(&m_imageList,TVSIL_NORMAL);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CInductionTabView::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	COXSizeDialogBar::OnUpdateCmdUI(pTarget,FALSE);
}

void CInductionTabView::CreateTab()
{
	
	TC_ITEM pTabCtrlItem;	// tab control item structure
	
    pTabCtrlItem.mask = TCIF_TEXT | TCIF_IMAGE;
	pTabCtrlItem.iImage = 0;
	
	
	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();

	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		pTabCtrlItem.pszText = _T("Atributes");
		break;
	default:
		pTabCtrlItem.pszText = _T("Atributos");
		break;
	}	
	m_TabCtrl.InsertItem( 0, &pTabCtrlItem );	// first tab
	
	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		pTabCtrlItem.pszText = _T("Data");
		break;
	default:
		pTabCtrlItem.pszText = _T("Datos");
		break;
	}

	pTabCtrlItem.iImage = 1;
	m_TabCtrl.InsertItem( 1, &pTabCtrlItem );	// second tab
	
	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		pTabCtrlItem.pszText = _T("Test");
		break;
	default:
		pTabCtrlItem.pszText = _T("Prueba");
		break;
	}
	
	pTabCtrlItem.iImage = 2;
	m_TabCtrl.InsertItem( 2, &pTabCtrlItem );	// third tab
	


	//	do image list here
	//
	m_TabImageList.Create(IDB_TABINDUCTIONIMAGES, 17, 1, COLORREF(0xc0c0c0));	
	m_TabCtrl.SetImageList(&m_TabImageList);
	//
	//	init the tab control & edit box
	//
	
	NMHDR nmHDR;
	LRESULT pResult;
	OnSelchangeTabCtrl(&nmHDR,  &pResult);	// default
}



BOOL CInductionTabView::TabToolTips(UINT id, NMHDR * pNMHDR, LRESULT * pResult )
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
			pTTT->lpszText = _T("Atributos");
			break;
			default:
			pTTT->lpszText = _T("Atributes");
			break;
		}
		return TRUE;
	}
	if(pTTT->hdr.idFrom == 1)
	{
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
			pTTT->lpszText = _T("Datos");
			break;
			default:
			pTTT->lpszText = _T("Data");
			break;
		}
		return TRUE;	
	}

	if(pTTT->hdr.idFrom == 2)
	{
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
			pTTT->lpszText = _T("Prueba");
			break;
			default:
			pTTT->lpszText = _T("Test");
			break;
		}
		return TRUE;	
	}

	return FALSE;
}

void CInductionTabView::OnSelchangeTabCtrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	
	*pResult = 0;
	int iCurTab = m_TabCtrl.GetCurSel();	// get tab 
	
	
	
	switch(iCurTab)
	{
		
		default:
		
		case 0:		// Induction Attributes
			//Page 1
			m_ListCtrl1.ShowWindow(SW_SHOW);
			m_ListCtrl2.ShowWindow(SW_SHOW);
			m_Chart.ShowWindow(SW_SHOW);
			m_stcAtributes.ShowWindow(SW_SHOW);
			m_stcSelAtributes.ShowWindow(SW_SHOW);
			m_stcGraph.ShowWindow(SW_SHOW);
			m_checkGraph.ShowWindow(SW_SHOW);
			m_checkValues.ShowWindow(SW_SHOW);

			//Page 2
			m_RollupCtrl.ShowWindow(SW_HIDE);
			pMainFrame->m_GridInduction.ShowWindow(SW_HIDE);
			m_stcQuery.ShowWindow(SW_HIDE);
			m_stcData.ShowWindow(SW_HIDE);
			m_stcTables.ShowWindow(SW_HIDE);
			m_ScinCtrl.ShowWindow(SW_HIDE);
			m_treeCtrl.ShowWindow(SW_HIDE);
			m_spinTable.ShowWindow(SW_HIDE);
			
			ActualInterfacePage1(m_eIntPage1);
			pInsertPage->UpdateEditControls();
	
			
			break;
		case 1:		// Data
			//Page 1
			pMainFrame->m_CurrentGrid = GRID_INDUCTION;

			m_ListCtrl1.ShowWindow(SW_HIDE);
			m_ListCtrl2.ShowWindow(SW_HIDE);
			m_Chart.ShowWindow(SW_HIDE);
			m_stcAtributes.ShowWindow(SW_HIDE);
			m_stcSelAtributes.ShowWindow(SW_HIDE);
			m_stcGraph.ShowWindow(SW_HIDE);
			m_checkGraph.ShowWindow(SW_HIDE);
			m_checkValues.ShowWindow(SW_HIDE);

			//Page 2
			m_RollupCtrl.ShowWindow(SW_SHOW);
			pMainFrame->m_GridInduction.ShowWindow(SW_SHOW);
			m_stcQuery.ShowWindow(SW_SHOW);
			m_stcData.ShowWindow(SW_SHOW);
			m_stcTables.ShowWindow(SW_SHOW);
			m_ScinCtrl.ShowWindow(SW_SHOW);
			m_treeCtrl.ShowWindow(SW_SHOW);
			m_spinTable.ShowWindow(SW_SHOW);
			
			ActualInterfacePage2(m_eIntPage2);
			pInsertPage->UpdateEditControls();
			UpdateMenuUI();
	
			break;
			
	}	// end switch on tab selection
	
}		// end OnSelchangeTabCtrl()


void CInductionTabView::ActualInterfacePage1(int actualWnd)
{
	switch(actualWnd)
	{
	case ATRIBUTES:
		Init_Atributes_Page1();
		break;
	case ATRIBUTES_ATRIBUTEVALUES:
		Init_Atributes_AtributeValues_Page1();
		break;
	case ATRIBUTES_GRAPH:
		Init_Atributes_Graph_Page1();
		break;
	case ATRIBUTES_ATRIBUTEVALUES_GRAPH:
		Init_Atributes_AtributeValues_Graph_Page1();
		break;

	}

}


void CInductionTabView::ActualInterfacePage2(int actualWnd)
{
	switch(actualWnd)
	{
	case QUERY:
		Init_Query_Page2();
		break;
	case TABLES:
		Init_Tables_Page2();
		break;
	case DATA:
		Init_Data_Page2();
		break;
	case QUERY_TABLES:
		Init_Query_Tables_Page2();
		break;
	case QUERY_DATA:
		Init_Query_Data_Page2();
		break;
	case TABLES_DATA:
		Init_Tables_Data_Page2();
		break;
	case VTABLES_DATA:
		Init_VTables_Data_Page2();
		break;
	case QUERY_TABLES_DATA:
		Init_Query_Tables_Data_Page2();
		break;
	case QUERY_VTABLES_DATA:
		Init_Query_VTables_Data_Page2();
		break;


	}

}


BOOL CInductionTabView::InitLayoutManager()
{
	
	BOOL retval = TRUE;

	if(!m_LayoutManager.IsAttached()) 
	{
		m_LayoutManager.Attach(this);

		//InitLayoutManagerPage1();
		//InitLayoutManagerPage2();
		InitPages();
		
	}

	return retval;
	
}

void CInductionTabView::InitPages()
{
		
		m_eIntPage1 = ATRIBUTES;
		m_eIntPage2 = DATA;
	
		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);
	
		m_LayoutManager.SetMinMax(IDC_INDUCTION_CHECKGRAPH, CSize(60,0), CSize(0,0));


		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_TOP, OX_LMT_SAME, 40);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_RIGHT, OX_LMT_POSITION, 30);
		
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_TOP, OX_LMT_SAME, 40);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_LEFT,  OX_LMT_OPPOSITE, 1, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_CHECKGRAPH);
		//m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_LIST1);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		// Constrain ListCtrl1
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_TOP,  OX_LMT_OPPOSITE, 5, IDC_STATIC_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_BOTTOM, OX_LMT_POSITION,100);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_RIGHT, OX_LMT_SAME, -5);



	
		
		//m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_CHECKGRAP);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		// Constrain ListCtrl2
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_TOP, OX_LMT_POSITION, 30 );
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
		//m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Graph control
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_GRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 40);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);
		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_TABLES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		



		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_TOP, OX_LMT_SAME, 40);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		

	//GridCtrl
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	
	
	m_LayoutManager.RedrawLayout();

}


void CInductionTabView::Hide_Page1()
{
		//m_LayoutManager.Detach();
		//m_LayoutManager.Attach(this);
	
		//m_LayoutManager.SetMinMax(IDC_INDUCTION_CHECKGRAPH, CSize(60,0), CSize(0,0));
	
		//m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_CHECKGRAPH);
		//m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		//m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		//m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_TOP, OX_LMT_SAME, 40);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_RIGHT, OX_LMT_POSITION, 30);
				
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_TOP, OX_LMT_SAME, 40);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_LEFT,  OX_LMT_OPPOSITE, 1, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
		//m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		// Constrain ListCtrl1
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_TOP,  OX_LMT_OPPOSITE, 5, IDC_STATIC_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		
		
		
		//m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_LIST1);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_RIGHT, OX_LMT_SAME, -5);


		// Constrain ListCtrl2
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_TOP, OX_LMT_POSITION, 30 );
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
		//m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_LIST2);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Graph control
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_GRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		//m_LayoutManager.RedrawLayout();	

}

void CInductionTabView::Hide_Page2()
{
	
		//m_LayoutManager.Detach();
		//m_LayoutManager.Attach(this);

		/*	
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);
      */

		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 40);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);
		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
				
		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_TABLES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		

	//GridCtrl
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_GRID);
	m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
	//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_SAME, -5);


		
	//m_LayoutManager.RedrawLayout();
	
}






void CInductionTabView::Init_Atributes_AtributeValues_Page1()
{
		
		m_eIntPage1 = ATRIBUTES_ATRIBUTEVALUES; 

		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);
	
		m_LayoutManager.SetMinMax(IDC_INDUCTION_CHECKGRAPH, CSize(60,0), CSize(0,0));
	
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_TOP, OX_LMT_SAME, 35);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_LIST2);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_RIGHT, OX_LMT_POSITION, 30);
				
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_TOP, OX_LMT_SAME, 35);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_LIST2);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_LEFT,  OX_LMT_OPPOSITE, 1, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_CHECKGRAPH);
		//m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_LIST1);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		// Constrain ListCtrl1
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_TOP,  OX_LMT_OPPOSITE, 5, IDC_STATIC_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_BOTTOM, OX_LMT_POSITION, 60);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		
		
		
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_LIST1);
		//m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_LIST2);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_RIGHT, OX_LMT_SAME, -5);


		// Constrain ListCtrl2
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_TOP, OX_LMT_POSITION, 30 );
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_BOTTOM, OX_LMT_POSITION, 100);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
		//m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_LIST2);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Graph control
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_GRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
		
		m_LayoutManager.RedrawLayout();

		
}


void CInductionTabView::Init_Atributes_AtributeValues_Graph_Page1()
{
		
		m_eIntPage1 = ATRIBUTES_ATRIBUTEVALUES_GRAPH; 

		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);
	
		m_LayoutManager.SetMinMax(IDC_INDUCTION_CHECKGRAPH, CSize(60,0), CSize(0,0));
	
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_TOP, OX_LMT_SAME, 35);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_RIGHT, OX_LMT_POSITION, 30);
		
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_TOP, OX_LMT_SAME, 35);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_LEFT,  OX_LMT_OPPOSITE, 1, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_RIGHT, OX_LMT_SAME, -5);


		
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_CHECKGRAPH);
		//m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_LIST1);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		// Constrain ListCtrl1
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_TOP,  OX_LMT_OPPOSITE, 5, IDC_STATIC_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_BOTTOM, OX_LMT_POSITION, 35);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
				
		
		
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_LIST1);
		//m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_LIST2);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_RIGHT, OX_LMT_SAME, -5);


		// Constrain ListCtrl2
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_TOP, OX_LMT_POSITION, 30 );
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_BOTTOM, OX_LMT_POSITION, 70);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_LIST2);
		//m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_GRAPH);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Graph control
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_GRAPH);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_BOTTOM, OX_LMT_POSITION, 100);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
		
		m_LayoutManager.RedrawLayout();
	

}



void CInductionTabView::Init_Atributes_Graph_Page1()
{
		
		m_eIntPage1 = ATRIBUTES_GRAPH; 


		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);
	
		m_LayoutManager.SetMinMax(IDC_INDUCTION_CHECKGRAPH, CSize(60,0), CSize(0,0));


		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_TOP, OX_LMT_SAME, 35);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_RIGHT, OX_LMT_POSITION, 30);
		
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_TOP, OX_LMT_SAME, 35);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_LEFT,  OX_LMT_OPPOSITE, 1, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_CHECKGRAPH);
		//m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_LIST1);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		// Constrain ListCtrl1
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_TOP,  OX_LMT_OPPOSITE, 5, IDC_STATIC_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_BOTTOM, OX_LMT_POSITION, 60);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		
		//m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_RIGHT, OX_LMT_SAME, -5);


		// Constrain ListCtrl2
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_TOP, OX_LMT_POSITION, 30 );
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_LIST1);
		//m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_GRAPH);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Graph control
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_GRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_BOTTOM, OX_LMT_POSITION, 100);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
				
		m_LayoutManager.RedrawLayout();
	

}


void CInductionTabView::Init_Atributes_Page1()
{
		
		
		m_eIntPage1 = ATRIBUTES; 


		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);
	
		m_LayoutManager.SetMinMax(IDC_INDUCTION_CHECKGRAPH, CSize(60,0), CSize(0,0));


		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_TOP, OX_LMT_SAME, 35);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKGRAPH, OX_LMS_RIGHT, OX_LMT_POSITION, 30);
		
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_TOP, OX_LMT_SAME, 35);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_LEFT,  OX_LMT_OPPOSITE, 1, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_CHECKVALUES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_CHECKGRAPH);
		//m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_INDUCTION_LIST1);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_ATRIBUTES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		// Constrain ListCtrl1
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_TOP,  OX_LMT_OPPOSITE, 5, IDC_STATIC_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_BOTTOM, OX_LMT_POSITION,100);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST1, OX_LMS_RIGHT, OX_LMT_SAME, -5);



	
		
		//m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_CHECKGRAP);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_SEL_ATRIBUTES, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		// Constrain ListCtrl2
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_TOP, OX_LMT_POSITION, 30 );
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_SEL_ATRIBUTES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_LIST2, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
		//m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_CHECKGRAPH);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_STATIC_GRAPH, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Graph control
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_GRAPH);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_GRAPH, OX_LMS_RIGHT, OX_LMT_SAME, -5);

				
		m_LayoutManager.RedrawLayout();
	

}




void CInductionTabView::InitLayoutManagerPage2()
{
		
	Init_Data_Page2();
	
}

void CInductionTabView::InitLayoutManagerPage1()
{
		
	Init_Atributes_Page1();	
			
	
}



void CInductionTabView::Init_Tables_Data_Page2()
{
		
		
		m_eIntPage2 = TABLES_DATA;
	
		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);

	
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_TABLES);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);
		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_GRID);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_SAME, -5);



		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_TABLES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 35);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_TREECTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		

	//GridCtrl
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_DATA);
	//m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_POSITION, 100);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	

		
	m_LayoutManager.RedrawLayout();
	
}

void CInductionTabView::Init_VTables_Data_Page2()
{
	
		m_eIntPage2 = VTABLES_DATA;
	
	
		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);

	
		m_LayoutManager.SetMinMax(IDC_INDUCTION_SPIN, CSize(50,0), CSize(0,0));
		
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_TABLES);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);
		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_POSITION, m_iVTablesPos);

		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_TABLES);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_POSITION, m_iVTablesPos);

						
		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_SPIN);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_POSITION, m_iVTablesPos);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_TREECTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_POSITION, 100);
		
		

	//GridCtrl
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_TREECTRL);
	//m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_POSITION, 100);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	
		
	m_LayoutManager.RedrawLayout();
	
}

void CInductionTabView::Init_Query_VTables_Data_Page2()
{
		
		m_eIntPage2 = QUERY_VTABLES_DATA;
	
		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);

		
		m_LayoutManager.SetMinMax(IDC_INDUCTION_TREECTRL, CSize(50,0), CSize(0,0));
		

		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);


		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_TOP, OX_LMT_SAME, 35 );
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 30);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_SCINCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_POSITION, m_iVTablesPos);

		
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_TABLES);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_POSITION, m_iVTablesPos);

		
				
		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_SPIN);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_POSITION, m_iVTablesPos);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_SCINCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_TREECTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_POSITION, 100);
		
		

	//GridCtrl
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_TREECTRL);
	//m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_POSITION, 100);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
	
		
	m_LayoutManager.RedrawLayout();
	
}


void CInductionTabView::Init_Query_Data_Page2()
{
		
		m_eIntPage2 = QUERY_DATA; 

		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);

	
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);
		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 35);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_GRID);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_SAME, -5);


		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_SCINCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		

	//GridCtrl
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_DATA);
	//m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_POSITION, 100);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	
	m_LayoutManager.RedrawLayout();
	
}

void CInductionTabView::Init_Query_Tables_Page2()
{
		
		m_eIntPage2 = QUERY_TABLES;
	
		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);

	
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);
		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 35);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_SCINCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_GRID);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_SAME, -5);



		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_TABLES);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 100);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		

	//GridCtrl
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	

	m_LayoutManager.RedrawLayout();
	
}







void CInductionTabView::Init_Data_Page2()
{
		

		m_eIntPage2 = DATA; 

		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);

	
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_DATA);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);
		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_TABLES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		



		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		

	//GridCtrl
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		
	m_LayoutManager.RedrawLayout();
	
}


void CInductionTabView::Init_Tables_Page2()
{
	
		m_eIntPage2 = TABLES;
		
	
		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);

		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_TABLES);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);
			
		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);
		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_GRID);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_SAME, -5);


				
		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_TABLES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		

	//GridCtrl
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	

		
	m_LayoutManager.RedrawLayout();
	
}



void CInductionTabView::Init_Query_Tables_Data_Page2()
{
	
		
		m_eIntPage2 = QUERY_TABLES_DATA;
	
		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);

	
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);


		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);
		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 30);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_SCINCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_GRID);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		

		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_TABLES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 60);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_TREECTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		

	//GridCtrl
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_POSITION, 100);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	

		
	m_LayoutManager.RedrawLayout();
	
}


void CInductionTabView::Init_Query_Page2()
{
	
		m_eIntPage2 = QUERY;		


		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);

	
	
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);
		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_TOP, OX_LMT_SAME, 35);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
	
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_GRID);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_SAME, -5);




		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_TABLES);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		

	//GridCtrl
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_DATA);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
	m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	Hide_Page1();
		
	m_LayoutManager.RedrawLayout();
	
}




void CInductionTabView::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
{
	
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	m_LayoutManager.RedrawLayout();

}

void CInductionTabView::CreateList1()
{
	m_ListCtrl1.SetExtendedStyle(LVS_EX_GRIDLINES| LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
	//Put Columns titles
	m_ListCtrl1.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 170);
	m_ListCtrl1.InsertColumn(1, _T("Input/Output"), LVCFMT_LEFT, 80);
	m_ListCtrl1.InsertColumn(2, _T("Type"), LVCFMT_LEFT, 70);
	m_ListCtrl1.InsertColumn(3, _T("No."), LVCFMT_LEFT, 40);

}

void CInductionTabView::CreateNominalList2()
{
	//Create image list
	m_ListCtrl2.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_UNDERLINEHOT|LVS_EX_INFOTIP |LVS_SORTASCENDING   );
    	
	//Put Columns titles
	m_ListCtrl2.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 30);
	m_ListCtrl2.InsertColumn(1, _T("Atribute Label"), LVCFMT_LEFT, 140);
	m_ListCtrl2.InsertColumn(2, _T("Frequency"), LVCFMT_LEFT, 80);
	m_ListCtrl2.InsertColumn(3, _T("%"), LVCFMT_LEFT, 60);

}

void CInductionTabView::CreateNumericList2()
{
	m_ListCtrl2.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_UNDERLINEHOT|LVS_EX_INFOTIP |LVS_SORTASCENDING   );
    
	//Put Columns titles
	m_ListCtrl2.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 30);
	m_ListCtrl2.InsertColumn(1, _T("Min. Limit"), LVCFMT_LEFT, 70);
	m_ListCtrl2.InsertColumn(2, _T("Max. Limit"), LVCFMT_LEFT, 70);
	m_ListCtrl2.InsertColumn(3, _T("Frequency"), LVCFMT_LEFT, 80);
	m_ListCtrl2.InsertColumn(4, _T("%"), LVCFMT_LEFT, 60);
	
}



LRESULT CInductionTabView::PopulateComboList(WPARAM wParam, LPARAM lParam)
{
	// Get the Combobox window pointer
	CComboBox* pInPlaceCombo = static_cast<CComboBox*> (GetFocus());

	// Get the inplace combbox top left
	CRect obWindowRect;

	pInPlaceCombo->GetWindowRect(&obWindowRect);
	
	CPoint obInPlaceComboTopLeft(obWindowRect.TopLeft()); 
	
	// Get the active list
	// Get the control window rect
	// If the inplace combobox top left is in the rect then
	// The control is the active control
	m_ListCtrl1.GetWindowRect(&obWindowRect);
	
	int iColIndex = wParam;
	
	CStringList* pComboList = reinterpret_cast<CStringList*>(lParam);
	pComboList->RemoveAll(); 

	if (obWindowRect.PtInRect(obInPlaceComboTopLeft)) 
	{
		if (INDEX_COMBO == iColIndex)
		{
			pComboList->AddTail(_T("Input"));
			pComboList->AddTail(_T("Output"));
		}
	}
	
	return true;
}

/*
LRESULT CInductionTabView::OnEndLabelEditVariableCriteria(WPARAM wParam, LPARAM lParam) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)lParam;
	// TODO: Add your control notification handler code here
	
	if (wParam == IDC_INDUCTION_LIST1)
	{
		// Update the item text with the new text
		CString strUpdatedTxt = pDispInfo->item.pszText;  
		
		// Validate the format of the new string for the edit columns
		// If invalid then
		// Set pResult to 1 
		switch(pDispInfo->item.iSubItem)
		{
		case 0:
		case 1:
			break;
		default:
			{
				if (!strUpdatedTxt.IsEmpty()) 
				{
					// Get the left most non numeral characters
					// Get the remaining numerals
					// If the left most part does not contain the mandatory conditions 
					// Or the rest contains the mandatory conditions 
					// Display an error and set focus back onto the control
					int iFirstNumeralOccurrance = strUpdatedTxt.FindOneOf(_T("0123456789."));
					CString strNonNumerals = strUpdatedTxt.Left(iFirstNumeralOccurrance);
					CString strNumerals = strUpdatedTxt.Mid(iFirstNumeralOccurrance);
					
					strNonNumerals.TrimLeft(); 
					strNonNumerals.TrimRight();
					strNumerals.TrimLeft();
					strNumerals.TrimRight();  

					int iDecimalIndex = strNumerals.Find(_T("."));
					
					if ((-1 != iDecimalIndex) && (iDecimalIndex != (strNumerals.GetLength() - 1)))  
					{
						iDecimalIndex = strNumerals.Find(_T("."), iDecimalIndex + 1);
					}

					// Check that the condition is either
					// Not empty or "=" or "!=" or "<" or ">" or "<=" or ">="
					// The Numerals do not contain 
					// Space or more than 1 "." or any of the conditions
					if (
						(!strNonNumerals.IsEmpty()) || 
						(-1 != strNumerals.Find(_T(" "))) ||
						(-1 != iDecimalIndex)
						)
					{
						AfxMessageBox(_T("Invalid text entered. The text will be reset")); 
						m_ListCtrl1.SetItemText(pDispInfo->item.iItem, pDispInfo->item.iSubItem, _T(""));
					}
					return 0;
				}
			}
			break;
		}
	}

	return 1;
}
*/


LVITEM CInductionTabView::AddListItem1( int iItem, int iSubItem, LPTSTR szText)
{

	
	//Fills the first column
	LVITEM item;
	item.iItem = iItem;
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT;
	item.pszText = szText;
	VERIFY(m_ListCtrl1.InsertItem(&item)!= -1);
	return item;

}

LVITEM CInductionTabView::AddListItem2( int iItem, int iSubItem, LPTSTR szText, int iImage)
{
	
//Fills the first column
	LVITEM item;
	item.iItem = iItem;
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT|LVIF_IMAGE;
	item.pszText = szText;
	item.iImage = iImage;
	VERIFY(m_ListCtrl2.InsertItem(&item)!= -1);
	return item;

}

void CInductionTabView::AddListSubItem1( LVITEM item, int iItem, int iSubItem, LPTSTR szText)
{
	//Fills the rest columns
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT;
	item.pszText = szText;
	m_ListCtrl1.SetItem(&item);

	return;

}
	  
void CInductionTabView::AddListSubItem2( LVITEM item, int iItem, int iSubItem, LPTSTR szText)
{
	//Fills the rest columns
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT;
	item.pszText = szText;
	m_ListCtrl2.SetItem(&item);

	return;

}

/*
int CInductionTabView::InsertItemList1( int iItem, int iSubItem, LPTSTR szText)
{
	LV_ITEM lvi;
	lvi.mask       = LVIF_TEXT;
	lvi.cchTextMax = 0;
	lvi.lParam     = 0;
	
	
	lvi.iItem      = iItem;
	lvi.iSubItem   = iSubItem;
	lvi.pszText = szText;
		
	int nRtnValue = m_ListCtrl1.InsertItem(&lvi);
	
	m_ListCtrl1.SetItemText(iItem, iSubItem, szText);
	
	
	return nRtnValue;

}

int CInductionTabView::InsertItemList2( int iItem, int iSubItem, LPTSTR szText)
{
	LV_ITEM lvi;
	lvi.mask       = LVIF_TEXT;
	lvi.cchTextMax = 0;
	lvi.lParam     = 0;
	
	
	lvi.iItem      = iItem;
	lvi.iSubItem   = iSubItem;
	lvi.pszText = szText;
		
	int nRtnValue = m_ListCtrl2.InsertItem(&lvi);
	
	m_ListCtrl2.SetItemText(iItem, iSubItem, szText);
	
	
	return nRtnValue;

}
*/

void CInductionTabView::PopulateList1()
{
	//Insert items and subitems
	
	LVITEM Item1, Item2, Item3, Item4;
	
	
	Item1 = AddListItem1(0, 0, _T("INFO") );
    AddListSubItem1(Item1, 0, 1,_T("245"));
	AddListSubItem1(Item1, 0, 2, _T("Por favor reinicie la aplicación para cambiar de estilo de menús."));

	Item2 = AddListItem1(1, 0,_T("ADVISE"));	
	AddListSubItem1(Item2, 1, 1,_T("567"));
	AddListSubItem1(Item2, 1, 2, _T("Antes de ejecutar la base de conocimientos debe ser depurada por el Editor AIPI."));
	
	Item3 = AddListItem1(2, 0, _T("ERROR") );
    AddListSubItem1(Item3, 2, 1,_T("245"));
	AddListSubItem1(Item3, 2, 2, _T("La proposición correspondiente a la regla No.23 no ha sido encontrada."));

	Item4 = AddListItem1(3, 0,_T("WARNING"));	
	AddListSubItem1(Item4, 3, 1,_T("1278"));
	AddListSubItem1(Item4, 3, 2, _T("La función en la regla No.34 está declarada dos veces."));
	

}

void CInductionTabView::PopulateList2()
{
	//Insert items and subitems
	LVITEM Item1, Item2, Item3, Item4;
	
	
	Item1 = AddListItem2(0, 0, _T("String"),0 );
    AddListSubItem2(Item1, 0, 1,_T("$Nombre del Cliente$"));
	AddListSubItem2(Item1, 0, 2, _T("José López"));

	Item2 = AddListItem2(1, 0,_T("int"), 1);	
	AddListSubItem2(Item2, 1, 1,_T("$Número de válvulas$"));
	AddListSubItem2(Item2, 1, 2, _T("24"));
	
	Item3 = AddListItem2(2, 0, _T("int"), 2 );
    AddListSubItem2(Item3, 2, 1,_T("$Número de Clientes$"));
	AddListSubItem2(Item3, 2, 2, _T("765"));

	Item4 = AddListItem2(3, 0,_T("float"), 3);	
	AddListSubItem2(Item4, 3, 1,_T("$Promedio de Venta$"));
	AddListSubItem2(Item4, 3, 2, _T("923.14"));

}

//////////////////////////////////////////////////////////////////////////////////////////////
/// GridCtrl Functions ////
///////////////////////////////////////////////////////////////////////////////////////////////

void CInductionTabView::InitGridCtrl()
{

		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		m_nFixCols = 1;
	    m_nFixRows = 1;
	    m_nCols = 8;
	    m_nRows = 20;
		
		
		g_iColumn = 8;
		g_iRow = 20;
		g_iFixColumn = 1;
		g_iFixRow = 1;

		
		
	    pMainFrame->m_GridInduction.SetEditable(pMainFrame->m_bEditable);
        pMainFrame->m_GridInduction.SetAutoSizeStyle();
		pMainFrame->m_GridInduction.EnableDragAndDrop(TRUE);
		pMainFrame->m_GridInduction.GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
		pMainFrame->m_GridInduction.SetFixedColumnSelection(TRUE);
		pMainFrame->m_GridInduction.SetFixedRowSelection(TRUE);
	    


	    TRY {
		    pMainFrame->m_GridInduction.SetRowCount(m_nRows);
		    pMainFrame->m_GridInduction.SetColumnCount(m_nCols);
		    pMainFrame->m_GridInduction.SetFixedRowCount(m_nFixRows);
		    pMainFrame->m_GridInduction.SetFixedColumnCount(m_nFixCols);
	    }
	    CATCH (CMemoryException, e)
	    {
	    	e->ReportError();
    		return;
	    }
        END_CATCH

		 // Set col/row width and height
	    for (int row = 0; row < pMainFrame->m_GridInduction.GetRowCount(); row++)
        {
	    	for (int col = 0; col < pMainFrame->m_GridInduction.GetColumnCount(); col++)
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
				pMainFrame->m_GridInduction.SetItem(&Item);
				
				pMainFrame->m_GridInduction.SetColumnWidth(col, 60);
				pMainFrame->m_GridInduction.SetRowHeight(row, 18);	
	    	}
        }

#if !defined(_WIN32_WCE) || (_WIN32_WCE < 211)
	//pMainFrame->m_GridInduction.AutoSize();
#endif

}



void CInductionTabView::UpdatePageFileDlg()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	if (!::IsWindow(pFilePage->m_hWnd)) 
	return;
	
	if( pMainFrame->m_bVirtualMode )
	{
		pFilePage->m_chkVirtualMode.SetCheck(true);
	}
	else
	{
		pFilePage->m_chkVirtualMode.SetCheck(false);
	}
	
	if( pMainFrame->m_bCallback)
	{
		pFilePage->m_chkCallback.SetCheck(true);
	}
	else
	{
		pFilePage->m_chkCallback.SetCheck(false);
	}
	
	if( pMainFrame->m_bTables)
	{
		pFilePage->m_chkTables.SetCheck(true);
	}
	else
	{
		pFilePage->m_chkTables.SetCheck(false);
	}
	
	if( pMainFrame->m_bQuery)
	{
		pFilePage->m_chkQuery.SetCheck(true);
	}
	else
	{
		pFilePage->m_chkQuery.SetCheck(false);
	}
	
	if( pMainFrame->m_bData)
	{
		pFilePage->m_chkData.SetCheck(true);
	}
	else
	{
		pFilePage->m_chkData.SetCheck(false);
	}		
	
	if( pMainFrame->m_bVTables)
	{
		pFilePage->m_chkVTables.SetCheck(true);
	}
	else
	{
		pFilePage->m_chkVTables.SetCheck(false);
	}

	
}


void CInductionTabView::UpdatePageOptionDlg()
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


void CInductionTabView::UpdatePageFormatDlg()
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



void CInductionTabView::UpdatePageCellSizeDlg()
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



void CInductionTabView::UpdatePageEditDlg()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	//CPageEditDlg  pageEdit;
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


void CInductionTabView::UpdateMenuUI()
{
	UpdatePageCellSizeDlg();
	UpdatePageEditDlg();
	UpdatePageFileDlg();
	UpdatePageFormatDlg();
	UpdatePageOptionDlg();
		
}



BOOL CInductionTabView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
    
	if (wParam == (WPARAM)pMainFrame->m_GridInduction.GetDlgCtrlID())
    {
        *pResult = 1;
        GV_DISPINFO *pDispInfo = (GV_DISPINFO*)lParam;
        if (GVN_GETDISPINFO == pDispInfo->hdr.code)
        {
            CString szValue = _T("");
			int Col = pDispInfo->item.col;
			int Row = pDispInfo->item.row-1;
			
			pMainFrame->m_GridInduction.SetFixedRowCount(1);
			pMainFrame->m_GridInduction.SetFixedColumnCount(0);
			
			
			int dfMaxCols = g_df.GetNumberOfVariables();
			if(dfMaxCols == 0 )
				return FALSE;
			
			int dfMaxRows = g_df.GetNumberOfSamples(0);
			if(dfMaxRows == 0 )
				return FALSE;

			//pMainFrame->m_GridInduction.SetColumnCount(dfMaxCols);
			//pMainFrame->m_GridInduction.SetRowCount(dfMaxRows + 1);

		
			//CString szHeader = _T("");
			//for(Col = 0; Col<dfMaxCols; ++Col)
			//{
				//int iLength = g_df.GetVariableName(Col, szHeader.GetBuffer(BUFF_SIZE));
				//if(iLength == -1 )
				//{
					//MessageBox(g_df.GetLastError());
					//return FALSE;
				//}
					//pMainFrame->m_GridInduction.SetItemText(0, Col, szHeader);
					//pDispInfo->item.strText.Format(szHeader);
				
				//szHeader.ReleaseBuffer();
			//}
			

			int iLength = g_df.GetData(Col, Row , szValue.GetBuffer(BUFF_SIZE));
			if(iLength == -1 )
			{
				//MessageBox(g_df.GetLastError());
				//return FALSE;
			}
			
						
			pDispInfo->item.strText.Format(szValue);
			
			//TRACE2("Getting Display info for cell %d,%d\n", pDispInfo->item.row, pDispInfo->item.col);
            //pDispInfo->item.strText.Format(_T("Message %d,%d"),pDispInfo->item.row, pDispInfo->item.col);
            return TRUE;
        }
        else if (GVN_ODCACHEHINT == pDispInfo->hdr.code)
        {
            GV_CACHEHINT *pCacheHint = (GV_CACHEHINT*)pDispInfo;
            TRACE(_T("Cache hint received for cell range %d,%d - %d,%d\n"),
                  pCacheHint->range.GetMinRow(), pCacheHint->range.GetMinCol(),
                  pCacheHint->range.GetMaxRow(), pCacheHint->range.GetMaxCol());
        }
    }
    
	return COXSizeDialogBar::OnNotify(wParam, lParam, pResult);
}


// (Thanks to Koay Kah Hoe for this)
BOOL CInductionTabView::PreTranslateMessage(MSG* pMsg) 
{
    if( pMsg->message == WM_KEYDOWN )
    {
        if(pMsg->wParam == VK_RETURN
            || pMsg->wParam == VK_ESCAPE )
        {
            ::TranslateMessage(pMsg);
            ::DispatchMessage(pMsg);
            return TRUE;                    // DO NOT process further
        }
    }
    return COXSizeDialogBar::PreTranslateMessage(pMsg);
}	


void CInductionTabView::Trace(LPCTSTR szFmt, ...)
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


void CInductionTabView::ClearTrace() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndOutputTabView.m_editCtrl1.SetWindowText(_T(""));
	
}



// NM_RCLICK
void CInductionTabView::OnGridRClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Right button click on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}

// GVN_BEGINLABELEDIT
void CInductionTabView::OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Start Edit on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	*pResult = (m_bRejectEditAttempts)? -1 : 0;
}

// GVN_ENDLABELEDIT
void CInductionTabView::OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("End Edit on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
	*pResult = (m_bRejectEditChanges)? -1 : 0;
}

// GVN_SELCHANGING
void CInductionTabView::OnGridStartSelChange(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Start Selection Change on row %d, col %d (%d Selected)\n"), 
		pItem->iRow, pItem->iColumn, pMainFrame->m_GridInduction.GetSelectedCount());
}

// GVN_SELCHANGED
void CInductionTabView::OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("End Selection Change on row %d, col %d (%d Selected)\n"), 
		pItem->iRow, pItem->iColumn, pMainFrame->m_GridInduction.GetSelectedCount());
}

// GVN_BEGINDRAG
void CInductionTabView::OnGridBeginDrag(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Begin Drag row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}

void CInductionTabView::OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Double Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}

void CInductionTabView::OnGridClick(NMHDR *pNotifyStruct, LRESULT* /*pResult*/)
{
    NM_GRIDVIEW* pItem = (NM_GRIDVIEW*) pNotifyStruct;
    Trace(_T("Clicked on row %d, col %d\n"), pItem->iRow, pItem->iColumn);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


BOOL CInductionTabView::ScintillaNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult )
{
   NMHDR *phDR;
   phDR = (NMHDR*)lParam;
// does notification come from my scintilla window?
   if (phDR != NULL && phDR->hwndFrom == m_ScinCtrl.m_hWnd)
   {
      SCNotification *pMsg = (SCNotification*)lParam;
      switch (phDR->code)
      {
         case SCN_STYLENEEDED:
         break;
         case SCN_CHARADDED:
         break;
         case SCN_SAVEPOINTREACHED:
         break;
//       called when the document is changed - mark document modified
         case SCN_SAVEPOINTLEFT:
         break;
         case SCN_MODIFYATTEMPTRO:
         break;
         case SCN_KEY:
         break;
         case SCN_DOUBLECLICK:
         break;
//       called when something changes and we want to show new indicator state or brace matching
         case SCN_UPDATEUI:
         {
            m_ScinCtrl.UpdateUI();
         }
         break;
         case SCN_MODIFIED:
         break;
         case SCN_MACRORECORD:
         break;
//       user clicked margin - try folding action
         case SCN_MARGINCLICK:
         {
            m_ScinCtrl.DoDefaultFolding(pMsg->margin, pMsg->position);
         }
         break;
         case SCN_NEEDSHOWN:
         break;
         case SCN_PAINTED:
         break;
         case SCN_USERLISTSELECTION:
         break;
         case SCN_URIDROPPED:
         break;
         case SCN_DWELLSTART:
         break;
         case SCN_DWELLEND:
         break;
      }
      return TRUE; // we processed the message
   }
  
   return FALSE;
}



void CInductionTabView::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int nSelected = pNMListView->iItem;
	

	CString strItem = m_ListCtrl1.GetItemText(nSelected, 2);
	
	if ( pNMListView->uNewState & LVIS_SELECTED)
	{
		Stat_AtributeFrequency(nSelected, strItem);
		
	}
	
	*pResult = 0;	
	
	
	if ( m_blInited && LVIF_STATE == pNMListView->uChanged)
	{
		BOOL blAllChecked = TRUE;
		int nCount = m_ListCtrl1.GetItemCount();
		for(int nItem = 0; nItem < nCount; nItem++)
		{
			if ( !ListView_GetCheckState(GetSafeHwnd(), nItem) )
			{
				blAllChecked = FALSE;
				break;
			}
		}
		
		HDITEM hdItem;
		hdItem.mask = HDI_IMAGE;
		if (blAllChecked)
			hdItem.iImage = 2;
		else
			hdItem.iImage = 1;
		
		//CHeaderCtrl* pHeader = (CHeaderCtrl*) m_ListCtrl1.GetDlgItem(0);
		//VERIFY( pHeader->SetItem(0, &hdItem) );
		//VERIFY( m_checkHeadCtrl.SetItem(0, &hdItem) );
	}
	
}



void CInductionTabView::OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
		
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;
	int nSelected = pNMListView->iItem;
	CString strItem = m_ListCtrl2.GetItemText(nSelected, 0);
	

	if ( pNMListView->uNewState & LVIS_SELECTED)
		//MessageBox(strItem);
	
	*pResult;
	
}

void CInductionTabView::Stat_AtributeFrequency(int idAtribute, CString strType)
{
	
	//Delete columns and items of ListCtrl2
	m_ListCtrl2.DeleteAllItems();

	CHeaderCtrl* pHeader = (CHeaderCtrl*) m_ListCtrl2.GetDlgItem(0);
	int nColCount = pHeader->GetItemCount();
	
	for(int i = nColCount - 1; i >= 0; i--)
			m_ListCtrl2.DeleteColumn(i);
	
			
	if(strType == _T("Numeric"))
	{
		
			CreateNumericList2();
			//Stat_NumericFrequencySTL(idAtribute, INT_CONTINUE);
			Stat_NumericFrequency(idAtribute, INT_CONTINUE);
			
	}
	else
	{
			CreateNominalList2();
				
			Stat_NominalFreqMap(idAtribute);
			//Stat_NomFreqSTL(idAtribute);
			//Stat_NominalFrequency(idAtribute);
			//Stat_NominalFrequencySTL(idAtribute);
			
	}
	
	NSChart_DrawChart();

}


LPTSTR CInductionTabView::Conv_StrToLPTSTR(std::tstring str)
{
	LPCTSTR lpctStr = str.data();
	CString CStr = LPCTSTR(lpctStr);
	LPTSTR lptStr = CStr.GetBuffer(BUFF_SIZE); 
						
	return lptStr;
}


void CInductionTabView::StopTimer(CPerfTimer t, CString msg)
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


void CInductionTabView::Stat_NominalFreqMap(int idAtribute)
{
		
	tstring strAV;
	typedef std::map<tstring, int> m_AV_Freq;
	m_AV_Freq  mAVF;
	m_AV_Freq::iterator iter;

	
	int dfMaxRows = g_df.GetNumberOfSamples(idAtribute)-1;
	int missingData = 0;
		
	CPerfTimer T;
	T.Start(TRUE);
	
	//Insert the atribute values in a temporal vector
	for(int row = 0; row<dfMaxRows; row++)
	{
		int iLength = g_df.GetData(idAtribute, row, strAV);
		if(iLength == -1 )
		{
			MessageBox(g_df.GetLastError());
			return;
		}
			
		if( strAV == _T("") )
		{
			missingData++;
		}

		
			mAVF.insert(m_AV_Freq::value_type(_T("*** Missing Data"), missingData));
			
			int cont = 0;
			for(iter = mAVF.begin(); iter!= mAVF.end(); ++iter)
			{
				cont++;

				if(iter->first == strAV)
				{
					int freq = iter->second;
					iter->second = ++freq;
					
				}
				else
				{
					mAVF.insert(m_AV_Freq::value_type(strAV, 0));
					
				}
				if(cont > mAVF.size() )
					break;
			}
		
		
						
								
	}
	
	
	
	TCHAR szBuffer[16];
	CString szPerc;
	int j = 0;

	for(m_AV_Freq::const_iterator it = mAVF.begin(); it != mAVF.end(); ++it)
	{
		j++;

		CString szId = _T("L");
		szId += _itot(mAVF.size() -j, szBuffer, 10);
		LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
		LVITEM item = AddListItem2(0, 0, lptId, 0);
		szId.Empty();
				
								
		tstring strLabel = it->first;
		LPCTSTR lpctLabel = strLabel.data();
		CString szLabel = LPCTSTR(lpctLabel);
		LPTSTR lptLabel = szLabel.GetBuffer(BUFF_SIZE); 
		AddListSubItem2(item, 0, 1, lptLabel);
					
		
		CString szFreq = _itot(it->second, szBuffer, 10);
		LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
		AddListSubItem2(item, 0, 2, lptFreq);
						
		double dblPerc = (double)it->second*100/dfMaxRows;
		szPerc.Format(_T("%2.2f"), dblPerc);
		LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
		AddListSubItem2(item, 0, 3, lptPerc);
		
		
									
	}
					
	StopTimer(T, _T("Insert data in a temporal Vector... " ));


/*
	//Print map container
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( m_AV_Freq::const_iterator i = mAVF.begin(); i!= mAVF.end(); ++i)
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(i->first.data());
		CString str;
		str.Format(_T("Frequency.... %d  " ),i->second);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
	}

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("****************************************"));
*/

	
	
}


void CInductionTabView::Stat_NominalFrequency(int idAtribute)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	
	CString szAtributeLabel, szLabel, szFreq, szPerc, szId = _T("");
	std::tstring strLabel;
	std::vector<std::tstring> v_strDataLabel;
	std::vector<std::tstring> v_strLabel;

	int dfMaxRows = g_df.GetNumberOfSamples(idAtribute)-1;
	int missingData = 0;
		
	CPerfTimer T;
	T.Start(TRUE);
	//Insert the atribute values in a temporal vector
	for(int row = 0; row<dfMaxRows; row++)
	{
		int iLength = g_df.GetData(idAtribute, row, szAtributeLabel.GetBuffer(BUFF_SIZE));
		if(iLength == -1 )
		{
			MessageBox(g_df.GetLastError());
			return;
		}
			
		if( szAtributeLabel == _T("") )
		{
			missingData++;
			continue;
		}

		strLabel = (tstring)szAtributeLabel;
		v_strDataLabel.push_back(strLabel);
				
								
	}

	


	StopTimer(T, _T("Insert data in a temporal Vector... " ));
	
	T.Start(TRUE);
	//Sort the vector
	sort(v_strDataLabel.begin(), v_strDataLabel.end());
	
	StopTimer(T, _T("Sort the Vector... "));

	T.Start(TRUE);
	//Puts one copy of each atribute 
	unique_copy(v_strDataLabel.begin(), v_strDataLabel.end(), back_inserter(v_strLabel));
	
	StopTimer(T, _T("Get distinc Atributes...  "));		
			//reverse(v_strLabel.begin(), v_strLabel.end());
			//Get the size of the new vector
			int iListSize = v_strLabel.size();
			int vectorSize = v_strDataLabel.size();

			CString str;
			str.Format(_T("Prueba List Atributes : %d"), iListSize);
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			str.Format(_T("Prueba Vector Atributes : %d"), vectorSize);
			pMainFrame->m_wndOutputTabView.AddMsg1(str);

			
			TCHAR szBuffer[BUFF_SIZE];
			LVITEM item;
			int freq = 0;

	T.Start();
			for (int i = 0; i<iListSize; ++i) 
			{
				freq = 0;
				
				std::tstring strId;
				szId = _T("L");
				szId += _itot(iListSize - i, szBuffer, 10);
				LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
				item = AddListItem2(0, 0, lptId, 0);
				szId.Empty();
				
				
				strLabel = v_strLabel.at(i);
				LPCTSTR lpctLabel = strLabel.data();
				szLabel = LPCTSTR(lpctLabel);
				LPTSTR lptLabel = szLabel.GetBuffer(BUFF_SIZE); 
				AddListSubItem2(item, 0, 1, lptLabel);
								
				for(int j = 0; j<vectorSize; ++j)
				{
					std::tstring strTempLabel = v_strDataLabel.at(j);
					
					if( strLabel == strTempLabel)
					{
						freq++;
						szFreq = _itot(freq, szBuffer, 10);
						LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
						AddListSubItem2(item, 0, 2, lptFreq);
						
						double dblPerc = (double)freq*100/dfMaxRows;
						szPerc.Format(_T("%2.2f"), dblPerc);
						LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
						AddListSubItem2(item, 0, 3, lptPerc);
									
					}
					

				}
					
			}
			
	StopTimer(T, _T("Calc the Frequency..."));
	
	
	std::tstring strId;
			szId = _T("L");
			szId += _itot(0, szBuffer, 10);
			LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
			item = AddListItem2(0, 0, lptId, 0);
			szId.Empty();
				
			AddListSubItem2(item, 0, 1, _T("*** Missing Data"));
			
			szFreq = _itot(missingData, szBuffer, 10);
			LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
			AddListSubItem2(item, 0, 2, lptFreq);
						
			double dblPerc = (double)missingData*100/dfMaxRows;
			szPerc.Format(_T("%2.2f"), dblPerc);
			LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
			AddListSubItem2(item, 0, 3, lptPerc);
			
	szAtributeLabel.ReleaseBuffer();
	szId.ReleaseBuffer();
	szFreq.ReleaseBuffer();
	szLabel.ReleaseBuffer();
}


bool CInductionTabView::Stat_ClassesCondSTL(double dblValue)
{
	
	return (dblValue > 50);		
}





void CInductionTabView::Stat_NomFreqSTL(int idAtribute)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	
	CString szAtributeLabel, szLabel, szFreq, szPerc, szId = _T("");
	std::tstring strLabel;
	std::vector<std::tstring> v_strDataLabel;
	std::vector<std::tstring> v_strLabel;

	int dfMaxRows = g_df.GetNumberOfSamples(idAtribute)-1;
	
	
		
	CPerfTimer T;
	//T.Start(TRUE);
	//Insert the atribute values in a temporal vector
	int iLength = g_df.GetData(idAtribute, v_strDataLabel);
	if(iLength == -1 )
	{
		MessageBox(g_df.GetLastError());
		return;
	}
			
	
	//StopTimer(T, _T("Insert data in a Temporal Vector..."));		
	
	//T.Start(TRUE);
	//Sort the vector
	sort(v_strDataLabel.begin(), v_strDataLabel.end());
	//sort(v_strDataLabel.rbegin(), v_strDataLabel.rend());
	
	
	//StopTimer(T, _T("Sort the Vector..."));
	
	//T.Start(TRUE);
	//Puts one copy of each atribute 
	unique_copy(v_strDataLabel.begin(), v_strDataLabel.end(), back_inserter(v_strLabel));
	//Reverse order
	reverse(v_strLabel.begin(), v_strLabel.end()); 
	
	//StopTimer(T, _T("Makes a copy of distinct Atributes in another Vector... "));
	//reverse(v_strLabel.begin(), v_strLabel.end());
		//Get the size of the new vector
			int iListSize = v_strLabel.size();
			
			/*
			CString str;
			str.Format(_T("Prueba List Atributes : %d"), iListSize);
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			str.Format(_T("Prueba Vector Atributes : %d"), iLength);
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
		*/

			
			TCHAR szBuffer[BUFF_SIZE];
			LVITEM item;
			int freq = 0;

	T.Start();
			for (int i = 0; i<iListSize; ++i) 
			{
				freq = 0;
				
				
				szId = _T("L");
				szId += _itot(iListSize - i, szBuffer, 10);
				LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
				item = AddListItem2(0, 0, lptId, 0);
				szId.Empty();
				
								
				strLabel = v_strLabel.at(i);
				LPCTSTR lpctLabel = strLabel.data();
				szLabel = LPCTSTR(lpctLabel);
				LPTSTR lptLabel = szLabel.GetBuffer(BUFF_SIZE); 
				
				//Check for missing data
				if(szLabel==_T(""))
				{
					AddListSubItem2(item, 0, 1, _T("*** Missing Data"));
					freq = count(v_strDataLabel.begin(), v_strDataLabel.end(), strLabel);
					--freq;
				}
				else
				{
					AddListSubItem2(item, 0, 1, lptLabel);
					freq = count(v_strDataLabel.begin(), v_strDataLabel.end(), strLabel);
				}
				
				szFreq = _itot(freq, szBuffer, 10);
				LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 2, lptFreq);
						
				double dblPerc = (double)freq*100/dfMaxRows;
				szPerc.Format(_T("%2.2f"), dblPerc);
				LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 3, lptPerc);
									
						
			}
			
	StopTimer(T, _T("Calc the Frequency..."));
	
	
	        /*
			szId = _T("L");
			szId += _itot(0, szBuffer, 10);
			LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
			item = AddListItem2(0, 0, lptId, 0);
			szId.Empty();
				
			AddListSubItem2(item, 0, 1, _T("*** Missing Data"));
			
			szFreq = _itot(freq, szBuffer, 10);
			LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
			AddListSubItem2(item, 0, 2, lptFreq);
						
			double dblPerc = (double)freq*100/dfMaxRows;
			szPerc.Format(_T("%2.2f"), dblPerc);
			LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
			AddListSubItem2(item, 0, 3, lptPerc);
			*/
			
	szAtributeLabel.ReleaseBuffer();
	szId.ReleaseBuffer();
	szFreq.ReleaseBuffer();
	szLabel.ReleaseBuffer();
}

void CInductionTabView::Stat_NominalFrequencySTL(int idAtribute)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	
	CString szAtributeLabel, szLabel, szFreq, szPerc, szId = _T("");
	std::tstring strLabel;
	std::vector<std::tstring> v_strDataLabel;
	std::vector<std::tstring> v_strLabel;

	int dfMaxRows = g_df.GetNumberOfSamples(idAtribute)-1;
	int missingData = 0;
		
	CPerfTimer T;
	T.Start(TRUE);
	//Insert the atribute values in a temporal vector
	for(int row = 0; row<dfMaxRows; row++)
	{
		int iLength = g_df.GetData(idAtribute, row, szAtributeLabel.GetBuffer(BUFF_SIZE));
		if(iLength == -1 )
		{
			MessageBox(g_df.GetLastError());
			return;
		}
			
		if( szAtributeLabel == _T("") )
		{
			missingData++;
			continue;
		}

		strLabel = (tstring)szAtributeLabel;
		v_strDataLabel.push_back(strLabel);
				
								
	}
	StopTimer(T, _T("Insert data in a Temporal Vector..."));		
	
	T.Start(TRUE);
	//Sort the vector
	sort(v_strDataLabel.begin(), v_strDataLabel.end());
	
	StopTimer(T, _T("Sort the Vector..."));
	
	T.Start(TRUE);
	//Puts one copy of each atribute 
	unique_copy(v_strDataLabel.begin(), v_strDataLabel.end(), back_inserter(v_strLabel));
	
	StopTimer(T, _T("Makes a copy of distinct Atributes in another Vector... "));
	//reverse(v_strLabel.begin(), v_strLabel.end());
		//Get the size of the new vector
			int iListSize = v_strLabel.size();
			int vectorSize = v_strDataLabel.size();

			CString str;
			str.Format(_T("Prueba List Atributes : %d"), iListSize);
			pMainFrame->m_wndOutputTabView.AddMsg1(str);
			str.Format(_T("Prueba Vector Atributes : %d"), vectorSize);
			pMainFrame->m_wndOutputTabView.AddMsg1(str);

			
			TCHAR szBuffer[BUFF_SIZE];
			LVITEM item;
			int freq = 0;

	T.Start();
			for (int i = 0; i<iListSize; ++i) 
			{
				freq = 0;
				
				std::tstring strId;
				szId = _T("L");
				szId += _itot(iListSize - i, szBuffer, 10);
				LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
				item = AddListItem2(0, 0, lptId, 0);
				szId.Empty();
				
				
				strLabel = v_strLabel.at(i);
				LPCTSTR lpctLabel = strLabel.data();
				szLabel = LPCTSTR(lpctLabel);
				LPTSTR lptLabel = szLabel.GetBuffer(BUFF_SIZE); 
				AddListSubItem2(item, 0, 1, lptLabel);
								
				freq = count(v_strDataLabel.begin(), v_strDataLabel.end(), strLabel);
				
				szFreq = _itot(freq, szBuffer, 10);
				LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 2, lptFreq);
						
				double dblPerc = (double)freq*100/dfMaxRows;
				szPerc.Format(_T("%2.2f"), dblPerc);
				LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 3, lptPerc);
									
						
			}
			
	StopTimer(T, _T("Calc the Frequency..."));
	
	
	std::tstring strId;
			szId = _T("L");
			szId += _itot(0, szBuffer, 10);
			LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
			item = AddListItem2(0, 0, lptId, 0);
			szId.Empty();
				
			AddListSubItem2(item, 0, 1, _T("*** Missing Data"));
			
			szFreq = _itot(missingData, szBuffer, 10);
			LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
			AddListSubItem2(item, 0, 2, lptFreq);
						
			double dblPerc = (double)missingData*100/dfMaxRows;
			szPerc.Format(_T("%2.2f"), dblPerc);
			LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
			AddListSubItem2(item, 0, 3, lptPerc);
			
	szAtributeLabel.ReleaseBuffer();
	szId.ReleaseBuffer();
	szFreq.ReleaseBuffer();
	szLabel.ReleaseBuffer();
}

void CInductionTabView::Stat_NominalFrequencyDesc(int idAtribute)
{
		
	CString szAtributeLabel, szLabel, szFreq, szPerc, szId = _T("");
	std::tstring strLabel;
	std::vector<std::tstring> v_strDataLabel;
	std::vector<std::tstring> v_strLabel;

	int dfMaxRows = g_df.GetNumberOfSamples(idAtribute)-1;
	int missingData = 0;
	
	//Insert the atribute values in a temporal vector
	for(int row = 0; row<dfMaxRows; row++)
	{
		int iLength = g_df.GetData(idAtribute, row, szAtributeLabel.GetBuffer(BUFF_SIZE));
		if(iLength == -1 )
		{
			MessageBox(g_df.GetLastError());
			return;
		}
				
		if( szAtributeLabel == _T("") )
		{
			missingData++;
			continue;
		}
		strLabel = (tstring)szAtributeLabel;
		v_strDataLabel.push_back(strLabel);
				
								
	}

					
			//Sort the vector
			sort(v_strDataLabel.begin(), v_strDataLabel.end());

			
			//Puts one copy of each atribute 
			unique_copy(v_strDataLabel.begin(), v_strDataLabel.end(), back_inserter(v_strLabel));
			//MessageBox(_T("Tiempo"));
			//reverse(v_strLabel.begin(), v_strLabel.end());
			//Get the size of the new vector
			int iListSize = v_strLabel.size();
			int vectorSize = v_strDataLabel.size();
			
			TCHAR szBuffer[BUFF_SIZE];
			LVITEM item;
			int freq = 0;
			
			
			for (int i = iListSize-1; i>=0; i--) 
			{
				freq = 0;
				
				std::tstring strId;
				szId = _T("L");
				szId += _itot(i+1, szBuffer, 10);
				LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
				item = AddListItem2(0, 0, lptId, 0);
				szId.Empty();
				
				
				strLabel = v_strLabel.at(i);
				LPCTSTR lpctLabel = strLabel.data();
				szLabel = LPCTSTR(lpctLabel);
				LPTSTR lptLabel = szLabel.GetBuffer(BUFF_SIZE); 
				AddListSubItem2(item, 0, 1, lptLabel);

				
				
				for(int j = vectorSize-1; j>=0; j--)
				{
					std::tstring strTempLabel = v_strDataLabel.at(j);
					
					if( strLabel == strTempLabel)
					{
						freq++;
						szFreq = _itot(freq, szBuffer, 10);
						LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
						AddListSubItem2(item, 0, 2, lptFreq);
						
						double dblPerc = (double)freq*100/dfMaxRows;
						szPerc.Format(_T("%2.2f"), dblPerc);
						LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
						AddListSubItem2(item, 0, 3, lptPerc);
									
					}
					

				}
					
			}
			
			std::tstring strId;
			szId = _T("L");
			szId += _itot(0, szBuffer, 10);
			LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
			item = AddListItem2(0, 0, lptId, 0);
			szId.Empty();
				
			AddListSubItem2(item, 0, 1, _T("*** Missing Data"));
			
			szFreq = _itot(missingData, szBuffer, 10);
			LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
			AddListSubItem2(item, 0, 2, lptFreq);
						
			double dblPerc = (double)missingData*100/dfMaxRows;
			szPerc.Format(_T("%2.2f"), dblPerc);
			LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
			AddListSubItem2(item, 0, 3, lptPerc);
						
	
			
	szAtributeLabel.ReleaseBuffer();
	szId.ReleaseBuffer();
	szFreq.ReleaseBuffer();
	szLabel.ReleaseBuffer();
}

void CInductionTabView::Stat_NumericFrequency(int idAtribute, int type)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	
	
	CString szAtributeLabel, szLabel, szFreq, szPerc, szId = _T("");
	std::vector<double> v_dblDataLabel;
		
	int dfMaxRows = g_df.GetNumberOfSamples(idAtribute)-1;
	int missingData = 0;	
	
	CPerfTimer T;
	T.Start();
	//Insert the atribute values in a temporal vector
	for(int row = 0; row<dfMaxRows; row++)
	{
		int iLength = g_df.GetData(idAtribute, row, szAtributeLabel.GetBuffer(BUFF_SIZE));
		if(iLength == -1 )
		{
			MessageBox(g_df.GetLastError());
			return;
		}
				
		if( szAtributeLabel == _T("") )
		{
			missingData++;
			continue;
		}

		double dblLabel = _tcstod(szAtributeLabel, NULL);
		v_dblDataLabel.push_back(dblLabel);
		
	}
	
	StopTimer(T, _T("Insert Numerical data in a Vector... ")); 	
	
		int vectorSize = v_dblDataLabel.size();
		//Sort the vector
	T.Start();
		sort(v_dblDataLabel.begin(), v_dblDataLabel.end());
	
	StopTimer(T, _T("Sort the Vector... "));
	
		float Func = 1 + 3.322*log10f(dfMaxRows);
		float ClassInt = 0;
		const double Min = v_dblDataLabel.at(0);
		const double Max = v_dblDataLabel.at(vectorSize - 1);

		if( Func > Max )
			nClasses = floor(1 + Max);
		else
			nClasses = floor(Func);

		
		if( nClasses > 20 )
			nClasses = 20;
		if ( nClasses < 5 )
			nClasses = 5;
	
		
		
		switch(type)
		{
		case INT_DISCRETE:		
			ClassInt = ceil((Max- Min)/nClasses);
			break;
			
		case INT_CONTINUE :
			ClassInt = (Max- Min)/nClasses + 0.000001;
			break;
		}	
		
		TCHAR szBuffer[BUFF_SIZE];
		LVITEM item;
		int freq = 0;
		CString	szTempMin = _T("0.00");	
		CString szTempMax = _T("0.00");

		double TempMin = Min;
		double TempMax = Min + ClassInt;
				
	T.Start();	
		for(int i = 0; i<nClasses; i++)
		{
				freq = 0;	
			
				std::tstring strId;
				szId = _T("C");
				szId += _itot(nClasses - i, szBuffer, 10);
				LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
				item = AddListItem2(0, 0, lptId, 0);
				szId.Empty();
				
				
				szTempMin.Format(_T("%.2f"), TempMin);
				szTempMax.Format(_T("%.2f"), TempMax);
				LPTSTR lptTempMin = szTempMin.GetBuffer(BUFF_SIZE);
				LPTSTR lptTempMax = szTempMax.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 1, lptTempMin);
				AddListSubItem2(item, 0, 2, lptTempMax);
				
				
				szFreq = _itot(freq, szBuffer, 10);
				LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 3, lptFreq);
				
				float dblPerc = (float)freq*100/dfMaxRows;
				szPerc.Format(_T("%2.2f"), dblPerc);
				LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 4, lptPerc);
						

				
				for(int row = 0; row<vectorSize; row++)
				{
					double dblValue = v_dblDataLabel.at(row);
					
					
					if( dblValue == Max && TempMax == Max && i== nClasses-1)
					{
						szFreq = _itot( freq, szBuffer, 10);
						//MessageBox(szFreq);
						
						freq++;
						szFreq = _itot(freq, szBuffer, 10);
						LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
						AddListSubItem2(item, 0, 3, lptFreq);
						
						float dblPerc = (float)freq*100/dfMaxRows;
						szPerc.Format(_T("%2.2f"), dblPerc);
						LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
						AddListSubItem2(item, 0, 4, lptPerc);
						continue;
						
						szFreq = _itot( i, szBuffer, 10);
						//MessageBox(szFreq);
						
					}
					
					if( (dblValue >= TempMin  &&  dblValue < TempMax))
					{
						freq++;
						szFreq = _itot(freq, szBuffer, 10);
						LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
						AddListSubItem2(item, 0, 3, lptFreq);
						
						float dblPerc = (float)freq*100/dfMaxRows;
						szPerc.Format(_T("%2.2f"), dblPerc);
						LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
						AddListSubItem2(item, 0, 4, lptPerc);

										
					}
					
				
				}
				
				
				TempMin = TempMax;
				TempMax = TempMin + ClassInt;
				
	
		}

	StopTimer(T, _T("Calc Frequency Distribution... "));


				szId = _T("C");
				szId += _itot(0, szBuffer, 10);
				LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
				item = AddListItem2(0, 0, lptId, 0);
				szId.Empty();
				
				AddListSubItem2(item, 0, 1, _T("***Missing"));
				AddListSubItem2(item, 0, 2, _T("Data"));
				
				
				szFreq = _itot(missingData, szBuffer, 10);
				LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 3, lptFreq);
				
				float dblPerc = (float)missingData*100/dfMaxRows;
				szPerc.Format(_T("%2.2f"), dblPerc);
				LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 4, lptPerc);


			
}

void CInductionTabView::Stat_NumericFrequencySTL(int idAtribute, int type)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	
	
	CString szAtributeLabel, szLabel, szFreq, szPerc, szId = _T("");
	std::vector<double> v_dblDataLabel;
		
	int dfMaxRows = g_df.GetNumberOfSamples(idAtribute)-1;
	int missingData = 0;	
	
	CPerfTimer T;
	T.Start();
	//Insert the atribute values in a temporal vector
	for(int row = 0; row<dfMaxRows; row++)
	{
		int iLength = g_df.GetData(idAtribute, row, szAtributeLabel.GetBuffer(BUFF_SIZE));
		if(iLength == -1 )
		{
			MessageBox(g_df.GetLastError());
			return;
		}
				
		if( szAtributeLabel == _T("") )
		{
			missingData++;
			continue;
		}

		double dblLabel = _tcstod(szAtributeLabel, NULL);
		v_dblDataLabel.push_back(dblLabel);
		
	}
	
	StopTimer(T, _T("Insert Numerical data in a Vector... "));	
	
		int vectorSize = v_dblDataLabel.size();
		//Sort the vector
	T.Start();
		sort(v_dblDataLabel.begin(), v_dblDataLabel.end());
	
	StopTimer(T, _T("Sort the Vector... "));			
	
	float Func = 1 + 3.322*log10f(dfMaxRows);
	float ClassInt = 0;
	const double Min = v_dblDataLabel.at(0);
	const double Max = v_dblDataLabel.at(vectorSize - 1);

		if( Func > Max )
			nClasses = floor(1 + Max);
		else
			nClasses = floor(Func);

		
		if( nClasses > 20 )
			nClasses = 20;
		if ( nClasses < 5 )
			nClasses = 5;
	
		
		
		switch(type)
		{
		case INT_DISCRETE:		
			ClassInt = ceil((Max- Min)/nClasses);
			break;
			
		case INT_CONTINUE :
			ClassInt = (Max- Min)/nClasses + 0.000001;
			break;
		}	
		
		TCHAR szBuffer[BUFF_SIZE];
		LVITEM item;
		int freq = 0;
		CString	szTempMin = _T("0.00");	
		CString szTempMax = _T("0.00");

		double TempMin = Min;
		double TempMax = Min + ClassInt;
		
				
	T.Start();	
		for(int i = 0; i<nClasses; i++)
		{
				freq = 0;	
			
				std::tstring strId;
				szId = _T("C");
				szId += _itot(nClasses - i, szBuffer, 10);
				LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
				item = AddListItem2(0, 0, lptId, 0);
				szId.Empty();
				
				
				szTempMin.Format(_T("%.2f"), TempMin);
				szTempMax.Format(_T("%.2f"), TempMax);
				LPTSTR lptTempMin = szTempMin.GetBuffer(BUFF_SIZE);
				LPTSTR lptTempMax = szTempMax.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 1, lptTempMin);
				AddListSubItem2(item, 0, 2, lptTempMax);
			
			
				double dblValue = v_dblDataLabel.at(i);
			
				int freq1 = count_if(v_dblDataLabel.begin(), v_dblDataLabel.end(),bind2nd(greater_equal<double>(), TempMin ));
				int freq2 = count_if(v_dblDataLabel.begin(), v_dblDataLabel.end(),bind2nd(greater<double>(), TempMax ));
					
				freq = abs(freq1 - freq2);
				
				szFreq = _itot(freq, szBuffer, 10);
				LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 3, lptFreq);
						
				float dblPerc = (float)freq*100/dfMaxRows;
				szPerc.Format(_T("%2.2f"), dblPerc);
				LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 4, lptPerc);
				
				TempMin = TempMax;
				TempMax = TempMin + ClassInt;
				
	
		}

	StopTimer(T, _T("Calc Distribution Frequency... "));
				szId = _T("C");
				szId += _itot(0, szBuffer, 10);
				LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
				item = AddListItem2(0, 0, lptId, 0);
				szId.Empty();
				
				AddListSubItem2(item, 0, 1, _T("***Missing"));
				AddListSubItem2(item, 0, 2, _T("Data"));
				
				
				szFreq = _itot(missingData, szBuffer, 10);
				LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 3, lptFreq);
				
				float dblPerc = (float)missingData*100/dfMaxRows;
				szPerc.Format(_T("%2.2f"), dblPerc);
				LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 4, lptPerc);


			
}

void CInductionTabView::Stat_NumericFrequencyDesc(int idAtribute, int type)
{
		
	CString szAtributeLabel, szLabel, szFreq, szPerc, szId = _T("");
	std::vector<double> v_dblDataLabel;
		
	int dfMaxRows = g_df.GetNumberOfSamples(idAtribute)-1;
	int missingData = 0;	
	
	//Insert the atribute values in a temporal vector
	for(int row = 0; row<dfMaxRows; row++)
	{
		int iLength = g_df.GetData(idAtribute, row, szAtributeLabel.GetBuffer(BUFF_SIZE));
		if(iLength == -1 )
		{
			MessageBox(g_df.GetLastError());
			return;
		}
				
		if( szAtributeLabel == _T("") )
		{
			missingData++;
			continue;
		}

		double dblLabel = _tcstod(szAtributeLabel, NULL);
		v_dblDataLabel.push_back(dblLabel);
		
	}
	
		
		int vectorSize = v_dblDataLabel.size();
		//Sort the vector
		sort(v_dblDataLabel.begin(), v_dblDataLabel.end());
		
		//reverse(v_dblDataLabel.begin(), v_dblDataLabel.end());

		
		float Func = 1 + 3.322*log10f(dfMaxRows);
		float ClassInt = 0;
		const double Min = v_dblDataLabel.at(0);
		const double Max = v_dblDataLabel.at(vectorSize - 1);

		if( Func > Max )
			nClasses = floor(1 + Max);
		else
			nClasses = floor(Func);

		
		if( nClasses > 20 )
			nClasses = 20;
		if ( nClasses < 5 )
			nClasses = 5;
	
		
		//MessageBox(_T("hola"));
		switch(type)
		{
		case INT_DISCRETE:		
			ClassInt = ceil(abs(Max- Min)/nClasses);
			break;
			
		case INT_CONTINUE :
			ClassInt = (Max - Min)/nClasses;
			break;
		}	
		
		TCHAR szBuffer[BUFF_SIZE];
		LVITEM item;
		int freq = 0;
		CString	szTempMin = _T("0.00");	
		CString szTempMax = _T("0.00");

		double TempMin = Max - ClassInt;
		double TempMax = Max;
				
		
		for(int i = nClasses-1; i>= 0; i--)
		{
				freq = 0;	
			
				std::tstring strId;
				szId = _T("C");
				szId += _itot(i+1, szBuffer, 10);
				LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
				item = AddListItem2(0, 0, lptId, 0);
				szId.Empty();
				
				
				szTempMin.Format(_T("%.2f"), TempMin);
				szTempMax.Format(_T("%.2f"), TempMax);
				LPTSTR lptTempMin = szTempMin.GetBuffer(BUFF_SIZE);
				LPTSTR lptTempMax = szTempMax.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 1, lptTempMin);
				AddListSubItem2(item, 0, 2, lptTempMax);
				
				
				szFreq = _itot(freq, szBuffer, 10);
				LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 3, lptFreq);
				
				float dblPerc = (float)freq*100/dfMaxRows;
				szPerc.Format(_T("%2.2f"), dblPerc);
				LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 4, lptPerc);
						

				
				for(int row = vectorSize-1; row >=0; row--)
				{
					double dblValue = v_dblDataLabel.at(row);
					
					
					if( dblValue == Max && TempMax == Max && i== nClasses-1)
					{
						//szFreq = _itot( freq, szBuffer, 10);
						//MessageBox(szFreq);
						
						freq++;
						szFreq = _itot(freq, szBuffer, 10);
						LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
						AddListSubItem2(item, 0, 3, lptFreq);
						
						float dblPerc = (float)freq*100/dfMaxRows;
						szPerc.Format(_T("%2.2f"), dblPerc);
						LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
						AddListSubItem2(item, 0, 4, lptPerc);
						continue;
						
						//szFreq = _itot( i, szBuffer, 10);
						//MessageBox(szFreq);
						
					}
					
					if( (dblValue >= TempMin  &&  dblValue < TempMax))
					{
						freq++;
						szFreq = _itot(freq, szBuffer, 10);
						LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
						AddListSubItem2(item, 0, 3, lptFreq);
						
						float dblPerc = (float)freq*100/dfMaxRows;
						szPerc.Format(_T("%2.2f"), dblPerc);
						LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
						AddListSubItem2(item, 0, 4, lptPerc);

										
					}
					
				
				}
				
				TempMax = TempMin;
				TempMin = TempMax - ClassInt;
				
				
	
		}

				szId = _T("C");
				szId += _itot(0, szBuffer, 10);
				LPTSTR lptId = szId.GetBuffer(BUFF_SIZE);
				item = AddListItem2(0, 0, lptId, 0);
				szId.Empty();
				
				AddListSubItem2(item, 0, 1, _T("***Missing"));
				AddListSubItem2(item, 0, 2, _T("Data"));
				
				
				szFreq = _itot(missingData, szBuffer, 10);
				LPTSTR lptFreq = szFreq.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 3, lptFreq);
				
				float dblPerc = (float)missingData*100/dfMaxRows;
				szPerc.Format(_T("%2.2f"), dblPerc);
				LPTSTR lptPerc = szPerc.GetBuffer(BUFF_SIZE);
				AddListSubItem2(item, 0, 4, lptPerc);


			
}


void CInductionTabView::NSChart_DrawChart()
{
	m_Chart.ResetChart();
	for(int i = 0; i< m_ListCtrl2.GetItemCount(); ++i)
	{
		CString szFreq = m_ListCtrl2.GetItemText( i, 2 );
		double dblFreq = _tcstod(szFreq, NULL);
        CString szLabel = m_ListCtrl2.GetItemText(i, 0);
		m_Chart.AddValue(dblFreq, szLabel);

	}

	//UpdateDialogControls(this,FALSE);
	m_Chart.Invalidate(FALSE);
}


void CInductionTabView::NSChart_OnChartSelectedItem(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCHARTCTRL nmchart = (LPNMCHARTCTRL)pNMHDR;
	
	int m_iItem = nmchart->iItem;
	double dValue = 0;
	CString sLabel = _T("");
	
	if(m_iItem >= 0)
	{
		dValue = nmchart->dValue;
		CString str;
		str.Format( _T("\t\tFrequency:  %0.0f"), dValue);
	
		sLabel = nmchart->sLabel;
		sLabel = NSChart_GetAtributeValueName(sLabel);
		
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		if ( pMainFrame->m_wndOutputTabView.IsVisible())
		{
			pMainFrame->m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(0);
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("Atribute value: ") + sLabel + str);
		}

	}else
	{
		dValue = 0;
		sLabel = _T("");
	}
	
	
	
	*pResult = FALSE;

}

CString CInductionTabView::NSChart_GetAtributeValueName(CString label)
{
	LVFINDINFO pFindInfo;
	pFindInfo.flags = LVFI_PARTIAL|LVFI_STRING;
	pFindInfo.psz = label;
	
	
	int pos = m_ListCtrl2.FindItem(&pFindInfo, -1);
	if( pos == -1)
	{
		AfxMessageBox(_T("ERROR: The atribute value was not found."));
	}
	else
	{
		CString szAV = m_ListCtrl2.GetItemText(pos, 1);
		//AfxMessageBox(szAV);
		return szAV;
	}
	
	return _T("NOT_FOUND"); 
	
}



void CInductionTabView::ChangeInterfacesPage1()
{
	//m_LayoutManager.SetMinMax(IDC_INDUCTIONTAB, CSize(0,0), CSize(40,40));

	if (BST_CHECKED == m_checkGraph.GetCheck() && BST_CHECKED == m_checkValues.GetCheck() )
	{
		Init_Atributes_AtributeValues_Graph_Page1();
		m_Chart.Invalidate();
	}
	else if(BST_CHECKED != m_checkGraph.GetCheck() && BST_CHECKED == m_checkValues.GetCheck())
	{
		Init_Atributes_AtributeValues_Page1();
		m_Chart.Invalidate();
	}
	else if(BST_CHECKED == m_checkGraph.GetCheck() && BST_CHECKED != m_checkValues.GetCheck())
	{
		Init_Atributes_Graph_Page1();
		m_Chart.Invalidate();
	}
	else if (BST_CHECKED != m_checkGraph.GetCheck() && BST_CHECKED != m_checkValues.GetCheck()) 
	{
		Init_Atributes_Page1();
	}
	else
	{
		AfxMessageBox(_T("ERROR: No se dió ningun caso"));
	}

}

void CInductionTabView::ChangeVTablesSize(int pos)
{
		
	if( m_eIntPage2 == VTABLES_DATA)
	{
				
	
		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);

	
		m_LayoutManager.SetMinMax(IDC_INDUCTION_SPIN, CSize(50,0), CSize(0,0));
		
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_TABLES);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 40);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);
		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 0);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_TOP, OX_LMT_SAME, 40);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_POSITION, pos);

		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_TABLES);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_POSITION, pos);

						
		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_SPIN);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_POSITION, pos);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_TOP, OX_LMT_SAME, 40);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_TREECTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_POSITION, 100);
		
		

		//GridCtrl
		m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_DATA);
		m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_TREECTRL);
		//m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_POSITION, 100);
		m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);

	
		
		m_LayoutManager.RedrawLayout();
	}

	if( m_eIntPage2 ==  QUERY_VTABLES_DATA )
	{

		m_LayoutManager.Detach();
		m_LayoutManager.Attach(this);

		
		m_LayoutManager.SetMinMax(IDC_INDUCTION_TREECTRL, CSize(50,0), CSize(0,0));
		

		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_LEFT,  OX_LMT_SAME, 5);
		m_LayoutManager.SetConstraint(IDC_INDUCTIONTAB, OX_LMS_RIGHT, OX_LMT_SAME, -5);

		//RollupCtrl
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_TOP, OX_LMT_SAME, 40);
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5 );
		m_LayoutManager.SetConstraint(IDC_ROLLUPCTRL, OX_LMS_LEFT, OX_LMT_SAME, 5);


		
		//Constrain Static Control
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_TOP, OX_LMT_SAME, 40 );
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_QUERY, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		
		
		//Constrain Edit Control
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_QUERY);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_BOTTOM, OX_LMT_POSITION, 30);
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL );
		m_LayoutManager.SetConstraint(IDC_SCINCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_SCINCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_TABLES, OX_LMS_RIGHT, OX_LMT_POSITION, pos);

		
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_TABLES);
		//m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_SPIN, OX_LMS_RIGHT, OX_LMT_POSITION, pos);

		
				
		//Constrain TreeCtrl
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_SPIN);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_ROLLUPCTRL);
		m_LayoutManager.SetConstraint(IDC_INDUCTION_TREECTRL, OX_LMS_RIGHT, OX_LMT_POSITION, pos);

		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_SCINCTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_TREECTRL);
		m_LayoutManager.SetConstraint(IDC_STATIC_DATA, OX_LMS_RIGHT, OX_LMT_POSITION, 100);
		
		

		//GridCtrl
		m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_TOP, OX_LMT_OPPOSITE, 5, IDC_STATIC_DATA);
		m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_BOTTOM, OX_LMT_SAME, -5);
		m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_INDUCTION_TREECTRL);
		//m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_POSITION, 100);
		m_LayoutManager.SetConstraint(IDC_GRID, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
	
		
		m_LayoutManager.RedrawLayout();
	}




}


void CInductionTabView::OnInductionCheckGraph() 
{
	ChangeInterfacesPage1();

}

void CInductionTabView::OnInductionCheckValues() 
{
	ChangeInterfacesPage1();	

}



void CInductionTabView::InitScintilla()
{
  
   m_ScinCtrl.Init();
   m_ScinCtrl.SetDisplayLinenumbers(TRUE);
   m_ScinCtrl.SetDisplayFolding(TRUE);
   //m_ScinCtrl.SetLexer(SCLEX_CPP);
   m_ScinCtrl.SetLexer(SCLEX_AIPI);
   //m_ScinCtrl.SendMessage(SCI_SETKEYWORDS, 0, (long)_T("SELECT FROM INSERT TABLE UPDATE"));
   //m_ScinCtrl.SetText(_T("int i=0;\nwhile(i<10)\n{\ni++;\n}\n"));
	//SetText(_T("int i=0;\nwhile(i<10)\n{\ni++;\n}\n"));
}









































///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// DATABASE FUNCTIONS //////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CInductionTabView::RunQuery() 
{
	CWaitCursor wait;
	TCHAR *c = m_strQuery.GetBuffer(m_strQuery.GetLength()*4);
	m_strQuery.ReleaseBuffer();

	m_ScinCtrl.GetText(m_strQuery.GetLength()*4, c);
	
	m_query.Empty(); // Clean old query sentence
	m_query << m_strQuery;
	if(!m_query.ExecuteSQL())		
		return;
	OnUpdate(NULL,HINT_ON_QUERY_RESULT_READY, NULL);

	UnCheckListCtrl1();
	
}


void CInductionTabView::OnUpdateRunQuery(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_strQuery.IsEmpty());
}



void CInductionTabView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch (lHint)
	{
	default:
		break;
	case HINT_UPDATE_WINDOW:    // redraw entire window
		Invalidate(FALSE);
		break;
	case HINT_ON_QUERY_RESULT_READY:
		{
			ShowQueryResult();
			UpdateData(FALSE);
		}
	case HINT_ON_NODE_SELECTED:
		{
			//ShowColumns();
			UpdateData(FALSE);
		}
		break;
	}
}


void CInductionTabView::OnSelectTreeNode(CInductionTabView::TreeNodeTypeDB node, const CString strText)
{
	m_hSelNodeType = node;
	m_strSelNodeName = strText;
	switch(m_hSelNodeType)
	{
	default:
		ASSERT(0);
		break;
	case TNode_None:
	case TNode_RootDatabase:
	case TNode_RootTables:
		m_strQuery = _T("");
		m_ScinCtrl.SetText(m_strQuery);
		break;
	case TNode_TableName:
		m_strQuery = _T(" SELECT TOP 100 * FROM [" + m_strSelNodeName + "]");
		m_ScinCtrl.SetText(m_strQuery);
		RunQuery();
		break;
	};
	
	OnUpdate(NULL,HINT_ON_NODE_SELECTED, NULL);
	UnCheckListCtrl1();
}


void CInductionTabView::UnCheckListCtrl1()
{
	HDITEM hdItem;
	hdItem.mask = HDI_IMAGE | HDI_FORMAT;
	VERIFY( m_ListCtrl1.m_checkHeadCtrl.GetItem(0, &hdItem) );
	hdItem.iImage = 1;
	hdItem.fmt |= HDF_IMAGE;
	VERIFY( m_ListCtrl1.m_checkHeadCtrl.SetItem(0, &hdItem) );
}


void CInductionTabView::ShowColumns() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CSQLQuery& query = m_query;
	int dfMaxCols = query.GetColumnsCount();
				
	
	int MaxCols = dfMaxCols;
	int MaxRows = 2;
	int MaxFixCols = 1;
	int MaxFixRows = 2;
	


	UpdateData(false);
	
	TRY 
	{
		    pMainFrame->m_GridInduction.SetRowCount(2);
		    pMainFrame->m_GridInduction.SetColumnCount(MaxCols+1);
		    pMainFrame->m_GridInduction.SetFixedRowCount(MaxFixRows);
		    pMainFrame->m_GridInduction.SetFixedColumnCount(MaxFixCols);
	}
	CATCH (CMemoryException, e)
	{
	    	
	e->ReportError();
    return;
	}
    END_CATCH


	CString str, szColName;
	
	//Populate grid control columns
	for (int col = 0; col <= MaxCols; ++col)
    {
		//Fill ListCtrl1 with header name
		if( col < dfMaxCols )
		{
			szColName = query.GetColumnName(col);
			pMainFrame->m_GridInduction.SetItemText(m_nFixCols, col+1, szColName);
						
		}
		
		//Set Column Number
		str.Format(_T("Column %d"),col);
		pMainFrame->m_GridInduction.SetItemText(0, col, str);
		
			
		if(col == 0)
		{
			int row = 1;
			str.Format(_T("Row %d"), row);
			pMainFrame->m_GridInduction.SetItemText(row, col, str);
		}
			

	}
	
		
}


void CInductionTabView::ShowQueryResult() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	LockWindowUpdate();

	g_df.SetReadFlags(DF::RF_READ_AS_STRING);
	
	
	// Clear Grid control
	CAipi_DT_ID3 dt;
	dt.ClearAll();
		
	//Delete previous data
	m_ListCtrl1.DeleteAllItems();
	m_ListCtrl2.DeleteAllItems();
	pMainFrame->m_GridInduction.DeleteAllItems();
	
	g_df.ClearData();
	

	QueryFixed();		

	
	UnlockWindowUpdate();

  
}

void CInductionTabView::QueryUnFixed()
{
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	//pMainFrame->m_wndStatusBar.SetPaneInfo( 1, nID, nStyle, 100);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	
	
	CSQLQuery& query = m_query;

	int dfMaxCols = query.GetColumnsCount();
	int dfMaxRows = query.GetDataCount()/dfMaxCols;

			
	if( dfMaxRows && dfMaxCols == 0 )
	{
		//MessageBox(g_df.GetLastError());
		//AfxMessageBox(_T("ERROR: No hay datos."));
	}

	int MaxCols = dfMaxCols;
	int MaxRows = dfMaxRows;
	int MaxFixCols = 0;
	int MaxFixRows = 1;
	UpdateData(false);
	
	TRY 
	{
		    pMainFrame->m_GridInduction.SetRowCount(MaxRows+1);
		    pMainFrame->m_GridInduction.SetColumnCount(MaxCols);
		    pMainFrame->m_GridInduction.SetFixedRowCount(MaxFixRows);
		    pMainFrame->m_GridInduction.SetFixedColumnCount(MaxFixCols);
	}
	CATCH (CMemoryException, e)
	{
	    	
	e->ReportError();
    return;
	}
    END_CATCH


	TCHAR sBuffer[BUFF_SIZE];	
	CString szColName;
	
	//Populate grid control columns
	for (int col = 0; col < MaxCols; ++col)
    {
		//Fill ListCtrl1 with header name
		szColName = query.GetColumnName(col);
		wsprintf(sBuffer, szColName);
		pMainFrame->m_GridInduction.SetItemText(0, col, szColName);
		/*
		if(!g_df.CreateVariable(szColName.GetBuffer(szColName.GetLength()*4), _T(""), dfMaxCols))
		{
				MessageBox(g_df.GetLastError());
				return;
		}
		*/
		LVITEM  Item;
		Item = AddListItem1(col, 0, sBuffer);
		CString strNo = _itot(col+1, sBuffer, 10);
		LPTSTR lpszNo = strNo.GetBuffer(strNo.GetLength()*4);
		AddListSubItem1(Item, col+1, 1, _T("Input"));
			
			
			CString sz; 
			query > sz;
			int row = 1;
			//Check for missing values to avoid crash with GetAt() function
			if(sz.IsEmpty())
			{
				
				while(!query.eof())
				{
					query > sz;
			
			//AfxMessageBox(_T("Valor  ") + sz);
			//CString str;
			//str.Format(_T("Max Rows ... %d dfMaxRows...%d  " ),col, row);
			//AfxMessageBox(str);
			
					if(!sz.IsEmpty())
					{
						break;
					}
					row++;
				}

			}

			//AfxMessageBox(_T("Valor  ") + sz);
			//CString str;
			//str.Format(_T("Max Rows ... %d Row...%d  " ),dfMaxRows, row);
			//AfxMessageBox(str);
			//If there is no data in all the table
			if(row == dfMaxRows || dfMaxRows == 0)
			{
				AddListSubItem1(Item, col, 2, _T("Unknown"));
				AddListSubItem1(Item, col, 3, lpszNo);
				//AfxMessageBox(_T("ERROR: Tipo de dato no compatible"));
			}
			else
			{
				
				if(LA_isNumeric(sz.GetAt(0)))
					AddListSubItem1(Item, col, 2, _T("Numeric"));
				else 
					AddListSubItem1(Item, col, 2, _T("Nominal"));
				
				  AddListSubItem1(Item, col, 3, lpszNo);
				
			}
			
	
	}
	
	//Populate Grid control rows
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Copying data to Memory..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);
	
	int row = 0;
	query.ExecuteSQL();
	while(!query.eof() )
	{
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, row*100/dfMaxRows);
		
		for(int col = 0; col<dfMaxCols; col++)
		{
			
			CString szValue; 
			query > szValue;
			pMainFrame->m_GridInduction.SetItemText(row+1, col, szValue);
			
			/*
			AfxMessageBox(_T("Valor  ") + szValue);
			CString str;
			str.Format(_T("col ... %d row...%d  " ),col, row);
			AfxMessageBox(str);
			*/
			/*
			if(!g_df.SetData(col, row , szValue.GetBuffer(szValue.GetLength()*4)))
			{
					//MessageBox(g_df.GetLastError());
					//return;
			}
			*/

		}
		
		row++;
	}
		
	
	//Get data from GridCtrl

		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);
		pMainFrame->m_wndStatusBar.ResetBar(1);


		int iLength =	pMainFrame->m_GridInduction.GetColumnCount() - pMainFrame->m_GridInduction.GetFixedColumnCount();
		int iSize =		pMainFrame->m_GridInduction.GetRowCount() - pMainFrame->m_GridInduction.GetFixedRowCount();
		
		for( col = 0; col<iLength; col++)
		{
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, col*100/iLength);

			szColName = pMainFrame->m_GridInduction.GetItemText(1, col + pMainFrame->m_GridInduction.GetFixedColumnCount());
			if(!g_df.CreateVariable(szColName.GetBuffer(szColName.GetLength()*4), _T(""), iSize))
			{
				MessageBox(g_df.GetLastError());
				return;
			}
			
				szColName.ReleaseBuffer();
		
			
			for( row = 0; row<iSize; row++)
			{
				CString szValue = pMainFrame->m_GridInduction.GetItemText(row + pMainFrame->m_GridInduction.GetFixedRowCount() , col + pMainFrame->m_GridInduction.GetFixedColumnCount());
				if(!g_df.SetData(col  , row , szValue.GetBuffer(szValue.GetLength()*4)))
				{
					MessageBox(g_df.GetLastError());
					return;
				}
				
				
			}
			
		}
	

	


	szColName.ReleaseBuffer();
	pMainFrame->m_GridInduction.AutoSize();

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);



}

void CInductionTabView::QueryFixed()
{
	
	
	//Set progress bar
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 0, 0);
	//pMainFrame->m_wndStatusBar.SetPaneInfo( 1, nID, nStyle, 100);
	pMainFrame->m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	
	
	CSQLQuery& query = m_query;
	int dfMaxCols = query.GetColumnsCount();
	int dfMaxRows = query.GetDataCount()/dfMaxCols;
	
				
	if( dfMaxRows && dfMaxCols == 0 )
	{
		MessageBox(g_df.GetLastError());
	}

	int MaxCols = dfMaxCols;
	int MaxRows = dfMaxRows;
	int MaxFixCols = 1;
	int MaxFixRows = 2;
	


	UpdateData(false);
	
	TRY 
	{
		    pMainFrame->m_GridInduction.SetRowCount(MaxRows+2);
		    pMainFrame->m_GridInduction.SetColumnCount(MaxCols+1);
		    pMainFrame->m_GridInduction.SetFixedRowCount(MaxFixRows);
		    pMainFrame->m_GridInduction.SetFixedColumnCount(MaxFixCols);
	}
	CATCH (CMemoryException, e)
	{
	    	
	e->ReportError();
    return;
	}
    END_CATCH

	
	TCHAR sBuffer[BUFF_SIZE];	
	CString szColName;


	//Populate grid control columns
	for (int col = 0; col <= MaxCols; ++col)
    {
		//Fill ListCtrl1 with header name
		if( col < dfMaxCols )
		{
			szColName = query.GetColumnName(col);
			wsprintf(sBuffer, szColName);
			pMainFrame->m_GridInduction.SetItemText(m_nFixCols, col+1, szColName);
			/*
			if(!g_df.CreateVariable(szColName.GetBuffer(szColName.GetLength()*4), _T(""), dfMaxCols))
			{
				MessageBox(g_df.GetLastError());
				return;
			}
			*/

			LVITEM  Item;
			Item = AddListItem1(col, 0, sBuffer);
			CString strNo = _itot(col+1, sBuffer, 10);
			LPTSTR lpszNo = strNo.GetBuffer(strNo.GetLength()*4);
			AddListSubItem1(Item, col+1, 1, _T("Input"));
			
			
			CString sz; 
			query > sz;
			int row = 1;
			//Check for missing values to avoid crash with GetAt() function
			if(sz.IsEmpty())
			{
				
				while(!query.eof())
				{
					query > sz;
					if(!sz.IsEmpty())
					{
						break;
					}
					row++;
				}

			}
			//If there is no data in all the table
			if(row == dfMaxRows || dfMaxRows == 0)
			{
				AddListSubItem1(Item, col, 2, _T("Unknown"));
				AddListSubItem1(Item, col, 3, lpszNo);
			}
			else
			{
				if(LA_isNumeric(sz.GetAt(0)))
					AddListSubItem1(Item, col, 2, _T("Numeric"));
				else 
					AddListSubItem1(Item, col, 2, _T("Nominal"));
				
				  AddListSubItem1(Item, col, 3, lpszNo);
			}
					
				
		}
		
		
		//Set Column Number
		CString str;
		str.Format(_T("Column %d"),col);
		pMainFrame->m_GridInduction.SetItemText(0, col, str);
		
			
		if(col == 0)
		{
			int row = 1;
			str.Format(_T("Row %d"), row);
			pMainFrame->m_GridInduction.SetItemText(row, col, str);
		}
			

	}
	
	
	
	//Populate grid control rows
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Loading data..."), RGB(0,0,0), TRUE);
	pMainFrame->m_wndStatusBar.ResetBar(1);
	
	int row = 2;
	query.ExecuteSQL();
	while(!query.eof())
	{
		pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, (row-2)*100/dfMaxRows);
		
		for(int col = 0; col<= dfMaxCols; col++)
		{
			

			if(col == 0)
			{
				CString str;
				str.Format(_T("Row %d"), row);
				pMainFrame->m_GridInduction.SetItemText(row, col, str);
			}
			else
			{
				CString szValue; 
				query > szValue;
				pMainFrame->m_GridInduction.SetItemText(row, col, szValue);
				/*
				if(!g_df.SetData(col-1  , row , szValue.GetBuffer(szValue.GetLength()*4)))
				{
					MessageBox(g_df.GetLastError());
					return;
				}
				*/
				
				
			}
		}
		row++;
	}

	
	
	//Get data from GridCtrl
		pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Copying data to Memory..."), RGB(0,0,0), TRUE);
		pMainFrame->m_wndStatusBar.ResetBar(1);

		int iLength =	pMainFrame->m_GridInduction.GetColumnCount() - pMainFrame->m_GridInduction.GetFixedColumnCount();
		int iSize =		pMainFrame->m_GridInduction.GetRowCount() - pMainFrame->m_GridInduction.GetFixedRowCount();
		
		for( col = 0; col<iLength; col++)
		{
			
			pMainFrame->m_wndStatusBar.SetBarProgress(1, TRUE, 100, col*100/iLength);


			szColName = pMainFrame->m_GridInduction.GetItemText(1, col + pMainFrame->m_GridInduction.GetFixedColumnCount());
			if(!g_df.CreateVariable(szColName.GetBuffer(szColName.GetLength()*4), _T(""), iSize))
			{
				MessageBox(g_df.GetLastError());
				return;
			}
			
				szColName.ReleaseBuffer();
		
			
			for( row = 0; row<iSize; row++)
			{
				CString szValue = pMainFrame->m_GridInduction.GetItemText(row + pMainFrame->m_GridInduction.GetFixedRowCount() , col + pMainFrame->m_GridInduction.GetFixedColumnCount());
				if(!g_df.SetData(col  , row , szValue.GetBuffer(szValue.GetLength()*4)))
				{
					MessageBox(g_df.GetLastError());
					return;
				}
				
				
			}
			
		}
		
	

	szColName.ReleaseBuffer();
	pMainFrame->m_GridInduction.AutoSize();

	pMainFrame->m_wndStatusBar.ResetBar(1, TRUE);
	pMainFrame->m_wndStatusBar.SetPaneText( 0, _T("Process finished"), RGB(0,0,0), TRUE);
	

}

int CInductionTabView::LA_isNumeric(CString t)
{
	
	if( t == _T("0"))
	{
		return 1;
	}
    else if (t == _T("1"))
	{
		return 1;
	}
	else if (t == _T("2"))
	{
		return 1;
	}
	else if (t == _T("3"))
	{
		return 1;
	}
	else if (t == _T("4"))
	{
		return 1;
	}
	else if (t == _T("5"))
	{
		return 1;
	}
	else if (t == _T("6"))
	{
		return 1;
	}
	else if (t == _T("7"))
	{
		return 1;
	}
	else if (t == _T("8"))
	{
		return 1;
	}
	else if (t == _T("9"))
	{
		return 1;
	}
	else if (t == _T("-"))
	{
		return 1;
	}
	else if (t == _T("+"))
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}



void CInductionTabView::OnChangeEditQuery() 
{
	UpdateData();	
}


void CInductionTabView::PopulateTree()
{
	
	COleDBConnectionProp& prop = ((CAIPIApp*)AfxGetApp())->m_props;

	m_treeCtrl.DeleteAllItems();
	

	CTables	tableSet;

	HTREEITEM hDatabase = 
	m_treeCtrl.InsertItem(prop.m_strDatabaseName,IID_DATABASE,IID_DATABASES);
	m_treeCtrl.SetItemData(hDatabase,TNode_RootDatabase);

	HTREEITEM hTables = 
	m_treeCtrl.InsertItem(_T("Tables"),IID_TABLE,IID_TABLES,hDatabase);
	m_treeCtrl.SetItemData(hTables,TNode_RootTables);

	CString strType("TABLE");
	

	if (tableSet.Open(*GetSession(), NULL, NULL, NULL, strType) != S_OK)
		return;

	while(tableSet.MoveNext() == S_OK)
	{
		HTREEITEM hItem = NULL;
		if (_tcscmp(tableSet.m_szType, _T("VIEW")) == 0)
			hItem = m_treeCtrl.InsertItem(tableSet.m_szName,IID_VIEW,IID_VIEWS,hTables);
		else
			hItem = m_treeCtrl.InsertItem(tableSet.m_szName,IID_TABLE,IID_TABLES,hTables);
		m_treeCtrl.SetItemData(hItem,TNode_TableName);
		
	}

	UpdateWindow();
	

}

void CInductionTabView::OnSelchangedTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	TreeNodeTypeDB nodeType = TNode_None;
	CString strText;

	if(hItem != NULL)
	{
		nodeType = (TreeNodeTypeDB)m_treeCtrl.GetItemData(hItem);
		strText = m_treeCtrl.GetItemText(hItem);
	}

	OnSelectTreeNode(nodeType, strText);

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pInsertPage->m_nMaxRows = pMainFrame->m_GridInduction.GetRowCount()-1;
	pInsertPage->m_nMaxCols = pMainFrame->m_GridInduction.GetColumnCount()-1;
	pInsertPage->m_nMaxFixRows = pMainFrame->m_GridInduction.GetFixedRowCount();
	pInsertPage->m_nMaxFixCols = pMainFrame->m_GridInduction.GetFixedColumnCount();
	pInsertPage->UpdateData(false);
	


	CString str;
	
	str.Format(_T("%d Rws."), pInsertPage->m_nMaxRows);
	pFilePage->m_nRows.SetWindowText(str);
	str.Format(_T("%d Cols."), pInsertPage->m_nMaxCols);
	pFilePage->m_nCols.SetWindowText(str);

	
	*pResult = 0;
}






BOOL CInductionTabView::OnOpenDatabaseConnection(int iDatabase)
{
	if( theApp.OpenDBConnDlg(iDatabase) != TRUE)
		return FALSE; 
	
	PopulateTree();
	
		return TRUE;
}




void CInductionTabView::OnDeltaposInductionSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if( pNMUpDown->iDelta < 0)
	{
		m_iVTablesPos = m_iVTablesPos + m_iSizeFactor;
		ChangeVTablesSize(m_iVTablesPos);
	}
	else
	{
		m_iVTablesPos = m_iVTablesPos - m_iSizeFactor;
		ChangeVTablesSize(m_iVTablesPos);
	}
	
	
	*pResult = 0;
}
