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

struct Memory_usage memory_usage;
struct Cpu_usage cpu[4];
struct Network net;
gchar *text;
gchar *memory_usage_text;
gchar *swap_usage_text;
gchar *cpu_usage_text;
gchar *network_usage_received_text;
gchar *network_usage_transimited_text;
static char *track;
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
GtkWidget *grid;
GtkWidget *frame1;
GtkWidget *frame2;
GtkWidget *frame3;
GtkWidget *frame4;

GtkWidget *button;
GtkWidget *button2;
GtkWidget *button3;
GArray *history[9];



GtkWidget *vseparator;
GtkWidget *hseparator;


void init_timeout();
void init_timeout2();
void timeout_refresh();
void measurements();







static void do_drawing(GtkWidget *widget,cairo_t *cr, int l);
static void do_drawing2(GtkWidget *widget,cairo_t *cr, int l);
static void do_drawing3(GtkWidget *widget,cairo_t *cr, int l);
static gboolean network_change_rc(gpointer data);
static gboolean network_change_ts(gpointer data);
void percent_ffs();
void button_clicked3();
static  guint  t =250;
  static  guint bjorg=1;//prvi ispis
    static guint bjorg2=1;
gboolean refresh=0;
int width2,height2;

static int time_step=0;
void button_clicked3(){





}

void measurements(){


    height2= gtk_widget_get_allocated_height(hbox2);
    width2= gtk_widget_get_allocated_width(hbox2);

}
void button_clicked(){

    if(t>=10000){

        t=10000;
    }
    else
    t+=250;
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
        t-=250;
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

   int data;
   data= GPOINTER_TO_INT(user_data);


    if(widget==graph1){

        do_drawing2(widget,cr,data);
    }
    if(widget==graph2){

        do_drawing(widget,cr,data);
    }
    if(widget==graph3){

        do_drawing3(widget,cr,data);
    }
    if(widget==graph4){

        do_drawing(widget,cr,data);
    }






}

