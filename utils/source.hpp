#ifndef HEADER_UTILS_SOURCE_DEFINED
#define HEADER_UTILS_SOURCE_DEFINED


#include "../libs.hpp"


namespace utils
{
	struct source_t
	{
		string name;
		
		string text;
		
		vector<string_view> lines;
		
		source_t(string_view name_view);
	};
}


#else // HEADER_UTILS_SOURCE_DEFINED


namespace utils
{
	struct source_t;
}


#endif // HEADER_UTILS_SOURCE_DEFINED