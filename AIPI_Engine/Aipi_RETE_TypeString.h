// Aipi_RETE_TypeString.h: interface for the CAipi_RETE_TypeString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_TYPESTRING_H__8BC35F1F_1016_478C_A083_9A142F69C9FA__INCLUDED_)
#define AFX_AIPI_RETE_TYPESTRING_H__8BC35F1F_1016_478C_A083_9A142F69C9FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_RETE_NumNode.h"

//This class saves information about numeric opeartions in the RETE Network
//In this case Operations between string data types
//Type : STRING

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



class CAipi_RETE_TypeString : public CAipi_RETE_NumNode
{

public:
	CAipi_RETE_TypeString();
	virtual ~CAipi_RETE_TypeString();

	inline CAipi_RETE_TypeString(int pm, int c, tstring dat, int wm, int bm, int old_tk)
	{
		CAipi_RETE_NumNode::setPM(pm);
		CAipi_RETE_NumNode::setCond(c);
		CAipi_RETE_NumNode::setWM(wm);
		CAipi_RETE_NumNode::setBM(bm);
		CAipi_RETE_NumNode::setTK(old_tk);
		
		m_Data  = dat;
	}

	inline void CAipi_RETE_TypeString::setPM(int pm)
	{
		CAipi_RETE_NumNode::setPM(pm);
	}

	
	inline void CAipi_RETE_TypeString::setCond(int c)
	{
		CAipi_RETE_NumNode::setCond(c);
	}

	
	inline void CAipi_RETE_TypeString::setData(tstring dat)
	{
		m_Data = dat;

	}
	
	inline void CAipi_RETE_TypeString::setWM(int wm)
	{
		CAipi_RETE_NumNode::setWM(wm);
	}

	inline void CAipi_RETE_TypeString::setBM(int bm)
	{
		CAipi_RETE_NumNode::setBM(bm);
	}

	inline void CAipi_RETE_TypeString::setTK(int old_tk)
	{
		CAipi_RETE_NumNode::setTK(old_tk);
	}


	inline int CAipi_RETE_TypeString::getPM()
	{
		return CAipi_RETE_NumNode::m_PM;
	}
	
	inline int CAipi_RETE_TypeString::getCond()
	{
		return CAipi_RETE_NumNode::m_Cond;
	}

	inline tstring CAipi_RETE_TypeString::getData()
	{
		return m_Data;
	}

	inline int CAipi_RETE_TypeString::getWM()
	{
		return CAipi_RETE_NumNode::m_WM;
	}

	inline int CAipi_RETE_TypeString::getBM()
	{
		return CAipi_RETE_NumNode::m_BM;
	}

	inline int CAipi_RETE_TypeString::getTK()
	{
		return CAipi_RETE_NumNode::m_TK;
	}
	
	
public:
	CAipi_RETE_TypeString* CAipi_RETE_TypeString::addTypeString(tstring var, int pm, int c, tstring dat, int wm, int bm, int oldtk);
	
	void  clearTypeString();
	void  printTypeString();


public:

	tstring	m_Data;
	int		m_Cond;
	int		m_PM;
	int		m_WM;
	int		m_BM;
	int		m_TK;


};

#endif // !defined(AFX_AIPI_RETE_TYPESTRING_H__8BC35F1F_1016_478C_A083_9A142F69C9FA__INCLUDED_)
