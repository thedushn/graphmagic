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
CMAKE_SOURCE_DIR = "/home/dusan/Desktop/clion_git/Client "

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/dusan/Desktop/clion_git/Client /cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/s.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/s.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/s.dir/flags.make

CMakeFiles/s.dir/functions.c.o: CMakeFiles/s.dir/flags.make
CMakeFiles/s.dir/functions.c.o: ../functions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dusan/Desktop/clion_git/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/s.dir/functions.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s.dir/functions.c.o   -c "/home/dusan/Desktop/clion_git/Client /functions.c"

CMakeFiles/s.dir/functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s.dir/functions.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dusan/Desktop/clion_git/Client /functions.c" > CMakeFiles/s.dir/functions.c.i

CMakeFiles/s.dir/functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s.dir/functions.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dusan/Desktop/clion_git/Client /functions.c" -o CMakeFiles/s.dir/functions.c.s

CMakeFiles/s.dir/functions.c.o.requires:

.PHONY : CMakeFiles/s.dir/functions.c.o.requires

CMakeFiles/s.dir/functions.c.o.provides: CMakeFiles/s.dir/functions.c.o.requires
	$(MAKE) -f CMakeFiles/s.dir/build.make CMakeFiles/s.dir/functions.c.o.provides.build
.PHONY : CMakeFiles/s.dir/functions.c.o.provides

CMakeFiles/s.dir/functions.c.o.provides.build: CMakeFiles/s.dir/functions.c.o


CMakeFiles/s.dir/server.c.o: CMakeFiles/s.dir/flags.make
CMakeFiles/s.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dusan/Desktop/clion_git/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/s.dir/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s.dir/server.c.o   -c "/home/dusan/Desktop/clion_git/Client /server.c"

CMakeFiles/s.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s.dir/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dusan/Desktop/clion_git/Client /server.c" > CMakeFiles/s.dir/server.c.i

CMakeFiles/s.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s.dir/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dusan/Desktop/clion_git/Client /server.c" -o CMakeFiles/s.dir/server.c.s

CMakeFiles/s.dir/server.c.o.requires:

.PHONY : CMakeFiles/s.dir/server.c.o.requires

CMakeFiles/s.dir/server.c.o.provides: CMakeFiles/s.dir/server.c.o.requires
	$(MAKE) -f CMakeFiles/s.dir/build.make CMakeFiles/s.dir/server.c.o.provides.build
.PHONY : CMakeFiles/s.dir/server.c.o.provides

CMakeFiles/s.dir/server.c.o.provides.build: CMakeFiles/s.dir/server.c.o


CMakeFiles/s.dir/memory_usage.c.o: CMakeFiles/s.dir/flags.make
CMakeFiles/s.dir/memory_usage.c.o: ../memory_usage.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dusan/Desktop/clion_git/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/s.dir/memory_usage.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s.dir/memory_usage.c.o   -c "/home/dusan/Desktop/clion_git/Client /memory_usage.c"

CMakeFiles/s.dir/memory_usage.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s.dir/memory_usage.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dusan/Desktop/clion_git/Client /memory_usage.c" > CMakeFiles/s.dir/memory_usage.c.i

CMakeFiles/s.dir/memory_usage.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s.dir/memory_usage.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dusan/Desktop/clion_git/Client /memory_usage.c" -o CMakeFiles/s.dir/memory_usage.c.s

CMakeFiles/s.dir/memory_usage.c.o.requires:

.PHONY : CMakeFiles/s.dir/memory_usage.c.o.requires

CMakeFiles/s.dir/memory_usage.c.o.provides: CMakeFiles/s.dir/memory_usage.c.o.requires
	$(MAKE) -f CMakeFiles/s.dir/build.make CMakeFiles/s.dir/memory_usage.c.o.provides.build
.PHONY : CMakeFiles/s.dir/memory_usage.c.o.provides

CMakeFiles/s.dir/memory_usage.c.o.provides.build: CMakeFiles/s.dir/memory_usage.c.o


CMakeFiles/s.dir/interrupts.c.o: CMakeFiles/s.dir/flags.make
CMakeFiles/s.dir/interrupts.c.o: ../interrupts.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dusan/Desktop/clion_git/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/s.dir/interrupts.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s.dir/interrupts.c.o   -c "/home/dusan/Desktop/clion_git/Client /interrupts.c"

CMakeFiles/s.dir/interrupts.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s.dir/interrupts.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dusan/Desktop/clion_git/Client /interrupts.c" > CMakeFiles/s.dir/interrupts.c.i

