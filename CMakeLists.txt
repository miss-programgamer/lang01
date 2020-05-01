cmake_minimum_required(VERSION 3.0.0)
project(Lang01 VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
enable_testing()

# Enable the maximum level of compiler errors
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options("-Wextra")
endif()

if(MSVC)
	string(REGEX REPLACE "/W[1-3]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# Find packages
find_package(RapidJSON CONFIG REQUIRED)

# Add utils library
add_library(utils STATIC EXCLUDE_FROM_ALL
	"libs.hpp"
	"ex.hpp"
	"utils/argsview.hpp"
	"utils/argsview.cpp"
	"utils/colors.hpp"
	"utils/colors.cpp"
	"utils/source.hpp"
	"utils/source.cpp"
	"utils/misc.hpp"
	"utils/misc.cpp"
	"utils.hpp")

# Add lexing library
add_library(lexing STATIC EXCLUDE_FROM_ALL
	"tokens/basic_token.hpp"
	"tokens/basic_token.cpp"
	"tokens/every_token.hpp"
	"tokens/every_token.cpp"
	"tokens/any_token.hpp"
	"tokens/any_token.cpp"
	"tokens/lexer.hpp"
	"tokens/lexer.cpp"
	"tokens.hpp")

target_link_libraries(lexing PRIVATE utils)

# Add parsing library
add_library(parsing STATIC EXCLUDE_FROM_ALL
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

target_link_libraries(parsing PRIVATE utils lexing)

# Add virtual machine library
add_library(vm STATIC EXCLUDE_FROM_ALL
	"vm/instruction.hpp"
	"vm/instruction.cpp"
	"vm/every_value.hpp"
	"vm/every_value.cpp"
	"vm/any_value.hpp"
	"vm/any_value.cpp"
	"vm/frame.hpp"
	"vm/frame.cpp"
	"vm/function.hpp"
	"vm/function.cpp"
	"vm/interpreter.hpp"
	"vm/interpreter.cpp"
	"vm.hpp")

target_link_libraries(vm PRIVATE utils)

# Add assembler library
add_library(assembling STATIC EXCLUDE_FROM_ALL
	"assem/assembler.hpp"
	"assem/assembler.cpp")

target_link_libraries(assembling PRIVATE utils parsing vm)

# Add executable targets
add_executable(Lang01 "main.cpp")
target_link_libraries(Lang01 PRIVATE utils lexing parsing)

add_executable(Lang01VM "vm-main.cpp")
target_link_libraries(Lang01VM PRIVATE utils vm)

add_executable(LexingTest "tokens/test.cpp")
target_link_libraries(LexingTest PRIVATE utils lexing)

add_executable(ParsingTest "nodes/test.cpp")
target_link_libraries(ParsingTest PRIVATE utils lexing parsing)

add_executable(VirtualMachineTest "vm/test.cpp")
target_link_libraries(VirtualMachineTest PRIVATE utils vm)

# Configure tests
add_test(NAME lexes_each_token COMMAND LexingTest "lexes_each_token")