//
// Created by dushn on 18.9.17..
//

#ifndef GTKWORLD_MAIN_HEADER_H
#define GTKWORLD_MAIN_HEADER_H

#include <cairo.h>
#include <gtk/gtk.h>

#include <stdlib.h>



 GtkWidget *window2;
 GtkWidget *process_swindow;
 GtkWidget *dev_swindow;

int newsockfd;
GArray *history[8];
GArray *task_array;
GArray *names_array;
GArray *interrupt_array_d;


void init_timeout();
void graph_refresh(GtkWidget *widget,gboolean);

void dec_refresh();
void inc_refresh();
void timeout_refresh();


#endif //GTKWORLD_MAIN_HEADER_H
