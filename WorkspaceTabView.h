#if !defined(AFX_WORKSPACETABVIEW_H__19647BB1_C0AA_4B0C_B474_883536A8A3BC__INCLUDED_)
#define AFX_WORKSPACETABVIEW_H__19647BB1_C0AA_4B0C_B474_883536A8A3BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WorkspaceTabView.h : header file
//
#include "OXSizeCtrlBar.h"
#include "OX3DTabView.h"
#include ".\ScintillaCtrl\ScintillaDocView.h"
/////////////////////////////////////////////////////////////////////////////
// CWorkspaceTabView window
enum { recordRegular, recordPush, recordPop };

class CWorkspaceTabView : public COXSizeControlBar
{
protected:
	DECLARE_DYNCREATE(CWorkspaceTabView)
	
	
	CWorkspaceTabView();           // protected constructor used by dynamic creation
	virtual ~CWorkspaceTabView();
	
	
	BOOL Create(CWnd * pParentWnd, const CString& sTitle=_T("Workspace"),
		const UINT nID=ID_WORKSPACETABVIEW);

// Attributes
public:
	COX3DTabViewContainer m_TabViewContainer;

	CTreeCtrl m_treeCtrl1;
	CTreeCtrl m_treeCtrl2;
	CTreeCtrl m_treeCtrl3;

	CImageList  m_ilTreeImageList1;
	CImageList  m_ilTreeImageList2;
	CImageList  m_ilTreeImageList3;
	CImageList	m_ilTabImageList;


protected:
	HTREEITEM m_hItems[9];
	
	
	int m_nIndex;

	

	int Create3DTabCtrl();
	int CreateTree1();
	int CreateTree2();
	int CreateTree3();


public:

	HTREEITEM CWorkspaceTabView::AddTreeItem1( HTREEITEM hParent, LPTSTR szText, HTREEITEM hInsAfter,int iImage);	
	HTREEITEM CWorkspaceTabView::AddTreeItem2( HTREEITEM hParent, LPTSTR szText, HTREEITEM hInsAfter,int iImage);
	HTREEITEM CWorkspaceTabView::AddTreeItem3( HTREEITEM hParent, LPTSTR szText, HTREEITEM hInsAfter,int iImage);

	CString GetTreeItem1(HTREEITEM hItem);
	void EditTreeItem1(CString label, HTREEITEM hItem);
	void RenameTreeItem1(CString label, HTREEITEM hItem);	

	void AddPasteWorkspace(CString keyword);
	
	void DeleteTree1(HTREEITEM hItem);
	void DeleteTree2(HTREEITEM hItem);
	void DeleteAllTree1();
	void DeleteAllTree2();

	void WSPCheckPositionChange(HTREEITEM hItem, CString name, CString file, int categ);
	long WSPSearchToken(long posStart, long posEnd, LPSTR szToken);
	int  CheckProjectFile(CString name, CString path);
	



	void PoblateTree1();
	//void PoblateTree2();
	//void PoblateTree3();

	void SamplePoblateTree1();
	void SamplePoblateTree2();
	void SamplePoblateTree3();

	
	void printWSPTree2();
	void printWSPTree3();

	void RecursiveWriteItems(CArchive& ar, CTreeCtrl& refCtrl, HTREEITEM hItem);
	void WriteTreeCtrlContent(CArchive& ar, CTreeCtrl& refCtrl);
	void ReadTreeCtrlContent(CArchive& ar, CTreeCtrl& refCtrl);




// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceTabView)
	public:
	virtual void Serialize(CArchive& ar);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceTabView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTree2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTree3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpandedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpandedTree2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpandedTree3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
		//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKSPACETABVIEW_H__19647BB1_C0AA_4B0C_B474_883536A8A3BC__INCLUDED_)
