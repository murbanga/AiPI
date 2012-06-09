// Aipi_RETE_DNode.cpp: implementation of the CAipi_RETE_DNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_DNode.h"

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

CAipi_RETE_DNode::CAipi_RETE_DNode()
{

}

CAipi_RETE_DNode::~CAipi_RETE_DNode()
{

}

CAipi_RETE_DNode* CAipi_RETE_DNode::addDNode(int c, int pm, int am, int bm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_DNode *pObject = new CAipi_RETE_DNode();
    try
	{
		pObject->setPM(pm);
		pObject->setAM(am);
		pObject->setBM(bm);
				
		pMainFrame->gmDNode.insert(CMainFrame::g_mDNode::value_type(c, *pObject));
				
				
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


void CAipi_RETE_DNode::clearDNode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmDNode.clear();

}




int CAipi_RETE_DNode::findDNodeMembers(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mDNode::iterator iter;
    iter = pMainFrame->gmDNode.find(c);
	if( iter != pMainFrame->gmDNode.end())
	{
  		CAipi_RETE_DNode dno = (CAipi_RETE_DNode)iter->second;
 		
		m_PM = dno.getPM();
		m_AM = dno.getAM();
		m_BM = dno.getBM();
		
		return c;
	}
	
	return NOT_FOUND;
}


int CAipi_RETE_DNode::findDNodePM(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mDNode::iterator iter;
    iter = pMainFrame->gmDNode.find(c);
	if( iter != pMainFrame->gmDNode.end())
	{
  		CAipi_RETE_DNode dno = (CAipi_RETE_DNode)iter->second;
 		return dno.getPM();
	}
	
	return NOT_FOUND;

}


int CAipi_RETE_DNode::findDNodeAM(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mDNode::iterator iter;
    iter = pMainFrame->gmDNode.find(c);
	if( iter != pMainFrame->gmDNode.end())
	{
  		CAipi_RETE_DNode dno = (CAipi_RETE_DNode)iter->second;
 		return dno.getAM();
	}
	
	return NOT_FOUND;

}


int CAipi_RETE_DNode::findDNodeBM(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mDNode::iterator iter;
    iter = pMainFrame->gmDNode.find(c);
	if( iter != pMainFrame->gmDNode.end())
	{
  		CAipi_RETE_DNode dno = (CAipi_RETE_DNode)iter->second;
 		return dno.getBM();
	}
	
	return NOT_FOUND;

}



int CAipi_RETE_DNode::lastCondDNode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mDNode::iterator iterDN;
	iterDN = pMainFrame->gmDNode.end(); 
	--iterDN;
	
	return iterDN->first;	
}

int CAipi_RETE_DNode::lastPMDNode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mDNode::iterator iterDN;
	iterDN = pMainFrame->gmDNode.end(); 
	--iterDN;
	
	CAipi_RETE_DNode dno = (CAipi_RETE_DNode)iterDN->second;

	return dno.getPM();	
}

int CAipi_RETE_DNode::lastBMDNode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mDNode::iterator iterDN;
	iterDN = pMainFrame->gmDNode.end(); 
	--iterDN;
	
	CAipi_RETE_DNode dno = (CAipi_RETE_DNode)iterDN->second;

	return dno.getBM();	
}


void CAipi_RETE_DNode::printDNode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Dummy Node  *******"));
	
	//Print map container
	for( CMainFrame::g_mDNode::const_iterator iter = pMainFrame->gmDNode.begin(); iter!= pMainFrame->gmDNode.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strPM =_T("P");
		CString strBM =_T("B");
		CString strAM =_T("A");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  DNode Element  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Conditon: "));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		
		CAipi_RETE_DNode dno = (CAipi_RETE_DNode)iter->second;
 		int pm	= dno.getPM();
		int am	= dno.getAM();
		int bm	= dno.getBM();
				


		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Production Memory: "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Alpha Memory: "));
		strAM +=  _itot( am, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Beta Memory: "));
		strBM +=  _itot( bm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		
			
	}

}

