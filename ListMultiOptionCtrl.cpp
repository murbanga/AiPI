// ListMultiOptionCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ListMultiOptionCtrl.h"
#include "StringInputDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define INDEXTOSTATEIMAGEMASK(i) ((i) << define stateimagemasktoindex(i) i) >> 12) &
//#define ALLSTATEIMAGEMASKS INDEXTOSTATEIMAGEMASK(0xF)


IMPLEMENT_DYNAMIC(CListMultiOptionCtrl, COXSizeControlBar);
/////////////////////////////////////////////////////////////////////////////
// CListMultiOptionCtrl

CListMultiOptionCtrl::CListMultiOptionCtrl()
:COXSizeControlBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	m_bInitialized = FALSE;
	
	m_bGridLines = FALSE;
	m_bEditCheck = FALSE;
	m_bMulti = FALSE;
	m_nRegion = 0;
	m_bSort = FALSE;
	m_iNumberOfRows = 5;
	m_iImageColumn = 0;
	m_bCheckable = FALSE;
	m_bAutoEdit = FALSE;
	m_bShowSel = FALSE;
	m_bHorizontal = TRUE;
	m_bVertical = TRUE;
	m_bResize = TRUE;
}

CListMultiOptionCtrl::~CListMultiOptionCtrl()
{
	
}


BEGIN_MESSAGE_MAP(CListMultiOptionCtrl, COXSizeControlBar)
	//{{AFX_MSG_MAP(CListMultiOptionCtrl)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	
	
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL_EX, OnTraceNotification)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL_EX, OnItemchangedList)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LISTCTRL_EX, OnTraceNotification)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LISTCTRL_EX, OnTraceNotification)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LISTCTRL_EX, OnTraceNotification)
	ON_NOTIFY(LVN_BEGINRDRAG, IDC_LISTCTRL_EX, OnTraceNotification)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTCTRL_EX, OnTraceNotification)
	ON_NOTIFY(LVN_DELETEALLITEMS, IDC_LISTCTRL_EX, OnTraceNotification)
	ON_NOTIFY(LVN_DELETEITEM, IDC_LISTCTRL_EX, OnTraceNotification)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LISTCTRL_EX, OnTraceNotification)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LISTCTRL_EX, OnTraceNotification)
	ON_NOTIFY(LVN_INSERTITEM, IDC_LISTCTRL_EX, OnTraceNotification)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LISTCTRL_EX, OnTraceNotification)
	ON_NOTIFY(LVN_SETDISPINFO, IDC_LISTCTRL_EX, OnTraceNotification)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListMultiOptionCtrl message handlers
int CListMultiOptionCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);

	//Create CListCtrl
	if (!m_gridCtrl.Create(WS_CHILD|WS_BORDER|WS_TABSTOP|LVS_REPORT 
		|LVS_OWNERDRAWFIXED | LVS_SINGLESEL | LVS_ALIGNTOP,
		CRect(0,0,0,0), this, IDC_LISTCTRL_EX))
		return -1;

	//m_gridCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_UNDERLINEHOT|LVS_EX_CHECKBOXES);
    m_gridCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE );

	
	InitListCtrl();

	return 0;
}


BOOL CListMultiOptionCtrl::Create(CWnd * pParentWnd, const CString& sTitle /* = _T("ListMultiOptionCtrl")*/,
					const UINT nID /* = IDC_LISCTRL_EX */)
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


void CListMultiOptionCtrl::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
		
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;
	int nSelected = pNMListView->iItem;
	CString strItem = m_gridCtrl.GetItemText(nSelected, 0);
	
	/*
	int iLastItem = m_gridCtrl.GetItemCount();
	
	  for(int i = 0; i<iLastItem; i++)
		m_gridCtrl.SetCheck(i, 0);
	
	  m_gridCtrl.SetCheck(nSelected, TRUE);
	*/
	
	
	if ( pNMListView->uNewState & LVIS_SELECTED)
		MessageBox(strItem);
	
	*pResult;
	
}


void CListMultiOptionCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
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
	menu.InsertMenu(0, MF_BYPOSITION ,ID_CTRL_LISTBAR_ADD , GetShort(ID_CTRL_LISTBAR_ADD));
	menu.InsertMenu(1, MF_BYPOSITION , ID_CTRL_LISTBAR_DELETE, GetShort(ID_CTRL_LISTBAR_DELETE));
	menu.InsertMenu(2, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(3, MF_BYPOSITION ,ID_CTRL_LISTBAR_BACKCOLOR , GetShort(ID_CTRL_LISTBAR_BACKCOLOR));
	menu.InsertMenu(4, MF_BYPOSITION ,ID_CTRL_LISTBAR_FONT , GetShort(ID_CTRL_LISTBAR_FONT));
	menu.InsertMenu(5, MF_BYPOSITION ,ID_CTRL_LISTBAR_TEXTBKCOLOR , GetShort(ID_CTRL_LISTBAR_TEXTBKCOLOR));
	
	menu.SetMenuTitle(_T("OptionBar"),MFT_GRADIENT|MFT_SIDE_TITLE);
	menu.LoadToolBar(IDR_OPTIONBAR);

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
*/
	
	
}

//-------------------------------------------------------------------
void CListMultiOptionCtrl::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
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

	m_gridCtrl.MoveWindow(&rect);
}

void CListMultiOptionCtrl::InitListCtrl()
{

	// Add Headers to Grid Control
	for (int i = 0; i < 4 ; i++)
	{
		CString sText;
		sText.Format(_T("Header %d"),i);
		m_gridCtrl.InsertColumn(i, sText);
	}

	
	m_gridCtrl.SetColumnWidth(0, 80);
	m_gridCtrl.SetColumnWidth(1, 80);
	m_gridCtrl.SetColumnWidth(2, 80);
	m_gridCtrl.SetColumnWidth(3, 80);


	// Set the spin ranges
	//m_wndNumRowsSpin.SetRange(0, 10000);
	// ... Only four columns (0 - 3)
	//m_wndImageColumnSpin.SetRange(0, 3);

	// create the small icon image list	
	m_ImageSmall.Create(IDB_IMAGEMULTILISTCTRL,16,0,RGB(255,255,255));
	// Associate the image lists with the grid control
	m_gridCtrl.SetImageList(&m_ImageSmall, LVSIL_SMALL);

	//m_gridCtrl.SetEqualWidth();

	m_gridCtrl.ShowWindow(SW_SHOW);
	
	m_bInitialized = TRUE;
	m_bCheckable = 2;
		
	InsertItems();
}

void CListMultiOptionCtrl::InsertItems() 
{
	if (!UpdateData(TRUE))
		return;
	
	BeginWaitCursor();
	m_gridCtrl.LockWindowUpdate();
	////////
	// Specify the entire row's column entries. 'lParam' points
	// to the data to be displayed in each column.
	////////
	LV_ITEM lvi;
	lvi.mask       = LVIF_TEXT | LVIF_IMAGE;
	lvi.cchTextMax = 0;
	lvi.lParam     = 0;
	
	int iSubItem;
	TCHAR sBuffer[20];
	// Insert the item
	for (int j = 0; j < m_iNumberOfRows ; j++)
		{
		iSubItem = 0;
		
		lvi.iItem      = j;
		lvi.iSubItem   = 0;
		lvi.iImage	  = 1;
		
		wsprintf(sBuffer, _T("Row%i,Col%i"),j + 1, iSubItem + 1);
		lvi.pszText = sBuffer;
		
		int nRtnValue = m_gridCtrl.InsertItem(&lvi);
		ASSERT(-1 != nRtnValue);
		
		// Note that we're starting from iSubItem '1'
		for (iSubItem = 1; iSubItem < 4; iSubItem++)
			{
			wsprintf(sBuffer, _T("Row%i,Col%i"),j + 1, iSubItem + 1);
			m_gridCtrl.SetItemText(j, iSubItem, sBuffer);
			}
	}
	
	m_gridCtrl.UnlockWindowUpdate();
	EndWaitCursor();	
}

