// Aipi_STableGlobalNumeric.h: interface for the CAipi_STableGlobalNumeric class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_STABLEGLOBALNUMERIC_H__0815AD19_470A_437F_A9A2_581F8B5E3092__INCLUDED_)
#define AFX_AIPI_STABLEGLOBALNUMERIC_H__0815AD19_470A_437F_A9A2_581F8B5E3092__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_STableNumeric.h"

class CAipi_STableGlobalNumeric: public CAipi_STableNumeric  
{
public:
	CAipi_STableGlobalNumeric();
	virtual ~CAipi_STableGlobalNumeric();

	inline void CAipi_STableGlobalNumeric::setSymbolId(long iform)
	{
		CAipi_STableNumeric::setSymbolId(iform);
	}

	inline void CAipi_STableGlobalNumeric::setSymbolName(tstring name)
	{
		CAipi_STableNumeric::setSymbolName(name);
		
	}
	
	inline void CAipi_STableGlobalNumeric::setSymbolType(int type)
	{
		CAipi_STableNumeric::setSymbolType(type);
	}
	
	inline void CAipi_STableGlobalNumeric::setSymbolValue(double value)
	{
		CAipi_STableNumeric::setSymbolValue(value);

	}
	

	
	
	inline long CAipi_STableGlobalNumeric::getSymbolId()
	{
		return CAipi_STableNumeric::m_SymbolId;
		
	}


	inline tstring CAipi_STableGlobalNumeric::getSymbolName()
	{
		return CAipi_STableNumeric::m_SymbolName;
		
	}


	inline int CAipi_STableGlobalNumeric::getSymbolType()
	{
		return CAipi_STableNumeric::m_SymbolType;
		
	}

	inline double CAipi_STableGlobalNumeric::getSymbolValue()
	{
		return CAipi_STableNumeric::m_STNumValue;
	}



public:
CAipi_STableGlobalNumeric* CAipi_STableGlobalNumeric::addSymbol(long iform, tstring name, int type, double val);
	tstring	findIdName(long id);
	double	findIdValue(long id);
	int		findIdType(long id);
	int     findSTableNumericMembers( long id);
	int		sizeSTableNumeric();
	void	eraseSTableNumeric(long id);
	void	editSTableNumericValue( long id, double val);
	void	editLastSTableNumericValue( double val);
	void	clearSTableNumeric();	
	void	printSTableNumeric();

public:
	long			m_STGNumId;
	tstring			m_STGNumName;
	int				m_STGNumType;
	double          m_STGNumValue;

};

#endif // !defined(AFX_AIPI_STABLEGLOBALNUMERIC_H__0815AD19_470A_437F_A9A2_581F8B5E3092__INCLUDED_)
