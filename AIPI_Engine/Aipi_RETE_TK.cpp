// Aipi_RETE_TK.cpp: implementation of the CAipi_RETE_TK class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_TK.h"

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

CAipi_RETE_TK::CAipi_RETE_TK()
{

}

CAipi_RETE_TK::~CAipi_RETE_TK()
{

}

int CAipi_RETE_TK::generateTKKey()
{
	/*
	static int nTk;
	nTk++;
	*/

	++g_currentTK;
		
return g_currentTK;


}

/*
tstring CAipi_RETE_TK::generateTDN()
{
	TCHAR buffer[8];
	tstring strTk =_T("D");

	static int nTk;
	nTk++;
	strTk +=  _itot( nTk, buffer, 10 );
	
	
return strTk;


}
*/

CAipi_RETE_TK* CAipi_RETE_TK::createTK(int tk, int parent_tk, int wm, int bm, int jnode )
{
	/*
	CString str;
	str.Format(_T("NEW TOKEN...%d  " ), tk);
	AfxMessageBox(str);
	*/
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_TK *pObject = new CAipi_RETE_TK();
    try
	{
		pObject->setParentTk(parent_tk);
		pObject->setWM(wm);
		pObject->setBM(bm);
		pObject->setNode(jnode);
				
		pMainFrame->gmTK.insert(CMainFrame::g_mTK::value_type(tk, *pObject));
		
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


void CAipi_RETE_TK::addWM_ParentTK(int wm, int parent_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmWM_ParentTK.insert(CMainFrame::g_mmWM_ParentTK::value_type(wm, parent_tk));

}


void CAipi_RETE_TK::addWM_ChildTK(int wm, int child_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmWM_ChildTK.insert(CMainFrame::g_mmWM_ChildTK::value_type(wm, child_tk));

}


int CAipi_RETE_TK::eraseWMParentTokenE(int w, int tk)
{
	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmWM_ParentTK::iterator iterTK;
	pair <CMainFrame::g_mmWM_ParentTK::iterator, CMainFrame::g_mmWM_ParentTK::iterator>  pTK;
	pTK = pMainFrame->gmmWM_ParentTK.equal_range(w);
			
	for(iterTK = pTK.first; iterTK != pTK.second; ++iterTK)
	{	
		if( iterTK->second == tk )
		{
			pMainFrame->gmmWM_ParentTK.erase(iterTK);
			return iterTK->first;
		}
		

	}

return NOT_FOUND;


}




int CAipi_RETE_TK::eraseWMChildTokenE(int w, int tk)
{
	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmWM_ChildTK::iterator iterTK;
	pair <CMainFrame::g_mmWM_ChildTK::iterator, CMainFrame::g_mmWM_ChildTK::iterator>  pTK;
	pTK = pMainFrame->gmmWM_ChildTK.equal_range(w);
			
	for(iterTK = pTK.first; iterTK != pTK.second; ++iterTK)
	{	
		if( iterTK->second == tk )
		{
			pMainFrame->gmmWM_ChildTK.erase(iterTK);
			return iterTK->first;
		}
		

	}

return NOT_FOUND;
	
	
/*	
	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmWMTk::iterator iterTK;
			
	for(iterTK = pMainFrame->gmmWMTk.begin(); iterTK != pMainFrame->gmmWMTk.end(); ++iterTK)
	{	
		if( iterTK->second == tk )
		{
			pMainFrame->gmmWMTk.erase(iterTK->first);
			return iterTK->first;
			
			
		}
		
	}

return NOT_FOUND;
*/

}



void CAipi_RETE_TK::addTKParent_TKChild(int parent, int child)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmTKParent_TKChild.insert(CMainFrame::g_mmTKParent_TKChild::value_type(parent, child));

}


void CAipi_RETE_TK::addTKParent_TKLink(int parent, int link)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmTKParent_TKLink.insert(CMainFrame::g_mmTKParent_TKLink::value_type(parent, link));

}

