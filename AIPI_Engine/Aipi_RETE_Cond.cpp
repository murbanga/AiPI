// Aipi_RETE_Cond.cpp: implementation of the CAipi_RETE_Cond class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_Cond.h"

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

CAipi_RETE_Cond::CAipi_RETE_Cond()
{

}

CAipi_RETE_Cond::~CAipi_RETE_Cond()
{

}

CAipi_RETE_Cond* CAipi_RETE_Cond::addCond1(int c1, int jn, int pm, tstring var )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_Cond *pObject = new CAipi_RETE_Cond();
    try
	{
		pObject->setJN(jn);
		pObject->setPM(pm);
		pObject->setVar(var);
				
		pMainFrame->gmmCond1.insert(CMainFrame::g_mmCond1::value_type(c1, *pObject));
			/*
			CString str;
			str.Format(_T("Condition1 Added...%d  " ), c1);
			AfxMessageBox(str);
			*/
						
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


CAipi_RETE_Cond* CAipi_RETE_Cond::addCond2(int c2, int jn, int pm, tstring var )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_Cond *pObject = new CAipi_RETE_Cond();
    try
	{
		pObject->setJN(jn);
		pObject->setPM(pm);
		pObject->setVar(var);
				
		pMainFrame->gmCond2.insert(CMainFrame::g_mCond2::value_type(c2, *pObject));
			/*
			CString str;
			str.Format(_T("Condition2 Added...%d  " ), c2);
			AfxMessageBox(str);
			*/
						
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


void CAipi_RETE_Cond::addPreCondBind(int c1, int c2)
{
	//AfxMessageBox(_T("Add Fact"));
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmPreCondBind.insert(CMainFrame::g_mPreCondBind::value_type(c1, c2));
}



void CAipi_RETE_Cond::editCond1(int c1, int jn, int pm, tstring var)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmCond1::iterator iter;
	
	iter = pMainFrame->gmmCond1.find(c1);
	if( iter != pMainFrame->gmmCond1.end())
	{
		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
		
		co.setJN(jn);
		co.setPM(pm);
		co.setVar(var);

	}		


}






void CAipi_RETE_Cond::editCond2(int c2, int jn, int pm, tstring var)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mCond2::iterator iter;
	
	iter = pMainFrame->gmCond2.find(c2);
	if( iter != pMainFrame->gmCond2.end())
	{
		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
		
		co.setJN(jn);
		co.setPM(pm);
		co.setVar(var);

	}		


}


void CAipi_RETE_Cond::clearCondStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmCond1.clear();
	pMainFrame->gmCond2.clear();
	pMainFrame->gmPreCondBind.clear();
	
}

void CAipi_RETE_Cond::clearPreCondBind()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmPreCondBind.clear();
	
	
}

void CAipi_RETE_Cond::eraseCond1(int c1 )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmCond1::iterator iterJN;
	
	iterJN = pMainFrame->gmmCond1.find(c1);
	if( iterJN != pMainFrame->gmmCond1.end())
	{
		pMainFrame->gmmCond1.erase(c1);
				
	}

	
}

void CAipi_RETE_Cond::eraseCond2(int c2 )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mCond2::iterator iterJN;
	
	iterJN = pMainFrame->gmCond2.find(c2);
	if( iterJN != pMainFrame->gmCond2.end())
	{
		pMainFrame->gmCond2.erase(c2);
				
	}
	
}





void CAipi_RETE_Cond::deleteJNCond1(int jn )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmCond1::iterator iter;
	
	for(iter = pMainFrame->gmmCond1.begin(); iter != pMainFrame->gmmCond1.end(); ++iter)
	{
		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;

		if( co.getJN() == jn)
		{
			pMainFrame->gmmCond1.erase(iter++);
		}
		else
		{
			++iter;
		}
				
	}

	
}

void CAipi_RETE_Cond::deleteJNCond2(int jn )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mCond2::iterator iter;
	
	for(iter = pMainFrame->gmCond2.begin(); iter != pMainFrame->gmCond2.end(); ++iter)
	{
		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
		
		if( co.getJN() == jn)
		{
			pMainFrame->gmCond2.erase(iter++);
		}
		else
		{
			++iter;
		}
				
	}

	
}


int CAipi_RETE_Cond::findCond1JN(int c1 )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmCond1::iterator iter;
    iter = pMainFrame->gmmCond1.find(c1);
	if( iter != pMainFrame->gmmCond1.end())
	{
  		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
 		return co.getJN();
	}
	
	return NOT_FOUND;

}

