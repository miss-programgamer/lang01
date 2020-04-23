#include "frame.hpp"


namespace vm
{
	frame::frame(size_t return_address, size_t base_index, size_t top_index):
		return_address(return_address),
		base_index(base_index),
		top_index(top_index)
	{}
}