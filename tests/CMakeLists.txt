include_directories("${PROJECT_SOURCE_DIR}/include")

### C Source Files ###
file(GLOB sources
      "${PROJECT_SOURCE_DIR}/src/*.c"
      "${PROJECT_SOURCE_DIR}/src/lexer/*.c"
      "${PROJECT_SOURCE_DIR}/src/parser/*.c"
      "${PROJECT_SOURCE_DIR}/src/expander/*.c"
      "${PROJECT_SOURCE_DIR}/src/executor/*.c"
      "${PROJECT_SOURCE_DIR}/src/utils/*.c"
    )
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.c")

### CPP Test Files ###
file(GLOB tests
      "${PROJECT_SOURCE_DIR}/tests/*.cpp"
      "${PROJECT_SOURCE_DIR}/tests/utils_tests/*.cpp"
      "${PROJECT_SOURCE_DIR}/tests/parser_tests/*.cpp"
    )
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/tests/main.cpp")

foreach(file ${tests})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests"
    ${sources}
    ${file}
    "${PROJECT_SOURCE_DIR}/tests/main.cpp")
  target_link_libraries("${name}_tests" gtest_main "readline")
  target_compile_options("${name}_tests" PRIVATE -Wextra -Wall -g)
  add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()