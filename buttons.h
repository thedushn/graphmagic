//
// Created by dushn on 19.9.17..
//

#ifndef GTKWORLD_BUTTONS_H
#define GTKWORLD_BUTTONS_H

#include <gtk/gtk.h>




static gboolean CPU0_line=TRUE;
static gboolean CPU1_line=TRUE;
static gboolean CPU2_line=TRUE;
static gboolean CPU3_line=TRUE;

static gboolean device_devices=TRUE;
static gboolean device_type=TRUE;
static gboolean device_directory=TRUE;
static gboolean device_used=TRUE;
static gboolean device_free=TRUE;
static gboolean device_total=TRUE;
static gboolean device_avail=TRUE;
static gboolean device_all=FALSE;

static gboolean process_task=TRUE;
static gboolean process_user=TRUE;
static gboolean process_pid=TRUE;
static gboolean process_ppid=TRUE;
static gboolean process_cpu=TRUE;
static gboolean process_vm_size=TRUE;
static gboolean process_rss=TRUE;
static gboolean process_state=TRUE;

GtkWidget *button;
GtkWidget *button2;
GtkWidget *button_proc;
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
GtkWidget *button_device_all;
GtkWidget * button_device_free;
GtkWidget * button_device_total;
GtkWidget * button_process_task;
GtkWidget * button_process_user;
GtkWidget * button_process_pid;
GtkWidget * button_process_ppid;
GtkWidget * button_process_state;
GtkWidget * button_process_vm_size;
GtkWidget * button_process_rss;
GtkWidget * button_process_cpu;


static guint refresh = 0;
static gfloat memory_used=.5;
void button_clicked_view_process(GtkWidget *widget);
//void dev_button_clicked(GtkWidget *widget);
void graph_button_clicked(GtkWidget *widget);

void close_window();
void pokazi_ili_hide(GtkWidget *button, GtkWidget *window);

void new_button_clicked2();
void dev_button_clicked(GtkWidget *widget);
void dev_button_clicked2(GtkWidget *widget);
void change_view(GtkWidget *wigdet);
void button_clicked_view_process(GtkWidget *widget);
void clean_button();
void device_window();
void process_window();
void process_clicked(GtkWidget *widget);
void device_clicked(GtkWidget *widget);
void graph_clicked(GtkWidget *widget);

#endif //GTKWORLD_BUTTONS_H
