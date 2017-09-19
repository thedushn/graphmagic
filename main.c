#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory_usage.h"
#include <glib.h>
#include "cpu_usage.h"
#include "network_bandwith.h"
#include "interrupts.h"
#include "task_manager.h"
//#include "model.h"
#include "drawing.h"
#include "main_header.h"
#include "buttons.h"

GtkWidget *menubar;
GtkWidget *filemenu;



struct Memory_usage memory_usage;
struct Cpu_usage cpu[4];
struct Network net;

 gboolean CPU0_line;
 gboolean CPU1_line;
gboolean CPU2_line;
 gboolean CPU3_line;
gchar *memory_usage_text;
gchar *swap_usage_text;
gchar *cpu0_usage_text;
gchar *cpu1_usage_text;
gchar *cpu2_usage_text;
gchar *cpu3_usage_text;
gchar *network_usage_received_text;
gchar *network_usage_transimited_text;
/*static*/ gchar *track;

gboolean CPU0_line= TRUE;
gboolean CPU1_line= TRUE;
gboolean CPU2_line= TRUE;
gboolean CPU3_line= TRUE;


GtkWidget *hseparator;
static  guint  t =1000;
static  guint bjorg=1;//prvi ispis
static guint bjorg2=1;
guint  refresh=0;


static guint time_step=0;


gboolean  toogle1= TRUE;
void init_timeout();
void init_timeout2();
void timeout_refresh();
void measurements();
//static gboolean on_draw_event(GtkWidget *widget,gpointer *user_data);
//static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,gpointer *user_data);
void closing(){

    GtkWidget *fuck;
   fuck= create_view_and_model_file_system();
   // g_object_unref(view2);
    gtk_container_add(GTK_CONTAINER(swindow1), fuck);

};
void dev_button_clicked(GtkWidget *widget);
gchar memory_text[20]="much memory";





static gboolean network_change_rc(gpointer data);
static gboolean network_change_ts(gpointer data);
void percent_ffs();

//void create_view_and_model_file_system(){
static GtkWidget *create_view_and_model_file_system(){


    GtkCellRenderer     *renderer;

    GtkWidget           *view;
//    GtkTreeViewColumn *column;
//    column = gtk_tree_view_column_new ();
    view = gtk_tree_view_new ();
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Device",
                                                 renderer,
                                                 "text", COL_DEV,
                                                 NULL);

    //   --- Column #2 ---

    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Directory",
                                                 renderer,
                                                 "text", COL_DIR,
                                                 NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Type",
                                                 renderer,
                                                 "text", COL_TYPE,
                                                 NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Total",
                                                 renderer,
                                                 "text", COL_TOTAL,
                                                 NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Available",
                                                 renderer,
                                                 "text", COL_AVAILABLE,
                                                 NULL);
    renderer = gtk_cell_renderer_text_new ();
    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view),
                                                 -1,
                                                 "Used",
                                                 renderer,
                                                 "text", COL_USED,
                                                 NULL);

    model = create_and_fill_model_file_system ();


    gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);

//     The tree view has acquired its own reference to the
//     *  model, so we can drop ours. That way the model will
//     *  be freed automatically when the tree view is destroyed

    g_object_unref (model);


    return view;

}

static GtkTreeModel *create_and_fill_model_file_system (void){


    store = gtk_list_store_new (NUM_COLS_DEV, G_TYPE_FLOAT, G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
   // gchar *rss, *vsz;
   // get_task_list(tasks);
    //  Append a row and fill in some data

  //  printf("TASKs-array : len: %d\n",tasks->len);

  //  for(int j=0 ;j<tasks->len;j++) {
     //   Task *task = &g_array_index(tasks, Task, j);
     /*   rss = g_format_size_full (task->rss, G_FORMAT_SIZE_IEC_UNITS);
        vsz = g_format_size_full (task->vsz, G_FORMAT_SIZE_IEC_UNITS);*/
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           COL_DEV, cpu->percentage,
                           COL_DIR, cpu->number,
                           COL_TYPE, "u dont want to know",
                           COL_TOTAL, "not a lot",
                           COL_AVAILABLE, "hwo knows",
                           COL_USED, "even less",

                           -1);



    return GTK_TREE_MODEL (store);

};
void close_window(){


    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(button_graph),
                                  FALSE);


};



void graph_refresh(GtkWidget *widget,gboolean CPU){

    if(widget==button_graph0){


       CPU0_line=CPU;



    }
    if(widget==button_graph1){


        CPU1_line=CPU;



    }
    if(widget==button_graph2){


        CPU2_line=CPU;



    }
    if(widget==button_graph3){


        CPU3_line=CPU;



    }

        if (!g_source_remove (refresh))
        {
            g_critical ("Unable to remove source");
            return;
        }
        refresh = 0;


        init_timeout ();



};



