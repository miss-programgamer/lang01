#ifndef HEADER_TOKENS_EVERY_TOKEN_DEFINED
#define HEADER_TOKENS_EVERY_TOKEN_DEFINED


#include "../main.hpp"
#include "basic_token.hpp"


namespace tokens
{
	// Signals an empty token.
	class empty: public basic_token
	{
	public:
		static constexpr string_view type = "empty";
		
		empty() noexcept;
		
		friend ostream& operator<<(ostream& os, const empty& token);
	};
	
	
	// Signals a line start token.
	class indentation: public basic_token
	{
	public:
		static constexpr string_view type = "indentation";
		
		using basic_token::basic_token;
		
		friend ostream& operator<<(ostream& os, const indentation& token);
	};
	
	
	// Signals a line end token.
	class newline: public basic_token
	{
	public:
		static constexpr string_view type = "new line";
		
		using basic_token::basic_token;
		
		friend ostream& operator<<(ostream& os, const newline& token);
	};
	
	
	// Represents an identifier token.
	class identifier: public basic_token
	{
	public:
		static constexpr string_view type = "identifier";
		
		using basic_token::basic_token;
		
		friend ostream& operator<<(ostream& os, const identifier& token);
	};
	
	
	// Represents a numeric token.
	class numeric: public basic_token
	{
	public:
		static constexpr string_view type = "numeric";
		
		using basic_token::basic_token;
		
		friend ostream& operator<<(ostream& os, const numeric& token);
	};
	
	
	// Represents a quoted string token.
	class quoted_string: public basic_token
	{
	public:
		static constexpr string_view type = "quoted string";
		
		using basic_token::basic_token;
		
		friend ostream& operator<<(ostream& os, const quoted_string& token);
	};
	
	
	// Represents a short string token.
	class short_string: public basic_token
	{
	public:
		static constexpr string_view type = "short string";
		
		using basic_token::basic_token;
		
		friend ostream& operator<<(ostream& os, const short_string& token);
	};
	
	
	// Represents a comment.
	class comment: public basic_token
	{
	public:
		static constexpr string_view type = "comment";
		
		using basic_token::basic_token;
		
		friend ostream& operator<<(ostream& os, const comment& token);
	};
	
	
	// Represents an invalid character.
	class invalid: public basic_token
	{
	public:
		static constexpr string_view type = "invalid";
		
		using basic_token::basic_token;
		
		friend ostream& operator<<(ostream& os, const invalid& token);
	};
}


#else // HEADER_TOKENS_LINESTART_DEFINED


namespace tokens
{
	class empty;
	class linestart;
	class lineend;
	class identifier;
	class numeric;
	class quoted_string;
	class short_string;
	class comment;
	class invalid;
}


#endif // HEADER_TOKENS_EVERY_TOKEN_DEFINED