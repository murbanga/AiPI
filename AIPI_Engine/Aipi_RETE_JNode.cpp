// Aipi_RETE_JNode.cpp: implementation of the CAipi_RETE_JNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_JNode.h"

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

CAipi_RETE_JNode::CAipi_RETE_JNode()
{

}

CAipi_RETE_JNode::~CAipi_RETE_JNode()
{

}

int CAipi_RETE_JNode::generateJNKey()
{
	/*
	static int nJN;
	nJN++;
	*/
	++g_currentJNode;
		
return g_currentJNode;
}







void CAipi_RETE_JNode::clearJNStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmJNode.clear();
	pMainFrame->gmmBM_ChildJN.clear();
	pMainFrame->g_vBMChildJN.clear();
	
}



void CAipi_RETE_JNode::eraseJN(int jn )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mJNode::iterator iterJN;
	
	iterJN = pMainFrame->gmJNode.find(jn);
	if( iterJN != pMainFrame->gmJNode.end())
	{
		pMainFrame->gmJNode.erase(jn);
				
	}

	
}








int CAipi_RETE_JNode::countBM_ChildJN(int b)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmBM_ChildJN::iterator iter;
    return  pMainFrame->gmmBM_ChildJN.count(b);

}




CAipi_RETE_JNode* CAipi_RETE_JNode::addJN(int jn, int c1, int f1, int c2, int f2, int pm, tstring var )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_RETE_Cond co;
	CAipi_RETE_NodeCond no;

	CAipi_RETE_JNode *pObject = new CAipi_RETE_JNode();
    try
	{
		pObject->setCond1(c1);
		pObject->setField1(f1);
		pObject->setCond2(c2);
		pObject->setField2(f2);
		pObject->setPM(pm);
		pObject->setVar(var);
		
		
		pMainFrame->gmJNode.insert(CMainFrame::g_mJNode::value_type(jn, *pObject));
				
		co.addCond1(c1, jn, pm, var);
		co.addCond2(c2, jn, pm, var);
		no.addNodeCond( jn, c1, c2, pm); 
		
	
				
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








int CAipi_RETE_JNode::editJN(int jn, int c1, int f1, int c2, int f2, int pm, tstring var)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mJNode::iterator iterJN;
	
	iterJN = pMainFrame->gmJNode.find(jn);
	if( iterJN != pMainFrame->gmJNode.end())
	{
		eraseJN(jn);
		addJN(jn, c1, f1, c2, f2, pm, var);
		return jn;
		
	}		

return NOT_FOUND;

}



int CAipi_RETE_JNode::findJNMembers(int jn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mJNode::iterator iter;
    iter = pMainFrame->gmJNode.find(jn);
	if( iter != pMainFrame->gmJNode.end())
	{
  		CAipi_RETE_JNode jno = (CAipi_RETE_JNode)iter->second;
 		
		m_Cond1 = jno.getCond1();
		m_Cond2 = jno.getCond2();
		m_Field1 = jno.getField1();
		m_Field2 = jno.getField2();
		m_PM = jno.getPM();
		m_Var = jno.getVar();
		

		return jn;
	}
	
	return NOT_FOUND;
}





int CAipi_RETE_JNode::findJNField1(int jn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mJNode::iterator iter;
    iter = pMainFrame->gmJNode.find(jn);
	if( iter != pMainFrame->gmJNode.end())
	{
  		CAipi_RETE_JNode jno = (CAipi_RETE_JNode)iter->second;
 		return jno.getField1();
	}
	else
	{
		return NOT_FOUND;
	}

}

int CAipi_RETE_JNode::findJNField2(int jn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mJNode::iterator iter;
    iter = pMainFrame->gmJNode.find(jn);
	if( iter != pMainFrame->gmJNode.end())
	{
  		CAipi_RETE_JNode jno = (CAipi_RETE_JNode)iter->second;
 		return jno.getField2();
	}
	else
	{
		return NOT_FOUND;
	}

}



int CAipi_RETE_JNode::findJNCond1(int jn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mJNode::iterator iter;
    iter = pMainFrame->gmJNode.find(jn);
	if( iter != pMainFrame->gmJNode.end())
	{
  		CAipi_RETE_JNode jno = (CAipi_RETE_JNode)iter->second;
 		return jno.getCond1();
	}
	else
	{
		return NOT_FOUND;
	}

}


