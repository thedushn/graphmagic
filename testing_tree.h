//
// Created by dushn on 10.10.17..
//

#ifndef GTKWORLD_TESTING_TREE_H
#define GTKWORLD_TESTING_TREE_H

#include "string.h"
#include <gtk/gtk.h>
#include "task_manager.h"
#include <stdlib.h>
#include "devices.h"
#include "main_header.h"
//GtkTreeStore *list_store1;

GtkTreeSelection *selection;

GtkTreeSelection *selection1;
GtkWidget *treeview;
GtkWidget *treeview1;

gint compare_int_list_item(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column);



static void
status_icon_activated (void);
void remove_list_item(gint pid);
void remove_list_item_device(gchar *directory,gchar *name,gchar *type);
void refresh_list_item(gint i);
void refresh_list_item_device(gint i);
void fill_list_item(gint i, GtkTreeIter *iter);
void fill_list_item_device(gint i, GtkTreeIter *iter);
gboolean on_treeview1_button_press_event(GtkButton *button, GdkEventButton *event);
void on_button3_toggled_event(GtkButton *button, GdkEventButton *event);
void on_button1_button_press_event(GtkButton *button, GdkEventButton *event);
GtkWidget* create_mainmenu (void);
GtkWidget* create_taskpopup (void);
void on_show_cached_as_free_toggled (GtkMenuItem *menuitem, gint uid);
void on_show_tasks_toggled (GtkMenuItem *menuitem, gint uid);
void change_list_store_view_devices(GtkWidget *widget, gboolean visible);
void change_list_store_view_process(GtkWidget *widget, gboolean visible);
void change_task_view(void);
void add_new_list_item(gint i);
void add_new_list_item_dev(gint i);
void send_signal_to_task(gchar *task_id, gchar *signal);
void handle_task_menu(GtkWidget *widget, gchar *signal);GtkTreeStore * create_list_store(void);
gint compare_string_list_item(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column);
gint compare_int_list_item_size(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column);


GtkWidget* create_main_window (void);
GtkTreeStore * create_list_store_dev(void);


#endif //GTKWORLD_TESTING_TREE_H
