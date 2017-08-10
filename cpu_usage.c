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
struct Cpu_usage cpu[4];
static gushort _cpu_count = 0;
static gulong jiffies_total_delta[4] = {0,0,0,0};


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
            break;
        }
        printf("buffer says %s", buffer);

        printf("(%d) number of cores \n \n ", c);


    }
    printf("(%d) number of cores \n \n ", c);
    ncpu = c;

    return c;
}
void cpu_percentage(int cpu_count){



    gfloat cpu_user;
    gfloat cpu_system;
    unsigned  long user[4];
    unsigned  long user_nice[4];
    unsigned  long idle[4];
    unsigned  long system[4];
    unsigned  long total;
    unsigned  long total_old;
    unsigned  long user_old;
    unsigned  long system_old;
    int cpu_number1[3];
    static unsigned long jiffies_system [5] = {0, 0, 0, 0,0}, jiffies_total [5] = {0, 0, 0, 0,0};
    static unsigned long jiffies_user[5] = {0, 0, 0, 0,0};
    static unsigned long jiffies_user_old [5] = {0,0,0,0,0}, jiffies_system_old [5] = {0,0,0,0,0}, jiffies_total_old [5] = {0,0,0,0,0};
    FILE *file;
    gchar *filename = "/proc/stat";
    gchar buffer[1024];
    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)
        exit(1);

    //sscanf (buffer, "cpu\t%lu %lu %lu %lu ", &user[0] , &user_nice[0], &system[0], &idle[0] );
    printf("%lu %lu %lu %lu\n", user[0] , user_nice[0], system[0], idle[0]);
   for(int i=0 ; i< cpu_count;i++) {

           printf(" CPU buffer before:%s\n",buffer);
           while (fgets(buffer, 1024, file) != NULL) {
               if (buffer[0] != 'c' && buffer[1] != 'p' && buffer[2] != 'u')
                   break;
               printf(" CPU buffer before2:%s\n",buffer);
                 sscanf(buffer,"cpu%4d %lu %lu %lu %lu",&cpu_number1[i],&user[i+1] , &user_nice[i+1], &system[i+1], &idle[i+1]);
               printf("CPu number for the love of god %d %lu %lu %lu %lu",cpu_number1[i],user[i+1] , user_nice[i+1], system[i+1], idle[i+1]);
               printf("CPUN:%d USER:%lu USER_NICE:%lu SYSTEM:%lu IDLE:%lu \n",cpu_number1[i],user[i+1] , user_nice[i+1], system[i+1], idle[i+1]);
               printf(" CPU buffer::%s\n",buffer);

           }
           jiffies_user_old[i] = jiffies_user[i];
           jiffies_system_old[i] = jiffies_system[i];
           jiffies_total_old[i] = jiffies_total[i];

           jiffies_user[i] = user[i] + user_nice[i];
           jiffies_system[i] = system[i];
           jiffies_total[i] = jiffies_user[i] + jiffies_system[i] + idle[i];

           cpu[i].user = cpu[i].system = 0.0;
           if (jiffies_total[i] > jiffies_total_old[i]) {
               jiffies_total_delta[i] = jiffies_total[i] - jiffies_total_old[i];
               cpu[i].user = (jiffies_user[i] - jiffies_user_old[i]) * 100 / (gdouble) (jiffies_total_delta[i]);
               cpu[i].system = (jiffies_system[i] - jiffies_system_old[i]) * 100 / (gdouble) (jiffies_total_delta[i]);
           }
           //  cpu.count = _cpu_count;
           // printf("cpu count in struct %d",_cpu_count);
           cpu[i].percentage = cpu[i].user + cpu[i].system;
           printf("cpu percentage %d \n", cpu[i].percentage);


   }
    fclose (file);


   // printf("%lu %lu %lu %lu\n", &user , &user_nice, &system, &idle);


  /*  for(int j =0 ;j<=cpu_count;j++) {
        jiffies_user_old[j] = jiffies_user[j];
        jiffies_system_old[j] = jiffies_system[j];
        jiffies_total_old[j] = jiffies_total[j];

        jiffies_user[j] = user[j] + user_nice[j];
        jiffies_system[j] = system[j];
        jiffies_total[j] = jiffies_user[j] + jiffies_system[j] + idle[j];

        cpu[j].user = cpu[j].system = 0.0;
        if (jiffies_total[j] > jiffies_total_old[j]) {
            jiffies_total_delta[j] = jiffies_total[j] - jiffies_total_old[j];
            cpu[j].user = (jiffies_user[j] - jiffies_user_old[j]) * 100 / (gdouble) (jiffies_total_delta[j]);
            cpu[j].system = (jiffies_system[j] - jiffies_system_old[j]) * 100 / (gdouble) (jiffies_total_delta[j]);
        }
        //  cpu.count = _cpu_count;
        // printf("cpu count in struct %d",_cpu_count);
        cpu[j].percentage = cpu[j].user + cpu[j].system;
        printf("cpu percentage %d \n", cpu[j].percentage);
    }
//    printf("cpu count %hu user %f system %f \n",cpu.count,cpu.user,cpu.system);


*/



}
