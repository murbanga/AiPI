/////////////////////////////////////////////////////////////////
//                                                             //
//                SQLQuery.cpp                                 //
//     implementation of the CSQLQuery class                   //
//-------------------------------------------------------------//
//             By Eugene Khodakovsky                           //
//                  June, 2000                                 //
//             Eugene@cpplab.com                               //
//            Last Update: April, 2002                         //
/////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SQLQuery.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define pACCESSOR	((CDynamicAccessor*)m_pCommand)

//////////////////////////////////////////////////////////////////////
// CQueryObject

IMPLEMENT_DYNAMIC(CQueryObject,CObject);

CQueryObject::CQueryObject()
{
	m_value.vt = VT_EMPTY;
}
CQueryObject::CQueryObject(const COleVariant& value)
{
	m_value = value;
}

CQueryObject::~CQueryObject()
{
	HRESULT hr =  ::VariantClear(&m_value);
	if (FAILED(hr))
	{
		ASSERT(0);
	}
}
void CQueryObject::RemoveAndDestroy()
{
	HRESULT hr =  ::VariantClear(&m_value);
	if (FAILED(hr))
	{
		ASSERT(0);
	}
	delete this;
}

CQueryObject& CQueryObject::operator>>(BYTE &value)
{
	if( m_value.vt == VT_EMPTY ||  m_value.vt == VT_NULL)
	{
		value = NULL;
	}
	else
	{
		ASSERT(m_value.vt == VT_I1 || m_value.vt == VT_UI1);
		value = m_value.intVal;
	}
	return *this;
}

CQueryObject& CQueryObject::operator>>(short &value)
{
	if( m_value.vt == VT_EMPTY ||  m_value.vt == VT_NULL)
	{
		value = NULL;
	}
	else
	{
		ASSERT(m_value.vt == VT_I2);
		value = m_value.iVal;
	}
	return *this;
}

CQueryObject& CQueryObject::operator>>(COleCurrency &value)
{
	if( m_value.vt == VT_EMPTY ||  m_value.vt == VT_NULL)
	{
		value.SetStatus(COleCurrency::CurrencyStatus::invalid);
	}
	else
	{
		ASSERT(m_value.vt == VT_CY);
		value = m_value;
	}
	return *this;
}

CQueryObject& CQueryObject::operator>>(CY &value)
{
	if( m_value.vt == VT_EMPTY ||  m_value.vt == VT_NULL)
	{
		value.Lo = NULL;
		value.Hi = NULL;
	}
	else
	{
		ASSERT(m_value.vt == VT_CY);
		value = m_value.cyVal;
	}
	return *this;
}

CQueryObject& CQueryObject::operator>>(int &value)
{
	if( m_value.vt == VT_EMPTY ||  m_value.vt == VT_NULL)
	{
		value = NULL;
	}
	else
	{
		ASSERT(m_value.vt == VT_I4);
		value = m_value.iVal;
	}
	return *this;
}

CQueryObject& CQueryObject::operator>>(long &value)
{
	if( m_value.vt == VT_EMPTY ||  m_value.vt == VT_NULL)
	{
		value = NULL;
	}
	else
	{
		ASSERT(m_value.vt == VT_I4);
		value = m_value.lVal;
	}
	return *this;
}

CQueryObject& CQueryObject::operator>>(float &value)
{
	if( m_value.vt == VT_EMPTY ||  m_value.vt == VT_NULL)
	{
		value = NULL;
	}
	else
	{
		ASSERT(m_value.vt == VT_R4);
		value = m_value.fltVal;
	}
	return *this;
}

CQueryObject& CQueryObject::operator>>(double &value)
{
	if( m_value.vt == VT_EMPTY ||  m_value.vt == VT_NULL)
	{
		value = NULL;
	}
	else
	{
		ASSERT(m_value.vt == VT_R8);
		value = m_value.dblVal;
	}
	return *this;
}

CQueryObject& CQueryObject::operator>>(COleDateTime &value)
{
	if( m_value.vt == VT_EMPTY ||  m_value.vt == VT_NULL)
	{
		//value = NULL;
	}
	else
	{
		ASSERT(m_value.vt == VT_DATE);
		value = m_value.date;
	}
	return *this;
}

