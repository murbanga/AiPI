// SQLQuery.h: interface for the CSQLQuery class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQLQUERY_H__8DC91E9B_037C_11D3_8591_00C0DF240228__INCLUDED_)
#define AFX_SQLQUERY_H__8DC91E9B_037C_11D3_8591_00C0DF240228__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

#ifndef __AFXDB_H__
#include <afxdb.h> // for ...
#endif 

class CQueryObject : public CObject
{
	DECLARE_DYNAMIC(CQueryObject)
public:
	CQueryObject();
	CQueryObject(const COleVariant& value);
	virtual ~CQueryObject();
	void RemoveAndDestroy();

    CQueryObject& operator>>(BYTE &value);
    CQueryObject& operator>>(short &);
    CQueryObject& operator>>(int &);
    CQueryObject& operator>>(long &);
    CQueryObject& operator>>(float &);
    CQueryObject& operator>>(double &);
    CQueryObject& operator>>(CY &value);
    CQueryObject& operator>>(COleCurrency &value);
	CQueryObject& operator>>(CTime &value);
	CQueryObject& operator>>(COleDateTime &value);
	CQueryObject& operator>>(CString &value);
	CQueryObject& operator>(CString &value);

	COleVariant		m_value;
};


class CQueryObjectList : public CTypedPtrList<CObList,CQueryObject*>
{
public:
	CQueryObjectList();
	virtual ~CQueryObjectList();

	void RemoveAndDestroy();
	bool eof();
	void InitPosition();

    CQueryObjectList& operator>>(BYTE &value);
    CQueryObjectList& operator>>(short &);
    CQueryObjectList& operator>>(CY &value);
    CQueryObjectList& operator>>(COleCurrency &value);
    CQueryObjectList& operator>>(int &);
    CQueryObjectList& operator>>(long &);
    CQueryObjectList& operator>>(float &);
    CQueryObjectList& operator>>(double &);
	CQueryObjectList& operator>>(TIMESTAMP_STRUCT &value);
	CQueryObjectList& operator>>(CTime &value);
	CQueryObjectList& operator>>(COleDateTime &value);
	CQueryObjectList& operator>>(CString &value);
	CQueryObjectList& operator>(CString &value);

protected:

	POSITION m_pos;
};

inline 
bool CQueryObjectList::eof()
{
	return m_pos == NULL;
}

struct MYBIND
{
	MYBIND()
	{
		memset(this, 0, sizeof(*this));
	}

	TCHAR   szValue[40];
	DWORD   dwStatus;
};

struct MYERRORINFO
{
	BSTR    bstrSource;
	BSTR    bstrDescription;
	DWORD   dwHelpContext;
	GUID    guid;
	BSTR    bstrHelpFile;
};

class CWhyResults
{
public:
	bool UseMultipleResults() { return m_bMultiple; }
	IMultipleResults** GetMultiplePtrAddress() { return m_bMultiple? &m_spMultipleResults.p : NULL; }
	IMultipleResults* GetMultiplePtr() { return m_bMultiple? m_spMultipleResults : NULL; }

	CComPtr<IMultipleResults> m_spMultipleResults;

	bool m_bMultiple;
};

class CQueryCommand : public	CCommand<CDynamicAccessor, CRowset, CWhyResults>
{
public:
	CQueryCommand(bool bMultiple)
	{
	  m_bMultiple = bMultiple;
	}
};

class CMultipleQuery : public	CQueryCommand
{
public:
	CMultipleQuery():CQueryCommand(true){}
};

class CSingleQuery : public CQueryCommand
{
public:
	CSingleQuery():CQueryCommand(false){}
};

class CSQLQuery : public CObject  
{
	DECLARE_DYNAMIC(CSQLQuery)
public:
	CSQLQuery(ATL::CDataSource* pDataSource,bool bShowError = true);
	CSQLQuery(ATL::CDataSource* pDataSource,ATL::CSession* pSession,bool bShowError = true);
	CSQLQuery(ATL::CSession* pSession,bool bShowError = true);
	virtual ~CSQLQuery();

	CString				GetLastError();
	ATL::CSession*		GetSession() const;
	ATL::CDataSource*	GetDataSource() const;
	int					GetDataCount();
	CQueryObjectList&	GetDataList();
	
	UINT			GetColumnsCount();
	void			GetColumns(CStringArray& dest);
	const CString	GetColumnName(int nIndex);


	HRESULT		BeginTrans();
	HRESULT		Abort(BOID* pboidReason = NULL, BOOL bRetaining = FALSE, BOOL bAsync = FALSE) const;
	HRESULT		Commit(BOOL bRetaining = FALSE, DWORD grfTC = XACTTC_SYNC, DWORD grfRM = 0) const;
	
	void AddColumns(LPCTSTR lpszCol);
	void ClearColumns();
	bool eof();
	void Empty();
	bool IsExistColumn(LPCTSTR lpszCol);
	void RemoveLastComma();
	
	bool ExecuteSQL();
	bool ExecuteSQL(LPCSTR szSQL);
	