void CListMultiOptionCtrl::SetFont() 
{
	LOGFONT logFont;
	
   memset(&logFont, 0, sizeof(LOGFONT));

                                // Logical font struct
	CFontDialog dlg(&logFont);
	
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.GetSize() > 90)
			AfxMessageBox(_T("This font might not fit the row height"));

		CFont rFont;
   		VERIFY(rFont.CreateFontIndirect(&logFont));

		m_gridCtrl.SetTextFont(&rFont);
	}
}

void CListMultiOptionCtrl::ResetFont() 
{

	m_gridCtrl.SetTextFont();

}


void CListMultiOptionCtrl::SetColor() 
{
	if (!UpdateData(TRUE))
		return;

	COLORREF color = 0;

	switch (m_nRegion)
		{
		case 0:
			color = m_gridCtrl.GetTextColor();
			break;
		case 1:
			color = m_gridCtrl.GetTextBkColor();
			break;
		case 2:
			color = m_gridCtrl.GetBkColor();
			break;
		case 3:
			{
			BOOL bGridLines;
			m_gridCtrl.GetGridLines(bGridLines, color);
			}
			break;
		default:
			TRACE1("CListMultiOptionCtrl::OnColorButton : Unexpected case in switch 1 : %i\n", m_nRegion);
			ASSERT(FALSE);
			break;
		}

	CColorDialog cdlg(color);
	if (cdlg.DoModal() != IDOK)
		return;
	color = cdlg.GetColor();

	switch (m_nRegion)
		{
		case 0:
			m_gridCtrl.SetTextColor(color);
			break;
		case 1:
			m_gridCtrl.SetTextBkColor(color);
			break;
		case 2:
			m_gridCtrl.SetBkColor(color);
			break;
		case 3:
			{
			BOOL bGridLines;
			COLORREF lineColor;
			m_gridCtrl.GetGridLines(bGridLines, lineColor);
			m_gridCtrl.SetGridLines(bGridLines, color);
			}
			break;
		default:
			TRACE1("CListMultiOptionCtrl::OnColorButton : Unexpected case in switch 2 : %i\n", m_nRegion);
			ASSERT(FALSE);
			break;
		}
	
	m_gridCtrl.RedrawWindow();
}



void CListMultiOptionCtrl::SetTextColor()
{
	m_nRegion = 0;
	SetColor();

}

void CListMultiOptionCtrl::SetTextBkColor()
{
	m_nRegion = 1;
	SetColor();

}

void CListMultiOptionCtrl::SetBkColor()
{
	m_nRegion = 2;
	SetColor();

}

void CListMultiOptionCtrl::SetGridLinesColor()
{
	m_nRegion = 3;
	SetColor();

}


void CListMultiOptionCtrl::Clear() 
{
	BeginWaitCursor();

	m_gridCtrl.DeleteAllItems();
	m_gridCtrl.Invalidate();
	
	EndWaitCursor();
}

