// Aipi_RETE_DNode.h: interface for the CAipi_RETE_DNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_DNODE_H__9EC37024_91AB_4A2C_B7EC_C31B76210FB7__INCLUDED_)
#define AFX_AIPI_RETE_DNODE_H__9EC37024_91AB_4A2C_B7EC_C31B76210FB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



/*
	/// Dummy Node (DNode) ///
This class represents the top node of the network.
It doesn´t store working memory elements and it represents the first Beta Memory	


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

class CAipi_RETE_DNode  
{
public:
	CAipi_RETE_DNode();
	virtual ~CAipi_RETE_DNode();

	CAipi_RETE_DNode(int pm, int am, int bm)
	{
		m_PM	= pm;
		m_AM	= am;
		m_BM	= bm;
			
	}

	inline void CAipi_RETE_DNode::setPM(int pm)
	{
		m_PM = pm;
	}


	inline void CAipi_RETE_DNode::setAM(int am)
	{
		m_AM = am;
	}

	inline void CAipi_RETE_DNode::setBM(int bm)
	{
		m_BM = bm;
	}

	inline int CAipi_RETE_DNode::getPM()
	{
		return m_PM;
	}


	inline int CAipi_RETE_DNode::getAM()
	{
		return m_AM;
	}

	inline int CAipi_RETE_DNode::getBM()
	{
		return m_BM;
	}

public:
	CAipi_RETE_DNode* CAipi_RETE_DNode::addDNode(int c, int pm, int am, int bm); 
	int		lastCondDNode();
	int		lastPMDNode();
	int		lastBMDNode();
	int		findDNodeMembers(int c);
	int		findDNodePM(int c);
	int		findDNodeAM(int c);
	int		findDNodeBM(int c);

	void	clearDNode();
	void	printDNode();

public:
	
	int		m_PM;
	int		m_AM;
	int		m_BM;


};

#endif // !defined(AFX_AIPI_RETE_DNODE_H__9EC37024_91AB_4A2C_B7EC_C31B76210FB7__INCLUDED_)
