// ImageFilterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ImageFilterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CImageDlg dialog
IMPLEMENT_DYNAMIC(CImageFilterDlg, COXSizeDialogBar)
/////////////////////////////////////////////////////////////////////////////
// CImageFilterDlg dialog


CImageFilterDlg::CImageFilterDlg(CWnd* pParent /*=NULL*/)
:COXSizeDialogBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	//{{AFX_DATA_INIT(CImageFilterDlg)
	
	//}}AFX_DATA_INIT
	m_hMemDC = 0;

	m_bLoadImage = false;
	m_nXScrollPos = 0;
	m_nYScrollPos= 0;
	m_visible = false;
}

CImageFilterDlg::~CImageFilterDlg()
{
	if (m_hMemDC)
	{
		DeleteDC(m_hMemDC);
		m_hMemDC = 0;
	}
}

void CImageFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	COXSizeDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageFilterDlg)
	DDX_Control(pDX, IDC_STC_BRIGHTNESS, m_stcBrightness);
	DDX_Control(pDX, IDC_STC_EFFECT, m_stcEffect);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnReset);
	DDX_Control(pDX, IDC_BTN_BROWSE, m_btnBrowse);
	DDX_Control(pDX, IDC_STATIC_PATH, m_StaticPath);
	DDX_Control(pDX, IDC_PICWND, m_PicWnd);
	DDX_Control(pDX, IDC_CHECK_SHARPNESS, m_btnSharpness);
	DDX_Control(pDX, IDC_CHECK_BLUR, m_btnBlur);
	DDX_Control(pDX, IDC_SCROLL_VERT_SIZE, m_scroll_Vert);
	DDX_Control(pDX, IDC_SCROLL_HORZ_SIZE, m_scroll_Horz);
	DDX_Control(pDX, IDC_CHECK_BLACK_WHITE, m_btnBlackAndWhite);
	DDX_Control(pDX, IDC_CHECK_INVERT, m_btnInvertColor);
	DDX_Control(pDX, IDC_SLIDER_BLUE, m_sli_Blue);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_sli_Contrast);
	DDX_Control(pDX, IDC_SLIDER_RED, m_sli_Red);
	DDX_Control(pDX, IDC_SLIDER_GREEN, m_sli_Green);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageFilterDlg, COXSizeDialogBar)
	//{{AFX_MSG_MAP(CImageFilterDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_INVERT, OnCheckInvert)
	ON_BN_CLICKED(IDC_BTN_BROWSE, OnBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnReset)
	ON_BN_CLICKED(IDC_CHECK_BLACK_WHITE, OnCheckBlackWhite)	
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK_BLUR, OnCheckBlur)
	ON_BN_CLICKED(IDC_CHECK_SHARPNESS, OnCheckSharpness)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageFilterDlg message handlers
