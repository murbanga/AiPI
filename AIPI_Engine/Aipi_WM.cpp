// Aipi_WM.cpp: implementation of the CAipi_WM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_WM.h"


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

CAipi_WM::CAipi_WM()
{

}

CAipi_WM::~CAipi_WM()
{
	
}


CAipi_WM* CAipi_WM::addWM(int wm, tstring id, tstring attr, tstring val, int type, int time )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_WM *pObject = new CAipi_WM();
    try
	{
		pObject->setId(id);
		pObject->setAttr(attr);
		pObject->setVal(val);
		pObject->setType(type);
		pObject->setTime(time);
		
		
		pMainFrame->gmWM.insert(CMainFrame::g_mWM::value_type(wm, *pObject));
		
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


CAipi_WM* CAipi_WM::addWMIForm(int wm, double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int type, int time)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_WM *pObject = new CAipi_WM();
    try
	{
		pObject->setIdIForm(id_iform);
		pObject->setAttrIForm(attr_iform);
		pObject->setValIForm(val_iform);
		pObject->setId(id);
		pObject->setAttr(attr);
		pObject->setVal(val);
		pObject->setType(type);
		pObject->setTime(time);
		
		pMainFrame->gmWM.insert(CMainFrame::g_mWM::value_type(wm, *pObject));
		
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


int CAipi_WM::editWM(int wm, tstring id, tstring attr, tstring val, int type)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mWM::iterator iterWM;
	
	iterWM = pMainFrame->gmWM.find(wm);
	if( iterWM != pMainFrame->gmWM.end())
	{
		eraseWM(wm);
		int time = lastWMTime();
		++time;
		addWM(wm, id, attr, val, type, time);
		return wm;
		
	}		

return NOT_FOUND;

}

int CAipi_WM::editWMIForm(int wm, double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int type)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mWM::iterator iterWM;
	
	iterWM = pMainFrame->gmWM.find(wm);
	if( iterWM != pMainFrame->gmWM.end())
	{
		eraseWM(wm);
		int time = lastWMTime();
		++time;
		addWMIForm(wm, id_iform, attr_iform, val_iform, id, attr, val, type, time);
		return wm;
		
	}		

return NOT_FOUND;

}




void CAipi_WM::clearWM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmWM.clear();
}


void CAipi_WM::clearWMCondStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmEQ_WM_Cond.clear();
	pMainFrame->gmmET_WM_Cond.clear();
	pMainFrame->gmmNE_WM_Cond.clear();
	pMainFrame->gmmGT_WM_Cond.clear();
	pMainFrame->gmmGE_WM_Cond.clear();
	pMainFrame->gmmLT_WM_Cond.clear();
	pMainFrame->gmmLE_WM_Cond.clear();
	pMainFrame->gmmAS_WM_Cond.clear();
}

void CAipi_WM::clearCondWMStructs()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmEQ_Cond_WM.clear();
	pMainFrame->gmET_Cond_WM.clear();
	pMainFrame->gmNE_Cond_WM.clear();
	pMainFrame->gmGT_Cond_WM.clear();
	pMainFrame->gmGE_Cond_WM.clear();
	pMainFrame->gmLT_Cond_WM.clear();
	pMainFrame->gmLE_Cond_WM.clear();
	pMainFrame->gmAS_Cond_WM.clear();
	
}



int CAipi_WM::eraseWM(int wm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mWM::iterator iter;
    iter = pMainFrame->gmWM.find(wm);
	if( iter != pMainFrame->gmWM.end())
	{
  		pMainFrame->gmWM.erase(wm);
		return wm;
	}
	
	
	return NOT_FOUND;
}


bool CAipi_WM::compareEqualWM(int wm1, int wm2)
{
	findWMMembers(wm1);
	
	tstring Id1		= m_Id;
	tstring Attr1	= m_Attr;
	tstring Val1	= m_Val;

	findWMMembers(wm2);
	
	tstring Id2		= m_Id;
	tstring Attr2	= m_Attr;
	tstring Val2	= m_Val;

	if( Id1 == Id2 && Attr1 == Attr2 && Val1 == Val2 )
	{
		return true;
	}

return false;
}


bool CAipi_WM::compareEqualWMIForm(int wm1, int wm2)
{
	findWMMembersIForm(wm1);
	
	double Id1	=	m_IdIForm;
	double Attr1	=	m_AttrIForm;
	double Val1	=	m_ValIForm;

	findWMMembersIForm(wm2);
	
	double Id2	=	m_IdIForm;
	double Attr2	=	m_AttrIForm;
	double Val2	=	m_ValIForm;

	if( Id1 == Id2 && Attr1 == Attr2 && Val1 == Val2 )
	{
		return true;
	}

return false;
}

double CAipi_WM::findWMIdIForm( int wm )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mWM::iterator iter;
    iter = pMainFrame->gmWM.find(wm);
	if( iter != pMainFrame->gmWM.end())
	{
  		CAipi_WM id = (CAipi_WM)iter->second;
 		return id.getIdIForm();
	}
	
	return NOT_FOUND;
	
}


double CAipi_WM::findWMAttrIForm( int wm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWM::iterator iter;
    iter = pMainFrame->gmWM.find(wm);
	if( iter != pMainFrame->gmWM.end())
	{
  		CAipi_WM attr = (CAipi_WM)iter->second;
		return attr.getAttrIForm();
	}
	
	return NOT_FOUND;

			

}

double CAipi_WM::findWMValIForm( int wm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWM::iterator iter;
    iter = pMainFrame->gmWM.find(wm);
	if( iter != pMainFrame->gmWM.end())
	{
  		CAipi_WM val = (CAipi_WM)iter->second;
 		return val.getValIForm();
	}
	
	
return NOT_FOUND;
	

}



tstring CAipi_WM::findWMId( int wm )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mWM::iterator iter;
    iter = pMainFrame->gmWM.find(wm);
	if( iter != pMainFrame->gmWM.end())
	{
  		CAipi_WM id = (CAipi_WM)iter->second;
 		return id.getId();
	}
	
	return _T("NOT_FOUND");
	
}


tstring CAipi_WM::findWMAttr( int wm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWM::iterator iter;
    iter = pMainFrame->gmWM.find(wm);
	if( iter != pMainFrame->gmWM.end())
	{
  		CAipi_WM attr = (CAipi_WM)iter->second;
		return attr.getAttr();
	}
	
	return _T("NOT_FOUND");

			

}

tstring CAipi_WM::findWMVal( int wm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWM::iterator iter;
    iter = pMainFrame->gmWM.find(wm);
	if( iter != pMainFrame->gmWM.end())
	{
  		CAipi_WM val = (CAipi_WM)iter->second;
 		return val.getVal();
	}
	
	
return _T("NOT_FOUND");
	

}

int CAipi_WM::findWMType( int wm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWM::iterator iter;
    iter = pMainFrame->gmWM.find(wm);
	if( iter != pMainFrame->gmWM.end())
	{
  		CAipi_WM val = (CAipi_WM)iter->second;
 		return val.getType();
	}
	
	
return NOT_FOUND;
	

}


int CAipi_WM::findWMTime( int wm )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWM::iterator iter;
    iter = pMainFrame->gmWM.find(wm);
	if( iter != pMainFrame->gmWM.end())
	{
  		CAipi_WM val = (CAipi_WM)iter->second;
 		return val.getTime();
	}
	
	
