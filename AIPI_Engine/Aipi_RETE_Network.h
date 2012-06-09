// Aipi_RETE_Network.h: interface for the CAipi_RETE_Network class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_NETWORK_H__AB637ADE_262D_47FD_879B_58AC567E4504__INCLUDED_)
#define AFX_AIPI_RETE_NETWORK_H__AB637ADE_262D_47FD_879B_58AC567E4504__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_WM.h"
#include "Aipi_LHS.h"
#include "Aipi_RHS.h"
#include "Aipi_RETE_AM.h"
#include "Aipi_RETE_BM.h"
#include "Aipi_RETE_BME.h"
#include "Aipi_RETE_TK.h"
#include "Aipi_RETE_JNode.h"
#include "Aipi_RETE_PNode.h"
#include "Aipi_RETE_NNode.h"
#include "Aipi_RETE_DNode.h"
#include "Aipi_RETE_NCCNode.h"
#include "Aipi_RETE_NodeCond.h"

#include "Aipi_RETE_Net.h"

#include "../AIPITabView.h"


#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <set>

//This class is a previous version of the RETE Net..
//It is no longer used


class CAipi_RETE_Network  
{
public:
	CAipi_RETE_Network();
	virtual ~CAipi_RETE_Network();

	int		findDN(int c);
	int     findEqualCond1(int a, int c );
	int     findEqualCond2(int a, int c );
	int		locateBM(CAipi_RETE_AM am, CAipi_RETE_JNode jn, int c1);
	void	processNCC(int c1, int c2, int b, int BME, int newJoin, int newTK, int finalCond, CAipi_RETE_NCCNode  ncc, CAipi_RETE_PNode pn, CAipi_RETE_BM bm);

	void	createNetwork();
	int		createDummyNode(int c1, int pm );
	int		createNCCNode(int c1);
	int		createNCCPartner(int c2);
	int		createJoinNode(int c1, int f1, int c2, int f2);
	//int     checkNCC(int c1);
	
	void	checkRepeatedCond(int p);
	int     checkRepeatedNegatedCond(int c, int rc);
	int     checkRepeatedNCC(int c, int rc, int a);
	
	int     bindBM_AM(int f1, int f2, int neg, int a, int b, int BME, CAipi_RETE_BM bm, CAipi_RETE_NNode nn);	
	int		bindCond(int c1, int c2);
	int     bindNegatedCond(int c1, int c2, int f);

	
	int     saveChildJN(int b1, int j);
	void    copyBM_ChildJN();
	int     eraseChildJN(int b, int j);	


	//int		assertUpdate(int b1, int b2, int w1, int w2, int f1, int f2,int j);
	//int		assertLeftActivation(int b1,int b2, int w2, int c1, int c2, int j);
	//int     assertRightActivation(int w2, CAipi_RETE_AM am, CAipi_RETE_JNode jn, CAipi_RETE_BM bm, CAipi_RETE_TK tk);
	//int		assertChildJN();
	
	//void    removeWMERematch(int w, RETE_AM am,RETE_JN jn, RETE_BM bm, RETE_Token tk);
	//int     removeBindCond(int b1, int b2, int w1, int w2, int c1, int c2);
	//int		removeUpdate( int b1, int b2, int w1, int w2, int f1, int f2);
	
	void	removeWMEScan(int w2, CAipi_RETE_AM am, CAipi_RETE_BM bm, CAipi_RETE_TK tk, CAipi_WM wm, CAipi_RETE_NNode nn);
	void	removeScanTk(int w2, CAipi_RETE_AM am, CAipi_RETE_BM bm, CAipi_RETE_TK tk, CAipi_WM wm, CAipi_RETE_NNode nn);
	
	void	removeWMETree(int w2, CAipi_RETE_AM am, CAipi_RETE_BM bm, CAipi_RETE_TK tk, CAipi_WM wm, CAipi_RETE_NNode nn);
	void	removeTreeTk(int w2, CAipi_RETE_AM am, CAipi_RETE_BM bm, CAipi_RETE_TK tk, CAipi_WM wm, CAipi_RETE_NNode nn);

	void    addNewProduction(int p);
	void	eraseOldProduction(int p);

	void	StopTimer(CPerfTimer t, CString msg);
	
	void	printDN();
	void	test();
	void	clear();
	
	//void bindVars_Vars();
	//void bindConst_Const();
	//void bindConst_Vars();
	//void bindConstant(tstring c1, tstring c2);
	//void bindingAllVars();
	//void bindingAllConst();


public:
	
	tstring m_Id;
	tstring m_Attr;
	tstring m_Val;
	int		m_CurrentPM;
	int		m_CurrentDN;
	int     m_CurrentChildJN;
	int     m_CurrentNCC;
	int		m_NewTK;
	
	bool    m_Negated;
	typedef std::set<int> m_mDN;
	m_mDN	mDN;
	typedef std::multimap<int, int> m_mmBM_ChildJN;
	m_mmBM_ChildJN	mmmBM_ChildJN;



};

#endif // !defined(AFX_AIPI_RETE_NETWORK_H__AB637ADE_262D_47FD_879B_58AC567E4504__INCLUDED_)
