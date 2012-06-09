// PropertiesBar.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "PropertiesBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertiesBar

CPropertiesBar::CPropertiesBar()
:COXSizeControlBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
}


CPropertiesBar::~CPropertiesBar()
{
}


BEGIN_MESSAGE_MAP(CPropertiesBar, COXSizeControlBar)
	//{{AFX_MSG_MAP(CPropertiesBar)
		ON_WM_CREATE()
		ON_WM_SIZE()
		//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTCTRL1, OnItemchangedList1)
		//ON_EN_CHANGE(IDC_EDIT_CUSTOM, OnChangeEditCustom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertiesBar message handlers
int CPropertiesBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	if (!m_wndPropertiesBar.Create(NULL, NULL, WS_VISIBLE | WS_CHILD, CRect(0,0,0,0), this/*,
		IDC_PROPERTIES*/))
	{
		return -1;
	}


	//COXSizeDialogBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
	// Uncomment the next line if you want to hide the combo box
	// m_wndPropertiesBar.ShowCombo(FALSE);

	// Put some items in the combo box
	for (int i = 0; i < 10; i++)
	{
		COMBOBOXEXITEM cbi;
		cbi.iItem = i;
		cbi.mask = CBEIF_TEXT;
		CString strText;
		strText.Format(_T("Item %d"), i);
		cbi.pszText = (TCHAR*)(LPCTSTR) strText;
		m_wndPropertiesBar.GetComboBoxEx().InsertItem(&cbi);
	}

	// Uncomment the next line if you want to hide the toolbar
	// m_wndPropertiesBar.ShowToolBar(FALSE);
	
	
	InitRuleProperties();

	return 0;
}



void CPropertiesBar::OnSize(UINT nType, int cx, int cy) 
{
	COXSizeControlBar::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rectClient;
	GetClientRect(rectClient);
	m_wndPropertiesBar.MoveWindow(rectClient);	
}

void CPropertiesBar::InitRuleProperties()
{
	ASSERT(::IsWindow(m_hWnd));	// this window must be already created	

	//Project Name
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Name:"),									// property name
		_T("Aipi Project1"),							// initail value
		_T("Shows the project name."),					// property description
		_T("Project"));									// category

	//Project Name
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("File:"),								// property name
		_T("Project1"),								// initail value
		_T("Shows the project file name."),			// property description
		_T("Project"));								// category

	//Project Full Path 
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Full Path:"),										// property name
		_T("D:\\Project AIPI VS6\\AIPI\\Aipi Projects"),		// initail value
		_T("Shows the rule full path file name."),				// property description
		_T("Project"),											// category
		&m_filenameEditor);										// editor window


//////////////////////////////////////////////////////////////////////////////////////////////////

	//Rule Name
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Name:"),									// property name
		_T("Rule1"),								// initail value
		_T("Shows the rule name."),					// property description
		_T("Rules"),								// category
		&m_textEditor);								// editor window


		// List of items
	CStringArray itemsType;
	itemsType.Add(_T("FUZZY"));
	itemsType.Add(_T("FUZZY_UNCERT"));
	itemsType.Add(_T("META"));
	itemsType.Add(_T("NORMAL"));
	itemsType.Add(_T("UNCERT"));
	
	
	//Rule Type
	m_listEditor.SetListItems(&itemsType, &m_wndPropertiesBar);	// set the list of items
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Type:"),										// property name
		_T("NORMAL"),										// initail value
		_T("Shows the rule inference type."),				// property description
		_T("Rules"),										// category
		&m_listEditor);										// editor window

	//Rule Weight
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Weight:"),										// property name
		_T("0.00"),											// initail value
		_T("Shows the rule weight."),						// property description
		_T("Rules"),										// category
		&m_numericEditor);									// editor window

	//Rule Certain Factor
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("C.F:"),											// property name
		_T("0.00"),											// initail value
		_T("Shows the rule certain factor."),				// property description
		_T("Rules"),										// category
		&m_numericEditor);									// editor window

	//Rule  Filename
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("File:"),										// property name
		_T("D:\\Project AIPI VS6\\AIPI\\Aipi Projects"),		// initail value
		_T("Shows the rule file name."),					// property description
		_T("Rules"),										// category
		&m_filenameEditor);									// editor window

}


