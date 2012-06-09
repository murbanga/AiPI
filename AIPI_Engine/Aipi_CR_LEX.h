// Aipi_CR_LEX.h: interface for the CAipi_CR_LEX class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_CR_LEX_H__8C59672F_D8AB_4E6F_BAE3_4F863947AD0E__INCLUDED_)
#define AFX_AIPI_CR_LEX_H__8C59672F_D8AB_4E6F_BAE3_4F863947AD0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_CR_Recency.h"
#include "Aipi_CR_Priority.h"

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

class CAipi_CR_LEX  
{
public:
	CAipi_CR_LEX();
	virtual ~CAipi_CR_LEX();

	

	
public:
	void    calcCR_LEX();
	void	clearCR_LEX();
	void	createAgenda();	



};

#endif // !defined(AFX_AIPI_CR_LEX_H__8C59672F_D8AB_4E6F_BAE3_4F863947AD0E__INCLUDED_)
