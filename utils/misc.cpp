#include "misc.hpp"


namespace utils
{
	void slurp(const string& filename, string& text, vector<string_view>& lines)
	{
		struct slice { size_t start; size_t size; };
		
		if (ifstream file(filename); file)
		{
            stringstream textbuf;
			vector<slice> slices;
			
			size_t cursor = 0;
			for (string line; std::getline(file, line);) {
				textbuf << line;
				if (file) textbuf << "\n";
				slices.push_back({ cursor, line.size() + 1 });
				cursor += line.size() + 1;
			}
			text = textbuf.str();
			text.pop_back();
			
			lines.clear();
			lines.reserve(slices.size());
			const string_view textview = text;
			for (auto slice: slices) {
				lines.push_back(textview.substr(slice.start, slice.size));
			}
        }
	}
	
	void slurp(istream& is, string& text, vector<string_view>& lines)
	{
		std::getline(is, text);
		lines.clear();
		lines.push_back(text);
	}
}