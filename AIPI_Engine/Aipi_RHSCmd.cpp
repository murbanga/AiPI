// Aipi_RHSCmd.cpp: implementation of the CAipi_RHSCmd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RHSCmd.h"

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

CAipi_RHSCmd::CAipi_RHSCmd()
{

}

CAipi_RHSCmd::~CAipi_RHSCmd()
{

}


CAipi_RHSCmd* CAipi_RHSCmd::addRHSCmd(int rhs, int cmd, int param_name, int param_type, tstring param_val)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RHSCmd *pObject = new CAipi_RHSCmd();
    try
	{
		pObject->setCmd(cmd);
		pObject->setParamName(param_name);
		pObject->setParamType(param_type);
		pObject->setParamVal(param_val);
			
		pMainFrame->gmmRHSCmd.insert(CMainFrame::g_mmRHSCmd::value_type(rhs, *pObject));
				
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



void CAipi_RHSCmd::eraseRHSCmd(int rhs)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int f = findRHSCmdMembers(rhs);
	
	if( f != NOT_FOUND )
	{
		pMainFrame->gmmRHSCmd.erase(rhs);
	}
}

void CAipi_RHSCmd::clearRHSCmd()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmRHSCmd.clear();
}


int CAipi_RHSCmd::sizeRHSCmd()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmmRHSCmd.size();

}




int CAipi_RHSCmd::findRHSCmd_Cmd( int rhs )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mmRHSCmd::iterator iter;
    iter = pMainFrame->gmmRHSCmd.find(rhs);
	if( iter != pMainFrame->gmmRHSCmd.end())
	{
  		CAipi_RHSCmd id = (CAipi_RHSCmd)iter->second;
 		return id.getCmd(); 
	}
	

return NOT_FOUND;
}


int CAipi_RHSCmd::findRHSCmd_ParamName( int rhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmRHSCmd::iterator iter;
    iter = pMainFrame->gmmRHSCmd.find(rhs);
	if( iter != pMainFrame->gmmRHSCmd.end())
	{
  		CAipi_RHSCmd cmd = (CAipi_RHSCmd)iter->second;
 		return cmd.getParamName(); 
	}

return NOT_FOUND;
			

}




int CAipi_RHSCmd::findRHSCmd_ParamType( int rhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmRHSCmd::iterator iter;
    iter = pMainFrame->gmmRHSCmd.find(rhs);
	if( iter != pMainFrame->gmmRHSCmd.end())
	{
  		CAipi_RHSCmd cmd = (CAipi_RHSCmd)iter->second;
 		return cmd.getParamType();
	}

return NOT_FOUND;

}




tstring CAipi_RHSCmd::findRHSCmd_ParamVal( int rhs )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mmRHSCmd::iterator iter;
    iter = pMainFrame->gmmRHSCmd.find(rhs);
	if( iter != pMainFrame->gmmRHSCmd.end())
	{
  		CAipi_RHSCmd cmd = (CAipi_RHSCmd)iter->second;
 		return cmd.getParamVal(); 
	}
	

return _T("NOT_FOUND");
}


int CAipi_RHSCmd::findRHSCmdMembers(int rhs)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmRHSCmd::iterator iter;
    iter = pMainFrame->gmmRHSCmd.find(rhs);
	if( iter != pMainFrame->gmmRHSCmd.end())
	{
		CAipi_RHSCmd rhso = (CAipi_RHSCmd)iter->second;
 	
		m_Command = rhso.getCmd();
		m_ParamName = rhso.getParamName();
		m_ParamType = rhso.getParamType();
		m_ParamVal = rhso.getParamVal();
				
		return rhs;
	}
	
	return NOT_FOUND;
}



void CAipi_RHSCmd::printRHSCmd()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Right Hand Side Command *******"));
	//Print map container
	for( CMainFrame::g_mmRHSCmd::const_iterator iter = pMainFrame->gmmRHSCmd.begin(); iter!= pMainFrame->gmmRHSCmd.end(); ++iter)
	{
		CString strFact =_T("F");
		strFact +=  _itot( iter->first, buffer, 10 );
		
		CAipi_RHSCmd rhso = (CAipi_RHSCmd)iter->second;
		int cmd				= rhso.getCmd();
		int param_name		= rhso.getParamName();
		int	param_type		= rhso.getParamType();
		tstring param_val	= rhso.getParamVal();
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  RHSCmd  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1(strFact);
		
		CString strPName =_T("Parameter Name:");
		strPName +=  _itot( param_name, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPName);
		CString strPType =_T("Parameter Type:");
		strPType +=  _itot( param_type, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPType);
		CString strPVal =_T("Parameter Value:");
		pMainFrame->m_wndOutputTabView.AddMsg1(strPVal);
		pMainFrame->m_wndOutputTabView.AddMsg1(param_val.data());
		
	
	}

}
