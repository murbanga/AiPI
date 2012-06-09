// AIPIView.cpp : implementation of the CAIPIView class
//

#include "stdafx.h"
#include "AIPI.h"

#include "AIPIDoc.h"
#include "CntrItem.h"
#include "AIPIView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAIPIView

IMPLEMENT_DYNCREATE(CAIPIView, MAINVIEW)

BEGIN_MESSAGE_MAP(CAIPIView, MAINVIEW)
	//{{AFX_MSG_MAP(CAIPIView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_CTRL_IMG2_OPEN, OnCtrlImg2Open)
	ON_COMMAND(ID_CTRL_IMG2_ROTATELEFT, OnCtrlImg2Rotateleft)
	ON_COMMAND(ID_CTRL_IMG2_ROTATERIGHT, OnCtrlImg2Rotateright)
	ON_COMMAND(ID_CTRL_IMG2_ZOOMIN, OnCtrlImg2Zoomin)
	ON_COMMAND(ID_CTRL_IMG2_ZOOMOUT, OnCtrlImg2Zoomout)
	ON_COMMAND(ID_CTRL_IMG2_STRETCHNOTHING, OnCtrlImg2Stretchnothing)
	ON_COMMAND(ID_CTRL_IMG2_STRETCHHEIGHT, OnCtrlImg2Stretchheight)
	ON_COMMAND(ID_CTRL_IMG2_STRETCHWIDTH, OnCtrlImg2Stretchwidth)
	ON_COMMAND(ID_CTRL_IMG2_STRETCHALL, OnCtrlImg2Stretchall)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG2_OPEN, OnUpdateCtrlImg2Open)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG2_ROTATELEFT, OnUpdateCtrlImg2Rotateleft)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG2_ROTATERIGHT, OnUpdateCtrlImg2Rotateright)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG2_ZOOMIN, OnUpdateCtrlImg2Zoomin)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG2_ZOOMOUT, OnUpdateCtrlImg2Zoomout)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG2_STRETCHNOTHING, OnUpdateCtrlImg2Stretchnothing)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG2_STRETCHHEIGHT, OnUpdateCtrlImg2Stretchheight)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG2_STRETCHWIDTH, OnUpdateCtrlImg2Stretchwidth)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG2_STRETCHALL, OnUpdateCtrlImg2Stretchall)
	ON_COMMAND(ID_CTRL_NSCHART_PIE, OnCtrlNSChartPie)
	ON_COMMAND(ID_CTRL_NSCHART_BAR, OnCtrlNSChartBar)
	ON_COMMAND(ID_CTRL_NSCHART_GRAY, OnCtrlNSChartGray)
	ON_COMMAND(ID_CTRL_NSCHART_COLOR, OnCtrlNSChartColor)
	ON_COMMAND(ID_CTRL_NSCHART_LINE, OnCtrlNSChartLine)
	ON_COMMAND(ID_CTRL_NSCHART_ADD, OnCtrlNSChartAdd)
	ON_COMMAND(ID_CTRL_NSCHART_DEL, OnCtrlNSChartDel)
	ON_COMMAND(ID_CTRL_NSCHART_MODIFY, OnCtrlNSChartModify)
	ON_UPDATE_COMMAND_UI(ID_CTRL_NSCHART_PIE, OnUpdateCtrlNSChartPie)
	ON_UPDATE_COMMAND_UI(ID_CTRL_NSCHART_BAR, OnUpdateCtrlNSChartBar)
	ON_UPDATE_COMMAND_UI(ID_CTRL_NSCHART_GRAY, OnUpdateCtrlNSChartGray)
	ON_UPDATE_COMMAND_UI(ID_CTRL_NSCHART_COLOR, OnUpdateCtrlNSChartColor)
	ON_UPDATE_COMMAND_UI(ID_CTRL_NSCHART_LINE, OnUpdateCtrlNSChartLine)
	ON_UPDATE_COMMAND_UI(ID_CTRL_NSCHART_ADD, OnUpdateCtrlNSChartAdd)
	ON_UPDATE_COMMAND_UI(ID_CTRL_NSCHART_DEL, OnUpdateCtrlNSChartDel)
	ON_UPDATE_COMMAND_UI(ID_CTRL_NSCHART_MODIFY, OnUpdateCtrlNSChartModify)
	ON_COMMAND(ID_CTRL_CHARTBAR_ADD, OnCtrlChartBarSerie)
	ON_COMMAND(ID_CTRL_CHARTBAR_DEL, OnCtrlChartBarDel)
	ON_COMMAND(ID_CTRL_CHARTBAR_BCKCOLOR, OnCtrlChartBarBckColor)
	ON_COMMAND(ID_CTRL_CHARTBAR_LEGENDVISIBLE, OnCtrlChartBarLegendVisible)
	ON_COMMAND(ID_CTRL_CHARTBAR_PANENABLE, OnCtrlChartBarPanEnable)
	ON_COMMAND(ID_CTRL_CHARTBAR_ZOOMENABLE, OnCtrlChartBarZoomEnable)
	ON_COMMAND(ID_CTRL_CHARTBAR_TITLE, OnCtrlChartBarTitle)
	ON_COMMAND(ID_CTRL_CHARTBAR_AXIS, OnCtrlChartBarAxis)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CHARTBAR_ADD, OnUpdateCtrlChartBarSerie)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CHARTBAR_DEL, OnUpdateCtrlChartBarDel)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CHARTBAR_BCKCOLOR, OnUpdateCtrlChartBarBckColor)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CHARTBAR_LEGENDVISIBLE, OnUpdateCtrlChartBarLegendVisible)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CHARTBAR_PANENABLE, OnUpdateCtrlChartBarPanEnable)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CHARTBAR_ZOOMENABLE, OnUpdateCtrlChartBarZoomEnable)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CHARTBAR_TITLE, OnUpdateCtrlChartBarTitle)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CHARTBAR_AXIS, OnUpdateCtrlChartBarAxis)
	ON_COMMAND(ID_CTRL_GRAPHBAR_TOOLTIP, OnCtrlGraphBarToolTip)
	ON_COMMAND(ID_CTRL_GRAPHBAR_SQUAREPOINTS, OnCtrlGraphBarSquarePoints)
	ON_COMMAND(ID_CTRL_GRAPHBAR_AXIS, OnCtrlGraphBarAxis)
	ON_COMMAND(ID_CTRL_GRAPHBAR_AXISPROP, OnCtrlGraphBarAxisProp)
	ON_COMMAND(ID_CTRL_GRAPHBAR_SCATTER, OnCtrlGraphBarScatter)
	ON_COMMAND(ID_CTRL_GRAPHBAR_COORDINATES, OnCtrlGraphBarCoordinates)
	ON_COMMAND(ID_CTRL_GRAPHBAR_ANIMATION, OnCtrlGraphBarAnimation)
	ON_COMMAND(ID_CTRL_GRAPHBAR_QUIT, OnCtrlGraphBarQuit)
	ON_UPDATE_COMMAND_UI(ID_CTRL_GRAPHBAR_ANIMATION, OnUpdateCtrlGraphBarAnimation)
	ON_UPDATE_COMMAND_UI(ID_CTRL_GRAPHBAR_QUIT, OnUpdateCtrlGraphBarQuit)
	ON_UPDATE_COMMAND_UI(ID_CTRL_GRAPHBAR_TOOLTIP, OnUpdateCtrlGraphBarToolTip)
	ON_UPDATE_COMMAND_UI(ID_CTRL_GRAPHBAR_SCATTER, OnUpdateCtrlGraphBarScatter)
	ON_UPDATE_COMMAND_UI(ID_CTRL_GRAPHBAR_SQUAREPOINTS, OnUpdateCtrlGraphBarSquarePoints)
	ON_UPDATE_COMMAND_UI(ID_CTRL_GRAPHBAR_AXIS, OnUpdateCtrlGraphBarAxis)
	ON_UPDATE_COMMAND_UI(ID_CTRL_GRAPHBAR_AXISPROP, OnUpdateCtrlGraphBarAxisProp)
	ON_UPDATE_COMMAND_UI(ID_CTRL_GRAPHBAR_COORDINATES, OnUpdateCtrlGraphBarCoordinates)
	ON_COMMAND(ID_CTRL_CALENDAR_GOTODATE, OnCtrlCalendarGoToDate)
	ON_COMMAND(ID_CTRL_CALENDAR_TODAY, OnCtrlCalendarToday)
	ON_COMMAND(ID_CTRL_CALENDAR_SUNDAY, OnCtrlCalendarSunday)
	ON_COMMAND(ID_CTRL_CALENDAR_MONDAY, OnCtrlCalendarMonday)
	ON_COMMAND(ID_CTRL_CALENDAR_TUESDAY, OnCtrlCalendarTuesday)
	ON_COMMAND(ID_CTRL_CALENDAR_WEDNESDAY, OnCtrlCalendarWednesday)
	ON_COMMAND(ID_CTRL_CALENDAR_THURSDAY, OnCtrlCalendarThursday)
	ON_COMMAND(ID_CTRL_CALENDAR_FRIDAY, OnCtrlCalendarFriday)
	ON_COMMAND(ID_CTRL_CALENDAR_SATURDAY, OnCtrlCalendarSaturday)
	ON_COMMAND(ID_CTRL_CALENDAR_MARK, OnCtrlCalendarMark)
	ON_COMMAND(ID_CTRL_CALENDAR_ADD, OnCtrlCalendarAdd)
	ON_COMMAND(ID_CTRL_CALENDAR_CLEAR, OnCtrlCalendarClear)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CALENDAR_GOTODATE, OnUpdateCtrlCalendarGoToDate)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CALENDAR_TODAY, OnUpdateCtrlCalendarToday)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CALENDAR_SUNDAY, OnUpdateCtrlCalendarSunday)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CALENDAR_MONDAY, OnUpdateCtrlCalendarMonday)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CALENDAR_TUESDAY, OnUpdateCtrlCalendarTuesday)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CALENDAR_WEDNESDAY, OnUpdateCtrlCalendarWednesday)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CALENDAR_THURSDAY, OnUpdateCtrlCalendarThursday)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CALENDAR_FRIDAY, OnUpdateCtrlCalendarFriday)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CALENDAR_SATURDAY, OnUpdateCtrlCalendarSaturday)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CALENDAR_MARK, OnUpdateCtrlCalendarMark)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CALENDAR_ADD, OnUpdateCtrlCalendarAdd)
	ON_UPDATE_COMMAND_UI(ID_CTRL_CALENDAR_CLEAR, OnUpdateCtrlCalendarClear)
	ON_COMMAND(ID_CTRL_METER_MAX, OnCtrlMeterMax)
	ON_COMMAND(ID_CTRL_METER_MIN, OnCtrlMeterMin)
	ON_COMMAND(ID_CTRL_METER_RANGEDECIMALS, OnCtrlMeterRangeDecimals)
	ON_COMMAND(ID_CTRL_METER_VALUEDECIMALS, OnCtrlMeterValueDecimals)
	ON_COMMAND(ID_CTRL_METER_UNITS, OnCtrlMeterUnits)
	ON_COMMAND(ID_CTRL_METER_COLOR, OnCtrlMeterColor)
	ON_UPDATE_COMMAND_UI(ID_CTRL_METER_MAX, OnUpdateCtrlMeterMax)
	ON_UPDATE_COMMAND_UI(ID_CTRL_METER_MIN, OnUpdateCtrlMeterMin)
	ON_UPDATE_COMMAND_UI(ID_CTRL_METER_RANGEDECIMALS, OnUpdateCtrlMeterRangeDecimals)
	ON_UPDATE_COMMAND_UI(ID_CTRL_METER_VALUEDECIMALS, OnUpdateCtrlMeterValueDecimals)
	ON_UPDATE_COMMAND_UI(ID_CTRL_METER_UNITS, OnUpdateCtrlMeterUnits)
	ON_UPDATE_COMMAND_UI(ID_CTRL_METER_COLOR, OnUpdateCtrlMeterColor)
	ON_COMMAND(ID_CTRL_IMG_OPEN, OnCtrlImgOpen)
	ON_COMMAND(ID_CTRL_IMG_LEFT, OnCtrlImgLeft)
	ON_COMMAND(ID_CTRL_IMG_CENTERX, OnCtrlImgCenterx)
	ON_COMMAND(ID_CTRL_IMG_RIGHT, OnCtrlImgRight)
	ON_COMMAND(ID_CTRL_IMG_TOP, OnCtrlImgTop)
	ON_COMMAND(ID_CTRL_IMG_CENTERY, OnCtrlImgCentery)
	ON_COMMAND(ID_CTRL_IMG_BOTTOM, OnCtrlImgBottom)
	ON_COMMAND(ID_CTRL_IMG_SCALE, OnCtrlImgStretchnormal)
	ON_COMMAND(ID_CTRL_IMG_STRETCH, OnCtrlImgStretch)
	ON_COMMAND(ID_CTRL_IMG_STRETCHXY, OnCtrlImgStretchxy)
	ON_COMMAND(ID_CTRL_IMG_STRETCHSM, OnCtrlImgStretchsm)
	ON_COMMAND(ID_CTRL_IMG_TILE, OnCtrlImgTile)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG_OPEN, OnUpdateCtrlImgOpen)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG_LEFT, OnUpdateCtrlImgLeft)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG_CENTERX, OnUpdateCtrlImgCenterx)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG_RIGHT, OnUpdateCtrlImgRight)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG_TOP, OnUpdateCtrlImgTop)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG_CENTERY, OnUpdateCtrlImgCentery)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG_BOTTOM, OnUpdateCtrlImgBottom)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG_SCALE, OnUpdateCtrlImgStretchnormal)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG_STRETCH, OnUpdateCtrlImgStretch)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG_STRETCHXY, OnUpdateCtrlImgStretchxy)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG_STRETCHSM, OnUpdateCtrlImgStretchsm)
	ON_UPDATE_COMMAND_UI(ID_CTRL_IMG_TILE, OnUpdateCtrlImgTile)
	ON_COMMAND(ID_CTRL_LISTBAR_ADD, OnCtrlListBarAdd)
	ON_COMMAND(ID_CTRL_LISTBAR_DELETE, OnCtrlListBarDelete)
	ON_COMMAND(ID_CTRL_LISTBAR_INDENT, OnCtrlListBarIndent)
	ON_COMMAND(ID_CTRL_LISTBAR_HIGHLIGHT, OnCtrlListBarHighLight)
	ON_COMMAND(ID_CTRL_LISTBAR_BACKCOLOR, OnCtrlListBarBackColor)
	ON_COMMAND(ID_CTRL_LISTBAR_FONT, OnCtrlListBarFont)
	ON_COMMAND(ID_CTRL_LISTBAR_TEXTBKCOLOR, OnCtrlListBarTextBkColor)
	ON_UPDATE_COMMAND_UI(ID_CTRL_LISTBAR_ADD, OnUpdateCtrlListBarAdd)
	ON_UPDATE_COMMAND_UI(ID_CTRL_LISTBAR_DELETE, OnUpdateCtrlListBarDelete)
	ON_UPDATE_COMMAND_UI(ID_CTRL_LISTBAR_INDENT, OnUpdateCtrlListBarIndent)
	ON_UPDATE_COMMAND_UI(ID_CTRL_LISTBAR_HIGHLIGHT, OnUpdateCtrlListBarHighLight)
	ON_UPDATE_COMMAND_UI(ID_CTRL_LISTBAR_BACKCOLOR, OnUpdateCtrlListBarBackColor)
	ON_UPDATE_COMMAND_UI(ID_CTRL_LISTBAR_FONT, OnUpdateCtrlListBarFont)
	ON_UPDATE_COMMAND_UI(ID_CTRL_LISTBAR_TEXTBKCOLOR, OnUpdateCtrlListBarTextBkColor)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_FONTCOLOR, OnCtrlListMultiOptionColor)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_FONTTYPE, OnCtrlListMultiOptionFontType)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_RESETFONTTYPE, OnCtrlListmultioptionResetFontType)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_DELETEITEM, OnCtrlListMultiOptionDeleteItem)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_CLEAR, OnCtrlListMultiOptionClear)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_SORT, OnCtrlListMultiOptionSort)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_CHECKABLE, OnCtrlListMultiOptionCheckable)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_MULTICHK, OnCtrlListMultiOptionMultichk)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_EDITABLE, OnCtrlListMultiOptionEditable)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_GRIDLINES, OnCtrlListMultiOptionGridLines)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_AUTOEDIT, OnCtrlListMultiOptionAutoEdit)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_SHOWSELECTION, OnCtrlListMultiOptionShowSelection)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_HORIZONTALGRID, OnCtrlListMultiOptionHorizontalGrid)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_VERTICALGRID, OnCtrlListMultiOptionVerticalGrid)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_COLRESIZE, OnCtrlListMultiOptionColResize)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_RIGHT, OnCtrlListMultiOptionRight)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_CENTER, OnCtrlListMultiOptionCenter)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_LEFT, OnCtrlListMultiOptionLeft)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_FONTBKCOLOR, OnCtrlListMultiOptionFontBkColor)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_BKCOLOR, OnCtrlListMultiOptionBkColor)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_GRIDLINESCOLOR, OnCtrlListMultiOptionGridLinesColor)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_NORMALGRIDLINES, OnCtrlListMultiOptionNormalGridLines)
	ON_COMMAND(ID_CTRL_LISTMULTIOPTION_NORMALCHKBOX, OnCtrlListMultiOptionNormalChkBox)
	ON_COMMAND(ID_CTRL_INFOBAR_FONTSTYLE, OnCtrlInfoBarFontStyle)
	ON_COMMAND(ID_CTRL_INFOBAR_FONTCOLOR, OnCtrlInfoBarFontColor)
	ON_COMMAND(ID_CTRL_INFOBAR_BKCOLOR, OnCtrlInfoBarBkColor)
	ON_COMMAND(ID_CTRL_OLEDBDLG_MSACESS, OnCtrlOledbDlgMsAcess)
	ON_COMMAND(ID_CTRL_OLEDBDLG_MSSQLSERVER, OnCtrlOledbDlgMsSqlServer)
	ON_COMMAND(ID_CTRL_OLEDBDLG_MSORACLE, OnCtrlOledbDlgMsOracle)
	ON_COMMAND(ID_CTRL_OLEDBDLG_ORACLE, OnCtrlOledbDlgOracle)
	ON_COMMAND(ID_CTRL_OLEDBDLG_MYSQL, OnCtrlOledbDlgMySql)
	ON_COMMAND(ID_CTRL_OLEDBDLG_DB2, OnCtrlOledbDlgDb2)
	ON_COMMAND(ID_CTRL_DXFCADDLG_OPEN, OnCtrlDxfCadDlgOpen)
	ON_COMMAND(ID_SETTINGS_SKIN_CLASSIC, OnSettingsSkinClassic)
	ON_COMMAND(ID_SETTINGS_SKIN_OFFICEXP, OnSettingsSkinOfficeXP)
	ON_COMMAND(ID_SETTINGS_SKIN_OFFICE2003, OnSettingsSkinOffice2003)
	ON_COMMAND(ID_EXEC_LOAD, OnExecLoad)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAIPIView construction/destruction

