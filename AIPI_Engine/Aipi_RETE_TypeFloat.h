// Aipi_RETE_TypeFloat.h: interface for the CAipi_RETE_TypeFloat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_TYPEFLOAT_H__46B9506A_2200_46F8_BC72_49E2B4D67384__INCLUDED_)
#define AFX_AIPI_RETE_TYPEFLOAT_H__46B9506A_2200_46F8_BC72_49E2B4D67384__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_RETE_NumNode.h"

//This class saves information about numeric opeartions in the RETE Network
//In this case Operations between floating numeric types
//Type : FLOAT

/*
	*** Symbols ***
	TK		= Token
	BM		= Beta Memory
	WM		= Working Memory
	PM		= Production Memory
	Cond	= Condition
	Data	= Numeric Value

	I	= Identifier (Id)   
	A	= Atribute (Attr)  
	V	= Value (Val)
	e	= Don`t care
	
	LT	= Lesser than
	LE	= Lesser or Equal than
	GT	= Greater than 
	GE	= Greater or Equal than
	EQ	= Equal than
	NE	= Not Equal than (Different)
	
	

	*** Function Parameters ***
	am		= Alpha Memory
	bm		= Beta Memory
	wm		= Working Memory
	pm		= Production Memory
	lhs		= Left Hand Side Function
	cond	= Condition
	
*/


class CAipi_RETE_TypeFloat : public CAipi_RETE_NumNode 
{
public:
	CAipi_RETE_TypeFloat();
	virtual ~CAipi_RETE_TypeFloat();

	inline CAipi_RETE_TypeFloat(int pm, int c, float dat, int wm, int bm, int oldtk)
	{
		CAipi_RETE_NumNode::setPM(pm);
		CAipi_RETE_NumNode::setCond(c);
		CAipi_RETE_NumNode::setWM(wm);
		CAipi_RETE_NumNode::setBM(bm);
		CAipi_RETE_NumNode::setTK(oldtk);
		
		m_Data  = dat;
		
	}

	inline void CAipi_RETE_TypeFloat::setPM(int pm)
	{
		CAipi_RETE_NumNode::setPM(pm);
	}

	
	inline void CAipi_RETE_TypeFloat::setCond(int c)
	{
		CAipi_RETE_NumNode::setCond(c);
	}

	
	inline void CAipi_RETE_TypeFloat::setData(float dat)
	{
		m_Data = dat;

	}
	
	inline void CAipi_RETE_TypeFloat::setWM(int wm)
	{
		
		CAipi_RETE_NumNode::setWM(wm);
	}

	inline void CAipi_RETE_TypeFloat::setBM(int bm)
	{
		
		CAipi_RETE_NumNode::setBM(bm);
	}

	inline void CAipi_RETE_TypeFloat::setTK(int oldtk)
	{
		
		CAipi_RETE_NumNode::setTK(oldtk);
	}
	

	inline int CAipi_RETE_TypeFloat::getPM()
	{
		return CAipi_RETE_NumNode::m_PM;
	}

	
	inline int CAipi_RETE_TypeFloat::getCond()
	{
		return CAipi_RETE_NumNode::m_Cond;
	}

	inline float CAipi_RETE_TypeFloat::getData()
	{
		return m_Data;
	}

	inline float CAipi_RETE_TypeFloat::getWM()
	{
		return CAipi_RETE_NumNode::m_WM;
	}

	inline float CAipi_RETE_TypeFloat::getBM()
	{
		return CAipi_RETE_NumNode::m_BM;
	}
	
	inline float CAipi_RETE_TypeFloat::getTK()
	{
		return CAipi_RETE_NumNode::m_TK;
	}
	
	
public:
	CAipi_RETE_TypeFloat* CAipi_RETE_TypeFloat::addTypeFloat(tstring var, int pm, int c, float dat, int wm, int bm, int oldtk);
	void	clearTypeFloat();
	void	printTypeFloat();


public:

	float	m_Data;
	int		m_Cond;
	int		m_PM;
	int		m_WM;
	int     m_BM;
	int     m_TK;
	
	

};

#endif // !defined(AFX_AIPI_RETE_TYPEFLOAT_H__46B9506A_2200_46F8_BC72_49E2B4D67384__INCLUDED_)
