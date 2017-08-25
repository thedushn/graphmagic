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
GtkWidget *button3;
GArray *history[8];



GtkWidget *vseparator;
GtkWidget *hseparator;


void init_timeout();
void init_timeout2();
void timeout_refresh();
void measurements();



struct Network net;

static double cpu1;
//static void do_drawing2(cairo_t *cr);
static void do_drawing(GtkWidget *widget,cairo_t *cr);
static void do_drawing2(GtkWidget *widget,cairo_t *cr);
static void do_drawing3(GtkWidget *widget,cairo_t *cr);
static gboolean network_change_rc(gpointer data);
static gboolean network_change_ts(gpointer data);
void percent_ffs();
void button_clicked3();
  guint  t =1000;
gboolean refresh=0;
float width,height;
void button_clicked3(){





}

void measurements(){


    height= gtk_widget_get_allocated_height(graph3);
    width= gtk_widget_get_allocated_width(graph3);

}
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

    gtk_widget_queue_draw(widget);

    return TRUE;
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,gpointer *user_data){
    double t ;
//    int data;
//    data= GPOINTER_TO_INT(user_data);
    if(widget==graph1){

        do_drawing2(widget,cr);
    }
    if(widget==graph2){


       do_drawing(widget,cr);
    }
    if(widget==graph3){

        do_drawing3(widget,cr);

    }
    if(widget==graph4){


        do_drawing3(widget,cr);
    }











}