BOOL CImageFilterDlg::InitLayoutManager()
{
	
	BOOL retval = TRUE;

	if(!m_LayoutManager.IsAttached()) 
	{
		m_LayoutManager.Attach(this);
		m_LayoutManager.SetMinMax(IDC_PICWND, CSize(240,60), CSize(0,0)); 


		//Constrain static contrast
	m_LayoutManager.SetConstraint(IDC_STATIC_CONTRAST, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_STATIC_CONTRAST, OX_LMS_LEFT, OX_LMT_SAME, 1);


	//Constrain slider contrast
	m_LayoutManager.SetConstraint(IDC_SLIDER_CONTRAST, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_SLIDER_CONTRAST, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_STATIC_CONTRAST);
	//m_LayoutManager.SetConstraint(IDC_SLIDER_CONTRAST, OX_LMS_RIGHT, OX_LMT_OPPOSITE, 1, IDC_STATIC_CONTRAST_LEVEL);

	//Constrain static contrast max range
	m_LayoutManager.SetConstraint(IDC_STATIC_CONTRAST_LEVEL, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_STATIC_CONTRAST_LEVEL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1,IDC_SLIDER_CONTRAST );
	//m_LayoutManager.SetConstraint(IDC_STATIC_CONTRAST_LEVEL, OX_LMS_RIGHT, OX_LMT_OPPOSITE, 1,IDC_STATIC_PATH );

	//Constrain static file path
	m_LayoutManager.SetConstraint(IDC_STATIC_PATH, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_STATIC_PATH, OX_LMS_LEFT, OX_LMT_OPPOSITE, 4, IDC_STATIC_CONTRAST_LEVEL);
	m_LayoutManager.SetConstraint(IDC_STATIC_PATH, OX_LMS_RIGHT, OX_LMT_SAME, -1);

	//Constrain button browse
	m_LayoutManager.SetConstraint(IDC_BTN_BROWSE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_SLIDER_CONTRAST);
	m_LayoutManager.SetConstraint(IDC_BTN_BROWSE, OX_LMS_RIGHT, OX_LMT_SAME, -1);
	
	//Constrain check sharpness
	m_LayoutManager.SetConstraint(IDC_CHECK_SHARPNESS, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_SLIDER_CONTRAST);
	m_LayoutManager.SetConstraint(IDC_CHECK_SHARPNESS, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -1, IDC_BTN_BROWSE);
	m_LayoutManager.SetConstraint(IDC_CHECK_SHARPNESS, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_STATIC_RED_LEVEL);

	

	//Constrain static blue level
	m_LayoutManager.SetConstraint(IDC_STATIC_BLUE_LEVEL, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_SLIDER_CONTRAST);
	m_LayoutManager.SetConstraint(IDC_STATIC_BLUE_LEVEL, OX_LMS_RIGHT, OX_LMT_OPPOSITE, 3, IDC_STC_EFFECT);

	//Constrain static blue
	m_LayoutManager.SetConstraint(IDC_STATIC_BLUE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_SLIDER_CONTRAST);
	m_LayoutManager.SetConstraint(IDC_STATIC_BLUE, OX_LMS_LEFT, OX_LMT_SAME, 1);

	//Constrain slider blue
	m_LayoutManager.SetConstraint(IDC_SLIDER_BLUE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_SLIDER_CONTRAST);
	m_LayoutManager.SetConstraint(IDC_SLIDER_BLUE, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_STATIC_BLUE);
	m_LayoutManager.SetConstraint(IDC_SLIDER_BLUE, OX_LMS_RIGHT, OX_LMT_OPPOSITE, 1, IDC_STATIC_BLUE_LEVEL);

	

	//Constrain check invert color
	m_LayoutManager.SetConstraint(IDC_CHECK_INVERT, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_BTN_BROWSE);
	m_LayoutManager.SetConstraint(IDC_CHECK_INVERT, OX_LMS_RIGHT, OX_LMT_SAME, -1);

	//Constrain check black white
	m_LayoutManager.SetConstraint(IDC_CHECK_BLACK_WHITE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_CHECK_SHARPNESS);
	m_LayoutManager.SetConstraint(IDC_CHECK_BLACK_WHITE, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -1, IDC_BTN_BROWSE);
	m_LayoutManager.SetConstraint(IDC_CHECK_BLACK_WHITE, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_STATIC_RED_LEVEL);

	
	//Constrain static green level
	m_LayoutManager.SetConstraint(IDC_STATIC_GREEN_LEVEL, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_SLIDER_BLUE);
	m_LayoutManager.SetConstraint(IDC_STATIC_GREEN_LEVEL, OX_LMS_RIGHT, OX_LMT_OPPOSITE, 3, IDC_STC_EFFECT);

	//Constrain static green
	m_LayoutManager.SetConstraint(IDC_STATIC_GREEN, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_SLIDER_BLUE);
	m_LayoutManager.SetConstraint(IDC_STATIC_GREEN, OX_LMS_LEFT, OX_LMT_SAME, 1);

	//Constrain slider green
	m_LayoutManager.SetConstraint(IDC_SLIDER_GREEN, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_SLIDER_BLUE);
	m_LayoutManager.SetConstraint(IDC_SLIDER_GREEN, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_STATIC_GREEN);
	m_LayoutManager.SetConstraint(IDC_SLIDER_GREEN, OX_LMS_RIGHT, OX_LMT_OPPOSITE, 1, IDC_STATIC_GREEN_LEVEL);
	
	
	
	//Constrain button reset
	m_LayoutManager.SetConstraint(IDC_BTN_CANCEL, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_CHECK_INVERT);
	m_LayoutManager.SetConstraint(IDC_BTN_CANCEL, OX_LMS_RIGHT, OX_LMT_SAME, -1);

	//Constrain check blur
	m_LayoutManager.SetConstraint(IDC_CHECK_BLUR, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_CHECK_BLACK_WHITE);
	m_LayoutManager.SetConstraint(IDC_CHECK_BLUR, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -1, IDC_BTN_BROWSE);
	m_LayoutManager.SetConstraint(IDC_CHECK_BLUR, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_STATIC_RED_LEVEL);

	//Constrain static red level
	m_LayoutManager.SetConstraint(IDC_STATIC_RED_LEVEL, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_SLIDER_GREEN);
	m_LayoutManager.SetConstraint(IDC_STATIC_RED_LEVEL, OX_LMS_RIGHT, OX_LMT_OPPOSITE, 3, IDC_STC_EFFECT);
	


	//Constrain static red
	m_LayoutManager.SetConstraint(IDC_STATIC_RED, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_SLIDER_GREEN);
	m_LayoutManager.SetConstraint(IDC_STATIC_RED, OX_LMS_LEFT, OX_LMT_SAME, 1);

	//Constrain slider red
	m_LayoutManager.SetConstraint(IDC_SLIDER_RED, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_SLIDER_GREEN);
	m_LayoutManager.SetConstraint(IDC_SLIDER_RED, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_STATIC_RED);
	m_LayoutManager.SetConstraint(IDC_SLIDER_RED, OX_LMS_RIGHT, OX_LMT_OPPOSITE, 1, IDC_STATIC_RED_LEVEL);
	


	//Constrain static brightness
	m_LayoutManager.SetConstraint(IDC_STC_BRIGHTNESS, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_SLIDER_RED);
	m_LayoutManager.SetConstraint(IDC_STC_BRIGHTNESS, OX_LMS_LEFT, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_STC_BRIGHTNESS, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -20, IDC_STC_EFFECT);

	//Constrain static effect
	m_LayoutManager.SetConstraint(IDC_STC_EFFECT, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_SLIDER_RED);
	//m_LayoutManager.SetConstraint(IDC_STC_EFFECT, OX_LMS_LEFT, OX_LMT_SAME, 1, IDC_CHECK_BLUR);
	m_LayoutManager.SetConstraint(IDC_STC_EFFECT, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -5, IDC_BTN_CANCEL);
	
	//Constrain horizontal scroll
	m_LayoutManager.SetConstraint(IDC_SCROLL_HORZ_SIZE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -2, IDC_BTN_CANCEL);
	m_LayoutManager.SetConstraint(IDC_SCROLL_HORZ_SIZE, OX_LMS_LEFT, OX_LMT_SAME, 0);
	m_LayoutManager.SetConstraint(IDC_SCROLL_HORZ_SIZE, OX_LMS_RIGHT, OX_LMT_SAME, 0);

	//Constrain vertical scroll
	m_LayoutManager.SetConstraint(IDC_SCROLL_VERT_SIZE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_SCROLL_HORZ_SIZE);
	m_LayoutManager.SetConstraint(IDC_SCROLL_VERT_SIZE, OX_LMS_TOP, OX_LMT_SAME, 0);
	m_LayoutManager.SetConstraint(IDC_SCROLL_VERT_SIZE, OX_LMS_RIGHT, OX_LMT_SAME, 0);

	// Constrain the static picture
	m_LayoutManager.SetConstraint(IDC_PICWND, OX_LMS_TOP, OX_LMT_SAME, 0);
	m_LayoutManager.SetConstraint(IDC_PICWND, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_SCROLL_HORZ_SIZE);
	m_LayoutManager.SetConstraint(IDC_PICWND, OX_LMS_LEFT,  OX_LMT_SAME, 0);
	m_LayoutManager.SetConstraint(IDC_PICWND, OX_LMS_RIGHT, OX_LMT_OPPOSITE, 0, IDC_SCROLL_VERT_SIZE);


 
	}

return retval;

}



