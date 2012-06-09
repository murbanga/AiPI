// Aipi_RETE_NCCNode.cpp: implementation of the CAipi_RETE_NCCNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_NCCNode.h"

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

CAipi_RETE_NCCNode::CAipi_RETE_NCCNode()
{

}

CAipi_RETE_NCCNode::~CAipi_RETE_NCCNode()
{

}


CAipi_RETE_NCCNode* CAipi_RETE_NCCNode::addNCC(int ncc, int pm, int c1, int c2 )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_NCCNode *pObject = new CAipi_RETE_NCCNode();
    try
	{
		pObject->setPM(pm);
		pObject->setIniCond(c1);
		pObject->setEndCond(c2);
		
		pMainFrame->gmNCCNode.insert(CMainFrame::g_mNCCNode::value_type(ncc, *pObject));
				
		
				
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



void CAipi_RETE_NCCNode::insertNCC(int cini, int cend, int pm)
{
	int ncc = generateNCCKey();
	addNCC(ncc, pm, cini, cend);

	for(int i = cini; i <=cend; ++i)
	{
		addNCC_Cond(ncc, i);
		addCond_NCC(i, ncc);
	}


}


void CAipi_RETE_NCCNode::addNCCN_BM(int ncc, int bm)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmNCCN_BM.insert(CMainFrame::g_mNCCN_BM::value_type(ncc, bm));
	
}

void CAipi_RETE_NCCNode::addNCCPartnerN_BM(int ncc, int bm)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmNCCPartnerN_BM.insert(CMainFrame::g_mNCCPartnerN_BM::value_type(ncc, bm));
	
}

void CAipi_RETE_NCCNode::addNCC_Cond(int ncc, int c)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmNCC_Cond.insert(CMainFrame::g_mmNCC_Cond::value_type(ncc, c));
	
}

void CAipi_RETE_NCCNode::addCond_NCC(int c, int ncc)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmCond_NCC.insert(CMainFrame::g_mmCond_NCC::value_type(c, ncc));
	
}




int CAipi_RETE_NCCNode::bindNCC(int ncc,int p)
{
	
	int f1,f2 = 0;
	tstring Field1,Field2;

	int cond = findInitCond_NCC(ncc);
	int previousCond = cond - 1;
	CAipi_PM pm;
	int np = pm.searchCond(previousCond);
	if( np == p )
	{
		CAipi_RETE_JNode jn;
		int previousJN = jn.searchJNCond1(previousCond);
		f1 = jn.findJNField1(previousJN);
	}
	else
	{
		return NOT_FOUND;
	}

	cond = findEndCond_NCC(ncc);
	int postCond = cond + 1;

	np = pm.searchCond(postCond);
	if( np == p )
	{

		CAipi_RETE_JNode jn;
		int postJN = jn.searchJNCond2(postCond);
		f2 = jn.findJNField2(postJN);
	}
	else
	{
		return NOT_FOUND;
	}
	
	CAipi_LHS lhs;

	if(f1 == AIPI_ID)
	{
		Field1 = lhs.findLHSId(previousCond);
	}
	else if(f1 == AIPI_AT)
	{
		Field1 = lhs.findLHSAttr(previousCond);	
	}
	else if(f1 == AIPI_VL)
	{
		Field1 = lhs.findLHSVal(previousCond);	
	}
	
	
	if(f2 == AIPI_ID)
	{
		Field2 = lhs.findLHSId(postCond); 
	}
	else if(f2 == AIPI_AT)
	{
		Field2 = lhs.findLHSAttr(postCond);	
	}
	else if(f2 == AIPI_VL)
	{
		Field2 = lhs.findLHSVal(postCond);	
	}



			
	if( Field1 == Field2 )
	{
		return 1;
	}	

	
return NOT_FOUND;
}




void CAipi_RETE_NCCNode::addNCCPartnerN_TK(int ncc, int tk)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmNCCPartnerN_TK.insert(CMainFrame::g_mmNCCPartnerN_TK::value_type(ncc, tk));

	
}




int CAipi_RETE_NCCNode::findNCC(int key)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNCCNode::iterator iter;
    iter = pMainFrame->gmNCCNode.find(key);
	if( iter != pMainFrame->gmNCCNode.end())
	{
  		CAipi_RETE_NCCNode ncc = (CAipi_RETE_NCCNode)iter->second;
 		
		m_IniCond	= ncc.getIniCond();
		m_EndCond	= ncc.getEndCond();
		m_PM		= ncc.getPM();
		
		return key;
	}
	
	
	return NOT_FOUND;
	

}



