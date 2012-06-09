#if !defined(AFX_WORKSPACEVIEW_H__95C3949F_EF86_4275_8FDB_EA9F8B721F9B__INCLUDED_)
#define AFX_WORKSPACEVIEW_H__95C3949F_EF86_4275_8FDB_EA9F8B721F9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkspaceView.h : header file
//
#include "OXSkinnedView.h"
#include "OXBackgroundPainter.h"

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView view
#define WORKSPACEMAINVIEW CView

class CWorkspaceView : public COXSkinnedView<WORKSPACEMAINVIEW>
{
protected:
	CWorkspaceView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CWorkspaceView)

// Attributes
public:
	CWorkspaceTabDoc* GetDocument();

public:
	int m_nPage;



protected:
	COXBackgroundPainterOrganizer m_backPainterOrganizer;

// Operations
private:
	void ShowFont1(CDC* pDC, int& xPos, int& yPos, int nPoints, CString text);
	void ShowFont2(CDC* pDC, int& xPos,  int& yPos, int nPoints, CString text);

	void PrintPageHeader(CDC* pDC);
	void PrintPageFooter(CDC* pDC);
	CString PrintDate();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CWorkspaceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKSPACEVIEW_H__95C3949F_EF86_4275_8FDB_EA9F8B721F9B__INCLUDED_)
