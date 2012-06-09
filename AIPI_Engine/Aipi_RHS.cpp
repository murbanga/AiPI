// Aipi_RHS.cpp: implementation of the CAipi_RHS class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RHS.h"

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

CAipi_RHS::CAipi_RHS()
{
	
}

CAipi_RHS::~CAipi_RHS()
{

}


CAipi_RHS* CAipi_RHS::addRHS(int rhs, tstring id, tstring attr, tstring val, int pm, int cmd)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RHS *pObject = new CAipi_RHS();
    try
	{
		pObject->setId(id);
		pObject->setAttr(attr);
		pObject->setVal(val);
		pObject->setPM(pm);
		pObject->setCommand(cmd);
			
		pMainFrame->gmRHS.insert(CMainFrame::g_mRHS::value_type(rhs, *pObject));
		pMainFrame->gmmPM_Fact.insert(CMainFrame::g_mmPM_Fact::value_type(pm, rhs));
		
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


CAipi_RHS* CAipi_RHS::addRHSIForm(int rhs, double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int pm, int cmd)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RHS *pObject = new CAipi_RHS();
    try
	{
		pObject->setIdIForm(id_iform);
		pObject->setAttrIForm(attr_iform);
		pObject->setValIForm(val_iform);
		pObject->setId(id);
		pObject->setAttr(attr);
		pObject->setVal(val);
		pObject->setPM(pm);
		pObject->setCommand(cmd);
			
		pMainFrame->gmRHS.insert(CMainFrame::g_mRHS::value_type(rhs, *pObject));
		pMainFrame->gmmPM_Fact.insert(CMainFrame::g_mmPM_Fact::value_type(pm, rhs));
		
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







int CAipi_RHS::editRHS(int rhs, tstring id, tstring attr, tstring val, int pm, int cmd)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mRHS::iterator iterRHS;
	
	iterRHS = pMainFrame->gmRHS.find(rhs);
	if( iterRHS != pMainFrame->gmRHS.end())
	{
		eraseRHS(rhs);
		addRHS(rhs, id, attr, val, pm, cmd);
		return rhs;
		
	}		

return NOT_FOUND;

}


int CAipi_RHS::editRHSIForm(int rhs, double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int pm, int cmd)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mRHS::iterator iterRHS;
	
	iterRHS = pMainFrame->gmRHS.find(rhs);
	if( iterRHS != pMainFrame->gmRHS.end())
	{
		eraseRHS(rhs);
		addRHSIForm(rhs, id_iform, attr_iform, val_iform, id, attr, val, pm, cmd);
		return rhs;
		
	}		

return NOT_FOUND;

}


