// Aipi_CR_Priority.h: interface for the CAipi_CR_Priority class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_CR_PRIORITY_H__47BB8130_EFA3_40DD_9CD7_A35CA2B24D59__INCLUDED_)
#define AFX_AIPI_CR_PRIORITY_H__47BB8130_EFA3_40DD_9CD7_A35CA2B24D59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAipi_CR_Priority  
{
public:
	CAipi_CR_Priority();
	virtual ~CAipi_CR_Priority();

	inline CAipi_CR_Priority( int weight, int max_ttag, int sum_ttag, int nc, long pm)
	{
		m_Weight		= weight;
		m_MaxTimeTag	= max_ttag;
		m_SumTimeTag	= sum_ttag;
		m_nCond			= nc;
		m_PM			= pm;
			
	}

	inline void CAipi_CR_Priority::setWeight(int weight)
	{
		m_Weight = weight;
	}

	inline void CAipi_CR_Priority::setMaxTimeTag(int max_ttag)
	{
		m_MaxTimeTag = max_ttag;
	}



	inline void CAipi_CR_Priority::setSumTimeTag(int sum_ttag)
	{
		m_SumTimeTag = sum_ttag;
	}

	
	inline void CAipi_CR_Priority::setnCond(int nc)
	{
		m_nCond = nc;
	}

	inline void CAipi_CR_Priority::setPM(long pm)
	{
		m_PM = pm;
	}


	inline int CAipi_CR_Priority::getWeight()
	{
		return m_Weight;
	}

	inline int CAipi_CR_Priority::getMaxTimeTag()
	{
		return m_MaxTimeTag;
	}
	
	inline int CAipi_CR_Priority::getSumTimeTag()
	{
		return m_SumTimeTag;
	}


	inline int CAipi_CR_Priority::getnCond()
	{
		return m_nCond;
	}

	inline long CAipi_CR_Priority::getPM()
	{
		return m_PM;
	}

	
public:
	CAipi_CR_Priority* CAipi_CR_Priority::addCR_Priority(int weight, int max_ttag, int sum_ttag, int nc, long pm);
	void	erasePriority(int weight);
	int		calcSumTimeTag(long fired_pm);
	long	calcPriorityFiredPM();
	long	calcPriorityPM(long pm);

	void	clearCR_Priority();

	void	createAgenda();
	void	printCR_Priority();


public:
	int		m_MaxTimeTag;
	int		m_SumTimeTag;
	int		m_Weight;
	int		m_nCond;
	int		m_PM;

	//Saves the maximum time tag for a production in constant test( the most recent)
	int		m_KMaxTimeTag;


};

#endif // !defined(AFX_AIPI_CR_PRIORITY_H__47BB8130_EFA3_40DD_9CD7_A35CA2B24D59__INCLUDED_)
