//
// Created by dushn on 11.10.17..
//

#ifndef GTKWORLD_WINDOW_C_H
#define GTKWORLD_WINDOW_C_H

#include "main_header.h"





void quit_activated() ;
gboolean  cpu_change();
void memory_change(gpointer data);
void swap_change(gpointer data);
GtkWidget *main_window(GtkWidget *des_swindow,GtkWidget *proc_swindow);

GtkWidget *menubar;
GtkWidget *filemenu;
#endif //GTKWORLD_WINDOW_C_H
