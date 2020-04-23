#ifndef HEADER_UTILS_COLORS_DEFINED
#define HEADER_UTILS_COLORS_DEFINED


#include "../libs.hpp"


namespace utils
{
	class style
	{
	protected:
		const char* seq;
		
	public:
		static const style reset;
		
		inline constexpr style(const char* seq = "") noexcept:
			seq(seq)
		{}
		
		friend ostream& operator<<(ostream& os, const style& ansi);
	};
}


#endif // HEADER_UTILS_COLORS_DEFINED