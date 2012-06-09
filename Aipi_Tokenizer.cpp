// Aipi_Tokenizer.cpp: implementation of the CAipi_Tokenizer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_Tokenizer.h"

#include "../MainFrm.h"
#include "../ChildFrm.h"
#include "../OutputTabView.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAipi_Tokenizer::CAipi_Tokenizer()
{
	
}

CAipi_Tokenizer::~CAipi_Tokenizer()
{

}

CAipi_Tokenizer* CAipi_Tokenizer::v_addTokenIndex(int index, long pos1, long pos2, int line, double iform, tstring token, int categ)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_Tokenizer *pObject = new CAipi_Tokenizer();
    try
	{
		pObject->setIndex(index);
		pObject->setPos1(pos1);
		pObject->setPos2(pos2);
		pObject->setLine(line);
		pObject->setIntForm(iform);
		pObject->setToken(token);
		pObject->setCategory(categ);
		
		pMainFrame->gvTokenizer.push_back(*pObject);
		
				
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

CAipi_Tokenizer* CAipi_Tokenizer::v_addToken(long pos1, long pos2, int line, double iform, tstring token, int categ)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_Tokenizer *pObject = new CAipi_Tokenizer();
    try
	{
		++g_TkzCurrentIndex;
		pObject->setIndex(g_TkzCurrentIndex);
		pObject->setPos1(pos1);
		pObject->setPos2(pos2);
		pObject->setLine(line);
		pObject->setIntForm(iform);
		pObject->setToken(token);
		pObject->setCategory(categ);
		
		pMainFrame->gvTokenizer.push_back(*pObject);
		
				
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




void CAipi_Tokenizer::v_clearTokenizer()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gvTokenizer.clear();

}




long CAipi_Tokenizer::v_getIntFormByIndex(int index)
{
	long iForm = NOT_FOUND;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if( index < pMainFrame->gvTokenizer.size() )
	{
		iForm = pMainFrame->gvTokenizer[index].getIntForm();
	}
return iForm;		
}

long CAipi_Tokenizer::v_getPos1ByIndex(int index)
{
	long lPos = NOT_FOUND;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if( index < pMainFrame->gvTokenizer.size() )
	{
		lPos = pMainFrame->gvTokenizer[index].getPos1();
	}
return lPos;		
}


long CAipi_Tokenizer::v_getPos2ByIndex(int index)
{
	long lPos = NOT_FOUND;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if( index < pMainFrame->gvTokenizer.size() )
	{
		lPos = pMainFrame->gvTokenizer[index].getPos2();
	}
return lPos;		
}


int CAipi_Tokenizer::v_getLineByIndex(int index)
{
	long iLine = NOT_FOUND;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if( index < pMainFrame->gvTokenizer.size() )
	{
		iLine = pMainFrame->gvTokenizer[index].getLine();
	}
return iLine;		
}



tstring CAipi_Tokenizer::v_getTokenByIndex(int index)
{
	tstring sToken = _T("NOT_FOUND");
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if( index < pMainFrame->gvTokenizer.size() )
	{
		sToken = pMainFrame->gvTokenizer[index].getToken();
	}
return sToken;		
}


int CAipi_Tokenizer::v_getCategoryByIndex(int index)
{
	int iCateg = NOT_FOUND;
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	if( index < pMainFrame->gvTokenizer.size() )
	{
		iCateg = pMainFrame->gvTokenizer[index].getCategory();
	}
return iCateg;		
}






long CAipi_Tokenizer::v_lastPosition()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_vTokenizer::iterator iter;
	if( !pMainFrame->gvTokenizer.empty())
	{
		iter = pMainFrame->gvTokenizer.end(); 
		--iter;
		CAipi_Tokenizer tk = (CAipi_Tokenizer)(*iter);
		return tk.getPos1();
	}

	return EMPTY;
	
}



long CAipi_Tokenizer::v_stepback_1Pos()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_vTokenizer::iterator iter;
	if( pMainFrame->gvTokenizer.size() > 1)
	{
		iter = pMainFrame->gvTokenizer.end(); 
		--iter;
		--iter;
		CAipi_Tokenizer tk = (CAipi_Tokenizer)(*iter);
		return tk.getPos1();
	}

	return EMPTY;
}

long CAipi_Tokenizer::v_stepback_2Pos()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_vTokenizer::iterator iter;
	if( pMainFrame->gvTokenizer.size() > 2)
	{
		iter = pMainFrame->gvTokenizer.end(); 
		--iter;
		--iter;
		--iter;

		CAipi_Tokenizer tk = (CAipi_Tokenizer)(*iter);
		return tk.getPos1();
	}

	return EMPTY;
}

