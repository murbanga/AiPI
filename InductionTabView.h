#if !defined(AFX_INDUCTIONTABVIEW_H__D1FD7E00_CBFA_4072_8016_7B5556A79CC3__INCLUDED_)
#define AFX_INDUCTIONTABVIEW_H__D1FD7E00_CBFA_4072_8016_7B5556A79CC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InductionTabView.h : header file
//
#include ".\ScintillaWnd\ScintillaWnd.h"
#include ".\SQLQuery\SQLQuery.h"
#include ".\DataFileCSV\CDataFile.h"
#include ".\BasicExcel\BasicExcelVC6.hpp"
#include ".\NSChart\NSChartCtrl.h"



#include "OXSizeDlgBar.h"
#include "OXLayoutManager.h"
#include "OXCoolCtrl.h"
#include "OXBitmapButton.h"
#include "OXSeparator.h"
#include "OX3DTabView.h"


#include "PageFileDlg.h"
#include "PageEditDlg.h"
#include "PageInsertDlg.h"
#include "PageFormatDlg.h"
#include "PageOptionsDlg.h"
#include "PageCellSizeDlg.h"


//ComboListCtrl
#include ".\ComboListCtrl\ComboListCtrl.h"
#include ".\ComboListCtrl\InPlaceEditCombo.h"
//GridCtrl
#include ".\GridCtrl\GridCtrl.h"
//RollupCtrl
#include "RollupCtrl.h"

#include <algorithm>
#include <numeric>
#include <vector>
#include <functional>


// AFXEXT
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif


#include <cmath>

#define INDEX_COMBO				1
#define INT_DISCRETE			10
#define INT_CONTINUE			11
#define INT_DISCRETE_CUSTOM		12
#define INT_CONTINUE_CUSTOM		13


//#include "OXSkinnedView.h"
/////////////////////////////////////////////////////////////////////////////
// CInductionTabView dialog
//#define BASEVIEW COXSizeDialogBar

class CInductionTabView : public COXSizeDialogBar
{

	DECLARE_DYNAMIC(CInductionTabView);

	// Construction
public:
	CInductionTabView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInductionTabView();
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	//int CInductionTabView::InsertItemList1( int iItem, int iSubItem, LPTSTR szText);
	//int CInductionTabView::InsertItemList2( int iItem, int iSubItem, LPTSTR szText);

// Dialog Data
	//{{AFX_DATA(CInductionTabView)
	enum { IDD = IDD_INDUCTION_FRAME_DLG };
	
	COXSeparator			m_stcSelAtributes;
	COXSeparator			m_stcAtributes;
	COXSeparator            m_stcGraph;
	CListCtrl				m_ListCtrl2;
	CComboListCtrl			m_ListCtrl1;
	CTabCtrl				m_TabCtrl;
	CTreeCtrl				m_treeCtrl;
	COXSeparator			m_stcQuery;
	COXSeparator			m_stcData;
	COXSeparator			m_stcTables;
	


	COXCoolButton			m_checkGraph;
	COXCoolButton			m_checkValues;
	COXCoolSpinButtonCtrl	m_spinTable;
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


public:
//CGridCtrl vars
	
	int		m_nFixCols;
	int		m_nFixRows;
	int		m_nCols;
	int		m_nRows;
	BOOL    m_bRejectEditAttempts;
    BOOL    m_bRejectEditChanges;

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInductionTabView)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL ScintillaNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

//Atributes
public:
	CImageList				m_TabImageList;	
	CImageList				m_ImageList1;
	CImageList				m_ImageList2;
	COXLayoutManager		m_LayoutManager;
	CRollupCtrl				m_RollupCtrl;
	CScintillaWnd			m_ScinCtrl;
	CNSChartCtrl			m_Chart;
	
	CSize					m_OldSize;
	BOOL					m_blInited;

	CPageFileDlg*			m_pFileDlg;
	
	
	int m_iItemCount;
	float nClasses;
	CString m_szMissingData;	

