//
// Created by dushn on 4.8.17..
//

#ifndef GTKWORLD_CPU_USAGE_H
#define GTKWORLD_CPU_USAGE_H
#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>


#include <math.h>
#include <stdlib.h>
#include "stdbool.h"

#include "common.h"



static  unsigned long jiffies_total_delta[5] = {0,0,0,0,0};
int cpu_number();
void cpu_percentage(int ncpu,Cpu_usage *cpu_usage);


void get_cpu_percent (unsigned int pid, unsigned long jiffies_user, float *cpu_user, unsigned long jiffies_system, float *cpu_system);

#endif //GTKWORLD_CPU_USAGE_H
