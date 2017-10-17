//
// Created by dushn on 19.9.17..
//

#ifndef GTKWORLD_BUTTONS_H
#define GTKWORLD_BUTTONS_H

#include <gtk/gtk.h>
#include "main_header.h"
//#include "drawing.h"


static gboolean CPU0_line=FALSE;
static gboolean CPU1_line=FALSE;
static gboolean CPU2_line=TRUE;
static gboolean CPU3_line=TRUE;

static gboolean device_devices=TRUE;
static gboolean device_type=TRUE;
static gboolean device_directory=TRUE;
static gboolean device_used=TRUE;
static gboolean device_free=TRUE;
static gboolean device_total=TRUE;
static gboolean device_avail=TRUE;
GtkWidget *button;
GtkWidget *button2;
GtkWidget *button3;
GtkWidget *button4;
GtkWidget *button5;
GtkWidget *button_dev;
GtkWidget * button_graph;
GtkWidget * button_graph0;
GtkWidget * button_graph1;
GtkWidget * button_graph2;
GtkWidget * button_graph3;
GtkWidget * button_device_devices;
GtkWidget * button_device_directory;
GtkWidget * button_device_type;
GtkWidget * button_device_avail;
GtkWidget * button_device_used;
GtkWidget * button_device_free;
GtkWidget * button_device_total;
static guint refresh = 0;
static gfloat memory_used=.5;
void button_clicked_view_process(GtkWidget *widget);
//void dev_button_clicked(GtkWidget *widget);
void graph_button_clicked(GtkWidget *widget);
void device_clicked(GtkWidget *widget);
void close_window();
void pokazi_ili_hide(GtkWidget *button, GtkWidget *window);
void graph_clicked(GtkWidget *widget);
void new_button_clicked2();
void dev_button_clicked(GtkWidget *widget);
void dev_button_clicked2(GtkWidget *widget);
void change_view(GtkWidget *wigdet);
void button_clicked_view_process(GtkWidget *widget);
void clean_button();
void device_window();

#endif //GTKWORLD_BUTTONS_H
