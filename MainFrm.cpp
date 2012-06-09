// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "AIPI.h"

#include "MainFrm.h"
#include ".\ScintillaCtrl\ScintillaDocView.h"
#include "WorkspaceTabDoc.h"
#include "WorkspaceView.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, MainFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, MainFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SETTINGCHANGE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_LINE, OnUpdateLine) 
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_DOC, OnUpdateDoc) 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_STYLE, OnUpdateStyle) 
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_FOLD, OnUpdateFold) 
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateInsert)
	ON_COMMAND(ID_VIEW_OUTPUTTABVIEW, OnViewOutputTabView)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUTTABVIEW, OnUpdateViewOutputTabView)
	ON_COMMAND(ID_VIEW_COMMANDDLGBAR, OnViewCommandDlgBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COMMANDDLGBAR, OnUpdateViewCommandDlgBar)
	ON_COMMAND(ID_SETTINGS_CUSTOMIZE, OnSettingsCustomize)
	ON_COMMAND(ID_VIEW_CTRL_JUKEBOXDLG, OnViewCtrlJukeBoxDlg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_JUKEBOXDLG, OnUpdateViewCtrlJukeBoxDlg)
	ON_COMMAND(ID_VIEW_CTRL_MEDIAPLAYERDLG, OnViewCtrlMediaPlayerDlg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_MEDIAPLAYERDLG, OnUpdateViewCtrlMediaPlayerDlg)
	ON_COMMAND(ID_VIEW_CTRL_IMAGEDLG, OnViewCtrlImageDlg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_IMAGEDLG, OnUpdateViewCtrlImageDlg)
	ON_COMMAND(ID_VIEW_CTRL_IMAGECTRL, OnViewCtrlImageCtrl)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_IMAGECTRL, OnUpdateViewCtrlImageCtrl)
	ON_COMMAND(ID_VIEW_CTRL_LISTOPTIONCTRL, OnViewCtrlListOptionCtrl)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_LISTOPTIONCTRL, OnUpdateViewCtrlListOptionCtrl)
	ON_COMMAND(ID_VIEW_CTRL_NSCHARTBARCTRL, OnViewCtrlNSChartBarCtrl)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_NSCHARTBARCTRL, OnUpdateViewCtrlNSChartBarCtrl)
	ON_COMMAND(ID_VIEW_CTRL_CHARTBARCTRL, OnViewCtrlChartBarCtrl)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_CHARTBARCTRL, OnUpdateViewCtrlChartBarCtrl)
	ON_COMMAND(ID_VIEW_CTRL_CALENDARDLG, OnViewCtrlCalendarDlg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_CALENDARDLG, OnUpdateViewCtrlCalendarDlg)
	ON_COMMAND(ID_VIEW_CTRL_STATICMETERCTRL, OnViewCtrlStaticMeterCtrl)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_STATICMETERCTRL, OnUpdateViewCtrlStaticMeterCtrl)
	ON_COMMAND(ID_VIEW_CTRL_IMAGEFILTERDLG, OnViewCtrlImageFilterDlg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_IMAGEFILTERDLG, OnUpdateViewCtrlImageFilterDlg)
	ON_COMMAND(ID_VIEW_CTRL_LISTMULTIOPTIONCTRL, OnViewCtrlListMultiOptionCtrl)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_LISTMULTIOPTIONCTRL, OnUpdateViewCtrlListMultiOptionCtrl)
	ON_COMMAND(ID_VIEW_CTRL_GRAPHBARCTRL, OnViewCtrlGraphBarCtrl)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_GRAPHBARCTRL, OnUpdateViewCtrlGraphBarCtrl)
	ON_COMMAND(ID_VIEW_CTRL_EDITINFOBAR, OnViewCtrlEditInfoBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_EDITINFOBAR, OnUpdateViewCtrlEditInfoBar)
	ON_COMMAND(ID_VIEW_CTRL_INFOCTRL, OnViewCtrlInfoCtrl)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_INFOCTRL, OnUpdateViewCtrlInfoCtrl)
	ON_COMMAND(ID_VIEW_WORKSPACETABVIEW, OnViewWorkSpaceTabView)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACETABVIEW, OnUpdateViewWorkSpaceTabView)
	ON_COMMAND(ID_VIEW_CTRL_OLEDBDLG, OnViewCtrlOleDBDlg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_OLEDBDLG, OnUpdateViewCtrlOleDBDlg)
	ON_COMMAND(ID_VIEW_CTRL_DXFCADDLG, OnViewCtrlDxfCadDlg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CTRL_DXFCADDLG, OnUpdateViewCtrlDxfCadDlg)
	ON_COMMAND(ID_SETTINGS_SKIN_CLASSIC, OnSettingsSkinClassic)
	ON_COMMAND(ID_SETTINGS_SKIN_OFFICEXP, OnSettingsSkinOfficeXP)
	ON_COMMAND(ID_SETTINGS_SKIN_OFFICE2003, OnSettingsSkinOffice2003)
	ON_COMMAND(ID_VIEW_INDUCTION_FRAME_DLG, OnViewInductionFrameDlg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INDUCTION_FRAME_DLG, OnUpdateViewInductionFrameDlg)
	ON_COMMAND(ID_VIEW_AIPI_FRAME_DLG, OnViewAipiFrameDlg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_AIPI_FRAME_DLG, OnUpdateViewAipiFrameDlg)
	ON_COMMAND(ID_PROJ_OPEN, OnProjOpen)
	ON_COMMAND(ID_PROJ_NEW, OnProjNew)
	ON_COMMAND(ID_FILE_SAVE_ALL, OnFileSaveAll)
	ON_COMMAND(ID_VIEW_PROPERTIESBAR, OnViewPropertiesBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTIESBAR, OnUpdateViewPropertiesBar)
	ON_COMMAND(ID_PROJ_CLOSE, OnProjClose)
	ON_COMMAND(ID_PROJ_SAVE, OnProjSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_ALL, OnUpdateFileSaveAll)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP

	ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, OnDropDown)
	ON_CBN_SELCHANGE(IDC_FINDFILESCOMBO, OnSelChangeCombo)

END_MESSAGE_MAP()

static UINT indicators[] =
{
  ID_SEPARATOR,           // status line indicator
  ID_INDICATOR_PROG,
  ID_INDICATOR_FOLD,
  ID_INDICATOR_STYLE,
  ID_INDICATOR_LINE,
  ID_INDICATOR_DOC,
  ID_INDICATOR_OVR,
  ID_INDICATOR_CAPS,
  ID_INDICATOR_NUM,
  ID_INDICATOR_SCRL,
};


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame():
COXMenuBarFrame<MainFrameWnd,COXSizeDockBar>(CBRS_ALIGN_ANY,
	RUNTIME_CLASS(COXSizableMiniDockFrameWnd))
{


//CPageEditDlg
	m_bEditable = FALSE;

	
//CPageFileDlg
	m_bVirtualMode = FALSE;
	m_bCallback = FALSE;
	m_bTables = TRUE;
	m_bQuery  = TRUE;
	m_bData = TRUE;
	m_bVTables = FALSE;
	
	
		
	
//CPageOptionsDlg	
	m_bToolTips = TRUE;
	m_bSort = FALSE;
	m_bCellSelect = TRUE;
	
//CPageFormatdlg
	m_bHorizontal = TRUE;
	m_bVertical = TRUE;
	m_bItalic = FALSE;
	m_bBold = FALSE;
	m_bNormal = TRUE;
	m_bVerticalHeader = FALSE;
	m_bTitleTips = TRUE;

//CPageCellSize
	m_bFitGrid = FALSE;
	m_bColumnResize = TRUE;
	m_bRowResize = TRUE;

	InitGridVars();


//WorkspaceTabView 
	hTProjectRoot = NULL;
	hTProjectRule = NULL;
	hTProjectFunction = NULL;
	hTProjectQuery = NULL;
	hTProjectVariable = NULL;
	hTProjectClass = NULL;
 
}

CMainFrame::~CMainFrame()
{
}





int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
#ifdef OX_CUSTOMIZE_INSTANCE_MANAGER
	if(m_customizeManager.CheckMaxAllowedInstances())
	{
		TRACE(_T("CMainFrame::OnCreate: the maximum allowed number of instances has been reached. The application won't be loaded\n"));
		return -1;
	}
#endif	//	OX_CUSTOMIZE_INSTANCE_MANAGER


#ifdef OX_CUSTOMIZE_SPLASHWINDOW
	VERIFY(m_customizeManager.InitializeSplashWindow(IDB_AIPI_LOGO));

