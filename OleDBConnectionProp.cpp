// OleDBConnectionProp.cpp : implementation file
//
/////////////////////////////////////////////////////////////////
//                                                             //
//                OleDBConnectionProp.cpp                          //
//     implementation of the COleDBConnectionProp class            //
//-------------------------------------------------------------//
//             By Eugene Khodakovsky                           //
//                  June, 2000                                 //
//             Eugene@cpplab.com                               //
//            Last Update: April, 2002                         //
/////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "AIPI.h"
#include "OleDBConnectionProp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COleDBConnectionProp


/////////////////////////////////////////////////////////////////////////////
// COleDBConnectionProp message handlers
#define PRESS_MARK_MASK 0x48

LPCTSTR	COleDBConnectionProp::m_szDSNEntry				= _T("DSN");
LPCTSTR	COleDBConnectionProp::m_szServerNameEntry		= _T("Server");
LPCTSTR	COleDBConnectionProp::m_szLoginNameEntry		= _T("UID");
LPCTSTR	COleDBConnectionProp::m_szDatabaseNameEntry		= _T("Database");
LPCTSTR	COleDBConnectionProp::m_szPasswordEntry			= _T("PWD");
LPCTSTR	COleDBConnectionProp::m_szTableEntry			= _T("Table");


static CString GetNextToken(CString& strSrc, const CString strDelim)
{
	CString token;
	int idx = strSrc.FindOneOf(strDelim);
	if(idx != -1)
	{
		token  = strSrc.Left(idx);
		strSrc = strSrc.Right(strSrc.GetLength() - (idx + 1) );
	}
	else
	{
		token = strSrc;
		strSrc.Empty();
	}
	return token;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(COleDBConnectionProp,CObject,0)

COleDBConnectionProp::COleDBConnectionProp(bool bSaveInRegistry):
	m_bSaveInRegistry(bSaveInRegistry)
{
	
	m_strServerName			= _T("");
	m_strDSN				= _T("");
	m_strDatabaseName		= _T("");
	m_strTableName			= _T("");
	m_strLoginName			= _T("");
	m_strPassword			= _T("");
	m_strIniFileName		= _T("");

	
}

COleDBConnectionProp::~COleDBConnectionProp()
{
	CloseConnection();
}

const COleDBConnectionProp& COleDBConnectionProp::operator =(const COleDBConnectionProp& right)
{
	Copy(right);
	return *this;
}

void COleDBConnectionProp::Copy(const COleDBConnectionProp& right)
{
	m_strDSN				= (LPCTSTR)right.m_strDSN;
	m_strDatabaseName		= (LPCTSTR)right.m_strDatabaseName;
	m_strTableName			= (LPCTSTR)right.m_strTableName;
	m_strLoginName			= (LPCTSTR)right.m_strLoginName;
	m_strPassword			= (LPCTSTR)right.m_strPassword;
	m_strServerName			= (LPCTSTR)right.m_strServerName;
	m_strIniFileName		= (LPCTSTR)right.m_strIniFileName;
}

void COleDBConnectionProp::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar	<< StrToFile(m_strDSN);
		ar	<< StrToFile(m_strDatabaseName);
		ar	<< StrToFile(m_strTableName);
		ar	<< StrToFile(m_strLoginName);
		ar	<< StrToFile(m_strPassword);
		ar	<< StrToFile(m_strServerName);
	}
	else
	{
		FileToStr(ar,m_strDSN);
		FileToStr(ar,m_strDatabaseName);
		FileToStr(ar,m_strTableName);
		FileToStr(ar,m_strLoginName);
		FileToStr(ar,m_strPassword);
		FileToStr(ar,m_strServerName);
	}
}

CString COleDBConnectionProp::StrToFile(LPCTSTR str, bool bPressMark)
{
	CString token(str);
	if(bPressMark)
	{
		for( int i = 0; i < token.GetLength(); i++)
			token.SetAt(i,token.GetAt(i)^PRESS_MARK_MASK);

	}

	return token;
}

void COleDBConnectionProp::FileToStr(CArchive& ar, CString& str, bool bPressMark)
{
	CString token;
	ar >> token;

	if(bPressMark)
	{
		for( int i = 0; i < token.GetLength(); i++)
			token.SetAt(i,token.GetAt(i)^PRESS_MARK_MASK);

	}
	str = token;
}

void COleDBConnectionProp::SetDSN(LPCSTR dsn)
{
	m_strDSN = dsn;
}
void COleDBConnectionProp::SetUID(LPCSTR uid)
{
	m_strLoginName = uid;
}
void COleDBConnectionProp::SetPassword(LPCSTR pwd)
{
	m_strPassword = pwd;
}


