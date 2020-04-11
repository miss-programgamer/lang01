#ifndef HEADER_NODES_NO_OP_DEFINED
#define HEADER_NODES_NO_OP_DEFINED


#include "../main.hpp"
#include "basic_node.hpp"


namespace nodes
{
	class no_op: public basic_node
	{
	public:
		static constexpr string_view type = "no op";
		
		friend ostream& operator<<(ostream& os, const no_op& node);
	};
}


#else // HEADER_NODES_NO_OP_DEFINED


namespace nodes
{
	class no_op;
}


#endif // HEADER_NODES_NO_OP_DEFINED