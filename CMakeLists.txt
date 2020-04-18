cmake_minimum_required(VERSION 3.0.0)
project(Lang01 VERSION 0.1.0)

# Enable the maximum level of errors
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options("-Wextra")
endif()
if(MSVC)
    string(REGEX REPLACE "/W[1-3]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# TODO: configure tests
# include(CTest)
# enable_testing()

# Add executable and its files
add_executable(Lang01
	"main.hpp"
	"main.cpp"
	
	"ex.hpp"
	
	"utils/argsview.hpp"
	"utils/argsview.cpp"
	"utils/misc.hpp"
	"utils/misc.cpp"
	"utils.hpp"
	
	"tokens/basic_token.hpp"
	"tokens/basic_token.cpp"
	"tokens/every_token.hpp"
	"tokens/every_token.cpp"
	"tokens/any_token.hpp"
	"tokens/any_token.cpp"
	"tokens/lexer.hpp"
	"tokens/lexer.cpp"
	"tokens.hpp"
	
	"nodes/basic_node.hpp"
	"nodes/basic_node.cpp"
	"nodes/every_node.hpp"
	"nodes/every_node.cpp"
	"nodes/any_node.hpp"
	"nodes/any_node.cpp"
	"nodes/context.hpp"
	"nodes/context.cpp"
	"nodes/parser.hpp"
	"nodes/parser.cpp"
	"nodes.hpp")

# Set the C++ standard for the main target
set_property(TARGET Lang01 PROPERTY CXX_STANDARD 17)