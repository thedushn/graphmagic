//
// Created by dushn on 11.10.17..
//

#include "window.h"

#include "testing_tree.h"
#include "buttons.h"



GtkWidget *label_rec;
GtkWidget *label_trans;

GtkWidget *label_cpu0;

GtkWidget *label_mem;
GtkWidget *label_swap;
GtkWidget *label_time;



  GtkWidget *main_window(GtkWidget *dev_swindow,GtkWidget *process_swindow){
      GtkWidget *vbox;
      GtkWidget *hbox;
      GtkWidget *hbox1;
      GtkWidget *hbox3;
      GtkWidget *hbox2;

      GtkWidget *menubar;
      GtkWidget *filemenu;
      GtkWidget *speed;
      GtkWidget *devices_menu;
      GtkWidget *filemenu2;
      GtkWidget *quit;
      GtkWidget *increase_refresh;
      GtkWidget *decrease_refresh;
      GtkWidget *file_system;

      GtkWidget *frame1;
      GtkWidget *frame2;
      GtkWidget *frame3;
      GtkWidget *frame4;
      GtkTreeSelection *selection1;
   GtkWidget *window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window1), 1400, 800);


    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);//cpu labels
    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);//graph1 graph2 frame1 frame2
    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);//izmedju graphova
    hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);//graph3 graph4 frame3 frame4

    button = gtk_button_new_with_label("refresh rate +");
    button2 = gtk_button_new_with_label("refresh rate-");
    button_proc = gtk_toggle_button_new_with_label("Process");
   // button4 = gtk_toggle_button_new_with_label("Dev");
    button_dev = gtk_toggle_button_new_with_label("Dev");
  //  button5 = gtk_toggle_button_new_with_label("NEW");
    button_graph = gtk_toggle_button_new_with_label("graphs");
    //  button_condition= gtk_button_new_with_label("COND");

    menubar = gtk_menu_bar_new();
    filemenu = gtk_menu_new();
    filemenu2 = gtk_menu_new();
   GtkWidget * filemenu3 =gtk_menu_new();
 //filemenu3=gtk_menu_item_new_with_label("testingalltheway");
    speed = gtk_menu_item_new_with_label("speed");
    devices_menu = gtk_menu_item_new_with_label("devices");
    GtkWidget *process_menu = gtk_menu_item_new_with_label("Process Manager");
  //  graph_menu = gtk_menu_item_new_with_label("graphs");
    GtkWidget *process_item=gtk_menu_item_new_with_label("Processes");
    increase_refresh = gtk_menu_item_new_with_label("+250");
    decrease_refresh = gtk_menu_item_new_with_label("-250");
    file_system = gtk_menu_item_new_with_label("file_systems");
   // GtkWidget *new = gtk_menu_item_new_with_label("return");
   // GtkWidget *test = gtk_menu_item_new_with_label("flush");
    quit = gtk_menu_item_new_with_label("Quit");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(speed), filemenu);
    //gtk_menu_item_set_submenu(GTK_MENU_ITEM(speed), filemenu3);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), increase_refresh);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), decrease_refresh);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), speed);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), process_menu);
//  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), graph_menu);


// gtk_menu_item_set_submenu(GTK_MENU_ITEM(graph_menu), filemenu3);

//  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu3), graph_window);






    gtk_menu_item_set_submenu(GTK_MENU_ITEM(devices_menu), filemenu2);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(process_menu), filemenu3);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu2), file_system);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu3), process_item);
 //   gtk_menu_shell_append(GTK_MENU_SHELL(filemenu2), new);
  //  gtk_menu_shell_append(GTK_MENU_SHELL(filemenu2), test);

    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), devices_menu);


    g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(quit_activated), NULL);

    g_signal_connect(increase_refresh, "activate", G_CALLBACK(inc_refresh), NULL);
    g_signal_connect(decrease_refresh, "activate", G_CALLBACK(dec_refresh), NULL);
    g_signal_connect(file_system, "activate", G_CALLBACK(device_window), NULL);
  //  g_signal_connect(new, "activate", G_CALLBACK(new_button_clicked2), NULL);
  //  g_signal_connect(test, "activate", G_CALLBACK(clean_button), NULL);
    g_signal_connect(process_item, "activate", G_CALLBACK(process_window), NULL);
//   g_signal_connect(graph_window, "activate", G_CALLBACK(graph_button_clicked), NULL);

    treeview = gtk_tree_view_new ();

    gtk_widget_show (treeview);



    GtkTreeStore *list_store =create_list_store();

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(list_store));
    g_object_unref(list_store);
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(list_store), 1, GTK_SORT_ASCENDING);
    gtk_container_add(GTK_CONTAINER(process_swindow),treeview);


   treeview1 = gtk_tree_view_new ();

    gtk_widget_show (treeview1);



    list_store1 =create_list_store_dev();

