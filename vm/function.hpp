#ifndef HEADER_VM_FUNCTION_DEFINED
#define HEADER_VM_FUNCTION_DEFINED


#include "../libs.hpp"
#include "instruction.hpp"
#include "any_value.hpp"


namespace vm
{
	class function
	{
		friend class frame;
		
		friend class interpreter;
		
	protected:
		vector<any_value>* captures;
		
		vector<instruction>* instructions;
		
		size_t stack_space;
		
	public:
		function(vector<any_value>& captures, vector<instruction>& instructions, size_t stack_space);
		
		instruction& get_instruction(size_t index);
		
		const instruction& get_instruction(size_t index) const;
		
		any_value& get_capture(size_t index);
		
		const any_value& get_capture(size_t index) const;
	};
}


#else // HEADER_VM_FUNCTION_DEFINED


namespace vm
{
	class function;
}


#endif // HEADER_VM_FUNCTION_DEFINED