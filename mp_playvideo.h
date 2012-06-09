//------------------------------------------------------------------------------
// File: MP_PlayVideo.h
//
// Desc: DirectShow sample code - declarations for media control functions.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#ifndef MPPLAY_VID_H
#define MPPLAY_VID_H
//
// Constants
//
#define MP_VOLUME_FULL     0L
#define MP_VOLUME_SILENCE  -10000L

// Application-defined messages
#define WM_GRAPHNOTIFY  WM_APP + 1
#define WM_PLAYFILE     WM_APP + 3


//
// Macros
//
#define SAFE_RELEASE(i) {if (i) i->Release(); i = NULL;}

#define LIF(x) if (FAILED(hr=(x))) \
    {MPRetailOutput(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr);}

#define JIF(x) if (FAILED(hr=(x))) \
    {MPRetailOutput(TEXT("FAILED(0x%x) ") TEXT(#x) TEXT("\n\0"), hr); goto CLEANUP;}

//
// Global data
//
extern IGraphBuilder *pGB_MP;
extern IMediaSeeking *pMS_MP;
extern IMediaControl *pMC_MP;
extern IMediaEventEx *pME_MP;
extern IBasicVideo   *pBV_MP;
extern IVideoWindow  *pVW_MP;
extern IBasicAudio   *pBA_MP;


extern FILTER_STATE g_psCurrent_MP;
extern BOOL g_bLooping_MP;
extern BOOL g_bAudioOnly_MP;
extern BOOL g_bGlobalMute_MP;
extern BOOL g_bFullScreen_MP;
extern long g_lCurrentVolume_MP;

//-----------------------------------------------------------------------------
// External function-prototypes
//-----------------------------------------------------------------------------
HRESULT MPRunMedia(void);
HRESULT MPStopMedia(void);
HRESULT MPPauseMedia(void);
HRESULT MPPlayMedia(LPTSTR lpszMovie, HINSTANCE hInstance);
HRESULT MPCheckMovieState(BOOL *pbComplete);
HRESULT MPGetInterfaces(void);
HRESULT MPMuteAudio(void);
HRESULT MPResumeAudio(void);
HRESULT MPToggleFullScreen(void);
void MPCleanupInterfaces(void);
void MPRetailOutput(TCHAR *tszErr, ...);

#endif // !defined(MPPLAY_VID_H)