int CAipi_RETE_JNode::findJNCond2(int jn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mJNode::iterator iter;
    iter = pMainFrame->gmJNode.find(jn);
	if( iter != pMainFrame->gmJNode.end())
	{
  		CAipi_RETE_JNode jno = (CAipi_RETE_JNode)iter->second;
 		return jno.getCond2();
	}
	else
	{
		return NOT_FOUND;
	}

}



int CAipi_RETE_JNode::findJNPM(int jn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mJNode::iterator iter;
    iter = pMainFrame->gmJNode.find(jn);
	if( iter != pMainFrame->gmJNode.end())
	{
  		CAipi_RETE_JNode jno = (CAipi_RETE_JNode)iter->second;
 		return jno.getPM();
	}
	else
	{
		return NOT_FOUND;
	}

}


tstring CAipi_RETE_JNode::findJNVar(int jn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mJNode::iterator iter;
    iter = pMainFrame->gmJNode.find(jn);
	if( iter != pMainFrame->gmJNode.end())
	{
  		CAipi_RETE_JNode jno = (CAipi_RETE_JNode)iter->second;
 		return jno.getVar();
	}
	else
	{
		return _T("NOT_FOUND");
	}

}






int CAipi_RETE_JNode::searchJNCond1(int c1)
{
   CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mJNode::const_iterator iter = pMainFrame->gmJNode.begin(); iter!= pMainFrame->gmJNode.end(); ++iter)
	{
		CAipi_RETE_JNode jno = (CAipi_RETE_JNode)iter->second;
		int c = jno.getCond1();
		
		if( c == c1 )
		{
			//pMainFrame->m_wndOutputTabView.AddMsg1(tok.getToken().data());
			return iter->first;
		}
        	
	} 
	

return NOT_FOUND;

}



int CAipi_RETE_JNode::searchJNCond2(int c2)
{
   CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mJNode::const_iterator iter = pMainFrame->gmJNode.begin(); iter!= pMainFrame->gmJNode.end(); ++iter)
	{
		CAipi_RETE_JNode jno = (CAipi_RETE_JNode)iter->second;
		int c = jno.getCond2();
		
		if( c == c2 )
		{
			//pMainFrame->m_wndOutputTabView.AddMsg1(tok.getToken().data());
			return iter->first;
		}
        	
	} 

return NOT_FOUND;

}


int CAipi_RETE_JNode::sizeJNode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmJNode.size();

}

void CAipi_RETE_JNode::fillJN()
{
	
	addJN(1, 0, AIPI_ID, 1, AIPI_VL, 1,  _T("JNode"));
	addJN(2, 1, AIPI_ID, 2, AIPI_VL, 2,  _T("JNode"));
	addJN(3, 2, AIPI_ID, 3, AIPI_VL, 3,  _T("JNode"));
	addJN(4, 3, AIPI_ID, 4, AIPI_VL, 4,  _T("JNode"));
	addJN(5, 4, AIPI_ID, 5, AIPI_VL, 5,  _T("JNode"));
	addJN(6, 5, AIPI_ID, 6, AIPI_VL, 6,  _T("JNode"));
	addJN(7, 6, AIPI_ID, 7, AIPI_VL, 7,  _T("JNode"));
	addJN(8, 7, AIPI_ID, 8, AIPI_VL, 8,  _T("JNode"));
	addJN(9, 8, AIPI_ID, 9, AIPI_VL, 9,  _T("JNode"));

}




void CAipi_RETE_JNode::printJN()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Join Node  *******"));
	
	//Print map container
	for( CMainFrame::g_mJNode::const_iterator iter = pMainFrame->gmJNode.begin(); iter!= pMainFrame->gmJNode.end(); ++iter)
	{
		CString strJN =_T("JN");
		CString strCond =_T("C");
		CString strField =_T("F");
		CString strPM =_T("P");
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  JNE  *******"));
		strJN +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strJN);
		CAipi_RETE_JNode jn = (CAipi_RETE_JNode)iter->second;
 		
		int c1 = jn.getCond1();
		int f1 = jn.getField1();
		int c2 = jn.getCond2();
		int f2 = jn.getField2();
		int pm = jn.getPM();
		tstring var = jn.getVar(); 
		
	
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Condition 1: "));
		strCond +=  _itot( c1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Field1: "));
		strField +=  _itot( f1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strField);
		
		strCond =_T("C");
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Condition 2: "));
		strCond +=  _itot( c2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		
		strField =_T("F");
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Field2: "));
		strField +=  _itot( f2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strField);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Production Memorie: "));
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Variable: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(var.data());

			
	}

}



