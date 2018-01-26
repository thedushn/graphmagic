//
// Created by root on 13.6.17..
//


#include"stdio.h"
#include <inttypes.h>
#include <stdlib.h>
#include <memory.h>

#include"sys/socket.h"

#include "functions.h"

#define BUF_SIZE 1024
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
    if(ret<64) {
        size_t velicina = 64;
        velicina -= ret;
        while (velicina > 0 || velicina < 0) {
            printf("Buffer2 [%s]\n", buffer);

            ret = send(socket, buffer, velicina, 0);
            velicina -= ret;

            if (ret < 0) {

                printf("error receing data\n %d", (int) ret);
                return  ret;
            }
            if(ret==0){

                printf("error sending data\n %d", (int) ret);
                printf("socket closed\n");
                return  ret;
            }
        }
    }

    return  64;

};
void  primanje3(void * socket ,Cpu_usage  *cpu_usage1, Network *network,Memory_usage  *memory_usage
,GArray * array_devices
  //,GArray *array_int
  //,GArray *array_tasks
        ){



    int flag= MSG_WAITALL;
    Task task;
    Devices devices;
    Interrupts interrupts;
    char buffer[64];
    ssize_t  ret;
    __int32_t num=0;
    struct	my_thread_info *info = socket;
    data_s data;
        ///memorija
    ret = recv(info->thread_socket,memory_usage, sizeof(Memory_usage), flag);

    if (ret < 0) {
        printf("Error receving data!\n\t-%s %ld %ld %ld \n", data.memory_usage.swap_percentage,data.memory_usage.swap_used
                ,data.memory_usage.memory_total,data.memory_usage.memory_used);
        // printf("slanje broja paketa nije uspelo %s\n ",buffer);
        gtk_main_quit();
        //  exit(1);
    }
    else{
        printf("Return value memory %d \n",(int)ret);

        printf("Memorija uspelo slanje%s %ld %ld %ld  %ld\n", memory_usage->swap_percentage
                ,memory_usage->swap_used
                ,memory_usage->memory_total
                ,memory_usage->swap_used
                ,memory_usage->memory_used
                );


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


    ///kraj memorije






   /* ret=recv(info->thread_socket,&num, sizeof(__int32_t), flag);
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

    if(num<0){
        printf("broj ne valja %d \n",num);
        exit(1);
    }

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







                 // g_array_append_val(array_int,interrupts);



              }

*/

                ///cpu usage
                  ret =  recv(info->thread_socket, cpu_usage1, sizeof(Cpu_usage), flag);
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

                    ret = test_recv(info->thread_socket);
                    if (ret < 0) {

                        printf("error receiving data\n %d", (int) ret);
                        gtk_main_quit();
                    }
                    if(ret==0){

                        printf("error sending data\n %d", (int) ret);
                        printf("socket closed\n");
                        gtk_main_quit();
                    }

                      printf("cpu usage %s %s %s %s \n",
                             cpu_usage1->percentage0,
                             cpu_usage1->percentage1,
                             cpu_usage1->percentage2,
                             cpu_usage1->percentage3
                      );
                      printf("Return value cpu %d \n",(int)ret);

                    ///kraj cpu_usage

              /*  ret= (int)recv(info->thread_socket,&num,sizeof(__int32_t),flag);
                 if (ret < 0) {
                     printf("Error sending num_packets!\n\t");

                     gtk_main_quit();
                     // exit(1);
                 }

                ret = test_recv(info->thread_socket);
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


                     ret =  recv(info->thread_socket, &task, sizeof(Task), flag);
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

                     ret = test_recv(info->thread_socket);
                     if (ret < 0) {

                         printf("error receiving data\n %d", (int) ret);
                         gtk_main_quit();
                     }
                     if(ret==0){

                         printf("error sending data\n %d", (int) ret);
                         printf("socket closed\n");
                         gtk_main_quit();
                     }

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
                     );
                     printf("Return value tasks %d \n",(int)ret);
                  //   g_array_append_val(array_tasks,task);

                 }

             ret= recv(info->thread_socket,&num,sizeof(__int32_t),flag);
              if (ret < 0) {
                  printf("Error sending num_packets!\n\t");
                  gtk_main_quit();
                  //  exit(1);
              }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }
    ret = test_recv(info->thread_socket);
    if (ret < 0) {

        printf("error receiving data\n %d", (int) ret);
        gtk_main_quit();
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }*/

             /* printf("Dev num %d\n",num);
              printf("Return value dev_num %d \n",(int)ret);


              for(int i=0 ;i<num;i++) {


                  ret =  recv(info->thread_socket, &devices, sizeof(Devices), flag);

                  if (ret < 0) {
                      printf("Error sending num_packets!\n\t");

                      gtk_main_quit();

                  }
                  if (ret == 0) {
                      printf("Error sending num_packets!\n\t");
                     printf("socket closed\n");
                      gtk_main_quit();
                      // exit(1);
                  }
                  ret = test_recv(info->thread_socket);
                  if (ret < 0) {

                      printf("error receiving data\n %d", (int) ret);
                      gtk_main_quit();
                  }
                  if(ret==0){

                      printf("error sending data\n %d", (int) ret);
                      printf("socket closed\n");
                      gtk_main_quit();
                  }


        printf("Devices %" SCNu64 ", %"SCNu64",%"SCNu64" %" SCNu64" %"SCNu64", %s %s %s\n",
               devices.used, devices.avail,
               devices.fid, devices.free, devices.total,
               devices.name, devices.directory, devices.type);
        printf("Return value devices %d \n", (int)ret);

        g_array_append_val(array_devices, devices);

    }
    ret= (int)recv(info->thread_socket,&num,sizeof(__int32_t),flag);
    if (ret < 0) {
        printf("Error sending num_packets!\n\t");
        gtk_main_quit();
        //  exit(1);
    }*/
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
        if(ret==0){

            printf("error sending data\n %d", (int) ret);
            printf("socket closed\n");
            gtk_main_quit();
        }
        ret = test_recv(info->thread_socket);
        if (ret < 0) {

            printf("error receiving data\n %d", (int) ret);
            gtk_main_quit();
        }
        if(ret==0){

            printf("error sending data\n %d", (int) ret);
            printf("socket closed\n");
            gtk_main_quit();
        }

        printf("Devices %" SCNu64 ", %"SCNu64",%"SCNu64" %" SCNu64" %"SCNu64", %s %s %s\n",
               devices.used, devices.avail,
               devices.fid, devices.free, devices.total,
               devices.name, devices.directory, devices.type);
        printf("Return value devices %d \n", ret);

        g_array_append_val(array_devices, devices);

    }

    ret =  recv(info->thread_socket,network, sizeof(Network), flag);
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

    ret = test_recv(info->thread_socket);
    if (ret < 0) {

        printf("error receiving data\n %d", (int) ret);
        gtk_main_quit();
    }
    if(ret==0){

        printf("error sending data\n %d", (int) ret);
        printf("socket closed\n");
        gtk_main_quit();
    }


    printf("NEt trans: %ld rec: %ld \n",network->transmited_bytes,network->received_bytes);
    printf("Return value network %d \n",(int)ret);

    printf("Socket for receving %d \n",info->thread_socket);





};


