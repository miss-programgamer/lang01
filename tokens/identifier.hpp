#ifndef HEADER_TOKENS_IDENTIFIER_DEFINED
#define HEADER_TOKENS_IDENTIFIER_DEFINED


#include "../main.hpp"
#include "basic_token.hpp"


namespace tokens
{
	class tokenizer;
	
	class any_token;
	
	/**
	 * Signals an empty token.
	 */
	class identifier: public basic_token
	{
	public:
		static constexpr string_view type = "identifier";
		
		using basic_token::basic_token;
		
		static bool start_match(tokenizer& stream, const any_token& prev);
		
		static bool end_match(tokenizer& stream, const any_token& prev);
		
		friend ostream& operator<<(ostream& os, const identifier& token);
	};
}


#else // HEADER_TOKENS_IDENTIFIER_DEFINED


namespace tokens
{
	class identifier;
}


#endif // HEADER_TOKENS_IDENTIFIER_DEFINED