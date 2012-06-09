// ZoomViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "ZoomViewDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomViewDlg dialog


CZoomViewDlg::CZoomViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZoomViewDlg)
	m_iValue = 100;
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
}


void CZoomViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomViewDlg)
	DDX_Control(pDX, IDC_STATIC_EXPANSION, m_stcExpansion);
	DDX_Control(pDX, IDC_SPIN_CUSTOM, m_spinCustom);
	DDX_Control(pDX, IDC_EDIT_CUSTOM, m_editCustom);
	DDX_Control(pDX, IDC_RADIO_200, m_radio200);
	DDX_Control(pDX, IDC_RADIO_100, m_radio100);
	DDX_Control(pDX, IDC_RADIO_75, m_radio75);
	DDX_Control(pDX, IDC_RADIO_50, m_radio50);
	DDX_Control(pDX, IDC_RADIO_25, m_radio25);
	DDX_Control(pDX, IDC_RADIO_CUSTOM, m_radioCustom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoomViewDlg, CDialog)
	//{{AFX_MSG_MAP(CZoomViewDlg)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_CUSTOM, OnDeltaposSpinCustom)
	ON_BN_CLICKED(IDC_RADIO_200, OnRadio200)
	ON_BN_CLICKED(IDC_RADIO_100, OnRadio100)
	ON_BN_CLICKED(IDC_RADIO_75, OnRadio75)
	ON_BN_CLICKED(IDC_RADIO_50, OnRadio50)
	ON_BN_CLICKED(IDC_RADIO_25, OnRadio25)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM, OnRadioCustom)
	ON_EN_CHANGE(IDC_EDIT_CUSTOM, OnChangeEditCustom)
	ON_EN_SETFOCUS(IDC_EDIT_CUSTOM, OnSetfocusEditCustom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomViewDlg message handlers

BOOL CZoomViewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_iValue = 100;

	m_radio100.SetCheck(true);

	m_editCustom.SetValue(m_iValue);
	m_editCustom.SetFractionalDigitCount(0);
	m_editCustom.SetTextColor(RGB(0, 0, 255), true);
	m_editCustom.SetGroupLength(0);

	m_spinCustom.SetBuddy(&m_editCustom);
	m_spinCustom.SetRange(10, 200);
	m_spinCustom.SetPos(100);
	m_spinCustom.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CZoomViewDlg::OnDeltaposSpinCustom(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	

	/*
	if(pNMUpDown->iDelta <0 )
	{
		if( m_iValue > 200 )
		{
			AfxMessageBox(_T("Maximun limit has been reached"));
		}
		else
		{
			m_iValue++;
		}
		
		m_editCustom.SetValue(m_iValue*10);
		
	}
	else
	{
		if( m_iValue < 0 )
		{
			AfxMessageBox(_T("Minimum limit has been reached"));
		}
		else
		{
			m_iValue--;
		}
		
		m_editCustom.SetValue(m_iValue*10);
	}
*/

	*pResult = 0;
}

void CZoomViewDlg::OnRadio200() 
{
	m_iValue = 200;
	m_spinCustom.SetPos(m_iValue);
	m_radioCustom.SetCheck(false);
	GetDlgItem(IDC_SPIN_CUSTOM)->EnableWindow(FALSE);
	
}

void CZoomViewDlg::OnRadio100() 
{
	m_iValue = 100;
	m_spinCustom.SetPos(m_iValue);
	m_radioCustom.SetCheck(false);
	GetDlgItem(IDC_SPIN_CUSTOM)->EnableWindow(FALSE);

}

void CZoomViewDlg::OnRadio75() 
{
	m_iValue = 75;
	m_spinCustom.SetPos(m_iValue);
	m_radioCustom.SetCheck(false);
	GetDlgItem(IDC_SPIN_CUSTOM)->EnableWindow(FALSE);
}

void CZoomViewDlg::OnRadio50() 
{
	m_iValue = 50;
	m_spinCustom.SetPos(m_iValue);
	m_radioCustom.SetCheck(false);
	GetDlgItem(IDC_SPIN_CUSTOM)->EnableWindow(FALSE);
}

void CZoomViewDlg::OnRadio25() 
{
	m_iValue = 25;
	m_spinCustom.SetPos(m_iValue);
	m_radioCustom.SetCheck(false);
	GetDlgItem(IDC_SPIN_CUSTOM)->EnableWindow(FALSE);
}

void CZoomViewDlg::OnRadioCustom() 
{
	m_spinCustom.SetPos(m_iValue);
	//GetDlgItem(IDC_EDIT_CUSTOM)->EnableWindow(TRUE);
	GetDlgItem(IDC_SPIN_CUSTOM)->EnableWindow(TRUE);
	
	
}


void CZoomViewDlg::OnChangeEditCustom() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	m_iValue = m_spinCustom.GetPos();
	
	
	GetDlgItem(IDC_SPIN_CUSTOM)->EnableWindow(TRUE);
	
	if( m_radio100.GetCheck() == 1 )
	{
		m_radioCustom.SetCheck(false);

		
	}
	
	/*
	if( m_radioCustom.GetCheck() == 1 )
	{
		if(m_iValue < 10  )
		{
			CString str1 = _T("WARNING: Value range out of limit.The input value is too low.");
			CString str2 = _T("Please insert value between 10% - 200% ");
			
			CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			pMainFrame->m_wndOutputTabView.AddMsg1(str1);
			pMainFrame->m_wndOutputTabView.AddMsg1(str2);
			m_iValue = 100;
			//m_spinCustom.SetPos(100);
			
		}
		if(m_iValue > 200  )
		{
			CString str1 = _T("Value range out of limit.The input value is too high");
			CString str2 = _T("Please insert value between 10% - 200% ");
			
			CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
			pMainFrame->m_wndOutputTabView.AddMsg1(str1);
			pMainFrame->m_wndOutputTabView.AddMsg1(str2);
			
			m_iValue = 100;
			//m_spinCustom.SetPos(100);
			
		}
	}

	*/


	
	
}

void CZoomViewDlg::OnSetfocusEditCustom() 
{

	m_radioCustom.SetCheck(true);
	m_radio200.SetCheck(false);
	m_radio100.SetCheck(false);
	m_radio75.SetCheck(false);
	m_radio50.SetCheck(false);
	m_radio25.SetCheck(false);
}
