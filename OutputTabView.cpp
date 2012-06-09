// OutputTabView.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "OutputTabView.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include ".\ScintillaCtrl\ScintillaDocView.h"
#include "FindInFilesExtDlg.h"

#include "FileFinder.h"
#include "PathFinder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputTabView

IMPLEMENT_DYNCREATE(COutputTabView, COXSizeControlBar)

COutputTabView::COutputTabView():
COXSizeControlBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	_bSearching = false;
}

COutputTabView::~COutputTabView()
{
}


BEGIN_MESSAGE_MAP(COutputTabView, COXSizeControlBar)
	//{{AFX_MSG_MAP(COutputTabView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL1, OnItemchangedList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL2, OnItemchangedList2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL3, OnItemchangedList3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL4, OnItemchangedList4)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL5, OnItemchangedList5)
	

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputTabView message handlers
void COutputTabView::DoDataExchange(CDataExchange* pDX) 
{
	
	DDX_Control(pDX, IDC_LISTCTRL1, m_listCtrl1);
	DDX_Control(pDX, IDC_LISTCTRL2, m_listCtrl2);
	DDX_Control(pDX, IDC_LISTCTRL3, m_listCtrl3);
	DDX_Control(pDX, IDC_LISTCTRL4, m_listCtrl4);
	DDX_Control(pDX, IDC_LISTCTRL5, m_listCtrl5);
	
	
	COXSizeControlBar::DoDataExchange(pDX);
}

//-------------------------------------------------------------------
void COutputTabView::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
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

	m_TabViewContainer.MoveWindow(&rect);
}





//-------------------------------------------------------------------
int COutputTabView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
//-------------------------------------------------------------------
{
	
//Creates TabViewBar control
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	

    Create3DTabCtrl();

	CreateEdit1();
	//PopulateEdit1();
	
	//CreateEdit2();
	//PopulateEdit2();
	
	
	//CreateList1();
	//PopulateList1();
	
	CreateList2();
	//PopulateList2();
		
	CreateList3();
	//PopulateList3();

	CreateList4();
	PopulateList4();

	CreateList5();
	
	

	CreateHistory1();
	PopulateHistory1();

	
	
		
	m_TabViewContainer.SetActivePageIndex(0);
	
	
	// Set callback function
	_finder.SetCallback(FileFinderProc, this);

	return 0;
}


BOOL COutputTabView::Create(CWnd * pParentWnd,
						 const CString& sTitle /*_T("Output")*/, 
						 const UINT nID /*=ID_OUTPUTTABVIEW*/)
{
	// register a window class for the control bar
	static CString strWndClass;
	if (strWndClass.IsEmpty())
	{
		strWndClass = AfxRegisterWndClass(CS_DBLCLKS);
	}
	
	return COXSizeControlBar::Create(strWndClass, sTitle,
		WS_VISIBLE|WS_CHILD|CBRS_BOTTOM|WS_CLIPCHILDREN,
		CFrameWnd::rectDefault, pParentWnd, nID);
}

int COutputTabView::Create3DTabCtrl()
{
	CRect rect;
	GetClientRect(&rect);

	if(!m_TabViewContainer.Create(this,rect, DEFAULT_TABCTRLSTYLE|TCS_BOTTOM|
		TCS_HOTTRACK|TCS_FOCUSNEVER|WS_VISIBLE|WS_CHILD, ID_OUTPUTTABVIEW))
		return -1;

	VERIFY(m_ilTabImageList.Create(IDB_TABLISTIMAGES,16,1,RGB(192,192,192)));
	m_TabViewContainer.SetImageList(&m_ilTabImageList);
	
	return 0;
}




int COutputTabView::CreateList1()
{
	
//Build page
	/*
	if(!m_listCtrl1.Create(WS_CHILD|LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|
		LVS_SHAREIMAGELISTS|LVS_AUTOARRANGE|LVS_ALIGNLEFT ,CRect(0,0,0,0),
		&m_TabViewContainer,IDC_LISTCTRL1))
		return -1;

	
	m_TabViewContainer.AddPage(&m_listCtrl1,_T("Build"),0);
	
	
	m_listCtrl1.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_INFOTIP);
    m_listCtrl1.ModifyStyleEx(0, WS_EX_CLIENTEDGE| WS_EX_RIGHTSCROLLBAR );
*/

/*	
	//Put Columns titles
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	
	if((m_listCtrl1.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT|LVCF_IMAGE;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.iImage = 0;
		lvc.cx=1000;
		
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
				lvc.pszText=_T("Mensajes Compilación");
			break;
			default:
				lvc.pszText=_T("Build Messages");
			break;
		}
		
		m_listCtrl1.InsertColumn(0, &lvc);
	}
*/
	
	m_listCtrl1.InsertColumn(0, _T("Build Messages"), LVCFMT_LEFT, 1500);
return 0;

}

