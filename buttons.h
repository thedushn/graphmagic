//
// Created by dushn on 19.9.17..
//

#ifndef GTKWORLD_BUTTONS_H
#define GTKWORLD_BUTTONS_H

#include <gtk/gtk.h>
typedef struct _Signal  Signal;
            struct _Signal{
                    gchar signal[5];
                    gchar task_id[256];

            };







GtkWidget *button;
GtkWidget *button2;
GtkWidget *button_proc;
//GtkWidget *button4;
//GtkWidget *button5;
//GtkWidget *buttton_cpus;
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
GtkWidget * button_process_prio;
GtkWidget * button_process_stime;

GtkWidget * button_condition;


static guint refresh = 0;
gboolean on_treeview1_button_press_event(GtkButton *button, GdkEventButton *event);
GtkWidget* create_taskpopup (void);
void send_signal_to_task(gchar *task_id, gchar *signal);
void handle_task_menu(GtkWidget *widget, gchar *signal);
void button_clicked_view_process(GtkWidget *widget);
//void dev_button_clicked(GtkWidget *widget);
void graph_button_clicked(GtkWidget *widget);

void close_window();
void pokazi_ili_hide(GtkWidget *button, GtkWidget *window);

void new_button_clicked2();
//void dev_button_clicked(GtkWidget *widget);
void dev_button_clicked2(GtkWidget *widget);
//void change_view(GtkWidget *wigdet);
void button_clicked_view_process(GtkWidget *widget);
void clean_button();
void device_window();
void process_window();
void process_clicked(GtkWidget *widget);
void device_clicked(GtkWidget *widget);
void graph_clicked(GtkWidget *widget);
void start_stop(int show,gchar *signal ,gchar *task_id);
#endif //GTKWORLD_BUTTONS_H
