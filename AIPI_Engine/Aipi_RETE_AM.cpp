// Aipi_RETE_AM.cpp: implementation of the CAipi_RETE_AM class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_AM.h"

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

CAipi_RETE_AM::CAipi_RETE_AM()
{

}

CAipi_RETE_AM::~CAipi_RETE_AM()
{
	
}


int CAipi_RETE_AM::generateAMKey()
{
	/*
	static int nAM;
	nAM++;
	*/	
	++g_currentAM;

return g_currentAM;

}

/*
void CAipi_RETE_AM::createAM()
{
	//constantTest();
	constantTestIForm();
	insertStructsWM_AM();

}
*/

int CAipi_RETE_AM::sizeAM_Cond()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmmAM_Cond.size();

}

int CAipi_RETE_AM::sizeCond_AM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmCond_AM.size();

}

int CAipi_RETE_AM::sizeAM_WM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gmmAM_WM.size();

}

int CAipi_RETE_AM::lastAM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_Cond::iterator iterAM;
	if( !pMainFrame->gmmAM_Cond.empty())
	{
		iterAM = pMainFrame->gmmAM_Cond.end(); 
		--iterAM;
		return iterAM->first;
	}

	return 0;
	
}


void CAipi_RETE_AM::addAM_WM(int am, int wm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(am, wm));
	
}


void CAipi_RETE_AM::addWM_AM(int wm, int am)
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	//pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, am));
	pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, am));
}




void CAipi_RETE_AM::eraseWM_AM(int wm)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmWM_AM::iterator iterAM;
	iterAM = pMainFrame->gmmWM_AM.find(wm);
	if( iterAM != pMainFrame->gmmWM_AM.end())
	{
		pMainFrame->gmmWM_AM.erase(wm);
	}
	

	/*
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mWM_AM::iterator iterAM;
	iterAM = pMainFrame->gmWM_AM.find(wm);
	if( iterAM != pMainFrame->gmWM_AM.end())
	{
		pMainFrame->gmWM_AM.erase(wm);
	}
	*/
}

/*
int CAipi_RETE_AM::eraseItemWM_AM(int wme, int a)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmWM_AM::iterator iterAM;
	pair <CMainFrame::g_mmWM_AM::iterator, CMainFrame::g_mmWM_AM::iterator>  pAM;
	pAM = pMainFrame->gmmWM_AM.equal_range(wme);
			
	for(iterAM = pAM.first; iterAM != pAM.second; ++iterAM)
	{	
		if( iterAM->second == a )
		{
			pMainFrame->gmmAM_WM.erase(iterAM);
			return iterAM->first;
		}
		

	}

return NOT_FOUND;
	
}
*/




int CAipi_RETE_AM::eraseItemAM_WM(int am, int wm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_WM::iterator iterAM;
	pair <CMainFrame::g_mmAM_WM::iterator, CMainFrame::g_mmAM_WM::iterator>  pAM;
	pAM = pMainFrame->gmmAM_WM.equal_range(am);
			
	for(iterAM = pAM.first; iterAM != pAM.second; ++iterAM)
	{	
		if( iterAM->second == wm )
		{
			//pMainFrame->gmmAM.erase(iterAM++);
			pMainFrame->gmmAM_WM.erase(iterAM);
			return iterAM->first;
		}
		//else
		//{
			//++iterAM;
		//}

	}

return NOT_FOUND;
	
}


void CAipi_RETE_AM::eraseCondStructs(int pm)
{
	CAipi_RETE_Cond co;

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_Cond::iterator it_PM;
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_Cond.equal_range(pm);	

	for(it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		int a = findCond_AM(it_PM->second);
		
		/*
		CString str;
		str.Format(_T("AM...%d  " ), a);
		AfxMessageBox(str);
		str.Format(_T("Condition...%d  " ), it_PM->second);
		AfxMessageBox(str);
		*/
		
		if( a != NOT_FOUND )
		{
			eraseItemAM_Cond(a, it_PM->second);
			eraseCond_AM(it_PM->second);
			co.eraseCond1(it_PM->second);
			co.eraseCond2(it_PM->second);
		}

	}
	
}




void CAipi_RETE_AM::eraseCond_AM(int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mCond_AM::iterator iterAM;
	iterAM = pMainFrame->gmCond_AM.find(c);
	if( iterAM != pMainFrame->gmCond_AM.end())	
	{
		pMainFrame->gmCond_AM.erase(c);
	}

}

void CAipi_RETE_AM::eraseAM_Cond(int am)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_Cond::iterator iterAM;

	iterAM = pMainFrame->gmmAM_Cond.find(am);
	if( iterAM != pMainFrame->gmmAM_Cond.end())
	{
		pMainFrame->gmmAM_Cond.erase(am);
	}

}


int CAipi_RETE_AM::eraseItemAM_Cond(int a, int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_Cond::iterator iterAM;
	pair <CMainFrame::g_mmAM_Cond::iterator, CMainFrame::g_mmAM_Cond::iterator>  pAM;
	pAM = pMainFrame->gmmAM_Cond.equal_range(a);
			
	for(iterAM = pAM.first; iterAM != pAM.second; ++iterAM)
	{	
		if( iterAM->second == c )
		{
			pMainFrame->gmmAM_Cond.erase(iterAM);
			return iterAM->first;
		}
		

	}

return NOT_FOUND;

}





void CAipi_RETE_AM::eraseAM_WM(int am )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_WM::iterator iterAM;
	
	iterAM = pMainFrame->gmmAM_WM.find(am);
	if( iterAM != pMainFrame->gmmAM_WM.end())
	{
		pMainFrame->gmmAM_WM.erase(am);	
		
	}

	
}

/*
void CAipi_RETE_AM::addWMEs()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	RETE_WM wme;
	tstring str =_T("");
	
	//constantTestLHS();
		

	for( CMainFrame::g_mWM::const_iterator it = pMainFrame->gmWM.begin(); it != pMainFrame->gmWM.end(); ++it)
	{
		tstring strId	= wme.getWMEId(it->first);
		tstring strAttr	= wme.getWMEAttr(it->first);
		tstring strVal	= wme.getWMEVal(it->first);

		//// Empty - Empty - Value  ( ID_AT_K )////
		
			m_mmEQ_I_A_K::iterator it_iaK;
			if( !mmEQ_I_A_K.empty())
			{
			
				pair <m_mmEQ_I_A_K::iterator, m_mmEQ_I_A_K::iterator>  piaK;
				piaK = mmEQ_I_A_K.equal_range(strVal);

				for(it_iaK = piaK.first; it_iaK != piaK.second; ++it_iaK)
				{	
					pMainFrame->gmmAM.insert(CMainFrame::g_mmAM::value_type(it_iaK->second , it->first));
				}
			}

			
		
		//// Empty - Attribute - Empty ( ID_K_VL )////
			
			m_mmEQ_I_K_V::iterator it_iKv;
			if( !mmEQ_I_K_V.empty() )
			{
				pair <m_mmEQ_I_K_V::iterator, m_mmEQ_I_K_V::iterator>  piKv;
				piKv = mmEQ_I_K_V.equal_range(strAttr);

				for(it_iKv = piKv.first; it_iKv != piKv.second; ++it_iKv)
				{	
					pMainFrame->gmmAM.insert(CMainFrame::g_mmAM::value_type(it_iKv->second , it->first));
				}
			}
			
		
		//// Empty - Attribute - Value ( ID_K_K )////
			
			m_mmEQ_I_K_K::iterator it_iKK;
			str = strAttr + strVal;
			if( !mmEQ_I_K_K.empty() )
			{
				pair <m_mmEQ_I_K_K::iterator, m_mmEQ_I_K_K::iterator>  piKK;
				piKK = mmEQ_I_K_K.equal_range(str);

				for(it_iKK = piKK.first; it_iKK != piKK.second; ++it_iKK)
				{	
					pMainFrame->gmmAM.insert(CMainFrame::g_mmAM::value_type(it_iKK->second , it->first));
				}
			}
					
		
		
		//// Identifier - Empty - Empty ( K_AT_VL )////
			
			m_mmEQ_K_A_V::iterator it_Kav;
			if( !mmEQ_K_A_V.empty() )
			{
				pair <m_mmEQ_K_A_V::iterator, m_mmEQ_K_A_V::iterator>  pKav;
				pKav = mmEQ_K_A_V.equal_range(strId);

				for(it_Kav = pKav.first; it_Kav != pKav.second; ++it_Kav)
				{	
					pMainFrame->gmmAM.insert(CMainFrame::g_mmAM::value_type(it_Kav->second , it->first));
				}
			}
			
		
		//// Identifier - Empty - Value (K_AT_K )////
			
			
			m_mmEQ_K_A_K::iterator it_KaK;
			str = strId + strVal;
			if ( !mmEQ_K_A_K.empty() )
			{
				pair <m_mmEQ_K_A_K::iterator, m_mmEQ_K_A_K::iterator>  pKaK;
				pKaK = mmEQ_K_A_K.equal_range(str);

				for(it_KaK = pKaK.first; it_KaK != pKaK.second; ++it_KaK)
				{	
					pMainFrame->gmmAM.insert(CMainFrame::g_mmAM::value_type(it_KaK->second , it->first));
				}
			}
			

		//// Identifier - Attribute - Empty ( K_K_VL )////
			
			m_mmEQ_K_K_V::iterator it_KKv;
			str = strId + strAttr;
			if( !mmEQ_K_K_V.empty() )
			{
				pair <m_mmEQ_K_K_V::iterator, m_mmEQ_K_K_V::iterator>  pKKv;
				pKKv = mmEQ_K_K_V.equal_range(str);

				for(it_KKv = pKKv.first; it_KKv != pKKv.second; ++it_KKv)
				{	
					pMainFrame->gmmAM.insert(CMainFrame::g_mmAM::value_type(it_KKv->second , it->first));
				}
			}
			

		//// Identifier - Attribute - Value ( K_K_K )////
			
			m_mmEQ_K_K_K::iterator it_KKK;
			str = strId + strAttr + strVal;
			if( !mmEQ_K_K_K.empty() )
			{
				pair <m_mmEQ_K_K_K::iterator, m_mmEQ_K_K_K::iterator>  pKKK;
				pKKK = mmEQ_K_K_K.equal_range(str);

				for(it_KKK = pKKK.first; it_KKK != pKKK.second; ++it_KKK)
				{	
					pMainFrame->gmmAM.insert(CMainFrame::g_mmAM::value_type(it_KKK->second , it->first));
				}
			}
			
		
		//// Empty - Empty - Empty ( ID_AT_VL )////
			
			m_mmEQ_I_A_V::iterator it_iav;
		
			if ( !mmEQ_I_A_V.empty())
			{
				pair <m_mmEQ_I_A_V::iterator, m_mmEQ_I_A_V::iterator>  piav;
				piav = mmEQ_I_A_V.equal_range(_T("e"));

				for(it_iav = piav.first; it_iav != piav.second; ++it_iav)
				{	
					pMainFrame->gmmAM.insert(CMainFrame::g_mmAM::value_type(it_iav->second , it->first));
				}
			}
			

		
	}



}
*/


/*
void CAipi_RETE_AM::addWMEsNewPM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_WM wme;
	tstring str =_T("");
	
	
		

	for( CMainFrame::g_mWM::const_iterator it = pMainFrame->gmWM.begin(); it != pMainFrame->gmWM.end(); ++it)
	{
		tstring strId	= wme.findwmd(it->first);
		tstring strAttr	= wme.findWMAttr(it->first);
		tstring strVal	= wme.findWMVal(it->first);

		int a = findAMWME(it->first);


		//// Empty - Empty - Value  ( ID_AT_K )////
		
			CMainFrame::g_mmEQ_I_A_K::iterator it_iaK;
			if( !pMainFrame->gmmEQ_I_A_K.empty())
			{
			
				
				pair <CMainFrame::g_mmEQ_I_A_K::iterator, CMainFrame::g_mmEQ_I_A_K::iterator>  piaK;
				piaK = pMainFrame->gmmEQ_I_A_K.equal_range(strVal);

				for(it_iaK = piaK.first; it_iaK != piaK.second; ++it_iaK)
				{	
					if( a != it_iaK->second )
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iaK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iaK->second));
				}
			}

			
		
		//// Empty - Attribute - Empty ( ID_K_VL )////
			
			CMainFrame::g_mmEQ_I_K_V::iterator it_iKv;
			if( !pMainFrame->gmmEQ_I_K_V.empty() )
			{
								
				pair <CMainFrame::g_mmEQ_I_K_V::iterator, CMainFrame::g_mmEQ_I_K_V::iterator>  piKv;
				piKv = pMainFrame->gmmEQ_I_K_V.equal_range(strAttr);

				for(it_iKv = piKv.first; it_iKv != piKv.second; ++it_iKv)
				{	
					if( a != it_iKv->second )
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iKv->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iKv->second));
				}
			}
			
		
		//// Empty - Attribute - Value ( ID_K_K )////
			
			CMainFrame::g_mmEQ_I_K_K::iterator it_iKK;
			str = strAttr + strVal;
			if( !pMainFrame->gmmEQ_I_K_K.empty() )
			{
				
								
				pair <CMainFrame::g_mmEQ_I_K_K::iterator, CMainFrame::g_mmEQ_I_K_K::iterator>  piKK;
				piKK = pMainFrame->gmmEQ_I_K_K.equal_range(str);

				for(it_iKK = piKK.first; it_iKK != piKK.second; ++it_iKK)
				{	
					if( a != it_iKK->second )
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iKK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iKK->second));
				}
			}
					
		
		
		//// Identifier - Empty - Empty ( K_AT_VL )////
			
			CMainFrame::g_mmEQ_K_A_V::iterator it_Kav;
			if( !pMainFrame->gmmEQ_K_A_V.empty() )
			{
				pair <CMainFrame::g_mmEQ_K_A_V::iterator, CMainFrame::g_mmEQ_K_A_V::iterator>  pKav;
				pKav = pMainFrame->gmmEQ_K_A_V.equal_range(strId);

				for(it_Kav = pKav.first; it_Kav != pKav.second; ++it_Kav)
				{	
					if( a != it_Kav->second )
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_Kav->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_Kav->second));
				}
			}
			
		
		//// Identifier - Empty - Value (K_AT_K )////
			
			
			CMainFrame::g_mmEQ_K_A_K::iterator it_KaK;
			str = strId + strVal;
			if ( !pMainFrame->gmmEQ_K_A_K.empty() )
			{
				pair <CMainFrame::g_mmEQ_K_A_K::iterator, CMainFrame::g_mmEQ_K_A_K::iterator>  pKaK;
				pKaK = pMainFrame->gmmEQ_K_A_K.equal_range(str);

				for(it_KaK = pKaK.first; it_KaK != pKaK.second; ++it_KaK)
				{	
					if( a != it_KaK->second )
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KaK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_KaK->second));
				}
			}
			

		//// Identifier - Attribute - Empty ( K_K_VL )////
			
			CMainFrame::g_mmEQ_K_K_V::iterator it_KKv;
			str = strId + strAttr;
			if( !pMainFrame->gmmEQ_K_K_V.empty() )
			{
				pair <CMainFrame::g_mmEQ_K_K_V::iterator, CMainFrame::g_mmEQ_K_K_V::iterator>  pKKv;
				pKKv = pMainFrame->gmmEQ_K_K_V.equal_range(str);

				for(it_KKv = pKKv.first; it_KKv != pKKv.second; ++it_KKv)
				{	
					if( a != it_KKv->second )
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KKv->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_KKv->second));
				}
			}
			

		//// Identifier - Attribute - Value ( K_K_K )////
			
			CMainFrame::g_mmEQ_K_K_K::iterator it_KKK;
			str = strId + strAttr + strVal;
			if( !pMainFrame->gmmEQ_K_K_K.empty() )
			{
				pair <CMainFrame::g_mmEQ_K_K_K::iterator, CMainFrame::g_mmEQ_K_K_K::iterator>  pKKK;
				pKKK = pMainFrame->gmmEQ_K_K_K.equal_range(str);

				for(it_KKK = pKKK.first; it_KKK != pKKK.second; ++it_KKK)
				{	
					if( a != it_KKK->second )
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KKK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_KKK->second));
				}
			}
			
		
		//// Empty - Empty - Empty ( ID_AT_VL )////
			
			CMainFrame::g_mmEQ_I_A_V::iterator it_iav;
		
			if ( !pMainFrame->gmmEQ_I_A_V.empty())
			{
				pair <CMainFrame::g_mmEQ_I_A_V::iterator, CMainFrame::g_mmEQ_I_A_V::iterator>  piav;
				piav = pMainFrame->gmmEQ_I_A_V.equal_range(_T("e"));

				for(it_iav = piav.first; it_iav != piav.second; ++it_iav)
				{	
					if( a != it_iav->second )
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iav->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iav->second));
				}
			}
			

		
	}



}

*/

/*
void CAipi_RETE_AM::insertAllWM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_WM wmo;
		
	
	for( CMainFrame::g_mWM::const_iterator it = pMainFrame->gmWM.begin(); it != pMainFrame->gmWM.end(); ++it)
	{
				
			
		wmo.findWMMembers(it->first);
		
		//// *** EQUALITY TEST **** //// 
		
		//// Empty - Empty - Value  ( ID_AT_K ) ////
		
			CMainFrame::g_mmEQ_I_A_K::iterator iteq_iaK;
			if( !pMainFrame->gmmEQ_I_A_K.empty())
			{
			
				pair <CMainFrame::g_mmEQ_I_A_K::iterator, CMainFrame::g_mmEQ_I_A_K::iterator>  peq_iaK;
				peq_iaK = pMainFrame->gmmEQ_I_A_K.equal_range(wmo.m_Val);

				for(iteq_iaK = peq_iaK.first; iteq_iaK != peq_iaK.second; ++iteq_iaK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_iaK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_iaK->second));
				}
				
			}

			
		
		//// Empty - Attribute - Empty ( ID_K_VL ) ////
			
			CMainFrame::g_mmEQ_I_K_V::iterator iteq_iKv;
			if( !pMainFrame->gmmEQ_I_K_V.empty() )
			{
				pair <CMainFrame::g_mmEQ_I_K_V::iterator, CMainFrame::g_mmEQ_I_K_V::iterator>  peq_iKv;
				peq_iKv = pMainFrame->gmmEQ_I_K_V.equal_range(wmo.m_Attr);

				for(iteq_iKv = peq_iKv.first; iteq_iKv != peq_iKv.second; ++iteq_iKv)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_iKv->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_iKv->second));
				}
				
			}
			
		
		//// Empty - Attribute - Value ( ID_K_K ) ////
			
			CMainFrame::g_mmEQ_I_K_K::iterator iteq_iKK;
			if( !pMainFrame->gmmEQ_I_K_K.empty() )
			{
				tstring str = wmo.m_Attr + wmo.m_Val;

				pair <CMainFrame::g_mmEQ_I_K_K::iterator, CMainFrame::g_mmEQ_I_K_K::iterator>  peq_iKK;
				peq_iKK = pMainFrame->gmmEQ_I_K_K.equal_range(str);

				for(iteq_iKK = peq_iKK.first; iteq_iKK != peq_iKK.second; ++iteq_iKK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_iKK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_iKK->second));
				}
			}
					
		
		
		//// Identifier - Empty - Empty ( K_AT_VL )////
			
			CMainFrame::g_mmEQ_K_A_V::iterator iteq_Kav;
			if( !pMainFrame->gmmEQ_K_A_V.empty() )
			{
				pair <CMainFrame::g_mmEQ_K_A_V::iterator, CMainFrame::g_mmEQ_K_A_V::iterator>  peq_Kav;
				peq_Kav = pMainFrame->gmmEQ_K_A_V.equal_range(wmo.m_Id);

				for(iteq_Kav = peq_Kav.first; iteq_Kav != peq_Kav.second; ++iteq_Kav)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_Kav->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_Kav->second));
				}
				
			}
			
		
		//// Identifier - Empty - Value (K_AT_K )////
			
			
			CMainFrame::g_mmEQ_K_A_K::iterator iteq_KaK;
			if ( !pMainFrame->gmmEQ_K_A_K.empty() )
			{
				tstring str = wmo.m_Id + wmo.m_Val;
				
				pair <CMainFrame::g_mmEQ_K_A_K::iterator, CMainFrame::g_mmEQ_K_A_K::iterator>  peq_KaK;
				peq_KaK = pMainFrame->gmmEQ_K_A_K.equal_range(str);

				for(iteq_KaK = peq_KaK.first; iteq_KaK != peq_KaK.second; ++iteq_KaK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_KaK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_KaK->second));
				}
				
			}
			

		//// Identifier - Attribute - Empty ( K_K_VL )////
			
			CMainFrame::g_mmEQ_K_K_V::iterator iteq_KKv;
			if( !pMainFrame->gmmEQ_K_K_V.empty() )
			{
				tstring str = wmo.m_Id + wmo.m_Attr;
				
				pair <CMainFrame::g_mmEQ_K_K_V::iterator, CMainFrame::g_mmEQ_K_K_V::iterator>  peq_KKv;
				peq_KKv = pMainFrame->gmmEQ_K_K_V.equal_range(str);

				for(iteq_KKv = peq_KKv.first; iteq_KKv != peq_KKv.second; ++iteq_KKv)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_KKv->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_KKv->second));
				}
				
			}
			

		//// Identifier - Attribute - Value ( K_K_K )////
			
			CMainFrame::g_mmEQ_K_K_K::iterator iteq_KKK;
			if( !pMainFrame->gmmEQ_K_K_K.empty() )
			{
				tstring str = wmo.m_Id + wmo.m_Attr + wmo.m_Val;
				
				pair <CMainFrame::g_mmEQ_K_K_K::iterator, CMainFrame::g_mmEQ_K_K_K::iterator>  peq_KKK;
				peq_KKK = pMainFrame->gmmEQ_K_K_K.equal_range(str);

				for(iteq_KKK = peq_KKK.first; iteq_KKK != peq_KKK.second; ++iteq_KKK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_KKK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_KKK->second));
				}
				
			}
			
		
		//// Empty - Empty - Empty ( ID_AT_VL )////
			
			CMainFrame::g_mmEQ_I_A_V::iterator iteq_iav;
			if ( !pMainFrame->gmmEQ_I_A_V.empty())
			{
				pair <CMainFrame::g_mmEQ_I_A_V::iterator, CMainFrame::g_mmEQ_I_A_V::iterator>  peq_iav;
				peq_iav = pMainFrame->gmmEQ_I_A_V.equal_range(_T("e"));

				for(iteq_iav = peq_iav.first; iteq_iav != peq_iav.second; ++iteq_iav)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_iav->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_iav->second));
				}
				
			}
			
			
			//// *** NO EQUALITY TEST **** //// 
		
		//// Empty - Empty - Value  ( ID_AT_K )////
		
			CMainFrame::g_mmNE_I_A_K::iterator it_iaK;
			if( !pMainFrame->gmmNE_I_A_K.empty())
			{
			
				pair <CMainFrame::g_mmNE_I_A_K::iterator, CMainFrame::g_mmEQ_I_A_K::iterator>  piaK;
				piaK = pMainFrame->gmmNE_I_A_K.equal_range(wmo.m_Val);

				for(it_iaK = piaK.first; it_iaK != piaK.second; ++it_iaK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iaK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iaK->second));
				}
				
			}

			
		
		//// Empty - Attribute - Empty ( ID_K_VL )////
			
			CMainFrame::g_mmNE_I_K_V::iterator it_iKv;
			if( !pMainFrame->gmmNE_I_K_V.empty() )
			{
				pair <CMainFrame::g_mmNE_I_K_V::iterator, CMainFrame::g_mmEQ_I_K_V::iterator>  piKv;
				piKv = pMainFrame->gmmNE_I_K_V.equal_range(wmo.m_Attr);

				for(it_iKv = piKv.first; it_iKv != piKv.second; ++it_iKv)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iKv->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iKv->second));
				}
				
			}
			
		
		//// Empty - Attribute - Value ( ID_K_K )////
			
			CMainFrame::g_mmNE_I_K_K::iterator it_iKK;
			if( !pMainFrame->gmmNE_I_K_K.empty() )
			{
				tstring str = wmo.m_Attr + wmo.m_Val;

				pair <CMainFrame::g_mmNE_I_K_K::iterator, CMainFrame::g_mmEQ_I_K_K::iterator>  piKK;
				piKK = pMainFrame->gmmNE_I_K_K.equal_range(str);

				for(it_iKK = piKK.first; it_iKK != piKK.second; ++it_iKK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iKK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iKK->second));
				}
			}
					
		
		
		//// Identifier - Empty - Empty ( K_AT_VL )////
			
			CMainFrame::g_mmNE_K_A_V::iterator it_Kav;
			if( !pMainFrame->gmmNE_K_A_V.empty() )
			{
				pair <CMainFrame::g_mmNE_K_A_V::iterator, CMainFrame::g_mmEQ_K_A_V::iterator>  pKav;
				pKav = pMainFrame->gmmNE_K_A_V.equal_range(wmo.m_Id);

				for(it_Kav = pKav.first; it_Kav != pKav.second; ++it_Kav)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_Kav->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_Kav->second));
				}
				
			}
			
		
		//// Identifier - Empty - Value (K_AT_K )////
			
			
			CMainFrame::g_mmEQ_K_A_K::iterator it_KaK;
			if ( !pMainFrame->gmmEQ_K_A_K.empty() )
			{
				tstring str = wmo.m_Id + wmo.m_Val;
				
				pair <CMainFrame::g_mmNE_K_A_K::iterator, CMainFrame::g_mmEQ_K_A_K::iterator>  pKaK;
				pKaK = pMainFrame->gmmNE_K_A_K.equal_range(str);

				for(it_KaK = pKaK.first; it_KaK != pKaK.second; ++it_KaK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KaK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_KaK->second));
				}
				
			}
			

		//// Identifier - Attribute - Empty ( K_K_VL )////
			
			CMainFrame::g_mmNE_K_K_V::iterator it_KKv;
			if( !pMainFrame->gmmNE_K_K_V.empty() )
			{
				tstring str = wmo.m_Id + wmo.m_Attr;
				
				pair <CMainFrame::g_mmNE_K_K_V::iterator, CMainFrame::g_mmEQ_K_K_V::iterator>  pKKv;
				pKKv = pMainFrame->gmmNE_K_K_V.equal_range(str);

				for(it_KKv = pKKv.first; it_KKv != pKKv.second; ++it_KKv)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KKv->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_KKv->second));
				}
				
			}
			

		//// Identifier - Attribute - Value ( K_K_K )////
			
			CMainFrame::g_mmNE_K_K_K::iterator it_KKK;
			if( !pMainFrame->gmmNE_K_K_K.empty() )
			{
				tstring str = wmo.m_Id + wmo.m_Attr + wmo.m_Val;
				
				pair <CMainFrame::g_mmNE_K_K_K::iterator, CMainFrame::g_mmEQ_K_K_K::iterator>  pKKK;
				pKKK = pMainFrame->gmmNE_K_K_K.equal_range(str);

				for(it_KKK = pKKK.first; it_KKK != pKKK.second; ++it_KKK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KKK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_KKK->second));
				}
				
			}
			
		
		//// Empty - Empty - Empty ( ID_AT_VL )////
			
			CMainFrame::g_mmNE_I_A_V::iterator it_iav;
			if ( !pMainFrame->gmmNE_I_A_V.empty())
			{
				pair <CMainFrame::g_mmNE_I_A_V::iterator, CMainFrame::g_mmEQ_I_A_V::iterator>  piav;
				piav = pMainFrame->gmmNE_I_A_V.equal_range(_T("e"));

				for(it_iav = piav.first; it_iav != piav.second; ++it_iav)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iav->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iav->second));
				}
				
			}
			
	
			







	}



}

*/



