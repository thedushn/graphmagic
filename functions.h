//
// Created by dusan on 23.10.17..
//

#ifndef GTKWORLD_FUNCTIONS_H
#define GTKWORLD_FUNCTIONS_H

//
// Created by root on 13.6.17..
//

#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

#include "pthread.h"
void * confromation(void *socket);
void *receiving(void *socket);
void *chat(void *socket);
void *chat2(void *socket);
pthread_mutex_t mut;
pthread_cond_t  cond ;

#endif //SERVER_FUNCTIONS_H
#endif //GTKWORLD_FUNCTIONS_H
