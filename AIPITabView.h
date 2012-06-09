#if !defined(AFX_AIPITABVIEW_H__57BEA730_F768_43D4_8246_36C45EBC31DE__INCLUDED_)
#define AFX_AIPITABVIEW_H__57BEA730_F768_43D4_8246_36C45EBC31DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AIPITabView.h : header file
//
#include ".\ScintillaWnd\ScintillaWnd.h"
#include ".\DataFileCSV\CDataFile.h"

#include "OXSizeDlgBar.h"
#include "OXLayoutManager.h"
#include "OXCoolCtrl.h"
#include "OXBitmapButton.h"
#include "OXSeparator.h"
#include "OX3DTabView.h"

//GridCtrl
#include ".\GridCtrl\GridCtrl.h"
//RollupCtrl
#include "RollupCtrl.h"

#include "PageFileDlg.h"
#include "PageEditDlg.h"
#include "PageInsertDlg.h"
#include "PageFormatDlg.h"
#include "PageOptionsDlg.h"
#include "PageCellSizeDlg.h"


#include "AIPI_Engine/Aipi_WM.h"
#include "AIPI_Engine/Aipi_LHS.h"
#include "AIPI_Engine/Aipi_RETE_AM.h"
#include "AIPI_Engine/Aipi_RETE_BM.h"
#include "AIPI_Engine/Aipi_RETE_BME.h"
#include "AIPI_Engine/Aipi_RETE_BMCond.h"
#include "AIPI_Engine/Aipi_RETE_TK.h"
#include "AIPI_Engine/Aipi_RETE_JNode.h"
#include "AIPI_Engine/Aipi_RETE_PNode.h"
#include "AIPI_Engine/Aipi_RETE_NNode.h"
#include "AIPI_Engine/Aipi_RETE_NCCNode.h"
#include "AIPI_Engine/Aipi_RETE_Node.h"
#include "AIPI_Engine/Aipi_RETE_NodeCond.h"
#include "AIPI_Engine/Aipi_RETE_NumVars.h"



/////////////////////////////////////////////////////////////////////////////
// CAIPITabView dialog

class CAIPITabView : public COXSizeDialogBar
{
	DECLARE_DYNAMIC(CAIPITabView);

	
// Construction
public:
	CAIPITabView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAIPITabView();
	void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Dialog Data
	//{{AFX_DATA(CAIPITabView)
	enum { IDD = IDD_AIPI_FRAME_DLG };
	CStatic	m_stcLabelRange;
	COXCoolButton	m_btnViewRange;
	COXCoolButton	m_btnViewAll;
	CTabCtrl		m_TabCtrl;
	COXSeparator	m_Stc_Range;
	COXSeparator	m_Stc_Aipi_Data;
	int		m_iMaxRange;
	int		m_iMinRange;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	// Generated message map functions
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
	//{{AFX_VIRTUAL(CAIPITabView)
	public:
	
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	//}}AFX_VIRTUAL

public:
	CImageList				m_TabImageList;	
	CRollupCtrl				m_RollupCtrl;
	CGridCtrl				m_GridLHS;
	CGridCtrl				m_GridRHS;
	CGridCtrl				m_GridWM;
	CGridCtrl				m_GridCondLink;
	CGridCtrl				m_GridAM;
	CGridCtrl				m_GridBM;
	CGridCtrl				m_GridBM_TK;
	CGridCtrl				m_GridRETE;
	CGridCtrl				m_GridAgenda;

	//Memories range
	int					m_iMinRange_LHS;
	int					m_iMaxRange_LHS;
	int					m_iMinRange_RHS;
	int					m_iMaxRange_RHS;
	int					m_iMinRange_WM;
	int					m_iMaxRange_WM;
	int					m_iMinRange_CLink;
	int					m_iMaxRange_CLink;
	int					m_iMinRange_Agenda;
	int					m_iMaxRange_Agenda;
	int					m_iMinRange_AM;
	int					m_iMaxRange_AM;
	int					m_iMinRange_BM;
	int					m_iMaxRange_BM;
	int					m_iMinRange_BM_TK;
	int					m_iMaxRange_BM_TK;
	int					m_iMinRange_RETE;
	int					m_iMaxRange_RETE;


	COXLayoutManager		m_LayoutManager;



// Implementation
protected:
	
	void	CreateTab();
	BOOL	InitLayoutManager();
	BOOL	CAIPITabView::TabToolTips(UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	void	StopTimer(CPerfTimer t, CString msg);
	void	Trace(LPCTSTR szFmt, ...);
	void	ClearTrace();

	void	Init_Page();
	void	InitGridLHS(int n_row,int n_col);
	void	InitGridRHS(int n_row,int n_col);
	void	InitGridWM(int n_row, int n_col);
	void	InitGridAgenda(int n_row, int n_col);
	void    InitGridCondLink(int n_row, int n_col); 
	void	InitGridAM(int n_row, int col);
	void	InitGridBM(int n_row, int n_col);
	void	InitGridBM_TK(int n_row, int n_col);
	void	InitGridRETE(int n_row, int n_col);
	void	InitGridCtrls();
	int		FillGridLHS();
	int		FillGridRHS();
	int		FillGridWM(); 
	int		FillGridCondLink(); 
	int		FillGridAgenda();
	int		FillGridAM();
	int		FillGridBM();
	int		FillGridBM_TK();
	int		FillGridRETE();

	void	FillRangeGridLHS();
	void	FillRangeGridRHS();
	void	FillRangeGridWM();
	void	FillRangeGridCondLink();
	void	FillRangeGridAgenda();
	void	FillRangeGridAM();
	void	FillRangeGridBM();
	void	FillRangeGridBM_TK();
	void	FillRangeGridRETE();


	void	ClickGridLHS(int row, int col);
	void	ClickGridRHS(int row, int col);
	void	ClickGridWM(int row, int col);
	void	ClickGridCondLink(int row, int col);
	void	ClickGridAgenda(int row, int col);
	void	ClickGridAM(int row, int col);
	void	ClickGridBM(int row, int col);
	void	ClickGridBM_TK(int row, int col);	
	void	ClickGridRETE(int row,int col);

	
public:	
	void UpdatePageOptionDlg();
	void UpdatePageFormatDlg();
	void UpdatePageEditDlg();
	void UpdatePageCellSizeDlg(); 
	void UpdateMenuUI();
	
	

public:
	int				m_nFixCols;
	int				m_nFixRows;
	int				m_nCols;
	int				m_nRows;
	vector<int>		m_vTempRepCond;
	vector<int>		m_vTempWM;
	vector<int>		m_vTempPM;
	vector<int>		m_vTempBM;
	BOOL			m_bRejectEditAttempts;
    BOOL			m_bRejectEditChanges;
	
	
	CPageEditDlg *pEditPage;
	CPageInsertDlg *pInsertPage;
	CPageFormatDlg *pFormatPage;
	CPageOptionsDlg *pOptionsPage;
	CPageCellSizeDlg *pCellSizePage;
		

// Generated message map functions
	//{{AFX_MSG(CAIPITabView)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeAipiTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnRange();
	afx_msg void OnBtnAll();
	//}}AFX_MSG
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

#endif // !defined(AFX_AIPITABVIEW_H__57BEA730_F768_43D4_8246_36C45EBC31DE__INCLUDED_)





