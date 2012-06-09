#if !defined(AFX_PROPERTIESBAR_H__BB4A1201_45ED_4D1B_9C99_F3839FCA8407__INCLUDED_)
#define AFX_PROPERTIESBAR_H__BB4A1201_45ED_4D1B_9C99_F3839FCA8407__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertiesBar.h : header file
//
#include "OXSizeCtrlBar.h"
#include "OXPropertiesWnd.h"	// Added by ClassView

#include "OXEdit.h"
#include "OXPhysicalEditEx.h"
#include "OXCalculatorEdit.h"
#include "OXBrowseDirEdit.h"
#include "OXListEdit.h"
#include "OXCalendarEdit.h"
#include "OXIPEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CPropertiesBar window

class CPropertiesBar : public COXSizeControlBar
{
// Construction
public:
	CPropertiesBar();

// Attributes
public:
	COXPropertiesWnd m_wndPropertiesBar;

	HPROPERTY hProperty;
	// Editor instances
	COXEdit				m_textEditor;
	COXListEdit			m_listEditor;
	COXNumericEdit		m_numericEditor;
	COXMaskedEdit		m_phoneNumberEditor;
	COXCurrencyEdit		m_currencyEditor;
	COXIPEdit			m_ipAddressEditor;
	COXCalendarEdit		m_dateEditor;
	COXTimeEdit			m_timeEditor;
	COXAngleEdit		m_angleEditor;
	COXLengthEdit		m_lengthEditor;
	COXTempEdit			m_temperatureEditor;
	COXBrowseColorEdit	m_colorEditor;
	COXCalculatorEdit	m_calculatorEditor;
	COXBrowseDirEdit	m_directoryEditor;
	COXBrowseFileEdit	m_filenameEditor;
// Operations
public:
	void InitProperties();
	
	void InitRuleProperties();
	void InitFileProperties();
	void InitFunctionProperties();
	void InitQueryProperties();
	void InitVariableProperties();

	void InsertEditProperty(CString name, CString desc, CString categ); 
	void EditPropertyValue(CString proName, CString proCateg, CString proValue);	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesBar)
		virtual BOOL OnPropertyValueChanged(HPROPERTY hProperty, LPCTSTR lpszOldValue, LPCTSTR lpszNewValue);

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropertiesBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropertiesBar)
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIESBAR_H__BB4A1201_45ED_4D1B_9C99_F3839FCA8407__INCLUDED_)
