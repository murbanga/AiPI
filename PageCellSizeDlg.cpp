// PageCellSizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "PageCellSizeDlg.h"
#include "InductionTabView.h"
#include ".\GridCtrl\GridCtrl.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageCellSizeDlg dialog


CPageCellSizeDlg::CPageCellSizeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPageCellSizeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageCellSizeDlg)
	
	//}}AFX_DATA_INIT
}


void CPageCellSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageCellSizeDlg)
	DDX_Control(pDX, IDC_CHK_COLUMNRESIZE, m_chkColumnResize);
	DDX_Control(pDX, IDC_CHK_FITGRID, m_chkFitGrid);
	DDX_Control(pDX, IDC_CHK_ROWRESIZE, m_chkRowResize);
	DDX_Control(pDX, IDC_STATIC_SEPARATOR, m_stcSeparator);
	DDX_Control(pDX, IDC_BTN_EXPANDCOLUMN, m_btnExpandCol);
	DDX_Control(pDX, IDC_BTN_AUTOSIZE, m_btnAutosize);
	DDX_Control(pDX, IDC_BTN_AUTOFILLGRID, m_btnAutofill);
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageCellSizeDlg, CDialog)
	//{{AFX_MSG_MAP(CPageCellSizeDlg)
	ON_BN_CLICKED(IDC_BTN_AUTOFILLGRID, OnBtnAutoFillGrid)
	ON_BN_CLICKED(IDC_BTN_AUTOSIZE, OnBtnAutoSize)
	ON_BN_CLICKED(IDC_BTN_EXPANDCOLUMN, OnBtnExpandColumn)
	ON_BN_CLICKED(IDC_CHK_ROWRESIZE, OnChkRowResize)
	ON_BN_CLICKED(IDC_CHK_COLUMNRESIZE, OnChkColumnResize)
	ON_BN_CLICKED(IDC_CHK_FITGRID, OnChkFitGrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageCellSizeDlg message handlers
/*
void CPageCellSizeDlg::SelectGrid()
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
void CPageCellSizeDlg::OnBtnAutoFillGrid() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->SelectGrid();
	//m_pGrid->DeleteAllItems();
    m_pGrid->AutoFill();
	
}

void CPageCellSizeDlg::OnBtnAutoSize() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	m_pGrid->AutoSize();
}

void CPageCellSizeDlg::OnBtnExpandColumn() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	m_pGrid->ExpandLastColumn();	
}



void CPageCellSizeDlg::OnChkRowResize() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int currentGrid =  pMainFrame->SelectGrid();
	
	//pMainFrame->m_bRowResize = !pMainFrame->m_bRowResize;
	//int state = m_chkRowSize.GetCheck();
	m_pGrid->SetRowResize(!pMainFrame->m_bRowResize);


	if( pMainFrame->m_bRowResize == 0)
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("RowResizeLHS"), true);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("RowResizeRHS"), true);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("RowResizeWM"), true);
			break;	
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("RowResizeCLink"), true);
			break;
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("RowResizeAgenda"), true);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("RowResizeAM"), true);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("RowResizeBM"), true);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("RowResizeBM_TK"), true);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("RowResizeRETE"), true);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("RowResizeInduction"), true);
			break;	
		}//end switch
	}
	else 
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("RowResizeLHS"), false);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("RowResizeRHS"), false);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("RowResizeWM"), false);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("RowResizeCLink"), false);
			break;
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("RowResizeAgenda"), false);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("RowResizeAM"), false);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("RowResizeBM"), false);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("RowResizeBM_TK"), false);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("RowResizeRETE"), false);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("RowResizeInduction"), false);
			break;	
		}
	}

	
    	
}

void CPageCellSizeDlg::OnChkColumnResize() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int currentGrid =  pMainFrame->SelectGrid();
	
	//pMainFrame->m_bColumnResize = !pMainFrame->m_bColumnResize;
	//int state = m_chkColumnResize.GetCheck();
	m_pGrid->SetColumnResize(!pMainFrame->m_bColumnResize);


	if( pMainFrame->m_bColumnResize == 0)
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeLHS"), true);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeRHS"), true);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeWM"), true);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeCLink"), true);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeAgenda"), true);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeAM"), true);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeBM"), true);
			break;	
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeBM_TK"), true);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeRETE"), true);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeInduction"), true);
			break;	
		}//end switch
	}
	else 
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeLHS"), false);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeRHS"), false);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeWM"), false);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeCLink"), false);
			break;
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeAgenda"), false);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeAM"), false);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeBM"), false);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeBM_TK"), false);
			break;
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeRETE"), false);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("ColumnResizeInduction"), false);
			break;	
		}
	}

	
	
    	
}

void CPageCellSizeDlg::OnChkFitGrid() 
{
	
	

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int currentGrid =  pMainFrame->SelectGrid();
	
	//pMainFrame->m_bFitGrid = !pMainFrame->m_bFitGrid;
	//int state = m_chkFitGrid.GetCheck();
	m_pGrid->ExpandToFit(!pMainFrame->m_bFitGrid);


	if( pMainFrame->m_bFitGrid == 0)
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("FitGridLHS"), true);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("FitGridRHS"), true);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("FitGridWM"), true);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("FitGridCLink"), true);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("FitGridAgenda"), true);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("FitGridAM"), true);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("FitGridBM"), true);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("FitGridBM_TK"), true);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("FitGridRETE"), true);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("FitGridInduction"), true);
			break;	
		}//end switch
	}
	else 
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("FitGridLHS"), false);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("FitGridRHS"), false);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("FitGridWM"), false);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("FitGridCLink"), false);
			break;
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("FitGridAgenda"), false);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("FitGridAM"), false);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("FitGridBM"), false);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("FitGridBM_TK"), false);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("FitGridRETE"), false);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("FitGridInduction"), false);
			break;	
		}
	}

	
}

BOOL CPageCellSizeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	m_chkColumnResize.SetCheck(TRUE);
	m_chkRowResize.SetCheck(TRUE);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
