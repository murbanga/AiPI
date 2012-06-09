// OleDBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "OleDBDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define CRLF CString("\r\n")


extern CAIPIApp theApp;
/////////////////////////////////////////////////////////////////////////////
// COleDBDlg dialog
IMPLEMENT_DYNAMIC(COleDBDlg, COXSizeDialogBar)

COleDBDlg::COleDBDlg(CWnd* pParent /*=NULL*/)
: m_query(GetSession()),	m_hSelNodeType(TreeNode_None),
COXSizeDialogBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	//{{AFX_DATA_INIT(COleDBDlg)
		
	//}}AFX_DATA_INIT
	m_iTreeCtrlSize = 40;
	m_iSizeFactor = 1;
}


void COleDBDlg::DoDataExchange(CDataExchange* pDX)
{
	COXSizeDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COleDBDlg)
	DDX_Control(pDX, IDC_OLEDB_TREECTRL, m_treeCtrl);
	DDX_Control(pDX, IDC_OLEDB_LISTCTRL, m_listCtrl);
	DDX_Control(pDX, IDC_OLEDB_STATICQUERY, m_wndQueryCap);
	DDX_Control(pDX, IDC_OLEDB_EDITQUERY, m_wndQueryEdit);
	DDX_Control(pDX, IDC_OLEDB_BUTTONQUERY, m_btnQueryExe);
	DDX_Control(pDX, IDC_OLEDB_SPINTABLE, m_spinTable);
	DDX_Control(pDX, IDC_OLEDB_CHECKTABLE, m_checkTable);


	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_OLEDB_EDITQUERY, m_strQuery);
}


