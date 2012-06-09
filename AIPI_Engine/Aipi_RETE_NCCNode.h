// Aipi_RETE_NCCNode.h: interface for the CAipi_RETE_NCCNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_NCCNODE_H__7D41444C_E95F_499F_9884_FEF30F0598C3__INCLUDED_)
#define AFX_AIPI_RETE_NCCNODE_H__7D41444C_E95F_499F_9884_FEF30F0598C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//Tested class for NNC
//This functions must be checked and debug again

class CAipi_RETE_NCCNode  
{
public:
	CAipi_RETE_NCCNode();
	virtual ~CAipi_RETE_NCCNode();

	inline CAipi_RETE_NCCNode(int pm, int cini, int cend)
	{
		m_PM = pm;
		m_IniCond = cini;
		m_EndCond = cend;
		

	}


	
	//Sets
	inline void CAipi_RETE_NCCNode::setPM(int pm)
	{
		m_PM = pm;

	}

	inline void CAipi_RETE_NCCNode::setIniCond(int c1)
	{
		m_IniCond = c1;

	}
	
	inline void CAipi_RETE_NCCNode::setEndCond(int c2)
	{
		m_EndCond = c2;

	}
	
	//Gets
	inline int CAipi_RETE_NCCNode::getPM()
	{
		return m_PM;
	}

	
	inline int CAipi_RETE_NCCNode::getIniCond()
	{
		return m_IniCond;
	}

	inline int CAipi_RETE_NCCNode::getEndCond()
	{
		return m_EndCond;
	}


	
	CAipi_RETE_NCCNode* addNCC(int ncc, int pm, int c1, int c2);
	
	void insertNCC(int cini, int cend, int pm);
	
	void addNCCN_BM(int ncc, int bm);
	void addNCCPartnerN_BM(int ncc,int bm);
	void addNCC_Cond(int ncc, int c);	
	void addCond_NCC(int c, int ncc);	
	
	
	
	void addNCCPartnerN_TK(int ncc, int tk);
	int editBM_TK(int ncc, int partner);
	
	void eraseNCCN_BM(int ncc);
	void eraseNCCPartnerN_BM(int ncc);
	void clearNCCStructs();

	int findInitCond_NCC(int ncc);
	int findEndCond_NCC(int ncc);
	int findNCC_Cond(int ncc);
	int	findCond_NCC(int c);
	int findNCCN_BM(int ncc);
	int findNCCPartnerN_BM(int ncc);
	int findNCC_PM(int ncc);
	int findNCC(int ncc);
	int findNCCPartnerN_TK(int ncc);
	int searchNCCPartnerN_TK(int tk);

	
	int bindNCC(int ncc,int p);
	int generateNCCKey();

	void printNCCN_BM();
	void printNCCPartnerN_BM();
	void printNCC_Cond();
	void printCond_NCC();	
	void printNCCPartnerN_TK();
	void printLinkNCCPartnerN_TK();
	void printNCC();
		

public:
	int m_PM;
	int m_IniCond;
	int m_EndCond;

};

#endif // !defined(AFX_AIPI_RETE_NCCNODE_H__7D41444C_E95F_499F_9884_FEF30F0598C3__INCLUDED_)
