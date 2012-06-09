// PageInsertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "PageInsertDlg.h"

#include "MainFrm.h"

#include ".\GridCtrl\GridCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageInsertDlg dialog


CPageInsertDlg::CPageInsertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPageInsertDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageInsertDlg)
		// NOTE: the ClassWizard will add member initialization here
	
	//}}AFX_DATA_INIT
	
}


void CPageInsertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageInsertDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_EDIT_NROWS, m_editRows);
	DDX_Control(pDX, IDC_EDIT_NFIXROWS, m_editFixedRows);
	DDX_Control(pDX, IDC_EDIT_NFIXCOLS, m_editFixedColumns);
	DDX_Control(pDX, IDC_EDIT_NCOLS, m_editColumns);
	DDX_Control(pDX, IDC_SPIN_NROWS, m_spnRows);
	DDX_Control(pDX, IDC_SPIN_NFIXROWS, m_spnFixedRows);
	DDX_Control(pDX, IDC_SPIN_NFIXCOLS, m_spnFixedColumns);
	DDX_Control(pDX, IDC_SPIN_NCOLS, m_spnColumns);
	DDX_Control(pDX, IDC_STATIC_NCELLS, m_stcNoCells);
	DDX_Text(pDX, IDC_EDIT_NCOLS, m_nMaxCols);
	DDX_Text(pDX, IDC_EDIT_NFIXCOLS, m_nMaxFixCols);
	DDX_Text(pDX, IDC_EDIT_NFIXROWS, m_nMaxFixRows);
	DDX_Text(pDX, IDC_EDIT_NROWS, m_nMaxRows);

	DDX_Control(pDX, IDC_BTN_DELETEROW, m_btnDeleteRow);
	DDX_Control(pDX, IDC_BTN_INSERTROW, m_btnInsertRow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageInsertDlg, CDialog)
	//{{AFX_MSG_MAP(CPageInsertDlg)
	ON_EN_UPDATE(IDC_EDIT_NROWS, OnUpdateEditNRows)
	ON_EN_UPDATE(IDC_EDIT_NCOLS, OnUpdateEditNCols)
	ON_EN_UPDATE(IDC_EDIT_NFIXROWS, OnUpdateEditNFixRows)
	ON_EN_UPDATE(IDC_EDIT_NFIXCOLS, OnUpdateEditNFixCols)
	ON_BN_CLICKED(IDC_BTN_DELETEROW, OnBtnDeleteRow)
	ON_BN_CLICKED(IDC_BTN_INSERTROW, OnBtnInsertRow)
	ON_BN_CLICKED(IDC_BTN_INSERTCOL, OnBtnInsertColumn)
	ON_BN_CLICKED(IDC_BTN_DELETECOL, OnBtnDeleteColumn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageInsertDlg message handlers

BOOL CPageInsertDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	// init spin controls
	m_spnRows.SetBuddy(&m_editRows);
	m_spnRows.SetRange(0, 9999);
	m_spnRows.SetPos(g_iRow);
	m_spnRows.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	m_spnColumns.SetBuddy(&m_editColumns);
	m_spnColumns.SetRange(0, 9999);
	m_spnColumns.SetPos(g_iColumn);
	m_spnColumns.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);


	m_spnFixedRows.SetBuddy(&m_editFixedRows);
	m_spnFixedRows.SetRange(0, 9999);
	m_spnFixedRows.SetPos(g_iFixRow);
	m_spnFixedRows.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);


	m_spnFixedColumns.SetBuddy(&m_editFixedColumns);
	m_spnFixedColumns.SetRange(0, 9999);
	m_spnFixedColumns.SetPos(g_iFixColumn);
	m_spnFixedColumns.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	m_nMaxRows = g_iRow;
	m_nMaxCols = g_iColumn;
	m_nMaxFixRows = g_iFixRow;
	m_nMaxFixCols = g_iFixColumn;
	UpdateData(false);

/*
	m_spnRows.SetRange(0,9999);
	m_spnColumns.SetRange(0,9999);
	m_spnFixedRows.SetRange(0,9999);
	m_spnFixedColumns.SetRange(0,9999);
*/
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*

void CPageInsertDlg::SelectGrid()
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

