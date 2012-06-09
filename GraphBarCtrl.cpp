// GraphBarCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "GraphBarCtrl.h"

#include "GraphAxisDlg.h"
#include "GraphCoordinatesDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CGraphBarCtrl, COXSizeControlBar);
/////////////////////////////////////////////////////////////////////////////
// CGraphBarCtrl

CGraphBarCtrl::CGraphBarCtrl()
: COXSizeControlBar( SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	lGraph_Count = 0;
}

CGraphBarCtrl::~CGraphBarCtrl()
{
}


BEGIN_MESSAGE_MAP(CGraphBarCtrl, COXSizeControlBar)
	//{{AFX_MSG_MAP(CGraphBarCtrl)
		ON_WM_CREATE()
		ON_WM_TIMER()
		//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define POINTS_X_RANGE	200
#define DEMO_MAX_GRAPHS 16
#define GRAPH_DYNAMIC_TIMER_ID	0x98765

COLORREF DefaultGraphColors[DEMO_MAX_GRAPHS] = {RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255), 
	RGB(255, 255, 0), RGB(0, 255, 255), 32768, 128, 
	8388736, 8421440, 12615808, 8421504, 33023, 
	16711935, 12632256, 32896, RGB(0, 0, 0)};

/////////////////////////////////////////////////////////////////////////////
// CGraphBarCtrl message handlers

int CGraphBarCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	//etSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

	m_graphCtrl.Create(_T("GraphBarCtrl"), CRect(0,0,0,0), this, IDC_GRAPHBARCTRL, WS_CHILD | WS_VISIBLE, TRUE);
	
	
	AddNewGraph();
	//AddNewDynamicGraph(TRUE, POINTS_X_RANGE);
	//OnDynamicGraph(); 

	return 0;
}



BOOL CGraphBarCtrl::Create(CWnd * pParentWnd, const CString& sTitle /* = _T("GraphBarCtrl")*/,
					const UINT nID /* = IDC_GRAPHBARCTRL */)
{
	//Register a windows class for the control bar
	static CString strWndClass;
	if ( strWndClass.IsEmpty())
	{
		strWndClass = AfxRegisterWndClass(CS_DBLCLKS);
	}
		

	return COXSizeControlBar::Create(strWndClass, sTitle, WS_VISIBLE |WS_CHILD |
		CBRS_RIGHT|WS_CLIPCHILDREN, CFrameWnd::rectDefault, pParentWnd, nID);


}


//-------------------------------------------------------------------
void CGraphBarCtrl::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// respond to this event as we need to override it
//-------------------------------------------------------------------
{
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	CRect rect;
	GetClientRect(rect);

	rect.DeflateRect(0, 0);

	m_graphCtrl.MoveWindow(&rect);
}


void CGraphBarCtrl::AddNewGraph() 
{
    CString title;
    title.Format(_T("New graph - %d"), lGraph_Count);
    int c = m_graphCtrl.AddGraph(DefaultGraphColors[lGraph_Count], title);
    if (c != -1)
    {
	//add new sin graph
	double x, y;
	for (int i=0; i<=POINTS_X_RANGE; i++)
	{
	    x = i;
	    y = sin((i*3.14*(lGraph_Count+1))/POINTS_X_RANGE);
	    m_graphCtrl.AddPoint(c, x, y, TRUE);
	};
    };
    lGraph_Count += 1;
}


long CGraphBarCtrl::AddNewDynamicGraph(BOOL bDrawPoints, double x_range)
{
    long Res_Graph = -1;
    //get view
    if (lGraph_Count == 0)
    {
	m_graphCtrl.SetAxisProps(_T("X-Axis"), _T(""), 4, GRAPH_X_AXIS, TRUE);
	m_graphCtrl.SetAxisProps(_T("Y-Axis"), _T(""), 4, GRAPH_Y_AXIS, TRUE);
	m_graphCtrl.SetGraphWorldCoords(0, x_range, -1, 1, TRUE);
	//m_graphCtrl.SetGraphFlags(m_graphCtrl.GetGraphFlags() | GRAPH_GRAPH_SCATTER, TRUE);
    };
    if (lGraph_Count < DEMO_MAX_GRAPHS)
    {
	//m_graphCtrl.OperateWithPointView(GRAPH_PO_DISABLE);

	CString szTitle;
	szTitle.Format(_T("New graph - %d"), lGraph_Count);
	Res_Graph = m_graphCtrl.AddGraph(DefaultGraphColors[lGraph_Count], szTitle);
	if (Res_Graph != -1 && bDrawPoints)
	{
	    //add new sin graph
	    double x, y;
	    for (int i=0; i<=x_range; i++)
	    {
		x = i;
		y = sin((i*3.14*(lGraph_Count+1))/x_range);
		m_graphCtrl.AddPoint(Res_Graph, x, y);
	    };
	};
	//m_graphCtrl.OperateWithPointView(GRAPH_PO_ENABLE);
    //m_graphCtrl.UpdateWindows(GRAPH_WUV_ALL);
	lGraph_Count += 1;
    } else
    {
	AfxMessageBox(_T("No more graphs... Sorry."));
    };
    return Res_Graph;
}


void CGraphBarCtrl::OnDynamicGraph() 
{
    SetTimer(GRAPH_DYNAMIC_TIMER_ID, 100, NULL);
    lDyn_Graph_ID = AddNewDynamicGraph(FALSE, 50);
    lCurrent_X = 0;
}