/*
void CAipi_RETE_TK::createChildList()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int t = 0;

	for( CMainFrame::g_mToken::const_iterator iter = pMainFrame->gmToken.begin(); iter!= pMainFrame->gmToken.end(); ++iter)
	{
		
		t = iter->first;
		
		do
		{
			t = searchParent(t);
		
			if( t != NOT_FOUND )
			{
				addTkChildList(iter->first, t);
			
				
				CString str;
				str.Format(_T("Key Token...%d  " ), iter->first);
				AfxMessageBox(str);
				str.Format(_T("Parent Token...%d  " ), t);
				AfxMessageBox(str);
				

			}
		}while( t != NOT_FOUND );
	}	


}
*/



void CAipi_RETE_TK::createTKParent_TKLink()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmTKParent_TKChild::iterator iterCP;
	pair <CMainFrame::g_mmTKParent_TKChild::iterator, CMainFrame::g_mmTKParent_TKChild::iterator>  pCP;
		
	
	int child_tk = 0;

	for( CMainFrame::g_mTK::const_iterator iter = pMainFrame->gmTK.begin(); iter!= pMainFrame->gmTK.end(); ++iter)
	{
		
		child_tk = iter->first;
		pCP = pMainFrame->gmmTKParent_TKChild.equal_range(child_tk);
		
		for(iterCP = pCP.first; iterCP != pCP.second; ++iterCP)
		{	
				
				child_tk = iterCP->second;	
				addTKParent_TKLink(iter->first, child_tk);
				
				do
				{
					child_tk = findChild_TKParent_TKChild(child_tk);
		
					if( child_tk != NOT_FOUND )
					{
						addTKParent_TKLink(iter->first, child_tk);
			
						/*
						CString str;
						str.Format(_T("Key Token...%d  " ), iter->first);
						AfxMessageBox(str);
						str.Format(_T("Child Token...%d  " ), child_tk);
						AfxMessageBox(str);
						*/
					}

				
				}while( child_tk != NOT_FOUND );
					
					
		}
	}


}



void CAipi_RETE_TK::createTKParent_TKLinkE(int parent_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmTKParent_TKChild::iterator iterCP;
	pair <CMainFrame::g_mmTKParent_TKChild::iterator, CMainFrame::g_mmTKParent_TKChild::iterator>  pCP;
	
	//AfxMessageBox(_T("Hello1"));
	int child_tk = 0;
	pCP = pMainFrame->gmmTKParent_TKChild.equal_range(parent_tk);
	
	for(iterCP = pCP.first; iterCP != pCP.second; ++iterCP)
	{	
		//AfxMessageBox(_T("Hello2"));
	
		child_tk = iterCP->second;	
		addTKParent_TKLink(parent_tk, child_tk);
		
		do
		{
			child_tk = findChild_TKParent_TKChild(child_tk);
			
			if( child_tk != NOT_FOUND )
			{
				addTKParent_TKLink(parent_tk, child_tk);
				
				/*
				CString str;
				str.Format(_T("Key Token...%d  " ), iter->first);
				AfxMessageBox(str);
				str.Format(_T("Child Token...%d  " ), child_tk);
				AfxMessageBox(str);
				*/
			}
			
		}while( child_tk != NOT_FOUND );
		
	}
	

}



void CAipi_RETE_TK::fillTK()
{
	/*
	createTK(1, DNode, 1,  POSITIVE);
	createTK(2, DNode, 2,  POSITIVE);
	createTK(3, DNode, 4,  POSITIVE);
	createTK(4, DNode, 8,  NEGATIVE);
	createTK(5, DNode, 11, NEGATIVE);
	createTK(6, 1, 5,   POSITIVE);
	createTK(7, 2, 7,   NEGATIVE);
	createTK(8, 7, 10,  POSITIVE);
	createTK(9, 7, 11,  NEGATIVE);
	createTK(10, 8, 11, POSITIVE);
*/

}




void CAipi_RETE_TK::eraseTK(int child_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	//CMainFrame::g_mToken::iterator iter;
    //iter = pMainFrame->gmToken.find(tk);
	//if( iter != pMainFrame->gmToken.end())
	//{
		pMainFrame->gmTK.erase(child_tk);		
	//}
	

}


void CAipi_RETE_TK::eraseParent_TKParent_TKLink(int parent_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmTKParent_TKLink.erase(parent_tk);		
	
	

}


