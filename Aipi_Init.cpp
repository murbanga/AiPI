// Aipi_Init.cpp: implementation of the CAipi_Init class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AIPI.h"
#include "Aipi_Init.h"

#include "../MainFrm.h"
#include "../ChildFrm.h"
#include "../OutputTabView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CAipi_Init::CAipi_Init()
{

}

CAipi_Init::~CAipi_Init()
{

}



void CAipi_Init::Initialize()
{
	fillAIPIKeyWords();
	fillID_AIPIKeyWords();
	
	fillCtrlKeyWords();
	fillID_CtrlKeyWords();

	fillCKeyWords();
	fillID_CKeyWords();

	fillJScriptKeyWords();
	fillID_JScriptKeyWords();

	fillVBScriptKeyWords();
	fillID_VBScriptKeyWords();
	
	fillErrorMsg();
	
	
	//fillOperator();
	//fillDBKeyWords();
	//fillID_DBKeyWords();

	
	g_LexError = 0;
	g_SintaxError = 0;
	g_SemantError = 0;
	g_StopError = 0;
	g_WarningError = 0;
	g_QuestionError = 0;
	g_InfoError = 0;
	g_currentFile = _T(" - ");
	g_bExecuteFlag  = false;


	g_CRStrategy = AIPI_CR_ORDER;
	g_currentDigit_Type = UNDEFINE;
	g_bNotificationModified = false;
	g_ImageListFlag = false;//Creation of CImageList for ClistOptionCtrl 
	g_includeDirective = true; //#include file





}


void CAipi_Init::fillAIPIKeyWords()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	
	//AIPI language keywords must be entered uppercase
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("ADDRULE"), AIPI_ADDRULE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("ADDRESS_INDEX"), AIPI_ADDRESS_INDEX ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("AND"),AIPI_AND ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("ASSERT"), AIPI_ASSERT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("BIND"), AIPI_BIND ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("CF"), AIPI_CF ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("CHAR"), AIPI_CHAR ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("CLASS"), AIPI_CLASS ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("CLOSE_FILE"), AIPI_CLOSE_FILE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("DB_CLOSE"), AIPI_DB_CLOSE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("DB_DNS"), AIPI_DB_DNS ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("DB_NAME"), AIPI_DB_NAME ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("DB_OPEN"), AIPI_DB_OPEN ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("DB_PROVIDER"), AIPI_DB_PROVIDER ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("DB_PASSWORD"), AIPI_DB_PASSWORD ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("DB_USER"), AIPI_DB_USER ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("DOUBLE"), AIPI_DOUBLE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("END"), AIPI_END ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("EXEC"), AIPI_EXEC ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("EXIST"),  AIPI_EXIST ));
	/*
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("txt"), AIPI_EXT1 ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("knw"), AIPI_EXT2 ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("js"), AIPI_EXT3 ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("vbs"), AIPI_EXT4 ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("sql"), AIPI_EXT5 ));
	*/
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("FACT_ADDRESS"), AIPI_FACT_ADDRESS ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("FLOAT"), AIPI_FLOAT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("FORALL"), AIPI_FORALL ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("FUNCTION"), AIPI_FUNCTION ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("FUZZY"), AIPI_FUZZY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("FUZZY_UNCERT"), AIPI_FUZZY_UNCERT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("GOTO_RULE"), AIPI_GOTO_RULE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("HALT"), AIPI_HALT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("IF"), AIPI_IF ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("INCLUDE"), AIPI_INCLUDE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("INIT"), AIPI_INIT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("INPUT"), AIPI_INPUT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("INT"), AIPI_INT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("LANGUAGE"), AIPI_LANGUAGE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("LONG"), AIPI_LONG ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("MODIFY"), AIPI_MODIFY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("NOT"), AIPI_NOT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("OPEN_FILE"), AIPI_OPEN_FILE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("OR"), AIPI_OR ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("ORDER"), AIPI_ORDER ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("OUTPUT"), AIPI_OUTPUT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("PRINTOUT"), AIPI_PRINTOUT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("PRIORITY"), AIPI_PRIORITY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("PAUSE"), AIPI_PAUSE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("QUERY"), AIPI_QUERY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("RECENCY"), AIPI_RECENCY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("RETRACT"), AIPI_RETRACT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("RULE"), AIPI_RULE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("SAVE_FILE"), AIPI_SAVE_FILE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("SCRIPT"), AIPI_SCRIPT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("SHORT"), AIPI_SHORT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("SHOW"), AIPI_SHOW ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("SQL"), AIPI_SQL ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("SQLQUERY"), AIPI_SQLQUERY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("STRING"), AIPI_STRING ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("STRATEGY"), AIPI_STRATEGY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("THEN"), AIPI_THEN ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("UNCERT"), AIPI_UNCERT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("VARIABLE"), AIPI_VARIABLE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("VOID"), AIPI_VOID ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("WEIGHT"), AIPI_WEIGHT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("WHEN"), AIPI_WHEN ));
	
	
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("true"), AIPI_TRUE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("false"), AIPI_FALSE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("TRUE"), AIPI_TRUE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("FALSE"), AIPI_FALSE ));
	
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("CR_PRIORITY"), AIPI_CR_PRIORITY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("CR_RECENCY"), AIPI_CR_RECENCY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("CR_SPECIFICITY"), AIPI_CR_SPECIFICITY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("CR_ORDER"), AIPI_CR_ORDER ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("CR_LEX"), AIPI_CR_LEX ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("CR_MEA"), AIPI_CR_MEA ));
	
				
}