return NOT_FOUND;
	

}


int CAipi_WM::findWMMembers(int wm)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWM::iterator iter;
    iter = pMainFrame->gmWM.find(wm);
	if( iter != pMainFrame->gmWM.end())
	{
		CAipi_WM wmo = (CAipi_WM)iter->second;
 	
		m_Id = wmo.getId();
		m_Attr = wmo.getAttr();
		m_Val = wmo.getVal();
		m_Type = wmo.getType();
		m_Time = wmo.getTime();

		return wm;
	}
	
return NOT_FOUND;
	
}

int CAipi_WM::findWMMembersIForm(int wm)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWM::iterator iter;
    iter = pMainFrame->gmWM.find(wm);
	if( iter != pMainFrame->gmWM.end())
	{
		CAipi_WM wmo = (CAipi_WM)iter->second;
 	
		m_IdIForm	= wmo.getIdIForm();
		m_AttrIForm	= wmo.getAttrIForm();
		m_ValIForm	= wmo.getValIForm();
		m_Id		= wmo.getId();
		m_Attr		= wmo.getAttr();
		m_Val		= wmo.getVal();
		m_Type		= wmo.getType();
		m_Time		= wmo.getTime();

		return wm;
	}
	
return NOT_FOUND;
	
}


int CAipi_WM::findWM(double id, double attr, double val)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		int w = iter->first;
		CAipi_WM wm = (CAipi_WM)iter->second;
 		double id_iform = wm.getIdIForm();
		double attr_iform = wm.getAttrIForm();
		double val_iform = wm.getValIForm();

		if( id_iform == id && attr_iform == attr && val_iform == val )
		{
			return w;
		}
	}
	
return NOT_FOUND;
	
}
/////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
/// Searchs for constant data /////
////////////////////////////////////////////////////////////////////////////////////////

CAipi_WM::findEQ_Cond_WM(int c )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mEQ_Cond_WM::iterator iter;
    iter = pMainFrame->gmEQ_Cond_WM.find(c);
	if( iter != pMainFrame->gmEQ_Cond_WM.end())
	{
  		return iter->second;
 	}

return NOT_FOUND;	

}


CAipi_WM::findET_Cond_WM(int c )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mET_Cond_WM::iterator iter;
    iter = pMainFrame->gmET_Cond_WM.find(c);
	if( iter != pMainFrame->gmET_Cond_WM.end())
	{
  		return iter->second;
 	}

return NOT_FOUND;	

}

CAipi_WM::findNE_Cond_WM(int c )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mNE_Cond_WM::iterator iter;
    iter = pMainFrame->gmNE_Cond_WM.find(c);
	if( iter != pMainFrame->gmNE_Cond_WM.end())
	{
  		return iter->second;
 	}

return NOT_FOUND;	

}


CAipi_WM::findGT_Cond_WM(int c )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mGT_Cond_WM::iterator iter;
    iter = pMainFrame->gmGT_Cond_WM.find(c);
	if( iter != pMainFrame->gmGT_Cond_WM.end())
	{
  		return iter->second;
 	}

return NOT_FOUND;	

}


CAipi_WM::findGE_Cond_WM(int c )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mGE_Cond_WM::iterator iter;
    iter = pMainFrame->gmGE_Cond_WM.find(c);
	if( iter != pMainFrame->gmGE_Cond_WM.end())
	{
  		return iter->second;
 	}

return NOT_FOUND;	

}

CAipi_WM::findLT_Cond_WM(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mLT_Cond_WM::iterator iter;
    iter = pMainFrame->gmLT_Cond_WM.find(c);
	if( iter != pMainFrame->gmLT_Cond_WM.end())
	{
  		return iter->second;
 	}

return NOT_FOUND;	

}

CAipi_WM::findLE_Cond_WM(int c )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mLE_Cond_WM::iterator iter;
    iter = pMainFrame->gmLE_Cond_WM.find(c);
	if( iter != pMainFrame->gmLE_Cond_WM.end())
	{
  		return iter->second;
 	}

return NOT_FOUND;	

}


CAipi_WM::findAS_Cond_WM(int c )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mAS_Cond_WM::iterator iter;
    iter = pMainFrame->gmAS_Cond_WM.find(c);
	if( iter != pMainFrame->gmAS_Cond_WM.end())
	{
  		return iter->second;
 	}

return NOT_FOUND;	

}









/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//// Inserts constant data /////
////////////////////////////////////////////////////////////////////////////////////////////

