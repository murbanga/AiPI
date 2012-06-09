// ChartBarCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ChartBarCtrl.h"


#include ".\ChartCtrl\ChartLineSerie.h"
#include ".\ChartCtrl\ChartPointsSerie.h"
#include ".\ChartCtrl\ChartSurfaceSerie.h"
#include ".\ChartCtrl\ChartGrid.h"
#include ".\ChartCtrl\ChartAxisLabel.h"





#include "ChartSeriePropDlg.h"
#include "ChartSerieDelDlg.h"
#include "ChartLinePropDlg.h"
#include "ChartSurfacePropDlg.h"
#include "ChartPointPropDlg.h"
#include "ChartAxisOptionDlg.h"
#include "StringInputDlg.h"


#include <math.h>
#include <string>

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

using namespace std;

IMPLEMENT_DYNAMIC(CChartBarCtrl, COXSizeControlBar);
/////////////////////////////////////////////////////////////////////////////
// CChartBarCtrl

CChartBarCtrl::CChartBarCtrl()
: COXSizeControlBar( SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	index = -1;
}

CChartBarCtrl::~CChartBarCtrl()
{
	
}


BEGIN_MESSAGE_MAP(CChartBarCtrl, COXSizeControlBar)
	//{{AFX_MSG_MAP(CChartBarCtrl)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChartBarCtrl message handlers
int CChartBarCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	
	
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	//SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

	if (!m_chartCtrl.Create(this, CRect(0,0,0,0), IDC_CHARTBARCTRL, WS_CHILD|WS_VISIBLE|   
			SS_ICON|SS_CENTER))
		return -1;

	m_chartCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);

	//Unable the pan and zoom options
	OnZoomUnChecked();
	OnPanUnChecked();
	
			
	return 0;
}

BOOL CChartBarCtrl::Create(CWnd * pParentWnd, const CString& sTitle /* = _T("ImageCtrl")*/,
					const UINT nID /* = IDC_ST_IMG */)
{
	//Register a windows class for the control bar
	static CString strWndClass;
	if ( strWndClass.IsEmpty())
	{
		strWndClass = AfxRegisterWndClass(CS_DBLCLKS);
	}

	return COXSizeControlBar::Create(strWndClass, sTitle, WS_VISIBLE |WS_CHILD |
		CBRS_RIGHT|WS_CLIPCHILDREN, CFrameWnd::rectDefault, pParentWnd, nID);


}

static CString GetShort(UINT id)
{
	CString str;
	str.LoadString(id);
	int nIndex = str.ReverseFind(_T('\n'));
	if(nIndex!=-1)
	{
		str=str.Mid(nIndex+1);
	}
	return str;
}


void CChartBarCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//Point marks
   /*
	UINT menu_flags; 
	menu_flags |= MF_CHECKED;
    	
	
	UNREFERENCED_PARAMETER(pWnd);

	if(point.x==-1 && point.y==-1)
	{
		CRect rect;
		GetWindowRect(rect);

		point = rect.TopLeft()+CPoint(10,10);
	}
	SetFocus();

	CNewMenu menu;

	
	menu.CreatePopupMenu();
	menu.InsertMenu(0, MF_BYPOSITION , ID_CTRL_CHARTBAR_ADD, GetShort(ID_CTRL_CHARTBAR_ADD));
	menu.InsertMenu(1, MF_BYPOSITION ,ID_CTRL_CHARTBAR_DEL , GetShort(ID_CTRL_CHARTBAR_DEL));
	menu.InsertMenu(2, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(3, MF_BYPOSITION ,ID_CTRL_CHARTBAR_TITLE , GetShort(ID_CTRL_CHARTBAR_TITLE));
	menu.InsertMenu(4, MF_BYPOSITION , ID_CTRL_CHARTBAR_BCKCOLOR, GetShort(ID_CTRL_CHARTBAR_BCKCOLOR));
	menu.InsertMenu(5, MF_BYPOSITION , ID_CTRL_CHARTBAR_LEGENDVISIBLE, GetShort(ID_CTRL_CHARTBAR_LEGENDVISIBLE));
	menu.InsertMenu(6, MF_BYPOSITION , ID_CTRL_CHARTBAR_PANENABLE, GetShort(ID_CTRL_CHARTBAR_PANENABLE));
	menu.InsertMenu(7, MF_BYPOSITION , ID_CTRL_CHARTBAR_ZOOMENABLE, GetShort(ID_CTRL_CHARTBAR_ZOOMENABLE));
	menu.InsertMenu(8, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(9, MF_BYPOSITION ,ID_CTRL_CHARTBAR_AXIS ,GetShort(ID_CTRL_CHARTBAR_AXIS));

	menu.SetMenuTitle(_T("RichChartBar"),MFT_GRADIENT|MFT_SIDE_TITLE);
	menu.LoadToolBar(IDR_CHARTBAR);

	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
	
*/
}

