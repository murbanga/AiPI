// PageOptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "PageOptionsDlg.h"
#include "InductionTabView.h"

#include "MainFrm.h"

#include ".\GridCtrl\GridCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageOptionsDlg dialog


CPageOptionsDlg::CPageOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPageOptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageOptionsDlg)

	//}}AFX_DATA_INIT
}


void CPageOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageOptionsDlg)
	DDX_Control(pDX, IDC_STATIC_SORT, m_stcSeparator);
	DDX_Control(pDX, IDC_STATIC_FOCUS, m_stcFocus);
	DDX_Control(pDX, IDC_CHK_TOOLTIPS, m_chkToolTips);
	DDX_Control(pDX, IDC_CHK_SORT, m_chkSort);
	DDX_Control(pDX, IDC_CHECK_CELLSELECT, m_chkCellSelect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(CPageOptionsDlg)
	ON_BN_CLICKED(IDC_CHK_TOOLTIPS, OnChkToolTips)
	ON_BN_CLICKED(IDC_CHK_SORT, OnChkSort)
	ON_BN_CLICKED(IDC_CHECK_CELLSELECT, OnCheckCellSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageOptionsDlg message handlers

/*

void CPageOptionsDlg::SelectGrid()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	switch(pMainFrame->m_CurrentGrid)
	{
			case GRID_INDUCTION:
				m_pGrid = &pMainFrame->m_GridInduction;
				break;
			case GRID_PM:
				m_pGrid = &pMainFrame->m_GridPM;
				break;
				case GRID_WM:
				m_pGrid = &pMainFrame->m_GridWM;
				break;
			case GRID_AGENDA:
				m_pGrid = &pMainFrame->m_GridAgenda;
				break;
			case GRID_AM:
				m_pGrid = &pMainFrame->m_GridAM;
				break;
			case GRID_BM:
				m_pGrid = &pMainFrame->m_GridBM;
				break;
			case GRID_RETE:
				m_pGrid = &pMainFrame->m_GridRETE;
				break;
	
	}


}

*/


void CPageOptionsDlg::OnChkToolTips() 
{
	

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int currentGrid =  pMainFrame->SelectGrid();
	
	m_pGrid->EnableTitleTips(!pMainFrame->m_bToolTips);
	m_pGrid->Invalidate();

	if( pMainFrame->m_bToolTips == 0)
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("ToolTipsLHS"), true);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("ToolTipsRHS"), true);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("ToolTipsWM"), true);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("ToolTipsCLink"), true);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("ToolTipsAgenda"), true);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("ToolTipsAM"), true);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("ToolTipsBM"), true);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("ToolTipsBM_TK"), true);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("ToolTipsRETE"), true);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("ToolTipsInduction"), true);
			break;	
		}//end switch
	}
	else 
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("ToolTipsLHS"), false);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("ToolTipsRHS"), false);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("ToolTipsWM"), false);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("ToolTipsCLink"), false);
			break;
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("ToolTipsAgenda"), false);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("ToolTipsAM"), false);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("ToolTipsBM"), false);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("ToolTipsBM_TK"), false);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("ToolTipsRETE"), false);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("ToolTipsInduction"), false);
			break;	
		}
	}
	

    	
}

void CPageOptionsDlg::OnChkSort() 
{
	

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int currentGrid =  pMainFrame->SelectGrid();
	
	m_pGrid->SetHeaderSort(!pMainFrame->m_bSort);
	m_pGrid->Invalidate();

	if( pMainFrame->m_bSort == 0)
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("SortLHS"), true);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("SortRHS"), true);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("SortWM"), true);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("SortCLink"), true);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("SortAgenda"), true);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("SortAM"), true);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("SortBM"), true);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("SortBM_TK"), true);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("SortRETE"), true);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("SortInduction"), true);
			break;	
		}//end switch
	}
	else 
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("SortLHS"), false);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("SortRHS"), false);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("SortWM"), false);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("SortCLink"), false);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("SortAgenda"), false);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("SortAM"), false);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("SortBM"), false);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("SortBM_TK"), false);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("SortRETE"), false);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("SortInduction"), false);
			break;	
		}
	}
    
}


    
void CPageOptionsDlg::OnCheckCellSelect() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	int currentGrid =  pMainFrame->SelectGrid();
	
	//pMainFrame->m_bCellSelect = !pMainFrame->m_bCellSelect;
	//int state = m_chkCellSelect.GetCheck();
	m_pGrid->EnableSelection(!pMainFrame->m_bCellSelect);

	if( pMainFrame->m_bCellSelect == 0)
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("CellSelectLHS"), true);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("CellSelectRHS"), true);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("CellSelectWM"), true);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("CellSelectCLink"), true);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("CellSelectAgenda"), true);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("CellSelectAM"), true);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("CellSelectBM"), true);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("CellSelectBM_TK"), true);
			break;
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("CellSelectRETE"), true);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("CellSelectInduction"), true);
			break;	
		}//end switch
	}
	else 
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("CellSelectLHS"), false);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("CellSelectRHS"), false);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("CellSelectWM"), false);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("CellSelectCLink"), false);
			break;
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("CellSelectAgenda"), false);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("CellSelectAM"), false);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("CellSelectBM"), false);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("CellSelectBM_TK"), false);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("CellSelectRETE"), false);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("CellSelectInduction"), false);
			break;	
		}
	}

	
	
    
}



BOOL CPageOptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//m_chkToolTips.SetCheck(true);
	//m_chkSort.SetCheck(false);
	//m_chkFocusTrack.SetCheck(false);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