int CAipi_RETE_NCCNode::findNCC_PM(int ncc)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNCCNode::iterator iter;
    iter = pMainFrame->gmNCCNode.find(ncc);
	if( iter != pMainFrame->gmNCCNode.end())
	{
  		CAipi_RETE_NCCNode ncc = (CAipi_RETE_NCCNode)iter->second;
 		
		return ncc.getPM();
		
	}
	
	
	return NOT_FOUND;	
	

}

int CAipi_RETE_NCCNode::findNCC_Cond(int ncc)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmNCC_Cond::iterator iter;
    iter = pMainFrame->gmmNCC_Cond.find(ncc);
	if( iter != pMainFrame->gmmNCC_Cond.end())
	{
  		return iter->second;
 	}
	
	return NOT_FOUND;
	
}


int CAipi_RETE_NCCNode::findCond_NCC(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmCond_NCC::iterator iter;
    iter = pMainFrame->gmmCond_NCC.find(c);
	if( iter != pMainFrame->gmmCond_NCC.end())
	{
  		return iter->second;
 	}
	
	return NOT_FOUND;
	
}


int CAipi_RETE_NCCNode::findInitCond_NCC(int ncc)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNCCNode::iterator iter;
    iter = pMainFrame->gmNCCNode.find(ncc);
	if( iter != pMainFrame->gmNCCNode.end())
	{
  		CAipi_RETE_NCCNode ncc = (CAipi_RETE_NCCNode)iter->second;
 		
		return ncc.getIniCond();
	}
	
	
	return NOT_FOUND;
	
}

int CAipi_RETE_NCCNode::findEndCond_NCC(int ncc)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNCCNode::iterator iter;
    iter = pMainFrame->gmNCCNode.find(ncc);
	if( iter != pMainFrame->gmNCCNode.end())
	{
  		CAipi_RETE_NCCNode ncc = (CAipi_RETE_NCCNode)iter->second;
 		
		return ncc.getEndCond();
	}
	
	
	return NOT_FOUND;
		
	
}



int CAipi_RETE_NCCNode::findNCCN_BM(int ncc)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNCCN_BM::iterator iter;
    iter = pMainFrame->gmNCCN_BM.find(ncc);
	if( iter != pMainFrame->gmNCCN_BM.end())
	{
  		return iter->second;
 	}
	
	return NOT_FOUND;
	
}


int CAipi_RETE_NCCNode::findNCCPartnerN_BM(int ncc)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNCCPartnerN_BM::iterator iter;
    iter = pMainFrame->gmNCCPartnerN_BM.find(ncc);
	if( iter != pMainFrame->gmNCCPartnerN_BM.end())
	{
  		return iter->second;
 	}
	
	return NOT_FOUND;
	
}

int CAipi_RETE_NCCNode::searchNCCPartnerN_TK(int tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmNCCPartnerN_TK::const_iterator iter;
	
	for( iter = pMainFrame->gmmNCCPartnerN_TK.begin(); iter!= pMainFrame->gmmNCCPartnerN_TK.end(); ++iter)
	{
		if( iter->second == tk )
		{
			return iter->first;
		}
	}

return NOT_FOUND;

}



int CAipi_RETE_NCCNode::findNCCPartnerN_TK(int ncc)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmNCCPartnerN_TK::iterator iter;
    iter = pMainFrame->gmmNCCPartnerN_TK.find(ncc);
	if( iter != pMainFrame->gmmNCCPartnerN_TK.end())
	{
		return iter->second;
		
	}
	
	return NOT_FOUND;

}


int CAipi_RETE_NCCNode::editBM_TK(int ncc, int partner )
{
		CAipi_RETE_BM bm;	
		bm.eraseBM(partner);
		
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		CMainFrame::g_mmBM::iterator it_BM;
		pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
		pBM = pMainFrame->gmmBM.equal_range(ncc);

		for(it_BM = pBM.first; it_BM != pBM.second; ++it_BM)
		{
			//int t = it_BM->second;
			//bm.addBM_TK(partner, t);
		
		}

		if( ncc == UNDEFINE )
		{
			//bm.addBM_TK(partner,EMPTY);
			return UNDEFINE;
		}
		

	return partner;
}





int CAipi_RETE_NCCNode::generateNCCKey()
{
	static int nNCC;
	nNCC++;

		
return nNCC;


}


void CAipi_RETE_NCCNode::eraseNCCN_BM(int ncc)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmNCCN_BM.erase(ncc);		
}	


void CAipi_RETE_NCCNode::eraseNCCPartnerN_BM(int ncc)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmNCCPartnerN_BM.erase(ncc);		
}	


