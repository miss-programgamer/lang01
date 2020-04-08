#ifndef HEADER_TOKENS_COMMENT_DEFINED
#define HEADER_TOKENS_COMMENT_DEFINED


#include "../main.hpp"
#include "basic_token.hpp"


namespace tokens
{
	class tokenizer;
	
	class any_token;
	
	/**
	 * Represents a single-line comment.
	 */
	class comment: public basic_token
	{
	public:
		static constexpr string_view type = "comment";
		
		using basic_token::basic_token;
		
		static bool start_match(tokenizer& stream, const any_token& prev);
		
		static bool end_match(tokenizer& stream, const any_token& prev);
		
		friend ostream& operator<<(ostream& os, const comment& token);
	};
}


#else // HEADER_TOKENS_COMMENT_DEFINED


namespace tokens
{
	class comment;
}


#endif // HEADER_TOKENS_COMMENT_DEFINED