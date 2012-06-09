// Aipi_RETE_Net.h: interface for the CAipi_RETE_Net class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_NET_H__54E7ECCF_CE4A_4502_AF20_F073B062C111__INCLUDED_)
#define AFX_AIPI_RETE_NET_H__54E7ECCF_CE4A_4502_AF20_F073B062C111__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Aipi_WM.h"
#include "Aipi_LHS.h"
#include "Aipi_RHS.h"
#include "Aipi_RHSCmd.h"
#include "Aipi_RETE_AM.h"
#include "Aipi_RETE_BM.h"
#include "Aipi_RETE_TK.h"
#include "Aipi_RETE_JNode.h"
#include "Aipi_RETE_PNode.h"
#include "Aipi_RETE_NNode.h"
#include "Aipi_RETE_NCCNode.h"
#include "Aipi_RETE_Node.h"
#include "Aipi_RETE_NodeCond.h"
#include "Aipi_RETE_NumVars.h"




#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <set>

#define ID_ID		1000
#define	ID_VAL		2000
#define	VAL_ID		3000

/*
	/// RETE Net ///
This class creates the RETE Network


	*** Symbols ***
	AM		= Alpha Memory
	BM		= Beta Memory
	WM		= Working Memory
	PM		= Production Memory
	Cond	= Condition
	
	I	= Identifier (Id)   
	A	= Atribute (Attr)  
	V	= Value (Val)
	e	= Don`t care
	


	*** Function Parameters ***
	am		= Alpha Memory
	bm		= Beta Memory
	wm		= Working Memory
	pm		= Production Memory
	lhs		= Left Hand Side Function
	cond	= Condition
	
*/

class CAipi_RETE_Net  
{
public:
	CAipi_RETE_Net();
	virtual ~CAipi_RETE_Net();

	void	preAnalysis();
	int		getPMVars(int pm);
	int		getRangePMVars(int cini, int cend, int pm);
	//int		linkVALVars(int pm, tstring var);
	int		lastIDVar(int pm, tstring var);
	int		firstIDVar(int pm, tstring var);
	int		linkRangeIDVars(int cini, int cend, tstring var);
	int		linkRangeVALVars(int cini, int cend, tstring var);
	
	void	linkCondID_ID(int size, int pm, tstring var);
	void	linkCondVAL_VAL(int size, int pm, tstring var);
	//void	saveVAL_ID(int pm, tstring var);
	void	linkCondVAL_ID(int cini, int cend, int pm, tstring var);

	tstring searchPMVarAssig(int pm, tstring val);
	int		matchRepCond(int c1, int c2);
	int		matchRepCondField(int c1, int c2, int f1, int f2, tstring var);


	int     createNet();
	int		createDNode(int c1, int pm, int bm);
	int		createBM(int c1, int c2, int f1, int f2, int am, int bm, int pm, int newBM, tstring var);
	int		createNumBM(int bm, tstring var1, tstring var2, tstring data1, tstring data2, int wm, int old_tk, int pm, int c1, int c2);
	
	int		createJN(int c1, int f1, int c2, int f2, int pm, int bm1, int bm2, int am, tstring var);
	void	createAM();
	void	createPNode();
	void    createBME(); 

	int		assertUpdateAM(int wm);
	int		assertUpdateBM(int am, int wm, int pm);
	int		assertUpdateCreateBM(int c1, int c2, int f1, int f2, int am, int bm, int pm, int newBM, tstring var);
	
	int		retractUpdateAM(int wm);
	int		retractUpdateBM(int wm);

	int		findEqualCond(int a,int c);
	//int     findTokenPM(int pm, int child_tk);
	
	int		checkPMRepCondMatch(long pm);
	int		checkingVars(tstring var1, tstring var2, tstring var3, tstring data1, int old_tk, int bm, int newBM);
	int		checkingDNode(int c);
	int		checkingRepeatedCond(int c1, int c2, int am1, int am2, long pm, tstring var);
	int		checkingRepeatedTK(int parent_tk, int wm);
	int     checkingNumVar(int ini_bm, int end_bm, int bm, int pm,  int wm, int old_tk, tstring var, int side);
	bool    checkEqualRelAtt(int c1, int c2, int wm, tstring var1, tstring var2);
	void    checkPreBMCondBinding(int c1, int c2, int am1, int am2, long pm);
	int		saveDataNum(int pm, int c2, int wm, int type, int bm, int old_tk, tstring varName, tstring varData);
	int		saveVarNum(tstring id_var, tstring var, int wm, int i_bm, int side);
	void	compareNumVars(int pm);
	void	selectRelOperator(int rel, int bm, tstring var1, tstring var2, tstring data1, tstring data2, int type1, int type2, int wm, int old_tk, int pm, int c1, int c2 );
	int		processRelCond(int rel_c);
	

public:


	vector<int> m_vID;
	vector<int> m_vVAL;
	
	
	int			m_iData1;
	int			m_iData2;
	long		m_lData1;
	long		m_lData2;
	float		m_fData1;
	float		m_fData2;
	double		m_dData1;
	double		m_dData2;
	tstring		m_sData1;
	tstring		m_sData2;
	
	


};

#endif // !defined(AFX_AIPI_RETE_NET_H__54E7ECCF_CE4A_4502_AF20_F073B062C111__INCLUDED_)
