#if !defined(AFX_DXFCADDLG_H__233749FE_5150_49A9_8CA4_99C098E6FD90__INCLUDED_)
#define AFX_DXFCADDLG_H__233749FE_5150_49A9_8CA4_99C098E6FD90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DxfCadDlg.h : header file
//
#include ".\CadLib\Interface\CadLib.h"
#include "DxfDrawingView.h"
#include	"OXSizeDlgBar.h"
#include "OXLayoutManager.h"

/////////////////////////////////////////////////////////////////////////////
// CDxfCadDlg dialog

class CDxfCadDlg : public COXSizeDialogBar
{
	DECLARE_DYNAMIC(CDxfCadDlg);
	
public:
	// Construction
	CDxfCadDlg(CWnd* pParent = NULL);   // standard constructor
	CDrawing drawing;

// Dialog Data
	//{{AFX_DATA(CDxfCadDlg)
	enum { IDD = IDD_DXFCAD_DLG };
	CDxfDrawingView	m_DrawingWindow;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
protected:
	HICON m_hIcon;
	COXLayoutManager m_LayoutManager;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDxfCadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnButton1();
	void OnButton2();
	void OnButton3();
	void OnButton4();
	void OnCloseButton();
	void OnZoomInButton();
	void OnZoomOutButton();
	void OnZoomExtentsButton();


protected:
	BOOL InitLayoutManager();

	// Generated message map functions
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);

	//{{AFX_MSG(CDxfCadDlg)
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPaint();
	
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DXFCADDLG_H__233749FE_5150_49A9_8CA4_99C098E6FD90__INCLUDED_)
