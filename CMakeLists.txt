cmake_minimum_required(VERSION 3.1)

project(minishell)

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
include_directories(
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/libft"
	)

file(GLOB sources
	"${PROJECT_SOURCE_DIR}/include/*.h"
	"${PROJECT_SOURCE_DIR}/src/lexer/*.c"
	"${PROJECT_SOURCE_DIR}/src/parser/*.c"
	"${PROJECT_SOURCE_DIR}/src/utils/*.c"
	"${PROJECT_SOURCE_DIR}/src/expander/*.c"
	"${PROJECT_SOURCE_DIR}/src/executor/*.c"
	"${PROJECT_SOURCE_DIR}/src/builtins/*.c"
	"${PROJECT_SOURCE_DIR}/src/*.c"
)

include(ExternalProject)
ExternalProject_Add(libft
  GIT_REPOSITORY    ""
  GIT_TAG           ""
  SOURCE_DIR        "${PROJECT_SOURCE_DIR}/libft"
  BINARY_DIR        "${PROJECT_SOURCE_DIR}/libft"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     "make"
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

add_executable(minishell ${sources})
target_compile_options(minishell PRIVATE -Wextra -Wall -Werror -g)
target_link_libraries(minishell "readline" ${PROJECT_SOURCE_DIR}/libft/libft.a)