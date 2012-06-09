// Aipi_RETE_PNode.cpp: implementation of the CAipi_RETE_PNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_PNode.h"

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

CAipi_RETE_PNode::CAipi_RETE_PNode()
{

}

CAipi_RETE_PNode::~CAipi_RETE_PNode()
{

}


CAipi_RETE_PNode* CAipi_RETE_PNode::addPNode(int bm, int c1, int c2, int type )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_PNode *pObject = new CAipi_RETE_PNode();
    try
	{
		pObject->setC1(c1);
		pObject->setC2(c2);
		pObject->setType(type);
		
		pMainFrame->gmPNode.insert(CMainFrame::g_mPNode::value_type(bm, *pObject));
				
		
				
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

void CAipi_RETE_PNode::addFiredPM(long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->g_vFiredPM.push_back(pm);
}


void CAipi_RETE_PNode::addRefractionPM(long pm)
{
	//CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	//pMainFrame->g_vRefractionPM.push_back(pm);

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gsRefractionPM.insert(CMainFrame::g_sRefractionPM::value_type(pm) );
	
	
}

void CAipi_RETE_PNode::clearPNStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmPNode.clear();
	pMainFrame->g_vFiredPM.clear();
	//pMainFrame->g_vRefractionPM.clear();
	pMainFrame->gsRefractionPM.clear();
	pMainFrame->g_vAgendaPM.clear();
}	


void CAipi_RETE_PNode::eraseFiredPM(long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	std::vector<long>::iterator pos;
	pos = find(pMainFrame->g_vFiredPM.begin(),pMainFrame->g_vFiredPM.end(), pm);
	if (pos != pMainFrame->g_vFiredPM.end()) 
	{
		pMainFrame->g_vFiredPM.erase(pos);
	}

}

/*
void CAipi_RETE_PNode::eraseRefractionPM(long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	std::vector<long>::iterator pos;
	pos = find(pMainFrame->g_vRefractionPM.begin(),pMainFrame->g_vRefractionPM.end(), pm);
	if (pos != pMainFrame->g_vRefractionPM.end()) 
	{
		pMainFrame->g_vRefractionPM.erase(pos);
	}

}


*/

void CAipi_RETE_PNode::conflictResolution(int strategy )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	 
	CMainFrame::g_mmCmdLocation::iterator iterCmd;
	pair <CMainFrame::g_mmCmdLocation::iterator, CMainFrame::g_mmCmdLocation::iterator>  pCmd;
	
	CMainFrame::g_mmScriptLocation::iterator iterScript;
	pair <CMainFrame::g_mmScriptLocation::iterator, CMainFrame::g_mmScriptLocation::iterator>  pScript;
	
	bool bDone = true;
	int nCicle = 0;
	g_maxCRCicles = 3;
	int k = 0;
	
