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
include CMakeFiles/Server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Server.dir/flags.make

CMakeFiles/Server.dir/functions.c.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/functions.c.o: ../functions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Server.dir/functions.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server.dir/functions.c.o   -c /home/dushn/Desktop/Server/functions.c

CMakeFiles/Server.dir/functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server.dir/functions.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/functions.c > CMakeFiles/Server.dir/functions.c.i

CMakeFiles/Server.dir/functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server.dir/functions.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/functions.c -o CMakeFiles/Server.dir/functions.c.s

CMakeFiles/Server.dir/functions.c.o.requires:

.PHONY : CMakeFiles/Server.dir/functions.c.o.requires

CMakeFiles/Server.dir/functions.c.o.provides: CMakeFiles/Server.dir/functions.c.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/functions.c.o.provides.build
.PHONY : CMakeFiles/Server.dir/functions.c.o.provides

CMakeFiles/Server.dir/functions.c.o.provides.build: CMakeFiles/Server.dir/functions.c.o


CMakeFiles/Server.dir/server.c.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Server.dir/server.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server.dir/server.c.o   -c /home/dushn/Desktop/Server/server.c

CMakeFiles/Server.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server.dir/server.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/server.c > CMakeFiles/Server.dir/server.c.i

CMakeFiles/Server.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server.dir/server.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/server.c -o CMakeFiles/Server.dir/server.c.s

CMakeFiles/Server.dir/server.c.o.requires:

.PHONY : CMakeFiles/Server.dir/server.c.o.requires

CMakeFiles/Server.dir/server.c.o.provides: CMakeFiles/Server.dir/server.c.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/server.c.o.provides.build
.PHONY : CMakeFiles/Server.dir/server.c.o.provides

CMakeFiles/Server.dir/server.c.o.provides.build: CMakeFiles/Server.dir/server.c.o


CMakeFiles/Server.dir/memory_usage.c.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/memory_usage.c.o: ../memory_usage.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Server.dir/memory_usage.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server.dir/memory_usage.c.o   -c /home/dushn/Desktop/Server/memory_usage.c

CMakeFiles/Server.dir/memory_usage.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server.dir/memory_usage.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/memory_usage.c > CMakeFiles/Server.dir/memory_usage.c.i

CMakeFiles/Server.dir/memory_usage.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server.dir/memory_usage.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/memory_usage.c -o CMakeFiles/Server.dir/memory_usage.c.s

CMakeFiles/Server.dir/memory_usage.c.o.requires:

.PHONY : CMakeFiles/Server.dir/memory_usage.c.o.requires

CMakeFiles/Server.dir/memory_usage.c.o.provides: CMakeFiles/Server.dir/memory_usage.c.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/memory_usage.c.o.provides.build
.PHONY : CMakeFiles/Server.dir/memory_usage.c.o.provides

CMakeFiles/Server.dir/memory_usage.c.o.provides.build: CMakeFiles/Server.dir/memory_usage.c.o


CMakeFiles/Server.dir/interrupts.c.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/interrupts.c.o: ../interrupts.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Server.dir/interrupts.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server.dir/interrupts.c.o   -c /home/dushn/Desktop/Server/interrupts.c

CMakeFiles/Server.dir/interrupts.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server.dir/interrupts.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/interrupts.c > CMakeFiles/Server.dir/interrupts.c.i

CMakeFiles/Server.dir/interrupts.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server.dir/interrupts.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/interrupts.c -o CMakeFiles/Server.dir/interrupts.c.s

CMakeFiles/Server.dir/interrupts.c.o.requires:

.PHONY : CMakeFiles/Server.dir/interrupts.c.o.requires

CMakeFiles/Server.dir/interrupts.c.o.provides: CMakeFiles/Server.dir/interrupts.c.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/interrupts.c.o.provides.build
.PHONY : CMakeFiles/Server.dir/interrupts.c.o.provides

CMakeFiles/Server.dir/interrupts.c.o.provides.build: CMakeFiles/Server.dir/interrupts.c.o


CMakeFiles/Server.dir/task_manager.c.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/task_manager.c.o: ../task_manager.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Server.dir/task_manager.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server.dir/task_manager.c.o   -c /home/dushn/Desktop/Server/task_manager.c

CMakeFiles/Server.dir/task_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server.dir/task_manager.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/task_manager.c > CMakeFiles/Server.dir/task_manager.c.i

CMakeFiles/Server.dir/task_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server.dir/task_manager.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/task_manager.c -o CMakeFiles/Server.dir/task_manager.c.s

CMakeFiles/Server.dir/task_manager.c.o.requires:

.PHONY : CMakeFiles/Server.dir/task_manager.c.o.requires

CMakeFiles/Server.dir/task_manager.c.o.provides: CMakeFiles/Server.dir/task_manager.c.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/task_manager.c.o.provides.build
.PHONY : CMakeFiles/Server.dir/task_manager.c.o.provides

CMakeFiles/Server.dir/task_manager.c.o.provides.build: CMakeFiles/Server.dir/task_manager.c.o


CMakeFiles/Server.dir/devices.c.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/devices.c.o: ../devices.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Server.dir/devices.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server.dir/devices.c.o   -c /home/dushn/Desktop/Server/devices.c

CMakeFiles/Server.dir/devices.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server.dir/devices.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/devices.c > CMakeFiles/Server.dir/devices.c.i