int CAipi_WM::insertEQ_WM_Cond(int c, tstring id, tstring attr, tstring val)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembers(iter->first);

		if( (m_Id == id) && (m_Attr == attr) && (m_Val == val))
		{
			pMainFrame->gmmEQ_WM_Cond.insert(CMainFrame::g_mmEQ_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmEQ_Cond_WM.insert(CMainFrame::g_mEQ_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;
}


int CAipi_WM::insertEQ_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembersIForm(iter->first);

		if( (m_IdIForm == id_iform) && (m_AttrIForm == attr_iform) && (m_ValIForm == val_iform))
		{
			pMainFrame->gmmEQ_WM_Cond.insert(CMainFrame::g_mmEQ_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmEQ_Cond_WM.insert(CMainFrame::g_mEQ_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;
}




int CAipi_WM::insertET_WM_Cond(int c, tstring id, tstring attr, tstring val)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembers(iter->first);

		if( (m_Id == id) && (m_Attr == attr) && (m_Val == val))
		{
			pMainFrame->gmmET_WM_Cond.insert(CMainFrame::g_mmET_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmET_Cond_WM.insert(CMainFrame::g_mET_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;
}


int CAipi_WM::insertET_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembersIForm(iter->first);

		if( (m_IdIForm == id_iform) && (m_AttrIForm == attr_iform) && (m_ValIForm == val_iform ))
		{
			pMainFrame->gmmET_WM_Cond.insert(CMainFrame::g_mmET_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmET_Cond_WM.insert(CMainFrame::g_mET_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;
}


int CAipi_WM::insertNE_WM_Cond(int c, tstring id, tstring attr, tstring val)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	int iVal = _ttoi(val.data());

	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembers(iter->first);

		int imVal = _ttoi(m_Val.data());

		if( (m_Id == id) && (m_Attr == attr) && (imVal != iVal))
		{
			pMainFrame->gmmNE_WM_Cond.insert(CMainFrame::g_mmNE_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmNE_Cond_WM.insert(CMainFrame::g_mNE_Cond_WM::value_type(c, iter->first));
			r = 1;
		}

	}

	return r;
}


int CAipi_WM::insertNE_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	
	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembersIForm(iter->first);
		
		if( (m_IdIForm == id_iform) && (m_AttrIForm == attr_iform) && (m_ValIForm != val_iform ))
		{
			pMainFrame->gmmNE_WM_Cond.insert(CMainFrame::g_mmNE_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmNE_Cond_WM.insert(CMainFrame::g_mNE_Cond_WM::value_type(c, iter->first));
			r = 1;
		}

	}

	return r;
}



int CAipi_WM::insertGT_WM_Cond(int c, tstring id, tstring attr, tstring val)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	int iVal = _ttoi(val.data());

	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembers(iter->first);
		int imVal = _ttoi(m_Val.data());

		if( (m_Id == id) && (m_Attr == attr) && (imVal > iVal))
		{
			pMainFrame->gmmGT_WM_Cond.insert(CMainFrame::g_mmGT_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmGT_Cond_WM.insert(CMainFrame::g_mGT_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;
}


int CAipi_WM::insertGT_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;
	
	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembersIForm(iter->first);
				
		if( (m_IdIForm == id_iform) && (m_AttrIForm == attr_iform) && (m_ValIForm > val_iform))
		{
			pMainFrame->gmmGT_WM_Cond.insert(CMainFrame::g_mmGT_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmGT_Cond_WM.insert(CMainFrame::g_mGT_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;
}



int CAipi_WM::insertGE_WM_Cond(int c, tstring id, tstring attr, tstring val)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	int iVal = _ttoi(val.data());

	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembers(iter->first);
		int imVal = _ttoi(m_Val.data());

		if( (m_Id == id) && (m_Attr == attr) && (imVal >= iVal))
		{
			pMainFrame->gmmGE_WM_Cond.insert(CMainFrame::g_mmGE_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmGE_Cond_WM.insert(CMainFrame::g_mGE_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;
}


int CAipi_WM::insertGE_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;
	
	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembersIForm(iter->first);
		
		if( (m_IdIForm == id_iform) && (m_AttrIForm == attr_iform) && (m_ValIForm >= val_iform))
		{
			pMainFrame->gmmGE_WM_Cond.insert(CMainFrame::g_mmGE_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmGE_Cond_WM.insert(CMainFrame::g_mGE_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;
}

int CAipi_WM::insertLT_WM_Cond(int c, tstring id, tstring attr, tstring val)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	int iVal = _ttoi(val.data());
	
	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembers(iter->first);
		int imVal = _ttoi(m_Val.data());


		if( (m_Id == id) && (m_Attr == attr) && (imVal < iVal))
		{
			pMainFrame->gmmLT_WM_Cond.insert(CMainFrame::g_mmLT_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmLT_Cond_WM.insert(CMainFrame::g_mLT_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;

}


int CAipi_WM::insertLT_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembersIForm(iter->first);
		
		
		if( (m_IdIForm == id_iform) && (m_AttrIForm == attr_iform) && (m_ValIForm < val_iform))
		{
			pMainFrame->gmmLT_WM_Cond.insert(CMainFrame::g_mmLT_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmLT_Cond_WM.insert(CMainFrame::g_mLT_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;

}

int CAipi_WM::insertLE_WM_Cond(int c, tstring id, tstring attr, tstring val)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	int iVal = _ttoi(val.data());

	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembers(iter->first);
		int imVal = _ttoi(m_Val.data());

		if( (m_Id == id) && (m_Attr == attr) && (imVal <= iVal))
		{
			pMainFrame->gmmLE_WM_Cond.insert(CMainFrame::g_mmLE_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmLE_Cond_WM.insert(CMainFrame::g_mLE_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;
}


int CAipi_WM::insertLE_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;
	
	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembersIForm(iter->first);
				
		if( (m_IdIForm == id_iform) && (m_AttrIForm == attr_iform) && (m_ValIForm <= val_iform))
		{
			pMainFrame->gmmLE_WM_Cond.insert(CMainFrame::g_mmLE_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmLE_Cond_WM.insert(CMainFrame::g_mLE_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;
}



int CAipi_WM::insertAS_WM_Cond(int c, tstring id, tstring attr, tstring val)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembers(iter->first);

		if( (m_Id == id) && (m_Attr == attr) && (m_Val == val))
		{
			pMainFrame->gmmAS_WM_Cond.insert(CMainFrame::g_mmAS_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmAS_Cond_WM.insert(CMainFrame::g_mAS_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;
}

int CAipi_WM::insertAS_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int r = NOT_FOUND;

	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		findWMMembersIForm(iter->first);

		if( (m_IdIForm == id_iform) && (m_AttrIForm == attr_iform) && (m_ValIForm == val_iform))
		{
			pMainFrame->gmmAS_WM_Cond.insert(CMainFrame::g_mmAS_WM_Cond::value_type(iter->first, c));
			pMainFrame->gmAS_Cond_WM.insert(CMainFrame::g_mAS_Cond_WM::value_type(c, iter->first));
			r = 1;
		}
	}

	return r;
}





int CAipi_WM::sizeWM()
{
	 CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWM::iterator iter;
    return pMainFrame->gmWM.size();

}


int CAipi_WM::lastWM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mWM::iterator iterWM;
	if( !pMainFrame->gmWM.empty())
	{
		iterWM = pMainFrame->gmWM.end(); 
		--iterWM;
		return iterWM->first;
	}

	return NOT_FOUND;
}

int CAipi_WM::lastWMTime()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mWM::iterator iterWM;
	if( !pMainFrame->gmWM.empty())
	{
		iterWM = pMainFrame->gmWM.end(); 
		--iterWM;
		//int wme = iterWM->first;
		CAipi_WM id = (CAipi_WM)iterWM->second;
 		return id.getTime();
	}

	return NOT_FOUND;
}


void CAipi_WM::SamplesNegated()
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 9.0, 9.1 
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"), S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("blue"), S_S_S, 0);
*/	


//////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 2.0, 9.2, 9.3, 13.1

	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"), S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"),  S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"),  S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"),  S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"),  S_S_S, 0);
	

////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Sample 1.0, 3.0, 3.1, 3.2, 3.3, 4.0, 4.1, 6.0, 6.1, 
	//Sample 8.0, 10.0, 10.1, 12.0, 12.2, 12.3, 12.4, 14.1,
	//Sample 14.4, 14.6, 14.7, 15.1, 24.0   
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"),S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"),S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 10.2 ,10.3, 10.4, 10.5, 14.2, 14.3, 14.5, 14.8
	//Sample 
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"), S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("yellow"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 11.0, 11.1, 11.2 

/*	
	
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"), S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("red"),S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"),S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"),S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("blue"),S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"),S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"),S_S_S, 0);
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 7.0, 12.1
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	//Missing W5
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"), S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("yellow"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);
*/



}



void CAipi_WM::SamplesConjuntiveNegations()
{
////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Sample 1.0, 3.0, 3.1, 3.2, 3.3, 4.0, 4.1, 6.0, 6.1, 
	//Sample 8.0, 10.0, 10.1, 12.0, 12.2, 12.3, 12.4, 14.1,
	//Sample 14.4, 14.6, 14.7, 15.1, 24.0   
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"),S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"),S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Sample 15.2   
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"), S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);
*/


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//Sample 15.3, 15.4, 15.5, 15.6, 16.1, 16.3, 17.1  
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block4") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"), S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 16.2, 16.4  
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block4") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(4,_T("block1") ,_T("left of") ,_T("block3"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"), S_S_S, 0);
	addWM(8,_T("block2") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);
*/

}



void CAipi_WM::SamplesRETE()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Sample 1.0, 3.0, 3.1, 3.2, 3.3, 4.0, 4.1, 6.0, 6.1, 
	//Sample 8.0, 10.0, 10.1, 12.0, 12.2, 12.3, 12.4, 14.1,
	//Sample 14.4, 14.6, 14.7, 15.1, 24.0   

/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"),S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"),S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);
*/


	//Sample 2.3   

	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"),S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("table"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	
	



}


void CAipi_WM::SamplesOrder()
{
/////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
	
	//Sample 22.0
	//Order Test  
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"),S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"), S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"), S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);

*/
///////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 24.1, 24.11, 24.12, 24.13, 24.14, 24.3, 24.4
//Order Test	
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"), S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);
*/

////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 24.41, 24.42
//Order Test	
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"), S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block1"), S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);
*/
////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 24.2
//Order Test	
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"),S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"),S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"), S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"), S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(12,_T("block4") ,_T("on") ,_T("block3"),S_S_S, 0);
*/



}





void CAipi_WM::SamplesNumeric()
{
/////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
	
	//Sample 23.5
	//Numeric Test
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"), S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);	
	addWM(12,_T("block1") ,_T("size") ,_T("2"), S_S_S, 0);
	addWM(13,_T("block2") ,_T("size") ,_T("4"), S_S_S, 0);
	addWM(14,_T("block3") ,_T("size") ,_T("6"), S_S_S, 0);
	addWM(15,_T("block4") ,_T("size") ,_T("8"), S_S_S, 0);	
*/

////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 23.0,  23.1, 23.2, 23.3, 25.0, 25.01, 25.02, 25.10, 26.0, 26.10, 26.11 26.12, 26,13,26.3
//Numeric Test
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"),S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"),S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"), S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"),S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"),S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"), S_S_S, 0);	
	addWM(12,_T("block1") ,_T("size") ,_T("2"), S_S_I, 0);
	addWM(13,_T("block2") ,_T("size") ,_T("4"), S_S_I, 0);
	addWM(14,_T("block3") ,_T("size") ,_T("6"), S_S_I, 0);
	addWM(15,_T("block4") ,_T("size") ,_T("8"),S_S_I, 0);	
*/	

////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample 23.4,  23.6, 26.20, 27, 27.01, 27.02, 27.03, 27.04, 27.1
//Numeric Test
/*
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block1") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block1") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(4,_T("block2") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(5,_T("block2") ,_T("left of") ,_T("block3"),S_S_S, 0);
	addWM(6,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(7,_T("block3") ,_T("left of") ,_T("block4"),S_S_S, 0);
	addWM(8,_T("block3") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(9,_T("block3") ,_T("color") ,_T("red"),S_S_S, 0);
	addWM(10,_T("block4") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(11,_T("block4") ,_T("on") ,_T("table"),S_S_S, 0);	
	addWM(12,_T("block1") ,_T("size") ,_T("2"), S_S_I, 0);
	addWM(13,_T("block2") ,_T("size") ,_T("4"), S_S_I, 0);
	addWM(14,_T("block3") ,_T("size") ,_T("6"), S_S_I, 0);
	addWM(15,_T("block4") ,_T("size") ,_T("8"),S_S_I, 0);	
	addWM(16,_T("block1") ,_T("area") ,_T("4.5"), S_S_D, 0);
	addWM(17,_T("block2") ,_T("area") ,_T("16.0"),S_S_D, 0);
	addWM(18,_T("block3") ,_T("area") ,_T("4.0"),S_S_D, 0);
	addWM(19,_T("block4") ,_T("area") ,_T("64.0"), S_S_D, 0);	
*/
 
////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////


//Sample 28.0
//Numeric Test

	//First Tower
/*	
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block2") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block3") ,_T("on") ,_T("block4"), S_S_S, 0);
	addWM(4,_T("block4") ,_T("on") ,_T("block5"), S_S_S, 0);
	
	//Second Tower
	  
	addWM(5,_T("block6") ,_T("on") ,_T("block7"),S_S_S, 0);
	addWM(6,_T("block7") ,_T("on") ,_T("block8"), S_S_S, 0);
	addWM(7,_T("block8") ,_T("on") ,_T("block9"),S_S_S, 0);
	addWM(8,_T("block9") ,_T("on") ,_T("block10"), S_S_S, 0);
	
	//Third Tower
	
	addWM(9,_T("block11") ,_T("on") ,_T("block12"),S_S_S, 0);
	addWM(10,_T("block12") ,_T("on") ,_T("block13"), S_S_S, 0);
	addWM(11,_T("block13") ,_T("on") ,_T("block14"),S_S_S, 0);	
	addWM(12,_T("block14") ,_T("on") ,_T("block15"), S_S_S, 0);
	
	//Left Sides
	  
	addWM(13,_T("block1") ,_T("left of") ,_T("block6"), S_S_S, 0);
	addWM(14,_T("block2") ,_T("left of") ,_T("block7"), S_S_S, 0);
	addWM(15,_T("block3") ,_T("left of") ,_T("block8"),S_S_S, 0);	
	addWM(16,_T("block4") ,_T("left of") ,_T("block9"), S_S_S, 0);
	addWM(17,_T("block5") ,_T("left of") ,_T("block10"),S_S_S, 0);
	addWM(18,_T("block6") ,_T("left of") ,_T("block11"),S_S_S, 0);
	addWM(19,_T("block7") ,_T("left of") ,_T("block12"), S_S_S, 0);
	addWM(20,_T("block8") ,_T("left of") ,_T("block13"),S_S_S, 0);
	addWM(21,_T("block9") ,_T("left of") ,_T("block14"),S_S_S, 0);
	addWM(22,_T("block10") ,_T("left of") ,_T("block15"), S_S_S, 0);

	//Colors

	addWM(23,_T("block1") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(24,_T("block2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(25,_T("block3") ,_T("color") ,_T("red"),S_S_S, 0);	
	addWM(26,_T("block4") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(27,_T("block5") ,_T("color") ,_T("blue"),S_S_S, 0);
	addWM(28,_T("block6") ,_T("color") ,_T("red"),S_S_S, 0);
	addWM(29,_T("block7") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(30,_T("block8") ,_T("color") ,_T("red"),S_S_S, 0);
	addWM(31,_T("block9") ,_T("color") ,_T("blue"),S_S_S, 0);
	addWM(32,_T("block10") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(33,_T("block11") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(34,_T("block12") ,_T("color") ,_T("red"),S_S_S, 0);
	addWM(35,_T("block13") ,_T("color") ,_T("blue"),S_S_S, 0);
	addWM(36,_T("block14") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(37,_T("block15") ,_T("color") ,_T("blue"), S_S_S, 0);	
	
	//Sizes
	
	addWM(38,_T("block1") ,_T("size") ,_T("4"), S_S_I, 0);
	addWM(39,_T("block2") ,_T("size") ,_T("4"), S_S_I, 0);
	addWM(40,_T("block3") ,_T("size") ,_T("4"),S_S_I, 0);	
	addWM(41,_T("block4") ,_T("size") ,_T("4"), S_S_I, 0);
	addWM(42,_T("block5") ,_T("size") ,_T("4"),S_S_I, 0);
	addWM(43,_T("block6") ,_T("size") ,_T("8"),S_S_I, 0);
	addWM(44,_T("block7") ,_T("size") ,_T("8"), S_S_I, 0);
	addWM(45,_T("block8") ,_T("size") ,_T("8"),S_S_I, 0);
	addWM(46,_T("block9") ,_T("size") ,_T("8"),S_S_I, 0);
	addWM(47,_T("block10") ,_T("size") ,_T("8"), S_S_I, 0);
	addWM(48,_T("block11") ,_T("size") ,_T("12"), S_S_I, 0);
	addWM(49,_T("block12") ,_T("size") ,_T("12"),S_S_I, 0);
	addWM(50,_T("block13") ,_T("size") ,_T("12"),S_S_I, 0);
	addWM(51,_T("block14") ,_T("size") ,_T("12"), S_S_I, 0);
	addWM(52,_T("block15") ,_T("size") ,_T("12"), S_S_I, 0);	
	
	//Areas   
	
	addWM(53,_T("block1") ,_T("area") ,_T("6"), S_S_D, 0);
	addWM(54,_T("block2") ,_T("area") ,_T("6"), S_S_D, 0);
	addWM(55,_T("block3") ,_T("area") ,_T("6"),S_S_D, 0);	
	addWM(56,_T("block4") ,_T("area") ,_T("6"), S_S_D, 0);
	addWM(57,_T("block5") ,_T("area") ,_T("6"),S_S_D, 0);
	addWM(58,_T("block6") ,_T("area") ,_T("8"),S_S_D, 0);
	addWM(59,_T("block7") ,_T("area") ,_T("8"), S_S_D, 0);
	addWM(60,_T("block8") ,_T("area") ,_T("8"),S_S_D, 0);
	addWM(61,_T("block9") ,_T("area") ,_T("8"),S_S_D, 0);
	addWM(62,_T("block10") ,_T("area") ,_T("8"), S_S_D, 0);
	addWM(63,_T("block11") ,_T("area") ,_T("10"), S_S_D, 0);
	addWM(64,_T("block12") ,_T("area") ,_T("10"),S_S_D, 0);
	addWM(65,_T("block13") ,_T("area") ,_T("10"),S_S_D, 0);
	addWM(66,_T("block14") ,_T("area") ,_T("10"), S_S_D, 0);
	addWM(67,_T("block15") ,_T("area") ,_T("10"), S_S_D, 0);	
	
*/


}


