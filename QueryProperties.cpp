// QueryProperties.cpp: implementation of the CQueryProperties class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "QueryProperties.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CQueryProperties, CObject, 0)
IMPLEMENT_SERIAL( CMapQueryProperties, CMapStringToOb, 0)


CQueryProperties::CQueryProperties()
{
	m_LastModified = CTime::GetCurrentTime();
}


CQueryProperties::CQueryProperties( const CQueryProperties &ob )
{
	*this = ob;
}

CQueryProperties &CQueryProperties::operator=( const CQueryProperties &ob )
{
	m_sqlName = ob.m_sqlName;
	m_sqlFile = ob.m_sqlFile;
	m_sqlhItem = ob.m_sqlhItem;
	m_sqlPath = ob.m_sqlPath;
	m_ReturnType = ob.m_ReturnType;

	return *this;
}


CQueryProperties::~CQueryProperties()
{

}


void CQueryProperties::Serialize( CArchive &ar)
{
	CObject::Serialize( ar );
	
	if( ar.IsStoring() )
	{
		//cast HTREEITEM type
		m_sqliItem = (int)m_sqlhItem; 
		
		ar << m_sqlName << m_sqliItem << m_sqlFile << m_sqlPath 
		   << m_ReturnType;
	}
	else
	{
	
		ar >> m_sqlName >> m_sqliItem >> m_sqlFile >> m_sqlPath
		   >> m_ReturnType;

		//cast HTREEITEM type
		m_sqlhItem = (HTREEITEM)m_sqliItem;
	}

	

}




/////////////////////////////////////////////////////////////////////////////////////////
//// CMapFunctionProperties Functions ////
///////////////////////////////////////////////////////////////////////////////////////////


CQueryProperties* CMapQueryProperties::AddQuery( const TCHAR *szName, HTREEITEM item, const TCHAR *szFile, const TCHAR *szPath, int rtype)
{
	
	CQueryProperties *pObject = new CQueryProperties();
    try
	{
		pObject->setName(szName);
		pObject->setItem(item);
		pObject->setFile(szFile);
		pObject->setPath(szPath);
		pObject->setReturnType(rtype);

		CMapQueryProperties *pMap = new CMapQueryProperties;
		SetAt(szName, pObject);
	
				
	}
	catch( CMemoryException* pErr)
	{
		AfxMessageBox(_T("Out of memory!!!"), MB_ICONSTOP | MB_OK);

		if(pObject)
		{
			delete pObject;
			pObject = NULL;
		}
		pErr->Delete();
	}
	
	return pObject;
}




CQueryProperties *CMapQueryProperties::FindbyRef( const TCHAR * szRef )
{
	CObject *pObject = NULL;
	if( Lookup( szRef, pObject ) )
	{
		
		return (CQueryProperties *) pObject;	
	}

return NULL;
}


HTREEITEM CMapQueryProperties::FindItembyRef(const TCHAR *szRef)
{
	CQueryProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getItem();
	}

	return NULL;
}


CString CMapQueryProperties::FindFilebyRef(const TCHAR *szRef)
{
	CQueryProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getFile();
	}

	return _T("NOT_FOUND");
}

CString CMapQueryProperties::FindPathbyRef(const TCHAR *szRef)
{
	CQueryProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getPath();
	}

	return _T("NOT_FOUND");
}


int CMapQueryProperties::FindReturnTypebyRef(const TCHAR *szRef)
{
	CQueryProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getReturnType();
	}

	return NOT_FOUND;
}






void CMapQueryProperties::ClearMap()
{
	CString ref;
	CObject *pNext = NULL;

	POSITION pos = GetStartPosition();

	while( pos != NULL )
	{
		GetNextAssoc( pos, ref, pNext );
		delete pNext;

	}

	RemoveAll();


}


void CMapQueryProperties::PrintMap()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CObject *pNext;
	
	CQueryProperties *pCurrent = NULL;
	POSITION pos;
	TCHAR buffer[8];

	

	if( GetCount() == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("QueryProperties Map is Empty"));	
	}
	else
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*** QUERY PROPERTIES MAP ***"));
		
		pos = GetStartPosition();
		while( pos != NULL )
		{
			CString ref = _T("REF_");
			CString strItem = _T("ITEM_");
			CString strFile = _T("FILE_");
			CString strPath = _T("PATH_");
			CString strRType = _T("RETURN_TYPE");

			GetNextAssoc(pos, ref, pNext);
			pCurrent = (CQueryProperties *) pNext;
			pMainFrame->m_wndOutputTabView.AddMsg1(ref);
			HTREEITEM hItem = pCurrent->getItem();
			int item = (int )hItem;
			strItem +=  _itot( item, buffer, 10 );
			pMainFrame->m_wndOutputTabView.AddMsg1(strItem);
			strFile += (const TCHAR *)pCurrent->getFile();
			pMainFrame->m_wndOutputTabView.AddMsg1(strFile);
			strPath += (const TCHAR *)pCurrent->getPath();
			pMainFrame->m_wndOutputTabView.AddMsg1(strPath);
			int rtype = pCurrent->getReturnType();
			strRType = _itot( rtype, buffer, 10 );
			pMainFrame->m_wndOutputTabView.AddMsg1(strRType);
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("************************"));	
		}

	}
	


}