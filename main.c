#include <cairo.h>
#include <gtk/gtk.h>

#include <stdlib.h>
//#include "memory_usage.h"
#include "cpu_usage.h"
#include "network_bandwith.h"
#include "interrupts.h"
#include "task_manager.h"
//#include "model.h"
#include "drawing.h"
#include "devices.h"
#include "process-tree-view.h"
#include "task-manager.h"

#include "settings.h"
#include "process-window.h"
#include "task-manager.h"


GtkWidget *menubar;
GtkWidget *filemenu;

static XtmSettings *settings;
static GtkWidget *window;
static GtkStatusIcon *status_icon;
static XtmTaskManager *task_manager;
GtkTreeStore *list_store;



//struct Memory_usage memory_usage;
struct Cpu_usage cpu[4];
struct Network net;



/*static*/ gchar *track;
void  array(){

    tasks=g_array_new (FALSE, FALSE, sizeof (Task));
}
gboolean CPU0_line = TRUE;
gboolean CPU1_line = TRUE;
gboolean CPU2_line = TRUE;
gboolean CPU3_line = TRUE;


static guint t = 1000;
static guint bjorg = 1;//prvi ispis
static guint bjorg2 = 1;


static guint time_step = 0;
static void
show_hide_status_icon (void)
{
    gboolean show_status_icon;
    g_object_get (settings, "show-status-icon", &show_status_icon, NULL);
    gtk_status_icon_set_visible (status_icon, show_status_icon);
}

void remove_list_item(gint pid)
{
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(list_store), &iter);

    while(valid)
    {
        gchar *str_data = "";
        gtk_tree_model_get(GTK_TREE_MODEL(list_store), &iter, 1, &str_data, -1);

        if(pid == atoi(str_data))
        {
            g_free(str_data);
            gtk_tree_store_remove(GTK_TREE_STORE(list_store), &iter);
            break;
        }

        g_free(str_data);
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(list_store), &iter);
    }
}
static void
status_icon_activated (void)
{
    if (!(gtk_widget_get_visible (window)))
        gtk_widget_show (window);
    else
        gtk_widget_hide (window);
}

void init_timeout2();

void timeout_refresh();

void measurements();



static void
status_icon_popup_menu (GtkStatusIcon *_status_icon, guint button, guint activate_time)
{
    static GtkWidget *menu = NULL;

    if (menu == NULL)
    {
        GtkWidget *mi;
        menu = gtk_menu_new ();
        mi = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, NULL);
        g_signal_connect (mi, "activate", G_CALLBACK (gtk_main_quit), NULL);
        gtk_container_add (GTK_CONTAINER (menu), mi);
        gtk_widget_show_all (menu);
    }

    gtk_menu_popup (GTK_MENU (menu), NULL, NULL, gtk_status_icon_position_menu, _status_icon, button, activate_time);
}

GtkWidget *closing(GtkWidget *widget) {

    GtkTreeModel *model;
    get_task_list(tasks);
    model = create_and_fill_model();
   // model=  xtm_process_tree_view_get_model(XTM_PROCESS_TREE_VIEW(widget));
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
  //  GtkWidget *view_dev;
//    GtkTreeViewColumn *column;
//    column = gtk_tree_view_column_new ();
    view_dev = gtk_tree_view_new();
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view_dev),
                                                -1,
                                                "Device",
                                                renderer,
                                                "text", COL_DEV,
                                                NULL);

    //   --- Column #2 ---

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view_dev),
                                                -1,
                                                "Directory",
                                                renderer,
                                                "text", COL_DIR,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view_dev),
                                                -1,
                                                "Type",
                                                renderer,
                                                "text", COL_TYPE,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view_dev),
                                                -1,
                                                "Total",
                                                renderer,
                                                "text", COL_TOTAL,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view_dev),
                                                -1,
                                                "Available",
                                                renderer,
                                                "text", COL_AVAILABLE,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view_dev),
                                                -1,
                                                "Used",
                                                renderer,
                                                "text", COL_USED,
                                                NULL);
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW (view_dev),
                                                -1,
                                                "Free",
                                                renderer,
                                                "text", COL_FREE,
                                                NULL);

  //  device();
    model = create_and_fill_model_file_system();


    gtk_tree_view_set_model(GTK_TREE_VIEW (view_dev), model);

