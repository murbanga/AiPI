// ChartSeriePropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ChartSeriePropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartSeriePropDlg dialog


CChartSeriePropDlg::CChartSeriePropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartSeriePropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartSeriePropDlg)
		
	//}}AFX_DATA_INIT
	m_iHorizAxis = m_iVertAxis = 0;
	m_iSeriesType = 0;
	m_SeriesColour = 0;
	m_iDataType = 0;
	m_fMaxXValue = m_fMinXValue = 0.0;
	m_iPointsNumber = 0;

	m_iRandMinVal = m_iRandMaxVal = 0;
	m_fSineAmplitude = m_fSinePeriod = 0;
	m_fLineSlope = m_fLineOffset = 0;
}


void CChartSeriePropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartSeriePropDlg)
	DDX_Control(pDX, IDC_VERTICALAXIS_COMBO, m_VertAxisCombo);
	DDX_Control(pDX, IDC_HORIZONTALAXIS_COMBO, m_HorizAxisCombo);
	DDX_Control(pDX, IDC_SERIESCOLOUR_BTN, m_ColourSelect);
	DDX_Control(pDX, IDC_SERIESTYPE_COMBO, m_SeriesTypeCombo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartSeriePropDlg, CDialog)
	//{{AFX_MSG_MAP(CChartSeriePropDlg)
	ON_BN_CLICKED(IDC_LINEDATA_RADIO, OnSelectLineData)
	ON_BN_CLICKED(IDC_RANDOMDATA_RADIO, OnSelectRandomData)
	ON_BN_CLICKED(IDC_SINEDATA_RADIO, OnSelectSineData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartSeriePropDlg message handlers
void CChartSeriePropDlg::OnOK() 
{
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	_TCHAR szName[255];
	GetDlgItem(IDC_SERIESNAME_EDIT)->GetWindowText(szName,254);
	for(int i=0; i<255; i++)
	{
		if( szName[i] != 'Ì')
		{
			m_strSeriesName += szName[i];
		}
	}
	
	
	if (_tcscmp(szName,_T("")) == 0)
	{
		
		switch (dwLanguageID)
		{
		case LANG_SPANISH:
			MessageBox(_T("Debe suplir un nombre a la serie"),_T("Error"));
			return;
		default:
			MessageBox(_T("You must supply a series name"),_T("Error"));
			return;
		}

	}

	m_iSeriesType = m_SeriesTypeCombo.GetCurSel();
	m_SeriesColour = m_ColourSelect.GetColour();
	
	TCHAR szBuff[255];
	GetDlgItem(IDC_MAXXVALUE_EDIT)->GetWindowText(szBuff,254); 
	m_fMaxXValue = (float)_tcstod(szBuff, NULL);
	GetDlgItem(IDC_MINXVALUE_EDIT)->GetWindowText(szBuff,254); 
	m_fMinXValue = (float)_tcstod(szBuff, NULL);
	if (m_fMinXValue > m_fMaxXValue)
	{
		switch(dwLanguageID)
		{
		case LANG_SPANISH:
			MessageBox(_T("El valor máximo de X debe ser > que el valor mínimo de X"));
			return;
		default:
			MessageBox(_T("Maximum X value should be > than the minimum X value"));
			return;
		}	
	}

	m_iHorizAxis = m_HorizAxisCombo.GetCurSel();
	m_iVertAxis = m_VertAxisCombo.GetCurSel();

	GetDlgItem(IDC_POINTSNUMBER_EDIT)->GetWindowText(szBuff,254); 
	m_iPointsNumber = _ttoi(szBuff);
	if (m_iPointsNumber < 2)
	{
		switch(dwLanguageID)
		{
		case LANG_SPANISH:
			MessageBox(_T("El número de puntos debe ser > 2"));
			return;
		default:
			MessageBox(_T("Number of points should be > 2"));
			return;
		}

	}

	if ( ((CButton*)GetDlgItem(IDC_LINEDATA_RADIO))->GetCheck() == 1)
	{
		m_iDataType = 0;
	
		GetDlgItem(IDC_DATAPARAM1_EDIT)->GetWindowText(szBuff,254); 
		m_fLineSlope = (float)_tcstod(szBuff, NULL);
		GetDlgItem(IDC_DATAPARAM2_EDIT)->GetWindowText(szBuff,254); 
		m_fLineOffset = (float)_tcstod(szBuff, NULL);
	}
	else if ( ((CButton*)GetDlgItem(IDC_SINEDATA_RADIO))->GetCheck() == 1)
	{
		m_iDataType = 1;
	
		GetDlgItem(IDC_DATAPARAM1_EDIT)->GetWindowText(szBuff,254); 
		m_fSineAmplitude = (float)_tcstod(szBuff, NULL);
		GetDlgItem(IDC_DATAPARAM2_EDIT)->GetWindowText(szBuff,254); 
		m_fSinePeriod = (float)_tcstod(szBuff, NULL);
		if (m_fSinePeriod == 0)
		{
			switch(dwLanguageID)
			{
			case LANG_SPANISH:
				MessageBox(_T("El período senoidal no puede ser 0.00"),_T("Error"));
				return;
			default:
				MessageBox(_T("Sine period cannot be 0.00"),_T("Error"));
				return;
			}
		}
	}
	else
	{
		m_iDataType = 2;
	
		GetDlgItem(IDC_DATAPARAM1_EDIT)->GetWindowText(szBuff,254); 
		m_iRandMinVal = _ttoi(szBuff);
		GetDlgItem(IDC_DATAPARAM2_EDIT)->GetWindowText(szBuff,254); 
		m_iRandMaxVal = _ttoi(szBuff);
		if (m_iRandMaxVal < m_iRandMinVal)
		{
			switch(dwLanguageID)
			{
			case LANG_SPANISH:
				MessageBox(_T("El máximo valor debe ser  > mínimo valor"));
				return;
			default:
				MessageBox(_T("Maximum random value should be > minimum random value"));
				return;
			}
		}
	}

	CDialog::OnOK();
}

BOOL CChartSeriePropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();

	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		m_SeriesTypeCombo.AddString(_T("Lineal"));
		m_SeriesTypeCombo.AddString(_T("Puntos"));
		m_SeriesTypeCombo.AddString(_T("Surperficie"));

		m_VertAxisCombo.AddString(_T("Izquierda"));
		m_VertAxisCombo.AddString(_T("Derecha"));

		m_HorizAxisCombo.AddString(_T("Inferior"));
		m_HorizAxisCombo.AddString(_T("Superior"));
		
/*
		CWnd::SetWindowText(_T("Propiedades series"));
		GetDlgItem(IDC_STATIC_SERIESPROP)->SetWindowText(_T("Propiedades series:"));
		GetDlgItem(IDC_STATIC_SERIESTYPE)->SetWindowText(_T("Tipo serie:"));
		GetDlgItem(IDC_STATIC_SERIESCOLOR)->SetWindowText(_T("Color serie:"));
		GetDlgItem(IDC_STATIC_SERIESNAME)->SetWindowText(_T("Nombre serie:"));
		GetDlgItem(IDC_STATIC_VERTICALAXIS)->SetWindowText(_T("Eje vertical asociado:"));
		GetDlgItem(IDC_STATIC_HORIZONTALAXIS)->SetWindowText(_T("Eje horizontal asociado:"));
		GetDlgItem(IDC_STATIC_SERIESDATA)->SetWindowText(_T("Datos serie:"));
				
		GetDlgItem(IDC_LINEDATA_RADIO)->SetWindowText(_T("Lineal"));
		GetDlgItem(IDC_SINEDATA_RADIO)->SetWindowText(_T("Senoidal"));
		GetDlgItem(IDC_RANDOMDATA_RADIO)->SetWindowText(_T("Aleatorio"));
		
		GetDlgItem(IDC_DATAPARAM1_TEXT)->SetWindowText(_T("Pendiente línea:"));
		GetDlgItem(IDC_DATAPARAM2_TEXT)->SetWindowText(_T("Intercepción:"));
		GetDlgItem(IDC_STATIC_POINTS)->SetWindowText(_T("Número puntos:"));
		GetDlgItem(IDC_STATIC_MINX_VAL)->SetWindowText(_T("Valor mínimo (X):"));
		GetDlgItem(IDC_STATIC_MAXX_VAL)->SetWindowText(_T("Valor máximo (X):"));	
		GetDlgItem(IDOK)->SetWindowText(_T("Aceptar"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancelar"));
*/
	break;
	default:
		m_SeriesTypeCombo.AddString(_T("Line"));
		m_SeriesTypeCombo.AddString(_T("Points"));
		m_SeriesTypeCombo.AddString(_T("Surface"));

		m_VertAxisCombo.AddString(_T("Left"));
		m_VertAxisCombo.AddString(_T("Right"));

		m_HorizAxisCombo.AddString(_T("Bottom"));
		m_HorizAxisCombo.AddString(_T("Top"));

/*
		CWnd::SetWindowText(_T("Series properties"));
		GetDlgItem(IDC_STATIC_SERIESPROP)->SetWindowText(_T("Series properties:"));
		GetDlgItem(IDC_STATIC_SERIESTYPE)->SetWindowText(_T("Series type:"));
		GetDlgItem(IDC_STATIC_SERIESCOLOR)->SetWindowText(_T("Series color:"));
		GetDlgItem(IDC_STATIC_SERIESNAME)->SetWindowText(_T("Series name:"));
		GetDlgItem(IDC_STATIC_VERTICALAXIS)->SetWindowText(_T("Associated vertical axis:"));
		GetDlgItem(IDC_STATIC_HORIZONTALAXIS)->SetWindowText(_T("Associated horizontal axis:"));
		GetDlgItem(IDC_STATIC_SERIESDATA)->SetWindowText(_T("Series data:"));
				
		GetDlgItem(IDC_LINEDATA_RADIO)->SetWindowText(_T("Line"));
		GetDlgItem(IDC_SINEDATA_RADIO)->SetWindowText(_T("Sine wave"));
		GetDlgItem(IDC_RANDOMDATA_RADIO)->SetWindowText(_T("Random"));
		
		GetDlgItem(IDC_DATAPARAM1_TEXT)->SetWindowText(_T("Line slope:"));
		GetDlgItem(IDC_DATAPARAM2_TEXT)->SetWindowText(_T("Line offset:"));
		GetDlgItem(IDC_STATIC_POINTS)->SetWindowText(_T("Number points:"));
		GetDlgItem(IDC_STATIC_MINX_VAL)->SetWindowText(_T("Minimum value (X):"));
		GetDlgItem(IDC_STATIC_MAXX_VAL)->SetWindowText(_T("Maximum value (X):"));
		GetDlgItem(IDOK)->SetWindowText(_T("OK"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancel"));
	break;
*/
	}


	m_SeriesTypeCombo.SetCurSel(0);
	m_HorizAxisCombo.SetCurSel(0);
	m_VertAxisCombo.SetCurSel(0);
	((CButton*)GetDlgItem(IDC_LINEDATA_RADIO))->SetCheck(1);
	
	GetDlgItem(IDC_MINXVALUE_EDIT)->SetWindowText(_T("0.00")); 
	GetDlgItem(IDC_MAXXVALUE_EDIT)->SetWindowText(_T("100.00")); 

	GetDlgItem(IDC_DATAPARAM1_EDIT)->SetWindowText(_T("1.00"));
	GetDlgItem(IDC_DATAPARAM2_EDIT)->SetWindowText(_T("0.00"));
	GetDlgItem(IDC_POINTSNUMBER_EDIT)->SetWindowText(_T("100.00")); 
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartSeriePropDlg::OnSelectLineData() 
{
		
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();

	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		GetDlgItem(IDC_DATAPARAM1_TEXT)->SetWindowText(_T("Pendiente línea:"));
		GetDlgItem(IDC_DATAPARAM2_TEXT)->SetWindowText(_T("Intercepción:"));
		GetDlgItem(IDC_DATAPARAM1_EDIT)->SetWindowText(_T("1.0"));
		GetDlgItem(IDC_DATAPARAM2_EDIT)->SetWindowText(_T("0.0"));
	break;
	default:
	GetDlgItem(IDC_DATAPARAM1_TEXT)->SetWindowText(_T("Line slope:"));
		GetDlgItem(IDC_DATAPARAM2_TEXT)->SetWindowText(_T("Line offset:"));
		GetDlgItem(IDC_DATAPARAM1_EDIT)->SetWindowText(_T("1.0"));
		GetDlgItem(IDC_DATAPARAM2_EDIT)->SetWindowText(_T("0.0"));
	break;
	}

  
}