static void do_drawing3(GtkWidget *widget,cairo_t *cr,int l){
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

    for(int i =1;i<=5;i++){
        cairo_move_to(cr,(width-2*3*font_size)/6*i+3*font_size,height-font_size);
        cairo_line_to(cr,(width-2*3*font_size)/6*i+3*font_size,0);
    }



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
    cairo_move_to(cr,(width-6*font_size)/6+3*font_size,height);
    cairo_show_text(cr,"10 sec");
    cairo_move_to(cr,(width-6*font_size)/6*2+3*font_size,height);
    cairo_show_text(cr,"20 sec");
    cairo_move_to(cr,(width-6*font_size)/6*3+3*font_size,height);
    cairo_show_text(cr,"30 sec");
    cairo_move_to(cr,(width-6*font_size)/6*4+3*font_size,height);
    cairo_show_text(cr,"40 sec");
    cairo_move_to(cr,(width-6*font_size)/6*5+3*font_size,height);
    cairo_show_text(cr,"50 sec");
    cairo_move_to(cr,width-3*font_size,height);
    cairo_show_text(cr,"60 s");
    cairo_stroke(cr);











    double prev[2]={height-font_size};

    for (int j = 0; j < bjorg; j++) {

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
            gfloat procent =*peak;
            procent=((height-font_size)/100)*procent;

            printf("PEAK: %0.2f\n",*peak);
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
static void do_drawing(GtkWidget *widget,cairo_t *cr,int l){
    float width, height;
     height= gtk_widget_get_allocated_height(widget);
       width= gtk_widget_get_allocated_width(widget);

    /*width=width2/2;
    height=height2/2;*/
/*width= width2;
height= height2;*/

    // cairo_surface_t *graph_surface;
    // graph_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 400, 400);
    // cr = cairo_create (graph_surface);
    //

    printf("%f width %f height",width,height);
    printf("%d width2 %d height2\n",width2,height2);
    //   cairo_set_source_rgb(cr,1,.05,1);
    cairo_set_line_width(cr,1);


    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
    //  cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);


    gfloat *peak;

    float font_size=10;
    double step =(width-5*font_size-5*font_size)/60;

    cairo_set_font_size(cr, font_size);


    //procent linije
    cairo_set_source_rgba(cr,.7,.7,.7,0.5);
    cairo_move_to(cr,5*font_size,height/4);//75%
    cairo_line_to(cr,width-5*font_size,height/4);
    cairo_move_to(cr,5*font_size,height/4*2);//50
    cairo_line_to(cr,width-5*font_size,height/4*2);
    cairo_move_to(cr,5*font_size,height/4*3);//25
    cairo_line_to(cr,width-5*font_size,height/4*3);
    //secund linije

    cairo_move_to(cr,step*10+5*font_size,height);
    cairo_line_to(cr,step*10+5*font_size,0);
    for(int i=2 ;i<=5;i++){
        cairo_move_to(cr,step*10*i+5*font_size,height-font_size);
        cairo_line_to(cr,step*10*i+5*font_size,0);
    }






    cairo_stroke(cr);
    //okvir
    cairo_move_to(cr,5*font_size,0);
    cairo_line_to(cr,width-5*font_size,0);
    cairo_move_to(cr,5*font_size,0);
    cairo_line_to(cr,5*font_size,height-font_size);
    //   cairo_move_to(cr,3*font_size,height-font_size);
    cairo_line_to(cr,width-5*font_size,height-font_size);
    cairo_move_to(cr,width-5*font_size,height-font_size);
    cairo_line_to(cr,width-5*font_size,0);

    //procenti
    char *rec;
    char *broj;
    float big_bytes;
    float rec_bytes;

    char *kb="kb/s";
    char *mb="mb/s";
    char *b="b/s";
      gfloat max_broj=0;
    gfloat max_broj3=0;

    rec=g_strdup_printf("%s",net.network_size_rc);

    /*if(0==strcmp(rec,mb)){


        track=rec;
    }*/

     float max_broj2;
   /* for(int i=0;i<bjorg2;i++){

        peak = &g_array_index(history[4], gfloat, i);// kb
        if(max_broj2>=*peak){

            max_broj2=*peak;

        }


    }

    if(max_broj<=max_broj2){


       max_broj==max_broj2;
    }
*/  for(int j=4; j<=5;j++) {
        for (int i = 0; i < bjorg2; i++) {

            peak = &g_array_index(history[j], gfloat, i);// kb
            if (max_broj2 <= *peak) {

                max_broj2 = *peak;
            }
        }
    }
        if(max_broj<=max_broj2){

            max_broj=max_broj2;


            printf("MAX_borj peak : %f\n",*peak);
            printf("MAX_borj : %f\n",max_broj);
        }



    float temp;
    cairo_set_source_rgb(cr,0,0,0);

    if(max_broj>1024){


        rec_bytes = max_broj / 1024;//mb
        rec_bytes += 1;
        track=mb;
        max_broj3=max_broj+1024;

    }
    if(max_broj<=1024 && max_broj >1){

        rec_bytes = max_broj;//kb

        rec_bytes+=100;
        track=kb;
        max_broj3=max_broj+100;


    }
    if(max_broj<=1){

        rec_bytes= max_broj*1024;//bytes

        track=rec;
        track=b;
        max_broj3=max_broj+1024;

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


cairo_stroke(cr);














    //sekunde
    cairo_move_to(cr,5*font_size,height);
    cairo_show_text(cr,"0 sec");
    cairo_move_to(cr,(width-8*font_size)/6+5*font_size,height);
    cairo_show_text(cr,"10 sec");
    cairo_move_to(cr,(width-8*font_size)/6*2+5*font_size,height);
    cairo_show_text(cr,"20 sec");
    cairo_move_to(cr,(width-8*font_size)/6*3+5*font_size,height);
    cairo_show_text(cr,"30 sec");
    cairo_move_to(cr,(width-8*font_size)/6*4+5*font_size,height);
    cairo_show_text(cr,"40 sec");
    cairo_move_to(cr,(width-8*font_size)/6*5+5*font_size,height);
    cairo_show_text(cr,"50 sec");
    cairo_move_to(cr,width-5*font_size,height);
    cairo_show_text(cr,"60 s");
    cairo_stroke(cr);



    gfloat procent=0;

    double prev[2]={height-font_size,height-font_size};

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

            printf("PEAK: %0.2f\n",*peak);
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

static void do_drawing2(GtkWidget *widget,cairo_t *cr,int l){
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

    for(int i =1;i<=5;i++){
    cairo_move_to(cr,(width-2*3*font_size)/6*i+3*font_size,height-font_size);
    cairo_line_to(cr,(width-2*3*font_size)/6*i+3*font_size,0);
    }
    /*cairo_move_to(cr,(width)/6+3*font_size,height-font_size);
    cairo_line_to(cr,(width-6*font_size)/5+3*font_size,0);
    cairo_move_to(cr,(width-6*font_size)/5*2+3*font_size,height-font_size);
    cairo_line_to(cr,(width-6*font_size)/5*2+3*font_size,0);
    cairo_move_to(cr,(width-6*font_size)/5*3+3*font_size,height-font_size);
    cairo_line_to(cr,(width-6*font_size)/5*3+3*font_size,0);*/
  /*  for(int i=2 ;i<=5;i++){
        cairo_move_to(cr,(width-6*font_size)/5*i,height-font_size);
        cairo_line_to(cr,(width-6*font_size)/5*i,height-font_size);
    }
*/


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
    cairo_move_to(cr,(width-6*font_size)/6+3*font_size,height);
    cairo_show_text(cr,"10 sec");
    cairo_move_to(cr,(width-6*font_size)/6*2+3*font_size,height);
    cairo_show_text(cr,"20 sec");
    cairo_move_to(cr,(width-6*font_size)/6*3+3*font_size,height);
    cairo_show_text(cr,"30 sec");
    cairo_move_to(cr,(width-6*font_size)/6*4+3*font_size,height);
    cairo_show_text(cr,"40 sec");
    cairo_move_to(cr,(width-6*font_size)/6*5+3*font_size,height);
    cairo_show_text(cr,"50 sec");
    cairo_move_to(cr,width-3*font_size,height);
    cairo_show_text(cr,"60 s");
    cairo_stroke(cr);


     double prev[4]={height-font_size,height-font_size,height-font_size,height-font_size};

    for (int j = 0; j < bjorg; j++) {

        //cairo_move_to(cr,0,400);
        for(int r=0;r<=3;r++) {


            cairo_move_to(cr,3*font_size,prev[r]);

            peak = &g_array_index(history[r], gfloat, j);

           // int height_temp=height;
            gfloat procent =*peak;
            procent=((height-font_size)/100)*procent;

        //    printf("PEAK: %0.2f\n",*peak);
           // prev[r]= height-font_size - *peak;
            prev[r]= height-font_size - procent;
            if(procent==height) {
                procent = height - 1;
            }
            cairo_line_to(cr, step+3*font_size, height-font_size - procent);



            if(r==0)
                cairo_set_source_rgb(cr,0,0,1);
            if(r==1)
                cairo_set_source_rgb(cr,0,1,0);
            if(r==2)
                cairo_set_source_rgb(cr,1,0,0);
            if(r==3)
                cairo_set_source_rgb(cr,0,0,0);
            cairo_stroke(cr);


        }
        cairo_translate(cr, step, 0);

    }



}
static gboolean network_change_ts(gpointer data){



    float net1= net.transmited_bytes;
    float net_kb = net.transmited_kb;
    static guint i =0;
    bjorg2++;

    if(bjorg2>=60){


        bjorg2=60;
    }
   // printf("STO NECE: %f",net1);
    g_array_insert_val(history[5], i, net_kb);



    network_usage_transimited_text =g_strdup_printf("TRANSMITED: %2.f %s",net.transmited_bytes,net.network_size_ts);

    gtk_label_set_text (GTK_LABEL (data),network_usage_transimited_text);

}
static gboolean network_change_rc(gpointer data){


   // received_transfered();
    float net1= net.received_bytes;
    float net_kb = net.received_kb;
   // net_kb/=100;
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

    g_array_insert_val(history[6], i, j);
    bjorg++;
   time_step=60000/t;
    printf("Time step: %d\n",time_step);
    if(bjorg>=time_step){

        bjorg=time_step;
    }


    memory_usage_text = g_strdup_printf (("Memory: %0.2f%%"),memory_usage.percentage);
    gtk_label_set_text (GTK_LABEL (data), memory_usage_text);
}
static gboolean swap_change(gpointer data){



    //get_memory_usage();


    static int i =0;
    gfloat  j = memory_usage.swap_used;

    g_array_insert_val(history[7], i, j);
    swap_usage_text = g_strdup_printf(("SWAP: %lu%%"),memory_usage.swap_used);
    gtk_label_set_text (GTK_LABEL (data), swap_usage_text);
}
/*void ninja(){


    g_timeout_add(t,memory_change,label);
    g_timeout_add(t,swap_change,label1);
   // g_timeout_add(t,cpu_change,label2);
    g_timeout_add(t,cpu_change,label3);
    g_timeout_add(t,cpu_change,label4);
    g_timeout_add(t,cpu_change,label5);
    g_timeout_add(t,cpu_change,label6);



}*/
void percent_ffs(){


    cpu_percentage(ncpu);
    static guint i= 0;
    gfloat j;
    gfloat *peak;
    for(int s=0;s<ncpu;s++) {

        j = cpu[s].percentage;
     //   j=4*j;

        g_array_insert_val(history[s], i, j);
        peak=&g_array_index(history[s],gfloat,i);

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
   /* time_handler(graph2);
    time_handler(graph4);*/


}
 void init_timeout(){

     measurements();
     percent_ffs();
     get_memory_usage();

     interrupt_usage();

    cpu_change(label1);
    cpu_change(label3);
    cpu_change(label4);
    cpu_change(label5);
    cpu_change(label6);
     memory_change(label);
     swap_change(label1);
   /* time_handler(graph1);
    time_handler(graph3);*/
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
    g_array_set_size(history[i], 60);
}
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);

    button =gtk_button_new_with_label("refresh rate");
    button2 =gtk_button_new_with_label("refresh rate");

    graph1 = gtk_drawing_area_new();
    graph2 = gtk_drawing_area_new();
    graph3 = gtk_drawing_area_new();
    graph4 = gtk_drawing_area_new();




  //  gtk_widget_set_size_request(graph1,800,400);
   /* gtk_widget_set_size_request(graph2,800,400);
    gtk_widget_set_size_request(graph3,800,400);
    gtk_widget_set_size_request(graph4,800,400);
*/


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



    hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    //gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hseparator,0,0,0);
  //  gtk_box_pack_start(GTK_BOX(vbox),hbox3,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox3,0,FALSE,0);
    hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    //frame testing
   // gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox3),label,0,FALSE,0);
    gtk_box_pack_start(GTK_BOX(hbox3),label1,0,FALSE,1);
  //  gtk_box_pack_start(GTK_BOX(hbox3),label2,1,TRUE,0);
  //  gtk_box_pack_start(GTK_BOX(hbox3),label6,1,TRUE,0);




    vseparator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
 //testing frames

   // gtk_box_pack_start(GTK_BOX(hbox1),vseparator,1,TRUE,0);
    frame2=gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(frame2),graph2);

    gtk_box_pack_start(GTK_BOX(hbox1),frame2,1,TRUE,0);
    // gtk_box_pack_start(GTK_BOX(hbox1),graph2,1,TRUE,0);
    //
    hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);

  //testing
  //  gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);


    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    gtk_box_pack_start(GTK_BOX(vbox),hbox2,1,TRUE,0);
    //testing frames
    frame3=gtk_frame_new(NULL);
    frame4=gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(frame3),graph3);
    gtk_container_add(GTK_CONTAINER(frame4),graph4);
    gtk_box_pack_start(GTK_BOX(hbox2),frame3,1,TRUE,0);


    vseparator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
  //testing frames
    //gtk_box_pack_start(GTK_BOX(hbox2),vseparator,1,TRUE,0);


    gtk_box_pack_start(GTK_BOX(hbox2),frame4,1,TRUE,0);




    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(button,"clicked", G_CALLBACK(button_clicked), NULL);
    g_signal_connect(button2,"clicked", G_CALLBACK(button_clicked2), NULL);
    g_signal_connect(button3,"clicked", G_CALLBACK(button_clicked3), NULL);
    g_signal_connect(G_OBJECT(graph1), "draw",
                     G_CALLBACK(on_draw_event),NULL);
    g_signal_connect(G_OBJECT(graph2), "draw",
                     G_CALLBACK(on_draw_event),NULL);
    g_signal_connect(G_OBJECT(graph3), "draw",
                     G_CALLBACK(on_draw_event),NULL);
    g_signal_connect(G_OBJECT(graph4), "draw",
                     G_CALLBACK(on_draw_event),NULL);





    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 1400, 800);
  //  gtk_window_get_resizable (window);
    measurements();
    init_timeout();
    g_timeout_add(1000,(GSourceFunc)init_timeout2,NULL);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_window_set_title(GTK_WINDOW(window), "lines mother do you see it ");


    gtk_widget_show_all(window);



    gtk_main();

    return 0;
}
