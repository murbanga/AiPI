// Aipi_LHS.cpp: implementation of the CAipi_LHS class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_LHS.h"

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

CAipi_LHS::CAipi_LHS()
{

}

CAipi_LHS::~CAipi_LHS()
{
	//clearLHS();
	//clearRepCond();
}


// LHS.cpp: implementation of the LHS class.
//
//////////////////////////////////////////////////////////////////////

CAipi_LHS* CAipi_LHS::addLHS(int lhs, tstring id, tstring attr, tstring val, int rel, int pm, int categ)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_LHS *pObject = new CAipi_LHS();
    try
	{
		pObject->setId(id);
		pObject->setAttr(attr);
		pObject->setVal(val);
		pObject->setRel(rel);
		pObject->setPM(pm);
		pObject->setCategory(categ);
	
		pMainFrame->gmLHS.insert(CMainFrame::g_mLHS::value_type(lhs, *pObject));
		pMainFrame->gmmPM_Cond.insert(CMainFrame::g_mmPM_Cond::value_type(pm, lhs));
		
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


CAipi_LHS* CAipi_LHS::addLHSIForm(int lhs, double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int rel, int pm, int categ)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_LHS *pObject = new CAipi_LHS();
    try
	{
		pObject->setIdIForm(id_iform);
		pObject->setAttrIForm(attr_iform);
		pObject->setValIForm(val_iform);
		pObject->setId(id);
		pObject->setAttr(attr);
		pObject->setVal(val);
		pObject->setRel(rel);
		pObject->setPM(pm);
		pObject->setCategory(categ);
	
		pMainFrame->gmLHS.insert(CMainFrame::g_mLHS::value_type(lhs, *pObject));
		pMainFrame->gmmPM_Cond.insert(CMainFrame::g_mmPM_Cond::value_type(pm, lhs));
		
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







int CAipi_LHS::editLHS(int lhs, tstring id, tstring attr, tstring val, int rel, int pm, int categ)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mLHS::iterator iterLHS;
	
	iterLHS = pMainFrame->gmLHS.find(lhs);
	if( iterLHS != pMainFrame->gmLHS.end())
	{
		eraseLHS(lhs);
		addLHS(lhs, id, attr, val, rel, pm, categ);
		return lhs;
		
	}		

return NOT_FOUND;

}


int CAipi_LHS::editLHSIForm(int lhs, double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int rel, int pm, int categ)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mLHS::iterator iterLHS;
	
	iterLHS = pMainFrame->gmLHS.find(lhs);
	if( iterLHS != pMainFrame->gmLHS.end())
	{
		eraseLHS(lhs);
		addLHSIForm(lhs, id_iform, attr_iform, val_iform, id, attr, val, rel, pm, categ);
		return lhs;
		
	}		

return NOT_FOUND;

}




int CAipi_LHS::lastLHS()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mLHS::iterator iter;
	if( !pMainFrame->gmLHS.empty())
	{
		iter = pMainFrame->gmLHS.end(); 
		--iter;
		return iter->first;
	}

	return 0;
	
}



void CAipi_LHS::clearLHS()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmLHS.clear();
}


void CAipi_LHS::eraseLHS(int lhs)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int f = findLHSMembers(lhs);
	
	if( f != NOT_FOUND )
	{
		pMainFrame->gmLHS.erase(lhs);
	}
}



double CAipi_LHS::findLHSIdIForm( int lhs )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mLHS::iterator iter;
    iter = pMainFrame->gmLHS.find(lhs);
	if( iter != pMainFrame->gmLHS.end())
	{
  		CAipi_LHS id = (CAipi_LHS)iter->second;
 		return id.getIdIForm(); 
	}
	

return NOT_FOUND;
}


double CAipi_LHS::findLHSAttrIForm( int lhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mLHS::iterator iter;
    iter = pMainFrame->gmLHS.find(lhs);
	if( iter != pMainFrame->gmLHS.end())
	{
  		CAipi_LHS attr = (CAipi_LHS)iter->second;
 		return attr.getAttrIForm(); 
	}

return NOT_FOUND;
			

}




double CAipi_LHS::findLHSValIForm( int lhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mLHS::iterator iter;
    iter = pMainFrame->gmLHS.find(lhs);
	if( iter != pMainFrame->gmLHS.end())
	{
  		CAipi_LHS val = (CAipi_LHS)iter->second;
 		return val.getValIForm();
	}

return NOT_FOUND;

}




tstring CAipi_LHS::findLHSId( int lhs )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mLHS::iterator iter;
    iter = pMainFrame->gmLHS.find(lhs);
	if( iter != pMainFrame->gmLHS.end())
	{
  		CAipi_LHS id = (CAipi_LHS)iter->second;
 		return id.getId(); 
	}
	

return _T("NOT_FOUND");
}


tstring CAipi_LHS::findLHSAttr( int lhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mLHS::iterator iter;
    iter = pMainFrame->gmLHS.find(lhs);
	if( iter != pMainFrame->gmLHS.end())
	{
  		CAipi_LHS attr = (CAipi_LHS)iter->second;
 		return attr.getAttr(); 
	}

return _T("NOT_FOUND");
			

}




tstring CAipi_LHS::findLHSVal( int lhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mLHS::iterator iter;
    iter = pMainFrame->gmLHS.find(lhs);
	if( iter != pMainFrame->gmLHS.end())
	{
  		CAipi_LHS val = (CAipi_LHS)iter->second;
 		return val.getVal();
	}

return _T("NOT_FOUND");

}

int CAipi_LHS::findLHSRel( int lhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mLHS::iterator iter;
    iter = pMainFrame->gmLHS.find(lhs);
	if( iter != pMainFrame->gmLHS.end())
	{
  		CAipi_LHS rel = (CAipi_LHS)iter->second;
 		return rel.getRel();
	}

return NOT_FOUND;

}


int CAipi_LHS::findLHSPM( int lhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mLHS::iterator iter;
    iter = pMainFrame->gmLHS.find(lhs);
	if( iter != pMainFrame->gmLHS.end())
	{
  		CAipi_LHS pm = (CAipi_LHS)iter->second;
 		return pm.getPM();
	}

return NOT_FOUND;

}


int CAipi_LHS::findLHSCategory( int lhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mLHS::iterator iter;
    iter = pMainFrame->gmLHS.find(lhs);
	if( iter != pMainFrame->gmLHS.end())
	{
  		CAipi_LHS categ = (CAipi_LHS)iter->second;
 		return categ.getCategory();
	}

return NOT_FOUND;

}



int CAipi_LHS::findLHSMembers(int lhs)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mLHS::iterator iter;
    iter = pMainFrame->gmLHS.find(lhs);
	if( iter != pMainFrame->gmLHS.end())
	{
		CAipi_LHS lhso = (CAipi_LHS)iter->second;
 	
		m_lhsId = lhso.getId();
		m_lhsAttr = lhso.getAttr();
		m_lhsVal = lhso.getVal();
		m_Rel = lhso.getRel();
		m_PM = lhso.getPM();
		m_Category = lhso.getCategory();
		

		return lhs;
	}
	
	return NOT_FOUND;
}


int CAipi_LHS::findLHSMembersIForm(int lhs)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mLHS::iterator iter;
    iter = pMainFrame->gmLHS.find(lhs);
	if( iter != pMainFrame->gmLHS.end())
	{
		CAipi_LHS lhso = (CAipi_LHS)iter->second;
 	
		m_lhsIdIForm = lhso.getIdIForm();
		m_lhsAttrIForm = lhso.getAttrIForm();
		m_lhsValIForm = lhso.getValIForm();
		m_lhsId = lhso.getId();
		m_lhsAttr = lhso.getAttr();
		m_lhsVal = lhso.getVal();
		m_Rel = lhso.getRel();
		m_PM = lhso.getPM();
		m_Category = lhso.getCategory();
		

		return lhs;
	}
	
	return NOT_FOUND;
}



int CAipi_LHS::searchFirstLHS_PMId( int pm, tstring id  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Cond.equal_range(pm);
	
	for(CMainFrame::g_mmPM_Cond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		int c = it_PM->second;
		tstring lhsId = findLHSId(c);	
		
		if(  lhsId == id )
		{
			return c;
			
		}
	}
	

return NOT_FOUND;

}


int CAipi_LHS::searchFirstLHS_PMAttr( int pm, tstring attr  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Cond.equal_range(pm);
	
	for(CMainFrame::g_mmPM_Cond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		int c = it_PM->second;
		tstring lhsAttr = findLHSAttr(c);	
		
		if(  lhsAttr == attr )
		{
			return c;
			
		}
	}
	

return NOT_FOUND;

}



int CAipi_LHS::searchFirstLHS_PMVal( int pm, tstring val  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Cond.equal_range(pm);
	
	for(CMainFrame::g_mmPM_Cond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		int c = it_PM->second;
		tstring lhsVal = findLHSVal(c);	
		
		if(  lhsVal == val )
		{
			return c;
			
		}
	}
	

return NOT_FOUND;

}


int CAipi_LHS::searchLHS_PMIdAfterCond( int pm, tstring id, int c  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Cond.equal_range(pm);
	
	for(CMainFrame::g_mmPM_Cond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		int cond = it_PM->second;
		
		if( cond == c )
		{
			continue;
		}

		tstring lhsId = findLHSId(cond);	
		
		if(  lhsId == id )
		{
			return cond;
			
		}
	}
	

return NOT_FOUND;

}




int CAipi_LHS::searchLHS_PMAttrAfterCond( int pm, tstring attr, int c  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Cond.equal_range(pm);
	
	for(CMainFrame::g_mmPM_Cond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		int cond = it_PM->second;

		if( cond == c )
		{
			continue;
		}
		
		tstring lhsAttr = findLHSAttr(cond);	
		
		if(  lhsAttr == attr )
		{
			return cond;
			
		}
	}
	

return NOT_FOUND;

}



int CAipi_LHS::searchLHS_PMValAfterCond( int pm, tstring val, int c  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Cond.equal_range(pm);
	
	for(CMainFrame::g_mmPM_Cond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		int cond = it_PM->second;

		if( cond == c )
		{
			continue;
		}
		
		tstring lhsVal = findLHSVal(cond);	
		
		if(  lhsVal == val )
		{
			return cond;
			
		}
	}
	

return NOT_FOUND;

}



int CAipi_LHS::sizeLHS()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmLHS.size();

}



int CAipi_LHS::variableTest(int lhs)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
		
	if( findLHSMembers(lhs))
	{
		 
		if((m_Id.substr(0,1) == _T("[")) && (m_Attr.substr(0,1) == _T("[")) && (m_Val.substr(0,1) != _T("[")) )
		{
			return ID_AT_K;
		}
		else if((m_Id.substr(0,1) == _T("[")) && (m_Attr.substr(0,1) != _T("[")) && (m_Val.substr(0,1) == _T("[")) )
		{	
			return ID_K_VL;
		}
		else if((m_Id.substr(0,1) == _T("[")) && (m_Attr.substr(0,1) != _T("[")) && (m_Val.substr(0,1) != _T("[")) )
		{
			return ID_K_K;
		}
		else if((m_Id.substr(0,1) != _T("[")) && (m_Attr.substr(0,1) == _T("[")) && (m_Val.substr(0,1) == _T("[")) )
		{
			return K_AT_VL;
		}
		else if((m_Id.substr(0,1) != _T("[")) && (m_Attr.substr(0,1) == _T("[")) && (m_Val.substr(0,1) != _T("[")) )
		{
			return K_AT_K;
		}
		else if((m_Id.substr(0,1) != _T("[")) && (m_Attr.substr(0,1) != _T("[")) && (m_Val.substr(0,1) == _T("[")) )
		{
			return K_K_VL;
		}
		else if ((m_Id.substr(0,1) != _T("[")) && (m_Attr.substr(0,1) != _T("[")) && (m_Val.substr(0,1) != _T("[")) )
		{	
			return K_K_K;
		}
		else
		{
			return ID_AT_VL;	
		}
	}


return 0;
}



void CAipi_LHS::SamplesAlphaNet()
{

////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 1
	//Extract from Tutorial RETE, Alpha Net - Mauricio Alfaro

/*	
	addLHS(1,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(2,_T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(3,_T("[z]") ,_T("color") ,_T("red"),  EQ; 1, ID_K_K);
	addLHS(4,_T("[a]") ,_T("color") ,_T("maize"), EQ, 1, ID_K_K);
	addLHS(5,_T("[b]") ,_T("color") ,_T("blue"), EQ, 1, ID_K_K);
	addLHS(6,_T("[c]") ,_T("color") ,_T("green"), EQ, 1, ID_K_K);
	addLHS(7,_T("[d]") ,_T("color") ,_T("white"), EQ, 1, ID_K_K);
	addLHS(8,_T("[s]") ,_T("on") ,_T("table"), EQ, 1, ID_K_K);
	addLHS(9,_T("[y]") ,_T("[a]") ,_T("[b]"), EQ, 1, ID_AT_VL);
	addLHS(10,_T("[a]") ,_T("left of") ,_T("[d]"), EQ, 1, ID_K_VL);
*/	

///////////////////////////////////////////////////////////////////////////////////////////////////////	

	//Sample 1.1
	/*	
	
	addLHS(1,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(2,_T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(3,_T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	addLHS(4,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(5,_T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(6,_T("[z]") ,_T("color") ,_T("blue"), EQ, 1, ID_K_K);
	addLHS(7,_T("[z]") ,_T("on") ,_T("table"), EQ, 1, ID_K_K);
	addLHS(8,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(9,_T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1,ID_K_VL);
	addLHS(10,_T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	addLHS(11,_T("[x]") ,_T("color") ,_T("blue"), EQ, 1, ID_K_K);
	*/
}

void CAipi_LHS::SamplesRETE()
{
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Sample No.2
	//Extract from Tutorial RETE, RETE Process - Mauricio Alfaro
	//Extract from Tutorial RETE, RETE Instantiated - Mauricio Alfaro
	//Extract from Tutorial RETE, Beta Memory - Mauricio Alfaro
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));	
	
	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1,ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1,ID_K_K);
*/


