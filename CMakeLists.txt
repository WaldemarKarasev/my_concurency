cmake_minimum_required(VERSION 3.11)

project(my_concurrency CXX C ASM)

# include(cmake/toolchain.cmake)

include(cmake/logging.cmake)
include(cmake/check_compiler.cmake)
include(cmake/compile_options.cmake)
include(cmake/sanitize.cmake)


add_subdirectory(concurrency)

add_subdirectory(example)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(test)