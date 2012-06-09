// AIPIDoc.h : interface of the CAIPIDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPIDOC_H__2B50522C_0D5E_4B22_9B8D_75FF41655100__INCLUDED_)
#define AFX_AIPIDOC_H__2B50522C_0D5E_4B22_9B8D_75FF41655100__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAIPIDoc : public CRichEditDoc
{
protected: // create from serialization only
	CAIPIDoc();
	DECLARE_DYNCREATE(CAIPIDoc)

// Attributes
public:
	enum { nLinesPerPage = 54 };
// Operations
public:
	void AddToRecentFileList(LPCTSTR lpszPathName);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAIPIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CAIPIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAIPIDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AIPIDOC_H__2B50522C_0D5E_4B22_9B8D_75FF41655100__INCLUDED_)
