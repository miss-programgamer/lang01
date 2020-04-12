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
	
	ostream& operator<<(ostream& os, const indentation& token)
	{
		os << "[" << token.type << ": " << token.source_slice.size() << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const newline& token)
	{
		os << "[" << token.type << ": \\n]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const identifier& token)
	{
		os << "[" << token.type << ": " << token.source_slice << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const numeric& token)
	{
		os << "[" << token.type << ": " << token.source_slice << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const quoted_string& token)
	{
		os << "[" << token.type << ": " << token.source_slice << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const short_string& token)
	{
		os << "[" << token.type << ": " << token.source_slice << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const comment& token)
	{
		os << "[" << token.type << ": " << token.source_slice << "]";
		return os;
	}
	
	ostream& operator<<(ostream& os, const invalid& token)
	{
		os << "[" << token.type << ": " << token.source_slice << "]";
		return os;
	}
}