cmake_minimum_required(VERSION 3.1)

project(minishell)

#set(CMAKE_BUILD_PARALLEL_LEVEL "4")

### Google Test ###
configure_file(CMakeLists.txt.in
		googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
		 ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(tests)

### Source definitions ###

file(GLOB sources
	"${PROJECT_SOURCE_DIR}/include/*.h"
	"${PROJECT_SOURCE_DIR}/src/lexer/*.c"
	"${PROJECT_SOURCE_DIR}/src/parser/*.c"
	"${PROJECT_SOURCE_DIR}/src/utils/*.c"
	"${PROJECT_SOURCE_DIR}/src/expander/*.c"
	"${PROJECT_SOURCE_DIR}/src/executor/*.c"
	"${PROJECT_SOURCE_DIR}/src/builtins/*.c"
	"${PROJECT_SOURCE_DIR}/src/heredoc/*.c"
	"${PROJECT_SOURCE_DIR}/src/signal_handling/*.c"
	"${PROJECT_SOURCE_DIR}/src/*.c"
)

include(ExternalProject)
ExternalProject_Add(libft_lib
	SOURCE_DIR			"${PROJECT_SOURCE_DIR}/libft"
	BINARY_DIR			"${PROJECT_SOURCE_DIR}/libft"
	CONFIGURE_COMMAND	""
	BUILD_COMMAND		"make"
	INSTALL_COMMAND		""
	TEST_COMMAND		""
)

include_directories(
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/libft"
	"${PROJECT_SOURCE_DIR}/vendor/readline/include"
)

link_directories(
	"${PROJECT_SOURCE_DIR}/libft"
	"${PROJECT_SOURCE_DIR}/vendor/readline/lib"
)

add_custom_target(READLINE_LIB ALL
	DEPENDS	"${PROJECT_SOURCE_DIR}/vendor/readline"
)
add_custom_command(
	OUTPUT	"${PROJECT_SOURCE_DIR}/vendor/readline"
	COMMAND "mkdir" "-p" "vendor"
	COMMAND "bash" "install_readline.sh"
	WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

add_executable(minishell ${sources})
target_compile_options(minishell PRIVATE -Wextra -Wall -Werror -g)
target_link_libraries(minishell libft.a readline)
