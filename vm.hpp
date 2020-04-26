#ifndef HEADER_VM_DEFINED
#define HEADER_VM_DEFINED


#include "vm/interpreter.hpp"
using vm::interpreter;
using vm::instruction;
using vm::opcode;
using vm::any_value;
namespace v = vm::value;
using namespace vm::literals;
using vm::false_addr;
using vm::true_addr;
using vm::zero_addr;
using vm::null_addr;


#endif // HEADER_VM_DEFINED