void CListMultiOptionCtrl::DeleteItem() 
{
	CStringInputDlg dlg ;
	
	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	  
	switch( dwLanguageID )
	{
	case LANG_SPANISH:
		dlg.m_strPrompt.Format(TEXT("Seleccione los elementos a eliminar")) ;
		dlg.szBtnOK = _T("Aceptar");
		dlg.szBtnCancel = _T("Cancelar");
		dlg.szDlgCaption = _T("OptionBar Cuadro de entrada");
		break;
	default:
		dlg.m_strPrompt.Format(TEXT("Select the items to be deleted")) ;
		dlg.szBtnOK = _T("OK");
		dlg.szBtnCancel = _T("Cancel");
		dlg.szDlgCaption = _T("OptionBar InputBox");
		break;
	}

	
		COXGridList* pListCtrl = (COXGridList*) GetDlgItem(IDC_LISTCTRL_EX);
		ASSERT(pListCtrl != NULL);

		POSITION pos = m_gridCtrl.GetFirstSelectedItemPosition();
		if (pos == NULL)
		{
			switch( dwLanguageID )
			{
			case LANG_SPANISH:
				MessageBox(_T("¡Ningún elemento fue selecionado!\n"));
				TRACE0("¡Ningún elemento fue seleccionado!\n");
				break;
			default:
				MessageBox(_T("No items were selected!\n"));
				TRACE0("No items were selected!\n");
				break;
			}
		}
		else
		{
			while (pos)
			{
				int nItem = m_gridCtrl.GetNextSelectedItem(pos);
				TCHAR buff[16];
				CString szItem = _itot(nItem, buff, 10);

				switch( dwLanguageID )
				{
				case LANG_SPANISH:
					MessageBox(_T("¡El elemento ") + szItem + _T(" fue seleccionado para eleminarse!\n"));
					TRACE1("¡El elemento %d fue selecconado para eliminarse!\n", nItem);
					break;
				default:
					MessageBox(_T("Item ") + szItem + _T(" was selected for deleted!\n"));
					TRACE1("Item %d was selected for deleted!\n", nItem);
					break;
				}	
				
				m_gridCtrl.DeleteItem(nItem);
				
			}

		}

	m_gridCtrl.Invalidate();
	
	
}
	



void CListMultiOptionCtrl::Sortable() 
{
	if (!UpdateData(TRUE))
		return;

	// ... Show wait cursor (may take a while)
	CWaitCursor wc;

	if(m_bSort == FALSE )
		m_bSort = TRUE;
	else
		m_bSort = FALSE;
		
	
	m_gridCtrl.SetSortable(m_bSort);
}

void CListMultiOptionCtrl::SetMulCheck() 
{
	if (!UpdateData(TRUE))
		return;

 	
	if( m_bMulti == FALSE)
		m_bMulti = TRUE;
	else
		m_bMulti = FALSE;
	
	m_gridCtrl.SetMultipleSelection(m_bMulti);
}

void CListMultiOptionCtrl::SetEditable() 
{
	if (!UpdateData(TRUE))
		return;

 	if( m_bEditCheck == FALSE)
		m_bEditCheck = TRUE;
	else
		m_bEditCheck = FALSE;
	
	m_gridCtrl.SetEditable(m_bEditCheck);
}



void CListMultiOptionCtrl::SetGridLines() 
{
	if (!UpdateData(TRUE))
		return;

	BOOL bGridLines;
	COLORREF lineColor;

	if( m_bGridLines == FALSE)
		m_bGridLines = TRUE;
	else
		m_bGridLines = FALSE;

	m_gridCtrl.GetGridLines(bGridLines, lineColor);
	m_gridCtrl.SetGridLines(m_bGridLines, lineColor);
}


void CListMultiOptionCtrl::SetNormalGridLines() 
{
	if (!UpdateData(TRUE))
		return;

	
	if( m_bNormalGridLines == FALSE)
	{
		m_bNormalGridLines = TRUE;
		m_gridCtrl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_UNDERLINEHOT);
	}
	else
	{
		m_bNormalGridLines = FALSE;
		m_gridCtrl.SetExtendedStyle(LVS_EX_UNDERLINEHOT);
	}
	

}

void CListMultiOptionCtrl::SetNormalCheckBox() 
{
	if (!UpdateData(TRUE))
		return;

	if( m_bNormalCheckBox == FALSE)
	{
		m_bNormalCheckBox = TRUE;
		m_gridCtrl.SetExtendedStyle(LVS_EX_UNDERLINEHOT| LVS_EX_CHECKBOXES);
	}
	else
	{
		m_bNormalCheckBox = FALSE;
		m_gridCtrl.SetExtendedStyle(LVS_EX_UNDERLINEHOT);
	}
	

}


void CListMultiOptionCtrl::SetCheckable() 
{
	if (!UpdateData(TRUE))
		return;

	if( m_bCheckable == FALSE)
		m_bCheckable = TRUE;
	else
		m_bCheckable = FALSE;
	
 	m_gridCtrl.SetCheckable(m_bCheckable != 0);
	m_gridCtrl.SetCheckStyle(m_bCheckable == 2 ? BS_AUTO3STATE : BS_AUTOCHECKBOX);
	
}





