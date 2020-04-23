#ifndef HEADER_VM_FRAME_DEFINED
#define HEADER_VM_FRAME_DEFINED


#include "../libs.hpp"
#include "any_value.hpp"


namespace vm
{
	class frame
	{
		friend class interpreter;
		
	protected:
		size_t return_address;
		
		size_t base_index;
		
		size_t top_index;
		
	public:
		frame(size_t return_address, size_t base_index, size_t top_index);
	};
}


#else // HEADER_VM_FRAME_DEFINED


namespace vm
{
	class frame;
}


#endif // HEADER_VM_FRAME_DEFINED