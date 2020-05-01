#include "frame.hpp"


namespace vm
{
	frame::frame(function* current_function, size_t base_index, size_t argc):
		current_function(current_function),
		args_index(base_index),
		values_index(base_index + argc),
		rets_index(base_index + argc + current_function->stack_space),
		program_counter(0)
	{}
	
	frame::operator bool()
	{
		return program_counter < current_function->instructions.size();
	}
	
	instruction& frame::current_instruction()
	{
		return current_function->get_instruction(program_counter);
	}
}