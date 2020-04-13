#ifndef HEADER_TOKENS_ANY_TOKEN_DEFINED
#define HEADER_TOKENS_ANY_TOKEN_DEFINED


#include "../main.hpp"
#include "every_token.hpp"


// Comma-separated list of all valid token types
#define TOKENS_EVERY empty, indentation, newline, identifier, numeric, quoted_string, short_string, delimiter, operator_t, invalid

// Comma-separated list of all tokens that can be matched
#define TOKENS_MATCHABLE indentation, newline, identifier, numeric, quoted_string, short_string, delimiter, operator_t, invalid


namespace tokens
{
	// A custom variant type that can hold an empty token or any matchable token.
	class any_token: protected variant<TOKENS_EVERY>
	{
	public:
		using variant::variant;
		
		using variant::emplace;
		
		using variant::operator=;
		
		// Checks if this holds any of the given token type.
		template<typename... T>
		constexpr bool holds() const
		{ return (holds_alternative<T>(self) || ...); }
		
		// Applies the given visitor object to the held token.
		template<typename V>
		decltype(auto) visit(V&& visitor)
		{ return std::visit(visitor, (variant&)self); }
		
		// Applies the given visitor object to the held token.
		template<typename V>
		decltype(auto) visit(V&& visitor) const
		{ return std::visit(visitor, (const variant&)self); }
		
		// Returns the held token's name.
		string_view name() const;
		
		// Returns the name of the source text where the held token was matched.
		string_view source_name() const;
		
		// Returns the slice of source text obtained when the held token was matched.
		string_view source_slice() const;
		
		// Returns the contents of the token. (Not always the same as source_slice)
		string_view content() const;
		
		// Returns the line number where the held token was matched.
		size_t lineno() const;
		
		// Returns the indentation of the line where the held token was matched.
		int lineindent() const;
		
		// Prints the token's text to an ostream.
		friend ostream& operator<<(ostream& os, const any_token& token);
	};
}


#else // HEADER_TOKENS_ANY_TOKEN_DEFINED


namespace tokens
{
	class any_token;
}


#endif // HEADER_TOKENS_ANY_TOKEN_DEFINED