// NewProjectEndPage.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "NewProjectEndPage.h"
#include "../MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewProjectEndPage property page

IMPLEMENT_DYNCREATE(CNewProjectEndPage, CPropertyPageEx)

CNewProjectEndPage::CNewProjectEndPage() : CPropertyPageEx(CNewProjectEndPage::IDD)
{
	//{{AFX_DATA_INIT(CNewProjectEndPage)
	
	//}}AFX_DATA_INIT
	m_psp.dwFlags |= PSP_HIDEHEADER;
}

CNewProjectEndPage::~CNewProjectEndPage()
{

}

void CNewProjectEndPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProjectEndPage)
	DDX_Control(pDX, IDC_STATIC_INFO, m_stcInfo);
	DDX_Control(pDX, IDC_STATIC_ROOT, m_stcRoot);
	DDX_Control(pDX, IDC_RICHEDIT_PROJECT_INFO, m_sProjectInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProjectEndPage, CPropertyPageEx)
	//{{AFX_MSG_MAP(CNewProjectEndPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProjectEndPage message handlers
BOOL CNewProjectEndPage::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons(PSWIZB_FINISH);
	return CPropertyPageEx::OnSetActive();
}

BOOL CNewProjectEndPage::OnWizardFinish() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CreateDirectory(g_projectRoot, NULL);

	//pMainFrame->ProjFileWrite(g_projectName, g_projectAuthor, g_projectDesc, g_projectRoot, g_projectDate, g_projectInference, g_projectResource);
	//pMainFrame->ProjFileRead(g_projectName, g_projectRoot);
	
	return CPropertyPageEx::OnWizardFinish();
}



BOOL CNewProjectEndPage::OnInitDialog() 
{
	CPropertyPageEx::OnInitDialog();
	
	CString sDate; 
	sDate = _T("Project was created: ") + g_projectDate;
	m_sProjectInfo.SetWindowText(sDate);

	CString txt;
	
	txt = _T("PROJECT SETTINGS: ");
	txt += _T("\xA\xA");
	txt += _T("Project Name: ") + g_projectName;
	txt += _T("\xA");
	txt += _T("Project Author(s): ") + g_projectAuthor;
	txt += _T("\xA");
	txt += _T("Project Description: ") + g_projectDesc;
	txt += _T("\xA");
	txt += _T("Project Directory: ") + g_projectRoot;
	txt += _T("\xA");
	txt += _T("Project Inference Method: ") + g_projectInference;
	txt += _T("\xA\xA");
	txt += _T("PROJECT RESOURCES: ");
	txt += _T("\xA\xA");
	txt += _T("Images: ") + g_projectResource[0];
	txt += _T("\xA");
	txt += _T("Videos: ") + g_projectResource[1];
	txt += _T("\xA");
	txt += _T("DataBases: ") + g_projectResource[2];
	txt += _T("\xA");
	txt += _T("Others: ") + g_projectResource[3];
	txt += _T("\xA");
	
	m_stcInfo.SetWindowText(txt);
	//AfxMessageBox(txt);
	

	m_stcRoot.SetWindowText( g_projectRoot + _T("\\") + g_projectName + _T(".apj") );
	UpdateData(false);

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