CAIPIView::CAIPIView()
{
	// TODO: add construction code here

}

CAIPIView::~CAIPIView()
{
}

int CAIPIView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRichEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_lpRichEditOle->AddRef();
	
	return 0;
}

BOOL CAIPIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CAIPIView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();
	UpdateSkinMenus();
		
	//Set font type 
	CRichEditCtrl& rCtrl = GetRichEditCtrl();
	CFont m_Font;
	LOGFONT lf;
	memset( &lf, 0, sizeof( LOGFONT));
	lf.lfHeight = -14;
	_tcscpy( lf.lfFaceName, _T("Verdana"));
	m_Font.CreateFontIndirect(&lf);
	rCtrl.SetFont( &m_Font);

	
	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 1200));

	UpdateSkinMenus();
	
	
}






/////////////////////////////////////////////////////////////////////////////
// CAIPIView printing

BOOL CAIPIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	//CAIPIDoc* pDoc = GetDocument();
	//pInfo->SetMaxPage(pInfo->GetToPage()/CAIPIDoc::nLinesPerPage + 1);
	return DoPreparePrinting(pInfo);
}

void CAIPIView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	
	CFont font;

	CAIPIDoc* pDoc = GetDocument();
	m_nPage = pInfo->m_nCurPage; // en beneficio de PrintPageFooter
    
	// fuente de 14 puntos, tamaño fijo
	font.CreateFont(-30, 0, 0, 0, 400, FALSE, FALSE,
	                0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
	                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	                DEFAULT_PITCH | FF_MODERN, _T("Arial"));
	                // Courier New es una fuente TrueType 
    CFont* pOldFont = (CFont*) (pDC->SelectObject(&font));
    
        
	PrintPageHeader(pDC);
	PrintPageFooter(pDC); 
	
	pDC->SelectObject(pOldFont);
	
	MAINVIEW::OnPrint(pDC, pInfo);
	
}

