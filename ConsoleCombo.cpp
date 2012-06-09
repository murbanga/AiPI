/*
	ConsoleCombo.cpp
	By: Kevin Bond
	kevinbond@gmail.com
	www.mechdesk.ath.cx

	Use and distribute freely.  
	Please don't remove my name and don't take credit for my work. You may edit my code
	as long as you don't remove my name.

	Send comments, questions or bugs to kevinbond@gmail.com 
	or visit my site www.mechdesk.ath.cx
*/

/*Instructions:	This class is derived from the CComboBox class.  To use this you must
				derive a class from this and override the virtual ParseCommand() function
				with commands to be initiated when the user presses the enter key.  This
				derived class is the class you use for the CComboBox(s) in your application.
*/

// ConsoleCombo.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ConsoleCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConsoleCombo

CConsoleCombo::CConsoleCombo()
{
	//set initial position
	m_nPos = -1;
}

CConsoleCombo::~CConsoleCombo()
{
}


BEGIN_MESSAGE_MAP(CConsoleCombo, CComboBox)
	//{{AFX_MSG_MAP(CConsoleCombo)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConsoleCombo message handlers

BOOL CConsoleCombo::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN)
	{
		CString str;				
		int nVirtKey = (int) pMsg->wParam;

		
		switch (nVirtKey)
		{
		//checks if up arrow key is pressed
		case VK_UP:
			
			//if this is first position save current text
			if (m_nPos == -1)
			{
				GetWindowText(str);
				m_current = str;
			}

			
			//makes sure an invalid position isn't going to be set
			if (m_nPos + 1 < GetCount())
			{				
				//increase position
				m_nPos++;
				//get text at current position display it highlighted
				GetLBText(m_nPos, str);
				SetWindowText(str);
				SetEditSel(0, str.GetLength());									
				
			}

			
			return TRUE;
		
		case VK_DOWN:
			
			//if going back to bottem restore previously entered text
			if (m_nPos - 1 == -1)
			{
				SetWindowText(m_current);
				SetEditSel(m_current.GetLength(), m_current.GetLength());
				m_nPos = -1;
			}
			
			if (m_nPos - 1 >= 0)
			{
								
				//decrease position
				m_nPos--;
				//get text at current position display it highlighted
				GetLBText(m_nPos, str);
				SetWindowText(str);
				SetEditSel(0, str.GetLength());								
				
			}
			return TRUE;
		
		//if enter key is pressed do following
		case VK_RETURN:
			
			GetWindowText(str);
			
			//make sure there is something input
			if (str != _T(""))
			{			
				//add string to the bottem of the list
				InsertString(0, str);
				m_nPos = -1;
				SetWindowText(_T(""));

				//function that must be customized for each program				
				ParseCommand(str);

			}
			break;
		
		}

		
		
	}
	
	return CComboBox::PreTranslateMessage(pMsg);
}

