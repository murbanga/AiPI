#if !defined(AFX_IMAGEDLG_H__256310BF_B508_4C86_84ED_12C1F95EA4C2__INCLUDED_)
#define AFX_IMAGEDLG_H__256310BF_B508_4C86_84ED_12C1F95EA4C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageDlg.h : header file
//
#include	".\MVImage\mvImage.h"
#include	"OXSizeDlgBar.h"

using namespace Gdiplus;
/////////////////////////////////////////////////////////////////////////////
// CImageDlg dialog

class CImageDlg : public COXSizeDialogBar
{

	DECLARE_DYNAMIC(CImageDlg);
	
public:
// Construction
	CImageDlg(CWnd* pParent = NULL);   // standard constructor
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
// Dialog Data
	//{{AFX_DATA(CImageDlg)
	enum { IDD = IDD_IMAGE_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void OpenImage();
	void LoadImage(CString szfilePath);
	void ImageExit();
	void StretchAll();
	void StretchNothing();
	void StretchHeight();
	void StretchWidth(); 
	void RotateLeft();
	void RotateRight();
	void ZoomIn();
	void ZoomOut();

	mvImage* m_Image;

	// Generated message map functions
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);

	//{{AFX_MSG(CImageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEDLG_H__256310BF_B508_4C86_84ED_12C1F95EA4C2__INCLUDED_)
