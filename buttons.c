//
// Created by dushn on 19.9.17..
//

#include "buttons.h"
#include "drawing.h"
#include "testing_tree.h"
#include "main_header.h"
#include "buttons_s.h"

void process_window(){
    proc_window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(proc_window), 200, 200);
    button_process_cpu=gtk_check_button_new_with_label ("CPU");
    button_process_pid=gtk_check_button_new_with_label ("PID");
    button_process_ppid=gtk_check_button_new_with_label ("PPID");
    button_process_rss=gtk_check_button_new_with_label ("RSS");
    button_process_state=gtk_check_button_new_with_label ("State");
    button_process_task=gtk_check_button_new_with_label ("Task");
    button_process_vm_size=gtk_check_button_new_with_label ("VM_size");
    button_process_user=gtk_check_button_new_with_label ("User");

    if(process_cpu==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_process_cpu),TRUE);
    }
    if(process_pid==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_process_pid),TRUE);
    }
    if(process_ppid==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_process_ppid),TRUE);
    }
    if(process_rss==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_process_rss),TRUE);
    }

    if(process_state==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_process_state),TRUE);
    }
    if(process_task==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_process_task),TRUE);
    }
    if(process_vm_size==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_process_vm_size),TRUE);
    }
    if(process_user==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_process_user),TRUE);
    }




    gtk_window_set_title (GTK_WINDOW (proc_window), "Process window");

    box2=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_container_add(GTK_CONTAINER(proc_window),box2);
    gtk_box_pack_start(GTK_BOX(box2),button_process_task,1,1,0);
    gtk_box_pack_start(GTK_BOX(box2),button_process_user,1,1,0);
    gtk_box_pack_start(GTK_BOX(box2),button_process_pid,1,1,0);
    gtk_box_pack_start(GTK_BOX(box2),button_process_ppid,1,1,0);
    gtk_box_pack_start(GTK_BOX(box2),button_process_state,1,1,0);
    gtk_box_pack_start(GTK_BOX(box2),button_process_vm_size,1,1,0);
    gtk_box_pack_start(GTK_BOX(box2),button_process_rss,1,1,0);
    gtk_box_pack_start(GTK_BOX(box2),button_process_cpu,1,1,0);
    g_signal_connect(button_process_user,"toggled", G_CALLBACK(process_clicked), NULL);
    g_signal_connect(button_process_rss,"toggled", G_CALLBACK(process_clicked), NULL);
    g_signal_connect(button_process_task,"toggled", G_CALLBACK(process_clicked), NULL);
    g_signal_connect(button_process_vm_size,"toggled", G_CALLBACK(process_clicked), NULL);
    g_signal_connect(button_process_state,"toggled", G_CALLBACK(process_clicked), NULL);
    g_signal_connect(button_process_cpu,"toggled", G_CALLBACK(process_clicked), NULL);
    g_signal_connect(button_process_pid,"toggled", G_CALLBACK(process_clicked), NULL);
    g_signal_connect(button_process_ppid,"toggled", G_CALLBACK(process_clicked), NULL);


    gtk_window_set_position(GTK_WINDOW(proc_window), GTK_WIN_POS_CENTER);

    g_signal_connect(G_OBJECT(proc_window), "destroy",
                     G_CALLBACK(close_window), NULL);

    gtk_widget_show_all(proc_window);

}
void device_window(){


        dev_window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(dev_window), 200, 200);
        button_device_devices=gtk_check_button_new_with_label ("Devices");
        button_device_directory=gtk_check_button_new_with_label ("Directories");
        button_device_total=gtk_check_button_new_with_label ("Total size");
        button_device_avail=gtk_check_button_new_with_label ("available");
        button_device_type=gtk_check_button_new_with_label ("type");
        button_device_free=gtk_check_button_new_with_label ("free");
        button_device_used=gtk_check_button_new_with_label ("used");
        button_device_all =gtk_check_button_new_with_label ("Show_all");

    if(device_devices==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_device_devices),TRUE);
    }
    if(device_all==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_device_all),TRUE);
    }
    if(device_directory==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_device_directory),TRUE);
    }
    if(device_used==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_device_used),TRUE);
    }
    if(device_free==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_device_free),TRUE);
    }

    if(device_total==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_device_total),TRUE);
    }
    if(device_avail==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_device_avail),TRUE);
    }
    if(device_type==TRUE){
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_device_type),TRUE);
    }




    gtk_window_set_title (GTK_WINDOW (dev_window), "Device window");

        box2=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
        gtk_container_add(GTK_CONTAINER(dev_window),box2);
        gtk_box_pack_start(GTK_BOX(box2),button_device_all,1,1,0);
        gtk_box_pack_start(GTK_BOX(box2),button_device_devices,1,1,0);
        gtk_box_pack_start(GTK_BOX(box2),button_device_directory,1,1,0);
        gtk_box_pack_start(GTK_BOX(box2),button_device_avail,1,1,0);
        gtk_box_pack_start(GTK_BOX(box2),button_device_total,1,1,0);
        gtk_box_pack_start(GTK_BOX(box2),button_device_free,1,1,0);
        gtk_box_pack_start(GTK_BOX(box2),button_device_used,1,1,0);
        gtk_box_pack_start(GTK_BOX(box2),button_device_type,1,1,0);
        g_signal_connect(button_device_devices,"toggled", G_CALLBACK(device_clicked), NULL);
        g_signal_connect(button_device_all,"toggled", G_CALLBACK(show_all), NULL);
        g_signal_connect(button_device_directory,"toggled", G_CALLBACK(device_clicked), NULL);
        g_signal_connect(button_device_avail,"toggled", G_CALLBACK(device_clicked), NULL);
        g_signal_connect(button_device_total,"toggled", G_CALLBACK(device_clicked), NULL);
        g_signal_connect(button_device_free,"toggled", G_CALLBACK(device_clicked), NULL);
        g_signal_connect(button_device_used,"toggled", G_CALLBACK(device_clicked), NULL);
        g_signal_connect(button_device_type,"toggled", G_CALLBACK(device_clicked), NULL);


        gtk_window_set_position(GTK_WINDOW(dev_window), GTK_WIN_POS_CENTER);

        g_signal_connect(G_OBJECT(dev_window), "destroy",
                         G_CALLBACK(close_window), NULL);

        gtk_widget_show_all(dev_window);




}