//     The tree view has acquired its own reference to the
//     *  model, so we can drop ours. That way the model will
//     *  be freed automatically when the tree view is destroyed

    g_array_free(names, TRUE);
    array_devices();

    g_object_unref(model);


    return view_dev;

}

static GtkTreeModel *create_and_fill_model_file_system(void) {
    GtkListStore  *store;

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
void clean_button(){
   // gtk_widget_unparent(view2);
  //
    if(view2==NULL){


    }
    else{


        gtk_container_remove(GTK_CONTAINER(dev_swindow),view2);
        view2=NULL;
    }
   // gtk_container_remove(GTK_CONTAINER(dev_swindow),view2);

   // view2=NULL;

//    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (button4))) {
//
//        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button4),FALSE);
//    }

}



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
    //column = gtk_tree_view_column_new();
    view = gtk_tree_view_new();
   // g_object_set(column, COLUMN_PROPERTIES, NULL);

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

//void dev_problems2(gboolean show) {
//    //  view2=NULL;
//    device(show);
//    printf("why timmy\n");
//    if(view2!=NULL){
//        printf("pokusaj remove\n");
//        // gtk_widget_unparent(view2);
//         gtk_container_remove(GTK_CONTAINER(dev_swindow),view2);
//
//    }
//
//    if(view2==NULL){
//
//        printf("how the fuck ");
//
//    }
//    view2=NULL;
//    view2 = create_view_and_model_file_system();
//
//
//    gtk_container_add(GTK_CONTAINER(dev_swindow), view2);
//
//
//
//    //  return view2;
//
//};
void dev_problems(gboolean show,GtkWidget *window) {
  //  view2=NULL;
    GtkWidget *view_dev;
    GtkTreeModel *model;
  //  device(show);
    printf("why timmy\n");
//    if(view2!=NULL){
//        printf("pokusaj remove\n");
//      // gtk_widget_unparent(view2);
//       // gtk_container_remove(GTK_CONTAINER(dev_swindow),view2);
//
//    }
//
//    if(view2==NULL){
//
//        printf("how the fuck ");
//
//    }
  //  view2=NULL;
    view2=NULL;
  // view = create_view_and_model_file_system();
  // view_dev = create_view_and_model_file_system();
   // xtm_task_manager_update_model (task_manager);
   
   // view_dev=  xtm_process_tree_view_new();


    view_dev= xtm_process_tree_view_new ();
    view_dev=closing(view_dev);





   // gtk_container_add(GTK_CONTAINER(dev_swindow), view2);
    gtk_container_add(GTK_CONTAINER(window), view_dev);





};

void devices_change(GtkWidget *widget) {

    if(widget==show_all){
        clean_button();
     //   dev_problems(TRUE);
        gtk_widget_show_all(dev_swindow);
    }

};
gboolean refresh_dev(){

    device(FALSE);

return TRUE;
};
void dev_button_clicked2(GtkWidget *widget){



    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (widget))) {

        pokazi_ili_hide(widget, dev_swindow);

      dev_problems(TRUE,dev_swindow);


        gtk_widget_show_all(dev_swindow);
       // g_timeout_add(1000, (GSourceFunc)refresh_dev(),NULL);
    } else {
        pokazi_ili_hide(widget, dev_swindow);

        GList *children=  gtk_container_get_children(GTK_CONTAINER(dev_swindow));

        // gtk_widget_destroy(progressbar);
        //  gtk_widget_unparent(children->data);
        gtk_container_remove(GTK_CONTAINER(dev_swindow),children->data);
        //gtk_widget_destroy(swindow2);
        //    gtk_widget_destroy(dev_swindow);
        //pokazi_ili_hide(widget);
        //   gtk_widget_hide(dev_swindow);
        //    clean_button();
        //   gtk_container_remove(GTK_CONTAINER(swindow2),view2);




    }

}
void dev_button_clicked(GtkWidget *widget) {

// GtkWidget *   dev_swindow = gtk_scrolled_window_new(NULL,
//                                          NULL);
//    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(dev_swindow), GTK_POLICY_AUTOMATIC,
//                                   GTK_POLICY_ALWAYS);

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (widget))) {

        pokazi_ili_hide(widget, dev_swindow);
     //   gtk_container_remove(GTK_CONTAINER(swindow2),view2);
       view2=NULL;
       // clean_button();
        dev_problems(FALSE,dev_swindow);
       // pokazi_ili_hide(widget);

//          progressbar=gtk_progress_bar_new();
//          gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar),memory_used);
//          gtk_progress_bar_get_show_text (GTK_PROGRESS_BAR(progressbar));
//          gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar),"text here");
//          gtk_box_pack_start(GTK_BOX(vbox),progressbar,0,TRUE,0);
//          gtk_widget_show_all(progressbar);

        //  gtk_container_add(GTK_CONTAINER(process_swindow), progressbar);

        gtk_widget_show_all(dev_swindow);
    } else {
        pokazi_ili_hide(widget, dev_swindow);

        GList *children=  gtk_container_get_children(GTK_CONTAINER(dev_swindow));

        // gtk_widget_destroy(progressbar);
         //  gtk_widget_unparent(children->data);
        gtk_container_remove(GTK_CONTAINER(dev_swindow),children->data);
        //gtk_widget_destroy(swindow2);
      //    gtk_widget_destroy(dev_swindow);
        //pokazi_ili_hide(widget);
     //   gtk_widget_hide(dev_swindow);
    //    clean_button();
     //   gtk_container_remove(GTK_CONTAINER(swindow2),view2);




    }
};


