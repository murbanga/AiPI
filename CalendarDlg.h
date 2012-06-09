#if !defined(AFX_CALENDARDLG_H__075ACEF2_64BB_44DE_929A_0B9F3B829F3B__INCLUDED_)
#define AFX_CALENDARDLG_H__075ACEF2_64BB_44DE_929A_0B9F3B829F3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalendarDlg.h : header file
//
#include ".\CalendarCtrl\CalendarCtrl.h"
#include	"OXSizeDlgBar.h"
/////////////////////////////////////////////////////////////////////////////
// CCalendarDlg dialog

class CCalendarDlg : public COXSizeDialogBar
{

		DECLARE_DYNAMIC(CCalendarDlg);
public:
	// Construction
	CCalendarDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCalendarDlg();
// Dialog Data
	//{{AFX_DATA(CCalendarDlg)
	enum { IDD = IDD_CALENDAR_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
private:
	void ResizeUI();
	static HRESULT CALLBACK CalendarDataCallback(CCalendarCtrl* pWnd, time_t date);

public:
	CCalendarCtrl*	m_pCalendarCtrl;

protected:
		virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
public:
	// Generated message map functions
	//{{AFX_MSG(CCalendarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnCalendarGoToToday();
	afx_msg void OnCalendarGoTo();
	afx_msg void OnCalendarMarkSelected();
	afx_msg void OnCalendarClearSelected();
	afx_msg void OnCalendarFirstDayOfWeekFriday();
	afx_msg void OnCalendarFirstDayOfWeekMonday();
	afx_msg void OnCalendarFirstDayOfWeekSaturday();
	afx_msg void OnCalendarFirstDayOfWeekSunday();
	afx_msg void OnCalendarFirstDayOfWeekThursday();
	afx_msg void OnCalendarFirstDayOfWeekTuesday();
	afx_msg void OnCalendarFirstDayOfWeekWednesday();
	afx_msg void OnCalendarAddEntryToSelected();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CCalendarDateDlg dialog

class CCalendarDateDlg : public CDialog
{
// Construction
public:
	CCalendarDateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalendarDateDlg)
	enum { IDD = IDD_CALENDARDATE_DLG };
	CDateTimeCtrl	m_DateCtrl;
	COleDateTime	m_Date;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarDateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:	

	// Generated message map functions
	//{{AFX_MSG(CCalendarDateDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CCalendarInputDlg dialog

class CCalendarInputDlg : public CDialog
{
// Construction
public:
	CCalendarInputDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalendarInputDlg)
	enum { IDD = IDD_CALENDARINPUT_DLG };
	CString	m_Text;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarInputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalendartInputDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARDLG_H__075ACEF2_64BB_44DE_929A_0B9F3B829F3B__INCLUDED_)
