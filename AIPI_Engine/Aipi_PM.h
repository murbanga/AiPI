// Aipi_PM.h: interface for the CAipi_PM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_PM_H__BD1B5D6A_573E_40F0_935F_8AFC6065F704__INCLUDED_)
#define AFX_AIPI_PM_H__BD1B5D6A_573E_40F0_935F_8AFC6065F704__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_LHS.h"
#include "Aipi_RHS.h"

/*

	*** Symbols ***
	PM		= Production Memory
	NN		= Negated Node	
	Cond	= Condition
	Name	= Production Name

	*** Function Parameters ***
	pm		= Production Memory
	pm1		= Production Memory 1 (different PM of pm2)
	pm2		= Production Memory 2 (different PM of pm1)
	lhs		= Left Hand Side Function
	cond	= Condition
	cond1	= Previous Condition of cond2
	cond2	= Next Condition of cond1
	cond11	= Previous Condition of cond2 in Production Memory 1
	cond12	= Next Condition of cond1 in Production Memory 1
	cond21	= Previous Condition of cond2 in Production Memory 2
	cond22	= Next Condition of cond1 in Production Memory 2

*/


class CAipi_PM  
{
public:
	CAipi_PM();
	virtual ~CAipi_PM();


	inline CAipi_PM( tstring name, float cf, int weight)
	{
		m_Name		= name;
		m_CF		= cf;
		m_Weight	= weight;
			
	}

	inline CAipi_PM( tstring name)
	{
		m_Name		= name;
		m_CF		= 1;
		m_Weight	= 0;
			
	}

	inline void CAipi_PM::setName(tstring name)
	{
		m_Name = name;
	}


	inline void CAipi_PM::setCF(float cf)
	{
		m_CF = cf;
	}

	inline void CAipi_PM::setWeight(int weight)
	{
		m_Weight = weight;
	}

	
	inline tstring CAipi_PM::getName()
	{
		return m_Name;
	}


	inline float CAipi_PM::getCF()
	{
		return m_CF;
	}

	inline int CAipi_PM::getWeight()
	{
		return m_Weight;
	}

	



	CAipi_PM*	addPM(long pm, tstring name, float cf, int weight);
	CAipi_PM*	addPM_Name(long pm, tstring name);
	void		addPM_Cond(long pm, int lhs);
	void		addPM_Fact(long pm, int rhs);
	void		addPM_RelCond(long pm, int lhs);
	void		addPM_BM(long pm, int bm);
	void		addPM_PNode(long pm, int pnode);

	void		addPM_IVar(long pm, tstring id);//Saves id variables and their respective pm
	void		addPM_AVar(long pm, tstring attr);//Saves attr variables and their respective pm
	void		addPM_VVar(long pm, tstring val);//Saves val variables and their respective pm

	int     countPM_Cond(long pm);
	int		countPM_BM(long pm);

	int		sizePM_Cond();
	int		sizePM_Fact();
	int		sizePM();

	void	clearPM();
	void	clearPM_Cond();
	void	clearPM_Vars();
	void	clearPMStructs();
	void	erasePM_BM(long pm );
	void	erasePM_Cond(long pm);	
	void	erasePM_PNode(long pm);
	
	//Compare all the conditions of two different productions (pm1 and pm2)
	bool    compareAllCond(long pm1, long pm2);
	//Compare a range of conditions of two different productions (pm1 and pm2)
	bool    compareRangeCond(long pm1, long pm2, int cond11, int cond12, int cond21, int cond22);
	//Compare a range of conditions (including negated conditons) of two different productions (pm1 and pm2)
	bool    compareRangeNNCond(long pm1, long pm2, int cond11, int cond12, int cond21, int cond22);
	
	void	replacePM_Cond(int pm, int cond1, int cond2);

	//Search a condition in all the productions
	int		searchCond(int cond);
	//Search a LHS condition in a especific production
	int		searchCondPM(int cond, int pm);
	//Search a RHS fact in a especific production
	int		searchFactPM(int fact, int pm);
	int		searchRelCondPM(int cond, int pm);
	/*
	int		findLowerCond(int pm);
	int		findUpperCond(int pm);
	*/
	int		PM_CondLowerBound(long pm);
	int		PM_CondUpperBound(long pm);
	int		PM_BMLowerBound(long pm);
	int		PM_BMUpperBound(long pm);
	
	float	findPMCF(long pm);
	int		findPMWeight(long pm);
	int		findPMMembers(long pm);
	int		findPM_BM(int pm, int bm);
	int		findPM_MetaCond(long pm);
	int		findPM_PNode(long pm);
	tstring findPMName(long pm);
	
	
	long	generatePMKey();
	void	fillPM_Cond();
	void	fillPM_Vars(long pm);

	
	void	printPM_Cond();
	void	printPM_Fact();
	void	printPM_RelCond();
	void	printPM_BM();
	void	printPM_PNode();
	void    printPM_IDVar();
	void	printPM_ATTRVar();
	void	printPM_VALVar();
	void	printPM();
	
/////////////////////////////////////////////
	///IForm Functions ///
	//Saves all variables and their respective pm
	//This function is not needed anymore it was sustitute by the 3 functions down
	void	fillPM_VarsIForm(long pm);
	void	addPM_IVarIForm(long pm, long id_iform);//Saves id variables and their respective pm
	void	addPM_AVarIForm(long pm, long attr_iform);//Saves attr variables and their respective pm
	void	addPM_VVarIForm(long pm, long val_iform);//Saves val variables and their respective pm
	void    printPM_IDVarIForm();
	void	printPM_ATTRVarIForm();
	void	printPM_VALVarIForm();
	

public:

	tstring		m_Name;
	float		m_CF;
	int			m_Weight;


};

#endif // !defined(AFX_AIPI_PM_H__BD1B5D6A_573E_40F0_935F_8AFC6065F704__INCLUDED_)
