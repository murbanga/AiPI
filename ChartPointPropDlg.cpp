// ChartPointPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ChartPointPropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartPointPropDlg dialog


CChartPointPropDlg::CChartPointPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartPointPropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartPointPropDlg)
	m_iPointsHeight = 0;
	m_iPointsWidth = 0;
	m_iPointsType = -1;
	//}}AFX_DATA_INIT
}


void CChartPointPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartPointPropDlg)
	DDX_Control(pDX, IDC_POINTTYPE_COMBO, m_CtrlPointsType);
	DDX_Text(pDX, IDC_POINTHEIGHT_EDIT, m_iPointsHeight);
	DDV_MinMaxInt(pDX, m_iPointsHeight, 0, 20);
	DDX_Text(pDX, IDC_POINTWIDTH_EDIT, m_iPointsWidth);
	DDV_MinMaxInt(pDX, m_iPointsWidth, 0, 20);
	DDX_CBIndex(pDX, IDC_POINTTYPE_COMBO, m_iPointsType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartPointPropDlg, CDialog)
	//{{AFX_MSG_MAP(CChartPointPropDlg)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartPointPropDlg message handlers
void CChartPointPropDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
}

void CChartPointPropDlg::OnOK() 
{
	UpdateData(TRUE);
	
	CDialog::OnOK();
}

BOOL CChartPointPropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
/*	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		m_CtrlPointsType.AddString(_T("Elipse"));
		m_CtrlPointsType.AddString(_T("Rectángulo"));
		m_CtrlPointsType.AddString(_T("Triángulo"));
			
		CWnd::SetWindowText(_T("Propiedades puntos"));
		GetDlgItem(IDC_STATIC_POINTSTYPE)->SetWindowText(_T("Tipo punto:"));
		GetDlgItem(IDC_STATIC_POINTSWIDTH)->SetWindowText(_T("Grosor punto:"));
		GetDlgItem(IDC_STATIC_POINTSHEIGHT)->SetWindowText(_T("Altura punto:"));
		GetDlgItem(IDOK)->SetWindowText(_T("Aceptar"));
		break;
	default:
		m_CtrlPointsType.AddString(_T("Ellipse"));
		m_CtrlPointsType.AddString(_T("Rectangle"));
		m_CtrlPointsType.AddString(_T("Triangle"));
			
		CWnd::SetWindowText(_T("Points properties"));
		GetDlgItem(IDC_STATIC_POINTSTYPE)->SetWindowText(_T("Point type:"));
		GetDlgItem(IDC_STATIC_POINTSWIDTH)->SetWindowText(_T("Point width:"));
		GetDlgItem(IDC_STATIC_POINTSHEIGHT)->SetWindowText(_T("Point height:"));
		GetDlgItem(IDOK)->SetWindowText(_T("OK"));
		break;
	}
*/
	
	m_iPointsWidth = m_iPointsHeight = 5;
	m_iPointsType = 0;
	UpdateData(FALSE);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
