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
#include <cairo.h>
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
#include "main_header.h"
GArray *names;
typedef struct _Devices Devices;
void try();
void readDir(char *path);
void device();
void get_names();
void mountlist(GArray *array);

struct _Devices {


    gchar		name[256];
    guint       available;
    gchar       type[256];
    gchar       directory[256];
    guint       total;
    guint       free;

};

void get_boot(void);