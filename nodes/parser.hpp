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
		string_view source_name;
		
		const vector<any_token>* tokens;
		
		any_node* root;
		
		size_t cursor_index;
		
	public:
		// Creates a parser of the given tokens.
		parser(const string_view& source_name, const vector<any_token>& tokens, any_node* root);
		
		// Checks if the parser has reached the end of its input.
		operator bool() const;
		
		// Parses the given node into a program node.
		bool fill();
		
		// Parses the given tokens into an expression tree as children of the given root node.
		static bool parse(const string_view& source_name, const vector<any_token>& tokens, any_node* root);
		
	protected:
		inline context& global_context()
		{ return root->parent_context(); }
		
		// Returns the token at the current cursor position.
		inline const any_token& cursor_token()
		{ return (*tokens)[cursor_index]; }
		
		// Returns the slice of the cursor token.
		inline const string_view cursor_slice()
		{ return cursor_token().source_slice(); }
		
		// Returns the slice of the cursor token.
		inline const string_view cursor_content()
		{ return cursor_token().content(); }
		
		// Returns whether the cursor contains the given content
		inline bool cursor_contains(const string_view& other_content)
		{ return cursor_content() == other_content; }
		
		// Returns whether the cursor is a trip keyword with the given content.
		inline bool cursor_contains_trip(const any_node& parent, const string_view& other_content)
		{ return parent.parent_context().holds_keyrole(cursor_token(), keyrole::TRIP) && cursor_content() == other_content; }
		
		// Returns whether the cursor is a constant value keyword.
		inline bool cursor_is_const(const any_node& parent)
		{ return parent.parent_context().holds_keyrole(cursor_token(), keyrole::CONST); }
		
		// Returns whether the cursor is a trip keyword.
		inline bool cursor_is_trip(const any_node& parent)
		{ return parent.parent_context().holds_keyrole(cursor_token(), keyrole::TRIP); }
		
		// Returns whether the cursor is a flow keyword.
		inline bool cursor_is_flow(const any_node& parent)
		{ return parent.parent_context().holds_keyrole(cursor_token(), keyrole::FLOW); }
		
		// Returns whether the cursor is a define keyword.
		inline bool cursor_is_define(const any_node& parent)
		{ return parent.parent_context().holds_keyrole(cursor_token(), keyrole::DEFINE); }
		
		// Returns whether the cursor is a variable name.
		inline bool cursor_is_variable(const any_node& parent)
		{ return parent.parent_context().holds_role(cursor_token(), role::VARIABLE); }
		
		// Returns whether the cursor is a variable name or undefined.
		inline bool cursor_is_variable_identifier(const any_node& parent)
		{ return cursor_token().holds<identifier>() && parent.parent_context().holds_any_role(cursor_token(), { role::VARIABLE, role::UNDEFINED }); }
		
		// Returns whether the cursor is a function name.
		inline bool cursor_is_function(const any_node& parent)
		{ return parent.parent_context().holds_role(cursor_token(), role::FUNCTION); }
		
		// Returns whether the cursor is a type name.
		inline bool cursor_is_type(const any_node& parent)
		{ return parent.parent_context().holds_role(cursor_token(), role::TYPE); }
		
		// Moves the cursor forward by one.
		inline bool advance_cursor()
		{ ++cursor_index; return self; }
		
		// Generic expression matching function. Only its specialisations can be called.
		template<typename T>
		bool match_expr(any_node& parent, int precedence);
		
		// Tries to match every given kind of token.
		template<typename... T>
		bool match_any_expr(any_node& parent, int precedence = numeric_limits<int>::max())
		{ return ((self && match_expr<T>(parent, precedence)) || ...); }
		
		// Tries matching a call expression.
		template<>
		bool match_expr<call>(any_node& parent, int precedence)
		{
			if (!cursor_is_function(parent))
				return false;
			
			auto& call_node = parent.emplace_child<call>(cursor_content());
			if (advance_cursor())
				match_any_expr<literal, tuple, scope>(call_node, precedence);
			return true;
		}
		
		// Tries matching a literal expression.
		template<>
		bool match_expr<literal>(any_node& parent, int precedence)
		{
			if (!cursor_token().holds<TOKENS_LITERAL>() && !cursor_is_const(parent))
				return false;
			
			parent.emplace_child<literal>(cursor_token());
			advance_cursor();
			return true;
		}
		
		// Tries matching a variable expression.
		template<>
		bool match_expr<variable>(any_node& parent, int precedence)
		{
			if (!cursor_is_variable_identifier(parent))
				return false;
			
			parent.emplace_child<variable>(cursor_content());
			advance_cursor();
			return true;
		}
		
		// Tries matching a tuple expression.
		template<>
		bool match_expr<tuple>(any_node& parent, int precedence)
		{
			if (!cursor_token().holds<delimiter>("("))
				return false;
			
			advance_cursor();
			auto& tuple_node = parent.emplace_child<tuple>();
			while (self && !cursor_token().holds<newline>() && !cursor_token().holds<delimiter>(")"))
			{
				if (match_any_expr<NODES_MATCHABLE>(tuple_node, precedence)) {
					if (self && cursor_token().holds<delimiter>(","))
						advance_cursor();
				} else {
					tuple_node.emplace_child<nop>();
				}
			}
			return true;
		}
		
		// Tries matching a branching expression.
		template<>
		bool match_expr<branch>(any_node& parent, int precedence)
		{
			if (!cursor_is_flow(parent))
				return false;
			
			if (cursor_contains("if"))
			{
				auto& branch_node = parent.emplace_child<branch>(cursor_token());
				if (advance_cursor() && match_any_expr<NODES_MATCHABLE>(branch_node, precedence))
				{
					if (self && cursor_contains_trip(parent, "do"))
						advance_cursor();
					
					if (!self || !match_any_expr<NODES_MATCHABLE, scope>(branch_node, precedence))
						branch_node.emplace_child<nop>();
				}
				else
				{
					branch_node.emplace_child<nop>();
					branch_node.emplace_child<nop>();
				}
			}
			else {
				// TODO: handle custom branch statements later.
			}
			
			return true;
		}
		
		// Tries matching a scope expression.
		template<>
		bool match_expr<scope>(any_node& parent, int precedence)
		{
			if (!cursor_token().holds<newline>())
				return false;
			
			vector<string_view> lines;
			while (advance_cursor() && cursor_token().holds<upline>())
				lines.push_back(cursor_content());
			parent.emplace_child<scope>(source_name, lines).as<scope>().fill();
			return true;
		}
	};
}


#else // HEADER_NODES_PARSER_DEFINED


namespace nodes
{
	class parser;
}


#endif // HEADER_NODES_PARSER_DEFINED