#include"stdio.h"
#include"stdlib.h"

#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"pthread.h"

#include "functions.h"

#include <arpa/inet.h>



#define BUF_SIZE 2000
#define PACKET_SIZE 1400
 pthread_mutex_t m;




int main(int argc, char *argv[]){

	struct sockaddr_in addr;
	int sockfd, ret,ret2;
	char buffer[BUF_SIZE];
	char * serverAddr;
	pthread_t t,t1,t2,t3;
	struct my_thread_info *info;
    printf("for the love of god");

	if(argc <2){
	printf("port number fail");
	exit(1);
	}
 	int portnum= atoi(argv[1]);
 serverAddr = "127.0.0.1";

	 sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) {
		printf("Error creating socket!\n");
		exit(1);
		}
	printf("Socket created...\n");
	printf("socket %d",sockfd);
	 memset(&addr, 0, sizeof(addr));
	 addr.sin_family = AF_INET;
	 addr.sin_addr.s_addr = inet_addr(serverAddr);
	 addr.sin_port =(uint16_t) htons(portnum);
//inicijalizunjemo mutex za zakljucavanje slanja
    pthread_mutex_init(&m, NULL);
	ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	 if (ret < 0) {
	  printf("Error connecting to the server!\n");
	  exit(1);
	 }
	 printf("Connected to the server...\n");

	info = malloc(sizeof(struct my_thread_info));
	info->thread_socket = sockfd;

	 memset(buffer, 0, BUF_SIZE);
	 printf("Enter your messages one by one and press return key!\n");


//	 ret = pthread_create(&t, NULL, chat,info);
//	 if (ret) {
//	  printf("ERROR: Return Code from pthread_create() is %d\n", ret);
//	  exit(1);
//	 }

//	ret2 = pthread_create(&t1, NULL, chat2, info);
// 	if (ret2) {
//	  printf("ERROR: Return Code from pthread_create() is %d\n", ret);
//	  exit(1);
//	 }
    ret2 = pthread_create(&t2, NULL, slanje, info);
   if(ret2){
  // if( pthread_create(&t2, NULL, slanje, &info)){
       printf("ERROR: Return Code from pthread_create() is %d\n",ret2);
       exit(1);

   }
//    ret2 = pthread_create(&t1, NULL, slanje_interrupta, info);
//    if(ret2){
//        // if( pthread_create(&t2, NULL, slanje, &info)){
//        printf("ERROR: Return Code from pthread_create() is %d\n",ret2);
//        exit(1);
//
//    }

    //ret= pthread_create(&t3,NULL,accept_c,info);

    if(ret){
        // if( pthread_create(&t2, NULL, slanje, &info)){
        printf("ERROR: Return Code from pthread_create() is %d\n",ret);
        exit(1);

    }
	// pthread_join( t1, NULL);

	// pthread_join( t, NULL);
   pthread_join( t2, NULL);
   // pthread_join( t3, NULL);

	 close(sockfd);

    pthread_mutex_destroy(&m);

	 pthread_exit(NULL);

	 return 0;
	}