void button_clicked_view_process(GtkWidget *widget) {




    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (widget))) {

        pokazi_ili_hide(widget, process_swindow);


        gtk_widget_show_all(process_swindow);


    } else {


        pokazi_ili_hide(widget, process_swindow);

    }
}
void dev_button_clicked2(GtkWidget *widget){



    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON (widget))) {


        pokazi_ili_hide(widget, dev_swindow);



        gtk_widget_show_all(dev_swindow);
        // g_timeout_add(1000, (GSourceFunc)refresh_dev(),NULL);
    } else {
        pokazi_ili_hide(widget, dev_swindow);

        //  GList *children=  gtk_container_get_children(GTK_CONTAINER(dev_swindow));

        // gtk_widget_destroy(progressbar);
        //  gtk_widget_unparent(children->data);
        // gtk_container_remove(GTK_CONTAINER(dev_swindow),children->data);
        //gtk_widget_destroy(swindow2);
        //    gtk_widget_destroy(dev_swindow);
        //pokazi_ili_hide(widget);
        //   gtk_widget_hide(dev_swindow);
        //    clean_button();
        //   gtk_container_remove(GTK_CONTAINER(swindow2),view2);




    }

}


void close_window() {


    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button_graph),
                                 FALSE);


};
void graph_button_clicked(GtkWidget *widget){


    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {
        window2 =gtk_window_new(GTK_WINDOW_TOPLEVEL);

        button_graph0=gtk_toggle_button_new_with_label("CPu0");
        button_graph1=gtk_toggle_button_new_with_label("CPu1");
        button_graph2=gtk_toggle_button_new_with_label("CPu2");
        button_graph3=gtk_toggle_button_new_with_label("CPu3");

        if(CPU0_line==TRUE){
            gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_graph0),TRUE);
        }
        if(CPU1_line==TRUE){
            gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_graph1),TRUE);
        }
        if(CPU2_line==TRUE){
            gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_graph2),TRUE);
        }
        if(CPU3_line==TRUE){
            gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_graph3),TRUE);
        }

        gtk_window_set_title (GTK_WINDOW (window2), "GRAPH buttons");

        box2=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
        gtk_container_add(GTK_CONTAINER(window2),box2);
        gtk_box_pack_start(GTK_BOX(box2),button_graph0,1,1,0);
        gtk_box_pack_start(GTK_BOX(box2),button_graph1,1,1,0);
        gtk_box_pack_start(GTK_BOX(box2),button_graph2,1,1,0);
        gtk_box_pack_start(GTK_BOX(box2),button_graph3,1,1,0);
        g_signal_connect(button_graph0,"toggled", G_CALLBACK(graph_clicked), NULL);
        g_signal_connect(button_graph1,"toggled", G_CALLBACK(graph_clicked), NULL);
        g_signal_connect(button_graph2,"toggled", G_CALLBACK(graph_clicked), NULL);
        g_signal_connect(button_graph3,"toggled", G_CALLBACK(graph_clicked), NULL);


        gtk_window_set_position(GTK_WINDOW(window2), GTK_WIN_POS_CENTER);

        g_signal_connect(G_OBJECT(window2), "destroy",
                         G_CALLBACK(close_window), NULL);

        gtk_widget_show_all(window2);

    }

    else{

        gtk_widget_destroy(window2);

    }
};
void device_clicked(GtkWidget *widget){
//void graph_clicked(GtkWidget *widget){

    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {
        if(widget==button_device_devices){

            device_devices= TRUE;
            //     testiranje=1;
            change_list_store_view_devices(widget, device_devices);
          //  device_refresh(widget,CPU0_line );

            //  return CPU0_line;
        }
        else if(widget==button_device_directory){

            device_directory= TRUE;
            change_list_store_view_devices(widget, device_directory);
           // device_refresh(widget,device_directory );
        }
        else if(widget==button_device_avail){

            device_avail= TRUE;
            change_list_store_view_devices(widget, device_avail);
           // device_refresh(widget,device_avail );
        }
        else if(widget==button_device_total){
            device_total= TRUE;
            change_list_store_view_devices(widget, device_total);
          //  device_refresh(widget,device_total );
        }
        else if(widget==button_device_used){
            device_used= TRUE;
            change_list_store_view_devices(widget, device_used);
           // device_refresh(widget,device_used );
        }
        else if(widget==button_device_type){
            device_type= TRUE;
            change_list_store_view_devices(widget, device_type);
          //  device_refresh(widget,device_type );
        }
        else /*if(widget==button_device_free)*/{
            device_free= TRUE;
            change_list_store_view_devices(widget, device_free);
         //   device_refresh(widget,device_free );
        }

    }
    else{

        if(widget==button_device_devices){

            device_devices= FALSE;

            // graph_refresh();
            change_list_store_view_devices(widget, device_devices);
          //  device_refresh(widget,device_devices );

        }
        else if(widget==button_device_directory){

            device_directory= FALSE;
            change_list_store_view_devices(widget, device_directory);
          //  device_refresh(widget,device_directory );
        }
        else if(widget==button_device_avail){

            device_avail= FALSE;
            change_list_store_view_devices(widget, device_avail);
           // device_refresh(widget,device_avail );
        }
        else if(widget==button_device_total){
                device_total= FALSE;
            change_list_store_view_devices(widget, device_total);
           // device_refresh(widget,device_total );
        }
        else if(widget==button_device_used){
            device_used= FALSE;
            change_list_store_view_devices(widget, device_used);
           // device_refresh(widget,device_used );
        }
        else if(widget==button_device_type){
            device_type= FALSE;
            change_list_store_view_devices(widget, device_type);
          //  device_refresh(widget,device_type );
        }
        else /*if(widget==button_device_free)*/{
            device_free= FALSE;
            change_list_store_view_devices(widget, device_free);
          //  device_refresh(widget,device_free );
        }



    }

};

