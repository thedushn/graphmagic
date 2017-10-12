#include "cpu_usage.h"
#include "network_bandwith.h"
#include "interrupts.h"
#include "task_manager.h"
#include "process-tree-view.h"
#include "drawing.h"

//
//#include "task-manager.h"
//
//#include "process-window.h"
#include "testing_tree.h"
#include "memory_usage.h"
#include "window.h"




//static XtmSettings *settings;
//static GtkWidget *window;
//static GtkStatusIcon *status_icon;
//static XtmTaskManager *task_manager;




//struct Memory_usage memory_usage;
struct Cpu_usage cpu[4];
struct Network net;


gboolean CPU0_line = TRUE;
gboolean CPU1_line = TRUE;
gboolean CPU2_line = TRUE;
gboolean CPU3_line = TRUE;

gchar *track;
//void  array(){
//
//    tasks=g_array_new (FALSE, FALSE, sizeof (Task));
//};





void init_timeout2();

void timeout_refresh();

void measurements();




GtkWidget *closing(GtkWidget *widget) {

    GtkTreeModel *model;
    get_task_list(tasks);
    model = create_and_fill_model();
   // model=  xtm_process_tree_view_get_model(XTM_PROCESS_TREE_VIEW(widget));
    g_array_free(tasks, TRUE);
   // array();


    gtk_tree_view_set_model(GTK_TREE_VIEW (widget), model);
    g_object_unref(model);
    return widget;
};



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
    device(show);
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
   view = create_view_and_model_file_system();
   // view_dev = create_view_and_model_file_system();
   // xtm_task_manager_update_model (task_manager);
   
    view_dev=  xtm_process_tree_view_new();


//    view_dev= xtm_process_tree_view_new ();
    view_dev=closing(view_dev);





//    gtk_container_add(GTK_CONTAINER(dev_swindow), view2);
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

  //  gtk_container_remove(GTK_CONTAINER(process_swindow),view);

};