//-------------------------------------------------------------------
void CChartBarCtrl::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
// respond to this event as we need to override it
//-------------------------------------------------------------------
{
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	CRect rect;
	GetClientRect(rect);

	rect.DeflateRect(0, 0);

	m_chartCtrl.MoveWindow(&rect);
}


void CChartBarCtrl::OnAddSeries() 
{
	CChartSeriePropDlg PropertiesDlg;
	if (PropertiesDlg.DoModal() == IDCANCEL)
		return;

	int Type = PropertiesDlg.m_iSeriesType;

#ifdef UNICODE
	std::wstring Name = PropertiesDlg.m_strSeriesName;
#else
	std::string Name = PropertiesDlg.m_strSeriesName;
#endif
	
	COLORREF Color = PropertiesDlg.m_SeriesColour;

	CChartSerie* pSeries = m_chartCtrl.AddSerie(Type);
	switch (Type)
	{
	case CChartSerie::stLineSerie:
		{
			CChartLineSerie* pLineSeries = static_cast<CChartLineSerie*>(pSeries); 

			CChartLinePropDlg LinePropDlg;
			LinePropDlg.DoModal();

			pLineSeries->SetWidth(LinePropDlg.m_iLineWidth);
			pLineSeries->SetPenStyle(LinePropDlg.m_iPenStyle);
		}
		break;

	case CChartSerie::stPointsSerie:
		{
			CChartPointsSerie* pPointsSeries = static_cast<CChartPointsSerie*>(pSeries); 

			CChartPointPropDlg PointsPropDlg;
			PointsPropDlg.DoModal();

			switch (PointsPropDlg.m_iPointsType)
			{
			case 0:
				pPointsSeries->SetPointType(CChartPointsSerie::ptEllipse);
				break;

			case 1:
				pPointsSeries->SetPointType(CChartPointsSerie::ptRectangle);
				break;

			case 2:
				pPointsSeries->SetPointType(CChartPointsSerie::ptTriangle);
				break;
			}

			pPointsSeries->SetPointSize(PointsPropDlg.m_iPointsWidth,PointsPropDlg.m_iPointsHeight);
		}
		break;

	case CChartSerie::stSurfaceSerie:
		{
			CChartSurfaceSerie* pSurfSeries = static_cast<CChartSurfaceSerie*>(pSeries); 

			CChartSurfacePropDlg SurfPropDlg;
			SurfPropDlg.DoModal();

			switch (SurfPropDlg.m_FillStyle)
			{
			case 0:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsSolid);
				break;
			case 1:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchDownDiag);
				break;
			case 2:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchUpDiag);
				break;
			case 3:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchCross);
				break;
			case 4:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchDiagCross);
				break;
			case 5:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchHorizontal);
				break;
			case 6:
				pSurfSeries->SetFillStyle(CChartSurfaceSerie::fsHatchVertical);
				break;
			}

			if (SurfPropDlg.m_iHorizSurf == 0)
				pSurfSeries->SetHorizontal(true);
			else
				pSurfSeries->SetHorizontal(false);
		}
		break;
	}

	pSeries->SetName(Name);
	pSeries->SetColor(Color);

	if (PropertiesDlg.m_iHorizAxis == 0)
		pSeries->SetHorizontalAxis(false);
	else
		pSeries->SetHorizontalAxis(true);
	if (PropertiesDlg.m_iVertAxis == 0)
		pSeries->SetVerticalAxis(false);
	else
		pSeries->SetVerticalAxis(true);

	int NumberPoints = PropertiesDlg.m_iPointsNumber;
	double* XValues = new double[NumberPoints];
	double* YValues = new double[NumberPoints];
	float Step = (PropertiesDlg.m_fMaxXValue - PropertiesDlg.m_fMinXValue)/(NumberPoints - 1);
	float XStart = PropertiesDlg.m_fMinXValue;
	switch (PropertiesDlg.m_iDataType)
	{
	case 0:
		{
			float Slope = PropertiesDlg.m_fLineSlope;
			float Offset = PropertiesDlg.m_fLineOffset;

			for (int i=0;i<NumberPoints;i++)
			{
				XValues[i] = XStart + i * Step;
				YValues[i] = XValues[i] * Slope + Offset;
			}
			pSeries->SetPoints(XValues,YValues,NumberPoints);

		}
		break;

	case 1:
		{
			float Amplitude = PropertiesDlg.m_fSineAmplitude;
			float Period = PropertiesDlg.m_fSinePeriod;

			for (int i=0;i<NumberPoints;i++)
			{
				XValues[i] = XStart + i * Step;
				YValues[i] = Amplitude * (float)sin( 2 * 3.141592 * XValues[i]/Period );
			}
			pSeries->SetPoints(XValues,YValues,NumberPoints);
		}
		break;

	case 2:
		{
			int Min = PropertiesDlg.m_iRandMinVal;
			int Max = PropertiesDlg.m_iRandMaxVal;
			srand((unsigned int)time(NULL));
			for (int i=0;i<NumberPoints;i++)
			{
				XValues[i] = XStart + i * Step;
				YValues[i] = Min + (rand()%(Max-Min));
			}
			pSeries->SetPoints(XValues,YValues,NumberPoints);
		}
		break;
	}
	
	delete[] XValues;
	delete[] YValues;
	m_chartCtrl.RefreshCtrl();
	
	saSerieName.Add(Name.c_str());
	
	/*
	CSeriesDelDlg DeleteDlg;
	DeleteDlg.szSerieName = Name.c_str();
	DeleteDlg.DoModal();
	*/
}	



