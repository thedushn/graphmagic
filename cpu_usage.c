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
    unsigned  long user[4]= {0, 0, 0, 0};
    unsigned  long user_nice[4]= {0, 0, 0, 0};
    unsigned  long idle[4]={0, 0, 0, 0};
    unsigned  long system[4]={0, 0, 0, 0};
    float percentage[4]={0,0,0,0};


    int cpu_number1[4]={0, 0, 0, 0};
    static unsigned long jiffies_system [5] = {0, 0, 0, 0,0}, jiffies_total [4] = {0, 0, 0, 0};
    static unsigned long jiffies_user[5] = {0, 0, 0, 0,0};
    static unsigned long jiffies_user_old [4] = {0,0,0,0}, jiffies_system_old [4] = {0,0,0,0}, jiffies_total_old [4] = {0,0,0,0};
    FILE *file;
    gchar *filename = "/proc/stat";
    gchar buffer[1024];
    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)
        exit(1);



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
            cpu_user[i] = (jiffies_user[i] - jiffies_user_old[i]) * 100 / (gdouble) (jiffies_total_delta[i]);
           cpu_system[i] = (jiffies_system[i] - jiffies_system_old[i]) * 100 / (gdouble) (jiffies_total_delta[i]);
        }

        percentage[i] =cpu_user[i] + cpu_system[i];


        cpu[i].percentage =percentage[i];
     //   printf("cpu percentage %f \n", cpu[i].percentage);

        jiffies_user[5]+=jiffies_user[i];

        jiffies_system[5]+=jiffies_system[i];




    }






}

void cpu_percent_change(){


    cpu_percentage(ncpu);
    //  static guint i= 0;
    gfloat j;
    //  gfloat *peak;
    for(int s=0;s<ncpu;s++) {

        j = cpu[s].percentage;
        //   j=4*j;

        g_array_prepend_val(history[s],  j);
        if (history[s]->len > 1)
            g_array_remove_index (history[s], history[s]->len - 1);
        // peak=&g_array_index(history[s],gfloat,i);

        // printf("peak problems: %f \n",*peak);


    }

};
void  cpu_change(){

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
