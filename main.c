#include <cairo.h>
#include <gtk/gtk.h>

#include <stdlib.h>
#include "memory_usage.h"
#include "cpu_usage.h"
#include "network_bandwith.h"
#include "interrupts.h"
#include "task_manager.h"
//#include "model.h"
#include "drawing.h"
#include "devices.h"


GtkWidget *menubar;
GtkWidget *filemenu;


struct Memory_usage memory_usage;
struct Cpu_usage cpu[4];
struct Network net;


/*static*/ gchar *track;

gboolean CPU0_line = TRUE;
gboolean CPU1_line = TRUE;
gboolean CPU2_line = TRUE;
gboolean CPU3_line = TRUE;


static guint t = 750;
static guint bjorg = 1;//prvi ispis
static guint bjorg2 = 1;


static guint time_step = 0;


void init_timeout2();

void timeout_refresh();

void measurements();





GtkWidget *closing(GtkWidget *widget) {

    GtkTreeModel *model;
    get_task_list(tasks);
    model = create_and_fill_model();
    g_array_free(tasks, TRUE);
    array();


    gtk_tree_view_set_model(GTK_TREE_VIEW (widget), model);
    g_object_unref(model);
    return widget;
};

void dev_button_clicked(GtkWidget *widget);

gchar memory_text[20] = "much memory";


//void cpu_percent_change();
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr) {


    if (widget == graph1) {

        do_drawing2(widget, cr, bjorg, time_step);
    }
    if (widget == graph2) {

        do_drawing(widget, cr, bjorg2);
    }
    if (widget == graph3) {

        do_drawing3(widget, cr, bjorg, time_step);
    }
    if (widget == graph4) {

        do_drawing4(widget, cr);
    }
return TRUE;

}

//void create_view_and_model_file_system(){
static GtkWidget *create_view_and_model_file_system() {


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

static GtkTreeModel *create_and_fill_model_file_system(void) {


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




void graph_refresh(GtkWidget *widget, gboolean CPU) {

    if (widget == button_graph0) {


        CPU0_line = CPU;


    }
    if (widget == button_graph1) {


        CPU1_line = CPU;


    }
    if (widget == button_graph2) {

        CPU2_line = CPU;

    }
    if (widget == button_graph3) {

        CPU3_line = CPU;
    }

    if (!g_source_remove(refresh)) {
        g_critical ("Unable to remove source");
        return;
    }
    refresh = 0;


    init_timeout();


};


static GtkWidget *create_view_and_model(void) {
    GtkCellRenderer *renderer;

    GtkWidget *view;
    GtkTreeViewColumn *column;
    column = gtk_tree_view_column_new();
    view = gtk_tree_view_new();
    g_object_set(column, COLUMN_PROPERTIES, NULL);

    //test
    //  column = gtk_tree_view_column_new ();
    renderer = gtk_cell_renderer_text_new();
    //gtk_tree_view_insert_column(GTK_TREE_VIEW (view),column,)
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                -1,
                                                "Task",
                                                renderer,
                                                "text", COL_TASK,
                                                NULL);

    //   --- Column #2 ---

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                -1,
                                                "PID",
                                                renderer,
                                                "text", COL_PID,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                -1,
                                                "RSS",
                                                renderer,
                                                "text", COL_RSS,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                -1,
                                                "CPU",
                                                renderer,
                                                "text", COL_CPU,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view),
                                                -1,
                                                "VSZ",
                                                renderer,
                                                "text", COL_VSZ,
                                                NULL);


    view = closing(view);


    return view;
};

GtkWidget *dev_problems(gboolean SHOW) {

    device(SHOW);
    /* GtkWidget **/ view2 = create_view_and_model_file_system();
//    swindow2 = gtk_scrolled_window_new(NULL,
//                                       NULL);
//    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(swindow2), GTK_POLICY_AUTOMATIC,
//                                   GTK_POLICY_ALWAYS);
//    gtk_box_pack_start(GTK_BOX(vbox), swindow2, TRUE, TRUE, 1);

    gtk_container_add(GTK_CONTAINER(swindow2), view2);



//izbrisati samo treba u dev_button da bude
    gtk_widget_show_all(swindow2);
    //  return view2;

};

void devices_change(GtkWidget *widget) {

    if(widget==show_all){
        dev_problems(TRUE);
    }

};

