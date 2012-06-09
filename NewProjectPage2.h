#if !defined(AFX_NEWPROJECTPAGE2_H__AD214265_01CF_4F29_A82D_D2560952894F__INCLUDED_)
#define AFX_NEWPROJECTPAGE2_H__AD214265_01CF_4F29_A82D_D2560952894F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewProjectPage2.h : header file
//
#include "OXStaticText.h"
#include "OXSeparator.h"
#include "OXCoolCtrl.h"
#include "OXBackgroundPainter.h"
/////////////////////////////////////////////////////////////////////////////
// CNewProjectPage2 dialog

class CNewProjectPage2 : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CNewProjectPage2)

// Construction
public:
	CNewProjectPage2();
	~CNewProjectPage2();

// Dialog Data
	//{{AFX_DATA(CNewProjectPage2)
	enum { IDD = IDD_NEWPROJECT_PAGE2 };
	COXCoolButton	m_chkVideos;
	COXCoolButton	m_chkOthers;
	COXCoolButton	m_chkImages;
	COXCoolButton	m_chkDataBase;
	COXCoolButton   m_radioFordward;
	COXCoolButton   m_radioBackward;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNewProjectPage2)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// background painter organizer
	COXBackgroundPainterOrganizer m_backPainterOrganizer;
	// window to display image
	CWnd m_pictureWnd;

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNewProjectPage2)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioForward();
	afx_msg void OnRadioBackward();
	afx_msg void OnCheckImages();
	afx_msg void OnCheckVideos();
	afx_msg void OnCheckDataBases();
	afx_msg void OnCheckOthers();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROJECTPAGE2_H__AD214265_01CF_4F29_A82D_D2560952894F__INCLUDED_)
