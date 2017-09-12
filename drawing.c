//
// Created by dushn on 8.9.17..
//

#include "drawing.h"

static  guint bjorg=1;//prvi ispis
static guint bjorg2=1;
static guint time_step=0;
static char *track;
static void do_drawing(GtkWidget *widget,cairo_t *cr, int l);
static void do_drawing2(GtkWidget *widget,cairo_t *cr, int l);
static void do_drawing3(GtkWidget *widget,cairo_t *cr, int l);
 void do_drawing3(GtkWidget *widget,cairo_t *cr,int l){
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
    double prev[2]={height-font_size};


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
            gfloat procent =*peak;
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
 void do_drawing(GtkWidget *widget,cairo_t *cr,int l){
    float width, height;
    char *rec;
    char *broj;
    float big_bytes;
    float rec_bytes=0;

    char *kb="kb/s";
    char *mb="mb/s";
    char *b="b/s";
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

 void do_drawing2(GtkWidget *widget,cairo_t *cr,int l){
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