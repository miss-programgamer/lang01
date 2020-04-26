#ifndef HEADER_VM_ANY_VALUE_DEFINED
#define HEADER_VM_ANY_VALUE_DEFINED


#include "../libs.hpp"
#include "every_value.hpp"


#define VALUES_EVERY value::null, value::boolean, value::number, value::text, value::function, value::ex_function


namespace vm
{
	class any_value: protected variant<VALUES_EVERY>
	{
	public:
		using variant::variant;
		
		using variant::operator=;
		
		using variant::emplace;
		
		any_value();
		
		any_value(nullptr_t);
		
		any_value(bool value);
		
		any_value(double value);
		
		operator bool();
		
		// Checks if this holds any of the given value types.
		template<typename... V>
		constexpr bool holds() const
		{ return (holds_alternative<V>(self) || ...); }
		
		// Checks if this holds the given value.
		constexpr bool holds(nullptr_t) const
		{ return holds<value::null>(); }
		
		// Checks if this holds the given value.
		constexpr bool holds(bool value) const
		{ return holds<value::boolean>() && as<value::boolean>().value == value; }
		
		// Checks if this holds the given value.
		constexpr bool holds(double value) const
		{ return holds<value::number>() && as<value::number>().value == value; }
		
		// Returns the current value as one of its variants.
		template<typename N>
		N& as()
		{
			// TODO: This should probably throw an exception when it's wrong (does it already?)
			return std::get<N>(self);
		}
		
		// Returns the current value as one of its variants.
		template<typename N>
		const N& as() const { return std::get<N>(self); }
		
		friend any_value operator==(const any_value& lhs, const any_value& rhs);
		
		friend any_value operator!=(const any_value& lhs, const any_value& rhs);
	};
}


#else // HEADER_VM_ANY_VALUE_DEFINED


namespace vm
{
	class any_value;
}


#endif // HEADER_VM_ANY_VALUE_DEFINED