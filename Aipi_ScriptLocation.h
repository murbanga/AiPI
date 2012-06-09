// Aipi_ScriptLocation.h: interface for the CAipi_ScriptLocation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_SCRIPTLOCATION_H__DD85113F_1D70_4C61_8A2B_B7C7A3AB0AF7__INCLUDED_)
#define AFX_AIPI_SCRIPTLOCATION_H__DD85113F_1D70_4C61_8A2B_B7C7A3AB0AF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAipi_ScriptLocation  
{
public:
	CAipi_ScriptLocation();
	virtual ~CAipi_ScriptLocation();

	inline CAipi_ScriptLocation(long pm, long index1, long index2, long pos1, long pos2 )
	{
		m_PM				= pm;
		m_StartIndex		= index1;
		m_EndIndex			= index2;
		m_StartPos			= pos1;
		m_EndPos			= pos2;
		
	}

	inline void CAipi_ScriptLocation::setPM(long pm)
	{
		m_PM = pm;
	}

	
	inline void CAipi_ScriptLocation::setStartIndex(long index1)
	{
		m_StartIndex = index1;
	}
	
	inline void CAipi_ScriptLocation::setEndIndex(long index2)
	{
		m_EndIndex = index2;
	}

	inline void CAipi_ScriptLocation::setStartPos(long pos1)
	{
		m_StartPos = pos1;
	}
	
	inline void CAipi_ScriptLocation::setEndPos(long pos2)
	{
		m_EndPos = pos2;
	}

	
	inline long CAipi_ScriptLocation::getPM()
	{
		return m_PM;
	}
	
	inline long CAipi_ScriptLocation::getStartIndex()
	{
		return m_StartIndex;
	}


	inline long CAipi_ScriptLocation::getEndIndex()
	{
		return m_EndIndex;
	}

	inline long CAipi_ScriptLocation::getStartPos()
	{
		return m_StartPos;
	}


	inline long CAipi_ScriptLocation::getEndPos()
	{
		return m_EndPos;
	}


public:
CAipi_ScriptLocation* CAipi_ScriptLocation::addScriptLocation(long pm, long index1, long index2, long pos1, long pos2);
	void	eraseScriptLocation(long id);
	void	clearScriptLocation();	

	void	printScriptLocation();



public:
	long			m_PM;
	long			m_StartIndex;
	long			m_EndIndex;
	long			m_StartPos;
	long			m_EndPos;
	
};

#endif // !defined(AFX_AIPI_SCRIPTLOCATION_H__DD85113F_1D70_4C61_8A2B_B7C7A3AB0AF7__INCLUDED_)
