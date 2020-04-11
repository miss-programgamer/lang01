#ifndef HEADER_TOKENS_INVALID_DEFINED
#define HEADER_TOKENS_INVALID_DEFINED


#include "../main.hpp"
#include "basic_token.hpp"


namespace tokens
{
	class tokenizer;
	
	class any_token;
	
	/**
	 * Represents an invalid character.
	 */
	class invalid: public basic_token
	{
	public:
		static constexpr string_view type = "invalid";
		
		using basic_token::basic_token;
		
		friend ostream& operator<<(ostream& os, const invalid& token);
	};
}


#else // HEADER_TOKENS_INVALID_DEFINED


namespace tokens
{
	class invalid;
}


#endif // HEADER_TOKENS_INVALID_DEFINED