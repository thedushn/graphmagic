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
CMAKE_SOURCE_DIR = "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client "

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/s_1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/s_1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/s_1.dir/flags.make

CMakeFiles/s_1.dir/functions2.c.o: CMakeFiles/s_1.dir/flags.make
CMakeFiles/s_1.dir/functions2.c.o: ../functions2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/s_1.dir/functions2.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s_1.dir/functions2.c.o   -c "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /functions2.c"

CMakeFiles/s_1.dir/functions2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s_1.dir/functions2.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /functions2.c" > CMakeFiles/s_1.dir/functions2.c.i

CMakeFiles/s_1.dir/functions2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s_1.dir/functions2.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /functions2.c" -o CMakeFiles/s_1.dir/functions2.c.s

CMakeFiles/s_1.dir/functions2.c.o.requires:

.PHONY : CMakeFiles/s_1.dir/functions2.c.o.requires

CMakeFiles/s_1.dir/functions2.c.o.provides: CMakeFiles/s_1.dir/functions2.c.o.requires
	$(MAKE) -f CMakeFiles/s_1.dir/build.make CMakeFiles/s_1.dir/functions2.c.o.provides.build
.PHONY : CMakeFiles/s_1.dir/functions2.c.o.provides

CMakeFiles/s_1.dir/functions2.c.o.provides.build: CMakeFiles/s_1.dir/functions2.c.o


CMakeFiles/s_1.dir/server.c.o: CMakeFiles/s_1.dir/flags.make
CMakeFiles/s_1.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/s_1.dir/server.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s_1.dir/server.c.o   -c "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /server.c"

CMakeFiles/s_1.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s_1.dir/server.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /server.c" > CMakeFiles/s_1.dir/server.c.i

CMakeFiles/s_1.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s_1.dir/server.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /server.c" -o CMakeFiles/s_1.dir/server.c.s

CMakeFiles/s_1.dir/server.c.o.requires:

.PHONY : CMakeFiles/s_1.dir/server.c.o.requires

CMakeFiles/s_1.dir/server.c.o.provides: CMakeFiles/s_1.dir/server.c.o.requires
	$(MAKE) -f CMakeFiles/s_1.dir/build.make CMakeFiles/s_1.dir/server.c.o.provides.build
.PHONY : CMakeFiles/s_1.dir/server.c.o.provides

CMakeFiles/s_1.dir/server.c.o.provides.build: CMakeFiles/s_1.dir/server.c.o


CMakeFiles/s_1.dir/memory_usage.c.o: CMakeFiles/s_1.dir/flags.make
CMakeFiles/s_1.dir/memory_usage.c.o: ../memory_usage.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/s_1.dir/memory_usage.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s_1.dir/memory_usage.c.o   -c "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /memory_usage.c"

CMakeFiles/s_1.dir/memory_usage.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s_1.dir/memory_usage.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /memory_usage.c" > CMakeFiles/s_1.dir/memory_usage.c.i

CMakeFiles/s_1.dir/memory_usage.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s_1.dir/memory_usage.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /memory_usage.c" -o CMakeFiles/s_1.dir/memory_usage.c.s

CMakeFiles/s_1.dir/memory_usage.c.o.requires:

.PHONY : CMakeFiles/s_1.dir/memory_usage.c.o.requires

CMakeFiles/s_1.dir/memory_usage.c.o.provides: CMakeFiles/s_1.dir/memory_usage.c.o.requires
	$(MAKE) -f CMakeFiles/s_1.dir/build.make CMakeFiles/s_1.dir/memory_usage.c.o.provides.build
.PHONY : CMakeFiles/s_1.dir/memory_usage.c.o.provides

CMakeFiles/s_1.dir/memory_usage.c.o.provides.build: CMakeFiles/s_1.dir/memory_usage.c.o


CMakeFiles/s_1.dir/interrupts.c.o: CMakeFiles/s_1.dir/flags.make
CMakeFiles/s_1.dir/interrupts.c.o: ../interrupts.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/s_1.dir/interrupts.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s_1.dir/interrupts.c.o   -c "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /interrupts.c"

CMakeFiles/s_1.dir/interrupts.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s_1.dir/interrupts.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /interrupts.c" > CMakeFiles/s_1.dir/interrupts.c.i

CMakeFiles/s_1.dir/interrupts.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s_1.dir/interrupts.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /interrupts.c" -o CMakeFiles/s_1.dir/interrupts.c.s

