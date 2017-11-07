//
// Created by root on 13.6.17..
//

#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

#include "gtk/gtk.h"
#include "common.h"

void* primanje(void * socket,GArray *array_int,Cpu_usage1 *cpu_usage1,GArray *array_tasks,GArray *array_devices,Network *network
        ,struct tm *tm,Memory_usage *memory);
//void* primanje(void * socket,GArray *array_int,Cpu_usage1 *cpu_usage1);


pthread_mutex_t mut;
pthread_cond_t  cond ;

struct my_thread_info {
    int thread_socket;
};



#endif //SERVER_FUNCTIONS_H
