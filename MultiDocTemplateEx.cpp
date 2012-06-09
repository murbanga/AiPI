// MultiDocTemplateEx.cpp: implementation of the CMultiDocTemplateEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MultiDocTemplateEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMultiDocTemplateEx::CMultiDocTemplateEx(UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass)
 : CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
{

}

CMultiDocTemplateEx::~CMultiDocTemplateEx()
{

}

CDocument* CMultiDocTemplateEx::OpenDocumentFile(LPCTSTR lpszPathName, BOOL bMakeVisible)
{
	
	if (m_docList.GetCount() == 1)
	{
		CDocument* pDocument = (CDocument*)m_docList.GetHead();
		BOOL e = pDocument->GetPathName().IsEmpty();
		BOOL m = pDocument->IsModified();

		if (lpszPathName != NULL && pDocument->GetPathName().IsEmpty() && pDocument->IsModified())
		{
			
			
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
	return CMultiDocTemplate::OpenDocumentFile(lpszPathName, bMakeVisible);
}



