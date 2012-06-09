// Aipi_RETE_TypeInt.h: interface for the CAipi_RETE_TypeInt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_TYPEINT_H__5F0C5698_6F9F_4D7F_A5E4_0AF9987669D2__INCLUDED_)
#define AFX_AIPI_RETE_TYPEINT_H__5F0C5698_6F9F_4D7F_A5E4_0AF9987669D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_RETE_NumNode.h"

//This class saves information about numeric opeartions in the RETE Network
//In this case Operations between integer numeric types
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


class CAipi_RETE_TypeInt : public CAipi_RETE_NumNode 
{
public:
	CAipi_RETE_TypeInt();
	virtual ~CAipi_RETE_TypeInt();

	inline CAipi_RETE_TypeInt(int pm, int c, int dat, int wm, int bm, int old_tk)
	{
		CAipi_RETE_NumNode::setPM(pm);
		CAipi_RETE_NumNode::setCond(c);
		CAipi_RETE_NumNode::setWM(wm);
		CAipi_RETE_NumNode::setBM(bm);
		CAipi_RETE_NumNode::setTK(old_tk);
		
		m_Data  = dat;
		

	}

	inline void CAipi_RETE_TypeInt::setPM(int pm)
	{
		CAipi_RETE_NumNode::setPM(pm);
	}
	
	inline void CAipi_RETE_TypeInt::setCond(int c)
	{
		CAipi_RETE_NumNode::setCond(c);
	}
	
	inline void CAipi_RETE_TypeInt::setData(int dat)
	{
		m_Data = dat;

	}
	
	inline void CAipi_RETE_TypeInt::setWM(int wm)
	{
		CAipi_RETE_NumNode::setWM(wm);

	}
	
	inline void CAipi_RETE_TypeInt::setBM(int bm)
	{
		CAipi_RETE_NumNode::setBM(bm);

	}
	
	inline void CAipi_RETE_TypeInt::setTK(int oldtk)
	{
		CAipi_RETE_NumNode::setTK(oldtk);

	}
	
	inline int CAipi_RETE_TypeInt::getCond()
	{
		return CAipi_RETE_NumNode::m_Cond;
	}


	inline int CAipi_RETE_TypeInt::getPM()
	{
		return CAipi_RETE_NumNode::m_PM;
	}


	inline int CAipi_RETE_TypeInt::getData()
	{
		return m_Data;
	}

	inline int CAipi_RETE_TypeInt::getWM()
	{
		return CAipi_RETE_NumNode::m_WM;
	}
	
	inline int CAipi_RETE_TypeInt::getBM()
	{
		return CAipi_RETE_NumNode::m_BM;
	}
	
	inline int CAipi_RETE_TypeInt::getTK()
	{
		return CAipi_RETE_NumNode::m_TK;
	}
	
	
public:
	CAipi_RETE_TypeInt* CAipi_RETE_TypeInt::addTypeInt(tstring var, int pm, int c, int dat, int wm, int bm, int oldtk);
	void		clearTypeInt();
	void		printTypeInt();


public:

	int		m_Data;
	int		m_Cond;
	int		m_PM;
	int		m_WM;
	int		m_BM;
	int		m_TK;
	



};

#endif // !defined(AFX_AIPI_RETE_TYPEINT_H__5F0C5698_6F9F_4D7F_A5E4_0AF9987669D2__INCLUDED_)