bool COleDBConnectionProp::SaveSettings(LPCTSTR lpszAppSection,LPCTSTR lpszEntry,LPCTSTR lpszValue)
{
	LPCTSTR lpszIniFileName = m_strIniFileName;
	if (m_bSaveInRegistry )
		return AfxGetApp()->WriteProfileString( lpszAppSection,lpszEntry ,lpszValue)== TRUE;
	return 
		::WritePrivateProfileString(lpszAppSection, lpszEntry, 
									lpszValue,lpszIniFileName) == TRUE;
}


bool COleDBConnectionProp::SaveSettings(LPCTSTR lpszAppSection)
{
	bool bok = true;

	if ( !SaveSettings( lpszAppSection,m_szDSNEntry ,m_strDSN))
		bok = false;
	if ( !SaveSettings( lpszAppSection,m_szDatabaseNameEntry ,m_strDatabaseName))
		bok = false;
	if ( !SaveSettings( lpszAppSection,m_szTableEntry ,m_strTableName))
		bok = false;
	if ( !SaveSettings( lpszAppSection,m_szLoginNameEntry ,m_strLoginName))
		bok = false;
	if ( !SaveSettings( lpszAppSection,m_szPasswordEntry ,m_strPassword))
		bok = false;
	if ( !SaveSettings( lpszAppSection,m_szServerNameEntry ,m_strServerName))
		bok = false;

	return bok;
}

CString COleDBConnectionProp::LoadSettings(LPCTSTR lpszAppSection,LPCTSTR lpszEntry)
{ 
	AFX_DATADEF TCHAR afxChNil = '\0';
	
	LPCTSTR lpszIniFileName = m_strIniFileName;
	if (m_bSaveInRegistry)
		return  AfxGetApp()->GetProfileString( lpszAppSection,lpszEntry );

	LPCTSTR	lpszDefault = &afxChNil;    // don't pass in NULL
	TCHAR szT[4096];
	DWORD dw = ::GetPrivateProfileString(lpszAppSection, lpszEntry,
			lpszDefault, szT, sizeof(szT),lpszIniFileName);
	ASSERT(dw < 4095);
	return szT;
}

bool COleDBConnectionProp::LoadSettings(LPCTSTR lpszAppSection)
{
	bool bok = true;
	CString value;

	if(m_strLoginName.IsEmpty())
	{
		value = LoadSettings( lpszAppSection,m_szLoginNameEntry );
		if(value.IsEmpty())
			bok = false;
		m_strLoginName = value; 
	}

	if(m_strPassword.IsEmpty())
	{
		value = LoadSettings( lpszAppSection,m_szPasswordEntry );
		m_strPassword = value; 
	}

	// The variables can be set up from comand line
	if(m_strDSN.IsEmpty())
	{
		value = LoadSettings(lpszAppSection, m_szDSNEntry );
		if(value.IsEmpty())
			bok = false;

		m_strDSN = value; 
	}


	if(m_strDatabaseName.IsEmpty())
	{
		value = LoadSettings( lpszAppSection,m_szDatabaseNameEntry );
		m_strDatabaseName = value; 
	}

	if(m_strTableName.IsEmpty())
	{
		value = LoadSettings( lpszAppSection,m_szTableEntry );
		if(value.IsEmpty())
			bok = false;
		m_strTableName = value; 
	}

	if(m_strServerName.IsEmpty())
	{
		value = LoadSettings( lpszAppSection,m_szServerNameEntry );
		if(value.IsEmpty())
			bok = false;
		m_strServerName = value; 
	}

	return bok;
}

#ifdef ODBDC_SUPPORT

bool COleDBConnectionProp::Connect(CDatabase& database, bool bShowDialog)
{
	CWaitCursor cursor;

	if(m_strDSN.IsEmpty())
	{

		ShowError("Empty ODBC Source");
		return false;
	}
	if(m_strLoginName.IsEmpty())
	{

		ShowError("Empty Login Name");
		return false;
	}

	CString ConnectString = 
	"DSN="			+ m_strDSN			+ ";";

	if(!m_strDatabaseName.IsEmpty())
	{
		ConnectString += 
		"DATABASE="		+ m_strDatabaseName + ";";
	}
	
	ConnectString += 
	"UID="			+ m_strLoginName	+ ";"	+
	"PWD="			+ m_strPassword		+ ";"
	;

	try
	{

		DWORD dwOptions = CDatabase::useCursorLib;
		if(!bShowDialog)
			dwOptions |= CDatabase::noOdbcDialog;
		if(database.IsOpen())
			database.Close();
		if(!database.OpenEx(ConnectString,dwOptions))
		{
			return false;
		}
	}
	catch( CDBException* pExc)
	{

		pExc->ReportError();
		pExc->Delete();
		return false;

	}

	return true;
}

