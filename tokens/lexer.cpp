#include "lexer.hpp"


namespace tokens
{
	lexer::lexer(const string_view& source_name, const vector<string_view>& source_lines, vector<any_token>* tokens):
		source_name(source_name),
		source_lines(&source_lines),
		tokens(tokens)
	{
		cursor_lineindex = 0;
		cursor_charindex = 0;
		cursor_lineindent = 0;
		invalid_count = 0;
	}
	
	lexer::operator bool() const
	{
		return cursor_lineindex < source_lines->size() && cursor_charindex < (*source_lines)[cursor_lineindex].size();
	}
	
	bool lexer::next(any_token& dest)
	{
		if (self && match_any_token<TOKENS_MATCHABLE>(cursor_token))
		{
			dest = cursor_token;
			return true;
		}
		else {
			return false;
		}	
	}
	
	bool lexer::fill()
	{
		for (any_token token; next(token);)
		{
			tokens->push_back(token);
		}
		
		return invalid_count == 0;
	}
	
	bool lexer::lex(const string_view& source_name, const vector<string_view>& source_lines, vector<any_token>& tokens)
	{
		return lexer(source_name, source_lines, &tokens).fill();
	}
}