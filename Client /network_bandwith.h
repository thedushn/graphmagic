//
// Created by dushn on 16.8.17..
//

#ifndef GTKWORLD_NETWORK_BANDWITH_H
#define GTKWORLD_NETWORK_BANDWITH_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>



#include <math.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdint.h>
#include "common.h"


Network received_transfered() ;
void received_transfered2(Network *network) ;
void received_transfered3(Network *network) ;
int interface_name(Network *network);
void get_rec_trans(char *name, uint64_t received, uint64_t *received_struct, uint64_t transmitted, uint64_t *transmited_struct);
void clean();




#endif //GTKWORLD_NETWORK_BANDWITH_H
