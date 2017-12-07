//
// Created by root on 13.6.17..
//

#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

#include "gtk/gtk.h"
#include "common.h"

void primanje(void * socket,GArray *array_int,Cpu_usage *cpu_usage1,GArray *array_tasks,GArray *array_devices,Network *network
        ,struct tm *tm,Memory_usage *memory);
//void* primanje(void * socket,GArray *array_int,Cpu_usage1 *cpu_usage1);

void  primanje2(void * socket,GArray *array_int,Cpu_usage  *cpu_usage1,GArray *array_tasks,GArray *array_devices
        ,Network *network,Memory_usage *memory_usage);



void  primanje3(void * socket
                ,Cpu_usage * cpu_usage1
               , Network *network
              , Memory_usage  *memory_usage
                ,GArray * array_devices
                ,GArray *array_int
                ,GArray *array_tasks
);
pthread_mutex_t mut;
pthread_cond_t  cond ;

struct my_thread_info {
    int thread_socket;
};



#endif //SERVER_FUNCTIONS_H
