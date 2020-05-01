#include "interpreter.hpp"


#define TRY_INSTR(i, op) case op: return do_instr<op>(i)


namespace vm
{
	any_value interpreter::zero_value = value::number{0};
	
	any_value interpreter::null_value;
	
	any_value interpreter::false_value = value::boolean{false};
	
	any_value interpreter::true_value = value::boolean{true};
	
	interpreter::interpreter(function& main_function, size_t value_size_hint, size_t frame_size_hint):
		value_stack(value_size_hint)
	{
		frame_stack.reserve(frame_size_hint);
		frame_stack.emplace_back(&main_function, 0, 0);
	}
	
	interpreter::operator bool()
	{
		return frame_stack.size() > 0u;
	}
	
	any_value& interpreter::operator[](address_t index)
	{
		const auto addr = strip_addr(index);
		
		if (is_arg_addr(index)) {
			return value_stack[frame_stack.back().args_index + addr];
		} else if (is_val_addr(index)) {
			return value_stack[frame_stack.back().values_index + addr];
		} else if (is_ret_addr(index)) {
			return value_stack[frame_stack.back().rets_index + addr];
		} else if (is_cap_addr(index))
		{
			if (addr < 60)
			{
				return top_frame().current_function->captures[addr];
			}
			else
			{
				if (addr == 60) {
					return zero_value;
				} else if (addr == 61) {
					return null_value;
				} else if (addr == 62) {
					return false_value;
				} else if (addr == 63) {
					return true_value;
				}
			}
		}
		
		throw std::runtime_error("this is unreachable, but compilers will complain if I don't put anything here.");
	}
	
	bool interpreter::step()
	{
		if (!self)
			return false;
		
		if (!top_frame())
			return do_instr<opcode::RET>({ opcode::RET, 0, 0, 0 });
		
		const auto& instr = current_instruction();
		skip_ahead();
		switch (instr.code)
		{
			TRY_INSTR(instr, opcode::COPY);
			TRY_INSTR(instr, opcode::JUMP);
			TRY_INSTR(instr, opcode::CALL);
			TRY_INSTR(instr, opcode::RET);
			
			TRY_INSTR(instr, opcode::ADD);
			TRY_INSTR(instr, opcode::SUB);
			TRY_INSTR(instr, opcode::MUL);
			TRY_INSTR(instr, opcode::DIV);
			
			TRY_INSTR(instr, opcode::MOD);
			TRY_INSTR(instr, opcode::POW);
			TRY_INSTR(instr, opcode::UNM);
			TRY_INSTR(instr, opcode::NOT);
			
			TRY_INSTR(instr, opcode::CHECK);
			TRY_INSTR(instr, opcode::EQ);
			TRY_INSTR(instr, opcode::LT);
			TRY_INSTR(instr, opcode::LE);
			
			default: return false;
		}
	}
	
	bool interpreter::run()
	{
		while (self && step());
		return false;
	}
}