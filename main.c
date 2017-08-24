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
//int ncpu;

struct Memory_usage memory_usage;
struct Cpu_usage cpu[4];
gchar *text;
gchar *memory_usage_text;
gchar *swap_usage_text;
gchar *cpu_usage_text;
gchar *network_usage_received_text;
gchar *network_usage_transimited_text;
static GtkWidget *window;
GtkWidget *graph1;
GtkWidget *graph2;
GtkWidget *graph3;
GtkWidget *graph4;
GtkWidget *vbox;
GtkWidget *hbox;
GtkWidget *hbox1;
GtkWidget *hbox2;
GtkWidget *hbox3;
GtkWidget *label;
GtkWidget *label1;
GtkWidget *label2;
GtkWidget *label3;
GtkWidget *label4;
GtkWidget *label5;
GtkWidget *label6;
GtkWidget *label7;
GtkWidget *label8;

GtkWidget *button;
GtkWidget *button2;
GArray *history[9];

gfloat niz[4][200];

GtkWidget *vseparator;
GtkWidget *hseparator;


void init_timeout();
void init_timeout2();
void timeout_refresh();




struct Network net;

static double cpu1;
//static void do_drawing2(cairo_t *cr);
static void do_drawing(GtkWidget *widget,cairo_t *cr1, int l);
static void do_drawing2(GtkWidget *widget,cairo_t *cr1, int l);
static gboolean network_change_rc(gpointer data);
static gboolean network_change_ts(gpointer data);
void percent_ffs();
  guint  t =200;
