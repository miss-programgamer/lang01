#ifndef HEADER_TOKENS_LEXER_DEFINED
#define HEADER_TOKENS_LEXER_DEFINED


#include "../main.hpp"
#include "any_token.hpp"


namespace tokens
{
	// Produces tokens from the given source text.
	class lexer
	{
		friend class empty;
		friend class upline;
		friend class newline;
		friend class identifier;
		friend class comment;
		friend class invalid;
		friend class any_token;
		
	protected:
		// the name of the source's source.
		const string_view source_name;
		
		// the source lines that will get tokenized.
		const vector<string_view>* source_lines;
		
		// the vector to fill with tokens.
		vector<any_token>* tokens;
		
		// the index of the current line.
		size_t cursor_lineindex;
		
		// the index of the current character.
		size_t cursor_charindex;
		
		// the indentation level of the current line. (will probably be removed TBH)
		int cursor_lineindent;
		
		// the last token matched by the cursor.
		any_token cursor_token;
		
		// the index of the current match's start.
		size_t match_start;
		
		// the number of invalid tokens encountered while lexing.
		size_t invalid_count;
		
	public:
		// Creates a lexer of the given source text.
		lexer(const string_view& source_name, const vector<string_view>& source_lines, vector<any_token>* tokens);
		
		// Checks if the lexer can still produce tokens.
		operator bool() const;
		
		// Produces the next token and stores it into the given reference.
		// Returns true if next can be called again, otherwise return false.
		bool next(any_token& dest);
		
		// Fills the given vector with tokens by repeatedly calling next.
		bool fill();
		
		// Converts the given source into tokens and places them into the given vector.
		static bool lex(const string_view& source_name, const vector<string_view>& source_lines, vector<any_token>& tokens);
		
	protected:
		// If the cursor position is valid, returns the current line. Otherwise, returns an empty slice.
		inline string_view cursor_line() const
		{ return (cursor_lineindex < source_lines->size()) ? (*source_lines)[cursor_lineindex] : string_view(); }
		
		// If the cursor position is valid, returns the character at that position. Otherwise, returns \0.
		inline codepoint_t cursor_char() const
		{ return self ? cursor_line()[cursor_charindex] : '\0'; }
		
		// Checks if the cursor is a line ending (\n or \0).
		inline bool cursor_is_endline() const
		{ codepoint_t c = cursor_char(); return c == '\n' || c == '\0'; }
		
