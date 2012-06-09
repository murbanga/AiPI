// CalendarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "CalendarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// We will use this to manage calendar data for this test app... 
typedef struct CalendarDataItem
{
	bool bMarked;
	CStringArray csLines;
}CalendarDataItem;

CMapPtrToPtr	g_CalendarData;

IMPLEMENT_DYNAMIC(CCalendarDlg, COXSizeDialogBar)
/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg dialog


CCalendarDlg::CCalendarDlg(CWnd* pParent /*=NULL*/)
 :COXSizeDialogBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	//{{AFX_DATA_INIT(CCalendarDlg)
		
	//}}AFX_DATA_INIT
	m_pCalendarCtrl = new CCalendarCtrl;
}

CCalendarDlg::~CCalendarDlg()
{
	delete m_pCalendarCtrl;

	POSITION pos = g_CalendarData.GetStartPosition();	 
	while (pos){
		CalendarDataItem* p; time_t date;
		g_CalendarData.GetNextAssoc(pos, (void*&)date, (void*&)p);
		delete p;
	}
}

void CCalendarDlg::DoDataExchange(CDataExchange* pDX)
{
	COXSizeDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarDlg)
		
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalendarDlg, COXSizeDialogBar)
	//{{AFX_MSG_MAP(CCalendarDlg)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg message handlers

BOOL CCalendarDlg::OnInitDialog() 
{
	COXSizeDialogBar::OnInitDialog();
	
	// TODO: Add extra initialization here
	VERIFY(m_pCalendarCtrl->Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL, CRect(0,0,0,0), this, IDC_CALENDARCTRL, 
										(LPFN_CALENDAR_DATA_CALLBACK)CCalendarDlg::CalendarDataCallback));
	m_pCalendarCtrl->Reset();
	ResizeUI();

	SetTimer(1, 100, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//-------------------------------------------------------------------
void CCalendarDlg::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// respond to this event as we need to override it
//-------------------------------------------------------------------
{
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	/*
	CRect rect;
	GetClientRect(rect);

	rect.DeflateRect(0, 0);

	m_pCalendarCtrl->MoveWindow(&rect);
	*/

}


void CCalendarDlg::ResizeUI()
{
	if(m_pCalendarCtrl && ::IsWindow(m_pCalendarCtrl->m_hWnd))
	{
		CRect rect;
		GetClientRect(rect);
		m_pCalendarCtrl->MoveWindow(rect);
	}
}

HRESULT CCalendarDlg::CalendarDataCallback(CCalendarCtrl* pWnd, time_t date)
{
	if(pWnd)
	{
		CalendarDataItem* p = NULL;
		if(g_CalendarData.Lookup((void*)date, (void*&)p))
		{
			CCalendarCell* pCell = pWnd->GetCell(date);
			pCell->bMark = p->bMarked;
			pCell->csaLines.Copy(p->csLines);
		}
	}
	return 0;
}

void CCalendarDlg::OnSize(UINT nType, int cx, int cy) 
{
	COXSizeDialogBar::OnSize(nType, cx, cy);
	
		ResizeUI();
	
}

void CCalendarDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1)
	{
		KillTimer(1);

		// Using a timer for this is not nice! In your real life app you will need to implement
		// a notification message sent from the calendar to the parent each time the date changes
		// (in the CCalendarCtrl::SetDate function for example ).
		if(m_pCalendarCtrl && ::IsWindow(m_pCalendarCtrl->m_hWnd))
		{
			CString csTitle;
			csTitle.Format(_T("Calendar : %s, %d - %s, %d"), 
									m_pCalendarCtrl->GetMinDate().Format(_T("%B")),
									m_pCalendarCtrl->GetMinDate().GetYear(),
									m_pCalendarCtrl->GetMaxDate().Format(_T("%B")),
									m_pCalendarCtrl->GetMaxDate().GetYear());
			SetWindowText(csTitle);
		}

		SetTimer(1, 100, NULL);
	}
	
	COXSizeDialogBar::OnTimer(nIDEvent);
}


BOOL CCalendarDlg::OnEraseBkgnd(CDC* pDC) 
{
	
	if(m_pCalendarCtrl && ::IsWindow(m_pCalendarCtrl->m_hWnd))
	{
		CRect clip;
		m_pCalendarCtrl->GetWindowRect(&clip);
		ScreenToClient(&clip);
		pDC->ExcludeClipRect(&clip);
		pDC->GetClipBox(&clip);
		pDC->FillSolidRect(clip, RGB(255,255,255));
		return FALSE;
	}
	return TRUE;
}


void CCalendarDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	
	// Do not call COXSizeDialogBar::OnPaint() for painting messages
}

