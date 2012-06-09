// Aipi_Symbol.h: interface for the CAipi_Symbol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_SYMBOL_H__63A2CE63_9FED_4B8E_9AA0_D45749B23698__INCLUDED_)
#define AFX_AIPI_SYMBOL_H__63A2CE63_9FED_4B8E_9AA0_D45749B23698__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAipi_Symbol  
{
public:
	CAipi_Symbol();
	virtual ~CAipi_Symbol();

public:
	void			addId_IntForm(tstring id, double iform);
	void			clearId_IntForm();
	int				findKeyWord(tstring kw);
	long			findId_IntForm(tstring id);
	//unsigned int	lastId_Pos();
	tstring			findIdKeyWord(int kw);
	tstring			findOperator(int op);


	void			printId_IntForm();
	void			printOperator();

};

#endif // !defined(AFX_AIPI_SYMBOL_H__63A2CE63_9FED_4B8E_9AA0_D45749B23698__INCLUDED_)
