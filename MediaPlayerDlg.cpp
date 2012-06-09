// MediaPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include <atlbase.h>
#include "AIPI.h"
#include "MediaPlayerDlg.h"
#include "mp_playvideo.h"
#include "mediatypes.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CMediaPlayerDlg, COXSizeDialogBar)
/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDlg dialog
CMediaPlayerDlg::CMediaPlayerDlg(CWnd* pParent /*=NULL*/)
	:COXSizeDialogBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	//{{AFX_DATA_INIT(CMediaPlayerDlg)
	//}}AFX_DATA_INIT
	
}


void CMediaPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	COXSizeDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMediaPlayerDlg)
	DDX_Control(pDX, IDC_MP_SLIDER_VOLUME, m_MPVolumeSlider);
    DDX_Control(pDX, IDC_MP_SLIDER, m_MPSeekbar);
    DDX_Control(pDX, IDC_MP_EDIT_MEDIADIR, m_MPEditMediaDir);
    DDX_Control(pDX, IDC_MP_MOVIE_SCREEN, m_MPScreen);
    DDX_Control(pDX, IDC_MP_CHECK_FULLSCREEN, m_MPCheckFullScreen);
    DDX_Control(pDX, IDC_MP_CHECK_MUTE, m_MPCheckMute);
	DDX_Control(pDX, IDC_MP_BUTTON_BROWSE, m_MPButtonBrowse);
    DDX_Control(pDX, IDC_MP_BUTTON_STOP, m_MPButtonStop);
    DDX_Control(pDX, IDC_MP_BUTTON_PLAY, m_MPButtonPlay);
    DDX_Control(pDX, IDC_MP_BUTTON_PAUSE, m_MPButtonPause);
    DDX_Control(pDX, IDC_MP_CHECK_LOOP, m_MPCheckLoop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMediaPlayerDlg, COXSizeDialogBar)
	//{{AFX_MSG_MAP(CMediaPlayerDlg)
	ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDC_MP_BUTTON_PAUSE, OnPause)
    ON_BN_CLICKED(IDC_MP_BUTTON_PLAY, OnPlay)
    ON_BN_CLICKED(IDC_MP_BUTTON_STOP, OnStop)
	ON_BN_CLICKED(IDC_MP_BUTTON_BROWSE, OnButtonSetMediadir)
    ON_BN_CLICKED(IDC_MP_CHECK_MUTE, OnCheckMute)
    ON_BN_CLICKED(IDC_MP_CHECK_LOOP, OnCheckLoop)
	
    ON_WM_TIMER()
    ON_WM_DESTROY()
    ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_MP_CHECK_FULLSCREEN, OnCheckFullScreen)
	ON_BN_CLICKED(IDC_MP_MOVIE_SCREEN, OnMovieScreen)
	//ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,DlgToolTips)    // my tool tips  handler
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDlg message handlers
void CMediaPlayerDlg::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	COXSizeDialogBar::OnUpdateCmdUI(pTarget,FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDlg message handlers


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMediaPlayerDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMediaPlayerDlg::OnQueryDragIcon()
{
    return (HCURSOR) m_hIcon;
}


/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDlg DirectShow code and message handlers

BOOL CMediaPlayerDlg::InitLayoutManager()
{
	
	BOOL retval = TRUE;

	if(!m_LayoutManager.IsAttached()) 
	{
		m_LayoutManager.Attach(this);
		m_LayoutManager.SetMinMax(IDC_MP_MOVIE_SCREEN, CSize(150,60), CSize(0,0)); 

	//Constrain browse button
	m_LayoutManager.SetConstraint(IDC_MP_BUTTON_BROWSE, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_MP_BUTTON_BROWSE, OX_LMS_LEFT, OX_LMT_SAME, 1);


	//Constrain check full screen
	m_LayoutManager.SetConstraint(IDC_MP_CHECK_FULLSCREEN, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_MP_CHECK_FULLSCREEN, OX_LMS_RIGHT, OX_LMT_SAME, 1);
	

	//Constrain edit media dir
	m_LayoutManager.SetConstraint(IDC_MP_EDIT_MEDIADIR, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_MP_EDIT_MEDIADIR, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -2, IDC_MP_CHECK_FULLSCREEN);
	m_LayoutManager.SetConstraint(IDC_MP_EDIT_MEDIADIR, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_MP_BUTTON_BROWSE);
	
		
	//Constrain button play
	m_LayoutManager.SetConstraint(IDC_MP_BUTTON_PLAY, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -2, IDC_MP_EDIT_MEDIADIR);
	m_LayoutManager.SetConstraint(IDC_MP_BUTTON_PLAY, OX_LMS_LEFT, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_MP_BUTTON_PLAY, OX_LMS_RIGHT, OX_LMT_POSITION, 22);

	//Constrain button stop
	m_LayoutManager.SetConstraint(IDC_MP_BUTTON_STOP, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -2, IDC_MP_EDIT_MEDIADIR);
	m_LayoutManager.SetConstraint(IDC_MP_BUTTON_STOP, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_MP_BUTTON_PLAY);
	m_LayoutManager.SetConstraint(IDC_MP_BUTTON_STOP, OX_LMS_RIGHT, OX_LMT_POSITION, 44);


	//Constrain button pause
	m_LayoutManager.SetConstraint(IDC_MP_BUTTON_PAUSE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -2, IDC_MP_EDIT_MEDIADIR);
	m_LayoutManager.SetConstraint(IDC_MP_BUTTON_PAUSE, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_MP_BUTTON_STOP);
	m_LayoutManager.SetConstraint(IDC_MP_BUTTON_PAUSE, OX_LMS_RIGHT, OX_LMT_POSITION, 66);


	//Constrain static volume
	m_LayoutManager.SetConstraint(IDC_MP_STATIC_VOLUME, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -5, IDC_MP_EDIT_MEDIADIR);
	m_LayoutManager.SetConstraint(IDC_MP_STATIC_VOLUME, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -5, IDC_MP_SLIDER_VOLUME);
		
	//Constrain slider volume
	m_LayoutManager.SetConstraint(IDC_MP_SLIDER_VOLUME, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_MP_EDIT_MEDIADIR);
	m_LayoutManager.SetConstraint(IDC_MP_SLIDER_VOLUME, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
		
	//Constrain check repeat
	m_LayoutManager.SetConstraint(IDC_MP_CHECK_LOOP, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_MP_SLIDER_VOLUME);
	m_LayoutManager.SetConstraint(IDC_MP_CHECK_LOOP, OX_LMS_RIGHT, OX_LMT_SAME, -5);
	
	
	//Constrain check mute
	m_LayoutManager.SetConstraint(IDC_MP_CHECK_MUTE, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_MP_SLIDER_VOLUME);
	m_LayoutManager.SetConstraint(IDC_MP_CHECK_MUTE, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -10, IDC_MP_CHECK_LOOP);
	
	// Constrain the slider bar
	m_LayoutManager.SetConstraint(IDC_MP_SLIDER, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -2, IDC_MP_CHECK_LOOP);
	m_LayoutManager.SetConstraint(IDC_MP_SLIDER, OX_LMS_LEFT,  OX_LMT_SAME, 0);
	m_LayoutManager.SetConstraint(IDC_MP_SLIDER, OX_LMS_RIGHT, OX_LMT_SAME, 0);


		// Constrain the movie screen
	m_LayoutManager.SetConstraint(IDC_MP_MOVIE_SCREEN, OX_LMS_TOP, OX_LMT_SAME, 0);
	m_LayoutManager.SetConstraint(IDC_MP_MOVIE_SCREEN, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, 0, IDC_MP_SLIDER);
	m_LayoutManager.SetConstraint(IDC_MP_MOVIE_SCREEN, OX_LMS_LEFT,  OX_LMT_SAME, 0);
	m_LayoutManager.SetConstraint(IDC_MP_MOVIE_SCREEN, OX_LMS_RIGHT, OX_LMT_SAME, 0);

	}

	return retval;

}



BOOL CMediaPlayerDlg::OnInitDialog()
{
    COXSizeDialogBar::OnInitDialog();

/*
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		CWnd::SetWindowText(_T("MediaPlayer"));
		GetDlgItem(IDC_MP_CHECK_LOOP)->SetWindowText(_T("Repetir"));
		GetDlgItem(IDC_MP_CHECK_MUTE)->SetWindowText(_T("Silencio"));
		GetDlgItem(IDC_MP_CHECK_FULLSCREEN)->SetWindowText(_T("Pantalla completa"));
		break;
	default:
		CWnd::SetWindowText(_T("MediaPlayer"));
		GetDlgItem(IDC_MP_CHECK_LOOP)->SetWindowText(_T("Repeat"));
		GetDlgItem(IDC_MP_CHECK_MUTE)->SetWindowText(_T("Mute"));
		GetDlgItem(IDC_MP_CHECK_FULLSCREEN)->SetWindowText(_T("Full screen"));
		break;
	}
	
	//Resize Controls
	
	
	AddSzControl(IDC_MP_STATIC_VOLUME, mdRelative, mdRepos);
	AddSzControl(IDC_MP_SLIDER, mdResize, mdRepos);
	AddSzControl(IDC_MP_SLIDER_VOLUME, mdRelative, mdRepos);
	AddSzControl(IDC_MP_MOVIE_SCREEN, mdResize, mdResize);
	AddSzControl(IDC_MP_BUTTON_PLAY, mdRelative, mdRepos);
	AddSzControl(IDC_MP_BUTTON_STOP, mdRelative, mdRepos);
	AddSzControl(IDC_MP_BUTTON_PAUSE, mdRelative, mdRepos);
	AddSzControl(IDC_MP_CHECK_LOOP, mdRepos, mdRepos);
    AddSzControl(IDC_MP_CHECK_MUTE, mdRepos, mdRepos);
	AddSzControl(IDC_MP_CHECK_FULLSCREEN, mdRepos, mdRepos);
	AddSzControl(IDC_MP_EDIT_MEDIADIR, mdResize, mdRepos);

	

  //Add icons

	hPlay= LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_MEDIAPLAYER_PLAY));
	hPause= LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_MEDIAPLAYER_PAUSE));
	hStop= LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_MEDIAPLAYER_STOP));
	

	m_MPButtonPlay.SetIcon(hPlay);
	m_MPButtonPause.SetIcon(hPause);
	m_MPButtonStop.SetIcon(hStop);
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
        MPRetailOutput(TEXT("Failed to initialize DirectShow!  hr=0x%x\r\n"), hr);
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
    m_MPScreen.ModifyStyle(0, WS_CLIPCHILDREN);

    // Initialize seeking trackbar range
    m_MPSeekbar.SetRange(0, 100, TRUE);
    m_MPSeekbar.SetTicFreq(5);

	//Current Volume
	g_lCurrentVolume_MP = MP_VOLUME_FULL;
	//Current Window size
	g_bFullScreen_MP = FALSE;
	
	//Set the Slider
	m_MPVolumeSlider.SetRange(0, MP_MINIMUM_VOLUME, TRUE);

	//SetMediadir();
	
	EnableToolTips();
    
    return TRUE;  // return TRUE  unless you set the focus to a control
}


LONG CMediaPlayerDlg::GetDXMediaPath(TCHAR *szPath, DWORD dwPathSize)
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
    if ((_tcslen(szPath) + MP_STR_MEDIA_FOLDER_SIZE) < dwPathSize )
    {
        _tcscat( szPath, MP_STR_MEDIA_FOLDER );
        return 0;
    }
    else
        return -1;
}


void CMediaPlayerDlg::OnClose() 
{
    // Release DirectShow interfaces
    MPStopMedia();
    FreeDirectShow();
	
	g_bFullScreen_MP = FALSE;

    // Release COM
    CoUninitialize();

    COXSizeDialogBar::OnClose();
}


void CMediaPlayerDlg::OnDestroy() 
{
    FreeDirectShow();   

    COXSizeDialogBar::OnDestroy();
}


void CMediaPlayerDlg::OnButtonSetMediadir() 
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
        m_MPEditMediaDir.SetWindowText(strFilename);

        // Render this file and show the first video frame, if present
        OnSelectFile();
    }

    strFilename.ReleaseBuffer();
	
	m_MPCheckFullScreen.EnableWindow(true);
	// Don't bother with full-screen for audio-only files
	if ((g_bAudioOnly_MP) || (!pVW_MP))
	{
        m_MPCheckFullScreen.EnableWindow(false);
		return;
	}


}


void CMediaPlayerDlg::OnSelectFile() 
{
    
	
	HRESULT hr;
    TCHAR szFilename[MAX_PATH];

	// Read file name from Edit control
    m_MPEditMediaDir.GetWindowText(szFilename, MAX_PATH);


    // Remember current play state to restart playback
    int nCurrentState = g_psCurrent_MP;

    // First release any existing interfaces
    ResetDirectShow();

    
        
    // Load the selected media file
    hr = PrepareMedia(szFilename);
    if (FAILED(hr))
    {
        // Error - disable play button and give feedback
        switch(languagePrimaryID)
		{
		case LANG_SPANISH:
			MessageBox(TEXT("¡Fallo en interpretación de fichero!"));
			break;
		default:
			MessageBox(TEXT("File failed to render!"));
			break;
		}
	
        m_MPButtonPlay.EnableWindow(FALSE);
        FreeDirectShow();
        MessageBeep(0);
        return;
    }
    else
    {
        m_MPButtonPlay.EnableWindow(TRUE);
    }

    
    // Set up the seeking trackbar and read capabilities
    ConfigureSeekbar();

	// Read the current volume slider setting so that the current
    // global volume will be preserved
    m_MPVolumeSlider.EnableWindow(TRUE);
	HandleVolumeSlider(0);

    // If the user has asked to mute audio then we
    // need to mute this new clip before continuing.
    if (g_bGlobalMute_MP)
        MPMuteAudio();

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


BOOL CMediaPlayerDlg::IsWindowsMediaFile(LPTSTR lpszFile)
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


HRESULT CMediaPlayerDlg::PrepareMedia(LPTSTR lpszMovie)
{
    USES_CONVERSION;
    HRESULT hr = S_OK;

    // Is this a Windows Media file (ASF, WMA, WMV)?  If so, use the new
    // ASF Reader filter, which is faster and much better at seeking than
    // the default ASF Reader filter used by default with RenderFile.
    if (IsWindowsMediaFile(lpszMovie))
    {
        hr = RenderWMFile(T2W(lpszMovie));
        if (FAILED(hr)) {
            MPRetailOutput(TEXT("*** Failed(%08lx) to Render WM File(%s)!\r\n"),
                     hr, lpszMovie);
            return hr;
        }
    }
    else
    {
        // Allow DirectShow to create the FilterGraph for this media file
        hr = pGB_MP->RenderFile(T2W(lpszMovie), NULL);
        if (FAILED(hr)) {
            MPRetailOutput(TEXT("*** Failed(%08lx) in RenderFile(%s)!\r\n"),
                     hr, lpszMovie);
            return hr;
        }
    }

    // Set the message drain of the video window to point to our main
    // application window.  If this is an audio-only or MIDI file, 
    // then put_MessageDrain will fail.
    hr = pVW_MP->put_MessageDrain((OAHWND) m_hWnd);
    if (FAILED(hr))
    {
        g_bAudioOnly_MP = TRUE;
    }

    // Have the graph signal event via window callbacks
    hr = pME_MP->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);

    // Configure the video window
    if (!g_bAudioOnly_MP)
    {
        // We'll manually set the video to be visible
        hr = pVW_MP->put_Visible(OAFALSE);

        hr = pVW_MP->put_WindowStyle(WS_CHILD);
        hr = pVW_MP->put_Owner((OAHWND) m_MPScreen.GetSafeHwnd());

        // Place video window within the bounding rectangle
        CenterVideo();

        // Make the video window visible within the screen window.
        // If this is an audio-only file, then there won't be a video interface.
        hr = pVW_MP->put_Visible(OATRUE);
        hr = pVW_MP->SetWindowForeground(-1);
    }

    return hr;
}


HRESULT CMediaPlayerDlg::RenderWMFile(LPCWSTR wFile)
{
    HRESULT hr=S_OK;
    IFileSourceFilter *pFS=NULL;
    IBaseFilter *pReader=NULL;

    // Load the improved ASF reader filter by CLSID
    hr = CreateFilter(CLSID_WMAsfReader, &pReader);
    if(FAILED(hr))
    {
        MPRetailOutput(TEXT("Failed to create WMAsfWriter filter!  hr=0x%x\n"), hr);
        return hr;
    }

    // Add the ASF reader filter to the graph.  For ASF/WMV/WMA content,
    // this filter is NOT the default and must be added explicitly.
    hr = pGB_MP->AddFilter(pReader, L"ASF Reader");
    if(FAILED(hr))
    {
        MPRetailOutput(TEXT("Failed to add ASF reader filter to graph!  hr=0x%x\n"), hr);
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
    JIF(AddKeyProvider(pGB_MP));
#endif

    // Set its source filename
    JIF(pReader->QueryInterface(IID_IFileSourceFilter, (void **) &pFS));
    JIF(pFS->Load(wFile, NULL));
    pFS->Release();

    
CLEANUP:
    // If there was a rendering error, make sure that the reader is released
    //
    // Otherwise, wince the graph is built and the filters are added to 
    // the graph, the WM ASF reader interface can be released.
    SAFE_RELEASE(pReader);

    return hr;
}


HRESULT CMediaPlayerDlg::CreateFilter(REFCLSID clsid, IBaseFilter **ppFilter)
{
    HRESULT hr;

    hr = CoCreateInstance(clsid,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IBaseFilter,
        (void **) ppFilter);

    if(FAILED(hr))
    {
        MPRetailOutput(TEXT("CreateFilter: Failed to create filter!  hr=0x%x\n"), hr);
        *ppFilter = NULL;
        return hr;
    }

    return S_OK;
}



// Windows Media 9 Series (code named 'Corona') no longer requires 
// a stub library.  If using WMF9, we don't need to provide a CKeyProvider
// implementation, and we don't need to link with the WMStub.lib library.
//
#ifndef TARGET_WMF9

HRESULT CMediaPlayerDlg::AddKeyProvider(IGraphBuilder *pGraph)
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


void CMediaPlayerDlg::OnPause() 
{  
    	
	if (g_psCurrent_MP == State_Paused)
    {
        MPRunMedia();
        StartSeekTimer();
		
		
    }
    else
    {
        StopSeekTimer();
        MPPauseMedia();
        
		
    }
}


void CMediaPlayerDlg::OnPlay() 
{
    MPRunMedia();
    StartSeekTimer();
    
	
	
}


void CMediaPlayerDlg::OnStop() 
{
    HRESULT hr;

    if (!pMC_MP || !pMS_MP)
        return;

    // Stop playback immediately with IMediaControl::Stop().
    StopSeekTimer();
    MPStopMedia();

    // Wait for the stop to propagate to all filters
    OAFilterState fs;
    hr = pMC_MP->GetState(500, &fs);
    if (FAILED(hr))
    {
        MPRetailOutput(TEXT("Failed to read graph state!  hr=0x%x\r\n"), hr);
    }

    // Reset to beginning of media clip
    LONGLONG pos=0;
    hr = pMS_MP->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                           NULL, AM_SEEKING_NoPositioning);
    if (FAILED(hr))
    {
        MPRetailOutput(TEXT("Failed to seek to beginning of media!  hr=0x%x\r\n"), hr);
    }
  
    // Display the first frame of the media clip, if it contains video.
    // StopWhenReady() pauses all filters internally (which allows the video
    // renderer to queue and display the first video frame), after which
    // it sets the filters to the stopped state.  This enables easy preview
    // of the video's poster frame.
    hr = pMC_MP->StopWhenReady();
    if (FAILED(hr))
    {
        MPRetailOutput(TEXT("Failed in StopWhenReady!  hr=0x%x\r\n"), hr);
    }

    

    // Reset slider bar and position label back to zero
    ReadMediaPosition();
}


HRESULT CMediaPlayerDlg::InitDirectShow(void)
{
    HRESULT hr = S_OK;

    g_bAudioOnly_MP = FALSE;

    // Zero interfaces (sanity check)
    pVW_MP = NULL;
    pBV_MP = NULL;

    JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, 
                        (void **)&pGB_MP));
    JIF(pGB_MP->QueryInterface(IID_IMediaControl,  (void **)&pMC_MP));
    JIF(pGB_MP->QueryInterface(IID_IMediaSeeking,  (void **)&pMS_MP));
    JIF(pGB_MP->QueryInterface(IID_IBasicVideo,    (void **)&pBV_MP));
    JIF(pGB_MP->QueryInterface(IID_IVideoWindow,   (void **)&pVW_MP));
    JIF(pGB_MP->QueryInterface(IID_IMediaEventEx,  (void **)&pME_MP));
	JIF(pGB_MP->QueryInterface(IID_IBasicAudio,    (void **)&pBA_MP));

    return S_OK;

CLEANUP:
    FreeDirectShow();
    return(hr);
}


HRESULT CMediaPlayerDlg::FreeDirectShow(void)
{
    HRESULT hr=S_OK;

    StopSeekTimer();
    MPStopMedia();

	 // Remember the current volume slider position so that the
    // same volume level can be applied to the next clip
    HandleVolumeSlider(0);

    // Disable event callbacks
    if (pME_MP)
        hr = pME_MP->SetNotifyWindow((OAHWND)NULL, 0, 0);

    // Hide video window and remove owner.  This is not necessary here,
    // since we are about to destroy the filter graph, but it is included
    // for demonstration purposes.  Remember to hide the video window and
    // clear its owner when destroying a window that plays video.
    if(pVW_MP)
    {
        hr = pVW_MP->put_Visible(OAFALSE);
        hr = pVW_MP->put_Owner(NULL);
    }

    SAFE_RELEASE(pMC_MP);
    SAFE_RELEASE(pMS_MP);
    SAFE_RELEASE(pVW_MP);
    SAFE_RELEASE(pBV_MP);
    SAFE_RELEASE(pME_MP);
    SAFE_RELEASE(pGB_MP);
	SAFE_RELEASE(pBA_MP);


    return hr;
}


void CMediaPlayerDlg::ResetDirectShow(void)
{
    // Destroy the current filter graph its filters.
    FreeDirectShow();

    // Reinitialize graph builder and query for interfaces
    InitDirectShow();

}

void CMediaPlayerDlg::CenterVideo(void)
{
    LONG width, height;
    HRESULT hr;

    if ((g_bAudioOnly_MP) || (!pVW_MP))
        return;

    // Read coordinates of video container window
    RECT rc;
    m_MPScreen.GetClientRect(&rc);
    width  =  rc.right - rc.left;
    height = rc.bottom - rc.top;

    // Ignore the video's original size and stretch to fit bounding rectangle
    hr = pVW_MP->SetWindowPosition(rc.left, rc.top, width, height);
    if (FAILED(hr))
    {
        MPRetailOutput(TEXT("Failed to set window position!  hr=0x%x\r\n"), hr);
        return;
    }
}


LRESULT CMediaPlayerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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
					if (g_bFullScreen_MP)
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
    // of the m_MPScreen window.  This method should be used by windows that 
    // make a renderer window a child window. It forwards significant messages 
    // to the child window that the child window would not otherwise receive. 
    if (pVW_MP)
    {
        pVW_MP->NotifyOwnerMessage((LONG_PTR) m_hWnd, message, wParam, lParam);
    }

    return COXSizeDialogBar::WindowProc(message, wParam, lParam);




}


HRESULT CMediaPlayerDlg::HandleGraphEvent(void)
{
    LONG evCode, evParam1, evParam2;
    HRESULT hr=S_OK;

    // Since we may have a scenario where we're shutting down the application,
    // but events are still being generated, make sure that the event
    // interface is still valid before using it.  It's possible that
    // the interface could be freed during shutdown but later referenced in
    // this callback before the app completely exits.
    if (!pME_MP)
        return S_OK;
    
    while(SUCCEEDED(pME_MP->GetEvent(&evCode, (LONG_PTR *) &evParam1, 
                    (LONG_PTR *) &evParam2, 0)))
    {
        // Spin through the events
        if(EC_COMPLETE == evCode)
        {
            // If looping, reset to beginning and continue playing
            if (g_bLooping_MP)
            {
                LONGLONG pos=0;

                // Reset to first frame of movie
                hr = pMS_MP->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                                       NULL, AM_SEEKING_NoPositioning);
                if (FAILED(hr))
                {
                    // Some custom filters (like the Windows CE MIDI filter) 
                    // may not implement seeking interfaces (IMediaSeeking)
                    // to allow seeking to the start.  In that case, just stop 
                    // and restart for the same effect.  This should not be
                    // necessary in most cases.
                    MPStopMedia();
                    MPRunMedia();
                }
            }
            else
            {
                // Stop playback and display first frame of movie
                OnStop();
            }
        }

        // Free memory associated with this event
        hr = pME_MP->FreeEventParams(evCode, evParam1, evParam2);

        
    }

    return hr;
}


void CMediaPlayerDlg::OnCheckMute() 
{
    // Remember global mute status for next file.  When you destroy a
    // filtergraph, you lose all of its audio settings.  Therefore, when
    // we create the next graph, we will mute the audio before running
    // the graph if this global variable is set.
    g_bGlobalMute_MP ^= 1; 

    if (g_bGlobalMute_MP)
	{
        MPMuteAudio();
		m_MPVolumeSlider.EnableWindow(FALSE);
	}
    else
	{
        MPResumeAudio();
		if (pBA_MP)
		m_MPVolumeSlider.EnableWindow(TRUE);
	}
}


void CMediaPlayerDlg::OnCheckLoop() 
{
    g_bLooping_MP ^= 1;
	

}

void CMediaPlayerDlg::SetMediaDir(CString strFileName) 
{
    
	//CString strFilename;
	
    //strFilename = TEXT("F:\\VIDEOS\\IzabellaScorupco\\Exorcist__the_Beginning_Izabella_Scorupco.avi");
	//strFilename = TEXT("E:\\Mis documentos\\Mis imágenes\\Batman_Dead_End.mov");
	m_MPEditMediaDir.SetWindowText(strFileName);

    // Render this file and show the first video frame, if present
    OnSelectFile();
    
    strFileName.ReleaseBuffer();
}



void CMediaPlayerDlg::PlaySelectedFile() 
{
    OnPlay();
}



// The GraphBuilder interface provides a FindFilterByName() method,
// which provides similar functionality to the method below.
// This local method is provided for educational purposes.
//
IBaseFilter *CMediaPlayerDlg::FindFilterFromName(LPTSTR szNameToFind)
{
    USES_CONVERSION;

    HRESULT hr;
    IEnumFilters *pEnum = NULL;
    IBaseFilter *pFilter = NULL;
    ULONG cFetched;
    BOOL bFound = FALSE;

    // Get filter enumerator
    hr = pGB_MP->EnumFilters(&pEnum);
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




BOOL CMediaPlayerDlg::SupportsPropertyPage(IBaseFilter *pFilter) 
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


//
// Some hardware decoders and video renderers support stepping media
// frame by frame with the IVideoFrameStep interface.  See the interface
// documentation for more details on frame stepping.
//
BOOL CMediaPlayerDlg::CanStep(void)
{
    HRESULT hr;
    IVideoFrameStep* pFS;

    hr = pGB_MP->QueryInterface(__uuidof(IVideoFrameStep), (PVOID *)&pFS);
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



void CMediaPlayerDlg::ConfigureSeekbar()
{
    // Disable seekbar for new file and reset tracker/position label
    m_MPSeekbar.SetPos(0);
	g_rtTotalTime=0;

    // If we can't read the file's duration, disable the seek bar
    if (pMS_MP && SUCCEEDED(pMS_MP->GetDuration(&g_rtTotalTime)))
        m_MPSeekbar.EnableWindow(TRUE);
    else
        m_MPSeekbar.EnableWindow(FALSE);
}


void CMediaPlayerDlg::StartSeekTimer() 
{
    // Cancel any pending timer event
    StopSeekTimer();

    // Create a new timer
    g_wTimerID = SetTimer(MP_TIMERID, MP_TICKLEN, NULL);
}

void CMediaPlayerDlg::StopSeekTimer() 
{
    // Cancel the timer
    if(g_wTimerID)        
    {                
        KillTimer(g_wTimerID);
        g_wTimerID = 0;
    }
}

void CMediaPlayerDlg::OnTimer(UINT nIDEvent) 
{
    ReadMediaPosition();

    COXSizeDialogBar::OnTimer(nIDEvent);
}


void CMediaPlayerDlg::ReadMediaPosition()
{
    HRESULT hr;
    REFERENCE_TIME rtNow;

    if (!pMS_MP)
        return;

    // Read the current stream position
    hr = pMS_MP->GetCurrentPosition(&rtNow);
    if (FAILED(hr))
        return;

    // Convert position into a percentage value and update slider position
    if (g_rtTotalTime != 0)
    {
        long lTick = (long)((rtNow * 100) / g_rtTotalTime);
        m_MPSeekbar.SetPos(lTick);
    }
    else
        m_MPSeekbar.SetPos(0);
    
    
}


void CMediaPlayerDlg::HandleVolumeSlider(WPARAM wReq)
{
    HRESULT hr=S_OK;
    long lVolume;

    // Disregard ENDSCROLL messages, which are redundant
    if ((!pBA_MP) || (wReq == SB_ENDSCROLL))
        return;

    // Since the IBasicAudio interface adjusts volume on a logarithmic
    // scale from -10000 to 0, volumes below -4000 sound like silence.
    // Therefore, the slider covers a smaller range.
    int nPosition = m_MPVolumeSlider.GetPos();

    // Since slider goes from MINIMUM_VOLUME to 0, use the negative value
    lVolume = -1 * nPosition;

    // Save current volume to global variable for use with Mute/Resume audio
    g_lCurrentVolume_MP = lVolume;

    // Set new volume
    hr = pBA_MP->put_Volume(lVolume);
}

void CMediaPlayerDlg::HandleVolumeUp(WPARAM wReq)
{
    HRESULT hr=S_OK;
    long lVolume;

    // Disregard ENDSCROLL messages, which are redundant
    if ((!pBA_MP) || (wReq == SB_ENDSCROLL))
        return;

    // Since the IBasicAudio interface adjusts volume on a logarithmic
    // scale from -10000 to 0, volumes below -4000 sound like silence.
    // Therefore, the slider covers a smaller range.
    int nPosition = m_MPVolumeSlider.GetPos();
	

    // Since slider goes from MINIMUM_VOLUME to 0, use the negative value
    lVolume = -1 * nPosition++;
	m_MPVolumeSlider.SetPos( nPosition);

    // Save current volume to global variable for use with Mute/Resume audio
    g_lCurrentVolume_MP = lVolume;

	// Set new volume
    hr = pBA_MP->put_Volume(lVolume);
}

void CMediaPlayerDlg::HandleVolumeDown(WPARAM wReq)
{
    HRESULT hr=S_OK;
    long lVolume;

    // Disregard ENDSCROLL messages, which are redundant
    if ((!pBA_MP) || (wReq == SB_ENDSCROLL))
        return;

    // Since the IBasicAudio interface adjusts volume on a logarithmic
    // scale from -10000 to 0, volumes below -4000 sound like silence.
    // Therefore, the slider covers a smaller range.
    int nPosition = m_MPVolumeSlider.GetPos();

    // Since slider goes from MINIMUM_VOLUME to 0, use the negative value
    lVolume = -1 * nPosition;

    // Save current volume to global variable for use with Mute/Resume audio
    g_lCurrentVolume_MP = lVolume;

    // Set new volume
    hr = pBA_MP->put_Volume(lVolume);
}



void CMediaPlayerDlg::HandleTrackbar(WPARAM wReq)
{
    HRESULT hr;
    static OAFilterState state;
    static BOOL bStartOfScroll = TRUE;

    if ((!pMS_MP) || (!pMC_MP))
        return;

    // If the file is not seekable, the trackbar is disabled. 
    DWORD dwPosition = m_MPSeekbar.GetPos();

    // Pause when the scroll action begins.
    if (bStartOfScroll) 
    {       
        hr = pMC_MP->GetState(10, &state);
        bStartOfScroll = FALSE;
        hr = pMC_MP->Pause();
    }
    
    // Update the position continuously.
    REFERENCE_TIME rtNew = (g_rtTotalTime * dwPosition) / 100;

    hr = pMS_MP->SetPositions(&rtNew, AM_SEEKING_AbsolutePositioning,
                           NULL,   AM_SEEKING_NoPositioning);

    // Restore the state at the end.
    if (wReq == TB_ENDTRACK)
    {
        if (state == State_Stopped)
            hr = pMC_MP->Stop();
        else if (state == State_Running) 
            hr = pMC_MP->Run();

        bStartOfScroll = TRUE;
    }

    
}


void CMediaPlayerDlg::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
{
	
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	m_LayoutManager.RedrawLayout();

}

BOOL CMediaPlayerDlg::OnEraseBkgnd(CDC *pDC)
{
    // Intercept background erasing for the movie window, since the
    // video renderer will keep the screen painted.  Without this code,
    // your video window might get painted over with gray (the default
    // background brush) when it is obscured by another window and redrawn.
    CRect rc;

    // Get the bounding rectangle for the movie screen
    m_MPScreen.GetWindowRect(&rc);
    ScreenToClient(&rc);

    // Exclude the clipping region occupied by our movie screen
    pDC->ExcludeClipRect(&rc);
    
    // Erase the remainder of the dialog as usual
    return COXSizeDialogBar::OnEraseBkgnd(pDC);
}



void CMediaPlayerDlg::OnCheckFullScreen() 
{
	MPToggleFullScreen();
	m_MPCheckFullScreen.SetCheck(0);
	
}

void CMediaPlayerDlg::OnMovieScreen() 
{
	OnCheckFullScreen();
	
}


BOOL CMediaPlayerDlg::DlgToolTips(UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
    LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	UINT nID = pTTT->uFlags;
	if(pTTT->uFlags & TTF_IDISHWND)
	{
		nID= ::GetDlgCtrlID((HWND)nID);
		if(!nID)
		{
			HWND hWndPlay = m_MPButtonPlay.GetSafeHwnd();
            HWND hWndStop = m_MPButtonStop.GetSafeHwnd();
            HWND hWndPause = m_MPButtonPause.GetSafeHwnd();
			HWND hWndMute = m_MPCheckMute.GetSafeHwnd();
			HWND hWndLoop = m_MPCheckLoop.GetSafeHwnd();
			HWND hWndFullScreen = m_MPCheckFullScreen.GetSafeHwnd();
			HWND hWndVolume = m_MPVolumeSlider.GetSafeHwnd();
			HWND hWndSeekBar = m_MPSeekbar.GetSafeHwnd();
			
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
					pTTT->lpszText = _T("Repetir [I]");
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

/*
void CMediaPlayerDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
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
	menu.InsertMenu(0, MF_BYPOSITION ,ID_CTRL_MEDIAPLAYER_PLAY , GetShort(ID_CTRL_MEDIAPLAYER_PLAY));
	menu.InsertMenu(1, MF_BYPOSITION , ID_CTRL_MEDIAPLAYER_STOP, GetShort(ID_CTRL_MEDIAPLAYER_STOP));
	menu.InsertMenu(2, MF_BYPOSITION , ID_CTRL_MEDIAPLAYER_PAUSE, GetShort(ID_CTRL_MEDIAPLAYER_PAUSE));
	menu.InsertMenu(3, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(4, MF_BYPOSITION ,ID_CTRL_MEDIAPLAYER_MUTE , GetShort(ID_CTRL_MEDIAPLAYER_MUTE));
	menu.InsertMenu(5, MF_BYPOSITION ,ID_CTRL_MEDIAPLAYER_LOOP , GetShort(ID_CTRL_MEDIAPLAYER_LOOP));
	menu.InsertMenu(6, MF_BYPOSITION ,ID_CTRL_MEDIAPLAYER_FULLSCREEN , GetShort(ID_CTRL_MEDIAPLAYER_FULLSCREEN));
	
	menu.SetMenuTitle(_T("MediaPlayer"),MFT_GRADIENT|MFT_SIDE_TITLE);
	menu.LoadToolBar(IDR_MEDIAPLAYERDLG);

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());

	
	
}
*/




