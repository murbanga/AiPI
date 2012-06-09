// Aipi_RETE_TypeFloat.cpp: implementation of the CAipi_RETE_TypeFloat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_TypeFloat.h"

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

CAipi_RETE_TypeFloat::CAipi_RETE_TypeFloat()
{

}

CAipi_RETE_TypeFloat::~CAipi_RETE_TypeFloat()
{

}


CAipi_RETE_TypeFloat* CAipi_RETE_TypeFloat::addTypeFloat(tstring var, int pm, int c, float dat, int wm, int bm, int old_tk  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_TypeFloat *pObject = new CAipi_RETE_TypeFloat();
    try
	{
		pObject->setPM(pm);
		pObject->setCond(c);
		pObject->setData(dat);
		pObject->setWM(wm);
		pObject->setBM(bm);
		pObject->setTK(old_tk);
					
		pMainFrame->gmmVar_Float.insert(CMainFrame::g_mmVar_Float::value_type(var, *pObject));
				
						
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


void CAipi_RETE_TypeFloat::clearTypeFloat()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmVar_Float.clear();

}


void CAipi_RETE_TypeFloat::printTypeFloat()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Variable - Type Float  *******"));
	
	//Print map container
	for( CMainFrame::g_mmVar_Float::const_iterator iter = pMainFrame->gmmVar_Float.begin(); iter!= pMainFrame->gmmVar_Float.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strCond =_T("C");
		CString strData =_T("DAT_");
		CString strWM  = _T("W");
		CString strBM  = _T("B");
		
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Var - TypeFloat  *******"));
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Variable: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->first.data());
		
		CAipi_RETE_TypeFloat flt = (CAipi_RETE_TypeFloat)iter->second;
 		
		int pm		= flt.getPM();
		int c		= flt.getCond();
		float data	= flt.getData();
		int	wm		= flt.getWM();
		int bm		= flt.getBM();
		

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
		
		
		
			
	}

}
