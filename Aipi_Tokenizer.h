// Aipi_Tokenizer.h: interface for the CAipi_Tokenizer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_TOKENIZER_H__FE42D69B_22B3_4936_A9B0_946C2F6734A6__INCLUDED_)
#define AFX_AIPI_TOKENIZER_H__FE42D69B_22B3_4936_A9B0_946C2F6734A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_Init.h"


class CAipi_Tokenizer  
{
public:
	CAipi_Tokenizer();
	virtual ~CAipi_Tokenizer();

	inline CAipi_Tokenizer( int index, long pos1, long pos2, int line, double iform, tstring token, int categ)
	{
		m_Index = index;
		m_Pos1 = pos1;
		m_Pos2 = pos2;
		m_Line = line;
		m_IntForm = iform;
		m_Token = token;
		m_Category = categ;
	}

	inline void CAipi_Tokenizer::setIndex(int index)
	{
		m_Index = index;
	}
	
	
	inline void CAipi_Tokenizer::setPos1(long pos1)
	{
		m_Pos1 = pos1;
	}


	inline void CAipi_Tokenizer::setPos2(long pos2)
	{
		m_Pos2 = pos2;
	}

	inline void CAipi_Tokenizer::setLine(int line)
	{
		m_Line = line;
	}

	
	inline void CAipi_Tokenizer::setToken(tstring token)
	{
		m_Token = token;
	}

	inline void CAipi_Tokenizer::setIntForm(double iform)
	{
		m_IntForm = iform;
	}

	inline void CAipi_Tokenizer::setCategory(int categ)
	{
		m_Category = categ;
	}
	
	
	inline long CAipi_Tokenizer::getIndex()
	{
		return m_Index;
	}
	
	inline long CAipi_Tokenizer::getPos1()
	{
		return m_Pos1;
	}

	inline long CAipi_Tokenizer::getPos2()
	{
		return m_Pos2;
	}

	inline int CAipi_Tokenizer::getLine()
	{
		return m_Line;
	}

	
	inline tstring CAipi_Tokenizer::getToken()
	{
		return m_Token;
	}

	inline double CAipi_Tokenizer::getIntForm()
	{
		return m_IntForm;
	}


	inline int CAipi_Tokenizer::getCategory()
	{
		return m_Category;
	}


public:
	CAipi_Tokenizer* CAipi_Tokenizer::v_addTokenIndex(int index, long pos1, long pos2, int line, double iform, tstring token, int categ ); 
	CAipi_Tokenizer* CAipi_Tokenizer::v_addToken(long pos1, long pos2, int line, double iform, tstring token, int categ ); 
	long			v_getIntFormByIndex( int index);
	long			v_getPos1ByIndex( int index);
	long			v_getPos2ByIndex( int index);
	int				v_getLineByIndex( int index);
	int				v_getCategoryByIndex(int index);
	tstring			v_getTokenByIndex(int index);

	tstring			v_lastToken();
	tstring			v_previousLastToken();	
	void			v_clearTokenizer();
	void			v_printTokenizer();
	
	//unsigned int	v_previousToken(unsigned int pos);
	long	v_lastPosition();
	long	v_stepback_1Pos();
	long	v_stepback_2Pos();
	long	v_stepback_3Pos();
	
	long	v_sizeTokenizer();
	
	double	v_lastIntFormToken();
	long	v_previousLastIntFormToken();		


public:
	int			m_Index;	
	long		m_Pos1;
	long		m_Pos2;
	int			m_Line;
	double		m_IntForm;
	int			m_Category;
	tstring		m_Token;

	
	
	

	
	


};

#endif // !defined(AFX_AIPI_TOKENIZER_H__FE42D69B_22B3_4936_A9B0_946C2F6734A6__INCLUDED_)
