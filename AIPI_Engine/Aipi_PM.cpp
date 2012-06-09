// Aipi_PM.cpp: implementation of the CAipi_PM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_PM.h"

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

CAipi_PM::CAipi_PM()
{

}

CAipi_PM::~CAipi_PM()
{
	//clearPM();
}


void CAipi_PM::addPM_Cond(long pm, int lhs)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_Cond.insert(CMainFrame::g_mmPM_Cond::value_type(pm, lhs));
}


void CAipi_PM::addPM_Fact(long pm, int rhs)
{
	//AfxMessageBox(_T("Add Fact"));
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_Fact.insert(CMainFrame::g_mmPM_Fact::value_type(pm, rhs));
}


void CAipi_PM::addPM_RelCond(long pm, int lhs)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_RelCond.insert(CMainFrame::g_mmPM_RelCond::value_type(pm, lhs));	
}



void CAipi_PM::addPM_BM(long pm, int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_BM.insert(CMainFrame::g_mmPM_BM::value_type(pm, bm));
}

void CAipi_PM::addPM_PNode(long pm, int pnode)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmPM_PNode.insert(CMainFrame::g_mPM_PNode::value_type(pm, pnode));
}

void CAipi_PM::addPM_IVar(long pm, tstring id)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_IVar.insert(CMainFrame::g_mmPM_IVar::value_type(pm, id) );

}

void CAipi_PM::addPM_AVar(long pm, tstring attr)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_AVar.insert(CMainFrame::g_mmPM_AVar::value_type(pm, attr) );
}

void CAipi_PM::addPM_VVar(long pm, tstring val)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_VVar.insert(CMainFrame::g_mmPM_VVar::value_type(pm, val) );

}



void CAipi_PM::addPM_IVarIForm(long pm, long id_iform)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_IVarIForm.insert(CMainFrame::g_mmPM_IVarIForm::value_type(pm, id_iform) );

}

void CAipi_PM::addPM_AVarIForm(long pm, long attr_iform)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_AVarIForm.insert(CMainFrame::g_mmPM_AVarIForm::value_type(pm, attr_iform) );
}

void CAipi_PM::addPM_VVarIForm(long pm, long val_iform)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_VVarIForm.insert(CMainFrame::g_mmPM_VVarIForm::value_type(pm, val_iform) );

}


CAipi_PM* CAipi_PM::addPM(long pm, tstring name, float cf, int weight)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_PM *pObject = new CAipi_PM();
    try
	{
		pObject->setName(name);
		pObject->setCF(cf);
		pObject->setWeight(weight);
				
		pMainFrame->gmPM.insert(CMainFrame::g_mPM::value_type(pm, *pObject));
		
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



CAipi_PM* CAipi_PM::addPM_Name(long pm, tstring name)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_PM *pObject = new CAipi_PM();
    try
	{
		pObject->setName(name);
		pObject->setCF(1);
		pObject->setWeight(0);
				
		pMainFrame->gmPM.insert(CMainFrame::g_mPM::value_type(pm, *pObject));
		
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





int CAipi_PM::countPM_Cond(long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmPM_Cond::iterator iter;
    return  pMainFrame->gmmPM_Cond.count(pm);

}

int CAipi_PM::countPM_BM(long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmPM_BM::iterator iter;
    return  pMainFrame->gmmPM_BM.count(pm);

}


int CAipi_PM::sizePM_Cond()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmmPM_Cond.size();

}

int CAipi_PM::sizePM_Fact()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmmPM_Fact.size();

}

int CAipi_PM::sizePM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmPM.size();

}


void CAipi_PM::clearPMStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	//Production memory information
	pMainFrame->gmPM.clear();
	//Production memory conditions
	pMainFrame->gmmPM_Cond.clear();
	//Production memory facts
	pMainFrame->gmmPM_Fact.clear();
	//Production memory beta memories
	pMainFrame->gmmPM_BM.clear();
	//Production memory production node
	pMainFrame->gmPM_PNode.clear();
	//Production memory relational conditions
	pMainFrame->gmmPM_RelCond.clear();
	

	//Production memory variables
	pMainFrame->gmmPM_IVar.clear();
	pMainFrame->gmmPM_AVar.clear();
	pMainFrame->gmmPM_VVar.clear();

	//Temporal
	pMainFrame->gsIVarIForm.clear();
	pMainFrame->gsAVarIForm.clear();
	pMainFrame->gsVVarIForm.clear();



}


