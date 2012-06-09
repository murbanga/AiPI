// Aipi_STableLiteral.h: interface for the CAipi_STableLiteral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_STABLELITERAL_H__CB116C07_79E5_4523_B9D8_FE9883360726__INCLUDED_)
#define AFX_AIPI_STABLELITERAL_H__CB116C07_79E5_4523_B9D8_FE9883360726__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_SymbolTable.h"

class CAipi_STableLiteral : public CAipi_SymbolTable  
{
public:
	CAipi_STableLiteral();
	virtual ~CAipi_STableLiteral();

	inline CAipi_STableLiteral(long iform, tstring name, int type, tstring value)
	{
		
		CAipi_SymbolTable::setSymbolId(iform);
		CAipi_SymbolTable::setSymbolName(name);
		CAipi_SymbolTable::setSymbolType(type);
		m_STLitValue   = value;
		
	}

	
	inline void CAipi_STableLiteral::setSymbolId(long iform)
	{
		CAipi_SymbolTable::setSymbolId(iform);
	}

	inline void CAipi_STableLiteral::setSymbolName(tstring name)
	{
		CAipi_SymbolTable::setSymbolName(name);
		
	}
	
	inline void CAipi_STableLiteral::setSymbolType(int type)
	{
		CAipi_SymbolTable::setSymbolType(type);
	}
	
	inline void CAipi_STableLiteral::setSymbolValue(tstring value)
	{
		m_STLitValue = value;

	}
	

	
	
	inline long CAipi_STableLiteral::getSymbolId()
	{
		return CAipi_SymbolTable::m_SymbolId;
		
	}


	inline tstring CAipi_STableLiteral::getSymbolName()
	{
		return CAipi_SymbolTable::m_SymbolName;
		
	}


	inline int CAipi_STableLiteral::getSymbolType()
	{
		return CAipi_SymbolTable::m_SymbolType;
		
	}

	inline tstring CAipi_STableLiteral::getSymbolValue()
	{
		return m_STLitValue;
	}






public:
	tstring         m_STLitValue;


};

#endif // !defined(AFX_AIPI_STABLELITERAL_H__CB116C07_79E5_4523_B9D8_FE9883360726__INCLUDED_)
