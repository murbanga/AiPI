// Aipi_RETE_NodeCond.h: interface for the CAipi_RETE_NodeCond class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_NODECOND_H__41DF49ED_1908_4C65_8D6C_029310E4E10B__INCLUDED_)
#define AFX_AIPI_RETE_NODECOND_H__41DF49ED_1908_4C65_8D6C_029310E4E10B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*

	*** Symbols ***
	Node	= Node Index(Join Node, Production Noide, Negated Node, etc..)
	Cond1	= Parent Condition of the Node (Parent)
	Cond2	= Child  Condition of the Node (Child)
	PM		= Production Memory where the conditions belong.
	AM		= Alpha Memory linked to the Node  

	*** Functions Parameters ***
	c1		= Parent Condition of the Node (parent)
	c2		= Child  Condition of the Node (child)
	pm		= Production Memory
	am		= Alpha Memory linked to the Node  
*/


class CAipi_RETE_NodeCond  
{
public:
	CAipi_RETE_NodeCond();
	virtual ~CAipi_RETE_NodeCond();

	CAipi_RETE_NodeCond(int c1, int c2, long pm,int am)
	{
		m_Cond1		= c1;
		m_Cond2		= c2;
		m_PM		= pm;
	}

	inline void CAipi_RETE_NodeCond::setCond1(int c1)
	{
		m_Cond1 = c1;
	}


	inline void CAipi_RETE_NodeCond::setCond2(int c2)
	{
		m_Cond2 = c2;
	}

	inline void CAipi_RETE_NodeCond::setPM(long pm)
	{
		m_PM = pm;
	}

	
	inline int CAipi_RETE_NodeCond::getCond1()
	{
		return m_Cond1;
	}


	inline int CAipi_RETE_NodeCond::getCond2()
	{
		return m_Cond2;
	}

	inline long CAipi_RETE_NodeCond::getPM()
	{
		return m_PM;
	}

	

public:
	CAipi_RETE_NodeCond* CAipi_RETE_NodeCond::addNodeCond(int node, int c1, int c2, int pm); 
	void	printNodeCond();
	int		findNodeCond1_PM(int node, long pm);
	int		findNodeCond2_PM(int node, long pm);
	int		findNodeCond1_Cond2(int node, int c2);
	int     countNodeCond(int node);

	void	clearNodeCond();

public:
	int		m_Cond1;
	int		m_Cond2;
	long	m_PM;
	

};

#endif // !defined(AFX_AIPI_RETE_NODECOND_H__41DF49ED_1908_4C65_8D6C_029310E4E10B__INCLUDED_)
