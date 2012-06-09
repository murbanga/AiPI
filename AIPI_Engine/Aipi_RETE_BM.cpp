// Aipi_RETE_BM.cpp: implementation of the CAipi_RETE_BM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_BM.h"

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

CAipi_RETE_BM::CAipi_RETE_BM()
{
	
}


CAipi_RETE_BM::~CAipi_RETE_BM()
{

}


CAipi_RETE_BM* CAipi_RETE_BM::addBM(int bm, tstring var1, tstring data1, tstring var2, tstring data2, int oldTK, int newTK, int wm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_BM *pObject = new CAipi_RETE_BM();
    try
	{
		pObject->setVar1(var1);
		pObject->setVar2(var2);
		pObject->setData1(data1);
		pObject->setData2(data2);
		pObject->setParentTK(oldTK);
		pObject->setChildTK(newTK);
		pObject->setWM(wm);
						
		pMainFrame->gmmBM.insert(CMainFrame::g_mmBM::value_type(bm, *pObject));
		
		/*
		CString str;
		str.Format(_T("NEW BM...%d  " ), bm);
		AfxMessageBox(str);
							
				
		str.Format(_T("var1...%s  " ), var1.c_str());
		AfxMessageBox(str);
		str.Format(_T("var1...%s  " ), var2.c_str());
		AfxMessageBox(str);
		*/
			
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




tstring CAipi_RETE_BM::findBMData1ChildTK(int bm, int child_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
 		int token = bmo.getChildTK();
		if ( token == child_tk ) 
		{
			return bmo.getData1();
		}
	
	}
	return _T("NOT_FOUND");
}

tstring CAipi_RETE_BM::findBMData2ChildTK(int bm, int child_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
 		int token = bmo.getChildTK();
		if ( token == child_tk ) 
		{
			return bmo.getData2();
		}
	
	}
	return _T("NOT_FOUND");	
}




void CAipi_RETE_BM::printBM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Beta Memory  - Variable Data *******"));
	//Print map container
	for( CMainFrame::g_mmBM::const_iterator iter = pMainFrame->gmmBM.begin(); iter!= pMainFrame->gmmBM.end(); ++iter)
	{
		CString strTK =_T("TK");
		CString strBM = _T("B");
		CString strWM = _T("W");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Beta Memory  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  BM: "));
		strBM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		

		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iter->second;
 		
		tstring var1 = bmo.getVar1();
		tstring var2 = bmo.getVar2();

		tstring data1 = bmo.getData1();
		tstring data2 = bmo.getData2();
		
		int oldTK = bmo.getParentTK();
		int newTK = bmo.getChildTK();
		int wm	= bmo.getWM();
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Variable1: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(var1.data());

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Data1: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(data1.data());
				

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Variable2: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(var2.data());
		
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Data2: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(data2.data());
		

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Parent Token: "));
		strTK +=  _itot( oldTK, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);
		
		strTK =_T("TK");
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Child Token: "));
		strTK +=  _itot( newTK, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTK);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  WM: "));
		strWM +=  _itot( wm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);


			
	}


}


/*
void CAipi_RETE_BM::addBM_TK(int bm, int tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmBM_TK.insert(CMainFrame::g_mmBM_TK::value_type(bm, tk));
	
	CString str;
	str.Format(_T("BM :...%d  " ), bm);
	AfxMessageBox(str);
	str.Format(_T("Token :...%d  " ), tk);
	AfxMessageBox(str);
	
	
}
*/

void CAipi_RETE_BM::addBM_ChildJN(int bm, int jn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmBM_ChildJN.insert(CMainFrame::g_mmBM_ChildJN::value_type(bm, jn));	
}


void CAipi_RETE_BM::editBM(int bm, tstring var1, tstring data1, tstring var2, tstring data2, int oldtk, int newtk, int wm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	eraseBM(bm);
	addBM(bm, var1, data1, var2, data2, oldtk, newtk, wm );
	

}



void CAipi_RETE_BM::editBM_ParentTK(int bm, int parent_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	int b = findBMMembers(bm);
	
		
	if( b != NOT_FOUND )
	{
		eraseBM(bm);
		addBM(bm, m_Var1, m_Data1, m_Var2, m_Data2, parent_tk, m_ChildTK, m_WM );
		
	}


}

