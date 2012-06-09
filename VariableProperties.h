// VariableProperties.h: interface for the CVariableProperties class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARIABLEPROPERTIES_H__FCB836DE_2986_4714_A406_1CEC2A4D9C33__INCLUDED_)
#define AFX_VARIABLEPROPERTIES_H__FCB836DE_2986_4714_A406_1CEC2A4D9C33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProjectProperties.h"

class CVariableProperties : public CProjectProperties  
{
DECLARE_SERIAL(CVariableProperties) 

public:
	CVariableProperties();
	CVariableProperties( const CVariableProperties &ob);
	CVariableProperties &operator= (const CVariableProperties &ob);
	virtual ~CVariableProperties();
	virtual void Serialize( CArchive &ar); 
	
	inline CVariableProperties(const TCHAR *pszName, HTREEITEM item, const TCHAR *pszFile, const TCHAR *pszPath, int type)
	{
		CProjectProperties::setName(pszName);
		CProjectProperties::setItem(item);
		CProjectProperties::setFile(pszFile);
		CProjectProperties::setPath(pszPath);

		m_Type = type;
	}
	

	inline void CVariableProperties::setName(const TCHAR *pszName)
	{
		CProjectProperties::setName(pszName);

	}

	inline void CVariableProperties::setItem(HTREEITEM item)
	{
		CProjectProperties::setItem(item);
	}

	inline void CVariableProperties::setFile(const TCHAR *pszFile)
	{
		CProjectProperties::setFile(pszFile);
	}
	
	inline void CVariableProperties::setPath(const TCHAR *pszPath)
	{
		CProjectProperties::setPath(pszPath);
	}

	inline void CVariableProperties::setType(int type)
	{
		m_Type = type;
	}	

	
	
	inline const CString &CVariableProperties::getName() const
	{
		return CProjectProperties::getName();
	}

	inline HTREEITEM CVariableProperties::getItem()
	{
		return CProjectProperties::getItem();
	}
	
	inline const CString &CVariableProperties::getFile() const
	{
		return CProjectProperties::getFile();
	}

	inline const CString &CVariableProperties::getPath() const
	{
		return CProjectProperties::getPath();
	}


	inline int CVariableProperties::getType()
	{
		return m_Type;
	}





public:

	CString		m_varName;
	HTREEITEM	m_varhItem;
	int			m_variItem;
	CString		m_varFile;
	CString		m_varPath;
	int			m_Type;
	CTime		m_LastModified;

};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CMapVariableProperties: public CMapStringToOb
{
	
	DECLARE_SERIAL( CMapVariableProperties)

public:
	CMapVariableProperties()
	{ 
		m_PropertiesModified = FALSE;
	}

	CVariableProperties *CMapVariableProperties::AddVariable(const TCHAR *szName, HTREEITEM item, const TCHAR *szFile, const TCHAR *szPath, int type);
	CVariableProperties *FindbyRef( const TCHAR *szRef );
	HTREEITEM	FindItembyRef( const TCHAR *szRef);
	CString		FindFilebyRef(const TCHAR *szRef);
	CString		FindPathbyRef(const TCHAR *szRef);
	int			FindTypebyRef(const TCHAR *szRef);
	
	
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

#endif // !defined(AFX_VARIABLEPROPERTIES_H__FCB836DE_2986_4714_A406_1CEC2A4D9C33__INCLUDED_)
