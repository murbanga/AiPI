// Aipi_RETE_TypeString.cpp: implementation of the CAipi_RETE_TypeString class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_TypeString.h"

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

CAipi_RETE_TypeString::CAipi_RETE_TypeString()
{

}

CAipi_RETE_TypeString::~CAipi_RETE_TypeString()
{

}

CAipi_RETE_TypeString* CAipi_RETE_TypeString::addTypeString(tstring var, int pm, int c, tstring dat, int wm, int bm, int old_tk  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_TypeString *pObject = new CAipi_RETE_TypeString();
    try
	{
		pObject->setPM(pm);
		pObject->setCond(c);
		pObject->setData(dat);
		pObject->setWM(wm);
		pObject->setBM(bm);
		pObject->setTK(old_tk);
			
		pMainFrame->gmmVar_String.insert(CMainFrame::g_mmVar_String::value_type(var, *pObject));
				
						
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


void CAipi_RETE_TypeString::clearTypeString()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmVar_String.clear();

}



void CAipi_RETE_TypeString::printTypeString()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Variable -  Type String  *******"));
	
	//Print map container
	for( CMainFrame::g_mmVar_String::const_iterator iter = pMainFrame->gmmVar_String.begin(); iter!= pMainFrame->gmmVar_String.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strCond =_T("C");
		
		CString strWM  = _T("W");
		CString strBM  = _T("B");
		CString strTK	= _T("TK");
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Var - TypeString  *******"));
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Variable: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->first.data());
		
		CAipi_RETE_TypeString str = (CAipi_RETE_TypeString)iter->second;
 		
		int pm			= str.getPM();
		int c			= str.getCond();
		tstring	data	= str.getData();
		int wm			= str.getWM();
		int bm			= str.getBM();
		int tk			= str.getTK();

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("PM: "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
	
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Condition: "));
		strCond +=  _itot( c, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);

		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Data: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(data.data());

		
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