BEGIN_MESSAGE_MAP(COleDBDlg, COXSizeDialogBar)
	//{{AFX_MSG_MAP(COleDBDlg)
	ON_EN_CHANGE(IDC_OLEDB_EDITQUERY, OnChangeEditQuery)
	ON_NOTIFY(TVN_SELCHANGED, IDC_OLEDB_TREECTRL, OnSelchangedTreeCtrl)
	ON_BN_CLICKED(IDC_OLEDB_BUTTONQUERY, OnRunQuery)
	ON_NOTIFY(UDN_DELTAPOS, IDC_OLEDB_SPINTABLE, OnDeltaposOledbSpinTable)
	ON_BN_CLICKED(IDC_OLEDB_CHECKTABLE, OnOledbCheckTable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-------------------------------------------------------------------
void COleDBDlg::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// respond to this event as we need to override it
//-------------------------------------------------------------------
{
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	m_LayoutManager.RedrawLayout();

	
}


/////////////////////////////////////////////////////////////////////////////
// COleDBDlg message handlers

BOOL COleDBDlg::InitLayoutManager()
{
	
	BOOL retval = TRUE;

	if(!m_LayoutManager.IsAttached()) 
	{
		m_LayoutManager.Attach(this);
		//m_LayoutManager.SetMinMax(IDC_OLEDB_LISTCTRL, CSize(150,60), CSize(0,0)); 

	//Constrain Check Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_CHECKTABLE, OX_LMS_TOP, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_CHECKTABLE, OX_LMS_LEFT, OX_LMT_SAME, 1);


	//Constrain Static Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_STATICQUERY, OX_LMS_TOP, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_STATICQUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_OLEDB_CHECKTABLE);
	

	//Constrain Button Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_BUTTONQUERY, OX_LMS_TOP, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_BUTTONQUERY, OX_LMS_RIGHT, OX_LMT_SAME, -1);
	
	
		
	//Constrain Edit Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_EDITQUERY, OX_LMS_TOP, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_EDITQUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_OLEDB_STATICQUERY);
	m_LayoutManager.SetConstraint(IDC_OLEDB_EDITQUERY, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -2, IDC_OLEDB_BUTTONQUERY);
	

	
	//Constrain TreeCtrl
	m_LayoutManager.SetConstraint(IDC_OLEDB_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 2, IDC_OLEDB_EDITQUERY);
	m_LayoutManager.SetConstraint(IDC_OLEDB_TREECTRL, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_OLEDB_SPINTABLE);
	m_LayoutManager.SetConstraint(IDC_OLEDB_TREECTRL, OX_LMS_LEFT, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_TREECTRL, OX_LMS_RIGHT, OX_LMT_POSITION, m_iTreeCtrlSize);


	//Constrain ListCtrl
	m_LayoutManager.SetConstraint(IDC_OLEDB_LISTCTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 2, IDC_OLEDB_EDITQUERY);
	m_LayoutManager.SetConstraint(IDC_OLEDB_LISTCTRL, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_OLEDB_SPINTABLE);
	m_LayoutManager.SetConstraint(IDC_OLEDB_LISTCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_LISTCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_OLEDB_TREECTRL);
	

	//Constrain Spin Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_SPINTABLE, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_SPINTABLE, OX_LMS_LEFT, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_SPINTABLE, OX_LMS_RIGHT, OX_LMT_SAME, -1);

	
	
	

	}

	return retval;

}


void COleDBDlg::ModifyTreeCtrlSize(int iSize) 
{
	//Constrain Check Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_CHECKTABLE, OX_LMS_TOP, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_CHECKTABLE, OX_LMS_LEFT, OX_LMT_SAME, 1);

	
	//Constrain Static Control
		//Constrain Static Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_STATICQUERY, OX_LMS_TOP, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_STATICQUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_OLEDB_CHECKTABLE);
	

	//Constrain Button Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_BUTTONQUERY, OX_LMS_TOP, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_BUTTONQUERY, OX_LMS_RIGHT, OX_LMT_SAME, -1);
	
	
		
	//Constrain Edit Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_EDITQUERY, OX_LMS_TOP, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_EDITQUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_OLEDB_STATICQUERY);
	m_LayoutManager.SetConstraint(IDC_OLEDB_EDITQUERY, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -2, IDC_OLEDB_BUTTONQUERY);
	

	
	//Constrain TreeCtrl
	m_LayoutManager.SetConstraint(IDC_OLEDB_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 2, IDC_OLEDB_EDITQUERY);
	m_LayoutManager.SetConstraint(IDC_OLEDB_TREECTRL, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_OLEDB_SPINTABLE);
	m_LayoutManager.SetConstraint(IDC_OLEDB_TREECTRL, OX_LMS_LEFT, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_TREECTRL, OX_LMS_RIGHT, OX_LMT_POSITION, iSize);


	//Constrain ListCtrl
	m_LayoutManager.SetConstraint(IDC_OLEDB_LISTCTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 2, IDC_OLEDB_EDITQUERY);
	m_LayoutManager.SetConstraint(IDC_OLEDB_LISTCTRL, OX_LMS_BOTTOM, OX_LMT_OPPOSITE, -1, IDC_OLEDB_SPINTABLE);
	m_LayoutManager.SetConstraint(IDC_OLEDB_LISTCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_LISTCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_OLEDB_TREECTRL);
	

	//Constrain Spin Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_SPINTABLE, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_SPINTABLE, OX_LMS_LEFT, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_SPINTABLE, OX_LMS_RIGHT, OX_LMT_SAME, -1);


	m_LayoutManager.RedrawLayout();
	
}


void COleDBDlg::HideSpinCtrl(int iSize) 
{
	//Constrain Check Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_CHECKTABLE, OX_LMS_TOP, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_CHECKTABLE, OX_LMS_LEFT, OX_LMT_SAME, 1);

	
	//Constrain Static Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_STATICQUERY, OX_LMS_TOP, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_STATICQUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_OLEDB_CHECKTABLE);
	

	//Constrain Button Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_BUTTONQUERY, OX_LMS_TOP, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_BUTTONQUERY, OX_LMS_RIGHT, OX_LMT_SAME, -1);
	
	
		
	//Constrain Edit Control
	m_LayoutManager.SetConstraint(IDC_OLEDB_EDITQUERY, OX_LMS_TOP, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_EDITQUERY, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_OLEDB_STATICQUERY);
	m_LayoutManager.SetConstraint(IDC_OLEDB_EDITQUERY, OX_LMS_RIGHT, OX_LMT_OPPOSITE, -2, IDC_OLEDB_BUTTONQUERY);
	

	
	//Constrain TreeCtrl
	m_LayoutManager.SetConstraint(IDC_OLEDB_TREECTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 2, IDC_OLEDB_EDITQUERY);
	m_LayoutManager.SetConstraint(IDC_OLEDB_TREECTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_TREECTRL, OX_LMS_LEFT, OX_LMT_SAME, 1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_TREECTRL, OX_LMS_RIGHT, OX_LMT_POSITION, iSize);


	//Constrain ListCtrl
	m_LayoutManager.SetConstraint(IDC_OLEDB_LISTCTRL, OX_LMS_TOP, OX_LMT_OPPOSITE, 2, IDC_OLEDB_EDITQUERY);
	m_LayoutManager.SetConstraint(IDC_OLEDB_LISTCTRL, OX_LMS_BOTTOM, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_LISTCTRL, OX_LMS_RIGHT, OX_LMT_SAME, -1);
	m_LayoutManager.SetConstraint(IDC_OLEDB_LISTCTRL, OX_LMS_LEFT, OX_LMT_OPPOSITE, 1, IDC_OLEDB_TREECTRL);
	


	m_LayoutManager.RedrawLayout();
	
}



void COleDBDlg::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	COXSizeDialogBar::OnUpdateCmdUI(pTarget,FALSE);
}


