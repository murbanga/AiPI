// AIPIDoc.cpp : implementation of the CAIPIDoc class
//

#include "stdafx.h"
#include "AIPI.h"

#include "AIPIDoc.h"
#include "CntrItem.h"
#include "DocTemplateEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAIPIDoc

IMPLEMENT_DYNCREATE(CAIPIDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CAIPIDoc, CRichEditDoc)
	//{{AFX_MSG_MAP(CAIPIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAIPIDoc construction/destruction

CAIPIDoc::CAIPIDoc()
{
	// TODO: add one-time construction code here

}

CAIPIDoc::~CAIPIDoc()
{
}

BOOL CAIPIDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CAIPIDoc::CreateClientItem(REOBJECT* preo) const
{
	// cast away constness of this
	return new CAIPICntrItem(preo, (CAIPIDoc*) this);
}



/////////////////////////////////////////////////////////////////////////////
// CAIPIDoc serialization

void CAIPIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	// TODO: set CRichEditDoc::m_bRTF = FALSE if you are serializing as text
	CRichEditDoc::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CAIPIDoc diagnostics

#ifdef _DEBUG
void CAIPIDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CAIPIDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAIPIDoc commands

BOOL CAIPIDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CRichEditDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// Add to MRU file list
	AddToRecentFileList(lpszPathName);
	
	return TRUE;
}


BOOL CAIPIDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// Add to MRU file list
	AddToRecentFileList(lpszPathName);
	
	return CRichEditDoc::OnSaveDocument(lpszPathName);
}


void CAIPIDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
	// TODO: Add your specialized code here and/or call the base class
	CDocument::SetPathName(lpszPathName, FALSE);
	CDocTemplateEx* pDocTemplate = (CDocTemplateEx *)GetDocTemplate();
	pDocTemplate->AddToRecentFileList(lpszPathName);
	
	
	//CRichEditDoc::SetPathName(lpszPathName, bAddToMRU);
}


void CAIPIDoc::AddToRecentFileList(LPCTSTR lpszPathName)
{
	((CAIPIApp*)AfxGetApp())->AddToRecentFileList(lpszPathName);
}


