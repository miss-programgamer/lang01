#ifndef HEADER_VM_EVERY_VALUE_DEFINED
#define HEADER_VM_EVERY_VALUE_DEFINED


#include "../libs.hpp"


namespace vm
{
	class function;
	class any_value;
}


namespace vm::value
{
	// Represents the absence of a value.
	struct null {};
	
	inline bool operator==(const null&, const null&)
	{ return true; }
	
	inline bool operator!=(const null&, const null&)
	{ return false; }
	
	// Represents either true or false.
	struct boolean { bool value; };
	
	inline bool operator==(const boolean& lhs, const boolean& rhs)
	{ return lhs.value == rhs.value; }
	
	inline bool operator!=(const boolean& lhs, const boolean& rhs)
	{ return lhs.value != rhs.value; }
	
	// Represents a double-precision floating-point number.
	struct number { double value; };
	
	inline bool operator==(const number& lhs, const number& rhs)
	{ return lhs.value == rhs.value; }
	
	inline bool operator!=(const number& lhs, const number& rhs)
	{ return lhs.value != rhs.value; }
	
	// Represents a null-terminated string of characters.
	struct text { const char* value; };
	
	inline bool operator==(const text& lhs, const text& rhs)
	{ return string_view(lhs.value) == string_view(rhs.value); }
	
	inline bool operator!=(const text& lhs, const text& rhs)
	{ return string_view(lhs.value) != string_view(rhs.value); }
	
	// Represents a function value.
	struct function { vm::function* value; };
	
	inline bool operator==(const function& lhs, const function& rhs)
	{ return lhs.value == rhs.value; }
	
	inline bool operator!=(const function& lhs, const function& rhs)
	{ return lhs.value != rhs.value; }
	
	// Represents an external function value.
	struct ex_function { size_t(*value)(any_value* base, size_t args_index, size_t values_index); };
	
	inline bool operator==(const ex_function& lhs, const ex_function& rhs)
	{ return lhs.value == rhs.value; }
	
	inline bool operator!=(const ex_function& lhs, const ex_function& rhs)
	{ return lhs.value != rhs.value; }
}


#else // HEADER_VM_EVERY_VALUE_DEFINED


namespace vm::value
{
	struct null;
	struct boolean;
	struct number;
	struct text;
	struct function;
	struct ex_function;
}


#endif // HEADER_VM_EVERY_VALUE_DEFINED