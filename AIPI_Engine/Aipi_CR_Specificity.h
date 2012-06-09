// Aipi_CR_Specificity.h: interface for the CAipi_CR_Specificity class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_CR_SPECIFICITY_H__611DBCF7_F454_44C4_9F98_7BDB27E28EE8__INCLUDED_)
#define AFX_AIPI_CR_SPECIFICITY_H__611DBCF7_F454_44C4_9F98_7BDB27E28EE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*
	This class represents helper structure to resolve conflict resolution stategy: Recency
	
	*** Symbols ***
	CR		= Conflict Resolution
	WM		= Working Memory
	LHS		= Left Hand Side
	RHS		= Right Hand Side
	Cond	= Condition
	Recency	= It consist to fired the production that match the most recency elements   
	
	*** Function Parameters ***
	ttag		= time tag ( Number that represents the recency of the working memory element(wme) 
	sum_ttag	= total sum of the time tags of the production conditions (Recency)
	weight		= represents the priority of a production
	nc			= number of conditions in the production (Specificity)
	pm			= production memory element

  
*/

class CAipi_CR_Specificity  
{
public:
	CAipi_CR_Specificity();
	virtual ~CAipi_CR_Specificity();

	inline CAipi_CR_Specificity( int nc, int ttag, int sum_ttag, int weight, long pm)
	{
		m_nCond			= nc;
		m_TimeTag		= ttag;
		m_SumTimeTag	= sum_ttag;
		m_Weight		= weight;
		m_PM			= pm;
			
	}

	inline void CAipi_CR_Specificity::setnCond(int nc)
	{
		m_nCond = nc;
	}

	inline void CAipi_CR_Specificity::setTimeTag(int ttag)
	{
		m_TimeTag = ttag;
	}


	inline void CAipi_CR_Specificity::setSumTimeTag(int sum_ttag)
	{
		m_SumTimeTag = sum_ttag;
	}

	inline void CAipi_CR_Specificity::setWeight(int weight)
	{
		m_Weight = weight;
	}

	

	inline void CAipi_CR_Specificity::setPM(long pm)
	{
		m_PM = pm;
	}


	
	inline int CAipi_CR_Specificity::getTimeTag()
	{
		return m_TimeTag;
	}


	inline int CAipi_CR_Specificity::getSumTimeTag()
	{
		return m_SumTimeTag;
	}

	inline int CAipi_CR_Specificity::getWeight()
	{
		return m_Weight;
	}

	inline int CAipi_CR_Specificity::getnCond()
	{
		return m_nCond;
	}

	inline long CAipi_CR_Specificity::getPM()
	{
		return m_PM;
	}

	
public:
	CAipi_CR_Specificity* CAipi_CR_Specificity::addCR_Specificity(int nc, int max_ttag, int sum_ttag, int weight, long pm);
	void	eraseSpecificity(int nc);
	int		calcSumTimeTag(long fired_pm);
	void	calcSpecificityFiredPM();
	int		calcSpecificityPM(long pm);

	void	createAgenda();	

	void    clearCR_Specificity();
	void	printCR_Specificity();


public:
	int		m_nCond;
	int		m_TimeTag;
	int		m_SumTimeTag;
	int		m_Weight;
	int		m_PM;

	//Saves the maximum time tag for a production in constant test( the most recent)
	int		m_KMaxTimeTag;

};

#endif // !defined(AFX_AIPI_CR_SPECIFICITY_H__611DBCF7_F454_44C4_9F98_7BDB27E28EE8__INCLUDED_)