void CAipi_WM::SamplesDuplicateAttr()
{
////////////////////////////////////////////////////////////////////////////////////////////////////
	
//////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 5
	//Duplicate Tokens
	//Extract from Ph.Thesis Chapter 2.6
/*	
	addWME(1,_T("block1") ,_T("self") ,_T("block1"), S_S_S, 0);
*/	


}


void CAipi_WM::SamplesOPS5()
{
	
	addWM( 1,_T("person") ,_T("name") ,_T("Rob"), S_S_S, 1);
	addWM( 2,_T("person") ,_T("city_of_residence") ,_T("New_Haven"), S_S_S, 1);
	addWM( 3,_T("person") ,_T("name") ,_T("Lee"), S_S_S, 1);
	addWM( 4,_T("person") ,_T("city_of_residence") ,_T("Pittsburg"), S_S_S, 1);
	addWM( 5,_T("city") ,_T("name") ,_T("Pittsburg"), S_S_S, 1);
	addWM( 6,_T("city") ,_T("state") ,_T("PA"), S_S_S, 1);
	addWM( 7,_T("city") ,_T("country") ,_T("USA"), S_S_S, 1);
	
	
}


void CAipi_WM::SamplesBlockWord()
{
////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////
//Blocks World
//Initial State	
/*	
	addWM( 1,_T("block a") ,_T("is a") ,_T("block"), S_S_S, 1);
	addWM( 2,_T("block b") ,_T("is a") ,_T("block"), S_S_S, 1);
	addWM( 3,_T("block c") ,_T("is a") ,_T("block"), S_S_S, 1);
	addWM( 4,_T("block d") ,_T("is a") ,_T("block"), S_S_S, 1);
	addWM( 5,_T("block e") ,_T("is a") ,_T("block"), S_S_S, 1);
	addWM( 6,_T("block f") ,_T("is a") ,_T("block"), S_S_S, 1);
	
	addWM( 7,_T("stack 1") ,_T("is a") ,_T("stack"), S_S_S, 1);
	addWM( 8,_T("stack 2") ,_T("is a") ,_T("stack"), S_S_S, 1);
	
	addWM( 9,_T("block a") ,_T("on") ,_T("block b"), S_S_S, 1);
	addWM(10,_T("block b") ,_T("on") ,_T("block c"), S_S_S, 1);
	addWM(11,_T("block c") ,_T("on") ,_T("floor"),   S_S_S, 1);	
	addWM(12,_T("block d") ,_T("on") ,_T("block e"), S_S_S, 1);
	addWM(13,_T("block e") ,_T("on") ,_T("block f"), S_S_S, 1);
	addWM(14,_T("block f") ,_T("on") ,_T("floor"),   S_S_S, 1);
	
	addWM(15,_T("block a") ,_T("top") ,_T("stack 1"), S_S_S, 1);	
	addWM(16,_T("block d") ,_T("top") ,_T("stack 2"), S_S_S, 1);
	
	addWM(17,_T("block a") ,_T("belong") ,_T("stack 1"), S_S_S, 1);
	addWM(18,_T("block b") ,_T("belong") ,_T("stack 1"), S_S_S, 1);
	addWM(19,_T("block c") ,_T("belong") ,_T("stack 1"), S_S_S, 1);	
	addWM(20,_T("block d") ,_T("belong") ,_T("stack 2"), S_S_S, 1);
	addWM(21,_T("block e") ,_T("belong") ,_T("stack 2"), S_S_S, 1);
	addWM(22,_T("block f") ,_T("belong") ,_T("stack 2"), S_S_S, 1);
	
	addWM(23,_T("goal") ,_T("is") ,_T("move block to floor"),S_S_S, 1);	
	addWM(24,_T("goal") ,_T("is") ,_T("move block"),         S_S_S, 1);
	addWM(25,_T("goal") ,_T("is") ,_T("move other block"),   S_S_S, 1);	
	addWM(26,_T("goal") ,_T("is") ,_T("move block directly"),S_S_S, 1);
*/



}




