# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Mandatory_Assignment_2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Mandatory_Assignment_2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Mandatory_Assignment_2.dir/flags.make

CMakeFiles/Mandatory_Assignment_2.dir/mymem.c.o: CMakeFiles/Mandatory_Assignment_2.dir/flags.make
CMakeFiles/Mandatory_Assignment_2.dir/mymem.c.o: ../mymem.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Mandatory_Assignment_2.dir/mymem.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Mandatory_Assignment_2.dir/mymem.c.o   -c "/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2/mymem.c"

CMakeFiles/Mandatory_Assignment_2.dir/mymem.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Mandatory_Assignment_2.dir/mymem.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2/mymem.c" > CMakeFiles/Mandatory_Assignment_2.dir/mymem.c.i

CMakeFiles/Mandatory_Assignment_2.dir/mymem.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Mandatory_Assignment_2.dir/mymem.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2/mymem.c" -o CMakeFiles/Mandatory_Assignment_2.dir/mymem.c.s

# Object files for target Mandatory_Assignment_2
Mandatory_Assignment_2_OBJECTS = \
"CMakeFiles/Mandatory_Assignment_2.dir/mymem.c.o"

# External object files for target Mandatory_Assignment_2
Mandatory_Assignment_2_EXTERNAL_OBJECTS =

Mandatory_Assignment_2: CMakeFiles/Mandatory_Assignment_2.dir/mymem.c.o
Mandatory_Assignment_2: CMakeFiles/Mandatory_Assignment_2.dir/build.make
Mandatory_Assignment_2: CMakeFiles/Mandatory_Assignment_2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Mandatory_Assignment_2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Mandatory_Assignment_2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Mandatory_Assignment_2.dir/build: Mandatory_Assignment_2

.PHONY : CMakeFiles/Mandatory_Assignment_2.dir/build

CMakeFiles/Mandatory_Assignment_2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Mandatory_Assignment_2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Mandatory_Assignment_2.dir/clean

CMakeFiles/Mandatory_Assignment_2.dir/depend:
	cd "/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2" "/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2" "/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2/cmake-build-debug" "/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2/cmake-build-debug" "/Users/mohammad/Desktop/OP/OpLap2/Mandatory Assignment 2/cmake-build-debug/CMakeFiles/Mandatory_Assignment_2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Mandatory_Assignment_2.dir/depend
