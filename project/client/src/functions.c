//
// Created by root on 13.6.17..
//

#include <inttypes.h>

#include"stdio.h"
#include"stdlib.h"

#include"sys/socket.h"

#include "functions.h"


void  primanje3(void * socket ,Cpu_usage  *cpu_usage1, Network *network,Memory_usage  *memory_usage,GArray * array_devices ,GArray *array_int,GArray *array_tasks
        ){


   //  Cpu_usage *cpu_usage1;
    // Network *network;
    int flag= MSG_WAITALL;
   //   cpu_usage1 = malloc(sizeof(Cpu_usage));
    // network = malloc(sizeof(Network));
    Task task;
    Devices devices;
   // Memory_usage  *memory_usage = malloc(sizeof(Memory_usage));
     // Devices *devices = malloc(sizeof(Devices));
    Interrupts interrupts;
    // tm1 = malloc(sizeof(struct tm));
    int  ret;
    __int32_t num=0;
 //  char buffer[1024];
  //  bool uspeo;
    struct	my_thread_info *info = socket;
    data_s data;

    ret = (int )recv(info->thread_socket,memory_usage, sizeof(Memory_usage), flag);
    // ret = (int )recv(info->thread_socket,buffer, BUF_SIZE, 0);
    if (ret < 0) {
        printf("Error receving data!\n\t-%s %ld %ld %ld \n", data.memory_usage.swap_percentage,data.memory_usage.swap_used
                ,data.memory_usage.memory_total,data.memory_usage.memory_used);
        // printf("slanje broja paketa nije uspelo %s\n ",buffer);
        gtk_main_quit();
        //  exit(1);
    }
    else{
        printf("Return value memory %d \n",ret);
       /* memset(buffer,0,sizeof(buffer));
          strcpy(buffer,"hello server i got your stuff");

       // uspeo=true;
        ret = (int )send(info->thread_socket,&buffer,sizeof(buffer), 0);
       if (ret < 0) {
            printf("Error sending data!\n\t-%s Ret %d \n", buffer,ret);
            // printf("slanje broja paketa nije uspelo %s\n ",buffer);
            gtk_main_quit();
            //  exit(1);
        }
        printf(" sending data!\n\t-%d Ret %d \n", uspeo,ret);*/
      /*  for(int i=0 ; i<sizeof(memory_usage->memory_percentage);i++){
            memory_usage->memory_percentage[i]=data.memory_usage.memory_percentage[i];
            memory_usage->swap_percentage[i]=data.memory_usage.swap_percentage[i];

        }

         memory_usage->memory_total=data.memory_usage.memory_total;
         memory_usage->swap_used=data.memory_usage.swap_used;

         memory_usage->swap_total=data.memory_usage.swap_total;
         memory_usage->memory_used=data.memory_usage.memory_used;*/
//        printf("Memorija uspelo slanje%f %ld %ld %ld \n", data.Memory.swap_percentage,data.Memory.swap_used
//                ,data.Memory.memory_total,data.Memory.memory_used);
        printf("Memorija uspelo slanje%s %ld %ld %ld  %ld\n", memory_usage->swap_percentage,memory_usage->swap_used,memory_usage->memory_total
                ,memory_usage->swap_used,memory_usage->memory_used);


    }
    // free(memory_usage);




    ret=(int )recv(info->thread_socket,&num, sizeof(__int32_t), flag);
    if(ret<0){

        printf("Error receving data! %d",num);
        gtk_main_quit();
        //  exit(1);
    }
   // printf("Broj Interrupta %d",num);
    if(num<0){
        printf("broj ne valja %d \n",num);
        exit(1);
    }

    for(int i=0 ;i<num;i++){
        ret = (int )recv(info->thread_socket,&interrupts, sizeof(Interrupts), flag);
        // ret = (int )recv(info->thread_socket,buffer, BUF_SIZE, 0);
        if (ret < 0) {
            printf("Error receving data!\n\t %ld  %s %s %s   \n", interrupts.CPU0,data.interrupts.name,
                   data.interrupts.ime1,data.interrupts.ime2);
            // printf("slanje broja paketa nije uspelo %s\n ",buffer);
            gtk_main_quit();
            // exit(1);
        }
        else{
                printf(" Receving data!return value interrupts %d \n\t Interrupts %ld %ld %ld %ld %s %s %s \n",ret, interrupts.CPU0,
                   interrupts.CPU1,
                   interrupts.CPU2,
                   interrupts.CPU3,interrupts.name,
                   interrupts.ime1,interrupts.ime2);


            printf("return value of Interrupts ret: %d number of recv %d  \n",ret,i );
            // interrupts={0};
        }






        g_array_append_val(array_int,interrupts);



    }

    //   printf("Garray lenght %d\n",array_int->len);

    //   }




        ret = (int) recv(info->thread_socket, cpu_usage1, sizeof(Cpu_usage), flag);
        if (ret < 0) {
            printf("Error receving data!\n");
            gtk_main_quit();
            //  exit(1);
        } else {
            printf("cpu usage %s %s %s %s \n", cpu_usage1->percentage0,cpu_usage1->percentage1,cpu_usage1->percentage2,cpu_usage1->percentage3);
            printf("Return value cpu %d \n",ret);

        }

      ret= (int)recv(info->thread_socket,&num,sizeof(__int32_t),0);
       if (ret < 0) {
           printf("Error sending num_packets!\n\t");

           gtk_main_quit();
           // exit(1);
       }
       printf("num %d\n",num);
       for(int i=0 ;i<num;i++) {


           ret = (int) recv(info->thread_socket, &task, sizeof(Task), flag);
           if (ret < 0) {
               printf("Error sending num_packets!\n\t");
               //  break;
               gtk_main_quit();
               // exit(1);
           }

           printf( "vreme trajanja rada %d %d %d\n",task.duration.tm_hour,
                   task.duration.tm_min,
                   task.duration.tm_sec);
           printf( "start time %d %d %d\n",task.stime.tm_hour,
                   task.stime.tm_min,
                   task.stime.tm_sec);
           printf("Name [%s]  checked [%hu] pid [%d] start_time[%"SCNu64" ]  prio [%d] %ld %ld %d %d %s %s [%s] [%s]\n",task.name
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
           );
           printf("Return value tasks %d \n",ret);
           g_array_append_val(array_tasks,task);

       }

   ret= (int)recv(info->thread_socket,&num,sizeof(__int32_t),flag);
    if (ret < 0) {
        printf("Error sending num_packets!\n\t");
        gtk_main_quit();
        //  exit(1);
    }
    printf("Dev num %d\n",num);
    printf("Return value dev_num %d \n",ret);

   // for(int i=0 ;i<4;i++) {
    for(int i=0 ;i<num;i++) {


        ret = (int) recv(info->thread_socket, &devices, sizeof(Devices), flag);
        //    ret = (int) recvfrom(info->thread_socket, &devices, sizeof(Devices), 0,NULL,NULL);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
            //  break;
            gtk_main_quit();
            // exit(1);
        }

        printf("Devices %" SCNu64 ", %"SCNu64",%"SCNu64" %" SCNu64" %"SCNu64", %s %s %s\n",
               devices.used, devices.avail,
               devices.fid, devices.free, devices.total,
               devices.name, devices.directory, devices.type);
        printf("Return value devices %d \n", ret);
        if(ret<sizeof(Devices)){

            printf("Return value trolled us %d \n", ret);
        }
        g_array_append_val(array_devices, devices);

    }

    ret = (int) recv(info->thread_socket,network, sizeof(Network), flag);
    if (ret < 0) {
        printf("Error sending num_packets!\n\t");
        //  break;
        gtk_main_quit();
        // exit(1);
    }

    printf("NEt trans: %ld rec: %ld \n",network->transmited_bytes,network->received_bytes);
    if(network->transmited_bytes>139803656033161 || network->received_bytes>139803656033161){

        printf("problems \n");
        printf("NEt trans:  %" SCNu64 " rec:  %" SCNu64 "\n",network->transmited_bytes,network->received_bytes);
        gtk_main_quit();
    }
    printf("Return value network %d \n",ret);






};


