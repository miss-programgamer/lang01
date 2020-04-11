#ifndef HEADER_TOKENS_ANY_TOKEN_DEFINED
#define HEADER_TOKENS_ANY_TOKEN_DEFINED


#include "../main.hpp"
#include "flags.hpp"
#include "empty.hpp"
#include "linestart.hpp"
#include "lineend.hpp"
#include "identifier.hpp"
#include "whitespace.hpp"
#include "comment.hpp"
#include "invalid.hpp"


// Comma-separated list of all valid token types
#define TOKENS_EVERY empty, linestart, lineend, identifier, whitespace, comment, invalid

// Comma-separated list of all tokens that can be matched
#define TOKENS_MATCHABLE linestart, lineend, identifier, whitespace, comment, invalid


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
		
		// Based on the given flags, checks if the held token should be skipped.
		bool should_skip(token_flags flags) const;
		
		// Returns the held token's name.
		string_view name() const;
		
		// Returns the name of the source where the held token was matched.
		string_view source_name() const;
		
		// Returns the section of the source text where the held token was matched.
		string_view source_slice() const;
		
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