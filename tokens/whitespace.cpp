#include "whitespace.hpp"


#include "tokenizer.hpp"
#include "any_token.hpp"


namespace tokens
{
	bool whitespace::start_match(tokenizer& stream, const any_token& prev)
	{
		return stream.cursor_char() == ' ';
	}
	
	bool whitespace::end_match(tokenizer& stream, const any_token& prev)
	{
		return stream.cursor_char() != ' ';
	}
	
	ostream& operator<<(ostream& os, const whitespace& token)
	{
		os << "[" << token.type << "] " << token.source_slice.size();
		return os;
	}
}