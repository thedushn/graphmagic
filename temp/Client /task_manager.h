//
// Created by dushn on 4.9.17..
//

#ifndef GTKWORLD_TASKS_C_H
#define GTKWORLD_TASKS_C_H


#include <math.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"


void get_task_list (Task * * array,int *niz);

static bool get_task_details (int pid, Task *task);
static inline long get_pagesize (void);



void differenceBetweenTimePeriod(struct tm start, struct tm1 stop, struct tm1 *diff);



#endif //GTKWORLD_TASKS_C_H