void CAIPIView::PrintPageHeader(CDC *pDC)
{
	CString str;

	str = _T("AIPI Sesion Report       ") + PrintDate();
	CPoint point1(0,0);
	pDC->TextOut(point1.x, point1.y, str);
	CPoint point2(0, 30);
	pDC->TextOut(point2.x, point2.y, _T("__________________________________________________________________________________________________________________________________________________"));


}

void CAIPIView::PrintPageFooter(CDC *pDC)
{
	CString str;
	
	CPoint point1(0, 3100);
	CAIPIDoc *pDoc = GetDocument();
	str.Format(_T("Document Name:  %s"), (LPCTSTR) pDoc->GetTitle());
	pDC->TextOut(point1.x, point1.y, str);
	
	str.Format(_T("Pag. %d"), m_nPage);

	CSize size = pDC->GetTextExtent(str);
	point1.x += 2300 - size.cx;
	pDC->TextOut(point1.x, point1.y, str);

	CPoint point2(0, 3050);
	pDC->TextOut(point2.x, point2.y, _T("_____________________________________________________________________________________________________________________________________________________"));



}

CString CAIPIView::PrintDate()
{
    _TCHAR buffer[10];
	
	WORD w_day, w_month, w_year, w_hour, w_minute, w_second;
	CString s_day, s_month, s_year, s_hour, s_minute, s_second;	
	
	SYSTEMTIME t;
	GetSystemTime(&t);

	GetLocalTime(&t);
	w_day = t.wDay;
	w_month = t.wMonth;
	w_year = t.wYear;
	w_hour = t.wHour;
	w_minute = t.wMinute;
	w_second = t.wSecond;
	
	s_day = _itot(w_day, buffer, 10);
	s_month = _itot(w_month, buffer, 10);
	s_year = _itot(w_year, buffer, 10);
	s_hour = _itot(w_hour, buffer, 10);
	s_minute = _itot(w_minute, buffer, 10);
	s_second = _itot(w_second, buffer, 10);

	return _T("Date: ") + s_day + _T("/") + s_month + _T("/") + s_year + _T("  Time: ") + s_hour + _T(":") + s_minute + _T(":") + s_second;
		

}


