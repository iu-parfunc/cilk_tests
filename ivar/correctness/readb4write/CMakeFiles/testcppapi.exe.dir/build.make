# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /u/parfunc/opt/concurrent_cilk/cilk_tests/ivar/correctness/readb4write

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /u/parfunc/opt/concurrent_cilk/cilk_tests/ivar/correctness/readb4write

# Include any dependencies generated for this target.
include CMakeFiles/testcppapi.exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testcppapi.exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testcppapi.exe.dir/flags.make

CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o: CMakeFiles/testcppapi.exe.dir/flags.make
CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o: testcppapi.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /u/parfunc/opt/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o"
	clang++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o -c /u/parfunc/opt/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/testcppapi.cpp

CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.i"
	clang++  $(CXX_DEFINES) $(CXX_FLAGS) -E /u/parfunc/opt/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/testcppapi.cpp > CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.i

CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.s"
	clang++  $(CXX_DEFINES) $(CXX_FLAGS) -S /u/parfunc/opt/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/testcppapi.cpp -o CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.s

CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o.requires:
.PHONY : CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o.requires

CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o.provides: CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o.requires
	$(MAKE) -f CMakeFiles/testcppapi.exe.dir/build.make CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o.provides.build
.PHONY : CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o.provides

CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o.provides.build: CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o

# Object files for target testcppapi.exe
testcppapi_exe_OBJECTS = \
"CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o"

# External object files for target testcppapi.exe
testcppapi_exe_EXTERNAL_OBJECTS =

testcppapi.exe: CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o
testcppapi.exe: CMakeFiles/testcppapi.exe.dir/build.make
testcppapi.exe: CMakeFiles/testcppapi.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable testcppapi.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testcppapi.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testcppapi.exe.dir/build: testcppapi.exe
.PHONY : CMakeFiles/testcppapi.exe.dir/build

CMakeFiles/testcppapi.exe.dir/requires: CMakeFiles/testcppapi.exe.dir/testcppapi.cpp.o.requires
.PHONY : CMakeFiles/testcppapi.exe.dir/requires

CMakeFiles/testcppapi.exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testcppapi.exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testcppapi.exe.dir/clean

CMakeFiles/testcppapi.exe.dir/depend:
	cd /u/parfunc/opt/concurrent_cilk/cilk_tests/ivar/correctness/readb4write && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /u/parfunc/opt/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /u/parfunc/opt/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /u/parfunc/opt/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /u/parfunc/opt/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /u/parfunc/opt/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/CMakeFiles/testcppapi.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testcppapi.exe.dir/depend

