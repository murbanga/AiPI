// Aipi_CR_RecencyTags.cpp: implementation of the CAipi_CR_RecencyTags class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_CR_RecencyTags.h"

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

CAipi_CR_RecencyTags::CAipi_CR_RecencyTags()
{

}

CAipi_CR_RecencyTags::~CAipi_CR_RecencyTags()
{

}


CAipi_CR_RecencyTags* CAipi_CR_RecencyTags::addCR_RecencyTags(int sum_ttag, int ttag, int weight, int nc, long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_CR_RecencyTags *pObject = new CAipi_CR_RecencyTags();
    try
	{
		pObject->setTimeTag(ttag);
		pObject->setWeight(weight);
		pObject->setnCond(nc);
		pObject->setPM(pm);
			
		pMainFrame->gmmCR_RecencyTags.insert(CMainFrame::g_mmCR_RecencyTags::value_type(sum_ttag, *pObject));
		
		
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


void CAipi_CR_RecencyTags::clearCR_RecencyTags()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmCR_RecencyTags.clear();
	
}



int CAipi_CR_RecencyTags::calcRecencyTagsPM(long pm)
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
			ro.addCR_Recency(total_ttag, m_KMaxTimeTag, weight, nCond, pm);		
		}
		else
		{
			maxTTag  = VarMaxTimeTag;
			ro.addCR_Recency(total_ttag, VarMaxTimeTag, weight, nCond, pm);
		
		}
		
	
return maxTTag;
}


void CAipi_CR_RecencyTags::calcRecencyTagsFiredPM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM_WM::iterator iterBM;
	pair <CMainFrame::g_mmBM_WM::iterator, CMainFrame::g_mmBM_WM::iterator>  pBM;
	
	CAipi_CR_RecencyTags rto;
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
			rto.addCR_RecencyTags(total_ttag, m_KMaxTimeTag, weight, nCond, pm);		
		}
		else
		{
			rto.addCR_RecencyTags(total_ttag, VarMaxTimeTag, weight, nCond, pm);
		
		}
		
	}

}


int CAipi_CR_RecencyTags::calcSumTimeTag(long fired_pm)
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


void CAipi_CR_RecencyTags::printCR_RecencyTags()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  RecencyTags  Structure  *******"));
	
	//Print map container
	for( CMainFrame::g_mmCR_RecencyTags::const_iterator iter = pMainFrame->gmmCR_RecencyTags.begin(); iter!= pMainFrame->gmmCR_RecencyTags.end(); ++iter)
	{
		CString strSumTTag =_T("Sum TimeTag: ");
		CString strTTag =_T("Max TimeTag: ");
		CString strWeight =_T("Weight: ");
		CString strnCond =_T("No. Cond: ");
		CString strPM =_T("P");
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  RecencyTags  *******"));
		strSumTTag +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strSumTTag);
		CAipi_CR_RecencyTags rt = (CAipi_CR_RecencyTags)iter->second;
 		
		int ttag = rt.getTimeTag();
		int w = rt.getWeight();
		int nc = rt.getnCond();
		int pm = rt.getPM();
		
	
		strTTag +=  _itot( ttag, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTTag);
		
		strWeight +=  _itot( w, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWeight);
		
		strnCond +=  _itot( nc, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strnCond);
		
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);

				
	}

}


