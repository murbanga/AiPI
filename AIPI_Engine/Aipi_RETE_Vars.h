// Aipi_RETE_Vars.h: interface for the CAipi_RETE_Vars class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_VARS_H__8D27EA03_1064_4F28_B651_D638B0F73861__INCLUDED_)
#define AFX_AIPI_RETE_VARS_H__8D27EA03_1064_4F28_B651_D638B0F73861__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//This class saves information about variables in the RETE Network

/*
	*** Symbols ***
	TK		= Token
	AM		= Alpha Memory
	WM		= Working Memory
	PM		= Production Memory
	Var		= Variable
	Cond	= Condition
	Data	= Numeric Value
	Rel		= Relational operator

	I	= Identifier (Id)   
	A	= Atribute (Attr)  
	V	= Value (Val)
	e	= Don`t care
	
	*** Relational Operators ***
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


class CAipi_RETE_Vars  
{
public:
	CAipi_RETE_Vars();
	virtual ~CAipi_RETE_Vars();

	
	inline CAipi_RETE_Vars( int am, int c, int rel, int pm)
	{
		m_AM = am;
		m_Cond = c;
		m_Rel = rel;
		m_PM = pm;
	
	}

	inline void CAipi_RETE_Vars::setAM(int am)
	{
		m_AM = am;
	}

	inline void CAipi_RETE_Vars::setCond(int c)
	{
		m_Cond = c;
	}

	inline void CAipi_RETE_Vars::setRel(int rel)
	{
		m_Rel = rel;
	}

	inline void CAipi_RETE_Vars::setPM(int pm)
	{
		m_PM = pm;
	}
	
	
	inline int CAipi_RETE_Vars::getAM()
	{
		return m_AM;
	}

	inline int CAipi_RETE_Vars::getCond()
	{
		return m_Cond;
	}

	inline int CAipi_RETE_Vars::getRel()
	{
		return m_Rel;
	}

	inline int CAipi_RETE_Vars::getPM()
	{
		return m_PM;
	}
	
	

	CAipi_RETE_Vars* CAipi_RETE_Vars::addVar(tstring var, int f, int am, int c, int rel, int pm);
	

	void		clearVarsStructs();
	
	void		printVar_I();
	void		printVar_A();
	void		printVar_V();
		
	void		printSetIDVar();
	void		printSetVALVar();

	
public:
	int		m_AM;
	int		m_Cond;
	int     m_Rel;
	int     m_PM;
	

};

#endif // !defined(AFX_AIPI_RETE_VARS_H__8D27EA03_1064_4F28_B651_D638B0F73861__INCLUDED_)
