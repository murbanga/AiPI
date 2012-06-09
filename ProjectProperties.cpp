// ProjectProperties.cpp: implementation of the CProjectProperties class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "ProjectProperties.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProjectProperties::CProjectProperties()
{
	m_LastModified = CTime::GetCurrentTime();
}

CProjectProperties::CProjectProperties( const CProjectProperties &ob)
{
	*this = ob;
}


CProjectProperties &CProjectProperties::operator = (const CProjectProperties &ob)
{
	m_Name = ob.m_Name;
	m_hItem = ob.m_hItem;
	m_File = ob.m_File;
	m_Path = ob.m_Path;
	m_LastModified = ob.m_LastModified;

	return *this;
}


CProjectProperties::~CProjectProperties()
{

}
