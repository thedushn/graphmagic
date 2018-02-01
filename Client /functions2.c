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

static int myCompare(const void *a, const void *b) {

    Interrupts interrupts1 = *(Interrupts *) a;
    Interrupts interrupts2 = *(Interrupts *) b;

    __uint64_t CPU0a = 0;
    __uint64_t CPU1a = 0;
    __uint64_t CPU2a = 0;
    __uint64_t CPU3a = 0;
    __uint64_t CPU0b = 0;
    __uint64_t CPU1b = 0;
    __uint64_t CPU2b = 0;
    __uint64_t CPU3b = 0;
    int CPUa = 0;
    int CPUb = 0;

    CPU0a = interrupts1.CPU0;
    CPU1a = interrupts1.CPU1;
    CPU2a = interrupts1.CPU2;
    CPU3a = interrupts1.CPU3;

    CPU0b = interrupts2.CPU0;
    CPU1b = interrupts2.CPU1;
    CPU2b = interrupts2.CPU2;
    CPU3b = interrupts2.CPU3;
    /* CPU0a=interrupts1->CPU0;
     CPU1a=interrupts1->CPU1;
     CPU2a=interrupts1->CPU2;
     CPU3a=interrupts1->CPU3;

     CPU0b=interrupts2->CPU0;
     CPU1b=interrupts2->CPU1;
     CPU2b=interrupts2->CPU2;
     CPU3b=interrupts2->CPU3;*/
    CPUa = (int) (CPU0a + CPU1a + CPU2a + CPU3a);
    CPUb = (int) (CPU0b + CPU1b + CPU2b + CPU3b);

    //  printf(" PRVi %lu %lu %lu %lu   ime: %s\n", interrupts1->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);
    //  printf(" DRUGI %lu %lu %lu %lu   ime: %s\n", interrupts2->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);

    return CPUa - CPUb;

}

void sort2(Interrupts *array, Interrupts *array2, Interrupts **array3, int n) {

    Interrupts *interrupts_send = NULL;
    interrupts_send = calloc((size_t) n, sizeof(Interrupts));
    for (int i = 0; i < n; i++) {

        Interrupts interrupts3;
        memset(&interrupts3, 0, sizeof(Interrupts));
        strcpy(interrupts3.name, array[i].name);
        //interrupts3.name[j] = interrupts1->name[j];
        //  }

        __uint64_t temp = array[i].CPU0 - array2[i].CPU0;
        interrupts3.CPU0 = temp;
        temp = array[i].CPU1 - array2[i].CPU1;
        interrupts3.CPU1 = temp;
        temp = array[i].CPU2 - array2[i].CPU2;
        interrupts3.CPU2 = temp;
        temp = array[i].CPU3 - array2[i].CPU3;
        interrupts3.CPU3 = temp;




        // upis_imena(interrupts1,&interrupts3);
        strcpy(interrupts3.ime1, array[i].ime1);
        strcpy(interrupts3.ime2, array[i].ime2);
        strcpy(interrupts3.ime3, array[i].ime3);
        strcpy(interrupts3.ime4, array[i].ime4);
        interrupts_send[i] = interrupts3;

    }

    *array3 = interrupts_send;


}

void sort(Interrupts *array, int n) {

    qsort(array, n, sizeof(Interrupts), myCompare);
}
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
    int sockfd = *(int *) socket;

    Commands commands;

    while (1) {

        ssize_t ret = recv(sockfd, &commands, sizeof(Commands), 0);
        if(ret<0){
            printf("error condition didnt get received\n");


            pthread_exit(&ret);
        }
        if(ret==0){
            printf("error condition didnt get received\n");
            printf("ret %d\n", (int) ret);

            pthread_exit(&ret);
        }
        printf("ret accept  %d \n", (int) ret);
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

                send_prio_to_task(commands.task_id, commands.command);
            }

        }


    }

};



