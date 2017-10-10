//
// Created by dushn on 18.9.17..
//

#ifndef GTKWORLD_MAIN_HEADER_H
#define GTKWORLD_MAIN_HEADER_H

#include "gtk/gtk.h"

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
GSList *group;
GtkWidget *window2;
GtkWidget *progressbar;
GtkWidget *box1;

GtkTreeIter iter;

GtkWidget *speed;
GtkWidget *devices_menu;
GtkWidget *graph_menu;
GtkWidget *filemenu2;
GtkWidget *filemenu3;
GtkWidget *quit;
GtkWidget *increase_refresh;
GtkWidget *decrease_refresh;
GtkWidget *show_all;
#define COLUMN_PROPERTIES "expand", TRUE, "clickable", TRUE, "reorderable", TRUE, "resizable", TRUE, "visible", TRUE






static int testiranje=1;
GtkWidget *box2;

GtkWidget *tree;
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


void init_timeout();
void graph_refresh(GtkWidget *widget,gboolean);
void close_window();
//void create_view_and_model_file_system (void);
static GtkWidget *create_view_and_model_file_system (void);
static GtkWidget *create_view_and_model (void);
static GtkTreeModel *create_and_fill_model (void);
static GtkTreeModel *create_and_fill_model_file_system (void);
GtkWidget*
find_child(GtkWidget* parent, const gchar* name);
void dev_problems(gboolean,GtkWidget *window);
gboolean show_user_tasks;
gboolean show_root_tasks;
gboolean show_other_tasks;
gint own_uid;

gint tasks_num;

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
GtkWidget *treeview;

gboolean show_cached_as_free; /* Show memory used Cache as free memory */
GtkTreeSelection *selection;
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
#endif //GTKWORLD_MAIN_HEADER_H
