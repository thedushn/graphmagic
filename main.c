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
#define NUMBER1 1
#define NUMBER2 2
#define NUMBER3 3
#define NUMBER4 4
struct Memory_usage memory_usage;
struct Cpu_usage cpu[4];
gchar *text;
gchar *memory_usage_text;
gchar *swap_usage_text;
gchar *cpu_usage_text;
gchar *network_usage_received_text;
gchar *network_usage_transimit_text;
int float_variable;
static GtkWidget *window;
GtkWidget *graph1;
GtkWidget *graph2;
GtkWidget *graph3;
GtkWidget *graph4;
GtkWidget *graph5;
GtkWidget *graph6;
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

GtkWidget *button;
GtkWidget *button2;
GArray *history[8];

gfloat niz[4][200];

GtkWidget *vseparator;
GtkWidget *hseparator;
//int cpu_change(int value);

gboolean init_timeout(void);
 struct cpu_drawing{

    double cpu1;
    double cpu2;
    double cpu3;
    double cpu4;


}cpu_drawing1;



struct Network net;
struct cpu_drawing cpu_drawing1;
static double cpu1;
static void do_drawing2(cairo_t *cr);
static void do_drawing(GtkWidget *widget,cairo_t *cr, int l);
void percent_ffs();
  guint  t =200;

void button_clicked(){



    t+=200;
    printf("I clicked a button %d", t);
    init_timeout();


};
void cpu_inc(void){

    cpu_drawing1.cpu1 += 1;
    cpu_drawing1.cpu2 +=0.5;
    cpu_drawing1.cpu3 +=0.2;
    cpu_drawing1.cpu4 +=0.1;

    if(cpu_drawing1.cpu1 >5)
        cpu_drawing1.cpu1=1;

}
static gboolean time_handler(GtkWidget *widget)
{
    /*cpu_drawing1.cpu1 += 0.4;
    cpu_drawing1.cpu2 +=2;
    cpu_drawing1.cpu3 +=0.2;
    cpu_drawing1.cpu4 +=0.1;

    if(cpu_drawing1.cpu2 >50)
        cpu_drawing1.cpu2=2;*/


  //  cpu_percentage(ncpu);
    percent_ffs();
    get_memory_usage();
    received_transfered();
    gtk_widget_queue_draw(widget);

    return TRUE;
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,gpointer *user_data){
    double t ;

   int data;
   data= GPOINTER_TO_INT(user_data);


   // percent_ffs();
    do_drawing(widget,cr,data);
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


static void do_drawing(GtkWidget *widget,cairo_t *cr,int l){
    int width, height;
   // GtkWidget *win = gtk_widget_get_toplevel(widget);
   // gtk_window_get_size(GTK_WINDOW(win), &width, &height);
    //

   // cairo_surface_t *graph_surface;
   // graph_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 400, 400);
   // cr = cairo_create (graph_surface);
    //


   // cairo_set_source_rgb(cr,0.2,0.12,0.3);
    cairo_set_line_width(cr,1);
    int j;

    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
   //cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);

 int p;
 int g=ncpu;
gfloat *peak;
   // g=cpu_drawing1.cpu2;
    p=cpu[0].percentage;
    //printf("(%d) sta kaze p \n",p);
  //  g_array

// kada stavimo da je gpointer(t) 0 desi se segmantation fault u Garray
 int i=3;
    //i=l;


       cairo_set_source_rgb(cr,0,0,0);
        cairo_move_to(cr,0,300);
        cairo_line_to(cr,300,350);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr,0,0,0);
    cairo_move_to(cr,0,300);
    cairo_line_to(cr,300,200);

    cairo_stroke_preserve(cr);
    //cairo_set_source_rgb(cr, (0.2 + i) / (i + 1), (0.12 + i) / (i + 1), (0.3 + i) / (i + 1)); //vredosti idu od 0 do 1
    cairo_set_source_rgb(cr,0,0,0);
    cairo_move_to(cr, 0, 400);
        // cairo_translate(cr,j/2,0);
        for (int j = 0; j < 200; j++) {

            //g_array_insert_val(history,j,p);
            peak = &g_array_index(history[6], gfloat, j);
            //   peak = &niz[l-1][j];
            //  printf("niz : %.1f %d \n ",niz[l-1][j],j);
          //  printf("peak1 %.1f\n", *peak);
            cairo_line_to(cr, 0, 400 - *peak);

            cairo_translate(cr, j / 2, 0);

        }
        cairo_stroke_preserve(cr);


       // i=5;
   // cairo_set_source_rgb(cr, (0.2 + i) / (i + 1), (0.12 + i) / (i + 1), (0.3 + i) / (i + 1)); //vredosti idu od 0 do 1
    cairo_set_source_rgb(cr,0.5,1,0.5);
    cairo_set_line_width(cr,5);
    cairo_move_to(cr,0,300);
    cairo_line_to(cr,300,100);
    cairo_stroke_preserve(cr);
    cairo_move_to(cr, 0, 400);
    // cairo_translate(cr,j/2,0);
    for (int j = 0; j < 200; j++) {

        //g_array_insert_val(history,j,p);
        peak = &g_array_index(history[3], gfloat, j);
        //   peak = &niz[l-1][j];
        //  printf("niz : %.1f %d \n ",niz[l-1][j],j);
        //  printf("peak1 %.1f\n", *peak);
        cairo_line_to(cr, 0, 400 - *peak);

        cairo_translate(cr, j / 2, 0);

    }
    printf("CRTAS LI ME \n");
    cairo_stroke(cr);
    printf("CRTAS LI ME1 \n");




}

