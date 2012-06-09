// Aipi_RETE_NumVars.h: interface for the CAipi_RETE_NumVars class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_NUMVARS_H__8F1735AB_14D3_4F01_B525_8B06292FB73F__INCLUDED_)
#define AFX_AIPI_RETE_NUMVARS_H__8F1735AB_14D3_4F01_B525_8B06292FB73F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAipi_RETE_NumVars  
{
public:
	CAipi_RETE_NumVars();
	virtual ~CAipi_RETE_NumVars();

	inline CAipi_RETE_NumVars(tstring assign_var, tstring var, tstring data1, tstring data2, int wm, int bm)
	{
		m_AssignVar	= assign_var;
		m_Var		= var;
		m_Data1		= data1;
		m_Data2		= data2;
		m_WM		= wm;
		m_BM		= bm;
			
	}

		
	inline void CAipi_RETE_NumVars::setAssignVar(tstring assign_var)
	{
		m_AssignVar = assign_var;

	}

	inline void CAipi_RETE_NumVars::setVar(tstring var)
	{
		m_Var = var;

	}

	inline void CAipi_RETE_NumVars::setData1(tstring data1)
	{
		m_Data1 = data1;
	}

	inline void CAipi_RETE_NumVars::setData2(tstring data2)
	{
		m_Data2 = data2;
	}

	inline void CAipi_RETE_NumVars::setWM(int wm)
	{
		m_WM = wm;
	}
	
	inline void CAipi_RETE_NumVars::setBM(int bm)
	{
		m_BM = bm;
	}

		
	
	
	inline tstring CAipi_RETE_NumVars::getAssignVar()
	{
		return m_AssignVar;
	}
	
	
	inline tstring CAipi_RETE_NumVars::getVar()
	{
		return m_Var;
	}

	inline tstring CAipi_RETE_NumVars::getData1()
	{
		return m_Data1;
	}

	inline tstring CAipi_RETE_NumVars::getData2()
	{
		return m_Data2;
	}

	inline int CAipi_RETE_NumVars::getWM()
	{
		return m_WM;
	}

	inline int CAipi_RETE_NumVars::getBM()
	{
		return m_BM;
	}


public:	
	CAipi_RETE_NumVars* addTK_LeftV(int child_tk, tstring assign_var, tstring var, tstring data1, tstring data2, int wm, int bm);
	CAipi_RETE_NumVars* addTK_RightV(int child_tk, tstring assign_var, tstring var, tstring data1, tstring data2, int wm, int bm);
	void	addNumVar_BM(tstring var, int bm);	
	void	clearNumVar_BM();
	void	clearTK_LeftV();
	void	clearTK_RightV();
	void	clearNumVarStructs();
	int		findNumVar_BM(tstring var);
	void	printTK_LeftV();
	void	printTK_RightV();
	void	printNumVar_BM();


public:

	int		m_WM;
	int		m_BM;
	tstring	m_AssignVar; 
	tstring m_Var;
	tstring m_Data1;
	tstring m_Data2;
	 



};

#endif // !defined(AFX_AIPI_RETE_NUMVARS_H__8F1735AB_14D3_4F01_B525_8B06292FB73F__INCLUDED_)
