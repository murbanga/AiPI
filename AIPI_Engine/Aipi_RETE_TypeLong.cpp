// Aipi_RETE_TypeLong.cpp: implementation of the CAipi_RETE_TypeLong class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_TypeLong.h"

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

CAipi_RETE_TypeLong::CAipi_RETE_TypeLong()
{

}

CAipi_RETE_TypeLong::~CAipi_RETE_TypeLong()
{

}


CAipi_RETE_TypeLong* CAipi_RETE_TypeLong::addTypeLong(tstring var, int pm, int c, long dat, int wm, int bm, int old_tk  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_TypeLong *pObject = new CAipi_RETE_TypeLong();
    try
	{
		pObject->setPM(pm);
		pObject->setCond(c);
		pObject->setData(dat);
		pObject->setWM(wm);
		pObject->setBM(bm);
		pObject->setTK(old_tk);
		
			
		pMainFrame->gmmVar_Long.insert(CMainFrame::g_mmVar_Long::value_type(var, *pObject));
				
						
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

void CAipi_RETE_TypeLong::clearTypeLong()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmVar_Long.clear();

}



void CAipi_RETE_TypeLong::printTypeLong()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Variable -  Type Long  *******"));
	
	//Print map container
	for( CMainFrame::g_mmVar_Long::const_iterator iter = pMainFrame->gmmVar_Long.begin(); iter!= pMainFrame->gmmVar_Long.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strCond =_T("C");
		CString strData =_T("DAT_");
		CString strWM  = _T("W");
		CString strBM  = _T("B");
		CString strTK	= _T("TK");
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Var - TypeLong  *******"));
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Variable: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->first.data());
		
		CAipi_RETE_TypeLong lng = (CAipi_RETE_TypeLong)iter->second;
 		
		int pm		= lng.getPM();
		int c		= lng.getCond();
		long data	= lng.getData();
		int wm		= lng.getWM();
		int bm		= lng.getBM();
		int tk		= lng.getTK();

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("PM: "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
	
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Condition: "));
		strCond +=  _itot( c, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);

		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Data: "));
		strData.Format(_T("%l" ), data);
		pMainFrame->m_wndOutputTabView.AddMsg1(strData);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("WM: "));
		strWM.Format(_T("%d" ), data);
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("BM: "));
		strBM.Format(_T("%d" ), bm);
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("TK: "));
		strTK.Format(_T("%d" ), tk);
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);
		
	}

}