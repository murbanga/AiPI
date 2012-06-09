// Aipi_CR_Recency.cpp: implementation of the CAipi_CR_Recency class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_CR_Recency.h"

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

CAipi_CR_Recency::CAipi_CR_Recency()
{

}

CAipi_CR_Recency::~CAipi_CR_Recency()
{

}


CAipi_CR_Recency* CAipi_CR_Recency::addCR_Recency(int ttag, int sum_ttag, int weight, int nc, long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_CR_Recency *pObject = new CAipi_CR_Recency();
    try
	{
		pObject->setSumTimeTag(sum_ttag);
		pObject->setWeight(weight);
		pObject->setnCond(nc);
		pObject->setPM(pm);
			
		pMainFrame->gmmCR_Recency.insert(CMainFrame::g_mmCR_Recency::value_type(ttag, *pObject));
		
		
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


void CAipi_CR_Recency::clearCR_Recency()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->gmmCR_Recency.clear();
	
}


void CAipi_CR_Recency::eraseRecency(int ttag)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmCR_Recency::iterator iter;

	iter = pMainFrame->gmmCR_Recency.find(ttag);
	if( iter != pMainFrame->gmmCR_Recency.end())
	{
		pMainFrame->gmmCR_Recency.erase(ttag);
	}

}


void CAipi_CR_Recency::analizeEqualMaxTimeTag()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	///Saves the time tags with equal max time tag
	CAipi_CR_RecencyTags rto;
	CAipi_CR_Recency ro;

	for( CMainFrame::g_mmCR_Recency::const_iterator iter = pMainFrame->gmmCR_Recency.begin(); iter!= pMainFrame->gmmCR_Recency.end(); ++iter)
	{
		int ttag = iter->first;

		//If there is more than one element with the same index
		//Then it means that there are repeated max time tags 
		int nEqualTTag = pMainFrame->gmmCR_Recency.count(ttag);
		if( nEqualTTag > 1 )
		{
			AfxMessageBox(_T("There are EQUAL TIME TTAGS"));
			ro = (CAipi_CR_Recency)iter->second;
			int ttag = iter->first;
			int sumttag = ro.getSumTimeTag();
			int weight = ro.getWeight();
			int nCond = ro.getnCond();
			long pm = ro.getPM();
			
			rto.addCR_RecencyTags(sumttag, ttag, weight, nCond, pm);
			
		}
	}

	rto.printCR_RecencyTags();
	//First erase the elements in the structure with the same maximum time tag
	for( CMainFrame::g_mmCR_RecencyTags::const_iterator iterTT = pMainFrame->gmmCR_RecencyTags.begin(); iterTT!= pMainFrame->gmmCR_RecencyTags.end(); ++iterTT)
	{
		pMainFrame->gmmCR_Recency.erase(iterTT->first);
	}

	ro.printCR_Recency();
	
	//Then reinserted in the right order acording to sum of all time tags
	for( CMainFrame::g_mmCR_RecencyTags::const_iterator it = pMainFrame->gmmCR_RecencyTags.begin(); it!= pMainFrame->gmmCR_RecencyTags.end(); ++it)
	{
			rto = (CAipi_CR_RecencyTags)it->second;
			int sumttag = iter->first;
			int ttag = rto.getSumTimeTag();
			int weight = rto.getWeight();
			int nCond = rto.getnCond();
			long pm = rto.getPM();
			
			ro.addCR_Recency(ttag, sumttag, weight, nCond, pm);
				
	}

	ro.printCR_Recency();
}



int CAipi_CR_Recency::calcRecencyPM(long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM_WM::iterator iterBM;
	pair <CMainFrame::g_mmBM_WM::iterator, CMainFrame::g_mmBM_WM::iterator>  pBM;
	
	CAipi_CR_Recency ro;
	CAipi_PM pmo;
	CAipi_WM wmo;
	//Saves the maximum time tag for a production in variable test( the most recent)
	int VarMaxTimeTag = 0;
	int	VarSumTimeTag = 0;
	
	//Saves the maximum time tag between constnat and variable ttag
	int maxTTag = 0;
	
		int weight = pmo.findPMWeight(pm);
		int nCond = pmo.countPM_Cond(pm);
		int KSumTimeTag =  calcSumTimeTag(pm);
		
		/*
		CString str;
		AfxMessageBox(_T("Constant Test"));
		str.Format(_T("Fired PM...%d  " ), pm);
		AfxMessageBox(str);
		str.Format(_T("Max Time Tag...%d  " ), m_KMaxTimeTag);
		AfxMessageBox(str);
		str.Format(_T("Sum Time Tag...%d  " ), KSumTimeTag);
		AfxMessageBox(str);
		*/

		//Calculate for variable test 
		int pNode = pmo.findPM_PNode(pm);
		if( pNode != NOT_FOUND )
		{
			VarMaxTimeTag = 0;
			VarSumTimeTag = 0;

			pBM = pMainFrame->gmmBM_WM.equal_range(pNode);
	
			for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
			{	
				int wm = iterBM->second;
				int ttag = wmo.findWMTime(wm);
				VarSumTimeTag += ttag;
				if( ttag > VarMaxTimeTag )
				{
					VarMaxTimeTag = ttag;
				}
				
				/*
				CString str;
				AfxMessageBox(_T("Variable Test"));
				str.Format(_T("Fired PM...%d  " ), pm);
				AfxMessageBox(str);
				str.Format(_T("WM...%d  " ), wm);
				AfxMessageBox(str);
				str.Format(_T("Time Tag...%d  " ), ttag);
				AfxMessageBox(str);
				str.Format(_T("Sum Time Tag...%d  " ), VarSumTimeTag);
				AfxMessageBox(str);
 				str.Format(_T("Max Time Tag...%d  " ), VarMaxTimeTag);
				AfxMessageBox(str);
 				*/
 			
			}
		}

		//Union of time tags sums for constant and variable test
		int total_ttag = VarSumTimeTag + KSumTimeTag;

		//Compare maximum time tags of RETE variable test and constant test
		if( m_KMaxTimeTag > VarMaxTimeTag )
		{
			maxTTag  = m_KMaxTimeTag;
			ro.addCR_Recency(m_KMaxTimeTag, total_ttag, weight, nCond, pm);		
		}
		else
		{
			maxTTag  = VarMaxTimeTag;
			ro.addCR_Recency(VarMaxTimeTag, total_ttag, weight, nCond, pm);
		
		}
		
	
return maxTTag;
}


