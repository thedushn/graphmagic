//
// Created by dushn on 11.10.17..
//

#ifndef GTKWORLD_WINDOW_C_H
#define GTKWORLD_WINDOW_C_H

#include "main_header.h"
#include "common.h"


GtkWidget *graph1;
GtkWidget *graph2;
GtkWidget *graph3;
GtkWidget *graph4;


void quit_activated() ;
void  cpu_change(Cpu_usage  *cpu_usage1);
void memory_change(Memory_usage *memory_usage);
void swap_change(Memory_usage *memory_usage);
void network_change_rc(Network *network);

GtkWidget *main_window(GtkWidget *des_swindow,GtkWidget *proc_swindow);


#endif //GTKWORLD_WINDOW_C_H
