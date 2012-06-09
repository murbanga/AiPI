/* PERF__FREZ/PUB
 * ====================================================
 * CalendarCtrl.cpp : implementation file
 * Frederic Rezeau
 * 
 * Perf'Control Personal Edition calendar 
 *
 * If you like it, feel free to use it. 
 *
 * www.performlabs.com 
 * ==================================================== 
 */

#include "stdafx.h"
#include "CalendarCtrl.h"
//#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarCtrl

CCalendarCtrl::CCalendarCtrl()
{
	LOGFONT lf;
	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT),sizeof(lf),&lf);
	memcpy(lf.lfFaceName, "Arial", 5);
	lf.lfHeight = 13;
	m_DefaultFont.CreateFontIndirect(&lf);

	m_bMonthIsOdd		= false;
	m_bSelectionStarted = false;
	m_SelectionRange[0]	= 0;
	m_SelectionRange[1]	= 0;
	m_SelectionRange[2]	= 0;
	m_nVscrollMax		= 110;
	m_nVscrollPos		= m_nVscrollMax/2;
	m_BoundDown			= COleDateTime(1999,12,31,0,0,0); 
	m_BoundUp			= COleDateTime(2036,1,1,0,0,0);
	m_nMaxSel			= 42;
	m_nFirstWeekDay		= 1;
	m_pfnDataCallback	= NULL;
}

CCalendarCtrl::~CCalendarCtrl()
{
}

BEGIN_MESSAGE_MAP(CCalendarCtrl, CWnd)
	//{{AFX_MSG_MAP(CCalendarCtrl)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CCalendarCtrl::Create(DWORD dwStyle, const CRect &wndRect, CWnd *pParent, UINT nID, LPFN_CALENDAR_DATA_CALLBACK pfnDataCallback)
{
	BOOL bResult = CWnd::CreateEx(NULL, NULL, NULL, dwStyle, wndRect, pParent, nID);
	m_pfnDataCallback = pfnDataCallback;
    SetScrollRange(SB_VERT, 0, m_nVscrollMax, FALSE);
	Reset();
	return bResult;
}

void CCalendarCtrl::Reset()
{
	COleDateTime today(time(NULL));
	COleDateTime dtFirstDay(today.GetYear(), today.GetMonth(), 1,0,0,0); 
	
	if(dtFirstDay > m_BoundUp) 
		dtFirstDay = m_BoundUp;
	else if(dtFirstDay < m_BoundDown)	
		dtFirstDay = m_BoundDown;

	if (dtFirstDay.GetMonth()%2) 
		m_bMonthIsOdd = true;

	Goto(dtFirstDay);

	// Reset selection
	m_SelectionRange[1] = DateToSeconds(COleDateTime(today.GetYear(), today.GetMonth(), today.GetDay(),0,0,0));
	m_SelectionRange[0] = m_SelectionRange[1];

	// Reset scroll pos
	m_nVscrollPos = m_nVscrollMax/2;
	SetScrollPos(SB_VERT, m_nVscrollPos, TRUE);
}

void CCalendarCtrl::Goto(const COleDateTime& dtDate, bool bSelect)
{
	if( (dtDate < m_BoundUp) && 
		(dtDate > m_BoundDown) )
	{
		m_DateCurrent = dtDate;		
		if(m_nFirstWeekDay<1 || m_nFirstWeekDay>7)
			m_nFirstWeekDay = 1;

		COleDateTime dtIte(m_DateCurrent.GetYear(), m_DateCurrent.GetMonth(), m_DateCurrent.GetDay(),0,0,0);
		int narr[7];
		for (int d=0; d<7; d++)	
			narr[((m_nFirstWeekDay-1)+d)%7] = d;
		int nCellStart = narr[dtIte.GetDayOfWeek()-1];
		for(int i=0; i<nCellStart; i++)	
			dtIte -= COleDateTimeSpan(1,0,0,0);

		for(i=0; i<CALENDAR_ROWS ; i++)
		{
			for(int u=0; u<CALENDAR_COLUMNS; u++)
			{
				// Init the cell
				m_dayCells[i][u].date = dtIte;
				m_dayCells[i][u].bPartial = false;
				m_dayCells[i][u].bMark = false;
				m_dayCells[i][u].csaLines.RemoveAll();

				if(m_pfnDataCallback)
					m_pfnDataCallback(this, DateToSeconds(m_dayCells[i][u].date));
				dtIte += COleDateTimeSpan(1,0,0,0);
			}
		}

		if(bSelect)
		{
			m_RandomSelection.RemoveAll();
			m_SelectionRange[2] = 0;
			m_SelectionRange[1] = DateToSeconds(COleDateTime(m_DateCurrent.GetYear(), m_DateCurrent.GetMonth(), m_DateCurrent.GetDay(),0,0,0));
			m_SelectionRange[0] = m_SelectionRange[1];

			// Scrolling pos
			COleDateTime today(time(NULL));
			m_nVscrollPos = (m_nVscrollMax/2) + (m_DateCurrent-today).GetDays()/7;
			SetScrollPos(SB_VERT, m_nVscrollPos, TRUE);
		}
	}

	Invalidate(true);
}