void CAipi_RETE_BM::editBM_ChildTK(int bm, int child_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	int b = findBMMembers(bm);
	
	if( b != NOT_FOUND ) 
	{
		eraseBM(bm);
		addBM(bm, m_Var1, m_Data1, m_Var2, m_Data2, m_ParentTK, child_tk, m_WM );
	}

}


int CAipi_RETE_BM::countBM(int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmBM::iterator iter;
    return  pMainFrame->gmmBM.count(bm);

}




int CAipi_RETE_BM::TK_LowerBound(int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iter;

	iter = pMainFrame->gmmBM.lower_bound(bm);
	if( iter == pMainFrame->gmmBM.end() )
	{
		return NOT_FOUND;
	}
	
	CAipi_RETE_BM bmo = (CAipi_RETE_BM)iter->second;
	

return bmo.getChildTK();

}


int CAipi_RETE_BM::TK_UpperBound(int bm)
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iter;

	iter = pMainFrame->gmmBM.upper_bound(bm);
	
	int n = pMainFrame->gmmBM.count(bm);
	if( n < 1 )
	{
		return NOT_FOUND;
	}
	
	--iter;		

	CAipi_RETE_BM bmo = (CAipi_RETE_BM)iter->second;


return bmo.getChildTK();

}



int CAipi_RETE_BM::eraseItemBM_ParentTK(int bm, int tk)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	pBM = pMainFrame->gmmBM.equal_range(bm);
			
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		//CString str;
		//str.Format(_T("1 - ERASE BM TOKEN...%d  " ), iterBM->second);
		//AfxMessageBox(str);
		
		CAipi_RETE_BM bmo = (CAipi_RETE_BM) iterBM->second;
		int parentToken = bmo.getParentTK();
		
		if( parentToken == tk )
		{
			pMainFrame->gmmBM.erase(iterBM);
			
			//str.Format(_T("2 - ERASE BM TOKEN...%d  " ), iterBM->second);
			//AfxMessageBox(str);
			
			return iterBM->first;
			
			
		}
		
	}

return NOT_FOUND;
	
}



int CAipi_RETE_BM::eraseItemBM_ChildTK(int bm, int tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	pBM = pMainFrame->gmmBM.equal_range(bm);
			
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		//CString str;
		//str.Format(_T("1 - ERASE BM TOKEN...%d  " ), iterBM->second);
		//AfxMessageBox(str);
		CAipi_RETE_BM bmo = (CAipi_RETE_BM) iterBM->second;
		
		if( bmo.m_ChildTK == tk )
		{
			pMainFrame->gmmBM.erase(iterBM);
			//str.Format(_T("2 - ERASE BM TOKEN...%d  " ), iterBM->second);
			//AfxMessageBox(str);
			return iterBM->first;
			
			
		}
		
	}

return NOT_FOUND;
	
}














void CAipi_RETE_BM::eraseBM(int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	
	iterBM = pMainFrame->gmmBM.find(bm);
	
	if( iterBM != pMainFrame->gmmBM.end())
	{
		pMainFrame->gmmBM.erase(bm);
	}
	
}


void CAipi_RETE_BM::eraseBM_ChildJN(int bm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM_ChildJN::iterator iterJN;
	
	iterJN = pMainFrame->gmmBM_ChildJN.find(bm);
	if( iterJN != pMainFrame->gmmBM_ChildJN.end())
	{
		pMainFrame->gmmBM_ChildJN.erase(bm);
				
	}

	
}


int CAipi_RETE_BM::eraseItemBM_ChildJN(int bm, int jn)
{
	/*
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM_ChildJN::iterator, CMainFrame::g_mmBM_ChildJN::iterator>  pBM;
	pBM = pMainFrame->gmmBM_ChildJN.equal_range(bm);
			
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		//CString str;
		//str.Format(_T("1 - ERASE BM TOKEN...%d  " ), iterBM->second);
		//AfxMessageBox(str);
		if( iterBM->second == jn )
		{
			pMainFrame->gmmBM_ChildJN.erase(iterBM);
			//str.Format(_T("2 - ERASE BM TOKEN...%d  " ), iterBM->second);
			//AfxMessageBox(str);
			return iterBM->first;
			
			
		}
		
	}
*/
return NOT_FOUND;
	
}



void CAipi_RETE_BM::clearBM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmBM.clear();

}



