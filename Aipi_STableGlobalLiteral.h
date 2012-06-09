// Aipi_STableGlobalLiteral.h: interface for the CAipi_STableGlobalLiteral class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_STABLEGLOBALLITERAL_H__F81D62FA_6266_4672_88D3_AE834EBA4234__INCLUDED_)
#define AFX_AIPI_STABLEGLOBALLITERAL_H__F81D62FA_6266_4672_88D3_AE834EBA4234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_STableLiteral.h"

class CAipi_STableGlobalLiteral : public CAipi_STableLiteral 
{
public:
	CAipi_STableGlobalLiteral();
	virtual ~CAipi_STableGlobalLiteral();


	inline void CAipi_STableGlobalLiteral::setSymbolId(long iform)
	{
		CAipi_STableLiteral::setSymbolId(iform);
	}

	inline void CAipi_STableGlobalLiteral::setSymbolName(tstring name)
	{
		CAipi_STableLiteral::setSymbolName(name);
		
	}
	
	inline void CAipi_STableGlobalLiteral::setSymbolType(int type)
	{
		CAipi_STableLiteral::setSymbolType(type);
	}
	
	inline void CAipi_STableGlobalLiteral::setSymbolValue(tstring value)
	{
		CAipi_STableLiteral::setSymbolValue(value);

	}
	

	
	
	inline long CAipi_STableGlobalLiteral::getSymbolId()
	{
		return CAipi_STableLiteral::m_SymbolId;
		
	}


	inline tstring CAipi_STableGlobalLiteral::getSymbolName()
	{
		return CAipi_STableLiteral::m_SymbolName;
		
	}


	inline int CAipi_STableGlobalLiteral::getSymbolType()
	{
		return CAipi_STableLiteral::m_SymbolType;
		
	}

	inline tstring CAipi_STableGlobalLiteral::getSymbolValue()
	{
		return CAipi_STableLiteral::m_STLitValue;
	}



public:
CAipi_STableGlobalLiteral* CAipi_STableGlobalLiteral::addSymbol(long iform, tstring name, int type, tstring val);
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
	long			m_STGLitId;
	tstring			m_STGLitName;
	int				m_STGLitType;
	tstring         m_STGLitValue;


};

#endif // !defined(AFX_AIPI_STABLEGLOBALLITERAL_H__F81D62FA_6266_4672_88D3_AE834EBA4234__INCLUDED_)
