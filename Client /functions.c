#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"netinet/in.h"
#include"pthread.h"
#include <sys/stat.h>
#include <fcntl.h>
#include "functions.h"
#include "interrupts.h"
#include "cpu_usage.h"
#include <string.h>




#define BUF_SIZE 2000

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t   cond = PTHREAD_COND_INITIALIZER;


//int rezultat =1;
bool devices_show=false;

void send_prio_to_task(char *task_id, char *signal)
{
    int prio=0;
    if(strcmp(signal,"VERY_LOW")==0){
        prio = 15;

    }
    if(strcmp(signal,"LOW")==0){
        prio = 5;

    }
    if(strcmp(signal,"NORMAL")==0){
        prio = 0;

    }
    if(strcmp(signal,"VERY_HIGH")==0){
        prio = -15;

    }
    if(strcmp(signal,"HIGH")==0){
        prio = -5;

    }


    char str[4];

    sprintf(str,"%d",prio);
    char command[64] = "renice -n ";
    strncat(command,str, sizeof command);
    strncat(command," -p ", sizeof command);
    strncat(command,task_id, sizeof command);
    printf("COMMAND %s\n",command);
    if(system(command) != 0){

        printf("comand failed\n");
    }

    //return (res== 0 ) ? TRUE : FALSE;

}
void send_signal_to_task(char *task_id, char *signal)
{
    printf("SIGNAL %s the task with ID %s\n", signal, task_id);
    if(task_id != "" && signal != NULL)
    {
        char command[64] = "kill -";
        strncat(command,signal, sizeof command);
        strncat(command," ", sizeof command);
        strncat(command,task_id, sizeof command);
        printf("Task id %s",task_id);
        if(system(command) != 0)
            printf("comand failed\n");
//            xfce_err("Couldn't %s the task with ID %s", signal, task_id);
    }
}
void *accept_c(void *socket){
    printf("usli smo u accpet\n");
    struct	my_thread_info *info = socket;
   /*static*/ int rezultat =1;
/*    char buffer[BUF_SIZE];
    gboolean res=FALSE;*/
    data_s data;
  /*  struct Sending_stuff{

       int mem;
        gboolean show;
        gchar command [10];
        gchar task_id [256];
    }stuff;*/

    while (1) {
     //  pthread_mutex_lock (&m);
        printf("ovdde sni");
       int ret = (int )recvfrom(info->thread_socket, &data.stuff, sizeof(data), 0, NULL, NULL);
        if(ret<0){
            printf("error condition didnt get received\n");
            //exit(1);
            pthread_cancel(t2);
            pthread_exit(&ret);
        }
       rezultat=data.stuff.mem;
        devices_show=data.stuff.show;

        printf("sHOW %s\n", data.stuff.show==true ? "TRUE" : "FALSE");
        printf("SHOW %s\n", devices_show==true ? "TRUE" : "FALSE");

        printf("command %s\n ",data.stuff.command);
        printf("id %s\n ",data.stuff.task_id);

        if(strcmp(data.stuff.task_id, "") != 0 && strcmp(data.stuff.command, "") != 0){
            if(strcmp(data.stuff.command, "STOP") == 0 ||
                    strcmp(data.stuff.command, "CONT") == 0 ||
                    strcmp(data.stuff.command, "KILL") == 0 ||
                    strcmp(data.stuff.command, "TERM") == 0){
                send_signal_to_task(data.stuff.task_id,data.stuff.command);
            }
            else{

               /*res= */ send_prio_to_task(data.stuff.task_id,data.stuff.command);
            }
           // printf("DA li smo uspeli %s\n", res==TRUE ? "TRUE" : "FALSE");
        }
        if(rezultat==0){
         //   pthread_cond_wait(&cond,&m);
            rezultat=1;

            pthread_cond_signal(&cond);
          //  pthread_mutex_unlock (&m);
           printf("condition WAS met\n");

       } /*else{

       //     pthread_cond_signal(&cond);
         //   printf("condition signal was sent\n");
        }*/

      //  pthread_mutex_unlock (&m);
    }

};



