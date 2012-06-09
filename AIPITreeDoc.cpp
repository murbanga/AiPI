// AIPITreeDoc.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "AIPITreeDoc.h"
#include "DocTemplateEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAIPITreeDoc
IMPLEMENT_DYNCREATE(CAIPITreeDoc, CDocument)

EXTENSION CAIPITreeDoc::m_apszExtension[] =
{
	EXTENSION(_T("idt"), _T("Decision Tree Files")),
	EXTENSION(_T("tre"), _T("Aipi Tree Files")),
	EXTENSION(_T("csv"), _T("Comma Delimited Files")),
	EXTENSION(_T("apj"), _T("Aipi Project Files")),
	
};

HINT_EXT CAIPITreeDoc::m_aheSave[] =
{
	HINT_EXT(HINT_SAVE_INDENT_TYPE,  FF_INDENT_TYPE),
	HINT_EXT(HINT_SAVE_TREE_TYPE,   FF_TREE_TYPE),
	HINT_EXT(HINT_SAVE_CSV_TYPE,    FF_CSV_TYPE),
	HINT_EXT(HINT_SAVE_PROJ_TYPE,   FF_PROJ_TYPE),
	
};

HINT_EXT CAIPITreeDoc::m_aheLoad[] =
{
	HINT_EXT(HINT_LOAD_INDENT_TYPE, FF_INDENT_TYPE),
	HINT_EXT(HINT_LOAD_TREE_TYPE,  FF_TREE_TYPE),
	HINT_EXT(HINT_LOAD_CSV_TYPE,   FF_CSV_TYPE),
	HINT_EXT(HINT_LOAD_PROJ_TYPE,  FF_PROJ_TYPE),
	
};




CAIPITreeDoc::CAIPITreeDoc()
{
	ASSERT(ARRAY_SIZE(m_aheLoad) == FF_MAX_TYPES);
	ASSERT(ARRAY_SIZE(m_aheSave) == FF_MAX_TYPES);
	ASSERT(ARRAY_SIZE(m_apszExtension) == FF_MAX_TYPES);

	GetCurrentDirectory(_MAX_PATH, m_ExamplesPath);
	_tcscat(m_ExamplesPath, _T("\\Examples"));
	_tcscpy(m_szDelimiter, _T(","));	// Default delimiter for *.csv type
	
}

BOOL CAIPITreeDoc::OnNewDocument()
{
	
	UpdateAllViews(NULL, HINT_NEW);
		return TRUE;
	
	
	/*
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
	*/
}

CAIPITreeDoc::~CAIPITreeDoc()
{
}


BEGIN_MESSAGE_MAP(CAIPITreeDoc, CDocument)
	//{{AFX_MSG_MAP(CAIPITreeDoc)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAIPITreeDoc diagnostics

#ifdef _DEBUG
void CAIPITreeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAIPITreeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAIPITreeDoc serialization

void CAIPITreeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAIPITreeDoc commands

void CAIPITreeDoc::OnFileSave() 
{
	if (m_strFileNamePath.IsEmpty())
		OnFileSaveAs();
	else
		SaveFile();
}

