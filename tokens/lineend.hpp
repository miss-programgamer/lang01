#ifndef HEADER_TOKENS_LINEEND_DEFINED
#define HEADER_TOKENS_LINEEND_DEFINED


#include "../main.hpp"
#include "basic_token.hpp"


namespace tokens
{
	class tokenizer;
	
	class any_token;
	
	/**
	 * Signals an lineend token.
	 */
	class lineend: public basic_token
	{
	public:
		static constexpr string_view type = "lineend";
		
		using basic_token::basic_token;
		
		static bool start_match(tokenizer& stream, const any_token& prev);
		
		static bool end_match(tokenizer& stream, const any_token& prev);
		
		friend ostream& operator<<(ostream& os, const lineend& token);
	};
}


#else // HEADER_TOKENS_LINEEND_DEFINED


namespace tokens
{
	class lineend;
}


#endif // HEADER_TOKENS_LINEEND_DEFINED