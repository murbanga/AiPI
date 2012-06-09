// ImageCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ImageCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CImageCtrl, COXSizeControlBar);
/////////////////////////////////////////////////////////////////////////////
// CImageCtrl

CImageCtrl::CImageCtrl()
: COXSizeControlBar( SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
}

CImageCtrl::~CImageCtrl()
{
}


BEGIN_MESSAGE_MAP(CImageCtrl, COXSizeControlBar)
	//{{AFX_MSG_MAP(CImageCtrl)
		ON_WM_CREATE()
		ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageCtrl message handlers
int CImageCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	if (!m_staticCtrl.Create(NULL, WS_CHILD|WS_VISIBLE|   
			SS_ICON|SS_CENTER,
		CRect(0,0,0,0), this, IDC_ST_IMG))
		return -1;

	m_staticCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

   
	
	
	CString path = TEXT("C:\\Nivel9_Samples\\Imagenes\\Especies\\ANELIDOS\\28.bmp");
	
	ImageInit(path);
	
	
	return 0;
}



BOOL CImageCtrl::Create(CWnd * pParentWnd, const CString& sTitle /* = _T("ImageCtrl")*/,
					const UINT nID /* = IDC_ST_IMG */)
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

void CImageCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
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

void CImageCtrl::ImageInit( CString szPath)
{
	//Initialize image
	m_img.CreateFromStatic( GetDlgItem(IDC_ST_IMG));
    m_img.SetImgFile(szPath);
	m_img.SetBackgroundBrush( COLOR_WINDOW );
	OnStretch();

}

void CImageCtrl::OpenImage()
{
	const static _TCHAR BASED_CODE szFilter[] = _T("Picture Files (*.bmp)|*.bmp|All Files (*.*)|*.*||");

	CFileDialog Fdlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	//Fdlg.DoModal();	
	
	//CFileDialog Fdlg(TRUE) ;
 	if(Fdlg.DoModal() == IDOK)
 	{
 		
 		CString path = Fdlg.GetPathName() ;		
 		ImageInit(path);
 	}//if
 	
}


void CImageCtrl::OnStretchNormal() 
{
  m_img.SetBltMode(m_img.bltNormal);	
}

void CImageCtrl::OnStretch() 
{
  m_img.SetBltMode(m_img.bltStretch);	
}

void CImageCtrl::OnStretchXY() 
{
  m_img.SetBltMode(m_img.bltFitXY);	
}

void CImageCtrl::OnStretchSM() 
{
  m_img.SetBltMode(m_img.bltFitSm);	
}


void CImageCtrl::OnTile() 
{
  m_img.SetBltMode(m_img.bltTile);	
}


void CImageCtrl::OnLeft() 
{
    m_img.SetAlign(m_img.bltLeft, 0);
}

void CImageCtrl::OnCenterX() 
{
    m_img.SetAlign(m_img.bltCenter, 0);
}

void CImageCtrl::OnRight() 
{
    m_img.SetAlign(m_img.bltRight, 0);
}

void CImageCtrl::OnTop() 
{
    m_img.SetAlign(0, m_img.bltTop);
}

void CImageCtrl::OnCenterY() 
{
    m_img.SetAlign(0, m_img.bltCenter);
}

void CImageCtrl::OnBottom() 
{
    m_img.SetAlign(0, m_img.bltBottom);
}

//-------------------------------------------------------------------
void CImageCtrl::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
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

	m_img.MoveWindow(&rect);
}