void CChartSeriePropDlg::OnSelectRandomData() 
{
	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();

	switch(dwLanguageID)
	{
   case LANG_SPANISH:	
		GetDlgItem(IDC_DATAPARAM1_TEXT)->SetWindowText(_T("Valor mínimo (Y):"));
		GetDlgItem(IDC_DATAPARAM2_TEXT)->SetWindowText(_T("Valor máximo (Y):"));
		GetDlgItem(IDC_DATAPARAM1_EDIT)->SetWindowText(_T("0"));
		GetDlgItem(IDC_DATAPARAM2_EDIT)->SetWindowText(_T("100"));
		break;
	default:
		GetDlgItem(IDC_DATAPARAM1_TEXT)->SetWindowText(_T("Minimun value (Y):"));
		GetDlgItem(IDC_DATAPARAM2_TEXT)->SetWindowText(_T("Maximun value (Y):"));
		GetDlgItem(IDC_DATAPARAM1_EDIT)->SetWindowText(_T("0"));
		GetDlgItem(IDC_DATAPARAM2_EDIT)->SetWindowText(_T("100"));
		break;
	}
	
}

void CChartSeriePropDlg::OnSelectSineData() 
{
	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	switch(dwLanguageID)
	{
	case LANG_SPANISH:
		GetDlgItem(IDC_DATAPARAM1_TEXT)->SetWindowText(_T("Amplitud senoidal:"));
		GetDlgItem(IDC_DATAPARAM2_TEXT)->SetWindowText(_T("Período senoidal:"));
		GetDlgItem(IDC_DATAPARAM1_EDIT)->SetWindowText(_T("100.0"));
		GetDlgItem(IDC_DATAPARAM2_EDIT)->SetWindowText(_T("10.0"));
	break;
	default:
		GetDlgItem(IDC_DATAPARAM1_TEXT)->SetWindowText(_T("Sine amplitude:"));
		GetDlgItem(IDC_DATAPARAM2_TEXT)->SetWindowText(_T("Sine period:"));
		GetDlgItem(IDC_DATAPARAM1_EDIT)->SetWindowText(_T("100.0"));
		GetDlgItem(IDC_DATAPARAM2_EDIT)->SetWindowText(_T("10.0"));
	break;
	}
	
}

