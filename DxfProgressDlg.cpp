// DxfProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "DxfProgressDlg.h"

#include ".\CadLib\Interface\CadLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDxfProgressDlg dialog

CDxfProgressDlg::CDxfProgressDlg(UINT nCaptionID)
{
	
	//Processing DXFCtrl
	/*
	m_nCaptionID = IDC_PROGRESS_CAPTION;
	if (nCaptionID != 0)
		m_nCaptionID = nCaptionID;
	*/
    m_bCancel=FALSE;
    m_nLower=0;
    m_nUpper=100;
    m_nStep=10;
	m_bParentDisabled = FALSE;
	//{{AFX_DATA_INIT(CDxfProgressDlg)
		
	//}}AFX_DATA_INIT
}


CDxfProgressDlg::~CDxfProgressDlg()
{
    if(m_hWnd!=NULL)
      DestroyWindow();
}


void CDxfProgressDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDxfProgressDlg)
    DDX_Control(pDX, IDC_PROGDLG_PROGRESS, m_Progress);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDxfProgressDlg, CDialog)
    //{{AFX_MSG_MAP(CDxfProgressDlg)
    //}}AFX_MSG_MAP
	
#if _MSC_VER >= 1310  // VC7.1
	ON_MESSAGE( WM_PROGRESS, (LRESULT(AFX_MSG_CALL CWnd::*)(WPARAM, LPARAM)) OnProgress )
#else
	ON_MESSAGE( WM_PROGRESS, OnProgress )
#endif

END_MESSAGE_MAP()




BOOL CDxfProgressDlg::DestroyWindow()
{
    ReEnableParent();
    return CDialog::DestroyWindow();
}

void CDxfProgressDlg::ReEnableParent()
{
    if(m_bParentDisabled && (m_pParentWnd!=NULL))
      m_pParentWnd->EnableWindow(TRUE);
    m_bParentDisabled=FALSE;
}

BOOL CDxfProgressDlg::Create(CWnd *pParent)
{
    // Get the true parent of the dialog
    m_pParentWnd = CWnd::GetSafeOwner(pParent);

    // m_bParentDisabled is used to re-enable the parent window
    // when the dialog is destroyed. So we don't want to set
    // it to TRUE unless the parent was already enabled.

    if((m_pParentWnd!=NULL) && m_pParentWnd->IsWindowEnabled())
    {
      m_pParentWnd->EnableWindow(FALSE);
      m_bParentDisabled = TRUE;
    }

    if(!CDialog::Create(CDxfProgressDlg::IDD,pParent))
    {
      ReEnableParent();
      return FALSE;
    }

    return TRUE;
}




void CDxfProgressDlg::OnCancel()
{
    m_bCancel=TRUE;
}

void CDxfProgressDlg::SetRange(int nLower,int nUpper)
{
    m_nLower = nLower;
    m_nUpper = nUpper;
    m_Progress.SetRange(nLower,nUpper);
}
  
int CDxfProgressDlg::SetPos(int nPos)
{
    PumpMessages();
    int iResult = m_Progress.SetPos(nPos);
    UpdatePercent(nPos);
    return iResult;
}

int CDxfProgressDlg::SetStep(int nStep)
{
    m_nStep = nStep; // Store for later use in calculating percentage
    return m_Progress.SetStep(nStep);
}

int CDxfProgressDlg::OffsetPos(int nPos)
{
    PumpMessages();
    int iResult = m_Progress.OffsetPos(nPos);
    UpdatePercent(iResult+nPos);
    return iResult;
}

int CDxfProgressDlg::StepIt()
{
    PumpMessages();
    int iResult = m_Progress.StepIt();
    UpdatePercent(iResult+m_nStep);
    return iResult;
}

void CDxfProgressDlg::PumpMessages()
{
    // Must call Create() before using the dialog
    ASSERT(m_hWnd!=NULL);

    MSG msg;
    // Handle dialog messages
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if(!IsDialogMessage(&msg))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);  
      }
    }
}

BOOL CDxfProgressDlg::CheckCancelButton()
{
    // Process all pending messages
    PumpMessages();

    // Reset m_bCancel to FALSE so that
    // CheckCancelButton returns FALSE until the user
    // clicks Cancel again. This will allow you to call
    // CheckCancelButton and still continue the operation.
    // If m_bCancel stayed TRUE, then the next call to
    // CheckCancelButton would always return TRUE

    BOOL bResult = m_bCancel;
    m_bCancel = FALSE;

    return bResult;
}

void CDxfProgressDlg::UpdatePercent(int nNewPos)
{
    CWnd *pWndPercent = GetDlgItem(IDC_PROGDLG_PERCENT);
    int nPercent;
    
    int nDivisor = m_nUpper - m_nLower;
    ASSERT(nDivisor>0);  // m_nLower should be smaller than m_nUpper

    int nDividend = (nNewPos - m_nLower);
    ASSERT(nDividend>=0);   // Current position should be greater than m_nLower

    nPercent = nDividend * 100 / nDivisor;

    // Since the Progress Control wraps, we will wrap the percentage
    // along with it. However, don't reset 100% back to 0%
    if(nPercent!=100)
      nPercent %= 100;

    // Display the percentage
    CString strBuf;
    strBuf.Format(_T("%d%c"),nPercent,_T('%'));

	CString strCur; // get current percentage
    pWndPercent->GetWindowText(strCur);

	if (strCur != strBuf)
		pWndPercent->SetWindowText(strBuf);
}


 /////////////////////////////////////////////////////////////////////////////
// CDxfProgressDlg message handlers

BOOL CDxfProgressDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    m_Progress.SetRange(m_nLower,m_nUpper);
    m_Progress.SetStep(m_nStep);
    m_Progress.SetPos(m_nLower);

	/*
	CString strCaption;
	VERIFY(strCaption.LoadString(m_nCaptionID));
    SetWindowText(strCaption);
	*/

    return TRUE;  
}

void CDxfProgressDlg::OnProgress(WPARAM Pos, LPARAM lparam)
{
	SetPos(Pos);
}
