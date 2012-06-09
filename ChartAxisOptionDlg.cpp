// ChartAxisOptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ChartAxisOptionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChartAxisOptionDlg dialog


CChartAxisOptionDlg::CChartAxisOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChartAxisOptionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChartAxisOptionDlg)
	m_iLeftAxis = -1;
	m_sAxisMaxVal = _T("");
	m_sAxisMinVal = _T("");
	m_sAxisLabel = _T("");
	m_bAxisGrid = FALSE;
	m_bAxisAutomatic = FALSE;
	m_bAxisVisible = FALSE;
	m_bAxisInverted = FALSE;
	m_bAxisLogarithmic = FALSE;
	//}}AFX_DATA_INIT
}


void CChartAxisOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChartAxisOptionDlg)
	DDX_Control(pDX, IDC_AXISMINVAL_EDIT, m_CEditAxisMinVal);
	DDX_Control(pDX, IDC_AXISMAXVAL_EDIT, m_CEditAxisMaxVal);
	DDX_Radio(pDX, IDC_LEFTAXIS_RADIO, m_iLeftAxis);
	DDX_Text(pDX, IDC_AXISMAXVAL_EDIT, m_sAxisMaxVal);
	DDX_Text(pDX, IDC_AXISMINVAL_EDIT, m_sAxisMinVal);
	DDX_Text(pDX, IDC_AXISLABEL_EDIT, m_sAxisLabel);
	DDX_Check(pDX, IDC_AXISGRIDVIS_CHECK, m_bAxisGrid);
	DDX_Check(pDX, IDC_AXISAUTOMATIC_CHECK, m_bAxisAutomatic);
	DDX_Check(pDX, IDC_AXISVISIBLE_CHECK, m_bAxisVisible);
	DDX_Check(pDX, IDC_AXISINVERTED_CHECK, m_bAxisInverted);
	DDX_Check(pDX, IDC_AXISLOGARITHMIC_CHECK, m_bAxisLogarithmic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChartAxisOptionDlg, CDialog)
	//{{AFX_MSG_MAP(CChartAxisOptionDlg)
	ON_EN_KILLFOCUS(IDC_AXISMINVAL_EDIT, OnChangeAxisMin)
	ON_EN_KILLFOCUS(IDC_AXISMAXVAL_EDIT, OnChangeAxisMax)
	ON_BN_CLICKED(IDC_LEFTAXIS_RADIO, OnLeftAxisRadio)
	ON_BN_CLICKED(IDC_BOTTOMAXIS_RADIO, OnBottomAxisRadio)
	ON_BN_CLICKED(IDC_RIGHTAXIS_RADIO, OnRightAxisRadio)
	ON_BN_CLICKED(IDC_TOPAXIS_RADIO, OnTopAxisRadio)
	ON_BN_CLICKED(IDC_AXISLOGARITHMIC_CHECK, OnAxisLogarithmicCheck)
	ON_BN_CLICKED(IDC_AXISAUTOMATIC_CHECK, OnAxisAutomaticCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartAxisOptionDlg message handlers
BOOL CChartAxisOptionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//ctrlBar.m_ChartCtrl.GetBottomAxis()->SetMinMax(0,100);
	//ctrlBar.m_ChartCtrl.GetLeftAxis()->SetMinMax(0,100);
/*	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID)
	{
	case LANG_SPANISH:
		CWnd::SetWindowText(_T("Opciones ejes"));
		GetDlgItem(IDC_LEFTAXIS_RADIO)->SetWindowText(_T("Izquierdo"));
		GetDlgItem(IDC_BOTTOMAXIS_RADIO)->SetWindowText(_T("Inferior"));
		GetDlgItem(IDC_RIGHTAXIS_RADIO)->SetWindowText(_T("Derecho"));
		GetDlgItem(IDC_TOPAXIS_RADIO)->SetWindowText(_T("Superior"));
		
		GetDlgItem(IDC_AXISVISIBLE_CHECK)->SetWindowText(_T("Visible"));
		GetDlgItem(IDC_AXISLOGARITHMIC_CHECK)->SetWindowText(_T("Logarítmico"));
		GetDlgItem(IDC_AXISINVERTED_CHECK)->SetWindowText(_T("Invertido"));
		GetDlgItem(IDC_AXISAUTOMATIC_CHECK)->SetWindowText(_T("Automático"));
		GetDlgItem(IDC_AXISGRIDVIS_CHECK)->SetWindowText(_T("Cuadrícula"));
		
		GetDlgItem(IDC_AXISMINVAL_STATIC)->SetWindowText(_T("Eje Mín"));
		GetDlgItem(IDC_AXISMAXVAL_STATIC)->SetWindowText(_T("Eje Máx"));
		GetDlgItem(IDC_AXISLABEL_STATIC)->SetWindowText(_T("Etiqueta"));
		
		GetDlgItem(IDOK)->SetWindowText(_T("Aceptar"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancelar"));
		break;
	default:
		CWnd::SetWindowText(_T("Axis options"));
		GetDlgItem(IDC_LEFTAXIS_RADIO)->SetWindowText(_T("Left"));
		GetDlgItem(IDC_BOTTOMAXIS_RADIO)->SetWindowText(_T("Bottom"));
		GetDlgItem(IDC_RIGHTAXIS_RADIO)->SetWindowText(_T("Right"));
		GetDlgItem(IDC_TOPAXIS_RADIO)->SetWindowText(_T("Top"));
		
		GetDlgItem(IDC_AXISVISIBLE_CHECK)->SetWindowText(_T("Visible"));
		GetDlgItem(IDC_AXISLOGARITHMIC_CHECK)->SetWindowText(_T("Logarithmic"));
		GetDlgItem(IDC_AXISINVERTED_CHECK)->SetWindowText(_T("Inverted"));
		GetDlgItem(IDC_AXISAUTOMATIC_CHECK)->SetWindowText(_T("Automatic"));
		GetDlgItem(IDC_AXISGRIDVIS_CHECK)->SetWindowText(_T("Grid"));
		
		GetDlgItem(IDC_AXISMINVAL_STATIC)->SetWindowText(_T("Min Axis"));
		GetDlgItem(IDC_AXISMAXVAL_STATIC)->SetWindowText(_T("Max Axis"));
		GetDlgItem(IDC_AXISLABEL_STATIC)->SetWindowText(_T("Label"));

		GetDlgItem(IDOK)->SetWindowText(_T("OK"));
		GetDlgItem(IDCANCEL)->SetWindowText(_T("Cancel"));
		break;
	}
*/

	((CButton*)GetDlgItem(IDC_LEFTAXIS_RADIO))->SetCheck(1);
	OnLeftAxisRadio();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChartAxisOptionDlg::OnLeftAxisRadio() 
{

	
	CChartAxis* pAxis = ctrlBar.m_chartCtrl.GetLeftAxis();
	
	if (pAxis->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(0);
	if (pAxis->IsLogarithmic())
		((CButton*)GetDlgItem(IDC_AXISLOGARITHMIC_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISLOGARITHMIC_CHECK))->SetCheck(0);
	if (pAxis->GetGrid()->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(0);
	if (pAxis->IsAutomatic())
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(0);


	
	if( szLeftAxisMin == _T("") )
	{
		szLeftAxisMin = _T("0.00");
	}
	else
	{
		float fLeftAxisMin = (float)_tcstod(szLeftAxisMin, NULL) ;
		szLeftAxisMin.Format(_T("%.*f"), 2, fLeftAxisMin);
	}
	
	if( szLeftAxisMax == _T("") )
	{
		szLeftAxisMax = _T("10.00");
	}
	else
	{
		float fLeftAxisMax = (float)_tcstod(szLeftAxisMax, NULL) ;
		szLeftAxisMax.Format( _T("%.*f"), 2,fLeftAxisMax);
	}
	
	GetDlgItem(IDC_AXISLABEL_EDIT)->SetWindowText(szLeftAxisLabel);
	GetDlgItem(IDC_AXISMAXVAL_EDIT)->SetWindowText(szLeftAxisMax);	
	GetDlgItem(IDC_AXISMINVAL_EDIT)->SetWindowText(szLeftAxisMin);
}

void CChartAxisOptionDlg::OnBottomAxisRadio() 
{
	
	CChartAxis* pAxis = ctrlBar.m_chartCtrl.GetBottomAxis();
	if (pAxis->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(0);
	if (pAxis->IsLogarithmic())
		((CButton*)GetDlgItem(IDC_AXISLOGARITHMIC_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISLOGARITHMIC_CHECK))->SetCheck(0);
	if (pAxis->GetGrid()->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(0);
	if (pAxis->IsAutomatic())
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(0);

	if( szBottomAxisMin == _T("") )
	{
		szBottomAxisMin = _T("0.00");
	}
	else
	{
		float fBottomAxisMin = (float)_tcstod(szBottomAxisMin, NULL) ;
		szBottomAxisMin.Format(_T("%.*f"), 2, fBottomAxisMin);
	}
	
	if( szBottomAxisMax == _T("") )
	{
		szBottomAxisMax = _T("10.00");
	}
	else
	{
		float fBottomAxisMax = (float)_tcstod(szBottomAxisMax, NULL) ;
		szBottomAxisMax.Format( _T("%.*f"), 2,fBottomAxisMax);
	}
	
	GetDlgItem(IDC_AXISLABEL_EDIT)->SetWindowText(szBottomAxisLabel);
	GetDlgItem(IDC_AXISMAXVAL_EDIT)->SetWindowText(szBottomAxisMax);	
	GetDlgItem(IDC_AXISMINVAL_EDIT)->SetWindowText(szBottomAxisMin);



}

void CChartAxisOptionDlg::OnRightAxisRadio() 
{

	CChartAxis* pAxis = ctrlBar.m_chartCtrl.GetRightAxis();
	if (pAxis->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(0);
	if (pAxis->IsLogarithmic())
		((CButton*)GetDlgItem(IDC_AXISLOGARITHMIC_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISLOGARITHMIC_CHECK))->SetCheck(0);
	if (pAxis->GetGrid()->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(0);
	if (pAxis->IsAutomatic())
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(0);


	if( szRightAxisMin == _T("") )
	{
		szRightAxisMin = _T("0.00");
	}
	else
	{
		float fRightAxisMin = (float)_tcstod(szRightAxisMin, NULL) ;
		szRightAxisMin.Format(_T("%.*f"), 2, fRightAxisMin);
	}
	
	if( szRightAxisMax == _T("") )
	{
		szRightAxisMax = _T("10.00");
	}
	else
	{
		float fRightAxisMax = (float)_tcstod(szRightAxisMax, NULL) ;
		szRightAxisMax.Format( _T("%.*f"), 2,fRightAxisMax);
	}
	
	GetDlgItem(IDC_AXISLABEL_EDIT)->SetWindowText(szRightAxisLabel);
	GetDlgItem(IDC_AXISMAXVAL_EDIT)->SetWindowText(szRightAxisMax);	
	GetDlgItem(IDC_AXISMINVAL_EDIT)->SetWindowText(szRightAxisMin);
}

void CChartAxisOptionDlg::OnTopAxisRadio() 
{

	
	
	CChartAxis* pAxis = ctrlBar.m_chartCtrl.GetTopAxis();
	if (pAxis->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISVISIBLE_CHECK))->SetCheck(0);
	if (pAxis->IsLogarithmic())
		((CButton*)GetDlgItem(IDC_AXISLOGARITHMIC_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISLOGARITHMIC_CHECK))->SetCheck(0);
	if (pAxis->GetGrid()->IsVisible())
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISGRIDVIS_CHECK))->SetCheck(0);
	if (pAxis->IsAutomatic())
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(1);
	else
		((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(0);

	
	if( szTopAxisMin == _T("") )
	{
		szTopAxisMin = _T("0.00");
	}
	else
	{
		float fTopAxisMin = (float)_tcstod(szTopAxisMin, NULL) ;
		szTopAxisMin.Format(_T("%.*f"), 2, fTopAxisMin);
	}
	
	if( szTopAxisMax == _T("") )
	{
		szTopAxisMax = _T("10.00");
	}
	else
	{
		float fTopAxisMax = (float)_tcstod(szTopAxisMax, NULL) ;
		szTopAxisMax.Format( _T("%.*f"), 2,fTopAxisMax);
	}
	
	GetDlgItem(IDC_AXISLABEL_EDIT)->SetWindowText(szTopAxisLabel);
	GetDlgItem(IDC_AXISMAXVAL_EDIT)->SetWindowText(szTopAxisMax);	
	GetDlgItem(IDC_AXISMINVAL_EDIT)->SetWindowText(szTopAxisMin);
}


void CChartAxisOptionDlg::OnAxisAutomaticCheck() 
{
	
	if ( ((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->GetCheck() == 1)
	{
		m_bAxisAutomatic = true;
	}
	else
	{
		TCHAR szBuffer[255];
		double MinVal=0, MaxVal=0;
		m_CEditAxisMinVal.GetWindowText(szBuffer,254);
		MinVal = _tcstod(szBuffer, NULL);
		m_CEditAxisMaxVal.GetWindowText(szBuffer,254);
		MaxVal = _tcstod(szBuffer, NULL);

		if (MinVal > MaxVal)
		{
			LANGID dwLanguageID = GetSystemLanguagePrimaryID();
			switch(dwLanguageID)
			{
				
			case LANG_SPANISH:
				MessageBox(_T("Valor mínimo > Valor máximo"),_T("Error"),MB_OK);
				((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(1);
				return;
			default:
				MessageBox(_T("Minimun value> Maximun value"),_T("Error"),MB_OK);
				((CButton*)GetDlgItem(IDC_AXISAUTOMATIC_CHECK))->SetCheck(1);
				return;
			}

		}
		m_bAxisAutomatic = false;
		
	}
	
}



void CChartAxisOptionDlg::OnAxisLogarithmicCheck() 
{
	TCHAR szBuffer[255];
	if ( ((CButton*)GetDlgItem(IDC_AXISLOGARITHMIC_CHECK))->GetCheck() == 1)
	{
		double MinVal=0,MaxVal=0;
		m_CEditAxisMinVal.GetWindowText(szBuffer,254);
		MinVal = _tcstod(szBuffer, NULL);
		if (MinVal <= 0)
		{
			LANGID dwLanguageID = GetSystemLanguagePrimaryID();
			
			switch(dwLanguageID)
			{
			case LANG_SPANISH:
				MessageBox(_T("Imposible generar eje: valores nulos o negativos"));
				((CButton*)GetDlgItem(IDC_AXISLOGARITHMIC_CHECK))->SetCheck(0);
				return;
			default:
				MessageBox(_T("Log axis impossible: null or negative values"));
				((CButton*)GetDlgItem(IDC_AXISLOGARITHMIC_CHECK))->SetCheck(0);
				return;
			}
		}
		m_bAxisLogarithmic = 1;
		
	}
	else
		m_bAxisLogarithmic = 0;	
	
}


CChartAxis* CChartAxisOptionDlg::GetSelectedAxis()
{
	if ( ((CButton*)GetDlgItem(IDC_LEFTAXIS_RADIO))->GetCheck() == 1)
		return ctrlBar.m_chartCtrl.GetLeftAxis();
	if ( ((CButton*)GetDlgItem(IDC_BOTTOMAXIS_RADIO))->GetCheck() == 1)
		return ctrlBar.m_chartCtrl.GetBottomAxis();
	if ( ((CButton*)GetDlgItem(IDC_RIGHTAXIS_RADIO))->GetCheck() == 1)
		return ctrlBar.m_chartCtrl.GetRightAxis();
	if ( ((CButton*)GetDlgItem(IDC_TOPAXIS_RADIO))->GetCheck() == 1)
		return ctrlBar.m_chartCtrl.GetTopAxis();

	return NULL;
}

void CChartAxisOptionDlg::OnChangeAxisMax() 
{
	
	TCHAR szBuffer[255];
	double MinVal=0, MaxVal=0;
	m_CEditAxisMinVal.GetWindowText(szBuffer,254);
	MinVal = _tcstod(szBuffer, NULL);
	m_CEditAxisMaxVal.GetWindowText(szBuffer,254);
	MaxVal = _tcstod(szBuffer, NULL);
	
	if (MinVal > MaxVal)
	{
		LANGID dwLanguageID = GetSystemLanguagePrimaryID();

		switch(dwLanguageID)
		{
		case LANG_SPANISH:
			MessageBox(TEXT("Valor mínimo > valor máximo"),TEXT("Error"),MB_OK);
			return;
		default:
			MessageBox(TEXT("Minimum value > maximum value"),TEXT("Error"),MB_OK);
			return;
		}
	}
	
	
}

void CChartAxisOptionDlg::OnChangeAxisMin() 
{
	
	TCHAR szBuffer[255];
	double MinVal=0, MaxVal=0;
	m_CEditAxisMinVal.GetWindowText(szBuffer,254);
	MinVal = _tcstod(szBuffer, NULL);
	m_CEditAxisMaxVal.GetWindowText(szBuffer,254);
	MaxVal = _tcstod(szBuffer, NULL);

	if (MinVal > MaxVal)
	{
		LANGID dwLanguageID = GetSystemLanguagePrimaryID();

		switch(dwLanguageID)
		{
		case LANG_SPANISH:
			MessageBox(TEXT("Valor mínimo > valor máximo"),TEXT("Error"),MB_OK);
			return;
		default:
			MessageBox(TEXT("Minimum value > maximum value"),TEXT("Error"),MB_OK);
			return;
		}
	}
	
}

