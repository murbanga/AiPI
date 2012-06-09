#if !defined(AFX_TREETYPE_H__F46BDCE6_9C55_44E0_9642_A57148C672BC__INCLUDED_)
#define AFX_TREETYPE_H__F46BDCE6_9C55_44E0_9642_A57148C672BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeType.h : header file
//

struct NODE_TYPE
{
	WORD wNbItems;
    WORD wBufSize;
    HTREEITEM hti;
	UINT uState;
	TCHAR *buf;
}; 

enum TREE_TYPE_ERROR
{
    TTE_MEMORY,
    TTE_INVALID_FILE,
	TTE_INVALID_CSV_FILE,
    TTE_OPEN,
    TTE_READ,
    TTE_WRITE,
    TTE_CLOSE,
	TTE_EMPTY_FILE,
    TTE_INVALID_DIRECTORY,
	TTE_MAX_LEVEL,
};

class CTreeType  
{
public:
    CTreeType();
	virtual ~CTreeType();
	BOOL AllocateTree(size_t uCount);
    void DeAllocateTree();

	WORD m_wTotalNbItems;
    NODE_TYPE *m_pnt;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREETYPE_H__F46BDCE6_9C55_44E0_9642_A57148C672BC__INCLUDED_)