BOOL CImageFilterDlg::OnInitDialog() 
{
	COXSizeDialogBar::OnInitDialog();
	
/*
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		CWnd::SetWindowText(_T("ImageFilterCtrl"));
		GetDlgItem(IDC_PICWND)->SetWindowText(_T("<Imágen>"));
		GetDlgItem(IDC_STC_BRIGHTNESS)->SetWindowText(_T("Luminosidad"));
		GetDlgItem(IDC_STC_EFFECT)->SetWindowText(_T("Efectos"));
		GetDlgItem(IDC_STATIC_PATH)->SetWindowText(_T("<Ruta>"));
		GetDlgItem(IDC_STATIC_R)->SetWindowText(_T("R"));
		GetDlgItem(IDC_STATIC_G)->SetWindowText(_T("V"));
		GetDlgItem(IDC_STATIC_B)->SetWindowText(_T("A"));
		GetDlgItem(IDC_STATIC_C)->SetWindowText(_T("Contraste"));
		
		GetDlgItem(IDC_CHECK_BLUR)->SetWindowText(_T("Borroso"));
		GetDlgItem(IDC_CHECK_BLACK_WHITE)->SetWindowText(_T("Negro/Blanco"));
		GetDlgItem(IDC_CHECK_SHARPNESS)->SetWindowText(_T("Agudeza"));
		GetDlgItem(IDC_CHECK_INVERT)->SetWindowText(_T("Inv. col"));
		GetDlgItem(IDC_BTN_BROWSE)->SetWindowText(_T("Examinar..."));
		GetDlgItem(IDC_BTN_CANCEL)->SetWindowText(_T("Restablecer"));
		break;
	default:
		CWnd::SetWindowText(_T("ImageFilterCtrl"));
		GetDlgItem(IDC_PICWND)->SetWindowText(_T("<Image>"));
		GetDlgItem(IDC_STC_BRIGHTNESS)->SetWindowText(_T("Brightness"));
		GetDlgItem(IDC_STC_EFFECT)->SetWindowText(_T("Effects"));
		GetDlgItem(IDC_STATIC_PATH)->SetWindowText(_T("<Path>"));
		GetDlgItem(IDC_STATIC_R)->SetWindowText(_T("R"));
		GetDlgItem(IDC_STATIC_G)->SetWindowText(_T("G"));
		GetDlgItem(IDC_STATIC_B)->SetWindowText(_T("B"));
		GetDlgItem(IDC_STATIC_C)->SetWindowText(_T("Contrast"));
		
		GetDlgItem(IDC_CHECK_BLUR)->SetWindowText(_T("Blur"));
		GetDlgItem(IDC_CHECK_BLACK_WHITE)->SetWindowText(_T("Black/White"));
		GetDlgItem(IDC_CHECK_SHARPNESS)->SetWindowText(_T("Sharpness"));
		GetDlgItem(IDC_CHECK_INVERT)->SetWindowText(_T("Inv. col"));
		GetDlgItem(IDC_BTN_BROWSE)->SetWindowText(_T("Browse..."));
		GetDlgItem(IDC_BTN_CANCEL)->SetWindowText(_T("Reset"));
		break;
	}
*/	
	
	/*
	AddSzControl(IDC_STC_BRIGHTNESS, mdResize, mdRepos);
	AddSzControl(IDC_STC_EFFECT, mdRepos, mdRepos);
	AddSzControl(IDC_STATIC_PATH, mdResize, mdRepos);
	

	AddSzControl(IDC_STATIC_RED, mdRepos, mdRepos);
	AddSzControl(IDC_STATIC_GREEN, mdRepos, mdRepos);
	AddSzControl(IDC_STATIC_BLUE, mdRepos, mdRepos);
	AddSzControl(IDC_STATIC_CONTRAST, mdNone, mdRepos);
	
	AddSzControl(IDC_STATIC_R, mdNone, mdRepos);
	AddSzControl(IDC_STATIC_G, mdNone, mdRepos);
	AddSzControl(IDC_STATIC_B, mdNone, mdRepos);
	AddSzControl(IDC_STATIC_C, mdNone, mdRepos);
	

	AddSzControl(IDC_SLIDER_RED, mdResize, mdRepos);
	AddSzControl(IDC_SLIDER_GREEN, mdResize, mdRepos);
	AddSzControl(IDC_SLIDER_BLUE, mdResize, mdRepos);
	AddSzControl(IDC_SLIDER_CONTRAST, mdNone, mdRepos);
	
	AddSzControl(IDC_BTN_BROWSE, mdRepos, mdRepos);
	AddSzControl(IDC_BTN_CANCEL, mdRepos, mdRepos);

	AddSzControl(IDC_CHECK_INVERT, mdRepos, mdRepos);
	AddSzControl(IDC_CHECK_SHARPNESS, mdRepos, mdRepos);
    AddSzControl(IDC_CHECK_BLACK_WHITE, mdRepos, mdRepos);
	AddSzControl(IDC_CHECK_BLUR, mdRepos, mdRepos);
	
	AddSzControl(IDC_SCROLL_HORZ_SIZE, mdResize, mdRepos);
	AddSzControl(IDC_SCROLL_VERT_SIZE, mdRepos, mdResize);
	AddSzControl(IDC_PICWND, mdResize, mdResize);
*/

	if(!InitLayoutManager())
	{
		MessageBox(_T("Failed to init layout manager!"));
	}
	
	UpdateData(FALSE);
	

	// TODO: Add extra initialization here	

	m_sli_Red.SetRange(-255, 255, TRUE);
	m_sli_Red.SetPos(0);

	m_sli_Green.SetRange(-255, 255, TRUE);
	m_sli_Green.SetPos(0);

	m_sli_Blue.SetRange(-255, 255, TRUE);
	m_sli_Blue.SetPos(0);

	m_sli_Contrast.SetRange(0, 200, TRUE);
	m_sli_Contrast.SetPos(100);

	m_PicWnd.GetClientRect(&m_Rect);
	

	RECT r = m_Rect;
	r.right += 0;
	r.bottom+= 0;
	r.left+= 0;
	r.top+= 0;
	InvalidateRect(&r, FALSE);
	
	//LoadImage(TEXT("E:\\FOTOS 2007-2010\\Geena_Lee_Nolin\\Geena_Lee_Nolin_Playboy\\glnolin23.JPG"));
	//LoadImage(TEXT("E:\\Mis documentos\\Mis imágenes\\MEAP\\Foto 4.JPG"));
	EnableToolTips();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CImageFilterDlg::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	COXSizeDialogBar::OnUpdateCmdUI(pTarget,FALSE);
}

void CImageFilterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		

		if (!m_bLoadImage)
		{
			BitBlt(dc.m_hDC, m_Rect.left, m_Rect.top,
					m_Rect.right, m_Rect.bottom,
					m_hMemDC, 0, 0, WHITENESS);
		}
		else
		{
			
			m_PicWnd.GetClientRect(&m_Rect);
					
		
			if (m_Image.GetImageWidth() < m_Rect.right)
			{
				BitBlt(dc.m_hDC, m_Rect.left+m_Image.GetImageWidth(), 
					m_Rect.top, m_Rect.right-m_Image.GetImageWidth(), m_Rect.bottom, 
					m_hMemDC, 0, 0, WHITENESS);
			}

			if (m_Image.GetImageHeight() < m_Rect.bottom)
			{
				BitBlt(dc.m_hDC, m_Rect.left, m_Rect.top+m_Image.GetImageHeight(), 
					m_Rect.right, m_Rect.bottom - m_Image.GetImageHeight(), 
					m_hMemDC, 0, 0, WHITENESS);
			}

			if ((m_Image.GetImageWidth()< m_Rect.right) &&  (m_Image.GetImageHeight() < m_Rect.bottom))
			{
				BitBlt(dc.m_hDC, m_Rect.left+m_Image.GetImageWidth(), m_Rect.top+m_Image.GetImageHeight(), 
					m_Rect.right - m_Image.GetImageWidth(), m_Rect.bottom - m_Image.GetImageHeight(), 
					m_hMemDC, 0, 0, WHITENESS);
			}

			// Transfer Image
			BitBlt(dc.m_hDC, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom,
				m_hMemDC, m_nXScrollPos, m_nYScrollPos, SRCCOPY);
		}
		
		
	
	   	COXSizeDialogBar::OnPaint();
	}
}




