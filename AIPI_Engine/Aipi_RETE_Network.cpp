// Aipi_RETE_Network.cpp: implementation of the CAipi_RETE_Network class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_Network.h"

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

CAipi_RETE_Network::CAipi_RETE_Network()
{

}

CAipi_RETE_Network::~CAipi_RETE_Network()
{

}


void CAipi_RETE_Network::StopTimer(CPerfTimer t, CString msg)
{

	CString str;
	str.Format(msg + _T("%0.4f"),t.Elapsed());
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndOutputTabView.IsVisible())
	{
		pMainFrame->m_wndOutputTabView.m_TabViewContainer.SetActivePageIndex(0);
		pMainFrame->m_wndOutputTabView.AddMsg1(str);
		
	}
	t.Stop();

}





int CAipi_RETE_Network::findDN(int c)
{
	m_mDN::iterator iter;
	iter = mDN.find( c );
	
	if( iter != mDN.end())
	{
		return c;
	}
return NOT_FOUND;

}




void CAipi_RETE_Network::printDN()
{
	TCHAR buffer[16];
	m_mDN::iterator pos;

	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Current Dummy Node  *******"));
 
	for (pos = mDN.begin(); pos != mDN.end(); ++pos) 
	{
        CString strPos = _T("DN");   
		strPos +=  _itot( *pos, buffer, 10 ); 
		pMainFrame->m_wndOutputTabView.AddMsg1(strPos);
		//AfxMessageBox(strPos);
    }



}


