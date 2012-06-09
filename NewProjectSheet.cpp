// NewProjectSheet.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "NewProjectSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//Finish back and next id's
/*
#define FINISH	12325
#define NEXT	12324
#define BACK	12323
*/

/////////////////////////////////////////////////////////////////////////////
// CNewProjectSheet

IMPLEMENT_DYNAMIC(CNewProjectSheet, CPropertySheetEx)

CNewProjectSheet::CNewProjectSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage,
								  HBITMAP hbmWatermark, HPALETTE hpalWatermark,	HBITMAP hbmHeader)
	:CPropertySheetEx(nIDCaption, pParentWnd, iSelectPage, hbmWatermark, hpalWatermark, hbmHeader)
{
	
	// add all the pages of the wizard
	AddPage(&m_Intro);
	AddPage(&m_Page1);
	AddPage(&m_Page2);
	AddPage(&m_End);

	
	// set the WIZARD97 flag so we'll get the new look
	m_psh.dwFlags |= PSH_WIZARD97;

	
	
	


}

CNewProjectSheet::CNewProjectSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage,
								   HBITMAP hbmWatermark, HPALETTE hpalWatermark, HBITMAP hbmHeader)
	:CPropertySheetEx(pszCaption, pParentWnd, iSelectPage, hbmWatermark, hpalWatermark, hbmHeader)
{
	// add all the pages of the wizard
	AddPage(&m_Intro);
	AddPage(&m_Page1);
	AddPage(&m_Page2);
	AddPage(&m_End);

	// set the WIZARD97 flag so we'll get the new look
	m_psh.dwFlags |= PSH_WIZARD97;

}

CNewProjectSheet::~CNewProjectSheet()
{

   
}


BEGIN_MESSAGE_MAP(CNewProjectSheet, CPropertySheetEx)
	//{{AFX_MSG_MAP(CNewProjectSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProjectSheet message handlers
/*
BOOL CNewProjectSheet::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	//Handle the Property Sheets back next and finish button settings

	int iPage = GetActiveIndex( );
	if(((iPage == 0) && (nID == NEXT)) || ((iPage == 2) && (nID == BACK)) )
	{
		SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
	}
	else if(iPage == 1)
	{
		if (nID == NEXT)
			SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);
		else if (nID == BACK)
			SetWizardButtons(PSWIZB_NEXT);
	}
	return CPropertySheetEx::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CNewProjectSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheetEx::OnInitDialog();
	
	//We need only the next button
	SetWizardButtons(PSWIZB_NEXT);
	
	return bResult;
}

*/
