int COutputTabView::CreateList2()
{
		//Create image list
	
	HICON hIcon[10];
	int n;


	//Debug page
	if(!m_listCtrl2.Create(WS_CHILD|LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|
		LVS_SHAREIMAGELISTS|LVS_AUTOARRANGE|LVS_ALIGNLEFT,CRect(0,0,0,0),
		&m_TabViewContainer,IDC_LISTCTRL2))
		return -1;
		
		
	m_TabViewContainer.AddPage(&m_listCtrl2,_T("Debug"), 1);

	
	
	m_ilImageList2.Create(16, 16, 0, 7, 10); // small icons
	hIcon[0] = AfxGetApp()->LoadIcon(IDI_ERROR_LEX);
	hIcon[1] = AfxGetApp()->LoadIcon(IDI_ERROR_SYNTAX);
	hIcon[2] = AfxGetApp()->LoadIcon(IDI_ERROR_SEMANT);
	hIcon[3] = AfxGetApp()->LoadIcon(IDI_ERROR_WARNING);
	hIcon[4] = AfxGetApp()->LoadIcon(IDI_ERROR_QUESTION);
	hIcon[5] = AfxGetApp()->LoadIcon(IDI_ERROR_STOP);
	hIcon[6] = AfxGetApp()->LoadIcon(IDI_ERROR_INFO);
	hIcon[7] = AfxGetApp()->LoadIcon(IDI_JS);
	hIcon[8] = AfxGetApp()->LoadIcon(IDI_VBS);
	
	for (n = 0; n < 10; n++) 
	{
		m_ilImageList2.Add(hIcon[n]);
	}
	m_listCtrl2.SetImageList(&m_ilImageList2, LVSIL_SMALL);


	m_listCtrl2.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_INFOTIP);
    
	
	//Put Columns titles
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	if((m_listCtrl2.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=24;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
				
				lvc.pszText= _T("");
            break; 
			default:
				lvc.pszText= _T("");
			break;	
			
		}

		m_listCtrl2.InsertColumn(0,&lvc);
		
	}

	
	if((m_listCtrl2.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=75;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
				
				lvc.pszText= _T("Línea No.");
            break; 
			default:
				lvc.pszText= _T("Line No.");
			break;	
			
		}

		m_listCtrl2.InsertColumn(1,&lvc);
		
	}
	
	if((m_listCtrl2.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=100;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
				
				lvc.pszText= _T("Pos. Caracter");
            break; 
			default:
				lvc.pszText= _T("Character Pos.");
			break;	
			
		}

		m_listCtrl2.InsertColumn(2,&lvc);
		
	}


	if((m_listCtrl2.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=750;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
				
				lvc.pszText= _T("Descripción Depuración");
            break; 
			default:
				lvc.pszText= _T("Debug Description");
			break;	
			
		}

		m_listCtrl2.InsertColumn(3,&lvc);
		
	}

	if((m_listCtrl2.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=300;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
				
				lvc.pszText= _T("Archivo");
            break; 
			default:
				lvc.pszText= _T("File");
			break;	
			
		}

		m_listCtrl2.InsertColumn(4, &lvc);
		
	}

	if((m_listCtrl2.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=75;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
				
				lvc.pszText= _T("Código Error");
            break; 
			default:
				lvc.pszText= _T("Error Code");
			break;	
			
		}

		m_listCtrl2.InsertColumn(5, &lvc);
		
	}


return 0;
}

int COutputTabView::CreateList3()
{
//Create image list
	
	HICON hIcon[3];
	int n;

	//Debug page
	if(!m_listCtrl3.Create(WS_CHILD|LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|
		LVS_SHAREIMAGELISTS|LVS_AUTOARRANGE|LVS_ALIGNLEFT,CRect(0,0,0,0),
		&m_TabViewContainer,IDC_LISTCTRL3))
		return -1;


	m_TabViewContainer.AddPage(&m_listCtrl3,_T("Find in files"), 2);

	
	m_ilImageList3.Create(16, 16, 0, 3, 3); // small icons
	hIcon[0] = AfxGetApp()->LoadIcon(IDI_FIND1);
	hIcon[1] = AfxGetApp()->LoadIcon(IDI_FIND2);
	hIcon[2] = AfxGetApp()->LoadIcon(IDI_FIND3);
		
	for (n = 0; n < 3; n++) 
	{
		m_ilImageList3.Add(hIcon[n]);
	}
	m_listCtrl3.SetImageList(&m_ilImageList3, LVSIL_SMALL);


	
	m_listCtrl3.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_UNDERLINEHOT|LVS_EX_ONECLICKACTIVATE|LVS_EX_INFOTIP);
    

   //Put Columns titles
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();


	if((m_listCtrl3.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=20;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:
				lvc.pszText=_T("");
				break;
			default:
				lvc.pszText=_T("");
				break;
		}		
				
		m_listCtrl3.InsertColumn(0,&lvc);
	}
	

	

	if((m_listCtrl3.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=50;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:	
				lvc.pszText=_T("Línea");
				break;
			default:
				lvc.pszText=_T("Line");
				break;
		}
		
		m_listCtrl3.InsertColumn(1,&lvc);
	}



	if((m_listCtrl3.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=60;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:	
				lvc.pszText=_T("Caracter");
				break;
			default:
				lvc.pszText=_T("Character");
				break;
		}
		
		m_listCtrl3.InsertColumn(2,&lvc);
	}

	if((m_listCtrl3.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=170;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:	
				lvc.pszText=_T("Ruta");
				break;
			default:
				lvc.pszText=_T("Path");
				break;
		}
		
		m_listCtrl3.InsertColumn(3 ,&lvc);
	}

	
	if((m_listCtrl3.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=75;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:	
				lvc.pszText=_T("Nombre");
				break;
			default:
				lvc.pszText=_T("Name");
				break;
		}
		
		m_listCtrl3.InsertColumn(4 ,&lvc);
	}


	if((m_listCtrl3.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=75;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:	
				lvc.pszText=_T("Tamaño");
				break;
			default:
				lvc.pszText=_T("Size");
				break;
		}
		
		m_listCtrl3.InsertColumn(5 ,&lvc);
	}


	if((m_listCtrl3.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=80;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:	
				lvc.pszText=_T("Modificado");
				break;
			default:
				lvc.pszText=_T("Modified");
				break;
		}
		
		m_listCtrl3.InsertColumn(6 ,&lvc);
	}


	if((m_listCtrl3.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=1000;
		switch(dwLanguageID)
		{
			case LANG_SPANISH:	
				lvc.pszText=_T("Contenido");
				break;
			default:
				lvc.pszText=_T("Content");
				break;
		}
		
		m_listCtrl3.InsertColumn(7,&lvc);
	}
	
	
	return 0;
}

int COutputTabView::CreateList4()
{
	
//FindAll page
	if(!m_listCtrl4.Create(WS_CHILD|LVS_REPORT |LVS_SINGLESEL|LVS_SHOWSELALWAYS|
		LVS_SHAREIMAGELISTS|LVS_AUTOARRANGE|LVS_ALIGNLEFT,CRect(0,0,0,0),
		&m_TabViewContainer,IDC_LISTCTRL4))
		return -1;

	//VERIFY(m_ilImageList4.Create(IDB_TABLISTIMAGES,16,6,RGB(192,192,192)));
	//m_listCtrl4.SetImageList(&m_ilImageList4,TVSIL_NORMAL);

	m_TabViewContainer.AddPage(&m_listCtrl4,_T("SQL Debugging"), 3);
	//Create image list
	m_listCtrl4.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_INFOTIP);
    m_listCtrl4.ModifyStyleEx(0, WS_EX_CLIENTEDGE| WS_EX_RIGHTSCROLLBAR );
	
	
	//Put Columns titles
	if((m_listCtrl4.GetStyle()&LVS_TYPEMASK)==LVS_REPORT)
	{
		LV_COLUMN lvc;
		lvc.mask=LVCF_WIDTH|LVCF_TEXT|LVCF_SUBITEM|LVCF_FMT;
		lvc.fmt=LVCFMT_LEFT;
		lvc.iSubItem=0;
		lvc.cx=200;
		lvc.pszText=_T("Debug Errors");
		m_listCtrl4.InsertColumn(0,&lvc);
	}


	
