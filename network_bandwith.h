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
#include <gtk/gtk.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "main_header.h"
typedef struct _Network Network;
struct _Network{

    unsigned  long received_bytes;
    unsigned  long transmited_bytes;
//    char *network_size_rc;
//    char *network_size_ts;
//    float received_kb;
//    float transmited_kb;


};

void received_transfered();
int interface_name();
gboolean network_change_rc(gpointer data,Network *network);
//gboolean network_change_ts(gpointer data);



#endif //GTKWORLD_NETWORK_BANDWITH_H