void CAIPITreeDoc::GetFilter(TCHAR sFilter[], HINT_EXT ahe[])
{
	int k;
	const int MAX_TYPES = 3;
	//const int MAX_TYPES = 6;
	TCHAR *name[MAX_TYPES];
	TCHAR *text[MAX_TYPES];

	for (k = 0; k < MAX_TYPES; k++)
	{
		name[k] = m_apszExtension[ahe[k].m_ff].m_name;
		text[k] = m_apszExtension[ahe[k].m_ff].m_text;
	}

	
	_stprintf(sFilter, 

		_T("%s (*.%s)|*.%s|")
		_T("Aipi Session File(*.ssn)|*.ssn|")
		_T("Aipi Knowledge File (*.knw)|*.knw|")
		_T("All Files (*.*)|*.*||"), 
		name[FF_INDENT_TYPE],  text[FF_INDENT_TYPE],  text[FF_INDENT_TYPE] );
		

	/*
	_stprintf(sFilter, 

		_T("%s (*.%s)|*.%s|")
		_T("%s (*.%s)|*.%s|")
		_T("%s (*.%s)|*.%s|")
		_T("%s (*.%s)|*.%s|")
		_T("Aipi Session File(*.ssn)|*.ssn|")
		_T("Aipi Knowledge File (*.knw)|*.knw|")
		_T("All Files (*.*)|*.*||"), 
		name[FF_AIPI_TYPE],  text[FF_AIPI_TYPE],  text[FF_AIPI_TYPE],
		name[FF_TREE_TYPE],  text[FF_TREE_TYPE],  text[FF_TREE_TYPE], 
		name[FF_INDENT_TYPE], text[FF_INDENT_TYPE], text[FF_INDENT_TYPE],
		name[FF_CSV_TYPE],   text[FF_CSV_TYPE],   text[FF_CSV_TYPE]);
	*/	

	for (k = 0; sFilter[k] != 0; k++)
		sFilter[k] = sFilter[k] == '|' ? '\0' : sFilter[k];
}

void CAIPITreeDoc::SaveFile()
{
	TCHAR dir[_MAX_DIR];
	TCHAR drive[_MAX_DRIVE];
	TCHAR ext[_MAX_EXT];
	TCHAR fname[_MAX_FNAME];
	int k;
	long lHint = HINT_LOAD_TREE_TYPE;

	if (!m_strFileNamePath.IsEmpty())
	{
		_tsplitpath(m_strFileNamePath, drive, dir, fname, ext);

		for(k = 0; k < ARRAY_SIZE(m_aheSave); k++)
		{
			if (_tcscmp(m_apszExtension[m_aheSave[k].m_ff].m_text, ext + 1) == 0)
			{
				lHint = m_aheSave[k].m_hint;
				break;
			}
		}
		
		CString strName = (LPCTSTR)fname;
		CString strExt = (LPCTSTR)ext;
		m_strFileNameExt = strName + strExt;
		SetTitle((LPCTSTR)strName);
		UpdateAllViews(NULL, lHint);
		
		// Add to MRU file list
		AddToRecentFileList(m_strFileNamePath);
	}
}

// Checks if the modified flag is on. If so, it displays a warning message
// (The file was changed. Do you want to save or to discard the modifications?)

BOOL CAIPITreeDoc::SaveModified() 
{
	if (!IsModified())
		return TRUE;        // ok to continue

	CString prompt, sTitle;

	sTitle = GetTitle();
	prompt.Format(_T("File %s has changed.\nDo you want to save the changes?"),
		sTitle);
	switch (AfxMessageBox(prompt, MB_YESNOCANCEL))
	{
	case IDCANCEL:
		return FALSE;       // don't continue

	case IDYES:
		// If so, either Save or Update, as appropriate
		OnFileSave();
		break;

	case IDNO:
		// If not saving changes, revert the document
		SetModifiedFlag(false);
		break;

	default:
		ASSERT(FALSE);
		break;
	}
	return TRUE;    // keep going
}



void CAIPITreeDoc::CreateNewFrame()
{
		CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
		CDocument *pDoc = NULL;
		CFrameWnd *pFrameWnd = NULL;
		CView *pView = NULL;
		CDocTemplate* pDocTemplate = pApp->m_pAIPITreeDocTemplate;
		//CDocTemplate* pDocTemplate = pDoc->GetDocTemplate();	

		
		pDoc = pApp->SearchDocument(m_strFileNamePath);
		if (pDoc != NULL)
		{
			// Document has already been opened, attach a new view to it
			pFrameWnd = pDocTemplate->CreateNewFrame(pDoc, NULL);
			if (pFrameWnd == NULL)
			{
				TRACE0("CAIPIApp::OpenDocument : Failed to create new frame for existing document.\n");
				pDoc = NULL;
				return;
			}
		
			// ... Frame is initially visible, this is necessary to send
			//     WM_INITIALUPDATE to the view
			pDocTemplate->InitialUpdateFrame(pFrameWnd, pDoc, TRUE);
			pView = pApp->GetFirstView(pFrameWnd);
			ASSERT(pView != NULL);
		}

}


