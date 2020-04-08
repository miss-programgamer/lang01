#ifndef HEADER_TOKENS_WHITESPACE_DEFINED
#define HEADER_TOKENS_WHITESPACE_DEFINED


#include "../main.hpp"
#include "basic_token.hpp"


namespace tokens
{
	class tokenizer;
	
	class any_token;
	
	/**
	 * Matches arbitrary non-leading whitespace.
	 */
	class whitespace: public basic_token
	{
	public:
		static constexpr string_view type = "whitespace";
		
		using basic_token::basic_token;
		
		static bool start_match(tokenizer& stream, const any_token& prev);
		
		static bool end_match(tokenizer& stream, const any_token& prev);
		
		friend ostream& operator<<(ostream& os, const whitespace& token);
	};
}


#else // HEADER_TOKENS_WHITESPACE_DEFINED


namespace tokens
{
	class whitespace;
}


#endif // HEADER_TOKENS_WHITESPACE_DEFINED