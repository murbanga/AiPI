// Aipi_STableNumeric.h: interface for the CAipi_STableNumeric class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_STABLENUMERIC_H__E8ED74E0_1342_4F82_B37C_EF7D941DDF48__INCLUDED_)
#define AFX_AIPI_STABLENUMERIC_H__E8ED74E0_1342_4F82_B37C_EF7D941DDF48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_SymbolTable.h"

class CAipi_STableNumeric : public CAipi_SymbolTable 
{
public:
	CAipi_STableNumeric();
	virtual ~CAipi_STableNumeric();

	inline CAipi_STableNumeric(long iform, tstring name, int type, double value)
	{
		
		CAipi_SymbolTable::setSymbolId(iform);
		CAipi_SymbolTable::setSymbolName(name);
		CAipi_SymbolTable::setSymbolType(type);
		m_STNumValue   = value;
		
	}

	
	inline void CAipi_STableNumeric::setSymbolId(long iform)
	{
		CAipi_SymbolTable::setSymbolId(iform);
	}

	inline void CAipi_STableNumeric::setSymbolName(tstring name)
	{
		CAipi_SymbolTable::setSymbolName(name);
		
	}
	
	inline void CAipi_STableNumeric::setSymbolType(int type)
	{
		CAipi_SymbolTable::setSymbolType(type);
	}
	
	inline void CAipi_STableNumeric::setSymbolValue(double value)
	{
		m_STNumValue = value;

	}
	

	
	
	inline long CAipi_STableNumeric::getSymbolId()
	{
		return CAipi_SymbolTable::m_SymbolId;
		
	}


	inline tstring CAipi_STableNumeric::getSymbolName()
	{
		return CAipi_SymbolTable::m_SymbolName;
		
	}


	inline int CAipi_STableNumeric::getSymbolType()
	{
		return CAipi_SymbolTable::m_SymbolType;
		
	}

	inline double CAipi_STableNumeric::getSymbolValue()
	{
		return m_STNumValue;
	}


public:
	double m_STNumValue; 



};

#endif // !defined(AFX_AIPI_STABLENUMERIC_H__E8ED74E0_1342_4F82_B37C_EF7D941DDF48__INCLUDED_)
