#include "program_decl.hpp"


namespace nodes
{
	program_decl::program_decl(const string_view& program_name):
		program_name(program_name)
	{}
	
	program_decl::program_decl(any_node* parent_node, const string_view& program_name):
		basic_node(parent_node),
		program_name(program_name)
	{}
	
	ostream& operator<<(ostream& os, const program_decl& node)
	{
		os << "[" << node.type << "]";
		return os;
	}
}