static GtkWidget *create_view_and_model (void)
{
    GtkCellRenderer     *renderer;

    GtkWidget           *view;
    GtkTreeViewColumn *column;
    column = gtk_tree_view_column_new ();
    view = gtk_tree_view_new ();
    g_object_set (column, COLUMN_PROPERTIES, NULL);

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

  //   --- Column #2 ---

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

//     The tree view has acquired its own reference to the
//     *  model, so we can drop ours. That way the model will
//     *  be freed automatically when the tree view is destroyed

    g_object_unref (model);
   

    return view;
};
void dev_problems(){

 //create_view_and_model_file_system();
    view2=create_view_and_model_file_system();
    swindow1=gtk_scrolled_window_new (NULL,
                                      NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(swindow1), GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_ALWAYS);
    gtk_box_pack_start(GTK_BOX(vbox), swindow1, TRUE, TRUE, 1);
    //  gtk_window_set_title(GTK_WINDOW(window1), "2222 ");
//    gtk_widget_destroy(vbox);
    //gtk_container_add(GTK_CONTAINER(swindow1), view);

    //  refeshing_tree();
    gtk_container_add(GTK_CONTAINER(swindow1), view2);



       /*   progressbar=gtk_progress_bar_new();
          gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar),memory_used);
          gtk_progress_bar_get_show_text (GTK_PROGRESS_BAR(progressbar));
          gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar),"text here");
          gtk_box_pack_start(GTK_BOX(vbox),progressbar,0,TRUE,0);
          gtk_widget_show_all(progressbar);*/

    //  gtk_container_add(GTK_CONTAINER(swindow1), progressbar);

    gtk_widget_show_all(swindow1);
}
void dev_button_clicked(GtkWidget *widget){

    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget))) {


    dev_problems();

/*
          progressbar=gtk_progress_bar_new();
          gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar),memory_used);
          gtk_progress_bar_get_show_text (GTK_PROGRESS_BAR(progressbar));
          gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progressbar),"text here");
          gtk_box_pack_start(GTK_BOX(vbox),progressbar,0,TRUE,0);
          gtk_widget_show_all(progressbar);*/

      //  gtk_container_add(GTK_CONTAINER(swindow1), progressbar);

        gtk_widget_show_all(swindow1);
    }
    else{

        // gtk_widget_destroy(progressbar);
        gtk_widget_destroy(view2);
        gtk_widget_destroy(swindow1);


    }
};

static GtkTreeModel *create_and_fill_model (void)
{



    store = gtk_list_store_new (NUM_COLS, G_TYPE_STRING, G_TYPE_UINT,G_TYPE_STRING,G_TYPE_FLOAT,G_TYPE_STRING);
    gchar *rss, *vsz;
    get_task_list(tasks);
   //  Append a row and fill in some data

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
//         append another row and fill in some data
//
//         ... and a third row

    }
       g_array_free(tasks,TRUE);
    array();
  //
    return GTK_TREE_MODEL (store);

};
void button_clicked_view_process(GtkWidget *widget){

   // tree= gtk_tree_view_new ();

   // window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (widget)))
    {
        view= create_view_and_model();
        swindow1=gtk_scrolled_window_new (NULL,
                                          NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(swindow1), GTK_POLICY_AUTOMATIC,
                                       GTK_POLICY_ALWAYS);
        gtk_box_pack_start(GTK_BOX(vbox), swindow1, TRUE, TRUE, 1);
        //  gtk_window_set_title(GTK_WINDOW(window1), "2222 ");
//    gtk_widget_destroy(vbox);
       // gtk_container_add(GTK_CONTAINER(swindow1), view);

      //  refeshing_tree();
        gtk_container_add(GTK_CONTAINER(swindow1), view);
        gtk_widget_show_all(swindow1);


    } else {


        /*gtk_widget_destroy(swindow1);
        gtk_container_remove(GTK_CONTAINER(vbox),swindow1);
        gtk_container_remove(GTK_CONTAINER(swindow1),view);

        gtk_widget_destroy(view);*/

      /*  g_signal_connect(G_OBJECT(window), "destroy",
                         G_CALLBACK(gtk_main_quit), NULL);*/
        gtk_widget_destroy(swindow1);
      //  g_object_unref(view);

        /*g_signal_connect(G_OBJECT(view), "destroy",
                         G_CALLBACK(gtk_main_quit), NULL);*/
    }
}


