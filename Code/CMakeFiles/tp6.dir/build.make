# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code

# Include any dependencies generated for this target.
include CMakeFiles/tp6.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tp6.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tp6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tp6.dir/flags.make

CMakeFiles/tp6.dir/src/Image_ppm.cpp.o: CMakeFiles/tp6.dir/flags.make
CMakeFiles/tp6.dir/src/Image_ppm.cpp.o: src/Image_ppm.cpp
CMakeFiles/tp6.dir/src/Image_ppm.cpp.o: CMakeFiles/tp6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tp6.dir/src/Image_ppm.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tp6.dir/src/Image_ppm.cpp.o -MF CMakeFiles/tp6.dir/src/Image_ppm.cpp.o.d -o CMakeFiles/tp6.dir/src/Image_ppm.cpp.o -c /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Image_ppm.cpp

CMakeFiles/tp6.dir/src/Image_ppm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tp6.dir/src/Image_ppm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Image_ppm.cpp > CMakeFiles/tp6.dir/src/Image_ppm.cpp.i

CMakeFiles/tp6.dir/src/Image_ppm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tp6.dir/src/Image_ppm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Image_ppm.cpp -o CMakeFiles/tp6.dir/src/Image_ppm.cpp.s

CMakeFiles/tp6.dir/src/Test.cpp.o: CMakeFiles/tp6.dir/flags.make
CMakeFiles/tp6.dir/src/Test.cpp.o: src/Test.cpp
CMakeFiles/tp6.dir/src/Test.cpp.o: CMakeFiles/tp6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tp6.dir/src/Test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tp6.dir/src/Test.cpp.o -MF CMakeFiles/tp6.dir/src/Test.cpp.o.d -o CMakeFiles/tp6.dir/src/Test.cpp.o -c /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Test.cpp

CMakeFiles/tp6.dir/src/Test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tp6.dir/src/Test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Test.cpp > CMakeFiles/tp6.dir/src/Test.cpp.i

CMakeFiles/tp6.dir/src/Test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tp6.dir/src/Test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Test.cpp -o CMakeFiles/tp6.dir/src/Test.cpp.s

CMakeFiles/tp6.dir/src/main.cpp.o: CMakeFiles/tp6.dir/flags.make
CMakeFiles/tp6.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/tp6.dir/src/main.cpp.o: CMakeFiles/tp6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tp6.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/tp6.dir/src/main.cpp.o -MF CMakeFiles/tp6.dir/src/main.cpp.o.d -o CMakeFiles/tp6.dir/src/main.cpp.o -c /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/main.cpp

CMakeFiles/tp6.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tp6.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/main.cpp > CMakeFiles/tp6.dir/src/main.cpp.i

CMakeFiles/tp6.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tp6.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/main.cpp -o CMakeFiles/tp6.dir/src/main.cpp.s

# Object files for target tp6
tp6_OBJECTS = \
"CMakeFiles/tp6.dir/src/Image_ppm.cpp.o" \
"CMakeFiles/tp6.dir/src/Test.cpp.o" \
"CMakeFiles/tp6.dir/src/main.cpp.o"

# External object files for target tp6
tp6_EXTERNAL_OBJECTS =

tp6: CMakeFiles/tp6.dir/src/Image_ppm.cpp.o
tp6: CMakeFiles/tp6.dir/src/Test.cpp.o
tp6: CMakeFiles/tp6.dir/src/main.cpp.o
tp6: CMakeFiles/tp6.dir/build.make
tp6: CMakeFiles/tp6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable tp6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tp6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tp6.dir/build: tp6
.PHONY : CMakeFiles/tp6.dir/build

CMakeFiles/tp6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tp6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tp6.dir/clean

CMakeFiles/tp6.dir/depend:
	cd /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code /home/vincent/Dokumente/Uni/Compression/Project/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles/tp6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tp6.dir/depend