void CAipi_WM::SamplesPumpingStation()
{
////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////

//Sample Pumping Station
/*	
	addWM(1,_T("block1") ,_T("is a") ,_T("block"), S_S_S, 0);
	addWM(2,_T("block2") ,_T("is a") ,_T("block"),S_S_S, 0);
	addWM(3,_T("motor1") ,_T("is a") ,_T("motor"), S_S_S, 0);
	addWM(4,_T("motor2") ,_T("is a") ,_T("motor"), S_S_S, 0);
	addWM(5,_T("pump1") ,_T("is a") ,_T("pump"), S_S_S, 0);
	addWM(6,_T("pump2") ,_T("is a") ,_T("pump"), S_S_S, 0);
	addWM(7,_T("line1") ,_T("is a") ,_T("line"), S_S_S, 0);
	addWM(8,_T("line2") ,_T("is a") ,_T("line"),S_S_S, 0);
	addWM(9,_T("line3") ,_T("is a") ,_T("line"), S_S_S, 0);
	addWM(10,_T("block1") ,_T("motor is") ,_T("motor1"), S_S_S, 0);
	addWM(11,_T("block1") ,_T("pump is") ,_T("pump1"), S_S_S, 0);
	addWM(12,_T("block1") ,_T("input line is") ,_T("line1"), S_S_S, 0);
	addWM(13,_T("block1") ,_T("output line is") ,_T("line2"), S_S_S, 0);
	addWM(14,_T("block2") ,_T("motor is") ,_T("motor2"), S_S_S, 0);
	addWM(15,_T("block2") ,_T("pump is") ,_T("pump2"), S_S_S, 0);
	addWM(16,_T("block2") ,_T("input line is") ,_T("line2"), S_S_S, 0);
	addWM(17,_T("block2") ,_T("output line is") ,_T("line3"), S_S_S, 0);
	addWM(18,_T("motor1") ,_T("nominal current") ,_T("1"), S_S_I, 0);
	addWM(19,_T("motor2") ,_T("nominal current") ,_T("1"), S_S_I, 0);
	addWM(20,_T("line1") ,_T("nominal pressure") ,_T("50"), S_S_I, 0);
	addWM(21,_T("line2") ,_T("nominal pressure") ,_T("100"), S_S_I, 0);
	addWM(22,_T("line3") ,_T("nominal pressure") ,_T("150"), S_S_I, 0);
	addWM(23,_T("line1") ,_T("current pressure") ,_T("50"), S_S_I, 0);
	addWM(24,_T("line2") ,_T("current pressure") ,_T("80"), S_S_I, 0);
	addWM(25,_T("line3") ,_T("current pressure") ,_T("120"), S_S_I, 0);
	addWM(26,_T("line1") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(27,_T("line2") ,_T("color") ,_T("blue"), S_S_S, 0);
	addWM(28,_T("line3") ,_T("color") ,_T("green"), S_S_S, 0);
	addWM(29,_T("line1") ,_T("heat status") ,_T("normal"), S_S_S, 0);
	addWM(30,_T("line2") ,_T("heat status") ,_T("high"), S_S_S, 0);
	addWM(31,_T("line3") ,_T("heat status") ,_T("low"), S_S_S, 0);


	//Sample 3
	addWM(50,_T("line1") ,_T("pressure status") ,_T("low"), S_S_S, 0);
	addWM(51,_T("line2") ,_T("pressure status") ,_T("normal"), S_S_S, 0);
	addWM(52,_T("line3") ,_T("pressure status") ,_T("low"), S_S_S, 0);

	//Sample 4
	addWM(53,_T("motor1") ,_T("status is") ,_T("bad"), S_S_S, 0);
	addWM(54,_T("motor2") ,_T("status is") ,_T("normal"), S_S_S, 0);
	addWM(55,_T("block1") ,_T("status is") ,_T("bad"), S_S_S, 0);
	addWM(56,_T("block2") ,_T("status is") ,_T("normal"), S_S_S, 0);
	
*/


}