void CPageInsertDlg::UpdateEditControls()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	
	if (!::IsWindow(m_pGrid->m_hWnd)) 
	return;
	UpdateData();
	
	m_nMaxRows = m_pGrid->GetRowCount();
	m_nMaxCols = m_pGrid->GetColumnCount();
	m_nMaxFixRows = m_pGrid->GetFixedRowCount();
	m_nMaxFixCols = m_pGrid->GetFixedColumnCount();
	
	UpdateData(FALSE);
	
}


void CPageInsertDlg::OnUpdateEditNRows() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	if (!::IsWindow(m_pGrid->m_hWnd)) 
	return;
	
	UpdateData();

    int nOldNumRows = m_pGrid->GetRowCount();

	
	TRY {
        m_pGrid->SetRowCount(m_nMaxRows); 
    }
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
    END_CATCH

	m_nMaxRows = m_pGrid->GetRowCount();
	m_nMaxFixRows = m_pGrid->GetFixedRowCount();
	UpdateData(FALSE);

    CString str;
    for (int i = nOldNumRows; i < m_nMaxRows; i++)
    {
        str.Format(_T("Row %d"), i);
        m_pGrid->SetItemText(i,0,str);
    }
	
	
	
	
}

void CPageInsertDlg::OnUpdateEditNCols() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	
	pMainFrame->SelectGrid();
	
	if (!::IsWindow(m_pGrid->m_hWnd)) 
	return;
	UpdateData();

    int nOldNumCols = m_pGrid->GetColumnCount();

	TRY { 
        m_pGrid->SetColumnCount(m_nMaxCols); 
    }
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
    END_CATCH

	m_nMaxCols = m_pGrid->GetColumnCount();
	m_nMaxFixCols = m_pGrid->GetFixedColumnCount();
	UpdateData(FALSE);

    CString str;
    for (int i = nOldNumCols; i < m_nMaxCols; i++)
    {
        str.Format(_T("Column %d"), i);
        m_pGrid->SetItemText(0,i,str);
    }
	
	
}

void CPageInsertDlg::OnUpdateEditNFixRows() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();	
	
	if (!::IsWindow(m_pGrid->m_hWnd)) 
	return;
	UpdateData();

	TRY {
        m_pGrid->SetFixedRowCount(m_nMaxFixRows); 
    }
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
    END_CATCH

	m_nMaxRows = m_pGrid->GetRowCount();
	m_nMaxFixRows = m_pGrid->GetFixedRowCount();
	UpdateData(FALSE);
	
	
}

void CPageInsertDlg::OnUpdateEditNFixCols() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	
	if (!::IsWindow(m_pGrid->m_hWnd)) 
	return;
	UpdateData();

	TRY {
        m_pGrid->SetFixedColumnCount(m_nMaxFixCols); 
    }
	CATCH (CMemoryException, e)
	{
		e->ReportError();
		return;
	}
    END_CATCH

	m_nMaxCols = m_pGrid->GetColumnCount();
	m_nMaxFixCols = m_pGrid->GetFixedColumnCount();
	UpdateData(FALSE);		
	
	
}



void CPageInsertDlg::OnBtnInsertRow() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	int nRow = m_pGrid->GetFocusCell().row;
    if (nRow >= 0)
    {
	    m_pGrid->InsertRow(_T("Newest Row"), nRow);	
	    m_pGrid->Invalidate();
    }

}

void CPageInsertDlg::OnBtnDeleteRow() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	int nRow = m_pGrid->GetFocusCell().row;
    if (nRow >= 0)
    {
	    m_pGrid->DeleteRow(nRow);	
	    m_pGrid->Invalidate();
    }
	
}

void CPageInsertDlg::OnBtnInsertColumn() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	int nCol = m_pGrid->GetFocusCell().col;
    if (nCol >= 0)
    {
	    m_pGrid->InsertColumn(_T("Newest Column"), DT_CENTER, nCol);	
	    m_pGrid->Invalidate();
    }
	

	
}


void CPageInsertDlg::OnBtnDeleteColumn() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	int nCol = m_pGrid->GetFocusCell().col;
    if (nCol >= 0)
    {
	    m_pGrid->DeleteColumn(nCol);	
	    m_pGrid->Invalidate();
    }	
	
}
