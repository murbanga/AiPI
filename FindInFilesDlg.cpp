// FindInFilesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "FindInFilesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindInFilesDlg dialog


CFindInFilesDlg::CFindInFilesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindInFilesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindInFilesDlg)
	m_strFind = _T("");
	m_chkMatchCase = FALSE;
	m_chkRegExp = FALSE;
	m_chkWholeWord = FALSE;
	//}}AFX_DATA_INIT
}


void CFindInFilesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindInFilesDlg)
	DDX_Text(pDX, ID_EDIT_FIND, m_strFind);
	DDX_Check(pDX, IDC_CHECK_MATCHCASE, m_chkMatchCase);
	DDX_Check(pDX, IDC_CHECK_REGEXP, m_chkRegExp);
	DDX_Check(pDX, IDC_CHECK_WHOLEWORD, m_chkWholeWord);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindInFilesDlg, CDialog)
	//{{AFX_MSG_MAP(CFindInFilesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindInFilesDlg message handlers

BOOL CFindInFilesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_strFind = g_findText;
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
