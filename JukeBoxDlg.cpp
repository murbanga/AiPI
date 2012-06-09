//------------------------------------------------------------------------------
// File: JukeboxDlg.cpp
//
// Desc: DirectShow sample code - implementation of CJukeBoxDlg class.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <atlbase.h>
#include "AIPI.h"
#include "JukeBoxDlg.h"
#include "jb_playvideo.h"
#include "mediatypes.h"

// JukeBoxDlg.cpp : implementation file
//


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJukeBoxDlg dialog
IMPLEMENT_DYNAMIC(CJukeBoxDlg, COXSizeDialogBar)

CJukeBoxDlg::CJukeBoxDlg(CWnd* pParent /*=NULL*/)
	:COXSizeDialogBar(/*SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER*/)
{
	//{{AFX_DATA_INIT(CJukeBoxDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CJukeBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	COXSizeDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJukeBoxDlg)
	DDX_Control(pDX, IDC_BUTTON_SET_MEDIADIR, m_ButtonBrowse);
	DDX_Control(pDX, IDC_BUTTON_GRAPHEDIT, m_ButtonGraphEdit);
    DDX_Control(pDX, IDC_BUTTON_PLAY, m_ButtonPlay);
    DDX_Control(pDX, IDC_BUTTON_STOP, m_ButtonStop);
    DDX_Control(pDX, IDC_BUTTON_PAUSE, m_ButtonPause);
    DDX_Control(pDX, IDC_BUTTON_FRAMESTEP, m_ButtonFrameStep);
    DDX_Control(pDX, IDC_CHECK_MUTE, m_CheckMute);
    DDX_Control(pDX, IDC_CHECK_LOOP, m_CheckLoop);
	DDX_Control(pDX, IDC_CHECK_FULLSCREEN, m_CheckFullScreen);
    DDX_Control(pDX, IDC_BUTTON_PROPPAGE, m_ButtonProperties);
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_VolumeSlider);
    DDX_Control(pDX, IDC_SLIDER, m_Seekbar);
    DDX_Control(pDX, IDC_EDIT_MEDIADIR, m_EditMediaDir);
    DDX_Control(pDX, IDC_STATIC_FILEDATE, m_StrFileDate);
    DDX_Control(pDX, IDC_STATIC_FILESIZE, m_StrFileSize);
    DDX_Control(pDX, IDC_STATUS, m_Status);
    DDX_Control(pDX, IDC_MOVIE_SCREEN, m_Screen);
    DDX_Control(pDX, IDC_STATIC_POSITION, m_StrPosition);
    DDX_Control(pDX, IDC_STATIC_IMAGESIZE, m_StrImageSize);
    DDX_Control(pDX, IDC_STATIC_DURATION, m_StrDuration);
    DDX_Control(pDX, IDC_LIST_FILTERS, m_ListFilters);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJukeBoxDlg, COXSizeDialogBar)
	//{{AFX_MSG_MAP(CJukeBoxDlg)
	ON_WM_PAINT()
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnPause)
    ON_BN_CLICKED(IDC_BUTTON_PLAY, OnPlay)
    ON_BN_CLICKED(IDC_BUTTON_STOP, OnStop)
    ON_BN_CLICKED(IDC_CHECK_MUTE, OnCheckMute)
    ON_BN_CLICKED(IDC_CHECK_LOOP, OnCheckLoop)
    ON_LBN_SELCHANGE(IDC_LIST_FILTERS, OnSelchangeListFilters)
    ON_LBN_DBLCLK(IDC_LIST_FILTERS, OnDblclkListFilters)
    ON_BN_CLICKED(IDC_BUTTON_PROPPAGE, OnButtonProppage)
    ON_BN_CLICKED(IDC_BUTTON_FRAMESTEP, OnButtonFramestep)
    ON_BN_CLICKED(IDC_BUTTON_SET_MEDIADIR, OnButtonSetMediadir)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON_GRAPHEDIT, OnButtonGraphedit)
    ON_WM_DESTROY()
    ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_CHECK_FULLSCREEN, OnCheckFullScreen)
	ON_BN_CLICKED(IDC_MOVIE_SCREEN, OnMovieScreen)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
		ON_NOTIFY_EX(TTN_NEEDTEXT,0,DlgToolTips)    // my tool tips  handler
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CJukeBoxDlg message handlers


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CJukeBoxDlg::OnPaint() 
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
        dc.DrawIcon(x, y, m_hIcon);
		
    }
    else
    {
        CenterVideo();
		COXSizeDialogBar::OnPaint();
    }
}



