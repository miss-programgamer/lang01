#ifndef HEADER_VM_FRAME_DEFINED
#define HEADER_VM_FRAME_DEFINED


#include "../libs.hpp"
#include "instruction.hpp"
#include "function.hpp"


namespace vm
{
	class frame
	{
		friend class interpreter;
		
	protected:
		function* current_function;
		
		size_t args_index;
		
		size_t values_index;
		
		size_t rets_index;
		
		size_t program_counter;
		
	public:
		frame(function* current_function, size_t base_index, size_t argc);
		
		operator bool();
		
		instruction& current_instruction();
	};
}


#else // HEADER_VM_FRAME_DEFINED


namespace vm
{
	class frame;
}


#endif // HEADER_VM_FRAME_DEFINED