// Aipi_RETE_NNode.cpp: implementation of the CAipi_RETE_NNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_NNode.h"

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

CAipi_RETE_NNode::CAipi_RETE_NNode()
{

}

CAipi_RETE_NNode::~CAipi_RETE_NNode()
{

}


void CAipi_RETE_NNode::insertNN(int c)
{
	addCond_NN(c, UNDEFINE);

}



CAipi_RETE_NNode* CAipi_RETE_NNode::addNN(int ncc, int c1, int f1, int c2, int f2, int bm1, int jn2, int type )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_NNode *pObject = new CAipi_RETE_NNode();
    try
	{
		pObject->setCond1(c1);
		pObject->setField1(f1);
		pObject->setCond2(c2);
		pObject->setField2(f2);
		pObject->setBM1(bm1);
		pObject->setJN2(jn2);
		pObject->setType(type);
		
		
		pMainFrame->gmNNode.insert(CMainFrame::g_mNNode::value_type(ncc, *pObject));
				
						
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




void CAipi_RETE_NNode::addCond_NN(int c, int nn)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmCond_NN.insert(CMainFrame::g_mCond_NN::value_type(c, nn));

	
}


void CAipi_RETE_NNode::addNN_TK(int nn, int tk)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmNN_TK.insert(CMainFrame::g_mmNN_TK::value_type(nn, tk));

	
}


void CAipi_RETE_NNode::addNN_WM(int nn, int wm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmNN_WM.insert(CMainFrame::g_mmNN_WM::value_type(nn, wm));

}



void CAipi_RETE_NNode::addWM_NN(int wm, int nn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmWM_NN.insert(CMainFrame::g_mWM_NN::value_type(wm, nn));

}




void CAipi_RETE_NNode::clearNNStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmNNode.clear();
	pMainFrame->gmmNN_TK.clear();
	pMainFrame->gmCond_NN.clear();
	pMainFrame->gmmNN_WM.clear();
	pMainFrame->gmWM_NN.clear();



}


int CAipi_RETE_NNode::eraseNN_WM(int nn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mmNN_WM::iterator iter;
    iter = pMainFrame->gmmNN_WM.find(nn);
	if( iter != pMainFrame->gmmNN_WM.end())
	{
  		pMainFrame->gmmNN_WM.erase(nn);
		return nn;
	}
	
	
	return NOT_FOUND;

}

int CAipi_RETE_NNode::eraseWM_NN(int wm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mWM_NN::iterator iter;
    iter = pMainFrame->gmWM_NN.find(wm);
	if( iter != pMainFrame->gmWM_NN.end())
	{
  		pMainFrame->gmWM_NN.erase(wm);
		return wm;
	}
	
	
	return NOT_FOUND;

}



int CAipi_RETE_NNode::eraseCond_NN(int nn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mCond_NN::const_iterator iterNN;

			
	for(iterNN = pMainFrame->gmCond_NN.begin(); iterNN != pMainFrame->gmCond_NN.end(); ++iterNN)
	{	
				
		if( iterNN->second == nn )
		{
			pMainFrame->gmCond_NN.erase(nn);
			return iterNN->first;
			
			
		}
		
	}

return NOT_FOUND;
	
}



int CAipi_RETE_NNode::eraseNN_TK(int nn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmNN_TK::iterator iter;
	iter = pMainFrame->gmmNN_TK .find(nn);
	if( iter != pMainFrame->gmmNN_TK.end())
	{
  		pMainFrame->gmmNN_TK.erase(nn);
		return nn;
	}


	return NOT_FOUND;
}


int CAipi_RETE_NNode::eraseItemNN_TK(int nn, int tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmNN_TK::iterator iterNN;
	pair <CMainFrame::g_mmNN_TK::iterator, CMainFrame::g_mmNN_TK::iterator>  pNN;
	pNN = pMainFrame->gmmNN_TK.equal_range(nn);
			
	for(iterNN = pNN.first; iterNN != pNN.second; ++iterNN)
	{	
		
		if( iterNN->second == tk )
		{
			pMainFrame->gmmNN_TK.erase(iterNN);
			return iterNN->first;
			
			
		}
		
	}

return NOT_FOUND;
	
}