static GtkTreeModel *create_and_fill_model(void) {
    GtkListStore  *store;

store=    gtk_list_store_new (XTM_PTV_N_COLUMNS, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_UINT64,
                        G_TYPE_STRING, G_TYPE_UINT64, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_FLOAT, G_TYPE_STRING, G_TYPE_INT,
                        G_TYPE_STRING, G_TYPE_STRING, G_TYPE_LONG);
  //  store = gtk_list_store_new(NUM_COLS, G_TYPE_STRING, G_TYPE_UINT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
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
//        gtk_list_store_set(store, &iter,
//                           COL_TASK, task->name,
//                           COL_PID, task->pid,
//                           COL_RSS, rss,
//                           COL_CPU, cpu,
//                           COL_VSZ, vsz,
//
//                           -1);

        gtk_list_store_set (store, &iter,
                            XTM_PTV_COLUMN_PRIORITY, task->prio,
                            XTM_PTV_COLUMN_COMMAND,task->name,
                            XTM_PTV_COLUMN_PID,task->pid,
                            XTM_PTV_COLUMN_PPID, task->ppid,
                            XTM_PTV_COLUMN_STATE, task->state,
                            XTM_PTV_COLUMN_VSZ, task->vsz,
                            XTM_PTV_COLUMN_VSZ_STR, vsz,
                            XTM_PTV_COLUMN_RSS, task->rss,
                            XTM_PTV_COLUMN_RSS_STR, rss,
                            XTM_PTV_COLUMN_UID,task->uid,


                            XTM_PTV_COLUMN_CPU, task->cpu_user + task->cpu_system,
                            XTM_PTV_COLUMN_CPU_STR, cpu,


                            -1);


        g_free(rss);
        g_free(vsz);


    }