int CAipi_RHS::execAssert(long pm, double if_id, double if_attr, double if_val, tstring s_id, tstring s_attr, tstring s_val )
{
	int r = NOT_FOUND;
	int type = S_S_S;
	
	//Search for the type of the WMEs
	CAipi_STableClass stclass;
	int attr_type = stclass.findAttrType(if_attr, if_id);
	if( attr_type != NOT_FOUND )
	{
		//AfxMessageBox(_T("Attr Type Encontrado"));
		switch( attr_type)
		{
			case AIPI_STRING:
				type = S_S_S;
				break;
			case AIPI_INT:
				type = S_S_I;
				break;
			case AIPI_LONG:
				type = S_S_L;
				break;
			case AIPI_FLOAT:
				type = S_S_F;
				break;
			case AIPI_DOUBLE:
				type = S_S_D;
				break;
		}
	}
	else
	{
		//Semantic error
		CAipi_Error err;
		CString strAttr = s_attr.data();
		CString  strDesc = _T("No class was found for identifier [") + strAttr + _T("]."); 
		//err.displayGUIError(UNKNOW_TYPE, SEMANT_ERROR, strDesc);
		//return;
	}
	
	
	CAipi_WM wm;
	//Check if working memory element already exist
	//Refraction
	int wme = wm.findWM(if_id, if_attr, if_val);
	if( wme == NOT_FOUND )
	{
		//AfxMessageBox(_T("EXEC ASSERT"));
		//Add new WME
		++g_currentWM;
		++g_currentTimeTag;
		
		wm.addWMIForm(g_currentWM, if_id, if_attr, if_val, s_id, s_attr, s_val, type , g_currentTimeTag);	
		
		//Update Alpha Memory with new WMEs
		CAipi_RETE_Net net;
		int am1 = net.assertUpdateAM(g_currentWM);
		if( am1 != UNDEFINE )
		{
			int c2 = net.assertUpdateBM(am1, g_currentWM, pm);
			CAipi_LHS lhso;
			long pm = lhso.findLHSPM(c2);
			
			/*
			CString st;
			st.Format(_T("Updated BM WME...%d  " ), g_currentWM);
			AfxMessageBox(st);
			st.Format(_T("Updated BM Cond...%d  " ), c2);
			AfxMessageBox(st);
			st.Format(_T("Cond belongs to PM...%d  " ), pm);
			AfxMessageBox(st);
			*/
			
			CAipi_RETE_PNode pno;
			int p = pno.definePNode(pm);
			if( p == P_UNSUCCESS )
			{
				return NOT_FOUND;
			}
			else
			{
				int f = pno.findRefraction(pm);
				if( f == NOT_FOUND )
				{
					pno.saveFiredPM(pm);
					/*
					st.Format(_T("SAVE FIRED PM...%d  " ), pm);
					AfxMessageBox(st);
					*/
				}
					
			}
		}
		
		r = FOUND;
	}
	
return r;
}


int CAipi_RHS::execRetract(double if_id, double if_attr, double if_val, tstring s_id, tstring s_attr, tstring s_val )
{
	int r = NOT_FOUND;
	
	int type = S_S_S;
	
	//Search for the type of the WMEs
	CAipi_STableClass stclass;
	int attr_type = stclass.findAttrType(if_attr, if_id);
	if( attr_type != NOT_FOUND )
	{
		//AfxMessageBox(_T("Attr Type Encontrado"));
		switch( attr_type)
		{
			case AIPI_STRING:
				type = S_S_S;
				break;
			case AIPI_INT:
				type = S_S_I;
				break;
			case AIPI_LONG:
				type = S_S_L;
				break;
			case AIPI_FLOAT:
				type = S_S_F;
				break;
			case AIPI_DOUBLE:
				type = S_S_D;
				break;
		}
	}
	else
	{
		//Semantic error
		CAipi_Error err;
		CString strAttr = s_attr.data();
		CString  strDesc = _T("No class was found for identifier [") + strAttr + _T("]."); 
		//err.displayGUIError(UNKNOW_TYPE, SEMANT_ERROR, strDesc);
		//return;
	}
	
	//AfxMessageBox(_T("EXEC RETRACT"));
	//Remove WME
	CAipi_WM wmo;
	int wme = wmo.findWM(if_id, if_attr, if_val );	

	/*
	CString str;
	str.Format(_T("Working Memory  Element...%d  " ), wme);
	AfxMessageBox(str);
	*/

	//Update Alpha Memory with new WMEs
	CAipi_RETE_Net net;
	int am1 = net.retractUpdateAM(wme);

	/*
	str.Format(_T("AM Element...%d  " ), am1);
	AfxMessageBox(str);
	*/
	
	if( am1 != UNDEFINE )
	{
		wmo.eraseWM(wme);
		int c2 = net.retractUpdateBM(wme);
			
		
		CAipi_LHS lhso;
		long pm = lhso.findLHSPM(c2);
			
		/*
		CString st;
		st.Format(_T("Updated BM WME...%d  " ), g_currentWM);
		AfxMessageBox(st);
		st.Format(_T("Updated BM Cond...%d  " ), c2);
		AfxMessageBox(st);
		st.Format(_T("Cond belongs to PM...%d  " ), pm);
		AfxMessageBox(st);
		*/
		
		/*
		CAipi_RETE_PNode pno;
		int p = pno.definePNode(pm);
		if( p == P_UNSUCCESS )
		{
		return NOT_FOUND;
		}
		else
		{
		pno.saveFiredPM( pm);
		}
		*/
		r = FOUND;
		
	}
	
	
return r;			
			 
}








