
#ifndef CLIENT_FUNCTIONS_H
#define CLIENT_FUNCTIONS_H

#include "memory_usage.h"
#include "common.h"
#include "task_manager.h"
#include "devices.h"
#include "network_bandwith.h"
void * chat(void * socket);
void *conformation (int socket);
void *send_some_files(int socket);
void *chat2(void * socket);
void *slanje(void * socket);
void *accept_c (void *socket);

void send_signal_to_task(char *task_id, char *signal);
struct my_thread_info {
    int thread_socket;
};
struct tm tm1;

struct tm1 pocetno;
pthread_t t2,t3;

#endif
