#if !defined(AFX_CHARTSERIEPROPDLG_H__A38E63E6_E0A0_44F4_BCDE_34D584B9B81E__INCLUDED_)
#define AFX_CHARTSERIEPROPDLG_H__A38E63E6_E0A0_44F4_BCDE_34D584B9B81E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChartSeriePropDlg.h : header file
//
#include <string>
#include "ColourPicker.h"
/////////////////////////////////////////////////////////////////////////////
// CChartSeriePropDlg dialog

class CChartSeriePropDlg : public CDialog
{
// Construction
public:
	CChartSeriePropDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChartSeriePropDlg)
	enum { IDD = IDD_CHART_SERIESPROP_DLG };
	CComboBox	m_VertAxisCombo;
	CComboBox	m_HorizAxisCombo;
	CColourPicker	m_ColourSelect;
	CComboBox	m_SeriesTypeCombo;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChartSeriePropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChartSeriePropDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectLineData();
	afx_msg void OnSelectRandomData();
	afx_msg void OnSelectSineData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
#ifdef _UNICODE
	std::wstring m_strSeriesName;
#else
	std::string m_strSeriesName;
#endif

	int			m_iSeriesType;
	COLORREF	m_SeriesColour;

	int m_iVertAxis;
	int m_iHorizAxis;
	
	int m_iDataType;
	int m_iPointsNumber;
	float m_fMaxXValue;
	float m_fMinXValue;

	//Line data:
	float m_fLineSlope;
	float m_fLineOffset;

	// Sine wave data:
	float m_fSineAmplitude;
	float m_fSinePeriod;

	// Random values data:
	int m_iRandMinVal;
	int m_iRandMaxVal;

};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTSERIEPROPDLG_H__A38E63E6_E0A0_44F4_BCDE_34D584B9B81E__INCLUDED_)
