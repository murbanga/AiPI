//------------------------------------------------------------------------------
// File: MP_PlayVideo.cpp
//
// Desc: DirectShow sample code - media control functions.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#include "stdafx.h"
#include <dshow.h>


#include "mp_playvideo.h"


HRESULT MPRunMedia()
{
    HRESULT hr=S_OK;

    if (!pMC_MP)
        return S_OK;

    // Start playback
    hr = pMC_MP->Run();
    if (FAILED(hr)) {
        MPRetailOutput(TEXT("\r\n*** Failed(%08lx) in Run()!\r\n"), hr);
        return hr;
    }

    // Remember play state
    g_psCurrent_MP = State_Running;
    return hr;
}


HRESULT MPStopMedia()
{
    HRESULT hr=S_OK;

    if (!pMC_MP)
        return S_OK;

    // If we're already stopped, don't check again
    if (g_psCurrent_MP == State_Stopped)
        return hr;

    // Stop playback
    hr = pMC_MP->Stop();
    if (FAILED(hr)) {
        MPRetailOutput(TEXT("\r\n*** Failed(%08lx) in Stop()!\r\n"), hr);
        return hr;
    }

    // Remember play state
    g_psCurrent_MP = State_Stopped;
    return hr;
}


HRESULT MPPauseMedia(void)
{
    HRESULT hr=S_OK;

    if (!pMC_MP)
        return S_OK;

    // Play/pause
    if(g_psCurrent_MP != State_Running)
        return S_OK;

    hr = pMC_MP->Pause();
    if (FAILED(hr)) {
        MPRetailOutput(TEXT("\r\n*** Failed(%08lx) in Pause()!\r\n"), hr);
        return hr;
    }

    // Remember play state
    g_psCurrent_MP = State_Paused;
    return hr;
}


HRESULT MPMuteAudio(void)
{
    HRESULT hr=S_OK;
    IBasicAudio *pBA_MP=NULL;
    long lVolume;

    if (!pGB_MP)
        return S_OK;

    hr = pGB_MP->QueryInterface(IID_IBasicAudio, (void **)&pBA_MP);
    if (FAILED(hr))
        return S_OK;

    // Read current volume
    hr = pBA_MP->get_Volume(&lVolume);
    if (hr == E_NOTIMPL)
    {
        // Fail quietly if this is a video-only media file
        pBA_MP->Release();
        return hr;
    }
    else if (FAILED(hr))
    {
        MPRetailOutput(TEXT("Failed in pBA_MP->get_Volume!  hr=0x%x\r\n"), hr);
        pBA_MP->Release();
        return hr;
    }

	 // Save the current volume level for resuming later
    g_lCurrentVolume_MP = lVolume;

    lVolume = MP_VOLUME_SILENCE;



    // Set new volume
    hr = pBA_MP->put_Volume(lVolume);
    if (FAILED(hr))
    {
        MPRetailOutput(TEXT("Failed in pBA_MP->put_Volume!  hr=0x%x\r\n"), hr);
    }

    pBA_MP->Release();
    return hr;
}


HRESULT MPResumeAudio(void)
{
    
	HRESULT hr=S_OK;
    IBasicAudio *pBA_MP=NULL;
    long lVolume;

    if (!pGB_MP)
        return S_OK;

    hr =  pGB_MP->QueryInterface(IID_IBasicAudio, (void **)&pBA_MP);
    if (FAILED(hr))
        return S_OK;

    // Read current volume
    hr = pBA_MP->get_Volume(&lVolume);
    if (hr == E_NOTIMPL)
    {
        // Fail quietly if this is a video-only media file
        pBA_MP->Release();
        return hr;
    }
    else if (FAILED(hr))
    {
        MPRetailOutput(TEXT("Failed in pBA_MP->get_Volume!  hr=0x%x\r\n"), hr);
        pBA_MP->Release();
        return hr;
    }

    // Set new volume
    lVolume = MP_VOLUME_FULL;

    hr = pBA_MP->put_Volume(lVolume);
    if (FAILED(hr))
    {
        MPRetailOutput(TEXT("Failed in pBA_MP->put_Volume!  hr=0x%x\r\n"), hr);
    }

	// Set new volume to previously saved value
    hr = pBA_MP->put_Volume(g_lCurrentVolume_MP);
    
	pBA_MP->Release();
    return hr;
	
}


HRESULT MPToggleFullScreen(void)
{
    
	HRESULT hr=S_OK;
	
    
	LONG lMode;
    static HWND hDrain=0;
	CWnd m_hWnd;
	
	
    // Don't bother with full-screen for audio-only files
    if ((g_bAudioOnly_MP) || (!pVW_MP))
        return S_OK;

    // Read current state
    JIF(pVW_MP->get_FullScreenMode(&lMode));

    if (lMode == OAFALSE)
    {
        // Save current message drain
        LIF(pVW_MP->get_MessageDrain((OAHWND *) &hDrain));

        // Set message drain to application main window
        LIF(pVW_MP->put_MessageDrain((OAHWND) (HWND)m_hWnd));

        // Switch to full-screen mode
        lMode = OATRUE;
        JIF(pVW_MP->put_FullScreenMode(lMode));
        g_bFullScreen_MP = TRUE;
		
    }
    else
    {
        // Switch back to windowed mode
        lMode = OAFALSE;
        JIF(pVW_MP->put_FullScreenMode(lMode));

        // Undo change of message drain
        LIF(pVW_MP->put_MessageDrain((OAHWND) hDrain));

        // Reset video window
        LIF(pVW_MP->SetWindowForeground(-1));

        // Reclaim keyboard focus for player application
        
		
		m_hWnd.UpdateWindow();
		m_hWnd.SetForegroundWindow();
		m_hWnd.SetFocus();
				
		g_bFullScreen_MP = FALSE;
		
    }

    
CLEANUP:  

    return(hr);
    
}


void MPRetailOutput(TCHAR *szFormat, ...)
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