void CAipi_WM::SamplesPerformance()
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Sample 20
	//Performance Test
/*	
	addWM(1,_T("block1") ,_T("on") ,_T("block2"), S_S_S, 0);
	addWM(2,_T("block2") ,_T("on") ,_T("block3"), S_S_S, 0);
	addWM(3,_T("block3") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(4,_T("block4") ,_T("on") ,_T("block5"), S_S_S, 0);
	addWM(5,_T("block5") ,_T("on") ,_T("block6"), S_S_S, 0);
	addWM(6,_T("block6") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(7,_T("block7") ,_T("on") ,_T("block8"), S_S_S, 0);
	addWM(8,_T("block8") ,_T("on") ,_T("block9"), S_S_S, 0);
	addWM(9,_T("block9") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(10,_T("block3") ,_T("left of") ,_T("block6"), S_S_S, 0);
	
	addWM(11,_T("block2") ,_T("left of") ,_T("block5"), S_S_S, 0);
	addWM(12,_T("block1") ,_T("left of") ,_T("block4"), S_S_S, 0);
	addWM(13,_T("block9") ,_T("right of") ,_T("block6"), S_S_S, 0);
	addWM(14,_T("block8") ,_T("right of") ,_T("block5"), S_S_S, 0);
	addWM(15,_T("block7") ,_T("right of") ,_T("block4"), S_S_S, 0);
	addWM(16,_T("block6") ,_T("left of") ,_T("block9"), S_S_S, 0);
	addWM(17,_T("block5") ,_T("left of") ,_T("block8"), S_S_S, 0);
	addWM(18,_T("block4") ,_T("left of") ,_T("block7"), S_S_S, 0);
	addWM(19,_T("block6") ,_T("right of") ,_T("block3"),S_S_S, 0);
	addWM(20,_T("block5") ,_T("right of") ,_T("block2"), S_S_S, 0);
	
	addWM(21,_T("block4") ,_T("right of") ,_T("block1"), S_S_S, 0);
	addWM(22,_T("block1") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(23,_T("block2") ,_T("color") ,_T("yellow"),S_S_S, 0);
	addWM(24,_T("block3") ,_T("color") ,_T("green"), S_S_S, 0);
	addWM(25,_T("block4") ,_T("color") ,_T("green"), S_S_S, 0);
	addWM(26,_T("block5") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(27,_T("block6") ,_T("color") ,_T("yellow"), S_S_S, 0);
	addWM(28,_T("block7") ,_T("color") ,_T("yellow"), S_S_S, 0);
	addWM(29,_T("block8") ,_T("color") ,_T("green"), S_S_S, 0);
	addWM(30,_T("block9") ,_T("color") ,_T("red"), S_S_S, 0);

	addWM(31,_T("block1") ,_T("under") ,_T("block2"), S_S_S, 0);
	addWM(32,_T("block2") ,_T("under") ,_T("block3"), S_S_S, 0);
	addWM(33,_T("block3") ,_T("under") ,_T("table"), S_S_S, 0);
	addWM(34,_T("block4") ,_T("under") ,_T("block5"), S_S_S, 0);
	addWM(35,_T("block5") ,_T("under") ,_T("block6"), S_S_S, 0);
	addWM(36,_T("block6") ,_T("under") ,_T("table"), S_S_S, 0);
	addWM(37,_T("block7") ,_T("under") ,_T("block8"), S_S_S, 0);
	addWM(38,_T("block8") ,_T("under") ,_T("block9"), S_S_S, 0);
	addWM(39,_T("block9") ,_T("under") ,_T("table"),S_S_S, 0);
	addWM(40,_T("block3") ,_T("up") ,_T("block6"), S_S_S, 0);
	
	addWM(41,_T("block2") ,_T("up") ,_T("block5"), S_S_S, 0);
	addWM(42,_T("block1") ,_T("up") ,_T("block4"), S_S_S, 0);
	addWM(43,_T("block9") ,_T("up") ,_T("block6"), S_S_S, 0);
	addWM(44,_T("block8") ,_T("up") ,_T("block5"), S_S_S, 0);
	addWM(45,_T("block7") ,_T("up") ,_T("block4"), S_S_S, 0);
	addWM(46,_T("block6") ,_T("up") ,_T("block9"), S_S_S, 0);
	addWM(47,_T("block5") ,_T("up") ,_T("block8"), S_S_S, 0);
	addWM(48,_T("block4") ,_T("up") ,_T("block7"), S_S_S, 0);
	addWM(49,_T("block6") ,_T("up") ,_T("block3"), S_S_S, 0);
	
	addWM(50,_T("block5") ,_T("up") ,_T("block2"), S_S_S, 0);
	addWM(51,_T("block4") ,_T("up") ,_T("block1"),S_S_S, 0);
	addWM(52,_T("block1") ,_T("size") ,_T("4"), S_S_S, 0);
	addWM(53,_T("block2") ,_T("size") ,_T("5"), S_S_S, 0);
	addWM(54,_T("block3") ,_T("size") ,_T("6"),S_S_S, 0);
	addWM(55,_T("block4") ,_T("size") ,_T("4"),S_S_S, 0);
	addWM(56,_T("block5") ,_T("size") ,_T("5"), S_S_S, 0);
	addWM(57,_T("block6") ,_T("size") ,_T("6"), S_S_S, 0);
	addWM(58,_T("block7") ,_T("size") ,_T("4"), S_S_S, 0);
	addWM(59,_T("block8") ,_T("size") ,_T("5"), S_S_S, 0);
	addWM(60,_T("block9") ,_T("size") ,_T("6"),S_S_S, 0);

	addWM(61,_T("block10") ,_T("on") ,_T("block20"),S_S_S, 0);
	addWM(62,_T("block20") ,_T("on") ,_T("block30"), S_S_S, 0);
	addWM(63,_T("block30") ,_T("on") ,_T("table"),S_S_S, 0);
	addWM(64,_T("block40") ,_T("on") ,_T("block50"),S_S_S, 0 );
	addWM(65,_T("block50") ,_T("on") ,_T("block60"), S_S_S, 0);
	addWM(66,_T("block60") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(67,_T("block70") ,_T("on") ,_T("block80"),S_S_S, 0);
	addWM(68,_T("block80") ,_T("on") ,_T("block90"), S_S_S, 0);
	addWM(69,_T("block90") ,_T("on") ,_T("table"), S_S_S, 0);
	addWM(70,_T("block30") ,_T("left of") ,_T("block60"), S_S_S, 0);
	
	addWM(71,_T("block20") ,_T("left of") ,_T("block50"), S_S_S, 0);
	addWM(72,_T("block10") ,_T("left of") ,_T("block40"), S_S_S, 0);
	addWM(73,_T("block90") ,_T("right of") ,_T("block60"), S_S_S, 0);
	addWM(74,_T("block80") ,_T("right of") ,_T("block50"), S_S_S, 0);
	addWM(75,_T("block70") ,_T("right of") ,_T("block40"), S_S_S, 0);
	addWM(76,_T("block60") ,_T("left of") ,_T("block90"), S_S_S, 0);
	addWM(77,_T("block50") ,_T("left of") ,_T("block80"), S_S_S, 0);
	addWM(78,_T("block40") ,_T("left of") ,_T("block70"), S_S_S, 0);
	addWM(79,_T("block60") ,_T("right of") ,_T("block30"), S_S_S, 0);
	
	addWM(80,_T("block50") ,_T("right of") ,_T("block20"),S_S_S, 0);
	addWM(81,_T("block40") ,_T("right of") ,_T("block10"), S_S_S, 0);
	addWM(82,_T("block10") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(83,_T("block20") ,_T("color") ,_T("yellow"), S_S_S, 0);
	addWM(84,_T("block30") ,_T("color") ,_T("green"), S_S_S, 0);
	addWM(85,_T("block40") ,_T("color") ,_T("green"), S_S_S, 0);
	addWM(86,_T("block50") ,_T("color") ,_T("red"), S_S_S, 0);
	addWM(87,_T("block60") ,_T("color") ,_T("yellow"), S_S_S, 0);
	addWM(88,_T("block70") ,_T("color") ,_T("yellow"), S_S_S, 0);
	addWM(89,_T("block80") ,_T("color") ,_T("green"), S_S_S, 0);
	addWM(90,_T("block90") ,_T("color") ,_T("red"), S_S_S, 0);

	addWM(91,_T("block10") ,_T("under") ,_T("block20"),S_S_S, 0);
	addWM(92,_T("block20") ,_T("under") ,_T("block30"), S_S_S, 0);
	addWM(93,_T("block30") ,_T("under") ,_T("table"), S_S_S, 0);
	addWM(94,_T("block40") ,_T("under") ,_T("block50"), S_S_S, 0);
	addWM(95,_T("block50") ,_T("under") ,_T("block60"), S_S_S, 0);
	addWM(96,_T("block60") ,_T("under") ,_T("table"), S_S_S, 0);
	addWM(97,_T("block70") ,_T("under") ,_T("block80"), S_S_S, 0);
	addWM(98,_T("block80") ,_T("under") ,_T("block90"), S_S_S, 0);
	addWM(99,_T("block90") ,_T("under") ,_T("table"), S_S_S, 0);
	addWM(100,_T("block30") ,_T("up") ,_T("block60"), S_S_S, 0);
	
	addWM(101,_T("block20") ,_T("up") ,_T("block50"), S_S_S, 0);
	addWM(102,_T("block10") ,_T("up") ,_T("block40"), S_S_S, 0);
	addWM(103,_T("block90") ,_T("up") ,_T("block60"), S_S_S, 0);
	addWM(104,_T("block80") ,_T("up") ,_T("block50"), S_S_S, 0);
	addWM(105,_T("block70") ,_T("up") ,_T("block40"), S_S_S, 0);
	addWM(106,_T("block60") ,_T("up") ,_T("block90"), S_S_S, 0);
	addWM(107,_T("block50") ,_T("up") ,_T("block80"), S_S_S, 0);
	addWM(108,_T("block40") ,_T("up") ,_T("block70"), S_S_S, 0);
	addWM(109,_T("block60") ,_T("up") ,_T("block30"), S_S_S, 0);
	addWM(110,_T("block50") ,_T("up") ,_T("block20"), S_S_S, 0);
	
	addWM(111,_T("block40") ,_T("up") ,_T("block10"), S_S_S, 0);
	addWM(112,_T("block10") ,_T("size") ,_T("4"), S_S_S, 0);
	addWM(113,_T("block20") ,_T("size") ,_T("5"), S_S_S, 0);
	addWM(114,_T("block30") ,_T("size") ,_T("6"), S_S_S, 0);
	addWM(115,_T("block40") ,_T("size") ,_T("4"), S_S_S, 0);
	addWM(116,_T("block50") ,_T("size") ,_T("5"),S_S_S, 0);
	addWM(117,_T("block60") ,_T("size") ,_T("6"), S_S_S, 0);
	addWM(118,_T("block70") ,_T("size") ,_T("4"), S_S_S, 0);
	addWM(119,_T("block80") ,_T("size") ,_T("5"), S_S_S, 0);
	addWM(120,_T("block90") ,_T("size") ,_T("6"), S_S_S, 0);

*/


}