int CAipi_RETE_Network::createDummyNode(int c1, int pm)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_WM::iterator it_AM;
	pair <CMainFrame::g_mmAM_WM::iterator, CMainFrame::g_mmAM_WM::iterator>  pAM;
		
	CAipi_RETE_TK		tk;
	CAipi_RETE_BM		bme;
	CAipi_RETE_JNode	jn;
	CAipi_RETE_AM		am;
	CAipi_LHS			lhs;
	CAipi_RETE_NNode	nn;	

	
	int a = am.findCond_AM(c1);
	
		
	int not = nn.findCond_NN(c1);
	
	if( not != NOT_FOUND )
	{
		int BME = bme.generateBMKey();
		if( !pMainFrame->gmmAM_WM.empty())
		{
			
			pAM = pMainFrame->gmmAM_WM.equal_range(a);

			for(it_AM = pAM.first; it_AM != pAM.second; ++it_AM)
			{	
			
				int Tk = tk.generateTKKey();
				tk.createTK(Tk, DNode, it_AM->second, BME, NEGATIVE);
				nn.addNN_TK(BME, Tk);
				tk.addWM_ChildTK(it_AM->second, Tk);
				nn.addWM_NN(it_AM->second, BME);
				nn.editCond_NN(c1, BME);
				

				
				
			}
			
			//bme.addBM_TK(BME, EMPTY);
			
			/*
			CString str;
			str.Format(_T("BME DM...%d  " ), BME);
			AfxMessageBox(str);
			*/
			
		}
		
	}
	else
	{
		/*
		CString str;
		str.Format(_T("Dummy Node...%d  " ), c1);
		AfxMessageBox(str);
		*/
		//printCurrentAM();
		//str.Format(_T("AM...%d  " ), a);
		//AfxMessageBox(str);
		m_mDN::iterator iter;

		if (!mDN.empty())
		{
			for (iter = mDN.begin(); iter != mDN.end(); ++iter) 
			{
				bool dn = lhs.compareEqualCond(*iter, c1);
				if( dn != false )
				{
					return REPEATED;
				}
			}
		}
	
		mDN.insert(m_mDN::value_type(c1));
		//tk.clearToken();
		int BME = bme.generateBMKey();
		int JNE = jn.generateJNKey();
		jn.addJN(JNE, UNDEFINE, UNDEFINE, c1, AIPI_VL, pm, _T("")); 
		//jn.addCond1_JN(UNDEFINE, JNE);

		
		if( !pMainFrame->gmmAM_WM.empty())
		{
			pAM = pMainFrame->gmmAM_WM.equal_range(a);

			for(it_AM = pAM.first; it_AM != pAM.second; ++it_AM)
			{	
			
				int Tk = tk.generateTKKey();
				tk.createTK(Tk, DNode, it_AM->second, BME, POSITIVE);
				//bme.addBM_TK(BME, Tk);
				tk.addWM_ChildTK(it_AM->second, Tk);
				//tk.addTkChildParent(DN, Tk);

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









int CAipi_RETE_Network::locateBM(CAipi_RETE_AM am, CAipi_RETE_JNode jn, int c1)
{
	CAipi_RETE_Cond co;
	CAipi_RETE_Node n;
	int a1 = am.findCond_AM(c1);
	int rc1 = findEqualCond2(a1, c1);
	int j1 = co.findCond2JN(rc1);
	int b = n.findNodeBM2(j1);

	return b;

}


int CAipi_RETE_Network::createJoinNode(int c1, int f1, int c2, int f2 )
{
	
	
	
	TCHAR buffer[4];
	CString str;
	AfxMessageBox(_T("CreateJN Conditions : "));
	str =  _itot( c1, buffer, 10 );
	AfxMessageBox(str);
	str =  _itot( c2, buffer, 10 );
	AfxMessageBox(str);
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	
	CAipi_RETE_AM		amo;
	CAipi_RETE_BM		bmo;
	CAipi_RETE_JNode	jno;
	//CAipi_RETE_TK		tko;
	//CAipi_WM			wko;
	CAipi_RETE_NNode	nno;
	CAipi_RETE_NCCNode	ncco;	
	
	m_NewTK = UNDEFINE;
	tstring Field1, Field2;
	int a, b = NOT_FOUND;
	int BME = bmo.generateBMKey();
	
	
	AfxMessageBox(_T("BME :"));
	str =  _itot( BME, buffer, 10 );
	AfxMessageBox(str);
		
	
	
	
	int neg = nno.findCond_NN(c1);
	if( neg != NOT_FOUND)
	{
		
		
		do
		{			
			
			c1--;
			neg = nno.findCond_NN(c1);
			f1 = bindNegatedCond(c1, c2, 1);
			 
		}while( neg != NOT_FOUND);

		
		b = locateBM(amo, jno, c1);
		
		/*
		AfxMessageBox(_T("Negated Conditions : "));
		str =  _itot( c1, buffer, 10 );
		AfxMessageBox(str);
		str =  _itot( c2, buffer, 10 );
		AfxMessageBox(str);
		AfxMessageBox(_T("Beta Memory :"));
		str =  _itot( b, buffer, 10 );
		AfxMessageBox(str);
		*/
		
		

		/*
		AfxMessageBox(_T("f1 Negated Field C1 : "));
		str =  _itot( f1, buffer, 10 );
		AfxMessageBox(str);

		AfxMessageBox(_T("f2 Negated Field C2 : "));
		str =  _itot( f2, buffer, 10 );
		AfxMessageBox(str);
		*/
	
	}


	
	
	else if( m_CurrentDN == NNode )
	{
		b = locateBM(amo, jno, c1);
		/*		
			AfxMessageBox(_T("Beta Memory :"));
			str =  _itot( b, buffer, 10 );
			AfxMessageBox(str);
		*/
		
		m_CurrentDN = c1;
	}

	
	else if( m_CurrentDN == REPEATED  )
	{
		/*
		AfxMessageBox(_T("REPEATED :"));
		str.Format(_T("DM...%d  " ), m_CurrentDN);
		AfxMessageBox(str);
		str.Format(_T("PM...%d  " ), m_CurrentPM);
		AfxMessageBox(str);
		*/
		
		if( m_CurrentNCC == -1 )
		{
			b = locateBM(amo, jno, c1);
			
			/*
			AfxMessageBox(_T("Repeated C1 :"));
			str =  _itot( rc1, buffer, 10 );
			AfxMessageBox(str);
			
			AfxMessageBox(_T("Repeated JoinNode :"));
			str =  _itot( j1, buffer, 10 );
			AfxMessageBox(str);
						
			AfxMessageBox(_T("Repeated Beta Memory :"));
			str =  _itot( b, buffer, 10 );
			AfxMessageBox(str);
			*/

		}
		else
		{
			b = bmo.lastBM();			/*
			AfxMessageBox(_T("Beta Memory :"));
			str =  _itot( b, buffer, 10 );
			AfxMessageBox(str);
			*/
		}
		
	   	
		
	}
	else
	{
		
		b = bmo.lastBM();
		
				
		AfxMessageBox(_T("Fuera Beta Memory :"));
		str =  _itot( b, buffer, 10 );
		AfxMessageBox(str);
		
	

		/*		
		TCHAR buffer[4];
		CString str;
		AfxMessageBox(_T("JoinNode"));
		str =  _itot( j1, buffer, 10 );
		AfxMessageBox(str);
		str =  _itot( m_CurrentPM, buffer, 10 );
		AfxMessageBox(_T("Production"));
		AfxMessageBox(str);


		CString strCond;
		strCond =  _itot( c1, buffer, 10 );
		AfxMessageBox(strCond);
		strCond =  _itot( c2, buffer, 10 );
		AfxMessageBox(strCond);
		*/
	}
	
	a =  amo.findCond_AM(c2);
	
	
	AfxMessageBox(_T("Alpha Memory :"));
	str =  _itot( a, buffer, 10 );
	AfxMessageBox(str);
	

	/*
	AfxMessageBox(_T("m_CurrentDN : "));
	str =  _itot( m_CurrentDN, buffer, 10 );
	AfxMessageBox(str);
	*/

	neg = nno.findCond_NN(c2);
	
	
	///r =0		-> The fields didn't match
	///r = -1	-> The conditions are negative
	///r= 1		-> The condition are positive

	//int r = bindBM_AM(f1, f2, neg, a, b, BME, bmo, nno);
	int r =0;
	
	

	CAipi_PM	pmo;
	CAipi_RETE_PNode	pno;
	int newJoin = jno.generateJNKey();
	int finalCond = pmo.PM_CondUpperBound(m_CurrentPM);
	int token = bmo.findBMParentTK(BME, 2);
	
	
	
	switch(r)
	{
	case -1:
		/*
		AfxMessageBox(_T("BME Beta Memory :"));
		str =  _itot( BME, buffer, 10 );
		AfxMessageBox(str);
		*/
		nno.addNN(BME, c1, f1, c2, f2, b, newJoin, NNode);
		nno.editCond_NN(c2, BME);

		//bmo.addBM_TK(BME, NNode);
		bmo.addBM_ChildJN(b, newJoin);
		jno.addJN(newJoin, c1, f1, c2, f2, m_CurrentPM, _T(""));
		//jno.editCond1_JN(c1, newJoin);
		//jno.editCond2_JN(c2, newJoin);

		if( finalCond == c2 )
		{
			if( m_Negated == true )
			{
				//pno.addPNode(m_CurrentPM, newJoin, c1, c2, b, BME, NNode );

			}
			else
			{
				//pno.addPNode(m_CurrentPM, newJoin, c1, c2, b, BME, PNode );
			}
		
			return r;

		}
		break;
	
	case 0:
		//bmo.addBM_TK(BME, EMPTY);
		bmo.addBM_ChildJN(b, newJoin);
		//jno.addJN(newJoin, c1, f1, c2, f2, b, BME, JNode);
		m_NewTK = EMPTY;

		/*
			AfxMessageBox(_T("NEW JOIN"));
			TCHAR buffer[4];
			CString strCond;
			strCond =  _itot( newJoin, buffer, 10 );
			AfxMessageBox(strCond);
			strCond =  _itot( c1, buffer, 10 );
			AfxMessageBox(strCond);
			strCond =  _itot( c2, buffer, 10 );
			AfxMessageBox(strCond);
			AfxMessageBox(_T("b Beta Memory :"));
			str =  _itot( b, buffer, 10 );
			AfxMessageBox(str);
		
			AfxMessageBox(_T("BME Beta Memory :"));
			str =  _itot( BME, buffer, 10 );
			AfxMessageBox(str);
		*/
		
		//jno.editCond1_JN(c1, newJoin);
		//jno.editCond2_JN(c2, newJoin);
			
		if( finalCond == c2 )
		{
			jno.addJN(newJoin , c1, f1, c2, f2, m_CurrentPM, _T(""));
			//pno.addPNode(m_CurrentPM, newJoin, c1, c2, b, BME, PNode );
		}
		else
		{
			jno.addJN(newJoin, c1, f1, c2, f2, m_CurrentPM, _T(""));
		}	
		
		
		if(token == EMPTY )
		{
			//Works NCC 
			processNCC(c1, c2, b, BME, newJoin, m_NewTK, finalCond, ncco, pno, bmo);
			return r;
		}
		
		break;
	
	case 1:
		bmo.addBM_ChildJN(b, newJoin);
		/*
		TCHAR buffer[4];
		CString strCond;
		strCond =  _itot( m_nFiredCond, buffer, 10 );
		AfxMessageBox(strCond);
		*/
		
		if( finalCond == c2 )
		{
			/*
			TCHAR buffer[4];
			CString str;
			AfxMessageBox(_T("BME Beta Memory Token:"));
			str =  _itot( BMtoken, buffer, 10 );
			AfxMessageBox(str);
			*/
			//jno.editCond1_JN(c1, newJoin);
			//jno.editCond2_JN(c2, newJoin);
				
			if( token != EMPTY)
			{
				//AfxMessageBox(_T("Estoy en fired"));
			
				jno.addJN(newJoin , c1, f1, c2, f2, m_CurrentPM, _T(""));
				int Negcc = ncco.findEndCond_NCC(c2);
				if( Negcc == NOT_FOUND )
				{
					//AfxMessageBox(_T("FIRED!!!!!!"));
					//pno.addPNode(m_CurrentPM, newJoin, c1, c2, b, BME, FPNode );
					pMainFrame->g_vFiredPM.push_back(m_CurrentPM);
				}
			}
		}
		else
		{
			jno.addJN(newJoin, c1, f1, c2, f2, m_CurrentPM, _T(""));
			
		}
		
		break;
	
	default:
		//jno.addJN(newJoin, c1, f1, c2, f2, b, BME, JN);
		//jno.editCond1_JN(c1, newJoin);
		//jno.editCond2_JN(c2, newJoin);
	
		/*
		AfxMessageBox(_T("NEW JOIN"));
		TCHAR buffer[4];
		CString strCond;
		strCond =  _itot( newJoin, buffer, 10 );
		AfxMessageBox(strCond);
		strCond =  _itot( c1, buffer, 10 );
		AfxMessageBox(strCond);
		strCond =  _itot( c2, buffer, 10 );
		AfxMessageBox(strCond);
		*/
		break;
	
	}

/*
	TCHAR buffer[4];
	CString str;
	AfxMessageBox(_T("CreateJN Conditions : "));
	str =  _itot( c1, buffer, 10 );
	AfxMessageBox(str);
	str =  _itot( c2, buffer, 10 );
	AfxMessageBox(str);
*/	

	processNCC(c1, c2, b, BME, newJoin, m_NewTK, finalCond, ncco, pno, bmo);
	

return r;

}


/*
int CAipi_RETE_Network::assertUpdate(int b1, int b2, int w1, int w2, int f1, int f2, int j )
{
	//AfxMessageBox(_T("Entro ASSERT UPDATE"));	
	TCHAR buffer[4];
	CString str;
	AfxMessageBox(_T("Conditions : "));
	str =  _itot( c1, buffer, 10 );
	AfxMessageBox(str);
	str =  _itot( c2, buffer, 10 );
	AfxMessageBox(str);

	str;
	str.Format(_T("AM...%d  " ), a);
	AfxMessageBox(str);

	str.Format(_T("BM1...%d  " ), b);
	AfxMessageBox(str);
	

	
	CString str;
	str.Format(_T("W1...%d  " ), w1);
	AfxMessageBox(str);

	str.Format(_T("W2...%d  " ), w2);
	AfxMessageBox(str);
    
		
	CAipi_WM		wk;
	CAipi_RETE_NNode	nn;
				
	tstring Field1, Field2;
	int r =0;
	
	
	if(f1 == AIPI_ID)
	{
		Field1 = wk.findWMId(w1); 
	}
	else if(f1 == AIPI_AT)
	{
		Field1 = wk.findWMAttr(w1);	
	}
	else if(f1 == AIPI_VL)
	{
		Field1 = wk.findWMVal(w1);	
	}
			
			
	if(f2 == AIPI_ID)
	{
		Field2 = wk.findWMId(w2); 
	}
	else if(f2 == AIPI_AT)
	{
		Field2 = wk.findWMAttr(w2);	
	}
	else if(f2 == AIPI_VL)
	{
		Field2 = wk.findWMVal(w2);	
	}
			
			AfxMessageBox(_T("Fields: "));
			AfxMessageBox(Field1.data());
			AfxMessageBox(Field2.data());
			

	if( Field1 == Field2)
	{
		
			

		CAipi_RETE_TK  tk;
		CAipi_RETE_BM bm;
		CAipi_RETE_JNode jn;
		
		
		
		int	oldTK = bm.searchWMTK(b1, w1);
		
		
		CString str;
		AfxMessageBox(_T("OLD Token"));
		str.Format(_T(" Token...%d  " ), oldTK);
		AfxMessageBox(str);
		
		
		if( oldTK != NOT_FOUND ) 
		{
					
			int newTK = tk.generateTKKey();
			int c2 = jn.findJNCond2(j);
			int not = nn.findCond_NN(c2);
			if( not != NOT_FOUND)
			{
				
				//nn.createTokenNN(newTK, oldTK, w2, NEGATIVE);
				tk.createTK(newTK, oldTK, w2, b2, NEGATIVE);
				nn.addNN_TK(b2, newTK);
				nn.addWM_NN(w2, b2);
				
			
				
				CString str;
				AfxMessageBox(_T("NEGATIVE Token"));
				str.Format(_T(" NOT Token...%d  " ), newTK);
				AfxMessageBox(str);
				
				
			
				
				r =-1;
			}
			else
			{
				tk.createTK(newTK, oldTK, w2, b2, POSITIVE);
				r = 1;

				
				CString str;
				AfxMessageBox(_T("POSITIVE Token"));
				str.Format(_T(" Token...%d  " ), newTK);
				AfxMessageBox(str);
				
				
			}
			
			tk.addWM_ChildTK(w2, newTK);
			//tk.addTkChildParent(oldTK, newTK);
			//jn.addBM_ChildJN(b1, j);
						
			
			int t = bm.findBMParentTK(b2);
			
			
			CString str;
			AfxMessageBox(_T("Assert Update"));
			str.Format(_T("BM...%d  " ), b2);
			AfxMessageBox(str);
			str.Format(_T("TK...%d  " ), t);
			AfxMessageBox(str);
			
			int bNot = b2 - 1;
			if( b1 != bNot )
			{
			//AfxMessageBox(_T("Entro2"));
				int not = nn.findNN_TK(bNot);
				if ( not != NOT_FOUND )
				{
					//AfxMessageBox(_T("Entro3"));
					return -1;
				}
			}



			switch(t)
			{
				case NNode:
					//Do nothing	
				break;
				case EMPTY:
					bm.editBM_TK(b2, newTK);
				break;
				default:
					bm.addBM_TK(b2, newTK);
				break;

			}	

			

		}
		
	}

	
return r;
}

*/


/*
int CAipi_RETE_Network::removeUpdate( int b1, int b2, int w1, int w2, int f1, int f2 )
{
	
	
	TCHAR buffer[4];
	CString str;
	AfxMessageBox(_T("Conditions : "));
	str =  _itot( c1, buffer, 10 );
	AfxMessageBox(str);
	str =  _itot( c2, buffer, 10 );
	AfxMessageBox(str);

	str;
	str.Format(_T("AM...%d  " ), a);
	AfxMessageBox(str);

	str.Format(_T("BM1...%d  " ), b);
	AfxMessageBox(str);
	
		
	
	CAipi_WM		wk;
				
	tstring Field1, Field2;
	int r =0;
	
	
	if(f1 == AIPI_ID)
	{
		Field1 = wk.getWMEId(w1); 
	}
	else if(f1 == AIPI_AT)
	{
		Field1 = wk.getWMEAttr(w1);	
	}
	else if(f1 == AIPI_VL)
	{
		Field1 = wk.getWMEVal(w1);	
	}
			
			
	if(f2 == AIPI_ID)
	{
		Field2 = wk.getWMEId(w2); 
	}
	else if(f2 == AIPI_AT)
	{
		Field2 = wk.getWMEAttr(w2);	
	}
	else if(f2 == AIPI_VL)
	{
		Field2 = wk.getWMEVal(w2);	
	}
			

	if( Field1 == Field2)
	{
		//AfxMessageBox(_T("Match"));
		CAipi_RETE_TK  tk;
		CAipi_RETE_BM bm;

		int oldTK = bm.findWMToken(b2, w2);
		if( oldTK != NOT_FOUND ) 
		{
			r = 1;
			tk.eraseToken(oldTK);
			
		}										
	}

	
return r;
}
*/



int CAipi_RETE_Network::bindBM_AM(int f1, int f2, int neg, int a, int b, int BME, CAipi_RETE_BM bm, CAipi_RETE_NNode nn)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmAM_WM::iterator iterAM;
	CMainFrame::g_mmBM::iterator iterBM;
	pair <CMainFrame::g_mmAM_WM::iterator, CMainFrame::g_mmAM_WM::iterator>  pAM;
	pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
	
	int WME1, WME2 = NOT_FOUND;
	int r = UNDEFINE;
	tstring Field1, Field2;
	CAipi_RETE_TK	tk;
	CAipi_WM		wk;

		
	//Para que no se desborde la adición de BM  
	int nTokens = bm.countBM(b);
	int cont = 0;

	pBM = pMainFrame->gmmBM.equal_range(b);
	
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		
		//tk.findTKMembers(iterBM->second);
		WME1 = tk.m_WM;
		cont++;
	
		/*
		AfxMessageBox(_T("BM :"));
		str =  _itot( iterBM->first, buffer, 10 );
		AfxMessageBox(str);
		AfxMessageBox(_T("WME1 :"));
		str =  _itot( WME1, buffer, 10 );
		AfxMessageBox(str);
		*/
		

		if(f1 == AIPI_ID)
		{
			Field1 = wk.findWMId(WME1);
		}
		else if(f1 == AIPI_AT)
		{
			Field1 = wk.findWMAttr(WME1);	
		}
		else if(f1 == AIPI_VL)
		{
			Field1 = wk.findWMVal(WME1);	
		}
														
			pAM = pMainFrame->gmmAM_WM.equal_range(a);

			for(iterAM = pAM.first; iterAM != pAM.second; ++iterAM)
			{	
				WME2 = iterAM->second;
			
				if(f2 == AIPI_ID)
				{
					Field2 = wk.findWMId(WME2); 
				}
				else if(f2 == AIPI_AT)
				{
					Field2 = wk.findWMAttr(WME2);	
				}
				else if(f2 == AIPI_VL)
				{
					Field2 = wk.findWMVal(WME2);	
				}
			
				/*			
				AfxMessageBox(_T("Fields: "));
				AfxMessageBox(Field1.data());
				AfxMessageBox(Field2.data());
				*/

				if( Field1 == Field2 )
				{
					if(Field1 == _T("") &&  Field2 == _T("") )
					{
						f1 = UNDEFINE;
						f2 = UNDEFINE;
						continue;
					}
					
				/*	
					AfxMessageBox(_T("************* Fields *********** "));
					AfxMessageBox(_T("Field1 AIPI_ID AIPI_AT AIPI_VL"));
					str =  _itot( f1, buffer, 10 );
					switch(f1)
					{
					case 1:	
						AfxMessageBox(_T("AIPI_ID"));
						break;
					case 2:
						AfxMessageBox(_T("AIPI_AT"));
						break;
					case 3:
						AfxMessageBox(_T("AIPI_VL"));
						break;
					}
					AfxMessageBox(_T("Field1: "));
					AfxMessageBox(Field1.data());
					
					AfxMessageBox(_T("WME1 :"));
					str =  _itot( WME1, buffer, 10 );
					AfxMessageBox(str);
		
					
					AfxMessageBox(_T("Field2 AIPI_ID AIPI_AT AIPI_VL"));
					str =  _itot( f2, buffer, 10 );
					switch(f2)
					{
					case 1:	
						AfxMessageBox(_T("AIPI_ID"));
						break;
					case 2:
						AfxMessageBox(_T("AIPI_AT"));
						break;
					case 3:
						AfxMessageBox(_T("AIPI_VL"));
						break;
					}
					
					AfxMessageBox(_T("Field2: "));
					AfxMessageBox(Field2.data());
					
					AfxMessageBox(_T("WME2 :"));
					str =  _itot( WME2, buffer, 10 );
					AfxMessageBox(str);
					*/
					
					
					
						int oldTK = bm.searchWMTK(b, WME1, UNDEFINE);
						if( oldTK != NOT_FOUND ) 
						{
																
							m_NewTK = tk.generateTKKey();
							
							//Negated Conditions
							if ( neg != NOT_FOUND )
							{
								m_Negated = true;
								r = -1;
								
								tk.createTK(m_NewTK, oldTK, WME2, BME, NEGATIVE);
								//nn.createTokenNN(newTK, oldTK, WME2, NEGATIVE);
								nn.addNN_TK(BME, m_NewTK);
								//bm.addBME(BME, UNDEFINE);
								tk.addWM_ChildTK(WME2, m_NewTK);
								nn.addWM_NN( WME2, BME);
								tk.addTKParent_TKChild(oldTK, m_NewTK);
								//AfxMessageBox(_T("Match Negative"));
								
							}
							//Positive Conditions
							else 
							{
								if( m_Negated == false )
								{
									r = 1;
																		
									tk.createTK(m_NewTK, oldTK, WME2, BME, POSITIVE);
									//bm.addBM_TK(BME, m_NewTK);
									tk.addWM_ChildTK(WME2, m_NewTK);
									tk.addTKParent_TKChild(oldTK, m_NewTK);
									//AfxMessageBox(_T("Match Positive"));
								}
							}
							
						}

					
					
				}
				//No Matching conditions
				else if( Field1 != Field2 && neg != NOT_FOUND )
				{
					r = -1;
					
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

		if( cont >= nTokens )
		{
			break;
		}
					

	}
					
		
	///r =0		-> The fields didn't match
	///r = -1	-> The conditions are negative
	///r= 1		-> The condition are positive

return r;

}



int CAipi_RETE_Network::bindCond(int c1, int c2)
{
	
	CAipi_LHS	lhs;
	int type = -1;
	int r = 0;

	tstring varId1			= _T("VI1");
	tstring varId2			= _T("VI2");
	tstring varAttr1		= _T("VA1");
	tstring varAttr2		= _T("VA2");
	tstring varVal1			= _T("VV1");
	tstring varVal2			= _T("VV2");


	tstring constId1		= _T("KI1");
	tstring constId2		= _T("KI2");
	tstring constAttr1		= _T("KA1");
	tstring constAttr2		= _T("KA2");
	tstring constVal1		= _T("KV1");
	tstring constVal2		= _T("KV2");

	type = lhs.variableTest(c1);
	lhs.findLHSMembers(c1);
	
	switch(type)
	{
		case ID_K_K:
			varId1		= lhs.m_Id;
			constAttr1	= lhs.m_Attr;
			constVal1	= lhs.m_Val;
			break;
		case K_AT_K:
			constId1	= lhs.m_Id;
			varAttr1	= lhs.m_Attr;
			constVal1	= lhs.m_Val;
			break;
		case K_K_VL:
			constId1	= lhs.m_Id;
			constAttr1	= lhs.m_Attr;
			varVal1		= lhs.m_Val;
			break;
		case ID_AT_K:
			varId1		= lhs.m_Id;
			varAttr1	= lhs.m_Attr;
			constVal1	= lhs.m_Val;
			break;
		case ID_K_VL:
			varId1		= lhs.m_Id;
			constAttr1	= lhs.m_Attr;
			varVal1		= lhs.m_Val;
			break;
		case K_AT_VL:
			constId1	= lhs.m_Id;
			varAttr1	= lhs.m_Attr;
			varVal1		= lhs.m_Val;
			break;
		case ID_AT_VL:
			varId1		= lhs.m_Id;
			varAttr1	= lhs.m_Attr;
			varVal1		= lhs.m_Val;
			break;
		default:
			constId1	= lhs.m_Id;
			constAttr1	= lhs.m_Attr;
			constVal1	= lhs.m_Val;
			break;
	}
	
	//AfxMessageBox(varId1.data());
	//AfxMessageBox(varAttr1.data());
	//AfxMessageBox(varVal1.data());


	type = lhs.variableTest(c2);
	lhs.findLHSMembers(c2);
	
	switch(type)
	{
		case ID_K_K:
			varId2		= lhs.m_Id;
			constAttr2	= lhs.m_Attr;
			constVal2	= lhs.m_Val;
			break;
		case K_AT_K:
			constId2	= lhs.m_Id;
			varAttr2	= lhs.m_Attr;
			constVal2	= lhs.m_Val;
			break;
		case K_K_VL:
			constId2	= lhs.m_Id;
			constAttr2	= lhs.m_Attr;
			varVal2		= lhs.m_Val;
			break;
		case ID_AT_K:
			varId2		= lhs.m_Id;
			varAttr2	= lhs.m_Attr;
			constVal2	= lhs.m_Val;
			break;
		case ID_K_VL:
			varId2		= lhs.m_Id;
			constAttr2	= lhs.m_Attr;
			varVal2		= lhs.m_Val;
			break;
		case K_AT_VL:
			constId2	= lhs.m_Id;
			varAttr2	= lhs.m_Attr;
			varVal2		= lhs.m_Val;
			break;
		case ID_AT_VL:
			varId2		= lhs.m_Id;
			varAttr2	= lhs.m_Attr;
			varVal2		= lhs.m_Val;
			break;
		default:
			constId2	= lhs.m_Id;
			constAttr2	= lhs.m_Attr;
			constVal2	= lhs.m_Val;
			break;
	}

	
	//AfxMessageBox(varId2.data());
	//AfxMessageBox(varAttr2.data());
	//AfxMessageBox(varVal2.data());

	int f1, f2 = 0;
	
	//Checking vars-vars
	if( varId1 == varId2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_ID  C2=AIPI_ID"));
		f1 = AIPI_ID;
		f2 = AIPI_ID;
		
		//r = createJoinNode(c1, AIPI_ID, c2, AIPI_ID);
		
	}
	else if ( varId1 == varAttr2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_ID  C2=AIPI_AT"));
		f1 = AIPI_ID;
		f2 = AIPI_AT;
		//r = createJoinNode(c1, AIPI_ID, c2, AIPI_AT );
	}
	else if ( varId1 == varVal2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_ID  C2=AIPI_VL"));
		f1 = AIPI_ID;
		f2 = AIPI_VL;
		//r = createJoinNode(c1, AIPI_ID, c2, AIPI_VL);
	}
	else if ( varAttr1 == varId2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_AT  C2=AIPI_ID"));
		f1 = AIPI_AT;
		f2 = AIPI_ID;
		//r = createJoinNode(c1, AIPI_AT, c2, AIPI_ID);
	}
	else if ( varAttr1 == varAttr2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_AT  C2=AIPI_AT"));
		f1 = AIPI_AT;
		f2 = AIPI_AT;
		//r = createJoinNode(c1, AIPI_AT, c2, AIPI_AT);
	}
	else if ( varAttr1 == varVal2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_AT  C2=AIPI_VL"));
		f1 = AIPI_AT;
		f2 = AIPI_VL;
		//r = createJoinNode(c1, AIPI_AT, c2, AIPI_VL);
	}
	else if ( varVal1 == varId2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_VL  C2=AIPI_ID"));
		f1 = AIPI_VL;
		f2 = AIPI_ID;
		//r = createJoinNode(c1, AIPI_VL, c2, AIPI_ID);
		
	}
	else if ( varVal1 == varAttr2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_VL  C2=AIPI_AT"));
		f1 = AIPI_VL;
		f2 = AIPI_AT;
		//r = createJoinNode(c1, AIPI_VL, c2, AIPI_AT);
	}
	else if ( varVal1 == varVal2)
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_VL  C2=AIPI_VL"));
		f1 = AIPI_VL;
		f2 = AIPI_VL;
		//r = createJoinNode(c1, AIPI_VL, c2, AIPI_VL);
	}
	
	//Checking const-const
/*	
	else if( constId1 == constId2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_ID  C2=AIPI_ID"));	
		  f1 = AIPI_ID;
		  f2 = AIPI_ID;
		  //r = createJoinNode(c1, AIPI_ID, c2, AIPI_ID);
	}
	else if ( constId1 == constAttr2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_ID  C2=AIPI_AT"));	
		 f1 = AIPI_ID;
		 f2 = AIPI_AT;
		 // r = createJoinNode(c1, AIPI_ID, c2, AIPI_AT);
	}
	else if ( constId1 == constVal2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_ID  C2=AIPI_VL"));
		 f1 = AIPI_ID;
		 f2 = AIPI_VL;
		 //r = createJoinNode(c1, AIPI_ID, c2, AIPI_VL);
	}
	else if ( constAttr1 == constId2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_AT  C2=AIPI_ID"));
		 f1 = AIPI_AT;
		 f2 = AIPI_ID;
		 //r = createJoinNode(c1, AIPI_AT, c2, AIPI_ID);
	}
	else if ( constAttr1 == constAttr2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_AT  C2=AIPI_AT"));
		  f1 = AIPI_AT;
		  f2 = AIPI_AT;
		  //r = createJoinNode(c1, AIPI_AT, c2, AIPI_AT);
	}
	else if ( constAttr1 == constVal2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_AT  C2=AIPI_VL"));
		  f1 = AIPI_AT;
		  f2 = AIPI_VL;
		  //r = createJoinNode(c1, AIPI_AT, c2, AIPI_VL);	
	}
	else if (constVal1 == constId2 )
	{
		 //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_VL  C2=AIPI_ID"));
		 f1 = AIPI_VL;
		 f2 = AIPI_ID;
		 //r = createJoinNode(c1, AIPI_VL, c2, AIPI_ID);
	}
	else if (constVal1 == constAttr2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_VL  C2=AIPI_AT"));
		 f1 = AIPI_VL;
		 f2 = AIPI_AT;
		 // r = createJoinNode(c1, AIPI_VL, c2, AIPI_AT);
	}
	else if (constVal1 == constVal2)
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_VL  C2=AIPI_VL"));
		  f1 = AIPI_VL;
		  f2 = AIPI_VL;
		  //r = createJoinNode(c1, AIPI_VL, c2, AIPI_VL);
	}
	else
	{
		//Cheking vars-const 
		//AfxMessageBox(_T("Estoy en VAR_CONST,    C1=AIPI_VL  C2=AIPI_ID"));
		f1 = AIPI_VL;
		f2 = AIPI_ID;
		//r = createJoinNode(c1, AIPI_VL, c2, AIPI_ID);
	}
*/
	
	r = createJoinNode(c1, f1, c2, f2);
return r;

}


int CAipi_RETE_Network::bindNegatedCond(int c1, int c2, int f)
{
	
	CAipi_LHS	lhs;
	int type = -1;
	int r = 0;

	tstring varId1			= _T("VI1");
	tstring varId2			= _T("VI2");
	tstring varAttr1		= _T("VA1");
	tstring varAttr2		= _T("VA2");
	tstring varVal1			= _T("VV1");
	tstring varVal2			= _T("VV2");


	tstring constId1		= _T("KI1");
	tstring constId2		= _T("KI2");
	tstring constAttr1		= _T("KA1");
	tstring constAttr2		= _T("KA2");
	tstring constVal1		= _T("KV1");
	tstring constVal2		= _T("KV2");

	type = lhs.variableTest(c1);
	lhs.findLHSMembers(c1);
	
	switch(type)
	{
		case ID_K_K:
			varId1		= lhs.m_Id;
			constAttr1	= lhs.m_Attr;
			constVal1	= lhs.m_Val;
			break;
		case K_AT_K:
			constId1	= lhs.m_Id;
			varAttr1	= lhs.m_Attr;
			constVal1	= lhs.m_Val;
			break;
		case K_K_VL:
			constId1	= lhs.m_Id;
			constAttr1	= lhs.m_Attr;
			varVal1		= lhs.m_Val;
			break;
		case ID_AT_K:
			varId1		= lhs.m_Id;
			varAttr1	= lhs.m_Attr;
			constVal1	= lhs.m_Val;
			break;
		case ID_K_VL:
			varId1		= lhs.m_Id;
			constAttr1	= lhs.m_Attr;
			varVal1		= lhs.m_Val;
			break;
		case K_AT_VL:
			constId1	= lhs.m_Id;
			varAttr1	= lhs.m_Attr;
			varVal1		= lhs.m_Val;
			break;
		case ID_AT_VL:
			varId1		= lhs.m_Id;
			varAttr1	= lhs.m_Attr;
			varVal1		= lhs.m_Val;
			break;
		default:
			constId1	= lhs.m_Id;
			constAttr1	= lhs.m_Attr;
			constVal1	= lhs.m_Val;
			break;
	}
	
	//AfxMessageBox(varId1.data());
	//AfxMessageBox(varAttr1.data());
	//AfxMessageBox(varVal1.data());


	type = lhs.variableTest(c2);
	lhs.findLHSMembers(c2);
	
	switch(type)
	{
		case ID_K_K:
			varId2		= lhs.m_Id;
			constAttr2	= lhs.m_Attr;
			constVal2	= lhs.m_Val;
			break;
		case K_AT_K:
			constId2	= lhs.m_Id;
			varAttr2	= lhs.m_Attr;
			constVal2	= lhs.m_Val;
			break;
		case K_K_VL:
			constId2	= lhs.m_Id;
			constAttr2	= lhs.m_Attr;
			varVal2		= lhs.m_Val;
			break;
		case ID_AT_K:
			varId2		= lhs.m_Id;
			varAttr2	= lhs.m_Attr;
			constVal2	= lhs.m_Val;
			break;
		case ID_K_VL:
			varId2		= lhs.m_Id;
			constAttr2	= lhs.m_Attr;
			varVal2		= lhs.m_Val;
			break;
		case K_AT_VL:
			constId2	= lhs.m_Id;
			varAttr2	= lhs.m_Attr;
			varVal2		= lhs.m_Val;
			break;
		case ID_AT_VL:
			varId2		= lhs.m_Id;
			varAttr2	= lhs.m_Attr;
			varVal2		= lhs.m_Val;
			break;
		default:
			constId2	= lhs.m_Id;
			constAttr2	= lhs.m_Attr;
			constVal2	= lhs.m_Val;
			break;
	}

	
	//AfxMessageBox(varId2.data());
	//AfxMessageBox(varAttr2.data());
	//AfxMessageBox(varVal2.data());

	int f1, f2 = 0;
	
	//Checking vars-vars
	if( varId1 == varId2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_ID  C2=AIPI_ID"));
		f1 = AIPI_ID;
		f2 = AIPI_ID;
		
		//r = createJoinNode(c1, AIPI_ID, c2, AIPI_ID);
		
	}
	else if ( varId1 == varAttr2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_ID  C2=AIPI_AT"));
		f1 = AIPI_ID;
		f2 = AIPI_AT;
		//r = createJoinNode(c1, AIPI_ID, c2, AIPI_AT );
	}
	else if ( varId1 == varVal2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_ID  C2=AIPI_VL"));
		f1 = AIPI_ID;
		f2 = AIPI_VL;
		//r = createJoinNode(c1, AIPI_ID, c2, AIPI_VL);
	}
	else if ( varAttr1 == varId2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_AT  C2=AIPI_ID"));
		f1 = AIPI_AT;
		f2 = AIPI_ID;
		//r = createJoinNode(c1, AIPI_AT, c2, AIPI_ID);
	}
	else if ( varAttr1 == varAttr2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_AT  C2=AIPI_AT"));
		f1 = AIPI_AT;
		f2 = AIPI_AT;
		//r = createJoinNode(c1, AIPI_AT, c2, AIPI_AT);
	}
	else if ( varAttr1 == varVal2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_AT  C2=AIPI_VL"));
		f1 = AIPI_AT;
		f2 = AIPI_VL;
		r = createJoinNode(c1, AIPI_AT, c2, AIPI_VL);
	}
	else if ( varVal1 == varId2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_VL  C2=AIPI_ID"));
		f1 = AIPI_VL;
		f2 = AIPI_ID;
		//r = createJoinNode(c1, AIPI_VL, c2, AIPI_ID);
		
	}
	else if ( varVal1 == varAttr2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_VL  C2=AIPI_AT"));
		f1 = AIPI_VL;
		f2 = AIPI_AT;
		//r = createJoinNode(c1, AIPI_VL, c2, AIPI_AT);
	}
	else if ( varVal1 == varVal2)
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_VL  C2=AIPI_VL"));
		f1 = AIPI_VL;
		f2 = AIPI_VL;
		//r = createJoinNode(c1, AIPI_VL, c2, AIPI_VL);
	}
	//Checking const-const
	
	else if( constId1 == constId2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_ID  C2=AIPI_ID"));	
		  f1 = AIPI_ID;
		  f2 = AIPI_ID;
		  //r = createJoinNode(c1, AIPI_ID, c2, AIPI_ID);
	}
	else if ( constId1 == constAttr2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_ID  C2=AIPI_AT"));	
		 f1 = AIPI_ID;
		 f2 = AIPI_AT;
		 // r = createJoinNode(c1, AIPI_ID, c2, AIPI_AT);
	}
	else if ( constId1 == constVal2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_ID  C2=AIPI_VL"));
		 f1 = AIPI_ID;
		 f2 = AIPI_VL;
		 //r = createJoinNode(c1, AIPI_ID, c2, AIPI_VL);
	}
	else if ( constAttr1 == constId2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_AT  C2=AIPI_ID"));
		 f1 = AIPI_AT;
		 f2 = AIPI_ID;
		 //r = createJoinNode(c1, AIPI_AT, c2, AIPI_ID);
	}
	else if ( constAttr1 == constAttr2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_AT  C2=AIPI_AT"));
		  f1 = AIPI_AT;
		  f2 = AIPI_AT;
		  //r = createJoinNode(c1, AIPI_AT, c2, AIPI_AT);
	}
	else if ( constAttr1 == constVal2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_AT  C2=AIPI_VL"));
		  f1 = AIPI_AT;
		  f2 = AIPI_VL;
		  //r = createJoinNode(c1, AIPI_AT, c2, AIPI_VL);	
	}
	else if (constVal1 == constId2 )
	{
		 //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_VL  C2=AIPI_ID"));
		 f1 = AIPI_VL;
		 f2 = AIPI_ID;
		 //r = createJoinNode(c1, AIPI_VL, c2, AIPI_ID);
	}
	else if (constVal1 == constAttr2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_VL  C2=AIPI_AT"));
		 f1 = AIPI_VL;
		 f2 = AIPI_AT;
		 // r = createJoinNode(c1, AIPI_VL, c2, AIPI_AT);
	}
	else if (constVal1 == constVal2)
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_VL  C2=AIPI_VL"));
		  f1 = AIPI_VL;
		  f2 = AIPI_VL;
		  //r = createJoinNode(c1, AIPI_VL, c2, AIPI_VL);
	}
	else
	{
		//Cheking vars-const 
		//AfxMessageBox(_T("Estoy en VAR_CONST,    C1=AIPI_VL  C2=AIPI_ID"));
		f1 = AIPI_VL;
		f2 = AIPI_ID;
		//r = createJoinNode(c1, AIPI_VL, c2, AIPI_ID);
	}
	
	
	if( f == 1 )
	{
		return f1;
	}
	
	
return f2;

}