void CAIPITreeDoc::OpenMDIDoc()
{
	CString strExt = m_strFileNamePath.Right(3);
	
	if(!m_strFileNamePath.IsEmpty())
	{
		
		if( strExt == _T("knw") || strExt == _T("txt") )
		{
		
			CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
			pApp->OpenDocumentFile(m_strFileNamePath);	
		
			if( pApp == NULL )
			{
				AfxMessageBox( _T("File was not found."));
			}
			return;
		
		}
		else if( strExt == _T("ssn") || strExt == _T("rtf") )
		{
			CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
			pApp->m_pAIPIDocTemplate->OpenDocumentFile(m_strFileNamePath);	
		
			if( pApp == NULL )
			{
				AfxMessageBox( _T("File was not found."));
			
			}
			return;
		
		}
		else if( strExt == _T("idt") || strExt == _T("csv") || strExt == _T("tre") )
		{
			CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
			pApp->m_pAIPITreeDocTemplate->OpenDocumentFile(m_strFileNamePath);	
		
			if( pApp == NULL )
			{
				AfxMessageBox( _T("File was not found."));
			
			}

			return;
		
		}
		else
		{
			AfxMessageBox( _T("Unable to open file. The file type is not compatible."));
		}

	}
		
		// Add to MRU file list
		AddToRecentFileList(m_strFileNamePath);


}




void CAIPITreeDoc::OpenFile()
{
	TCHAR dir[_MAX_DIR];
	TCHAR drive[_MAX_DRIVE];
	TCHAR ext[_MAX_EXT];
	TCHAR fname[_MAX_FNAME];
	int k;
	long lHint = HINT_LOAD_INDENT_TYPE;
	CString strExt = m_strFileNamePath.Right(3);

	if(!m_strFileNamePath.IsEmpty())
	{
		
		if( strExt == _T("knw") || strExt == _T("txt") )
		{
		
			CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
			pApp->OpenDocumentFile(m_strFileNamePath);	
		
			if( pApp == NULL )
			{
				AfxMessageBox( _T("File was not found."));
			}
			return;
		
		}
		if( strExt == _T("ssn") || strExt == _T("rtf") )
		{
			CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();
			pApp->m_pAIPIDocTemplate->OpenDocumentFile(m_strFileNamePath);	
		
			if( pApp == NULL )
			{
				AfxMessageBox( _T("File was not found."));
			
			}
			return;
		
		}
		
				
		_tsplitpath((LPCTSTR)m_strFileNamePath, drive, dir, fname, ext);

		for(k = 0; k < ARRAY_SIZE(m_aheLoad); k++)
		{
			if (_tcscmp(m_apszExtension[m_aheLoad[k].m_ff].m_text, ext + 1) == 0)
			{
				
				lHint = m_aheLoad[k].m_hint;
				break;
			}
			
		}

		
		CString strName = (LPCTSTR)fname;
		CString strExt = (LPCTSTR)ext;
		m_strFileNameExt = strName + strExt;
		
		SetTitle((LPCTSTR)strName);
		UpdateAllViews(NULL, lHint);
	  		
			// Add to MRU file list
		AddToRecentFileList(m_strFileNamePath);
		
	}

}

