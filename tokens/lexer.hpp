#ifndef HEADER_TOKENS_LEXER_DEFINED
#define HEADER_TOKENS_LEXER_DEFINED


#include "../main.hpp"
#include "flags.hpp"
#include "any_token.hpp"


namespace tokens
{
	// Produces tokens from the given source text.
	class lexer
	{
		friend class empty;
		friend class indentation;
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
		
	public:
		// Creates a lexer of the given source text.
		lexer(const string_view& source_name, const vector<string_view>& source_lines);
		
		// Checks if the lexer can still produce tokens.
		operator bool() const;
		
		// Produces the next token and stores it into the given reference.
		// Returns true if next can be called again, otherwise return false.
		bool next(any_token& token, token_flags flags = token_flags::NONE);
		
		// Fills the given vector with tokens by repeatedly calling next.
		void fill(vector<any_token>& tokens, token_flags flags = token_flags::NONE);
		
	protected:
		// If the cursor position is valid, returns the current line. Otherwise, returns an empty slice.
		inline string_view cursor_line() const
		{ return (cursor_lineindex < source_lines->size()) ? (*source_lines)[cursor_lineindex] : string_view(); }
		
		// If the cursor position is valid, returns the character at that position. Otherwise, returns \0.
		inline unsigned int cursor_char() const
		{ return self ? cursor_line()[cursor_charindex] : '\0'; }
		
		// Checks if the cursor is a line ending (\n or \0).
		inline bool cursor_is_endline() const
		{ int c = cursor_char(); return c == '\n' || c == '\0'; }
		
		// Checks if the cursor is a letter.
		inline bool cursor_is_letter() const
		{ int c = cursor_char(); return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
		
		// Checks if the cursor is a letter or underscore.
		inline bool cursor_is_letter_or_underscore() const
		{ return cursor_is_letter() || cursor_char() == '_'; }
		
		// Checks if the cursor is a number.
		inline bool cursor_is_number() const
		{ int c = cursor_char(); return c >= '0' && c <= '9'; }
		
		// Checks if the cursor is either empty space or a tab.
		inline bool cursor_is_whitespace() const
		{  int c = cursor_char(); return c == ' ' || c == '\t'; }
		
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
		{
			auto line = cursor_line();
			return cursor_line().substr(match_start, match_size());
		}
		
		// Emplaces a match into the given token
		template<typename T>
		inline bool emplace_match(any_token& token, size_t leading_space)
		{ token.emplace<T>(source_name, match_slice(), cursor_lineindex + 1, cursor_lineindent, leading_space); return true; }
		
		// Generic token matching function. Only its specialisations can be called.
		template<typename T>
		bool match_token(any_token& token, size_t leading_space);
		
		// Matches any amount of whitespace and returns that amount.
		inline size_t match_whitespace()
		{
			start_match();
			while (cursor_char() == ' ')
				advance_cursor_char();
			return match_size();
		}
		
		// Tries to match every given kind of token.
		template<typename... T>
		bool match_any_token(any_token& token)
		{
			auto leading_space = match_whitespace();
			return (match_token<T>(token, leading_space) || ...);
		}
		
		// Try matching a linestart token.
		template<>
		bool match_token<indentation>(any_token& token, size_t leading_space)
		{
			if (!cursor_token.holds<empty, newline>())
				return false;
			
			start_match();
			while (cursor_char() == '\t')
				advance_cursor_char();
			return emplace_match<indentation>(token, leading_space);
		}
		
		// Try matching a lineend token.
		template<>
		bool match_token<newline>(any_token& token, size_t leading_space)
		{
			if (cursor_char() == '\n') {
				start_match();
				advance_cursor_char();
				emplace_match<newline>(token, leading_space);
				advance_cursor_line();
				return true;
			} else {
				return false;
			}
		}
		
		// Try matching an identifier token.
		template<>
		bool match_token<identifier>(any_token& token, size_t leading_space)
		{
			if (!cursor_is_letter_or_underscore())
				return false;
				
			start_match();
			advance_cursor_char();
			while (cursor_is_letter_or_underscore())
				advance_cursor_char();
			return emplace_match<identifier>(token, leading_space);
		}
		
		// Try matching a numeric token.
		template<>
		bool match_token<numeric>(any_token& token, size_t leading_space)
		{
			if (!cursor_is_number())
				return false;
				
			start_match();
			advance_cursor_char();
			while (cursor_is_number())
				advance_cursor_char();
			return emplace_match<numeric>(token, leading_space);
		}
		
		// Try matching a quoted string token.
		template<>
		bool match_token<quoted_string>(any_token& token, size_t leading_space)
		{
			if (cursor_char() != '"')
				return false;
				
			start_match();
			advance_cursor_char();
			until (cursor_char() == '"' || cursor_is_endline())
				advance_cursor_char();
			advance_cursor_char();
			return emplace_match<quoted_string>(token, leading_space);
		}
		
		// Try matching a short string token.
		template<>
		bool match_token<short_string>(any_token& token, size_t leading_space)
		{
			if (cursor_char() != '$')
				return false;
				
			start_match();
			advance_cursor_char();
			until (cursor_is_whitespace() || cursor_is_endline())
				advance_cursor_char();
			return emplace_match<short_string>(token, leading_space);
		}
		
		// Try matching a comment token.
		template<>
		bool match_token<comment>(any_token& token, size_t leading_space)
		{
			if (cursor_char() != ';')
				return false;
			
			start_match();
			advance_cursor_char();
			until (cursor_is_endline())
				advance_cursor_char();
			return emplace_match<comment>(token, leading_space);
		}
		
		// Match little a invalid character token, as a fallback.
		template<>
		bool match_token<invalid>(any_token& token, size_t leading_space)
		{
			start_match();
			advance_cursor_char();
			return emplace_match<invalid>(token, leading_space);
		}
	};
}


#else // HEADER_TOKENS_LEXER_DEFINED


namespace tokens
{
	class lexer;
}


#endif // HEADER_TOKENS_LEXER_DEFINED