void CAipi_PM::clearPM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmPM.clear();

}

void CAipi_PM::clearPM_Cond()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_Cond.clear();

}

void CAipi_PM::clearPM_Vars()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_IVar.clear();
	pMainFrame->gmmPM_AVar.clear();
	pMainFrame->gmmPM_VVar.clear();

}

void CAipi_PM::erasePM_BM(long pm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_BM::iterator iterPM;
	
	iterPM = pMainFrame->gmmPM_BM.find(pm);
	if( iterPM != pMainFrame->gmmPM_BM.end())
	{
		pMainFrame->gmmPM_BM.erase(pm);	
		
	}

	
}
void CAipi_PM::erasePM_Cond(long pm)
{
	CAipi_LHS lhso;
	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_Cond::iterator it_PM;
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Cond.equal_range(pm);	

	for(it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		lhso.eraseLHS( it_PM->second );
	}

	it_PM = pMainFrame->gmmPM_Cond.find(pm);
	if( it_PM != pMainFrame->gmmPM_Cond.end())
	{
		pMainFrame->gmmPM_Cond.erase(pm);	
	}


}


void CAipi_PM::erasePM_PNode(long pm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mPM_PNode::iterator iterPM;
	
	iterPM = pMainFrame->gmPM_PNode.find(pm);
	if( iterPM != pMainFrame->gmPM_PNode.end())
	{
		pMainFrame->gmPM_PNode.erase(pm);	
		
	}

}


long CAipi_PM::generatePMKey()
{
	static long nPM;
	nPM++;
		
return nPM;
}


void CAipi_PM::fillPM_Cond()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	addPM_Name(1, _T("Reglas 01"));
	addPM_Name(2, _T("Reglas 02"));
	addPM_Name(3, _T("Reglas 03"));
	
	
	addPM_Cond(1,1);
	addPM_Cond(1,2);
	addPM_Cond(1,3);
	addPM_Cond(2,4);
	addPM_Cond(2,5);
	addPM_Cond(2,6);
	addPM_Cond(2,7);
	addPM_Cond(3,8);
	addPM_Cond(3,9);
	addPM_Cond(3,10);
	addPM_Cond(3,11);

	

	CString f;
	f.Format(_T("PM SIZE ...%d"), pMainFrame->gmmPM_Cond.size());
	pMainFrame->m_wndOutputTabView.AddMsg1(f);



}



void CAipi_PM::fillPM_Vars(long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_sIVar::iterator it_i;
	
	for (it_i = pMainFrame->gsIVar.begin(); it_i != pMainFrame->gsIVar.end(); ++it_i) 
	{
        pMainFrame->gmmPM_IVar.insert(CMainFrame::g_mmPM_IVar::value_type(pm, *it_i) );
    }

	CMainFrame::g_sAVar::iterator it_a;
	
	for (it_a = pMainFrame->gsAVar.begin(); it_a != pMainFrame->gsAVar.end(); ++it_a) 
	{
        pMainFrame->gmmPM_AVar.insert(CMainFrame::g_mmPM_AVar::value_type(pm, *it_a) );
    }

	CMainFrame::g_sVVar::iterator it_v;
	
	for (it_v = pMainFrame->gsVVar.begin(); it_v != pMainFrame->gsVVar.end(); ++it_v) 
	{
        pMainFrame->gmmPM_VVar.insert(CMainFrame::g_mmPM_VVar::value_type(pm, *it_v) );
    }

	pMainFrame->gsIVar.clear();
	pMainFrame->gsAVar.clear();
	pMainFrame->gsVVar.clear();

}





