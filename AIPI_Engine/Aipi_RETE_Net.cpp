// Aipi_RETE_Net.cpp: implementation of the CAipi_RETE_Net class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_Net.h"

#include "../MainFrm.h"
#include "../ChildFrm.h"
#include "../OutputTabView.h"

#include <math.h>
#include <stdlib.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAipi_RETE_Net::CAipi_RETE_Net()
{

}

CAipi_RETE_Net::~CAipi_RETE_Net()
{

}

void CAipi_RETE_Net::preAnalysis()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mPM::iterator it_PM;

		
	if ( !pMainFrame->gmPM.empty() )
	{
		for(it_PM = pMainFrame->gmPM.begin(); it_PM != pMainFrame->gmPM.end(); ++it_PM)
		{
			getPMVars(it_PM->first);
		}
	}
}





int CAipi_RETE_Net::getPMVars(int pm)
{
	CAipi_PM	pmo;
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmPM_IVar::iterator itId;
	pair <CMainFrame::g_mmPM_IVar::iterator, CMainFrame::g_mmPM_IVar::iterator>  pId;
	pId = pMainFrame->gmmPM_IVar.equal_range(pm);

	CMainFrame::g_mmPM_VVar::iterator itVal;
	pair <CMainFrame::g_mmPM_VVar::iterator, CMainFrame::g_mmPM_VVar::iterator>  pVal;
	pVal = pMainFrame->gmmPM_VVar.equal_range(pm);
	
	int c1 = pmo.PM_CondLowerBound(pm);
	int c2 = pmo.PM_CondUpperBound(pm);
	
		/*
		CString str;
		str.Format(_T("CIni :...%d  " ), c1);
		AfxMessageBox(str);
		str.Format(_T("CEnd :...%d  " ), c2);
		AfxMessageBox(str);
		*/
	
	
	for(itId = pId.first; itId != pId.second; ++itId)
	{	
		tstring varId = itId->second;
		int size = linkRangeIDVars(c1, c2, varId);
		linkCondID_ID(size, pm, varId);
		
	}
	
	for(itVal = pVal.first; itVal != pVal.second; ++itVal)
	{	
		tstring varVal = itVal->second;
		int size = linkRangeVALVars(c1, c2, varVal);
		linkCondVAL_VAL(size, pm, varVal);
		
	}


	for(itId = pId.first; itId != pId.second; ++itId)
	{	
		tstring varId = itId->second;
		for(itVal = pVal.first; itVal != pVal.second; ++itVal)
		{
			tstring varVal = itVal->second;
				
				if( varId == varVal )
				{
					linkCondVAL_ID(c1, c2, pm, varId);
				}
				
		}

	}

return 1;	
}


int CAipi_RETE_Net::getRangePMVars(int cini, int cend, int pm)
{
	CAipi_RETE_NCCNode ncco;
		
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmPM_IVar::iterator itId;
	pair <CMainFrame::g_mmPM_IVar::iterator, CMainFrame::g_mmPM_IVar::iterator>  pId;
	pId = pMainFrame->gmmPM_IVar.equal_range(pm);

	CMainFrame::g_mmPM_VVar::iterator itVal;
	pair <CMainFrame::g_mmPM_VVar::iterator, CMainFrame::g_mmPM_VVar::iterator>  pVal;
	pVal = pMainFrame->gmmPM_VVar.equal_range(pm);
	
	
	for(itId = pId.first; itId != pId.second; ++itId)
	{	
		tstring varId = itId->second;
		int size = linkRangeIDVars(cini, cend, varId);
		linkCondID_ID(size, pm, varId);
		

		
		for(itVal = pVal.first; itVal != pVal.second; ++itVal)
		{
			tstring varVal = itVal->second;
				
				if( varId == varVal )
				{
					linkCondVAL_ID(cini, cend, pm, varId);
				}

		}

	}

return 1;
	
}

int CAipi_RETE_Net::lastIDVar(int pm, tstring var)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int lastCond = NOT_FOUND;
		
	//Saving the conditions with Identifier variable(var) in a temporal vector
	CMainFrame::g_mmVar_I::iterator iterVI;
	pair <CMainFrame::g_mmVar_I::iterator, CMainFrame::g_mmVar_I::iterator>  pVI;
	
	pVI = pMainFrame->gmmVar_I.equal_range(var);
	
	int n = pMainFrame->gmmVar_I.count(var);
	
	if( n > 1 )
	{

		for(iterVI = pVI.first; iterVI != pVI.second; ++iterVI)
		{	
			CAipi_RETE_Vars varo = (CAipi_RETE_Vars)iterVI->second;
 			int prodM = varo.getPM();

			
			if( prodM == pm  )
			{
				lastCond = varo.getCond();
				
				/*
					CString str;
					str.Format(_T("ID Condition :...%d  " ), cId);
					AfxMessageBox(str);
				*/
					
			}

		
		}
	}

	if( lastCond != NOT_FOUND)
	{
		return lastCond;
	}
		
return NOT_FOUND;

}


int CAipi_RETE_Net::firstIDVar(int pm, tstring var)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int firstCond = NOT_FOUND;
	
	//Saving the conditions with Identifier variable(var) in a temporal vector
	CMainFrame::g_mmVar_I::iterator iterVI;
	pair <CMainFrame::g_mmVar_I::iterator, CMainFrame::g_mmVar_I::iterator>  pVI;
	
	pVI = pMainFrame->gmmVar_I.equal_range(var);
	
	int n = pMainFrame->gmmVar_I.count(var);
	
	if( n > 1 )
	{

		for(iterVI = pVI.first; iterVI != pVI.second; ++iterVI)
		{	
			CAipi_RETE_Vars varo = (CAipi_RETE_Vars)iterVI->second;
 			int prodM = varo.getPM();

			
			if( prodM == pm  )
			{
				firstCond = varo.getCond();
				return firstCond;
				/*
					CString str;
					str.Format(_T("ID Condition :...%d  " ), cId);
					AfxMessageBox(str);
				*/
					
			}
		
		}
	}

	
		
return NOT_FOUND;

}


/*
int CAipi_RETE_Net::linkVALVars(int pm, tstring var)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
    //Saving the conditions with Value variable(var) in a temporal vector
	CMainFrame::g_mmVar_V::iterator iterVV;
	pair <CMainFrame::g_mmVar_V::iterator, CMainFrame::g_mmVar_V::iterator>  pVV;
	
	pVV = pMainFrame->gmmVar_V.equal_range(var);

	int n = pMainFrame->gmmVar_V.count(var);
	
	if( n > 0 )
	{

		for(iterVV = pVV.first; iterVV != pVV.second; ++iterVV)
		{	
			CAipi_RETE_Vars varo = (CAipi_RETE_Vars)iterVV->second;
 			int prodM = varo.getPM();

			if( prodM == pm  )
			{
				int cVal = varo.getCond();
				m_vVAL.push_back(cVal);
						
					
					CString str;
					str.Format(_T("VAL Condition :...%d  " ), cVal);
					AfxMessageBox(str);
					
				
			}
		}
	}



return m_vVAL.size();

}

*/

int CAipi_RETE_Net::linkRangeIDVars(int cini, int cend, tstring var)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	//AfxMessageBox(var.data());
	
	//Saving the conditions with Identifier variable(var) in a temporal vector
	CMainFrame::g_mmVar_I::iterator iterVI;
	pair <CMainFrame::g_mmVar_I::iterator, CMainFrame::g_mmVar_I::iterator>  pVI;
	
	pVI = pMainFrame->gmmVar_I.equal_range(var);
	
	//int n = pMainFrame->gmmVar_I.count(var);
	
		for(iterVI = pVI.first; iterVI != pVI.second; ++iterVI)
		{	
			CAipi_RETE_Vars varo = (CAipi_RETE_Vars)iterVI->second;
 			int cId = varo.getCond();
			
			
			if( cId >= cini  &&  cId <= cend )
			{
				m_vID.push_back(cId);
					
											
					/*
					CString str;
					str.Format(_T("ID Condition :...%d  " ), cId);
					AfxMessageBox(str);
					*/
					
				
				
					
			}
			if( cId == cend)
			{
				break;
			}
		
		}
	
return m_vID.size();

}


int CAipi_RETE_Net::linkRangeVALVars(int cini, int cend, tstring var)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
    //Saving the conditions with Value variable(var) in a temporal vector
	CMainFrame::g_mmVar_V::iterator iterVV;
	pair <CMainFrame::g_mmVar_V::iterator, CMainFrame::g_mmVar_V::iterator>  pVV;
	
	pVV = pMainFrame->gmmVar_V.equal_range(var);

	//int n = pMainFrame->gmmVar_V.count(var);
	
	

		for(iterVV = pVV.first; iterVV != pVV.second; ++iterVV)
		{	
			CAipi_RETE_Vars varo = (CAipi_RETE_Vars)iterVV->second;
			int cVal = varo.getCond();
			

 			if( cVal >= cini  &&  cVal <= cend )
			{
				m_vVAL.push_back(cVal);
								
					/*
					CString str;
					str.Format(_T("VAL Condition :...%d  " ), cVal);
					AfxMessageBox(str);
					*/
				
			}
			if( cVal == cend)
			{
				break;
			}
				
			
		}
	

return m_vVAL.size();

}


void CAipi_RETE_Net::linkCondID_ID(int size, int pm, tstring var)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_RETE_Links  linko;
	//Checking and saving coditions with the same variable 
	//as Identifier in both conditions for matching
	
	if( size > 1  )
	{	
		
		for(int i = 0; i<size-1; ++i)
		{
			int cId1 = m_vID.at(i);
			int cId2 = m_vID.at(i+1);

			linko.addLink(cId1, cId2, AIPI_ID, AIPI_ID, pm, var);			
		
			/*
			TCHAR buffer[4];
			CString str;
			AfxMessageBox(_T("ID_ID Conditions : "));
			str =  _itot( cId1, buffer, 10 );
			AfxMessageBox(str);
			str =  _itot( cId2, buffer, 10 );
			AfxMessageBox(str);
			*/
		
		}

	}
	
	m_vID.clear();


}


void CAipi_RETE_Net::linkCondVAL_VAL(int size, int pm, tstring var)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_RETE_Links  linko;
	//Checking and saving coditions with the same variable 
	//as Values in both conditions for matching
	
	if( size > 1  )
	{	
		
		for(int i = 0; i<size-1; ++i)
		{
			int cVal1 = m_vVAL.at(i);
			int cVal2 = m_vVAL.at(i+1);

			linko.addLink(cVal1, cVal2, AIPI_VL, AIPI_VL, pm, var);			
		
			/*
			TCHAR buffer[4];
			CString str;
			AfxMessageBox(_T("VAL_VAL Conditions : "));
			str =  _itot( cVal1, buffer, 10 );
			AfxMessageBox(str);
			str =  _itot( cVal2, buffer, 10 );
			AfxMessageBox(str);
			*/
		
		}

	}
	
	m_vVAL.clear();


}




/*
void CAipi_RETE_Net::saveVAL_ID(int pm,  tstring var)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	int nId = linkIDVars(pm, var);
	int nVal = linkVALVars(pm, var);
	
	AfxMessageBox(var.data());

//Checking and saving conditions with the same variable
//one in the Identifier and one in Value 
		for(int i=0; i<1; ++i)
		{
			int cId = m_vID.at(i);

			for(int j=0; j<nVal; ++j)
			{
				int cVal = m_vVAL.at(j);

				pMainFrame->gmVCond_ICond.insert(CMainFrame::g_mVCond_ICond::value_type(cVal, cId));
				
				
				TCHAR buffer[8];
				CString str;
				AfxMessageBox(_T("VAL_ID Conditions : "));
				str =  _itot( cId, buffer, 10 );
				AfxMessageBox(str);
				str =  _itot( cVal, buffer, 10 );
				AfxMessageBox(str);
				
				
				
			}

		}
	
	m_vID.clear();
	m_vVAL.clear();

	

}
*/


void CAipi_RETE_Net::linkCondVAL_ID(int cini,  int cend, int pm, tstring var)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_RETE_Links linko;

	int nId = linkRangeIDVars(cini, cend, var);
	int nVal = linkRangeVALVars(cini, cend, var);


	
	//AfxMessageBox(var.data());
	
	/*
	TCHAR buffer[4];
	CString str;
	AfxMessageBox(_T("nId : "));
	str =  _itot( nId, buffer, 10 );
	AfxMessageBox(str);
	*/

//Checking and saving conditions with the same variable
//one in the Identifier and one in Value
	
	if( nId > 0 )
	{
		for(int i=0; i<1; ++i)
		{
			int cId = m_vID.at(i);
			
			for(int j=0; j<nVal; ++j)
			{
				int cVal = m_vVAL.at(j);
				
				linko.addLink(cVal, cId, AIPI_VL, AIPI_ID, pm, var);
				
				
				/*
				TCHAR buffer[4];
				CString str;
				AfxMessageBox(_T("VAL_ID Conditions : "));
				str =  _itot( cVal, buffer, 10 );
				AfxMessageBox(str);
				str =  _itot( cId, buffer, 10 );
				AfxMessageBox(str);
				*/
				
				
			}

		}
	}
	
	
	m_vID.clear();
	m_vVAL.clear();

	//AfxMessageBox(_T("Fin"));

}






int CAipi_RETE_Net::createDNode(int c1, int pm, int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_WM::iterator it_AM;
	pair <CMainFrame::g_mmAM_WM::iterator, CMainFrame::g_mmAM_WM::iterator>  pAM;
		
	CAipi_RETE_DNode	dno;
	CAipi_RETE_TK		tko;
	CAipi_RETE_BM		bmo;
	CAipi_RETE_Node		ndo;
	CAipi_RETE_JNode	jno;
	CAipi_RETE_AM		amo;
	CAipi_LHS			lhso;
	CAipi_RETE_NNode	nno;	
	
	tstring varId1 = _T("Undef");
	tstring dataId1 =_T("Undef");
	int wm = UNDEFINE;
	
	int am = amo.findCond_AM(c1);
	int not = nno.findCond_NN(c1);
	
	//Check for negated conditions
	if( not != NOT_FOUND )
	{
		if( !pMainFrame->gmmAM_WM.empty())
		{
			
			pAM = pMainFrame->gmmAM_WM.equal_range(am);

			for(it_AM = pAM.first; it_AM != pAM.second; ++it_AM)
			{	
			
				int new_tk = tko.generateTKKey();
				wm = it_AM->second;
				tko.createTK(new_tk, DNode, wm, bm, NNode);
				nno.addNN_TK(bm, new_tk);
				//tko.addWM_ParentTK(it_AM->second, DNode);
				tko.addWM_ChildTK(it_AM->second, new_tk);
				nno.addWM_NN(it_AM->second, bm);
				nno.editCond_NN(c1, bm);
					
			}
			
			bmo.addBM(bm, varId1, dataId1, _T("Undef"),_T("Undef"), DNode, NOT_FOUND, wm);
			
			/*
			CString str;
			str.Format(_T("BME DM...%d  " ), BME);
			AfxMessageBox(str);
			*/
			
		}
		
	}
	//Check for normal conditions
	else
	{
		/*
		CString str;
		str.Format(_T("Dummy Node...%d  " ), c1);
		AfxMessageBox(str);
		*/
				
		
		dno.addDNode(c1, pm, am, bm);	
		
		
		int newJN = jno.generateJNKey();
		jno.addJN(bm, UNDEFINE, UNDEFINE, c1, AIPI_VL, pm, _T("Undef"));
		ndo.addNode(newJN, DNode, UNDEFINE, bm, am);
		
		
		if( !pMainFrame->gmmAM_WM.empty())
		{
			pAM = pMainFrame->gmmAM_WM.equal_range(am);
			CAipi_LHS lhso;
			CAipi_WM  wmo;
			
			lhso.findLHSMembers(c1);
			varId1 = lhso.m_lhsId;
			tstring varName1 = lhso.m_lhsVal;
			
			int categ = lhso.m_Category;
			int rel = lhso.m_Rel;
							

			for(it_AM = pAM.first; it_AM != pAM.second; ++it_AM)
			{	
			
				int new_tk = tko.generateTKKey();
				wm = it_AM->second;
				lhso.findWMMembers(wm);
				tstring varData1 = lhso.m_Val;

				if( rel == AS  )
				{
					
					int type = lhso.m_Type;
					saveDataNum(pm, c1, wm, type, bm, DNode, varName1, varData1 );
				}
				
				
				
				tko.createTK(new_tk, DNode, wm, bm, DNode);
				dataId1 = lhso.m_Id;
				bmo.addBM(bm, varId1, dataId1, _T("Undef"), _T("Undef"), DNode, new_tk, wm);
				
				//tko.addWM_ParentTK(it_AM->second, DNode);
				tko.addWM_ChildTK(it_AM->second, new_tk);
				
				
				/*
				CString str;
				str.Format(_T("BME DM...%d  " ), BME);
				AfxMessageBox(str);
				*/
	
			}
		}
	}
	
	return c1;

}

