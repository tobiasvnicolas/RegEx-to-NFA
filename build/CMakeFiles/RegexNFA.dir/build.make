# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = "C:\Users\Usuario\Desktop\Facultad\3 ANIO\Lenguajes Formales y Automatas\RegexNFA"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Usuario\Desktop\Facultad\3 ANIO\Lenguajes Formales y Automatas\RegexNFA\build"

# Include any dependencies generated for this target.
include CMakeFiles/RegexNFA.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RegexNFA.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RegexNFA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RegexNFA.dir/flags.make

CMakeFiles/RegexNFA.dir/main.cpp.obj: CMakeFiles/RegexNFA.dir/flags.make
CMakeFiles/RegexNFA.dir/main.cpp.obj: CMakeFiles/RegexNFA.dir/includes_CXX.rsp
CMakeFiles/RegexNFA.dir/main.cpp.obj: C:/Users/Usuario/Desktop/Facultad/3\ ANIO/Lenguajes\ Formales\ y\ Automatas/RegexNFA/main.cpp
CMakeFiles/RegexNFA.dir/main.cpp.obj: CMakeFiles/RegexNFA.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\Usuario\Desktop\Facultad\3 ANIO\Lenguajes Formales y Automatas\RegexNFA\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RegexNFA.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RegexNFA.dir/main.cpp.obj -MF CMakeFiles\RegexNFA.dir\main.cpp.obj.d -o CMakeFiles\RegexNFA.dir\main.cpp.obj -c "C:\Users\Usuario\Desktop\Facultad\3 ANIO\Lenguajes Formales y Automatas\RegexNFA\main.cpp"

CMakeFiles/RegexNFA.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/RegexNFA.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Usuario\Desktop\Facultad\3 ANIO\Lenguajes Formales y Automatas\RegexNFA\main.cpp" > CMakeFiles\RegexNFA.dir\main.cpp.i

CMakeFiles/RegexNFA.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/RegexNFA.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Usuario\Desktop\Facultad\3 ANIO\Lenguajes Formales y Automatas\RegexNFA\main.cpp" -o CMakeFiles\RegexNFA.dir\main.cpp.s

# Object files for target RegexNFA
RegexNFA_OBJECTS = \
"CMakeFiles/RegexNFA.dir/main.cpp.obj"

# External object files for target RegexNFA
RegexNFA_EXTERNAL_OBJECTS =

RegexNFA.exe: CMakeFiles/RegexNFA.dir/main.cpp.obj
RegexNFA.exe: CMakeFiles/RegexNFA.dir/build.make
RegexNFA.exe: CMakeFiles/RegexNFA.dir/linkLibs.rsp
RegexNFA.exe: CMakeFiles/RegexNFA.dir/objects1.rsp
RegexNFA.exe: CMakeFiles/RegexNFA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\Usuario\Desktop\Facultad\3 ANIO\Lenguajes Formales y Automatas\RegexNFA\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RegexNFA.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\RegexNFA.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RegexNFA.dir/build: RegexNFA.exe
.PHONY : CMakeFiles/RegexNFA.dir/build

CMakeFiles/RegexNFA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\RegexNFA.dir\cmake_clean.cmake
.PHONY : CMakeFiles/RegexNFA.dir/clean

CMakeFiles/RegexNFA.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Usuario\Desktop\Facultad\3 ANIO\Lenguajes Formales y Automatas\RegexNFA" "C:\Users\Usuario\Desktop\Facultad\3 ANIO\Lenguajes Formales y Automatas\RegexNFA" "C:\Users\Usuario\Desktop\Facultad\3 ANIO\Lenguajes Formales y Automatas\RegexNFA\build" "C:\Users\Usuario\Desktop\Facultad\3 ANIO\Lenguajes Formales y Automatas\RegexNFA\build" "C:\Users\Usuario\Desktop\Facultad\3 ANIO\Lenguajes Formales y Automatas\RegexNFA\build\CMakeFiles\RegexNFA.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/RegexNFA.dir/depend