/////////////////////////////////////////////////////////////////////////////
// CJukeBoxDlg DirectShow code and message handlers
BOOL CJukeBoxDlg::InitLayoutManager()
{
	
	BOOL retval = TRUE;

	if(!m_LayoutManager.IsAttached()) 
	{
		m_LayoutManager.Attach(this);
		m_LayoutManager.SetMinMax(IDC_MOVIE_SCREEN, CSize(240,60), CSize(0,0)); 


	//Constrain browse button
	m_LayoutManager.SetConstraint(IDC_BUTTON_SET_MEDIADIR, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_BUTTON_SET_MEDIADIR, OX_LMS_LEFT, OX_LMT_SAME, 1);

	//Constrain edit media dir
	m_LayoutManager.SetConstraint(IDC_EDIT_MEDIADIR, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_EDIT_MEDIADIR, OX_LMS_RIGHT, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_EDIT_MEDIADIR, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_BUTTON_SET_MEDIADIR);
	
	//Constrain check full screen
	m_LayoutManager.SetConstraint(IDC_CHECK_FULLSCREEN, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_EDIT_MEDIADIR);
	m_LayoutManager.SetConstraint(IDC_CHECK_FULLSCREEN, OX_LMS_RIGHT, OX_LMT_SAME, 1);

	//Constrain static duration
	m_LayoutManager.SetConstraint(IDC_STATIC_DURATION, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_EDIT_MEDIADIR);
	m_LayoutManager.SetConstraint(IDC_STATIC_DURATION, OX_LMS_LEFT, OX_LMT_SAME, 1);

	//Constrain static file size
	m_LayoutManager.SetConstraint(IDC_STATIC_FILESIZE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_CHECK_FULLSCREEN);
	m_LayoutManager.SetConstraint(IDC_STATIC_FILESIZE, OX_LMS_RIGHT, OX_LMT_SAME, 1);

	//Constrain static file date
	m_LayoutManager.SetConstraint(IDC_STATIC_FILEDATE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_STATIC_FILESIZE);
	m_LayoutManager.SetConstraint(IDC_STATIC_FILEDATE, OX_LMS_RIGHT, OX_LMT_SAME, 1);

	//Constrain list filters
	m_LayoutManager.SetConstraint(IDC_LIST_FILTERS, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_STATIC_DURATION);
	m_LayoutManager.SetConstraint(IDC_LIST_FILTERS, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -5, IDC_STATIC_FILESIZE);
	m_LayoutManager.SetConstraint(IDC_LIST_FILTERS, OX_LMS_LEFT, OX_LMT_SAME, 1);

	//Constrain static filters
	m_LayoutManager.SetConstraint(IDC_STATIC_FILTERS, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_LIST_FILTERS);
	m_LayoutManager.SetConstraint(IDC_STATIC_FILTERS, OX_LMS_LEFT, OX_LMT_SAME, 1);

	//Constrain button filters properties
	m_LayoutManager.SetConstraint(IDC_BUTTON_PROPPAGE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_STATIC_FILEDATE);
	m_LayoutManager.SetConstraint(IDC_BUTTON_PROPPAGE, OX_LMS_LEFT, OX_LMT_OPPOSITE, 5, IDC_LIST_FILTERS);
	
	
	//Constrain button play
	m_LayoutManager.SetConstraint(IDC_BUTTON_PLAY, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_STATIC_FILTERS);
	m_LayoutManager.SetConstraint(IDC_BUTTON_PLAY, OX_LMS_LEFT, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_BUTTON_PLAY, OX_LMS_RIGHT, OX_LMT_POSITION, 15);

	//Constrain button stop
	m_LayoutManager.SetConstraint(IDC_BUTTON_STOP, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_STATIC_FILTERS);
	m_LayoutManager.SetConstraint(IDC_BUTTON_STOP, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_BUTTON_PLAY);
	m_LayoutManager.SetConstraint(IDC_BUTTON_STOP, OX_LMS_RIGHT, OX_LMT_POSITION, 30);


	//Constrain button pause
	m_LayoutManager.SetConstraint(IDC_BUTTON_PAUSE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_STATIC_FILTERS);
	m_LayoutManager.SetConstraint(IDC_BUTTON_PAUSE, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_BUTTON_STOP);
	m_LayoutManager.SetConstraint(IDC_BUTTON_PAUSE, OX_LMS_RIGHT, OX_LMT_POSITION, 45);

	//Constrain button framestep
	m_LayoutManager.SetConstraint(IDC_BUTTON_FRAMESTEP, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_STATIC_FILTERS);
	m_LayoutManager.SetConstraint(IDC_BUTTON_FRAMESTEP, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_BUTTON_PAUSE);
	m_LayoutManager.SetConstraint(IDC_BUTTON_FRAMESTEP, OX_LMS_RIGHT, OX_LMT_POSITION, 60);
	

	//Constrain button graphedit
	m_LayoutManager.SetConstraint(IDC_BUTTON_GRAPHEDIT, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_STATIC_FILTERS);
	m_LayoutManager.SetConstraint(IDC_BUTTON_GRAPHEDIT, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_BUTTON_FRAMESTEP);
	m_LayoutManager.SetConstraint(IDC_BUTTON_GRAPHEDIT, OX_LMS_RIGHT, OX_LMT_POSITION, 75); 

	//Constrain static volume
	m_LayoutManager.SetConstraint(IDC_STATIC_VOLUME, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -20, IDC_BUTTON_PROPPAGE);
	m_LayoutManager.SetConstraint(IDC_STATIC_VOLUME, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -5, IDC_SLIDER_VOLUME);
		
	//Constrain slider volume
	m_LayoutManager.SetConstraint(IDC_SLIDER_VOLUME, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -10, IDC_BUTTON_PROPPAGE);
	m_LayoutManager.SetConstraint(IDC_SLIDER_VOLUME, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	

	//Constrain static status
	m_LayoutManager.SetConstraint(IDC_STATUS, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_SLIDER_VOLUME);
	m_LayoutManager.SetConstraint(IDC_STATUS, OX_LMS_LEFT, OX_LMT_SAME, 1);
	

	//Constrain static image size
	m_LayoutManager.SetConstraint(IDC_STATIC_IMAGESIZE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_SLIDER_VOLUME);
	m_LayoutManager.SetConstraint(IDC_STATIC_IMAGESIZE, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	m_LayoutManager.SetConstraint(IDC_STATIC_IMAGESIZE, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_STATUS);	

	//Constrain static position
	m_LayoutManager.SetConstraint(IDC_STATIC_POSITION, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_STATUS);
	m_LayoutManager.SetConstraint(IDC_STATIC_POSITION, OX_LMS_LEFT, OX_LMT_SAME, 1);
	
	//Constrain check repeat
	m_LayoutManager.SetConstraint(IDC_CHECK_LOOP, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_STATIC_IMAGESIZE);
	m_LayoutManager.SetConstraint(IDC_CHECK_LOOP, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
	
	//Constrain check mute
	m_LayoutManager.SetConstraint(IDC_CHECK_MUTE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_STATIC_IMAGESIZE);
	m_LayoutManager.SetConstraint(IDC_CHECK_MUTE, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -10, IDC_CHECK_LOOP);
	
	// Constrain the slider bar
	m_LayoutManager.SetConstraint(IDC_SLIDER, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -2, IDC_STATIC_POSITION);
	m_LayoutManager.SetConstraint(IDC_SLIDER, OX_LMS_LEFT,  OX_LMT_SAME, 0);
	m_LayoutManager.SetConstraint(IDC_SLIDER, OX_LMS_RIGHT, OX_LMT_SAME, 0);


		// Constrain the movie screen
	m_LayoutManager.SetConstraint(IDC_MOVIE_SCREEN, OX_LMS_TOP, OX_LMT_SAME, 0);
	m_LayoutManager.SetConstraint(IDC_MOVIE_SCREEN, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_SLIDER);
	m_LayoutManager.SetConstraint(IDC_MOVIE_SCREEN, OX_LMS_LEFT,  OX_LMT_SAME, 0);
	m_LayoutManager.SetConstraint(IDC_MOVIE_SCREEN, OX_LMS_RIGHT, OX_LMT_SAME, 0);

  
	}

	
return retval;

}

BOOL CJukeBoxDlg::OnInitDialog()
{
    COXSizeDialogBar::OnInitDialog();

	
//Multilanguage manage
/*	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		CWnd::SetWindowText(_T("JukeBox"));
		GetDlgItem(IDC_CHECK_LOOP)->SetWindowText(_T("Repetir"));
		GetDlgItem(IDC_CHECK_MUTE)->SetWindowText(_T("Silencio"));
		GetDlgItem(IDC_STATUS)->SetWindowText(_T("<Estado>"));
		GetDlgItem(IDC_STATIC_FILTERS)->SetWindowText(_T("Filtros"));
		GetDlgItem(IDC_CHECK_FULLSCREEN)->SetWindowText(_T("Pantalla completa"));
		GetDlgItem(IDC_BUTTON_SET_MEDIADIR)->SetWindowText(_T("Examinar..."));
		GetDlgItem(IDC_BUTTON_PROPPAGE)->SetWindowText(_T("Propiedades filtro"));
		break;
	default:
		CWnd::SetWindowText(_T("JukeBox"));
		GetDlgItem(IDC_CHECK_LOOP)->SetWindowText(_T("Repeat"));
		GetDlgItem(IDC_CHECK_MUTE)->SetWindowText(_T("Mute"));
		GetDlgItem(IDC_STATUS)->SetWindowText(_T("<Status>"));
		GetDlgItem(IDC_STATIC_FILTERS)->SetWindowText(_T("Filters"));
		GetDlgItem(IDC_CHECK_FULLSCREEN)->SetWindowText(_T("Full screen"));
		GetDlgItem(IDC_BUTTON_SET_MEDIADIR)->SetWindowText(_T("Browse..."));
		GetDlgItem(IDC_BUTTON_PROPPAGE)->SetWindowText(_T("Filter properties"));
		break;
	}
	

	
//Icons manage
	hPlay= LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_JUKEBOX_PLAY));
	hPause= LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_JUKEBOX_PAUSE));
	hStop= LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_JUKEBOX_STOP));
	hFrameStep= LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_JUKEBOX_FRAMESTEP));
	hGraphEdit= LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_JUKEBOX_GRAPHEDIT));

	m_ButtonPlay.SetIcon(hPlay);
	m_ButtonPause.SetIcon(hPause);
	m_ButtonStop.SetIcon(hStop);
	m_ButtonFrameStep.SetIcon(hFrameStep);
	m_ButtonGraphEdit.SetIcon(hGraphEdit);
	
*/
	if(!InitLayoutManager())
	{
		MessageBox(_T("Failed to init layout manager!"));
	}
	
	UpdateData(FALSE);
		
    ////////////////////////////////////////////////////////////////////////
    //
    //  DirectShow-specific initialization code

    // Initialize COM
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);


    
    // Initialize DirectShow and query for needed interfaces
    HRESULT hr = InitDirectShow();
    if(FAILED(hr))
    {
        RetailOutput(TEXT("Failed to initialize DirectShow!  hr=0x%x\r\n"), hr);
        return FALSE;
    }

    // IMPORTANT
    // Since we're embedding video in a child window of a dialog,
     // we must set the WS_CLIPCHILDREN style to prevent the bounding
    // rectangle from drawing over our video frames.
    //
    // Neglecting to set this style can lead to situations when the video
    // is erased and replaced with black (or the default color of the 
    // bounding rectangle).
    m_Screen.ModifyStyle(0, WS_CLIPCHILDREN);

    // Initialize seeking trackbar range
    m_Seekbar.SetRange(0, 100, TRUE);
    m_Seekbar.SetTicFreq(5);

	//Current Volume
	g_lCurrentVolume = VOLUME_FULL;
	//Current Window size
	g_bFullscreen = FALSE;
	
	//Set the Slider
	m_VolumeSlider.SetRange(0, MINIMUM_VOLUME, TRUE);

	//SetMediadir();
	
	EnableToolTips();
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}





void CJukeBoxDlg::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	COXSizeDialogBar::OnUpdateCmdUI(pTarget,FALSE);
}	



void CJukeBoxDlg::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
{
	
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	m_LayoutManager.RedrawLayout();

}



LONG CJukeBoxDlg::GetDXMediaPath(TCHAR *szPath, DWORD dwPathSize)
{
    HKEY  hKey=0;
    DWORD dwType=0, dwValueSize=dwPathSize;

    // Open the appropriate registry key
    LONG lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                                _T("Software\\Microsoft\\DirectX SDK"),
                                0, KEY_READ, &hKey );
    if( ERROR_SUCCESS != lResult )
        return -1;

    // Start with DirectX9 SDK
    lResult = RegQueryValueEx( hKey, _T("DX9SDK Samples Path"), NULL,
                              &dwType, (BYTE*)szPath, &dwValueSize );

    if( ERROR_SUCCESS != lResult )
    {
        // Next try DirectX 8.1 SDK
        lResult = RegQueryValueEx( hKey, _T("DX81SDK Samples Path"), NULL,
                                  &dwType, (BYTE*)szPath, &dwValueSize );
        if( ERROR_SUCCESS != lResult )
        {
            // Finally, try DirectX 8.0 SDK
            lResult = RegQueryValueEx( hKey, _T("DX8SDK Samples Path"), NULL,
                                      &dwType, (BYTE*)szPath, &dwValueSize );
            if( ERROR_SUCCESS != lResult )
            {
                RegCloseKey( hKey );
                return -1;
            }
        }
    }

    RegCloseKey( hKey );

    // Now that we have the location of the installed SDK samples path,
    // append the name of the folder where media files are stored.
    // Make sure that the szPath string has enough space to hold the
    // full SDK samples path plus the "\Media\" string.
    if ((_tcslen(szPath) + STR_MEDIA_FOLDER_SIZE) < dwPathSize )
    {
        _tcscat( szPath, STR_MEDIA_FOLDER );
        return 0;
    }
    else
        return -1;
}


