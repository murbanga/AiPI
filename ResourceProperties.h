// ResourceProperties.h: interface for the CResourceProperties class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESOURCEPROPERTIES_H__A0B745F0_A058_4798_A9EE_10B8B9AFBA50__INCLUDED_)
#define AFX_RESOURCEPROPERTIES_H__A0B745F0_A058_4798_A9EE_10B8B9AFBA50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProjectProperties.h"

class CResourceProperties : public CProjectProperties  
{
public:
	CResourceProperties();
	virtual ~CResourceProperties();

	inline CResourceProperties(CString name, HTREEITEM item, CString file, CString path, CString type)
	{
		CProjectProperties::setName(name);
		CProjectProperties::setItem(item);
		CProjectProperties::setFile(file);
		CProjectProperties::setPath(path);

		m_Type = type;
	}
	
	inline void CResourceProperties::setName(CString name)
	{
		CProjectProperties::setName(name);

	}

	inline void CResourceProperties::setItem(HTREEITEM item)
	{
		CProjectProperties::setItem(item);
	}

	inline void CResourceProperties::setFile(CString file)
	{
		CProjectProperties::setFile(file);
	}
	
	inline void CResourceProperties::setPath(CString path)
	{
		CProjectProperties::setPath(path);
	}

	inline void CResourceProperties::setType(CString type)
	{
		m_Type = type;
	}	

	
	
	inline CString CResourceProperties::getName()
	{
		return CProjectProperties::getName();
	}

	inline HTREEITEM CResourceProperties::getItem()
	{
		return CProjectProperties::getItem();
	}
	
	inline CString CResourceProperties::getFile()
	{
		return CProjectProperties::getFile();
	}

	inline CString CResourceProperties::getPath()
	{
		return CProjectProperties::getPath();
	}


	inline CString CResourceProperties::getType()
	{
		return m_Type;
	}


public:

	CString		m_rscName;
	HTREEITEM	m_rcshItem;
	CString		m_rcsFile;
	CString		m_rcsPath;
	CString		m_Type;

};

#endif // !defined(AFX_RESOURCEPROPERTIES_H__A0B745F0_A058_4798_A9EE_10B8B9AFBA50__INCLUDED_)
