//
// Created by root on 13.6.17..
//

#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"netdb.h"
#include"pthread.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include "functions.h"
#include "memory_usage.h"
#include "common.h"
#include "interrupts.h"
#include <unistd.h>
#define BUF_SIZE 2000
#define CLADDR_LEN 100
#define PACKET_SIZE 1400
char * test="Type the name  of the file u want to receive\n";
char *message= "Iste su extensions mozemo da nastavimo sa slanjem";
int num_packets;
char *message2= "reci kako oces da se zove file koji ti primas\n";
char *end ="\nend of file";
struct _Memory_usage memory_usage;
int rezultat=1;


void* primanje_interrupta(void * socket){
    printf("\nusli smo tu gde treba: primanje_inter \n");
    int  ret;
    // Memory_usage memory_usage;
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE);
    int sockfd= (int)socket;
    char buffer2[BUF_SIZE];
    char buffer_file[BUF_SIZE];
    char num_packets[BUF_SIZE];
    memset(num_packets, 0, BUF_SIZE);
    memset(buffer_file, 0, BUF_SIZE);
    memset(buffer2, 0, BUF_SIZE);
    ssize_t dataReceived;
    int NUM;
    struct	my_thread_info *info = socket;
    data_s interrupts;
    Interrupts interrupts1;
    ret=(int )recvfrom(info->thread_socket,&NUM, sizeof(int), 0,NULL,NULL);
    if(ret<0){

        printf("Error receving data! %d",NUM);
    }
    printf("BROJ INT %d",NUM);
    for(int i=0 ;i<NUM;i++){
        ret = (int )recvfrom(info->thread_socket,&interrupts, sizeof(data_s), 0,NULL,NULL);
        // ret = (int )recv(info->thread_socket,buffer, BUF_SIZE, 0);
        if (ret < 0) {
            printf("Error receving data!\n\t %lu  %s %s %s   \n", interrupts.interrupts.CPU0,interrupts.interrupts.name,
                   interrupts.interrupts.ime1,interrupts.interrupts.ime2);
            // printf("slanje broja paketa nije uspelo %s\n ",buffer);
        }
        else
            printf(" Receving data!\n\t %lu %lu %lu %lu %s %s %s \n", interrupts.interrupts.CPU0,
                   interrupts.interrupts.CPU1,
                   interrupts.interrupts.CPU2,
                   interrupts.interrupts.CPU3,interrupts.interrupts.name,
                   interrupts.interrupts.ime1,interrupts.interrupts.ime2);


        //   }

        interrupts1.CPU0=interrupts.interrupts.CPU0;
    }




}
//void* primanje(void * socket,GArray *array_int,Cpu_usage1 *cpu_usage1){
void* primanje(void * socket,GArray *array_int,Cpu_usage1 *cpu_usage1,GArray *array_tasks,GArray *array_devices,Network *network){
    printf("\nusli smo tu gde treba: primanje \n");
    int  ret;
   // Memory_usage memory_usage;
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE);
    int sockfd= (int)socket;
    char buffer2[BUF_SIZE];
    char buffer_file[BUF_SIZE];
    char num_packets[BUF_SIZE];
    memset(num_packets, 0, BUF_SIZE);
    memset(buffer_file, 0, BUF_SIZE);
    memset(buffer2, 0, BUF_SIZE);
    ssize_t dataReceived;

    struct	my_thread_info *info = socket;


    data_s data;
    ret = (int )recvfrom(info->thread_socket,&data, sizeof(data_s), 0,NULL,NULL);
    // ret = (int )recv(info->thread_socket,buffer, BUF_SIZE, 0);
    if (ret < 0) {
        printf("Error receving data!\n\t-%f %lli %lli %lli \n", data.Memory.swap_percentage,data.Memory.swap_used
                ,data.Memory.memory_total,data.Memory.memory_used);
        // printf("slanje broja paketa nije uspelo %s\n ",buffer);
    }
    else{
        memory_usage.percentage=data.Memory.percentage;
        memory_usage.memory_total=data.Memory.memory_total;
        memory_usage.swap_used=data.Memory.swap_used;
        memory_usage.swap_percentage=data.Memory.swap_percentage;
        memory_usage.swap_total=data.Memory.swap_total;
        memory_usage.memory_used=data.Memory.memory_used;
        printf("uspelo slanje%f %lli %lli %lli \n", data.Memory.swap_percentage,data.Memory.swap_used
                ,data.Memory.memory_total,data.Memory.memory_used);

    }

    int num;
    // struct	my_thread_info *info = socket;
  //  data_s interrupts;
    Interrupts interrupts1;
   // GArray * ginterrupts;
  //  ginterrupts=g_array_new (FALSE, FALSE, sizeof (Interrupts));
    ret=(int )recvfrom(info->thread_socket,&num, sizeof(int), 0,NULL,NULL);
    if(ret<0){

        printf("Error receving data! %d",num);
    }
  //  printf("BROJ INT %d",num);
    for(int i=0 ;i<num;i++){
        ret = (int )recvfrom(info->thread_socket,&data, sizeof(data_s), 0,NULL,NULL);
        // ret = (int )recv(info->thread_socket,buffer, BUF_SIZE, 0);
        if (ret < 0) {
            printf("Error receving data!\n\t %lu  %s %s %s   \n", data.interrupts.CPU0,data.interrupts.name,
                   data.interrupts.ime1,data.interrupts.ime2);
            // printf("slanje broja paketa nije uspelo %s\n ",buffer);
        }
        else
//            printf(" Receving data!\n\t %lu %lu %lu %lu %s %s %s \n", data.interrupts.CPU0,
//                   data.interrupts.CPU1,
//                   data.interrupts.CPU2,
//                   data.interrupts.CPU3,data.interrupts.name,
//                   data.interrupts.ime1,data.interrupts.ime2);


        //   }

//        interrupts1.CPU0=data.interrupts.CPU0;
//        interrupts1.CPU1=data.interrupts.CPU1;
//        interrupts1.CPU2=data.interrupts.CPU2;
//        interrupts1.CPU3=data.interrupts.CPU3;
//        for( i=0 ;i<sizeof(interrupts1.name);i++){
//            interrupts1.name[i]=data.interrupts.name[i];
//
//        }
//        upis_imena(&interrupts1,&data.interrupts);

        g_array_append_val(array_int,data.interrupts);



    }
 //   printf("Garray lenght %d\n",array_int->len);

    //   }
    ret=(int )recvfrom(info->thread_socket,&data, sizeof(data_s), 0,NULL,NULL);
    if (ret < 0) {
        printf("Error receving data!\n");
    }
    else{

//        printf("cpu usage %f %f %f %f\n",data.cpu_usage.percentage0,
//               data.cpu_usage.percentage1,
//               data.cpu_usage.percentage2,
//               data.cpu_usage.percentage3);
    }
        cpu_usage1->percentage0    =data.cpu_usage.percentage0;
        cpu_usage1->percentage1   = data.cpu_usage.percentage1;
          cpu_usage1->percentage2 = data.cpu_usage.percentage2;
           cpu_usage1->percentage3= data.cpu_usage.percentage3;

 // GArray  * array_tasks=g_array_new (FALSE, FALSE, sizeof (Task));