int CAipi_RETE_BM::generateBMKey()
{
	/*
	static int nBM;
	nBM++;
	*/
	++g_currentBM;
		
return g_currentBM;


}


int CAipi_RETE_BM::previousBM(int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int prevKey = NOT_FOUND;


	CMainFrame::g_mmBM::iterator iter;
    iter = pMainFrame->gmmBM.find(bm);
	if( iter != pMainFrame->gmmBM.end())
	{
		--iter;
		prevKey = iter->first; 	
			
	}	
	
	return prevKey;
	
}

int CAipi_RETE_BM::lastBM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	if( !pMainFrame->gmmBM.empty())
	{
		iterBM = pMainFrame->gmmBM.end(); 
		--iterBM;
		return iterBM->first;
	}

	return 0;
}

	
int CAipi_RETE_BM::sizeBM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmmBM.size();

}



int CAipi_RETE_BM::searchBMParentTK(int tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::const_iterator iter;
	
	for( iter = pMainFrame->gmmBM.begin(); iter!= pMainFrame->gmmBM.end(); ++iter)
	{
		CAipi_RETE_BM bmo = (CAipi_RETE_BM) iter->second;
		
		if( bmo.m_ParentTK == tk )
		{
			return iter->first;
		}
	}

return NOT_FOUND;

}

int CAipi_RETE_BM::searchBMChildTK(int tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::const_iterator iter;
	
	for( iter = pMainFrame->gmmBM.begin(); iter!= pMainFrame->gmmBM.end(); ++iter)
	{
		CAipi_RETE_BM bmo = (CAipi_RETE_BM) iter->second;
		
		if( bmo.m_ChildTK == tk )
		{
			return iter->first;
		}
	}

return NOT_FOUND;

}

int CAipi_RETE_BM::findBMMembers(int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmBM::iterator iter;
    iter = pMainFrame->gmmBM.find(bm);
	if( iter != pMainFrame->gmmBM.end())
	{
  		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iter->second;
 		
		m_Var1 = bmo.getVar1();
		m_Var2 = bmo.getVar2();
		m_Data1 = bmo.getData1();
		m_Data2 = bmo.getData2();
		m_ParentTK = bmo.getParentTK();
		m_ChildTK	=	bmo.getChildTK();
		m_WM		= bmo.getWM();
			
		return bm;
	}
	
	return NOT_FOUND;
}

int CAipi_RETE_BM::findBMParentTK(int bm, int parent_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
 		int token = bmo.getParentTK();
		if ( token == parent_tk ) 
		{
			return token;
		}
	
	}
	
	
return NOT_FOUND;

}


int CAipi_RETE_BM::findBMChildTK(int bm, int child_tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
 		int token = bmo.getChildTK();
		if ( token == child_tk ) 
		{
			return token;
		}
	
	}
	
	
return NOT_FOUND;

}


tstring CAipi_RETE_BM::findBMVar1(int bm, tstring var1)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
 		tstring var = bmo.getVar1();
		if ( var == var1 ) 
		{
			return var;
		}
	
	}
	
	
return _T("NOT_FOUND");

}


tstring CAipi_RETE_BM::findBMVar2(int bm, tstring var2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
 		tstring var = bmo.getVar2();
		if ( var == var2 ) 
		{
			return var;
		}
	
	}
	
	
return _T("NOT_FOUND");

}

tstring CAipi_RETE_BM::findBMData1(int bm, tstring data1)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
 		tstring data = bmo.getData1();
		if ( data == data1 ) 
		{
			return data;
		}
	
	}
	
	
return _T("NOT_FOUND");

}


tstring CAipi_RETE_BM::findBMData2(int bm, tstring data2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
 		tstring data = bmo.getData2();
		if ( data == data2 ) 
		{
			return data;
		}
	
	}
	
	
return _T("NOT_FOUND");

}

int CAipi_RETE_BM::findBMWM(int bm, int wm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
 		int w = bmo.getWM();
		if ( w == wm ) 
		{
			return w;
		}
	
	}

return NOT_FOUND;	
}



int CAipi_RETE_BM::findBM_ChildJN(int bm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM_ChildJN::iterator iterJN;
	
	iterJN = pMainFrame->gmmBM_ChildJN.find(bm);
	if( iterJN != pMainFrame->gmmBM_ChildJN.end())
	{
		return iterJN->second;
				
	}

return NOT_FOUND;	
}