/*
int CAipi_RETE_Net::findTokenPM( int pm, int child_tk)
{
	CAipi_RETE_BM bmo;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_BM::iterator iterPM;
	pair <CMainFrame::g_mmPM_BM::iterator, CMainFrame::g_mmPM_BM::iterator>  pPM;

	pPM = pMainFrame->gmmPM_BM.equal_range(pm);
	
	for(iterPM = pPM.first; iterPM != pPM.second; ++iterPM)
	{	
		int bm = iterPM->second;
		int chld = bmo.findBMChildTK( bm, child_tk);
		if( chld != NOT_FOUND)
		{
			return chld;
		}
	}

return NOT_FOUND;

}

*/


int CAipi_RETE_Net::createJN(int c1, int f1, int c2, int f2, int pm, int bm1, int bm2, int am, tstring var)
{
	CAipi_RETE_JNode jno;
	CAipi_RETE_Node no;

	int jn =  jno.generateJNKey();
	jno.addJN(jn, c1, f1, c2, f2, pm, var);
	no.addNode(jn, JNode, bm1, bm2, am);

	

return jn;

}






//This function compares all the conditions that correspond to a specific Alpha memory(AM)
//If a equal condition if found returns the first condition thar fits, if is not return the current condition. 
int CAipi_RETE_Net::findEqualCond(int a, int c)
{
	CAipi_LHS lhs;

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_Cond::const_iterator it_AM;
	pair <CMainFrame::g_mmAM_Cond::iterator, CMainFrame::g_mmAM_Cond::iterator>  pAM;

	int n = pMainFrame->gmmAM_Cond.count(a);

	if( n > 1 )
	{
		pAM = pMainFrame->gmmAM_Cond.equal_range(a);

		for(it_AM = pAM.first; it_AM != pAM.second; ++it_AM)
		{	
			if( lhs.compareEqualCond(it_AM->second, c))
			{
				return it_AM->second;
			}	
		}
	}
	else
	{
		it_AM = pMainFrame->gmmAM_Cond.find(a);
		if( it_AM != pMainFrame->gmmAM_Cond.end())
		{
  			return it_AM->second;
 		}
	}
	
	return c;	

}



int CAipi_RETE_Net::createNet()
{
	CAipi_PM			pmo;
	CAipi_RETE_BM		bmo;
	CAipi_RETE_AM		amo;
	CAipi_RETE_Node		no;
	CAipi_RETE_TK		tko;
	CAipi_RepCond		rco;
	CAipi_RETE_Cond		co;
	
	int tempPM = 0;				//Temporal production memory index
	int tempNextPM = 0;			//Temporal next production memory index
	int bm2 = 0; 
	int r = UNDEFINE;
	int newBM = 0;				//Takes the index of the new beta memory created 
	int currentJN = 0;			//The current join node index
	int rev_c1, rev_c2 = 0;		//Reverse conditions
	int rev_f1, rev_f2 = 0;		//Reverse fields of conditions
	int rev_am1, rev_am2 =0;	//Reverse alpha memory index
	bool rel_flag = false;		//Relational operation flag
	
	/*
	//Production with repeated conditions
	typedef std::set<long> s_repPM;
	s_repPM	srepPM;
	*/


	//This save all the repeated conditions
	//rco.createRepCondEx();
	

	
	
	CAipi_RETE_Links linko;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLink::const_iterator iter = pMainFrame->gmmLink.begin(); iter!= pMainFrame->gmmLink.end(); ++iter)
	{
		CAipi_RETE_Links linko = (CAipi_RETE_Links)iter->second;
 				
		int		c1			= iter->first;
		int		c2			= linko.getCond2();
		int		f1			= linko.getField1();
		int		f2			= linko.getField2();
		int		pm			= linko.getPM();
		tstring link_var	= linko.getVar(); 
		
		//Check for conditions besides c1 and c2 that match de current BM
		
		int calready2 = co.findPreCondBind(c1);
		if( calready2 == c2 )
		{
			 continue;
		}
		

		/*
		CString str;
		str.Format(_T("PM...%d  " ), pm);
		AfxMessageBox(str);
		*/
		//str.Format(_T("Temp Num PM...%d  " ), tempNumPM);
		//AfxMessageBox(str);
		
		
		if( pm == tempNextPM )
		{
			compareNumVars(pm - 1);
			
		}

		//Change to a new production memory
		if( pm > tempPM )
		{
			int dNode = checkingDNode(c1);
			/*
			CString str;
			str.Format(_T("DNode...%d  " ), dNode);
			AfxMessageBox(str);
			*/
			if( dNode == NOT_FOUND )
			{
				newBM = bmo.generateBMKey();
				createDNode(c1, pm, newBM);
				pmo.addPM_BM(pm, newBM);
				
				/*
				m_DN_BM = newBM;
				CAipi_RETE_DNode dn;
				int lBM = dn.lastBMDNode();
				
				CString str;
				str.Format(_T("Dummy newBM...%d  " ), newBM);
				AfxMessageBox(str);
				
				str.Format(_T("last Dummy BM...%d  " ), lBM);
				AfxMessageBox(str);
				*/
				
			}

			tempPM = pm;
			tempNextPM = pm+1;

			
			/*
			CString str;
			str.Format(_T("PM...%d  " ), pm);
			AfxMessageBox(str);
			*/
		
			
		}
		
		/*
		CString st;
		st.Format(_T("C1...%d  " ), c1);
		AfxMessageBox(st);
		st.Format(_T("C2...%d  " ), c2);
		AfxMessageBox(st);
	   */
		
		int am1 = amo.findCond_AM(c1);
		int am2 = amo.findCond_AM(c2);

		
					
				
		int jn2 = checkingRepeatedCond(c1, c2, am1, am2, pm, link_var);

		
		
		
		//st.Format(_T("JN original...%d  " ), jn2);
		//AfxMessageBox(st);
			
		
		//Check if the conditions area repeated.This way do not create unnecesary nodes.
		//If the Network sends the REPEATED message then jump this process.
		//The RETE node already has created the join nodes.
		if( jn2 == REPEATED )
		{
			//If there is a repeated condition the production has check
			//the matching process because it skips from continue the process
			//srepPM.insert(pm);

			//Save productions and their respective BM elements even for repeated conditions
			CAipi_RETE_Cond co;
			int oldJN1 = co.findCond1JN(c1);
			int oldJN2 = co.findCond2JN(c2);
			int oldBM1 = no.findNodeBM1(oldJN1);
			int oldBM2 = no.findNodeBM2(oldJN2);
			
			//Check for repeated BM, don´t save them 
			int found1 = pmo.findPM_BM(pm, oldBM1 );
			if( found1 != FOUND )
			{
				pmo.addPM_BM(pm, oldBM1);
			}
			int found2 = pmo.findPM_BM(pm, oldBM2 );
			if( found2 != FOUND )
			{			
				pmo.addPM_BM(pm, oldBM2);
			}

			/*
			//Check if all the production has repeated conditions
			++countCond;
			int nCond = pmo.countPM_Cond(pm);
			if( nCond == countCond)
			{
				pmo.erasePM_BM(pm);
			}
			*/	
			/*
			CString st;
			st.Format(_T("PM...%d  " ), pm);
			AfxMessageBox(st);
			st.Format(_T("C1...%d  " ), c1);
			AfxMessageBox(st);
			st.Format(_T("C2...%d  " ), c2);
			AfxMessageBox(st);
			st.Format(_T("old JN1...%d  " ), oldJN1);
			AfxMessageBox(st);
			st.Format(_T("old JN2...%d  " ), oldJN2);
			AfxMessageBox(st);
			st.Format(_T("old BM1...%d  " ), oldBM1);
			AfxMessageBox(st);
			st.Format(_T("old BM2...%d  " ), oldBM2);
			AfxMessageBox(st);
			*/
			
			continue;
		}
		
		//Check if no conditions were found then change the order of the conditions
		//and repeat the processs of checking repeated conditions
		if( jn2 == NOT_FOUND )
		{
			//CString str;
			//str.Format(_T("JN not found...%d  " ), jn2);
			//AfxMessageBox(str);
			
			
			rev_c1 = c2;
			rev_c2 = c1;
			rev_f1 = f2;
			rev_f2 = f1;
			rev_am1 = am2;
			rev_am2 = am1;

			//Check repeated conditions int inverse order	
			int rev_jn2 = checkingRepeatedCond(rev_c1, rev_c2, rev_am1, rev_am2, pm, link_var);
			
			//If the conditions are not found again
			//then revert the process again an reorder the conditions in the original way
			if(rev_jn2 != NOT_FOUND )
			{
				c1 = rev_c1;
				c2 = rev_c2;
				f1 = rev_f1;
				f2 = rev_f2;
				am1 = rev_am1;
				am2 = rev_am2;
				jn2 = rev_jn2;
				/*
				CString str;
				str.Format(_T("JN rev...%d  " ), jn2);
				AfxMessageBox(str);
			*/
											
			}
			else
			{
				rel_flag = true;
				
			}
			
			
		}
			//pMainFrame->m_wndOutputTabView.AddMsg1(_T("CICLO"));
			//no.printNode();
			
			//st.Format(_T("JN final...%d  " ), jn2);
			//AfxMessageBox(st);
			bm2 = no.findNodeBM2(jn2);
			

			//Generates a new Beta Memory Index
			newBM = bmo.generateBMKey();

			/*
			CString str;
			str.Format(_T("newBM...%d  " ), newBM);
			AfxMessageBox(str);
			*/

			//Creates Beta Memories of the RETE Netowrk
			createBM(c1, c2, f1, f2, am2, bm2, pm, newBM, link_var);
			pmo.addPM_BM(pm, newBM);
			
			
			
			
			/*
			CString str;
			str.Format(_T("2) bm2...%d  " ), bm2);
			AfxMessageBox(str);
			str.Format(_T("2) am...%d  " ), am);
			AfxMessageBox(str);
			*/
			//Creates the join node of RETE Network
			currentJN = createJN(c1, f1, c2, f2, pm, bm2, newBM, am2, link_var);
			checkPreBMCondBinding(c1, c2, am1,  am2, pm);
			
	
	}

	/*		
	//If there is repeated conditions in the current production
	//check if the conditions match
	s_repPM::iterator it;
	for (it = srepPM.begin(); it != srepPM.end(); ++it) 
	{
		checkPMRepCondMatch(*it);
  
    }
	*/
			

	//Creates all Beta Memories linked elements ( WM )
	createBME();
	//Creates all Production nodes
	createPNode();
	//Creates all linked tokens 
	tko.createTKParent_TKLink();
	co.clearPreCondBind();
	


	if( rel_flag == true)
	{
		pair <CMainFrame::g_mmPM_RelCond::iterator, CMainFrame::g_mmPM_RelCond::iterator>  pPM;
		pPM = pMainFrame->gmmPM_RelCond.equal_range(tempPM);
	
		for(CMainFrame::g_mmPM_RelCond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
		{	
			processRelCond(it_PM->second);
		}
	}

	//Analize numeric variables from the last pm conditions
	compareNumVars(tempPM);
	
	

return r;
}


//This process relational conditions with numeric constant comparison

int CAipi_RETE_Net::processRelCond(int rel_c)
{
	CAipi_PM		pmo;
	CAipi_RETE_BM	bmo;
	CAipi_RETE_AM	amo;
	CAipi_RETE_Node no;
	
	int bm2 = 0; 
	int r = NEGATIVE;
	int newBM = 0; 
	int rep = false;
	int rev_c1, rev_c2 = 0;
	int rev_f1, rev_f2 = 0;
	int rev_am1, rev_am2 =0;
	
	CAipi_RETE_Links linko;
	int rc = linko.findLinksMembers(rel_c);
	if( rc == NOT_FOUND )
	{
		return r;
	}
	
		int		c1			= rel_c;
		int		c2			= linko.getCond2();
		int		f1			= linko.getField1();
		int		f2			= linko.getField2();
		int		pm			= linko.getPM();
		tstring link_var	= linko.getVar(); 
		
		/*
		CString str;
		str.Format(_T("PM...%d  " ), pm);
		AfxMessageBox(str);
		str.Format(_T("Temp Num PM...%d  " ), tempNumPM);
		AfxMessageBox(str);
		*/
		/*
		AfxMessageBox(_T("Processed Rel Cond"));
		CString st;
		st.Format(_T("C1...%d  " ), c1);
		AfxMessageBox(st);
		st.Format(_T("C2...%d  " ), c2);
		AfxMessageBox(st);
	   */
		
		int am1 = amo.findCond_AM(c1);
		int am2 = amo.findCond_AM(c2);
					
				
		int jn2 = checkingRepeatedCond(c1, c2, am1, am2, pm, link_var);
		
		if( jn2 == REPEATED )
		{
			return REPEATED;
		}
		
		if( jn2 == NOT_FOUND )
		{
			rev_c1 = c2;
			rev_c2 = c1;
			rev_f1 = f2;
			rev_f2 = f1;
			rev_am1 = am2;
			rev_am2 = am1;

					
			int rev_jn2 = checkingRepeatedCond(rev_c1, rev_c2, rev_am1, rev_am2, pm, link_var);
			
			if(rev_jn2 != NOT_FOUND )
			{
				c1 = rev_c1;
				c2 = rev_c2;
				f1 = rev_f1;
				f2 = rev_f2;
				am1 = rev_am1;
				am2 = rev_am2;
				jn2 = rev_jn2;				
			}
			
		}
			
		
			bm2 = no.findNodeBM2(jn2);
			newBM = bmo.generateBMKey();

			/*
			CString str;
			str.Format(_T("newBM...%d  " ), newBM);
			AfxMessageBox(str);
			*/

			createBM(c1, c2, f1, f2, am2, bm2, pm, newBM, link_var);
			pmo.addPM_BM(pm, newBM);
			
			
			
			/*
			CString str;
			str.Format(_T("2) bm2...%d  " ), bm2);
			AfxMessageBox(str);
			str.Format(_T("2) am...%d  " ), am);
			AfxMessageBox(str);
			*/

			createJN(c1, f1, c2, f2, pm, bm2, newBM, am2, link_var);
	
			r = POSITIVE;		
		
		
		
		

return r;
}



int CAipi_RETE_Net::saveDataNum(int pm, int c2, int wm , int type, int bm, int old_tk, tstring varName, tstring varData )
{
	
	//Returns the beta memory(BM) who keeps the numeric variables
	
	CAipi_RETE_TypeDouble	typDouble;
	CAipi_RETE_TypeFloat	typFloat;
	CAipi_RETE_TypeInt		typInt;
	CAipi_RETE_TypeLong		typLong;
	CAipi_RETE_TypeString	typString;
	CAipi_LHS				lhso;
	int		intData = 0;
	long	longData =0;
	float	floatData = 0;
	double	doubleData = 0;
	
	int num_bm = UNDEFINE;


	/*
	AfxMessageBox(_T("VarName"));
	AfxMessageBox(varName.data());
	AfxMessageBox(_T("VarData"));
	AfxMessageBox(varData.data());
	CString st;
	st.Format(_T("PM...%d  " ), pm);
	AfxMessageBox(st);
	*/

/*	
	//CString st;
	st.Format(_T("Type...%d  " ), type);
	AfxMessageBox(st);
*/	

	switch( type )
	{
	case S_S_I :
		intData = _ttoi(varData.data());
		typInt.addTypeInt(varName, pm, c2, intData, wm, bm, old_tk);
		num_bm = bm;
		break;
	case S_S_L :
		longData = _ttol(varData.data());
		typLong.addTypeLong(varName, pm, c2, longData, wm, bm, old_tk);
		num_bm = bm;
		break;
	case S_S_F :
		floatData = _tcstod(varData.data(), NULL);
		typFloat.addTypeFloat(varName, pm, c2, floatData, wm, bm, old_tk);
		num_bm = bm;
		break;
	case S_S_D :
		doubleData = _tcstod(varData.data(), NULL);
		typDouble.addTypeDouble(varName, pm, c2, doubleData, wm, bm, old_tk);
		num_bm = bm;
		break;
	case S_S_S :
		typString.addTypeString(varName, pm, c2, varData, wm, bm, old_tk);
		num_bm = bm;
		break;
	
	}
	

	if( num_bm != UNDEFINE )
	{
		return num_bm;
	}

return NOT_FOUND;
}