CMakeFiles/s.dir/interrupts.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s.dir/interrupts.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dusan/Desktop/clion_git/Client /interrupts.c" -o CMakeFiles/s.dir/interrupts.c.s

CMakeFiles/s.dir/interrupts.c.o.requires:

.PHONY : CMakeFiles/s.dir/interrupts.c.o.requires

CMakeFiles/s.dir/interrupts.c.o.provides: CMakeFiles/s.dir/interrupts.c.o.requires
	$(MAKE) -f CMakeFiles/s.dir/build.make CMakeFiles/s.dir/interrupts.c.o.provides.build
.PHONY : CMakeFiles/s.dir/interrupts.c.o.provides

CMakeFiles/s.dir/interrupts.c.o.provides.build: CMakeFiles/s.dir/interrupts.c.o


CMakeFiles/s.dir/task_manager.c.o: CMakeFiles/s.dir/flags.make
CMakeFiles/s.dir/task_manager.c.o: ../task_manager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dusan/Desktop/clion_git/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/s.dir/task_manager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s.dir/task_manager.c.o   -c "/home/dusan/Desktop/clion_git/Client /task_manager.c"

CMakeFiles/s.dir/task_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s.dir/task_manager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dusan/Desktop/clion_git/Client /task_manager.c" > CMakeFiles/s.dir/task_manager.c.i

CMakeFiles/s.dir/task_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s.dir/task_manager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dusan/Desktop/clion_git/Client /task_manager.c" -o CMakeFiles/s.dir/task_manager.c.s

CMakeFiles/s.dir/task_manager.c.o.requires:

.PHONY : CMakeFiles/s.dir/task_manager.c.o.requires

CMakeFiles/s.dir/task_manager.c.o.provides: CMakeFiles/s.dir/task_manager.c.o.requires
	$(MAKE) -f CMakeFiles/s.dir/build.make CMakeFiles/s.dir/task_manager.c.o.provides.build
.PHONY : CMakeFiles/s.dir/task_manager.c.o.provides

CMakeFiles/s.dir/task_manager.c.o.provides.build: CMakeFiles/s.dir/task_manager.c.o


CMakeFiles/s.dir/devices.c.o: CMakeFiles/s.dir/flags.make
CMakeFiles/s.dir/devices.c.o: ../devices.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dusan/Desktop/clion_git/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/s.dir/devices.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s.dir/devices.c.o   -c "/home/dusan/Desktop/clion_git/Client /devices.c"

CMakeFiles/s.dir/devices.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s.dir/devices.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dusan/Desktop/clion_git/Client /devices.c" > CMakeFiles/s.dir/devices.c.i

CMakeFiles/s.dir/devices.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s.dir/devices.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dusan/Desktop/clion_git/Client /devices.c" -o CMakeFiles/s.dir/devices.c.s

CMakeFiles/s.dir/devices.c.o.requires:

.PHONY : CMakeFiles/s.dir/devices.c.o.requires

CMakeFiles/s.dir/devices.c.o.provides: CMakeFiles/s.dir/devices.c.o.requires
	$(MAKE) -f CMakeFiles/s.dir/build.make CMakeFiles/s.dir/devices.c.o.provides.build
.PHONY : CMakeFiles/s.dir/devices.c.o.provides

CMakeFiles/s.dir/devices.c.o.provides.build: CMakeFiles/s.dir/devices.c.o


CMakeFiles/s.dir/network_bandwith.c.o: CMakeFiles/s.dir/flags.make
CMakeFiles/s.dir/network_bandwith.c.o: ../network_bandwith.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dusan/Desktop/clion_git/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/s.dir/network_bandwith.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s.dir/network_bandwith.c.o   -c "/home/dusan/Desktop/clion_git/Client /network_bandwith.c"

CMakeFiles/s.dir/network_bandwith.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s.dir/network_bandwith.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dusan/Desktop/clion_git/Client /network_bandwith.c" > CMakeFiles/s.dir/network_bandwith.c.i

CMakeFiles/s.dir/network_bandwith.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s.dir/network_bandwith.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dusan/Desktop/clion_git/Client /network_bandwith.c" -o CMakeFiles/s.dir/network_bandwith.c.s

CMakeFiles/s.dir/network_bandwith.c.o.requires:

.PHONY : CMakeFiles/s.dir/network_bandwith.c.o.requires

CMakeFiles/s.dir/network_bandwith.c.o.provides: CMakeFiles/s.dir/network_bandwith.c.o.requires
	$(MAKE) -f CMakeFiles/s.dir/build.make CMakeFiles/s.dir/network_bandwith.c.o.provides.build