static void do_drawing3(GtkWidget *widget,cairo_t *cr){
  /*  int width, height;

   height= gtk_widget_get_allocated_height(graph3);
   width= gtk_widget_get_allocated_width(graph3);*/
    //

    // cairo_surface_t *graph_surface;
    // graph_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 400, 400);
    // cr = cairo_create (graph_surface);
    //

//    printf("%f width %f height\n",width,height);
    //   cairo_set_source_rgb(cr,1,.05,1);
    cairo_set_line_width(cr,1);


    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
    //  cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);


    gfloat *peak;

    double font_size=12;
    double step =(width-3*font_size-3*font_size)/60;

    cairo_set_font_size(cr, font_size);


    //procent linije
    cairo_set_source_rgba(cr,.7,.7,.7,0.5);
    cairo_move_to(cr,0,height/4);//75%
    cairo_line_to(cr,width-3*font_size,height/4);
    cairo_move_to(cr,0,height/4*2);//50
    cairo_line_to(cr,width-3*font_size,height/4*2);
    cairo_move_to(cr,0,height/4*3);//25
    cairo_line_to(cr,width-3*font_size,height/4*3);
    //secund linije

    cairo_move_to(cr,step*10+3*font_size,height);
    cairo_line_to(cr,step*10+3*font_size,0);
    for(int i=2 ;i<=5;i++){
        cairo_move_to(cr,step*10*i+3*font_size,height-font_size);
        cairo_line_to(cr,step*10*i+3*font_size,0);
    }



    /* cairo_move_to(cr,(width-3*font_size)/6*3,height);
     cairo_line_to(cr,(width-3*font_size)/6*3,0);

     cairo_move_to(cr,(width-3*font_size)/6*4,height);
     cairo_line_to(cr,(width-3*font_size)/6*4,0);

     cairo_move_to(cr,(width-3*font_size)/6*5,height);
     cairo_line_to(cr,(width-3*font_size)/6*5,0);*/



    cairo_stroke(cr);
    //okvir
    cairo_move_to(cr,3*font_size,0);
    cairo_line_to(cr,width-3*font_size,0);
    cairo_move_to(cr,3*font_size,0);
    cairo_line_to(cr,3*font_size,height-font_size);
    //   cairo_move_to(cr,3*font_size,height-font_size);
    cairo_line_to(cr,width-3*font_size,height-font_size);
    cairo_move_to(cr,width-3*font_size,height-font_size);
    cairo_line_to(cr,width-3*font_size,0);

    //procenti
    cairo_move_to(cr, 0,font_size);
    cairo_set_source_rgb(cr,0,0,0);
    cairo_show_text(cr,"100%");
    cairo_move_to(cr,0,height/4);
    cairo_show_text(cr,"75%");
    cairo_move_to(cr,0,height/4*2);
    cairo_show_text(cr,"50%");
    cairo_move_to(cr,0,height/4*3);
    cairo_show_text(cr,"25%");
    cairo_move_to(cr,0,height-font_size);
    cairo_show_text(cr,"0%");
    cairo_stroke(cr);
    //sekunde
    cairo_move_to(cr,3*font_size,height);
    cairo_show_text(cr,"0 sec");
    cairo_move_to(cr,width/6,height);
    cairo_show_text(cr,"10 sec");
    cairo_move_to(cr,width/6*2,height);
    cairo_show_text(cr,"20 sec");
    cairo_move_to(cr,width/6*3,height);
    cairo_show_text(cr,"30 sec");
    cairo_move_to(cr,width/6*4,height);
    cairo_show_text(cr,"40 sec");
    cairo_move_to(cr,width/6*5,height);
    cairo_show_text(cr,"50 sec");
    cairo_move_to(cr,width-3*font_size,height);
    cairo_show_text(cr,"60 s");
    cairo_stroke(cr);

// kada stavimo da je gpointer(t) 0 desi se segmantation fault u Garray










       double prev[2]={height-font_size};

    for (int j = 0; j < 60; j++) {

        //cairo_move_to(cr,0,400);

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
            if(*peak==height)
                peak=&height-1;
            prev[r]= height-font_size - *peak;



            if(j==0)
                 cairo_line_to(cr, 3*font_size, height-font_size - *peak);

            cairo_line_to(cr, step+3*font_size, height-font_size - *peak);



            cairo_stroke(cr);
        }
        cairo_translate(cr, step, 0);
    }










}
static void do_drawing(GtkWidget *widget,cairo_t *cr){
    /*  int width, height;

      height= gtk_widget_get_allocated_height(graph3);
      width= gtk_widget_get_allocated_width(graph3);*/
    //

    // cairo_surface_t *graph_surface;
    // graph_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 400, 400);
    // cr = cairo_create (graph_surface);
    //

    printf("%f width %f height\n",width,height);
    //   cairo_set_source_rgb(cr,1,.05,1);
    cairo_set_line_width(cr,1);


    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
    //  cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);


    gfloat *peak;

    double font_size=12;
    double step =(width-3*font_size-3*font_size)/60;

    cairo_set_font_size(cr, font_size);


    //procent linije
    cairo_set_source_rgba(cr,.7,.7,.7,0.5);
    cairo_move_to(cr,0,height/4);//75%
    cairo_line_to(cr,width-3*font_size,height/4);
    cairo_move_to(cr,0,height/4*2);//50
    cairo_line_to(cr,width-3*font_size,height/4*2);
    cairo_move_to(cr,0,height/4*3);//25
    cairo_line_to(cr,width-3*font_size,height/4*3);
    //secund linije

    cairo_move_to(cr,step*10+3*font_size,height);
    cairo_line_to(cr,step*10+3*font_size,0);
    for(int i=2 ;i<=5;i++){
        cairo_move_to(cr,step*10*i+3*font_size,height-font_size);
        cairo_line_to(cr,step*10*i+3*font_size,0);
    }



    /* cairo_move_to(cr,(width-3*font_size)/6*3,height);
     cairo_line_to(cr,(width-3*font_size)/6*3,0);

     cairo_move_to(cr,(width-3*font_size)/6*4,height);
     cairo_line_to(cr,(width-3*font_size)/6*4,0);

     cairo_move_to(cr,(width-3*font_size)/6*5,height);
     cairo_line_to(cr,(width-3*font_size)/6*5,0);*/



    cairo_stroke(cr);
    //okvir
    cairo_move_to(cr,3*font_size,0);
    cairo_line_to(cr,width-3*font_size,0);
    cairo_move_to(cr,3*font_size,0);
    cairo_line_to(cr,3*font_size,height-font_size);
    //   cairo_move_to(cr,3*font_size,height-font_size);
    cairo_line_to(cr,width-3*font_size,height-font_size);
    cairo_move_to(cr,width-3*font_size,height-font_size);
    cairo_line_to(cr,width-3*font_size,0);

    //procenti
    cairo_move_to(cr, 0,font_size);
    cairo_set_source_rgb(cr,0,0,0);
    cairo_show_text(cr,"100%");
    cairo_move_to(cr,0,height/4);
    cairo_show_text(cr,"75%");
    cairo_move_to(cr,0,height/4*2);
    cairo_show_text(cr,"50%");
    cairo_move_to(cr,0,height/4*3);
    cairo_show_text(cr,"25%");
    cairo_move_to(cr,0,height-font_size);
    cairo_show_text(cr,"0%");
    cairo_stroke(cr);
    //sekunde
    cairo_move_to(cr,3*font_size,height);
    cairo_show_text(cr,"0 sec");
    cairo_move_to(cr,width/6,height);
    cairo_show_text(cr,"10 sec");
    cairo_move_to(cr,width/6*2,height);
    cairo_show_text(cr,"20 sec");
    cairo_move_to(cr,width/6*3,height);
    cairo_show_text(cr,"30 sec");
    cairo_move_to(cr,width/6*4,height);
    cairo_show_text(cr,"40 sec");
    cairo_move_to(cr,width/6*5,height);
    cairo_show_text(cr,"50 sec");
    cairo_move_to(cr,width-3*font_size,height);
    cairo_show_text(cr,"60 s");
    cairo_stroke(cr);

// kada stavimo da je gpointer(t) 0 desi se segmantation fault u Garray









    double prev[2]={height-font_size,height-font_size};

    for (int j = 0; j < 60; j++) {

        //cairo_move_to(cr,0,400);
        for(int r=0;r<=1;r++) {

            if(j==0)
                prev[r]=height-font_size;

            cairo_move_to(cr,3*font_size,prev[r]);

            if(r==0){
                peak = &g_array_index(history[4], gfloat, j);
                cairo_set_source_rgb(cr,1,0,0);
            }
            if(r==1){
                peak = &g_array_index(history[5], gfloat, j);

                cairo_set_source_rgba(cr,1,.5,1,.5);
            }
           /* if(*peak==height)
                peak=&height-1;*/
            prev[r]= height-font_size - *peak;

            if(j==0)
                cairo_line_to(cr, 3*font_size, height-font_size - *peak);

            cairo_line_to(cr, step+3*font_size, height-font_size - *peak);





            cairo_stroke(cr);


        }
        cairo_translate(cr, step, 0);

    }









}

