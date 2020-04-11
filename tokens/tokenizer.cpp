#include "tokenizer.hpp"


namespace tokens
{
	tokenizer::tokenizer(const string_view& source_name, const string_view& source_text):
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
		unless (self)
			return false;
		
		do { // try matching tokens until we find one we shouldn't skip.
			match_any_token<TOKENS_MATCHABLE>(cursor_token);
		} while (self && cursor_token.should_skip(flags));
		
		if (!cursor_token.should_skip(flags)) {
			token = cursor_token;
			return true;
		} else {
			return false;
		}
	}
	
	void tokenizer::fill(vector<any_token>& tokens, token_flags flags)
	{
		for (any_token token; next(token, flags);)
			tokens.push_back(token);
		
		// TODO: return false if any invalid tokens matched
	}
}