// Aipi_RETE_Vars.cpp: implementation of the CAipi_RETE_Vars class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_Vars.h"

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

CAipi_RETE_Vars::CAipi_RETE_Vars()
{

}

CAipi_RETE_Vars::~CAipi_RETE_Vars()
{

}


CAipi_RETE_Vars* CAipi_RETE_Vars::addVar(tstring var, int f, int am, int c, int rel, int pm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_Vars *pObject = new CAipi_RETE_Vars();
    try
	{
		pObject->setAM(am);
		pObject->setCond(c);
		pObject->setRel(rel);
		pObject->setPM(pm);
				
		switch(f)
		{
		case AIPI_ID:
			pMainFrame->gmmVar_I.insert(CMainFrame::g_mmVar_I::value_type(var, *pObject));
			break;
		case AIPI_AT:
			pMainFrame->gmmVar_A.insert(CMainFrame::g_mmVar_A::value_type(var, *pObject));
			break;
		case AIPI_VL:
			pMainFrame->gmmVar_V.insert(CMainFrame::g_mmVar_V::value_type(var, *pObject));
			break;
		default:
			AfxMessageBox(_T("Field type error"));
		}
				
						
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





void CAipi_RETE_Vars::clearVarsStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->gmmVar_I.clear();
	pMainFrame->gmmVar_A.clear();
	pMainFrame->gmmVar_V.clear();
			
}





void CAipi_RETE_Vars::printVar_I()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Variables - Identifier *******"));
	
	//Print map container
	for( CMainFrame::g_mmVar_I::const_iterator iter = pMainFrame->gmmVar_I.begin(); iter!= pMainFrame->gmmVar_I.end(); ++iter)
	{
		CString strVar =_T("VAR: ");
		CString strAM =_T("AM");
		CString strCond =_T("C");
		CString strRel = _T("REL_");
		CString strPM = _T("PM");
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Var - AIPI_ID  *******"));
		strVar +=  iter->first.data();
		pMainFrame->m_wndOutputTabView.AddMsg1(strVar);
		
		CAipi_RETE_Vars varo = (CAipi_RETE_Vars)iter->second;
 		int am = varo.getAM();
		int c = varo.getCond();
		int rel = varo.getRel();
		int pm = varo.getPM();
		
	
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  AM : "));
		strAM +=  _itot( am, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Condition : "));
		strCond +=  _itot( c, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Relational : "));
		strRel +=  _itot( rel, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strRel);


		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  PM : "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);

		
			
	}

}


void CAipi_RETE_Vars::printVar_A()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Variables - Attribute *******"));
	
	//Print map container
	for( CMainFrame::g_mmVar_A::const_iterator iter = pMainFrame->gmmVar_A.begin(); iter!= pMainFrame->gmmVar_A.end(); ++iter)
	{
		CString strVar =_T("VAR: ");
		CString strAM =_T("AM");
		CString strCond =_T("C");
		CString strRel = _T("REL_");
		CString strPM = _T("PM");
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Var - AIPI_AT  *******"));
		strVar +=  iter->first.data();
		pMainFrame->m_wndOutputTabView.AddMsg1(strVar);
		
		CAipi_RETE_Vars varo = (CAipi_RETE_Vars)iter->second;
 		int am = varo.getAM();
		int c = varo.getCond();
		int rel = varo.getRel();
		int pm = varo.getPM();
		

		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  AM : "));
		strAM +=  _itot( am, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Condition : "));
		strCond +=  _itot( c, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Relational : "));
		strRel +=  _itot( rel, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strRel);

		

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  PM : "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);

		
			
	}

}


void CAipi_RETE_Vars::printVar_V()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Variables - Value *******"));
	
	//Print map container
	for( CMainFrame::g_mmVar_V::const_iterator iter = pMainFrame->gmmVar_V.begin(); iter!= pMainFrame->gmmVar_V.end(); ++iter)
	{
		CString strVar =_T("VAR: ");
		CString strAM =_T("AM");
		CString strCond =_T("C");
		CString strRel = _T("REL_");
		CString strPM = _T("PM");
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Var - AIPI_VL  *******"));
		strVar +=  iter->first.data();
		pMainFrame->m_wndOutputTabView.AddMsg1(strVar);
		
		CAipi_RETE_Vars varo = (CAipi_RETE_Vars)iter->second;
 	
		int am = varo.getAM();
		int c = varo.getCond();
		int rel = varo.getRel();
		int pm = varo.getPM();
		

		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  AM : "));
		strAM +=  _itot( am, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Condition : "));
		strCond +=  _itot( c, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);


		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Relational : "));
		strRel +=  _itot( rel, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strRel);


		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  PM : "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);

		
			
	}

}




void CAipi_RETE_Vars::printSetIDVar()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_sIVar::iterator iter;
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  SET - ID Variable  *******"));

	for (iter = pMainFrame->gsIVar.begin(); iter != pMainFrame->gsIVar.end(); ++iter) 
	{
        pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Set-ID Var  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1((*iter).data());
		   	
    }
       
}


void CAipi_RETE_Vars::printSetVALVar()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_sVVar::iterator iter;
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  SET - VAL Variable  *******"));

	for (iter = pMainFrame->gsVVar.begin(); iter != pMainFrame->gsVVar.end(); ++iter) 
	{
        pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Set-VAL Var  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1((*iter).data());
		   	
    }
       
}



