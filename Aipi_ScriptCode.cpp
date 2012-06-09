// Aipi_ScriptCode.cpp: implementation of the CAipi_ScriptCode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_ScriptCode.h"

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

CAipi_ScriptCode::CAipi_ScriptCode()
{

}

CAipi_ScriptCode::~CAipi_ScriptCode()
{

}

CAipi_ScriptCode* CAipi_ScriptCode::addScriptCode(long iform, tstring name, long index1, long index2, long pos1, long pos2, int nparam, CString lang, CString def )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_ScriptCode *pObject = new CAipi_ScriptCode();
    try
	{
		pObject->setScriptName(name);
		pObject->setStartIndex(index1);
		pObject->setEndIndex(index2);
		pObject->setStartPos(pos1);
		pObject->setEndPos(pos2);
		pObject->setParameters(nparam);
		pObject->setScriptLanguage(lang);
		pObject->setScriptDefinition(def);
		
			
		pMainFrame->gmScriptCode.insert(CMainFrame::g_mScriptCode::value_type(iform, *pObject));
				
						
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


void CAipi_ScriptCode::eraseScriptCode(long id)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mScriptCode::iterator iter;
	
	iter = pMainFrame->gmScriptCode.find(id);
	if( iter != pMainFrame->gmScriptCode.end())
	{
		pMainFrame->gmScriptCode.erase(id);
				
	}

	
}


void CAipi_ScriptCode::clearScriptCode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmScriptCode.clear();

}

long CAipi_ScriptCode::findId_Into_ScriptCode(long id)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	//Check each script
	for( CMainFrame::g_mScriptCode::const_iterator iter = pMainFrame->gmScriptCode.begin(); iter!= pMainFrame->gmScriptCode.end(); ++iter)
	{
		CAipi_ScriptCode sc = (CAipi_ScriptCode)iter->second;
 		long	index1			= sc.getStartIndex();
		long	index2			= sc.getEndIndex();
		
		//Now search the identifier in the tokenizer range of the script code
		for( long i = index1; i<index2; ++i)
		{
			long iform = pMainFrame->gvTokenizer[i].getIntForm();
			if( iform == id )
			{
				return i;
			}
		}
					
	}

return NOT_FOUND;

}




tstring CAipi_ScriptCode::findScriptName( long id )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mScriptCode::iterator iter;
    iter = pMainFrame->gmScriptCode.find(id);
	if( iter != pMainFrame->gmScriptCode.end())
	{
  		CAipi_ScriptCode  sc = (CAipi_ScriptCode)iter->second;
 		return sc.getScriptName();
	}
	
	return _T("NOT_FOUND");
	
}


CString CAipi_ScriptCode::findScriptDefinition( long id )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mScriptCode::iterator iter;
    iter = pMainFrame->gmScriptCode.find(id);
	if( iter != pMainFrame->gmScriptCode.end())
	{
  		CAipi_ScriptCode  sc = (CAipi_ScriptCode)iter->second;
 		return sc.getScriptDefinition();
	}
	
	return _T("NOT_FOUND");
	
}

int CAipi_ScriptCode::findScriptNoParameters( long id )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mScriptCode::iterator iter;
    iter = pMainFrame->gmScriptCode.find(id);
	if( iter != pMainFrame->gmScriptCode.end())
	{
  		CAipi_ScriptCode  sc = (CAipi_ScriptCode)iter->second;
 		return sc.getParameters();
	}
	
	return NOT_FOUND;
	
}

CString CAipi_ScriptCode::findScriptLanguage( long id )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mScriptCode::iterator iter;
    iter = pMainFrame->gmScriptCode.find(id);
	if( iter != pMainFrame->gmScriptCode.end())
	{
  		CAipi_ScriptCode  sc = (CAipi_ScriptCode)iter->second;
 		return sc.getScriptLanguage();
	}
	
	return _T("NOT_FOUND");
	
}

