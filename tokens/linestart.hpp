#ifndef HEADER_TOKENS_LINESTART_DEFINED
#define HEADER_TOKENS_LINESTART_DEFINED


#include "../main.hpp"
#include "basic_token.hpp"


namespace tokens
{
	class tokenizer;
	
	class any_token;
	
	/**
	 * Signals an linestart token.
	 */
	class linestart: public basic_token
	{
	public:
		static constexpr string_view type = "linestart";
		
		using basic_token::basic_token;
		
		friend ostream& operator<<(ostream& os, const linestart& token);
	};
}


#else // HEADER_TOKENS_LINESTART_DEFINED


namespace tokens
{
	class linestart;
}


#endif // HEADER_TOKENS_LINESTART_DEFINED