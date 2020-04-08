#include "misc.hpp"


namespace utils
{
	bool slurp(const string& filename, string& text)
	{
		if (ifstream file(filename); file)
		{
            const std::istreambuf_iterator<char> begin(file);
            const std::istreambuf_iterator<char> end;
            text = string(begin, end);
			
			return true;
        }
		else
		{
			return false;
		}
	}
	
	void slurp(istream& is, string& text)
	{
		std::getline(is, text);
	}
}