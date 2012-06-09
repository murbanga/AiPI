// Aipi_ExpParserFileGlobal.h: interface for the CAipi_ExpParserFileGlobal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_EXPPARSERFILEGLOBAL_H__8D70E15C_E6DB_4860_B3AC_2A474175AF45__INCLUDED_)
#define AFX_AIPI_EXPPARSERFILEGLOBAL_H__8D70E15C_E6DB_4860_B3AC_2A474175AF45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <setjmp.h>

#include "Aipi_Lexer.h"
#include "Aipi_Symbol.h"
#include "Aipi_STableGlobalNumeric.h"
#include "Aipi_Main.h"
#include "Aipi_Tokenizer.h"
#include <stack>
using namespace std;



class CAipi_ExpParserFileGlobal  
{
public:
	CAipi_ExpParserFileGlobal();
	virtual ~CAipi_ExpParserFileGlobal();

	void initExpParserFileGlobal();
	int matchToken(int tk);
	void translation_unit();
	void emit_expression(int tk);
	void emit_declaration(int tk);
	

//////////////////////////////////////
//Declaration parser
//////////////////////////////////////
	void declaration_specifiers();
	void declaration();
	void declarator_direct();
	void declarator_list_init();
	void declarator_init();
//Initializers	
	void initializer();
	void initializer_list();
	void parameter_declaration();
	void parameter_list();


	
////////////////////////////////////////
//Expression parser
///////////////////////////////////////
	void expression_argument_list();
	void expression();
	void expression_assignment();
	void expression_logical_or();
	void expression_logical_and();
	void expression_equality();
	void expression_relational(); 	
	void expression_aritmetic();
	void expression_term();
	void expression_unary_plus();
	void expression_unary_minus();
	void expression_unary_increment();
	void expression_unary_decrement();
	void expression_factor();
//Atoms
	void expression_atom_identifier();
	void expression_atom_constant();
	void expression_atom_literal();	

////////////////////////////////////////
//Commands
///////////////////////////////////////
	void cmd_db_open();
	void cmd_db_open_parameter();
	void cmd_db_open_parameter_list();
	void cmd_db_close();
	void cmd_output();
	int  cmd_input();
	void cmd_input_continue();

/////////////////////////////////////////////
//Controls
/////////////////////////////////////////////
	void ctrl_jukebox();
	void ctrl_mediaplayer();
	void ctrl_imagefilter();
	int  ctrl_listoption();
	void ctrl_listoption_continue();
	void ctrl_oledb();
		

//Operators
	void operator_unary();
	void operator_assigment();
	void type_name();

public:
	long    m_lCurrentIForm;
	double	m_dCurrentId;
	tstring m_sCurrentId; //It is not necesary ,it just for test

	long m_lookahead;
	long m_fendPos;
	int	 m_currentType; 
	int	 m_dataCateg;
	CString m_sToken;
	std::stack<double> m_stackNumeric;
	std::stack<tstring> m_stackLiteral;

	//Flag for Open Data Base Connection Dlg 
	bool	m_bFlagConnDlg;
	//int		m_idbProvider;	
	tstring	m_dbProvider;
	tstring m_dbDNS;
	tstring m_dbUser;
	tstring m_dbPassword;
	tstring m_dbName;


protected:
	CScriptObject	m_ScriptObj;
	//Saves script function parameters
	vector<CString>	m_vParameters;

	int	 SqlSelectDB(tstring db);	
	void SqlOpenOleDB();
	void SqlOpenConnectionDlg();
	void SqlShowDBDlg();

	CString LiteralVarSearch(long iform);
	double  NumericVarSearch(long iform);

};

#endif // !defined(AFX_AIPI_EXPPARSERFILEGLOBAL_H__8D70E15C_E6DB_4860_B3AC_2A474175AF45__INCLUDED_)