#endif	//	OX_CUSTOMIZE_INSTANCE_MANAGER



	if (MainFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	//Creates the toolbars
/*	
	CreateImageDlgToolBar();
	CreateCalendarDlgToolBar();
	CreateNSChartBarCtrlToolBar();
	CreateChartBarCtrlToolBar();
	CreateGraphBarCtrlToolBar();
	CreateStaticMeterCtrlToolBar();
	CreateImageCtrlToolBar();
	CreateListOptionCtrlToolBar();
*/	
	
	CreateStandardToolBar();
	CreateStatusBar();
	

	
		
	
	

	EnableDocking(CBRS_ALIGN_ANY);

	//Comment these lines if you don't want the toolbars to be dockable
	
	//Standard toolbar
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//CreateComboToolBar();

	/*
	//ImageDlg toolbar
	m_wndToolBarImageDlg.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarImageDlg);
	

	//CalendarDlg toolbar
	m_wndToolBarCalendarDlg.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarCalendarDlg);
	
	//NSChartBarCtrl toolbar
	m_wndToolBarNSChartBarCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarNSChartBarCtrl);

  //ChartBarCtrl toolbar
	m_wndToolBarChartBarCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarChartBarCtrl);

  //GraphBarCtrl toolbar
	m_wndToolBarGraphBarCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarGraphBarCtrl);

  //StaticMeterCtrl toolbar
	m_wndToolBarStaticMeterCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarStaticMeterCtrl);

  //ImageCtrl toolbar
	m_wndToolBarImageCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarImageCtrl);

  //ListOptionCtrl toolbar
	m_wndToolBarListOptionCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarListOptionCtrl);
*/


	//Creates the controls
	
	


	
	
	
	

	CreateImageDlg();
	CreateJukeBoxDlg();
	CreateMediaPlayerDlg();

	CreateCalendarDlg();
	CreateDxfCadDlg();
	CreateImageFilterDlg();
	
	 CreateOleDBDlg();

	CreateImageCtrl();
	CreateEditInfoCtrl();
	CreateInfoCtrl();
	CreateListOptionCtrl();

	CreateListMultiOptionCtrl();

	CreateNSChartBarCtrl();
	CreateChartBarCtrl();
	CreateGraphBarCtrl();
	CreateStaticMeterCtrl();

		
	CreateCommandDlgBar();
	CreateOutputTabView();
	CreateWorkspaceTabView();
	CreatePropertiesBar();
	CreateInductionTabView();
	CreateAIPITabView();
	
	

	// Add the following 2 lines to tab all the windows docked to the left dock bar
	// and have the properties bar as the selected tab.
	//COXSizeDockBar* pLeftDockBar = (COXSizeDockBar*) m_wndWorkspaceTabView.m_pDockBar;
	//pLeftDockBar->TabAllDockedControlBars(&m_wndWorkspaceTabView);

	// Add the following 2 lines to tab all the windows docked to the right dock bar
	// and have the listoption bar as the selected tab.
	//COXSizeDockBar* pRightDockBar = (COXSizeDockBar*) m_wndListOptionCtrl.m_pDockBar;
	//pRightDockBar->TabAllDockedControlBars(&m_wndListOptionCtrl);
	
	
	CustomizeApp();
	RecalcLayout();
	

	// Enable the snapping and tear-off befavior for toolbars,
	// menu bars and docking windows
	//EnableSnapping();

	// Uncomment the following lines if you don't want the user to be able to move
	// the menubar and the toolbars
	GetMenuBar().EnableFloating(FALSE);


	
	
	
	
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !MainFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


void CMainFrame::StopTimer(CPerfTimer t, CString msg)
{

	CString str;
	str.Format(msg + _T("%0.4f"),t.Elapsed());
	
	if ( m_wndOutputTabView.IsVisible())
	{
		m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(0);
		m_wndOutputTabView.AddMsg1(str);
		
	}
	t.Stop();

}



//////////////////////////////////////////////////////////////////////////////
//// GRID FUNCTIONS /////
///////////////////////////////////////////////////////////////////////////////




void CMainFrame::InitGridVars()
{
	
	//CPageEditDlg
	CreateGridVarState(_T("EditableLHS"),				false);
	CreateGridVarState(_T("EditableRHS"),				false);
	CreateGridVarState(_T("EditableWM"),				false);
	CreateGridVarState(_T("EditableCLink"),				false);
	CreateGridVarState(_T("EditableAgenda"),			false);
	CreateGridVarState(_T("EditableAM"),				false);
	CreateGridVarState(_T("EditableBM"),				false);
	CreateGridVarState(_T("EditableBM_TK"),				false);
	CreateGridVarState(_T("EditableRETE"),				false);
	CreateGridVarState(_T("EditableInduction"),			false);
	
	//CPageFileDlg
	CreateGridVarState(_T("VirtualModeLHS"),			false);
	CreateGridVarState(_T("VirtualModeRHS"),			false);
	CreateGridVarState(_T("VirtualModeWM"),				false);
	CreateGridVarState(_T("VirtualModeCLink"),			false);
	CreateGridVarState(_T("VirtualModeAgenda"),			false);
	CreateGridVarState(_T("VirtualModeAM"),				false);
	CreateGridVarState(_T("VirtualModeBM"),				false);
	CreateGridVarState(_T("VirtualModeBM_TK"),			false);
	CreateGridVarState(_T("VirtualModeRETE"),			false);
	CreateGridVarState(_T("VirtualModeInduction"),		false);
	
	CreateGridVarState(_T("CallbackLHS"),				false);
	CreateGridVarState(_T("CallbackRHS"),				false);
	CreateGridVarState(_T("CallbackWM"),				false);
	CreateGridVarState(_T("CallbackCLink"),				false);
	CreateGridVarState(_T("CallbackAgenda"),			false);
	CreateGridVarState(_T("CallbackAM"),				false);
	CreateGridVarState(_T("CallbackBM"),				false);
	CreateGridVarState(_T("CallbackBM_TK"),				false);
	CreateGridVarState(_T("CallbackRETE"),				false);
	CreateGridVarState(_T("CallbackInduction"),			false);
	
	
	
	
	//CPageOptionsDlg
	CreateGridVarState(_T("ToolTipsLHS"),				true);
	CreateGridVarState(_T("ToolTipsRHS"),				true);
	CreateGridVarState(_T("ToolTipsWM"),				true);
	CreateGridVarState(_T("ToolTipsCLink"),				true);
	CreateGridVarState(_T("ToolTipsAgenda"),			true);
	CreateGridVarState(_T("ToolTipsAM"),				true);
	CreateGridVarState(_T("ToolTipsBM"),				true);
	CreateGridVarState(_T("ToolTipsBM_TK"),				true);
	CreateGridVarState(_T("ToolTipsRETE"),				true);
	CreateGridVarState(_T("ToolTipsInduction"),			true);

	CreateGridVarState(_T("SortLHS"),					false);
	CreateGridVarState(_T("SortRHS"),					false);
	CreateGridVarState(_T("SortWM"),					false);
	CreateGridVarState(_T("SortCLink"),					false);
	CreateGridVarState(_T("SortAgenda"),				false);
	CreateGridVarState(_T("SortAM"),					false);
	CreateGridVarState(_T("SortBM"),					false);
	CreateGridVarState(_T("SortBM_TK"),					false);
	CreateGridVarState(_T("SortRETE"),					false);
	CreateGridVarState(_T("SortInduction"),				false);

	CreateGridVarState(_T("CellSelectLHS"),				true);
	CreateGridVarState(_T("CellSelectRHS"),				true);
	CreateGridVarState(_T("CellSelectWM"),				true);
	CreateGridVarState(_T("CellSelectCLink"),			true);
	CreateGridVarState(_T("CellSelectAgenda"),			true);
	CreateGridVarState(_T("CellSelectAM"),				true);
	CreateGridVarState(_T("CellSelectBM"),				true);
	CreateGridVarState(_T("CellSelectBM_TK"),			true);
	CreateGridVarState(_T("CellSelectRETE"),			true);
	CreateGridVarState(_T("CellSelectInduction"),		true);

	//CPageFormatDlg
	CreateGridVarState(_T("HorizontalLHS"),				true);
	CreateGridVarState(_T("HorizontalRHS"),				true);
	CreateGridVarState(_T("HorizontalWM"),				true);
	CreateGridVarState(_T("HorizontalCLink"),			true);
	CreateGridVarState(_T("HorizontalAgenda"),			true);
	CreateGridVarState(_T("HorizontalAM"),				true);
	CreateGridVarState(_T("HorizontalBM"),				true);
	CreateGridVarState(_T("HorizontalBM_TK"),			true);
	CreateGridVarState(_T("HorizontalRETE"),			true);
	CreateGridVarState(_T("HorizontalInduction"),		true);

	CreateGridVarState(_T("VerticalLHS"),				true);
	CreateGridVarState(_T("VerticalRHS"),				true);
	CreateGridVarState(_T("VerticalWM"),				true);
	CreateGridVarState(_T("VerticalCLink"),				true);
	CreateGridVarState(_T("VerticalAgenda"),			true);
	CreateGridVarState(_T("VerticalAM"),				true);
	CreateGridVarState(_T("VerticalBM"),				true);
	CreateGridVarState(_T("VerticalBM_TK"),				true);
	CreateGridVarState(_T("VerticalRETE"),				true);
	CreateGridVarState(_T("VerticalInduction"),			true);

	CreateGridVarState(_T("ItalicLHS"),					false);
	CreateGridVarState(_T("ItalicRHS"),					false);
	CreateGridVarState(_T("ItalicWM"),					false);
	CreateGridVarState(_T("ItalicCLink"),				false);
	CreateGridVarState(_T("ItalicAgenda"),				false);
	CreateGridVarState(_T("ItalicAM"),					false);
	CreateGridVarState(_T("ItalicBM"),					false);
	CreateGridVarState(_T("ItalicBM_TK"),				false);
	CreateGridVarState(_T("ItalicRETE"),				false);
	CreateGridVarState(_T("ItalicInduction"),			false);

	CreateGridVarState(_T("BoldLHS"),					false);
	CreateGridVarState(_T("BoldRHS"),					false);
	CreateGridVarState(_T("BoldWM"),					false);
	CreateGridVarState(_T("BoldCLink"),					false);
	CreateGridVarState(_T("BoldAgenda"),				false);
	CreateGridVarState(_T("BoldAM"),					false);
	CreateGridVarState(_T("BoldBM"),					false);
	CreateGridVarState(_T("BoldBM_TK"),					false);
	CreateGridVarState(_T("BoldRETE"),					false);
	CreateGridVarState(_T("BoldInduction"),				false);

	CreateGridVarState(_T("NormalLHS"),					true);
	CreateGridVarState(_T("NormalRHS"),					true);
	CreateGridVarState(_T("NormalWM"),					true);
	CreateGridVarState(_T("NormalCLink"),				true);
	CreateGridVarState(_T("NormalAgenda"),				true);
	CreateGridVarState(_T("NormalAM"),					true);
	CreateGridVarState(_T("NormalBM"),					true);
	CreateGridVarState(_T("NormalBM_TK"),				true);
	CreateGridVarState(_T("NormalRETE"),				true);
	CreateGridVarState(_T("NormalInduction"),			true);

	CreateGridVarState(_T("VerticalHeaderLHS"),			false);
	CreateGridVarState(_T("VerticalHeaderRHS"),			false);
	CreateGridVarState(_T("VerticalHeaderWM"),			false);
	CreateGridVarState(_T("VerticalHeaderCLink"),		false);
	CreateGridVarState(_T("VerticalHeaderAgenda"),		false);
	CreateGridVarState(_T("VerticalHeaderAM"),			false);
	CreateGridVarState(_T("VerticalHeaderBM"),			false);
	CreateGridVarState(_T("VerticalHeaderBM_TK"),		false);
	CreateGridVarState(_T("VerticalHeaderRETE"),		false);
	CreateGridVarState(_T("VerticalHeaderInduction"),	false);

	
	//CPageCellSizeDlg
	CreateGridVarState(_T("FitGridLHS"),				false);
	CreateGridVarState(_T("FitGridRHS"),				false);
	CreateGridVarState(_T("FitGridWM"),					false);
	CreateGridVarState(_T("FitGridCLink"),				false);
	CreateGridVarState(_T("FitGridAgenda"),				false);
	CreateGridVarState(_T("FitGridAM"),					false);
	CreateGridVarState(_T("FitGridBM"),					false);
	CreateGridVarState(_T("FitGridBM_TK"),				false);
	CreateGridVarState(_T("FitGridRETE"),				false);
	CreateGridVarState(_T("FitGridInduction"),			false);

	CreateGridVarState(_T("ColumnResizeLHS"),			true);
	CreateGridVarState(_T("ColumnResizeRHS"),			true);
	CreateGridVarState(_T("ColumnResizeWM"),			true);
	CreateGridVarState(_T("ColumnResizeCLink"),			true);
	CreateGridVarState(_T("ColumnResizeAgenda"),		true);
	CreateGridVarState(_T("ColumnResizeAM"),			true);
	CreateGridVarState(_T("ColumnResizeBM"),			true);
	CreateGridVarState(_T("ColumnResizeBM_TK"),			true);
	CreateGridVarState(_T("ColumnResizeRETE"),			true);
	CreateGridVarState(_T("ColumnResizeInduction"),		true);

	CreateGridVarState(_T("RowResizeLHS"),				true);
	CreateGridVarState(_T("RowResizeRHS"),				true);
	CreateGridVarState(_T("RowResizeWM"),				true);
	CreateGridVarState(_T("RowResizeCLink"),			true);
	CreateGridVarState(_T("RowResizeAgenda"),			true);
	CreateGridVarState(_T("RowResizeAM"),				true);
	CreateGridVarState(_T("RowResizeBM"),				true);
	CreateGridVarState(_T("RowResizeBM_TK"),			true);
	CreateGridVarState(_T("RowResizeRETE"),				true);
	CreateGridVarState(_T("RowResizeInduction"),		true);
	
}

void CMainFrame::CreateGridVarState(tstring var, bool state)
{
	
	gmGridVar_State.insert(g_mGridVar_State::value_type(var, state));
	
}


void CMainFrame::ChangeGridVarState(tstring var, bool state)
{
	g_mGridVar_State::iterator iter;
	gmGridVar_State[var] = state;
	
	/*
	CString st;
	st.Format(_T("State...%d  " ), state);
	AfxMessageBox(st);
	*/
}

bool CMainFrame::FindGridVarState(tstring var)
{
	g_mGridVar_State::iterator iter;
    iter = gmGridVar_State.find(var);
	if( iter != gmGridVar_State.end())
	{
		/*
		AfxMessageBox(_T("Found"));
		CString st;
		AfxMessageBox(var.data());
		st.Format(_T("State...%d  " ), iter->second);
		AfxMessageBox(st);
	*/

		return iter->second;
		
	}
	
	return false;

}



void CMainFrame::PrintGrid()
{
	TCHAR buffer[8];
	CString strState;
	

	for( g_mGridVar_State::const_iterator iter = gmGridVar_State.begin(); iter!= gmGridVar_State.end(); ++iter)
	{
		if( iter->first == _T("ListModeAM"))
		{
			m_wndOutputTabView.AddMsg1(_T("*******  GRID VARIABLES  *******"));
		}
		
		//if( iter->first == _T("ListModePM") || iter->first == _T("ListModeWM") || iter->first == _T("ListModeRETE"))
		//{
			
			m_wndOutputTabView.AddMsg1(_T("***)  Variable: "));
			m_wndOutputTabView.AddMsg1(iter->first.data());

			strState =  _itot( iter->second, buffer, 10 );
			m_wndOutputTabView.AddMsg1(strState);
		//}
		

	}
}



void CMainFrame::UpdateGridStates(int grid)
{
	
	
	switch(grid)
	{
	case GRID_LHS:
			m_bEditable = FindGridVarState(_T("EditableLHS"));
			//m_bVirtualMode = FindGridVarState(_T("VirtualModeLHS"));
			//m_bCallback = FindGridVarState(_T("CallbackLHS"));
		
			
		
			m_bToolTips = FindGridVarState(_T("ToolTipsLHS"));	
			m_bSort = FindGridVarState(_T("SortLHS"));
			m_bCellSelect = FindGridVarState(_T("CellSelectLHS"));
		
			
			m_bHorizontal = FindGridVarState(_T("HorizontalLHS"));
			m_bVertical = FindGridVarState(_T("VerticalLHS"));
			m_bItalic = FindGridVarState(_T("ItalicLHS"));
			m_bBold = FindGridVarState(_T("BoldLHS"));
			m_bNormal = FindGridVarState(_T("NormalLHS"));
			m_bVerticalHeader = FindGridVarState(_T("VerticalHeaderLHS"));
		
			m_bFitGrid = FindGridVarState(_T("FitGridLHS"));
			m_bColumnResize = FindGridVarState(_T("ColumnResizeLHS"));
			m_bRowResize = FindGridVarState(_T("RowResizeLHS"));
		
		break;
	case GRID_RHS:
			m_bEditable = FindGridVarState(_T("EditableRHS"));
			//m_bVirtualMode = FindGridVarState(_T("VirtualModeRHS"));
			//m_bCallback = FindGridVarState(_T("CallbackRHS"));
		
			
		
			m_bToolTips = FindGridVarState(_T("ToolTipsRHS"));	
			m_bSort = FindGridVarState(_T("SortRHS"));
			m_bCellSelect = FindGridVarState(_T("CellSelectRHS"));
		
			
			m_bHorizontal = FindGridVarState(_T("HorizontalRHS"));
			m_bVertical = FindGridVarState(_T("VerticalRHS"));
			m_bItalic = FindGridVarState(_T("ItalicRHS"));
			m_bBold = FindGridVarState(_T("BoldRHS"));
			m_bNormal = FindGridVarState(_T("NormalRHS"));
			m_bVerticalHeader = FindGridVarState(_T("VerticalHeaderRHS"));
		
			m_bFitGrid = FindGridVarState(_T("FitGridRHS"));
			m_bColumnResize = FindGridVarState(_T("ColumnResizeRHS"));
			m_bRowResize = FindGridVarState(_T("RowResizeRHS"));
		
		break;
	
	case GRID_WM:
		m_bEditable = FindGridVarState(_T("EditableWM"));	
		
		//m_bVirtualMode = FindGridVarState(_T("VirtualModeWM"));
		//m_bCallback = FindGridVarState(_T("CallbackWM"));
				
		m_bToolTips = FindGridVarState(_T("ToolTipsWM"));	
		m_bSort = FindGridVarState(_T("SortWM"));
		m_bCellSelect = FindGridVarState(_T("CellSelectWM"));
		
		
		m_bHorizontal = FindGridVarState(_T("HorizontalWM"));
		m_bVertical = FindGridVarState(_T("VerticalWM"));
		m_bItalic = FindGridVarState(_T("ItalicWM"));
		m_bBold = FindGridVarState(_T("BoldWM"));
		m_bNormal = FindGridVarState(_T("NormalWM"));
		m_bVerticalHeader = FindGridVarState(_T("VerticalHeaderWM"));
		
		m_bFitGrid = FindGridVarState(_T("FitGridWM"));
		m_bColumnResize = FindGridVarState(_T("ColumnResizeWM"));
		m_bRowResize = FindGridVarState(_T("RowResizeWM"));
		break;

	case GRID_COND_LINK:
		m_bEditable = FindGridVarState(_T("EditableCLink"));	
		
		//m_bVirtualMode = FindGridVarState(_T("VirtualModeCLink"));
		//m_bCallback = FindGridVarState(_T("CallbackCLink"));
				
		m_bToolTips = FindGridVarState(_T("ToolTipsCLink"));	
		m_bSort = FindGridVarState(_T("SortCLink"));
		m_bCellSelect = FindGridVarState(_T("CellSelectCLink"));
		
		
		m_bHorizontal = FindGridVarState(_T("HorizontalCLink"));
		m_bVertical = FindGridVarState(_T("VerticalCLink"));
		m_bItalic = FindGridVarState(_T("ItalicCLink"));
		m_bBold = FindGridVarState(_T("BoldCLink"));
		m_bNormal = FindGridVarState(_T("NormalCLink"));
		m_bVerticalHeader = FindGridVarState(_T("VerticalHeaderCLink"));
		
		m_bFitGrid = FindGridVarState(_T("FitGridCLink"));
		m_bColumnResize = FindGridVarState(_T("ColumnResizeCLink"));
		m_bRowResize = FindGridVarState(_T("RowResizeCLink"));
		break;
	
	
	case GRID_AGENDA:
		m_bEditable = FindGridVarState(_T("EditableAgenda"));	
		
		//m_bVirtualMode = FindGridVarState(_T("VirtualModeAgenda"));
		//m_bCallback = FindGridVarState(_T("CallbackAgenda"));
		
		
				
		m_bToolTips = FindGridVarState(_T("ToolTipsAgenda"));	
		m_bSort = FindGridVarState(_T("SortAgenda"));
		m_bCellSelect = FindGridVarState(_T("CellSelectAgenda"));
		
		m_bHorizontal = FindGridVarState(_T("HorizontalAgenda"));
		m_bVertical = FindGridVarState(_T("VerticalAgenda"));
		m_bItalic = FindGridVarState(_T("ItalicAgenda"));
		m_bBold = FindGridVarState(_T("BoldAgenda"));
		m_bNormal = FindGridVarState(_T("NormalAgenda"));
		m_bVerticalHeader = FindGridVarState(_T("VerticalHeaderAgenda"));
		
		m_bFitGrid = FindGridVarState(_T("FitGridAgenda"));
		m_bColumnResize = FindGridVarState(_T("ColumnResizeAgenda"));
		m_bRowResize = FindGridVarState(_T("RowResizeAgenda"));
		break;
	
	case GRID_AM:
		m_bEditable = FindGridVarState(_T("EditableAM"));	
		
		//m_bVirtualMode = FindGridVarState(_T("VirtualModeAM"));
		//m_bCallback = FindGridVarState(_T("CallbackAM"));
		
		
		m_bToolTips = FindGridVarState(_T("ToolTipsAM"));	
		m_bSort = FindGridVarState(_T("SortAM"));
		m_bCellSelect = FindGridVarState(_T("CellSelectAM"));
		
		
		m_bHorizontal = FindGridVarState(_T("HorizontalAM"));
		m_bVertical = FindGridVarState(_T("VerticalAM"));
		m_bItalic = FindGridVarState(_T("ItalicAM"));
		m_bBold = FindGridVarState(_T("BoldAM"));
		m_bNormal = FindGridVarState(_T("NormalAM"));
		m_bVerticalHeader = FindGridVarState(_T("VerticalHeaderAM"));
		
		m_bFitGrid = FindGridVarState(_T("FitGridAM"));
		m_bColumnResize = FindGridVarState(_T("ColumnResizeAM"));
		m_bRowResize = FindGridVarState(_T("RowResizeAM"));
		break;
	
	case GRID_BM:
		m_bEditable = FindGridVarState(_T("EditableBM"));	
		
		//m_bVirtualMode = FindGridVarState(_T("VirtualModeBM"));
		//m_bCallback = FindGridVarState(_T("CallbackBM"));
			
		
		m_bToolTips = FindGridVarState(_T("ToolTipsBM"));	
		m_bSort = FindGridVarState(_T("SortBM"));
		m_bCellSelect = FindGridVarState(_T("CellSelectBM"));
		
		
		m_bHorizontal = FindGridVarState(_T("HorizontalBM"));
		m_bVertical = FindGridVarState(_T("VerticalBM"));
		m_bItalic = FindGridVarState(_T("ItalicBM"));
		m_bBold = FindGridVarState(_T("BoldBM"));
		m_bNormal = FindGridVarState(_T("NormalBM"));
		m_bVerticalHeader = FindGridVarState(_T("VerticalHeaderBM"));
		
		m_bFitGrid = FindGridVarState(_T("FitGridBM"));
		m_bColumnResize = FindGridVarState(_T("ColumnResizeBM"));
		m_bRowResize = FindGridVarState(_T("RowResizeBM"));
		break;
	
	case GRID_BM_TK:
		m_bEditable = FindGridVarState(_T("EditableBM_TK"));	
		
		//m_bVirtualMode = FindGridVarState(_T("VirtualModeBM_TK"));
		//m_bCallback = FindGridVarState(_T("CallbackBM_TK"));
			
		
		m_bToolTips = FindGridVarState(_T("ToolTipsBM_TK"));	
		m_bSort = FindGridVarState(_T("SortBM_TK"));
		m_bCellSelect = FindGridVarState(_T("CellSelectBM_TK"));
		
		
		m_bHorizontal = FindGridVarState(_T("HorizontalBM_TK"));
		m_bVertical = FindGridVarState(_T("VerticalBM_TK"));
		m_bItalic = FindGridVarState(_T("ItalicBM_TK"));
		m_bBold = FindGridVarState(_T("BoldBM_TK"));
		m_bNormal = FindGridVarState(_T("NormalBM_TK"));
		m_bVerticalHeader = FindGridVarState(_T("VerticalHeaderBM_TK"));
		
		m_bFitGrid = FindGridVarState(_T("FitGridBM_TK"));
		m_bColumnResize = FindGridVarState(_T("ColumnResizeBM_TK"));
		m_bRowResize = FindGridVarState(_T("RowResizeBM_TK"));
		break;
	
	case GRID_RETE:
		m_bEditable = FindGridVarState(_T("EditableRETE"));	
		
		//m_bVirtualMode = FindGridVarState(_T("VirtualModeRETE"));
		//m_bCallback = FindGridVarState(_T("CallbackRETE"));
		
		
		m_bToolTips = FindGridVarState(_T("ToolTipsRETE"));	
		m_bSort = FindGridVarState(_T("SortRETE"));
		m_bCellSelect = FindGridVarState(_T("CellSelectRETE"));
				
		
		m_bHorizontal = FindGridVarState(_T("HorizontalRETE"));
		m_bVertical = FindGridVarState(_T("VerticalRETE"));
		m_bItalic = FindGridVarState(_T("ItalicRETE"));
		m_bBold = FindGridVarState(_T("BoldRETE"));
		m_bNormal = FindGridVarState(_T("NormalRETE"));
		m_bVerticalHeader = FindGridVarState(_T("VerticalHeaderRETE"));
		
		m_bFitGrid = FindGridVarState(_T("FitGridRETE"));
		m_bColumnResize = FindGridVarState(_T("ColumnResizeRETE"));
		m_bRowResize = FindGridVarState(_T("RowResizeRETE"));
		break;
	
	case GRID_INDUCTION:
		m_bEditable = FindGridVarState(_T("EditableInduction"));	
		
		m_bVirtualMode = FindGridVarState(_T("VirtualModeInduction"));
		m_bCallback = FindGridVarState(_T("CallbackInduction"));
		
		
		m_bToolTips = FindGridVarState(_T("ToolTipsInduction"));	
		m_bSort = FindGridVarState(_T("SortInduction"));
		m_bCellSelect = FindGridVarState(_T("CellSelectInduction"));
		
		
		m_bHorizontal = FindGridVarState(_T("HorizontalInduction"));
		m_bVertical = FindGridVarState(_T("VerticalInduction"));
		m_bItalic = FindGridVarState(_T("ItalicInduction"));
		m_bBold = FindGridVarState(_T("BoldInduction"));
		m_bNormal = FindGridVarState(_T("NormalInduction"));
		m_bVerticalHeader = FindGridVarState(_T("VerticalHeaderInduction"));
		
		m_bFitGrid = FindGridVarState(_T("FitGridInduction"));
		m_bColumnResize = FindGridVarState(_T("ColumnResizeInduction"));
		m_bRowResize = FindGridVarState(_T("RowResizeInduction"));
		break;		

	}

	/*		
	CString st;
	st.Format(_T("Editable...%d  " ), m_bEditable);
	AfxMessageBox(st);
	*/

}




int CMainFrame::SelectGrid()
{
	CGridCtrl *m_pGrid;
	

	switch(m_CurrentGrid)
	{
			case GRID_INDUCTION:
				m_pGrid = &m_GridInduction;
				UpdateGridStates(GRID_INDUCTION);
				break;
			case GRID_LHS:
				m_pGrid = &m_GridLHS;
				UpdateGridStates(GRID_LHS);
				break;
            case GRID_RHS:
				m_pGrid = &m_GridRHS;
				UpdateGridStates(GRID_RHS);
				break;
			 
			case GRID_WM:
				m_pGrid = &m_GridWM;
				UpdateGridStates(GRID_WM);
				break;
			case GRID_COND_LINK:
				m_pGrid = &m_GridCondLink;
				UpdateGridStates(GRID_COND_LINK);
				break;
			
			case GRID_AGENDA:
				m_pGrid = &m_GridAgenda;
				UpdateGridStates(GRID_AGENDA);
				break;
			case GRID_AM:
				m_pGrid = &m_GridAM;
				UpdateGridStates(GRID_AM);
				break;
			case GRID_BM:
				m_pGrid = &m_GridBM;
				UpdateGridStates(GRID_BM);
				break;
			case GRID_BM_TK:
				m_pGrid = &m_GridBM_TK;
				UpdateGridStates(GRID_BM_TK);
				break;
			case GRID_RETE:
				m_pGrid = &m_GridRETE;
				UpdateGridStates(GRID_RETE);
				break;
	
	}

	//PrintGrid();	

return m_CurrentGrid;
}


////////////////////////////////////////////////////////////////////////////////////////
				///	CREATES TOOLBARS ///
////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::CreateComboToolBar()
{

	// Add the skinned combo box
	int iCombo = COXCoolToolBar::AddCustomButton(&m_FindCombo, IDC_FINDFILESCOMBO, 160, 100);
	m_wndToolBar.InsertComboBox(m_wndToolBar.CommandToIndex(ID_EDIT_FINDINFILES ) +1, iCombo);
	
}

void CMainFrame::OnSelChangeCombo() 
{
	// Beep when the combo box selection changes
	int iFrequency = (int) m_FindCombo.GetItemData(m_FindCombo.GetCurSel());
	Beep(iFrequency, 100);
	CString sCombo;
	m_FindCombo.GetLBText(m_FindCombo.GetCurSel(), sCombo);
	g_findText = sCombo;
	///AfxMessageBox(g_findText);
}


void CMainFrame::AddComboItem(CString word, int item)
{
	static CFont font;
	if(font.m_hObject == NULL)
		font.CreatePointFont(-80,_T("MS Sans Serif"));


	m_FindCombo.SetFont(&font);

	m_FindCombo.AddString(word);
	m_FindCombo.SetItemData(item, item*100);
	
}


void CMainFrame::SetToolBarArrows()
{

// Set the drop down style
	int iIndexNew = m_wndToolBar.CommandToIndex(ID_FILE_NEW);
	m_wndToolBar.SetButtonStyle(iIndexNew,	m_wndToolBar.GetButtonStyle(iIndexNew) | TBSTYLE_DROPDOWN );
	m_wndToolBar.SetDropDownArrow(TRUE);

	int iIndexOpen = m_wndToolBar.CommandToIndex(ID_FILE_OPEN);
	m_wndToolBar.SetButtonStyle(iIndexOpen,	m_wndToolBar.GetButtonStyle(iIndexOpen) | TBSTYLE_DROPDOWN );
	m_wndToolBar.SetDropDownArrow(TRUE);

}

////////////////////////////////////////////////////////////////////////////////////////	
/// Creates Standard Toolbar ///
/////////////////////////////////////////////////////////////////////////////////////////

BOOL CMainFrame::CreateStandardToolBar()
{

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(2,2,2,2), AFX_IDW_TOOLBAR ) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	//UINT iconsIds[ ]= { IDI_APJ, IDI_FILE_PROJ, IDI_RTF, IDI_SAVE_ALL };
	//m_wndToolBar.SetBitmapIds(iconsIds, IDI_TXT); 
	
	m_wndToolBar.IniSizes(CSize(ID_OXCUSTOMIZE_TBIMAGE_WIDTH, ID_OXCUSTOMIZE_TBIMAGE_HEIGHT));
	m_wndToolBar.UpdateSizes();
	m_wndToolBar.SetWindowText(_T("Standard Toolbar"));
	
	CreateComboToolBar();
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////	
/// Creates Statusbar ///
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateStatusBar()
{
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	//Tooltips
	m_wndStatusBar.SetPaneTip(1, _T("ProgressBar Pane"));
	m_wndStatusBar.SetPaneTip(2, _T("Editor Folding Level"));
	m_wndStatusBar.SetPaneTip(3, _T("Editor Style"));
	m_wndStatusBar.SetPaneTip(4, _T("Editor Position and Character Information"));
	m_wndStatusBar.SetPaneTip(5, _T("Open Documents"));
	m_wndStatusBar.ActivatePaneTips(TRUE);

	
	
	UINT nID, nStyle;
	int cxWidth;
	m_wndStatusBar.GetPaneInfo( 1, nID, nStyle, cxWidth);
	nStyle |= SBPS_PERCENT;
	m_wndStatusBar.SetPaneInfo( 1, nID, nStyle, 100);
	m_wndStatusBar.SetUpBar(1, TRUE, TRUE);
	
	
	return 0;
}



////////////////////////////////////////////////////////////////////////////////////////	
/// Creates Project Toolbar ///
/////////////////////////////////////////////////////////////////////////////////////////
/*
BOOL CMainFrame::CreateProjectToolBar()
{
	if (!m_wndToolBarProject.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarProject.LoadToolBar(IDR_PROJTYPE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	return 0;
}
*/

/*
////////////////////////////////////////////////////////////////////////////////////////	
/// Creates ImageDlg Toolbar ///
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateImageDlgToolBar()
{
	if (!m_wndToolBarImageDlg.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarImageDlg.LoadToolBar(IDR_IMAGEDLG))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////	
/// Creates ImageDlg Toolbar ///
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateCalendarDlgToolBar()
{
	if (!m_wndToolBarCalendarDlg.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarCalendarDlg.LoadToolBar(IDR_CALENDARCTRL))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////	
/// Creates ImageCtrl Toolbar ///
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateImageCtrlToolBar()
{
	if (!m_wndToolBarImageCtrl.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarImageCtrl.LoadToolBar(IDR_IMAGECTRL))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////	
/// Creates NSChartBarCtrl Toolbar ///
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateNSChartBarCtrlToolBar()
{
	if (!m_wndToolBarNSChartBarCtrl.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarNSChartBarCtrl.LoadToolBar(IDR_NSCHART))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////	
/// Creates ChartBarCtrl Toolbar ///
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateChartBarCtrlToolBar()
{
	if (!m_wndToolBarChartBarCtrl.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarChartBarCtrl.LoadToolBar(IDR_CHARTBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////	
/// Creates GraphBarCtrl Toolbar ///
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateGraphBarCtrlToolBar()
{
	if (!m_wndToolBarGraphBarCtrl.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarGraphBarCtrl.LoadToolBar(IDR_GRAPHBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////	
/// Creates StaticMeterCtrl Toolbar ///
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateStaticMeterCtrlToolBar()
{
	if (!m_wndToolBarStaticMeterCtrl.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarStaticMeterCtrl.LoadToolBar(IDR_METERCTRL))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////	
/// Creates ListOptionCtrl Toolbar ///
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateListOptionCtrlToolBar()
{
	if (!m_wndToolBarListOptionCtrl.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarListOptionCtrl.LoadToolBar(IDR_LISTOPTION))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	return 0;
}

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////
				///	CREATES CONTROLS ///
/////////////////////////////////////////////////////////////////////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////////////////////////////
/// Create CPropertiesBar ///
//////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreatePropertiesBar()
{

	
	if (!m_wndPropertiesBar.Create(this, _T("Properties"), IDR_PROPERTYBAR,
		WS_CHILD | WS_VISIBLE | CBRS_LEFT /*| CBRS_SIZE_DYNAMIC */ , CRect(0, 0, 220, 200)))
	{
		TRACE(_T("CMainFrame::OnCreate: failed to create the Properties Bar.\n"));
		return -1;      
	}

	m_wndPropertiesBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndPropertiesBar,AFX_IDW_DOCKBAR_LEFT);

	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates COutputTabBar ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateOutputTabView()
{

	if(!m_wndOutputTabView.Create(this))
	{
		TRACE(_T("CMainFrame::OnCreate: failed to create 3DTabView Bar\n"));
		return -1;      
	} 
	m_wndOutputTabView.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndOutputTabView,AFX_IDW_DOCKBAR_BOTTOM);

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CWorkspaceTabBar ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateWorkspaceTabView()
{

	if(!m_wndWorkspaceTabView.Create(this))
	{
		TRACE(_T("CMainFrame::OnCreate: failed to create 3DTabView Bar\n"));
		return -1;      
	} 
	m_wndWorkspaceTabView.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndWorkspaceTabView,AFX_IDW_DOCKBAR_LEFT);

	return 0;
}
 


