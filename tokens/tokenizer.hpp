#ifndef HEADER_TOKENS_TOKENSTREAM_DEFINED
#define HEADER_TOKENS_TOKENSTREAM_DEFINED


#include "../main.hpp"
#include "flags.hpp"
#include "any_token.hpp"


namespace tokens
{
	/**
	 * Produces a stream of tokens from the given source text.
	 */
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
		
		size_t match_start;
		
	public:
		/**
		 * Creates a tokenizer for the given source text.
		 */
		tokenizer(const string& source_name, const string& source_text);
		
		/**
		 * Checks if the stream has reached its end.
		 */
		operator bool() const;
		
		/**
		 * Produces the next token and stores it into the token passed to this function.
		 * Assumes the given token is the same as the previous produced token.
		 * Returns true if a token was matched and stored into the given reference, otherwise returns false.
		 */
		bool next(any_token& token, token_flags flags = token_flags::NONE);
		
	protected:
		unsigned int cursor_char() const;
		
		string_view match_slice() const;
		
		template<typename T>
		bool match_token(any_token& token)
		{
			if (T::start_match(self, token))
			{
				match_start = cursor_index;
				while(!T::end_match(self, token))
					++cursor_index;
				token.emplace<T>(source_name, match_slice(), cursor_lineno, cursor_lineindent);
				return true;
			}
			else
			{
				return false;
			}
		}
		
		template<typename... T>
		bool match_any_token(any_token& token)
		{
			return (match_token<T>(token) || ...);
		}
	};
}


#else // HEADER_TOKENS_TOKENSTREAM_DEFINED


namespace tokens
{
	class tokenizer;
}


#endif // HEADER_TOKENS_TOKENSTREAM_DEFINED