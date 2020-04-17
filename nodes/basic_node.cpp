#include "basic_node.hpp"
#include "any_node.hpp"


namespace nodes
{
	basic_node::basic_node(any_node* parent_node):
		parent_node(parent_node)
	{}
	
	context& basic_node::parent_context()
	{
		return parent_node->parent_context();
	}
	
	const context& basic_node::parent_context() const
	{
		return parent_node->parent_context();
	}
}