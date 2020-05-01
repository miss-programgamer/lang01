#include "function.hpp"


namespace vm
{
	function::function(vector<any_value>& captures, vector<instruction>& instructions, size_t stack_space):
		captures(captures),
		instructions(instructions),
		stack_space(stack_space)
	{}
	
	instruction& function::get_instruction(size_t index)
	{
		return instructions[index];
	}
	
	const instruction& function::get_instruction(size_t index) const
	{
		return instructions[index];
	}
	
	any_value& function::get_capture(size_t index)
	{
		return captures[index];
	}
	
	const any_value& function::get_capture(size_t index) const
	{
		return captures[index];
	}
}