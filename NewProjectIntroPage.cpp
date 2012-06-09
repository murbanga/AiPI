// NewProjectIntroPage.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "NewProjectIntroPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewProjectIntroPage property page

IMPLEMENT_DYNCREATE(CNewProjectIntroPage, CPropertyPageEx)

CNewProjectIntroPage::CNewProjectIntroPage() : CPropertyPageEx(CNewProjectIntroPage::IDD)
{
	//{{AFX_DATA_INIT(CNewProjectIntroPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_psp.dwFlags |= PSP_HIDEHEADER;
	
}

CNewProjectIntroPage::~CNewProjectIntroPage()
{
}

void CNewProjectIntroPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProjectIntroPage)
	DDX_Control(pDX, IDC_STATIC_SEPARATOR, m_staticSeparator0);
	DDX_Control(pDX, IDC_STATIC_TITLE, m_staticTitle);
	DDX_Control(pDX, IDC_STATIC_THAKS, m_staticThanks);
	DDX_Control(pDX, IDC_STATIC_INFO, m_staticInfo);
	DDX_Control(pDX, IDC_STATIC_ADVICE, m_staticAdvice);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProjectIntroPage, CPropertyPageEx)
	//{{AFX_MSG_MAP(CNewProjectIntroPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProjectIntroPage message handlers

BOOL CNewProjectIntroPage::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons(PSWIZB_NEXT);
	return CPropertyPageEx::OnSetActive();
}

BOOL CNewProjectIntroPage::OnInitDialog() 
{
	CPropertyPageEx::OnInitDialog();
	
	// Set the Static Text window.
	LPTSTR	psText = _T("Welcome to Aipi Project Wizard");
	//int	nTextLeft = 10;
	//int nTextTop = 10;
	int nTextHeight = 20;
	m_staticTitle.SetWindowText(psText);
	m_staticTitle.SetTextColor(RGB(0, 0, 0));
	m_staticTitle.SetBkColor(RGB(192, 192, 192));

	LOGFONT lf;
	if(m_staticTitle.GetLogFont(&lf))
	{
		lf.lfHeight=nTextHeight;
		lf.lfWidth=0;
		lf.lfItalic=TRUE;
		lf.lfWeight=900;
		m_staticTitle.SetLogFont(&lf);
	}
	m_staticTitle.SetFontName(_T("Arial Narrow"));

	m_staticTitle.SetEmboss();
	m_staticTitle.SetClientEdge();
	m_staticTitle.SetCharSet(ANSI_CHARSET,TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
