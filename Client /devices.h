//
// Created by dushn on 25.9.17..
//

#ifndef GTKWORLD_DEVICES_H
#define GTKWORLD_DEVICES_H

#endif //GTKWORLD_DEVICES_H
#include <setjmp.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include <math.h>
#include <sys/stat.h>
#include <pwd.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>


#include "common.h"

//void try();
void readDir(char *path);


void device2(Devices * * array,bool show,int *niz2);

//void get_names();
void mountlist(char *path,size_t j,gboolean mount);
void mountlist3(Devices **array,bool mount,int *fake);
//void array_devices();







//void get_boot(void);