CQueryObject& CQueryObject::operator>>(CTime &value)
{
	COleDateTime date;
	*this >> date;
	CTime time( date.GetYear(),date.GetMonth(),date.GetDay(),
				date.GetHour(),date.GetMinute(),date.GetSecond());
	value = time;
	return *this;
}
CQueryObject& CQueryObject::operator>>(CString &value)
{
	if( m_value.vt == VT_EMPTY ||  m_value.vt == VT_NULL)
	{
		value.Empty();
	}
	else
	{
		ASSERT(m_value.vt == VT_BSTR);
		value = m_value.bstrVal;
	}
	return *this;
}

CQueryObject& CQueryObject::operator>(CString &value)
{
	COleDateTime date;
	switch(m_value.vt)
	{
	default:
		ASSERT(0);
		break;
	case VT_CY:
		{
			COleCurrency cur(m_value.cyVal);
			value = cur.Format();
		}
		break;
	case VT_BOOL:
		value.Format(_T("%d"),m_value.boolVal);
		break;
	case VT_DATE:
		date = m_value;
		value =	date.Format(_T("%d %b.%Y"));
		break;
	case VT_EMPTY:
	case VT_NULL:
		value.Empty();
		break;
	case VT_I2:
	case VT_I4:
		value.Format(_T("%d"),m_value.iVal);
		break;
	case VT_R4:
		value.Format(_T("%.2f"),m_value.fltVal);
		break;
	case VT_R8:
		value.Format(_T("%.2f"),m_value.dblVal);
		break;
	case VT_BSTR:
		*this >> value;
		break;
	}
	return *this;
}

//////////////////////////////////////////////////////////////////////
// CQueryObjectList

CQueryObjectList::CQueryObjectList():
	m_pos(NULL)
{
}

CQueryObjectList::~CQueryObjectList()
{
	RemoveAndDestroy();
}

void CQueryObjectList::RemoveAndDestroy()
{
	POSITION pos = GetHeadPosition();
	while(pos != NULL)
	{
		GetNext(pos)->RemoveAndDestroy();
	}
	RemoveAll();
}

void CQueryObjectList::InitPosition()
{
	m_pos = GetHeadPosition();
}

CQueryObjectList& CQueryObjectList::operator>>(BYTE &value)
{
	if(m_pos)
		*GetNext(m_pos)>> value;
	return *this;
}
CQueryObjectList& CQueryObjectList::operator>>(short &value)
{
	if(m_pos)
		*GetNext(m_pos)>> value;
	return *this;
}
CQueryObjectList& CQueryObjectList::operator>>(CY &value)
{
	if(m_pos)
		*GetNext(m_pos)>> value;
	return *this;
}
CQueryObjectList& CQueryObjectList::operator>>(COleCurrency &value)
{
	if(m_pos)
		*GetNext(m_pos)>> value;
	return *this;
}

CQueryObjectList& CQueryObjectList::operator>>(int &value)
{
	if(m_pos)
		*GetNext(m_pos)>> value;
	return *this;
}
CQueryObjectList& CQueryObjectList::operator>>(long &value)
{
	if(m_pos)
		*GetNext(m_pos)>> value;
	return *this;
}
CQueryObjectList& CQueryObjectList::operator>>(float &value)
{
	if(m_pos)
		*GetNext(m_pos)>> value;
	return *this;
}
CQueryObjectList& CQueryObjectList::operator>>(double &value)
{
	if(m_pos)
		*GetNext(m_pos)>> value;
	return *this;
}
CQueryObjectList& CQueryObjectList::operator>>(CTime &value)
{
	if(m_pos)
		*GetNext(m_pos)>> value;
	return *this;
}
CQueryObjectList& CQueryObjectList::operator>>(COleDateTime &value)
{
	if(m_pos)
		*GetNext(m_pos)>> value;
	return *this;
}
CQueryObjectList& CQueryObjectList::operator>>(CString &value)
{
	if(m_pos)
		*GetNext(m_pos)>> value;
	return *this;
}
CQueryObjectList& CQueryObjectList::operator>(CString &value)
{
	if(m_pos)
		*GetNext(m_pos)> value;
	return *this;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CSQLQuery,CObject);

