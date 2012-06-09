// Aipi_CR_RecencyTags.h: interface for the CAipi_CR_RecencyTags class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_CR_RECENCYTAGS_H__77725A7D_E9DF_4889_8A49_C5AB54BE0CEA__INCLUDED_)
#define AFX_AIPI_CR_RECENCYTAGS_H__77725A7D_E9DF_4889_8A49_C5AB54BE0CEA__INCLUDED_

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

class CAipi_CR_RecencyTags  
{
public:
	CAipi_CR_RecencyTags();
	virtual ~CAipi_CR_RecencyTags();

	inline CAipi_CR_RecencyTags( int sum_ttag, int ttag, int weight, int nc, long pm)
	{
		m_SumTimeTag	= sum_ttag;
		m_TimeTag		= ttag;
		m_Weight		= weight;
		m_nCond			= nc;
		m_PM			= pm;
			
	}

	

	inline void CAipi_CR_RecencyTags::setSumTimeTag(int sum_ttag)
	{
		m_SumTimeTag = sum_ttag;
	}


	inline void CAipi_CR_RecencyTags::setTimeTag(int ttag)
	{
		m_TimeTag = ttag;
	}


	inline void CAipi_CR_RecencyTags::setWeight(int weight)
	{
		m_Weight = weight;
	}

	inline void CAipi_CR_RecencyTags::setnCond(int nc)
	{
		m_nCond = nc;
	}

	inline void CAipi_CR_RecencyTags::setPM(long pm)
	{
		m_PM = pm;
	}
	
	
	inline int CAipi_CR_RecencyTags::getSumTimeTag()
	{
		return m_SumTimeTag;
	}

	
	inline int CAipi_CR_RecencyTags::getTimeTag()
	{
		return m_TimeTag;
	}


	inline int CAipi_CR_RecencyTags::getWeight()
	{
		return m_Weight;
	}

	inline int CAipi_CR_RecencyTags::getnCond()
	{
		return m_nCond;
	}

	inline long CAipi_CR_RecencyTags::getPM()
	{
		return m_PM;
	}

public:
CAipi_CR_RecencyTags* CAipi_CR_RecencyTags::addCR_RecencyTags(int sum_ttag, int ttag, int weight, int nc, long pm);
	int		calcSumTimeTag(long fired_pm);
	void	calcRecencyTagsFiredPM();
	int		calcRecencyTagsPM(long pm);

	void	clearCR_RecencyTags();

	void	printCR_RecencyTags();

public:
	int		m_SumTimeTag;
	int		m_TimeTag;
	int		m_Weight;
	int		m_nCond;
	int		m_PM;

	//Saves the maximum time tag for a production in constant test( the most recent)
	int		m_KMaxTimeTag;


};

#endif // !defined(AFX_AIPI_CR_RECENCYTAGS_H__77725A7D_E9DF_4889_8A49_C5AB54BE0CEA__INCLUDED_)