while ( bDone  != false  )
{
	++nCicle;

	if( nCicle > g_maxCRCicles )
	{
	  return;		
	}

	//Make the conflict resolution process
	//AfxMessageBox(_T("CR Hello"));
				
	if(	strategy == AIPI_CR_PRIORITY )
	{
		CAipi_CR_Priority pri;
		pri.clearCR_Priority();
		pri.calcPriorityFiredPM();
		pri.createAgenda();
	}
	else if ( strategy == AIPI_CR_RECENCY )
	{
		//AfxMessageBox(_T("CR Function Recency"));
		CAipi_CR_Recency recy;
		recy.clearCR_Recency();
		recy.calcRecencyFiredPM();
		recy.createAgenda();
	}
	else if( strategy == AIPI_CR_SPECIFICITY )
	{
		CAipi_CR_Specificity spety;
		spety.clearCR_Specificity();
		spety.calcSpecificityFiredPM();
		spety.createAgenda();
	}
	else if ( strategy == AIPI_CR_LEX )
	{
		CAipi_CR_LEX lex;
		lex.calcCR_LEX();
		lex.createAgenda();
	}
	else if( strategy == AIPI_CR_MEA )
	{
		//No done yet
	}
	else if ( strategy == AIPI_CR_ORDER )
	{
		//Create agenda by the order the rules where fired
		//AfxMessageBox(_T("strategy by ORDER"));
		/*
		int n = pMainFrame->g_vFiredPM.size();
		if( n > 0 )
		{
			AfxMessageBox(_T("TIENE"));
		}
		*/
		//copy(pMainFrame->g_vFiredPM.begin(), pMainFrame->g_vFiredPM.end(), pMainFrame->g_vAgendaPM.begin());
		//Creates agenda 
		pMainFrame->g_vAgendaPM.clear();
		copy(pMainFrame->g_vFiredPM.begin(), pMainFrame->g_vFiredPM.end(), back_inserter(pMainFrame->g_vAgendaPM));
		
		
	}
	else
	{
		//No strategy were selected
	}

//while ( bDone  != false )
//{

	if( !pMainFrame->g_vAgendaPM.empty() )
	{
		//AfxMessageBox(_T("Agenda Not Empty"));
		printAgendaPM();		
		printFiredPM();
		
		//CAipi_CR_Recency rec;
		//rec.printCR_Recency();
		
		/*
		CAipi_CR_Priority pri;
		pri.printCR_Priority();
		*/

		long higherFiredPM = pMainFrame->g_vAgendaPM.at(0);
		
		/*
		CString str;
		str.Format(_T("HigherFiredPM...%d  " ), higherFiredPM);
		AfxMessageBox(str);
		*/

		//Erase the higher pm from the agenda
		pMainFrame->g_vAgendaPM.erase(pMainFrame->g_vAgendaPM.begin());
		//Erase that production from the fired pm
		CAipi_RETE_PNode pno;
		pno.eraseFiredPM(higherFiredPM);
		
		//Get Alpha Memory Elements Updated
		CAipi_RHS rhs;
		int r = rhs.execPMFacts( higherFiredPM );

		/*
		int r = rhs.assertPMFacts(higherFiredPM);
		if( r == NOT_FOUND )
		{
		  	AfxMessageBox(_T("AM Not Added"));
			//bDone = false;
			
		}

		r = rhs.retractPMFacts(higherFiredPM);
		//AfxMessageBox(_T("Sale"));
		if( r == NOT_FOUND )
		{
			AfxMessageBox(_T("AM Not Removed"));	
		}
		*/	
		
		

		//Search for Commands in the production
		pCmd = pMainFrame->gmmCmdLocation.equal_range(higherFiredPM);
		for(iterCmd = pCmd.first; iterCmd != pCmd.second; ++iterCmd)
		{	
			//AfxMessageBox(_T("Entro a buscar command"));
			CAipi_CmdLocation cloc = (CAipi_CmdLocation)iterCmd->second;
			long index1  = cloc.getStartIndex();
			long index2 = cloc.getEndIndex();
				 
				
			CAipi_ExpParserFile exp;
			g_currentFiredPM = higherFiredPM;
			
			g_TkzIndex1 = index1;
			exp.m_index = index1;
			g_TkzIndex2 = index2;
			exp.m_endIndex = index2;
			exp.callExpParserFile();
			//AfxMessageBox(_T("END ExpParserFILE CONFLIC_SET"));
			if( g_bStopFlag )
			{
				//AfxMessageBox(_T("RETURN"));
				return;
			}			
				
		}

		/*
		//Search for Executable Scripts in the production
		pScript = pMainFrame->gmmScriptLocation.equal_range(higherFiredPM);
		for(iterScript = pScript.first; iterScript != pScript.second; ++iterScript)
		{	
			AfxMessageBox(_T("Entro a buscar script"));
			CAipi_ScriptLocation sloc = (CAipi_ScriptLocation)iterScript->second;
			long index1  = sloc.getStartIndex();
			long index2 = sloc.getEndIndex();
				 
				
			CAipi_ExpParserGUI exp;
			exp.m_index = index1;
			exp.m_endIndex = index2;
			exp.callExpParserGUI();
				
		}
		*/
		
	}
		
	else
	{
		bDone = false;
		//AfxMessageBox(_T("DONE"));
	}
	
	
	
}
	

	
}


