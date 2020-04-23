#ifndef HEADER_VM_INTERPRETER_DEFINED
#define HEADER_VM_INTERPRETER_DEFINED


#include "../libs.hpp"
#include "instruction.hpp"
#include "frame.hpp"


namespace vm
{
	class interpreter
	{
	protected:
		size_t program_counter;
		
		const vector<instruction>* instructions;
		
		vector<any_value> value_stack;
		
		vector<frame> frame_stack;
		
	public:
		interpreter(vector<instruction>* instructions, size_t value_size_hint = 4096u, size_t frame_size_hint = 128u);
		
		operator bool();
		
		any_value& operator[](signed char index);
		
		const any_value& operator[](signed char index) const;
		
		bool step();
		
		bool run();
		
	protected:
		template<opcode C>
		inline bool do_instr(const instruction&);
		
		template<>
		inline bool do_instr<opcode::COPY>(const instruction& i)
		{
			self[i.val_b] = self[i.val_a];
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::CHECK>(const instruction& i)
		{
			if (!self[i.val_a])
				++program_counter;
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::CHECK_SET>(const instruction& i)
		{
			if (auto& val_a = self[i.val_a]; val_a) {
				self[i.val_c] = val_a;
				++program_counter;
			}
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::CHECK_EQ>(const instruction& i)
		{
			if (const auto& result = self[i.val_a] == self[i.val_b]; result != self[i.val_c])
				++program_counter;
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::CHECK_LT>(const instruction& i)
		{
			const auto& val_a = self[i.val_a];
			const auto& val_b = self[i.val_b];
			
			// TODO: Implement some sort of exception mechanism for this.
			if (!val_a.holds<number>() || !val_b.holds<number>())
				return false;
			
			if (any_value result = boolean{val_a.as<number>().value < val_b.as<number>().value}; result != self[i.val_c])
				++program_counter;
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::CHECK_LE>(const instruction& i)
		{
			const auto& val_a = self[i.val_a];
			const auto& val_b = self[i.val_b];
			
			// TODO: Implement some sort of exception mechanism for this.
			if (!val_a.holds<number>() || !val_b.holds<number>())
				return false;
			
			if (any_value result = boolean{val_a.as<number>().value <= val_b.as<number>().value}; result != self[i.val_c])
				++program_counter;
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::JUMP>(const instruction& i)
		{
			const auto& val_a = self[i.val_a];
			
			if (!val_a.holds<number>())
				return false;
			
			program_counter = size_t(double(program_counter) + val_a.as<number>().value);
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::CALL>(const instruction& i)
		{
			const auto& val_a = self[i.val_a];
			const auto& val_b = self[i.val_b];
			const auto& val_c = self[i.val_b];
			
			if (!val_a.holds<number>() || !val_b.holds<number>() || !val_c.holds<number>())
				return false;
			
			frame_stack.emplace_back(program_counter, size_t(val_a.as<number>().value), size_t(val_b.as<number>().value));
			program_counter = size_t(val_c.as<number>().value);
			
			return true;
		}
		
		template<>
		inline bool do_instr<opcode::RETURN>(const instruction&)
		{
			program_counter = frame_stack.back().return_address;
			frame_stack.pop_back();
			
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