//
// Created by dushn on 31.8.17..
//

#ifndef GTKWORLD_INTERRUPTS_H
#define GTKWORLD_INTERRUPTS_H
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
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

typedef struct _Interrupts Interrupts;
 void interrupt_usage();
void array_interrupts ();
GArray *ginterrupts;

struct _Interrupts{

    gchar name[3];
    gint CPU0;
    gint CPU1;
    gint CPU2;
    gint CPU3;
    gchar ime1;
    gchar ime2;
    gchar ime3;




};
#endif //GTKWORLD_INTERRUPTS_H
