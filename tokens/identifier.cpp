#include "identifier.hpp"


#include "tokenizer.hpp"
#include "any_token.hpp"


namespace tokens
{
	bool identifier::start_match(tokenizer& stream, const any_token& prev)
	{
		const auto c = stream.cursor_char();
		return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_';
	}
	
	bool identifier::end_match(tokenizer& stream, const any_token& prev)
	{
		const auto c = stream.cursor_char();
		return !(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_');
	}
	
	ostream& operator<<(ostream& os, const identifier& token)
	{
		os << "[" << token.type << "] " << token.source_slice;
		return os;
	}
}