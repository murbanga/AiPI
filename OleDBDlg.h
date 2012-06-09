#if !defined(AFX_OLEDBDLG_H__C2013665_D932_40AE_BE59_662ACA6BC33C__INCLUDED_)
#define AFX_OLEDBDLG_H__C2013665_D932_40AE_BE59_662ACA6BC33C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OleDBDlg.h : header file
//
#include	"OXSizeDlgBar.h"
#include "OXLayoutManager.h"
#include "OXCoolCtrl.h"
#include "OXBitmapButton.h"
#include ".\SQLQuery\SQLQuery.h"

/////////////////////////////////////////////////////////////////////////////
// COleDBDlg dialog
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif



enum UpdateHints
{
	HINT_UPDATE_WINDOW,
	HINT_ON_QUERY_RESULT_READY,
	HINT_ON_NODE_SELECTED,
};


typedef enum
{
	TreeNode_None,
	TreeNode_RootDatabase,
	TreeNode_RootTables,
	TreeNode_TableName,

} TreeNodeType;


class COleDBDlg : public COXSizeDialogBar
{

	DECLARE_DYNAMIC(COleDBDlg);


public:
// Construction
	COleDBDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COleDBDlg)
	enum { IDD = IDD_OLEDB_DLG };
	CTreeCtrl		m_treeCtrl;
	CListCtrl		m_listCtrl;
	CStatic			m_wndQueryCap;
	CEdit			m_wndQueryEdit;
	COXCoolButton    m_btnQueryExe;
	COXCoolSpinButtonCtrl m_spinTable;
	COXCoolButton    m_checkTable;

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA
	
public:
	enum ImageIDS
	{
		IID_DATABASE = 0,
		IID_DATABASES,
		IID_TABLE,
		IID_TABLES,
		IID_FIELD,
		IID_FIELDS,
		IID_INDEX,
		IID_INDEXES,
		IID_VIEW,
		IID_VIEWS,
		IID_PROCEDURE,
		IID_PROCEDURES,
		IID_FOREIGNKEY, 
		IID_FOREIGNKEYS
	};
	
	COXLayoutManager m_LayoutManager;
	CImageList      m_imageList;
	CString			m_strQuery;
	CString			m_strSelNodeName;
	CSQLQuery		m_query;
	TreeNodeType	m_hSelNodeType;
	CFont			m_queryFont;

	int				m_iTreeCtrlSize;
	int				m_iSizeFactor;
	
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COleDBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	void OnSelectTreeNode(TreeNodeType node, const CString strText);
	//void SetSize();
	void ShowQueryResult();
	void ShowColumns();
	void PopulateTree();

	void RunQuery();

	void OnUpdateRunQuery(CCmdUI* pCmdUI);
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	BOOL OnOpenDatabaseConnection(int iBatabase);
	BOOL OnOpenDatabase(int iBatabase);
	BOOL InitLayoutManager();
	void ModifyTreeCtrlSize(int iSize); 
	void HideSpinCtrl(int iSize);

// Generated message map functions
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
	// Generated message map functions
	//{{AFX_MSG(COleDBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditQuery();
	afx_msg void OnSelchangedTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRunQuery();
	afx_msg void OnDeltaposOledbSpinTable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOledbCheckTable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OLEDBDLG_H__C2013665_D932_40AE_BE59_662ACA6BC33C__INCLUDED_)
