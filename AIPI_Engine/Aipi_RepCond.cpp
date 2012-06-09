// Aipi_RepCond.cpp: implementation of the CAipi_RepCond class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RepCond.h"

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

CAipi_RepCond::CAipi_RepCond()
{

}

CAipi_RepCond::~CAipi_RepCond()
{

}


CAipi_RepCond* CAipi_RepCond::addRepCond(int c1, int pm1, int c2, int pm2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RepCond *pObject = new CAipi_RepCond();
    try
	{
		pObject->setRepCond(c2);
		pObject->setPM1(pm1);
		pObject->setPM2(pm2);
		
		pMainFrame->gmmRepCond.insert(CMainFrame::g_mmRepCond::value_type(c1, *pObject));
		
		
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


CAipi_RepCond* CAipi_RepCond::addRepCondEx(int c1, int pm1, int c2, int pm2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RepCond *pObject = new CAipi_RepCond();
    try
	{
		pObject->setRepCond(c2);
		pObject->setPM1(pm1);
		pObject->setPM2(pm2);
		
		pMainFrame->gmmRepCondEx.insert(CMainFrame::g_mmRepCondEx::value_type(c1, *pObject));
		
		
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


void CAipi_RepCond::saveRepeatedCond(tstring id, tstring attr, tstring val, int c, int pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	for( CMainFrame::g_mLHS::const_iterator it_LHS = pMainFrame->gmLHS.begin(); it_LHS!= pMainFrame->gmLHS.end(); ++it_LHS)
	{
		CAipi_LHS lhso = (CAipi_LHS)it_LHS->second;
		tstring i = lhso.getId();
		tstring a = lhso.getAttr();
		tstring v = lhso.getVal();
		if(i == id && a == attr && v == val)
		{
				if( it_LHS->first < c )
				{
					addRepCond(it_LHS->first, lhso.m_PM, c, pm);
				}
					
		}
	}
	
	
	for( CMainFrame::g_mmRepCond::const_iterator it = pMainFrame->gmmRepCond.begin(); it!= pMainFrame->gmmRepCond.end(); ++it)
	{
		CAipi_RepCond rco = (CAipi_RepCond)it->second;
		int cond = rco.getRepCond();
		pMainFrame->gmmRepCond.erase(cond);
	
	}




}


void CAipi_RepCond::saveRepeatedCondIForm(long id_iform, long attr_iform, long val_iform, int c, int pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	for( CMainFrame::g_mLHS::const_iterator it_LHS = pMainFrame->gmLHS.begin(); it_LHS!= pMainFrame->gmLHS.end(); ++it_LHS)
	{
		CAipi_LHS lhso = (CAipi_LHS)it_LHS->second;
		long i = lhso.getIdIForm();
		long a = lhso.getAttrIForm();
		long v = lhso.getValIForm();
		if(i == id_iform && a == attr_iform && v == val_iform)
		{
				if( it_LHS->first < c )
				{
					addRepCond(it_LHS->first, lhso.m_PM, c, pm);
				}
					
		}
	}
	
	
	for( CMainFrame::g_mmRepCond::const_iterator it = pMainFrame->gmmRepCond.begin(); it!= pMainFrame->gmmRepCond.end(); ++it)
	{
		CAipi_RepCond rco = (CAipi_RepCond)it->second;
		int cond = rco.getRepCond();
		pMainFrame->gmmRepCond.erase(cond);
	
	}


}


void CAipi_RepCond::clearRepCondStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmRepCond.clear();
	pMainFrame->gmmRepCondEx.clear();
	
}



int CAipi_RepCond::checkEqualCond( int c1, int c2 )
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmRepCond::iterator iter;
	pair <CMainFrame::g_mmRepCond::iterator, CMainFrame::g_mmRepCond::iterator>  pIt;

	pIt = pMainFrame->gmmRepCond.equal_range(c1);
	
	for(iter = pIt.first; iter != pIt.second; ++iter)
	{
		CAipi_RepCond rco = (CAipi_RepCond)iter->second;
		int rc2 = rco.getRepCond();

		if( rc2 == c2 )
		{
			return rc2;
		}
	}

return NOT_FOUND;
}


int CAipi_RepCond::checkEqualCondEx( int c1, int c2 )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmRepCondEx::iterator iter;
	pair <CMainFrame::g_mmRepCondEx::iterator, CMainFrame::g_mmRepCondEx::iterator>  pIt;

	pIt = pMainFrame->gmmRepCondEx.equal_range(c1);
	
	for(iter = pIt.first; iter != pIt.second; ++iter)
	{
		CAipi_RepCond rco = (CAipi_RepCond)iter->second;
		int rc2 = rco.getRepCond();

		if( rc2 == c2 )
		{
			return rc2;
		}
	}
	

return NOT_FOUND;
}


//This function finds the lowest PM repeated condition of a condition
//This is posible because the g_mmRepCondEx structure is generated in a
//Ascendent order including the repeated conditions elements of the class
//If the condition is not repeated then returns the same input condition
int CAipi_RepCond::findLowestRepCondEx(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmRepCondEx::iterator iter;

	iter = pMainFrame->gmmRepCondEx.find(c);
	if( iter != pMainFrame->gmmRepCondEx.end())
	{
  		CAipi_RepCond rco = (CAipi_RepCond)iter->second;
 		return rco.getRepCond();
	}
	
return c;
}

//This is the same as findLowestRepCondEx but it saves in members
//all the values of the class elements 
int CAipi_RepCond::findLowestRepCondExMembers(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmRepCondEx::iterator iter;

	iter = pMainFrame->gmmRepCondEx.find(c);
	if( iter != pMainFrame->gmmRepCondEx.end())
	{
  		CAipi_RepCond rco = (CAipi_RepCond)iter->second;
 		m_RepCond = rco.getRepCond();
		m_PM1 = rco.getPM1();
		m_PM2 = rco.getPM2();
		return FOUND;
	}
	
return NOT_FOUND;
}


/*
int CAipi_RepCond::findEqualCond( int c )
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmRepCond::iterator iter;

	iter = pMainFrame->gmmRepCond.find(c);
	if( iter != pMainFrame->gmmRepCond.end())
	{
  		return iter->first;
 		
	}
	
	for( iter = pMainFrame->gmmRepCond.begin(); iter!= pMainFrame->gmmRepCond.end(); ++iter)
	{
		CAipi_RepCond rco = (CAipi_RepCond)iter->second;
		int rc = rco.getRepCond();
		if( rc == c )
		{
			return rc;
		}	
	}

	
return NOT_FOUND; 
}
*/

int CAipi_RepCond::countRepCond(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmRepCond::iterator iter;
    return  pMainFrame->gmmRepCond.count(c);

}

int CAipi_RepCond::countRepCondEx(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmRepCondEx::iterator iter;
    return  pMainFrame->gmmRepCondEx.count(c);

}





//This function saves all combinations of repeated conditions
//So it would be easy to search for a repeated condition
void CAipi_RepCond::createRepCondEx()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmRepCond::iterator iterRCond;
	pair <CMainFrame::g_mmRepCond::iterator, CMainFrame::g_mmRepCond::iterator>  pRCond;
	

	
	for( CMainFrame::g_mmRepCond::const_iterator iter = pMainFrame->gmmRepCond.begin(); iter!= pMainFrame->gmmRepCond.end(); ++iter)
	{
		CAipi_RepCond rc = (CAipi_RepCond)iter->second;
		int currentCond = rc.getRepCond();
		int currentPM = rc.getPM2();
		int c1 = iter->first;
		int pm1 = rc.getPM1();
		
		addRepCondEx(c1, pm1, currentCond, currentPM);

		pRCond = pMainFrame->gmmRepCond.equal_range(c1);
		
		addRepCondEx(currentCond, currentPM, c1, pm1);
	
		for(iterRCond = pRCond.first; iterRCond != pRCond.second; ++iterRCond)
		{	
			CAipi_RepCond rce = (CAipi_RepCond)iterRCond->second;
 			int c2		= rce.getRepCond();
			long pm1	= rce.getPM1();
			long pm2	= rce.getPM2();

			if( c2 == currentCond )
			{
				continue;
			}
			
			addRepCondEx(currentCond, currentPM, c2, pm2);
			
		}
	}
				
	
		

}



