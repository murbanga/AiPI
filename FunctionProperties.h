// FunctionProperties.h: interface for the CFunctionProperties class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCTIONPROPERTIES_H__963F23B0_6324_4298_A248_360F9ADAEC12__INCLUDED_)
#define AFX_FUNCTIONPROPERTIES_H__963F23B0_6324_4298_A248_360F9ADAEC12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProjectProperties.h"

class CFunctionProperties : public CProjectProperties  
{

DECLARE_SERIAL(CFunctionProperties) 

public:
	CFunctionProperties();
	CFunctionProperties( const CFunctionProperties &ob);
	CFunctionProperties &operator= (const CFunctionProperties &ob);
	virtual ~CFunctionProperties();
	virtual void Serialize( CArchive &ar); 
	
	inline CFunctionProperties(const TCHAR *pszName, HTREEITEM item, const TCHAR *pszFile, const TCHAR *pszPath, int lang, int rtype)
	{
		CProjectProperties::setName(pszName);
		CProjectProperties::setItem(item);
		CProjectProperties::setFile(pszFile);
		CProjectProperties::setPath(pszPath);

		m_Language = lang;
		m_ReturnType = rtype;
	}
	

	inline void CFunctionProperties::setName(const TCHAR *pszName)
	{
		CProjectProperties::setName(pszName);

	}

	inline void CFunctionProperties::setItem(HTREEITEM item)
	{
		CProjectProperties::setItem(item);
	}

	inline void CFunctionProperties::setFile(const TCHAR *pszFile)
	{
		CProjectProperties::setFile(pszFile);
	}
	
	inline void CFunctionProperties::setPath(const TCHAR *pszPath)
	{
		CProjectProperties::setPath(pszPath);
	}

	inline void CFunctionProperties::setLanguaje(int lang)
	{
		m_Language = lang;
	}

	inline void CFunctionProperties::setReturnType(int rtype)
	{
		m_ReturnType = rtype;
	}	

	
	
	inline const CString &CFunctionProperties::getName() const
	{
		return CProjectProperties::getName();
	}

	inline HTREEITEM CFunctionProperties::getItem()
	{
		return CProjectProperties::getItem();
	}
	
	inline const CString &CFunctionProperties::getFile() const
	{
		return CProjectProperties::getFile();
	}

	inline const CString &CFunctionProperties::getPath() const
	{
		return CProjectProperties::getPath();
	}


	inline int CFunctionProperties::getLanguage()
	{
		return m_Language;
	}

	inline int CFunctionProperties::getReturnType()
	{
		return m_ReturnType;
	}





public:

	CString		m_funName;
	HTREEITEM	m_funhItem;
	int			m_funiItem;
	CString		m_funFile;
	CString		m_funPath;
	int			m_Language;
	int			m_ReturnType;
	CTime		m_LastModified;
	
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CMapFunctionProperties: public CMapStringToOb
{
	
	DECLARE_SERIAL( CMapFunctionProperties)

public:
	CMapFunctionProperties()
	{ 
		m_PropertiesModified = FALSE;
	}

	//void AddFunction(const TCHAR *szName, HTREEITEM item, const TCHAR *szFile, const TCHAR *szPath, int lang, int rtype);
	CFunctionProperties *CMapFunctionProperties::AddFunction(const TCHAR *szName, HTREEITEM item, const TCHAR *szFile, const TCHAR *szPath, int lang, int rtype);
	CFunctionProperties *FindbyRef( const TCHAR *szRef );
	HTREEITEM	FindItembyRef( const TCHAR *szRef);
	CString		FindFilebyRef(const TCHAR *szRef);
	CString		FindPathbyRef(const TCHAR *szRef);
	int			FindLanguagebyRef(const TCHAR *szRef);
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


#endif // !defined(AFX_FUNCTIONPROPERTIES_H__963F23B0_6324_4298_A248_360F9ADAEC12__INCLUDED_)


