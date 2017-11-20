//
// Created by root on 13.6.17..
//

#include"stdio.h"
#include"stdlib.h"

#include"sys/socket.h"

#include"pthread.h"

#include "functions.h"

#define BUF_SIZE 2000
#define CLADDR_LEN 100






//void* primanje(void * socket,GArray *array_int,Cpu_usage1 *cpu_usage1){
void  primanje(void * socket,GArray *array_int,Cpu_usage *cpu_usage1,GArray *array_tasks,GArray *array_devices,Network *network,struct tm *tm,Memory_usage *memory_usage){

    int  ret;
    __int32_t num;

    struct	my_thread_info *info = socket;
    data_s data;

    ret = (int )recvfrom(info->thread_socket,&data, sizeof(data_s), 0,NULL,NULL);
    // ret = (int )recv(info->thread_socket,buffer, BUF_SIZE, 0);
    if (ret < 0) {
        printf("Error receving data!\n\t-%f %lli %lli %lli \n", data.Memory.swap_percentage,data.Memory.swap_used
                ,data.Memory.memory_total,data.Memory.memory_used);
        // printf("slanje broja paketa nije uspelo %s\n ",buffer);
        gtk_main_quit();
      //  exit(1);
    }
    else{
        memory_usage->percentage=data.Memory.percentage;
        memory_usage->memory_total=data.Memory.memory_total;
        memory_usage->swap_used=data.Memory.swap_used;
        memory_usage->swap_percentage=data.Memory.swap_percentage;
        memory_usage->swap_total=data.Memory.swap_total;
        memory_usage->memory_used=data.Memory.memory_used;
            printf("uspelo slanje%f %lli %lli %lli \n", data.Memory.swap_percentage,data.Memory.swap_used
                    ,data.Memory.memory_total,data.Memory.memory_used);

    }





    ret=(int )recvfrom(info->thread_socket,&num, sizeof(__int32_t), 0,NULL,NULL);
    if(ret<0){

        printf("Error receving data! %d",num);
        gtk_main_quit();
      //  exit(1);
    }
    printf("NUm of intrypps %d \n",num);
    for(int i=0 ;i<num;i++){
        ret = (int )recvfrom(info->thread_socket,&data, sizeof(Interrupts), 0,NULL,NULL);
        // ret = (int )recv(info->thread_socket,buffer, BUF_SIZE, 0);
        printf("SIZE OF %d \n",(int)sizeof(data));
        if (ret < 0) {
            printf("Error receving data!\n\t %lu  %s %s %s   \n", data.interrupts.CPU0,data.interrupts.name,
                   data.interrupts.ime1,data.interrupts.ime2);
            // printf("slanje broja paketa nije uspelo %s\n ",buffer);
            gtk_main_quit();
           // exit(1);
        }
        else
            printf(" Receving data!\n\t %lu %lu %lu %lu %s %s %s %s %s\n", data.interrupts.CPU0,
                   data.interrupts.CPU1,
                   data.interrupts.CPU2,
                   data.interrupts.CPU3,data.interrupts.name,
                   data.interrupts.ime1,data.interrupts.ime2,data.interrupts.ime3,data.interrupts.ime4);





            g_array_append_val(array_int,data.interrupts);



    }
       printf("Garray lenght %d\n",array_int->len);

    //   }
    ret=(int )recvfrom(info->thread_socket,&data, sizeof(data_s), 0,NULL,NULL);
    if (ret < 0) {
        printf("Error receving data!\n");
        gtk_main_quit();
      //  exit(1);
    }
    else{

        printf("cpu usage %f %f %f %f\n",data.cpu_usage.percentage0,
               data.cpu_usage.percentage1,
               data.cpu_usage.percentage2,
               data.cpu_usage.percentage3);
    }
    cpu_usage1->percentage0    =data.cpu_usage.percentage0;
    cpu_usage1->percentage1   = data.cpu_usage.percentage1;
    cpu_usage1->percentage2 = data.cpu_usage.percentage2;
    cpu_usage1->percentage3= data.cpu_usage.percentage3;

    // GArray  * array_tasks=g_array_new (FALSE, FALSE, sizeof (Task));

//
    ret= (int)recvfrom(info->thread_socket,&num,sizeof(__uint32_t),0,NULL,NULL);
    if (ret < 0) {
        printf("Error sending num_packets!\n\t");

        gtk_main_quit();
       // exit(1);
    }
       printf("num %d\n",num);
    for(int i=0 ;i<num;i++) {


        ret = (int) recvfrom(info->thread_socket, &data, sizeof(data), 0,NULL,NULL);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
            //  break;
            gtk_main_quit();
           // exit(1);
        }

        printf( "vreme trajanja rada %d %d %d\n",data.task.duration.tm_hour,
                data.task.duration.tm_min,
                data.task.duration.tm_sec);
        printf( "start time %d %d %d\n",data.task.stime.tm_hour,
                data.task.stime.tm_min,
                data.task.stime.tm_sec);
        printf("Name [%s]  checked [%hu] pid [%d] start_time[%d] prio [%d] %llu %llu %d %d %f %f [%s] [%s]\n",data.task.name
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
        //  printf("prio ffs %lu \n",data.task.start_time);
        g_array_append_val(array_tasks,data.task);

    }
   ret= (int)recvfrom(info->thread_socket,&num,sizeof(__int32_t),0,NULL,NULL);
    if (ret < 0) {
        printf("Error sending num_packets!\n\t");
        gtk_main_quit();
      //  exit(1);
    }
       printf("num %d\n",num);
    for(int i=0 ;i<num;i++) {


        ret = (int) recvfrom(info->thread_socket, &data, sizeof(data), 0,NULL,NULL);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
            //  break;
            gtk_main_quit();
           // exit(1);
        }

        printf("Devices %lu, %lu,%lu,%lu %lu, %s %s %s\n",
               data.devices.used,data.devices.avail,
               data.devices.fid,data.devices.free,data.devices.total,
               data.devices.name,data.devices.directory,data.devices.type);
        g_array_append_val(array_devices,data.devices);

    }

    ret = (int) recvfrom(info->thread_socket, &data, sizeof(data), 0,NULL,NULL);
    if (ret < 0) {
        printf("Error sending num_packets!\n\t");
        //  break;
        gtk_main_quit();
       // exit(1);
    }
    network->received_bytes= data.network.received_bytes;
    network->transmited_bytes=data.network.transmited_bytes;
      printf("Network %lli %lli \n",network->transmited_bytes,network->received_bytes);


    struct tm1 tm1;
    ret = (int) recvfrom(info->thread_socket, &tm1, sizeof(tm1), 0,0,0);
    if (ret<0) {
        printf("ERROR: Return Code  is %d\n", ret);
        gtk_main_quit();
      //  exit(1);
    }
    tm->tm_year= tm1.tm_year ;
    tm->tm_mon = tm1.tm_mon ;
    tm->tm_mday= tm1.tm_mday;
    tm->tm_hour=tm1.tm_hour;
    tm->tm_min= tm1.tm_min;
    tm->tm_sec=tm1.tm_sec;

    printf("now: %d-%d-%d %d:%d:%d\n", tm->tm_year , tm->tm_mon , tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    // printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


};