# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pingvinus/prog/cpp/my_concurency

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pingvinus/prog/cpp/my_concurency/build

# Include any dependencies generated for this target.
include test/CMakeFiles/atomic_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/atomic_test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/atomic_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/atomic_test.dir/flags.make

test/CMakeFiles/atomic_test.dir/atomic.cpp.o: test/CMakeFiles/atomic_test.dir/flags.make
test/CMakeFiles/atomic_test.dir/atomic.cpp.o: /home/pingvinus/prog/cpp/my_concurency/test/atomic.cpp
test/CMakeFiles/atomic_test.dir/atomic.cpp.o: test/CMakeFiles/atomic_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/pingvinus/prog/cpp/my_concurency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/atomic_test.dir/atomic.cpp.o"
	cd /home/pingvinus/prog/cpp/my_concurency/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/atomic_test.dir/atomic.cpp.o -MF CMakeFiles/atomic_test.dir/atomic.cpp.o.d -o CMakeFiles/atomic_test.dir/atomic.cpp.o -c /home/pingvinus/prog/cpp/my_concurency/test/atomic.cpp

test/CMakeFiles/atomic_test.dir/atomic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/atomic_test.dir/atomic.cpp.i"
	cd /home/pingvinus/prog/cpp/my_concurency/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pingvinus/prog/cpp/my_concurency/test/atomic.cpp > CMakeFiles/atomic_test.dir/atomic.cpp.i

test/CMakeFiles/atomic_test.dir/atomic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/atomic_test.dir/atomic.cpp.s"
	cd /home/pingvinus/prog/cpp/my_concurency/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pingvinus/prog/cpp/my_concurency/test/atomic.cpp -o CMakeFiles/atomic_test.dir/atomic.cpp.s

# Object files for target atomic_test
atomic_test_OBJECTS = \
"CMakeFiles/atomic_test.dir/atomic.cpp.o"

# External object files for target atomic_test
atomic_test_EXTERNAL_OBJECTS =

test/atomic_test: test/CMakeFiles/atomic_test.dir/atomic.cpp.o
test/atomic_test: test/CMakeFiles/atomic_test.dir/build.make
test/atomic_test: concurency/libconcurency.a
test/atomic_test: test/CMakeFiles/atomic_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/pingvinus/prog/cpp/my_concurency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable atomic_test"
	cd /home/pingvinus/prog/cpp/my_concurency/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/atomic_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/atomic_test.dir/build: test/atomic_test
.PHONY : test/CMakeFiles/atomic_test.dir/build

test/CMakeFiles/atomic_test.dir/clean:
	cd /home/pingvinus/prog/cpp/my_concurency/build/test && $(CMAKE_COMMAND) -P CMakeFiles/atomic_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/atomic_test.dir/clean

test/CMakeFiles/atomic_test.dir/depend:
	cd /home/pingvinus/prog/cpp/my_concurency/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pingvinus/prog/cpp/my_concurency /home/pingvinus/prog/cpp/my_concurency/test /home/pingvinus/prog/cpp/my_concurency/build /home/pingvinus/prog/cpp/my_concurency/build/test /home/pingvinus/prog/cpp/my_concurency/build/test/CMakeFiles/atomic_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/atomic_test.dir/depend

