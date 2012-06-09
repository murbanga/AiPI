// AIPIView.h : interface of the CAIPIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPIVIEW_H__13780E61_18D7_4A4C_89A2_AE1D9B2C34C1__INCLUDED_)
#define AFX_AIPIVIEW_H__13780E61_18D7_4A4C_89A2_AE1D9B2C34C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_Main.h"
#include "OXSkinnedView.h"


#define MAINVIEW CRichEditView

class CAIPICntrItem;

class CAIPIView : public COXSkinnedView<MAINVIEW>
{
protected: // create from serialization only
	CAIPIView();
	DECLARE_DYNCREATE(CAIPIView)

// Attributes
public:
	CAIPIDoc* GetDocument();

public:
	int			m_nPage;
	CString		m_sDocContent;	
	

// Operations
public:
	void PrintPageHeader(CDC *pDC);
	void PrintPageFooter(CDC *pDC);
	CString PrintDate();
	void	UpdateSkinMenus();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAIPIView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAIPIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAIPIView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnCtrlImg2Open();
	afx_msg void OnCtrlImg2Rotateleft();
	afx_msg void OnCtrlImg2Rotateright();
	afx_msg void OnCtrlImg2Zoomin();
	afx_msg void OnCtrlImg2Zoomout();
	afx_msg void OnCtrlImg2Stretchnothing();
	afx_msg void OnCtrlImg2Stretchheight();
	afx_msg void OnCtrlImg2Stretchwidth();
	afx_msg void OnCtrlImg2Stretchall();
	afx_msg void OnUpdateCtrlImg2Open(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImg2Rotateleft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImg2Rotateright(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImg2Zoomin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImg2Zoomout(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImg2Stretchnothing(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImg2Stretchheight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImg2Stretchwidth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImg2Stretchall(CCmdUI* pCmdUI);
	afx_msg void OnCtrlNSChartPie();
	afx_msg void OnCtrlNSChartBar();
	afx_msg void OnCtrlNSChartGray();
	afx_msg void OnCtrlNSChartColor();
	afx_msg void OnCtrlNSChartLine();
	afx_msg void OnCtrlNSChartAdd();
	afx_msg void OnCtrlNSChartDel();
	afx_msg void OnCtrlNSChartModify();
	afx_msg void OnUpdateCtrlNSChartPie(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlNSChartBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlNSChartGray(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlNSChartColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlNSChartLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlNSChartAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlNSChartDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlNSChartModify(CCmdUI* pCmdUI);
	afx_msg void OnCtrlChartBarSerie();
	afx_msg void OnCtrlChartBarDel();
	afx_msg void OnCtrlChartBarBckColor();
	afx_msg void OnCtrlChartBarLegendVisible();
	afx_msg void OnCtrlChartBarPanEnable();
	afx_msg void OnCtrlChartBarZoomEnable();
	afx_msg void OnCtrlChartBarTitle();
	afx_msg void OnCtrlChartBarAxis();
	afx_msg void OnUpdateCtrlChartBarSerie(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlChartBarDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlChartBarBckColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlChartBarLegendVisible(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlChartBarPanEnable(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlChartBarZoomEnable(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlChartBarTitle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlChartBarAxis(CCmdUI* pCmdUI);
	afx_msg void OnCtrlGraphBarToolTip();
	afx_msg void OnCtrlGraphBarSquarePoints();
	afx_msg void OnCtrlGraphBarAxis();
	afx_msg void OnCtrlGraphBarAxisProp();
	afx_msg void OnCtrlGraphBarScatter();
	afx_msg void OnCtrlGraphBarCoordinates();
	afx_msg void OnCtrlGraphBarAnimation();
	afx_msg void OnCtrlGraphBarQuit();
	afx_msg void OnUpdateCtrlGraphBarAnimation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlGraphBarQuit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlGraphBarToolTip(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlGraphBarScatter(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlGraphBarSquarePoints(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlGraphBarAxis(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlGraphBarAxisProp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlGraphBarCoordinates(CCmdUI* pCmdUI);
	afx_msg void OnCtrlCalendarGoToDate();
	afx_msg void OnCtrlCalendarToday();
	afx_msg void OnCtrlCalendarSunday();
	afx_msg void OnCtrlCalendarMonday();
	afx_msg void OnCtrlCalendarTuesday();
	afx_msg void OnCtrlCalendarWednesday();
	afx_msg void OnCtrlCalendarThursday();
	afx_msg void OnCtrlCalendarFriday();
	afx_msg void OnCtrlCalendarSaturday();
	afx_msg void OnCtrlCalendarMark();
	afx_msg void OnCtrlCalendarAdd();
	afx_msg void OnCtrlCalendarClear();
	afx_msg void OnUpdateCtrlCalendarGoToDate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlCalendarToday(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlCalendarSunday(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlCalendarMonday(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlCalendarTuesday(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlCalendarWednesday(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlCalendarThursday(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlCalendarFriday(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlCalendarSaturday(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlCalendarMark(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlCalendarAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlCalendarClear(CCmdUI* pCmdUI);
	afx_msg void OnCtrlMeterMax();
	afx_msg void OnCtrlMeterMin();
	afx_msg void OnCtrlMeterRangeDecimals();
	afx_msg void OnCtrlMeterValueDecimals();
	afx_msg void OnCtrlMeterUnits();
	afx_msg void OnCtrlMeterColor();
	afx_msg void OnUpdateCtrlMeterMax(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlMeterMin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlMeterRangeDecimals(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlMeterValueDecimals(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlMeterUnits(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlMeterColor(CCmdUI* pCmdUI);
	afx_msg void OnCtrlImgOpen();
	afx_msg void OnCtrlImgLeft();
	afx_msg void OnCtrlImgCenterx();
	afx_msg void OnCtrlImgRight();
	afx_msg void OnCtrlImgTop();
	afx_msg void OnCtrlImgCentery();
	afx_msg void OnCtrlImgBottom();
	afx_msg void OnCtrlImgStretchnormal();
	afx_msg void OnCtrlImgStretch();
	afx_msg void OnCtrlImgStretchxy();
	afx_msg void OnCtrlImgStretchsm();
	afx_msg void OnCtrlImgTile();
	afx_msg void OnUpdateCtrlImgOpen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImgLeft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImgCenterx(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImgRight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImgTop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImgCentery(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImgBottom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImgStretchnormal(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImgStretch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImgStretchxy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImgStretchsm(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlImgTile(CCmdUI* pCmdUI);
	afx_msg void OnCtrlListBarAdd();
	afx_msg void OnCtrlListBarDelete();
	afx_msg void OnCtrlListBarIndent();
	afx_msg void OnCtrlListBarHighLight();
	afx_msg void OnCtrlListBarBackColor();
	afx_msg void OnCtrlListBarFont();
	afx_msg void OnCtrlListBarTextBkColor();
	afx_msg void OnUpdateCtrlListBarAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlListBarDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlListBarIndent(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlListBarHighLight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlListBarBackColor(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlListBarFont(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtrlListBarTextBkColor(CCmdUI* pCmdUI);
	afx_msg void OnCtrlListMultiOptionColor();
	afx_msg void OnCtrlListMultiOptionFontType();
	afx_msg void OnCtrlListmultioptionResetFontType();
	afx_msg void OnCtrlListMultiOptionDeleteItem();
	afx_msg void OnCtrlListMultiOptionClear();
	afx_msg void OnCtrlListMultiOptionSort();
	afx_msg void OnCtrlListMultiOptionCheckable();
	afx_msg void OnCtrlListMultiOptionMultichk();
	afx_msg void OnCtrlListMultiOptionEditable();
	afx_msg void OnCtrlListMultiOptionGridLines();
	afx_msg void OnCtrlListMultiOptionAutoEdit();
	afx_msg void OnCtrlListMultiOptionShowSelection();
	afx_msg void OnCtrlListMultiOptionHorizontalGrid();
	afx_msg void OnCtrlListMultiOptionVerticalGrid();
	afx_msg void OnCtrlListMultiOptionColResize();
	afx_msg void OnCtrlListMultiOptionRight();
	afx_msg void OnCtrlListMultiOptionCenter();
	afx_msg void OnCtrlListMultiOptionLeft();
	afx_msg void OnCtrlListMultiOptionFontBkColor();
	afx_msg void OnCtrlListMultiOptionBkColor();
	afx_msg void OnCtrlListMultiOptionGridLinesColor();
	afx_msg void OnCtrlListMultiOptionNormalGridLines();
	afx_msg void OnCtrlListMultiOptionNormalChkBox();
	afx_msg void OnCtrlInfoBarFontStyle();
	afx_msg void OnCtrlInfoBarFontColor();
	afx_msg void OnCtrlInfoBarBkColor();
	afx_msg void OnCtrlOledbDlgMsAcess();
	afx_msg void OnCtrlOledbDlgMsSqlServer();
	afx_msg void OnCtrlOledbDlgMsOracle();
	afx_msg void OnCtrlOledbDlgOracle();
	afx_msg void OnCtrlOledbDlgMySql();
	afx_msg void OnCtrlOledbDlgDb2();
	afx_msg void OnCtrlDxfCadDlgOpen();
	afx_msg void OnSettingsSkinClassic();
	afx_msg void OnSettingsSkinOfficeXP();
	afx_msg void OnSettingsSkinOffice2003();
	afx_msg void OnExecLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AIPIView.cpp
inline CAIPIDoc* CAIPIView::GetDocument()
   { return (CAIPIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIPIVIEW_H__13780E61_18D7_4A4C_89A2_AE1D9B2C34C1__INCLUDED_)