/*
void measurements(){


    height2= gtk_widget_get_allocated_height(hbox2);
    width2= gtk_widget_get_allocated_width(hbox2);

}*/
void inc_refresh(){

    if(t>=10000){

        t=10000;
    }
    else
    t+=250;
 //   printf("I clicked a button %d", t);
    timeout_refresh();
    //refresh= 0;
  /*  gint id;
    // gpointer q=GINT_TO_POINTER(t);
    id= g_timeout_add (t,(GSourceFunc) init_timeout, NULL);
    g_source_remove (id);
    t+=500;
    id= g_timeout_add (t,(GSourceFunc) init_timeout, NULL);
    */

};
void dec_refresh(){


    if(t<500){
        t=500;
      //  printf("promena refresh rate \n");
    }
   else
        t-=250;
 //   printf("I clicked a button2 %d", t);
    timeout_refresh();


};
static gboolean time_handler(GtkWidget *widget)
{

    gtk_widget_queue_draw(widget);

    return TRUE;
}

void do_drawing4(GtkWidget *widget,cairo_t *cr){
    int width, height;
    height= gtk_widget_get_allocated_height(widget);
    width= gtk_widget_get_allocated_width(widget);
    cairo_set_line_width(cr,1);
    float font_size=10;
    cairo_set_font_size(cr, font_size);
    Interrupts *peak;
    gchar broj[5];

    cr = crtaj_okvir(cr,width,height,font_size,5);
    cairo_set_source_rgb(cr,0,0,0);
  //  gchar ime[3];
    gchar *ime2;
    long max_broj=0;
    signed long temp=0;
  //  gfloat procent=0;
    for (int i = 0; i <= 9; i++) {

        cairo_move_to(cr, 5 * font_size, height);
        peak = &g_array_index(ginterrupts_final, Interrupts, i);
        if(max_broj<=peak->CPU0){

            max_broj=peak->CPU0;
        }
        if(max_broj<=peak->CPU1){

            max_broj=peak->CPU1;
        }
        if(max_broj<=peak->CPU2){

            max_broj=peak->CPU2;
        }
        if(max_broj<=peak->CPU3){

            max_broj=peak->CPU3;
        }

    }
    max_broj+=100;
    cairo_move_to(cr, 0,font_size);
    sprintf(broj,"%li",max_broj);
    cairo_show_text(cr,broj);
    for(int i=1;i<=3;i++){


        temp= max_broj/4*i;

        cairo_move_to(cr,0,(height-font_size)/4*(4-i));
        sprintf(broj,"%li",temp);
        cairo_show_text(cr,broj);
        // cairo_show_text(cr,track);


    }
    cairo_move_to(cr,0,height-font_size);
    cairo_show_text(cr,"0");
    float duzina= (width-(5*font_size*2))/5/10;
    for (int i = 0; i <= 9; i++) {

        // cairo_move_to(cr, 5 * font_size, height);
        peak = &g_array_index(ginterrupts_final, Interrupts, i);

        cairo_move_to(cr, 5 * font_size + 5 * duzina * (i), height);
        ime2 = g_strdup_printf("%s", peak->name);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_show_text(cr, ime2);

        crtaj_interrupte(cr, i, peak, height, font_size, max_broj, duzina);
    }
    //  cairo_stroke(cr);

};
void do_drawing3(GtkWidget *widget,cairo_t *cr){
    int width, height;
    height= gtk_widget_get_allocated_height(widget);
    width= gtk_widget_get_allocated_width(widget);

    /* width=width2/2;
     height=height2/2;*/

    /*  cairo_surface_t *graph_surface;
      graph_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height2);
      cr = cairo_create (graph_surface);*/
    //


    //   cairo_set_source_rgb(cr,1,.05,1);
    cairo_set_line_width(cr,1);
    float font_size=12;
    double step =(width-3*font_size-3*font_size)/time_step;

    cairo_set_font_size(cr, font_size);

    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
    //  cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);


    gfloat *peak;
    gfloat procent;
    double prev[2]={height-font_size};


    cairo_set_font_size(cr, font_size);


    //procent linije

    //secund linije
    /*cairo_set_source_rgba(cr,.7,.7,.7,0.5);
    for(int i =1;i<=5;i++){
        cairo_move_to(cr,(width-2*3*font_size)/6*i+3*font_size,height-font_size);
        cairo_line_to(cr,(width-2*3*font_size)/6*i+3*font_size,0);
    }
*/


    cairo_stroke(cr);
    //okvir
    cr= crtaj_okvir(cr,width,height,font_size,3);


    //procenti
    crtaj_procente(cr,height,font_size);

    //sekunde
    crtaj_sekunde(cr,width,height,font_size,3);













    for (int j = 0; j < bjorg; j++) {



        for(int r=0;r<=1;r++) {

            if(j==0)
                prev[r]=height-font_size;
            cairo_move_to(cr,3*font_size,prev[r]);

            if(r==0){
                peak = &g_array_index(history[6], gfloat, j);
                cairo_set_source_rgb(cr,1,0,0);
            }
            if(r==1){
                peak = &g_array_index(history[7], gfloat, j);

                cairo_set_source_rgba(cr,1,.5,1,.5);
            }
            procent =*peak;

            procent=((height-font_size)/100)*procent;

            //  printf("PEAK: %0.2f\n",*peak);
            // prev[r]= height-font_size - *peak;
            //prev[r]= height-font_size - procent;
            prev[r]= height-font_size - procent;


            cairo_line_to(cr, (3 * font_size), height-font_size - procent);

            cairo_line_to(cr, step+(3 * font_size), height-font_size - procent);



            cairo_stroke(cr);
        }
        cairo_translate(cr, step, 0);
    }









}
void do_drawing(GtkWidget *widget,cairo_t *cr){
    float width, height;
    gchar *rec;
    gchar broj[5];

    float rec_bytes=0;

    gchar *kb="KB/s";
    gchar *mb="MB/s";
    gchar *b="bytes/s";
    gfloat max_broj=0;
    gfloat max_broj2=0;
    gfloat max_broj3=0;
    gfloat procent=0;
    gfloat *peak=0;
    float font_size=10;
    height= gtk_widget_get_allocated_height(widget);
    width= gtk_widget_get_allocated_width(widget);

    double prev[2]={height-font_size,height-font_size};

    float temp;
    double step =(width-5*font_size-5*font_size)/60;
    /*width=width2/2;
    height=height2/2;*/
/*width= width2;
height= height2;*/

    // cairo_surface_t *graph_surface;
    // graph_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 400, 400);
    // cr = cairo_create (graph_surface);
    //

    //   printf("%f width %f height",width,height);
    //   printf("%d width2 %d height2\n",width2,height2);
    //   cairo_set_source_rgb(cr,1,.05,1);
    cairo_set_line_width(cr,1);


    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
    //  cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);


    cairo_set_font_size(cr, font_size);


    crtaj_okvir(cr,width,height,font_size,5);
    //secund linije
    //sekunde
    crtaj_sekunde(cr,width,height,font_size,5);
    cairo_stroke(cr);
    //okvir



    rec=g_strdup_printf("%s",net.network_size_rc);


    for(int j=4; j<=5;j++) {
        for (int i = 0; i < bjorg2; i++) {

            peak = &g_array_index(history[j], float, i);// kb
            if (max_broj2 <= *peak) {

                max_broj2 = *peak;
            }
        }
    }
    if(max_broj<=max_broj2){

        max_broj=max_broj2;


        //    printf("MAX_borj peak : %f\n",*peak);
        //    printf("MAX_borj : %f\n",max_broj);
    }




    cairo_set_source_rgb(cr,0,0,0);

 //   if(max_broj>1024){
    if(max_broj>1000){


      //  rec_bytes = max_broj / 1024;//mb
        rec_bytes = max_broj / 1000;//mb
        rec_bytes += 1;
        track=mb;
        max_broj3=max_broj+1000;
      //  max_broj3=max_broj+1024;

    }
    if(max_broj<=1000 && max_broj >1){
    //if(max_broj<=1024 && max_broj >1){

        rec_bytes = max_broj;//kb

        rec_bytes+=100;
        track=kb;
        max_broj3=max_broj+100;


    }
    if(max_broj<=1){

        rec_bytes= max_broj*1000;//bytes
       // rec_bytes= max_broj*1024;//bytes

        track=rec;
        track=b;
   //     max_broj3=max_broj+1024;
        max_broj3=max_broj+1000;

    }


    cairo_move_to(cr, 0,font_size);//najveci broj
    sprintf(broj,"%.1f",rec_bytes);

    cairo_show_text(cr,broj);

    cairo_show_text(cr,track);
    for(int i=1;i<=3;i++){


        temp= rec_bytes/4*i;

        cairo_move_to(cr,0,(height-font_size)/4*(4-i));
        sprintf(broj,"%.1f",temp);
        cairo_show_text(cr,broj);
        cairo_show_text(cr,track);


    }
    cairo_move_to(cr,0,(height-font_size));
    cairo_show_text(cr,"0");
    cairo_show_text(cr,track);

    // g_free(track);
    g_free(rec);





    for (int j = 0; j < bjorg2; j++) {


        for(int r=0;r<=1;r++) {

//            if(j==0)
//                prev[r]=height-font_size;

            //cairo_move_to(cr,3*font_size,prev[r]);
            cairo_move_to(cr,5*font_size,prev[r]);

            if(r==0){
                peak = &g_array_index(history[4], gfloat, j);
                // procent = *peak;
            }
            if(r==1){
                peak = &g_array_index(history[5], gfloat, j);


            }
            //  procent= *peak;
            procent=((height-font_size)/max_broj3)* *peak;

            //  printf("PEAK: %0.2f\n",*peak);
            // prev[r]= height-font_size - *peak;
            prev[r]= height-font_size - procent;

            //  prev[r]= height-font_size - *peak;

//            if(j==0)
//                cairo_line_to(cr, 3*font_size, height-font_size - *peak);

            //  cairo_line_to(cr, step+3*font_size, height-font_size - procent);
            cairo_line_to(cr, step+5*font_size, height-font_size - procent);
            if(r==0)
                cairo_set_source_rgb(cr,1,0,0);
            if(r==1)
                cairo_set_source_rgba(cr,1,.5,1,.5);

            cairo_stroke(cr);


        }
        cairo_translate(cr, step, 0);

    }

}

