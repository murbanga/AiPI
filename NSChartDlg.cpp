// NSChartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "NSChartDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNSChartDlg dialog


CNSChartDlg::CNSChartDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNSChartDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNSChartDlg)
	m_sLabel = _T("");
	m_sValue = _T("");
	m_strTask = _T("");
	//}}AFX_DATA_INIT
}


void CNSChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNSChartDlg)
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Text(pDX, IDC_LABEL, m_sLabel);
	DDX_Text(pDX, IDC_VALUE, m_sValue);
	DDX_Text(pDX, IDC_STATIC_NSCHART, m_strTask);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNSChartDlg, CDialog)
	//{{AFX_MSG_MAP(CNSChartDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNSChartDlg message handlers
BOOL CNSChartDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

/*
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		CWnd::SetWindowText(_T("Entradas NSChartCtrl"));
		GetDlgItem(IDC_STATIC_LABEL)->SetWindowText(_T("Nombre etiqueta:"));
		GetDlgItem(IDC_STATIC_VALUE)->SetWindowText(_T("Valor:"));
		GetDlgItem(IDOK)->SetWindowText(_T("Aceptar"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancelar"));
		break;
	default:
		CWnd::SetWindowText(_T("NSChartCtrl Inputs"));
		GetDlgItem(IDC_STATIC_LABEL)->SetWindowText(_T("Label name:"));
		GetDlgItem(IDC_STATIC_VALUE)->SetWindowText(_T("Value:"));
		GetDlgItem(IDOK)->SetWindowText(_T("OK"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancel"));
		break;
	}
*/	
	m_btnOK.SetWindowText(szBtnCaption) ;
	m_btnCancel.SetWindowText(szBtnCancel) ;
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
