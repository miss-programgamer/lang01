#ifndef HEADER_VM_ANY_VALUE_DEFINED
#define HEADER_VM_ANY_VALUE_DEFINED


#include "../libs.hpp"
#include "every_value.hpp"


#define VALUES_EVERY null, boolean, number, text


namespace vm
{
	class any_value: protected variant<VALUES_EVERY>
	{
	public:
		using variant::variant;
		
		using variant::operator=;
		
		using variant::emplace;
		
		operator bool();
		
		// Checks if this holds any of the given value types.
		template<typename... V>
		constexpr bool holds() const
		{ return (holds_alternative<V>(self) || ...); }
		
		// Checks if this holds the given value.
		constexpr bool holds(nullptr_t) const
		{ return holds<null>(); }
		
		// Checks if this holds the given value.
		constexpr bool holds(bool value) const
		{ return holds<boolean>() && as<boolean>().value == value; }
		
		// Checks if this holds the given value.
		constexpr bool holds(double value) const
		{ return holds<number>() && as<number>().value == value; }
		
		// Returns the current value as one of its variants.
		template<typename N>
		N& as() { return std::get<N>(self); }
		
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