CMakeFiles/s_1.dir/interrupts.c.o.requires:

.PHONY : CMakeFiles/s_1.dir/interrupts.c.o.requires

CMakeFiles/s_1.dir/interrupts.c.o.provides: CMakeFiles/s_1.dir/interrupts.c.o.requires
	$(MAKE) -f CMakeFiles/s_1.dir/build.make CMakeFiles/s_1.dir/interrupts.c.o.provides.build
.PHONY : CMakeFiles/s_1.dir/interrupts.c.o.provides

CMakeFiles/s_1.dir/interrupts.c.o.provides.build: CMakeFiles/s_1.dir/interrupts.c.o


CMakeFiles/s_1.dir/task_manager.c.o: CMakeFiles/s_1.dir/flags.make
CMakeFiles/s_1.dir/task_manager.c.o: ../task_manager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/s_1.dir/task_manager.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s_1.dir/task_manager.c.o   -c "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /task_manager.c"

CMakeFiles/s_1.dir/task_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s_1.dir/task_manager.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /task_manager.c" > CMakeFiles/s_1.dir/task_manager.c.i

CMakeFiles/s_1.dir/task_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s_1.dir/task_manager.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /task_manager.c" -o CMakeFiles/s_1.dir/task_manager.c.s

CMakeFiles/s_1.dir/task_manager.c.o.requires:

.PHONY : CMakeFiles/s_1.dir/task_manager.c.o.requires

CMakeFiles/s_1.dir/task_manager.c.o.provides: CMakeFiles/s_1.dir/task_manager.c.o.requires
	$(MAKE) -f CMakeFiles/s_1.dir/build.make CMakeFiles/s_1.dir/task_manager.c.o.provides.build
.PHONY : CMakeFiles/s_1.dir/task_manager.c.o.provides

CMakeFiles/s_1.dir/task_manager.c.o.provides.build: CMakeFiles/s_1.dir/task_manager.c.o


CMakeFiles/s_1.dir/devices.c.o: CMakeFiles/s_1.dir/flags.make
CMakeFiles/s_1.dir/devices.c.o: ../devices.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/s_1.dir/devices.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s_1.dir/devices.c.o   -c "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /devices.c"

CMakeFiles/s_1.dir/devices.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s_1.dir/devices.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /devices.c" > CMakeFiles/s_1.dir/devices.c.i

CMakeFiles/s_1.dir/devices.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s_1.dir/devices.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /devices.c" -o CMakeFiles/s_1.dir/devices.c.s

CMakeFiles/s_1.dir/devices.c.o.requires:

.PHONY : CMakeFiles/s_1.dir/devices.c.o.requires

CMakeFiles/s_1.dir/devices.c.o.provides: CMakeFiles/s_1.dir/devices.c.o.requires
	$(MAKE) -f CMakeFiles/s_1.dir/build.make CMakeFiles/s_1.dir/devices.c.o.provides.build
.PHONY : CMakeFiles/s_1.dir/devices.c.o.provides

CMakeFiles/s_1.dir/devices.c.o.provides.build: CMakeFiles/s_1.dir/devices.c.o


CMakeFiles/s_1.dir/network_bandwith.c.o: CMakeFiles/s_1.dir/flags.make
CMakeFiles/s_1.dir/network_bandwith.c.o: ../network_bandwith.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/s_1.dir/network_bandwith.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s_1.dir/network_bandwith.c.o   -c "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /network_bandwith.c"

CMakeFiles/s_1.dir/network_bandwith.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s_1.dir/network_bandwith.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /network_bandwith.c" > CMakeFiles/s_1.dir/network_bandwith.c.i

CMakeFiles/s_1.dir/network_bandwith.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s_1.dir/network_bandwith.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /network_bandwith.c" -o CMakeFiles/s_1.dir/network_bandwith.c.s

CMakeFiles/s_1.dir/network_bandwith.c.o.requires:

.PHONY : CMakeFiles/s_1.dir/network_bandwith.c.o.requires

CMakeFiles/s_1.dir/network_bandwith.c.o.provides: CMakeFiles/s_1.dir/network_bandwith.c.o.requires
	$(MAKE) -f CMakeFiles/s_1.dir/build.make CMakeFiles/s_1.dir/network_bandwith.c.o.provides.build
.PHONY : CMakeFiles/s_1.dir/network_bandwith.c.o.provides