//
//     for(int i=0 ;i<names->len;i++){
//      GtkTreeIter iter;
//         printf("%d \n",i);
//         gtk_tree_store_append(GTK_TREE_STORE(list_store1), &iter, NULL);
//         fill_list_item_dev(i, &iter);
//                               }
//        for(int i=0 ;i<names->len;i++){
//    printf("i %d",i);
//    add_new_list_item(i);
//     }

    selection1 = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview1));



    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview1), GTK_TREE_MODEL(list_store1));
    g_object_unref(list_store1);
    gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(list_store1), 1, GTK_SORT_ASCENDING);
   gtk_container_add(GTK_CONTAINER(dev_swindow),treeview1);




    graph1 = gtk_drawing_area_new();
    graph2 = gtk_drawing_area_new();
    graph3 = gtk_drawing_area_new();
    graph4 = gtk_drawing_area_new();
      printf("graph is floating %s\n", g_object_is_floating (graph1)==TRUE ? "TRUE" : "FALSE");

    frame1 = gtk_frame_new(NULL);
    frame2 = gtk_frame_new(NULL);
    frame3 = gtk_frame_new(NULL);
    frame4 = gtk_frame_new(NULL);
      printf("frame is floating %s\n", g_object_is_floating (frame1)==TRUE ? "TRUE" : "FALSE");

    label_rec = gtk_label_new(NULL);//memory
    label_trans = gtk_label_new(NULL);//swap
    label_cpu0 = gtk_label_new(NULL);//cpu1
/*    label_cpu1 = gtk_label_new(NULL);//cpu2
    label_cpu2 = gtk_label_new(NULL);//cpu3
    label_cpu3 = gtk_label_new(NULL);//cpu4*/
    label_mem = gtk_label_new(NULL);//network_received
    label_swap = gtk_label_new(NULL);//network_transimited
    label_time = gtk_label_new(NULL);//time(local)



    gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, FALSE);//expand,fill,padding
    gtk_box_pack_start(GTK_BOX(hbox), button2, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button_proc, 0, 0, 0);
  //  gtk_box_pack_start(GTK_BOX(hbox), button5, 0, 0, 0);
   // gtk_box_pack_start(GTK_BOX(hbox), button4, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button_dev, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button_graph, 0, 0, 0);
  //  gtk_box_pack_start(GTK_BOX(hbox), button_condition, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), label_cpu0, 0, 0, 0);
  /*  gtk_box_pack_start(GTK_BOX(hbox), label_cpu1, 0, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox), label_cpu2, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), label_cpu3, 0, 0, 0);*/
    gtk_box_pack_start(GTK_BOX(hbox), label_rec, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(hbox), label_trans, 1, TRUE, 1);



    gtk_box_pack_start(GTK_BOX(vbox), hbox1, 1, 1, 0);


    gtk_container_add(GTK_CONTAINER(frame1), graph1);
    gtk_box_pack_start(GTK_BOX(hbox1), frame1, 1, TRUE, 0);
      printf("graph is floating %s\n", g_object_is_floating (graph1)==TRUE ? "TRUE" : "FALSE");


    gtk_box_pack_start(GTK_BOX(vbox), hbox2, 0, FALSE, 0);

//  gtk_box_pack_start(GTK_BOX(hbox2), button4, 0, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), label_mem, 0, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox2), label_swap, 0, FALSE, 1);
    gtk_box_pack_start(GTK_BOX(hbox2), label_time, 0, 0,1 );
//    gtk_box_pack_start(GTK_BOX(hbox2), label_mem, 1, TRUE, 1);



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









    gtk_container_add(GTK_CONTAINER(window1), vbox);


    gtk_window_set_title(GTK_WINDOW(window1), "College lines");

    return window1;
};

void quit_activated() {
    g_print("File -> Quit activated...bye.\n");
    gtk_main_quit();
};

