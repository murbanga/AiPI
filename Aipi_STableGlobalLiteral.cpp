// Aipi_STableGlobalLiteral.cpp: implementation of the CAipi_STableGlobalLiteral class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_STableGlobalLiteral.h"

#include "../MainFrm.h"
#include "../ChildFrm.h"
#include "../OutputTabView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAipi_STableGlobalLiteral::CAipi_STableGlobalLiteral()
{

}

CAipi_STableGlobalLiteral::~CAipi_STableGlobalLiteral()
{

}


CAipi_STableGlobalLiteral* CAipi_STableGlobalLiteral::addSymbol(long iform, tstring name, int type, tstring val )
{
		
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_STableGlobalLiteral *pObject = new CAipi_STableGlobalLiteral();
    try
	{
		pObject->setSymbolName(name);
		pObject->setSymbolType(type);
		pObject->setSymbolValue(val);
		
		
			
		pMainFrame->gmSTableGlobalLiteral.insert(CMainFrame::g_mSTableGlobalLiteral::value_type(iform, *pObject));
				
						
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


tstring CAipi_STableGlobalLiteral::findIdValue( long id )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableGlobalLiteral::iterator iter;
    iter = pMainFrame->gmSTableGlobalLiteral.find(id);
	if( iter != pMainFrame->gmSTableGlobalLiteral.end())
	{
  		CAipi_STableGlobalLiteral lit = (CAipi_STableGlobalLiteral)iter->second;
		return lit.getSymbolValue();
	}
	
	return _T("NOT_FOUND");

}

int CAipi_STableGlobalLiteral::findIdType( long id )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableGlobalLiteral::iterator iter;
    iter = pMainFrame->gmSTableGlobalLiteral.find(id);
	if( iter != pMainFrame->gmSTableGlobalLiteral.end())
	{
  		CAipi_STableGlobalLiteral lit = (CAipi_STableGlobalLiteral)iter->second;
		return lit.getSymbolType();
	}
	
	return NOT_FOUND;

}

tstring CAipi_STableGlobalLiteral::findIdName( long id )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableGlobalLiteral::iterator iter;
    iter = pMainFrame->gmSTableGlobalLiteral.find(id);
	if( iter != pMainFrame->gmSTableGlobalLiteral.end())
	{
  		CAipi_STableGlobalLiteral lit = (CAipi_STableGlobalLiteral)iter->second;
		return lit.getSymbolName();
	}
	
	return _T("NOT_FOUND");

}


int CAipi_STableGlobalLiteral::findSTableLiteralMembers(long id)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableGlobalLiteral::iterator iter;
    iter = pMainFrame->gmSTableGlobalLiteral.find(id);
	if( iter != pMainFrame->gmSTableGlobalLiteral.end())
	{
		CAipi_STableGlobalLiteral lit = (CAipi_STableGlobalLiteral)iter->second;
 	
		m_STGLitId = id;
		m_STGLitName = lit.getSymbolName();
		m_STGLitType = lit.getSymbolType();
		m_STGLitValue = lit.getSymbolValue();
		
		return FOUND;
	}
	
return NOT_FOUND;
	
}




void CAipi_STableGlobalLiteral::eraseSTableLiteral(long id)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mSTableGlobalLiteral::iterator iter;
	
	iter = pMainFrame->gmSTableGlobalLiteral.find(id);
	if( iter != pMainFrame->gmSTableGlobalLiteral.end())
	{
		pMainFrame->gmSTableGlobalLiteral.erase(id);
				
	}

	
}

void CAipi_STableGlobalLiteral::editLastSTableLiteralValue(tstring value)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mSTableGlobalLiteral::iterator iter;
	if( !pMainFrame->gmSTableGlobalLiteral.empty())
	{
		iter = pMainFrame->gmSTableGlobalLiteral.end(); 
		
		--iter;
		CAipi_STableGlobalLiteral v = (CAipi_STableGlobalLiteral)iter->second;
		long id =		iter->first;
		tstring name =	v.getSymbolName();
		int	type =		v.getSymbolType();

			
		
		pMainFrame->gmSTableGlobalLiteral.erase(id);
		addSymbol(id, name, type, value);
		/*
		CString str;
		str.Format(_T("EDIT VALUE %f" ), value);
		AfxMessageBox(str);
		str.Format(_T("%d" ), id);
		AfxMessageBox(str);
		AfxMessageBox(name.data());
		*/
		
	}

}


void CAipi_STableGlobalLiteral::editSTableLiteralValue(long id, tstring value)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mSTableGlobalLiteral::iterator iter;
	if( !pMainFrame->gmSTableGlobalLiteral.empty())
	{
		int found = findSTableLiteralMembers( id );
		if( found != NOT_FOUND )
		{
			pMainFrame->gmSTableGlobalLiteral.erase(id);
			addSymbol(m_STGLitId, m_STGLitName, m_STGLitType, value);
		
			/*
			CString str;
			AfxMessageBox(_T("OLD VALUE"));
			str.Format(m_STGLitValue.data());
			AfxMessageBox(str);
			AfxMessageBox(_T("EDIT VALUE"));
			str.Format(value.data());
			AfxMessageBox(str);
			str.Format(_T("%d" ), m_STGLitType);
			AfxMessageBox(str);
			AfxMessageBox(m_STGLitName.data());
			*/
		}
		
		
	}

}



int CAipi_STableGlobalLiteral::sizeSTableLiteral()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmSTableGlobalLiteral.size();

}



void CAipi_STableGlobalLiteral::clearSTableLiteral()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmSTableGlobalLiteral.clear();

}





void CAipi_STableGlobalLiteral::printSTableLiteral()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GLOBAL IDENTIFIER  -  Type String  *******"));
	
	//Print map container
	for( CMainFrame::g_mSTableGlobalLiteral::const_iterator iter = pMainFrame->gmSTableGlobalLiteral.begin(); iter!= pMainFrame->gmSTableGlobalLiteral.end(); ++iter)
	{
		CString strID =_T("ID_");
		CString strType =_T("TYPE_");
							
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("******* Global Id - TypeString  *******"));

		long id		= iter->first;
		
		CAipi_STableGlobalLiteral lit = (CAipi_STableGlobalLiteral)iter->second;
 		
		tstring name			= lit.getSymbolName();
		int		type			= lit.getSymbolType();
		tstring	value			= lit.getSymbolValue();

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Identifier: "));
		strID.Format(_T("%d" ), id);
		pMainFrame->m_wndOutputTabView.AddMsg1(strID);
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Name: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(name.data());
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Type: "));
		strType +=  _itot( type, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strType);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Value: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(value.data());
		
		
			
	}

}

