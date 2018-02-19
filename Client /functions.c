
#include"stdio.h"
#include"stdlib.h"

#include"sys/socket.h"

#include"pthread.h"


#include "functions.h"
#include "interrupts.h"
#include "cpu_usage.h"



#define BUF_SIZE 1024


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


    CPUa = (int) (CPU0a + CPU1a + CPU2a + CPU3a);
    CPUb = (int) (CPU0b + CPU1b + CPU2b + CPU3b);



    return CPUa - CPUb;

}

void sort2(Interrupts *array, Interrupts *array2, Interrupts **array3, int n) {

    Interrupts *interrupts_send = NULL;
    interrupts_send = calloc((size_t) n, sizeof(Interrupts));
    for (int i = 0; i < n; i++) {

        Interrupts interrupts3;
        memset(&interrupts3, 0, sizeof(Interrupts));
        strcpy(interrupts3.name, array[i].name);

        __int64_t temp = array[i].CPU0 - array2[i].CPU0;
        if(temp<0){
            temp=0;
        }
        interrupts3.CPU0 = (__uint64_t)temp;

        temp = array[i].CPU1 - array2[i].CPU1;
        if(temp<0){
            temp=0;
        }
        interrupts3.CPU1 = (__uint64_t)temp;


        temp = array[i].CPU2 - array2[i].CPU2;
        if(temp<0){
            temp=0;
        }
        interrupts3.CPU2 = (__uint64_t)temp;

        temp = array[i].CPU3 - array2[i].CPU3;
        if(temp<0){
            temp=0;
        }
        interrupts3.CPU3 =(__uint64_t)temp;





        strcpy(interrupts3.ime1, array[i].ime1);
        strcpy(interrupts3.ime2, array[i].ime2);
        strcpy(interrupts3.ime3, array[i].ime3);
        strcpy(interrupts3.ime4, array[i].ime4);
        interrupts_send[i] = interrupts3;

    }

    *array3 = interrupts_send;


}

void sort(Interrupts *array, int n) {

    qsort(array,(size_t) n, sizeof(Interrupts), myCompare);
}

bool devices_show=false;
ssize_t test_send(int socket){

    ssize_t  ret=0;
    char buffer[64];
    memset(buffer,0,sizeof(buffer));
    ret= recv(socket, buffer,sizeof(buffer),0);

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


            ret = (int) recv(socket, buffer, velicina, 0);
            velicina -= ret;

            if (ret < 0) {

                printf("error receing data\n %d", (int)ret);
                return ret;
            }
            if (ret == 0) {

                printf("socket closed\n");
               return ret;
            }

        }
    }
    if (strcmp(buffer, "stiglo sve") != 0) {

        printf("conforamtion didnt get received  \n");

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
    if(system(command) != 0){

        printf("comand failed\n");
    }



}
void send_signal_to_task(char *task_id, char *signal)
{

    if(task_id != NULL && signal != NULL)
    {
        char command[64] = "kill -";
        strncat(command,signal, sizeof command);
        strncat(command," ", sizeof command);
        strncat(command,task_id, sizeof command);

        if(system(command) != 0)
            printf("comand failed\n");
    }
}
void *accept_c(void *socket){

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

        devices_show=commands.show;



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



    time_t time1;

    Task *task_array=NULL;
    Interrupts  *interrupts=NULL;
    Interrupts *interrupts_main = NULL;
    Interrupts *interrupts_send = NULL;

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




        ///devices
        __int32_t niz=0;

      result=  device2(&devices,devices_show,&niz);
        if (result != 0) {

            break;
        }



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




        __int32_t j=h;
        sort2(interrupts, interrupts_main, &interrupts_send, h);


        sort(interrupts_send, j);




            for (int r = h-10; r < h; r++) {


            ret = send(sockfd, &interrupts_send[r], sizeof(Interrupts), 0);


            if (ret < 0) {
                printf("Error sending data!\n\t");
                break;

            }
            if (ret == 0) {

                printf("socket closed\n");
                break;
            }



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


        free(interrupts_send);


        for (int r = 0; r < h; r++) {

            interrupts_main[r] = interrupts[r];
        }
        interrupts_send = NULL;



        free(task_array);
        free(devices);
        free(interrupts);


        task_array=NULL;
        devices=NULL;
        interrupts=NULL;


    }


    if(task_array!=NULL){

        free(task_array);
    }
    if(devices!=NULL){

        free(devices);
    }

    if(interrupts!=NULL){

        free(interrupts);
    }
    if (interrupts_main != NULL) {

        free(interrupts_main);
    }
    if (interrupts_send != NULL) {

        free(interrupts_send);
    }



  return 0;
};