//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CInductionTabBar ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateInductionTabView()
{

	if (!m_wndInductionTabView.Create(this, IDD_INDUCTION_FRAME_DLG, CBRS_LEFT, ID_VIEW_INDUCTION_FRAME_DLG))   
	{
		TRACE0("Failed to create image dialog bar\n");
		return -1;      
	}	 
	
	m_wndInductionTabView.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndInductionTabView);	

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CAIPITabBar ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateAIPITabView()
{

	if (!m_wndAIPITabView.Create(this, IDD_AIPI_FRAME_DLG, CBRS_LEFT, ID_VIEW_AIPI_FRAME_DLG))   
	{
		TRACE0("Failed to create image dialog bar\n");
		return -1;      
	}	 
	
	m_wndAIPITabView.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndAIPITabView);	

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CCommandDlgBar ///
//////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateCommandDlgBar()
{

	if (!m_wndCommandDlgBar.Create(this,IDD_COMMAND_DLG, CBRS_BOTTOM|CBRS_SIZE_DYNAMIC, ID_VIEW_COMMANDDLGBAR))
		return -1;
	
	//If you want to dock the dialogbar
	//m_wndCommandDlgBar.EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndCommandDlgBar);
	

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
///Creates  CJukeBoxDlg ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateJukeBoxDlg()
{

	if (!m_wndJukeBoxDlg.Create(this, IDD_JUKEBOX_DLG, CBRS_RIGHT, ID_VIEW_CTRL_JUKEBOXDLG))   
	{
		TRACE0("Failed to create jukebox player dialog bar\n");
		return -1;      
	}	 
	
	m_wndJukeBoxDlg.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndJukeBoxDlg);	

	return 0;
}

