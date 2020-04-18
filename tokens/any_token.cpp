#include "any_token.hpp"


namespace tokens
{
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
	
	string_view any_token::content() const
	{
		return visit([](auto&& token) -> string_view {
			return token.content();
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
	
	ostream& operator<<(ostream& os, const vector<any_token>& tokens)
	{
		for (auto token: tokens)
		{
			cout << token << "\n";
		}
		return os;
	}
}