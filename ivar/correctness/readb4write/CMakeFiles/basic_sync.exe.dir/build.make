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
CMAKE_SOURCE_DIR = /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write

# Include any dependencies generated for this target.
include CMakeFiles/basic_sync.exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/basic_sync.exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/basic_sync.exe.dir/flags.make

CMakeFiles/basic_sync.exe.dir/basic_sync.c.o: CMakeFiles/basic_sync.exe.dir/flags.make
CMakeFiles/basic_sync.exe.dir/basic_sync.c.o: basic_sync.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/basic_sync.exe.dir/basic_sync.c.o"
	clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/basic_sync.exe.dir/basic_sync.c.o   -c /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/basic_sync.c

CMakeFiles/basic_sync.exe.dir/basic_sync.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/basic_sync.exe.dir/basic_sync.c.i"
	clang  $(C_DEFINES) $(C_FLAGS) -E /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/basic_sync.c > CMakeFiles/basic_sync.exe.dir/basic_sync.c.i

CMakeFiles/basic_sync.exe.dir/basic_sync.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/basic_sync.exe.dir/basic_sync.c.s"
	clang  $(C_DEFINES) $(C_FLAGS) -S /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/basic_sync.c -o CMakeFiles/basic_sync.exe.dir/basic_sync.c.s

CMakeFiles/basic_sync.exe.dir/basic_sync.c.o.requires:
.PHONY : CMakeFiles/basic_sync.exe.dir/basic_sync.c.o.requires

CMakeFiles/basic_sync.exe.dir/basic_sync.c.o.provides: CMakeFiles/basic_sync.exe.dir/basic_sync.c.o.requires
	$(MAKE) -f CMakeFiles/basic_sync.exe.dir/build.make CMakeFiles/basic_sync.exe.dir/basic_sync.c.o.provides.build
.PHONY : CMakeFiles/basic_sync.exe.dir/basic_sync.c.o.provides

CMakeFiles/basic_sync.exe.dir/basic_sync.c.o.provides.build: CMakeFiles/basic_sync.exe.dir/basic_sync.c.o

# Object files for target basic_sync.exe
basic_sync_exe_OBJECTS = \
"CMakeFiles/basic_sync.exe.dir/basic_sync.c.o"

# External object files for target basic_sync.exe
basic_sync_exe_EXTERNAL_OBJECTS =

basic_sync.exe: CMakeFiles/basic_sync.exe.dir/basic_sync.c.o
basic_sync.exe: CMakeFiles/basic_sync.exe.dir/build.make
basic_sync.exe: CMakeFiles/basic_sync.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable basic_sync.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/basic_sync.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/basic_sync.exe.dir/build: basic_sync.exe
.PHONY : CMakeFiles/basic_sync.exe.dir/build

CMakeFiles/basic_sync.exe.dir/requires: CMakeFiles/basic_sync.exe.dir/basic_sync.c.o.requires
.PHONY : CMakeFiles/basic_sync.exe.dir/requires

CMakeFiles/basic_sync.exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/basic_sync.exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/basic_sync.exe.dir/clean

CMakeFiles/basic_sync.exe.dir/depend:
	cd /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/CMakeFiles/basic_sync.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/basic_sync.exe.dir/depend
