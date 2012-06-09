// Aipi_RETE_BMCond.h: interface for the CAipi_RETE_BMCond class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_BMCOND_H__5C091FFC_E58D_4516_8923_CAA2BD13319D__INCLUDED_)
#define AFX_AIPI_RETE_BMCOND_H__5C091FFC_E58D_4516_8923_CAA2BD13319D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAipi_RETE_BMCond  
{
public:
	CAipi_RETE_BMCond();
	virtual ~CAipi_RETE_BMCond();

	inline CAipi_RETE_BMCond(int bm, int c1, int c2, tstring var )
	{
		m_Cond1 = c1;
		m_Cond2 = c2;
		m_Var =  var;
	}

	inline void CAipi_RETE_BMCond::setCond1(int c1)
	{
		m_Cond1 = c1;

	}

	inline void CAipi_RETE_BMCond::setCond2(int c2)
	{
		m_Cond2 = c2;

	}

	inline void CAipi_RETE_BMCond::setVar(tstring var)
	{
		m_Var = var;
	}
	
	
	
	inline int CAipi_RETE_BMCond::getCond1()
	{
		return m_Cond1;
	}
	
	inline int CAipi_RETE_BMCond::getCond2()
	{
		return m_Cond2;
	}

	
	inline tstring CAipi_RETE_BMCond::getVar()
	{
		return m_Var;
	}

	
public:

	CAipi_RETE_BMCond* CAipi_RETE_BMCond::addBMCond(int bm, int c1, int c2, tstring var);
	void		eraseBMCond(int bm);
	void		clearBMCond();
	int			countBMCond(int bm);
	
	void		printBMCond();


public:
	int		m_Cond1;
	int		m_Cond2;
	tstring m_Var;


};

#endif // !defined(AFX_AIPI_RETE_BMCOND_H__5C091FFC_E58D_4516_8923_CAA2BD13319D__INCLUDED_)
