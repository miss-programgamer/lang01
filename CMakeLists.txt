cmake_minimum_required(VERSION 3.0.0)
project(Lang01 VERSION 0.1.0)

# TODO: configure tests
# include(CTest)
# enable_testing()

add_executable(Lang01
	"main.hpp"
	"main.cpp"
	
	"ex.hpp"
	
	"tokens/flags.hpp"
	"tokens/tokenizer.hpp"
	"tokens/tokenizer.cpp"
	"tokens/basic_token.hpp"
	"tokens/basic_token.cpp"
	"tokens/empty.hpp"
	"tokens/empty.cpp"
	"tokens/linestart.hpp"
	"tokens/linestart.cpp"
	"tokens/lineend.hpp"
	"tokens/lineend.cpp"
	"tokens/identifier.hpp"
	"tokens/identifier.cpp"
	"tokens/whitespace.hpp"
	"tokens/whitespace.cpp"
	"tokens/comment.hpp"
	"tokens/comment.cpp"
	"tokens/invalid.hpp"
	"tokens/invalid.cpp"
	"tokens/any_token.hpp"
	"tokens/any_token.cpp"
	
	"utils/argsview.hpp"
	"utils/argsview.cpp"
	"utils/misc.hpp"
	"utils/misc.cpp"
	"utils.hpp")

set_property(TARGET Lang01 PROPERTY CXX_STANDARD 17)