CSQLQuery::CSQLQuery(CDataSource* pDataSource,bool bShowError):
	m_pDataSource(pDataSource),
	m_bShowError(bShowError),
	m_pSession(NULL),
	m_bMySession(false),
	m_pCommand(NULL)
{
	if(pDataSource)
	{
		InitSession();
		CComVariant var;
		if(SUCCEEDED(pDataSource->
			GetProperty(DBPROPSET_DATASOURCE,DBPROP_CURRENTCATALOG, &var) &&
			var.vt != VT_EMPTY && var.vt != VT_NULL))
		{
			USES_CONVERSION;
			m_strDatabase = OLE2T(var.bstrVal);
		}
		else
		{
			ASSERT(0);
		}
	}
}

CSQLQuery::CSQLQuery(CDataSource* pDataSource,CSession* pSession,bool bShowError):
	m_pDataSource(pDataSource),
	m_bShowError(bShowError),
	m_pSession(pSession),
	m_bMySession(false),
	m_pCommand(NULL)
{
	if(pDataSource)
	{
		CComVariant var;
		if(SUCCEEDED(pDataSource->
			GetProperty(DBPROPSET_DATASOURCE,DBPROP_CURRENTCATALOG, &var) &&
			var.vt != VT_EMPTY && var.vt != VT_NULL))
		{
			USES_CONVERSION;
			m_strDatabase = OLE2T(var.bstrVal);
		}
		else
		{
			ASSERT(0);
		}
	}
}

CSQLQuery::CSQLQuery(CSession* pSession,bool bShowError):
	m_pDataSource(NULL),
	m_bShowError(bShowError),
	m_pSession(pSession),
	m_bMySession(false),
	m_pCommand(NULL)
{
}


CSQLQuery::~CSQLQuery()
{
	m_object_list.RemoveAndDestroy();
	if(m_bMySession && m_pSession)
		delete m_pSession;
	m_pSession = NULL;
	DeleteCommand();
}

void CSQLQuery::ShowError(LPCTSTR error)
{
	m_strError = (CString)error;
	if(m_bShowError)
		MessageBox(NULL,error,_T("CSQLQuery"),MB_ICONERROR | MB_OK);
}

void CSQLQuery::ShowDBError(IUnknown* pUnk, const IID& iid )
{
	CString strError;
	CDBErrorInfo errInfo;
	ULONG ulRecords = 0;
	HRESULT hr = errInfo.GetErrorRecords(pUnk,iid, &ulRecords);
	if (FAILED(hr) || hr == S_FALSE || ulRecords == 0)
	{
		ShowError(_T("NOSPECIFIED_SOURCE"));
		return ;
	}
	else 
	{
		LCID lcid = GetUserDefaultLCID();
		for (ULONG l=0; l<ulRecords; l++)
		{
			// Get the error information from the source
			struct MYERRORINFO* pInfo = new MYERRORINFO;
			hr = errInfo.GetAllErrorInfo(l, lcid, &pInfo->bstrDescription,
				&pInfo->bstrSource, &pInfo->guid, &pInfo->dwHelpContext,
				&pInfo->bstrHelpFile);
			if (FAILED(hr))
			{
				delete pInfo;
				continue;
			}

			strError += CString(pInfo->bstrDescription) + "\n";
			delete pInfo;
		}
	}

	ShowError(strError);
}

bool CSQLQuery::CheckDBError(IUnknown* pUnk, const IID& iid )
{
	CString strError;
	CDBErrorInfo errInfo;
	ULONG ulRecords = 0;
	HRESULT hr = errInfo.GetErrorRecords(pUnk,iid, &ulRecords);
	if (FAILED(hr) || hr == S_FALSE || ulRecords == 0)
	{
//		ShowError(_T("NOSPECIFIED_SOURCE"));
		return false;
	}
	else 
	{
		LCID lcid = GetUserDefaultLCID();
		for (ULONG l=0; l<ulRecords; l++)
		{
			// Get the error information from the source
			struct MYERRORINFO* pInfo = new MYERRORINFO;
			hr = errInfo.GetAllErrorInfo(l, lcid, &pInfo->bstrDescription,
				&pInfo->bstrSource, &pInfo->guid, &pInfo->dwHelpContext,
				&pInfo->bstrHelpFile);
			if (FAILED(hr))
			{
				delete pInfo;
				continue;
			}

			strError += CString(pInfo->bstrDescription) + "\n";
			delete pInfo;
		}
	}

	if(!strError.IsEmpty())
	{
		ShowError(strError);
		return true;
	}
	return false;
}

