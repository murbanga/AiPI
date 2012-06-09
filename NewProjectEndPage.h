#if !defined(AFX_NEWPROJECTENDPAGE_H__C6F9C85C_B072_4CCA_B88C_E88706F3AF5A__INCLUDED_)
#define AFX_NEWPROJECTENDPAGE_H__C6F9C85C_B072_4CCA_B88C_E88706F3AF5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewProjectEndPage.h : header file
//
#include "OXStaticText.h"
#include "OXSeparator.h"


/////////////////////////////////////////////////////////////////////////////
// CNewProjectEndPage dialog

class CNewProjectEndPage : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CNewProjectEndPage)

// Construction
public:
	CNewProjectEndPage();
	~CNewProjectEndPage();

// Dialog Data
	//{{AFX_DATA(CNewProjectEndPage)
	enum { IDD = IDD_NEWPROJECT_ENDPAGE };
	CStatic	m_stcInfo;
	CStatic	m_stcRoot;
	CEdit	m_sProjectInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNewProjectEndPage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNewProjectEndPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROJECTENDPAGE_H__C6F9C85C_B072_4CCA_B88C_E88706F3AF5A__INCLUDED_)
