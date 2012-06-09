// PageEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "PageEditDlg.h"
#include "InductionTabView.h"
#include "AIPITabView.h"
#include ".\GridCtrl\GridCtrl.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageEditDlg dialog


CPageEditDlg::CPageEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPageEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPageEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageEditDlg)
	
	DDX_Control(pDX, IDC_STATIC_SEPARATOR, m_stcSeparator);
	DDX_Control(pDX, IDC_STATIC_MODE, m_stcMode);
	DDX_Control(pDX, IDC_BTN_SELECTALL, m_btnSelectAll);
	DDX_Control(pDX, IDC_BTN_PASTE, m_btnPaste);
	DDX_Control(pDX, IDC_BTN_CUT, m_btnCut);
	DDX_Control(pDX, IDC_BTN_COPY, m_btnCopy);
	DDX_Control(pDX, IDC_RADIO_READ, m_radioRead);
	DDX_Control(pDX, IDC_RADIO_WRITE, m_radioWrite);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageEditDlg, CDialog)
	//{{AFX_MSG_MAP(CPageEditDlg)
	
	ON_BN_CLICKED(IDC_BTN_COPY, OnBtnCopy)
	ON_BN_CLICKED(IDC_BTN_CUT, OnBtnCut)
	ON_BN_CLICKED(IDC_BTN_PASTE, OnBtnPaste)
	ON_BN_CLICKED(IDC_BTN_SELECTALL, OnBtnSelectAll)
	ON_BN_CLICKED(IDC_RADIO_READ, OnRadioRead)
	ON_BN_CLICKED(IDC_RADIO_WRITE, OnRadioWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageEditDlg message handlers
BOOL CPageEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_radioRead.SetCheck(TRUE);
	//m_radioRead.EnableWindow(FALSE);
	//m_radioWrite.EnableWindow(FALSE);
	
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*
void CPageEditDlg::SelectGrid()
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

#ifndef GRIDCONTROL_NO_CLIPBOARD

void CPageEditDlg::OnBtnCopy() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	m_pGrid->OnEditCopy();
	

	
}

void CPageEditDlg::OnBtnCut() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	m_pGrid->OnEditCut();

}

void CPageEditDlg::OnBtnPaste() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	m_pGrid->OnEditPaste();		
}

void CPageEditDlg::OnUpdateEditCopyOrCut(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	pCmdUI->Enable(m_pGrid->GetSelectedCount() > 0);
	m_btnCopy.EnableWindow(m_pGrid->GetSelectedCount() > 0);
	m_btnCut.EnableWindow(m_pGrid->GetSelectedCount() > 0);
}

void CPageEditDlg::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
    // Attach a COleDataObject to the clipboard see if there is any data
    COleDataObject obj;
    pCmdUI->Enable(obj.AttachClipboard() && obj.IsDataAvailable(CF_TEXT));
	m_btnPaste.EnableWindow(obj.AttachClipboard() && obj.IsDataAvailable(CF_TEXT));

}

#endif


void CPageEditDlg::OnBtnSelectAll() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	m_pGrid->OnEditSelectAll();	
}

void CPageEditDlg::OnRadioRead() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	COLORREF clr = RGB(255, 255, 220);
	int currentGrid= pMainFrame->SelectGrid();
	
	m_pGrid->SetEditable(FALSE);
	
	
	switch(currentGrid)
	{
	case GRID_LHS:
		pMainFrame->ChangeGridVarState(_T("EditableLHS"), false);
		break;
	case GRID_RHS:
		pMainFrame->ChangeGridVarState(_T("EditableRHS"), false);
		break;	
	case GRID_WM:
		pMainFrame->ChangeGridVarState(_T("EditableWM"), false);
		break;
	case GRID_COND_LINK:
		pMainFrame->ChangeGridVarState(_T("EditableCLink"), false);
		break;	
	case GRID_AGENDA:
		pMainFrame->ChangeGridVarState(_T("EditableAgenda"), false);
		break;
	case GRID_AM:
		pMainFrame->ChangeGridVarState(_T("EditableAM"), false);
		break;	
	case GRID_BM:
		pMainFrame->ChangeGridVarState(_T("EditableBM"), false);
		break;
	case GRID_BM_TK:
		pMainFrame->ChangeGridVarState(_T("EditableBM_TK"), false);
		break;
	case GRID_RETE:
		pMainFrame->ChangeGridVarState(_T("EditableRETE"), false);
		break;
	case GRID_INDUCTION:
		pMainFrame->ChangeGridVarState(_T("EditableInduction"), false);
		break;	


	}//end switch


	for (int row = m_pGrid->GetFixedRowCount(); row < m_pGrid->GetRowCount(); row++)
     {
	   	for (int col = m_pGrid->GetFixedColumnCount(); col < m_pGrid->GetColumnCount(); col++)
	    { 
			 
			 m_pGrid->SetItemBkColour(row, col, clr);
             //m_pGrid->SetItemFgColour(row, col, RGB(0,0,0));				    
             
    	}
	}
	
	m_pGrid->Invalidate();
	
}

void CPageEditDlg::OnRadioWrite() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	COLORREF clr = RGB(255, 255, 255);
	int f = NOT_FOUND;
	int currentGrid = pMainFrame->SelectGrid();
	
	m_pGrid->SetEditable(TRUE);	

	switch(currentGrid)
	{
	case GRID_LHS:
		pMainFrame->ChangeGridVarState(_T("EditableLHS"), true);
		break;
	case GRID_RHS:
		pMainFrame->ChangeGridVarState(_T("EditableRHS"), true);
		break;
	case GRID_WM:
		pMainFrame->ChangeGridVarState(_T("EditableWM"), true);
		break;
	case GRID_COND_LINK:
		pMainFrame->ChangeGridVarState(_T("EditableCLink"), true);
		break;	
	case GRID_AGENDA:
		pMainFrame->ChangeGridVarState(_T("EditableAgenda"), true);
		break;
	case GRID_AM:
		pMainFrame->ChangeGridVarState(_T("EditableAM"), true);
		break;	
	case GRID_BM:
		pMainFrame->ChangeGridVarState(_T("EditableBM"), true);
		break;	
	case GRID_BM_TK:
		pMainFrame->ChangeGridVarState(_T("EditableBM_TK"), true);
		break;
	case GRID_RETE:
		pMainFrame->ChangeGridVarState(_T("EditableRETE"), true);
		break;
	case GRID_INDUCTION:
		pMainFrame->ChangeGridVarState(_T("EditableInduction"), true);
		break;	

	}//end switch

	
	for (int row = m_pGrid->GetFixedRowCount(); row < m_pGrid->GetRowCount(); row++)
     {
	   	for (int col = m_pGrid->GetFixedColumnCount(); col < m_pGrid->GetColumnCount(); col++)
	    { 
			m_pGrid->SetItemBkColour(row, col, clr);
			//m_pGrid->SetItemFgColour(row, col, RGB(0,0,0));
             
    	}
	}
	
	m_pGrid->Invalidate();
	
}	
