// StaticMeterCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "StaticMeterCtrl.h"
#include "StringInputDlg.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CStaticMeterCtrl, COXSizeControlBar);
/////////////////////////////////////////////////////////////////////////////
// CStaticMeterCtrl

CStaticMeterCtrl::CStaticMeterCtrl()
:COXSizeControlBar(SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
}

CStaticMeterCtrl::~CStaticMeterCtrl()
{
}


BEGIN_MESSAGE_MAP(CStaticMeterCtrl, COXSizeControlBar)
	//{{AFX_MSG_MAP(CStaticMeterCtrl)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticMeterCtrl message handlers
int CStaticMeterCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	//SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

	if (!m_3DMeterCtrl.Create(NULL, WS_CHILD|WS_VISIBLE|   
			SS_ICON|SS_CENTER,
		CRect(0,0,0,0), this, IDC_3DMETERCTRL))
		return -1;

	m_3DMeterCtrl.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
    
	return 0;
}

BOOL CStaticMeterCtrl::Create(CWnd * pParentWnd, const CString& sTitle /* = _T("ListOptionCtrl")*/,
					const UINT nID /* = IDC_LISTOPTIONCTRL */)
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

//-------------------------------------------------------------------
void CStaticMeterCtrl::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
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

	m_3DMeterCtrl.MoveWindow(&rect);
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

void CStaticMeterCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	/*	
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
	
	menu.InsertMenu(0, MF_BYPOSITION , ID_CTRL_METER_MAX, GetShort(ID_CTRL_METER_MAX));
	menu.InsertMenu(1, MF_BYPOSITION ,ID_CTRL_METER_MIN , GetShort(ID_CTRL_METER_MIN));
	menu.InsertMenu(2, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(3, MF_BYPOSITION ,ID_CTRL_METER_RANGEDECIMALS , GetShort(ID_CTRL_METER_RANGEDECIMALS));
	menu.InsertMenu(4, MF_BYPOSITION ,ID_CTRL_METER_VALUEDECIMALS , GetShort(ID_CTRL_METER_VALUEDECIMALS));
	menu.InsertMenu(5, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(6, MF_BYPOSITION ,ID_CTRL_METER_UNITS , GetShort(ID_CTRL_METER_UNITS));
	menu.InsertMenu(7, MF_BYPOSITION ,ID_CTRL_METER_COLOR , GetShort(ID_CTRL_METER_COLOR));
	
	
	menu.SetMenuTitle(_T("3DMeterCtrl"),MFT_GRADIENT|MFT_SIDE_TITLE);
	menu.LoadToolBar(IDR_METERCTRL);
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
	*/	

}

/*
void CStaticMeterCtrl::OnDestroy() 
{
	CStaticMeterCtrl::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_nTimer > 0)
		KillTimer(m_nTimer) ;
	
}

void CStaticMeterCtrl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	static double dStep = 0.2 ;
	static double dValue = 0.0 ;

	dValue += dStep ;
	if (dValue > m_3DMeterCtrl.m_dMaxValue)
	{
		dStep = -fabs(dStep) ;
		dValue = m_3DMeterCtrl.m_dMaxValue-dStep ;
	}
	else if (dValue < m_3DMeterCtrl.m_dMinValue)
	{	
		dStep = fabs(dStep) ;
		dValue = m_3DMeterCtrl.m_dMinValue+dStep ;
	}
		

	m_3DMeterCtrl.UpdateNeedle(dValue) ;

	CStaticMeterCtrl::OnTimer(nIDEvent);
}
*/

void CStaticMeterCtrl::SetNeedleValue(double dValue)
{
	m_3DMeterCtrl.UpdateNeedle(dValue);
}

void CStaticMeterCtrl::SetNeedleDecimalPlaces(int nPlaces)
{
	m_3DMeterCtrl.SetValueDecimals(nPlaces);
}

void CStaticMeterCtrl::SetNeedleRange(double dMin, double dMax)
{
	m_3DMeterCtrl.SetRange(dMin, dMax);
}

void CStaticMeterCtrl::SetNeedleUnits(CString szUnit)
{
	m_3DMeterCtrl.SetUnits(szUnit);
}

void CStaticMeterCtrl::SetRangeDecimalPlaces(int nPlaces)
{
	m_3DMeterCtrl.SetScaleDecimals(nPlaces);
}



void CStaticMeterCtrl::OnMeterDecimals() 
{
	
	int nTemp ;
	CStringInputDlg dlg ;

	dlg.m_strEdit.Format(TEXT("%d"), m_3DMeterCtrl.m_nValueDecimals) ;

	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID )
	{
	case LANG_SPANISH:
		dlg.m_strPrompt.Format(TEXT("Introduzca el número de espacios decimales:")) ;
		dlg.szBtnOK = _T("Aceptar");
		dlg.szBtnCancel = _T("Cancelar");
		dlg.szDlgCaption = _T("3DMeterCtrl Cuadro de entrada");
		break;
	default:
		dlg.m_strPrompt.Format(TEXT("Enter the meter decimal places:")) ;
		dlg.szBtnOK = _T("OK");
		dlg.szBtnCancel = _T("Cancel");
		dlg.szDlgCaption = _T("3DMeterCtrl InputBox");
		break;
	}


	if (dlg.DoModal() == IDOK)
	{
		nTemp = _ttoi(dlg.m_strEdit) ;
		if (nTemp >= 0)
			m_3DMeterCtrl.SetValueDecimals(nTemp) ;
	}

}

