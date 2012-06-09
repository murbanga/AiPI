// WorkspaceView.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "WorkspaceTabDoc.h"
#include "WorkspaceView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView

IMPLEMENT_DYNCREATE(CWorkspaceView, CView)

CWorkspaceView::CWorkspaceView()
{
}

CWorkspaceView::~CWorkspaceView()
{
}


BEGIN_MESSAGE_MAP(CWorkspaceView, CView)
	//{{AFX_MSG_MAP(CWorkspaceView)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView drawing

void CWorkspaceView::OnDraw(CDC* pDC)
{
	CWorkspaceTabDoc* pDoc = GetDocument();
	
	g_projectDate = pDoc->m_strInfoArray.GetAt(0);
	g_projectName = pDoc->m_strInfoArray.GetAt(1);
	g_projectAuthor = pDoc->m_strInfoArray.GetAt(2);
	g_projectDesc = pDoc->m_strInfoArray.GetAt(3);
	g_projectRoot = pDoc->m_strInfoArray.GetAt(4);
	g_projectInference = pDoc->m_strInfoArray.GetAt(5);
	g_projectResource[0] = pDoc->m_strInfoArray.GetAt(6);
	g_projectResource[1] = pDoc->m_strInfoArray.GetAt(7);
	g_projectResource[2] = pDoc->m_strInfoArray.GetAt(8);
	g_projectResource[3] = pDoc->m_strInfoArray.GetAt(9);
		


	int yPosition = -400;
	int xPosition = 200;

	ShowFont2(pDC, xPosition, yPosition, 14, _T("Project Settings:"));
	ShowFont2(pDC, xPosition, yPosition, 14, _T(""));
	ShowFont1(pDC, xPosition, yPosition, 10, _T("Project Name:   ") + g_projectName );
	ShowFont1(pDC, xPosition, yPosition, 10, _T("Project was created:   ") + g_projectDate );
	ShowFont1(pDC, xPosition, yPosition, 10, _T(""));

	ShowFont1(pDC, xPosition, yPosition, 10, _T("Project Author(s):   ") + g_projectAuthor );
	ShowFont1(pDC, xPosition, yPosition, 10, _T("Project Description:   ") + g_projectDesc );
	ShowFont1(pDC, xPosition, yPosition, 10, _T("Project Directory:   ") + g_projectRoot );
	ShowFont1(pDC, xPosition, yPosition, 10, _T("Inference Method :   ") + g_projectInference );
	
	ShowFont2(pDC, xPosition, yPosition, 14, _T("") );
	ShowFont2(pDC, xPosition, yPosition, 14, _T("Resources:") );
	ShowFont2(pDC, xPosition, yPosition, 14, _T("") );
	
	for(int i= 0; i<4; ++i)
	{
		switch(i)
		{
		case 0:
			ShowFont1(pDC, xPosition, yPosition, 10, _T("Images :   ") + g_projectResource[i]);
			break;
		case 1:
			ShowFont1(pDC, xPosition, yPosition, 10, _T("Videos :   ") + g_projectResource[i]);
			break;
		case 2:
			ShowFont1(pDC, xPosition, yPosition, 10, _T("DataBases :   ") + g_projectResource[i]);
			break;
		case 3:
			ShowFont1(pDC, xPosition, yPosition, 10, _T("Others :   ") + g_projectResource[i]);
			break;
		}
	}
    
    
    TRACE(_T("LOGPIXELSX = %d, LOGPIXELSY = %d\n"), pDC->GetDeviceCaps(LOGPIXELSX), pDC->GetDeviceCaps(LOGPIXELSY)); 
    TRACE(_T("HORZSIZE = %d, VERTSIZE = %d\n"), pDC->GetDeviceCaps(HORZSIZE), pDC->GetDeviceCaps(VERTSIZE)); 
    TRACE(_T("HORZRES = %d, VERTRES = %d\n"), pDC->GetDeviceCaps(HORZRES), pDC->GetDeviceCaps(VERTRES));

	pDoc->SetModifiedFlag(TRUE);

	/*
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CRect rect;
	GetClientRect(rect);
	rect.DeflateRect(0, 0);
	pMainFrame->m_wndWorkspaceTabView.MoveWindow(&rect);
	*/
		
}


CWorkspaceTabDoc* CWorkspaceView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorkspaceTabDoc)));
	return (CWorkspaceTabDoc*)m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView diagnostics

#ifdef _DEBUG
void CWorkspaceView::AssertValid() const
{
	CView::AssertValid();
}

void CWorkspaceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}



#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView message handlers

void CWorkspaceView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	//m_backPainterOrganizer.Attach(this, IDB_EMPTY_SCREEN);
	m_backPainterOrganizer.Attach(this, RGB(192, 192, 192));



	
	
}

