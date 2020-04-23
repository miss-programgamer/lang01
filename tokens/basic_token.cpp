#include "basic_token.hpp"


namespace tokens
{
	basic_token::basic_token(const string_view source_slice, size_t lineno, int lineindent, size_t leading_space) noexcept:
		source_slice(source_slice),
		lineno(lineno),
		lineindent(lineindent),
		leading_space(leading_space)
	{}
}