return 0;
}


int COutputTabView::CreateList5()
{
	
//SQLDebug
	if(!m_listCtrl5.Create(WS_CHILD|LVS_REPORT|LVS_SINGLESEL|LVS_SHOWSELALWAYS|
		LVS_SHAREIMAGELISTS|LVS_AUTOARRANGE|LVS_ALIGNLEFT,CRect(0,0,0,0),
		&m_TabViewContainer,IDC_LISTCTRL5))
		return -1;

	//VERIFY(m_ilImageList5.Create(IDB_TABLISTIMAGES,16,6,RGB(192,192,192)));
	//m_listCtrl5.SetImageList(&m_ilImageList5,TVSIL_NORMAL);

	m_TabViewContainer.AddPage(&m_listCtrl5,_T("Log"), 4);
	
	//Create image list
	m_listCtrl5.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_UNDERLINEHOT|LVS_EX_INFOTIP);
    //m_listCtrl5.ModifyStyleEx(0, WS_EX_CLIENTEDGE| WS_EX_RIGHTSCROLLBAR );
	
	//Put Columns titles
	
	m_listCtrl5.InsertColumn(0, _T("Bitácora"), LVCFMT_LEFT, 1500);
	
return 0;
}


int COutputTabView::CreateHistory1()
{
	
	// result page
	if(!m_HistoryCtrl.Create(NULL,NULL,WS_CHILD,CRect(0,0,0,0),
		&m_TabViewContainer,666))
		return -1;
	
	m_TabViewContainer.AddPage(&m_HistoryCtrl ,_T("Messages"), 5);
	
return 0;
}

int COutputTabView::CreateEdit1()
{
	
	// messages page
	if(!m_editCtrl1.Create(WS_CHILD |WS_TABSTOP|ES_MULTILINE|ES_AUTOHSCROLL|ES_AUTOVSCROLL
		|WS_HSCROLL|WS_VSCROLL|ES_WANTRETURN|ES_READONLY ,CRect(0,0,0,0),&m_TabViewContainer,IDC_RICHEDITCTRL1))
		return -1;
	
	CFont m_font;
	if (!m_font.CreateStockObject(DEFAULT_GUI_FONT))
		if (!m_font.CreatePointFont(80, _T("MS Sans Serif")))
			return -1;

	m_editCtrl1.SetFont(&m_font);
	
	//m_editCtrl1.LimitText(64000);
	//long n = m_editCtrl1.GetLimitText();
	
	m_TabViewContainer.AddPage(&m_editCtrl1 ,_T("Messages"), 0);
	
return 0;

}


int COutputTabView::CreateEdit2()
{
	
	// messages page
	if(!m_editCtrl2.Create(WS_CHILD|WS_TABSTOP|ES_MULTILINE|ES_AUTOHSCROLL|ES_AUTOVSCROLL
		|WS_HSCROLL|WS_VSCROLL|ES_WANTRETURN|ES_READONLY,CRect(0,0,0,0),&m_TabViewContainer,IDC_RICHEDITCTRL2))
		return -1;

	CFont m_font;
	if (!m_font.CreateStockObject(DEFAULT_GUI_FONT))
		if (!m_font.CreatePointFont(80, _T("MS Sans Serif")))
			return -1;

	m_editCtrl2.SetFont(&m_font);
	
	m_TabViewContainer.AddPage(&m_editCtrl2 ,_T("Result"), 6);
	
return 0;

}

LVITEM COutputTabView::AddListItem1( int iItem, int iSubItem, LPTSTR szText, int iImage)
{
	
	//Fills the first column
	LVITEM item;
	item.iItem = iItem;
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT|LVIF_IMAGE;
	item.pszText = szText;
	item.iImage = iImage;
	m_listCtrl1.InsertItem(&item);

	return item;

}

LVITEM COutputTabView::AddListItem2( int iItem, int iSubItem, LPTSTR szText, int iImage)
{
	
	//Fills the first column
	LVITEM item;
	item.iItem = iItem;
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT|LVIF_IMAGE;
	item.pszText = szText;
	item.iImage = iImage;
	VERIFY(m_listCtrl2.InsertItem(&item)!= -1);

	return item;

}

LVITEM COutputTabView::AddListItem3( int iItem, int iSubItem, LPTSTR szText, int iImage)
{
	
	//Fills the first column
	LVITEM item;
	item.iItem = iItem;
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT|LVIF_IMAGE;
	item.pszText = szText;
	item.iImage = iImage;
	m_listCtrl3.InsertItem(&item);

	return item;

}

LVITEM COutputTabView::AddListItem4( int iItem, int iSubItem, LPTSTR szText, int iImage)
{
	
	//Fills the first column
	LVITEM item;
	item.iItem = iItem;
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT|LVIF_IMAGE;
	item.pszText = szText;
	item.iImage = iImage;
	m_listCtrl4.InsertItem(&item);

	return item;

}
	  
void COutputTabView::AddListSubItem1( LVITEM item, int iItem, int iSubItem, LPTSTR szText)
{
	//Fills the rest columns
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT;
	item.pszText = szText;
	m_listCtrl1.SetItem( &item);

	return;

}
	  
void COutputTabView::AddListSubItem2( LVITEM item, int iItem, int iSubItem, LPTSTR szText)
{
	//Fills the rest columns
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT;
	item.pszText = szText;
	m_listCtrl2.SetItem(&item);

	return;

}

void COutputTabView::AddListSubItem3( LVITEM item, int iItem, int iSubItem, LPTSTR szText)
{
	//Fills the rest columns
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT;
	item.pszText = szText;
	VERIFY(m_listCtrl3.SetItem(&item)!= -1);

	return;

}

void COutputTabView::AddListSubItem4( LVITEM item, int iItem, int iSubItem, LPTSTR szText)
{
	//Fills the rest columns
	item.iSubItem = iSubItem;
	item.mask = LVIF_TEXT;
	item.pszText = szText;
	m_listCtrl4.SetItem(&item);

	return;

}


void COutputTabView::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
		
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;
	int nSelected = pNMListView->iItem;
	CString strItem = m_listCtrl1.GetItemText(nSelected, 0);
	

	if ( pNMListView->uNewState & LVIS_SELECTED)
		MessageBox(strItem);
	
	*pResult;

	Beep(nSelected*1000, 100);
	
}