void CAIPIView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   m_lpRichEditOle->Release();
}


/////////////////////////////////////////////////////////////////////////////
// CAIPIView diagnostics

#ifdef _DEBUG
void CAIPIView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CAIPIView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CAIPIDoc* CAIPIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAIPIDoc)));
	return (CAIPIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAIPIView message handlers


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ImageCtrl V.2.0  Functions///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnCtrlImg2Open() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageDlg.IsVisible())
	{
		pMainFrame->m_wndImageDlg.OpenImage();
	}
}

void CAIPIView::OnCtrlImg2Rotateleft() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageDlg.IsVisible())
	{
		pMainFrame->m_wndImageDlg.RotateLeft();
	}	
}

void CAIPIView::OnCtrlImg2Rotateright() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageDlg.IsVisible())
	{
		pMainFrame->m_wndImageDlg.RotateRight();
	}	
}

void CAIPIView::OnCtrlImg2Zoomin() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageDlg.IsVisible())
	{
		pMainFrame->m_wndImageDlg.ZoomIn();
	}	
}

void CAIPIView::OnCtrlImg2Zoomout() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageDlg.IsVisible())
	{
		pMainFrame->m_wndImageDlg.ZoomOut();
	}	
}



void CAIPIView::OnCtrlImg2Stretchnothing() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageDlg.IsVisible())
	{
		pMainFrame->m_wndImageDlg.StretchNothing();
	}
}


void CAIPIView::OnCtrlImg2Stretchheight() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageDlg.IsVisible())
	{
		pMainFrame->m_wndImageDlg.StretchHeight();
	}	
}

void CAIPIView::OnCtrlImg2Stretchwidth() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageDlg.IsVisible())
	{
		pMainFrame->m_wndImageDlg.StretchWidth();
	}	
}


void CAIPIView::OnCtrlImg2Stretchall() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageDlg.IsVisible())
	{
		pMainFrame->m_wndImageDlg.StretchAll();
	}	
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Update ImageCtrl v.2.0 Functions///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnUpdateCtrlImg2Open(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageDlg.IsWindowVisible()== 1);
		
}

void CAIPIView::OnUpdateCtrlImg2Rotateleft(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageDlg.IsWindowVisible()== 1);
	
}

void CAIPIView::OnUpdateCtrlImg2Rotateright(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageDlg.IsWindowVisible()== 1);
		
}

void CAIPIView::OnUpdateCtrlImg2Zoomin(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageDlg.IsWindowVisible()== 1);
	
}

void CAIPIView::OnUpdateCtrlImg2Zoomout(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageDlg.IsWindowVisible()== 1);
	
	
}

void CAIPIView::OnUpdateCtrlImg2Stretchnothing(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageDlg.IsWindowVisible()== 1);
		
}

void CAIPIView::OnUpdateCtrlImg2Stretchheight(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageDlg.IsWindowVisible()== 1);
	
}

void CAIPIView::OnUpdateCtrlImg2Stretchwidth(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageDlg.IsWindowVisible()== 1);
	
	
}

void CAIPIView::OnUpdateCtrlImg2Stretchall(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageDlg.IsWindowVisible()== 1);
	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///NSChartCtrl Functions///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CAIPIView::OnCtrlNSChartPie() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndNSChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndNSChartBarCtrl.OnPieStyle();
	}
}

void CAIPIView::OnCtrlNSChartBar() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndNSChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndNSChartBarCtrl.OnBarStyle();
	}	
}

void CAIPIView::OnCtrlNSChartGray() 
{
	
	
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndNSChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndNSChartBarCtrl.OnGrayBackground();
	}
	

}

void CAIPIView::OnCtrlNSChartColor() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndNSChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndNSChartBarCtrl.OnColorBackground();
	}	
	
}

void CAIPIView::OnCtrlNSChartLine() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndNSChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndNSChartBarCtrl.OnLineBackground();
	}	
}

void CAIPIView::OnCtrlNSChartAdd() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndNSChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndNSChartBarCtrl.OnAdd();
	}	
}

void CAIPIView::OnCtrlNSChartDel() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndNSChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndNSChartBarCtrl.OnDel();
	}		
}