//    g_array_free(tasks, TRUE);
    //  array();
    //
    return GTK_TREE_MODEL (store);

};
//GtkWidget* process_tree() {
void process_tree() {
   // GtkWidget *view;
  //  gtk_container_remove(GTK_CONTAINER(process_swindow), view);

    if(view==NULL){

        printf("why the fuck ");
    }
    if(view!=NULL){

        gtk_container_remove(GTK_CONTAINER(process_swindow),view);
    }
    view = create_view_and_model();



   // gtk_container_remove(GTK_CONTAINER(process_swindow),view);
    gtk_container_add(GTK_CONTAINER(process_swindow),view);
    gtk_widget_show(process_swindow);

//    GtkWidget* child = find_child(vbox, "process_swindow");
//    if (child == process_swindow) {
//        g_print("found it!\n");
//    } else {
//        g_print("not found it!\n");
//    }
  //  gtk_container_remove(GTK_CONTAINER(process_swindow),view);

};

//GtkWidget*
//find_child(GtkWidget* parent, const gchar* name)
//{
//    if (g_strcasecmp(gtk_widget_get_name((GtkWidget*)parent), (gchar*)name) == 0) {
//        return parent;
//    }
//
//    if (GTK_IS_BIN(parent)) {
//        GtkWidget *child = gtk_bin_get_child(GTK_BIN(parent));
//        return find_child(child, name);
//    }
//
//    if (GTK_IS_CONTAINER(parent)) {
//        GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
//        while ((children = g_list_next(children)) != NULL) {
//            GtkWidget* widget = find_child(children->data, name);
//            printf("name %s\n",name);
//            if (widget != NULL) {
//                return widget;
//            }
//        }
//    }
//
//    return NULL;
//}
void button_clicked_view_process(GtkWidget *widget) {




    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (widget))) {

        pokazi_ili_hide(widget, process_swindow);
        process_tree();

        gtk_widget_show_all(process_swindow);


    } else {


        pokazi_ili_hide(widget, process_swindow);
        /*gtk_widget_destroy(process_swindow);
        gtk_container_remove(GTK_CONTAINER(vbox),process_swindow);
        gtk_container_remove(GTK_CONTAINER(process_swindow),view);

        gtk_widget_destroy(view);*/

        /*  g_signal_connect(G_OBJECT(window), "destroy",
                           G_CALLBACK(gtk_main_quit), NULL);*/
     //   gtk_widget_destroy(view);
       // gtk_widget_hide(process_swindow);
      //  gtk_widget_unparent(testing);
        //   gtk_container_remove(GTK_CONTAINER(process_swindow),view3);

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
void fill_list_item(gint i, GtkTreeIter *iter)
{






    if(iter != NULL)
    {
        Task *task = &g_array_index(task_array, Task, i);
     gchar cpu[16], value[14];
//
        gchar *rss, *vsz;
        rss = g_format_size_full(task->rss, G_FORMAT_SIZE_IEC_UNITS);
        vsz = g_format_size_full(task->vsz, G_FORMAT_SIZE_IEC_UNITS);
//
        g_snprintf(value, 14, (more_precision) ? "%.2f" : "%.f", task->cpu_user + task->cpu_system);
        printf("cpu_user %d cpu_system %d \n ",task->cpu_user,task->cpu_system);
        g_snprintf(cpu, 16, ("%s%%"), value);
        gchar *pid = g_strdup_printf("%i", task->pid);
        gchar *ppid = g_strdup_printf("%i", task->ppid);
        gchar *state = g_strdup_printf("%s", task->state);
      //  gchar *size = g_strdup_printf("%i kB", task->vsz);
     //   gchar *rss = g_strdup_printf("%i kB", task->rss);
        gchar *name = g_strdup_printf("%s", task->name);
        gchar *uname = g_strdup_printf("%s", task->uid_name);
      //  gchar *time = g_strdup_printf("%0d%%", (guint)task->time_percentage);

        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COLUMN_NAME, name, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COLUMN_PID, pid, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COLUMN_PPID, ppid, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COLUMN_STATE, state, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COLUMN_MEM, vsz, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COLUMN_RSS, rss, -1);

       // gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COLUMN_TIME, time, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COLUMN_CPU, cpu, -1);
        gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COLUMN_UNAME, uname, -1);
     //   gtk_tree_store_set(GTK_TREE_STORE(list_store), iter, COLUMN_CPU2, cpu, -1);

        g_free(pid);
        g_free(ppid);
        g_free(state);
       // g_free(size);

        g_free(name);
        g_free(uname);
      //  g_free(time);
        g_free(rss);
        g_free(vsz);
    }
}