void CChartBarCtrl::OnDeleteSeries() 
{
	CChartSerieDelDlg DeleteDlg;
	for(int i = 0; i< saSerieName.GetSize(); i++)
	{
		DeleteDlg.dlgSerieName.Add(saSerieName[i]);
	}
	
	if( DeleteDlg.DoModal() == IDOK)
	{
		int Index = DeleteDlg.dlgIndex;
		m_chartCtrl.RemoveSerie(Index);
		saSerieName.RemoveAt(Index);
	}
}

LONG CChartBarCtrl::OnChangeBckCol()
{
	COLORREF BackColor =::GetSysColor(COLOR_3DFACE); 
	CColorDialog DlgColor(BackColor, CC_RGBINIT);
	
	if( DlgColor.DoModal() == IDOK )
	{
		BackColor = DlgColor.GetColor();
		m_chartCtrl.SetBackColor(BackColor);
		m_chartCtrl.RefreshCtrl();
	}
	
	return TRUE;
}

void CChartBarCtrl::OnLegendVisible() 
{
	
	m_chartCtrl.GetLegend()->SetVisible(true);
	m_chartCtrl.RefreshCtrl();
	
}

void CChartBarCtrl::OnLegendNotVisible() 
{
	m_chartCtrl.GetLegend()->SetVisible(false);
	m_chartCtrl.RefreshCtrl();
		
}

