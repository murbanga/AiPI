// GraphCoordinatesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "GraphCoordinatesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphCoordinatesDlg dialog


CGraphCoordinatesDlg::CGraphCoordinatesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphCoordinatesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphCoordinatesDlg)
	m_x1 = 0.0;
	m_x2 = 0.0;
	m_y1 = 0.0;
	m_y2 = 0.0;
	//}}AFX_DATA_INIT
}


void CGraphCoordinatesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphCoordinatesDlg)
	DDX_Text(pDX, IDC_X1_DLG, m_x1);
	DDX_Text(pDX, IDC_X2_DLG, m_x2);
	DDX_Text(pDX, IDC_Y1_DLG, m_y1);
	DDX_Text(pDX, IDC_Y2_DLG, m_y2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphCoordinatesDlg, CDialog)
	//{{AFX_MSG_MAP(CGraphCoordinatesDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphCoordinatesDlg message handlers
BOOL CGraphCoordinatesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

/*	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		CWnd::SetWindowText(_T("Coordenadas"));
		GetDlgItem(IDC_STATIC_GENERAL_COORDINATES_DLG)->SetWindowText(_T("Rango coordenadas"));
		GetDlgItem(IDOK)->SetWindowText(_T("Aceptar"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancelar"));
		break;
	default:
		CWnd::SetWindowText(_T("Coordinates"));
		GetDlgItem(IDC_STATIC_GENERAL_COORDINATES_DLG)->SetWindowText(_T("Coordinates range"));
		GetDlgItem(IDOK)->SetWindowText(_T("OK"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancel"));
		break;
	}
	
*/	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