int CAipi_RETE_Cond::findCond1JN_JN(int c1, int jn2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmCond1::iterator iterC1;
	pair <CMainFrame::g_mmCond1::iterator, CMainFrame::g_mmCond1::iterator>  pC1;
	
	pC1 = pMainFrame->gmmCond1.equal_range(c1);
	
	for(iterC1 = pC1.first; iterC1 != pC1.second; ++iterC1)
	{	
		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iterC1->second;
 		int jn = co.getJN();
		if ( jn == jn2 ) 
		{
			return jn;
		}
	
	}
	
	
return NOT_FOUND;

}



int CAipi_RETE_Cond::findCond2JN(int c2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mCond2::iterator iter;
    iter = pMainFrame->gmCond2.find(c2);
	if( iter != pMainFrame->gmCond2.end())
	{
  		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
 		return co.getJN();
	}
	
	return NOT_FOUND;

}


int CAipi_RETE_Cond::findCond1Members(int c1)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmCond1::iterator iter;
    iter = pMainFrame->gmmCond1.find(c1);
	if( iter != pMainFrame->gmmCond1.end())
	{
  		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
 		
		m_JN = co.getJN();
		m_PM = co.getPM();
		m_Var =	co.getVar();
		
		return c1;
	}
	
	return NOT_FOUND;
}



int CAipi_RETE_Cond::findCond2Members(int c2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mCond2::iterator iter;
    iter = pMainFrame->gmCond2.find(c2);
	if( iter != pMainFrame->gmCond2.end())
	{
  		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
 		
		m_JN = co.getJN();
		m_PM = co.getPM();
		m_Var =	co.getVar();
		
		return c2;
	}
	
	return NOT_FOUND;
}




int CAipi_RETE_Cond::findCond1PM(int c1)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmCond1::iterator iter;
    iter = pMainFrame->gmmCond1.find(c1);
	if( iter != pMainFrame->gmmCond1.end())
	{
  		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
 		
		return co.getPM();
	}
	
	return NOT_FOUND;
}





int CAipi_RETE_Cond::findCond2PM(int c2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mCond2::iterator iter;
    iter = pMainFrame->gmCond2.find(c2);
	if( iter != pMainFrame->gmCond2.end())
	{
  		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
 		return co.getPM();
	}
	
	return NOT_FOUND;

}


tstring CAipi_RETE_Cond::findCond1Var(int c1)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmCond1::iterator iter;
    iter = pMainFrame->gmmCond1.find(c1);
	if( iter != pMainFrame->gmmCond1.end())
	{
  		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
 		
		return co.getVar();
	}
	
	return _T("NOT_FOUND");
}




tstring CAipi_RETE_Cond::findCond2Var(int c2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mCond2::iterator iter;
    iter = pMainFrame->gmCond2.find(c2);
	if( iter != pMainFrame->gmCond2.end())
	{
  		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
 		return co.getVar();
	}
	
	return _T("NOT_FOUND");

}



int CAipi_RETE_Cond::findPreCondBind(int c1)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mPreCondBind::iterator iter;
    iter = pMainFrame->gmPreCondBind.find(c1);
	if( iter != pMainFrame->gmPreCondBind.end())
	{
  		return iter->second;
	}
	
	return NOT_FOUND;
}




int CAipi_RETE_Cond::sizeCond1()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmmCond1.size();

}


int CAipi_RETE_Cond::sizeCond2()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmCond2.size();

}


void CAipi_RETE_Cond::printCond1()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Conditions 1  *******"));
	//Print map container
	for( CMainFrame::g_mmCond1::const_iterator iter = pMainFrame->gmmCond1.begin(); iter!= pMainFrame->gmmCond1.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strJN = _T("JN");
		CString strPM = _T("PM");
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("_______________"));
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Cond1: "));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		

		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
 		
		int jn = co.getJN();
		int pm = co.getPM();
		tstring var = co.getVar(); 
				


		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  JN: "));
		strJN +=  _itot( jn, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strJN);
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  PM: "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Variable: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(var.data());
		
		/*
		AfxMessageBox(_T("COND1"));
		AfxMessageBox(strCond);
		AfxMessageBox(strJN);
		*/	
	}


}

void CAipi_RETE_Cond::printCond2()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Conditions 2  *******"));
	//Print map container
	for( CMainFrame::g_mCond2::const_iterator iter = pMainFrame->gmCond2.begin(); iter!= pMainFrame->gmCond2.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strJN = _T("JN");
		CString strPM = _T("PM");
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("_______________"));
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Cond2: "));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		

		CAipi_RETE_Cond co = (CAipi_RETE_Cond)iter->second;
 		
		int jn = co.getJN();
		int pm = co.getPM();
		tstring var = co.getVar(); 
				


		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  JN: "));
		strJN +=  _itot( jn, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strJN);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  PM: "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Variable: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(var.data());

		/*
		AfxMessageBox(_T("COND2"));
		AfxMessageBox(strCond);
		AfxMessageBox(strJN);
		*/
		
			
	}


}