/*
int CAipi_RETE_TK::eraseChildListE(int tk1, int tk2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmTKParent_TKLink::iterator iterTK;
	pair <CMainFrame::g_mmTKParent_TKLink::iterator, CMainFrame::g_mmTKParent_TKLink::iterator>  pTK;
	pTK = pMainFrame->gmmTKParent_TKLink.equal_range(tk1);
	int r = NOT_FOUND;
	
	for(iterTK = pTK.first; iterTK != pTK.second; ++iterTK)
	{	
		if( iterTK->second == tk2 )
		{
			pMainFrame->gmmTKParent_TKLink.erase(iterTK++);
			r = 1;
		}
		else
		{
			++iterTK;
		}
		
	}


return r;
}
*/


int CAipi_RETE_TK::eraseChild_TKParent_TKLink(int tk_child)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmTKParent_TKLink::iterator iterTK;
	
	int r = NOT_FOUND;
	
	
	for(iterTK = pMainFrame->gmmTKParent_TKLink.begin(); iterTK != pMainFrame->gmmTKParent_TKLink.end();) 
	{	
		if( iterTK->second == tk_child )
		{
			pMainFrame->gmmTKParent_TKLink.erase(iterTK++);
			r = FOUND;
		}
		else
		{
			++iterTK;
		}
		
	}

return r;
}

int CAipi_RETE_TK::eraseChild_TKParent_TKChild(int tk_child)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmTKParent_TKChild::iterator iterTK;
	
	int r = NOT_FOUND;
	
	
	for(iterTK = pMainFrame->gmmTKParent_TKChild.begin(); iterTK != pMainFrame->gmmTKParent_TKChild.end();) 
	{	
		if( iterTK->second == tk_child )
		{
			pMainFrame->gmmTKParent_TKChild.erase(iterTK++);
			r = FOUND;
		}
		else
		{
			++iterTK;
		}
		
	}

return r;
}


void CAipi_RETE_TK::eraseParent_TKParent_TKChild(int tk_parent)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmTKParent_TKChild.erase(tk_parent);		
	
	

}

int CAipi_RETE_TK::eraseItemTKParent_TKChild(int tk1, int tk2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmTKParent_TKLink::iterator iterTK;
	pair <CMainFrame::g_mmTKParent_TKLink::iterator, CMainFrame::g_mmTKParent_TKLink::iterator>  pTK;
	pTK = pMainFrame->gmmTKParent_TKLink.equal_range(tk1);
			
	for(iterTK = pTK.first; iterTK != pTK.second; ++iterTK)
	{	
		if( iterTK->second == tk2 )
		{
			pMainFrame->gmmTKParent_TKChild.erase(iterTK);
			return iterTK->first;
			
			
		}
		
	}

return NOT_FOUND;
}













void CAipi_RETE_TK::eraseWMParentTK(int wme)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmWM_ParentTK.erase(wme);		
	
	

}

void CAipi_RETE_TK::eraseWMChildTK(int wme)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmWM_ChildTK.erase(wme);		
	
	

}


int CAipi_RETE_TK::eraseWMParentTKE(int wme, int tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmWM_ParentTK::iterator iterTk;
	pair <CMainFrame::g_mmWM_ParentTK::iterator, CMainFrame::g_mmWM_ParentTK::iterator>  pTk;
	pTk = pMainFrame->gmmWM_ParentTK.equal_range(wme);
			
	for(iterTk = pTk.first; iterTk != pTk.second; ++iterTk)
	{	
		if( iterTk->second == tk )
		{
			pMainFrame->gmmWM_ParentTK.erase(iterTk);
			return iterTk->first;
			
			
		}
		
	}

return NOT_FOUND;
	
}


int CAipi_RETE_TK::eraseWMChildTKE(int wme, int tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmWM_ChildTK::iterator iterTk;
	pair <CMainFrame::g_mmWM_ChildTK::iterator, CMainFrame::g_mmWM_ChildTK::iterator>  pTk;
	pTk = pMainFrame->gmmWM_ChildTK.equal_range(wme);
			
	for(iterTk = pTk.first; iterTk != pTk.second; ++iterTk)
	{	
		if( iterTk->second == tk )
		{
			pMainFrame->gmmWM_ChildTK.erase(iterTk);
			return iterTk->first;
			
			
		}
		
	}

return NOT_FOUND;
	
}

