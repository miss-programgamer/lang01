#include "comment.hpp"


#include "tokenizer.hpp"
#include "any_token.hpp"


namespace tokens
{
	bool comment::start_match(tokenizer& stream, const any_token& prev)
	{
		return stream.cursor_char() == ';';
	}
	
	bool comment::end_match(tokenizer& stream, const any_token& prev)
	{
		return stream.cursor_char() == '\n';
	}
	
	ostream& operator<<(ostream& os, const comment& token)
	{
		os << "[" << token.type << "] " << token.source_slice;
		return os;
	}
}