// WorkspaceLocation.cpp: implementation of the CWorkspaceLocation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "WorkspaceLocation.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWorkspaceLocation::CWorkspaceLocation()
{

}

CWorkspaceLocation::~CWorkspaceLocation()
{

}

CWorkspaceLocation* CWorkspaceLocation::addLocation(HTREEITEM item, long pos, int line, CString name, CString file, int categ )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CWorkspaceLocation *pObject = new CWorkspaceLocation();
    try
	{
		pObject->setItem( item);
		pObject->setPos(pos);
		pObject->setLine(line);
		pObject->setName(name);
		pObject->setFile(file);
		pObject->setCategory(categ);
		
		pMainFrame->gmWSPLocation.insert(CMainFrame::g_mWSPLocation::value_type(item, *pObject));
				
				
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




void CWorkspaceLocation::printLocation()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Workspace Node Tree Location  *******"));
	
	//Print map container
	for( CMainFrame::g_mWSPLocation::const_iterator iter = pMainFrame->gmWSPLocation.begin(); iter!= pMainFrame->gmWSPLocation.end(); ++iter)
	{
		
		CString strHItem =_T("ITEM_");
		CString strPos =_T("POS_");
		CString strLine =_T("LINE_");
		CString strCateg = _T("CATEG_");
							
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  WSPNode - WSPElements  *******"));

		int item		= (int)iter->first;
		
		CWorkspaceLocation loc = (CWorkspaceLocation)iter->second;
 		
		long pos				= loc.getPos();
		int line				= loc.getLine();
		CString name			= loc.getName();
		CString file			= loc.getFile();
		int categ				= loc.getCategory();

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Item: "));
		strHItem.Format(_T("%d" ), item);
		pMainFrame->m_wndOutputTabView.AddMsg1(strHItem);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Pos: "));
		strPos.Format(_T("%d" ), pos);
		pMainFrame->m_wndOutputTabView.AddMsg1(strPos);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Line: "));
		strLine.Format(_T("%d" ), line);
		pMainFrame->m_wndOutputTabView.AddMsg1(strLine);
		
						
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Name: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(name);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("File: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(file);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Categ: "));
		strCateg.Format(_T("%d" ), categ);
		pMainFrame->m_wndOutputTabView.AddMsg1(strCateg);
		
			
	}

}


long CWorkspaceLocation::findPosition( HTREEITEM hItem )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWSPLocation::iterator iter;
    iter = pMainFrame->gmWSPLocation.find(hItem);
	if( iter != pMainFrame->gmWSPLocation.end())
	{
  		CWorkspaceLocation wsp = (CWorkspaceLocation)iter->second;
 		return wsp.getPos(); 
	}

return NOT_FOUND;
			

}

int CWorkspaceLocation::findLine( HTREEITEM hItem )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWSPLocation::iterator iter;
    iter = pMainFrame->gmWSPLocation.find(hItem);
	if( iter != pMainFrame->gmWSPLocation.end())
	{
  		CWorkspaceLocation wsp = (CWorkspaceLocation)iter->second;
 		return wsp.getLine(); 
	}

return NOT_FOUND;
			

}



int CWorkspaceLocation::findCategory( HTREEITEM hItem )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWSPLocation::iterator iter;
    iter = pMainFrame->gmWSPLocation.find(hItem);
	if( iter != pMainFrame->gmWSPLocation.end())
	{
  		CWorkspaceLocation wsp = (CWorkspaceLocation)iter->second;
 		return wsp.getCategory(); 
	}

return NOT_FOUND;
			

}


CString CWorkspaceLocation::findFile( HTREEITEM hItem )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWSPLocation::iterator iter;
    iter = pMainFrame->gmWSPLocation.find(hItem);
	if( iter != pMainFrame->gmWSPLocation.end())
	{
  		CWorkspaceLocation wsp = (CWorkspaceLocation)iter->second;
 		return wsp.getFile(); 
	}

return _T("NOT_FOUND");
			

}

CString CWorkspaceLocation::findName( HTREEITEM hItem )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWSPLocation::iterator iter;
    iter = pMainFrame->gmWSPLocation.find(hItem);
	if( iter != pMainFrame->gmWSPLocation.end())
	{
  		CWorkspaceLocation wsp = (CWorkspaceLocation)iter->second;
 		return wsp.getName(); 
	}

return _T("NOT_FOUND");
			

}


int CWorkspaceLocation::findLocationMembers(HTREEITEM hItem)
{
    CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWSPLocation::iterator iter;
    iter = pMainFrame->gmWSPLocation.find(hItem);
	if( iter != pMainFrame->gmWSPLocation.end())
	{
		CWorkspaceLocation wsp = (CWorkspaceLocation)iter->second;
 	
		m_Position = wsp.getPos();
		m_Line	   = wsp.getLine();
		m_NodeName = wsp.getName();
		m_FilePath = wsp.getFile();
		m_Category = wsp.getCategory();;
		
		
		return FOUND;
	}
	
	return NOT_FOUND;
}



void CWorkspaceLocation::eraseLocation(HTREEITEM item )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	CMainFrame::g_mWSPLocation::iterator iter;
    iter = pMainFrame->gmWSPLocation.find(item);
	if( iter != pMainFrame->gmWSPLocation.end())
	{
  		pMainFrame->gmWSPLocation.erase(item);
		
	}
	
}

void CWorkspaceLocation::clearLocation()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmWSPLocation.clear();
}


