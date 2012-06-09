#if !defined(AFX_OLEDBCONNECTIONDLG_H__4EE0A12C_3F53_4B99_BA0A_C2D34B5D4BE0__INCLUDED_)
#define AFX_OLEDBCONNECTIONDLG_H__4EE0A12C_3F53_4B99_BA0A_C2D34B5D4BE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OleDBConnectionDlg.h : header file
//
#include "Resource.h"
#include "OleDBConnectionProp.h"
#include "OXCoolCtrl.h"
#include "OXBitmapButton.h"
#include "Aipi_ParserGUI.h"

/////////////////////////////////////////////////////////////////////////////
// COleDBConnectionDlg dialog

class COleDBConnectionDlg : public CDialog
{
// Construction
public:
	COleDBConnectionDlg(CWnd* pParent = NULL,bool bOleDBSupport = true);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COleDBConnectionDlg)
	enum { IDD = IDD_OLEDB_CONNECTION_DLG };
	COXCoolButton	m_radioDB2;
	COXCoolButton	m_radioMSAccess;
	COXCoolButton	m_radioMSSql;
	COXCoolButton	m_radioMSOracle;
	COXCoolButton	m_radioMySql;
	COXCoolButton	m_radioOracle;
	
	//}}AFX_DATA

	COleDBConnectionProp	m_props;
	CString					m_strDataSourceCaption;
	int						m_iDBType;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COleDBConnectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool IsValidPassword();
	bool	m_bInit;
	bool	m_bOleDBSupport;

	// Generated message map functions
	//{{AFX_MSG(COleDBConnectionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEdit();
	afx_msg void OnBtnOledbBrowse();
	afx_msg void OnRadioDB2();
	afx_msg void OnRadioMSAccess();
	afx_msg void OnRadioMSSql();
	afx_msg void OnRadioMSOracle();
	afx_msg void OnRadioMySql();
	afx_msg void OnRadioOracle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OLEDBCONNECTIONDLG_H__4EE0A12C_3F53_4B99_BA0A_C2D34B5D4BE0__INCLUDED_)
