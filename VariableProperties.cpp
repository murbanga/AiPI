// VariableProperties.cpp: implementation of the CVariableProperties class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "VariableProperties.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CVariableProperties, CObject, 0)
IMPLEMENT_SERIAL( CMapVariableProperties, CMapStringToOb, 0)


CVariableProperties::CVariableProperties()
{
	m_LastModified = CTime::GetCurrentTime();
}


CVariableProperties::CVariableProperties( const CVariableProperties &ob )
{
	*this = ob;
}

CVariableProperties &CVariableProperties::operator=( const CVariableProperties &ob )
{
	m_varName = ob.m_varName;
	m_varFile = ob.m_varFile;
	m_varhItem = ob.m_varhItem;
	m_varPath = ob.m_varPath;
	m_Type = ob.m_Type;

	return *this;
}


CVariableProperties::~CVariableProperties()
{

}


void CVariableProperties::Serialize( CArchive &ar)
{
	CObject::Serialize( ar );
	
	if( ar.IsStoring() )
	{
		//cast HTREEITEM type
		m_variItem = (int)m_varhItem; 
		
		ar << m_varName << m_variItem << m_varFile << m_varPath 
		   << m_Type;
	}
	else
	{
	
		ar >> m_varName >> m_variItem >> m_varFile >> m_varPath
		   >> m_Type;

		//cast HTREEITEM type
		m_varhItem = (HTREEITEM)m_variItem;
	}

	

}


/////////////////////////////////////////////////////////////////////////////////////////
//// CMapVariableProperties Functions ////
///////////////////////////////////////////////////////////////////////////////////////////


CVariableProperties* CMapVariableProperties::AddVariable( const TCHAR *szName, HTREEITEM item, const TCHAR *szFile, const TCHAR *szPath, int type)
{
	
	CVariableProperties *pObject = new CVariableProperties();
    try
	{
		pObject->setName(szName);
		pObject->setItem(item);
		pObject->setFile(szFile);
		pObject->setPath(szPath);
		pObject->setType(type);

		CMapVariableProperties *pMap = new CMapVariableProperties;
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




CVariableProperties *CMapVariableProperties::FindbyRef( const TCHAR * szRef )
{
	CObject *pObject = NULL;
	if( Lookup( szRef, pObject ) )
	{
		
		return (CVariableProperties *) pObject;	
	}

return NULL;
}


HTREEITEM CMapVariableProperties::FindItembyRef(const TCHAR *szRef)
{
	CVariableProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getItem();
	}

	return NULL;
}


CString CMapVariableProperties::FindFilebyRef(const TCHAR *szRef)
{
	CVariableProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getFile();
	}

	return _T("NOT_FOUND");
}

CString CMapVariableProperties::FindPathbyRef(const TCHAR *szRef)
{
	CVariableProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getPath();
	}

	return _T("NOT_FOUND");
}



int CMapVariableProperties::FindTypebyRef(const TCHAR *szRef)
{
	CVariableProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getType();
	}

	return NOT_FOUND;
}






void CMapVariableProperties::ClearMap()
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


void CMapVariableProperties::PrintMap()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CObject *pNext;
	
	CVariableProperties *pCurrent = NULL;
	POSITION pos;
	TCHAR buffer[8];

	

	if( GetCount() == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("VariableProperties Map is Empty"));	
	}
	else
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*** VARIABLE PROPERTIES MAP ***"));
		
		pos = GetStartPosition();
		while( pos != NULL )
		{
			CString ref = _T("REF_");
			CString strItem = _T("ITEM_");
			CString strFile = _T("FILE_");
			CString strPath = _T("PATH_");
			CString strType = _T("TYPE_");

			GetNextAssoc(pos, ref, pNext);
			pCurrent = (CVariableProperties *) pNext;
			pMainFrame->m_wndOutputTabView.AddMsg1(ref);
			HTREEITEM hItem = pCurrent->getItem();
			int item = (int )hItem;
			strItem +=  _itot( item, buffer, 10 );
			pMainFrame->m_wndOutputTabView.AddMsg1(strItem);
			strFile += (const TCHAR *)pCurrent->getFile();
			pMainFrame->m_wndOutputTabView.AddMsg1(strFile);
			strPath += (const TCHAR *)pCurrent->getPath();
			pMainFrame->m_wndOutputTabView.AddMsg1(strPath);
			int type = pCurrent->getType();
			strType = _itot( type, buffer, 10 );
			pMainFrame->m_wndOutputTabView.AddMsg1(strType);
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("************************"));	
		}

	}
	


}


