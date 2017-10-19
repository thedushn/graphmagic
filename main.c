#include "cpu_usage.h"
#include "network_bandwith.h"
#include "interrupts.h"
#include "task_manager.h"

#include "drawing.h"


#include "testing_tree.h"
#include "memory_usage.h"
#include "window.h"


static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr) {


    if (widget == graph1) {

        do_drawing2(widget, cr, bjorg, time_step);
    }
    else if (widget == graph2) {

        do_drawing(widget, cr, bjorg2);
    }
    else if (widget == graph3) {

        do_drawing3(widget, cr, bjorg, time_step);
    }
//    else  /*if (widget == graph4)*/ {
//
//        do_drawing4(widget, cr);
//    }
return TRUE;

}
void process_refresh(GtkWidget *widget, gboolean BOOL){


    if (widget == button_process_state) {


        process_state = BOOL;


    }
    else if (widget ==button_process_vm_size) {


        process_vm_size = BOOL;


    }
    else if (widget == button_process_rss) {


        process_rss = BOOL;


    }
    else if (widget == button_process_task) {


        process_task = BOOL;


    }
    else if (widget == button_process_pid) {


        process_pid = BOOL;


    }
    else if (widget == button_process_ppid) {


        process_ppid = BOOL;


    }
    else if (widget == button_process_cpu) {


        process_cpu = BOOL;


    }
    else /* (widget == button_device_type)*/ {


        process_user = BOOL;


    }


    timeout_refresh();
}

void device_refresh(GtkWidget *widget, gboolean BOOL) {

    if (widget == button_device_devices) {


        device_devices = BOOL;


    }
    else if (widget == button_device_directory) {


        device_directory = BOOL;


    }
    else if (widget == button_device_total) {


        device_total = BOOL;


    }
    else if (widget == button_device_free) {


        device_free = BOOL;


    }
    else if (widget == button_device_used) {


        device_used = BOOL;


    }
    else if (widget == button_device_avail) {


        device_avail = BOOL;


    }
    else /* (widget == button_device_type)*/ {


        device_type = BOOL;


    }


    timeout_refresh();


};
void show_all(GtkWidget *widget){

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (widget))) {

        device_all=TRUE;

    } else
        device_all=FALSE;

    timeout_refresh();


};
void graph_refresh(GtkWidget *widget, gboolean CPU) {

    if (widget == button_graph0) {


        CPU0_line = CPU;


    }
    else if (widget == button_graph1) {


        CPU1_line = CPU;


    }
    else if (widget == button_graph2) {

        CPU2_line = CPU;

    }
    else /* (widget == button_graph3)*/ {

        CPU3_line = CPU;
    }

    timeout_refresh();


};


void inc_refresh() {

    if (t >= 10000) {

        t = 10000;
    }
    else
    {
        t += 250;
    }

    timeout_refresh();



};