void CCalendarCtrl::UpdateCells()
{
	if(m_pfnDataCallback)
		Goto(m_DateCurrent, false);
}

/////////////////////////////////////////////////////////////////////////////
// CCalendarCtrl message handlers

void CCalendarCtrl::OnPaint() 
{
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(&rc);

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap MemBitmap;
	MemBitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());
	CBitmap *pOldBitmap = MemDC.SelectObject(&MemBitmap);

	CBrush brBkGnd;
	brBkGnd.CreateSolidBrush(RGB(252,255,255));
	MemDC.FillRect(&rc ,&brBkGnd);
	MemDC.SetBkMode(TRANSPARENT);
	
	// Draw calendar elements
	DrawHeader(&MemDC);			
	DrawCells(&MemDC);	
	DrawGrid(&MemDC);

	// Render
	dc.BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
}

void CCalendarCtrl::DrawHeader(CDC* pDC)
{
	CRect rc;
	GetClientRect(&rc);
	rc.bottom = rc.top + CALENDAR_HEADER_HEIGHT;

	CRect rcLine(rc);
	rcLine.top = rcLine.bottom-1;
	for(int i=0; i<CALENDAR_HEADER_HEIGHT; i++)
	{
		pDC->FillSolidRect(rcLine, GetFadedBlue(i*4));
		rcLine.bottom--;
		rcLine.top = rcLine.bottom-1;
	}

	CFont* pOldFont = pDC->SelectObject(&m_DefaultFont);
	int nWidth = rc.Width()/CALENDAR_COLUMNS;
	bool bShort = false;
	for(i=0; i<CALENDAR_COLUMNS; i++)
	{
		CRect txtRect(i*nWidth, 0, (i+1)*nWidth, CALENDAR_HEADER_HEIGHT);
		CString csTitle(m_dayCells[0][i].date.Format(_T("%A")));
		CSize TitleSize(pDC->GetTextExtent(csTitle));
		if(TitleSize.cx	> txtRect.Width()){
			bShort = true;
			break;
		}
	}
	
	for(i=0 ; i<CALENDAR_COLUMNS; i++)
	{
		CString csTitle(m_dayCells[0][i].date.Format(_T("%A")));
		CRect txtRect(i*nWidth, 0, (i+1)*nWidth, CALENDAR_HEADER_HEIGHT);
		if(bShort)
			csTitle = csTitle.Left(3);
		pDC->DrawText(csTitle, txtRect, DT_CENTER|DT_VCENTER);
	}
	pDC->SelectObject(pOldFont);
}

void CCalendarCtrl::DrawGrid(CDC* pDC)
{
	CRect rc;
	GetClientRect(&rc);
	int nHeight = (rc.Height()-CALENDAR_HEADER_HEIGHT)/CALENDAR_ROWS;
	int nWidth = rc.Width()/CALENDAR_COLUMNS;

	CPen thinPen(PS_SOLID, 1, RGB(125,175,255));
	CPen* pOldPen = pDC->SelectObject(&thinPen);
	for(int i=1; i<CALENDAR_COLUMNS; i++)
	{
		pDC->MoveTo(i*nWidth, CALENDAR_HEADER_HEIGHT);
		pDC->LineTo(i*nWidth, rc.Height());
	}
	
	for(i=0; i<CALENDAR_ROWS; i++)
	{
		pDC->MoveTo(0,			(i*nHeight)+CALENDAR_HEADER_HEIGHT);
		pDC->LineTo(rc.Width(),	(i*nHeight)+CALENDAR_HEADER_HEIGHT);
	}
	pDC->SelectObject(pOldPen);
}

