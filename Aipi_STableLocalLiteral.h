// Aipi_STableLocalLiteral.h: interface for the CAipi_STableLocalLiteral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_STABLELOCALLITERAL_H__8A3E4759_F2FC_40EA_9B2C_A694FF6F61A0__INCLUDED_)
#define AFX_AIPI_STABLELOCALLITERAL_H__8A3E4759_F2FC_40EA_9B2C_A694FF6F61A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_STableLiteral.h"

class CAipi_STableLocalLiteral: public CAipi_STableLiteral  
{
public:
	CAipi_STableLocalLiteral();
	virtual ~CAipi_STableLocalLiteral();

	inline void CAipi_STableLocalLiteral::setSymbolId(long iform)
	{
		CAipi_STableLiteral::setSymbolId(iform);
	}

	inline void CAipi_STableLocalLiteral::setSymbolName(tstring name)
	{
		CAipi_STableLiteral::setSymbolName(name);
		
	}
	
	inline void CAipi_STableLocalLiteral::setSymbolType(int type)
	{
		CAipi_STableLiteral::setSymbolType(type);
	}
	
	inline void CAipi_STableLocalLiteral::setSymbolValue(tstring value)
	{
		CAipi_STableLiteral::setSymbolValue(value);

	}
	

	
	
	inline long CAipi_STableLocalLiteral::getSymbolId()
	{
		return CAipi_STableLiteral::m_SymbolId;
		
	}


	inline tstring CAipi_STableLocalLiteral::getSymbolName()
	{
		return CAipi_STableLiteral::m_SymbolName;
		
	}


	inline int CAipi_STableLocalLiteral::getSymbolType()
	{
		return CAipi_STableLiteral::m_SymbolType;
		
	}

	inline tstring CAipi_STableLocalLiteral::getSymbolValue()
	{
		return CAipi_STableLiteral::m_STLitValue;
	}



public:
CAipi_STableLocalLiteral* CAipi_STableLocalLiteral::addSymbol(long iform, tstring name, int type, tstring val);
	tstring	findIdName(long id);
	tstring	findIdValue(long id);
	int		findIdType(long id);
	int     findSTableLiteralMembers( long id);
	int		sizeSTableLiteral();
	void	eraseSTableLiteral(long id);
	void	editSTableLiteralValue( long id, tstring val);
	void	editLastSTableLiteralValue( tstring val);
	void	clearSTableLiteral();	
	void	printSTableLiteral();

public:
	long			m_STLLitId;
	tstring			m_STLLitName;
	int				m_STLLitType;
	tstring         m_STLLitValue;


};

#endif // !defined(AFX_AIPI_STABLELOCALLITERAL_H__8A3E4759_F2FC_40EA_9B2C_A694FF6F61A0__INCLUDED_)
