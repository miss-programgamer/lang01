#include "any_value.hpp"


namespace vm
{
	static_assert(sizeof(any_value) == 16, "vm::any_value is not 16 bytes in size.");
	
	any_value::any_value():
		variant(value::null{})
	{}
	
	any_value::any_value(nullptr_t):
		variant(value::null{})
	{}
	
	any_value::any_value(bool value):
		variant(value::boolean{value})
	{}
	
	any_value::any_value(double value):
		variant(value::number{value})
	{}
	
	any_value::operator bool()
	{
		return !holds<value::null>() && !holds(false);
	}
	
	any_value operator==(const any_value& lhs, const any_value& rhs)
	{
		return static_cast<any_value::variant>(lhs) == static_cast<any_value::variant>(rhs);
	}
	
	any_value operator!=(const any_value& lhs, const any_value& rhs)
	{
		return static_cast<any_value::variant>(lhs) != static_cast<any_value::variant>(rhs);
	}
}