BOOL COleDBDlg::OnInitDialog() 
{
	COXSizeDialogBar::OnInitDialog();

	m_iTreeCtrlSize = 40;
	m_iSizeFactor = 1;
	((CButton*)GetDlgItem(IDC_OLEDB_CHECKTABLE))->SetCheck(1);

	if(!InitLayoutManager())
	{
		MessageBox(_T("Failed to init layout manager!"));
	}

	UpdateData(FALSE);


	if(!::IsWindow(m_listCtrl.GetSafeHwnd()))
		return 0;

		
	if(m_queryFont.CreatePointFont(50,_T("Courier")))
	{
		m_listCtrl.SetFont(&m_queryFont);
	}
	
	
	DWORD dwExStyle = LVS_EX_FULLROWSELECT;
	m_listCtrl.SetExtendedStyle(dwExStyle);
	

	if(!::IsWindow(m_treeCtrl.GetSafeHwnd()))
	return 0;
	
	VERIFY(m_imageList.Create(IDB_IMAGELIST, 16, 0, RGB(255,0,255)));
	m_imageList.SetBkColor(GetSysColor(COLOR_WINDOW));
	m_treeCtrl.SetImageList(&m_imageList,TVSIL_NORMAL);
	

		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void COleDBDlg::RunQuery() 
{
		
	CWaitCursor wait;
	m_query.Empty(); // Clean old query sentence
	
	m_query << m_strQuery;
	if(!m_query.ExecuteSQL())		
		return;
	
	
	OnUpdate(NULL,HINT_ON_QUERY_RESULT_READY, NULL);

	
}




void COleDBDlg::OnUpdateRunQuery(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_strQuery.IsEmpty());
}


void COleDBDlg::OnSelectTreeNode(TreeNodeType node, const CString strText)
{
	m_hSelNodeType = node;
	m_strSelNodeName = strText;
	switch(m_hSelNodeType)
	{
	default:
		ASSERT(0);
		break;
	case TreeNode_None:
	case TreeNode_RootDatabase:
	case TreeNode_RootTables:
		m_strQuery = _T("");
		break;
	case TreeNode_TableName:
		m_strQuery = _T(" SELECT TOP 100 * FROM [" + m_strSelNodeName + "]");
		RunQuery();
		break;
	};
	
	OnUpdate(NULL,HINT_ON_NODE_SELECTED, NULL);
}