void CCalendarCtrl::DrawCells(CDC* pDC)
{
	CRect rc;
	GetClientRect(&rc);
	int ncHeight = (rc.Height()-CALENDAR_HEADER_HEIGHT)/CALENDAR_ROWS;
	int ncWidth = rc.Width()/CALENDAR_COLUMNS;

	CPen whitePen(PS_SOLID, 1, RGB(255,255,255));
	CPen blackPen(PS_SOLID, 1, RGB(0,0,0));

	CFont* pOldFont = pDC->SelectObject(&m_DefaultFont);
	CPen* pOldPen = pDC->SelectObject(&blackPen);

	for(int i=0; i<CALENDAR_ROWS ; i++)
	{
		for(int u=0; u<CALENDAR_COLUMNS ; u++)
		{
			CRect rect;
			if(GetRectFromCell(i, u, rect))
			{
				if(u == CALENDAR_COLUMNS-1) rect.right = rc.right;
				if(i == CALENDAR_ROWS-1) rect.bottom = rc.bottom;

				if((m_bMonthIsOdd &&  !(m_dayCells[i][u].date.GetMonth()%2))
					|| (!m_bMonthIsOdd && (m_dayCells[i][u].date.GetMonth()%2)))
				{
					CBrush br;
					br.CreateSolidBrush(CALENDAR_LIGHTGREY);
					pDC->FillRect(&rect ,&br);
				}

				COleDateTime today(time(NULL));
				bool btoday = false;
				if(today.GetDay() == m_dayCells[i][u].date.GetDay()	&& today.GetMonth() == m_dayCells[i][u].date.GetMonth()	&& today.GetYear() == m_dayCells[i][u].date.GetYear())
				{
					// Draw the frame 
					CRect rcLine(rect);
					rcLine.bottom = rcLine.top+15;
					rcLine.top = rcLine.bottom-1;
					for(int c=0; c<15; c++)
					{
						pDC->FillSolidRect(rcLine, GetFadedBlue(c*6));
						rcLine.bottom--;
						rcLine.top = rcLine.bottom-1;
					}
					btoday = true;
				}

				// Draw the selection
				bool bSelected = false;
				time_t tmax = max(m_SelectionRange[0], m_SelectionRange[1]);
				time_t tmin = min(m_SelectionRange[0], m_SelectionRange[1]);			
				time_t tcur = DateToSeconds(m_dayCells[i][u].date);				
				if(m_RandomSelection.GetCount())
				{	
					POSITION pos = m_RandomSelection.GetStartPosition();	 
					while (pos){
						void* p; DWORD date;
						m_RandomSelection.GetNextAssoc(pos, (void*&)date, p);
						if(date == (DWORD)tcur)
						{							
							CBrush br;
							br.CreateSolidBrush(GetFadedBlue(70));
							CRect selRect(rect);
							if(btoday)	selRect.top += 15;
							pDC->FillRect(&selRect, &br);
							bSelected = true;
						}
					}

					if(m_SelectionRange[2] == tcur)
					{
						rect.left+=2;	rect.right -=1;
						rect.top+=2;	rect.bottom -=1;
						pDC->DrawFocusRect(rect);
					}
				}
				else if((tmax >= tcur) && (tcur >= tmin))
				{						
					CRect selRect(rect);
					CBrush br;
					br.CreateSolidBrush(GetFadedBlue(70));
					if(btoday)	selRect.top += 15;
					pDC->FillRect(&selRect, &br);
					bSelected = true;
				}

				// Out of range
				if( (m_dayCells[i][u].date >= m_BoundUp) || 
					(m_dayCells[i][u].date <= m_BoundDown) )	
				{
					CRect selRect(rect);
					CBrush br;
					br.CreateSolidBrush(RGB(255,225,225));
					pDC->FillRect(&selRect, &br);
				}

				if(m_dayCells[i][u].bMark)
				{
					CBrush br;
					br.CreateSolidBrush(RGB(255,104,4));
					CRect rcMark(rect);
					rcMark.DeflateRect(3,3);
					rcMark.right = rcMark.left +6;
					rcMark.bottom = rcMark.top +6;
					pDC->FillRect(&rcMark, &br);
				}

				// draw inside...
				rect.DeflateRect(1,1);		
				CString csDay;
				int nDay = m_dayCells[i][u].date.GetDay();
				if(nDay == 1 || (i==0 && u==0))
				{
					csDay.Format(_T("%s %d"), m_dayCells[i][u].date.Format(_T("%B")), nDay);
					CSize dtSize(pDC->GetTextExtent(csDay));
					if(dtSize.cx>rect.Width())
						csDay.Format(_T("%s %d"), m_dayCells[i][u].date.Format(_T("%b")), nDay);
				}
				else
					csDay.Format(_T("%d"), nDay);

				unsigned long nColor;
				if(bSelected && !btoday)
					nColor = pDC->SetTextColor(RGB(255,104,4));
				else
					nColor = pDC->SetTextColor(RGB(0,0,0));
				pDC->DrawText(csDay, rect, DT_RIGHT|DT_TOP);
				pDC->SetTextColor(nColor);

				// Draw the cell content if possible
				if(rect.Width() >= 15)
				{
					for (int j=0; j<m_dayCells[i][u].csaLines.GetSize(); j++)
					{
						CRect txtRect(rect);
						CRect dotRect(rect);

						txtRect.left += 9; //CALENDAR_LINE_HEIGHT;
						txtRect.right-= 2;
						txtRect.top += (j+1)*CALENDAR_LINE_HEIGHT; 

						dotRect.top += (j+1)*CALENDAR_LINE_HEIGHT+(CALENDAR_LINE_HEIGHT/2-1); 
						dotRect.bottom = dotRect.top + 3;
						dotRect.left += 3;
						dotRect.right = dotRect.left +3;

						m_dayCells[i][u].bPartial = false;
						if(!m_dayCells[i][u].csaLines[j].IsEmpty() && txtRect.Height() > CALENDAR_LINE_HEIGHT)
						{
							pDC->SetTextColor(RGB(0,0,0));
							pDC->DrawText(m_dayCells[i][u].csaLines[j], txtRect, DT_LEFT|DT_TOP);								
							CBrush br;
							br.CreateSolidBrush(RGB(125,175,255));
							pDC->FillRect(&dotRect, &br);
						}
						else if(!m_dayCells[i][u].csaLines[j].IsEmpty())
						{
							CPen dotPen(PS_SOLID, 1, RGB(170,170,170));
							pDC->SelectObject(&dotPen);
							// Draw a little arrow
							static int t[2][7] = {5,5,8,8,8,5,5,4,3,2,1,2,3,4};
							int n = 0;
							for(int r=7; r>0; r--){
								pDC->MoveTo(rect.right-9+r, rect.bottom-t[0][n]);
								pDC->LineTo(rect.right-9+r, rect.bottom-t[1][n]);
								n++;
							}
							m_dayCells[i][u].bPartial = true;
							break;
						}
					}
				}
			}
		}
	}

	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
}

