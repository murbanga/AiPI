// Aipi_RETE_NN.h: interface for the CAipi_RETE_NN class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_NN_H__AC7D75B7_0C20_49AE_BA39_CDAE48A819F5__INCLUDED_)
#define AFX_AIPI_RETE_NN_H__AC7D75B7_0C20_49AE_BA39_CDAE48A819F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
	/// Negated Conditions or Negated Node (NN) ///
This class represents the special node for Negated conditions.


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


class CAipi_RETE_NN 
{
public:
	CAipi_RETE_NN();
	virtual ~CAipi_RETE_NN();

	

};

#endif // !defined(AFX_AIPI_RETE_NN_H__AC7D75B7_0C20_49AE_BA39_CDAE48A819F5__INCLUDED_)
