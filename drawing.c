//
// Created by dushn on 8.9.17..
//

#include "drawing.h"

static gfloat max_broj3=0;
static char *track;


cairo_t * crtaj_sekunde(cairo_t *cr,float width,float height,float font_size,int i){
   cairo_set_source_rgb(cr,0,0,0);
    cairo_move_to(cr,i*font_size,height);
    cairo_show_text(cr,"0 sec");
    cairo_move_to(cr,(width-6*font_size)/6+i*font_size,height);
    cairo_show_text(cr,"10 sec");
    cairo_move_to(cr,(width-6*font_size)/6*2+i*font_size,height);
    cairo_show_text(cr,"20 sec");
    cairo_move_to(cr,(width-6*font_size)/6*3+i*font_size,height);
    cairo_show_text(cr,"30 sec");
    cairo_move_to(cr,(width-6*font_size)/6*4+i*font_size,height);
    cairo_show_text(cr,"40 sec");
    cairo_move_to(cr,(width-6*font_size)/6*5+i*font_size,height);
    cairo_show_text(cr,"50 sec");
    cairo_move_to(cr,width-i*font_size,height);
    cairo_show_text(cr,"60 s");
    cairo_stroke(cr);

    cairo_set_source_rgba(cr,.7,.7,.7,0.5);
    for(int j =1;j<=5;j++){
        cairo_move_to(cr,(width-2*i*font_size)/6*j+i*font_size,height-font_size);
        cairo_line_to(cr,(width-2*i*font_size)/6*j+i*font_size,0);
    }
cairo_stroke(cr);
    return cr;

}

cairo_t * crtaj_okvir(cairo_t *cr,float width,float height,float font_size,int i){



    //okvir
    cairo_set_source_rgb(cr,0,0,0);
  /*  cairo_move_to(cr,i*font_size,0);
    cairo_line_to(cr,width-i*font_size,0);
    cairo_move_to(cr,i*font_size,0);
    cairo_line_to(cr,i*font_size,height-font_size);
    //   cairo_move_to(cr,3*font_size,height-font_size);
    cairo_line_to(cr,width-i*font_size,height-font_size);
    cairo_move_to(cr,width-i*font_size,height-font_size);
    cairo_line_to(cr,width-i*font_size,0);*/
    cairo_rectangle(cr,i*font_size,height-font_size,width-2*i*font_size,-height+font_size);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgba (cr, 1.0, 0.43, 0.0, 0.3);
    cairo_fill(cr);
    //procent linije
    cairo_set_source_rgba(cr,.7,.7,.7,0.5);
    cairo_move_to(cr,i*font_size,height/4);//75%
    cairo_line_to(cr,width-i*font_size,height/4);
    cairo_move_to(cr,i*font_size,height/4*2);//50
    cairo_line_to(cr,width-i*font_size,height/4*2);
    cairo_move_to(cr,i*font_size,height/4*3);//25
    cairo_line_to(cr,width-i*font_size,height/4*3);
    cairo_stroke(cr);
    return cr;


};
cairo_t * crtaj_procente(cairo_t *cr,gfloat height,gfloat font_size){

    cairo_set_source_rgb(cr,0,0,0);
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
    return cr;
};
cairo_surface_t *crtaj_surface(cairo_t *cr,int width, int height){
    cairo_surface_t *graph_surface;


    graph_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create (graph_surface);


    cairo_destroy(cr);
    return graph_surface;

}
cairo_t *  crtaj_interrupte(cairo_t *cr,int i,Interrupts *peak,float height,float font_size,long max_broj,float duzina){

    gfloat procent=0;
    cairo_set_line_width(cr,1);
    procent=((height-font_size)/max_broj)* peak->CPU0;
    cairo_rectangle(cr, 5 * font_size+5*duzina*i , height-font_size, duzina-1, -procent);
    cairo_set_source_rgb(cr,0,0,0);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr,1,0,0);
    cairo_fill(cr);
    procent=((height-font_size)/max_broj)* peak->CPU1;
    cairo_rectangle(cr, 5 * font_size+duzina*(5*i+1)  , height-font_size, duzina-1, -procent);
    cairo_set_source_rgb(cr,0,0,0);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr,0,1,0);
    cairo_fill(cr);
    procent=((height-font_size)/max_broj)* peak->CPU2;
    cairo_rectangle(cr, 5 * font_size +duzina*(5*i+2) , height-font_size, duzina-1, -procent);
    cairo_set_source_rgb(cr,0,0,0);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr,0,0,1);
    cairo_fill(cr);
    procent=((height-font_size)/max_broj)* peak->CPU3;
    cairo_rectangle(cr, 5 * font_size+ duzina*(5*i+3) , height-font_size, duzina-1, -procent);
    cairo_set_source_rgb(cr,0,0,0);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr,1,.5,0);
    cairo_fill(cr);
    return cr;

}