void CAipi_Init::fillID_AIPIKeyWords()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	
	//AIPI language keywords must be entered uppercase

	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_ADDRULE, _T("ADDRULE") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_ADDRESS_INDEX, _T("ADDRESS_INDEX") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_AND, _T("AND") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_ASSERT, _T("ASSERT") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_BIND, _T("BIND") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CF, _T("CF") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CHAR, _T("CHAR") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CLASS, _T("CLASS") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CLOSE_FILE, _T("CLOSE_FILE") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_DB_CLOSE, _T("DB_CLOSE")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_DB_DNS, _T("DB_DNS")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_DB_NAME, _T("DB_NAME") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_DB_OPEN, _T("DB_OPEN")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_DB_PROVIDER, _T("DB_PROVIDER") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_DB_PASSWORD, _T("DB_PASSWORD")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_DB_USER, _T("DB_USER") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_DOUBLE, _T("DOUBLE") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_END, _T("END") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_EXEC, _T("EXEC") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_EXIST, _T("EXIST") ));
	/*
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_EXT1, _T("txt") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_EXT2, _T("knw") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_EXT3, _T("js") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_EXT4, _T("vbs") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_EXT5, _T("sql") ));
	*/
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_FACT_ADDRESS, _T("FACT_ADDRESS") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_FLOAT, _T("FLOAT") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_FORALL, _T("FORALL") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_FUNCTION, _T("FUNCTION") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_FUZZY, _T("FUZZY") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_FUZZY_UNCERT, _T("FUZZY_UNCERT") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_GOTO_RULE, _T("GOTO_RULE") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_HALT, _T("HALT") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_INCLUDE, _T("INCLUDE") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_IF, _T("IF") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_INIT, _T("INIT")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_INPUT, _T("INPUT")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_INT, _T("INT")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_LANGUAGE, _T("LANGUAGE") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_LONG, _T("LONG") ));	
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_MODIFY, _T("MODIFY") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_NOT, _T("NOT") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_OPEN_FILE, _T("OPEN_FILE")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_OR, _T("OR") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_ORDER, _T("ORDER") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_OUTPUT, _T("OUTPUT") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_PRINTOUT, _T("PRINTOUT") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_PRIORITY, _T("AIPI_PRIORITY") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_PAUSE, _T("AIPI_PAUSE") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_QUERY, _T("AIPI_QUERY") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_RECENCY, _T("RECENCY") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_RETRACT, _T("RETRACT") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_RULE, _T("RULE") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_SAVE_FILE, _T("SAVE_FILE") ));	
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_SCRIPT, _T("SCRIPT") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_SHORT, _T("SHORT") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_SHOW, _T("SHOW") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_SQL, _T("SQL") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_SQLQUERY, _T("SQLQUERY") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_STRING, _T("STRING") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_STRATEGY, _T("STRATEGY") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_THEN, _T("THEN") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_UNCERT, _T("UNCERT") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_VARIABLE, _T("VARIABLE") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_VOID, _T("VOID") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_WEIGHT, _T("WEIGHT") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_WHEN, _T("WHEN") ));


	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_TRUE, _T("true") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_FALSE, _T("false") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_TRUE, _T("TRUE") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_FALSE, _T("FALSE") ));
	
	//Conflict Resolution Strategy
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CR_PRIORITY, _T("CR_PRIORITY") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CR_RECENCY, _T("CR_RECENCY") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CR_SPECIFICITY, _T("CR_SPECIFICITY") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CR_ORDER, _T("CR_ORDER") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CR_LEX, _T("CR_LEX") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CR_MEA, _T("CR_MEA") ));
	
	
				
}





