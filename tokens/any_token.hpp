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
	class any_token: protected variant<TOKENS_EVERY>
	{
	public:
		using variant = variant;
		
		using variant::variant;
		
		using variant::emplace;
		
		using variant::operator=;
		
		template<typename... T>
		constexpr bool holds() const
		{
			return (holds_alternative<T>(self) || ...);
		}
		
		bool should_skip(token_flags flags);
		
		string_view name();
		
		string_view source_name();
		
		string_view source_slice();
		
		size_t lineno();
		
		int lineindent();
		
		friend ostream& operator<<(ostream& os, const any_token& token);
	};
}


#else // HEADER_TOKENS_ANY_TOKEN_DEFINED


namespace tokens
{
	class any_token;
}


#endif // HEADER_TOKENS_ANY_TOKEN_DEFINED