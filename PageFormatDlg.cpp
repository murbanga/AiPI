// PageFormatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "PageFormatDlg.h"
#include "InductionTabView.h"
#include ".\GridCtrl\GridCtrl.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageFormatDlg dialog


CPageFormatDlg::CPageFormatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPageFormatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageFormatDlg)
	
	//}}AFX_DATA_INIT
}


void CPageFormatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageFormatDlg)
	DDX_Control(pDX, IDC_STATIC_GRIDLINES, m_stcGridLines);
	DDX_Control(pDX, IDC_STATIC_FONT, m_stcFont);
	DDX_Control(pDX, IDC_CHK_VERTICAL, m_chkVertical);
	DDX_Control(pDX, IDC_CHK_HORIZONTAL, m_chkHorizontal);
	DDX_Control(pDX, IDC_BTN_FONT, m_btnCellFont);
	DDX_Control(pDX, IDC_RADIO_FIXEDITALIC, m_radioItalic);
	DDX_Control(pDX, IDC_RADIO_FIXEDBOLD, m_radioBold);
	DDX_Control(pDX, IDC_RADIO_FIXEDNORMAL, m_radioNormal);
	DDX_Control(pDX, IDC_RADIO_FIXEDVERTICAL, m_radioVerticalHeader);
	DDX_Control(pDX, IDC_BTN_PRINT, m_btnPrint);
	DDX_Control(pDX, IDC_STATIC_SEPARATOR01, m_stcSeparator01);
		
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageFormatDlg, CDialog)
	//{{AFX_MSG_MAP(CPageFormatDlg)
	ON_BN_CLICKED(IDC_CHK_HORIZONTAL, OnChkHorizontal)
	ON_BN_CLICKED(IDC_CHK_VERTICAL, OnChkVertical)
	ON_BN_CLICKED(IDC_BTN_FONT, OnBtnFont)
	ON_BN_CLICKED(IDC_RADIO_FIXEDITALIC, OnRadioFixedItalic)
	ON_BN_CLICKED(IDC_RADIO_FIXEDBOLD, OnRadioFixedBold)
	ON_BN_CLICKED(IDC_RADIO_FIXEDVERTICAL, OnRadioFixedVertical)
	ON_BN_CLICKED(IDC_RADIO_FIXEDNORMAL, OnRadioFixedNormal)
	ON_BN_CLICKED(IDC_BTN_PRINT, OnBtnPrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageFormatDlg message handlers

/*

void CPageFormatDlg::SelectGrid()
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

void CPageFormatDlg::OnGridLines() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	if (pMainFrame->m_bHorizontal == false && pMainFrame->m_bVertical == false)
		m_pGrid->SetGridLines(GVL_NONE);
	else if (pMainFrame->m_bHorizontal == true && pMainFrame->m_bVertical == false)
		m_pGrid->SetGridLines(GVL_HORZ);
	else if (pMainFrame->m_bHorizontal == false && pMainFrame->m_bVertical == true)
		m_pGrid->SetGridLines(GVL_VERT);
	else 
		m_pGrid->SetGridLines(GVL_BOTH);

	/*	
		CString str;
		str.Format(_T("Horiz...%d  " ), pMainFrame->m_bHorizontal);
		AfxMessageBox(str);
		str.Format(_T("Vert...%d  " ), pMainFrame->m_bVertical);
		AfxMessageBox(str);
		*/
		

}

void CPageFormatDlg::OnChkHorizontal() 
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int currentGrid =  pMainFrame->SelectGrid();
	
    
	if( pMainFrame->m_bHorizontal == 0)
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("HorizontalLHS"), true);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("HorizontalRHS"), true);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("HorizontalWM"), true);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("HorizontalCLink"), true);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("HorizontalAgenda"), true);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("HorizontalAM"), true);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("HorizontalBM"), true);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("HorizontalBM_TK"), true);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("HorizontalRETE"), true);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("HorizontalInduction"), true);
			break;	
		}//end switch
	}
	else 
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("HorizontalLHS"), false);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("HorizontalRHS"), false);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("HorizontalWM"), false);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("HorizontalCLink"), false);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("HorizontalAgenda"), false);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("HorizontalAM"), false);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("HorizontalBM"), false);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("HorizontalBM_TK"), false);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("HorizontalRETE"), false);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("HorizontalInduction"), false);
			break;	
		}
	}
    
	pMainFrame->m_bHorizontal = !pMainFrame->m_bHorizontal;
	OnGridLines();
	
}

