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
include concurency/CMakeFiles/concurency.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include concurency/CMakeFiles/concurency.dir/compiler_depend.make

# Include the progress variables for this target.
include concurency/CMakeFiles/concurency.dir/progress.make

# Include the compile flags for this target's objects.
include concurency/CMakeFiles/concurency.dir/flags.make

concurency/CMakeFiles/concurency.dir/atomic/atomic.cpp.o: concurency/CMakeFiles/concurency.dir/flags.make
concurency/CMakeFiles/concurency.dir/atomic/atomic.cpp.o: /home/pingvinus/prog/cpp/my_concurency/concurency/atomic/atomic.cpp
concurency/CMakeFiles/concurency.dir/atomic/atomic.cpp.o: concurency/CMakeFiles/concurency.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/pingvinus/prog/cpp/my_concurency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object concurency/CMakeFiles/concurency.dir/atomic/atomic.cpp.o"
	cd /home/pingvinus/prog/cpp/my_concurency/build/concurency && /usr/bin/clang++-15 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT concurency/CMakeFiles/concurency.dir/atomic/atomic.cpp.o -MF CMakeFiles/concurency.dir/atomic/atomic.cpp.o.d -o CMakeFiles/concurency.dir/atomic/atomic.cpp.o -c /home/pingvinus/prog/cpp/my_concurency/concurency/atomic/atomic.cpp

concurency/CMakeFiles/concurency.dir/atomic/atomic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/concurency.dir/atomic/atomic.cpp.i"
	cd /home/pingvinus/prog/cpp/my_concurency/build/concurency && /usr/bin/clang++-15 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pingvinus/prog/cpp/my_concurency/concurency/atomic/atomic.cpp > CMakeFiles/concurency.dir/atomic/atomic.cpp.i

concurency/CMakeFiles/concurency.dir/atomic/atomic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/concurency.dir/atomic/atomic.cpp.s"
	cd /home/pingvinus/prog/cpp/my_concurency/build/concurency && /usr/bin/clang++-15 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pingvinus/prog/cpp/my_concurency/concurency/atomic/atomic.cpp -o CMakeFiles/concurency.dir/atomic/atomic.cpp.s

concurency/CMakeFiles/concurency.dir/mutex/mutex.cpp.o: concurency/CMakeFiles/concurency.dir/flags.make
concurency/CMakeFiles/concurency.dir/mutex/mutex.cpp.o: /home/pingvinus/prog/cpp/my_concurency/concurency/mutex/mutex.cpp
concurency/CMakeFiles/concurency.dir/mutex/mutex.cpp.o: concurency/CMakeFiles/concurency.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/pingvinus/prog/cpp/my_concurency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object concurency/CMakeFiles/concurency.dir/mutex/mutex.cpp.o"
	cd /home/pingvinus/prog/cpp/my_concurency/build/concurency && /usr/bin/clang++-15 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT concurency/CMakeFiles/concurency.dir/mutex/mutex.cpp.o -MF CMakeFiles/concurency.dir/mutex/mutex.cpp.o.d -o CMakeFiles/concurency.dir/mutex/mutex.cpp.o -c /home/pingvinus/prog/cpp/my_concurency/concurency/mutex/mutex.cpp

concurency/CMakeFiles/concurency.dir/mutex/mutex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/concurency.dir/mutex/mutex.cpp.i"
	cd /home/pingvinus/prog/cpp/my_concurency/build/concurency && /usr/bin/clang++-15 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pingvinus/prog/cpp/my_concurency/concurency/mutex/mutex.cpp > CMakeFiles/concurency.dir/mutex/mutex.cpp.i

concurency/CMakeFiles/concurency.dir/mutex/mutex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/concurency.dir/mutex/mutex.cpp.s"
	cd /home/pingvinus/prog/cpp/my_concurency/build/concurency && /usr/bin/clang++-15 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pingvinus/prog/cpp/my_concurency/concurency/mutex/mutex.cpp -o CMakeFiles/concurency.dir/mutex/mutex.cpp.s

# Object files for target concurency
concurency_OBJECTS = \
"CMakeFiles/concurency.dir/atomic/atomic.cpp.o" \
"CMakeFiles/concurency.dir/mutex/mutex.cpp.o"

# External object files for target concurency
concurency_EXTERNAL_OBJECTS =

concurency/libconcurency.a: concurency/CMakeFiles/concurency.dir/atomic/atomic.cpp.o
concurency/libconcurency.a: concurency/CMakeFiles/concurency.dir/mutex/mutex.cpp.o
concurency/libconcurency.a: concurency/CMakeFiles/concurency.dir/build.make
concurency/libconcurency.a: concurency/CMakeFiles/concurency.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/pingvinus/prog/cpp/my_concurency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libconcurency.a"
	cd /home/pingvinus/prog/cpp/my_concurency/build/concurency && $(CMAKE_COMMAND) -P CMakeFiles/concurency.dir/cmake_clean_target.cmake
	cd /home/pingvinus/prog/cpp/my_concurency/build/concurency && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/concurency.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
concurency/CMakeFiles/concurency.dir/build: concurency/libconcurency.a
.PHONY : concurency/CMakeFiles/concurency.dir/build

concurency/CMakeFiles/concurency.dir/clean:
	cd /home/pingvinus/prog/cpp/my_concurency/build/concurency && $(CMAKE_COMMAND) -P CMakeFiles/concurency.dir/cmake_clean.cmake
.PHONY : concurency/CMakeFiles/concurency.dir/clean

concurency/CMakeFiles/concurency.dir/depend:
	cd /home/pingvinus/prog/cpp/my_concurency/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pingvinus/prog/cpp/my_concurency /home/pingvinus/prog/cpp/my_concurency/concurency /home/pingvinus/prog/cpp/my_concurency/build /home/pingvinus/prog/cpp/my_concurency/build/concurency /home/pingvinus/prog/cpp/my_concurency/build/concurency/CMakeFiles/concurency.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : concurency/CMakeFiles/concurency.dir/depend