void COutputTabView::OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//CAIPIEditView notification modified message
    g_bNotificationModified = false; 
	
	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;
	int nSelected = pNMListView->iItem;
	
	
	CString strItemLine = m_listCtrl2.GetItemText(nSelected, 1);
	CString strItemPos = m_listCtrl2.GetItemText(nSelected, 2);
	CString strFilePath = m_listCtrl2.GetItemText(nSelected, 4); 

    int iLine = _ttoi(strItemLine);
	unsigned int iPos = _ttoi(strItemPos);
	
	
		
	if ( pNMListView->uNewState & LVIS_SELECTED)
	{
		
		if( strFilePath != _T(" - ") )
		{		
			CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
			BOOL alreadyOpen = pApp->SetDocumentView(strFilePath);
			
			//if document is not already open then open it
			if( alreadyOpen == FALSE )
			{
				pApp->m_pAIPIEditorDocTemplate->OpenDocumentFile(strFilePath);
				if( pApp == NULL )
				{
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->m_wndOutputTabView.AddMsg1(_T("ERROR: The file  (") + strFilePath + _T(")   could not be linked. Check if the file is not corrupted."));
					return;
				}
			}
			else
			{

				
				//MessageBox(strItem);
				CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
				CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
				CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
				ASSERT(pView);
				CScintillaCtrl& rCtrl = pView->GetCtrl();
		
				// Reset Scintilla Markers 
				rCtrl.MarkerDeleteAll(0);

				// Initilaize error markers
				rCtrl.MarkerDefine(0, SC_MARK_SHORTARROW);
				rCtrl.MarkerSetFore(0, RGB( 0, 0, 255 ));
				rCtrl.MarkerSetBack(0, RGB( 0, 0, 255 ));
		
				// Set error marker to proper line
				rCtrl.GotoLine(iLine -1 );
				rCtrl.MarkerAdd((iLine - 1), 0);

				//Set the cursor position in the GUI
				rCtrl.SetFocus();
				rCtrl.SetSel(iPos, iPos + 1);
			}
		}
		
	}	
	
	*pResult;
	Beep(iPos, 100);

	g_bNotificationModified = true;
	
}

void COutputTabView::OnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	//AfxMessageBox(_T("hola"));
	
	//CAIPIEditView notification modified message
	g_bNotificationModified = false;
	

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;
	int nSelected = pNMListView->iItem;
	
	CString strItemLine		= m_listCtrl3.GetItemText(nSelected, 1);
	CString strItemPos		= m_listCtrl3.GetItemText(nSelected, 2);
	CString strFilePath		= m_listCtrl3.GetItemText(nSelected, 3);
	CString strFileName		= m_listCtrl3.GetItemText(nSelected, 4);
	
	CString strPathName = strFilePath + strFileName;

	int iLine = _ttoi(strItemLine);
	long iPos = _ttoi(strItemPos);
	int len = m_strFindText.GetLength();

		
	if ( pNMListView->uNewState & LVIS_SELECTED)
	{
			
		if( strFileName != _T(" - ") )
		{
		
			CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
			BOOL alreadyOpen = pApp->SetDocumentView(strPathName);
		

				//if document is not already open then open it
			if( alreadyOpen == FALSE )
			{
				CString strExt = strPathName.Right(3);

			
				if( strExt == _T("knw") || strExt == _T("txt") )
				{
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->m_wndOutputTabView.AddMsg1(_T("The file  (") + strFileName + _T(")  was opened."));		
				}
				else if ( strExt == _T("ssn") || strExt == _T("rtf") )
				{
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->m_wndOutputTabView.AddMsg1(_T("WARNING: Aipi session file found (.ipi). The file  (") + strFileName + _T(")  do not belong to Aipi knowlegde files. Check the path and the name of the file."));	
				}
				else if( strExt == _T("csv") || _T("idt") || _T("tre") )
				{
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->m_wndOutputTabView.AddMsg1(_T("WARNING: Aipi tree file (.adt). The file  (") + strFileName + _T(")  do not belong to Aipi knowledge files. Check the path and the name of the file."));
				}
				else
				{
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->m_wndOutputTabView.AddMsg1(_T("WARNING: The file  (") + strFileName + _T(")   do not belong to Aipi knowledge files. Check the path and the name of the file."));
				}
		
				pApp->m_pAIPIEditorDocTemplate->OpenDocumentFile(strPathName);
				if( pApp == NULL )
				{
					CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
					pMainFrame->m_wndOutputTabView.AddMsg1(_T("ERROR: The file  (") + strFileName + _T(")   could not be linked. Check if the file is not corrupted."));
					return;
				}
		
		
			}
			else
			{
				CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
				CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
				CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
				ASSERT(pView);
				CScintillaCtrl& rCtrl = pView->GetCtrl();
				// Reset Scintilla Markers 
				rCtrl.MarkerDeleteAll(0);

				// Initilaize error markers
				rCtrl.MarkerDefine(0, SC_MARK_SHORTARROW);
				rCtrl.MarkerSetFore(0, RGB( 0, 0, 255 ));
				rCtrl.MarkerSetBack(0, RGB( 0, 0, 255 ));
		
				// Set error marker to proper line
				rCtrl.GotoLine(iLine -1 );
				rCtrl.MarkerAdd((iLine - 1), 0);

				//Set the cursor position in the GUI
				rCtrl.SetFocus();
				rCtrl.SetSel(iPos - len, iPos);
				
				//int n = pApp->CountOpenDocuments();
				//int b = n;
			}

		}

		 
		
		
	}	

	
	*pResult;
	Beep(iPos, 100);

	g_bNotificationModified = true;
	
	
	
}

void COutputTabView::OnItemchangedList4(NMHDR* pNMHDR, LRESULT* pResult) 
{
		
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;
	int nSelected = pNMListView->iItem;
	CString strItem = m_listCtrl4.GetItemText(nSelected, 0);
	
	if ( pNMListView->uNewState & LVIS_SELECTED)
		MessageBox(strItem);
	
	*pResult;
	Beep(nSelected*1000, 100);

}


void COutputTabView::OnItemchangedList5(NMHDR* pNMHDR, LRESULT* pResult) 
{
		
		NM_LISTVIEW* pNMListView = (NM_LISTVIEW*) pNMHDR;
	int nSelected = pNMListView->iItem;
	CString strItem = m_listCtrl5.GetItemText(nSelected, 0);
	
	if ( pNMListView->uNewState & LVIS_SELECTED)
		MessageBox(strItem);
	
	*pResult;
	Beep(nSelected*1000, 100);
	
}

