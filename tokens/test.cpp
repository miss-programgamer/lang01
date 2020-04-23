#include "../libs.hpp"
#include "../utils.hpp"
#include "lexer.hpp"


using namespace tokens;


static bool lexes_each_token(const source_t& source)
{
	// Produce source tokens
	vector<any_token> source_tokens;
	lexer::lex(source.name, source.lines, source_tokens);
	
	// Produce expected tokens manually
	vector<any_token> expected_tokens
	{
		identifier    ({&source.text[00], 15}, 1, 0, 0),
		numeric       ({&source.text[16], 13}, 1, 0, 1),
		quoted_string ({&source.text[30], 13}, 1, 0, 1),
		short_string  ({&source.text[44], 06}, 1, 0, 1),
		delimiter     ({&source.text[51], 01}, 1, 0, 1),
		operator_t    ({&source.text[53], 02}, 1, 0, 1),
		newline       ({&source.text[55], 01}, 1, 0, 0), // newline tokens are technically placed on the line they terminate
		upline        ({&source.text[56], 16}, 2, 0, 0),
	};
	
	bool same = true;
	for (size_t i = 0; i < expected_tokens.size(); ++i) {
		if (const auto& lhs = source_tokens[i], rhs = expected_tokens[i]; lhs != rhs)
		{
			same = false;
			cout << lhs << " != " << rhs << "\n";
		}
	}
	return same;
}


static map<string, function<bool(const source_t&)>> tests
{
	packname(lexes_each_token),
};


int main(int argc, char* argv[])
{
	argsview args(argc - 1, &argv[1]);
	
	try
	{
		string testname = string(args.at(0));
		source_t source("../tests/"s + testname + ".lang01"s);
		return tests[testname](source) ? 0 : 1;
	}
	catch (std::exception ex)
	{
		cout << ex.what() << "\n";
		return 1;
	}
}