int CAipi_RETE_Net::checkingVars(tstring var1, tstring var2, tstring var3, tstring data1, int old_tk, int bm, int newBM)
{

	/*** Nomenclature ***///
/*	

   
var1		= Variable name of Identifier(Id) for condition 1 (c1) 
			  [Beta Memory 1st class atribute (var1) ]
var2		= Variable name where condition 1(c1) and condition 2(c2) links  
			  [Beta Memory 3rd class atribute (var2) ] 		
var3		= Variable name of Value(Val) for condition 2 (c2)
		

data1		= Data component of Identifier(Id) for condition 1 (c1)
	          [Beta Memory 2nd class atribute (data1) ]
*/	
	/*** NOTES ***/	
/*
	Returns -10 when is testing a Dummy Node (DNode) (Where bm is equal to prevBM)
	Returns -20 when finds Parent Tokens from previous BM to the new created BM
	Returns -30 when finds Child Tokens from linked BM to the new created BM 
	Returns NOT_FOUND when it couldn´t find any link with variable
*/	
	
	CAipi_RETE_BM bmo;
	CAipi_RETE_DNode dn;
	int DN_BM = dn.lastBMDNode();
/*
	TCHAR buffer[4];
	AfxMessageBox(_T("bm : "));
	CString str =  _itot( bm, buffer, 10 );
	AfxMessageBox(str);
					
	AfxMessageBox(_T("newBM:"));
	str =  _itot( newBM, buffer, 10 );
	AfxMessageBox(str);
*/	
					
	int prevBM = newBM - 1;
/*	
	AfxMessageBox(_T("prevBM :"));
	str =  _itot( prevBM, buffer, 10 );
	AfxMessageBox(str);
*/					
			
	if( prevBM != DN_BM  )
	{
		/*
			AfxMessageBox(_T("VAR1"));
			AfxMessageBox(var1.data());
			AfxMessageBox(_T("VAR2"));
			AfxMessageBox(var2.data());
		*/	
		
		if( var1 != var2 )
		{
			int ptok = bmo.findBMParentTK(prevBM, old_tk);
			
			/*
			AfxMessageBox(_T("old_tk :"));
			str =  _itot( old_tk, buffer, 10 );
			AfxMessageBox(str);
			AfxMessageBox(_T("ptok :"));
			str =  _itot( ptok, buffer, 10 );
			AfxMessageBox(str);
			*/
			if( ptok == NOT_FOUND )
			{
				int ctok =  bmo.findBMChildTK(bm, old_tk);


				tstring bmVar1 = bmo.findBMVar1(bm, var1);
					
				/*
				AfxMessageBox(_T("Var3 :"));
				AfxMessageBox(var3.data());
					
				AfxMessageBox(_T("Var4 :"));
				AfxMessageBox(bmVar1.data());
				*/	
					if( bmVar1 == var3)
					{
						return -40;
					}
					
				/*
				AfxMessageBox(_T("old_tk :"));
				str =  _itot( old_tk, buffer, 10 );
				AfxMessageBox(str);
				AfxMessageBox(_T("ctok :"));
				str =  _itot( ctok, buffer, 10 );
				AfxMessageBox(str);
				*/
				if(ctok != NOT_FOUND)
				{
					
					
					tstring bmData2 = bmo.findBMData2ChildTK(bm, old_tk);
										
					/*
					AfxMessageBox(_T("DATA 1"));
					AfxMessageBox(data1.data());
					AfxMessageBox(_T("DATA 2"));
					AfxMessageBox(data2.data());
					*/
					
					
					if( data1 == bmData2 )
					{
						return -30;
					}
					else
					{
						return NOT_FOUND;
					}
					
				}
				
			}
			else
			{
				/*
				AfxMessageBox(_T("old_tk :"));
				str =  _itot( old_tk, buffer, 10 );
				AfxMessageBox(str);
				*/
				return -20;
			}
			

						
		}
	}

return -10;

}



int CAipi_RETE_Net::checkingRepeatedTK(int parent_tk, int wm)
{
	/*
	CString str;
	str.Format(_T("Parent TK...%d  " ), parent_tk);
	AfxMessageBox(str);
	str.Format(_T("Working Memory...%d  " ), wm);
	AfxMessageBox(str);
	*/
	
	CAipi_RETE_TK tko;
	int Tk = NOT_FOUND;
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmTKParent_TKChild::iterator iterTK;
	pair <CMainFrame::g_mmTKParent_TKChild::iterator, CMainFrame::g_mmTKParent_TKChild::iterator>  pTK;
	pTK = pMainFrame->gmmTKParent_TKChild.equal_range(parent_tk);
			
		for(iterTK = pTK.first; iterTK != pTK.second; ++iterTK)
		{	
			int chldTk = iterTK->second;
			Tk = tko.findTKMembers(chldTk);
			int tkWM = tko.m_WM ;
			/*
			CString str;
			str.Format(_T("Child TK...%d  " ), chldTk);
			AfxMessageBox(str);
			str.Format(_T("TK Working Memory...%d  " ), tkWM);
			AfxMessageBox(str);
			*/
			if( wm == tkWM )
			{
				//AfxMessageBox(_T("FOUND"));
				return REPEATED;
			}
			
		}

	

	
return Tk;
			
}




int CAipi_RETE_Net::checkingDNode(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_LHS lhso;
	CMainFrame::g_mDNode::iterator iter;
	
	if (!pMainFrame->gmDNode.empty())
	{
		for (iter = pMainFrame->gmDNode.begin(); iter != pMainFrame->gmDNode.end(); ++iter) 
		{
			bool dn = lhso.compareEqualCond(iter->first, c);
			if( dn != false )
			{
				return REPEATED;
			}
		}
	}


return NOT_FOUND;

}

/*
int CAipi_RETE_Net::checkingRepeatedCond(int c1, int c2, int am1, int am2)
{
	CAipi_RETE_Cond co;
	CAipi_RETE_NodeCond no;
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmRepCond::iterator iter1;
	CMainFrame::g_mmRepCond::iterator iter2;
	
	pair <CMainFrame::g_mmRepCond::iterator, CMainFrame::g_mmRepCond::iterator>  pIt1;
	pair <CMainFrame::g_mmRepCond::iterator, CMainFrame::g_mmRepCond::iterator>  pIt2;
	
	//Search equal conditions in the corresponding Alpha Memory
	int rc1 = findEqualCond(am1, c1);
	int rc2 = findEqualCond(am2, c2);

	AfxMessageBox(_T("CURRENT CONDITIONS"));
	
	CString st;	
	st.Format(_T("C1...%d  " ), c1);
	AfxMessageBox(st);
	st.Format(_T("C2...%d  " ), c2);
	AfxMessageBox(st);

	AfxMessageBox(_T("REPEATED CONDITIONS"));
	
	//CString st;	
	st.Format(_T("Repeated C1...%d  " ), rc1);
	AfxMessageBox(st);
	st.Format(_T("Repeated C2...%d  " ), rc2);
	AfxMessageBox(st);
	
	//If the current condition is different from the condition found in AM
	//then they are repeated.
	if( c1 != rc1 && c2 != rc2 )
	{
		AfxMessageBox(_T("Condiciones Diferentes"));
		
		pIt1 = pMainFrame->gmmRepCond.equal_range(rc1);
		pIt2 = pMainFrame->gmmRepCond.equal_range(rc2);
	
	
		for(iter1 = pIt1.first; iter1 != pIt1.second; ++iter1)
		{
			CAipi_RepCond rco1 = (CAipi_RepCond)iter1->second;
			int pm1 = rco1.getPM2();
			
			
			CString str;
			str.Format(_T("PM1...%d  " ), pm1);
			AfxMessageBox(str);
				
			for(iter2 = pIt2.first; iter2 != pIt2.second; ++iter2)
			{
				CAipi_RepCond rco2 = (CAipi_RepCond)iter2->second;
				int pm2 = rco2.getPM2();
				
				
				CString str;
				str.Format(_T("PM2...%d  " ), pm2);
				AfxMessageBox(str);
				
				
				//Check if the conditions belongs to the same production
				if( pm1 == pm2 )
				{
					AfxMessageBox(_T("PM1 = PM2"));

					CAipi_RETE_DNode dno;
					int dnPM = dno.lastPMDNode();

					
					CString str;
					str.Format(_T("Dnode PM...%d  " ), dnPM);
					AfxMessageBox(str);
					str.Format(_T("Current PM...%d  " ), pm);
					AfxMessageBox(str);
					

					//Check special case when the production genereates a DummyNode (DNode)
					//Then returns the respective node
					if( dnPM == pm)
					{
						int jn2 = co.findCond2JN(c1);
						AfxMessageBox(_T("RETURN DUMMY NONE"));
						return jn2;
					}
					
					//Otherwise updates other structures and return REPEATED
					int j1 = co.findCond1JN(rc1);
					int j2 = co.findCond2JN(rc2);

					co.addCond1(c1, j1, pm, var);
					co.addCond2(c2, j2, pm, var);
					no.addNodeCond(j2, c1, c2, pm);

					AfxMessageBox(_T("RETURN REPEATED"));

					return REPEATED;
				}
			}
		}
	}
	//If the current conditions are equal to the ones found in AM
	//Then return the join node
	else
	{
		int jn2 = co.findCond2JN(rc1);
		
		
		CString str;
		str.Format(_T("JN2...%d  " ), jn2);
		AfxMessageBox(str);
		
		AfxMessageBox(_T("RETURN JN"));
		return jn2;
	}
	
//If the conditions doesnt exist the reutrn NOT FOUND
AfxMessageBox(_T("RETURN NOT_FOUND"));
return NOT_FOUND;
}
*/


//This function checks if the current conditions are repeated
//If they are repeated returns REPEATED
//If they are not repeated return the respective join node (JNode)
//If the condition doesn´t exist return NOT_FOUND (This should never happen)
int CAipi_RETE_Net::checkingRepeatedCond(int c1, int c2, int am1, int am2, long pm, tstring var )
{
	CAipi_RETE_Cond co;
	CAipi_RETE_NodeCond no;
	CAipi_RepCond rco;
	
	//Search equal conditions in the corresponding Alpha Memory
	int rc1 = findEqualCond(am1, c1);
	int rc2 = findEqualCond(am2, c2);

	/*
	
	AfxMessageBox(_T("CURRENT CONDITIONS"));
	
	CString st;	
	st.Format(_T("C1...%d  " ), c1);
	AfxMessageBox(st);
	st.Format(_T("C2...%d  " ), c2);
	AfxMessageBox(st);
	

	AfxMessageBox(_T("REPEATED CONDITIONS"));
	
	//CString st;	
	st.Format(_T("Repeated C1...%d  " ), rc1);
	AfxMessageBox(st);
	st.Format(_T("Repeated C2...%d  " ), rc2);
	AfxMessageBox(st);
	*/
	

	

	//If the current condition is different from the condition found in AM
	//then they are repeated.
	if( c1 != rc1 && c2 != rc2 )
	{
		
		CAipi_RETE_DNode dno;
		int dnPM = dno.lastPMDNode();

		/*
			CString str;
			str.Format(_T("Dnode PM...%d  " ), dnPM);
			AfxMessageBox(str);
			str.Format(_T("Current PM...%d  " ), pm);
			AfxMessageBox(str);
		*/

		//Check special case when the production genereates a DummyNode (DNode)
		//Then returns the respective node
		if( dnPM == pm)
		{
			int jn2 = co.findCond2JN(c1);
			//AfxMessageBox(_T("RETURN DUMMY NONE"));
			return jn2;
		}
					
		//Otherwise updates other structures and return REPEATED
		int j2 = co.findCond2JN(rc2);
		int j1 = co.findCond1JN(rc1);
		/*
		CString str;
		str.Format(_T("JN1...%d  " ), j1);
		AfxMessageBox(str);
		str.Format(_T("JN2...%d  " ), j2);
		AfxMessageBox(str);
		*/

		
		//Check if this conditions were linked before
		//If they were no,t then return the join node so it can create a new BM
		//When join nodes are different, the links could not be right ( check it!!!)
		if( j1 != j2 )
		{
			CAipi_RETE_Links lko;
			int r = lko.checkRepLinks(rc1, rc2, c1, c2);
			if( r == NOT_FOUND )
			{
				int jn2 = co.findCond2JN(rc1);
				//AfxMessageBox(_T("Not Found"));
				
				/*
				CString str;
				str.Format(_T("JN2...%d  " ), jn2);
				AfxMessageBox(str);
				*/
				return jn2;
			}
		}


		co.addCond1(c1, j1, pm, var);
		co.addCond2(c2, j2, pm, var);
		no.addNodeCond(j2, c1, c2, pm);

		//AfxMessageBox(_T("RETURN REPEATED"));

		return REPEATED;
		
		
	}
	//If the current conditions are equal to the ones found in AM
	//Then they are not repeated, is he first time they get found, return the join node
	else
	{
		//co.printCond1();
		//co.printCond2();
		
		int jn2 = co.findCond2JN(rc1);
		
		
		/*
		CString str;
		str.Format(_T("RC1...%d  " ), rc1);
		AfxMessageBox(str);
		
		str.Format(_T("JN2...%d  " ), jn2);
		AfxMessageBox(str);
		*/
		//AfxMessageBox(_T("RETURN JN"));
		return jn2;
	}
	
//If the conditions doesnt exist the reutrn NOT FOUND
//AfxMessageBox(_T("RETURN NOT_FOUND"));
return NOT_FOUND;
}


//This function checks matching process of productions with repeated conditions
int CAipi_RETE_Net::checkPMRepCondMatch(long pm)
{
	int match = UNDEFINE;
	
	CAipi_PM pmo;
	
	int firstPMCond = pmo.PM_CondLowerBound(pm);
	int lastPMCond = pmo.PM_CondUpperBound(pm);
	CString str;
	str.Format(_T("production...%d  " ), pm);
	/*
	AfxMessageBox(str);
	str.Format(_T("first condition...%d  " ), firstPMCond);
	AfxMessageBox(str);
	str.Format(_T("last condition...%d  " ), lastPMCond);
	AfxMessageBox(str);
	*/
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmLink::iterator iter1;
	iter1 = pMainFrame->gmmLink.find(firstPMCond);
	
	for( CMainFrame::g_mmLink::const_iterator iter = iter1; iter!= pMainFrame->gmmLink.end(); ++iter)
	{
		CAipi_RETE_Links lko = (CAipi_RETE_Links)iter->second;
 		int c1 = iter->first;
		int f1 = lko.getField1();
		int c2 = lko.getCond2();
		int f2 = lko.getField2();
		tstring var = lko.getVar();
		/*
		str.Format(_T("condition1...%d  " ), c1);
		AfxMessageBox(str);
		str.Format(_T("condition2...%d  " ), c2);
		AfxMessageBox(str);
		*/

		match = matchRepCondField(c1, c2, f1, f2, var);
				
		if( c2 == lastPMCond )
		{
			break;
		}
	}		
	

return match;
}

//NOT CORRECT
//Check the other with more parameters
//Is the same as matchRepCondField but without the fields parameters
int CAipi_RETE_Net::matchRepCond(int c1, int c2 )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_WM::iterator iterAM;
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmAM_WM::iterator, CMainFrame::g_mmAM_WM::iterator>  pAM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	int wm1 = NOT_FOUND;
	int wm2 = NOT_FOUND;
	int match = NEGATIVE;
	int par_tk, chd_tk = UNDEFINE;
	int num_bm = UNDEFINE;

	tstring field1, field2;
	tstring varId1 =  _T("Undef");
	tstring dataId1 = _T("Undef");
	
	CAipi_RETE_TK		tko;
	CAipi_WM			wmo;
	CAipi_RETE_BM		bmo;
	CAipi_RETE_AM		amo;
	CAipi_LHS			lhso;
	CAipi_RETE_Cond		co;
	CAipi_RETE_Node		no;
	CAipi_RETE_Links	lnko;


	lnko.findLinksMembers(c1);
	int f1 = lnko.m_Field1;
	int f2 = lnko.m_Field2;
	
	int jn = co.findCond2JN(c1);
	if( jn == NOT_FOUND)
	{
		jn = co.findCond1JN(c1);
	}
	int bm = no.findNodeBM2(jn);
	int am = amo.findCond_AM(c2);

		/*
			CString st;
			st.Format(_T("c1...%d  " ), c1);
			AfxMessageBox(st);
			st.Format(_T("c2...%d  " ), c2);
			AfxMessageBox(st);
			
			st.Format(_T("f1...%d  " ), f1);
			AfxMessageBox(st);
			st.Format(_T("f2...%d  " ), f2);
			AfxMessageBox(st);
			st.Format(_T("jn...%d  " ), jn);
			AfxMessageBox(st);
			st.Format(_T("bm...%d  " ), bm);
			AfxMessageBox(st);
			st.Format(_T("am...%d  " ), am);
			AfxMessageBox(st);
	*/
	
		
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
 		
		/*
		int tk= bmo.getChildTK();
		tko.findTKMembers(tk);
		wm1 = tko.m_WM;
		child = tko.m_ChildTK;
		*/
		
		wm1 = bmo.getWM();
		lhso.findWMMembers(wm1);

		par_tk = bmo.getParentTK();
		chd_tk  = bmo.getChildTK();
		
		
		/*	
		
		TCHAR buffer[4];
		CString str;
		AfxMessageBox(_T("Parent Tk :"));
		str =  _itot( par_tk, buffer, 10 );
		AfxMessageBox(str);
		AfxMessageBox(_T("Child Tk :"));
		str =  _itot( chd_tk, buffer, 10 );
		AfxMessageBox(str);
		*/
		

		switch(f1)
		{
		case AIPI_ID:
			field1 = lhso.m_Id;
			break;
		case AIPI_AT:
			field1 = lhso.m_Attr;	
			break;
		case AIPI_VL:
			field1 = lhso.m_Val;
			dataId1 = lhso.m_Id;
			break;
		}
														
			pAM = pMainFrame->gmmAM_WM.equal_range(am);

			for(iterAM = pAM.first; iterAM != pAM.second; ++iterAM)
			{	
				wm2 = iterAM->second;
				lhso.findWMMembers(wm2);
			
				switch(f2)
				{
				case AIPI_ID:
					field2 = lhso.m_Id;
					break;
				case AIPI_AT:
					field2 = lhso.m_Attr;	
					break;
				case AIPI_VL:
					field2 = lhso.m_Val;
					break;
				}
				
				

				if( field1 == field2 )
				{
					//AfxMessageBox(field1.data());
					match = POSITIVE;
				}
			}
	}

	/*
CString str;
str.Format(_T("MATCH %d"), match);
AfxMessageBox(str);
*/							
return match;

}


