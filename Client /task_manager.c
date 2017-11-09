//
// Created by dushn on 4.9.17..
//

#include "task_manager.h"

#include "cpu_usage.h"
#include "functions.h"
#include "errno.h"


void differenceBetweenTimePeriod(struct tm start, struct tm stop, struct tm *diff)
{
    if(stop.tm_sec > start.tm_sec){
        --start.tm_min;
        start.tm_sec += 60;
    }

    diff->tm_sec = start.tm_sec - stop.tm_sec;
    if(stop.tm_min > start.tm_min){
        --start.tm_hour;
        start.tm_min += 60;
    }

    diff->tm_min = start.tm_min - stop.tm_min;
    diff->tm_hour = start.tm_hour - stop.tm_hour;
}





static inline long get_pagesize (void)
{
    static long pagesize = 0;
    if (pagesize == 0)
    {
        pagesize = sysconf (_SC_PAGESIZE);
        if (pagesize == 0)
            pagesize = 4096;
    }
    return pagesize;
}



static gboolean
get_task_details (int pid, Task *task)
{
    FILE *file;
    char filename[96];
    char buffer[1024];
    snprintf (filename, 96, "/proc/%d/stat", pid);
    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)
        return FALSE;
    fclose (file);

 /*Scanning the short process name is unreliable with scanf when it contains
      spaces, retrieve it manually and fill the buffer
*/
    {
        char *p1, *po, *p2;
        int i = 0;
        p1 = po = g_strstr_len (buffer, -1, "(");
        p2 = strrchr (buffer, ')');
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
        char dummy[256];
        int idummy;

        long jiffies_user = 0, jiffies_system = 0;
        struct passwd *pw;
        struct stat sstat;
        unsigned  long long stime;

        sscanf(buffer, "%i %255s %1s %i %i %i %i %i %255s %255s %255s %255s %255s %lu %lu %i %i %i %hi %i %i %llu %llu %llu %255s %255s %255s %i %255s %255s %255s %255s %255s %255s %255s %255s %255s %255s %i %255s %255s",
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
              &task->prio, // nice range from 19 to -19
               &idummy,	// hardcoded 0

               &idummy,	// itrealvalue time in jiffies to next SIGALRM send to this process
               //&stime,	// starttime jiffies the process started after system boot //clock ticks 100 ticks=1sec
               &task->start_time,	// starttime jiffies the process started after system boot //clock ticks 100 ticks=1sec
              /* (unsigned long long*)*/&task->vsz, // vsize in bytes
              /* (unsigned long long*)*/&task->rss, // rss (number of pages in real memory)
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
    //    printf("%lu\n" ,task->start_time);
        stat (filename, &sstat);
        pw = getpwuid (sstat.st_uid);
        task->uid = sstat.st_uid;
        strncpy (task->uid_name, (pw != NULL) ? pw->pw_name : "nobody", sizeof (task->uid_name));
         long long  sec, hr, min, t;
         long long h,m,s;
        struct tm   diff;


        sec=task->start_time/100;
        hr =sec /3600;
        t = sec%3600;
        min = t/60;
        sec = t%60;





        s=0;
        h=0;
        m=0;
        s=sec+pocetno.tm_sec;
        if(s>60)
        {
            m=s/60;
            s=s%60;
        }
        m=m+min+pocetno.tm_min;
        if(m>60)
        {
            h=m/60;
            m=m%60;
        }
        h=h+pocetno.tm_hour+hr;




        task->stime.tm_hour=0;
        task->stime.tm_min=0;
        task->stime.tm_sec=0;
        task->stime.tm_hour=(int)h;
        task->stime.tm_min=(int)m;
        task->stime.tm_sec=(int)s;


       /* start_time.tm_sec=s;
        start_time.tm_min=m;
        start_time.tm_hour=h;*/
     /*   printf( "start %d %d %d\n",task->stime.tm_hour,
                task->stime.tm_min,
                task->stime.tm_sec);
        printf( "lokalno %d %d %d\n",tm1.tm_hour,
                tm1.tm_min,
                tm1.tm_sec);*/
        differenceBetweenTimePeriod(tm1, task->stime, &diff);
        task->duration.tm_hour=diff.tm_hour;
        task->duration.tm_min=diff.tm_min;
        task->duration.tm_sec=diff.tm_sec;
     /*   printf( "vreme trajanja rada %d %d %d\n",task->duration.tm_hour,
        task->duration.tm_min,
        task->duration.tm_sec);*/
    }



 /*Read the full command line
    if (!get_task_cmdline (task))
        return FALSE;
*/

    return TRUE;
}
void
get_task_list (Task * * array,int *niz)
{

    Task *tasks_array, *temp;
    tasks_array=malloc(sizeof(Task));
    DIR *dir;
    struct dirent *d_file;
    char *directory="/proc";
    int pid;
    int g=0;
    Task task = { 0 };


        if((dir=opendir(directory))==NULL){
                printf("error task dir %d\n",errno);
        }


    while ((d_file = readdir(dir)) != NULL)
    {
        if ((pid = atoi(d_file->d_name)) > 0)
        {
            if (get_task_details (pid, &tasks_array[g]))
            {
                temp=realloc(tasks_array,( /**j*/ g+2)*sizeof(Task));
                if ( temp != NULL ) {
                    tasks_array=temp;
                } else {
                    free(tasks_array);
                }
                g++;
                *niz=g;





            }

        }

    }
    printf("g %d",g);
    for(int i=0;i<g;i++){


        printf("%s %d \n",tasks_array[i].name,tasks_array[i].pid);
    }
    g=0;
    *array=tasks_array;
   closedir(dir);

   // compare_lists(tasks);

}
GArray *get_task_list2(void) {
    GDir *dir;

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
                g_array_prepend_val (task_list, task);
            }
        }
    }

    g_dir_close (dir);

    return task_list;


}
//void compare_lists(GArray *array){
//
//    GArray *temp;
//   temp= g_array_new (FALSE, FALSE, sizeof (Task));
//
//
//}

