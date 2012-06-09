// Aipi_DT_AVF.cpp: implementation of the CAipi_DT_AVF class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../AIPI.h"
#include "Aipi_DT_AVF.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAipi_DT_AVF::CAipi_DT_AVF()
{

}

CAipi_DT_AVF::~CAipi_DT_AVF()
{

}

void CAipi_DT_AVF::setAtributeName(tstring a)
{
	m_AtributeName = a;

}


void CAipi_DT_AVF::setAtributeValue(tstring av)
{
	m_AtributeValue = av;
}

void CAipi_DT_AVF::setAtributeValueFreq(int freq)
{
	m_Freq = freq;
}

tstring CAipi_DT_AVF::getAtributeName()
{
	return m_AtributeName;
}


tstring CAipi_DT_AVF::getAtributeValue()
{
	return m_AtributeValue;
}

int CAipi_DT_AVF::getAtributeValueFreq()
{
	return m_Freq;
}


