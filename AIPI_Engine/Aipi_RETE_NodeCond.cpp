// Aipi_RETE_NodeCond.cpp: implementation of the CAipi_RETE_NodeCond class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_NodeCond.h"

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

CAipi_RETE_NodeCond::CAipi_RETE_NodeCond()
{

}

CAipi_RETE_NodeCond::~CAipi_RETE_NodeCond()
{

}


CAipi_RETE_NodeCond* CAipi_RETE_NodeCond::addNodeCond(int node, int c1, int c2, int pm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_NodeCond *pObject = new CAipi_RETE_NodeCond();
    try
	{
		pObject->setCond1(c1);
		pObject->setCond2(c2);
		pObject->setPM(pm);
				
		pMainFrame->gmmNodeCond.insert(CMainFrame::g_mmNodeCond::value_type(node, *pObject));
				
				
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


void CAipi_RETE_NodeCond::clearNodeCond()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmNodeCond.clear();

}	


int CAipi_RETE_NodeCond::findNodeCond1_PM(int node, long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmNodeCond::iterator iterNode;
	pair <CMainFrame::g_mmNodeCond::iterator, CMainFrame::g_mmNodeCond::iterator>  pNode;
	
	pNode = pMainFrame->gmmNodeCond.equal_range(node);
	
	for(iterNode = pNode.first; iterNode != pNode.second; ++iterNode)
	{	
		CAipi_RETE_NodeCond no = (CAipi_RETE_NodeCond)iterNode->second;
 		int pm1 = no.getPM();
		if ( pm1 == pm ) 
		{
			return no.getCond1();
		}
	
	}
	
return NOT_FOUND;

}


int CAipi_RETE_NodeCond::findNodeCond2_PM(int node, long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmNodeCond::iterator iterNode;
	pair <CMainFrame::g_mmNodeCond::iterator, CMainFrame::g_mmNodeCond::iterator>  pNode;
	
	pNode = pMainFrame->gmmNodeCond.equal_range(node);
	
	for(iterNode = pNode.first; iterNode != pNode.second; ++iterNode)
	{	
		CAipi_RETE_NodeCond no = (CAipi_RETE_NodeCond)iterNode->second;
 		int pm1 = no.getPM();
		if ( pm1 == pm ) 
		{
			return no.getCond2();
		}
	
	}
	
return NOT_FOUND;

}


int CAipi_RETE_NodeCond::findNodeCond1_Cond2(int node, int c2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmNodeCond::iterator iterNode;
	pair <CMainFrame::g_mmNodeCond::iterator, CMainFrame::g_mmNodeCond::iterator>  pNode;
	
	pNode = pMainFrame->gmmNodeCond.equal_range(node);
	
	for(iterNode = pNode.first; iterNode != pNode.second; ++iterNode)
	{	
		CAipi_RETE_NodeCond no = (CAipi_RETE_NodeCond)iterNode->second;
 		int nc2 = no.getCond2();
		if ( nc2 == c2 ) 
		{
			return no.getCond1();
		}
	
	}
	
return NOT_FOUND;

}



int CAipi_RETE_NodeCond::countNodeCond(int node)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmNodeCond::iterator iter;
    return  pMainFrame->gmmNodeCond.count(node);

}




void CAipi_RETE_NodeCond::printNodeCond()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NodeCond  *******"));
	
	//Print map container
	for( CMainFrame::g_mmNodeCond::const_iterator iter = pMainFrame->gmmNodeCond.begin(); iter!= pMainFrame->gmmNodeCond.end(); ++iter)
	{
		CString strN =_T("N");
		CString strCond =_T("C");
		CString strPM =_T("P");
		CString strAM =_T("A");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ___Node Element___  *******"));
		strN +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strN);
		
		CAipi_RETE_NodeCond node = (CAipi_RETE_NodeCond)iter->second;
 		int c1 = node.getCond1();
		int c2 = node.getCond2();
		int pm = node.getPM();
		

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Cond1: "));
		strCond +=  _itot( c1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		
		strCond = _T("C");
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Cond2: "));
		strCond +=  _itot( c2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Production Memorie: "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);

			
	}

}
