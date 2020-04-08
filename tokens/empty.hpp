#ifndef HEADER_TOKENS_EMPTY_DEFINED
#define HEADER_TOKENS_EMPTY_DEFINED


#include "../main.hpp"


namespace tokens
{
	class tokenizer;
	
	class any_token;
	
	/**
	 * Signals an empty token.
	 */
	class empty
	{
	public:
		static constexpr string_view type = "empty";
		
		static constexpr string_view source_name = "";
		
		static constexpr string_view source_slice = "";
		
		static constexpr size_t lineno = 0;
		
		static constexpr int lineindent = -1;
		
		static bool start_match(const tokenizer& stream, const any_token& prev);
		
		static bool end_match(const tokenizer& stream, const any_token& prev);
		
		friend ostream& operator<<(ostream& os, const empty& token);
	};
}


#else // HEADER_TOKENS_EMPTY_DEFINED


namespace tokens
{
	class empty;
}


#endif // HEADER_TOKENS_EMPTY_DEFINED