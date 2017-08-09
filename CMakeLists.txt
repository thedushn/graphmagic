cmake_minimum_required(VERSION 3.7)
project(gtkworld)

set(CMAKE_C_STANDARD 11)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
set(SOURCE_FILES main.c memory_usage.c memory_usage.h cpu_usage.c cpu_usage.h)




include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
link_libraries(${GTK3_LIBRARIES})
add_executable(gktworld ${SOURCE_FILES})