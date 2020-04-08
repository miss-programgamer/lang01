#include "empty.hpp"


#include "tokenizer.hpp"
#include "any_token.hpp"


namespace tokens
{
	bool empty::start_match(const tokenizer& stream, const any_token& prev)
	{
		return false;
	}
		
	bool empty::end_match(const tokenizer& stream, const any_token& prev)
	{
		return true;
	}
	
	ostream& operator<<(ostream& os, const empty& token)
	{
		os << "[" << token.type << "]";
		return os;
	}
}