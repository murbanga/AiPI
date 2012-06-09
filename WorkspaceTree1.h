// WorkspaceTree1.h: interface for the CWorkspaceTree1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WORKSPACETREE1_H__9DDDA202_BC9F_46D2_B68C_2543913AA5BF__INCLUDED_)
#define AFX_WORKSPACETREE1_H__9DDDA202_BC9F_46D2_B68C_2543913AA5BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWorkspaceTree1  
{
public:
	CWorkspaceTree1();
	virtual ~CWorkspaceTree1();

	inline CWorkspaceTree1( CString nname, HTREEITEM item, CString fpath, CString fname)
	{
		m_NodeName		= nname;
		m_HItem		    = item;
		m_FilePath		= fpath;
		m_FileName		= fname;	
	}

	
	inline void CWorkspaceTree1::setNodeName(CString nname)
	{
		m_NodeName = nname;
	}


	inline void CWorkspaceTree1::setItem(HTREEITEM item)
	{
		m_HItem = item;
	}

	inline void CWorkspaceTree1::setFilePath(CString fpath)
	{
		m_FilePath = fpath;
	}

	inline void CWorkspaceTree1::setFileName(CString fname)
	{
		m_FileName = fname;
	}
	

	inline CString CWorkspaceTree1::getNodeName()
	{
		return m_NodeName;
	}


	inline HTREEITEM CWorkspaceTree1::getItem()
	{
		return m_HItem;
	}

	inline CString CWorkspaceTree1::getFilePath()
	{
		return m_FilePath;
	}
	
	inline CString CWorkspaceTree1::getFileName()
	{
		return m_FileName;
	}

public:
	CWorkspaceTree1*	addElement(CString nname, HTREEITEM item, CString fpath, CString fname );
	HTREEITEM			findItem(CString node_name);
	CString				findFilePath(CString node_name);
	CString				findFileName(CString node_name);
	int					findNodeTree1Members(CString node_name);
	int					eraseElement(CString nname);
	void				clearWSPTree1();
	void				printWSPTree1();


public:
	CString		m_NodeName;
	HTREEITEM	m_HItem;
	CString		m_FilePath;
	CString		m_FileName;
	

};

#endif // !defined(AFX_WORKSPACETREE1_H__9DDDA202_BC9F_46D2_B68C_2543913AA5BF__INCLUDED_)
