// Aipi_Parser.h: interface for the CAipi_Parser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_PARSER_H__EAAF8FF9_B2C9_41BF_9655_051206BAFCCB__INCLUDED_)
#define AFX_AIPI_PARSER_H__EAAF8FF9_B2C9_41BF_9655_051206BAFCCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include ".\ScintillaCtrl\ScintillaDocView.h"
#include "Aipi_Lexer.h"
#include "Aipi_Error.h"
#include "Aipi_Emitter.h"
#include "Aipi_ExpParser.h"


class CAipi_Parser  
{
public:
	CAipi_Parser();
	virtual ~CAipi_Parser();

public:
	int matchToken(int tk);
	void translation_unit();
	void initParser();
	//Directive functions
	void directive();
	void directive_list();

	//Class functions
	int attribute_type(); 	
	void class_attr_declaration();
	void class_attr_declaration_list();
	void class_element();
	void class_element_list();
	
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
	
////////////////////////////////////////
//Expression parser
///////////////////////////////////////
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


public:
	unsigned long	m_lookahead;
	

};

#endif // !defined(AFX_AIPI_PARSER_H__EAAF8FF9_B2C9_41BF_9655_051206BAFCCB__INCLUDED_)
