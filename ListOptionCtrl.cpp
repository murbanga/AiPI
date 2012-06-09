// ListOptionCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ListOptionCtrl.h"
#include "StringInputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CListOptionCtrl, COXSizeControlBar);
/////////////////////////////////////////////////////////////////////////////
// CListOptionCtrl

CListOptionCtrl::CListOptionCtrl()
:COXSizeControlBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	m_bHighlightOnlyText = FALSE;
	m_nIndent = 0;
	
}

CListOptionCtrl::~CListOptionCtrl()
{
	for(int nIndex=0; nIndex<m_arrFonts.GetSize(); nIndex++)
	{
		CFont* pFont=m_arrFonts[nIndex];
		ASSERT(pFont!=NULL);
		delete pFont;
	}

}


BEGIN_MESSAGE_MAP(CListOptionCtrl, COXSizeControlBar)
	//{{AFX_MSG_MAP(CListOptionCtrl)
	ON_WM_CREATE()
	//ON_WM_CONTEXTMENU()
	ON_LBN_SELCHANGE(IDC_LISTBOX_EX, OnSelChangeListBoxEx)
	ON_LBN_DBLCLK(IDC_LISTBOX_EX, OnDblclkListBoxEx)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL, OnItemchangedList)
	//}}AFX_MSG_MAP
		
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListOptionCtrl message handlers

int CListOptionCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(&rect);
		
	//Create CListBox
	if (!m_listBoxEx.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|WS_HSCROLL|WS_VSCROLL
		|LBS_OWNERDRAWVARIABLE|LBS_HASSTRINGS|LBS_NOTIFY |LBS_NOINTEGRALHEIGHT,
		CRect(0,0,0,0), this, IDC_LISTBOX_EX))
		return -1;

	//m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_UNDERLINEHOT|LVS_EX_CHECKBOXES);
    m_listBoxEx.ModifyStyleEx(0, WS_EX_CLIENTEDGE );

	//InitListBox();
	ResetListBox();

	return 0;
}


BOOL CListOptionCtrl::Create(CWnd * pParentWnd, const CString& sTitle /* = _T("ListOptionCtrl")*/,
					const UINT nID /* = IDC_LISBOX_EX */)
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


void CListOptionCtrl::ResetListBox()
{
	m_listBoxEx.ResetContent();

}

void CListOptionCtrl::SetImageList()
{
	m_bHighlightOnlyText=m_listBoxEx.GetHighlightOnlyText();
	m_clrListBoxBack=m_listBoxEx.GetBkColor();
	
	UpdateData(FALSE);

	//AfxMessageBox(_T("AddImageList"));

	// set image list to be displayed
	static CImageList imageList;
	imageList.Create(IDB_IL_LISTBOXCHK,16,0,RGB(192,192,192));
	m_listBoxEx.SetImageList(&imageList);
	
	
	VERIFY(g_fontHeader.CreatePointFont(150,_T("Arial")));
	
}


