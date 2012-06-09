// ImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ImageDlg.h"

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageDlg dialog
IMPLEMENT_DYNAMIC(CImageDlg, COXSizeDialogBar)

CImageDlg::CImageDlg(CWnd* pParent /*=NULL*/)
	:COXSizeDialogBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	//{{AFX_DATA_INIT(CImageDlg)
		
	//}}AFX_DATA_INIT
	m_Image = 0x000000 ;
}


void CImageDlg::DoDataExchange(CDataExchange* pDX)
{
	COXSizeDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageDlg)
		
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageDlg, COXSizeDialogBar)
	//{{AFX_MSG_MAP(CImageDlg)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageDlg message handlers
BOOL CImageDlg::OnInitDialog() 
{
	COXSizeDialogBar::OnInitDialog();

	//Init image pointer
	if((m_Image == 0x000000) && (this->m_hWnd != 0x000000))
		m_Image = new mvImage(this->m_hWnd);

	//Load image
	//CString path = TEXT("E:\\FOTOS 2007-2010\\Allure\\05131_Allure_Mai_2003_JulieBowen_123_961lo.jpg");
	//CString path = TEXT("E:\\FOTOS 2007-2010\\Iran_Castillo\\Iran_Castillo_RevistaHExtremo_Julio2007\\Iran_Castillo_H_Extremo_0.JPG"); 		
 	//CString path = TEXT("E:\\Mis documentos\\Mis imágenes\\MEAP\\Foto 6-2.JPG");
	//LoadImage(path);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImageDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		//SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		//int cxIcon = GetSystemMetrics(SM_CXICON);
		//int cyIcon = GetSystemMetrics(SM_CYICON);
		//CRect rect;
		//GetClientRect(&rect);
		//int x = (rect.Width() - cxIcon + 1) / 2;
		//int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(rect);
		COLORREF colorRGB = ::GetSysColor(COLOR_WINDOW);
		dc.FillSolidRect(rect, colorRGB);
		
		
		if(m_Image->mvIsValidImage())
		{
			m_Image->mvOnPaint();
			
		}
		
		COXSizeDialogBar::OnPaint();
	}



	
	// Do not call COXSizeDialogBar::OnPaint() for painting messages
}

void CImageDlg::LoadImage(CString szfilePath)
{
	CString path = szfilePath;
	m_Image->mvLoadImage(path) ;
 	
	//display image 'best fit' in wind.
 	if(m_Image->mvIsValidImage())	
		m_Image->mvConstraintAll();	
	else
	{
		LANGID dwLanguageID = GetSystemLanguagePrimaryID();
		switch(dwLanguageID)
		{
		case LANG_SPANISH:
			MessageBox(TEXT("La imagen no puede ser cargada"));
			break;
		default:
			MessageBox(TEXT("The image can't be loaded"));
			break;
		}
	}
}



void CImageDlg::OpenImage()
{
	const static _TCHAR BASED_CODE szFilter[] = _T("Picture Files (*.jpg;*.gif;*.bmp;*.png)|*.jpg;*.gif;*.bmp;*.png|All Files (*.*)|*.*||");

	CFileDialog Fdlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

	//Fdlg.DoModal();	
	
	//CFileDialog Fdlg(TRUE) ;
 	if(Fdlg.DoModal() == IDOK)
 	{
 		
 		CString path = Fdlg.GetPathName() ;		
 		m_Image->mvLoadImage(path) ;
 	}//if
 	else 
		return ;
	//display image 'best fit' in wind.
 	if(m_Image->mvIsValidImage())	m_Image->mvConstraintAll();
	
}


void CImageDlg::ImageExit() 
{
	//COXSizeDialogBar::OnOK();	
}

void CImageDlg::StretchAll() 
{
	if(m_Image->mvIsValidImage())
	{
		
		m_Image->mvConstraintAll();
	}		
		
}

void CImageDlg::StretchNothing() 
{
	if(m_Image->mvIsValidImage())
	{
		m_Image->mvConstraintNothing();
	}
	
}


void CImageDlg::StretchHeight() 
{
	if(m_Image->mvIsValidImage())
	{
		m_Image->mvConstraintHeight();
	}
	
}

void CImageDlg::StretchWidth() 
{
	if(m_Image->mvIsValidImage())
	{
		m_Image->mvConstraintWidth();
	}
	
}

void CImageDlg::RotateLeft() 
{
	if(m_Image->mvIsValidImage())
	{
		m_Image->mvRotateLeft();
	}
	
}

