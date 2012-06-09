// Aipi_RETE_TypeDouble.h: interface for the CAipi_RETE_TypeDouble class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_TYPEDOUBLE_H__1440C230_2A65_4865_BE32_11292560D350__INCLUDED_)
#define AFX_AIPI_RETE_TYPEDOUBLE_H__1440C230_2A65_4865_BE32_11292560D350__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_RETE_NumNode.h"

//This class saves information about numeric opeartions in the RETE Network
//In this case Operations between large floating numeric types (double)
//Type : DOUBLE

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
class CAipi_RETE_TypeDouble  : public CAipi_RETE_NumNode 
{
public:
	CAipi_RETE_TypeDouble();
	virtual ~CAipi_RETE_TypeDouble();

	inline CAipi_RETE_TypeDouble(int pm, int c,  double dat, int wm, int bm, int old_tk)
	{
		CAipi_RETE_NumNode::setPM(pm);
		CAipi_RETE_NumNode::setCond(c);
		CAipi_RETE_NumNode::setWM(wm);
		CAipi_RETE_NumNode::setBM(bm);
		CAipi_RETE_NumNode::setTK(old_tk);
		
		m_Data  = dat;
		
	}

	
	
	inline void CAipi_RETE_TypeDouble::setPM(int pm)
	{
		CAipi_RETE_NumNode::setPM(pm);
	}

	inline void CAipi_RETE_TypeDouble::setCond(int c)
	{
		CAipi_RETE_NumNode::setCond(c);
	}

	inline void CAipi_RETE_TypeDouble::setData(double dat)
	{
		m_Data = dat;
	}

	inline void CAipi_RETE_TypeDouble::setWM(int wm)
	{
		CAipi_RETE_NumNode::setWM(wm);
	}
	
	inline void CAipi_RETE_TypeDouble::setBM(int bm)
	{
		CAipi_RETE_NumNode::setBM(bm);
	}	

	inline void CAipi_RETE_TypeDouble::setTK(int oldtk)
	{
		CAipi_RETE_NumNode::setTK(oldtk);
	}
	


	inline int CAipi_RETE_TypeDouble::getPM()
	{
		return CAipi_RETE_NumNode::m_PM;
	}

	inline int CAipi_RETE_TypeDouble::getCond()
	{
		return CAipi_RETE_NumNode::m_Cond;
	}

	inline double CAipi_RETE_TypeDouble::getData()
	{
		return m_Data;
	}

	inline double CAipi_RETE_TypeDouble::getWM()
	{
		return CAipi_RETE_NumNode::m_WM;
	}
	
	inline double CAipi_RETE_TypeDouble::getBM()
	{
		return CAipi_RETE_NumNode::m_BM;
	}
	
	inline double CAipi_RETE_TypeDouble::getTK()
	{
		return CAipi_RETE_NumNode::m_TK;
	}
	
public:
	CAipi_RETE_TypeDouble* CAipi_RETE_TypeDouble::addTypeDouble(tstring var, int pm, int c, double dat, int wm, int bm, int oldtk);
	
	void  clearTypeDouble();	
	void  printTypeDouble();


public:

	double	m_Data;
	int		m_Cond;
	int		m_PM;
	int		m_WM;
	int		m_BM;
	int     m_TK;
		

};

#endif // !defined(AFX_AIPI_RETE_TYPEDOUBLE_H__1440C230_2A65_4865_BE32_11292560D350__INCLUDED_)