/*
int CAipi_RETE_Network::removeBindCond( int b1, int b2, int w1, int w2,int c1, int c2)
{
	CAipi_LHS		lhs;
	CAipi_WM		wm;
	CAipi_RETE_BM	bm;
	CAipi_RETE_TK	tk;
	
	int type = -1;
	int r = 0;

	tstring varId1					= _T("VI1");
	tstring varId2					= _T("VI2");
	tstring varAttr1				= _T("VA1");
	tstring varAttr2				= _T("VA2");
	tstring varVal1					= _T("VV1");
	tstring varVal2					= _T("VV2");

	tstring constId1				= _T("KI1");
	tstring constId2				= _T("KI2");
	tstring constAttr1				= _T("KA1");
	tstring constAttr2				= _T("KA2");
	tstring constVal1				= _T("KV1");
	tstring constVal2				= _T("KV2");

	
	
	type = lhs.variableTest(c1);
	lhs.findLHSE(c1);
	
	switch(type)
	{
		case ID_K_K:
			varId1		= lhs.m_Id;
			constAttr1	= lhs.m_Attr;
			constVal1	= lhs.m_Val;
			break;
		case K_AT_K:
			constId1	= lhs.m_Id;
			varAttr1	= lhs.m_Attr;
			constVal1	= lhs.m_Val;
			break;
		case K_K_VL:
			constId1	= lhs.m_Id;
			constAttr1	= lhs.m_Attr;
			varVal1		= lhs.m_Val;
			break;
		case ID_AT_K:
			varId1		= lhs.m_Id;
			varAttr1	= lhs.m_Attr;
			constVal1	= lhs.m_Val;
			break;
		case ID_K_VL:
			varId1		= lhs.m_Id;
			constAttr1	= lhs.m_Attr;
			varVal1		= lhs.m_Val;
			break;
		case K_AT_VL:
			constId1	= lhs.m_Id;
			varAttr1	= lhs.m_Attr;
			varVal1		= lhs.m_Val;
			break;
		case ID_AT_VL:
			varId1		= lhs.m_Id;
			varAttr1	= lhs.m_Attr;
			varVal1		= lhs.m_Val;
			break;
		default:
			constId1	= lhs.m_Id;
			constAttr1	= lhs.m_Attr;
			constVal1	= lhs.m_Val;
			break;
	}
	
	//AfxMessageBox(varId1.data());
	//AfxMessageBox(varAttr1.data());
	//AfxMessageBox(varVal1.data());


	type = lhs.variableTest(c2);
	lhs.findLHSE(c2);
	
	switch(type)
	{
		case ID_K_K:
			varId2		= lhs.m_Id;
			constAttr2	= lhs.m_Attr;
			constVal2	= lhs.m_Val;
			break;
		case K_AT_K:
			constId2	= lhs.m_Id;
			varAttr2	= lhs.m_Attr;
			constVal2	= lhs.m_Val;
			break;
		case K_K_VL:
			constId2	= lhs.m_Id;
			constAttr2	= lhs.m_Attr;
			varVal2		= lhs.m_Val;
			break;
		case ID_AT_K:
			varId2		= lhs.m_Id;
			varAttr2	= lhs.m_Attr;
			constVal2	= lhs.m_Val;
			break;
		case ID_K_VL:
			varId2		= lhs.m_Id;
			constAttr2	= lhs.m_Attr;
			varVal2		= lhs.m_Val;
			break;
		case K_AT_VL:
			constId2	= lhs.m_Id;
			varAttr2	= lhs.m_Attr;
			varVal2		= lhs.m_Val;
			break;
		case ID_AT_VL:
			varId2		= lhs.m_Id;
			varAttr2	= lhs.m_Attr;
			varVal2		= lhs.m_Val;
			break;
		default:
			constId2	= lhs.m_Id;
			constAttr2	= lhs.m_Attr;
			constVal2	= lhs.m_Val;
			break;
	}

	
	//AfxMessageBox(varId2.data());
	//AfxMessageBox(varAttr2.data());
	//AfxMessageBox(varVal2.data());


	
	//Checking vars-vars
	if( varId1 == varId2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_ID  C2=AIPI_ID"));
		
		r = removeUpdate(b1, b2, w1, w2, AIPI_ID, AIPI_ID);
		
	}
	else if ( varId1 == varAttr2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_ID  C2=AIPI_AT"));
		
		r = removeUpdate(b1, b2, w1, w2, AIPI_ID, AIPI_AT );
	}
	else if ( varId1 == varVal2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_ID  C2=AIPI_VL"));
		
		r = removeUpdate( b1, b2, w1, w2, AIPI_ID, AIPI_VL);
	}
	else if ( varAttr1 == varId2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_AT  C2=AIPI_ID"));
		
		r = removeUpdate( b1, b2, w1, w2, AIPI_AT,  AIPI_ID);
	}
	else if ( varAttr1 == varAttr2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_AT  C2=AIPI_AT"));
	
		r = removeUpdate( b1, b2, w1, w2, AIPI_AT, AIPI_AT);
	}
	else if ( varAttr1 == varVal2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_AT  C2=AIPI_AT"));
		
		r = removeUpdate( b1, b2, w1, w2, AIPI_AT, AIPI_VL);
	}
	else if ( varVal1 == varId2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_VL  C2=AIPI_ID"));
		
		r = removeUpdate( b1, b2, w1, w2, AIPI_VL, AIPI_ID);
		
	}
	else if ( varVal1 == varAttr2 )
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_VL  C2=AIPI_AT"));
	
		r = removeUpdate( b1, b2, w1, w2, AIPI_VL, AIPI_AT);
	}
	else if ( varVal1 == varVal2)
	{
		//AfxMessageBox(_T("Estoy en VAR,    C1=AIPI_VL  C2=AIPI_VL"));
		
		r = removeUpdate( b1, b2, w1, w2, AIPI_VL, AIPI_VL);
	}
	//Checking const-const
	
	else if( constId1 == constId2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_ID  C2=AIPI_ID"));	
		  
		  r = removeUpdate( b1, b2, w1, w2, AIPI_ID, AIPI_ID);
	}
	else if ( constId1 == constAttr2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_ID  C2=AIPI_AT"));	
		 
		  r = removeUpdate( b1, b2, w1, w2, AIPI_ID, AIPI_AT);
	}
	else if ( constId1 == constVal2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_ID  C2=AIPI_VL"));
		 
		  r = removeUpdate( b1, b2, w1, w2, AIPI_ID, AIPI_VL);
	}
	else if ( constAttr1 == constId2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_AT  C2=AIPI_ID"));
		 
		  r = removeUpdate( b1, b2, w1, w2, AIPI_AT, AIPI_ID);
	}
	else if ( constAttr1 == constAttr2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_AT  C2=AIPI_AT"));
		  
		  r = removeUpdate( b1, b2, w1, w2, AIPI_AT, AIPI_AT);
	}
	else if ( constAttr1 == constVal2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_AT  C2=AIPI_VL"));
		  
		  r = removeUpdate( b1, b2, w1, w2, AIPI_AT, AIPI_VL);	
	}
	else if (constVal1 == constId2 )
	{
		 //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_VL  C2=AIPI_ID"));
		 
		 r = removeUpdate( b1, b2, w1, w2, AIPI_VL, AIPI_ID);
	}
	else if (constVal1 == constAttr2 )
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_VL  C2=AIPI_AT"));
		 
		  r = removeUpdate( b1, b2, w1, w2, AIPI_VL, AIPI_AT);
	}
	else if (constVal1 == constVal2)
	{
		  //AfxMessageBox(_T("Estoy en CONST,    C1=AIPI_VL  C2=AIPI_VL"));
		  
		  r = removeUpdate( b1, b2, w1, w2, AIPI_VL, AIPI_VL);
	}
	else
	{
		//Cheking vars-const 
		//AfxMessageBox(_T("Estoy en VAR_CONST,    C1=AIPI_VL  C2=AIPI_ID"));
		
		r = removeUpdate( b1, b2, w1, w2, AIPI_VL, AIPI_ID);
	}
	

return r;

}

*/





















