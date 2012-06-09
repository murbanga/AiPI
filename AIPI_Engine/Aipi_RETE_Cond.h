// Aipi_RETE_Cond.h: interface for the CAipi_RETE_Cond class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_COND_H__2AD8CC46_CBA0_4EC6_B64C_6833770DE2E9__INCLUDED_)
#define AFX_AIPI_RETE_COND_H__2AD8CC46_CBA0_4EC6_B64C_6833770DE2E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*
	This class saves information of conditions and others RETE elements.
		

	*** Symbols ***
	C1		= Condition1
	C2		= Condition2
	Var		= Variable of the condition
	PM		= Production Memory
	JN		= Join Node were the condition belongs
	
	

	*** Function Parameters ***
	pm		= Production Memory
	lhs		= Left Hand Side Function
	cond	= Condition
	
*/

class CAipi_RETE_Cond  
{
public:
	CAipi_RETE_Cond();
	virtual ~CAipi_RETE_Cond();

	inline CAipi_RETE_Cond(int jn, int pm, tstring var)
	{
		m_JN = jn;
		m_PM = pm;
		m_Var	 = var;	
	}

	
	
	inline void CAipi_RETE_Cond::setJN(int jn)
	{
		m_JN = jn;

	}

	inline void CAipi_RETE_Cond::setPM(int pm)
	{
		m_PM = pm;
	}


	inline void CAipi_RETE_Cond::setVar(tstring var)
	{
		m_Var = var;
	}

	
	
	
	inline int CAipi_RETE_Cond::getJN()
	{
		return m_JN;
	}
	
	
	inline int CAipi_RETE_Cond::getPM()
	{
		return m_PM;
	}


	inline tstring CAipi_RETE_Cond::getVar()
	{
		return m_Var;
	}

	
	

public:	
	CAipi_RETE_Cond* CAipi_RETE_Cond::addCond1(int c1, int jn, int pm, tstring var);
	CAipi_RETE_Cond* CAipi_RETE_Cond::addCond2(int c2, int jn, int pm, tstring var);
	void		addPreCondBind(int c1, int c2);	
	void		editCond1(int c2, int jn, int pm, tstring var);
	void		editCond2(int c2, int jn, int pm, tstring var);
	void		clearCondStructs();
	void        clearPreCondBind();
	void		eraseCond1(int c1);
	void		eraseCond2(int c2);
	void		deleteJNCond1(int jn);
	void		deleteJNCond2(int jn);

	int			findCond1Members(int c1);
	int			findCond2Members(int c2);
	int			findCond1JN(int c1);
	int			findCond2JN(int c2);
	int			findCond1PM(int c1);
	int			findCond2PM(int c2);
	tstring		findCond1Var(int c1);
	tstring		findCond2Var(int c2);

	int			findCond1JN_JN(int c1, int jn2);
	int         findPreCondBind(int c1);

	int			sizeCond1();
	int			sizeCond2();

	void		printCond1();
	void		printCond2();
	
public:
	
	int			m_JN;
	int			m_PM;
	tstring		m_Var;

};

#endif // !defined(AFX_AIPI_RETE_COND_H__2AD8CC46_CBA0_4EC6_B64C_6833770DE2E9__INCLUDED_)
