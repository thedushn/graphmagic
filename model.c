
//
// Created by dushn on 12.9.17..
//

#include "model.h"
#include "main_header.h"
#include "devices.h"
 GtkWidget *create_view_and_model_file_system() {


    GtkCellRenderer *renderer;
    GtkTreeModel *model;
    GtkWidget *view;
//    GtkTreeViewColumn *column;
//    column = gtk_tree_view_column_new ();
    view = gtk_tree_view_new();
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                -1,
                                                "Device",
                                                renderer,
                                                "text", COL_DEV,
                                                NULL);

    //   --- Column #2 ---

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                -1,
                                                "Directory",
                                                renderer,
                                                "text", COL_DIR,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                -1,
                                                "Type",
                                                renderer,
                                                "text", COL_TYPE,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                -1,
                                                "Total",
                                                renderer,
                                                "text", COL_TOTAL,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                -1,
                                                "Available",
                                                renderer,
                                                "text", COL_AVAILABLE,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                -1,
                                                "Used",
                                                renderer,
                                                "text", COL_USED,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                -1,
                                                "Free",
                                                renderer,
                                                "text", COL_FREE,
                                                NULL);

  //  device();
    model = create_and_fill_model_file_system();


    gtk_tree_view_set_model(GTK_TREE_VIEW (view), model);

//     The tree view has acquired its own reference to the
//     *  model, so we can drop ours. That way the model will
//     *  be freed automatically when the tree view is destroyed

    g_array_free(names, TRUE);
    array_devices();

    g_object_unref(model);


    return view;

}

 GtkTreeModel *create_and_fill_model_file_system(void) {


    store = gtk_list_store_new(NUM_COLS_DEV, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    gchar *total, *avail, *used, *free;

    for (int j = 0; j < names->len; j++) {
        Devices *devices = &g_array_index(names, Devices, j);
        used = g_format_size_full((guint64) devices->used, G_FORMAT_SIZE_IEC_UNITS);
        total = g_format_size_full((guint64) devices->total, G_FORMAT_SIZE_IEC_UNITS);
        avail = g_format_size_full((guint64) devices->avail, G_FORMAT_SIZE_IEC_UNITS);
        free = g_format_size_full((guint64) devices->free, G_FORMAT_SIZE_IEC_UNITS);
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           COL_DEV, devices->name,
                           COL_DIR, devices->directory,
                           COL_TYPE, devices->type,
                           COL_TOTAL, total,
                           COL_AVAILABLE, avail,
                           COL_USED, used,
                           COL_FREE, free,


                           -1);

        printf(" Final Directory: %s Device: %s used %lu total %lu free %lu type %s available %lu\n",
               devices->directory,
               devices->name,
               devices->used,
               devices->total,
               devices->free,
               devices->type,
               devices->avail);

        g_free(used);
        g_free(total);
        g_free(avail);
        g_free(free);


    }


    return GTK_TREE_MODEL (store);

};

