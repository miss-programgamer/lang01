#ifndef HEADER_NODES_PROGRAM_DECL_DEFINED
#define HEADER_NODES_PROGRAM_DECL_DEFINED


#include "../main.hpp"
#include "basic_node.hpp"


namespace nodes
{
	class program_decl: public basic_node
	{
	protected:
		string_view program_name;
		
	public:
		static constexpr string_view type = "program declaration";
		
		// Builds a program node with a program name and without a parent node.
		program_decl(const string_view& program_name);
		
		// Builds a program node with a program name and a parent node.
		program_decl(any_node* parent_node, const string_view& program_name);
		
		friend ostream& operator<<(ostream& os, const program_decl& node);
	};
}


#else // HEADER_NODES_PROGRAM_DECL_DEFINED


namespace nodes
{
	class program_decl;
}


#endif // HEADER_NODES_PROGRAM_DECL_DEFINED