void CChartBarCtrl::OnPanChecked() 
{
	m_chartCtrl.SetPanEnabled(true);
		
}

void CChartBarCtrl::OnPanUnChecked() 
{
	m_chartCtrl.SetPanEnabled(false);	
	
}

void CChartBarCtrl::OnZoomChecked() 
{
	m_chartCtrl.SetZoomEnabled(true);
}

void CChartBarCtrl::OnZoomUnChecked() 
{
	m_chartCtrl.SetZoomEnabled(false);	
}

void CChartBarCtrl::OnChangeTitle() 
{
	
	CStringInputDlg dlg ;


	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	switch( dwLanguageID )
	{
	case LANG_SPANISH:
		dlg.m_strPrompt.Format(TEXT("Introduzca el nuevo título:")) ;
		dlg.szBtnOK = _T("Aceptar");
		dlg.szBtnCancel = _T("Cancelar");
		dlg.szDlgCaption = _T("RichChartBar Cuadro de entrada");
		break;
	default:
		dlg.m_strPrompt.Format(TEXT("Enter the new title:")) ;
		dlg.szBtnOK = _T("OK");
		dlg.szBtnCancel = _T("Cancel");
		dlg.szDlgCaption = _T("RichChartBar InputBox");
		break;
	}


	if( dlg.DoModal() == IDOK )
	{
		CChartTitle* pTitle = m_chartCtrl.GetTitle();
		pTitle->RemoveAll();

#ifdef _UNICODE
		std::wstring Title = dlg.m_strTitleName;
#else		
		std::string Title = dlg.m_strTitleName;
#endif
		
		pTitle->AddString(Title);
		m_chartCtrl.RefreshCtrl();
	
	}
}


