cmake_minimum_required(VERSION 3.7)
project(Client_)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
set(CMAKE_C_STANDARD 11)
SET(CMAKE_C_COMPILER      /home/dushn/toolchains/tegra-4.8.1-nv/usr/bin/arm-cortex_a15-linux-gnueabi/arm-cortex_a15-linux-gnueabi-gcc)

set(SOURCE_FILES
        functions.c
        functions.c
        server.c
        memory_usage.c
        memory_usage.h
        common.h
        interrupts.h
        interrupts.c
        task_manager.c
        task_manager.h
        devices.c
        devices.h
        network_bandwith.c
        network_bandwith.h
        cpu_usage.h
        cpu_usage.c
        )

add_executable(s ${SOURCE_FILES})
