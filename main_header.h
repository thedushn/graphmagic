//
// Created by dushn on 18.9.17..
//

#ifndef GTKWORLD_MAIN_HEADER_H
#define GTKWORLD_MAIN_HEADER_H

#include <cairo.h>
#include <gtk/gtk.h>

#include <stdlib.h>


static GtkWidget *window;
static GtkWidget *process_swindow;
static GtkWidget *dev_swindow;

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
GtkWidget *label2;
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
GtkTreeIter iter;
GtkWidget *speed;
GtkWidget *devices_menu;
GtkWidget *filemenu2;
GtkWidget *quit;
GtkWidget *increase_refresh;
GtkWidget *decrease_refresh;
GtkWidget *show_all;








GtkWidget *box2;


GtkWidget *view;
GtkWidget *view2;
GtkWidget *view_dev;


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
void close_window();

static GtkWidget *create_view_and_model_file_system (void);
static GtkWidget *create_view_and_model (void);
static GtkTreeModel *create_and_fill_model (void);
static GtkTreeModel *create_and_fill_model_file_system (void);
void dev_problems(gboolean,GtkWidget *window);
gboolean show_user_tasks;
gboolean show_root_tasks;
gboolean show_other_tasks;
gint own_uid;
void dec_refresh();
void inc_refresh();
void dev_button_clicked(GtkWidget *widget);

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

gboolean full_view;


GtkWidget *mainmenu;

GtkWidget *taskpopup;
GtkWidget *cpu_usage_progress_bar;
GtkWidget *mem_usage_progress_bar;
GtkWidget *cpu_usage_progress_bar_box;
GtkWidget *mem_usage_progress_bar_box;
GtkTreeViewColumn *column;

#define COLUMN_NAME	0
#define COLUMN_PID	1
#define COLUMN_PPID	2
#define COLUMN_STATE	3
#define COLUMN_MEM	4
#define COLUMN_RSS	5
#define COLUMN_UNAME	6
#define COLUMN_CPU   7
#define COLUMN_CPU2   8
#define COLUMN_TIME	7



static guint t = 1000;
static guint bjorg = 1;//prvi ispis
static guint bjorg2 = 1;


static guint time_step = 0;

#endif //GTKWORLD_MAIN_HEADER_H