void process_clicked(GtkWidget *widget){
//void graph_clicked(GtkWidget *widget){

    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {
        if(widget==button_process_task){

            process_task= TRUE;
            //     testiranje=1;
            change_list_store_view_process(widget, process_task);
            //  process_refresh(widget,process_task );

            //  return CPU0_line;
        }
        else if(widget==button_process_cpu){

            process_cpu= TRUE;
            change_list_store_view_process(widget, process_cpu);
          //  process_refresh(widget,process_cpu );
        }
        else if(widget==button_process_pid){

            process_pid= TRUE;
            change_list_store_view_process(widget, process_pid);
         //   process_refresh(widget,process_pid );
        }
        else if(widget==button_process_ppid){
            process_ppid= TRUE;
            change_list_store_view_process(widget, process_ppid);
          //  process_refresh(widget,process_ppid );
        }
        else if(widget==button_process_rss){
            process_rss= TRUE;
            change_list_store_view_process(widget, process_rss);
        //    process_refresh(widget,process_rss );
        }
        else if(widget==button_process_vm_size){
            process_vm_size= TRUE;
            change_list_store_view_process(widget, process_vm_size);
         //   process_refresh(widget,process_vm_size );
        }
        else if(widget==button_process_state){
            process_state= TRUE;
            change_list_store_view_process(widget, process_state);
          //  process_refresh(widget,process_state );
        }
        else{

            process_user= TRUE;
            change_list_store_view_process(widget, process_user);
          //  process_refresh(widget,process_user );
        }


    }
    else{

        if(widget==button_process_task){

            process_task= FALSE;
            //     testiranje=1;
            change_list_store_view_process(widget, process_task);
          //    process_refresh(widget,process_task );

            //  return CPU0_line;
        }
        else if(widget==button_process_cpu){

            process_cpu= FALSE;
            change_list_store_view_process(widget, process_cpu);
           // process_refresh(widget,process_cpu );
        }
        else if(widget==button_process_pid){

            process_pid= FALSE;
            change_list_store_view_process(widget, process_pid);
           // process_refresh(widget,process_pid );
        }
        else if(widget==button_process_ppid){
            process_ppid= FALSE;
            change_list_store_view_process(widget, process_ppid);
           // process_refresh(widget,process_ppid );
        }
        else if(widget==button_process_rss){
            process_rss= FALSE;
            change_list_store_view_process(widget, process_rss);
            //process_refresh(widget,process_rss );
        }
        else if(widget==button_process_vm_size){
            process_vm_size= FALSE;
            change_list_store_view_process(widget, process_vm_size);
            //process_refresh(widget,process_vm_size );
        }
        else if(widget==button_process_state){
            process_state= FALSE;
            change_list_store_view_process(widget, process_state);
           // process_refresh(widget,process_state );
        }
        else{

            process_user= FALSE;
            change_list_store_view_process(widget, process_user);
          //  process_refresh(widget,process_user );
        }



    }

};
void graph_clicked(GtkWidget *widget){
//void graph_clicked(GtkWidget *widget){

    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {
        if(widget==button_graph0){

            CPU0_line= TRUE;
       //     testiranje=1;
//             graph_refresh(widget,CPU0_line );

          //  return CPU0_line;
        }
        if(widget==button_graph1){

            CPU1_line= TRUE;
        //    graph_refresh(widget,CPU1_line );
            printf("CPU line %d\n",CPU1_line);
        }
        if(widget==button_graph2){

            CPU2_line= TRUE;
        //    graph_refresh(widget,CPU2_line );
            printf("CPU line %d\n",CPU2_line);
        }
        if(widget==button_graph3){

            CPU3_line= TRUE;
            printf("CPU line %d\n",CPU3_line);
         //   graph_refresh(widget,CPU3_line );
            //  graph_refresh();
        }
      //  graph_refresh();

    }
    else{

        if(widget==button_graph0){

            CPU0_line= FALSE;

            // graph_refresh();
         //   graph_refresh(widget,CPU0_line );

        }
        if(widget==button_graph1){

            CPU1_line= FALSE;
            // graph_refresh();
        //    graph_refresh(widget,CPU1_line );
            printf("CPU line %d\n",CPU1_line);
        }
        if(widget==button_graph2){

            CPU2_line= FALSE;
            // graph_refresh();
        //    graph_refresh(widget,CPU2_line );
            printf("CPU line %d\n",CPU2_line);
        }
        if(widget==button_graph3){

            CPU3_line= FALSE;
            // graph_refresh();
        //    graph_refresh(widget,CPU3_line );
            printf("CPU line %d\n",CPU3_line);
        }
       // graph_refresh();


    }

};