//Creates the MediaPlayer dialog bar
//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CMediaPlayerDlg ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateMediaPlayerDlg()
{

	if (!m_wndMediaPlayerDlg.Create(this, IDD_MEDIAPLAYER_DLG, CBRS_RIGHT, ID_VIEW_CTRL_MEDIAPLAYERDLG))   
	{
		TRACE0("Failed to create media player dialog bar\n");
		return -1;      
	}	 
	
	m_wndMediaPlayerDlg.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMediaPlayerDlg);	

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CCalendarDlg ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateCalendarDlg()
{
	
	if (!m_wndCalendarDlg.Create(this, IDD_CALENDAR_DLG, CBRS_RIGHT, ID_VIEW_CTRL_CALENDARDLG))   
	{
		TRACE0("Failed to create image dialog bar\n");
		return -1;      
	}	 
			
	m_wndCalendarDlg.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndCalendarDlg, AFX_IDW_DOCKBAR_RIGHT);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CImageDlg ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateImageDlg()
{

	if (!m_wndImageDlg.Create(this, IDD_IMAGE_DLG, CBRS_RIGHT, ID_VIEW_CTRL_IMAGEDLG))   
	{
		TRACE0("Failed to create image dialog bar\n");
		return -1;      
	}	 
	
	m_wndImageDlg.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndImageDlg);	

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CDxfCadDlg ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateDxfCadDlg()
{

	if (!m_wndDxfCadDlg.Create(this, IDD_DXFCAD_DLG, CBRS_RIGHT, ID_VIEW_CTRL_DXFCADDLG))   
	{
		TRACE0("Failed to create image dialog bar\n");
		return -1;      
	}	 
	
	m_wndDxfCadDlg.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndDxfCadDlg);	

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CImageFilterDlg ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateImageFilterDlg()
{

	if (!m_wndImageFilterDlg.Create(this, IDD_IMAGEFILTER_DLG, CBRS_RIGHT, ID_VIEW_CTRL_IMAGEFILTERDLG))   
	{
		TRACE0("Failed to create image dialog bar\n");
		return -1;      
	}	 
	
	m_wndImageFilterDlg.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndImageFilterDlg);	

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates COleDBDlg ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateOleDBDlg()
{

	if (!m_wndOleDBDlg.Create(this, IDD_OLEDB_DLG, CBRS_RIGHT, ID_VIEW_CTRL_OLEDBDLG))   
	{
		TRACE0("Failed to create image dialog bar\n");
		return -1;      
	}	 
	
	m_wndOleDBDlg.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndOleDBDlg);	

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CImageCtrl ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateImageCtrl()
{
	
	if (!m_wndImageCtrl.Create(this))
		{
		TRACE0("Failed to create static  bar\n");
		return -1;      
		} 
			
	m_wndImageCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndImageCtrl, AFX_IDW_DOCKBAR_RIGHT);
	
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CEditInfoCtrl ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateEditInfoCtrl()
{
	
	if (!m_wndEditInfoCtrl.Create(this))
		{
		TRACE0("Failed to create edit bar\n");
		return -1;      
		} 
			
	m_wndEditInfoCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndEditInfoCtrl, AFX_IDW_DOCKBAR_RIGHT);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CInfoCtrl ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateInfoCtrl()
{
	
	if (!m_wndInfoCtrl.Create(this))
		{
		TRACE0("Failed to create edit bar\n");
		return -1;      
		} 
			
	m_wndInfoCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndInfoCtrl, AFX_IDW_DOCKBAR_RIGHT);
	
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CListOptionCtrl ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateListOptionCtrl()
{
	
	if (!m_wndListOptionCtrl.Create(this))
		{
		TRACE0("Failed to create list box bar\n");
		return -1;      
		} 
			
	m_wndListOptionCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndListOptionCtrl, AFX_IDW_DOCKBAR_RIGHT);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CListMultiOptionCtrl ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateListMultiOptionCtrl()
{
	
	if (!m_wndListMultiOptionCtrl.Create(this))
		{
		TRACE0("Failed to create list ctrl bar\n");
		return -1;      
		} 
			
	m_wndListMultiOptionCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndListMultiOptionCtrl, AFX_IDW_DOCKBAR_RIGHT);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CNSChartBarCtrl ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateNSChartBarCtrl()
{
	
	if (!m_wndNSChartBarCtrl.Create(this))
		{
		TRACE0("Failed to create chart bar bar\n");
		return -1;      
		} 
			
	m_wndNSChartBarCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndNSChartBarCtrl, AFX_IDW_DOCKBAR_RIGHT);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CChartBarCtrl ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateChartBarCtrl()
{
	
	if (!m_wndChartBarCtrl.Create(this))
		{
		TRACE0("Failed to create chart bar bar\n");
		return -1;      
		} 
			
	m_wndChartBarCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndChartBarCtrl, AFX_IDW_DOCKBAR_RIGHT);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CGraphBarCtrl ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateGraphBarCtrl()
{
	
	if (!m_wndGraphBarCtrl.Create(this))
		{
		TRACE0("Failed to create graph bar\n");
		return -1;      
		} 
			
	m_wndGraphBarCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndGraphBarCtrl, AFX_IDW_DOCKBAR_RIGHT);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////
