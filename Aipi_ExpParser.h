// Aipi_ExpParser.h: interface for the CAipi_ExpParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_EXPPARSER_H__0CA8B0DE_A582_4FA5_A9CD_687E3EB4FE1F__INCLUDED_)
#define AFX_AIPI_EXPPARSER_H__0CA8B0DE_A582_4FA5_A9CD_687E3EB4FE1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Aipi_Lexer.h"
#include "Aipi_Symbol.h"
#include "Aipi_STableNumeric.h"
#include <stack>
using namespace std;


//enum types { DELIMITER = 1, VARIABLE, NUMBER};

//const int NUMVARS = 26;



class CAipi_ExpParser  
{
public:
	CAipi_ExpParser();
	virtual ~CAipi_ExpParser();

	void initExpParser();
	void getToken();
	void translation_unit();
	void emit_expression(int tk);
	void emit_declaration(int tk);
	void printStack();
	long getTokenizer();
	

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
	void operator_unary();
	void operator_assigment();
	void type_name();

public:
	long m_lookahead;
	CString m_sToken;
	std::stack <double> m_stack;
	
};


#endif // !defined(AFX_AIPI_EXPPARSER_H__0CA8B0DE_A582_4FA5_A9CD_687E3EB4FE1F__INCLUDED_)
