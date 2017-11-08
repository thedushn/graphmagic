//
// Created by dushn on 23.10.17..
//

#ifndef GTKWORLD_COMMON_H
#define GTKWORLD_COMMON_H

#include "gtk/gtk.h"


#include "task_manager.h"
#include "devices.h"

typedef struct _Network Network;
struct _Network{

    unsigned  long received_bytes;
    unsigned  long transmited_bytes;



};
typedef struct _Cpu_usage Cpu_usage;
struct _Cpu_usage {


    gfloat percentage0;
    gfloat percentage1;
    gfloat percentage2;
    gfloat percentage3;
    int number;

};
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
typedef struct _Interrupts Interrupts;
struct _Interrupts{

    char name[4];
    signed long CPU0;
    signed long CPU1;
    signed long CPU2;
    signed long CPU3;
    char ime1[256];
    char ime2[256];
    char ime3[256];
    char ime4[256];

};
typedef struct  _Sending_stuff Sending_stuff;
struct _Sending_stuff{

    int mem;
    gboolean show;
    gchar command [10];
    gchar task_id [256];
};

typedef struct _Devices Devices;
struct _Devices {


    gchar		name[256];
    gchar       type[256];
    gchar       directory[256];
    glong used;
    glong total;
    glong free;
    glong avail;
    glong fid;
    gboolean checked;
};
typedef union DATA_S data_s;
union DATA_S {

    Memory_usage memory_usage;
    Interrupts interrupts;
    Cpu_usage cpu_usage;
    Network network;
    Task task;
    Devices devices;
    Sending_stuff stuff;




} ;



#endif //GTKWORLD_COMMON_H