int CAipi_RETE_Network::findEqualCond1(int a, int c)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_LHS lhs;

	for( CMainFrame::g_mCond_AM::const_iterator iter1 = pMainFrame->gmCond_AM.begin(); iter1!= pMainFrame->gmCond_AM.end(); ++iter1)
	{
		int am = iter1->second;
		if( am == a )
		{
			if( lhs.compareEqualCond(iter1->first, c))
			{
				return iter1->first;
				
			}
		}
	}

return c;

}


int CAipi_RETE_Network::findEqualCond2(int a, int c)
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


/*
int CAipi_RETE_Network::checkNCC(int c1)
{
	CAipi_RETE_NCCNode ncc;
		
	int NegCC = ncc.findEndCondNCC(c1);
	int c = NOT_FOUND; 
	
	if( NegCC != NOT_FOUND )
	{
		c = ncc.findNodeNCC(NegCC);
		if( c != NOT_FOUND )
		{
			return ncc.m_C1;
		}
	}

		
return c;

}		
		
*/		
		
		
		


void CAipi_RETE_Network::checkRepeatedCond(int p)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmPM_Cond::iterator it_PM;
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
		
	vector<int> vPM;
	m_CurrentPM = p;
	m_CurrentNCC = -1;
	m_Negated = false;
	
	
	
	pPM = pMainFrame->gmmPM_Cond.equal_range(p);

	for(it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		vPM.push_back(it_PM->second);
		/*
		CString str;
		str.Format(_T("PM...%d  " ), it_PM->second);
		AfxMessageBox(str);
		*/
	}
		
	if( vPM.size() > 1  )
	{	
					
		m_CurrentDN = createDummyNode(vPM.at(0), p);
		
		/*
		CString str;
		str.Format(_T("DM...%d  " ), m_CurrentDN);
		AfxMessageBox(str);
		str.Format(_T("PM...%d  " ), p);
		AfxMessageBox(str);
		*/

		int n = pMainFrame->gmmPM_Cond.count(p);
		
		for(int i = 0; i<n-1; ++i)
		{
			
			 
			int c1 = vPM.at(i);
			int c2 = vPM.at(i+1);
			
			/*
			TCHAR buffer[4];
			CString str;
			AfxMessageBox(_T("CheckRepeated Conditions : "));
			str =  _itot( c1, buffer, 10 );
			AfxMessageBox(str);
			str =  _itot( c2, buffer, 10 );
			AfxMessageBox(str);	
			*/

			
			
			if( m_CurrentDN != REPEATED )
			{
				bindCond(c1,c2);
			}
			else
			{
				
				CAipi_RETE_AM am;
				int a1 = am.findCond_AM(c1);
				int a2 = am.findCond_AM(c2);
					
				int rc1 = findEqualCond2(a1, c1);
				int rc2 = findEqualCond2(a2, c2);
				
				/*
				CString str;
				str.Format(_T("RC1...%d  " ), rc1);
				AfxMessageBox(str);
				str.Format(_T("RC2...%d  " ), rc2);
				AfxMessageBox(str);
				*/
				
				int notc = checkRepeatedNegatedCond(c2, rc2);
				if( notc != REPEATED )
				{
					//AfxMessageBox(_T("Negado Repetido"));	
					bindCond(c1,c2);
					continue;
				}
				
				int negcc = checkRepeatedNCC(c1, rc1, a1);
				if( negcc != NOT_FOUND )
				{
					//AfxMessageBox(_T("Negado Condición Conjunción"));
					CAipi_PM pm;
					int cj = pm.PM_CondUpperBound(m_CurrentPM);
					/*
					CString str;
					str.Format(_T("Upper Cond...%d  " ), cj);
					AfxMessageBox(str);
					*/
					if( cj == negcc )
					{
						return;
					}
					else
					{
						//AfxMessageBox(_T("HHHH"));
						c1 = negcc;
						c2 = negcc + 1;
						bindCond(c1, c2);
						continue;
					}
				}
				else
				{
					//AfxMessageBox(_T("AIPI"));
					
					//bindCond(c1, c2);
					//continue;
				}

				CAipi_RETE_Cond co;
				
				int j1 = co.findCond2JN(rc1);
				int j2 = co.findCond2JN(rc2);

				
			
				
				if( j1 == NOT_FOUND || j2 == NOT_FOUND )
				{
					//AfxMessageBox(_T("jn1 o jn2 No encontrado"));
					bindCond(c1, c2);
					continue;
					
				}
				
								
				/*	
				CString str;
				str.Format(_T("C1...%d  " ), c1);
				AfxMessageBox(str);
				str.Format(_T("C2...%d  " ), c2);
				AfxMessageBox(str);
				*/
				
						
				
							
				if(rc1 + 1 != rc2 )
				{
					bindCond(c1,c2);
					continue;
				}
				
				CAipi_RETE_NodeCond no;
				co.addCond2(c2, j2, m_CurrentPM, _T(""));
				co.addCond1(c1, j2, m_CurrentPM, _T(""));
				no.addNodeCond(j2, c1, c2, m_CurrentPM);
				//m_nFiredCond++;

				
				/*
				str.Format(_T("JN1...%d  " ), j1);
				AfxMessageBox(str);
				str.Format(_T("JN2...%d  " ), j2);
				AfxMessageBox(str);
				*/
							
			}
		}
	}	
	else if ( vPM.size() == 1  )
	{
		m_CurrentDN = createDummyNode(vPM.at(0), m_CurrentPM );
	}
	else
	{
		AfxMessageBox(_T("No hay reglas en la producción"));
	}
		
	
			
}		





int CAipi_RETE_Network::checkRepeatedNegatedCond(int c, int rc)
{

	if( c != rc )
	{
		CAipi_RETE_NNode nn;
		int nc = nn.findCond_NN(c);
		int rnc = nn.findCond_NN(rc);
		/*			
		CString str;
		str.Format(_T("NEGATED NODE...%d  " ), nc);
		AfxMessageBox(str);
		str.Format(_T("REPEATED NEGATED NODE...%d  " ), rnc);
		AfxMessageBox(str);
		*/			
		if( nc != rnc )
		{
			m_CurrentDN = NNode;
			return c;
		}
	}

return REPEATED;

}



int CAipi_RETE_Network::checkRepeatedNCC(int c, int rc, int a)
{
	
	CAipi_RETE_NCCNode ncc;
	CAipi_PM pm;
	
	int end = ncc.findEndCond_NCC(c);
	if( end != NOT_FOUND)
	{
		AfxMessageBox(_T("Fin Hola2"));
		m_CurrentNCC = 1;
	}
	
	int ncc2 = ncc.findInitCond_NCC(c);
	if( ncc2 == NOT_FOUND )
	{
		return NOT_FOUND;
	}
	else
	{
		
		int uCond = pm.PM_CondLowerBound(m_CurrentPM);
		
		CString str;
		str.Format(_T("Upper C...%d  " ), uCond);
		AfxMessageBox(str);
		
		if( m_CurrentDN == REPEATED && uCond == c )
		{
			AfxMessageBox(_T("Hola3"));
			m_CurrentNCC = -1;
		}
		else
		{
			AfxMessageBox(_T("Hola2"));
			m_CurrentNCC = 1;
		}
	}
	
	if( c != rc )
	{
		CString str;
		str.Format(_T("C...%d  " ), c);
		AfxMessageBox(str);
		str.Format(_T("RC...%d  " ), rc);
		AfxMessageBox(str);
		
		
		
		
	

		

		

		int ncc1 = ncc.findInitCond_NCC(rc);
		if( ncc1 == NOT_FOUND )
		{
			//AfxMessageBox(_T("Hola1"));
			//m_CurrentNCC = -1;
			return NOT_FOUND;
		}

		
		

		int rcini = ncc.findInitCond_NCC(ncc1);
		int rcend = ncc.findEndCond_NCC(ncc1);
		
		//int eqIni1 = findEqualCond2(a, rcini);
		//int eqEnd1 = findEqualCond2(a, rcend);

		
		int rp = ncc.findNCC_PM(ncc1);
		
		
		
		int cini = ncc.findInitCond_NCC(ncc2);
		int cend = ncc.findEndCond_NCC(ncc2);

		
		
		//int eqIni2 = findEqualCond2(a, rcini);
		//int eqEnd2 = findEqualCond2(a, rcend);

		int p = ncc.findNCC_PM(ncc2);
		
		int eq = pm.compareRangeNNCond(rp, p, rcini, rcend, cini, cend);
		
		if( eq == 1 )
		{
			AfxMessageBox(_T("Adios"));
			return cend;
		}
		
		/*
		CString str;
		str.Format(_T("NCC1...%d  " ), ncc1);
		AfxMessageBox(str);
		str.Format(_T("NCC2...%d  " ), ncc2);
		AfxMessageBox(str);
		str.Format(_T("RCondIni...%d  " ), rcini);
		AfxMessageBox(str);
		str.Format(_T("CondIni...%d  " ), cini);
		AfxMessageBox(str);
		str.Format(_T("RCondEnd...%d  " ), rcend);
		AfxMessageBox(str);
		str.Format(_T("CondEnd...%d  " ), cend);
		AfxMessageBox(str);
		*/
		//str.Format(_T("EqCondIni 1...%d  " ), eqIni1);
		//AfxMessageBox(str);
		//str.Format(_T("EqCondIni 2...%d  " ), eqIni2);
		//AfxMessageBox(str);
		//str.Format(_T("EqCondEnd 1...%d  " ), eqEnd1);
		//AfxMessageBox(str);
		//str.Format(_T("EqCondEnd 2...%d  " ), eqEnd2);
		//AfxMessageBox(str);
		/*
		str.Format(_T("rp...%d  " ), rp);
		AfxMessageBox(str);
		str.Format(_T("p...%d  " ), p);
		AfxMessageBox(str);
*/

		/*
		if( eqIni1 == eqIni2 && eqEnd1 == eqEnd2)
		{
			return cend;
		}
		*/
	}


return NOT_FOUND;

}


int CAipi_RETE_Network::createNCCNode(int c1)
{
	
	CAipi_RETE_NCCNode	ncc;

/*	
	TCHAR buffer[4];
	CString str;
	AfxMessageBox(_T("CreateJN Conditions : "));
	str =  _itot( c1, buffer, 10 );
	AfxMessageBox(str);
*/	
	
	
	
	int ncc1 = ncc.findInitCond_NCC(c1);
	
/*	
	AfxMessageBox(_T("NCC1 : "));
	str =  _itot( ncc1, buffer, 10 );
	AfxMessageBox(str);
*/	

	if( ncc1 != NOT_FOUND)
	{
		
		CAipi_RETE_Node node;
		CAipi_RETE_Cond co;
		int nccJN1 = co.findCond2JN(c1);
		int nccBM1 = node.findNodeBM1(nccJN1);
		ncc.addNCCN_BM(ncc1, nccBM1);

		//jn.findJN(nccJN1);

		//ncc.addNodeNCC(ncc1, m_CurrentPM, nccJN1, jn.m_Cond1, jn.m_Field1, jn.m_Cond2, jn.m_Field2, jn.m_BM1, jn.m_BM2, jn.m_Type);
		
/*		
		AfxMessageBox(_T("NCC1 Join Node : "));
		str =  _itot( nccJN1, buffer, 10 );
		AfxMessageBox(str);
		AfxMessageBox(_T("NCC1 Beta Memory : "));
		str =  _itot( nccBM1, buffer, 10 );
		AfxMessageBox(str);
		AfxMessageBox(_T("Current PM : "));
		str =  _itot( m_CurrentPM, buffer, 10 );
		AfxMessageBox(str);
*/	
		
		
		return ncc1;
	}
	
	

return NOT_FOUND;

}