void CAipi_RETE_NNode::eraseTK(int nn)
{
	CAipi_RETE_TK tk;
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmNN_TK::iterator iterNN;
	pair <CMainFrame::g_mmNN_TK::iterator, CMainFrame::g_mmNN_TK::iterator>  pNN;
	pNN = pMainFrame->gmmNN_TK.equal_range(nn);
			
	for(iterNN = pNN.first; iterNN != pNN.second; ++iterNN)
	{	
		//tk.findTokenObject(iterNN->second);
		
		int w = tk.findWM(iterNN->second);
		tk.eraseWMChildTokenE(w, iterNN->second);
		
		tk.eraseTK(iterNN->second);
		//tk.eraseTKLinks(iterNN->second);
		
		/*
		
		CString str;
		str.Format(_T("Token to Erase ...%d  " ), iterBM->second);
		AfxMessageBox(str);
		str.Format(_T("Working Memory element ...%d  " ), w);
		AfxMessageBox(str);
		*/
		
		
	}


	
}




int CAipi_RETE_NNode::eraseNN(int nn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mNNode::iterator iter;
	iter = pMainFrame->gmNNode.find(nn);
	if( iter != pMainFrame->gmNNode.end())
	{
  		pMainFrame->gmNNode.erase(nn);
		return nn;
	}


	return NOT_FOUND;

}

/*
int CAipi_RETE_NNode::findTokenNN(int t)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mTokenNN::iterator iter;
    iter = pMainFrame->gmTokenNN.find(t);
	if( iter != pMainFrame->gmTokenNN.end())
	{
  		CAipi_RETE_TK tk = (CAipi_RETE_TK)iter->second;
 		
		m_Token = tk.getToken();
		m_WME	= tk.getWME();	
		m_Sign	= tk.getSign();	
		
		return t;
	}
	
	
	return NOT_FOUND;
}
*/

int CAipi_RETE_NNode::findNNMembers(int nn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNNode::iterator iter;
    iter = pMainFrame->gmNNode.find(nn);
	if( iter != pMainFrame->gmNNode.end())
	{
  		CAipi_RETE_NNode nno = (CAipi_RETE_NNode)iter->second;
 		
		m_Cond1 = nno.getCond1();
		m_Cond2 = nno.getCond2();
		m_Field1 = nno.getField1();
		m_Field2 = nno.getField2();
		m_BM1 = nno.getBM1();
		m_JN2 = nno.getJN2();
		m_Type = nno.getType();

		return nn;
	}
	
	
	return NOT_FOUND;
	

}




int CAipi_RETE_NNode::findCond_NN(int c)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mCond_NN::iterator iter;
    iter = pMainFrame->gmCond_NN.find(c);
	if( iter != pMainFrame->gmCond_NN.end())
	{
		return iter->second;
		
	}
	
	return NOT_FOUND;

}


int CAipi_RETE_NNode::findWM_NN(int wm)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWM_NN::iterator iter;
    iter = pMainFrame->gmWM_NN.find(wm);
	if( iter != pMainFrame->gmWM_NN.end())
	{
		return iter->second;
		
	}
	
	return NOT_FOUND;

}



int CAipi_RETE_NNode::searchNN_TK(int tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmNN_TK::const_iterator iter;
	
	for( iter = pMainFrame->gmmNN_TK.begin(); iter!= pMainFrame->gmmNN_TK.end(); ++iter)
	{
		if( iter->second == tk )
		{
			return iter->first;
		}
	}

return NOT_FOUND;

}



int CAipi_RETE_NNode::findNN_TK(int nn)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmNN_TK::iterator iter;
    iter = pMainFrame->gmmNN_TK.find(nn);
	if( iter != pMainFrame->gmmNN_TK.end())
	{
		return iter->second;
		
	}
	
	return NOT_FOUND;

}


void CAipi_RETE_NNode::editCond_NN(int c, int nn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mCond_NN::iterator iterNN;
	
	iterNN = pMainFrame->gmCond_NN.find(c);
	if( iterNN != pMainFrame->gmCond_NN.end())
	{
		
		iterNN->second = nn; 
	}		


}

int CAipi_RETE_NNode::findField1NN(int nn)
{
   CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNNode::iterator iter;
    iter = pMainFrame->gmNNode.find(nn);
	if( iter != pMainFrame->gmNNode.end())
	{
  		CAipi_RETE_NNode n = (CAipi_RETE_NNode)iter->second;
 		return n.getField1();
	}
	
return NOT_FOUND;
	
}


