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

#include <gtk/gtk.h>
#include <math.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "common.h"


Network received_transfered() ;
int interface_name();
gboolean network_change_rc(gpointer data);
gboolean network_change_ts(gpointer data);



#endif //GTKWORLD_NETWORK_BANDWITH_H
