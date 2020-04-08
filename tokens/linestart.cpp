#include "linestart.hpp"


#include "tokenizer.hpp"
#include "any_token.hpp"


namespace tokens
{
	bool linestart::start_match(tokenizer& stream, const any_token& prev)
	{
		if (prev.holds<empty, lineend>()) {
			++stream.cursor_lineno;
			stream.cursor_lineindent = 0;
			return true;
		} else {
			return false;
		}
	}
		
	bool linestart::end_match(tokenizer& stream, const any_token& prev)
	{
		if (stream.cursor_char() == '\t') {
			++stream.cursor_lineindent;
			return false;
		} else {
			return true;
		}
	}
	
	ostream& operator<<(ostream& os, const linestart& token)
	{
		os << "[" << token.type << "] " << token.source_slice.size();
		return os;
	}
}