// WorkspaceTree1.cpp: implementation of the CWorkspaceTree1 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "WorkspaceTree1.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWorkspaceTree1::CWorkspaceTree1()
{

}

CWorkspaceTree1::~CWorkspaceTree1()
{

}


CWorkspaceTree1* CWorkspaceTree1::addElement(CString nname, HTREEITEM item, CString fpath, CString fname )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CWorkspaceTree1 *pObject = new CWorkspaceTree1();
    try
	{
		pObject->setItem(item);
		pObject->setFilePath(fpath);
		pObject->setFileName(fname);
				
		pMainFrame->gmWSPTree1.insert(CMainFrame::g_mWSPTree1::value_type(nname, *pObject));
				
				
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


int CWorkspaceTree1::eraseElement(CString nname )
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_mWSPTree1::iterator iter;
	
	iter = pMainFrame->gmWSPTree1.find(nname);
	if( iter != pMainFrame->gmWSPTree1.end())
	{
		pMainFrame->gmWSPTree1.erase(nname);
		return P_SUCCESS;		
	}

return P_UNSUCCESS;
	
}


void CWorkspaceTree1::clearWSPTree1()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmWSPTree1.clear();
	

}


HTREEITEM CWorkspaceTree1::findItem(CString nname)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWSPTree1::iterator iter;
    iter = pMainFrame->gmWSPTree1.find(nname);
	if( iter != pMainFrame->gmWSPTree1.end())
	{
  		CWorkspaceTree1 wsp = (CWorkspaceTree1)iter->second;
 		return wsp.getItem();
	}
	
 return NULL;

}


CString CWorkspaceTree1::findFilePath(CString nname)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWSPTree1::iterator iter;
    iter = pMainFrame->gmWSPTree1.find(nname);
	if( iter != pMainFrame->gmWSPTree1.end())
	{
  		CWorkspaceTree1 wsp = (CWorkspaceTree1)iter->second;
 		return wsp.getFilePath();
	}
	
 return _T("NOT_FOUND");

}

CString CWorkspaceTree1::findFileName(CString nname)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWSPTree1::iterator iter;
    iter = pMainFrame->gmWSPTree1.find(nname);
	if( iter != pMainFrame->gmWSPTree1.end())
	{
  		CWorkspaceTree1 wsp = (CWorkspaceTree1)iter->second;
 		return wsp.getFileName();
	}
	
 return _T("NOT_FOUND");

}



int CWorkspaceTree1::findNodeTree1Members(CString nname)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_mWSPTree1::iterator iter;
    iter = pMainFrame->gmWSPTree1.find(nname);
	if( iter != pMainFrame->gmWSPTree1.end())
	{
  		CWorkspaceTree1 wsp = (CWorkspaceTree1)iter->second;
 		
		m_NodeName = nname;
		m_HItem = wsp.getItem();
		m_FilePath = wsp.getFilePath();
		m_FileName = wsp.getFileName();
		

		return FOUND;
	}
	
	return NOT_FOUND;
}


void CWorkspaceTree1::printWSPTree1()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];
	

	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  WorkspaceTree 1 *******"));
	//Print map container
	for( CMainFrame::g_mWSPTree1::const_iterator iter = pMainFrame->gmWSPTree1.begin(); iter!= pMainFrame->gmWSPTree1.end(); ++iter)
	{
		CString strNode =_T("NODE_");
		CString strItem =_T("Item: ");
		CString strfPath = _T("File_Path: ");
		CString strfName = _T("File_Name: ");
		
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Node Name - HTREEITEM  *******"));
		strNode +=  iter->first;

	
		CWorkspaceTree1 wsp = (CWorkspaceTree1)iter->second;

		HTREEITEM item = wsp.getItem();
		int hItem = (int)item;
		strItem +=  _itot( hItem, buffer, 10 );
		strfPath += wsp.getFilePath();
		strfName += wsp.getFileName();

		pMainFrame->m_wndOutputTabView.AddMsg1(strNode);
		pMainFrame->m_wndOutputTabView.AddMsg1(strItem);
		pMainFrame->m_wndOutputTabView.AddMsg1(strfPath);
		pMainFrame->m_wndOutputTabView.AddMsg1(strfName);
		
		
			
	}

}