bool COleDBConnectionProp::ReadProps(CDatabase& database)
{
	return ReadProps(database.GetConnect());
}

bool COleDBConnectionProp::ReadProps(const CString strConnectionString)
{
	CString strConnection = strConnectionString;

	CString strToken;
	while( !(strToken = GetNextToken(strConnection,";")).IsEmpty())
	{
		CString strTok	 = GetNextToken(strToken,"=");
		strTok.TrimLeft(); strTok.TrimRight();
		CString strValue = GetNextToken(strToken,"");
		strValue.TrimLeft(); strValue.TrimRight();

		if(strTok.CompareNoCase(m_szDSNEntry) == 0)
			m_strDSN = strValue;
		else
		if(strTok.CompareNoCase(m_szServerNameEntry) == 0)
			m_strServerName = strValue;
		else
		if(strTok.CompareNoCase(m_szLoginNameEntry) == 0)
			m_strLoginName = strValue;
		else
		if(strTok.CompareNoCase(m_szDatabaseNameEntry) == 0)
			m_strDatabaseName = strValue;
		else
		if(strTok.CompareNoCase(m_szPasswordEntry) == 0)
			m_strPassword = strValue;
		else
		if(strTok.CompareNoCase(m_szTableEntry) == 0)
			m_strTableName = strValue;
	}

	return true;
}

#else

bool COleDBConnectionProp::ConnectMSSQLServer(ATL::CDataSource* pDataSource,CSession* pSession)
{
	ASSERT(pDataSource);

	m_strDatabaseName = g_sDBName;
	m_strLoginName = g_sDBUser;
	m_strPassword = g_sDBPassword;
	m_strServerName = g_sDBDNS;


	CComBSTR bstrServer(m_strServerName);
	CComBSTR bstrUser(m_strLoginName);
	CComBSTR bstrPassword(m_strPassword);
	CComBSTR bstrDatabase(m_strDatabaseName);


	if (pSession && pSession->m_spOpenRowset != NULL)
		pSession->m_spOpenRowset.Release();

	
	CDBPropSet	dbinit(DBPROPSET_DBINIT);

	dbinit.AddProperty(DBPROP_AUTH_PASSWORD, bstrPassword);
	dbinit.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	dbinit.AddProperty(DBPROP_AUTH_USERID, bstrUser);
	dbinit.AddProperty(DBPROP_INIT_CATALOG, bstrDatabase);
	dbinit.AddProperty(DBPROP_INIT_DATASOURCE, bstrServer);
	dbinit.AddProperty(DBPROP_INIT_LCID, (long)1049);
	dbinit.AddProperty(DBPROP_INIT_PROMPT, (short)4);

	
	CLSID clsid = {0xdee35070L,0x506b,0x11cf, 
	              {0xb1,0xaa,0x0,0xaa,0x0,0xb8,0xde,0x95}};

	
	if(FAILED(pDataSource->Open(_T("SQLOLEDB.1"), &dbinit)))
	{
		CString strMsg = "Cannot connect to data source";
		strMsg += "\nServer\t= "	+ m_strServerName;
		strMsg += "\nDatabase\t= "	+ m_strDatabaseName;
		strMsg += "\nLogin\t= "		+ m_strLoginName;
		strMsg += "\nPassword\t= "	+ m_strPassword;

		AfxMessageBox(strMsg);
		if(pDataSource)
		{
			pDataSource->Close();
		}
		goto ErrorExit;
	}
	else
	{
		if (pSession && pSession->Open(*pDataSource) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source"));
			goto ErrorExit;
		}
	}
	return true;

ErrorExit:
	CloseConnection();
	return false;
}

