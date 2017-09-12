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
#include "model.h"
typedef struct _Task Task;
gboolean	get_task_list		(GArray *task_list);
static gboolean get_task_details (guint pid, Task *task);
static inline int get_pagesize (void);
static void get_cpu_percent (guint pid, gulong jiffies_user, gfloat *cpu_user, gulong jiffies_system, gfloat *cpu_system);
static void	model_update_tree_iter				(GtkTreeModel *model, GtkTreeIter *iter, Task *task);
void  array();
void compare_lists(GArray *array);
GArray *tasks;
static gboolean more_precision;
struct _Task
{
    guint		uid;
    gchar		uid_name[256];
    guint		pid;
    guint		ppid;
    gchar		name[256];
    gchar		cmdline[1024];
    gchar		state[16];
    gfloat		cpu_user;
    gfloat		cpu_system;
    guint64		vsz;
    guint64		rss;
    gshort		prio;
};
enum
{
    COL_TASK = 0,
    COL_PID,
    COL_RSS,
    COL_CPU,
    COL_VSZ,
    NUM_COLS
} ;
#endif //GTKWORLD_TASKS_C_H