void do_drawing2(GtkWidget *widget,cairo_t *cr) {
    int width, height;
    height = gtk_widget_get_allocated_height(widget);
    width = gtk_widget_get_allocated_width(widget);
    cairo_surface_t *graph_surface;


    /* width=width2/2;
     height=height2/2;*/


  //  cairo_set_line_width(cr, 1);
    float font_size = 12;
    double step = (width - 3 * font_size - 3 * font_size) / time_step;

    cairo_set_font_size(cr, font_size);

    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
    //  cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);


    // gfloat *peak;

    cairo_set_font_size(cr, font_size);

    //procent linije



    double prev[4] = {height - font_size, height - font_size, height - font_size, height - font_size};

    int r=0;
      int y= bjorg;
   /*   for(int r=0;r<=1;r++){
         //
          crtanje_cpu(cr, r, y, height, font_size, step);
      }*/
    /* int r=0;
     graph_surface =crtaj(r,height,font_size,step);

     if (graph_surface != NULL)
     {
         cairo_set_source_surface (cr, graph_surface, 0.0, 0.0);
         cairo_paint (cr);
         cairo_surface_destroy (graph_surface);
     }*/





    graph_surface= crtaj_surface(cr,width,height);




    crtaj_okvir(cr, width, height, font_size, 3);
    cairo_set_source_rgba(cr, .7, .7, .7, 0.5);


    cairo_stroke(cr);
    //okvir


    //procenti
    crtaj_procente(cr, height, font_size);
    //sekunde //secund linije
    crtaj_sekunde(cr, width, height, font_size, 3);

  /*  printf("hocemo li ");
    printf("CPU0_pre %d\n",CPU0_line);
    printf("CPU1_pre %d\n",CPU1_line);
    printf("CPU2_pre %d\n",CPU2_line);
    printf("CPU3_pre %d\n",CPU3_line);*/
    if(CPU0_line==TRUE){
   // if(testiranje==1){

        crtanje_cpu(cr, history[0], 0, y, width, height, font_size, step);
    }
    if(CPU1_line==TRUE){
        crtanje_cpu(cr, history[1], 1, y, width, height, font_size, step);
    }
    if(CPU2_line==TRUE){
        crtanje_cpu(cr, history[2], 2, y, width, height, font_size, step);
    }
    if(CPU3_line==TRUE){
        crtanje_cpu(cr, history[3], 3, y, width, height, font_size, step);
    }





   /*     for (int g = 0; g < bjorg; g++) {

            cairo_translate(cr, -step, 0);
        }*/



    /* for (int j = 0; j < bjorg; j++) {

        // cairo_translate(cr, -step, 0);
         int r=0;
      //   crtanje_cpu(cr, r, j, height, font_size, step);
       for (int r = 0; r <= 3; r++) {


                   cairo_move_to(cr, 3 * font_size, prev[r]);
                   gfloat *peak;
                   peak = &g_array_index(history[r], gfloat, j);

                   // int height_temp=height;
                   gfloat procent;// = *peak;
                   procent = ((height - font_size) / 100) * *peak;

                   //    printf("PEAK: %0.2f\n",*peak);
                   // prev[r]= height-font_size - *peak;
                   prev[r] = height - font_size - procent;

                   if (procent == height) {
                       procent = height - 1;
                   }

                       cairo_line_to(cr, step + 3 * font_size, height - font_size - procent);




                   if (r == 0)
                       cairo_set_source_rgb(cr, 0, 0, 1);
                   if (r == 1)
                       cairo_set_source_rgb(cr, 0, 1, 0);
                   if (r == 2)
                       cairo_set_source_rgb(cr, 1, 0, 0);
                   if (r == 3)
                       cairo_set_source_rgb(cr, 0, 0, 0);
                   cairo_stroke(cr);


               }
               cairo_translate(cr, step, 0);



         }
 */


    if (graph_surface != NULL)
    {
        cairo_set_source_surface (cr, graph_surface, 0.0, 0.0);
        cairo_paint (cr);
        cairo_surface_destroy (graph_surface);
    }
};

