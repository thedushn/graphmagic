//
// Created by dushn on 4.9.17..
//

#ifndef GTKWORLD_TASKS_C_H
#define GTKWORLD_TASKS_C_H


#include "common.h"


int get_task_list(Task **array, __int32_t *niz);

int get_task_details(int pid, Task *task);

void differenceBetweenTimePeriod(struct tm start, struct tm1 stop, struct tm1 *diff);


#endif //GTKWORLD_TASKS_C_H