/// Creates CStaticMeterCtrl ///
///////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateStaticMeterCtrl()
{
	
	if (!m_wndStaticMeterCtrl.Create(this))
		{
		TRACE0("Failed to create chart bar bar\n");
		return -1;      
		} 
			
	m_wndStaticMeterCtrl.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndStaticMeterCtrl, AFX_IDW_DOCKBAR_RIGHT);
	
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	MainFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	MainFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::LoadWorkspace() 
{


//Init	OX_CUSTOMIZE_BACKGROUND
#ifdef OX_CUSTOMIZE_BACKGROUND
	VERIFY(m_customizeManager.InitializeBackgroundPainter(TRUE,TRUE,IDB_EMPTY_SCREEN));
#endif


//Init	OX_CUSTOMIZE_CAPTION
#ifdef OX_CUSTOMIZE_CAPTION
	VERIFY(m_customizeManager.InitializeCaptionPainter());
#endif


//Init	OX_CUSTOMIZE_SHORTKEYS
#ifdef OX_CUSTOMIZE_SHORTKEYS
	VERIFY(m_customizeManager.InitializeShortkeys(this));
#endif
	


//Init	OX_CUSTOMIZE_INTELLIMOUSE
#ifdef OX_CUSTOMIZE_INTELLIMOUSE
	VERIFY(m_customizeManager.InitializeIntelliMouse(TRUE,WM_LBUTTONDOWN,KEYPRESSED_SHIFT));
#endif
	

//Init OX_CUSTOMIZE_COOLCONTROLS
#ifdef OX_CUSTOMIZE_COOLCONTROLS
	m_customizeManager.InitializeCoolControls();
#endif 

//Init	OX_CUSTOMIZE_TRAYICON
#ifdef OX_CUSTOMIZE_TRAYICON
	VERIFY(m_customizeManager.InitializeTrayIcon(IDR_MAINFRAME,	IDR_MAINFRAME,_T("Aipi")));
#endif	

	

/*


//Init	OX_CUSTOMIZE_SPLASHWINDOW
#ifdef OX_CUSTOMIZE_SPLASHWINDOW
	m_customizeManager.GetSplashWindow()->Hide();
#endif	

*/

//Init	OX_CUSTOMIZE_WORKSPACE_STATE

#ifdef OX_CUSTOMIZE_WORKSPACE_STATE
	//AfxMessageBox(g_sCurrentDir);
	m_customizeManager.LoadWorkspaceState();


#else
	LoadSizeBarState(_T("SizeBarState"));
	COXWorkspaceState workspaceState;
	switch(g_iWorkspaceStore)
	{
	case AIPI_REGISTRY:
		//AfxMessageBox(_T("Registry"));

		if(!workspaceState.LoadFromRegistry())
		{
			TRACE(_T("CMainFrame::OnClose : Failed to save workspace to registry, continuing\n)"));
		}
		break;
	case AIPI_FILE:
		//AfxMessageBox(_T("File"));
		GetCurrentDirectory( MAX_SIZE_PATH, g_sCurrentDir.GetBufferSetLength(MAX_SIZE_PATH) );
		g_sCurrentDir.ReleaseBuffer();
		g_sCurrentDir = g_sCurrentDir + _T("\\AipiProj1.wsp");
		
		if(!workspaceState.LoadFromFile(g_sCurrentDir))
		{
			TRACE(_T("CMainFrame::OnClose : Failed to load workspace to file, continuing\n)"));
		}
		break;
	}		
	
#endif	


	//AfxMessageBox(_T("End Loading MainFrame Workspace"));
	
	//ProjFileRead( g_projectName, g_projectRoot);
	//WSPTree1Read(g_projectName, g_projectRoot);
	
	g_bNotificationModified = true;	
}



void CMainFrame::SaveWorkspace() 
{


//Init	OX_CUSTOMIZE_WORKSPACE_STATE


m_customizeManager.SaveWorkspaceState();


#ifndef OX_CUSTOMIZE_WORKSPACE_STATE
	//AfxMessageBox(g_sCurrentDir);
	g_sCurrentDir.ReleaseBuffer();

	SaveSizeBarState(_T("SizeBarState"));
	// common procedure to save workspace
	COXWorkspaceState workspaceState;
	switch(g_iWorkspaceStore)
	{
	case AIPI_REGISTRY:
		//AfxMessageBox(_T("Registry"));
		if(!workspaceState.StoreToRegistry())
		{
			TRACE(_T("CMainFrame::OnClose : Failed to save workspace to registry, continuing\n)"));
		}
		break;
	case AIPI_FILE:
		//AfxMessageBox(_T("File"));
		if(!workspaceState.StoreToFile(g_sCurrentDir))
		{
			TRACE(_T("CMainFrame::OnClose : Failed to save workspace to file, continuing\n)"));
		}
		break;
	}

#endif	//	OX_CUSTOMIZE_WORKSPACE_STATE




}







void CMainFrame::CustomizeApp()
{
	

//Init	OX_CUSTOMIZE_TABBEDMDI
#ifdef OX_CUSTOMIZE_TABBEDMDI
	VERIFY(m_customizeManager.InitializeTabbedMDI());
#else
	m_MTIClientWnd.Attach(this);	
#endif


#ifdef OX_CUSTOMIZE_COMMANDS
	COXBitmapMenuOrganizer* pBMOrganizer = m_customizeManager.GetBMOrganizer();
	ASSERT(pBMOrganizer!=NULL);
	//pBMOrganizer->SetMenuBitmap(ID_PROJ_NEW, MAKEINTRESOURCE(IDB_PROJ_NEW));
	//pBMOrganizer->SetMenuBitmap(ID_PROJ_OPEN, MAKEINTRESOURCE(IDB_PROJ_OPEN));
	
	//pBMOrganizer->ExcludeFromRecentlyUsed(ID_FILE_PRINT_SETUP);
	//pBMOrganizer->ExcludeFromRecentlyUsed(ID_FILE_OPEN);
	//pBMOrganizer->ExcludeFromRecentlyUsed(ID_PROJ_OPEN);
	//pBMOrganizer->ExcludeFromRecentlyUsed(AFX_ID_PREVIEW_ZOOMOUT);
	//pBMOrganizer->ExcludeFromRecentlyUsed(AFX_ID_PREVIEW_NEXT);
	
#endif	//

//Init	OX_CUSTOMIZE_COMMANDS
#ifdef OX_CUSTOMIZE_COMMANDS

	VERIFY(m_customizeManager.InitializeCommands());
	pBMOrganizer->SetMenuBitmap(ID_PROJ_NEW, MAKEINTRESOURCE(IDB_PROJ_NEW));
	pBMOrganizer->SetMenuBitmap(ID_PROJ_OPEN, MAKEINTRESOURCE(IDB_PROJ_OPEN));
	
	
	
#else
	COXBitmapMenuOrganizer BMOrganizer;
	BMOrganizer.AttachFrameWnd(this);
	BMOrganizer.AutoSetMenuImage();
	BMOrganizer.SetMenuBitmap(ID_PROJ_NEW, MAKEINTRESOURCE(IDB_PROJ_NEW));
	BMOrganizer.SetMenuBitmap(ID_PROJ_OPEN, MAKEINTRESOURCE(IDB_PROJ_OPEN));
#endif

	

//Init	OX_CUSTOMIZE_TOOLBARS
#ifdef OX_CUSTOMIZE_TOOLBARS

	
	VERIFY(m_customizeManager.InitializeToolbars());
	SetToolBarArrows();
#else
	SetToolBarArrows();

#endif
  
//Init	OX_CUSTOMIZE_INSTANCE_MANAGER
#ifdef OX_CUSTOMIZE_INSTANCE_MANAGER
	VERIFY(m_customizeManager.InitializeInstanceManager());
#endif		

	
//	OX_CUSTOMIZE_SPLASHWINDOW
#ifdef OX_CUSTOMIZE_SPLASHWINDOW
	m_customizeManager.GetSplashWindow()->Hide();
#endif	


}


void CMainFrame::OnClose() 
{
	SaveWorkspace();
	
	
	MainFrameWnd::OnClose();
}


void CMainFrame::OnDropDown(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	// this function handles the dropdown menus from the toolbar
	NMTOOLBAR* pNMToolBar = (NMTOOLBAR*)pNotifyStruct;
	CRect rect;

	// translate the current toolbar item rectangle into screen coordinates
	// so that we'll know where to pop up the menu
	m_wndToolBar.GetItemRect(m_wndToolBar.CommandToIndex(pNMToolBar->iItem), &rect);
	rect.top = rect.bottom;
	::ClientToScreen(pNMToolBar->hdr.hwndFrom, &rect.TopLeft());
	

	CMenu menu;
	CMenu* pPopup;
	

	if (pNMToolBar->iItem == ID_FILE_NEW)
	{

		menu.LoadMenu(IDR_PROJTYPE);
		pPopup = menu.GetSubMenu(0)->GetSubMenu(0);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, rect.left, 
			rect.top + 1, AfxGetMainWnd());
	}
	else if (pNMToolBar->iItem == ID_FILE_OPEN)
	{

		menu.LoadMenu(IDR_PROJTYPE);
		pPopup = menu.GetSubMenu(0)->GetSubMenu(1);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, rect.left, 
			rect.top + 1, AfxGetMainWnd());
	}
	else
	{
		AfxMessageBox(_T("This menu item doesn´t exist"));
		return;
	}

		

*pResult = TBDDRET_DEFAULT; 



}



///////////////////////////////////////////////////////////////////////////////////
	//// Scintilla messages handlers////
////////////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	
	CWinApp* pApp = AfxGetApp();
    ASSERT(pApp);

  //Pass the message on to all scintilla control
  POSITION posTemplate = pApp->GetFirstDocTemplatePosition();
  if (posTemplate)
  {
    CDocTemplate* pTemplate = pApp->GetNextDocTemplate(posTemplate);
    POSITION posDoc = pTemplate->GetFirstDocPosition();
    if (posDoc)
    {
      CDocument* pDocument = pTemplate->GetNextDoc(posDoc);
      if (pDocument)
      {
        POSITION posView = pDocument->GetFirstViewPosition();
        if (posView)
        {
          CScintillaView* pView = static_cast<CScintillaView*>(pDocument->GetNextView(posView));
          if (pView->IsKindOf(RUNTIME_CLASS(CScintillaView)))
          {
            const MSG* pMsg = GetCurrentMessage();
            pView->GetCtrl().SendMessage(WM_SETTINGCHANGE, pMsg->wParam, pMsg->lParam);
          }
        }
      }
    }
  }

  //Let the base class do its thing
	CFrameWnd::OnSettingChange(uFlags, lpszSection);
	
}