void CAIPIView::OnCtrlNSChartModify() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndNSChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndNSChartBarCtrl.OnModify();
	}	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Update NSChartCtrl Functions///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnUpdateCtrlNSChartPie(CCmdUI* pCmdUI) 
{
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndNSChartBarCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlNSChartBar(CCmdUI* pCmdUI) 
{
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndNSChartBarCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlNSChartGray(CCmdUI* pCmdUI) 
{
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndNSChartBarCtrl.IsWindowVisible()== 1);
}

void CAIPIView::OnUpdateCtrlNSChartColor(CCmdUI* pCmdUI) 
{
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndNSChartBarCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlNSChartLine(CCmdUI* pCmdUI) 
{
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndNSChartBarCtrl.IsWindowVisible()== 1);
}

void CAIPIView::OnUpdateCtrlNSChartAdd(CCmdUI* pCmdUI) 
{
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndNSChartBarCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlNSChartDel(CCmdUI* pCmdUI) 
{
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndNSChartBarCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlNSChartModify(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndNSChartBarCtrl.IsWindowVisible()== 1);		
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ChartBarCtrl Functions///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CAIPIView::OnCtrlChartBarSerie() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndChartBarCtrl.OnAddSeries();
	}	
	
}



void CAIPIView::OnCtrlChartBarDel() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndChartBarCtrl.OnDeleteSeries();
	}
	
}

void CAIPIView::OnCtrlChartBarBckColor() 
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndChartBarCtrl.OnChangeBckCol();
	}	
}


void CAIPIView::OnCtrlChartBarLegendVisible() 
{
	
	
	/*
	if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndChartBarCtrl.OnLegendVisible();
	}
	*/

	/*
	CNewMenu menu;
	CNewMenu submenu = menu.GetSubMenu(3)->GetSubMenu(7);
	menu.LoadMenu(IDR_MAINFRAME);
	UINT state = submenu->GetMenuState(ID_CTRL_CHARTBAR_LEGENDVISIBLE, MF_COMMAND);
	
	if(state & MF_CHECKED)
	{
		submenu->CheckMenuItem(ID_CTRL_CHARTBAR_LEGENDVISIBLE, MF_UNCHECKED|MF_COMMAND);
	}
	else
	{
		submenu->CheckMenuItem(ID_CTRL_CHARTBAR_LEGENDVISIBLE, MF_CHECKED|MF_COMMAND);
	}
*/

	
/*
	CWnd *pVentanaPadre = GetParent();
	CMenu *pMenu = pVentanaPadre->GetSubMenu(3)->GetSubMenu(8)

	if( pMenu->GetMenuState(ID_CTRL_CHARTBAR_LEGENDVISIBLE, MF_BYCOMMAND) == MF_CHECKED)
	{
	   		
			MessageBox(_T("Estoy 1"));
			if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
			{
				pMenu->CheckMenuItem( ID_CTRL_CHARTBAR_LEGENDVISIBLE, MF_CHECKED | MF_BYCOMMAND);
				pMainFrame->m_wndChartBarCtrl.OnLegendVisible();
			}		
	}
	if( pMenu->GetMenuState(ID_CTRL_CHARTBAR_LEGENDVISIBLE, MF_BYCOMMAND) == MF_UNCHECKED)
	{
	   	MessageBox(_T("Estoy 2"));	
		if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
			{
				pMenu->CheckMenuItem( ID_CTRL_CHARTBAR_LEGENDVISIBLE, MF_UNCHECKED | MF_BYCOMMAND);
				pMainFrame->m_wndChartBarCtrl.OnLegendNotVisible();
			}
	}

*/	


	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	static UINT uIdMenu = ID_CTRL_CHARTBAR_LEGENDVISIBLE;
	
	CMenu *pMenu = pMainFrame->GetMenu();
	
	UINT state = pMenu->GetMenuState(uIdMenu, MF_BYCOMMAND);
		ASSERT(state != 0xFFFFFFFF);
			
	if( state == 256)
	{
	   		if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
			{
				pMainFrame->m_wndChartBarCtrl.OnLegendVisible();
				pMenu->CheckMenuItem( uIdMenu, MF_CHECKED | MF_BYCOMMAND );
				//pMainFrame->m_wndToolBarChartBarCtrl.GetToolBarCtrl().CheckButton(uIdMenu, TRUE);
			}		
	}
	else
	{
			if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
			{
				pMainFrame->m_wndChartBarCtrl.OnLegendNotVisible();
				pMenu->CheckMenuItem( uIdMenu, MF_UNCHECKED | MF_BYCOMMAND );
				//pMainFrame->m_wndToolBarChartBarCtrl.GetToolBarCtrl().CheckButton(uIdMenu, FALSE);
					
			}
	}
	/*
		m_uMenuChartBar = LOWORD( GetCurrentMessage()->wParam);
	
	if( pMenu->GetMenuState(m_uMenuChartBar, MF_BYCOMMAND) == MF_UNCHECKED)
	{
	   		MessageBox(_T("Estoy 2"));
			if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
			{
				pMainFrame->m_wndChartBarCtrl.OnLegendNotVisible();
			}
	}
	
	pMenu->CheckMenuItem( uPrevSelect, MF_UNCHECKED | MF_BYCOMMAND);
	pMenu->CheckMenuItem( m_uMenuChartBar, MF_CHECKED | MF_BYCOMMAND );

	uPrevSelect = m_uMenuChartBar;
	*/

}

void CAIPIView::OnCtrlChartBarPanEnable() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	static UINT uIdMenu = ID_CTRL_CHARTBAR_PANENABLE;
	
	CMenu *pMenu = pMainFrame->GetMenu();
	
	UINT state = pMenu->GetMenuState(uIdMenu, MF_BYCOMMAND);
		ASSERT(state != 0xFFFFFFFF);
	
	
	if( state == 256)
	{
	   		if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
			{
				pMainFrame->m_wndChartBarCtrl.OnPanChecked();
				pMenu->CheckMenuItem( uIdMenu, MF_CHECKED | MF_BYCOMMAND );
				//pMainFrame->m_wndToolBarChartBarCtrl.GetToolBarCtrl().CheckButton(uIdMenu, TRUE);
			}		
	}
	else
	{
			if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
			{
				pMainFrame->m_wndChartBarCtrl.OnPanUnChecked();
				pMenu->CheckMenuItem( uIdMenu, MF_UNCHECKED | MF_BYCOMMAND );
				//pMainFrame->m_wndToolBarChartBarCtrl.GetToolBarCtrl().CheckButton(uIdMenu, FALSE);
			}
	}
	
}

void CAIPIView::OnCtrlChartBarZoomEnable() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	static UINT uIdMenu = ID_CTRL_CHARTBAR_ZOOMENABLE;
	
	CMenu *pMenu = pMainFrame->GetMenu();
	
	UINT state = pMenu->GetMenuState(uIdMenu, MF_BYCOMMAND);
		ASSERT(state != 0xFFFFFFFF);
	
	if( state == 256)
	{
	   		if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
			{
				pMainFrame->m_wndChartBarCtrl.OnZoomChecked();
				pMenu->CheckMenuItem( uIdMenu, MF_CHECKED | MF_BYCOMMAND );
				//pMainFrame->m_wndToolBarChartBarCtrl.GetToolBarCtrl().CheckButton(uIdMenu, TRUE);
			}		
	}
	else
	{
			if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
			{
				pMainFrame->m_wndChartBarCtrl.OnZoomUnChecked();
				pMenu->CheckMenuItem( uIdMenu, MF_UNCHECKED | MF_BYCOMMAND );
				//pMainFrame->m_wndToolBarChartBarCtrl.GetToolBarCtrl().CheckButton(uIdMenu, FALSE);
			}
	}	
	
}

