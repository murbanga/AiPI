// Aipi_RETE_Node.h: interface for the CAipi_RETE_Node class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_NODE_H__A4D898A9_9211_4442_ACB9_7DBB672A3E47__INCLUDED_)
#define AFX_AIPI_RETE_NODE_H__A4D898A9_9211_4442_ACB9_7DBB672A3E47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/*

	*** Symbols ***
	Type	= The Type of Node (Join Node, Production Noide, Negated Node, etc..)
	BM1		= Parent Beta Memory of the Node (Parent)
	BM2		= Child  Beta Memory of the Node (Child) 
	AM		= Alpha Memory linked to the Node  

	*** Functions Parameters ***
	bm1		= Parent Beta Memory of the Node (parent)
	bm2		= Child  Beta Memory of the Node (child)
	am		= Alpha Memory linked to the Node  

*/


class CAipi_RETE_Node  
{
public:
	CAipi_RETE_Node();
	virtual ~CAipi_RETE_Node();

	
	CAipi_RETE_Node(int type, int parent, int child, int am)
	{
		m_Type		= type;
		m_Parent	= parent;
		m_Child		= child;
		m_AM		= am;	
	}

	inline void CAipi_RETE_Node::setType(int type)
	{
		m_Type = type;
	}


	inline void CAipi_RETE_Node::setParent(int parent)
	{
		m_Parent = parent;
	}

	inline void CAipi_RETE_Node::setChild(int child)
	{
		m_Child = child;
	}

	inline void CAipi_RETE_Node::setAM(int am)
	{
		m_AM = am;
	}

	inline int CAipi_RETE_Node::getType()
	{
		return m_Type;
	}


	inline int CAipi_RETE_Node::getParent()
	{
		return m_Parent;
	}

	inline int CAipi_RETE_Node::getChild()
	{
		return m_Child;
	}

	inline int CAipi_RETE_Node::getAM()
	{
		return m_AM;
	}


public:
	CAipi_RETE_Node* CAipi_RETE_Node::addNode(int node, int type, int bm1, int bm2, int am); 
	int		findNodeMembers(int node);
	int		findNodeType(int node);
	int		findNodeBM1(int node);
	int		findNodeBM2(int node);
	int		findNodeAM(int node);
	int		sizeNode();

	void	clearNode();
	void	printNode();	

	
public:
	int		m_Type;
	int		m_Parent;
	int		m_Child;
	int     m_AM;

};

#endif // !defined(AFX_AIPI_RETE_NODE_H__A4D898A9_9211_4442_ACB9_7DBB672A3E47__INCLUDED_)
