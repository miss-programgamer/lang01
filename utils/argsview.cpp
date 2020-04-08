#include "argsview.hpp"


namespace utils
{
	argsview::argsview(int argc, char* argv[]):
		vector<string_view>(argc)
	{
		for (int i = 0; i < argc; i++) {
			(*this)[i] = argv[i];
		}
	}
}