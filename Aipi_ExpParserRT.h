// Aipi_ExpParserRT.h: interface for the CAipi_ExpParserRT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_EXPPARSERRT_H__D96E24D4_0CA1_4E69_B676_CD938031ACE4__INCLUDED_)
#define AFX_AIPI_EXPPARSERRT_H__D96E24D4_0CA1_4E69_B676_CD938031ACE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_Lexer.h"
#include "Aipi_Symbol.h"
#include "Aipi_STableNumeric.h"
#include <stack>
using namespace std;



class CAipi_ExpParserRT  
{
public:
	CAipi_ExpParserRT();
	virtual ~CAipi_ExpParserRT();

	void initExpParserRT();
	void emit_expression(int tk);
	void emit_declaration(int tk);
	int matchToken(int tk);
	void printStack();

//  Begins the parser transllation
	void translation_unit();

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
	
	
//Operators
	int operator_unary();
	int operator_assigment();

//Keywords
	int keyword_type_name();

public:
	int m_lookahead;
	CString m_sToken;
	std::stack <double> m_stack;

};

#endif // !defined(AFX_AIPI_EXPPARSERRT_H__D96E24D4_0CA1_4E69_B676_CD938031ACE4__INCLUDED_)
