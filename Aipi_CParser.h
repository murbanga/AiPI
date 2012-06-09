// Aipi_CParser.h: interface for the CAipi_CParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIPI_CPARSER_H__F2EAC5C7_E6E7_4240_B4B3_847AB87C45C5__INCLUDED_)
#define AFX_AIPI_CPARSER_H__F2EAC5C7_E6E7_4240_B4B3_847AB87C45C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include ".\ScintillaCtrl\ScintillaDocView.h"
#include "Aipi_Lexer.h"
#include "Aipi_Error.h"
#include "Aipi_Emitter.h"


class CAipi_CParser  
{
public:
	CAipi_CParser();
	virtual ~CAipi_CParser();

	public:
	int				matchToken(int tk);
	int				matchTokenGUI(int tk);
	int				matchTokenFile(int tk);
	int				putbackToken(int n_step);	
	int				checkType();
	unsigned int	getPreviousToken();
	
	
	void			initParser();

	void			directive_list();
	void			directive();
	void			declaration_list();
	void			function_definition();
	void			external_declaration();
	void			translation_unit();
	void			jump_statement();
	void			iteration_statement();
	void			selection_statement();
	void			expression_statement();
	void			block_item();
	void			block_item_list();
	void			compound_statement();
	void			labeled_statement();
	void			statement();
	void			statement_list();
	void			designator();
	void			designator_list();
	void			designation();
	void			initializer_list();
	void			initializer();
	void			direct_abstract_declarator();	
	void			abstract_declarator();
	void			type_name();
	void			identifier_list();
	void			parameter_declaration();
	void			parameter_list();
	void			parameter_type_list();
	void			type_qualifier_list();
	void			pointer();	
	void			direct_declarator();
	void			declarator();
	void			type_qualifier();
	void			enumerator();
	void			enumerator_list();
	void			enum_specifier();
	void			struct_declarator();
	void			struct_declarator_list();
	void			specifier_qualifier_list();
	void			struct_declaration();
	void			struct_declaration_list();
	void			struct_or_union();
	void			struct_or_union_specifier();
	void			type_specifier();
	void			storage_class_specifier();
	void			init_declarator();
	void			init_declarator_list();
	void			declaration_specifiers();
	void			declaration();
	void			constant_expression();
	void			expression();
	void			assigment_operator();
	void			assigment_expression();
	void			conditional_expression();
	void			logical_or_expression();
	void			logical_and_expression();
	void			inclusive_or_expression();
	void			exclusive_or_expression();
	void			and_expression();
	void			equality_expression();
	void			relational_expression();
	void			shift_expression();
	void			additive_expression();
	void			multiplicative_expression();
	void			cast_expression();
	void			unary_operator();
	void			unary_expression();
	void			argument_expression_list();
	void			postfix_expression();
	void			primary_expression();
	
		
	
public:
	unsigned long	m_lookahead;
	int				m_currentId_Type;
	int				m_currentDigitType;
	bool			m_jumpExit;



};

#endif // !defined(AFX_AIPI_CPARSER_H__F2EAC5C7_E6E7_4240_B4B3_847AB87C45C5__INCLUDED_)
