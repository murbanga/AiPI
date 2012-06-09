// NSChartBarCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "NSChartBarCtrl.h"
#include "NSChartDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CNSChartBarCtrl, COXSizeControlBar);
/////////////////////////////////////////////////////////////////////////////
// CNSChartBarCtrl

CNSChartBarCtrl::CNSChartBarCtrl()
: COXSizeControlBar( SZBARF_STDMOUSECLICKS|SZBARF_ALLOW_MDI_FLOAT|SZBARF_SOLIDGRIPPER)
{
	m_strTitle = TEXT("NSChartCtrl");
	m_iItem = -1;
	m_dValue = 0.0;
	m_sLabel = _T("");
}

CNSChartBarCtrl::~CNSChartBarCtrl()
{
}


BEGIN_MESSAGE_MAP(CNSChartBarCtrl, COXSizeControlBar)
	//{{AFX_MSG_MAP(CNSChartBarCtrl)
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	ON_NOTIFY(NSCS_SELECTEDITEM, IDC_NSCHARTBARCTRL, OnChartSelectedItem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNSChartBarCtrl message handlers
int CNSChartBarCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	
	//Subclassing
	m_chart.SubclassDlgItem(IDC_NSCHARTBARCTRL,this);
	
	
	if (COXSizeControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	//SetSCBStyle(GetSCBStyle() | SCBS_SHOWEDGES | SCBS_SIZECHILD);

	if (!m_chart.Create(NULL, m_strTitle, WS_CHILD|WS_VISIBLE|   
			SS_ICON|SS_CENTER,
		CRect(0,0,0,0), this, IDC_NSCHARTBARCTRL))
		return -1;

	m_chart.ModifyStyleEx(0, WS_EX_CLIENTEDGE);
    

	m_chart.PrepareColors(CNSChartCtrl::SimpleColors);
	m_chart.AddValue(10,_T("One"));
	m_chart.AddValue(20,_T("Two"));
	m_chart.AddValue(40,_T("Three"));
	m_chart.AddValue(30,_T("Four"));
	m_chart.AddValue(10,_T("Five"));
	m_chart.AddValue(20,_T("Six"));

	/*
	m_chart.AddValue(40,_T("Seven"));
	m_chart.AddValue(30,_T("Eight"));
	m_chart.AddValue(10,_T("Nine"));
	m_chart.AddValue(20,_T("Ten"));
	m_chart.AddValue(40,_T("Eleven"));
	m_chart.AddValue(30,_T("Twelve"));
	m_chart.AddValue(10,_T("Thirteen"));
	m_chart.AddValue(20,_T("FourTeen"));
	m_chart.AddValue(40,_T("FifhTeen"));
	m_chart.AddValue(30,_T("SixTeen"));
*/

	m_chart.SetChartStyle(NSCS_BAR);
		
	return 0;
}

BOOL CNSChartBarCtrl::Create(CWnd * pParentWnd, const CString& sTitle /* = _T("ListOptionCtrl")*/,
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

void CNSChartBarCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
		
	/*
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	menu.GetSubMenu(3)->GetSubMenu(8)->TrackPopupMenu(TPM_LEFTALIGN| TPM_RIGHTBUTTON, point.x, point.y, m_pDockSite);

	menu.SetMenuTitle(_T("NSChartCtrl"),MFT_GRADIENT|MFT_SIDE_TITLE);
	menu.LoadToolBar(IDR_NSCHART);
*/

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
	
	menu.InsertMenu(0, MF_BYPOSITION , ID_CTRL_NSCHART_PIE, GetShort(ID_CTRL_NSCHART_PIE));
	menu.InsertMenu(1, MF_BYPOSITION ,ID_CTRL_NSCHART_BAR , GetShort(ID_CTRL_NSCHART_BAR));
	menu.InsertMenu(2, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(3, MF_BYPOSITION ,ID_CTRL_NSCHART_GRAY , GetShort(ID_CTRL_NSCHART_GRAY));
	menu.InsertMenu(4, MF_BYPOSITION ,ID_CTRL_NSCHART_COLOR , GetShort(ID_CTRL_NSCHART_COLOR));
	menu.InsertMenu(5, MF_BYPOSITION ,ID_CTRL_NSCHART_LINE , GetShort(ID_CTRL_NSCHART_LINE));
	menu.InsertMenu(6, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(7, MF_BYPOSITION ,ID_CTRL_NSCHART_ADD , GetShort(ID_CTRL_NSCHART_ADD));
	menu.InsertMenu(8, MF_BYPOSITION ,ID_CTRL_NSCHART_DEL , GetShort(ID_CTRL_NSCHART_DEL));
	menu.InsertMenu(9, MF_BYPOSITION ,ID_CTRL_NSCHART_MODIFY , GetShort(ID_CTRL_NSCHART_MODIFY));
		
	menu.SetMenuTitle(_T("NSChartCtrl"),MFT_GRADIENT|MFT_SIDE_TITLE);
	menu.LoadToolBar(IDR_NSCHART);
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
*/	

}

//-------------------------------------------------------------------
void CNSChartBarCtrl::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
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

	m_chart.MoveWindow(&rect);
}


void CNSChartBarCtrl::SetChartTitle(CString strTitle)
{
	m_strTitle = strTitle;
	
}


void CNSChartBarCtrl::OnPieStyle() 
{
	m_chart.SetChartStyle(NSCS_PIE);
	
}

void CNSChartBarCtrl::OnBarStyle() 
{
	
	m_chart.SetChartStyle(NSCS_BAR);
	
}

void CNSChartBarCtrl::OnGrayBackground() 
{
	m_chart.PrepareColors(CNSChartCtrl::GrayScale);
	m_chart.Invalidate(FALSE);
	
}

void CNSChartBarCtrl::OnColorBackground() 
{
	m_chart.PrepareColors(CNSChartCtrl::SimpleColors);
	m_chart.Invalidate(FALSE);
	
}
void CNSChartBarCtrl::OnLineBackground() 
{
	m_chart.ResetColors();
	m_chart.AddBrush(new CBrush(HS_BDIAGONAL,0x0));
	m_chart.AddBrush(new CBrush(HS_HORIZONTAL,0x0));
	m_chart.AddBrush(new CBrush(HS_VERTICAL,0x0));
	m_chart.AddBrush(new CBrush(HS_CROSS,0x0));
	m_chart.AddBrush(new CBrush(HS_DIAGCROSS,0x0));
	m_chart.AddBrush(new CBrush(HS_FDIAGONAL,0x0));
		
	m_chart.Invalidate(FALSE);
	
}


void CNSChartBarCtrl::OnAdd() 
{

	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	double dTemp;
	CNSChartDlg dlg ;

	
	switch( dwLanguageID )
	{
	case LANG_SPANISH:
		dlg.m_strTask.Format(TEXT("A G R E G A R")) ;
		dlg.szBtnCaption = _T("Agregar");
		dlg.szBtnCancel = _T("Cancelar");
		break;
	default:
		dlg.m_strTask.Format(TEXT("A D D")) ;
		dlg.szBtnCaption = _T("Add");
		dlg.szBtnCancel = _T("Cancel");
		break;
	}
	

	
	if (dlg.DoModal() == IDOK)
	{
		dTemp = _tcstod(dlg.m_sValue, NULL) ;
		if(m_iItem < 0)
		{
			
			if(dTemp > 0.0 && !dlg.m_sLabel.IsEmpty())
			{
				m_chart.AddValue(dTemp, dlg.m_sLabel, TRUE);
				m_iItem = -1;
				dTemp = 0.0;
				dlg.m_sLabel = _T("");
				
			}
		}
	
	}
	

}

void CNSChartBarCtrl::OnChartSelectedItem(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCHARTCTRL nmchart = (LPNMCHARTCTRL)pNMHDR;
	
	m_iItem = nmchart->iItem;

	if(m_iItem >= 0)
	{
		m_dValue = nmchart->dValue;
		m_sLabel = nmchart->sLabel;
	}else
	{
		m_dValue = 0;
		m_sLabel = _T("");
	}
	
	*pResult = FALSE;
}


void CNSChartBarCtrl::OnDel() 
{
	if(m_chart.DeleteItem(m_iItem))
	{
		m_dValue = 0;
		m_sLabel = _T("");
		m_iItem  = -1;
				
	}
}

void CNSChartBarCtrl::OnModify() 
{
	
	LANGID dwLanguageID = GetSystemLanguagePrimaryID();
	double dTemp;
	CNSChartDlg dlg ;

	
	switch( dwLanguageID )
	{
	case LANG_SPANISH:
		dlg.m_strTask.Format(TEXT("M O D I F I C A R")) ;
		dlg.szBtnCaption = _T("Modificar");
		dlg.szBtnCancel = _T("Cancelar");
		break;
	default:
		dlg.m_strTask.Format(TEXT("M O D I F Y")) ;
		dlg.szBtnCaption = _T("Modify");
		dlg.szBtnCancel = _T("Cancel");
		break;
	}
	
	
	if (dlg.DoModal() == IDOK)
	{
		dTemp = _tcstod(dlg.m_sValue, NULL) ;
		
		
		if(dTemp > 0.0 && !dlg.m_sLabel.IsEmpty())
		{
			m_chart.ModifyItem(m_iItem, dTemp, dlg.m_sLabel);
			
		}
	}

}
void CNSChartBarCtrl::OnUpdateModify(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_iItem>=0);
}


void CNSChartBarCtrl::OnUpdateAdd(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_iItem < 0);
}