int CAipi_RHS::assertPMFacts(long pm)
{
	int type = S_S_S;
	int r = NOT_FOUND;
	CAipi_RHS rhs;

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_Fact::iterator iterPM;
	pair <CMainFrame::g_mmPM_Fact::iterator, CMainFrame::g_mmPM_Fact::iterator>  pPM;
	
	pPM = pMainFrame->gmmPM_Fact.equal_range(pm);
	
	for(iterPM = pPM.first; iterPM != pPM.second; ++iterPM)
	{	
		int rhse = iterPM->second;
		int found = rhs.findRHSMembersIForm(rhse);
 		/*
		CString str;
		str.Format(_T("RHS Element...%d  " ), rhse);
		AfxMessageBox(str);
		str.Format(_T("PM Element...%d  " ), iterPM->first);
		AfxMessageBox(str);
		*/
		/*
		long idIForm = rhs.m_rhsIdIForm;
		long attrIForm = rhs.m_rhsAttrIForm;
		long valIForm = rhs.m_rhsValIForm;
		*/
		
		if( found != NOT_FOUND )
		{
			//AfxMessageBox(_T("Found ASSERT RHS Element"));
			
			if( rhs.m_Command != AIPI_ASSERT )
			{
				//AfxMessageBox(_T("OUT"));
				return NOT_FOUND;
			}
			/*
			CAipi_Symbol sym;
			long idIForm = sym.findId_IntForm(rhs.m_rhsId);
			if( idIForm == NOT_FOUND )
			{
				idIForm = ++g_currentId_IForm;
			}
			long attrIForm = sym.findId_IntForm(rhs.m_rhsAttr);
			if( attrIForm == NOT_FOUND )
			{
				attrIForm = ++g_currentId_IForm;
			}
			long valIForm = sym.findId_IntForm(rhs.m_rhsVal);
			if( valIForm == NOT_FOUND )
			{
				valIForm = ++g_currentId_IForm;
			}
			*/
			//Search for the type of the WMEs
			CAipi_STableClass stclass;
			int attr_type = stclass.findAttrType(rhs.m_rhsAttrIForm, rhs.m_rhsIdIForm);
			if( attr_type != NOT_FOUND )
			{
				//AfxMessageBox(_T("Attr Type Encontrado"));
				switch( attr_type)
				{
				case AIPI_STRING:
					type = S_S_S;
					break;
				case AIPI_INT:
					type = S_S_I;
					break;
				case AIPI_LONG:
					type = S_S_L;
					break;
				case AIPI_FLOAT:
					type = S_S_F;
					break;
				case AIPI_DOUBLE:
					type = S_S_D;
					break;
				}
			}
			else
			{
				//Semantic error
				CAipi_Error err;
				CString strAttr = rhs.m_Attr.data();
				CString  strDesc = _T("No class was found for identifier [") + strAttr + _T("]."); 
				//err.displayGUIError(UNKNOW_TYPE, SEMANT_ERROR, strDesc);
				//return;
			}
			
			
			CAipi_WM wm;
			//Check if working memory element already exist
			//Refraction
			int wme = wm.findWM(rhs.m_rhsIdIForm, rhs.m_rhsAttrIForm, rhs.m_rhsValIForm);
			if( wme == NOT_FOUND )
			{
				//AfxMessageBox(_T("Added Fact"));
				//Add new WME
				++g_currentWM;
				++g_currentTimeTag;
				
				wm.addWMIForm(g_currentWM, rhs.m_rhsIdIForm, rhs.m_rhsAttrIForm, rhs.m_rhsValIForm, rhs.m_rhsId, rhs.m_rhsAttr, rhs.m_rhsVal, type , g_currentTimeTag);	
				
				
				
				//Update Alpha Memory with new WMEs
				CAipi_RETE_Net net;
				int am1 = net.assertUpdateAM(g_currentWM);
				if( am1 != UNDEFINE )
				{
					
					
					int c2 = net.assertUpdateBM(am1, g_currentWM, pm);
					CAipi_LHS lhso;
					long pm = lhso.findLHSPM(c2);
					
					/*
					CString st;
					st.Format(_T("Updated BM WME...%d  " ), g_currentWM);
					AfxMessageBox(st);
					st.Format(_T("Updated BM Cond...%d  " ), c2);
					AfxMessageBox(st);
					st.Format(_T("Cond belongs to PM...%d  " ), pm);
					AfxMessageBox(st);
					*/

					CAipi_RETE_PNode pno;
					int p = pno.definePNode(pm);
					if( p == P_UNSUCCESS )
					{
						return NOT_FOUND;
					}
					else
					{
						int f = pno.findRefraction(pm);
						if( f == NOT_FOUND )
						{
							pno.saveFiredPM(pm);
							/*
							st.Format(_T("SAVE FIRED PM...%d  " ), pm);
							AfxMessageBox(st);
							*/
						}
						
						
					}
					
					
					
				}
				
				r = FOUND;
			}
			
			
		}
	}

			
return r;
		
}			