void CPropertiesBar::InitFileProperties()
{
	ASSERT(::IsWindow(m_hWnd));	// this window must be already created

	//Project Name
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Name:"),									// property name
		_T("Aipi Project1"),							// initail value
		_T("Shows the project name."),					// property description
		_T("Project"));									// category

	//Project Name
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("File:"),								// property name
		_T("Project1"),								// initail value
		_T("Shows the project file name."),			// property description
		_T("Project"));								// category

	//Project Full Path 
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Full Path:"),										// property name
		_T("D:\\Project AIPI VS6\\AIPI\\Aipi Projects"),		// initail value
		_T("Shows the rule full path file name."),				// property description
		_T("Project"),											// category
		&m_filenameEditor);										// editor window

////////////////////////////////////////////////////////////////////////////////////////////////////
	//File Name
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Name:"),								// property name
		_T("Rule1"),								// initail value
		_T("Shows the rule name."),					// property description
		_T("File"),								// category
		&m_textEditor);								// editor window

	// List of items
	CStringArray itemsExt;
	itemsExt.Add(_T(".knw"));
	itemsExt.Add(_T(".txt"));
	itemsExt.Add(_T(".csv"));
	itemsExt.Add(_T(".jpg"));
	itemsExt.Add(_T(".bmp"));
	itemsExt.Add(_T(".mp3"));
	
	//File Extension
	m_listEditor.SetListItems(&itemsExt, &m_wndPropertiesBar);	// set the list of items
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Extension:"),										// property name
		_T(".knw"),										// initail value
		_T("Shows the extension of the file."),				// property description
		_T("File"),										// category
		&m_listEditor);										// editor window


	// List of items
	CStringArray itemsRs;
	itemsRs.Add(_T("Image"));
	itemsRs.Add(_T("Video"));
	itemsRs.Add(_T("Data"));
	itemsRs.Add(_T("Code"));
	
	//File Extension
	m_listEditor.SetListItems(&itemsRs, &m_wndPropertiesBar);	// set the list of items
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Resource:"),										// property name
		_T("Image"),										// initail value
		_T("Shows the file resource type."),				// property description
		_T("File"),										// category
		&m_listEditor);										// editor window


	//File Full Path 
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Full Path:"),										// property name
		_T("D:\\Project AIPI VS6\\AIPI\\Aipi Projects"),		// initail value
		_T("Shows the rule full path file name."),				// property description
		_T("File"),											// category
		&m_filenameEditor);										// editor window


	//File Relative Path 
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Relative Path:"),										// property name
		_T("D:\\Project AIPI VS6\\AIPI\\Aipi Projects"),		// initail value
		_T("Shows the rule relative path file name."),				// property description
		_T("File"),											// category
		&m_filenameEditor);										// editor window


}


void CPropertiesBar::InitFunctionProperties()
{
	ASSERT(::IsWindow(m_hWnd));	// this window must be already created

		//Project Name
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Name:"),									// property name
		_T("Aipi Project1"),							// initail value
		_T("Shows the project name."),					// property description
		_T("Project"));									// category

	//Project Name
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("File:"),								// property name
		_T("Project1"),								// initail value
		_T("Shows the project file name."),			// property description
		_T("Project"));								// category

	//Project Full Path 
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Full Path:"),										// property name
		_T("D:\\Project AIPI VS6\\AIPI\\Aipi Projects"),		// initail value
		_T("Shows the rule full path file name."),				// property description
		_T("Project"),											// category
		&m_filenameEditor);										// editor window

////////////////////////////////////////////////////////////////////////////////////////


	//Function Name
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Name:"),									// property name
		_T("Function1"),								// initail value
		_T("Shows the function name."),					// property description
		_T("Functions"),								// category
		&m_textEditor);								// editor window


	// List of items
	CStringArray itemsAcs;
	itemsAcs.Add(_T("public"));
	itemsAcs.Add(_T("private"));
	
	
	//Function Access
	m_listEditor.SetListItems(&itemsAcs, &m_wndPropertiesBar);	// set the list of items
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Access:"),										// property name
		_T("public"),										// initail value
		_T("Shows the function access."),				// property description
		_T("Functions"),										// category
		&m_listEditor);										// editor window


	// List of items
	CStringArray itemsRType;
	itemsRType.Add(_T("bool"));
	itemsRType.Add(_T("double"));
	itemsRType.Add(_T("float"));
	itemsRType.Add(_T("int"));
	itemsRType.Add(_T("void"));
	
	
	//Function Return Type
	m_listEditor.SetListItems(&itemsRType, &m_wndPropertiesBar);	// set the list of items
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Return Type:"),										// property name
		_T("void"),										// initail value
		_T("Shows the function return type."),				// property description
		_T("Functions"),										// category
		&m_listEditor);										// editor window


	//Function  Filename
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("File:"),										// property name
		_T("D:\\Project AIPI VS6\\AIPI\\Aipi Projects"),		// initail value
		_T("Shows the function file name."),					// property description
		_T("Functions"),										// category
		&m_filenameEditor);									// editor window

}


