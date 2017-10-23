//
// Created by dushn on 10.10.17..
//

#ifndef GTKWORLD_TESTING_TREE_H
#define GTKWORLD_TESTING_TREE_H

#include "string.h"
#include <gtk/gtk.h>

#include <stdlib.h>



//GtkTreeStore *list_store1;

GtkTreeSelection *selection;

GtkTreeSelection *selection1;
GtkWidget *treeview;
GtkWidget *treeview1;

gint compare_int_list_item(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column);





void remove_list_item(gint pid);
void remove_list_item_device(gchar *directory,gchar *name,gchar *type);
void refresh_list_item(gint i);
void refresh_list_item_device(gint i);
void fill_list_item(gint i, GtkTreeIter *iter);
void fill_list_item_device(gint i, GtkTreeIter *iter);


void change_list_store_view_devices(GtkWidget *widget, gboolean visible);
void change_list_store_view_process(GtkWidget *widget, gboolean visible);

void add_new_list_item(gint i);
void add_new_list_item_dev(gint i);

GtkTreeStore * create_list_store(void);
gint compare_string_list_item(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column);
gint compare_int_list_item_size(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column);



GtkTreeStore * create_list_store_dev(void);

enum
{
    COL_TASK = 0,
    COL_PID,
    COL_RSS,
    COL_CPU,
    COL_VSZ,
    COL_PPID,
    COL_STATE,
    COL_UNAME,
    NUM_COLS
} ;

#endif //GTKWORLD_TESTING_TREE_H
