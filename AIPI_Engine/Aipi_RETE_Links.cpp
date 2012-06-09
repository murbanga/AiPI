// Aipi_RETE_Links.cpp: implementation of the CAipi_RETE_Links class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_Links.h"

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

CAipi_RETE_Links::CAipi_RETE_Links()
{

}

CAipi_RETE_Links::~CAipi_RETE_Links()
{

}


CAipi_RETE_Links* CAipi_RETE_Links::addLink(int c1, int c2, int f1, int f2, int pm, tstring var )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_Links *pObject = new CAipi_RETE_Links();
    try
	{
		pObject->setCond2(c2);
		pObject->setField1(f1);
		pObject->setField2(f2);
		pObject->setPM(pm);
		pObject->setVar(var);
				
		pMainFrame->gmmLink.insert(CMainFrame::g_mmLink::value_type(c1, *pObject));
				
						
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

void CAipi_RETE_Links::clearLinks()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmLink.clear();

}



int CAipi_RETE_Links::findCond1_Cond2(int c1, int c2)
{
	/*
	CString str;
	str.Format(_T("Link cond 1...%d  " ), c1);
	AfxMessageBox(str);
	str.Format(_T("Link cond 2...%d  " ), c2);
	AfxMessageBox(str);
	*/
			
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmLink::iterator iter;
	pair <CMainFrame::g_mmLink::iterator, CMainFrame::g_mmLink::iterator>  pIter;
	
	pIter = pMainFrame->gmmLink.equal_range(c1);
	
	for(iter = pIter.first; iter != pIter.second; ++iter)
	{	
		CAipi_RETE_Links lko = (CAipi_RETE_Links)iter->second;
 		int lkc2 = lko.getCond2();
		if ( lkc2 == c2 ) 
		{
			return FOUND;
		}
	
	}
	
	
return NOT_FOUND;

}




int CAipi_RETE_Links::findLinksMembers(int c1)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmLink::iterator iter;
    iter = pMainFrame->gmmLink.find(c1);
	if( iter != pMainFrame->gmmLink.end())
	{
  		CAipi_RETE_Links linko = (CAipi_RETE_Links)iter->second;
 		
		m_Cond2 = linko.getCond2();
		m_Field1 = linko.getField1();
		m_Field2 = linko.getField2();
		m_PM	=	linko.getPM();	
		m_Var =		linko.getVar();
		
		return c1;
	}
	
	return NOT_FOUND;
}


//This function check for repeated conditions are already linked
//return FOUND if the repeated conditions are linked
//return NOT_FOUND if the repeated conditions asre not linked
//rc1 = The repeated condition for condition c1
//rc2 = The repeated condition for condition c2
//c1 = current condition 1
//c2 = current condition 2  
int CAipi_RETE_Links::checkRepLinks(int rc1, int rc2, int c1, int c2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmRepCond::iterator iter1;
	pair <CMainFrame::g_mmRepCond::iterator, CMainFrame::g_mmRepCond::iterator>  pIt1;
	CMainFrame::g_mmRepCond::iterator iter2;
	pair <CMainFrame::g_mmRepCond::iterator, CMainFrame::g_mmRepCond::iterator>  pIt2;

	pIt1 = pMainFrame->gmmRepCond.equal_range(rc1);
	pIt2 = pMainFrame->gmmRepCond.equal_range(rc2);
	
	int search = UNDEFINE;
	
	
	for(iter1 = pIt1.first; iter1 != pIt1.second; ++iter1)
	{
		CAipi_RepCond rco = (CAipi_RepCond)iter1->second;
		int rep_c1 = rco.getRepCond();
		if( rep_c1 <= c1 )
		{
			/*
				CString str;
				str.Format(_T("rep cond 1...%d  " ), rep_c1);
				AfxMessageBox(str);
			*/
			for(iter2 = pIt2.first; iter2 != pIt2.second; ++iter2)
			{
				
				CAipi_RepCond rco = (CAipi_RepCond)iter2->second;
				int rep_c2 = rco.getRepCond();
				if( rep_c2 <= c2 )
				{
					if( rep_c1 == c1 && rep_c2 == c2 && search == NOT_FOUND )
					{
						return NOT_FOUND;
					}
					/*
						CString str;
						str.Format(_T("rep cond 2...%d  " ), rep_c1);
						AfxMessageBox(str);
						*/
					search = findCond1_Cond2(rc1, rep_c2);
					if( search == NOT_FOUND )
					{
						search = findCond1_Cond2(rep_c1, rc2);
						if( search == NOT_FOUND )
						{
							search = findCond1_Cond2(rep_c1, rep_c2);
							if( search == FOUND )
							{
								return search;
							}
						}
						else
						{
							return FOUND;
						}
					}
					else
					{
						return FOUND;
					}
				}
				
			}
		}
					
	}

	
return search;	
}



int CAipi_RETE_Links::countLinks(int c1)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmLink::iterator iter;
    return  pMainFrame->gmmLink.count(c1);

}

int CAipi_RETE_Links::sizeLinks()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmmLink.size();

}



void CAipi_RETE_Links::printCondLink()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Links Conditions Order *******"));
	//Print map container
	for( CMainFrame::g_mmLink::const_iterator iter = pMainFrame->gmmLink.begin(); iter!= pMainFrame->gmmLink.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strField =_T("F");
		CString strPM = _T("PM");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Linked Cond1 - Cond2  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Condition 1: "));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		

		CAipi_RETE_Links lko = (CAipi_RETE_Links)iter->second;
 		
		int f1 = lko.getField1();
		int c2 = lko.getCond2();
		int f2 = lko.getField2();
		int pm = lko.getPM();
		tstring var = lko.getVar(); 
				


		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Field1: "));
		strField +=  _itot( f1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strField);
		
		strCond =_T("C");
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Condition 2: "));
		strCond +=  _itot( c2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);

		strField = _T("F");
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Field2: "));
		strField +=  _itot( f2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strField);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  PM: "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);


		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Variable: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(var.data());
		
		
			
	}


}