void CAIPITreeDoc::OnFileSaveAs() 
{
	OPENFILENAME   ofn;
	TCHAR szFile[MAX_PATH] = TEXT("");
	TCHAR sFilter[256];

	GetFilter(sFilter, m_aheLoad);

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize         = sizeof(ofn);
	ofn.hwndOwner           = NULL;
	ofn.hInstance           = GetModuleHandle(NULL);
	ofn.lpstrFilter         = sFilter;
	ofn.lpstrCustomFilter   = NULL;
	ofn.nMaxCustFilter      = 0;
	ofn.nFilterIndex        = 1;
	ofn.nMaxFile            = _MAX_PATH;
	ofn.lpstrFileTitle      = NULL;
	ofn.nMaxFileTitle       = 0;
	ofn.lpstrInitialDir     = m_ExamplesPath;
	ofn.lpstrDefExt			= m_apszExtension[m_aheSave[0].m_ff].m_text;
	ofn.lpstrTitle          = TEXT("Save As");
	ofn.lpTemplateName      = MAKEINTRESOURCE(IDD_OPEN_DELIMITER_DLG);
	ofn.lpfnHook            = (LPOFNHOOKPROC)DelimiterHookProc;
	ofn.lCustData           = (DWORD)this;
	ofn.Flags               = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | 
									OFN_ENABLEHOOK | OFN_ENABLETEMPLATE | 0;
	ofn.lpstrFile = szFile;

	if (GetSaveFileName(&ofn))
	{
		m_strFileNamePath = ofn.lpstrFile;
		SaveFile();
	}
}

void CAIPITreeDoc::OnFileOpen() 
{
	// Customize the common dialog: CFileDialog with a hook procedure to be able to ask
	// about the suitable delimiter.

	OPENFILENAME   ofn;
	TCHAR sFilter[256];
	TCHAR szFile[MAX_PATH] = TEXT("");

	if (!SaveModified())
		return;
	GetFilter(sFilter, m_aheLoad);

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize         = sizeof(ofn);
	ofn.hwndOwner           = NULL;
	ofn.hInstance           = GetModuleHandle(NULL);
	ofn.lpstrFilter         = sFilter;
	ofn.lpstrCustomFilter   = NULL;
	ofn.nMaxCustFilter      = 0;
	ofn.nFilterIndex        = 1;
	ofn.nMaxFile            = _MAX_PATH;
	ofn.lpstrFileTitle      = NULL;
	ofn.nMaxFileTitle       = 0;
	ofn.lpstrInitialDir     = m_ExamplesPath;
	ofn.lpstrDefExt			= m_apszExtension[m_aheLoad[0].m_ff].m_text;
	ofn.lpstrTitle          = TEXT("Open");
	ofn.lpTemplateName      = MAKEINTRESOURCE(IDD_OPEN_DELIMITER_DLG);
	ofn.lpfnHook            = (LPOFNHOOKPROC)DelimiterHookProc;
	ofn.lCustData           = (DWORD)this;
	ofn.Flags               = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST |
								OFN_HIDEREADONLY | OFN_ENABLEHOOK | OFN_ENABLETEMPLATE | 0;
	ofn.lpstrFile = szFile;

	if (GetOpenFileName(&ofn))
	{
		m_strFileNamePath = ofn.lpstrFile;
		OpenMDIDoc();
	}
}