void CSQLQuery::Empty()
{
	m_strError.Empty();
	m_strQuery.Empty();
	m_object_list.RemoveAndDestroy();
	DeleteCommand();
	ClearColumns();
}

bool CSQLQuery::InitSession()
{
	ASSERT(m_pSession == NULL);

	if(m_pSession == NULL)
		m_pSession = new CSession;

	m_bMySession = true;
	if (m_pSession->m_spOpenRowset != NULL)
		m_pSession->m_spOpenRowset.Release();

	USES_CONVERSION;

	if (m_pSession->Open(*GetDataSource()) != S_OK)
	{
		ShowError(_T("Couldn't create session on data source"));
		return false;
	}

	return true;
}


COleVariant CSQLQuery::ToVariant(CDynamicAccessor*  pDynamicAccessor,int nCol)
{
	ASSERT(pDynamicAccessor != NULL);
	COleVariant vt;
	DBSTATUS dbStatus;
	DBTYPE dbType;

	pDynamicAccessor->GetStatus(nCol, &dbStatus);
	if(dbStatus == DBSTATUS_S_ISNULL)
		return vt;                      // just return a blank variant

	if(!pDynamicAccessor->GetColumnType(nCol, &dbType))
		return vt;
	switch (dbType)
	{
	case DBTYPE_VARIANT:
		vt = COleVariant((LPCVARIANT)pDynamicAccessor->GetValue(nCol));
		break;
	case DBTYPE_STR:
		vt = COleVariant(CString((LPCSTR)pDynamicAccessor->GetValue(nCol)), VT_BSTR);
		break;
	case DBTYPE_WSTR:
	case DBTYPE_BSTR:
		vt = COleVariant(CString((LPCWSTR)pDynamicAccessor->GetValue(nCol)), VT_BSTR);
		break;
	case DBTYPE_I1:
	case DBTYPE_UI1:
		vt = COleVariant(*((BYTE*)pDynamicAccessor->GetValue(nCol)));
		break;
	case DBTYPE_I2:
	case DBTYPE_UI2:
		vt = COleVariant(*((short*)pDynamicAccessor->GetValue(nCol)));
		break;
	case DBTYPE_I4:
	case DBTYPE_UI4:
		vt = COleVariant(*((long*)pDynamicAccessor->GetValue(nCol)));
		break;
	case DBTYPE_R4:
		vt = COleVariant(*((float*)pDynamicAccessor->GetValue(nCol)));
		break;
	case DBTYPE_R8:
		vt = COleVariant(*((double*)pDynamicAccessor->GetValue(nCol)));
		break;
	case DBTYPE_BOOL:
		vt = COleVariant((short)*(BOOL*)pDynamicAccessor->GetValue(nCol), VT_BOOL);
		break;
	case DBTYPE_DATE:
		{
			COleDateTime dt(*((DATE*)pDynamicAccessor->GetValue(nCol)));
			vt = COleVariant(dt);
		}
		break;
	case DBTYPE_CY:
		{
			COleCurrency cy(*((CURRENCY*)pDynamicAccessor->GetValue(nCol)));
			vt = COleVariant(cy);
		}
		break;
	case DBTYPE_NUMERIC:
		{
			DB_NUMERIC num;

			if(pDynamicAccessor->GetValue(nCol, &num))
			{
				double dbl;

				dbl = (double)*((__int64*)num.val);
				while(num.scale-- > 0)
					dbl /= 10;
				if(num.sign == 0)
					dbl = -dbl;
				vt = COleVariant(dbl);
			}
		}
		break;
	case DBTYPE_DBDATE:
		{
			DBDATE dbDate;

			if(pDynamicAccessor->GetValue(nCol, &dbDate))
			{
				COleDateTime dt;

				dt.SetDate(dbDate.year, dbDate.month, dbDate.day);
				vt = COleVariant(dt);
			}
		}
		break;
	case DBTYPE_DBTIME:
		{
			DBTIME dbTime;

			if(pDynamicAccessor->GetValue(nCol, &dbTime))
			{
				COleDateTime dt;

				dt.SetTime(dbTime.hour, dbTime.minute, dbTime.second);
				vt = COleVariant(dt);
			}
		}
		break;
	case DBTYPE_DBTIMESTAMP:
		{
			DBTIMESTAMP dbTimeStamp;

			if(pDynamicAccessor->GetValue(nCol, &dbTimeStamp))
			{
				vt = COleVariant(COleDateTime(dbTimeStamp.year, dbTimeStamp.month, dbTimeStamp.day,
											  dbTimeStamp.hour, dbTimeStamp.minute, dbTimeStamp.second));
			}
		}
		break;
	case DBTYPE_NULL:
	case DBTYPE_EMPTY:
		break;
	default:
		TRACE2("Unsupported DBTYPE (%d) in column %d\n", dbType, nCol);
		ASSERT(0);
		break;
	}
	return vt;
}

