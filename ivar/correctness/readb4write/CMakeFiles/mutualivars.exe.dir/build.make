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
include CMakeFiles/mutualivars.exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mutualivars.exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mutualivars.exe.dir/flags.make

CMakeFiles/mutualivars.exe.dir/mutualivars.c.o: CMakeFiles/mutualivars.exe.dir/flags.make
CMakeFiles/mutualivars.exe.dir/mutualivars.c.o: mutualivars.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/mutualivars.exe.dir/mutualivars.c.o"
	clang  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/mutualivars.exe.dir/mutualivars.c.o   -c /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/mutualivars.c

CMakeFiles/mutualivars.exe.dir/mutualivars.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mutualivars.exe.dir/mutualivars.c.i"
	clang  $(C_DEFINES) $(C_FLAGS) -E /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/mutualivars.c > CMakeFiles/mutualivars.exe.dir/mutualivars.c.i

CMakeFiles/mutualivars.exe.dir/mutualivars.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mutualivars.exe.dir/mutualivars.c.s"
	clang  $(C_DEFINES) $(C_FLAGS) -S /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/mutualivars.c -o CMakeFiles/mutualivars.exe.dir/mutualivars.c.s

CMakeFiles/mutualivars.exe.dir/mutualivars.c.o.requires:
.PHONY : CMakeFiles/mutualivars.exe.dir/mutualivars.c.o.requires

CMakeFiles/mutualivars.exe.dir/mutualivars.c.o.provides: CMakeFiles/mutualivars.exe.dir/mutualivars.c.o.requires
	$(MAKE) -f CMakeFiles/mutualivars.exe.dir/build.make CMakeFiles/mutualivars.exe.dir/mutualivars.c.o.provides.build
.PHONY : CMakeFiles/mutualivars.exe.dir/mutualivars.c.o.provides

CMakeFiles/mutualivars.exe.dir/mutualivars.c.o.provides.build: CMakeFiles/mutualivars.exe.dir/mutualivars.c.o

# Object files for target mutualivars.exe
mutualivars_exe_OBJECTS = \
"CMakeFiles/mutualivars.exe.dir/mutualivars.c.o"

# External object files for target mutualivars.exe
mutualivars_exe_EXTERNAL_OBJECTS =

mutualivars.exe: CMakeFiles/mutualivars.exe.dir/mutualivars.c.o
mutualivars.exe: CMakeFiles/mutualivars.exe.dir/build.make
mutualivars.exe: CMakeFiles/mutualivars.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable mutualivars.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mutualivars.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mutualivars.exe.dir/build: mutualivars.exe
.PHONY : CMakeFiles/mutualivars.exe.dir/build

CMakeFiles/mutualivars.exe.dir/requires: CMakeFiles/mutualivars.exe.dir/mutualivars.c.o.requires
.PHONY : CMakeFiles/mutualivars.exe.dir/requires

CMakeFiles/mutualivars.exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mutualivars.exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mutualivars.exe.dir/clean

CMakeFiles/mutualivars.exe.dir/depend:
	cd /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write /home/czakian/Research/concurrent_cilk/cilk_tests/ivar/correctness/readb4write/CMakeFiles/mutualivars.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mutualivars.exe.dir/depend
