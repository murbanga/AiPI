// Aipi_RETE_BME.cpp: implementation of the CAipi_RETE_BME class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_BME.h"

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

CAipi_RETE_BME::CAipi_RETE_BME()
{

}

CAipi_RETE_BME::~CAipi_RETE_BME()
{

}


CAipi_RETE_BME* CAipi_RETE_BME::addBME(int bm, int nTk, int sizeTk )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_BME *pObject = new CAipi_RETE_BME();
    try
	{
		pObject->setNTokens(nTk);
		pObject->setSizeToken(sizeTk);
						
		pMainFrame->gmBM_Info.insert(CMainFrame::g_mBM_Info::value_type(bm, *pObject));
						
						
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

void CAipi_RETE_BME::clearBME()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmBM_Info.clear();
	pMainFrame->gmmBM_WM.clear();

}


void CAipi_RETE_BME::eraseBM_WM(int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmBM_WM::iterator iterBM;
	
	iterBM = pMainFrame->gmmBM_WM.find(bm);
	
	if( iterBM != pMainFrame->gmmBM_WM.end())
	{
		pMainFrame->gmmBM_WM.erase(bm);
	}
	
}

void CAipi_RETE_BME::eraseBM_Info(int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mBM_Info::iterator iterBM;
	
	iterBM = pMainFrame->gmBM_Info.find(bm);
	
	if( iterBM != pMainFrame->gmBM_Info.end())
	{
		pMainFrame->gmBM_Info.erase(bm);
	}
	
}


void CAipi_RETE_BME::eraseBME(int bm)
{
	eraseBM_WM(bm);
	eraseBM_Info(bm);
}



int CAipi_RETE_BME::findBME_nTokens( int bm )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mBM_Info::iterator iter;
    iter = pMainFrame->gmBM_Info.find(bm);
	if( iter != pMainFrame->gmBM_Info.end())
	{
  		CAipi_RETE_BME  n = (CAipi_RETE_BME)iter->second;
 		return n.getNTokens();
	}
	
	return NOT_FOUND;
	
}


int CAipi_RETE_BME::findBME_sizeToken( int bm )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mBM_Info::iterator iter;
    iter = pMainFrame->gmBM_Info.find(bm);
	if( iter != pMainFrame->gmBM_Info.end())
	{
  		CAipi_RETE_BME  n = (CAipi_RETE_BME)iter->second;
 		return n.getSizeToken();
	}
	
	return NOT_FOUND;
	
}


int CAipi_RETE_BME::findBMEMembers(int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mBM_Info::iterator iter;
    iter = pMainFrame->gmBM_Info.find(bm);
	if( iter != pMainFrame->gmBM_Info.end())
	{
  		CAipi_RETE_BME bme = (CAipi_RETE_BME)iter->second;
 		
		m_nTokens	= bme.getNTokens();
		m_sizeToken = bme.getSizeToken();
			
		return bm;
	}
	
	return NOT_FOUND;
}

/*
void CAipi_RETE_BME::createBME()
{
	CAipi_RETE_BM bmo;
	int tempBM = 0;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	for( CMainFrame::g_mmBM::const_iterator iter = pMainFrame->gmmBM.begin(); iter!= pMainFrame->gmmBM.end(); ++iter)
	{
		CAipi_RETE_BM bmo = (CAipi_RETE_BM) iter->second;
		int tk = bmo.getChildTK();
		int bm = iter->first;
		
		
		int sizeTk = linkWMEs(bm, tk);
		
		if( bm > tempBM )
		{
			int nTk = bmo.countBM(bm);
			addBME(bm, nTk, sizeTk);
			tempBM = bm;
			
			CString str;
			str.Format(_T("bm...%d  " ), bm);
			AfxMessageBox(str);
			str.Format(_T("tk...%d  " ), tk);
			AfxMessageBox(str);
			str.Format(_T("size tk...%d  " ), sizeTk);
			AfxMessageBox(str);	
			str.Format(_T("n tk...%d  " ), nTk);
			AfxMessageBox(str);	
			
		}	
		
		
		
				
	}

}
*/


int CAipi_RETE_BME::linkWMEs(int bm, int tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	//pMainFrame->gmmBM_WM.clear();
	
	CAipi_RETE_TK tko;
	//Working memory element
	int wmTk = NOT_FOUND;
	//This is number of working memory elements linked in a BM token
	int sizeTk = 1;
	wmTk = tko.findWM(tk);
	if( wmTk != NOT_FOUND )
	{
		pMainFrame->gmmBM_WM.insert(CMainFrame::g_mmBM_WM::value_type(bm, wmTk));
	}
	
	int iWME = NOT_FOUND;	
	
	if(pMainFrame->gmTK.size() > 0 )
	{
		CMainFrame::g_mTK::iterator iter;
		iter = pMainFrame->gmTK.find(tk);
		if( iter != pMainFrame->gmTK.end())
		{
			do
			{
				tk = tko.findParentTk(tk);
				iWME = tko.findWM(tk);
				if( iWME != NOT_FOUND) 
				{
					++sizeTk;
					wmTk = iWME;
					pMainFrame->gmmBM_WM.insert(CMainFrame::g_mmBM_WM::value_type(bm, wmTk));
				}
				
				
			}while( iWME != NOT_FOUND );
	
		}
		else
		{
			return NOT_FOUND;
		}
	}
	
	return sizeTk;

	
	

	
}


int CAipi_RETE_BME::countBMTKs(int bm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mmBM_WM::iterator iter;
    return  pMainFrame->gmmBM_WM.count(bm);

}



void CAipi_RETE_BME::printBME()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Beta Memory  - Information Elements *******"));
	//Print map container
	for( CMainFrame::g_mBM_Info::const_iterator iter = pMainFrame->gmBM_Info.begin(); iter!= pMainFrame->gmBM_Info.end(); ++iter)
	{
		CString strBM = _T("B");
		CString strNTK = _T("nTK_");
		CString strSTK =_T("SizeTK_");
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Beta Memory - Info  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  BME: "));
		strBM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		

		CAipi_RETE_BME bmo = (CAipi_RETE_BME)iter->second;
 		
		
		int nTk = bmo.getNTokens();
		int sizeTk = bmo.getSizeToken();
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  nTokens: "));
		strNTK +=  _itot( nTk, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strNTK);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("***)  Size Token: "));
		strSTK +=  _itot( sizeTk, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strSTK);
		

			
	}


}


void CAipi_RETE_BME::printBM_WM()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Beta Memory - Working Memory elements (TK) *******"));
	//Print map container
	for( CMainFrame::g_mmBM_WM::const_iterator iter = pMainFrame->gmmBM_WM.begin(); iter!= pMainFrame->gmmBM_WM.end(); ++iter)
	{
		CString strBM =_T("B");
		CString strWM =_T("W");
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  BM _ WM  *******"));
		strBM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strBM);
		strWM +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strWM);
			
	}
}