void CGraphBarCtrl::QuitDynamicGraph()
{
	KillTimer(GRAPH_DYNAMIC_TIMER_ID);

}
void CGraphBarCtrl::OnTimer(UINT nIDEvent) 
{
    CWnd::OnTimer(nIDEvent);

    if (nIDEvent == GRAPH_DYNAMIC_TIMER_ID)
    {
	BOOL bRedraw = FALSE;

	double x, y;
	x = lCurrent_X;
	y = sin(lCurrent_X*3.14/10);

	double x1, x2, y1, y2;
	m_graphCtrl.GetGraphWorldCoords(&x1, &x2, &y1, &y2);
	if (x > x2)
	{
	    bRedraw = TRUE;

	    CGraphProps* grprops = m_graphCtrl.GetGraph(lDyn_Graph_ID);
	    SSinglePoint ssp;
	    grprops->GetPoint(1, &ssp);

	    m_graphCtrl.RemovePoint(lDyn_Graph_ID, 0, TRUE);

	    m_graphCtrl.SetGraphWorldCoords(ssp.x, x, y1, y2, TRUE);
	};
	//m_graphCtrl.AddPoint(lDyn_Graph_ID, x, y, !bRedraw);
	m_graphCtrl.AddPoint(lDyn_Graph_ID, x, y);
/*
	if (bRedraw)
	{
	    m_graphCtrl.UpdateWindows(GRAPH_WUV_ALL);
	};
*/
	lCurrent_X += 1;
    };
}

void CGraphBarCtrl::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
    CRect rect(100, 100, pDC->GetDeviceCaps(HORZRES) - 100, pDC->GetDeviceCaps(VERTRES) - 100);
    m_graphCtrl.DrawGraphToDC(pDC, rect);
	
//	CView::OnPrint(pDC, pInfo);
}


void CGraphBarCtrl::RemoveGraph(int index)
{
	m_graphCtrl.RemoveGraph(index, TRUE);

}

void CGraphBarCtrl::ToggleGraphFlag(unsigned long graph_flag, BOOL bUpdate)
{
    DWORD win_flags = m_graphCtrl.GetGraphFlags();
    if ((win_flags & graph_flag) == graph_flag)
    {
	win_flags = win_flags & (~graph_flag);
    } else
    {
	win_flags = win_flags | graph_flag;
    };
    m_graphCtrl.SetGraphFlags(win_flags, bUpdate);
}


void CGraphBarCtrl::GraphAutoScale()
{
	m_graphCtrl.SetGraphFlags(m_graphCtrl.GetGraphFlags() | GRAPH_AUTOSCALE, TRUE);	
}

void CGraphBarCtrl::SetToolTipCoordenates()
{

	ToggleGraphFlag(GRAPH_SHOW_TOOLTIP, TRUE);
}

void CGraphBarCtrl::SetSquarePoints()
{

	ToggleGraphFlag(GRAPH_SQUAREPOINTS, TRUE);

}

void CGraphBarCtrl::SetGraphAxis()
{
	
	ToggleGraphFlag(GRAPH_DRAW_AXIS, TRUE);
		
}

void CGraphBarCtrl::SetGraphScatter()
{

	ToggleGraphFlag(GRAPH_GRAPH_SCATTER, TRUE);	
}

void CGraphBarCtrl::OnGraphAxisProperties() 
{
	CGraphAxisDlg dlg;

    CAxisProps* axis = m_graphCtrl.GetAxisProps(GRAPH_X_AXIS);
    
	dlg.m_x_precision = axis->GetPrecision();
    dlg.m_x_title = axis->GetTitle();
    dlg.m_x_uom = axis->GetUOM();

    axis = m_graphCtrl.GetAxisProps(GRAPH_Y_AXIS);
    dlg.m_y_precision = axis->GetPrecision();
    dlg.m_y_title = axis->GetTitle();
    dlg.m_y_uom = axis->GetUOM();

	
    if ( dlg.DoModal() == IDOK)
	{
		m_graphCtrl.SetAxisProps(dlg.m_x_title, dlg.m_x_uom, dlg.m_x_precision, GRAPH_X_AXIS, TRUE);
		m_graphCtrl.SetAxisProps(dlg.m_y_title, dlg.m_y_uom, dlg.m_y_precision, GRAPH_Y_AXIS, TRUE);
	}
	

}

void CGraphBarCtrl::OnGraphCoordinates() 
{

	CGraphCoordinatesDlg dlg;

	double x1, x2, y1, y2;
	m_graphCtrl.GetGraphWorldCoords(&x1, &x2, &y1, &y2);
	
	dlg.m_x1 = x1;
    dlg.m_x2 = x2;
    dlg.m_y1 = y1;
    dlg.m_y2 = y2;

	if ( dlg.DoModal() == IDOK)
	{
		m_graphCtrl.SetGraphWorldCoords(dlg.m_x1, dlg.m_x2, dlg.m_y1, dlg.m_y2, TRUE);
		
	}
	

}


void CGraphBarCtrl::OnGraphSetTitle()
{
	CGraphComboBox	m_graph_combo;
	
	CArray<CGraphProps*, CGraphProps*> grprops;

	
	int index = m_graph_combo.GetCurSel();
    if (index == -1) 
		return;
    
	//CGraphProps* grprops = m_graphCtrl.GetGraph(TRUE);
	CGraphProps* grprop = grprops.GetAt(index);
   
	
	CGraphTitlePrompt dlg;
    
	dlg.m_title = grprop->GetTitle();
    
	
	/*
	
	if (dlg.DoModal() == IDOK)
    {
	grprop->SetTitle(dlg.m_title);
	m_graph_combo.RedrawWindow();
	UpdateData(FALSE);
    };
	*/
	
}