int CAipi_RETE_Network::createNCCPartner(int c2)
{
	
	CAipi_RETE_NCCNode	ncc;
	CAipi_RETE_Node	node;
	CAipi_RETE_Cond co;
	/*
	TCHAR buffer[4];
	CString str;
	AfxMessageBox(_T("CreateJN Conditions : "));
	str =  _itot( c2, buffer, 10 );
	AfxMessageBox(str);
	*/
	
	
	
	int ncc2 = ncc.findEndCond_NCC(c2);
	
	/*
	AfxMessageBox(_T("NCC2 : "));
	str =  _itot( ncc2, buffer, 10 );
	AfxMessageBox(str);
	*/
		
	if( ncc2 != NOT_FOUND)
	{
		int nccJN2 = co.findCond2JN(c2);
		int nccBM2 = node.findNodeBM2(nccJN2);
		ncc.addNCCPartnerN_BM(ncc2, nccBM2);

/*	
		AfxMessageBox(_T("NCC2 Join Node : "));
		str =  _itot( nccJN2, buffer, 10 );
		AfxMessageBox(str);
		AfxMessageBox(_T("NCC2 Beta Memory : "));
		str =  _itot( nccBM2, buffer, 10 );
		AfxMessageBox(str);

*/
		return ncc2;
	}

return NOT_FOUND;

}



void CAipi_RETE_Network::processNCC(int c1, int c2, int b, int BME, int newJoin, int newTK, int finalCond, CAipi_RETE_NCCNode ncc, CAipi_RETE_PNode pn, CAipi_RETE_BM bm)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		
	int ncc1 = createNCCNode(c1);
	int nccBM1 =0;
	int nccBM2 = 0;

	if( ncc1 != NOT_FOUND )
	{
		nccBM1 = ncc.findNCCN_BM(ncc1);
	}
	
	int ncc2 = createNCCPartner(c2);
	if( ncc2 != NOT_FOUND )
	{
			
		nccBM2 = ncc.findNCCPartnerN_BM(ncc2);
			
		CMainFrame::g_mmBM::iterator it_BM;
		pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
		pBM = pMainFrame->gmmBM.equal_range(nccBM2);

		for(it_BM = pBM.first; it_BM != pBM.second; ++it_BM)
		{
			//ncc.addNCCPartnerN_TK(ncc2, it_BM->second);
		}
			
			/*					
			CString str;
			str.Format(_T("NewTK1...%d  " ), newTK);
			AfxMessageBox(str);
			str.Format(_T("WME2...%d  " ), WME2);
			AfxMessageBox(str);
			*/
			
		if( newTK != UNDEFINE && newTK != EMPTY )
		{
			bm.editBM_ParentTK(nccBM2 ,EMPTY);
			//AfxMessageBox(_T("hola1"));
		}
		else
		{
			//AfxMessageBox(_T("hola2"));
			 ncc.editBM_TK(nccBM1, nccBM2);
				
			/*
			AfxMessageBox(_T("nccBM1"));
			str =  _itot( nccBM1, buffer, 10 );
			AfxMessageBox(str);
			*/
			
				 
			if( finalCond == c2 )
			{
				//AfxMessageBox(_T("hola3"));
				//int BMtoken = bm.searchTokenBM(nccBM2);
					
				/*
				TCHAR buffer[4];
				CString str;
				AfxMessageBox(_T("BME Beta Memory Token:"));
				str =  _itot( BMtoken, buffer, 10 );
				AfxMessageBox(str);
				*/
		
				//pn.addPNode(m_CurrentPM, newJoin, c1, c2, b, BME, FPNode );
				pMainFrame->g_vFiredPM.push_back(m_CurrentPM);
				
			}
				
				/*
				
				CString str;
				str.Format(_T("nccC1...%d  " ), nccC1);
				AfxMessageBox(str);
				str.Format(_T("nccC2...%d  " ), nccC2);
				AfxMessageBox(str);
				*/
			
		}
		
	}


}




void CAipi_RETE_Network::createNetwork()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mPM::iterator it_PM;

		
	if ( !pMainFrame->gmPM.empty() )
	{
		for(it_PM = pMainFrame->gmPM.begin(); it_PM != pMainFrame->gmPM.end(); ++it_PM)
		{
			//int c1 = pm.findLowerCond(it_PM->first);
			checkRepeatedCond(it_PM->first);		
		}
	}
}






void CAipi_RETE_Network::clear()
{
	CAipi_LHS	lhs;
	lhs.clearLHS();
	//lhs.clearRepCond();

	CAipi_RETE_AM	am;
	am.clearAMStructs();
	am.clearLogicStructs();
	
	CAipi_RETE_BM	bm;
	bm.clearBM();
	
	CAipi_RETE_JNode	jn;
	jn.clearJNStructs();
	
	CAipi_RETE_TK	tk;
	tk.clearTK();
	
	CAipi_PM		pm;
	pm.clearPM_Cond();
	pm.clearPM_Vars();

	CAipi_WM		wk;
	wk.clearWM();

	CAipi_RETE_NNode   nn;
	nn.clearNNStructs();

	CAipi_RETE_Vars var;
	var.clearVarsStructs();
	



}



/*
void CAipi_RETE_Network::bindingAllVars()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	for( CMainFrame::g_mLHS::const_iterator iter1 = pMainFrame->gmLHS.begin(); iter1!= pMainFrame->gmLHS.end(); ++iter1)
	{	
		for( CMainFrame::g_mLHS::const_iterator iter2 = pMainFrame->gmLHS.begin(); iter2!= pMainFrame->gmLHS.end(); ++iter2)
		{	
			if(iter1->first < iter2->first  )
			{
				getLHSVars(iter1->first, iter2->first);
				//getLHS(iter1->first, iter2->first);
			}
		}				

	}
}

void CAipi_RETE_Network::bindingAllConst()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	for( CMainFrame::g_mLHS::const_iterator iter1 = pMainFrame->gmLHS.begin(); iter1!= pMainFrame->gmLHS.end(); ++iter1)
	{	
		for( CMainFrame::g_mLHS::const_iterator iter2 = pMainFrame->gmLHS.begin(); iter2!= pMainFrame->gmLHS.end(); ++iter2)
		{	
			if(iter1->first != iter2->first  )
			{
				bindConstant(iter1->first, iter2->first);
			}
		}				

	}
}

*/

  /*

void CAipi_RETE_Network::bindVars_Vars()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	vector <tstring> vBindCond;
	
	CMainFrame::g_mmVar_Id::iterator iterId;
    CMainFrame::g_mmVar_Attr::iterator iterAttr;
	CMainFrame::g_mmVar_Val::iterator iterVal;

	int sizeId		= pMainFrame->gmmVar_Id.size();
	int sizeAttr	= pMainFrame->gmmVar_Attr.size();
	int sizeVal		= pMainFrame->gmmVar_Val.size();
	
	
	for( iterId = pMainFrame->gmmVar_Id.begin(); iterId!= pMainFrame->gmmVar_Id.end(); ++iterId)
	{
			iterAttr = pMainFrame->gmmVar_Attr.find(iterId->first);
			if( iterAttr != pMainFrame->gmmVar_Attr.end())
			{
				
				pMainFrame->mmBindCond.insert(CMainFrame::m_mmBindCond::value_type(iterId->second, iterAttr->second));
				
				//findFieldBound(iterAttr->second, _T("AIPI_AT"), iterId->second, _T("AIPI_ID"));	
				findFieldBound(iterId->second, _T("AIPI_ID"), iterAttr->second, _T("AIPI_AT"));	
				//AfxMessageBox(iterAttr->second.data());
				//AfxMessageBox(iterId->second.data());
				//vBindCond.push_back(iterId->second);
				//vBindCond.push_back(iterAttr->second);
			
			}
		
			iterVal = pMainFrame->gmmVar_Val.find(iterId->first);	
			if( iterVal != pMainFrame->gmmVar_Val.end())
			{
				
				pMainFrame->mmBindCond.insert(CMainFrame::m_mmBindCond::value_type(iterId->second, iterVal->second));

				//findFieldBound(iterVal->second, _T("AIPI_VL"), iterId->second, _T("AIPI_ID"));
				findFieldBound(iterId->second, _T("AIPI_ID"), iterVal->second, _T("AIPI_VL"));
				//AfxMessageBox(iterVal->second.data());
				//AfxMessageBox(iterId->second.data());
				//vBindCond.push_back(iterId->second);
				//vBindCond.push_back(iterVal->second);
			}
		
	}


	

	for( iterAttr = pMainFrame->gmmVar_Attr.begin(); iterAttr!= pMainFrame->gmmVar_Attr.end(); ++iterAttr)
	{
		
		iterVal = pMainFrame->gmmVar_Val.find(iterAttr->first);	
		if( iterVal != pMainFrame->gmmVar_Val.end())
		{
			
			pMainFrame->mmBindCond.insert(CMainFrame::m_mmBindCond::value_type(iterAttr->second, iterVal->second));
			
			//findFieldBound(iterVal->second, _T("AIPI_VL"), iterAttr->second, _T("AIPI_AT"));
			findFieldBound(iterAttr->second, _T("AIPI_AT"), iterVal->second, _T("AIPI_VL"));
			//AfxMessageBox(iterVal->second.data());
			//AfxMessageBox(iterId->second.data());
			//vBindCond.push_back(iterAttr->second);
			//vBindCond.push_back(iterVal->second);
		}


	}

	//unique_copy(vBindCond.begin(), vBindCond.end(), back_inserter(pMainFrame->g_vDistBindCond));

}


void CAipi_RETE_Network::bindConst_Const()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	vector <tstring> vBindCond;
	
	CMainFrame::g_mmConst_Id::iterator iterId;
    CMainFrame::g_mmConst_Attr::iterator iterAttr;
	CMainFrame::g_mmConst_Val::iterator iterVal;

	int sizeId		= pMainFrame->gmmConst_Id.size();
	int sizeAttr	= pMainFrame->gmmConst_Attr.size();
	int sizeVal		= pMainFrame->gmmConst_Val.size();
	
	
	for( iterId = pMainFrame->gmmConst_Id.begin(); iterId!= pMainFrame->gmmConst_Id.end(); ++iterId)
	{
			iterAttr = pMainFrame->gmmConst_Attr.find(iterId->first);
			if( iterAttr != pMainFrame->gmmConst_Attr.end())
			{
				
				pMainFrame->mmBindCond.insert(CMainFrame::m_mmBindCond::value_type(iterId->second, iterAttr->second));
				
				//findFieldBound(iterAttr->second, _T("AIPI_AT"), iterId->second, _T("AIPI_ID"));	
				findFieldBoundConst(iterId->second, _T("AIPI_ID"), iterAttr->second, _T("AIPI_AT"));	
				//AfxMessageBox(iterAttr->second.data());
				//AfxMessageBox(iterId->second.data());
				//vBindCond.push_back(iterId->second);
				//vBindCond.push_back(iterAttr->second);
			
			}
		
			iterVal = pMainFrame->gmmConst_Val.find(iterId->first);	
			if( iterVal != pMainFrame->gmmConst_Val.end())
			{
				
				pMainFrame->mmBindCond.insert(CMainFrame::m_mmBindCond::value_type(iterId->second, iterVal->second));
	
				//findFieldBound(iterVal->second, _T("AIPI_VL"), iterId->second, _T("AIPI_ID"));
				findFieldBoundConst(iterId->second, _T("AIPI_ID"), iterVal->second, _T("AIPI_VL"));
				//AfxMessageBox(iterVal->second.data());
				//AfxMessageBox(iterId->second.data());
				//vBindCond.push_back(iterId->second);
				//vBindCond.push_back(iterVal->second);
			}
		
	}


	

	for( iterAttr = pMainFrame->gmmConst_Attr.begin(); iterAttr!= pMainFrame->gmmConst_Attr.end(); ++iterAttr)
	{
		
		iterVal = pMainFrame->gmmConst_Val.find(iterAttr->first);	
		if( iterVal != pMainFrame->gmmConst_Val.end())
		{
			
			pMainFrame->mmBindCond.insert(CMainFrame::m_mmBindCond::value_type(iterVal->second, iterAttr->second));
			
			
			findFieldBoundConst(iterVal->second, _T("AIPI_VL"), iterAttr->second, _T("AIPI_AT"));
			//findFieldBound(iterAttr->second, _T("AIPI_AT"), iterVal->second, _T("AIPI_VL"));
			//AfxMessageBox(iterVal->second.data());
			//AfxMessageBox(iterId->second.data());
			//vBindCond.push_back(iterAttr->second);
			//vBindCond.push_back(iterVal->second);
		}


	}

	//unique_copy(vBindCond.begin(), vBindCond.end(), back_inserter(pMainFrame->g_vDistBindCond));

}



void CAipi_RETE_Network::bindConst_Vars()
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	vector <tstring> vBindCond;
	
	CMainFrame::g_mmConst_Id::iterator iterIdK;
    CMainFrame::g_mmConst_Attr::iterator iterAttrK;
	CMainFrame::g_mmConst_Val::iterator iterValK;
	
	CMainFrame::g_mmVar_Id::iterator iterIdV;
    CMainFrame::g_mmVar_Attr::iterator iterAttrV;
	CMainFrame::g_mmVar_Val::iterator iterValV;


	int sizeId		= pMainFrame->gmmVar_Id.size();
	int sizeAttr	= pMainFrame->gmmVar_Attr.size();
	int sizeVal		= pMainFrame->gmmVar_Val.size();
	
	
	if( sizeId > 0 )
	{
		for( iterIdK = pMainFrame->gmmConst_Id.begin(); iterIdK!= pMainFrame->gmmConst_Id.end(); ++iterIdK)
		{
			for( iterAttrV = pMainFrame->gmmVar_Attr.begin(); iterAttrV!= pMainFrame->gmmVar_Attr.end(); ++iterAttrV)
			{
				pMainFrame->mmBindCond.insert(CMainFrame::m_mmBindCond::value_type(iterIdK->second, iterAttrV->second));
				
				findFieldBound(iterIdK->second, _T("AIPI_ID"), iterAttrV->second, _T("AIPI_AT"));			
			}
		
			for( iterValV = pMainFrame->gmmVar_Val.begin(); iterValV!= pMainFrame->gmmVar_Val.end(); ++iterValV)
			{
				pMainFrame->mmBindCond.insert(CMainFrame::m_mmBindCond::value_type(iterIdK->second, iterValV->second));
				
				findFieldBound(iterIdK->second, _T("AIPI_ID"), iterValV->second, _T("AIPI_VL"));			
			}
		}
	}


	if(sizeAttr > 0)
	{
		for( iterAttrK = pMainFrame->gmmConst_Attr.begin(); iterAttrK!= pMainFrame->gmmConst_Attr.end(); ++iterAttrK)
		{
			for( iterIdV = pMainFrame->gmmVar_Id.begin(); iterIdV!= pMainFrame->gmmVar_Id.end(); ++iterIdV)
			{
				
				pMainFrame->mmBindCond.insert(CMainFrame::m_mmBindCond::value_type(iterAttrK->second, iterIdV->second));
				
				findFieldBound(iterAttrK->second, _T("AIPI_AT"), iterIdV->second, _T("AIPI_ID"));			
			}
			for( iterValV = pMainFrame->gmmVar_Val.begin(); iterValV!= pMainFrame->gmmVar_Val.end(); ++iterValV)
			{
				
				pMainFrame->mmBindCond.insert(CMainFrame::m_mmBindCond::value_type(iterAttrK->second, iterValV->second));
				
				findFieldBound(iterAttrK->second, _T("AIPI_AT"), iterValV->second, _T("AIPI_VL"));			
			}	
		}
	}


	if( sizeVal > 0 )
	{
		for( iterValK = pMainFrame->gmmConst_Val.begin(); iterValK!= pMainFrame->gmmConst_Val.end(); ++iterValK)
		{
			for( iterIdV = pMainFrame->gmmVar_Id.begin(); iterIdV!= pMainFrame->gmmVar_Id.end(); ++iterIdV)
			{
				pMainFrame->mmBindCond.insert(CMainFrame::m_mmBindCond::value_type(iterValK->second, iterIdV->second));
				
				findFieldBound(iterValK->second, _T("AIPI_VL"), iterIdV->second, _T("AIPI_ID"));			
			}
		
			for( iterAttrV = pMainFrame->gmmVar_Attr.begin(); iterAttrV!= pMainFrame->gmmVar_Attr.end(); ++iterAttrV)
			{
				pMainFrame->mmBindCond.insert(CMainFrame::m_mmBindCond::value_type(iterValK->second, iterAttrV->second));
				
				findFieldBound(iterValK->second, _T("AIPI_VL"), iterAttrV->second, _T("AIPI_AT"));			
			}
		}
	}

	//unique_copy(vBindCond.begin(), vBindCond.end(), back_inserter(pMainFrame->g_vDistBindCond));

}

*/


