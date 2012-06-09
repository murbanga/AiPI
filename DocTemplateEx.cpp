// DocTemplateEx.cpp : implementation file
//

#include "stdafx.h"
#include "AIPI.h"
#include "DocTemplateEx.h"

#include <afxadv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDocTemplateEx, CMultiDocTemplate)

/////////////////////////////////////////////////////////////////////////////
// CDocTemplateEx

CDocTemplateEx::CDocTemplateEx(UINT nIDResource, CRuntimeClass* pDocClass,
			CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass, WORD nMenuId, UINT nMaxMRU)
			: CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
{
	m_pRecentFileList = NULL;
	m_nMenuId = nMenuId;
	if (m_nMenuId)
		LoadStdProfileSettings(nMaxMRU);
}

CDocTemplateEx::~CDocTemplateEx()
{
	CWinApp* pApp = AfxGetApp();
	if (pApp->m_pCmdInfo == NULL ||
		pApp->m_pCmdInfo->m_nShellCommand != CCommandLineInfo::AppUnregister)
	{
		if (!afxContextIsDLL)
			SaveStdProfileSettings();
	}

	// free recent file list
	if (m_pRecentFileList != NULL)
		delete m_pRecentFileList;
}

/////////////////////////////////////////////////////////////////////////////
// CDocTemplateEx diagnostics

#ifdef _DEBUG
void CDocTemplateEx::Dump(CDumpContext& dc) const
{
	CMultiDocTemplate::Dump(dc);

	if (m_pRecentFileList != NULL)
	{
		dc << "\nm_strRecentFiles[] = ";
		int nSize = m_pRecentFileList->GetSize();
		for (int i = 0; i < nSize; i++)
		{
			if ((*m_pRecentFileList)[i].GetLength() != 0)
				dc << "\n\tFile: " << (*m_pRecentFileList)[i];
		}
	}

	dc << "\n";
}