void CAipi_Init::fillDBKeyWords()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("Ms_Access"), AIPI_MS_ACCESS ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("Ms_SqlServer"), AIPI_MS_SQLSERVER ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("Ms_Oracle"),AIPI_MS_ORACLE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("Oracle"), AIPI_ORACLE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("MySql"), AIPI_MYSQL ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("Db2"), AIPI_DB2 ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("MS_ACCESS"), AIPI_MS_ACCESS_UPP));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("MS_SQLSERVER"), AIPI_MS_SQLSERVER_UPP ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("MS_ORACLE"), AIPI_MS_ORACLE_UPP ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("ORACLE"), AIPI_ORACLE_UPP ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("MYSQL"), AIPI_MYSQL_UPP ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("DB2"), AIPI_DB2_UPP ));
	
}

void CAipi_Init::fillID_DBKeyWords()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_MS_ACCESS, _T("Ms_Access") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_MS_SQLSERVER, _T("Ms_SqlServer") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_MS_ORACLE, _T("Ms_Oracle") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_ORACLE, _T("Oracle") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_MYSQL, _T("MySql") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_DB2, _T("Db2") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_MS_ACCESS_UPP, _T("MS_ACCESS") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_MS_SQLSERVER_UPP, _T("MS_SQLSERVER") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_MS_ORACLE_UPP, _T("MS_ORACLE") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_ORACLE_UPP, _T("ORACLE") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_MYSQL_UPP, _T("MYSQL") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_DB2_UPP, _T("DB2") ));
	
	
}


void CAipi_Init::fillCtrlKeyWords()
{
	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("DISPLAYCTRL"), AIPI_DISPLAYCTRL ));
	
	//Controls names
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("OleDBDlg"), AIPI_CTRL_OLEDB ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("JukeBoxDlg"), AIPI_CTRL_JUKEBOX ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("MediaPlayerDlg"), AIPI_CTRL_MEDIAPLAYER ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("ImageFilterDlg"),AIPI_CTRL_IMAGEFILTER ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("ListOptionCtrl"),AIPI_CTRL_LISTOPTION ));
	
	//Control commands
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("ShowCtrl"), AIPI_SHOWCTRL ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("CtrlName"), AIPI_CTRLNAME ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("Play"), AIPI_PLAY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("Path"),AIPI_PATH ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("Insert"),AIPI_INSERT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("InputVar"),AIPI_INPUTVAR ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("ShowTables"),AIPI_SHOWTABLES ));
	
	

}

void CAipi_Init::fillID_CtrlKeyWords()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_DISPLAYCTRL, _T("DISPLAYCTRL") ));
	
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CTRL_OLEDB, _T("OleDBDlg") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CTRL_JUKEBOX, _T("JukeBoxDlg") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CTRL_MEDIAPLAYER, _T("MediaPlayerDlg") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CTRL_IMAGEFILTER, _T("ImageFilterDlg") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CTRL_LISTOPTION, _T("ListOptionCtrl") ));


	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_SHOWCTRL, _T("ShowCtrl") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_CTRLNAME, _T("CtrlName") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_PLAY, _T("Play") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_PATH, _T("Path") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_INSERT, _T("Insert") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_INPUTVAR, _T("InputVar") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(AIPI_SHOWTABLES, _T("ShowTables") ));
	
	
}