void button_clicked_view_process(GtkWidget *widget) {




    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (widget))) {

        pokazi_ili_hide(widget, process_swindow);
     //   process_tree();

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
    get_memory_usage();//nije ovde
    // array_interrupts();
    interrupt_usage();
GArray *new_task_list;
    GArray *new_device_list;
    new_task_list =  get_task_list2();
    new_device_list   = device(FALSE);

 //   printf("names lenght %d \n",new_device_list->len);
   // printf("names lenght %d \n",new_device_list->len);

    for(i = 0; i < names_array->len; i++)
    {
        Devices *tmp = &g_array_index(names_array, Devices, i);
        tmp->checked = FALSE;
        // printf("%s\n",tmp->name);
        for(j = 0; j < new_device_list->len; j++)
        {
            Devices *new_tmp = &g_array_index(new_device_list, Devices, j);

            if(strcmp(new_tmp->name, tmp->name)==0)
            {

                if((gint)tmp->avail != (gint)new_tmp->avail
                  /* || strcmp(tmp->used,new_tmp->used)*/ ||
                    strcmp(tmp->type,new_tmp->type)!=0 ||
                    strcmp(tmp->directory,new_tmp->directory)!=0 ||
                   (unsigned int)tmp->used != (unsigned int)new_tmp->used ||
                   (unsigned int)tmp->free != (unsigned int)new_tmp->free ||
                   (unsigned int)tmp->total != (unsigned int)new_tmp->total) //||
                    // (unsigned int)tmp->time != (unsigned int)tmp->old_time)
                {
                    tmp->avail = new_tmp->avail;
                    strcpy(tmp->directory, new_tmp->directory);
                    strcpy(tmp->type, new_tmp->type);
                    tmp->used = new_tmp->used;
                    tmp->total = new_tmp->total;
                    tmp->free = new_tmp->free;

                    refresh_list_item_device(i);
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
    while( i < names_array->len)
    {

        Devices *tmp = &g_array_index(names_array, Devices, i);

        if(!tmp->checked)
        {
            remove_list_item_device(tmp->directory);
            g_array_remove_index(names_array, i);
            dev_num--;
        }
        else
            i++;

    }


    /* check for unchecked new tasks for inserting */
    for(i = 0; i < new_device_list->len; i++)
    {
        Devices *new_tmp = &g_array_index(new_device_list, Devices, i);

        if(!new_tmp->checked)
        {
            Devices *new_device = new_tmp;

            g_array_append_val(names_array, *new_device);
            //   if(( new_task->uid == own_uid))
            add_new_list_item_dev(dev_num);
            dev_num++;
        }
    }

////////////



    for(i = 0; i < task_array->len; i++)
    {
       Task *tmp = &g_array_index(task_array, Task, i);
        tmp->checked = FALSE;
           // printf("%s\n",tmp->name);
        for(j = 0; j < new_task_list->len; j++)
        {
            Task *new_tmp = &g_array_index(new_task_list, Task, j);

            if(new_tmp->pid == tmp->pid)
            {

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

////////////


//
//
//
   g_array_free(new_task_list, TRUE);
   // g_array_free(names,TRUE);
      g_array_free(new_device_list,TRUE);
//   g_array_free(tasks, FALSE);
//    array();



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
gboolean TESTIRANJE=TRUE;
void CHANGE(){


    TESTIRANJE=FALSE;
    init_timeout();
}

int main(int argc, char *argv[]) {


gtk_init(&argc, &argv);



    dev_swindow = gtk_scrolled_window_new(NULL,
                                          NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(dev_swindow), GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_ALWAYS);
    process_swindow = gtk_scrolled_window_new(NULL,
                                              NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(process_swindow), GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_ALWAYS);



   int g= strcmp("/fsgs","/");

    ncpu = cpu_number();

    interface_name();
    array_interrupts();
    //test
 //   array();
    tasks=g_array_new (FALSE, FALSE, sizeof (Task));
  //  array_devices();

    //  get_task_list(tasks);
    tasks_num=0;
    task_array=g_array_new (FALSE, FALSE, sizeof (Task));

   // names_temp=g_array_new (FALSE, TRUE, sizeof (Devices));
    names_temp=g_array_new (FALSE, FALSE, sizeof (Devices));
    names_array=g_array_new (FALSE, FALSE, sizeof (Devices));


    // names_temp=g_array_new (TRUE, FALSE, sizeof (Devices));
 //   device(TRUE);
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
    window= main_window(dev_swindow,process_swindow);
    g_signal_connect(button, "clicked", G_CALLBACK(inc_refresh), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(dec_refresh), NULL);
    g_signal_connect(button3, "toggled", G_CALLBACK(button_clicked_view_process), NULL);
    g_signal_connect(button4, "toggled", G_CALLBACK(dev_button_clicked), NULL);
    g_signal_connect(button_dev, "toggled", G_CALLBACK(dev_button_clicked2), NULL);
    //g_signal_connect(button5, "toggled", G_CALLBACK(pokazi_ili_hide), NULL);
    g_signal_connect(button5, "toggled", G_CALLBACK(CHANGE), NULL);

    g_signal_connect(button_graph, "clicked", G_CALLBACK(graph_button_clicked), NULL);
    g_signal_connect_swapped ((gpointer) treeview, "button-press-event", G_CALLBACK(on_treeview1_button_press_event), NULL);


    g_signal_connect(G_OBJECT(graph1), "draw",
                     G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(G_OBJECT(graph2), "draw",
                     G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(G_OBJECT(graph3), "draw",
                     G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(G_OBJECT(graph4), "draw",
                     G_CALLBACK(on_draw_event), NULL);



    g_timeout_add(1000, (GSourceFunc) init_timeout2, NULL);

    init_timeout();




    gtk_widget_show_all(window);


   // gtk_widget_hide(dev_swindow);
 //  gtk_widget_hide(process_swindow);


    gtk_main();


    return 0;
}
