// NewProjectPage2.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "NewProjectPage2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewProjectPage2 property page

IMPLEMENT_DYNCREATE(CNewProjectPage2, CPropertyPageEx)

CNewProjectPage2::CNewProjectPage2() 
: CPropertyPageEx(CNewProjectPage2::IDD, 0, IDS_HEADERTITLE_PROJ_PAGE2, IDS_HEADERSUBTITLE_PROJ_PAGE2)
{
	//{{AFX_DATA_INIT(CNewProjectPage2)
		
	//}}AFX_DATA_INIT
}

CNewProjectPage2::~CNewProjectPage2()
{
}

void CNewProjectPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProjectPage2)
	DDX_Control(pDX, IDC_CHECK_IMAGES, m_chkImages);
	DDX_Control(pDX, IDC_CHECK_VIDEOS, m_chkVideos);
	DDX_Control(pDX, IDC_CHECK_DB, m_chkDataBase);
	DDX_Control(pDX, IDC_CHECK_OTHER, m_chkOthers);
	DDX_Control(pDX, IDC_RADIO_FORDWARD, m_radioFordward);
	DDX_Control(pDX, IDC_RADIO_BACKWARD, m_radioBackward);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProjectPage2, CPropertyPageEx)
	//{{AFX_MSG_MAP(CNewProjectPage2)
	ON_BN_CLICKED(IDC_RADIO_FORDWARD, OnRadioForward)
	ON_BN_CLICKED(IDC_RADIO_BACKWARD, OnRadioBackward)
	ON_BN_CLICKED(IDC_CHECK_IMAGES, OnCheckImages)
	ON_BN_CLICKED(IDC_CHECK_VIDEOS, OnCheckVideos)
	ON_BN_CLICKED(IDC_CHECK_DB, OnCheckDataBases)
	ON_BN_CLICKED(IDC_CHECK_OTHER, OnCheckOthers)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProjectPage2 message handlers
BOOL CNewProjectPage2::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	return CPropertyPageEx::OnSetActive();
}

BOOL CNewProjectPage2::OnInitDialog() 
{
	CPropertyPageEx::OnInitDialog();
	
	CWnd* pCtrl=GetDlgItem(IDC_IMAGE_NEW_PAGE2);
	ASSERT(pCtrl!=NULL);

	
	CString sCurrentDir;
	GetCurrentDirectory( MAX_SIZE_PATH, sCurrentDir.GetBufferSetLength(MAX_SIZE_PATH) );
	sCurrentDir.ReleaseBuffer();
	CString	m_sFilename =  sCurrentDir + _T("\\res\\plarge.bmp");	
	
	int		m_nAlign = 0;
	CRect rect;
	pCtrl->GetWindowRect(rect);
	pCtrl->DestroyWindow();
	ScreenToClient(rect);
	m_pictureWnd.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rect,this,IDC_IMAGE_NEW_PAGE2);
	m_backPainterOrganizer.Attach(&m_pictureWnd,m_sFilename,(PaintType)m_nAlign);
	m_pictureWnd.ModifyStyleEx(NULL,WS_EX_CLIENTEDGE,SWP_DRAWFRAME);

	m_pictureWnd.RedrawWindow();

	UpdateData(true);

	m_radioFordward.SetCheck(TRUE);
	g_projectInference = _T("Fordward-Chaining");

	g_projectResource[0] = _T("Not Used");
	g_projectResource[1] = _T("Not Used");
	g_projectResource[2] = _T("Not Used");
	g_projectResource[3] = _T("Not Used");

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CNewProjectPage2::OnWizardNext() 
{
	/*
	UpdateData(true);
	
	m_radioFordward;
	m_radioBackward;
	m_chkImages;
	m_chkVideos;
	m_chkDataBase;
	m_chkOthers;
	*/
	
	 
	return CPropertyPageEx::OnWizardNext();
}


void CNewProjectPage2::OnRadioForward() 
{
	g_projectInference = _T("Forward-Chaining");
	
}

void CNewProjectPage2::OnRadioBackward() 
{
	g_projectInference = _T("Backward-Chaining");
	
}

void CNewProjectPage2::OnCheckImages() 
{
	g_projectResource[0] = _T("Used");  	
}

void CNewProjectPage2::OnCheckVideos() 
{
	g_projectResource[1] = _T("Used");
}

void CNewProjectPage2::OnCheckDataBases() 
{
	g_projectResource[2] = _T("Used");
}

void CNewProjectPage2::OnCheckOthers() 
{
	g_projectResource[3] = _T("Used");
}