void CImageFilterDlg::OnBtnBrowse()
{
	
	// Browse the file BMP, ICON, GIF, JPEG, Exif, PNG, TIFF, WMF, and EMF
	TCHAR szFilters[]= TEXT("BMP(*.bmp)|*.bmp|ICON(*.ico)|*.ico|GIF(*.gif)|*.gif|JPEG(*.jpg)|*.jpg|TIFF(*.tif)|*.tif|WMF(*.wmf)|*.wmf|EMF(*.emf)|*.emf|PNG(*.png)|*.png|All Files(*.*)|*.*||");

	CFileDialog fileDlg(TRUE, NULL, NULL, 0, szFilters, this);
	if (fileDlg.DoModal() == IDOK)
	{
		m_PicWnd.GetClientRect(&m_Rect);
		
		m_fileName  = fileDlg.GetPathName();
		m_StaticPath.SetWindowText(m_fileName);
		m_bLoadImage = true;	
	
		CDC *pDC = GetDC();


#ifdef _UNICODE
		
		wchar_t *wszPathName = m_fileName.GetBuffer(MAX_PATH);
				
#else
		
		const char *pszPath = m_fileName.GetBuffer(MAX_PATH);
		unsigned short wszPathName[MAX_PATH] = {0};
		int iRes = mbstowcs(wszPathName, pszPath, MAX_PATH);
		
		if( iRes == 1)
		{
			LANGID dwLanguageID = GetSystemLanguagePrimaryID();
			switch(dwLanguageID)
			{
			case LANG_SPANISH:
				AfxMessageBox(TEXT("La imagen no puede ser cargada"));
				return;
			default:
				AfxMessageBox(TEXT("The image can't be loaded"));
				return;
			}
		}
		
		
#endif

		if (NULL != m_hMemDC)
		{
			DeleteDC(m_hMemDC);
			m_hMemDC = NULL;
		}

		// Load the image and get the memory device context.
		m_hMemDC = m_Image.LoadImage(pDC->m_hDC, wszPathName, m_Rect);	
		ReleaseDC(pDC);
		

		m_sli_Red.SetPos(0);
		m_sli_Green.SetPos(0);
		m_sli_Blue.SetPos(0);		
		m_nXScrollPos = 0;
		m_nYScrollPos = 0;

		m_scroll_Horz.SetScrollPos(m_nXScrollPos);
		m_scroll_Vert.SetScrollPos(m_nXScrollPos);
		
		// Enable color slider bar
		m_sli_Red.EnableWindow();
		m_sli_Green.EnableWindow();
		m_sli_Blue.EnableWindow();
		m_sli_Contrast.EnableWindow();
		m_btnInvertColor.EnableWindow();
		m_btnBlackAndWhite.EnableWindow();
		m_btnBlur.EnableWindow();
		m_btnSharpness.EnableWindow();		
		//((CButton*)GetDlgItem(IDC_BTN_APPLY))->EnableWindow();
		((CButton*)GetDlgItem(IDC_BTN_CANCEL))->EnableWindow();


		m_btnInvertColor.SetCheck(BST_UNCHECKED);
		m_btnBlackAndWhite.SetCheck(BST_UNCHECKED);

		((CButton*)GetDlgItem(IDC_CHECK_BLUR))->SetCheck(BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_CHECK_SHARPNESS))->SetCheck(BST_UNCHECKED);

		m_sli_Contrast.SetPos(100);

		// Set the Horizontal scroll bar range
		if (m_Image.GetImageWidth() > m_Rect.right)
		{
			m_scroll_Horz.ShowWindow(SW_SHOW);
			SCROLLINFO horz;
			horz.cbSize = sizeof(SCROLLINFO);
			horz.fMask = SIF_ALL;
			horz.nMin = 0;
			horz.nMax = m_Image.GetImageWidth()-m_Rect.right;
			horz.nPage =0;
			horz.nPos = 0;
			horz.nTrackPos=0;
			m_scroll_Horz.SetScrollInfo(&horz);			
		}
		else
		{
			m_scroll_Horz.ShowWindow(SW_HIDE);
		}

		// Set the Vertical scroll bar range
		if (m_Image.GetImageHeight() > m_Rect.bottom)
		{
			m_scroll_Vert.ShowWindow(SW_SHOW);
			SCROLLINFO vert;			
			vert.cbSize = sizeof(SCROLLINFO);
			vert.fMask = SIF_ALL;
			vert.nMin = 0;
			vert.nMax = m_Image.GetImageHeight()-m_Rect.bottom;
			vert.nPage =0;
			vert.nPos = 0;
			vert.nTrackPos=0;			
			m_scroll_Vert.SetScrollInfo(&vert);			
		}
		else
		{
			m_scroll_Vert.ShowWindow(SW_HIDE);
		}

		
		RECT r = m_Rect;
		r.right += 0;
		r.bottom+= 0;
		r.left+= 0;
		r.top+= 0;
		InvalidateRect(&r, FALSE);
		Invalidate();
		
		
				
	}
}


void CImageFilterDlg::ApplyEffect() 
{
	// Get the R G B and Contrast value 
	m_nRedPos = m_sli_Red.GetPos();
	m_nGreenPos = m_sli_Green.GetPos();
	m_nBluePos = m_sli_Blue.GetPos();
	m_nContrastPos = m_sli_Contrast.GetPos();

	// For Brightness
	if (m_nRedPos || m_nGreenPos || m_nBluePos )
	{
		CDC *pDC = GetDC();
		m_Image.DisplayBrightness(m_hMemDC, m_Rect, m_nRedPos, m_nGreenPos, m_nBluePos);
		ReleaseDC(pDC);

		m_sli_Red.SetPos(m_nRedPos);
		m_sli_Green.SetPos(m_nGreenPos);
		m_sli_Blue.SetPos(m_nBluePos);
			
		// Red
		//GetDlgItem(IDC_STATIC_RED)->SetWindowText(_T("0"));

		// Green	
		//GetDlgItem(IDC_STATIC_GREEN)->SetWindowText(_T("0"));

		// Blue	
		//GetDlgItem(IDC_STATIC_BLUE)->SetWindowText(_T("0"));		
	}

	// Contrast
	if (100 != m_nContrastPos)
	{
		m_Image.DisplayContrast(m_hMemDC, m_Rect, m_nContrastPos);
		//GetDlgItem(IDC_STATIC_CONTRAST_LEVEL)->SetWindowText(_T("100"));
		m_sli_Contrast.SetPos(m_nContrastPos);
	}
}



