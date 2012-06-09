// QueryProperties.h: interface for the CQueryProperties class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUERYPROPERTIES_H__69FF6847_9112_4440_8C22_F9B2F6763BB0__INCLUDED_)
#define AFX_QUERYPROPERTIES_H__69FF6847_9112_4440_8C22_F9B2F6763BB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProjectProperties.h"

class CQueryProperties : public CProjectProperties  
{
DECLARE_SERIAL(CQueryProperties) 

public:
	CQueryProperties();
	CQueryProperties( const CQueryProperties &ob);
	CQueryProperties &operator= (const CQueryProperties &ob);
	virtual ~CQueryProperties();
	virtual void Serialize( CArchive &ar); 
	
	inline CQueryProperties(const TCHAR *pszName, HTREEITEM item, const TCHAR *pszFile, const TCHAR *pszPath, int rtype)
	{
		CProjectProperties::setName(pszName);
		CProjectProperties::setItem(item);
		CProjectProperties::setFile(pszFile);
		CProjectProperties::setPath(pszPath);

		m_ReturnType = rtype;
	}
	

	inline void CQueryProperties::setName(const TCHAR *pszName)
	{
		CProjectProperties::setName(pszName);

	}

	inline void CQueryProperties::setItem(HTREEITEM item)
	{
		CProjectProperties::setItem(item);
	}

	inline void CQueryProperties::setFile(const TCHAR *pszFile)
	{
		CProjectProperties::setFile(pszFile);
	}
	
	inline void CQueryProperties::setPath(const TCHAR *pszPath)
	{
		CProjectProperties::setPath(pszPath);
	}


	inline void CQueryProperties::setReturnType(int rtype)
	{
		m_ReturnType = rtype;
	}	

	
	
	inline const CString &CQueryProperties::getName() const
	{
		return CProjectProperties::getName();
	}

	inline HTREEITEM CQueryProperties::getItem()
	{
		return CProjectProperties::getItem();
	}
	
	inline const CString &CQueryProperties::getFile() const
	{
		return CProjectProperties::getFile();
	}

	inline const CString &CQueryProperties::getPath() const
	{
		return CProjectProperties::getPath();
	}


	inline int CQueryProperties::getReturnType()
	{
		return m_ReturnType;
	}





public:

	CString		m_sqlName;
	HTREEITEM	m_sqlhItem;
	int			m_sqliItem;
	CString		m_sqlFile;
	CString		m_sqlPath;
	int			m_ReturnType;
	CTime		m_LastModified;

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CMapQueryProperties: public CMapStringToOb
{
	
	DECLARE_SERIAL( CMapQueryProperties)

public:
	CMapQueryProperties()
	{ 
		m_PropertiesModified = FALSE;
	}

	CQueryProperties *CMapQueryProperties::AddQuery(const TCHAR *szName, HTREEITEM item, const TCHAR *szFile, const TCHAR *szPath, int rtype);
	CQueryProperties *FindbyRef( const TCHAR *szRef );
	HTREEITEM	FindItembyRef( const TCHAR *szRef);
	CString		FindFilebyRef(const TCHAR *szRef);
	CString		FindPathbyRef(const TCHAR *szRef);
	int			FindReturnTypebyRef(const TCHAR *szRef);
	
	
	void		PrintMap();

	void SetModifiedState( BOOL mod )
	{
		m_PropertiesModified = mod;
	}

	BOOL GetModifiedState()
	{
		return m_PropertiesModified;
	}

	void ClearMap();

public:
	BOOL m_PropertiesModified;

};

#endif // !defined(AFX_QUERYPROPERTIES_H__69FF6847_9112_4440_8C22_F9B2F6763BB0__INCLUDED_)