// Implementation
public:
	
	void CreateTab();
	void UpdatePageOptionDlg();
	void UpdatePageFormatDlg();
	void UpdatePageFileDlg();
	void UpdatePageEditDlg();
	void UpdatePageCellSizeDlg(); 
	void UpdateMenuUI();
	void InitScintilla();
	BOOL InitLayoutManager();
	void InitPages();
	void InitLayoutManagerPage2();
	void InitLayoutManagerPage1();
	void Hide_Page1();
	void Hide_Page2();
	void ActualInterfacePage1(int actualWnd);
	void ActualInterfacePage2(int actualWnd);

	void Init_Atributes_AtributeValues_Page1();
	void Init_Atributes_AtributeValues_Graph_Page1();
	void Init_Atributes_Page1();
	void Init_Atributes_Graph_Page1();
	
	void Init_Query_Tables_Data_Page2();
	void Init_Query_Page2();
	void Init_Tables_Page2();
	void Init_Data_Page2();
	void Init_Query_Tables_Page2();
	void Init_Query_Data_Page2();
	void Init_Tables_Data_Page2();
	void Init_VTables_Data_Page2();
	void Init_Query_VTables_Data_Page2();
	void ChangeInterfacesPage1();	
	void ChangeVTablesSize(int pos);



	BOOL CInductionTabView::TabToolTips(UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	void CreateList1();
	void CreateNominalList2();
	void CreateNumericList2();

public:

	LVITEM CInductionTabView::AddListItem1( int iItem, int iSubItem, LPTSTR szText);	
	LVITEM CInductionTabView::AddListItem2( int iItem, int iSubItem, LPTSTR szText, int iImage);
	void CInductionTabView::AddListSubItem1( LVITEM item, int iItem, int iSubItem, LPTSTR szText);
	void CInductionTabView::AddListSubItem2( LVITEM item, int iItem, int iSubItem, LPTSTR szText);
	void PopulateList1();
	void PopulateList2();
	
	LPTSTR Conv_StrToLPTSTR(std::tstring str);
	void StopTimer(CPerfTimer t, CString msg);
	void Stat_NominalFrequency(int idAtribute);
	void Stat_NominalFreqMap(int idAtribute);
	void Stat_NomFreqSTL(int idAtribute);
	void Stat_NominalFrequencySTL(int idAtribute);
	void Stat_NominalFrequencyDesc(int idAtribute);
	void Stat_NumericFrequency(int idAtribute, int type);
	void Stat_NumericFrequencySTL(int idAtribute, int type);
	void Stat_NumericFrequencyDesc(int idAtribute, int type);
	void Stat_AtributeFrequency(int idAtribute, CString strType);
	bool Stat_ClassesCondSTL(double dblValue);
	void NSChart_DrawChart();
	void NSChart_OnChartSelectedItem(NMHDR* pNMHDR, LRESULT* pResult);
	CString NSChart_GetAtributeValueName(CString label);
	

//CGridCtrl
public:
	void InitGridCtrl();
	void Trace(LPCTSTR szFmt, ...);
	void ClearTrace();

//DataBase Enumerations

enum UpdateHints
{
	HINT_UPDATE_WINDOW,
	HINT_ON_QUERY_RESULT_READY,
	HINT_ON_NODE_SELECTED,
};


typedef enum
{
	TNode_None,
	TNode_RootDatabase,
	TNode_RootTables,
	TNode_TableName,

} TreeNodeTypeDB;

enum InductionWnd
{
	//Page1
	ATRIBUTES = 0,
	ATRIBUTES_ATRIBUTEVALUES,
	ATRIBUTES_GRAPH,
	ATRIBUTES_ATRIBUTEVALUES_GRAPH,
	//Page2
	QUERY,
    TABLES,
	DATA,
	QUERY_DATA,
	QUERY_TABLES,
	TABLES_DATA,
	VTABLES_DATA,
	QUERY_TABLES_DATA,
	QUERY_VTABLES_DATA

		

};
		
enum InductionWnd m_eIntPage1;
enum InductionWnd m_eIntPage2;

//DataBase
	 void OnSelectTreeNode(TreeNodeTypeDB node, const CString strText);
	 void ShowQueryResult();
	 void ShowColumns();
	 void PopulateTree();
	 void RunQuery();
	 void QueryUnFixed();
	 void QueryFixed();
	 int  LA_isNumeric(CString t);
	 void OnUpdateRunQuery(CCmdUI* pCmdUI);
	 BOOL OnOpenDatabaseConnection(int iBatabase);
	 void ModifyTreeCtrlSize(int iSize); 
	 void HideSpinCtrl(int iSize);
	 void UnCheckListCtrl1();

//DataBase Vars
	CImageList      m_imageList;
	CString			m_strQuery;
	CString			m_strSelNodeName;
	CSQLQuery		m_query;
	TreeNodeTypeDB	m_hSelNodeType;
	CFont			m_queryFont;

	int				m_iVTablesPos;
	int				m_iSizeFactor;

//RollupCtrl Pages
	CPageFileDlg		*pFilePage;
	CPageEditDlg		*pEditPage;
	CPageInsertDlg		*pInsertPage;
	CPageFormatDlg		*pFormatPage;
	CPageOptionsDlg		*pOptionsPage;
	CPageCellSizeDlg	*pCellSizePage;
	
	


	// Generated message map functions
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
	//{{AFX_MSG(CInductionTabView)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInductionCheckGraph();
	afx_msg void OnInductionCheckValues();
	afx_msg void OnChangeEditQuery();
	afx_msg void OnSelchangedTreeCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposInductionSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	//afx_msg LRESULT OnEndLabelEditVariableCriteria(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT PopulateComboList(WPARAM wParam, LPARAM lParam);
	//Grid Mouse Events
	afx_msg void OnGridDblClick(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridClick(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridRClick(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridStartEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridEndEdit(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridStartSelChange(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridEndSelChange(NMHDR *pNotifyStruct, LRESULT* pResult);
    afx_msg void OnGridBeginDrag(NMHDR *pNotifyStruct, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INDUCTIONTABVIEW_H__D1FD7E00_CBFA_4072_8016_7B5556A79CC3__INCLUDED_)