void CAipi_PM::fillPM_VarsIForm(long pm)
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_sIVarIForm::iterator it_i;
	
	for (it_i = pMainFrame->gsIVarIForm.begin(); it_i != pMainFrame->gsIVarIForm.end(); ++it_i) 
	{
        pMainFrame->gmmPM_IVarIForm.insert(CMainFrame::g_mmPM_IVarIForm::value_type(pm, *it_i) );
    }

	CMainFrame::g_sAVarIForm::iterator it_a;
	
	for (it_a = pMainFrame->gsAVarIForm.begin(); it_a != pMainFrame->gsAVarIForm.end(); ++it_a) 
	{
        pMainFrame->gmmPM_AVarIForm.insert(CMainFrame::g_mmPM_AVarIForm::value_type(pm, *it_a) );
    }

	CMainFrame::g_sVVarIForm::iterator it_v;
	
	for (it_v = pMainFrame->gsVVarIForm.begin(); it_v != pMainFrame->gsVVarIForm.end(); ++it_v) 
	{
        pMainFrame->gmmPM_VVarIForm.insert(CMainFrame::g_mmPM_VVarIForm::value_type(pm, *it_v) );
    }

	pMainFrame->gsIVarIForm.clear();
	pMainFrame->gsAVarIForm.clear();
	pMainFrame->gsVVarIForm.clear();

}


int CAipi_PM::searchCond(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmPM_Cond::const_iterator iter = pMainFrame->gmmPM_Cond.begin(); iter!= pMainFrame->gmmPM_Cond.end(); ++iter)
	{
		if( c == iter->second )
			return iter->first;
	}
	
return NOT_FOUND;
}


int CAipi_PM::searchCondPM(int c, int p)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Cond.equal_range(p);
	
	for(CMainFrame::g_mmPM_Cond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		if( it_PM->second == c )
		{
			return c;
			
		}
	}
	
return NOT_FOUND;
}

int CAipi_PM::searchFactPM(int f, int p)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pair <CMainFrame::g_mmPM_Fact::iterator, CMainFrame::g_mmPM_Fact::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Fact.equal_range(p);
	
	for(CMainFrame::g_mmPM_Fact::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		if( it_PM->second == f )
		{
			return f;
			
		}
	}
	
return NOT_FOUND;
}

int CAipi_PM::searchRelCondPM(int c, int p)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pair <CMainFrame::g_mmPM_RelCond::iterator, CMainFrame::g_mmPM_RelCond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_RelCond.equal_range(p);
	
	for(CMainFrame::g_mmPM_RelCond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		if( it_PM->second == c )
		{
			return c;
			
		}
	}
	
return NOT_FOUND;
}




//If productions have the same conditions returns TRUE
//If productions doesn't have the same conditions returns FALSE
 
bool CAipi_PM::compareAllCond(long p1, long p2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM1;
	pPM1 = pMainFrame->gmmPM_Cond.equal_range(p1);
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM2;
	pPM2 = pMainFrame->gmmPM_Cond.equal_range(p2);
	
	bool b = false;
	int initCount = 0;
	int count1 = countPM_Cond(p1);
	int count2 = countPM_Cond(p2);

	if( count1 != count2)
	{
		return false;
	}
	
	CAipi_LHS lhso;

	for(CMainFrame::g_mmPM_Cond::iterator it_PM1 = pPM1.first; it_PM1 != pPM1.second; ++it_PM1)
	{	
		for(CMainFrame::g_mmPM_Cond::iterator it_PM2 = pPM2.first; it_PM2 != pPM2.second; ++it_PM2)
		{	
			if( lhso.compareEqualCond(it_PM1->second, it_PM2->second ) )
			{
				initCount++;
			}
		}	
	}
	
	if( initCount == count1 )
	{
		b = true;
		//AfxMessageBox(_T("The conditions are equal"));
	}
	else
	{
		b = false;
		//AfxMessageBox(_T("The conditions are not equal"));
	}


return b;
}


