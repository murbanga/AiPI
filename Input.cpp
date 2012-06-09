/*
	Input.cpp
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



// Input.cpp: implementation of the CInput class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Input.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInput::CInput()
{

}

CInput::~CInput()
{

}

void CInput::ParseCommand(CString command)
{
	//this virtual function sends a message containing the command to the dialogbox
	
	CString *pstr;
	pstr = new CString(command);

	GetParent()->SendMessage(WM_CCOMMAND, (WPARAM) pstr);
}
