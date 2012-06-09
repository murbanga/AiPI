// Aipi_RETE_NCC.h: interface for the CAipi_RETE_NCC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_NCC_H__E6FE7927_97E1_4903_8EDC_0D49DD68122D__INCLUDED_)
#define AFX_AIPI_RETE_NCC_H__E6FE7927_97E1_4903_8EDC_0D49DD68122D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
	/// Negated Conjunctive Conditions (NCC) ///
This class represents the special node that represents predicate logic Negated Conjunctive Conditions.
	


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

class CAipi_RETE_NCC  
{
public:
	CAipi_RETE_NCC();
	virtual ~CAipi_RETE_NCC();
	



};

#endif // !defined(AFX_AIPI_RETE_NCC_H__E6FE7927_97E1_4903_8EDC_0D49DD68122D__INCLUDED_)