//If productions have the same conditions returns TRUE
//If productions doesn't have the same conditions returns FALSE

bool CAipi_PM::compareRangeCond(long p1, long p2, int c11, int c12, int c21, int c22)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM1;
	pPM1 = pMainFrame->gmmPM_Cond.equal_range(p1);
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM2;
	pPM2 = pMainFrame->gmmPM_Cond.equal_range(p2);
	
	bool b = false;
	int initCount = 0;
	int Count1 = (c12 - c11)+1;
	int Count2 = (c22 -  c21)+1;

	if( Count1 != Count2)
	{
		//AfxMessageBox(_T("No Son iguales"));
		return false;
	}
	
	CAipi_LHS lhso;
	
	
	for(CMainFrame::g_mmPM_Cond::iterator it_PM1 = pPM1.first; it_PM1 != pPM1.second; ++it_PM1)
	{	
		if( it_PM1->second < c11 )
			continue;
		
		if( it_PM1->second > c12 )
			break; 
		
		for(CMainFrame::g_mmPM_Cond::iterator it_PM2 = pPM2.first; it_PM2 != pPM2.second; ++it_PM2)
		{	
			if( it_PM2->second < c21 )
				continue;
			if( it_PM2->second > c22 )
				break; 
		
			if( lhso.compareEqualCond(it_PM1->second, it_PM2->second ) )
			{
				/*
				CString str;
				str.Format(_T("Cond1...%d  " ), it_PM1->second);
				AfxMessageBox(str);
				str.Format(_T("Cond2...%d  " ), it_PM2->second);
				AfxMessageBox(str);
				*/
				initCount++;
			}
		
		}	
	}
	
	if( initCount == Count1 )
	{
		b = true;
		//AfxMessageBox(_T("The conditions are equal"));
	}
	else
	{
		b = false;
		//AfxMessageBox(_T("The conditions are not equal"));

	}

return b;
}


//If productions have the same conditions returns 1
//If productions doesn't have the same conditions returns -1

bool CAipi_PM::compareRangeNNCond(long p1, long p2, int c11, int c12, int c21, int c22)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM1;
	pPM1 = pMainFrame->gmmPM_Cond.equal_range(p1);
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM2;
	pPM2 = pMainFrame->gmmPM_Cond.equal_range(p2);
	
	bool b = false;
	int initCount = 0;
	int Count1 = (c12 - c11)+1;
	int Count2 = (c22 -  c21)+1;

	if( Count1 != Count2)
	{
		return false;
	}
	
	CAipi_LHS lhso;
	
	
	for(CMainFrame::g_mmPM_Cond::iterator it_PM1 = pPM1.first; it_PM1 != pPM1.second; ++it_PM1)
	{	
		if( it_PM1->second < c11 )
			continue;
		
		if( it_PM1->second > c12 )
			break; 
		
		for(CMainFrame::g_mmPM_Cond::iterator it_PM2 = pPM2.first; it_PM2 != pPM2.second; ++it_PM2)
		{	
			if( it_PM2->second < c21 )
				continue;
			if( it_PM2->second > c22 )
				break; 
		
			if( lhso.compareEqualCond(it_PM1->second, it_PM2->second ) )
			{
				CAipi_RETE_NNode not;
				int  not1 = not.findCond_NN(it_PM1->second);
				int  not2 = not.findCond_NN(it_PM2->second);

				if( (not1 == NOT_FOUND  && not2 == NOT_FOUND) || (not1 != NOT_FOUND && not2 != NOT_FOUND)  )
				{
					initCount++;
					/*
						CString str;
						str.Format(_T("Cond1...%d  " ), it_PM1->second);
						AfxMessageBox(str);
						str.Format(_T("Cond2...%d  " ), it_PM2->second);
						AfxMessageBox(str);
					*/
				}
				else
				{
					//AfxMessageBox(_T("No Son iguales"));
					return -1;
				}
				
			}
		
		}	
	}
	
	if( initCount == Count1 )
	{
		b = true;
		//AfxMessageBox(_T("The conditions are equal"));
	}
	else
	{
		b = false;
		//AfxMessageBox(_T("The conditions are not equal"));

	}