bool CCalendarCtrl::GetRectFromCell(int nRow, int nCol, CRect& rect)
{
	if(nRow >=0 && nRow<CALENDAR_ROWS && nCol>=0 && nCol<CALENDAR_COLUMNS)
	{
		CRect rc;
		GetClientRect(&rc);
		int nHeight = (rc.Height()-CALENDAR_HEADER_HEIGHT)/CALENDAR_ROWS;
		int nWidth = rc.Width()/CALENDAR_COLUMNS;
		rect.left = nWidth*nCol;
		rect.right = rect.left + nWidth;
		rect.top = CALENDAR_HEADER_HEIGHT + nRow*nHeight;
		rect.bottom = rect.top + nHeight;
		return true;
	}
	return false;
}

CCalendarCell* CCalendarCtrl::GetCell(CPoint point, int &nRow, int &nCol)
{
	if(GetGridCellFromPoint(point, nRow, nCol))
		return &m_dayCells[nRow][nCol];
	return NULL;
}

bool CCalendarCtrl::GetGridCellFromPoint(CPoint point, int &nRow, int &nCol)
{
	if(point.y > CALENDAR_HEADER_HEIGHT) 
	{
		CRect rc;
		GetClientRect(&rc);
		int nHeight = (rc.Height()-CALENDAR_HEADER_HEIGHT)/CALENDAR_ROWS;
		int nWidth = rc.Width()/CALENDAR_COLUMNS;
		if(nHeight && nWidth)
		{
			nRow = (point.y-CALENDAR_HEADER_HEIGHT)/nHeight;
			nCol = point.x/nWidth;	
			if((nRow>=0) && (nRow<CALENDAR_ROWS) && (nCol>=0) && (nCol<CALENDAR_COLUMNS))
				return true;
		}
	}
	return false;
}

