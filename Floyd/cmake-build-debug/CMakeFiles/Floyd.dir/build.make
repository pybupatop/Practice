# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /cygdrive/c/Users/pankin/AppData/Local/JetBrains/CLion2020.3/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/pankin/AppData/Local/JetBrains/CLion2020.3/cygwin_cmake/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Floyd.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Floyd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Floyd.dir/flags.make

CMakeFiles/Floyd.dir/main.cpp.o: CMakeFiles/Floyd.dir/flags.make
CMakeFiles/Floyd.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Floyd.dir/main.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Floyd.dir/main.cpp.o -c "/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd/main.cpp"

CMakeFiles/Floyd.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Floyd.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd/main.cpp" > CMakeFiles/Floyd.dir/main.cpp.i

CMakeFiles/Floyd.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Floyd.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd/main.cpp" -o CMakeFiles/Floyd.dir/main.cpp.s

# Object files for target Floyd
Floyd_OBJECTS = \
"CMakeFiles/Floyd.dir/main.cpp.o"

# External object files for target Floyd
Floyd_EXTERNAL_OBJECTS =

Floyd.exe: CMakeFiles/Floyd.dir/main.cpp.o
Floyd.exe: CMakeFiles/Floyd.dir/build.make
Floyd.exe: CMakeFiles/Floyd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Floyd.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Floyd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Floyd.dir/build: Floyd.exe

.PHONY : CMakeFiles/Floyd.dir/build

CMakeFiles/Floyd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Floyd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Floyd.dir/clean

CMakeFiles/Floyd.dir/depend:
	cd "/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd" "/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd" "/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd/cmake-build-debug" "/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd/cmake-build-debug" "/cygdrive/c/Users/pankin/Desktop/Programming methods Practice/Floyd/cmake-build-debug/CMakeFiles/Floyd.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Floyd.dir/depend