void CAipi_RepCond::printRepCond()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Repeated Conditions  *******"));
	
	//Print map container
	for( CMainFrame::g_mmRepCond::const_iterator iter = pMainFrame->gmmRepCond.begin(); iter!= pMainFrame->gmmRepCond.end(); ++iter)
	{
		CString strC1 = _T("C1:... ");
		CString strC2 = _T("C2:... ");
		CString strPM1 =_T("PM1:... ");
		CString strPM2 =_T("PM2:... ");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Rep Conds  *******"));
		strC1 +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strC1);
		
		CAipi_RepCond rc = (CAipi_RepCond)iter->second;
 		int c2 = rc.getRepCond();
		int pm1 = rc.getPM1();
		int pm2 = rc.getPM2();
				
	
		//pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  C2: "));
		strC2 +=  _itot( c2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strC2);

		//pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  PM1: "));
		strPM1 +=  _itot( pm1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM1);
		
		//pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  PM2: "));
		strPM2 +=  _itot( pm2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM2);
		
			
	}

}


void CAipi_RepCond::printRepCondEx()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Repeated Conditions Extended *******"));
	
	//Print map container
	for( CMainFrame::g_mmRepCondEx::const_iterator iter = pMainFrame->gmmRepCondEx.begin(); iter!= pMainFrame->gmmRepCondEx.end(); ++iter)
	{
		CString strC1 = _T("C1:... ");
		CString strC2 = _T("C2:... ");
		CString strPM1 =_T("PM1:... ");
		CString strPM2 =_T("PM2:... ");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Rep Conds Ex *******"));
		strC1 +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strC1);
		
		CAipi_RepCond rc = (CAipi_RepCond)iter->second;
 		int c2 = rc.getRepCond();
		int pm1 = rc.getPM1();
		int pm2 = rc.getPM2();
				
	
		//pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  C2: "));
		strC2 +=  _itot( c2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strC2);

		//pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  PM1: "));
		strPM1 +=  _itot( pm1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM1);
		
		//pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  PM2: "));
		strPM2 +=  _itot( pm2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM2);
		
			
	}

}