void dec_refresh() {


    if (t <= 250) {
        t = 250;
        //  printf("promena refresh rate \n");

    }
    else {
        t -= 250;
    }
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

    guint i=0,j=0;


GArray *new_task_list;
    GArray *new_device_list;
    GArray *new_interrupt_list;
    new_task_list =  get_task_list2();
    new_device_list   = device(device_all);
   new_interrupt_list=interrupt_usage();


    printf("new list%d\n",new_interrupt_list->len);
   Interrupts *interrupts=&g_array_index(interrupt_array_temp, Interrupts, i);

    if(interrupts==NULL){

        interrupt_array_temp=upis(new_interrupt_list,interrupt_array_temp);
    }
    poredjenje();
    printf("list%d\n",interrupt_array_temp->len);
    for(i = 0; i < interrupt_array_temp->len; i++) //uzimamo element niza
    {
         interrupts=&g_array_index(interrupt_array_temp, Interrupts, i);
        printf("name[%s] CPU0[%lu] CPU1[%lu] CPU2[%lu] CPU3[%lu] ime1[%s],ime2 [%s] ime3 [%s] ime4[%s]\n",interrupts->name,interrupts->CPU0,interrupts->CPU1,interrupts->CPU2,interrupts->CPU3,interrupts->ime1,interrupts->ime2,interrupts->ime3,interrupts->ime4);
        }
    printf("/////\n");
    for(i = 0; i < names_array->len; i++) //uzimamo element niza
    {
        Devices *tmp = &g_array_index(names_array, Devices, i);
        tmp->checked = FALSE;
        // printf("%s\n",tmp->name);
        for(j = 0; j < new_device_list->len; j++)
        {
            Devices *new_tmp = &g_array_index(new_device_list, Devices, j);

            if(strcmp(new_tmp->directory, tmp->directory)==0 &&strcmp(new_tmp->name, tmp->name)==0 && strcmp(new_tmp->type, tmp->type)==0&&
                        new_tmp->fid==tmp->fid && new_tmp->total ==tmp->total
                    )  //poredimo elemente nizova
            {
              //  if(strcmp(new_tmp->name, tmp->name)==0) {

                    if((gint)tmp->avail != (gint)new_tmp->avail //ako ima razlika
                       /* || strcmp(tmp->used,new_tmp->used)*/ ||
                   //    strcmp(tmp->type,new_tmp->type)!=0 ||
                     //  strcmp(tmp->name,new_tmp->name)!=0 ||
                       (unsigned int)tmp->used != (unsigned int)new_tmp->used ||
                       (unsigned int)tmp->free != (unsigned int)new_tmp->free ||
                       (unsigned int)tmp->total != (unsigned int)new_tmp->total) //||
                        // (unsigned int)tmp->time != (unsigned int)tmp->old_time)
                    {
                        tmp->avail = new_tmp->avail;
                        //strcpy(tmp->name, new_tmp->name);
                     //   strcpy(tmp->type, new_tmp->type);
                        tmp->used = new_tmp->used;
                        tmp->total = new_tmp->total;
                        tmp->free = new_tmp->free;

                        refresh_list_item_device(i);
                      //  printf("I %d name %s directory %s size %lu\n",i,tmp->name,tmp->directory,tmp->total);
                    }
                    tmp->checked = TRUE; //
                    new_tmp->checked = TRUE;
                    break;
             //   }

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
     //   printf("name %s I %d checked %s \n",tmp->name,i,tmp->checked  ? "TRUE" : "FALSE");
        if(!tmp->checked)//element niza koji se ne nalazi vise u novom nizu
        {
            remove_list_item_device(tmp->directory,tmp->name,tmp->type);
            g_array_remove_index(names_array, i);
         //   printf("we removed a item from the list I [%d] name: %s directry: %s\n",i,tmp->name,tmp->directory);
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
            printf("new item added for no reason %d name %s\n",i,new_device->name);
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




   g_array_free(new_task_list, TRUE);

      g_array_free(new_device_list,TRUE);
      g_array_free(new_interrupt_list,TRUE);




    cpu_percent_change(ncpu);//nije ovde
    get_memory_usage();//nije ovde

   // interrupt_usage();
    cpu_change();
 //   cpu_change(ncpu);

   memory_change(label);// nije ovde
    swap_change(label1); // nije ovde

    time_handler(window);
    bjorg++;



    time_step = 60000 / t;

    if (bjorg >= time_step) {


        bjorg = time_step;
    }


    if (refresh == 0) {

        refresh = g_timeout_add(t, (GSourceFunc) init_timeout, NULL);
    }

};


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



    ncpu = cpu_number();

    interface_name();
    //array_interrupts();



    task_array=g_array_new (FALSE, FALSE, sizeof (Task));
    interrupt_array_d=g_array_new (FALSE, FALSE, sizeof (Interrupts));
    interrupt_array_temp=g_array_new (FALSE, FALSE, sizeof (Interrupts));


    names_temp=g_array_new (FALSE, FALSE, sizeof (Devices));
    names_array=g_array_new (FALSE, FALSE, sizeof (Devices));



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
    g_signal_connect(button_proc, "toggled", G_CALLBACK(button_clicked_view_process), NULL);
  //  g_signal_connect(button4, "toggled", G_CALLBACK(dev_button_clicked), NULL);
    g_signal_connect(button_dev, "toggled", G_CALLBACK(dev_button_clicked2), NULL);



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


    gtk_widget_hide(dev_swindow);
   gtk_widget_hide(process_swindow);
//    gtk_widget_hide(hbox1);
//    gtk_widget_hide(hbox3);
//    gtk_widget_hide(hbox2);


    gtk_main();


    if (refresh > 0){
        g_source_remove (refresh);

    }
   // g_object_unref (window);

    return 0;
}
