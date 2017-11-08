//
// Created by dushn on 4.8.17..
//

#ifndef GTKWORLD_CPU_USAGE_H
#define GTKWORLD_CPU_USAGE_H
#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdlib.h>


static int ncpu;
typedef struct _Cpu_usage Cpu_usage;
struct _Cpu_usage {


    gfloat percentage0;
    gfloat percentage1;
    gfloat percentage2;
    gfloat percentage3;
    int number;

};

static gulong jiffies_total_delta[5] = {0,0,0,0,0};


int cpu_number();
Cpu_usage cpu_percentage(int);
Cpu_usage cpu_percent_change(int ncpu);
//gboolean  cpu_change(int ncpu);

//gboolean  cpu_change2();
 void
get_cpu_percent (guint pid, gulong jiffies_user, gfloat *cpu_user, gulong jiffies_system, gfloat *cpu_system);
//void cpu_change(int ncpu);
#endif //GTKWORLD_CPU_USAGE_H
