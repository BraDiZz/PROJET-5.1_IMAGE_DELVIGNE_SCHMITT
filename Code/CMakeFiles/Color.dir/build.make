# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code

# Include any dependencies generated for this target.
include CMakeFiles/Color.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Color.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Color.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Color.dir/flags.make

CMakeFiles/Color.dir/src/Color.cpp.o: CMakeFiles/Color.dir/flags.make
CMakeFiles/Color.dir/src/Color.cpp.o: src/Color.cpp
CMakeFiles/Color.dir/src/Color.cpp.o: CMakeFiles/Color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Color.dir/src/Color.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Color.dir/src/Color.cpp.o -MF CMakeFiles/Color.dir/src/Color.cpp.o.d -o CMakeFiles/Color.dir/src/Color.cpp.o -c /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Color.cpp

CMakeFiles/Color.dir/src/Color.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Color.dir/src/Color.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Color.cpp > CMakeFiles/Color.dir/src/Color.cpp.i

CMakeFiles/Color.dir/src/Color.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Color.dir/src/Color.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Color.cpp -o CMakeFiles/Color.dir/src/Color.cpp.s

CMakeFiles/Color.dir/src/ColorImage.cpp.o: CMakeFiles/Color.dir/flags.make
CMakeFiles/Color.dir/src/ColorImage.cpp.o: src/ColorImage.cpp
CMakeFiles/Color.dir/src/ColorImage.cpp.o: CMakeFiles/Color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Color.dir/src/ColorImage.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Color.dir/src/ColorImage.cpp.o -MF CMakeFiles/Color.dir/src/ColorImage.cpp.o.d -o CMakeFiles/Color.dir/src/ColorImage.cpp.o -c /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/ColorImage.cpp

CMakeFiles/Color.dir/src/ColorImage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Color.dir/src/ColorImage.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/ColorImage.cpp > CMakeFiles/Color.dir/src/ColorImage.cpp.i

CMakeFiles/Color.dir/src/ColorImage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Color.dir/src/ColorImage.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/ColorImage.cpp -o CMakeFiles/Color.dir/src/ColorImage.cpp.s

CMakeFiles/Color.dir/src/ColorScheme.cpp.o: CMakeFiles/Color.dir/flags.make
CMakeFiles/Color.dir/src/ColorScheme.cpp.o: src/ColorScheme.cpp
CMakeFiles/Color.dir/src/ColorScheme.cpp.o: CMakeFiles/Color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Color.dir/src/ColorScheme.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Color.dir/src/ColorScheme.cpp.o -MF CMakeFiles/Color.dir/src/ColorScheme.cpp.o.d -o CMakeFiles/Color.dir/src/ColorScheme.cpp.o -c /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/ColorScheme.cpp

CMakeFiles/Color.dir/src/ColorScheme.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Color.dir/src/ColorScheme.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/ColorScheme.cpp > CMakeFiles/Color.dir/src/ColorScheme.cpp.i

CMakeFiles/Color.dir/src/ColorScheme.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Color.dir/src/ColorScheme.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/ColorScheme.cpp -o CMakeFiles/Color.dir/src/ColorScheme.cpp.s

CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.o: CMakeFiles/Color.dir/flags.make
CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.o: src/ColorSchemeConverter.cpp
CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.o: CMakeFiles/Color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.o -MF CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.o.d -o CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.o -c /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/ColorSchemeConverter.cpp

CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/ColorSchemeConverter.cpp > CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.i

CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/ColorSchemeConverter.cpp -o CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.s

CMakeFiles/Color.dir/src/HueSmother.cpp.o: CMakeFiles/Color.dir/flags.make
CMakeFiles/Color.dir/src/HueSmother.cpp.o: src/HueSmother.cpp
CMakeFiles/Color.dir/src/HueSmother.cpp.o: CMakeFiles/Color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Color.dir/src/HueSmother.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Color.dir/src/HueSmother.cpp.o -MF CMakeFiles/Color.dir/src/HueSmother.cpp.o.d -o CMakeFiles/Color.dir/src/HueSmother.cpp.o -c /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/HueSmother.cpp

CMakeFiles/Color.dir/src/HueSmother.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Color.dir/src/HueSmother.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/HueSmother.cpp > CMakeFiles/Color.dir/src/HueSmother.cpp.i