void CPropertiesBar::InitVariableProperties()
{
	ASSERT(::IsWindow(m_hWnd));	// this window must be already created

		//Project Name
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Name:"),									// property name
		_T("Aipi Project1"),							// initail value
		_T("Shows the project name."),					// property description
		_T("Project"));									// category

	//Project Name
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("File:"),								// property name
		_T("Project1"),								// initail value
		_T("Shows the project file name."),			// property description
		_T("Project"));								// category

	//Project Full Path 
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Full Path:"),										// property name
		_T("D:\\Project AIPI VS6\\AIPI\\Aipi Projects"),		// initail value
		_T("Shows the rule full path file name."),				// property description
		_T("Project"),											// category
		&m_filenameEditor);										// editor window

////////////////////////////////////////////////////////////////////////////////////////


	//Variable Name
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Name:"),									// property name
		_T("Function1"),								// initail value
		_T("Shows the function name."),					// property description
		_T("Variables"),								// category
		&m_textEditor);								// editor window


	// List of items
	CStringArray itemsAcs;
	itemsAcs.Add(_T("public"));
	itemsAcs.Add(_T("private"));
	
	
	//Variable Access
	m_listEditor.SetListItems(&itemsAcs, &m_wndPropertiesBar);	// set the list of items
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Access:"),										// property name
		_T("public"),										// initail value
		_T("Shows the function access."),				// property description
		_T("Variables"),										// category
		&m_listEditor);										// editor window


	// List of items
	CStringArray itemsType;
	itemsType.Add(_T("bool"));
	itemsType.Add(_T("double"));
	itemsType.Add(_T("float"));
	itemsType.Add(_T("int"));
	itemsType.Add(_T("void"));
	
	
	//Variable Type
	m_listEditor.SetListItems(&itemsType, &m_wndPropertiesBar);	// set the list of items
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Type:"),										// property name
		_T("void"),										// initail value
		_T("Shows the function return type."),				// property description
		_T("Variables"),										// category
		&m_listEditor);										// editor window


	//Variable  Filename
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("File:"),										// property name
		_T("D:\\Project AIPI VS6\\AIPI\\Aipi Projects"),		// initail value
		_T("Shows the function file name."),					// property description
		_T("Variables"),										// category
		&m_filenameEditor);									// editor window


}




void CPropertiesBar::InitQueryProperties()
{
	ASSERT(::IsWindow(m_hWnd));	// this window must be already created

}





