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
CMAKE_SOURCE_DIR = /home/dushn/Desktop/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dushn/Desktop/Server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/functions.c.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/functions.c.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/functions.c.dir/flags.make

CMakeFiles/functions.c.dir/functions.c.o: CMakeFiles/functions.c.dir/flags.make
CMakeFiles/functions.c.dir/functions.c.o: ../functions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/functions.c.dir/functions.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/functions.c.dir/functions.c.o   -c /home/dushn/Desktop/Server/functions.c

CMakeFiles/functions.c.dir/functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/functions.c.dir/functions.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/functions.c > CMakeFiles/functions.c.dir/functions.c.i

CMakeFiles/functions.c.dir/functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/functions.c.dir/functions.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/functions.c -o CMakeFiles/functions.c.dir/functions.c.s

CMakeFiles/functions.c.dir/functions.c.o.requires:

.PHONY : CMakeFiles/functions.c.dir/functions.c.o.requires

CMakeFiles/functions.c.dir/functions.c.o.provides: CMakeFiles/functions.c.dir/functions.c.o.requires
	$(MAKE) -f CMakeFiles/functions.c.dir/build.make CMakeFiles/functions.c.dir/functions.c.o.provides.build
.PHONY : CMakeFiles/functions.c.dir/functions.c.o.provides

CMakeFiles/functions.c.dir/functions.c.o.provides.build: CMakeFiles/functions.c.dir/functions.c.o


CMakeFiles/functions.c.dir/server.c.o: CMakeFiles/functions.c.dir/flags.make
CMakeFiles/functions.c.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/functions.c.dir/server.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/functions.c.dir/server.c.o   -c /home/dushn/Desktop/Server/server.c

CMakeFiles/functions.c.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/functions.c.dir/server.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/server.c > CMakeFiles/functions.c.dir/server.c.i

CMakeFiles/functions.c.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/functions.c.dir/server.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/server.c -o CMakeFiles/functions.c.dir/server.c.s

CMakeFiles/functions.c.dir/server.c.o.requires:

.PHONY : CMakeFiles/functions.c.dir/server.c.o.requires

CMakeFiles/functions.c.dir/server.c.o.provides: CMakeFiles/functions.c.dir/server.c.o.requires
	$(MAKE) -f CMakeFiles/functions.c.dir/build.make CMakeFiles/functions.c.dir/server.c.o.provides.build
.PHONY : CMakeFiles/functions.c.dir/server.c.o.provides

CMakeFiles/functions.c.dir/server.c.o.provides.build: CMakeFiles/functions.c.dir/server.c.o


CMakeFiles/functions.c.dir/memory_usage.c.o: CMakeFiles/functions.c.dir/flags.make
CMakeFiles/functions.c.dir/memory_usage.c.o: ../memory_usage.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/functions.c.dir/memory_usage.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/functions.c.dir/memory_usage.c.o   -c /home/dushn/Desktop/Server/memory_usage.c

CMakeFiles/functions.c.dir/memory_usage.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/functions.c.dir/memory_usage.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/memory_usage.c > CMakeFiles/functions.c.dir/memory_usage.c.i

CMakeFiles/functions.c.dir/memory_usage.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/functions.c.dir/memory_usage.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/memory_usage.c -o CMakeFiles/functions.c.dir/memory_usage.c.s

CMakeFiles/functions.c.dir/memory_usage.c.o.requires:

.PHONY : CMakeFiles/functions.c.dir/memory_usage.c.o.requires

CMakeFiles/functions.c.dir/memory_usage.c.o.provides: CMakeFiles/functions.c.dir/memory_usage.c.o.requires
	$(MAKE) -f CMakeFiles/functions.c.dir/build.make CMakeFiles/functions.c.dir/memory_usage.c.o.provides.build
.PHONY : CMakeFiles/functions.c.dir/memory_usage.c.o.provides

CMakeFiles/functions.c.dir/memory_usage.c.o.provides.build: CMakeFiles/functions.c.dir/memory_usage.c.o


CMakeFiles/functions.c.dir/interrupts.c.o: CMakeFiles/functions.c.dir/flags.make
CMakeFiles/functions.c.dir/interrupts.c.o: ../interrupts.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/functions.c.dir/interrupts.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/functions.c.dir/interrupts.c.o   -c /home/dushn/Desktop/Server/interrupts.c

CMakeFiles/functions.c.dir/interrupts.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/functions.c.dir/interrupts.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/interrupts.c > CMakeFiles/functions.c.dir/interrupts.c.i

CMakeFiles/functions.c.dir/interrupts.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/functions.c.dir/interrupts.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/interrupts.c -o CMakeFiles/functions.c.dir/interrupts.c.s

