#if !defined(AFX_GRAPHAXISDLG_H__38CA2D87_A990_497F_8724_A544C6A8F91D__INCLUDED_)
#define AFX_GRAPHAXISDLG_H__38CA2D87_A990_497F_8724_A544C6A8F91D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphAxisDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphAxisDlg dialog

class CGraphAxisDlg : public CDialog
{
// Construction
public:
	CGraphAxisDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGraphAxisDlg)
	enum { IDD = IDD_GRAPH_AXIS_DLG };
	CString	m_x_title;
	CString	m_y_title;
	CString	m_x_uom;
	CString	m_y_uom;
	int		m_x_precision;
	int		m_y_precision;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphAxisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphAxisDlg)
		virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHAXISDLG_H__38CA2D87_A990_497F_8724_A544C6A8F91D__INCLUDED_)