void CAipi_RETE_AM::insertAllWM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_WM wmo;
		
	
	for( CMainFrame::g_mWM::const_iterator it = pMainFrame->gmWM.begin(); it != pMainFrame->gmWM.end(); ++it)
	{
				
		wmo = (CAipi_WM)it->second;
 	
		m_Id = wmo.getId();
		m_Attr = wmo.getAttr();
		m_Val = wmo.getVal();
		
				
		//// *** EQUALITY TEST **** //// 
		
		//// Empty - Empty - Value  ( ID_AT_K ) ////
		
			CMainFrame::g_mmEQ_I_A_K::iterator iteq_iaK;
			if( !pMainFrame->gmmEQ_I_A_K.empty())
			{
			
				pair <CMainFrame::g_mmEQ_I_A_K::iterator, CMainFrame::g_mmEQ_I_A_K::iterator>  peq_iaK;
				peq_iaK = pMainFrame->gmmEQ_I_A_K.equal_range(m_Val);

				for(iteq_iaK = peq_iaK.first; iteq_iaK != peq_iaK.second; ++iteq_iaK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_iaK->second , it->first));
					//pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_iaK->second));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_iaK->second));
				}
				
			}

			
		
		//// Empty - Attribute - Empty ( ID_K_VL ) ////
			
			CMainFrame::g_mmEQ_I_K_V::iterator iteq_iKv;
			if( !pMainFrame->gmmEQ_I_K_V.empty() )
			{
				pair <CMainFrame::g_mmEQ_I_K_V::iterator, CMainFrame::g_mmEQ_I_K_V::iterator>  peq_iKv;
				peq_iKv = pMainFrame->gmmEQ_I_K_V.equal_range(m_Attr);

				for(iteq_iKv = peq_iKv.first; iteq_iKv != peq_iKv.second; ++iteq_iKv)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_iKv->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_iKv->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, iteq_iKv->second));
				}
				
			}
			
		
		//// Empty - Attribute - Value ( ID_K_K ) ////
			
			CMainFrame::g_mmEQ_I_K_K::iterator iteq_iKK;
			if( !pMainFrame->gmmEQ_I_K_K.empty() )
			{
				tstring str = m_Attr + m_Val;

				pair <CMainFrame::g_mmEQ_I_K_K::iterator, CMainFrame::g_mmEQ_I_K_K::iterator>  peq_iKK;
				peq_iKK = pMainFrame->gmmEQ_I_K_K.equal_range(str);

				for(iteq_iKK = peq_iKK.first; iteq_iKK != peq_iKK.second; ++iteq_iKK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_iKK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_iKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, iteq_iKK->second));
				}
			}
					
		
		
		//// Identifier - Empty - Empty ( K_AT_VL )////
			
			CMainFrame::g_mmEQ_K_A_V::iterator iteq_Kav;
			if( !pMainFrame->gmmEQ_K_A_V.empty() )
			{
				pair <CMainFrame::g_mmEQ_K_A_V::iterator, CMainFrame::g_mmEQ_K_A_V::iterator>  peq_Kav;
				peq_Kav = pMainFrame->gmmEQ_K_A_V.equal_range(m_Id);

				for(iteq_Kav = peq_Kav.first; iteq_Kav != peq_Kav.second; ++iteq_Kav)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_Kav->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_Kav->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, iteq_Kav->second));
				}
				
			}
			
		
		//// Identifier - Empty - Value (K_AT_K )////
			
			
			CMainFrame::g_mmEQ_K_A_K::iterator iteq_KaK;
			if ( !pMainFrame->gmmEQ_K_A_K.empty() )
			{
				tstring str = m_Id + m_Val;
				
				pair <CMainFrame::g_mmEQ_K_A_K::iterator, CMainFrame::g_mmEQ_K_A_K::iterator>  peq_KaK;
				peq_KaK = pMainFrame->gmmEQ_K_A_K.equal_range(str);

				for(iteq_KaK = peq_KaK.first; iteq_KaK != peq_KaK.second; ++iteq_KaK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_KaK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_KaK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, iteq_KaK->second));
				}
				
			}
			

		//// Identifier - Attribute - Empty ( K_K_VL )////
			
			CMainFrame::g_mmEQ_K_K_V::iterator iteq_KKv;
			if( !pMainFrame->gmmEQ_K_K_V.empty() )
			{
				tstring str = m_Id + m_Attr;
				
				pair <CMainFrame::g_mmEQ_K_K_V::iterator, CMainFrame::g_mmEQ_K_K_V::iterator>  peq_KKv;
				peq_KKv = pMainFrame->gmmEQ_K_K_V.equal_range(str);

				for(iteq_KKv = peq_KKv.first; iteq_KKv != peq_KKv.second; ++iteq_KKv)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_KKv->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_KKv->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, iteq_KKv->second));
				}
				
			}
			

		//// Identifier - Attribute - Value ( K_K_K )////
			
			CMainFrame::g_mmEQ_K_K_K::iterator iteq_KKK;
			if( !pMainFrame->gmmEQ_K_K_K.empty() )
			{
				tstring str = m_Id + m_Attr + m_Val;
				
				pair <CMainFrame::g_mmEQ_K_K_K::iterator, CMainFrame::g_mmEQ_K_K_K::iterator>  peq_KKK;
				peq_KKK = pMainFrame->gmmEQ_K_K_K.equal_range(str);

				for(iteq_KKK = peq_KKK.first; iteq_KKK != peq_KKK.second; ++iteq_KKK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_KKK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_KKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, iteq_KKK->second));
				}
				
			}
			
		
		//// Empty - Empty - Empty ( ID_AT_VL )////
			
			CMainFrame::g_mmEQ_I_A_V::iterator iteq_iav;
			if ( !pMainFrame->gmmEQ_I_A_V.empty())
			{
				pair <CMainFrame::g_mmEQ_I_A_V::iterator, CMainFrame::g_mmEQ_I_A_V::iterator>  peq_iav;
				peq_iav = pMainFrame->gmmEQ_I_A_V.equal_range(_T("e"));

				for(iteq_iav = peq_iav.first; iteq_iav != peq_iav.second; ++iteq_iav)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_iav->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, iteq_iav->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, iteq_iav->second));
				}
				
			}
			
			
			//// *** NO EQUALITY TEST **** //// 
		
		//// Empty - Empty - Value  ( ID_AT_K )////
		
			CMainFrame::g_mmNE_I_A_K::iterator it_iaK;
			if( !pMainFrame->gmmNE_I_A_K.empty())
			{
			
				pair <CMainFrame::g_mmNE_I_A_K::iterator, CMainFrame::g_mmEQ_I_A_K::iterator>  piaK;
				piaK = pMainFrame->gmmNE_I_A_K.equal_range(wmo.m_Val);

				for(it_iaK = piaK.first; it_iaK != piaK.second; ++it_iaK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iaK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iaK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, it_iaK->second));
				}
				
			}

			
		
		//// Empty - Attribute - Empty ( ID_K_VL )////
			
			CMainFrame::g_mmNE_I_K_V::iterator it_iKv;
			if( !pMainFrame->gmmNE_I_K_V.empty() )
			{
				pair <CMainFrame::g_mmNE_I_K_V::iterator, CMainFrame::g_mmEQ_I_K_V::iterator>  piKv;
				piKv = pMainFrame->gmmNE_I_K_V.equal_range(wmo.m_Attr);

				for(it_iKv = piKv.first; it_iKv != piKv.second; ++it_iKv)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iKv->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iKv->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, it_iKv->second));
				}
				
			}
			
		
		//// Empty - Attribute - Value ( ID_K_K )////
			
			CMainFrame::g_mmNE_I_K_K::iterator it_iKK;
			if( !pMainFrame->gmmNE_I_K_K.empty() )
			{
				tstring str = wmo.m_Attr + wmo.m_Val;

				pair <CMainFrame::g_mmNE_I_K_K::iterator, CMainFrame::g_mmEQ_I_K_K::iterator>  piKK;
				piKK = pMainFrame->gmmNE_I_K_K.equal_range(str);

				for(it_iKK = piKK.first; it_iKK != piKK.second; ++it_iKK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iKK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, it_iKK->second));
				}
			}
					
		
		
		//// Identifier - Empty - Empty ( K_AT_VL )////
			
			CMainFrame::g_mmNE_K_A_V::iterator it_Kav;
			if( !pMainFrame->gmmNE_K_A_V.empty() )
			{
				pair <CMainFrame::g_mmNE_K_A_V::iterator, CMainFrame::g_mmEQ_K_A_V::iterator>  pKav;
				pKav = pMainFrame->gmmNE_K_A_V.equal_range(wmo.m_Id);

				for(it_Kav = pKav.first; it_Kav != pKav.second; ++it_Kav)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_Kav->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_Kav->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, it_Kav->second));
				}
				
			}
			
		
		//// Identifier - Empty - Value (K_AT_K )////
			
			
			CMainFrame::g_mmEQ_K_A_K::iterator it_KaK;
			if ( !pMainFrame->gmmEQ_K_A_K.empty() )
			{
				tstring str = wmo.m_Id + wmo.m_Val;
				
				pair <CMainFrame::g_mmNE_K_A_K::iterator, CMainFrame::g_mmEQ_K_A_K::iterator>  pKaK;
				pKaK = pMainFrame->gmmNE_K_A_K.equal_range(str);

				for(it_KaK = pKaK.first; it_KaK != pKaK.second; ++it_KaK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KaK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_KaK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, it_KaK->second));
				}
				
			}
			

		//// Identifier - Attribute - Empty ( K_K_VL )////
			
			CMainFrame::g_mmNE_K_K_V::iterator it_KKv;
			if( !pMainFrame->gmmNE_K_K_V.empty() )
			{
				tstring str = wmo.m_Id + wmo.m_Attr;
				
				pair <CMainFrame::g_mmNE_K_K_V::iterator, CMainFrame::g_mmEQ_K_K_V::iterator>  pKKv;
				pKKv = pMainFrame->gmmNE_K_K_V.equal_range(str);

				for(it_KKv = pKKv.first; it_KKv != pKKv.second; ++it_KKv)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KKv->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_KKv->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, it_KKv->second));
				}
				
			}
			

		//// Identifier - Attribute - Value ( K_K_K )////
			
			CMainFrame::g_mmNE_K_K_K::iterator it_KKK;
			if( !pMainFrame->gmmNE_K_K_K.empty() )
			{
				tstring str = wmo.m_Id + wmo.m_Attr + wmo.m_Val;
				
				pair <CMainFrame::g_mmNE_K_K_K::iterator, CMainFrame::g_mmEQ_K_K_K::iterator>  pKKK;
				pKKK = pMainFrame->gmmNE_K_K_K.equal_range(str);

				for(it_KKK = pKKK.first; it_KKK != pKKK.second; ++it_KKK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KKK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_KKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, it_KKK->second));
				}
				
			}
			
		
		//// Empty - Empty - Empty ( ID_AT_VL )////
			
			CMainFrame::g_mmNE_I_A_V::iterator it_iav;
			if ( !pMainFrame->gmmNE_I_A_V.empty())
			{
				pair <CMainFrame::g_mmNE_I_A_V::iterator, CMainFrame::g_mmEQ_I_A_V::iterator>  piav;
				piav = pMainFrame->gmmNE_I_A_V.equal_range(_T("e"));

				for(it_iav = piav.first; it_iav != piav.second; ++it_iav)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iav->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iav->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(it->first, it_iav->second));
				}
				
			}
			

	}



}


int CAipi_RETE_AM::updateStructsWM_AM(int w)
{
		
		CAipi_WM wmo;
		int ame = UNDEFINE;

		int f = wmo.findWMMembersIForm(w);
		if( f != NOT_FOUND )
		{
			tstring id		= wmo.getId();
			tstring attr	= wmo.getAttr();
			tstring val		= wmo.getVal();
		
			ame = insertEQ(w, id, attr, val );
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




void CAipi_RETE_AM::insertStructsWM_AM()
{

	//AfxMessageBox(_T("AM   ...  INSERT STRUCTS"));

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_WM wmo;
		
	
	for( CMainFrame::g_mWM::const_iterator it = pMainFrame->gmWM.begin(); it != pMainFrame->gmWM.end(); ++it)
	{
				
		wmo = (CAipi_WM)it->second;
		
	 	
		tstring id		= wmo.getId();
		tstring attr	= wmo.getAttr();
		tstring val		= wmo.getVal();
		
		int w			= it->first;
		
		/*
		CString str;
		str.Format(_T("WM...%d  " ), w);
		AfxMessageBox(str);
		*/

		//AfxMessageBox(id.c_str());
		//AfxMessageBox(attr.c_str());
		//AfxMessageBox(val.c_str());
			

		insertEQ(w, id, attr, val );
		insertET(w, id, attr, val );
		insertNE(w, id, attr, val );
		insertLT(w, id, attr, val );
		insertLE(w, id, attr, val );
		insertGT(w, id, attr, val );
		insertGE(w, id, attr, val );
		insertAS(w, id, attr, val );
	}

	CAipi_RETE_AM amo;
	amo.printAM_WM();
	amo.printEQ();
	amo.printET();
	amo.printNE();
	amo.printLT();
	amo.printLE();
	amo.printGT();
	amo.printGE();
	amo.printAS();


}



int CAipi_RETE_AM::insertEQ(int wm, tstring id, tstring attr, tstring val)
{

//// *** EQUALITY TEST **** //// 
	int ame = UNDEFINE;
		
	//// Empty - Empty - Value  ( ID_AT_K ) ////
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	CMainFrame::g_mmEQ_I_A_K::iterator iteq_iaK;
	if( !pMainFrame->gmmEQ_I_A_K.empty())
	{
			
		pair <CMainFrame::g_mmEQ_I_A_K::iterator, CMainFrame::g_mmEQ_I_A_K::iterator>  peq_iaK;
		peq_iaK = pMainFrame->gmmEQ_I_A_K.equal_range(val);

		for(iteq_iaK = peq_iaK.first; iteq_iaK != peq_iaK.second; ++iteq_iaK)
		{	
			
			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_iaK->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, iteq_iaK->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, iteq_iaK->second));
			ame = iteq_iaK->second;
				
		}
				
	}

			
		
	//// Empty - Attribute - Empty ( ID_K_VL ) ////
			
	CMainFrame::g_mmEQ_I_K_V::iterator iteq_iKv;
	if( !pMainFrame->gmmEQ_I_K_V.empty() )
	{
		pair <CMainFrame::g_mmEQ_I_K_V::iterator, CMainFrame::g_mmEQ_I_K_V::iterator>  peq_iKv;
		peq_iKv = pMainFrame->gmmEQ_I_K_V.equal_range(attr);

		for(iteq_iKv = peq_iKv.first; iteq_iKv != peq_iKv.second; ++iteq_iKv)
		{	
			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_iKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, iteq_iKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, iteq_iKv->second));
			ame = iteq_iKv->second;
		}
			
	}
			
		
	//// Empty - Attribute - Value ( ID_K_K ) ////
			
	CMainFrame::g_mmEQ_I_K_K::iterator iteq_iKK;
	if( !pMainFrame->gmmEQ_I_K_K.empty() )
	{
		tstring str = attr + _T("|") + val;

		pair <CMainFrame::g_mmEQ_I_K_K::iterator, CMainFrame::g_mmEQ_I_K_K::iterator>  peq_iKK;
		peq_iKK = pMainFrame->gmmEQ_I_K_K.equal_range(str);

		for(iteq_iKK = peq_iKK.first; iteq_iKK != peq_iKK.second; ++iteq_iKK)
		{	
			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_iKK->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, iteq_iKK->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, iteq_iKK->second));
			ame = iteq_iKK->second;
		}
	}
					
		
	//// Identifier - Empty - Empty ( K_AT_VL )////
			
	CMainFrame::g_mmEQ_K_A_V::iterator iteq_Kav;
	if( !pMainFrame->gmmEQ_K_A_V.empty() )
	{
		pair <CMainFrame::g_mmEQ_K_A_V::iterator, CMainFrame::g_mmEQ_K_A_V::iterator>  peq_Kav;
		peq_Kav = pMainFrame->gmmEQ_K_A_V.equal_range(id);

		for(iteq_Kav = peq_Kav.first; iteq_Kav != peq_Kav.second; ++iteq_Kav)
		{	
			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_Kav->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, iteq_Kav->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, iteq_Kav->second));
			ame = iteq_Kav->second;
		}
				
	}
			
		
	//// Identifier - Empty - Value (K_AT_K )////
			
			
	CMainFrame::g_mmEQ_K_A_K::iterator iteq_KaK;
	if ( !pMainFrame->gmmEQ_K_A_K.empty() )
	{
		tstring str = id + _T("|") + val;
				
		pair <CMainFrame::g_mmEQ_K_A_K::iterator, CMainFrame::g_mmEQ_K_A_K::iterator>  peq_KaK;
		peq_KaK = pMainFrame->gmmEQ_K_A_K.equal_range(str);

		for(iteq_KaK = peq_KaK.first; iteq_KaK != peq_KaK.second; ++iteq_KaK)
		{	
			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_KaK->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, iteq_KaK->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, iteq_KaK->second));
			ame = iteq_KaK->second;
		}
				
	}
			

	//// Identifier - Attribute - Empty ( K_K_VL )////
			
	CMainFrame::g_mmEQ_K_K_V::iterator iteq_KKv;
	if( !pMainFrame->gmmEQ_K_K_V.empty() )
	{
		tstring str = id + _T("|") + attr;
				
		pair <CMainFrame::g_mmEQ_K_K_V::iterator, CMainFrame::g_mmEQ_K_K_V::iterator>  peq_KKv;
		peq_KKv = pMainFrame->gmmEQ_K_K_V.equal_range(str);

		for(iteq_KKv = peq_KKv.first; iteq_KKv != peq_KKv.second; ++iteq_KKv)
		{	
			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_KKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, iteq_KKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, iteq_KKv->second));
			ame = iteq_KKv->second;
		}
		
	}
			

	//// Identifier - Attribute - Value ( K_K_K )////
			
	CMainFrame::g_mmEQ_K_K_K::iterator iteq_KKK;
	if( !pMainFrame->gmmEQ_K_K_K.empty() )
	{
		//AfxMessageBox(_T("Insert EQ"));
		
		tstring str = id + _T("|") + attr + _T("|") + val;
		/*
		AfxMessageBox(_T("Entro"));
		AfxMessageBox(str.data());
		*/
		
		pair <CMainFrame::g_mmEQ_K_K_K::iterator, CMainFrame::g_mmEQ_K_K_K::iterator>  peq_KKK;
		peq_KKK = pMainFrame->gmmEQ_K_K_K.equal_range(str);

		for(iteq_KKK = peq_KKK.first; iteq_KKK != peq_KKK.second; ++iteq_KKK)
		{	
			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_KKK->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, iteq_KKK->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, iteq_KKK->second));
			ame = iteq_KKK->second;
			/*
			CString str;
			str.Format(_T("Inserto WM...%d  " ), wm);
			AfxMessageBox(str);
			
			str.Format(_T("Inserto AM...%d  " ), ame);
			AfxMessageBox(str);
			*/
		}
				
	}
			
		
	//// Empty - Empty - Empty ( ID_AT_VL )////
			
	CMainFrame::g_mmEQ_I_A_V::iterator iteq_iav;
	if ( !pMainFrame->gmmEQ_I_A_V.empty())
	{
		pair <CMainFrame::g_mmEQ_I_A_V::iterator, CMainFrame::g_mmEQ_I_A_V::iterator>  peq_iav;
		peq_iav = pMainFrame->gmmEQ_I_A_V.equal_range(_T("e"));

		for(iteq_iav = peq_iav.first; iteq_iav != peq_iav.second; ++iteq_iav)
		{	
			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(iteq_iav->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, iteq_iav->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, iteq_iav->second));
			ame = iteq_iav->second;
		}
			
	}
		
	/*
	CString str;
	str.Format(_T("Updated AM...%d  " ), ame);
	AfxMessageBox(str);
	*/
return ame;
}

int CAipi_RETE_AM::insertET(int wm, tstring id, tstring attr, tstring val)
{
	///NUMERIC OPERATIONS////

//// *** EQUALITY THAN TEST **** //// 
	int ame = UNDEFINE;
		
	//// Empty - Empty - Value  ( ID_AT_K ) ////
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	if( !pMainFrame->gmmET_I_A_K.empty())
	{
		//int iVal	= UNDEFINE;
		double dVal = UNDEFINE;
		
		CMainFrame::g_mmET_I_A_K::iterator itet_iaK;
		
		for(itet_iaK = pMainFrame->gmmET_I_A_K.begin(); itet_iaK != pMainFrame->gmmET_I_A_K.end(); ++itet_iaK)
		{	
			tstring key = itet_iaK->first;
			/*
			AfxMessageBox(_T("Key"));
			AfxMessageBox(key.data());
			*/
			
			if( isNumber( val) == true )
			{
				
				//iVal = _ttoi(val.data());
				dVal = _tcstod(val.data(), NULL);
			}
			else
			{
				continue;
			}

			//int ET_iVal = _ttoi(key.data());
			double ET_dVal = _tcstod(key.data(), NULL);
			/*
			TCHAR buff[8];
			CString sET_Val = _itot(ET_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sET_Val :"));
			AfxMessageBox(sET_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			//if( iVal == ET_Val )
			if( dVal == ET_dVal )
			{	
				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itet_iaK->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itet_iaK->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itet_iaK->second));
				ame = itet_iaK->second;
			}
		}

				
	}

			
		
	//// Empty - Attribute - Empty ( ID_K_VL ) ////
			
	if( !pMainFrame->gmmET_I_K_V.empty() )
	{
		
		
		CMainFrame::g_mmET_I_K_V::iterator itet_iKv;
		
		for(itet_iKv = pMainFrame->gmmET_I_K_V.begin(); itet_iKv != pMainFrame->gmmET_I_K_V.end(); ++itet_iKv)
		{	
			tstring key = itet_iKv->first;
			
			if( key != attr )
			{
				continue;
				
			}
			
			/*
			TCHAR buff[8];
			CString sET_Val = _itot(ET_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sET_Val :"));
			AfxMessageBox(sET_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itet_iKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itet_iKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itet_iKv->second));
			ame = itet_iKv->second;
			
		}
		
			
	}
			
		
	//// Empty - Attribute - Value ( ID_K_K ) ////
			
	if( !pMainFrame->gmmET_I_K_K.empty() )
	{
		//tstring str = attr + val;
		int iVal = UNDEFINE;
		double dVal = UNDEFINE;
		
		CMainFrame::g_mmET_I_K_K::iterator itet_iKK;

		/*
		AfxMessageBox(_T("iVAL"));
		AfxMessageBox(val.data());
		*/
		
		for(itet_iKK = pMainFrame->gmmET_I_K_K.begin(); itet_iKK != pMainFrame->gmmET_I_K_K.end(); ++itet_iKK)
		{	
			tstring key = itet_iKK->first;
			int pos = key.find_first_of(_T("|"));
			
			if( key.substr(0, pos) == attr )
			{
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
			
				
				tstring sVal = key.substr(pos + 1, key.length());
				//int ET_Val = _ttoi(sVal.data());
				double ET_dVal = _tcstod(sVal.data(), NULL);
						
		
				/*
				
				TCHAR buff[8];
				CString sET_Val = _itot(ET_iVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sET_Val :"));
				AfxMessageBox(sET_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal == ET_Val )
				if( dVal == ET_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itet_iKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itet_iKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itet_iKK->second));
					ame = itet_iKK->second;
				}

			}
		}
		
	}
					
		
	//// Identifier - Empty - Empty ( K_AT_VL )////
			
	if( !pMainFrame->gmmET_K_A_V.empty() )
	{
		CMainFrame::g_mmET_K_A_V::iterator itet_Kav;

		for(itet_Kav = pMainFrame->gmmET_K_A_V.begin(); itet_Kav != pMainFrame->gmmET_K_A_V.end(); ++itet_Kav)
		{	
			tstring key = itet_Kav->first;
			if ( key != id )
			{
				continue;
			
			}
			else
			{
				if( isNumber(val) != true)
				{
					continue;
				}
				
			}
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itet_Kav->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itet_Kav->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itet_Kav->second));
				ame = itet_Kav->second;
			
		}
		
				
	}
			
		
	//// Identifier - Empty - Value (K_AT_K )////
			
			
	if ( !pMainFrame->gmmET_K_A_K.empty() )
	{
		//tstring str = id + val;
		//int iVal = _ttoi(val.data());
		double dVal = _tcstod(val.data(), NULL);

		CMainFrame::g_mmET_K_A_K::iterator itet_KaK;
		
		for(itet_KaK = pMainFrame->gmmET_K_A_K.begin(); itet_KaK != pMainFrame->gmmET_K_A_K.end(); ++itet_KaK)
		{	
			tstring key = itet_KaK->first;
			int pos = key.find_first_of(_T("|"));
			//AfxMessageBox(key.substr(0, pos).data());
			if( key.substr(0, pos) == id )
			{
			
				tstring key = itet_KaK->first;
				int pos = key.find_first_of(_T("|"));
				//AfxMessageBox(key.substr(0, pos).data());
				if( key.substr(0, pos) == id )
				{
					if( isNumber(val) == true)
					{
						//iVal = _ttoi(val.data());
						dVal = _tcstod(val.data(), NULL);
					}
					else
					{
						continue;
					}
				
					tstring sVal = key.substr(pos + 1, key.length());
					//int ET_iVal = _ttoi(sVal.data());
					double ET_dVal = _tcstod(sVal.data(), NULL);
			
				
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_dVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

					//if( iVal == ET_Val )
					if( dVal == ET_dVal )
					{	
						pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itet_KaK->second , wm));
						pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itet_KaK->second));
						//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itet_KaK->second));
						ame = itet_KaK->second;
					}
				}
			}	
		}
				
	}
			

	//// Identifier - Attribute - Empty ( K_K_VL )////
			
	if( !pMainFrame->gmmET_K_K_V.empty() )
	{
		//tstring str = id + attr;
		CMainFrame::g_mmET_K_K_V::iterator itet_KKv;
		
		for(itet_KKv = pMainFrame->gmmET_K_K_V.begin(); itet_KKv != pMainFrame->gmmET_K_K_V.end(); ++itet_KKv)
		{	
			
			tstring key = itet_KKv->first;
			int pos = key.find_first_of(_T("|"));
			tstring sId  =  key.substr(0, pos);
			tstring sAttr = key.substr(pos + 1, key.length());
			
			if( sAttr != attr || id != sId)
			{
				continue;
					
			}	
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itet_KKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itet_KKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itet_KKv->second));
			ame = itet_KKv->second;
		}	
		
		
	}
			

	//// Identifier - Attribute - Value ( K_K_K )////
			
	if( !pMainFrame->gmmET_K_K_K.empty() )
	{
		//tstring str = id + attr + m_Val;
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;

		CMainFrame::g_mmET_K_K_K::iterator itet_KKK;
		
		for(itet_KKK = pMainFrame->gmmET_K_K_K.begin(); itet_KKK != pMainFrame->gmmET_K_K_K.end(); ++itet_KKK)
		{	
			tstring key = itet_KKK->first;
			int pos1 = key.find_first_of(_T("|"));
			int pos2 = key.find_last_of(_T("|"));
			int aSize = pos2 - pos1 -1;

			tstring sId = key.substr(0, pos1);
			tstring sAttr = key.substr(pos1 + 1, aSize);
			tstring sVal = key.substr(pos2 + 1, key.length());
			
			/*
			AfxMessageBox(sId.data());
			AfxMessageBox(sAttr.data());
			AfxMessageBox(sVal.data());
			*/
			
			if( sId == id  && sAttr == attr )
			{
			
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				//int ET_iVal = _ttoi(sVal.data());
				double ET_dVal = _tcstod(sVal.data(), NULL);
				
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(ET_iVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal == ET_iVal )
				if( dVal == ET_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itet_KKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itet_KKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itet_KKK->second));
					ame = itet_KKK->second;
				}
			}
		}
				
	}
			
		
	//// Empty - Empty - Empty ( ID_AT_VL )////
			
	if ( !pMainFrame->gmmET_I_A_V.empty())
	{
		
		CMainFrame::g_mmET_I_A_V::iterator itet_IAV;
		
		for(itet_IAV = pMainFrame->gmmET_I_A_V.begin(); itet_IAV != pMainFrame->gmmET_I_A_V.end(); ++itet_IAV)
		{	
			if( isNumber(val) != true)
			{
				continue;
			}
			
			
			//AfxMessageBox(val.data());
			

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itet_IAV->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itet_IAV->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itet_IAV->second));
			ame = itet_IAV->second;
			
		}
			
	}
		

return ame;

}