void dev_button_clicked(GtkWidget *widget) {

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (widget))) {

        gtk_container_remove(GTK_CONTAINER(swindow2),view2);
        dev_problems(FALSE);
        new_button_clicked(widget);

//          progressbar=gtk_progress_bar_new();
//          gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar),memory_used);
//          gtk_progress_bar_get_show_text (GTK_PROGRESS_BAR(progressbar));
//          gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar),"text here");
//          gtk_box_pack_start(GTK_BOX(vbox),progressbar,0,TRUE,0);
//          gtk_widget_show_all(progressbar);

        //  gtk_container_add(GTK_CONTAINER(swindow1), progressbar);

        gtk_widget_show_all(swindow2);
    } else {
        new_button_clicked(widget);
        // gtk_widget_destroy(progressbar);
        //   gtk_widget_unparent(view2);
        //gtk_widget_destroy(swindow2);
        //  gtk_widget_destroy(view2);
        gtk_widget_hide(swindow2);
        gtk_container_remove(GTK_CONTAINER(swindow2),view2);




    }
};
void clean_button(){
    //gtk_widget_unparent(view);
   // gtk_container_remove(GTK_CONTAINER(swindow1),view);
   //  process_tree();


}

static GtkTreeModel *create_and_fill_model(void) {


    store = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    gchar *rss, *vsz;
    gchar cpu[16], value[14];
    //get_task_list(tasks);
    //  Append a row and fill in some data

//    printf("TASKs-array : len: %d\n", tasks->len);

    for (int j = 0; j < tasks->len; j++) {
        Task *task = &g_array_index(tasks, Task, j);
        g_snprintf(value, 14, (more_precision) ? "%.2f" : "%.f", task->cpu_user + task->cpu_system);
     //   printf("value : %s index %d\n",value,j);
        g_snprintf(cpu, 16, ("%s%%"), value);
        rss = g_format_size_full(task->rss, G_FORMAT_SIZE_IEC_UNITS);
        vsz = g_format_size_full(task->vsz, G_FORMAT_SIZE_IEC_UNITS);


        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           COL_TASK, task->name,
                           COL_PID, task->pid,
                           COL_RSS, rss,
                           COL_CPU, cpu,
                           COL_VSZ, vsz,

                           -1);


        g_free(rss);
        g_free(vsz);


    }

//    g_array_free(tasks, TRUE);
    //  array();
    //
    return GTK_TREE_MODEL (store);

};

GtkWidget * process_tree() {
    GtkWidget *view;
  //  gtk_container_remove(GTK_CONTAINER(swindow1), view);
    view = create_view_and_model();


    gtk_container_add(GTK_CONTAINER(swindow1), view);
  //  gtk_container_remove(GTK_CONTAINER(swindow1),view);
    return view;
}

void button_clicked_view_process(GtkWidget *widget) {


static GtkWidget *view3;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (widget))) {
//        view = create_view_and_model();
//        swindow1 = gtk_scrolled_window_new(NULL,
//                                           NULL);
//        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(swindow1), GTK_POLICY_AUTOMATIC,
//                                       GTK_POLICY_ALWAYS);
//        gtk_box_pack_start(GTK_BOX(vbox), swindow1, TRUE, TRUE, 1);
//
//        gtk_container_add(GTK_CONTAINER(swin dow1), view);
        view3=process_tree();

        gtk_widget_show_all(swindow1);


    } else {


        /*gtk_widget_destroy(swindow1);
        gtk_container_remove(GTK_CONTAINER(vbox),swindow1);
        gtk_container_remove(GTK_CONTAINER(swindow1),view);

        gtk_widget_destroy(view);*/

        /*  g_signal_connect(G_OBJECT(window), "destroy",
                           G_CALLBACK(gtk_main_quit), NULL);*/
     //   gtk_widget_destroy(view);
        gtk_widget_hide(swindow1);
        gtk_container_remove(GTK_CONTAINER(swindow1),view3);


        /*g_signal_connect(G_OBJECT(view), "destroy",
                         G_CALLBACK(gtk_main_quit), NULL);*/
    }
}


void inc_refresh() {

    if (t >= 10000) {

        t = 10000;
    } else
        t += 250;

    timeout_refresh();


};

void dec_refresh() {


    if (t < 500) {
        t = 500;
        //  printf("promena refresh rate \n");
    } else
        t -= 250;
    //   printf("I clicked a button2 %d", t);
    timeout_refresh();


};