void CPropertiesBar::InitProperties()
{
	
	
	ASSERT(::IsWindow(m_hWnd));	// this window must be already created

	
	
	// Text
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Text"),											// property name
		_T(""),												// initail value
		_T("Demonstrates the use of a text field."),		// property description
		_T("Data"),											// category
		&m_textEditor);										// editor window

	// Read-only field (no editor)
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Serial Number"),								// property name
		_T("K67-FR45-5"),									// initail value
		_T("Demonstrates the use of a read-only field."),	// property description
		_T("Data"));										// category

	// List of items
	CStringArray items;
	items.Add(_T("New York"));
	items.Add(_T("Chicago"));
	items.Add(_T("London"));
	items.Add(_T("Paris"));
	items.Add(_T("Toronto"));
	items.Add(_T("Berlin"));
	items.Add(_T("Rome"));
	items.Add(_T("Los Angeles"));

	m_listEditor.SetListItems(&items, &m_wndPropertiesBar);	// set the list of items
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("City"),											// property name
		_T(""),												// initail value
		_T("Demonstrates the use of a list field."),		// property description
		_T("Data"),											// category
		&m_listEditor);										// editor window

	// Number
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Number"),										// property name
		_T("0.00"),											// initail value
		_T("Demonstrates the use of a numeric field."),		// property description
		_T("Data3"),											// category
		&m_numericEditor);									// editor window

	// Phone number (using COXMaskedEdit)
	m_phoneNumberEditor.SetMask(_T("(###) ###-#### Ex.###"));
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Telephone"),									// property name
		_T("(   )    -     Ex."),							// initail value
		_T("Demonstrates the use of a masked field."),		// property description
		_T("Data"),											// category
		&m_phoneNumberEditor);								// editor window

	// Currency
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Currency"),										// property name
		_T("$0.00"),										// initail value
		_T("Demonstrates the use of a currency field."),	// property description
		_T("Data"),											// category
		&m_currencyEditor);									// editor window

	// IP Address
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("IP Address"),									// property name
		_T(""),												// initail value
		_T("Demonstrates the use of a ip address field."),	// property description
		_T("Data"),											// category
		&m_ipAddressEditor);								// editor window

	// Date (use "dd" to specify the day, "mm" to specify the month
	// and either "yy" or "yyyy" to specify the year)
	m_dateEditor.SetDateFormat(_T("dd/mm/yyyy"));
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Date"),											// property name
		_T(""),												// initail value
		_T("Demonstrates the use of a date field."),		// property description
		_T("Data"),											// category
		&m_dateEditor);										// editor window

	// Time
	hProperty= m_wndPropertiesBar.InsertProperty(
		_T("Time"),											// property name
		_T("1.00 s"),										// initail value
		_T("Demonstrates the use of a time field."),		// property description
		_T("Physical Fields"),								// category
		&m_timeEditor);										// editor window
	
	// Angle
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Angle"),										// property name
		_T("0.00 °"),										// initail value
		_T("Demonstrates the use of an angle field."),		// property description
		_T("Physical Fields"),								// category
		&m_angleEditor);									// editor window
	
	// Length
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Length"),										// property name
		_T("0.00 m"),										// initail value
		_T("Demonstrates the use of a length field."),		// property description
		_T("Physical Fields"),								// category
		&m_lengthEditor);									// editor window
	
	// Temperature
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Temperature"),									// property name
		_T("0.00 °C"),										// initail value
		_T("Demonstrates the use of a temparature field."),	// property description
		_T("Physical Fields"),								// category
		&m_temperatureEditor);								// editor window

	// Color
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Color"),										// property name
		_T("None"),											// initail value
		_T("Demonstrates the use of a color field."),		// property description
		_T("Miscellaneous"),								// category
		&m_colorEditor);									// editor window

	// Calculator
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Calculator"),									// property name
		_T("0.00"),											// initail value
		_T("Demonstrates the use of a calculator field."),	// property description
		_T("Miscellaneous"),								// category
		&m_calculatorEditor);								// editor window

	// Directory
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Directory"),									// property name
		_T(""),												// initail value
		_T("Demonstrates the use of a directory field."),	// property description
		_T("Miscellaneous"),								// category
		&m_directoryEditor);								// editor window

	// Filename
	hProperty = m_wndPropertiesBar.InsertProperty(
		_T("Filename"),										// property name
		_T(""),												// initail value
		_T("Demonstrates the use of a filename field."),	// property description
		_T("Miscellaneous"),								// category
		&m_filenameEditor);									// editor window

  
}


void CPropertiesBar::InsertEditProperty(CString name, CString desc, CString categ)
{
	ASSERT(::IsWindow(m_hWnd));	// this window must be already created
	
	// Text
	hProperty= m_wndPropertiesBar.InsertProperty(name, _T(""), desc, categ, &m_textEditor);
				
}


void CPropertiesBar::EditPropertyValue(CString name, CString categ, CString value)
{
	HPROPERTY hProperty = m_wndPropertiesBar.FindProperty(name, categ);
	if( hProperty != NULL )
	{
		m_wndPropertiesBar.SetPropertyValue(hProperty, value);
	}

}



BOOL CPropertiesBar::OnPropertyValueChanged(HPROPERTY hProperty, LPCTSTR lpszOldValue, LPCTSTR lpszNewValue)
{
	
	//AfxMessageBox(_T("Hi"));

return TRUE;
}
