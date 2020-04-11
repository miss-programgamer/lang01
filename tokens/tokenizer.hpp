#ifndef HEADER_TOKENS_TOKENIZER_DEFINED
#define HEADER_TOKENS_TOKENIZER_DEFINED


#include "../main.hpp"
#include "flags.hpp"
#include "any_token.hpp"


namespace tokens
{
	// Produces tokens from the given source text.
	class tokenizer
	{
		friend class empty;
		friend class linestart;
		friend class lineend;
		friend class identifier;
		friend class whitespace;
		friend class comment;
		friend class invalid;
		friend class any_token;
		
	protected:
		const string_view source_name;
		
		const string_view source_text;
		
		size_t cursor_index;
		
		size_t cursor_lineno;
		
		int cursor_lineindent;
		
		any_token cursor_token;
		
		size_t match_start;
		
	public:
		// Creates a tokenizer of the given source text.
		tokenizer(const string_view& source_name, const string_view& source_text);
		
		// Checks if the tokenizer has reached its end.
		operator bool() const;
		
		// Produces the next token and stores it into the given reference.
		// Returns true if next can be called again, otherwise return false.
		bool next(any_token& token, token_flags flags = token_flags::NONE);
		
		// Fills the given vector with tokens by repeatedly calling next.
		void fill(vector<any_token>& tokens, token_flags flags = token_flags::NONE);
		
	protected:
		// If the cursor position is valid, returns the character at that position. Otherwise, returns \0.
		inline unsigned int cursor_char() const
		{ return self ? source_text[cursor_index] : '\0'; }
		
		// Checks if the cursor is a tab.
		inline bool cursor_is_tab() const
		{ return cursor_char() == '\t'; }
		
		// Checks if the cursor is a newline \n.
		inline bool cursor_is_newline() const
		{ return cursor_char() == '\n'; }
		
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
		{ int c = cursor_char(); return c == ' ' || c == '\t'; }
		
		// Moves the cursor forward to the next character.
		inline void advance_cursor()
		{ ++cursor_index; }
		
		// Resets the cursor to the given position.
		inline void reset_cursor(size_t position)
		{ cursor_index = position; }
		
		// Starts a match at the cursor.
		inline void start_match()
		{ match_start = cursor_index; }
		
		// Returns the string view between the match start and the cursor.
		inline string_view match_slice() const
		{ return source_text.substr(match_start, cursor_index - match_start); }
		
		// Emplaces a match into the given token
		template<typename T>
		inline bool emplace_match(any_token& token)
		{ token.emplace<T>(source_name, match_slice(), cursor_lineno, cursor_lineindent); return true; }
		
		// Generic token matching function. Only its specialisations can be called.
		template<typename T>
		bool match_token(any_token& token);
		
		// Tries to match every given kind of token.
		template<typename... T>
		bool match_any_token(any_token& token)
		{
			return (match_token<T>(token) || ...);
		}
		
		// Try matching a linestart token.
		template<>
		bool match_token<linestart>(any_token& token)
		{
			if (!token.holds<empty, lineend>())
				return false;
			
			start_match();
			while (cursor_is_tab())
				advance_cursor();
			
			return emplace_match<linestart>(token);
		}
		
		// Try matching a lineend token.
		template<>
		bool match_token<lineend>(any_token& token)
		{
			if (cursor_is_newline()) {
				start_match();
				advance_cursor();
				return emplace_match<lineend>(token);
			} else {
				return false;
			}
		}
		
		// Try matching an identifier token.
		template<>
		bool match_token<identifier>(any_token& token)
		{
			if (!cursor_is_letter_or_underscore())
				return false;
			
			start_match();
			while (cursor_is_letter_or_underscore())
				advance_cursor();
			
			return emplace_match<identifier>(token);
		}
		
		// Try matching a whitespace token.
		template<>
		bool match_token<whitespace>(any_token& token)
		{
			if (!cursor_is_whitespace())
				return false;
			
			start_match();
			while (cursor_is_whitespace())
				advance_cursor();
			
			return emplace_match<whitespace>(token);
		}
		
		// Try matching a comment token.
		template<>
		bool match_token<comment>(any_token& token)
		{
			if (cursor_char() != ';')
				return false;
			
			start_match();
			until (cursor_is_newline())
				advance_cursor();
			
			return emplace_match<comment>(token);
		}
		
		// Match little a invalid character token, as a fallback.
		template<>
		bool match_token<invalid>(any_token& token)
		{
			start_match();
			advance_cursor();
			return emplace_match<invalid>(token);
		}
	};
}


#else // HEADER_TOKENS_TOKENIZER_DEFINED


namespace tokens
{
	class tokenizer;
}


#endif // HEADER_TOKENS_TOKENIZER_DEFINED