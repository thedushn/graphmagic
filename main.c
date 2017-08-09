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
//int ncpu;
#define NUMBER1 1
#define NUMBER2 2
#define NUMBER3 3
#define NUMBER4 4
struct Memory_usage memory_usage;
struct Cpu_usage cpu;
gchar *text;
gchar *memory_usage_text;
gchar *swap_usage_text;
gchar *cpu_usage_text;
int float_variable;
static GtkWidget *window;
GtkWidget *graph1;
GtkWidget *graph2;
GtkWidget *graph3;
GtkWidget *graph4;
GtkWidget *vbox;
GtkWidget *hbox;
GtkWidget *hbox1;
GtkWidget *hbox2;
GtkWidget *label;
GtkWidget *label1;
GtkWidget *label2;
GtkWidget *button;
GtkWidget *button2;
GArray *history;

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




struct cpu_drawing cpu_drawing1;
static double cpu1;
static void do_drawing2(cairo_t *cr);
static void do_drawing(GtkWidget *widget,cairo_t *cr, double t);
static  gint  i =500;

void button_clicked(){



    i+=200;
    printf("I clicked a button %d", i);
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
    cpu_drawing1.cpu1 += 0.4;
    cpu_drawing1.cpu2 +=2;
    cpu_drawing1.cpu3 +=0.2;
    cpu_drawing1.cpu4 +=0.1;

    if(cpu_drawing1.cpu2 >50)
        cpu_drawing1.cpu2=2;
    gtk_widget_queue_draw(widget);

    return TRUE;
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,gpointer *user_data){
    double t=0.4 ;

  // int data=user_data;
    do_drawing(widget,cr,t);
 /*   cpu_inc();
   switch(data) {
       case 1:
            t=t*memory_usage.percentage;


       case 2:
           t+=cpu_drawing1.cpu2;

           do_drawing(widget,cr,t);
       case 3:
           t=t*cpu_drawing1.cpu3;
           do_drawing(widget,cr,t);
       case 4:
           t=t*cpu_drawing1.cpu4;
           do_drawing(widget,cr,t);
      default:
           t=t+cpu1;

           do_drawing(widget,cr,t);
       }


*/

}


static void do_drawing(GtkWidget *widget,cairo_t *cr,double t){
    int width, height;
   // GtkWidget *win = gtk_widget_get_toplevel(widget);
   // gtk_window_get_size(GTK_WINDOW(win), &width, &height);
    //

   // cairo_surface_t *graph_surface;
   // graph_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 400, 400);
   // cr = cairo_create (graph_surface);
    //


    cairo_set_source_rgb(cr,0.2,0.12,0.3);
    cairo_set_line_width(cr,2);
    int i, j;

    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
   cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);

 int p;
static int g;
gfloat *peak;
    g=cpu_drawing1.cpu2;
    p=cpu.percentage;
    //printf("(%d) sta kaze p \n",p);
  //  g_array


    cairo_move_to(cr,0,400);
    cairo_translate(cr,j,0);
    for(int j =0; j<200;j++){

        //g_array_insert_val(history,j,p);
        peak= &g_array_index(history,gfloat,j);

        printf("peak %f",*peak);
        cairo_line_to(cr,0,400 - *peak);

        cairo_translate(cr,j,0);

    }
    cairo_stroke(cr);
//pomera se linija i izgleda kao grafik ali ne brise kada izadje iz obsega
   /* cairo_move_to(cr,0,0);
    cairo_translate(cr,j,0);
    for(int j =0; j<500;j++){

        //g_array_insert_val(history,j,p);
        peak= &g_array_index(history,gfloat,j);

        printf("peak %f",*peak);
        cairo_line_to(cr,0,*peak);

        cairo_translate(cr,j,0);

    }
    cairo_stroke(cr);*/

    //pomera se linija i cuva se predhodne u nizu  ali pravi preveliki razmak izmedju linija
    /* for(int j =0; j<500;j++){

        //g_array_insert_val(history,j,p);
        peak= &g_array_index(history,gfloat,j);
        cairo_move_to(cr,0,0);
        printf("peak %f",*peak);
        cairo_line_to(cr,0,*peak);

        cairo_translate(cr,j,0);

    }
    cairo_stroke(cr); */

   //pomera se linija ali ne cuva predhodnu nacrtanu liniju
  /*  cairo_move_to(cr,200,0);
        cairo_translate(cr,2+g,0);
    cairo_move_to(cr,200,0);
    cairo_line_to(cr,200,p*3);
    cairo_stroke(cr);
*/






   /* cairo_set_source_rgb(cr,0.42,0.112,0.3);
    for(int j=0;j<1000;j++) {
        cairo_move_to(cr, 200, 0);
        cairo_line_to(cr, 200, j);
        cairo_translate(cr,-2,0);
    }
    cairo_stroke(cr);
   */






    //cairo_move_to(cr,300,200);
    //cairo_line_to(cr,200,100);

   // cairo_translate(cr,-i+10,0);


   //}










}


