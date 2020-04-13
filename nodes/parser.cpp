#include "parser.hpp"


namespace nodes
{
	parser::parser(const vector<any_token>& tokens, const string_view& source_name):
		tokens(&tokens),
		source_name(source_name),
		root(program(source_name))
	{
		cursor_index = 0;
	}
	
	parser::operator bool() const
	{
		return cursor_index < tokens->size();
	}
	
	bool parser::fill(any_node& node)
	{
		while (self) {
			if (!match_any_expr<NODES_MATCHABLE>(root)) {
				advance_cursor();
			}
		}
		
		node = move(root);
		return false;
	}
}