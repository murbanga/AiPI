#if !defined(AFX_NEWPROJECTINTROPAGE_H__79C136DE_0FE1_405A_8BE6_3E054ACFA0CD__INCLUDED_)
#define AFX_NEWPROJECTINTROPAGE_H__79C136DE_0FE1_405A_8BE6_3E054ACFA0CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewProjectIntroPage.h : header file
//
#include "OXStaticText.h"
#include "OXSeparator.h"
/////////////////////////////////////////////////////////////////////////////
// CNewProjectIntroPage dialog

class CNewProjectIntroPage : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CNewProjectIntroPage)

// Construction
public:
	CNewProjectIntroPage();
	~CNewProjectIntroPage();

// Dialog Data
	//{{AFX_DATA(CNewProjectIntroPage)
	enum { IDD = IDD_NEWPROJECT_INTROPAGE };
	COXSeparator	m_staticSeparator0;
	COXStaticText	m_staticTitle;
	CStatic	m_staticThanks;
	CStatic	m_staticInfo;
	CStatic	m_staticAdvice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNewProjectIntroPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNewProjectIntroPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROJECTINTROPAGE_H__79C136DE_0FE1_405A_8BE6_3E054ACFA0CD__INCLUDED_)
