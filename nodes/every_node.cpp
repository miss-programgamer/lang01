#include "every_node.hpp"


namespace nodes
{
	//========================================
	// class nop;
	//========================================
	
	ostream& operator<<(ostream& os, const nop& node)
	{
		os << "[" << node.type << "]";
		return os;
	}
	
	//========================================
	// class program;
	//========================================
	
	program::program(const string_view& program_name):
		program_name(program_name)
	{}
	
	program::program(any_node* parent_node, const string_view& program_name):
		basic_node(parent_node),
		program_name(program_name)
	{}
	
	ostream& operator<<(ostream& os, const program& node)
	{
		os << "[" << node.type << "]";
		return os;
	}
	
	//========================================
	// class call;
	//========================================
	
	call::call(any_node* parent_node, const string_view& action_name):
		basic_node(parent_node),
		action_name(action_name)
	{}
	
	ostream& operator<<(ostream& os, const call& node)
	{
		os << "[" << node.type << ": " << node.action_name << "]";
		return os;
	}
}