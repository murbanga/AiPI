// Aipi_RETE_BME.h: interface for the CAipi_RETE_BME class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_RETE_BME_H__7990220E_0333_4D9F_B63B_819F9781B61C__INCLUDED_)
#define AFX_AIPI_RETE_BME_H__7990220E_0333_4D9F_B63B_819F9781B61C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
	This class represents the Beta Memory Elements.
	It saves specific information of each Beta Memory Element (WMEs)
	Beta Memory has WME´s as elements, this wme´s are linked generating tokens.


	*** Symbols ***
	BM			= Beta Memory
	WM			= Working Memory
	PM			= Production Memory
	TK			= Token
	nTokens		= Represents the number of tokens tha the BM has.
				(Sample: BM2: W1^W5, W2^W7, W6^W9) BM2 has 3 tokens.
	sizeTokens	= Represents the number of linked working memory elemens for each token.
				(Sample: BM5: W1^W5^W8, W2^W7^W11) BM5 has tokens of size 3	  
	
	

	*** Function Parameters ***
	nTk		= Represents the number of tokens tha the BM has.
			  (Sample: BM2: W1^W5, W2^W7, W6^W9) BM2 has 3 tokens.
	sizeTk	= Represents the number of linked working memory elemens for each token.
			  (Sample: BM5: W1^W5^W8, W2^W7^W11) BM5 has tokens of size 3	  
	
	am		= Alpha Memory
	bm		= Beta Memory
	wm		= Working Memory
	pm		= Production Memory
	cond	= Condition
	
*/

class CAipi_RETE_BME  
{
public:
	CAipi_RETE_BME();
	virtual ~CAipi_RETE_BME();

	inline CAipi_RETE_BME(int bm, int nTk, int sizeTk )
	{
		m_BM = bm;
		m_nTokens = nTk;
		m_sizeToken = sizeTk;
		
	}
	
	//Sets
	inline void CAipi_RETE_BME::setNTokens(int nTk)
	{
		m_nTokens = nTk;

	}
	
	inline void CAipi_RETE_BME::setSizeToken(int sizeTk)
	{
		m_sizeToken = sizeTk;

	}

	


	//Gets
	inline int CAipi_RETE_BME::getNTokens()
	{
		return m_nTokens;
	}

	
	inline int CAipi_RETE_BME::getSizeToken()
	{
		return m_sizeToken;
	}

	



public:
	CAipi_RETE_BME* CAipi_RETE_BME::addBME(int bm, int nTk, int sizeTk);
	int			findBME_nTokens(int bm);
	int			findBME_sizeToken(int bm);
	int			findBMEMembers(int bm);
	
	//void		createBME();
	int			linkWMEs(int bm, int tk);
	int			countBMTKs(int bm);

	void		eraseBM_WM(int bm);
	void		eraseBM_Info(int bm);
	void		eraseBME(int bm);
	void		clearBME();
	void		printBME();
	void		printBM_WM();


public:
	int	m_BM;
	int m_nTokens;
	int m_sizeToken;
	
};

#endif // !defined(AFX_AIPI_RETE_BME_H__7990220E_0333_4D9F_B63B_819F9781B61C__INCLUDED_)