return b;
}

/*
int CAipi_PM::findLowerCond(int pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_Cond::iterator iter;
	
	int n = pMainFrame->gmmPM_Cond.count(pm);

		if(n > 0 )	
		{
			pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
			pPM = pMainFrame->gmmPM_Cond.equal_range(pm);
			iter = pPM.first;
			return iter->second;
		
		}
	


return NOT_FOUND;
}


int CAipi_PM::findUpperCond(int pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_Cond::iterator iter;
	
	int n = pMainFrame->gmmPM_Cond.count(pm);

		if(n > 0 )	
		{
			pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
			pPM = pMainFrame->gmmPM_Cond.equal_range(pm);	
			iter = pPM.second;
			--iter;
			return iter->second;	
		}

return NOT_FOUND;

}
*/

int CAipi_PM::PM_CondLowerBound(long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_Cond::iterator iter;

	iter = pMainFrame->gmmPM_Cond.lower_bound(pm);
	if( iter == pMainFrame->gmmPM_Cond.end() )
	{
		return NOT_FOUND;
	}
	
return iter->second;

}


int CAipi_PM::PM_CondUpperBound(long pm)
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_Cond::iterator iter;

	iter = pMainFrame->gmmPM_Cond.upper_bound(pm);
	
	int n = pMainFrame->gmmPM_Cond.count(pm);
	if( n < 1 )
	{
		return NOT_FOUND;
	}
	
	--iter;		
return iter->second;

}


int CAipi_PM::PM_BMLowerBound(long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_BM::iterator iter;

	iter = pMainFrame->gmmPM_BM.lower_bound(pm);
	if( iter == pMainFrame->gmmPM_BM.end() )
	{
		return NOT_FOUND;
	}
	
return iter->second;

}


int CAipi_PM::PM_BMUpperBound(long pm)
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_BM::iterator iter;

	iter = pMainFrame->gmmPM_BM.upper_bound(pm);
	
	int n = pMainFrame->gmmPM_BM.count(pm);
	if( n < 1 )
	{
		return NOT_FOUND;
	}
	
	--iter;		
return iter->second;

}

//return 1 if there are elements in the production
//return 0 if there are no elements in the production
/*
int CAipi_PM::getPMEs( int p )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->g_vPME.clear();

	CMainFrame::g_mmPM::iterator iter;
	int n = pMainFrame->gmmPM.count(p);

		if(n > 0 )	
		{
				pair <CMainFrame::g_mmPM::iterator, CMainFrame::g_mmPM::iterator>  pPM;
				pPM = pMainFrame->gmmPM.equal_range(p);

				for(iter = pPM.first; iter != pPM.second; ++iter)
				{	
					pMainFrame->g_vPME.push_back(iter->second);
				}
			return 1;
		}
				
return 0;	  	 
}

*/



tstring CAipi_PM::findPMName( long pm )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mPM::iterator iter;
    iter = pMainFrame->gmPM.find(pm);
	if( iter != pMainFrame->gmPM.end())
	{
  		CAipi_PM  name = (CAipi_PM)iter->second;
 		return name.getName();
	}
	
	return _T("NOT_FOUND");
	
}


float CAipi_PM::findPMCF( long pm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mPM::iterator iter;
    iter = pMainFrame->gmPM.find(pm);
	if( iter != pMainFrame->gmPM.end())
	{
  		CAipi_PM cf = (CAipi_PM)iter->second;
		return cf.getCF();
	}
	
	return NOT_FOUND;

			

}

int CAipi_PM::findPMWeight( long pm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mPM::iterator iter;
    iter = pMainFrame->gmPM.find(pm);
	if( iter != pMainFrame->gmPM.end())
	{
  		CAipi_PM weight = (CAipi_PM)iter->second;
 		return weight.getWeight();
	}
	
	
return NOT_FOUND;
	

}