static gboolean network_change(gpointer data){


   // received_transfered();
    float net1= net.received_bytes;
    float net_kb = net.received_kb;
    net_kb/=100;
    static guint i =0;
    printf("STO NECE: %f",net1);
    g_array_insert_val(history[5], i, net_kb);

    net_kb++;
   // if(i>=200)
        if(i<=200)
        i=0;
    i++;
    network_usage_received_text =g_strdup_printf("RECEIVED: %2.f %s",net.received_bytes,net.network_size);

    gtk_label_set_text (GTK_LABEL (data),network_usage_received_text);
}
static gboolean cpu_change(gpointer data){


    static int g =0;
    //percent_ffs();

    if(g<=4){
    cpu_usage_text = g_strdup_printf (("CPU%d: %2.f%%"),cpu[g].number,cpu[g].percentage);

    g++;


    gtk_label_set_text (GTK_LABEL (data),cpu_usage_text);
        if (g==4)
            g=0;
    }
};
static gboolean memory_change(gpointer data){


    //get_memory_usage();

    static int i =0;
    gfloat  j = memory_usage.percentage;

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
 gboolean init_timeout(void){

    // guint g =i;
   // printf("%d %d \n",i ,g);

     g_timeout_add(1000,network_change,label7);
     ninja();
     g_timeout_add(t,(GSourceFunc) time_handler,window);







  //  g_timeout_add(t,(GSourceFunc) init_timeout,NULL);


};



int main (int argc, char *argv[]) {


    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    ncpu = cpu_number();
    for (int i = 1; i <= 7; i++) {
    history[i] = g_array_new(FALSE, TRUE, sizeof(gfloat));
    g_array_set_size(history[i], 201);
}
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);

    button =gtk_button_new_with_label("refresh rate");
    button2 =gtk_button_new_with_label("refresh rate");

    graph1 = gtk_drawing_area_new();
    graph2 = gtk_drawing_area_new();
    graph3 = gtk_drawing_area_new();
    graph4 = gtk_drawing_area_new();


    gtk_widget_set_size_request(graph1,400,400);
    gtk_widget_set_size_request(graph2,400,400);
    gtk_widget_set_size_request(graph3,400,400);
    gtk_widget_set_size_request(graph4,400,400);

    label= gtk_label_new(NULL);//memory
    label1= gtk_label_new(NULL);//swap
    label2= gtk_label_new(NULL);//CPU
    label3= gtk_label_new(NULL);//cpu1
    label4= gtk_label_new(NULL);//cpu2
    label5= gtk_label_new(NULL);//cpu3
    label6= gtk_label_new(NULL);//cpu4
    label7= gtk_label_new(NULL);//network_received for now


    hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);

   // gtk_box_pack_start(GTK_BOX(vbox),label,1,TRUE,0);


    gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,FALSE);//expand,fill,padding
   gtk_box_pack_start(GTK_BOX(hbox),button2,0,0,0);
   gtk_box_pack_start(GTK_BOX(hbox),label,0,0,0);
    gtk_box_pack_start(GTK_BOX(hbox),label3,0,FALSE,1);
    gtk_box_pack_start(GTK_BOX(hbox),label4,1,TRUE,0);
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
    g_signal_connect(button2,"clicked", G_CALLBACK(button_clicked), NULL);
    g_signal_connect(G_OBJECT(graph1), "draw",
                     G_CALLBACK(on_draw_event),(gpointer)1);
    g_signal_connect(G_OBJECT(graph2), "draw",
                     G_CALLBACK(on_draw_event),(gpointer)5);
    g_signal_connect(G_OBJECT(graph3), "draw",
                     G_CALLBACK(on_draw_event),(gpointer)7);
    g_signal_connect(G_OBJECT(graph4), "draw",
                     G_CALLBACK(on_draw_event),(gpointer)6);





    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    init_timeout();
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_window_set_title(GTK_WINDOW(window), "lines mother do you see it ");


    gtk_widget_show_all(window);



    gtk_main();

    return 0;
}
