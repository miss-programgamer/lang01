#include "no_op.hpp"


namespace nodes
{
	ostream& operator<<(ostream& os, const no_op& node)
	{
		os << "[" << node.type << "]";
		return os;
	}
}