void CAipi_Init::fillCKeyWords()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	//C Language keywords must be entered lowercase
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("auto"), C_AUTO ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("break"),C_BREAK ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("case"), C_CASE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("char"), C_CHAR ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("const"), C_CONST ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("continue"), C_CONTINUE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("default"), C_DEFAULT));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("do"), C_DO ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("double"), C_DOUBLE));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("else"), C_ELSE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("enum"), C_ENUM ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("extern"), C_EXTERN));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("float"), C_FLOAT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("for"), C_FOR  ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("goto"), C_GOTO));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("if"), C_IF));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("int"), C_INT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("long"), C_LONG ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("register"), C_REGISTER));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("return"), C_RETURN ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("short"), C_SHORT));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("signed"), C_SIGNED));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("sizeof"), C_SIZEOF));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("static"), C_STATIC));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("struct"), C_STRUCT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("switch"), C_SWITCH ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("typedef"), C_TYPEDEF));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("union"), C_UNION ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("unsigned"), C_UNSIGNED ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("void"), C_VOID ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("volatile"), C_VOLATILE));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("while"), C_WHILE ));

	//pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("c"), C_EXT ));

}


void CAipi_Init::fillID_CKeyWords()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();


	//C Language keywords must be entered lowercase
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_AUTO, _T("auto") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_BREAK, _T("break") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_CASE, _T("case") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_CHAR, _T("char") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_CONST, _T("const") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_CONTINUE, _T("continue") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_DEFAULT, _T("default") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_DO, _T("do") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_DOUBLE, _T("double") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_ELSE, _T("else") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_ENUM, _T("enum") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_EXTERN, _T("extern") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_FLOAT, _T("float") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_FOR, _T("for") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_GOTO, _T("goto") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_IF, _T("if") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_INT, _T("int") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_LONG, _T("long") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_REGISTER, _T("register") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_RETURN, _T("retutn") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_SHORT, _T("short") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_SIGNED, _T("signed") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_SIZEOF, _T("sizeof") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_STATIC, _T("static") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_STRUCT, _T("struct") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_SWITCH, _T("switch") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_TYPEDEF, _T("typedef") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_UNION, _T("union") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_UNSIGNED, _T("unsigned") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_VOID, _T("void") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_VOLATILE, _T("volatile") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_WHILE, _T("while") ));

	//pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(C_EXT, _T("c") ));
	
}





//JavaScript keywords that are not repeated on the C language
void CAipi_Init::fillJScriptKeyWords()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	/* 
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("abstract"), JS_ABSTRACT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("boolean"),JS_BOOLEAN ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("break"),JS_BREAK ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("byte"), JS_BYTE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("case"), JS_CASE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("catch"), JS_CATCH ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("char"), JS_CHAR ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("class"), JS_CLASS));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("const"), JS_CONST ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("continue"), JS_CONTINUE));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("default"), JS_DEFAULT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("do"), JS_DO ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("double"), JS_DOUBLE));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("else"), JS_ELSE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("extends"), JS_EXTENDS  ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("false"), JS_FALSE));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("final"), JS_FINAL));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("finally"), JS_FINALLY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("float"), JS_FLOAT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("for"), JS_FOR)); 
	*/
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("function"), JS_FUNCTION ));
	/*
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("goto"), JS_GOTO));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("int"), JS_INT));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("implements"), JS_IMPLEMENTS));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("input"), JS_INPUT));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("in"), JS_IN ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("instanceof"), JS_INSTANCEOF ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("interface"), JS_INTERFACE));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("long"), JS_LONG ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("native"), JS_NATIVE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("new"), JS_NEW ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("null"), JS_NULL));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("package"), JS_PACKAGE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("private"), JS_PRIVATE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("protected"), JS_PROTECTED));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("public"), JS_PUBLIC ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("return"), JS_RETURN ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("short"), JS_SHORT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("static"), JS_STATIC));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("super"), JS_SUPER ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("switch"), JS_SWITCH ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("synchronized"), JS_SYNCHRONIZED));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("this"), JS_THIS ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("throw"), JS_THROW ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("throws"), JS_THROWS));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("trasient"), JS_TRASIENT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("true"), JS_TRUE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("try"), JS_TRY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("var"), JS_VAR));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("val"), JS_VAL ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("while"), JS_WHILE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("while"), JS_WITH ));
	*/

}