/*
int CAipi_RETE_Network::assertLeftActivation(int b1, int b2, int w2, int f1, int f2, int j)
{
		
		CAipi_RETE_TK tk;
		CAipi_RETE_JNode jn;
		CAipi_RETE_NNode nn;
		
		int result = 0;
		int w1 = NOT_FOUND;
		//AfxMessageBox(_T("Entro1"));


		if( b1 == 0 )
		{
			
			int newTK = tk.generateTKKey();
			int c2 = jn.findJNCond2(j);
			int not = nn.findCond_NN(c2);
			if( not != NOT_FOUND)
			{
				AfxMessageBox(_T("Entro NOT"));
				tk.createTK(newTK, DNode, w2, b2, NEGATIVE);
				nn.addNN_TK(b2, newTK);
			}
			else
			{
				tk.createTK(newTK, DNode, w2, b2, POSITIVE);	
				
			
			CString str;
			AfxMessageBox(_T("Left ACTIVATION"));
			str.Format(_T("JN...%d  " ), j);
			AfxMessageBox(str);
			
			str.Format(_T("C2...%d  " ), c2);
			AfxMessageBox(str);
			str.Format(_T("TK...%d  " ), newTK);
			AfxMessageBox(str);
			
				
			}
			
			tk.addWM_ChildTK(w2, newTK);
			CAipi_RETE_BM bm;
			int t = bm.findBMParentTK(b2);
			
			
			CString str;
			AfxMessageBox(_T("Left ACTIVATION"));
			str.Format(_T("BM...%d  " ), b1);
			AfxMessageBox(str);
			str.Format(_T("TK...%d  " ), t);
			AfxMessageBox(str);
			

			switch(t)
			{
				case NNode:
					//Do nothing	
				break;
				case EMPTY:
					bm.editBM_TK(b2, newTK);
				break;
				default:
					bm.addBM_TK(b2, newTK);
				break;

			}	

		}
				
		
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

		
		CMainFrame::g_mmBM_TK::iterator it_BM;
		pair <CMainFrame::g_mmBM_TK::iterator, CMainFrame::g_mmBM_TK::iterator>  pBM;
		pBM = pMainFrame->gmmBM_TK.equal_range(b1);

			for(it_BM = pBM.first; it_BM != pBM.second; ++it_BM)
			{
				int t = it_BM->second;
				int w1 =  tk.findWMTK(t);
				
				
				
				CString str;
				str.Format(_T("Token ...%d  " ), t);
				AfxMessageBox(str);
				str.Format(_T("WM1...%d  " ), w1);
				AfxMessageBox(str);
				str.Format(_T("BM1...%d  " ), b1);
				AfxMessageBox(str);
				
				
						
				int r = assertUpdate(b1, b2, w1, w2, f1, f2, j);
				if( r == 1 )
				{
					result = 1;
				}

			}
		

	
return result;

}

*/


/*
int CAipi_RETE_Network::saveChildJN(int b1, int j)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	RETE_JN jn;
	int r = 0;
	
	
		int nj = jn.countBMChildJN(b1);
		if( nj > 1)
		{
			CMainFrame::g_mmBM_ChildJN::iterator iterChild;
			pair <CMainFrame::g_mmBM_ChildJN::iterator, CMainFrame::g_mmBM_ChildJN::iterator>  pChild;
			pChild = pMainFrame->gmmBM_ChildJN.equal_range(b1);
			for(iterChild = pChild.first; iterChild != pChild.second; ++iterChild)
			{	
					pMainFrame->g_vBMChildJN.push_back(iterChild->second);
					r = 1;
					
					CString str;
					str.Format(_T("Saved Child JN...%d  " ), iterChild->second);
					AfxMessageBox(str);
					
	
				
			}
		}
	
	

	if( r == 1 )
	{
		pMainFrame->g_vBMChildJN.erase
		(
			remove(pMainFrame->g_vBMChildJN.begin(), pMainFrame->g_vBMChildJN.end(), j ), 
			pMainFrame->g_vBMChildJN.end()
		);

		
		CString str;
		str.Format(_T("Erase JN...%d  " ), j);
		AfxMessageBox(str);
		
	}

	

return r;


}

*/

int CAipi_RETE_Network::saveChildJN(int b1, int j)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_RETE_JNode jn;
	int r = 0;
	
	m_mmBM_ChildJN::iterator iter;
    int nj = mmmBM_ChildJN.count(b1);
	
		
		if( nj > 1)
		{
			m_mmBM_ChildJN::iterator iterChild;
			pair <m_mmBM_ChildJN::iterator, m_mmBM_ChildJN::iterator>  pChild;
			pChild = mmmBM_ChildJN.equal_range(b1);
			for(iterChild = pChild.first; iterChild != pChild.second; ++iterChild)
			{	
					pMainFrame->g_vBMChildJN.push_back(iterChild->second);
					r = 1;
					
					
					CString str;
					str.Format(_T("Saved Child JN...%d  " ), iterChild->second);
					AfxMessageBox(str);
					
	
				
			}
		}
	
	

	if( r == 1 )
	{
		pMainFrame->g_vBMChildJN.erase
		(
			remove(pMainFrame->g_vBMChildJN.begin(), pMainFrame->g_vBMChildJN.end(), j ), 
			pMainFrame->g_vBMChildJN.end()
		);

		eraseChildJN(b1, j);

		CString str;
		str.Format(_T("Erase JN...%d  " ), j);
		AfxMessageBox(str);

		
	}

	

return r;

}



void CAipi_RETE_Network::copyBM_ChildJN()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	for( CMainFrame::g_mmBM_ChildJN::const_iterator iter = pMainFrame->gmmBM_ChildJN.begin(); iter!= pMainFrame->gmmBM_ChildJN.end(); ++iter)
	{
		mmmBM_ChildJN.insert(m_mmBM_ChildJN::value_type(iter->first, iter->second));			
	}
}




int CAipi_RETE_Network::eraseChildJN(int b, int j)
{
	//CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	
	m_mmBM_ChildJN::iterator iterBM;
	pair <m_mmBM_ChildJN::iterator, m_mmBM_ChildJN::iterator>  pBM;
	pBM = mmmBM_ChildJN.equal_range(b);
			
	for(iterBM = pBM.first; iterBM != pBM.second; ++iterBM)
	{	
		
		if( iterBM->second == j )
		{
			mmmBM_ChildJN.erase(iterBM);
			return iterBM->first;
			
			
		}
		
	}

return NOT_FOUND;
	
}


/*
int CAipi_RETE_Network::assertRightActivation(int w2, CAipi_RETE_AM am, CAipi_RETE_JNode jn, CAipi_RETE_BM bm, CAipi_RETE_TK tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	copyBM_ChildJN();

	CAipi_RETE_NNode nn;
	CAipi_RETE_Cond co;
	CAipi_RETE_Node node;

	typedef std::set<int> m_mJoin;
	m_mJoin	mJoin;
	m_mJoin::iterator it_J;

	typedef std::set<int> m_mCond;
	m_mCond	mCond;
	m_mCond::iterator it_C;


	am.insertWM(w2);

	int tempChildJN = 0;
	m_CurrentChildJN = 0;
	
	
CMainFrame::g_mmWM_AM::iterator it_WM;
pair <CMainFrame::g_mmWM_AM::iterator, CMainFrame::g_mmWM_AM::iterator>  pWM;
pWM = pMainFrame->gmmWM_AM.equal_range(w2);

	
for(it_WM = pWM.first; it_WM != pWM.second; ++it_WM)
{
	
		int a = it_WM->second;
		
		
		CString str;
		str.Format(_T("AM...%d  " ), a);
		AfxMessageBox(str);
		
	

	CMainFrame::g_mmAM_Cond::iterator it_AM;
	pair <CMainFrame::g_mmAM_Cond::iterator, CMainFrame::g_mmAM_Cond::iterator>  pAM;
		
	pAM = pMainFrame->gmmAM_Cond.equal_range(a);

	for(it_AM = pAM.first; it_AM != pAM.second; ++it_AM)
	{	
		int r = 0;	
		
		
		int c2 = it_AM->second;
		
		CString str;
		str.Format(_T("AM Condition...%d  " ), c2);
		AfxMessageBox(str);
		

		if( mCond.size() > 0 )
		{
			for (it_C = mCond.begin(); it_C != mCond.end(); ++it_C) 
			{
				if(*it_C == c2)
				{
					r = REPEATED;
				}
			}

			if( r == REPEATED )
			{
				//AfxMessageBox(_T("C Repetido"));
				continue;
			}	
		}

		mCond.insert(m_mCond::value_type(c2));
		
		
	
		int j = co.findCond2JN(c2);

		
		str.Format(_T("Join Node 1...%d  " ), j);
		AfxMessageBox(str);
		
		
		jn.findJNMembers(j);
		node.findNodeMembers(j);
		
		if( j == NOT_FOUND )
		{
			int not = nn.findCond_NN(c2);
			if( not != NOT_FOUND )
			{
				int newTK = tk.generateTKKey();
				tk.createTK(m_NewTK, DNode, w2, node.m_Child, NEGATIVE);
				nn.addNN_TK(not, m_NewTK);
				tk.addWM_ChildTK(w2, m_NewTK);
				nn.addWM_NN(w2, not);
				continue;
				//tk.addTkChildParent(DN, newTK);
			}
			else
			{
				continue;
			}
		}

		
			
	
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  SET J Node  *******"));
 
		for (iter = mJoin.begin(); iter != mJoin.end(); ++iter) 
		{
			TCHAR buffer[10];
			CString strPos = _T("R JN");   
			strPos +=  _itot( *iter, buffer, 10 ); 
			//pMainFrame->m_wndOutputTabView.AddMsg1(strPos);
			AfxMessageBox(strPos);
		}

		
		if( mJoin.size() > 0 )
		{
			for (it_J = mJoin.begin(); it_J != mJoin.end(); ++it_J) 
			{
				if(*it_J == j)
				{
					r = REPEATED;
				}
			}

			if( r == REPEATED )
			{
				//AfxMessageBox(_T("JN Repetido"));
				continue;
			}	
		}
		
		
		
		mJoin.insert(m_mJoin::value_type(j));
		
		int f1 = jn.m_Field1;
		//str.Format(_T("Field1...%d  " ), f1);
		//AfxMessageBox(str);
	
		int f2 = jn.m_Field2;
		//str.Format(_T("Field2...%d  " ), f2);
		//AfxMessageBox(str);
		

		int b1 = node.m_Parent;
		str.Format(_T("JN1 BM1...%d  " ), b1);
		AfxMessageBox(str);
	

		int b2 = node.m_Child;
		str.Format(_T("JN1 BM2...%d  " ), b2);
		AfxMessageBox(str);

		
		
		str.Format(_T("W2...%d  " ), w2);
		AfxMessageBox(str);
	
		assertLeftActivation(b1, b2, w2, f1, f2, j);

		
		m_CurrentChildJN = saveChildJN(b1, j);
		 
		
		 CString str;
		 str.Format(_T("SAVE 1...%d  " ), m_CurrentChildJN);
		 AfxMessageBox(str);
			
		

		do
		{
			
			//j = jn.searchJNCond1(c2);
			j = co.findCond1JN(c2);
					
			
			CString str;
			str.Format(_T("Join Node 2...%d  " ), j);
			AfxMessageBox(str);
			
			
		
			if( j != NOT_FOUND )
			{
				//str.Format(_T("ALPHA M Condition...%d  " ), c2);
				//AfxMessageBox(str);
				
				jn.findJNMembers(j);
						
				int f1 = jn.m_Field1;
				//CString str;
				//str.Format(_T("Field1...%d  " ), f1);
				//AfxMessageBox(str);
	
				int f2 = jn.m_Field2;
				//str.Format(_T("Field2...%d  " ), f2);
				//AfxMessageBox(str);
	

				int b1 = node.m_Parent;
				str.Format(_T("JN2 BM1...%d  " ), b1);
				AfxMessageBox(str);
	

				int b2 = node.m_Child;
				str.Format(_T("JN2 BM2...%d  " ), b2);
				AfxMessageBox(str);
				
									

				c2 = jn.m_Cond2;
				mCond.insert(m_mCond::value_type(c2));

				str.Format(_T("ALPHA M Condition...%d  " ), c2);
				AfxMessageBox(str);

				
				int a = am.findCond_AM(c2);
				str.Format(_T("ALPHA M...%d  " ), a);
				AfxMessageBox(str);
				
				

		
				CMainFrame::g_mmAM_WM::iterator iterAM;
				pair <CMainFrame::g_mmAM_WM::iterator, CMainFrame::g_mmAM_WM::iterator>  pAM;
				pAM = pMainFrame->gmmAM_WM.equal_range(a);

						
				for(iterAM = pAM.first; iterAM != pAM.second; ++iterAM)
				{	
					
					

					int w2 = iterAM->second;
					int not = nn.findWM_NN(w2);
					if( not != NOT_FOUND )
					{
						int found = nn.findCond_NN(c2);
						if( found != NOT_FOUND)
						{
							continue;
						}
					}
				
					int t = bm.searchWMTK(b2, w2);



					
					CString str;
					str.Format(_T("W2...%d  " ), w2);
					AfxMessageBox(str);
					
					str.Format(_T("TK...%d  " ), t);
					AfxMessageBox(str);
					

					if(t == NOT_FOUND)
					{
						assertLeftActivation(b1, b2, w2, f1, f2, j );
					}
										
					
				}

					tempChildJN = saveChildJN(b1, j);
					if( tempChildJN == 1 )
					{
						m_CurrentChildJN = 1;
					}
					
					
					CString str;
					str.Format(_T("SAVE 2...%d  " ), m_CurrentChildJN);
					AfxMessageBox(str);
					
								 
				

			}
			

		}while( j != NOT_FOUND );
		
		
	}
	
}

	
	if( m_CurrentChildJN == 1 )
	{
		AfxMessageBox(_T("Assert Child"));
		assertChildJN();
	}

return 1;
}

*/


