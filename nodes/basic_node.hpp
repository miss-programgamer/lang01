#ifndef HEADER_NODES_BASIC_NODE_DEFINED
#define HEADER_NODES_BASIC_NODE_DEFINED


#include "../main.hpp"
#include "context.hpp"


namespace nodes
{
	class any_node;
	
	class basic_node
	{
		friend class any_node;
		
	protected:
		any_node* parent_node;
		
		vector<any_node*> children_nodes;
		
		basic_node(any_node* parent_node = nullptr);
		
		context& parent_context();
		
		const context& parent_context() const;
	};
}


#else // HEADER_NODES_BASIC_NODE_DEFINED


namespace nodes
{
	class basic_node;
}


#endif // HEADER_NODES_BASIC_NODE_DEFINED