void CAipi_RETE_NCCNode::clearNCCStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->gmNCCNode.clear();
	pMainFrame->gmNCCN_BM.clear();
	pMainFrame->gmNCCPartnerN_BM.clear();
	pMainFrame->gmmNCCPartnerN_TK.clear();

	pMainFrame->gmmNCC_Cond.clear();
	pMainFrame->gmmCond_NCC.clear();


}




void CAipi_RETE_NCCNode::printNCCN_BM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Negated Conjuctive Conditions Node - Beta Memory  *******"));
	//Print map container
	for( CMainFrame::g_mNCCN_BM::const_iterator iter = pMainFrame->gmNCCN_BM.begin(); iter!= pMainFrame->gmNCCN_BM.end(); ++iter)
	{
		CString strNCC =_T("NCC_N");
		CString strBM =_T("B");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NCCNode - BM  *******"));
		strNCC +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNCC);
		strBM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
			
	}


}

void CAipi_RETE_NCCNode::printNCCPartnerN_BM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Negated Conjuctive Conditions Partner - Beta Memory  *******"));
	//Print map container
	for( CMainFrame::g_mNCCPartnerN_BM::const_iterator iter = pMainFrame->gmNCCPartnerN_BM.begin(); iter!= pMainFrame->gmNCCPartnerN_BM.end(); ++iter)
	{
		CString strNCC =_T("NCC_P");
		CString strBM =_T("B");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NCCPartner - BM  *******"));
		strNCC +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNCC);
		strBM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
			
	}


}



void CAipi_RETE_NCCNode::printNCC_Cond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Negated Conjuctive Conditions  - Condition  *******"));
	//Print map container
	for( CMainFrame::g_mmNCC_Cond::const_iterator iter = pMainFrame->gmmNCC_Cond.begin(); iter!= pMainFrame->gmmNCC_Cond.end(); ++iter)
	{
		CString strNCC =_T("NCC");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NCC - Cond  *******"));
		strNCC +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNCC);
		strCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
			
	}


}


void CAipi_RETE_NCCNode::printCond_NCC()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Condition - Negated Conjuctive Conditions  *******"));
	//Print map container
	for( CMainFrame::g_mmCond_NCC::const_iterator iter = pMainFrame->gmmCond_NCC.begin(); iter!= pMainFrame->gmmCond_NCC.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strNCC =_T("NCC");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Cond - NCC  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		strNCC +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNCC);
			
	}


}






void CAipi_RETE_NCCNode::printNCCPartnerN_TK()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NOT Node - Token  *******"));
	//Print map container
	for( CMainFrame::g_mmNCCPartnerN_TK::const_iterator iter = pMainFrame->gmmNCCPartnerN_TK.begin(); iter!= pMainFrame->gmmNCCPartnerN_TK.end(); ++iter)
	{
		
		CString strNCC =_T("NCC");
		CString strTK =_T("T");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NCC Node - Token  *******"));
		strNCC +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNCC);
		strTK +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);
			
	}


}





void CAipi_RETE_NCCNode::printLinkNCCPartnerN_TK()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	CAipi_RETE_TK tk;

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Negated Conjuctive Conditions Tokens  *******"));
	//Print map container
	for( CMainFrame::g_mmNCCPartnerN_TK::const_iterator iter = pMainFrame->gmmNCCPartnerN_TK.begin(); iter!= pMainFrame->gmmNCCPartnerN_TK.end(); ++iter)
	{
		CString strNCC =_T("NCC");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NCC Partner TKE  *******"));
		strNCC +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNCC);
		tstring w = tk.linkWMEs(iter->second);	
		pMainFrame->m_wndOutputTabView.AddMsg1(w.data());
			
	}

}


void CAipi_RETE_NCCNode::printNCC()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Negative Conjuctive Conditions Information  *******"));
	
	//Print map container
	for( CMainFrame::g_mNCCNode::const_iterator iter = pMainFrame->gmNCCNode.begin(); iter!= pMainFrame->gmNCCNode.end(); ++iter)
	{
		CString strNCC = _T("NCC");
		CString strPM = _T("P");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NCC Info  *******"));
		strNCC +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNCC);
		CAipi_RETE_NCCNode ncc = (CAipi_RETE_NCCNode)iter->second;
 		int p =  ncc.getPM();
		int c1 = ncc.getIniCond();
		int c2 = ncc.getEndCond();
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Production : "));
		strPM +=  _itot( p, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Initial Condition : "));
		strCond +=  _itot( c1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		
		strCond =_T("C");
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  End Condition : "));
		strCond +=  _itot( c2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
	
			
	}

}

