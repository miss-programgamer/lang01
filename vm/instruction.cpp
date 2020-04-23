#include "instruction.hpp"


namespace vm
{
	static_assert(sizeof(instruction) == 4, "vm::instruction is not 32 bits in size.");
	
	instruction::instruction(opcode code, address_t val_a, address_t val_b, address_t val_c):
		code(code),
		val_a(val_a),
		val_b(val_b),
		val_c(val_c)
	{}
	
	address_t arg_addr(address_t addr)
	{
		return (0b00 << 6) | (addr & 0b11'1111);
	}
	
	address_t value_addr(address_t addr)
	{
		return (0b01 << 6) | (addr & 0b11'1111);
	}
	
	address_t const_addr(address_t addr)
	{
		return (0b10 << 6) | (addr & 0b11'1111);
	}
	
	address_t closure_addr(address_t addr)
	{
		return (0b11 << 6) | (addr & 0b11'1111);
	}
}