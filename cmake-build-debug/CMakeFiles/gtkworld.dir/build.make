# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/dusan/clion-2017.2.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/dusan/clion-2017.2.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dusan/Desktop/clion_git

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dusan/Desktop/clion_git/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/gtkworld.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gtkworld.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gtkworld.dir/flags.make

CMakeFiles/gtkworld.dir/client.c.o: CMakeFiles/gtkworld.dir/flags.make
CMakeFiles/gtkworld.dir/client.c.o: ../client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dusan/Desktop/clion_git/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/gtkworld.dir/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld.dir/client.c.o   -c /home/dusan/Desktop/clion_git/client.c

CMakeFiles/gtkworld.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld.dir/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dusan/Desktop/clion_git/client.c > CMakeFiles/gtkworld.dir/client.c.i

CMakeFiles/gtkworld.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld.dir/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dusan/Desktop/clion_git/client.c -o CMakeFiles/gtkworld.dir/client.c.s

CMakeFiles/gtkworld.dir/client.c.o.requires:

.PHONY : CMakeFiles/gtkworld.dir/client.c.o.requires

CMakeFiles/gtkworld.dir/client.c.o.provides: CMakeFiles/gtkworld.dir/client.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld.dir/build.make CMakeFiles/gtkworld.dir/client.c.o.provides.build
.PHONY : CMakeFiles/gtkworld.dir/client.c.o.provides

CMakeFiles/gtkworld.dir/client.c.o.provides.build: CMakeFiles/gtkworld.dir/client.c.o


CMakeFiles/gtkworld.dir/interrupts.c.o: CMakeFiles/gtkworld.dir/flags.make
CMakeFiles/gtkworld.dir/interrupts.c.o: ../interrupts.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dusan/Desktop/clion_git/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/gtkworld.dir/interrupts.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld.dir/interrupts.c.o   -c /home/dusan/Desktop/clion_git/interrupts.c

CMakeFiles/gtkworld.dir/interrupts.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld.dir/interrupts.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dusan/Desktop/clion_git/interrupts.c > CMakeFiles/gtkworld.dir/interrupts.c.i

CMakeFiles/gtkworld.dir/interrupts.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld.dir/interrupts.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dusan/Desktop/clion_git/interrupts.c -o CMakeFiles/gtkworld.dir/interrupts.c.s

CMakeFiles/gtkworld.dir/interrupts.c.o.requires:

.PHONY : CMakeFiles/gtkworld.dir/interrupts.c.o.requires

CMakeFiles/gtkworld.dir/interrupts.c.o.provides: CMakeFiles/gtkworld.dir/interrupts.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld.dir/build.make CMakeFiles/gtkworld.dir/interrupts.c.o.provides.build
.PHONY : CMakeFiles/gtkworld.dir/interrupts.c.o.provides

CMakeFiles/gtkworld.dir/interrupts.c.o.provides.build: CMakeFiles/gtkworld.dir/interrupts.c.o


CMakeFiles/gtkworld.dir/drawing.c.o: CMakeFiles/gtkworld.dir/flags.make
CMakeFiles/gtkworld.dir/drawing.c.o: ../drawing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dusan/Desktop/clion_git/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/gtkworld.dir/drawing.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld.dir/drawing.c.o   -c /home/dusan/Desktop/clion_git/drawing.c

CMakeFiles/gtkworld.dir/drawing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld.dir/drawing.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dusan/Desktop/clion_git/drawing.c > CMakeFiles/gtkworld.dir/drawing.c.i

CMakeFiles/gtkworld.dir/drawing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld.dir/drawing.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dusan/Desktop/clion_git/drawing.c -o CMakeFiles/gtkworld.dir/drawing.c.s

CMakeFiles/gtkworld.dir/drawing.c.o.requires:

.PHONY : CMakeFiles/gtkworld.dir/drawing.c.o.requires

CMakeFiles/gtkworld.dir/drawing.c.o.provides: CMakeFiles/gtkworld.dir/drawing.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld.dir/build.make CMakeFiles/gtkworld.dir/drawing.c.o.provides.build
.PHONY : CMakeFiles/gtkworld.dir/drawing.c.o.provides

CMakeFiles/gtkworld.dir/drawing.c.o.provides.build: CMakeFiles/gtkworld.dir/drawing.c.o


CMakeFiles/gtkworld.dir/buttons.c.o: CMakeFiles/gtkworld.dir/flags.make
CMakeFiles/gtkworld.dir/buttons.c.o: ../buttons.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dusan/Desktop/clion_git/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/gtkworld.dir/buttons.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld.dir/buttons.c.o   -c /home/dusan/Desktop/clion_git/buttons.c

CMakeFiles/gtkworld.dir/buttons.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld.dir/buttons.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dusan/Desktop/clion_git/buttons.c > CMakeFiles/gtkworld.dir/buttons.c.i

CMakeFiles/gtkworld.dir/buttons.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld.dir/buttons.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dusan/Desktop/clion_git/buttons.c -o CMakeFiles/gtkworld.dir/buttons.c.s

CMakeFiles/gtkworld.dir/buttons.c.o.requires:

.PHONY : CMakeFiles/gtkworld.dir/buttons.c.o.requires

CMakeFiles/gtkworld.dir/buttons.c.o.provides: CMakeFiles/gtkworld.dir/buttons.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld.dir/build.make CMakeFiles/gtkworld.dir/buttons.c.o.provides.build
.PHONY : CMakeFiles/gtkworld.dir/buttons.c.o.provides

