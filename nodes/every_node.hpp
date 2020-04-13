#ifndef HEADER_NODES_EVERY_NODE_DEFINED
#define HEADER_NODES_EVERY_NODE_DEFINED


#include "../main.hpp"
#include "basic_node.hpp"


namespace nodes
{
	// Represents the absence of any kind operation. It does nothing!
	class nop: public basic_node
	{
	public:
		static constexpr string_view type = "nop";
		
		friend ostream& operator<<(ostream& os, const nop& node);
	};
	
	// Represents the root node of a program.
	class program: public basic_node
	{
	protected:
		string_view program_name;
		
	public:
		static constexpr string_view type = "program declaration";
		
		// Builds a program node with a program name and without a parent node.
		program(const string_view& program_name);
		
		// Builds a program node with a program name and a parent node.
		program(any_node* parent_node, const string_view& program_name);
		
		friend ostream& operator<<(ostream& os, const program& node);
	};
	
	// Represents a procedure call expression.
	class call: public basic_node
	{
	protected:
		string_view action_name;
		
	public:
		static constexpr string_view type = "call operation";
		
		// Builds a call operation with a parent node and a function name
		call(any_node* parent_node, const string_view& action_name);
		
		friend ostream& operator<<(ostream& os, const call& node);
	};
}


#else // HEADER_NODES_EVERY_NODE_DEFINED


namespace nodes
{
	class nop;
	class program;
}


#endif // HEADER_NODES_EVERY_NODE_DEFINED