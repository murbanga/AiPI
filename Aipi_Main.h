// Aipi_Main.h: interface for the CAipi_Main class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_MAIN_H__7592B862_ED89_4589_A279_3DF72F6FF3EE__INCLUDED_)
#define AFX_AIPI_MAIN_H__7592B862_ED89_4589_A279_3DF72F6FF3EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Aipi_Init.h"
#include "Aipi_Tokenizer.h"
#include "Aipi_Lexer.h"
#include "Aipi_Parser.h"
#include "Aipi_ParserFile.h"
#include "Aipi_ParserGUI.h"
#include "Aipi_ExpParser.h"
#include "Aipi_ExpParserFile.h"
#include "Aipi_ExpParserGUI.h"
#include "Aipi_ExpParserRT.h"
#include "Aipi_CParser.h"
#include "Aipi_Symbol.h"
#include "Aipi_SymbolTable.h"
#include "Aipi_STableNumeric.h"
#include "Aipi_STableLiteral.h"
#include "Aipi_ScriptCode.h"
#include "Aipi_Error.h"
#include ".\ScintillaCtrl\ScintillaDocView.h"




class CAipi_Main  
{
public:
	CAipi_Main();
	virtual ~CAipi_Main();


public:
	void	stopTimer(CPerfTimer t, CString msg);
	void	buildGUI();
	void    buildFile();
	void    buildProject();
	void    createNetRETE(); 
	void	conflictSet(int crtype);

	void	init();
	void    execExpParserGUI();
	void    execExpParserFile();
	int		runInterp();
	int     parseExpertSystem(CString path);
	int     parseExpertSystem_continue();
	void    execute();
	void    execute_continue();

	void	test();

};

#endif // !defined(AFX_AIPI_MAIN_H__7592B862_ED89_4589_A279_3DF72F6FF3EE__INCLUDED_)
