# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = C:\Users\david\Desktop\Gioco-Scacchi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\david\Desktop\Gioco-Scacchi\build

# Include any dependencies generated for this target.
include CMakeFiles/PedinaL.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PedinaL.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PedinaL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PedinaL.dir/flags.make

CMakeFiles/PedinaL.dir/src/Pedina.cpp.obj: CMakeFiles/PedinaL.dir/flags.make
CMakeFiles/PedinaL.dir/src/Pedina.cpp.obj: CMakeFiles/PedinaL.dir/includes_CXX.rsp
CMakeFiles/PedinaL.dir/src/Pedina.cpp.obj: ../src/Pedina.cpp
CMakeFiles/PedinaL.dir/src/Pedina.cpp.obj: CMakeFiles/PedinaL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\david\Desktop\Gioco-Scacchi\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PedinaL.dir/src/Pedina.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PedinaL.dir/src/Pedina.cpp.obj -MF CMakeFiles\PedinaL.dir\src\Pedina.cpp.obj.d -o CMakeFiles\PedinaL.dir\src\Pedina.cpp.obj -c C:\Users\david\Desktop\Gioco-Scacchi\src\Pedina.cpp

CMakeFiles/PedinaL.dir/src/Pedina.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PedinaL.dir/src/Pedina.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\david\Desktop\Gioco-Scacchi\src\Pedina.cpp > CMakeFiles\PedinaL.dir\src\Pedina.cpp.i

CMakeFiles/PedinaL.dir/src/Pedina.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PedinaL.dir/src/Pedina.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\david\Desktop\Gioco-Scacchi\src\Pedina.cpp -o CMakeFiles\PedinaL.dir\src\Pedina.cpp.s

# Object files for target PedinaL
PedinaL_OBJECTS = \
"CMakeFiles/PedinaL.dir/src/Pedina.cpp.obj"

# External object files for target PedinaL
PedinaL_EXTERNAL_OBJECTS =

libPedinaL.a: CMakeFiles/PedinaL.dir/src/Pedina.cpp.obj
libPedinaL.a: CMakeFiles/PedinaL.dir/build.make
libPedinaL.a: CMakeFiles/PedinaL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\david\Desktop\Gioco-Scacchi\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libPedinaL.a"
	$(CMAKE_COMMAND) -P CMakeFiles\PedinaL.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\PedinaL.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PedinaL.dir/build: libPedinaL.a
.PHONY : CMakeFiles/PedinaL.dir/build

CMakeFiles/PedinaL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\PedinaL.dir\cmake_clean.cmake
.PHONY : CMakeFiles/PedinaL.dir/clean

CMakeFiles/PedinaL.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\david\Desktop\Gioco-Scacchi C:\Users\david\Desktop\Gioco-Scacchi C:\Users\david\Desktop\Gioco-Scacchi\build C:\Users\david\Desktop\Gioco-Scacchi\build C:\Users\david\Desktop\Gioco-Scacchi\build\CMakeFiles\PedinaL.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PedinaL.dir/depend