// Invert color
void CImageFilterDlg::OnCheckInvert() 
{
	m_Image.DisplayInvertColor(m_hMemDC, m_Rect);
	RECT r = m_Rect;
	r.right += 16;
	r.bottom+= 16;
	InvalidateRect(&r, FALSE);
}

// Black and white color
void CImageFilterDlg::OnCheckBlackWhite() 
{
	// If image is black and white don't need RGB value. So disable that slider conrol bar
	if (BST_CHECKED == m_btnBlackAndWhite.GetCheck())
	{
		m_Image.DisplayBlackAndWhite(m_hMemDC, m_Rect);
		m_sli_Red.EnableWindow(FALSE);
		m_sli_Green.EnableWindow(FALSE);
		m_sli_Blue.EnableWindow(FALSE);
		
		RECT r = m_Rect;
		r.right += 16;
		r.bottom+= 16;
		InvalidateRect(&r, FALSE);
			
	}
	else
	{
		m_btnBlackAndWhite.SetCheck(BST_CHECKED);
	}
	
}

// Blur
void CImageFilterDlg::OnCheckBlur() 
{
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_BLUR))->GetCheck())
	{
		m_Image.DisplayBlur(m_hMemDC, m_Rect);
		RECT r = m_Rect;
		r.right += 16;
		r.bottom+= 16;
		InvalidateRect(&r, FALSE);
	
		
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_BLUR))->SetCheck(BST_CHECKED);
	}
	
}

// Sharpness
void CImageFilterDlg::OnCheckSharpness() 
{
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK_SHARPNESS))->GetCheck())
	{
		m_Image.DisplaySharpness(m_hMemDC, m_Rect);
		RECT r = m_Rect;
		r.right += 16;
		r.bottom+= 16;
		InvalidateRect(&r, FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_CHECK_SHARPNESS))->SetCheck(BST_CHECKED);
	}	
}
/*
void CImageFilterDlg::OnCustomdrawSliderRed(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMCUSTOMDRAW nmcd = *(LPNMCUSTOMDRAW)pNMHDR;

    if ( nmcd.dwDrawStage == CDDS_PREPAINT )
    {
        *pResult = CDRF_NOTIFYITEMDRAW ;
        return;
    }
    
	if ( nmcd.dwDrawStage == CDDS_ITEMPREPAINT )
    {
        if ( nmcd.dwItemSpec == TBCD_THUMB )
        {
            CDC* pDC = CDC::FromHandle( nmcd.hdc );
			CBrush brush(RGB(255, 0, 0));
			CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
            pDC->SelectObject( brush );
            pDC->SelectObject( pen );
            pDC->Ellipse( &(nmcd.rc) );
            pDC->Detach();
            *pResult = CDRF_SKIPDEFAULT;
        }
    } 
}

void CImageFilterDlg::OnCustomdrawSliderGreen(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMCUSTOMDRAW nmcd = *(LPNMCUSTOMDRAW)pNMHDR;

    if ( nmcd.dwDrawStage == CDDS_PREPAINT )
    {
        *pResult = CDRF_NOTIFYITEMDRAW ;
        return;
    }
    
	if ( nmcd.dwDrawStage == CDDS_ITEMPREPAINT )
    {
        if ( nmcd.dwItemSpec == TBCD_THUMB )
        {
            CDC* pDC = CDC::FromHandle( nmcd.hdc );
			CBrush brush(RGB(0, 255, 0));
			CPen pen(PS_SOLID, 1, RGB(0, 255, 0));
            pDC->SelectObject( brush );
            pDC->SelectObject( pen );
            pDC->Ellipse( &(nmcd.rc) );
            pDC->Detach();
            *pResult = CDRF_SKIPDEFAULT;
        }
    }
}

void CImageFilterDlg::OnCustomdrawSliderBlue(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMCUSTOMDRAW nmcd = *(LPNMCUSTOMDRAW)pNMHDR;

    if ( nmcd.dwDrawStage == CDDS_PREPAINT )
    {
        *pResult = CDRF_NOTIFYITEMDRAW ;
        return;
    }
    
	if ( nmcd.dwDrawStage == CDDS_ITEMPREPAINT )
    {
        if ( nmcd.dwItemSpec == TBCD_THUMB )
        {
            CDC* pDC = CDC::FromHandle( nmcd.hdc );
			CBrush brush(RGB(0, 0, 255));
			CPen pen(PS_SOLID, 1, RGB(0, 0, 255));
            pDC->SelectObject( brush );
            pDC->SelectObject( pen );
            pDC->Ellipse( &(nmcd.rc) );
            pDC->Detach();
            *pResult = CDRF_SKIPDEFAULT;
        }
    }
	
}
*/
// Reset the Image
void CImageFilterDlg::OnBtnReset() 
{
	CDC *pDC = GetDC();
	
#ifdef _UNICODE
	wchar_t *wszPathName = m_fileName.GetBuffer(MAX_PATH);

#else
	const char *pszPath = m_fileName.GetBuffer(MAX_PATH);
	unsigned short wszPathName[MAX_PATH] = {0};
	int iRes = mbstowcs(wszPathName, pszPath, MAX_PATH);
	if( iRes == -1)
	{
		LANGID dwLanguageID = GetSystemLanguagePrimaryID();
		switch(dwLanguageID)
		{
		case LANG_SPANISH:
			AfxMessageBox(TEXT("La imagen no puede ser cargada"));
			return;
		default:
			AfxMessageBox(TEXT("The image can't be loaded"));
			return;
		}
	}

#endif
	// Reset all controls
	m_btnBlackAndWhite.SetCheck(BST_UNCHECKED);
	m_btnInvertColor.SetCheck(BST_UNCHECKED);

	m_btnBlur.SetCheck(BST_UNCHECKED);
	m_btnSharpness.SetCheck(BST_UNCHECKED);

	m_sli_Contrast.SetPos(100);
	m_sli_Red.SetPos(0);
	m_sli_Green.SetPos(0);
	m_sli_Blue.SetPos(0);		
	m_nXScrollPos = 0;
	m_nYScrollPos = 0;
	m_scroll_Horz.SetScrollPos(m_nXScrollPos);
	m_scroll_Vert.SetScrollPos(m_nXScrollPos);

	// Red
	GetDlgItem(IDC_STATIC_RED_LEVEL)->SetWindowText(_T("0"));

	// Green	
	GetDlgItem(IDC_STATIC_GREEN_LEVEL)->SetWindowText(_T("0"));

	// Blue	
	GetDlgItem(IDC_STATIC_BLUE_LEVEL)->SetWindowText(_T("0"));

	// Contrast
	GetDlgItem(IDC_STATIC_CONTRAST_LEVEL)->SetWindowText(_T("100"));

	// Enable color slider bar
	m_sli_Red.EnableWindow();
	m_sli_Green.EnableWindow();
	m_sli_Blue.EnableWindow();

	m_hMemDC = m_Image.LoadImage(pDC->m_hDC, wszPathName, m_Rect);	
	ReleaseDC(pDC);

	
	RECT r = m_Rect;
	r.right += 16;
	r.bottom+= 16;
	InvalidateRect(&r, FALSE);
	
}