static gboolean network_change_ts(gpointer data){



   // float net1= net.transmited_bytes;
    float net_kb = net.transmited_kb;
   // static guint i =0;
    bjorg2++;

    if(bjorg2>=60){


        bjorg2=60;
    }
   // printf("STO NECE: %f",net1);
    g_array_prepend_val(history[5], net_kb);
    if (history[5]->len > 1)
        g_array_remove_index (history[5], history[5]->len - 1);



    network_usage_transimited_text =g_strdup_printf("TRANSMITED: %2.f %s",net.transmited_bytes,net.network_size_ts);

    gtk_label_set_text (GTK_LABEL (data),network_usage_transimited_text);
    return TRUE;

}
static gboolean network_change_rc(gpointer data){


   // received_transfered();
   // float net1= net.received_bytes;
    float net_kb = net.received_kb;
   // net_kb/=100;

   // printf("STO NECE: %f",net1);
    g_array_prepend_val(history[4], net_kb);
    if (history[4]->len > 1)
        g_array_remove_index (history[4], history[4]->len - 1);



    network_usage_received_text =g_strdup_printf("RECEIVED: %2.f %s",net.received_bytes,net.network_size_rc);

    gtk_label_set_text (GTK_LABEL (data),network_usage_received_text);
    g_free(network_usage_received_text);
    return TRUE;
}
//static gboolean cpu_change(gpointer data){
static gboolean  cpu_change(){

    cpu0_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[0].number, cpu[0].percentage);
    cpu1_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[1].number, cpu[1].percentage);
    cpu2_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[2].number, cpu[2].percentage);
    cpu3_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[3].number, cpu[3].percentage);

    gtk_label_set_text (GTK_LABEL (label3),cpu0_usage_text);
    gtk_label_set_text (GTK_LABEL (label4),cpu1_usage_text);
    gtk_label_set_text (GTK_LABEL (label5),cpu2_usage_text);
    gtk_label_set_text (GTK_LABEL (label6),cpu3_usage_text);

    g_free(cpu0_usage_text);
    g_free(cpu1_usage_text);
    g_free(cpu2_usage_text);
    g_free(cpu3_usage_text);

    /*if(data== label3) {

        cpu_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[0].number, cpu[0].percentage);
        gtk_label_set_text (GTK_LABEL (data),cpu_usage_text);
    }
    if(data== label4) {

        cpu_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[1].number, cpu[1].percentage);
        gtk_label_set_text (GTK_LABEL (data),cpu_usage_text);
    }
    if(data== label5) {

        cpu_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[2].number, cpu[2].percentage);
        gtk_label_set_text (GTK_LABEL (data),cpu_usage_text);
    }
    if(data== label6) {

        cpu_usage_text = g_strdup_printf(("CPU%d: %2.f%%"), cpu[3].number, cpu[3].percentage);
        gtk_label_set_text (GTK_LABEL (data),cpu_usage_text);
    }
*/

    return TRUE;
};
void memory_change(gpointer data){


    //get_memory_usage();

    gfloat  j = memory_usage.percentage;



     g_array_prepend_val(history[6], j);

    if (history[6]->len > 1)
        g_array_remove_index (history[6], history[6]->len - 1);



    bjorg++;


   time_step=60000/t;

    if(bjorg>=time_step){


        bjorg=time_step;
    }


    memory_usage_text = g_strdup_printf (("Memory: %0.2f%%"),memory_usage.percentage);
    gtk_label_set_text (GTK_LABEL (data), memory_usage_text);
    g_free(memory_usage_text);
    //return TRUE;
}
void swap_change(gpointer data){




   // static guint i =0;
    gfloat  j = memory_usage.swap_used;

    g_array_prepend_val(history[7],  j);
    if (history[7]->len > 1)
        g_array_remove_index (history[7], history[7]->len - 1);
    swap_usage_text = g_strdup_printf(("SWAP: %lu%%"),memory_usage.swap_used);
    gtk_label_set_text (GTK_LABEL (data), swap_usage_text);
    g_free(swap_usage_text);

}

