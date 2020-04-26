cmake_minimum_required(VERSION 3.0.0)
project(Lang01 VERSION 0.1.0)
enable_testing()

# Enable the maximum level of compiler errors
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options("-Wextra")
endif()
if(MSVC)
    string(REGEX REPLACE "/W[1-3]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

list(APPEND lib_files
	"ex.hpp"
	"libs.hpp")

list(APPEND utils_files
	"utils/argsview.hpp"
	"utils/argsview.cpp"
	"utils/colors.hpp"
	"utils/colors.cpp"
	"utils/source.hpp"
	"utils/source.cpp"
	"utils/misc.hpp"
	"utils/misc.cpp"
	"utils.hpp")

list(APPEND tokens_files
	"tokens/basic_token.hpp"
	"tokens/basic_token.cpp"
	"tokens/every_token.hpp"
	"tokens/every_token.cpp"
	"tokens/any_token.hpp"
	"tokens/any_token.cpp"
	"tokens/lexer.hpp"
	"tokens/lexer.cpp"
	"tokens.hpp")

list(APPEND nodes_files
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

list(APPEND vm_files
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

# Add main executable
add_executable(Lang01
	"main.cpp"
	${lib_files}
	${utils_files}
	${tokens_files}
	${nodes_files}
	${vm_files})

# Add vm executable
add_executable(Lang01VM
	"vm-main.cpp"
	${lib_files}
	${utils_files}
	${vm_files})

# Add lexing test
add_executable(LexingTest
	"tokens/test.cpp"
	${lib_files}
	${utils_files}
	${tokens_files})

# Add parsing test
add_executable(ParsingTest
	"nodes/test.cpp"
	${lib_files}
	${utils_files}
	${tokens_files}
	${nodes_files})

# Add vm test
add_executable(VirtualMachineTest
	"vm/test.cpp"
	${lib_files}
	${utils_files}
	${vm_files})

# C++ 17 for all targets
set_property(TARGET Lang01 PROPERTY CXX_STANDARD 17)
set_property(TARGET Lang01VM PROPERTY CXX_STANDARD 17)
set_property(TARGET LexingTest PROPERTY CXX_STANDARD 17)
set_property(TARGET ParsingTest PROPERTY CXX_STANDARD 17)
set_property(TARGET VirtualMachineTest PROPERTY CXX_STANDARD 17)

# Configure tests
add_test(NAME lexes_each_token
	COMMAND LexingTest "lexes_each_token")