void COutputTabView::AddMsg1(CString msg)
{
	
	int nLines = m_editCtrl1.GetLineCount();
	int nFirstVisible = m_editCtrl1.GetFirstVisibleLine();

	// Scroll the edit control so that the first visible line
	// is the first line of text.
	
	if (nLines > 0)
	{
		m_editCtrl1.LineScroll(nLines - nFirstVisible , 0);
	}
	
	static CString str;

	str += msg + _T('\xA');
	m_editCtrl1.SetWindowText(str);
	


}


void COutputTabView::AddMsg(LPCTSTR szFmt, ...)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CString str;

	// Format the message text
    va_list argptr;
    va_start(argptr, szFmt);
    str.FormatV(szFmt, argptr);
    va_end(argptr);

	str.Replace(_T("\n"), _T("\r\n"));

	

	CString strWndText;
	m_editCtrl1.GetWindowText(strWndText);
	strWndText += str;
	m_editCtrl1.SetWindowText(strWndText);
	
	//m_editCtrl1.SetSel(str.GetLength()-1, str.GetLength()-2, FALSE);
	m_editCtrl1.LineScroll(-m_editCtrl1.GetLineCount());
	m_editCtrl1.LineScroll(m_editCtrl1.GetLineCount()-4);

}





void COutputTabView::AddMsg2(CString msg)
{
	static CString str;

	str += msg + _T('\xA');
	m_editCtrl2.SetWindowText(str);

}


void COutputTabView::PopulateEdit1()
{
	CString X = _T("456.78");
	CString M = _T("478.23");
	CString D = _T("26.89");

	AddMsg1(_T("************** MEDIDAS CENTRALES *****************\n"));
	AddMsg1(_T("Media Aritmética (X): ") + X + _T("		Desviación Estandar (D): ") + D);
	AddMsg1(_T("Mediana (M): ") + M + _T("		Moda (Mod): ") + M);
	AddMsg1(_T("Fin de los Mensajes"));

}

void COutputTabView::PopulateEdit2()
{
	CString X = _T("456.78");
	CString M = _T("478.23");
	CString D = _T("26.89");

	AddMsg2(_T("************** MEDIDAS CENTRALES *****************\n"));
	AddMsg2(_T("Media Aritmética (X): ") + X + _T("		Desviación Estandar (D): ") + D);
	AddMsg2(_T("Mediana (M): ") + M + _T("		Moda (Mod): ") + M);
	AddMsg2(_T("Fin de los Mensajes"));

}

void COutputTabView::PopulateList1()
{
	//Insert items and subitems
	
	
	LVITEM  Item1, Item2, Item3, Item4;
		
	Item1 = AddListItem1(0, 0, _T("INFO"), 0 );
    AddListSubItem1(Item1, 0, 1,_T("245"));
	AddListSubItem1(Item1, 0, 2, _T("Por favor reinicie la aplicación para cambiar de estilo de menús."));

	Item2 = AddListItem1(1, 0,_T("ADVISE"), 1);	
	AddListSubItem1(Item2, 1, 1,_T("567"));
	AddListSubItem1(Item2, 1, 2, _T("Antes de ejecutar la base de conocimientos debe ser depurada por el Editor AIPI."));
	
	Item3 = AddListItem1(2, 0, _T("ERROR"), 2 );
    AddListSubItem1(Item3, 2, 1,_T("245"));
	AddListSubItem1(Item3, 2, 2, _T("La proposición correspondiente a la regla No.23 no ha sido encontrada."));

	Item4 = AddListItem1(3, 0,_T("WARNING"), 3);	
	AddListSubItem1(Item4, 3, 1,_T("1278"));
	AddListSubItem1(Item4, 3, 2, _T("La función en la regla No.34 está declarada dos veces."));
	

	
	/*
	for(int nIndex=0; nIndex<20; nIndex++)
	{
		CString string;
		string.Format(_T("List control test string number %d"),nIndex);
		VERIFY(m_listCtrl1.InsertItem(nIndex,string,2)!=-1);
	}*/

}

void COutputTabView::PopulateList2()
{
	


	//Insert items and subitems
	
	LVITEM Item1, Item2, Item3, Item4;
	
	
	Item1 = AddListItem2(0, 0, _T("String"), 0 );
    AddListSubItem2(Item1, 0, 1,_T("$Nombre del Cliente$"));
	AddListSubItem2(Item1, 0, 2, _T("José López"));

	Item2 = AddListItem2(1, 0,_T("int"), 1);	
	AddListSubItem2(Item2, 1, 1,_T("$Número de válvulas$"));
	AddListSubItem2(Item2, 1, 2, _T("24"));
	
	Item3 = AddListItem2(2, 0, _T("int"), 2 );
    AddListSubItem2(Item3, 2, 1,_T("$Número de Clientes$"));
	AddListSubItem2(Item3, 2, 2, _T("765"));

	Item4 = AddListItem2(3, 0,_T("float"), 3);	
	AddListSubItem2(Item4, 3, 1,_T("$Promedio de Venta$"));
	AddListSubItem2(Item4, 3, 2, _T("923.14"));

  

}

void COutputTabView::PopulateList3()
{
	

	
	//Insert items and subitems
	LVITEM Item1, Item2, Item3, Item4;
	LPTSTR str = _T("El puma y la niña comen carne");
	
	Item1 = AddListItem3(0, 0, _T("45"), 1 );
    AddListSubItem3(Item1, 0, 1, str);
	
	Item2 = AddListItem3(1, 0,_T("12"), 1);	
	AddListSubItem3(Item2, 1, 1,_T("El camión tiene 4 llantas"));
		
	Item3 = AddListItem3(2, 0, _T("6"), 1 );
    AddListSubItem3(Item3, 2, 1,_T("El puma es mamífero"));
	

	Item4 = AddListItem3(3, 0,_T("29"), 1);	
	AddListSubItem3(Item4, 3, 1,_T("El puma es hembra"));
	
}

void COutputTabView::PopulateList4()
{
	//Insert items and subitems
	LVITEM Item1, Item2, Item3, Item4;
	
	
	Item1 = AddListItem4(0, 0, _T("Revisando identificadores..."), 0 );
    Item2 = AddListItem4(1, 0,_T("Revisando gramática..."), 0);	
	Item3 = AddListItem4(2, 0, _T("Generando código intermedio..."), 0 );
    Item4 = AddListItem4(3, 0,_T("INFORME: La base de conocimientos ha sido revisada."), 0);	
	
}


