#if !defined(AFX_DXFPROGRESSDLG_H__FEEA996A_E202_44C4_A4F4_863B27197A7B__INCLUDED_)
#define AFX_DXFPROGRESSDLG_H__FEEA996A_E202_44C4_A4F4_863B27197A7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DxfProgressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDxfProgressDlg dialog

class CDxfProgressDlg : public CDialog
{
// Construction
public:
	CDxfProgressDlg(UINT nCaptionID = 0);   // standard constructor
	 ~CDxfProgressDlg();

	BOOL Create(CWnd *pParent=NULL);

    // Checking for Cancel button
    BOOL CheckCancelButton();
    // Progress Dialog manipulation
    void SetRange(int nLower,int nUpper);
    int  SetStep(int nStep);
    int  SetPos(int nPos);
    int  OffsetPos(int nPos);
    int  StepIt();

// Dialog Data
	//{{AFX_DATA(CDxfProgressDlg)
	enum { IDD = IDD_DXFPROGRESS_DLG };
	CProgressCtrl	m_Progress;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDxfProgressDlg)
	public:
    virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

//Atributes
protected:
	
	UINT m_nCaptionID;
    int m_nLower;
    int m_nUpper;
    int m_nStep;
    
    BOOL m_bCancel;
    BOOL m_bParentDisabled;

	
// Implementation
protected:
    void ReEnableParent();

    virtual void OnCancel();
    virtual void OnOK() {}; 
    void UpdatePercent(int nCurrent);
    void PumpMessages();

	// Generated message map functions
	afx_msg void OnProgress(WPARAM, LPARAM);

	//{{AFX_MSG(CDxfProgressDlg)
		virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DXFPROGRESSDLG_H__FEEA996A_E202_44C4_A4F4_863B27197A7B__INCLUDED_)
