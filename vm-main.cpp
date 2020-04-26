#include "libs.hpp"
#include "vm.hpp"


size_t print(any_value* base, size_t args_index, size_t values_index)
{
	for (size_t i = args_index; i < values_index; i++)
	{
		any_value& val = base[i];
		
		if (val.holds<v::boolean>())
			cout << val.as<v::boolean>().value;
		else if (val.holds<v::number>())
			cout << val.as<v::number>().value;
		else if (val.holds<v::text>())
			cout << val.as<v::text>().value;
		else if (val.holds<v::function>())
			cout << val.as<v::function>().value;
		else if (val.holds<v::ex_function>())
			cout << val.as<v::ex_function>().value;
		else
			cout << "null";
	}
	
	cout << endl;
	return 0;
}


int main(int, char**)
{
	std::iostream::sync_with_stdio(false);
	
	vector<any_value> captures
	{
		v::number{2}, // offset to jump for cond 1
		v::number{4}, // offset to jump for cond 2
		v::number{1}, // number of arguments for print
		
		v::ex_function{print},
		v::text{"expression is true!"},
		v::text{"expression is false..."},
	};
	
	vector<instruction> instructions
	{
		{ opcode::EQ,   true_addr,  true_addr,  false_addr }, // skip next instruction if result of comparing first two values is not equal to third value
		{ opcode::JUMP, 0_cap_addr, 0,          0 },          // jump ahead two instructions
		{ opcode::JUMP, 1_cap_addr, 0,          0 },          // jump ahead four instructions
		
		{ opcode::COPY, 4_cap_addr, 0_ret_addr, 0 },          // first argument of print is "expression is true!"
		{ opcode::CALL, 3_cap_addr, 2_cap_addr, 0 },          // call print with one argument
		{ opcode::RET,  zero_addr,  0,          0 },          // return no values from main
		
		{ opcode::COPY, 5_cap_addr, 0_ret_addr, 0 },          // first argument of print is "expression is false..."
		{ opcode::CALL, 3_cap_addr, 2_cap_addr, 0 },          // call print with one argument
		{ opcode::RET,  zero_addr,  0,          0 },          // return no values from main
	};
	
	vm::function main_function(captures, instructions, 0);
	vm::interpreter interpreter(main_function);
	any_value result = interpreter.run();
	
	return 0;
}