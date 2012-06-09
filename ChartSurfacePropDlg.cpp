// ChartSurfacePropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ChartSurfacePropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartSurfacePropDlg dialog


CChartSurfacePropDlg::CChartSurfacePropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartSurfacePropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartSurfacePropDlg)
	m_iHorizSurf = -1;
	m_FillStyle = -1;
	//}}AFX_DATA_INIT
}


void CChartSurfacePropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartSurfacePropDlg)
	DDX_Control(pDX, IDC_FILLSTYLE_COMBO, m_CtrlFillStyle);
	DDX_Radio(pDX, IDC_HORIZONTAL_RADIO, m_iHorizSurf);
	DDX_CBIndex(pDX, IDC_FILLSTYLE_COMBO, m_FillStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartSurfacePropDlg, CDialog)
	//{{AFX_MSG_MAP(CChartSurfacePropDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartSurfacePropDlg message handlers

BOOL CChartSurfacePropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
/*	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		m_CtrlFillStyle.AddString(_T("Solido"));
		m_CtrlFillStyle.AddString(_T("Plumear diagonal-inferior"));
		m_CtrlFillStyle.AddString(_T("Plumear diagonal-superior"));
		m_CtrlFillStyle.AddString(_T("Plumear cruzado"));
		m_CtrlFillStyle.AddString(_T("Plumear diagonal-cruzado"));
		m_CtrlFillStyle.AddString(_T("Plumear horizontal"));

	
		CWnd::SetWindowText(_T("Propiedades superficie"));
		GetDlgItem(IDC_STATIC_FILLSTYLE)->SetWindowText(_T("Estilo relleno:"));
		GetDlgItem(IDC_HORIZONTAL_RADIO)->SetWindowText(_T("Superficie horizontal"));
		GetDlgItem(IDC_VERTICAL_RADIO)->SetWindowText(_T("Superficie vertical"));
		GetDlgItem(IDOK)->SetWindowText(_T("Aceptar"));
		break;
	default:
		m_CtrlFillStyle.AddString(_T("Solid"));
		m_CtrlFillStyle.AddString(_T("Hatch down-diagonal"));
		m_CtrlFillStyle.AddString(_T("Hatch up-diagonal"));
		m_CtrlFillStyle.AddString(_T("Hatch cross"));
		m_CtrlFillStyle.AddString(_T("Hatch cross-diagonal"));
		m_CtrlFillStyle.AddString(_T("Hatch horizontal"));
	
	
		CWnd::SetWindowText(_T("Surface properties"));
		GetDlgItem(IDC_STATIC_FILLSTYLE)->SetWindowText(_T("Fill style:"));
		GetDlgItem(IDC_HORIZONTAL_RADIO)->SetWindowText(_T("Horizontal surface"));
		GetDlgItem(IDC_VERTICAL_RADIO)->SetWindowText(_T("Vertical surface"));
		GetDlgItem(IDOK)->SetWindowText(_T("OK"));
		break;
	}

*/

	m_FillStyle = 0;
	m_iHorizSurf = 0;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartSurfacePropDlg::OnOK() 
{
	UpdateData(TRUE);	
	CDialog::OnOK();
}