// Horizontal scroll bar
void CImageFilterDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (m_scroll_Horz.m_hWnd == pScrollBar->m_hWnd)
	{
		m_nXScrollPos = m_scroll_Horz.GetScrollPos();
		
		switch (nSBCode)
		{
		case SB_LEFT:
			m_nXScrollPos = 0;
			break;
		case SB_RIGHT:
			m_nXScrollPos = INT_MAX;
			break;
		case SB_PAGERIGHT:
			m_nXScrollPos += min(INT_MAX, nPos + 20);
			break;
		case SB_PAGELEFT:
			m_nXScrollPos += max(0, nPos - 20);
			break;
		case SB_LINERIGHT:
			m_nXScrollPos += min(INT_MAX, nPos + 1);
			break;
		case SB_LINELEFT:
			m_nXScrollPos += max(0, nPos - 1);
			break;
		case SB_THUMBTRACK:
			m_nXScrollPos = nPos;
			break;
		}  
	
		m_scroll_Horz.SetScrollPos(m_nXScrollPos, TRUE);

		RECT r = m_Rect;
		r.right += 16;
		r.bottom+= 16;
		InvalidateRect(&r, FALSE);
	}


	
	
	TCHAR tszBuf[5] = {0};
	
	// Red
	if (m_sli_Red.m_hWnd == pScrollBar->m_hWnd)
	{
		m_nRedPos = m_sli_Red.GetPos();
		
		switch (nSBCode)
		{
		case TB_TOP:
			m_nRedPos = 0;
			break;
		case TB_BOTTOM:
			m_nRedPos = INT_MAX;
			break;
		case TB_PAGEDOWN:
			m_nRedPos += min(INT_MAX, nPos + 8);
			break;
		case TB_PAGEUP:
			m_nRedPos += max(0, nPos - 8);
			break;
		case TB_LINEDOWN:
			m_nRedPos += min(INT_MAX, nPos + 1);
			break;
		case TB_LINEUP:
			m_nRedPos += max(0, nPos - 1);
			break;
		case TB_THUMBTRACK:
			m_nRedPos = nPos;
			break;
		}  
	
		m_sli_Red.SetPos(m_nRedPos);
		ApplyEffect();

		RECT r = m_Rect;
		r.right += 16;
		r.bottom+= 16;
		InvalidateRect(&r, FALSE);

		_itot(m_sli_Red.GetPos(), tszBuf, 10);
		GetDlgItem(IDC_STATIC_RED_LEVEL)->SetWindowText(tszBuf);
	
	}
	
	

	// Green
	if (m_sli_Green.m_hWnd == pScrollBar->m_hWnd)
	{
		m_nGreenPos = m_sli_Green.GetPos();
		
		switch (nSBCode)
		{
		case TB_TOP:
			m_nGreenPos = 0;
			break;
		case TB_BOTTOM:
			m_nGreenPos = INT_MAX;
			break;
		case TB_PAGEDOWN:
			m_nGreenPos += min(INT_MAX, nPos + 5);
			break;
		case TB_PAGEUP:
			m_nGreenPos += max(0, nPos - 5);
			break;
		case TB_LINEDOWN:
			m_nGreenPos += min(INT_MAX, nPos + 1);
			break;
		case TB_LINEUP:
			m_nGreenPos += max(0, nPos - 1);
			break;
		case TB_THUMBTRACK:
			m_nGreenPos = nPos;
			break;
		}  
	
		m_sli_Green.SetPos(m_nGreenPos);
		ApplyEffect();

		RECT r = m_Rect;
		r.right += 16;
		r.bottom+= 16;
		InvalidateRect(&r, FALSE);
		
		_itot(m_sli_Green.GetPos(), tszBuf, 10);
		GetDlgItem(IDC_STATIC_GREEN_LEVEL)->SetWindowText(tszBuf);
	
	}
	


	// Blue
	if (m_sli_Blue.m_hWnd == pScrollBar->m_hWnd)
	{
		m_nBluePos = m_sli_Blue.GetPos();
		
		switch (nSBCode)
		{
		case TB_TOP:
			m_nBluePos = 0;
			break;
		case TB_BOTTOM:
			m_nBluePos = INT_MAX;
			break;
		case TB_PAGEDOWN:
			m_nBluePos += min(INT_MAX, nPos + 5);
			break;
		case TB_PAGEUP:
			m_nBluePos += max(0, nPos - 5);
			break;
		case TB_LINEDOWN:
			m_nBluePos += min(INT_MAX, nPos + 1);
			break;
		case TB_LINEUP:
			m_nBluePos += max(0, nPos - 1);
			break;
		case TB_THUMBTRACK:
			m_nBluePos = nPos;
			break;
		}  
	
		m_sli_Blue.SetPos(m_nBluePos);
		ApplyEffect();

		RECT r = m_Rect;
		r.right += 16;
		r.bottom+= 16;
		InvalidateRect(&r, FALSE);
		
		_itot(m_sli_Blue.GetPos(), tszBuf, 10);
		GetDlgItem(IDC_STATIC_BLUE_LEVEL)->SetWindowText(tszBuf);
	
	}
	
	

	// Contrast
	if (m_sli_Contrast.m_hWnd == pScrollBar->m_hWnd)
	{
		m_nContrastPos = m_sli_Contrast.GetPos();
		
		switch (nSBCode)
		{
		case TB_TOP:
			m_nContrastPos = 0;
			break;
		case TB_BOTTOM:
			m_nContrastPos = INT_MAX;
			break;
		case TB_PAGEDOWN:
			m_nContrastPos += min(INT_MAX, nPos + 5);
			break;
		case TB_PAGEUP:
			m_nContrastPos += max(0, nPos - 5);
			break;
		case TB_LINEDOWN:
			m_nContrastPos += min(INT_MAX, nPos + 1);
			break;
		case TB_LINEUP:
			m_nContrastPos += max(0, nPos - 1);
			break;
		case TB_THUMBTRACK:
			m_nContrastPos = nPos;
			break;
		}  
	
		m_sli_Contrast.SetPos(m_nContrastPos);
		ApplyEffect();

		RECT r = m_Rect;
		r.right += 16;
		r.bottom+= 16;
		InvalidateRect(&r, FALSE);
		
		_itot(m_sli_Contrast.GetPos(), tszBuf, 10);
		GetDlgItem(IDC_STATIC_CONTRAST_LEVEL)->SetWindowText(tszBuf);
	
	}

	
	
    COXSizeDialogBar::OnHScroll(nSBCode, nPos, pScrollBar);
}