CMakeFiles/functions.c.dir/interrupts.c.o.requires:

.PHONY : CMakeFiles/functions.c.dir/interrupts.c.o.requires

CMakeFiles/functions.c.dir/interrupts.c.o.provides: CMakeFiles/functions.c.dir/interrupts.c.o.requires
	$(MAKE) -f CMakeFiles/functions.c.dir/build.make CMakeFiles/functions.c.dir/interrupts.c.o.provides.build
.PHONY : CMakeFiles/functions.c.dir/interrupts.c.o.provides

CMakeFiles/functions.c.dir/interrupts.c.o.provides.build: CMakeFiles/functions.c.dir/interrupts.c.o


CMakeFiles/functions.c.dir/task_manager.c.o: CMakeFiles/functions.c.dir/flags.make
CMakeFiles/functions.c.dir/task_manager.c.o: ../task_manager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/functions.c.dir/task_manager.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/functions.c.dir/task_manager.c.o   -c /home/dushn/Desktop/Server/task_manager.c

CMakeFiles/functions.c.dir/task_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/functions.c.dir/task_manager.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/task_manager.c > CMakeFiles/functions.c.dir/task_manager.c.i

CMakeFiles/functions.c.dir/task_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/functions.c.dir/task_manager.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/task_manager.c -o CMakeFiles/functions.c.dir/task_manager.c.s

CMakeFiles/functions.c.dir/task_manager.c.o.requires:

.PHONY : CMakeFiles/functions.c.dir/task_manager.c.o.requires

CMakeFiles/functions.c.dir/task_manager.c.o.provides: CMakeFiles/functions.c.dir/task_manager.c.o.requires
	$(MAKE) -f CMakeFiles/functions.c.dir/build.make CMakeFiles/functions.c.dir/task_manager.c.o.provides.build
.PHONY : CMakeFiles/functions.c.dir/task_manager.c.o.provides

CMakeFiles/functions.c.dir/task_manager.c.o.provides.build: CMakeFiles/functions.c.dir/task_manager.c.o


CMakeFiles/functions.c.dir/devices.c.o: CMakeFiles/functions.c.dir/flags.make
CMakeFiles/functions.c.dir/devices.c.o: ../devices.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/functions.c.dir/devices.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/functions.c.dir/devices.c.o   -c /home/dushn/Desktop/Server/devices.c

CMakeFiles/functions.c.dir/devices.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/functions.c.dir/devices.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/devices.c > CMakeFiles/functions.c.dir/devices.c.i

CMakeFiles/functions.c.dir/devices.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/functions.c.dir/devices.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/devices.c -o CMakeFiles/functions.c.dir/devices.c.s

CMakeFiles/functions.c.dir/devices.c.o.requires:

.PHONY : CMakeFiles/functions.c.dir/devices.c.o.requires

CMakeFiles/functions.c.dir/devices.c.o.provides: CMakeFiles/functions.c.dir/devices.c.o.requires
	$(MAKE) -f CMakeFiles/functions.c.dir/build.make CMakeFiles/functions.c.dir/devices.c.o.provides.build
.PHONY : CMakeFiles/functions.c.dir/devices.c.o.provides

CMakeFiles/functions.c.dir/devices.c.o.provides.build: CMakeFiles/functions.c.dir/devices.c.o


CMakeFiles/functions.c.dir/network_bandwith.c.o: CMakeFiles/functions.c.dir/flags.make
CMakeFiles/functions.c.dir/network_bandwith.c.o: ../network_bandwith.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/functions.c.dir/network_bandwith.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/functions.c.dir/network_bandwith.c.o   -c /home/dushn/Desktop/Server/network_bandwith.c

CMakeFiles/functions.c.dir/network_bandwith.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/functions.c.dir/network_bandwith.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/network_bandwith.c > CMakeFiles/functions.c.dir/network_bandwith.c.i

CMakeFiles/functions.c.dir/network_bandwith.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/functions.c.dir/network_bandwith.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/network_bandwith.c -o CMakeFiles/functions.c.dir/network_bandwith.c.s

CMakeFiles/functions.c.dir/network_bandwith.c.o.requires:

.PHONY : CMakeFiles/functions.c.dir/network_bandwith.c.o.requires

CMakeFiles/functions.c.dir/network_bandwith.c.o.provides: CMakeFiles/functions.c.dir/network_bandwith.c.o.requires
	$(MAKE) -f CMakeFiles/functions.c.dir/build.make CMakeFiles/functions.c.dir/network_bandwith.c.o.provides.build
.PHONY : CMakeFiles/functions.c.dir/network_bandwith.c.o.provides