int CAipi_RHS::retractPMFacts(long pm)
{
	int type = S_S_S;
	int r = NOT_FOUND;
	CAipi_RHS rhs;

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_Fact::iterator iterPM;
	pair <CMainFrame::g_mmPM_Fact::iterator, CMainFrame::g_mmPM_Fact::iterator>  pPM;
	
	pPM = pMainFrame->gmmPM_Fact.equal_range(pm);
	
	for(iterPM = pPM.first; iterPM != pPM.second; ++iterPM)
	{	
		int rhse = iterPM->second;
		int found = rhs.findRHSMembersIForm(rhse);
 		/*
		CString str;
		str.Format(_T("RHS Element...%d  " ), rhse);
		AfxMessageBox(str);
		str.Format(_T("PM Element...%d  " ), iterPM->first);
		AfxMessageBox(str);
		*/
		/*
		long idIForm = rhs.m_rhsIdIForm;
		long attrIForm = rhs.m_rhsAttrIForm;
		long valIForm = rhs.m_rhsValIForm;
		*/
		
		if( found != NOT_FOUND )
		{
			//AfxMessageBox(_T("Found RHS Element"));

			/*
			CString st;
			st.Format(_T("RHS Command...%d  " ), rhs.m_Command);
			AfxMessageBox(st);
			*/

			if( rhs.m_Command != AIPI_RETRACT )
			{
				continue;
			}
			/*
			CAipi_Symbol sym;
			long idIForm = sym.findId_IntForm(rhs.m_rhsId);
			if( idIForm == NOT_FOUND )
			{
				idIForm = ++g_currentId_IForm;
			}
			long attrIForm = sym.findId_IntForm(rhs.m_rhsAttr);
			if( attrIForm == NOT_FOUND )
			{
				attrIForm = ++g_currentId_IForm;
			}
			long valIForm = sym.findId_IntForm(rhs.m_rhsVal);
			if( valIForm == NOT_FOUND )
			{
				valIForm = ++g_currentId_IForm;
			}
			*/
			//Search for the type of the WMEs
			CAipi_STableClass stclass;
			int attr_type = stclass.findAttrType(rhs.m_rhsAttrIForm, rhs.m_rhsIdIForm);
			if( attr_type != NOT_FOUND )
			{
				//AfxMessageBox(_T("Attr Type Encontrado"));
				switch( attr_type)
				{
				case AIPI_STRING:
					type = S_S_S;
					break;
				case AIPI_INT:
					type = S_S_I;
					break;
				case AIPI_LONG:
					type = S_S_L;
					break;
				case AIPI_FLOAT:
					type = S_S_F;
					break;
				case AIPI_DOUBLE:
					type = S_S_D;
					break;
				}
			}
			else
			{
				//Semantic error
				CAipi_Error err;
				CString strAttr = rhs.m_Attr.data();
				CString  strDesc = _T("No class was found for identifier [") + strAttr + _T("]."); 
				//err.displayGUIError(UNKNOW_TYPE, SEMANT_ERROR, strDesc);
				//return;
			}
			
			//AfxMessageBox(_T("Remove Fact"));
			//Remove WME
			CAipi_WM wmo;
			int wme = wmo.findWM(rhs.m_rhsIdIForm, rhs.m_rhsAttrIForm, rhs.m_rhsValIForm);	
			/*
			CString str;
			str.Format(_T("Working Memory  Element...%d  " ), wme);
			AfxMessageBox(str);
			*/
			//Update Alpha Memory with new WMEs
			CAipi_RETE_Net net;
			int am1 = net.retractUpdateAM(wme);


			//str.Format(_T("AM Element...%d  " ), am1);
			//AfxMessageBox(str);
			
			
			if( am1 != UNDEFINE )
			{
				wmo.eraseWM(wme);
				int c2 = net.retractUpdateBM(wme);
				
				
				
				CAipi_LHS lhso;
				long pm = lhso.findLHSPM(c2);
				
				/*
				CString st;
				st.Format(_T("Updated BM WME...%d  " ), g_currentWM);
				AfxMessageBox(st);
				st.Format(_T("Updated BM Cond...%d  " ), c2);
				AfxMessageBox(st);
				st.Format(_T("Cond belongs to PM...%d  " ), pm);
				AfxMessageBox(st);
				*/

				/*
				CAipi_RETE_PNode pno;
				int p = pno.definePNode(pm);
				if( p == P_UNSUCCESS )
				{
					return NOT_FOUND;
				}
				else
				{
					pno.saveFiredPM( pm);
				}
				*/

				
			}
		
		
			r = FOUND;		
			 
		}
	}

			
return r;
		
}			