void CAipi_CR_Recency::calcRecencyFiredPM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM_WM::iterator iterBM;
	pair <CMainFrame::g_mmBM_WM::iterator, CMainFrame::g_mmBM_WM::iterator>  pBM;
	
	CAipi_CR_Recency ro;
	CAipi_PM pmo;
	CAipi_WM wmo;
	//Saves the maximum time tag for a production in variable test( the most recent)
	int VarMaxTimeTag = 0;
	int	VarSumTimeTag = 0;
	
	for(int i=0; i<pMainFrame->g_vFiredPM.size(); ++i)
	{
		long pm = pMainFrame->g_vFiredPM.at(i);
		int weight = pmo.findPMWeight(pm);
		int nCond = pmo.countPM_Cond(pm);
		int KSumTimeTag =  calcSumTimeTag(pm);
		
		/*
		CString str;
		AfxMessageBox(_T("Constant Test"));
		str.Format(_T("Fired PM...%d  " ), pm);
		AfxMessageBox(str);
		str.Format(_T("Max Time Tag...%d  " ), m_KMaxTimeTag);
		AfxMessageBox(str);
		str.Format(_T("Sum Time Tag...%d  " ), KSumTimeTag);
		AfxMessageBox(str);
		*/

		//Calculate for variable test 
		int pNode = pmo.findPM_PNode(pm);
		if( pNode != NOT_FOUND )
		{
			VarMaxTimeTag = 0;
			VarSumTimeTag = 0;

			pBM = pMainFrame->gmmBM_WM.equal_range(pNode);
	
			for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
			{	
				int wm = iterBM->second;
				int ttag = wmo.findWMTime(wm);
				VarSumTimeTag += ttag;
				if( ttag > VarMaxTimeTag )
				{
					VarMaxTimeTag = ttag;
				}
				
				/*
				CString str;
				AfxMessageBox(_T("Variable Test"));
				str.Format(_T("Fired PM...%d  " ), pm);
				AfxMessageBox(str);
				str.Format(_T("WM...%d  " ), wm);
				AfxMessageBox(str);
				str.Format(_T("Time Tag...%d  " ), ttag);
				AfxMessageBox(str);
				str.Format(_T("Sum Time Tag...%d  " ), VarSumTimeTag);
				AfxMessageBox(str);
 				str.Format(_T("Max Time Tag...%d  " ), VarMaxTimeTag);
				AfxMessageBox(str);
 				*/
 			
			}
		}

		//Union of time tags sums for constant and variable test
		int total_ttag = VarSumTimeTag + KSumTimeTag;

		//Compare maximum time tags of RETE variable test and constant test
		if( m_KMaxTimeTag > VarMaxTimeTag )
		{
			ro.addCR_Recency(m_KMaxTimeTag, total_ttag, weight, nCond, pm);	
			
		}
		else 
		{
			ro.addCR_Recency(VarMaxTimeTag, total_ttag, weight, nCond, pm);

		
		}
		
	}


	//analizeEqualMaxTimeTag();
	

}


