#include "lexer.hpp"


namespace tokens
{
	lexer::lexer(const string_view& source_name, const vector<string_view>& source_lines):
		source_name(source_name),
		source_lines(&source_lines)
	{
		cursor_lineindex = 0;
		cursor_charindex = 0;
		cursor_lineindent = 0;
	}
	
	lexer::operator bool() const
	{
		return cursor_lineindex < source_lines->size() && cursor_charindex < (*source_lines)[cursor_lineindex].size();
	}
	
	bool lexer::next(any_token& token, token_flags flags)
	{
		unless (self) return false;
		
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
	
	void lexer::fill(vector<any_token>& tokens, token_flags flags)
	{
		for (any_token token; next(token, flags);)
			tokens.push_back(token);
		
		// TODO: return false if any invalid tokens matched
	}
}