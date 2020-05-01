#ifndef HEADER_VM_INTERPRETER_DEFINED
#define HEADER_VM_INTERPRETER_DEFINED


#include "../libs.hpp"
#include "instruction.hpp"
#include "any_value.hpp"
#include "function.hpp"
#include "frame.hpp"


namespace vm
{
	class interpreter
	{
	protected:
		static any_value zero_value;
		
		static any_value null_value;
		
		static any_value false_value;
		
		static any_value true_value;
		
		vector<any_value> value_stack;
		
		vector<frame> frame_stack;
		
	public:
		interpreter(function& main_function, size_t value_size_hint = 4096u, size_t frame_size_hint = 128u);
		
		operator bool();
		
		any_value& operator[](address_t index);
		
		bool step();
		
		bool run();
		
	protected:
		inline frame& top_frame()
		{ return frame_stack.back(); }
		
		inline const frame& top_frame() const
		{ return frame_stack.back(); }
		
		inline size_t& program_counter()
		{ return top_frame().program_counter; }
		
		inline const instruction& current_instruction()
		{ return top_frame().current_instruction(); }
		
		inline void skip_ahead()
		{ program_counter()++; }
		
		inline void skip_offset(size_t offset)
		{ program_counter() += offset; }
		
		template<opcode C>
		inline bool do_instr(const instruction&);
		
		template<>
		inline bool do_instr<opcode::COPY>(const instruction& i)
		{
			self[i.addr_b] = self[i.addr_a];
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::JUMP>(const instruction& i)
		{
			auto& val = self[i.addr_a].as<value::number>().value;
			skip_offset(size_t(val) - 1);
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::CALL>(const instruction& i)
		{
			if (self[i.addr_a].holds<value::function>())
			{
				auto func = self[i.addr_a].as<value::function>().value;
				auto argc = self[i.addr_b].as<value::number>().value;
				
				frame_stack.emplace_back(func, top_frame().rets_index, size_t(argc));
				return true;
			}
			else if (self[i.addr_a].holds<value::ex_function>())
			{
				auto func = self[i.addr_a].as<value::ex_function>().value;
				auto argc = self[i.addr_b].as<value::number>().value;
				
				func(value_stack.data(), top_frame().rets_index, top_frame().rets_index + size_t(argc));
				return true;
			}
			else {
				return false;
			}
		}
		
		template<>
		inline bool do_instr<opcode::RET>(const instruction&)
		{
			frame_stack.pop_back();
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::ADD>(const instruction& i)
		{
			auto& lhs  = self[i.addr_a].as<value::number>();
			auto& rhs  = self[i.addr_b].as<value::number>();
			auto& dest = self[i.addr_c];
			
			dest = lhs.value + rhs.value;
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::SUB>(const instruction& i)
		{
			auto& lhs  = self[i.addr_a].as<value::number>();
			auto& rhs  = self[i.addr_b].as<value::number>();
			auto& dest = self[i.addr_c];
			
			dest = lhs.value - rhs.value;
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::MUL>(const instruction& i)
		{
			auto& lhs  = self[i.addr_a].as<value::number>();
			auto& rhs  = self[i.addr_b].as<value::number>();
			auto& dest = self[i.addr_c];
			
			dest = lhs.value * rhs.value;
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::DIV>(const instruction& i)
		{
			auto& lhs  = self[i.addr_a].as<value::number>();
			auto& rhs  = self[i.addr_b].as<value::number>();
			auto& dest = self[i.addr_c];
			
			dest = lhs.value / rhs.value;
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::MOD>(const instruction& i)
		{
			auto& lhs  = self[i.addr_a].as<value::number>();
			auto& rhs  = self[i.addr_b].as<value::number>();
			auto& dest = self[i.addr_c];
			
			dest = double(std::int_fast64_t(lhs.value) % std::int_fast64_t(rhs.value));
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::POW>(const instruction& i)
		{
			auto& lhs  = self[i.addr_a].as<value::number>();
			auto& rhs  = self[i.addr_b].as<value::number>();
			auto& dest = self[i.addr_c];
			
			dest = std::pow(lhs.value, rhs.value);
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::UNM>(const instruction& i)
		{
			auto& arg  = self[i.addr_a].as<value::number>();
			auto& dest = self[i.addr_c];
			
			dest = -arg.value;
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::NOT>(const instruction& i)
		{
			auto& arg  = self[i.addr_a];
			auto& dest = self[i.addr_c];
			
			dest = value::boolean{!arg};
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::CHECK>(const instruction& i)
		{
			auto& arg  = self[i.addr_a];
			auto& set  = self[i.addr_b];
			auto& dest = self[i.addr_c];
			
			if (!arg) {
				if (set) dest = arg;
				skip_ahead();
			}
			
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::EQ>(const instruction& i)
		{
			const auto& lhs = self[i.addr_a];
			const auto& rhs = self[i.addr_b];
			const auto& ref = self[i.addr_c];
			
			if (any_value result = lhs == rhs; result != ref)
				skip_ahead();
			
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::LT>(const instruction& i)
		{
			const auto& lhs = self[i.addr_a].as<value::number>().value;
			const auto& rhs = self[i.addr_b].as<value::number>().value;
			const auto& ref = self[i.addr_c];
			
			if (any_value result = lhs < rhs; result != ref)
				skip_ahead();
			
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::LE>(const instruction& i)
		{
			const auto& lhs = self[i.addr_a].as<value::number>().value;
			const auto& rhs = self[i.addr_b].as<value::number>().value;
			const auto& ref = self[i.addr_c];
			
			if (any_value result = lhs <= rhs; result != ref)
				skip_ahead();
			
			return true;
		}
	};
}


#else // HEADER_VM_INTERPRETER_DEFINED


namespace vm
{
	class interpreter;
}


#endif // HEADER_VM_INTERPRETER_DEFINED