int CAipi_RHS::execPMFacts(long pm)
{
	int type = S_S_S;
	int r = NOT_FOUND;
	CAipi_RHS rhs;

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_Fact::iterator iterPM;
	pair <CMainFrame::g_mmPM_Fact::iterator, CMainFrame::g_mmPM_Fact::iterator>  pPM;
	
	pPM = pMainFrame->gmmPM_Fact.equal_range(pm);
	
	for(iterPM = pPM.first; iterPM != pPM.second; ++iterPM)
	{	
		int rhse = iterPM->second;
		int found = rhs.findRHSMembersIForm(rhse);
 		int command = rhs.m_Command;
		/*
		CString str;
		str.Format(_T("RHS Element...%d  " ), rhse);
		AfxMessageBox(str);
		str.Format(_T("PM Element...%d  " ), iterPM->first);
		AfxMessageBox(str);
		*/
		/*
		long idIForm = rhs.m_rhsIdIForm;
		long attrIForm = rhs.m_rhsAttrIForm;
		long valIForm = rhs.m_rhsValIForm;
		*/
		
		if( found != NOT_FOUND )
		{
			r = FOUND;
			//AfxMessageBox(_T("Found ASSERT RHS Element"));
			if( command == AIPI_ASSERT )
			{
				double if_id = rhs.m_rhsIdIForm;
				double if_attr = rhs.m_rhsAttrIForm;
				double if_val = rhs.m_rhsValIForm;
				tstring s_id = rhs.m_rhsId;
				tstring s_attr = rhs.m_rhsAttr;
				tstring s_val = rhs.m_rhsVal;

				execAssert(pm, if_id, if_attr, if_val, s_id, s_attr, s_val);
					
			}
			else if ( command == AIPI_RETRACT )
			{
				double if_id = rhs.m_rhsIdIForm;
				double if_attr = rhs.m_rhsAttrIForm;
				double if_val = rhs.m_rhsValIForm;
				tstring s_id = rhs.m_rhsId;
				tstring s_attr = rhs.m_rhsAttr;
				tstring s_val = rhs.m_rhsVal;

				execRetract(if_id, if_attr, if_val, s_id, s_attr, s_val);
				
			}
			
			
		}
        else
		{
			return r;
		}
	}

			
return r;
		
}			