////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Sample No.2.1
	//Extract from Tutorial RETE, RETE Process - Mauricio Alfaro
	//Extract from Tutorial RETE, RETE Instantiated - Mauricio Alfaro
	//Extract from Tutorial RETE, Beta Memory - Mauricio Alfaro
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));	
	
	//Production 1
	addLHS(1, _T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(3, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1,ID_K_VL);
*/

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Sample No.2.2
	//Extract from Tutorial RETE, RETE Process - Mauricio Alfaro
	//Extract from Tutorial RETE, RETE Instantiated - Mauricio Alfaro
	//Extract from Tutorial RETE, Beta Memory - Mauricio Alfaro
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));	
	
	//Production 1
	addLHS(1, _T("[z]") ,_T("color") ,_T("red"), EQ, 1,ID_K_K);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(3, _T("block1") ,_T("on") ,_T("[z]"), EQ, 1, K_K_VL);
*/

////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Sample No.2.3
	//Extract from Tutorial RETE, RETE Instantiated - Mauricio Alfaro
	//Extract from Tutorial RETE, Beta Memory - Mauricio Alfaro

	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));	
	
	//Production 1
	addLHS(1, _T("block1") ,_T("on") ,_T("[y]"), EQ, 1,K_K_VL);
	addLHS(2, _T("block2") ,_T("on") ,_T("[y]"), EQ, 1, K_K_VL);
	


//////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 3.0
	//Extract from Tutorial RETE, RETE Comunication - Mauricio Alfaro
	//Extract from Tutorial RETE, RETE Instantiated - Mauricio Alfaro
	//Extract from Tutorial RETE, Beta Memory - Mauricio Alfaro
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	pm.addPM_Name(3,_T("Reglas 03"));


	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);

	
	//Production 2
	addLHS(4, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 2, ID_K_VL);
	addLHS(5, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 2, ID_K_VL);
	addLHS(6, _T("[z]") ,_T("color") ,_T("blue"), EQ, 2, ID_K_K);
	addLHS(7, _T("[z]") ,_T("on") ,_T("table"), EQ, 2, ID_K_K);


	//Production 3
	addLHS(8, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 3, ID_K_VL);
	addLHS(9, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 3, ID_K_VL );
	addLHS(10, _T("[z]") ,_T("color") ,_T("blue"), EQ, 3, ID_K_K);
	addLHS(11, _T("[z]") ,_T("color") ,_T("red"), EQ, 3, ID_K_K);
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 3.01
	//Extract from Tutorial RETE, RETE Comunication - Mauricio Alfaro
	//Extract from Tutorial RETE, RETE Instantiated - Mauricio Alfaro
	//Extract from Tutorial RETE, Beta Memory - Mauricio Alfaro
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	pm.addPM_Name(3,_T("Reglas 03"));


	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);

	
	//Production 2
	addLHS(4, _T("[a]") ,_T("on") ,_T("[b]"), EQ, 2, ID_K_VL);
	addLHS(5, _T("[b]") ,_T("left of") ,_T("[c]"), EQ, 2, ID_K_VL);
	addLHS(6, _T("[c]") ,_T("color") ,_T("blue"), EQ, 2, ID_K_K);
	addLHS(7, _T("[c]") ,_T("on") ,_T("table"), EQ, 2, ID_K_K);


	//Production 3
	addLHS(8, _T("[i]") ,_T("on") ,_T("[j]"), EQ, 3, ID_K_VL);
	addLHS(9, _T("[j]") ,_T("left of") ,_T("[k]"), EQ, 3, ID_K_VL );
	addLHS(10, _T("[k]") ,_T("color") ,_T("blue"), EQ, 3, ID_K_K);
	addLHS(11, _T("[k]") ,_T("color") ,_T("red"), EQ, 3, ID_K_K);
*/




////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 3.1
	//Different ordering rules
	//Extract from Tutorial RETE, RETE Comunication - Mauricio Alfaro
/*	
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	pm.addPM_Name(3,_T("Reglas 03"));


	//Production 1
	addLHS(1, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(2, _T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	addLHS(3, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);


	
	//Production 2
	addLHS(4, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 2, ID_K_VL);
	addLHS(5, _T("[z]") ,_T("color") ,_T("blue"), EQ, 2, ID_K_K);
	addLHS(6, _T("[z]") ,_T("on") ,_T("table"), EQ, 2, ID_K_K);
	addLHS(7, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 2, ID_K_VL);
	


	//Production 3
	addLHS(8, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 3, ID_K_VL);
	addLHS(9, _T("[z]") ,_T("color") ,_T("blue"), EQ, 3, ID_K_K);
	addLHS(10, _T("[z]") ,_T("color") ,_T("red"), EQ, 3, ID_K_K);
	addLHS(11, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 3, ID_K_VL);
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 3.1
	
/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	pm.addPMEName(2,_T("Reglas 02"));
	pm.addPMEName(3,_T("Reglas 03"));

	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("block2") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);


	//Production 2
	addLHSE(4,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHSE(5,_T("block3") ,_T("left of") ,_T("[z]"), EQ, 2);
	addLHSE(6,_T("[z]") ,_T("color") ,_T("blue"), EQ, 2);
	addLHSE(7,_T("[z]") ,_T("on") ,_T("table"), EQ,2);

  //Production 3
	addLHSE(8,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 3);
	addLHSE(9,_T("block2") ,_T("left of") ,_T("[z]"), EQ, 3);
	addLHSE(10,_T("[z]") ,_T("color") ,_T("blue"), EQ, 3);
	addLHSE(11,_T("[z]") ,_T("color") ,_T("red"), EQ, 3);
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Sample 3.2
/*

	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	pm.addPM_Name(3,_T("Reglas 03"));

	
	//Production 1
	addLHS(1,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2,_T("block2") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHS(3,_T("[z]") ,_T("color") ,_T("red"), EQ, 1);


	//Production 2
	addLHS(10,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHS(20,_T("block2") ,_T("left of") ,_T("[z]"), EQ, 2);
	addLHS(40,_T("[z]") ,_T("color") ,_T("blue"), EQ, 2);
	addLHS(50,_T("[z]") ,_T("on") ,_T("table"), EQ, 2);

	//Production 3
	addLHS(100,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 3);
	addLHS(200,_T("block2") ,_T("left of") ,_T("[z]"), EQ, 3);
	addLHS(400,_T("[z]") ,_T("color") ,_T("blue"), EQ, 3);
	addLHS(300,_T("[z]") ,_T("color") ,_T("red"), EQ, 3);
*/
	
/////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 3.3

/*
  
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	pm.addPM_Name(3,_T("Reglas 03"));

	
	//Production 1
	addLHS(3,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2,_T("block2") ,_T("left of") ,_T("block3"), EQ, 1);
	addLHS(1,_T("[z]") ,_T("color") ,_T("red"), EQ, 1);


	//Production 2
	addLHS(30,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHS(20,_T("block2") ,_T("left of") ,_T("block3"), EQ, 2);
	addLHS(40,_T("[z]") ,_T("color") ,_T("blue"), EQ, 2);
	addLHS(50,_T("[z]") ,_T("on") ,_T("table"), EQ, 2);

	//Production 3
	addLHS(300,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 3);
	addLHS(200,_T("block2") ,_T("left of") ,_T("block3"), EQ, 3);
	addLHS(400,_T("[z]") ,_T("color") ,_T("blue"), EQ, 3);
	addLHS(100,_T("[z]") ,_T("color") ,_T("red"), EQ, 3);
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////


  	//Sample 3.4
	
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	pm.addPM_Name(3,_T("Reglas 03"));

	
	//Production 1
	addLHS(1,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2,_T("block2") ,_T("left of") ,_T("block3"), EQ, 1);
	addLHS(3,_T("[z]") ,_T("color") ,_T("red"), EQ, 1);


	//Production 2
	addLHS(10,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHS(20,_T("block2") ,_T("left of") ,_T("block3"), EQ, 2);
	addLHS(40,_T("[z]") ,_T("color") ,_T("blue"), EQ, 2);
	addLHS(50,_T("[z]") ,_T("on") ,_T("table"), EQ, 2);

	//Production 3
	addLHS(100,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 3);
	addLHS(200,_T("block2") ,_T("left of") ,_T("block3"), EQ, 3);
	addLHS(400,_T("[z]") ,_T("color") ,_T("blue"), EQ, 3);
	addLHS(300,_T("[z]") ,_T("color") ,_T("red"), EQ, 3);
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Sample 3.5

/*

  	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	pm.addPM_Name(3,_T("Reglas 03"));

	
	//Production 1
	addLHS(1,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2,_T("block2") ,_T("left of") ,_T("block3"), EQ, 1);
	addLHS(3,_T("block3") ,_T("color") ,_T("red"), EQ, 1);


	//Production 2
	addLHS(10,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHS(20,_T("block2") ,_T("left of") ,_T("block3"), EQ, 2);
	addLHS(40,_T("[z]") ,_T("color") ,_T("blue"), EQ, 2);
	addLHS(50,_T("[z]") ,_T("on") ,_T("table"), EQ, 2);

	//Production 3
	addLHS(100,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 3);
	addLHS(200,_T("block2") ,_T("left of") ,_T("block3"), EQ, 3);
	addLHS(400,_T("[z]") ,_T("color") ,_T("blue"), EQ, 3);
	addLHS(300,_T("block3") ,_T("color") ,_T("red"), EQ, 3);
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Sample 3.6

/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	//pm.addPM_Name(2,_T("Reglas 02"));
	//pm.addPM_Name(3,_T("Reglas 03"));

	
	//Production 1
	addLHS(1,_T("block1") ,_T("on") ,_T("block2"), EQ, 1, K_K_K);
	addLHS(2,_T("block2") ,_T("left of") ,_T("block3"), EQ, 1, K_K_K);
	addLHS(3,_T("block3") ,_T("color") ,_T("red"), EQ, 1, K_K_K);


	//Production 2
	addLHS(10,_T("block1") ,_T("on") ,_T("block2"), EQ, 2, K_K_K);
	addLHS(20,_T("block2") ,_T("left of") ,_T("block3"), EQ, 2, K_K_K);
	addLHS(40,_T("[z]") ,_T("color") ,_T("blue"), EQ, 2, ID_K_K);
	addLHS(50,_T("[z]") ,_T("on") ,_T("table"), EQ, 2, ID_K_K);

	//Production 3
	addLHS(100,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 3, ID_K_VL);
	addLHS(200,_T("block2") ,_T("left of") ,_T("block3"), EQ, 3, K_K_K);
	addLHS(400,_T("[z]") ,_T("color") ,_T("blue"), EQ, 3, ID_K_K);
	addLHS(300,_T("block3") ,_T("color") ,_T("red"), EQ, 3, ID_K_K);
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 3.7
/*
  	
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	pm.addPM_Name(3,_T("Reglas 03"));

	
	//Production 1
	addLHS(1,_T("block1") ,_T("on") ,_T("block2"), EQ, 1);
	addLHS(2,_T("block2") ,_T("left of") ,_T("block3"), EQ, 1);
	addLHS(3,_T("block3") ,_T("color") ,_T("red"), EQ, 1);


	//Production 2
	addLHS(10,_T("block1") ,_T("on") ,_T("block3"), EQ, 2);
	addLHS(20,_T("block3") ,_T("left of") ,_T("block4"), EQ, 2);
	addLHS(40,_T("block4") ,_T("color") ,_T("blue"), EQ,2);
	addLHS(50,_T("block4") ,_T("on") ,_T("table"), EQ,2);

	//Production 3
	addLHS(100"),_T("block2") ,_T("on") ,_T("table"), EQ, 3);
	addLHS(200"),_T("block2") ,_T("color") ,_T("blue"), EQ, 3);
	addLHS(400"),_T("block2") ,_T("left of") ,_T("block3"), EQ, 3);
	addLHS(300"),_T("block2") ,_T("on") ,_T("table"), EQ, 3);
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 3.8

 /* 	
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	
	
	//Production 1
	addLHS(1,_T("block1") ,_T("on") ,_T("block2"), EQ, 1, K_K_K);
	addLHS(2,_T("block2") ,_T("left of") ,_T("block3"), EQ, 1, K_K_K);
	addLHS(3,_T("block3") ,_T("color") ,_T("red"), EQ, 1, K_K_K);
	addLHS(4,_T("block1") ,_T("on") ,_T("block3"), EQ, 1, K_K_K);
	addLHS(5,_T("block3") ,_T("left of") ,_T("block4"), EQ, 1, K_K_K);
	addLHS(6,_T("block4") ,_T("color") ,_T("blue"), EQ, 1, K_K_K);
	addLHS(7,_T("block4") ,_T("on") ,_T("table"), EQ, 1, K_K_K);
	addLHS(8,_T("block4") ,_T("on") ,_T("table"), EQ, 1, K_K_K);
	addLHS(9,_T("block2") ,_T("left of") ,_T("block3"), EQ, 1, K_K_K);

  */
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Sample 4.0
	//Extract from Tutorial RETE, RETE Samples - Mauricio Alfaro
	//Extract from RETE Sample Process Structures - Mauricio Alfaro
/*	
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	pm.addPM_Name(3,_T("Reglas 03"));
	pm.addPM_Name(4,_T("Reglas 04"));
		
	
	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("blue"), EQ, 1, ID_K_K);
	addLHS(4, _T("[z]") ,_T("on") ,_T("table"), EQ, 1, ID_K_K);

	//Production 2
	addLHS(5, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 2, ID_K_VL);
	addLHS(6, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 2, ID_K_VL);
	addLHS(7, _T("[z]") ,_T("color") ,_T("blue"), EQ, 2, ID_K_K);
	addLHS(8, _T("[z]") ,_T("color") ,_T("red"), EQ, 2, ID_K_K);


	//Production 3
	addLHS(9,  _T("[x]") ,_T("color") ,_T("blue"), EQ, 3, ID_K_K);
	addLHS(10, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 3, ID_K_VL);
	addLHS(11, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 3, ID_K_VL);
	
	//Production 4
	addLHS(12, _T("[x]") ,_T("color") ,_T("blue"), EQ, 4, ID_K_K);
	addLHS(13, _T("[x]") ,_T("left of") ,_T("[y]"), EQ, 4, ID_K_VL);
	addLHS(14, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 4, ID_K_VL);
*/

	
/////////////////////////////////////////////////////////////////////////////////


	//Sample 4.1
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	pm.addPM_Name(3,_T("Reglas 03"));
	pm.addPM_Name(4,_T("Reglas 04"));
	pm.addPM_Name(5,_T("Reglas 05"));
	
	
	
	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("blue"), EQ, 1, ID_K_K);
	addLHS(4, _T("[z]") ,_T("on") ,_T("table"), EQ, 1, ID_K_K);

	//Production 2
	addLHS(5, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 2, ID_K_VL);
	addLHS(6, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 2, ID_K_VL);
	addLHS(7, _T("[z]") ,_T("color") ,_T("blue"), EQ, 2, ID_K_K);
	addLHS(8, _T("[z]") ,_T("color") ,_T("red"), EQ, 2, ID_K_K);


	//Production 3
	addLHS(9,  _T("[x]") ,_T("color") ,_T("blue"), EQ, 3, ID_K_K);
	addLHS(10, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 3, ID_K_VL);
	addLHS(11, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 3, ID_K_VL);
	
	//Production 4
	addLHS(12, _T("[x]") ,_T("color") ,_T("blue"), EQ, 4, ID_K_K);
	addLHS(13, _T("[x]") ,_T("left of") ,_T("[y]"), EQ, 4, ID_K_VL);
	addLHS(14, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 4, ID_K_VL);

	

	//Production 5
	addLHS(15, _T("[x]") ,_T("up") ,_T("[y]"), EQ, 5, ID_K_VL);
	addLHS(16, _T("[y]") ,_T("right of") ,_T("[z]"), EQ, 5,ID_K_VL);
	addLHS(17, _T("[z]") ,_T("size") ,_T("10"), ET, 5, ID_K_K);
