#if !defined(AFX_PAGEFILEDLG_H__5D09BD92_34F4_42A3_BA84_CE84F7EBD7B1__INCLUDED_)
#define AFX_PAGEFILEDLG_H__5D09BD92_34F4_42A3_BA84_CE84F7EBD7B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageFileDlg.h : header file
//
#include "PageInsertDlg.h"
#include "OXCoolCtrl.h"
#include "OXSeparator.h"
#include ".\GridCtrl\GridCtrl.h"

#include ".\DataFileCSV\CDataFile.h"
#include ".\BasicExcel\BasicExcelVC6.hpp"
//ComboListCtrl
#include ".\ComboListCtrl\ComboListCtrl.h"
#include ".\ComboListCtrl\InPlaceEditCombo.h"
#include "AIPI_DecisionTree/Aipi_DT_ID3.h"


/////////////////////////////////////////////////////////////////////////////
// CPageFileDlg dialog
class CGridCtrl;


class CPageFileDlg : public CDialog
{
// Construction
public:
	CPageFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageFileDlg)
	enum { IDD = IDD_PAGEFILE_DLG };
	CStatic	m_nRows;
	CStatic	m_nCols;
	
	COXCoolButton	m_chkTables;
	COXCoolButton	m_chkQuery;
	COXCoolButton	m_chkData;
	COXCoolButton	m_chkVTables;
	
	COXSeparator	m_stcSeparator02;
	COXSeparator	m_stcSeparator03;
	COXSeparator	m_stcSeparator04;
	COXSeparator	m_stcSeparator05;
	COXSeparator	m_stcSeparator;
	
	COXCoolButton	m_btnOpenFile;
	COXCoolButton	m_btnConnectDB;
	COXCoolButton   m_btnExecQuery;
	COXCoolButton	m_chkVirtualMode;
	COXCoolButton	m_chkCallback;
	//}}AFX_DATA
	CGridCtrl			*m_pGrid;
	CPageInsertDlg		*pInsertPage;
	//CInductionTabView   *pTab;
	CComboListCtrl		*m_pListCtrl1;
	CListCtrl			*m_pListCtrl2;
	



	
private:
	//void	SelectGrid();
	int		LA_isNumeric(CString t);
	void	StopTimer(CPerfTimer t, CString msg);
	LVITEM	CPageFileDlg::AddListItem1( int iItem, int iSubItem, LPTSTR szText);	
	LVITEM	CPageFileDlg::AddListItem2( int iItem, int iSubItem, LPTSTR szText, int iImage);
	void	CPageFileDlg::AddListSubItem1( LVITEM item, int iItem, int iSubItem, LPTSTR szText);
	void	CPageFileDlg::AddListSubItem2( LVITEM item, int iItem, int iSubItem, LPTSTR szText);
	void	ChangeInterfacesPage2();
	void	UnCheckListCtrl1();

public:
	static BOOL CALLBACK GridCallback(GV_DISPINFO *pDispInfo, LPARAM lParam);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageFileDlg)
	afx_msg void OnBtnOpenFile();
	afx_msg void OnBtnConnectDB();
	
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBtnSaveAs();
	afx_msg void OnCheckViewQuery();
	afx_msg void OnCheckViewTables();
	afx_msg void OnCheckViewData();
	afx_msg void OnCheckTableV();
	afx_msg void OnBtnExecQuery();

	afx_msg void OnChkVirtualMode();
	afx_msg void OnChkCallback();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEFILEDLG_H__5D09BD92_34F4_42A3_BA84_CE84F7EBD7B1__INCLUDED_)
