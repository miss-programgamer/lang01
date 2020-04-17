#include "parser.hpp"


namespace nodes
{
	parser::parser(const string_view& source_name, const vector<any_token>& tokens, any_node* root):
		source_name(source_name),
		tokens(&tokens),
		root(root)
	{
		cursor_index = 0;
		
		global_context().define_keyword("true",  keyrole::CONST);
		global_context().define_keyword("false", keyrole::CONST);
		
		global_context().define_keyword("if", keyrole::FLOW);
		global_context().define_keyword("do", keyrole::TRIP);
		// global_context().define_keyword("while", keyrole::FLOW);
		
		global_context().define("print", role::FUNCTION);
	}
	
	parser::operator bool() const
	{
		return cursor_index < tokens->size();
	}
	
	bool parser::fill()
	{
		while (self)
			if (!match_any_expr<NODES_MATCHABLE>(*root))
				advance_cursor();
		
		return false;
	}
	
	bool parser::parse(const string_view& source_name, const vector<any_token>& tokens, any_node* root)
	{
		return parser(source_name, tokens, root).fill();
	}
}