void CCalendarCtrl::GetLastSelectedGridCell(int &nRow, int &nCol)
{
	nRow = 0; nCol = 0;
	for(int i=0; i<CALENDAR_ROWS ; i++)
	{
		for(int u=0; u<CALENDAR_COLUMNS ; u++)
		{
			if(m_SelectionRange[1] == DateToSeconds(m_dayCells[i][u].date)){
				nRow = i; nCol = u;
				return;
			}
		}
	}
}

void CCalendarCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	bool bHold = (GetKeyState(VK_SHIFT)>>8 == -1)?true:false;
	bool bCtrl = (GetKeyState(VK_CONTROL)>>8 == -1)?true:false;
	if(bHold) bCtrl = false; // allow one combination

	int nRow, nCol;
	if(GetGridCellFromPoint(point, nRow, nCol) && !bCtrl)
	{
		if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
			(m_dayCells[nRow][nCol].date > m_BoundDown) )
		{
			m_RandomSelection.RemoveAll();
			m_SelectionRange[2] = 0;
			m_bSelectionStarted = true;
			m_SelectionRange[0] = DateToSeconds(m_dayCells[nRow][nCol].date);
			m_SelectionRange[1] = m_SelectionRange[0];
			SetCapture();
			Invalidate(true);
		}
	}	
	
	SetFocus();
	CWnd::OnLButtonDown(nFlags, point);
}

void CCalendarCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	bool bHold = (GetKeyState(VK_SHIFT)>>8 == -1)?true:false;
	bool bCtrl = (GetKeyState(VK_CONTROL)>>8 == -1)?true:false;
	if(bHold) bCtrl = false; // allow one combination
	if(m_bSelectionStarted && !bCtrl)
	{
		m_RandomSelection.RemoveAll();
		m_bSelectionStarted = false;

		int nRow, nCol;
		if(GetGridCellFromPoint(point, nRow, nCol))
		{
			if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
				(m_dayCells[nRow][nCol].date > m_BoundDown) )			
				m_SelectionRange[1] = DateToSeconds(m_dayCells[nRow][nCol].date);
			else
				m_SelectionRange[1]=m_SelectionRange[0];
		}
		else
			m_SelectionRange[1]=m_SelectionRange[0];		
		ReleaseCapture();
		AdjustSelection();
		Invalidate(true);
	}

	if(bCtrl){
		int nRow, nCol;
		if(GetGridCellFromPoint(point, nRow, nCol))
		{
			if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
				(m_dayCells[nRow][nCol].date > m_BoundDown) )	
			{
				if(m_SelectionRange[2])
				{				
						m_SelectionRange[1] = DateToSeconds(m_dayCells[nRow][nCol].date);
						m_SelectionRange[0] = m_SelectionRange[1];

						void*p;
						if(m_RandomSelection.Lookup((void*)m_SelectionRange[1], p))
							m_RandomSelection.RemoveKey((void*)m_SelectionRange[1]);
						else{
							if(m_RandomSelection.GetCount() < m_nMaxSel)
								m_RandomSelection.SetAt((void*)m_SelectionRange[1], 0);
						}
						m_SelectionRange[2] = m_SelectionRange[1];
				}
				else{
					if(m_RandomSelection.GetCount() < m_nMaxSel)
						m_RandomSelection.SetAt((void*)m_SelectionRange[1], 0);
					m_SelectionRange[1] = DateToSeconds(m_dayCells[nRow][nCol].date);
					m_SelectionRange[0] = m_SelectionRange[1];
					if(m_RandomSelection.GetCount() < m_nMaxSel)
						m_RandomSelection.SetAt((void*)m_SelectionRange[1], 0);
					m_SelectionRange[2] = m_SelectionRange[1];
				}			
				Invalidate(true);
			}
		}
	}
	else{
		m_RandomSelection.RemoveAll();
		m_SelectionRange[2] = 0;
		Invalidate(true);
	}
	CWnd::OnLButtonUp(nFlags, point);
}

void CCalendarCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_bSelectionStarted)
	{
		int nRow, nCol;
		if(GetGridCellFromPoint(point, nRow, nCol))
		{
			if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
				(m_dayCells[nRow][nCol].date > m_BoundDown) )	
			{
				m_RandomSelection.RemoveAll();
				m_SelectionRange[1] = DateToSeconds(m_dayCells[nRow][nCol].date);
				AdjustSelection();
				Invalidate(true);
			}
		}
	}	
	CWnd::OnMouseMove(nFlags, point);
}

void CCalendarCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int nInc = 0;
    switch (nSBCode)
    {
        case SB_TOP:
        case SB_LINEUP:
        case SB_PAGEUP:     
			nInc = -1;
			break;
		case SB_BOTTOM:
		case SB_LINEDOWN:
        case SB_PAGEDOWN:
			nInc = 1;
			break;
        case SB_THUMBTRACK: 
			nInc = nPos - m_nVscrollPos;
			break;
		case SB_ENDSCROLL:	
        default:
			nInc = 0;
    }

    m_nVscrollPos += nInc;	
	if(nInc)
	{		
		COleDateTime newDate = m_DateCurrent;
		if(nInc > 0) 
			newDate += COleDateTimeSpan(abs(7*nInc),0,0,0); 
		else 
			newDate -= COleDateTimeSpan(abs(7*nInc),0,0,0);
		if((m_BoundUp > newDate) && (newDate > m_BoundDown))
			Goto(newDate);
		else
			m_nVscrollPos -= nInc;
		SetScrollPos(SB_VERT, m_nVscrollPos, TRUE);
	}
	
	SetFocus();
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CCalendarCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{	
	COleDateTime newDate = m_DateCurrent;
	if(zDelta < 0){
		// SendMessage(WM_VSCROLL,SB_LINEDOWN);
		newDate += COleDateTimeSpan(7,0,0,0); 	
		if((m_BoundUp > newDate) && (newDate > m_BoundDown))	
		{			
			m_nVscrollPos++;
			SetScrollPos(SB_VERT, m_nVscrollPos, TRUE);
			Goto(newDate);
			return TRUE;
		}
	}
	else if(zDelta > 0){
		// SendMessage(WM_VSCROLL,SB_LINEUP);
		newDate -= COleDateTimeSpan(7,0,0,0);
		if((m_BoundUp > newDate) && (newDate > m_BoundDown))
		{			
			m_nVscrollPos--;
			SetScrollPos(SB_VERT, m_nVscrollPos, TRUE);
			Goto(newDate);
			return TRUE;			
		}
	}
	
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

time_t CCalendarCtrl::DateToSeconds(COleDateTime& date)
{
	// FIX : We need to find the gmt bias for the zone	
	time_t t = (time_t)(date - COleDateTime(1970, 1, 1, 0, 0, 0)).GetTotalSeconds();
	COleDateTime diffdate(t);
	int gmtbias = 0;
	if(diffdate > date) 
		 gmtbias = -((int)(diffdate-date).GetTotalSeconds());
	else gmtbias =  ((int)(date-diffdate).GetTotalSeconds());

	// The next check is to handle the case when system is adjusting the clock 
	// and we meet a time change
	// Note: for the missing hour case, bias is left untouched so the date may have a time > 0
	COleDateTime v((time_t)(t/86400*86400 + gmtbias));
	if(v < date) gmtbias += 3600;

	return (time_t)(t/86400*86400 + gmtbias);
}

BOOL CCalendarCtrl::PreTranslateMessage(MSG* pMsg) 
{		
	if( pMsg->message == WM_KEYDOWN )
	{
		COleDateTime newDate = m_DateCurrent;
		bool bHold = (GetKeyState(VK_SHIFT)>>8 == -1)?true:false;
		bool bCtrl = (GetKeyState(VK_CONTROL)>>8 == -1)?true:false;
		if(bHold) bCtrl = false; // allow one combination

		switch(pMsg->wParam)
		{
		case VK_SPACE:
			{
				if(bCtrl)
				{
					int nRow, nCol;
					GetLastSelectedGridCell(nRow, nCol);
					if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
						(m_dayCells[nRow][nCol].date > m_BoundDown) )	
					{
						void*p; time_t t = DateToSeconds(m_dayCells[nRow][nCol].date);
						if(m_RandomSelection.Lookup((void*)t ,p))
							m_RandomSelection.RemoveKey((void*)t);
						else{
							if(m_RandomSelection.GetCount() < m_nMaxSel)
								m_RandomSelection.SetAt((void*)t, 0);
						}
						Invalidate(true);
						return TRUE;
					}
				}
				break;
			}
		case VK_UP:
			{
				int nRow, nCol;
				GetLastSelectedGridCell(nRow, nCol);
				if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
					(m_dayCells[nRow][nCol].date > m_BoundDown) )	
				{
					if(!bCtrl){
						m_RandomSelection.RemoveAll();
						m_SelectionRange[2] = 0;
					}
					else{
						if(m_RandomSelection.GetCount() == 0)
							m_RandomSelection.SetAt((void*)m_SelectionRange[0], 0);
					}

					if(nRow == 0){
						newDate -= COleDateTimeSpan(7,0,0,0);
						if((m_BoundUp > newDate) && (newDate > m_BoundDown))
						{
							m_nVscrollPos--;
							SetScrollPos(SB_VERT, m_nVscrollPos, TRUE);
							Goto(newDate);
						}
					}
					else
						nRow--;	
					
					if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
						(m_dayCells[nRow][nCol].date > m_BoundDown) )	
					{
						m_SelectionRange[1] = DateToSeconds(m_dayCells[nRow][nCol].date);
						if(bCtrl)
							m_SelectionRange[2] = m_SelectionRange[1];

						if(!bHold)
							m_SelectionRange[0] = m_SelectionRange[1];

						AdjustSelection();
						Invalidate(true);
					}
				}
				return TRUE;
			}
		case VK_DOWN:
			{
				int nRow, nCol;
				GetLastSelectedGridCell(nRow, nCol);
				if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
					(m_dayCells[nRow][nCol].date > m_BoundDown) )	
				{
					if(!bCtrl){
						m_RandomSelection.RemoveAll();
						m_SelectionRange[2] = 0;
					}
					else{
						if(m_RandomSelection.GetCount() == 0)
							m_RandomSelection.SetAt((void*)m_SelectionRange[0], 0);
					}

					if(nRow == CALENDAR_ROWS-1){
						newDate += COleDateTimeSpan(7,0,0,0);
						if((m_BoundUp > newDate) && (newDate > m_BoundDown))
						{
							m_nVscrollPos++;
							SetScrollPos(SB_VERT, m_nVscrollPos, TRUE);
							Goto(newDate);
						}
					}
					else
						nRow++;

					if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
						(m_dayCells[nRow][nCol].date > m_BoundDown) )	
					{	
						m_SelectionRange[1] = DateToSeconds(m_dayCells[nRow][nCol].date);
						if(bCtrl)
							m_SelectionRange[2] = m_SelectionRange[1];

						if(!bHold)
							m_SelectionRange[0] = m_SelectionRange[1];

						AdjustSelection();
						Invalidate(true);
					}
				}
				return TRUE;
			}
		case VK_LEFT:
			{
				int nRow, nCol;
				GetLastSelectedGridCell(nRow, nCol);
				if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
					(m_dayCells[nRow][nCol].date > m_BoundDown) )	
				{
					if(!bCtrl){
						m_RandomSelection.RemoveAll();
						m_SelectionRange[2] = 0;
					}
					else{
						if(m_RandomSelection.GetCount() == 0)
							m_RandomSelection.SetAt((void*)m_SelectionRange[0], 0);
					}
					if(nCol > 0) nCol--;
					else
					{
						nCol = CALENDAR_COLUMNS-1;
						if(nRow == 0){
							newDate -= COleDateTimeSpan(7,0,0,0);
							if((m_BoundUp > newDate) && (newDate > m_BoundDown))
							{
								m_nVscrollPos--;
								SetScrollPos(SB_VERT, m_nVscrollPos, TRUE);
								Goto(newDate);
							}
							else
								nCol = 0;
						}
						else
							nRow--;
					}

					if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
						(m_dayCells[nRow][nCol].date > m_BoundDown) )	
					{					
						m_SelectionRange[1] = DateToSeconds(m_dayCells[nRow][nCol].date);
						if(bCtrl)
							m_SelectionRange[2] = m_SelectionRange[1];

						if(!bHold)
							m_SelectionRange[0] = m_SelectionRange[1];

						AdjustSelection();
						Invalidate(true);
					}
				}
				return TRUE;
			}
		case VK_RIGHT:
			{
				int nRow, nCol;
				GetLastSelectedGridCell(nRow, nCol);
				if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
					(m_dayCells[nRow][nCol].date > m_BoundDown) )	
				{
					if(!bCtrl){
						m_RandomSelection.RemoveAll();
						m_SelectionRange[2] = 0;
					}
					else{
						if(m_RandomSelection.GetCount() == 0)
							m_RandomSelection.SetAt((void*)m_SelectionRange[0], 0);
					}
					if(nCol < CALENDAR_COLUMNS-1)	nCol++;
					else
					{
						nCol = 0;
						if(nRow == CALENDAR_ROWS-1){
							newDate += COleDateTimeSpan(7,0,0,0);
							if((m_BoundUp > newDate) && (newDate > m_BoundDown))
							{
								m_nVscrollPos++;
								SetScrollPos(SB_VERT, m_nVscrollPos, TRUE);
								Goto(newDate);
							}
							else
								nCol = CALENDAR_COLUMNS-1;
						}
						else
							nRow++;
					}
					
					if( (m_dayCells[nRow][nCol].date < m_BoundUp) && 
						(m_dayCells[nRow][nCol].date > m_BoundDown) )	
					{
						m_SelectionRange[1] = DateToSeconds(m_dayCells[nRow][nCol].date);
						if(bCtrl)
							m_SelectionRange[2] = m_SelectionRange[1];

						if(!bHold)
							m_SelectionRange[0] = m_SelectionRange[1];

						AdjustSelection();
						Invalidate(true);
					}
				}
				return TRUE;
			}
		}
	}

	return CWnd::PreTranslateMessage(pMsg);
}

