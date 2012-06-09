// ChartLinePropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ChartLinePropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartLinePropDlg dialog


CChartLinePropDlg::CChartLinePropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartLinePropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartLinePropDlg)
	m_iLineWidth = 0;
	m_iPenStyle = -1;
	//}}AFX_DATA_INIT
}


void CChartLinePropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartLinePropDlg)
	DDX_Control(pDX, IDC_PENSTYLE_COMBO, m_CtrlPenStyle);
	DDX_Text(pDX, IDC_LINEWIDTH_EDIT, m_iLineWidth);
	DDX_CBIndex(pDX, IDC_PENSTYLE_COMBO, m_iPenStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartLinePropDlg, CDialog)
	//{{AFX_MSG_MAP(CChartLinePropDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartLinePropDlg message handlers
BOOL CChartLinePropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
/*	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		m_CtrlPenStyle.AddString(_T("Solido"));
		m_CtrlPenStyle.AddString(_T("Raya"));
		m_CtrlPenStyle.AddString(_T("Punto"));
		m_CtrlPenStyle.AddString(_T("Raya-Punto"));
		m_CtrlPenStyle.AddString(_T("Raya-Punto-Punto"));
	
		CWnd::SetWindowText(_T("Propiedades línea"));
		GetDlgItem(IDC_STATIC_PENSTYLE)->SetWindowText(_T("Estilo pluma"));
		GetDlgItem(IDC_STATIC_LINEWIDTH)->SetWindowText(_T("Grosor línea"));
		GetDlgItem(IDOK)->SetWindowText(_T("Aceptar"));
		break;
	default:
		m_CtrlPenStyle.AddString(_T("Solid"));
		m_CtrlPenStyle.AddString(_T("Dash"));
		m_CtrlPenStyle.AddString(_T("Dot"));
		m_CtrlPenStyle.AddString(_T("Dash-Dot"));
		m_CtrlPenStyle.AddString(_T("Dash-Dot-Dot"));
	
		CWnd::SetWindowText(_T("Line properties"));
		GetDlgItem(IDC_STATIC_PENSTYLE)->SetWindowText(_T("Pen style"));
		GetDlgItem(IDC_STATIC_LINEWIDTH)->SetWindowText(_T("Line width"));
		GetDlgItem(IDOK)->SetWindowText(_T("OK"));
		break;
	}
*/	
	
	m_iLineWidth = 1;
	m_iPenStyle = 0;
	UpdateData(FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartLinePropDlg::OnOK() 
{
	UpdateData(TRUE);
	
	CDialog::OnOK();
}
