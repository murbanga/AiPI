// Aipi_DT_AVF.h: interface for the CAipi_DT_AVF class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_DT_AVF_H__8926F452_8CCE_4A50_96F2_7BB9CEFF6A26__INCLUDED_)
#define AFX_AIPI_DT_AVF_H__8926F452_8CCE_4A50_96F2_7BB9CEFF6A26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAipi_DT_AVF  
{
public:
	CAipi_DT_AVF();
	virtual ~CAipi_DT_AVF();

	public:
	void		setAtributeName(tstring a);
	void		setAtributeValue(tstring av);
	void		setAtributeValueFreq(int freq);
	tstring		getAtributeName();
	tstring		getAtributeValue();
	int			getAtributeValueFreq();
	
public:	
	std::tstring	m_AtributeName;
	std::tstring	m_AtributeValue;
	int				m_Freq;

};

#endif // !defined(AFX_AIPI_DT_AVF_H__8926F452_8CCE_4A50_96F2_7BB9CEFF6A26__INCLUDED_)
