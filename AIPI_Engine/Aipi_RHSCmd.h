// Aipi_RHSCmd.h: interface for the CAipi_RHSCmd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RHSCMD_H__5A80482A_E907_4C90_8C49_04D4FB168E24__INCLUDED_)
#define AFX_AIPI_RHSCMD_H__5A80482A_E907_4C90_8C49_04D4FB168E24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_RHS.h"


class CAipi_RHSCmd  
{
public:
	CAipi_RHSCmd();
	virtual ~CAipi_RHSCmd();

	inline CAipi_RHSCmd( int rhs, int cmd, int param_name, int param_type, tstring param_val)
	{
		m_Command	= cmd;
		m_ParamName	= param_name;
		m_ParamType = param_type;
		m_ParamVal	= param_val;
		

	}

	////////////////////////////////
	//Sets//
	/////////////////////////////////

	
	inline void CAipi_RHSCmd::setCmd(int cmd)
	{
		m_Command = cmd;

	}

	inline void CAipi_RHSCmd::setParamName(int param_name)
	{
		m_ParamName = param_name;
	}

	inline void CAipi_RHSCmd::setParamType(int param_type)
	{
		m_ParamType = param_type;

	}

	inline void CAipi_RHSCmd::setParamVal(tstring param_val)
	{
		m_ParamVal = param_val;
	}
	
	

	
	////////////////////////////////
	//Gets//
	/////////////////////////////////

	inline int CAipi_RHSCmd::getCmd()
	{
		return m_Command;
	}
	

	inline int CAipi_RHSCmd::getParamName()
	{
		return m_ParamName;
	}
	
	inline int CAipi_RHSCmd::getParamType()
	{
		return m_ParamType;
	}
	

	inline tstring CAipi_RHSCmd::getParamVal()
	{
		return m_ParamVal;
	}
	

	
	
//////////////////////////////////////////
////  Internal Form Functions ////
//////////////////////////////////////////	
public:
	CAipi_RHSCmd*	addRHSCmd(int rhs, int cmd, int param_name, int param_type, tstring param_val);
	void			eraseRHSCmd( int rhs);
	void			clearRHSCmd();	
	int				sizeRHSCmd();

	int				findRHSCmd_Cmd(int rhs);
	int				findRHSCmd_ParamName( int rhs);
	int				findRHSCmd_ParamType( int rhs);
	tstring			findRHSCmd_ParamVal(int rhs);
	int				findRHSCmdMembers( int rhs);

	void			printRHSCmd();


////////////////////////////////////////////
//// Member Vars ////
/////////////////////////////////////////////
public:
	int		m_Command;
	int		m_ParamName;
	int		m_ParamType;
	tstring	m_ParamVal;

};

#endif // !defined(AFX_AIPI_RHSCMD_H__5A80482A_E907_4C90_8C49_04D4FB168E24__INCLUDED_)
