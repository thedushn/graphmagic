//
// Created by dushn on 4.9.17..
//

#include "task_manager.h"










static inline int get_pagesize (void)
{
    static int pagesize = 0;
    if (pagesize == 0)
    {
        pagesize = sysconf (_SC_PAGESIZE);
        if (pagesize == 0)
            pagesize = 4096;
    }
    return pagesize;
}


void  array(){

    tasks=g_array_new (FALSE, FALSE, sizeof (Task));
}

static gboolean
get_task_details (guint pid, Task *task)
{
    FILE *file;
    gchar filename[96];
    gchar buffer[1024];

    snprintf (filename, 96, "/proc/%d/stat", pid);
    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)
        return FALSE;
    fclose (file);

 /*Scanning the short process name is unreliable with scanf when it contains
      spaces, retrieve it manually and fill the buffer
*/
    {
        gchar *p1, *po, *p2;
        guint i = 0;
        p1 = po = g_strstr_len (buffer, -1, "(");
        p2 = g_strrstr (buffer, ")");
        while (po <= p2)
        {
            if (po > p1 && po < p2)
            {
                task->name[i++] = *po;
                task->name[i] = '\0';
            }
            *po = 'x';
            po++;
        }
    }

 //Parse the stat file

    {
        gchar dummy[256];
        gint idummy;
        gulong jiffies_user = 0, jiffies_system = 0;
        struct passwd *pw;
        struct stat sstat;

        sscanf(buffer, "%i %255s %1s %i %i %i %i %i %255s %255s %255s %255s %255s %lu %lu %i %i %i %d %i %i %i %llu %llu %255s %255s %255s %i %255s %255s %255s %255s %255s %255s %255s %255s %255s %255s %i %255s %255s",
               &task->pid,	// processid
               dummy,		// processname
               task->state,	// processstate
               &task->ppid,	// parentid
               &idummy,	// processs groupid

               &idummy,	// session id
               &idummy,	// tty id
               &idummy,	// tpgid the process group ID of the process running on tty of the process
               dummy,		// flags
               dummy,		// minflt minor faults the process has maid

               dummy,		// cminflt
               dummy,		// majflt
               dummy,		// cmajflt
               &jiffies_user,	// utime the number of jiffies that this process has scheduled in user mode
               &jiffies_system,// stime " system mode

               &idummy,	// cutime " waited for children in user mode
               &idummy,	// cstime " system mode
               &idummy,	// priority (nice value + fifteen)
               (gint*)&task->prio, // nice range from 19 to -19
               &idummy,	// hardcoded 0

               &idummy,	// itrealvalue time in jiffies to next SIGALRM send to this process
               &idummy,	// starttime jiffies the process startet after system boot
               (unsigned long long*)&task->vsz, // vsize in bytes
               (unsigned long long*)&task->rss, // rss (number of pages in real memory)
               dummy,		// rlim limit in bytes for rss

               dummy,		// startcode
               dummy,		// endcode
               &idummy,	// startstack
               dummy,		// kstkesp value of esp (stack pointer)
               dummy,		// kstkeip value of EIP (instruction pointer)

               dummy,		// signal. bitmap of pending signals
               dummy,		// blocked: bitmap of blocked signals
               dummy,		// sigignore: bitmap of ignored signals
               dummy,		// sigcatch: bitmap of catched signals
               dummy,		// wchan

               dummy,		// nswap
               dummy,		// cnswap
               dummy,		// exit_signal
               &idummy,	// CPU number last executed on
               dummy,

               dummy
        );

        task->rss *= get_pagesize ();
        get_cpu_percent (task->pid, jiffies_user, &task->cpu_user, jiffies_system, &task->cpu_system);
      //  printf("total1  Delta final %lu user %f system %f \n",jiffies_total_delta[4],task->cpu_user,task->cpu_system);

        stat (filename, &sstat);
        pw = getpwuid (sstat.st_uid);
        task->uid = sstat.st_uid;
        g_strlcpy (task->uid_name, (pw != NULL) ? pw->pw_name : "nobody", sizeof (task->uid_name));
    }


 /*Read the full command line
    if (!get_task_cmdline (task))
        return FALSE;
*/

    return TRUE;
}
gboolean
get_task_list (GArray *tasks)
{
    static int i=0;
    GDir *dir;
    const gchar *name;
    guint pid;
    Task task = { 0 };


    if ((dir = g_dir_open ("/proc", 0, NULL)) == NULL)
        return FALSE;

    while ((name = g_dir_read_name(dir)) != NULL)
    {
        if ((pid = (guint)g_ascii_strtoull (name, NULL, 0)) > 0)
        {
            if (get_task_details (pid, &task))
            {
                g_array_prepend_val (tasks, task);


            }

        }

    }

    g_dir_close (dir);

    compare_lists(tasks);
    return TRUE;
}
void compare_lists(GArray *array){

    GArray *temp;
   temp= g_array_new (FALSE, FALSE, sizeof (Task));


}

