// NewProjectPage1.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "NewProjectPage1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewProjectPage1 property page

IMPLEMENT_DYNCREATE(CNewProjectPage1, CPropertyPageEx)

CNewProjectPage1::CNewProjectPage1()
 : CPropertyPageEx(CNewProjectPage1::IDD, 0, IDS_HEADERTITLE_PROJ_PAGE1, IDS_HEADERSUBTITLE_PROJ_PAGE1)
{
	//{{AFX_DATA_INIT(CNewProjectPage1)
	m_sProjectName = _T("<Required>");
	m_sProjectAuthor = _T("");
	m_sProjectDesc = _T("");
	
	//}}AFX_DATA_INIT

}

CNewProjectPage1::~CNewProjectPage1()
{

	
}

void CNewProjectPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProjectPage1)
	DDX_Control(pDX, IDC_STATIC_SEPARATOR, m_staticSeparator0);
	DDX_Control(pDX, IDC_EDIT_PROJ_ROOT, m_editBrowse32);
	DDX_Text(pDX, IDC_EDIT_PROJ_AUTHOR, m_sProjectAuthor);
	DDX_Text(pDX, IDC_EDIT_PROJ_DESC, m_sProjectDesc);
	DDX_Text(pDX, IDC_EDIT_PROJ_NAME, m_sProjectName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProjectPage1, CPropertyPageEx)
	//{{AFX_MSG_MAP(CNewProjectPage1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProjectPage1 message handlers


BOOL CNewProjectPage1::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	return CPropertyPageEx::OnSetActive();

	
}














BOOL CNewProjectPage1::OnInitDialog() 
{
	CPropertyPageEx::OnInitDialog();
	
	CWnd* pCtrl=GetDlgItem(IDC_IMAGE_NEW_PAGE1);
	ASSERT(pCtrl!=NULL);


	CString sCurrentDir;
	GetCurrentDirectory( MAX_SIZE_PATH, sCurrentDir.GetBufferSetLength(MAX_SIZE_PATH) );
	sCurrentDir.ReleaseBuffer();
	CString	m_sFilename =  sCurrentDir + _T("\\res\\hardware.bmp");	
	int		m_nAlign = 0;
	CRect rect;
	pCtrl->GetWindowRect(rect);
	pCtrl->DestroyWindow();
	ScreenToClient(rect);
	m_pictureWnd.Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rect,this,IDC_IMAGE_NEW_PAGE1);
	m_backPainterOrganizer.Attach(&m_pictureWnd,m_sFilename,(PaintType)m_nAlign);
	m_pictureWnd.ModifyStyleEx(NULL,WS_EX_CLIENTEDGE,SWP_DRAWFRAME);

	m_pictureWnd.RedrawWindow();


	UpdateData(true);

	g_projectDate = _T("");
	g_projectName = _T("");
	g_projectAuthor = _T("");
	g_projectDesc = _T("");
	
	
	CString m_sProjectDefaultRoot = sCurrentDir + _T("\\Aipi Projects");
	CreateDirectory(m_sProjectDefaultRoot, NULL);
	m_editBrowse32.SetWindowText(m_sProjectDefaultRoot);
	g_projectRoot = m_sProjectDefaultRoot;

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CNewProjectPage1::OnWizardNext() 
{
	
	UpdateData(true);
	
	g_projectDate = PrintDate();
	g_projectName = m_sProjectName;
	g_projectAuthor = m_sProjectAuthor;
	g_projectDesc = m_sProjectDesc;
	g_projectRoot = m_editBrowse32.GetPath();
	g_projectRoot = g_projectRoot + _T("\\") + g_projectName;

	//AfxMessageBox(m_sProjectName);

	
	return CPropertyPageEx::OnWizardNext();
}


CString CNewProjectPage1::PrintDate()
{
    _TCHAR buffer[10];
	
	WORD w_day, w_month, w_year, w_hour, w_minute, w_second;
	CString s_day, s_month, s_year, s_hour, s_minute, s_second;	
	
	SYSTEMTIME t;
	GetSystemTime(&t);

	GetLocalTime(&t);
	w_day = t.wDay;
	w_month = t.wMonth;
	w_year = t.wYear;
	w_hour = t.wHour;
	w_minute = t.wMinute;
	w_second = t.wSecond;
	
	s_day = _itot(w_day, buffer, 10);
	s_month = _itot(w_month, buffer, 10);
	s_year = _itot(w_year, buffer, 10);
	s_hour = _itot(w_hour, buffer, 10);
	s_minute = _itot(w_minute, buffer, 10);
	s_second = _itot(w_second, buffer, 10);

	return s_day + _T("/") + s_month + _T("/") + s_year + _T("  Time: ") + s_hour + _T(":") + s_minute + _T(":") + s_second;
		

}