gboolean refresh=0;
void button_clicked(){

    if(t>=10000){

        t=10000;
    }
    else
    t+=500;
    printf("I clicked a button %d", t);
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
void button_clicked2(){


    if(t<500){
        t=500;
        printf("promena refresh rate \n");
    }
   else
        t-=500;
    printf("I clicked a button2 %d", t);
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
static gboolean time_handler(GtkWidget *widget)
{
    /*cpu_drawing1.cpu1 += 0.4;
    cpu_drawing1.cpu2 +=2;
    cpu_drawing1.cpu3 +=0.2;
    cpu_drawing1.cpu4 +=0.1;

    if(cpu_drawing1.cpu2 >50)
        cpu_drawing1.cpu2=2;*/


  //  cpu_percentage(ncpu);

  /*  percent_ffs();
    get_memory_usage();
    received_transfered();*/
    gtk_widget_queue_draw(widget);

    return TRUE;
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr1,gpointer *user_data){
    double t ;

   int data;
   data= GPOINTER_TO_INT(user_data);


   // percent_ffs();
    do_drawing(widget,cr1,data);
    //do_drawing2(widget,cr1,data);
 /*  switch(data) {
       case 1:
           t=cpu[1].percentage;
           do_drawing(widget,cr,t);


       case 2:
           t=cpu[2].percentage;
           do_drawing(widget,cr,t);
       case 3:
           t=cpu[3].percentage;
           do_drawing(widget,cr,t);
       case 4:
           t=cpu[4].percentage;
           do_drawing(widget,cr,t);
      default:


           do_drawing(widget,cr,t);
       }

*/


}


static void do_drawing(GtkWidget *widget,cairo_t *cr1,int l){
    int width, height;
   GtkWidget *win = gtk_widget_get_toplevel(widget);
    gtk_window_get_size(GTK_WINDOW(win), &width, &height);
    //

   // cairo_surface_t *graph_surface;
   // graph_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 400, 400);
   // cr = cairo_create (graph_surface);
    //

    cairo_t *cr = cr1;
 //   cairo_set_source_rgb(cr,1,.05,1);
    cairo_set_line_width(cr,1);
    int j;

   cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
 //  cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);


gfloat *peak;




// kada stavimo da je gpointer(t) 0 desi se segmantation fault u Garray







int r1= 0;

    int prev[4]={0};
    int step =10;

    for (int j = 0; j < 501; j++) {

        //cairo_move_to(cr,0,400);
        for(int r=1;r<=4;r++) {

//            cairo_translate(cr, step, 0);
             cairo_move_to(cr,0,prev[r]);

            peak = &g_array_index(history[r], gfloat, j);

             prev[r]= 400 - *peak;


            cairo_line_to(cr, step, 400 - *peak);



            if(r==1)
                cairo_set_source_rgba(cr,0.5,0.5,0.5,.5);
            if(r==2)
                cairo_set_source_rgba(cr,1,.5,1,.5);
            if(r==3)
                cairo_set_source_rgba(cr,.4,.5,1,.5);
            if(r==4)
                cairo_set_source_rgba(cr,0,0,0,.5);
            cairo_stroke(cr);


        }
        cairo_translate(cr, step, 0);

    }
   //it works but the lines go to the buttom of the graph
  /*  for (int j = 0; j < 500; j++) {


        for(int r=1;r<=4;r++) {

            cairo_move_to(cr,0,400);

            peak = &g_array_index(history[r], gfloat, j);

            cairo_line_to(cr, 0, 400 - *peak);
            // cairo_set_source_rgb(cr,r/4,r/4,r/4);

            cairo_translate(cr, 1, 0);
            if(r==1)
                cairo_set_source_rgb(cr,0.5,0.5,0.5);
            if(r==2)
                cairo_set_source_rgb(cr,1,.5,1);
            if(r==3)
                cairo_set_source_rgb(cr,.4,.5,1);
            if(r==4)
                cairo_set_source_rgb(cr,0,0,0);
            cairo_stroke(cr);


        }
        cairo_translate(cr, -1, 0);

    }*/


    /*    cairo_move_to(cr, 0, 400);
        for (int j = 0; j < 500; j++) {


            for(int r=6;r<=7;r++) {

                cairo_move_to(cr,0,400);

                peak = &g_array_index(history[r], gfloat, j);

                cairo_line_to(cr, 0, 400 - *peak);
               // cairo_set_source_rgb(cr,r/4,r/4,r/4);

                cairo_translate(cr, 2, 0);
                if(r==6)
                    cairo_set_source_rgb(cr,0.5,0.5,0.5);
                if(r==7)
                    cairo_set_source_rgb(cr,1,.5,1);

                cairo_stroke(cr);

            }
            cairo_translate(cr, -2, 0);
          //  cairo_translate(cr, 2, 0);
        }*/









}

static void do_drawing2(GtkWidget *widget,cairo_t *cr1,int l){
    int width, height;
    // GtkWidget *win = gtk_widget_get_toplevel(widget);
    // gtk_window_get_size(GTK_WINDOW(win), &width, &height);
    //

    // cairo_surface_t *graph_surface;
    // graph_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 400, 400);
    // cr = cairo_create (graph_surface);
    //

    cairo_t *cr = cr1;
     cairo_set_source_rgb(cr,0.2,0.12,0.3);
    cairo_set_line_width(cr,1);


    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
    //cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);

  gfloat *peak;

// kada stavimo da je gpointer(t) 0 desi se segmantation fault u Garray

    //i=l;



    cairo_move_to(cr, 0, 400);
    // cairo_translate(cr,j/2,0);
    for (int j = 0; j < 501; j++) {

        //g_array_insert_val(history,j,p);
        peak = &g_array_index(history[l], gfloat, j);

        //   peak = &niz[l-1][j];
        //  printf("niz : %.1f %d \n ",niz[l-1][j],j);
        //  printf("peak1 %.1f\n", *peak);
        cairo_line_to(cr, 0, 400 - *peak);

      /*  peak = &g_array_index(history[l], gfloat, j+1);

        cairo_line_to(cr, 0, 400 - *peak);*/

        cairo_translate(cr, 2, 0);

    }
    cairo_stroke_preserve(cr);






}
static gboolean network_change_ts(gpointer data){



    float net1= net.transmited_bytes;
    float net_kb = net.transmited_kb;
    static guint i =0;
    printf("STO NECE: %f",net1);
    g_array_insert_val(history[6], i, net_kb);



    network_usage_transimited_text =g_strdup_printf("TRANSMITED: %2.f %s",net.transmited_bytes,net.network_size_ts);

    gtk_label_set_text (GTK_LABEL (data),network_usage_transimited_text);

}
static gboolean network_change_rc(gpointer data){


   // received_transfered();
    float net1= net.received_bytes;
    float net_kb = net.received_kb;
    net_kb/=100;
    static guint i =0;
    printf("STO NECE: %f",net1);
    g_array_insert_val(history[5], i, net_kb);



    network_usage_received_text =g_strdup_printf("RECEIVED: %2.f %s",net.received_bytes,net.network_size_rc);

    gtk_label_set_text (GTK_LABEL (data),network_usage_received_text);
}
static gboolean cpu_change(gpointer data){

    if(data== label3) {

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


};
static gboolean memory_change(gpointer data){


    //get_memory_usage();

    static int i =0;
    gfloat  j = memory_usage.percentage;
    
    g_array_insert_val(history[7], i, j);



    memory_usage_text = g_strdup_printf (("Memory: %d%%"),memory_usage.percentage);
    gtk_label_set_text (GTK_LABEL (data), memory_usage_text);
}
static gboolean swap_change(gpointer data){



    //get_memory_usage();


    static int i =0;
    gfloat  j = memory_usage.swap_used;

    g_array_insert_val(history[8], i, j);
    swap_usage_text = g_strdup_printf(("SWAP: %d%%"),memory_usage.swap_used);
    gtk_label_set_text (GTK_LABEL (data), swap_usage_text);
}
void ninja(){


    g_timeout_add(t,memory_change,label);
    g_timeout_add(t,swap_change,label1);
   // g_timeout_add(t,cpu_change,label2);
    g_timeout_add(t,cpu_change,label3);
    g_timeout_add(t,cpu_change,label4);
    g_timeout_add(t,cpu_change,label5);
    g_timeout_add(t,cpu_change,label6);



}
void percent_ffs(){


    cpu_percentage(ncpu);
    static guint i= 0;
    gfloat j;
    gfloat *peak;
    for(int s=1;s<=ncpu;s++) {

        j = cpu[s - 1].percentage;
      //  j=i;
        niz[s-1][i]=j;
        g_array_insert_val(history[s], i, j);
        peak=&g_array_index(history[s],gfloat,i);

       // printf("peak problems: %f \n",*peak);


    }
 /*   i++;
    if(i<=200)
        i=0; */
/*    static guint i =0;

    cpu_percentage(ncpu);
    for(int n =0; n<ncpu; n++){
        for(int s=1; s<=ncpu;s++) {
            gfloat j = cpu[s - 1].percentage;
            j *= 3;
            //test

            niz[i] = j;
            printf("%f j problems\n", j);
            g_array_insert_val(history[s], i, j);// ako je s ==0 dolazi do greske

            gfloat *peak;
            peak = &g_array_index(history[s], gfloat, i); // ako je s == 0 dolazi do segmantaion fault

            printf("da li prodje? %f\n", *peak);
            //}
            //  cpu_usage_text = g_strdup_printf (("CPU%d: %f%%"),cpu[1].number,cpu[n].percentage);

            if (i == 200)//200
                i = 0;
            i += 1;
            //  j++;
            printf("%d i problems\n", i);
        }//dodato

    }*/
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

    // guint g =i;
   // printf("%d %d \n",i ,g);
     percent_ffs();
     get_memory_usage();

    cpu_change(label1);
    cpu_change(label3);
    cpu_change(label4);
    cpu_change(label5);
    cpu_change(label6);
     memory_change(label);
     swap_change(label1);
    time_handler(window);
    // ninja();
   //  g_timeout_add(t,(GSourceFunc) time_handler,window);

    if(refresh==0)
    {
      //  refresh=g_timeout_add(t,(GSourceFunc)init_timeout,NULL);
       // gint id;
      // gpointer q=GINT_TO_POINTER(t);

       // refresh= g_timeout_add (t,(GSourceFunc) init_timeout, NULL);
       // g_source_remove (refresh);
        refresh= g_timeout_add (t,(GSourceFunc) init_timeout, NULL);
    }







  //  g_timeout_add(t,(GSourceFunc) init_timeout,NULL);


};



int main (int argc, char *argv[]) {


    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    ncpu = cpu_number();
    interface_name();
    for (int i = 0; i <= 9; i++) {
    history[i] = g_array_new(FALSE, TRUE, sizeof(gfloat));
    g_array_set_size(history[i], 900);
}
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);

    button =gtk_button_new_with_label("refresh rate");
    button2 =gtk_button_new_with_label("refresh rate");

    graph1 = gtk_drawing_area_new();
    graph2 = gtk_drawing_area_new();
    graph3 = gtk_drawing_area_new();
    graph4 = gtk_drawing_area_new();


    gtk_widget_set_size_request(graph1,900,400);
    gtk_widget_set_size_request(graph2,900,400);
    gtk_widget_set_size_request(graph3,900,400);
    gtk_widget_set_size_request(graph4,900,400);

    label= gtk_label_new(NULL);//memory
    label1= gtk_label_new(NULL);//swap
    label2= gtk_label_new(NULL);//CPU
    label3= gtk_label_new(NULL);//cpu1
    label4= gtk_label_new(NULL);//cpu2
    label5= gtk_label_new(NULL);//cpu3
    label6= gtk_label_new(NULL);//cpu4
    label7= gtk_label_new(NULL);//network_received
    label8= gtk_label_new(NULL);//network_transimited



    hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);

   // gtk_box_pack_start(GTK_BOX(vbox),label,1,TRUE,0);


    gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,FALSE);//expand,fill,padding
   gtk_box_pack_start(GTK_BOX(hbox),button2,0,0,0);
   gtk_box_pack_start(GTK_BOX(hbox),label,0,0,0);
    gtk_box_pack_start(GTK_BOX(hbox),label3,0,FALSE,1);
    gtk_box_pack_start(GTK_BOX(hbox),label4,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox),label8,1,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox),label7,1,TRUE,0);



    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    gtk_box_pack_start(GTK_BOX(vbox),hbox1,1,TRUE,0);

    gtk_box_pack_start(GTK_BOX(hbox1),graph1,1,TRUE,0);


   // gtk_box_pack_start(GTK_BOX(vbox),label1,0,FALSE,0);
    hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox3,1,TRUE,0);
    hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox3),label1,0,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox3),label5,0,FALSE,1);
    gtk_box_pack_start(GTK_BOX(hbox3),label2,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox3),label6,1,TRUE,0);
 //   gtk_box_pack_start(GTK_BOX(hbox3),label7,1,TRUE,0);



    vseparator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(hbox1),vseparator,1,TRUE,0);

    gtk_box_pack_start(GTK_BOX(hbox1),graph2,1,TRUE,0);
    hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);
    //gtk_box_pack_start(GTK_BOX(vbox),label2,1,TRUE,0);


    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    gtk_box_pack_start(GTK_BOX(vbox),hbox2,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox2),graph3,1,TRUE,0);
   // gtk_box_pack_start(GTK_BOX(hbox3),label4,0,0,0);

    vseparator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(hbox2),vseparator,1,TRUE,0);

    gtk_box_pack_start(GTK_BOX(hbox2),graph4,1,TRUE,0);




    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(button,"clicked", G_CALLBACK(button_clicked), NULL);
    g_signal_connect(button2,"clicked", G_CALLBACK(button_clicked2), NULL);
    g_signal_connect(G_OBJECT(graph1), "draw",
                     G_CALLBACK(on_draw_event),(gpointer)1);
    g_signal_connect(G_OBJECT(graph2), "draw",
                     G_CALLBACK(on_draw_event),(gpointer)5);
    g_signal_connect(G_OBJECT(graph3), "draw",
                     G_CALLBACK(on_draw_event),(gpointer)4);
    g_signal_connect(G_OBJECT(graph4), "draw",
                     G_CALLBACK(on_draw_event),(gpointer)6);





    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1800, 800);
    //gtk_window_get_resizable (window);
    init_timeout();
    g_timeout_add(1000,(GSourceFunc)init_timeout2,NULL);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_window_set_title(GTK_WINDOW(window), "lines mother do you see it ");


    gtk_widget_show_all(window);



    gtk_main();

    return 0;
}
