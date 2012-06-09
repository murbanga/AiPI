// Aipi_RHS.h: interface for the CAipi_RHS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RHS_H__078AB502_B708_4B31_9297_3859DAF30EC8__INCLUDED_)
#define AFX_AIPI_RHS_H__078AB502_B708_4B31_9297_3859DAF30EC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_PM.h"
#include "Aipi_WM.h"


/*
	This class represents the Right Hand Side of the Productions.
	This allso are call the conclusions of the production.
	The left hand side has facts.

	*** Symbols ***
	RHS		= Left Hand Side (Conclusions)
	I		= Identifier (Id)   
	A		= Atribute (Attr)  
	V		= Value (Val)
	Cond	= Condition (LHS Element)
	
	*** Function Parameters ***
	rhs		= Right Hand Side Element (Fact)
	pm		= Production Memory
	type	= Condition Type
	cond1	= Condition 1 (different condition of cond2)
	cond2	= Condition 2 (different condition of cond1)
	id		= Identifier	
	attr	= Attribute
	val		= Value

  *********************************
	NOTE: Working memory elements 
	representation in a more convenient way 
	
	IForm		= Internal Form Representation
	IdIForm		= Identifier Internal Form Representation
	AttrIForm	= Attribute Internal Form Representation
	ValIForm	= Value Internal Form Representation

*/



class CAipi_RHS : public CAipi_WM
{
public:
	CAipi_RHS();
	virtual ~CAipi_RHS();

	inline CAipi_RHS(tstring id, tstring attr, tstring val, int pm, int cmd)
	{
		m_Command   = cmd;
		m_PM		= pm;
		CAipi_WM::setId(id);
		CAipi_WM::setAttr(attr);
		CAipi_WM::setVal(val);
	
	}

	inline CAipi_RHS( double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int pm, int cmd)
	{
		m_Command	= cmd;
		m_PM		= pm;
		CAipi_WM::setIdIForm(id_iform);
		CAipi_WM::setAttrIForm(attr_iform);
		CAipi_WM::setValIForm(val_iform);
	
		CAipi_WM::setId(id);
		CAipi_WM::setAttr(attr);
		CAipi_WM::setVal(val);
	
	}

	
	inline void CAipi_RHS::setIdIForm(double id_iform)
	{
		CAipi_WM::setIdIForm(id_iform);

	}

	inline void CAipi_RHS::setAttrIForm(double attr_iform)
	{
		CAipi_WM::setAttrIForm(attr_iform);
	}

	inline void CAipi_RHS::setValIForm(double val_iform)
	{
		CAipi_WM::setValIForm(val_iform);
	}
	
	inline void CAipi_RHS::setId(tstring id)
	{
		CAipi_WM::setId(id);

	}

	inline void CAipi_RHS::setAttr(tstring attr)
	{
		CAipi_WM::setAttr(attr);
	}

	inline void CAipi_RHS::setVal(tstring val)
	{
		CAipi_WM::setVal(val);
	}
	
	inline void CAipi_RHS::setPM(int pm)
	{
		m_PM = pm;
	}

	inline void CAipi_RHS::setCommand(int cmd)
	{
		m_Command = cmd;

	}

	////////////////////////////////
	//Gets//
	/////////////////////////////////

	inline double CAipi_RHS::getIdIForm()
	{
		return CAipi_WM::getIdIForm();
	}
	

	inline double CAipi_RHS::getAttrIForm()
	{
		return CAipi_WM::getAttrIForm();
	}
	
	inline double CAipi_RHS::getValIForm()
	{
		return CAipi_WM::getValIForm();
	}
	

	inline tstring CAipi_RHS::getId()
	{
		return CAipi_WM::getId();
	}
	

	inline tstring CAipi_RHS::getAttr()
	{
		return CAipi_WM::getAttr();
	}
	
	inline tstring CAipi_RHS::getVal()
	{
		return CAipi_WM::getVal();
	}

	inline int CAipi_RHS::getPM()
	{
		return m_PM;
	}

	inline double CAipi_RHS::getCommand()
	{
		return m_Command;
	}
	
//////////////////////////////////////////
////  Internal Form Functions ////
//////////////////////////////////////////	
	CAipi_RHS*	addRHSIForm(int rhs, double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int pm, int cmd);
	int			editRHSIForm(int rhs, double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int pm, int cmd);
	double		findRHSIdIForm( int rhs );
	double		findRHSAttrIForm( int rhs );
	double		findRHSValIForm( int rhs );
	int			findRHSMembersIForm(int rhs);
	void		printRHSIForm();


//////////////////////////////////////////////

public:
	CAipi_RHS*	addRHS(int rhs, tstring id, tstring attr, tstring val, int pm, int cmd);
	int			execPMFacts(long pm);
	int			execAssert(long pm, double if_id, double if_attr, double if_val, tstring s_id, tstring s_attr, tstring s_val);
	int			execRetract(double if_id, double if_attr, double if_val, tstring s_id, tstring s_attr, tstring s_val);
	int			assertPMFacts(long pm);
	int			retractPMFacts(long pm);
	int			editRHS(int rhs, tstring id, tstring attr, tstring val, int pm, int cmd);
	int			sizeRHS();
	void		clearRHS();
	void		eraseRHS( int rhs);	
	tstring		findRHSId( int rhs );
	tstring		findRHSAttr( int rhs );
	tstring		findRHSVal( int rhs );
	long		findRHSPM( int rhs );
	int			findRHSCommand(int rhs);
	int			findRHSMembers(int rhs);
	void		printRHS();

public:
	double		m_rhsIdIForm;
	double		m_rhsAttrIForm;
	double		m_rhsValIForm;
	tstring     m_rhsId;
	tstring		m_rhsAttr;
	tstring		m_rhsVal;
	int         m_PM;
	int         m_Command;
	
};

#endif // !defined(AFX_AIPI_RHS_H__078AB502_B708_4B31_9297_3859DAF30EC8__INCLUDED_)
