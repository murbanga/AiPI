// Aipi_RETE_TK.h: interface for the CAipi_RETE_TK class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_TK_H__45B40ADC_D670_478D_A69D_22F6BE5354E0__INCLUDED_)
#define AFX_AIPI_RETE_TK_H__45B40ADC_D670_478D_A69D_22F6BE5354E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



//// Tokens (TK)

/*
	This class represents the Tokens of the Beta Memory.
	Tokens are Working Memory elements linked that are inside the Beta Memory

	*** Symbols ***
	TK		= Token
	AM		= Alpha Memory
	BM		= Beta Memory
	WM		= Working Memory
	PM		= Production Memory
	Cond	= Condition
	
	
	I	= Identifier (Id)   
	A	= Atribute (Attr)  
	V	= Value (Val)
	e	= Don`t care
	
	ParentTK	= Parent Token 
	ChildTK		= Child	Token
	
	

	*** Function Parameters ***
	am		= Alpha Memory
	bm		= Beta Memory
	wm		= Working Memory
	pm		= Production Memory
	lhs		= Left Hand Side Function
	cond	= Condition
	
*/


class CAipi_RETE_TK  
{
public:
	CAipi_RETE_TK();
	virtual ~CAipi_RETE_TK();

	//Child token is the index of the structure
	CAipi_RETE_TK(int parent_tk, int wm, int bm, int node)
	{
		m_ParentTk	= parent_tk;
		m_WM		= wm;
		m_BM		= bm;
		m_Node		= node;
	}
	
	inline void CAipi_RETE_TK::setParentTk(int parent_tk)
	{
		m_ParentTk = parent_tk;
	}


	inline void CAipi_RETE_TK::setWM(int wm)
	{
		m_WM = wm;
	}

	inline void CAipi_RETE_TK::setBM(int bm)
	{
		m_BM = bm;
	}

	inline void CAipi_RETE_TK::setNode(int node)
	{
		m_Node = node;
	}

	inline int CAipi_RETE_TK::getWM()
	{
		return m_WM;
	}

	inline int CAipi_RETE_TK::getBM()
	{
		return m_BM;
	}


	inline int CAipi_RETE_TK::getParentTk()
	{
		return m_ParentTk;
	}

	inline int CAipi_RETE_TK::getNode()
	{
		return m_Node;
	}






public:
	CAipi_RETE_TK*	createTK(int child_tk, int parent_tk, int wm, int bm, int jnode);

	void		addWM_ParentTK(int wm, int parent_tk);
	void		addWM_ChildTK(int wm, int child_tk);

	void		addTKParent_TKChild(int parent,int child);
	void		addTKParent_TKLink(int parent,int link);
	void		createTKParent_TKLink();
	void		createTKParent_TKLinkE(int parent_tk);
	
	void		fillTK();
	void		eraseTK(int child_tk);
	
	//Deletes all tokens linked with the parent token
	void		eraseParent_TKParent_TKLink(int parent_tk);
	//Deletes all tokens linked with the child token
	int			eraseChild_TKParent_TKLink(int child_tk);
	
	void		eraseParent_TKParent_TKChild(int parent_tk);
	int			eraseChild_TKParent_TKChild(int child_tk);
	
	int			eraseItemTKParent_TKChild(int parent_tk,int child_tk);
	
	void		eraseWMParentTK(int wme);
	void		eraseWMChildTK(int wme);
	
	int			eraseWMParentTKE(int wme, int parent_tk);	
	int			eraseWMChildTKE(int wme, int child_tk);	
	
	int			eraseWMParentTokenE(int w, int parent_tk);
	int			eraseWMChildTokenE(int w, int child_tk);

	void		clearTK();
	void		clearTKParent_TKLink();
	void		clearTKParent_TKChild();
	
	void		clearWM_ParentTK();
	void		clearWM_ChildTK();
	
	void		clearTKStructs();
	
	
		
	
	int			generateTKKey();
	
	int		    findTKMembers(int child_tk);
	int			findParentTk(int child_tk);
	int			findNode(int child_tk);
	int			findBM(int child_tk);
	int			findWM(int child_tk);

	
	int			findWMParentTK(int tk);

	int			findWM_ParentTK(int wm);
	int			findWM_ChildTK(int wm);
	int			findChild_TKParent_TKChild(int parent_tk);
	
	

	tstring		linkWMEs(int tk);
	
	
	
	
	
	int			searchTKWM(int wm);
	int			searchTKChildTK(int parent_tk);


	

	int			countWM(int wm);
	int			countWM_ParentTK(int wm);
	int			countWM_ChildTK(int wm);
	int			countParentTK(int parent_tk);
	int			countChildTK(int child_tk);


	
	void		printTK();
	void		printLinkTK();
	
	void		printWM_ParentTK();
	void		printWM_ChildTK();
	void		printTKParent_TKChild();
	void		printTKParent_TKLink();
	

public:
	int		m_WM;
	int		m_BM;
	int		m_ParentTk;
	int		m_Node;
		
};

#endif // !defined(AFX_AIPI_RETE_TK_H__45B40ADC_D670_478D_A69D_22F6BE5354E0__INCLUDED_)