void CMainFrame::OnSysColorChange() 
{
	
	CWinApp* pApp = AfxGetApp();
    ASSERT(pApp);

  //Pass the message on to all scintilla control
  POSITION posTemplate = pApp->GetFirstDocTemplatePosition();
  if (posTemplate)
  {
    CDocTemplate* pTemplate = pApp->GetNextDocTemplate(posTemplate);
    POSITION posDoc = pTemplate->GetFirstDocPosition();
    if (posDoc)
    {
      CDocument* pDocument = pTemplate->GetNextDoc(posDoc);
      if (pDocument)
      {
        POSITION posView = pDocument->GetFirstViewPosition();
        if (posView)
        {
          CScintillaView* pView = static_cast<CScintillaView*>(pDocument->GetNextView(posView));
          if (pView->IsKindOf(RUNTIME_CLASS(CScintillaView)))
          {
            const MSG* pMsg = GetCurrentMessage();
            pView->GetCtrl().SendMessage(WM_SYSCOLORCHANGE, pMsg->wParam, pMsg->lParam);
          }
        }
      }
    }
  }

  //Let the base class do its thing
	CFrameWnd::OnSysColorChange();
		
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
	
   CWinApp* pApp = AfxGetApp();
   ASSERT(pApp);

  //Pass the message on to all scintilla control
  POSITION posTemplate = pApp->GetFirstDocTemplatePosition();
  if (posTemplate)
  {
    CDocTemplate* pTemplate = pApp->GetNextDocTemplate(posTemplate);
    POSITION posDoc = pTemplate->GetFirstDocPosition();
    if (posDoc)
    {
      CDocument* pDocument = pTemplate->GetNextDoc(posDoc);
      if (pDocument)
      {
        POSITION posView = pDocument->GetFirstViewPosition();
        if (posView)
        {
          CScintillaView* pView = static_cast<CScintillaView*>(pDocument->GetNextView(posView));
          if (pView->IsKindOf(RUNTIME_CLASS(CScintillaView)))
          {
            const MSG* pMsg = GetCurrentMessage();
            pView->GetCtrl().SendMessage(WM_PALETTECHANGED, pMsg->wParam, pMsg->lParam);
          }
        }
      }
    }
  }

  //Let the base class do its thing
	CFrameWnd::OnPaletteChanged(pFocusWnd);
	
}

BOOL CMainFrame::OnQueryNewPalette() 
{
  
  CWinApp* pApp = AfxGetApp();
  ASSERT(pApp);

  //Pass the message on to all scintilla control
  POSITION posTemplate = pApp->GetFirstDocTemplatePosition();
  if (posTemplate)
  {
    CDocTemplate* pTemplate = pApp->GetNextDocTemplate(posTemplate);
    POSITION posDoc = pTemplate->GetFirstDocPosition();
    if (posDoc)
    {
      CDocument* pDocument = pTemplate->GetNextDoc(posDoc);
      if (pDocument)
      {
        POSITION posView = pDocument->GetFirstViewPosition();
        if (posView)
        {
          CScintillaView* pView = static_cast<CScintillaView*>(pDocument->GetNextView(posView));
          if (pView->IsKindOf(RUNTIME_CLASS(CScintillaView)))
          {
            const MSG* pMsg = GetCurrentMessage();
            pView->GetCtrl().SendMessage(WM_QUERYNEWPALETTE, pMsg->wParam, pMsg->lParam);
          }
        }
      }
    }
  }

  //Let the base class do its thing
	return CFrameWnd::OnQueryNewPalette();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
  /// Manage StatusBar messages ////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateInsert(CCmdUI* pCmdUI)
{
	pCmdUI->SetText(_T(""));
}

void CMainFrame::OnUpdateStyle(CCmdUI* pCmdUI)
{
   pCmdUI->SetText(_T(""));
} 

void CMainFrame::OnUpdateFold(CCmdUI* pCmdUI)
{
  pCmdUI->SetText(_T(""));
} 

void CMainFrame::OnUpdateLine(CCmdUI* pCmdUI)
{
  pCmdUI->SetText(_T(""));
} 

void CMainFrame::OnUpdateDoc(CCmdUI* pCmdUI)
{
  	CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
	
	TCHAR buffer[8];
	int nDoc = pApp->CountOpenDocuments();
	CString sDoc =  _itot( nDoc, buffer, 10 );
	//AfxMessageBox(sDoc);
	
    sDoc.Format(IDS_DOC_INDICATOR, nDoc);
	pCmdUI->Enable(TRUE);
	pCmdUI->SetText(sDoc);
} 




///////////////////////////////////////////////////////////////////////////////////////
/// Menu handlers ////
///////////////////////////////////////////////////////////////////////////////////////


void CMainFrame::OnSettingsCustomize() 
{
	if(!::IsWindow(m_customizeManager.GetSafeHwnd()))
	{
		VERIFY(m_customizeManager.Create(COXCustomizeManager::IDD,this));
	}
	m_customizeManager.ActivatePage(CAPTION_PAINTER);
	m_customizeManager.SetActiveWindow();
	m_customizeManager.ShowWindow(SW_SHOW);

		
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/// SKINS MANAGE ///
//////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::CheckMenuSkinType()
{
	CMenu *pMenu = GetMenu();

	switch(g_iSkinType)
	{
		case OXSkinClassic:
			pMenu->CheckMenuItem(ID_SETTINGS_SKIN_CLASSIC, MF_CHECKED|MF_BYCOMMAND);
			pMenu->CheckMenuItem(ID_SETTINGS_SKIN_OFFICEXP, MF_UNCHECKED|MF_BYCOMMAND);
			pMenu->CheckMenuItem(ID_SETTINGS_SKIN_OFFICE2003, MF_UNCHECKED|MF_BYCOMMAND);
			break;
		case OXSkinOfficeXP:
			pMenu->CheckMenuItem(ID_SETTINGS_SKIN_CLASSIC, MF_UNCHECKED|MF_BYCOMMAND);
			pMenu->CheckMenuItem(ID_SETTINGS_SKIN_OFFICEXP, MF_CHECKED|MF_BYCOMMAND);
			pMenu->CheckMenuItem(ID_SETTINGS_SKIN_OFFICE2003, MF_UNCHECKED|MF_BYCOMMAND);
			break;
		case OXSkinOffice2003:
			pMenu->CheckMenuItem(ID_SETTINGS_SKIN_CLASSIC, MF_UNCHECKED|MF_BYCOMMAND);
			pMenu->CheckMenuItem(ID_SETTINGS_SKIN_OFFICEXP, MF_UNCHECKED|MF_BYCOMMAND);
			pMenu->CheckMenuItem(ID_SETTINGS_SKIN_OFFICE2003, MF_CHECKED|MF_BYCOMMAND);
			break;
		default:
			pMenu->CheckMenuItem(ID_SETTINGS_SKIN_CLASSIC, MF_UNCHECKED|MF_BYCOMMAND);
			pMenu->CheckMenuItem(ID_SETTINGS_SKIN_OFFICEXP, MF_UNCHECKED|MF_BYCOMMAND);
			pMenu->CheckMenuItem(ID_SETTINGS_SKIN_OFFICE2003, MF_UNCHECKED|MF_BYCOMMAND);
			break;
	}

}


void CMainFrame::OnSettingsSkinClassic() 
{
	
	COXSkinnedApp* pSkinnedApp = DYNAMIC_DOWNCAST(COXSkinnedApp, AfxGetApp());
	if (pSkinnedApp != NULL)
	{
		pSkinnedApp->SetCurrentSkin(OXSkinClassic);	
		g_iSkinType = OXSkinClassic;
	}
	
	CRect rect;
	GetClientRect(rect);
	rect.DeflateRect(0, 0);
	m_wndWorkspaceTabView.MoveWindow(&rect);
	m_wndOutputTabView.MoveWindow(&rect);
	
}



void CMainFrame::OnSettingsSkinOfficeXP() 
{
	
	COXSkinnedApp* pSkinnedApp = DYNAMIC_DOWNCAST(COXSkinnedApp, AfxGetApp());
	if (pSkinnedApp != NULL)
	{
		pSkinnedApp->SetCurrentSkin(OXSkinOfficeXP);
		g_iSkinType = OXSkinOfficeXP;
	}

	
	CRect rect;
	GetClientRect(rect);
	rect.DeflateRect(0, 0);
	m_wndWorkspaceTabView.MoveWindow(&rect);
	m_wndOutputTabView.MoveWindow(&rect);


}

void CMainFrame::OnSettingsSkinOffice2003() 
{
	
	COXSkinnedApp* pSkinnedApp = DYNAMIC_DOWNCAST(COXSkinnedApp, AfxGetApp());
	if (pSkinnedApp != NULL)
	{
		pSkinnedApp->SetCurrentSkin(OXSkinOffice2003);
		g_iSkinType = OXSkinOffice2003;
	}

	CRect rect;
	GetClientRect(rect);
	rect.DeflateRect(0, 0);
	m_wndWorkspaceTabView.MoveWindow(&rect);
	m_wndOutputTabView.MoveWindow(&rect);


	
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnViewPropertiesBar() 
{
	
		// Toggle the properties window
	m_wndPropertiesBar.ShowBar(!m_wndPropertiesBar.IsShown());
}

void CMainFrame::OnUpdateViewPropertiesBar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndPropertiesBar.IsShown());	
	
}




void CMainFrame::OnViewOutputTabView() 
{
	ShowControlBar(&m_wndOutputTabView, !m_wndOutputTabView.IsVisible(), FALSE);	
}




void CMainFrame::OnUpdateViewOutputTabView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndOutputTabView.IsVisible());		
	
}

void CMainFrame::OnViewInductionFrameDlg() 
{
	ShowControlBar(&m_wndInductionTabView, !m_wndInductionTabView.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewInductionFrameDlg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndInductionTabView.IsVisible());	
	
}

void CMainFrame::OnViewAipiFrameDlg() 
{
	
	ShowControlBar(&m_wndAIPITabView, !m_wndAIPITabView.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewAipiFrameDlg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndAIPITabView.IsVisible());
	
}

void CMainFrame::OnViewCommandDlgBar() 
{
	ShowControlBar(&m_wndCommandDlgBar, !m_wndCommandDlgBar.IsVisible(), FALSE);	
}


void CMainFrame::OnUpdateViewCommandDlgBar(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndCommandDlgBar.IsVisible());	
}

void CMainFrame::Cmd_OpenCommandDlgBar() 
{
	if ( !m_wndCommandDlgBar.IsVisible())
	{
		ShowControlBar(&m_wndCommandDlgBar, TRUE, FALSE);	
	}
}

void CMainFrame::Cmd_CloseCommandDlgBar() 
{
	if ( m_wndCommandDlgBar.IsVisible())
	{
		ShowControlBar(&m_wndCommandDlgBar, FALSE, FALSE);	
	}
}


void CMainFrame::OnViewCtrlJukeBoxDlg() 
{
		ShowControlBar(&m_wndJukeBoxDlg, !m_wndJukeBoxDlg.IsVisible(), FALSE);	
	
}

void CMainFrame::OnUpdateViewCtrlJukeBoxDlg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndJukeBoxDlg.IsVisible());	
	
}

void CMainFrame::Cmd_OpenJukeBoxDlg() 
{
	if ( !m_wndJukeBoxDlg.IsVisible())
	{
		ShowControlBar(&m_wndJukeBoxDlg, TRUE, FALSE);	
	}
}

void CMainFrame::Cmd_CloseJukeBoxDlg() 
{
	if ( m_wndJukeBoxDlg.IsVisible())
	{
		ShowControlBar(&m_wndJukeBoxDlg, FALSE, FALSE);	
		
	}
}

void CMainFrame::Cmd_PlayJukeBoxDlg() 
{
	m_wndJukeBoxDlg.PlaySelectedFile();
}

void CMainFrame::Cmd_PathJukeBoxDlg(CString strPath) 
{
	m_wndJukeBoxDlg.SetMediaDir(strPath);
}


void CMainFrame::OnViewCtrlMediaPlayerDlg() 
{

	ShowControlBar(&m_wndMediaPlayerDlg, !m_wndMediaPlayerDlg.IsVisible(), FALSE);	
}


void CMainFrame::OnUpdateViewCtrlMediaPlayerDlg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndMediaPlayerDlg.IsVisible());	
	
	
}


void CMainFrame::Cmd_OpenMediaPlayerDlg() 
{
	if ( !m_wndMediaPlayerDlg.IsVisible())
	{
		ShowControlBar(&m_wndMediaPlayerDlg, TRUE, FALSE);	
	}
}

