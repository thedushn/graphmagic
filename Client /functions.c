#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"pthread.h"
#include <sys/stat.h>
#include <fcntl.h>
#include "functions.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include"string.h"
#include "interrupts_s.h"
#include "interrupts.h"

#define PORT 4440
#define BUF_SIZE 2000
#define PACKET_SIZE 1400
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t   cond = PTHREAD_COND_INITIALIZER;
char *test ="send\n";
char *test2 =".";
char *test3= "Type the name  of the file u want to receive\n";
char *message= "Iste su extensions mozemo da nastavimo sa slanjem\n";
char *message2= "reci kako oces da se zove file koji ti primas\n";

char *end ="end of file";
int rezultat =1;

void *accept_c(void *socket){
    printf("usli smo u accpet\n");
    struct	my_thread_info *info = socket;
    char *mem="salji mem\n";
    char buffer[BUF_SIZE];
    while (1) {
       int ret = (int )recvfrom(info->thread_socket, buffer, BUF_SIZE, 0, NULL, NULL);
       rezultat= strcmp(buffer,mem);
        if(rezultat==0){
            pthread_cond_wait(&cond,&m);
            printf("condition WAS met\n");
        }
        else
        printf("condition wasnt met\n");
    }

};
void * chat(void * socket) {
	 int sockfd, ret;
	 char buffer[BUF_SIZE];
	 struct	my_thread_info *info = socket;
	pthread_t t;
	int new;
 memset(buffer, 0, BUF_SIZE);
	printf("chat \n");
 while (1) {
	printf("we are in chat (receiving messages) \n");
  ret = recvfrom(info->thread_socket, buffer, BUF_SIZE, 0, NULL, NULL);
  if (ret < 0) {
   printf("Error receiving data!\n");
  } else {
   printf("server: ");
   fputs(buffer, stdout);
   //printf("\n");
	printf("\ndosli smo \n");
	printf("sta pise u bufferu %s \n",buffer);
	printf("sta pise u test %s\n",test);
		 rezultat=strcmp(buffer, test);
	printf("rezultat %d\n",rezultat);
	if (rezultat==0){
    	printf("it worked oce da primi file\n");
		printf("izlazimo iz chat\n");
	conformation(info->thread_socket);
	}
	else{
	printf("u didnt type it right u lemon \n");
	}


  }
 }
}