void CJukeBoxDlg::OnClose() 
{
    // Release DirectShow interfaces
    StopMedia();
    FreeDirectShow();
	
	g_bFullscreen = FALSE;

    // Release COM
    CoUninitialize();

    COXSizeDialogBar::OnClose();
}


void CJukeBoxDlg::OnDestroy() 
{
    FreeDirectShow();   

    COXSizeDialogBar::OnDestroy();
}


void CJukeBoxDlg::OnSelectFile() 
{
    
	
	HRESULT hr;
    TCHAR szFilename[MAX_PATH];

	// Read file name from Edit control
    m_EditMediaDir.GetWindowText(szFilename, MAX_PATH);


    // Remember current play state to restart playback
    int nCurrentState = g_psCurrent;

    // First release any existing interfaces
    ResetDirectShow();

    // Clear filter/pin/event information listboxes
    m_ListFilters.ResetContent();
    
    // Load the selected media file
    hr = PrepareMedia(szFilename);
    if (FAILED(hr))
    {
        // Error - disable play button and give feedback
        switch(languagePrimaryID)
		{
		case LANG_SPANISH:  //Spanish
			Say(TEXT("¡Fallo interpretación fichero!"));
			break;
		default:  //English
			Say(TEXT("File failed to render!"));
			break;
		}

        m_ButtonPlay.EnableWindow(FALSE);
        FreeDirectShow();
        MessageBeep(0);
        return;
    }
    else
    {
        m_ButtonPlay.EnableWindow(TRUE);
    }

    // Display useful information about this file
    DisplayFileInfo(szFilename);
    DisplayImageInfo();
    DisplayFileDuration();

    // Set up the seeking trackbar and read capabilities
    ConfigureSeekbar();

	// Read the current volume slider setting so that the current
    // global volume will be preserved
    m_VolumeSlider.EnableWindow(TRUE);
	HandleVolumeSlider(0);

    // Enumerate and display filters in graph
    hr = EnumFilters();

    // Select the first filter in the list to display pin info
    m_ListFilters.SetCurSel(0);
    OnSelchangeListFilters();

    // See if the renderer supports frame stepping on this file.
    // Enable/disable frame stepping button accordingly
    m_ButtonFrameStep.EnableWindow(CanStep());

    // If the user has asked to mute audio then we
    // need to mute this new clip before continuing.
    if (g_bGlobalMute)
        MuteAudio();

    // If we were running when the user changed selection,
    // start running the newly selected clip
    if (nCurrentState == State_Running)
    {
        OnPlay();
    }
    else
    {
        // Cue the first video frame
        OnStop();
    }
		
    
	
}






BOOL CJukeBoxDlg::IsWindowsMediaFile(LPTSTR lpszFile)
{
    TCHAR szFilename[MAX_PATH];

    // Copy the file name to a local string and convert to lowercase
    _tcsncpy(szFilename, lpszFile, NUMELMS(szFilename));
    szFilename[MAX_PATH-1] = 0;
    _tcslwr(szFilename);

    if (_tcsstr(szFilename, TEXT(".asf")) ||
        _tcsstr(szFilename, TEXT(".wma")) ||
        _tcsstr(szFilename, TEXT(".wmv")))
        return TRUE;
    else
        return FALSE;
}


HRESULT CJukeBoxDlg::PrepareMedia(LPTSTR lpszMovie)
{
    USES_CONVERSION;
    HRESULT hr = S_OK;

    switch(languagePrimaryID)
	{
	case LANG_SPANISH: //Spanish
		Say(TEXT("Cargando..."));
		break;
	default:  //English
		Say(TEXT("Loading..."));
		break;
	}

    // Is this a Windows Media file (ASF, WMA, WMV)?  If so, use the new
    // ASF Reader filter, which is faster and much better at seeking than
    // the default ASF Reader filter used by default with RenderFile.
    if (IsWindowsMediaFile(lpszMovie))
    {
        hr = RenderWMFile(T2W(lpszMovie));
        if (FAILED(hr)) {
            RetailOutput(TEXT("*** Failed(%08lx) to Render WM File(%s)!\r\n"),
                     hr, lpszMovie);
            return hr;
        }
    }
    else
    {
        // Allow DirectShow to create the FilterGraph for this media file
        hr = pGB->RenderFile(T2W(lpszMovie), NULL);
        if (FAILED(hr)) {
            RetailOutput(TEXT("*** Failed(%08lx) in RenderFile(%s)!\r\n"),
                     hr, lpszMovie);
            return hr;
        }
    }

    // Set the message drain of the video window to point to our main
    // application window.  If this is an audio-only or MIDI file, 
    // then put_MessageDrain will fail.
    hr = pVW->put_MessageDrain((OAHWND) m_hWnd);
    if (FAILED(hr))
    {
        g_bAudioOnly = TRUE;
    }

    // Have the graph signal event via window callbacks
    hr = pME->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);

    // Configure the video window
    if (!g_bAudioOnly)
    {
        // We'll manually set the video to be visible
        hr = pVW->put_Visible(OAFALSE);

        hr = pVW->put_WindowStyle(WS_CHILD);
        hr = pVW->put_Owner((OAHWND) m_Screen.GetSafeHwnd());

        // Place video window within the bounding rectangle
        CenterVideo();

        // Make the video window visible within the screen window.
        // If this is an audio-only file, then there won't be a video interface.
        hr = pVW->put_Visible(OATRUE);
        hr = pVW->SetWindowForeground(-1);
    }

    switch(languagePrimaryID)
	{
	case LANG_SPANISH:  //Spanish
		Say(TEXT("Preparado"));
		break;
	default: //English
		Say(TEXT("Ready"));
		break;
	}
    return hr;
}


HRESULT CJukeBoxDlg::RenderWMFile(LPCWSTR wFile)
{
    HRESULT hr=S_OK;
    IFileSourceFilter *pFS=NULL;
    IBaseFilter *pReader=NULL;

    // Load the improved ASF reader filter by CLSID
    hr = CreateFilter(CLSID_WMAsfReader, &pReader);
    if(FAILED(hr))
    {
        RetailOutput(TEXT("Failed to create WMAsfWriter filter!  hr=0x%x\n"), hr);
        return hr;
    }

    // Add the ASF reader filter to the graph.  For ASF/WMV/WMA content,
    // this filter is NOT the default and must be added explicitly.
    hr = pGB->AddFilter(pReader, L"ASF Reader");
    if(FAILED(hr))
    {
        RetailOutput(TEXT("Failed to add ASF reader filter to graph!  hr=0x%x\n"), hr);
        pReader->Release();
        return hr;
    }

//
// Windows Media 9 Series (code named 'Corona') no longer requires 
// a stub library.  If using WMF9, we don't need to provide a CKeyProvider
// implementation, and we don't need to link with the WMStub.lib library.
//
#ifndef TARGET_WMF9
    // Create the key provider that will be used to unlock the WM SDK
    JIF(AddKeyProvider(pGB));
#endif

    // Set its source filename
    JIF(pReader->QueryInterface(IID_IFileSourceFilter, (void **) &pFS));
    JIF(pFS->Load(wFile, NULL));
    pFS->Release();

    // Render the output pins of the ASF reader to build the
    // remainder of the graph automatically
    JIF(RenderOutputPins(pGB, pReader));

CLEANUP:
    // If there was a rendering error, make sure that the reader is released
    //
    // Otherwise, wince the graph is built and the filters are added to 
    // the graph, the WM ASF reader interface can be released.
    SAFE_RELEASE(pReader);

    return hr;
}