int CAipi_RETE_PNode::firedConstMetaRule( long pm)
{
	CAipi_PM pmo;
	CAipi_WM wmo;
	CAipi_LHS lhso;
	
	int c = pmo.findPM_MetaCond(pm);
	lhso.findLHSMembersIForm(c);
	
	/*
	CString str;
	str.Format(_T("Condition...%d  " ), c);
	AfxMessageBox(str);
	str.Format(_T("Id...%f  " ), lhso.m_lhsIdIForm);
	AfxMessageBox(str);
	str.Format(_T("Attr...%f  " ), lhso.m_lhsAttrIForm);
	AfxMessageBox(str);
	str.Format(_T("Val...%f  " ), lhso.m_lhsValIForm);
	AfxMessageBox(str);
	*/
	
	int wm = wmo.findWM(lhso.m_lhsIdIForm, lhso.m_lhsAttrIForm, lhso.m_lhsValIForm);

	//str.Format(_T("WM...%d  " ), wm);
	//AfxMessageBox(str);
	
	if( wm != NOT_FOUND )
	{
		//Already check This is to check numeric operators like GT, LT, GE...
		/*
		CAipi_RETE_AM amo;
		int am = amo.findWM_AM(wm );
		if( am != NOT_FOUND )
		{
			return pm;
		}
		*/
		return pm;
			
	}
	
	
return NOT_FOUND;
}

int CAipi_RETE_PNode::firedVarMetaRule( long pm)
{
	
	CAipi_PM pmo;
	CAipi_RETE_AM amo;
	
	int c = pmo.findPM_MetaCond(pm);

	/*
	CString str;
	str.Format(_T("MetaRule Cond...%d  " ), c);
	AfxMessageBox(str);
	*/

	int am = amo.findCond_AM( c );

	/*
	str.Format(_T("MetaRule AM...%d  " ), am);
	AfxMessageBox(str);
	*/

	int ne = amo.countAM_Cond(am);
	/*
	str.Format(_T("MetaRule No AM elements...%d  " ), ne);
	AfxMessageBox(str);
	*/

	if( ne > 1 )
	{
		//AfxMessageBox(_T("Mayores que 1"));

		return pm;
	}

	
return NOT_FOUND;
}


