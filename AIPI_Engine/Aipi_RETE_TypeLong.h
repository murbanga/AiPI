// Aipi_RETE_TypeLong.h: interface for the CAipi_RETE_TypeLong class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_TYPELONG_H__38A0E628_EE94_485E_9F69_1DB393D61CD0__INCLUDED_)
#define AFX_AIPI_RETE_TYPELONG_H__38A0E628_EE94_485E_9F69_1DB393D61CD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_RETE_NumNode.h"

//This class saves information about numeric opeartions in the RETE Network
//In this case Operations between long integers numeric types (long)
//Type : INT

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


class CAipi_RETE_TypeLong : public CAipi_RETE_NumNode 
{
public:
	CAipi_RETE_TypeLong();
	virtual ~CAipi_RETE_TypeLong();

	inline CAipi_RETE_TypeLong(int pm, int c, long dat, int wm, int bm, int old_tk)
	{
		CAipi_RETE_NumNode::setPM(pm);
		CAipi_RETE_NumNode::setCond(c);
		CAipi_RETE_NumNode::setWM(wm);
		CAipi_RETE_NumNode::setBM(bm);
		CAipi_RETE_NumNode::setTK(old_tk);
		
		m_Data  = dat;
	}

	inline void CAipi_RETE_TypeLong::setPM(int pm)
	{
		CAipi_RETE_NumNode::setPM(pm);
	}

	
	inline void CAipi_RETE_TypeLong::setCond(int c)
	{
		CAipi_RETE_NumNode::setCond(c);
	}

	
	inline void CAipi_RETE_TypeLong::setData(long dat)
	{
		m_Data = dat;

	}
	
	inline void CAipi_RETE_TypeLong::setWM(int wm)
	{
		CAipi_RETE_NumNode::setWM(wm);
	}

	inline void CAipi_RETE_TypeLong::setBM(int bm)
	{
		CAipi_RETE_NumNode::setBM(bm);
	}

	inline void CAipi_RETE_TypeLong::setTK(int old_tk)
	{
		CAipi_RETE_NumNode::setTK(old_tk);
	}



	inline int CAipi_RETE_TypeLong::getPM()
	{
		return CAipi_RETE_NumNode::m_PM;
	}
	
	inline int CAipi_RETE_TypeLong::getCond()
	{
		return CAipi_RETE_NumNode::m_Cond;
	}

	inline long CAipi_RETE_TypeLong::getData()
	{
		return m_Data;
	}

	inline int CAipi_RETE_TypeLong::getWM()
	{
		return CAipi_RETE_NumNode::m_WM;
	}

	inline int CAipi_RETE_TypeLong::getBM()
	{
		return CAipi_RETE_NumNode::m_BM;
	}

	inline int CAipi_RETE_TypeLong::getTK()
	{
		return CAipi_RETE_NumNode::m_TK;
	}
	
	
public:
	CAipi_RETE_TypeLong* CAipi_RETE_TypeLong::addTypeLong(tstring var, int pm, int c, long dat, int wm, int bm, int oldtk);
	void  clearTypeLong();	
	void  printTypeLong();


public:

	long	m_Data;
	int		m_Cond;
	int		m_PM;
	int		m_WM;
	int		m_BM;
	int		m_TK;



};

#endif // !defined(AFX_AIPI_RETE_TYPELONG_H__38A0E628_EE94_485E_9F69_1DB393D61CD0__INCLUDED_)