/*
void COleDBDlg::SetSize()
{
	if(!::IsWindow(m_listCtrl.GetSafeHwnd()))
		return;

	const cH = 25, d = 5;
	CRect rcClient,rcListCtrl,rcQueryCap,rcQueryEdit;
	GetClientRect(rcClient);
	rcListCtrl	= rcClient;
	rcQueryCap		= rcClient;
	rcQueryEdit		= rcClient;

	rcQueryCap.DeflateRect(d,d);
	rcQueryCap.bottom = rcQueryCap.top   + cH;
	rcQueryEdit		  = rcQueryCap;
	rcQueryCap.right  = rcQueryCap.left  + 40;
	rcQueryEdit.left  = rcQueryCap.right + 2;

	rcListCtrl.DeflateRect(d,35,d,d);
	rcListCtrl.top = rcQueryEdit.bottom + 4;

	m_wndQueryCap.MoveWindow(rcQueryCap);
	m_wndQueryEdit.MoveWindow(rcQueryEdit);
	m_listCtrl.MoveWindow(rcListCtrl);
}
*/


void COleDBDlg::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch (lHint)
	{
	default:
		break;
	case HINT_UPDATE_WINDOW:    // redraw entire window
		Invalidate(FALSE);
		break;
	case HINT_ON_QUERY_RESULT_READY:
		{
			ShowQueryResult();
			UpdateData(FALSE);
		}
	case HINT_ON_NODE_SELECTED:
		{
//			ShowColumns();
			UpdateData(FALSE);
		}
		break;
	}
}


void COleDBDlg::ShowColumns() 
{
	// Clear List control
	m_listCtrl.DeleteAllItems();
	while(m_listCtrl.DeleteColumn(0)) {}

	CSQLQuery& query = m_query;
	
	// Show columns
	int cols = query.GetColumnsCount();
	for( int nCol = 0; nCol < cols; nCol++)
	{
		CString strColName = query.GetColumnName(nCol);
		m_listCtrl.InsertColumn(nCol,strColName,LVCFMT_LEFT,60);
	}
}


void COleDBDlg::ShowQueryResult() 
{

	LockWindowUpdate();

		//AfxMessageBox(_T("Hello"));
	// Clear List control
	m_listCtrl.DeleteAllItems();
	while(m_listCtrl.DeleteColumn(0)) {}

	CSQLQuery& query = m_query;
	
	// Show columns
	int cols = query.GetColumnsCount();
	for( int nCol = 0; nCol < cols; nCol++)
	{
		CString strColName = query.GetColumnName(nCol);
		m_listCtrl.InsertColumn(nCol,strColName,LVCFMT_LEFT,80);
	}
	
	// Show data
	int nItem = 0;
	while(!query.eof())
	{
		CString str; query > str;
		m_listCtrl.InsertItem(nItem,str);
		for( int nSubItem = 1; nSubItem < cols; nSubItem++)
		{
			CString str; query > str;
			m_listCtrl.SetItemText(nItem,nSubItem,str);
		}
		nItem++;
	}
	UnlockWindowUpdate();
}


void COleDBDlg::OnChangeEditQuery() 
{
	UpdateData();	
}

/*
void CLeftView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	SetSize();
}
*/

/*
void COleDBDlg::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch (lHint)
	{
	default:
		break;
	case HINT_UPDATE_WINDOW:    // redraw entire window
		Invalidate(FALSE);
		break;
	case HINT_ON_QUERY_RESULT_READY:
		{
			UpdateData(FALSE);
		}
		break;
	}
}
*/

