# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/routine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/routine.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/routine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/routine.dir/flags.make

CMakeFiles/routine.dir/routine.c.o: CMakeFiles/routine.dir/flags.make
CMakeFiles/routine.dir/routine.c.o: /Users/nicolaischultz/Library/Mobile\ Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main/routine.c
CMakeFiles/routine.dir/routine.c.o: CMakeFiles/routine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/routine.dir/routine.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/routine.dir/routine.c.o -MF CMakeFiles/routine.dir/routine.c.o.d -o CMakeFiles/routine.dir/routine.c.o -c "/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main/routine.c"

CMakeFiles/routine.dir/routine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/routine.dir/routine.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main/routine.c" > CMakeFiles/routine.dir/routine.c.i

CMakeFiles/routine.dir/routine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/routine.dir/routine.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main/routine.c" -o CMakeFiles/routine.dir/routine.c.s

# Object files for target routine
routine_OBJECTS = \
"CMakeFiles/routine.dir/routine.c.o"

# External object files for target routine
routine_EXTERNAL_OBJECTS =

libroutine.a: CMakeFiles/routine.dir/routine.c.o
libroutine.a: CMakeFiles/routine.dir/build.make
libroutine.a: CMakeFiles/routine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libroutine.a"
	$(CMAKE_COMMAND) -P CMakeFiles/routine.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/routine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/routine.dir/build: libroutine.a
.PHONY : CMakeFiles/routine.dir/build

CMakeFiles/routine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/routine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/routine.dir/clean

CMakeFiles/routine.dir/depend:
	cd "/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main" "/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main" "/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main/cmake-build-debug" "/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main/cmake-build-debug" "/Users/nicolaischultz/Library/Mobile Documents/com~apple~CloudDocs/UNI/IMPR/P1-project/Main/cmake-build-debug/CMakeFiles/routine.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/routine.dir/depend

