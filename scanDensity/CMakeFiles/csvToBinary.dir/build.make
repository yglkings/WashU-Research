# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/erikwijmans/c++/scanDensity

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/erikwijmans/c++/scanDensity

# Include any dependencies generated for this target.
include CMakeFiles/csvToBinary.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/csvToBinary.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/csvToBinary.dir/flags.make

CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o: CMakeFiles/csvToBinary.dir/flags.make
CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o: csvToBinary.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/erikwijmans/c++/scanDensity/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o -c /Users/erikwijmans/c++/scanDensity/csvToBinary.cpp

CMakeFiles/csvToBinary.dir/csvToBinary.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/csvToBinary.dir/csvToBinary.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/erikwijmans/c++/scanDensity/csvToBinary.cpp > CMakeFiles/csvToBinary.dir/csvToBinary.cpp.i

CMakeFiles/csvToBinary.dir/csvToBinary.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/csvToBinary.dir/csvToBinary.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/erikwijmans/c++/scanDensity/csvToBinary.cpp -o CMakeFiles/csvToBinary.dir/csvToBinary.cpp.s

CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o.requires:

.PHONY : CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o.requires

CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o.provides: CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o.requires
	$(MAKE) -f CMakeFiles/csvToBinary.dir/build.make CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o.provides.build
.PHONY : CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o.provides

CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o.provides.build: CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o


# Object files for target csvToBinary
csvToBinary_OBJECTS = \
"CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o"

# External object files for target csvToBinary
csvToBinary_EXTERNAL_OBJECTS =

csvToBinary: CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o
csvToBinary: CMakeFiles/csvToBinary.dir/build.make
csvToBinary: /usr/local/lib/libgflags.a
csvToBinary: CMakeFiles/csvToBinary.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/erikwijmans/c++/scanDensity/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable csvToBinary"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/csvToBinary.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/csvToBinary.dir/build: csvToBinary

.PHONY : CMakeFiles/csvToBinary.dir/build

CMakeFiles/csvToBinary.dir/requires: CMakeFiles/csvToBinary.dir/csvToBinary.cpp.o.requires

.PHONY : CMakeFiles/csvToBinary.dir/requires

CMakeFiles/csvToBinary.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/csvToBinary.dir/cmake_clean.cmake
.PHONY : CMakeFiles/csvToBinary.dir/clean

CMakeFiles/csvToBinary.dir/depend:
	cd /Users/erikwijmans/c++/scanDensity && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/erikwijmans/c++/scanDensity /Users/erikwijmans/c++/scanDensity /Users/erikwijmans/c++/scanDensity /Users/erikwijmans/c++/scanDensity /Users/erikwijmans/c++/scanDensity/CMakeFiles/csvToBinary.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/csvToBinary.dir/depend