static CString GetShort(UINT id)
{
	CString str;
	str.LoadString(id);
	int nIndex = str.ReverseFind(_T('\n'));
	if(nIndex!=-1)
	{
		str=str.Mid(nIndex+1);
	}
	return str;
}


void CCalendarDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	/*
	UNREFERENCED_PARAMETER(pWnd);

	if(point.x==-1 && point.y==-1)
	{
		CRect rect;
		GetWindowRect(rect);

		point = rect.TopLeft()+CPoint(10,10);
	}
	SetFocus();

	CNewMenu menu;
	menu.CreatePopupMenu();
	menu.InsertMenu(0, MF_BYPOSITION , ID_CTRL_CALENDAR_GOTODATE, GetShort(ID_CTRL_CALENDAR_GOTODATE));
	menu.InsertMenu(1, MF_BYPOSITION ,ID_CTRL_CALENDAR_TODAY , GetShort(ID_CTRL_CALENDAR_TODAY));
	menu.InsertMenu(2, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(3, MF_BYPOSITION ,ID_CTRL_CALENDAR_SUNDAY , GetShort(ID_CTRL_CALENDAR_SUNDAY));
	menu.InsertMenu(4, MF_BYPOSITION , ID_CTRL_CALENDAR_MONDAY, GetShort(ID_CTRL_CALENDAR_MONDAY));
	menu.InsertMenu(5, MF_BYPOSITION , ID_CTRL_CALENDAR_TUESDAY, GetShort(ID_CTRL_CALENDAR_TUESDAY));
	menu.InsertMenu(6, MF_BYPOSITION , ID_CTRL_CALENDAR_WEDNESDAY, GetShort(ID_CTRL_CALENDAR_WEDNESDAY));
	menu.InsertMenu(7, MF_BYPOSITION ,ID_CTRL_CALENDAR_THURSDAY , GetShort(ID_CTRL_CALENDAR_THURSDAY));
	menu.InsertMenu(8, MF_BYPOSITION ,ID_CTRL_CALENDAR_FRIDAY , GetShort(ID_CTRL_CALENDAR_FRIDAY));
	menu.InsertMenu(9, MF_BYPOSITION ,ID_CTRL_CALENDAR_SATURDAY , GetShort(ID_CTRL_CALENDAR_SATURDAY));
	menu.InsertMenu(10, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(11, MF_BYPOSITION ,ID_CTRL_CALENDAR_MARK , GetShort(ID_CTRL_CALENDAR_MARK));
	menu.InsertMenu(12, MF_BYPOSITION ,ID_CTRL_CALENDAR_ADD , GetShort(ID_CTRL_CALENDAR_ADD));
	menu.InsertMenu(13, MF_BYPOSITION ,ID_CTRL_CALENDAR_CLEAR , GetShort(ID_CTRL_CALENDAR_CLEAR));
	

	menu.SetMenuTitle(_T("CalendarCtrl"),MFT_GRADIENT|MFT_SIDE_TITLE);
	menu.LoadToolBar(IDR_CALENDARCTRL);

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());

	*/
	
}


void CCalendarDlg::OnCalendarGoToToday() 
{
	m_pCalendarCtrl->Reset();	
}

void CCalendarDlg::OnCalendarGoTo() 
{
	// TODO: Add your command handler code here
	CCalendarDateDlg dlg;
	dlg.m_Date = m_pCalendarCtrl->GetMinDate();
	if(dlg.DoModal() == IDOK)
		m_pCalendarCtrl->Goto(dlg.m_Date, true);	
}

void CCalendarDlg::OnCalendarMarkSelected() 
{
	CDWordArray dwaSelection;
	m_pCalendarCtrl->GetSelectedItems(dwaSelection);
	for(int i=0; i<dwaSelection.GetSize(); i++)
	{
		CalendarDataItem* p = NULL;
		if(!g_CalendarData.Lookup((void*)dwaSelection[i], (void*&)p))
		{
			p = new CalendarDataItem;
			g_CalendarData.SetAt((void*)dwaSelection[i], (void*)p);
		}
		p->bMarked = true;
	}
	m_pCalendarCtrl->UpdateCells();
}

void CCalendarDlg::OnCalendarClearSelected() 
{
	CDWordArray dwaSelection;
	m_pCalendarCtrl->GetSelectedItems(dwaSelection);
	for(int i=0; i<dwaSelection.GetSize(); i++)
	{
		CalendarDataItem* p = NULL;
		if(g_CalendarData.Lookup((void*)dwaSelection[i], (void*&)p))
		{
			p->bMarked = false;
			p->csLines.RemoveAll();
		}		
	}
	m_pCalendarCtrl->UpdateCells();
}

