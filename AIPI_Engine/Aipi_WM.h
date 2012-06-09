// Aipi_WM.h: interface for the CAipi_WM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_WM_H__ED2448BA_CC41_49B4_8C33_08AFB8E064FC__INCLUDED_)
#define AFX_AIPI_WM_H__ED2448BA_CC41_49B4_8C33_08AFB8E064FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*
	Working Memory (WM)
	The working memory save all the facts used in the inference engine.

	*** Symbols ***
	WM		= Working Memory
	I	= Identifier (Id)   
	A	= Atribute (Attr)  
	V	= Value (Val)
	
	*** Function Parameters ***
	wm		= Working Memory
	wm1		= Working Memory 1 (different PM of pm2)
	wm2		= Working Memory 2 (different PM of pm1)
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

class CAipi_WM  
{

public:
	CAipi_WM();
	virtual ~CAipi_WM();

	inline CAipi_WM( tstring id, tstring attr, tstring val, int type)
	{
		m_Id = id;
		m_Attr = attr;
		m_Val = val;
		m_Type = type;
		m_Time = 0;
			
	}

	inline CAipi_WM( long id_iform, long attr_iform, long val_iform, tstring id, tstring attr, tstring val, int type)
	{
		m_IdIForm	= id_iform;
		m_AttrIForm	= attr_iform;
		m_ValIForm	= val_iform;
		m_Id = id;
		m_Attr = attr;
		m_Val = val;
		m_Type = type;
		m_Time = 0;
			
	}

	///Sets
	inline void CAipi_WM::setIdIForm(long id_iform)
	{
		m_IdIForm = id_iform;
	}


	inline void CAipi_WM::setAttrIForm(long attr_iform)
	{
		m_AttrIForm = attr_iform;
	}

	inline void CAipi_WM::setValIForm(long val_iform)
	{
		m_ValIForm = val_iform;
	}


	inline void CAipi_WM::setId(tstring id)
	{
		m_Id = id;
	}


	inline void CAipi_WM::setAttr(tstring attr)
	{
		m_Attr = attr;
	}

	inline void CAipi_WM::setVal(tstring val)
	{
		m_Val = val;
	}

	
	inline void CAipi_WM::setType(int type)
	{
		m_Type = type;
	}
	
	inline void CAipi_WM::setTime(int time)
	{
		m_Time = time;
	}


	

	//Gets
	inline long CAipi_WM::getIdIForm()
	{
		return m_IdIForm;
	}


	inline long CAipi_WM::getAttrIForm()
	{
		return m_AttrIForm;
	}

	inline long CAipi_WM::getValIForm()
	{
		return m_ValIForm;
	}

	inline tstring CAipi_WM::getId()
	{
		return m_Id;
	}


	inline tstring CAipi_WM::getAttr()
	{
		return m_Attr;
	}

	inline tstring CAipi_WM::getVal()
	{
		return m_Val;
	}

	inline int CAipi_WM::getType()
	{
		return m_Type;
	}

	inline int CAipi_WM::getTime()
	{
		return m_Time;
	}
	

public:
	long		m_IdIForm;
	long		m_AttrIForm;
	long		m_ValIForm;
	tstring		m_Id;
	tstring		m_Attr;
	tstring		m_Val;
	int			m_Type;
	int			m_Time;
	
////////////////////////////////////
/// Internal Form functions ///
////////////////////////////////////
	CAipi_WM*	addWMIForm(int wm, double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int type, int time);
	int			editWMIForm(int wm, double id_iform, double attr_iform, double val_iform, tstring id, tstring attr, tstring val, int type);
	
	int			insertEQ_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform);
	int			insertET_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform);
	
	int			insertNE_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform);
	int			insertGT_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform);
	int			insertGE_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform);
	int			insertLT_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform);
	int			insertLE_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform);
	int			insertAS_WM_CondIForm(int c, double id_iform, double attr_iform, double val_iform);

	double		findWMIdIForm( int wm );
	double		findWMAttrIForm( int wm );
	double		findWMValIForm( int wm );
	int			findWMMembersIForm( int wm );
	void		printWMIForm();
	bool		compareEqualWMIForm(int wm1, int wm2);



////////////////////////////////////////
/// String Form Functions ////
///////////////////////////////////////	
	CAipi_WM*	addWM(int wm, tstring id, tstring attr, tstring val, int type, int time);
	int			editWM(int wm, tstring id, tstring attr, tstring val, int type);
	
	int			insertEQ_WM_Cond(int c, tstring id, tstring attr, tstring val);
	int			insertET_WM_Cond(int c, tstring id, tstring attr, tstring val);
	int			insertNE_WM_Cond(int c, tstring id, tstring attr, tstring val);
	int			insertGT_WM_Cond(int c, tstring id, tstring attr, tstring val);
	int			insertGE_WM_Cond(int c, tstring id, tstring attr, tstring val);
	int			insertLT_WM_Cond(int c, tstring id, tstring attr, tstring val);
	int			insertLE_WM_Cond(int c, tstring id, tstring attr, tstring val);
	int			insertAS_WM_Cond(int c, tstring id, tstring attr, tstring val);

	int			eraseWM(int wm);
	void		clearWM();
	void		clearWMCondStructs();
	void        clearCondWMStructs(); 
	
	tstring		findWMId( int wm );
	tstring		findWMAttr( int wm );
	tstring		findWMVal( int wm );
	int			findWMType(int wm);
	int			findWMTime(int wm);
	int			findWMMembers( int wm );
	int			findWM(double id, double attr, double val);

	//Searchs for constant data
	int			findEQ_Cond_WM(int c);
	int			findET_Cond_WM(int c);
	int			findNE_Cond_WM(int c);
	int			findGT_Cond_WM(int c);
	int			findGE_Cond_WM(int c);
	int			findLT_Cond_WM(int c);
	int			findLE_Cond_WM(int c);
	int			findAS_Cond_WM(int c);
	

	int			sizeWM();
	int			lastWM();
	int			lastWMTime();
	
	
	void		printWM();
	void		printEQ_WM_Cond();
	void		printET_WM_Cond();
	void		printNE_WM_Cond();
	void		printGT_WM_Cond();
	void		printGE_WM_Cond();
	void		printLT_WM_Cond();
	void		printLE_WM_Cond();
	void		printAS_WM_Cond();

	void		printEQ_Cond_WM();
	void		printET_Cond_WM();
	void		printNE_Cond_WM();
	void		printGT_Cond_WM();
	void		printGE_Cond_WM();
	void		printLT_Cond_WM();
	void		printLE_Cond_WM();
	void		printAS_Cond_WM();
	
	
	bool		compareEqualWM(int wm1, int wm2);

	void		SamplesRETE();
	void		SamplesPumpingStation();
	void		SamplesNegated();
	void		SamplesConjuntiveNegations();
	void		SamplesNumeric();
	void		SamplesOrder();
	void		SamplesDuplicateAttr();
	void		SamplesBlockWord();
	void		SamplesOPS5();
	void		SamplesPerformance();


public:
		

};

#endif // !defined(AFX_AIPI_WM_H__ED2448BA_CC41_49B4_8C33_08AFB8E064FC__INCLUDED_)