void pokazi_ili_hide(GtkWidget *button, GtkWidget *window) {


    if( gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (button))!=FALSE){//ako je button toggled


//        gtk_widget_hide(hbox1);
//        gtk_widget_hide(hbox3);
//        gtk_widget_hide(hbox2);
        gtk_widget_show(window);
        if(window==dev_swindow){

            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button_proc),FALSE); //postavljamo butto_proc na not toggled
                gtk_widget_hide(process_swindow);
        }
        else{

            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button_dev),FALSE); //postavljamo butto_proc na not toggled
            gtk_widget_hide(dev_swindow);
        }

        }
        else{

//        gtk_widget_show(hbox1);
//        gtk_widget_show(hbox3);
//        gtk_widget_show(hbox2);
        gtk_widget_hide(window);

        }



};
void new_button_clicked2(){


    gtk_widget_hide(hbox1);
    gtk_widget_hide(hbox3);
    gtk_widget_hide(hbox2);
}
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
void handle_task_menu(GtkWidget *widget, gchar *signal)
{
    printf("signal %s\n",signal);
    if(signal != NULL)
    {


//        if (strcmp(signal, "KILL") == 0)
//            s = ("Really kill the task?");
//        else
//            s = ("Really terminate the task?");

        if(strcmp(signal, "STOP") == 0 || strcmp(signal, "CONT") == 0 || strcmp(signal, "KILL") == 0 )
        {
            gchar *task_id = "";
            GtkTreeModel *model;
            GtkTreeIter iter;

            if(gtk_tree_selection_get_selected(selection, &model, &iter))
            {
                gtk_tree_model_get(model, &iter, 1, &task_id, -1);
                send_signal_to_task(task_id, signal);
                init_timeout();
            }
        }
    }
}
void send_signal_to_task(gchar *task_id, gchar *signal)
{
    printf("SIGNAL %s the task with ID %s\n", signal, task_id);
    if(task_id != "" && signal != NULL)
    {
        gchar command[64] = "kill -";
        g_strlcat(command,signal, sizeof command);
        g_strlcat(command," ", sizeof command);
        g_strlcat(command,task_id, sizeof command);
        printf("Task id %s",task_id);
        if(system(command) != 0)
            printf("comand failed\n");
//            xfce_err("Couldn't %s the task with ID %s", signal, task_id);
    }
}
GtkWidget* create_taskpopup (void)
{
    GtkWidget *taskpopup;
    GtkWidget *menu_item;

    taskpopup = gtk_menu_new ();

    menu_item = gtk_menu_item_new_with_mnemonic (("Stop"));
    gtk_widget_show (menu_item);
    gtk_container_add (GTK_CONTAINER (taskpopup), menu_item);
    g_signal_connect ((gpointer) menu_item, "activate", G_CALLBACK (handle_task_menu), "STOP");

    menu_item = gtk_menu_item_new_with_mnemonic (("Continue"));
    gtk_widget_show (menu_item);
    gtk_container_add (GTK_CONTAINER (taskpopup), menu_item);
    g_signal_connect ((gpointer) menu_item, "activate", G_CALLBACK (handle_task_menu), "CONT");

    menu_item = gtk_menu_item_new_with_mnemonic (("Term"));
    gtk_widget_show (menu_item);
    gtk_container_add (GTK_CONTAINER (taskpopup), menu_item);
    g_signal_connect ((gpointer) menu_item, "activate", G_CALLBACK (handle_task_menu), "TERM");

    menu_item = gtk_menu_item_new_with_mnemonic (("Kill"));
    gtk_widget_show (menu_item);
    gtk_container_add (GTK_CONTAINER (taskpopup), menu_item);
    g_signal_connect ((gpointer) menu_item, "activate", G_CALLBACK (handle_task_menu), "KILL");

    return taskpopup;
}
gboolean on_treeview1_button_press_event(GtkButton *button, GdkEventButton *event)
{
    if(event->button == 3)
    {
        printf("i was here\n");
        GdkEventButton *mouseevent = (GdkEventButton *)event;
        printf("moseevent button %d\n",mouseevent->button);
        if(taskpopup == NULL)
            taskpopup = create_taskpopup ();
        gtk_menu_popup(GTK_MENU(taskpopup), NULL, NULL, NULL, NULL, mouseevent->button, mouseevent->time);

    }
    return FALSE;
}
void do_drawing2(GtkWidget *widget,cairo_t *cr,guint bjorg,guint time_step) {
    int width, height;
    float font_size = 12;
    double step;
    cairo_surface_t *graph_surface;

    height = gtk_widget_get_allocated_height(widget);
    width = gtk_widget_get_allocated_width(widget);




    //  cairo_set_line_width(cr, 1);

    step = (width - 3 * font_size - 3 * font_size) / time_step;

    cairo_set_font_size(cr, font_size);

    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);


    cairo_set_font_size(cr, font_size);


    graph_surface= crtaj_surface(cr,width,height);

    //okvir
    //   crtaj_procent_linije(cr, width,height, font_size, 3);
    crtaj_okvir(cr, width, height, font_size, 3);
    cairo_set_source_rgba(cr, .7, .7, .7, 0.5);
    cairo_stroke(cr);

    //procenti
    crtaj_procente(cr, height, font_size);
    //sekunde //secund linije
    crtaj_sekunde(cr, width, height, font_size, 3);


//    printf("CPU0 LINE %s\n", CPU0_line==TRUE ? "TRUE" : "FALSE");
//    printf("CPU1 LINE %s\n", CPU1_line==TRUE ? "TRUE" : "FALSE");
//    printf("CPU2 LINE %s\n", CPU2_line==TRUE ? "TRUE" : "FALSE");
//    printf("CPU3 LINE %s\n", CPU3_line==TRUE ? "TRUE" : "FALSE");
    if(CPU0_line==TRUE){


        crtanje_graph(cr, history[0], 0, bjorg, 3, height, font_size, step);
    }
    if(CPU1_line==TRUE){
        crtanje_graph(cr, history[1], 1, bjorg, 3, height, font_size, step);
    }
    if(CPU2_line==TRUE){
        crtanje_graph(cr, history[2], 2, bjorg, 3, height, font_size, step);
    }
    if(CPU3_line==TRUE){
        crtanje_graph(cr, history[3], 3, bjorg, 3, height, font_size, step);
    }



    if (graph_surface != NULL)
    {
        cairo_set_source_surface (cr, graph_surface, 0.0, 0.0);
        cairo_paint (cr);
        cairo_surface_destroy (graph_surface);
    }
};