void CAipi_RETE_TK::clearTKStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmTK.clear();
	pMainFrame->gmmTKParent_TKLink.clear();
	pMainFrame->gmmTKParent_TKChild.clear();
	pMainFrame->gmmWM_ParentTK.clear();	
	pMainFrame->gmmWM_ChildTK.clear();	
}



void CAipi_RETE_TK::clearTK()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->gmTK.clear();		
	

}


void CAipi_RETE_TK::clearTKParent_TKLink()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->gmmTKParent_TKLink.clear();		
	

}

void CAipi_RETE_TK::clearTKParent_TKChild()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->gmmTKParent_TKChild.clear();		
	

}

void CAipi_RETE_TK::clearWM_ParentTK()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->gmmWM_ParentTK.clear();		
	

}

void CAipi_RETE_TK::clearWM_ChildTK()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->gmmWM_ChildTK.clear();		
	

}


int CAipi_RETE_TK::findWMParentTK(int tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mTK::iterator iter;
    iter = pMainFrame->gmTK.find(tk);
	if( iter != pMainFrame->gmTK.end())
	{
		CAipi_RETE_TK tko = (CAipi_RETE_TK)iter->second;
 	
		int parent_tk = tko.getParentTk();
		
		return findWM(parent_tk);
	}
	
		return NOT_FOUND;
	

}


int CAipi_RETE_TK::findParentTk(int chld_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mTK::iterator iter;
    iter = pMainFrame->gmTK.find(chld_tk);
	if( iter != pMainFrame->gmTK.end())
	{
		CAipi_RETE_TK tko = (CAipi_RETE_TK)iter->second;
 	
		return tko.getParentTk();
	}
	
		return NOT_FOUND;
	

}



int CAipi_RETE_TK::findNode(int chld_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mTK::iterator iter;
    iter = pMainFrame->gmTK.find(chld_tk);
	if( iter != pMainFrame->gmTK.end())
	{
		CAipi_RETE_TK tko = (CAipi_RETE_TK)iter->second;
 	
		return tko.getNode();
	}
	
		return NOT_FOUND;
	

}

int CAipi_RETE_TK::findBM(int chld_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mTK::iterator iter;
    iter = pMainFrame->gmTK.find(chld_tk);
	if( iter != pMainFrame->gmTK.end())
	{
		CAipi_RETE_TK tko = (CAipi_RETE_TK)iter->second;
 	
		return tko.getBM();
	}
	
		return NOT_FOUND;
	

}



int CAipi_RETE_TK::findWM(int chld_tk)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mTK::iterator iter;
    iter = pMainFrame->gmTK.find(chld_tk);
	if( iter != pMainFrame->gmTK.end())
	{
		CAipi_RETE_TK tko = (CAipi_RETE_TK)iter->second;
 	
		return tko.getWM();
		
	}
	
	return NOT_FOUND;

}





int CAipi_RETE_TK::findTKMembers(int chld_tk)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mTK::iterator iter;
    iter = pMainFrame->gmTK.find(chld_tk);
	if( iter != pMainFrame->gmTK.end())
	{
		CAipi_RETE_TK tko = (CAipi_RETE_TK)iter->second;
 	
		m_ParentTk = tko.getParentTk();
		m_WM = tko.getWM();
		m_Node = tko.getNode();
		
		return FOUND;
	}
	
	return NOT_FOUND;

}








int CAipi_RETE_TK::searchTKWM(int wm)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mTK::const_iterator iter = pMainFrame->gmTK.begin(); iter!= pMainFrame->gmTK.end(); ++iter)
	{
		CAipi_RETE_TK tko = (CAipi_RETE_TK)iter->second;
		int w = tko.getWM();
		
		if( w == wm )
		{
			//pMainFrame->m_wndOutputTabView.AddMsg1(tok.getToken().data());
			return iter->first;
		}
        	
	} 
	
