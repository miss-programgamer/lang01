#include "interpreter.hpp"


namespace vm
{
	interpreter::interpreter(vector<instruction>* instructions, size_t value_size_hint, size_t frame_size_hint):
		program_counter(0),
		instructions(instructions),
		value_stack(value_size_hint)
	{
		frame_stack.reserve(frame_size_hint);
		frame_stack.emplace_back(0, 1, 1);
	}
	
	interpreter::operator bool()
	{
		return program_counter < instructions->size();
	}
	
	any_value& interpreter::operator[](signed char index)
	{
		return value_stack[frame_stack.back().base_index + index];
	}
	
	const any_value& interpreter::operator[](signed char index) const
	{
		return value_stack[frame_stack.back().base_index + index];
	}
	
	bool interpreter::step()
	{
		if (!self)
			return false;
		
		const auto& i = (*instructions)[program_counter++];
		switch (i.code)
		{
		case opcode::COPY:      return do_instr<opcode::COPY>(i);
		case opcode::CHECK:     return do_instr<opcode::CHECK>(i);
		case opcode::CHECK_SET: return do_instr<opcode::CHECK_SET>(i);
		case opcode::CHECK_EQ:  return do_instr<opcode::CHECK_EQ>(i);
		case opcode::CHECK_LT:  return do_instr<opcode::CHECK_LT>(i);
		case opcode::CHECK_LE:  return do_instr<opcode::CHECK_LE>(i);
		case opcode::JUMP:      return do_instr<opcode::JUMP>(i);
		case opcode::CALL:      return do_instr<opcode::CALL>(i);
		case opcode::RETURN:    return do_instr<opcode::RETURN>(i);
		default:                return false;
		}
	}
	
	bool interpreter::run()
	{
		while (step());
		return false;
	}
}