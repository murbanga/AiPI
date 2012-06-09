// Aipi_RETE_TypeInt.cpp: implementation of the CAipi_RETE_TypeInt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_TypeInt.h"

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

CAipi_RETE_TypeInt::CAipi_RETE_TypeInt()
{

}

CAipi_RETE_TypeInt::~CAipi_RETE_TypeInt()
{

}


CAipi_RETE_TypeInt* CAipi_RETE_TypeInt::addTypeInt(tstring var, int pm, int c, int dat, int wm, int bm, int oldtk  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_TypeInt *pObject = new CAipi_RETE_TypeInt();
    try
	{
		pObject->setPM(pm);
		pObject->setCond(c);
		pObject->setData(dat);
		pObject->setWM(wm);
		pObject->setBM(bm);
		pObject->setTK(oldtk);
		
			
		pMainFrame->gmmVar_Int.insert(CMainFrame::g_mmVar_Int::value_type(var, *pObject));
				
						
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

void CAipi_RETE_TypeInt::clearTypeInt()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmVar_Int.clear();

}

void CAipi_RETE_TypeInt::printTypeInt()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Variable - Type Int  *******"));
	
	//Print map container
	for( CMainFrame::g_mmVar_Int::const_iterator iter = pMainFrame->gmmVar_Int.begin(); iter!= pMainFrame->gmmVar_Int.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strCond =_T("C");
		CString strData =_T("DAT_");
		CString strWM = _T("W");
		CString strBM = _T("B");
		CString strTK = _T("TK_");
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Var - TypeInt  *******"));
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Variable: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->first.data());
		
		CAipi_RETE_TypeInt in = (CAipi_RETE_TypeInt)iter->second;
 		
		int pm		= in.getPM();
		int c		= in.getCond();
		int data	= in.getData();
		int wm		= in.getWM();
		int bm		= in.getBM();
		int tk		= in.getTK();
		

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("PM: "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
	
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Condition: "));
		strCond +=  _itot( c, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);

		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Data: "));
		strData.Format(_T("%d" ), data);
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