int CAipi_RETE_AM::insertNE(int wm, tstring id, tstring attr, tstring val)
{

//// *** NON EQUALITY TEST **** //// 
	int ame = UNDEFINE;	
	//// Empty - Empty - Value  ( ID_AT_K ) ////
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	if( !pMainFrame->gmmNE_I_A_K.empty())
	{
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;
		
		CMainFrame::g_mmNE_I_A_K::iterator itne_iaK;
		
		for(itne_iaK = pMainFrame->gmmNE_I_A_K.begin(); itne_iaK != pMainFrame->gmmNE_I_A_K.end(); ++itne_iaK)
		{	
			tstring key = itne_iaK->first;
			/*
			AfxMessageBox(_T("Key"));
			AfxMessageBox(key.data());
			*/
			
			if( isNumber( val) == true )
			{
				
				//iVal = _ttoi(val.data());
				dVal = _tcstod(val.data(), NULL);
			}
			else
			{
				continue;
			}

			//int NE_iVal = _ttoi(key.data());
			double NE_dVal = _tcstod(key.data(), NULL); 
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			//if( iVal != NE_iVal )
			if( dVal != NE_dVal )
			{	
				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itne_iaK->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itne_iaK->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itne_iaK->second));
				ame = itne_iaK->second;
			}
		}
		
				
	}

			
		
	//// Empty - Attribute - Empty ( ID_K_VL ) ////
			
	if( !pMainFrame->gmmNE_I_K_V.empty() )
	{
		
		CMainFrame::g_mmNE_I_K_V::iterator itne_iKv;
		
		for(itne_iKv = pMainFrame->gmmNE_I_K_V.begin(); itne_iKv != pMainFrame->gmmNE_I_K_V.end(); ++itne_iKv)
		{	
			tstring key = itne_iKv->first;

			
			if( key != attr )
			{
				continue;
				
			}
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itne_iKv->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itne_iKv->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itne_iKv->second));
				ame = itne_iKv->second;
			
		}
		
			
	}
			
		
	//// Empty - Attribute - Value ( ID_K_K ) ////
			
	if( !pMainFrame->gmmNE_I_K_K.empty() )
	{
		//tstring str = attr + val;
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;
		
		CMainFrame::g_mmNE_I_K_K::iterator itne_iKK;

		/*
		AfxMessageBox(_T("iVAL"));
		AfxMessageBox(val.data());
		*/
		
		for(itne_iKK = pMainFrame->gmmNE_I_K_K.begin(); itne_iKK != pMainFrame->gmmNE_I_K_K.end(); ++itne_iKK)
		{	
			tstring key = itne_iKK->first;
			int pos = key.find_first_of(_T("|"));
			if( key.substr(0, pos) == attr )
			{
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				tstring sVal = key.substr(pos + 1, key.length());
				//int NE_Val = _ttoi(sVal.data());
				double NE_dVal = _tcstod(sVal.data(), NULL);
				
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_Val, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal != NE_iVal )
				if( dVal != NE_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itne_iKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itne_iKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itne_iKK->second));
					ame = itne_iKK->second;
				}

			}
		}
		
	}
					
		
	//// Identifier - Empty - Empty ( K_AT_VL )////
			
	if( !pMainFrame->gmmNE_K_A_V.empty() )
	{
		
		CMainFrame::g_mmNE_K_A_V::iterator itne_Kav;

		for(itne_Kav = pMainFrame->gmmNE_K_A_V.begin(); itne_Kav != pMainFrame->gmmNE_K_A_V.end(); ++itne_Kav)
		{	
			tstring key = itne_Kav->first;
			if ( key != id )
			{
				continue;
			
			}
			else
			{
				if( isNumber(val) != true)
				{
					continue;
				}
				
			}
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itne_Kav->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itne_Kav->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itne_Kav->second));
			ame = itne_Kav->second;
		}
		
				
	}
			
		
	//// Identifier - Empty - Value (K_AT_K )////
			
			
	if ( !pMainFrame->gmmNE_K_A_K.empty() )
	{
		//tstring str = id + val;
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;

		CMainFrame::g_mmNE_K_A_K::iterator itne_KaK;
		
		for(itne_KaK = pMainFrame->gmmNE_K_A_K.begin(); itne_KaK != pMainFrame->gmmNE_K_A_K.end(); ++itne_KaK)
		{	
			
			tstring key = itne_KaK->first;
			int pos = key.find_first_of(_T("|"));
			//AfxMessageBox(key.substr(0, pos).data());
			if( key.substr(0, pos) == id )
			{
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				tstring sVal = key.substr(pos + 1, key.length());
				//int NE_iVal = _ttoi(sVal.data());
				double NE_dVal = _tcstod(sVal.data(), NULL);

				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_iVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal != NE_iVal )
				if( dVal != NE_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itne_KaK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itne_KaK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itne_KaK->second));
					ame = itne_KaK->second;
				}

			}
		}	
			
				
	}
			

	//// Identifier - Attribute - Empty ( K_K_VL )////
			
	if( !pMainFrame->gmmNE_K_K_V.empty() )
	{
		//tstring str = id + attr;
		CMainFrame::g_mmNE_K_K_V::iterator itne_KKv;
		
		for(itne_KKv = pMainFrame->gmmNE_K_K_V.begin(); itne_KKv != pMainFrame->gmmNE_K_K_V.end(); ++itne_KKv)
		{	
			tstring key = itne_KKv->first;
			int pos = key.find_first_of(_T("|"));
			tstring sId  =  key.substr(0, pos);
			tstring sAttr = key.substr(pos + 1, key.length());
			
			if( sAttr != attr || id != sId)
			{
				continue;
					
			}	
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itne_KKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itne_KKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itne_KKv->second));
			ame = itne_KKv->second;
		}	
		
		
	}
			

	//// Identifier - Attribute - Value ( K_K_K )////
			
	if( !pMainFrame->gmmNE_K_K_K.empty() )
	{
		//tstring str = id + attr + m_Val;
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;

		CMainFrame::g_mmNE_K_K_K::iterator itne_KKK;
		
		for(itne_KKK = pMainFrame->gmmNE_K_K_K.begin(); itne_KKK != pMainFrame->gmmNE_K_K_K.end(); ++itne_KKK)
		{	
			
			tstring key = itne_KKK->first;
			int pos1 = key.find_first_of(_T("|"));
			int pos2 = key.find_last_of(_T("|"));
			int aSize = pos2 - pos1 -1;

			tstring sId = key.substr(0, pos1);
			tstring sAttr = key.substr(pos1 + 1, aSize);
			tstring sVal = key.substr(pos2 + 1, key.length());
			
			/*
			AfxMessageBox(sId.data());
			AfxMessageBox(sAttr.data());
			AfxMessageBox(sVal.data());
			*/
			
			if( sId == id  && sAttr == attr )
			{
			
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				//int NE_iVal = _ttoi(sVal.data());
				double NE_dVal = _tcstod(sVal.data(), NULL);
			
				/*
					TCHAR buff[8];
					CString sGT_Val = _itot(GT_Val, buff, 10);
					CString siVal =_itot(iVal,buff, 10);
					AfxMessageBox(_T("sGT_Val :"));
					AfxMessageBox(sGT_Val);
					AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal != NE_iVal )
				if( dVal != NE_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itne_KKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itne_KKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itne_KKK->second));
					ame = itne_KKK->second;
				}
			}
		}		
		
				
	}
			
		
	//// Empty - Empty - Empty ( ID_AT_VL )////
			
	if ( !pMainFrame->gmmNE_I_A_V.empty())
	{
		CMainFrame::g_mmNE_I_A_V::iterator itne_IAV;
		
		for(itne_IAV = pMainFrame->gmmNE_I_A_V.begin(); itne_IAV != pMainFrame->gmmNE_I_A_V.end(); ++itne_IAV)
		{	
			if( isNumber(val) != true)
			{
				continue;
			}
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itne_IAV->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itne_IAV->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itne_IAV->second));
			ame = itne_IAV->second;
		}		
		
			
	}

return ame;

}



int CAipi_RETE_AM::insertLT(int wm, tstring id, tstring attr, tstring val)
{

//// *** LESSER THAN TEST **** //// 
	int ame = UNDEFINE;	
	//// Empty - Empty - Value  ( ID_AT_K ) ////
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	if( !pMainFrame->gmmLT_I_A_K.empty())
	{
		//int iVal	= UNDEFINE;
		double dVal = UNDEFINE;
		
		CMainFrame::g_mmLT_I_A_K::iterator itlt_iaK;
		
		for(itlt_iaK = pMainFrame->gmmLT_I_A_K.begin(); itlt_iaK != pMainFrame->gmmLT_I_A_K.end(); ++itlt_iaK)
		{	
			tstring key = itlt_iaK->first;
			/*
			AfxMessageBox(_T("Key"));
			AfxMessageBox(key.data());
			*/
			
			if( isNumber( val) == true )
			{
				
				//iVal = _ttoi(val.data());
				dVal = _tcstod(val.data(), NULL);
			}
			else
			{
				continue;
			}

			//int LT_iVal = _ttoi(key.data());
			double LT_dVal = _tcstod(key.data(), NULL);
			/*
			AfxMessageBox(_T("Val"));
			AfxMessageBox(val.data());
			
			TCHAR buff[8];
			CString sGT_Val = _itot(LT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			//if( iVal < LT_iVal )
			if( dVal < LT_dVal )
			{	
				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itlt_iaK->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itlt_iaK->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itlt_iaK->second));
				ame = itlt_iaK->second;
			}
		}
		
				
	}

			
		
	//// Empty - Attribute - Empty ( ID_K_VL ) ////
	//Este caso no va asuceder nunca		
	if( !pMainFrame->gmmLT_I_K_V.empty() )
	{
		
		CMainFrame::g_mmLT_I_K_V::iterator itlt_iKv;
		
		for(itlt_iKv = pMainFrame->gmmLT_I_K_V.begin(); itlt_iKv != pMainFrame->gmmLT_I_K_V.end(); ++itlt_iKv)
		{	
			tstring key = itlt_iKv->first;

			
			if( key != attr )
			{
				continue;
				
			}
			
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itlt_iKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itlt_iKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itlt_iKv->second));
			ame = itlt_iKv->second;

		}
		
			
	}
			
		
	//// Empty - Attribute - Value ( ID_K_K ) ////
			
	if( !pMainFrame->gmmLT_I_K_K.empty() )
	{
		//tstring str = attr + val;
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;
		
		CMainFrame::g_mmLT_I_K_K::iterator itlt_iKK;

		
		//AfxMessageBox(_T("iVAL"));
		//AfxMessageBox(val.data());
		
		
		for(itlt_iKK = pMainFrame->gmmLT_I_K_K.begin(); itlt_iKK != pMainFrame->gmmLT_I_K_K.end(); ++itlt_iKK)
		{	
			tstring key = itlt_iKK->first;
			int pos = key.find_first_of(_T("|"));
			if( key.substr(0, pos) == attr )
			{
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				tstring sVal = key.substr(pos + 1, key.length());
				//int LT_dVal = _ttoi(sVal.data());
				double LT_dVal = _tcstod(sVal.data(), NULL); 
				
			/*
				TCHAR buff[8];
				CString sLT_Val = _itot(LT_dVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sLT_Val :"));
				AfxMessageBox(sLT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
			*/

				//if( iVal < LT_iVal )
				if( dVal < LT_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itlt_iKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itlt_iKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itlt_iKK->second));
					ame = itlt_iKK->second;

				}
			}
		}
		
	}
					
		
	//// Identifier - Empty - Empty ( K_AT_VL )////
			
	if( !pMainFrame->gmmLT_K_A_V.empty() )
	{
		CMainFrame::g_mmLT_K_A_V::iterator itlt_Kav;

		for(itlt_Kav = pMainFrame->gmmLT_K_A_V.begin(); itlt_Kav != pMainFrame->gmmLT_K_A_V.end(); ++itlt_Kav)
		{	
			tstring key = itlt_Kav->first;
			if ( key != id )
			{
				continue;
			
			}
			else
			{
				if( isNumber(val) != true)
				{
					continue;
				}
				
			}
				
			
			
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itlt_Kav->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itlt_Kav->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itlt_Kav->second));
			ame = itlt_Kav->second;

			
		}
		
				
	}
			
		
	//// Identifier - Empty - Value (K_AT_K )////
			
				
	if ( !pMainFrame->gmmLT_K_A_K.empty() )
	{
		//tstring str = id + val;
		int iVal = UNDEFINE;
		CMainFrame::g_mmLT_K_A_K::iterator itlt_KaK;
		
		for(itlt_KaK = pMainFrame->gmmLT_K_A_K.begin(); itlt_KaK != pMainFrame->gmmLT_K_A_K.end(); ++itlt_KaK)
		{	
			tstring key = itlt_KaK->first;
			int pos = key.find_first_of(_T("|"));
			//AfxMessageBox(key.substr(0, pos).data());
			if( key.substr(0, pos) == id )
			{
				if( isNumber(val) == true )
				{
					iVal = _ttoi(val.data());
				}
				else
				{
					continue;
				}
				
				tstring sVal = key.substr(pos + 1, key.length());
				int LT_Val = _ttoi(sVal.data());
			
			
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_Val, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				if( iVal < LT_Val )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itlt_KaK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itlt_KaK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itlt_KaK->second));
					ame = itlt_KaK->second;

				}
			}
		}	
		
				
	}
			

	//// Identifier - Attribute - Empty ( K_K_VL )////
			
	if( !pMainFrame->gmmLT_K_K_V.empty() )
	{
		//tstring str = id + attr;
		CMainFrame::g_mmLT_K_K_V::iterator itlt_KKv;
		
		for(itlt_KKv = pMainFrame->gmmLT_K_K_V.begin(); itlt_KKv != pMainFrame->gmmLT_K_K_V.end(); ++itlt_KKv)
		{	
			tstring key = itlt_KKv->first;
			int pos = key.find_first_of(_T("|"));
			tstring sId  =  key.substr(0, pos);
			tstring sAttr = key.substr(pos + 1, key.length());
			
			if( sAttr != attr || id != sId)
			{
				continue;
					
			}	
			
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itlt_KKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itlt_KKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itlt_KKv->second));
			ame = itlt_KKv->second;

		}	
		
		
	}
			

	//// Identifier - Attribute - Value ( K_K_K )////
			
	if( !pMainFrame->gmmLT_K_K_K.empty() )
	{
		//tstring str = id + attr + m_Val;
		int iVal = UNDEFINE;
		CMainFrame::g_mmLT_K_K_K::iterator itlt_KKK;
		
		for(itlt_KKK = pMainFrame->gmmLT_K_K_K.begin(); itlt_KKK != pMainFrame->gmmLT_K_K_K.end(); ++itlt_KKK)
		{	
			
			tstring key = itlt_KKK->first;
			int pos1 = key.find_first_of(_T("|"));
			int pos2 = key.find_last_of(_T("|"));
			int aSize = pos2 - pos1 -1;

			tstring sId = key.substr(0, pos1);
			tstring sAttr = key.substr(pos1 + 1, aSize);
			tstring sVal = key.substr(pos2 + 1, key.length());
			
			/*
			AfxMessageBox(sId.data());
			AfxMessageBox(sAttr.data());
			AfxMessageBox(sVal.data());
			*/
			
			if( sId == id  && sAttr == attr )
			{
			
				if( isNumber(val) == true )
				{
					iVal = _ttoi(val.data());
				}
				else
				{
					continue;
				}
				
				int LT_Val = _ttoi(sVal.data());
			
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_Val, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				if( iVal < LT_Val )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itlt_KKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itlt_KKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itlt_KKK->second));
					ame = itlt_KKK->second;

				}
			}
		}
				
	}
			
		
	//// Empty - Empty - Empty ( ID_AT_VL )////
			
	if ( !pMainFrame->gmmLT_I_A_V.empty())
	{
		
		CMainFrame::g_mmLT_I_A_V::iterator itlt_IAV;
		
		for(itlt_IAV = pMainFrame->gmmLT_I_A_V.begin(); itlt_IAV != pMainFrame->gmmLT_I_A_V.end(); ++itlt_IAV)
		{	
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			if( isNumber(val) != true )
			{
				continue;
			}
			
			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itlt_IAV->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itlt_IAV->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itlt_IAV->second));
			ame = itlt_IAV->second;

			
		}
			
	}
		


return ame;
}


int CAipi_RETE_AM::insertLE(int wm, tstring id, tstring attr, tstring val)
{

//// *** LESSER OR EQUAL THAN TEST **** //// 
	int ame = UNDEFINE;		
	//// Empty - Empty - Value  ( ID_AT_K ) ////
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	if( !pMainFrame->gmmLE_I_A_K.empty())
	{
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;

		CMainFrame::g_mmLE_I_A_K::iterator itle_iaK;
		
		for(itle_iaK = pMainFrame->gmmLE_I_A_K.begin(); itle_iaK != pMainFrame->gmmLE_I_A_K.end(); ++itle_iaK)
		{	
			tstring key = itle_iaK->first;
			/*
			AfxMessageBox(_T("Key"));
			AfxMessageBox(key.data());
			*/
			
			if( isNumber( val) == true )
			{
				
				//iVal = _ttoi(val.data());
				dVal = _tcstod(val.data(), NULL);
			}
			else
			{
				continue;
			}

			//int LE_Val = _ttoi(key.data());
			double LE_dVal = _tcstod(key.data(), NULL);	
			
		/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			//if( iVal <= LE_iVal )
			if( dVal <= LE_dVal )
			{	
				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itle_iaK->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itle_iaK->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itle_iaK->second));
				ame = itle_iaK->second;
			}
		}

				
	}

			
		
	//// Empty - Attribute - Empty ( ID_K_VL ) ////
			
	if( !pMainFrame->gmmLE_I_K_V.empty() )
	{
		CMainFrame::g_mmLE_I_K_V::iterator itle_iKv;
		
		for(itle_iKv = pMainFrame->gmmLE_I_K_V.begin(); itle_iKv != pMainFrame->gmmLE_I_K_V.end(); ++itle_iKv)
		{	
			tstring key = itle_iKv->first;

			if( key != attr )
			{
				continue;
				
			}
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itle_iKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itle_iKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itle_iKv->second));
			ame = itle_iKv->second;
			
		}
				
			
	}
			
		
	//// Empty - Attribute - Value ( ID_K_K ) ////
			
	if( !pMainFrame->gmmLE_I_K_K.empty() )
	{
		//tstring str = attr + val;
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;

		CMainFrame::g_mmLE_I_K_K::iterator itle_iKK;

		/*
		AfxMessageBox(_T("iVAL"));
		AfxMessageBox(val.data());
		*/
		
		for(itle_iKK = pMainFrame->gmmLE_I_K_K.begin(); itle_iKK != pMainFrame->gmmLE_I_K_K.end(); ++itle_iKK)
		{	
			
			tstring key = itle_iKK->first;
			int pos = key.find_first_of(_T("|"));
			if( key.substr(0, pos) == attr )
			{
				if( isNumber(val) == true )
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				tstring sVal = key.substr(pos + 1, key.length());
				//int LE_iVal = _ttoi(sVal.data());
				
				double LE_dVal = _tcstod(sVal.data(), NULL);
				
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_iVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal <= LE_iVal )
				if( dVal >= LE_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itle_iKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itle_iKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itle_iKK->second));
					ame = itle_iKK->second;
				}
			}
		}
	}
					
		
	//// Identifier - Empty - Empty ( K_AT_VL )////
			
	if( !pMainFrame->gmmLE_K_A_V.empty() )
	{
		CMainFrame::g_mmLE_K_A_V::iterator itle_Kav;

		for(itle_Kav = pMainFrame->gmmLE_K_A_V.begin(); itle_Kav != pMainFrame->gmmLE_K_A_V.end(); ++itle_Kav)
		{	
			tstring key = itle_Kav->first;
			if ( key != id )
			{
				continue;
			
			}
			else
			{
				if( isNumber(val) != true )
				{
					continue;
				}
				
			}
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itle_Kav->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itle_Kav->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itle_Kav->second));
				ame = itle_Kav->second;
			
		}
				
	}
			
		
	//// Identifier - Empty - Value (K_AT_K )////
			
	if ( !pMainFrame->gmmLE_K_A_K.empty() )
	{
		//tstring str = id + val;
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;

		CMainFrame::g_mmLE_K_A_K::iterator itle_KaK;
		
		for(itle_KaK = pMainFrame->gmmLE_K_A_K.begin(); itle_KaK != pMainFrame->gmmLE_K_A_K.end(); ++itle_KaK)
		{	
			tstring key = itle_KaK->first;
			int pos = key.find_first_of(_T("|"));
			//AfxMessageBox(key.substr(0, pos).data());
			if( key.substr(0, pos) == id )
			{
				if( isNumber(val) == true )
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				tstring sVal = key.substr(pos + 1, key.length());
				//int LE_Val = _ttoi(sVal.data());
				double LE_dVal = _tcstod(sVal.data(), NULL);	
			
					
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_Val, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal <= LE_iVal )
				if( dVal >= LE_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itle_KaK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itle_KaK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itle_KaK->second));
					ame = itle_KaK->second;
				}
			}
		}
				
	}
			

	//// Identifier - Attribute - Empty ( K_K_VL )////
			
	if( !pMainFrame->gmmLE_K_K_V.empty() )
	{
		//tstring str = id + attr;
		//int iVal = _ttoi(val.data());
		double dVal = _tcstod(val.data(), NULL);

		CMainFrame::g_mmLE_K_K_V::iterator itle_KKv;
		
		for(itle_KKv = pMainFrame->gmmLE_K_K_V.begin(); itle_KKv != pMainFrame->gmmLE_K_K_V.end(); ++itle_KKv)
		{	
			tstring key = itle_KKv->first;
			int pos = key.find_first_of(_T("|"));
			tstring sId  =  key.substr(0, pos);
			tstring sAttr = key.substr(pos + 1, key.length());
			
			if( sAttr != attr || id != sId)
			{
				continue;
					
			}	
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itle_KKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itle_KKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itle_KKv->second));
			ame = itle_KKv->second;
			
		}
		
	}
			

	//// Identifier - Attribute - Value ( K_K_K )////
			
	if( !pMainFrame->gmmLE_K_K_K.empty() )
	{
		//tstring str = id + attr + m_Val;
		//int iVal = _ttoi(val.data());
		double dVal = _tcstod(val.data(), NULL);

		CMainFrame::g_mmLE_K_K_K::iterator itle_KKK;
		
		for(itle_KKK = pMainFrame->gmmLE_K_K_K.begin(); itle_KKK != pMainFrame->gmmLE_K_K_K.end(); ++itle_KKK)
		{	
		
			tstring key = itle_KKK->first;
			int pos1 = key.find_first_of(_T("|"));
			int pos2 = key.find_last_of(_T("|"));
			int aSize = pos2 - pos1 -1;

			tstring sId = key.substr(0, pos1);
			tstring sAttr = key.substr(pos1 + 1, aSize);
			tstring sVal = key.substr(pos2 + 1, key.length());
			
			/*
			AfxMessageBox(sId.data());
			AfxMessageBox(sAttr.data());
			AfxMessageBox(sVal.data());
			*/
			
			if( sId == id  && sAttr == attr )
			{
			
				if( isNumber(val) == true )
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				//int LE_iVal = _ttoi(sVal.data());
				double LE_dVal = _tcstod(sVal.data(), NULL);
				
				//if( iVal <= LE_dVal )
				if( dVal >= LE_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itle_KKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itle_KKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itle_KKK->second));
					ame = itle_KKK->second;
				}
			}
		}
				
	}
			
		
	//// Empty - Empty - Empty ( ID_AT_VL )////
			
	if ( !pMainFrame->gmmLE_I_A_V.empty())
	{
		//int iVal = _ttoi(val.data());
		double dVal = _tcstod(val.data(), NULL);

		CMainFrame::g_mmLE_I_A_V::iterator itle_IAV;
		
		for(itle_IAV = pMainFrame->gmmLE_I_A_V.begin(); itle_IAV != pMainFrame->gmmLE_I_A_V.end(); ++itle_IAV)
		{	
			if( isNumber(val) != true)
			{
				continue;
			}
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itle_IAV->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itle_IAV->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itle_IAV->second));
				ame = itle_IAV->second;
			
		}
			
	}
		

return ame;

}



int CAipi_RETE_AM::insertGT(int wm, tstring id, tstring attr, tstring val)
{

//// *** GREATER THAN TEST **** //// 
	int ame = UNDEFINE;
		
	//// Empty - Empty - Value  ( ID_AT_K ) ////
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	if( !pMainFrame->gmmGT_I_A_K.empty())
	{
		
		//int    iVal = UNDEFINE;
		double dVal = UNDEFINE;
		
		CMainFrame::g_mmGT_I_A_K::iterator itgt_iaK;
		
		for(itgt_iaK = pMainFrame->gmmGT_I_A_K.begin(); itgt_iaK != pMainFrame->gmmGT_I_A_K.end(); ++itgt_iaK)
		{	
			
			tstring key = itgt_iaK->first;
			/*
			AfxMessageBox(_T("Key"));
			AfxMessageBox(key.data());
			*/
			
			if( isNumber( val) == true )
			{
				
				//iVal = _ttoi(val.data());
				dVal = _tcstod(val.data(), NULL);
			}
			else
			{
				continue;
			}

			//int GT_iVal = _ttoi(key.data());
			double GT_dVal = _tcstod(key.data(), NULL);
				
		/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			//if( iVal > GT_iVal )
			if( dVal > GT_dVal)
			{	
				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itgt_iaK->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itgt_iaK->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itgt_iaK->second));
				ame = itgt_iaK->second;
			}
		}
		

	}
	
		
				
	

			
		
	//// Empty - Attribute - Empty ( ID_K_VL ) ////
			
	if( !pMainFrame->gmmGT_I_K_V.empty() )
	{
		CMainFrame::g_mmGT_I_K_V::iterator itgt_iKv;
		
		for(itgt_iKv = pMainFrame->gmmGT_I_K_V.begin(); itgt_iKv != pMainFrame->gmmGT_I_K_V.end(); ++itgt_iKv)
		{	
			tstring key = itgt_iKv->first;
			
			if( key != attr )
			{
				continue;
				
			}
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itgt_iKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itgt_iKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itgt_iKv->second));
			ame = itgt_iKv->second;
			
		}
		
		
			
	}
			
		
	//// Empty - Attribute - Value ( ID_K_K ) ////
			
	if( !pMainFrame->gmmGT_I_K_K.empty() )
	{
		//tstring str = attr + val;
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;

		CMainFrame::g_mmGT_I_K_K::iterator itgt_iKK;

		/*
		AfxMessageBox(_T("iVAL"));
		AfxMessageBox(val.data());
		*/
		
		for(itgt_iKK = pMainFrame->gmmGT_I_K_K.begin(); itgt_iKK != pMainFrame->gmmGT_I_K_K.end(); ++itgt_iKK)
		{	
			tstring key = itgt_iKK->first;
			int pos = key.find_first_of(_T("|"));

			/*
			AfxMessageBox(_T("Attr1"));
			AfxMessageBox(key.substr(0, pos).data());
			AfxMessageBox(_T("Attr2"));
			AfxMessageBox(attr.data());
			*/
			if( key.substr(0, pos) == attr )
			{
				/*
				AfxMessageBox(_T("iVAL"));
				AfxMessageBox(val.data());
				*/
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				tstring sVal = key.substr(pos + 1, key.length());
				//int GT_iVal = _ttoi(sVal.data());
				double GT_dVal = _tcstod(sVal.data(), NULL);
				
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_iVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal > GT_iVal )
				if( dVal > GT_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itgt_iKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itgt_iKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itgt_iKK->second));
					ame = itgt_iKK->second;
				}
			}
		}
		

	}
					
		
	//// Identifier - Empty - Empty ( K_AT_VL )////
	if( !pMainFrame->gmmGT_K_A_V.empty() )
	{
		CMainFrame::g_mmGT_K_A_V::iterator itgt_Kav;

		for(itgt_Kav = pMainFrame->gmmGT_K_A_V.begin(); itgt_Kav != pMainFrame->gmmGT_K_A_V.end(); ++itgt_Kav)
		{	
			tstring key = itgt_Kav->first;
			if ( key != id )
			{
				continue;
			
			}
			else
			{
				if( isNumber(val) != true)
				{
					continue;
				}
				
			}
				
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itgt_Kav->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itgt_Kav->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itgt_Kav->second));
			ame = itgt_Kav->second;
		}
		
				
	}
			
		
	//// Identifier - Empty - Value (K_AT_K )////
			
			
	
	if ( !pMainFrame->gmmGT_K_A_K.empty() )
	{
		//tstring str = id + val;
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;

		CMainFrame::g_mmGT_K_A_K::iterator itgt_KaK;
		
		for(itgt_KaK = pMainFrame->gmmGT_K_A_K.begin(); itgt_KaK != pMainFrame->gmmGT_K_A_K.end(); ++itgt_KaK)
		{	
			tstring key = itgt_KaK->first;
			int pos = key.find_first_of(_T("|"));
			
			//AfxMessageBox(key.substr(0, pos).data());
			if( key.substr(0, pos) == id )
			{
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				tstring sVal = key.substr(pos + 1, key.length());
				//int GT_Val = _ttoi(sVal.data());
				double GT_dVal = _tcstod(sVal.data(), NULL);
			
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_Val, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal > GT_iVal )
				if( dVal > GT_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itgt_KaK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itgt_KaK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itgt_KaK->second));
					ame = itgt_KaK->second;
				}

			}
		}	
				
		
				
	}
			

	//// Identifier - Attribute - Empty ( K_K_VL )////
			
	if( !pMainFrame->gmmGT_K_K_V.empty() )
	{
		//tstring str = id + attr;
		//int iVal = _ttoi(val.data());
		double dVal = _tcstod(val.data(), NULL);

		CMainFrame::g_mmGT_K_K_V::iterator itgt_KKv;
		
		for(itgt_KKv = pMainFrame->gmmGT_K_K_V.begin(); itgt_KKv != pMainFrame->gmmGT_K_K_V.end(); ++itgt_KKv)
		{	
			tstring key = itgt_KKv->first;
			int pos = key.find_first_of(_T("|"));
			tstring sId  =  key.substr(0, pos);
			tstring sAttr = key.substr(pos + 1, key.length());
			
			if( sAttr != attr || id != sId)
			{
				continue;
					
			}	
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itgt_KKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itgt_KKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itgt_KKv->second));
			ame = itgt_KKv->second;
			
		}	
				
		
		
	}
			

	//// Identifier - Attribute - Value ( K_K_K )////
			
	if( !pMainFrame->gmmGT_K_K_K.empty() )
	{
		
		//AfxMessageBox(_T("Insert GT"));
		//tstring str = id + attr + m_Val;
		///int iVal = UNDEFINE;
		double dVal = UNDEFINE;

		CMainFrame::g_mmGT_K_K_K::iterator itgt_KKK;
		
		for(itgt_KKK = pMainFrame->gmmGT_K_K_K.begin(); itgt_KKK != pMainFrame->gmmGT_K_K_K.end(); ++itgt_KKK)
		{	
			tstring key = itgt_KKK->first;
			int pos1 = key.find_first_of(_T("|"));
			int pos2 = key.find_last_of(_T("|"));
			int aSize = pos2 - pos1 -1;

			tstring sId = key.substr(0, pos1);
			tstring sAttr = key.substr(pos1 + 1, aSize);
			tstring sVal = key.substr(pos2 + 1, key.length());

			/*
			AfxMessageBox(_T("GT1"));
			AfxMessageBox(val.data());
			AfxMessageBox(sVal.data());
			*/
			/*
			AfxMessageBox(sId.data());
			AfxMessageBox(sAttr.data());
			AfxMessageBox(sVal.data());
			*/
			
			if( sId == id  && sAttr == attr )
			{
				//AfxMessageBox(_T("GT2"));
			
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
					//AfxMessageBox(_T("Is Number"));
				}
				else
				{
					//AfxMessageBox(_T("Continue"));
					continue;
				}
				
				//int GT_iVal = _ttoi(sVal.data());
				double GT_dVal = _tcstod(sVal.data(), NULL);
				//AfxMessageBox(_T("GT3"));
			
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_iVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal > GT_iVal )
				if( dVal > GT_dVal )
				{	
					//AfxMessageBox(_T("GT4"));
			
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itgt_KKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itgt_KKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itgt_KKK->second));
					ame = itgt_KKK->second;
					
					/*
					CString str;
					str.Format(_T("Inserto WM...%d  " ), wm);
					AfxMessageBox(str);
			
					str.Format(_T("Inserto AM...%d  " ), ame);
					AfxMessageBox(str);
					*/
				}
			}
		}		
		
				
	}
			
		
	//// Empty - Empty - Empty ( ID_AT_VL )////
			
	if ( !pMainFrame->gmmGT_I_A_V.empty())
	{
		//int iVal = _ttoi(val.data());
		double dVal = _tcstod(val.data(), NULL);
		CMainFrame::g_mmGT_I_A_V::iterator itgt_IAV;
		
		for(itgt_IAV = pMainFrame->gmmGT_I_A_V.begin(); itgt_IAV != pMainFrame->gmmGT_I_A_V.end(); ++itgt_IAV)
		{	
			if( isNumber(val) != true)
			{
				continue;
			}
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itgt_IAV->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itgt_IAV->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itgt_IAV->second));
			ame = itgt_IAV->second;
		}		
			
	}
		
return ame;


}


int CAipi_RETE_AM::insertGE(int wm, tstring id, tstring attr, tstring val)
{

//// *** GREATER OR EQUAL THAN TEST **** //// 
	int ame = UNDEFINE;		
	//// Empty - Empty - Value  ( ID_AT_K ) ////
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	if( !pMainFrame->gmmGE_I_A_K.empty())
	{
		//int iVal	= UNDEFINE;
		double dVal = UNDEFINE;
		
		CMainFrame::g_mmGE_I_A_K::iterator itge_iaK;
		
		for(itge_iaK = pMainFrame->gmmGE_I_A_K.begin(); itge_iaK != pMainFrame->gmmGE_I_A_K.end(); ++itge_iaK)
		{	
			tstring key = itge_iaK->first;
			/*
			AfxMessageBox(_T("Key"));
			AfxMessageBox(key.data());
			*/
			
			if( isNumber( val) == true )
			{
				//iVal = _ttoi(val.data());
				dVal = _tcstod(val.data(), NULL);
			}
			else
			{
				continue;
			}

			//int GE_iVal = _ttoi(key.data());
			double GE_dVal = _tcstod(key.data(), NULL);
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			//if( iVal >= GE_Val )
			if( dVal >= GE_dVal )
			{	
				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itge_iaK->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itge_iaK->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itge_iaK->second));
				ame = itge_iaK->second;
			}
		}

				
	}

			
		
	//// Empty - Attribute - Empty ( ID_K_VL ) ////
			
	if( !pMainFrame->gmmGE_I_K_V.empty() )
	{
		CMainFrame::g_mmGE_I_K_V::iterator itge_iKv;
		
		for(itge_iKv = pMainFrame->gmmGE_I_K_V.begin(); itge_iKv != pMainFrame->gmmGE_I_K_V.end(); ++itge_iKv)
		{	
			tstring key = itge_iKv->first;

			
			if( key != attr )
			{
				continue;
				
			}
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itge_iKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itge_iKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itge_iKv->second));
			ame = itge_iKv->second;
		}
		
			
	}
			
		
	//// Empty - Attribute - Value ( ID_K_K ) ////
			
	if( !pMainFrame->gmmGE_I_K_K.empty() )
	{
		//tstring str = attr + val;
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;

		CMainFrame::g_mmGE_I_K_K::iterator itge_iKK;

		/*
		AfxMessageBox(_T("iVAL"));
		AfxMessageBox(val.data());
		*/
		
		for(itge_iKK = pMainFrame->gmmGE_I_K_K.begin(); itge_iKK != pMainFrame->gmmGE_I_K_K.end(); ++itge_iKK)
		{	
			
			tstring key = itge_iKK->first;
			int pos = key.find_first_of(_T("|"));
			if( key.substr(0, pos) == attr )
			{
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				tstring sVal = key.substr(pos + 1, key.length());
				//int GE_iVal = _ttoi(sVal.data());
				double GE_dVal = _tcstod(sVal.data(), NULL);

				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_iVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal >= GE_Val )
				if( dVal >= GE_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itge_iKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itge_iKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itge_iKK->second));
					ame = itge_iKK->second;
				}

			}
		}
		
	}
					
		
	//// Identifier - Empty - Empty ( K_AT_VL )////
			
	if( !pMainFrame->gmmGE_K_A_V.empty() )
	{
		CMainFrame::g_mmGE_K_A_V::iterator itge_Kav;

		for(itge_Kav = pMainFrame->gmmGE_K_A_V.begin(); itge_Kav != pMainFrame->gmmGE_K_A_V.end(); ++itge_Kav)
		{	
			tstring key = itge_Kav->first;
			if ( key != id )
			{
				continue;
			
			}
			else
			{
				if( isNumber(val) != true)
				{
					continue;
				}
				
			}
			
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			
				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itge_Kav->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itge_Kav->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itge_Kav->second));
				ame = itge_Kav->second;
		}
		
				
	}
			
		
	//// Identifier - Empty - Value (K_AT_K )////
			
			
	if ( !pMainFrame->gmmGE_K_A_K.empty() )
	{
		//tstring str = id + val;
		//int iVal = UNDEFINE;
		double dVal = UNDEFINE;

		CMainFrame::g_mmGE_K_A_K::iterator itge_KaK;
		
		for(itge_KaK = pMainFrame->gmmGE_K_A_K.begin(); itge_KaK != pMainFrame->gmmGE_K_A_K.end(); ++itge_KaK)
		{	
			tstring key = itge_KaK->first;
			int pos = key.find_first_of(_T("|"));
			//AfxMessageBox(key.substr(0, pos).data());
			if( key.substr(0, pos) == id )
			{
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					double dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				tstring sVal = key.substr(pos + 1, key.length());
				//int GE_Val = _ttoi(sVal.data());
				double GE_dVal = _tcstod(sVal.data(), NULL);
			
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_iVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal >= GE_iVal )
				if( dVal >= GE_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itge_KaK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itge_KaK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itge_KaK->second));
					ame = itge_KaK->second;
				}

			}
		}	
		
				
	}
			

	//// Identifier - Attribute - Empty ( K_K_VL )////
			
	if( !pMainFrame->gmmGE_K_K_V.empty() )
	{
		//tstring str = id + attr;
		CMainFrame::g_mmGE_K_K_V::iterator itge_KKv;
		
		for(itge_KKv = pMainFrame->gmmGE_K_K_V.begin(); itge_KKv != pMainFrame->gmmGE_K_K_V.end(); ++itge_KKv)
		{	
			tstring key = itge_KKv->first;
			int pos = key.find_first_of(_T("|"));
			tstring sId  =  key.substr(0, pos);
			tstring sAttr = key.substr(pos + 1, key.length());
			
			if( sAttr != attr || id != sId)
			{
				continue;
					
			}	
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itge_KKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itge_KKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itge_KKv->second));
			ame = itge_KKv->second;
		}	
		
		
	}
			

	//// Identifier - Attribute - Value ( K_K_K )////
			
	if( !pMainFrame->gmmGE_K_K_K.empty() )
	{
		//tstring str = id + attr + m_Val;
		//int iVal = _ttoi(val.data());
		double dVal = _tcstod(val.data(), NULL);

		CMainFrame::g_mmGE_K_K_K::iterator itge_KKK;
		
		for(itge_KKK = pMainFrame->gmmGE_K_K_K.begin(); itge_KKK != pMainFrame->gmmGE_K_K_K.end(); ++itge_KKK)
		{	
			tstring key = itge_KKK->first;
			int pos1 = key.find_first_of(_T("|"));
			int pos2 = key.find_last_of(_T("|"));
			int aSize = pos2 - pos1 -1;

			tstring sId = key.substr(0, pos1);
			tstring sAttr = key.substr(pos1 + 1, aSize);
			tstring sVal = key.substr(pos2 + 1, key.length());
			
			/*
			AfxMessageBox(sId.data());
			AfxMessageBox(sAttr.data());
			AfxMessageBox(sVal.data());
			*/
			
			if( sId == id  && sAttr == attr )
			{
			
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					dVal = _tcstod(val.data(), NULL);
				}
				else
				{
					continue;
				}
				
				//int GE_iVal = _ttoi(sVal.data());
				double GE_dVal = _tcstod(sVal.data(), NULL);	

				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_iVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal >= GE_iVal )
				if( dVal >= GE_dVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itge_KKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itge_KKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itge_KKK->second));
					ame = itge_KKK->second;
				}
			}
		}
				
	}
			
		
	//// Empty - Empty - Empty ( ID_AT_VL )////
			
	if ( !pMainFrame->gmmGE_I_A_V.empty())
	{
		
		CMainFrame::g_mmGE_I_A_V::iterator itge_IAV;
		
		for(itge_IAV = pMainFrame->gmmGE_I_A_V.begin(); itge_IAV != pMainFrame->gmmGE_I_A_V.end(); ++itge_IAV)
		{	
			if( isNumber(val) != true)
			{
				continue;
			}
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_Val, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itge_IAV->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itge_IAV->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itge_IAV->second));
			ame = itge_IAV->second;
		}
			
	}
		

