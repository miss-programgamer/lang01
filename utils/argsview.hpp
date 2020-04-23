#ifndef HEADER_UTIL_ARGSVIEW_DEFINED
#define HEADER_UTIL_ARGSVIEW_DEFINED


#include "../libs.hpp"


namespace utils
{
	class argsview: public vector<string_view>
	{
	public:
		argsview(int argc, char* argv[]);
		
		using vector::operator[];
	};
}


#endif // HEADER_UTIL_ARGSVIEW_DEFINED