		// Checks if the cursor is a letter.
		inline bool cursor_is_letter() const
		{ codepoint_t c = cursor_char(); return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
		
		// Checks if the cursor is a letter or underscore.
		inline bool cursor_is_letter_or_underscore() const
		{ return cursor_is_letter() || cursor_char() == '_'; }
		
		// Checks if the cursor is a digit.
		inline bool cursor_is_digit() const
		{ codepoint_t c = cursor_char(); return c >= '0' && c <= '9'; }
		
		// Checks if the cursor is a delimiter.
		inline bool cursor_is_delimiter() const
		{ codepoint_t c = cursor_char(); return c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ',' || c == '.'; }
		
		// Checks if the cursor is a symbol, part of an operator.
		inline bool cursor_is_symbol() const
		{
			codepoint_t c = cursor_char();
			return c == '!' || (c >= '#' && c <= '&') ||
				   c == '*' || c == '+' || c == '-' || c == '/' ||
				   (c >= ':' && c <= '@') || c == '\\' || c == '^' || c == '|' || c == '~';
		}
		
		// Checks if the cursor is either empty space or a tab.
		inline bool cursor_is_whitespace() const
		{  codepoint_t c = cursor_char(); return c == ' ' || c == '\t'; }
		
		// Moves the cursor forward to the next character.
		inline void advance_cursor_char()
		{ ++cursor_charindex; }
		
		// Moves the cursor forward to the next character.
		inline void advance_cursor_line()
		{ ++cursor_lineindex; cursor_charindex = 0; }
		
		// Resets the cursor to the given position.
		inline void reset_cursor(size_t position)
		{ cursor_charindex = position; }
		
		// Starts a match at the cursor.
		inline void start_match()
		{ match_start = cursor_charindex; }
		
		// Returns the size of the current match.
		inline size_t match_size() const
		{ return cursor_charindex - match_start; }
		
		// Returns the string view between the match start and the cursor.
		inline string_view match_slice() const
		{ return cursor_line().substr(match_start, match_size()); }
		
		// Emplaces a match into the given token
		template<typename T>
		inline bool emplace_match(any_token& token, size_t leading_space)
		{ token.emplace<T>(source_name, match_slice(), cursor_lineindex + 1, cursor_lineindent, leading_space); return true; }
		
		// Matches any amount of whitespace and returns that amount.
		inline size_t match_whitespace()
		{
			start_match();
			while (cursor_char() == ' ')
				advance_cursor_char();
			return match_size();
		}
		
		// Generic token matching function. Only its specialisations can be called.
		template<typename T>
		bool match_token(any_token& dest, size_t leading_space);
		
		// Tries to match every given kind of token.
		template<typename... T>
		bool match_any_token(any_token& dest)
		{
			auto leading_space = match_whitespace();
			return (match_token<T>(dest, leading_space) || ...);
		}
		
		// Try matching an up line token.
		template<>
		bool match_token<upline>(any_token& dest, size_t leading_space)
		{
			if (!cursor_token.holds<empty, newline, upline>() || cursor_char() != '\t')
				return false;
			
			start_match();
			while (!cursor_is_endline())
				advance_cursor_char();
			advance_cursor_char();
			emplace_match<upline>(dest, leading_space);
			advance_cursor_line();
			return true;
		}
		
		// Try matching a new line token.
		template<>
		bool match_token<newline>(any_token& dest, size_t leading_space)
		{
			if (cursor_is_endline() || cursor_char() == ';')
			{
				start_match();
				
				if (cursor_char() == ';')
					do advance_cursor_char();
						while (!cursor_is_endline());
				
				advance_cursor_char();
				emplace_match<newline>(dest, leading_space);
				advance_cursor_line();
				return true;
			}
			else {
				return false;
			}
		}
		
		// Try matching an identifier token.
		template<>
		bool match_token<identifier>(any_token& dest, size_t leading_space)
		{
			if (!cursor_is_letter_or_underscore())
				return false;
				
			start_match();
			
			do advance_cursor_char();
				while (cursor_is_letter_or_underscore() || cursor_is_digit());
			
			return emplace_match<identifier>(dest, leading_space);
		}
		
		// Try matching a numeric token.
		template<>
		bool match_token<numeric>(any_token& dest, size_t leading_space)
		{
			if (!cursor_is_digit())
				return false;
				
			start_match();
			
			do advance_cursor_char();
				while (cursor_is_letter_or_underscore() || cursor_is_digit());
			
			return emplace_match<numeric>(dest, leading_space);
		}
		
		// Try matching a quoted string token.
		template<>
		bool match_token<quoted_string>(any_token& dest, size_t leading_space)
		{
			if (cursor_char() != '"')
				return false;
				
			start_match();
			
			do advance_cursor_char();
				while (cursor_char() != '"' && !cursor_is_endline());
			advance_cursor_char();
			
			return emplace_match<quoted_string>(dest, leading_space);
		}
		
		// Try matching a short string token.
		template<>
		bool match_token<short_string>(any_token& dest, size_t leading_space)
		{
			if (cursor_char() != '$')
				return false;
				
			start_match();
			
			do advance_cursor_char();
				while (!cursor_is_whitespace() && !cursor_is_endline());
			
			return emplace_match<short_string>(dest, leading_space);
		}
		
		// Try matching a surrounding delimiter token.
		template<>
		bool match_token<delimiter>(any_token& dest, size_t leading_space)
		{
			if (cursor_is_delimiter())
			{
				start_match();
				advance_cursor_char();
				return emplace_match<delimiter>(dest, leading_space);
			}
			else {
				return false;
			}
		}
		
		// Try matching an operator token.
		template<>
		bool match_token<operator_t>(any_token& dest, size_t leading_space)
		{
			if (!cursor_is_symbol())
				return false;
				
			start_match();
			
			do advance_cursor_char();
				while (cursor_is_symbol());
			
			
			return emplace_match<operator_t>(dest, leading_space);
		}
		
		// Match little a invalid character token, as a fallback.
		template<>
		bool match_token<invalid>(any_token& dest, size_t leading_space)
		{
			++invalid_count;
			start_match();
			advance_cursor_char();
			return emplace_match<invalid>(dest, leading_space);
		}
	};
}


#else // HEADER_TOKENS_LEXER_DEFINED


namespace tokens
{
	class lexer;
}


#endif // HEADER_TOKENS_LEXER_DEFINED