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
include CMakeFiles/minimal_cilk.exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/minimal_cilk.exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/minimal_cilk.exe.dir/flags.make

CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o: CMakeFiles/minimal_cilk.exe.dir/flags.make
CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o: minimal_cilk.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o"
	clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o   -c /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/minimal_cilk.c

CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.i"
	clang  $(C_DEFINES) $(C_FLAGS) -E /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/minimal_cilk.c > CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.i

CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.s"
	clang  $(C_DEFINES) $(C_FLAGS) -S /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/minimal_cilk.c -o CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.s

CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o.requires:
.PHONY : CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o.requires

CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o.provides: CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o.requires
	$(MAKE) -f CMakeFiles/minimal_cilk.exe.dir/build.make CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o.provides.build
.PHONY : CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o.provides

CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o.provides.build: CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o

# Object files for target minimal_cilk.exe
minimal_cilk_exe_OBJECTS = \
"CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o"

# External object files for target minimal_cilk.exe
minimal_cilk_exe_EXTERNAL_OBJECTS =

minimal_cilk.exe: CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o
minimal_cilk.exe: CMakeFiles/minimal_cilk.exe.dir/build.make
minimal_cilk.exe: CMakeFiles/minimal_cilk.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable minimal_cilk.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minimal_cilk.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/minimal_cilk.exe.dir/build: minimal_cilk.exe
.PHONY : CMakeFiles/minimal_cilk.exe.dir/build

CMakeFiles/minimal_cilk.exe.dir/requires: CMakeFiles/minimal_cilk.exe.dir/minimal_cilk.c.o.requires
.PHONY : CMakeFiles/minimal_cilk.exe.dir/requires

CMakeFiles/minimal_cilk.exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/minimal_cilk.exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/minimal_cilk.exe.dir/clean

CMakeFiles/minimal_cilk.exe.dir/depend:
	cd /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/CMakeFiles/minimal_cilk.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/minimal_cilk.exe.dir/depend