void CImageDlg::RotateRight() 
{
	if(m_Image->mvIsValidImage())
	{
		m_Image->mvRotateRight();
	}
	
}

void CImageDlg::ZoomIn() 
{
	if(m_Image->mvIsValidImage())
	{
		m_Image->mvZoomIn();
	}
}

void CImageDlg::ZoomOut() 
{
	if(m_Image->mvIsValidImage())
	{
		m_Image->mvZoomOut();
	}
}



void CImageDlg::OnSize(UINT nType, int cx, int cy) 
{
	COXSizeDialogBar::OnSize(nType, cx, cy);
	
	/*
	if((m_Image != 0x000000) && (this->m_hWnd != 0x000000))
	{
		if(m_Image->mvIsValidImage())	
			m_Image->mvOnSize(nType, cx, cy) ;			
	}
	*/

	
	if( cx|cy)
	{
		UpdateWindow();
	}
	
}

void CImageDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(m_Image->mvIsValidImage())	
		m_Image->mvOnHScroll(nSBCode, nPos, pScrollBar) ;

	COXSizeDialogBar::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CImageDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	
	if(m_Image->mvIsValidImage())	
		m_Image->mvOnVScroll(nSBCode, nPos, pScrollBar) ;
	
	COXSizeDialogBar::OnVScroll(nSBCode, nPos, pScrollBar);
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

void CImageDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point) 
{
	
/*
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_IMAGEDLG));
	CMenu* pMenu = menu.GetSubMenu(1);


	pMenu->SetDefaultItem(0, MF_BYPOSITION | MF_ENABLED);
	pMenu->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);

	
	pMenu->TrackPopupMenu(TPM_LEFTALIGN| TPM_RIGHTBUTTON, point.x, point.y, this);
*/

/*	
	COXBitmapMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	menu.GetSubMenu(5)->GetSubMenu(3)->TrackPopupMenu(TPM_LEFTALIGN| TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());

	//menu.SetMenuTitle(_T("ImageDlg"),MFT_GRADIENT|MFT_SIDE_TITLE);
	//menu.LoadToolBar(IDR_IMAGEDLG);
*/

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
	menu.InsertMenu(0, MF_BYPOSITION , ID_CTRL_IMG2_OPEN, GetShort(ID_CTRL_IMG2_OPEN));
	menu.InsertMenu(1, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(2, MF_BYPOSITION ,ID_CTRL_IMG2_ROTATELEFT , GetShort(ID_CTRL_IMG2_ROTATELEFT));
	menu.InsertMenu(3, MF_BYPOSITION , ID_CTRL_IMG2_ROTATERIGHT, GetShort(ID_CTRL_IMG2_ROTATERIGHT));
	menu.InsertMenu(4, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(5, MF_BYPOSITION ,ID_CTRL_IMG2_ZOOMIN , GetShort(ID_CTRL_IMG2_ZOOMIN));
	menu.InsertMenu(6, MF_BYPOSITION ,ID_CTRL_IMG2_ZOOMOUT , GetShort(ID_CTRL_IMG2_ZOOMOUT));
	menu.InsertMenu(7, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(8, MF_BYPOSITION ,ID_CTRL_IMG2_STRETCHNOTHING , GetShort(ID_CTRL_IMG2_STRETCHNOTHING));
	menu.InsertMenu(9, MF_BYPOSITION ,ID_CTRL_IMG2_STRETCHHEIGHT , GetShort(ID_CTRL_IMG2_STRETCHHEIGHT));
	menu.InsertMenu(10, MF_BYPOSITION ,ID_CTRL_IMG2_STRETCHWIDTH ,GetShort(ID_CTRL_IMG2_STRETCHWIDTH));
	menu.InsertMenu(11, MF_BYPOSITION ,ID_CTRL_IMG2_STRETCHALL ,GetShort(ID_CTRL_IMG2_STRETCHALL));

	menu.SetMenuTitle(_T("ImageCtrl v.2.0"),MFT_GRADIENT|MFT_SIDE_TITLE);
	menu.LoadToolBar(IDR_IMAGEDLG);

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
*/

}

void CImageDlg::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	COXSizeDialogBar::OnUpdateCmdUI(pTarget,FALSE);
}

void CImageDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);

	ClientToScreen(&point);
	//OnContextMenu(0,point);
	
	COXSizeDialogBar::OnRButtonUp(nFlags, point);
}

//-------------------------------------------------------------------
void CImageDlg::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// respond to this event as we need to override it
//-------------------------------------------------------------------
{
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

		
}

