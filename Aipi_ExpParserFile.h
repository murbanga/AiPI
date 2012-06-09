// Aipi_ExpParserFile.h: interface for the CAipi_ExpParserFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_EXPPARSERFILE_H__3495A648_A7A6_4145_8C2D_E83E9F07AEA1__INCLUDED_)
#define AFX_AIPI_EXPPARSERFILE_H__3495A648_A7A6_4145_8C2D_E83E9F07AEA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include ".\ScriptObject\ScriptObject.h"
#include ".\ScriptObject\SafeArrayHelper.h"
#include ".\SQLQuery\SQLQuery.h"
#include "OleDBConnectionDlg.h"
#include "OleDBConnectionProp.h"
#include "OleDBDlg.h"

#include <setjmp.h>

#include "Aipi_Lexer.h"
#include "Aipi_Symbol.h"
#include "Aipi_STableLocalNumeric.h"
#include "Aipi_Main.h"
#include <stack>
using namespace std;



#define	VAR_GLOBAL		0
#define VAR_LOCAL		1		

class CAipi_ExpParserFile  
{
public:
	CAipi_ExpParserFile();
	virtual ~CAipi_ExpParserFile();
	
	void initExpParserFile();
	void callExpParserFile();
	void initTokenizer();
	void getToken();
	void translation_unit();
	void emit_expression(int tk);
	void emit_declaration(int tk);
	void printStack();
	long getTokenizer();

//////////////////////////////////////
//Lexer//
/////////////////////////////////////
	bool	isDigit(CString s);
	double  isDigitOpt(CString s);
	bool	isAlphabetic(CString s);

	

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
	void expression_statement();
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

//Functions
	void expression_argument_list();

		

//Operators
	void operator_unary();
	void operator_assigment();
	void type_name();


protected:
	CString LiteralVarSearch( long iform);
	double  NumericVarSearch( long iform);
	void	ExecCmdSearch(long pm, int index1, int index2);
	long	ScriptSaveParam( long i1, long i2);
	void	ScriptDisplayError(long nStartSel, int line, CString name);
	void    ScriptSearch(long iform, tstring sId);
	CString ScriptExecute(long pos1, long index1, int nparam, CString name, CString lang, CString code);

public:
	tstring m_sCurrentId;
	double	m_dCurrentId;
	

	long m_lookahead;
	long m_index;
	long m_endIndex;
	long m_fendPos;
	int  m_currentType;
	CString m_sToken;

	

//Variables structures	
	std::stack <double> m_stackNumeric;
	std::stack <tstring> m_stackLiteral;

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
	CSQLQuery		m_query;

	//Saves script function parameters
	vector<CString>	m_vParameters;

	int	 SqlSelectDB(tstring db);	
	void SqlOpenOleDB();
	void SqlOpenConnectionDlg();
	void SqlShowDBDlg();
	void SqlRunQuery(CString query);
	void SqlRunQueryVars(CString query, long index1, long index2);

private:
	jmp_buf e_buf; /* hold environment for longjmp() */


};

#endif // !defined(AFX_AIPI_EXPPARSERFILE_H__3495A648_A7A6_4145_8C2D_E83E9F07AEA1__INCLUDED_)