void percent_ffs(){


    cpu_percentage(ncpu);
  //  static guint i= 0;
    gfloat j;
  //  gfloat *peak;
    for(int s=0;s<ncpu;s++) {

        j = cpu[s].percentage;
     //   j=4*j;

        g_array_prepend_val(history[s],  j);
        if (history[s]->len > 1)
            g_array_remove_index (history[s], history[s]->len - 1);
       // peak=&g_array_index(history[s],gfloat,i);

       // printf("peak problems: %f \n",*peak);


    }

};
void timeout_refresh(){

    if (!g_source_remove (refresh))
    {
        g_critical ("Unable to remove source");
        return;
    }
    refresh = 0;
    init_timeout ();

}
void init_timeout2(){
    received_transfered();
    network_change_rc( label7);
  network_change_ts (label8);



}
 void init_timeout(){

//     measurements();
     percent_ffs();//nije ovde
     get_memory_usage();//nije ovde
  // array_interrupts();
     interrupt_usage();



   /* cpu_change(label1);
    cpu_change(label3);
    cpu_change(label4);
    cpu_change(label5);
    cpu_change(label6);*/

     cpu_change();//nije ovde
     memory_change(label);// nije ovde
     swap_change(label1); // nije ovde

    time_handler(window);
//test
   // array();
   //  get_task_list(tasks);
    // refeshing_tree();

 //   get_task_list(tasks);
  //  printf("CPU problems %d %d %d %d \n",CPU0_line,CPU1_line,CPU2_line,CPU3_line);

    if(refresh==0)
    {

        refresh= g_timeout_add (t,(GSourceFunc) init_timeout, NULL);
    }

};


