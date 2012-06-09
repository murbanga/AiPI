// Aipi_RETE_NumVars.cpp: implementation of the CAipi_RETE_NumVars class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_NumVars.h"

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

CAipi_RETE_NumVars::CAipi_RETE_NumVars()
{

}

CAipi_RETE_NumVars::~CAipi_RETE_NumVars()
{

}


CAipi_RETE_NumVars* CAipi_RETE_NumVars::addTK_LeftV(int child_tk, tstring assign_var, tstring var, tstring data1, tstring data2, int wm, int bm  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_NumVars *pObject = new CAipi_RETE_NumVars();
    try
	{
		pObject->setAssignVar(assign_var);
		pObject->setVar(var);
		pObject->setData1(data1);
		pObject->setData2(data2);
		pObject->setWM(wm);
		pObject->setBM(bm);
			
		pMainFrame->gmTK_LeftV.insert(CMainFrame::g_mTK_LeftV::value_type(child_tk, *pObject));
				
						
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


CAipi_RETE_NumVars* CAipi_RETE_NumVars::addTK_RightV(int child_tk, tstring assign_var, tstring var, tstring data1, tstring data2, int wm, int bm  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_NumVars *pObject = new CAipi_RETE_NumVars();
    try
	{
		pObject->setAssignVar(assign_var);
		pObject->setVar(var);
		pObject->setData1(data1);
		pObject->setData2(data2);
		pObject->setWM(wm);
		pObject->setBM(bm);
			
		pMainFrame->gmTK_RightV.insert(CMainFrame::g_mTK_RightV::value_type(child_tk, *pObject));
				
						
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


void CAipi_RETE_NumVars::clearTK_LeftV()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmTK_LeftV.clear();

		
}

void CAipi_RETE_NumVars::clearTK_RightV()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmTK_RightV.clear();

		
}

void CAipi_RETE_NumVars::clearNumVarStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmNumVar_BM.clear();
	pMainFrame->gmTK_LeftV.clear();
	pMainFrame->gmTK_RightV.clear();


}



void CAipi_RETE_NumVars::addNumVar_BM(tstring var, int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmNumVar_BM.insert(CMainFrame::g_mNumVar_BM::value_type(var, bm));	
}

void CAipi_RETE_NumVars::clearNumVar_BM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmNumVar_BM.clear();

		
}

int CAipi_RETE_NumVars::findNumVar_BM(tstring var)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNumVar_BM::iterator iter;
    iter = pMainFrame->gmNumVar_BM.find(var);
	if( iter != pMainFrame->gmNumVar_BM.end())
	{
		return iter->second;
		
	}
	
	return NOT_FOUND;

}


void CAipi_RETE_NumVars::printTK_LeftV()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Token  -  Left Variable  *******"));
	
	//Print map container
	for( CMainFrame::g_mTK_LeftV::const_iterator iter = pMainFrame->gmTK_LeftV.begin(); iter!= pMainFrame->gmTK_LeftV.end(); ++iter)
	{
		CString strTK = _T("TK");
		CString strWM = _T("W");
		CString strBM = _T("B");
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  TK - LeftV  *******"));
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Token: "));
		strTK +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);
		
		
		CAipi_RETE_NumVars nvar = (CAipi_RETE_NumVars)iter->second;
 		
		tstring assign_var		= nvar.getAssignVar();
		tstring var				= nvar.getVar();
		tstring data1			= nvar.getData1();
		tstring data2			= nvar.getData2();
		int	wm					= nvar.getWM();
		int bm					= nvar.getBM();
		

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("AssignVar: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(assign_var.data());

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Var: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(var.data());
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Data1: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(data1.data());

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Data2: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(data2.data());
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("WM: "));
		strWM +=  _itot( wm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("BM: "));
		strBM +=  _itot( bm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		
		
			
	}

}


void CAipi_RETE_NumVars::printTK_RightV()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Token  -  Right Variable  *******"));
	
	//Print map container
	for( CMainFrame::g_mTK_RightV::const_iterator iter = pMainFrame->gmTK_RightV.begin(); iter!= pMainFrame->gmTK_RightV.end(); ++iter)
	{
		CString strTK = _T("TK");
		CString strWM = _T("W");
		CString strBM = _T("B");
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  TK - RightV  *******"));
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Token: "));
		strTK +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);
		
		
		CAipi_RETE_NumVars nvar = (CAipi_RETE_NumVars)iter->second;
 		
		tstring assign_var		= nvar.getAssignVar();
		tstring var				= nvar.getVar();
		tstring data1			= nvar.getData1();
		tstring data2			= nvar.getData2();
		int	wm					= nvar.getWM();
		int bm					= nvar.getBM();
		

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("AssignVar: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(assign_var.data());

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Var: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(var.data());
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Data1: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(data1.data());

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Data2: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(data2.data());
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("WM: "));
		strWM +=  _itot( wm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("BM: "));
		strBM +=  _itot( bm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		
		
			
	}

}
	
void CAipi_RETE_NumVars::printNumVar_BM()
{
	TCHAR buffer[16];
	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Numeric Variable - Beta Memory  *******"));
	//Print map container
	for( CMainFrame::g_mNumVar_BM::const_iterator iter = pMainFrame->gmNumVar_BM.begin(); iter!= pMainFrame->gmNumVar_BM.end(); ++iter)
	{
		CString strBM =_T("B");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NumVar - BM  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("NumVar:"));
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->first.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("BM:"));
		strBM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
			
	}

}
