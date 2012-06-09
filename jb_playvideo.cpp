//------------------------------------------------------------------------------
// File: JB_PlayVideo.cpp
//
// Desc: DirectShow sample code - media control functions.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#include "stdafx.h"
#include <dshow.h>


#include "jb_playvideo.h"


HRESULT RunMedia()
{
    HRESULT hr=S_OK;

    if (!pMC)
        return S_OK;

    // Start playback
    hr = pMC->Run();
    if (FAILED(hr)) {
        RetailOutput(TEXT("\r\n*** Failed(%08lx) in Run()!\r\n"), hr);
        return hr;
    }

    // Remember play state
    g_psCurrent = State_Running;
    return hr;
}


HRESULT StopMedia()
{
    HRESULT hr=S_OK;

    if (!pMC)
        return S_OK;

    // If we're already stopped, don't check again
    if (g_psCurrent == State_Stopped)
        return hr;

    // Stop playback
    hr = pMC->Stop();
    if (FAILED(hr)) {
        RetailOutput(TEXT("\r\n*** Failed(%08lx) in Stop()!\r\n"), hr);
        return hr;
    }

    // Remember play state
    g_psCurrent = State_Stopped;
    return hr;
}


HRESULT PauseMedia(void)
{
    HRESULT hr=S_OK;

    if (!pMC)
        return S_OK;

    // Play/pause
    if(g_psCurrent != State_Running)
        return S_OK;

    hr = pMC->Pause();
    if (FAILED(hr)) {
        RetailOutput(TEXT("\r\n*** Failed(%08lx) in Pause()!\r\n"), hr);
        return hr;
    }

    // Remember play state
    g_psCurrent = State_Paused;
    return hr;
}


HRESULT MuteAudio(void)
{
    HRESULT hr=S_OK;
    IBasicAudio *pBA=NULL;
    long lVolume;

    if (!pGB)
        return S_OK;

    hr = pGB->QueryInterface(IID_IBasicAudio, (void **)&pBA);
    if (FAILED(hr))
        return S_OK;

    // Read current volume
    hr = pBA->get_Volume(&lVolume);
    if (hr == E_NOTIMPL)
    {
        // Fail quietly if this is a video-only media file
        pBA->Release();
        return hr;
    }
    else if (FAILED(hr))
    {
        RetailOutput(TEXT("Failed in pBA->get_Volume!  hr=0x%x\r\n"), hr);
        pBA->Release();
        return hr;
    }

	 // Save the current volume level for resuming later
    g_lCurrentVolume = lVolume;

    lVolume = VOLUME_SILENCE;



    // Set new volume
    hr = pBA->put_Volume(lVolume);
    if (FAILED(hr))
    {
        RetailOutput(TEXT("Failed in pBA->put_Volume!  hr=0x%x\r\n"), hr);
    }

    pBA->Release();
    return hr;
}


HRESULT ResumeAudio(void)
{
    
	HRESULT hr=S_OK;
    IBasicAudio *pBA=NULL;
    long lVolume;

    if (!pGB)
        return S_OK;

    hr =  pGB->QueryInterface(IID_IBasicAudio, (void **)&pBA);
    if (FAILED(hr))
        return S_OK;

    // Read current volume
    hr = pBA->get_Volume(&lVolume);
    if (hr == E_NOTIMPL)
    {
        // Fail quietly if this is a video-only media file
        pBA->Release();
        return hr;
    }
    else if (FAILED(hr))
    {
        RetailOutput(TEXT("Failed in pBA->get_Volume!  hr=0x%x\r\n"), hr);
        pBA->Release();
        return hr;
    }

    // Set new volume
    lVolume = VOLUME_FULL;

    hr = pBA->put_Volume(lVolume);
    if (FAILED(hr))
    {
        RetailOutput(TEXT("Failed in pBA->put_Volume!  hr=0x%x\r\n"), hr);
    }

	// Set new volume to previously saved value
    hr = pBA->put_Volume(g_lCurrentVolume);
    
	pBA->Release();
    return hr;
	
	

}


HRESULT ToggleFullScreen(void)
{
    
	HRESULT hr=S_OK;
	
    
	LONG lMode;
    static HWND hDrain=0;
	CWnd m_hWnd;
	
	
    // Don't bother with full-screen for audio-only files
    if ((g_bAudioOnly) || (!pVW))
        return S_OK;

    // Read current state
    JIF(pVW->get_FullScreenMode(&lMode));

    if (lMode == OAFALSE)
    {
        // Save current message drain
        LIF(pVW->get_MessageDrain((OAHWND *) &hDrain));

        // Set message drain to application main window
        LIF(pVW->put_MessageDrain((OAHWND) (HWND)m_hWnd));

        // Switch to full-screen mode
        lMode = OATRUE;
        JIF(pVW->put_FullScreenMode(lMode));
        g_bFullScreen = TRUE;
		
    }
    else
    {
        // Switch back to windowed mode
        lMode = OAFALSE;
        JIF(pVW->put_FullScreenMode(lMode));

        // Undo change of message drain
        LIF(pVW->put_MessageDrain((OAHWND) hDrain));

        // Reset video window
        LIF(pVW->SetWindowForeground(-1));

        // Reclaim keyboard focus for player application
        
		
		m_hWnd.UpdateWindow();
		m_hWnd.SetForegroundWindow();
		m_hWnd.SetFocus();
				
		g_bFullScreen = FALSE;
		
    }

    
CLEANUP:  

    return(hr);
    
}


void RetailOutput(TCHAR *szFormat, ...)
{
    TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
    const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    const int LASTCHAR = NUMCHARS - 1;

    // Format the input string
    va_list pArgs;
    va_start(pArgs, szFormat);

    // Use a bounded buffer size to prevent buffer overruns.  Limit count to
    // character size minus one to allow for a NULL terminating character.
    _vsntprintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);

    // Ensure that the formatted string is NULL-terminated
    szBuffer[LASTCHAR] = TEXT('\0');

    OutputDebugString(szBuffer);
}