static void do_drawing2(GtkWidget *widget,cairo_t *cr){

    cairo_set_line_width(cr,1);


    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
    //  cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);

    gfloat *peak;
   double font_size=12;
    double step =(width-3*font_size-3*font_size)/60;

    cairo_set_font_size(cr, font_size);


    //procent linije
    cairo_set_source_rgba(cr,.7,.7,.7,0.5);
    cairo_move_to(cr,0,height/4);//75%
    cairo_line_to(cr,width-3*font_size,height/4);
    cairo_move_to(cr,0,height/4*2);//50
    cairo_line_to(cr,width-3*font_size,height/4*2);
    cairo_move_to(cr,0,height/4*3);//25
    cairo_line_to(cr,width-3*font_size,height/4*3);
    //secund linije

    cairo_move_to(cr,step*10+3*font_size,height);
    cairo_line_to(cr,step*10+3*font_size,0);
    for(int i=2 ;i<=5;i++){
        cairo_move_to(cr,step*10*i+3*font_size,height-font_size);
        cairo_line_to(cr,step*10*i+3*font_size,0);
    }



   /* cairo_move_to(cr,(width-3*font_size)/6*3,height);
    cairo_line_to(cr,(width-3*font_size)/6*3,0);

    cairo_move_to(cr,(width-3*font_size)/6*4,height);
    cairo_line_to(cr,(width-3*font_size)/6*4,0);

    cairo_move_to(cr,(width-3*font_size)/6*5,height);
    cairo_line_to(cr,(width-3*font_size)/6*5,0);*/



    cairo_stroke(cr);
    //okvir
    cairo_set_source_rgb(cr,0,0,0);
    cairo_move_to(cr,3*font_size,0);
    cairo_line_to(cr,width-3*font_size,0);
    cairo_move_to(cr,3*font_size,0);
    cairo_line_to(cr,3*font_size,height-font_size);
 //   cairo_move_to(cr,3*font_size,height-font_size);
    cairo_line_to(cr,width-3*font_size,height-font_size);
    cairo_move_to(cr,width-3*font_size,height-font_size);
    cairo_line_to(cr,width-3*font_size,0);

    //procenti
    cairo_move_to(cr, 0,font_size);

    cairo_show_text(cr,"100%");
    cairo_move_to(cr,0,height/4);
    cairo_show_text(cr,"75%");
    cairo_move_to(cr,0,height/4*2);
    cairo_show_text(cr,"50%");
    cairo_move_to(cr,0,height/4*3);
    cairo_show_text(cr,"25%");
    cairo_move_to(cr,0,height-font_size);
    cairo_show_text(cr,"0%");
    cairo_stroke(cr);
    //sekunde
    cairo_move_to(cr,3*font_size,height);
    cairo_show_text(cr,"0 sec");
    cairo_move_to(cr,width/6,height);
    cairo_show_text(cr,"10 sec");
    cairo_move_to(cr,width/6*2,height);
    cairo_show_text(cr,"20 sec");
    cairo_move_to(cr,width/6*3,height);
    cairo_show_text(cr,"30 sec");
    cairo_move_to(cr,width/6*4,height);
    cairo_show_text(cr,"40 sec");
    cairo_move_to(cr,width/6*5,height);
    cairo_show_text(cr,"50 sec");
    cairo_move_to(cr,width-3*font_size,height);
    cairo_show_text(cr,"60 s");
    cairo_stroke(cr);

     double prev[4]={height-font_size,height-font_size,height-font_size,height-font_size};


    for (int j = 0; j <60; j++) {


        for(int r=0;r<=3;r++) {




            cairo_move_to(cr,2+3*font_size,prev[r]);


            peak = &g_array_index(history[r], gfloat, j);
            printf("PREV %4.0f,PEAK %4.0f)\n",prev[r] ,*peak);
            prev[r]= height-font_size - *peak;



            cairo_line_to(cr, step+3*font_size, height-font_size - *peak);



            if(r==0)
                cairo_set_source_rgba(cr,0.5,0.5,0.5,.5);
            if(r==1)
                cairo_set_source_rgba(cr,1,.5,1,.5);
            if(r==2)
                cairo_set_source_rgba(cr,.4,.5,1,.5);
            if(r==3)
                cairo_set_source_rgba(cr,0,0,0,.5);
            cairo_stroke(cr);


        }
        cairo_translate(cr, step, 0);

    }



}
static gboolean network_change_ts(gpointer data){



    float net1= net.transmited_bytes;
    float net_kb = net.transmited_kb;
    static guint i =0;
    printf("STO NECE: %f",net1);
    g_array_insert_val(history[5], i, net_kb);



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
    g_array_insert_val(history[4], i, net_kb);



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
    j=(height/100)*j;
    
    g_array_insert_val(history[6], i, j);



    memory_usage_text = g_strdup_printf (("Memory: %d%%"),memory_usage.percentage);
    gtk_label_set_text (GTK_LABEL (data), memory_usage_text);
}
static gboolean swap_change(gpointer data){



    //get_memory_usage();


    static int i =0;
    gfloat  j = memory_usage.swap_used;

    g_array_insert_val(history[7], i, j);
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
    static guint g=0;
    gfloat j;
    g++;
   /* if(g==60)
        exit(1);*/
    printf("%d bjorg\n",g);
    gfloat *peak;
    for(int s=0;s<=ncpu;s++) {

        j = cpu[s].percentage;
        j=(height/100)*j;

        g_array_insert_val(history[s], i, j);



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
   // time_handler(graph2);

}
 void init_timeout(){

    // guint g =i;
   // printf("%d %d \n",i ,g);
     percent_ffs();
     get_memory_usage();
     measurements();

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

    for (int i = 0; i < 8; i++) {
    history[i] = g_array_new(FALSE, TRUE, sizeof(gfloat));
    g_array_set_size(history[i], 300);
}
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);

    button =gtk_button_new_with_label("refresh rate");
    button2 =gtk_button_new_with_label("refresh rate2");

    graph1 = gtk_drawing_area_new();
    graph2 = gtk_drawing_area_new();
    graph3 = gtk_drawing_area_new();
    graph4 = gtk_drawing_area_new();


    gtk_widget_set_size_request(graph1,800,400);
    gtk_widget_set_size_request(graph2,800,400);
    gtk_widget_set_size_request(graph3,800,400);
    gtk_widget_set_size_request(graph4,800,400);

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
   gtk_box_pack_start(GTK_BOX(hbox),button3,0,0,0);
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
    g_signal_connect(button3,"clicked", G_CALLBACK(button_clicked3), NULL);
    g_signal_connect(G_OBJECT(graph1), "draw",
                     G_CALLBACK(on_draw_event),(gpointer)1);
    g_signal_connect(G_OBJECT(graph2), "draw",
                     G_CALLBACK(on_draw_event),(gpointer)2);
    g_signal_connect(G_OBJECT(graph3), "draw",
                     G_CALLBACK(on_draw_event),(gpointer)3);
    g_signal_connect(G_OBJECT(graph4), "draw",
                     G_CALLBACK(on_draw_event),(gpointer)4);





    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1600, 600);
    //gtk_window_get_resizable (window);
    init_timeout();
    g_timeout_add(1000,(GSourceFunc)init_timeout2,NULL);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_window_set_title(GTK_WINDOW(window), "lines mother do you see it ");


    gtk_widget_show_all(window);



    gtk_main();

    return 0;
}
