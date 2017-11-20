#include"stdio.h"
#include"stdlib.h"

#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"pthread.h"

#include "functions.h"
#include "cpu_usage.h"

#include <arpa/inet.h>



#define BUF_SIZE 2000

// pthread_mutex_t m;

#define CLADDR_LEN 100


int main(int argc, char *argv[]){


	struct sockaddr_in addr ,cl_addr;
	int sockfd ,ret;
	char buffer[BUF_SIZE];
	char clientAddr[CLADDR_LEN];

    int ret2;


    struct my_thread_info *info;

//    if(argc <2){
//
//        printf("no port provided");
//        exit(1);
//    }
	uint16_t portnum=(uint16_t)atoi(argv[1]);
	// int portnum=5555;
	printf("port number %d ",portnum);
	sockfd =socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		printf("Error creating socket!\n");
		exit(1);
	}
	printf("Socket created \n");

	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = (uint16_t)htons(portnum);


	ret = bind(sockfd,(struct sockaddr *) &addr, sizeof(addr));
	if (ret < 0){
		printf("Error binding!\n");
		exit(1);
	}
	printf("Binding done...\n");

	printf("Waiting for a connection...\n");

	listen(sockfd, 5); //hello is anybody going to call me :{
	printf("da li smo prosli \n");
	socklen_t len =sizeof(cl_addr);
	sockfd = accept(sockfd,(struct sockaddr *) &cl_addr, &len);
	if (sockfd < 0) {
		printf("Error accepting connection!\n");
		exit(1);
	}

	inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
	printf("Connection accepted from %s...\n", clientAddr);

	memset(buffer,0,BUF_SIZE);

//    if(pthread_mutex_init(&mut, NULL)!=0){
//        printf("mutex init failed \n");
//        exit(1);
//    }

	printf("making threads\n");






	info = malloc(sizeof(struct my_thread_info));
	info->thread_socket = sockfd;





    FILE *fp;

	int uptime1=0;
  fp = fopen ("/proc/uptime", "r");
  if (fp != NULL) {

      while (fgets(buffer, 1024, fp) != NULL) {


        sscanf(buffer,"%d",&uptime1);
      }
  }

      fclose (fp);






	time_t time1 = time(NULL);
	struct tm tm = *localtime(&time1);

    int sec0, hr0, min0, t0;

    struct tm1  stop_time;






    hr0 =(int) uptime1/3600;
    t0 =(int) uptime1%3600;
    min0 = t0/60;
    sec0 = t0%60;
    stop_time.tm_hour=hr0; //pre koliko sati se upalio komp
    stop_time.tm_min=min0;
    stop_time.tm_sec=sec0;

    differenceBetweenTimePeriod(tm, stop_time, &pocetno);// vreme kada je poceo da radi linux
    interface_name();
	printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year , tm.tm_mon , tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	/*ret = (int) send(sockfd, &tm, sizeof(tm), 0);
	if (ret<0) {
		printf("ERROR: Return Code  is %d\n", ret);
		exit(1);
	}*/

    ret2 = pthread_create(&t2, NULL, slanje, &sockfd);
   if(ret2!=0){
  // if( pthread_create(&t2, NULL, slanje, &info)){
       printf("ERROR: Return Code from pthread_create() is %d\n",ret2);
       exit(1);

   }

    ret= pthread_create(&t3,NULL,accept_c,&sockfd);

    if(ret!=0){

        printf("ERROR: Return Code from pthread_create() is %d\n",ret);
        exit(1);

    }
    printf("threads joined\n");
   pthread_join( t2, NULL);
    pthread_join( t3, NULL);

	 close(sockfd);
    printf("socket_closed\n");
    uradi(true);
    /*free(hash_cpu_system);
    free(hash_cpu_user);*/
    free(info);
    printf("hash_freed\n");



	 //pthread_exit(NULL);

	 return 0;
	}

