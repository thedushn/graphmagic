//
// Created by dushn on 11.10.17..
//

#include "window.h"

#include "testing_tree.h"
#include "buttons.h"
#include "memory_usage.h"
#include "cpu_usage.h"

struct _Memory_usage memory_usage;
struct _Cpu_usage cpu[4];
  GtkWidget *main_window(GtkWidget *dev_swindow,GtkWidget *process_swindow){


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
      button_condition= gtk_button_new_with_label("COND");

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
    GtkWidget *new = gtk_menu_item_new_with_label("return");
    GtkWidget *test = gtk_menu_item_new_with_label("flush");
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
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu2), new);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu2), test);

    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), devices_menu);


    g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(quit_activated), NULL);

    g_signal_connect(increase_refresh, "activate", G_CALLBACK(inc_refresh), NULL);
    g_signal_connect(decrease_refresh, "activate", G_CALLBACK(dec_refresh), NULL);
    g_signal_connect(file_system, "activate", G_CALLBACK(device_window), NULL);
    g_signal_connect(new, "activate", G_CALLBACK(new_button_clicked2), NULL);
    g_signal_connect(test, "activate", G_CALLBACK(clean_button), NULL);
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
    gtk_box_pack_start(GTK_BOX(hbox), button_proc, 0, 0, 0);
  //  gtk_box_pack_start(GTK_BOX(hbox), button5, 0, 0, 0);
   // gtk_box_pack_start(GTK_BOX(hbox), button4, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button_dev, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button_graph, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(hbox), button_condition, 0, 0, 0);
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



    g_signal_connect(G_OBJECT(window1), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);





    gtk_container_add(GTK_CONTAINER(window1), vbox);

    gtk_window_set_title(GTK_WINDOW(window1), "lines mother do you see it ");

    return window1;
};

void quit_activated() {
    g_print("File -> Quit activated...bye.\n");
    gtk_main_quit();
};

void swap_change(gpointer data){




 // static guint i =0;
 gchar  *swap_total,*swap_used;

 gfloat  j = memory_usage.swap_percentage;
 swap_used = g_format_size_full((guint64) memory_usage.swap_used, G_FORMAT_SIZE_IEC_UNITS);
 swap_total = g_format_size_full((guint64) memory_usage.swap_total, G_FORMAT_SIZE_IEC_UNITS);
 g_array_prepend_val(history[7],  j);
 if (history[7]->len > 1)
  g_array_remove_index (history[7], history[7]->len - 1);
 swap_usage_text = g_strdup_printf(("SWAP: %0.2f%% (%s) %s"),memory_usage.swap_percentage,swap_used,swap_total);
 gtk_label_set_text (GTK_LABEL (data), swap_usage_text);
 g_free(swap_usage_text);
 g_free(swap_total);
 g_free(swap_used);

}
void memory_change(gpointer data){


 gchar *used,*total,*memory_usage_text1;

 gfloat  j = memory_usage.percentage;


 used = g_format_size_full((guint64) memory_usage.memory_used, G_FORMAT_SIZE_IEC_UNITS);

 total = g_format_size_full((guint64) memory_usage.memory_total, G_FORMAT_SIZE_IEC_UNITS);

 g_array_prepend_val(history[6], j);

 if (history[6]->len > 1)
  g_array_remove_index (history[6], history[6]->len - 1);






 memory_usage_text1 = g_strdup_printf (("Memory: %0.2f%%(%s)%s"),memory_usage.percentage,used,total);
 gtk_label_set_text (GTK_LABEL (data), memory_usage_text1);
 g_free(memory_usage_text1);
 g_free(total);
 g_free(used);

}
gboolean  cpu_change(Cpu_usage1 *cpu_usage1){

    ////vratiti nazad
    cpu0_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), 0, cpu_usage1->percentage0);
    cpu1_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), 1,  cpu_usage1->percentage1);
    cpu2_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), 2,  cpu_usage1->percentage2);
    cpu3_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), 3,  cpu_usage1->percentage3);

    gtk_label_set_text (GTK_LABEL (label3),cpu0_usage_text);
    gtk_label_set_text (GTK_LABEL (label4),cpu1_usage_text);
    gtk_label_set_text (GTK_LABEL (label5),cpu2_usage_text);
    gtk_label_set_text (GTK_LABEL (label6),cpu3_usage_text);

    g_free(cpu0_usage_text);
    g_free(cpu1_usage_text);
    g_free(cpu2_usage_text);
    g_free(cpu3_usage_text);
    ////vratiti nazad
    return TRUE;

};