CMakeFiles/s_1.dir/network_bandwith.c.o.provides.build: CMakeFiles/s_1.dir/network_bandwith.c.o


CMakeFiles/s_1.dir/cpu_usage.c.o: CMakeFiles/s_1.dir/flags.make
CMakeFiles/s_1.dir/cpu_usage.c.o: ../cpu_usage.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/s_1.dir/cpu_usage.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/s_1.dir/cpu_usage.c.o   -c "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cpu_usage.c"

CMakeFiles/s_1.dir/cpu_usage.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/s_1.dir/cpu_usage.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cpu_usage.c" > CMakeFiles/s_1.dir/cpu_usage.c.i

CMakeFiles/s_1.dir/cpu_usage.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/s_1.dir/cpu_usage.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cpu_usage.c" -o CMakeFiles/s_1.dir/cpu_usage.c.s

CMakeFiles/s_1.dir/cpu_usage.c.o.requires:

.PHONY : CMakeFiles/s_1.dir/cpu_usage.c.o.requires

CMakeFiles/s_1.dir/cpu_usage.c.o.provides: CMakeFiles/s_1.dir/cpu_usage.c.o.requires
	$(MAKE) -f CMakeFiles/s_1.dir/build.make CMakeFiles/s_1.dir/cpu_usage.c.o.provides.build
.PHONY : CMakeFiles/s_1.dir/cpu_usage.c.o.provides

CMakeFiles/s_1.dir/cpu_usage.c.o.provides.build: CMakeFiles/s_1.dir/cpu_usage.c.o


# Object files for target s_1
s_1_OBJECTS = \
"CMakeFiles/s_1.dir/functions2.c.o" \
"CMakeFiles/s_1.dir/server.c.o" \
"CMakeFiles/s_1.dir/memory_usage.c.o" \
"CMakeFiles/s_1.dir/interrupts.c.o" \
"CMakeFiles/s_1.dir/task_manager.c.o" \
"CMakeFiles/s_1.dir/devices.c.o" \
"CMakeFiles/s_1.dir/network_bandwith.c.o" \
"CMakeFiles/s_1.dir/cpu_usage.c.o"

# External object files for target s_1
s_1_EXTERNAL_OBJECTS =

s_1: CMakeFiles/s_1.dir/functions2.c.o
s_1: CMakeFiles/s_1.dir/server.c.o
s_1: CMakeFiles/s_1.dir/memory_usage.c.o
s_1: CMakeFiles/s_1.dir/interrupts.c.o
s_1: CMakeFiles/s_1.dir/task_manager.c.o
s_1: CMakeFiles/s_1.dir/devices.c.o
s_1: CMakeFiles/s_1.dir/network_bandwith.c.o
s_1: CMakeFiles/s_1.dir/cpu_usage.c.o
s_1: CMakeFiles/s_1.dir/build.make
s_1: CMakeFiles/s_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable s_1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/s_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/s_1.dir/build: s_1

.PHONY : CMakeFiles/s_1.dir/build

CMakeFiles/s_1.dir/requires: CMakeFiles/s_1.dir/functions2.c.o.requires
CMakeFiles/s_1.dir/requires: CMakeFiles/s_1.dir/server.c.o.requires
CMakeFiles/s_1.dir/requires: CMakeFiles/s_1.dir/memory_usage.c.o.requires
CMakeFiles/s_1.dir/requires: CMakeFiles/s_1.dir/interrupts.c.o.requires
CMakeFiles/s_1.dir/requires: CMakeFiles/s_1.dir/task_manager.c.o.requires
CMakeFiles/s_1.dir/requires: CMakeFiles/s_1.dir/devices.c.o.requires
CMakeFiles/s_1.dir/requires: CMakeFiles/s_1.dir/network_bandwith.c.o.requires
CMakeFiles/s_1.dir/requires: CMakeFiles/s_1.dir/cpu_usage.c.o.requires

.PHONY : CMakeFiles/s_1.dir/requires

CMakeFiles/s_1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/s_1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/s_1.dir/clean

CMakeFiles/s_1.dir/depend:
	cd "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client " "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client " "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug" "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug" "/home/dushn/Desktop/TEST_RADI_slanje/TEST_ADDING NEW things /TEST_cleaing up code /TEST/Client /cmake-build-debug/CMakeFiles/s_1.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/s_1.dir/depend