HRESULT CJukeBoxDlg::CreateFilter(REFCLSID clsid, IBaseFilter **ppFilter)
{
    HRESULT hr;

    hr = CoCreateInstance(clsid,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IBaseFilter,
        (void **) ppFilter);

    if(FAILED(hr))
    {
        RetailOutput(TEXT("CreateFilter: Failed to create filter!  hr=0x%x\n"), hr);
        *ppFilter = NULL;
        return hr;
    }

    return S_OK;
}


HRESULT CJukeBoxDlg::RenderOutputPins(IGraphBuilder *pGB, IBaseFilter *pFilter)
{
    HRESULT         hr = S_OK;
    IEnumPins *     pEnumPin = NULL;
    IPin *          pConnectedPin = NULL, * pPin;
    PIN_DIRECTION   PinDirection;
    ULONG           ulFetched;

    // Enumerate all pins on the filter
    hr = pFilter->EnumPins( &pEnumPin );

    if(SUCCEEDED(hr))
    {
        // Step through every pin, looking for the output pins
        while (S_OK == (hr = pEnumPin->Next( 1L, &pPin, &ulFetched)))
        {
            // Is this pin connected?  We're not interested in connected pins.
            hr = pPin->ConnectedTo(&pConnectedPin);
            if (pConnectedPin)
            {
                pConnectedPin->Release();
                pConnectedPin = NULL;
            }

            // If this pin is not connected, render it.
            if (VFW_E_NOT_CONNECTED == hr)
            {
                hr = pPin->QueryDirection( &PinDirection );
                if ( ( S_OK == hr ) && ( PinDirection == PINDIR_OUTPUT ) )
                {
                    hr = pGB->Render(pPin);
                }
            }
            pPin->Release();

            // If there was an error, stop enumerating
            if (FAILED(hr))                      
                break;
        }
    }

    // Release pin enumerator
    pEnumPin->Release();
    return hr;
}


//
// Windows Media 9 Series (code named 'Corona') no longer requires 
// a stub library.  If using WMF9, we don't need to provide a CKeyProvider
// implementation, and we don't need to link with the WMStub.lib library.
//
#ifndef TARGET_WMF9

HRESULT CJukeBoxDlg::AddKeyProvider(IGraphBuilder *pGraph)
{
    HRESULT hr;

    // Instantiate the key provider class, and AddRef it
    // so that COM doesn't try to free our static object.
    prov.AddRef();  // Don't let COM try to free our static object.

    // Give the graph an IObjectWithSite pointer to us for callbacks & QueryService.
    IObjectWithSite* pObjectWithSite = NULL;

    hr = pGraph->QueryInterface(IID_IObjectWithSite, (void**)&pObjectWithSite);
    if (SUCCEEDED(hr))
    {
        // Use the IObjectWithSite pointer to specify our key provider object.
        // The filter graph manager will use this pointer to call
        // QueryService to do the unlocking.
        // If the unlocking succeeds, then we can build our graph.
            
        hr = pObjectWithSite->SetSite((IUnknown *) (IServiceProvider *) &prov);
        pObjectWithSite->Release();
    }

    return hr;
}

#endif


//
//  Displays a text string in a status line near the bottom of the dialog
//
void CJukeBoxDlg::Say(LPTSTR szText)
{
    m_Status.SetWindowText(szText);
}


void CJukeBoxDlg::OnPause() 
{  
    LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	if (g_psCurrent == State_Paused)
    {
        RunMedia();
        StartSeekTimer();
		
		switch( dwLanguageID )
		{
		case LANG_SPANISH:
			Say(TEXT("Reproduciendo..."));
			break;
		default:
			Say(TEXT("Running..."));
			break;
		}
    }
    else
    {
        StopSeekTimer();
        PauseMedia();
        
		dwLanguageID = GetSystemLanguagePrimaryID();
		switch( dwLanguageID)
		{
		case LANG_SPANISH:
			Say(TEXT("Pausado"));
			break;
		default:
			Say(TEXT("Paused"));
			break;
		}
    }
}


void CJukeBoxDlg::OnPlay() 
{
    RunMedia();
    StartSeekTimer();
    
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
		switch( dwLanguageID )
		{
		case LANG_SPANISH:
			Say(TEXT("Reproduciendo..."));
			break;
		default:
			Say(TEXT("Running..."));
			break;
		}
}


void CJukeBoxDlg::OnStop() 
{
    HRESULT hr;

    if (!pMC || !pMS)
        return;

    // Stop playback immediately with IMediaControl::Stop().
    StopSeekTimer();
    StopMedia();

    // Wait for the stop to propagate to all filters
    OAFilterState fs;
    hr = pMC->GetState(500, &fs);
    if (FAILED(hr))
    {
        RetailOutput(TEXT("Failed to read graph state!  hr=0x%x\r\n"), hr);
    }

    // Reset to beginning of media clip
    LONGLONG pos=0;
    hr = pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                           NULL, AM_SEEKING_NoPositioning);
    if (FAILED(hr))
    {
        RetailOutput(TEXT("Failed to seek to beginning of media!  hr=0x%x\r\n"), hr);
    }
  
    // Display the first frame of the media clip, if it contains video.
    // StopWhenReady() pauses all filters internally (which allows the video
    // renderer to queue and display the first video frame), after which
    // it sets the filters to the stopped state.  This enables easy preview
    // of the video's poster frame.
    hr = pMC->StopWhenReady();
    if (FAILED(hr))
    {
        RetailOutput(TEXT("Failed in StopWhenReady!  hr=0x%x\r\n"), hr);
    }

    LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	switch (dwLanguageID)
	{
	case LANG_SPANISH:
		Say(TEXT("Detenido"));
		break;
	default:
		Say(TEXT("Stopped"));
		break;
	}

    // Reset slider bar and position label back to zero
    ReadMediaPosition();
}


HRESULT CJukeBoxDlg::InitDirectShow(void)
{
    HRESULT hr = S_OK;

    g_bAudioOnly = FALSE;

    // Zero interfaces (sanity check)
    pVW = NULL;
    pBV = NULL;

    JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, 
                        (void **)&pGB));
    JIF(pGB->QueryInterface(IID_IMediaControl,  (void **)&pMC));
    JIF(pGB->QueryInterface(IID_IMediaSeeking,  (void **)&pMS));
    JIF(pGB->QueryInterface(IID_IBasicVideo,    (void **)&pBV));
    JIF(pGB->QueryInterface(IID_IVideoWindow,   (void **)&pVW));
    JIF(pGB->QueryInterface(IID_IMediaEventEx,  (void **)&pME));
	JIF(pGB->QueryInterface(IID_IBasicAudio,    (void **)&pBA));

    return S_OK;

CLEANUP:
    FreeDirectShow();
    return(hr);
}


HRESULT CJukeBoxDlg::FreeDirectShow(void)
{
    HRESULT hr=S_OK;

    StopSeekTimer();
    StopMedia();

	 // Remember the current volume slider position so that the
    // same volume level can be applied to the next clip
    HandleVolumeSlider(0);

    // Disable event callbacks
    if (pME)
        hr = pME->SetNotifyWindow((OAHWND)NULL, 0, 0);

    // Hide video window and remove owner.  This is not necessary here,
    // since we are about to destroy the filter graph, but it is included
    // for demonstration purposes.  Remember to hide the video window and
    // clear its owner when destroying a window that plays video.
    if(pVW)
    {
        hr = pVW->put_Visible(OAFALSE);
        hr = pVW->put_Owner(NULL);
    }

    SAFE_RELEASE(pMC);
    SAFE_RELEASE(pMS);
    SAFE_RELEASE(pVW);
    SAFE_RELEASE(pBV);
    SAFE_RELEASE(pME);
    SAFE_RELEASE(pGB);
	SAFE_RELEASE(pBA);


    return hr;
}


void CJukeBoxDlg::ResetDirectShow(void)
{
    // Destroy the current filter graph its filters.
    FreeDirectShow();

    // Reinitialize graph builder and query for interfaces
    InitDirectShow();

}

void CJukeBoxDlg::CenterVideo(void)
{
    LONG width, height;
    HRESULT hr;

    if ((g_bAudioOnly) || (!pVW))
        return;

    // Read coordinates of video container window
    RECT rc;
    m_Screen.GetClientRect(&rc);
    width  =  rc.right - rc.left;
    height = rc.bottom - rc.top;

    // Ignore the video's original size and stretch to fit bounding rectangle
    hr = pVW->SetWindowPosition(rc.left, rc.top, width, height);
    if (FAILED(hr))
    {
        RetailOutput(TEXT("Failed to set window position!  hr=0x%x\r\n"), hr);
        return;
    }
}


