#include "basic_token.hpp"


namespace tokens
{
	basic_token::basic_token(const string_view source_name, const string_view source_slice, size_t lineno, int lineindent) noexcept:
		source_name(source_name),
		source_slice(source_slice),
		lineno(lineno),
		lineindent(lineindent)
	{}
}