//JavaScript language IDs keywords that are not repeated in C language
void CAipi_Init::fillID_JScriptKeyWords()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	
	/*
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_ABSTRACT, _T("abstract") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_BOOLEAN, _T("boolean") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_BREAK, _T("break") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_BYTE, _T("byte") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_CASE, _T("case") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_CATCH, _T("catch") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_CHAR, _T("char") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_CLASS, _T("class") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_CONST, _T("const") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_CONTINUE, _T("continue") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_DEFAULT, _T("default") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_DO, _T("do")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_DOUBLE, _T("double") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_ELSE, _T("else") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_EXTENDS, _T("extends") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_FALSE, _T("flase") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_FINAL, _T("final") ));	
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_FINALLY, _T("finally") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_FLOAT, _T("float") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_FOR, _T("for") ));
	*/
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_FUNCTION, _T("function") ));
	/*
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_GOTO, _T("goto") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_INT, _T("int") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_IMPLEMENTS, _T("implements") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_INPUT, _T("input") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_IN, _T("in") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_INSTANCEOF, _T("instanceof") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_INTERFACE, _T("interface") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_LONG, _T("long") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_NATIVE, _T("native") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_NEW, _T("new") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_NULL, _T("null")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_PACKAGE, _T("package")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_PRIVATE, _T("private") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_PROTECTED, _T("protected") ));	
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_PUBLIC, _T("public") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_RETURN, _T("return") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_SHORT, _T("short")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_STATIC, _T("static")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_SUPER, _T("super") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_SWITCH, _T("switch") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_SYNCHRONIZED, _T("synchronized") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_THIS, _T("this") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_THROW, _T("throw") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_THROWS, _T("throws") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_TRASIENT, _T("trasient") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_TRUE, _T("true") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_TRY, _T("try") ));	
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_VAR, _T("var") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_VAL, _T("val") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_WHILE, _T("while") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_WITH, _T("with") ));
	*/

				
}

//Visual Basic Script keywords that are not repeated on the C language
void CAipi_Init::fillVBScriptKeyWords()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();

	/* 
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("IsArray"), VBS_ISARRAY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("Erase"),JS_BOOLEAN ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("break"),JS_BREAK ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("byte"), JS_BYTE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("case"), JS_CASE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("catch"), JS_CATCH ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("char"), JS_CHAR ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("class"), JS_CLASS));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("const"), JS_CONST ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("continue"), JS_CONTINUE));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("default"), JS_DEFAULT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("do"), JS_DO ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("double"), JS_DOUBLE));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("else"), JS_ELSE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("extends"), JS_EXTENDS  ));
	*/
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("End"), VBS_END));
	/*
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("false"), JS_FALSE));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("final"), JS_FINAL));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("finally"), JS_FINALLY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("float"), JS_FLOAT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("for"), JS_FOR)); 
	*/
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("Function"), VBS_FUNCTION ));
	/*
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("goto"), JS_GOTO));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("int"), JS_INT));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("implements"), JS_IMPLEMENTS));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("input"), JS_INPUT));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("in"), JS_IN ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("instanceof"), JS_INSTANCEOF ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("interface"), JS_INTERFACE));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("long"), JS_LONG ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("native"), JS_NATIVE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("new"), JS_NEW ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("null"), JS_NULL));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("package"), JS_PACKAGE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("private"), JS_PRIVATE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("protected"), JS_PROTECTED));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("public"), JS_PUBLIC ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("return"), JS_RETURN ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("short"), JS_SHORT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("static"), JS_STATIC));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("super"), JS_SUPER ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("switch"), JS_SWITCH ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("synchronized"), JS_SYNCHRONIZED));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("this"), JS_THIS ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("throw"), JS_THROW ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("throws"), JS_THROWS));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("trasient"), JS_TRASIENT ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("true"), JS_TRUE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("try"), JS_TRY ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("var"), JS_VAR));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("val"), JS_VAL ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("while"), JS_WHILE ));
	pMainFrame->gmKeyWord.insert(CMainFrame::g_mKeyWord::value_type(_T("while"), JS_WITH ));
	*/

}



