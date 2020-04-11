#include "parser.hpp"


namespace nodes
{
	parser::parser(const vector<any_token>& tokens, const string_view& source_name):
		tokens(&tokens),
		source_name(source_name)
	{}
	
	parser::operator bool() const
	{
		return cursor_index < tokens->size();
	}
	
	bool parser::fill(any_node& node)
	{
		node.emplace<program_decl>(source_name);
		
		while (self) {
			match_call_op(node);
		}
		
		return false;
	}
	
	const any_token& parser::cursor_token()
	{
		return (*tokens)[cursor_index];
	}
	
	bool parser::match_call_op(any_node& parent)
	{
		if (cursor_token().holds<identifier>()) {
			parent.emplace_child<call_op>(cursor_token().source_slice());
			++cursor_index;
			return true;
		} else {
			return false;
		}
	}
}