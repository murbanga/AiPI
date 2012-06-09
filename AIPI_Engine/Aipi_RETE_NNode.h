// Aipi_RETE_NNode.h: interface for the CAipi_RETE_NNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_NNODE_H__EC0773F7_4B34_42DA_963A_F4D49C1CBD83__INCLUDED_)
#define AFX_AIPI_RETE_NNODE_H__EC0773F7_4B34_42DA_963A_F4D49C1CBD83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_RETE_Node.h"
#include "Aipi_RETE_TK.h"

//This class was the first version of Negated Conditions
//It has to be revised and debbug



class CAipi_RETE_NNode : public CAipi_RETE_Node 
{
public:
	CAipi_RETE_NNode();
	virtual ~CAipi_RETE_NNode();

	inline CAipi_RETE_NNode(int type, int c1, int f1, int c2, int f2, int bm1, int jn2)
	{
		CAipi_RETE_Node::setType(type);
		m_Cond1 = c1;
		m_Field1 = f1;
		m_Cond2 = c2;
		m_Field2 = f2;
		CAipi_RETE_Node::setParent(bm1);
		CAipi_RETE_Node::setChild(jn2);
	}

	inline void CAipi_RETE_NNode::setType(int type)
	{
		CAipi_RETE_Node::setType(type);

	}

	
	inline void CAipi_RETE_NNode::setCond1(int c1)
	{
		m_Cond1 = c1;

	}

	inline void CAipi_RETE_NNode::setField1(int f1)
	{
		m_Field1 = f1;
	}


	inline void CAipi_RETE_NNode::setCond2(int c2)
	{
		m_Cond2 = c2;
	}

	inline void CAipi_RETE_NNode::setField2(int f2)
	{
		m_Field2 = f2;
	}

	inline void CAipi_RETE_NNode::setBM1(int bm1)
	{
		CAipi_RETE_Node::setParent(bm1);

	}

	inline void CAipi_RETE_NNode::setJN2(int jn2)
	{
		CAipi_RETE_Node::setChild(jn2);

	}

	
	inline int CAipi_RETE_NNode::getCond1()
	{
		return m_Cond1;
	}
	
	
	inline int CAipi_RETE_NNode::getField1()
	{
		return m_Field1;
	}


	inline int CAipi_RETE_NNode::getCond2()
	{
		return m_Cond2;
	}

	
	inline int CAipi_RETE_NNode::getField2()
	{
		return m_Field2;
	}

	
	inline int CAipi_RETE_NNode::getBM1()
	{
		return CAipi_RETE_Node::m_Parent;
	}

	
	inline int CAipi_RETE_NNode::getJN2()
	{
		return CAipi_RETE_Node::m_Child;
	}
	
	
	inline int CAipi_RETE_NNode::getType()
	{
		return CAipi_RETE_Node::m_Type;
	}


public:
	CAipi_RETE_NNode* CAipi_RETE_NNode::addNN(int ncc, int c1, int f1, int c2, int f2, int bm1, int jn2, int type);
	void	addCond_NN(int c, int nn);
	void	addNN_TK(int nn, int tk);
	void    addNN_WM(int nn,int wm);
	void	addWM_NN(int wm,int nn);
	
	void	insertNN(int c);
	
	int		eraseNN_WM(int nn);
	int		eraseWM_NN(int wm);
	int		eraseNN(int nn);
	int     eraseCond_NN(int nn);
	int     eraseNN_TK(int nn);
	int     eraseItemNN_TK(int nn, int tk);
	void	eraseTK(int nn);	
	void    clearNNStructs();
	int		findCond_NN(int c);
	int     searchNN_TK(int tk);
	int		findNN_TK(int nn);
	int		findNNMembers(int nn);
	
	//int		findTokenNN(int t);
	int		findWM_NN(int wm);
	void	editCond_NN(int c, int nn);

	int		findField1NN(int nn);
	int		findField2NN(int nn);
	int		generateNNKey();
	int		sizeNNode();
	void	printCond_NN();
	void    printWM_NN();
	void    printNN_WM();
	void	printNN_TK();
	void	printLinkNN_TK();
	void	printNN();



public:
	int		m_Cond1;
	int		m_Cond2;
	int		m_Field1;
	int		m_Field2;
	int		m_BM1;
	int		m_JN2;
	int		m_Type;


	int    m_Token;
	int	   m_WME;
	int    m_Sign;

};

#endif // !defined(AFX_AIPI_RETE_NNODE_H__EC0773F7_4B34_42DA_963A_F4D49C1CBD83__INCLUDED_)