//cairo_t *crtanje_graph(cairo_t *cr,GArray *history,int r,int y,int width,int height, gfloat font_size, double step){
cairo_t *crtanje_graph(cairo_t *cr, GArray *history, int r, int y, int i, int height, gfloat font_size, double step){

   // double prev[4]= {height-font_size,height-font_size,height-font_size,height-font_size};
    double prev=height-font_size;

 //
    gfloat *peak;
  //  gfloat step_size;


    if (r == 0 || r==5)

        cairo_set_source_rgb(cr, 1, 0, 0);
    if (r == 1 )
        cairo_set_source_rgb(cr, 0, 1, 0);
    if (r == 2 || r==4)
        cairo_set_source_rgb(cr, 0, 0, 1); //rgb
    if (r == 3)
        cairo_set_source_rgb(cr, 1, .5, 0);


    for (int j = 0; j < y; j++) {




        cairo_move_to(cr, i * font_size, prev);
        //cairo_move_to(cr, 3 * font_size, prev[r]);
        gfloat *peak;
        // peak = &g_array_index(history[r], gfloat, j);
        peak = &g_array_index(history, gfloat, j);

        // int height_temp=height;
        gfloat procent = 0;// = *peak;
        if(r==4 || r==5){
            procent=((height-font_size)/max_broj3)* *peak;
        }
        else {
            procent = ((height - font_size) / 100) * *peak;
        }
        //    printf("PEAK: %0.2f\n",*peak);
        // prev[r]= height-font_size - *peak;
        prev = height - font_size - procent;

        if (procent == height) {
            procent = height - 1;
        }

        cairo_line_to(cr, step + i * font_size, height - font_size - procent);






        //  }
        cairo_translate(cr, step, 0);


    }
    cairo_stroke(cr);
    //vracanje na pocetnu poziciju

        cairo_translate(cr, -step*y, 0);



    return cr;
};

void do_drawing3(GtkWidget *widget,cairo_t *cr,guint bjorg,guint time_step){
    int width, height;
    height= gtk_widget_get_allocated_height(widget);
    width= gtk_widget_get_allocated_width(widget);

    cairo_surface_t *graph_surface;


    //   cairo_set_source_rgb(cr,1,.05,1);
    cairo_set_line_width(cr,1);
    float font_size=12;
    double step =(width-3*font_size-3*font_size)/time_step;

    cairo_set_font_size(cr, font_size);

    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
    //  cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);


//    gfloat *peak;
//    gfloat procent;
//    double prev[2]={height-font_size};


    cairo_set_font_size(cr, font_size);



    //secund linije
    graph_surface= crtaj_surface(cr,width,height);


  //  cairo_stroke(cr);
    //okvir
     crtaj_okvir(cr,width,height,font_size,3);

//procent linije
  //  crtaj_procent_linije(cr, width,height, font_size, 3);

    //procenti
    crtaj_procente(cr,height,font_size);

    //sekunde
    crtaj_sekunde(cr,width,height,font_size,3);


    crtanje_graph(cr, history[6], 0, bjorg, 3, height, font_size, step);
    crtanje_graph(cr, history[7], 2, bjorg, 3, height, font_size, step);


    if (graph_surface != NULL)
    {
        cairo_set_source_surface (cr, graph_surface, 0.0, 0.0);
        cairo_paint (cr);
        cairo_surface_destroy (graph_surface);
    }


}
void do_drawing4(GtkWidget *widget,cairo_t *cr){
    int width, height;
    gchar *ime2;
    long max_broj=0;
    signed long temp=0;
    Interrupts *peak;
    gchar broj[5];
    cairo_surface_t *graph_surface;
    float font_size=10;


    height= gtk_widget_get_allocated_height(widget);
    width= gtk_widget_get_allocated_width(widget);

    cairo_set_line_width(cr,1);
    cairo_set_font_size(cr, font_size);

    graph_surface= crtaj_surface(cr,width,height);
 //   crtaj_procent_linije(cr, width,height, font_size, 5);
     crtaj_okvir(cr,width,height,font_size,5);
    cairo_set_source_rgb(cr,0,0,0);



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
    if (graph_surface != NULL)
    {
        cairo_set_source_surface (cr, graph_surface, 0.0, 0.0);
        cairo_paint (cr);
        cairo_surface_destroy (graph_surface);
    }

};
void do_drawing(GtkWidget *widget,cairo_t *cr,guint bjorg2){
    int width, height;
    gchar *rec;
    gchar broj[5];

    float rec_bytes=0;

    gchar *kb="KB/s";
    gchar *mb="MB/s";
    gchar *b="bytes/s";
    gfloat max_broj=0;
    gfloat max_broj2=0;

    gfloat procent=0;
    gfloat *peak=0;
    float font_size=10;
    height= gtk_widget_get_allocated_height(widget);
    width= gtk_widget_get_allocated_width(widget);

   // double prev[2]={height-font_size,height-font_size};

    float temp;
    double step =(width-5*font_size-5*font_size)/60;


     cairo_surface_t *graph_surface;
    graph_surface= crtaj_surface(cr,width,height);

    cairo_set_line_width(cr,1);


    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
    //  cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);


    cairo_set_font_size(cr, font_size);

//    crtaj_procent_linije(cr, width,height, font_size, 5);
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

    g_free(rec);


    crtanje_graph(cr,history[4],4,bjorg2,5,height,font_size,step);
    crtanje_graph(cr,history[5],5,bjorg2,5,height,font_size,step);

    if (graph_surface != NULL)
    {
        cairo_set_source_surface (cr, graph_surface, 0.0, 0.0);
        cairo_paint (cr);
        cairo_surface_destroy (graph_surface);
    }

}

