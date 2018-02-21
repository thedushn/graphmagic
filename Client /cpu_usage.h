//
// Created by dushn on 4.8.17..
//

#ifndef GTKWORLD_CPU_USAGE_H
#define GTKWORLD_CPU_USAGE_H


#include "common.h"

struct DataItem {
    __uint64_t data;
    unsigned int key;
};


int cpu_number();

void cpu_percentage(int ncpu, Cpu_usage *cpu_usage);

void uradi(bool clean);

int
get_cpu_percent(unsigned int pid, __uint64_t jiffies_user, float *cpu_user, __uint64_t jiffies_system,
                float *cpu_system);

__uint64_t search(unsigned int key, struct DataItem *hashArray, int hash_size, bool *ima, __uint64_t data);

#endif //GTKWORLD_CPU_USAGE_H