bool COleDBConnectionProp::ConnectMSOracle(ATL::CDataSource* pDataSource,CSession* pSession)
{
	ASSERT(pDataSource);

	m_strDatabaseName = g_sDBName;
	m_strLoginName = g_sDBUser;
	m_strPassword = g_sDBPassword;
	m_strServerName = g_sDBDNS;


	CComBSTR bstrServer(m_strServerName);
	CComBSTR bstrUser(m_strLoginName);
	CComBSTR bstrPassword(m_strPassword);
	CComBSTR bstrDatabase(m_strDatabaseName);


	if (pSession && pSession->m_spOpenRowset != NULL)
		pSession->m_spOpenRowset.Release();

	
	CDBPropSet	dbinit(DBPROPSET_DBINIT);

	dbinit.AddProperty(DBPROP_AUTH_PASSWORD, bstrPassword);
	dbinit.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	dbinit.AddProperty(DBPROP_AUTH_USERID, bstrUser);
	dbinit.AddProperty(DBPROP_INIT_DATASOURCE, bstrDatabase);
	dbinit.AddProperty(DBPROP_INIT_LCID, (long)1049);
	dbinit.AddProperty(DBPROP_INIT_PROMPT, (short)4);

		
	
	if(FAILED(pDataSource->Open(_T("MSDAORA"), &dbinit)))
	{
		CString strMsg = "Cannot connect to data source";
		strMsg += "\nDatabase\t= "	+ m_strDatabaseName;
		strMsg += "\nLogin\t= "		+ m_strLoginName;
		strMsg += "\nPassword\t= "	+ m_strPassword;

		AfxMessageBox(strMsg);
		if(pDataSource)
		{
			pDataSource->Close();
		}
		goto ErrorExit;
	}
	else
	{
		if (pSession && pSession->Open(*pDataSource) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source"));
			goto ErrorExit;
		}
	}
	return true;

ErrorExit:
	CloseConnection();
	return false;
}

bool COleDBConnectionProp::ConnectMySQL(ATL::CDataSource* pDataSource,CSession* pSession)
{
	ASSERT(pDataSource);

	m_strDatabaseName = g_sDBName;
	m_strLoginName = g_sDBUser;
	m_strPassword = g_sDBPassword;
	m_strServerName = g_sDBDNS;


	CComBSTR bstrServer(m_strServerName);
	CComBSTR bstrUser(m_strLoginName);
	CComBSTR bstrPassword(m_strPassword);
	CComBSTR bstrDatabase(m_strDatabaseName);


	if (pSession && pSession->m_spOpenRowset != NULL)
		pSession->m_spOpenRowset.Release();

	
	CDBPropSet	dbinit(DBPROPSET_DBINIT);

	dbinit.AddProperty(DBPROP_AUTH_PASSWORD, bstrPassword);
	dbinit.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
	dbinit.AddProperty(DBPROP_AUTH_USERID, bstrUser);
	dbinit.AddProperty(DBPROP_INIT_LOCATION, bstrServer);
	dbinit.AddProperty(DBPROP_INIT_DATASOURCE, bstrDatabase);
	dbinit.AddProperty(DBPROP_INIT_LCID, (long)1049);
	dbinit.AddProperty(DBPROP_INIT_PROMPT, (short)4);

		
	
	if(FAILED(pDataSource->Open(_T("MySQLProv"), &dbinit)))
	{
		CString strMsg = "Cannot connect to data source";
		strMsg += "\nServer\t= "	+ m_strServerName;
		strMsg += "\nDatabase\t= "	+ m_strDatabaseName;
		strMsg += "\nLogin\t= "		+ m_strLoginName;
		strMsg += "\nPassword\t= "	+ m_strPassword;

		AfxMessageBox(strMsg);
		if(pDataSource)
		{
			pDataSource->Close();
		}
		goto ErrorExit;
	}
	else
	{
		if (pSession && pSession->Open(*pDataSource) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source"));
			goto ErrorExit;
		}
	}
	return true;

ErrorExit:
	CloseConnection();
	return false;
}



bool COleDBConnectionProp::ConnectOracle(ATL::CDataSource* pDataSource,CSession* pSession)
{
	ASSERT(pDataSource);

	m_strDatabaseName = g_sDBName;
	m_strLoginName = g_sDBUser;
	m_strPassword = g_sDBPassword;
	m_strServerName = g_sDBDNS;


	CComBSTR bstrServer(m_strServerName);
	CComBSTR bstrUser(m_strLoginName);
	CComBSTR bstrPassword(m_strPassword);
	CComBSTR bstrDatabase(m_strDatabaseName);


	if (pSession && pSession->m_spOpenRowset != NULL)
		pSession->m_spOpenRowset.Release();

	
		
	if(FAILED(pDataSource->Open(_T("OraOLEDB.Oracle"), m_strDatabaseName, m_strLoginName, _T("change to install") )))
	{
		CString strMsg = "Cannot connect to data source";
		strMsg += "\nDatabase\t= "	+ m_strDatabaseName;
		strMsg += "\nLogin\t= "		+ m_strLoginName;

		AfxMessageBox(strMsg);
		if(pDataSource)
		{
			pDataSource->Close();
		}
		goto ErrorExit;
	}
	else
	{
		if (pSession && pSession->Open(*pDataSource) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source"));
			goto ErrorExit;
		}
	}
	return true;

ErrorExit:
	CloseConnection();
	return false;
}

