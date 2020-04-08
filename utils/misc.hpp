#ifndef HEADER_UTIL_MISC_DEFINED
#define HEADER_UTIL_MISC_DEFINED


#include "../main.hpp"


namespace utils
{
	bool slurp(const string& filename, string& text);
	
	void slurp(istream& is, string& text);
}


#endif // HEADER_UTIL_MISC_DEFINED