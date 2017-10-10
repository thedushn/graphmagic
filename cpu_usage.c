//
// Created by dushn on 4.8.17..
//

#include "cpu_usage.h"

#include "main_header.h"

struct Cpu_usage cpu[4];
static gushort _cpu_count = 0;



//void cpu_number (){
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
     //   printf("buffer says %s", buffer);

       // printf("(%d) number of cores \n \n ", c);


    }
  //  printf("(%d) number of cores \n \n ", c);
 //   ncpu = c;

    return c;
}
void cpu_percentage(int cpu_count){



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
    for(int i=0 ; i< cpu_count;i++) {
        cpu[i].number=cpu_number1[i];
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
            cpu_user[i] = (jiffies_user[i] - jiffies_user_old[i]) * 100 / (gdouble) (jiffies_total_delta[i]);
           cpu_system[i] = (jiffies_system[i] - jiffies_system_old[i]) * 100 / (gdouble) (jiffies_total_delta[i]);
        }

        percentage[i] =cpu_user[i] + cpu_system[i];


        cpu[i].percentage =percentage[i];
     //   printf("cpu percentage %f \n", cpu[i].percentage);

      //  jiffies_user[5]+=jiffies_user[i];

        //jiffies_system[5]+=jiffies_system[i];





    }


    jiffies_total_delta[4]= jiffies_total_delta[0]+jiffies_total_delta[1]+jiffies_total_delta[2]+jiffies_total_delta[3];




}

void cpu_percent_change(int ncpu){


    cpu_percentage(ncpu);
    //  static guint i= 0;
    gfloat j;
  //    gfloat *peak;
    for(int s=0;s<ncpu;s++) {

        j = cpu[s].percentage;
        //   j=4*j;

        g_array_prepend_val(history[s],  j);
      //  printf("array size %d\n",history[s]->len);
        if (history[s]->len > 1)
            g_array_remove_index (history[s], history[s]->len - 1);


    }

};
gboolean  cpu_change(int ncpu){


//
//    for(int i=0;i<ncpu;i++){
//        gchar *cpu_usage_text_temp[ncpu];
//        label3 = gtk_label_new(NULL);
//        gtk_box_pack_start(GTK_BOX(hbox), label3, 0, 0, 0);
//        cpu_usage_text_temp[i] = g_strdup_printf(("CPU%d: %2.f%%"), cpu[i].number, cpu[i].percentage);
//        gtk_label_set_text (GTK_LABEL (label3),cpu_usage_text_temp[i]);
//        g_free(cpu_usage_text_temp[i]);
//    }
//
//    return TRUE;


    // label3 = gtk_label_new(NULL);
//    gchar *cpu_usage_text_temp;
//    gtk_box_pack_start(GTK_BOX(hbox), label3, 0, 0, 0);
//    cpu_usage_text_temp = g_strdup_printf(("CPU%d: %2.f%%"), cpu[1].number, cpu[1].percentage);
//    gtk_label_set_text (GTK_LABEL (label3),cpu_usage_text_temp);
//    g_free(cpu_usage_text_temp);
    ////vratiti nazad
    cpu0_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[0].number, cpu[0].percentage);
    cpu1_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[1].number, cpu[1].percentage);
    cpu2_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[2].number, cpu[2].percentage);
    cpu3_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[3].number, cpu[3].percentage);

    gtk_label_set_text (GTK_LABEL (label3),cpu0_usage_text);
    gtk_label_set_text (GTK_LABEL (label4),cpu1_usage_text);
    gtk_label_set_text (GTK_LABEL (label5),cpu2_usage_text);
    gtk_label_set_text (GTK_LABEL (label6),cpu3_usage_text);

    g_free(cpu0_usage_text);
    g_free(cpu1_usage_text);
    g_free(cpu2_usage_text);
    g_free(cpu3_usage_text);
    ////vratiti nazad
return TRUE;
    /*if(data== label3) {

        cpu_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[0].number, cpu[0].percentage);
        gtk_label_set_text (GTK_LABEL (data),cpu_usage_text);
    }
    if(data== label4) {

        cpu_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[1].number, cpu[1].percentage);
        gtk_label_set_text (GTK_LABEL (data),cpu_usage_text);
    }
    if(data== label5) {

        cpu_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[2].number, cpu[2].percentage);
        gtk_label_set_text (GTK_LABEL (data),cpu_usage_text);
    }
    if(data== label6) {

        cpu_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[3].number, cpu[3].percentage);
        gtk_label_set_text (GTK_LABEL (data),cpu_usage_text);
    }
*/

    // return TRUE;
};


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

        *cpu_user = (jiffies_user - jiffies_user_old) * 100 / (gdouble)jiffies_total_delta[4];
        *cpu_system = (jiffies_system - jiffies_system_old) * 100 / (gdouble)jiffies_total_delta[4];
       // printf("total  Delta final %lu user %f system %f \n",jiffies_total_delta[4],*cpu_user,*cpu_system);
    }
    else
    {
        *cpu_user = *cpu_system = 0;
    }

}
//gboolean cpu_change2(){
//FILE *file;
//gchar *filename = "/proc/stat";
//gchar buffer[1024];
//static gulong jiffies_user = 0, jiffies_system = 0, jiffies_total = 0;
//static gulong jiffies_user_old = 0, jiffies_system_old = 0, jiffies_total_old = 0;
//gulong user = 0, user_nice = 0, system = 0, idle = 0;
//
//if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)
//return FALSE;
//
//sscanf (buffer, "cpu\t%lu %lu %lu %lu", &user, &user_nice, &system, &idle);
//
//if (_cpu_count == 0)
//{
//while (fgets (buffer, 1024, file) != NULL)
//{
//if (buffer[0] != 'c' && buffer[1] != 'p' && buffer[2] != 'u')
//break;
//_cpu_count += 1;
//}
//if (_cpu_count == 0)
//_cpu_count = 1;
//}
//
//fclose (file);
//
//jiffies_user_old = jiffies_user;
//jiffies_system_old = jiffies_system;
//jiffies_total_old = jiffies_total;
//
//jiffies_user = user + user_nice;
//jiffies_system = system;
//jiffies_total = jiffies_user + jiffies_system + idle;
//
//
//if (jiffies_total > jiffies_total_old) {
//    jiffies_total_delta[4] = jiffies_total - jiffies_total_old;
//}
//    printf("jiffies_total_delta %lu\n",jiffies_total_delta[4]);
//
//
//return TRUE;
//}