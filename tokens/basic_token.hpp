#ifndef HEADER_TOKENS_BASIC_TOKEN_DEFINED
#define HEADER_TOKENS_BASIC_TOKEN_DEFINED


#include "../main.hpp"


namespace tokens
{
	class any_token;
	
	// The type from which every token inherits. Useless when used on its own.
	class basic_token
	{
		friend class any_token;
		
	protected:
		string_view source_name;
		
		string_view source_slice;
		
		size_t lineno;
		
		int lineindent;
		
		size_t leading_space;
		
	public:
		basic_token(const string_view source_name, const string_view source_slice, size_t lineno, int lineindent, size_t leading_space) noexcept;
	};
}


#else // HEADER_TOKENS_BASIC_TOKEN_DEFINED


namespace tokens
{
	class basic_token;
}


#endif // HEADER_TOKENS_BASIC_TOKEN_DEFINED