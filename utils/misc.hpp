#ifndef HEADER_UTIL_MISC_DEFINED
#define HEADER_UTIL_MISC_DEFINED


#include "../main.hpp"


namespace utils
{
	void slurp(const string& filename, string& text, vector<string_view>& lines);
	
	void slurp(istream& is, string& text, vector<string_view>& lines);
}


#endif // HEADER_UTIL_MISC_DEFINED