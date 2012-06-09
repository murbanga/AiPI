// Aipi_RETE_PNode.h: interface for the CAipi_RETE_PNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_PNODE_H__EE3A8C92_4970_417F_AD57_73BC676CF0DA__INCLUDED_)
#define AFX_AIPI_RETE_PNODE_H__EE3A8C92_4970_417F_AD57_73BC676CF0DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_RETE_Node.h"
#include "Aipi_PM.h"
#include "Aipi_RETE_BM.h"
#include "Aipi_RETE_BME.h"


/*
/// Production Node (PNode) ///
This class represents the special node Production Node.
PNode or Production Node
This class represent the conflict set or the agenda 
PNode has the structure of a Beta Memory element for a specific production.
This node has the working memories elements that match the production



	*** Symbols ***
	AM		= Alpha Memory
	BM		= Beta Memory
	WM		= Working Memory
	PM		= Production Memory
	Cond	= Condition
	C1		= Condition1
	C2		= Condition2
	


	*** Function Parameters ***
	am		= Alpha Memory
	bm		= Beta Memory
	wm		= Working Memory
	pm		= Production Memory
	cond	= Condition
	
*/

class CAipi_RETE_PNode : public CAipi_RETE_Node 
{
public:
	CAipi_RETE_PNode();
	virtual ~CAipi_RETE_PNode();

	inline CAipi_RETE_PNode(int bm, int c1, int c2, int type)
	{
		CAipi_RETE_Node::setType(type);
		m_BM = bm;
		m_C1 = c1;
		m_C2 = c2;

	}
	
	//Sets
	inline void CAipi_RETE_PNode::setC1(int c1)
	{
		m_C1 = c1;

	}
	
	inline void CAipi_RETE_PNode::setC2(int c2)
	{
		m_C2 = c2;

	}

	inline void CAipi_RETE_PNode::setType(int type)
	{
		CAipi_RETE_Node::setType(type);

	}
	

	//Gets
	inline int CAipi_RETE_PNode::getC1()
	{
		return m_C1;
	}

	
	inline int CAipi_RETE_PNode::getC2()
	{
		return m_C2;
	}


	inline int CAipi_RETE_PNode::getType()
	{
		return CAipi_RETE_Node::m_Type;
	}


	


public:
	CAipi_RETE_PNode* addPNode(int bm, int c1, int c2, int type);
	//void createPNode();
	void addFiredPM( long pm);
	void eraseFiredPM(long pm);
	void addRefractionPM( long pm);
	//void eraseRefractionPM(long pm);
	int definePNode(long pm);
	
	int  saveFiredPM();
	int	 saveFiredPM(long pm); 
	int  findRefraction( long pm);
	int	 firedConstMetaRule(long pm);
	int	 firedVarMetaRule(long pm);	
	
	
	void conflictResolution(int strategy);
	void clearPNStructs();
	int findC1(int bm);
	int findC2(int bm);
	int findPNodeMembers(int bm);

	//Conflict set methods


	void printPN();
	void printAgendaPM();
	void printFiredPM();
	void printRefractionPM();
	

public:
	int m_BM;
	int m_C1;
	int m_C2;
	int m_Type;

};

#endif // !defined(AFX_AIPI_RETE_PNODE_H__EE3A8C92_4970_417F_AD57_73BC676CF0DA__INCLUDED_)
