cmake_minimum_required(VERSION 3.7)
project(gtkworld)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
set(CMAKE_C_STANDARD 11)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
set(SOURCE_FILES main.c
        #network_bandwith.c
        interrupts.c
       # network_bandwith.h
        interrupts.h
     #   process-tree-model.c process-tree-model.h process-tree-view.h
      #  process-tree-view.c
    #    task-manager.c task-manager.h
        #   task-manager-linux.c
        drawing.c drawing.h
       # model.c model.h
     #   task_manager.h
        #   process-monitor.h  process-monitor.c

     #   process-window.c
      #  process-window-gtk3_ui.h
      #  process-statusbar.c process-statusbar.h
      #  exec-tool-button.c exec-tool-button.h
      #  settings-tool-button.c settings-tool-button.h
      #  settings-dialog.c settings-dialog.h
       # settings-dialog-gtk3_ui.h
        main_header.h buttons.c buttons.h
        # process-window.c process-window.h
        testing_tree.c testing_tree.h window.c window.h
        #lines.h
        common.h buttons_s.h functions.c functions.h)




include_directories(${GTK3_INCLUDE_DIRS})
include_directories(${})
link_directories(${GTK3_LIBRARY_DIRS})
link_libraries(${GTK3_LIBRARIES})
add_executable(gtkworld ${SOURCE_FILES})