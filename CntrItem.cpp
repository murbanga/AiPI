// CntrItem.cpp : implementation of the CAIPICntrItem class
//

#include "stdafx.h"
#include "AIPI.h"

#include "AIPIDoc.h"
#include "AIPIView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAIPICntrItem implementation

IMPLEMENT_SERIAL(CAIPICntrItem, CRichEditCntrItem, 0)

CAIPICntrItem::CAIPICntrItem(REOBJECT* preo, CAIPIDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CAIPICntrItem::~CAIPICntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CAIPICntrItem diagnostics

#ifdef _DEBUG
void CAIPICntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CAIPICntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
