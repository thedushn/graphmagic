//
// Created by dushn on 3.8.17..
//

#ifndef GKTWORLD_MEMORY_USAGE_H
#define GKTWORLD_MEMORY_USAGE_H
#include <gtk/gtk.h>
#include <math.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"


void get_memory_usage(data_s *memory);
//void get_memory_usage();

#endif //GKTWORLD_MEMORY_USAGE_H