void swap_change(Memory_usage *memory_usage){




 // static guint i =0;
 gchar  *swap_total,*swap_used;

 gfloat  j = memory_usage->swap_percentage;
 swap_used = g_format_size_full((guint64) memory_usage->swap_used, G_FORMAT_SIZE_IEC_UNITS);
 swap_total = g_format_size_full((guint64) memory_usage->swap_total, G_FORMAT_SIZE_IEC_UNITS);

 g_array_prepend_val(history[7],  j);
 if (history[7]->len > 1)
  g_array_remove_index (history[7], history[7]->len - 1);


    gchar* swap_usage_text = g_strdup_printf(("SWAP: %0.2f%% (%s) %s"),memory_usage->swap_percentage,swap_used,swap_total);
    gtk_label_set_text (GTK_LABEL (label_swap), swap_usage_text);

    g_free(swap_usage_text);
    g_free(swap_total);
    g_free(swap_used);

}
void memory_change(Memory_usage *memory_usage){


 gchar *used,*total,*memory_usage_text1;

 gfloat  j = memory_usage->percentage;


 used = g_format_size_full((guint64) memory_usage->memory_used, G_FORMAT_SIZE_IEC_UNITS);

 total = g_format_size_full((guint64) memory_usage->memory_total, G_FORMAT_SIZE_IEC_UNITS);

 g_array_prepend_val(history[6], j);

 if (history[6]->len > 1)
  g_array_remove_index (history[6], history[6]->len - 1);


 memory_usage_text1 = g_strdup_printf (("Memory: %0.2f%%(%s)%s"),memory_usage->percentage,used,total);
 gtk_label_set_text (GTK_LABEL (label_mem), memory_usage_text1);

 g_free(memory_usage_text1);
 g_free(total);
 g_free(used);

}
void time_change(struct tm *tm){


    gchar *time = g_strdup_printf(("Year: %d Month-%d Day-%d  Hour:%d Min:%d Sec:%d"), tm->tm_year,
                                  tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
 gtk_label_set_text (GTK_LABEL (label_time),time);
 g_free(time);


}
void  cpu_change(Cpu_usage1 *cpu_usage1){





    g_array_prepend_val(history[0], cpu_usage1->percentage0);
    if (history[0]->len > 1)
        g_array_remove_index (history[0], history[0]->len - 1);

    g_array_prepend_val(history[1], cpu_usage1->percentage1);
    if (history[1]->len > 1)
        g_array_remove_index (history[1], history[1]->len - 1);

    g_array_prepend_val(history[2], cpu_usage1->percentage2);
    if (history[2]->len > 1)
        g_array_remove_index (history[2], history[2]->len - 1);

    g_array_prepend_val(history[3], cpu_usage1->percentage3);
    if (history[3]->len > 1)
        g_array_remove_index (history[3], history[3]->len - 1);




    ////vratiti nazad
    /*gchar*   cpu1_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), 1,  cpu_usage1->percentage1);
    gchar*   cpu2_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), 2,  cpu_usage1->percentage2);
    gchar*  cpu3_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), 3,  cpu_usage1->percentage3);*/
    gchar*  cpu0_usage_text = g_strdup_printf(("CPU%d: %2.f%% CPU%d: %2.f%%CPU%d: %2.f%%CPU%d: %2.f%%"),
                                              0,cpu_usage1->percentage0,
                                              1,  cpu_usage1->percentage1,
                                              2,  cpu_usage1->percentage2,
                                              3,  cpu_usage1->percentage3
    );

    gtk_label_set_text (GTK_LABEL (label_cpu0),cpu0_usage_text);
 /*   gtk_label_set_text (GTK_LABEL (label_cpu1),cpu1_usage_text);
    gtk_label_set_text (GTK_LABEL (label_cpu2),cpu2_usage_text);
    gtk_label_set_text (GTK_LABEL (label_cpu3),cpu3_usage_text);*/

    g_free(cpu0_usage_text);
   /* g_free(cpu1_usage_text);
    g_free(cpu2_usage_text);
    g_free(cpu3_usage_text);*/
    ////vratiti nazad


};
void network_change_rc(Network *network){



    float net_kb =  network->received_bytes/1024;
    float net_kb_tr=network->transmited_bytes/1024;

    g_array_prepend_val(history[5], net_kb_tr);
    if (history[5]->len > 1)
        g_array_remove_index (history[5], history[5]->len - 1);
    g_array_prepend_val(history[4], net_kb);
    if (history[4]->len > 1)
        g_array_remove_index (history[4], history[4]->len - 1);

    gchar *  rec_bytes = g_format_size_full(network->received_bytes, G_FORMAT_SIZE_IEC_UNITS);
    gchar *  rec_tr_bytes=g_format_size_full(network->transmited_bytes, G_FORMAT_SIZE_IEC_UNITS);
    gchar*   network_usage_received_text =g_strdup_printf("RECEIVED:  %s/s",rec_bytes);
    gchar*  network_usage_transimited_text =g_strdup_printf("TRANSMITED: %s/s",rec_tr_bytes);
    gtk_label_set_text (GTK_LABEL (label_rec),network_usage_received_text);


    gtk_label_set_text (GTK_LABEL (label_trans),network_usage_transimited_text);
    g_free(rec_bytes);
    g_free(rec_tr_bytes);
    g_free(network_usage_received_text);
    g_free(network_usage_transimited_text);

}