int CCalendarCtrl::GetSelectedItems(CDWordArray& dwaSelection)
{
	if(m_RandomSelection.GetCount())
	{
		POSITION pos = m_RandomSelection.GetStartPosition();
		while (pos){
			void* p; DWORD date;
			m_RandomSelection.GetNextAssoc(pos, (void*&)date, p);
			dwaSelection.Add(date);
		}
	}
	else
	{
		if(m_SelectionRange[0] && m_SelectionRange[1])
		{
			COleDateTime dmax(max(m_SelectionRange[0], m_SelectionRange[1]));
			COleDateTime dmin(min(m_SelectionRange[0], m_SelectionRange[1]));			
			COleDateTime dcur = dmin;
			// FIX : Remove added hour if any
			if(dmin.GetHour())	dmin -= COleDateTimeSpan(0,1,0,0);
			int nDays = 1;
			while(dcur <= dmax)
			{	
				dwaSelection.Add(DateToSeconds(dcur));
				dcur = dmin + COleDateTimeSpan(nDays,0,0,0);				
				dcur = COleDateTime(DateToSeconds(dcur));
				nDays++;
			}
		}
	}
	return dwaSelection.GetSize();
}


CCalendarCell* CCalendarCtrl::GetCell(time_t date)
{
	for(int i=0; i<CALENDAR_ROWS ; i++)
		for(int u=0; u<CALENDAR_COLUMNS; u++)
			if(DateToSeconds(m_dayCells[i][u].date) == date)
				return &m_dayCells[i][u];
	return NULL;
}