LRESULT CJukeBoxDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    // Field notifications from the DirectShow filter graph manager
    // and those posted by the application
    
	switch (message)
    {
        case WM_GRAPHNOTIFY:
            HandleGraphEvent();
            break;

        case WM_HSCROLL:
            HandleTrackbar(LOWORD(wParam));
            break;

        case WM_VSCROLL:
            HandleVolumeSlider(LOWORD(wParam));
            break;

		case WM_PLAYFILE:
            PlaySelectedFile();
	       break;
		
		case WM_KEYDOWN:
			switch(LOWORD(wParam))
            {
                    
				case 'P':
                    OnPlay();
                    break;

                case 'S':
                    OnStop();
                    break;
				
				case 'U':
                    OnPause();
                    break;

                case 'L':
                    OnCheckLoop();
                    break;
				
				case 'M':
                    OnCheckMute();
                    break;

				case VK_ESCAPE:
					if (g_bFullScreen)
						OnCheckFullScreen();
					else
						OnClose();
				break;

            }
        break;
		
		case WM_CLOSE:
            FreeDirectShow();
        break;
    }

    // Pass along this message to the video window, which exists as a child
    // of the m_Screen window.  This method should be used by windows that 
    // make a renderer window a child window. It forwards significant messages 
    // to the child window that the child window would not otherwise receive. 
    if (pVW)
    {
        pVW->NotifyOwnerMessage((LONG_PTR) m_hWnd, message, wParam, lParam);
    }

    return COXSizeDialogBar::WindowProc(message, wParam, lParam);




}


HRESULT CJukeBoxDlg::HandleGraphEvent(void)
{
    LONG evCode, evParam1, evParam2;
    HRESULT hr=S_OK;

    // Since we may have a scenario where we're shutting down the application,
    // but events are still being generated, make sure that the event
    // interface is still valid before using it.  It's possible that
    // the interface could be freed during shutdown but later referenced in
    // this callback before the app completely exits.
    if (!pME)
        return S_OK;
    
    while(SUCCEEDED(pME->GetEvent(&evCode, (LONG_PTR *) &evParam1, 
                    (LONG_PTR *) &evParam2, 0)))
    {
        // Spin through the events
        if(EC_COMPLETE == evCode)
        {
            // If looping, reset to beginning and continue playing
            if (g_bLooping)
            {
                LONGLONG pos=0;

                // Reset to first frame of movie
                hr = pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                                       NULL, AM_SEEKING_NoPositioning);
                if (FAILED(hr))
                {
                    // Some custom filters (like the Windows CE MIDI filter) 
                    // may not implement seeking interfaces (IMediaSeeking)
                    // to allow seeking to the start.  In that case, just stop 
                    // and restart for the same effect.  This should not be
                    // necessary in most cases.
                    StopMedia();
                    RunMedia();
                }
            }
            else
            {
                // Stop playback and display first frame of movie
                OnStop();
            }
        }

        // Free memory associated with this event
        hr = pME->FreeEventParams(evCode, evParam1, evParam2);

        
    }

    return hr;
}


void CJukeBoxDlg::OnCheckMute() 
{
    // Remember global mute status for next file.  When you destroy a
    // filtergraph, you lose all of its audio settings.  Therefore, when
    // we create the next graph, we will mute the audio before running
    // the graph if this global variable is set.
    g_bGlobalMute ^= 1; 

    if (g_bGlobalMute)
	{
        MuteAudio();
		m_VolumeSlider.EnableWindow(FALSE);
	}
    else
	{
        ResumeAudio();
		if (pBA)
		m_VolumeSlider.EnableWindow(TRUE);
	}
}


void CJukeBoxDlg::OnCheckLoop() 
{
    g_bLooping ^= 1;

}

void CJukeBoxDlg::OnButtonSetMediadir() 
{
    
	CFileDialog dlgFile(TRUE);
    CString title;
    CString strFilter, strDefault, strFilename;
	
	VERIFY(title.LoadString(AFX_IDS_OPENFILE));

    // Initialize the file extensions and descriptions
    strFilter += "Media Files (*.avi, *.mpg, *.wav, *.mid, *.mpeg)\0";
    strFilter += (TCHAR)'\0';
    strFilter += _T("*.avi;*.mpg;*.wav;*.mid;*.mpeg\0");
    strFilter += (TCHAR)'\0';
    dlgFile.m_ofn.nMaxCustFilter++;

    CString allFilter;
    VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));

    // Append the "*.*" all files filter
    strFilter += allFilter;
    strFilter += (TCHAR)'\0';     // next string
    strFilter += _T("*.*\0");
    strFilter += (TCHAR)'\0\0';   // last string
    dlgFile.m_ofn.nMaxCustFilter++;

    dlgFile.m_ofn.lpstrFilter = strFilter;
    dlgFile.m_ofn.lpstrTitle  = title;
    dlgFile.m_ofn.lpstrFile   = strFilename.GetBuffer(_MAX_PATH);

    // Display the file open dialog
    INT_PTR nResult = dlgFile.DoModal();

    // If a file was selected, update the main dialog
    if (nResult == IDOK)
    {
        m_EditMediaDir.SetWindowText(strFilename);

        // Render this file and show the first video frame, if present
        OnSelectFile();
    }

    strFilename.ReleaseBuffer();
	
	m_CheckFullScreen.EnableWindow(true);
	// Don't bother with full-screen for audio-only files
	if ((g_bAudioOnly) || (!pVW))
	{
        m_CheckFullScreen.EnableWindow(false);
		return;
	}


}



void CJukeBoxDlg::PlaySelectedFile() 
{
    OnPlay();
}



HRESULT CJukeBoxDlg::EnumFilters (void) 
{
    HRESULT hr;
    IEnumFilters *pEnum = NULL;
    IBaseFilter *pFilter = NULL;
    ULONG cFetched;

    // Clear filters list box
    m_ListFilters.ResetContent();
    
    // Get filter enumerator
    hr = pGB->EnumFilters(&pEnum);
    if (FAILED(hr))
    {
        m_ListFilters.AddString(TEXT("<ERROR>"));
        return hr;
    }

    // Enumerate all filters in the graph
    while(pEnum->Next(1, &pFilter, &cFetched) == S_OK)
    {
        FILTER_INFO FilterInfo;
        TCHAR szName[256];
        
        hr = pFilter->QueryFilterInfo(&FilterInfo);
        if (FAILED(hr))
        {
            m_ListFilters.AddString(TEXT("<ERROR>"));
        }
        else
        {
            // Add the filter name to the filters listbox
            USES_CONVERSION;

            lstrcpy(szName, W2T(FilterInfo.achName));
            m_ListFilters.AddString(szName);

            FilterInfo.pGraph->Release();
        }       
        pFilter->Release();
    }
    pEnum->Release();

    return hr;
}


//
// The GraphBuilder interface provides a FindFilterByName() method,
// which provides similar functionality to the method below.
// This local method is provided for educational purposes.
//
IBaseFilter *CJukeBoxDlg::FindFilterFromName(LPTSTR szNameToFind)
{
    USES_CONVERSION;

    HRESULT hr;
    IEnumFilters *pEnum = NULL;
    IBaseFilter *pFilter = NULL;
    ULONG cFetched;
    BOOL bFound = FALSE;

    // Get filter enumerator
    hr = pGB->EnumFilters(&pEnum);
    if (FAILED(hr))
        return NULL;

    // Enumerate all filters in the graph
    while((pEnum->Next(1, &pFilter, &cFetched) == S_OK) && (!bFound))
    {
        FILTER_INFO FilterInfo;
        TCHAR szName[256];
        
        hr = pFilter->QueryFilterInfo(&FilterInfo);
        if (FAILED(hr))
        {
            pFilter->Release();
            pEnum->Release();
            return NULL;
        }

        // Compare this filter's name with the one we want
        lstrcpy(szName, W2T(FilterInfo.achName));
        if (! lstrcmp(szName, szNameToFind))
        {
            bFound = TRUE;
        }

        FilterInfo.pGraph->Release();

        // If we found the right filter, don't release its interface.
        // The caller will use it and release it later.
        if (!bFound)
            pFilter->Release();
        else
            break;
    }
    pEnum->Release();

    return (bFound ? pFilter : NULL);
}


