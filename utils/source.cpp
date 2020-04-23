#include "source.hpp"
#include "misc.hpp"


namespace utils
{
	source_t::source_t(string_view name_view)
	{
		name = string(name_view);
		slurp(name, text, lines);
	}
}