//
// Created by dushn on 3.8.17..
//

#ifndef GKTWORLD_MEMORY_USAGE_H
#define GKTWORLD_MEMORY_USAGE_H
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _Memory_usage Memory_usage;

struct _Memory_usage {

    unsigned long long  memory_used;
    unsigned long long  memory_total;
    float swap_percentage;
    unsigned long long  swap_total;
    unsigned  long long swap_used;
    float percentage ;

};

void get_memory_usage();

#endif //GKTWORLD_MEMORY_USAGE_H
