// Aipi_RETE_Node.cpp: implementation of the CAipi_RETE_Node class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_Node.h"

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

CAipi_RETE_Node::CAipi_RETE_Node()
{

}

CAipi_RETE_Node::~CAipi_RETE_Node()
{

}

CAipi_RETE_Node* CAipi_RETE_Node::addNode(int node, int type, int bm1, int bm2, int am )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_Node *pObject = new CAipi_RETE_Node();
    try
	{
		pObject->setType(type);
		pObject->setParent(bm1);
		pObject->setChild(bm2);
		pObject->setAM(am);
		
		
		pMainFrame->gmNode.insert(CMainFrame::g_mNode::value_type(node, *pObject));
				
				
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


void CAipi_RETE_Node::clearNode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmNode.clear();

}



int CAipi_RETE_Node::findNodeMembers(int node)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNode::iterator iter;
    iter = pMainFrame->gmNode.find(node);
	if( iter != pMainFrame->gmNode.end())
	{
  		CAipi_RETE_Node nodo = (CAipi_RETE_Node)iter->second;
 		
		m_Type = nodo.getType();
		m_Parent = nodo.getParent();
		m_Child = nodo.getChild();
		m_AM = nodo.getAM();

		return node;
	}
	
	return NOT_FOUND;
}


int CAipi_RETE_Node::findNodeType(int node)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNode::iterator iter;
    iter = pMainFrame->gmNode.find(node);
	if( iter != pMainFrame->gmNode.end())
	{
  		CAipi_RETE_Node type = (CAipi_RETE_Node)iter->second;
 		return type.getType();
	}
	
	return NOT_FOUND;

}


int CAipi_RETE_Node::findNodeBM1(int node)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNode::iterator iter;
    iter = pMainFrame->gmNode.find(node);
	if( iter != pMainFrame->gmNode.end())
	{
  		CAipi_RETE_Node bm1 = (CAipi_RETE_Node)iter->second;
 		return bm1.getParent();
	}
	
	return NOT_FOUND;

}


int CAipi_RETE_Node::findNodeBM2(int node)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNode::iterator iter;
    iter = pMainFrame->gmNode.find(node);
	if( iter != pMainFrame->gmNode.end())
	{
  		CAipi_RETE_Node bm2 = (CAipi_RETE_Node)iter->second;
 		return bm2.getChild();
	}
	
	return NOT_FOUND;

}

int CAipi_RETE_Node::findNodeAM(int node)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNode::iterator iter;
    iter = pMainFrame->gmNode.find(node);
	if( iter != pMainFrame->gmNode.end())
	{
  		CAipi_RETE_Node am = (CAipi_RETE_Node)iter->second;
 		return am.getAM();
	}
	
	return NOT_FOUND;

}

int CAipi_RETE_Node::sizeNode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmNode.size();

}


void CAipi_RETE_Node::printNode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Node  *******"));
	
	//Print map container
	for( CMainFrame::g_mNode::const_iterator iter = pMainFrame->gmNode.begin(); iter!= pMainFrame->gmNode.end(); ++iter)
	{
		CString strN =_T("N");
		CString strBM =_T("B");
		CString strType =_T("TYPE_");
		CString strAM =_T("A");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ___Node Element___  *******"));
		strN +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strN);
		
		CAipi_RETE_Node node = (CAipi_RETE_Node)iter->second;
 		int type = node.getType();
		int bm1 = node.getParent();
		int bm2 = node.getChild();
		int am = node.getAM();		


		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Node Type: "));
		strType +=  _itot( type, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strType);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Beta Memorie 1: "));
		strBM +=  _itot( bm1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		
		strBM =_T("B");
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Beta Memorie 2: "));
		strBM +=  _itot( bm2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Alpha Memorie: "));
		strAM +=  _itot( am, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
			
	}

}