//
    ret= (int)recvfrom(info->thread_socket,&num,sizeof(int),NULL,NULL,NULL);
    if (ret < 0) {
        printf("Error sending num_packets!\n\t");

        exit(1);
    }
 //   printf("num %d\n",num);
    for(int i=0 ;i<num;i++) {


        ret = (int) recvfrom(info->thread_socket, &data, sizeof(data), NULL,NULL,NULL);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
            //  break;
            exit(1);
        }
        g_array_append_val(array_tasks,data.task);

    }
    ret= (int)recvfrom(info->thread_socket,&num,sizeof(int),NULL,NULL,NULL);
    if (ret < 0) {
        printf("Error sending num_packets!\n\t");

        exit(1);
    }
 //   printf("num %d\n",num);
    for(int i=0 ;i<num;i++) {


        ret = (int) recvfrom(info->thread_socket, &data, sizeof(data), NULL,NULL,NULL);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
            //  break;
            exit(1);
        }

        printf("%s %s %s \n",data.devices.directory,data.devices.name,data.devices.type);
        g_array_append_val(array_devices,data.devices);

    }

    ret = (int) recvfrom(info->thread_socket, &data, sizeof(data), NULL,NULL,NULL);
    if (ret < 0) {
        printf("Error sending num_packets!\n\t");
        //  break;
        exit(1);
    }
    network->received_bytes= data.network.received_bytes;
    network->transmited_bytes=data.network.transmited_bytes;
    printf("%lli %lli \n",network->transmited_bytes,network->received_bytes);



}
void *receiving(int socket) {
    printf("\nusli smo tu gde treba: receiving \n");
    int sockfd, ret;
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE);
    sockfd =  socket;
    char buffer2[BUF_SIZE];
    char buffer_file[BUF_SIZE];
    char num_packets[BUF_SIZE];
    memset(num_packets, 0, BUF_SIZE);
    memset(buffer_file, 0, BUF_SIZE);
    memset(buffer2, 0, BUF_SIZE);
    ssize_t dataReceived;
    FILE *filefd = NULL;
    //zakljucamo chat2
    if (pthread_mutex_lock(&mut) != 0) {
        printf("lock didnt work fuck my life\n");
        exit(1);
    }
    printf("kako oces da se zove file \n");


    ret = (int )recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
    if (ret < 0) {
        printf("Error sending data!\n\t-%s", buffer);
        //printf("slanje broja paketa nije uspelo\n");
    }
    //	printf("sta salje client %s\n", buffer2);
    printf("sta salje client %s\n", buffer);//ovde primi da su file iste extensions
    //sada u ovom receive treba da primi file kako treba da sse zove
    ret = (int )recvfrom(sockfd, buffer2, BUF_SIZE, 0, NULL, NULL);
    if (ret < 0) {
        printf("Error sending data!\n\t-%s", buffer2);
    }
    printf("sta salje client %s\n", buffer2);
    //primanje broja paketa
    ret = (int )recvfrom(sockfd, num_packets, BUF_SIZE, 0, NULL, NULL);
    if (ret < 0) {
        printf("Error sending data!\n\t-%s", num_packets);
    }
    printf("broj paketa : %s\n", num_packets);
    int packets = atoi(num_packets);
    printf("broj packeta %d \n", packets);
    filefd = fopen(buffer, "w+");

    if (filefd == NULL) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<packets;i++){


        dataReceived = read(sockfd,buffer_file,PACKET_SIZE);
        printf("data %s",buffer_file);


        if(dataReceived>0) {
            if(strcmp(buffer_file,end)==0) {
                printf("dosli smo do kraja file");
                fclose(filefd);
                break;
            }
            fwrite(buffer_file, 1, dataReceived, filefd);
        }
            if(dataReceived < 0) {
                printf("\n Read Error \n");
            }


            printf("%d\n",i);



    	}
    fclose(filefd);
    rezultat =1;
    printf("\nFile OK....Completed\n");
    printf("lets seee if this works\n");
    pthread_mutex_unlock(&mut);
    pthread_cond_signal(&cond);




}
void * confromation(int socket){
    int sockfd, ret;
    char buffer[BUF_SIZE];
    sockfd =  socket;
    printf("usli smo u conformation \n");
    printf("treba poslati ime file to se radi u chat2\n");

    ret = (int) recv(sockfd,buffer,BUF_SIZE,0);
    if(ret<0){
        printf("Error sending data!\n\t-%s", buffer);
    }
    printf("KLIJENT:%s\n",buffer);
    rezultat =strcmp(message2,buffer);
    if(rezultat==0){
        receiving(sockfd);
    }
    else{
        printf("KLIJENT kaze nisu iste extensions");

    }
    printf("izasli smo iz conformation\n");

}
void*  chat2(void *socket){
    int sockfd, ret;
    char buffer[BUF_SIZE];
   
    struct sockaddr_in addr;
	struct	my_thread_info *info = socket;
	 
    while(1){
        printf("we made it to chat2(sending messages)\n");
        if(rezultat==0){
            pthread_cond_wait(&cond,&mut);
            printf("condtion was met\n");
        }
        else{
            while (fgets(buffer,BUF_SIZE,stdin) != NULL) {
                //pthread_mutex_lock(&mut);
                //while(rezultat==0){pthread_cond_wait(&cond,&m);
                //}

                printf("YOU : %s\n",buffer);
                ret = send(info->thread_socket,buffer,BUF_SIZE,0);

                if (ret < 0) {
                    printf("Error sending data!\n\t-%s", buffer);
                }
                // pthread_mutex_unlock(&mut);
                break;
            }
        }
        //sleep(10);
    }
    printf("izasli smo iz while petlje#nismo\n");

}
void*  chat(void  *socket) {
    int  ret;
    char buffer [BUF_SIZE];
    
    memset(buffer,0,BUF_SIZE);

	struct	my_thread_info *info = socket;
	
    printf("we made it to chat(receving messages)\n");
    while (1){
        printf("still in chat\n");
        ret =recv(info->thread_socket,buffer,BUF_SIZE,0);
        if (ret < 0) {
            printf("Error receiving data!\n");
        }
        else {
            printf("\nclient: ");
            fputs(buffer, stdout);
            printf("\n");
        }
        if(strcmp(buffer,test)==0){
            printf("Iz chat client: %s",buffer);
            confromation(info->thread_socket);
            //samo za test da vidimo sta client salje tj da li uopste salje
            //*receive_some_files(sockfd);
        }
        else{
            printf("nope didnt work lets try again\n");
            printf("rezultat %d ",rezultat);
        }
    }
}
