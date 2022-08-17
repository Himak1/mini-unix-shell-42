include_directories(
	"${PROJECT_SOURCE_DIR}/include"
	"${PROJECT_SOURCE_DIR}/libft"
)

### C Source Files ###
file(GLOB sources
			"${PROJECT_SOURCE_DIR}/src/*.c"
			"${PROJECT_SOURCE_DIR}/src/lexer/*.c"
			"${PROJECT_SOURCE_DIR}/src/parser/*.c"
			"${PROJECT_SOURCE_DIR}/src/expander/*.c"
			"${PROJECT_SOURCE_DIR}/src/executor/*.c"
			"${PROJECT_SOURCE_DIR}/src/utils/*.c"
			"${PROJECT_SOURCE_DIR}/src/builtins/*.c"
		)
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.c")

### CPP Test Files ###
file(GLOB tests
			"${PROJECT_SOURCE_DIR}/tests/*.cpp"
			"${PROJECT_SOURCE_DIR}/tests/utils_tests/*.cpp"
			"${PROJECT_SOURCE_DIR}/tests/parser_tests/*.cpp"
			"${PROJECT_SOURCE_DIR}/tests/lexer_tests/*.cpp"
			"${PROJECT_SOURCE_DIR}/tests/expander_tests/*.cpp"
			"${PROJECT_SOURCE_DIR}/tests/executor_tests/*.cpp"
			"${PROJECT_SOURCE_DIR}/tests/builtins_tests/*.cpp"
			)
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/tests/main.cpp")

foreach(file ${tests})
	set(name)
	get_filename_component(name ${file} NAME_WE)
	add_executable("${name}_tests"
		${sources}
		${file}
		"${PROJECT_SOURCE_DIR}/tests/main.cpp")
	target_link_libraries("${name}_tests" gtest_main "readline" ${PROJECT_SOURCE_DIR}/libft/libft.a)
	target_compile_options("${name}_tests" PRIVATE -Wextra -Wall -g)
	add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()