void COutputTabView::PopulateHistory1()
{
	m_HistoryCtrl.AddLine(_T("Loaded symbols for 'D:\\Ultimate ToolBox\\Samples\\gui\\VisualStudioLikeDemo\\Debug\\VisualStudioLikeDemo.exe'"));
	m_HistoryCtrl.AddLine(_T("Loaded 'F:\\WINNT\\system32\\NTDLL.DLL', no matching symbolic information found."));
	m_HistoryCtrl.AddLine(_T("Loaded symbols for 'F:\\WINNT\\system32\\MFC42D.DLL'"));
	m_HistoryCtrl.AddLine(_T("Loaded symbols for 'F:\\WINNT\\system32\\MSVCRTD.DLL'"));
	m_HistoryCtrl.AddLine(_T("Loaded 'F:\\WINNT\\system32\\KERNEL32.DLL', no matching symbolic information found."));
	m_HistoryCtrl.AddLine(_T("Loaded 'F:\\WINNT\\system32\\riched32.dll', no matching symbolic information found."));
	m_HistoryCtrl.AddLine(_T("Loaded symbols for 'F:\\WINNT\\system32\\MFCO42D.DLL'"));
	m_HistoryCtrl.AddLine(_T("Loaded 'F:\\WINNT\\system32\\USER32.DLL', no matching symbolic information found."));
	m_HistoryCtrl.AddLine(_T("The thread 0xB1 has exited with code 0 (0x0)."));
	m_HistoryCtrl.AddLine(_T("The program 'D:\\Ultimate ToolBox\\Samples\\gui\\VisualStudioLikeDemo\\Debug\\VisualStudioLikeDemo.exe' has exited with code 0 (0x0)."));
	
}


void COutputTabView::DeleteAllList1()
{
	m_listCtrl1.DeleteAllItems();
}

void COutputTabView::DeleteAllList2()
{
	m_listCtrl2.DeleteAllItems();
}

void COutputTabView::DeleteAllList3()
{
	m_listCtrl3.DeleteAllItems();
}


void COutputTabView::DeleteAllEdit1()
{
	m_editCtrl1.SetFocus();
	m_editCtrl1.SetSel(0, -1);
	m_editCtrl1.Clear();
	//m_editCtrl1.Invalidate();
		

}
void COutputTabView::DeleteAllEdit2()
{
	m_editCtrl2.SetSel(0, -1);
	m_editCtrl2.Clear();
}




void COutputTabView::FindExtAsc(CString strFindText, BOOL bCase, BOOL bWord, BOOL bRegularExpression)
{
	//USES_CONVERSION;
	const int FIND_LENGTH = 1040;
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	BOOL bFound = FALSE;
	BOOL bWholeWord = FALSE;
	BOOL bMatchCase = FALSE;
	BOOL bRegExp = FALSE;

	LVITEM Item;
	int iBufferSize = 254;
	int iCount = 0;
	int iLine = 0;
	int iPos = 0;
	int iType = 2;
		
	TCHAR chBuff[16];

	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	rCtrl.GotoPos(iPos);
		
		if ( bCase == TRUE)
			bMatchCase = SCFIND_MATCHCASE;
		if ( bWord == TRUE)
			bWholeWord = SCFIND_WHOLEWORD;
		if ( bRegularExpression == TRUE)
			bRegExp = SCFIND_REGEXP;


	do 
	{
		
		bFound = pView->FindTextSimple(strFindText, TRUE ,bMatchCase ,bWholeWord ,bRegExp);
		
		if (bFound == FALSE )
			break;

		iPos = rCtrl.GetCurrentPos();
		iLine = rCtrl.LineFromPosition(iPos);
		//int iLen = rCtrl.LineLength(iLine);
	
		
		int nStartSel = rCtrl.PositionFromLine(iLine);
		int nEndSel = rCtrl.GetLineEndPosition(iLine);
		int iLength = nEndSel - nStartSel + 1;
		
		
			
			TextRange tr;
			tr.chrg.cpMin = nStartSel;
			tr.chrg.cpMax = nEndSel;
			char chText[FIND_LENGTH];
							
			tr.lpstrText = chText;
			
			if (iLength > FIND_LENGTH )
			{
				rCtrl.GetText(FIND_LENGTH, chText);
			}
			else
				rCtrl.GetTextRange(&tr);
			
			CString strPos = _itot(iPos, chBuff, 10);
			CString strLine = _itot(iLine + 1, chBuff, 10);
			CString strText = (CString)chText;
			strText.Remove('\t');
			
			LPTSTR lpszText = (LPTSTR)strText.GetBuffer(iBufferSize);
			LPTSTR lpszLine = strLine.GetBuffer(iBufferSize);
			LPTSTR lpszPos = strPos.GetBuffer(iBufferSize);
			LPTSTR lpszFilePath = _T("Undefine");
			LPTSTR lpszFileName = _T("Undefine");
			LPTSTR lpszFileSize = _T("Undefine");
			LPTSTR lpszFileDate = _T("Undefine");
			
			//Handle Internationational
			switch(dwLanguageID)
			{
				case LANG_SPANISH:
					Item = AddListItem3(0, 0, _T(""), iType );
					break;
				default:
					Item = AddListItem3(0, 0, _T(""), iType );
					break;
			}
				
			
			AddListSubItem3(Item, 0, 1,lpszLine);
			AddListSubItem3(Item, 0, 2,lpszPos);
			AddListSubItem3(Item, 0, 3,lpszFilePath);
			AddListSubItem3(Item, 0, 4,lpszFileName);
			AddListSubItem3(Item, 0, 5,lpszFileSize);
			AddListSubItem3(Item, 0, 6,lpszFileDate);
			AddListSubItem3(Item, 0, 7,lpszText);
			
			iCount++;
	
	} while( bFound == TRUE);

	CString strCount = _itot(iCount, chBuff, 10);
	LPTSTR lpszCount = _T("0");

	switch(dwLanguageID)
	{
		case 10:
			strCount = strCount + _T("  palabra(s) encontrada(s) de la búsqueda.");
			lpszCount = strCount.GetBuffer(iBufferSize);
			Item = AddListItem3(0, 1, _T("Resultado de búsqueda..."), 1 );
			AddListSubItem3(Item, 0, 2, _T(" - "));
			break;
		default:
			strCount = strCount + _T("  ocurrence(s) have been found.");
			lpszCount = strCount.GetBuffer(iBufferSize);
			Item = AddListItem3(0, 1, _T("Search results..."), 1 );
			AddListSubItem3(Item, 0, 2, _T(" - "));
			break;
	}

	AddListSubItem3(Item, 0, 3, lpszCount);
	
}


