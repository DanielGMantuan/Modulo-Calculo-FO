# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\NOTE155\source\personal\teste

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\NOTE155\source\personal\teste\build

# Include any dependencies generated for this target.
include CMakeFiles/meu_modulo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/meu_modulo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/meu_modulo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/meu_modulo.dir/flags.make

CMakeFiles/meu_modulo.dir/codegen:
.PHONY : CMakeFiles/meu_modulo.dir/codegen

CMakeFiles/meu_modulo.dir/src/meu_modulo.cpp.obj: CMakeFiles/meu_modulo.dir/flags.make
CMakeFiles/meu_modulo.dir/src/meu_modulo.cpp.obj: CMakeFiles/meu_modulo.dir/includes_CXX.rsp
CMakeFiles/meu_modulo.dir/src/meu_modulo.cpp.obj: C:/Users/NOTE155/source/personal/teste/src/meu_modulo.cpp
CMakeFiles/meu_modulo.dir/src/meu_modulo.cpp.obj: CMakeFiles/meu_modulo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\NOTE155\source\personal\teste\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/meu_modulo.dir/src/meu_modulo.cpp.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/meu_modulo.dir/src/meu_modulo.cpp.obj -MF CMakeFiles\meu_modulo.dir\src\meu_modulo.cpp.obj.d -o CMakeFiles\meu_modulo.dir\src\meu_modulo.cpp.obj -c C:\Users\NOTE155\source\personal\teste\src\meu_modulo.cpp

CMakeFiles/meu_modulo.dir/src/meu_modulo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/meu_modulo.dir/src/meu_modulo.cpp.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\NOTE155\source\personal\teste\src\meu_modulo.cpp > CMakeFiles\meu_modulo.dir\src\meu_modulo.cpp.i

CMakeFiles/meu_modulo.dir/src/meu_modulo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/meu_modulo.dir/src/meu_modulo.cpp.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\NOTE155\source\personal\teste\src\meu_modulo.cpp -o CMakeFiles\meu_modulo.dir\src\meu_modulo.cpp.s

# Object files for target meu_modulo
meu_modulo_OBJECTS = \
"CMakeFiles/meu_modulo.dir/src/meu_modulo.cpp.obj"

# External object files for target meu_modulo
meu_modulo_EXTERNAL_OBJECTS =

meu_modulo.cp310-win_amd64.pyd: CMakeFiles/meu_modulo.dir/src/meu_modulo.cpp.obj
meu_modulo.cp310-win_amd64.pyd: CMakeFiles/meu_modulo.dir/build.make
meu_modulo.cp310-win_amd64.pyd: C:/Users/NOTE155/AppData/Local/Programs/Python/Python310/libs/python310.lib
meu_modulo.cp310-win_amd64.pyd: CMakeFiles/meu_modulo.dir/linkLibs.rsp
meu_modulo.cp310-win_amd64.pyd: CMakeFiles/meu_modulo.dir/objects1.rsp
meu_modulo.cp310-win_amd64.pyd: CMakeFiles/meu_modulo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\NOTE155\source\personal\teste\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module meu_modulo.cp310-win_amd64.pyd"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\meu_modulo.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/meu_modulo.dir/build: meu_modulo.cp310-win_amd64.pyd
.PHONY : CMakeFiles/meu_modulo.dir/build

CMakeFiles/meu_modulo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\meu_modulo.dir\cmake_clean.cmake
.PHONY : CMakeFiles/meu_modulo.dir/clean

CMakeFiles/meu_modulo.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\NOTE155\source\personal\teste C:\Users\NOTE155\source\personal\teste C:\Users\NOTE155\source\personal\teste\build C:\Users\NOTE155\source\personal\teste\build C:\Users\NOTE155\source\personal\teste\build\CMakeFiles\meu_modulo.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/meu_modulo.dir/depend

