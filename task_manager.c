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
GArray *get_task_list2(void) {
    GDir *dir;
    struct dirent *dir_entry;
    guint pid;
    const gchar *name;
    GArray *task_list;
    Task task = {0};

    task_list = g_array_new(FALSE, FALSE, sizeof(Task));

    if ((dir = g_dir_open ("/proc", 0, NULL)) == NULL)
        return FALSE;

    while ((name = g_dir_read_name(dir)) != NULL)
    {
        if ((pid = (guint)g_ascii_strtoull (name, NULL, 0)) > 0)
        {
            if (get_task_details (pid, &task))
            {
                g_array_append_val (task_list, task);
            }
        }
    }

    g_dir_close (dir);

    return task_list;


}
void compare_lists(GArray *array){

    GArray *temp;
   temp= g_array_new (FALSE, FALSE, sizeof (Task));


}

