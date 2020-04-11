#include "linestart.hpp"


#include "tokenizer.hpp"
#include "any_token.hpp"


namespace tokens
{
	ostream& operator<<(ostream& os, const linestart& token)
	{
		os << "[" << token.type << ": indent " << token.source_slice.size() << "]";
		return os;
	}
}