HRESULT CJukeBoxDlg::EnumPins(IBaseFilter *pFilter, PIN_DIRECTION PinDir,
                              CListBox& Listbox)
{
    HRESULT hr;
    IEnumPins  *pEnum = NULL;
    IPin *pPin = NULL;

    // Clear the specified listbox (input or output)
    Listbox.ResetContent();

    // Get pin enumerator
    hr = pFilter->EnumPins(&pEnum);
    if (FAILED(hr))
    {
        Listbox.AddString(TEXT("<ERROR>"));
        return hr;
    }

    // Enumerate all pins on this filter
    while(pEnum->Next(1, &pPin, 0) == S_OK)
    {
        PIN_DIRECTION PinDirThis;

        hr = pPin->QueryDirection(&PinDirThis);
        if (FAILED(hr))
        {
            Listbox.AddString(TEXT("<ERROR>"));
            pPin->Release();
            continue;
        }

        // Does the pin's direction match the requested direction?
        if (PinDir == PinDirThis)
        {
            PIN_INFO pininfo={0};

            // Direction matches, so add pin name to listbox
            hr = pPin->QueryPinInfo(&pininfo);
            if (SUCCEEDED(hr))
            {
                CString str(pininfo.achName);
                Listbox.AddString(str);
            }

            // The pininfo structure contains a reference to an IBaseFilter,
            // so you must release its reference to prevent resource a leak.
            pininfo.pFilter->Release();
        }
        pPin->Release();
    }
    pEnum->Release();

    return hr;
}


void CJukeBoxDlg::OnSelchangeListFilters() 
{
    
    IBaseFilter *pFilter = NULL;
    TCHAR szNameToFind[128];

    // Read the current filter name from the list box
    int nCurSel = m_ListFilters.GetCurSel();
    m_ListFilters.GetText(nCurSel, szNameToFind);

    // Read the current list box name and find it in the graph
    pFilter = FindFilterFromName(szNameToFind);
    if (!pFilter)
        return;

    
    // Find out if this filter supports a property page
    if (SupportsPropertyPage(pFilter))
        m_ButtonProperties.EnableWindow(TRUE);
    else
        m_ButtonProperties.EnableWindow(FALSE);
    
    // Must release the filter interface returned from FindFilterByName()
    pFilter->Release();
}


BOOL CJukeBoxDlg::DisplayImageInfo(void)
{
    HRESULT hr;
    long lWidth, lHeight;
    
    // If this file has no video component, clear the text field
    if ((!pBV) || (g_bAudioOnly))
    {
        m_StrImageSize.SetWindowText(TEXT("\0"));
        return FALSE;
    }

    hr = pBV->GetVideoSize(&lWidth, &lHeight);
    if (SUCCEEDED(hr))
    {
        TCHAR szSize[64];
		switch(languagePrimaryID)
		{
		case LANG_SPANISH: //Spanish
			wsprintf(szSize, TEXT("Imagen: %d x %d\0"), lWidth, lHeight);
			break;
		default: //English
			wsprintf(szSize, TEXT("Image: %d x %d\0"), lWidth, lHeight);
			break;
		}
        
		m_StrImageSize.SetWindowText(szSize);
    }

    return TRUE;
}


BOOL CJukeBoxDlg::DisplayFileInfo(LPTSTR szFile)
{
    HANDLE hFile;
    LONGLONG llSize=0;
    DWORD dwSizeLow=0, dwSizeHigh=0;
    TCHAR szScrap[64];

    // Open the specified file to read size and date information
    hFile = CreateFile(szFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,
                       (DWORD) 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        RetailOutput(TEXT("*** Failed(0x%x) to open file (to read size)!\r\n"),
                     GetLastError());
        return FALSE;
    }

    dwSizeLow = GetFileSize(hFile, &dwSizeHigh);
    if ((dwSizeLow == 0xFFFFFFFF) && (GetLastError() != NO_ERROR))
    {
        RetailOutput(TEXT("*** Error(0x%x) reading file size!\r\n"),
                     GetLastError());
        CloseHandle(hFile);
        return FALSE;
    }

    // Large files will also use the upper DWORD to report size.
    // Add them together for the true size if necessary.
    if (dwSizeHigh)
        llSize = (dwSizeHigh << 16) + dwSizeLow;
    else
        llSize = dwSizeLow;

    // Read date information
    BY_HANDLE_FILE_INFORMATION fi;
    if (GetFileInformationByHandle(hFile, &fi))
    {
        CTime time(fi.ftLastWriteTime);
		
		switch(languagePrimaryID)
		{
		case LANG_SPANISH: //Spanish
			wsprintf(szScrap, TEXT("Fecha fichero: %02d/%02d/%d\0"), 
                 time.GetMonth(), time.GetDay(), time.GetYear());
			break;
		default:  //English
			wsprintf(szScrap, TEXT("File date: %02d/%02d/%d\0"), 
                 time.GetMonth(), time.GetDay(), time.GetYear());
			break;
		}
		
		m_StrFileDate.SetWindowText(szScrap);
    
	}

    CloseHandle(hFile);

    // Update size/date windows
	switch(languagePrimaryID)
	{
	case LANG_SPANISH: //Spanish
		wsprintf(szScrap, TEXT("Tamaño: %d bytes\0"), dwSizeLow);
		break;
	default:  //English
		wsprintf(szScrap, TEXT("Size: %d bytes\0"), dwSizeLow);
		break;
	}
    
	m_StrFileSize.SetWindowText(szScrap);

    return TRUE;
}


HRESULT CJukeBoxDlg::DisplayFileDuration(void)
{
    HRESULT hr;

    if (!pMS)
        return E_NOINTERFACE;

    // Initialize the display in case we can't read the duration
    m_StrDuration.SetWindowText(TEXT("<00:00.000>"));

    // Is media time supported for this file?
    if (S_OK != pMS->IsFormatSupported(&TIME_FORMAT_MEDIA_TIME))
        return E_NOINTERFACE;

    // Read the time format to restore later
    GUID guidOriginalFormat;
    hr = pMS->GetTimeFormat(&guidOriginalFormat);
    if (FAILED(hr))
        return hr;

    // Ensure media time format for easy display
    hr = pMS->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
    if (FAILED(hr))
        return hr;

    // Read the file's duration
    LONGLONG llDuration;
    hr = pMS->GetDuration(&llDuration);
    if (FAILED(hr))
        return hr;

    // Return to the original format
    if (guidOriginalFormat != TIME_FORMAT_MEDIA_TIME)
    {
        hr = pMS->SetTimeFormat(&guidOriginalFormat);
        if (FAILED(hr))
            return hr;
    }

    // Convert the LONGLONG duration into human-readable format
    unsigned long nTotalMS = (unsigned long) llDuration / 10000; // 100ns -> ms
    int nMS = nTotalMS % 1000;
    int nSeconds = nTotalMS / 1000;
    int nMinutes = nSeconds / 60;
    nSeconds %= 60;

    // Update the display
    TCHAR szDuration[24];
    wsprintf(szDuration, _T("%02dm:%02d.%03ds\0"), nMinutes, nSeconds, nMS);
    m_StrDuration.SetWindowText(szDuration);

    return hr;
}


BOOL CJukeBoxDlg::SupportsPropertyPage(IBaseFilter *pFilter) 
{
    HRESULT hr;
    ISpecifyPropertyPages *pSpecify;

    // Discover if this filter contains a property page
    hr = pFilter->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pSpecify);
    if (SUCCEEDED(hr)) 
    {
        pSpecify->Release();
        return TRUE;
    }
    else
        return FALSE;
}


void CJukeBoxDlg::OnButtonProppage() 
{
    HRESULT hr;
    IBaseFilter *pFilter = NULL;
    TCHAR szNameToFind[128];
    ISpecifyPropertyPages *pSpecify;

    // Read the current filter name from the list box
    int nCurSel = m_ListFilters.GetCurSel();
    m_ListFilters.GetText(nCurSel, szNameToFind);

    // Read the current list box name and find it in the graph
    pFilter = FindFilterFromName(szNameToFind);
    if (!pFilter)
        return;

    // Discover if this filter contains a property page
    hr = pFilter->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pSpecify);
    if (SUCCEEDED(hr)) 
    {
        do 
        {
            FILTER_INFO FilterInfo;
            hr = pFilter->QueryFilterInfo(&FilterInfo);
            if (FAILED(hr))
                break;

            CAUUID caGUID;
            hr = pSpecify->GetPages(&caGUID);
            if (FAILED(hr))
                break;

            pSpecify->Release();
        
            // Display the filter's property page
            OleCreatePropertyFrame(
                m_hWnd,                 // Parent window
                0,                      // x (Reserved)
                0,                      // y (Reserved)
                FilterInfo.achName,     // Caption for the dialog box
                1,                      // Number of filters
                (IUnknown **)&pFilter,  // Pointer to the filter 
                caGUID.cElems,          // Number of property pages
                caGUID.pElems,          // Pointer to property page CLSIDs
                0,                      // Locale identifier
                0,                      // Reserved
                NULL                    // Reserved
            );
            CoTaskMemFree(caGUID.pElems);
            FilterInfo.pGraph->Release(); 

        } while(0);
    }

    pFilter->Release();
}


