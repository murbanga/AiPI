// Aipi_RETE_AM.h: interface for the CAipi_RETE_AM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_AM_H__F06EC08F_9451_4B9B_9232_45359BB2EEAE__INCLUDED_)
#define AFX_AIPI_RETE_AM_H__F06EC08F_9451_4B9B_9232_45359BB2EEAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_WM.h"
#include "Aipi_LHS.h"
#include "Aipi_RETE_Net.h"

/*
	This class rerpresents the Alpha Memory and all the relations with others RETE structures.


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
	
	LT	= Lesser than
	LE	= Lesser or Equal than
	GT	= Greater than 
	GE	= Greater or Equal than
	EQ	= Equal than
	NE	= Not Equal than (Different)
	
	

	*** Function Parameters ***
	am		= Alpha Memory
	bm		= Beta Memory
	wm		= Working Memory
	pm		= Production Memory
	lhs		= Left Hand Side Function
	cond	= Condition
	
*/

class CAipi_RETE_AM  
{
public:
	CAipi_RETE_AM();
	virtual ~CAipi_RETE_AM();

	void		addAM_WM(int am, int wm);
	void		addWM_AM(int wm, int am); 
	
	
	int			insertWM(int wm);
	void		insertAllWM();
	void		insertStructsWM_AM();
	int			updateStructsWM_AM(int wm);
	int			insertEQ(int wm, tstring id, tstring attr, tstring val);
	int			insertET(int wm, tstring id, tstring attr, tstring val);
	int			insertNE(int wm, tstring id, tstring attr, tstring val);
	int			insertLT(int wm, tstring id, tstring attr, tstring val);
	int			insertLE(int wm, tstring id, tstring attr, tstring val);
	int			insertGT(int wm, tstring id, tstring attr, tstring val);
	int			insertGE(int wm, tstring id, tstring attr, tstring val);
	int			insertAS(int wm, tstring id, tstring attr, tstring val);	
	//void		addWMEsNewPM();
	
	int         eraseItemAM_WM(int am,int wm);
	//int			eraseItemWM_AM(int wm,int am);
	int			eraseItemAM_Cond(int am,int c);
	void		eraseAM_WM(int am);
	void		eraseWM_AM(int wm);
	void		eraseCond_AM(int c);
	void		eraseAM_Cond(int am);
	void		eraseCondStructs(int pm);

	void		clearAMStructs();
	void		clearLogicStructs();
	
	//void		createAM();
	void		constantTestCond(int c);
	void		constantTestAllCond();
	void		constantTest();
	void		constantTestEQ(int c, tstring id, tstring attr, tstring val, int pm, int categ);
	void		constantTestET(int c, tstring id, tstring attr, tstring val, int pm, int categ);
	void		constantTestNE(int c, tstring id, tstring attr, tstring val, int pm, int categ);
	void		constantTestLT(int c, tstring id, tstring attr, tstring val, int pm, int categ);
	void		constantTestLE(int c, tstring id, tstring attr, tstring val, int pm, int categ);
	void		constantTestGT(int c, tstring id, tstring attr, tstring val, int pm, int categ);
	void		constantTestGE(int c, tstring id, tstring attr, tstring val, int pm, int categ);
	void		constantTestAS(int c, tstring id, tstring attr, tstring val, int pm, int categ);
	void		updateRelAM(int pm);
	int			largerItemAM_WM();
	bool		isNumber(tstring c);
	bool		isVariable(tstring c);
	int			isType(tstring c);
	int			saveConstDataNum(int pm, int c, int type, tstring var, tstring data);	
	int			generateAMKey();
	void		fillAM_WM();
	void		fillPM_Vars(int pm);

	////////////////////////////////////////
	/// IForm ///
	////////////////////////////////////////
	void		constantTestIForm();
	void		updateRelAMIForm(int pm);


	///////////////////////////////////////////
	int			sizeAM_Cond();
	int			sizeCond_AM();
	int			sizeAM_WM();
	int			lastAM();
	

	int			countAM_Cond(int am);
	//int         countWM_AM(int wm);
	int         countAM_WM(int am);

	int			findAM_WM(int am);
	int			findWM_AM(int wm);
	int			findCond_AM(int c);
	int			findAM_Cond(int am);
	
	tstring		findAM_EQ_I_K_V(int am);
	tstring		findAM_EQ_I_K_K(int am);
	tstring		findAM_EQ_I_A_V(int am);
	tstring		findAM_EQ_I_A_K(int am);
	tstring		findAM_EQ_K_K_V(int am);
	tstring		findAM_EQ_K_K_K(int am);
	tstring		findAM_EQ_K_A_V(int am);
	tstring		findAM_EQ_K_A_K(int am);

	tstring		findAM_ET_I_K_V(int am);
	tstring		findAM_ET_I_K_K(int am);
	tstring		findAM_ET_I_A_V(int am);
	tstring		findAM_ET_I_A_K(int am);
	tstring		findAM_ET_K_K_V(int am);
	tstring		findAM_ET_K_K_K(int am);
	tstring		findAM_ET_K_A_V(int am);
	tstring		findAM_ET_K_A_K(int am);

	tstring		findAM_GE_I_K_V(int am);
	tstring		findAM_GE_I_K_K(int am);
	tstring		findAM_GE_I_A_V(int am);
	tstring		findAM_GE_I_A_K(int am);
	tstring		findAM_GE_K_K_V(int am);
	tstring		findAM_GE_K_K_K(int am);
	tstring		findAM_GE_K_A_V(int am);
	tstring		findAM_GE_K_A_K(int am);

