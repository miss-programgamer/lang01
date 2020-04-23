#ifndef HEADER_VM_INSTRUCTION_DEFINED
#define HEADER_VM_INSTRUCTION_DEFINED


#include "../libs.hpp"


namespace vm
{
	using address_t = unsigned char;
	
	enum opcode: unsigned char
	{
		COPY,

		OP_ADD,
		OP_SUB,
		OP_MUL,
		OP_DIV,

		OP_MOD,
		OP_POW,
		OP_UNM,
		OP_NOT,

		CHECK,
		CHECK_SET,
		CHECK_EQ,
		CHECK_LT,
		CHECK_LE,
		
		JUMP,
		CALL,
		RETURN,
		FORLOOP
	};
	
	class instruction
	{
		friend class interpreter;
		
	protected:
		opcode code;
		
		address_t val_a;
		
		address_t val_b;
		
		address_t val_c;
		
	public:
		instruction(opcode code, address_t val_a, address_t val_b, address_t val_c);
	};
	
	address_t arg_addr(address_t addr);
	
	address_t value_addr(address_t addr);
	
	address_t const_addr(address_t addr);
	
	address_t closure_addr(address_t addr);
}


#else // HEADER_VM_INSTRUCTION_DEFINED


namespace vm
{
	class instruction;
}


#endif // HEADER_VM_INSTRUCTION_DEFINED