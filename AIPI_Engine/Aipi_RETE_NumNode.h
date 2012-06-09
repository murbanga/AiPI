// Aipi_RETE_NumNode.h: interface for the CAipi_RETE_NumNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_NUMNODE_H__BE4E8579_41CA_4471_8771_8CC2AD83E2DE__INCLUDED_)
#define AFX_AIPI_RETE_NUMNODE_H__BE4E8579_41CA_4471_8771_8CC2AD83E2DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_RETE_Node.h"

/*
	/// Numeric Node (NumNode) ///
This is a virtual class for numeric tested in the RETE Network.



	*** Symbols ***
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

class CAipi_RETE_NumNode : public CAipi_RETE_Node  
{
public:
	CAipi_RETE_NumNode();
	virtual ~CAipi_RETE_NumNode();

	inline CAipi_RETE_NumNode(int pm, int c, int bm, int wm, int tk, tstring var)
	{
		m_PM	= pm;
		m_Cond	= c;
		m_BM	= bm;
		m_WM	= wm;
		m_TK	= tk;
		m_Var	= var;	
	}

	
	
	inline void CAipi_RETE_NumNode::setPM(int pm)
	{
		m_PM = pm;

	}

	inline void CAipi_RETE_NumNode::setCond(int c)
	{
		m_Cond = c;
	}

	inline void CAipi_RETE_NumNode::setBM(int bm)
	{
		m_BM = bm;
	}

	inline void CAipi_RETE_NumNode::setWM(int wm)
	{
		m_WM = wm;
	}

	inline void CAipi_RETE_NumNode::setTK(int tk)
	{
		m_TK = tk;
	}

	inline void CAipi_RETE_NumNode::setVar(tstring var)
	{
		m_Var = var;
	}

	
	
	
	inline int CAipi_RETE_NumNode::getPM()
	{
		return m_PM;
	}
	
	
	inline int CAipi_RETE_NumNode::getCond()
	{
		return m_Cond;
	}

	inline int CAipi_RETE_NumNode::getBM()
	{
		return m_BM;
	}

	inline int CAipi_RETE_NumNode::getWM()
	{
		return m_WM;
	}

	inline int CAipi_RETE_NumNode::getTK()
	{
		return m_TK;
	}



	inline tstring CAipi_RETE_NumNode::getVar()
	{
		return m_Var;
	}



public:

	int		m_PM;
	int		m_Cond;
	int		m_BM;
	int		m_WM;
	int		m_TK;
	tstring	m_Var; 




};

#endif // !defined(AFX_AIPI_RETE_NUMNODE_H__BE4E8579_41CA_4471_8771_8CC2AD83E2DE__INCLUDED_)
