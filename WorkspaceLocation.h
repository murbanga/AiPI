// WorkspaceLocation.h: interface for the CWorkspaceLocation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKSPACELOCATION_H__39FE4C49_E593_4E35_B1D3_6AAF7B605ACF__INCLUDED_)
#define AFX_WORKSPACELOCATION_H__39FE4C49_E593_4E35_B1D3_6AAF7B605ACF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWorkspaceLocation  
{
public:
	CWorkspaceLocation();
	virtual ~CWorkspaceLocation();

	CWorkspaceLocation(HTREEITEM hItem, long pos, int line, CString name, CString file, int categ)
	{
		m_hTreeItem		= hItem;
		m_Position		= pos;
		m_Line			= line;
		m_NodeName		= name;
		m_FilePath		= file;
		m_Category		= categ;
	}

	inline void CWorkspaceLocation::setItem(HTREEITEM hItem)
	{
		m_hTreeItem = hItem;
	}


	inline void CWorkspaceLocation::setPos(int pos)
	{
		m_Position = pos;
	}

	inline void CWorkspaceLocation::setLine(int line)
	{
		m_Line = line;
	}

	inline void CWorkspaceLocation::setName(CString name)
	{
		m_NodeName = name;
	}

	inline void CWorkspaceLocation::setFile(CString file)
	{
		m_FilePath = file;
	}

	inline void CWorkspaceLocation::setCategory(int categ)
	{
		m_Category = categ;
	}




	inline HTREEITEM CWorkspaceLocation::getItem()
	{
		return m_hTreeItem;
	}


	inline long CWorkspaceLocation::getPos()
	{
		return m_Position;
	}

	inline long CWorkspaceLocation::getLine()
	{
		return m_Line;
	}

	inline CString CWorkspaceLocation::getName()
	{
		return m_NodeName;
	}

	inline CString CWorkspaceLocation::getFile()
	{
		return m_FilePath;
	}


	inline int CWorkspaceLocation::getCategory()
	{
		return m_Category;
	}


public:
	CWorkspaceLocation* CWorkspaceLocation::addLocation(HTREEITEM item, long pos, int line, CString name, CString file, int categ); 
	int			findLocationMembers(HTREEITEM hItem);
	int			findCategory(HTREEITEM hItem);
	int			findLine(HTREEITEM hITem);
	long		findPosition(HTREEITEM hItem);
	CString		findName( HTREEITEM hItem);
	CString	    findFile( HTREEITEM hItem);

	void		eraseLocation( HTREEITEM hItem);
	void		clearLocation();
	void		printLocation();




public:
	HTREEITEM m_hTreeItem;
	long	  m_Position;
	int		  m_Line;	
	int		  m_Category;
	CString	  m_NodeName;
	CString   m_FilePath;

};

#endif // !defined(AFX_WORKSPACELOCATION_H__39FE4C49_E593_4E35_B1D3_6AAF7B605ACF__INCLUDED_)
