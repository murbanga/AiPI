#if !defined(AFX_IMAGEFILTERDLG_H__AC964031_A9EA_4D81_AC60_DC0B22AE9D8F__INCLUDED_)
#define AFX_IMAGEFILTERDLG_H__AC964031_A9EA_4D81_AC60_DC0B22AE9D8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageFilterDlg.h : header file
//
#include ".\ImageProcess\CimageProcess.h"
#include	"OXSizeDlgBar.h"
#include "OXLayoutManager.h"
#include "OXCoolCtrl.h"
#include "OXSeparator.h"

using namespace Gdiplus;
// LayoutCtrlDlg dialog
class COXLayoutManager;
/////////////////////////////////////////////////////////////////////////////
// CImageFilterDlg dialog

class CImageFilterDlg : public COXSizeDialogBar
{

		DECLARE_DYNAMIC(CImageFilterDlg);
public:
// Construction
	CImageFilterDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageFilterDlg();
// Dialog Data
	//{{AFX_DATA(CImageFilterDlg)
	enum { IDD = IDD_IMAGEFILTER_DLG };
	COXSeparator	m_stcBrightness;
	COXSeparator	m_stcEffect;
	COXCoolButton	m_btnReset;
	COXCoolButton	m_btnBrowse;
	CStatic	m_StaticPath;
	CStatic	m_PicWnd;
	COXCoolButton	m_btnSharpness;
	COXCoolButton	m_btnBlur;
	CScrollBar	m_scroll_Vert;
	CScrollBar	m_scroll_Horz;
	COXCoolButton	m_btnBlackAndWhite;
	COXCoolButton	m_btnInvertColor;
	COXCoolSliderCtrl	m_sli_Blue;
	COXCoolSliderCtrl	m_sli_Contrast;
	COXCoolSliderCtrl	m_sli_Red;
	COXCoolSliderCtrl	m_sli_Green;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	COXLayoutManager m_LayoutManager;
	
	HDC m_hMemDC;
	CImageProcess m_Image;
	int m_nWidth;
	int m_nHeight;

	int m_nRedPos;
	int m_nGreenPos;
	int m_nBluePos;
	int m_nContrastPos;

	int m_nXScrollPos;
	int m_nYScrollPos;

	RECT m_Rect;
	bool m_bLoadImage ;
	bool m_visible;

	CString m_fileName;	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageFilterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	//HICON m_hIcon;
	BOOL DlgToolTips(UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	void ApplyEffect();
	void LoadImage(CString szfileName);


protected:
	BOOL InitLayoutManager();

	// Generated message map functions
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
	//{{AFX_MSG(CImageFilterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	afx_msg void OnCheckInvert();
	afx_msg void OnBtnBrowse();
	afx_msg void OnBtnReset();
	afx_msg void OnCheckBlackWhite();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckBlur();
	afx_msg void OnCheckSharpness();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos); 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEFILTERDLG_H__AC964031_A9EA_4D81_AC60_DC0B22AE9D8F__INCLUDED_)
