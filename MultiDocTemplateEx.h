// MultiDocTemplateEx.h: interface for the CMultiDocTemplateEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MULTIDOCTEMPLATEEX_H__878098E5_B02D_4951_A689_3B6F6217D125__INCLUDED_)
#define AFX_MULTIDOCTEMPLATEEX_H__878098E5_B02D_4951_A689_3B6F6217D125__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMultiDocTemplateEx : public CMultiDocTemplate  
{
public:
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszPathName, BOOL bMakeVisible = TRUE);
	CMultiDocTemplateEx(UINT nIDResource, CRuntimeClass* pDocClass, CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass);
	virtual ~CMultiDocTemplateEx();


	
};

#endif // !defined(AFX_MULTIDOCTEMPLATEEX_H__878098E5_B02D_4951_A689_3B6F6217D125__INCLUDED_)
