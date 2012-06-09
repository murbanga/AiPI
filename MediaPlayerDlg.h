#if !defined(AFX_MEDIAPLAYERDLG_H__1533F44B_25B9_4196_A830_885C94C14601__INCLUDED_)
#define AFX_MEDIAPLAYERDLG_H__1533F44B_25B9_4196_A830_885C94C14601__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MediaPlayerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDlg dialog
#include "OXSizeDlgBar.h"
#include "OXLayoutManager.h"
#include "OXCoolCtrl.h"
#include "OXBitmapButton.h"

#include <dshow.h>
//#include "keyprovider.h"


//
// Constants
//

const int MP_TICKLEN=100, MP_TIMERID=55;
const int MP_VOLUME_FULL=0L;
const int MP_VOLUME_SILENCE=-10000L;
const int MP_MINIMUM_VOLUME=3000;

#define MP_STR_MEDIA_FOLDER        TEXT("\\Media\\\0")
#define MP_STR_MEDIA_FOLDER_SIZE   (sizeof(MP_STR_MEDIA_FOLDER))

/////////////////////////////////////////////////////////////////////////////
// CMediaPlayerDlg dialog

class CMediaPlayerDlg : public COXSizeDialogBar
{

	DECLARE_DYNAMIC(CMediaPlayerDlg);
	
public:
	// Construction
	CMediaPlayerDlg(CWnd* pParent = NULL);   // standard constructor
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

    BOOL IsWindowsMediaFile(LPTSTR lpszFile);
	BOOL DlgToolTips(UINT id, NMHDR * pNMHDR, LRESULT * pResult );
    LONG GetDXMediaPath(TCHAR *strPath, DWORD dwPathSize);
    

    HRESULT PrepareMedia(LPTSTR lpszMovie);
    HRESULT RenderWMFile(LPCWSTR wFile);
    HRESULT CreateFilter(REFCLSID clsid, IBaseFilter **ppFilter);
    HRESULT AddKeyProvider(IGraphBuilder *pGraph);
    HRESULT InitDirectShow(void);
    HRESULT FreeDirectShow(void);
    HRESULT HandleGraphEvent(void);
		

    void ResetDirectShow(void);
    void CenterVideo(void);
    void PlaySelectedFile(void);
    void ConfigureSeekbar(void);
    void StartSeekTimer(void);
    void StopSeekTimer(void);
	void HandleVolumeSlider(WPARAM wReq);
    void HandleVolumeUp(WPARAM wReq);
	void HandleVolumeDown(WPARAM wReq);
	void HandleTrackbar(WPARAM wReq);
    void SetMediaDir(CString sPath);
    void ReadMediaPosition(void);
	
	
    BOOL CanStep(void);
    IBaseFilter * FindFilterFromName(LPTSTR szName);
    BOOL SupportsPropertyPage(IBaseFilter *pFilter);

    void CALLBACK MediaTimer(UINT wTimerID, UINT msg, ULONG dwUser, ULONG dw1, ULONG dw2);
		// moved this out of the AFX_MSG declaration
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
protected:
	BOOL InitLayoutManager();
	
	//Dialog Data
	//{{AFX_DATA(CMediaPlayerDlg)
	enum { IDD = IDD_MEDIAPLAYER_DLG };
	COXCoolButton		m_MPButtonBrowse;
	CButton   m_MPButtonPlay;
	CButton   m_MPButtonStop;
	CButton   m_MPButtonPause;
	CButton m_MPCheckMute;
	CButton m_MPCheckLoop;
	CButton m_MPCheckFullScreen;
	CSliderCtrl	m_MPVolumeSlider;
	CSliderCtrl	m_MPSeekbar;
	CEdit	m_MPEditMediaDir;
	CStatic	m_MPScreen;
	//}}AFX_DATA
	COXLayoutManager m_LayoutManager;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMediaPlayerDlg)
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
		 
	int   m_nCurrentFileSelection;
	REFERENCE_TIME g_rtTotalTime;
    UINT_PTR g_wTimerID;
	TCHAR m_szCurrentDir[MAX_PATH];

#ifndef TARGET_WMF9
    // Global key provider object created/released during the
    // Windows Media graph-building stage.
    CKeyProvider prov;
#endif
	
public:	
	// Generated message map functions
	//{{AFX_MSG(CMediaPlayerDlg)
		virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSetMediadir();
	afx_msg void OnClose();
	afx_msg void OnPause();
	afx_msg void OnPlay();
	afx_msg void OnStop();
	afx_msg void OnSelectFile();
	afx_msg void OnCheckMute();
	afx_msg void OnCheckLoop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC *);
	afx_msg void OnCheckFullScreen();
	afx_msg void OnMovieScreen();
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIAPLAYERDLG_H__1533F44B_25B9_4196_A830_885C94C14601__INCLUDED_)
