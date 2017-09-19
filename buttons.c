//
// Created by dushn on 19.9.17..
//

#include "buttons.h"
static gboolean CPU0_line=TRUE;
static gboolean CPU1_line=TRUE;
static gboolean CPU2_line=TRUE;
static gboolean CPU3_line=TRUE;

void graph_button_clicked(GtkWidget *widget){


    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {
        window2 =gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_default_size(GTK_WINDOW(window2), 200, 200);

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
//
//        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_graph1),TRUE);
//        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_graph2),TRUE);
//        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_graph3),TRUE);
        gtk_window_set_title (GTK_WINDOW (window2), "GRAPH buttons");

        box2=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
        gtk_container_add(GTK_CONTAINER(window2),box2);
        gtk_box_pack_start(GTK_BOX(box2),button_graph0,0,0,0);
        gtk_box_pack_start(GTK_BOX(box2),button_graph1,0,0,0);
        gtk_box_pack_start(GTK_BOX(box2),button_graph2,0,0,0);
        gtk_box_pack_start(GTK_BOX(box2),button_graph3,0,0,0);
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
void graph_clicked(GtkWidget *widget){
//void graph_clicked(GtkWidget *widget){

    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {
        if(widget==button_graph0){

            CPU0_line= TRUE;
            testiranje=1;
             graph_refresh(widget,CPU0_line );

          //  return CPU0_line;
        }
        if(widget==button_graph1){

            CPU1_line= TRUE;
            graph_refresh(widget,CPU1_line );
            printf("CPU line %d\n",CPU1_line);
        }
        if(widget==button_graph2){

            CPU2_line= TRUE;
            graph_refresh(widget,CPU2_line );
            printf("CPU line %d\n",CPU2_line);
        }
        if(widget==button_graph3){

            CPU3_line= TRUE;
            printf("CPU line %d\n",CPU3_line);
            graph_refresh(widget,CPU3_line );
            //  graph_refresh();
        }
      //  graph_refresh();

    }
    else{

        if(widget==button_graph0){

            CPU0_line= FALSE;
            testiranje=0;
            // graph_refresh();
            graph_refresh(widget,CPU0_line );
            printf("testiranje line %d\n",testiranje);
        }
        if(widget==button_graph1){

            CPU1_line= FALSE;
            // graph_refresh();
            graph_refresh(widget,CPU1_line );
            printf("CPU line %d\n",CPU1_line);
        }
        if(widget==button_graph2){

            CPU2_line= FALSE;
            // graph_refresh();
            graph_refresh(widget,CPU2_line );
            printf("CPU line %d\n",CPU2_line);
        }
        if(widget==button_graph3){

            CPU3_line= FALSE;
            // graph_refresh();
            graph_refresh(widget,CPU3_line );
            printf("CPU line %d\n",CPU3_line);
        }
       // graph_refresh();


    }

};