.PHONY : CMakeFiles/s.dir/network_bandwith.c.o.provides

CMakeFiles/s.dir/network_bandwith.c.o.provides.build: CMakeFiles/s.dir/network_bandwith.c.o


CMakeFiles/s.dir/cpu_usage.c.o: CMakeFiles/s.dir/flags.make
CMakeFiles/s.dir/cpu_usage.c.o: ../cpu_usage.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dusan/Desktop/clion_git/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/s.dir/cpu_usage.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s.dir/cpu_usage.c.o   -c "/home/dusan/Desktop/clion_git/Client /cpu_usage.c"

CMakeFiles/s.dir/cpu_usage.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s.dir/cpu_usage.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dusan/Desktop/clion_git/Client /cpu_usage.c" > CMakeFiles/s.dir/cpu_usage.c.i

CMakeFiles/s.dir/cpu_usage.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s.dir/cpu_usage.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dusan/Desktop/clion_git/Client /cpu_usage.c" -o CMakeFiles/s.dir/cpu_usage.c.s

CMakeFiles/s.dir/cpu_usage.c.o.requires:

.PHONY : CMakeFiles/s.dir/cpu_usage.c.o.requires

CMakeFiles/s.dir/cpu_usage.c.o.provides: CMakeFiles/s.dir/cpu_usage.c.o.requires
	$(MAKE) -f CMakeFiles/s.dir/build.make CMakeFiles/s.dir/cpu_usage.c.o.provides.build
.PHONY : CMakeFiles/s.dir/cpu_usage.c.o.provides

CMakeFiles/s.dir/cpu_usage.c.o.provides.build: CMakeFiles/s.dir/cpu_usage.c.o


# Object files for target s
s_OBJECTS = \
"CMakeFiles/s.dir/functions.c.o" \
"CMakeFiles/s.dir/server.c.o" \
"CMakeFiles/s.dir/memory_usage.c.o" \
"CMakeFiles/s.dir/interrupts.c.o" \
"CMakeFiles/s.dir/task_manager.c.o" \
"CMakeFiles/s.dir/devices.c.o" \
"CMakeFiles/s.dir/network_bandwith.c.o" \
"CMakeFiles/s.dir/cpu_usage.c.o"

# External object files for target s
s_EXTERNAL_OBJECTS =

s : CMakeFiles/s.dir/functions.c.o
s : CMakeFiles/s.dir/server.c.o
s : CMakeFiles/s.dir/memory_usage.c.o
s : CMakeFiles/s.dir/interrupts.c.o
s : CMakeFiles/s.dir/task_manager.c.o
s : CMakeFiles/s.dir/devices.c.o
s : CMakeFiles/s.dir/network_bandwith.c.o
s : CMakeFiles/s.dir/cpu_usage.c.o
s : CMakeFiles/s.dir/build.make
s : CMakeFiles/s.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/dusan/Desktop/clion_git/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable s"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/s.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/s.dir/build: s

.PHONY : CMakeFiles/s.dir/build

CMakeFiles/s.dir/requires: CMakeFiles/s.dir/functions.c.o.requires
CMakeFiles/s.dir/requires: CMakeFiles/s.dir/server.c.o.requires
CMakeFiles/s.dir/requires: CMakeFiles/s.dir/memory_usage.c.o.requires
CMakeFiles/s.dir/requires: CMakeFiles/s.dir/interrupts.c.o.requires
CMakeFiles/s.dir/requires: CMakeFiles/s.dir/task_manager.c.o.requires
CMakeFiles/s.dir/requires: CMakeFiles/s.dir/devices.c.o.requires
CMakeFiles/s.dir/requires: CMakeFiles/s.dir/network_bandwith.c.o.requires
CMakeFiles/s.dir/requires: CMakeFiles/s.dir/cpu_usage.c.o.requires

.PHONY : CMakeFiles/s.dir/requires

CMakeFiles/s.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/s.dir/cmake_clean.cmake
.PHONY : CMakeFiles/s.dir/clean

CMakeFiles/s.dir/depend:
	cd "/home/dusan/Desktop/clion_git/Client /cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/dusan/Desktop/clion_git/Client " "/home/dusan/Desktop/clion_git/Client " "/home/dusan/Desktop/clion_git/Client /cmake-build-debug" "/home/dusan/Desktop/clion_git/Client /cmake-build-debug" "/home/dusan/Desktop/clion_git/Client /cmake-build-debug/CMakeFiles/s.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/s.dir/depend

