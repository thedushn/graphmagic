//
// Created by dushn on 23.10.17..
//

#ifndef GTKWORLD_COMMON_H
#define GTKWORLD_COMMON_H

#include "gtk/gtk.h"


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


typedef struct _Task Task;

struct _Task
{
    guint		uid;
    gchar		uid_name[256];
    guint		pid;
    guint		ppid;
    gchar		name[256];
    // gchar		cmdline[1024];
    gchar		state[16];
    gfloat		cpu_user;
    gfloat		cpu_system;
    guint64		vsz;
    guint64		rss;
    gshort		prio;
    unsigned long long     start_time;
    struct tm duration;
    struct tm stime;
    gboolean checked;
};

typedef struct _Network Network;
struct _Network{

    unsigned  long received_bytes;
    unsigned  long transmited_bytes;



};
typedef struct _Cpu_usage1 Cpu_usage1;
struct _Cpu_usage1 {


    gfloat percentage0;
    gfloat percentage1;
    gfloat percentage2;
    gfloat percentage3;
    int number;

};

typedef struct  _Sending_stuff Sending_stuff;
struct _Sending_stuff{

    int mem;
    gboolean show;
    gchar command [10];
    gchar task_id [256];
};
typedef union DATA_S data_s;
union DATA_S {

    Memory_usage Memory;
    Interrupts interrupts;
    Cpu_usage1 cpu_usage;
    Network network;
    Task task;
    Devices devices;
    Sending_stuff stuff;



} ;



#endif //GTKWORLD_COMMON_H