//This function searchs for  fired productions and then save it
//This function has to be apply after the complete RETE network was generated
int CAipi_RETE_PNode::saveFiredPM( )
{
	
	//AfxMessageBox(_T("-----saved 1"));
	
	CAipi_LHS lhso;
	CAipi_WM wmo;
	CAipi_PM pmo;
	CAipi_RETE_BM bmo;
	bool  bFiredPM = true;
	bool  bK_K_K = true;
	long firedPM = 0;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	for( CMainFrame::g_mPM::const_iterator iter = pMainFrame->gmPM.begin(); iter!= pMainFrame->gmPM.end(); ++iter)
	{
		bFiredPM = true;
		
		int nCond = pmo.countPM_Cond(iter->first);
		
		pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
		pPM = pMainFrame->gmmPM_Cond.equal_range(iter->first);
		
		//Checking Fired productions for constant elements
		
		for(CMainFrame::g_mmPM_Cond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
		{	
			
			int c = it_PM->second;
			int categ = lhso.findLHSCategory(c);
			if( categ == K_K_K )
			{
				bK_K_K = true;

				CAipi_RETE_AM amo;
				int am = amo.findCond_AM(it_PM->second);
				/*
				CString str;
				str.Format(_T("AM...%d  " ), am);
				AfxMessageBox(str);
				*/
				int wm = amo.findAM_WM(am);
				
				//str.Format(_T("WM...%d  " ), wm);
				//AfxMessageBox(str);
				if( wm == NOT_FOUND )
				{
					//Don´t fired the production
					bFiredPM = false;
					//AfxMessageBox(_T("Fired False"));
					
				}
				
				/*
				//check for MetaRules ( the ones that have just one condition
				if( nCond == 1 )
				{
					int f = firedConstMetaRule(iter->first);
					if( f == NOT_FOUND )
					{
						AfxMessageBox(_T("Not Found WM = Cond in MetaRule"));
						//Don´t fired the production
						bFiredPM = false;
					}
					
				}
				*/


			}
			else
			{
				//If any condition of the PM it's not constant
				bK_K_K = false;
			}
			
			/*
			CString str;
			str.Format(_T("Production...%d  " ), it_PM->first);
			AfxMessageBox(str);
			str.Format(_T("Condition...%d  " ), c);
			AfxMessageBox(str);
			str.Format(_T("Category...%d  " ), categ);
			AfxMessageBox(str);
			str.Format(_T("Flag...%d  " ), bFiredPM);
			AfxMessageBox(str);
			str.Format(_T("Flag KKK...%d  " ), bK_K_K);
			AfxMessageBox(str);
			*/
		
			
			
		
		}

		//If all the conditions are constant
		if( bFiredPM == true && bK_K_K == true)
		{
			/*
			CString str;
			str.Format(_T("Constant Fired Production Saved...%d  " ), iter->first);
			AfxMessageBox(str);
			*/
			firedPM = iter->first;
			addFiredPM( firedPM );
			addRefractionPM( firedPM );
			
		}
		
		
		
		//Checking Fired productions for variable bindings
		//If all the Beta Memories(BM) for a specific production has elements
		//then the production match all the variables and it has to fired
			
		/*
		//check for MetaRules ( the ones that have just one condition
		if( nCond == 1 )
		{	
			
			int f = firedVarMetaRule(iter->first);
			if( f != NOT_FOUND )
			{
				AfxMessageBox(_T("Found Var MetaRule"));

				
				CString str;
				str.Format(_T("Variable Fired Meta Production Saved...%d  " ), iter->first);
				AfxMessageBox(str);
						
				CAipi_RETE_PNode pno;
				pno.addFiredPM( iter->first);
				pno.addRefractionPM( iter->first);

			}
			
		}
		*/

		//Get the production node of each production
		int pNode = pmo.findPM_PNode(iter->first);
		int found = bmo.findBMMembers(pNode);
		
		/*
		CString str;
		str.Format(_T("found...%d  " ), found);
		AfxMessageBox(str);
		str.Format(_T("pNode...%d  " ), pNode);
		AfxMessageBox(str);
		*/
		
		if( found != NOT_FOUND )
		{
			//Get the child token of the BM.
			//If this member is Undefine then the last beta memorie is empty
			//(It has no elements)
			int bmChildTK = bmo.m_ChildTK;
						
			/*
			CString str;
			str.Format(_T("BM Child TK...%d  " ), bmChildTK);
			AfxMessageBox(str);
			*/

			if( bmChildTK != UNDEFINE )
			{
							
				//Check if the production is already fired for the constant test
				//This applies in productions that has elements with variables and elements with constants
				if( firedPM != iter->first )
				{
					//Check if some constant test fails
					if( bFiredPM != false )
					{
						/*
						CString str;
						str.Format(_T("Variable Fired Production Saved...%d  " ), iter->first);
						AfxMessageBox(str);
						*/
						
						CAipi_RETE_PNode pno;
						pno.addFiredPM( iter->first);
						pno.addRefractionPM( iter->first);

						
						
					}
				}
			}
		}
	}

return 0;
}


//This function checks if the current fire PM was fired
//before
int CAipi_RETE_PNode::findRefraction( long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_sRefractionPM::iterator iter;
    iter = pMainFrame->gsRefractionPM.find(pm);
	if( iter != pMainFrame->gsRefractionPM.end())
	{
		return *iter;
		
	}
	
	return NOT_FOUND;	

/*
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	vector< long >::iterator iter;
	iter = find(pMainFrame->g_vRefractionPM.begin(), pMainFrame->g_vRefractionPM.end(), pm);
	if( iter != pMainFrame->g_vRefractionPM.end() )
	{
		return FOUND;
	}
	

return NOT_FOUND;
*/
}




//This function searchs for  fired productions and then save it
//This function has to be apply after the complete RETE network was generated
int CAipi_RETE_PNode::saveFiredPM(long pm )
{
	
	//AfxMessageBox(_T("-----saved 2"));
	
	CAipi_LHS lhso;
	CAipi_WM wmo;
	CAipi_PM pmo;
	CAipi_RETE_BM bmo;
	bool  bFiredPM = true;
	bool  bK_K_K = true;
	long firedPM = 0;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Cond.equal_range(pm);
	
	//Checking Fired productions for constant elements
	for(CMainFrame::g_mmPM_Cond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		int c = it_PM->second;
		int categ = lhso.findLHSCategory(c);
		if( categ == K_K_K )
		{
			CAipi_RETE_AM amo;
			int am = amo.findCond_AM(it_PM->second);
			/*
			CString str;
			str.Format(_T("Save F AM...%d  " ), am);
			AfxMessageBox(str);
			*/
			int wm = amo.findAM_WM(am);
			//str.Format(_T("Save F WM...%d  " ), wm);
			//AfxMessageBox(str);
			//amo.printAM_WM();
			
			if( wm == NOT_FOUND )
			{
				//AfxMessageBox(_T("WM Not Found"));
				//Don´t fired the production
				bFiredPM = false;
			}
		}
		else
		{
			//AfxMessageBox(_T("Not Constant"));
			//If any condition of the PM it's not constant
			bK_K_K = false;
		}
		
		/*
		CString str;
		str.Format(_T("Production...%d  " ), it_PM->first);
		AfxMessageBox(str);
		str.Format(_T("Condition...%d  " ), c);
		AfxMessageBox(str);
		str.Format(_T("Category...%d  " ), categ);
		AfxMessageBox(str);
		str.Format(_T("Flag Fired...%d  " ), bFiredPM);
		AfxMessageBox(str);
		str.Format(_T("Flag KKK...%d  " ), bK_K_K);
		AfxMessageBox(str);
		*/
		
		
	}
	
	//If all the conditions are constant
	if( bFiredPM == true && bK_K_K == true)
	{
		/*
		CString str;
		str.Format(_T("Constant Fired Production...%d  " ), pm);
		AfxMessageBox(str);
		*/

		firedPM = pm;
		addFiredPM( firedPM);
		addRefractionPM( firedPM );
		
	}
	
	
	
	//Checking Fired productions for variable bindings
	//If all the Beta Memories(BM) for a specific production has elements
	//then the production match all the variables and it has to fired
	
	//Get the production node of each production
	int pNode = pmo.findPM_PNode(pm);
	int found = bmo.findBMMembers(pNode);
	
	/*
	CString str;
	str.Format(_T("found...%d  " ), found);
	AfxMessageBox(str);
	str.Format(_T("pNode...%d  " ), pNode);
	AfxMessageBox(str);
	*/
	
	if( found != NOT_FOUND )
	{
		//Get the child token of the BM.
		//If this member is Undefine then the last beta memorie is empty
		//(It has no elements)
		int bmChildTK = bmo.m_ChildTK;
		
		/*
		CString str;
		str.Format(_T("BM Child TK...%d  " ), bmChildTK);
		AfxMessageBox(str);
		*/
		
		if( bmChildTK != UNDEFINE )
		{
			//Check if the production is already fired for the constant test
			//This applies in productions that has elements with variables and elements with constants
			if( firedPM != pm )
			{
				//Check if some constant test fails
				if( bFiredPM != false )
				{
					/*
					CString str;
					str.Format(_T("Variable Fired Production...%d  " ), pm);
					AfxMessageBox(str);
					*/
					
					CAipi_RETE_PNode pno;
					pno.addFiredPM( pm);
					pno.addRefractionPM( pm);
					
				}
			}
		}
	}
	

return 0;
}


/*
void CAipi_RETE_PNode::createPNode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	for( CMainFrame::g_mPM::const_iterator iter = pMainFrame->gmPM.begin(); iter!= pMainFrame->gmPM.end(); ++iter)
	{
		definePNode(iter->first);
	}

}

*/





int CAipi_RETE_PNode::definePNode(long pm)
{
/*
	The PNode of a production will be define by the follow criterium:
	1- The number of tokens in the node.
	It will be selected the node that has less numbers of tokens.
	2- The size of each token. ( The number of working memory elements linked in each token).
	It will be selected the node with more linked working memory elements.
	    	
*/
	CAipi_PM pmo;
	CAipi_RETE_BM bmo;
	CAipi_RETE_BME bmeo;
	
	int	temp_sizeTk = 0;
	int temp_bm = UNDEFINE;
			
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_BM::iterator iterPM;
	pair <CMainFrame::g_mmPM_BM::iterator, CMainFrame::g_mmPM_BM::iterator>  pPM;
	pPM = pMainFrame->gmmPM_BM.equal_range(pm);
	
	for(iterPM = pPM.first; iterPM != pPM.second; ++iterPM)
	{	
		int bm = iterPM->second;
		int f = bmo.findBMMembers(bm);
		if( f != NOT_FOUND )
		{
			int chdTk =  bmo.m_ChildTK;
			/*
			CString str;
			str.Format(_T("BM...%d  " ), bm);
			AfxMessageBox(str);
			str.Format(_T("Chld TK...%d  " ), chdTk);
			AfxMessageBox(str);
		  */
			if( chdTk == UNDEFINE )
			{
				//AfxMessageBox(_T("PNode UNDEFINE"));
				pmo.addPM_PNode(pm, UNDEFINE);
				return UNDEFINE;
			}
		
			bmeo.findBMEMembers(bm);
			int nTk = bmeo.m_nTokens;
			int sizeTk = bmeo.m_sizeToken;
	
			
			if( sizeTk > temp_sizeTk )
			{
				temp_sizeTk = sizeTk;
				temp_bm = bm;
			}

			/*
			if( nTk < temp_nTk )
			{
				temp_nTk = nTk;
				temp_bm_nTk = bm;
			}
			*/
		
		}

	}

	
	int pNode = pmo.findPM_PNode(pm);
	if( pNode == temp_bm )
	{
		//AfxMessageBox(_T("PNODE : No Update has made"));
		return P_UNSUCCESS;
	}

	if( pNode == UNDEFINE )
	{
		pmo.erasePM_PNode(pm);
	}
	
	if( temp_bm != UNDEFINE )
	{
		pmo.addPM_PNode(pm, temp_bm);
	}

return P_SUCCESS;
}



void CAipi_RETE_PNode::printPN()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Node  *******"));
	
	//Print map container
	for( CMainFrame::g_mPNode::const_iterator iter = pMainFrame->gmPNode.begin(); iter!= pMainFrame->gmPNode.end(); ++iter)
	{
		CString strPN = _T("PN");
		CString strCond = _T("C");
		CString strType =_T("TYPE_");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PNode Element  *******"));
		strPN +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPN);
		
		CAipi_RETE_PNode pn = (CAipi_RETE_PNode)iter->second;
 		int c1 = pn.getC1();
		int c2 = pn.getC2();
		int type = pn.getType();
				
	
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  C1: "));
		strCond +=  _itot( c1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);

		strCond =_T("C");
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  C2: "));
		strCond +=  _itot( c2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Type: "));
		strType +=  _itot( type, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strType);
		
			
	}

}


