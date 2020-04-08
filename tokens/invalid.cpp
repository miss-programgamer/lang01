#include "invalid.hpp"


#include "tokenizer.hpp"
#include "any_token.hpp"


namespace tokens
{
	bool invalid::start_match(tokenizer& stream, const any_token& prev)
	{
		return true;
	}
	
	bool invalid::end_match(tokenizer& stream, const any_token& prev)
	{
		return stream.cursor_index - stream.match_start >= 1;
	}
	
	ostream& operator<<(ostream& os, const invalid& token)
	{
		os << "[" << token.type << "] " << token.source_slice;
		return os;
	}
}