void CAipi_RHS::eraseRHS(int rhs)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int f = findRHSMembers(rhs);
	
	if( f != NOT_FOUND )
	{
		pMainFrame->gmRHS.erase(rhs);
	}
}

void CAipi_RHS::clearRHS()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmRHS.clear();
}


int CAipi_RHS::sizeRHS()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmRHS.size();

}




double CAipi_RHS::findRHSIdIForm( int rhs )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mRHS::iterator iter;
    iter = pMainFrame->gmRHS.find(rhs);
	if( iter != pMainFrame->gmRHS.end())
	{
  		CAipi_RHS id = (CAipi_RHS)iter->second;
 		return id.getIdIForm(); 
	}
	

return NOT_FOUND;
}


double CAipi_RHS::findRHSAttrIForm( int rhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mRHS::iterator iter;
    iter = pMainFrame->gmRHS.find(rhs);
	if( iter != pMainFrame->gmRHS.end())
	{
  		CAipi_RHS attr = (CAipi_RHS)iter->second;
 		return attr.getAttrIForm(); 
	}

return NOT_FOUND;
			

}




double CAipi_RHS::findRHSValIForm( int rhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mRHS::iterator iter;
    iter = pMainFrame->gmRHS.find(rhs);
	if( iter != pMainFrame->gmRHS.end())
	{
  		CAipi_RHS val = (CAipi_RHS)iter->second;
 		return val.getValIForm();
	}

return NOT_FOUND;

}




tstring CAipi_RHS::findRHSId( int rhs )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mRHS::iterator iter;
    iter = pMainFrame->gmRHS.find(rhs);
	if( iter != pMainFrame->gmRHS.end())
	{
  		CAipi_RHS id = (CAipi_RHS)iter->second;
 		return id.getId(); 
	}
	

return _T("NOT_FOUND");
}


tstring CAipi_RHS::findRHSAttr( int rhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mRHS::iterator iter;
    iter = pMainFrame->gmRHS.find(rhs);
	if( iter != pMainFrame->gmRHS.end())
	{
  		CAipi_RHS attr = (CAipi_RHS)iter->second;
 		return attr.getAttr(); 
	}

return _T("NOT_FOUND");
			

}



tstring CAipi_RHS::findRHSVal( int rhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mRHS::iterator iter;
    iter = pMainFrame->gmRHS.find(rhs);
	if( iter != pMainFrame->gmRHS.end())
	{
  		CAipi_RHS val = (CAipi_RHS)iter->second;
 		return val.getVal();
	}

return _T("NOT_FOUND");

}


long CAipi_RHS::findRHSPM( int rhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mRHS::iterator iter;
    iter = pMainFrame->gmRHS.find(rhs);
	if( iter != pMainFrame->gmRHS.end())
	{
  		CAipi_RHS pm = (CAipi_RHS)iter->second;
 		return pm.getPM();
	}

return NOT_FOUND;

}

int CAipi_RHS::findRHSCommand( int rhs )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mRHS::iterator iter;
    iter = pMainFrame->gmRHS.find(rhs);
	if( iter != pMainFrame->gmRHS.end())
	{
  		CAipi_RHS cmd = (CAipi_RHS)iter->second;
 		return cmd.getCommand();
	}

