#if !defined(AFX_NEWPROJECTSHEET_H__61817BB8_2621_4198_A404_F812A1840E7E__INCLUDED_)
#define AFX_NEWPROJECTSHEET_H__61817BB8_2621_4198_A404_F812A1840E7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewProjectSheet.h : header file
//
#include "NewProjectIntroPage.h"
#include "NewProjectPage1.h"
#include "NewProjectPage2.h"
#include "NewProjectEndPage.h"

/////////////////////////////////////////////////////////////////////////////
// CNewProjectSheet

class CNewProjectSheet : public CPropertySheetEx
{
	DECLARE_DYNAMIC(CNewProjectSheet)

// Construction
public:
	CNewProjectSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0, 
		HBITMAP hbmWatermark = NULL, HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL);
	CNewProjectSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0, 
		HBITMAP hbmWatermark = NULL, HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL);

// Attributes
public:
	CNewProjectIntroPage	m_Intro;
	CNewProjectPage1		m_Page1;
	CNewProjectPage2		m_Page2;
	CNewProjectEndPage		m_End;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewProjectSheet)
	public:
	//virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNewProjectSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNewProjectSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROJECTSHEET_H__61817BB8_2621_4198_A404_F812A1840E7E__INCLUDED_)


























