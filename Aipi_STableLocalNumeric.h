// Aipi_STableLocalNumeric.h: interface for the CAipi_STableLocalNumeric class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_STABLELOCALNUMERIC_H__BC8F2805_38E6_4CAF_9170_E93CA96FFF2C__INCLUDED_)
#define AFX_AIPI_STABLELOCALNUMERIC_H__BC8F2805_38E6_4CAF_9170_E93CA96FFF2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_STableNumeric.h"

class CAipi_STableLocalNumeric : public CAipi_STableNumeric 
{
public:
	CAipi_STableLocalNumeric();
	virtual ~CAipi_STableLocalNumeric();

	inline void CAipi_STableLocalNumeric::setSymbolId(long iform)
	{
		CAipi_STableNumeric::setSymbolId(iform);
	}

	inline void CAipi_STableLocalNumeric::setSymbolName(tstring name)
	{
		CAipi_STableNumeric::setSymbolName(name);
		
	}
	
	inline void CAipi_STableLocalNumeric::setSymbolType(int type)
	{
		CAipi_STableNumeric::setSymbolType(type);
	}
	
	inline void CAipi_STableLocalNumeric::setSymbolValue(double value)
	{
		CAipi_STableNumeric::setSymbolValue(value);

	}
	

	
	
	inline long CAipi_STableLocalNumeric::getSymbolId()
	{
		return CAipi_STableNumeric::m_SymbolId;
		
	}


	inline tstring CAipi_STableLocalNumeric::getSymbolName()
	{
		return CAipi_STableNumeric::m_SymbolName;
		
	}


	inline int CAipi_STableLocalNumeric::getSymbolType()
	{
		return CAipi_STableNumeric::m_SymbolType;
		
	}

	inline double CAipi_STableLocalNumeric::getSymbolValue()
	{
		return CAipi_STableNumeric::m_STNumValue;
	}



public:
CAipi_STableLocalNumeric* CAipi_STableLocalNumeric::addSymbol(long iform, tstring name, int type, double val);
	tstring	findIdName(long id);
	double	findIdValue(long id);
	int		findIdType(long id);
	int     findSTableNumericMembers( long id);
	int     sizeSTableNumeric();
	void	eraseSTableNumeric(long id);
	void	editSTableNumericValue( long id, double val);
	void	editLastSTableNumericValue( double val);
	void	clearSTableNumeric();	
	void	printSTableNumeric();

public:
	long			m_STLNumId;
	tstring			m_STLNumName;
	int				m_STLNumType;
	double          m_STLNumValue;

};

#endif // !defined(AFX_AIPI_STABLELOCALNUMERIC_H__BC8F2805_38E6_4CAF_9170_E93CA96FFF2C__INCLUDED_)