//This function match conditions that already exist in others productions
//It is based on already exist an Betra Memory and a Join Node for this conditions
//Has similar process of function createBM but it doesn´t creates BM because they already exist
int CAipi_RETE_Net::matchRepCondField(int c1, int c2, int f1, int f2,tstring var )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_WM::iterator iterAM;
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmAM_WM::iterator, CMainFrame::g_mmAM_WM::iterator>  pAM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	int wm1 = NOT_FOUND;
	int wm2 = NOT_FOUND;
	int match = NEGATIVE;
	//int par_tk, chd_tk = UNDEFINE;
	int num_bm = UNDEFINE;
	
	tstring field1, field2;
	tstring varId1 =  _T("Undef");
	tstring dataId1 = _T("Undef");
	
	CAipi_RETE_TK		tko;
	CAipi_WM			wmo;
	CAipi_RETE_BM		bmo;
	CAipi_RETE_AM		amo;
	CAipi_LHS			lhso;
	CAipi_RETE_Cond		co;
	CAipi_RETE_Node		no;
	
	int jn = UNDEFINE;
	tstring vr1 = co.findCond1Var(c1);
	tstring vr2 = co.findCond2Var(c2);


	if( vr2 == var)
	{
		//AfxMessageBox(_T("Aserto C2"));
		jn = co.findCond2JN(c2);
	}
	else if( vr1 == var )
	{
		//AfxMessageBox(_T("Aserto C1"));
		jn = co.findCond1JN(c1);
	}
	
	
	
	int bm = no.findNodeBM1(jn);
	int am = amo.findCond_AM(c2);

			/*
			CString st;
			st.Format(_T("c1...%d  " ), c1);
			AfxMessageBox(st);
			st.Format(_T("c2...%d  " ), c2);
			AfxMessageBox(st);

			
			AfxMessageBox(_T("Var:"));
			AfxMessageBox(var.data());
	
			
			st.Format(_T("f1...%d  " ), f1);
			AfxMessageBox(st);
			st.Format(_T("f2...%d  " ), f2);
			AfxMessageBox(st);
			st.Format(_T("jn...%d  " ), jn);
			AfxMessageBox(st);
			st.Format(_T("bm...%d  " ), bm);
			AfxMessageBox(st);
			st.Format(_T("am...%d  " ), am);
			AfxMessageBox(st);
			*/
	
		
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
 		
		/*
		int tk= bmo.getChildTK();
		tko.findTKMembers(tk);
		wm1 = tko.m_WM;
		child = tko.m_ChildTK;
		*/
		
		wm1 = bmo.getWM();
		lhso.findWMMembers(wm1);
		/*
		CString s;
		s.Format(_T("wm1...%d  " ), wm1);
		AfxMessageBox(s);
		*/	
	
		//par_tk = bmo.getParentTK();
		//chd_tk  = bmo.getChildTK();
		
		
		/*	
		
		TCHAR buffer[4];
		CString str;
		AfxMessageBox(_T("Parent Tk :"));
		str =  _itot( par_tk, buffer, 10 );
		AfxMessageBox(str);
		AfxMessageBox(_T("Child Tk :"));
		str =  _itot( chd_tk, buffer, 10 );
		AfxMessageBox(str);
		*/
		

		switch(f1)
		{
		case AIPI_ID:
			field1 = lhso.m_Id;
			break;
		case AIPI_AT:
			field1 = lhso.m_Attr;	
			break;
		case AIPI_VL:
			field1 = lhso.m_Val;
			dataId1 = lhso.m_Id;
			//AfxMessageBox(_T("field1"));
			//AfxMessageBox(field1.data());
			break;
		}
														
			pAM = pMainFrame->gmmAM_WM.equal_range(am);

			for(iterAM = pAM.first; iterAM != pAM.second; ++iterAM)
			{	
				wm2 = iterAM->second;
				lhso.findWMMembers(wm2);

				/*
				CString s;
				s.Format(_T("wm2...%d  " ), wm2);
				AfxMessageBox(s);
				*/
			
				switch(f2)
				{
				case AIPI_ID:
					field2 = lhso.m_Id;
					//AfxMessageBox(_T("filed2"));
					//AfxMessageBox(field2.data());
					break;
				case AIPI_AT:
					field2 = lhso.m_Attr;	
					break;
				case AIPI_VL:
					field2 = lhso.m_Val;
					break;
				}
				
				

				if( field1 == field2 )
				{
					//AfxMessageBox(field1.data());
					match = POSITIVE;
				}
			}
	}
/*
CString str;
str.Format(_T("MATCH %d"), match);
AfxMessageBox(str);
*/							
return match;

}


void CAipi_RETE_Net::createAM()
{
	//constantTest();
	CAipi_RETE_AM amo;
	amo.constantTestIForm();
	amo.insertStructsWM_AM();

}


void CAipi_RETE_Net::createPNode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_RETE_PNode pno;
	
	for( CMainFrame::g_mPM::const_iterator iter = pMainFrame->gmPM.begin(); iter!= pMainFrame->gmPM.end(); ++iter)
	{
		pno.definePNode(iter->first);
	}

	//Saves fired PM
	pno.saveFiredPM();

}

int CAipi_RETE_Net::createBM(int c1, int c2, int f1, int f2, int am, int bm, int pm, int newBM, tstring link_var)
{
	/*** Nomenclature ***///
						  /*	
					  
	link_var	= Variable name where condition 1(c1) and condition 2(c2) links   
	VarId1		= Variable name of Identifier(Id) for condition 1 (c1)
	VarId2		= Variable name of Identifier(Id) for condition 2 (c2)
	VarVal1		= Variable name of Value(Val) for condition 1 (c1)
	VarVal2		= Variable name of Value(Val) for condition 2 (c2)
				
	 dataId1	= Data component of Identifier(Id) for condition 1 (c1)
	 dataId2	= Data component of Identifier(Id) for condition 2 (c2)
	 dataVal1	= Data component of Value(Val) for condition 1 (c1)
	 dataVal2	= Data component of Value(Val) for condition 2 (c2)
							  
	*/
	
	/*		
	CString st;
	st.Format(_T("C1...%d  " ), c1);
	AfxMessageBox(st);
	st.Format(_T("C2...%d  " ), c2);
	AfxMessageBox(st);
	st.Format(_T("Link Var...%s  " ), link_var.c_str());
	AfxMessageBox(st);
	
	
	   
	   st.Format(_T("AM...%d  " ), am);
	   AfxMessageBox(st);
	   st.Format(_T("BM...%d  " ), bm);
	   AfxMessageBox(st);
	   st.Format(_T("New BM...%d  " ), newBM);
	   AfxMessageBox(st);
	
	*/
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_WM::iterator iterAM;
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmAM_WM::iterator, CMainFrame::g_mmAM_WM::iterator>  pAM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	int wm1 = NOT_FOUND; 
	int	wm2 = NOT_FOUND;
	int match = NEGATIVE;
	int par_tk, chd_tk = UNDEFINE;
	int num_bm = UNDEFINE;
	
	tstring field1, field2;
	tstring varId1 =  _T("Undef");
	tstring dataId1 = _T("Undef");

	tstring varId2 =  _T("Undef");
	tstring dataId2 = _T("Undef");
	
	tstring varVal2 = _T("Undef");
	tstring dataVal2 = _T("Undef");

	CAipi_RETE_TK	tko;
	CAipi_WM		wmo;
	CAipi_RETE_BM	bmo;
	CAipi_LHS		lhso;
	
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
		
		/*
		int tk= bmo.getChildTK();
		tko.findTKMembers(tk);
		wm1 = tko.m_WM;
		child = tko.m_ChildTK;
		*/
		
		wm1 = bmo.getWM();
		lhso.findWMMembers(wm1);
		
		par_tk = bmo.getParentTK();
		chd_tk  = bmo.getChildTK();
		
		
		/*	
		
		  TCHAR buffer[4];
		  CString str;
		  AfxMessageBox(_T("Parent Tk :"));
		  str =  _itot( par_tk, buffer, 10 );
		  AfxMessageBox(str);
		  AfxMessageBox(_T("Child Tk :"));
		  str =  _itot( chd_tk, buffer, 10 );
		  AfxMessageBox(str);
		*/
		
		
		switch(f1)
		{
		case AIPI_ID:
			field1 = lhso.m_Id;
			//AfxMessageBox(_T("Field1"));
			//AfxMessageBox(field1.c_str());
			break;
		case AIPI_AT:
			field1 = lhso.m_Attr;	
			break;
		case AIPI_VL:
			field1 = lhso.m_Val;
			dataId1 = lhso.m_Id;
			//AfxMessageBox(_T("Field1"));
			//AfxMessageBox(field1.c_str());
			break;
		}
		
		pAM = pMainFrame->gmmAM_WM.equal_range(am);
		
		for(iterAM = pAM.first; iterAM != pAM.second; ++iterAM)
		{	
			wm2 = iterAM->second;
			lhso.findWMMembers(wm2);

			//CString st;
			//st.Format(_T("WM of AM...%d  " ), wm2);
			//AfxMessageBox(st);
			
			if( wm2 == NOT_FOUND )
			{
			/*
			TCHAR buffer[4];
			CString str;
			AfxMessageBox(_T("CREATE BM:"));
			AfxMessageBox(_T("AM :"));
			str =  _itot( iterAM->first, buffer, 10 );
			AfxMessageBox(str);
			AfxMessageBox(_T("WM :"));
			str =  _itot( wm2, buffer, 10 );
			AfxMessageBox(str);
			*/	
			}
			
			switch(f2)
			{
			case AIPI_ID:
				field2 = lhso.m_Id;
				dataId2 = wmo.findWMId(wm2);
				//AfxMessageBox(_T("Field2"));
				//AfxMessageBox(field2.c_str());
				break;
			case AIPI_AT:
				field2 = lhso.m_Attr;	
				break;
			case AIPI_VL:
				field2 = lhso.m_Val;
				varVal2 = lhso.m_lhsVal;	
				//AfxMessageBox(_T("Field2"));
				//AfxMessageBox(field2.c_str());
				//AfxMessageBox(varVal2.c_str());
				break;
			}
			
			
			
			if( field1 == field2 )
			{
				
				varId1 = lhso.findLHSId(c1);	
				lhso.findLHSMembers(c2);
				varId2 = lhso.m_lhsId; 
				varVal2 = lhso.m_lhsVal;
				dataVal2 = lhso.m_Val;

				/*
				CString s;
				s.Format(_T("CONDITION...%d  " ), c2);
				AfxMessageBox(s);
				s.Format(_T("LHS Value...%s  " ), varVal2.c_str());
				AfxMessageBox(s);
				*/

				int categ2 = lhso.m_Category;
				int type = lhso.m_Type;
				int rel = lhso.m_Rel;
				
				int old_tk = bmo.searchWMTK(bm, wm1, par_tk);
				
				/*
				TCHAR buffer[4];
				CString str;
				AfxMessageBox(_T("OLD TOKEN"));
				str =  _itot( old_tk, buffer, 10 );
				AfxMessageBox(str);
				*/
				
				if( old_tk != NOT_FOUND ) 
				{
					//AfxMessageBox(_T("OLD TK FOUND"));						
					
					if( rel == AS )
					{
						num_bm = saveDataNum(pm, c2, wm2, type, newBM, old_tk, varVal2, dataVal2);
					}
					
					
					int tk = checkingVars(varId1, link_var, varVal2, dataId1, old_tk, bm, newBM);
					if (tk == -40 )
					{
						tstring bmData1 = bmo.findBMData1ChildTK(bm, old_tk);
						
						/*
						TCHAR buffer[4];
						CString str;
						AfxMessageBox(_T("Checking Vars -40 :"));
						str =  _itot( wm2, buffer, 10 );
						AfxMessageBox(str);
						*/
						
						if( bmData1 != dataVal2)
						{
							//AfxMessageBox(_T("CONTINUE 1"));
							continue;
						}
						
					}
					
					
					
					if( tk == NOT_FOUND)
					{
						//Aquí falla chequear despues
						//AfxMessageBox(_T("CONTINUE 2"));
						/*
						CString str;
						str.Format(_T("C1...%d  " ), c1);
						AfxMessageBox(str);
						str.Format(_T("C2...%d  " ), c2);
						AfxMessageBox(str);
						*/
						//continue;
					}
					
					
					//Check for repeated tokens in BM
					//Avoid repeated tokens tokens
					int rTk = checkingRepeatedTK( old_tk, wm2);
					if( rTk == REPEATED )
					{
						//AfxMessageBox(_T("CONTINUE 3"));
						continue;
					}
					
					
					
					int new_tk = tko.generateTKKey();
					tko.createTK(new_tk, old_tk, wm2, newBM, JNode);
					bmo.addBM(newBM, varId1, dataId1, link_var, field2, old_tk, new_tk, wm2);
					tko.addWM_ParentTK(wm2, old_tk);
					tko.addWM_ChildTK(wm2, new_tk);
					tko.addTKParent_TKChild(old_tk, new_tk);
					
					match = POSITIVE;
					
					/*		
					CString str;
					str.Format(_T("OLD TK...%d  " ), old_tk);
					AfxMessageBox(str);
					str.Format(_T("NEW TK...%d  " ), new_tk);
					AfxMessageBox(str);
					str.Format(_T("NEW BM...%d  " ), newBM);
					AfxMessageBox(str);
					*/	
					
					
				}
				
				
			}
			
			
			}
			
			/*
			AfxMessageBox(_T("N Tokens :"));
			str =  _itot( nTokens, buffer, 10 );
			AfxMessageBox(str);
			AfxMessageBox(_T("Cont :"));
			str =  _itot( cont, buffer, 10 );
			AfxMessageBox(str);
			*/
			
			
			
	}
	
	/*
	//Handle instrucction FOR_ALL
	int n1 = bmo.countBM_TK(b);
	int n2 = bmo.countBM_TK(newBM);
	CString str;				
	str.Format(_T("BM1 n1...%d  " ), n1);
	AfxMessageBox(str);
	str.Format(_T("BM2 n2...%d  " ), n2);
	AfxMessageBox(str);
	
	  if( n1 == n2 )
	  {
	  
		AfxMessageBox(_T("FOR_ALL Cumple"));
		}
		*/
		
		if( match == NEGATIVE || (num_bm != UNDEFINE && match == NEGATIVE) )
		{
		/*
		AfxMessageBox(_T("No-Match"));
		CString str;				
		str.Format(_T("WM...%d  " ), wm2);
		AfxMessageBox(str);
		str.Format(_T("BM...%d  " ), newBM);
		AfxMessageBox(str);
			*/
			/*
			str.Format(_T("C1...%d  " ), c1);
			AfxMessageBox(str);
			str.Format(_T("C2...%d  " ), c2);
			AfxMessageBox(str);
			*/
			
			varId1 = lhso.findLHSId(c1);
			bmo.addBM(newBM, varId1, dataId1, link_var, field2, UNDEFINE, UNDEFINE, wm2);
		}
		
		
		/*
		
		  CString str;				
		  str.Format(_T("Match Result...%d  " ), match);
		  AfxMessageBox(str);
		  
		*/	
		
		
		return match;
		
}


