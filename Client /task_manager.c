//
// Created by dushn on 4.9.17..
//

#include "task_manager.h"

#include "cpu_usage.h"
#include "functions.h"
#include "errno.h"
#include <inttypes.h>

void differenceBetweenTimePeriod(struct tm start, struct tm1 stop, struct tm1 *diff)
{
   // printf("enter %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
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
  //  printf("leave %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
}





static inline long get_pagesize (void)
{
//    printf("enter %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
    static long pagesize = 0;
    if (pagesize == 0)
    {
        pagesize = sysconf (_SC_PAGESIZE);
        if (pagesize == 0)
            pagesize = 4096;
    }
 //   printf("exit %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
    return pagesize;
}



 bool
get_task_details (int pid, Task *task)
{
    FILE *file;
    char filename[96];
    char buffer[1024];
    float cpu_user=0;
    float cpu_system=0;

   // printf("enter %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);

    snprintf (filename, 96, "/proc/%d/stat", pid);
  //  printf("/proc/%d/stat\n", pid);
    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL){
        printf("nece da otvori fajl\n");
        return false;
    }
//    printf("reading /proc/%d/stat done\n", pid);
    fclose (file);
 //   printf("closing /proc/%d/stat done\n", pid);
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


    __uint64_t jiffies_user = 0, jiffies_system = 0;
    struct passwd *pw;
    struct stat sstat;
    // unsigned  long long stime;

    sscanf(buffer, "%i %255s %1s %i %i %i %i %i %255s %255s %255s %255s %255s %" SCNu64 "   %" SCNu64 " %i %i %i %hi %i %i  %" SCNu64 " %" SCNu64 " %" SCNu64 " %255s %255s %255s %i %255s %255s %255s %255s %255s %255s %255s %255s %255s %255s %i %255s %255s",
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
    get_cpu_percent (task->pid, jiffies_user, &cpu_user, jiffies_system, &cpu_system);
    if(sprintf(task->cpu_user,"%f",cpu_user)<0) {

        printf("nije uspelo convertovanje %s \n",task->cpu_user);
    }
    if(sprintf(task->cpu_system,"%f",cpu_system)<0) {

        printf("nije uspelo convertovanje %s \n",task->cpu_system);
    }
    //  printf("total1  Delta final %lu user %f system %f \n",jiffies_total_delta[4],task->cpu_user,task->cpu_system);
    //    printf("%lu\n" ,task->start_time);
    stat (filename, &sstat);
    pw = getpwuid (sstat.st_uid);
    task->uid = sstat.st_uid;
    strncpy (task->uid_name, (pw != NULL) ? pw->pw_name : "nobody", sizeof (task->uid_name));
    __uint64_t  sec, hr, min, t;
    __uint64_t h,m,s;
    struct tm1   diff;


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
    task->stime.tm_hour=(__uint32_t )h;
    task->stime.tm_min=(__uint32_t)m;
    task->stime.tm_sec=(__uint32_t)s;


/*     start_time.tm_sec=s;
     start_time.tm_min=m;
     start_time.tm_hour=h;*/


     differenceBetweenTimePeriod(lokalno, task->stime, &diff);
     task->duration.tm_hour=diff.tm_hour;
     task->duration.tm_min=diff.tm_min;
     task->duration.tm_sec=diff.tm_sec;
     task->checked=false;
       printf( "start %d %d %d\n",task->stime.tm_hour,
               task->stime.tm_min,
               task->stime.tm_sec);
       printf( "lokalno %d %d %d\n",lokalno.tm_hour,
               lokalno.tm_min,
               lokalno.tm_sec);
       printf( "vreme trajanja rada %d %d %d\n",task->duration.tm_hour,
       task->duration.tm_min,
       task->duration.tm_sec);



   // printf("enter %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
    return true;
}

int
get_task_list (Task * * array,int *niz)
{
  //  printf("enter %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
    Task *tasks_array;
    Task *temp = NULL;
    tasks_array = calloc(1, sizeof(Task));
    DIR *dir;
    struct dirent *d_file;
    char *directory="/proc";
    int pid=0;
    int g=0;



    if((dir=opendir(directory))==NULL){
        printf("error task dir %d\n",errno);
        return 1;
    }


    while ((d_file = readdir(dir)) != NULL)
    {
        //   printf( "Ime file  %s\n",d_file->d_name);

        // if ((pid = atoi (d_file->d_name) > 0))
        if((pid= (int)strtol(d_file->d_name,NULL,0))>0)
            // if ((pid = (int)strtoul (d_file->d_name,NULL,0)) > 0)
        {


            if (get_task_details (pid, &tasks_array[g]))
            {
                g++;
                temp=realloc(tasks_array,( /**j*/ g+1)*sizeof(Task));
                if ( temp != NULL ) {
                    tasks_array=temp;
                } else {
                    free(tasks_array);
                    closedir(dir);
                    printf("relloc error %d \n",errno);
                    return 1;
                }
            }

        }
        else{

            //     printf( "Ime file koji nije prosao %s\n",d_file->d_name);

        }

    }
    temp = realloc(tasks_array, ( /**j*/ g) * sizeof(Task));
    if (temp != NULL) {
        tasks_array = temp;
    } else {
        free(tasks_array);
        closedir(dir);
        printf("relloc error %d \n", errno);
        return 1;
    }

    *niz = g;
    *array=tasks_array;
    closedir(dir);
    return 0;
    // compare_lists(tasks);
   // printf("leave %s in %s:%d \n",__FUNCTION__,__FILE__,__LINE__);
}