void CStaticMeterCtrl::OnMeterMax() 
{

	double dTemp ;
	CStringInputDlg dlg ;

	dlg.m_strEdit.Format(TEXT("%.*f"), m_3DMeterCtrl.m_nScaleDecimals, 
		                   m_3DMeterCtrl.m_dMaxValue) ;

	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID )
	{
	case LANG_SPANISH:
		dlg.m_strPrompt.Format(TEXT("Introduzca el límite máximo:")) ;
		dlg.szBtnOK = _T("Aceptar");
		dlg.szBtnCancel = _T("Cancelar");
		dlg.szDlgCaption = _T("3DMeterCtrl Cuadro de entrada");
		break;
	default:
		dlg.m_strPrompt.Format(TEXT("Enter the maximun value:")) ;
		dlg.szBtnOK = _T("OK");
		dlg.szBtnCancel = _T("Cancel");
		dlg.szDlgCaption = _T("3DMeterCtrl InputBox");
		break;
	}
	
	if (dlg.DoModal() == IDOK)
	{
		dTemp = _tcstod(dlg.m_strEdit, NULL) ;
		m_3DMeterCtrl.SetRange(m_3DMeterCtrl.m_dMinValue, dTemp) ;
	}
	
}

void CStaticMeterCtrl::OnMeterMin() 
{
	
	double dTemp ;
	CStringInputDlg dlg ;

	dlg.m_strEdit.Format(TEXT("%.*f"), m_3DMeterCtrl.m_nScaleDecimals, 
		                   m_3DMeterCtrl.m_dMinValue) ;

	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID )
	{
	case LANG_SPANISH:
		dlg.m_strPrompt.Format(TEXT("Introduzca el límite mínimo:")) ;
		dlg.szBtnOK = _T("Aceptar");
		dlg.szBtnCancel = _T("Cancelar");
		dlg.szDlgCaption = _T("3DMeterCtrl Cuadro de entrada");
		break;
	default:
		dlg.m_strPrompt.Format(TEXT("Enter the minimun value:")) ;
		dlg.szBtnOK = _T("OK");
		dlg.szBtnCancel = _T("Cancel");
		dlg.szDlgCaption = _T("3DMeterCtrl InputBox");
		break;
	}
	

	if (dlg.DoModal() == IDOK)
	{
		dTemp = _tcstod(dlg.m_strEdit, NULL) ;
		m_3DMeterCtrl.SetRange(dTemp, m_3DMeterCtrl.m_dMaxValue) ;
	}
	
}

void CStaticMeterCtrl::OnMeterScaleDecimals() 
{
	
	int nTemp ;
	CStringInputDlg dlg ;

	dlg.m_strEdit.Format(TEXT("%d"), m_3DMeterCtrl.m_nScaleDecimals) ;

	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	
	switch( dwLanguageID )
	{
	case LANG_SPANISH:
		dlg.m_strPrompt.Format(TEXT("Introduzca el número de espacios decimales:")) ;
		dlg.szBtnOK = _T("Aceptar");
		dlg.szBtnCancel = _T("Cancelar");
		dlg.szDlgCaption = _T("Cuadro de entrada 3DMeterCtrl");
		break;
	default:
		dlg.m_strPrompt.Format(TEXT("Enter the meter scale decimal places:")) ;
		dlg.szBtnOK = _T("OK");
		dlg.szBtnCancel = _T("Cancel");
		dlg.szDlgCaption = _T("3DMeterCtrl InputBox");
		break;
	}
	

	if (dlg.DoModal() == IDOK)
	{
		nTemp = _ttoi(dlg.m_strEdit) ;
		if (nTemp >= 0)
			m_3DMeterCtrl.SetScaleDecimals(nTemp) ;
	}

	
}

void CStaticMeterCtrl::OnMeterUnits() 
{
	
	CStringInputDlg dlg ;

	dlg.m_strEdit= m_3DMeterCtrl.m_strUnits ;

	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	switch( dwLanguageID )
	{
	case LANG_SPANISH:
		dlg.m_strPrompt.Format(TEXT("Introduzca las unidades:")) ;
		dlg.szBtnOK = _T("Aceptar");
		dlg.szBtnCancel = _T("Cancelar");
		dlg.szDlgCaption = _T("3DMeterCtrl Cuadro de entrada");
		break;
	default:
		dlg.m_strPrompt.Format(TEXT("Enter the meter units:")) ;
		dlg.szBtnOK = _T("OK");
		dlg.szBtnCancel = _T("Cancel");
		dlg.szDlgCaption = _T("3DMeterCtrl InputBox");
		break;
	}
	

	if (dlg.DoModal() == IDOK)
		m_3DMeterCtrl.SetUnits(dlg.m_strEdit) ;
	
}

void CStaticMeterCtrl::OnMeterNeedleColor() 
{
	CColorDialog dlg ;
	COLORREF colorNeedle ;

	if (dlg.DoModal() == IDOK)
	{
		colorNeedle = dlg.GetColor() ;
		m_3DMeterCtrl.SetNeedleColor(colorNeedle) ;
	}

}

