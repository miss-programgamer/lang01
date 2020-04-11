#ifndef HEADER_NODES_CALL_OP_DEFINED
#define HEADER_NODES_CALL_OP_DEFINED


#include "../main.hpp"
#include "basic_node.hpp"


namespace nodes
{
	class call_op: public basic_node
	{
	protected:
		string_view action_name;
		
	public:
		static constexpr string_view type = "call operation";
		
		// Builds a call operation with a parent node and a function name
		call_op(any_node* parent_node, const string_view& action_name);
		
		friend ostream& operator<<(ostream& os, const call_op& node);
	};
}


#else // HEADER_NODES_CALL_OP_DEFINED


namespace nodes
{
	class call_act;
}


#endif // HEADER_NODES_CALL_OP_DEFINED