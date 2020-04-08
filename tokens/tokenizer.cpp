#include "tokenizer.hpp"


namespace tokens
{
	tokenizer::tokenizer(const string& source_name, const string& source_text):
		source_name(source_name),
		source_text(source_text)
	{
		cursor_index = 0;
		cursor_lineno = 0;
		cursor_lineindent = 0;
	}
	
	tokenizer::operator bool() const
	{
		return cursor_index < source_text.size();
	}
	
	bool tokenizer::next(any_token& token, token_flags flags)
	{
		if (!self)
			return false;
		
		any_token temp = token;
		do match_any_token<TOKENS_MATCHABLE>(temp);
			while (self && temp.should_skip(flags));
		
		if (!temp.should_skip(flags)) {
			token = temp;
			return true;
		} else {
			return false;
		}
	}
	
	unsigned int tokenizer::cursor_char() const
	{
		return self ? source_text[cursor_index] : '\0';
	}
	
	string_view tokenizer::match_slice() const
	{
		return source_text.substr(match_start, cursor_index - match_start);
	}
}