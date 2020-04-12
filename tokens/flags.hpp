#ifndef HEADER_TOKENS_FLAGS_DEFINED
#define HEADER_TOKENS_FLAGS_DEFINED


namespace tokens
{
	enum class token_flags: unsigned
	{
		// Next token can contain any token
		NONE = 0u,
		
		// Next token cannot be a comment
		SKIP_COMMENTS = 1u << 1,
		
		// Next token can only be a token with semantic importance
		ONLY_SEMANTIC = SKIP_COMMENTS
	};

	inline token_flags operator|(token_flags lhs, token_flags rhs)
	{ return token_flags(unsigned(lhs)|unsigned(rhs)); }

	inline token_flags operator&(token_flags lhs, token_flags rhs)
	{ return token_flags(unsigned(lhs)&unsigned(rhs)); }
}


#endif // HEADER_TOKENS_ANY_TOKEN_DEFINED