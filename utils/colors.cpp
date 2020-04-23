#include "colors.hpp"


namespace utils
{
	const style style::reset;
	
	ostream& operator<<(ostream& os, const style& ansi)
	{
		os << "\x1b[" << ansi.seq << "m";
		return os;
	}
}