void CPageFormatDlg::OnChkVertical() 
{
	
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	int currentGrid =  pMainFrame->SelectGrid();

	if( pMainFrame->m_bVertical == 0)
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("VerticalLHS"), true);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("VerticalRHS"), true);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("VerticalWM"), true);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("VerticalCLink"), true);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("VerticalAgenda"), true);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("VerticalAM"), true);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("VerticalBM"), true);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("VerticalBM_TK"), true);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("VerticalRETE"), true);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("VerticalInduction"), true);
			break;	
		}//end switch
	}
	else 
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("VerticalLHS"), false);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("VerticalRHS"), false);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("VerticalWM"), false);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("VerticalCLink"), false);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("VerticalAgenda"), false);
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("VerticalAM"), false);
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("VerticalBM"), false);
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("VerticalBM_TK"), false);
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("VerticalRETE"), false);
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("VerticalInduction"), false);
			break;	
		}
	}


	pMainFrame->m_bVertical = !pMainFrame->m_bVertical;
	OnGridLines();

}

void CPageFormatDlg::OnBtnFont() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
#ifndef _WIN32_WCE
	LOGFONT lf;
	
	pMainFrame->SelectGrid();
	m_pGrid->GetFont()->GetLogFont(&lf);
	
	
	CFontDialog dlg(&lf);
	if (dlg.DoModal() == IDOK) 
	{
		dlg.GetCurrentFont(&lf);

		CFont Font;
		Font.CreateFontIndirect(&lf);
		

		m_pGrid->SetFont(&Font);
        m_pGrid->AutoSize();
		
		
		Font.DeleteObject();	
	}

#endif

}
	


void CPageFormatDlg::OnRadioFixedItalic() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	int currentGrid =  pMainFrame->SelectGrid();
	
	if( pMainFrame->m_bItalic == 0)
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("BoldLHS"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicLHS"), true);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderLHS"), false);
			pMainFrame->ChangeGridVarState(_T("NormalLHS"), false);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("BoldRHS"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicRHS"), true);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderRHS"), false);
			pMainFrame->ChangeGridVarState(_T("NormalRHS"), false);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("BoldWM"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicWM"), true);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderWM"), false);
			pMainFrame->ChangeGridVarState(_T("NormalWM"), false);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("BoldCLink"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicCLink"), true);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderCLink"), false);
			pMainFrame->ChangeGridVarState(_T("NormalCLink"), false);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("BoldAgenda"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicAgenda"), true);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderAgenda"), false);
			pMainFrame->ChangeGridVarState(_T("NormalAgenda"), false);
			
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("BoldAM"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicAM"), true);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderAM"), false);
			pMainFrame->ChangeGridVarState(_T("NormalAM"), false);
			
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("BoldBM"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicBM"), true);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderBM"), false);
			pMainFrame->ChangeGridVarState(_T("NormalBM"), false);
			
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("BoldBM_TK"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicBM_TK"), true);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderBM_TK"), false);
			pMainFrame->ChangeGridVarState(_T("NormalBM_TK"), false);
			
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("BoldRETE"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicRETE"), true);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderRETE"), false);
			pMainFrame->ChangeGridVarState(_T("NormalRETE"), false);
			
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("BoldInduction"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicInduction"), true);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderInduction"), false);
			pMainFrame->ChangeGridVarState(_T("NormalInduction"), false);
			
			break;	
		}//end switch
	}
	

    CFont *pFont = m_pGrid->GetFont();
	
	if (!pFont) 
        return;

	LOGFONT lf;
    pFont->GetLogFont(&lf);
	lf.lfItalic = (BYTE) !pMainFrame->m_bItalic;

    m_pGrid->GetDefaultCell(TRUE, FALSE)->SetFont(&lf);
    m_pGrid->GetDefaultCell(FALSE, TRUE)->SetFont(&lf);
    m_pGrid->GetDefaultCell(TRUE, TRUE)->SetFont(&lf);

	m_pGrid->Invalidate();
    m_pGrid->AutoSizeColumns(GVS_HEADER);

   	
}

