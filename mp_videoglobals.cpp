//------------------------------------------------------------------------------
// File: MP_VideoGlobals.h
//
// Desc: DirectShow sample code - global data for Jukebox application.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#include "stdafx.h"
#include <dshow.h>

#include "mp_playvideo.h"

//
// Global data
//
IGraphBuilder *pGB_MP = NULL;
IMediaSeeking *pMS_MP = NULL;
IMediaControl *pMC_MP = NULL;
IMediaEventEx *pME_MP = NULL;
IBasicVideo   *pBV_MP = NULL;
IVideoWindow  *pVW_MP = NULL;
IBasicAudio	  *pBA_MP = NULL;	

long  g_lCurrentVolume_MP = MP_VOLUME_FULL;

FILTER_STATE g_psCurrent_MP=State_Stopped;

BOOL g_bLooping_MP      = FALSE,
     g_bAudioOnly_MP    = FALSE,
	 g_bFullScreen_MP   = FALSE,
     g_bGlobalMute_MP   = FALSE;
