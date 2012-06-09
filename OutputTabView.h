#if !defined(AFX_OUTPUTTABVIEW_H__746A5662_F368_4BF9_B3C0_7F57544C651E__INCLUDED_)
#define AFX_OUTPUTTABVIEW_H__746A5662_F368_4BF9_B3C0_7F57544C651E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutputTabView.h : header file
//
#include "OXSizeCtrlBar.h"
#include "OX3DTabView.h"
#include "OXHistoryCtrl.h"
#include "FindInFilesExtDlg.h"

#include "FileFinder.h"
#include "PathFinder.h"
/////////////////////////////////////////////////////////////////////////////



// COutputTabView window


class COutputTabView : public COXSizeControlBar
{
// Construction
public:
	DECLARE_DYNCREATE(COutputTabView)
	COutputTabView();           // protected constructor used by dynamic creation
	virtual ~COutputTabView();

	BOOL Create(CWnd * pParentWnd, const CString& sTitle=_T("Output"), 
		const UINT nID=ID_OUTPUTTABVIEW);
		

// Attributes
public:
	COX3DTabViewContainer m_TabViewContainer;

public:
	//Controls

	CListCtrl	m_listCtrl1;
	CListCtrl	m_listCtrl2;
	CListCtrl	m_listCtrl3;
	CListCtrl   m_listCtrl4;
	CListCtrl	m_listCtrl5;

	COXHistoryCtrl m_HistoryCtrl;

	CRichEditCtrl	m_editCtrl1;
	CRichEditCtrl   m_editCtrl2;


	CImageList	m_ilTabImageList;

	CImageList	m_ilImageList1;
	CImageList	m_ilImageList2;
	CImageList	m_ilImageList3;
	CImageList	m_ilImageList4;

//CFileFinder options attributes
	
	bool		_bSearching;
	CFileFinder	_finder;
	CString		m_strFindText;
	


// Operations
public:
	LVITEM COutputTabView::AddListItem1( int iItem, int iSubItem, LPTSTR szText, int iImage);	
	LVITEM COutputTabView::AddListItem2( int iItem, int iSubItem, LPTSTR szText, int iImage);
	LVITEM COutputTabView::AddListItem3( int iItem, int iSubItem, LPTSTR szText, int iImage);
	LVITEM COutputTabView::AddListItem4( int iItem, int iSubItem, LPTSTR szText, int iImage);
	
	void COutputTabView::AddListSubItem1( LVITEM item, int iItem, int iSubItem, LPTSTR szText);
	void COutputTabView::AddListSubItem2( LVITEM item, int iItem, int iSubItem, LPTSTR szText);
	void COutputTabView::AddListSubItem3( LVITEM item, int iItem, int iSubItem, LPTSTR szText);
	void COutputTabView::AddListSubItem4( LVITEM item, int iItem, int iSubItem, LPTSTR szText);


	void AddMsg(LPCTSTR szFmt, ...);
	void AddMsg1(CString msg);
	void AddMsg2(CString msg);
		
	
	int Create3DTabCtrl();
	int CreateList1();
	int CreateList2();
	int CreateList3();
	int CreateList4();
	int CreateList5();
	int CreateHistory1();
	int CreateEdit1();
	int CreateEdit2();

	void PopulateList1();
	void PopulateList2();
	void PopulateList3();
	void PopulateList4();
	void PopulateHistory1();

	void PopulateEdit1();
	void PopulateEdit2();

	

	void DeleteAllList1();
	void DeleteAllList2();
	void DeleteAllList3();
	void DeleteAllEdit1();
	void DeleteAllEdit2();
	void FindExtAsc(CString strFind, BOOL bCase, BOOL bWord, BOOL bRegularExpression);
	void FindExtDesc(CString strFind, BOOL bCase, BOOL bWord, BOOL bRegularExpression);
	void FindInFiles(CString text, CString folder, CString mask, bool subfolder, bool size, int nmin, int nmax);
	void FindCurrentDirFiles();

	
	
	//FindInFiles Operations

	void	AddFileToListCtrl3(CString szFilePath, CString szFileName, CString szFileSize, CString szFileDate);
	void	AddStatusListCtrl3();
	void	SetStatus(int nCount = 0, LPCTSTR szFolder = NULL);
	

public:
	static void FileFinderProc(CFileFinder *pFinder, DWORD dwCode, void *pCustomParam);
	LONG		m_fSize;
	CTime       m_fDate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputTabView)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);
		
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);

	//{{AFX_MSG(COutputTabView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedList4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedList5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTTABVIEW_H__746A5662_F368_4BF9_B3C0_7F57544C651E__INCLUDED_)
