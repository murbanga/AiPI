// Aipi_Lexer.h: interface for the CAipi_Lexer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_LEXER_H__F7860514_B5D6_42F1_8DFE_06E3F75F15F5__INCLUDED_)
#define AFX_AIPI_LEXER_H__F7860514_B5D6_42F1_8DFE_06E3F75F15F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include ".\ScintillaCtrl\ScintillaDocView.h"
#include "Aipi_Init.h"
#include "Aipi_Tokenizer.h"
#include "Aipi_Error.h"
#include "Aipi_Symbol.h"


class CAipi_Lexer  
{
public:
	CAipi_Lexer();
	virtual ~CAipi_Lexer();

public:
	tstring			getTextRange(int pos1, int pos2);
	tstring			getTextFileRange(fpos_t pos1, fpos_t pos2);
	tstring			getText(int len);
	tstring			formatTkNameOpt(tstring name);
	unsigned long	getGUIDocumentLen();
	unsigned long	getFileDocumentLen(CString file);
	
////Lexer	
	int				getCharAt(unsigned long pos);
	int				getTokenGUI();
	int				getTokenFile(TCHAR symbol);
	int				getTokenGUIExp();
	int				getTokenFileExp(TCHAR symbol);

////Tokenizer
	int				addTokenizerGUIExp();
	int				addTokenizerFileExp(TCHAR symbol);
	int				addTokenizerGUI();
	int				addTokenizerFile(TCHAR symbol);
	void			createTokenizerGUI();
	void			createTokenizerFile(CString fname);
	
////Tokens	
	bool			isDigit(int c);
	bool			isAlphabetic(int c);
	bool			isAlphaNumeric(int c);
	bool			isUnicodeAlphabetic(int c);
	bool			isUnicodeSymbol( int c);
	bool			isOperator(int c);
	bool			isPunctuator(int c);
	bool			isTypeName(int c);

////Lexer Tests
	int				testGetTextFileRange(fpos_t pos1, fpos_t pos2);
	int				testGetTokenGUI();
	int				testGetTokenFile(TCHAR symbol);
	int				testGetTokenGUIExp();
	int				testGetTokenFileExp(TCHAR symbol);
	void			testScanGUI();
	void			testScanFile();
	


public:
    CString m_sToken;
	long	m_fileDocumentLen;
	long	m_guiDocumentLen;
	

};

#endif // !defined(AFX_AIPI_LEXER_H__F7860514_B5D6_42F1_8DFE_06E3F75F15F5__INCLUDED_)
