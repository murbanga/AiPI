// Aipi_LHS.h: interface for the CAipi_LHS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_LHS_H__3327B41A_52C3_44D5_BF72_2D5C2B007310__INCLUDED_)
#define AFX_AIPI_LHS_H__3327B41A_52C3_44D5_BF72_2D5C2B007310__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Aipi_PM.h"
#include "Aipi_WM.h"
#include "Aipi_RETE_NNode.h"
#include "Aipi_RETE_NCCNode.h"

/*
	This class represents the Left Hand Side of the Productions
	This allso are call the premises of the production
	The left hand side has conditions

	*** Symbols ***
	LHS		= Left Hand Side (Premises)
	I		= Identifier (Id)   
	A		= Atribute (Attr)  
	V		= Value (Val)
	Cond	= Condition (LHS Element)
	
	*** Function Parameters ***
	lhs		= Left Hand Side Element (Condition)
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


class CAipi_LHS : public CAipi_WM  
{
public:
	CAipi_LHS();
	virtual ~CAipi_LHS();

	inline CAipi_LHS(tstring id, tstring attr, tstring val, int rel, int pm, int categ)
	{
		m_Rel		= rel;
		m_PM		= pm;
		m_Category	= categ;
				
		CAipi_WM::setId(id);
		CAipi_WM::setAttr(attr);
		CAipi_WM::setVal(val);
	
	}

	inline CAipi_LHS(double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int rel, int pm, int categ)
	{
		m_Rel		= rel;
		m_PM		= pm;
		m_Category	= categ;
		
		CAipi_WM::setIdIForm(id_iform);
		CAipi_WM::setAttrIForm(attr_iform);
		CAipi_WM::setValIForm(val_iform);
	
		CAipi_WM::setId(id);
		CAipi_WM::setAttr(attr);
		CAipi_WM::setVal(val);
	
	}

	inline void CAipi_LHS::setIdIForm(double id_iform)
	{
		CAipi_WM::setIdIForm(id_iform);

	}

	inline void CAipi_LHS::setAttrIForm(double attr_iform)
	{
		CAipi_WM::setAttrIForm(attr_iform);
	}

	inline void CAipi_LHS::setValIForm(double val_iform)
	{
		CAipi_WM::setValIForm(val_iform);
	}
	
	inline void CAipi_LHS::setId(tstring id)
	{
		CAipi_WM::setId(id);

	}

	inline void CAipi_LHS::setAttr(tstring attr)
	{
		CAipi_WM::setAttr(attr);
	}

	inline void CAipi_LHS::setVal(tstring val)
	{
		CAipi_WM::setVal(val);
	}
	
	inline void CAipi_LHS::setRel(int rel)
	{
		m_Rel = rel;
	}

	inline void CAipi_LHS::setPM(int pm)
	{
		m_PM = pm;
	}

	inline void CAipi_LHS::setCategory(int categ)
	{
		m_Category = categ;
	}
	

	inline double CAipi_LHS::getIdIForm()
	{
		return CAipi_WM::getIdIForm();
	}
	

	inline double CAipi_LHS::getAttrIForm()
	{
		return CAipi_WM::getAttrIForm();
	}
	
	inline double CAipi_LHS::getValIForm()
	{
		return CAipi_WM::getValIForm();
	}
	

	inline tstring CAipi_LHS::getId()
	{
		return CAipi_WM::getId();
	}
	

	inline tstring CAipi_LHS::getAttr()
	{
		return CAipi_WM::getAttr();
	}
	
	inline tstring CAipi_LHS::getVal()
	{
		return CAipi_WM::getVal();
	}

	inline int CAipi_LHS::getRel()
	{
		return m_Rel;
	}


	inline int CAipi_LHS::getPM()
	{
		return m_PM;
	}

	inline int CAipi_LHS::getCategory()
	{
		return m_Category;
	}

//////////////////////////////////////////
////  Internal Form Functions ////
//////////////////////////////////////////	
	CAipi_LHS*	addLHSIForm(int lhs, double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int rel, int pm, int categ);
	int			editLHSIForm(int lhs, double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int rel, int pm, int categ);
	double		findLHSIdIForm( int lhs );
	double		findLHSAttrIForm( int lhs );
	double		findLHSValIForm( int lhs );
	int			findLHSMembersIForm( int lhs );

	bool		compareEqualCondIForm(int cond1, int cond2);
	void		printLHSIForm();


/////////////////////////////////////////////

	CAipi_LHS*	addLHS(int lhs, tstring id, tstring attr, tstring val, int rel, int pm, int categ);
	int			editLHS(int lhs, tstring id, tstring attr, tstring val, int rel, int pm, int categ);
	
	 
	tstring		findLHSId( int lhs );
	tstring		findLHSAttr( int lhs );
	tstring		findLHSVal( int lhs );
	int			findLHSRel( int lhs );
	int			findLHSPM( int lhs );
	int			findLHSCategory(int lhs);
	int			findLHSMembers( int lhs );
	
	int			searchFirstLHS_PMId(int pm, tstring id);
	int			searchFirstLHS_PMAttr(int pm, tstring attr);
	int			searchFirstLHS_PMVal(int pm, tstring val);
	int			searchLHS_PMIdAfterCond(int pm, tstring id, int c);
	int			searchLHS_PMAttrAfterCond(int pm, tstring attr, int c);
	int			searchLHS_PMValAfterCond(int pm, tstring val, int c);
	
	
	int			sizeLHS();
	int			lastLHS();
	
	int			variableTest(int lhs);
	bool		compareEqualCond(int cond1, int cond2);
	void		clearLHS();
	void		eraseLHS(int lhs);

	
	void		SamplesPerformance();
	void		SamplesOPS5();
	void		SamplesBlockWord();
	void		SamplesPumpingStation();
	void		SamplesRETE();
	void		SamplesDuplicateAttr();
	void		SamplesConstantAttr();
	void		SamplesOrder();
	void		SamplesNumeric();
	void		SamplesStringRelational();
	void		SamplesAlphaNet();
	void		SamplesNegated();
	void		SamplesConjuntiveNegations();
	void		printLHS();
	void		printRepCond();
	


	
	



public:

/*
	//Repeated Conditions
	//Key = First Condition
	//Value = Repeated Conditions for the Key Condition
	typedef std::multimap<int, int> m_mmRepCond;
	m_mmRepCond	mmRepCond;

	vector <int> m_vRepCond;
*/

	double		m_lhsIdIForm;
	double		m_lhsAttrIForm;
	double		m_lhsValIForm;
	tstring     m_lhsId;
	tstring		m_lhsAttr;
	tstring		m_lhsVal;
	int			m_Rel;
	int         m_PM;
	int			m_Category;


};



#endif // !defined(AFX_AIPI_LHS_H__3327B41A_52C3_44D5_BF72_2D5C2B007310__INCLUDED_)
