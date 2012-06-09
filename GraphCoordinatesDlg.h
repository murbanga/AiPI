#if !defined(AFX_GRAPHCOORDINATESDLG_H__5D1DD0F1_3B1E_429A_8848_5D531BAC11C2__INCLUDED_)
#define AFX_GRAPHCOORDINATESDLG_H__5D1DD0F1_3B1E_429A_8848_5D531BAC11C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphCoordinatesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphCoordinatesDlg dialog

class CGraphCoordinatesDlg : public CDialog
{
// Construction
public:
	CGraphCoordinatesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGraphCoordinatesDlg)
	enum { IDD = IDD_GRAPH_COORDINATES_DLG };
	double	m_x1;
	double	m_x2;
	double	m_y1;
	double	m_y2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphCoordinatesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphCoordinatesDlg)
			virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHCOORDINATESDLG_H__5D1DD0F1_3B1E_429A_8848_5D531BAC11C2__INCLUDED_)