CMakeFiles/Color.dir/src/HueSmother.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Color.dir/src/HueSmother.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/HueSmother.cpp -o CMakeFiles/Color.dir/src/HueSmother.cpp.s

CMakeFiles/Color.dir/src/Image_ppm.cpp.o: CMakeFiles/Color.dir/flags.make
CMakeFiles/Color.dir/src/Image_ppm.cpp.o: src/Image_ppm.cpp
CMakeFiles/Color.dir/src/Image_ppm.cpp.o: CMakeFiles/Color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Color.dir/src/Image_ppm.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Color.dir/src/Image_ppm.cpp.o -MF CMakeFiles/Color.dir/src/Image_ppm.cpp.o.d -o CMakeFiles/Color.dir/src/Image_ppm.cpp.o -c /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Image_ppm.cpp

CMakeFiles/Color.dir/src/Image_ppm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Color.dir/src/Image_ppm.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Image_ppm.cpp > CMakeFiles/Color.dir/src/Image_ppm.cpp.i

CMakeFiles/Color.dir/src/Image_ppm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Color.dir/src/Image_ppm.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Image_ppm.cpp -o CMakeFiles/Color.dir/src/Image_ppm.cpp.s

CMakeFiles/Color.dir/src/Test.cpp.o: CMakeFiles/Color.dir/flags.make
CMakeFiles/Color.dir/src/Test.cpp.o: src/Test.cpp
CMakeFiles/Color.dir/src/Test.cpp.o: CMakeFiles/Color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Color.dir/src/Test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Color.dir/src/Test.cpp.o -MF CMakeFiles/Color.dir/src/Test.cpp.o.d -o CMakeFiles/Color.dir/src/Test.cpp.o -c /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Test.cpp

CMakeFiles/Color.dir/src/Test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Color.dir/src/Test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Test.cpp > CMakeFiles/Color.dir/src/Test.cpp.i

CMakeFiles/Color.dir/src/Test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Color.dir/src/Test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/Test.cpp -o CMakeFiles/Color.dir/src/Test.cpp.s

CMakeFiles/Color.dir/src/main.cpp.o: CMakeFiles/Color.dir/flags.make
CMakeFiles/Color.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/Color.dir/src/main.cpp.o: CMakeFiles/Color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Color.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Color.dir/src/main.cpp.o -MF CMakeFiles/Color.dir/src/main.cpp.o.d -o CMakeFiles/Color.dir/src/main.cpp.o -c /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/main.cpp

CMakeFiles/Color.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Color.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/main.cpp > CMakeFiles/Color.dir/src/main.cpp.i

CMakeFiles/Color.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Color.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/src/main.cpp -o CMakeFiles/Color.dir/src/main.cpp.s

# Object files for target Color
Color_OBJECTS = \
"CMakeFiles/Color.dir/src/Color.cpp.o" \
"CMakeFiles/Color.dir/src/ColorImage.cpp.o" \
"CMakeFiles/Color.dir/src/ColorScheme.cpp.o" \
"CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.o" \
"CMakeFiles/Color.dir/src/HueSmother.cpp.o" \
"CMakeFiles/Color.dir/src/Image_ppm.cpp.o" \
"CMakeFiles/Color.dir/src/Test.cpp.o" \
"CMakeFiles/Color.dir/src/main.cpp.o"

# External object files for target Color
Color_EXTERNAL_OBJECTS =

Color: CMakeFiles/Color.dir/src/Color.cpp.o
Color: CMakeFiles/Color.dir/src/ColorImage.cpp.o
Color: CMakeFiles/Color.dir/src/ColorScheme.cpp.o
Color: CMakeFiles/Color.dir/src/ColorSchemeConverter.cpp.o
Color: CMakeFiles/Color.dir/src/HueSmother.cpp.o
Color: CMakeFiles/Color.dir/src/Image_ppm.cpp.o
Color: CMakeFiles/Color.dir/src/Test.cpp.o
Color: CMakeFiles/Color.dir/src/main.cpp.o
Color: CMakeFiles/Color.dir/build.make
Color: CMakeFiles/Color.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable Color"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Color.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Color.dir/build: Color
.PHONY : CMakeFiles/Color.dir/build

CMakeFiles/Color.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Color.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Color.dir/clean

CMakeFiles/Color.dir/depend:
	cd /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code /home/e20230010831/Bureau/PROJET-5.1_IMAGE_DELVIGNE_SCHMITT/Code/CMakeFiles/Color.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Color.dir/depend