CMakeFiles/gtkworld.dir/buttons.c.o.provides.build: CMakeFiles/gtkworld.dir/buttons.c.o


CMakeFiles/gtkworld.dir/testing_tree.c.o: CMakeFiles/gtkworld.dir/flags.make
CMakeFiles/gtkworld.dir/testing_tree.c.o: ../testing_tree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dusan/Desktop/clion_git/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/gtkworld.dir/testing_tree.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld.dir/testing_tree.c.o   -c /home/dusan/Desktop/clion_git/testing_tree.c

CMakeFiles/gtkworld.dir/testing_tree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld.dir/testing_tree.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dusan/Desktop/clion_git/testing_tree.c > CMakeFiles/gtkworld.dir/testing_tree.c.i

CMakeFiles/gtkworld.dir/testing_tree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld.dir/testing_tree.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dusan/Desktop/clion_git/testing_tree.c -o CMakeFiles/gtkworld.dir/testing_tree.c.s

CMakeFiles/gtkworld.dir/testing_tree.c.o.requires:

.PHONY : CMakeFiles/gtkworld.dir/testing_tree.c.o.requires

CMakeFiles/gtkworld.dir/testing_tree.c.o.provides: CMakeFiles/gtkworld.dir/testing_tree.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld.dir/build.make CMakeFiles/gtkworld.dir/testing_tree.c.o.provides.build
.PHONY : CMakeFiles/gtkworld.dir/testing_tree.c.o.provides

CMakeFiles/gtkworld.dir/testing_tree.c.o.provides.build: CMakeFiles/gtkworld.dir/testing_tree.c.o


CMakeFiles/gtkworld.dir/window.c.o: CMakeFiles/gtkworld.dir/flags.make
CMakeFiles/gtkworld.dir/window.c.o: ../window.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dusan/Desktop/clion_git/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/gtkworld.dir/window.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld.dir/window.c.o   -c /home/dusan/Desktop/clion_git/window.c

CMakeFiles/gtkworld.dir/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld.dir/window.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dusan/Desktop/clion_git/window.c > CMakeFiles/gtkworld.dir/window.c.i

CMakeFiles/gtkworld.dir/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld.dir/window.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dusan/Desktop/clion_git/window.c -o CMakeFiles/gtkworld.dir/window.c.s

CMakeFiles/gtkworld.dir/window.c.o.requires:

.PHONY : CMakeFiles/gtkworld.dir/window.c.o.requires

CMakeFiles/gtkworld.dir/window.c.o.provides: CMakeFiles/gtkworld.dir/window.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld.dir/build.make CMakeFiles/gtkworld.dir/window.c.o.provides.build
.PHONY : CMakeFiles/gtkworld.dir/window.c.o.provides

CMakeFiles/gtkworld.dir/window.c.o.provides.build: CMakeFiles/gtkworld.dir/window.c.o


# Object files for target gtkworld
gtkworld_OBJECTS = \
"CMakeFiles/gtkworld.dir/client.c.o" \
"CMakeFiles/gtkworld.dir/interrupts.c.o" \
"CMakeFiles/gtkworld.dir/drawing.c.o" \
"CMakeFiles/gtkworld.dir/buttons.c.o" \
"CMakeFiles/gtkworld.dir/testing_tree.c.o" \
"CMakeFiles/gtkworld.dir/window.c.o"

# External object files for target gtkworld
gtkworld_EXTERNAL_OBJECTS =

gtkworld: CMakeFiles/gtkworld.dir/client.c.o
gtkworld: CMakeFiles/gtkworld.dir/interrupts.c.o
gtkworld: CMakeFiles/gtkworld.dir/drawing.c.o
gtkworld: CMakeFiles/gtkworld.dir/buttons.c.o
gtkworld: CMakeFiles/gtkworld.dir/testing_tree.c.o
gtkworld: CMakeFiles/gtkworld.dir/window.c.o
gtkworld: CMakeFiles/gtkworld.dir/build.make
gtkworld: CMakeFiles/gtkworld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dusan/Desktop/clion_git/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable gtkworld"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtkworld.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gtkworld.dir/build: gtkworld

.PHONY : CMakeFiles/gtkworld.dir/build

CMakeFiles/gtkworld.dir/requires: CMakeFiles/gtkworld.dir/client.c.o.requires
CMakeFiles/gtkworld.dir/requires: CMakeFiles/gtkworld.dir/interrupts.c.o.requires
CMakeFiles/gtkworld.dir/requires: CMakeFiles/gtkworld.dir/drawing.c.o.requires
CMakeFiles/gtkworld.dir/requires: CMakeFiles/gtkworld.dir/buttons.c.o.requires
CMakeFiles/gtkworld.dir/requires: CMakeFiles/gtkworld.dir/testing_tree.c.o.requires
CMakeFiles/gtkworld.dir/requires: CMakeFiles/gtkworld.dir/window.c.o.requires

.PHONY : CMakeFiles/gtkworld.dir/requires

CMakeFiles/gtkworld.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gtkworld.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gtkworld.dir/clean

CMakeFiles/gtkworld.dir/depend:
	cd /home/dusan/Desktop/clion_git/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dusan/Desktop/clion_git /home/dusan/Desktop/clion_git /home/dusan/Desktop/clion_git/cmake-build-debug /home/dusan/Desktop/clion_git/cmake-build-debug /home/dusan/Desktop/clion_git/cmake-build-debug/CMakeFiles/gtkworld.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gtkworld.dir/depend