//Visual Basic Script language IDs keywords that are not repeated in C language
void CAipi_Init::fillID_VBScriptKeyWords()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	
	/*
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_ABSTRACT, _T("abstract") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_BOOLEAN, _T("boolean") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_BREAK, _T("break") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_BYTE, _T("byte") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_CASE, _T("case") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_CATCH, _T("catch") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_CHAR, _T("char") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_CLASS, _T("class") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_CONST, _T("const") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_CONTINUE, _T("continue") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_DEFAULT, _T("default") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_DO, _T("do")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_DOUBLE, _T("double") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_ELSE, _T("else") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_EXTENDS, _T("extends") ));
	*/
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(VBS_END, _T("End") ));
	/*
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_FALSE, _T("flase") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_FINAL, _T("final") ));	
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_FINALLY, _T("finally") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_FLOAT, _T("float") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_FOR, _T("for") ));
	*/
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(VBS_FUNCTION, _T("Function") ));
	/*
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_GOTO, _T("goto") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_INT, _T("int") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_IMPLEMENTS, _T("implements") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_INPUT, _T("input") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_IN, _T("in") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_INSTANCEOF, _T("instanceof") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_INTERFACE, _T("interface") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_LONG, _T("long") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_NATIVE, _T("native") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_NEW, _T("new") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_NULL, _T("null")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_PACKAGE, _T("package")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_PRIVATE, _T("private") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_PROTECTED, _T("protected") ));	
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_PUBLIC, _T("public") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_RETURN, _T("return") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_SHORT, _T("short")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_STATIC, _T("static")  ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_SUPER, _T("super") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_SWITCH, _T("switch") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_SYNCHRONIZED, _T("synchronized") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_THIS, _T("this") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_THROW, _T("throw") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_THROWS, _T("throws") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_TRASIENT, _T("trasient") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_TRUE, _T("true") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_TRY, _T("try") ));	
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_VAR, _T("var") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_VAL, _T("val") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_WHILE, _T("while") ));
	pMainFrame->gmIdKeyWord.insert(CMainFrame::g_mIdKeyWord::value_type(JS_WITH, _T("with") ));
	*/

				
}





