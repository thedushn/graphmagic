cmake_minimum_required(VERSION 3.7)
project(Client_)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
set(CMAKE_C_STANDARD 11)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

set(SOURCE_FILES
        functions.c
        functions.c
        client.c
        memory_usage.c
        memory_usage.h
        common.h
        interrupts.h
        interrupts.c
        interrupts_s.h
        cpu_usage.c
        cpu_usage.h
        )
include_directories(${GTK3_INCLUDE_DIRS})
include_directories(${})
link_directories(${GTK3_LIBRARY_DIRS})
link_libraries(${GTK3_LIBRARIES})
add_executable(Client_ ${SOURCE_FILES})
