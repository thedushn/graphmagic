# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/dushn/clion/clion-2017.1.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/dushn/clion/clion-2017.1.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/gtkworld_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gtkworld_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gtkworld_1.dir/flags.make

CMakeFiles/gtkworld_1.dir/client.c.o: CMakeFiles/gtkworld_1.dir/flags.make
CMakeFiles/gtkworld_1.dir/client.c.o: ../client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/gtkworld_1.dir/client.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld_1.dir/client.c.o   -c /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/client.c

CMakeFiles/gtkworld_1.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld_1.dir/client.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/client.c > CMakeFiles/gtkworld_1.dir/client.c.i

CMakeFiles/gtkworld_1.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld_1.dir/client.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/client.c -o CMakeFiles/gtkworld_1.dir/client.c.s

CMakeFiles/gtkworld_1.dir/client.c.o.requires:

.PHONY : CMakeFiles/gtkworld_1.dir/client.c.o.requires

CMakeFiles/gtkworld_1.dir/client.c.o.provides: CMakeFiles/gtkworld_1.dir/client.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld_1.dir/build.make CMakeFiles/gtkworld_1.dir/client.c.o.provides.build
.PHONY : CMakeFiles/gtkworld_1.dir/client.c.o.provides

CMakeFiles/gtkworld_1.dir/client.c.o.provides.build: CMakeFiles/gtkworld_1.dir/client.c.o


CMakeFiles/gtkworld_1.dir/interrupts.c.o: CMakeFiles/gtkworld_1.dir/flags.make
CMakeFiles/gtkworld_1.dir/interrupts.c.o: ../interrupts.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/gtkworld_1.dir/interrupts.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld_1.dir/interrupts.c.o   -c /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/interrupts.c

CMakeFiles/gtkworld_1.dir/interrupts.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld_1.dir/interrupts.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/interrupts.c > CMakeFiles/gtkworld_1.dir/interrupts.c.i

CMakeFiles/gtkworld_1.dir/interrupts.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld_1.dir/interrupts.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/interrupts.c -o CMakeFiles/gtkworld_1.dir/interrupts.c.s

CMakeFiles/gtkworld_1.dir/interrupts.c.o.requires:

.PHONY : CMakeFiles/gtkworld_1.dir/interrupts.c.o.requires

CMakeFiles/gtkworld_1.dir/interrupts.c.o.provides: CMakeFiles/gtkworld_1.dir/interrupts.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld_1.dir/build.make CMakeFiles/gtkworld_1.dir/interrupts.c.o.provides.build
.PHONY : CMakeFiles/gtkworld_1.dir/interrupts.c.o.provides

CMakeFiles/gtkworld_1.dir/interrupts.c.o.provides.build: CMakeFiles/gtkworld_1.dir/interrupts.c.o


CMakeFiles/gtkworld_1.dir/drawing.c.o: CMakeFiles/gtkworld_1.dir/flags.make
CMakeFiles/gtkworld_1.dir/drawing.c.o: ../drawing.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/gtkworld_1.dir/drawing.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld_1.dir/drawing.c.o   -c /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/drawing.c

CMakeFiles/gtkworld_1.dir/drawing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld_1.dir/drawing.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/drawing.c > CMakeFiles/gtkworld_1.dir/drawing.c.i

CMakeFiles/gtkworld_1.dir/drawing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld_1.dir/drawing.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/drawing.c -o CMakeFiles/gtkworld_1.dir/drawing.c.s

CMakeFiles/gtkworld_1.dir/drawing.c.o.requires:

.PHONY : CMakeFiles/gtkworld_1.dir/drawing.c.o.requires

CMakeFiles/gtkworld_1.dir/drawing.c.o.provides: CMakeFiles/gtkworld_1.dir/drawing.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld_1.dir/build.make CMakeFiles/gtkworld_1.dir/drawing.c.o.provides.build
.PHONY : CMakeFiles/gtkworld_1.dir/drawing.c.o.provides

CMakeFiles/gtkworld_1.dir/drawing.c.o.provides.build: CMakeFiles/gtkworld_1.dir/drawing.c.o