void CDocTemplateEx::AssertValid() const
{
	CMultiDocTemplate::AssertValid();
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDocTemplateEx implementation

void CDocTemplateEx::AddToRecentFileList(LPCTSTR lpszPathName)
{
	ASSERT_VALID(this);
	ASSERT(lpszPathName != NULL);
	ASSERT(AfxIsValidString(lpszPathName));

	if (m_pRecentFileList != NULL)
		m_pRecentFileList->Add(lpszPathName);
}

void CDocTemplateEx::LoadStdProfileSettings(UINT nMaxMRU)
{
	ASSERT_VALID(this);
	ASSERT(m_pRecentFileList == NULL);

	CString FileEntry = _T("File%d");
	CString FileSection;
	GetDocString(FileSection, CDocTemplate::docName);
	if (nMaxMRU != 0)
	{
		// create file MRU since nMaxMRU not zero
		m_pRecentFileList = new CRecentFileList(0, FileSection, FileEntry, nMaxMRU);
		m_pRecentFileList->ReadList();
	}
}

void CDocTemplateEx::SaveStdProfileSettings()
{
	ASSERT_VALID(this);

	if (m_pRecentFileList != NULL)
		m_pRecentFileList->WriteList();
}

void CDocTemplateEx::OnUpdateRecentFileMenu(CCmdUI* pCmdUI)
{
	ASSERT_VALID(this);
	if (pCmdUI->m_pSubMenu!=NULL) // updating a submenu?
	{
		// The following inactivates the submenu when the MRU list is empty
		UINT nEnable = MF_ENABLED;
		if ((m_pRecentFileList==NULL)	|| 
				(m_pRecentFileList->GetSize()==0)	||
				(*m_pRecentFileList)[0].IsEmpty())
		{
			nEnable = (MF_DISABLED | MF_GRAYED);
		}
		
		pCmdUI->m_pMenu->EnableMenuItem(pCmdUI->m_nIndex, MF_BYPOSITION | nEnable);
		return;
	}
	if (m_pRecentFileList == NULL) // no MRU files
		pCmdUI->Enable(FALSE);
	else
		m_pRecentFileList->UpdateMenu(pCmdUI);
}

BOOL CDocTemplateEx::OnOpenRecentFile(UINT nID)
{
	ASSERT_VALID(this);
	ASSERT(m_pRecentFileList != NULL);

	ASSERT(nID >= m_nMenuId);
	ASSERT(nID < m_nMenuId + (UINT)m_pRecentFileList->GetSize());
	int nIndex = nID - m_nMenuId;
	ASSERT((*m_pRecentFileList)[nIndex].GetLength() != 0);

	TRACE2("MRU: open file (%d) '%s'.\n", (nIndex) + 1,
			(LPCTSTR)(*m_pRecentFileList)[nIndex]);

	if (OpenDocumentFile((*m_pRecentFileList)[nIndex]) == NULL)
		m_pRecentFileList->Remove(nIndex);

	return TRUE;
}

// This hack is necessary because the menu ID is a member of the class.
// MFC message maps need the IDs to be global.
BOOL CDocTemplateEx::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// determine the message number and code (packed into nCode)
	UINT nMsg = 0;
	int nCod = nCode;

	if (nCod != CN_UPDATE_COMMAND_UI)
	{
		nMsg = HIWORD(nCod);
		nCod = LOWORD(nCod);
	}

	// for backward compatibility HIWORD(nCode)==0 is WM_COMMAND
	if (nMsg == 0)
		nMsg = WM_COMMAND;

	if ((nCod==CN_UPDATE_COMMAND_UI) && (nID>=m_nMenuId) && (nID<=m_nMenuId+MRU_RANGE))	
	{
		BOOL bResult = TRUE; // default is ok
		ASSERT(pExtra != NULL);
		CCmdUI* pCmdUI = (CCmdUI*)pExtra;
		ASSERT(!pCmdUI->m_bContinueRouting);    // idle - not set
		OnUpdateRecentFileMenu(pCmdUI);
		bResult = !pCmdUI->m_bContinueRouting;
		pCmdUI->m_bContinueRouting = FALSE;     // go back to idle
		return bResult;
	}

	if ((nMsg==WM_COMMAND) && (nCod==CN_COMMAND) && (nID>=m_nMenuId) && (nID<=m_nMenuId+MRU_RANGE))	
	{

#ifdef _DEBUG
			if (afxTraceFlags & traceCmdRouting)
			{
				TRACE2("SENDING command id 0x%04X to %hs target.\n", nID,
					GetRuntimeClass()->m_lpszClassName);
			}
#endif //_DEBUG

		return OnOpenRecentFile(nID);
	}

	return CMultiDocTemplate::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


CDocument* CDocTemplateEx::OpenDocumentFile(LPCTSTR lpszPathName, BOOL bMakeVisible)
{
	CAIPIApp* pApp = (CAIPIApp*)AfxGetApp();

	if (m_docList.GetCount() == 1)
	{
		CDocument* pDocument = (CDocument*)m_docList.GetHead();
		BOOL e = pDocument->GetPathName().IsEmpty();
		BOOL m = pDocument->IsModified();

		if (lpszPathName != NULL && pDocument->GetPathName().IsEmpty() && pDocument->IsModified())
		{
			
			pApp->AipiOpenDocumentFile(lpszPathName);
	
			CWaitCursor wait;
			if (!pDocument->OnOpenDocument(lpszPathName))
			{
				// user has be alerted to what failed in OnOpenDocument
				TRACE0("CDocument::OnOpenDocument returned FALSE.\n");
				return NULL;
			}
			
			pDocument->SetPathName(lpszPathName);
			POSITION pos = pDocument->GetFirstViewPosition();
			CView* pView = pDocument->GetNextView(pos);
			CFrameWnd* pFrame = pView->GetParentFrame();
			InitialUpdateFrame(pFrame, pDocument);
			return pDocument;
		}
	}

	pApp->AipiOpenDocumentFile(lpszPathName);
	

	return CMultiDocTemplate::OpenDocumentFile(lpszPathName, bMakeVisible);
}