int CAipi_RETE_Net::assertUpdateCreateBM(int c1, int c2, int f1, int f2, int am, int bm, int pm, int newBM, tstring link_var)
{
	/*** Nomenclature ***///
						  /*	
						  
							link_var	= Variable name where condition 1(c1) and condition 2(c2) links   
							VarId1		= Variable name of Identifier(Id) for condition 1 (c1)
							VarId2		= Variable name of Identifier(Id) for condition 2 (c2)
							VarVal1		= Variable name of Value(Val) for condition 1 (c1)
							VarVal2		= Variable name of Value(Val) for condition 2 (c2)
							
							  dataId1		= Data component of Identifier(Id) for condition 1 (c1)
							  dataId2		= Data component of Identifier(Id) for condition 2 (c2)
							  dataVal1	= Data component of Value(Val) for condition 1 (c1)
							  dataVal2	= Data component of Value(Val) for condition 2 (c2)
							  
	*/
	
	/*		
	CString st;
	st.Format(_T("C1...%d  " ), c1);
	AfxMessageBox(st);
	st.Format(_T("C2...%d  " ), c2);
	AfxMessageBox(st);
	*/
	   /*
	   st.Format(_T("AM...%d  " ), am);
	   AfxMessageBox(st);
	   st.Format(_T("BM...%d  " ), bm);
	   AfxMessageBox(st);
	   st.Format(_T("New BM...%d  " ), newBM);
	   AfxMessageBox(st);
	*/
	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_WM::iterator iterAM;
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmAM_WM::iterator, CMainFrame::g_mmAM_WM::iterator>  pAM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	int wm1 = NOT_FOUND; 
	int	wm2 = NOT_FOUND;
	int match = NEGATIVE;
	int par_tk, chd_tk = UNDEFINE;
	int num_bm = UNDEFINE;
	
	tstring field1, field2;
	tstring varId1 =  _T("Undef");
	tstring dataId1 = _T("Undef");
	
	CAipi_RETE_TK	tko;
	CAipi_WM		wmo;
	CAipi_RETE_BM	bmo;
	CAipi_LHS		lhso;
	
	pBM = pMainFrame->gmmBM.equal_range(bm);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
		
		/*
		int tk= bmo.getChildTK();
		tko.findTKMembers(tk);
		wm1 = tko.m_WM;
		child = tko.m_ChildTK;
		*/
		
		wm1 = bmo.getWM();
		lhso.findWMMembers(wm1);
		
		par_tk = bmo.getParentTK();
		chd_tk  = bmo.getChildTK();
		
		
		/*	
		
		  TCHAR buffer[4];
		  CString str;
		  AfxMessageBox(_T("Parent Tk :"));
		  str =  _itot( par_tk, buffer, 10 );
		  AfxMessageBox(str);
		  AfxMessageBox(_T("Child Tk :"));
		  str =  _itot( chd_tk, buffer, 10 );
		  AfxMessageBox(str);
		*/
		
		
		switch(f1)
		{
		case AIPI_ID:
			field1 = lhso.m_Id;
			break;
		case AIPI_AT:
			field1 = lhso.m_Attr;	
			break;
		case AIPI_VL:
			field1 = lhso.m_Val;
			dataId1 = lhso.m_Id;
			break;
		}
		
		pAM = pMainFrame->gmmAM_WM.equal_range(am);
		
		for(iterAM = pAM.first; iterAM != pAM.second; ++iterAM)
		{	
			wm2 = iterAM->second;
			lhso.findWMMembers(wm2);
			
			if( wm2 == NOT_FOUND )
			{
				/*
				TCHAR buffer[4];
				CString str;
				AfxMessageBox(_T("UPDATE BM :"));
				AfxMessageBox(_T("AM :"));
				str =  _itot( iterAM->first, buffer, 10 );
				AfxMessageBox(str);
				AfxMessageBox(_T("WM :"));
				str =  _itot( wm2, buffer, 10 );
				AfxMessageBox(str);
				*/
			}
			
			switch(f2)
			{
			case AIPI_ID:
				field2 = lhso.m_Id;
				break;
			case AIPI_AT:
				field2 = lhso.m_Attr;	
				break;
			case AIPI_VL:
				field2 = lhso.m_Val;
				break;
			}
			
			
			
			if( field1 == field2 )
			{
				
				varId1 = lhso.findLHSId(c1);	
				lhso.findLHSMembers(c2);
				
				tstring varId2 = lhso.m_lhsId; 
				tstring varVal2 = lhso.m_lhsVal;
				tstring dataVal2 = lhso.m_Val;
				
				int categ2 = lhso.m_Category;
				int type = lhso.m_Type;
				int rel = lhso.m_Rel;
				
				int old_tk = bmo.searchWMTK(bm, wm1, par_tk);
				
				/*
				TCHAR buffer[4];
				CString str;
				AfxMessageBox(_T("OLD TOKEN"));
				str =  _itot( old_tk, buffer, 10 );
				AfxMessageBox(str);
				*/
				
				if( old_tk != NOT_FOUND ) 
				{
					//AfxMessageBox(_T("OLD TK FOUND"));						
					
					if( rel == AS )
					{
						num_bm = saveDataNum(pm, c2, wm2, type, newBM, old_tk, varVal2, dataVal2);
					}
					
					
					int tk = checkingVars(varId1, link_var, varVal2, dataId1, old_tk, bm, newBM);
					if (tk == -40 )
					{
						tstring bmData1 = bmo.findBMData1ChildTK(bm, old_tk);
						
						
						
						//TCHAR buffer[4];
						//CString str;
						//AfxMessageBox(_T("Checking Vars -40 :"));
						//str =  _itot( wm2, buffer, 10 );
						//AfxMessageBox(str);
						
						
						if( bmData1 != dataVal2)
						{
							//AfxMessageBox(_T("CONTINUE 1"));
							continue;
						}
					}
					
					if( tk == NOT_FOUND)
					{
						//Aquí falla chequear despues
						//AfxMessageBox(_T("CONTINUE 2"));
						//continue;
					}
					
					//Check for repeated tokens in BM
					//Avoid repeated tokens tokens
					int rTk = checkingRepeatedTK( old_tk, wm2);
					if( rTk == REPEATED )
					{
						continue;
					}
					
					
					
					int new_tk = tko.generateTKKey();
					tko.createTK(new_tk, old_tk, wm2, newBM, JNode);
					bmo.addBM(newBM, varId1, dataId1, link_var, field2, old_tk, new_tk, wm2);
					tko.addWM_ParentTK(wm2, old_tk);
					tko.addWM_ChildTK(wm2, new_tk);
					tko.addTKParent_TKChild(old_tk, new_tk);
					tko.addTKParent_TKLink(old_tk, new_tk);
					
					match = POSITIVE;
					
					/*		
					CString str;
					str.Format(_T("OLD TK...%d  " ), old_tk);
					AfxMessageBox(str);
					str.Format(_T("NEW TK...%d  " ), new_tk);
					AfxMessageBox(str);
					str.Format(_T("NEW BM...%d  " ), newBM);
					AfxMessageBox(str);
					*/	
					
					
				}
				
				
			}
			
			
			}
			
			/*
			AfxMessageBox(_T("N Tokens :"));
			str =  _itot( nTokens, buffer, 10 );
			AfxMessageBox(str);
			AfxMessageBox(_T("Cont :"));
			str =  _itot( cont, buffer, 10 );
			AfxMessageBox(str);
			*/
			
			
			
	}
	
	/*
	//Handle instrucction FOR_ALL
	int n1 = bmo.countBM_TK(b);
	int n2 = bmo.countBM_TK(newBM);
	CString str;				
	str.Format(_T("BM1 n1...%d  " ), n1);
	AfxMessageBox(str);
	str.Format(_T("BM2 n2...%d  " ), n2);
	AfxMessageBox(str);
	
	  if( n1 == n2 )
	  {
	  
		AfxMessageBox(_T("FOR_ALL Cumple"));
		}
		*/
		
		if( match == NEGATIVE || (num_bm != UNDEFINE && match == NEGATIVE) )
		{
			//AfxMessageBox(_T("No-Match"));
			varId1 = lhso.findLHSId(c1);
			bmo.addBM(newBM, varId1, dataId1, link_var, field2, UNDEFINE, UNDEFINE, wm2);
		}
		
		
		/*
		
		  CString str;				
		  str.Format(_T("Match Result...%d  " ), match);
		  AfxMessageBox(str);
		  
		*/	
		
		
		return match;
		
}




void CAipi_RETE_Net::createBME()
{
	CAipi_RETE_BM bmo;
	CAipi_RETE_BME bmeo;
	
	int tempBM = 0;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	for( CMainFrame::g_mmBM::const_iterator iter = pMainFrame->gmmBM.begin(); iter!= pMainFrame->gmmBM.end(); ++iter)
	{
		CAipi_RETE_BM bmo = (CAipi_RETE_BM) iter->second;
		int tk = bmo.getChildTK();
		int bm = iter->first;
		
		
		int sizeTk = bmeo.linkWMEs(bm, tk);
		
		if( bm > tempBM )
		{
			int nTk = bmo.countBM(bm);
			bmeo.addBME(bm, nTk, sizeTk);
			tempBM = bm;
			/*
			CString str;
			str.Format(_T("bm...%d  " ), bm);
			AfxMessageBox(str);
			str.Format(_T("tk...%d  " ), tk);
			AfxMessageBox(str);
			str.Format(_T("size tk...%d  " ), sizeTk);
			AfxMessageBox(str);	
			str.Format(_T("n tk...%d  " ), nTk);
			AfxMessageBox(str);	
			*/
		}	
		
		
		
		
	}

}




int CAipi_RETE_Net::saveVarNum(tstring id_var, tstring var, int wm, int i_bm, int side)
{
	int match =NEGATIVE;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	/*
	AfxMessageBox(_T("IDVAR : "));
	AfxMessageBox(id_var.data());
	AfxMessageBox(_T("VAR : "));
	AfxMessageBox(var.data());
	*/
	


				
		pBM = pMainFrame->gmmBM.equal_range(i_bm);
		for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
		{	
			CAipi_RETE_BM bmo = (CAipi_RETE_BM)iterBM->second;
			int parent_tk  = bmo.getParentTK();
			int child_tk = bmo.getChildTK();
			tstring prevData1 = bmo.getData1();
			tstring prevData2 = bmo.getData2();
					
			/*	
			AfxMessageBox(_T("PrevDATA1 : "));
			AfxMessageBox(prevData1.data());
			
			
			AfxMessageBox(_T("PrevDATA2 : "));
			AfxMessageBox(prevData2.data());
			*/		
														
			if( prevData2 != _T("Undef") )
			{
				CAipi_RETE_TK tko;
				int parent_wm = tko.findWM(parent_tk);		
				//int gchild_tk = tko.searchTKChildTK(child_tk);
				//NOTE se supone que está funcion hace lo mismo que la de arriba, probar...
				int  gchild_tk = tko.findChild_TKParent_TKChild(child_tk);
				
				int child_wm = tko.findWM(gchild_tk);
				int bm_wm = bmo.getWM();
				
				
				/*
				CString str;
				str.Format(_T("Parent WM...%d  " ), parent_wm);
				AfxMessageBox(str);
				//str.Format(_T("Repeated Parent WM...%d  " ), rparent_wm);
				//AfxMessageBox(str);
				str.Format(_T("Child WM...%d  " ), child_wm);
				AfxMessageBox(str);
				str.Format(_T("Current Beta Memory WM...%d  " ), bm_wm);
				AfxMessageBox(str);
								
				
				str.Format(_T("WM...%d  " ), wm);		
				AfxMessageBox(str);
				*/		
				
				//if( bm_wm == wm || ( parent_wm == wm && rparent_wm != NOT_FOUND ))
				if( bm_wm == wm || parent_wm == wm )
				{
					
					//AfxMessageBox(_T("MATCH"));
					
					
					match = POSITIVE;
					int tk = tko.findWM_ChildTK(wm);
					CAipi_RETE_NumVars nuo;
					
					if( side == 1 )
					{
						nuo.addTK_LeftV(tk, var, id_var, prevData1, prevData2, wm, i_bm);
					}
					else
					{
						nuo.addTK_RightV(tk, var, id_var, prevData1, prevData2, wm, i_bm);
					}
							
				}
				
				else if( child_wm == wm )
				{
					
					/*
					AfxMessageBox(_T("MATCH CHILD_WM"));
					CString str;
					str.Format(_T("Child WM...%d  " ), child_wm);
					AfxMessageBox(str);
					*/
					
					int child_bm = tko.findBM(gchild_tk);				
					bmo.findBMMembers(child_bm);
					int bm_ptk = bmo.m_ParentTK;
					int bm_ctk = bmo.m_ChildTK;

					if( bmo.m_ParentTK == gchild_tk || bmo.m_ChildTK == gchild_tk)
					{
						prevData2 = bmo.m_Data2;
					}

								
					match = POSITIVE;
					int tk = tko.findWM_ChildTK(wm);
					CAipi_RETE_NumVars nuo;
					if( side == 1 )
					{
						nuo.addTK_LeftV(tk, var, id_var, prevData1, prevData2, wm, i_bm);
					}
					else
					{
						nuo.addTK_RightV(tk, var, id_var, prevData1, prevData2, wm, i_bm);
					}


				}
				



			}
		}
		if(  match == POSITIVE )
		{
			//AfxMessageBox(_T("Sale LEFT MATCH 1"));
			return match;
		}


		
	
return match;
}






int CAipi_RETE_Net::checkingNumVar(int ini_bm, int end_bm, int bm, int pm, int wm, int old_tk, tstring var, int side)
{
	
	CAipi_RETE_BM bmo;
	CAipi_RETE_AM amo; 
	int match = NEGATIVE;
	static int st_bm = UNDEFINE;
	static int st_matchBM = ini_bm;


	
	/*
	CString str;
	str.Format(_T("WM...%d  " ), wm);
	AfxMessageBox(str);
	str.Format(_T("STATIC BM...%d  " ), st_matchBM);
	AfxMessageBox(str);
	*/

	tstring id_var = searchPMVarAssig(pm, var);
	
	/*
	AfxMessageBox(_T("Var:" ));
	AfxMessageBox(var.data());
	AfxMessageBox(_T("IdVar:" ));
	AfxMessageBox(id_var.data());
  	
	*/ 


	for(int i= end_bm; i > ini_bm; --i)
	{
		
		if( i == bm )
		{
			continue;
		}
	
		/*
		CString st;
		st.Format(_T("i Beta Memory...%d  " ), i);
		AfxMessageBox(st);
		*/

		bmo.findBMMembers(i);
		
		tstring prevVar1 = bmo.m_Var1;
		tstring prevVar2 = bmo.m_Var2;
		
		/*
		AfxMessageBox(_T(" PrevVar1 : "));
		AfxMessageBox(prevVar1.data());
		
		AfxMessageBox(_T(" PrevVar2 : "));
		AfxMessageBox(prevVar2.data());
		*/
		
		if( id_var == prevVar1 || id_var == prevVar2 )
		{
			match =  saveVarNum(id_var, var, wm, i, side); 
			
			if( match == POSITIVE )
			{
				return match;
			}
			
			
		}

		
	}
	

return match;

}


//This function checks for more conditions bindings beside the ones of the parameter conditions (c1, c2)
//If the Alpha Memory finds others links then add it to the CAipi_RETE_Cond class
//So it can find a join node for the function checkingRepeatedCond()
void CAipi_RETE_Net::checkPreBMCondBinding(int c1, int c2, int am1, int am2, long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_Cond::iterator iterAM1;
	CMainFrame::g_mmAM_Cond::iterator iterAM2;

	pair <CMainFrame::g_mmAM_Cond::iterator, CMainFrame::g_mmAM_Cond::iterator>  pAM1;
	pair <CMainFrame::g_mmAM_Cond::iterator, CMainFrame::g_mmAM_Cond::iterator>  pAM2;

	pAM1 = pMainFrame->gmmAM_Cond.equal_range(am1);
	pAM2 = pMainFrame->gmmAM_Cond.equal_range(am2);

	CAipi_RETE_Links lnk;
	CAipi_LHS lhs;
	CAipi_RETE_Cond co;

		
	for(iterAM1 = pAM1.first; iterAM1 != pAM1.second; ++iterAM1)
	{	
		int condAM1 = iterAM1->second;
		
		if( condAM1 != c1 )
		{
			int cpm = lhs.findLHSPM(condAM1);
			if( cpm != pm )
			{
				return;
			}
			
			/*
			CString str;
			str.Format(_T("AM1 Cond...%d  " ), condAM1);
			AfxMessageBox(str);
			*/
			for(iterAM2 = pAM2.first; iterAM2 != pAM2.second; ++iterAM2)
			{	
				int condAM2 = iterAM2->second;
			
				if( condAM2 != c2 )
				{
					int cond2LNK = lnk.findCond1_Cond2(condAM1, condAM2);
					
					if( cond2LNK != NOT_FOUND )
					{
						/*
						CString str;
						str.Format(_T("AM1 Cond...%d  " ), condAM1);
						AfxMessageBox(str);
						str.Format(_T("AM2 Cond...%d  " ), condAM2);
						AfxMessageBox(str);
						*/

						lnk.findLinksMembers(c1);
						long pm = lnk.m_PM; 
						tstring var = lnk.m_Var;
						int jn = co.findCond2JN(c2); 
						/*
						str.Format(_T("JN...%d  " ), jn);
						AfxMessageBox(str);
						*/
						
						CAipi_RETE_Cond co;
						int fd1 = co.findCond1JN(condAM1);
						int fd2 = co.findCond2JN(condAM2);
						if( fd1 == NOT_FOUND && fd2 == NOT_FOUND )
						{
							co.addCond1(condAM1, jn, pm, var);
							co.addCond2(condAM2, jn, pm, var);
							co.addPreCondBind(condAM1, condAM2);

							//fxMessageBox(_T("Added PreCondBind Structure C1 y C2"));
						}

					}

				}
		
				
			}

		}
	
	}
}