int CAipi_RETE_NNode::findField2NN(int nn)
{
   CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNNode::iterator iter;
    iter = pMainFrame->gmNNode.find(nn);
	if( iter != pMainFrame->gmNNode.end())
	{
  		CAipi_RETE_NNode n = (CAipi_RETE_NNode)iter->second;
 		return n.getField2();
	}
	
return NOT_FOUND;
	
}



int CAipi_RETE_NNode::generateNNKey()
{
	static int nNN;
	nNN++;

		
return nNN;


}

int CAipi_RETE_NNode::sizeNNode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmNNode.size();

}



void CAipi_RETE_NNode::printCond_NN()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Condition - NOT Node *******"));
	//Print map container
	for( CMainFrame::g_mCond_NN::const_iterator iter = pMainFrame->gmCond_NN.begin(); iter!= pMainFrame->gmCond_NN.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strNOT =_T("NOT");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Cond - NOTNode  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		strNOT +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNOT);
			
	}


}


void CAipi_RETE_NNode::printNN_WM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NOT Node - Working Memory  *******"));
	//Print map container
	for( CMainFrame::g_mmNN_WM::const_iterator iter = pMainFrame->gmmNN_WM.begin(); iter!= pMainFrame->gmmNN_WM.end(); ++iter)
	{
		
		CString strNOT =_T("NOT");
		CString strWM =_T("W");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NOTNode - WME  *******"));
		strNOT +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNOT);
		strWM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
			
	}


}


void CAipi_RETE_NNode::printWM_NN()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Working Memory - NOT Node *******"));
	//Print map container
	for( CMainFrame::g_mWM_NN::const_iterator iter = pMainFrame->gmWM_NN.begin(); iter!= pMainFrame->gmWM_NN.end(); ++iter)
	{
		
		CString strWM =_T("WM");
		CString strNOT =_T("NOT");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  WME - NOTNode  *******"));
		strWM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		strNOT +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNOT);
			
	}


}


void CAipi_RETE_NNode::printNN_TK()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NOT Node - Token  *******"));
	//Print map container
	for( CMainFrame::g_mmNN_TK::const_iterator iter = pMainFrame->gmmNN_TK.begin(); iter!= pMainFrame->gmmNN_TK.end(); ++iter)
	{
		
		CString strNOT =_T("NOT");
		CString strTK =_T("T");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NOTNode - Token  *******"));
		strNOT +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNOT);
		strTK +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);
			
	}


}





void CAipi_RETE_NNode::printLinkNN_TK()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	CAipi_RETE_TK tk;

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Negated Tokens  *******"));
	//Print map container
	for( CMainFrame::g_mmNN_TK::const_iterator iter = pMainFrame->gmmNN_TK.begin(); iter!= pMainFrame->gmmNN_TK.end(); ++iter)
	{
		CString strNOT =_T("NOT");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NOT TKE  *******"));
		strNOT +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNOT);
		tstring w = tk.linkWMEs(iter->second);	
		pMainFrame->m_wndOutputTabView.AddMsg1(w.data());
			
	}

}





void CAipi_RETE_NNode::printNN()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Negated Node  *******"));
	
	//Print map container
	for( CMainFrame::g_mNNode::const_iterator iter = pMainFrame->gmNNode.begin(); iter!= pMainFrame->gmNNode.end(); ++iter)
	{
		CString strNOT =_T("NOT");
		CString strCond =_T("C");
		CString strField =_T("F");
		CString strBM =_T("B");
		CString strJN = _T("JN");
		CString strType =_T("TYPE_");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NOTNode  *******"));
		strNOT +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNOT);
		CAipi_RETE_NNode nn = (CAipi_RETE_NNode)iter->second;
 		int type = nn.getType();
		int c1 = nn.getCond1();
		int f1 = nn.getField1();
		int c2 = nn.getCond2();
		int f2 = nn.getField2();
		int bm1 = nn.getBM1();
		int jn2 = nn.getJN2();

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Node Type: "));
		strType +=  _itot( type, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strType);
		
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

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Beta Memorie 1: "));
		strBM +=  _itot( bm1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Join Node 2: "));
		strJN +=  _itot( jn2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strJN);

			
	}

}


