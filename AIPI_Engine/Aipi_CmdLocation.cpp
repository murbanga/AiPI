// Aipi_CmdLocation.cpp: implementation of the CAipi_CmdLocation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_CmdLocation.h"

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

CAipi_CmdLocation::CAipi_CmdLocation()
{

}

CAipi_CmdLocation::~CAipi_CmdLocation()
{

}


CAipi_CmdLocation* CAipi_CmdLocation::addCmdLocation(long pm, long index1, long index2, long pos1, long pos2, int cmd)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_CmdLocation *pObject = new CAipi_CmdLocation();
    try
	{
		pObject->setStartIndex(index1);
		pObject->setEndIndex(index2);
		pObject->setStartPos(pos1);
		pObject->setEndPos(pos2);
		pObject->setCommand(cmd);
					
		pMainFrame->gmmCmdLocation.insert(CMainFrame::g_mmCmdLocation::value_type(pm, *pObject));
				
						
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


void CAipi_CmdLocation::eraseCmdLocation(long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmCmdLocation::iterator iter;
	
	iter = pMainFrame->gmmCmdLocation.find(pm);
	if( iter != pMainFrame->gmmCmdLocation.end())
	{
		pMainFrame->gmmCmdLocation.erase(pm);
				
	}

	
}


void CAipi_CmdLocation::clearCmdLocation()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmCmdLocation.clear();

}


void CAipi_CmdLocation::printCmdLocation()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  COMMAND RHS PM  -  Command Location  *******"));
	
	//Print map container
	for( CMainFrame::g_mmCmdLocation::const_iterator iter = pMainFrame->gmmCmdLocation.begin(); iter!= pMainFrame->gmmCmdLocation.end(); ++iter)
	{
		CString strPM =_T("PM");
		CString strIndex1 =_T("");
		CString strIndex2 =_T("");
		CString strPos1 =_T("");
		CString strPos2 =_T("");
		CString strCmd =_T("");
				
					
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  CommandPM - Location  *******"));

		long pm		= iter->first;
		
		CAipi_CmdLocation sl = (CAipi_CmdLocation)iter->second;
 		
		long	index1			= sl.getStartIndex();
		long	index2			= sl.getEndIndex();
		long	pos1			= sl.getStartPos();
		long	pos2			= sl.getEndPos();
		int		cmd				= sl.getCommand();
		
		
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

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Command: "));
		strCmd +=  _itot( cmd, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCmd);



			
	}

}