void send_signal_to_task(gchar *task_id, gchar *signal)
{
    if(task_id != "" && signal != NULL)
    {
        gchar command[64] = "kill -";
        g_strlcat(command,signal, sizeof command);
        g_strlcat(command," ", sizeof command);
        g_strlcat(command,task_id, sizeof command);

//        if(system(command) != 0)
//            xfce_err("Couldn't %s the task with ID %s", signal, task_id);
    }
}


void add_new_list_item(gint i)
{
    GtkTreeIter iter;

    gtk_tree_store_append(GTK_TREE_STORE(list_store), &iter, NULL);

    fill_list_item(i, &iter);
}

void refresh_list_item(gint i)
{
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(list_store), &iter);
    Task *task = &g_array_index(task_array, Task, i);
    while(valid)
    {
        gchar *str_data = "";
        gtk_tree_model_get(GTK_TREE_MODEL(list_store), &iter, 1, &str_data, -1);

        if(task->pid == atoi(str_data))
        {
            g_free(str_data);
            fill_list_item(i, &iter);
            break;
        }

        g_free(str_data);
        valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(list_store), &iter);
    }
}
void change_list_store_view(void)
{
    gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), COLUMN_PPID), full_view);
    gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), COLUMN_MEM), full_view);
    gtk_tree_view_column_set_visible (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), COLUMN_RSS), full_view);
}
gint compare_int_list_item(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column)
{
    gchar *s1 = "";
    gchar *s2 = "";

    gint ret = 0;

    gtk_tree_model_get(model, iter1, column, &s1, -1);
    gtk_tree_model_get(model, iter2, column, &s2, -1);

    gint i1 = 0;
    gint i2 = 0;

    if(s1 != NULL)
        i1 = atoi(s1);

    if(s2 != NULL)
        i2 = atoi(s2);

    ret = i1 - i2;

    if(s1 != NULL)
        g_free(s1);
    if(s2 != NULL)
        g_free(s2);

    return ret;
}

gint compare_string_list_item(GtkTreeModel *model, GtkTreeIter *iter1, GtkTreeIter *iter2, gpointer column)
{
    gchar *s1 = "";
    gchar *s2 = "";

    gint ret = 0;

    gtk_tree_model_get(model, iter1, GPOINTER_TO_INT(column), &s1, -1);
    gtk_tree_model_get(model, iter2, GPOINTER_TO_INT(column), &s2, -1);

    if(s1 != NULL && s2 != NULL)
        ret = strcmp(s1, s2);
    else
        ret = 0;

    if(s1 != NULL)
        g_free(s1);
    if(s2 != NULL)
        g_free(s2);

    return ret;
}
GtkTreeStore * create_list_store(void)
{
    GtkCellRenderer *cell_renderer;

    list_store = gtk_tree_store_new(8, G_TYPE_STRING, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

    cell_renderer = gtk_cell_renderer_text_new();

    column = gtk_tree_view_column_new_with_attributes(("Command"), cell_renderer, "text", 0, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, 0);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), 0, compare_string_list_item, (void *)0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("PID"), cell_renderer, "text", 1, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, 1);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), 1, compare_int_list_item, (void *)1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("PPID"), cell_renderer, "text", 2, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, 2);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), 2, compare_string_list_item, (void *)2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("State"), cell_renderer, "text", 3, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, 3);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), 3, compare_int_list_item, (void *)3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("VM-Size"), cell_renderer, "text", 4, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, 4);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), 4, compare_int_list_item, (void *)4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("RSS"), cell_renderer, "text", 5, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, 5);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), 5, compare_int_list_item, (void *)5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("User"), cell_renderer, "text", 6, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, 6);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), 6, compare_string_list_item, (void *)6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes(("CPU%"), cell_renderer, "text", 7, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sort_column_id(column, 7);
    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), 7, compare_int_list_item, (void *)7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

