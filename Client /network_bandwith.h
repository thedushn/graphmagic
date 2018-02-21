//
// Created by dushn on 16.8.17..
//

#ifndef GTKWORLD_NETWORK_BANDWITH_H
#define GTKWORLD_NETWORK_BANDWITH_H

#include "common.h"

struct DataItem_net {

    __uint64_t data;
    char key[64];


};

int interface_name(Network *network);

void get_rec_trans(char *name, __uint64_t received
        ,__uint64_t *received_struct
        ,__uint64_t transmitted
        , __uint64_t *transmited_struct
    )
;
void clean();

__uint64_t search_net(char * key, struct DataItem_net  *hashArray
        ,int hash_size ,bool *ima, __uint64_t data);





#endif //GTKWORLD_NETWORK_BANDWITH_H