return NOT_FOUND;

}


int CAipi_RHS::findRHSMembers(int rhs)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mRHS::iterator iter;
    iter = pMainFrame->gmRHS.find(rhs);
	if( iter != pMainFrame->gmRHS.end())
	{
		CAipi_RHS rhso = (CAipi_RHS)iter->second;
 	
		m_rhsId = rhso.getId();
		m_rhsAttr = rhso.getAttr();
		m_rhsVal = rhso.getVal();
		m_PM = rhso.getPM();
		m_Command = rhso.getCommand();
		
		
		return rhs;
	}
	
	return NOT_FOUND;
}


int CAipi_RHS::findRHSMembersIForm(int rhs)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mRHS::iterator iter;
    iter = pMainFrame->gmRHS.find(rhs);
	if( iter != pMainFrame->gmRHS.end())
	{
		CAipi_RHS rhso = (CAipi_RHS)iter->second;
 	
		m_rhsIdIForm = rhso.getIdIForm();
		m_rhsAttrIForm = rhso.getAttrIForm();
		m_rhsValIForm = rhso.getValIForm();
		m_rhsId = rhso.getId();
		m_rhsAttr = rhso.getAttr();
		m_rhsVal = rhso.getVal();
		m_PM = rhso.getPM();
		m_Command = rhso.getCommand();
			

		return rhs;
	}
	
	return NOT_FOUND;
}


void CAipi_RHS::printRHS()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Right Hand Side  *******"));
	//Print map container
	for( CMainFrame::g_mRHS::const_iterator iter = pMainFrame->gmRHS.begin(); iter!= pMainFrame->gmRHS.end(); ++iter)
	{
		CString strFact =_T("F");
		strFact +=  _itot( iter->first, buffer, 10 );
		tstring i = findRHSId(iter->first);
		tstring a = findRHSAttr(iter->first);
		tstring v = findRHSVal(iter->first);

		CAipi_RHS rhso = (CAipi_RHS)iter->second;
		int pm	  = rhso.getPM();
		int cmd	  = rhso.getCommand();
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  RHS  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1(strFact);
		pMainFrame->m_wndOutputTabView.AddMsg1(i.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(a.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(v.data());
		
		CString strPM =_T("PM");
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		CString strCmd =_T("Command");
		strCmd +=  _itot( cmd, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCmd);
		
		
		
	}

}


void CAipi_RHS::printRHSIForm()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Right Hand Side  *******"));
	//Print map container
	for( CMainFrame::g_mRHS::const_iterator iter = pMainFrame->gmRHS.begin(); iter!= pMainFrame->gmRHS.end(); ++iter)
	{
		CString strFact =_T("F");
		CString strIdIForm = _T("ID_");
		CString strAttrIForm = _T("ATTR_");
		CString strValIForm = _T("VAL_");

		strFact +=  _itot( iter->first, buffer, 10 );
		tstring i = findRHSId(iter->first);
		tstring a = findRHSAttr(iter->first);
		tstring v = findRHSVal(iter->first);

		long	i_iform = findRHSIdIForm( iter->first);
		long	a_iform = findRHSAttrIForm( iter->first);
		long	v_iform = findRHSValIForm( iter->first);

		CAipi_RHS rhso = (CAipi_RHS)iter->second;
		int pm	  = rhso.getPM();
		int cmd   = rhso.getCommand();
				
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  RHS  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1(strFact);
		pMainFrame->m_wndOutputTabView.AddMsg1(i.data());
		
		strIdIForm +=  _itot( i_iform, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strIdIForm);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(a.data());

		strAttrIForm +=  _itot( a_iform, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAttrIForm);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(v.data());

		strValIForm +=  _itot( v_iform, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strValIForm);
		
		CString strPM =_T("PM");
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);

		CString strCmd =_T("Command");
		strCmd +=  _itot( cmd, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCmd);
		
		
		
	}

}