static gboolean cpu_change(gpointer data){


    cpu_percentage();
    static int i =0;
    gfloat j = cpu.percentage;
    j*=2;
    cpu_usage_text = g_strdup_printf (("CPU: %d%%"),cpu.percentage);
    g_array_insert_val(history,i,j);
    if(i<=200)
        i=0;
    i++;
    j++;
    printf("%d i problems\n",i);
    printf("%f j problems\n",j);
    gtk_label_set_text (GTK_LABEL (data),cpu_usage_text);

};
static gboolean memory_change(gpointer data){


    get_memory_usage();
    memory_usage_text = g_strdup_printf (("Memory: %d%%"),memory_usage.percentage);
    gtk_label_set_text (GTK_LABEL (data), memory_usage_text);
}
static gboolean swap_change(gpointer data){


    get_memory_usage();
    swap_usage_text = g_strdup_printf(("SWAP: %d%%"),memory_usage.swap_used);
    gtk_label_set_text (GTK_LABEL (data), swap_usage_text);
}
 gboolean init_timeout(void){

    // guint g =i;
   // printf("%d %d \n",i ,g);

    g_timeout_add(i,memory_change,label);
    g_timeout_add(i,swap_change,label1);
    g_timeout_add(i,cpu_change,label2);

    g_timeout_add(i,(GSourceFunc) time_handler,window);


};

/*
void restartovanje(gpointer data){


    float percent ;
    percent += 0.05;
    if(percent > 1.0)
        percent = 0.0;
    int percent2 = (int) percent;
    char c[3];
    sprintf(text, "%d%%",  percent2);
    gtk_label_set_text(GTK_LABEL(data),c);

}*/

int main (int argc, char *argv[])
{



    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

 //  ncpu= cpu_number();
    history = g_array_new(FALSE,TRUE, sizeof(gint));
    g_array_set_size(history,500);

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
    label= gtk_label_new(NULL);
    label1= gtk_label_new(NULL);
    label2= gtk_label_new(NULL);

    hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(vbox),hbox,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);

    gtk_box_pack_start(GTK_BOX(vbox),label,1,TRUE,0);


    gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,FALSE);
   gtk_box_pack_start(GTK_BOX(hbox),button2,0,0,0);


    hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    gtk_box_pack_start(GTK_BOX(vbox),hbox1,1,TRUE,0);

    gtk_box_pack_start(GTK_BOX(hbox1),graph1,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),label1,1,TRUE,0);

    vseparator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(hbox1),vseparator,1,TRUE,0);

    gtk_box_pack_start(GTK_BOX(hbox1),graph2,1,TRUE,0);
    hseparator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_box_pack_start(GTK_BOX(vbox),hseparator,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),label2,1,TRUE,0);


    hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,1);
    gtk_box_pack_start(GTK_BOX(vbox),hbox2,1,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox2),graph3,1,TRUE,0);

    vseparator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
    gtk_box_pack_start(GTK_BOX(hbox2),vseparator,1,TRUE,0);

    gtk_box_pack_start(GTK_BOX(hbox2),graph4,1,TRUE,0);




    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(button,"clicked", G_CALLBACK(button_clicked), NULL);
    g_signal_connect(button2,"clicked", G_CALLBACK(button_clicked), NULL);
    g_signal_connect(G_OBJECT(graph1), "draw",
                     G_CALLBACK(on_draw_event),NULL);
    g_signal_connect(G_OBJECT(graph2), "draw",
                     G_CALLBACK(on_draw_event),NULL);
    g_signal_connect(G_OBJECT(graph3), "draw",
                     G_CALLBACK(on_draw_event),NULL);
    g_signal_connect(G_OBJECT(graph4), "draw",
                     G_CALLBACK(on_draw_event),NULL);





    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 800);
    init_timeout();
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_window_set_title(GTK_WINDOW(window), "lines mother do you see it ");


    gtk_widget_show_all(window);



    gtk_main();

    return 0;
}