static gboolean time_handler(GtkWidget *widget) {

    gtk_widget_queue_draw(widget);

    return TRUE;
}


void timeout_refresh() {

    if (!g_source_remove(refresh)) {
        g_critical ("Unable to remove source");
        return;
    }
    refresh = 0;
    init_timeout();

}

void init_timeout2() {
    received_transfered();
    network_change_rc(label7);
    network_change_ts(label8);
    bjorg2++;

    if (bjorg2 >= 60) {


        bjorg2 = 60;
    }


}


void init_timeout() {


    cpu_percent_change(ncpu);//nije ovde
    get_memory_usage();//nije ovde
    // array_interrupts();
    interrupt_usage();



    /* cpu_change(label1);
     cpu_change(label3);
     cpu_change(label4);
     cpu_change(label5);
     cpu_change(label6);*/

    cpu_change(ncpu);
//    cpu_change2();
    memory_change(label);// nije ovde
    swap_change(label1); // nije ovde

    time_handler(window);
    bjorg++;

    //  closing();
    //   device();
    //  view2= dev_problems();
      process_tree();
   // gtk_container_remove(GTK_CONTAINER(swindow1),view);



    time_step = 60000 / t;

    if (bjorg >= time_step) {


        bjorg = time_step;
    }


    if (refresh == 0) {

        refresh = g_timeout_add(t, (GSourceFunc) init_timeout, NULL);
    }

};


void quit_activated() {
    g_print("File -> Quit activated...bye.\n");
    gtk_main_quit();
}

int main(int argc, char *argv[]) {


    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1400, 800);



    ncpu = cpu_number();

    interface_name();
    array_interrupts();
    //test
    array();
    array_devices();
    //  get_task_list(tasks);



    for (int i = 0; i < 8; i++) {
        history[i] = g_array_new(FALSE, TRUE, sizeof(gfloat));

    }
    for (int i = 0; i <= 3; i++) {

        g_array_set_size(history[i], 240);
    }
    for (int i = 4; i <= 5; i++) {

        g_array_set_size(history[i], 60);
    }
    for (int i = 6; i <= 7; i++) {


        g_array_set_size(history[i], 240);
    }

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);//cpu labels
    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);//graph1 graph2 frame1 frame2
    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);//izmedju graphova
    hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);//graph3 graph4 frame3 frame4

    button = gtk_button_new_with_label("refresh rate +");
    button2 = gtk_button_new_with_label("refresh rate-");
    button3 = gtk_toggle_button_new_with_label("Process");
    button4 = gtk_toggle_button_new_with_label("Dev");
    button5 = gtk_toggle_button_new_with_label("NEW");
    button_graph = gtk_toggle_button_new_with_label("graphs");

    menubar = gtk_menu_bar_new();
    filemenu = gtk_menu_new();
      filemenu2 = gtk_menu_new();
      filemenu3 = gtk_menu_new();

    speed = gtk_menu_item_new_with_label("speed");
    devices_menu = gtk_menu_item_new_with_label("devices");
    graph_menu = gtk_menu_item_new_with_label("graphs");

    increase_refresh = gtk_menu_item_new_with_label("+250");
    decrease_refresh = gtk_menu_item_new_with_label("-250");
    show_all = gtk_menu_item_new_with_label("All_file_systems");
  //  GtkWidget *graph_window=gtk_menu_item_new_with_label("graphs");
    GtkWidget *new = gtk_menu_item_new_with_label("return");
    GtkWidget *test = gtk_menu_item_new_with_label("flush");




    quit = gtk_menu_item_new_with_label("Quit");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(speed), filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), increase_refresh);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), decrease_refresh);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), speed);
  //  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), graph_menu);


   // gtk_menu_item_set_submenu(GTK_MENU_ITEM(graph_menu), filemenu3);

  //  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu3), graph_window);






    gtk_menu_item_set_submenu(GTK_MENU_ITEM(devices_menu), filemenu2);
      gtk_menu_shell_append(GTK_MENU_SHELL(filemenu2), show_all);
      gtk_menu_shell_append(GTK_MENU_SHELL(filemenu2), new);
      gtk_menu_shell_append(GTK_MENU_SHELL(filemenu2), test);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), devices_menu);


    g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(quit_activated), NULL);
    g_signal_connect(increase_refresh, "activate", G_CALLBACK(inc_refresh), NULL);
    g_signal_connect(decrease_refresh, "activate", G_CALLBACK(dec_refresh), NULL);
    g_signal_connect(show_all, "activate", G_CALLBACK(devices_change), NULL);
    g_signal_connect(new, "activate", G_CALLBACK(new_button_clicked2), NULL);
    g_signal_connect(test, "activate", G_CALLBACK(clean_button), NULL);
 //   g_signal_connect(graph_window, "activate", G_CALLBACK(graph_button_clicked), NULL);


    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);



    graph1 = gtk_drawing_area_new();
    graph2 = gtk_drawing_area_new();
    graph3 = gtk_drawing_area_new();
    graph4 = gtk_drawing_area_new();

    frame1 = gtk_frame_new(NULL);
    frame2 = gtk_frame_new(NULL);
    frame3 = gtk_frame_new(NULL);
    frame4 = gtk_frame_new(NULL);


    label = gtk_label_new(NULL);//memory
    label1 = gtk_label_new(NULL);//swap
    label3 = gtk_label_new(NULL);//cpu1
    label4 = gtk_label_new(NULL);//cpu2
    label5 = gtk_label_new(NULL);//cpu3
    label6 = gtk_label_new(NULL);//cpu4
    label7 = gtk_label_new(NULL);//network_received
    label8 = gtk_label_new(NULL);//network_transimited
    swindow2 = gtk_scrolled_window_new(NULL,
                                       NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(swindow2), GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_ALWAYS);

    swindow1 = gtk_scrolled_window_new(NULL,
                                       NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(swindow1), GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_ALWAYS);


    gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, FALSE);//expand,fill,padding
    gtk_box_pack_start(GTK_BOX(hbox), button2, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button3, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button5, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button4, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button_graph, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), label3, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), label4, 0, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox), label5, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), label6, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), label8, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(hbox), label7, 1, TRUE, 1);



    gtk_box_pack_start(GTK_BOX(vbox), hbox1, 1, 1, 0);


    gtk_container_add(GTK_CONTAINER(frame1), graph1);
    gtk_box_pack_start(GTK_BOX(hbox1), frame1, 1, TRUE, 0);


    gtk_box_pack_start(GTK_BOX(vbox), hbox2, 0, FALSE, 0);

  //  gtk_box_pack_start(GTK_BOX(hbox2), button4, 0, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), label, 0, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), label1, 0, FALSE, 1);
