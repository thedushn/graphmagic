#include <inttypes.h>
#include"stdio.h"
#include"stdlib.h"

#include"sys/socket.h"

#include"pthread.h"


#include "functions.h"
#include "interrupts.h"
#include "cpu_usage.h"



#define BUF_SIZE 1024

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t   cond = PTHREAD_COND_INITIALIZER;


//int rezultat =1;
bool devices_show=false;
ssize_t test_send(int socket){

    ssize_t  ret=0;
    char buffer[64];
    memset(buffer,0,sizeof(buffer));
    ret= recv(socket, buffer,sizeof(buffer),0);
    printf("Return value %d",(int)ret);
    if (ret < 0) {

        printf("error receing data\n %d",(int) ret);
       return ret;
    }
    if (ret == 0) {

        printf("socket closed\n");
        return ret;
    }
    if(ret<64) {
        size_t velicina = 64;
        velicina -= ret;
        while (velicina > 0 || velicina < 0) {
            printf("Buffer [%s]\n", buffer);

            ret = (int) recv(socket, buffer, velicina, 0);
            velicina -= ret;
            //koliko_bytes+=ret;
            if (ret < 0) {

                printf("error receing data\n %d", (int)ret);
                return ret;
            }
            if (ret == 0) {

                printf("socket closed\n");
               return ret;
            }
            printf("Return value %d",(int) ret);
        }
    }
    if (strcmp(buffer, "stiglo sve") != 0) {

        printf("NOPE  \n");

       return -1;
    }

    return 64;
};
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
    if(task_id != NULL && signal != NULL)
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
   /*static*/ int rezultat ;
/*    char buffer[BUF_SIZE];
    gboolean res=FALSE;*/
   // data_s data;
  /*  struct Commands{

       int mem;
        gboolean show;
        gchar command [10];
        gchar task_id [256];
    }stuff;*/
    Commands commands;

    while (1) {
     //  pthread_mutex_lock (&m);
       /* info = malloc(sizeof(struct my_thread_info));
        info->thread_socket= *(int*)socket;*/
       int ret = (int )recv(info->thread_socket, &commands, sizeof(Commands), NULL);
        if(ret<0){
            printf("error condition didnt get received\n");


            pthread_exit(&ret);
        }
        if(ret==0){
            printf("error condition didnt get received\n");
            printf("ret %d\n",ret);

            pthread_exit(&ret);
        }
        printf("ret accept  %d \n",ret);
       rezultat=commands.mem;
        devices_show=commands.show;

        printf("sHOW %s\n", commands.show==true ? "TRUE" : "FALSE");
        printf("SHOW %s\n", devices_show==true ? "TRUE" : "FALSE");

        printf("command %s\n ",commands.command);
        printf("id %s\n ",commands.task_id);

        if(strcmp(commands.task_id, "") != 0 && strcmp(commands.command, "") != 0){
            if(strcmp(commands.command, "STOP") == 0 ||
                    strcmp(commands.command, "CONT") == 0 ||
                    strcmp(commands.command, "KILL") == 0 ||
                    strcmp(commands.command, "TERM") == 0){
                send_signal_to_task(commands.task_id,commands.command);
            }
            else{

               /*res= */ send_prio_to_task(commands.task_id,commands.command);
            }
           // printf("DA li smo uspeli %s\n", res==TRUE ? "TRUE" : "FALSE");
        }


    }

};



