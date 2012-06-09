// Aipi_RETE_Operations.cpp: implementation of the CAipi_RETE_Operations class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_RETE_Operations.h"

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

CAipi_RETE_Operations::CAipi_RETE_Operations()
{

}

CAipi_RETE_Operations::~CAipi_RETE_Operations()
{

}


CAipi_RETE_Operations* CAipi_RETE_Operations::addOperation(int pm, int c, tstring v1, tstring v2, int type1, int type2, int rel  )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_RETE_Operations *pObject = new CAipi_RETE_Operations();
    try
	{
		pObject->setCond(c);
		pObject->setLeftVar(v1);
		pObject->setRightVar(v2);
		pObject->setLeftType(type1);
		pObject->setRightType(type2);
		pObject->setRel(rel);
			
		pMainFrame->gmmPM_Operation.insert(CMainFrame::g_mmPM_Operation::value_type(pm, *pObject));
				
						
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




void CAipi_RETE_Operations::clearOperation()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmmPM_Operation.clear();

}

void CAipi_RETE_Operations::addAttr_Type(tstring attr, int type)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmAttr_Type.insert(CMainFrame::g_mAttr_Type::value_type(attr, type));	
}


void CAipi_RETE_Operations::clearAttrType()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmAttr_Type.clear();

}



int CAipi_RETE_Operations::findAttr_Type(tstring attr )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mAttr_Type::iterator iter;
	
	iter = pMainFrame->gmAttr_Type.find(attr);
	
	if( iter != pMainFrame->gmAttr_Type.end())
	{
		return iter->second;
				
	}

return NOT_FOUND;	
}


void CAipi_RETE_Operations::printOperation()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Production Memory - Operations  *******"));
	
	//Print map container
	for( CMainFrame::g_mmPM_Operation::const_iterator iter = pMainFrame->gmmPM_Operation.begin(); iter!= pMainFrame->gmmPM_Operation.end(); ++iter)
	{
		CString strPM =_T("P");
		CString strCond =_T("C");
		CString strType1 =_T("LEFT_TYPE_");
		CString strType2 =_T("RIGHT_TYPE_");
		CString strRel =_T("REL_");
		
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  PM - Operation  *******"));
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("PM: "));
		strPM +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPM);
		
		CAipi_RETE_Operations op = (CAipi_RETE_Operations)iter->second;
 		
		int c			= op.getCond();
		tstring v1		= op.getLeftVar();
		tstring v2		= op.getRightVar();
		int type1		= op.getLeftType();
		int type2		= op.getRightType();
		int rel			= op.getRel();
	
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Condition: "));
		strCond +=  _itot( c, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCond);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Left Variable: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(v1.data());

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Right Variable: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(v2.data());

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Left Type: "));
		strType1 +=  _itot( type1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strType1);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Right Type: "));
		strType2 +=  _itot( type2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strType2);
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Rel: "));
		strRel +=  _itot( rel, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strRel);	
		
			
	}

}


void CAipi_RETE_Operations::printAttr_Type()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Attribute - Type *******"));
	//Print map container
	for( CMainFrame::g_mAttr_Type::const_iterator iter = pMainFrame->gmAttr_Type.begin(); iter!= pMainFrame->gmAttr_Type.end(); ++iter)
	{
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Attr _ Type  *******"));
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("ATTRIBUTE:"));
		tstring attr = iter->first;
		pMainFrame->m_wndOutputTabView.AddMsg1(attr.data());

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("TYPE:"));
		int type = iter->second;
		switch( type )
		{
		case AIPI_INT:
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("Int"));
			break;
		case AIPI_LONG:
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("Long"));
			break;
		case AIPI_FLOAT:
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("Float"));
			break;
		case AIPI_DOUBLE:
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("Double"));
			break;
		case AIPI_STRING:
			pMainFrame->m_wndOutputTabView.AddMsg1(_T("String"));
			break;

		}
		
	}
	
}