/*
int CAipi_RETE_Network::assertChildJN()
{
	CAipi_RETE_JNode jn;
	CAipi_RETE_AM am;
	CAipi_RETE_BM bm;
	CAipi_RETE_NNode nn;
	CAipi_RETE_Node node;
	
	int tempChildJN = 0;
	m_CurrentChildJN = 0;
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int size = pMainFrame->g_vBMChildJN.size();
	
	CString str;
	for(int i= 0; i<size; ++i)	
	{
		
		int j = pMainFrame->g_vBMChildJN.at(i);
		//str.Format(_T("Assert JN...%d  " ), j);
		//AfxMessageBox(str);
		int not = nn.findNN_TK(j);
		if ( not != NOT_FOUND )
		{
			//AfxMessageBox(_T("Entro3"));
			continue;
		}

		jn.findJNMembers(j);
		node.findNodeMembers(j);

		int f1 = jn.m_Field1;
		//str.Format(_T("Field1...%d  " ), f1);
		//AfxMessageBox(str);
	
		int f2 = jn.m_Field2;
		//str.Format(_T("Field2...%d  " ), f2);
		//AfxMessageBox(str);
		

		int b1 = node.m_Parent;
		//str.Format(_T("JN BM1...%d  " ), b1);
		//AfxMessageBox(str);
	

		int b2 = node.m_Child;
		//str.Format(_T("JN BM2...%d  " ), b2);
		//AfxMessageBox(str);

		int c2 = jn.m_Cond2;
		//str.Format(_T("JN C2...%d  " ), c2);
		//AfxMessageBox(str);

		int a = am.findCond_AM(c2);
		//str.Format(_T("ALPHA M...%d  " ), a);
		//AfxMessageBox(str);
	
		CMainFrame::g_mmAM_WM::iterator iterAM;
		pair <CMainFrame::g_mmAM_WM::iterator, CMainFrame::g_mmAM_WM::iterator>  pAM;
		pAM = pMainFrame->gmmAM_WM.equal_range(a);

		for(iterAM = pAM.first; iterAM != pAM.second; ++iterAM)
		{	
			int w2 = iterAM->second;
			
			int t = bm.searchWMTK(b2, w2);
			
			
			CString str;
			str.Format(_T("W2...%d  " ), w2);
			AfxMessageBox(str);
			
			
			if(t == NOT_FOUND)
			{
				assertLeftActivation(b1, b2, w2, f1, f2, j );
			}
		}

			
		
		
		do
		{
			
			j = jn.searchJNCond1(c2);
		
					
			CString str;
			str.Format(_T("Join Node2...%d  " ), j);
			AfxMessageBox(str);
			
		   
			if( j != NOT_FOUND )
			{
				jn.findJNMembers(j);
						
				int f1 = jn.m_Field1;
				//CString str;
				//str.Format(_T("Field1...%d  " ), f1);
				//AfxMessageBox(str);
	
				int f2 = jn.m_Field2;
				//str.Format(_T("Field2...%d  " ), f2);
				//AfxMessageBox(str);
	

				int b1 = node.m_Parent;
				//str.Format(_T("JN BM1...%d  " ), b1);
				//AfxMessageBox(str);
	

				int b2 = node.m_Child;
				//str.Format(_T("JN BM2...%d  " ), b2);
				//AfxMessageBox(str);

						

				c2 = jn.m_Cond2;
				//str.Format(_T("ALPHA M Condition...%d  " ), c2);
				//AfxMessageBox(str);

				int a = am.findCond_AM(c2);
				//str.Format(_T("ALPHA M...%d  " ), a);
				//AfxMessageBox(str);
	

		
				CMainFrame::g_mmAM_WM::iterator iterAM;
				pair <CMainFrame::g_mmAM_WM::iterator, CMainFrame::g_mmAM_WM::iterator>  pAM;
				pAM = pMainFrame->gmmAM_WM.equal_range(a);

						
				for(iterAM = pAM.first; iterAM != pAM.second; ++iterAM)
				{	
					int w2 = iterAM->second;
					int t = bm.searchWMTK(b2, w2);
					if(t == NOT_FOUND)
					{
						assertLeftActivation(b1, b2, w2, f1, f2, j );
					}
										
					
				}

					
					tempChildJN = saveChildJN(b1, j);
					if( tempChildJN == 1 )
					{
						m_CurrentChildJN = 1;
					}	
					
					
					CString str;
					str.Format(_T("SAVE 3...%d  " ), m_CurrentChildJN);
					AfxMessageBox(str);
					
				

			}
			

		}while( j != NOT_FOUND);
	}	


	if( m_CurrentChildJN == 1)
	{
		
		assertChildJN();
	}


return 1;

}

*/





/*

void CAipi_RETE_Network::assertWME(int w2, RETE_AM am, RETE_JN jn, RETE_BM bm, RETE_Token tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	typedef std::set<int> m_mJoin;
	m_mJoin	mJoin;
	m_mJoin::iterator iter;


	int a = am.addWME(w2);
	int r = 0;
	
	CString str;
	str.Format(_T("AM...%d  " ), a);
	AfxMessageBox(str);
	
	
	CMainFrame::g_mmAMCond::iterator it_AM;
	pair <CMainFrame::g_mmAMCond::iterator, CMainFrame::g_mmAMCond::iterator>  pAM;
		
	pAM = pMainFrame->gmmAMCond.equal_range(a);

	for(it_AM = pAM.first; it_AM != pAM.second; ++it_AM)
	{	
		int c2 = it_AM->second;
		str.Format(_T("AM Condition...%d  " ), c2);
		AfxMessageBox(str);
	
		int j = jn.findNodeCond_JN(c2);
		str.Format(_T("Condition Join Node...%d  " ), j);
		AfxMessageBox(str);

		jn.findJN(j);
			
	
		
		
		if( mJoin.size() > 0 )
		{
			for (iter = mJoin.begin(); iter != mJoin.end(); ++iter) 
			{
				if(*iter == j)
				{
					r = REPEATED;
				}
			}

			if( r == REPEATED )
			{
				AfxMessageBox(_T("Repetido"));
				continue;
			}	
		}
		
		
		
		mJoin.insert(m_mJoin::value_type(j));
		
		int c1 = jn.m_Cond1;
		str.Format(_T("JN C1...%d  " ), c1);
		AfxMessageBox(str);
	
			

		int b1 = jn.m_BM1;
		str.Format(_T("JN BM1...%d  " ), b1);
		AfxMessageBox(str);
	

		int b2 = jn.m_BM2;
		str.Format(_T("JN BM2...%d  " ), b2);
		AfxMessageBox(str);
	
		
		
		CMainFrame::g_mmBM::iterator it_BM;
		pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
		
		pBM = pMainFrame->gmmBM.equal_range(b1);

		for(it_BM = pBM.first; it_BM != pBM.second; ++it_BM)
		{
			int t = it_BM->second;
			str.Format(_T("Token BM1...%d  " ), t);
			AfxMessageBox(str);

			int w1 =  tk.getKeyWME(t);
			str.Format(_T("WM1...%d  " ), w1);
			AfxMessageBox(str);

			
			assertBindCond(b1, b2, w1, w2, c1, c2);
			

		}
		
	}
			
}

*/



/*
void CAipi_RETE_Network::removeWMERematch(int w2, RETE_AM am, RETE_JN jn, RETE_BM bm, RETE_Token tk)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	int a = am.findAMWME(w2);
	CString str;
	str.Format(_T("AM...%d  " ), a);
	AfxMessageBox(str);
	
	am.eraseAME(a, w2);
	
	
	
	CMainFrame::g_mmAMCond::iterator it_AM;
	pair <CMainFrame::g_mmAMCond::iterator, CMainFrame::g_mmAMCond::iterator>  pAM;
		
	pAM = pMainFrame->gmmAMCond.equal_range(a);

	for(it_AM = pAM.first; it_AM != pAM.second; ++it_AM)
	{	
		int c2 = it_AM->second;
		//str.Format(_T("AM Condition...%d  " ), c);
		//AfxMessageBox(str);
	
		int j = jn.findNodeCond_JN(c2);
		//str.Format(_T("Condition Join Node...%d  " ), j);
		//AfxMessageBox(str);
	
		
		jn.findJN(j);
		
		int c1 = jn.m_Cond1;
		
		//str.Format(_T("JN C1...%d  " ), c1);
		//AfxMessageBox(str);
	
		//int c2 = jn.m_Cond2;
		
		//str.Format(_T("JN C2...%d  " ), c2);
		//AfxMessageBox(str);
	

		int b1 = jn.m_BM1;
		//str.Format(_T("JN BM1...%d  " ), bm1);
		//AfxMessageBox(str);
	

		int b2 = jn.m_BM2;
		//str.Format(_T("JN BM2...%d  " ), bm2);
		//AfxMessageBox(str);
	
		
		int r,t =0;
		
		CMainFrame::g_mmBM::iterator it_BM1;
		pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM1;
		
		pBM1 = pMainFrame->gmmBM.equal_range(b1);

		for(it_BM1 = pBM1.first; it_BM1 != pBM1.second; ++it_BM1)
		{
			t = it_BM1->second;
			//str.Format(_T("Token BM1...%d  " ), tk1);
			//AfxMessageBox(str);

			int w1 =  tk.getKeyWME(t);
			//str.Format(_T("WM1...%d  " ), w1);
			//AfxMessageBox(str);

			
			r = removeBindCond(b1, b2, w1, w2, c1, c2);
			if ( r == 1 )
			{
				CMainFrame::g_mmBM::iterator it_BM2;
				pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM2;
				pBM2 = pMainFrame->gmmBM.equal_range(b2);
				for(it_BM2 = pBM2.first; it_BM2 != pBM2.second; ++it_BM2)
				{
					t = it_BM2->second;
					AfxMessageBox(_T("entro"));
					if( it_BM2->second == t )
					{
						CString str;
						str.Format(_T("Token ...%d  " ), t);
						AfxMessageBox(str);
						pMainFrame->gmmBM.erase(it_BM2++);
					}
					else
					{
						++it_BM2;
					}
				}
			}
			
		}

	
	}

	
			
}

*/


void CAipi_RETE_Network::removeWMEScan(int w2, CAipi_RETE_AM am, CAipi_RETE_BM bm, CAipi_RETE_TK tk, CAipi_WM wm, CAipi_RETE_NNode nn)
{
	int n = tk.countWM(w2);
	
	if( n > 0 )
	{
		for(int i= 0; i< n; ++i)
		{
			removeScanTk(w2, am, bm, tk, wm, nn);
		}
	}
	


}



void CAipi_RETE_Network::removeWMETree(int w2, CAipi_RETE_AM am, CAipi_RETE_BM bm, CAipi_RETE_TK tk, CAipi_WM wm, CAipi_RETE_NNode nn)
{
	//int n = tk.countKeyWME(w2);
	int n = tk.countWM_ParentTK(w2);
	if( n > 0 )
	{
		for(int i= 0; i< n; ++i)
		{
			removeTreeTk(w2, am, bm, tk, wm, nn);
		}
	}
	
	int a = 0;
	do
	{
		a = am.findWM_AM(w2);
		if( a != NOT_FOUND )
		{
			am.eraseItemAM_WM(a, w2);
		}
	}while( a != NOT_FOUND );

	wm.eraseWM(w2);
	am.eraseWM_AM(w2);
	nn.eraseWM_NN(w2);

}

void CAipi_RETE_Network::removeScanTk(int w2, CAipi_RETE_AM am, CAipi_RETE_BM bm, CAipi_RETE_TK tk, CAipi_WM wm, CAipi_RETE_NNode nn)
{

	int t, a = 0;
	vector <int> vToken;
	
	t = tk.searchTKWM(w2);
	vToken.push_back(t);
	//CString str;
	//str.Format(_T("Token...%d  " ), t);
	//AfxMessageBox(str);
	
	if( t != NOT_FOUND )
	{
		do
		{
			t = tk.searchTKChildTK(t);
			if( t != NOT_FOUND )
			{
				vToken.push_back(t);
				
					//CString str;
					//str.Format(_T("Key Token...%d  " ), t);
					//AfxMessageBox(str);
			}
		}while( t != NOT_FOUND );
	}	


	for(int i=0; i<vToken.size();++i)
	{
		
		CString str;
		//str.Format(_T("Token at...%d  " ), i);
		//AfxMessageBox(str);
		
		int t = vToken.at(i);
		
		//str.Format(_T("Token = ...%d  " ), vToken.at(i));
		//AfxMessageBox(str);
		
		int b = bm.searchBMParentTK(t);
		if( b != NOT_FOUND )
		{
			bm.eraseItemBM_ParentTK(b, t);
			tk.eraseTK(t);
		}

		int not = nn.searchNN_TK(t);
		if( not != NOT_FOUND )
		{
			nn.eraseItemNN_TK(not, t);
			tk.eraseTK(t);
		}
	}
	

	
	do
	{
		a = am.findWM_AM(w2);
		if( a != NOT_FOUND )
		{
			am.eraseItemAM_WM(a,w2);
		}
	}while( a != NOT_FOUND );


	wm.eraseWM(w2);
	nn.eraseWM_NN(w2);



}




void CAipi_RETE_Network::removeTreeTk(int w2, CAipi_RETE_AM am, CAipi_RETE_BM bm, CAipi_RETE_TK tk, CAipi_WM wm, CAipi_RETE_NNode nn)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	int t = tk.findWM_ChildTK(w2);
	
	/*
	CString str;
	str.Format(_T("Token...%d  " ), t);
	AfxMessageBox(str);
	*/
	
	CMainFrame::g_mmTKParent_TKLink::iterator it_List;
	pair <CMainFrame::g_mmTKParent_TKLink::iterator, CMainFrame::g_mmTKParent_TKLink::iterator>  pList;
	pList = pMainFrame->gmmTKParent_TKLink.equal_range(t);
	
	for(it_List = pList.first; it_List != pList.second; ++it_List)
	{
		/*
		CString str;
		str.Format(_T("Child Token...%d  " ), it_List->second);
		AfxMessageBox(str);
		*/
		int chdTk = it_List->second;
		
		int b = bm.searchBMParentTK(chdTk);
		if( b != NOT_FOUND )
		{
			bm.eraseItemBM_ParentTK(b, chdTk);
			tk.eraseTK(chdTk);

			if( bm.countBM(b) == 0 )
			{
				//bm.addBM_TK(b, EMPTY);
			}
		}
		
		int not = nn.searchNN_TK(chdTk);
		if( not != NOT_FOUND )
		{
			nn.eraseItemNN_TK(not, chdTk);
			tk.eraseTK(chdTk);
		}

		
		/*
		CString str;
		str.Format(_T("BM...%d  " ), b);
		AfxMessageBox(str);
		*/
	}
	
	int b = bm.searchBMParentTK(t);
	if( b != NOT_FOUND )
	{
		bm.eraseItemBM_ParentTK(b, t);
		tk.eraseTK(t);
		if( bm.countBM(b) == 0 )
		{
				//bm.addBM_TK(b, EMPTY);
		}
	}
	int not = nn.searchNN_TK(t);
	if( not != NOT_FOUND )
	{
		nn.eraseItemNN_TK(not, t);
		tk.eraseTK(t);
	}	

	
	
	
	

	

	
	
	tk.eraseWMChildTKE(w2, t);
	

}



void CAipi_RETE_Network::addNewProduction(int p)
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CAipi_RETE_AM am;
	CAipi_PM pm;
	CAipi_RETE_BM bm;

	int b1 = bm.lastBM();

	pm.addPM_Name(6,_T("Reglas 6"));

	CMainFrame::g_mmPM_Cond::iterator it_PM;
	pair <CMainFrame::g_mmPM_Cond::iterator, CMainFrame::g_mmPM_Cond::iterator>  pPM;
		
	pPM = pMainFrame->gmmPM_Cond.equal_range(p);

	
	for(it_PM = pPM.first; it_PM != pPM.second; ++it_PM)
	{	
		am.constantTestCond(it_PM->second);
		
	}
	
	//am.addWMEsNewPM();
	//am.insertAllWM();
	 am.insertStructsWM_AM();	

	checkRepeatedCond(p);
	CAipi_RETE_TK tk;
	tk.clearTKParent_TKLink();
	tk.createTKParent_TKLink();