return ame; 


}





int CAipi_RETE_AM::insertAS(int wm, tstring id, tstring attr, tstring val)
{
	///NUMERIC OPERATIONS////

//// *** ASSIGNATION TEST **** //// 
	int ame = UNDEFINE;
		
	//// Empty - Empty - Value  ( ID_AT_K ) ////
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	if( !pMainFrame->gmmAS_I_A_K.empty())
	{
		//int iVal	= UNDEFINE;
		//int AS_iVal = UNDEFINE;
		double dVal = UNDEFINE;
		double AS_dVal = UNDEFINE;
		
		CMainFrame::g_mmAS_I_A_K::iterator itas_iaK;
		
		for(itas_iaK = pMainFrame->gmmAS_I_A_K.begin(); itas_iaK != pMainFrame->gmmAS_I_A_K.end(); ++itas_iaK)
		{	
			tstring key = itas_iaK->first;
			/*
			AfxMessageBox(_T("Key"));
			AfxMessageBox(key.data());
			*/
			
			if( isNumber( val) == true )
			{
				
				//iVal = _ttoi(val.data());
				//AS_iVal = _ttoi(key.data());
				dVal =  _tcstod(val.data(), NULL);
				AS_dVal = _tcstod(key.data(), NULL);
			}
						
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			//if( iVal == AS_iVal ||  val == key )
			if( dVal == AS_dVal || val == key )
			{	
				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itas_iaK->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itas_iaK->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itas_iaK->second));
				ame = itas_iaK->second;
			}
		}

				
	}

			
		
	//// Empty - Attribute - Empty ( ID_K_VL ) ////
			
	if( !pMainFrame->gmmAS_I_K_V.empty() )
	{
				
		CMainFrame::g_mmAS_I_K_V::iterator itas_iKv;
		
		for(itas_iKv = pMainFrame->gmmAS_I_K_V.begin(); itas_iKv != pMainFrame->gmmAS_I_K_V.end(); ++itas_iKv)
		{	
			tstring key = itas_iKv->first;
					
			if( key != attr )
			{
				
				continue;
				
			}
			/*
			AfxMessageBox(_T("key :"));
			AfxMessageBox(key.data());
			AfxMessageBox(_T("attr :"));
			AfxMessageBox(attr.data());
			*/			

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itas_iKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itas_iKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itas_iKv->second));
			ame = itas_iKv->second;
		}
		
			
	}
			
		
	//// Empty - Attribute - Value ( ID_K_K ) ////
			
	if( !pMainFrame->gmmAS_I_K_K.empty() )
	{
		//tstring str = attr + val;
		//int iVal = UNDEFINE;
		//int AS_iVal = UNDEFINE;
		double dVal = UNDEFINE;
		double AS_dVal = UNDEFINE;
		
		
		CMainFrame::g_mmAS_I_K_K::iterator itas_iKK;

		/*
		AfxMessageBox(_T("iVAL"));
		AfxMessageBox(val.data());
		*/
		
		for(itas_iKK = pMainFrame->gmmAS_I_K_K.begin(); itas_iKK != pMainFrame->gmmAS_I_K_K.end(); ++itas_iKK)
		{	
			tstring key = itas_iKK->first;
			int pos = key.find_first_of(_T("|"));
			
			if( key.substr(0, pos) == attr )
			{
				
				tstring sVal = key.substr(pos + 1, key.length());

				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					//AS_Val = _ttoi(sVal.data());

					dVal = _tcstod(val.data(), NULL);
					AS_dVal = _tcstod(sVal.data(), NULL);
				}
						
			
				/*
				TCHAR buff[8];
				CString sAS_Val = _itot(AS_iVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sAS_Val :"));
				AfxMessageBox(sAS_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal == AS_iVal || val == sVal )
				if( dVal == AS_dVal || val == sVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itas_iKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itas_iKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itas_iKK->second));
					ame = itas_iKK->second;
				}

			}
		}
		
	}
					
		
	//// Identifier - Empty - Empty ( K_AT_VL )////
			
	if( !pMainFrame->gmmAS_K_A_V.empty() )
	{
		CMainFrame::g_mmAS_K_A_V::iterator itas_Kav;

		for(itas_Kav = pMainFrame->gmmAS_K_A_V.begin(); itas_Kav != pMainFrame->gmmAS_K_A_V.end(); ++itas_Kav)
		{	
			tstring key = itas_Kav->first;
			if ( key != id )
			{
				continue;
			
			}
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

				pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itas_Kav->second , wm));
				pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itas_Kav->second));
				//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itas_Kav->second));
				ame = itas_Kav->second;
		}
		
				
	}
			
		
	//// Identifier - Empty - Value (K_AT_K )////
			
			
	if ( !pMainFrame->gmmAS_K_A_K.empty() )
	{
		//tstring str = id + val;
		//int iVal = _ttoi(val.data());
		//int AS_iVal = UNDEFINE;

		double dVal =  _tcstod(val.data(), NULL);
		double AS_dVal = UNDEFINE;

		CMainFrame::g_mmAS_K_A_K::iterator itas_KaK;
		
		for(itas_KaK = pMainFrame->gmmAS_K_A_K.begin(); itas_KaK != pMainFrame->gmmAS_K_A_K.end(); ++itas_KaK)
		{	
			tstring key = itas_KaK->first;
			int pos = key.find_first_of(_T("|"));
			//AfxMessageBox(key.substr(0, pos).data());
			if( key.substr(0, pos) == id )
			{
			
				tstring key = itas_KaK->first;
				int pos = key.find_first_of(_T("|"));
				//AfxMessageBox(key.substr(0, pos).data());
				if( key.substr(0, pos) == id )
				{
					
					tstring sVal = key.substr(pos + 1, key.length());
					
					if( isNumber(val) == true)
					{
						//iVal = _ttoi(val.data());
						//AS_iVal = _ttoi(sVal.data());
						
						dVal = _tcstod(val.data(), NULL);
						AS_dVal = _tcstod(sVal.data(), NULL);

					}
										
								
			
				
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_iVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

					//if( iVal == AS_Val || val == sVal )
					if( dVal == AS_dVal || val == sVal )
					{	
						pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itas_KaK->second , wm));
						pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itas_KaK->second));
						//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itas_KaK->second));
						ame = itas_KaK->second;
					}
				}
			}	
		}
				
	}
			

	//// Identifier - Attribute - Empty ( K_K_VL )////
			
	if( !pMainFrame->gmmAS_K_K_V.empty() )
	{
		//tstring str = id + attr;
		CMainFrame::g_mmAS_K_K_V::iterator itas_KKv;
		
		for(itas_KKv = pMainFrame->gmmAS_K_K_V.begin(); itas_KKv != pMainFrame->gmmAS_K_K_V.end(); ++itas_KKv)
		{	
			
			tstring key = itas_KKv->first;
			int pos = key.find_first_of(_T("|"));
			tstring sId  =  key.substr(0, pos);
			tstring sAttr = key.substr(pos + 1, key.length());
			
			if( sAttr != attr || id != sId)
			{
				continue;
					
			}	
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itas_KKv->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itas_KKv->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itas_KKv->second));
			ame = itas_KKv->second;
		}	
		
		
	}
			

	//// Identifier - Attribute - Value ( K_K_K )////
			
	if( !pMainFrame->gmmAS_K_K_K.empty() )
	{
		//tstring str = id + attr + m_Val;
		//int iVal = UNDEFINE;
		//int AS_iVal = UNDEFINE;

		double dVal = UNDEFINE;
		double AS_dVal = UNDEFINE;
		
		
		
		CMainFrame::g_mmAS_K_K_K::iterator itas_KKK;
		
		for(itas_KKK = pMainFrame->gmmAS_K_K_K.begin(); itas_KKK != pMainFrame->gmmAS_K_K_K.end(); ++itas_KKK)
		{	
			tstring key = itas_KKK->first;
			int pos1 = key.find_first_of(_T("|"));
			int pos2 = key.find_last_of(_T("|"));
			int aSize = pos2 - pos1 -1;

			tstring sId = key.substr(0, pos1);
			tstring sAttr = key.substr(pos1 + 1, aSize);
			tstring sVal = key.substr(pos2 + 1, key.length());
			
			/*
			AfxMessageBox(sId.data());
			AfxMessageBox(sAttr.data());
			AfxMessageBox(sVal.data());
			*/
			
			if( sId == id  && sAttr == attr )
			{
			
				if( isNumber(val) == true)
				{
					//iVal = _ttoi(val.data());
					//AS_Val = _ttoi(sVal.data());
					dVal = _tcstod(val.data(), NULL);
					AS_dVal = _tcstod(sVal.data(), NULL);


				}
				
							
				/*
				TCHAR buff[8];
				CString sGT_Val = _itot(GT_iVal, buff, 10);
				CString siVal =_itot(iVal,buff, 10);
				AfxMessageBox(_T("sGT_Val :"));
				AfxMessageBox(sGT_Val);
				AfxMessageBox(_T("siVal :"));
				AfxMessageBox(siVal);
				*/

				//if( iVal == AS_iVal || val == sVal)
				if( dVal == AS_dVal || val == sVal )
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itas_KKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itas_KKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itas_KKK->second));
					ame = itas_KKK->second;
				}
			}
		}
				
	}
			
		
	//// Empty - Empty - Empty ( ID_AT_VL )////
			
	if ( !pMainFrame->gmmAS_I_A_V.empty())
	{
		
		CMainFrame::g_mmAS_I_A_V::iterator itas_IAV;
		
		for(itas_IAV = pMainFrame->gmmAS_I_A_V.begin(); itas_IAV != pMainFrame->gmmAS_I_A_V.end(); ++itas_IAV)
		{	
			
			/*
			TCHAR buff[8];
			CString sGT_Val = _itot(GT_iVal, buff, 10);
			CString siVal =_itot(iVal,buff, 10);
			AfxMessageBox(_T("sGT_Val :"));
			AfxMessageBox(sGT_Val);
			AfxMessageBox(_T("siVal :"));
			AfxMessageBox(siVal);
			*/

			pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(itas_IAV->second , wm));
			pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, itas_IAV->second));
			//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, itas_IAV->second));
			ame = itas_IAV->second;
			
		}
			
	}
		

return ame;

}






/*
void CAipi_RETE_AM::insertAllWM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_WM wmo;
		
	
	for( CMainFrame::g_mWM::const_iterator it = pMainFrame->gmWM.begin(); it != pMainFrame->gmWM.end(); ++it)
	{
				
		wmo.findWMMembers(it->first);
		//// *** EQUALITY TEST **** //// 
		
		//// Empty - Empty - Value  ( ID_AT_K )////
		
			CMainFrame::g_mmEQ_I_A_K::iterator it_iaK;
			if( !pMainFrame->gmmEQ_I_A_K.empty())
			{
			
				pair <CMainFrame::g_mmEQ_I_A_K::iterator, CMainFrame::g_mmEQ_I_A_K::iterator>  piaK;
				piaK = pMainFrame->gmmEQ_I_A_K.equal_range(wmo.m_Val);

				for(it_iaK = piaK.first; it_iaK != piaK.second; ++it_iaK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iaK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iaK->second));
				}
				
			}

			
		
		//// Empty - Attribute - Empty ( ID_K_VL )////
			
			CMainFrame::g_mmEQ_I_K_V::iterator it_iKv;
			if( !pMainFrame->gmmEQ_I_K_V.empty() )
			{
				pair <CMainFrame::g_mmEQ_I_K_V::iterator, CMainFrame::g_mmEQ_I_K_V::iterator>  piKv;
				piKv = pMainFrame->gmmEQ_I_K_V.equal_range(wmo.m_Attr);

				for(it_iKv = piKv.first; it_iKv != piKv.second; ++it_iKv)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iKv->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iKv->second));
				}
				
			}
			
		
		//// Empty - Attribute - Value ( ID_K_K )////
			
			CMainFrame::g_mmEQ_I_K_K::iterator it_iKK;
			if( !pMainFrame->gmmEQ_I_K_K.empty() )
			{
				tstring str = wmo.m_Attr + wmo.m_Val;

				pair <CMainFrame::g_mmEQ_I_K_K::iterator, CMainFrame::g_mmEQ_I_K_K::iterator>  piKK;
				piKK = pMainFrame->gmmEQ_I_K_K.equal_range(str);

				for(it_iKK = piKK.first; it_iKK != piKK.second; ++it_iKK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iKK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iKK->second));
				}
			}
					
		
		
		//// Identifier - Empty - Empty ( K_AT_VL )////
			
			CMainFrame::g_mmEQ_K_A_V::iterator it_Kav;
			if( !pMainFrame->gmmEQ_K_A_V.empty() )
			{
				pair <CMainFrame::g_mmEQ_K_A_V::iterator, CMainFrame::g_mmEQ_K_A_V::iterator>  pKav;
				pKav = pMainFrame->gmmEQ_K_A_V.equal_range(wmo.m_Id);

				for(it_Kav = pKav.first; it_Kav != pKav.second; ++it_Kav)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_Kav->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_Kav->second));
				}
				
			}
			
		
		//// Identifier - Empty - Value (K_AT_K )////
			
			
			CMainFrame::g_mmEQ_K_A_K::iterator it_KaK;
			if ( !pMainFrame->gmmEQ_K_A_K.empty() )
			{
				tstring str = wmo.m_Id + wmo.m_Val;
				
				pair <CMainFrame::g_mmEQ_K_A_K::iterator, CMainFrame::g_mmEQ_K_A_K::iterator>  pKaK;
				pKaK = pMainFrame->gmmEQ_K_A_K.equal_range(str);

				for(it_KaK = pKaK.first; it_KaK != pKaK.second; ++it_KaK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KaK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_KaK->second));
				}
				
			}
			

		//// Identifier - Attribute - Empty ( K_K_VL )////
			
			CMainFrame::g_mmEQ_K_K_V::iterator it_KKv;
			if( !pMainFrame->gmmEQ_K_K_V.empty() )
			{
				tstring str = wmo.m_Id + wmo.m_Attr;
				
				pair <CMainFrame::g_mmEQ_K_K_V::iterator, CMainFrame::g_mmEQ_K_K_V::iterator>  pKKv;
				pKKv = pMainFrame->gmmEQ_K_K_V.equal_range(str);

				for(it_KKv = pKKv.first; it_KKv != pKKv.second; ++it_KKv)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KKv->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_KKv->second));
				}
				
			}
			

		//// Identifier - Attribute - Value ( K_K_K )////
			
			CMainFrame::g_mmEQ_K_K_K::iterator it_KKK;
			if( !pMainFrame->gmmEQ_K_K_K.empty() )
			{
				tstring str = wmo.m_Id + wmo.m_Attr + wmo.m_Val;
				
				pair <CMainFrame::g_mmEQ_K_K_K::iterator, CMainFrame::g_mmEQ_K_K_K::iterator>  pKKK;
				pKKK = pMainFrame->gmmEQ_K_K_K.equal_range(str);

				for(it_KKK = pKKK.first; it_KKK != pKKK.second; ++it_KKK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KKK->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_KKK->second));
				}
				
			}
			
		
		//// Empty - Empty - Empty ( ID_AT_VL )////
			
			CMainFrame::g_mmEQ_I_A_V::iterator it_iav;
			if ( !pMainFrame->gmmEQ_I_A_V.empty())
			{
				pair <CMainFrame::g_mmEQ_I_A_V::iterator, CMainFrame::g_mmEQ_I_A_V::iterator>  piav;
				piav = pMainFrame->gmmEQ_I_A_V.equal_range(_T("e"));

				for(it_iav = piav.first; it_iav != piav.second; ++it_iav)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iav->second , it->first));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(it->first, it_iav->second));
				}
				
			}
		
	}

}

*/

int CAipi_RETE_AM::insertWM(int wm)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_WM wmo;
	bool empty =  true;
	int am = NOT_FOUND;
	
		wmo.findWMMembers(wm);
		
		

		//// Empty - Empty - Value  ( ID_AT_K )////
		
			CMainFrame::g_mmEQ_I_A_K::iterator it_iaK;
			empty = pMainFrame->gmmEQ_I_A_K.empty();
			if(empty == false )	
			{
			    
				pair <CMainFrame::g_mmEQ_I_A_K::iterator, CMainFrame::g_mmEQ_I_A_K::iterator>  piaK;
				piaK = pMainFrame->gmmEQ_I_A_K.equal_range(wmo.m_Val);

				for(it_iaK = piaK.first; it_iaK != piaK.second; ++it_iaK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iaK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, it_iaK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, it_iaK->second));

					am = it_iaK->second;

					
					
					//if(am != NOT_FOUND)
					//return am;
					
				}

				
				
			}

			
		
		//// Empty - Attribute - Empty ( ID_K_VL )////
			
			CMainFrame::g_mmEQ_I_K_V::iterator it_iKv;
			empty = pMainFrame->gmmEQ_I_K_V.empty();
			

			if(empty == false )	
			{
				
				pair <CMainFrame::g_mmEQ_I_K_V::iterator, CMainFrame::g_mmEQ_I_K_V::iterator>  piKv;
				piKv = pMainFrame->gmmEQ_I_K_V.equal_range(wmo.m_Attr);

				for(it_iKv = piKv.first; it_iKv != piKv.second; ++it_iKv)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iKv->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, it_iKv->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, it_iKv->second));
					am = it_iKv->second;

					/*

					CString str;
					str.Format(_T("Alpha Memory...%d  " ), it_iKv->second);
					AfxMessageBox(str);
					*/	
					//if(am != NOT_FOUND)
					//return am;
					
				}
				
				
			}
			
		
		//// Empty - Attribute - Value ( ID_K_K )////
			
			CMainFrame::g_mmEQ_I_K_K::iterator it_iKK;
			
			//AfxMessageBox(str.data());
			empty = pMainFrame->gmmEQ_I_K_K.empty();
			if(empty == false )	
			{
				tstring str = wmo.m_Attr + wmo.m_Val;

				pair <CMainFrame::g_mmEQ_I_K_K::iterator, CMainFrame::g_mmEQ_I_K_K::iterator>  piKK;
				piKK = pMainFrame->gmmEQ_I_K_K.equal_range(str);

				for(it_iKK = piKK.first; it_iKK != piKK.second; ++it_iKK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, it_iKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, it_iKK->second));
					am = it_iKK->second;
					
					/*
					CString str;
					str.Format(_T("AM...%d  " ), it_iKK->second);
					AfxMessageBox(str);
					*/

					//if(am != NOT_FOUND)
					//return am;
					
				}
				
				
				
				
			}
					
		
		
		//// Identifier - Empty - Empty ( K_AT_VL )////
			
			CMainFrame::g_mmEQ_K_A_V::iterator it_Kav;
			empty = pMainFrame->gmmEQ_K_A_V.empty();
			if(empty == false )	
			{
				pair <CMainFrame::g_mmEQ_K_A_V::iterator, CMainFrame::g_mmEQ_K_A_V::iterator>  pKav;
				pKav = pMainFrame->gmmEQ_K_A_V.equal_range(wmo.m_Id);

				for(it_Kav = pKav.first; it_Kav != pKav.second; ++it_Kav)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_Kav->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, it_Kav->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, it_Kav->second));
					am = it_Kav->second;
					//if(am != NOT_FOUND)
					//return am;
					
				}
				
				
				
			}
			
		
		//// Identifier - Empty - Value (K_AT_K )////
			
			
			CMainFrame::g_mmEQ_K_A_K::iterator it_KaK;
			
			
			empty = pMainFrame->gmmEQ_K_A_K.empty();
			if(empty == false )	
			{
				tstring str = wmo.m_Id + wmo.m_Val;

				pair <CMainFrame::g_mmEQ_K_A_K::iterator, CMainFrame::g_mmEQ_K_A_K::iterator>  pKaK;
				pKaK = pMainFrame->gmmEQ_K_A_K.equal_range(str);

				for(it_KaK = pKaK.first; it_KaK != pKaK.second; ++it_KaK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KaK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, it_KaK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, it_KaK->second));
					am = it_KaK->second;

				

					//if(am != NOT_FOUND)
					//return am;

				}
				
				
					

			}
			

		//// Identifier - Attribute - Empty ( K_K_VL )////
			
			CMainFrame::g_mmEQ_K_K_V::iterator it_KKv;
			
			empty = pMainFrame->gmmEQ_K_K_V.empty();
			if(empty == false )	
			{
				tstring str = wmo.m_Id + wmo.m_Attr;

				pair <CMainFrame::g_mmEQ_K_K_V::iterator, CMainFrame::g_mmEQ_K_K_V::iterator>  pKKv;
				pKKv = pMainFrame->gmmEQ_K_K_V.equal_range(str);

				for(it_KKv = pKKv.first; it_KKv != pKKv.second; ++it_KKv)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KKv->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, it_KKv->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, it_KKv->second));
					am = it_KKv->second;
					//if(am != NOT_FOUND)
					//return am;
					
				}
				
				
				
				
			}
			

		//// Identifier - Attribute - Value ( K_K_K )////
			
			CMainFrame::g_mmEQ_K_K_K::iterator it_KKK;
			
			empty = pMainFrame->gmmEQ_K_K_K.empty();
			if(empty == false )	
			{
				tstring str = wmo.m_Id + wmo.m_Attr + wmo.m_Val;

				pair <CMainFrame::g_mmEQ_K_K_K::iterator, CMainFrame::g_mmEQ_K_K_K::iterator>  pKKK;
				pKKK = pMainFrame->gmmEQ_K_K_K.equal_range(str);

				for(it_KKK = pKKK.first; it_KKK != pKKK.second; ++it_KKK)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_KKK->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, it_KKK->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, it_KKK->second));
					am = it_KKK->second;
					//if(am != NOT_FOUND)
					//return am;
				}
				
				
				
				
			}
			
		
		//// Empty - Empty - Empty ( ID_AT_VL )////
			
			CMainFrame::g_mmEQ_I_A_V::iterator it_iav;
		
			empty = pMainFrame->gmmEQ_I_A_V.empty();
			if(empty == false )	
			{
				pair <CMainFrame::g_mmEQ_I_A_V::iterator, CMainFrame::g_mmEQ_I_A_V::iterator>  piav;
				piav = pMainFrame->gmmEQ_I_A_V.equal_range(_T("e"));

				for(it_iav = piav.first; it_iav != piav.second; ++it_iav)
				{	
					pMainFrame->gmmAM_WM.insert(CMainFrame::g_mmAM_WM::value_type(it_iav->second , wm));
					pMainFrame->gmmWM_AM.insert(CMainFrame::g_mmWM_AM::value_type(wm, it_iav->second));
					//pMainFrame->gmWM_AM.insert(CMainFrame::g_mWM_AM::value_type(wm, it_iav->second));
					am = it_iav->second;
					//if(am != NOT_FOUND)
					//return am;
				}
				
				
				
				
			}
			
			
return am;			

			

}




void CAipi_RETE_AM::clearAMStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmAM_WM.clear();
	pMainFrame->gmmWM_AM.clear();
	//pMainFrame->gmWM_AM.clear();
	pMainFrame->gmmAM_Cond.clear();
	pMainFrame->gmCond_AM.clear();
	
}


void CAipi_RETE_AM::clearLogicStructs()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	//"Equal Than" Structs
	pMainFrame->gmmEQ_I_A_K.clear();
	pMainFrame->gmmEQ_I_A_V.clear();
	pMainFrame->gmmEQ_I_K_K.clear();
	pMainFrame->gmmEQ_I_K_V.clear();
	pMainFrame->gmmEQ_K_A_K.clear();
	pMainFrame->gmmEQ_K_A_V.clear();
	pMainFrame->gmmEQ_K_K_K.clear();
	pMainFrame->gmmEQ_K_K_V.clear();
	//"Non Equal" Structs	
	pMainFrame->gmmNE_I_A_K.clear();
	pMainFrame->gmmNE_I_A_V.clear();
	pMainFrame->gmmNE_I_K_K.clear();
	pMainFrame->gmmNE_I_K_V.clear();
	pMainFrame->gmmNE_K_A_K.clear();
	pMainFrame->gmmNE_K_A_V.clear();
	pMainFrame->gmmNE_K_K_K.clear();
	pMainFrame->gmmNE_K_K_V.clear();
	//"Less Than" Structs	
	pMainFrame->gmmLT_I_A_K.clear();
	pMainFrame->gmmLT_I_A_V.clear();
	pMainFrame->gmmLT_I_K_K.clear();
	pMainFrame->gmmLT_I_K_V.clear();
	pMainFrame->gmmLT_K_A_K.clear();
	pMainFrame->gmmLT_K_A_V.clear();
	pMainFrame->gmmLT_K_K_K.clear();
	pMainFrame->gmmLT_K_K_V.clear();
	//"Less or Equal Than" Structs	
	pMainFrame->gmmLE_I_A_K.clear();
	pMainFrame->gmmLE_I_A_V.clear();
	pMainFrame->gmmLE_I_K_K.clear();
	pMainFrame->gmmLE_I_K_V.clear();
	pMainFrame->gmmLE_K_A_K.clear();
	pMainFrame->gmmLE_K_A_V.clear();
	pMainFrame->gmmLE_K_K_K.clear();
	pMainFrame->gmmLE_K_K_V.clear();
	//"Greater Than" Structs	
	pMainFrame->gmmGT_I_A_K.clear();
	pMainFrame->gmmGT_I_A_V.clear();
	pMainFrame->gmmGT_I_K_K.clear();
	pMainFrame->gmmGT_I_K_V.clear();
	pMainFrame->gmmGT_K_A_K.clear();
	pMainFrame->gmmGT_K_A_V.clear();
	pMainFrame->gmmGT_K_K_K.clear();
	pMainFrame->gmmGT_K_K_V.clear();
	//"Greater or Equal Than" Structs	
	pMainFrame->gmmGE_I_A_K.clear();
	pMainFrame->gmmGE_I_A_V.clear();
	pMainFrame->gmmGE_I_K_K.clear();
	pMainFrame->gmmGE_I_K_V.clear();
	pMainFrame->gmmGE_K_A_K.clear();
	pMainFrame->gmmGE_K_A_V.clear();
	pMainFrame->gmmGE_K_K_K.clear();
	pMainFrame->gmmGE_K_K_V.clear();
				

}





