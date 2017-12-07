#include"stdio.h"
#include"stdlib.h"

#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"pthread.h"

#include "functions.h"
#include "cpu_usage.h"


#include <arpa/inet.h>
#include <bits/signum.h>

#include <netdb.h>
#include <signal.h>
#include <errno.h>
#include <wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>


#define BUF_SIZE 2000

// pthread_mutex_t m;

#define CLADDR_LEN 100

void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
int main(int argc, char *argv[]){

/*

	struct sockaddr_in addr ,cl_addr;
	int sockfd ,ret;
	char buffer[BUF_SIZE];
	char clientAddr[CLADDR_LEN];

    int ret2;
    printf("interrupti %d",(int)sizeof(Interrupts));
    printf("memory %d",(int)sizeof(Memory_usage));
    printf("devices %d",(int)sizeof(Devices));
    printf("tasks %d",(int)sizeof(Task));
    printf("cpu %d",(int)sizeof(Cpu_usage));
    printf("commands %d",(int)sizeof(Commands));
    printf("network %d",(int)sizeof(Network));
    // printf("tm %d\n",(int)sizeof(struct tm));
    //  printf("tm1 %d\n",(int)sizeof(struct tm1));
    printf("uns long long  %d\n",(int)sizeof(unsigned long long));


    struct my_thread_info *info;

    if(argc <2){

        printf("no port provided");
        exit(1);
    }
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
*/


    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv,ret, ret2;
    char buffer[BUF_SIZE];
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if(argc <2){

        printf("no port provided");
        exit(1);
    }
   // uint16_t portnum=(uint16_t)atoi(argv[1]);

    if ((rv = getaddrinfo(NULL, argv[1], &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, 10) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");


     {  // main accept() loop
        sin_size = sizeof their_addr;
        sockfd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
        if (sockfd == -1) {
            perror("accept");

        }
    }


    inet_ntop(their_addr.ss_family,
              get_in_addr((struct sockaddr *)&their_addr),
              s, sizeof s);
    printf("server: got connection from %s\n", s);


        struct my_thread_info *info;




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
	struct tm tm2 = *localtime(&time1);

    int sec0, hr0, min0, t0;

    struct tm1  stop_time;






    hr0 =uptime1/3600;
    t0 = uptime1%3600;
    min0 = t0/60;
    sec0 = t0%60;
    stop_time.tm_hour=(__uint32_t)hr0; //pre koliko sati se upalio komp
    stop_time.tm_min=(__uint32_t)min0;
    stop_time.tm_sec=(__uint32_t)sec0;

    differenceBetweenTimePeriod(tm2, stop_time, &pocetno);// vreme kada je poceo da radi linux
   // interface_name();
	printf("now: %d-%d-%d %d:%d:%d\n", tm2.tm_year+1900 , tm2.tm_mon , tm2.tm_mday, tm2.tm_hour, tm2.tm_min, tm2.tm_sec);
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
	clean();
    /*free(hash_cpu_system);
    free(hash_cpu_user);*/
    free(info);

    printf("hash_freed\n");



	 //pthread_exit(NULL);

	 return 0;
	}

