// Aipi_CR_Specificity.cpp: implementation of the CAipi_CR_Specificity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_CR_Specificity.h"

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

CAipi_CR_Specificity::CAipi_CR_Specificity()
{

}

CAipi_CR_Specificity::~CAipi_CR_Specificity()
{

}

CAipi_CR_Specificity* CAipi_CR_Specificity::addCR_Specificity(int nc, int max_ttag, int sum_ttag, int weight, long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_CR_Specificity *pObject = new CAipi_CR_Specificity();
    try
	{
		pObject->setTimeTag(max_ttag);
		pObject->setSumTimeTag(sum_ttag);
		pObject->setWeight(weight);
		pObject->setPM(pm);
			
		pMainFrame->gmmCR_Specificity.insert(CMainFrame::g_mmCR_Specificity::value_type(nc, *pObject));
		
		
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


void CAipi_CR_Specificity::clearCR_Specificity()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->gmmCR_Specificity.clear();
}


void CAipi_CR_Specificity::eraseSpecificity(int nc)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmCR_Specificity::iterator iter;

	iter = pMainFrame->gmmCR_Specificity.find(nc);
	if( iter != pMainFrame->gmmCR_Specificity.end())
	{
		pMainFrame->gmmCR_Specificity.erase(nc);
	}

}


int CAipi_CR_Specificity::calcSpecificityPM(long pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM_WM::iterator iterBM;
	pair <CMainFrame::g_mmBM_WM::iterator, CMainFrame::g_mmBM_WM::iterator>  pBM;
	
	CAipi_CR_Specificity sp;
	CAipi_PM pmo;
	CAipi_WM wmo;
	//Saves the maximum time tag for a production in variable test( the most recent)
	int VarMaxTimeTag = 0;
	int	VarSumTimeTag = 0;
	
	//Saves the maximum time tag between constant and variable ttag
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
			sp.addCR_Specificity(nCond, m_KMaxTimeTag, total_ttag, weight, pm);		
		}
		else
		{
			maxTTag  = VarMaxTimeTag;
			sp.addCR_Specificity(nCond, VarMaxTimeTag, total_ttag, weight, pm);
		
		}
		
	
return maxTTag;
}


void CAipi_CR_Specificity::calcSpecificityFiredPM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM_WM::iterator iterBM;
	pair <CMainFrame::g_mmBM_WM::iterator, CMainFrame::g_mmBM_WM::iterator>  pBM;
	
	CAipi_CR_Specificity sp;
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
			sp.addCR_Specificity(nCond, m_KMaxTimeTag, total_ttag, weight, pm);		
		}
		else
		{
			sp.addCR_Specificity(nCond, VarMaxTimeTag, total_ttag, weight, pm);
		
		}
		
	}

}


int CAipi_CR_Specificity::calcSumTimeTag(long fired_pm)
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




void CAipi_CR_Specificity::createAgenda()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	vector< long >::iterator location;

	
	for( CMainFrame::g_mmCR_Specificity::reverse_iterator iterSpe = pMainFrame->gmmCR_Specificity.rbegin(); iterSpe!= pMainFrame->gmmCR_Specificity.rend(); ++iterSpe)
	{
		CAipi_CR_Specificity s = (CAipi_CR_Specificity)iterSpe->second;
		long specificity_pm = s.getPM();

		location = find(pMainFrame->g_vAgendaPM.begin(), pMainFrame->g_vAgendaPM.end(), specificity_pm);
		if( location == pMainFrame->g_vAgendaPM.end() )
		{
			pMainFrame->g_vAgendaPM.push_back(specificity_pm);
		}
	}

	//reverse(pMainFrame->g_vAgendaPM.begin(), pMainFrame->g_vAgendaPM.end());
}


void CAipi_CR_Specificity::printCR_Specificity()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Specificity Structure  *******"));
	
	//Print map container
	for( CMainFrame::g_mmCR_Specificity::const_iterator iter = pMainFrame->gmmCR_Specificity.begin(); iter!= pMainFrame->gmmCR_Specificity.end(); ++iter)
	{
		CString strnCond =_T("No. Cond: ");
		CString strTTag =_T("Max TimeTag: ");
		CString strSumTTag =_T("Sum TimeTag: ");
		CString strWeight =_T("Weight: ");
		CString strPM =_T("P");
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Specificity  *******"));
		strnCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strnCond);
		
		CAipi_CR_Specificity s = (CAipi_CR_Specificity)iter->second;
 		
		int	max_ttag = s.getTimeTag();
		int sum_ttag = s.getSumTimeTag();
		int w = s.getWeight();
		int nc = s.getnCond();
		int pm = s.getPM();
		

		strTTag +=  _itot( max_ttag, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strTTag);
	
		strSumTTag +=  _itot( sum_ttag, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strSumTTag);
		
		strWeight +=  _itot( w, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWeight);
		
		
		
		strPM +=  _itot( pm, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);

				
	}

}