// Vertical scroll bar
void CImageFilterDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

	if (m_scroll_Vert.m_hWnd == pScrollBar->m_hWnd)
	{
		m_nYScrollPos = m_scroll_Vert.GetScrollPos();

		switch (nSBCode)
		{
		
		case SB_TOP:
			m_nYScrollPos = 0;
			break;
		case SB_BOTTOM:
			m_nYScrollPos = INT_MAX;
			break;
		case SB_PAGEDOWN:
			m_nYScrollPos += min(INT_MAX, nPos + 20);
			break;
		case SB_PAGEUP:
			m_nYScrollPos += max(0, nPos - 20);
			break;
		case SB_LINEDOWN:
			m_nYScrollPos += min(INT_MAX, nPos + 1);
			break;
		case SB_LINEUP:
			m_nYScrollPos += max(0, nPos - 1);
			break;
		case SB_THUMBTRACK:
			m_nYScrollPos = nPos;
			break;
		
		}
		
		m_scroll_Vert.SetScrollPos(m_nYScrollPos, TRUE);
				
		RECT r = m_Rect;
		r.right += 16;
		r.bottom+= 16;
		InvalidateRect(&r, FALSE);
			
		
	
	}
	
	COXSizeDialogBar::OnVScroll(nSBCode, nPos, pScrollBar);
}

// On button OK
/*
void CImageFilterDlg::OnBtnOk() 
{	
	COXSizeDialogBar::OnOK();	
}
*/


void CImageFilterDlg::OnSize(UINT nType, int cx, int cy) 
{
	COXSizeDialogBar::OnSize(nType, cx, cy);
	
	
	// TODO: Add your message handler code here
	if(GetUpdateRect(&m_Rect, FALSE))
	{
		m_PicWnd.GetClientRect(&m_Rect);


		// Set the Horizontal scroll bar range
		if (m_Image.GetImageWidth() > m_Rect.right)
		{
			m_scroll_Horz.ShowWindow(SW_SHOW);
			SCROLLINFO horz;
			horz.cbSize = sizeof(SCROLLINFO);
			horz.fMask = SIF_ALL;
			horz.nMin = 0;
			horz.nMax = m_Image.GetImageWidth()-m_Rect.right;
			horz.nPage =0;
			horz.nPos = 0;
			horz.nTrackPos=0;
			m_scroll_Horz.SetScrollInfo(&horz);
			
		}
		else
		{
			m_scroll_Horz.ShowWindow(SW_HIDE);
		}

		// Set the Vertical scroll bar range
		if (m_Image.GetImageHeight() > m_Rect.bottom)
		{
			m_scroll_Vert.ShowWindow(SW_SHOW);
			SCROLLINFO vert;			
			vert.cbSize = sizeof(SCROLLINFO);
			vert.fMask = SIF_ALL;
			vert.nMin = 0;
			vert.nMax = m_Image.GetImageHeight()-m_Rect.bottom;
			vert.nPage =0;
			vert.nPos = 0;
			vert.nTrackPos=0;			
			m_scroll_Vert.SetScrollInfo(&vert);
			
		}
		else
		{
			m_scroll_Vert.ShowWindow(SW_HIDE);
		}
		
		
		RECT r = m_Rect;
		r.right += 0;
		r.bottom+= 0;
		r.left+= 0;
		r.top+= 0;
		InvalidateRect(&r, FALSE);
		Invalidate();
		
		
		/*
		CRect rect;
		GetClientRect(rect);
		InvalidateRect(&rect, FALSE);
		*/
		
	}		
	
}