//    column = gtk_tree_view_column_new_with_attributes(("CPU2%"), cell_renderer, "text", 8, NULL);
//    gtk_tree_view_column_set_resizable(column, TRUE);
//    gtk_tree_view_column_set_sort_column_id(column, 8);
//    gtk_tree_sortable_set_sort_func(GTK_TREE_SORTABLE(list_store), 8, compare_int_list_item, (void *)8, NULL);
//    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    change_list_store_view();
    return list_store;
}

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

    gint i,j;
   // gchar *cpu_tooltip, *mem_tooltip;
    gdouble cpu_usage;
    guint num_cpus;
    guint memory_used;
    cpu_percent_change(ncpu);//nije ovde
    //get_memory_usage();//nije ovde
    // array_interrupts();
    interrupt_usage();
GArray *new_task_list;
    new_task_list =  get_task_list2();


    // names_temp=g_array_new (FALSE, FALSE, sizeof (Devices));
//    new_task_list= tasks;
//    get_task_list(tasks);


   // printf("temp_process len %d\n",new_task_list->len);
   // printf("tasks len %d\n",tasks->len);
    for(i = 0; i < task_array->len; i++)
    {
       Task *tmp = &g_array_index(task_array, Task, i);
        tmp->checked = FALSE;
            printf("%s\n",tmp->name);
        for(j = 0; j < new_task_list->len; j++)
        {
            Task *new_tmp = &g_array_index(new_task_list, Task, j);

            if(new_tmp->pid == tmp->pid)
            {
//                tmp->old_time = tmp->time;
//
//                tmp->time = new_tmp->time;
//
//                tmp->time_percentage = (gdouble)(tmp->time - tmp->old_time) * (gdouble)(1000.0 / (REFRESH_INTERVAL*num_cpus));
                if((gint)tmp->ppid != (gint)new_tmp->ppid || strcmp(tmp->state,new_tmp->state) ||
                        (unsigned int)tmp->cpu_system != (unsigned int)new_tmp->cpu_system ||
                        (unsigned int)tmp->cpu_user != (unsigned int)new_tmp->cpu_user ||
                        (unsigned int)tmp->rss != (unsigned int)new_tmp->rss) //||
                       // (unsigned int)tmp->time != (unsigned int)tmp->old_time)
                {
                    tmp->ppid = new_tmp->ppid;
                    strcpy(tmp->state, new_tmp->state);
                    tmp->cpu_user = new_tmp->cpu_user;
                    tmp->cpu_system = new_tmp->cpu_system;
                    tmp->rss = new_tmp->rss;

                    refresh_list_item(i);
                }
                tmp->checked = TRUE;
                new_tmp->checked = TRUE;
                break;
            }
            else
                tmp->checked = FALSE;
        }
    }

    /* check for unchecked old-tasks for deleting */
    i = 0;
    while( i < task_array->len)
    {

       Task *tmp = &g_array_index(task_array, Task, i);

        if(!tmp->checked)
        {
            remove_list_item((gint)tmp->pid);
            g_array_remove_index(task_array, i);
            tasks_num--;
        }
        else
            i++;

    }


    /* check for unchecked new tasks for inserting */
    for(i = 0; i < new_task_list->len; i++)
    {
        Task *new_tmp = &g_array_index(new_task_list, Task, i);

        if(!new_tmp->checked)
        {
            Task *new_task = new_tmp;

            g_array_append_val(task_array, *new_task);
         //   if(( new_task->uid == own_uid))
                add_new_list_item(tasks_num);
            tasks_num++;
        }
    }




//    for(int i=0 ;i<tasks->len;i++){
//
//        GtkTreeIter iter;
//        printf("%d \n",i);
//        gtk_tree_store_append(GTK_TREE_STORE(list_store), &iter, NULL);
//        fill_list_item(i, &iter);
//    }



   g_array_free(new_task_list, TRUE);