CQueryObject* CSQLQuery::Get()
{
	return m_object_list.IsEmpty() ? NULL : m_object_list.RemoveHead();
}

CSQLQuery& CSQLQuery::operator>>(BYTE &value)
{
	CQueryObject* pObj = Get();
	ASSERT(pObj);
	if(pObj)
	{
		*pObj >> value;
		delete pObj;
	}
	return *this;
}

CSQLQuery& CSQLQuery::operator>>(short &value)
{
	CQueryObject* pObj = Get();
	ASSERT(pObj);
	if(pObj)
	{
		*pObj >> value;
		delete pObj;
	}
	return *this;
}
CSQLQuery& CSQLQuery::operator>>(CY &value)
{
	CQueryObject* pObj = Get();
	ASSERT(pObj);
	if(pObj)
	{
		*pObj >> value;
		delete pObj;
	}
	return *this;
}
CSQLQuery& CSQLQuery::operator>>(COleCurrency &value)
{
	CQueryObject* pObj = Get();
	ASSERT(pObj);
	if(pObj)
	{
		*pObj >> value;
		delete pObj;
	}
	return *this;
}

CSQLQuery& CSQLQuery::operator>>(int &value)
{
	CQueryObject* pObj = Get();
	ASSERT(pObj);
	if(pObj)
	{
		*pObj >> value;
		delete pObj;
	}
	return *this;
}

CSQLQuery& CSQLQuery::operator>>(long &value)
{
	CQueryObject* pObj = Get();
	ASSERT(pObj);
	if(pObj)
	{
		*pObj >> value;
		delete pObj;
	}
	return *this;
}

CSQLQuery& CSQLQuery::operator>>(float &value)
{
	CQueryObject* pObj = Get();
	ASSERT(pObj);
	if(pObj)
	{
		*pObj >> value;
		delete pObj;
	}
	return *this;
}
CSQLQuery& CSQLQuery::operator>>(double &value)
{
	CQueryObject* pObj = Get();
	ASSERT(pObj);
	if(pObj)
	{
		*pObj >> value;
		delete pObj;
	}
	return *this;
}
CSQLQuery& CSQLQuery::operator>>(CTime &value)
{
	CQueryObject* pObj = Get();
	ASSERT(pObj);
	if(pObj)
	{
		*pObj >> value;
		delete pObj;
	}
	return *this;
}
CSQLQuery& CSQLQuery::operator>>(COleDateTime &value)
{
	CQueryObject* pObj = Get();
	ASSERT(pObj);
	if(pObj)
	{
		*pObj >> value;
		delete pObj;
	}
	return *this;
}
CSQLQuery& CSQLQuery::operator>>(CString &value)
{
	CQueryObject* pObj = Get();
	ASSERT(pObj);
	if(pObj)
	{
		*pObj >> value;
		delete pObj;
	}
	return *this;
}

