// CommandDlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "CommandDlgBar.h"
#include "MainFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandDlgBar dialog


CCommandDlgBar::CCommandDlgBar()
{

}


CCommandDlgBar::~CCommandDlgBar()
{

}

void CCommandDlgBar::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CCommandDlgBar)
	//DDX_Control(pDX, IDC_COMBO_COMMAND, m_Combo);
	DDX_Control(pDX, IDC_COMBO_COMMAND, m_wndInput);
	DDX_Control(pDX, IDC_STATIC_COMMAND, m_Label);
	//}}AFX_DATA_MAP
	
	CDialogBar::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CCommandDlgBar, CDialogBar)
//{{AFX_MSG_MAP(CCommandDlgBar)
	
//}}AFX_MSG_MAP
	ON_MESSAGE (WM_CCOMMAND, UserMsg)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandDlgBar message handlers


BOOL CCommandDlgBar::Create(CWnd* pParentWnd, UINT nIDTemplate,
			UINT nStyle, UINT nID, BOOL bChange)
{
	if (!CDialogBar::Create(pParentWnd, nIDTemplate,
		nStyle, nID))
		return FALSE;

		m_bChangeDockedSize = bChange;
		m_sizeFloating = m_sizeDocked = m_sizeDefault;
		InitLayoutManager();
		UpdateData(FALSE);
	
	return TRUE;
}


BOOL CCommandDlgBar::Create(CWnd* pParentWnd, LPCTSTR lpszTemplateName,
			UINT nStyle, UINT nID, BOOL bChange)
{
	if (!CDialogBar::Create(pParentWnd, lpszTemplateName, nStyle, nID))
		return FALSE;

		m_bChangeDockedSize = bChange;
		m_sizeFloating = m_sizeDocked = m_sizeDefault;
		
	
	return TRUE;
}


void CCommandDlgBar::OnSizedOrDocked(int cx, int cy, BOOL bFloating, int flags)
{
	
	
	UNREFERENCED_PARAMETER(bFloating);
	UNREFERENCED_PARAMETER(flags);
	UNREFERENCED_PARAMETER(cx);
	UNREFERENCED_PARAMETER(cy);

	m_LayoutManager.RedrawLayout();


}


BOOL CCommandDlgBar::InitLayoutManager()
{
	BOOL retval = TRUE;

	if(!m_LayoutManager.IsAttached()) 
	{
		m_LayoutManager.Attach(this);
		m_LayoutManager.AddChild(IDC_COMBO_COMMAND);
		m_LayoutManager.SetConstraint(IDC_COMBO_COMMAND, OX_LMS_LEFT, OX_LMT_OPPOSITE, 0, IDC_STATIC_COMMAND);
		m_LayoutManager.SetConstraint(IDC_COMBO_COMMAND, OX_LMS_RIGHT, OX_LMT_SAME, -5);
		m_LayoutManager.RedrawLayout();
	}

	
	return retval;

}

CSize CCommandDlgBar::CalcDynamicLayout(int nLength, DWORD dwMode)
{

	if ((dwMode & LM_VERTDOCK) || (dwMode & LM_HORZDOCK ))
	{
		if( dwMode & LM_STRETCH) 
			return CSize((dwMode & LM_HORZ) ? 32767 : m_sizeDocked.cx, (dwMode & LM_HORZ) ? m_sizeDocked.cy : 32767);
		else
			return m_sizeDocked;
	}

	if( dwMode & LM_MRUWIDTH)
		return m_sizeFloating;
	if( dwMode & LM_LENGTHY)
		return CSize(m_sizeFloating.cx, (m_bChangeDockedSize) ? m_sizeFloating.cy = m_sizeDocked.cy = nLength : m_sizeFloating.cy = nLength);
	else
		return CSize((m_bChangeDockedSize) ? m_sizeFloating.cx = m_sizeDocked.cx = nLength : m_sizeFloating.cx = nLength, m_sizeFloating.cy);
}

BOOL CCommandDlgBar::PreTranslateMessage(MSG* pMsg) 
{
	// prevent enter or esc from closing dialog
	if(pMsg->message==WM_KEYDOWN)
          {
              if(pMsg->wParam==VK_RETURN || pMsg->wParam==VK_ESCAPE)
                  pMsg->wParam=NULL ;
          } 

	return CDialogBar::PreTranslateMessage(pMsg);
}


LRESULT CCommandDlgBar::UserMsg(WPARAM n1, LPARAM n2)
{
	//this is where the messages from ParseCommand() get sent
	
	CString *command, str;

	command = (CString *) n1;
	
	
	//Add Command to the CRichEditCtrl
	CMDIFrameWnd* pFrame = (CMDIFrameWnd*)::AfxGetApp()->m_pMainWnd;
	CMDIChildWnd* pChild = (CMDIChildWnd*) pFrame->MDIGetActive();	
	CRichEditView* pView = (CRichEditView*) pChild->GetActiveView();
	ASSERT(pView);
	pView->GetRichEditCtrl().GetWindowText(str);
	str = str + "\r\n" "Command: " + *command;
	pView->GetRichEditCtrl().SetWindowText(str);

	//Save the input
	g_currentCmdInput = *command;

	
	//Continue with the parser
	if( g_currentParserClass == EXP_PARSER_FILE )
	{
		g_bStopFlag = false; 
		CAipi_ExpParserFile epf;
		epf.cmd_input_continue();
		//AfxMessageBox(_T("Sale CMD EXP_PARS_FILE"));
		//CAipi_Tokenizer tkz;
		//tkz.v_printTokenizer();
	}
	else if( g_currentParserClass == EXP_PARSER_FILE_GLOBAL )
	{
		g_bStopFlag = false; 
		CAipi_ExpParserFileGlobal epfg;
		epfg.cmd_input_continue();

	}
	else if( g_currentParserClass == EXP_PARSER_GUI )
	{
		g_bStopFlag = false; 
		CAipi_ExpParserGUI epg;
		epg.cmd_input_continue();

		
	}
	else if( g_currentParserClass == EXP_PARSER_GUI_GLOBAL )
	{
		g_bStopFlag = false; 
		CAipi_ExpParserGUIGlobal epgg;
		epgg.cmd_input_continue();


	}

	
	
/*	
	//Add Command to the CRichEditCtrl
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->GetActiveDocument();
	
	CRichEditView *pView = (CRichEditView*) pMainFrame->GetActiveView();
	pView->GetRichEditCtrl().GetWindowText(str);
	str = str + "\r\n" "Command: " + *command;
	pView->GetRichEditCtrl().SetWindowText(str);
*/	
	
	return 0;
}

