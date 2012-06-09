// OleDBConnectionDlg.cpp : implementation file
//
/////////////////////////////////////////////////////////////////
//                                                             //
//                OleDBConnectionDlg.cpp                          //
//     implementation of the COleDBConnectionDlg class            //
//-------------------------------------------------------------//
//             By Eugene Khodakovsky                           //
//                  June, 2000                                 //
//             Eugene@cpplab.com                               //
//            Last Update: April, 2002                         //
/////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "AIPI.h"
#include "OleDBConnectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CAIPIApp theApp;
/////////////////////////////////////////////////////////////////////////////
// COleDBConnectionDlg dialog
COleDBConnectionDlg::COleDBConnectionDlg(CWnd* pParent,bool bOleDBSupport)
	: CDialog(COleDBConnectionDlg::IDD, pParent),
	m_bOleDBSupport(bOleDBSupport)
{
	//{{AFX_DATA_INIT(COleDBConnectionDlg)
	m_iDBType = UNDEFINE;
	//}}AFX_DATA_INIT
	m_strDataSourceCaption = m_bOleDBSupport ? _T("Server") : _T("DSN:");
}


void COleDBConnectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COleDBConnectionDlg)
	DDX_Control(pDX, IDC_RADIO_DB2, m_radioDB2);
	DDX_Control(pDX, IDC_RADIO_MSACCESS, m_radioMSAccess);
	DDX_Control(pDX, IDC_RADIO_MSSQL, m_radioMSSql);
	DDX_Control(pDX, IDC_RADIO_MSORACLE, m_radioMSOracle);
	DDX_Control(pDX, IDC_RADIO_MYSQL, m_radioMySql);
	DDX_Control(pDX, IDC_RADIO_ORACLE, m_radioOracle);
	
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_STATIC_DATASOURCE_CAPTION,m_strDataSourceCaption);
	DDX_Text(pDX, IDC_EDIT_DSN_D,m_bOleDBSupport ? m_props.m_strServerName : m_props.m_strDSN);
	DDX_Text(pDX, IDC_EDIT_PWD_D,m_props.m_strPassword);
	DDX_Text(pDX, IDC_EDIT_UID_D,m_props.m_strLoginName);
	DDX_Text(pDX, IDC_EDIT_DATABASE_NAME,m_props.m_strDatabaseName);
}


BEGIN_MESSAGE_MAP(COleDBConnectionDlg, CDialog)
	//{{AFX_MSG_MAP(COleDBConnectionDlg)
	ON_EN_CHANGE(IDC_EDIT_DSN_D, OnChangeEdit)
	ON_BN_CLICKED(IDC_BTN_OLEDB_BROWSE, OnBtnOledbBrowse)
	ON_BN_CLICKED(IDC_RADIO_DB2, OnRadioDB2)
	ON_BN_CLICKED(IDC_RADIO_MSACCESS, OnRadioMSAccess)
	ON_BN_CLICKED(IDC_RADIO_MSSQL, OnRadioMSSql)
	ON_BN_CLICKED(IDC_RADIO_MSORACLE, OnRadioMSOracle)
	ON_BN_CLICKED(IDC_RADIO_MYSQL, OnRadioMySql)
	ON_EN_CHANGE(IDC_EDIT_PWD_D, OnChangeEdit)
	ON_EN_CHANGE(IDC_EDIT_UID_D, OnChangeEdit)
	ON_BN_CLICKED(IDC_RADIO_ORACLE, OnRadioOracle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectionDlg message handlers

BOOL COleDBConnectionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	UpdateData(TRUE);

	m_props.m_strDatabaseName = g_sDBName;
	m_props.m_strDSN = g_sDBDNS;
	m_props.m_strLoginName = g_sDBUser;
	m_props.m_strPassword = g_sDBPassword;
	m_props.m_strServerName = g_sDBDNS;

	
	m_iDBType = g_iDBProvider;
	
	
	switch(m_iDBType)	
	{
	case MS_ACCESS:
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(FALSE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(TRUE);
		m_radioMSAccess.SetCheck(TRUE);
		break;
	case MS_SQLSERVER:
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(FALSE);
		m_radioMSSql.SetCheck(TRUE);
		break;
	case MS_ORACLE:
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(FALSE);
		m_radioMSOracle.SetCheck(TRUE);
		break;
	case ORACLE:
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(FALSE);
		m_radioOracle.SetCheck(TRUE);
		break;
	case MYSQL:
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(FALSE);
		m_radioMySql.SetCheck(TRUE);
		break;
	case DB2:
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(FALSE);
		m_radioDB2.SetCheck(TRUE);
		break;
	default :
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(FALSE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(FALSE);

		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(FALSE);
	}

	m_bInit = true;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COleDBConnectionDlg::OnOK()
{
	UpdateData();
	g_sDBDNS ? m_props.m_strServerName : m_props.m_strDSN;
	//g_sDBDNS = m_props.m_strServerName;
	g_sDBPassword = m_props.m_strPassword;
	g_sDBUser = m_props.m_strLoginName;
	g_sDBName = m_props.m_strDatabaseName;
	
	if(!IsValidPassword())
		return;
	CDialog::OnOK();
}

void COleDBConnectionDlg::OnChangeEdit() 
{
	if(!m_bInit)
		return;
	UpdateData();
}

bool COleDBConnectionDlg::IsValidPassword()
{
	return true;
}



void COleDBConnectionDlg::OnBtnOledbBrowse() 
{
	const static _TCHAR BASED_CODE szFilter[] = _T("Database Files (*.mdb)|*.mdb|All Files (*.*)|*.*||");

	CFileDialog Fdlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	if(Fdlg.DoModal() == IDOK)
 	{
 		
 		CString path = Fdlg.GetPathName();
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->SetWindowText(path);
 	}
	
}

void COleDBConnectionDlg::OnRadioDB2() 
{
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(FALSE);	
}

void COleDBConnectionDlg::OnRadioMSAccess() 
{
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(FALSE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(FALSE);
		
		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(TRUE);
}

void COleDBConnectionDlg::OnRadioMSSql() 
{
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(FALSE);	
}

void COleDBConnectionDlg::OnRadioMSOracle() 
{
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(FALSE);	
}

void COleDBConnectionDlg::OnRadioMySql() 
{
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(FALSE);	
}

void COleDBConnectionDlg::OnRadioOracle() 
{
		GetDlgItem(IDC_EDIT_DSN_D)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DATABASE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_UID_D)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PWD_D)->EnableWindow(TRUE);

		GetDlgItem(IDC_STATIC_DATASOURCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_STATIC_DATABASE)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_USER)->EnableWindow(TRUE);
		GetDlgItem(IDC_STATIC_PASSWORD)->EnableWindow(TRUE);

		GetDlgItem(IDC_BTN_OLEDB_BROWSE)->EnableWindow(FALSE);
		
}