void CAipi_WM::printWM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	CString strType;
	CString strTime;

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Working Memory  *******"));
	//Print map container
	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		int k= iter->first;
		findWMMembers(iter->first);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  WME  *******"));
		CString strWM =_T("W");
		strWM +=  _itot( iter->first, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		pMainFrame->m_wndOutputTabView.AddMsg1(m_Id.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(m_Attr.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(m_Val.data());
		
		strType =  _itot( m_Type, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strType);

		strTime =  _itot( m_Time, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTime);
	}


}


void CAipi_WM::printWMIForm()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	CString strType;
	CString strTime;
	CString strIdIForm;
	CString strAttrIForm;
	CString strValIForm;

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Working Memory  *******"));
	//Print map container
	for( CMainFrame::g_mWM::const_iterator iter = pMainFrame->gmWM.begin(); iter!= pMainFrame->gmWM.end(); ++iter)
	{
		int k= iter->first;
		findWMMembersIForm(iter->first);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  WME  *******"));
		CString strWM =_T("W");
		strWM +=  _itot( iter->first, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(m_Id.data());
		strIdIForm =  _itot( m_IdIForm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strIdIForm);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(m_Attr.data());
		strAttrIForm =  _itot( m_AttrIForm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAttrIForm);
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(m_Val.data());
		strValIForm =  _itot( m_ValIForm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strValIForm);
		
		strType =  _itot( m_Type, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strType);

		strTime =  _itot( m_Time, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTime);
	}


}



void CAipi_WM::printEQ_WM_Cond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Equality - Working Memory Condition  *******"));
	//Print map container
	for( CMainFrame::g_mmEQ_WM_Cond::const_iterator iter = pMainFrame->gmmEQ_WM_Cond.begin(); iter!= pMainFrame->gmmEQ_WM_Cond.end(); ++iter)
	{
		CString strWM =_T("W");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  EQ-WM-Cond  *******"));
		strWM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		strCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
			
	}


}


