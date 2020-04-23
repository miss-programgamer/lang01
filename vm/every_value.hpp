#ifndef HEADER_VM_EVERY_VALUE_DEFINED
#define HEADER_VM_EVERY_VALUE_DEFINED


#include "../libs.hpp"


namespace vm
{
	// Represents the absence of a value.
	struct null {};
	
	// Represents either true or false.
	struct boolean { bool value; };
	
	// Represents a double-precision floating-point number.
	struct number { double value; };
	
	// Represents a null-terminated string of characters.
	struct text { const char* value; };
	
	// Represents a function value.
	struct function { const char* name; };
}


#else // HEADER_VM_EVERY_VALUE_DEFINED


namespace vm
{
	struct number;
}


#endif // HEADER_VM_EVERY_VALUE_DEFINED