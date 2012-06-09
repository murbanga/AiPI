// Aipi_RETE_JNode.h: interface for the CAipi_RETE_JNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_JNODE_H__6C7AA744_3B2C_4F2D_A666_0AEA379749B5__INCLUDED_)
#define AFX_AIPI_RETE_JNODE_H__6C7AA744_3B2C_4F2D_A666_0AEA379749B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*
	/// Join Node (JNode) ///
This class represents the nodes that connect the RETE network with AM and BM.


	*** Symbols ***
	AM		= Alpha Memory
	BM		= Beta Memory
	WM		= Working Memory
	PM		= Production Memory
	Cond	= Condition
	f1		= Field1 
	f2		= Field2
	
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

class CAipi_RETE_JNode  
{
public:
	CAipi_RETE_JNode();
	virtual ~CAipi_RETE_JNode();

	inline CAipi_RETE_JNode(int c1, int f1, int c2, int f2, int pm, tstring var)
	{
		m_Cond1 = c1;
		m_Field1 = f1;
		m_Cond2 = c2;
		m_Field2 = f2;
		m_PM	= pm;
		m_Var	= var;
	}

	
	inline void CAipi_RETE_JNode::setCond1(int c1)
	{
		m_Cond1 = c1;

	}

	inline void CAipi_RETE_JNode::setField1(int f1)
	{
		m_Field1 = f1;
	}


	inline void CAipi_RETE_JNode::setCond2(int c2)
	{
		m_Cond2 = c2;
	}

	inline void CAipi_RETE_JNode::setField2(int f2)
	{
		m_Field2 = f2;
	}

	inline void CAipi_RETE_JNode::setPM(int pm)
	{
		m_PM = pm;

	}

	inline void CAipi_RETE_JNode::setVar(tstring var)
	{
		m_Var = var;

	}

	
	inline int CAipi_RETE_JNode::getCond1()
	{
		return m_Cond1;
	}
	
	
	inline int CAipi_RETE_JNode::getField1()
	{
		return m_Field1;
	}


	inline int CAipi_RETE_JNode::getCond2()
	{
		return m_Cond2;
	}

	inline int CAipi_RETE_JNode::getField2()
	{
		return m_Field2;
	}

	
	inline int CAipi_RETE_JNode::getPM()
	{
		return m_PM;
	}

	
	inline tstring CAipi_RETE_JNode::getVar()
	{
		return m_Var;
	}


public:

	
	CAipi_RETE_JNode* CAipi_RETE_JNode::addJN(int jn, int c1, int f1, int c2, int f2, int pm, tstring var); 
	
	int		editJN(	int jn, int c1, int f1, int c2, int f2, int pm, tstring var);		
	int		findJNMembers(int jn);
	int		findJNCond1(int jn);
	int		findJNCond2(int jn);
	int		findJNField1(int jn);
	int		findJNField2(int jn);
	int		findJNPM(int jn);
	
	tstring findJNVar(int jn);
	
	int		searchJNCond1(int c1);
	int		searchJNCond2(int c2);

	void	clearJNStructs();
	void	eraseJN(int jn);
	int		sizeJNode();
	
	
	void	fillJN();
	void	printJN();
	
	int		generateJNKey();
	
	int countBM_ChildJN(int b);

public:
	int		m_Cond1;
	int		m_Cond2;
	int		m_Field1;
	int		m_Field2;
	int		m_PM;
	tstring	m_Var;

};

#endif // !defined(AFX_AIPI_RETE_JNODE_H__6C7AA744_3B2C_4F2D_A666_0AEA379749B5__INCLUDED_)
