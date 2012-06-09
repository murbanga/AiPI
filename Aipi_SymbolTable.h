// Aipi_SymbolTable.h: interface for the CAipi_SymbolTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_SYMBOLTABLE_H__4957C845_BC4B_41DE_A7D1_C2B79166FD97__INCLUDED_)
#define AFX_AIPI_SYMBOLTABLE_H__4957C845_BC4B_41DE_A7D1_C2B79166FD97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAipi_SymbolTable  
{
public:
	CAipi_SymbolTable();
	virtual ~CAipi_SymbolTable();

	inline CAipi_SymbolTable(unsigned long symbol, tstring name, int type)
	{
		m_SymbolId		= symbol;
		m_SymbolName	= name;
		m_SymbolType	= type;

	}

	
	inline void CAipi_SymbolTable::setSymbolId(unsigned long symbol)
	{
		m_SymbolId = symbol;
	}

	inline void CAipi_SymbolTable::setSymbolName(tstring name)
	{
		m_SymbolName = name;
	}
	
	inline void CAipi_SymbolTable::setSymbolType(int type)
	{
		m_SymbolType = type;
	}

	
	inline unsigned long CAipi_SymbolTable::getSymbolId()
	{
		return m_SymbolId;
	}


	inline tstring CAipi_SymbolTable::getSymbolName()
	{
		return m_SymbolName;
	}


	inline int CAipi_SymbolTable::getSymbolType()
	{
		return m_SymbolType;
	}







public:
	unsigned long	m_SymbolId;
	tstring			m_SymbolName;
	int				m_SymbolType;
	

};

#endif // !defined(AFX_AIPI_SYMBOLTABLE_H__4957C845_BC4B_41DE_A7D1_C2B79166FD97__INCLUDED_)
