// Aipi_RETE_BMCond.cpp: implementation of the CAipi_RETE_BMCond class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_BMCond.h"

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

CAipi_RETE_BMCond::CAipi_RETE_BMCond()
{

}

CAipi_RETE_BMCond::~CAipi_RETE_BMCond()
{

}


CAipi_RETE_BMCond* CAipi_RETE_BMCond::addBMCond(int bm, int c1, int c2, tstring var )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_BMCond *pObject = new CAipi_RETE_BMCond();
    try
	{
		pObject->setCond1(c1);
		pObject->setCond2(c2);
		pObject->setVar(var);
						
		pMainFrame->gmmBM_Cond.insert(CMainFrame::g_mmBM_Cond::value_type(bm, *pObject));
		
		/*
		CString str;
		str.Format(_T("NEW BM...%d  " ), bm);
		AfxMessageBox(str);
							
		str.Format(_T("Cond1...%d  " ), c1);
		AfxMessageBox(str);
		str.Format(_T("Cond2...%d  " ), c2);
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



void CAipi_RETE_BMCond::eraseBMCond(int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM_Cond::iterator iterBM;
	
	iterBM = pMainFrame->gmmBM_Cond.find(bm);
	
	if( iterBM != pMainFrame->gmmBM_Cond.end())
	{
		pMainFrame->gmmBM_Cond.erase(bm);
	}
	
}

void CAipi_RETE_BMCond::clearBMCond()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmBM_Cond.clear();

}


int CAipi_RETE_BMCond::countBMCond(int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmBM_Cond::iterator iter;
    return  pMainFrame->gmmBM_Cond.count(bm);

}


void CAipi_RETE_BMCond::printBMCond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Beta Memory  - Conditions *******"));
	//Print map container
	for( CMainFrame::g_mmBM_Cond::const_iterator iter = pMainFrame->gmmBM_Cond.begin(); iter!= pMainFrame->gmmBM_Cond.end(); ++iter)
	{
		CString strCond1 =_T("C");
		CString strCond2 =_T("C");
		CString strBM = _T("B");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  BM - Cond  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  BM: "));
		strBM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		

		CAipi_RETE_BMCond bmo = (CAipi_RETE_BMCond)iter->second;
 		
		tstring var = bmo.getVar();
		int c1 = bmo.getCond1();
		int c2 = bmo.getCond2();
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Variable: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(var.data());

		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Cond1: "));
		strCond1 +=  _itot( c1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond1);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Cond2: "));
		strCond2 +=  _itot( c2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond2);


			
	}


}
