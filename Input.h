/*
	Input.h
	By: Kevin Bond
	kevinbond@gmail.com
	www.mechdesk.ath.cx

	Use and distribute freely.  
	Please don't remove my name and don't take credit for my work. You may edit my code
	as long as you don't remove my name.

	Send comments, questions or bugs to kevinbond@gmail.com 
	or visit my site www.mechdesk.ath.cx
*/

//Instructions:	This class is derived from the CConsoleCombo class.

// Input.h: interface for the CInput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUT_H__714CDAA6_D11C_40C0_852A_360AD432756C__INCLUDED_)
#define AFX_INPUT_H__714CDAA6_D11C_40C0_852A_360AD432756C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConsoleCombo.h"

class CInput : public CConsoleCombo  
{
public:
	CInput();
	virtual ~CInput();

protected:
	virtual void ParseCommand(CString command);
};

#endif // !defined(AFX_INPUT_H__714CDAA6_D11C_40C0_852A_360AD432756C__INCLUDED_)
