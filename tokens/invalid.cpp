#include "invalid.hpp"


#include "tokenizer.hpp"
#include "any_token.hpp"


namespace tokens
{
	ostream& operator<<(ostream& os, const invalid& token)
	{
		os << "[" << token.type << ": " << token.source_slice << "]";
		return os;
	}
}