void * chat2(void * socket){
    int sockfd, ret;
    char buffer[BUF_SIZE];

    struct sockaddr_in addr;

    printf("we are in chat2,(sending messages)  \n");
	struct	my_thread_info *info = socket;

    while(1){
        printf("we made it to chat2(sending messages)\n");
        if(rezultat==0){
            pthread_cond_wait(&cond,&m);
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
  /*  while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
        printf("YOU : %s",buffer);
        ret = send(sockfd,buffer,BUF_SIZE,0);
        if (ret < 0) {
            printf("Error sending data!\n\t-%s", buffer);
        }
    }*/



}

void *conformation (int socket){
 int sockfd, ret;
 char buffer[BUF_SIZE];
 sockfd =  socket;

printf("we made it conformation\n");

ret = send(sockfd,test3,BUF_SIZE,0);

		if (ret < 0) {
	   	printf("Error sending data!\n\t-%s", test3);
		exit(1);
	 	}
	printf("sending server to tell him to type the name of the new file \n");
	send_some_files(sockfd);
}


void  *send_some_files(int socket){
	int sockfd, ret;
 	char buffer[BUF_SIZE];
	char buffer_test[BUF_SIZE];
	char buffer_file[PACKET_SIZE];
 	sockfd =  socket;
	struct sockaddr_in addr;
	FILE *filefd ;
	//ssize_t i;
    	//ssize_t read_return;
	char test_buffer[BUF_SIZE];
	double	file_size;


	printf("usli smo u send_some_files \n");
	//zakljucamo chat da ne mozemo da primamo vise poruka od servera dok se ne zavrsi slanje
	pthread_mutex_lock (&m);
	ret =(int) recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
	printf("primio je ime file od servera\n");
	if (ret < 0) {
	   printf("Error sending data!\n\t-%s", buffer);
	  }
	//upisujemo u buffer_test ime file koji server oce da primi
	printf("buffer %s\n",buffer);
    strncpy(buffer_test,buffer,strlen(buffer)-1);
	//strcat(buffer_test, buffer);
	printf("buffer_test %s\n",buffer_test);
	//proveravamo da li file postoji
	filefd= fopen(buffer_test,"r");
	if (&filefd == NULL) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	 //ispis prve linije u file
	fgets(test_buffer, 1000, filefd);
		  printf("\n%s\n",test_buffer);


	printf("we opened the file \n");
	printf("sending to server that we found the file\n");
	ret =(int) send(sockfd,message2,BUF_SIZE,0);
	if(ret<0){
		printf("Error sending data!\n\t-%s", message2);
		}
	fseek(filefd, 0, SEEK_END);
//da vidimo koliki je file
	file_size = ftell(filefd);
	fseek(filefd, SEEK_SET, 0);// da postavimo pokazivac na pocetak file
	//Provera da li je isti extension lakse bi bilo u server ali ajde da se igramo
	ret =(int) recv(sockfd,buffer,BUF_SIZE,0);
	printf("kako server oce da nazove file %s \n",buffer);
	if(ret<0){
		printf("Error sending data!\n\t-%s", buffer);
		}
    strncpy(buffer_file,buffer,strlen(buffer)-1);
	printf("da li je primio ime file %s\n", buffer);

 	 char test2 ='.';
	const char *buffer_const=  (const char *) buffer_file;
	const char *buffer_test_c=  (const char *)buffer_test;

	char *r;
	char *r2;
	r= strchr(buffer_test_c,'.');
	r2= strchr(buffer_const,'.');
	int compare;
	compare=strcmp(r,r2);
	printf("buffer_test: %s buffer: %s r:%s r2:%s \n",buffer_test,buffer,r ,r2);
	if(compare!=0){
	printf("the extensions arent the same we fucked up \n");

	printf("comparing %d ",compare);
	printf("return to begging of the program");
		pthread_mutex_unlock(&m);
		chat(&sockfd);

	}
	memset(buffer_test,0,BUF_SIZE);
	printf("comparing %d \n",compare);
	ret=(int)send(sockfd,buffer,BUF_SIZE,0);//dodato 6.5
	ret=(int) send(sockfd,message,BUF_SIZE,0);
	if(ret<0){
		printf("Error sending data!\n\t-%s", message);

		}


	printf("file size is %f mb\n",file_size/1000000);
	double packets = (file_size/PACKET_SIZE+1);
	int ipackets = (int)packets;
	printf("number of packets %d\n",ipackets);
	int cpackets = htonl(packets);
	//upisivanje velicinu file tj broj packeta i slanje serveru
	snprintf(buffer, BUF_SIZE, "%d", ipackets);
		ret=0;
	printf("%s\n",buffer);
	ret=(int)send(sockfd,buffer,BUF_SIZE,0);
	printf("%s\n",buffer);
	if(ret<0){
	 	printf("Error sending data!\n\t-%s", buffer);

	}





	memset(buffer_file,0,BUF_SIZE);
    int count=0;
	while(1){

		//printf("usli smo u nread while petlju\n");
	size_t nread =fread(buffer_file,1,PACKET_SIZE,filefd);

	if(nread >0){

	write(sockfd,buffer_file,nread);
	//printf("%s",buffer_file);
	//printf("nread %d\n",nread);
	count++;
	}
	if(nread < PACKET_SIZE){

		if(feof(filefd)){
			printf("end of file \n");
			printf("the file was sent to %d\n",sockfd);
			//ret= send(sockfd,end,BUF_SIZE,0);
               // write(sockfd,end,PACKET_SIZE);
				if(ret<0){
					printf("Error sending data!\n\t-%s", end);

				}

		}
		if (ferror(filefd)){
                    printf("Error reading\n");
		}

        printf("%d",count);
                break;
        }
	}

	fclose(filefd);//6.6
    pthread_mutex_unlock(&m);
    pthread_cond_signal(&cond);
	printf("Closing file\n");
    memset(buffer_file,0,BUF_SIZE);
	sleep(1);
	/*while(1){
	read_return = read(filefd,buffer,BUF_SIZE);
	if(read_return ==0)
		printf("neuspesna mizija za izija\n");
		break;
		if(read_return==-1){
			 perror("read");
            		exit(EXIT_FAILURE);
		}
		 if (write(sockfd, buffer, read_return) == -1) {
           	 perror("write");
           	 exit(EXIT_FAILURE);
        	}

	close(filefd);
	}*/

}

//void *slanje(void *socket){
//
//
//    data_s memory;
//    int sockfd= (int) socket;
//    char buffer[BUF_SIZE];
//    struct	my_thread_info *info = socket;
//    while(1){
//        get_memory_usage(&memory);
//
//        int ret=(int) send(info->thread_socket,&memory,sizeof(data_s),NULL);
//        if(ret<0){
//
//            printf("Error sending data!\n\t %f %lli %lli %lli \n", memory.memory_usage.swap_percentage,
//                   memory.memory_usage.swap_used
//                    ,memory.memory_usage.memory_total,
//                   memory.memory_usage.memory_used);
//        }
//
//
//
//    }
//
//}

void *slanje_interrupta(void *socket){


    int ret;
    int num_packets;
    printf("we are in slanje(sending messages)  \n");
    struct	my_thread_info *info = socket;

    while(1){
        data_s interrupts;

        GArray * ginterrupts=interrupt_usage();
         num_packets=ginterrupts->len;
        printf("we made it to slanje(sending stuff)\n");
        ret= (int)send(info->thread_socket,&num_packets,sizeof(int),NULL);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
            //  break;
            exit(1);
        }
        for(int i=0 ;i<ginterrupts->len;i++){

           Interrupts *interrupts1;
                interrupts1=&g_array_index(ginterrupts,Interrupts,i);
            interrupts.interrupts.CPU0=interrupts1->CPU0;
            interrupts.interrupts.CPU1=interrupts1->CPU1;
            interrupts.interrupts.CPU2=interrupts1->CPU2;
            interrupts.interrupts.CPU3=interrupts1->CPU3;
                    for(int j=0;j<sizeof(interrupts1->name);j++){
                        interrupts.interrupts.name[j]=interrupts1->name[j];
                    }

            upis_imena(interrupts1,&interrupts.interrupts);

            ret = (int )send(info->thread_socket,&interrupts,sizeof(data_s),0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                //  break;
                exit(1);
            }
            else{

            printf(" sending data!\n\t %lu %lu %lu %lu %s %s %s %s %s  \n", interrupts.interrupts.CPU0,interrupts.interrupts.CPU1,interrupts.interrupts.CPU2,
                 interrupts.interrupts.CPU3,  interrupts.interrupts.name,interrupts.interrupts.ime1,interrupts.interrupts.ime2,interrupts.interrupts.ime3,interrupts.interrupts.ime4);

            }

        }

//        ret = (int )send(info->thread_socket,&interrupts,sizeof(data_s),0);
//
//        if (ret < 0) {
//            printf("Error sending data!\n\t");
//            //  break;
//            exit(1);
//        }
//        else{
//
////            printf(" sending data!\n\t %f %lli %lli %lli \n", memory.memory_usage.swap_percentage,
////                   memory.memory_usage.swap_used
////                    ,memory.memory_usage.memory_total,
////                   memory.memory_usage.memory_used);
//
//        }



        sleep(1);
    }


}
void *slanje(void *socket){

    int sockfd, ret;
    char buffer[BUF_SIZE];
    int num_packets;
    struct sockaddr_in addr;

    printf("we are in slanje(sending messages)  \n");
    struct	my_thread_info *info = socket;
    char *mem="salji mem";
    while(1){
        data_s data;
     //   recv(info->thread_socket,buffer, BUF_SIZE,0);
    //    if(buffer==mem){

            get_memory_usage(&data);
            printf("we made it to slanje(sending stuff)\n");
//        if(rezultat==0){
//            pthread_cond_wait(&cond,&m);
//           printf("condtion was met\n");
//       }


            ret = (int)send(info->thread_socket,&data,sizeof(data_s),0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
              //  break;
                exit(1);
            }
    else{

                printf(" sending data!\n\t %f %lli %lli %lli \n", data.memory_usage.swap_percentage,
                       data.memory_usage.swap_used
                        ,data.memory_usage.memory_total,
                       data.memory_usage.memory_used);

            }

        GArray * ginterrupts=interrupt_usage();
        num_packets=ginterrupts->len;
        printf("we made it to slanje(sending stuff)\n");
      //  char num_packtes_c[BUF_SIZE];
      //          sprintf(num_packtes_c, "%d", num_packets);.
        printf("num of packets %d\n",num_packets);
        ret= (int)send(info->thread_socket,&num_packets,sizeof(int),NULL);
        if (ret < 0) {
            printf("Error sending num_packets!\n\t");
            //  break;
            exit(1);
        }
        for(int i=0 ;i<ginterrupts->len;i++){

            Interrupts *interrupts1;
            interrupts1=&g_array_index(ginterrupts,Interrupts,i);
            data.interrupts.CPU0=interrupts1->CPU0;
            data.interrupts.CPU1=interrupts1->CPU1;
            data.interrupts.CPU2=interrupts1->CPU2;
            data.interrupts.CPU3=interrupts1->CPU3;
            for(int j=0;j<sizeof(interrupts1->name);j++){
                data.interrupts.name[j]=interrupts1->name[j];
            }

            upis_imena(interrupts1,&data.interrupts);

            ret = (int )send(info->thread_socket,&data,sizeof(data_s),0);

            if (ret < 0) {
                printf("Error sending data!\n\t");
                //  break;
                exit(1);
            }
            else{

                printf(" sending data!\n\t %lu %lu %lu %lu %s %s %s %s %s  \n", data.interrupts.CPU0,data.interrupts.CPU1,data.interrupts.CPU2,
                       data.interrupts.CPU3,  data.interrupts.name,data.interrupts.ime1,data.interrupts.ime2,data.interrupts.ime3,data.interrupts.ime4);

            }

        }

      int  ncpu = cpu_number();
       data.cpu_usage = cpu_percentage(ncpu);
            ret=(int )send(info->thread_socket,&data,sizeof(data_s),0);
        if (ret < 0) {
            printf("Error sending data!\n\t");
            //  break;
            exit(1);
        }
        else{
            printf("CPU usage %f %f %f %f\n",data.cpu_usage.percentage0,data.cpu_usage.percentage1,data.cpu_usage.percentage2,data.cpu_usage.percentage3);
        }


    sleep(1); //treba uvesti cond variable koja kaze sada salji sada ne salji :P  #thread2
    }


}
void * stop_start(void *socket){


    struct	my_thread_info *info = socket;
int ret;
    printf("we are in stop start HELLO \n");
    char buffer[BUF_SIZE];

    char *mem="salji mem\n";
    while(1){

        recv(info->thread_socket,buffer, BUF_SIZE,0);
        rezultat= strcmp(buffer,mem);


        if(rezultat==0){
            pthread_mutex_lock (&m);
           // pthread_cond_wait(&cond,&m);
//            printf("condtion was met\n");
        }









    }

}