bool CAipi_RETE_Net::checkEqualRelAtt(int c1, int c2, int wm, tstring var1, tstring var2)
{
	CAipi_LHS lhso;
	tstring att1 = lhso.findLHSAttr(c1);
	tstring att2 = lhso.findLHSAttr(c2);

	/*
	if( att1 == att2)
	{
		CAipi_RETE_Cond co;
		int jn1 = co.findCond2JN(c1);
		int jn2 = co.findCond2JN(c2);

		CAipi_RETE_Node no;
		int bm1 = no.getChild();
		int bm2 = no.getChild();
		

		CAipi_RETE_BM bmo;
		int id_var1 = bmo.findBMVar1(bm1);
		int id_var2 = bmo.findBMVar1(bm2);
		int data1 = bmo.findBMData1(bm1);
		int data2 = bmo.findBMData1(bm2);
		int wm1 = bmo.findBMWM(bm1);
		int wm2 = bmo.findBMWM(bm2);
		
		Caipi_RETE_TK tko;
		int tk1 = tko.findWM_TK(wm1);
		int tk2 = tko.findWM_TK(wm2);

		CAipi_RETE_NumVars nuo;
		nuo.addTK_LeftV(tk1, var1, id_var1, data1, wm1, bm1);
		nuo.addTK_RightV(tk2, var2, id_var2, data2, wm2, bm2);
		
	}
	*/
return false;
}









int CAipi_RETE_Net::createNumBM(int bm, tstring var1, tstring var2, tstring data1, tstring data2, int wm, int old_tk, int pm, int c1, int c2)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mTK_LeftV::iterator iterL;
	CMainFrame::g_mTK_RightV::iterator iterR;
	
	CAipi_PM pmo;
	CAipi_RETE_AM  amo;
	CAipi_RETE_BM bmo;
	CAipi_RETE_TK tko;

	int match = NEGATIVE;
	int newBM = UNDEFINE;
	int iniBM = pmo.PM_BMLowerBound(pm);
	int endBM = pmo.PM_BMUpperBound(pm);
	
	const int l = 1;
	const int r = 0;
	

/*	
	CString st;
	st.Format(_T("Ini Beta Memory...%d  " ), iniBM);
	AfxMessageBox(st);
	st.Format(_T("End Beta Memory...%d  " ), endBM);
	AfxMessageBox(st);
*/	
	
	/*
	CString str;				
	str.Format(_T("WM...%d  " ), wm);
	AfxMessageBox(str);
  	str.Format(_T("Parameter BM...%d  " ), bm);
	AfxMessageBox(str);
	*/	

		/*
	
		CString str;
		AfxMessageBox(_T("Var1:"));
		AfxMessageBox(var1.data());
		AfxMessageBox(_T("Data1:"));
		AfxMessageBox(data1.data());
		AfxMessageBox(_T("Var2:"));
		AfxMessageBox(var2.data());
		AfxMessageBox(_T("Data2:"));
		AfxMessageBox(data2.data());
*/
	

	

	if( amo.isVariable(var1) == false )
	{
		var1 = var2;
	}
	if (amo.isVariable(var2) == false)
	{
		var2 = var1;
	}


	int lr = checkingNumVar(iniBM, endBM, bm, pm, wm, old_tk, var1,  l);
	int rr = checkingNumVar(iniBM, endBM, bm, pm, wm, old_tk, var2,  r);
	
	

	/*
	//CString str;				
	str.Format(_T("LR...%d  " ), lr);
	AfxMessageBox(str);
	str.Format(_T("RR...%d  " ), rr);
	AfxMessageBox(str);
	*/

	
	for( iterL = pMainFrame->gmTK_LeftV.begin(); iterL!= pMainFrame->gmTK_LeftV.end(); ++iterL)
	{
		CAipi_RETE_NumVars num = (CAipi_RETE_NumVars)iterL->second;
		
			tstring l_data1 = num.getData1();
			tstring l_data2 = num.getData2();
			tstring lid_var = num.getVar(); 
			int		lbm		= num.getBM();
			//int		lnumBM		= num.findNumVar_BM(lid_var);
		
			//if( lnumBM > lbm )
			//{
				//return match;
			//}
		
			for( iterR = pMainFrame->gmTK_RightV.begin(); iterR!= pMainFrame->gmTK_RightV.end(); ++iterR)
			{
				CAipi_RETE_NumVars num = (CAipi_RETE_NumVars)iterR->second;
				
				
					tstring r_data1	= num.getData1();
					tstring r_data2  = num.getData2();
					tstring rid_var = num.getVar();
					int		rbm		= num.getBM();
					//int		rnumBM  = num.findNumVar_BM(rid_var);

					//if( rnumBM > rbm )
					//{
						//return match;
					//}
					
					/*
					CString str;
					AfxMessageBox(_T("Left Id_Var : "));
					AfxMessageBox(lid_var.data());
					AfxMessageBox(_T("Left Data1: "));
					AfxMessageBox(l_data1.data());
					AfxMessageBox(_T("Left Data2: "));
					AfxMessageBox(l_data2.data());
					
					str.Format(_T("Left BM...%d  " ), lbm);
					AfxMessageBox(str);
	
					AfxMessageBox(_T("Right Id_Var : "));
					AfxMessageBox(rid_var.data());
					AfxMessageBox(_T("Right Data1 : "));
					AfxMessageBox(r_data1.data());
					AfxMessageBox(_T("Right Data2 : "));
					AfxMessageBox(r_data2.data());
					str.Format(_T("Right BM...%d  " ), rbm);
					AfxMessageBox(str);
					*/
				
		
					if( l_data2 == r_data2 && l_data1 == r_data1 )
					{
						
						num.addNumVar_BM(lid_var, lbm);
						num.addNumVar_BM(rid_var, rbm);

						int new_tk = tko.generateTKKey();
						tko.createTK(new_tk, old_tk, wm, bm, NumNode);
						bmo.addBM(bm, var1, data1, var2, data2, old_tk, new_tk, wm);
						tko.addWM_ParentTK(wm, old_tk);
						tko.addWM_ChildTK(wm, new_tk);
						tko.addTKParent_TKChild(old_tk, new_tk);
						match = POSITIVE;
						
						int tk_emptyBM = bmo.findBMParentTK(bm, UNDEFINE);
						if( tk_emptyBM != NOT_FOUND )
						{
							bmo.eraseItemBM_ParentTK(bm, tk_emptyBM);
						}
						
						/*
						AfxMessageBox(_T("Crea Num Beta Memory"));
						CString str;				
						str.Format(_T("BM...%d  " ), bm);
						AfxMessageBox(str);
						*/						
  	
					}
				
			}

		
	}

	
	if( match == NEGATIVE )
	{
		
		int lastBM = bmo.lastBM();
		
		if( bmo.findBMMembers(bm) )
		{
			return match;
		}
		/*
		CString str;
		str.Format(_T("lastBM...%d  " ), lastBM);
		AfxMessageBox(str);
		str.Format(_T("Actual BM...%d  " ), bm);
		AfxMessageBox(str);
		*/
		
		if( bm != lastBM )
		{
			//AfxMessageBox(_T("No-Match"));
			bmo.addBM(bm, var1, data1, var2, data2, UNDEFINE, UNDEFINE, wm);
			//pmo.addPM_BM(pm, bm);	
		}
		
	}
	
	
	CAipi_RETE_NumVars num;
	num.clearTK_LeftV();
	num.clearTK_RightV();
	
	

return match;
}




