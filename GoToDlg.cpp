// GoToDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "AIPIEditorDoc.h"
#include "AIPIEditorView.h"
#include "GoToDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGoToDlg dialog


CGoToDlg::CGoToDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGoToDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGoToDlg)
	
	//}}AFX_DATA_INIT
}


void CGoToDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGoToDlg)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_STATIC_GOTO, m_labelGoTo);
	DDX_Control(pDX, IDC_EDIT_GOTO,  m_editGoTo);
	DDX_Control(pDX, IDC_RADIO_CHAR, m_radioChar);
	DDX_Control(pDX, IDC_RADIO_LINE, m_radioLine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGoToDlg, CDialog)
	//{{AFX_MSG_MAP(CGoToDlg)
	ON_BN_CLICKED(IDC_RADIO_CHAR, OnRadioChar)
	ON_BN_CLICKED(IDC_RADIO_LINE, OnRadioLine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGoToDlg message handlers

BOOL CGoToDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_editGoTo.SetFractionalDigitCount(0);
	m_editGoTo.SetGroupSeparator(',');
	m_editGoTo.SetGroupLength(3);

	OnRadioChar();

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGoToDlg::GoToChar()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	
	long charPos = m_editGoTo.GetValue();
	rCtrl.GotoPos(charPos);
	int charLine = rCtrl.LineFromPosition(charPos);

	// Reset Scintilla Markers 
	rCtrl.MarkerDeleteAll(0);

	// Initilaize markers
	rCtrl.MarkerDefine(0, SC_MARK_DOTDOTDOT);
	rCtrl.MarkerSetFore(0, RGB( 95, 95, 95 ));
	rCtrl.MarkerSetBack(0, RGB( 95, 95, 95 ));
		
	// Set marker to proper line
	rCtrl.GotoLine(charLine );
	rCtrl.MarkerAdd((charLine), 0);

	//Set the cursor position in the GUI
	rCtrl.SetFocus();
	rCtrl.SetSel(charPos, charPos + 1);
}


void CGoToDlg::GoToLine()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CScintillaView* pView = (CScintillaView*) pChild->GetActiveView();
	ASSERT(pView);
	CScintillaCtrl& rCtrl = pView->GetCtrl();
	
	long linePos = m_editGoTo.GetValue();
	rCtrl.GotoLine(linePos);

	// Reset Scintilla Markers 
	rCtrl.MarkerDeleteAll(0);

	// Initilaize markers
	rCtrl.MarkerDefine(0, SC_MARK_MINUS);
	rCtrl.MarkerSetFore(0, RGB( 128, 128, 128 ));
	rCtrl.MarkerSetBack(0, RGB( 128, 128, 128 ));

	// Set error marker to proper line
	rCtrl.GotoLine(linePos -1 );
	rCtrl.MarkerAdd((linePos - 1), 0);
	

}


void CGoToDlg::OnRadioChar() 
{
	m_radioChar.SetCheck(true);
	m_labelGoTo.SetWindowText(_T("Enter character position:"));
	
}

void CGoToDlg::OnRadioLine() 
{
	m_radioLine.SetCheck(true);
	m_labelGoTo.SetWindowText(_T("Enter line position:"));
	
}

void CGoToDlg::OnOK() 
{
	if( m_radioChar.GetCheck() )
	{
		GoToChar();
	}
	else
	{
		GoToLine();
	}
	
	CDialog::OnOK();
}