long CAipi_Tokenizer::v_stepback_3Pos()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_vTokenizer::iterator iter;
	if( pMainFrame->gvTokenizer.size() > 3)
	{
		iter = pMainFrame->gvTokenizer.end(); 
		--iter;
		--iter;
		--iter;
		--iter;

		CAipi_Tokenizer tk = (CAipi_Tokenizer)(*iter);
		return tk.getPos1();
	}

	return EMPTY;	
}

tstring CAipi_Tokenizer::v_lastToken()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_vTokenizer::iterator iter;
	if( !pMainFrame->gvTokenizer.empty())
	{
		iter = pMainFrame->gvTokenizer.end(); 
		--iter;
		CAipi_Tokenizer tk = (CAipi_Tokenizer)(*iter);
		
		return tk.getToken();
	}

	return _T("EMPTY");
}



tstring CAipi_Tokenizer::v_previousLastToken()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_vTokenizer::iterator iter;
	if( pMainFrame->gvTokenizer.size() > 1)
	{
		iter = pMainFrame->gvTokenizer.end(); 
		--iter;
		--iter;
		CAipi_Tokenizer tk = (CAipi_Tokenizer)(*iter);
		
		return tk.getToken();
	}

	return _T("EMPTY");
}



double CAipi_Tokenizer::v_lastIntFormToken()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_vTokenizer::iterator iter;
	if( !pMainFrame->gvTokenizer.empty())
	{
		iter = pMainFrame->gvTokenizer.end(); 
		
		--iter;
		CAipi_Tokenizer tk = (CAipi_Tokenizer)(*iter);
		
		return tk.getIntForm();
	}

	return EMPTY;
}


long CAipi_Tokenizer::v_previousLastIntFormToken()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CMainFrame::g_vTokenizer::iterator iter;
	if( !pMainFrame->gvTokenizer.empty())
	{
		iter = pMainFrame->gvTokenizer.end(); 
		
		--iter;
		--iter;
		CAipi_Tokenizer tk = (CAipi_Tokenizer)(*iter);
		
		return tk.getIntForm();
	}

	return EMPTY;
}


long CAipi_Tokenizer::v_sizeTokenizer()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	return pMainFrame->gvTokenizer.size();

}


/*
tstring CAipi_Tokenizer::v_findToken(unsigned int pos)
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	CMainFrame::g_vTokenizer::iterator iter;

	CAipi_Tokenizer tk;
	
	iter = find( pMainFrame->gvTokenizer.begin(), pMainFrame->gvTokenizer.end(), tk ); 
	
	
	if( iter != pMainFrame->gvTokenizer.end())
	{
		tk = (CAipi_Tokenizer)(*iter);
		return tk.getToken();
				
	}

return _T("NOT_FOUND");	
}
*/


void CAipi_Tokenizer::v_printTokenizer()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	TCHAR buffer[16];

	
	pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  TOKENIZER  *******"));
	
	//Print map container
	for( CMainFrame::g_vTokenizer::const_iterator iter = pMainFrame->gvTokenizer.begin(); iter!= pMainFrame->gvTokenizer.end(); ++iter)
	{
		CString strIndex =_T("");
		CString strPos1 =_T("");
		CString strPos2 =_T("");
		CString strLine = _T("");
		CString strIntForm =_T("");
		CString strCateg =_T("");
		
			
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("*******  Token Element  *******"));

		
		CAipi_Tokenizer tk = (CAipi_Tokenizer)(*iter);

 		int index = tk.getIndex();
		int pos1 = tk.getPos1();
		int pos2 = tk.getPos2();
		int line = tk.getLine();
		double iform = tk.getIntForm();
		int categ = tk.getCategory();
		tstring token = tk.getToken(); 

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Index: "));
		strIndex +=  _itot( index, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strIndex);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Pos1: "));
		strPos1 +=  _itot( pos1, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPos1);
	
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Pos2: "));
		strPos2 +=  _itot( pos2, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strPos2);

		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Line: "));
		strLine +=  _itot( line, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strLine);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("IntForm: "));
		strIntForm.Format(_T("%f" ), iform);
		pMainFrame->m_wndOutputTabView.AddMsg1(strIntForm);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Category: "));
		strCateg +=  _itot( categ, buffer, 10 );
		pMainFrame->m_wndOutputTabView.AddMsg1(strCateg);
		
		pMainFrame->m_wndOutputTabView.AddMsg1(_T("Token: "));
		pMainFrame->m_wndOutputTabView.AddMsg1(token.data());

			
	}

}