void CPageFormatDlg::OnRadioFixedBold() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
    
	int currentGrid =  pMainFrame->SelectGrid();
	if( pMainFrame->m_bBold == 0)
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("BoldLHS"), true);
			pMainFrame->ChangeGridVarState(_T("ItalicLHS"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderLHS"), false);
			pMainFrame->ChangeGridVarState(_T("NormalLHS"), false);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("BoldRHS"), true);
			pMainFrame->ChangeGridVarState(_T("ItalicRHS"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderRHS"), false);
			pMainFrame->ChangeGridVarState(_T("NormalRHS"), false);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("BoldWM"), true);
			pMainFrame->ChangeGridVarState(_T("ItalicWM"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderWM"), false);
			pMainFrame->ChangeGridVarState(_T("NormalWM"), false);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("BoldCLink"), true);
			pMainFrame->ChangeGridVarState(_T("ItalicCLink"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderCLink"), false);
			pMainFrame->ChangeGridVarState(_T("NormalCLink"), false);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("BoldAgenda"), true);
			pMainFrame->ChangeGridVarState(_T("ItalicAgenda"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderAgenda"), false);
			pMainFrame->ChangeGridVarState(_T("NormalAgenda"), false);
			
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("BoldAM"), true);
			pMainFrame->ChangeGridVarState(_T("ItalicAM"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderAM"), false);
			pMainFrame->ChangeGridVarState(_T("NormalAM"), false);
			
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("BoldBM"), true);
			pMainFrame->ChangeGridVarState(_T("ItalicBM"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderBM"), false);
			pMainFrame->ChangeGridVarState(_T("NormalBM"), false);
			
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("BoldBM_TK"), true);
			pMainFrame->ChangeGridVarState(_T("ItalicBM_TK"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderBM_TK"), false);
			pMainFrame->ChangeGridVarState(_T("NormalBM_TK"), false);
			
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("BoldRETE"), true);
			pMainFrame->ChangeGridVarState(_T("ItalicRETE"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderRETE"), false);
			pMainFrame->ChangeGridVarState(_T("NormalRETE"), false);
			
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("BoldInduction"), true);
			pMainFrame->ChangeGridVarState(_T("ItalicInduction"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderInduction"), false);
			pMainFrame->ChangeGridVarState(_T("NormalInduction"), false);
			
			break;	
		}//end switch
	}
	
	
	CFont *pFont = m_pGrid->GetFont();
	
	if (!pFont) 
        return;

	LOGFONT lf;
    pFont->GetLogFont(&lf);
	lf.lfWeight = FW_BOLD;

    m_pGrid->GetDefaultCell(TRUE, FALSE)->SetFont(&lf);
    m_pGrid->GetDefaultCell(FALSE, TRUE)->SetFont(&lf);
    m_pGrid->GetDefaultCell(TRUE, TRUE)->SetFont(&lf);

	m_pGrid->Invalidate();
    m_pGrid->AutoSizeColumns(GVS_HEADER);
	
	

	
}

void CPageFormatDlg::OnRadioFixedVertical() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	int currentGrid =  pMainFrame->SelectGrid();
	if( pMainFrame->m_bVerticalHeader == 0)
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("BoldLHS"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicLHS"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderLHS"), true);
			pMainFrame->ChangeGridVarState(_T("NormalLHS"), false);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("BoldRHS"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicRHS"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderRHS"), true);
			pMainFrame->ChangeGridVarState(_T("NormalRHS"), false);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("BoldWM"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicWM"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderWM"), true);
			pMainFrame->ChangeGridVarState(_T("NormalWM"), false);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("BoldCLink"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicCLink"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderCLink"), true);
			pMainFrame->ChangeGridVarState(_T("NormalCLink"), false);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("BoldAgenda"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicAgenda"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderAgenda"), true);
			pMainFrame->ChangeGridVarState(_T("NormalAgenda"), false);
			
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("BoldAM"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicAM"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderAM"), true);
			pMainFrame->ChangeGridVarState(_T("NormalAM"), false);
			
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("BoldBM"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicBM"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderBM"), true);
			pMainFrame->ChangeGridVarState(_T("NormalBM"), false);
			
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("BoldBM_TK"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicBM_TK"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderBM_TK"), true);
			pMainFrame->ChangeGridVarState(_T("NormalBM_TK"), false);
			
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("BoldRETE"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicRETE"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderRETE"), true);
			pMainFrame->ChangeGridVarState(_T("NormalRETE"), false);
			
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("BoldInduction"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicInduction"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderInduction"), true);
			pMainFrame->ChangeGridVarState(_T("NormalInduction"), false);
			
			break;	
		}//end switch
	}

	pMainFrame->m_bVerticalHeader = !pMainFrame->m_bVerticalHeader;
    	
	// Set reasonable format
	m_pGrid->GetDefaultCell(TRUE, FALSE)->SetFormat(DT_SINGLELINE|DT_NOPREFIX|DT_END_ELLIPSIS|DT_LEFT|DT_BOTTOM);
    m_pGrid->GetDefaultCell(TRUE, TRUE)->SetFormat(DT_SINGLELINE|DT_NOPREFIX|DT_END_ELLIPSIS|DT_LEFT|DT_BOTTOM);
	
    // Get the font
    CFont* pFont = m_pGrid->GetFont();
			
	LOGFONT lf;
    pFont->GetLogFont(&lf);
    
    // Make it true-type
    memcpy(lf.lfFaceName, _T("Arial Narrow"), 6);

    // Vertical or horizontal
    if (pMainFrame->m_bVerticalHeader)
    {
        lf.lfEscapement = 900;
        lf.lfOrientation = 900;
    }
    else
    {
        lf.lfEscapement = 0;
        lf.lfOrientation = 0;
    }


    // Set the fixed row defaults as this new font
    m_pGrid->GetDefaultCell(TRUE, FALSE)->SetFont(&lf);

    // Set cell 1,1 as the more normal font so URL cells look OK
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    
	m_pGrid->SetItemFont(0,0, &lf);
    m_pGrid->AutoSize(GVS_HEADER);
    m_pGrid->EnableTitleTips(TRUE);
	
	
	
  if (pMainFrame->m_bTitleTips)
    {
        pMainFrame->m_bTitleTips = !pMainFrame->m_bVerticalHeader;
        m_pGrid->EnableTitleTips(!pMainFrame->m_bVerticalHeader);
    }

    	
}