void CMainFrame::Cmd_CloseMediaPlayerDlg() 
{
	if ( m_wndMediaPlayerDlg.IsVisible())
	{
		ShowControlBar(&m_wndMediaPlayerDlg, FALSE, FALSE);	
	}
}

void CMainFrame::Cmd_PlayMediaPlayerDlg() 
{
	m_wndMediaPlayerDlg.PlaySelectedFile();
}

void CMainFrame::Cmd_PathMediaPlayerDlg(CString strPath) 
{
	m_wndMediaPlayerDlg.SetMediaDir(strPath);
}



void CMainFrame::OnViewCtrlImageDlg() 
{
	ShowControlBar(&m_wndImageDlg, !m_wndImageDlg.IsVisible(), FALSE);
	
}

void CMainFrame::OnUpdateViewCtrlImageDlg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndImageDlg.IsVisible());	
	
}

void CMainFrame::OnViewCtrlImageCtrl() 
{
	ShowControlBar(&m_wndImageCtrl, !m_wndImageCtrl.IsVisible(), FALSE);

	//Shows and hides the ImageCtrl toolbar
	/*
	if ( m_wndImageCtrl.IsVisible() == TRUE)
		ShowControlBar(&m_wndToolBarImageCtrl, TRUE ,FALSE);
	else
		ShowControlBar(&m_wndToolBarImageCtrl, FALSE ,TRUE);
		*/
	
}

void CMainFrame::OnUpdateViewCtrlImageCtrl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndImageCtrl.IsVisible());	
	
}

void CMainFrame::OnViewCtrlListOptionCtrl() 
{
	ShowControlBar(&m_wndListOptionCtrl, !m_wndListOptionCtrl.IsVisible(), FALSE);
	
}

void CMainFrame::OnUpdateViewCtrlListOptionCtrl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndListOptionCtrl.IsVisible());	
	
}

void CMainFrame::Cmd_OpenListOptionCtrl() 
{
	if ( !m_wndListOptionCtrl.IsVisible())
	{
		ShowControlBar(&m_wndListOptionCtrl, TRUE, FALSE);	
	}
}

void CMainFrame::Cmd_CloseListOptionCtrl() 
{
	if ( m_wndListOptionCtrl.IsVisible())
	{
		ShowControlBar(&m_wndListOptionCtrl, FALSE, FALSE);	
	}
}

void CMainFrame::Cmd_InsertListOptionCtrl(LPCTSTR lpcItem, LPCTSTR lpcTip) 
{
	m_wndListOptionCtrl.AddItemDirect(lpcItem, lpcTip );
	
}



void CMainFrame::OnViewCtrlNSChartBarCtrl() 
{
	ShowControlBar(&m_wndNSChartBarCtrl, !m_wndNSChartBarCtrl.IsVisible(), FALSE);
	
}

void CMainFrame::OnUpdateViewCtrlNSChartBarCtrl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndNSChartBarCtrl.IsVisible());		
}

void CMainFrame::OnViewCtrlChartBarCtrl() 
{
	ShowControlBar(&m_wndChartBarCtrl, !m_wndChartBarCtrl.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewCtrlChartBarCtrl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndChartBarCtrl.IsVisible());	
}

void CMainFrame::OnViewCtrlCalendarDlg() 
{
	ShowControlBar(&m_wndCalendarDlg, !m_wndCalendarDlg.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewCtrlCalendarDlg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndCalendarDlg.IsVisible());	
}

void CMainFrame::OnViewCtrlStaticMeterCtrl() 
{
	ShowControlBar(&m_wndStaticMeterCtrl, !m_wndStaticMeterCtrl.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewCtrlStaticMeterCtrl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndStaticMeterCtrl.IsVisible());	
}

void CMainFrame::OnViewCtrlImageFilterDlg() 
{
	ShowControlBar(&m_wndImageFilterDlg, !m_wndImageFilterDlg.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewCtrlImageFilterDlg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndImageFilterDlg.IsVisible());	
}

void CMainFrame::Cmd_OpenImageFilterDlg() 
{
	if ( !m_wndImageFilterDlg.IsVisible())
	{
		ShowControlBar(&m_wndImageFilterDlg, TRUE, FALSE);	
	}
}

void CMainFrame::Cmd_CloseImageFilterDlg() 
{
	if ( m_wndImageFilterDlg.IsVisible())
	{
		ShowControlBar(&m_wndImageFilterDlg, FALSE, FALSE);	
	}
}

void CMainFrame::Cmd_PathImageFilterDlg(CString strPath) 
{
	m_wndImageFilterDlg.LoadImage( strPath);	
	
}

void CMainFrame::OnViewCtrlListMultiOptionCtrl() 
{
	ShowControlBar(&m_wndListMultiOptionCtrl, !m_wndListMultiOptionCtrl.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewCtrlListMultiOptionCtrl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndListMultiOptionCtrl.IsVisible());		
}

void CMainFrame::OnViewCtrlGraphBarCtrl() 
{
	ShowControlBar(&m_wndGraphBarCtrl, !m_wndGraphBarCtrl.IsVisible(), FALSE);
}

void CMainFrame::OnUpdateViewCtrlGraphBarCtrl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndGraphBarCtrl.IsVisible());	
}

