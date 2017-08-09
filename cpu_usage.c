//
// Created by dushn on 4.8.17..
//

#include "cpu_usage.h"
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>


#include <math.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define  npcu
struct Cpu_usage cpu;
static gushort _cpu_count = 0;
static gulong jiffies_total_delta = 0;


int cpu_number (){

        int c;
    FILE *file;
    gchar *filename = "/proc/cpuinfo";
    gchar buffer[1024];
    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)
        exit(1);
    while (fgets (buffer, 1024, file) != NULL) {
        if (buffer[0] == 'c' && buffer[1] == 'p' && buffer[2] == 'u' && buffer[3] == ' ' && buffer[4] == 'c' &&
        buffer[5] == 'o' && buffer[6] == 'r')
        {
            sscanf(buffer, "cpu cores\t: %d", &c);
        }
        printf("buffer says %s", buffer);

        printf("%d", c);
        ncpu = c;
        return c;
    }

}
void cpu_percentage(){


    gushort cpu_count;
    gfloat cpu_user;
    gfloat cpu_system;
    unsigned  long user;
    unsigned  long user_nice;
    unsigned  long idle;
    unsigned  long system;
    unsigned  long total;
    unsigned  long total_old;
    unsigned  long user_old;
    unsigned  long system_old;
    static unsigned long jiffies_user = 0, jiffies_system = 0, jiffies_total = 0;
    static unsigned long jiffies_user_old = 0, jiffies_system_old = 0, jiffies_total_old = 0;
    FILE *file;
    gchar *filename = "/proc/stat";
    gchar buffer[1024];
    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)
        exit(1);

    sscanf (buffer, "cpu\t%lu %lu %lu %lu ", &user , &user_nice, &system, &idle );

    if (_cpu_count == 0)
    {
        while (fgets (buffer, 1024, file) != NULL)
        {
            if (buffer[0] != 'c' && buffer[1] != 'p' && buffer[2] != 'u')
                break;
            _cpu_count += 1;
          //  sscanf(buffer,"")
        }
        if (_cpu_count == 0)
            _cpu_count = 1;
    }

    fclose (file);

    printf("%lu %lu %lu %lu\n", &user , &user_nice, &system, &idle);




    jiffies_user_old = jiffies_user;
    jiffies_system_old = jiffies_system;
    jiffies_total_old = jiffies_total;

    jiffies_user = user + user_nice;
    jiffies_system = system;
    jiffies_total = jiffies_user + jiffies_system + idle;

    cpu.user = cpu.system = 0.0;
    if (jiffies_total > jiffies_total_old)
    {
        jiffies_total_delta = jiffies_total - jiffies_total_old;
        cpu.user = (jiffies_user - jiffies_user_old) * 100 / (gdouble)(jiffies_total_delta);
        cpu.system = (jiffies_system - jiffies_system_old) * 100 / (gdouble)(jiffies_total_delta);
    }
    cpu.count = _cpu_count;
   // printf("cpu count in struct %d",_cpu_count);
   cpu.percentage=cpu.user+ cpu_system;
        printf("cpu percentage %d \n",cpu.percentage);

//    printf("cpu count %hu user %f system %f \n",cpu.count,cpu.user,cpu.system);






}