//    gtk_box_pack_start(GTK_BOX(hbox2), label8, 1, 0, 1);
//    gtk_box_pack_start(GTK_BOX(hbox2), label7, 1, TRUE, 1);



    gtk_container_add(GTK_CONTAINER(frame2), graph2);
    gtk_box_pack_start(GTK_BOX(hbox1), frame2, 1, TRUE, 0);

  //  hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

    gtk_box_pack_start(GTK_BOX(vbox), hbox3, 1, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(frame3), graph3);
    gtk_container_add(GTK_CONTAINER(frame4), graph4);
    gtk_box_pack_start(GTK_BOX(hbox3), frame3, 1, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox3), frame4, 1, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), swindow2, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), swindow1, TRUE, TRUE, 1);

//process_tree();

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(button, "clicked", G_CALLBACK(inc_refresh), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(dec_refresh), NULL);
    g_signal_connect(button3, "toggled", G_CALLBACK(button_clicked_view_process), NULL);
    g_signal_connect(button4, "toggled", G_CALLBACK(dev_button_clicked), NULL);
    g_signal_connect(button5, "toggled", G_CALLBACK(new_button_clicked), NULL);
    g_signal_connect(button_graph, "clicked", G_CALLBACK(graph_button_clicked), NULL);


    g_signal_connect(G_OBJECT(graph1), "draw",
                     G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(G_OBJECT(graph2), "draw",
                     G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(G_OBJECT(graph3), "draw",
                     G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(G_OBJECT(graph4), "draw",
                     G_CALLBACK(on_draw_event), NULL);



    g_timeout_add(1000, (GSourceFunc) init_timeout2, NULL);



    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_window_set_title(GTK_WINDOW(window), "lines mother do you see it ");

    init_timeout();



    gtk_widget_show_all(window);


    gtk_widget_hide(swindow2);
  // gtk_widget_hide(swindow1);


    gtk_main();


    return 0;
}
