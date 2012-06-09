// Aipi_STableLocalNumeric.cpp: implementation of the CAipi_STableLocalNumeric class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_STableLocalNumeric.h"

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

CAipi_STableLocalNumeric::CAipi_STableLocalNumeric()
{

}

CAipi_STableLocalNumeric::~CAipi_STableLocalNumeric()
{

}


CAipi_STableLocalNumeric* CAipi_STableLocalNumeric::addSymbol(long iform, tstring name, int type, double val )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_STableLocalNumeric *pObject = new CAipi_STableLocalNumeric();
    try
	{
		pObject->setSymbolName(name);
		pObject->setSymbolType(type);
		pObject->setSymbolValue(val);
		
		
			
		pMainFrame->gmSTableLocalNumeric.insert(CMainFrame::g_mSTableLocalNumeric::value_type(iform, *pObject));
				
						
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


double CAipi_STableLocalNumeric::findIdValue( long id )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableLocalNumeric::iterator iter;
    iter = pMainFrame->gmSTableLocalNumeric.find(id);
	if( iter != pMainFrame->gmSTableLocalNumeric.end())
	{
  		CAipi_STableLocalNumeric num = (CAipi_STableLocalNumeric)iter->second;
		return num.getSymbolValue();
	}
	
	return NOT_FOUND;

}


int CAipi_STableLocalNumeric::findIdType( long id )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableLocalNumeric::iterator iter;
    iter = pMainFrame->gmSTableLocalNumeric.find(id);
	if( iter != pMainFrame->gmSTableLocalNumeric.end())
	{
  		CAipi_STableLocalNumeric num = (CAipi_STableLocalNumeric)iter->second;
		return num.getSymbolType();
	}
	
	return NOT_FOUND;

}

tstring CAipi_STableLocalNumeric::findIdName( long id )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableLocalNumeric::iterator iter;
    iter = pMainFrame->gmSTableLocalNumeric.find(id);
	if( iter != pMainFrame->gmSTableLocalNumeric.end())
	{
  		CAipi_STableLocalNumeric num = (CAipi_STableLocalNumeric)iter->second;
		return num.getSymbolName();
	}
	
	return _T("NOT_FOUND");

}


int CAipi_STableLocalNumeric::findSTableNumericMembers(long id)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mSTableLocalNumeric::iterator iter;
    iter = pMainFrame->gmSTableLocalNumeric.find(id);
	if( iter != pMainFrame->gmSTableLocalNumeric.end())
	{
		CAipi_STableLocalNumeric num = (CAipi_STableLocalNumeric)iter->second;
 	
		m_STLNumId = id;
		m_STLNumName = num.getSymbolName();
		m_STLNumType = num.getSymbolType();
		m_STLNumValue = num.getSymbolValue();
		
		return FOUND;
	}
	
return NOT_FOUND;
	
}


void CAipi_STableLocalNumeric::eraseSTableNumeric(long id)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mSTableLocalNumeric::iterator iter;
	
	iter = pMainFrame->gmSTableLocalNumeric.find(id);
	if( iter != pMainFrame->gmSTableLocalNumeric.end())
	{
		pMainFrame->gmSTableLocalNumeric.erase(id);
				
	}

	
}

void CAipi_STableLocalNumeric::editLastSTableNumericValue(double value)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mSTableLocalNumeric::iterator iter;
	if( !pMainFrame->gmSTableLocalNumeric.empty())
	{
		iter = pMainFrame->gmSTableLocalNumeric.end(); 
		
		--iter;
		CAipi_STableLocalNumeric v = (CAipi_STableLocalNumeric)iter->second;
		long id =		iter->first;
		tstring name =	v.getSymbolName();
		int	type =		v.getSymbolType();
		double oldValue = v.getSymbolValue();
			
		
		pMainFrame->gmSTableLocalNumeric.erase(id);
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


void CAipi_STableLocalNumeric::editSTableNumericValue(long id, double value)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mSTableLocalNumeric::iterator iter;
	
	if( !pMainFrame->gmSTableLocalNumeric.empty())
	{
		
		int found = findSTableNumericMembers( id );
		if( found != NOT_FOUND )
		{
			pMainFrame->gmSTableLocalNumeric.erase(id);
			addSymbol(m_STLNumId, m_STLNumName, m_STLNumType, value);
		
			/*
			CString str;
			str.Format(_T("OLD VALUE %f" ), m_STLNumValue);
			AfxMessageBox(str);
			str.Format(_T("EDIT VALUE %f" ), value);
			AfxMessageBox(str);
			str.Format(_T("%d" ), m_STLNumId);
			AfxMessageBox(str);
			AfxMessageBox(m_STLNumName.data());
			*/
		}
		
		
	}

}

void CAipi_STableLocalNumeric::clearSTableNumeric()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmSTableLocalNumeric.clear();

}


int CAipi_STableLocalNumeric::sizeSTableNumeric()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmSTableLocalNumeric.size();

}



void CAipi_STableLocalNumeric::printSTableNumeric()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LOCAL IDENTIFIER  -  Type Double  *******"));
	
	//Print map container
	for( CMainFrame::g_mSTableLocalNumeric::const_iterator iter = pMainFrame->gmSTableLocalNumeric.begin(); iter!= pMainFrame->gmSTableLocalNumeric.end(); ++iter)
	{
		CString strID =_T("ID_");
		CString strType =_T("TYPE_");
		CString strValue = _T("VAL");
					
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Local Id - TypeDouble  *******"));

		long id		= iter->first;
		
		CAipi_STableNumeric num = (CAipi_STableLocalNumeric)iter->second;
 		
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


