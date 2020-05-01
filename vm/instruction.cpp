#include "instruction.hpp"


namespace vm
{
	static_assert(sizeof(instruction) == 4, "vm::instruction is not 4 bytes in size.");
	
	instruction::instruction(opcode code, address_t addr_a, address_t addr_b, address_t addr_c):
		code(code),
		addr_a(addr_a),
		addr_b(addr_b),
		addr_c(addr_c)
	{}
	
	
	address_t strip_addr(address_t addr)
	{
		return addr & 0b11'1111;
	}
	
	
	address_t arg_addr(address_t addr)
	{
		return (0b00 << 6) | (addr & 0b11'1111);
	}
	
	address_t val_addr(address_t addr)
	{
		return (0b01 << 6) | (addr & 0b11'1111);
	}
	
	address_t ret_addr(address_t addr)
	{
		return (0b10 << 6) | (addr & 0b11'1111);
	}
	
	address_t cap_addr(address_t addr)
	{
		return (0b11 << 6) | (addr & 0b11'1111);
	}
	
	
	bool is_arg_addr(address_t addr)
	{
		return (addr & (0b11 << 6)) == (0b00 << 6);
	}
	
	bool is_val_addr(address_t addr)
	{
		return (addr & (0b11 << 6)) == (0b01 << 6);
	}
	
	bool is_ret_addr(address_t addr)
	{
		return (addr & (0b11 << 6)) == (0b10 << 6);
	}
	
	bool is_cap_addr(address_t addr)
	{
		return (addr & (0b11 << 6)) == (0b11 << 6);
	}
}