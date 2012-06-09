// GraphAxisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "GraphAxisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphAxisDlg dialog


CGraphAxisDlg::CGraphAxisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphAxisDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphAxisDlg)
	m_x_title = _T("");
	m_y_title = _T("");
	m_x_uom = _T("");
	m_y_uom = _T("");
	m_x_precision = 0;
	m_y_precision = 0;
	//}}AFX_DATA_INIT
}


void CGraphAxisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphAxisDlg)
	DDX_Text(pDX, IDC_XTITLE_DLG, m_x_title);
	DDX_Text(pDX, IDC_YTITLE_DLG, m_y_title);
	DDX_Text(pDX, IDC_XUOM_DLG, m_x_uom);
	DDX_Text(pDX, IDC_YUOM_DLG, m_y_uom);
	DDX_Text(pDX, IDC_XAXIS_PRECISION_DLG, m_x_precision);
	DDX_Text(pDX, IDC_YAXIS_PRECISION_DLG, m_y_precision);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphAxisDlg, CDialog)
	//{{AFX_MSG_MAP(CGraphAxisDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphAxisDlg message handlers

BOOL CGraphAxisDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
/*	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		CWnd::SetWindowText(_T("Ejes"));
		GetDlgItem(IDC_STATIC_X_AXIS_DLG)->SetWindowText(_T("Eje X:"));
		GetDlgItem(IDC_STATIC_Y_AXIS_DLG)->SetWindowText(_T("Eje Y:"));
		GetDlgItem(IDC_STATIC_X_AXIS_TITLE_DLG)->SetWindowText(_T("Título:"));
		GetDlgItem(IDC_STATIC_Y_AXIS_TITLE_DLG)->SetWindowText(_T("Título:"));
		GetDlgItem(IDC_STATIC_X_AXIS_UOM_DLG)->SetWindowText(_T("UOM:"));
		GetDlgItem(IDC_STATIC_Y_AXIS_UOM_DLG)->SetWindowText(_T("UOM:"));
		GetDlgItem(IDC_STATIC_X_AXIS_PRECISION_DLG)->SetWindowText(_T("Precisión:"));
		GetDlgItem(IDC_STATIC_Y_AXIS_PRECISION_DLG)->SetWindowText(_T("Precisión:"));
		
		//GetDlgItem(IDC_XTITLE_DLG)->SetWindowText(_T("Eje X"));
		//GetDlgItem(IDC_YTITLE_DLG)->SetWindowText(_T("Eje Y"));
		//GetDlgItem(IDC_XAXIS_PRECISION_DLG)->SetWindowText(_T("2"));
		//GetDlgItem(IDC_YAXIS_PRECISION_DLG)->SetWindowText(_T("2"));
		
		GetDlgItem(IDOK)->SetWindowText(_T("Aceptar"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancelar"));
		break;
	default:
		CWnd::SetWindowText(_T("Axis"));
		GetDlgItem(IDC_STATIC_X_AXIS_DLG)->SetWindowText(_T("X Axis:"));
		GetDlgItem(IDC_STATIC_Y_AXIS_DLG)->SetWindowText(_T("Y Axis:"));
		GetDlgItem(IDC_STATIC_X_AXIS_TITLE_DLG)->SetWindowText(_T("Title:"));
		GetDlgItem(IDC_STATIC_Y_AXIS_TITLE_DLG)->SetWindowText(_T("Title:"));
		GetDlgItem(IDC_STATIC_X_AXIS_UOM_DLG)->SetWindowText(_T("UOM:"));
		GetDlgItem(IDC_STATIC_Y_AXIS_UOM_DLG)->SetWindowText(_T("UOM:"));
		GetDlgItem(IDC_STATIC_X_AXIS_PRECISION_DLG)->SetWindowText(_T("Precision:"));
		GetDlgItem(IDC_STATIC_Y_AXIS_PRECISION_DLG)->SetWindowText(_T("Precision:"));

		//GetDlgItem(IDC_XTITLE_DLG)->SetWindowText(_T("X Axis"));
		//GetDlgItem(IDC_YTITLE_DLG)->SetWindowText(_T("Y Axis"));
		//GetDlgItem(IDC_XAXIS_PRECISION_DLG)->SetWindowText(_T("2"));
		//GetDlgItem(IDC_YAXIS_PRECISION_DLG)->SetWindowText(_T("2"));
		
		GetDlgItem(IDOK)->SetWindowText(_T("OK"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancel"));
		break;
	}
*/	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