void CChartBarCtrl::OnAxisOption()
{
	CChartAxisOptionDlg dlg;
	double MinVal, MaxVal;
	
	//Updates values of the CAxisOptionsDlg
	dlg.szLeftAxisLabel = szLeftLabel;
	dlg.szBottomAxisLabel = szBottomLabel;
	dlg.szRightAxisLabel = szRightLabel;
	dlg.szTopAxisLabel = szTopLabel;

	dlg.szLeftAxisMax = szLeftMax;
	dlg.szBottomAxisMax = szBottomMax;
	dlg.szRightAxisMax = szRightMax;
	dlg.szTopAxisMax = szTopMax;

	dlg.szLeftAxisMin = szLeftMin;
	dlg.szBottomAxisMin = szBottomMin;
	dlg.szRightAxisMin = szRightMin;
	dlg.szTopAxisMin = szTopMin;

	if( dlg.DoModal() == IDOK )
	{
		int iAxisOption = dlg.m_iLeftAxis;
		
		switch( iAxisOption)
		{
		case 0:
			MinVal = _tcstod(dlg.m_sAxisMinVal, NULL);
			MaxVal = _tcstod(dlg.m_sAxisMaxVal, NULL);
			SetLeftAxisMinMax(MinVal, MaxVal);
			SetLeftAxisLabel(dlg.m_sAxisLabel);
			SetLeftAxisGrid(dlg.m_bAxisGrid);
			SetLeftAxisVisible(dlg.m_bAxisVisible);
			SetLeftAxisInverted(dlg.m_bAxisInverted);
			SetLeftAxisAutomatic(dlg.m_bAxisAutomatic, MinVal, MaxVal);

			szLeftLabel = dlg.m_sAxisLabel;
			szLeftMax = dlg.m_sAxisMaxVal;
			szLeftMin = dlg.m_sAxisMinVal;
			break;
		case 1:
			MinVal = _tcstod(dlg.m_sAxisMinVal, NULL);
			MaxVal = _tcstod(dlg.m_sAxisMaxVal, NULL);
			SetBottomAxisLabel(dlg.m_sAxisLabel);
			SetBottomAxisMinMax(MinVal, MaxVal);
			SetBottomAxisGrid(dlg.m_bAxisGrid);
			SetBottomAxisVisible(dlg.m_bAxisVisible);
			SetBottomAxisInverted(dlg.m_bAxisInverted);
			SetBottomAxisAutomatic(dlg.m_bAxisAutomatic, MinVal, MaxVal);

			szBottomLabel = dlg.m_sAxisLabel;
			szBottomMax = dlg.m_sAxisMaxVal;
			szBottomMin = dlg.m_sAxisMinVal;
			break;
		case 2:
			MinVal = _tcstod(dlg.m_sAxisMinVal, NULL);
			MaxVal = _tcstod(dlg.m_sAxisMaxVal, NULL);
			SetRightAxisLabel(dlg.m_sAxisLabel);
			SetRightAxisMinMax(MinVal, MaxVal);
			SetRightAxisGrid(dlg.m_bAxisGrid);
			SetRightAxisVisible(dlg.m_bAxisVisible);
			SetRightAxisInverted(dlg.m_bAxisInverted);
			SetRightAxisAutomatic(dlg.m_bAxisAutomatic, MinVal, MaxVal);

			szRightLabel = dlg.m_sAxisLabel;
			szRightMax = dlg.m_sAxisMaxVal;
			szRightMin = dlg.m_sAxisMinVal;
			break;
		case 3:
			MinVal = _tcstod(dlg.m_sAxisMinVal, NULL);
			MaxVal = _tcstod(dlg.m_sAxisMaxVal, NULL);
			SetTopAxisLabel(dlg.m_sAxisLabel);
			SetTopAxisMinMax(MinVal, MaxVal);
			SetTopAxisGrid(dlg.m_bAxisGrid);
			SetTopAxisVisible(dlg.m_bAxisVisible);
			SetTopAxisInverted(dlg.m_bAxisInverted);
			SetTopAxisAutomatic(dlg.m_bAxisAutomatic, MinVal, MaxVal);

			szTopLabel = dlg.m_sAxisLabel;
			szTopMax = dlg.m_sAxisMaxVal;
			szTopMin = dlg.m_sAxisMinVal;
			break;	
		}
	}
	
	m_chartCtrl.RefreshCtrl();
}



void CChartBarCtrl::SetLeftAxisMinMax(double min, double max)
{
	CChartAxis* pAxis = m_chartCtrl.GetLeftAxis();
	pAxis->SetMinMax(min, max);
}

void CChartBarCtrl::SetBottomAxisMinMax(double min, double max)
{
	CChartAxis* pAxis = m_chartCtrl.GetBottomAxis();
	pAxis->SetMinMax(min, max);
}

void CChartBarCtrl::SetRightAxisMinMax(double min, double max)
{
	CChartAxis* pAxis = m_chartCtrl.GetRightAxis();
	pAxis->SetMinMax(min, max);
}

void CChartBarCtrl::SetTopAxisMinMax(double min, double max)
{
	CChartAxis* pAxis = m_chartCtrl.GetTopAxis();
	pAxis->SetMinMax(min, max);
}

void CChartBarCtrl::SetLeftAxisVisible(int flag)
{
	CChartAxis* pAxis = m_chartCtrl.GetLeftAxis();
		
	if ( flag == 1 )
	{
		pAxis->SetVisible(true);
	}
	else
	{
		pAxis->SetVisible(false);
	}
	
}

void CChartBarCtrl::SetBottomAxisVisible(int flag)
{
	CChartAxis* pAxis = m_chartCtrl.GetBottomAxis();
		
	if ( flag == 1 )
	{
		pAxis->SetVisible(true);
	}
	else
	{
		pAxis->SetVisible(false);
	}
	
}