void *slanje(void *socket){

    ssize_t  ret=0;

    printf("usli smo u slanje\n");
        //unsigned int num_packets;

    time_t time1;
    static struct	my_thread_info *info;
    Task *task_array=NULL;
    Interrupts  *interrupts=NULL;
    Devices  *devices=NULL;

    data_s data;

    while(1) {

        Memory_usage memory_usage={0};
        Cpu_usage cpu_usage={0} ;
        Network network={0};
        info = malloc(sizeof(struct my_thread_info));
        info->thread_socket= *(int*)socket;
//        if(rezultat==1){
//            pthread_cond_wait(&cond,&m);
//            printf("condition WAS met\n");
//        }


       // data.memory_usage.memory_percentage=0;
        data.memory_usage.memory_used=0;
        data.memory_usage.swap_total=0;
      //  data.memory_usage.swap_percentage=0;
        data.memory_usage.memory_total=0;
        data.memory_usage.swap_used=0;

        get_memory_usage(&memory_usage);
        time1 = time(NULL);
        /*    struct tm*/
        lokalno = *localtime(&time1);
        /*
//        if(rezultat==0){
//            pthread_cond_wait(&cond,&m);
//           printf("condtion was met\n");
//       }
*/
/*        char buffer[1400];

        memset(buffer,0,sizeof(buffer));
            sprintf(buffer, "%"PRIu64 "%"PRIu64 "%"PRIu64 "%"PRIu64
                    ,memory_usage.swap_used
                    ,memory_usage.swap_total
                    ,memory_usage.memory_used
                    ,memory_usage.memory_total
            );
        strcat(buffer,memory_usage.swap_percentage);
        strcat(buffer,memory_usage.memory_percentage);*/



        ret = send(info->thread_socket, &memory_usage, sizeof(Memory_usage), 0);

        if (ret < 0) {
            printf("Error sending data!\n\t");
              break;

        }   if (ret == 0) {

            printf("socket closed\n");
            break;
        }

        ret=test_send(info->thread_socket);
        if (ret < 0) {
            printf("Error receiving  num_packets!\n\t");
            break;

        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }


            printf(" sending data!\n\t Memory Swap[%s] %" SCNu64 " %" SCNu64 "  %" SCNu64 " Memory[%s]\n"
                    ,memory_usage.swap_percentage
                    , memory_usage.swap_used
                    ,memory_usage.memory_total
                    , memory_usage.memory_used
                    , memory_usage.memory_percentage
            );





     /*   __int32_t h=0;

        interrupt_usage2(&interrupts,&h);



        __int32_t j=h;

        printf("BROJ INT %d \n",j);
        ret = (int) send(info->thread_socket, &j, sizeof(__int32_t), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
              break;

        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }
        ret=test_send(info->thread_socket);
        if (ret < 0) {

            printf("error receing data\n %d",(int) ret);
            break;
        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }
        for(int r=0;r<h;r++){


            ret = (int) send(info->thread_socket, &interrupts[r], sizeof(Interrupts), 0);


            if (ret < 0) {
                printf("Error sending data!\n\t");
                  break;

            }
            if (ret == 0) {

                printf("socket closed\n");
                break;
            }


            ret=test_send(info->thread_socket);
            if (ret < 0) {

                printf("error receing data\n %d",(int) ret);
                break;
            }
            if (ret == 0) {

                printf("socket closed\n");
                break;
            }

            printf("return value of Interrupts ret: %d number of send %d  \n",(int)ret,r );

        }



*/





        __int32_t cpu_num= cpu_number();
          cpu_percentage(cpu_num,&cpu_usage);

            ret = (int) send(info->thread_socket, &cpu_usage, sizeof(Cpu_usage), 0);
            if (ret < 0) {
                printf("Error sending data!\n\t");
                  break;

            }
             if (ret == 0) {

            printf("socket closed\n");
            break;
            }
        ret=test_send(info->thread_socket);
        if (ret < 0) {

            printf("error receing data\n %d",(int) ret);
            break;
        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }





     /*  int niz_task=0;
        get_task_list(&task_array,&niz_task);

        __int32_t niz_temp= (__int32_t) niz_task;
       ret = (int) send(info->thread_socket, &niz_temp, sizeof(__int32_t), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");

            break;

        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }
        ret=test_send(info->thread_socket);
        if (ret < 0) {

            printf("error receing data\n %d",(int) ret);
            break;
        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }*/
/*        for (int i = 0; i < niz_task; i++) {


            size_t g = strlen(task_array[i].name);
            for (int r = 0; r <= g; r++) {

                data.task.name[r] = task_array[i].name[r];

            }
            g = strlen(task_array[i].state);
            for (int r = 0; r <= g; r++) {

                data.task.state[r] = task_array[i].state[r];

            }
            g = strlen(task_array[i].uid_name);
            for (int r = 0; r <= g; r++) {

                data.task.uid_name[r] = task_array[i].uid_name[r];

            }
            data.task.uid = task_array[i].uid;
         //   data.task.cpu_system = task_array[i].cpu_system;
          //  data.task.cpu_user = task_array[i].cpu_user;
            data.task.vsz = task_array[i].vsz;
            data.task.rss = task_array[i].rss;
            data.task.prio = task_array[i].prio;

            data.task.pid = task_array[i].pid;
            data.task.ppid = task_array[i].ppid;

/ data.task.start_time = task_array[i].start_time;
            data.task.duration.tm_sec = task_array[i].duration.tm_sec;
            data.task.duration.tm_min = task_array[i].duration.tm_min;
            data.task.duration.tm_hour = task_array[i].duration.tm_hour;
            data.task.stime.tm_sec = task_array[i].stime.tm_sec;
            data.task.stime.tm_min = task_array[i].stime.tm_min;
            data.task.stime.tm_hour = task_array[i].stime.tm_hour;


     printf("vreme trajanja rada %d %d %d\n", data.task.duration.tm_hour,
                   data.task.duration.tm_min,
                   data.task.duration.tm_sec);
            printf("start time %d %d %d\n", data.task.stime.tm_hour,
                   data.task.stime.tm_min,
                   data.task.stime.tm_sec);
            printf("Name [%s]  checked [%hu] pid [%d] start_time[%" SCNu64 "] prio [%d] %" SCNu64 " %" SCNu64 " %d %d %s %s [%s] [%s]\n",
                   data.task.name, data.task.checked, data.task.pid, data.task.start_time, data.task.prio,
                   data.task.rss, data.task.vsz,
                   data.task.uid,
                   data.task.ppid,
                   data.task.cpu_user,
                   data.task.cpu_system,
                   data.task.state,
                   data.task.uid_name);

        }*/

      /*  for (int i = 0; i < niz_task; i++) {


            ret = (int) send(info->thread_socket, &task_array[i], sizeof(Task), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                 break;

            }
            if (ret == 0) {

                printf("socket closed\n");
                break;
            }

            ret=test_send(info->thread_socket);
            if (ret < 0) {

                printf("error receing data\n %d",(int) ret);
                break;
            }
            if (ret == 0) {

                printf("socket closed\n");
                break;
            }
        }*/
      //  Devices  *devices;

        __int32_t niz=0;
        device2(&devices,devices_show,&niz);
        printf("prosli \n");




        ret = (int) send(info->thread_socket, &niz, sizeof(__int32_t), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");

            break;
        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }
        ret=test_send(info->thread_socket);
        if (ret < 0) {

            printf("error receing data\n %d",(int) ret);
            break;
        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }
    /*    for(int r=0;r<niz;r++){

/* printf("Devices % "SCNu64 ", %"SCNu64 ",%"SCNu64 ",%"SCNu64 "%"SCNu64 ", %s %s %s\n",
                   devices[r].used,devices[r].avail,
                   devices[r].fid,devices[r].free,devices[r].total,
                   devices[r].name,devices[r].directory,devices[r].type);*//*


        }
  */
/*      for (int i = 0; i < niz; i++) {




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

               // printf("%lu, %lu,%lu,%lu %lu, %s %s %s\n",data.devices.used,data.devices.avail,data.devices.fid,data.devices.free,data.devices.total,data.devices.name,data.devices.directory,data.devices.type);
            ret = (int) send(info->thread_socket, &devices[i], sizeof(Devices), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                //  break;
                pthread_cancel(t3);
                pthread_exit(&ret);
            }
        }*/


        for(int i =0;i<niz ;i++){
                    devices[i].checked=false;
            ret = (int) send(info->thread_socket, &devices[i], sizeof(Devices), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                  break;

            }
            if (ret == 0) {

                printf("socket closed\n");
                break;
            }
            ret=test_send(info->thread_socket);
            if (ret < 0) {

                printf("error receing data\n %d",(int) ret);
                break;
            }
            if (ret == 0) {

                printf("socket closed\n");
                break;
            }
            printf("Return value devices %d \n", (int)ret);


        }


        printf("Before Network  %" SCNu64 ", %" SCNu64 "\n ",network.received_bytes,network.transmited_bytes);
        interface_name(&network);

        if(network.transmited_bytes>139803656033161 || network.received_bytes>139803656033161){

            printf("problems \n");
            printf("NEt trans:  %" SCNu64 " rec:  %" SCNu64 "\n",network.transmited_bytes,network.received_bytes);
            exit(1);
        }
        ret =  send(info->thread_socket, &network, sizeof(Network), 0);
        printf("Network  %" SCNu64 ", %" SCNu64 "\n ",network.received_bytes,network.transmited_bytes);
        if (ret < 0) {
            printf("Error sending data!\n\t");
              break;

        }
        if (ret == 0) {
            printf("Error sending data!\n\t");
            printf("socket closed\n");
            break;

        }
        ret=test_send(info->thread_socket);
        if (ret < 0) {

            printf("error receing data\n %d",(int) ret);
            break;
        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }

        printf("Return value network %d \n", (int)ret);








        free(task_array);
        free(devices);
        free(interrupts);

        free(info);
            printf("pre\n");
        task_array=NULL;
        devices=NULL;
        interrupts=NULL;
        info=NULL;
      //      pthread_cond_wait(&cond, &m);
            printf("posle\n");


        }

        printf("freing stuff\n");

    if(task_array!=NULL){
        printf("free tasks\n");
        free(task_array);
    }
    if(devices!=NULL){
        printf("free devices\n");
        free(devices);
    }

    if(interrupts!=NULL){
        printf("interrupts\n");
        free(interrupts);
    }
    if(info!=NULL){
        printf("info\n");
        free(info);

    }



   // pthread_exit(&ret);

  return 0;
};