void CAIPIView::OnCtrlChartBarTitle() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndChartBarCtrl.OnChangeTitle();
	}

}

void CAIPIView::OnCtrlChartBarAxis() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndChartBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndChartBarCtrl.OnAxisOption();
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Update ChartBarCtrl Functions///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnUpdateCtrlChartBarSerie(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndChartBarCtrl.IsWindowVisible()== 1);
}

void CAIPIView::OnUpdateCtrlChartBarDel(CCmdUI* pCmdUI) 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndChartBarCtrl.IsWindowVisible()== 1);	
}


void CAIPIView::OnUpdateCtrlChartBarBckColor(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndChartBarCtrl.IsWindowVisible()== 1);		
	
}


void CAIPIView::OnUpdateCtrlChartBarLegendVisible(CCmdUI* pCmdUI) 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndChartBarCtrl.IsWindowVisible()== 1);
				

}


void CAIPIView::OnUpdateCtrlChartBarPanEnable(CCmdUI* pCmdUI) 
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndChartBarCtrl.IsWindowVisible()== 1);
	
}


void CAIPIView::OnUpdateCtrlChartBarZoomEnable(CCmdUI* pCmdUI) 
{
		CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
		pCmdUI->Enable( pMainFrame->m_wndChartBarCtrl.IsWindowVisible()== 1);
			
}


void CAIPIView::OnUpdateCtrlChartBarTitle(CCmdUI* pCmdUI) 
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndChartBarCtrl.IsWindowVisible()== 1);
		
}



void CAIPIView::OnUpdateCtrlChartBarAxis(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndChartBarCtrl.IsWindowVisible()== 1);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///GraphBarCtrl Functions///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnCtrlGraphBarSquarePoints() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndGraphBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndGraphBarCtrl.SetSquarePoints();
	}		
	
}

void CAIPIView::OnCtrlGraphBarAxis() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndGraphBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndGraphBarCtrl.SetGraphAxis();
	}		
		
}



void CAIPIView::OnCtrlGraphBarScatter() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndGraphBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndGraphBarCtrl.SetGraphScatter();
	}		
		
}


void CAIPIView::OnCtrlGraphBarAxisProp() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndGraphBarCtrl.IsVisible())
	{
		pMainFrame->m_wndGraphBarCtrl.OnGraphAxisProperties();
	}	
}

void CAIPIView::OnCtrlGraphBarCoordinates() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndGraphBarCtrl.IsVisible())
	{
		pMainFrame->m_wndGraphBarCtrl.OnGraphCoordinates();
	}		
}


void CAIPIView::OnCtrlGraphBarAnimation() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndGraphBarCtrl.IsVisible())
	{
		pMainFrame->m_wndGraphBarCtrl.OnDynamicGraph();
	}		
}

void CAIPIView::OnCtrlGraphBarQuit() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndGraphBarCtrl.IsVisible())
	{
		pMainFrame->m_wndGraphBarCtrl.QuitDynamicGraph();
	}	
	
}

void CAIPIView::OnCtrlGraphBarToolTip() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndGraphBarCtrl.IsVisible() )
	{
		pMainFrame->m_wndGraphBarCtrl.SetToolTipCoordenates();
	}		
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Update GraphBarCtrl Functions///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CAIPIView::OnUpdateCtrlGraphBarAnimation(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndGraphBarCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlGraphBarQuit(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndGraphBarCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlGraphBarToolTip(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndGraphBarCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlGraphBarScatter(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndGraphBarCtrl.IsWindowVisible()== 1);		
}

void CAIPIView::OnUpdateCtrlGraphBarSquarePoints(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndGraphBarCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlGraphBarAxis(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndGraphBarCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlGraphBarAxisProp(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndGraphBarCtrl.IsWindowVisible()== 1);
}

void CAIPIView::OnUpdateCtrlGraphBarCoordinates(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndGraphBarCtrl.IsWindowVisible()== 1);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///CalendarDlg Functions///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnCtrlCalendarGoToDate() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndCalendarDlg.IsVisible())
	{
		pMainFrame->m_wndCalendarDlg.OnCalendarGoTo();
	}
}



void CAIPIView::OnCtrlCalendarToday() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndCalendarDlg.IsVisible())
	{
		pMainFrame->m_wndCalendarDlg.OnCalendarGoToToday();
	}	
}

void CAIPIView::OnCtrlCalendarSunday() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndCalendarDlg.IsVisible())
	{
		pMainFrame->m_wndCalendarDlg.OnCalendarFirstDayOfWeekSunday();
	}	
}

void CAIPIView::OnCtrlCalendarMonday() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndCalendarDlg.IsVisible())
	{
		pMainFrame->m_wndCalendarDlg.OnCalendarFirstDayOfWeekMonday();
	}
}


void CAIPIView::OnCtrlCalendarTuesday() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndCalendarDlg.IsVisible())
	{
		pMainFrame->m_wndCalendarDlg.OnCalendarFirstDayOfWeekTuesday();
	}	
}


void CAIPIView::OnCtrlCalendarWednesday() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndCalendarDlg.IsVisible())
	{
		pMainFrame->m_wndCalendarDlg.OnCalendarFirstDayOfWeekWednesday();
	}
}



void CAIPIView::OnCtrlCalendarThursday() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndCalendarDlg.IsVisible())
	{
		pMainFrame->m_wndCalendarDlg.OnCalendarFirstDayOfWeekThursday();
	}	
}


void CAIPIView::OnCtrlCalendarFriday() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndCalendarDlg.IsVisible())
	{
		pMainFrame->m_wndCalendarDlg.OnCalendarFirstDayOfWeekFriday();
	}		
}

void CAIPIView::OnCtrlCalendarSaturday() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndCalendarDlg.IsVisible())
	{
		pMainFrame->m_wndCalendarDlg.OnCalendarFirstDayOfWeekSaturday();
	}		
}

void CAIPIView::OnCtrlCalendarMark() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndCalendarDlg.IsVisible())
	{
		pMainFrame->m_wndCalendarDlg.OnCalendarMarkSelected();
	}	
}

void CAIPIView::OnCtrlCalendarAdd() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndCalendarDlg.IsVisible())
	{
		pMainFrame->m_wndCalendarDlg.OnCalendarAddEntryToSelected();
	}
}


void CAIPIView::OnCtrlCalendarClear() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndCalendarDlg.IsVisible())
	{
		pMainFrame->m_wndCalendarDlg.OnCalendarClearSelected();
	}	
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Update CalendarDlg Functions///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnUpdateCtrlCalendarToday(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndCalendarDlg.IsWindowVisible()== 1);
		
}

void CAIPIView::OnUpdateCtrlCalendarGoToDate(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndCalendarDlg.IsWindowVisible()== 1);
		
}



void CAIPIView::OnUpdateCtrlCalendarSunday(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndCalendarDlg.IsWindowVisible()== 1);
		
}


void CAIPIView::OnUpdateCtrlCalendarMonday(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndCalendarDlg.IsWindowVisible()== 1);
		
}


