// Aipi_STableClass.h: interface for the CAipi_STableClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_STABLECLASS_H__BA260274_2450_4119_94AF_FE063E45E0B1__INCLUDED_)
#define AFX_AIPI_STABLECLASS_H__BA260274_2450_4119_94AF_FE063E45E0B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_SymbolTable.h"

class CAipi_STableClass : public CAipi_SymbolTable  
{
public:
	CAipi_STableClass();
	virtual ~CAipi_STableClass();

	inline CAipi_STableClass(long attr_iform, tstring attr_name, int attr_type, long class_iform, tstring class_name )
	{
		
		CAipi_SymbolTable::setSymbolName(attr_name);
		CAipi_SymbolTable::setSymbolType(attr_type);
		m_ClassId   = class_iform;
		m_ClassName = class_name;
		
	}

	
	inline void CAipi_STableClass::setAttrId(long attr_iform)
	{
		CAipi_SymbolTable::setSymbolId(attr_iform);
	}

	inline void CAipi_STableClass::setAttrName(tstring attr_name)
	{
		CAipi_SymbolTable::setSymbolName(attr_name);
		
	}
	
	inline void CAipi_STableClass::setAttrType(int attr_type)
	{
		CAipi_SymbolTable::setSymbolType(attr_type);
	}
	
	inline void CAipi_STableClass::setClassId(long class_iform)
	{
		m_ClassId = class_iform;

	}

	inline void CAipi_STableClass::setClassName(tstring class_name)
	{
		m_ClassName = class_name;

	}
	

	
	
	inline long CAipi_STableClass::getAttrId()
	{
		return CAipi_SymbolTable::m_SymbolId;
		
	}


	inline tstring CAipi_STableClass::getAttrName()
	{
		return CAipi_SymbolTable::m_SymbolName;
		
	}


	inline int CAipi_STableClass::getAttrType()
	{
		return CAipi_SymbolTable::m_SymbolType;
		
	}

	inline long CAipi_STableClass::getClassId()
	{
		return m_ClassId;
	}

	inline tstring CAipi_STableClass::getClassName()
	{
		return m_ClassName;
	}

public:
CAipi_STableClass* CAipi_STableClass::addSymbol(long attr_iform, tstring attr_name, int attr_type, long class_iform, tstring class_name);
	void	eraseSTableClass(long attr_id);
	void	clearSTableClass();	
	void	printSTableClass();

	int     findSTableClassMembers( long attr_iform, long class_iform);
	int		findAttrType( long attr_iform, long class_iform);
	tstring	findAttrName( long attr_iform, long class_iform);
	

public:
	long			m_AttrId;
	tstring			m_AttrName;
	int				m_AttrType;
	long			m_ClassId;
	tstring			m_ClassName;

};

#endif // !defined(AFX_AIPI_STABLECLASS_H__BA260274_2450_4119_94AF_FE063E45E0B1__INCLUDED_)
