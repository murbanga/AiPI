// WorkspaceFormView.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "WorkspaceFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WorkspaceFormView

IMPLEMENT_DYNCREATE(WorkspaceFormView, CFormView)

WorkspaceFormView::WorkspaceFormView()
	: CFormView(WorkspaceFormView::IDD)
{
	//{{AFX_DATA_INIT(WorkspaceFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

WorkspaceFormView::~WorkspaceFormView()
{
}

void WorkspaceFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WorkspaceFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WorkspaceFormView, CFormView)
	//{{AFX_MSG_MAP(WorkspaceFormView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WorkspaceFormView diagnostics

#ifdef _DEBUG
void WorkspaceFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void WorkspaceFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// WorkspaceFormView message handlers
