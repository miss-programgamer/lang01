#include "any_token.hpp"


namespace tokens
{
	bool any_token::should_skip(token_flags flags) const
	{
		return (flags & token_flags::SKIP_COMMENTS) != token_flags::NONE && holds<comment>();
	}
	
	string_view any_token::name() const
	{
		return visit([](auto&& token) {
			return token.type;
		});
	}
	
	string_view any_token::source_name() const
	{
		return visit([](auto&& token) -> string_view {
			return token.source_name;
		});
	}
	
	string_view any_token::source_slice() const
	{
		return visit([](auto&& token) -> string_view {
			return token.source_slice;
		});
	}
	
	size_t any_token::lineno() const
	{
		return visit([](auto&& token) -> size_t {
			return token.lineno;
		});
	}
	
	int any_token::lineindent() const
	{
		return visit([](auto&& token) -> int {
			return token.lineindent;
		});
	}
	
	ostream& operator<<(ostream& os, const any_token& token)
	{
		token.visit([&os](auto&& token) { os << token; });
		return os;
	}
}