CMakeFiles/Server.dir/devices.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server.dir/devices.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/devices.c -o CMakeFiles/Server.dir/devices.c.s

CMakeFiles/Server.dir/devices.c.o.requires:

.PHONY : CMakeFiles/Server.dir/devices.c.o.requires

CMakeFiles/Server.dir/devices.c.o.provides: CMakeFiles/Server.dir/devices.c.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/devices.c.o.provides.build
.PHONY : CMakeFiles/Server.dir/devices.c.o.provides

CMakeFiles/Server.dir/devices.c.o.provides.build: CMakeFiles/Server.dir/devices.c.o


CMakeFiles/Server.dir/network_bandwith.c.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/network_bandwith.c.o: ../network_bandwith.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/Server.dir/network_bandwith.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server.dir/network_bandwith.c.o   -c /home/dushn/Desktop/Server/network_bandwith.c

CMakeFiles/Server.dir/network_bandwith.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server.dir/network_bandwith.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/network_bandwith.c > CMakeFiles/Server.dir/network_bandwith.c.i

CMakeFiles/Server.dir/network_bandwith.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server.dir/network_bandwith.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/network_bandwith.c -o CMakeFiles/Server.dir/network_bandwith.c.s

CMakeFiles/Server.dir/network_bandwith.c.o.requires:

.PHONY : CMakeFiles/Server.dir/network_bandwith.c.o.requires

CMakeFiles/Server.dir/network_bandwith.c.o.provides: CMakeFiles/Server.dir/network_bandwith.c.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/network_bandwith.c.o.provides.build
.PHONY : CMakeFiles/Server.dir/network_bandwith.c.o.provides

CMakeFiles/Server.dir/network_bandwith.c.o.provides.build: CMakeFiles/Server.dir/network_bandwith.c.o


CMakeFiles/Server.dir/cpu_usage.c.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/cpu_usage.c.o: ../cpu_usage.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/Server.dir/cpu_usage.c.o"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server.dir/cpu_usage.c.o   -c /home/dushn/Desktop/Server/cpu_usage.c

CMakeFiles/Server.dir/cpu_usage.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server.dir/cpu_usage.c.i"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/dushn/Desktop/Server/cpu_usage.c > CMakeFiles/Server.dir/cpu_usage.c.i

CMakeFiles/Server.dir/cpu_usage.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server.dir/cpu_usage.c.s"
	/home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/dushn/Desktop/Server/cpu_usage.c -o CMakeFiles/Server.dir/cpu_usage.c.s

CMakeFiles/Server.dir/cpu_usage.c.o.requires:

.PHONY : CMakeFiles/Server.dir/cpu_usage.c.o.requires

CMakeFiles/Server.dir/cpu_usage.c.o.provides: CMakeFiles/Server.dir/cpu_usage.c.o.requires
	$(MAKE) -f CMakeFiles/Server.dir/build.make CMakeFiles/Server.dir/cpu_usage.c.o.provides.build
.PHONY : CMakeFiles/Server.dir/cpu_usage.c.o.provides

CMakeFiles/Server.dir/cpu_usage.c.o.provides.build: CMakeFiles/Server.dir/cpu_usage.c.o


# Object files for target Server
Server_OBJECTS = \
"CMakeFiles/Server.dir/functions.c.o" \
"CMakeFiles/Server.dir/server.c.o" \
"CMakeFiles/Server.dir/memory_usage.c.o" \
"CMakeFiles/Server.dir/interrupts.c.o" \
"CMakeFiles/Server.dir/task_manager.c.o" \
"CMakeFiles/Server.dir/devices.c.o" \
"CMakeFiles/Server.dir/network_bandwith.c.o" \
"CMakeFiles/Server.dir/cpu_usage.c.o"

# External object files for target Server
Server_EXTERNAL_OBJECTS =

Server: CMakeFiles/Server.dir/functions.c.o
Server: CMakeFiles/Server.dir/server.c.o
Server: CMakeFiles/Server.dir/memory_usage.c.o
Server: CMakeFiles/Server.dir/interrupts.c.o
Server: CMakeFiles/Server.dir/task_manager.c.o
Server: CMakeFiles/Server.dir/devices.c.o
Server: CMakeFiles/Server.dir/network_bandwith.c.o
Server: CMakeFiles/Server.dir/cpu_usage.c.o
Server: CMakeFiles/Server.dir/build.make
Server: CMakeFiles/Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable Server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Server.dir/build: Server

.PHONY : CMakeFiles/Server.dir/build

CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/functions.c.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/server.c.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/memory_usage.c.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/interrupts.c.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/task_manager.c.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/devices.c.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/network_bandwith.c.o.requires
CMakeFiles/Server.dir/requires: CMakeFiles/Server.dir/cpu_usage.c.o.requires

.PHONY : CMakeFiles/Server.dir/requires

CMakeFiles/Server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Server.dir/clean

CMakeFiles/Server.dir/depend:
	cd /home/dushn/Desktop/Server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dushn/Desktop/Server /home/dushn/Desktop/Server /home/dushn/Desktop/Server/cmake-build-debug /home/dushn/Desktop/Server/cmake-build-debug /home/dushn/Desktop/Server/cmake-build-debug/CMakeFiles/Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Server.dir/depend

