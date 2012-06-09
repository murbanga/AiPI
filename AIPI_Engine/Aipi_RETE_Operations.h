// Aipi_RETE_Operations.h: interface for the CAipi_RETE_Operations class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_OPERATIONS_H__BAC9821A_1B0C_4A2D_91D6_DC2947E85019__INCLUDED_)
#define AFX_AIPI_RETE_OPERATIONS_H__BAC9821A_1B0C_4A2D_91D6_DC2947E85019__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
	/// Operations (RETE Operations) ///
This is a helper class that saves information for numeric operations.
It will be helpfull to check consistent between attibutes data types in the debbuging process. 	


	*** Symbols ***
	LeftVar	= Variable that is left from the operator
	RightVar= Variable that is right form the operator
	AttrType= The identifier type ( int  ,long string etc...)
	AM		= Alpha Memory
	BM		= Beta Memory
	WM		= Working Memory
	PM		= Production Memory
	Cond	= Condition
	
	I	= Identifier (Id)   
	A	= Atribute (Attr)  
	V	= Value (Val)
	e	= Don`t care
	


	*** Function Parameters ***
	am		= Alpha Memory
	bm		= Beta Memory
	wm		= Working Memory
	pm		= Production Memory
	lhs		= Left Hand Side Function
	cond	= Condition
	
*/
class CAipi_RETE_Operations  
{
public:
	CAipi_RETE_Operations();
	virtual ~CAipi_RETE_Operations();

	inline CAipi_RETE_Operations(int c, tstring v1, tstring v2, int type1, int type2, int rel)
	{
		m_Cond		= c;
		m_LeftVar	= v1;
		m_RightVar	= v2;
		m_LeftType	= type1;
		m_RightType = type2;
		m_Rel		= rel;
	}

	
	
	inline void CAipi_RETE_Operations::setCond(int c)
	{
		m_Cond = c;
	}

	inline void CAipi_RETE_Operations::setLeftVar(tstring v1)
	{
		m_LeftVar = v1;
	}
	
	inline void CAipi_RETE_Operations::setRightVar(tstring v2)
	{
		m_RightVar = v2;
	}
	
	inline void CAipi_RETE_Operations::setLeftType(int type1)
	{
		m_LeftType = type1;

	}
	
	inline void CAipi_RETE_Operations::setRightType(int type2)
	{
		m_RightType = type2;

	}
	inline void CAipi_RETE_Operations::setRel(int rel)
	{
		m_Rel = rel;;
	}

	

		

	
	inline int CAipi_RETE_Operations::getCond()
	{
		return m_Cond;
	}

	inline tstring CAipi_RETE_Operations::getLeftVar()
	{
		return m_LeftVar;
	}

	inline tstring CAipi_RETE_Operations::getRightVar()
	{
		return m_RightVar;
	}

	inline int CAipi_RETE_Operations::getLeftType()
	{
		return m_LeftType;
	}
	
	inline int CAipi_RETE_Operations::getRightType()
	{
		return m_RightType;
	}

	inline int CAipi_RETE_Operations::getRel()
	{
		return m_Rel;
	}
	
public:
	CAipi_RETE_Operations* CAipi_RETE_Operations::addOperation(int pm, int c, tstring v1, tstring v2, int type1, int type2, int rel);
	void    clearOperation();
	void	addAttr_Type(tstring attr, int type);
	void    clearAttrType();
	int		findAttr_Type(tstring attr);
	void	printOperation();
	void	printAttr_Type();


public:

	int		m_Cond;
	int		m_LeftType;
	int		m_RightType;
	int		m_Rel;
	tstring	m_LeftVar;
	tstring	m_RightVar;

};

#endif // !defined(AFX_AIPI_RETE_OPERATIONS_H__BAC9821A_1B0C_4A2D_91D6_DC2947E85019__INCLUDED_)
