// Aipi_Symbol.cpp: implementation of the CAipi_Symbol class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_Symbol.h"

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

CAipi_Symbol::CAipi_Symbol()
{

}

CAipi_Symbol::~CAipi_Symbol()
{

}


void CAipi_Symbol::addId_IntForm(tstring id, double iform)
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmId_IntForm.insert(CMainFrame::g_mId_IntForm::value_type(id, iform));
}

void CAipi_Symbol::clearId_IntForm()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmId_IntForm.clear();

}


int CAipi_Symbol::findKeyWord(tstring kw)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mKeyWord::iterator iter;
	
	iter = pMainFrame->gmKeyWord.find(kw);
	
	if( iter != pMainFrame->gmKeyWord.end())
	{
		return iter->second;
				
	}
	else
	{

	}



return NOT_FOUND;	
}


tstring CAipi_Symbol::findIdKeyWord(int kw)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mIdKeyWord::iterator iter;
	
	iter = pMainFrame->gmIdKeyWord.find(kw);
	
	if( iter != pMainFrame->gmIdKeyWord.end())
	{
		return iter->second;
				
	}

return _T("NOT_FOUND");	
}


tstring CAipi_Symbol::findOperator(int op)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mOperator::iterator iter;
	
	iter = pMainFrame->gmOperator.find(op);
	
	if( iter != pMainFrame->gmOperator.end())
	{
		return iter->second;
				
	}

return _T("NOT_FOUND");	
}



long CAipi_Symbol::findId_IntForm(tstring id)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mId_IntForm::iterator iter;
	
	iter = pMainFrame->gmId_IntForm.find(id);
	
	if( iter != pMainFrame->gmId_IntForm.end())
	{
		return iter->second;
				
	}

return NOT_FOUND;	
}

/*
unsigned int CAipi_Symbol::lastId_Pos()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mmId_Pos::iterator iter;
	if( !pMainFrame->gmmId_Pos.empty())
	{
		iter = pMainFrame->gmmId_Pos.end(); 
		
		--iter;
		return iter->first;
			
	}

	return NOT_FOUND;
}
*/



void CAipi_Symbol::printId_IntForm()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  IDENTIFIER INTERNAL FORM *******"));
	//Print map container
	for( CMainFrame::g_mId_IntForm::const_iterator iter = pMainFrame->gmId_IntForm.begin(); iter!= pMainFrame->gmId_IntForm.end(); ++iter)
	{
		CString strIntForm =_T("IFORM_");
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Identifier Element  *******"));
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->first.data());
		strIntForm +=  _itot( iter->second, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strIntForm);
		
			
	}
}





void CAipi_Symbol::printOperator()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  OPERATOR  *******"));
	//Print map container
	for( CMainFrame::g_mOperator::const_iterator iter = pMainFrame->gmOperator.begin(); iter!= pMainFrame->gmOperator.end(); ++iter)
	{
		CString strOP =_T("OP_");
		
				
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Operator Element  *******"));
		strOP +=  _itot( iter->first, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strOP);
		pMainFrame->m_wndOutputTabView.AddMsg1(iter->second.data());
		
			
	}
}