void CAipi_Init::fillOperator()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	
	//Doble Character Operators
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(RIGHT_OP, _T(">>") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(LEFT_OP, _T("<<") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(INC_OP, _T("++") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(DEC_OP, _T("--") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(PTR_OP, _T("->") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(ADD_ASSIGN, _T("+=") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(SUB_ASSIGN, _T("-=") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(MUL_ASSIGN, _T("*=") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(DIV_ASSIGN, _T("/=") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(MOD_ASSIGN, _T("%=") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(LE, _T("<=") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(GE, _T(">=") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(ET, _T("==") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(NE, _T("!=") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(AND_OP, _T("&&") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(OR_OP, _T("||") ));

	//Triple Character Operators
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(RIGHT_ASSIGN, _T(">>=") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(LEFT_ASSIGN, _T("<<=") ));
	pMainFrame->gmOperator.insert(CMainFrame::g_mOperator::value_type(ELLIPSIS, _T("...") ));
	
	
}


void CAipi_Init::fillErrorMsg()
{

	CMainFrame* pMainFrame = (CMainFrame*)::AfxGetMainWnd();
	
	CAipi_Error e;
	
	//Lexical Errors Messages
	e.addError(LEXICAL, _T("ERROR: Lexical error."),_T("lexical_error.html"), LEX_ERROR);
	e.addError(OVER_TK_LENGTH, _T("Token length overflow."), _T("over_tk_length_error.html"), LEX_ERROR);

	//Sintax Errors Messages
	e.addError(SINTAX, _T("ERROR: Sintax error."), _T("sintax_error.html"), SINTAX_ERROR );
	e.addError(NO_EXP, _T("No expression was found."),_T("no_exp_error.html"), SINTAX_ERROR);
	e.addError(NO_VAR, _T("No variable was found."), _T("no_var_error.html"), SINTAX_ERROR);
	e.addError(SEMI_EXPECTED, _T("Semicolon expected."), _T("semi_expected_error.html"), SINTAX_ERROR);
	e.addError(UNBAL_BRACES, _T("Unbalance braces."), _T("unbal_braces_error.html"), SINTAX_ERROR );
	e.addError(FUNC_UNDEF, _T("Function undefined."),_T("func_undef_error.html"), SINTAX_ERROR);
	e.addError(TYPE_EXPECTED, _T("Identifier type expected."), _T("type_expected_error.html"), SINTAX_ERROR);
	e.addError(DIRECT_DECLARATOR, _T("Direct declarator incorrect sintax."), _T("direct_declarator.html"), SINTAX_ERROR );
	e.addError(PAREN_EXPECTED, _T("Parenthesis expected."),_T("paren_expected_error.html"), SINTAX_ERROR);
	e.addError(DO_WHILE_END, _T("Do-While end instruction expected."), _T("do_while_expected_error.html"), SINTAX_ERROR);
	e.addError(QUOTE_EXPECTED, _T("Quote expected."), _T("quote_expected_error.html"), SINTAX_ERROR );
	e.addError(BRACE_EXPECTED, _T("Brace expected."), _T("brace_expected_error.html"), SINTAX_ERROR);
	e.addError(COLON_EXPECTED, _T("Colon expected."),_T("colon_expected_error.html"), SINTAX_ERROR);
	
	//Semantic Errors Messages
	e.addError(SEMANT, _T("ERROR: Semantic error."),_T("semant_error.html"), SEMANT_ERROR);
	e.addError(TYPE_ASSIGN, _T("Incompatible type assignation."), _T("type_assign_error.html"), SEMANT_ERROR);
	e.addError(TYPE_VERIFY, _T("Incompatible type operation."), _T("type_verify_error.html"), SEMANT_ERROR);
	e.addError(DUP_VAR, _T("Duplicate variable."), _T("dup_var_error.html"), SEMANT_ERROR );
	e.addError(DUP_FUNC, _T("Duplicate function."),_T("dup_func_error.html"), SEMANT_ERROR);
	e.addError(FLOW_VERIFY, _T("Bad use of flow control instrucction."),_T("flow_verify_error.html"), SEMANT_ERROR);
	e.addError(DIV_BY_ZERO, _T("Division by zero."),_T("div_by_zero.html"), SEMANT_ERROR);
	e.addError(UNKNOW_TYPE, _T("Unknow type."),_T("unknow_type.html"), SEMANT_ERROR);
	e.addError(UNKNOW_CLASS, _T("Unknow class."),_T("unknow_class.html"), SEMANT_ERROR);
	e.addError(NOT_DECLARE, _T("Identifier is not declare."),_T("not_declare.html"), SEMANT_ERROR);

	//Script Errors Messages
	e.addError(JSCRIPT, _T("ERROR: JScript error."),_T("jscript_error.html"), JSCRIPT_ERROR);
	e.addError(VBSCRIPT, _T("ERROR: VBScript error."),_T("vbscript_error.html"), VBSCRIPT_ERROR);
	e.addError(JSCRIPT_PARAM, _T("ERROR: Unable to cath the script function parameters."),_T("script_param.html"), JSCRIPT_ERROR);
	e.addError(VBSCRIPT_PARAM, _T("ERROR: Unable to cath the script function parameters."),_T("script_param.html"), VBSCRIPT_ERROR);
	

	//Others Errors Messages
	e.addError(FILE_READ, _T("File error."), _T("file_error.html"), STOP_ERROR);
	e.addError(DEBUG_STOP, _T("Debug process was suspended."), _T("debug_stop.html"), STOP_ERROR);
	e.addError(ABNORMAL_STOP, _T("WARNING: Abnormal termination."), _T("abnormal_stop.html"), WARNING_ERROR);
	e.addError(FINISH, _T("AIPI depuration process finsihed."), _T("finish.html"), INFO_ERROR);
	e.addError(ERROR_COUNT, _T("Error(s) Summary:-   "), _T("error_count.html"), INFO_ERROR);
	e.addError(WARNING_COUNT, _T("Warning(s) Summary:-   "), _T("warning_count.html"), INFO_ERROR);
	e.addError(EMPTY_MSG, _T(""), _T(""), INFO_ERROR);


	//Warnings Messages
	e.addError(TYPE_CONVERT, _T("The was converted to a compatible type."), _T("type_assign_warning.html"), WARNING_ERROR);
	e.addError(ELEMENT_MISSING, _T("The element is missing."), _T("element_missing.html"), WARNING_ERROR);
}









