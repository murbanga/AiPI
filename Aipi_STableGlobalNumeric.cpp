// Aipi_STableGlobalNumeric.cpp: implementation of the CAipi_STableGlobalNumeric class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_STableGlobalNumeric.h"

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

CAipi_STableGlobalNumeric::CAipi_STableGlobalNumeric()
{

}

CAipi_STableGlobalNumeric::~CAipi_STableGlobalNumeric()
{

}

CAipi_STableGlobalNumeric* CAipi_STableGlobalNumeric::addSymbol(long iform, tstring name, int type, double val )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_STableGlobalNumeric *pObject = new CAipi_STableGlobalNumeric();
    try
	{
		pObject->setSymbolName(name);
		pObject->setSymbolType(type);
		pObject->setSymbolValue(val);
		
		
			
		pMainFrame->gmSTableGlobalNumeric.insert(CMainFrame::g_mSTableGlobalNumeric::value_type(iform, *pObject));
				
						
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


double CAipi_STableGlobalNumeric::findIdValue( long id )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableGlobalNumeric::iterator iter;
    iter = pMainFrame->gmSTableGlobalNumeric.find(id);
	if( iter != pMainFrame->gmSTableGlobalNumeric.end())
	{
  		CAipi_STableGlobalNumeric num = (CAipi_STableGlobalNumeric)iter->second;
		return num.getSymbolValue();
	}
	
	return NOT_FOUND;

}


int CAipi_STableGlobalNumeric::findIdType( long id )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableGlobalNumeric::iterator iter;
    iter = pMainFrame->gmSTableGlobalNumeric.find(id);
	if( iter != pMainFrame->gmSTableGlobalNumeric.end())
	{
  		CAipi_STableGlobalNumeric num = (CAipi_STableGlobalNumeric)iter->second;
		return num.getSymbolType();
	}
	
	return NOT_FOUND;

}

tstring CAipi_STableGlobalNumeric::findIdName( long id )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableGlobalNumeric::iterator iter;
    iter = pMainFrame->gmSTableGlobalNumeric.find(id);
	if( iter != pMainFrame->gmSTableGlobalNumeric.end())
	{
  		CAipi_STableGlobalNumeric num = (CAipi_STableGlobalNumeric)iter->second;
		return num.getSymbolName();
	}
	
	return _T("NOT_FOUND");

}


int CAipi_STableGlobalNumeric::findSTableNumericMembers(long id)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableGlobalNumeric::iterator iter;
    iter = pMainFrame->gmSTableGlobalNumeric.find(id);
	if( iter != pMainFrame->gmSTableGlobalNumeric.end())
	{
		CAipi_STableGlobalNumeric num = (CAipi_STableGlobalNumeric)iter->second;
 	
		m_STGNumId = id;
		m_STGNumName = num.getSymbolName();
		m_STGNumType = num.getSymbolType();
		m_STGNumValue = num.getSymbolValue();
		
		return FOUND;
	}
	
return NOT_FOUND;
	
}


void CAipi_STableGlobalNumeric::eraseSTableNumeric(long id)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mSTableGlobalNumeric::iterator iter;
	
	iter = pMainFrame->gmSTableGlobalNumeric.find(id);
	if( iter != pMainFrame->gmSTableGlobalNumeric.end())
	{
		pMainFrame->gmSTableGlobalNumeric.erase(id);
				
	}

	
}

void CAipi_STableGlobalNumeric::editLastSTableNumericValue(double value)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mSTableGlobalNumeric::iterator iter;
	if( !pMainFrame->gmSTableGlobalNumeric.empty())
	{
		iter = pMainFrame->gmSTableGlobalNumeric.end(); 
		
		--iter;
		CAipi_STableGlobalNumeric v = (CAipi_STableGlobalNumeric)iter->second;
		long id =		iter->first;
		tstring name =	v.getSymbolName();
		int	type =		v.getSymbolType();
		double oldValue = v.getSymbolValue();
			
		
		pMainFrame->gmSTableGlobalNumeric.erase(id);
		addSymbol(id, name, type, value);
		
		/*
		CString str;
		str.Format(_T("OLD VALUE %f" ), oldValue);
		AfxMessageBox(str);
		str.Format(_T("EDIT VALUE %f" ), value);
		AfxMessageBox(str);
		str.Format(_T("%d" ), id);
		AfxMessageBox(str);
		AfxMessageBox(name.data());
		*/
		
		
	}

}


void CAipi_STableGlobalNumeric::editSTableNumericValue(long id, double value)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mSTableGlobalNumeric::iterator iter;
	
	if( !pMainFrame->gmSTableGlobalNumeric.empty())
	{
		
		int found = findSTableNumericMembers( id );
		if( found != NOT_FOUND )
		{
			pMainFrame->gmSTableGlobalNumeric.erase(id);
			addSymbol(m_STGNumId, m_STGNumName, m_STGNumType, value);
		
			/*
			CString str;
			str.Format(_T("OLD VALUE %f" ), m_STGNumValue);
			AfxMessageBox(str);
			str.Format(_T("EDIT VALUE %f" ), value);
			AfxMessageBox(str);
			str.Format(_T("%d" ), m_STGNumId);
			AfxMessageBox(str);
			AfxMessageBox(m_STGNumName.data());
			*/
		}
		
		
	}

}

void CAipi_STableGlobalNumeric::clearSTableNumeric()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmSTableGlobalNumeric.clear();

}



int CAipi_STableGlobalNumeric::sizeSTableNumeric()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmSTableGlobalNumeric.size();

}





void CAipi_STableGlobalNumeric::printSTableNumeric()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GLOBAL IDENTIFIER  -  Type Double  *******"));
	
	//Print map container
	for( CMainFrame::g_mSTableGlobalNumeric::const_iterator iter = pMainFrame->gmSTableGlobalNumeric.begin(); iter!= pMainFrame->gmSTableGlobalNumeric.end(); ++iter)
	{
		CString strID =_T("ID_");
		CString strType =_T("TYPE_");
		CString strValue = _T("VAL");
					
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("******* Global Id - TypeDouble  *******"));

		long id		= iter->first;
		
		CAipi_STableGlobalNumeric num = (CAipi_STableGlobalNumeric)iter->second;
 		
		tstring name			= num.getSymbolName();
		int		type			= num.getSymbolType();
		double	value			= num.getSymbolValue();

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Identifier: "));
		strID.Format(_T("%d" ), id);
		pMainFrame->m_wndOutputTabView.AddMsg1(strID);
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Name: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(name.data());
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Type: "));
		strType +=  _itot( type, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strType);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Value: "));
		strValue.Format(_T("%f" ), value);
		pMainFrame->m_wndOutputTabView.AddMsg1(strValue);
	
			
	}

}