bool COleDBConnectionProp::ConnectDB2(ATL::CDataSource* pDataSource,CSession* pSession)
{
	ASSERT(pDataSource);

	m_strDatabaseName = g_sDBName;
	m_strLoginName = g_sDBUser;
	m_strPassword = g_sDBPassword;
	m_strServerName = g_sDBDNS;


	CComBSTR bstrServer(m_strServerName);
	CComBSTR bstrUser(m_strLoginName);
	CComBSTR bstrPassword(m_strPassword);
	CComBSTR bstrDatabase(m_strDatabaseName);


	if (pSession && pSession->m_spOpenRowset != NULL)
		pSession->m_spOpenRowset.Release();

	
		
	if(FAILED(pDataSource->Open(_T("IBMDADB2.1"), m_strDatabaseName, m_strLoginName, m_strPassword )))
	{
		CString strMsg = "Cannot connect to data source";
		strMsg += "\nDatabase\t= "	+ m_strDatabaseName;
		strMsg += "\nLogin\t= "		+ m_strLoginName;
		strMsg += "\nPassword\t= "	+ m_strPassword;

		AfxMessageBox(strMsg);
		if(pDataSource)
		{
			pDataSource->Close();
		}
		goto ErrorExit;
	}
	else
	{
		if (pSession && pSession->Open(*pDataSource) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source"));
			goto ErrorExit;
		}
	}
	return true;

ErrorExit:
	CloseConnection();
	return false;
}



bool COleDBConnectionProp::ConnectMSAccess(ATL::CDataSource* pDataSource,CSession* pSession)
{
	ASSERT(pDataSource);

	m_strDatabaseName = g_sDBName;
	m_strLoginName = g_sDBUser;
	m_strPassword = g_sDBPassword;
	m_strServerName = g_sDBDNS;

	CComBSTR bstrServer(m_strServerName);
	CComBSTR bstrUser(m_strLoginName);
	CComBSTR bstrPassword(m_strPassword);
	CComBSTR bstrDatabase(m_strDatabaseName);


	if (pSession && pSession->m_spOpenRowset != NULL)
		pSession->m_spOpenRowset.Release();

	
	
	CLSID clsid = {0xdee35070L,0x506b,0x11cf, 
	              {0xb1,0xaa,0x0,0xaa,0x0,0xb8,0xde,0x95}};

	
	if(FAILED(pDataSource->Open(clsid, m_strDatabaseName, NULL, NULL, DB_MODE_SHARE_EXCLUSIVE)))
	{
		CString strMsg = "Cannot connect to data source";
		strMsg += "\nDatabase\t= "	+ m_strDatabaseName;

		AfxMessageBox(strMsg);
		if(pDataSource)
		{
			pDataSource->Close();
		}
		goto ErrorExit;
	}
	else
	{
		if (pSession && pSession->Open(*pDataSource) != S_OK)
		{
			AfxMessageBox(_T("Couldn't create session on data source"));
			goto ErrorExit;
		}
	}
	return true;

ErrorExit:
	CloseConnection();
	return false;
}


#endif

void COleDBConnectionProp::CloseConnection()
{
#ifdef ODBDC_SUPPORT
#else
	if(m_Session.m_spOpenRowset)
		m_Session.Close();

	if(m_DataSource.m_spInit)
		m_DataSource.Close();
#endif
}

void COleDBConnectionProp::ShowError(LPCTSTR error)
{
	MessageBox(NULL,error,_T("Error"),MB_ICONERROR | MB_OK);
}

bool COleDBConnectionProp::LoadFromFile(LPCTSTR FileName)
{
	LPCTSTR iniFileName = FileName;
	try
	{
		CFile file(iniFileName,CFile::modeRead);
		CArchive ar(&file,CArchive::load);
		Serialize(ar);
	}
	catch(CFileException *ex)
	{
		ex->Delete();
		return false;

	}
	catch(CArchiveException *exAr)
	{
		exAr->Delete();
		return false;

	}

	return true;
}

void COleDBConnectionProp::SaveToFile(LPCTSTR FileName)
{
	LPCTSTR iniFileName = FileName;
	try
	{
		CFile file(iniFileName,CFile::modeWrite | CFile::modeCreate);
		CArchive ar(&file,CArchive::store);
		Serialize(ar);
	}
	catch(CFileException *ex)
	{
		ex->Delete();
		return ;

	}
	catch(CArchiveException *exAr)
	{
		exAr->Delete();
		return ;

	}
}