/*
void COleDBDlg::SetSize()
{
	if(!::IsWindow(m_treeCtrl.GetSafeHwnd()))
		return;
	const d = 5;
	CRect rcClient,rcTree;
	GetClientRect(rcClient);
	rcTree	= rcClient;
	rcTree.DeflateRect(d,d);
	m_treeCtrl.MoveWindow(rcTree);
}
*/
void COleDBDlg::PopulateTree()
{
	COleDBConnectionProp& prop = ((CAIPIApp*)AfxGetApp())->m_props;

	m_treeCtrl.DeleteAllItems();

	CTables	tableSet;

	HTREEITEM hDatabase = 
	m_treeCtrl.InsertItem(prop.m_strDatabaseName,IID_DATABASE,IID_DATABASES);
	m_treeCtrl.SetItemData(hDatabase,TreeNode_RootDatabase);

	HTREEITEM hTables = 
	m_treeCtrl.InsertItem(_T("Tables"),IID_TABLE,IID_TABLES,hDatabase);
	m_treeCtrl.SetItemData(hTables,TreeNode_RootTables);

	CString strType("TABLE");
	

	if (tableSet.Open(*GetSession(), NULL, NULL, NULL, strType) != S_OK)
		return;

	while(tableSet.MoveNext() == S_OK)
	{
		HTREEITEM hItem = NULL;
		if (_tcscmp(tableSet.m_szType, _T("VIEW")) == 0)
			hItem = m_treeCtrl.InsertItem(tableSet.m_szName,IID_VIEW,IID_VIEWS,hTables);
		else
			hItem = m_treeCtrl.InsertItem(tableSet.m_szName,IID_TABLE,IID_TABLES,hTables);
		m_treeCtrl.SetItemData(hItem,TreeNode_TableName);
	}

	UpdateWindow();
}

void COleDBDlg::OnSelchangedTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	TreeNodeType nodeType = TreeNode_None;
	CString strText;

	if(hItem != NULL)
	{
		nodeType = (TreeNodeType)m_treeCtrl.GetItemData(hItem);
		strText = m_treeCtrl.GetItemText(hItem);
	}

	OnSelectTreeNode(nodeType,strText);
	
	*pResult = 0;
}


void COleDBDlg::OnRunQuery() 
{
	RunQuery();
	
}



BOOL COleDBDlg::OnOpenDatabaseConnection(int iDatabase)
{
	if( theApp.OpenDBConnDlg(iDatabase) != TRUE)
		return FALSE; 
	
	PopulateTree();
		return TRUE;
}

BOOL COleDBDlg::OnOpenDatabase(int iDatabase)
{
	if( theApp.OpenDB(iDatabase) != TRUE)
		return FALSE; 
	
	PopulateTree();
		return TRUE;
}


void COleDBDlg::OnDeltaposOledbSpinTable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if( pNMUpDown->iDelta < 0)
	{
		m_iTreeCtrlSize = m_iTreeCtrlSize + m_iSizeFactor;
		ModifyTreeCtrlSize(m_iTreeCtrlSize);
	}
	else
	{
		m_iTreeCtrlSize = m_iTreeCtrlSize - m_iSizeFactor;
		ModifyTreeCtrlSize(m_iTreeCtrlSize);
	}
	
	*pResult = 0;
}

void COleDBDlg::OnOledbCheckTable() 
{
	if ( BST_CHECKED == ((CButton*)GetDlgItem(IDC_OLEDB_CHECKTABLE))->GetCheck() )
	{
		ModifyTreeCtrlSize(m_iTreeCtrlSize);
		((CSpinButtonCtrl*)GetDlgItem(IDC_OLEDB_SPINTABLE))->ShowWindow(SW_SHOW);
	}
	else
	{
		HideSpinCtrl(0);
		((CSpinButtonCtrl*)GetDlgItem(IDC_OLEDB_SPINTABLE))->ShowWindow(SW_HIDE);
	}	

}
