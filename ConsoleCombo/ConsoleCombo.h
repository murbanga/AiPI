/*
	ConsoleCombo.h
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

#if !defined(AFX_CONSOLECOMBO_H__C517018C_A929_457C_850B_9D4798B0CF40__INCLUDED_)
#define AFX_CONSOLECOMBO_H__C517018C_A929_457C_850B_9D4798B0CF40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConsoleCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConsoleCombo window

class CConsoleCombo : public CComboBox
{
// Construction
public:
	CConsoleCombo();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConsoleCombo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CConsoleCombo();

	// Generated message map functions
protected:
	CString m_current;
	virtual void ParseCommand(CString command) { }
	int m_nPos;
	//{{AFX_MSG(CConsoleCombo)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSOLECOMBO_H__C517018C_A929_457C_850B_9D4798B0CF40__INCLUDED_)