void COutputTabView::FindExtDesc(CString strFindText, BOOL bCase, BOOL bWord, BOOL bRegularExpression)
{
	//USES_CONVERSION;
	const int FIND_LENGTH = 1040;
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	BOOL bFound = FALSE;
	BOOL bWholeWord = FALSE;
	BOOL bMatchCase = FALSE;
	BOOL bRegExp = FALSE;

	LVITEM Item;
	int iBufferSize = 254;
	int iCount = 0;
	int iLine = 0;
	int iPos = 0;
	int iType = 1;
		
	TCHAR chBuff[16];

	
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);

	
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	int iLastLine = rCtrl.GetLineCount();
	iPos = rCtrl.GetLineEndPosition(iLastLine -1);
	rCtrl.GotoPos(iPos);
	rCtrl.SetCurrentPos(iPos);

	
		if ( bCase == TRUE)
			bMatchCase = SCFIND_MATCHCASE;
		if ( bWord == TRUE)
			bWholeWord = SCFIND_WHOLEWORD;
		if ( bRegularExpression == TRUE)
			bRegExp = SCFIND_REGEXP;


	do 
	{
		
		bFound = pView->FindTextSimple(strFindText, FALSE ,bMatchCase ,bWholeWord ,bRegExp);
		
		if (bFound == FALSE )
			break;

		iPos = rCtrl.GetCurrentPos();
		iLine = rCtrl.LineFromPosition(iPos);
		//int iLen = rCtrl.LineLength(iLine);
	
		
		int nStartSel = rCtrl.PositionFromLine(iLine);
		int nEndSel = rCtrl.GetLineEndPosition(iLine);
		int iLength = nEndSel - nStartSel + 1;
		
		
			
			TextRange tr;
			tr.chrg.cpMin = nStartSel;
			tr.chrg.cpMax = nEndSel;
			char sText[FIND_LENGTH];
							
			tr.lpstrText = sText;
			
			if (iLength > FIND_LENGTH )
			{
				rCtrl.GetText(FIND_LENGTH, sText);
			}
			else
				rCtrl.GetTextRange(&tr);
			
			CString strPos = _itot(iPos, chBuff, 10);
			CString strLine = _itot(iLine + 1, chBuff, 10);
			CString strText = (CString)sText;
			strText.Remove('\t');
			
			
			LPTSTR lpszText = (LPTSTR)strText.GetBuffer(iBufferSize);
			LPTSTR lpszLine = strLine.GetBuffer(iBufferSize);
			LPTSTR lpszPos = strPos.GetBuffer(iBufferSize);
			LPTSTR lpszFilePath = _T(" - ");
			LPTSTR lpszFileName = _T(" - ");
			LPTSTR lpszFileSize = _T(" - ");
			LPTSTR lpszFileDate = _T(" - ");
			
			//Handle Internationational
			switch(dwLanguageID)
			{
				case LANG_SPANISH:
					Item = AddListItem3(0, 0, _T(""), iType );
					break;
				default:
					Item = AddListItem3(0, 0, _T(""), iType );
					break;
			}
			
			AddListSubItem3(Item, 0, 1,lpszLine);
			AddListSubItem3(Item, 0, 2,lpszPos);
			AddListSubItem3(Item, 0, 3,lpszFilePath);
			AddListSubItem3(Item, 0, 4,lpszFileName);
			AddListSubItem3(Item, 0, 5,lpszFileSize);
			AddListSubItem3(Item, 0, 6,lpszFileDate);
			AddListSubItem3(Item, 0, 7,lpszText);
			
			iCount++;
	
	} while( bFound == TRUE);

	
	
	CString strCount = _itot(iCount, chBuff, 10);
	LPTSTR lpszCount = _T("0");

	LVCOLUMN lvcol;

	switch(dwLanguageID)
	{
		case LANG_SPANISH:
			strCount = _T("Contenido     *** ") + strCount + _T("  palabra(s) encontrada(s) de la búsqueda. ***");
			lpszCount = strCount.GetBuffer(iBufferSize);
			
			lvcol.pszText = lpszCount;
			m_listCtrl3.SetColumn(7, &lvcol);
			break;
		default:
			strCount = _T("Content     *** ")+ strCount + _T("  ocurrence(s) have been found. ***");
			lpszCount = strCount.GetBuffer(iBufferSize);
			
			lvcol.pszText = lpszCount;
			m_listCtrl3.SetColumn(7, &lvcol);
			break;
	}


}


void COutputTabView::FindCurrentDirFiles()
{
	CString currentDir;
	GetCurrentDirectory( MAX_SIZE_PATH, currentDir.GetBufferSetLength(MAX_SIZE_PATH) );
	//AfxMessageBox(currentDir);
	currentDir.ReleaseBuffer();

	CFileFind finder;
	BOOL bContinue;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	if( bContinue = finder.FindFile(_T("*.*")) )
	{
		while(bContinue)
		{
			bContinue = finder.FindNextFile();
			CString strName = finder.GetFileName();
			CString strPath = finder.GetFilePath();
			pMainFrame->m_wndOutputTabView.AddMsg1(strName);		
		}

	}
  
}









void COutputTabView::FindInFiles(CString text, CString folder, CString mask, bool subfolder, bool size, int nmin, int nmax ) 
{
		
	if (_bSearching)
	{
		_finder.StopSearch();
		return;
	}

	CFileFinder::CFindOpts	opts;

	// Set CFindOpts object
	opts.sBaseFolder = folder;
	opts.sFileMask.Format(_T("*%s*"), mask);
	opts.bSubfolders = subfolder;
	opts.FindNormalFiles();

	if (size)
	{
		opts.dwOptionsFlags |= FIND_SIZE;
		opts.nMinSize = (__int64)nmin * (__int64)1024;
		opts.nMaxSize = (__int64)nmax * (__int64)1024;
	}

	if (!text.IsEmpty())
	{
		opts.FindText(text);
	}

	m_listCtrl3.DeleteAllItems();
		

	_bSearching = true;
	_finder.RemoveAll();
	_finder.Find(opts);
	_bSearching = false;

	
}


