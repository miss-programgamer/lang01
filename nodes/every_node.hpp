#ifndef HEADER_NODES_EVERY_NODE_DEFINED
#define HEADER_NODES_EVERY_NODE_DEFINED


#include "../main.hpp"
#include "../tokens.hpp"
#include "basic_node.hpp"
#include "context.hpp"


namespace nodes
{
	// Represents the absence of any kind operation. It does nothing!
	class nop: public basic_node
	{
	public:
		static constexpr string_view type = "nop";
		
		using basic_node::basic_node;
		
		friend ostream& operator<<(ostream& os, const nop& node);
	};
	
	// Represents the root node of a program.
	class program: public basic_node, public context
	{
	protected:
		string_view program_name;
		
	public:
		static constexpr string_view type = "program";
		
		// Builds a program node with a program name and a parent node.
		program(any_node* parent_node, const string_view& program_name);
		
		context& parent_context();
		
		const context& parent_context() const;
		
		friend ostream& operator<<(ostream& os, const program& node);
	};
	
	// Represents the literal value of a token.
	class literal: public basic_node
	{
	protected:
		const any_token* value;
		
	public:
		static constexpr string_view type = "literal";
		
		// Builds a literal node with a parent node and a token value.
		literal(any_node* parent_node, const any_token& value);
		
		friend ostream& operator<<(ostream& os, const literal& node);
	};
	
	// Represents the variable value of an identifier.
	class variable: public basic_node
	{
	protected:
		string_view variable_name;
		
	public:
		static constexpr string_view type = "variable";
		
		// Builds a literal node with a parent node and a token value.
		variable(any_node* parent_node, const string_view& variable_name);
		
		friend ostream& operator<<(ostream& os, const variable& node);
	};
	
	// Represents a list of any expressions delimited by parentheses and commas.
	class tuple: public basic_node
	{
	public:
		static constexpr string_view type = "tuple";
		
		using basic_node::basic_node;
		
		friend ostream& operator<<(ostream& os, const tuple& node);
	};
	
	// Represents a procedure call expression.
	class call: public basic_node
	{
	protected:
		string_view action_name;
		
	public:
		static constexpr string_view type = "call";
		
		// Builds a call operation with a parent node and a function name
		call(any_node* parent_node, const string_view& action_name);
		
		friend ostream& operator<<(ostream& os, const call& node);
	};
	
	// Represents a branching path expression.
	class branch: public basic_node
	{
	protected:
		const any_token* kind;
		
	public:
		static constexpr string_view type = "branch";
		
		// Builds a branching node with a parent node and a token value.
		branch(any_node* parent_node, const any_token& kind);
		
		friend ostream& operator<<(ostream& os, const branch& node);
	};
	
	// Represents a list of lines to be lexed and parsed.
	class scope: public basic_node, public context
	{
	protected:
		const string_view* source_name;
		
		const vector<string_view>* source_lines;
		
		vector<any_token> tokens;
		
	public:
		static constexpr string_view type = "scope";
		
		// Builds a scope node with a parent node and a list of lines.
		scope(any_node* parent_node, const string_view& source_name, const vector<string_view>& source_lines);
		
		context& parent_context();
		
		const context& parent_context() const;
		
		bool fill();
	
	protected:
		// Returns the last child of this node's parent, which should always just be the variant containing this node.
		any_node* parent_last_child();
		
		friend ostream& operator<<(ostream& os, const scope& node);
	};
}


#else // HEADER_NODES_EVERY_NODE_DEFINED


namespace nodes
{
	class nop;
	class program;
	class literal;
	class variable;
	class tuple;
	class call;
	class branch;
	class scope;
}


#endif // HEADER_NODES_EVERY_NODE_DEFINED