#include "every_token.hpp"


namespace tokens
{
	empty::empty() noexcept:
		basic_token("", "", 0, -1, 0)
	{}
	
	ostream& operator<<(ostream& os, const empty& token)
	{
		os << "[" << token.type << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const upline& token)
	{
		os << "[" << token.type << ": " << token.content() << " ]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const newline& token)
	{
		if (token.has_comment()) {
			os << "[" << token.type << ":" << token.content() << " ]";
		} else {
			os << "[" << token.type << "]";
		}
		return os;
	}
	
	ostream& operator<<(ostream& os, const identifier& token)
	{
		os << "[" << token.type << ": " << token.content() << " ]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const numeric& token)
	{
		os << "[" << token.type << ": " << token.content() << " ]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const quoted_string& token)
	{
		os << "[" << token.type << ": " << token.content() << " ]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const short_string& token)
	{
		os << "[" << token.type << ": " << token.content() << " ]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const delimiter& token)
	{
		os << "[" << token.type << ": " << token.content() << " ]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const operator_t& token)
	{
		os << "[" << token.type << ": " << token.content() << " ]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const invalid& token)
	{
		os << "[" << token.type << ": " << token.content() << " ]";
		return os;
	}
}