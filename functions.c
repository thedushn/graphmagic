//
// Created by root on 13.6.17..
//


#include"stdio.h"

#include <memory.h>

#include"sys/socket.h"

#include "functions.h"

ssize_t  test_recv(int socket){


    char buffer[64];
    ssize_t ret=0;
    memset(buffer,0,64);
    strcpy(buffer,"stiglo sve");
    ret=send(socket,buffer,64,0);

    if(ret<0){

        printf("error sending data\n %d", (int) ret);
        return  ret;
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        return  ret;
    }


    return  64;

};

void primanje3(int socket, Cpu_usage *cpu_usage1, Network *network, Memory_usage *memory_usage, GArray *array_devices,
               GArray *array_int, GArray *array_tasks
        ){



    int flag= MSG_WAITALL;
    Task task;
    Devices devices;
    Interrupts interrupts;
    ssize_t  ret;
    __int32_t num=0;
    data_s data;

    ///memorija
    ret = recv(socket, memory_usage, sizeof(Memory_usage), flag);
    if (ret < 0) {

        printf("error receiving data\n %d", (int) ret);
        gtk_main_quit();
    }
    if(ret==0){

        printf("error receiving data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }


    ret = test_recv(socket);
    if (ret < 0) {

        printf("error sending data\n %d", (int) ret);
        gtk_main_quit();
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }
    //kraj memorije

    ///cpu_usage
    ret = recv(socket, cpu_usage1, sizeof(Cpu_usage), flag);
    if (ret < 0) {
        printf("Error receiving data!\n");
        gtk_main_quit();
        //  exit(1);
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }

    ret = test_recv(socket);
    if (ret < 0) {

        printf("error receiving data\n %d", (int) ret);
        gtk_main_quit();
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }

   /* printf("cpu usage %s %s %s %s \n",
           cpu_usage1->percentage0,
           cpu_usage1->percentage1,
           cpu_usage1->percentage2,
           cpu_usage1->percentage3
    );*/
  //  printf("Return value cpu %d \n",(int)ret);

    ///kraj cpu_usage

    ///network
    ret = recv(socket, network, sizeof(Network), flag);
    if (ret < 0) {
        printf("Error receiving num_packets!\n\t");
        //  break;
        gtk_main_quit();
        // exit(1);
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }

    ret = test_recv(socket);
    if (ret < 0) {

        printf("error receiving data\n %d", (int) ret);
        gtk_main_quit();
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }


  /*  printf("NEt trans: %ld rec: %ld \n",network->transmited_bytes,network->received_bytes);
    printf("Return value network %d \n",(int)ret);

    printf("Socket for receving %d \n",info->thread_socket);*/
    /// kraj networka


    ///devices
    ret = (int) recv(socket, &num, sizeof(__int32_t), flag);
    if (ret < 0) {
        printf("Error sending num_packets!\n\t");
        gtk_main_quit();
        //  exit(1);
    }
    ret = test_recv(socket);
    if (ret < 0) {

        printf("error receiving data\n %d", (int) ret);
        gtk_main_quit();
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }

    for(int i=0 ;i<num;i++) {


        ret = (int) recv(socket, &devices, sizeof(Devices), flag);
        //    ret = (int) recvfrom(info->thread_socket, &devices, sizeof(Devices), 0,NULL,NULL);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
            //  break;
            gtk_main_quit();
            // exit(1);
        }
        if(ret==0){

            printf("error sending data\n %d", (int) ret);
            printf("socket closed\n");
            gtk_main_quit();
        }

/*
        printf("Devices %" SCNu64 ", %"SCNu64",%"SCNu64" %" SCNu64" %"SCNu64", %s %s %s\n",
                devices.used, devices.avail,
                devices.fid, devices.free, devices.total,
                devices.name, devices.directory, devices.type);
        printf("Return value devices %d \n", ret);*/

        g_array_append_val(array_devices, devices);

    }
    ///end of devices

    /// tasks
    ret = (int) recv(socket, &num, sizeof(__int32_t), flag);
    if (ret < 0) {
        printf("Error sending num_packets!\n\t");

        gtk_main_quit();
        // exit(1);
    }

    ret = test_recv(socket);
    if (ret < 0) {

        printf("error receiving data\n %d", (int) ret);
        gtk_main_quit();
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }
    printf("num %d\n",num);
    for(int i=0 ;i<num;i++) {


        ret = recv(socket, &task, sizeof(Task), flag);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
            //  break;
            gtk_main_quit();
            // exit(1);
        }
        if(ret==0){

            printf("error sending data\n %d", (int) ret);
            printf("socket closed\n");
            gtk_main_quit();
        }


/*
        printf( "vreme trajanja rada %d %d %d\n",
                task.duration.tm_hour,
                task.duration.tm_min,
                task.duration.tm_sec
        );
        printf( "start time %d %d %d\n",task.stime.tm_hour,
                task.stime.tm_min,
                task.stime.tm_sec
        );
        printf("Name [%s]  checked [%hu] pid [%d] start_time[%"SCNu64" ]  prio [%d] %ld %ld %d %d %s %s [%s] [%s]\n",
               task.name
                ,task.checked
                ,task.pid
                ,task.start_time
                ,task.prio
                ,task.rss
                ,task.vsz,
               task.uid,
               task.ppid,
               task.cpu_user,
               task.cpu_system,
               task.state,
               task.uid_name
        );*/
      //  printf("Return value tasks %d \n",(int)ret);
           g_array_append_val(array_tasks,task);

    }


    /// interrupts
    ret = recv(socket, &num, sizeof(__int32_t), flag);
    if(ret<0){

        printf("Error receving data! %d",num);
        gtk_main_quit();
        //  exit(1);
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }
    ret = test_recv(socket);
    if (ret < 0) {

        printf("error receing data\n %d", (int) ret);
        gtk_main_quit();
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");

    }

    if(num<0){
        printf("broj ne valja %d \n",num);
        gtk_main_quit();
    }

    for(int i=0 ;i<num;i++){
        ret = recv(socket, &interrupts, sizeof(Interrupts), flag);

        if (ret < 0) {
            printf("Error receving data!\n\t %ld  %s %s %s   \n", interrupts.CPU0,data.interrupts.name,
                   data.interrupts.ime1,data.interrupts.ime2);

            gtk_main_quit();

        }
        if(ret==0){

            printf("error sending data\n %d", (int) ret);
            printf("socket closed\n");
            gtk_main_quit();
        }



/*

        printf(" Receving data!return value interrupts %d \n\t Interrupts %ld %ld %ld %ld %s %s %s \n",
               (int) ret,
               interrupts.CPU0,
               interrupts.CPU1,
               interrupts.CPU2,
               interrupts.CPU3,
               interrupts.name,
               interrupts.ime1,
               interrupts.ime2
        );
*/


    //    printf("return value of Interrupts ret: %d number of recv %d  \n",(int)ret,i );







           g_array_append_val(array_int,interrupts);



    }
    ret = test_recv(socket);
    if (ret < 0) {

        printf("error receing data\n %d", (int) ret);
        gtk_main_quit();
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }
/*
    for(int i=0 ;i<num;i++){
        ret = recv(info->thread_socket,&interrupts, sizeof(Interrupts), flag);

        if (ret < 0) {
            printf("Error receving data!\n\t %ld  %s %s %s   \n", interrupts.CPU0,data.interrupts.name,
                   data.interrupts.ime1,data.interrupts.ime2);

            gtk_main_quit();

        }
        if(ret==0){

            printf("error sending data\n %d", (int) ret);
            printf("socket closed\n");
            gtk_main_quit();
        }
        ret = test_recv(info->thread_socket);
        if (ret < 0) {

            printf("error receing data\n %d", (int) ret);
            gtk_main_quit();
        }
        if(ret==0){

            printf("error sending data\n %d", (int) ret);
            printf("socket closed\n");
            gtk_main_quit();
        }



        printf(" Receving data!return value interrupts %d \n\t Interrupts %ld %ld %ld %ld %s %s %s \n",
               (int) ret,
               interrupts.CPU0,
               interrupts.CPU1,
               interrupts.CPU2,
               interrupts.CPU3,
               interrupts.name,
               interrupts.ime1,
               interrupts.ime2
        );


        printf("return value of Interrupts ret: %d number of recv %d  \n",(int)ret,i );







      //   g_array_append_val(array_int,interrupts);



    }*/

    ///intterupts end






};


