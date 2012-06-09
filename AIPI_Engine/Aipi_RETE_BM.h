// Aipi_RETE_BM.h: interface for the CAipi_RETE_BM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_BM_H__86A3CBD5_4D8F_4A90_8B31_022FF24E0BB5__INCLUDED_)
#define AFX_AIPI_RETE_BM_H__86A3CBD5_4D8F_4A90_8B31_022FF24E0BB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "CAipi_WM.h"
#include "Aipi_RETE_Node.h"
#include "Aipi_RETE_TK.h"


/*
	This class rerpresents the Beta Memory and all the relations with others RETE structures.


	*** Symbols ***
	BM		= Beta Memory
	Var1	= Variable1
	Var2	= Variable2
	WM		= Working Memory
	PM		= Production Memory
	TK		= Token
	ChildTK = Child Token (Token that depends from other tokens previously created)  
	ParentTK= Parent Token(Token that has others tokens that were dependent of it)  	
	
	
	

	*** Function Parameters ***
	am		= Alpha Memory
	bm		= Beta Memory
	wm		= Working Memory
	pm		= Production Memory
	lhs		= Left Hand Side Function
	cond	= Condition
	
*/


class CAipi_RETE_BM  
{
public:
	CAipi_RETE_BM();
	virtual ~CAipi_RETE_BM();

	inline CAipi_RETE_BM(tstring var1, tstring data1, tstring var2, tstring data2, int oldTK, int newTK, int wm )
	{
		m_Var1 = var1;
		m_Var2 = var2;
		m_Data1 = data1;
		m_Data2 = data2;
		m_ParentTK = oldTK;
		m_ChildTK	 = newTK;
		m_WM		= wm;
		
	}

	inline void CAipi_RETE_BM::setVar1(tstring var1)
	{
		m_Var1 = var1;

	}

	inline void CAipi_RETE_BM::setVar2(tstring var2)
	{
		m_Var2 = var2;

	}

	inline void CAipi_RETE_BM::setData1(tstring data1)
	{
		m_Data1 = data1;
	}
	
	inline void CAipi_RETE_BM::setData2(tstring data2)
	{
		m_Data2 = data2;
	}


	inline void CAipi_RETE_BM::setParentTK(int oldTK)
	{
		m_ParentTK = oldTK;
	}

	inline void CAipi_RETE_BM::setChildTK(int newTK)
	{
		m_ChildTK = newTK;
	}

	inline void CAipi_RETE_BM::setWM(int wm)
	{
		m_WM = wm;
	}
	
	
	
	inline tstring CAipi_RETE_BM::getVar1()
	{
		return m_Var1;
	}
	
	inline tstring CAipi_RETE_BM::getVar2()
	{
		return m_Var2;
	}

	
	inline tstring CAipi_RETE_BM::getData1()
	{
		return m_Data1;
	}

	inline tstring CAipi_RETE_BM::getData2()
	{
		return m_Data2;
	}



	inline int CAipi_RETE_BM::getParentTK()
	{
		return m_ParentTK;
	}

	inline int CAipi_RETE_BM::getChildTK()
	{
		return m_ChildTK;
	}

	inline int CAipi_RETE_BM::getWM()
	{
		return m_WM;
	}

public:

	CAipi_RETE_BM* CAipi_RETE_BM::addBM(int bm, tstring var1, tstring data1, tstring var2, tstring data2, int oldTK, int newTK, int wm);

	//void		addBM_TK(int bm, int tk);
	void		addBM_ChildJN(int bm, int jn);
	void		editBM(int bm, tstring var1, tstring data1, tstring var2, tstring data2, int oldtk, int newtk, int wm);
	void		editBM_ParentTK(int bm,int tk);
	void		editBM_ChildTK(int bm,int tk);

	int			previousBM(int bm);
	int			lastBM();
	int			sizeBM();
	int			countBM(int bm);
		

	int			TK_LowerBound(int bm);
	int			TK_UpperBound(int bm);

	void		eraseBM(int bm);
	int			eraseItemBM_ParentTK(int bm, int tk);
	int			eraseItemBM_ChildTK(int bm, int tk);
	
	void		eraseBM_ChildJN(int bm);
	int			eraseItemBM_ChildJN(int bm, int jn);
	void		clearBM();
		
	int			searchWMTK(int bm,int wm, int chd);
	int			searchBMParentTK(int tk);
	int			searchBMChildTK(int tk);
	int			findBMMembers(int bm);
	int			findBMWM(int bm, int wm);
	tstring		findBMData1ChildTK(int bm, int chd_tk);
	tstring		findBMData2ChildTK(int bm, int chd_tk);
	tstring		findBMVar1(int bm, tstring var1);
	tstring		findBMVar2(int bm, tstring var2);
	tstring		findBMData1(int bm, tstring data1);
	tstring		findBMData2(int bm, tstring data2);
	
	int			findBMParentTK(int bm, int parent_tk);
	int			findBMChildTK(int bm, int child_tk);
	int			findBM_ChildJN(int bm);
	
	
	void		printBM();
	void		printLinkBM_TK();
	void		printBM_ChildJN();
	void		printV_BM_ChildJN();
	//void		printWMTK();
			

	int			generateBMKey();
	
public:

	tstring		m_Var1;
	tstring		m_Var2;
	tstring		m_Data1;
	tstring		m_Data2;
	int			m_ParentTK;
	int			m_ChildTK;
	int			m_WM;

};

#endif // !defined(AFX_AIPI_RETE_BM_H__86A3CBD5_4D8F_4A90_8B31_022FF24E0BB5__INCLUDED_)