void *slanje(void *socket){

    int  ret=0;

    printf("interrupti %d",(int)sizeof(Interrupts));
    printf("memory %d",(int)sizeof(Memory_usage));
    printf("devices %d",(int)sizeof(Devices));
    printf("tasks %d",(int)sizeof(Task));
    printf("cpu %d",(int)sizeof(Cpu_usage));
    printf("stuff %d",(int)sizeof(Sending_stuff));
    printf("network %d",(int)sizeof(Network));
    // printf("tm %d\n",(int)sizeof(struct tm));
    printf("tm1 %d\n",(int)sizeof(struct tm1));
  //  printf("const char * %d\n",(int)sizeof(const char *));
  //  printf("const char * %d\n",(int)sizeof(long int));
    printf("uns long long  %d\n",(int)sizeof(unsigned long long));
    time_t time1;
    static struct	my_thread_info *info;



    data_s data;
    Devices  *devices;
    Interrupts  *interrupts;
    Task *task_array;


    while(1) {
        info = malloc(sizeof(struct my_thread_info));
        info->thread_socket= *(int*)socket;
//        if(rezultat==1){
//            pthread_cond_wait(&cond,&m);
//            printf("condition WAS met\n");
//        }


        data.memory_usage.percentage=0;
        data.memory_usage.memory_used=0;
        data.memory_usage.swap_total=0;
        data.memory_usage.swap_percentage=0;
        data.memory_usage.memory_total=0;
        data.memory_usage.swap_used=0;

        get_memory_usage(&data.memory_usage);
        time1 = time(NULL);
        /*    struct tm*/ lokalno_vreme = *localtime(&time1);
//        if(rezultat==0){
//            pthread_cond_wait(&cond,&m);
//           printf("condtion was met\n");
//       }


        ret = (int) send(info->thread_socket, &data, sizeof(data_s), 0);

        if (ret < 0) {
            printf("Error sending data!\n\t");
           break;
            //exit(1);
        } else {

                printf(" sending data!\n\t %f %lli %lli %lli \n", data.memory_usage.swap_percentage,
                       data.memory_usage.swap_used
                        ,data.memory_usage.memory_total,
                       data.memory_usage.memory_used);

        }

        int h=0;

        interrupt_usage2(&interrupts,&h);



        int j=h;
        for(int r=0;r<j;r++){

            printf("hello[%s %li %li %li %li %s %s %s %s]\n",interrupts[r].name, interrupts[r].CPU0, interrupts[r].CPU1,
                   interrupts[r].CPU2,
                   interrupts[r].CPU3,
                   interrupts[r].ime1,
                   interrupts[r].ime2,
                   interrupts[r].ime3,
                   interrupts[r].ime4 );

        }


        printf("J %d\n",j);
        ret = (int) send(info->thread_socket, &j, sizeof(__int32_t), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
              break;
            pthread_cancel(t3);
            pthread_exit(&ret);
        }
        for (int i = 0; i < j; i++) {

            Interrupts *interrupts1;
            interrupts1 = &interrupts[i];
            data.interrupts.CPU0 = interrupts1->CPU0;
            data.interrupts.CPU1 = interrupts1->CPU1;
            data.interrupts.CPU2 = interrupts1->CPU2;
            data.interrupts.CPU3 = interrupts1->CPU3;
            for (int n = 0; n < sizeof(interrupts1->name); n++) {
                data.interrupts.name[n] = interrupts1->name[n];
            }
 /*  printf(" sending data!\n\t %lu %lu %lu %lu %s %s %s %s %s  \n", data.interrupts.CPU0,data.interrupts.CPU1,data.interrupts.CPU2,
                   data.interrupts.CPU3,  data.interrupts.name,data.interrupts.ime1,data.interrupts.ime2,data.interrupts.ime3,data.interrupts.ime4);*/
            upis_imena(interrupts1, &data.interrupts);
            printf(" sending data!\n\t %lu %lu %lu %lu %s %s %s %s %s  \n", data.interrupts.CPU0,data.interrupts.CPU1,data.interrupts.CPU2,
                   data.interrupts.CPU3,  data.interrupts.name,data.interrupts.ime1,data.interrupts.ime2,data.interrupts.ime3,data.interrupts.ime4);
            ret = (int) send(info->thread_socket, &data, sizeof(data.interrupts), 0);
            printf("SIZE OF %d \n",(int)sizeof(data_s));
            if (ret < 0) {
                printf("Error sending data!\n\t");
                  break;
                exit(1);
            }
        }





        int ncpu = cpu_number();
        printf("NUMBER %d \n",ncpu);
          cpu_percentage(ncpu,&data.cpu_usage);

        ret = (int) send(info->thread_socket, &data, sizeof(data_s), 0);
        if (ret < 0) {
            printf("Error sending data!\n\t");
              break;
            exit(1);
        } else {
                   printf("CPU usage %f %f %f %f\n",data.cpu_usage.percentage0,
                   data.cpu_usage.percentage1,
                   data.cpu_usage.percentage2,
                  data.cpu_usage.percentage3);
        }
      //  GArray *task_list =g_array_new(FALSE,FALSE,sizeof(Task));

        int niz_task=0;
        get_task_list(&task_array,&niz_task);
      //  num_packets = task_list->len;
      //  int broj_koji_treba_promenit=(int)num_packets;
//
       ret = (int) send(info->thread_socket, &niz_task, sizeof(int), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");

            exit(1);
        }
        for (int i = 0; i < niz_task; i++) {


            size_t g = strlen(task_array[i].name);
            for (int r = 0; r <= g; r++) {

                data.task.name[r] = task_array[i].name[r];

            }
            g = strlen(task_array[i].state);
            for (int r = 0; r <= g; r++) {

               data.task.state[r] =task_array[i].state[r];

            }
            g = strlen(task_array[i].uid_name);
            for (int r = 0; r <= g; r++) {

               data.task.uid_name[r] = task_array[i].uid_name[r];

            }
            data.task.uid = task_array[i].uid;
            data.task.cpu_system = task_array[i].cpu_system;
            data.task.cpu_user = task_array[i].cpu_user;
            data.task.vsz = task_array[i].vsz;
            data.task.rss =task_array[i].rss;
            data.task.prio = task_array[i].prio;

            data.task.pid = task_array[i].pid;
            data.task.ppid = task_array[i].ppid;
            data.task.start_time=task_array[i].start_time;
            data.task.duration.tm_sec =task_array[i].duration.tm_sec;
            data.task.duration.tm_min =task_array[i].duration.tm_min;
            data.task.duration.tm_hour =task_array[i].duration.tm_hour;
            data.task.stime.tm_sec =task_array[i].stime.tm_sec;
            data.task.stime.tm_min =task_array[i].stime.tm_min;
            data.task.stime.tm_hour =task_array[i].stime.tm_hour;
          //  data.task.checked=false;
            printf( "vreme trajanja rada %d %d %d\n",data.task.duration.tm_hour,
                    data.task.duration.tm_min,
                    data.task.duration.tm_sec);
            printf( "start time %d %d %d\n",data.task.stime.tm_hour,
                    data.task.stime.tm_min,
                    data.task.stime.tm_sec);
            printf("Name [%s]  checked [%hu] pid [%d] start_time[%llu] prio [%d] %llu %llu %d %d %f %f %s %s\n",data.task.name
                    ,data.task.checked
                    ,data.task.pid
                    ,data.task.start_time
                    ,data.task.prio
                    ,data.task.rss
                    ,data.task.vsz,
                   data.task.uid,
                   data.task.ppid,
                   data.task.cpu_user,
                   data.task.cpu_system,
                   data.task.state,
                   data.task.uid_name
            )   ;

            ret = (int) send(info->thread_socket, &data, sizeof(data_s), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                  break;
                exit(1);
            }
          }




        printf("tasks %d",(int)sizeof(Task));

        int niz=0;
        device2(&devices,devices_show,&niz);



        printf("Devices num %d\n",niz);

        ret = (int) send(info->thread_socket, &niz, sizeof(int), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
            break;
            exit(1);
        }
        for(int r=0;r<niz;r++){

            printf("Devices %lu, %lu,%lu,%lu %lu, %s %s %s\n",
                   devices[r].used,devices[r].avail,
                   devices[r].fid,devices[r].free,devices[r].total,
                   devices[r].name,devices[r].directory,devices[r].type);

        }
        for (int i = 0; i < niz; i++) {




            size_t g = strlen(devices[i].name);
            for (int r = 0; r <= g; r++) {

                data.devices.name[r] = devices[i].name[r];

            }
            g = strlen(devices[i].directory);
            for (int r = 0; r <= g; r++) {

                data.devices.directory[r] = devices[i].directory[r];

            }
            g = strlen(devices[i].type);
            for (int r = 0; r <= g; r++) {

                data.devices.type[r] = devices[i].type[r];

            }
            data.devices.avail =devices[i].avail;
            data.devices.fid = devices[i].fid;
            data.devices.free = devices[i].free;
            data.devices.total = devices[i].total;
            data.devices.used =devices[i].used;
            data.devices.checked=false;

            //    printf("%lu, %lu,%lu,%lu %lu, %s %s %s\n",data.devices.used,data.devices.avail,data.devices.fid,data.devices.free,data.devices.total,data.devices.name,data.devices.directory,data.devices.type);
            ret = (int) send(info->thread_socket, &data, sizeof(data_s), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                  break;
                exit(1);
            }
        }




      //  data.network=received_transfered();
        received_transfered2(&data.network);
        ret = (int) send(info->thread_socket, &data, sizeof(data_s), 0);
        printf("Network %lu, %lu\n ",data.network.received_bytes,data.network.transmited_bytes);
        if (ret < 0) {
            printf("Error sending data!\n\t");
              break;
            exit(1);
        }




        lokalno_vreme.tm_year+=1900;
        lokalno_vreme.tm_mon+=1;
        struct tm1 test;
        test.tm_sec=lokalno_vreme.tm_sec;
        test.tm_min=lokalno_vreme.tm_min;
        test.tm_hour=lokalno_vreme.tm_hour;
        test.tm_mday=lokalno_vreme.tm_mday;
        test.tm_mon=lokalno_vreme.tm_mon;
        test.tm_year=lokalno_vreme.tm_year;
        test.tm_wday=lokalno_vreme.tm_wday;
        test.tm_yday=lokalno_vreme.tm_yday;
        test.tm_isdst=lokalno_vreme.tm_isdst;
        ret = (int) send(info->thread_socket, &test, sizeof(struct tm1), 0);
        if (ret<0) {
            printf("ERROR: Return Code  is %d\n", ret);
            break;
            exit(1);
        }
        printf("now: %d-%d-%d %d:%d:%d\n", test.tm_year , test.tm_mon ,
               test.tm_mday,
               test.tm_hour,
               test.tm_min,
               test.tm_sec);
       /* printf("vreme%d %d %d %d %d %d %d %d %d \n",  test.tm_sec=lokalno_vreme.tm_sec,
        test.tm_min=lokalno_vreme.tm_min,
        test.tm_hour=lokalno_vreme.tm_hour,
        test.tm_mday=lokalno_vreme.tm_mday,
        test.tm_mon=lokalno_vreme.tm_mon,
        test.tm_year=lokalno_vreme.tm_year,
        test.tm_wday=lokalno_vreme.tm_wday,
        test.tm_yday=lokalno_vreme.tm_yday,
        test.tm_isdst=lokalno_vreme.tm_isdst);*/
        free(task_array);
        free(devices);
        free(interrupts);
        free(info);
            printf("pre\n");

       // sleep(1);
            pthread_cond_wait(&cond, &m);
            printf("posle\n");


        }
    free(task_array);
    free(devices);
    free(interrupts);
    free(info);
    pthread_cancel(t3);
    printf("everything freed in slanje\n");

    return 0;
};
