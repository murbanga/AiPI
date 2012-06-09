// Aipi_CR_Recency.h: interface for the CAipi_CR_Recency class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_CR_RECENCY_H__85622846_C21B_4B29_B0EE_E5F4A316A8EE__INCLUDED_)
#define AFX_AIPI_CR_RECENCY_H__85622846_C21B_4B29_B0EE_E5F4A316A8EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_CR_RecencyTags.h"

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

class CAipi_CR_Recency  
{
public:
	CAipi_CR_Recency();
	virtual ~CAipi_CR_Recency();

	inline CAipi_CR_Recency( int ttag, int sum_ttag, int weight, int nc, long pm)
	{
		m_TimeTag		= ttag;
		m_SumTimeTag	= sum_ttag;
		m_Weight		= weight;
		m_nCond			= nc;
		m_PM			= pm;
			
	}

	inline void CAipi_CR_Recency::setTimeTag(int ttag)
	{
		m_TimeTag = ttag;
	}


	inline void CAipi_CR_Recency::setSumTimeTag(int sum_ttag)
	{
		m_SumTimeTag = sum_ttag;
	}

	inline void CAipi_CR_Recency::setWeight(int weight)
	{
		m_Weight = weight;
	}

	inline void CAipi_CR_Recency::setnCond(int nc)
	{
		m_nCond = nc;
	}

	inline void CAipi_CR_Recency::setPM(long pm)
	{
		m_PM = pm;
	}


	
	inline int CAipi_CR_Recency::getTimeTag()
	{
		return m_TimeTag;
	}


	inline int CAipi_CR_Recency::getSumTimeTag()
	{
		return m_SumTimeTag;
	}

	inline int CAipi_CR_Recency::getWeight()
	{
		return m_Weight;
	}

	inline int CAipi_CR_Recency::getnCond()
	{
		return m_nCond;
	}

	inline long CAipi_CR_Recency::getPM()
	{
		return m_PM;
	}

	
public:
	CAipi_CR_Recency* CAipi_CR_Recency::addCR_Recency(int ttag, int sum_ttag, int weight, int nc, long pm);
	void	eraseRecency(int ttag);
	void	analizeEqualMaxTimeTag();	
	int		calcSumTimeTag(long fired_pm);
	void	calcRecencyFiredPM();
	int		calcRecencyPM(long pm);
	void	createAgenda();	

	void	clearCR_Recency();

	void	printCR_Recency();


public:
	int		m_TimeTag;
	int		m_SumTimeTag;
	int		m_Weight;
	int		m_nCond;
	int		m_PM;

	//Saves the maximum time tag for a production in constant test( the most recent)
	int		m_KMaxTimeTag;


};

#endif // !defined(AFX_AIPI_CR_RECENCY_H__85622846_C21B_4B29_B0EE_E5F4A316A8EE__INCLUDED_)