CSQLQuery& CSQLQuery::operator>(CString &value)
{
	CQueryObject* pObj = Get();
	ASSERT(pObj);
	if(pObj)
	{
		*pObj > value;
		delete pObj;
	}
	return *this;
}

void CSQLQuery::AddColumns(LPCTSTR lpszCol)
{
	m_columns.Add(lpszCol);
}

void CSQLQuery::ClearColumns()
{
	m_columns.RemoveAll();
}

UINT CSQLQuery::GetColumnsCount()
{
	ASSERT(m_pCommand);
	if(!m_pCommand)
		return 0;

	UINT cnt = pACCESSOR->GetColumnCount();
	return cnt;
}

const CString CSQLQuery::GetColumnName(int nIndex)
{
	ULONG nCol = nIndex + 1;
	CString strName = pACCESSOR->GetColumnName(nCol);
	return strName;
}

void CSQLQuery::GetColumns(CStringArray& dest)
{
	UINT cnt = GetColumnsCount();
	ULONG nCol = 1;
	while(cnt--)
	{
		CString str = pACCESSOR->GetColumnName(nCol++);
		dest.Add(str);
	}
}

bool CSQLQuery::IsExistColumn(LPCTSTR lpszCol)
{
	UINT cnt = GetColumnsCount();
	if(cnt == 0)
		return false;
	ULONG nCol = 1;
	while(cnt--)
	{
		CString str = pACCESSOR->GetColumnName(nCol++);
		if(str == lpszCol)
			return true;
	}

	return false;
}

void CSQLQuery::RemoveLastComma()
{
	int idx = m_strQuery.ReverseFind(',');
	if(idx != -1)
		m_strQuery.SetAt(idx,' ');
}

bool CSQLQuery::ExecuteSQL(LPCSTR szSQL)
{
	m_strQuery = szSQL;
	return ExecuteSQL();
}

bool CSQLQuery::ExecuteSQL()
{
	HRESULT hr;
	if(m_strQuery.IsEmpty())
	{
		ShowError(_T("Empty Query"));
		return false;
	}
	
	m_object_list.RemoveAndDestroy();

	DeleteCommand();

	m_pCommand = new CSingleQuery;

	CDBPropSet	propset(DBPROPSET_ROWSET);

	bool bBind = true;
	hr = m_pCommand->Open(*GetSession(), m_strQuery, &propset, NULL, DBGUID_DEFAULT, false);
	if (hr != S_OK)
	{
		ShowDBError(m_pCommand->m_spCommand, IID_ICommand);
		return false;
	}

	if(m_pCommand->GetInterface() != NULL)
	{
		hr = m_pCommand->Bind();
		if (hr != S_OK)
		{
			ShowDBError(m_pCommand->m_spCommand, IID_ICommand);
			return false;
		}
	}

	// Display the data
	if(m_pCommand->GetInterface() != NULL)
	while(m_pCommand->MoveNext() == S_OK)
	{
		if(m_columns.GetSize() == 0)
		{
			for(ULONG nCol = 0; nCol < m_pCommand->GetColumnCount(); nCol++)
			{
				COleVariant vt = ToVariant(m_pCommand,nCol+1);
				CQueryObject*pObj = new CQueryObject(vt);
				m_object_list.AddTail(pObj);
				vt.Clear();
			}
		}
		else
		{
			for(int i = 0; i < m_columns.GetSize(); i++)
			{
				ULONG nCol = 0;
				LPCTSTR pColumnName = m_columns[i];
				bool bOk = m_pCommand->GetInternalColumnNo((TCHAR*)pColumnName,&nCol);
				ASSERT(bOk);
				COleVariant vt = ToVariant(m_pCommand,nCol+1);
				CQueryObject*pObj = new CQueryObject(vt);
				m_object_list.AddTail(pObj);
				vt.Clear();
			}
		}
	
	}
	return true;
}

void CSQLQuery::DeleteCommand()
{
	if(m_pCommand)
	{
		delete m_pCommand;
	}
	m_pCommand = NULL;
}
