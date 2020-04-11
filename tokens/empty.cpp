#include "empty.hpp"


#include "tokenizer.hpp"
#include "any_token.hpp"


namespace tokens
{
	ostream& operator<<(ostream& os, const empty& token)
	{
		os << "[" << token.type << "]";
		return os;
	}
}