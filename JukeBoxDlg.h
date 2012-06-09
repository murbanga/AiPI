//------------------------------------------------------------------------------
// File: JukeboxDlg.h
//
// Desc: DirectShow sample code - main dialog header file for the Jukebox
//       application.
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#if !defined(AFX_JUKEBOXDLG_H__F139C46E_AC04_46B0_BA4B_97F2B3EB6B90__INCLUDED_)
#define AFX_JUKEBOXDLG_H__F139C46E_AC04_46B0_BA4B_97F2B3EB6B90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JukeBoxDlg.h : header file
//

#include "OXSizeDlgBar.h"
#include "OXLayoutManager.h"
#include "OXCoolCtrl.h"
#include "OXBitmapButton.h"
#include <dshow.h>
//#include "keyprovider.h"

//
// Constants
//
const int TICKLEN=100, TIMERID=55;
const int VOLUME_FULL=0L;
const int VOLUME_SILENCE=-10000L;
const int MINIMUM_VOLUME=3000;

#define STR_MEDIA_FOLDER        TEXT("\\Media\\\0")
#define STR_MEDIA_FOLDER_SIZE   (sizeof(STR_MEDIA_FOLDER))



// LayoutCtrlDlg dialog
class COXLayoutManager;
/////////////////////////////////////////////////////////////////////////////
// CJukeBoxDlg dialog

class CJukeBoxDlg : public COXSizeDialogBar
{

	DECLARE_DYNAMIC(CJukeBoxDlg);
	

public:
	// Construction
	CJukeBoxDlg(CWnd* pParent = NULL);   // standard constructor
	
	BOOL DisplayFileInfo(LPTSTR szFile);
    BOOL DisplayImageInfo(void);
    BOOL IsWindowsMediaFile(LPTSTR lpszFile);
	BOOL DlgToolTips(UINT id, NMHDR * pNMHDR, LRESULT * pResult );

    LONG GetDXMediaPath(TCHAR *strPath, DWORD dwPathSize);
    LONG GetGraphEditPath(TCHAR *szPath);

    HRESULT PrepareMedia(LPTSTR lpszMovie);
    HRESULT DisplayFileDuration(void);
    HRESULT RenderWMFile(LPCWSTR wFile);
    HRESULT CreateFilter(REFCLSID clsid, IBaseFilter **ppFilter);
    HRESULT AddKeyProvider(IGraphBuilder *pGraph);
    HRESULT RenderOutputPins(IGraphBuilder *pGB, IBaseFilter *pReader);
    HRESULT InitDirectShow(void);
    HRESULT FreeDirectShow(void);
    HRESULT HandleGraphEvent(void);
	
	

    void Say(LPTSTR szText);
    void ResetDirectShow(void);
    void CenterVideo(void);
    void PlaySelectedFile(void);
	   void ConfigureSeekbar(void);
    void StartSeekTimer(void);
    void StopSeekTimer(void);
	void HandleVolumeSlider(WPARAM wReq);
    void HandleTrackbar(WPARAM wReq);
    void UpdatePosition(REFERENCE_TIME rtNow);
    void ReadMediaPosition(void);
	void SetMediaDir(CString strPath);	

    BOOL CanStep(void);
    HRESULT StepFrame(void);
    HRESULT EnumFilters(void);
    HRESULT EnumPins(IBaseFilter *pFilter, PIN_DIRECTION PinDir, CListBox& Listbox);
    IBaseFilter * FindFilterFromName(LPTSTR szName);
    BOOL SupportsPropertyPage(IBaseFilter *pFilter);

    void CALLBACK MediaTimer(UINT wTimerID, UINT msg, ULONG dwUser, ULONG dw1, ULONG dw2);
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	// moved this out of the AFX_MSG declaration
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);

protected:
	BOOL InitLayoutManager();

	
	
	


// Dialog Data
	//{{AFX_DATA(CJukeBoxDlg)
	enum { IDD = IDD_JUKEBOX_DLG };
	COXCoolButton		m_ButtonBrowse;
	COXCoolButton		m_ButtonGraphEdit;
	COXCoolButton		m_ButtonPlay;
	COXCoolButton		m_ButtonStop;
	COXCoolButton		m_ButtonPause;
	COXCoolButton		m_ButtonFrameStep;	
	COXCoolButton		m_CheckMute;
	COXCoolButton		m_CheckLoop;
	COXCoolButton		m_CheckFullScreen;
	COXCoolButton		m_ButtonProperties;
	COXCoolSliderCtrl	m_VolumeSlider;
	COXCoolSliderCtrl	m_Seekbar;
	CEdit				m_EditMediaDir;
	CStatic				m_StrFileDate;
	CStatic				m_StrFileSize;
	CStatic				m_Status;
	CStatic				m_Screen;
	CStatic				m_StrPosition;
	CStatic				m_StrImageSize;
	CStatic				m_StrDuration;

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	COXCoolCtrl<CListBox>	m_ListInfo;
	COXCoolCtrl<CListBox>	m_ListFilters;
	COXLayoutManager m_LayoutManager;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJukeBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	HICON hPlay;
	HICON hPause;
	HICON hStop;
	HICON hFrameStep;
	HICON hGraphEdit;
	HICON hMute;
	HICON hLoop;
	HICON hFullScreen;
	
	 
	
	int   m_nCurrentFileSelection;
	
	REFERENCE_TIME g_rtTotalTime;
    UINT_PTR g_wTimerID;
	BOOL g_bFullscreen;
    TCHAR m_szCurrentDir[MAX_PATH];

#ifndef TARGET_WMF9
    // Global key provider object created/released during the
    // Windows Media graph-building stage.
    CKeyProvider prov;
#endif

	// Generated message map functions
	//{{AFX_MSG(CJukeBoxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnPause();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnCheckMute();
	afx_msg void OnCheckLoop();
	afx_msg void OnSelectFile();
	afx_msg void OnSelchangeListFilters();
	afx_msg void OnDblclkListFilters();
	afx_msg void OnButtonProppage();
	afx_msg void OnButtonFramestep();
	afx_msg void OnButtonSetMediadir();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonGraphedit();
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC *);
	afx_msg void OnCheckFullScreen();
	afx_msg void OnMovieScreen();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUKEBOXDLG_H__F139C46E_AC04_46B0_BA4B_97F2B3EB6B90__INCLUDED_)