void CAipi_RETE_Net::selectRelOperator(int rel, int bm, tstring var1, tstring var2, tstring data1, tstring data2, int type1, int type2, int wm, int old_tk, int pm, int c1, int c2 )
{
	
		/*	
		CString str;
		AfxMessageBox(_T("Data1:"));
		AfxMessageBox(data1.data());
		AfxMessageBox(_T("Data2:"));
		AfxMessageBox(data2.data());
		*/

	/*
	CString str;
	str.Format(_T("REL...%d  " ), rel);
	AfxMessageBox(str);
	*/

	if( type1 == AIPI_INT && type2 == AIPI_INT )
	{
		switch( rel )
		{
			case ET:
				if( m_iData1 == m_iData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
			case NE:
				if( m_iData1 != m_iData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
				case LT:
				if( m_iData1 < m_iData2 )
				{
					//CString str;
					//str.Format(_T("select REL WM...%d  " ), wm);
					//AfxMessageBox(str);
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);							
				}
				break;
			case LE:
				if( m_iData1 <= m_iData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
			case GT:
				if( m_iData1 > m_iData2 )
				{
					/*
					CString str;
					str.Format(_T("select REL WM...%d  " ), wm);
					AfxMessageBox(str);
					*/
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
			case GE:
				if( m_iData1 >= m_iData2 )
				{
					/*
					CString str;
					str.Format(_T("select REL WM...%d  " ), wm);
					AfxMessageBox(str);
					*/
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;

		}
	}
	else if( type1 == AIPI_LONG && type2 == AIPI_LONG )
	{
			switch( rel )
			{
			case ET:
				if( m_lData1 == m_lData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
			case NE:
				if( m_lData1 != m_lData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
				case LT:
				if( m_lData1 < m_lData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);							
				}
				break;
			case LE:
				if( m_lData1 <= m_lData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
			case GT:
				if( m_lData1 > m_lData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
			case GE:
				if( m_lData1 >= m_lData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;

		}
	}
	else if( type1 == AIPI_FLOAT && type2 == AIPI_FLOAT )
	{
			switch( rel )
			{
			case ET:
				if( m_fData1 == m_fData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
			case NE:
				if( m_fData1 != m_fData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
				case LT:
				if( m_fData1 < m_fData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);							
				}
				break;
			case LE:
				if( m_fData1 <= m_fData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
			case GT:
				if( m_fData1 > m_fData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
			case GE:
				if( m_fData1 >= m_fData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;

		}
	}
	else if( type1 == AIPI_DOUBLE && type2 == AIPI_DOUBLE )
	{
			switch( rel )
			{
			case ET:
				if( m_dData1 == m_dData2 )
				{
					/*
					CString str;
					str.Format(_T("select REL WM...%d  " ), wm);
					AfxMessageBox(str);
					*/
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
			case NE:
				if( m_dData1 != m_dData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
				case LT:
				if( m_dData1 < m_dData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);							
				}
				break;
			case LE:
				if( m_dData1 <= m_dData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
			case GT:
				if( m_dData1 > m_dData2 )
				{
					//CString str;
					//str.Format(_T("select REL WM...%d  " ), wm);
					//AfxMessageBox(str);
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
					
					
				}
				break;
			case GE:
				if( m_dData1 >= m_dData2 )
				{
					//CString str;
					//str.Format(_T("select REL WM...%d  " ), wm);
					//AfxMessageBox(str);
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
					
				}
				break;
			}

		}
		else if( type1 == AIPI_STRING && type2 == AIPI_STRING )
		{
			/*
			AfxMessageBox(_T("Checking String ET"));
			AfxMessageBox(m_sData1.data());
			AfxMessageBox(m_sData2.data());
			*/

			switch( rel )
			{
			case ET:
				if( m_sData1 == m_sData2 )
				{
					createNumBM(bm, var1, var2, data1, data2, wm, old_tk, pm, c1, c2);
				}
				break;
			case NE:
				AfxMessageBox(_T("AIPI ERROR: Can not be applied relational operator (NE)" ));
				break;
				case LT:
				AfxMessageBox(_T("AIPI ERROR: Can not be applied relational operator (LT)" ));
				break;
			case LE:
				AfxMessageBox(_T("AIPI ERROR: Can not be applied relational operator (LE)" ));
				break;
			case GT:
				AfxMessageBox(_T("AIPI ERROR: Can not be applied relational operator (GT)" ));
				break;
			case GE:
				AfxMessageBox(_T("AIPI ERROR: Can not be applied relational operator (GE)" ));
				break;

			}
		
	}
	else
	{
		AfxMessageBox(_T("AIPI ERROR: Variable type is not identifed" ));
	}




}



void CAipi_RETE_Net::compareNumVars(int pm)
{
	/*
	CString str;
	str.Format(_T("PM...%d  " ), pm);
	AfxMessageBox(str);
	*/
	
	CAipi_RETE_Cond co;
	CAipi_RETE_Node no;
	CAipi_RETE_NumVars numo;

	int type1 = UNDEFINE;
	int type2 = UNDEFINE;
	tstring var1,var2 = _T("");
	tstring strData1, strData2 = _T("");	
	TCHAR buff[4];

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mmPM_Operation::iterator iterOpe;
	pair <CMainFrame::g_mmPM_Operation::iterator, CMainFrame::g_mmPM_Operation::iterator>  pOpe;
	pOpe = pMainFrame->gmmPM_Operation.equal_range(pm);
	
	for(iterOpe = pOpe.first; iterOpe != pOpe.second; ++iterOpe)
	{	
		CAipi_RETE_Operations ope = (CAipi_RETE_Operations)iterOpe->second;
 		
		int rel = ope.getRel();
		int c = ope.getCond();

		int jn =  co.findCond2JN(c);
		int bm =  no.findNodeBM2(jn);
		
		if( bm == NOT_FOUND )
		{
			CAipi_RETE_BM bmo;
			CAipi_PM  pmo;

			bm = bmo.generateBMKey();
			pmo.addPM_BM(pm, bm);
			
			/*
			CString str;
			str.Format(_T("newBM...%d  " ), bm);
			AfxMessageBox(str);
			*/	
		}
												
							
				/*
				
				CString str;		
				str.Format(_T("Condition...%d  " ), c);
				AfxMessageBox(str);
				str.Format(_T("JN...%d  " ), jn);
				AfxMessageBox(str);
				str.Format(_T("BM...%d  " ), bm);
				AfxMessageBox(str);
				*/
						
		
		var1	= ope.getLeftVar();
		type1	= ope.getLeftType();
				
		var2	= ope.getRightVar();
		type2	= ope.getRightType();
	
		
	
			
/*Int*/ 
		if( type1 == AIPI_INT )
		{
		
			CMainFrame::g_mmVar_Int::iterator iterInt;
			pair <CMainFrame::g_mmVar_Int::iterator, CMainFrame::g_mmVar_Int::iterator>  pInt;
			pInt = pMainFrame->gmmVar_Int.equal_range(var1);
			
			for(iterInt = pInt.first; iterInt != pInt.second; ++iterInt)
			{	
				CAipi_RETE_TypeInt typeI = (CAipi_RETE_TypeInt)iterInt->second;
				
				m_iData1 = typeI.getData();
				strData1 = _itot(m_iData1, buff, 10);
				int wm = typeI.getWM();
				int oldTK = typeI.getTK();
				int c1 = typeI.getCond();
				
				
				
				/*
				CString str;			
				AfxMessageBox(_T("Var1:"));
				AfxMessageBox(var1.data());
				str.Format(_T("m_iData1...%d  " ), m_iData1);
				AfxMessageBox(str);
				str.Format(_T("WM...%d  " ), wm);
				AfxMessageBox(str);
				*/		
				
			

				if( type2 == AIPI_INT )
				{
				
					CMainFrame::g_mmVar_Int::iterator iterInt;
					pair <CMainFrame::g_mmVar_Int::iterator, CMainFrame::g_mmVar_Int::iterator>  pInt;
					pInt = pMainFrame->gmmVar_Int.equal_range(var2);

						/*
						CString str;
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						str.Format(_T("m_iData2...%d  " ), m_iData2);
						AfxMessageBox(str);
						*/
				
					for(iterInt = pInt.first; iterInt != pInt.second; ++iterInt)
					{	
						CAipi_RETE_TypeInt typeI = (CAipi_RETE_TypeInt)iterInt->second;
						m_iData2 = typeI.getData();
						strData2 = _itot(m_iData2, buff, 10);
						int c2 = typeI.getCond();
						
						
						/*
						CString str;
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						str.Format(_T("m_iData2...%d  " ), m_iData2);
						AfxMessageBox(str);
						str.Format(_T("WM...%d  " ), wm);
						AfxMessageBox(str);
						*/
						
						
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_INT, AIPI_INT, wm, oldTK, pm, c1, c2);
						
					}//end for

				}//end if
				else if( type2 == AIPI_LONG )
				{
				
					CMainFrame::g_mmVar_Long::iterator iterLong;
					pair <CMainFrame::g_mmVar_Long::iterator, CMainFrame::g_mmVar_Long::iterator>  pLong;
					pLong = pMainFrame->gmmVar_Long.equal_range(var2);
				
					for(iterLong = pLong.first; iterLong != pLong.second; ++iterLong)
					{	
						CAipi_RETE_TypeLong typeL = (CAipi_RETE_TypeLong)iterLong->second;
						m_lData2 = typeL.getData();
						strData2 = _ltot(m_lData2, buff, 10);
						m_lData1 = (long)m_iData1;
						int c2 = typeL.getCond();

						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						str.Format(_T("m_lData2...%l  " ), m_lData2);
						AfxMessageBox(str);
						*/
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_LONG, AIPI_LONG, wm, oldTK, pm, c1, c2);
						
					}

				}
				else if( type2 == AIPI_FLOAT )
				{
				
					CMainFrame::g_mmVar_Float::iterator iterFloat;
					pair <CMainFrame::g_mmVar_Float::iterator, CMainFrame::g_mmVar_Float::iterator>  pFloat;
					pFloat = pMainFrame->gmmVar_Float.equal_range(var2);
				
					for(iterFloat = pFloat.first; iterFloat != pFloat.second; ++iterFloat)
					{	
						CAipi_RETE_TypeFloat typeF = (CAipi_RETE_TypeFloat)iterFloat->second;
						m_fData2 = typeF.getData();
						m_fData1 = (float)m_iData1;
						int c2 = typeF.getCond();
						
						CString sData2;
						sData2.Format(_T("%f"), m_fData2);
						strData2 = (tstring)sData2;
						
						
						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						sData2.Format(_T("m_fData2...%f  " ), m_fData2);
						AfxMessageBox(sData2);
						*/
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_FLOAT, AIPI_FLOAT, wm, oldTK, pm, c1, c2);
						
						
					}

				}
				else if( type2 == AIPI_DOUBLE )
				{
				
					CMainFrame::g_mmVar_Double::iterator iterDouble;
					pair <CMainFrame::g_mmVar_Double::iterator, CMainFrame::g_mmVar_Double::iterator>  pDouble;
					pDouble = pMainFrame->gmmVar_Double.equal_range(var2);
				
					for(iterDouble = pDouble.first; iterDouble != pDouble.second; ++iterDouble)
					{	
						CAipi_RETE_TypeDouble typeD = (CAipi_RETE_TypeDouble)iterDouble->second;
						m_dData2 = typeD.getData();
						m_dData1 = (double)m_iData1;
						int c2 = typeD.getCond();

						CString sData2;
						sData2.Format(_T("%f"), m_dData2);
						strData2 = (tstring)sData2;


						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						sData2.Format(_T("m_dData2...%f  " ), m_dData2);
						AfxMessageBox(sData2);
						*/
						
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_DOUBLE, AIPI_DOUBLE, wm, oldTK, pm, c1, c2);
					}

				}
				else if( type2 == AIPI_STRING )
				{
					AfxMessageBox(_T("ERROR: Can not convert types from Int to String"));
				
				}

			}//end for
				
		}//end if

/*Long*/
		else if( type1 == AIPI_LONG )
		{
		
			CMainFrame::g_mmVar_Long::iterator iterLong;
			pair <CMainFrame::g_mmVar_Long::iterator, CMainFrame::g_mmVar_Long::iterator>  pLong;
			pLong = pMainFrame->gmmVar_Long.equal_range(var1);
			
			for(iterLong = pLong.first; iterLong != pLong.second; ++iterLong)
			{	
				CAipi_RETE_TypeLong typeL = (CAipi_RETE_TypeLong)iterLong->second;
				m_lData1 = typeL.getData();
				strData1 = _ltot(m_lData1, buff, 10);

				int wm = typeL.getWM();
				int oldTK = typeL.getTK();
				int c1 = typeL.getCond();
				
				/*			
				AfxMessageBox(_T("Var1:"));
				AfxMessageBox(var1.data());
				str.Format(_T("m_lData1...%l  " ), m_lData1);
				AfxMessageBox(str);
				*/		

			
				if( type2 == AIPI_LONG )
				{
				
					CMainFrame::g_mmVar_Long::iterator iterLong;
					pair <CMainFrame::g_mmVar_Long::iterator, CMainFrame::g_mmVar_Long::iterator>  pLong;
					pLong = pMainFrame->gmmVar_Long.equal_range(var2);
				
					for(iterLong = pLong.first; iterLong != pLong.second; ++iterLong)
					{	
						CAipi_RETE_TypeLong typeL = (CAipi_RETE_TypeLong)iterLong->second;
						m_lData2 = typeL.getData();
						strData2 = _ltot(m_lData2, buff, 10);
						int c2 = typeL.getCond();
						
						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						str.Format(_T("m_lData2...%l  " ), m_lData2);
						AfxMessageBox(str);
						*/
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_LONG, AIPI_LONG, wm, oldTK, pm, c1, c2);
						
					}

				}
				else if( type2 == AIPI_INT )
				{
				
					CMainFrame::g_mmVar_Int::iterator iterInt;
					pair <CMainFrame::g_mmVar_Int::iterator, CMainFrame::g_mmVar_Int::iterator>  pInt;
					pInt = pMainFrame->gmmVar_Int.equal_range(var2);
				
					for(iterInt = pInt.first; iterInt != pInt.second; ++iterInt)
					{	
						CAipi_RETE_TypeInt typeI = (CAipi_RETE_TypeInt)iterInt->second;
						m_lData2 = (long)typeI.getData();
						strData2 = _ltot(m_lData2, buff, 10);
						int c2 = typeL.getCond();

						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						str.Format(_T("m_lData2...%l  " ), m_lData2);
						AfxMessageBox(str);
						*/
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_LONG, AIPI_LONG, wm, oldTK, pm, c1, c2);
								
					}

				}
				else if( type2 == AIPI_FLOAT )
				{
				
					CMainFrame::g_mmVar_Float::iterator iterFloat;
					pair <CMainFrame::g_mmVar_Float::iterator, CMainFrame::g_mmVar_Float::iterator>  pFloat;
					pFloat = pMainFrame->gmmVar_Float.equal_range(var2);
				
					for(iterFloat = pFloat.first; iterFloat != pFloat.second; ++iterFloat)
					{	
						CAipi_RETE_TypeFloat typeF = (CAipi_RETE_TypeFloat)iterFloat->second;
						m_fData2 = typeF.getData();
						m_fData1 = (float)m_lData1;
						int c2 = typeF.getCond();

						CString sData2;
						sData2.Format(_T("%f"), m_fData2);
						strData2 = (tstring)sData2;


						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						sData2.Format(_T("m_fData2...%f  " ), m_fData2);
						AfxMessageBox(sData2);
						*/
						
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_FLOAT, AIPI_FLOAT, wm, oldTK, pm, c1, c2);
						
					}

				}
				else if( type2 == AIPI_DOUBLE )
				{
				
					CMainFrame::g_mmVar_Double::iterator iterDouble;
					pair <CMainFrame::g_mmVar_Double::iterator, CMainFrame::g_mmVar_Double::iterator>  pDouble;
					pDouble = pMainFrame->gmmVar_Double.equal_range(var2);
				
					for(iterDouble = pDouble.first; iterDouble != pDouble.second; ++iterDouble)
					{	
						CAipi_RETE_TypeDouble typeD = (CAipi_RETE_TypeDouble)iterDouble->second;
						m_dData2 = typeD.getData();
						m_dData1 = (double)m_lData1;
						int c2 = typeD.getCond();

						CString sData2;
						sData2.Format(_T("%f"), m_dData2);
						strData2 = (tstring)sData2;

						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						sData2.Format(_T("m_dData2...%d  " ), m_dData2);
						AfxMessageBox(sData2);
						*/
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_DOUBLE, AIPI_DOUBLE, wm, oldTK, pm, c1, c2);
												
					}

				}
				else if( type2 == AIPI_STRING )
				{
					AfxMessageBox(_T("ERROR: Can not convert types from Long to String"));
				
				}
			
			}//end for	

		}//end if

/*Float*/
		else if( type1 == AIPI_FLOAT )
		{
		
			CMainFrame::g_mmVar_Float::iterator iterFloat;
			pair <CMainFrame::g_mmVar_Float::iterator, CMainFrame::g_mmVar_Float::iterator>  pFloat;
			pFloat = pMainFrame->gmmVar_Float.equal_range(var1);
			
			for(iterFloat = pFloat.first; iterFloat != pFloat.second; ++iterFloat)
			{	
				CAipi_RETE_TypeFloat typeF = (CAipi_RETE_TypeFloat)iterFloat->second;
				m_fData1 = typeF.getData();

				int wm = typeF.getWM();
				int oldTK = typeF.getTK();
				int c1 = typeF.getCond();
				
				CString sData1;
				sData1.Format(_T("%f"), m_fData1);
				strData1 = (tstring)sData1;
				/*
				CString str;			
				AfxMessageBox(_T("Var1:"));
				AfxMessageBox(var1.data());
				sData1.Format(_T("m_fData1...%f  " ), m_fData1);
				AfxMessageBox(sData1);
				*/		

			
				if( type2 == AIPI_FLOAT )
				{
				
					CMainFrame::g_mmVar_Float::iterator iterFloat;
					pair <CMainFrame::g_mmVar_Float::iterator, CMainFrame::g_mmVar_Float::iterator>  pFloat;
					pFloat = pMainFrame->gmmVar_Float.equal_range(var2);
				
					for(iterFloat = pFloat.first; iterFloat != pFloat.second; ++iterFloat)
					{	
						CAipi_RETE_TypeFloat typeF = (CAipi_RETE_TypeFloat)iterFloat->second;
						m_fData2 = typeF.getData();
						int c2 = typeF.getCond();

						CString sData2;
						sData2.Format(_T("%f"), m_fData2);
						strData2 = (tstring)sData2;
						
						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						sData2.Format(_T("m_fData2...%f  " ), m_fData2);
						AfxMessageBox(sData2);
						*/
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_FLOAT, AIPI_FLOAT, wm, oldTK, pm, c1, c2);
						
					}

				}
				else if( type2 == AIPI_INT )
				{
				
					CMainFrame::g_mmVar_Int::iterator iterInt;
					pair <CMainFrame::g_mmVar_Int::iterator, CMainFrame::g_mmVar_Int::iterator>  pInt;
					pInt = pMainFrame->gmmVar_Int.equal_range(var2);
				
					for(iterInt = pInt.first; iterInt != pInt.second; ++iterInt)
					{	
						CAipi_RETE_TypeInt typeI = (CAipi_RETE_TypeInt)iterInt->second;
						m_fData2 = (float)typeI.getData();
						int c2 = typeI.getCond();

						CString sData2;
						sData2.Format(_T("%f"), m_fData2);
						strData2 = (tstring)sData2;
						

						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						sData2.Format(_T("m_fData2...%f  " ), m_fData2);
						AfxMessageBox(sData2);
						*/
						
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_FLOAT, AIPI_FLOAT, wm, oldTK, pm, c1, c2);
					}

				}
				else if( type2 == AIPI_LONG )
				{
				
					CMainFrame::g_mmVar_Long::iterator iterLong;
					pair <CMainFrame::g_mmVar_Long::iterator, CMainFrame::g_mmVar_Long::iterator>  pLong;
					pLong = pMainFrame->gmmVar_Long.equal_range(var2);
				
					for(iterLong = pLong.first; iterLong != pLong.second; ++iterLong)
					{	
						CAipi_RETE_TypeLong typeL = (CAipi_RETE_TypeLong)iterLong->second;
						m_fData2 = (float)typeL.getData();
						int c2 = typeL.getCond();

						CString sData2;
						sData2.Format(_T("%f"), m_fData2);
						strData2 = (tstring)sData2;
						

						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						sData2.Format(_T("m_fData2...%f  " ), m_fData2);
						AfxMessageBox(sData2);
						*/
						
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_FLOAT, AIPI_FLOAT, wm, oldTK, pm, c1, c2);
					
					}

				}
				else if( type2 == AIPI_DOUBLE )
				{
				
					CMainFrame::g_mmVar_Double::iterator iterDouble;
					pair <CMainFrame::g_mmVar_Double::iterator, CMainFrame::g_mmVar_Double::iterator>  pDouble;
					pDouble = pMainFrame->gmmVar_Double.equal_range(var2);
				
					for(iterDouble = pDouble.first; iterDouble != pDouble.second; ++iterDouble)
					{	
						CAipi_RETE_TypeDouble typeD = (CAipi_RETE_TypeDouble)iterDouble->second;
						m_dData2 = typeD.getData();
						m_dData1 = (double)m_fData1;
						int c2 = typeD.getCond();

						CString sData2;
						sData2.Format(_T("%f"), m_dData2);
						strData2 = (tstring)sData2;

						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						sData2.Format(_T("m_dData2...%f  " ), m_dData2);
						AfxMessageBox(sData2);
						*/
						
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_DOUBLE, AIPI_DOUBLE, wm, oldTK, pm, c1, c2);
						
					}

				}
				else if( type2 == AIPI_STRING )
				{
					AfxMessageBox(_T("ERROR: Can not convert types from Float to String"));
				
				}
			
			}//end for	

		}//end if

/*Double*/
		else if( type1 == AIPI_DOUBLE )
		{
		
			CMainFrame::g_mmVar_Double::iterator iterDouble;
			pair <CMainFrame::g_mmVar_Double::iterator, CMainFrame::g_mmVar_Double::iterator>  pDouble;
			pDouble = pMainFrame->gmmVar_Double.equal_range(var1);
			
			for(iterDouble = pDouble.first; iterDouble != pDouble.second; ++iterDouble)
			{	
				CAipi_RETE_TypeDouble typeD = (CAipi_RETE_TypeDouble)iterDouble->second;
				m_dData1 = typeD.getData();

				int wm = typeD.getWM();
				int oldTK = typeD.getTK();
				int c1 = typeD.getCond();
				
				CString sData1;
				sData1.Format(_T("%f"), m_dData1);
				strData1 = (tstring)sData1;

					
				/*			
				AfxMessageBox(_T("Var1:"));
				AfxMessageBox(var1.data());
				sData1.Format(_T("m_dData1...%f  " ), m_dData1);
				AfxMessageBox(sData1);
				CString str;
				str.Format(_T("WM...%d  " ), wm);
				AfxMessageBox(str);
				*/	

			
				if( type2 == AIPI_DOUBLE )
				{
				
					CMainFrame::g_mmVar_Double::iterator iterDouble;
					pair <CMainFrame::g_mmVar_Double::iterator, CMainFrame::g_mmVar_Double::iterator>  pDouble;
					pDouble = pMainFrame->gmmVar_Double.equal_range(var2);
				
					for(iterDouble = pDouble.first; iterDouble != pDouble.second; ++iterDouble)
					{	
						CAipi_RETE_TypeDouble typeD = (CAipi_RETE_TypeDouble)iterDouble->second;
						m_dData2 = typeD.getData();
						int c2 = typeD.getCond();
						
						CString sData2;
						sData2.Format(_T("%f"), m_dData2);
						strData2 = (tstring)sData2;

						
						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						sData2.Format(_T("m_dData2...%f  " ), m_dData2);
						AfxMessageBox(sData2);
						*/
						
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_DOUBLE, AIPI_DOUBLE, wm, oldTK, pm, c1, c2);
						
					}

				}
				else if( type2 == AIPI_INT )
				{
				
					CMainFrame::g_mmVar_Int::iterator iterInt;
					pair <CMainFrame::g_mmVar_Int::iterator, CMainFrame::g_mmVar_Int::iterator>  pInt;
					pInt = pMainFrame->gmmVar_Int.equal_range(var2);
				
					for(iterInt = pInt.first; iterInt != pInt.second; ++iterInt)
					{	
						CAipi_RETE_TypeInt typeI = (CAipi_RETE_TypeInt)iterInt->second;
						m_dData2 = (double)typeI.getData();
						int c2 = typeI.getCond();
						
						CString sData2;
						sData2.Format(_T("%f"), m_dData2);
						strData2 = (tstring)sData2;


						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						sData2.Format(_T("m_dData2...%f  " ), m_dData2);
						AfxMessageBox(sData2);
						*/
						
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_DOUBLE, AIPI_DOUBLE, wm, oldTK, pm, c1, c2);
						
					}

				}
				else if( type2 == AIPI_LONG )
				{
				
					CMainFrame::g_mmVar_Long::iterator iterLong;
					pair <CMainFrame::g_mmVar_Long::iterator, CMainFrame::g_mmVar_Long::iterator>  pLong;
					pLong = pMainFrame->gmmVar_Long.equal_range(var2);
				
					for(iterLong = pLong.first; iterLong != pLong.second; ++iterLong)
					{	
						CAipi_RETE_TypeLong typeL = (CAipi_RETE_TypeLong)iterLong->second;
						m_dData2 = (double)typeL.getData();
						int c2 = typeL.getCond();
						
						CString sData2;
						sData2.Format(_T("%f"), m_dData2);
						strData2 = (tstring)sData2;

						
						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						sData2.Format(_T("m_dData2...%f  " ), m_dData2);
						AfxMessageBox(sData2);
						*/
						
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_DOUBLE, AIPI_DOUBLE, wm, oldTK, pm, c1, c2);
					}

				}
				else if( type2 == AIPI_FLOAT )
				{
				
					CMainFrame::g_mmVar_Float::iterator iterFloat;
					pair <CMainFrame::g_mmVar_Float::iterator, CMainFrame::g_mmVar_Float::iterator>  pFloat;
					pFloat = pMainFrame->gmmVar_Float.equal_range(var2);
				
					for(iterFloat = pFloat.first; iterFloat != pFloat.second; ++iterFloat)
					{	
						CAipi_RETE_TypeFloat typeF = (CAipi_RETE_TypeFloat)iterFloat->second;
						m_dData2 = (double)typeF.getData();
						int c2 = typeF.getCond();
						
						CString sData2;
						sData2.Format(_T("%f"), m_dData2);
						strData2 = (tstring)sData2;

						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						sData2.Format(_T("m_dData2...%f  " ), m_dData2);
						AfxMessageBox(sData2);
						*/
						
						selectRelOperator(rel, bm, var1, var2, strData1, strData2, AIPI_DOUBLE, AIPI_DOUBLE, wm, oldTK, pm, c1, c2);
						
					}

				}
				else if( type2 == AIPI_STRING )
				{
					AfxMessageBox(_T("ERROR: Can not convert types from Double to String"));
				
				}
			
			}//end for	

		}//end if
	
/*String*/
		else if( type1 == AIPI_STRING )
		{
		
			CMainFrame::g_mmVar_String::iterator iterString;
			pair <CMainFrame::g_mmVar_String::iterator, CMainFrame::g_mmVar_String::iterator>  pString;
			pString = pMainFrame->gmmVar_String.equal_range(var1);
			
			for(iterString = pString.first; iterString != pString.second; ++iterString)
			{	
				CAipi_RETE_TypeString typeS = (CAipi_RETE_TypeString)iterString->second;
				m_sData1 = typeS.getData();

				int wm = typeS.getWM();
				int oldTK = typeS.getTK();
				int c1 = typeS.getCond();
				
					
				/*			
				AfxMessageBox(_T("Var1:"));
				AfxMessageBox(var1.data());
				AfxMessageBox(_T("Data1:"));
				AfxMessageBox(m_sData1.data());
				CString str;
				str.Format(_T("WM...%d  " ), wm);
				AfxMessageBox(str);
				*/
					
				
				/*
				AfxMessageBox(_T("Var2:"));
				AfxMessageBox(var2.data());
				AfxMessageBox(_T("Data2:"));
				AfxMessageBox(m_sData2.data());
				*/

				if( type2 == AIPI_STRING )
				{
				
					CMainFrame::g_mmVar_String::iterator iterString;
					pair <CMainFrame::g_mmVar_String::iterator, CMainFrame::g_mmVar_String::iterator>  pString;
					pString = pMainFrame->gmmVar_String.equal_range(var2);
				
					for(iterString = pString.first; iterString != pString.second; ++iterString)
					{	
						CAipi_RETE_TypeString typeS = (CAipi_RETE_TypeString)iterString->second;
						m_sData2 = typeS.getData();
						int c2 = typeS.getCond();
											
						/*
						AfxMessageBox(_T("Var2:"));
						AfxMessageBox(var2.data());
						AfxMessageBox(_T("Data2:"));
						AfxMessageBox(m_sData2.data());
						*/
						
						
						selectRelOperator(rel, bm, var1, var2, m_sData1, m_sData2, AIPI_STRING, AIPI_STRING, wm, oldTK, pm, c1, c2);
						
					}

				}
			
				else if( type2 == AIPI_DOUBLE )
				{
					AfxMessageBox(_T("ERROR: Can not convert types from String to Double"));
					
				}
				else if( type2 == AIPI_INT )
				{
					AfxMessageBox(_T("ERROR: Can not convert types from String to Int"));
					
				}
				else if( type2 == AIPI_LONG )
				{
					AfxMessageBox(_T("ERROR: Can not convert types from String to Long"));
					
				}
				else if( type2 == AIPI_FLOAT )
				{
					AfxMessageBox(_T("ERROR: Can not convert types from String to Float"));				

				}
			
			}//end for	

		}//end if 


	




	}//end for operator



	//clear NumVars_BM structure
	numo.clearNumVar_BM();



}


