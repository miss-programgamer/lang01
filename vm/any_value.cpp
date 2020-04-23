#include "any_value.hpp"


namespace vm
{
	any_value::operator bool()
	{
		return !holds<null>() && !holds(false);
	}
	
	any_value operator==(const any_value& lhs, const any_value& rhs)
	{
		return any_value(boolean{(any_value::variant&)(lhs) == (any_value::variant&)(rhs)});
	}
	
	any_value operator!=(const any_value& lhs, const any_value& rhs)
	{
		return any_value(boolean{(any_value::variant&)(lhs) != (any_value::variant&)(rhs)});
	}
}