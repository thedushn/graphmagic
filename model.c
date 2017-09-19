/*
//
// Created by dushn on 12.9.17..
//

#include "model.h"
#include "main_header.h"
static GtkWidget *create_view_and_model (void);
static GtkTreeModel *create_and_fill_model (void);
static GtkWidget *create_view_and_model (void)
{
    GtkCellRenderer     *renderer;

    GtkWidget           *view;
    GtkTreeViewColumn *column;
    column = gtk_tree_view_column_new ();
    view = gtk_tree_view_new ();
  //  g_object_set (column, COLUMN_PROPERTIES, NULL);
    */
/* --- Column #1 --- *//*

    //test
    //  column = gtk_tree_view_column_new ();
    renderer = gtk_cell_renderer_text_new ();
    //gtk_tree_view_insert_column(GTK_TREE_VIEW (view),column,)
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Task",
                                                 renderer,
                                                 "text", COL_TASK,
                                                 NULL);

    */
/* --- Column #2 --- *//*


    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "PID",
                                                 renderer,
                                                 "text", COL_PID,
                                                 NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "RSS",
                                                 renderer,
                                                 "text", COL_RSS,
                                                 NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "CPU",
                                                 renderer,
                                                 "text", COL_CPU,
                                                 NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "VSZ",
                                                 renderer,
                                                 "text", COL_VSZ,
                                                 NULL);


    model = create_and_fill_model ();

    gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

    */
/* The tree view has acquired its own reference to the
     *  model, so we can drop ours. That way the model will
     *  be freed automatically when the tree view is destroyed *//*


    g_object_unref (model);

    return view;
};
static GtkTreeModel *create_and_fill_model (void)
{



    store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_UINT,G_TYPE_STRING,G_TYPE_FLOAT,G_TYPE_STRING);
    gchar *rss, *vsz;
    */
/* Append a row and fill in some data *//*


    printf("TASKs-array : len: %d\n",tasks->len);

    for(int j=0 ;j<tasks->len;j++) {
        Task *task = &g_array_index(tasks, Task, j);
        rss = g_format_size_full (task->rss, G_FORMAT_SIZE_IEC_UNITS);
        vsz = g_format_size_full (task->vsz, G_FORMAT_SIZE_IEC_UNITS);
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           COL_TASK, task->name,
                           COL_PID, task->pid,
                           COL_RSS, rss,
                           COL_CPU, task->cpu_user,
                           COL_VSZ, vsz,

                           -1);


        //  array();
        */
/* append another row and fill in some data *//*


        */
/* ... and a third row *//*


    }
    //   g_array_free(tasks,TRUE);
    return GTK_TREE_MODEL (store);
}*/
