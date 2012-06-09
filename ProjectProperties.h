// ProjectProperties.h: interface for the CProjectProperties class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECTPROPERTIES_H__DD96B878_84E1_48FB_A898_22CD6F752C06__INCLUDED_)
#define AFX_PROJECTPROPERTIES_H__DD96B878_84E1_48FB_A898_22CD6F752C06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProjectProperties : public CObject   
{
public:
	CProjectProperties();
	CProjectProperties( const CProjectProperties &ob);
	virtual ~CProjectProperties();
	CProjectProperties &operator= ( const CProjectProperties &ob);



	inline CProjectProperties(const TCHAR *pszName, HTREEITEM item, const TCHAR *pszFile, const TCHAR *pszPath)
	{
		m_Name = pszName;
		m_hItem = item;
		m_File = pszFile;
		m_Path = pszPath;
	
	}
	
	

	inline void CProjectProperties::setName(const TCHAR  *pszName)
	{
		m_Name = pszName;
		m_LastModified = CTime::GetCurrentTime();

	}

	inline void CProjectProperties::setItem(HTREEITEM item)
	{
		m_hItem = item;
	}

	inline void CProjectProperties::setFile(const TCHAR *pszFile)
	{
		m_File = pszFile;
	}
	
	inline void CProjectProperties::setPath(const TCHAR *pszPath)
	{
		m_Path = pszPath;
	}

	

	

	inline const CString &CProjectProperties::getName() const
	{
		return m_Name;
	}
	

	inline HTREEITEM CProjectProperties::getItem()
	{
		return m_hItem;
	}
	
	inline const CString &CProjectProperties::getFile() const
	{
		return m_File;
	}

	inline const CString &CProjectProperties::getPath() const
	{
		return m_Path;
	}


public:

	CString		m_Name;
	HTREEITEM	m_hItem;
	CString		m_File;
	CString		m_Path;
	CTime		m_LastModified;
};

#endif // !defined(AFX_PROJECTPROPERTIES_H__DD96B878_84E1_48FB_A898_22CD6F752C06__INCLUDED_)
