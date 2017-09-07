//
// Created by dushn on 4.8.17..
//

#ifndef GTKWORLD_CPU_USAGE_H
#define GTKWORLD_CPU_USAGE_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
static int ncpu=1;
static gulong jiffies_total_delta[5] = {0,0,0,0,0};
 struct Cpu_usage {


    gfloat percentage;
    int number;

};

int cpu_number();
void cpu_percentage(int);
#endif //GTKWORLD_CPU_USAGE_H
