# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/miron/MIRON-Project/engine-workspace/Adaptation-Engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/miron/MIRON-Project/engine-workspace/Adaptation-Engine/build

# Include any dependencies generated for this target.
include CMakeFiles/AdaptationEngine_engine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AdaptationEngine_engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AdaptationEngine_engine.dir/flags.make

CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o: CMakeFiles/AdaptationEngine_engine.dir/flags.make
CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o: ../Adaptation-Engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/miron/MIRON-Project/engine-workspace/Adaptation-Engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o -c /home/miron/MIRON-Project/engine-workspace/Adaptation-Engine/Adaptation-Engine.cpp

CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miron/MIRON-Project/engine-workspace/Adaptation-Engine/Adaptation-Engine.cpp > CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.i

CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miron/MIRON-Project/engine-workspace/Adaptation-Engine/Adaptation-Engine.cpp -o CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.s

CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o.requires:

.PHONY : CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o.requires

CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o.provides: CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o.requires
	$(MAKE) -f CMakeFiles/AdaptationEngine_engine.dir/build.make CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o.provides.build
.PHONY : CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o.provides

CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o.provides.build: CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o


# Object files for target AdaptationEngine_engine
AdaptationEngine_engine_OBJECTS = \
"CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o"

# External object files for target AdaptationEngine_engine
AdaptationEngine_engine_EXTERNAL_OBJECTS =

AdaptationEngine_engine: CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o
AdaptationEngine_engine: CMakeFiles/AdaptationEngine_engine.dir/build.make
AdaptationEngine_engine: CMakeFiles/AdaptationEngine_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/miron/MIRON-Project/engine-workspace/Adaptation-Engine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AdaptationEngine_engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AdaptationEngine_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AdaptationEngine_engine.dir/build: AdaptationEngine_engine

.PHONY : CMakeFiles/AdaptationEngine_engine.dir/build

CMakeFiles/AdaptationEngine_engine.dir/requires: CMakeFiles/AdaptationEngine_engine.dir/Adaptation-Engine.cpp.o.requires

.PHONY : CMakeFiles/AdaptationEngine_engine.dir/requires

CMakeFiles/AdaptationEngine_engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AdaptationEngine_engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AdaptationEngine_engine.dir/clean

CMakeFiles/AdaptationEngine_engine.dir/depend:
	cd /home/miron/MIRON-Project/engine-workspace/Adaptation-Engine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/miron/MIRON-Project/engine-workspace/Adaptation-Engine /home/miron/MIRON-Project/engine-workspace/Adaptation-Engine /home/miron/MIRON-Project/engine-workspace/Adaptation-Engine/build /home/miron/MIRON-Project/engine-workspace/Adaptation-Engine/build /home/miron/MIRON-Project/engine-workspace/Adaptation-Engine/build/CMakeFiles/AdaptationEngine_engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AdaptationEngine_engine.dir/depend