	CQueryObject* Get();

    CSQLQuery& operator>>(BYTE &value);
    CSQLQuery& operator>>(short &);
    CSQLQuery& operator>>(CY &value);
    CSQLQuery& operator>>(COleCurrency &value);
    CSQLQuery& operator>>(int &);
    CSQLQuery& operator>>(long &);
    CSQLQuery& operator>>(float &);
    CSQLQuery& operator>>(double &);
	CSQLQuery& operator>>(CTime &value);
	CSQLQuery& operator>>(COleDateTime &value);
	CSQLQuery& operator>>(CString &value);
	CSQLQuery& operator>(CString &value);


	const CSQLQuery& operator =(const LPCTSTR& right);
	const CSQLQuery& operator +=(const LPCTSTR& right);

    CSQLQuery& operator<<(const long value);
    CSQLQuery& operator<<(const double value);
    CSQLQuery& operator<<(const BYTE value);
    CSQLQuery& operator<<(const short value);
    CSQLQuery& operator<<(const int value);
    CSQLQuery& operator<<(const float value);
	CSQLQuery& operator<<(LPCTSTR value);
	CSQLQuery& operator<<(const CTime &value);
	

protected:

	void DeleteCommand();
	void ShowError(LPCTSTR error);
	void ShowDBError(IUnknown* pUnk, const IID& iid );
	bool CheckDBError(IUnknown* pUnk, const IID& iid );
	bool InitSession();
	COleVariant ToVariant(CDynamicAccessor*,int nCol);

protected:

	ATL::CDataSource*		m_pDataSource;
	CString					m_strDatabase;
	ATL::CSession*			m_pSession;
	CStringArray			m_columns;
	CQueryCommand*			m_pCommand;

	CQueryObjectList		m_object_list;

	CString					m_strError;
	bool					m_bMySession;

public:
	CString			m_strQuery;
	bool			m_bShowError;

};

inline
HRESULT	CSQLQuery::BeginTrans()
{
	ASSERT(m_pSession);
	if(m_pSession)
		return m_pSession->StartTransaction();
	else return S_FALSE;
}
inline
HRESULT	CSQLQuery::Abort(BOID* pboidReason, BOOL bRetaining, BOOL bAsync) const
{
	ASSERT(m_pSession);
	if(m_pSession)
		return m_pSession->Abort(pboidReason,bRetaining,bAsync);
	else return S_FALSE;
}
inline
HRESULT	CSQLQuery::Commit(BOOL bRetaining, DWORD grfTC, DWORD grfRM) const
{
	ASSERT(m_pSession);
	if(m_pSession)
		return m_pSession->Commit(bRetaining,grfTC,grfRM);
	else return S_FALSE;
}

inline
CQueryObjectList& CSQLQuery::GetDataList()
{ m_object_list.InitPosition();return m_object_list; }

inline
CString	CSQLQuery::GetLastError()
{ return m_strError;}

inline
ATL::CSession* CSQLQuery::GetSession() const
{ return	m_pSession;}

inline
ATL::CDataSource*CSQLQuery::GetDataSource() const
{ return m_pDataSource;}

inline
int	CSQLQuery::GetDataCount()			
{ return m_object_list.GetCount();}

inline
const CSQLQuery& CSQLQuery::operator =(const LPCTSTR& right)
{
	m_strQuery = right;
	return *this;
}
inline
const CSQLQuery& CSQLQuery::operator +=(const LPCTSTR& right)
{
	m_strQuery += right;
	return *this;
}
inline
CSQLQuery& CSQLQuery::operator<<(const long value)
{
	CString str; str.Format(_T("%d"),value);
	m_strQuery += str;
	return *this;
}
inline
CSQLQuery& CSQLQuery::operator<<(const double value)
{
	CString str; str.Format(_T("%f"),value);
	m_strQuery += str;
	return *this;
}
inline
CSQLQuery& CSQLQuery::operator<<(const BYTE value)
{
	return *this << (long) value;
}
inline
CSQLQuery& CSQLQuery::operator<<(const short value)
{
	return *this << (long) value;
}
inline
CSQLQuery& CSQLQuery::operator<<(const int value)
{
	return *this << (long) value;
}
inline
CSQLQuery& CSQLQuery::operator<<(const float value)
{
	return *this << (double) value;
}
inline
CSQLQuery& CSQLQuery::operator<<(LPCTSTR value)
{
	m_strQuery += value;
	return *this;
}
inline
CSQLQuery& CSQLQuery::operator<<(const CTime &value)
{
	m_strQuery += value.Format(_T("'%m/%d/%Y %H:%M:%S'"));
	return *this;
}

inline 
bool CSQLQuery::eof()
{
	return m_object_list.IsEmpty()== TRUE;
}
inline CSQLQuery& __cdecl ccc(CSQLQuery& query) { return query << _T(" , "); }

#endif // !defined(AFX_SQLQUERY_H__8DC91E9B_037C_11D3_8591_00C0DF240228__INCLUDED_)
