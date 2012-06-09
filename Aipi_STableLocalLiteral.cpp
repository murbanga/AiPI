// Aipi_STableLocalLiteral.cpp: implementation of the CAipi_STableLocalLiteral class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_STableLocalLiteral.h"

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

CAipi_STableLocalLiteral::CAipi_STableLocalLiteral()
{

}

CAipi_STableLocalLiteral::~CAipi_STableLocalLiteral()
{

}

CAipi_STableLocalLiteral* CAipi_STableLocalLiteral::addSymbol(long iform, tstring name, int type, tstring val )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_STableLocalLiteral *pObject = new CAipi_STableLocalLiteral();
    try
	{
		pObject->setSymbolName(name);
		pObject->setSymbolType(type);
		pObject->setSymbolValue(val);
		
		
			
		pMainFrame->gmSTableLocalLiteral.insert(CMainFrame::g_mSTableLocalLiteral::value_type(iform, *pObject));
				
						
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


tstring CAipi_STableLocalLiteral::findIdValue( long id )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableLocalLiteral::iterator iter;
    iter = pMainFrame->gmSTableLocalLiteral.find(id);
	if( iter != pMainFrame->gmSTableLocalLiteral.end())
	{
  		CAipi_STableLocalLiteral lit = (CAipi_STableLocalLiteral)iter->second;
		return lit.getSymbolValue();
	}
	
	return _T("NOT_FOUND");

}

int CAipi_STableLocalLiteral::findIdType( long id )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableLocalLiteral::iterator iter;
    iter = pMainFrame->gmSTableLocalLiteral.find(id);
	if( iter != pMainFrame->gmSTableLocalLiteral.end())
	{
  		CAipi_STableLocalLiteral lit = (CAipi_STableLocalLiteral)iter->second;
		return lit.getSymbolType();
	}
	
	return NOT_FOUND;

}

tstring CAipi_STableLocalLiteral::findIdName( long id )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableLocalLiteral::iterator iter;
    iter = pMainFrame->gmSTableLocalLiteral.find(id);
	if( iter != pMainFrame->gmSTableLocalLiteral.end())
	{
  		CAipi_STableLocalLiteral lit = (CAipi_STableLocalLiteral)iter->second;
		return lit.getSymbolName();
	}
	
	return _T("NOT_FOUND");

}


int CAipi_STableLocalLiteral::findSTableLiteralMembers(long id)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableLocalLiteral::iterator iter;
    iter = pMainFrame->gmSTableLocalLiteral.find(id);
	if( iter != pMainFrame->gmSTableLocalLiteral.end())
	{
		CAipi_STableLocalLiteral lit = (CAipi_STableLocalLiteral)iter->second;
 	
		m_STLLitId = id;
		m_STLLitName = lit.getSymbolName();
		m_STLLitType = lit.getSymbolType();
		m_STLLitValue = lit.getSymbolValue();
		
		return FOUND;
	}
	
return NOT_FOUND;
	
}




void CAipi_STableLocalLiteral::eraseSTableLiteral(long id)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mSTableLocalLiteral::iterator iter;
	
	iter = pMainFrame->gmSTableLocalLiteral.find(id);
	if( iter != pMainFrame->gmSTableLocalLiteral.end())
	{
		pMainFrame->gmSTableLocalLiteral.erase(id);
				
	}

	
}

void CAipi_STableLocalLiteral::editLastSTableLiteralValue(tstring value)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mSTableLocalLiteral::iterator iter;
	if( !pMainFrame->gmSTableLocalLiteral.empty())
	{
		iter = pMainFrame->gmSTableLocalLiteral.end(); 
		
		--iter;
		CAipi_STableLocalLiteral v = (CAipi_STableLocalLiteral)iter->second;
		long id =		iter->first;
		tstring name =	v.getSymbolName();
		int	type =		v.getSymbolType();

			
		
		pMainFrame->gmSTableLocalLiteral.erase(id);
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


void CAipi_STableLocalLiteral::editSTableLiteralValue(long id, tstring value)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mSTableLocalLiteral::iterator iter;
	if( !pMainFrame->gmSTableLocalLiteral.empty())
	{
		int found = findSTableLiteralMembers( id );
		if( found != NOT_FOUND )
		{
			pMainFrame->gmSTableLocalLiteral.erase(id);
			addSymbol(m_STLLitId, m_STLLitName, m_STLLitType, value);
		
			/*
			CString str;
			AfxMessageBox(_T("OLD VALUE"));
			str.Format(m_STLLitValue.data());
			AfxMessageBox(str);
			AfxMessageBox(_T("EDIT VALUE"));
			str.Format(value.data());
			AfxMessageBox(str);
			str.Format(_T("%d" ), m_STLLitType);
			AfxMessageBox(str);
			AfxMessageBox(m_STLLitName.data());
			*/
		}
		
		
	}

}

void CAipi_STableLocalLiteral::clearSTableLiteral()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmSTableLocalLiteral.clear();

}


int CAipi_STableLocalLiteral::sizeSTableLiteral()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmSTableLocalLiteral.size();

}



void CAipi_STableLocalLiteral::printSTableLiteral()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LOCAL IDENTIFIER  -  Type String  *******"));
	
	//Print map container
	for( CMainFrame::g_mSTableLocalLiteral::const_iterator iter = pMainFrame->gmSTableLocalLiteral.begin(); iter!= pMainFrame->gmSTableLocalLiteral.end(); ++iter)
	{
		CString strID =_T("ID_");
		CString strType =_T("TYPE_");
							
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("******* Local Id - TypeString  *******"));

		long id		= iter->first;
		
		CAipi_STableLocalLiteral lit = (CAipi_STableLocalLiteral)iter->second;
 		
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



