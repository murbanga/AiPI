// Aipi_ScriptLocation.cpp: implementation of the CAipi_ScriptLocation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_ScriptLocation.h"

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

CAipi_ScriptLocation::CAipi_ScriptLocation()
{

}

CAipi_ScriptLocation::~CAipi_ScriptLocation()
{

}



CAipi_ScriptLocation* CAipi_ScriptLocation::addScriptLocation(long pm, long index1, long index2, long pos1, long pos2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_ScriptLocation *pObject = new CAipi_ScriptLocation();
    try
	{
		pObject->setStartIndex(index1);
		pObject->setEndIndex(index2);
		pObject->setStartPos(pos1);
		pObject->setEndPos(pos2);
					
		pMainFrame->gmmScriptLocation.insert(CMainFrame::g_mmScriptLocation::value_type(pm, *pObject));
				
						
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


void CAipi_ScriptLocation::eraseScriptLocation(long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmScriptLocation::iterator iter;
	
	iter = pMainFrame->gmmScriptLocation.find(pm);
	if( iter != pMainFrame->gmmScriptLocation.end())
	{
		pMainFrame->gmmScriptLocation.erase(pm);
				
	}

	
}


void CAipi_ScriptLocation::clearScriptLocation()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmScriptLocation.clear();

}


void CAipi_ScriptLocation::printScriptLocation()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  SCRIPT PM  -  Script Location  *******"));
	
	//Print map container
	for( CMainFrame::g_mmScriptLocation::const_iterator iter = pMainFrame->gmmScriptLocation.begin(); iter!= pMainFrame->gmmScriptLocation.end(); ++iter)
	{
		CString strPM =_T("PM");
		CString strIndex1 =_T("");
		CString strIndex2 =_T("");
		CString strPos1 =_T("");
		CString strPos2 =_T("");
				
					
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ScriptPM - Location  *******"));

		long pm		= iter->first;
		
		CAipi_ScriptLocation sl = (CAipi_ScriptLocation)iter->second;
 		
		long	index1			= sl.getStartIndex();
		long	index2			= sl.getEndIndex();
		long	pos1			= sl.getStartPos();
		long	pos2			= sl.getEndPos();
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Production: "));
		strPM.Format(_T("%d" ), pm);
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Index1: "));
		strIndex1 +=  _itot( index1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strIndex1);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Index2: "));
		strIndex2 +=  _itot( index2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strIndex2);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Pos1: "));
		strPos1 +=  _itot( pos1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPos1);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Pos2: "));
		strPos2 +=  _itot( pos2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPos2);


			
	}

}