long CAipi_ScriptCode::findScriptStartPos( long id )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mScriptCode::iterator iter;
    iter = pMainFrame->gmScriptCode.find(id);
	if( iter != pMainFrame->gmScriptCode.end())
	{
  		CAipi_ScriptCode  sc = (CAipi_ScriptCode)iter->second;
 		return sc.getStartPos();
	}
	
	return NOT_FOUND;
	
}

long CAipi_ScriptCode::findScriptEndPos( long id )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mScriptCode::iterator iter;
    iter = pMainFrame->gmScriptCode.find(id);
	if( iter != pMainFrame->gmScriptCode.end())
	{
  		CAipi_ScriptCode  sc = (CAipi_ScriptCode)iter->second;
 		return sc.getEndPos();
	}
	
	return NOT_FOUND;
	
}

long CAipi_ScriptCode::findScriptStartIndex( long id )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mScriptCode::iterator iter;
    iter = pMainFrame->gmScriptCode.find(id);
	if( iter != pMainFrame->gmScriptCode.end())
	{
  		CAipi_ScriptCode  sc = (CAipi_ScriptCode)iter->second;
 		return sc.getStartIndex();
	}
	
	return NOT_FOUND;
	
}

long CAipi_ScriptCode::findScriptEndIndex( long id )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mScriptCode::iterator iter;
    iter = pMainFrame->gmScriptCode.find(id);
	if( iter != pMainFrame->gmScriptCode.end())
	{
  		CAipi_ScriptCode  sc = (CAipi_ScriptCode)iter->second;
 		return sc.getEndIndex();
	}
	
	return NOT_FOUND;
	
}




int CAipi_ScriptCode::findScriptMembers( long id )
{
	
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mScriptCode::iterator iter;
    iter = pMainFrame->gmScriptCode.find(id);
	if( iter != pMainFrame->gmScriptCode.end())
	{
  		CAipi_ScriptCode  sc = (CAipi_ScriptCode)iter->second;
 		m_ScriptName = sc.getScriptName();
		m_StartIndex = sc.getStartIndex();
		m_EndIndex   = sc.getEndIndex();
		m_StartPos   = sc.getStartPos();
		m_EndPos     = sc.getEndPos();
		m_nParameters = sc.getParameters();
		m_ScriptLanguage = sc.getScriptLanguage();
		m_ScriptDefinition = sc.getScriptDefinition();

		return FOUND;
	}
	
	return NOT_FOUND;
	
}


void CAipi_ScriptCode::printScriptCode()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  SCRIPT IDENTIFIER  -  Script Definition  *******"));
	
	//Print map container
	for( CMainFrame::g_mScriptCode::const_iterator iter = pMainFrame->gmScriptCode.begin(); iter!= pMainFrame->gmScriptCode.end(); ++iter)
	{
		CString strID =_T("ID_");
		CString strIndex1 =_T("");
		CString strIndex2 =_T("");
		CString strPos1 =_T("");
		CString strPos2 =_T("");
		CString strParam = _T("");
		
		
					
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  ScriptId - Code Definition  *******"));

		long id		= iter->first;
		
		CAipi_ScriptCode sc = (CAipi_ScriptCode)iter->second;
 		
		tstring name			= sc.getScriptName();
		long	index1			= sc.getStartIndex();
		long	index2			= sc.getEndIndex();
		long	pos1			= sc.getStartPos();
		long	pos2			= sc.getEndPos();
		
		int     nparam			= sc.getParameters();
		CString	lang			= sc.getScriptLanguage();
		CString	def				= sc.getScriptDefinition();

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Identifier: "));
		strID.Format(_T("%d" ), id);
		pMainFrame->m_wndOutputTabView.AddMsg1(strID);
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Name: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(name.data());
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Index1: "));
		strIndex1 +=  _itot( index1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strIndex1);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Index2: "));
		strIndex2 +=  _itot( index2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strIndex2);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Pos1: "));
		strPos1 +=  _itot( pos1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPos1);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Pos2: "));
		strPos2 +=  _itot( pos2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPos2);


		pMainFrame->m_wndOutputTabView.AddMsg1(_T("No. Parameters: "));
		strParam +=  _itot( nparam, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strParam);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Script Language: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(lang);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Script Def: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(def);
	
			
	}

}