int CAipi_PM::findPMMembers(long pm)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mPM::iterator iter;
    iter = pMainFrame->gmPM.find(pm);
	if( iter != pMainFrame->gmPM.end())
	{
		CAipi_PM pmo = (CAipi_PM)iter->second;
 	
		m_Name = pmo.getName();
		m_CF = pmo.getCF();
		m_Weight = pmo.getWeight();
		
		return pm;
	}
	
return NOT_FOUND;
	
}


int CAipi_PM::findPM_PNode( long pm )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mPM_PNode::iterator iter;
    iter = pMainFrame->gmPM_PNode.find(pm);
	if( iter != pMainFrame->gmPM_PNode.end())
	{
  		return iter->second;
 	}
	
	return NOT_FOUND;
	
}


int CAipi_PM::findPM_BM(int pm, int bm)
{
	/*
	CString st;
	st.Format(_T("PM...%d  " ), pm);
	AfxMessageBox(st);
	st.Format(_T("BM...%d  " ), bm);
	AfxMessageBox(st);
	*/		
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_BM::iterator iterPM;
	pair <CMainFrame::g_mmPM_BM::iterator, CMainFrame::g_mmPM_BM::iterator>  pPM;
	
	pPM = pMainFrame->gmmPM_BM.equal_range(pm);
	
	for(iterPM = pPM.first; iterPM != pPM.second; ++iterPM)
	{	
			int bme = iterPM->second;
			if( bme == bm )
			{
				//AfxMessageBox(_T("Found"));
				return FOUND;
			}
	
	}
	
return NOT_FOUND;

}

int CAipi_PM::findPM_MetaCond( long pm)
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmPM_Cond::iterator iter;
    iter = pMainFrame->gmmPM_Cond.find(pm);
	if( iter != pMainFrame->gmmPM_Cond.end())
	{
  		return iter->second;
	}
	
	return NOT_FOUND;
}


void CAipi_PM::replacePM_Cond(int pm, int cond1, int cond2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Cond.equal_range(pm);
	
	for(CMainFrame::g_mmPM_Cond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		if( it_PM->second == cond1 )
		{
			it_PM->second = cond2;
			
		}
	}
}

void CAipi_PM::printPM_Cond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory - Condition  *******"));
	//Print map container
	for( CMainFrame::g_mmPM_Cond::const_iterator iter = pMainFrame->gmmPM_Cond.begin(); iter!= pMainFrame->gmmPM_Cond.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM - Cond  *******"));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		strCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
			
	}


}


void CAipi_PM::printPM_Fact()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory - Fact  *******"));
	//Print map container
	for( CMainFrame::g_mmPM_Fact::const_iterator iter = pMainFrame->gmmPM_Fact.begin(); iter!= pMainFrame->gmmPM_Fact.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strFact =_T("F");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM - Fact  *******"));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		strFact +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strFact);
			
	}


}


void CAipi_PM::printPM_RelCond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory - Relational Condition  *******"));
	//Print map container
	for( CMainFrame::g_mmPM_RelCond::const_iterator iter = pMainFrame->gmmPM_RelCond.begin(); iter!= pMainFrame->gmmPM_RelCond.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM - RelCond  *******"));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		strCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
			
	}


}




void CAipi_PM::printPM_BM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory - Beta Memory *******"));
	//Print map container
	for( CMainFrame::g_mmPM_BM::const_iterator iter = pMainFrame->gmmPM_BM.begin(); iter!= pMainFrame->gmmPM_BM.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strBM =_T("B");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM - BM  *******"));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		strBM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
			
	}


}


void CAipi_PM::printPM_PNode()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory - Production Node *******"));
	//Print map container
	for( CMainFrame::g_mPM_PNode::const_iterator iter = pMainFrame->gmPM_PNode.begin(); iter!= pMainFrame->gmPM_PNode.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strPN =_T("PN");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM - PNode  *******"));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		strPN +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPN);
			
	}


}