void CAipi_WM::printET_WM_Cond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Equal Than - Working Memory Condition  *******"));
	//Print map container
	for( CMainFrame::g_mmET_WM_Cond::const_iterator iter = pMainFrame->gmmET_WM_Cond.begin(); iter!= pMainFrame->gmmET_WM_Cond.end(); ++iter)
	{
		CString strWM =_T("W");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ET-WM-Cond  *******"));
		strWM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		strCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
			
	}


}


void CAipi_WM::printNE_WM_Cond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Non Equality - Working Memory Condition  *******"));
	//Print map container
	for( CMainFrame::g_mmNE_WM_Cond::const_iterator iter = pMainFrame->gmmNE_WM_Cond.begin(); iter!= pMainFrame->gmmNE_WM_Cond.end(); ++iter)
	{
		CString strWM =_T("W");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NE-WM-Cond  *******"));
		strWM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		strCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
			
	}


}

void CAipi_WM::printGT_WM_Cond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Greater Than - Working Memory Condition  *******"));
	//Print map container
	for( CMainFrame::g_mmGT_WM_Cond::const_iterator iter = pMainFrame->gmmGT_WM_Cond.begin(); iter!= pMainFrame->gmmGT_WM_Cond.end(); ++iter)
	{
		CString strWM =_T("W");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GT-WM-Cond  *******"));
		strWM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		strCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
			
	}


}


void CAipi_WM::printGE_WM_Cond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Greater or Equal Than - Working Memory Condition  *******"));
	//Print map container
	for( CMainFrame::g_mmGE_WM_Cond::const_iterator iter = pMainFrame->gmmGE_WM_Cond.begin(); iter!= pMainFrame->gmmGE_WM_Cond.end(); ++iter)
	{
		CString strWM =_T("W");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GE-WM-Cond  *******"));
		strWM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		strCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
			
	}


}

void CAipi_WM::printLT_WM_Cond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Lesser Than - Working Memory Condition  *******"));
	//Print map container
	for( CMainFrame::g_mmLT_WM_Cond::const_iterator iter = pMainFrame->gmmLT_WM_Cond.begin(); iter!= pMainFrame->gmmLT_WM_Cond.end(); ++iter)
	{
		CString strWM =_T("W");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LT-WM-Cond  *******"));
		strWM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		strCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
			
	}


}


void CAipi_WM::printLE_WM_Cond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Lesser or Equal Than - Working Memory Condition  *******"));
	//Print map container
	for( CMainFrame::g_mmLE_WM_Cond::const_iterator iter = pMainFrame->gmmLE_WM_Cond.begin(); iter!= pMainFrame->gmmLE_WM_Cond.end(); ++iter)
	{
		CString strWM =_T("W");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LE-WM-Cond  *******"));
		strWM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		strCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
			
	}


}


void CAipi_WM::printAS_WM_Cond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Assignation - Working Memory Condition  *******"));
	//Print map container
	for( CMainFrame::g_mmAS_WM_Cond::const_iterator iter = pMainFrame->gmmAS_WM_Cond.begin(); iter!= pMainFrame->gmmAS_WM_Cond.end(); ++iter)
	{
		CString strWM =_T("W");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AS-WM-Cond  *******"));
		strWM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
		strCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
			
	}


}



void CAipi_WM::printEQ_Cond_WM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Equality - Condition Working Memory *******"));
	//Print map container
	for( CMainFrame::g_mEQ_Cond_WM::const_iterator iter = pMainFrame->gmEQ_Cond_WM.begin(); iter!= pMainFrame->gmEQ_Cond_WM.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strWM =_T("W");
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  EQ-Cond-WM  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		strWM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
			
	}


}



void CAipi_WM::printET_Cond_WM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Equal Than - Condition Working Memory *******"));
	//Print map container
	for( CMainFrame::g_mET_Cond_WM::const_iterator iter = pMainFrame->gmET_Cond_WM.begin(); iter!= pMainFrame->gmET_Cond_WM.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strWM =_T("W");
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ET-Cond-WM  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		strWM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
			
	}


}


void CAipi_WM::printNE_Cond_WM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Non Equality - Condition Working Memory *******"));
	//Print map container
	for( CMainFrame::g_mNE_Cond_WM::const_iterator iter = pMainFrame->gmNE_Cond_WM.begin(); iter!= pMainFrame->gmNE_Cond_WM.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strWM =_T("W");
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NE-Cond-WM  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		strWM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
			
	}


}


void CAipi_WM::printGT_Cond_WM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Greater Than - Condition Working Memory *******"));
	//Print map container
	for( CMainFrame::g_mGT_Cond_WM::const_iterator iter = pMainFrame->gmGT_Cond_WM.begin(); iter!= pMainFrame->gmGT_Cond_WM.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strWM =_T("W");
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GT-Cond-WM  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		strWM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
			
	}


}


void CAipi_WM::printGE_Cond_WM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Greater or Equal Than - Condition Working Memory *******"));
	//Print map container
	for( CMainFrame::g_mGE_Cond_WM::const_iterator iter = pMainFrame->gmGE_Cond_WM.begin(); iter!= pMainFrame->gmGE_Cond_WM.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strWM =_T("W");
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GE-Cond-WM  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		strWM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
			
	}


}


void CAipi_WM::printLT_Cond_WM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Lesser Than - Condition Working Memory *******"));
	//Print map container
	for( CMainFrame::g_mLT_Cond_WM::const_iterator iter = pMainFrame->gmLT_Cond_WM.begin(); iter!= pMainFrame->gmLT_Cond_WM.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strWM =_T("W");
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LT-Cond-WM  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		strWM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
			
	}


}


void CAipi_WM::printLE_Cond_WM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Lesser Than - Condition Working Memory *******"));
	//Print map container
	for( CMainFrame::g_mLE_Cond_WM::const_iterator iter = pMainFrame->gmLE_Cond_WM.begin(); iter!= pMainFrame->gmLE_Cond_WM.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strWM =_T("W");
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LE-Cond-WM  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		strWM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
			
	}


}


void CAipi_WM::printAS_Cond_WM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Assignation - Condition Working Memory *******"));
	//Print map container
	for( CMainFrame::g_mAS_Cond_WM::const_iterator iter = pMainFrame->gmAS_Cond_WM.begin(); iter!= pMainFrame->gmAS_Cond_WM.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strWM =_T("W");
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AS-Cond-WM  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		strWM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
			
	}


}
