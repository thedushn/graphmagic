//
// Created by dushn on 23.10.17..
//

#ifndef GTKWORLD_COMMON_H
#define GTKWORLD_COMMON_H

#include "gtk/gtk.h"

//#include "network_bandwith.h"
//#include "task_manager.h"

#include "cpu_usage.h"
//#include "memory_usage.h"
#include "interrupts_s.h"

typedef struct _Memory_usage Memory_usage;

struct _Memory_usage {

    unsigned long long  memory_used;
    unsigned long long  memory_total;
    float swap_percentage;
    unsigned long long  swap_total;
    unsigned  long long swap_used;
    float percentage ;

};

typedef union DATA_S data_s;
union DATA_S {

    Memory_usage memory_usage;
    Interrupts interrupts;
    Cpu_usage cpu_usage;
//    Network network;
//    Task task;
//    Devices devices;




} ;



#endif //GTKWORLD_COMMON_H
