// RuleProperties.cpp: implementation of the CRuleProperties class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "RuleProperties.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CRuleProperties, CObject, 0)
IMPLEMENT_SERIAL( CMapRuleProperties, CMapStringToOb, 0)


CRuleProperties::CRuleProperties()
{
	m_LastModified = CTime::GetCurrentTime();
}


CRuleProperties::CRuleProperties( const CRuleProperties &ob )
{
	*this = ob;
}

CRuleProperties &CRuleProperties::operator=( const CRuleProperties &ob )
{
	m_rulName = ob.m_rulName;
	m_rulFile = ob.m_rulFile;
	m_rulhItem = ob.m_rulhItem;
	m_rulPath = ob.m_rulPath;
	m_Weight = ob.m_Weight;
	m_CertainFactor = ob.m_CertainFactor;

	return *this;
}


CRuleProperties::~CRuleProperties()
{

}


void CRuleProperties::Serialize( CArchive &ar)
{
	CObject::Serialize( ar );
	
	if( ar.IsStoring() )
	{
		//cast HTREEITEM type
		m_ruliItem = (int)m_rulhItem; 
		
		ar << m_rulName << m_ruliItem << m_rulFile << m_rulPath 
		   << m_Weight << m_CertainFactor;
	}
	else
	{
	
		ar >> m_rulName >> m_ruliItem >> m_rulFile >> m_rulPath
		   >> m_Weight >> m_CertainFactor;

		//cast HTREEITEM type
		m_rulhItem = (HTREEITEM)m_ruliItem;
	}

	

}




/////////////////////////////////////////////////////////////////////////////////////////
//// CMapFunctionProperties Functions ////
///////////////////////////////////////////////////////////////////////////////////////////


CRuleProperties* CMapRuleProperties::AddRule( const TCHAR *szName, HTREEITEM item, const TCHAR *szFile, const TCHAR *szPath, float w, float cf)
{
	
	CRuleProperties *pObject = new CRuleProperties();
    try
	{
		pObject->setName(szName);
		pObject->setItem(item);
		pObject->setFile(szFile);
		pObject->setPath(szPath);
		pObject->setWeight(w);
		pObject->setCertainFactor(cf);

		CMapRuleProperties *pMap = new CMapRuleProperties;
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




CRuleProperties *CMapRuleProperties::FindbyRef( const TCHAR * szRef )
{
	CObject *pObject = NULL;
	if( Lookup( szRef, pObject ) )
	{
		
		return (CRuleProperties *) pObject;	
	}

return NULL;
}


HTREEITEM CMapRuleProperties::FindItembyRef(const TCHAR *szRef)
{
	CRuleProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getItem();
	}

	return NULL;
}


CString CMapRuleProperties::FindFilebyRef(const TCHAR *szRef)
{
	CRuleProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getFile();
	}

	return _T("NOT_FOUND");
}

CString CMapRuleProperties::FindPathbyRef(const TCHAR *szRef)
{
	CRuleProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getPath();
	}

	return _T("NOT_FOUND");
}

float CMapRuleProperties::FindWeightbyRef(const TCHAR *szRef)
{
	CRuleProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getWeight();
	}

	return NOT_FOUND;
}

float CMapRuleProperties::FindCertainFactorbyRef(const TCHAR *szRef)
{
	CRuleProperties *pObject;
		
	if( ( pObject = FindbyRef(szRef)) != NULL )
	{
		return pObject->getCertainFactor();
	}

	return NOT_FOUND;
}






void CMapRuleProperties::ClearMap()
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


void CMapRuleProperties::PrintMap()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CObject *pNext;
	
	CRuleProperties *pCurrent = NULL;
	POSITION pos;
	TCHAR buffer[8];

	

	if( GetCount() == 0 )
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("RuleProperties Map is Empty"));	
	}
	else
	{
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*** RULE PROPERTIES MAP ***"));
		
		pos = GetStartPosition();
		while( pos != NULL )
		{
			CString ref = _T("REF_");
			CString strItem = _T("ITEM_");
			CString strFile = _T("FILE_");
			CString strPath = _T("PATH_");
			CString strW = _T("W_");
			CString strCF = _T("CF_");

			GetNextAssoc(pos, ref, pNext);
			pCurrent = (CRuleProperties *) pNext;
			pMainFrame->m_wndOutputTabView.AddMsg1(ref);
			HTREEITEM hItem = pCurrent->getItem();
			int item = (int )hItem;
			strItem +=  _itot( item, buffer, 10 );
			pMainFrame->m_wndOutputTabView.AddMsg1(strItem);
			strFile += (const TCHAR *)pCurrent->getFile();
			pMainFrame->m_wndOutputTabView.AddMsg1(strFile);
			strPath += (const TCHAR *)pCurrent->getPath();
			pMainFrame->m_wndOutputTabView.AddMsg1(strPath);
			float w = pCurrent->getWeight();
			strW.Format(_T("Weight... %f"), w);
			pMainFrame->m_wndOutputTabView.AddMsg1(strW);
			float cf = pCurrent->getCertainFactor();
			strCF.Format(_T("CertainFactor... %f"), cf);
			pMainFrame->m_wndOutputTabView.AddMsg1(strCF);
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("************************"));	
		}

	}
	


}
