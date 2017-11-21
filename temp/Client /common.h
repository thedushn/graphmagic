//
// Created by dushn on 23.10.17..
//

#ifndef GTKWORLD_COMMON_H
#define GTKWORLD_COMMON_H

#include <stdbool.h>
#include "time.h"



struct __attribute__((__packed__))tm1
{
    __uint32_t tm_sec;			/* Seconds.	[0-60] (1 leap second) */
    __uint32_t tm_min;			/* Minutes.	[0-59] */
    __uint32_t tm_hour;			/* Hours.	[0-23] */
    __uint32_t tm_mday;			/* Day.		[1-31] */
    __uint32_t tm_mon;			/* Month.	[0-11] */
    __uint32_t tm_year;			/* Year	- 1900.  */
    __uint32_t tm_wday;			/* Day of week.	[0-6] */
    __uint32_t tm_yday;			/* Days in year.[0-365]	*/
    __uint32_t tm_isdst;			/* DST.		[-1/0/1]*/

};
typedef struct _Task Task;
struct _Task
{
    bool checked;
    short		prio;
    __uint32_t uid;
    __uint32_t		pid;
    __uint32_t		ppid;
    float		cpu_user;
    float		cpu_system;
    __uint64_t	vsz;
    __uint64_t	rss;
    __int64_t    start_time;
    char		name[256];
    char		uid_name[256];
    char		state[16];
    struct tm1 stime;
    struct tm1 duration;




};
typedef struct _Network Network;
struct _Network{

    unsigned  long received_bytes;
    unsigned  long transmited_bytes;



};
typedef struct _Cpu_usage Cpu_usage;
struct _Cpu_usage {


    float percentage0;
    float percentage1;
    float percentage2;
    float percentage3;
    int number;

};



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
    bool show;
    char command [10];
    char task_id [256];
};

typedef struct _Devices Devices;
struct _Devices {


    char		name[256];
    char       type[256];
    char       directory[256];
    long used;
    long total;
    long free;
    long avail;
    long fid;
    bool checked;
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
