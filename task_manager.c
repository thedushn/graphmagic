//
// Created by dushn on 4.9.17..
//

#include "task_manager.h"
#include "cpu_usage.h"


static void

model_update_tree_iter (GtkTreeModel *model, GtkTreeIter *iter, Task *task)

{
    gchar *vsz, *rss, cpu[16];
    gchar value[14];
    glong old_timestamp;
    gchar *old_state;
    gchar *background, *foreground;


    vsz = g_format_size_full (task->vsz, G_FORMAT_SIZE_IEC_UNITS);
    rss = g_format_size_full (task->rss, G_FORMAT_SIZE_IEC_UNITS);

    g_snprintf (value, 14, (more_precision) ? "%.2f" : "%.0f", task->cpu_user + task->cpu_system);
    g_snprintf (cpu, 16, ("%s%%"), value);






    gtk_list_store_set (GTK_LIST_STORE (model), iter,
                        COL_TASK, task->name,
                        COL_PID, task->pid,
                        COL_RSS, task->rss,
                        COL_CPU, task->cpu_user,
                        -1);



    g_free (vsz);
    g_free (rss);
}
static void
get_cpu_percent (guint pid, gulong jiffies_user, gfloat *cpu_user, gulong jiffies_system, gfloat *cpu_system)
{
    static GHashTable *hash_cpu_user = NULL;
    static GHashTable *hash_cpu_system = NULL;
    gulong jiffies_user_old, jiffies_system_old;

    if (hash_cpu_user == NULL)
    {
        hash_cpu_user = g_hash_table_new (NULL, NULL);
        hash_cpu_system = g_hash_table_new (NULL, NULL);
    }

    jiffies_user_old = GPOINTER_TO_UINT (g_hash_table_lookup (hash_cpu_user, GUINT_TO_POINTER (pid)));
    jiffies_system_old = GPOINTER_TO_UINT (g_hash_table_lookup (hash_cpu_system, GUINT_TO_POINTER (pid)));
    g_hash_table_insert (hash_cpu_user, GUINT_TO_POINTER (pid), GUINT_TO_POINTER (jiffies_user));
    g_hash_table_insert (hash_cpu_system, GUINT_TO_POINTER (pid), GUINT_TO_POINTER (jiffies_system));

    if (jiffies_user < jiffies_user_old || jiffies_system < jiffies_system_old)
        return;

    //if (_cpu_count > 0 && jiffies_total_delta > 0)
    if (jiffies_total_delta > 0)
    {
        *cpu_user = (jiffies_user - jiffies_user_old) * 100 / (gfloat)jiffies_total_delta[5];
        *cpu_system = (jiffies_system - jiffies_system_old) * 100 / (gfloat)jiffies_total_delta[5];
    }
    else
    {
        *cpu_user = *cpu_system = 0;
    }

}





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
                g_array_append_val (tasks, task);

            }
        }
    }

    g_dir_close (dir);

    return TRUE;
}
