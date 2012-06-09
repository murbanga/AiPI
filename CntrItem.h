// CntrItem.h : interface of the CAIPICntrItem class
//

#if !defined(AFX_CNTRITEM_H__6579EC9C_D478_42C2_A9C5_E6EB9E9BA626__INCLUDED_)
#define AFX_CNTRITEM_H__6579EC9C_D478_42C2_A9C5_E6EB9E9BA626__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAIPIDoc;
class CAIPIView;

class CAIPICntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CAIPICntrItem)

// Constructors
public:
	CAIPICntrItem(REOBJECT* preo = NULL, CAIPIDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CAIPIDoc* GetDocument()
		{ return (CAIPIDoc*)CRichEditCntrItem::GetDocument(); }
	CAIPIView* GetActiveView()
		{ return (CAIPIView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAIPICntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CAIPICntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__6579EC9C_D478_42C2_A9C5_E6EB9E9BA626__INCLUDED_)
