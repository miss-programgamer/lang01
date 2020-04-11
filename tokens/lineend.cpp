#include "lineend.hpp"


#include "tokenizer.hpp"
#include "any_token.hpp"


namespace tokens
{
	ostream& operator<<(ostream& os, const lineend& token)
	{
		os << "[" << token.type << "]";
		return os;
	}
}