void CImageFilterDlg::LoadImage(CString szfileName)
{
		
		m_PicWnd.GetClientRect(&m_Rect);
		
		m_fileName  = szfileName;
		m_StaticPath.SetWindowText(m_fileName);
		m_bLoadImage = true;	
	
		CDC *pDC = GetDC();


#ifdef _UNICODE
		
		wchar_t *wszPathName = m_fileName.GetBuffer(MAX_PATH);
				
#else
		
		const char *pszPath = m_fileName.GetBuffer(MAX_PATH);
		unsigned short wszPathName[MAX_PATH] = {0};
		int iRes = mbstowcs(wszPathName, pszPath, MAX_PATH);
		
		if( iRes == 1)
		{
			LANGID dwLanguageID = GetSystemLanguagePrimaryID();
			switch(dwLanguageID)
			{
			case LANG_SPANISH:
				AfxMessageBox(TEXT("La imagen no puede ser cargada"));
				return;
			default:
				AfxMessageBox(TEXT("The image can't be loaded"));
				return;
			}
		}
		
		
#endif

		if (NULL != m_hMemDC)
		{
			DeleteDC(m_hMemDC);
			m_hMemDC = NULL;
		}

		// Load the image and get the memory device context.
		m_hMemDC = m_Image.LoadImage(pDC->m_hDC, wszPathName, m_Rect);	
		ReleaseDC(pDC);
		

		m_sli_Red.SetPos(0);
		m_sli_Green.SetPos(0);
		m_sli_Blue.SetPos(0);		
		m_nXScrollPos = 0;
		m_nYScrollPos = 0;

		m_scroll_Horz.SetScrollPos(m_nXScrollPos);
		m_scroll_Vert.SetScrollPos(m_nXScrollPos);
		
		// Enable color slider bar
		m_sli_Red.EnableWindow();
		m_sli_Green.EnableWindow();
		m_sli_Blue.EnableWindow();
		m_sli_Contrast.EnableWindow();
		m_btnInvertColor.EnableWindow();
		m_btnBlackAndWhite.EnableWindow();
		m_btnBlur.EnableWindow();
		m_btnSharpness.EnableWindow();		
		//((CButton*)GetDlgItem(IDC_BTN_APPLY))->EnableWindow();
		((CButton*)GetDlgItem(IDC_BTN_CANCEL))->EnableWindow();


		m_btnInvertColor.SetCheck(BST_UNCHECKED);
		m_btnBlackAndWhite.SetCheck(BST_UNCHECKED);

		((CButton*)GetDlgItem(IDC_CHECK_BLUR))->SetCheck(BST_UNCHECKED);
		((CButton*)GetDlgItem(IDC_CHECK_SHARPNESS))->SetCheck(BST_UNCHECKED);

		m_sli_Contrast.SetPos(100);

		// Set the Horizontal scroll bar range
		if (m_Image.GetImageWidth() > m_Rect.right)
		{
			m_scroll_Horz.ShowWindow(SW_SHOW);
			SCROLLINFO horz;
			horz.cbSize = sizeof(SCROLLINFO);
			horz.fMask = SIF_ALL;
			horz.nMin = 0;
			horz.nMax = m_Image.GetImageWidth()-m_Rect.right;
			horz.nPage =0;
			horz.nPos = 0;
			horz.nTrackPos=0;
			m_scroll_Horz.SetScrollInfo(&horz);			
		}
		else
		{
			m_scroll_Horz.ShowWindow(SW_HIDE);
		}

		// Set the Vertical scroll bar range
		if (m_Image.GetImageHeight() > m_Rect.bottom)
		{
			m_scroll_Vert.ShowWindow(SW_SHOW);
			SCROLLINFO vert;			
			vert.cbSize = sizeof(SCROLLINFO);
			vert.fMask = SIF_ALL;
			vert.nMin = 0;
			vert.nMax = m_Image.GetImageHeight()-m_Rect.bottom;
			vert.nPage =0;
			vert.nPos = 0;
			vert.nTrackPos=0;			
			m_scroll_Vert.SetScrollInfo(&vert);			
		}
		else
		{
			m_scroll_Vert.ShowWindow(SW_HIDE);
		}

		
		
		RECT r = m_Rect;
		r.right += 0;
		r.bottom+= 0;
		r.left+= 0;
		r.top+= 0;
		InvalidateRect(&r, FALSE);
		Invalidate();
		

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

void CImageFilterDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
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
	menu.InsertMenu(0, MF_BYPOSITION , ID_CTRL_IMG3_OPEN, GetShort(ID_CTRL_IMG3_OPEN));
	menu.InsertMenu(1, MF_BYPOSITION ,ID_CTRL_IMG3_RESET , GetShort(ID_CTRL_IMG3_RESET));
	menu.InsertMenu(2, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(3, MF_BYPOSITION , ID_CTRL_IMG3_BLUR, GetShort(ID_CTRL_IMG3_BLUR));
	menu.InsertMenu(4, MF_BYPOSITION ,ID_CTRL_IMG3_GRAY , GetShort(ID_CTRL_IMG3_GRAY));
	menu.InsertMenu(5, MF_BYPOSITION ,ID_CTRL_IMG3_SHARP , GetShort(ID_CTRL_IMG3_SHARP));
	menu.InsertMenu(6, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(7, MF_BYPOSITION ,ID_CTRL_IMG3_INVERT , GetShort(ID_CTRL_IMG3_INVERT));
	
	menu.SetMenuTitle(_T("ImageFilterCtrl"),MFT_GRADIENT|MFT_SIDE_TITLE);
	menu.LoadToolBar(IDR_IMAGEFILTERDLG);

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
	*/
}

BOOL CImageFilterDlg::DlgToolTips(UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
    LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	UINT nID = pTTT->uFlags;
	if(pTTT->uFlags & TTF_IDISHWND)
	{
		nID= ::GetDlgCtrlID((HWND)nID);
		if(!nID)
		{
			HWND hWndRed = m_sli_Red.GetSafeHwnd();
            HWND hWndGreen = m_sli_Green.GetSafeHwnd();
            HWND hWndBlue = m_sli_Blue.GetSafeHwnd();
			HWND hWndContrast = m_sli_Contrast.GetSafeHwnd();
			HWND hWndBlur = m_btnBlur.GetSafeHwnd();
			HWND hWndBlackWhite = m_btnBlackAndWhite.GetSafeHwnd();
			HWND hWndSharpness = m_btnSharpness.GetSafeHwnd();
			HWND hWndInvert = m_btnInvertColor.GetSafeHwnd();
			HWND hWndBrowse = m_btnBrowse.GetSafeHwnd();
			HWND hWndReset = m_btnReset.GetSafeHwnd();
			
			
			//Show tooltip Red
			if((HWND)(pNMHDR->idFrom) == hWndRed)
			{	
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Rojo");
					break;
				default :
					pTTT->lpszText = _T("Red");
					break;
				}
				return TRUE;								
			}
            //Show tooltip Green
			if((HWND)(pNMHDR->idFrom) == hWndGreen)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Verde");
					break;
				default :
					pTTT->lpszText = _T("Green");
					break;
				}	
				return TRUE;
			}
            //Show tooltip Blue
			if((HWND)(pNMHDR->idFrom) == hWndBlue)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Azul");
					break;
				default :
					pTTT->lpszText = _T("Blue");
					break;
				}	
				return TRUE;
			}
			//Show tooltip Contrast
			if((HWND)(pNMHDR->idFrom) == hWndContrast)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Regulación de contraste");
					break;
				default :
					pTTT->lpszText = _T("Contrast regulation");
					break;
				}	
				return TRUE;
			}
			//Show tooltip Blur
			if((HWND)(pNMHDR->idFrom) == hWndBlur)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Efecto borroso");
					break;
				default :
					pTTT->lpszText = _T("Blur effect");
					break;
				}	
				return TRUE;
			}
			//Show tooltip Black/White
			if((HWND)(pNMHDR->idFrom) == hWndBlackWhite)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Efecto negro/blanco");
					break;
				default :
					pTTT->lpszText = _T("Black/White effect");
					break;
				}	
				return TRUE;
			}
			//Show tooltip Sharpness
			if((HWND)(pNMHDR->idFrom) == hWndSharpness)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Efecto agudeza");
					break;
				default :
					pTTT->lpszText = _T("Sharpness effect");
					break;
				}	
				return TRUE;
			}
			//Show tooltip Invert Color
			if((HWND)(pNMHDR->idFrom) == hWndInvert)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Invertir colores");
					break;
				default :
					pTTT->lpszText = _T("Invert colors");
					break;
				}
				return TRUE;
			}
			//Show tooltip Browse
			if((HWND)(pNMHDR->idFrom) == hWndBrowse)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Examinar ficheros de imágen");
					break;
				default :
					pTTT->lpszText = _T("Browse image files");
					break;
				}
				return TRUE;
			}
			//Show tooltip Reset
			if((HWND)(pNMHDR->idFrom) == hWndReset)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Restablecer al estado original");
					break;
				default :
					pTTT->lpszText = _T("Reset to original state");
					break;
				}
				return TRUE;
			}
		}
    }
    return FALSE;
}

//-------------------------------------------------------------------
void CImageFilterDlg::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// respond to this event as we need to override it
//-------------------------------------------------------------------
{
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);
	
	m_LayoutManager.RedrawLayout();
		
}
