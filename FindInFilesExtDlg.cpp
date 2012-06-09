// FindInFilesExtDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "FindInFilesExtDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindInFilesExtDlg dialog


CFindInFilesExtDlg::CFindInFilesExtDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindInFilesExtDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindInFilesExtDlg)
	m_sFindText = _T("");
	m_bSize = FALSE;
	m_bSubFolders = TRUE;
	m_sFileMask = _T("*.knw");
	m_sBaseFolder = _T("");
	
	//}}AFX_DATA_INIT


}


void CFindInFilesExtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindInFilesExtDlg)
	DDX_Text(pDX, ID_EDITTEXT, m_sFindText);
	DDX_Check(pDX, IDC_CKSIZE, m_bSize);
	DDX_Check(pDX, IDC_CKSUBFOLDERS, m_bSubFolders);
	DDX_Text(pDX, IDC_EDITMASK, m_sFileMask);
	DDX_Control(pDX, IDC_EDITMAXSIZE, m_editMaxSize);
	DDX_Control(pDX, IDC_EDITMINSIZE, m_editMinSize);
	DDX_Text(pDX, IDC_EDITROOT, m_sBaseFolder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindInFilesExtDlg, CDialog)
	//{{AFX_MSG_MAP(CFindInFilesExtDlg)
	ON_BN_CLICKED(IDC_CKSIZE, OnCheckSize)
	ON_BN_CLICKED(IDC_BTBROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindInFilesExtDlg message handlers

void CFindInFilesExtDlg::OnBrowse() 
{
	/*
	
	CString		sFolder;
	LPMALLOC	pMalloc;

    // Gets the Shell's default allocator
    if (::SHGetMalloc(&pMalloc) == NOERROR)
    {
        BROWSEINFO bi;
        TCHAR pszBuffer[MAX_PATH];
        LPITEMIDLIST pidl;

        bi.hwndOwner = GetSafeHwnd();
        bi.pidlRoot = NULL;
        bi.pszDisplayName = pszBuffer;
        bi.lpszTitle = _T("Select a directory for searching...");
        bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
        bi.lpfn = NULL;
        bi.lParam = 0;

        // This next call issues the dialog box.
        if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)
        {
            if (::SHGetPathFromIDList(pidl, pszBuffer))
            { 
	            // At this point pszBuffer contains the selected path
				sFolder = pszBuffer;
            }

            // Free the PIDL allocated by SHBrowseForFolder.
            pMalloc->Free(pidl);
			GetDlgItem(IDC_EDITROOT)->SetWindowText(sFolder);
        }
        // Release the shell's allocator.
        pMalloc->Release();

		
    }

	*/

	COXFolderPickerDlg dlg;
	dlg.DoModal( );
	
	m_sBaseFolder = dlg.GetFolderPath();
	UpdateData(false);
	
	
	
}

void CFindInFilesExtDlg::OnCheckSize() 
{
	BOOL bEnable = (((CButton *)GetDlgItem(IDC_CKSIZE))->GetCheck() == 1);

	GetDlgItem(IDC_EDITMINSIZE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDITMAXSIZE)->EnableWindow(bEnable);
	
}


BOOL CFindInFilesExtDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetCurrentDirectory( MAX_SIZE_PATH, m_sBaseFolder.GetBufferSetLength(MAX_SIZE_PATH) );
	m_sFindText = g_findText;
	m_editMaxSize.SetFractionalDigitCount(0);
	m_editMinSize.SetFractionalDigitCount(0);
	m_editMaxSize.SetGroupSeparator(',');
	m_editMinSize.SetGroupSeparator(',');
	m_editMaxSize.SetGroupLength(3);
	m_editMinSize.SetGroupLength(3);
	
	UpdateData(false);

	
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
