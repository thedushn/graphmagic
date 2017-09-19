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
#include "interrupts.h"
//#include "main_header.h"
GArray *history[9];
struct Network net;


void do_drawing(GtkWidget *widget,cairo_t *cr);
void do_drawing2(GtkWidget *widget,cairo_t *cr);
void do_drawing3(GtkWidget *widget,cairo_t *cr);
void do_drawing4(GtkWidget *widget,cairo_t *cr);
cairo_t * crtaj_sekunde(cairo_t *cr,float width,float height,float font_size,int i);
cairo_t * crtaj_okvir(cairo_t *cr,float width,float height,float font_size,int i);
cairo_t * crtaj_procente(cairo_t *cr,gfloat height,gfloat font_size);
cairo_t *  crtaj_interrupte(cairo_t *cr,int i,Interrupts *peak,float height,float font_size,long max_broj,float duzina);
//cairo_t *crtanje_cpu2(cairo_t *cr,int r,int j,gfloat weight,gfloat height, gfloat font_size, double step);
cairo_t *crtanje_cpu(cairo_t *cr,GArray *history,int r,int j,int weight,int height, gfloat font_size, double step);
//cairo_t *crtanje_cpu(cairo_t *cr,int r,int j,int weight,int height, gfloat font_size, double step);
cairo_surface_t *crtaj_surface(cairo_t *cr,int width,int height);
#endif //GTKWORLD_DRAWING_H
