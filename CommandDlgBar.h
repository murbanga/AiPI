#if !defined(AFX_COMMANDDLGBAR_H__37FCB55C_117E_41F3_98D2_2F98BE7257C4__INCLUDED_)
#define AFX_COMMANDDLGBAR_H__37FCB55C_117E_41F3_98D2_2F98BE7257C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommandDlgBar.h : header file
//
#include "OXCoolCtrl.h"
#include "OXCoolComboBox.h"
#include "OXLayoutManager.h"
#include "OXSizeDlgBar.h"

#include    "Input.h"
#include "Aipi_ExpParserFileGlobal.h"
#include "Aipi_ExpParserFile.h"
#include "Aipi_ExpParserGUIGlobal.h"
#include "Aipi_ExpParserGUI.h"
/////////////////////////////////////////////////////////////////////////////
// CCommandDlgBar dialog

class CCommandDlgBar : public CDialogBar
{


// Construction
public:
	CCommandDlgBar();   // standard constructor
	virtual ~CCommandDlgBar();
		
	BOOL Create(CWnd* pParentWnd, UINT nIDTemplate,	UINT nStyle, UINT nID, BOOL = TRUE);
	BOOL Create(CWnd* pParentWnd, LPCTSTR lpszTemplateName, UINT nStyle, UINT nID, BOOL = TRUE);

	//COXCoolComboBox			m_Combo;
	//COXCoolCtrl<CStatic>    m_Label;
	CInput					m_wndInput;
	//CComboBox				m_Combo;
	CStatic					m_Label;
	COXLayoutManager		m_LayoutManager;
	
	
	BOOL InitLayoutManager();

public :
	CSize m_sizeDocked;
	CSize m_sizeFloating;
	BOOL m_bChangeDockedSize;
	int  m_tkzIndex1;
	int  m_tkzIndex2;


	protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags);
	virtual CSize CalcDynamicLayout(int nLength, DWORD dwWord);


// Implementation
protected:
	//{{AFX_MSG(CCommandDlgBar)
	
	//}}AFX_MSG
	afx_msg LRESULT UserMsg(WPARAM n1, LPARAM n2);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDDLGBAR_H__37FCB55C_117E_41F3_98D2_2F98BE7257C4__INCLUDED_)