CMakeFiles/functions.c.dir/network_bandwith.c.o.provides.build: CMakeFiles/functions.c.dir/network_bandwith.c.o


CMakeFiles/functions.c.dir/cpu_usage.c.o: CMakeFiles/functions.c.dir/flags.make
CMakeFiles/functions.c.dir/cpu_usage.c.o: ../cpu_usage.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/functions.c.dir/cpu_usage.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/functions.c.dir/cpu_usage.c.o   -c /home/dushn/Desktop/Server/cpu_usage.c

CMakeFiles/functions.c.dir/cpu_usage.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/functions.c.dir/cpu_usage.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/cpu_usage.c > CMakeFiles/functions.c.dir/cpu_usage.c.i

CMakeFiles/functions.c.dir/cpu_usage.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/functions.c.dir/cpu_usage.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/cpu_usage.c -o CMakeFiles/functions.c.dir/cpu_usage.c.s

CMakeFiles/functions.c.dir/cpu_usage.c.o.requires:

.PHONY : CMakeFiles/functions.c.dir/cpu_usage.c.o.requires

CMakeFiles/functions.c.dir/cpu_usage.c.o.provides: CMakeFiles/functions.c.dir/cpu_usage.c.o.requires
	$(MAKE) -f CMakeFiles/functions.c.dir/build.make CMakeFiles/functions.c.dir/cpu_usage.c.o.provides.build
.PHONY : CMakeFiles/functions.c.dir/cpu_usage.c.o.provides

CMakeFiles/functions.c.dir/cpu_usage.c.o.provides.build: CMakeFiles/functions.c.dir/cpu_usage.c.o


# Object files for target functions.c
functions_c_OBJECTS = \
"CMakeFiles/functions.c.dir/functions.c.o" \
"CMakeFiles/functions.c.dir/server.c.o" \
"CMakeFiles/functions.c.dir/memory_usage.c.o" \
"CMakeFiles/functions.c.dir/interrupts.c.o" \
"CMakeFiles/functions.c.dir/task_manager.c.o" \
"CMakeFiles/functions.c.dir/devices.c.o" \
"CMakeFiles/functions.c.dir/network_bandwith.c.o" \
"CMakeFiles/functions.c.dir/cpu_usage.c.o"

# External object files for target functions.c
functions_c_EXTERNAL_OBJECTS =

functions.c: CMakeFiles/functions.c.dir/functions.c.o
functions.c: CMakeFiles/functions.c.dir/server.c.o
functions.c: CMakeFiles/functions.c.dir/memory_usage.c.o
functions.c: CMakeFiles/functions.c.dir/interrupts.c.o
functions.c: CMakeFiles/functions.c.dir/task_manager.c.o
functions.c: CMakeFiles/functions.c.dir/devices.c.o
functions.c: CMakeFiles/functions.c.dir/network_bandwith.c.o
functions.c: CMakeFiles/functions.c.dir/cpu_usage.c.o
functions.c: CMakeFiles/functions.c.dir/build.make
functions.c: CMakeFiles/functions.c.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable functions.c"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/functions.c.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/functions.c.dir/build: functions.c

.PHONY : CMakeFiles/functions.c.dir/build

CMakeFiles/functions.c.dir/requires: CMakeFiles/functions.c.dir/functions.c.o.requires
CMakeFiles/functions.c.dir/requires: CMakeFiles/functions.c.dir/server.c.o.requires
CMakeFiles/functions.c.dir/requires: CMakeFiles/functions.c.dir/memory_usage.c.o.requires
CMakeFiles/functions.c.dir/requires: CMakeFiles/functions.c.dir/interrupts.c.o.requires
CMakeFiles/functions.c.dir/requires: CMakeFiles/functions.c.dir/task_manager.c.o.requires
CMakeFiles/functions.c.dir/requires: CMakeFiles/functions.c.dir/devices.c.o.requires
CMakeFiles/functions.c.dir/requires: CMakeFiles/functions.c.dir/network_bandwith.c.o.requires
CMakeFiles/functions.c.dir/requires: CMakeFiles/functions.c.dir/cpu_usage.c.o.requires

.PHONY : CMakeFiles/functions.c.dir/requires

CMakeFiles/functions.c.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/functions.c.dir/cmake_clean.cmake
.PHONY : CMakeFiles/functions.c.dir/clean

CMakeFiles/functions.c.dir/depend:
	cd /home/dushn/Desktop/Server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dushn/Desktop/Server /home/dushn/Desktop/Server /home/dushn/Desktop/Server/cmake-build-debug /home/dushn/Desktop/Server/cmake-build-debug /home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles/functions.c.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/functions.c.dir/depend

