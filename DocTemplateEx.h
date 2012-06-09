#if !defined(AFX_DOCTEMPLATEEX_H__ACB6DEAC_B710_11D2_A2C0_006067323266__INCLUDED_)
#define AFX_DOCTEMPLATEEX_H__ACB6DEAC_B710_11D2_A2C0_006067323266__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DocTemplateEx.h : header file
//

#define MRU_RANGE unsigned(ID_FILE_MRU_LAST-ID_FILE_MRU_FIRST)

/////////////////////////////////////////////////////////////////////////////
// CDocTemplateEx class

class CDocTemplateEx : public CMultiDocTemplate
{
	DECLARE_DYNAMIC(CDocTemplateEx)

// Constructors
public:
	CDocTemplateEx(UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass,
								 CRuntimeClass* pViewClass, WORD nMenuId = 0, UINT nMaxMRU = _AFX_MRU_COUNT);

// Attributes
public:
	WORD GetMenuID() const { return m_nMenuId; }
	
// Implementation
public:
	virtual ~CDocTemplateEx();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszPathName, BOOL bMakeVisible = TRUE);
#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

public:
	void AddToRecentFileList(LPCTSTR lpszPathName);

protected:
	void LoadStdProfileSettings(UINT nMaxMRU);
	void SaveStdProfileSettings();
	void OnUpdateRecentFileMenu(CCmdUI* pCmdUI);
	BOOL OnOpenRecentFile(UINT nID);

// Overridables
	// route and dispatch standard command message types
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

protected:
	CRecentFileList* m_pRecentFileList;
	WORD m_nMenuId;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCTEMPLATEEX_H__ACB6DEAC_B710_11D2_A2C0_006067323266__INCLUDED_)
