// Aipi_RETE_Links.h: interface for the CAipi_RETE_Links class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_LINKS_H__7357F4AC_DB01_4DF3_A1E3_2ACFB1B75739__INCLUDED_)
#define AFX_AIPI_RETE_LINKS_H__7357F4AC_DB01_4DF3_A1E3_2ACFB1B75739__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*

	This class represents links between conditions in a production.
	The conditions are linked by equal variables.

	*** Symbols ***
	c1		= Condition1 
	c2		= Condition2
	f1		= Field1
	f2		= Field2
	PM		= Production Memory
	Var		= Variable that links c1 with c2

	
*/

class CAipi_RETE_Links  
{
public:
	CAipi_RETE_Links();
	virtual ~CAipi_RETE_Links();

	
	inline CAipi_RETE_Links(int c2, int f1, int f2, int pm, tstring var)
	{
		m_Cond2 = c2;
		m_Field1 = f1;
		m_Field2 = f2;
		m_PM	 = pm;	
		m_Var	 = var;	
	}

	
	
	inline void CAipi_RETE_Links::setCond2(int c2)
	{
		m_Cond2 = c2;

	}

	inline void CAipi_RETE_Links::setField1(int f1)
	{
		m_Field1 = f1;
	}


	inline void CAipi_RETE_Links::setField2(int f2)
	{
		m_Field2 = f2;
	}

	inline void CAipi_RETE_Links::setPM(int pm)
	{
		m_PM = pm;
	}

	inline void CAipi_RETE_Links::setVar(tstring var)
	{
		m_Var = var;

	}

	
	
	inline int CAipi_RETE_Links::getCond2()
	{
		return m_Cond2;
	}
	
	
	inline int CAipi_RETE_Links::getField1()
	{
		return m_Field1;
	}


	inline int CAipi_RETE_Links::getField2()
	{
		return m_Field2;
	}

	inline int CAipi_RETE_Links::getPM()
	{
		return m_PM;
	}

	
	inline tstring CAipi_RETE_Links::getVar()
	{
		return m_Var;
	}


public:	
	CAipi_RETE_Links* CAipi_RETE_Links::addLink(int c1, int c2, int f1, int f2, int pm, tstring var);

	void		printCondLink();
	int			findLinksMembers(int c1);
	int			findCond1_Cond2(int c1, int c2);	
	int			checkRepLinks(int rc1, int rc2, int c1, int c2);
	int			countLinks(int c1);
	int         sizeLinks();

	void		clearLinks();

public:
	
	int			m_Cond2;
	int			m_Field1;
	int			m_Field2;
	int			m_PM;
	tstring		m_Var;

};

#endif // !defined(AFX_AIPI_RETE_LINKS_H__7357F4AC_DB01_4DF3_A1E3_2ACFB1B75739__INCLUDED_)