//   g_array_free(tasks, FALSE);
//    array();


//dev_problems2(FALSE);
   // gtk_container_remove(GTK_CONTAINER(swindow2),view2);
    /* cpu_change(label1);
     cpu_change(label3);
     cpu_change(label4);
     cpu_change(label5);
     cpu_change(label6);*/

    cpu_change(ncpu);
//    cpu_change2();
 //   memory_change(label);// nije ovde
  //  swap_change(label1); // nije ovde

    time_handler(window);
    bjorg++;

  // get_task_list(tasks);


    //   device();
    //  view2= dev_problems();

   // gtk_container_remove(GTK_CONTAINER(process_swindow),view);




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
    dev_swindow = gtk_scrolled_window_new(NULL,
                                          NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(dev_swindow), GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_ALWAYS);
    process_swindow = gtk_scrolled_window_new(NULL,
                                              NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(process_swindow), GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_ALWAYS);


    ncpu = cpu_number();

    interface_name();
    array_interrupts();
    //test
    array();
    array_devices();
    //  get_task_list(tasks);
    tasks_num=0;
    task_array=g_array_new (FALSE, FALSE, sizeof (Task));

   // names_temp=g_array_new (FALSE, TRUE, sizeof (Devices));
    names_temp=g_array_new (FALSE, FALSE, sizeof (Devices));
    // names_temp=g_array_new (TRUE, FALSE, sizeof (Devices));

    for (int i = 0; i < 8; i++) {
        history[i] = g_array_new(FALSE, TRUE, sizeof(gfloat));

    }
    for (int i = 0; i <= 3; i++) {

        g_array_set_size(history[i], 240);//max steps 
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
    button_dev = gtk_toggle_button_new_with_label("Dev2");
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
   // g_signal_connect(show_all, "activate", G_CALLBACK(devices_change), NULL);
    g_signal_connect(new, "activate", G_CALLBACK(new_button_clicked2), NULL);
    g_signal_connect(test, "activate", G_CALLBACK(clean_button), NULL);
 //   g_signal_connect(graph_window, "activate", G_CALLBACK(graph_button_clicked), NULL);

    treeview = gtk_tree_view_new ();
    gtk_widget_show (treeview);



    GtkTreeStore *list_store =create_list_store();

//    for(int i=0 ;i<tasks->len;i++){
//
//        GtkTreeIter iter;
//        printf("%d \n",i);
//        gtk_tree_store_append(GTK_TREE_STORE(list_store), &iter, NULL);
//        fill_list_item(i, &iter);
//    }
//
//    for(int i=0 ;i<tasks->len;i++){
//        printf("i %d",i);
//        add_new_list_item(i);
//    }

    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(list_store));

    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(list_store), 1, GTK_SORT_ASCENDING);
    gtk_container_add(GTK_CONTAINER(dev_swindow),treeview);

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



    gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, FALSE);//expand,fill,padding
    gtk_box_pack_start(GTK_BOX(hbox), button2, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button3, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button5, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button4, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button_dev, 0, 0, 0);
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

    gtk_box_pack_start(GTK_BOX(vbox), dev_swindow, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(vbox), process_swindow, TRUE, TRUE, 1);

//process_tree();

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(button, "clicked", G_CALLBACK(inc_refresh), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(dec_refresh), NULL);
    g_signal_connect(button3, "toggled", G_CALLBACK(button_clicked_view_process), NULL);
    g_signal_connect(button4, "toggled", G_CALLBACK(dev_button_clicked), NULL);
    g_signal_connect(button_dev, "toggled", G_CALLBACK(dev_button_clicked2), NULL);
    g_signal_connect(button5, "toggled", G_CALLBACK(pokazi_ili_hide), NULL);
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


   // gtk_widget_hide(dev_swindow);
   gtk_widget_hide(process_swindow);


    gtk_main();


    return 0;
}
