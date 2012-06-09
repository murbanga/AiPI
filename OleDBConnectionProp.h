#if !defined(AFX_OLEDBCONNECTIONPROP_H__3C3307CF_1817_4FB2_9E14_47A122A61CDF__INCLUDED_)
#define AFX_OLEDBCONNECTIONPROP_H__3C3307CF_1817_4FB2_9E14_47A122A61CDF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OleDBConnectionProp.h : header file
//
#ifdef ODBDC_SUPPORT

#ifndef __AFXDB_H__
#include <afxdb.h>
#endif 
class CDatabase;

#else

class ATL::CDataSource;
class ATL::CSession;

#endif
/////////////////////////////////////////////////////////////////////////////
// COleDBConnectionProp window
class COleDBConnectionProp : public CObject  
{
	DECLARE_SERIAL(COleDBConnectionProp)
public:
	COleDBConnectionProp(bool bSaveInRegistry = true);
	virtual ~COleDBConnectionProp();
	const COleDBConnectionProp& operator =(const COleDBConnectionProp& right);

	void Copy(const COleDBConnectionProp& right);
	
	void SetDSN(LPCSTR dsn);
	void SetUID(LPCSTR uid);
	void SetPassword(LPCSTR pwd);

	bool SaveSettings(LPCTSTR lpszAppSection = _T("Connection"));
	bool LoadSettings(LPCTSTR lpszAppSection = _T("Connection"));

	void SaveToFile(LPCTSTR FileName);
	bool LoadFromFile(LPCTSTR FileName);

#ifdef ODBDC_SUPPORT
	bool Connect(CDatabase& database, bool bShowDialog = true);
	bool ReadProps(CDatabase& database);
	bool ReadProps(const CString strConnectionString);
#else
	ATL::CSession*		GetSession();
	ATL::CDataSource*	GetDataSource();
	//bool Connect(ATL::CDataSource* pDataSource,CSession* pSession);
	bool ConnectMSAccess(ATL::CDataSource* pDataSource,CSession* pSession);
	bool ConnectMSSQLServer(ATL::CDataSource* pDataSource,CSession* pSession);
	bool ConnectMSOracle(ATL::CDataSource* pDataSource,CSession* pSession);
	bool ConnectOracle(ATL::CDataSource* pDataSource,CSession* pSession);
	bool ConnectMySQL(ATL::CDataSource* pDataSource,CSession* pSession);
	bool ConnectDB2(ATL::CDataSource* pDataSource,CSession* pSession);
#endif

	bool Connect(int iDBType);
	void CloseConnection();

	void ShowError(LPCTSTR error);

// Overrides

	virtual void Serialize(CArchive& ar);
	CString StrToFile(LPCTSTR str, bool sMark = true);
	void	FileToStr(CArchive& ar, CString& str, bool bPressMark = true);

public:

	CString			m_strDSN;
	CString			m_strServerName;
	CString			m_strDatabaseName;
	CString			m_strTableName;
	CString			m_strLoginName;
	CString			m_strPassword;

	CString			m_strIniFileName;

	// 
#ifndef ODBDC_SUPPORT
	ATL::CSession		m_Session;
	ATL::CDataSource	m_DataSource;
#endif

protected:
	bool SaveSettings(LPCTSTR lpszAppSection,LPCTSTR lpszEntry,LPCTSTR lpszValue);
	CString LoadSettings(LPCTSTR lpszAppSection,LPCTSTR lpszEntry);

public:
	static LPCTSTR	m_szDSNEntry;
	static LPCTSTR	m_szLoginNameEntry;
	static LPCTSTR	m_szDatabaseNameEntry;
	static LPCTSTR	m_szPasswordEntry;
	static LPCTSTR	m_szTableEntry;
	static LPCTSTR	m_szServerNameEntry;

protected:
	bool			m_bSaveInRegistry;

};

#ifndef ODBDC_SUPPORT

inline
ATL::CSession* COleDBConnectionProp::GetSession()
{
	return &m_Session;
}
inline
ATL::CDataSource* COleDBConnectionProp::GetDataSource()
{
	return &m_DataSource;
}
inline
bool COleDBConnectionProp::Connect(int iDBType)
{
	switch(iDBType)
	{
	case MS_ACCESS :
		return ConnectMSAccess(&m_DataSource, &m_Session);
			
	case MS_SQLSERVER:
		return ConnectMSSQLServer(&m_DataSource, &m_Session);
			
	case MS_ORACLE:
		return ConnectMSOracle(&m_DataSource, &m_Session);
			
	case ORACLE:
		return ConnectOracle(&m_DataSource, &m_Session);
	case MYSQL:
		return ConnectMySQL(&m_DataSource, &m_Session);
			
	case DB2:
		return ConnectMySQL(&m_DataSource, &m_Session);
	default:
		return 0;
		
	}

	 

}
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OLEDBCONNECTIONPROP_H__3C3307CF_1817_4FB2_9E14_47A122A61CDF__INCLUDED_)
