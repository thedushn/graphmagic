//
// Created by dushn on 31.8.17..
//

#ifndef GTKWORLD_INTERRUPTS_H
#define GTKWORLD_INTERRUPTS_H
#include <gtk/gtk.h>
#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>






#include <stdlib.h>
#include "common.h"
//typedef struct _Interrupts Interrupts;
GArray * interrupt_usage();
void upis(GArray *array,GArray *array2);
void poredjenje(GArray *array,GArray *array2,GArray *array3);
//GArray * poredjenje(GArray *array,GArray *array2);
void upis_imena(Interrupts *interrupts1,Interrupts *interrupts3);
gint sortiranje(gconstpointer a,gconstpointer b);
//struct _Interrupts{
//
//    gchar name[4];
//    signed long CPU0;
//    signed long CPU1;
//    signed long CPU2;
//    signed long CPU3;
//    gchar ime1[256];
//    gchar ime2[256];
//    gchar ime3[256];
//    gchar ime4[256];
//
//};
#endif //GTKWORLD_INTERRUPTS_H