/*
	int b2 = bm.getLastBMKey();

	if ( b1 < b2 )
	{
		RETE_Token tk;
		CMainFrame::g_mmBM::iterator it_BM;
		pair <CMainFrame::g_mmBM::iterator, CMainFrame::g_mmBM::iterator>  pBM;
		
		
		for(int i = b1  + 1; i<= b2; ++i)
		{
			pBM = pMainFrame->gmmBM.equal_range(i);
			for(it_BM = pBM.first; it_BM != pBM.second; ++it_BM)
			{	
				int t= it_BM->second;
				do
				{
					t = tk.searchParent(t);
		
					if( t != NOT_FOUND )
					{
						tk.addTkChildList(it_BM->second, t);
			
						
						CString str;
						str.Format(_T("Key Token...%d  " ), it_BM->first);
						AfxMessageBox(str);
						str.Format(_T("Parent Token...%d  " ), t);
						AfxMessageBox(str);
					

					}

				}while( t != NOT_FOUND );
			
			}
		}

	}
*/


}


void CAipi_RETE_Network::eraseOldProduction(int p)
{
	/*
	CAipi_RETE_PNode pn;
	CAipi_RETE_AM am;
	CAipi_RETE_BM bm;
	CAipi_PM pm;
	CAipi_RETE_JNode jn;
	CAipi_RETE_TK tk;
	CAipi_RETE_NNode nn;
	CAipi_RETE_Cond co;
	CAipi_RETE_Node node;

	bool stop = false; 
	int n = 0;

	

	pn.searchPNode(p);

	int c1 = pn.m_C1;
	int c2 = pn.m_C2;
	int b1 = pn.m_BM1;
	int b2 = pn.m_BM2;
	int j =  pn.m_JN;
	int type = pn.m_Type;


	CString str;
	str.Format(_T("Conditon 1 ...%d  " ), c1);
	AfxMessageBox(str);
	str.Format(_T("Conditon 2 ...%d  " ), c2);
	AfxMessageBox(str);
	str.Format(_T("Beta Memory 1 ...%d  " ), b1);
	AfxMessageBox(str);
	str.Format(_T("Beta Memory 2 ...%d  " ), b2);
	AfxMessageBox(str);
	str.Format(_T("Join Node ...%d  " ), j);
	AfxMessageBox(str);
	
	
	
	
	int a = am.findCond_AM(c2);

	
	str.Format(_T("Alpha Memory ...%d  " ), a);
	AfxMessageBox(str);
	
	
	
	n = am.countAM_Cond(a);

	str.Format(_T("Number Condition of AM ...%d  " ), n);
	AfxMessageBox(str);
	
	
	if ( n == 1 )
	{
		am.eraseAM_Cond(a);
		am.eraseAM_WM( a);
		
	}
	
	
	bm.eraseTKStructs(b2);
	bm.eraseBM(b2);

	int not = nn.findCond_NN(c2);
	if( not != NOT_FOUND)
	{
		str.Format(_T("Number Joins in NOT Condition...%d  " ), not);
		AfxMessageBox(str);

		nn.eraseTK(not);
		nn.eraseNN_TK(not);
	}
	
	
		
	
	n = jn.countBM_ChildJN(b1);
	
	str.Format(_T("Number Joins in BM1 ...%d  " ), n);
	AfxMessageBox(str);

	
	if( n > 1 )
	{
		jn.eraseJN(j);
		co.eraseCond2(c2);
		co.eraseCond1(c1);
		bm.eraseItemBM_ChildJN(b1, j);

		if( not != NOT_FOUND )
		{
			nn.eraseCond_NN(c2);
		}

		//stop = true;
		return;
	}
	else if( n == 1 )
	{
		bm.eraseTKStructs(b1);
		bm.eraseBM(b1);

		nn.eraseTK(b1);
		nn.eraseNN_TK(b1);
	
		jn.eraseJN(j);
		co.eraseCond2(c2);
		co.eraseCond1(c1);
		bm.eraseBM_ChildJN(b1);

		nn.eraseCond_NN(c2);
		nn.eraseNN(b1);
	}

	c2 = c1;
	
	do
	{
		
		j = jn.searchJNCond2(c2);
		not = nn.findCond_NN(c2);
		
		
		CString str;
		str.Format(_T("Join Node1...%d  " ), j);
		AfxMessageBox(str);
		str.Format(_T("Join Negated Condition...%d  " ), not);
		AfxMessageBox(str);
		


		if( j != NOT_FOUND )
		{
			jn.findJNMembers(j);
			node.findNodeMembers(j);

			c1 = jn.m_Cond1;
		
			str.Format(_T("C1...%d  " ), c1);
			AfxMessageBox(str);
		

			c2 = jn.m_Cond2;
			
			str.Format(_T("C2...%d  " ), c2);
			AfxMessageBox(str);
		
			
			b1 = node.m_Parent;
		
			str.Format(_T("BM1...%d  " ), b1);
			AfxMessageBox(str);
		
			
			b2 = node.m_Child;
		
			str.Format(_T("BM2...%d  " ), b2);
			AfxMessageBox(str);
		
			
			//type = jn.m_Type;
		
			type = 5;
			str.Format(_T("Join Node Type...%d  " ), type);
			AfxMessageBox(str);
		
			
			int a = am.findCond_AM(c2);
			
			CString str;
			str.Format(_T("Alpha Memory ...%d  " ), a);
			AfxMessageBox(str);
			
			int n = am.countAM_Cond(a);
			
			str.Format(_T("Number Condition of AM ...%d  " ), n);
			AfxMessageBox(str);
		
		   	if ( n == 1 )
			{
				am.eraseAM_Cond(a);
				am.eraseAM_WM( a);
				
			}
			  
			n = jn.countBM_ChildJN(b1);
			
			str.Format(_T("Number Joins in BM1 ...%d  " ), n);
			AfxMessageBox(str);
			

			if( n > 1 )
			{
				jn.eraseJN(j);
				co.eraseCond1(c1);
				co.eraseCond2(c2);
				bm.eraseItemBM_ChildJN(b1, j);

				if( not != NOT_FOUND )
				{
					nn.eraseCond_NN(c2);
				}
				stop = true;
			}
			if( n == 1 )
			{
				AfxMessageBox(_T("Borrar2"));
				bm.eraseTKStructs(b1);
				bm.eraseBM(b1);

				int not = nn.findCond_NN(c2);
				if( not != NOT_FOUND)
				{
					nn.eraseTK(not);
					nn.eraseNN_TK(not);
				}
	
				jn.eraseJN(j);
				co.eraseCond2(c2);
				co.eraseCond1(c1);
				bm.eraseBM_ChildJN(b1);
				
				nn.eraseCond_NN(c2);
				nn.eraseNN(b1);
			}
			
			c2 = c1;
		}

	}while(stop != true && type != DNode );

	am.eraseCondStructs(c2);
	pm.erasePM_Cond(c2);
	
*/	
}





void CAipi_RETE_Network::test()
{
	CPerfTimer T;		
	clear();
	//return;

	CAipi_LHS lhso;
	//lhso.SamplesNegated();
	lhso.SamplesOPS5();
	//lhso.SamplesRETE();
	lhso.printLHS();
	
	CAipi_PM pmo;
	//pmo.printPM_Cond();
	
	CAipi_WM wmo;
	//wmo.SamplesNegated();
	wmo.SamplesOPS5();
	//wmo.SamplesRETE();
	wmo.printWM();
	

	
	CAipi_RETE_AM amo;
	T.Start();
	//amo.createAM();
	StopTimer(T, _T("Time ... "));
	
	amo.printAM_WM();
	amo.printWM_AM();
	amo.printCond_AM();
	amo.printAM_Cond();
	amo.printEQ();
	amo.printET();
	amo.printNE();
	amo.printLT();
	amo.printLE();
	amo.printGT();
	amo.printGE();
	amo.printAS();
/*
	wmo.printEQ_Cond_WM();
	wmo.printNE_Cond_WM();
	wmo.printGE_Cond_WM();
	wmo.printGT_Cond_WM();
	wmo.printLT_Cond_WM();
	wmo.printLE_Cond_WM();
	wmo.printAS_Cond_WM();


	wmo.printEQ_WM_Cond();
	wmo.printNE_WM_Cond();
	wmo.printGE_WM_Cond();
	wmo.printGT_WM_Cond();
	wmo.printLT_WM_Cond();
	wmo.printLE_WM_Cond();
	wmo.printAS_WM_Cond();


	CAipi_RETE_Vars varo;

	varo.printVar_I();
	varo.printVar_A();
	varo.printVar_V();

	pmo.printPM_IDVar();
	pmo.printPM_ATTRVar();
	pmo.printPM_VALVar();
	pmo.printPM_RelCond();
*/	
	
	

T.Start();
	
	CAipi_RETE_Net  net;  
	net.preAnalysis();
	net.createNet();

StopTimer(T, _T("Time ... "));

	lhso.printRepCond();	

	CAipi_RETE_Links lko;
	lko.printCondLink();
		
	CAipi_RETE_TK tko;
	
	tko.printTK();
	tko.printLinkTK();
	tko.printWM_ChildTK();
	//tko.printTKParent_TKChild();
	tko.createTKParent_TKLink();
	//tko.printTKParent_TKLink();

	CAipi_RETE_BM bmo;
	
	bmo.printLinkBM_TK();
	bmo.printBM();
	pmo.printPM_BM();
	
	

	CAipi_RETE_Cond co;
	co.printCond1();
	co.printCond2();
	
	CAipi_RETE_Node no;
	no.printNode();

	CAipi_RETE_JNode jno;
	jno.printJN();
	
	CAipi_RETE_DNode dno;
	dno.printDNode();

	CAipi_RETE_NodeCond nco;
	nco.printNodeCond();

	CAipi_RETE_TypeInt		typei;
	CAipi_RETE_TypeLong		typel;
	CAipi_RETE_TypeFloat	typef;
	CAipi_RETE_TypeDouble   typed;
	CAipi_RETE_TypeString   types;

	typei.printTypeInt();
	typel.printTypeLong();
	typef.printTypeFloat();
	typed.printTypeDouble();
	types.printTypeString();
	
	
	CAipi_RETE_Operations op;
	op.printOperation();
	op.printAttr_Type();


	CAipi_RETE_NumVars num;
	num.printTK_LeftV();
	num.printTK_RightV();
	num.printNumVar_BM();


	
	
/*
	CAipi_RETE_NNode nno;
	nno.printCond_NN();
	nno.printNN();
	nno.printNN_TK();
	nno.printLinkNN_TK();
	nno.printWM_NN();

	CAipi_RETE_NCCNode ncco;
	ncco.printNCCN_BM();
	ncco.printNCCPartnerN_BM();
	ncco.printNCCPartnerN_TK();
	ncco.printLinkNCCPartnerN_TK();
	
	ncco.printNCC();
	ncco.printNCC_Cond();
	ncco.printCond_NCC();

	CAipi_RETE_PN pno;
	pno.printPN();
	pno.printV_FiredPN();
	pno.printMatchedWM();

*/



	/*
	int join = jno.searchJNCond1(9);
	CString str;
	str.Format(_T("Join Node...%d  " ), join);
	AfxMessageBox(str);
  */
	//wmo.addWME(9, _T("block3") ,_T("color") ,_T("red"));
	//wmo.addWME(10, _T("block3") ,_T("color") ,_T("red"));
	//wmo.addWME(11, _T("block2") ,_T("left of") ,_T("block5"));
	
	//wmo.addWME(2, _T("block1") ,_T("color") ,_T("red"));
	
	
	
	
	

	

/*
	wmo.addWME(11, _T("block2") ,_T("left of") ,_T("block3"));
	assertRightActivation(11, am, jn, bm, tk);
	wmo.printWM();
	amo.printAM();
	tko.printToken();
	tko.printTokenF();
	bmo.printBM();
	bmo.printBMF();
*/	

/*
	int j = jno.findNodeCond_JN(2);
	CString str;
	str.Format(_T("JN...%d  " ),j);
	AfxMessageBox(str);
*/
	

/*	
	//Production 5
	lhso.addLHSE(15,_T("[x]") ,_T("up") ,_T("[y]"), 10);
	lhso.addLHSE(16,_T("[y]") ,_T("right of") ,_T("[z]"), 10);
	lhso.addLHSE(17,_T("[z]") ,_T("size") ,_T("10"), 10);
*/	
/*
	lhso.addLHSE(15,_T("[x]") ,_T("on") ,_T("[y]"), 10);
	lhso.addLHSE(16,_T("[y]") ,_T("left of") ,_T("[z]"), 10);
	lhso.addLHSE(17,_T("[z]") ,_T("color") ,_T("red"), 10);
*/
/*
	addNewProduction(10);
	amo.printAM();
	tko.printToken();
	tko.printTokenF();
	bmo.printBM();
	bmo.printBMF();
*/


/*

//Erase P2
	eraseOldProduction(2);
	lhso.printLHS();
	amo.printAM();
	amo.printCondAM();
	amo.printAMCond();
	amo.printEQ();
	tko.printWMToken();
	tko.printToken();
	tko.printTokenF();
	tko.printTkChildParent();
	tko.printTkChildList();
	
	bmo.printBM();
	bmo.printBMF();

	
	jno.printCond1_JN();
	jno.printCond2_JN();
	jno.printJN();
	jno.printBM_ChildJN();


//Add P2
		//Production 6
	lhso.addLHS(14, _T("[x]") ,_T("on") ,_T("[y]"), 6);
	lhso.addLHS(15, _T("[y]") ,_T("left of") ,_T("[z]"), 6);
	lhso.addLHS(16, _T("[z]") ,_T("color") ,_T("blue"), 6);
	lhso.addLHS(17, _T("[z]") ,_T("on") ,_T("table"), 6);
	
	addNewProduction(6);
	lhso.printLHS();
	pmo.printPM_Cond();
	amo.printAM();
	amo.printCondAM();
	amo.printAMCond();
	amo.printEQ();
	tko.printWMToken();
	tko.printToken();
	tko.printTokenF();
	tko.printTkChildParent();
	tko.printTkChildList();
	
	bmo.printBM();
	bmo.printBMF();

	
	jno.printCond2_JN();
	jno.printJN();
	jno.printBM_ChildJN();
*/

	
/*	
	//removeWMETree(5, amo, bmo, tko, wmo, nno);
	//removeWMETree(7, amo, bmo, tko, wmo, nno);
	//removeWMETree(9, amo, bmo, tko, wmo, nno);
	//removeWMETree(10, amo, bmo, tko, wmo, nno);
	removeWMETree(11, amo, bmo, tko, wmo, nno);

	wmo.printWM();
	amo.printAM();
	amo.printWM_AM();
	
	tko.printToken();
	tko.printTokenF();
	bmo.printBM();
	bmo.printBMF();
	//tko.printTkChildParent();
	//tko.printTkChildList();
	

	jno.printCond2_JN();
	jno.printJN();
	jno.printBM_ChildJN();
	nno.printCond_NOT();
	
	nno.printNOTNode();
	nno.printNOT_Token();
	nno.printNOT_TokenF();
	nno.printWM_NOT();



	
	//woo.addWME(5, _T("block2"), _T("left of"),  _T("block3"));
	//assertRightActivation(5, amo, jno, bmo, tko);
	//wmo.addWME(7, _T("block3"), _T("left of"),  _T("block4"));
	//assertRightActivation(7, amo, jno, bmo, tko);
	
	//wmo.addWME(9, _T("block3"), _T("color"),  _T("red"));
	//assertRightActivation(9, amo, jno, bmo, tko);
	//wmo.addWME(10, _T("block4"), _T("color"),  _T("blue"));
	//assertRightActivation(10, amo, jno, bmo, tko);

	wmo.addWME(11, _T("block4"), _T("on"),  _T("table"));
	assertRightActivation(11, amo, jno, bmo, tko);



	wmo.printWM();
	amo.printAM();
	amo.printWM_AM();
	tko.printToken();
	tko.printTokenF();
	bmo.printBM();
	bmo.printBMF();
	jno.printCond1_JN();
	jno.printCond2_JN();
	jno.printJN();
	jno.printBM_ChildJN();
	jno.printVectorBM_ChildJN();

	nno.printCond_NOT();
	nno.printNOTNode();
	nno.printNOT_Token();
	nno.printNOT_TokenF();
	nno.printWM_NOT();

*/
	//clear();

}		