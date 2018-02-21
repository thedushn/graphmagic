
#ifndef CLIENT_FUNCTIONS_H
#define CLIENT_FUNCTIONS_H


#include "common.h"

void *slanje(void *socket);

void *accept_c(void *socket);

ssize_t test_send(int socket);

void send_signal_to_task(char *task_id, char *signal);

struct tm lokalno;

struct tm1 pocetno;


#endif