CMakeFiles/gtkworld_1.dir/buttons.c.o: CMakeFiles/gtkworld_1.dir/flags.make
CMakeFiles/gtkworld_1.dir/buttons.c.o: ../buttons.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/gtkworld_1.dir/buttons.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld_1.dir/buttons.c.o   -c /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/buttons.c

CMakeFiles/gtkworld_1.dir/buttons.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld_1.dir/buttons.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/buttons.c > CMakeFiles/gtkworld_1.dir/buttons.c.i

CMakeFiles/gtkworld_1.dir/buttons.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld_1.dir/buttons.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/buttons.c -o CMakeFiles/gtkworld_1.dir/buttons.c.s

CMakeFiles/gtkworld_1.dir/buttons.c.o.requires:

.PHONY : CMakeFiles/gtkworld_1.dir/buttons.c.o.requires

CMakeFiles/gtkworld_1.dir/buttons.c.o.provides: CMakeFiles/gtkworld_1.dir/buttons.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld_1.dir/build.make CMakeFiles/gtkworld_1.dir/buttons.c.o.provides.build
.PHONY : CMakeFiles/gtkworld_1.dir/buttons.c.o.provides

CMakeFiles/gtkworld_1.dir/buttons.c.o.provides.build: CMakeFiles/gtkworld_1.dir/buttons.c.o


CMakeFiles/gtkworld_1.dir/testing_tree.c.o: CMakeFiles/gtkworld_1.dir/flags.make
CMakeFiles/gtkworld_1.dir/testing_tree.c.o: ../testing_tree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/gtkworld_1.dir/testing_tree.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld_1.dir/testing_tree.c.o   -c /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/testing_tree.c

CMakeFiles/gtkworld_1.dir/testing_tree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld_1.dir/testing_tree.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/testing_tree.c > CMakeFiles/gtkworld_1.dir/testing_tree.c.i

CMakeFiles/gtkworld_1.dir/testing_tree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld_1.dir/testing_tree.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/testing_tree.c -o CMakeFiles/gtkworld_1.dir/testing_tree.c.s

CMakeFiles/gtkworld_1.dir/testing_tree.c.o.requires:

.PHONY : CMakeFiles/gtkworld_1.dir/testing_tree.c.o.requires

CMakeFiles/gtkworld_1.dir/testing_tree.c.o.provides: CMakeFiles/gtkworld_1.dir/testing_tree.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld_1.dir/build.make CMakeFiles/gtkworld_1.dir/testing_tree.c.o.provides.build
.PHONY : CMakeFiles/gtkworld_1.dir/testing_tree.c.o.provides

CMakeFiles/gtkworld_1.dir/testing_tree.c.o.provides.build: CMakeFiles/gtkworld_1.dir/testing_tree.c.o


CMakeFiles/gtkworld_1.dir/window.c.o: CMakeFiles/gtkworld_1.dir/flags.make
CMakeFiles/gtkworld_1.dir/window.c.o: ../window.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/gtkworld_1.dir/window.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld_1.dir/window.c.o   -c /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/window.c

CMakeFiles/gtkworld_1.dir/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld_1.dir/window.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/window.c > CMakeFiles/gtkworld_1.dir/window.c.i

CMakeFiles/gtkworld_1.dir/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld_1.dir/window.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/window.c -o CMakeFiles/gtkworld_1.dir/window.c.s

CMakeFiles/gtkworld_1.dir/window.c.o.requires:

.PHONY : CMakeFiles/gtkworld_1.dir/window.c.o.requires

CMakeFiles/gtkworld_1.dir/window.c.o.provides: CMakeFiles/gtkworld_1.dir/window.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld_1.dir/build.make CMakeFiles/gtkworld_1.dir/window.c.o.provides.build
.PHONY : CMakeFiles/gtkworld_1.dir/window.c.o.provides

CMakeFiles/gtkworld_1.dir/window.c.o.provides.build: CMakeFiles/gtkworld_1.dir/window.c.o


CMakeFiles/gtkworld_1.dir/functions2.c.o: CMakeFiles/gtkworld_1.dir/flags.make
CMakeFiles/gtkworld_1.dir/functions2.c.o: ../functions2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/gtkworld_1.dir/functions2.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gtkworld_1.dir/functions2.c.o   -c /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/functions2.c

