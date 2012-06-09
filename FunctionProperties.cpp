// FunctionProperties.cpp: implementation of the CFunctionProperties class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "FunctionProperties.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL( CFunctionProperties, CObject, 0)
IMPLEMENT_SERIAL( CMapFunctionProperties, CMapStringToOb, 0)


CFunctionProperties::CFunctionProperties()
{
	m_LastModified = CTime::GetCurrentTime();
}


CFunctionProperties::CFunctionProperties( const CFunctionProperties &ob )
{
	*this = ob;
}

CFunctionProperties &CFunctionProperties::operator=( const CFunctionProperties &ob )
{
	m_funName = ob.m_funName;
	m_funFile = ob.m_funFile;
	m_funhItem = ob.m_funhItem;
	m_funPath = ob.m_funPath;
	m_Language = ob.m_Language;
	m_ReturnType = ob.m_ReturnType;

	return *this;
}


CFunctionProperties::~CFunctionProperties()
{

}


void CFunctionProperties::Serialize( CArchive &ar)
{
	CObject::Serialize( ar );
	
	if( ar.IsStoring() )
	{
		//cast HTREEITEM type
		m_funiItem = (int)m_funhItem; 
		
		ar << m_funName << m_funiItem << m_funFile << m_funPath 
		   << m_Language << m_ReturnType;
	}
	else
	{
	
		ar >> m_funName >> m_funiItem >> m_funFile >> m_funPath
		   >> m_Language >> m_ReturnType;

		//cast HTREEITEM type
		m_funhItem = (HTREEITEM)m_funiItem;
	}

	

}




/////////////////////////////////////////////////////////////////////////////////////////
//// CMapFunctionProperties Functions ////
///////////////////////////////////////////////////////////////////////////////////////////


CFunctionProperties* CMapFunctionProperties::AddFunction( const TCHAR *szName, HTREEITEM item, const TCHAR *szFile, const TCHAR *szPath, int lang, int rtype)
{
	
	CFunctionProperties *pObject = new CFunctionProperties();
    try
	{
		pObject->setName(szName);
		pObject->setItem(item);
		pObject->setFile(szFile);
		pObject->setPath(szPath);
		pObject->setLanguaje(lang);
		pObject->setReturnType(rtype);

		CMapFunctionProperties *pMap = new CMapFunctionProperties;
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




CFunctionProperties *CMapFunctionProperties::FindbyRef( const TCHAR * szRef )
{
	CObject *pObject = NULL;
	if( Lookup( szRef, pObject ) )
	{
		
		return (CFunctionProperties *) pObject;	
	}

return NULL;
}


HTREEITEM CMapFunctionProperties::FindItembyRef(const TCHAR *szRef)
{
	CFunctionProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getItem();
	}

	return NULL;
}


CString CMapFunctionProperties::FindFilebyRef(const TCHAR *szRef)
{
	CFunctionProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getFile();
	}

	return _T("NOT_FOUND");
}

CString CMapFunctionProperties::FindPathbyRef(const TCHAR *szRef)
{
	CFunctionProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getPath();
	}

	return _T("NOT_FOUND");
}

int CMapFunctionProperties::FindLanguagebyRef(const TCHAR *szRef)
{
	CFunctionProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getLanguage();
	}

	return NOT_FOUND;
}

int CMapFunctionProperties::FindReturnTypebyRef(const TCHAR *szRef)
{
	CFunctionProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getReturnType();
	}

	return NOT_FOUND;
}






void CMapFunctionProperties::ClearMap()
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


void CMapFunctionProperties::PrintMap()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CObject *pNext;
	
	CFunctionProperties *pCurrent = NULL;
	POSITION pos;
	TCHAR buffer[8];

	

	if( GetCount() == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("FunctionProperties Map is Empty"));	
	}
	else
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*** FUNCTION PROPERTIES MAP ***"));
		
		pos = GetStartPosition();
		while( pos != NULL )
		{
			CString ref = _T("REF_");
			CString strItem = _T("ITEM_");
			CString strFile = _T("FILE_");
			CString strPath = _T("PATH_");
			CString strLang = _T("LANG");
			CString strRType = _T("RETURN_TYPE");

			GetNextAssoc(pos, ref, pNext);
			pCurrent = (CFunctionProperties *) pNext;
			pMainFrame->m_wndOutputTabView.AddMsg1(ref);
			HTREEITEM hItem = pCurrent->getItem();
			int item = (int )hItem;
			strItem +=  _itot( item, buffer, 10 );
			pMainFrame->m_wndOutputTabView.AddMsg1(strItem);
			strFile += (const TCHAR *)pCurrent->getFile();
			pMainFrame->m_wndOutputTabView.AddMsg1(strFile);
			strPath += (const TCHAR *)pCurrent->getPath();
			pMainFrame->m_wndOutputTabView.AddMsg1(strPath);
			int lang = pCurrent->getLanguage();
			strLang =  _itot( lang, buffer, 10 );
			pMainFrame->m_wndOutputTabView.AddMsg1(strLang);
			int rtype = pCurrent->getReturnType();
			strRType = _itot( rtype, buffer, 10 );
			pMainFrame->m_wndOutputTabView.AddMsg1(strRType);
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("************************"));	
		}

	}
	


}