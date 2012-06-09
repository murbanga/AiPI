// StringInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "StringInputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStringInputDlg dialog


CStringInputDlg::CStringInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStringInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStringInputDlg)
		m_strPrompt = _T("");
		m_strEdit = _T("");
	//}}AFX_DATA_INIT
}


void CStringInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStringInputDlg)
	DDX_Control(pDX, IDC_EDIT, m_ctrlEdit);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Text(pDX, IDC_STATICPROMPT, m_strPrompt);
	DDX_Text(pDX, IDC_EDIT, m_strEdit);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStringInputDlg, CDialog)
	//{{AFX_MSG_MAP(CStringInputDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStringInputDlg message handlers
BOOL CStringInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	/*
	AddSzControl(IDC_STATICPROMPT, mdResize, mdNone);
	AddSzControl(IDC_EDIT, mdResize, mdResize);
	AddSzControl(IDOK, mdRelative, mdRepos);
	AddSzControl(IDCANCEL, mdRelative, mdRepos);
	*/

	m_btnOK.SetWindowText(szBtnOK) ;
	m_btnCancel.SetWindowText(szBtnCancel);
	CDialog::SetWindowText(szDlgCaption);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStringInputDlg::OnOK() 
{
	_TCHAR szName[255];
	GetDlgItem(IDC_EDIT)->GetWindowText(szName,254);
	
	
	for(int i=0; i<255; i++)
	{
		if( szName[i] != 'Ì')
		{
			m_strTitleName += szName[i];
		}
	}
	
	if (_tcscmp(szName,_T("")) == 0)
	{
		LANGID dwLanguageID = GetSystemLanguagePrimaryID();
		switch(dwLanguageID)
		{
		case LANG_SPANISH:
			MessageBox(_T("Debe suplir un nombre a la serie"),_T("Error"));
			return;
		default:
			MessageBox(_T("You must supply a name"),_T("Error"));
			return;
		}

	}
	
	CDialog::OnOK();
}