int CAipi_CR_Recency::calcSumTimeTag(long fired_pm)
{
	
	CAipi_PM pmo;
	CAipi_LHS lhso;
	CAipi_WM wmo;
	int wm = UNDEFINE;
	int timeTag = 0;
	int sumTimeTag = 0;
	m_KMaxTimeTag = 0;

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_Cond::iterator iterPM;
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	
	//CString str;
	pPM = pMainFrame->gmmPM_Cond.equal_range(fired_pm);
	
	//Checks for conditions with just constans elements 
	for(iterPM = pPM.first; iterPM != pPM.second; ++iterPM)
	{	
		int c = iterPM->second;
		int f = lhso.findLHSMembers(c);
		if( f != NOT_FOUND )
		{
			int rel = lhso.m_Rel;
			int categ = lhso.m_Category;
			/*
			str.Format(_T("Cond...%d  " ), c);
			AfxMessageBox(str);
			str.Format(_T("Rel...%d  " ), rel);
			AfxMessageBox(str);
			*/
			if( categ == K_K_K )
			{
			
				switch( rel)
				{
					case EQ : 
						wm = wmo.findEQ_Cond_WM(c);
						timeTag = wmo.findWMTime(wm);
						sumTimeTag += timeTag;
						if( timeTag > m_KMaxTimeTag )
						{
							m_KMaxTimeTag = timeTag;
						}
						/*
						str.Format(_T("WME...%d  " ), wm);
						AfxMessageBox(str);
						str.Format(_T("TimeTag...%d  " ), timeTag);
						AfxMessageBox(str);
						str.Format(_T("sum TimeTag...%d  " ), sumTimeTag);
						AfxMessageBox(str);
						*/
						break;
					case ET :
						wm = wmo.findET_Cond_WM(c);
						timeTag = wmo.findWMTime(wm);
						sumTimeTag += timeTag;
						if( timeTag > m_KMaxTimeTag )
						{
							m_KMaxTimeTag = timeTag;
						}
						break;
					case NE :
						wm = wmo.findNE_Cond_WM(c);
						timeTag = wmo.findWMTime(wm);
						sumTimeTag += timeTag;
						if( timeTag > m_KMaxTimeTag )
						{
							m_KMaxTimeTag = timeTag;
						}
						break;
					case LT : 
						wm = wmo.findLT_Cond_WM(c);
						timeTag = wmo.findWMTime(wm);
						sumTimeTag += timeTag;
						if( timeTag > m_KMaxTimeTag )
						{
							m_KMaxTimeTag = timeTag;
						}
						break;
					case LE :
						wm = wmo.findLE_Cond_WM(c);
						timeTag = wmo.findWMTime(wm);
						sumTimeTag += timeTag;
						if( timeTag > m_KMaxTimeTag )
						{
							m_KMaxTimeTag = timeTag;
						}
						break;
					case GT :
						wm = wmo.findGT_Cond_WM(c);
						timeTag = wmo.findWMTime(wm);
						sumTimeTag += timeTag;
						if( timeTag > m_KMaxTimeTag )
						{
							m_KMaxTimeTag = timeTag;
						}
						break;
					case GE :
						wm = wmo.findGE_Cond_WM(c);
						timeTag = wmo.findWMTime(wm);
						sumTimeTag += timeTag;
						if( timeTag > m_KMaxTimeTag )
						{
							m_KMaxTimeTag = timeTag;
						}
						break;
					//Assignations are not considered in recency conflict resolution	
					/*
					case AS :
						wm = wmo.findAS_Cond_WM(c);
						timeTag = wmo.findWMTime(wm);
						if( timeTag > m_KMaxTimeTag )
						{
							m_KMaxTimeTag = timeTag;
						}
						break;
					default:
						AfxMessageBox(_T("Error in relational operation symbol"));
						break;
					*/
				}
			}

		}
	}
			
	   	
return sumTimeTag;
}





void CAipi_CR_Recency::createAgenda()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	vector< long >::iterator location;

	

	for( CMainFrame::g_mmCR_Recency::reverse_iterator iterRec = pMainFrame->gmmCR_Recency.rbegin(); iterRec!= pMainFrame->gmmCR_Recency.rend(); ++iterRec)
	{
		CAipi_CR_Recency r = (CAipi_CR_Recency)iterRec->second;
		long recency_pm = r.getPM();
		
		
		location = find(pMainFrame->g_vAgendaPM.begin(), pMainFrame->g_vAgendaPM.end(), recency_pm);
		if( location == pMainFrame->g_vAgendaPM.end() )
		{
			pMainFrame->g_vAgendaPM.push_back(recency_pm);
		}
		
	}

	//reverse(pMainFrame->g_vAgendaPM.begin(), pMainFrame->g_vAgendaPM.end());
}


void CAipi_CR_Recency::printCR_Recency()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Recency Structure  *******"));
	
	//Print map container
	for( CMainFrame::g_mmCR_Recency::const_iterator iter = pMainFrame->gmmCR_Recency.begin(); iter!= pMainFrame->gmmCR_Recency.end(); ++iter)
	{
		CString strTTag =_T("Max TimeTag: ");
		CString strSumTTag =_T("Sum TimeTag: ");
		CString strWeight =_T("Weight: ");
		CString strnCond =_T("No. Cond: ");
		CString strPM =_T("P");
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Recency  *******"));
		strTTag +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTTag);
		CAipi_CR_Recency r = (CAipi_CR_Recency)iter->second;
 		
		int sum_ttag = r.getSumTimeTag();
		int w = r.getWeight();
		int nc = r.getnCond();
		int pm = r.getPM();
		
	
		strSumTTag +=  _itot( sum_ttag, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strSumTTag);
		
		strWeight +=  _itot( w, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWeight);
		
		strnCond +=  _itot( nc, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strnCond);
		
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);

				
	}

}