void CWorkspaceView::ShowFont1(CDC* pDC, int& nxPos, int& nyPos, int nPoints, CString text)
{
    TEXTMETRIC tm;
    CFont      fontText;
    CString    strText;
    CSize      sizeText;

    fontText.CreateFont(-nPoints * 20, 0, 0, 0, 400, FALSE, FALSE, 0,
                        ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                        DEFAULT_PITCH | FF_SWISS, _T("Arial"));
    CFont* pOldFont = (CFont*) pDC->SelectObject(&fontText);
    pDC->GetTextMetrics(&tm);
	
	TRACE(_T("puntos = %d, tmHeight = %d, tmInternalLeading = %d,") _T(" tmExternalLeading = %d\n"), nPoints, tm.tmHeight,
          tm.tmInternalLeading, tm.tmExternalLeading);
	
	strText.Format(text, nPoints);
	
	sizeText = pDC->GetTextExtent(strText);
	
	TRACE(_T("anchura de cadena = %d, altura de cadena = %d\n"), sizeText.cx,
          sizeText.cy);
    
	pDC->TextOut(nxPos, nyPos, strText);
    pDC->SelectObject(pOldFont);
    nyPos -= tm.tmHeight + tm.tmExternalLeading;
	
}


void CWorkspaceView::ShowFont2(CDC* pDC, int& nxPos,  int& nyPos, int nPoints, CString text)
{
    TEXTMETRIC tm;
    CFont      fontText;
    CString    strText;
    CSize      sizeText;

    fontText.CreateFont(-nPoints * 20, 0, 0, 0, 400, FALSE, FALSE, 0,
                        ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                        CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                        DEFAULT_PITCH | FF_SWISS, _T("Times New Roman"));
    CFont* pOldFont = (CFont*) pDC->SelectObject(&fontText);
    pDC->GetTextMetrics(&tm);
	
	TRACE(_T("puntos = %d, tmHeight = %d, tmInternalLeading = %d,") _T(" tmExternalLeading = %d\n"), nPoints, tm.tmHeight,
          tm.tmInternalLeading, tm.tmExternalLeading);
	
	strText.Format(text, nPoints);
	
	sizeText = pDC->GetTextExtent(strText);
	
	TRACE(_T("anchura de cadena = %d, altura de cadena = %d\n"), sizeText.cx,
          sizeText.cy);
    
	pDC->TextOut(nxPos, nyPos, strText);
    pDC->SelectObject(pOldFont);
    nyPos -= tm.tmHeight + tm.tmExternalLeading;
}


void CWorkspaceView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	pDC->SetMapMode(MM_ANISOTROPIC);
	//pDC->SetMapMode(MM_LOENGLISH);

    pDC->SetWindowExt(1440, 1440);
    pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),
							-pDC->GetDeviceCaps(LOGPIXELSY));
	
	
}



void CWorkspaceView::PrintPageHeader(CDC* pDC)
{
	CString str;
	int yPosition = -20;
	int xPosition = 10;

	str = _T("AIPI Project Information       ") + PrintDate();
	ShowFont2(pDC, xPosition, yPosition, 8, str);
	ShowFont2(pDC, xPosition, yPosition, 8, _T("__________________________________________________________________________________________________________________________________________________"));
	
	
	/*
	//CPoint point1(0,0);
	//pDC->TextOut(point1.x, point1.y, str);
	//CPoint point2(0, 30);
	//pDC->TextOut(point2.x, point2.y, _T("__________________________________________________________________________________________________________________________________________________"));
	//CPoint point3(720, -720);
	//pDC->TextOut(point2.x, point2.y, _T("Aipi Project Settings:"));
	*/
	

}


void CWorkspaceView::PrintPageFooter(CDC* pDC)
{
	CString str;
	int yPosition = -14400;
	int xPosition = 0;

	ShowFont2(pDC, xPosition, yPosition, 14, _T("__________________________________________________________________________________________________________________________________________________"));
	

	CWorkspaceTabDoc *pDoc = GetDocument();
	str.Format(_T("Document Name:  %s"), (LPCTSTR) pDoc->GetTitle());
	
	ShowFont2(pDC, xPosition, yPosition, 8, str);
	

	//CPoint point1(0, 3100);
	//pDC->TextOut(point1.x, point1.y, str);
	
	str.Format(_T("Pag. %d"), m_nPage);
	ShowFont2(pDC, xPosition, yPosition, 8, str);
	

	/*
	CSize size = pDC->GetTextExtent(str);
	point1.x += 2300 - size.cx;
	pDC->TextOut(point1.x, point1.y, str);

	CPoint point2(0, 3050);
	pDC->TextOut(point2.x, point2.y, _T("_____________________________________________________________________________________________________________________________________________________"));
	*/

}



CString CWorkspaceView::PrintDate()
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

BOOL CWorkspaceView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// default preparation
	CWorkspaceTabDoc* pDoc = GetDocument();
	pInfo->SetMaxPage(pInfo->GetToPage()/CWorkspaceTabDoc::nLinesPerPage + 1);
	
	return DoPreparePrinting(pInfo);

}



void CWorkspaceView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	CFont font;

	CWorkspaceTabDoc* pDoc = GetDocument();
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
	
	
	WORKSPACEMAINVIEW::OnPrint(pDC, pInfo);
}

void CWorkspaceView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( ( nFlags & MK_LBUTTON ) == MK_LBUTTON )
	{

		CClientDC dc(this);
		dc.SetPixel(point.x, point.y, RGB(0,0,0));
	}
	
	CView::OnMouseMove(nFlags, point);
}