void COutputTabView::FileFinderProc(CFileFinder *pFinder, DWORD dwCode, void *pCustomParam)
{
	
	
	COutputTabView	*pView = (COutputTabView *)pCustomParam;
	MSG	 msg;
	CString sNewFile;
	CString	sFileSize;
	CString sFileDate;
	CString sPath;
	CString sFileName;
	long	nSize;
	

	CPathFinder	path;
			
	switch (dwCode)
	{
	case FF_FOUND:
		
		sNewFile = pFinder->GetFilePath(pFinder->GetFileCount() -1);
		path = sNewFile;
				
		nSize = (long) (pView->m_fSize / (__int64)1024);
		if (nSize < 10)
			sFileSize.Format(_T("%ld B"), pView->m_fSize);
		else
			sFileSize.Format(_T("%ld KB"), nSize);

		sFileDate = pView->m_fDate.FormatGmt(_T("%d-%m-%Y %I:%M %p"));

		sPath = path.GetLocation();
		sFileName = path.GetFileName();

		// Update list
		pView->AddFileToListCtrl3(sPath, sFileName, sFileSize, sFileDate  );
		break;
		
		
	case FF_FOLDER:
		//pView->SetStatus(pFinder->GetFileCount(), pFinder->GetSearchingFolder());
		break;
		
		


	}

	// Process all process messages
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}





void COutputTabView::AddFileToListCtrl3(CString sPath, CString sFileName, CString sFileSize, CString sFileDate)
{
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	LVITEM Item;
	int iBufferSize = 128;
	int iCount = 0;
	int iType = 2;
	
	TCHAR buffer[1024];
	
		
	
	CString sPos = _itot(g_fcurrentPos, buffer, 10);
	CString sLine = _itot(g_currentLine + 1, buffer, 10);

	
	LPTSTR lpszLine			= sLine.GetBuffer(iBufferSize);
	LPTSTR lpszPos			=  sPos.GetBuffer(iBufferSize);
	LPTSTR lpszFilePath	= (LPTSTR)sPath.GetBuffer(iBufferSize);
	LPTSTR lpszFileName	= (LPTSTR)sFileName.GetBuffer(iBufferSize);
	LPTSTR lpszFileSize	= (LPTSTR)sFileSize.GetBuffer(iBufferSize);
	LPTSTR lpszFileDate	= (LPTSTR)sFileDate.GetBuffer(iBufferSize); 
	LPTSTR lpszText			= (LPTSTR)g_fText.GetBuffer(iBufferSize);


	sFileSize.ReleaseBuffer();
	sFileDate.ReleaseBuffer();
	sPath.ReleaseBuffer();
	sFileName.ReleaseBuffer();   
	sPos.ReleaseBuffer();
	sLine.ReleaseBuffer();
	g_fText.ReleaseBuffer();


	//Handle Internationational
	switch(dwLanguageID)
	{
		case LANG_SPANISH:
			Item = AddListItem3(0, 0, _T(""), iType );
			break;
		default:
			Item = AddListItem3(0, 0, _T(""), iType );
		break;
	}
			
	
	AddListSubItem3(Item, 0, 1,lpszLine);
	AddListSubItem3(Item, 0, 2,lpszPos);
	AddListSubItem3(Item, 0, 3,lpszFilePath);
	AddListSubItem3(Item, 0, 4,lpszFileName);
	AddListSubItem3(Item, 0, 5,lpszFileSize);
	AddListSubItem3(Item, 0, 6,lpszFileDate);
	AddListSubItem3(Item, 0, 7,lpszText);

	iCount = m_listCtrl3.GetItemCount();
	CString strCount = _itot(iCount, buffer, 10);
	LPTSTR lpszCount = _T("0");

	LVCOLUMN lvcol;

	switch(dwLanguageID)
	{
		case LANG_SPANISH:
			strCount = _T("Contenido     *** ") + strCount + _T("  fichero(s) encontrado(s) de la búsqueda. ***");
			lpszCount = strCount.GetBuffer(iBufferSize);
			
			lvcol.pszText = lpszCount;
			m_listCtrl3.SetColumn(7, &lvcol);
			break;
		default:
			strCount = _T("Content     *** ")+ strCount + _T("  ocurrence(s) have been found. ***");
			lpszCount = strCount.GetBuffer(iBufferSize);
			
			lvcol.pszText = lpszCount;
			m_listCtrl3.SetColumn(7, &lvcol);
			break;
	}

	
}






void COutputTabView::AddStatusListCtrl3()
{
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	TCHAR buffer[16];
	int iCount = m_listCtrl3.GetItemCount();
	int iBufferSize = 16;

	CString strCount = _itot(iCount, buffer, 10);
	LPTSTR lpszCount = _T("0");

	LVCOLUMN lvcol;

	switch(dwLanguageID)
	{
		case LANG_SPANISH:
			strCount = _T("Contenido     *** ") + strCount + _T("  palabra(s) encontrada(s) de la búsqueda. ***");
			lpszCount = strCount.GetBuffer(iBufferSize);
			
			lvcol.pszText = lpszCount;
			m_listCtrl3.SetColumn(7, &lvcol);
			break;
		default:
			strCount = _T("Content     *** ")+ strCount + _T("  ocurrence(s) have been found. ***");
			lpszCount = strCount.GetBuffer(iBufferSize);
			
			lvcol.pszText = lpszCount;
			m_listCtrl3.SetColumn(7, &lvcol);
			break;
	}


}














void COutputTabView::SetStatus(int nCount, LPCTSTR szFolder)
{
	CString sStatus;
	LPTSTR lpszStatus = _T("0");


	if (szFolder != NULL)
		sStatus.Format(_T("(%d) - %s"), nCount, szFolder);
	else
		sStatus.Format(_T("%d items found"), nCount);

	
	
	LVCOLUMN lvcol;
	int iBufferSize = 254;
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();

	switch(dwLanguageID)
	{
		case LANG_SPANISH:
			//strCount = _T("Contenido     *** ") + strCount + _T("  palabra(s) encontrada(s) de la búsqueda. ***");
			lpszStatus = sStatus.GetBuffer(iBufferSize);
			
			lvcol.pszText = lpszStatus;
			m_listCtrl3.SetColumn(7, &lvcol);
			break;
		default:
			//strCount = _T("Content     *** ")+ strCount + _T("  ocurrence(s) have been found. ***");
			lpszStatus = sStatus.GetBuffer(iBufferSize);
			
			lvcol.pszText = lpszStatus;
			m_listCtrl3.SetColumn(7, &lvcol);
			break;
	}

}










BOOL COutputTabView::OnEraseBkgnd(CDC* pDC) 
{

	UNREFERENCED_PARAMETER(pDC);
	
	return COXSizeControlBar::OnEraseBkgnd(pDC);
}

