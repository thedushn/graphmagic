//
// Created by dushn on 18.9.17..
//

#ifndef GTKWORLD_MAIN_HEADER_H
#define GTKWORLD_MAIN_HEADER_H

#include <cairo.h>
#include <gtk/gtk.h>

#include <stdlib.h>


static GtkWidget *window;
 GtkWidget *window2;
 GtkWidget *process_swindow;
 GtkWidget *dev_swindow;

GtkWidget *graph1;
GtkWidget *graph2;
GtkWidget *graph3;
GtkWidget *graph4;
GtkWidget *vbox;
GtkWidget *hbox;
GtkWidget *hbox1;
GtkWidget *hbox3;
GtkWidget *hbox2;
GtkWidget *label;
GtkWidget *label1;

GtkWidget *label3;
GtkWidget *label4;
GtkWidget *label5;
GtkWidget *label6;
GtkWidget *label7;
GtkWidget *label8;
GtkWidget *label_time;

GtkWidget *frame1;
GtkWidget *frame2;
GtkWidget *frame3;
GtkWidget *frame4;



GtkWidget *dev_window;
GtkWidget *proc_window;

GtkWidget *speed;
GtkWidget *devices_menu;
GtkWidget *filemenu2;
GtkWidget *quit;
GtkWidget *increase_refresh;
GtkWidget *decrease_refresh;
GtkWidget *file_system;
int newsockfd;

struct tm tm;

struct tm pocetno;
void differenceBetweenTimePeriod(struct tm start, struct tm stop, struct tm *diff);



GtkWidget *box2;



GtkWidget *view2;








GArray *history[9];
GArray *task_array;
//GArray *names_temp;
GArray *names_array;
GArray *interrupt_array_d;
 GArray *interrupt_array_temp;



void *init_timeout();
void graph_refresh(GtkWidget *widget,gboolean);
void device_refresh(GtkWidget *widget, gboolean );
void process_refresh(GtkWidget *widget, gboolean BOOL);
void show_all(GtkWidget *widget);
void close_window();
static gboolean time_handler(GtkWidget *widget);





void dec_refresh();
void inc_refresh();


void init_timeout2();
void timeout_refresh();

gint tasks_num;
gint dev_num;




GtkTreeStore *list_store;
GtkTreeStore *list_store1;





GtkWidget *taskpopup;





static guint t = 1000;
static guint bjorg = 1;//prvi ispis
static guint bjorg2 = 1;


static guint time_step = 0;

#endif //GTKWORLD_MAIN_HEADER_H
