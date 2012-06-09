// TreeType.cpp : implementation file
//

#include "stdafx.h"
#include ".\..\AIPI.h"
#include "TreeType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeType

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTreeType::CTreeType()
{
	m_pnt = NULL;
}

CTreeType::~CTreeType()
{
    DeAllocateTree();
}

/************************************************************************************
    Ensure tt is always allocated and deallocated correctly:
*************************************************************************************
1) As it is mentionned in the comments of these functions:
   OnLoadEntireTree(), OnSaveEntireTree() and OnButtonUp() deallocate always the 
   CtreeType that they allocate.

2) By way of contrast, the CTreeType allocated in OnSaveSubtree() is NOT deallocated 
   on Ctrl-V (OnLoadSubtree()). The reason is that we want to allow the user to make 
   several "Paste" for the same tree that was copied by Ctrl-C. 

   However, before allocating, AllocateTree() checks if a tree was already allocated
   (by comparing m_pnt to NULL).

3) Since, the constructor of CTreeType initializes m_pnt to NULL, and the destructor
   calls DeAllocateTree() to deallocate an allocated tree (if there is any), all the
   cases are covered.
************************************************************************************/

BOOL CTreeType::AllocateTree(size_t uCount)
{
    WORD w;

    DeAllocateTree();
    m_wTotalNbItems = 0;
    m_pnt = (NODE_TYPE *)new NODE_TYPE[uCount + 1];
	if (m_pnt == NULL)
		return false;
    for (w = 0; w < uCount + 1; w++)
	{
        ZeroMemory(m_pnt + w, sizeof(NODE_TYPE));
		m_pnt[w].uState = TVIS_EXPANDED;
	}
	return true;
}

void CTreeType::DeAllocateTree()
{
    int k;

	if (m_pnt != NULL)
    {
        for (k = 0; k <= m_wTotalNbItems; k++)
        {
            if (m_pnt[k].buf != NULL)
                delete [] m_pnt[k].buf;
        }    
		delete m_pnt;
    	m_pnt = NULL;
    }
}
