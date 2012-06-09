// Aipi_RETE_TypeDouble.cpp: implementation of the CAipi_RETE_TypeDouble class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_TypeDouble.h"

#include "../MainFrm.h"
#include "../ChildFrm.h"
#include "../OutputTabView.h"
#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAipi_RETE_TypeDouble::CAipi_RETE_TypeDouble()
{

}

CAipi_RETE_TypeDouble::~CAipi_RETE_TypeDouble()
{

}


CAipi_RETE_TypeDouble* CAipi_RETE_TypeDouble::addTypeDouble(tstring var, int pm, int c, double dat, int wm, int bm, int old_tk )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_TypeDouble *pObject = new CAipi_RETE_TypeDouble();
    try
	{
		pObject->setPM(pm);
		pObject->setCond(c);
		pObject->setData(dat);
		pObject->setWM(wm);
		pObject->setBM(bm);
		pObject->setTK(old_tk);
		
			
		pMainFrame->gmmVar_Double.insert(CMainFrame::g_mmVar_Double::value_type(var, *pObject));
				
						
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


void CAipi_RETE_TypeDouble::clearTypeDouble()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmVar_Double.clear();

}



void CAipi_RETE_TypeDouble::printTypeDouble()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Variable  -  Type Double  *******"));
	
	//Print map container
	for( CMainFrame::g_mmVar_Double::const_iterator iter = pMainFrame->gmmVar_Double.begin(); iter!= pMainFrame->gmmVar_Double.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strCond =_T("C");
		CString strData =_T("DAT_");
		CString strWM = _T("W");
		CString strBM = _T("B");
		CString strTK = _T("TK");
		

			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Var - TypeDouble  *******"));
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Variable: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->first.data());
		
		CAipi_RETE_TypeDouble dbl = (CAipi_RETE_TypeDouble)iter->second;
 		
		int pm		= dbl.getPM();
		int c		= dbl.getCond();
		double data	= dbl.getData();
		int	wm		= dbl.getWM();
		int bm		= dbl.getBM();
		int tk		= dbl.getTK();		

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("PM: "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Condition: "));
		strCond +=  _itot( c, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Data: "));
		strData.Format(_T("%f" ), data);
		pMainFrame->m_wndOutputTabView.AddMsg1(strData);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("WM: "));
		strWM.Format(_T("%d" ), wm);
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
	
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("BM: "));
		strBM.Format(_T("%d" ), bm);
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("TK: "));
		strTK.Format(_T("%d" ), tk);
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);
		
		
			
	}

}




