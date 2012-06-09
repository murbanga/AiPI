// InfoCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "InfoCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CInfoCtrl, COXSizeControlBar);
/////////////////////////////////////////////////////////////////////////////
// CInfoCtrl

CInfoCtrl::CInfoCtrl()
: COXSizeControlBar( SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
}

CInfoCtrl::~CInfoCtrl()
{
}


BEGIN_MESSAGE_MAP(CInfoCtrl, COXSizeControlBar)
	//{{AFX_MSG_MAP(CInfoCtrl)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoCtrl message handlers
int CInfoCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	//SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

	if (!m_staticCtrl.Create(WS_CHILD|WS_VISIBLE| SS_LEFT,
		CRect(0,0,0,0), this, IDC_STATIC_EX))
		return -1;

	m_staticCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

	

	// older versions of Windows* (NT 3.51 for instance)
	// fail with DEFAULT_GUI_FONT
	//if (!m_font.CreateStockObject(DEFAULT_GUI_FONT))
		//if (!m_font.CreatePointFont(110, _T("Trebuchet MS")))
			if (!m_font.CreatePointFont(160, _T("Dutch801 XBd BT")))
			return -1;

		
	m_staticCtrl.SetFont(&m_font);
	m_staticCtrl.SetWindowText(TEXT("Información sobre cualquier instrucción o ayuda en el Sistema Experto"));
	
	
	return 0;
}




BOOL CInfoCtrl::Create(CWnd * pParentWnd, const CString& sTitle /* = _T("InfoCtrl")*/,
					const UINT nID /* = IDC_STATIC_EX */)
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
void CInfoCtrl::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
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

	m_staticCtrl.MoveWindow(&rect);
}

void CInfoCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
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
	
	menu.InsertMenu(0, MF_BYPOSITION , ID_CTRL_IMG_LEFT, GetShort(ID_CTRL_IMG_LEFT));
	menu.InsertMenu(1, MF_BYPOSITION ,ID_CTRL_IMG_CENTERX , GetShort(ID_CTRL_IMG_CENTERX));
	menu.InsertMenu(2, MF_BYPOSITION , ID_CTRL_IMG_RIGHT, GetShort(ID_CTRL_IMG_RIGHT));
	menu.InsertMenu(3, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(4, MF_BYPOSITION ,ID_CTRL_IMG_TOP , GetShort(ID_CTRL_IMG_TOP));
	menu.InsertMenu(5, MF_BYPOSITION ,ID_CTRL_IMG_CENTERY , GetShort(ID_CTRL_IMG_CENTERY));
	menu.InsertMenu(6, MF_BYPOSITION ,ID_CTRL_IMG_BOTTOM , GetShort(ID_CTRL_IMG_BOTTOM));
	menu.InsertMenu(7, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(8, MF_BYPOSITION ,ID_CTRL_IMG_SCALE , GetShort(ID_CTRL_IMG_SCALE));
	menu.InsertMenu(9, MF_BYPOSITION ,ID_CTRL_IMG_STRETCH , GetShort(ID_CTRL_IMG_STRETCH));
	menu.InsertMenu(10, MF_BYPOSITION ,ID_CTRL_IMG_STRETCHSM , GetShort(ID_CTRL_IMG_STRETCHSM));
	menu.InsertMenu(11, MF_BYPOSITION ,ID_CTRL_IMG_STRETCHXY ,GetShort(ID_CTRL_IMG_STRETCHXY));
	menu.InsertMenu(12, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(13, MF_BYPOSITION ,ID_CTRL_IMG_TILE ,GetShort(ID_CTRL_IMG_TILE));

	
	menu.SetMenuTitle(_T("BitImage"),MFT_GRADIENT|MFT_SIDE_TITLE);
	menu.LoadToolBar(IDR_IMAGE);
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
	*/


}

