#if !defined(AFX_NEWPROJECTPAGE1_H__66A4F5BD_9ABB_40B8_8C43_730F25EC69B6__INCLUDED_)
#define AFX_NEWPROJECTPAGE1_H__66A4F5BD_9ABB_40B8_8C43_730F25EC69B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewProjectPage1.h : header file
//
#include "OXBrowseDirEdit.h"
#include "OXStaticText.h"
#include "OXSeparator.h"
#include "OXBackgroundPainter.h"
/////////////////////////////////////////////////////////////////////////////
// CNewProjectPage1 dialog

class CNewProjectPage1 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CNewProjectPage1)

// Construction
public:
	CNewProjectPage1();
	~CNewProjectPage1();

// Dialog Data
	//{{AFX_DATA(CNewProjectPage1)
	enum { IDD = IDD_NEWPROJECT_PAGE1 };
	COXSeparator	m_staticSeparator0;
	COXBrowseDirEdit	m_editBrowse32;
	CString	m_sProjectAuthor;
	CString	m_sProjectDesc;
	CString	m_sProjectName;
	//}}AFX_DATA
protected:
	// background painter organizer
	COXBackgroundPainterOrganizer m_backPainterOrganizer;
	// window to display image
	CWnd m_pictureWnd;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNewProjectPage1)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	CString	PrintDate();

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNewProjectPage1)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROJECTPAGE1_H__66A4F5BD_9ABB_40B8_8C43_730F25EC69B6__INCLUDED_)










