//
// Created by dushn on 4.9.17..
//

#ifndef GTKWORLD_TASKS_C_H
#define GTKWORLD_TASKS_C_H
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct _Task Task;
//gboolean	get_task_list		(GArray *task_list);
GArray *get_task_list2(void);
static gboolean get_task_details (guint pid, Task *task);
static inline int get_pagesize (void);

//static void	model_update_tree_iter				(GtkTreeModel *model, GtkTreeIter *iter, Task *task);

void compare_lists(GArray *array);

static gboolean more_precision;



struct _Task
{
    guint		uid;
    gchar		uid_name[256];
    guint		pid;
    guint		ppid;
    gchar		name[256];
   // gchar		cmdline[1024];
    gchar		state[16];
    gfloat		cpu_user;
    gfloat		cpu_system;
    guint64		vsz;
    guint64		rss;
    gshort		prio;
    guint64     start_time;
    gboolean checked;
};

#endif //GTKWORLD_TASKS_C_H
