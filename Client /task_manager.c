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



static bool
get_task_details (int pid, Task *task)
{
    FILE *file;
    char filename[96];
    char buffer[1024];
    snprintf (filename, 96, "/proc/%d/stat", pid);
    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)
        return false;
    fclose (file);

 /*Scanning the short process name is unreliable with scanf when it contains
      spaces, retrieve it manually and fill the buffer
*/

        char *p1, *po, *p2;
        int i = 0;
        p1 = po = strchr (buffer, '(');
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



 //Parse the stat file


        char dummy[256];
        int idummy;

        unsigned  long jiffies_user = 0, jiffies_system = 0;
        struct passwd *pw;
        struct stat sstat;
       // unsigned  long long stime;

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





     //   s=0;
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
        task->checked=false;
     /*   printf( "vreme trajanja rada %d %d %d\n",task->duration.tm_hour,
        task->duration.tm_min,
        task->duration.tm_sec);*/



    return true;
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



        if((dir=opendir(directory))==NULL){
                printf("error task dir %d\n",errno);
        }


    while ((d_file = readdir(dir)) != NULL)
    {
        if ((pid = atoi(d_file->d_name)) > 0)
        {
            if (get_task_details (pid, &tasks_array[g]))
            {
                g++;
                temp=realloc(tasks_array,( /**j*/ g+1)*sizeof(Task));
                if ( temp != NULL ) {
                    tasks_array=temp;
                } else {
                    free(tasks_array);
                }

                *niz=g;





            }

        }

    }


    *array=tasks_array;
   closedir(dir);

   // compare_lists(tasks);

}


