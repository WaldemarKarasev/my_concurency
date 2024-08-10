cmake_minimum_required(VERSION 3.11)

project(my_concurency CXX C ASM)

include(cmake/logging.cmake)
include(cmake/check_compiler.cmake)
include(cmake/compile_options.cmake)
include(cmake/sanitize.cmake)


add_subdirectory(concurency)

add_subdirectory(example)

add_subdirectory(test)