//Search in BM structure a specific working memory element with a specific parent token
int CAipi_RETE_BM::searchWMTK( int bm, int wm, int parent_tk )
{
	
	CAipi_RETE_TK tko;

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::const_iterator it_BM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;

	int n = pMainFrame->gmmBM.count(bm);
	int token = NOT_FOUND;
	

	if( n > 1 )
	{
		pBM = pMainFrame->gmmBM.equal_range(bm);

		for(it_BM = pBM.first; it_BM != pBM.second; ++it_BM)
		{	
			CAipi_RETE_BM bmo = (CAipi_RETE_BM)it_BM->second;
			
			int key_tk = bmo.getChildTK();
			
			tko.findTKMembers(key_tk);

			int w = tko.m_WM;
			int parent = tko.m_ParentTk;
			
				
			/*
			CString str;
			str.Format(_T("Child TK...%d  " ), key_tk);
			AfxMessageBox(str);
			str.Format(_T("Parent TK...%d  " ), parent);
			AfxMessageBox(str);
			*/
			
			if( w == wm  &&  parent == parent_tk )
			{
				/*			
				CString str;

				str.Format(_T("BM...%d  " ), bm);
				AfxMessageBox(str);
			
				str.Format(_T("WM...%d  " ), w);
				AfxMessageBox(str);

				str.Format(_T("Parent TK...%d  " ), parent_tk);
				AfxMessageBox(str);
				*/
			
				token = key_tk;
		
			}
			
			
		}
	}
	else
	{
		it_BM = pMainFrame->gmmBM.find(bm);
		if( it_BM != pMainFrame->gmmBM.end())
		{
  			CAipi_RETE_BM bmo = (CAipi_RETE_BM)it_BM->second;
					
			int key_tk =  bmo.getChildTK();

			int w = tko.findWM(key_tk);
			if( w == wm )
			{
				return key_tk;
			}
			
 		}
	}
	

	if( token != NOT_FOUND )
	{
		return token;
	}
	
return NOT_FOUND;	
	
}




















void CAipi_RETE_BM::printLinkBM_TK()
{
	CAipi_RETE_TK tko;
	TCHAR buffer[16];
	
	tstring strWM =_T("W");
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Beta Memory  *******"));
	//Print map container
	for( CMainFrame::g_mmBM::const_iterator iter = pMainFrame->gmmBM.begin(); iter!= pMainFrame->gmmBM.end(); ++iter)
	{
		CString strBM =_T("B");
		
		CAipi_RETE_BM bmo = (CAipi_RETE_BM) iter->second;

		int tk = bmo.getChildTK();

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  BME  *******"));
		strBM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		strWM = tko.linkWMEs(tk);
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM.data());
			
	}

}


void CAipi_RETE_BM::printBM_ChildJN()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Beta Memory - Child Join Node *******"));
	//Print map container
	for( CMainFrame::g_mmBM_ChildJN::const_iterator iter = pMainFrame->gmmBM_ChildJN.begin(); iter!= pMainFrame->gmmBM_ChildJN.end(); ++iter)
	{
		CString strBM =_T("B");
		CString strJN =_T("JN");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  BM _ Child JN  *******"));
		strBM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		strJN +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strJN);
			
	}
}


void CAipi_RETE_BM::printV_BM_ChildJN()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	int vsize = pMainFrame->g_vBMChildJN.size();

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Vector BM Child Join Node *******"));

	for(int i= 0; i<vsize; ++i)
	{
		CString strJN =_T("JN");

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Child JN  *******"));
		strJN +=  _itot(pMainFrame->g_vBMChildJN.at(i) , buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strJN);	
	}
}


/*
void CAipi_RETE_BM::printWMTK()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_WM wm;	
	TCHAR buffer[16];

	for(int i =0; i<pMainFrame->g_vBM_TK.size(); ++i)
	{
		CString strWM =_T("W");	
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Working Memory - Token  *******"));
		
		int w = pMainFrame->g_vBM_TK.at(i);
		strWM +=  _itot( w, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		wm.findWMMembers(w);
		tstring strI = wm.m_Id;
		tstring strA = wm.m_Attr;
		tstring strV = wm.m_Val;
		
		tstring str = strI + _T("   ") + strA + _T("   ") + strV;
		pMainFrame->m_wndOutputTabView.AddMsg1(str.data());

	}

}

*/