BOOL CALLBACK DelimiterHookProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	static CAIPITreeDoc *pted = NULL;
	LPOFNOTIFY lpon;
	BOOL bIsCsvSelected;

	static int aid[] =
	{
		IDC_STATIC_GROUP,
		IDC_TAB,
		IDC_COMMA,
		IDC_OTHER,
		IDC_DELIMITER,
	}, k;
	static HWND ahCtrl[ARRAY_SIZE(aid)];

	switch(uMessage)
	{
	case WM_INITDIALOG:
		for (k = 0; k < ARRAY_SIZE(aid); k++)
		{
			ahCtrl[k] = GetDlgItem(hWnd, aid[k]);
			EnableWindow(ahCtrl[k], false);
		}

		pted = (CAIPITreeDoc *)((LPOPENFILENAME)(lParam))->lCustData;
		SendDlgItemMessage(hWnd, IDC_DELIMITER, EM_LIMITTEXT, 1, 0);
		SendDlgItemMessage(hWnd, IDC_DELIMITER, WM_SETTEXT, 0,(LPARAM) pted->m_szDelimiter); 
		CheckRadioButton(hWnd, IDC_TAB, IDC_OTHER, IDC_COMMA);
		break;

	case WM_COMMAND: 
		if(HIWORD (wParam) == EN_CHANGE && LOWORD(wParam) == IDC_DELIMITER)
		{
			// Get the character
			SendDlgItemMessage(hWnd, IDC_DELIMITER, EM_GETLINE,0,(LPARAM) pted->m_szDelimiter); 
			pted->m_szDelimiter[1] = 0;
		}
		if (HIWORD (wParam) == BN_CLICKED)
			EnableWindow(ahCtrl[4], LOWORD(wParam) == IDC_OTHER);
		break;

	case WM_NOTIFY:
		lpon = (LPOFNOTIFY) lParam; 
		if (lpon->hdr.code == CDN_FILEOK)
		{
			if (IsDlgButtonChecked(hWnd, IDC_TAB))
				_tcscpy(pted->m_szDelimiter, _T("\t"));
			else if (IsDlgButtonChecked(hWnd, IDC_COMMA))
				_tcscpy(pted->m_szDelimiter, _T(","));
		}
		if (lpon->hdr.code == CDN_TYPECHANGE)
		{
			bIsCsvSelected = lpon->lpOFN->nFilterIndex == FF_CSV_TYPE + 1;
			for (k = 0; aid[k] != IDC_DELIMITER; k++)
				EnableWindow(ahCtrl[k], bIsCsvSelected);
		}
		break;
	}
	return FALSE;
}

BOOL CAIPITreeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	
	
	if (SaveModified())
	{
		m_strFileNamePath = lpszPathName;
		OpenFile();
		

		
	}
	return TRUE;
	
}


void CAIPITreeDoc::OnDisplayDirectoryTree() 
{
	// Customize the common dialog: CFileDialog with a hook procedure to be able to ask
	// about the suitable delimiter.
	BROWSEINFO bi;
	LPMALLOC pMalloc = NULL;
	LPITEMIDLIST pidl = NULL;
	TCHAR szFileName[MAX_PATH];
	long lHint = HINT_LOAD_DIRECTORY;
	BOOL bRC;
	CString str;

	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	
	if (!SaveModified())
		return;
	pidl = SHBrowseForFolder(&bi);
	if (pidl != NULL)
	{
		bRC = SHGetPathFromIDList(pidl, szFileName);
		if (!bRC)
		{
			AfxMessageBox(_T("Invalid selection!"));
			return;
		}
		m_strFileNamePath = szFileName;
		SHGetMalloc(&pMalloc);
		pMalloc->Free(pidl);  
		pMalloc->Release(); 

		// When we read a directory, we dwr paths of the form:
		// X:\Subdirectory_1\...Subdirectory_n". Reading that is similar to reading CSV
		// files, where the delimiter is "\".
		_tcscpy(m_szDelimiter, _T("\\"));

// Title is "Untitled"
//		>m_strFileName is used as the default file name , when the Save 
//		function (Ctrl+S) is called. If Ctrl+D was called, we cannot, of course, 
//		giving the tree name we built, the name of an existing directory. So, we reset
//		m_strFileName as soon as the directory is loaded, to force the user to choose a name, 
//		when he saves the tree. See last instructions of function:
//		void CEditTreeCtrl::OnLoadEntireTree(FILE_FORMAT ff, CTreeType &tt) after
//		......................
//		    if (ff == FF_DIRECTORY_TYPE)
//			{
//			}
		SetTitle(_T("Untitled"));
		UpdateAllViews(NULL, lHint);
	}
}

void CAIPITreeDoc::AddToRecentFileList(LPCTSTR lpszPathName)
{
	((CAIPIApp*)AfxGetApp())->AddToRecentFileList(lpszPathName);
}


void CAIPITreeDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDocument::SetPathName(lpszPathName, FALSE);
	CDocTemplateEx* pDocTemplate = (CDocTemplateEx *)GetDocTemplate();
	pDocTemplate->AddToRecentFileList(lpszPathName);
	
	
	//CDocument::SetPathName(lpszPathName, bAddToMRU);
}
