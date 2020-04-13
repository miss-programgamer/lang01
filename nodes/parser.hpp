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
		
		any_node root;
		
		size_t match_start;
		
	public:
		// Creates a parser of the given tokens.
		parser(const vector<any_token>& tokens, const string_view& source_name);
		
		// Checks if the parser has reached the end of its input.
		operator bool() const;
		
		// Parses the given node into a program node.
		bool fill(any_node& node);
		
	protected:
		// Returns the token at the current cursor position.
		inline const any_token& cursor_token()
		{ return (*tokens)[cursor_index]; }
		
		// Returns the slice of the cursor token.
		inline const string_view cursor_slice()
		{ return cursor_token().source_slice(); }
		
		// Moves the cursor forward by one.
		inline void advance_cursor()
		{ ++cursor_index; }
		
		// Generic expression matching function. Only its specialisations can be called.
		template<typename T>
		bool match_expr(any_node& parent);
		
		// Tries to match every given kind of token.
		template<typename... T>
		bool match_any_expr(any_node& parent)
		{ return (match_expr<T>(parent) || ...); }
		
		// Tries matching a call expression.
		template<>
		bool match_expr<call>(any_node& parent)
		{
			if (cursor_token().holds<identifier>())
			{
				parent.emplace_child<call>(cursor_slice());
				advance_cursor();
				return true;
			}
			else {
				return false;
			}
		}
	};
}


#else // HEADER_NODES_PARSER_DEFINED


namespace nodes
{
	class parser;
}


#endif // HEADER_NODES_PARSER_DEFINED