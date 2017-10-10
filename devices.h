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

typedef struct _Devices Devices;
typedef struct _Memory Memory;
void try();
void readDir(char *path);
void device(gboolean show);
void get_names();
void mountlist(char *path,size_t j,gboolean mount);
void array_devices();

void printanje_dev(GArray *array);
GArray *names;
GArray *names_temp;

struct _Devices {


    gchar		name[256];

    gchar       type[256];
    gchar       directory[256];
    glong used;
    glong total;
    glong free;
    glong avail;
};

void get_boot(void);