/*
void task_update_model (GArray *array1)
{
static GArray *removed_tasks = NULL;
GArray *array;
guint i;



if (removed_tasks == NULL)
removed_tasks = g_array_new (FALSE, FALSE, sizeof (GtkTreeIter));

*/
/* Retrieve initial task list and return *//*

if (tasks->len == 0)
{
get_task_list (tasks);
for (i = 0; i < tasks->len; i++)
{
Task *task = &g_array_index (tasks, Task, i);

model_add_task (manager->model, task, 0);

}
return;
}

*/
/* Retrieve new task list *//*

array = g_array_new (FALSE, FALSE, sizeof (Task));
get_task_list (array);

*/
/* Remove terminated tasks *//*

for (i = 0; i < removed_tasks->len; i++)
{
GtkTreeIter *iter = &g_array_index (removed_tasks, GtkTreeIter, i);
glong old_timestamp;
gtk_tree_model_get (manager->model, iter, XTM_PTV_COLUMN_TIMESTAMP, &old_timestamp, -1);
if (__current_timestamp () - old_timestamp > TIMESTAMP_DELTA)
{
#if DEBUG
gint pid;
			gtk_tree_model_get (manager->model, iter, XTM_PTV_COLUMN_PID, &pid, -1);
			g_debug ("Remove old task %d", pid);
#endif
model_remove_tree_iter (manager->model, iter);
g_array_remove_index (removed_tasks, i);
}
}

for (i = 0; i < manager->tasks->len; i++)
{
guint j;
Task *tasktmp;
Task *task = &g_array_index (manager->tasks, Task, i);
gboolean found = FALSE;

for (j = 0; j < array->len; j++)
{
tasktmp = &g_array_index (array, Task, j);
if (task->pid != tasktmp->pid)
continue;
found = TRUE;
break;
}

if (found == FALSE)
{
GtkTreeIter iter;
#if DEBUG
g_debug ("Task %d '%s' terminated, marking as removed", task->pid, task->name);
#endif
model_find_tree_iter_for_pid (manager->model, task->pid, &iter);
model_mark_tree_iter_as_removed (manager->model, &iter);
g_array_append_val (removed_tasks, iter);
g_array_remove_index (manager->tasks, i);
}
}

*/
/* Append started tasks and update existing ones *//*

for (i = 0; i < array->len; i++)
{
guint j;
Task *tasktmp = &g_array_index (array, Task, i);
gboolean found = FALSE;

for (j = 0; j < manager->tasks->len; j++)
{
Task *task = &g_array_index (manager->tasks, Task, j);
#ifdef HAVE_WNCK
App *app;
#endif
gboolean updated = FALSE;

if (task->pid != tasktmp->pid)
continue;

#ifdef HAVE_WNCK
app = xtm_app_manager_get_app_from_pid (manager->app_manager, task->pid);
#endif
found = TRUE;

*/
/* Update the model (with the rest) only if needed, this keeps the CPU cool *//*

if (model_update_forced
|| task->ppid != tasktmp->ppid
|| g_strcmp0 (task->state, tasktmp->state)
|| task->cpu_user != tasktmp->cpu_user
|| task->cpu_system != tasktmp->cpu_system
|| task->rss != tasktmp->rss
|| task->vsz != tasktmp->vsz
|| task->prio != tasktmp->prio)
{
updated = TRUE;
task->ppid = tasktmp->ppid;
g_strlcpy (task->state, tasktmp->state, sizeof (task->state));
task->cpu_user = tasktmp->cpu_user;
task->cpu_system = tasktmp->cpu_system;
task->rss = tasktmp->rss;
task->vsz = tasktmp->vsz;
task->prio = tasktmp->prio;
#ifdef HAVE_WNCK
model_update_task (manager->model, tasktmp, app);
#else
model_update_task (manager->model, tasktmp);
#endif
}

*/
/* Update command name if needed (can happen) *//*

if (!model_update_forced && g_strcmp0 (task->cmdline, tasktmp->cmdline))
{
GtkTreeIter iter;
gchar *cmdline;

cmdline = pretty_cmdline (tasktmp->cmdline, tasktmp->name);
model_find_tree_iter_for_pid (manager->model, task->pid, &iter);
gtk_list_store_set (GTK_LIST_STORE (manager->model), &iter, XTM_PTV_COLUMN_COMMAND, cmdline, -1);
g_free (cmdline);
}

*/
/* Update color if needed *//*

if (updated == FALSE)
{
GtkTreeIter iter;
gchar *color;
glong old_timestamp;

model_find_tree_iter_for_pid (manager->model, task->pid, &iter);
gtk_tree_model_get (manager->model, &iter, XTM_PTV_COLUMN_BACKGROUND, &color, XTM_PTV_COLUMN_TIMESTAMP, &old_timestamp, -1);

if (color != NULL && __current_timestamp () - old_timestamp > TIMESTAMP_DELTA)
{
#if DEBUG
g_debug ("Remove color from running PID %d", task->pid);
#endif
#ifdef HAVE_WNCK
model_update_task (manager->model, tasktmp, app);
#else
model_update_task (manager->model, tasktmp);
#endif
}

g_free (color);
}

break;
}

if (found == FALSE)
{
#ifdef HAVE_WNCK
App *app = xtm_app_manager_get_app_from_pid (manager->app_manager, tasktmp->pid);
			model_add_task (manager->model, tasktmp, app, __current_timestamp ());
#else
model_add_task (manager->model, tasktmp, __current_timestamp ());
#endif
g_array_append_val (manager->tasks, *tasktmp);
#if DEBUG
g_debug ("Add new task %d %s", tasktmp->pid, tasktmp->name);
#endif
}
}

g_array_free (array, TRUE);
model_update_forced = FALSE;

return;
}
static void
#ifdef HAVE_WNCK
model_add_task (GtkTreeModel *model, Task *task, App *app, glong timestamp)
#else
model_add_task (GtkTreeModel *model, Task *task, glong timestamp)
#endif
{
    GtkTreeIter iter;
    gchar *cmdline;

#ifdef HAVE_WNCK
    if (app != NULL && full_cmdline == FALSE)
		cmdline = g_strdup (app->name);
	else
		cmdline = pretty_cmdline (task->cmdline, task->name);
#else
    cmdline = pretty_cmdline (task->cmdline, task->name);
#endif

    gtk_list_store_append (GTK_LIST_STORE (model), &iter);
    gtk_list_store_set (GTK_LIST_STORE (model), &iter,
                        XTM_PTV_COLUMN_COMMAND, cmdline,
                        XTM_PTV_COLUMN_PID, task->pid,
                        XTM_PTV_COLUMN_STATE, task->state,
                        XTM_PTV_COLUMN_UID, task->uid,
                        XTM_PTV_COLUMN_UID_STR, task->uid_name,
                        XTM_PTV_COLUMN_BACKGROUND, NULL,
                        XTM_PTV_COLUMN_FOREGROUND, NULL,
                        XTM_PTV_COLUMN_TIMESTAMP, timestamp,
                        -1);
#ifdef HAVE_WNCK
    model_update_tree_iter (model, &iter, task, app);
#else
    model_update_tree_iter (model, &iter, task);
#endif

    g_free (cmdline);
}*/
