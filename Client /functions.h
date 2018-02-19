
#ifndef CLIENT_FUNCTIONS_H
#define CLIENT_FUNCTIONS_H

#include "memory_usage.h"
#include "common.h"
#include "task_manager.h"
#include "devices.h"
#include "network_bandwith.h"

void *slanje(void * socket);
void *accept_c (void *socket);
ssize_t test_send(int socket);
void send_signal_to_task(char *task_id, char *signal);

struct tm lokalno;

struct tm1 pocetno;


#endif
