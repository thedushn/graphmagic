cmake_minimum_required(VERSION 3.7)
project(gtkworld)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -pthread  -Wall ")
set(CMAKE_L_FLAGS "${CMAKE_C_FLAGS}  -pthread  -Wall ")
set(CMAKE_C_STANDARD 11)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
set(SOURCE_FILES
        client.c

        interrupts.c

        interrupts.h

        drawing.c drawing.h

        main_header.h buttons.c buttons.h

        testing_tree.c testing_tree.h window.c window.h

        common.h buttons_s.h

        functions.h)
set(SOURCE_FILES_1
        client.c

        interrupts.c

        interrupts.h

        drawing.c drawing.h

        main_header.h buttons.c buttons.h

        testing_tree.c testing_tree.h window.c window.h

        common.h buttons_s.h
        functions.c
        functions.h)


include_directories(${GTK3_INCLUDE_DIRS})

link_directories(${GTK3_LIBRARY_DIRS})
link_libraries(${GTK3_LIBRARIES})
add_executable(gtkworld ${SOURCE_FILES})
add_executable(gtkworld_1 ${SOURCE_FILES_1})
target_link_libraries(gtkworld_1 m)