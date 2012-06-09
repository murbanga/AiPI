//------------------------------------------------------------------------------
// File: JB_PlayVideo.h
//
// Desc: DirectShow sample code - declarations for media control functions.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef JBPLAY_VID_H
#define JBPLAY_VID_H

//
// Constants
//
#define VOLUME_FULL     0L
#define VOLUME_SILENCE  -10000L

// Application-defined messages
#define WM_GRAPHNOTIFY  WM_APP + 1
#define WM_PLAYFILE     WM_APP + 3


//
// Macros
//
#define SAFE_RELEASE(i) {if (i) i->Release(); i = NULL;}

#define LIF(x) if (FAILED(hr=(x))) \
    {RetailOutput(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr);}

#define JIF(x) if (FAILED(hr=(x))) \
    {RetailOutput(TEXT("FAILED(0x%x) ") TEXT(#x) TEXT("\n\0"), hr); goto CLEANUP;}

//
// Global data
//
extern IGraphBuilder *pGB;
extern IMediaSeeking *pMS;
extern IMediaControl *pMC;
extern IMediaEventEx *pME;
extern IBasicVideo   *pBV;
extern IVideoWindow  *pVW;
extern IBasicAudio   *pBA;


extern FILTER_STATE g_psCurrent;
extern BOOL g_bLooping;
extern BOOL g_bAudioOnly;
extern BOOL g_bGlobalMute;
extern BOOL g_bFullScreen;
extern long g_lCurrentVolume;

//-----------------------------------------------------------------------------
// External function-prototypes
//-----------------------------------------------------------------------------
HRESULT RunMedia(void);
HRESULT StopMedia(void);
HRESULT PauseMedia(void);
HRESULT PlayMedia(LPTSTR lpszMovie, HINSTANCE hInstance);
HRESULT CheckMovieState(BOOL *pbComplete);
HRESULT GetInterfaces(void);
HRESULT MuteAudio(void);
HRESULT ResumeAudio(void);
HRESULT ToggleFullScreen(void);

void CleanupInterfaces(void);
void RetailOutput(TCHAR *tszErr, ...);

#endif // !defined(JBPLAY_VID_H)