void CJukeBoxDlg::OnDblclkListFilters() 
{
    OnButtonProppage();
}


void CJukeBoxDlg::OnButtonFramestep() 
{
    StepFrame();
}


//
// Some hardware decoders and video renderers support stepping media
// frame by frame with the IVideoFrameStep interface.  See the interface
// documentation for more details on frame stepping.
//
BOOL CJukeBoxDlg::CanStep(void)
{
    HRESULT hr;
    IVideoFrameStep* pFS;

    hr = pGB->QueryInterface(__uuidof(IVideoFrameStep), (PVOID *)&pFS);
    if (FAILED(hr))
        return FALSE;

    // Check if this decoder can step
    hr = pFS->CanStep(0L, NULL); 

    pFS->Release();

    if (hr == S_OK)
        return TRUE;
    else
        return FALSE;
}


HRESULT CJukeBoxDlg::StepFrame(void)
{
    // Get the Frame Stepping Interface
    HRESULT hr;
    IVideoFrameStep* pFS;

    hr = pGB->QueryInterface(__uuidof(IVideoFrameStep), (PVOID *)&pFS);
    if (FAILED(hr))
        return hr;

    // The graph must be paused for frame stepping to work
    if (g_psCurrent != State_Paused)
        OnPause();

    // Step one frame
    hr = pFS->Step(1, NULL); 
    pFS->Release();

    // Since the media position has changed slightly, update the
    // slider bar and position label.
    ReadMediaPosition();
    return hr;
}


void CJukeBoxDlg::ConfigureSeekbar()
{
    // Disable seekbar for new file and reset tracker/position label
    m_Seekbar.SetPos(0);
	
	//Verify the system language configuration
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch (dwLanguageID)
	{
	case LANG_SPANISH :
		m_StrPosition.SetWindowText(TEXT("Posición: 00m:00s\0"));
		break;
    default :
		m_StrPosition.SetWindowText(TEXT("Position: 00m:00s\0"));
		break;
	}
    
	g_rtTotalTime=0;

    // If we can't read the file's duration, disable the seek bar
    if (pMS && SUCCEEDED(pMS->GetDuration(&g_rtTotalTime)))
        m_Seekbar.EnableWindow(TRUE);
    else
        m_Seekbar.EnableWindow(FALSE);
}


void CJukeBoxDlg::StartSeekTimer() 
{
    // Cancel any pending timer event
    StopSeekTimer();

    // Create a new timer
    g_wTimerID = SetTimer(TIMERID, TICKLEN, NULL);
}

void CJukeBoxDlg::StopSeekTimer() 
{
    // Cancel the timer
    if(g_wTimerID)        
    {                
        KillTimer(g_wTimerID);
        g_wTimerID = 0;
    }
}

void CJukeBoxDlg::OnTimer(UINT nIDEvent) 
{
    ReadMediaPosition();

    COXSizeDialogBar::OnTimer(nIDEvent);
}


void CJukeBoxDlg::ReadMediaPosition()
{
    HRESULT hr;
    REFERENCE_TIME rtNow;

    if (!pMS)
        return;

    // Read the current stream position
    hr = pMS->GetCurrentPosition(&rtNow);
    if (FAILED(hr))
        return;

    // Convert position into a percentage value and update slider position
    if (g_rtTotalTime != 0)
    {
        long lTick = (long)((rtNow * 100) / g_rtTotalTime);
        m_Seekbar.SetPos(lTick);
    }
    else
        m_Seekbar.SetPos(0);
    
    // Update the 'current position' string on the main dialog
    UpdatePosition(rtNow);
}


void CJukeBoxDlg::UpdatePosition(REFERENCE_TIME rtNow) 
{
    HRESULT hr;

    if (!pMS)
        return;

    // If no reference time was passed in, read the current position
    if (rtNow == 0)
    {
        // Read the current stream position
        hr = pMS->GetCurrentPosition(&rtNow);
        if (FAILED(hr))
            return;
    }

    // Convert the LONGLONG duration into human-readable format
    unsigned long nTotalMS = (unsigned long) rtNow / 10000; // 100ns -> ms
    int nSeconds = nTotalMS / 1000;
    int nMinutes = nSeconds / 60;
    nSeconds %= 60;

    // Update the display
    TCHAR szPosition[24], szCurrentString[24];

	//Verify the system language configuration
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch (dwLanguageID)
	{
	case LANG_SPANISH :
		wsprintf(szPosition, _T("Posición: %02dm:%02ds\0"), nMinutes, nSeconds);
		break;
    default :
		wsprintf(szPosition, _T("Position: %02dm:%02ds\0"), nMinutes, nSeconds);
		break;
	}
    

    // Read current string and compare to the new string.  To prevent flicker,
    // don't update this label unless the string has changed.
    m_StrPosition.GetWindowText(szCurrentString, 24);

    if (_tcscmp(szCurrentString, szPosition))
        m_StrPosition.SetWindowText(szPosition);
}


void CJukeBoxDlg::HandleVolumeSlider(WPARAM wReq)
{
    HRESULT hr=S_OK;
    long lVolume;

    // Disregard ENDSCROLL messages, which are redundant
    if ((!pBA) || (wReq == SB_ENDSCROLL))
        return;

    // Since the IBasicAudio interface adjusts volume on a logarithmic
    // scale from -10000 to 0, volumes below -4000 sound like silence.
    // Therefore, the slider covers a smaller range.
    int nPosition = m_VolumeSlider.GetPos();

    // Since slider goes from MINIMUM_VOLUME to 0, use the negative value
    lVolume = -1 * nPosition;

    // Save current volume to global variable for use with Mute/Resume audio
    g_lCurrentVolume = lVolume;

    // Set new volume
    hr = pBA->put_Volume(lVolume);
}


void CJukeBoxDlg::HandleTrackbar(WPARAM wReq)
{
    HRESULT hr;
    static OAFilterState state;
    static BOOL bStartOfScroll = TRUE;

    if ((!pMS) || (!pMC))
        return;

    // If the file is not seekable, the trackbar is disabled. 
    DWORD dwPosition = m_Seekbar.GetPos();

    // Pause when the scroll action begins.
    if (bStartOfScroll) 
    {       
        hr = pMC->GetState(10, &state);
        bStartOfScroll = FALSE;
        hr = pMC->Pause();
    }
    
    // Update the position continuously.
    REFERENCE_TIME rtNew = (g_rtTotalTime * dwPosition) / 100;

    hr = pMS->SetPositions(&rtNew, AM_SEEKING_AbsolutePositioning,
                           NULL,   AM_SEEKING_NoPositioning);

    // Restore the state at the end.
    if (wReq == TB_ENDTRACK)
    {
        if (state == State_Stopped)
            hr = pMC->Stop();
        else if (state == State_Running) 
            hr = pMC->Run();

        bStartOfScroll = TRUE;
    }

    // Update the 'current position' string on the main dialog.
    UpdatePosition(rtNew);
}


LONG CJukeBoxDlg::GetGraphEditPath(TCHAR *szPath)
{
    HKEY  hKey;
    DWORD dwType, dwSize = MAX_PATH;

    // Open the appropriate registry key
    LONG lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                                _T("Software\\Microsoft\\Shared Tools\\Graphedit"),
                                0, KEY_READ, &hKey );
    if( ERROR_SUCCESS != lResult )
        return -1;

    // Read the full path (including .exe name) for the GraphEdit tool
    lResult = RegQueryValueEx( hKey, _T("Path"), NULL,
                              &dwType, (BYTE*)szPath, &dwSize );
    RegCloseKey( hKey );

    if( ERROR_SUCCESS != lResult )
        return -1;

    return 0;
}


void CJukeBoxDlg::OnButtonGraphedit() 
{
    TCHAR szFilename[128], szFile[MAX_PATH];

    // Read file name from Edit control
    m_EditMediaDir.GetWindowText(szFilename, MAX_PATH);

    // Build the full file name with path.  The path will already have
    // a '\' appended to the end.
    wsprintf(szFile, szFilename);

    // Launch GraphEdit for the selected file
    //    
    // First look for a registry key containing its full path
    TCHAR szPath[MAX_PATH];

    LONG lResult = GetGraphEditPath(szPath);

    // If the DirectX SDK is not installed, just look for GraphEdit
    // anywhere in the system path.
    if (lResult != 0)
    {
        _tcscpy(szPath, TEXT("graphedt\0"));
    }

    // Lauch GraphEdit using either the full tool path or just its name                               
    HINSTANCE rc = ShellExecute(m_hWnd, TEXT("open\0"), szPath, 
                                szFile, NULL, SW_SHOWNORMAL);

    if (rc < (HINSTANCE) 32)
    {
        // Failed to start the app
        if ((rc == (HINSTANCE) ERROR_FILE_NOT_FOUND) || 
            (rc == (HINSTANCE) ERROR_PATH_NOT_FOUND))
        {
            LANGID dwLanguageID = GetSystemLanguagePrimaryID();
			
			switch(dwLanguageID)
			{
			case LANG_SPANISH:
				MessageBox(TEXT("No se puede encontrar la aplicación GraphEdit.\r\n\r\n")
                       TEXT("Porfavor copie graphedt.exe al directorio donde apunta su ruta."), 
                       TEXT("No se encontró GraphEdit"));
			break;
			default:
				MessageBox(TEXT("Couldn't find the GraphEdit application.\r\n\r\n")
                       TEXT("Please copy graphedt.exe to a directory on your path."), 
                       TEXT("Can't find GraphEdit"));
			break;
			}


        }
    }
}


