#include "lineend.hpp"


#include "tokenizer.hpp"
#include "any_token.hpp"


namespace tokens
{
	bool lineend::start_match(tokenizer& stream, const any_token& prev)
	{
		return stream.cursor_char() == '\n' || stream.cursor_char() == '\0';
	}
	
	bool lineend::end_match(tokenizer& stream, const any_token& prev)
	{
		return stream.cursor_index - stream.match_start >= 1;
	}
	
	ostream& operator<<(ostream& os, const lineend& token)
	{
		os << "[" << token.type << "]";
		return os;
	}
}