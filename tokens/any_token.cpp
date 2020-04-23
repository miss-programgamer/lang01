#include "any_token.hpp"


namespace tokens
{
	string_view any_token::name() const
	{
		return visit([](auto&& token) {
			return token.type;
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
	
	size_t any_token::leading_space() const
	{
		return visit([](auto&& token) -> size_t {
			return token.leading_space;
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
	
	bool operator==(const any_token& lhs, const any_token& rhs)
	{
		// return false;
		// return (any_token::variant&)(lhs) == (any_token::variant&)(rhs);
		return
		(
			lhs.name()          == rhs.name() &&
			lhs.source_slice()  == rhs.source_slice() &&
			lhs.lineno()        == rhs.lineno() &&
			lhs.lineindent()    == rhs.lineindent() &&
			lhs.leading_space() == rhs.leading_space()
		);
	}
	
	bool operator!=(const any_token& lhs, const any_token& rhs)
	{
		// return false;
		return !(lhs == rhs);
	}
}