void CListMultiOptionCtrl::SetAutoEdit() 
{
	if (!UpdateData(TRUE))
		return;

	if( m_bAutoEdit == FALSE)
		m_bAutoEdit = TRUE;
	else
		m_bAutoEdit = FALSE;

 	m_gridCtrl.SetAutoEdit(m_bAutoEdit);
}



void CListMultiOptionCtrl::ShowSelection() 
{
	if (!UpdateData(TRUE))
		return;

	if( m_bShowSel == FALSE)
		m_bShowSel = TRUE;
	else
		m_bShowSel = FALSE;

 	m_gridCtrl.SetShowSelAlways(m_bShowSel);
}


void CListMultiOptionCtrl::ChangeImageColumn() 
{
	if (!m_bInitialized || !UpdateData(TRUE))
		return;
	
	if (!m_gridCtrl.SetImageColumn(m_iImageColumn))
		AfxMessageBox(_T("Unable to set desired ImageColumn"));
}


void CListMultiOptionCtrl::SetHorizontalGrid() 
{
	if (!UpdateData(TRUE))
		return;

	if( m_bHorizontal == FALSE)
		m_bHorizontal = TRUE;
	else
		m_bHorizontal = FALSE;

		
 	m_gridCtrl.SetGridLineOrientation(m_bHorizontal, m_bVertical);
}

void CListMultiOptionCtrl::SetVerticalGrid() 
{
	if (!UpdateData(TRUE))
		return;

	if( m_bVertical == FALSE)
		m_bVertical = TRUE;
	else
		m_bVertical = FALSE;
	
 	m_gridCtrl.SetGridLineOrientation(m_bHorizontal, m_bVertical);
}


void CListMultiOptionCtrl::SetGridColResize() 
{
	if (!UpdateData(TRUE))
		return;
	
	if( m_bResize == FALSE)
		m_bResize = TRUE;
	else
		m_bResize = FALSE;

 	m_gridCtrl.SetResizing(m_bResize);
}


void CListMultiOptionCtrl::SetRadioCenter() 
{
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT;
	lvc.fmt = LVCFMT_CENTER;

 	m_gridCtrl.SetColumn(0, &lvc);
	m_gridCtrl.SetColumn(1, &lvc);
	m_gridCtrl.SetColumn(2, &lvc);

	m_gridCtrl.RedrawWindow();
}

void CListMultiOptionCtrl::SetRadioLeft() 
{
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT;
	lvc.fmt = LVCFMT_LEFT;

 	m_gridCtrl.SetColumn(0, &lvc);
	m_gridCtrl.SetColumn(1, &lvc);
	m_gridCtrl.SetColumn(2, &lvc);
	
	
	m_gridCtrl.RedrawWindow();
}

void CListMultiOptionCtrl::SetRadioRight() 
{
	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT;
	lvc.fmt = LVCFMT_RIGHT;

 	m_gridCtrl.SetColumn(0, &lvc);
	m_gridCtrl.SetColumn(1, &lvc);
	m_gridCtrl.SetColumn(2, &lvc);

	m_gridCtrl.RedrawWindow();
}

void CListMultiOptionCtrl::SingleCheck(NMHDR* pNMHDR, LRESULT* pResult) 
{
		
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;
	int nSelected = pNMListView->iItem;
	
	int iLastItem = m_gridCtrl.GetItemCount();
	
	CString strItem = m_gridCtrl.GetItemText(nSelected, 0);
	
	for(int i = 0; i<iLastItem; i++)
		m_gridCtrl.SetCheck(i, 0);
	
	m_gridCtrl.SetCheck(nSelected, 1);
	
	

	if ( pNMListView->uNewState & LVIS_SELECTED)
	{
		MessageBox(strItem);
	}
		
	
	*pResult;
	
}


void CListMultiOptionCtrl::OnTraceNotification(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
//	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	static BOOL bAbort = FALSE;

	*pResult = bAbort;
}
