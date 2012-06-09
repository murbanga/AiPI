#if !defined(AFX_DXFDRAWINGVIEW_H__0C965127_372B_4A48_ACF2_95FC235DB9DB__INCLUDED_)
#define AFX_DXFDRAWINGVIEW_H__0C965127_372B_4A48_ACF2_95FC235DB9DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DxfDrawingView.h : header file
//
#include ".\CadLib\Interface\CadLib.h"
/////////////////////////////////////////////////////////////////////////////
// CDxfDrawingView window

class CDxfDrawingView : public CStatic
{
// Construction
public:
	CDxfDrawingView();

// Attributes
public:

private:
	CPoint PrevMousePnt;
	bool m_Pan;

// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDxfDrawingView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDxfDrawingView();
	
	bool SetDrawing(CDrawing* pDrawing);
	CDrawing* m_pDrawing;

	// Generated message map functions
protected:
	//{{AFX_MSG(CDxfDrawingView)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DXFDRAWINGVIEW_H__0C965127_372B_4A48_ACF2_95FC235DB9DB__INCLUDED_)