void CAIPIView::OnUpdateCtrlCalendarTuesday(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndCalendarDlg.IsWindowVisible()== 1);
		
}


void CAIPIView::OnUpdateCtrlCalendarWednesday(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndCalendarDlg.IsWindowVisible()== 1);
		
}


void CAIPIView::OnUpdateCtrlCalendarThursday(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndCalendarDlg.IsWindowVisible()== 1);
	
}


void CAIPIView::OnUpdateCtrlCalendarFriday(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndCalendarDlg.IsWindowVisible()== 1);
		
}


void CAIPIView::OnUpdateCtrlCalendarSaturday(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndCalendarDlg.IsWindowVisible()== 1);
}



void CAIPIView::OnUpdateCtrlCalendarMark(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndCalendarDlg.IsWindowVisible()== 1);	
}




void CAIPIView::OnUpdateCtrlCalendarAdd(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndCalendarDlg.IsWindowVisible()== 1);
}



void CAIPIView::OnUpdateCtrlCalendarClear(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndCalendarDlg.IsWindowVisible()== 1);	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///3DMeterCtrl Functions///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnCtrlMeterMax() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndStaticMeterCtrl.IsVisible() )
	{
		pMainFrame->m_wndStaticMeterCtrl.OnMeterMax();
	}	
}

void CAIPIView::OnCtrlMeterMin() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndStaticMeterCtrl.IsVisible() )
	{
		pMainFrame->m_wndStaticMeterCtrl.OnMeterMin();
	}		
}

void CAIPIView::OnCtrlMeterRangeDecimals() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndStaticMeterCtrl.IsVisible() )
	{
		pMainFrame->m_wndStaticMeterCtrl.OnMeterScaleDecimals();
	}		
}

void CAIPIView::OnCtrlMeterValueDecimals() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndStaticMeterCtrl.IsVisible() )
	{
		pMainFrame->m_wndStaticMeterCtrl.OnMeterDecimals();
	}		
}

void CAIPIView::OnCtrlMeterUnits() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndStaticMeterCtrl.IsVisible() )
	{
		pMainFrame->m_wndStaticMeterCtrl.OnMeterUnits();
	}		
}

void CAIPIView::OnCtrlMeterColor() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndStaticMeterCtrl.IsVisible() )
	{
		pMainFrame->m_wndStaticMeterCtrl.OnMeterNeedleColor();
	}			
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Update 3DMeterCtrl Functions///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CAIPIView::OnUpdateCtrlMeterMax(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndStaticMeterCtrl.IsWindowVisible()== 1);		
}

void CAIPIView::OnUpdateCtrlMeterMin(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndStaticMeterCtrl.IsWindowVisible()== 1);		
}

void CAIPIView::OnUpdateCtrlMeterRangeDecimals(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndStaticMeterCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlMeterValueDecimals(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndStaticMeterCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlMeterUnits(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndStaticMeterCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlMeterColor(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndStaticMeterCtrl.IsWindowVisible()== 1);	
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///BitImageCtrl Functions///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAIPIView::OnCtrlImgOpen() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageCtrl.IsVisible() )
	{
		pMainFrame->m_wndImageCtrl.OpenImage();
	}
	
}

void CAIPIView::OnCtrlImgLeft() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageCtrl.IsVisible() )
	{
		pMainFrame->m_wndImageCtrl.OnLeft();
	}
	
}

void CAIPIView::OnCtrlImgCenterx() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageCtrl.IsVisible() )
	{
		pMainFrame->m_wndImageCtrl.OnCenterX();
	}
	

}

void CAIPIView::OnCtrlImgRight() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageCtrl.IsVisible() )
	{
		pMainFrame->m_wndImageCtrl.OnRight();
	}		
}

void CAIPIView::OnCtrlImgTop() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageCtrl.IsVisible() )
	{
		pMainFrame->m_wndImageCtrl.OnTop();
	}	
}

void CAIPIView::OnCtrlImgCentery() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageCtrl.IsVisible() )
	{
		pMainFrame->m_wndImageCtrl.OnCenterY();
	}		
}

void CAIPIView::OnCtrlImgBottom() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageCtrl.IsVisible() )
	{
		pMainFrame->m_wndImageCtrl.OnBottom();
	}	
}

void CAIPIView::OnCtrlImgStretchnormal() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageCtrl.IsVisible() )
	{
		pMainFrame->m_wndImageCtrl.OnStretchNormal();
	}		
	
}

void CAIPIView::OnCtrlImgStretch() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageCtrl.IsVisible() )
	{
		pMainFrame->m_wndImageCtrl.OnStretch();
	}	
}

void CAIPIView::OnCtrlImgStretchxy() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageCtrl.IsVisible() )
	{
		pMainFrame->m_wndImageCtrl.OnStretchXY();
	}		
}

void CAIPIView::OnCtrlImgStretchsm() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageCtrl.IsVisible() )
	{
		pMainFrame->m_wndImageCtrl.OnStretchSM();
	}		
}


void CAIPIView::OnCtrlImgTile() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if ( pMainFrame->m_wndImageCtrl.IsVisible() )
	{
		pMainFrame->m_wndImageCtrl.OnTile();
	}		
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Update BitImageCtrl Functions////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CAIPIView::OnUpdateCtrlImgOpen(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageCtrl.IsWindowVisible()== 1);
} 


void CAIPIView::OnUpdateCtrlImgLeft(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageCtrl.IsWindowVisible()== 1);
}


void CAIPIView::OnUpdateCtrlImgCenterx(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlImgRight(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlImgTop(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlImgCentery(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlImgBottom(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlImgStretchnormal(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlImgStretch(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlImgStretchxy(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlImgStretchsm(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageCtrl.IsWindowVisible()== 1);	
}

void CAIPIView::OnUpdateCtrlImgTile(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndImageCtrl.IsWindowVisible()== 1);	
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ListOptionBar Functions ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnCtrlListBarAdd() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListOptionCtrl.OnAddItem();
	}
	
}


void CAIPIView::OnCtrlListBarDelete() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListOptionCtrl.DeleteItem();
	}
	
}

void CAIPIView::OnCtrlListBarIndent() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListOptionCtrl.SetIndent();
	}
	
}


void CAIPIView::OnCtrlListBarHighLight() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListOptionCtrl.SetHighLightOnlyText();
	}
	
}

void CAIPIView::OnCtrlListBarBackColor() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListOptionCtrl.SetBkColor();
	}
	
	
}

void CAIPIView::OnCtrlListBarFont() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListOptionCtrl.SetItemFont();
	}
	
}

void CAIPIView::OnCtrlListBarTextBkColor() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListOptionCtrl.SetItemBkColor();
	}
	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ListOptionBar Update Functions ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnUpdateCtrlListBarAdd(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndListOptionCtrl.IsWindowVisible()== 1);	
	
}

void CAIPIView::OnUpdateCtrlListBarDelete(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndListOptionCtrl.IsWindowVisible()== 1);	
		
	
}