void CMainFrame::OnViewCtrlEditInfoBar() 
{
	ShowControlBar(&m_wndEditInfoCtrl, !m_wndEditInfoCtrl.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewCtrlEditInfoBar(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndEditInfoCtrl.IsVisible());	
}

void CMainFrame::OnViewCtrlInfoCtrl() 
{
	ShowControlBar(&m_wndInfoCtrl, !m_wndInfoCtrl.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewCtrlInfoCtrl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndInfoCtrl.IsVisible());	
}



void CMainFrame::OnViewWorkSpaceTabView() 
{
	ShowControlBar(&m_wndWorkspaceTabView, !m_wndWorkspaceTabView.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewWorkSpaceTabView(CCmdUI* pCmdUI) 
{
	
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndWorkspaceTabView.IsVisible());
}


void CMainFrame::OnViewCtrlOleDBDlg() 
{
	ShowControlBar(&m_wndOleDBDlg, !m_wndOleDBDlg.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewCtrlOleDBDlg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndOleDBDlg.IsVisible());
	
}

void CMainFrame::Cmd_OpenOleDBDlg() 
{
	if ( !m_wndOleDBDlg.IsVisible())
	{
		ShowControlBar(&m_wndOleDBDlg, TRUE, TRUE);	
	}
}


void CMainFrame::Cmd_CloseOleDBDlg() 
{
	if ( m_wndOleDBDlg.IsVisible())
	{
		ShowControlBar(&m_wndOleDBDlg, FALSE, FALSE);	
	}
}


void CMainFrame::OnViewCtrlDxfCadDlg() 
{
	ShowControlBar(&m_wndDxfCadDlg, !m_wndDxfCadDlg.IsVisible(), FALSE);	
}

void CMainFrame::OnUpdateViewCtrlDxfCadDlg(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(m_wndDxfCadDlg.IsVisible());
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ImageCtrl ToolBar///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*
void CMainFrame::OnViewToolbarImageCtrl() 
{
	
	BOOL bVisible;
	bVisible = ((m_wndToolBarImageCtrl.GetStyle() & WS_VISIBLE) != 0);
	ShowControlBar( &m_wndToolBarImageCtrl, !bVisible, FALSE );
	RecalcLayout();
	
	
	
}

void CMainFrame::OnUpdateViewToolbarImageCtrl(CCmdUI* pCmdUI) 
{
	
	pCmdUI->SetCheck(((m_wndToolBarImageCtrl.GetStyle() & WS_VISIBLE) != 0));	
	
}
*/


void CMainFrame::OnFileSaveAll() 
{

	CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
	pApp->SaveAllOpenDocs();

	
}

void CMainFrame::OnUpdateFileSaveAll(CCmdUI* pCmdUI) 
{
	CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
	if( pApp->CountOpenDocuments() > 0 )
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}



void CMainFrame::OnProjOpen() 
{
	const static _TCHAR BASED_CODE szFilter[] = _T("Project Files (*.apj)|*.apj|All Files (*.*)|*.*||");
	CFileDialog openDlg( TRUE, _T("*.apj"), NULL, OFN_HIDEREADONLY | OFN_EXPLORER, szFilter, NULL );
	
	m_wndOutputTabView.DeleteAllEdit1();
	
	
	if(openDlg.DoModal()==IDOK)
	{	
		CString szFileName( openDlg.GetPathName() );
			
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
		pApp->m_pAIPIProjDocTemplate->CloseAllDocuments(TRUE);	
		pApp->m_pAIPIProjDocTemplate->OpenDocumentFile(szFileName);


		/* 
		CMDIChildWnd * pChild = ((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
			if ( !pChild )
				return;

			pChild->ShowWindow(SW_HIDE );

		*/

			// Add to MRU file list
		((CAIPIApp*)AfxGetApp())->AddToRecentFileList(szFileName);
		
	}

	
	if (m_wndWorkspaceTabView.IsVisible() == FALSE)
	{
		//Set visible at first
		ShowControlBar(&m_wndWorkspaceTabView, TRUE ,TRUE);
		ShowControlBar(&m_wndPropertiesBar, TRUE ,TRUE);
	}
	
	m_wndWorkspaceTabView.m_TabViewContainer.SetActivePageIndex(0);
	
	
	
}
/*
void CMainFrame::OnProjNew() 
{
	CBitmap bmpWatermark;
	CBitmap bmpHeader;

	if( g_iSkinType == OXSkinClassic )
	{
		VERIFY(bmpWatermark.LoadBitmap(IDB_WATERMARK16));
		VERIFY(bmpHeader.LoadBitmap(IDB_BANNER16));
	}
	else  
	{
		VERIFY(bmpWatermark.LoadBitmap(IDB_WATERMARK256));
		VERIFY(bmpHeader.LoadBitmap(IDB_BANNER256));
	}

	CNewProjectSheet dlg(IDS_NEWPROJECTWIZARD, this, 0, bmpWatermark, NULL, bmpHeader);
	if( dlg.DoModal() != IDCANCEL )
	{
		CString sFileName = g_projectName + _T(".apj");
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();

		pApp->m_pAIPIProjDocTemplate->CloseAllDocuments(TRUE);
		pApp->m_pAIPIProjDocTemplate->SaveAllModified();
		pApp->m_pAIPIProjDocTemplate->OpenDocumentFile(NULL);
		
	
		CWorkspaceTabDoc *pDoc = CWorkspaceTabDoc::GetWorkspaceDoc();
		CString sFilePath = g_projectRoot + _T("\\") + sFileName;
		pDoc->ProjectSave(sFilePath);
		pDoc->ProjectClose();
		
		int BufSize = 254;
		LPTSTR lpszProjectName = g_projectName.GetBuffer(BufSize);
		hTProjectRoot = m_wndWorkspaceTabView.AddTreeItem1((HTREEITEM)NULL, lpszProjectName, (HTREEITEM)TVI_ROOT, 0);
		
		pApp->m_pAIPIProjDocTemplate->OpenDocumentFile(sFilePath);
		pApp->m_pAIPIEditorDocTemplate->OpenDocumentFile(NULL);
			
	}

}
*/
void CMainFrame::OnProjNew() 
{
	CWorkspaceTree1 wsp1;
	CWorkspaceLocation wsploc;
	wsp1.clearWSPTree1();
	wsploc.clearLocation();
	
	CBitmap bmpWatermark;
	CBitmap bmpHeader;

	if( g_iSkinType == OXSkinClassic )
	{
		VERIFY(bmpWatermark.LoadBitmap(IDB_WATERMARK16));
		VERIFY(bmpHeader.LoadBitmap(IDB_BANNER16));
	}
	else  
	{
		VERIFY(bmpWatermark.LoadBitmap(IDB_WATERMARK256));
		VERIFY(bmpHeader.LoadBitmap(IDB_BANNER256));
	}

	CNewProjectSheet dlg(IDS_NEWPROJECTWIZARD, this, 0, bmpWatermark, NULL, bmpHeader);
	if( dlg.DoModal() != IDCANCEL )
	{
		CString sFileName = g_projectName + _T(".apj");
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();

		pApp->m_pAIPIProjDocTemplate->CloseAllDocuments(TRUE);
		pApp->m_pAIPIProjDocTemplate->SaveAllModified();
		pApp->m_pAIPIProjDocTemplate->OpenDocumentFile(NULL);
		
		
		
		

	
		CWorkspaceTabDoc *pDoc = CWorkspaceTabDoc::GetWorkspaceDoc();
		CString sFilePath = g_projectRoot + _T("\\") + sFileName;
		pDoc->ProjectSave(sFilePath);
		pDoc->ProjectClose();
		
				
		pApp->m_pAIPIProjDocTemplate->OpenDocumentFile(sFilePath);
		pApp->m_pAIPIEditorDocTemplate->OpenDocumentFile(NULL);
		

		PoblateRuleView();
		
		TCHAR buffer[16];
		//sFilePath = g_projectRoot +  _T("\\") + g_projectName + _T(".prj");
		CString strRoot = _itot( (int)hTProjectRoot, buffer, 10 );
		CString strClass = _itot( (int)hTProjectClass, buffer, 10 );
		CString strFunc = _itot( (int)hTProjectFunction, buffer, 10 );
		CString strQuery = _itot( (int)hTProjectQuery, buffer, 10 );
		CString strRule = _itot( (int)hTProjectRule, buffer, 10 );
		CString strVar = _itot( (int)hTProjectVariable, buffer, 10 );
		
		
		//WSPTree1Write(sFilePath, strRoot, strClass, strFunc, strQuery, strRule, strVar);
		//WSPTree1Read(g_projectName, g_projectRoot);
		
	
		g_bNotificationModified = true;

			
	}

}



void CMainFrame::OnProjClose() 
{
	CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
	pApp->m_pAIPIProjDocTemplate->SaveAllModified();
	pApp->m_pAIPIProjDocTemplate->CloseAllDocuments(TRUE);	
	
	if (m_wndWorkspaceTabView.IsVisible() == TRUE)
	{
		//Set visible at first
		ShowControlBar(&m_wndWorkspaceTabView, FALSE ,FALSE);
		ShowControlBar(&m_wndPropertiesBar, FALSE ,FALSE);	
	}
	
	
}

void CMainFrame::OnProjSave() 
{
	CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
	pApp->m_pAIPIProjDocTemplate->SaveAllModified();
	pApp->SaveAllProjectDocs();
}


void CMainFrame::ProjFileWrite(CString name, CString author, CString desc, CString root, CString date, CString inference, CString resource[4])
{
	
	//AfxMessageBox(_T("WRITE File Project.prj"));
	//AfxMessageBox(name);
	//AfxMessageBox(author);
	//AfxMessageBox(desc);
	//AfxMessageBox(root);
	//AfxMessageBox(date);
	//AfxMessageBox(inference);


	CStdioFile f;
	CFileException e;


	CString pFileName =  root + name + _T(".prj");
	if( !f.Open( pFileName, CFile::modeCreate | CFile::modeWrite, &e ) )
    {
		CAipi_Error err;
		err.displayFileError(FILE_READ, STOP_ERROR, _T("Unable to open file") );
    }


	f.WriteString(name + _T("\n"));
	f.WriteString(author + _T("\n"));
	f.WriteString(desc + _T("\n"));
	f.WriteString(root + _T("\n"));
	f.WriteString(date + _T("\n"));
	f.WriteString(inference + _T("\n"));



	
	for(int i= 0; i<4; ++i)
	{
		switch(i)
		{
		case 0:
			f.WriteString(_T("Images:  ") + resource[i]);
			f.WriteString(_T("\n"));
			break;
		case 1:
			f.WriteString( _T("Videos:  ") + resource[i]);
			f.WriteString(_T("\n"));
			break;
		case 2:
			f.WriteString(_T("DataBases:  ") + resource[i]);
			f.WriteString(_T("\n"));
			break;
		case 3:
			f.WriteString( _T("Others:  ") + resource[i]);
			break;
		}
	}

	
	

}

void CMainFrame::WSPTree1Write(CString filePath, CString hTRoot, CString hTClass, CString hTFunc, CString hTQuery, CString hTRule, CString hTVar )
{
	
	CStdioFile f;
	CFileException e;

	/*
	AfxMessageBox(_T("WRITE Tree1.tr1"));
	AfxMessageBox(hTRoot);
	AfxMessageBox(hTClass);
	AfxMessageBox(hTFunc);
	AfxMessageBox(hTQuery);
	AfxMessageBox(hTRule);
	AfxMessageBox(hTVar);
	*/

	/*
	CString pFileName =  filePath + _T(".tr1");
	if( !f.Open( pFileName, CFile::modeCreate | CFile::modeWrite, &e ) )
    {
		CAipi_Error err;
		err.displayFileError(FILE_READ, STOP_ERROR, _T("Unable to open file") );
    }
	*/

	if( !f.Open( filePath, CFile::modeCreate | CFile::modeWrite, &e ) )
    {
		CAipi_Error err;
		err.displayFileError(FILE_READ, STOP_ERROR, _T("Unable to open file") );
    }

	f.WriteString(hTRoot + _T("\n"));
	f.WriteString(hTClass + _T("\n"));
	f.WriteString(hTFunc + _T("\n"));
	f.WriteString(hTQuery + _T("\n"));
	f.WriteString(hTRule + _T("\n"));
	f.WriteString(hTVar + _T("\n"));


	

}




void CMainFrame::ProjFileRead(CString name, CString root)
{
	CStdioFile f;
	CString strTempText = _T("");
	CString strProjPath = root + name + _T(".prj");

	//AfxMessageBox(_T("READ File Project.prj"));

	//AfxMessageBox(strProjPath);

	if(f.Open(strProjPath, CFile::modeRead, NULL))
	{
		int n = 0;
		while(f.ReadString(strTempText))
		{
			switch(n )
			{
			case 0:
				g_projectName = strTempText;
				//AfxMessageBox(strTempText);
				break;
			case 1:
				g_projectAuthor = strTempText;
				//AfxMessageBox(strTempText);
				break;
			case 2:
				g_projectDesc = strTempText;
				//AfxMessageBox(strTempText);
				break;
			case 3:
				g_projectRoot = strTempText;
				//AfxMessageBox(strTempText);
				break;
			case 4:
				g_projectDate = strTempText;
				//AfxMessageBox(strTempText);
				break;
			case 5:
				g_projectInference = strTempText;
				//AfxMessageBox(strTempText);
				break;
			case 6:
				g_projectResource[0] = strTempText;
				//AfxMessageBox(strTempText);
				break;
			case 7:
				g_projectResource[1] = strTempText;
				//AfxMessageBox(strTempText);
				break;	
			case 8:
				g_projectResource[2] = strTempText;
				//AfxMessageBox(strTempText);
				break;	
			case 9:
				g_projectResource[3] = strTempText;
				//AfxMessageBox(strTempText);
				break;	

			}
			++n;
		}
	}


}


void CMainFrame::WSPTree1Read(CString name, CString root)
{
	CStdioFile f;
	CString strTempText = _T("");
	CString strProjPath = root + name + _T(".tr1");
	
	
	//AfxMessageBox(_T("READ Tree1.tr1"));
	//AfxMessageBox(strProjPath);


	if(f.Open(strProjPath, CFile::modeRead, NULL))
	{
		int n = 0;
		int iItem = 0;
		while(f.ReadString(strTempText))
		{
			switch(n )
			{
				case 0:
					iItem = _ttoi(strTempText);
					hTProjectRoot = (HTREEITEM)iItem;
					//AfxMessageBox(strTempText);
					break;
				case 1:
					iItem = _ttoi(strTempText);
					hTProjectClass = (HTREEITEM)iItem;
					//AfxMessageBox(strTempText);
					break;
				case 2:
					iItem = _ttoi(strTempText);
					hTProjectFunction = (HTREEITEM)iItem;
					//AfxMessageBox(strTempText);
					break;
				case 3:
					iItem = _ttoi(strTempText);
					hTProjectQuery = (HTREEITEM)iItem;
					//AfxMessageBox(strTempText);
					break;
				case 4:
					iItem = _ttoi(strTempText);
					hTProjectRule = (HTREEITEM)iItem;
					//AfxMessageBox(strTempText);
					break;
				case 5:
					iItem = _ttoi(strTempText);
					hTProjectVariable = (HTREEITEM)iItem;
					//AfxMessageBox(strTempText);
					break;
			
			}
			++n;
		}
	}


}


int CMainFrame::ProjFileFind(CString name, CString root, CString txt)
{
	CStdioFile f;
	CString strTempText = _T("");
	CString strProjPath = root + name + _T(".prj");
	//AfxMessageBox(strProjPath);

	if(f.Open(strProjPath, CFile::modeRead, NULL))
	{
		int n = 0;
		while(f.ReadString(strTempText))
		{
			if( strTempText.Find(txt) != LB_ERR )
			{
				 
				//you have found "txt"
				// do stuff
				return FOUND;
			}
		}
	}

return NOT_FOUND;			

}




void CMainFrame::PoblateRuleView()
{
	int BufSize = 254;

	m_wndWorkspaceTabView.m_treeCtrl1.DeleteAllItems();

	CString sProject = _T("Project ") + g_projectName;
	LPTSTR lpszProjectName = sProject.GetBuffer(BufSize);
	hTProjectRoot = m_wndWorkspaceTabView.AddTreeItem1((HTREEITEM)NULL, lpszProjectName, (HTREEITEM)TVI_ROOT, 0);

	CString sClasses = g_projectName + _T(" Classes");
	LPTSTR lpszProjectClasses = sClasses.GetBuffer(BufSize);
	hTProjectClass = m_wndWorkspaceTabView.AddTreeItem1(hTProjectRoot, lpszProjectClasses, (HTREEITEM)TVI_SORT, 20);

	CString sFunctions = g_projectName + _T(" Functions");
	LPTSTR lpszProjectFunctions = sFunctions.GetBuffer(BufSize);
	hTProjectFunction = m_wndWorkspaceTabView.AddTreeItem1(hTProjectRoot, lpszProjectFunctions, (HTREEITEM)TVI_SORT, 16);

	CString sQuerys = g_projectName + _T(" Queries");
	LPTSTR lpszProjectQuerys = sQuerys.GetBuffer(BufSize);
	hTProjectQuery = m_wndWorkspaceTabView.AddTreeItem1(hTProjectRoot, lpszProjectQuerys, (HTREEITEM)TVI_SORT, 18);
	
	CString sRules = g_projectName + _T(" Rules");
	LPTSTR lpszProjectRules = sRules.GetBuffer(BufSize);
	hTProjectRule = m_wndWorkspaceTabView.AddTreeItem1(hTProjectRoot, lpszProjectRules, (HTREEITEM)TVI_SORT, 22);
	
	CString sVariables = g_projectName + _T(" Variables");
	LPTSTR lpszProjectVariables = sVariables.GetBuffer(BufSize);
	hTProjectVariable = m_wndWorkspaceTabView.AddTreeItem1(hTProjectRoot, lpszProjectVariables, (HTREEITEM)TVI_SORT, 24);

	m_wndWorkspaceTabView.m_treeCtrl1.Expand(hTProjectRoot ,TVE_EXPAND);

	/*
	CString str;
	str.Format(_T("Ini HTREEITEM...%d  " ), TVI_ROOT);
	AfxMessageBox(str);
	str.Format(_T("Root HTREEITEM...%d  " ), hTProjectRoot);
	AfxMessageBox(str);
	str.Format(_T("Class HTREEITEM...%d  " ), hTProjectClass);
	AfxMessageBox(str);
	str.Format(_T("Function HTREEITEM...%d  " ), hTProjectFunction);
	AfxMessageBox(str);
	str.Format(_T("Query HTREEITEM...%d  " ), hTProjectQuery);
	AfxMessageBox(str);
	str.Format(_T("Rule HTREEITEM...%d  " ), hTProjectRule);
	AfxMessageBox(str);
	str.Format(_T("Variable HTREEITEM...%d  " ), hTProjectVariable);
	AfxMessageBox(str);
	*/
	
}




void CMainFrame::OnAppExit() 
{
	
	//AfxMessageBox(g_projectName);

	if( g_projectName != _T("") && g_projectRoot != _T("") )
	{
		
		//Save Workspace on Exit
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();

		CString sFileName = g_projectName + _T(".apj");
		CString sFilePath = g_projectRoot + _T("\\") + sFileName;
		//AfxMessageBox(sFilePath);

		pApp->m_pAIPIProjDocTemplate->OpenDocumentFile(sFilePath);
		CWorkspaceTabDoc *pDoc = CWorkspaceTabDoc::GetWorkspaceDoc();
		pDoc->ProjectSave(sFilePath);
		pDoc->ProjectClose();
	}

	ASSERT(AfxGetApp()->m_pMainWnd != NULL);
    AfxGetApp()->m_pMainWnd->SendMessage(WM_CLOSE);

}
