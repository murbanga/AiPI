#if !defined(AFX_IMAGECTRL_H__6FF56F47_D193_4F6E_83DD_3176D79F6DB5__INCLUDED_)
#define AFX_IMAGECTRL_H__6FF56F47_D193_4F6E_83DD_3176D79F6DB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageCtrl.h : header file
//
#include ".\WndImage\WndImage.h"
#include "OXSizeCtrlBar.h"
/////////////////////////////////////////////////////////////////////////////
// CImageCtrl window

class CImageCtrl : public COXSizeControlBar
{
	DECLARE_DYNAMIC(CImageCtrl);

public:
	BOOL Create(CWnd * pParentWnd, const CString& sTitle = _T("ImageCtrl"),
		const UINT nID=IDC_ST_IMG);
// Construction	
	CImageCtrl();

// Attributes
public:

// Operations
public:
	void ImageInit(CString szPath);
	void OpenImage();
	void OnStretchNormal();
	void OnStretch();
	void OnStretchXY(); 
	void OnStretchSM(); 
    void OnTile(); 
    void OnLeft(); 
	void OnCenterX(); 
	void OnRight(); 
	void OnTop(); 
    void OnCenterY(); 
    void OnBottom(); 


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageCtrl();

public:
	CStatic			m_staticCtrl;
	CWndImage       m_img;


	// Generated message map functions
protected:
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);

	//{{AFX_MSG(CImageCtrl)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGECTRL_H__6FF56F47_D193_4F6E_83DD_3176D79F6DB5__INCLUDED_)
