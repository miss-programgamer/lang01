cmake_minimum_required(VERSION 3.0.0)
project(Lang01 VERSION 0.1.0)

# TODO: configure tests
# include(CTest)
# enable_testing()

add_executable(Lang01
	"main.hpp"
	"main.cpp"
	
	"ex.hpp"
	
	"utils/argsview.hpp"
	"utils/argsview.cpp"
	"utils/misc.hpp"
	"utils/misc.cpp"
	"utils.hpp"
	
	"tokens/flags.hpp"
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
	"tokens/tokenizer.hpp"
	"tokens/tokenizer.cpp"
	"tokens.hpp"
	
	"nodes/basic_node.hpp"
	"nodes/basic_node.cpp"
	"nodes/no_op.hpp"
	"nodes/no_op.cpp"
	"nodes/program_decl.hpp"
	"nodes/program_decl.cpp"
	"nodes/call_op.hpp"
	"nodes/call_op.cpp"
	"nodes/any_node.hpp"
	"nodes/any_node.cpp"
	"nodes/parser.hpp"
	"nodes/parser.cpp"
	"nodes.hpp")

set_property(TARGET Lang01 PROPERTY CXX_STANDARD 17)