void CAIPIView::OnUpdateCtrlListBarIndent(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndListOptionCtrl.IsWindowVisible()== 1);	
	
}

void CAIPIView::OnUpdateCtrlListBarHighLight(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndListOptionCtrl.IsWindowVisible()== 1);	
		
	
}

void CAIPIView::OnUpdateCtrlListBarBackColor(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndListOptionCtrl.IsWindowVisible()== 1);	
		
}

void CAIPIView::OnUpdateCtrlListBarFont(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndListOptionCtrl.IsWindowVisible()== 1);	
		
}

void CAIPIView::OnUpdateCtrlListBarTextBkColor(CCmdUI* pCmdUI) 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pCmdUI->Enable( pMainFrame->m_wndListOptionCtrl.IsWindowVisible()== 1);	
	
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ListMultiOptionCtrl Functions ///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnCtrlListMultiOptionColor() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetTextColor();
	}
	
}


void CAIPIView::OnCtrlListMultiOptionFontType() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetFont();
	}	
}

void CAIPIView::OnCtrlListmultioptionResetFontType() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.ResetFont();
	}
}

void CAIPIView::OnCtrlListMultiOptionDeleteItem() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.DeleteItem();
	}	
}

void CAIPIView::OnCtrlListMultiOptionClear() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.Clear();
	}	
}

void CAIPIView::OnCtrlListMultiOptionSort() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.Sortable();
	}	
}

void CAIPIView::OnCtrlListMultiOptionCheckable() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetCheckable();
	}	
}

void CAIPIView::OnCtrlListMultiOptionMultichk() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetMulCheck();
	}	
}


void CAIPIView::OnCtrlListMultiOptionEditable() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetEditable();
	}
}


void CAIPIView::OnCtrlListMultiOptionGridLines() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetGridLines();
	}	
}

void CAIPIView::OnCtrlListMultiOptionAutoEdit() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetAutoEdit();
	}		
}

void CAIPIView::OnCtrlListMultiOptionShowSelection() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.ShowSelection();
	}	
}

void CAIPIView::OnCtrlListMultiOptionHorizontalGrid() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetHorizontalGrid();
	}	
}

void CAIPIView::OnCtrlListMultiOptionVerticalGrid() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetVerticalGrid();
	}	
}



void CAIPIView::OnCtrlListMultiOptionColResize() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetGridColResize();
	}	
}


void CAIPIView::OnCtrlListMultiOptionRight() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetRadioRight();
	}	
}

void CAIPIView::OnCtrlListMultiOptionCenter() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetRadioCenter();
	}	
}

void CAIPIView::OnCtrlListMultiOptionLeft() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetRadioLeft();
	}
}

void CAIPIView::OnCtrlListMultiOptionFontBkColor() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetTextBkColor();
	}	
}

void CAIPIView::OnCtrlListMultiOptionBkColor() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetBkColor();
	}		
}

void CAIPIView::OnCtrlListMultiOptionGridLinesColor() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetGridLinesColor();
	}
}

void CAIPIView::OnCtrlListMultiOptionNormalGridLines() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetNormalGridLines();
	}	
}

void CAIPIView::OnCtrlListMultiOptionNormalChkBox() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndListMultiOptionCtrl.IsVisible() )
	{
		pMainFrame->m_wndListMultiOptionCtrl.SetNormalCheckBox();
	}	
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/// InfoCtrl Functions ////
//////////////////////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnCtrlInfoBarFontStyle() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndEditInfoCtrl.IsVisible() )
	{
		pMainFrame->m_wndEditInfoCtrl.SetFontStyle();
	}
	
}



void CAIPIView::OnCtrlInfoBarFontColor() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndEditInfoCtrl.IsVisible() )
	{
		pMainFrame->m_wndEditInfoCtrl.SetFontColor();
	}
}


void CAIPIView::OnCtrlInfoBarBkColor() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndEditInfoCtrl.IsVisible() )
	{
		pMainFrame->m_wndEditInfoCtrl.SetBackColor();
	}
}



///////////////////////////////////////////////////////////////////////////////////////
//// OleDBDlg /////
////////////////////////////////////////////////////////////////////////////////////////


void CAIPIView::OnCtrlOledbDlgMsAcess() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndOleDBDlg.IsVisible() )
	{
		pMainFrame->m_wndOleDBDlg.OnOpenDatabaseConnection(MS_ACCESS);
	}
}


void CAIPIView::OnCtrlOledbDlgMsSqlServer() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndOleDBDlg.IsVisible() )
	{
		pMainFrame->m_wndOleDBDlg.OnOpenDatabaseConnection(MS_SQLSERVER);
	}	
}


void CAIPIView::OnCtrlOledbDlgMsOracle() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndOleDBDlg.IsVisible() )
	{
		pMainFrame->m_wndOleDBDlg.OnOpenDatabaseConnection(MS_ORACLE);
	}	
}


void CAIPIView::OnCtrlOledbDlgOracle() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndOleDBDlg.IsVisible() )
	{
		pMainFrame->m_wndOleDBDlg.OnOpenDatabaseConnection(ORACLE);
	}	
}

void CAIPIView::OnCtrlOledbDlgMySql() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndOleDBDlg.IsVisible() )
	{
		pMainFrame->m_wndOleDBDlg.OnOpenDatabaseConnection(MYSQL);
	}	
}

void CAIPIView::OnCtrlOledbDlgDb2() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndOleDBDlg.IsVisible() )
	{
		pMainFrame->m_wndOleDBDlg.OnOpenDatabaseConnection(DB2);
	}
}


///////////////////////////////////////////////////////////////////////////////
void CAIPIView::OnCtrlDxfCadDlgOpen() 
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();	 	
	if ( pMainFrame->m_wndDxfCadDlg.IsVisible() )
	{
		pMainFrame->m_wndDxfCadDlg.OnButton4();
	}	
}











void CAIPIView::OnSettingsSkinClassic() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->OnSettingsSkinClassic();
	pMainFrame->CheckMenuSkinType();

		
}

void CAIPIView::OnSettingsSkinOfficeXP() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->OnSettingsSkinOfficeXP();
	pMainFrame->CheckMenuSkinType();



	
}

void CAIPIView::OnSettingsSkinOffice2003() 
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->OnSettingsSkinOffice2003();
	pMainFrame->CheckMenuSkinType();

		

}


void CAIPIView::UpdateSkinMenus()
{
   /*
	TCHAR buffer[8];
   CString	str =  _itot( g_iSkinType, buffer, 10 );
   AfxMessageBox(_T("CAIPIView"));
   AfxMessageBox(str);
	*/

	switch(g_iSkinType)
	{
	case OXSkinClassic:
		OnSettingsSkinClassic();
		break;
	case OXSkinOfficeXP:
		OnSettingsSkinOfficeXP();
		break;
	case OXSkinOffice2003:
		OnSettingsSkinOffice2003();
		break;

	}

}


void CAIPIView::OnExecLoad() 
{
	g_bExecuteFlag  = true;
 	CAipi_Main main;
	main.execute();
	
}