void CListOptionCtrl::InitListBox()
{

	m_bHighlightOnlyText=m_listBoxEx.GetHighlightOnlyText();
	m_clrListBoxBack=m_listBoxEx.GetBkColor();
	
	UpdateData(FALSE);

	// set image list to be displayed
	static CImageList imageList;
	imageList.Create(IDB_IL_LISTBOXCHK,16,0,RGB(192,192,192));
	m_listBoxEx.SetImageList(&imageList);

	// fonts for items
	static CFont g_fontHeader;
	VERIFY(g_fontHeader.CreatePointFont(150,_T("Arial")));
	static CFont g_fontFamily;
	VERIFY(g_fontFamily.CreatePointFont(140,_T("Times New Roman")));

	// hierarchial items
	AddItem(_T("Simpsons"),0,0,RGB(0,0,0),
		_T("Reside in Springfield, USA"),&g_fontHeader);
	AddItem(_T("Homer"),0,20,RGB(0,0,255),_T("Still has hair"),&g_fontFamily);
	AddItem(_T("Marge"),0,20,RGB(0,0,255),_T(""),&g_fontFamily);
	AddItem(_T("Bart"),0,40,RGB(0,128,0),_T(""),&g_fontFamily);
	AddItem(_T("Lisa"),0,40,RGB(0,128,0),_T(""),&g_fontFamily);
	AddItem(_T("Maggie"),0,40,RGB(0,128,0),_T(""),&g_fontFamily);
	AddItem(_T("GrandPa"),0,20,RGB(128,128,128),_T(""),&g_fontFamily);

	for(int nIndex=0; nIndex<m_listBoxEx.GetCount(); nIndex++)
	{
		CFont* pFont=new CFont;
		m_arrFonts.Add(pFont);
	}

	
	m_listBoxEx.SetCurSel(0);
	
	OnSelChangeListBoxEx();
	


	//GetParentFrame()->RecalcLayout();
	//ResizeParentToFit();



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

/*
void CListOptionCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	
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

	
	
}
*/

//-------------------------------------------------------------------
void CListOptionCtrl::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
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

	m_listBoxEx.MoveWindow(&rect);
}

int CListOptionCtrl::AddItem(LPCTSTR lpszText, int nImageIndex, int nIndent, COLORREF clrText,LPCTSTR lpszTooltipText, CFont* pFont)
{
	int nIndex=m_listBoxEx.AddString(lpszText);
	ASSERT(nIndex!=LB_ERR);
	m_listBoxEx.SetItemImageIndex(nIndex,nImageIndex);
	m_listBoxEx.SetItemIndent(nIndex,nIndent);
	m_listBoxEx.SetItemTextColor(nIndex,clrText);
	m_listBoxEx.SetItemTooltipText(nIndex,lpszTooltipText);
	m_listBoxEx.SetItemFont(nIndex,pFont);
	return nIndex;
}

int CListOptionCtrl::AddItem(LPCTSTR lpszText)
{
	//AfxMessageBox(_T("AddItem1"));
	
	
	static CFont g_fontNormal;
	VERIFY(g_fontNormal.CreatePointFont(120,_T("Arial")));

	int nIndex= m_listBoxEx.AddString(lpszText);
	ASSERT(nIndex!=LB_ERR);
	
	//AfxMessageBox(_T("AddItem2"));
	
	
	m_listBoxEx.SetItemImageIndex(nIndex,0);
	m_listBoxEx.SetItemIndent(nIndex,0);
	m_listBoxEx.SetItemTextColor(nIndex, RGB(0,0,0));
	m_listBoxEx.SetItemTooltipText(nIndex,lpszText);
	m_listBoxEx.SetItemFont(nIndex, &g_fontNormal);

	
	
		
	return nIndex;
}


void CListOptionCtrl::AddItemDirect(LPCTSTR lpcItem, LPCTSTR lpcTip) 
{
	
	//AfxMessageBox(_T("AddItem1"));
	
	// hierarchial items
	AddItem(lpcItem ,0,0,RGB(0,0,0), lpcTip, &g_fontHeader);

	//AfxMessageBox(_T("AddItem2"));
	

	for(int nIndex=0; nIndex<m_listBoxEx.GetCount(); nIndex++)
	{
		CFont* pFont=new CFont;
		m_arrFonts.Add(pFont);
	}
	
	//AfxMessageBox(_T("AddItem3"));

}