*/


}


void CAipi_LHS::SamplesDuplicateAttr()
{
///////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	//Sample 5.0
	//Duplicate Tokens
	//Extract from Ph.Thesis Chapter 2.6

/*	
	
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	addLHS(1,_T("[x]") ,_T("self") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(2,_T("[x]") ,_T("color") ,_T("red"),EQ,  1, ID_K_K);
	addLHS(3,_T("[y]") ,_T("color") ,_T("red"),EQ,  1, ID_K_K);
*/	
///////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////

/*	
	//Sample 5.10
		
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	addLHS(1,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(2,_T("[z]") ,_T("left of") ,_T("[y]"),EQ,  1, ID_K_VL);
	addLHS(3,_T("[y]") ,_T("color") ,_T("red"),EQ,  1, ID_K_K);

 */ 
///////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////

/*	
	//Sample 5.11
		
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	addLHS(1,_T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(2,_T("[z]") ,_T("left of") ,_T("[y]"),EQ,  1, ID_K_VL);
	addLHS(3,_T("[v]") ,_T("color") ,_T("red"),EQ,  1, ID_K_K);
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	//Sample 6
	//Extract from Tutorial RETE, RETE Samples - Mauricio Alfaro
/*	
	
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHS(3, _T("[z]") ,_T("color") ,_T("blue"), EQ, 1);
	addLHS(4, _T("[z]") ,_T("on") ,_T("table"), EQ, 1);


*/	


////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 6.1
	//Extract from Tutorial RETE, RETE Samples - Mauricio Alfaro
	
/*	
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	//Production 1
	addLHS(1, _T("[z]") ,_T("on") ,_T("table"), EQ, 1, ID_K_K);
	addLHS(2, _T("[z]") ,_T("color") ,_T("blue"), EQ, 1, ID_K_K);
	addLHS(3, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(4, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1,   ID_K_VL);
*/


///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 7, 8, 10 
//Extract from Tutorial RETE, RETE Samples - Mauricio Alfaro
//Extract from Tutorial RETE, Removals of WME's - Mauricio Alfaro
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*

	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	
	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1,ID_K_K);
	addLHS(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1, ID_K_VL);
	addLHS(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1, ID_K_K);

*/



}


void CAipi_LHS::SamplesConstantAttr()
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 6.11 
	//Constant Conditions	


  /*	
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
		
	
	//Production 1
	addLHS(1, _T("block1") ,_T("color") ,_T("red"), EQ, 1, K_K_K);
	addLHS(2, _T("block3") ,_T("color") ,_T("red"), EQ, 1, K_K_K);
	addLHS(3, _T("block1") ,_T("on") ,_T("block2"), EQ, 1, K_K_K);
	
	//Production 2
	addLHS(4, _T("block1") ,_T("color") ,_T("red"), EQ, 2, K_K_K);
	addLHS(5, _T("block3") ,_T("color") ,_T("red"), EQ, 2, K_K_K);
	addLHS(6, _T("block1") ,_T("on") ,_T("block2"), EQ, 2, K_K_K);
*/


}


void CAipi_LHS::SamplesBlockWord()
{

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Blocks World
//Sample 1

/*
	CAipi_PM pm;
	pm.addPM_Name(0,_T("Reglas 01"));
	pm.addPM_Name(1,_T("Reglas 02"));
	pm.addPM_Name(2,_T("Reglas 03"));
	pm.addPM_Name(3,_T("Reglas 04"));
	pm.addPM_Name(4,_T("Reglas 05"));
	
	
	//Production 0
	//Goal Rule
	
	addLHS(1, _T("block_c") ,_T("on") ,_T("block_e"),	EQ, 1, K_K_K);
	addLHS(2, _T("block_e") ,_T("on") ,_T("floor"),	EQ, 1, K_K_K);
	

  //Production 1
  //Move Directly
	addLHS(3, _T("goal") ,_T("is") ,_T("move block directly"),	EQ, 2, K_K_K);
	addLHS(4, _T("[upper]") ,_T("is a") ,_T("block"),	EQ, 2, ID_K_K);
	addLHS(5, _T("[lower]") ,_T("is a") ,_T("block"),	EQ, 2, ID_K_K);
	addLHS(6, _T("[stack]") ,_T("is a") ,_T("stack"),	EQ, 2, ID_K_K);
	addLHS(7, _T("[upper]") ,_T("top") ,_T("[stack]"),	EQ, 2, ID_K_VL);
	addLHS(8, _T("[lower]") ,_T("top") ,_T("[stack]"),	EQ, 2, ID_K_VL);


  //Production 2
  //Clear Upper Block
	addLHS(9, _T("goal") ,_T("is") ,_T("move block"),	EQ, 3, K_K_K);
	addLHS(10, _T("[x]") ,_T("is a") ,_T("block"),	EQ, 3, ID_K_K);
	addLHS(11, _T("[upper]") ,_T("is a") ,_T("block"),	EQ, 3, ID_K_K);
	addLHS(12, _T("[stack]") ,_T("is a") ,_T("stack"),	EQ, 3, ID_K_K);
	addLHS(13, _T("[x]") ,_T("top") ,_T("[stack]"),	EQ, 3, ID_K_VL);
	addLHS(14, _T("[upper]") ,_T("on") ,_T("[x]"),	EQ, 3, ID_K_VL);

	//Production 3
	//Clear Lower Block
	addLHS(15, _T("goal") ,_T("is") ,_T("move other block"),	EQ, 4, K_K_K);
	addLHS(16, _T("[x]") ,_T("is a") ,_T("block"),	EQ, 4, ID_K_K);
	addLHS(17, _T("[upper]") ,_T("is a") ,_T("block"),	EQ, 4, ID_K_K);
	addLHS(18, _T("[stack]") ,_T("is a") ,_T("stack"),	EQ, 4, ID_K_K);
	addLHS(19, _T("[x]") ,_T("top") ,_T("[stack]"),	EQ, 4, ID_K_VL);
	addLHS(20, _T("[upper]") ,_T("on") ,_T("[x]"),	EQ, 4, ID_K_VL);


	//Production 4
	//Move Block to Floor
	addLHS(21, _T("goal") ,_T("is") ,_T("move block to floor"),	EQ, 5, K_K_K);
	addLHS(22, _T("[upper]") ,_T("is a") ,_T("block"),	EQ, 5, ID_K_K);
	addLHS(23, _T("[stack]") ,_T("is a") ,_T("stack"),	EQ, 5, ID_K_K);
	addLHS(24, _T("[upper]") ,_T("top") ,_T("[stack]"),	EQ, 5, ID_K_VL);
*/
	

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Blocks World
//Move Block to the Floor
//Sample 4.0

/*
	CAipi_PM pm;
	pm.addPM_Name(4,_T("Reglas 04"));
	
	
	
	//Production 4
	//Move Block to Floor
	addLHS(1, _T("goal") ,_T("is") ,_T("move block to floor"),	EQ, 5, K_K_K);
	addLHS(2, _T("[upper]") ,_T("is a") ,_T("block"),	EQ, 5, ID_K_K);
	addLHS(3, _T("[stack]") ,_T("is a") ,_T("stack"),	EQ, 5, ID_K_K);
	addLHS(4, _T("[upper]") ,_T("top") ,_T("[stack]"),	EQ, 5, ID_K_VL);
*/

	
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Blocks World
//Move Block to the Floor 
//Sample 4.1

/*
	CAipi_PM pm;
	pm.addPM_Name(4,_T("Reglas 04"));
	
	
	
	//Production 4
	//Move Block to Floor
	addLHS(1, _T("goal") ,_T("is") ,_T("move block to floor"),	EQ, 5, K_K_K);
	addLHS(2, _T("[upper]") ,_T("is a") ,_T("block"),	EQ, 5, ID_K_K);
	addLHS(3, _T("[stack]") ,_T("is a") ,_T("stack"),	EQ, 5, ID_K_K);
	addLHS(4, _T("[upper]") ,_T("belong") ,_T("[stack]"),	EQ, 5, ID_K_VL);
	addLHS(5, _T("[upper]") ,_T("top") ,_T("[stack]"),	EQ, 5, ID_K_VL);
*/
	
//////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Blocks World
//Move Block Directly
//Sample 1.0
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	
	
	//Production 1
  //Move Directly
	addLHS(1, _T("goal") ,_T("is") ,_T("move block directly"),	EQ, 1, K_K_K);
	addLHS(2, _T("[upper]") ,_T("is a") ,_T("block"),	EQ, 1, ID_K_K);
	addLHS(3, _T("[lower]") ,_T("is a") ,_T("block"),	EQ, 1, ID_K_K);
	addLHS(4, _T("[stack]") ,_T("is a") ,_T("stack"),	EQ, 1, ID_K_K);
	addLHS(5, _T("[upper]") ,_T("top") ,_T("[stack]"),	EQ, 1, ID_K_VL);
	addLHS(6, _T("[lower]") ,_T("top") ,_T("[stack]"),	EQ, 1, ID_K_VL);
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Blocks World
//Move Upper Block 
//Sample 2.0
/*
	CAipi_PM pm;
	pm.addPM_Name(2,_T("Reglas 02"));
	
	
	//Production 1
  //Move Directly
	addLHS(1, _T("goal") ,_T("is") ,_T("move block"),	EQ, 2, K_K_K);
	addLHS(2, _T("[upper]") ,_T("is a") ,_T("block"),	EQ, 2, ID_K_K);
	addLHS(3, _T("[x]") ,    _T("is a") ,_T("block"),	EQ, 2, ID_K_K);
	addLHS(4, _T("[stack]") ,_T("is a") ,_T("stack"),	EQ, 2, ID_K_K);
	addLHS(5, _T("[x]")		,_T("top") ,_T("[stack]"),	EQ, 2, ID_K_K);
	addLHS(6, _T("[upper]") ,_T("on") , _T("[x]"),		EQ, 2, ID_K_VL);
*/

}



