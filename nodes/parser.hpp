#ifndef HEADER_NODES_PARSER_DEFINED
#define HEADER_NODES_PARSER_DEFINED


#include "../main.hpp"
#include "../tokens.hpp"
#include "any_node.hpp"


namespace nodes
{
	class parser
	{
	protected:
		const vector<any_token>* tokens;
		
		string_view source_name;
		
		size_t cursor_index;
		
		size_t match_start;
		
	public:
		// Creates a parser of the given tokens.
		parser(const vector<any_token>& tokens, const string_view& source_name);
		
		// Checks if the parser has reached the end of its input.
		operator bool() const;
		
		// Parses the given node into a program node.
		bool fill(any_node& node);
		
	protected:
		const any_token& cursor_token();
		
		bool match_call_op(any_node& parent);
	};
}


#else // HEADER_NODES_PARSER_DEFINED


namespace nodes
{
	class parser;
}


#endif // HEADER_NODES_PARSER_DEFINED