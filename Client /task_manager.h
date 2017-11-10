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
GArray *get_task_list2(void);
static gboolean get_task_details (int pid, Task *task);
static inline long get_pagesize (void);

//static void	model_update_tree_iter				(GtkTreeModel *model, GtkTreeIter *iter, Task *task);

void compare_lists(GArray *array);

static gboolean more_precision;
void differenceBetweenTimePeriod(struct tm start, struct tm stop, struct tm *diff);



#endif //GTKWORLD_TASKS_C_H