void CCalendarCtrl::AdjustSelection()
{
	int nSelCount = 0;
	COleDateTime dmax(max(m_SelectionRange[0], m_SelectionRange[1]));
	COleDateTime dmin(min(m_SelectionRange[0], m_SelectionRange[1]));
	COleDateTime dcur = dmin;
	while(dcur <= dmax)
	{
		nSelCount++;
		dcur += COleDateTimeSpan(1,0,0,0);			
	}

	if(nSelCount > m_nMaxSel)
	{
		if(m_SelectionRange[1] > m_SelectionRange[0])
		{
			COleDateTime dMin((time_t)m_SelectionRange[1]);
			dMin -= COleDateTimeSpan(m_nMaxSel-1,0,0,0);
			m_SelectionRange[0] = DateToSeconds(dMin);
		}
		else if(m_SelectionRange[1] < m_SelectionRange[0])
		{
			COleDateTime dMax((time_t)m_SelectionRange[1]);
			dMax += COleDateTimeSpan(m_nMaxSel-1,0,0,0);
			m_SelectionRange[0] = DateToSeconds(dMax);
		}
	}
}

COLORREF CCalendarCtrl::GetFadedBlue(unsigned char percent)
{	
	int r = 180, g = 205, b = 255;
	int al = percent*75/100;
	return RGB(	(unsigned char)(r + ((255-r)/(float)75) * al), 
				(unsigned char)(g + ((255-g)/(float)75) * al), 
				(unsigned char)(b + ((255-b)/(float)75) * al));
}

void CCalendarCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int nRow, nCol;
	CCalendarCell* pCell = GetCell(point, nRow, nCol);
	if(pCell)
	{
		CString csMessage;
		csMessage.Format(_T("DBL_CLICK\nCoords: row(%d) col(%d)\nDate: %s"), nRow, nCol, pCell->date.Format(_T("%A, %B %d, %Y")));
		AfxMessageBox(csMessage);
	}
	
	CWnd::OnLButtonDblClk(nFlags, point);
}
