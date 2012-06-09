// Aipi_STableClass.cpp: implementation of the CAipi_STableClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_STableClass.h"

#include "../MainFrm.h"
#include "../ChildFrm.h"
#include "../OutputTabView.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAipi_STableClass::CAipi_STableClass()
{

}

CAipi_STableClass::~CAipi_STableClass()
{

}

CAipi_STableClass* CAipi_STableClass::addSymbol(long attr_iform, tstring attr_name, int attr_type, long class_iform, tstring class_name  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_STableClass *pObject = new CAipi_STableClass();
    try
	{
		pObject->setAttrName(attr_name);
		pObject->setAttrType(attr_type);
		pObject->setClassId(class_iform);
		pObject->setClassName(class_name);
		
		pMainFrame->gmmSTableClass.insert(CMainFrame::g_mmSTableClass::value_type(attr_iform, *pObject));
				
						
	}
	catch( CMemoryException* pErr)
	{
		AfxMessageBox(_T("Out of memory!!!"), MB_ICONSTOP | MB_OK);

		if(pObject)
		{
			delete pObject;
			pObject = NULL;
		}
		pErr->Delete();
	}
	
	return pObject;
}




void CAipi_STableClass::eraseSTableClass(long attr_id)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmSTableClass::iterator iter;
	
	iter = pMainFrame->gmmSTableClass.find(attr_id);
	if( iter != pMainFrame->gmmSTableClass.end())
	{
		pMainFrame->gmmSTableClass.erase(attr_id);
				
	}

	
}

void CAipi_STableClass::clearSTableClass()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmSTableClass.clear();

}



tstring CAipi_STableClass::findAttrName( long attr_iform, long class_iform )
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmSTableClass::iterator iter;
	pair <CMainFrame::g_mmSTableClass::iterator, CMainFrame::g_mmSTableClass::iterator>  pIter;
	
	pIter = pMainFrame->gmmSTableClass.equal_range(attr_iform);
	
	for(iter = pIter.first; iter != pIter.second; ++iter)
	{	
		CAipi_STableClass cl = (CAipi_STableClass)iter->second;
 		long classIForm  = cl.getClassId();
		if ( classIForm == class_iform ) 
		{
			return cl.getAttrName();
		}
	
	}
	
return _T("NOT_FOUND");	
	
}

int CAipi_STableClass::findAttrType( long attr_iform, long class_iform )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmSTableClass::iterator iter;
	pair <CMainFrame::g_mmSTableClass::iterator, CMainFrame::g_mmSTableClass::iterator>  pIter;

	/*
	CString str;
	str.Format(_T("Attr I %d"), attr_iform);
	AfxMessageBox(str);
	str.Format(_T("Class I %d"), class_iform);
	AfxMessageBox(str);
	*/
	pIter = pMainFrame->gmmSTableClass.equal_range(attr_iform);
	
	for(iter = pIter.first; iter != pIter.second; ++iter)
	{	
		CAipi_STableClass cl = (CAipi_STableClass)iter->second;
 		long classIForm  = cl.getClassId();
		
		if ( classIForm == class_iform ) 
		{
			//AfxMessageBox(_T("Encontrado"));
			return cl.getAttrType();
		}
	
	}
	
return NOT_FOUND;	
}








int CAipi_STableClass::findSTableClassMembers(long attr_iform, long class_iform)
{
    
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmSTableClass::iterator iter;
	pair <CMainFrame::g_mmSTableClass::iterator, CMainFrame::g_mmSTableClass::iterator>  pIter;
	
	pIter = pMainFrame->gmmSTableClass.equal_range(attr_iform);
	
	for(iter = pIter.first; iter != pIter.second; ++iter)
	{	
		CAipi_STableClass cl = (CAipi_STableClass)iter->second;
 		long classIForm  = cl.getClassId();
		if ( classIForm == class_iform ) 
		{
			m_AttrName = cl.getAttrName();
			m_AttrType = cl.getAttrType();
			m_ClassName = cl.getClassName();
			m_ClassId = cl.getClassId();
		
			return P_SUCCESS;	
		}
	
	}
	
return NOT_FOUND;
	
}






void CAipi_STableClass::printSTableClass()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ATTRIBUTR IDENTIFIER  -  Class Name  *******"));
	
	//Print map container
	for( CMainFrame::g_mmSTableClass::const_iterator iter = pMainFrame->gmmSTableClass.begin(); iter!= pMainFrame->gmmSTableClass.end(); ++iter)
	{
		CString strAttrId =_T("ATTRID_");
		CString strAttrType =_T("ATTRTYPE_");
		CString strClassId = _T("CLASSID");
					
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  AttrId - ClassId  *******"));

		long attr_id		= iter->first;
		
		CAipi_STableClass cl = (CAipi_STableClass)iter->second;
 		
		tstring attr_name		= cl.getAttrName();
		int		attr_type		= cl.getAttrType();
		long	class_id		= cl.getClassId();
		tstring class_name		= cl.getClassName();

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Attribute Identifier: "));
		strAttrId.Format(_T("%d" ), attr_id);
		pMainFrame->m_wndOutputTabView.AddMsg1(strAttrId);
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Attribute Name: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(attr_name.data());
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Atribute Type: "));
		strAttrType +=  _itot( attr_type, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strAttrType);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Class Identifier: "));
		strClassId.Format(_T("%d" ), class_id);
		pMainFrame->m_wndOutputTabView.AddMsg1(strClassId);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Class Name: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(class_name.data());

			
	}

}


