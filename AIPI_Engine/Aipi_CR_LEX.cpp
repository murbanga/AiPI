// Aipi_CR_LEX.cpp: implementation of the CAipi_CR_LEX class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_CR_LEX.h"


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

CAipi_CR_LEX::CAipi_CR_LEX()
{

}

CAipi_CR_LEX::~CAipi_CR_LEX()
{

}


void CAipi_CR_LEX::calcCR_LEX()
{
	CAipi_CR_Priority pri;
	pri.calcPriorityFiredPM();

	

	int tempWeight = 0;
	int tempSumTTag = 0;
	int maxttag = 0;
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmCR_Priority::iterator iterPri;
	pair <CMainFrame::g_mmCR_Priority::iterator, CMainFrame::g_mmCR_Priority::iterator>  pPri;
	//CMainFrame::g_mmCR_Recency::iterator iterRec;
	//pair <CMainFrame::g_mmCR_Recency::iterator, CMainFrame::g_mmCR_Recency::iterator>  pRec;
	CMainFrame::g_mmCR_RecencyTags::iterator iterRecT;
	pair <CMainFrame::g_mmCR_RecencyTags::iterator, CMainFrame::g_mmCR_RecencyTags::iterator>  pRecT;
	
	
	for( CMainFrame::g_mmCR_Priority::const_iterator itPri = pMainFrame->gmmCR_Priority.begin(); itPri!= pMainFrame->gmmCR_Priority.end(); ++itPri)
	{
		int weight = itPri->first;
		//Check for repeated weights in the structure jump them
		if( tempWeight == weight )
		{
			tempWeight = weight;
			continue;
		}
		
		int nWeight = pMainFrame->gmmCR_Priority.count(weight);
	
		if( nWeight > 1 )
		{
			pPri = pMainFrame->gmmCR_Priority.equal_range(weight);
			
	
			//Fill recency structure for fired productions with the same priority 
			for(iterPri = pPri.first; iterPri != pPri.second; ++iterPri)
			{	
				pri = (CAipi_CR_Priority)iterPri->second;
				long pm = pri.getPM();
							
				CAipi_CR_Recency ro;
				maxttag = ro.calcRecencyPM( pm);
			}
		}
	}

	
	
	//Check for equality of maximum time tags in recency structure 
	int nTimeTag = pMainFrame->gmmCR_Recency.count(maxttag);
	if( nTimeTag > 1 )
	{
		//Check equal maximum time tags for recency structure and sort it
		CAipi_CR_Recency ro;
		ro.analizeEqualMaxTimeTag();
	}

	for( CMainFrame::g_mmCR_RecencyTags::const_iterator itRT = pMainFrame->gmmCR_RecencyTags.begin(); itRT!= pMainFrame->gmmCR_RecencyTags.end(); ++itRT)
	{
		int sumttag = itRT->first;
		//Check for repeated weights in the structure jump them
		if( tempSumTTag == sumttag )
		{
			tempSumTTag = sumttag; 
			continue;
		}
		//Check for equal sum of tiem tags in RecencyTags structure
		int nSumTimeTag = pMainFrame->gmmCR_RecencyTags.count(itRT->first);
		
		if( nSumTimeTag > 1 )
		{
			CAipi_CR_Specificity spo;
			CAipi_CR_RecencyTags rto;

			pRecT= pMainFrame->gmmCR_RecencyTags.equal_range(sumttag);

			for(iterRecT = pRecT.first; iterRecT != pRecT.second; ++iterRecT)
			{	
				rto = (CAipi_CR_RecencyTags)iterRecT->second;

				int nCond = rto.getnCond();
				int ttag = rto.getTimeTag();
				int sttag = rto.getSumTimeTag();
				int w = rto.getWeight();
				int pm = rto.getPM();

				
				spo.addCR_Specificity(nCond, ttag, sttag, w, pm);

						
			}
		}
	}

					
	
					
}


void CAipi_CR_LEX::createAgenda()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	vector< long >::iterator location;

	for( CMainFrame::g_mmCR_Specificity::const_iterator iterSpe = pMainFrame->gmmCR_Specificity.begin(); iterSpe!= pMainFrame->gmmCR_Specificity.end(); ++iterSpe)
	{
		CAipi_CR_Specificity s = (CAipi_CR_Specificity)iterSpe->second;
		long specificity_pm = s.getPM();
		pMainFrame->g_vAgendaPM.push_back(specificity_pm);
	}

	for( CMainFrame::g_mmCR_Recency::const_iterator iterRec = pMainFrame->gmmCR_Recency.begin(); iterRec!= pMainFrame->gmmCR_Recency.end(); ++iterRec)
	{
		CAipi_CR_Recency r = (CAipi_CR_Recency)iterRec->second;
		long recency_pm = r.getPM();
		
		for(int i = 0; i< pMainFrame->g_vAgendaPM.size(); ++i )
		{
			long agenda_pm = pMainFrame->g_vAgendaPM.at(i);
			if( recency_pm != agenda_pm )
			{
				location = find(pMainFrame->g_vAgendaPM.begin(), pMainFrame->g_vAgendaPM.end(), recency_pm);
				
				if( location == pMainFrame->g_vAgendaPM.end() ) 
				{
					pMainFrame->g_vAgendaPM.push_back(recency_pm);
				
				}
			}
		}
	}

	for( CMainFrame::g_mmCR_Priority::const_iterator iterPri = pMainFrame->gmmCR_Priority.begin(); iterPri!= pMainFrame->gmmCR_Priority.end(); ++iterPri)
	{
		CAipi_CR_Priority p = (CAipi_CR_Priority)iterPri->second;
		long priority_pm = p.getPM();
		
		for(int i = 0; i< pMainFrame->g_vAgendaPM.size(); ++i )
		{
			long agenda_pm = pMainFrame->g_vAgendaPM.at(i);
			if( priority_pm != agenda_pm )
			{
				
				
				location = find(pMainFrame->g_vAgendaPM.begin(), pMainFrame->g_vAgendaPM.end(), priority_pm);
				if( location == pMainFrame->g_vAgendaPM.end() ) 
				{
					pMainFrame->g_vAgendaPM.push_back(priority_pm);
				}
			}
		}
	}


	reverse(pMainFrame->g_vAgendaPM.begin(), pMainFrame->g_vAgendaPM.end());

}


void CAipi_CR_LEX::clearCR_LEX()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->gmmCR_Priority.clear();
	pMainFrame->gmmCR_Recency.clear();
	pMainFrame->gmmCR_RecencyTags.clear();
	pMainFrame->gmmCR_Specificity.clear();
}


