#include"stdio.h"
#include"stdlib.h"

#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"pthread.h"

#include "functions.h"

#include <arpa/inet.h>



#define BUF_SIZE 2000

// pthread_mutex_t m;




int main(int argc, char *argv[]){

	struct sockaddr_in addr;
	int sockfd, ret,ret2;
	char buffer[BUF_SIZE];
	char * serverAddr;
	pthread_t t2,t3;
	struct my_thread_info *info;
    printf("for the love of god\n");
	 interface_name();
	if(argc <2){
	printf("port number fail\n");
	exit(1);
	}
    uint16_t portnum= (uint16_t)atoi(argv[1]);
 	serverAddr = "127.0.0.1";

	 sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0) {
		printf("Error creating socket!\n");
		exit(1);
		}
	printf("Socket created...\n");
	printf("socket %d\n",sockfd);
   // printf ("_SC_CLK_TCK = %ld\n", sysconf (_SC_CLK_TCK));
 //   long int clock_ticks=sysconf (_SC_CLK_TCK);
	 memset(&addr, 0, sizeof(addr));
	 addr.sin_family = AF_INET;
	 addr.sin_addr.s_addr = inet_addr(serverAddr);
	 addr.sin_port =(uint16_t) htons(portnum);

//inicijalizunjemo mutex za zakljucavanje slanja
   // pthread_mutex_init(&m, NULL);
	ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	 if (ret < 0) {
	  printf("Error connecting to the server!\n");
	  exit(1);
	 }
	 printf("Connected to the server...\n");

	info = malloc(sizeof(struct my_thread_info));
	info->thread_socket = sockfd;

/*	 printf("Enter your messages one by one and press return key!\n");*/

 /*   ret = (int) send(sockfd, &clock_ticks, sizeof(long int), 0);

	 if (ret<0) {
	  printf("ERROR: Return Code  is %d\n", ret);
	  exit(1);
	 }
*/



    FILE *fp;

	unsigned long  uptime1=0;
  fp = fopen ("/proc/uptime", "r");
  if (fp != NULL) {

      while (fgets(buffer, 1024, fp) != NULL) {


        sscanf(buffer,"%lu",&uptime1);
      }
  }

      fclose (fp);


  /*  ret =(int)send(sockfd,&uptime1,sizeof(unsigned long),0);
    	if (ret<0) {
	  printf("ERROR: Return Code from pthread_create() is %d\n", ret);
	  exit(1);
	 }*/


	time_t time1 = time(NULL);
	struct tm tm = *localtime(&time1);

    int sec0, hr0, min0, t0;

    struct tm  stop_time;






    hr0 =(int) uptime1/3600;
    t0 =(int) uptime1%3600;
    min0 = t0/60;
    sec0 = t0%60;
    stop_time.tm_hour=hr0; //pre koliko sati se upalio komp
    stop_time.tm_min=min0;
    stop_time.tm_sec=sec0;

    differenceBetweenTimePeriod(tm, stop_time, &pocetno);// vreme kada je poceo da radi linux

//	printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year , tm.tm_mon , tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	/*ret = (int) send(sockfd, &tm, sizeof(tm), 0);
	if (ret<0) {
		printf("ERROR: Return Code  is %d\n", ret);
		exit(1);
	}*/

    ret2 = pthread_create(&t2, NULL, slanje, info);
   if(ret2){
  // if( pthread_create(&t2, NULL, slanje, &info)){
       printf("ERROR: Return Code from pthread_create() is %d\n",ret2);
       exit(1);

   }

    ret= pthread_create(&t3,NULL,accept_c,info);

    if(ret){

        printf("ERROR: Return Code from pthread_create() is %d\n",ret);
        exit(1);

    }

   pthread_join( t2, NULL);
    pthread_join( t3, NULL);

	 close(sockfd);



	 pthread_exit(NULL);

	 return 0;
	}

