//
// Created by root on 13.6.17..
//

#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H
#include "common.h"

void * confromation(int socket);
void *receiving(int socket);
void* chat(void* socket);
void* chat2(void* socket);
void *primanje(void * socket);

pthread_mutex_t mut;
pthread_cond_t  cond ;

struct my_thread_info {
    int thread_socket;
};



#endif //SERVER_FUNCTIONS_H