void CListOptionCtrl::OnSelChangeListBoxEx() 
{
	
	if(!UpdateData(TRUE))
		return;

	int nIndex= m_listBoxEx.GetCurSel();

		
	ASSERT(nIndex!=LB_ERR);
	
	m_nIndent= m_listBoxEx.GetItemIndent(nIndex);;
	m_clrItemBack= m_listBoxEx.GetItemBkColor(nIndex);
	m_clrItemText= m_listBoxEx.GetItemTextColor(nIndex);
	
	CFont* pFont=m_listBoxEx.GetItemFont(nIndex);
	
	
	ASSERT(pFont!=NULL);
	LOGFONT lf;
	VERIFY(pFont->GetLogFont(&lf));
	
	if((HFONT)m_fontItem!=NULL)
		VERIFY(m_fontItem.DeleteObject());
	VERIFY(m_fontItem.CreateFontIndirect(&lf));

	UpdateData(FALSE);
}

void CListOptionCtrl::SetItemBkColor() 
{
		
	if(!UpdateData(TRUE))
		return;

	CColorDialog dlg ;
	COLORREF colorItemBack ;

	if (dlg.DoModal() == IDOK)
	{
		colorItemBack = dlg.GetColor() ;
		int nIndex=m_listBoxEx.GetCurSel();
		VERIFY(m_listBoxEx.SetItemBkColor(nIndex,colorItemBack));
		
	}

	
}

void CListOptionCtrl::SetItemFont() 
{
	if(!UpdateData(TRUE))
		return;
	
	int nIndex = m_listBoxEx.GetCurSel();
  	
	COLORREF colorItemText;
	CFont fontItem;
	CFont* pFont=  m_arrFonts[nIndex];
	ASSERT(pFont!=NULL);
	
	
	LOGFONT lf;
	
	CFontDialog dlgFont; 
	dlgFont.m_cf.lpLogFont = &lf;
	

	if(dlgFont.DoModal() == IDOK)
	{
		//VERIFY(fontItem.GetLogFont(&lf));
		colorItemText = dlgFont.GetColor();
	
		if(pFont->m_hObject!=NULL)
			VERIFY(pFont->DeleteObject());
		
		VERIFY(pFont->CreateFontIndirect(&lf));
		VERIFY(m_listBoxEx.SetItemFont(nIndex, pFont));
		VERIFY(m_listBoxEx.SetItemTextColor(nIndex, colorItemText));
	}
}

void CListOptionCtrl::SetBkColor() 
{

	if(!UpdateData(TRUE))
		return;

	CColorDialog dlg;
	COLORREF colorListBoxBack;

	if (dlg.DoModal() == IDOK)
	{
		colorListBoxBack = dlg.GetColor();
		m_listBoxEx.SetBkColor(colorListBoxBack);
		VERIFY(m_listBoxEx.SetItemBkColor(-1, colorListBoxBack));
		
	}
}


void CListOptionCtrl::SetHighLightOnlyText() 
{
	
	if(!UpdateData(TRUE))
		return;

	if( m_bHighlightOnlyText == FALSE )
		m_bHighlightOnlyText = TRUE;
	else
		m_bHighlightOnlyText = FALSE;
		
	m_listBoxEx.SetHighlightOnlyText(m_bHighlightOnlyText);
	
}

void CListOptionCtrl::SetIndent() 
{
	
	if(!UpdateData(TRUE))
		return;

	int nTemp = 0;
	CStringInputDlg dlg ;
	int nIndex=m_listBoxEx.GetCurSel();

	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID )
	{
	case LANG_SPANISH:
		dlg.m_strPrompt.Format(TEXT("Introduzca el número de espacios indentados:")) ;
		dlg.szBtnOK = _T("Aceptar");
		dlg.szBtnCancel = _T("Cancelar");
		dlg.szDlgCaption = _T("ListOptionCtrl Cuadro de entrada");
		break;
	default:
		dlg.m_strPrompt.Format(TEXT("Enter the list indent spaces:")) ;
		dlg.szBtnOK = _T("OK");
		dlg.szBtnCancel = _T("Cancel");
		dlg.szDlgCaption = _T("ListOptionCtrl InputBox");
		break;
	}


	if (dlg.DoModal() == IDOK)
	{
		nTemp = _ttoi(dlg.m_strEdit) ;
		if (nTemp >= 0)
			m_nIndent = nTemp;
			VERIFY(m_listBoxEx.SetItemIndent(nIndex,m_nIndent));
			
	}

}


