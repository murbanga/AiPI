//------------------------------------------------------------------------------
// File: JB_VideoGlobals.h
//
// Desc: DirectShow sample code - global data for Jukebox application.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#include "stdafx.h"
#include <dshow.h>

#include "jb_playvideo.h"

//
// Global data
//
IGraphBuilder *pGB = NULL;
IMediaSeeking *pMS = NULL;
IMediaControl *pMC = NULL;
IMediaEventEx *pME = NULL;
IBasicVideo   *pBV = NULL;
IVideoWindow  *pVW = NULL;
IBasicAudio	  *pBA = NULL;	

long  g_lCurrentVolume = VOLUME_FULL;

FILTER_STATE g_psCurrent=State_Stopped;

BOOL g_bLooping      = FALSE,
     g_bAudioOnly    = FALSE,
	 g_bFullScreen	 = FALSE,
     g_bGlobalMute   = FALSE;
    