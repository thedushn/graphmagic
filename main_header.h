//
// Created by dushn on 18.9.17..
//

#ifndef GTKWORLD_MAIN_HEADER_H
#define GTKWORLD_MAIN_HEADER_H

#include <cairo.h>
#include <gtk/gtk.h>

#include <stdlib.h>


static GtkWidget *window;
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

GtkWidget *frame1;
GtkWidget *frame2;
GtkWidget *frame3;
GtkWidget *frame4;


GtkWidget *window2;
GtkWidget *dev_window;
GtkWidget *proc_window;

GtkWidget *speed;
GtkWidget *devices_menu;
GtkWidget *filemenu2;
GtkWidget *quit;
GtkWidget *increase_refresh;
GtkWidget *decrease_refresh;
GtkWidget *file_system;






GtkWidget *box2;



GtkWidget *view2;



gchar *memory_usage_text;
gchar *swap_usage_text;
gchar *cpu0_usage_text;
gchar *cpu1_usage_text;
gchar *cpu2_usage_text;
gchar *cpu3_usage_text;
gchar *network_usage_received_text;
gchar *network_usage_transimited_text;

GArray *history[9];
GArray *task_array;
GArray *names_array;



void init_timeout();
void graph_refresh(GtkWidget *widget,gboolean);
void device_refresh(GtkWidget *widget, gboolean );
void process_refresh(GtkWidget *widget, gboolean BOOL);
void show_all(GtkWidget *widget);
void close_window();



gboolean show_user_tasks;
gboolean show_root_tasks;
gboolean show_other_tasks;
gint own_uid;
void dec_refresh();
void inc_refresh();


void init_timeout2();
void timeout_refresh();

gint tasks_num;
gint dev_num;

enum{

    COL_DEV=0,
    COL_DIR,
    COL_TYPE,
    COL_TOTAL,
    COL_AVAILABLE,
    COL_USED,
    COL_FREE,
    NUM_COLS_DEV


};


GtkTreeStore *list_store;
GtkTreeStore *list_store1;


gboolean show_cached_as_free; /* Show memory used Cache as free memory */


GtkWidget *taskpopup;





static guint t = 1000;
static guint bjorg = 1;//prvi ispis
static guint bjorg2 = 1;


static guint time_step = 0;

#endif //GTKWORLD_MAIN_HEADER_H
