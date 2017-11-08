//
// Created by dushn on 4.8.17..
//

#include "cpu_usage.h"








//void cpu_number (){
int cpu_number (){

    int c=0;
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
     //   printf("buffer says %s", buffer);

       // printf("(%d) number of cores \n \n ", c);


    }
    fclose(file);
  //  printf("(%d) number of cores \n \n ", c);
 //   ncpu = c;

    return c;
}
void cpu_percentage(int cpu_count,Cpu_usage *cpu_usage){



    gfloat cpu_user[4];
    gfloat cpu_system[4];
    unsigned  long user[4]={0,0,0,0};
    unsigned  long user_nice[4]={0,0,0,0};
    unsigned  long idle[4]={0,0,0,0};
    unsigned  long system[4]={0,0,0,0};
    float percentage[4]={0,0,0,0};


    int cpu_number1[4]={0,0,0,0};
    static unsigned long jiffies_system [4]={0,0,0,0}, jiffies_total [4]={0,0,0,0};
    static unsigned long jiffies_user[4]={0,0,0,0};
    static unsigned long jiffies_user_old [4]={0,0,0,0}, jiffies_system_old [4]={0,0,0,0}, jiffies_total_old [4]={0,0,0,0};;
     unsigned long test=0;
    FILE *file;
    gchar *filename = "/proc/stat";
    gchar buffer[1024];
    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)

        exit(1);
   // sscanf(buffer,"cpu%4d  %lu %lu %lu %lu",&cpu_number1[5],&user[5] , &user_nice[5], &system[5], &idle[5]);


    static int j=0;
  //  printf(" CPU buffer before:%s\n",buffer);
    while (fgets(buffer, 1024, file) != NULL) {
        if (buffer[0] != 'c' && buffer[1] != 'p' && buffer[2] != 'u')
            break;


   //     printf(" CPU buffer before2:%s\n",buffer);
     //   printf(" j %d\n",j);
        sscanf(buffer,"cpu%4d %lu %lu %lu %lu",&cpu_number1[j],&user[j] , &user_nice[j], &system[j], &idle[j]);
      //  printf("CPu number for the love of god %d %lu %lu %lu %lu",cpu_number1[j],user[j] , user_nice[j], system[j], idle[j]);
       // printf("CPUN:%d USER:%lu USER_NICE:%lu SYSTEM:%lu IDLE:%lu \n",cpu_number1[j],user[j] , user_nice[j], system[j], idle[j]);
       // printf(" CPU buffer::%s\n",buffer);
        j++;
        if (j==cpu_count){
            j=0;
            break;
        }

    }
    fclose (file);
  //  float cpu_percentage[4];

    for(int i=0 ; i< cpu_count;i++) {

     //   printf("Numbers do you see them %d %d \n",cpu_number1[i],i);
        jiffies_user_old[i] = jiffies_user[i];
        jiffies_system_old[i] = jiffies_system[i];
        jiffies_total_old[i] = jiffies_total[i];

        jiffies_user[i] = user[i] + user_nice[i];
        jiffies_system[i] = system[i];
        jiffies_total[i] = jiffies_user[i] + jiffies_system[i] + idle[i];


        cpu_user[i]= cpu_system[i]= 0.0;
        if (jiffies_total[i] > jiffies_total_old[i]) {
            jiffies_total_delta[i] = jiffies_total[i] - jiffies_total_old[i];
          //  printf("total deltaprvi%lu\n",  jiffies_total_delta[i]);
            test+=jiffies_total_delta[i];
            cpu_user[i] = (jiffies_user[i] - jiffies_user_old[i]) * 100 / (float) (jiffies_total_delta[i]);
           cpu_system[i] = (jiffies_system[i] - jiffies_system_old[i]) * 100 / (float) (jiffies_total_delta[i]);
        }

        percentage[i] =cpu_user[i] + cpu_system[i];









    }
    cpu_usage->percentage0 =percentage[0];
        cpu_usage->percentage1 =percentage[1];
        cpu_usage->percentage2 =percentage[2];
        cpu_usage->percentage3 =percentage[3];


    jiffies_total_delta[4]= jiffies_total_delta[0]+jiffies_total_delta[1]+jiffies_total_delta[2]+jiffies_total_delta[3];




}


void
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

    // if (_cpu_count > 0 && jiffies_total_delta > 0)
    if (jiffies_total_delta[4] > 0)
    {

        *cpu_user = (jiffies_user - jiffies_user_old) * 100 / (float)jiffies_total_delta[4];
        *cpu_system = (jiffies_system - jiffies_system_old) * 100 / (float)jiffies_total_delta[4];
        // printf("total  Delta final %lu user %f system %f \n",jiffies_total_delta[4],*cpu_user,*cpu_system);
    }
    else
    {
        *cpu_user = *cpu_system = 0;
    }

}