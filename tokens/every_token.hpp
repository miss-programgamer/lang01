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
	
	
	// Contains an indented line that will be lexed later.
	class upline: public basic_token
	{
	public:
		static constexpr string_view type = "up line";
		
		using basic_token::basic_token;
		
		inline string_view content() const
		{ return source_slice.substr(1, source_slice.size() - 1); }
		
		friend ostream& operator<<(ostream& os, const upline& token);
	};
	
	
	// Signals a new line token with a comment.
	class newline: public basic_token
	{
	public:
		static constexpr string_view type = "new line";
		
		using basic_token::basic_token;
		
		inline bool has_comment() const
		{ return source_slice[0] == ';'; }
		
		inline bool has_linefeed() const
		{ return source_slice[source_slice.size() - 1] == '\n'; }
		
		inline string_view content() const
		{ return has_comment() ? source_slice.substr(1, source_slice.size() - 1 - has_linefeed()) : source_slice.substr(0, 0); }
		
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
		
		inline bool has_closing_quote() const
		{ return source_slice[source_slice.size() - 1] == '"'; }
		
		inline string_view content() const
		{ return source_slice.substr(1, source_slice.size() - 1 - has_closing_quote()); }
		
		friend ostream& operator<<(ostream& os, const quoted_string& token);
	};
	
	
	// Represents a short string token.
	class short_string: public basic_token
	{
	public:
		static constexpr string_view type = "short string";
		
		using basic_token::basic_token;
		
		inline string_view content() const
		{ return source_slice.substr(1, source_slice.size() - 1); }
		
		friend ostream& operator<<(ostream& os, const short_string& token);
	};
	
	
	// Represents a surrounding or separating delimiter.
	class delimiter: public basic_token
	{
	public:
		static constexpr string_view type = "delimiter";
		
		using basic_token::basic_token;
		
		friend ostream& operator<<(ostream& os, const delimiter& token);
	};
	
	
	// Represents an operator.
	class operator_t: public basic_token
	{
	public:
		static constexpr string_view type = "operator";
		
		using basic_token::basic_token;
		
		friend ostream& operator<<(ostream& os, const operator_t& token);
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


#else // HEADER_TOKENS_EVERY_TOKEN_DEFINED


namespace tokens
{
	class empty;
	class upline;
	class newline;
	class identifier;
	class numeric;
	class quoted_string;
	class short_string;
	class delimiter;
	class operator_t;
	class invalid;
}


#endif // HEADER_TOKENS_EVERY_TOKEN_DEFINED