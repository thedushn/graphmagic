//
// Created by dushn on 11.10.17..
//

#ifndef GTKWORLD_WINDOW_C_H
#define GTKWORLD_WINDOW_C_H

#include "main_header.h"
#include "common.h"




void quit_activated() ;
void  cpu_change(Cpu_usage1 *cpu_usage1);
void memory_change(gpointer data,Memory_usage *memory_usage);
void swap_change(gpointer data,Memory_usage *memory_usage);
void network_change_rc(gpointer data,gpointer data2,Network *network);
void time_change(gpointer data,struct tm *tm);
GtkWidget *main_window(GtkWidget *des_swindow,GtkWidget *proc_swindow);

GtkWidget *menubar;
GtkWidget *filemenu;
#endif //GTKWORLD_WINDOW_C_H