tstring CAipi_RETE_Net::searchPMVarAssig( int pm, tstring val  )
{
	CAipi_LHS lhso;
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Cond.equal_range(pm);
	
	for(CMainFrame::g_mmPM_Cond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		int c = it_PM->second;
		lhso.findLHSMembers(c);	
		
		
		int lhsRel = lhso.m_Rel;
	
		if( lhsRel == AS )
		{
			
			tstring lhsVal = lhso.m_lhsVal;
			
			if(  lhsVal == val  )
			{
				return lhso.m_lhsId;
			
			}
		}
		
	}
	

return _T("NOT_FOUND");

}

int CAipi_RETE_Net::assertUpdateAM(int w)
{
		
		CAipi_WM wmo;
		int ame = UNDEFINE;

		int f = wmo.findWMMembersIForm(w);
		if( f != NOT_FOUND )
		{
			tstring id		= wmo.getId();
			tstring attr	= wmo.getAttr();
			tstring val		= wmo.getVal();
		
			CAipi_RETE_AM amo;
			ame = amo.insertEQ(w, id, attr, val );
			/*
			ame = insertET(w, id, attr, val );
			ame = insertNE(w, id, attr, val );
			ame = insertLT(w, id, attr, val );
			ame = insertLE(w, id, attr, val );
			ame = insertGT(w, id, attr, val );
			ame = insertGE(w, id, attr, val );
			ame = insertAS(w, id, attr, val );
			*/
		}

return ame;
}


int CAipi_RETE_Net::retractUpdateAM(int w)
{
	
	CAipi_RETE_AM amo;
	int ame = UNDEFINE;

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmWM_AM::iterator iterWM;
	pair <CMainFrame::g_mmWM_AM::iterator, CMainFrame::g_mmWM_AM::iterator>  pWM;
	pWM = pMainFrame->gmmWM_AM.equal_range(w);	
	
		
	for(iterWM = pWM.first; iterWM != pWM.second; ++iterWM)
	{	
		ame = iterWM->second;
		
		/*
		CString st;
		st.Format(_T("Alpha Memory Element...%d  " ), ame);
		AfxMessageBox(st);
		*/
		amo.eraseItemAM_WM(ame, w);
		

		
	}

	amo.eraseWM_AM(w);
	
		
return ame;
}

int CAipi_RETE_Net::assertUpdateBM(int am1, int wm, int pm)
{
	//AfxMessageBox(_T("ASSERT BM"));
	
	CAipi_RETE_AM amo;
	int c2 = amo.findAM_Cond(am1);
	if( c2 == NOT_FOUND )
	{
		return c2;
	}

	CAipi_LHS lhso;
	int categ = lhso.findLHSCategory(c2);
	if( categ == K_K_K )
	{
		return c2;		
	}
	else
	{
		CAipi_RETE_Cond co;
		int jn = co.findCond2JN(c2);
		CAipi_RETE_NodeCond ncond;
		int c1 = ncond.findNodeCond1_Cond2(jn, c2);
		
		if( c1 != UNDEFINE )
		{
			CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			int n = pMainFrame->gmmLink.count(c1);
			while ( n != 0 )
			{
				
				CMainFrame::g_mmLink::iterator iter;
				pair <CMainFrame::g_mmLink::iterator, CMainFrame::g_mmLink::iterator>  pIter;
				pIter = pMainFrame->gmmLink.equal_range(c1);
				
				for(iter = pIter.first; iter != pIter.second; ++iter)
				{	
					CAipi_RETE_Links lnk = (CAipi_RETE_Links)iter->second;
					int c2	= lnk.getCond2();
					int f1	= lnk.getField1();
					int f2	= lnk.getField2();
					tstring link_var = lnk.getVar();
					
					int am2 = amo.findCond_AM(c2);
					jn = co.findCond2JN(c2);
					
										
					CAipi_RETE_Node no;
					int bm1 = no.findNodeBM1(jn);
					int bm2 = no.findNodeBM2(jn);
					CAipi_RETE_BM bmo;
					bmo.findBMMembers(bm2);
					
					
					CAipi_RETE_BME bmeo;
					if( bmo.m_ParentTK == UNDEFINE && bmo.m_ChildTK == UNDEFINE )
					{
						bmo.eraseBM(bm2);
						bmeo.eraseBME(bm2);
					}
					
					/*
					CString st;
					st.Format(_T("AM1...%d  " ), am1);
					AfxMessageBox(st);
					st.Format(_T("AM2...%d  " ), am2);
					AfxMessageBox(st);
					st.Format(_T("Links C1...%d  " ), c1);
					AfxMessageBox(st);
					st.Format(_T("Links C2...%d  " ), c2);
					AfxMessageBox(st);
					st.Format(_T("Links field1...%d  " ), f1);
					AfxMessageBox(st);
					st.Format(_T("Links field2...%d  " ), f2);
					AfxMessageBox(st);
					AfxMessageBox(_T("Linked Variable"));
					AfxMessageBox(link_var.data());
					
					
					st.Format(_T("JNode...%d  " ), jn);
					AfxMessageBox(st);
					st.Format(_T("BM1 (Parent)...%d  " ), bm1);
					AfxMessageBox(st);
					st.Format(_T("BM2 (Current)...%d  " ), bm2);
					AfxMessageBox(st);
					*/
					//Updates Beta Memories of the RETE Network
					
					CAipi_RETE_Net net;
					net.assertUpdateCreateBM(c1, c2, f1, f2, am2, bm1, pm, bm2, link_var);
					
					/*
					CAipi_PM pmo;
					pmo.addPM_BM(pm, bm2);
					*/			
					CAipi_RETE_TK tko;
					/*
					AfxMessageBox(st);
					st.Format(_T("ParentTK...%d  " ), bmo.m_ParentTK);
					AfxMessageBox(st);
					st.Format(_T("ChildTK...%d  " ), bmo.m_ChildTK);
					AfxMessageBox(st);
					tko.createTKParent_TKLinkE(tko.m_ParentTk);
					*/
					
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					CMainFrame::g_mmWM_ChildTK::iterator iterTK;
					pair <CMainFrame::g_mmWM_ChildTK::iterator, CMainFrame::g_mmWM_ChildTK::iterator>  pTK;
					pTK = pMainFrame->gmmWM_ChildTK.equal_range(wm);
					
					for(iterTK = pTK.first; iterTK != pTK.second; ++iterTK)
					{	
						int tk = iterTK->second;
						bmeo.linkWMEs(bm2, tk);
						//st.Format(_T("Chld Tk...%d  " ), tk);
						//AfxMessageBox(st);
					}
					
					c1 = c2;
					n = pMainFrame->gmmLink.count(c1);
					/*
					st.Format(_T("n..%d  " ), n);
					AfxMessageBox(st);
					*/
				}
				
				
			}
		}
	}

return c2;
}


int CAipi_RETE_Net::retractUpdateBM(int wm)
{

	//AfxMessageBox(_T("RETRACT Update BM"));

	CAipi_RETE_BM bmo;
	CAipi_RETE_TK tko;
	std::vector <int> vLinkToken;

	int parent_tk = tko.findWM_ParentTK(wm);
	int child_tk = tko.findWM_ChildTK(wm);
	//vLinkToken.push_back(parent_tk);	

	/*
	CString st;
	st.Format(_T("WM Parent Token ...%d  " ), parent_tk);
	AfxMessageBox(st);
	st.Format(_T("WM Child Token ...%d  " ), child_tk);
	AfxMessageBox(st);
	*/

	int bm = bmo.searchBMChildTK(child_tk);
	bmo.findBMMembers(bm);
	/*
	st.Format(_T("BM...%d  " ), bm);
	AfxMessageBox(st);
   */
	if( bm != NOT_FOUND )
	{
		vLinkToken.push_back(parent_tk);

		bmo.eraseItemBM_ChildTK(bm, child_tk);
		tko.eraseTK(child_tk);
		tko.eraseWMParentTK(wm);
		tko.eraseWMChildTK(wm);
			
		tko.eraseParent_TKParent_TKChild(parent_tk);
		tko.eraseChild_TKParent_TKChild(child_tk);
		
		if( bmo.countBM(bm) == 0 )
		{
			bmo.addBM(bm, bmo.m_Var1, bmo.m_Data1, bmo.m_Var2, bmo.m_Data2, UNDEFINE, UNDEFINE, bmo.m_WM);	
		}
		
		
	}
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmTKParent_TKLink::iterator it_List;
	pair <CMainFrame::g_mmTKParent_TKLink::iterator, CMainFrame::g_mmTKParent_TKLink::iterator>  pList;
	pList = pMainFrame->gmmTKParent_TKLink.equal_range(parent_tk);

	for(it_List = pList.first; it_List != pList.second; ++it_List)
	{
		/*
		CString str;
		str.Format(_T("Parent Token...%d  " ), it_List->first);
		AfxMessageBox(str);
		str.Format(_T("Child Token...%d  " ), it_List->second);
		AfxMessageBox(str);
		*/
		int token = it_List->first;
		int link_token = it_List->second;
		
		vLinkToken.push_back(link_token);
		
		bm = bmo.searchBMChildTK(link_token);
		bmo.findBMMembers(bm);
		/*
		st.Format(_T("BM...%d  " ), bm);
		AfxMessageBox(st);
		*/
		
		if( bm != NOT_FOUND )
		{
			tko.findTKMembers(link_token);
			int wm = tko.m_WM;
			int p_tk = tko.m_ParentTk;

			tko.eraseWMParentTKE(wm, p_tk);
			tko.eraseWMChildTKE(wm, link_token);
			
			/*
			CString str;
			str.Format(_T("WM_TK Erase...%d  " ), wm);
			AfxMessageBox(str);
			*/
			
			bmo.eraseItemBM_ChildTK(bm, link_token);
			tko.eraseTK(link_token);
			tko.eraseParent_TKParent_TKChild(token);
			tko.eraseChild_TKParent_TKChild(link_token);
			
			if( bmo.countBM(bm) == 0 )
			{
				bmo.addBM(bm, bmo.m_Var1, bmo.m_Data1, bmo.m_Var2, bmo.m_Data2, UNDEFINE, UNDEFINE, bmo.m_WM);	
				
			}
			
		}
			
	}

	//Updates the TKParent_TKLink structure
	for( int i = 0; i< vLinkToken.size(); ++i )
	{
		int tk = vLinkToken.at(i);
		tko.eraseParent_TKParent_TKLink(tk);
	
	}
	

return wm;
}

/*
int CAipi_RETE_Net::retractUpdateBM(int wm)
{
	AfxMessageBox(_T("RETRACT BM"));

	CAipi_RETE_BM bmo;
	CAipi_RETE_TK tko;
	std::vector <int> vLinkToken;

	int token = tko.findWM_ChildTK(wm);
	vLinkToken.push_back(token);	

	CString st;
	st.Format(_T("WM Token ...%d  " ), token);
	AfxMessageBox(st);

	tko.eraseWMChildTKE(wm, token);
	int bm = bmo.searchBMChildTK(token);
	bmo.findBMMembers(bm);
	st.Format(_T("BM...%d  " ), bm);
	AfxMessageBox(st);
	
	if( bm != NOT_FOUND )
	{
		bmo.eraseItemBM_ChildTK(bm, token);
		tko.eraseTK(token);
		tko.eraseParent_TKParent_TKChild(token);
		tko.eraseChild_TKParent_TKChild(token);

		if( bmo.countBM(bm) == 0 )
		{
			bmo.addBM(bm, bmo.m_Var1, bmo.m_Data1, bmo.m_Var2, bmo.m_Data2, UNDEFINE, UNDEFINE, bmo.m_WM);	
		}
		
		
	}





	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmTKParent_TKLink::iterator it_List;
	pair <CMainFrame::g_mmTKParent_TKLink::iterator, CMainFrame::g_mmTKParent_TKLink::iterator>  pList;
	pList = pMainFrame->gmmTKParent_TKLink.equal_range(token);

	for(it_List = pList.first; it_List != pList.second; ++it_List)
	{
		
		CString str;
		str.Format(_T("Child Token...%d  " ), it_List->second);
		AfxMessageBox(str);
		
		token = it_List->second;
		vLinkToken.push_back(token);
		
		bm = bmo.searchBMChildTK(token);
		bmo.findBMMembers(bm);
		st.Format(_T("BM...%d  " ), bm);
		AfxMessageBox(st);
	
		
		if( bm != NOT_FOUND )
		{
			int wm = tko.findWM(token);
			tko.eraseWMChildTKE(wm, token);
			CString str;
			str.Format(_T("WM_TK Erase...%d  " ), wm);
			AfxMessageBox(str);
		
			
			bmo.eraseItemBM_ChildTK(bm, token);
			tko.eraseTK(token);
			tko.eraseParent_TKParent_TKChild(token);
			tko.eraseChild_TKParent_TKChild(token);
			
			if( bmo.countBM(bm) == 0 )
			{
				bmo.addBM(bm, bmo.m_Var1, bmo.m_Data1, bmo.m_Var2, bmo.m_Data2, UNDEFINE, UNDEFINE, bmo.m_WM);	
				
			}
			
		}
		
		
		
			
	}

	for( int i = 0; i< vLinkToken.size(); ++i )
	{
		int tk = vLinkToken.at(i);
		tko.eraseParent_TKParent_TKLink(tk);
	
	}
	
	

return wm;	
}

*/