void CAipi_RETE_AM::constantTestCond(int c)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_LHS lhso;
	int LHSCategory = K_K_K;		

		if( lhso.findLHSMembers(c))
		{
			
			m_Id	= lhso.m_Id;
			m_Attr	= lhso.m_Attr;
			m_Val	= lhso.m_Val;
			LHSCategory = lhso.m_Category;

			//ID_AT_K
			//if((m_Id.substr(0,1) == _T("[")) && (m_Attr.substr(0,1) == _T("[")) && (m_Val.substr(0,1) != _T("[")) )
			//{
			if( LHSCategory == ID_AT_K )
			{
				
				if( !pMainFrame->gmmEQ_I_A_K.empty() )
				{	
					CMainFrame::g_mmEQ_I_A_K::iterator iter;
					iter = pMainFrame->gmmEQ_I_A_K.find(m_Val);
					if( iter == pMainFrame->gmmEQ_I_A_K.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_I_A_K.insert(CMainFrame::g_mmEQ_I_A_K::value_type( m_Val, key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
						
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_I_A_K.insert(CMainFrame::g_mmEQ_I_A_K::value_type( m_Val, key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				}
			
			}//ID_K_VL
	
			//else if((m_Id.substr(0,1) == _T("[")) && (m_Attr.substr(0,1) != _T("[")) && (m_Val.substr(0,1) == _T("[")) )
			else if( LHSCategory == ID_K_VL )
			{	
				
				if( !pMainFrame->gmmEQ_I_K_V.empty() )
				{
					CMainFrame::g_mmEQ_I_K_V::iterator iter;
					iter = pMainFrame->gmmEQ_I_K_V.find(m_Attr);
					if( iter == pMainFrame->gmmEQ_I_K_V.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_I_K_V.insert(CMainFrame::g_mmEQ_I_K_V::value_type( m_Attr, key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
						//AfxMessageBox(_T("hola1"));
					
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
						//AfxMessageBox(_T("hola2"));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_I_K_V.insert(CMainFrame::g_mmEQ_I_K_V::value_type( m_Attr, key ));	
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
					//AfxMessageBox(_T("hola3"));
				}	
								
			}//ID_K_K

			
			//else if((m_Id.substr(0,1) == _T("[")) && (m_Attr.substr(0,1) != _T("[")) && (m_Val.substr(0,1) != _T("[")) )
			else if ( LHSCategory == ID_K_K )
			{
				tstring str = m_Attr + _T("|") + m_Val;
												
				if( !pMainFrame->gmmEQ_I_K_K.empty() )
				{
					
					CMainFrame::g_mmEQ_I_K_K::iterator iter;
					iter = pMainFrame->gmmEQ_I_K_K.find(str);
					if( iter == pMainFrame->gmmEQ_I_K_K.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_I_K_K.insert(CMainFrame::g_mmEQ_I_K_K::value_type(str, key ));	
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
					}	
				}	
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_I_K_K.insert(CMainFrame::g_mmEQ_I_K_K::value_type(str, key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				}
				
				
			}//K_AT_VL

		
			//else if((m_Id.substr(0,1) != _T("[")) && (m_Attr.substr(0,1) == _T("[")) && (m_Val.substr(0,1) == _T("[")) )
			else if ( LHSCategory == K_AT_VL )
			{
				
				if( !pMainFrame->gmmEQ_K_A_V.empty() )
				{
					CMainFrame::g_mmEQ_K_A_V::iterator iter;
					iter = pMainFrame->gmmEQ_K_A_V.find(m_Id);
					if( iter == pMainFrame->gmmEQ_K_A_V.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_K_A_V.insert(CMainFrame::g_mmEQ_K_A_V::value_type( m_Id, key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
					}
					else
					{	
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_K_A_V.insert(CMainFrame::g_mmEQ_K_A_V::value_type( m_Id, key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				}
				
			}//K_AT_K
			//else if((m_Id.substr(0,1) != _T("[")) && (m_Attr.substr(0,1) == _T("[")) && (m_Val.substr(0,1) != _T("[")) )
			else if( LHSCategory == K_AT_K )
			{
				
				tstring str = m_Id + m_Val;
				
				if( !pMainFrame->gmmEQ_K_A_K.empty() )
				{
					CMainFrame::g_mmEQ_K_A_K::iterator iter;
					iter = pMainFrame->gmmEQ_K_A_K.find(str);
					if( iter == pMainFrame->gmmEQ_K_A_K.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_K_A_K.insert(CMainFrame::g_mmEQ_K_A_K::value_type( str, key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_K_A_K.insert(CMainFrame::g_mmEQ_K_A_K::value_type( str, key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				}

			}//K_K_VL
			//else if((m_Id.substr(0,1) != _T("[")) && (m_Attr.substr(0,1) != _T("[")) && (m_Val.substr(0,1) == _T("[")) )
			else if ( LHSCategory == K_K_VL )
			{
				
				tstring str = m_Id + m_Attr;
				
				if( !pMainFrame->gmmEQ_K_K_V.empty() )
				{
					CMainFrame::g_mmEQ_K_K_V::iterator iter;
					iter = pMainFrame->gmmEQ_K_K_V.find(str);
					if( iter == pMainFrame->gmmEQ_K_K_V.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_K_K_V.insert(CMainFrame::g_mmEQ_K_K_V::value_type(str, key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_K_K_V.insert(CMainFrame::g_mmEQ_K_K_V::value_type(str, key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				}
				
			}//K_K_K
			//else if ((m_Id.substr(0,1) != _T("[")) && (m_Attr.substr(0,1) != _T("[")) && (m_Val.substr(0,1) != _T("[")) )
			else if( LHSCategory == K_K_K )
			{	
				tstring str = m_Id + m_Attr + m_Val;
				
				if( !pMainFrame->gmmEQ_K_K_K.empty() )
				{
					CMainFrame::g_mmEQ_K_K_K::iterator iter;
					iter = pMainFrame->gmmEQ_K_K_K.find(str);
				
					if( iter == pMainFrame->gmmEQ_K_K_K.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_K_K_K.insert(CMainFrame::g_mmEQ_K_K_K::value_type( str , key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_K_K_K.insert(CMainFrame::g_mmEQ_K_K_K::value_type( str , key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				}
				
			}//ID_AT_VL
			else
			{
				if( !pMainFrame->gmmEQ_I_A_V.empty() )
				{
					CMainFrame::g_mmEQ_I_A_V::iterator iter;
					iter = pMainFrame->gmmEQ_I_A_V.find(_T("e"));
					if( iter == pMainFrame->gmmEQ_I_A_V.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_I_A_V.insert(CMainFrame::g_mmEQ_I_A_V::value_type( _T("e"), key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_I_A_V.insert(CMainFrame::g_mmEQ_I_A_V::value_type( _T("e"), key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				}
				
		  }
		
		  
	}
	
	

}






void CAipi_RETE_AM::constantTestAllCond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_LHS lhso;
			
	for( CMainFrame::g_mLHS::const_iterator itc = pMainFrame->gmLHS.begin(); itc!= pMainFrame->gmLHS.end(); ++itc)
	{	
			lhso = (CAipi_LHS)itc->second;
 			m_Id =		lhso.getId();
			m_Attr =	lhso.getAttr();
			m_Val =		lhso.getVal();
			m_Rel =		lhso.getRel();
			

			
			//ID_AT_K
			if((m_Id.substr(0,1) == _T("[")) && (m_Attr.substr(0,1) == _T("[")) && (m_Val.substr(0,1) != _T("[")) )
			{
				
				if( !pMainFrame->gmmEQ_I_A_K.empty() )
				{	
					CMainFrame::g_mmEQ_I_A_K::iterator iter;
					iter = pMainFrame->gmmEQ_I_A_K.find(m_Val);
					if( iter == pMainFrame->gmmEQ_I_A_K.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_I_A_K.insert(CMainFrame::g_mmEQ_I_A_K::value_type( m_Val, key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
						
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, itc->first));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_I_A_K.insert(CMainFrame::g_mmEQ_I_A_K::value_type( m_Val, key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
				}
			
			}//ID_K_VL
	
			else if((m_Id.substr(0,1) == _T("[")) && (m_Attr.substr(0,1) != _T("[")) && (m_Val.substr(0,1) == _T("[")) )
			{	
				
				if( !pMainFrame->gmmEQ_I_K_V.empty() )
				{
					CMainFrame::g_mmEQ_I_K_V::iterator iter;
					iter = pMainFrame->gmmEQ_I_K_V.find(m_Attr);
					if( iter == pMainFrame->gmmEQ_I_K_V.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_I_K_V.insert(CMainFrame::g_mmEQ_I_K_V::value_type( m_Attr, key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
						//AfxMessageBox(_T("hola1"));
					
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, itc->first));
						//AfxMessageBox(_T("hola2"));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_I_K_V.insert(CMainFrame::g_mmEQ_I_K_V::value_type( m_Attr, key ));	
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
					//AfxMessageBox(_T("hola3"));
				}	
								
			}//ID_K_K

			
			else if((m_Id.substr(0,1) == _T("[")) && (m_Attr.substr(0,1) != _T("[")) && (m_Val.substr(0,1) != _T("[")) )
			{
				tstring str = m_Attr + _T("|") + m_Val;
												
				if( !pMainFrame->gmmEQ_I_K_K.empty() )
				{
					
					CMainFrame::g_mmEQ_I_K_K::iterator iter;
					iter = pMainFrame->gmmEQ_I_K_K.find(str);
					if( iter == pMainFrame->gmmEQ_I_K_K.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_I_K_K.insert(CMainFrame::g_mmEQ_I_K_K::value_type(str, key ));	
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, itc->first));
					}	
				}	
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_I_K_K.insert(CMainFrame::g_mmEQ_I_K_K::value_type(str, key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
				}
				
				
			}//K_AT_VL

		
			else if((m_Id.substr(0,1) != _T("[")) && (m_Attr.substr(0,1) == _T("[")) && (m_Val.substr(0,1) == _T("[")) )
			{
				
				if( !pMainFrame->gmmEQ_K_A_V.empty() )
				{
					CMainFrame::g_mmEQ_K_A_V::iterator iter;
					iter = pMainFrame->gmmEQ_K_A_V.find(m_Id);
					if( iter == pMainFrame->gmmEQ_K_A_V.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_K_A_V.insert(CMainFrame::g_mmEQ_K_A_V::value_type( m_Id, key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
					}
					else
					{	
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, itc->first));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_K_A_V.insert(CMainFrame::g_mmEQ_K_A_V::value_type( m_Id, key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
				}
				
			}//K_AT_K
			else if((m_Id.substr(0,1) != _T("[")) && (m_Attr.substr(0,1) == _T("[")) && (m_Val.substr(0,1) != _T("[")) )
			{
				
				tstring str = m_Id + _T("|") + m_Val;
				
				if( !pMainFrame->gmmEQ_K_A_K.empty() )
				{
					CMainFrame::g_mmEQ_K_A_K::iterator iter;
					iter = pMainFrame->gmmEQ_K_A_K.find(str);
					if( iter == pMainFrame->gmmEQ_K_A_K.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_K_A_K.insert(CMainFrame::g_mmEQ_K_A_K::value_type( str, key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, itc->first));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_K_A_K.insert(CMainFrame::g_mmEQ_K_A_K::value_type( str, key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
				}

			}//K_K_VL
			else if((m_Id.substr(0,1) != _T("[")) && (m_Attr.substr(0,1) != _T("[")) && (m_Val.substr(0,1) == _T("[")) )
			{
				
				tstring str = m_Id + _T("|") + m_Attr;
				
				if( !pMainFrame->gmmEQ_K_K_V.empty() )
				{
					CMainFrame::g_mmEQ_K_K_V::iterator iter;
					iter = pMainFrame->gmmEQ_K_K_V.find(str);
					if( iter == pMainFrame->gmmEQ_K_K_V.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_K_K_V.insert(CMainFrame::g_mmEQ_K_K_V::value_type(str, key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, itc->first));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_K_K_V.insert(CMainFrame::g_mmEQ_K_K_V::value_type(str, key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
				}
				
			}//K_K_K
			else if ((m_Id.substr(0,1) != _T("[")) && (m_Attr.substr(0,1) != _T("[")) && (m_Val.substr(0,1) != _T("[")) )
			{	
				tstring str = m_Id + _T("|") + m_Attr + _T("|") + m_Val;
				
				if( !pMainFrame->gmmEQ_K_K_K.empty() )
				{
					CMainFrame::g_mmEQ_K_K_K::iterator iter;
					iter = pMainFrame->gmmEQ_K_K_K.find(str);
				
					if( iter == pMainFrame->gmmEQ_K_K_K.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_K_K_K.insert(CMainFrame::g_mmEQ_K_K_K::value_type( str , key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, itc->first));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_K_K_K.insert(CMainFrame::g_mmEQ_K_K_K::value_type( str , key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
				}
				
			}//ID_AT_VL
			else
			{
				if( !pMainFrame->gmmEQ_I_A_V.empty() )
				{
					CMainFrame::g_mmEQ_I_A_V::iterator iter;
					iter = pMainFrame->gmmEQ_I_A_V.find(_T("e"));
					if( iter == pMainFrame->gmmEQ_I_A_V.end())
					{
						int key = generateAMKey();
						pMainFrame->gmmEQ_I_A_V.insert(CMainFrame::g_mmEQ_I_A_V::value_type( _T("e"), key ));
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
					}
					else
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, iter->second));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, itc->first));
					}
				}
				else
				{
					int key = generateAMKey();
					pMainFrame->gmmEQ_I_A_V.insert(CMainFrame::g_mmEQ_I_A_V::value_type( _T("e"), key ));
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(itc->first, key));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,itc->first));
				}
				
		  }
		
		  
	
	}
	

}


void CAipi_RETE_AM::fillPM_Vars(int pm)
{

	
	CAipi_PM pmo;

	int static cont = 0;
	cont++;
	int n = pmo.countPM_Cond(pm);
/*
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  n PM Elements *******"));
	strN +=  _itot( n, buffer, 10 );
	pMainFrame->m_wndOutputTabView.AddMsg1(strN);
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Cont *******"));
	strC +=  _itot( cont, buffer, 10 );
	pMainFrame->m_wndOutputTabView.AddMsg1(strC);
	pMainFrame->m_wndOutputTabView.AddMsg1(id.data());
*/	
	if( cont == n )
	{
		cont = 0;
		pmo.fillPM_Vars(pm);
		/*
		CAipi_RETE_Vars varo;
		varo.printSetIDVar();
		varo.printSetVALVar();
		*/
	}

}



void CAipi_RETE_AM::updateRelAM(int pm)
{
	//AfxMessageBox(_T("Update AM"));
	
	
	CAipi_LHS lhso;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pair <CMainFrame::g_mmPM_RelCond::iterator, CMainFrame::g_mmPM_RelCond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_RelCond.equal_range(pm);
	
	for(CMainFrame::g_mmPM_RelCond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		int rel_c = it_PM->second;
		tstring id_var = lhso.findLHSId(rel_c);
		 if ( isVariable(id_var) == true )
		 {
			
			int c = lhso.searchLHS_PMValAfterCond(pm, id_var, rel_c);
			int am = findCond_AM(c);
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(rel_c, am));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(am, rel_c));

			/*
			CString st;
			st.Format(_T("Cond...%d  " ), c);
			AfxMessageBox(st);
			st.Format(_T("Alpha Memory...%d  " ), am);
			AfxMessageBox(st);
			*/

		 }
		 else
		 {
			tstring val_var = lhso.findLHSVal(rel_c);
			if ( isVariable(val_var) == true )
			{
				int c = lhso.searchLHS_PMValAfterCond(pm, val_var, rel_c);
				int am = findCond_AM(c);
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(rel_c, am));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(am, rel_c));

			}

		 }
	}


}

void CAipi_RETE_AM::updateRelAMIForm(int pm)
{
	//AfxMessageBox(_T("Update AM"));
	
	
	CAipi_LHS lhso;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pair <CMainFrame::g_mmPM_RelCond::iterator, CMainFrame::g_mmPM_RelCond::iterator>  pPM;
	pPM = pMainFrame->gmmPM_RelCond.equal_range(pm);
	
	for(CMainFrame::g_mmPM_RelCond::iterator it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		int rel_c = it_PM->second;
		lhso.findLHSMembers(rel_c);
		tstring id_var = lhso.m_Id;
		int categ = lhso.m_Category;

		if ( categ == ID_AT_VL || categ == ID_K_VL || categ == ID_AT_K || categ == ID_K_K  )
		 {
			
			int c = lhso.searchLHS_PMValAfterCond(pm, id_var, rel_c);
			if( c != NOT_FOUND )
			{
				int am = findCond_AM(c);
				if( am != NOT_FOUND )
				{
					pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(rel_c, am));
					pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(am, rel_c));

					/*
					CString st;
					st.Format(_T("Cond...%d  " ), c);
					AfxMessageBox(st);
					st.Format(_T("Alpha Memory...%d  " ), am);
					AfxMessageBox(st);
					*/
				}
			
			}
			
			

		 }
		 else
		 {
			tstring val_var = lhso.findLHSVal(rel_c);
			if ( isVariable(val_var) == true )
			{
				int c = lhso.searchLHS_PMValAfterCond(pm, val_var, rel_c);
				if( c != NOT_FOUND )
				{
					int am = findCond_AM(c);
					if( am != NOT_FOUND )
					{
						pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(rel_c, am));
						pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(am, rel_c));

						/*
						CString st;
						st.Format(_T("Cond...%d  " ), c);
						AfxMessageBox(st);
						st.Format(_T("Alpha Memory...%d  " ), am);
						AfxMessageBox(st);
						*/
					}
				}
			

			}

		 }
	}


}





void CAipi_RETE_AM::constantTest()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_LHS lhso;
	CAipi_RETE_Operations opo;
	CAipi_RepCond rco;
	CAipi_PM  pmo;

	//Key	= Variable Name
	//Val	= Type
	typedef std::map<tstring, int> l_mVar_Type;
	l_mVar_Type	 lmVar_Type;
	int tempPM = 0;
	int tempPostPM = 0;
	
	for( CMainFrame::g_mLHS::const_iterator itc = pMainFrame->gmLHS.begin(); itc!= pMainFrame->gmLHS.end(); ++itc)
	{	
			lhso = (CAipi_LHS)itc->second;
			tstring id			= lhso.getId();
			tstring attr		= lhso.getAttr();
			tstring val			= lhso.getVal();
			int		rel			= lhso.getRel();
			int		pm			= lhso.getPM();
			int		categ		= lhso.getCategory();

			int		c		= itc->first;

			
			if( pm == tempPostPM )
			{
				updateRelAM(pm-1);
			}
			
			if( pm > tempPM )
			{

				tempPM = pm;
				tempPostPM = pm + 1;

			}
			
			rco.saveRepeatedCond(id, attr, val, c, pm);
			 	

			if( rel != EQ  )
			{
				int type = opo.findAttr_Type(attr);
				if( type == NOT_FOUND )
				{
					//If the relational condition is the first condition in the production 
					int id_c = lhso.searchLHS_PMValAfterCond(pm, id, c);
					tstring at_c = lhso.findLHSAttr(id_c);
					type = opo.findAttr_Type(at_c);
					lmVar_Type.insert(l_mVar_Type::value_type(id, type));
					
					int val_c = lhso.searchLHS_PMValAfterCond(pm, val, c);
					at_c = lhso.findLHSAttr(val_c);
					type = opo.findAttr_Type(at_c);
					lmVar_Type.insert(l_mVar_Type::value_type(val, type));
					
				}
				
							
				
				
			}
										
			if( categ == ID_RO_K || categ == ID_RO_VL || categ == K_RO_K || categ == K_RO_VL )
			{
				if( tempPM == pm)
				{
					
					l_mVar_Type::iterator iter;
					
					iter = lmVar_Type.find(id);
					int type1 = iter->second;
 					
					iter = lmVar_Type.find(val);
					int type2 = iter->second;
 					
					
					
					if( type2 == NOT_FOUND )
					{
						 type2 = isType(val);
						 saveConstDataNum(pm, c, type2, val, val);
						 
						 //AfxMessageBox(_T("Ahora"));
						 //AfxMessageBox(val.data());
				 
					}
					else
					{
						saveConstDataNum(pm, c, type2, val, val);
					}
					
					opo.addOperation(pm, c, id, val, type1, type2, rel);
					
				}
				
			}
			

			switch( rel)
			{
			case EQ : 
					constantTestEQ(c, id, attr, val, pm, categ );
					break;
			case ET : 
					constantTestET(c, id, attr, val, pm, categ );
					pmo.addPM_RelCond(pm, c);
					break;
			case NE :
					constantTestNE(c, id, attr, val, pm, categ );
					pmo.addPM_RelCond(pm, c);
					break;
			case LT : 
					constantTestLT(c, id, attr, val, pm, categ );
					pmo.addPM_RelCond(pm, c);
					break;
			case LE :
					constantTestLE(c, id, attr, val, pm, categ );
					pmo.addPM_RelCond(pm, c);
					break;
			case GT : 
					constantTestGT(c, id, attr, val, pm, categ );
					pmo.addPM_RelCond(pm, c);
					break;
			case GE :
					constantTestGE(c, id, attr, val, pm, categ );
					pmo.addPM_RelCond(pm, c);
					break;
			case AS :
					constantTestAS(c, id, attr, val, pm, categ );
					break;
			default:
					AfxMessageBox(_T("Error in relational operation symbol"));
					break;
			}
				
	
	}

	updateRelAM(tempPM);

}



void CAipi_RETE_AM::constantTestIForm()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_LHS lhso;
	CAipi_RETE_Operations opo;
	CAipi_RepCond rco;
	CAipi_PM  pmo;

	//Key	= Variable Name
	//Val	= Type
	typedef std::map<tstring, int> l_mVar_Type;
	l_mVar_Type	 lmVar_Type;
	int tempPM = 0;
	int tempPostPM = 0;
	
	for( CMainFrame::g_mLHS::const_iterator itc = pMainFrame->gmLHS.begin(); itc!= pMainFrame->gmLHS.end(); ++itc)
	{	
			lhso = (CAipi_LHS)itc->second;
			long	id_iform	= lhso.getIdIForm();
			long    attr_iform	= lhso.getAttrIForm();
			long	val_iform	= lhso.getValIForm();
			tstring id			= lhso.getId();
			tstring attr		= lhso.getAttr();
			tstring val			= lhso.getVal();
			int		rel			= lhso.getRel();
			int		pm			= lhso.getPM();
			int		categ		= lhso.getCategory();

			int		c		= itc->first;

			
			if( pm == tempPostPM )
			{
				updateRelAMIForm(pm-1);
			}
			
			if( pm > tempPM )
			{

				tempPM = pm;
				tempPostPM = pm + 1;

			}
			
			rco.saveRepeatedCondIForm(id_iform, attr_iform, val_iform, c, pm); 	

			//This for conditions when the attribute is a relational operator  
			///?????
			if( rel != EQ  )
			{
				int type = opo.findAttr_Type(attr);
				//There is no type for the attribute element
				if( type == NOT_FOUND )
				{
					//If the relational condition is the first condition in the production 
					int id_c = lhso.searchLHS_PMValAfterCond(pm, id, c);
					tstring at_c = lhso.findLHSAttr(id_c);
					type = opo.findAttr_Type(at_c);
					lmVar_Type.insert(l_mVar_Type::value_type(id, type));
					
					int val_c = lhso.searchLHS_PMValAfterCond(pm, val, c);
					at_c = lhso.findLHSAttr(val_c);
					type = opo.findAttr_Type(at_c);
					lmVar_Type.insert(l_mVar_Type::value_type(val, type));
					
				}
				
							
				
				
			}
			
			//This for conditions when the attribute is a relational operator
			//??????
			if( categ == ID_RO_K || categ == ID_RO_VL || categ == K_RO_K || categ == K_RO_VL )
			{
				if( tempPM == pm)
				{
					
					l_mVar_Type::iterator iter;
					
					iter = lmVar_Type.find(id);
					int type1 = iter->second;
 					
					iter = lmVar_Type.find(val);
					int type2 = iter->second;
 					
					
					
					if( type2 == NOT_FOUND )
					{
						 type2 = isType(val);
						 saveConstDataNum(pm, c, type2, val, val);
						 
						 //AfxMessageBox(_T("Ahora"));
						 //AfxMessageBox(val.data());
				 
					}
					else
					{
						saveConstDataNum(pm, c, type2, val, val);
					}
					
					opo.addOperation(pm, c, id, val, type1, type2, rel);
					
				}
				
			}
			

			switch( rel)
			{
			case EQ : 
					constantTestEQ(c, id, attr, val, pm, categ );
					break;
			case ET : 
					constantTestET(c, id, attr, val, pm, categ );
					pmo.addPM_RelCond(pm, c);
					break;
			case NE :
					constantTestNE(c, id, attr, val, pm, categ );
					pmo.addPM_RelCond(pm, c);
					break;
			case LT : 
					constantTestLT(c, id, attr, val, pm, categ );
					pmo.addPM_RelCond(pm, c);
					break;
			case LE :
					constantTestLE(c, id, attr, val, pm, categ );
					pmo.addPM_RelCond(pm, c);
					break;
			case GT : 
					constantTestGT(c, id, attr, val, pm, categ );
					pmo.addPM_RelCond(pm, c);
					break;
			case GE :
					constantTestGE(c, id, attr, val, pm, categ );
					pmo.addPM_RelCond(pm, c);
					break;
			case AS :
					constantTestAS(c, id, attr, val, pm, categ );
					break;
			default:
					AfxMessageBox(_T("Error in relational operation symbol"));
					break;
			}
				
	
	}

	updateRelAMIForm(tempPM);

}






void CAipi_RETE_AM::constantTestEQ(int c, tstring id, tstring attr, tstring val, int pm, int categ)
{
	//This functions saves the variables of each lhs element.
	//pMainFrame->gsIVar.insert(id);
	//pMainFrame->gsAVar.insert(attr);
	//pMainFrame->gsVVar.insert(attr);
	
	//This process was already made in the parser, Method: emit_rule(AIPI_LHS);
	//So here it is just comment.

	//AfxMessageBox(_T("CONSTANT TEST EQ"));
/*
	CString str;
	str.Format(_T("Category...%d  " ), categ);
	AfxMessageBox(str);
*/	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	
	CAipi_RETE_Vars varo;
	

	//// *** EQUALITY TEST **** //// 	

	//ID_AT_K
	if( categ == ID_AT_K )
	{
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
					
		if( !pMainFrame->gmmEQ_I_A_K.empty() )
		{	
			CMainFrame::g_mmEQ_I_A_K::iterator iter;
			iter = pMainFrame->gmmEQ_I_A_K.find(val);
			if( iter == pMainFrame->gmmEQ_I_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmEQ_I_A_K.insert(CMainFrame::g_mmEQ_I_A_K::value_type( val, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				
				varo.addVar(id, AIPI_ID, key, c, EQ, pm);
				varo.addVar(attr, AIPI_AT, key, c, EQ, pm);
										
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, EQ, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, EQ, pm);
				

			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmEQ_I_A_K.insert(CMainFrame::g_mmEQ_I_A_K::value_type( val, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key, c));

			varo.addVar(id, AIPI_ID, key, c, EQ, pm);
			varo.addVar(attr, AIPI_AT, key, c, EQ, pm);
				
								
		}
			
	}//ID_K_VL
	
	else if( categ == ID_K_VL )
	{	
		
		
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmEQ_I_K_V.empty() )
		{
						
			CMainFrame::g_mmEQ_I_K_V::iterator iter;
			iter = pMainFrame->gmmEQ_I_K_V.find(attr);
			if( iter == pMainFrame->gmmEQ_I_K_V.end())
			{
				int key = generateAMKey();
												
				pMainFrame->gmmEQ_I_K_V.insert(CMainFrame::g_mmEQ_I_K_V::value_type( attr, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, EQ, pm);
				varo.addVar(val, AIPI_VL, key, c, EQ, pm);
				
		
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
				
				varo.addVar(id, AIPI_ID, iter->second, c, EQ, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, EQ, pm);
				
				
								
			}
		}
		else
		{
			int key = generateAMKey();
			
			pMainFrame->gmmEQ_I_K_V.insert(CMainFrame::g_mmEQ_I_K_V::value_type( attr, key ));	
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, EQ, pm);
			varo.addVar(val, AIPI_VL, key, c, EQ, pm);
				
		
		}	
								
	}//ID_K_K

			
	else if( categ == ID_K_K )
	{
				
		//pMainFrame->gsIVar.insert(id);

		tstring str = attr + _T("|") + val;
												
		if( !pMainFrame->gmmEQ_I_K_K.empty() )
		{
			CMainFrame::g_mmEQ_I_K_K::iterator iter;
			iter = pMainFrame->gmmEQ_I_K_K.find(str);
			if( iter == pMainFrame->gmmEQ_I_K_K.end())
			{
				int key = generateAMKey();
				
				pMainFrame->gmmEQ_I_K_K.insert(CMainFrame::g_mmEQ_I_K_K::value_type(str, key ));	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, EQ, pm);
				
				
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
				
				varo.addVar(id, AIPI_ID, iter->second, c, EQ, pm);
			}	
		}	
		else
		{
			int key = generateAMKey();
			
			pMainFrame->gmmEQ_I_K_K.insert(CMainFrame::g_mmEQ_I_K_K::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, EQ, pm);
		}
				
				
	}//K_AT_VL

		
	else if( categ == K_AT_VL )
	{
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmEQ_K_A_V.empty() )
		{
			CMainFrame::g_mmEQ_K_A_V::iterator iter;
			iter = pMainFrame->gmmEQ_K_A_V.find(id);
			if( iter == pMainFrame->gmmEQ_K_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmEQ_K_A_V.insert(CMainFrame::g_mmEQ_K_A_V::value_type( id, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, EQ, pm);
				varo.addVar(val, AIPI_VL, key, c, EQ, pm);
				
				
			}
			else
			{	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, EQ, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, EQ, pm);
			
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmEQ_K_A_V.insert(CMainFrame::g_mmEQ_K_A_V::value_type( id, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, EQ, pm);
			varo.addVar(val, AIPI_VL, key, c, EQ, pm);
				
			

		}
				
	}//K_AT_K
	else if( categ == K_AT_K )
	{
		//pMainFrame->gsAVar.insert(attr);
						
		tstring str = id + _T("|") + val;
				
		if( !pMainFrame->gmmEQ_K_A_K.empty() )
		{
			CMainFrame::g_mmEQ_K_A_K::iterator iter;
			iter = pMainFrame->gmmEQ_K_A_K.find(str);
			if( iter == pMainFrame->gmmEQ_K_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmEQ_K_A_K.insert(CMainFrame::g_mmEQ_K_A_K::value_type( str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				
				varo.addVar(attr, AIPI_AT, key, c, EQ, pm);
				
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, EQ, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmEQ_K_A_K.insert(CMainFrame::g_mmEQ_K_A_K::value_type( str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, EQ, pm);
			
		}

	}//K_K_VL
	else if( categ == K_K_VL )
	{
		//pMainFrame->gsVVar.insert(val);
		/*
		CString s;
		s.Format(_T("Constan Test Condition...%d  " ), c);
		AfxMessageBox(s);
		*/
		  
		tstring str = id + _T("|") + attr;
				
		if( !pMainFrame->gmmEQ_K_K_V.empty() )
		{
			CMainFrame::g_mmEQ_K_K_V::iterator iter;
			iter = pMainFrame->gmmEQ_K_K_V.find(str);
			if( iter == pMainFrame->gmmEQ_K_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmEQ_K_K_V.insert(CMainFrame::g_mmEQ_K_K_V::value_type(str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				
				varo.addVar(val, AIPI_VL, key, c, EQ, pm);
				/*
				AfxMessageBox(_T("Inserta1"));
				s.Format(_T("AM...%d  " ), key);
				AfxMessageBox(s);
				*/
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(val, AIPI_VL, iter->second, c, EQ, pm);
				/*
				AfxMessageBox(_T("Inserta2"));
				s.Format(_T("AM...%d  " ), iter->second);
				AfxMessageBox(s);
				*/
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmEQ_K_K_V.insert(CMainFrame::g_mmEQ_K_K_V::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(val, AIPI_VL, key, c, EQ, pm);
			/*
			AfxMessageBox(_T("Inserta3"));
			s.Format(_T("AM...%d  " ), key);
			AfxMessageBox(s);
			*/	
			
		}
				
	}//K_K_K
	else if ( categ == K_K_K )
	{	
		tstring str = id + _T("|") + attr + _T("|") + val;
		
		/*
		CString stri;
		stri.Format(_T("Constan Test Condition...%d  " ), c);
		AfxMessageBox(stri);				
		AfxMessageBox(str.data());
		*/
		
		//Works with constants only
		CAipi_WM		wmo;
		wmo.insertEQ_WM_Cond(c, id, attr, val);
				
		if( !pMainFrame->gmmEQ_K_K_K.empty() )
		{
			CMainFrame::g_mmEQ_K_K_K::iterator iter;
			iter = pMainFrame->gmmEQ_K_K_K.find(str);
				
			if( iter == pMainFrame->gmmEQ_K_K_K.end())
			{
				int key = generateAMKey();
				//str.Format(_T("Constan Test KEY...%d  " ), key);
				//AfxMessageBox(_T("Inserta"));
				//AfxMessageBox(str.c_str());				
		
				pMainFrame->gmmEQ_K_K_K.insert(CMainFrame::g_mmEQ_K_K_K::value_type( str , key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
			}
			else
			{
				//AfxMessageBox(_T("No"));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
			}
		}
		else
		{
			int key = generateAMKey();
			//stri.Format(_T("Constan Test KEY...%d  " ), key);
			//AfxMessageBox(stri);				
			//AfxMessageBox(_T("Inserta"));
			//AfxMessageBox(str.c_str());				
		
			pMainFrame->gmmEQ_K_K_K.insert(CMainFrame::g_mmEQ_K_K_K::value_type( str , key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
		}
				
	}//ID_AT_VL
	else if ( categ == ID_AT_VL )
	{
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		
		if( !pMainFrame->gmmEQ_I_A_V.empty() )
		{
			CMainFrame::g_mmEQ_I_A_V::iterator iter;
			iter = pMainFrame->gmmEQ_I_A_V.find(_T("e"));
			if( iter == pMainFrame->gmmEQ_I_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmEQ_I_A_V.insert(CMainFrame::g_mmEQ_I_A_V::value_type( _T("e"), key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, EQ, pm);
				varo.addVar(attr, AIPI_AT, key, c, EQ, pm);
				varo.addVar(val, AIPI_VL, key, c, EQ, pm);
			
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, EQ, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, EQ, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, EQ, pm);
			
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmEQ_I_A_V.insert(CMainFrame::g_mmEQ_I_A_V::value_type( _T("e"), key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, EQ, pm);
			varo.addVar(attr, AIPI_AT, key, c, EQ, pm);
			varo.addVar(val, AIPI_VL, key, c, EQ, pm);
			
		}
				
	 }//Testing Relational Variables
	else
	{		
		switch ( categ )
		{
			//Error has ocurred
			//AfxMessageBox(_T("EQ Error, can manage relational opearations"));
			case ID_RO_VL :
				//pMainFrame->gsIVar.insert(id);
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, EQ, pm);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, EQ, pm);
				break;
			case ID_RO_K:
				//pMainFrame->gsIVar.insert(id);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, EQ, pm);
				break;
			case K_RO_K:
				break;
			case K_RO_VL:
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, EQ, pm);
				break;
		}
	 }	

	//This process ( fill_PM_Vars(pm) ) was already made in the parser
	//Method: emit_rule( AIPI_RHS)
	
	//fillPM_Vars(pm);


}



void CAipi_RETE_AM::constantTestET(int c,tstring id, tstring attr, tstring val, int pm, int categ)
{
	
	//This functions saves the variables of each lhs element.
	//pMainFrame->gsIVar.insert(id);
	//pMainFrame->gsAVar.insert(attr);
	//pMainFrame->gsVVar.insert(attr);
	
	//This process was already made in the parser, Method: emit_rule(AIPI_LHS);
	//So here it is just comment.
	
	//AfxMessageBox(_T("CONSTANT TEST ET"));
	
	/*
	CString stri;
	stri.Format(_T("Constan Test Condition...%d  " ), c);
	AfxMessageBox(stri);				
	*/
	
	
	CAipi_RETE_Vars varo;
	
	//// *** EQUAL THAN TEST **** //// 
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	//ID_AT_K
	if( categ == ID_AT_K )
	{
			
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
		
		if( !pMainFrame->gmmET_I_A_K.empty() )
		{	
			CMainFrame::g_mmET_I_A_K::iterator iter;
			iter = pMainFrame->gmmET_I_A_K.find(val);
			if( iter == pMainFrame->gmmET_I_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmET_I_A_K.insert(CMainFrame::g_mmET_I_A_K::value_type( val, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, ET, pm);
				varo.addVar(attr, AIPI_AT, key, c, ET, pm);
				
						
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, ET, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, ET, pm);
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmET_I_A_K.insert(CMainFrame::g_mmET_I_A_K::value_type( val, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, ET, pm);
			varo.addVar(attr, AIPI_AT, key, c, ET, pm);
				
		}
			
	}//ID_K_VL
	
	else if( categ == ID_K_VL )
	{	
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmET_I_K_V.empty() )
		{
			CMainFrame::g_mmET_I_K_V::iterator iter;
			iter = pMainFrame->gmmET_I_K_V.find(attr);
			if( iter == pMainFrame->gmmET_I_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmET_I_K_V.insert(CMainFrame::g_mmET_I_K_V::value_type( attr, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				
				varo.addVar(id, AIPI_ID, key, c, ET, pm);
				varo.addVar(val, AIPI_VL, key, c, ET, pm);
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, ET, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, ET, pm);
				
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmET_I_K_V.insert(CMainFrame::g_mmET_I_K_V::value_type( attr, key ));	
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, ET, pm);
			varo.addVar(val, AIPI_VL, key, c, ET, pm);
				
		
		}	
								
	}//ID_K_K

			
	else if( categ == ID_K_K )
	{
		//pMainFrame->gsIVar.insert(id);
		
		
		tstring str = attr + _T("|") + val;
												
		if( !pMainFrame->gmmET_I_K_K.empty() )
		{
					
			CMainFrame::g_mmET_I_K_K::iterator iter;
			iter = pMainFrame->gmmET_I_K_K.find(str);
			if( iter == pMainFrame->gmmET_I_K_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmET_I_K_K.insert(CMainFrame::g_mmET_I_K_K::value_type(str, key ));	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, ET, pm);
								

			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, ET, pm);
							

			}	
		}	
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmET_I_K_K.insert(CMainFrame::g_mmET_I_K_K::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
			
			varo.addVar(id, AIPI_ID, key, c, ET, pm);

		}
				
				
	}//K_AT_VL

		
	else if( categ == K_AT_VL )
	{
		
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmET_K_A_V.empty() )
		{
			CMainFrame::g_mmET_K_A_V::iterator iter;
			iter = pMainFrame->gmmET_K_A_V.find(id);
			if( iter == pMainFrame->gmmET_K_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmET_K_A_V.insert(CMainFrame::g_mmET_K_A_V::value_type( id, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, ET, pm);
				varo.addVar(val, AIPI_VL, key, c, ET, pm);
			}
			else
			{	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, ET, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, ET, pm);

			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmET_K_A_V.insert(CMainFrame::g_mmET_K_A_V::value_type( id, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, ET, pm);
			varo.addVar(val, AIPI_VL, key, c, ET, pm);
		}
				
	}//K_AT_K
	else if( categ == K_AT_K  )
	{
		//pMainFrame->gsAVar.insert(attr);
				
		tstring str = id + _T("|") + val;
				
		if( !pMainFrame->gmmET_K_A_K.empty() )
		{
			CMainFrame::g_mmET_K_A_K::iterator iter;
			iter = pMainFrame->gmmET_K_A_K.find(str);
			if( iter == pMainFrame->gmmET_K_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmET_K_A_K.insert(CMainFrame::g_mmET_K_A_K::value_type( str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, ET, pm);
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, ET, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmET_K_A_K.insert(CMainFrame::g_mmET_K_A_K::value_type( str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, ET, pm);
		}

	}//K_K_VL
	else if( categ == K_K_VL )
	{
		//pMainFrame->gsVVar.insert(val);
				
		tstring str = id + _T("|") + attr;
				
		if( !pMainFrame->gmmET_K_K_V.empty() )
		{
			CMainFrame::g_mmET_K_K_V::iterator iter;
			iter = pMainFrame->gmmET_K_K_V.find(str);
			if( iter == pMainFrame->gmmET_K_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmET_K_K_V.insert(CMainFrame::g_mmET_K_K_V::value_type(str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(val, AIPI_VL, key, c, ET, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(val, AIPI_VL, iter->second, c, ET, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmET_K_K_V.insert(CMainFrame::g_mmET_K_K_V::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(val, AIPI_VL, key, c, ET, pm);
		}
				
	}//K_K_K
	else if (  categ == K_K_K )
	{	
		tstring str = id + _T("|") + attr + _T("|") + val;
		
		//Works with constants only
		CAipi_WM wmo;
		wmo.insertET_WM_Cond(c, id, attr, val);
				
		if( !pMainFrame->gmmET_K_K_K.empty() )
		{
			CMainFrame::g_mmET_K_K_K::iterator iter;
			iter = pMainFrame->gmmET_K_K_K.find(str);
				
			if( iter == pMainFrame->gmmET_K_K_K.end())
			{
				//AfxMessageBox(_T("Inserta"));
				//AfxMessageBox(str.c_str());				
		
				int key = generateAMKey();
				pMainFrame->gmmET_K_K_K.insert(CMainFrame::g_mmET_K_K_K::value_type( str , key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
			}
		}
		else
		{
			//AfxMessageBox(_T("Inserta"));
			//AfxMessageBox(str.c_str());				
		
			int key = generateAMKey();
			pMainFrame->gmmET_K_K_K.insert(CMainFrame::g_mmET_K_K_K::value_type( str , key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
		}
				
	}//ID_AT_VL
	else if( categ == ID_AT_VL )
	{
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		
		if( !pMainFrame->gmmET_I_A_V.empty() )
		{
			CMainFrame::g_mmET_I_A_V::iterator iter;
			iter = pMainFrame->gmmET_I_A_V.find(_T("e"));
			if( iter == pMainFrame->gmmGT_I_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmET_I_A_V.insert(CMainFrame::g_mmET_I_A_V::value_type( _T("e"), key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, ET, pm);
				varo.addVar(attr, AIPI_AT, key, c, ET, pm);
				varo.addVar(val, AIPI_VL, key, c, ET, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, ET, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, ET, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, ET, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmET_I_A_V.insert(CMainFrame::g_mmET_I_A_V::value_type( _T("e"), key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, ET, pm);
			varo.addVar(attr, AIPI_AT, key, c, ET, pm);
			varo.addVar(val, AIPI_VL, key, c, ET, pm);
		}
				
	 } //Testing relational operations 
	 else
	 {		
		switch ( categ )
		{
			case ID_RO_VL :
				//pMainFrame->gsIVar.insert(id);
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, ET, pm);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, ET, pm);
				break;
			case ID_RO_K:
				//pMainFrame->gsIVar.insert(id);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, ET, pm);
				break;
			case K_RO_K:
				break;
			case K_RO_VL:
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, ET, pm);
				break;
		}
	 }	
	 


	//This process ( fill_PM_Vars(pm) ) was already made in the parser
	//Method: emit_rule( AIPI_RHS)
	
	//fillPM_Vars(pm);
}





void CAipi_RETE_AM::constantTestNE(int c,tstring id, tstring attr, tstring val, int pm, int categ )
{
	//This functions saves the variables of each lhs element.
	//pMainFrame->gsIVar.insert(id);
	//pMainFrame->gsAVar.insert(attr);
	//pMainFrame->gsVVar.insert(attr);
	
	//This process was already made in the parser, Method: emit_rule(AIPI_LHS);
	//So here it is just comment.
	//AfxMessageBox(_T("CONSTANT TEST NE"));
	
	CAipi_RETE_Vars varo;

	//// *** NON EQUALITY TEST **** //// 
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	//ID_AT_K
	if( categ == ID_AT_K )
	{
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
				
		if( !pMainFrame->gmmNE_I_A_K.empty() )
		{	
			CMainFrame::g_mmNE_I_A_K::iterator iter;
			iter = pMainFrame->gmmNE_I_A_K.find(val);
			if( iter == pMainFrame->gmmNE_I_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmNE_I_A_K.insert(CMainFrame::g_mmNE_I_A_K::value_type( val, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, NE, pm);
				varo.addVar(attr, AIPI_AT, key, c, NE, pm);
				
						
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, NE, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, NE, pm);
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmNE_I_A_K.insert(CMainFrame::g_mmNE_I_A_K::value_type( val, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, NE, pm);
			varo.addVar(attr, AIPI_AT, key, c, NE, pm);
				
		}
			
	}//ID_K_VL
	
	else if( categ == ID_K_VL )
	{	
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsVVar.insert(val);	
		
		if( !pMainFrame->gmmNE_I_K_V.empty() )
		{
			CMainFrame::g_mmNE_I_K_V::iterator iter;
			iter = pMainFrame->gmmNE_I_K_V.find(attr);
			if( iter == pMainFrame->gmmNE_I_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmNE_I_K_V.insert(CMainFrame::g_mmNE_I_K_V::value_type( attr, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, NE, pm);
				varo.addVar(val, AIPI_VL, key, c, NE, pm);
				
				
		
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, NE, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, NE, pm);
				
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmNE_I_K_V.insert(CMainFrame::g_mmNE_I_K_V::value_type( attr, key ));	
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, NE, pm);
			varo.addVar(val, AIPI_VL, key, c, NE, pm);
				
		
		}	
								
	}//ID_K_K

			
	else if( categ == ID_K_K )
	{
		//pMainFrame->gsIVar.insert(id);
		
		tstring str = attr + _T("|") + val;
												
		if( !pMainFrame->gmmNE_I_K_K.empty() )
		{
					
			CMainFrame::g_mmNE_I_K_K::iterator iter;
			iter = pMainFrame->gmmNE_I_K_K.find(str);
			if( iter == pMainFrame->gmmNE_I_K_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmNE_I_K_K.insert(CMainFrame::g_mmNE_I_K_K::value_type(str, key ));	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				
				varo.addVar(id, AIPI_ID, key, c, NE, pm);

			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, NE, pm);
			}	
		}	
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmNE_I_K_K.insert(CMainFrame::g_mmNE_I_K_K::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, NE, pm);
		}
				
				
	}//K_AT_VL

		
	else if( categ == K_AT_VL )
	{
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmNE_K_A_V.empty() )
		{
			CMainFrame::g_mmNE_K_A_V::iterator iter;
			iter = pMainFrame->gmmNE_K_A_V.find(id);
			if( iter == pMainFrame->gmmNE_K_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmNE_K_A_V.insert(CMainFrame::g_mmNE_K_A_V::value_type( id, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, NE, pm);
				varo.addVar(val, AIPI_VL, key, c, NE, pm);
			
			}
			else
			{	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, NE, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, NE, pm);
			
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmNE_K_A_V.insert(CMainFrame::g_mmNE_K_A_V::value_type( id, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, NE, pm);
			varo.addVar(val, AIPI_VL, key, c, NE, pm);

		}
				
	}//K_AT_K
	else if( categ == K_AT_K )
	{
				
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsVVar.insert(val);

		tstring str = id + _T("|") + val;
				
		if( !pMainFrame->gmmNE_K_A_K.empty() )
		{
			CMainFrame::g_mmNE_K_A_K::iterator iter;
			iter = pMainFrame->gmmNE_K_A_K.find(str);
			if( iter == pMainFrame->gmmNE_K_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmNE_K_A_K.insert(CMainFrame::g_mmNE_K_A_K::value_type( str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, NE, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, NE, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmNE_K_A_K.insert(CMainFrame::g_mmNE_K_A_K::value_type( str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
			
			varo.addVar(attr, AIPI_AT, key, c, NE, pm);

		}

	}//K_K_VL
	else if( categ == K_K_VL )
	{
				
		//pMainFrame->gsVVar.insert(val);
		
		tstring str = id + _T("|") + attr;
				
		if( !pMainFrame->gmmNE_K_K_V.empty() )
		{
			CMainFrame::g_mmNE_K_K_V::iterator iter;
			iter = pMainFrame->gmmNE_K_K_V.find(str);
			if( iter == pMainFrame->gmmNE_K_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmNE_K_K_V.insert(CMainFrame::g_mmNE_K_K_V::value_type(str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(val, AIPI_VL, key, c, NE, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(val, AIPI_VL, iter->second, c, NE, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmNE_K_K_V.insert(CMainFrame::g_mmNE_K_K_V::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(val, AIPI_VL, key, c, NE, pm);
		}
				
	}//K_K_K
	else if ( categ == K_K_K )
	{	
		tstring str = id + _T("|") + attr + _T("|") + val;

		//Works with constants only
		CAipi_WM wmo;
		wmo.insertNE_WM_Cond(c, id, attr, val); 
				
		if( !pMainFrame->gmmNE_K_K_K.empty() )
		{
			CMainFrame::g_mmNE_K_K_K::iterator iter;
			iter = pMainFrame->gmmNE_K_K_K.find(str);
				
			if( iter == pMainFrame->gmmNE_K_K_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmNE_K_K_K.insert(CMainFrame::g_mmNE_K_K_K::value_type( str , key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmNE_K_K_K.insert(CMainFrame::g_mmNE_K_K_K::value_type( str , key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
		}
				
	}//ID_AT_VL
	else if( ID_AT_VL )
	{
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmNE_I_A_V.empty() )
		{
			CMainFrame::g_mmNE_I_A_V::iterator iter;
			iter = pMainFrame->gmmNE_I_A_V.find(_T("e"));
			if( iter == pMainFrame->gmmNE_I_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmNE_I_A_V.insert(CMainFrame::g_mmNE_I_A_V::value_type( _T("e"), key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, NE, pm);
				varo.addVar(attr, AIPI_AT, key, c, NE, pm);
				varo.addVar(val, AIPI_VL, key, c, NE, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, NE, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, NE, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, NE, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmNE_I_A_V.insert(CMainFrame::g_mmNE_I_A_V::value_type( _T("e"), key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, NE, pm);
			varo.addVar(attr, AIPI_AT, key, c, NE, pm);
			varo.addVar(val, AIPI_VL, key, c, NE, pm);
		}
				
	 }//Testing relational operations 
	 else
	 {		
		switch ( categ )
		{
			case ID_RO_VL :
				//pMainFrame->gsIVar.insert(id);
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, NE, pm);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, NE, pm);
				break;
			case ID_RO_K:
				//pMainFrame->gsIVar.insert(id);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, NE, pm);
				break;
			case K_RO_K:
				break;
			case K_RO_VL:
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, NE, pm);
				break;
		}
	 }	

	//This process ( fill_PM_Vars(pm) ) was already made in the parser
	//Method: emit_rule( AIPI_RHS)
	
	//fillPM_Vars(pm);
}



void CAipi_RETE_AM::constantTestLT(int c,tstring id, tstring attr, tstring val, int pm, int categ)
{
	//This functions saves the variables of each lhs element.
	//pMainFrame->gsIVar.insert(id);
	//pMainFrame->gsAVar.insert(attr);
	//pMainFrame->gsVVar.insert(attr);
	
	//This process was already made in the parser, Method: emit_rule(AIPI_LHS);
	//So here it is just comment.
	//AfxMessageBox(_T("CONSTANT TEST LT"));
	
	CAipi_RETE_Vars varo;
	
	//// *** LESSER THAN TEST **** //// 	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	//ID_AT_K
	if(categ == ID_AT_K )
	{
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
				
		if( !pMainFrame->gmmLT_I_A_K.empty() )
		{	
			CMainFrame::g_mmLT_I_A_K::iterator iter;
			iter = pMainFrame->gmmLT_I_A_K.find(val);
			if( iter == pMainFrame->gmmLT_I_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLT_I_A_K.insert(CMainFrame::g_mmLT_I_A_K::value_type( val, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, LT, pm);
				varo.addVar(attr, AIPI_AT, key, c, LT, pm);
				
						
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, LT, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, LT, pm);
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLT_I_A_K.insert(CMainFrame::g_mmLT_I_A_K::value_type( val, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, LT, pm);
			varo.addVar(attr, AIPI_AT, key, c, LT, pm);
		}
			
	}//ID_K_VL
	
	else if( categ == ID_K_VL )
	{	
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsVVar.insert(val);	
		
		
		if( !pMainFrame->gmmLT_I_K_V.empty() )
		{
			CMainFrame::g_mmLT_I_K_V::iterator iter;
			iter = pMainFrame->gmmLT_I_K_V.find(attr);
			if( iter == pMainFrame->gmmLT_I_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLT_I_K_V.insert(CMainFrame::g_mmLT_I_K_V::value_type( attr, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, LT, pm);
				varo.addVar(val, AIPI_VL, key, c, LT, pm);
				
		
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, LT, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, LT, pm);
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLT_I_K_V.insert(CMainFrame::g_mmLT_I_K_V::value_type( attr, key ));	
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, LT, pm);
			varo.addVar(val, AIPI_VL, key, c, LT, pm);
		
		}	
								
	}//ID_K_K

			
	else if( categ == ID_K_K )
	{
		//pMainFrame->gsIVar.insert(id);
		/*
		CString s;
		s.Format(_T("Constan Test Condition...%d  " ), c);
		AfxMessageBox(s);	
		*/

		tstring str = attr + _T("|") + val;
												
		if( !pMainFrame->gmmLT_I_K_K.empty() )
		{
					
			CMainFrame::g_mmLT_I_K_K::iterator iter;
			iter = pMainFrame->gmmLT_I_K_K.find(str);
			if( iter == pMainFrame->gmmLT_I_K_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLT_I_K_K.insert(CMainFrame::g_mmLT_I_K_K::value_type(str, key ));	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, LT, pm);

				/*
				AfxMessageBox(_T("Inserta1"));
				s.Format(_T("AM...%d  " ), key);
				AfxMessageBox(s);				
				*/
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, LT, pm);
				
				/*
				AfxMessageBox(_T("Inserta2"));
				s.Format(_T("AM...%d  " ), iter->second);
				AfxMessageBox(s);	
				*/
		
				
			}	
		}	
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLT_I_K_K.insert(CMainFrame::g_mmLT_I_K_K::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, LT, pm);

			/*
			AfxMessageBox(_T("Inserta3"));
			s.Format(_T("AM...%d  " ), key);
			AfxMessageBox(s);				
			*/
			
		}
				
				
	}//K_AT_VL

		
	else if( categ == K_AT_VL )
	{
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmLT_K_A_V.empty() )
		{
			CMainFrame::g_mmLT_K_A_V::iterator iter;
			iter = pMainFrame->gmmLT_K_A_V.find(id);
			if( iter == pMainFrame->gmmLT_K_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLT_K_A_V.insert(CMainFrame::g_mmLT_K_A_V::value_type( id, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, LT, pm);
				varo.addVar(val, AIPI_VL, key, c, LT, pm);
			}
			else
			{	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, LT, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, LT, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLT_K_A_V.insert(CMainFrame::g_mmLT_K_A_V::value_type( id, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, LT, pm);
			varo.addVar(val, AIPI_VL, key, c, LT, pm);
		}
				
	}//K_AT_K
	else if( categ == K_AT_K )
	{
				
		//pMainFrame->gsAVar.insert(attr);
		
		tstring str = id + _T("|") + val;
				
		if( !pMainFrame->gmmLT_K_A_K.empty() )
		{
			CMainFrame::g_mmLT_K_A_K::iterator iter;
			iter = pMainFrame->gmmLT_K_A_K.find(str);
			if( iter == pMainFrame->gmmLT_K_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLT_K_A_K.insert(CMainFrame::g_mmLT_K_A_K::value_type( str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, LT, pm);
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, LT, pm);
			
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLT_K_A_K.insert(CMainFrame::g_mmLT_K_A_K::value_type( str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, LT, pm);
			
		}

	}//K_K_VL
	else if( categ == K_K_VL )
	{
				
		//pMainFrame->gsVVar.insert(val);

		tstring str = id + _T("|") + attr;
				
		if( !pMainFrame->gmmLT_K_K_V.empty() )
		{
			CMainFrame::g_mmLT_K_K_V::iterator iter;
			iter = pMainFrame->gmmLT_K_K_V.find(str);
			if( iter == pMainFrame->gmmLT_K_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLT_K_K_V.insert(CMainFrame::g_mmLT_K_K_V::value_type(str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(val, AIPI_VL, key, c, LT, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(val, AIPI_VL, iter->second, c, LT, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLT_K_K_V.insert(CMainFrame::g_mmLT_K_K_V::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(val, AIPI_VL, key, c, LT, pm);
		}
				
	}//K_K_K
	else if ( categ == K_K_K )
	{	
		tstring str = id + _T("|") + attr + _T("|") + val;

		//Works with constants only
		CAipi_WM wmo;
		wmo.insertLT_WM_Cond(c, id, attr, val); 
				
		if( !pMainFrame->gmmLT_K_K_K.empty() )
		{
			CMainFrame::g_mmLT_K_K_K::iterator iter;
			iter = pMainFrame->gmmLT_K_K_K.find(str);
				
			if( iter == pMainFrame->gmmLT_K_K_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLT_K_K_K.insert(CMainFrame::g_mmLT_K_K_K::value_type( str , key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLT_K_K_K.insert(CMainFrame::g_mmLT_K_K_K::value_type( str , key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
		}
				
	}//ID_AT_VL
	else if ( categ == ID_AT_VL )
	{
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmLT_I_A_V.empty() )
		{
			CMainFrame::g_mmLT_I_A_V::iterator iter;
			iter = pMainFrame->gmmLT_I_A_V.find(_T("e"));
			if( iter == pMainFrame->gmmLT_I_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLT_I_A_V.insert(CMainFrame::g_mmLT_I_A_V::value_type( _T("e"), key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, LT, pm);
				varo.addVar(attr, AIPI_AT, key, c, LT, pm);
				varo.addVar(val, AIPI_VL, key, c, LT, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, LT, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, LT, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, LT, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLT_I_A_V.insert(CMainFrame::g_mmLT_I_A_V::value_type( _T("e"), key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, LT, pm);
			varo.addVar(attr, AIPI_AT, key, c, LT, pm);
			varo.addVar(val, AIPI_VL, key, c, LT, pm);
		}
				
	 }//Testing relational operations 
	else
	{		
		switch ( categ )
		{
			case ID_RO_VL :
				//pMainFrame->gsIVar.insert(id);
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, LT, pm);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, LT, pm);
				break;
			case ID_RO_K:
				//pMainFrame->gsIVar.insert(id);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, LT, pm);
				break;
			case K_RO_K:
				break;
			case K_RO_VL:
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, LT, pm);
				break;
		}
	 }
	 
	//This process ( fill_PM_Vars(pm) ) was already made in the parser
	//Method: emit_rule( AIPI_RHS)
	
	//fillPM_Vars(pm);

}


void CAipi_RETE_AM::constantTestLE(int c,tstring id, tstring attr, tstring val, int pm, int categ)
{
	//This functions saves the variables of each lhs element.
	//pMainFrame->gsIVar.insert(id);
	//pMainFrame->gsAVar.insert(attr);
	//pMainFrame->gsVVar.insert(attr);
	
	//This process was already made in the parser, Method: emit_rule(AIPI_LHS);
	//So here it is just comment.
	//AfxMessageBox(_T("CONSTANT TEST LE"));

	CAipi_WM wmo;
	CAipi_RETE_Vars varo;

//// *** LESSER OR EQUAL THAN TEST **** //// 
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	//ID_AT_K
	if( categ == ID_AT_K )
	{
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
				
		if( !pMainFrame->gmmLE_I_A_K.empty() )
		{	
			CMainFrame::g_mmLE_I_A_K::iterator iter;
			iter = pMainFrame->gmmLE_I_A_K.find(val);
			if( iter == pMainFrame->gmmLE_I_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLE_I_A_K.insert(CMainFrame::g_mmLE_I_A_K::value_type( val, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, LE, pm);
				varo.addVar(attr, AIPI_AT, key, c, LE, pm);
				
						
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, LE, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, LE, pm);
				 
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLE_I_A_K.insert(CMainFrame::g_mmLE_I_A_K::value_type( val, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, LE, pm);
			varo.addVar(attr, AIPI_AT, key, c, LE, pm);
			
		}
			
	}//ID_K_VL
	
	else if( categ == ID_K_VL )
	{	
			
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsVVar.insert(val);

		if( !pMainFrame->gmmLE_I_K_V.empty() )
		{
			CMainFrame::g_mmLE_I_K_V::iterator iter;
			iter = pMainFrame->gmmLE_I_K_V.find(attr);
			if( iter == pMainFrame->gmmLE_I_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLE_I_K_V.insert(CMainFrame::g_mmLE_I_K_V::value_type( attr, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, LE, pm);
				varo.addVar(val, AIPI_VL, key, c, LE, pm);
				
		
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, LE, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, LE, pm);
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLE_I_K_V.insert(CMainFrame::g_mmLE_I_K_V::value_type( attr, key ));	
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, LE, pm);
			varo.addVar(val, AIPI_VL, key, c, LE, pm);
		
		}	
								
	}//ID_K_K

			
	else if( categ == ID_K_K )
	{
		//pMainFrame->gsIVar.insert(id);
		
		tstring str = attr + _T("|") + val;
												
		if( !pMainFrame->gmmLE_I_K_K.empty() )
		{
					
			CMainFrame::g_mmLE_I_K_K::iterator iter;
			iter = pMainFrame->gmmLT_I_K_K.find(str);
			if( iter == pMainFrame->gmmLT_I_K_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLE_I_K_K.insert(CMainFrame::g_mmLE_I_K_K::value_type(str, key ));	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, LE, pm);
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, LE, pm);
				
			}	
		}	
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLE_I_K_K.insert(CMainFrame::g_mmLE_I_K_K::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, LE, pm);
			
		}
				
				
	}//K_AT_VL

		
	else if( categ == K_AT_VL )
	{
		
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmLE_K_A_V.empty() )
		{
			CMainFrame::g_mmLE_K_A_V::iterator iter;
			iter = pMainFrame->gmmLE_K_A_V.find(id);
			if( iter == pMainFrame->gmmLE_K_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLE_K_A_V.insert(CMainFrame::g_mmLE_K_A_V::value_type( id, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, LE, pm);
				varo.addVar(val, AIPI_VL, key, c, LE, pm);
			}
			else
			{	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, LE, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, LE, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLE_K_A_V.insert(CMainFrame::g_mmLE_K_A_V::value_type( id, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, LE, pm);
			varo.addVar(val, AIPI_VL, key, c, LE, pm);
		}
				
	}//K_AT_K
	else if( categ == K_AT_K )
	{
		//pMainFrame->gsAVar.insert(attr);
				
		tstring str = id + _T("|") + val;
				
		if( !pMainFrame->gmmLE_K_A_K.empty() )
		{
			CMainFrame::g_mmLE_K_A_K::iterator iter;
			iter = pMainFrame->gmmLE_K_A_K.find(str);
			if( iter == pMainFrame->gmmLE_K_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLE_K_A_K.insert(CMainFrame::g_mmLE_K_A_K::value_type( str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, LE, pm);
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, LE, pm);
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLE_K_A_K.insert(CMainFrame::g_mmLE_K_A_K::value_type( str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, LE, pm);
			
		}

	}//K_K_VL
	else if( categ == K_K_VL )
	{
		//pMainFrame->gsVVar.insert(val);		
		
		tstring str = id + _T("|") + attr;
				
		if( !pMainFrame->gmmLE_K_K_V.empty() )
		{
			CMainFrame::g_mmLE_K_K_V::iterator iter;
			iter = pMainFrame->gmmLE_K_K_V.find(str);
			if( iter == pMainFrame->gmmLE_K_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLE_K_K_V.insert(CMainFrame::g_mmLE_K_K_V::value_type(str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(val, AIPI_VL, key, c, LE, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(val, AIPI_VL, iter->second, c, LE, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLE_K_K_V.insert(CMainFrame::g_mmLE_K_K_V::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(val, AIPI_VL, key, c, LE, pm);
		}
				
	}//K_K_K
	else if ((id.substr(0,1) != _T("[")) && (attr.substr(0,1) != _T("[")) && (val.substr(0,1) != _T("[")) )
	{	
		tstring str = id + _T("|") + attr + _T("|") + val;

		//Works with constants only
		CAipi_WM wmo;
		wmo.insertLE_WM_Cond(c, id, attr, val); 
				
		if( !pMainFrame->gmmLE_K_K_K.empty() )
		{
			CMainFrame::g_mmLE_K_K_K::iterator iter;
			iter = pMainFrame->gmmLE_K_K_K.find(str);
				
			if( iter == pMainFrame->gmmLE_K_K_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLE_K_K_K.insert(CMainFrame::g_mmLE_K_K_K::value_type( str , key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
			
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLE_K_K_K.insert(CMainFrame::g_mmLE_K_K_K::value_type( str , key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			
		}
				
	}//ID_AT_VL
	else if( categ == ID_AT_VL)
	{
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmLT_I_A_V.empty() )
		{
			CMainFrame::g_mmLE_I_A_V::iterator iter;
			iter = pMainFrame->gmmLE_I_A_V.find(_T("e"));
			if( iter == pMainFrame->gmmLE_I_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmLE_I_A_V.insert(CMainFrame::g_mmLE_I_A_V::value_type( _T("e"), key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, LE, pm);
				varo.addVar(attr, AIPI_AT, key, c, LE, pm);
				varo.addVar(val, AIPI_VL, key, c, LE, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, LE, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, LE, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, LE, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmLE_I_A_V.insert(CMainFrame::g_mmLE_I_A_V::value_type( _T("e"), key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, LE, pm);
			varo.addVar(attr, AIPI_AT, key, c, LE, pm);
			varo.addVar(val, AIPI_VL, key, c, LE, pm);
		}
				
	 }//Testing relational operations 
	 else
	 {		
		switch ( categ )
		{
			case ID_RO_VL :
				//pMainFrame->gsIVar.insert(id);
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, LE, pm);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, LE, pm);
				break;
			case ID_RO_K:
				//pMainFrame->gsIVar.insert(id);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, LE, pm);
				break;
			case K_RO_K:
				break;
			case K_RO_VL:
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, LE, pm);
				break;
		}
	 }	

	//This process ( fill_PM_Vars(pm) ) was already made in the parser
	//Method: emit_rule( AIPI_RHS)
	
	//fillPM_Vars(pm);
}





void CAipi_RETE_AM::constantTestGT(int c,tstring id, tstring attr, tstring val, int pm, int categ )
{
	//This functions saves the variables of each lhs element.
	//pMainFrame->gsIVar.insert(id);
	//pMainFrame->gsAVar.insert(attr);
	//pMainFrame->gsVVar.insert(attr);
	
	//This process was already made in the parser, Method: emit_rule(AIPI_LHS);
	//So here it is just comment.

	
	//AfxMessageBox(_T("CONSTANT TEST GT"));
	/*
	CString str;
	str.Format(_T("Category...%d  " ), categ);
	AfxMessageBox(str);
	*/
	
	CAipi_RETE_Vars varo;
	
	//// *** GREATER THAN TEST **** //// 
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	//ID_AT_K
	if( categ == ID_AT_K )
	{
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
		//AfxMessageBox(_T("ID_AT_K"));
		
		if( !pMainFrame->gmmGT_I_A_K.empty() )
		{	
			CMainFrame::g_mmGT_I_A_K::iterator iter;
			iter = pMainFrame->gmmGT_I_A_K.find(val);
			if( iter == pMainFrame->gmmGT_I_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGT_I_A_K.insert(CMainFrame::g_mmGT_I_A_K::value_type( val, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));


				varo.addVar(id, AIPI_ID, key, c, GT, pm);
				varo.addVar(attr, AIPI_AT, key, c, GT, pm);
				
						
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, GT, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, GT, pm);
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGT_I_A_K.insert(CMainFrame::g_mmGT_I_A_K::value_type( val, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, GT, pm);
			varo.addVar(attr, AIPI_AT, key, c, GT, pm);
		}
			
	}//ID_K_VL
	
	else if( categ == ID_K_VL )
	{	
			
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmGT_I_K_V.empty() )
		{
			CMainFrame::g_mmGT_I_K_V::iterator iter;
			iter = pMainFrame->gmmGT_I_K_V.find(attr);
			if( iter == pMainFrame->gmmGT_I_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGT_I_K_V.insert(CMainFrame::g_mmGT_I_K_V::value_type( attr, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, GT, pm);
				varo.addVar(val, AIPI_VL, key, c, GT, pm);
				
		
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, GT, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, GT, pm);
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGT_I_K_V.insert(CMainFrame::g_mmGT_I_K_V::value_type( attr, key ));	
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, GT, pm);
			varo.addVar(val, AIPI_VL, key, c, GT, pm);
		
		}	
								
	}//ID_K_K

			
	else if( categ == ID_K_K )
	{
		//pMainFrame->gsIVar.insert(id);
		
		/*
		CString s;
		s.Format(_T("Constan Test Condition...%d  " ), c);
		AfxMessageBox(s);
		*/
		//AfxMessageBox(s.data());
		
				
		tstring str = attr + _T("|") + val;
												
		if( !pMainFrame->gmmGT_I_K_K.empty() )
		{
					
			CMainFrame::g_mmGT_I_K_K::iterator iter;
			iter = pMainFrame->gmmGT_I_K_K.find(str);
			if( iter == pMainFrame->gmmGT_I_K_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGT_I_K_K.insert(CMainFrame::g_mmGT_I_K_K::value_type(str, key ));	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, GT, pm);
				
				/*
				AfxMessageBox(_T("Inserta1"));
				s.Format(_T("AM...%d  " ), key);
				AfxMessageBox(s);				
				*/	
				//AfxMessageBox(s.c_str());				
		
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, GT, pm);
				/*
				AfxMessageBox(_T("Inserta2"));
				s.Format(_T("AM...%d  " ), iter->second);
				AfxMessageBox(s);
				*/
				//AfxMessageBox(s.c_str());				
		
				
			}	
		}	
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGT_I_K_K.insert(CMainFrame::g_mmGT_I_K_K::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, GT, pm);
			/*
			AfxMessageBox(_T("Inserta3"));
			s.Format(_T("AM...%d  " ), key);
			AfxMessageBox(s);
			*/
			//AfxMessageBox(s.c_str());				
		
			
		}
				
				
	}//K_AT_VL

		
	else if( categ == K_AT_VL )
	{
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmGT_K_A_V.empty() )
		{
			CMainFrame::g_mmGT_K_A_V::iterator iter;
			iter = pMainFrame->gmmGT_K_A_V.find(id);
			if( iter == pMainFrame->gmmGT_K_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGT_K_A_V.insert(CMainFrame::g_mmGT_K_A_V::value_type( id, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, GT, pm);
				varo.addVar(val, AIPI_VL, key, c, GT, pm);
			}
			else
			{	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, GT, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, GT, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGT_K_A_V.insert(CMainFrame::g_mmGT_K_A_V::value_type( id, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, GT, pm);
			varo.addVar(val, AIPI_VL, key, c, GT, pm);
		}
				
	}//K_AT_K
	else if( categ == K_AT_K )
	{
		//pMainFrame->gsAVar.insert(attr);
			
		tstring str = id + _T("|") + val;
				
		if( !pMainFrame->gmmGT_K_A_K.empty() )
		{
			CMainFrame::g_mmGT_K_A_K::iterator iter;
			iter = pMainFrame->gmmGT_K_A_K.find(str);
			if( iter == pMainFrame->gmmGT_K_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGT_K_A_K.insert(CMainFrame::g_mmGT_K_A_K::value_type( str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, GT, pm);
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, GT, pm);
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGT_K_A_K.insert(CMainFrame::g_mmGT_K_A_K::value_type( str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, GT, pm);
			
		}

	}//K_K_VL
	else if( categ == K_K_VL )
	{
				
		//pMainFrame->gsVVar.insert(val);
		
		tstring str = id + _T("|") + attr;
				
		if( !pMainFrame->gmmGT_K_K_V.empty() )
		{
			CMainFrame::g_mmGT_K_K_V::iterator iter;
			iter = pMainFrame->gmmGT_K_K_V.find(str);
			if( iter == pMainFrame->gmmGT_K_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGT_K_K_V.insert(CMainFrame::g_mmGT_K_K_V::value_type(str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(val, AIPI_VL, key, c, GT, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(val, AIPI_VL, iter->second, c, GT, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGT_K_K_V.insert(CMainFrame::g_mmGT_K_K_V::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(val, AIPI_VL, key, c, GT, pm);
		}
				
	}//K_K_K
	else if ((id.substr(0,1) != _T("[")) && (attr.substr(0,1) != _T("[")) && (val.substr(0,1) != _T("[")) )
	{	
		tstring str = id + _T("|") + attr + _T("|") + val;

		/*
		CString stri;
		stri.Format(_T("Constan Test Condition...%d  " ), c);
		AfxMessageBox(stri);				
		AfxMessageBox(str.data());
		*/
		
		//Works with constants only
		CAipi_WM wmo;
		wmo.insertGT_WM_Cond(c, id, attr, val);
				
		if( !pMainFrame->gmmGT_K_K_K.empty() )
		{
			CMainFrame::g_mmGT_K_K_K::iterator iter;
			iter = pMainFrame->gmmGT_K_K_K.find(str);
				
			if( iter == pMainFrame->gmmGT_K_K_K.end())
			{
				//AfxMessageBox(_T("Inserta"));
				//AfxMessageBox(str.c_str());				
		
				
				int key = generateAMKey();
				pMainFrame->gmmGT_K_K_K.insert(CMainFrame::g_mmGT_K_K_K::value_type( str , key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
			}
		}
		else
		{
			//AfxMessageBox(_T("Inserta"));
			//AfxMessageBox(str.c_str());				
		
			int key = generateAMKey();
			pMainFrame->gmmGT_K_K_K.insert(CMainFrame::g_mmGT_K_K_K::value_type( str , key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
		}
				
	}//ID_AT_VL
	else if ( categ == ID_AT_VL)
	{
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmGT_I_A_V.empty() )
		{
			CMainFrame::g_mmGT_I_A_V::iterator iter;
			iter = pMainFrame->gmmGT_I_A_V.find(_T("e"));
			if( iter == pMainFrame->gmmGT_I_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGT_I_A_V.insert(CMainFrame::g_mmGT_I_A_V::value_type( _T("e"), key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, GT, pm);
				varo.addVar(attr, AIPI_AT, key, c, GT, pm);
				varo.addVar(val, AIPI_VL, key, c, GT, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, GT, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, GT, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, GT, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGT_I_A_V.insert(CMainFrame::g_mmGT_I_A_V::value_type( _T("e"), key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, GT, pm);
			varo.addVar(attr, AIPI_AT, key, c, GT, pm);
			varo.addVar(val, AIPI_VL, key, c, GT, pm);
		}
				
	 }//Testing relational operations 
     else
	 {
		switch ( categ )
		{
		case ID_RO_VL :
			//pMainFrame->gsIVar.insert(id);
			//pMainFrame->gsVVar.insert(val);
			varo.addVar(id, AIPI_ID, UNDEFINE, c, GT, pm);
			varo.addVar(val, AIPI_VL, UNDEFINE, c, GT, pm);
			break;
		case ID_RO_K:
			//pMainFrame->gsIVar.insert(id);
			varo.addVar(id, AIPI_ID, UNDEFINE, c, GT, pm);
			break;
		case K_RO_K:
			break;
		case K_RO_VL:
			//pMainFrame->gsVVar.insert(val);
			varo.addVar(val, AIPI_VL, UNDEFINE, c, GT, pm);
			break;
		}
	 }

	//This process ( fill_PM_Vars(pm) ) was already made in the parser
	//Method: emit_rule( AIPI_RHS)
	
	//fillPM_Vars(pm);
}


void CAipi_RETE_AM::constantTestGE(int c,tstring id, tstring attr, tstring val, int pm, int categ )
{

	//This functions saves the variables of each lhs element.
	//pMainFrame->gsIVar.insert(id);
	//pMainFrame->gsAVar.insert(attr);
	//pMainFrame->gsVVar.insert(attr);
	
	//This process was already made in the parser, Method: emit_rule(AIPI_LHS);
	//So here it is just comment.

	//AfxMessageBox(_T("CONSTANT TEST GE"));
	
	CAipi_RETE_Vars varo;

//// *** GREATER OR EQUAL THAN TEST **** //// 

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	//ID_AT_K
	if( categ == ID_AT_K )
	{
			
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
		
		
		if( !pMainFrame->gmmGE_I_A_K.empty() )
		{	
			CMainFrame::g_mmGE_I_A_K::iterator iter;
			iter = pMainFrame->gmmGE_I_A_K.find(val);
			if( iter == pMainFrame->gmmGE_I_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGE_I_A_K.insert(CMainFrame::g_mmGE_I_A_K::value_type( val, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, GE, pm);
				varo.addVar(attr, AIPI_AT, key, c, GE, pm);
				
						
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, GE, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, GE, pm);
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGE_I_A_K.insert(CMainFrame::g_mmGE_I_A_K::value_type( val, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, GE, pm);
			varo.addVar(attr, AIPI_AT, key, c, GE, pm);
			
		}
			
	}//ID_K_VL
	
	else if( categ == ID_K_VL )
	{	
			
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmGE_I_K_V.empty() )
		{
			CMainFrame::g_mmGE_I_K_V::iterator iter;
			iter = pMainFrame->gmmGE_I_K_V.find(attr);
			if( iter == pMainFrame->gmmGE_I_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGE_I_K_V.insert(CMainFrame::g_mmGE_I_K_V::value_type( attr, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, GE, pm);
				varo.addVar(val, AIPI_VL, key, c, GE, pm);
				
		
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, GE, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, GE, pm);
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGE_I_K_V.insert(CMainFrame::g_mmGE_I_K_V::value_type( attr, key ));	
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, GE, pm);
			varo.addVar(val, AIPI_VL, key, c, GE, pm);
		
		}	
								
	}//ID_K_K

			
	else if( categ == ID_K_K )
	{
		
		//pMainFrame->gsIVar.insert(id);
				
		tstring str = attr + _T("|") + val;
												
		if( !pMainFrame->gmmGE_I_K_K.empty() )
		{
					
			CMainFrame::g_mmGE_I_K_K::iterator iter;
			iter = pMainFrame->gmmGE_I_K_K.find(str);
			if( iter == pMainFrame->gmmGE_I_K_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGE_I_K_K.insert(CMainFrame::g_mmGE_I_K_K::value_type(str, key ));	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, GE, pm);
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, GE, pm);
				
			}	
		}	
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGE_I_K_K.insert(CMainFrame::g_mmGE_I_K_K::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, GE, pm);
			
		}
				
				
	}//K_AT_VL

		
	else if( categ == K_AT_VL )
	{
		
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmGE_K_A_V.empty() )
		{
			CMainFrame::g_mmGE_K_A_V::iterator iter;
			iter = pMainFrame->gmmGE_K_A_V.find(id);
			if( iter == pMainFrame->gmmGT_K_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGE_K_A_V.insert(CMainFrame::g_mmGE_K_A_V::value_type( id, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, GE, pm);
				varo.addVar(val, AIPI_VL, key, c, GE, pm);
			}
			else
			{	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, GE, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, GE, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGE_K_A_V.insert(CMainFrame::g_mmGE_K_A_V::value_type( id, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, GE, pm);
			varo.addVar(val, AIPI_VL, key, c, GE, pm);
		}
				
	}//K_AT_K
	else if( categ == K_AT_K )
	{
		//pMainFrame->gsAVar.insert(attr);
				
		tstring str = id + _T("|") + val;
				
		if( !pMainFrame->gmmGE_K_A_K.empty() )
		{
			CMainFrame::g_mmGE_K_A_K::iterator iter;
			iter = pMainFrame->gmmGE_K_A_K.find(str);
			if( iter == pMainFrame->gmmGE_K_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGE_K_A_K.insert(CMainFrame::g_mmGE_K_A_K::value_type( str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, GE, pm);
			
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, GE, pm);
			
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGE_K_A_K.insert(CMainFrame::g_mmGE_K_A_K::value_type( str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, GE, pm);
		}

	}//K_K_VL
	else if( categ == K_K_VL )
	{
				
		//pMainFrame->gsVVar.insert(val);
		
		tstring str = id + _T("|") + attr;
				
		if( !pMainFrame->gmmGE_K_K_V.empty() )
		{
			CMainFrame::g_mmGE_K_K_V::iterator iter;
			iter = pMainFrame->gmmGE_K_K_V.find(str);
			if( iter == pMainFrame->gmmGE_K_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGE_K_K_V.insert(CMainFrame::g_mmGE_K_K_V::value_type(str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(val, AIPI_VL, key, c, GE, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(val, AIPI_VL, iter->second, c, GE, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGE_K_K_V.insert(CMainFrame::g_mmGE_K_K_V::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(val, AIPI_VL, key, c, GE, pm);
		}
				
	}//K_K_K
	else if ( categ == K_K_K )
	{	
		tstring str = id + _T("|") + attr + _T("|") + val;

				
		//Works with constants only
		CAipi_WM wmo;
		wmo.insertGE_WM_Cond(c, id, attr, val);
						
		if( !pMainFrame->gmmGE_K_K_K.empty() )
		{
			CMainFrame::g_mmGE_K_K_K::iterator iter;
			iter = pMainFrame->gmmGE_K_K_K.find(str);
				
			if( iter == pMainFrame->gmmGE_K_K_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGE_K_K_K.insert(CMainFrame::g_mmGE_K_K_K::value_type( str , key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGE_K_K_K.insert(CMainFrame::g_mmGE_K_K_K::value_type( str , key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
		}
				
	}//ID_AT_VL
	else if( categ == ID_AT_VL )
	{
		
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmGE_I_A_V.empty() )
		{
			CMainFrame::g_mmGE_I_A_V::iterator iter;
			iter = pMainFrame->gmmGE_I_A_V.find(_T("e"));
			if( iter == pMainFrame->gmmGE_I_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmGE_I_A_V.insert(CMainFrame::g_mmGE_I_A_V::value_type( _T("e"), key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, GE, pm);
				varo.addVar(attr, AIPI_AT, key, c, GE, pm);
				varo.addVar(val, AIPI_VL, key, c, GE, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, GE, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, GE, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, GE, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmGE_I_A_V.insert(CMainFrame::g_mmGE_I_A_V::value_type( _T("e"), key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, GE, pm);
			varo.addVar(attr, AIPI_AT, key, c, GE, pm);
			varo.addVar(val, AIPI_VL, key, c, GE, pm);
		}
				
	 }//Testing relational operations 
	 else
	 {		
		switch ( categ )
		{
			case ID_RO_VL :
				//pMainFrame->gsIVar.insert(id);
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, GE, pm);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, GE, pm);
				break;
			case ID_RO_K:
				//pMainFrame->gsIVar.insert(id);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, GE, pm);
				break;
			case K_RO_K:
				break;
			case K_RO_VL:
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, GE, pm);
				break;
		}
	 }	
	

	//This process ( fill_PM_Vars(pm) ) was already made in the parser
	//Method: emit_rule( AIPI_RHS)
	
	//fillPM_Vars(pm);

}








void CAipi_RETE_AM::constantTestAS(int c,tstring id, tstring attr, tstring val, int pm, int categ)
{
	//AfxMessageBox(_T("CONSTANT TEST AS"));

	/*
	CString str;
	str.Format(_T("Category...%d  " ), categ);
	AfxMessageBox(str);
	*/

	CAipi_RETE_Vars varo;
	
	//// *** ASSIGNATION TEST **** //// 
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	//ID_AT_K
	if( categ == ID_AT_K )
	{
			
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
		
		if( !pMainFrame->gmmAS_I_A_K.empty() )
		{	
			CMainFrame::g_mmAS_I_A_K::iterator iter;
			iter = pMainFrame->gmmAS_I_A_K.find(val);
			if( iter == pMainFrame->gmmAS_I_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmAS_I_A_K.insert(CMainFrame::g_mmAS_I_A_K::value_type( val, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, AS, pm);
				varo.addVar(attr, AIPI_AT, key, c, AS, pm);
				
						
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, AS, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, AS, pm);
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmAS_I_A_K.insert(CMainFrame::g_mmAS_I_A_K::value_type( val, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, AS, pm);
			varo.addVar(attr, AIPI_AT, key, c, AS, pm);
				
		}
			
	}//ID_K_VL
	
	else if( categ == ID_K_VL )
	{	
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmAS_I_K_V.empty() )
		{
			CMainFrame::g_mmAS_I_K_V::iterator iter;
			iter = pMainFrame->gmmAS_I_K_V.find(attr);
			if( iter == pMainFrame->gmmAS_I_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmAS_I_K_V.insert(CMainFrame::g_mmAS_I_K_V::value_type( attr, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
				
				varo.addVar(id, AIPI_ID, key, c, AS, pm);
				varo.addVar(val, AIPI_VL, key, c, AS, pm);
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, AS, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, AS, pm);
				
				
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmAS_I_K_V.insert(CMainFrame::g_mmAS_I_K_V::value_type( attr, key ));	
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, AS, pm);
			varo.addVar(val, AIPI_VL, key, c, AS, pm);
				
		
		}	
								
	}//ID_K_K

			
	else if( categ == ID_K_K )
	{
		//pMainFrame->gsIVar.insert(id);
		
		
		tstring str = attr + _T("|") + val;
												
		if( !pMainFrame->gmmAS_I_K_K.empty() )
		{
					
			CMainFrame::g_mmAS_I_K_K::iterator iter;
			iter = pMainFrame->gmmAS_I_K_K.find(str);
			if( iter == pMainFrame->gmmAS_I_K_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmAS_I_K_K.insert(CMainFrame::g_mmAS_I_K_K::value_type(str, key ));	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, AS, pm);
								

			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, AS, pm);
							

			}	
		}	
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmAS_I_K_K.insert(CMainFrame::g_mmAS_I_K_K::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
			
			varo.addVar(id, AIPI_ID, key, c, AS, pm);

		}
				
				
	}//K_AT_VL

		
	else if( categ == K_AT_VL )
	{
		
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		if( !pMainFrame->gmmAS_K_A_V.empty() )
		{
			CMainFrame::g_mmAS_K_A_V::iterator iter;
			iter = pMainFrame->gmmAS_K_A_V.find(id);
			if( iter == pMainFrame->gmmAS_K_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmAS_K_A_V.insert(CMainFrame::g_mmAS_K_A_V::value_type( id, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, AS, pm);
				varo.addVar(val, AIPI_VL, key, c, AS, pm);
			}
			else
			{	
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, AS, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, AS, pm);

			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmAS_K_A_V.insert(CMainFrame::g_mmAS_K_A_V::value_type( id, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, AS, pm);
			varo.addVar(val, AIPI_VL, key, c, AS, pm);
		}
				
	}//K_AT_K
	else if( categ == K_AT_K  )
	{
		//pMainFrame->gsAVar.insert(attr);
				
		tstring str = id + _T("|") + val;
				
		if( !pMainFrame->gmmAS_K_A_K.empty() )
		{
			CMainFrame::g_mmAS_K_A_K::iterator iter;
			iter = pMainFrame->gmmAS_K_A_K.find(str);
			if( iter == pMainFrame->gmmAS_K_A_K.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmAS_K_A_K.insert(CMainFrame::g_mmAS_K_A_K::value_type( str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(attr, AIPI_AT, key, c, AS, pm);
				
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(attr, AIPI_AT, iter->second, c, AS,  pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmAS_K_A_K.insert(CMainFrame::g_mmAS_K_A_K::value_type( str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(attr, AIPI_AT, key, c, AS, pm);
		}

	}//K_K_VL
	else if( categ == K_K_VL )
	{
		//pMainFrame->gsVVar.insert(val);
				
		tstring str = id + _T("|") + attr;
				
		if( !pMainFrame->gmmAS_K_K_V.empty() )
		{
			CMainFrame::g_mmAS_K_K_V::iterator iter;
			iter = pMainFrame->gmmAS_K_K_V.find(str);
			if( iter == pMainFrame->gmmAS_K_K_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmAS_K_K_V.insert(CMainFrame::g_mmAS_K_K_V::value_type(str, key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(val, AIPI_VL, key, c, AS, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(val, AIPI_VL, iter->second, c, AS, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmAS_K_K_V.insert(CMainFrame::g_mmAS_K_K_V::value_type(str, key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(val, AIPI_VL, key, c, AS, pm);
		}
				
	}//K_K_K
	else if (  categ == K_K_K )
	{	
		tstring str = id + _T("|") + attr + _T("|") + val;

		/*
		CString stri;
		stri.Format(_T("Constan Test Condition...%d  " ), c);
		AfxMessageBox(stri);				
		AfxMessageBox(str.data());
		*/
		
		CAipi_WM wmo;
		wmo.insertET_WM_Cond(c, id, attr, val);
				
		if( !pMainFrame->gmmAS_K_K_K.empty() )
		{
			CMainFrame::g_mmAS_K_K_K::iterator iter;
			iter = pMainFrame->gmmAS_K_K_K.find(str);
				
			if( iter == pMainFrame->gmmAS_K_K_K.end())
			{
				//AfxMessageBox(_T("Inserta"));
				//AfxMessageBox(str.c_str());				
		
				
				int key = generateAMKey();
				pMainFrame->gmmAS_K_K_K.insert(CMainFrame::g_mmAS_K_K_K::value_type( str , key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));
			}
		}
		else
		{
			//AfxMessageBox(_T("Inserta"));
			//AfxMessageBox(str.c_str());				
		
			int key = generateAMKey();
			pMainFrame->gmmAS_K_K_K.insert(CMainFrame::g_mmAS_K_K_K::value_type( str , key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));
		}
				
	}//ID_AT_VL
	else if( ID_AT_VL )
	{
		//pMainFrame->gsIVar.insert(id);
		//pMainFrame->gsAVar.insert(attr);
		//pMainFrame->gsVVar.insert(val);
		
		
		if( !pMainFrame->gmmAS_I_A_V.empty() )
		{
			CMainFrame::g_mmAS_I_A_V::iterator iter;
			iter = pMainFrame->gmmAS_I_A_V.find(_T("e"));
			if( iter == pMainFrame->gmmGT_I_A_V.end())
			{
				int key = generateAMKey();
				pMainFrame->gmmAS_I_A_V.insert(CMainFrame::g_mmAS_I_A_V::value_type( _T("e"), key ));
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

				varo.addVar(id, AIPI_ID, key, c, AS, pm);
				varo.addVar(attr, AIPI_AT, key, c, AS, pm);
				varo.addVar(val, AIPI_VL, key, c, AS, pm);
			}
			else
			{
				pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, iter->second));
				pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(iter->second, c));

				varo.addVar(id, AIPI_ID, iter->second, c, AS, pm);
				varo.addVar(attr, AIPI_AT, iter->second, c, AS, pm);
				varo.addVar(val, AIPI_VL, iter->second, c, AS, pm);
			}
		}
		else
		{
			int key = generateAMKey();
			pMainFrame->gmmAS_I_A_V.insert(CMainFrame::g_mmAS_I_A_V::value_type( _T("e"), key ));
			pMainFrame->gmCond_AM.insert(CMainFrame::g_mCond_AM::value_type(c, key));
			pMainFrame->gmmAM_Cond.insert(CMainFrame::g_mmAM_Cond::value_type(key,c));

			varo.addVar(id, AIPI_ID, key, c, AS, pm);
			varo.addVar(attr, AIPI_AT, key, c, AS, pm);
			varo.addVar(val, AIPI_VL, key, c, AS, pm);
		}
				
	 }//Testing relational operations 
	 else
	 {		
		switch ( categ )
		{
			AfxMessageBox(_T("AS Error, Asignaton can not manage relational operations"));
			case ID_RO_VL :
				//pMainFrame->gsIVar.insert(id);
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, AS, pm);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, AS, pm);
				break;
			case ID_RO_K:
				//pMainFrame->gsIVar.insert(id);
				varo.addVar(id, AIPI_ID, UNDEFINE, c, AS, pm);
				break;
			case K_RO_K:
				break;
			case K_RO_VL:
				//pMainFrame->gsVVar.insert(val);
				varo.addVar(val, AIPI_VL, UNDEFINE, c, AS, pm);
				break;
		}
	 }	
	 
	
	 


	//SE puede hacer con analizador léxico
	//fillPM_Vars(pm);

}


/////////////////////////////////////////////////////////////////////////////////////
/// End Constant Test ////
//////////////////////////////////////////////////////////////////////////////////////




int CAipi_RETE_AM::countAM_Cond(int am)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmAM_Cond::iterator iter;
    return  pMainFrame->gmmAM_Cond.count(am);

}

/*
int CAipi_RETE_AM::countWM_AM(int wm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmWM_AM::iterator iter;
    return  pMainFrame->gmmWM_AM.count(wm);

}
*/

int CAipi_RETE_AM::countAM_WM(int am)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmAM_WM::iterator iter;
    return  pMainFrame->gmmAM_WM.count(am);

}



int CAipi_RETE_AM::findAM_WM(int am)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmAM_WM::iterator iter;
    iter = pMainFrame->gmmAM_WM.find(am);
	if( iter != pMainFrame->gmmAM_WM.end())
	{
		return iter->second;
		
	}
	
	return NOT_FOUND;
	

}

/*
int CAipi_RETE_AM::findAM_WM(int wm)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmAM_WM::iterator iter;
   	
	for( iter = pMainFrame->gmmAM_WM.begin(); iter!= pMainFrame->gmmAM_WM.end(); ++iter)
	{
		if( iter->second == wm )
		{
			return iter->first;
		}	
	}
	
return NOT_FOUND;
}
*/



int CAipi_RETE_AM::findWM_AM(int wm)
{
    
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmWM_AM::iterator iter;
    iter = pMainFrame->gmmWM_AM.find(wm);
	if( iter != pMainFrame->gmmWM_AM.end())
	{
		return iter->second;
		
	}
	

/*
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWM_AM::iterator iter;
    iter = pMainFrame->gmWM_AM.find(wm);
	if( iter != pMainFrame->gmWM_AM.end())
	{
		return iter->second;
		
	}
*/


	return NOT_FOUND;
	

}



int CAipi_RETE_AM::findCond_AM(int c)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mCond_AM::iterator iter;
    iter = pMainFrame->gmCond_AM.find(c);
	if( iter != pMainFrame->gmCond_AM.end())
	{
		return iter->second;
		
	}
	
	return NOT_FOUND;
	

}

int CAipi_RETE_AM::findAM_Cond(int am)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmAM_Cond::iterator iter;
    iter = pMainFrame->gmmAM_Cond.find(am);
	if( iter != pMainFrame->gmmAM_Cond.end())
	{
		return iter->second;
		
	}
	
	return NOT_FOUND;
	

}







/*
int CAipi_RETE_AM::variableTest(tstring key)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
		
	if( findLHSE(key))
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

*/

/*
void CAipi_RETE_AM::printAMEs( int k )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	CString strCond =_T("C");
	
	CMainFrame::g_mmAM_WM::iterator iter = NULL;
	int n = pMainFrame->gmmAM_WM.count(k);

		if(n > 1 )	
		{
			strCond +=  _itot( iter->first, buffer, 10 );	
			pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
				
				pair <CMainFrame::g_mmAM_WM::iterator, CMainFrame::g_mmAM_WM::iterator>  pAM;
				pAM = pMainFrame->gmmAM_WM.equal_range(k);

				for(iter = pAM.first; iter != pAM.second; ++iter)
				{	
					CString strWME =_T("W");

					strWME +=  _itot( iter->second, buffer, 10 );
					pMainFrame->m_wndOutputTabView.AddMsg1(strWME);	
				}
		}
		else
		{
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("No existen elementos"));	
		}
				
	  	 
}
*/

int CAipi_RETE_AM::largerItemAM_WM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_WM::const_iterator it_AM;
	if(pMainFrame->gmmAM_WM.empty())
	{
		return EMPTY;
	}
	
	it_AM = pMainFrame->gmmAM_WM.begin();
	int maxAM = it_AM->first;
	int nAM = pMainFrame->gmmAM_WM.count(maxAM);
	
	
	for( CMainFrame::g_mLHS::const_iterator it_LHS = pMainFrame->gmLHS.begin(); it_LHS!= pMainFrame->gmLHS.end(); ++it_LHS)
	{
		int tempAM = pMainFrame->gmmAM_WM.count(it_LHS->first);
		if(  tempAM > nAM )
		{
			nAM = tempAM;
			maxAM = it_LHS->first;
		}
	}

return maxAM;	
}	

	
bool CAipi_RETE_AM::isNumber(tstring c)
{
	c = c.substr(0, 1);
	
	//AfxMessageBox(c.data());

	if ( c == _T("1") || c == _T("2") || c == _T("3") || c == _T("4") || c == _T("5") || c == _T("6") || c == _T("7") || c == _T("8") || c == _T("9") )
	{
		return true;
	}

	if( c == _T("-") )
	{
		c.substr(0, 2);
		if ( c == _T("1") || c == _T("2") || c == _T("3") || c == _T("4") || c == _T("5") || c == _T("6") || c == _T("7") || c == _T("8") || c == _T("9") )
		{
			return true;
		}
	}

return false;
}


bool CAipi_RETE_AM::isVariable(tstring c)
{
	c = c.substr(0, 1);
	
	//AfxMessageBox(c.data());

	if ( c == _T("["))
	{
		return true;
	}

return false;
}


int CAipi_RETE_AM::isType(tstring c)
{
	
	if( isNumber(c) == true )
	{
		int pos = c.find('.');
		int nWords	= c.size();
		int nDecimal = nWords - pos;

		if( pos == -1 )
		{
			if( nWords > 8 )
				return AIPI_LONG;
			else 
				return AIPI_INT;
		}
	
		if( nDecimal > 6 )
			return AIPI_DOUBLE;
		else
			return AIPI_FLOAT;
	}
	else
	{
			return AIPI_STRING;
	}
	
return NOT_FOUND;
}


int CAipi_RETE_AM::saveConstDataNum(int pm, int c2, int type, tstring varName, tstring varData )
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
	
	int k = UNDEFINE;
	int wm = UNDEFINE;
	int	bm = UNDEFINE;
	int old_tk = UNDEFINE;



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
	case AIPI_INT :
		if(isNumber(varData))
		{
			intData = _ttoi(varData.data());
			typInt.addTypeInt(varName, pm, c2, intData, wm, bm, old_tk);
			k = POSITIVE;
		}
		break;
	case AIPI_LONG :
		if( isNumber(varData))
		{
			longData = _ttol(varData.data());
			typLong.addTypeLong(varName, pm, c2, longData, wm, bm, old_tk);
			k = POSITIVE;
		}
		break;
	case AIPI_FLOAT :
		if(isNumber(varData))
		{
			floatData = _tcstod(varData.data(), NULL);
			typFloat.addTypeFloat(varName, pm, c2, floatData, wm, bm, old_tk);
			k = POSITIVE;
		}
		break;
	case AIPI_DOUBLE :
		if( isNumber(varData))
		{
			doubleData = _tcstod(varData.data(), NULL);
			typDouble.addTypeDouble(varName, pm, c2, doubleData, wm, bm, old_tk);
			k = POSITIVE;
		}
		break;
	case AIPI_STRING :
		typString.addTypeString(varName, pm, c2, varData, wm, bm, old_tk);
		k = POSITIVE;
		break;

	}
	
	k = NEGATIVE;
	

return k;
}




void CAipi_RETE_AM::fillAM_WM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	addAM_WM(1,1);
	addAM_WM(2,2);
	addAM_WM(3,3);
	addAM_WM(4,4);
	addAM_WM(5,5);
	addAM_WM(6,6);
	addAM_WM(7,7);
	addAM_WM(8,8);

	CString f;
	f.Format(_T("AM SIZE ...%d"), pMainFrame->gmmAM_WM.size());
	pMainFrame->m_wndOutputTabView.AddMsg1(f);

}


void CAipi_RETE_AM::printAM_WM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Alpha Memory - Working Memory  *******"));
	//Print map container
	for( CMainFrame::g_mmAM_WM::const_iterator iter = pMainFrame->gmmAM_WM.begin(); iter!= pMainFrame->gmmAM_WM.end(); ++iter)
	{
		CString strAM =_T("A");
		CString strWME =_T("W");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AME - WME *******"));
		strAM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		strWME +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWME);
			
	}


}




void CAipi_RETE_AM::printWM_AM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Working Memory - Alpha Memory  *******"));
	//Print map container
	
	for( CMainFrame::g_mmWM_AM::const_iterator iter = pMainFrame->gmmWM_AM.begin(); iter!= pMainFrame->gmmWM_AM.end(); ++iter)
	{
		CString strWME =_T("W");
		CString strAM =_T("A");
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  WME - AME *******"));
		strWME +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWME);
		strAM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
			
	}


	/*
	for( CMainFrame::g_mWM_AM::const_iterator iter = pMainFrame->gmWM_AM.begin(); iter!= pMainFrame->gmWM_AM.end(); ++iter)
	{
		CString strWME =_T("W");
		CString strAM =_T("A");
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  WME - AME *******"));
		strWME +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWME);
		strAM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
			
	}
*/


}


void CAipi_RETE_AM::printCond_AM()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Condition - Alpha Memory  *******"));
	//Print map container
	for( CMainFrame::g_mCond_AM::const_iterator iter = pMainFrame->gmCond_AM.begin(); iter!= pMainFrame->gmCond_AM.end(); ++iter)
	{
		CString strCond =_T("C");
		CString strAM =_T("A");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  C - AME  *******"));
		strCond +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
		strAM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
			
	}


}

void CAipi_RETE_AM::printAM_Cond()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[20];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Alpha Memory - Condition  *******"));
	//Print map container
	for( CMainFrame::g_mmAM_Cond::const_iterator iter = pMainFrame->gmmAM_Cond.begin(); iter!= pMainFrame->gmmAM_Cond.end(); ++iter)
	{
		CString strAM =_T("A");
		CString strCond =_T("C");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AME - C  *******"));
		strAM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		strCond +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);
			
	}


}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void CAipi_RETE_AM::printEQ_e_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  EQ_e_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmEQ_I_A_V::const_iterator iter = pMainFrame->gmmEQ_I_A_V.begin(); iter!= pMainFrame->gmmEQ_I_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}

void CAipi_RETE_AM::printEQ_e_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  EQ_e_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmEQ_I_K_V::const_iterator iter = pMainFrame->gmmEQ_I_K_V.begin(); iter!= pMainFrame->gmmEQ_I_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}


void CAipi_RETE_AM::printEQ_e_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  EQ_e_A_V  *******"));

	//Print map container
	for( CMainFrame::g_mmEQ_I_K_K::const_iterator iter = pMainFrame->gmmEQ_I_K_K.begin(); iter!= pMainFrame->gmmEQ_I_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
			
	}


}

void CAipi_RETE_AM::printEQ_e_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  EQ_e_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmEQ_I_A_K::const_iterator iter = pMainFrame->gmmEQ_I_A_K.begin(); iter!= pMainFrame->gmmEQ_I_A_K.end(); ++iter)
	{
		
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printEQ_I_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  EQ_I_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmEQ_K_K_V::const_iterator iter = pMainFrame->gmmEQ_K_K_V.begin(); iter!= pMainFrame->gmmEQ_K_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printEQ_I_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  EQ_I_A_V  *******"));
	//Print map container
	for( CMainFrame::g_mmEQ_K_K_K::const_iterator iter = pMainFrame->gmmEQ_K_K_K.begin(); iter!= pMainFrame->gmmEQ_K_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printEQ_I_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  EQ_I_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmEQ_K_A_V::const_iterator iter = pMainFrame->gmmEQ_K_A_V.begin(); iter!= pMainFrame->gmmEQ_K_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printEQ_I_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  EQ_I_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmEQ_K_A_K::const_iterator iter = pMainFrame->gmmEQ_K_A_K.begin(); iter!= pMainFrame->gmmEQ_K_A_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printEQ()
{
	printEQ_e_e_e();
	printEQ_e_e_V();
	printEQ_e_A_e();
	printEQ_e_A_V();
	printEQ_I_e_e();
	printEQ_I_e_V();
	printEQ_I_A_e();
	printEQ_I_A_V();

}





void CAipi_RETE_AM::printET_e_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ET_e_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmET_I_A_V::const_iterator iter = pMainFrame->gmmET_I_A_V.begin(); iter!= pMainFrame->gmmET_I_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}

void CAipi_RETE_AM::printET_e_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ET_e_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmET_I_K_V::const_iterator iter = pMainFrame->gmmET_I_K_V.begin(); iter!= pMainFrame->gmmET_I_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}


void CAipi_RETE_AM::printET_e_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ET_e_A_V  *******"));

	//Print map container
	for( CMainFrame::g_mmET_I_K_K::const_iterator iter = pMainFrame->gmmET_I_K_K.begin(); iter!= pMainFrame->gmmET_I_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
			
	}


}

void CAipi_RETE_AM::printET_e_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ET_e_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmET_I_A_K::const_iterator iter = pMainFrame->gmmET_I_A_K.begin(); iter!= pMainFrame->gmmET_I_A_K.end(); ++iter)
	{
		
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printET_I_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ET_I_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmET_K_K_V::const_iterator iter = pMainFrame->gmmET_K_K_V.begin(); iter!= pMainFrame->gmmET_K_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printET_I_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ET_I_A_V  *******"));
	//Print map container
	for( CMainFrame::g_mmET_K_K_K::const_iterator iter = pMainFrame->gmmET_K_K_K.begin(); iter!= pMainFrame->gmmET_K_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printET_I_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ET_I_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmET_K_A_V::const_iterator iter = pMainFrame->gmmET_K_A_V.begin(); iter!= pMainFrame->gmmET_K_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printET_I_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ET_I_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmET_K_A_K::const_iterator iter = pMainFrame->gmmET_K_A_K.begin(); iter!= pMainFrame->gmmET_K_A_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printET()
{
	printET_e_e_e();
	printET_e_e_V();
	printET_e_A_e();
	printET_e_A_V();
	printET_I_e_e();
	printET_I_e_V();
	printET_I_A_e();
	printET_I_A_V();

}



void CAipi_RETE_AM::printLT_e_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LT_e_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmLT_I_A_V::const_iterator iter = pMainFrame->gmmLT_I_A_V.begin(); iter!= pMainFrame->gmmLT_I_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}

void CAipi_RETE_AM::printLT_e_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LT_e_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmLT_I_K_V::const_iterator iter = pMainFrame->gmmLT_I_K_V.begin(); iter!= pMainFrame->gmmLT_I_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}


void CAipi_RETE_AM::printLT_e_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LT_e_A_V  *******"));

	//Print map container
	for( CMainFrame::g_mmLT_I_K_K::const_iterator iter = pMainFrame->gmmLT_I_K_K.begin(); iter!= pMainFrame->gmmLT_I_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
			
	}


}

void CAipi_RETE_AM::printLT_e_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LT_e_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmLT_I_A_K::const_iterator iter = pMainFrame->gmmLT_I_A_K.begin(); iter!= pMainFrame->gmmLT_I_A_K.end(); ++iter)
	{
		
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printLT_I_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LT_I_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmLT_K_K_V::const_iterator iter = pMainFrame->gmmLT_K_K_V.begin(); iter!= pMainFrame->gmmLT_K_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printLT_I_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LT_I_A_V  *******"));
	//Print map container
	for( CMainFrame::g_mmLT_K_K_K::const_iterator iter = pMainFrame->gmmLT_K_K_K.begin(); iter!= pMainFrame->gmmLT_K_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printLT_I_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LT_I_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmLT_K_A_V::const_iterator iter = pMainFrame->gmmLT_K_A_V.begin(); iter!= pMainFrame->gmmLT_K_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printLT_I_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LT_I_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmLT_K_A_K::const_iterator iter = pMainFrame->gmmLT_K_A_K.begin(); iter!= pMainFrame->gmmLT_K_A_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printLT()
{
	printLT_e_e_e();
	printLT_e_e_V();
	printLT_e_A_e();
	printLT_e_A_V();
	printLT_I_e_e();
	printLT_I_e_V();
	printLT_I_A_e();
	printLT_I_A_V();

}


void CAipi_RETE_AM::printLE_e_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LE_e_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmLE_I_A_V::const_iterator iter = pMainFrame->gmmLE_I_A_V.begin(); iter!= pMainFrame->gmmLE_I_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}

void CAipi_RETE_AM::printLE_e_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LE_e_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmLE_I_K_V::const_iterator iter = pMainFrame->gmmLE_I_K_V.begin(); iter!= pMainFrame->gmmLE_I_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}


void CAipi_RETE_AM::printLE_e_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LE_e_A_V  *******"));

	//Print map container
	for( CMainFrame::g_mmLE_I_K_K::const_iterator iter = pMainFrame->gmmLE_I_K_K.begin(); iter!= pMainFrame->gmmLE_I_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
			
	}


}

void CAipi_RETE_AM::printLE_e_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LE_e_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmLE_I_A_K::const_iterator iter = pMainFrame->gmmLE_I_A_K.begin(); iter!= pMainFrame->gmmLE_I_A_K.end(); ++iter)
	{
		
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printLE_I_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LE_I_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmLE_K_K_V::const_iterator iter = pMainFrame->gmmLE_K_K_V.begin(); iter!= pMainFrame->gmmLE_K_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printLE_I_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LE_I_A_V  *******"));
	//Print map container
	for( CMainFrame::g_mmLE_K_K_K::const_iterator iter = pMainFrame->gmmLE_K_K_K.begin(); iter!= pMainFrame->gmmLE_K_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printLE_I_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LE_I_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmLE_K_A_V::const_iterator iter = pMainFrame->gmmLE_K_A_V.begin(); iter!= pMainFrame->gmmLE_K_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printLE_I_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  LE_I_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmLE_K_A_K::const_iterator iter = pMainFrame->gmmLE_K_A_K.begin(); iter!= pMainFrame->gmmLE_K_A_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printLE()
{
	printLE_e_e_e();
	printLE_e_e_V();
	printLE_e_A_e();
	printLE_e_A_V();
	printLE_I_e_e();
	printLE_I_e_V();
	printLE_I_A_e();
	printLE_I_A_V();

}

void CAipi_RETE_AM::printGT_e_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GT_e_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmGT_I_A_V::const_iterator iter = pMainFrame->gmmGT_I_A_V.begin(); iter!= pMainFrame->gmmGT_I_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}

void CAipi_RETE_AM::printGT_e_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GT_e_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmGT_I_K_V::const_iterator iter = pMainFrame->gmmGT_I_K_V.begin(); iter!= pMainFrame->gmmGT_I_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}


void CAipi_RETE_AM::printGT_e_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GT_e_A_V  *******"));

	//Print map container
	for( CMainFrame::g_mmGT_I_K_K::const_iterator iter = pMainFrame->gmmGT_I_K_K.begin(); iter!= pMainFrame->gmmGT_I_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
			
	}


}

void CAipi_RETE_AM::printGT_e_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GT_e_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmGT_I_A_K::const_iterator iter = pMainFrame->gmmGT_I_A_K.begin(); iter!= pMainFrame->gmmGT_I_A_K.end(); ++iter)
	{
		
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printGT_I_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GT_I_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmGT_K_K_V::const_iterator iter = pMainFrame->gmmGT_K_K_V.begin(); iter!= pMainFrame->gmmGT_K_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printGT_I_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GT_I_A_V  *******"));
	//Print map container
	for( CMainFrame::g_mmGT_K_K_K::const_iterator iter = pMainFrame->gmmGT_K_K_K.begin(); iter!= pMainFrame->gmmGT_K_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printGT_I_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GT_I_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmGT_K_A_V::const_iterator iter = pMainFrame->gmmGT_K_A_V.begin(); iter!= pMainFrame->gmmGT_K_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printGT_I_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GT_I_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmGT_K_A_K::const_iterator iter = pMainFrame->gmmGT_K_A_K.begin(); iter!= pMainFrame->gmmGT_K_A_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printGT()
{
	printGT_e_e_e();
	printGT_e_e_V();
	printGT_e_A_e();
	printGT_e_A_V();
	printGT_I_e_e();
	printGT_I_e_V();
	printGT_I_A_e();
	printGT_I_A_V();

}

void CAipi_RETE_AM::printGE_e_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GE_e_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmGE_I_A_V::const_iterator iter = pMainFrame->gmmGE_I_A_V.begin(); iter!= pMainFrame->gmmGE_I_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}

void CAipi_RETE_AM::printGE_e_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GE_e_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmGE_I_K_V::const_iterator iter = pMainFrame->gmmGE_I_K_V.begin(); iter!= pMainFrame->gmmGE_I_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}


void CAipi_RETE_AM::printGE_e_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GE_e_A_V  *******"));

	//Print map container
	for( CMainFrame::g_mmGE_I_K_K::const_iterator iter = pMainFrame->gmmGE_I_K_K.begin(); iter!= pMainFrame->gmmGE_I_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
			
	}


}

void CAipi_RETE_AM::printGE_e_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GE_e_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmGE_I_A_K::const_iterator iter = pMainFrame->gmmGE_I_A_K.begin(); iter!= pMainFrame->gmmGE_I_A_K.end(); ++iter)
	{
		
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printGE_I_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GE_I_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmGE_K_K_V::const_iterator iter = pMainFrame->gmmGE_K_K_V.begin(); iter!= pMainFrame->gmmGE_K_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printGE_I_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GE_I_A_V  *******"));
	//Print map container
	for( CMainFrame::g_mmGE_K_K_K::const_iterator iter = pMainFrame->gmmGE_K_K_K.begin(); iter!= pMainFrame->gmmGE_K_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printGE_I_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GE_I_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmGE_K_A_V::const_iterator iter = pMainFrame->gmmGE_K_A_V.begin(); iter!= pMainFrame->gmmGE_K_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printGE_I_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  GE_I_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmGE_K_A_K::const_iterator iter = pMainFrame->gmmGE_K_A_K.begin(); iter!= pMainFrame->gmmGE_K_A_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printGE()
{
	printGE_e_e_e();
	printGE_e_e_V();
	printGE_e_A_e();
	printGE_e_A_V();
	printGE_I_e_e();
	printGE_I_e_V();
	printGE_I_A_e();
	printGE_I_A_V();

}




void CAipi_RETE_AM::printNE_e_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NE_e_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmNE_I_A_V::const_iterator iter = pMainFrame->gmmNE_I_A_V.begin(); iter!= pMainFrame->gmmNE_I_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}

void CAipi_RETE_AM::printNE_e_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NE_e_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmNE_I_K_V::const_iterator iter = pMainFrame->gmmNE_I_K_V.begin(); iter!= pMainFrame->gmmNE_I_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}


void CAipi_RETE_AM::printNE_e_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NE_e_A_V  *******"));

	//Print map container
	for( CMainFrame::g_mmNE_I_K_K::const_iterator iter = pMainFrame->gmmNE_I_K_K.begin(); iter!= pMainFrame->gmmNE_I_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
			
	}


}

void CAipi_RETE_AM::printNE_e_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NE_e_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmNE_I_A_K::const_iterator iter = pMainFrame->gmmNE_I_A_K.begin(); iter!= pMainFrame->gmmNE_I_A_K.end(); ++iter)
	{
		
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printNE_I_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NE_I_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmNE_K_K_V::const_iterator iter = pMainFrame->gmmNE_K_K_V.begin(); iter!= pMainFrame->gmmNE_K_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printNE_I_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NE_I_A_V  *******"));
	//Print map container
	for( CMainFrame::g_mmNE_K_K_K::const_iterator iter = pMainFrame->gmmNE_K_K_K.begin(); iter!= pMainFrame->gmmNE_K_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printNE_I_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NE_I_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmNE_K_A_V::const_iterator iter = pMainFrame->gmmNE_K_A_V.begin(); iter!= pMainFrame->gmmNE_K_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printNE_I_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  NE_I_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmNE_K_A_K::const_iterator iter = pMainFrame->gmmNE_K_A_K.begin(); iter!= pMainFrame->gmmNE_K_A_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printNE()
{
	printNE_e_e_e();
	printNE_e_e_V();
	printNE_e_A_e();
	printNE_e_A_V();
	printNE_I_e_e();
	printNE_I_e_V();
	printNE_I_A_e();
	printNE_I_A_V();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CAipi_RETE_AM::printAS_e_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AS_e_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmAS_I_A_V::const_iterator iter = pMainFrame->gmmAS_I_A_V.begin(); iter!= pMainFrame->gmmAS_I_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}

void CAipi_RETE_AM::printAS_e_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AS_e_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmAS_I_K_V::const_iterator iter = pMainFrame->gmmAS_I_K_V.begin(); iter!= pMainFrame->gmmAS_I_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
		
	}


}


void CAipi_RETE_AM::printAS_e_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AS_e_A_V  *******"));

	//Print map container
	for( CMainFrame::g_mmAS_I_K_K::const_iterator iter = pMainFrame->gmmAS_I_K_K.begin(); iter!= pMainFrame->gmmAS_I_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
			
	}


}

void CAipi_RETE_AM::printAS_e_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AS_e_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmAS_I_A_K::const_iterator iter = pMainFrame->gmmAS_I_A_K.begin(); iter!= pMainFrame->gmmAS_I_A_K.end(); ++iter)
	{
		
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printAS_I_A_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AS_I_A_e  *******"));
	//Print map container
	for( CMainFrame::g_mmAS_K_K_V::const_iterator iter = pMainFrame->gmmAS_K_K_V.begin(); iter!= pMainFrame->gmmAS_K_K_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printAS_I_A_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AS_I_A_V  *******"));
	//Print map container
	for( CMainFrame::g_mmAS_K_K_K::const_iterator iter = pMainFrame->gmmAS_K_K_K.begin(); iter!= pMainFrame->gmmAS_K_K_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}

void CAipi_RETE_AM::printAS_I_e_e()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AS_I_e_e  *******"));
	//Print map container
	for( CMainFrame::g_mmAS_K_A_V::const_iterator iter = pMainFrame->gmmAS_K_A_V.begin(); iter!= pMainFrame->gmmAS_K_A_V.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printAS_I_e_V()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AS_I_e_V  *******"));
	//Print map container
	for( CMainFrame::g_mmAS_K_A_K::const_iterator iter = pMainFrame->gmmAS_K_A_K.begin(); iter!= pMainFrame->gmmAS_K_A_K.end(); ++iter)
	{
		tstring val	= iter->first;
		CString strAM =_T("A");
		strAM +=  _itot( iter->second, buffer, 10 );
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("**************"));
		pMainFrame->m_wndOutputTabView.AddMsg1(val.data());
		pMainFrame->m_wndOutputTabView.AddMsg1(strAM);
		
	}


}


void CAipi_RETE_AM::printAS()
{
	printAS_e_e_e();
	printAS_e_e_V();
	printAS_e_A_e();
	printAS_e_A_V();
	printAS_I_e_e();
	printAS_I_e_V();
	printAS_I_A_e();
	printAS_I_A_V();

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//EQ
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


tstring CAipi_RETE_AM::findAM_EQ_I_K_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	for( CMainFrame::g_mmEQ_I_K_V::const_iterator iter = pMainFrame->gmmEQ_I_K_V.begin(); iter!= pMainFrame->gmmEQ_I_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
		
	}

return _T("NOT_FOUND");
}

tstring CAipi_RETE_AM::findAM_EQ_I_K_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
		
	for( CMainFrame::g_mmEQ_I_K_K::const_iterator iter = pMainFrame->gmmEQ_I_K_K.begin(); iter!= pMainFrame->gmmEQ_I_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}		
	}

return _T("NOT_FOUND");
}



tstring CAipi_RETE_AM::findAM_EQ_I_A_V(int am)
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	for( CMainFrame::g_mmEQ_I_A_V::const_iterator iter = pMainFrame->gmmEQ_I_A_V.begin(); iter!= pMainFrame->gmmEQ_I_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
		
	}
return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_EQ_I_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmEQ_I_A_K::const_iterator iter = pMainFrame->gmmEQ_I_A_K.begin(); iter!= pMainFrame->gmmEQ_I_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
		
	}
return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_EQ_K_K_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  EQ_I_A_e  *******"));
	
	for( CMainFrame::g_mmEQ_K_K_V::const_iterator iter = pMainFrame->gmmEQ_K_K_V.begin(); iter!= pMainFrame->gmmEQ_K_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
		
	}
return _T("NOT_FOUND");
}



tstring CAipi_RETE_AM::findAM_EQ_K_K_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	for( CMainFrame::g_mmEQ_K_K_K::const_iterator iter = pMainFrame->gmmEQ_K_K_K.begin(); iter!= pMainFrame->gmmEQ_K_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
		
	}
return _T("NOT_FOUND");

}


tstring CAipi_RETE_AM::findAM_EQ_K_A_V(int am)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	for( CMainFrame::g_mmEQ_K_A_V::const_iterator iter = pMainFrame->gmmEQ_K_A_V.begin(); iter!= pMainFrame->gmmEQ_K_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
		
	}
return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_EQ_K_A_K(int am)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmEQ_K_A_K::const_iterator iter = pMainFrame->gmmEQ_K_A_K.begin(); iter!= pMainFrame->gmmEQ_K_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}
return _T("NOT_FOUND");

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//ET
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tstring CAipi_RETE_AM::findAM_ET_I_K_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmET_I_K_V::const_iterator iter = pMainFrame->gmmET_I_K_V.begin(); iter!= pMainFrame->gmmET_I_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}		
		
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_ET_I_K_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmET_I_K_K::const_iterator iter = pMainFrame->gmmET_I_K_K.begin(); iter!= pMainFrame->gmmET_I_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
			
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_ET_I_A_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmET_I_A_V::const_iterator iter = pMainFrame->gmmET_I_A_V.begin(); iter!= pMainFrame->gmmET_I_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
		
	}

return _T("NOT_FOUND");
}



tstring CAipi_RETE_AM::findAM_ET_I_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmET_I_A_K::const_iterator iter = pMainFrame->gmmET_I_A_K.begin(); iter!= pMainFrame->gmmET_I_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
		
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_ET_K_K_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmET_K_K_V::const_iterator iter = pMainFrame->gmmET_K_K_V.begin(); iter!= pMainFrame->gmmET_K_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
		
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_ET_K_K_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	for( CMainFrame::g_mmET_K_K_K::const_iterator iter = pMainFrame->gmmET_K_K_K.begin(); iter!= pMainFrame->gmmET_K_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
		
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_ET_K_A_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmET_K_A_V::const_iterator iter = pMainFrame->gmmET_K_A_V.begin(); iter!= pMainFrame->gmmET_K_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_ET_K_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmET_K_A_K::const_iterator iter = pMainFrame->gmmET_K_A_K.begin(); iter!= pMainFrame->gmmET_K_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
	}
return _T("NOT_FOUND");
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// GE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


tstring CAipi_RETE_AM::findAM_GE_I_A_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGE_I_A_V::const_iterator iter = pMainFrame->gmmGE_I_A_V.begin(); iter!= pMainFrame->gmmGE_I_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");

}


tstring CAipi_RETE_AM::findAM_GE_I_K_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGE_I_K_V::const_iterator iter = pMainFrame->gmmGE_I_K_V.begin(); iter!= pMainFrame->gmmGE_I_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");

}


tstring CAipi_RETE_AM::findAM_GE_I_K_K(int am)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGE_I_K_K::const_iterator iter = pMainFrame->gmmGE_I_K_K.begin(); iter!= pMainFrame->gmmGE_I_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}				
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_GE_I_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGE_I_A_K::const_iterator iter = pMainFrame->gmmGE_I_A_K.begin(); iter!= pMainFrame->gmmGE_I_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}			
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_GE_K_K_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGE_K_K_V::const_iterator iter = pMainFrame->gmmGE_K_K_V.begin(); iter!= pMainFrame->gmmGE_K_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}		
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_GE_K_K_K(int am)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGE_K_K_K::const_iterator iter = pMainFrame->gmmGE_K_K_K.begin(); iter!= pMainFrame->gmmGE_K_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
		
	}
return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_GE_K_A_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGE_K_A_V::const_iterator iter = pMainFrame->gmmGE_K_A_V.begin(); iter!= pMainFrame->gmmGE_K_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
		
	}

return _T("NOT_FOUND");
}



tstring CAipi_RETE_AM::findAM_GE_K_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGE_K_A_K::const_iterator iter = pMainFrame->gmmGE_K_A_K.begin(); iter!= pMainFrame->gmmGE_K_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// GT
///////////////////////////////////////////////////////////////////////////////////////////////////////////



tstring CAipi_RETE_AM::findAM_GT_I_A_V(int am)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGT_I_A_V::const_iterator iter = pMainFrame->gmmGT_I_A_V.begin(); iter!= pMainFrame->gmmGT_I_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_GT_I_K_V(int am)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGT_I_K_V::const_iterator iter = pMainFrame->gmmGT_I_K_V.begin(); iter!= pMainFrame->gmmGT_I_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
		
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_GT_I_K_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGT_I_K_K::const_iterator iter = pMainFrame->gmmGT_I_K_K.begin(); iter!= pMainFrame->gmmGT_I_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
			
	}

return _T("NOT_FOUND");
}



tstring CAipi_RETE_AM::findAM_GT_I_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGT_I_A_K::const_iterator iter = pMainFrame->gmmGT_I_A_K.begin(); iter!= pMainFrame->gmmGT_I_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}



tstring CAipi_RETE_AM::findAM_GT_K_K_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGT_K_K_V::const_iterator iter = pMainFrame->gmmGT_K_K_V.begin(); iter!= pMainFrame->gmmGT_K_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
		
	}

return _T("NOT_FOUND");
}



tstring CAipi_RETE_AM::findAM_GT_K_K_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGT_K_K_K::const_iterator iter = pMainFrame->gmmGT_K_K_K.begin(); iter!= pMainFrame->gmmGT_K_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
	
	}

return _T("NOT_FOUND");
}



tstring CAipi_RETE_AM::findAM_GT_K_A_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGT_K_A_V::const_iterator iter = pMainFrame->gmmGT_K_A_V.begin(); iter!= pMainFrame->gmmGT_K_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_GT_K_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmGT_K_A_K::const_iterator iter = pMainFrame->gmmGT_K_A_K.begin(); iter!= pMainFrame->gmmGT_K_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// LE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


tstring CAipi_RETE_AM::findAM_LE_I_A_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLE_I_A_V::const_iterator iter = pMainFrame->gmmLE_I_A_V.begin(); iter!= pMainFrame->gmmLE_I_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}



tstring CAipi_RETE_AM::findAM_LE_I_K_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLE_I_K_V::const_iterator iter = pMainFrame->gmmLE_I_K_V.begin(); iter!= pMainFrame->gmmLE_I_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LE_I_K_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLE_I_K_K::const_iterator iter = pMainFrame->gmmLE_I_K_K.begin(); iter!= pMainFrame->gmmLE_I_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}		
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LE_I_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLE_I_A_K::const_iterator iter = pMainFrame->gmmLE_I_A_K.begin(); iter!= pMainFrame->gmmLE_I_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LE_K_K_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLE_K_K_V::const_iterator iter = pMainFrame->gmmLE_K_K_V.begin(); iter!= pMainFrame->gmmLE_K_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}		
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LE_K_K_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLE_K_K_K::const_iterator iter = pMainFrame->gmmLE_K_K_K.begin(); iter!= pMainFrame->gmmLE_K_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LE_K_A_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLE_K_A_V::const_iterator iter = pMainFrame->gmmLE_K_A_V.begin(); iter!= pMainFrame->gmmLE_K_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LE_K_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLE_K_A_K::const_iterator iter = pMainFrame->gmmLE_K_A_K.begin(); iter!= pMainFrame->gmmLE_K_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// LT
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



tstring CAipi_RETE_AM::findAM_LT_I_A_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLT_I_A_V::const_iterator iter = pMainFrame->gmmLT_I_A_V.begin(); iter!= pMainFrame->gmmLT_I_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LT_I_K_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLT_I_K_V::const_iterator iter = pMainFrame->gmmLT_I_K_V.begin(); iter!= pMainFrame->gmmLT_I_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LT_I_K_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLT_I_K_K::const_iterator iter = pMainFrame->gmmLT_I_K_K.begin(); iter!= pMainFrame->gmmLT_I_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}		
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LT_I_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLT_I_A_K::const_iterator iter = pMainFrame->gmmLT_I_A_K.begin(); iter!= pMainFrame->gmmLT_I_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LT_K_K_V(int am)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLT_K_K_V::const_iterator iter = pMainFrame->gmmLT_K_K_V.begin(); iter!= pMainFrame->gmmLT_K_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LT_K_K_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLT_K_K_K::const_iterator iter = pMainFrame->gmmLT_K_K_K.begin(); iter!= pMainFrame->gmmLT_K_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}			
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LT_K_A_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLT_K_A_V::const_iterator iter = pMainFrame->gmmLT_K_A_V.begin(); iter!= pMainFrame->gmmLT_K_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_LT_K_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmLT_K_A_K::const_iterator iter = pMainFrame->gmmLT_K_A_K.begin(); iter!= pMainFrame->gmmLT_K_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}
return _T("NOT_FOUND");

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// AS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



tstring CAipi_RETE_AM::findAM_AS_I_A_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmAS_I_A_V::const_iterator iter = pMainFrame->gmmAS_I_A_V.begin(); iter!= pMainFrame->gmmAS_I_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");

}

tstring CAipi_RETE_AM::findAM_AS_I_K_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmAS_I_K_V::const_iterator iter = pMainFrame->gmmAS_I_K_V.begin(); iter!= pMainFrame->gmmAS_I_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}
		
	}

return _T("NOT_FOUND");

}


tstring CAipi_RETE_AM::findAM_AS_I_K_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmAS_I_K_K::const_iterator iter = pMainFrame->gmmAS_I_K_K.begin(); iter!= pMainFrame->gmmAS_I_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}		
	}

return _T("NOT_FOUND");

}


tstring CAipi_RETE_AM::findAM_AS_I_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmAS_I_A_K::const_iterator iter = pMainFrame->gmmAS_I_A_K.begin(); iter!= pMainFrame->gmmAS_I_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}



tstring CAipi_RETE_AM::findAM_AS_K_K_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmAS_K_K_V::const_iterator iter = pMainFrame->gmmAS_K_K_V.begin(); iter!= pMainFrame->gmmAS_K_K_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_AS_K_K_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmAS_K_K_K::const_iterator iter = pMainFrame->gmmAS_K_K_K.begin(); iter!= pMainFrame->gmmAS_K_K_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}



tstring CAipi_RETE_AM::findAM_AS_K_A_V(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmAS_K_A_V::const_iterator iter = pMainFrame->gmmAS_K_A_V.begin(); iter!= pMainFrame->gmmAS_K_A_V.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}


tstring CAipi_RETE_AM::findAM_AS_K_A_K(int am)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmAS_K_A_K::const_iterator iter = pMainFrame->gmmAS_K_A_K.begin(); iter!= pMainFrame->gmmAS_K_A_K.end(); ++iter)
	{
		if( iter->second == am )
		{
			return iter->first;
		}	
	}

return _T("NOT_FOUND");
}


