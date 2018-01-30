//
// Created by root on 13.6.17..
//

#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

#include "gtk/gtk.h"
#include "common.h"

ssize_t  test_recv(int socket);




void  primanje3(int socket
                ,Cpu_usage * cpu_usage1
               , Network *network
              , Memory_usage  *memory_usage
                ,GArray * array_devices
                ,GArray *array_int
               ,GArray *array_tasks
);


struct my_thread_info {
    int thread_socket;
};



#endif //SERVER_FUNCTIONS_H