void CAipi_PM::printPM_IDVar()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory  - Identifier Variables *******"));
	//Print map container
	for( CMainFrame::g_mmPM_IVar::const_iterator iter = pMainFrame->gmmPM_IVar.begin(); iter!= pMainFrame->gmmPM_IVar.end(); ++iter)
	{
		CString strPM =_T("P");
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM - ID Vars  *******"));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->second.data());
			
	}


}

void CAipi_PM::printPM_ATTRVar()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory  - Attributes Variables *******"));
	//Print map container
	for( CMainFrame::g_mmPM_AVar::const_iterator iter = pMainFrame->gmmPM_AVar.begin(); iter!= pMainFrame->gmmPM_AVar.end(); ++iter)
	{
		CString strPM =_T("P");
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM - ATTR Vars  *******"));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->second.data());
			
	}


}

void CAipi_PM::printPM_VALVar()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory  - Values Variables *******"));
	//Print map container
	for( CMainFrame::g_mmPM_VVar::const_iterator iter = pMainFrame->gmmPM_VVar.begin(); iter!= pMainFrame->gmmPM_VVar.end(); ++iter)
	{
		CString strPM =_T("P");
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM - VAL Vars  *******"));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->second.data());
			
	}


}


void CAipi_PM::printPM_IDVarIForm()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory  - Identifier Variables *******"));
	//Print map container
	for( CMainFrame::g_mmPM_IVarIForm::const_iterator iter = pMainFrame->gmmPM_IVarIForm.begin(); iter!= pMainFrame->gmmPM_IVarIForm.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strID =_T("ID_");
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM - ID Vars IForm *******"));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		strID +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strID);
		
			
	}


}

void CAipi_PM::printPM_ATTRVarIForm()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory  - Attributes Variables *******"));
	//Print map container
	for( CMainFrame::g_mmPM_AVarIForm::const_iterator iter = pMainFrame->gmmPM_AVarIForm.begin(); iter!= pMainFrame->gmmPM_AVarIForm.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strAT =_T("AT_");
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM - ATTR Vars IForm  *******"));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		strAT +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAT);
		
			
	}


}

void CAipi_PM::printPM_VALVarIForm()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory  - Values Variables *******"));
	//Print map container
	for( CMainFrame::g_mmPM_VVarIForm::const_iterator iter = pMainFrame->gmmPM_VVarIForm.begin(); iter!= pMainFrame->gmmPM_VVarIForm.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strVL =_T("VL_");
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM - VAL Vars IForm  *******"));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		strVL +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strVL);
		
			
	}


}





void CAipi_PM::printPM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory Names Info *******"));
	//Print map container
	for( CMainFrame::g_mPM::const_iterator iter = pMainFrame->gmPM.begin(); iter!= pMainFrame->gmPM.end(); ++iter)
	{
		int k = iter->first;
		tstring name = findPMName(iter->first);
		float cf = findPMCF(iter->first);
		float weight = findPMWeight(iter->first);
		
		
		CString strPM =_T("P");		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PME Name and Info *******"));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
		CString strCF;
		strCF.Format(_T("%2.2f"), cf);
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("CF : "));
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);


		CString strWeight;
		strWeight.Format(_T("%2.2f"), weight);
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("WEIGHT : "));
		pMainFrame->m_wndOutputTabView.AddMsg1(strWeight);
			
	}


	

}

/*
void CAipi_PM::printRepCondPM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Repeated Conditions Production Memory  *******"));
	//Print map container
	for( CMainFrame::g_mmRepCondPM::const_iterator iter = pMainFrame->gmmRepCondPM.begin(); iter!= pMainFrame->gmmRepCondPM.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strRepeatedCond =_T("Repeated C");

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Condition - Production  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		strRepeatedCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strRepeatedCond);
			
	}


}
*/

/*
void CAipi_PM::printPMEVector()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	int vsize = pMainFrame->g_vPME.size();

	for(int i= 0; i<vsize; ++i)
	{
		CString strPM =_T("P");

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM Element for P... *******"));
		strPM +=  _itot(pMainFrame->g_vPME.at(i) , buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);	
	}
}

*/