void CListOptionCtrl::OnAddItem() 
{
	
	if(!UpdateData(TRUE))
		return;

	CStringInputDlg dlg ;
	int nIndex=m_listBoxEx.GetCount() + 1;

	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID )
	{
	case LANG_SPANISH:
		dlg.m_strPrompt.Format(TEXT("Introduzca el nuevo item:")) ;
		dlg.szBtnOK = _T("Aceptar");
		dlg.szBtnCancel = _T("Cancelar");
		dlg.szDlgCaption = _T("ListOptionCtrl Cuadro de entrada");
		break;
	default:
		dlg.m_strPrompt.Format(TEXT("Enter the new item:")) ;
		dlg.szBtnOK = _T("OK");
		dlg.szBtnCancel = _T("Cancel");
		dlg.szDlgCaption = _T("ListOptionCtrl InputBox");
		break;
	}


	if (dlg.DoModal() == IDOK)
	{
		LPCTSTR lpcItem = (LPCTSTR)dlg.m_strEdit;
		VERIFY(AddItem(lpcItem));

	}

}

void CListOptionCtrl::DeleteItem() 
{
	
	if(!UpdateData(TRUE))
		return;

	int nTemp = 0;
	CStringInputDlg dlg ;
	int nIndex=m_listBoxEx.GetCurSel();
	m_listBoxEx.DeleteString(nIndex);

	

}


void CListOptionCtrl::OnDblclkListBoxEx()
{
	if(!UpdateData(TRUE))
		return;

	for(int nIndex=0; nIndex<m_listBoxEx.GetCount(); nIndex++)
	{
	
		VERIFY(m_listBoxEx.SetItemImageIndex( nIndex, 0));
	}
	
	CString strSelection;
	nIndex=m_listBoxEx.GetCurSel();
	m_listBoxEx.GetText(nIndex, strSelection);
	
	VERIFY(m_listBoxEx.SetItemImageIndex( nIndex, 1));
	//MessageBox(str);
	
	//Add Command to the CRichEditCtrl
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CRichEditView* pView = (CRichEditView*) pChild->GetActiveView();
	ASSERT(pView);
	CString str;
	pView->GetRichEditCtrl().GetWindowText(str);
	str = str + "\r\n" "Command: " + strSelection;
	pView->GetRichEditCtrl().SetWindowText(str);
	
	g_currentCmdInput = strSelection;


	//Continue with the parser
	if( g_currentParserClass == EXP_PARSER_FILE )
	{
		AfxMessageBox(_T("EXP_PARS_FILE"));
		g_bStopFlag = false; 
		CAipi_ExpParserFile epf;
		epf.ctrl_listoption_continue();
		
		//CAipi_Tokenizer tkz;
		//tkz.v_printTokenizer();
	}
	else if( g_currentParserClass == EXP_PARSER_FILE_GLOBAL )
	{
		AfxMessageBox(_T("EXP_PARS_FILE_GLOBAL"));
		g_bStopFlag = false; 
		CAipi_ExpParserFileGlobal epfg;
		epfg.ctrl_listoption_continue();

	}
	else if( g_currentParserClass == EXP_PARSER_GUI )
	{
		//AfxMessageBox(_T("EXP_PARS_GUI"));
		g_bStopFlag = false; 
		CAipi_ExpParserGUI epg;
		epg.ctrl_listoption_continue();

		
	}
	else if( g_currentParserClass == EXP_PARSER_GUI_GLOBAL )
	{
		//AfxMessageBox(_T("EXP_PARS_GUI_GLOBAL"));
		g_bStopFlag = false; 
		CAipi_ExpParserGUIGlobal epgg;
		epgg.ctrl_listoption_continue();


	}

	
	
}
