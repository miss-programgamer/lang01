#include "whitespace.hpp"


#include "tokenizer.hpp"
#include "any_token.hpp"


namespace tokens
{
	ostream& operator<<(ostream& os, const whitespace& token)
	{
		os << "[" << token.type << ": size " << token.source_slice.size() << "]";
		return os;
	}
}