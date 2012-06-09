// Aipi_ParserFile.h: interface for the CAipi_ParserFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_PARSERFILE_H__24D14C26_F5C3_4541_BB84_1C535986345D__INCLUDED_)
#define AFX_AIPI_PARSERFILE_H__24D14C26_F5C3_4541_BB84_1C535986345D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include ".\ScintillaCtrl\ScintillaDocView.h"
#include ".\ScriptObject\ScriptObject.h"

#include "Aipi_Lexer.h"
#include "Aipi_Error.h"
#include "Aipi_Emitter.h"
#include "Aipi_ScriptCode.h"
#include "Aipi_ExpParserFile.h"
#include "Aipi_ExpParserFileGlobal.h"

class CAipi_ParserFile  
{
public:
	CAipi_ParserFile();
	virtual ~CAipi_ParserFile();

	public:
	int matchToken(int tk);
	void  emit_rule(int tk);
	void translation_unit();
	void initParser(CString fileName );
	void endParser();
	//Directive functions
	void directive();
	void directive_list();
	//Conflict resolution strategy
	void cr_strategy();

	//Class functions
	int attribute_type(); 	
	void class_attr_declaration(long class_iform, tstring class_name);
	void class_attr_declaration_list(long class_iform, tstring class_name);
	void class_element();
	void class_element_list();

	//Working Memory functions
	void wm_element();
	void wm_element_list();
	void wm_attribute_value_list();
	void wm_attribute_value();
	void wm_multi_attribute_value();
	void wm_parameter();
	void wm_parameter_list();
	
	//Rule functions
	void rule_element();
	void rule_element_list();
	void rule_parameter();
	void rule_parameter_list();
	
	//Left hand side functions
	void lhs_start();
	void lhs_connector();
	void lhs_attribute_value();
	void lhs_multi_attribute_value();
	void lhs_element();
	void lhs_element_list();
	void lhs_attribute_value_list();
	void lhs_fact_address(); 
	
	//Right hand side functions
	void rhs_start();
	void rhs_connector();
	void rhs_attribute_value();	
	void rhs_multi_attribute_value();
	void rhs_element();
	void rhs_element_list();	
	void rhs_attribute_value_list();
	void rhs_parameter();
	void rhs_parameter_list();
	void rhs_action_fact();
	void rhs_action_ctrl();
	void rhs_action_script();
	void rhs_action_command();
	
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

//Functions
	void expression_argument_list();
	
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

///////////////////////////////////////
//Script parser
///////////////////////////////////////
	void script_translation_unit();
	void script_definition();
	void script_js_function_definition();
	void script_vbs_function_definition();
	void script_sql();

////////////////////////////////////////
//Commands
///////////////////////////////////////
	void cmd_db_open();
	void cmd_db_open_parameter();
	void cmd_db_open_parameter_list();
	void cmd_db_close();
	void cmd_printout();
	void cmd_output();
	void cmd_input();

/////////////////////////////////////////////
//Controls
/////////////////////////////////////////////
	void ctrl_jukebox();
	void ctrl_mediaplayer();
	void ctrl_imagefilter();
	void ctrl_listoption();
	void ctrl_oledb();


protected:
	CString	LiteralVarSearch(long iform);
	double	NumericVarSearch(long iform );		
	bool ScriptLoadCode(long nStartSel, long nEndSel, int line, CString lan, CString code, CString name);	
	void ScriptDisplayError( long nStartSel, int line, CString name);


public:
	int		m_currentVarLoc;
	long	m_lookahead;
	long	m_fendPos;

	long	m_currentRuleIForm;
	long	m_currentIdIForm;
	long	m_currentAttrIForm;
	long	m_currentValIForm;
	
	int		m_currentRel;
	int		m_currentCateg;
	int		m_currentCmd;

	float   m_currentCF;
	int		m_currentWeight;

	tstring	m_currentRule;
	tstring m_currentId;
	tstring m_currentAttr;
	tstring m_currentVal;

	

	//Variable or Constant
	int		m_categId;
	int     m_categAttr;
	int     m_categVal;

	//Open Data Base Parameters
	tstring m_dbUser;
	tstring m_dbPassword;
	tstring m_dbProvider;
	tstring m_dbName;

	//New production flag
	bool	m_bNewProduction;
	//Errors cuantity
	int		m_nError;
protected:
	CScriptObject	m_ScriptObj;	
	

};

#endif // !defined(AFX_AIPI_PARSERFILE_H__24D14C26_F5C3_4541_BB84_1C535986345D__INCLUDED_)
