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

void upis(GArray *array,GArray *array2);
void poredjenje(GArray *array,GArray *array2,GArray *array3);
void upis_imena(Interrupts *interrupts1,Interrupts *interrupts3);
gint sortiranje(gconstpointer a,gconstpointer b);

#endif //GTKWORLD_INTERRUPTS_H