static void quit_activated()
{
    g_print("File -> Quit activated...bye.\n");
    gtk_main_quit();
}
int main (int argc, char *argv[]) {


    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    ncpu = cpu_number();
    interface_name();
   array_interrupts();
    //test
    array();
 //  get_task_list(tasks);


    for (int i = 0; i < 8; i++) {
    history[i] = g_array_new(FALSE, TRUE, sizeof(gfloat));
   // g_array_set_size(history[i], 240);//treba staviti da  history[4] i 5  imaju size 60
}
    for(int i=0;i<=3;i++){

        g_array_set_size(history[i], 240);
    }
    for(int i=4 ;i<=5;i++){

        g_array_set_size(history[i], 60);
    }
    for(int i=6 ;i<=7;i++){


        g_array_set_size(history[i], 240);
    }

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);

    button =gtk_button_new_with_label("refresh rate +");
    button2 =gtk_button_new_with_label("refresh rate-");
    button3=  gtk_toggle_button_new_with_label( "Process");
    button4=  gtk_toggle_button_new_with_label( "Dev");
 /*   gtk_toggle_button_set_mode (GTK_TOGGLE_BUTTON (button3),
                                FALSE);
*/


    menubar = gtk_menu_bar_new();
    filemenu =gtk_menu_new();

   speed = gtk_menu_item_new_with_label("speed");
   increase_refresh = gtk_menu_item_new_with_label("+250");
   decrease_refresh = gtk_menu_item_new_with_label("-250");

    quit = gtk_menu_item_new_with_label("Quit");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(speed), filemenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), increase_refresh);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), decrease_refresh);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar),speed);
    g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(quit_activated), NULL);
    g_signal_connect(increase_refresh,"activate", G_CALLBACK(inc_refresh), NULL);
    g_signal_connect(decrease_refresh,"activate", G_CALLBACK(dec_refresh), NULL);
   gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);




    button_graph =gtk_toggle_button_new_with_label("graphs");

    graph1 = gtk_drawing_area_new();
    graph2 = gtk_drawing_area_new();
    graph3 = gtk_drawing_area_new();
    graph4 = gtk_drawing_area_new();



    label= gtk_label_new(NULL);//memory
    label1= gtk_label_new(NULL);//swap
   // label2= gtk_label_new(NULL);//CPU
    label3= gtk_label_new(NULL);//cpu1
    label4= gtk_label_new(NULL);//cpu2
    label5= gtk_label_new(NULL);//cpu3
    label6= gtk_label_new(NULL);//cpu4
    label7= gtk_label_new(NULL);//network_received
    label8= gtk_label_new(NULL);//network_transimited












    hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
  //  gtk_box_pack_start(GTK_BOX(vbox),hbox,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,0,FALSE,0);
    //gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);
  //testing frames
   // gtk_box_pack_start(GTK_BOX(vbox),hseparator,0,FALSE,0);




    gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,FALSE);//expand,fill,padding
   gtk_box_pack_start(GTK_BOX(hbox),button2,0,0,0);
   gtk_box_pack_start(GTK_BOX(hbox),button3,0,0,0);
   gtk_box_pack_start(GTK_BOX(hbox),button_graph,0,0,0);
   gtk_box_pack_start(GTK_BOX(hbox),label3,0,0,0);
    gtk_box_pack_start(GTK_BOX(hbox),label4,0,FALSE,1);
    gtk_box_pack_start(GTK_BOX(hbox),label5,0,0,0);
    gtk_box_pack_start(GTK_BOX(hbox),label6,0,0,0);
    gtk_box_pack_start(GTK_BOX(hbox),label8,1,1,1);
    gtk_box_pack_start(GTK_BOX(hbox),label7,1,TRUE,1);



    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    //gtk_box_pack_start(GTK_BOX(vbox),hbox1,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox1,1,1,0);
