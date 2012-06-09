// Aipi_CmdLocation.h: interface for the CAipi_CmdLocation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_CMDLOCATION_H__35D53125_E779_4D9C_BB56_624AA80DE487__INCLUDED_)
#define AFX_AIPI_CMDLOCATION_H__35D53125_E779_4D9C_BB56_624AA80DE487__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_RHS.h"

class CAipi_CmdLocation  
{
public:
	CAipi_CmdLocation();
	virtual ~CAipi_CmdLocation();

	inline CAipi_CmdLocation(long pm, long index1, long index2, long pos1, long pos2, int cmd )
	{
		m_PM				= pm;
		m_StartIndex		= index1;
		m_EndIndex			= index2;
		m_StartPos			= pos1;
		m_EndPos			= pos2;
		m_Command			= cmd;
		
	}

	inline void CAipi_CmdLocation::setPM(long pm)
	{
		m_PM = pm;
	}

	
	inline void CAipi_CmdLocation::setStartIndex(long index1)
	{
		m_StartIndex = index1;
	}
	
	inline void CAipi_CmdLocation::setEndIndex(long index2)
	{
		m_EndIndex = index2;
	}

	inline void CAipi_CmdLocation::setStartPos(long pos1)
	{
		m_StartPos = pos1;
	}
	
	inline void CAipi_CmdLocation::setEndPos(long pos2)
	{
		m_EndPos = pos2;
	}

	inline void CAipi_CmdLocation::setCommand(int cmd)
	{
		m_Command = cmd;
	}

	
	inline long CAipi_CmdLocation::getPM()
	{
		return m_PM;
	}
	
	inline long CAipi_CmdLocation::getStartIndex()
	{
		return m_StartIndex;
	}


	inline long CAipi_CmdLocation::getEndIndex()
	{
		return m_EndIndex;
	}

	inline long CAipi_CmdLocation::getStartPos()
	{
		return m_StartPos;
	}


	inline long CAipi_CmdLocation::getEndPos()
	{
		return m_EndPos;
	}

	inline int CAipi_CmdLocation::getCommand()
	{
		return m_Command;
	}


public:
CAipi_CmdLocation* CAipi_CmdLocation::addCmdLocation(long pm, long index1, long index2, long pos1, long pos2, int cmd);
	void	eraseCmdLocation(long id);
	void	clearCmdLocation();	

	void	printCmdLocation();



public:
	long			m_PM;
	long			m_StartIndex;
	long			m_EndIndex;
	long			m_StartPos;
	long			m_EndPos;
	int				m_Command;

};

#endif // !defined(AFX_AIPI_CMDLOCATION_H__35D53125_E779_4D9C_BB56_624AA80DE487__INCLUDED_)