void CAipi_RETE_PNode::printAgendaPM()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Agenda  *******"));
	
	
	for(int i=0; i<pMainFrame->g_vAgendaPM.size(); ++i)
	{
		CString strPM =_T("PM");
		strPM +=  _itot( pMainFrame->g_vAgendaPM.at(i), buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		//AfxMessageBox(strPM);
	}


}


void CAipi_RETE_PNode::printFiredPM()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Fired PM *******"));
	
	
	for(int i=0; i<pMainFrame->g_vFiredPM.size(); ++i)
	{
		CString strPM =_T("PM");
		strPM +=  _itot( pMainFrame->g_vFiredPM.at(i), buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
	}


}

void CAipi_RETE_PNode::printRefractionPM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Refraction Production Memory  *******"));
	
	//Print map container
	for( CMainFrame::g_sRefractionPM::const_iterator iter = pMainFrame->gsRefractionPM.begin(); iter!= pMainFrame->gsRefractionPM.end(); ++iter)
	{
		CString strPM = _T("PM");
		strPM +=  _itot( *iter, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
			
	}


/*
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Refraction PM *******"));
	
	
	for(int i=0; i<pMainFrame->g_vRefractionPM.size(); ++i)
	{
		CString strPM =_T("PM");
		strPM +=  _itot( pMainFrame->g_vRefractionPM.at(i), buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
	}
*/

}



int CAipi_RETE_PNode::findPNodeMembers(int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mPNode::iterator iter;
    iter = pMainFrame->gmPNode.find(bm);
	if( iter != pMainFrame->gmPNode.end())
	{
  		CAipi_RETE_PNode pn = (CAipi_RETE_PNode)iter->second;
 		m_C1 =  pn.getC1();
		m_C2 = pn.getC2();
		m_Type =pn.getType();
	}
	
		return NOT_FOUND;
	
}






int CAipi_RETE_PNode::findC1(int p)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mPNode::iterator iter;
    iter = pMainFrame->gmPNode.find(p);
	if( iter != pMainFrame->gmPNode.end())
	{
  		CAipi_RETE_PNode pn = (CAipi_RETE_PNode)iter->second;
 		return pn.getC1();
	}
	
		return NOT_FOUND;
	
}


int CAipi_RETE_PNode::findC2(int p)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mPNode::iterator iter;
    iter = pMainFrame->gmPNode.find(p);
	if( iter != pMainFrame->gmPNode.end())
	{
  		CAipi_RETE_PNode pn = (CAipi_RETE_PNode)iter->second;
 		return pn.getC2();
	}
	
		return NOT_FOUND;
	

}