void CAipi_LHS::SamplesPumpingStation()
{
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample Pumping Station
//Sample 1
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Rule 01"));
	
	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	op.addAttr_Type(_T("nominal pressure"), AIPI_I);
	

	//Production 1
	addLHS(1, _T("[line]") ,_T("is a") ,_T("line"),	EQ, 1, ID_K_K);
	addLHS(2, _T("[line]") ,_T("current pressure") ,_T("[x]"), AS, 1, ID_K_VL);
	addLHS(3, _T("[line]") ,_T("nominal pressure") ,_T("[y]"), AS, 1, ID_K_VL);
	addLHS(4, _T("[x]") ,_T("LT") ,_T("[y]"),	LT, 1, ID_RO_VL);
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample Pumping Station
//Sample 1.1
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Rule 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	op.addAttr_Type(_T("nominal pressure"), AIPI_I);
	

	//Production 1
	addLHS(1, _T("[line]") ,_T("is a") ,_T("line"),	EQ, 1, ID_K_K);
	addLHS(2, _T("[line]") ,_T("current pressure") ,_T("[x]"), AS, 1, ID_K_VL);
	addLHS(3, _T("[line]") ,_T("nominal pressure") ,_T("[y]"), AS, 1, ID_K_VL);
	addLHS(4, _T("[x]") ,_T("GT") ,_T("[y]"),	GT, 1, ID_RO_VL);		
*/




////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample Pumping Station
//Sample 1.2
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Rule 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	op.addAttr_Type(_T("nominal pressure"), AIPI_I);
	

	//Production 1
	addLHS(1, _T("[line]") ,_T("is a") ,_T("line"),	EQ, 1, ID_K_K);
	addLHS(2, _T("[line]") ,_T("current pressure") ,_T("[x]"), AS, 1, ID_K_VL);
	addLHS(3, _T("[line]") ,_T("nominal pressure") ,_T("[y]"), AS, 1, ID_K_VL);
	addLHS(4, _T("[x]") ,_T("ET") ,_T("[y]"), ET, 1, ID_RO_VL);
	addLHS(5, _T("[x]") ,_T("GT") ,_T("[y]"),	GT, 1, ID_RO_VL);		
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample Pumping Station
//Sample 1.21
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Rule 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	op.addAttr_Type(_T("nominal pressure"), AIPI_I);
	op.addAttr_Type(_T("is a"), AIPI_S);
	

	//Production 1
	addLHS(1, _T("[line]") ,_T("is a") ,_T("line"),	EQ, 1, ID_K_K);
	addLHS(2, _T("[line]") ,_T("is a") ,_T("[z]"),	AS, 1, ID_K_VL);
	addLHS(3, _T("[line]") ,_T("current pressure") ,_T("[x]"), AS, 1, ID_K_VL);
	addLHS(4, _T("[line]") ,_T("nominal pressure") ,_T("[y]"), AS, 1, ID_K_VL);
	addLHS(5, _T("[line]") ,_T("ET") ,_T("[z]"), ET, 1, ID_RO_VL);
	addLHS(6, _T("[x]") ,_T("GT") ,_T("[y]"),	GT, 1, ID_RO_VL);		
*/
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample Pumping Station
//Sample 1.3
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Rule 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	op.addAttr_Type(_T("nominal pressure"), AIPI_I);
	

	//Production 1
	addLHS(1, _T("[line]") ,_T("is a") ,_T("line"),	EQ, 1, ID_K_K);
	addLHS(2, _T("[line]") ,_T("current pressure") ,_T("[x]"), AS, 1, ID_K_VL);
	addLHS(3, _T("[line]") ,_T("nominal pressure") ,_T("[y]"), AS, 1, ID_K_VL);
	addLHS(4, _T("[line]") ,_T("is a") ,_T("[z]"), AS, 1, ID_K_VL);
	addLHS(5, _T("[x]") ,_T("GT") ,_T("[y]"),	GT, 1, ID_RO_VL);		
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample Pumping Station
//Sample 1.4
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Rule 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	op.addAttr_Type(_T("nominal pressure"), AIPI_I);
	op.addAttr_Type(_T("is a"), AIPI_S);
	

	//Production 1
	addLHS(1, _T("[line]") ,_T("is a") ,_T("line"),	EQ, 1, ID_K_K);
	addLHS(2, _T("[line]") ,_T("current pressure") ,_T("[x]"), AS, 1, ID_K_VL);
	addLHS(3, _T("[line]") ,_T("nominal pressure") ,_T("[y]"), AS, 1, ID_K_VL);
	addLHS(4, _T("[line]") ,_T("is a") ,_T("[z]"), AS, 1, ID_K_VL);
	addLHS(5, _T("[z]") ,_T("ET") ,_T("line"),	ET, 1, ID_RO_K);
*/			
	
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample Pumping Station
//Sample 1.5
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Rule 01"));
	
	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	

	//Production 1
	addLHS(1, _T("[line]") ,_T("is a") ,_T("line"),	EQ, 1, ID_K_K);
	addLHS(2, _T("[line]") ,_T("current pressure") ,_T("[x]"), AS, 1, ID_K_VL);
	addLHS(3, _T("[line]") ,_T("current pressure") ,_T("[y]"), AS, 1, ID_K_VL);
	addLHS(4, _T("[x]") ,_T("LT") ,_T("[y]"),	LT, 1, ID_RO_VL);
*/


////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample Pumping Station
//Sample 2
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Rule 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	op.addAttr_Type(_T("nominal pressure"), AIPI_I);
	op.addAttr_Type(_T("color"), AIPI_S);
	

	//Production 1
	addLHS(1, _T("[line]") ,_T("is a") ,_T("line"),	EQ, 1, ID_K_K);
	addLHS(2, _T("[line]") ,_T("current pressure") ,_T("[x]"), AS, 1, ID_K_VL);
	addLHS(3, _T("[line]") ,_T("nominal pressure") ,_T("[y]"), AS, 1, ID_K_VL);
	addLHS(4, _T("[line]") ,_T("color") ,_T("[z]"),AS, 1, ID_K_VL);
	addLHS(5, _T("[z]") ,_T("ET") ,_T("red"), ET, 1, ID_RO_K);
	addLHS(6, _T("[x]") ,_T("LT") ,_T("[y]"),	LT, 1, ID_RO_VL);
*/	

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample Pumping Station
//Sample 2.1
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Rule 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	op.addAttr_Type(_T("nominal pressure"), AIPI_I);
	op.addAttr_Type(_T("color"), AIPI_S);
	

	//Production 1
	addLHS(1, _T("[line]") ,_T("is a") ,_T("line"),	EQ, 1, ID_K_K);
	addLHS(2, _T("[line]") ,_T("current pressure") ,_T("[x]"), AS, 1, ID_K_VL);
	addLHS(3, _T("[line]") ,_T("nominal pressure") ,_T("[y]"), AS, 1, ID_K_VL);
	addLHS(4, _T("[line]") ,_T("color") ,_T("[z]"),AS, 1, ID_K_VL);
	addLHS(5, _T("[z]") ,_T("ET") ,_T("red"), ET, 1, ID_RO_K);
	addLHS(6, _T("[y]") ,_T("LT") ,_T("[x]"),	LT, 1, ID_RO_VL);
*/
	
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample Pumping Station
//Sample 2.2
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Rule 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	op.addAttr_Type(_T("nominal pressure"), AIPI_I);


	//Production 1
	addLHS(1, _T("[line]") ,_T("is a") ,_T("line"),	EQ, 1, ID_K_K);
	addLHS(2, _T("[line]") ,_T("current pressure") ,_T("[x]"), AS, 1, ID_K_VL);
	addLHS(3, _T("[line]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	addLHS(4, _T("[line]") ,_T("nominal pressure") ,_T("[y]"), AS, 1, ID_K_VL);
	addLHS(5, _T("[y]") ,_T("LT") ,_T("[x]"),	LT, 1, ID_RO_VL);
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample Pumping Station
//Sample 3
//Production 
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Rule 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	op.addAttr_Type(_T("nominal pressure"), AIPI_I);
	

	//Production 1
	addLHS(1, _T("[block]") ,_T("is a") ,_T("block"),	EQ, 1, ID_K_K);
	addLHS(2, _T("[block]") ,_T("input line is") ,_T("[x]"), EQ, 1, ID_K_VL);
	addLHS(3, _T("[block]") ,_T("output line is") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(4, _T("[x]") ,_T("pressure status") ,_T("normal"), EQ, 1, ID_K_K);
	addLHS(5, _T("[y]") ,_T("pressure status") ,_T("low"), AS, 1, ID_K_K);
	
*/		
	

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample Pumping Station
//Sample 4
//Production 

/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Rule 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("nominal current"), AIPI_I);
	
	

	//Production 1
	addLHS(1, _T("[block]") ,_T("is a") ,_T("block"),	EQ, 1, ID_K_K);
	addLHS(2, _T("[block]") ,_T("status is") ,_T("bad"), EQ, 1, ID_K_K);
	addLHS(3, _T("[block]") ,_T("motor is") ,_T("[motor]"), AS, 1, ID_K_VL);
	addLHS(4, _T("[motor]") ,_T("nominal current") ,_T("1"), ET, 1, ID_K_K);
	addLHS(5, _T("[motor]") ,_T("status is") ,_T("bad"), EQ, 1, ID_K_K);
*/	
	


////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample Pumping Station
//Sample 8
/*
	CAipi_PM pm;
	pm.addPM_Name(8,_T("Rule 08"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	
	
	//Production 8
	addLHS(1, _T("[block]") ,_T("is a") ,_T("block"),	EQ, 8, ID_K_K);
	addLHS(2, _T("[block]") ,_T("pump is") ,_T("[pump]"), EQ, 8, ID_K_VL);
	addLHS(3, _T("[block]") ,_T("input line is") ,_T("[iline]"), EQ, 8, ID_K_VL);
	addLHS(4, _T("[block]") ,_T("output line is") ,_T("[oline]"), EQ, 8, ID_K_VL);
	addLHS(5, _T("[block]") ,_T("status is") ,_T("bad"), EQ, 8, ID_K_K);
	addLHS(6, _T("[iline]") ,_T("current pressure") ,_T("[x]"), AS, 8, ID_K_VL);
	addLHS(7, _T("[oline]") ,_T("current pressure") ,_T("[y]"), AS, 8, ID_K_VL);
	addLHS(8, _T("[x]") ,_T("LT") ,_T("[y]"), LT, 8, ID_RO_VL);
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample Pumping Station
//Sample 8.01
/*
	CAipi_PM pm;
	pm.addPM_Name(8,_T("Rule 08"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	
	
	//Production 8
	addLHS(1, _T("[block]") ,_T("is a") ,_T("block"),	EQ, 8, ID_K_K);
	addLHS(2, _T("[block]") ,_T("pump is") ,_T("[pump]"), EQ, 8, ID_K_VL);
	addLHS(3, _T("[block]") ,_T("input line is") ,_T("[iline]"), EQ, 8, ID_K_VL);
	addLHS(4, _T("[block]") ,_T("output line is") ,_T("[oline]"), EQ, 8, ID_K_VL);
	addLHS(5, _T("[block]") ,_T("status is") ,_T("bad"), EQ, 8, ID_K_K);
	addLHS(6, _T("[iline]") ,_T("current pressure") ,_T("[x]"), AS, 8, ID_K_VL);
	addLHS(7, _T("[oline]") ,_T("current pressure") ,_T("[y]"), AS, 8, ID_K_VL);
	addLHS(8, _T("[y]") ,_T("GT") ,_T("[x]"), GT, 8, ID_RO_VL);
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample Pumping Station
//Sample 8.02
//Production different order 

/*
	CAipi_PM pm;
	pm.addPM_Name(8,_T("Rule 08"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("current pressure"), AIPI_I);
	
	
	//Production 8
	addLHS(1, _T("[block]") ,_T("is a") ,_T("block"),	EQ, 8, ID_K_K);
	addLHS(2, _T("[block]") ,_T("status is") ,_T("bad"), EQ, 8, ID_K_K);
	addLHS(3, _T("[block]") ,_T("pump is") ,_T("[pump]"), EQ, 8, ID_K_VL);
	addLHS(4, _T("[block]") ,_T("input line is") ,_T("[iline]"), EQ, 8, ID_K_VL);
	addLHS(5, _T("[block]") ,_T("output line is") ,_T("[oline]"), EQ, 8, ID_K_VL);
	addLHS(6, _T("[iline]") ,_T("current pressure") ,_T("[x]"), AS, 8, ID_K_VL);
	addLHS(7, _T("[oline]") ,_T("current pressure") ,_T("[y]"), AS, 8, ID_K_VL);
	addLHS(8, _T("[x]") ,_T("LT") ,_T("[y]"), LT, 8, ID_RO_VL);

*/

}


void CAipi_LHS::SamplesOPS5()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_PM pm;
	pm.addPM_Name(1,_T("R1"));
	CAipi_RETE_NNode not;
	not.insertNN(2);   //Condition 2
	
	
	//Production 1
	addLHS(1, _T("person") ,_T("city_of_residence") ,_T("[city1]"), EQ, 1, K_K_VL);
	addLHS(2, _T("city") ,_T("name") ,_T("[city1]"), EQ, 1, K_K_VL);
	



}



void CAipi_LHS::SamplesOrder()
{

//Sample 22.0
//Order Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	//Production 1
	addLHS(1, _T("[x]") ,_T("color") ,_T("red"),EQ, 1, ID_K_K);
	addLHS(2, _T("[y]") ,_T("on") ,_T("[x]"),EQ, 1, ID_K_VL);
	addLHS(3, _T("[y]") ,_T("color") ,_T("blue"), EQ, 1, ID_K_K);
*/	


////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 22.0
//Order Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	//Production 1
	addLHS(1, _T("[y]") ,_T("on") ,_T("[x]"),EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("color") ,_T("blue"),EQ, 1, ID_K_K);
	addLHS(3, _T("[x]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
*/	

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 22.0
//Order Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	//Production 1
	addLHS(1, _T("[y]") ,_T("color") ,_T("blue"),EQ, 1, ID_K_K);
	addLHS(2, _T("[y]") ,_T("on") ,_T("[x]"),EQ, 1, ID_K_VL);
	addLHS(3, _T("[x]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
*/	

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 24.1
//Order  Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	
	//Production 1
	
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("left of") ,_T("[z]"),EQ, 1, ID_K_VL);
	addLHS(3, _T("[x]") ,_T("color") ,_T("blue"), EQ, 1, ID_K_K);
	addLHS(4, _T("[y]") ,_T("on") ,_T("[w]"),	EQ, 1, ID_K_VL);
	addLHS(5, _T("[y]") ,_T("left of") ,_T("[u]"),	EQ, 1, ID_K_VL);
	addLHS(6, _T("[y]") ,_T("color") ,_T("red"),	EQ, 1, ID_K_K);
	addLHS(7, _T("[z]") ,_T("color") ,_T("red"),EQ, 1, ID_K_K);
	addLHS(8, _T("[w]") ,_T("color") ,_T("blue"), EQ, 1, ID_K_K);
	addLHS(9, _T("[u]") ,_T("color") ,_T("blue"),	EQ, 1, ID_K_K);
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 24.11
//Order Test  Different Order

/*
	CAipi_PM pm;
	pm.addPM_Name(11,_T("Reglas 11"));
	
	//Production 1
	
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 11, ID_K_VL);
	addLHS(2, _T("[u]") ,_T("color") ,_T("blue"),EQ, 11, ID_K_K);
	addLHS(3, _T("[x]") ,_T("color") ,_T("blue"), EQ, 11, ID_K_K);
	addLHS(4, _T("[z]") ,_T("color") ,_T("red"),	EQ, 11, ID_K_K);
	addLHS(5, _T("[y]") ,_T("left of") ,_T("[u]"),	EQ, 11, ID_K_VL);
	addLHS(6, _T("[y]") ,_T("color") ,_T("red"),	EQ, 11, ID_K_K);
	addLHS(7, _T("[y]") ,_T("on") ,_T("[w]"),EQ, 11, ID_K_VL);
	addLHS(8, _T("[w]") ,_T("color") ,_T("blue"), EQ, 11, ID_K_K);
	addLHS(9, _T("[x]") ,_T("left of") ,_T("[z]"),	EQ, 11, ID_K_VL);
*/
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 24.11.1
//Order Test  Different Order

/*
	CAipi_PM pm;
	pm.addPM_Name(12,_T("Reglas 12"));
	
	//Production 1
	
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 12, ID_K_VL);
	addLHS(2, _T("[u]") ,_T("color") ,_T("blue"),EQ, 12, ID_K_K);
	addLHS(3, _T("[x]") ,_T("color") ,_T("blue"), EQ, 12, ID_K_K);
	addLHS(4, _T("[z]") ,_T("color") ,_T("red"),	EQ, 12, ID_K_K);
	addLHS(5, _T("[y]") ,_T("left of") ,_T("[u]"),	EQ, 12, ID_K_VL);
	addLHS(6, _T("[y]") ,_T("color") ,_T("red"),	EQ, 12, ID_K_K);
	addLHS(7, _T("[y]") ,_T("on") ,_T("[w]"),EQ, 12, ID_K_VL);
	addLHS(8, _T("[x]") ,_T("left of") ,_T("[z]"),	EQ, 12, ID_K_VL);
	addLHS(9, _T("[w]") ,_T("color") ,_T("blue"), EQ, 12, ID_K_K);
*/
	
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 24.11.2
//Order Test  Different Order

/*
	CAipi_PM pm;
	pm.addPM_Name(13,_T("Reglas 13"));
	
	//Production 1
	
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 13, ID_K_VL);
	addLHS(2, _T("[u]") ,_T("color") ,_T("blue"),EQ, 13, ID_K_K);
	addLHS(3, _T("[x]") ,_T("color") ,_T("blue"), EQ, 13, ID_K_K);
	addLHS(4, _T("[z]") ,_T("color") ,_T("red"),	EQ, 13, ID_K_K);
	addLHS(5, _T("[y]") ,_T("left of") ,_T("[u]"),	EQ, 13, ID_K_VL);
	addLHS(6, _T("[y]") ,_T("color") ,_T("red"),	EQ, 13, ID_K_K);
	addLHS(7, _T("[x]") ,_T("left of") ,_T("[z]"),	EQ, 13, ID_K_VL);
	addLHS(8, _T("[y]") ,_T("on") ,_T("[w]"),EQ, 13, ID_K_VL);
	addLHS(9, _T("[w]") ,_T("color") ,_T("blue"), EQ, 13, ID_K_K);

*/

	////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 24.11.3
//Order Test  Different Order

/*
	CAipi_PM pm;
	pm.addPM_Name(13,_T("Reglas 13"));
	
	//Production 1
	
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 13, ID_K_VL);
	addLHS(2, _T("[u]") ,_T("color") ,_T("blue"),EQ, 13, ID_K_K);
	addLHS(3, _T("[x]") ,_T("color") ,_T("blue"), EQ, 13, ID_K_K);
	addLHS(4, _T("[z]") ,_T("color") ,_T("red"),	EQ, 13, ID_K_K);
	addLHS(5, _T("[y]") ,_T("left of") ,_T("[u]"),	EQ, 13, ID_K_VL);
	addLHS(6, _T("[y]") ,_T("color") ,_T("red"),	EQ, 13, ID_K_K);
	addLHS(7, _T("[x]") ,_T("left of") ,_T("[z]"),	EQ, 13, ID_K_VL);
	addLHS(8, _T("[w]") ,_T("color") ,_T("blue"),EQ, 13, ID_K_K);
	addLHS(9, _T("[y]") ,_T("on") ,_T("[w]"), EQ, 13, ID_K_VL);
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 24.12
//Order Test
/*
	CAipi_PM pm;
	pm.addPM_Name(2,_T("Reglas 2"));
	
	//Production 2
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 2);
	addLHS(2, _T("[x]") ,_T("left of") ,_T("[z]"),EQ, 2);
	addLHS(3, _T("[x]") ,_T("color") ,_T("blue"), EQ, 2);
	addLHS(4, _T("[y]") ,_T("on") ,_T("[w]"),	EQ, 2);
	addLHS(5, _T("[y]") ,_T("left of") ,_T("[u]"),	EQ, 2);
	addLHS(6, _T("[y]") ,_T("color") ,_T("red"),	EQ, 2);
	addLHS(7, _T("[z]") ,_T("color") ,_T("red"),EQ, 2);
	addLHS(8, _T("[w]") ,_T("color") ,_T("blue"), EQ, 2);
	addLHS(9, _T("[u]") ,_T("color") ,_T("blue"),	EQ, 2);
	addLHS(10, _T("[a]") ,_T("on") ,_T("[b]"),		EQ, 2);
	addLHS(11, _T("[b]") ,_T("left of") ,_T("[c]"),EQ, 2);
*/	
	


////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//Sample 24.13
//Order Test
/*
	CAipi_PM pm;
	pm.addPM_Name(3,_T("Reglas 3"));
	
	//Production 3
		
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 3, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("left of") ,_T("[z]"),EQ, 3, ID_K_VL);
	addLHS(3, _T("block2") ,_T("color") ,_T("blue"), EQ, 3, K_K_K);
	addLHS(4, _T("[y]") ,_T("on") ,_T("[w]"),	EQ, 3, ID_K_VL);
	addLHS(5, _T("[y]") ,_T("left of") ,_T("[u]"),	EQ, 3, ID_K_VL);
	addLHS(6, _T("[y]") ,_T("color") ,_T("red"),	EQ, 3, ID_K_K);
	addLHS(7, _T("[z]") ,_T("color") ,_T("red"),EQ, 3, ID_K_K);
	addLHS(8, _T("[w]") ,_T("color") ,_T("blue"), EQ, 3, ID_K_K);
	addLHS(9, _T("[u]") ,_T("color") ,_T("blue"),	EQ, 3, ID_K_K);
*/	

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//Sample 24.2
//Order Test
/*
	CAipi_PM pm;
	pm.addPM_Name(3,_T("Reglas 3"));
	
	//Production 3
		
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 3, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("left of") ,_T("[z]"),EQ, 3, ID_K_VL);
	addLHS(3, _T("[x]") ,_T("color") ,_T("blue"), EQ, 3, ID_K_K);
	addLHS(4, _T("[y]") ,_T("on") ,_T("[w]"),	EQ, 3, ID_K_VL);
	addLHS(5, _T("[y]") ,_T("left of") ,_T("[u]"),	EQ, 3, ID_K_VL);
	addLHS(6, _T("[y]") ,_T("color") ,_T("blue"),	EQ, 3, ID_K_K);
	addLHS(7, _T("[z]") ,_T("on") ,_T("[y]"),EQ, 3, ID_K_VL);
	addLHS(8, _T("[w]") ,_T("on") ,_T("[y]"), EQ, 3, ID_K_VL);
	addLHS(9, _T("[u]") ,_T("on") ,_T("[y]"),	EQ, 3, ID_K_VL);
*/	

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//Sample 24.3
//Order Test
/*
	CAipi_PM pm;
	pm.addPM_Name(3,_T("Reglas 3"));
	
	//Production 3
		
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 3, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("left of") ,_T("[z]"),EQ, 3, ID_K_VL);
	addLHS(3, _T("[x]") ,_T("color") ,_T("blue"), EQ, 3, ID_K_K);
	addLHS(4, _T("[a]") ,_T("on") ,_T("[b]"),	EQ, 3, ID_K_VL);
	addLHS(5, _T("[b]") ,_T("left of") ,_T("[b]"),	EQ, 3, ID_K_VL);
	addLHS(6, _T("[c]") ,_T("color") ,_T("red"),	EQ, 3, ID_K_K);
*/	
	

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//Sample 24.4, 24.41, 24.42
//Order Test
/*
	CAipi_PM pm;
	pm.addPM_Name(3,_T("Reglas 3"));
	
	//Production 3
		
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 3, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"),EQ, 3, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("left of") ,_T("[x]"), EQ, 3, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("color") ,_T("red"),	EQ, 3, ID_K_K);
*/	

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//Order Test

//Sample 25.01
//Numeric Test

/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);

	//Production 1
	addLHS(1, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[z]") ,_T("size") ,_T("[sz]"),AS, 1, ID_K_VL);
	addLHS(3, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(4, _T("[y]") ,_T("left of") ,_T("[z]"),	EQ, 1, ID_K_VL);
	addLHS(5, _T("[sz]") ,_T("LT") ,_T("[sx]"),	LT, 1, ID_RO_VL);
*/


////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//Order Test

//Sample 25.02
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);

	//Production 1
	addLHS(1, _T("[sz]") ,_T("LT") ,_T("[sx]"),	LT, 1, ID_RO_VL);
	addLHS(2, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("size") ,_T("[sz]"), AS, 1, ID_K_VL);
	addLHS(4, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(5, _T("[y]") ,_T("left of") ,_T("[z]"),	EQ, 1, ID_K_VL);
*/
	
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
//Order Test

//Sample 25.03
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);

	//Production 1
	
	addLHS(1, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[z]") ,_T("size") ,_T("[sz]"), AS, 1, ID_K_VL);
	addLHS(3, _T("[sz]") ,_T("LT") ,_T("[sx]"),	LT, 1, ID_RO_VL);
	addLHS(4, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(5, _T("[y]") ,_T("left of") ,_T("[z]"),	EQ, 1, ID_K_VL);
*/

}


void CAipi_LHS::SamplesNumeric()
{

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 23.0
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"),EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	addLHS(4, _T("block3") ,_T("size") ,_T("2"),	GE, 1, K_K_K);
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 23.4
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"),EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	addLHS(4, _T("block3") ,_T("[area]") ,_T("2"),	GT, 1, ID_AT_K);
*/


////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 23.5
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"),EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	addLHS(4, _T("[z]") ,_T("size") ,_T("2"),	GT, 1, ID_K_K);
*/	

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 23.6
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"),EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	addLHS(4, _T("[z]") ,_T("[a]") ,_T("2"),	GT, 1, ID_AT_K);
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 23.7
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"),EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	addLHS(4, _T("[z]") ,_T("size") ,_T("[w]"),	GT, 1, ID_K_VL);
*/



////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 24.0
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("left of") ,_T("[z]"),EQ, 1, ID_K_VL);
	addLHS(3, _T("[x]") ,_T("color") ,_T("blue"), EQ, 1, ID_K_K);
	addLHS(4, _T("[y]") ,_T("on") ,_T("[w]"),	EQ, 1, ID_K_VL );
	addLHS(5, _T("[y]") ,_T("left of") ,_T("[u]"),	EQ, 1, ID_K_VL);
	addLHS(6, _T("[y]") ,_T("color") ,_T("blue"),	EQ, 1, ID_K_K);
	addLHS(7, _T("[z]") ,_T("color") ,_T("red"),EQ, 1, ID_K_K);
	addLHS(8, _T("[w]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	addLHS(9, _T("[u]") ,_T("color") ,_T("blue"),	EQ, 1, ID_K_K);
*/	


////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 24.43
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"),EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	addLHS(4, _T("[z]") ,_T("size") ,_T("2"),	GT, 1, ID_K_K);
	addLHS(5, _T("[y]") ,_T("size") ,_T("2"),	GE, 1, ID_K_K);
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 25.0
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	

	//Production 1
	addLHS(1, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(3, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("size") ,_T("[sz]"),	AS, 1, ID_K_VL);
	addLHS(5, _T("[sz]") ,_T("LT") ,_T("[sx]"),	LT, 1, ID_RO_VL);
*/
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 25.11
//Numeric Test
//Check logic of the problem
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);

	//Production 1
	addLHS(1, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[z]") ,_T("size") ,_T("[sz]"),	AS, 1, ID_K_VL);
	addLHS(3, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(4, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(5, _T("[sz]") ,_T("LT") ,_T("[sx]"),	LT, 1, ID_RO_VL);
	addLHS(6, _T("[sz]") ,_T("size") ,_T("6"),	GE, 1, ID_K_K);
	addLHS(7, _T("[sx]") ,_T("size") ,_T("2"),	GT, 1, ID_K_K);
*/




////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 26.00
//Numeric Test
	
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	
	

	//Production 1
	addLHS(1, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(3, _T("[y]") ,_T("left of") ,_T("[z]"),	EQ, 1, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("size") ,_T("[sz]"),	AS, 1, ID_K_VL);
	addLHS(5, _T("[z]") ,_T("color") ,_T("red"),	EQ, 1, ID_K_K);
	addLHS(6, _T("[sx]") ,_T("GE") ,_T("[sz]"),		GE, 1, ID_RO_VL);
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 26.10
//Numeric Test
	
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	
	

	//Production 1
	addLHS(1, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(3, _T("[y]") ,_T("left of") ,_T("[z]"),	EQ, 1, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("size") ,_T("[sz]"),	AS, 1, ID_K_VL);
	addLHS(5, _T("[z]") ,_T("color") ,_T("red"),	EQ, 1, ID_K_K);
	addLHS(6, _T("[sz]") ,_T("GE") ,_T("[sx]"),		GE, 1, ID_RO_VL);
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 26.11
//Numeric Test
	
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	
	

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"),	EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("size") ,_T("[sz]"),	AS, 1, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("color") ,_T("red"),	EQ, 1, ID_K_K);
	addLHS(5, _T("[sz]") ,_T("GE") ,_T("5"),		GE, 1, ID_RO_K);
*/


////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 26.12
//Numeric Test

/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	
	

	//Production 1
	addLHS(1, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(3, _T("[y]") ,_T("left of") ,_T("[z]"),	EQ, 1, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("size") ,_T("[sz]"),	AS, 1, ID_K_VL);
	addLHS(5, _T("[z]") ,_T("color") ,_T("red"),	EQ, 1, ID_K_K);
	addLHS(6, _T("[sz]") ,_T("GE") ,_T("5"),		GE, 1, ID_RO_K);
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 26.13
//Numeric Test

/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	
	

	//Production 1
	addLHS(1, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(3, _T("[y]") ,_T("left of") ,_T("[z]"),	EQ, 1, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("size") ,_T("[sz]"),	AS, 1, ID_K_VL);
	addLHS(5, _T("[z]") ,_T("color") ,_T("red"),	EQ, 1, ID_K_K);
	addLHS(6, _T("5") ,_T("LT") ,_T("[sz]"),		LT, 1, K_RO_VL);
*/

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 26.20
//Numeric Test
	
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	op.addAttr_Type(_T("area"), AIPI_D);
	

	//Production 1
	addLHS(1, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(3, _T("[y]") ,_T("left of") ,_T("[z]"),	EQ, 1, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("area") ,_T("[az]"),	AS, 1, ID_K_VL);
	addLHS(5, _T("[z]") ,_T("color") ,_T("red"),	EQ, 1, ID_K_K);
	addLHS(6, _T("[az]") ,_T("LT") ,_T("[sx]"),		LT, 1, ID_RO_VL);
*/


////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 26.21
//Numeric Test
	
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	op.addAttr_Type(_T("area"), AIPI_D);
	

	//Production 1
	addLHS(1, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("on") ,_T("[z]"),		EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("area") ,_T("[az]"),	AS, 1, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("color") ,_T("red"),	EQ, 1, ID_K_K);
	addLHS(5, _T("[az]") ,_T("LT") ,_T("[sx]"),		LT, 1, ID_RO_VL);
*/
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 27.0
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	op.addAttr_Type(_T("area"), AIPI_D);
	//Production 1
	addLHS(1, _T("[x]") ,_T("size")		,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("on")		,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(3, _T("[y]") ,_T("left of")	,_T("[z]"),		EQ, 1, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("size")		,_T("[sz]"),	AS, 1, ID_K_VL);
	addLHS(5, _T("[sz]") ,_T("LT")		,_T("[sx]"),	LT, 1, ID_RO_VL);
	addLHS(6, _T("[x]") ,_T("area")		,_T("[ax]"),	AS, 1, ID_K_VL);
	addLHS(7, _T("[z]") ,_T("area")		,_T("[az]"),	AS, 1, ID_K_VL);
	addLHS(8, _T("[ax]") ,_T("LT")		,_T("[az]"),	LT, 1, ID_RO_VL);
*/
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 27.01
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	op.addAttr_Type(_T("area"), AIPI_D);
	//Production 1
	
	addLHS(1, _T("[x]") ,_T("size")		,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("on")		,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(3, _T("[y]") ,_T("left of")	,_T("[z]"),		EQ, 1, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("size")		,_T("[sz]"),	AS, 1, ID_K_VL);
	addLHS(5, _T("[sz]") ,_T("LT")		,_T("[sx]"),	LT, 1, ID_RO_VL);
	addLHS(6, _T("[x]") ,_T("area")		,_T("[ax]"),	AS, 1, ID_K_VL);
	addLHS(7, _T("[z]") ,_T("area")		,_T("[az]"),	AS, 1, ID_K_VL);
	addLHS(8, _T("[ax]") ,_T("GT")		,_T("[az]"),	GT, 1, ID_RO_VL);
*/


////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 27.02
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("area"), AIPI_D);
	
	//Production 1
	addLHS(1, _T("[x]") ,_T("area") ,_T("[ax]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(3, _T("[y]") ,_T("left of") ,_T("[z]"),	EQ, 1, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("area") ,_T("[az]"),	AS, 1, ID_K_VL);
	addLHS(5, _T("[z]") ,_T("color") ,_T("red"),	EQ, 1, ID_K_K);
	addLHS(6, _T("[az]") ,_T("GE") ,_T("[ax]"),		GE, 1, ID_RO_VL);
*/	
	

////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 27.03
//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	op.addAttr_Type(_T("area"), AIPI_D);
	//Production 1
	
	addLHS(1, _T("[x]") ,_T("size")		,_T("[sx]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[x]") ,_T("on")		,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(3, _T("[y]") ,_T("left of")	,_T("[z]"),		EQ, 1, ID_K_VL);
	addLHS(4, _T("[z]") ,_T("size")		,_T("[sz]"),	AS, 1, ID_K_VL);
	addLHS(5, _T("[sz]") ,_T("LT")		,_T("[sx]"),	LT, 1, ID_RO_VL);
	addLHS(6, _T("[x]") ,_T("area")		,_T("[ax]"),	AS, 1, ID_K_VL);
	addLHS(7, _T("[z]") ,_T("area")		,_T("[az]"),	AS, 1, ID_K_VL);
	addLHS(8, _T("[sz]") ,_T("GT")		,_T("[az]"),	GT, 1, ID_RO_VL);
*/


////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 27.04

//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	
	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	op.addAttr_Type(_T("area"), AIPI_D);
	
	
	//Production 1
	addLHS(1, _T("[a]") ,_T("on") ,_T("[b]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[a]") ,_T("area") ,_T("[aa]"),	AS, 1, ID_K_VL);
	addLHS(3, _T("[b]") ,_T("area") ,_T("[ab]"),	AS, 1, ID_K_VL);
	addLHS(4, _T("[ab]") ,_T("ET") ,_T("[aa]"),		ET, 1, ID_RO_VL);
	
	

  //Production 2
	addLHS(5, _T("[x]") ,_T("on") ,_T("[z]"),		EQ, 2, ID_K_VL);
	addLHS(6, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 2, ID_K_VL);
	addLHS(7, _T("[z]") ,_T("size") ,_T("[sz]"),	AS, 2, ID_K_VL);
	addLHS(8, _T("[sz]") ,_T("ET") ,_T("[sx]"),		ET, 2, ID_RO_VL);
*/	
	
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 27.05

//Numeric Test
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	
	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	op.addAttr_Type(_T("area"), AIPI_D);
	
	
	//Production 1
	addLHS(1, _T("[a]") ,_T("on") ,_T("[b]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[a]") ,_T("area") ,_T("[aa]"),	AS, 1, ID_K_VL);
	addLHS(3, _T("[b]") ,_T("size") ,_T("[sb]"),	AS, 1, ID_K_VL);
	addLHS(4, _T("[sb]") ,_T("ET") ,_T("[aa]"),		ET, 1, ID_RO_VL);
	
	

  //Production 2
	addLHS(5, _T("[x]") ,_T("on") ,_T("[z]"),		EQ, 2, ID_K_VL);
	addLHS(6, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 2, ID_K_VL);
	addLHS(7, _T("[z]") ,_T("area") ,_T("[az]"),	AS, 2, ID_K_VL);
	addLHS(8, _T("[az]") ,_T("ET") ,_T("[sx]"),		ET, 2, ID_RO_VL);

*/



////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 27.051

//Numeric Test different Order
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	
	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("size"), AIPI_I);
	op.addAttr_Type(_T("area"), AIPI_D);
	
	
	//Production 1
	
	addLHS(1, _T("[a]") ,_T("area") ,_T("[aa]"),	AS, 1, ID_K_VL);
	addLHS(2, _T("[b]") ,_T("size") ,_T("[sb]"),	AS, 1, ID_K_VL);
	addLHS(3, _T("[sb]") ,_T("ET") ,_T("[aa]"),		ET, 1, ID_RO_VL);
	addLHS(4, _T("[a]") ,_T("on") ,_T("[b]"),		EQ, 1, ID_K_VL);
	

  //Production 2
	addLHS(5, _T("[x]") ,_T("size") ,_T("[sx]"),	AS, 2, ID_K_VL);
	addLHS(6, _T("[z]") ,_T("area") ,_T("[az]"),	AS, 2, ID_K_VL);
	addLHS(7, _T("[az]") ,_T("ET") ,_T("[sx]"),		ET, 2, ID_RO_VL);
	addLHS(8, _T("[x]") ,_T("on") ,_T("[z]"),		EQ, 2, ID_K_VL);
*/


}



void CAipi_LHS::SamplesStringRelational()
{
////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////



//Sample 26.30
//Relational String Test
	
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("color"), AIPI_S);
	

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),	EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"),		EQ, 1, ID_K_VL);
	addLHS(3, _T("[y]") ,_T("color") ,_T("[sy]"),	AS, 1, ID_K_VL);
	addLHS(4, _T("[sy]") ,_T("ET") ,_T("red"),	ET, 1, ID_RO_K);
*/	


////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 26.31
//Relational String Test
	
/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));

	CAipi_RETE_Operations op;
	op.addAttr_Type(_T("left of"), AIPI_S);
	
	
	

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("color") ,_T("red"),	EQ, 1, ID_K_K);
	addLHS(3, _T("[y]") ,_T("left of") ,_T("[var]"),	AS, 1, ID_K_VL);
	addLHS(4, _T("[var]") ,_T("ET") ,_T("block4"),	ET, 1, ID_RO_K);
*/	

}



void CAipi_LHS::SamplesNegated()
{

//Sample 9, 9.3
//Negated Conditions
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	RETE_NOTNode not;
	not.insertNOT(3);   //Condition 3
	
	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("color") ,_T("blue"), EQ, 1);
	

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 9.1, 9.2
//Negated Conditions
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro


	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	CAipi_RETE_NNode not;
	not.insertNN(3);   //Condition 3
	
	
	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1, ID_K_K);
	
	



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 10.1, 10.2 
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	RETE_NOTNode not;
	not.insertNOT(3);   //Condition 3
	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHSE(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);

*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 10.3 
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	RETE_NOTNode not;
	not.insertNOT(3);   //Condition 3
	not.insertNOT(4);   //Condition 4

	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHSE(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);

*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 10.4 
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	RETE_NOTNode not;
	not.insertNOT(3);   //Condition 3
	not.insertNOT(5);   //Condition 5

	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHSE(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);

*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 10.5 
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	RETE_NOTNode not;
	not.insertNOT(2);   //Condition 2
	

	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHSE(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);

*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 11 
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	
	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("blue"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHSE(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);

*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 11.1 
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	RETE_NOTNode not;
	not.insertNOT(3);   //Condition 3
	
	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("blue"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHSE(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);

*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 11.2 
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	RETE_NOTNode not;
	not.insertNOT(4);   //Condition 4
	
	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("blue"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHSE(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);

*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 12, 12.1 
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	pm.addPMEName(2,_T("Reglas 02"));
	RETE_NOTNode not;
	not.insertNOT(3);   //Condition 3
	
	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHSE(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);

   //Production 2
	addLHSE(6, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHSE(7, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 2);
	addLHSE(8, _T("[z]") ,_T("color") ,_T("red"), EQ, 2);
	addLHSE(9, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 2);
	addLHSE(10, _T("[w]") ,_T("on") ,_T("table"), EQ, 2);


*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 12.2 
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	pm.addPMEName(2,_T("Reglas 02"));
	RETE_NOTNode not;
	not.insertNOT(3);   //Condition 3
	not.insertNOT(4);   //Condition 4
	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHSE(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);

   //Production 2
	addLHSE(6, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHSE(7, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 2);
	addLHSE(8, _T("[z]") ,_T("color") ,_T("red"), EQ, 2);
	addLHSE(9, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 2);
	addLHSE(10, _T("[w]") ,_T("on") ,_T("table"), EQ, 2);


*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 12.3 
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	pm.addPMEName(2,_T("Reglas 02"));
	RETE_NOTNode not;
	not.insertNOT(1);   //Condition 1
	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHSE(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);

   //Production 2
	addLHSE(6, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHSE(7, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 2);
	addLHSE(8, _T("[z]") ,_T("color") ,_T("red"), EQ, 2);
	addLHSE(9, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 2);
	addLHSE(10, _T("[w]") ,_T("on") ,_T("table"), EQ, 2);


*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 12.4 
//Extract from Tutorial RETE, Negated Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	pm.addPMEName(2,_T("Reglas 02"));
	RETE_NOTNode not;
	not.insertNOT(3);   //Condition 3
	not.insertNOT(7);   //Condition 7
	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHSE(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);

   //Production 2
	addLHSE(6, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHSE(7, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 2);
	addLHSE(8, _T("[z]") ,_T("color") ,_T("red"), EQ, 2);
	addLHSE(9, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 2);
	addLHSE(10, _T("[w]") ,_T("on") ,_T("table"), EQ, 2);


*/


}


void CAipi_LHS::SamplesConjuntiveNegations()
{
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 13.1
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	CAipi_RETE_NCCNode ncc;
	ncc.insertNCC(3,4,1);   //Condition 3 to Condition 4,Production 1	
		
	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ; 1);
	
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 14.1, 14.2
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro
	

/*
			
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	CAipi_RETE_NCCNode ncc;
	ncc.insertNCC(3,4,1);  //Condition 3 to Condition 4,Production 1

	//Production 1
	addLHSE(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHSE(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHSE(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 14.3
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro


/*		
	CAipi_PM pmo;
	pmo.addPM_Name(1,_T("Reglas 01"));
	CAipi_RETE_NCC Nodencc;
	ncc.insertNCC(3,4,1);  //Condition 3 to Condition 4,Production 1

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHS(5, _T("[z]") ,_T("on") ,_T("table"), EQ, 1);
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 14.4
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro


/*		
	CAipi_PM pmo;
	pmo.addPM_Name(1,_T("Reglas 01"));
	CAipi_RETE_NCCNode ncc;
	ncc.insertNCC(2,3, 1);  //Condition 2 to Condition 3,Production 1

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHS(5, _T("[w") ,_T("on") ,_T("table"), EQ, 1);
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 14.5
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro


/*  
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	CAipi_RETE_NCCNode ncc;
	ncc.insertNCC(2,3,1);   //Condition 2 to Condition 3, Production 1

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(4, _T("[y]") ,_T("on") ,_T("[w]"), EQ, 1);
	addLHS(5, _T("[w]") ,_T("on") ,_T("table"), EQ, 1);
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 14.6
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro

/*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	CAipi_RETE_NCCNode ncc;
	ncc.insertNCC(1,4,1);  //Condition 1 to Condition 4, Production 1

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);	
		

	
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 14.7, 14.8
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro


/*  
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	CAipi_RETE_NCCNode ncc;
	ncc.insertNCC(1,4,1);  //Condition 1 to Condition 4, Production 1
	
	CAipi_RETE_NNode not;
	not.insertNOT(3);

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
*/	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 15.1, 15.2, 15.3
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro


/*
  	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	CAipi_RETE_NCCNode ncc;
	ncc.insertNCC(1,3,1);   //Condition 1 to Condition 3, Production 1
	ncc.insertNCC(2,3,1);   //Condition 2 to Condition 3, Production 1
	
	
	//Production 1
	addLHS(1, _T("[x]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(2, _T("[y]") ,_T("on") ,_T("[x]"), EQ, 1);
	addLHS(3, _T("[y]") ,_T("color") ,_T("blue"), EQ, 1);
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 15.4
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro

/*

  	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	CAipi_RETE_NCCNode ncc;
	ncc.insertNCC(2,3,1);   //Condition 2 to Condition 3, Production 1
	
	
	//Production 1
	addLHS(1, _T("[x]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(2, _T("[y]") ,_T("on") ,_T("[x]"), EQ, 1);
	addLHS(3, _T("[y]") ,_T("color") ,_T("blue"), EQ, 1);
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 15.5
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro

/*

  	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	CAipi_RETE_NNode not;
	not.insertNOT(1);    //Condition 1
	
	CAipi_RETE_NCCNode ncc;
	ncc.insertNCC(2,3,1);   //Condition 2 to Condition 3, Production 1
	
	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("on") ,_T("[x]"), EQ, 1);
	addLHSE(3, _T("[y]") ,_T("color") ,_T("blue"), EQ, 1);
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 15.6
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro

/*

  	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	CAipi_RETE_NCCNode ncc;
	ncc.insertNCC(1,1,1);   //Condition 1 to Condition 1, Production 1
	ncc.insertNCC(2,3,1);   //Condition 2 to Condition 3, Production 1
	
	//Equivalent to Sample 15.5
	
	//Production 1
	addLHSE(1, _T("[x]") ,_T("color") ,_T("red"), EQ, 1);
	addLHSE(2, _T("[y]") ,_T("on") ,_T("[x]"), EQ, 1);
	addLHSE(3, _T("[y]") ,_T("color") ,_T("blue"), EQ, 1);
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 16.1, 16.2
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro
	

/*	
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	CAipi_RETE_NCCNode ncc;
	ncc.insertNCC(3, 5, 1);
	ncc.insertNCC(4, 5, 1);

	//Production 1
	addLHS(1, _T("[a]") ,_T("left of") ,_T("[b]"), EQ, 1);
	addLHS(2, _T("[b]") ,_T("left of") ,_T("[x]"), EQ, 1);
	addLHS(3, _T("[x]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(4, _T("[y]") ,_T("on") ,_T("[x]"), EQ, 1);
	addLHS(4, _T("[y]") ,_T("color") ,_T("blue"), EQ, 1);
*/
	

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 16.3, 16.4
//Conjuctive Conditions Negations
//Extract from Tutorial RETE, Negated Conjunctive Conditions - Mauricio Alfaro
	

/*	
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	CAipi_RETE_NCCNode ncc;
	ncc.insertNCC(2, 5, 1);
	ncc.insertNCC(4, 5, 1);

	//Production 1
	addLHS(1, _T("[a]") ,_T("left of") ,_T("[b]"), EQ, 1);
	addLHS(2, _T("[b]") ,_T("left of") ,_T("[x]"), EQ, 1);
	addLHS(3, _T("[x]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(4, _T("[y]") ,_T("on") ,_T("[x]"), EQ, 1);
	addLHS(4, _T("[y]") ,_T("color") ,_T("blue"), EQ, 1);

*/	

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
//Sample 17.0
	
/*
	
	  
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	pm.addPMEName(2,_T("Reglas 02"));
	CAipi_RETE_NCCNode ncc;
	CAipi_RETE_NNode not;
	//not.insertNOT(7);
	ncc.insertNCC(2, 4, 1);
	ncc.insertNCC(6, 8, 2);

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	

	  //Production 2
	addLHS(5, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHS(6, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 2);
	addLHS(7, _T("[y]") ,_T("color") ,_T("red"), EQ, 2);
	addLHS(8, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 2);	
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 17.1

/*
	
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	pm.addPMEName(2,_T("Reglas 02"));
	CAipi_RETE_NCCNode ncc;
	CAipi_RETE_NNode not;
	//not.insertNOT(7);
	ncc.insertNCC(2, 4, 1);
	ncc.insertNCC(6, 8, 2);

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	

	  //Production 2
	addLHS(5, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHS(6, _T("[y]") ,_T("color") ,_T("red"), EQ, 2);
	addLHS(7, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 2);
	addLHS(8, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 2);	
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 17.2

	
 /*
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	pm.addPMEName(2,_T("Reglas 02"));
	CAipi_RETE_NCCNode ncc;
	CAipi_RETE_NNode not;
	//not.insertNOT(7);
	ncc.insertNCC(1, 2, 1);
	ncc.insertNCC(6, 7, 2);

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	

	  //Production 2
	addLHS(5, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHS(6, _T("[y]") ,_T("color") ,_T("red"), EQ, 2);
	addLHS(7, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 2);
	addLHS(8, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 2);
*/	


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
	//Sample 17.3
	  
	CAipi_PM pm;
	pm.addPMEName(1,_T("Reglas 01"));
	pm.addPMEName(2,_T("Reglas 02"));
	CAipi_RETE_NCCNode ncc;
	CAipi_RETE_NNode not;
	//not.insertNOT(7);
	ncc.insertNCC(2, 3, 1);
	ncc.insertNCC(5, 6, 2);

	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 1);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 1);
	addLHS(3, _T("[z]") ,_T("color") ,_T("red"), EQ, 1);
	addLHS(4, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 1);
	

	  //Production 2
	addLHS(5, _T("[x]") ,_T("on") ,_T("[y]"), EQ, 2);
	addLHS(6, _T("[y]") ,_T("color") ,_T("red"), EQ, 2);
	addLHS(7, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 2);
	addLHS(8, _T("[z]") ,_T("on") ,_T("[w]"), EQ, 2);	

*/



}



void CAipi_LHS::SamplesPerformance()
{


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 20
/*
	//Performance Test
	CAipi_PM pm;
	pm.addPM_Name(1,_T("Reglas 01"));
	pm.addPM_Name(2,_T("Reglas 02"));
	pm.addPM_Name(3,_T("Reglas 03"));
	pm.addPM_Name(4,_T("Reglas 04"));
	pm.addPM_Name(5,_T("Reglas 05"));
	pm.addPM_Name(6,_T("Reglas 06"));
	pm.addPM_Name(7,_T("Reglas 07"));
	pm.addPM_Name(8,_T("Reglas 08"));
	pm.addPM_Name(9,_T("Reglas 09"));
	pm.addPM_Name(10,_T("Reglas 10"));
	pm.addPM_Name(11,_T("Reglas 11"));
	pm.addPM_Name(12,_T("Reglas 12"));
	pm.addPM_Name(13,_T("Reglas 13"));
	pm.addPM_Name(14,_T("Reglas 14"));
	pm.addPM_Name(15,_T("Reglas 15"));
	pm.addPM_Name(16,_T("Reglas 16"));
	pm.addPM_Name(17,_T("Reglas 17"));
	pm.addPM_Name(18,_T("Reglas 18"));
	pm.addPM_Name(19,_T("Reglas 19"));
	pm.addPM_Name(20,_T("Reglas 20"));
	pm.addPM_Name(21,_T("Reglas 21"));
	pm.addPM_Name(22,_T("Reglas 22"));
	pm.addPM_Name(23,_T("Reglas 23"));
	pm.addPM_Name(24,_T("Reglas 24"));
	pm.addPM_Name(25,_T("Reglas 25"));
	pm.addPM_Name(26,_T("Reglas 26"));
	pm.addPM_Name(27,_T("Reglas 27"));
	pm.addPM_Name(28,_T("Reglas 28"));
	pm.addPM_Name(29,_T("Reglas 29"));
	pm.addPM_Name(30,_T("Reglas 30"));
	pm.addPM_Name(31,_T("Reglas 31"));
	pm.addPM_Name(32,_T("Reglas 32"));
	pm.addPM_Name(33,_T("Reglas 33"));
	pm.addPM_Name(34,_T("Reglas 34"));
	pm.addPM_Name(35,_T("Reglas 35"));
	pm.addPM_Name(36,_T("Reglas 36"));
	pm.addPM_Name(37,_T("Reglas 37"));
	pm.addPM_Name(38,_T("Reglas 38"));
	pm.addPM_Name(39,_T("Reglas 39"));
	pm.addPM_Name(40,_T("Reglas 40"));
	
	
	
	//Production 1
	addLHS(1, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 1, ID_K_VL);
	addLHS(2, _T("[y]") ,_T("left of") ,_T("[z]"),	EQ, 1, ID_K_VL);
	addLHS(3, _T("[z]") ,_T("color") ,_T("blue"),	EQ, 1, ID_K_K);
	addLHS(4, _T("[z]") ,_T("on") ,_T("table"),		EQ, 1, ID_K_K);

	//Production 2
	addLHS(5, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 2, ID_K_VL);
	addLHS(6, _T("[y]") ,_T("left of") ,_T("[z]"),	EQ, 2, ID_K_VL);
	addLHS(7, _T("[z]") ,_T("color") ,_T("blue"),	EQ, 2, ID_K_K);
	addLHS(8, _T("[z]") ,_T("color") ,_T("red"),	EQ, 2, ID_K_K);


	//Production 3
	addLHS(9,  _T("[x]") ,_T("color") ,_T("blue"),	EQ, 3, ID_K_K);
	addLHS(10, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 3, ID_K_VL);
	addLHS(11, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 3, ID_K_VL);
	
	//Production 4
	addLHS(12, _T("[x]") ,_T("color") ,_T("blue"),	EQ, 4, ID_K_K);
	addLHS(13, _T("[x]") ,_T("left of") ,_T("[y]"), EQ, 4, ID_K_VL);
	addLHS(14, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 4, ID_K_VL);

	

	//Production 5
	addLHS(15, _T("[x]") ,_T("up") ,_T("[y]"),		EQ, 5, ID_K_VL);
	addLHS(16, _T("[y]") ,_T("right of") ,_T("[z]"),EQ, 5, ID_K_VL);
	addLHS(17, _T("[z]") ,_T("size") ,_T("10"),		ET, 5, ID_K_K);

	//Production 6
	addLHS(18, _T("[a]") ,_T("on") ,_T("[b]"),		EQ, 6, ID_K_VL);
	addLHS(19, _T("[b]") ,_T("left of") ,_T("[c]"), EQ, 6, ID_K_VL);
	addLHS(20, _T("[c]") ,_T("color") ,_T("red"),	EQ, 6, ID_K_K);
	addLHS(21, _T("[c]") ,_T("on") ,_T("[d]"),		EQ, 6, ID_K_VL);

	//Production 7
	addLHS(22, _T("[b]") ,_T("on") ,_T("[c]"),		EQ, 7, ID_K_VL);
	addLHS(23, _T("[c]") ,_T("left of") ,_T("[d]"), EQ, 7, ID_K_VL);
	addLHS(24, _T("[b]") ,_T("color") ,_T("blue"),	EQ, 7, ID_K_K);
	addLHS(25, _T("[c]") ,_T("color") ,_T("red"),	EQ, 7, ID_K_K);


	//Production 8
	addLHS(26,  _T("[i]") ,_T("color") ,_T("blue"), EQ, 8, ID_K_K);
	addLHS(27, _T("[j]") ,_T("on") ,_T("[k]"),		EQ, 8, ID_K_VL);
	addLHS(28, _T("[k]") ,_T("left of") ,_T("[m]"), EQ, 8, ID_K_VL);
	
	//Production 9
	addLHS(29, _T("[i]") ,_T("color") ,_T("blue"),	EQ, 9, ID_K_K);
	addLHS(30, _T("[i]") ,_T("left of") ,_T("[j]"), EQ, 9, ID_K_VL);
	addLHS(31, _T("[j]") ,_T("left of") ,_T("[m]"), EQ, 9, ID_K_VL);

	

	//Production 10
	addLHS(32, _T("[i]") ,_T("up") ,_T("[j]"),		EQ, 10, ID_K_VL);
	addLHS(33, _T("[i]") ,_T("right of") ,_T("[k]"),EQ, 10, ID_K_VL);
	addLHS(34, _T("[i]") ,_T("size") ,_T("10"),		ET,	10, ID_K_K);

	//Production 11
	addLHS(35, _T("[i]") ,_T("on") ,_T("[j]"),		EQ, 11, ID_K_VL);
	addLHS(36, _T("[j]") ,_T("left of") ,_T("[k]"), EQ, 11, ID_K_VL);
	addLHS(37, _T("[k]") ,_T("color") ,_T("blue"),	EQ, 11,ID_K_K);
	addLHS(38, _T("[k]") ,_T("on") ,_T("table"),	EQ, 11, ID_K_K);

	//Production 12
	addLHS(39, _T("[a]") ,_T("on") ,_T("[b]"),		EQ, 12, ID_K_VL);
	addLHS(40, _T("[a]") ,_T("left of") ,_T("[c]"), EQ, 12, ID_K_VL);
	addLHS(41, _T("[b]") ,_T("color") ,_T("blue"),	EQ, 12, ID_K_K);
	addLHS(42, _T("[c]") ,_T("color") ,_T("red"),	EQ, 12, ID_K_K);


	//Production 13
	addLHS(43,  _T("[a]") ,_T("color") ,_T("blue"), EQ, 13, ID_K_K);
	addLHS(44, _T("[a]") ,_T("on") ,_T("[j]"),		EQ, 13, ID_K_VL);
	addLHS(45, _T("[a]") ,_T("left of") ,_T("[z]"), EQ, 13, ID_K_VL);
	
	//Production 14
	addLHS(46, _T("[x]") ,_T("color") ,_T("blue"),	EQ, 14, ID_K_K);
	addLHS(47, _T("[x]") ,_T("left of") ,_T("[y]"), EQ, 14, ID_K_VL);
	addLHS(48, _T("[x]") ,_T("right of") ,_T("[z]"),EQ, 14, ID_K_VL);

	

	//Production 15
	addLHS(49, _T("[x]") ,_T("up") ,_T("[y]"),		EQ, 15, ID_K_VL);
	addLHS(50, _T("[y]") ,_T("right of") ,_T("[z]"),EQ, 15, ID_K_VL);
	addLHS(51, _T("[z]") ,_T("size") ,_T("20"),		ET, 15, ID_K_K);

	//Production 16
	addLHS(52, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 16, ID_K_VL);
	addLHS(53, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 16, ID_K_VL);
	addLHS(54, _T("[z]") ,_T("color") ,_T("yellow"),EQ, 16, ID_K_K);
	addLHS(55, _T("[z]") ,_T("on") ,_T("block4"),	EQ, 16, ID_K_K);

	//Production 17
	addLHS(56, _T("[x]") ,_T("on") ,_T("block2"),	EQ, 17, ID_K_K);
	addLHS(57, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 17, ID_K_VL);
	addLHS(58, _T("[y]") ,_T("color") ,_T("green"), EQ, 17, ID_K_K);
	addLHS(59, _T("[z]") ,_T("color") ,_T("red"),	EQ, 17, ID_K_K);


	//Production 18
	addLHS(60,  _T("[x]") ,_T("color") ,_T("blue"), EQ, 18, ID_K_K);
	addLHS(61, _T("[y]") ,_T("on") ,_T("table"),	EQ, 18, ID_K_K);
	addLHS(62, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 18, ID_K_VL);
	
	//Production 19
	addLHS(63, _T("[x]") ,_T("color") ,_T("blue"),	EQ, 19, ID_K_K);
	addLHS(64, _T("[y]") ,_T("left of"),_T("block3"),EQ,19, ID_K_K);
	addLHS(65, _T("[y]") ,_T("left of"),_T("[z]"),	EQ, 19, ID_K_VL);

	

	//Production 20
	addLHS(66, _T("[x]") ,_T("up") ,_T("[y]"),		EQ, 20, ID_K_VL);
	addLHS(67, _T("[y]") ,_T("right of") ,_T("[z]"),EQ,	20, ID_K_VL);
	addLHS(68, _T("[z]") ,_T("size") ,_T("30"),		ET,	20, ID_K_K);


	//Production 21
	addLHS(69, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 21, ID_K_VL);
	addLHS(70, _T("[y]") ,_T("right of") ,_T("[z]"),EQ, 21, ID_K_VL);
	addLHS(71, _T("[z]") ,_T("color") ,_T("blue"),  EQ, 21, ID_K_K);
	addLHS(72, _T("[z]") ,_T("on") ,_T("table"),	EQ, 21, ID_K_K);

	//Production 22
	addLHS(73, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 22, ID_K_VL);
	addLHS(74, _T("[y]") ,_T("right of") ,_T("[z]"),EQ, 22, ID_K_VL);
	addLHS(75, _T("[z]") ,_T("color") ,_T("blue"),  EQ, 22, ID_K_K);
	addLHS(76, _T("[z]") ,_T("color") ,_T("red"),   EQ, 22, ID_K_K);


	//Production 23
	addLHS(77,  _T("[x]") ,_T("color") ,_T("blue"), EQ, 23, ID_K_K);
	addLHS(78, _T("[x]") ,_T("up") ,_T("[y]"),		EQ, 23, ID_K_VL);
	addLHS(79, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 23, ID_K_VL);
	
	//Production 24
	addLHS(80, _T("[x]") ,_T("color") ,_T("blue"),  EQ, 24, ID_K_K);
	addLHS(81, _T("[x]") ,_T("right of") ,_T("[y]"),EQ, 24, ID_K_VL);
	addLHS(82, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 24, ID_K_VL);

	

	//Production 25
	addLHS(83, _T("[x]") ,_T("up") ,_T("[y]"),		EQ, 25, ID_K_VL);
	addLHS(84, _T("[y]") ,_T("right of") ,_T("[z]"),EQ, 25, ID_K_VL);
	addLHS(85, _T("[z]") ,_T("size") ,_T("10"),		LT, 25, ID_K_K);

	//Production 26
	addLHS(86, _T("[x]") ,_T("up") ,_T("[y]"),		EQ, 26, ID_K_VL);
	addLHS(87, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 26, ID_K_VL);
	addLHS(88, _T("[z]") ,_T("color") ,_T("blue"),  EQ, 26, ID_K_K);
	addLHS(89, _T("[z]") ,_T("on") ,_T("table"),    EQ, 26, ID_K_K);

	//Production 27
	addLHS(90, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 27, ID_K_VL);
	addLHS(91, _T("[y]") ,_T("left of") ,_T("[z]"), EQ, 27, ID_K_VL);
	addLHS(92, _T("[z]") ,_T("color") ,_T("green"), EQ, 27, ID_K_K);
	addLHS(93, _T("[z]") ,_T("color") ,_T("red"),   EQ, 27, ID_K_K);


	//Production 28
	addLHS(94,  _T("[x]") ,_T("color") ,_T("blue"), EQ, 28, ID_K_K);
	addLHS(95, _T("[x]") ,_T("under") ,_T("[y]"),	EQ, 28, ID_K_VL);
	addLHS(96, _T("[y]") ,_T("under") ,_T("[z]"),   EQ, 28, ID_K_VL);
	
	//Production 29
	addLHS(97, _T("[a]") ,_T("color") ,_T("blue"),  EQ, 29, ID_K_K);
	addLHS(98, _T("[b]") ,_T("under") ,_T("[y]"),   EQ, 29, ID_K_VL);
	addLHS(99, _T("[b]") ,_T("left of") ,_T("[z]"), EQ, 29, ID_K_VL);

	

	//Production 30
	addLHS(100, _T("[x]") ,_T("up") ,_T("[y]"),		EQ, 30, ID_K_VL);
	addLHS(101, _T("[y]") ,_T("right of") ,_T("[z]"),EQ, 30, ID_K_VL);
	addLHS(102, _T("[z]") ,_T("size") ,_T("10"),	GT, 30, ID_K_K);

	//Production 31
	addLHS(103, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 31, ID_K_VL);
	addLHS(104, _T("[y]") ,_T("left of") ,_T("[z]"),EQ, 31, ID_K_VL);
	addLHS(105, _T("[z]") ,_T("color") ,_T("blue"), EQ, 31, ID_K_K);
	addLHS(106, _T("[z]") ,_T("under") ,_T("table"),EQ, 31, ID_K_K);

	//Production 32
	addLHS(107, _T("[a]") ,_T("on") ,_T("[b]"),		EQ, 32, ID_K_VL);
	addLHS(108, _T("[b]") ,_T("under") ,_T("[c]"),	EQ, 32, ID_K_VL);
	addLHS(109, _T("[z]") ,_T("color") ,_T("blue"), EQ, 32,ID_K_K);
	addLHS(110, _T("[z]") ,_T("color") ,_T("red"),	EQ, 32, ID_K_K);


	//Production 33
	addLHS(111,  _T("[a]") ,_T("color") ,_T("blue"),EQ, 33, ID_K_K);
	addLHS(112, _T("[b]") ,_T("up") ,_T("[y]"),		EQ, 33, ID_K_VL);  
	addLHS(113, _T("[b]") ,_T("left of") ,_T("[z]"),EQ, 33, ID_K_VL);
	
	//Production 34
	addLHS(114, _T("[x]") ,_T("color") ,_T("red"),	EQ, 34, ID_K_K);
	addLHS(115, _T("[x]") ,_T("left of") ,_T("[y]"),EQ, 34, ID_K_VL);
	addLHS(116, _T("[y]") ,_T("left of") ,_T("[z]"),EQ, 34, ID_K_VL);

	

	//Production 35
	addLHS(117, _T("[x]") ,_T("up") ,_T("[y]"),		EQ, 35, ID_K_VL);
	addLHS(118, _T("[y]") ,_T("right of") ,_T("[z]"),EQ, 35, ID_K_VL);
	addLHS(119, _T("[y]") ,_T("size") ,_T("10"),	GE, 35, ID_K_K);

	//Production 36
	addLHS(120, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 36, ID_K_VL);
	addLHS(121, _T("[y]") ,_T("right of") ,_T("[z]"), EQ, 36, ID_K_VL);
	addLHS(122, _T("[y]") ,_T("color") ,_T("blue"), EQ, 36, ID_K_K);
	addLHS(123, _T("[y]") ,_T("under") ,_T("table"),EQ,36, ID_K_K);

	//Production 37
	addLHS(124, _T("[x]") ,_T("on") ,_T("[y]"),		EQ, 37, ID_K_VL);
	addLHS(125, _T("[x]") ,_T("left of") ,_T("[z]"),EQ, 37, ID_K_VL);
	addLHS(126, _T("[x]") ,_T("color") ,_T("blue"), EQ, 37, ID_K_K);
	addLHS(127, _T("[z]") ,_T("color") ,_T("red"),	EQ, 37, ID_K_K);


	//Production 38
	addLHS(128,  _T("[a]") ,_T("color") ,_T("blue"),EQ, 38, ID_K_K);
	addLHS(129, _T("[a]") ,_T("under") ,_T("[y]"),  EQ, 38, ID_K_VL);
	addLHS(130, _T("[b]") ,_T("left of") ,_T("[z]"),EQ, 38, ID_K_VL);
	
	//Production 39
	addLHS(131, _T("[x]") ,_T("color") ,_T("green"),EQ, 39, ID_K_K);
	addLHS(132, _T("[x]") ,_T("right of") ,_T("[y]"),EQ, 39, ID_K_VL);
	addLHS(133, _T("[y]") ,_T("right of") ,_T("[z]"), EQ, 39, ID_K_VL);

	

	//Production 40
	addLHS(134, _T("[x]") ,_T("up") ,_T("[y]"),		EQ, 40, ID_K_VL);
	addLHS(135, _T("[y]") ,_T("right of") ,_T("[z]"), EQ, 40, ID_K_VL);
	addLHS(136, _T("[y]") ,_T("size") ,_T("10"),	LT, 40, ID_K_K);
*/


}





bool CAipi_LHS::compareEqualCond(int cond1, int cond2)
{
	findLHSMembers(cond1);
	
	tstring Id1		= m_lhsId;
	tstring Attr1	= m_lhsAttr;
	tstring Val1	= m_lhsVal;
	int		Rel1	= m_Rel;

	findLHSMembers(cond2);
	
	tstring Id2		= m_lhsId;
	tstring Attr2	= m_lhsAttr;
	tstring Val2	= m_lhsVal;
	int		Rel2	= m_Rel;

	if( Id1 == Id2 && Attr1 == Attr2 && Val1 == Val2 && Rel1 == Rel2 )
	{
		return true;
	}

return false;
}


bool CAipi_LHS::compareEqualCondIForm(int cond1, int cond2)
{
	findLHSMembersIForm(cond1);
	
	double Id1		= m_lhsIdIForm;
	double Attr1		= m_lhsAttrIForm;
	double Val1		= m_lhsValIForm;
	int	 Rel1		= m_Rel;

	findLHSMembersIForm(cond2);
	
	double Id2		= m_lhsIdIForm;
	double Attr2		= m_lhsAttrIForm;
	double Val2		= m_lhsValIForm;
	int	 Rel2		= m_Rel;

	if( Id1 == Id2 && Attr1 == Attr2 && Val1 == Val2 && Rel1 == Rel2 )
	{
		return true;
	}

return false;
}




void CAipi_LHS::printRepCond()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Repeated Conditions  *******"));
	//Print map container
	for( CMainFrame::g_mmRepCond::const_iterator iter = pMainFrame->gmmRepCond.begin(); iter!= pMainFrame->gmmRepCond.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strPM = _T("P");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Repeated Condition Element  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		
		CAipi_RepCond rco = (CAipi_RepCond) iter->second;
		int c2 = rco.getRepCond();
		int pm1 = rco.getPM1();
		int pm2 = rco.getPM2();
		
		strCond =_T("C");
		strCond +=  _itot( c2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		
		strPM +=  _itot( pm1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
		strPM = _T("P");
		strPM +=  _itot( pm2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
	}


}


void CAipi_LHS::printLHS()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Left Hand Side  *******"));
	//Print map container
	for( CMainFrame::g_mLHS::const_iterator iter = pMainFrame->gmLHS.begin(); iter!= pMainFrame->gmLHS.end(); ++iter)
	{
		CString strRel;
		CString strCond =_T("C");
		strCond +=  _itot( iter->first, buffer, 10 );
		tstring i = findLHSId(iter->first);
		tstring a = findLHSAttr(iter->first);
		tstring v = findLHSVal(iter->first);

		CAipi_LHS lhso = (CAipi_LHS)iter->second;
		int	rel	  = lhso.getRel();
		int pm	  = lhso.getPM();
		int categ = lhso.getCategory();
		//int type  = lhso.getType();
		
		
		switch(rel)
		{
		case 100: 
			strRel =_T("EQ");
		break;
		case 101: 
			strRel =_T("LT");
		break;
		case 102: 
			strRel =_T("LE");
		break;
		case 103: 
			strRel =_T("GT");
		break;
		case 104: 
			strRel =_T("GE");
		break;
		case 105: 
			strRel =_T("ET");
		break;
		case 106: 
			strRel =_T("NE");
		break;
		case 107: 
			strRel =_T("AS");
		break;

		}
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LHS  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		pMainFrame->m_wndOutputTabView.AddMsg1(i.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(a.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(v.data());
		
		pMainFrame->m_wndOutputTabView.AddMsg1(strRel);
		CString strPM =_T("PM");
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		CString strCateg =_T("CATEG_");
		strCateg +=  _itot( categ, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCateg);
		
		/*
		CString strType =_T("TYPE_");
		strType +=  _itot( type, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strType);
		*/
	}

}


void CAipi_LHS::printLHSIForm()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Left Hand Side  *******"));
	//Print map container
	for( CMainFrame::g_mLHS::const_iterator iter = pMainFrame->gmLHS.begin(); iter!= pMainFrame->gmLHS.end(); ++iter)
	{
		CString strRel;
		CString strCond =_T("C");
		CString strIdIForm = _T("ID_");
		CString strAttrIForm = _T("ATTR_");
		CString strValIForm = _T("VAL_");

		strCond +=  _itot( iter->first, buffer, 10 );
		tstring i = findLHSId(iter->first);
		tstring a = findLHSAttr(iter->first);
		tstring v = findLHSVal(iter->first);

		double	i_iform = findLHSIdIForm( iter->first);
		double	a_iform = findLHSAttrIForm( iter->first);
		double	v_iform = findLHSValIForm( iter->first);

		CAipi_LHS lhso = (CAipi_LHS)iter->second;
		int	rel	  = lhso.getRel();
		int pm	  = lhso.getPM();
		int categ = lhso.getCategory();
		//int type  = lhso.getType();
		
		
		switch(rel)
		{
		case 320: 
			strRel =_T("EQ");
		break;
		case 60: 
			strRel =_T("LT");
		break;
		case 321: 
			strRel =_T("LE");
		break;
		case 62: 
			strRel =_T("GT");
		break;
		case 322: 
			strRel =_T("GE");
		break;
		case 323: 
			strRel =_T("ET");
		break;
		case 324: 
			strRel =_T("NE");
		break;
		case 61: 
			strRel =_T("AS");
		break;

		}
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LHS  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		pMainFrame->m_wndOutputTabView.AddMsg1(i.data());
		
		strIdIForm.Format(_T("%f"), i_iform );
		pMainFrame->m_wndOutputTabView.AddMsg1(strIdIForm);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(a.data());

		strAttrIForm.Format(_T("%f"), a_iform );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAttrIForm);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(v.data());

		strValIForm.Format(_T("%f"), v_iform );
		pMainFrame->m_wndOutputTabView.AddMsg1(strValIForm);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(strRel);
		
		CString strPM =_T("PM");
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
		CString strCateg =_T("CATEG_");
		strCateg +=  _itot( categ, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCateg);
		
		/*
		CString strType =_T("TYPE_");
		strType +=  _itot( type, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strType);
		*/
	}

}