void CChartBarCtrl::SetRightAxisVisible(int flag)
{
	CChartAxis* pAxis = m_chartCtrl.GetRightAxis();
		
	if ( flag == 1 )
	{
		pAxis->SetVisible(true);
	}
	else
	{
		pAxis->SetVisible(false);
	}
	
}
void CChartBarCtrl::SetTopAxisVisible(int flag)
{
	CChartAxis* pAxis = m_chartCtrl.GetTopAxis();
		
	if ( flag == 1 )
	{
		pAxis->SetVisible(true);
	}
	else
	{
		pAxis->SetVisible(false);
	}
	
}




void CChartBarCtrl::SetLeftAxisGrid(int flag)
{
	CChartAxis* pAxis = m_chartCtrl.GetLeftAxis();
		
	if ( flag == 1 )
	{
		pAxis->GetGrid()->SetVisible(true);
	}
	else
	{
		pAxis->GetGrid()->SetVisible(false);
	}
	
}

void CChartBarCtrl::SetBottomAxisGrid(int flag)
{
	CChartAxis* pAxis = m_chartCtrl.GetBottomAxis();
	
	if ( flag == 1 )
	{
		pAxis->GetGrid()->SetVisible(true);
	}
	else
	{
		pAxis->GetGrid()->SetVisible(false);
	}
}


void CChartBarCtrl::SetRightAxisGrid(int flag)
{
	CChartAxis* pAxis = m_chartCtrl.GetRightAxis();
	
	if ( flag == 1 )
	{
		pAxis->GetGrid()->SetVisible(true);
	}
	else
	{
		pAxis->GetGrid()->SetVisible(false);
	}
}

void CChartBarCtrl::SetTopAxisGrid(int flag)
{
	CChartAxis* pAxis = m_chartCtrl.GetTopAxis();
	
	if ( flag == 1 )
	{
		pAxis->GetGrid()->SetVisible(true);
	}
	else
	{
		pAxis->GetGrid()->SetVisible(false);
	}
}

void CChartBarCtrl::SetLeftAxisInverted(int flag)
{
	CChartAxis* pAxis = m_chartCtrl.GetLeftAxis();
		
	if ( flag == 1 )
	{
		pAxis->SetInverted(true);
	}
	else
	{
		pAxis->SetInverted(false);
	}
	
}

void CChartBarCtrl::SetBottomAxisInverted(int flag)
{
	CChartAxis* pAxis = m_chartCtrl.GetBottomAxis();
	
	if ( flag == 1 )
	{
		pAxis->SetInverted(true);
	}
	else
	{
		pAxis->SetInverted(false);
	}
}


void CChartBarCtrl::SetRightAxisInverted(int flag)
{
	CChartAxis* pAxis = m_chartCtrl.GetRightAxis();
	
	if ( flag == 1 )
	{
		pAxis->SetInverted(true);
	}
	else
	{
		pAxis->SetInverted(false);
	}
}

void CChartBarCtrl::SetTopAxisInverted(int flag)
{
	CChartAxis* pAxis = m_chartCtrl.GetTopAxis();
	
	if ( flag == 1 )
	{
		pAxis->SetInverted(true);
	}
	else
	{
		pAxis->SetInverted(false);
	}
}



void CChartBarCtrl::SetLeftAxisAutomatic(int flag, double min, double max)
{

	CChartAxis* pAxis = m_chartCtrl.GetLeftAxis();
	
	if ( flag == 1 )
	{
		pAxis->SetAutomatic(true);
	}
	else
	{
		pAxis->SetAutomatic(false);
		pAxis->SetMinMax(min,max);
	}

}

void CChartBarCtrl::SetBottomAxisAutomatic(int flag, double min, double max)
{

	CChartAxis* pAxis = m_chartCtrl.GetBottomAxis();
	
	if ( flag == 1 )
	{
		pAxis->SetAutomatic(true);
	}
	else
	{
		pAxis->SetAutomatic(false);
		pAxis->SetMinMax(min,max);
	}

}

