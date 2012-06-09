// ChartSerieDelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ChartSerieDelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartSerieDelDlg dialog


CChartSerieDelDlg::CChartSerieDelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartSerieDelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartSerieDelDlg)
		
	//}}AFX_DATA_INIT
}


void CChartSerieDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartSerieDelDlg)
		DDX_Control(pDX, IDC_LIST_SERIES, m_SeriesList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartSerieDelDlg, CDialog)
	//{{AFX_MSG_MAP(CChartSerieDelDlg)
		
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartSerieDelDlg message handlers
BOOL CChartSerieDelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

/*
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();

	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		CWnd::SetWindowText(_T("Eliminar series"));
		GetDlgItem(IDC_STATIC_SERIES)->SetWindowText(_T("Series"));
		GetDlgItem(IDOK)->SetWindowText(_T("Eliminar"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancelar"));
		break;
	default:
		CWnd::SetWindowText(_T("Delete series"));
		GetDlgItem(IDC_STATIC_SERIES)->SetWindowText(_T("Series"));
		GetDlgItem(IDOK)->SetWindowText(_T("Delete"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancel"));
		break;
	}
*/
	
	for(int i= 0; i< dlgSerieName.GetSize(); i++)
	{
		m_SeriesList.AddString(dlgSerieName.GetAt(i));
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartSerieDelDlg::OnOK() 
{
	dlgIndex = m_SeriesList.GetCurSel();
		if (dlgIndex == -1)
			return;

	m_SeriesList.DeleteString(dlgIndex);
	
	
	CDialog::OnOK();
}
