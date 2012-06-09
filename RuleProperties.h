// RuleProperties.h: interface for the CRuleProperties class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULEPROPERTIES_H__316E8C52_B542_4CB5_BB8E_971D38142FA7__INCLUDED_)
#define AFX_RULEPROPERTIES_H__316E8C52_B542_4CB5_BB8E_971D38142FA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProjectProperties.h"

class CRuleProperties : public CProjectProperties  
{

DECLARE_SERIAL(CRuleProperties) 

public:
	CRuleProperties();
	CRuleProperties( const CRuleProperties &ob);
	CRuleProperties &operator= (const CRuleProperties &ob);
	virtual ~CRuleProperties();
	virtual void Serialize( CArchive &ar); 
	
	inline CRuleProperties(const TCHAR *pszName, HTREEITEM item, const TCHAR *pszFile, const TCHAR *pszPath, float w, float cf)
	{
		CProjectProperties::setName(pszName);
		CProjectProperties::setItem(item);
		CProjectProperties::setFile(pszFile);
		CProjectProperties::setPath(pszPath);

		m_Weight = w;
		m_CertainFactor = cf;
	}
	

	inline void CRuleProperties::setName(const TCHAR *pszName)
	{
		CProjectProperties::setName(pszName);

	}

	inline void CRuleProperties::setItem(HTREEITEM item)
	{
		CProjectProperties::setItem(item);
	}

	inline void CRuleProperties::setFile(const TCHAR *pszFile)
	{
		CProjectProperties::setFile(pszFile);
	}
	
	inline void CRuleProperties::setPath(const TCHAR *pszPath)
	{
		CProjectProperties::setPath(pszPath);
	}

	inline void CRuleProperties::setWeight(float w)
	{
		m_Weight = w;
	}

	inline void CRuleProperties::setCertainFactor(float cf)
	{
		m_CertainFactor = cf;
	}	

	
	
	inline const CString &CRuleProperties::getName() const
	{
		return CProjectProperties::getName();
	}

	inline HTREEITEM CRuleProperties::getItem()
	{
		return CProjectProperties::getItem();
	}
	
	inline const CString &CRuleProperties::getFile() const
	{
		return CProjectProperties::getFile();
	}

	inline const CString &CRuleProperties::getPath() const
	{
		return CProjectProperties::getPath();
	}


	inline int CRuleProperties::getWeight()
	{
		return m_Weight;
	}

	inline int CRuleProperties::getCertainFactor()
	{
		return m_CertainFactor;
	}





public:

	CString		m_rulName;
	HTREEITEM	m_rulhItem;
	int			m_ruliItem;
	CString		m_rulFile;
	CString		m_rulPath;
	float		m_Weight;
	float		m_CertainFactor;
	CTime		m_LastModified;

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CMapRuleProperties: public CMapStringToOb
{
	
	DECLARE_SERIAL( CMapRuleProperties)

public:
	CMapRuleProperties()
	{ 
		m_PropertiesModified = FALSE;
	}

	CRuleProperties *CMapRuleProperties::AddRule(const TCHAR *szName, HTREEITEM item, const TCHAR *szFile, const TCHAR *szPath, float w, float cf);
	CRuleProperties *FindbyRef( const TCHAR *szRef );
	HTREEITEM	FindItembyRef( const TCHAR *szRef);
	CString		FindFilebyRef(const TCHAR *szRef);
	CString		FindPathbyRef(const TCHAR *szRef);
	float			FindWeightbyRef(const TCHAR *szRef);
	float			FindCertainFactorbyRef(const TCHAR *szRef);
	
	
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


#endif // !defined(AFX_RULEPROPERTIES_H__316E8C52_B542_4CB5_BB8E_971D38142FA7__INCLUDED_)