return NOT_FOUND;
}




int CAipi_RETE_TK::searchTKChildTK(int parent_tk)
{
   CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mTK::const_iterator iter = pMainFrame->gmTK.begin(); iter!= pMainFrame->gmTK.end(); ++iter)
	{
		CAipi_RETE_TK tko = (CAipi_RETE_TK)iter->second;
		int t = tko.getParentTk();
		
		if( t == parent_tk )
		{
			//pMainFrame->m_wndOutputTabView.AddMsg1(tok.getToken().data());
			return iter->first;
		}
        	
	} 
	

return NOT_FOUND;

}



int CAipi_RETE_TK::findWM_ParentTK(int wm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmWM_ParentTK::iterator iter;
    iter = pMainFrame->gmmWM_ParentTK.find(wm);
	
	if( iter != pMainFrame->gmmWM_ParentTK.end())
	{
		return iter->second;
	}
		
return NOT_FOUND;

}

int CAipi_RETE_TK::findWM_ChildTK(int wm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmWM_ChildTK::iterator iter;
    iter = pMainFrame->gmmWM_ChildTK.find(wm);
	
	if( iter != pMainFrame->gmmWM_ChildTK.end())
	{
		return iter->second;
	}
		
return NOT_FOUND;

}




int CAipi_RETE_TK::findChild_TKParent_TKChild(int parent)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmTKParent_TKChild::iterator iter;
    iter = pMainFrame->gmmTKParent_TKChild.find(parent);
	
	if( iter != pMainFrame->gmmTKParent_TKChild.end())
	{
		return iter->second;
	}
		
return NOT_FOUND;

}





int CAipi_RETE_TK::countWM(int wm)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int n =0;
	
	for( CMainFrame::g_mTK::const_iterator iter = pMainFrame->gmTK.begin(); iter!= pMainFrame->gmTK.end(); ++iter)
	{
		CAipi_RETE_TK tko = (CAipi_RETE_TK)iter->second;
		int w = tko.getWM();
		
		if( w == wm )
		{
			n++;
		}
        	
	} 
	
return n;
}

int CAipi_RETE_TK::countWM_ParentTK(int wm)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmWM_ParentTK::iterator iter;
    return  pMainFrame->gmmWM_ParentTK.count(wm);
	
}

int CAipi_RETE_TK::countWM_ChildTK(int wm)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmWM_ChildTK::iterator iter;
    return  pMainFrame->gmmWM_ChildTK.count(wm);
	
}




int CAipi_RETE_TK::countParentTK(int parent_tk)
{
   CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
   int n =0;
	
   for( CMainFrame::g_mTK::const_iterator iter = pMainFrame->gmTK.begin(); iter!= pMainFrame->gmTK.end(); ++iter)
	{
		CAipi_RETE_TK tko = (CAipi_RETE_TK)iter->second;
		int t = tko.getParentTk();
		
		if( t == parent_tk )
		{
			n++;
		}
        	
	} 
	

return n;

}


int CAipi_RETE_TK::countChildTK(int child_tk)
{
   CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
   int n =0;
	
   for( CMainFrame::g_mTK::const_iterator iter = pMainFrame->gmTK.begin(); iter!= pMainFrame->gmTK.end(); ++iter)
	{
		CAipi_RETE_TK tko = (CAipi_RETE_TK)iter->second;
		int t = iter->first;
		
		if( t == child_tk )
		{
			n++;
		}
        	
	} 
	

return n;

}










void CAipi_RETE_TK::printTK()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Tokens  *******"));
	//Print map container
	for( CMainFrame::g_mTK::const_iterator iter = pMainFrame->gmTK.begin(); iter!= pMainFrame->gmTK.end(); ++iter)
	{
		CString strTK	=_T("T");
		CString strWM	=_T("W");
		CString strBM =_T("B");
		CString strNode =_T("N");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  TKE  *******"));
		
		strTK +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);
		
		strTK = _T("T");
		CAipi_RETE_TK tko = (CAipi_RETE_TK)iter->second;
		int t =  tko.getParentTk();
		strTK +=  _itot( t,  buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);
        
		int wm = tko.getWM();
		strWM +=  _itot( wm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);

		int bm = tko.getBM();
		strBM +=  _itot( bm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);


		int node = tko.getNode();
		strNode +=  _itot( node, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNode);
		
			
	}


}