CMakeFiles/gtkworld_1.dir/functions2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gtkworld_1.dir/functions2.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/functions2.c > CMakeFiles/gtkworld_1.dir/functions2.c.i

CMakeFiles/gtkworld_1.dir/functions2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gtkworld_1.dir/functions2.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/functions2.c -o CMakeFiles/gtkworld_1.dir/functions2.c.s

CMakeFiles/gtkworld_1.dir/functions2.c.o.requires:

.PHONY : CMakeFiles/gtkworld_1.dir/functions2.c.o.requires

CMakeFiles/gtkworld_1.dir/functions2.c.o.provides: CMakeFiles/gtkworld_1.dir/functions2.c.o.requires
	$(MAKE) -f CMakeFiles/gtkworld_1.dir/build.make CMakeFiles/gtkworld_1.dir/functions2.c.o.provides.build
.PHONY : CMakeFiles/gtkworld_1.dir/functions2.c.o.provides

CMakeFiles/gtkworld_1.dir/functions2.c.o.provides.build: CMakeFiles/gtkworld_1.dir/functions2.c.o


# Object files for target gtkworld_1
gtkworld_1_OBJECTS = \
"CMakeFiles/gtkworld_1.dir/client.c.o" \
"CMakeFiles/gtkworld_1.dir/interrupts.c.o" \
"CMakeFiles/gtkworld_1.dir/drawing.c.o" \
"CMakeFiles/gtkworld_1.dir/buttons.c.o" \
"CMakeFiles/gtkworld_1.dir/testing_tree.c.o" \
"CMakeFiles/gtkworld_1.dir/window.c.o" \
"CMakeFiles/gtkworld_1.dir/functions2.c.o"

# External object files for target gtkworld_1
gtkworld_1_EXTERNAL_OBJECTS =

gtkworld_1: CMakeFiles/gtkworld_1.dir/client.c.o
gtkworld_1: CMakeFiles/gtkworld_1.dir/interrupts.c.o
gtkworld_1: CMakeFiles/gtkworld_1.dir/drawing.c.o
gtkworld_1: CMakeFiles/gtkworld_1.dir/buttons.c.o
gtkworld_1: CMakeFiles/gtkworld_1.dir/testing_tree.c.o
gtkworld_1: CMakeFiles/gtkworld_1.dir/window.c.o
gtkworld_1: CMakeFiles/gtkworld_1.dir/functions2.c.o
gtkworld_1: CMakeFiles/gtkworld_1.dir/build.make
gtkworld_1: CMakeFiles/gtkworld_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable gtkworld_1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtkworld_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gtkworld_1.dir/build: gtkworld_1

.PHONY : CMakeFiles/gtkworld_1.dir/build

CMakeFiles/gtkworld_1.dir/requires: CMakeFiles/gtkworld_1.dir/client.c.o.requires
CMakeFiles/gtkworld_1.dir/requires: CMakeFiles/gtkworld_1.dir/interrupts.c.o.requires
CMakeFiles/gtkworld_1.dir/requires: CMakeFiles/gtkworld_1.dir/drawing.c.o.requires
CMakeFiles/gtkworld_1.dir/requires: CMakeFiles/gtkworld_1.dir/buttons.c.o.requires
CMakeFiles/gtkworld_1.dir/requires: CMakeFiles/gtkworld_1.dir/testing_tree.c.o.requires
CMakeFiles/gtkworld_1.dir/requires: CMakeFiles/gtkworld_1.dir/window.c.o.requires
CMakeFiles/gtkworld_1.dir/requires: CMakeFiles/gtkworld_1.dir/functions2.c.o.requires

.PHONY : CMakeFiles/gtkworld_1.dir/requires

CMakeFiles/gtkworld_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gtkworld_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gtkworld_1.dir/clean

CMakeFiles/gtkworld_1.dir/depend:
	cd /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug /home/dushn/Desktop/TEST_RADI_slanje/TEST_GIT_NEW_YEAR/graphmagic/cmake-build-debug/CMakeFiles/gtkworld_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gtkworld_1.dir/depend