	tstring		findAM_GT_I_K_V(int am);
	tstring		findAM_GT_I_K_K(int am);
	tstring		findAM_GT_I_A_V(int am);
	tstring		findAM_GT_I_A_K(int am);
	tstring		findAM_GT_K_K_V(int am);
	tstring		findAM_GT_K_K_K(int am);
	tstring		findAM_GT_K_A_V(int am);
	tstring		findAM_GT_K_A_K(int am);

	tstring		findAM_LE_I_K_V(int am);
	tstring		findAM_LE_I_K_K(int am);
	tstring		findAM_LE_I_A_V(int am);
	tstring		findAM_LE_I_A_K(int am);
	tstring		findAM_LE_K_K_V(int am);
	tstring		findAM_LE_K_K_K(int am);
	tstring		findAM_LE_K_A_V(int am);
	tstring		findAM_LE_K_A_K(int am);

	tstring		findAM_LT_I_K_V(int am);
	tstring		findAM_LT_I_K_K(int am);
	tstring		findAM_LT_I_A_V(int am);
	tstring		findAM_LT_I_A_K(int am);
	tstring		findAM_LT_K_K_V(int am);
	tstring		findAM_LT_K_K_K(int am);
	tstring		findAM_LT_K_A_V(int am);
	tstring		findAM_LT_K_A_K(int am);

	tstring		findAM_AS_I_K_V(int am);
	tstring		findAM_AS_I_K_K(int am);
	tstring		findAM_AS_I_A_V(int am);
	tstring		findAM_AS_I_A_K(int am);
	tstring		findAM_AS_K_K_V(int am);
	tstring		findAM_AS_K_K_K(int am);
	tstring		findAM_AS_K_A_V(int am);
	tstring		findAM_AS_K_A_K(int am);



	void		printAM_WM();
	void		printWM_AM();	
	void		printCond_AM();
	void		printAM_Cond();
	void		printEQ();
	void		printEQ_e_e_e();
	void		printEQ_e_A_e();
	void		printEQ_e_A_V();
	void		printEQ_e_e_V();
	void		printEQ_I_A_e();
	void		printEQ_I_A_V();
	void		printEQ_I_e_e();
	void		printEQ_I_e_V();
	void		printET();
	void		printET_e_e_e();
	void		printET_e_A_e();
	void		printET_e_A_V();
	void		printET_e_e_V();
	void		printET_I_A_e();
	void		printET_I_A_V();
	void		printET_I_e_e();
	void		printET_I_e_V();
	void		printNE();
	void		printNE_e_e_e();
	void		printNE_e_A_e();
	void		printNE_e_A_V();
	void		printNE_e_e_V();
	void		printNE_I_A_e();
	void		printNE_I_A_V();
	void		printNE_I_e_e();
	void		printNE_I_e_V();
	void		printLT();
	void		printLT_e_e_e();
	void		printLT_e_A_e();
	void		printLT_e_A_V();
	void		printLT_e_e_V();
	void		printLT_I_A_e();
	void		printLT_I_A_V();
	void		printLT_I_e_e();
	void		printLT_I_e_V();
	void		printLE();
	void		printLE_e_e_e();
	void		printLE_e_A_e();
	void		printLE_e_A_V();
	void		printLE_e_e_V();
	void		printLE_I_A_e();
	void		printLE_I_A_V();
	void		printLE_I_e_e();
	void		printLE_I_e_V();
	void		printGT();
	void		printGT_e_e_e();
	void		printGT_e_A_e();
	void		printGT_e_A_V();
	void		printGT_e_e_V();
	void		printGT_I_A_e();
	void		printGT_I_A_V();
	void		printGT_I_e_e();
	void		printGT_I_e_V();
	void		printGE();
	void		printGE_e_e_e();
	void		printGE_e_A_e();
	void		printGE_e_A_V();
	void		printGE_e_e_V();
	void		printGE_I_A_e();
	void		printGE_I_A_V();
	void		printGE_I_e_e();
	void		printGE_I_e_V();
	void		printAS();
	void		printAS_e_e_e();
	void		printAS_e_A_e();
	void		printAS_e_A_V();
	void		printAS_e_e_V();
	void		printAS_I_A_e();
	void		printAS_I_A_V();
	void		printAS_I_e_e();
	void		printAS_I_e_V();
	
	

public:
	

	


	
/*	

	//Structures for Equality Test ( == )
	//Key = Identifier, Attribute or Value
	//Value = Condition Index
	typedef std::multimap<tstring, int> m_mmEQ_I_A_V;
	m_mmEQ_I_A_V	mmEQ_I_A_V;
	typedef std::multimap<tstring, int> m_mmEQ_I_A_K;
	m_mmEQ_I_A_K	mmEQ_I_A_K;
	typedef std::multimap<tstring, int> m_mmEQ_I_K_V;
	m_mmEQ_I_K_V	mmEQ_I_K_V;
	typedef std::multimap<tstring, int> m_mmEQ_I_K_K;
	m_mmEQ_I_K_K	mmEQ_I_K_K;
	typedef std::multimap<tstring, int> m_mmEQ_K_A_V;
	m_mmEQ_K_A_V	mmEQ_K_A_V;
	typedef std::multimap<tstring, int> m_mmEQ_K_A_K;
	m_mmEQ_K_A_K	mmEQ_K_A_K;
	typedef std::multimap<tstring, int> m_mmEQ_K_K_V;
	m_mmEQ_K_K_V	mmEQ_K_K_V;
	typedef std::multimap<tstring, int> m_mmEQ_K_K_K;
	m_mmEQ_K_K_K	mmEQ_K_K_K;

*/	

	tstring m_Id;
	tstring m_Attr;
	tstring m_Val;
	int		m_Rel;

	int m_cont;

	


};

#endif // !defined(AFX_AIPI_RETE_AM_H__F06EC08F_9451_4B9B_9232_45359BB2EEAE__INCLUDED_)