BOOL CJukeBoxDlg::OnEraseBkgnd(CDC *pDC)
{
    // Intercept background erasing for the movie window, since the
    // video renderer will keep the screen painted.  Without this code,
    // your video window might get painted over with gray (the default
    // background brush) when it is obscured by another window and redrawn.
    CRect rc;

    // Get the bounding rectangle for the movie screen
    m_Screen.GetWindowRect(&rc);
    ScreenToClient(&rc);

    // Exclude the clipping region occupied by our movie screen
    pDC->ExcludeClipRect(&rc);
    
    // Erase the remainder of the dialog as usual
    return COXSizeDialogBar::OnEraseBkgnd(pDC);
}








void CJukeBoxDlg::OnCheckFullScreen() 
{
	ToggleFullScreen();	
	m_CheckFullScreen.SetCheck(0);
}

void CJukeBoxDlg::OnMovieScreen() 
{
	OnCheckFullScreen();
	
}

void CJukeBoxDlg::SetMediaDir(CString strFileName) 
{
    
	m_EditMediaDir.SetWindowText(strFileName);

    // Render this file and show the first video frame, if present
    OnSelectFile();
    
    strFileName.ReleaseBuffer();
}

BOOL CJukeBoxDlg::DlgToolTips(UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
    LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	UINT nID = pTTT->uFlags;
	if(pTTT->uFlags & TTF_IDISHWND)
	{
		nID= ::GetDlgCtrlID((HWND)nID);
		if(!nID)
		{
			HWND hWndPlay = m_ButtonPlay.GetSafeHwnd();
            HWND hWndStop = m_ButtonStop.GetSafeHwnd();
            HWND hWndPause = m_ButtonPause.GetSafeHwnd();
			HWND hWndFrameStep = m_ButtonFrameStep.GetSafeHwnd();
			HWND hWndGraphEdit = m_ButtonGraphEdit.GetSafeHwnd();
			HWND hWndProperties = m_ButtonProperties.GetSafeHwnd();
			HWND hWndBrowse = m_ButtonBrowse.GetSafeHwnd();
			HWND hWndMute = m_CheckMute.GetSafeHwnd();
			HWND hWndLoop = m_CheckLoop.GetSafeHwnd();
			HWND hWndFullScreen = m_CheckFullScreen.GetSafeHwnd();
			HWND hWndVolume = m_VolumeSlider.GetSafeHwnd();
			HWND hWndSeekBar = m_Seekbar.GetSafeHwnd();
			
			//Show tooltip Play
			if((HWND)(pNMHDR->idFrom) == hWndPlay)
			{	
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Reproducir [R]");
					break;
				default :
					pTTT->lpszText = _T("Play [P]");
					break;
				}
				return TRUE;								
			}
            //Show tooltip Stop
			if((HWND)(pNMHDR->idFrom) == hWndStop)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Detener [D]");
					break;
				default :
					pTTT->lpszText = _T("Stop [S]");
					break;
				}	
				return TRUE;
			}
            //Show tooltip Pause
			if((HWND)(pNMHDR->idFrom) == hWndPause)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Pausar [P]");
					break;
				default :
					pTTT->lpszText = _T("Pause [U]");
					break;
				}	
				return TRUE;
			}
			//Show tooltip FrameStep
			if((HWND)(pNMHDR->idFrom) == hWndFrameStep)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Recorrer marcos [M]");
					break;
				default :
					pTTT->lpszText = _T("FrameStep [R]");
					break;
				}	
				return TRUE;
			}
			//Show tooltip GraphEdit
			if((HWND)(pNMHDR->idFrom) == hWndGraphEdit)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Editor gráfico de filtros [G]");
					break;
				default :
					pTTT->lpszText = _T("GraphEdit [G]");
					break;
				}	
				return TRUE;
			}
			//Show tooltip Properties
			if((HWND)(pNMHDR->idFrom) == hWndProperties)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Propiedades de filtros [T]");
					break;
				default :
					pTTT->lpszText = _T("Filter properties [T]");
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
					pTTT->lpszText = _T("Examinar archivos de video [E]");
					break;
				default :
					pTTT->lpszText = _T("Browse video files [B]");
					break;
				}	
				return TRUE;
			}
			//Show tooltip Mute
			if((HWND)(pNMHDR->idFrom) == hWndMute)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Silencio [S]");
					break;
				default :
					pTTT->lpszText = _T("Mute [M]");
					break;
				}
				return TRUE;
			}
			//Show tooltip Loop
			if((HWND)(pNMHDR->idFrom) == hWndLoop)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Repetir [R]");
					break;
				default :
					pTTT->lpszText = _T("Loop [L]");
					break;
				}
				return TRUE;
			}
			//Show tooltip FullScreen
			if((HWND)(pNMHDR->idFrom) == hWndFullScreen)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Pantalla completa [C]  Abandonar [Alt+Esc]");
					break;
				default :
					pTTT->lpszText = _T("FullScreen [F]  Quit [Alt+Esc]");
					break;
				}
				return TRUE;
			}
			//Show tooltip Volume
			if((HWND)(pNMHDR->idFrom) == hWndVolume)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Volumen");
					break;
				default :
					pTTT->lpszText = _T("Volume");
					break;
				}
				return TRUE;
			}
			//Show tooltip Seekbar
			if((HWND)(pNMHDR->idFrom) == hWndSeekBar)
			{
				switch(dwLanguageID)
				{
				case LANG_SPANISH:
					pTTT->lpszText = _T("Buscar");
					break;
				default :
					pTTT->lpszText = _T("Find");
					break;
				}
				return TRUE;
			}
        }
    }
    return FALSE;
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


void CJukeBoxDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
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
	menu.InsertMenu(0, MF_BYPOSITION , ID_CTRL_JUKEBOX_FILE, GetShort(ID_CTRL_JUKEBOX_FILE));
	menu.InsertMenu(1, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(2, MF_BYPOSITION ,ID_CTRL_JUKEBOX_PLAY , GetShort(ID_CTRL_JUKEBOX_PLAY));
	menu.InsertMenu(3, MF_BYPOSITION , ID_CTRL_JUKEBOX_STOP, GetShort(ID_CTRL_JUKEBOX_STOP));
	menu.InsertMenu(4, MF_BYPOSITION , ID_CTRL_JUKEBOX_PAUSE, GetShort(ID_CTRL_JUKEBOX_PAUSE));
	menu.InsertMenu(5, MF_BYPOSITION , ID_CTRL_JUKEBOX_FRAMESTEP, GetShort(ID_CTRL_JUKEBOX_FRAMESTEP));
	menu.InsertMenu(6, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(7, MF_BYPOSITION ,ID_CTRL_JUKEBOX_MUTE , GetShort(ID_CTRL_JUKEBOX_MUTE));
	menu.InsertMenu(8, MF_BYPOSITION ,ID_CTRL_JUKEBOX_LOOP , GetShort(ID_CTRL_JUKEBOX_LOOP));
	menu.InsertMenu(9, MF_BYPOSITION ,ID_CTRL_JUKEBOX_FULLSCREEN , GetShort(ID_CTRL_JUKEBOX_FULLSCREEN));
	menu.InsertMenu(10, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(11, MF_BYPOSITION ,ID_CTRL_JUKEBOX_GRAPHEDIT , GetShort(ID_CTRL_JUKEBOX_GRAPHEDIT));
	menu.InsertMenu(12, MF_BYPOSITION ,ID_CTRL_JUKEBOX_PROPERTIES , GetShort(ID_CTRL_JUKEBOX_PROPERTIES));
	

	menu.SetMenuTitle(_T("JukeBox"),MFT_GRADIENT|MFT_SIDE_TITLE);
	menu.LoadToolBar(IDR_JUKEBOXDLG);

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
*/
	
	
}

void CJukeBoxDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);

	ClientToScreen(&point);
	OnContextMenu(0,point);
	//COXSizeDialogBar::OnRButtonUp(nFlags, point);
}