void CCalendarDlg::OnCalendarAddEntryToSelected() 
{
	// TODO: Add your command handler code here
	CCalendarInputDlg dlg;
	if(dlg.DoModal() == IDOK && !dlg.m_Text.IsEmpty())
	{
		CDWordArray dwaSelection;
		m_pCalendarCtrl->GetSelectedItems(dwaSelection);
		for(int i=0; i<dwaSelection.GetSize(); i++)
		{
			CalendarDataItem* p = NULL;
			if(!g_CalendarData.Lookup((void*)dwaSelection[i], (void*&)p))
			{
				p = new CalendarDataItem;
				p->bMarked = false;
				g_CalendarData.SetAt((void*)dwaSelection[i], (void*)p);
			}
			p->csLines.Add(dlg.m_Text);
		}
		m_pCalendarCtrl->UpdateCells();
	}	
}

void CCalendarDlg::OnCalendarFirstDayOfWeekSunday() 
{
	m_pCalendarCtrl->SetFirstWeekDay(1);
	m_pCalendarCtrl->UpdateCells();
}
void CCalendarDlg::OnCalendarFirstDayOfWeekMonday() 
{
	m_pCalendarCtrl->SetFirstWeekDay(2);	
	m_pCalendarCtrl->UpdateCells();
}
void CCalendarDlg::OnCalendarFirstDayOfWeekTuesday() 
{
	m_pCalendarCtrl->SetFirstWeekDay(3);
	m_pCalendarCtrl->UpdateCells();
}
void CCalendarDlg::OnCalendarFirstDayOfWeekWednesday() 
{
	m_pCalendarCtrl->SetFirstWeekDay(4);
	m_pCalendarCtrl->UpdateCells();
}
void CCalendarDlg::OnCalendarFirstDayOfWeekThursday() 
{
	m_pCalendarCtrl->SetFirstWeekDay(5);
	m_pCalendarCtrl->UpdateCells();	
}
void CCalendarDlg::OnCalendarFirstDayOfWeekFriday() 
{
	m_pCalendarCtrl->SetFirstWeekDay(6);
	m_pCalendarCtrl->UpdateCells();
}
void CCalendarDlg::OnCalendarFirstDayOfWeekSaturday() 
{
	m_pCalendarCtrl->SetFirstWeekDay(7);
	m_pCalendarCtrl->UpdateCells();
}




/////////////////////////////////////////////////////////////////////////////
// CCalendarDateDlg dialog


CCalendarDateDlg::CCalendarDateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalendarDateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendarDateDlg)
	m_Date = COleDateTime::GetCurrentTime();
	//}}AFX_DATA_INIT
}


void CCalendarDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarDateDlg)
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateCtrl);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Date);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalendarDateDlg, CDialog)
	//{{AFX_MSG_MAP(CCalendarDateDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarDateDlg message handlers

BOOL CCalendarDateDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
/*	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		CWnd::SetWindowText(_T("Cuadro de selección"));
		GetDlgItem(IDC_STATIC_PICKDATE)->SetWindowText(_T("Seleccione una fecha:"));
		GetDlgItem(IDOK)->SetWindowText(_T("Aceptar"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancelar"));
		break;
	default:
		CWnd::SetWindowText(_T("Selection dialog"));
		GetDlgItem(IDC_STATIC_PICKDATE)->SetWindowText(_T("Select a date:"));
		GetDlgItem(IDOK)->SetWindowText(_T("OK"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancel"));
		break;
	}

*/	
	// TODO: Add extra initialization here
	COleDateTime DateMin = COleDateTime(2000,1,1,0,0,0);
	COleDateTime DateMax = COleDateTime(2035,12,31,0,0,0);
	m_DateCtrl.SetRange(&DateMin, &DateMax);
	m_DateCtrl.SetFocus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/////////////////////////////////////////////////////////////////////////////
// CCalendarInputDlg dialog
CCalendarInputDlg::CCalendarInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalendarInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalendarInputDlg)
	m_Text = _T("New Entry");
	//}}AFX_DATA_INIT
}


void CCalendarInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextDlg)
	DDX_Text(pDX,IDC_EDIT_CALENDARTEXT , m_Text);
	DDV_MaxChars(pDX, m_Text, 50);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalendarInputDlg, CDialog)
	//{{AFX_MSG_MAP(CCalendarInputDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextDlg message handlers

void CCalendarInputDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);
	
	CDialog::OnOK();
}

BOOL CCalendarInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

/*
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		CWnd::SetWindowText(_T("Cuadro de entrada CalendarCtrl"));
		GetDlgItem(IDOK)->SetWindowText(_T("Aceptar"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancelar"));
		break;
	default:
		CWnd::SetWindowText(_T("Input dialog CalendarCtrl"));
		GetDlgItem(IDOK)->SetWindowText(_T("OK"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancel"));
		break;
	}
*/
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_EDIT_CALENDARTEXT)->SetFocus();
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