void *slanje(void *socket){

    ssize_t  ret=0;

    printf("usli smo u slanje\n");
        //unsigned int num_packets;

    time_t time1;

    Task *task_array=NULL;
    Interrupts  *interrupts=NULL;
    Interrupts *interrupts_main = NULL;
    Interrupts *interrupts_send = NULL;
    Interrupts *interrupts1 = NULL;
    Devices  *devices=NULL;
    int sockfd = *(int *) socket;
    int result = 0;

    while(1) {

        Memory_usage memory_usage={0};
        Cpu_usage cpu_usage={0} ;
        Network network={0};
        memset(&network, 0, sizeof(Network));


        time1 = time(NULL);

        lokalno = *localtime(&time1);
        ///memory
        get_memory_usage(&memory_usage);


        ret = send(sockfd, &memory_usage, sizeof(Memory_usage), 0);

        if (ret < 0) {
            printf("Error sending data!\n\t");
              break;

        }   if (ret == 0) {

            printf("socket closed\n");
            break;
        }

        ret = test_send(sockfd);
        if (ret < 0) {
            printf("Error receiving  num_packets!\n\t");
            break;

        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }


        /*    printf(" sending data!\n\t Memory Swap[%s] %" SCNu64 " %" SCNu64 "  %" SCNu64 " Memory[%s]\n"
                    ,memory_usage.swap_percentage
                    , memory_usage.swap_used
                    ,memory_usage.memory_total
                    , memory_usage.memory_used
                    , memory_usage.memory_percentage
            );*/

        ///memory_end
        ///cpu
        __int32_t cpu_num= cpu_number();
        cpu_percentage(cpu_num,&cpu_usage);

        ret = send(sockfd, &cpu_usage, sizeof(Cpu_usage), 0);
        if (ret < 0) {
            printf("Error sending data!\n\t");
            break;

        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }
        ret = test_send(sockfd);
        if (ret < 0) {

            printf("error receing data\n %d",(int) ret);
            break;
        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }

        ///cpu end

        ///network
        result = interface_name(&network);
        if (result != 0) {

            break;
        }
        ret = send(sockfd, &network, sizeof(Network), 0);

        if (ret < 0) {
            printf("Error sending data!\n\t");
            break;

        }
        if (ret == 0) {
            printf("Error sending data!\n\t");
            printf("socket closed\n");
            break;

        }
        ret = test_send(sockfd);
        if (ret < 0) {

            printf("error receing data\n %d",(int) ret);
            break;
        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }
     //   printf("Network  %" SCNu64 ", %" SCNu64 "\n ",network.received_bytes,network.transmited_bytes);

        printf("Return value network %d \n", (int)ret);
            ///network end


        ///devices
        __int32_t niz=0;
        //  devices=calloc(0,sizeof(Devices));
        device2(&devices,devices_show,&niz);
        printf("prosli \n");


        ret = send(sockfd, &niz, sizeof(__int32_t), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");

            break;
        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }
        ret = test_send(sockfd);
        if (ret < 0) {

            printf("error receing data\n %d",(int) ret);
            break;
        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }

        for(int i =0;i<niz ;i++){
            devices[i].checked=false;
            ret = (int) send(sockfd, &devices[i], sizeof(Devices), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                break;

            }
            if (ret == 0) {

                printf("socket closed\n");
                break;
            }


        }

        /// tasks
        int niz_task=0;
        //  task_array=calloc(0,sizeof(Task));
        result = get_task_list(&task_array, &niz_task);
        if (result != 0) {

            printf("error in get_task_list\n");
            break;
        }
        __int32_t niz_temp= (__int32_t) niz_task;
        ret = send(sockfd, &niz_temp, sizeof(__int32_t), 0);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");

            break;

        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }
        ret = test_send(sockfd);
        if (ret < 0) {

            printf("error receing data\n %d",(int) ret);
            break;
        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }

        for (int i = 0; i < niz_task; i++) {


            ret = send(sockfd, &task_array[i], sizeof(Task), 0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                break;

            }
            if (ret == 0) {

                printf("socket closed\n");
                break;
            }


        }

      /*  for (int i = 0; i < niz_task; i++) {


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

            data.task.vsz = task_array[i].vsz;
            data.task.rss = task_array[i].rss;
            data.task.prio = task_array[i].prio;

            data.task.pid = task_array[i].pid;
            data.task.ppid = task_array[i].ppid;

             data.task.start_time = task_array[i].start_time;
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
        ///tasks end


        ///interrupts
        __int32_t h=0;

        result = interrupt_usage2(&interrupts, &h);
        if (result != 0) {

            break;
        }

        if (interrupts_main == NULL) {

            interrupts_main = calloc((size_t) h, sizeof(Interrupts));
            for (int r = 0; r < h; r++) {

                interrupts_main[r] = interrupts[r];
            }


        }

        // sort(interrupts,h);
        // sort(interrupts_main,h);
        /* for(int r=0;r<h;r++){

             printf("%s %d %d %d %d  \n",&interrupts[r].ime1,interrupts[r].CPU0,interrupts[r].CPU1,interrupts[r].CPU2,interrupts[r].CPU3);
         }*/


        __int32_t j=h;
        sort2(interrupts, interrupts_main, &interrupts_send, h);

        for (int r = 0; r < h; r++) {

            printf("%s %d %d %d %d  \n", &interrupts_send[r].ime1, interrupts_send[r].CPU0, interrupts_send[r].CPU1,
                   interrupts_send[r].CPU2, interrupts_send[r].CPU3);
        }
        sort(interrupts_send, j);
        printf("AFTER sort \n \n");
        for (int r = 0; r < h; r++) {

            printf("%s %d %d %d %d  \n", &interrupts_send[r].ime1, interrupts_send[r].CPU0, interrupts_send[r].CPU1,
                   interrupts_send[r].CPU2, interrupts_send[r].CPU3);
        }
        printf("BROJ INT %d \n",j);
        interrupts1 = calloc((size_t) 10, sizeof(Interrupts));
        int g = 0;
        for (int r = h - 10; r < h; r++) {

            // memset(&interrupts1[g],0,sizeof(Interrupts));
            interrupts1[g] = interrupts_send[r];
            g++;

        }

        for (int r = 0; r < 10; r++) {
            printf(" Interrupts  %ld %ld %ld %ld %s %s %s \n",

                   interrupts1[r].CPU0,
                   interrupts1[r].CPU1,
                   interrupts1[r].CPU2,
                   interrupts1[r].CPU3,
                   interrupts1[r].name,
                   interrupts1[r].ime1,
                   interrupts1[r].ime2
            );
        }
        /* ret = send(sockfd, &j, sizeof(__int32_t), 0);
         if (ret < 0) {
             printf("Error sending num_packets!\n\t");
             break;

         }
         if (ret == 0) {

             printf("socket closed\n");
             break;
         }*/
        /*     ret = test_send(sockfd);
             if (ret < 0) {

                 printf("error receing data\n %d",(int) ret);
                 break;
             }
             if (ret == 0) {

                 printf("socket closed\n");
                 break;
             }*/
        for (int r = 0; r < 10; r++) {


            ret = send(sockfd, &interrupts1[r], sizeof(Interrupts), 0);


            if (ret < 0) {
                printf("Error sending data!\n\t");
                break;

            }
            if (ret == 0) {

                printf("socket closed\n");
                break;
            }




            printf("return value of Interrupts ret: %d number of send %d  \n",(int)ret,r );

        }
        ret = test_send(sockfd);
        if (ret < 0) {

            printf("error receing data\n %d",(int) ret);
            break;
        }
        if (ret == 0) {

            printf("socket closed\n");
            break;
        }

        //  free(interrupts_main);
        free(interrupts_send);
        free(interrupts1);

        for (int r = 0; r < h; r++) {

            interrupts_main[r] = interrupts[r];
        }
        interrupts_send = NULL;
        interrupts1 = NULL;


        free(task_array);
        free(devices);
        free(interrupts);


        task_array=NULL;
        devices=NULL;
        interrupts=NULL;


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
    if (interrupts_main != NULL) {
        printf("interrupts_main\n");
        free(interrupts_main);
    }
    if (interrupts_send != NULL) {
        printf("interrupts_send\n");
        free(interrupts_send);
    }

    if (interrupts1 != NULL) {
        printf("interrupts1\n");
        free(interrupts1);
    }


   // pthread_exit(&ret);

  return 0;
};
