#include "call_op.hpp"


namespace nodes
{
	call_op::call_op(any_node* parent_node, const string_view& action_name):
		basic_node(parent_node),
		action_name(action_name)
	{}
	
	ostream& operator<<(ostream& os, const call_op& node)
	{
		os << "[" << node.type << ": " << node.action_name << "]";
		return os;
	}
}