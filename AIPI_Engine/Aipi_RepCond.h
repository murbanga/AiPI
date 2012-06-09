// Aipi_RepCond.h: interface for the CAipi_RepCond class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_REPCOND_H__98593D5B_ECAC_4EF6_B164_D42373B112EE__INCLUDED_)
#define AFX_AIPI_REPCOND_H__98593D5B_ECAC_4EF6_B164_D42373B112EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAipi_RepCond  
{
public:
	CAipi_RepCond();
	virtual ~CAipi_RepCond();

	inline CAipi_RepCond(int c, int pm1, int pm2 )
	{
		m_RepCond = c;
		m_PM1 = pm1;
		m_PM2 = pm2;
		
	}

	
	
	inline void CAipi_RepCond::setRepCond(int c)
	{
		m_RepCond = c;

	}

	inline void CAipi_RepCond::setPM1(int pm1)
	{
		m_PM1 = pm1;
	}

	inline void CAipi_RepCond::setPM2(int pm2)
	{
		m_PM2 = pm2;
	}

	inline int CAipi_RepCond::getRepCond()
	{
		return m_RepCond;
	}

	
	inline int CAipi_RepCond::getPM1()
	{
		return m_PM1;
	}

	inline int CAipi_RepCond::getPM2()
	{
		return m_PM2;
	}


public:
	CAipi_RepCond* CAipi_RepCond::addRepCond(int c1, int pm1, int c2, int pm2);
	CAipi_RepCond* CAipi_RepCond::addRepCondEx(int c1, int pm1, int c2, int pm2);
	void	saveRepeatedCond(tstring id, tstring attr, tstring val, int c, int pm);	
	void	saveRepeatedCondIForm(long id_iform, long attr_iform, long val_iform, int c, int pm);	
	void	clearRepCondStructs();
	int     checkEqualCond(int c1, int c2);
	int     checkEqualCondEx(int c1, int c2);

	int		findLowestRepCondEx(int c);
	int		findLowestRepCondExMembers(int c);
	
	//int     findEqualCond(int c);
	
	int		countRepCond(int c);
	int		countRepCondEx(int c);
	
	void	createRepCondEx();
	void	printRepCond();
	void	printRepCondEx();

public:
	
	int m_RepCond;
	int m_PM1;
	int m_PM2;

};

#endif // !defined(AFX_AIPI_REPCOND_H__98593D5B_ECAC_4EF6_B164_D42373B112EE__INCLUDED_)