void CChartBarCtrl::SetRightAxisAutomatic(int flag, double min, double max)
{

	CChartAxis* pAxis = m_chartCtrl.GetRightAxis();
	
	if ( flag == 1 )
	{
		pAxis->SetAutomatic(true);
	}
	else
	{
		pAxis->SetAutomatic(false);
		pAxis->SetMinMax(min,max);
	}

}

void CChartBarCtrl::SetTopAxisAutomatic(int flag, double min, double max)
{

	CChartAxis* pAxis = m_chartCtrl.GetRightAxis();
	
	if ( flag == 1 )
	{
		pAxis->SetAutomatic(true);
	}
	else
	{
		pAxis->SetAutomatic(false);
		pAxis->SetMinMax(min,max);
	}

}

void CChartBarCtrl::SetLeftAxisLogarithmic(int flag, double min, double max)
{

	CChartAxis* pAxis = m_chartCtrl.GetLeftAxis();
	
	if ( flag == 1 )
	{
		pAxis->SetLogarithmic(true);
	}
	else
	{
		pAxis->SetLogarithmic(false);
		pAxis->SetMinMax(min,max);
	}

}

void CChartBarCtrl::SetBottomAxisLogarithmic(int flag, double min, double max)
{

	CChartAxis* pAxis = m_chartCtrl.GetBottomAxis();
	
	if ( flag == 1 )
	{
		pAxis->SetLogarithmic(true);
	}
	else
	{
		pAxis->SetLogarithmic(false);
		pAxis->SetMinMax(min,max);
	}

}

void CChartBarCtrl::SetRightAxisLogarithmic(int flag, double min, double max)
{

	CChartAxis* pAxis = m_chartCtrl.GetRightAxis();
	
	if ( flag == 1 )
	{
		pAxis->SetLogarithmic(true);
	}
	else
	{
		pAxis->SetLogarithmic(false);
		pAxis->SetMinMax(min,max);
	}

}

void CChartBarCtrl::SetTopAxisLogarithmic(int flag, double min, double max)
{

	CChartAxis* pAxis = m_chartCtrl.GetRightAxis();
	
	if ( flag == 1 )
	{
		pAxis->SetLogarithmic(true);
	}
	else
	{
		pAxis->SetLogarithmic(false);
		pAxis->SetMinMax(min,max);
	}

}

void CChartBarCtrl::SetLeftAxisLabel(CString label)
{

	TCHAR szBuffer[255] = {' '};
	for(int i= 0; i<label.GetLength(); i++)
	{
		szBuffer[i] = label[i];
		
	}
	
	CChartAxis* pAxis = m_chartCtrl.GetLeftAxis();
	pAxis->GetLabel()->SetText(szBuffer);
}

void CChartBarCtrl::SetBottomAxisLabel(CString label)
{
	TCHAR szBuffer[255] = {' '};
	for(int i= 0; i<label.GetLength(); i++)
	{
		szBuffer[i] = label[i];
		
	}
	
	CChartAxis* pAxis = m_chartCtrl.GetBottomAxis();
	pAxis->GetLabel()->SetText(szBuffer);
}

void CChartBarCtrl::SetRightAxisLabel(CString label)
{
	TCHAR szBuffer[255] = {' '};
	for(int i= 0; i<label.GetLength(); i++)
	{
		szBuffer[i] = label[i];
		
	}
	
	CChartAxis* pAxis = m_chartCtrl.GetRightAxis();
	pAxis->GetLabel()->SetText(szBuffer);
}

void CChartBarCtrl::SetTopAxisLabel(CString label)
{
	TCHAR szBuffer[255] = {' '};
	for(int i= 0; i<label.GetLength(); i++)
	{
		szBuffer[i] = label[i];
		
	}
	
	CChartAxis* pAxis = m_chartCtrl.GetTopAxis();
	pAxis->GetLabel()->SetText(szBuffer);
}