//testing frames
    frame1=gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(frame1),graph1);
    gtk_box_pack_start(GTK_BOX(hbox1),frame1,1,TRUE,0);
    //
   // gtk_box_pack_start(GTK_BOX(hbox1),graph1,1,TRUE,0);



   // hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    //gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);
   // gtk_box_pack_start(GTK_BOX(vbox),hseparator,0,0,0);
  //  gtk_box_pack_start(GTK_BOX(vbox),hbox3,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox3,0,FALSE,0);
 //   hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    //frame testing
   // gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox3),button4,0,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox3),label,0,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox3),label1,0,FALSE,1);
  //  gtk_box_pack_start(GTK_BOX(hbox3),label2,1,TRUE,0);
  //  gtk_box_pack_start(GTK_BOX(hbox3),label6,1,TRUE,0);




 //   vseparator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
 //testing frames

   // gtk_box_pack_start(GTK_BOX(hbox1),vseparator,1,TRUE,0);
    frame2=gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(frame2),graph2);

    gtk_box_pack_start(GTK_BOX(hbox1),frame2,1,TRUE,0);
    // gtk_box_pack_start(GTK_BOX(hbox1),graph2,1,TRUE,0);
    //
  //  hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);

  //testing
  //  gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);


    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    gtk_box_pack_start(GTK_BOX(vbox),hbox2,1,TRUE,0);
   // gtk_box_pack_start(GTK_BOX(vbox),progressbar,1,TRUE,0);

    //testing frames
    frame3=gtk_frame_new(NULL);
    frame4=gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(frame3),graph3);
    gtk_container_add(GTK_CONTAINER(frame4),graph4);
    gtk_box_pack_start(GTK_BOX(hbox2),frame3,1,TRUE,0);


   // vseparator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
  //testing frames
    //gtk_box_pack_start(GTK_BOX(hbox2),vseparator,1,TRUE,0);


    gtk_box_pack_start(GTK_BOX(hbox2),frame4,1,TRUE,0);





    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(button,"clicked", G_CALLBACK(inc_refresh), NULL);
    g_signal_connect(button2,"clicked", G_CALLBACK(dec_refresh), NULL);
    g_signal_connect(button3,"toggled", G_CALLBACK(button_clicked_view_process), NULL);
    g_signal_connect(button4,"toggled", G_CALLBACK(dev_button_clicked), NULL);
    g_signal_connect(button_graph,"clicked", G_CALLBACK(graph_button_clicked), NULL);



    g_signal_connect(G_OBJECT(graph1), "draw",
                     G_CALLBACK(do_drawing2),NULL);
    g_signal_connect(G_OBJECT(graph2), "draw",
                     G_CALLBACK(do_drawing),NULL);
    g_signal_connect(G_OBJECT(graph3), "draw",
                     G_CALLBACK(do_drawing3),NULL);
    g_signal_connect(G_OBJECT(graph4), "draw",
                     G_CALLBACK(do_drawing4),NULL);






    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1400, 800);
  //  gtk_window_get_resizable (window);
//    measurements();
   init_timeout();
    g_timeout_add(1000,(GSourceFunc)init_timeout2,NULL);
   //g_timeout_add(1000,(GSourceFunc)dev_problems,NULL);
  //  dev_problems();
  //  g_timeout_add(1000,(GSourceFunc)closing,NULL);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_window_set_title(GTK_WINDOW(window), "lines mother do you see it ");


    gtk_widget_show_all(window);



    gtk_main();


 /*   if(refresh> 0){
        g_source_remove (refresh);
        g_object_unref (window);
    }
*/





    return 0;
}
