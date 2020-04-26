#ifndef HEADER_VM_INSTRUCTION_DEFINED
#define HEADER_VM_INSTRUCTION_DEFINED


#include "../libs.hpp"


namespace vm
{
	using address_t = unsigned char;
	
	enum opcode: unsigned char
	{
		COPY,  JUMP, CALL, RET,
		ADD,   SUB,  MUL,  DIV,
		MOD,   POW,  UNM,  NOT,
		CHECK, EQ,   LT,   LE,
	};
	
	class instruction
	{
		friend class interpreter;
		
	protected:
		opcode code;
		
		address_t addr_a;
		
		address_t addr_b;
		
		address_t addr_c;
		
	public:
		instruction(opcode code, address_t addr_a, address_t addr_b, address_t addr_c);
	};
	
	// Strip the meta information of an address
	address_t strip_addr(address_t addr);
	
	
	// Returns an argument address
	address_t arg_addr(address_t addr);
	
	// Returns a value address
	address_t val_addr(address_t addr);
	
	// Returns a return address (an address to the values returned by the last function call)
	address_t ret_addr(address_t addr);
	
	// Returns a capture address
	address_t cap_addr(address_t addr);
	
	
	inline namespace literals
	{
		inline address_t operator "" _arg_addr(unsigned long long addr)
		{ return arg_addr(address_t(addr)); }
		
		inline address_t operator "" _val_addr(unsigned long long addr)
		{ return val_addr(address_t(addr)); }
		
		inline address_t operator "" _ret_addr(unsigned long long addr)
		{ return ret_addr(address_t(addr)); }
		
		inline address_t operator "" _cap_addr(unsigned long long addr)
		{ return cap_addr(address_t(addr)); }
	}
	
	
	enum cap_reserved_addr: address_t
	{
		false_addr = 0b1111'1100,
		true_addr  = 0b1111'1101,
		zero_addr  = 0b1111'1110,
		null_addr  = 0b1111'1111,
	};
	
	
	// Whether or not the given address is an argument address
	bool is_arg_addr(address_t addr);
	
	// Whether or not the given address is a value address
	bool is_val_addr(address_t addr);
	
	// Whether or not the given address is a return address (an address to the values returned by the last function call)
	bool is_ret_addr(address_t addr);
	
	// Whether or not the given address is a capture address
	bool is_cap_addr(address_t addr);
}


#else // HEADER_VM_INSTRUCTION_DEFINED


namespace vm
{
	class instruction;
}


#endif // HEADER_VM_INSTRUCTION_DEFINED