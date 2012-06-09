#if !defined(AFX_AIPITREEDOC_H__79BB2D6F_EB2B_455D_A15E_DBF8A95C4F76__INCLUDED_)
#define AFX_AIPITREEDOC_H__79BB2D6F_EB2B_455D_A15E_DBF8A95C4F76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AIPITreeDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAIPITreeDoc document
BOOL CALLBACK DelimiterHookProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

enum FILE_FORMAT
{
    FF_INDENT_TYPE,
	FF_TREE_TYPE,
	FF_CSV_TYPE,
	FF_PROJ_TYPE,
        
	FF_MAX_TYPES = 4,
	FF_DIRECTORY_TYPE, // Special type to read directories
	FF_CLIPBOARD_TYPE, // Special type to copy to/from the Clipboard
	
};


enum HINT
{
	HINT_NONE = 0,
	HINT_NEW,
	HINT_LOAD_DIRECTORY,
	HINT_LOAD_INDENT_TYPE,
	HINT_LOAD_TREE_TYPE,
	HINT_LOAD_CSV_TYPE,
	HINT_LOAD_PROJ_TYPE,
	HINT_SAVE_INDENT_TYPE,
	HINT_SAVE_TREE_TYPE,
	HINT_SAVE_CSV_TYPE,
	HINT_SAVE_PROJ_TYPE,
	
};

struct EXTENSION
{
	TCHAR *m_text;
	TCHAR *m_name;

	EXTENSION(TCHAR *text, TCHAR *name)
	{
		m_text = text;
		m_name = name;
	}
};

struct  HINT_EXT
{
	HINT m_hint;
	FILE_FORMAT m_ff;

	HINT_EXT(HINT hint, FILE_FORMAT ff)
	{
		m_hint = hint;
		m_ff = ff;
	}
};



class CAIPITreeDoc : public CDocument
{
protected:
	CAIPITreeDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAIPITreeDoc)

	void GetFilter(TCHAR sFilter[], HINT_EXT ahe[]);
	
	static HINT_EXT m_aheSave[FF_MAX_TYPES];
	static HINT_EXT m_aheLoad[FF_MAX_TYPES];
	static EXTENSION m_apszExtension[FF_MAX_TYPES];


// Attributes
public:
	CTreeType m_tt;
	CString m_strFileNamePath;
	CString m_strFileNameExt;
	TCHAR m_szDelimiter[2];
	TCHAR m_ExamplesPath[_MAX_PATH];

// Operations
private:
	void SaveFile();
	void OpenFile();
	void OpenMDIDoc();
	void CreateNewFrame();
	void AddToRecentFileList(LPCTSTR lpszPathName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAIPITreeDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual BOOL OnNewDocument();
	virtual BOOL SaveModified();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAIPITreeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CAIPITreeDoc)
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileOpen();
	afx_msg void OnDisplayDirectoryTree();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIPITREEDOC_H__79BB2D6F_EB2B_455D_A15E_DBF8A95C4F76__INCLUDED_)
