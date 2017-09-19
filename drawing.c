//
// Created by dushn on 8.9.17..
//

#include "drawing.h"


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

    //procent linije
    cairo_set_source_rgba(cr,.7,.7,.7,0.5);
    cairo_move_to(cr,i*font_size,height/4);//75%
    cairo_line_to(cr,width-i*font_size,height/4);
    cairo_move_to(cr,i*font_size,height/4*2);//50
    cairo_line_to(cr,width-i*font_size,height/4*2);
    cairo_move_to(cr,i*font_size,height/4*3);//25
    cairo_line_to(cr,width-i*font_size,height/4*3);
    cairo_stroke(cr);

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
    cairo_stroke(cr);
    cairo_set_source_rgba (cr, 1.0, 0.43, 0.0, 0.3);
    cairo_fill_preserve(cr);
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

cairo_t *crtanje_cpu(cairo_t *cr,GArray *history,int r,int y,int width,int height, gfloat font_size, double step){

   // double prev[4]= {height-font_size,height-font_size,height-font_size,height-font_size};
    double prev=height-font_size;

    //cairo_t *cr;
    cairo_surface_t *graph_surface;
    gfloat *peak;
  //  gfloat step_size;





    for (int j = 0; j < y; j++) {




        cairo_move_to(cr, 3 * font_size, prev);
        //cairo_move_to(cr, 3 * font_size, prev[r]);
        gfloat *peak;
        // peak = &g_array_index(history[r], gfloat, j);
        peak = &g_array_index(history, gfloat, j);

        // int height_temp=height;
        gfloat procent = 0;// = *peak;
        procent = ((height - font_size) / 100) * *peak;

        //    printf("PEAK: %0.2f\n",*peak);
        // prev[r]= height-font_size - *peak;
        prev = height - font_size - procent;

        if (procent == height) {
            procent = height - 1;
        }

        cairo_line_to(cr, step + 3 * font_size, height - font_size - procent);


        if (r == 0)

            cairo_set_source_rgb(cr, 1, 0, 0);
        if (r == 1)
            cairo_set_source_rgb(cr, 0, 1, 0);
        if (r == 2)
            cairo_set_source_rgb(cr, 0, 0, 1); //rgb
        if (r == 3)
            cairo_set_source_rgb(cr, 1, .5, 0);



        //  }
        cairo_translate(cr, step, 0);


    }
    cairo_stroke(cr);
    //vracanje na pocetnu poziciju

        cairo_translate(cr, -step*y, 0);



    return cr;
};