void CPageFormatDlg::OnRadioFixedNormal() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();


    int currentGrid =  pMainFrame->SelectGrid();
	if( pMainFrame->m_bNormal == 0)
	{
		switch(currentGrid)
		{
		case GRID_LHS:
			pMainFrame->ChangeGridVarState(_T("BoldLHS"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicLHS"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderLHS"), false);
			pMainFrame->ChangeGridVarState(_T("NormalLHS"), true);
			break;
		case GRID_RHS:
			pMainFrame->ChangeGridVarState(_T("BoldRHS"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicRHS"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderRHS"), false);
			pMainFrame->ChangeGridVarState(_T("NormalRHS"), true);
			break;
		case GRID_WM:
			pMainFrame->ChangeGridVarState(_T("BoldWM"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicWM"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderWM"), false);
			pMainFrame->ChangeGridVarState(_T("NormalWM"), true);
			break;
		case GRID_COND_LINK:
			pMainFrame->ChangeGridVarState(_T("BoldCLink"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicCLink"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderCLink"), false);
			pMainFrame->ChangeGridVarState(_T("NormalCLink"), true);
			break;	
		case GRID_AGENDA:
			pMainFrame->ChangeGridVarState(_T("BoldAgenda"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicAgenda"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderAgenda"), false);
			pMainFrame->ChangeGridVarState(_T("NormalAgenda"), true);
			
			break;
		case GRID_AM:
			pMainFrame->ChangeGridVarState(_T("BoldAM"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicAM"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderAM"), false);
			pMainFrame->ChangeGridVarState(_T("NormalAM"), true);
			
			break;	
		case GRID_BM:
			pMainFrame->ChangeGridVarState(_T("BoldBM"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicBM"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderBM"), false);
			pMainFrame->ChangeGridVarState(_T("NormalBM"), true);
			
			break;
		case GRID_BM_TK:
			pMainFrame->ChangeGridVarState(_T("BoldBM_TK"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicBM_TK"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderBM_TK"), false);
			pMainFrame->ChangeGridVarState(_T("NormalBM_TK"), true);
			
			break;	
		case GRID_RETE:
			pMainFrame->ChangeGridVarState(_T("BoldRETE"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicRETE"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderRETE"), false);
			pMainFrame->ChangeGridVarState(_T("NormalRETE"), true);
			
			break;
		case GRID_INDUCTION:
			pMainFrame->ChangeGridVarState(_T("BoldInduction"), false);
			pMainFrame->ChangeGridVarState(_T("ItalicInduction"), false);
			pMainFrame->ChangeGridVarState(_T("VerticalHeaderInduction"), false);
			pMainFrame->ChangeGridVarState(_T("NormalInduction"), true);
			
			break;	
		}//end switch
	}
	
	CFont *pFont = m_pGrid->GetFont();
	
	if (!pFont) 
        return;

	LOGFONT lf;
    pFont->GetLogFont(&lf);
	lf.lfWeight = FW_NORMAL;

    m_pGrid->GetDefaultCell(TRUE, FALSE)->SetFont(&lf);
    m_pGrid->GetDefaultCell(FALSE, TRUE)->SetFont(&lf);
    m_pGrid->GetDefaultCell(TRUE, TRUE)->SetFont(&lf);

	m_pGrid->Invalidate();
    m_pGrid->AutoSizeColumns(GVS_HEADER);
	
}


void CPageFormatDlg::OnBtnPrint() 
{

#if !defined(WCE_NO_PRINTING) && !defined(GRIDCONTROL_NO_PRINTING)
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->SelectGrid();
	m_pGrid->Print();
	

#endif
}



BOOL CPageFormatDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_radioNormal.SetCheck(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
