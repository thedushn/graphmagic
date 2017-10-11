//
// Created by dushn on 19.9.17..
//

#ifndef GTKWORLD_BUTTONS_H
#define GTKWORLD_BUTTONS_H

#include <gtk/gtk.h>
#include "main_header.h"
#include "drawing.h"

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
static guint refresh = 0;
static gfloat memory_used=.5;
void button_clicked_view_process(GtkWidget *widget);
//void dev_button_clicked(GtkWidget *widget);
void graph_button_clicked(GtkWidget *widget);
void graph_clicked(GtkWidget *widget);
void close_window();
void pokazi_ili_hide(GtkWidget *button, GtkWidget *window);
//gboolean graph_clicked(GtkWidget *widget);
void new_button_clicked2();

void clean_button();

#endif //GTKWORLD_BUTTONS_H
