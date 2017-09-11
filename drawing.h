//
// Created by dushn on 8.9.17..
//

#ifndef GTKWORLD_DRAWING_H
#define GTKWORLD_DRAWING_H
#include <math.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include "network_bandwith.h"

GArray *history[9];
struct Network net;
static  guint bjorg=1;//prvi ispis
static guint bjorg2=1;
static guint time_step=0;
static char *track;
static void do_drawing(GtkWidget *widget,cairo_t *cr, int l);
static void do_drawing2(GtkWidget *widget,cairo_t *cr, int l);
static void do_drawing3(GtkWidget *widget,cairo_t *cr, int l);

#endif //GTKWORLD_DRAWING_H
