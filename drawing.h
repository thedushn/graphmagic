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


#include "common.h"


void do_drawing_net(GtkWidget *widget, cairo_t *cr, guint bjorg2, guint time_step);
void do_drawing_cpu(GtkWidget *widget, cairo_t *cr, guint bjorg, guint time_step);

void do_drawing_mem(GtkWidget *widget, cairo_t *cr, guint bjorg, guint time_step);
void do_drawing_int(GtkWidget *widget, cairo_t *cr);
//void do_drawing_int(GtkWidget *widget,cairo_t *cr,GArray *interrupts_array);
void crtaj_sekunde(cairo_t *cr,float width,float height,float font_size,int i,int j);
void crtaj_okvir(cairo_t *cr,float width,float height,float font_size,int i);
void crtaj_procente(cairo_t *cr,gfloat height,gfloat font_size);
void  crtaj_interrupte(cairo_t *cr,int i,Interrupts *peak,float height,float font_size,long max_broj,float duzina);
void ispis_interrupta2(cairo_t *cr,float font_size,float duzina,int i,gchar *ime1,gchar *ime2);

void crtanje_graph(cairo_t *cr, GArray *history, int r, int y, int i, int height, gfloat font_size, double step,gfloat max_broj3);

cairo_surface_t *crtaj_surface(cairo_t *cr,int width,int height);
#endif //GTKWORLD_DRAWING_H
