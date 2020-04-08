#include "any_token.hpp"


namespace tokens
{
	bool any_token::should_skip(token_flags flags)
	{
		return ((flags & token_flags::SKIP_WHITESPACE) != token_flags::NONE && holds<whitespace>() ||
				(flags & token_flags::SKIP_COMMENTS)   != token_flags::NONE && holds<comment>());
	}
	
	string_view any_token::name()
	{
		return visit([](auto&& token)->string_view{
			return token.type;
		}, (variant&)self);
	}
	
	string_view any_token::source_name()
	{
		return visit([](auto&& token)->string_view{
			return token.source_name;
		}, (variant&)self);
	}
	
	string_view any_token::source_slice()
	{
		return visit([](auto&& token)->string_view{
			return token.source_slice;
		}, (variant&)self);
	}
	
	size_t any_token::lineno()
	{
		return visit([](auto&& token)->size_t{
			return token.lineno;
		}, (variant&)self);
	}
	
	int any_token::lineindent()
	{
		return visit([](auto&& token)->int{
			return token.lineindent;
		}, (variant&)self);
	}
	
	ostream& operator<<(ostream& os, const any_token& token)
	{
		visit([&os](auto&& token){ os << token; }, (const any_token::variant&)token);
		return os;
	}
}