void CAipi_RETE_TK::printLinkTK()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Tokens  *******"));
	//Print map container
	for( CMainFrame::g_mTK::const_iterator iter = pMainFrame->gmTK.begin(); iter!= pMainFrame->gmTK.end(); ++iter)
	{
		CString strTK =_T("T");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  TKE  *******"));
		strTK +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);
		tstring w = linkWMEs(iter->first);	
		pMainFrame->m_wndOutputTabView.AddMsg1(w.data());
			
	}

}


void CAipi_RETE_TK::printWM_ParentTK()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Working Memory Elements - Parent Tokens  *******"));
	//Print map container
	for( CMainFrame::g_mmWM_ParentTK::const_iterator iter = pMainFrame->gmmWM_ParentTK.begin(); iter!= pMainFrame->gmmWM_ParentTK.end(); ++iter)
	{
		CString strTK =_T("T");
		CString strWM = _T("W");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  WME - ParentTKE  *******"));
		strWM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
			
		strTK +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);
		
	}

}

void CAipi_RETE_TK::printWM_ChildTK()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Working Memory Elements - Child Tokens  *******"));
	//Print map container
	for( CMainFrame::g_mmWM_ChildTK::const_iterator iter = pMainFrame->gmmWM_ChildTK.begin(); iter!= pMainFrame->gmmWM_ChildTK.end(); ++iter)
	{
		CString strTK =_T("T");
		CString strWM = _T("W");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  WME - ChildTKE  *******"));
		strWM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
			
		strTK +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);
		
	}

}

void CAipi_RETE_TK::printTKParent_TKChild()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Token Parent - Token Child  *******"));
	//Print map container
	for( CMainFrame::g_mmTKParent_TKChild::const_iterator iter = pMainFrame->gmmTKParent_TKChild.begin(); iter!= pMainFrame->gmmTKParent_TKChild.end(); ++iter)
	{
		CString strChild =_T("TKC");
		CString strParent = _T("TKP");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  TKParent - TKChild  *******"));
		strParent +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strParent);
			
		strChild +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strChild);
		
	}

}


void CAipi_RETE_TK::printTKParent_TKLink()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  List of Linked Tokens  *******"));
	//Print map container
	for( CMainFrame::g_mmTKParent_TKLink::const_iterator iter = pMainFrame->gmmTKParent_TKLink.begin(); iter!= pMainFrame->gmmTKParent_TKLink.end(); ++iter)
	{
		CString strParent =_T("TK_Parent");
		CString strChild = _T("TK_LinkedChilds");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  TKParent - Linked Child Tokens *******"));
		strParent +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strParent);
			
		strChild +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strChild);
		
	}

}

//Shows all working memory elements linked in a token
//Search for all the tokens to find links between them
//If the token doesn't exist returns NOT_FOUND
//If any WME is repeated in a token returns REPEATED
 
tstring CAipi_RETE_TK::linkWMEs(int tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buf[4];
	
	tstring strTK =_T("W"); 
	int iTK = findWM(tk);
	
	strTK += _itot(iTK, buf,10);
	
	int iWME = NOT_FOUND;	
	
	if(pMainFrame->gmTK.size() > 0 )
	{
		CMainFrame::g_mTK::iterator iter;
		iter = pMainFrame->gmTK.find(tk);

		
		if( iter != pMainFrame->gmTK.end())
		{
		
			do
			{
				tstring strWME =_T("W");
							
				
				tk = findParentTk(tk);
				iWME = findWM(tk);
				strWME += _itot(iWME, buf,10);
				
				
				if( iWME != NOT_FOUND) 
				{
					strTK += _T("^") + strWME;
				}
				
				//AfxMessageBox(strTK.data());
				//AfxMessageBox(strWME.data());

			}while( iWME != NOT_FOUND );
	
		}
		else
		{
			return _T("NOT_FOUND");
		}
	}
	
	return strTK;
	
	
}



