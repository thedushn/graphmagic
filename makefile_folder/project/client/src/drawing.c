//
// Created by dushn on 8.9.17..
//

#include <inttypes.h>
#include "drawing.h"
#include <math.h>
#include "main_header.h"


/*void ispis_interrupta_old(cairo_t *cr,double font_size,double duzina,int i,gchar *ime1,gchar *ime2){

    size_t j;
    size_t g=11;//toliko slova moze da stane u jedan red
    int q=0;//koliko redova
    j=strlen(ime1);


    if(g<j){

        j-=g;
        q++;
    }
    if(q==0){

        gchar text_int[g];
        memset(text_int, 0, g);
        cairo_move_to(cr,5 * font_size+5*duzina*i,font_size);//pomerimo ga na pocetnu poziciju

        for(int s=0 ;s<j;s++){

            text_int[s]=ime1[s];
        }
        //  text_int[11]='\0';
        cairo_show_text(cr,text_int);
    }
    if(q>=1){

        for (int r = 0; r <= q; r++) {
            //pomeramo ga u zavisnosti od koliko redova nam treba
            cairo_move_to(cr, 5 * font_size + 5 * duzina * i, font_size + r * font_size);

            gchar text_int[g];
            memset(text_int, 0, g);
            if(r==q){
                for (int s = 0; s <= j; s++) {

                    int w = s + r *(int)g;
                    text_int[s] = ime1[w];
                }
                // text_int[11] = '\0';
                cairo_show_text(cr, text_int);
            }
            else {
                for (int s = 0; s < g; s++) {

                    int w = s + r *(int) g;
                    text_int[s] = ime1[w];
                }
                //   text_int[11] = '\0';
                cairo_show_text(cr, text_int);
            }

        }

    }
    int pomeraj=q;
    q=0;
    j=strlen(ime2);
    if(g<j){

        j-=g;
        q++;
    }
    if(q==0){

        gchar text_int[g];
        memset(text_int, 0, g);
        //ako ima ime4 ima i ime3
        cairo_move_to(cr,5 * font_size+5*duzina*i,2*font_size+pomeraj*font_size);//pomerimo ga na pocetnu poziciju

        for(int s=0 ;s<j;s++){

            text_int[s]=ime2[s];
        }
        // text_int[g-1]='\0';
        cairo_show_text(cr,text_int);
    }
    else  *//*if(q>=1)*//*{

        for (int r = 0; r <= q; r++) {
            //pomeramo ga u zavisnosti od koliko redova nam treba
            cairo_move_to(cr, 5 * font_size + 5 * duzina * i,2*font_size+pomeraj*font_size+r*font_size);

            gchar text_int[g];
            memset(text_int, 0, g);
            if(r==q){
                for (int s = 0; s <= j; s++) {

                    int w = s + r *(int)g;
                    text_int[s] = ime2[w];
                }
                // text_int[11] = '\0';
                cairo_show_text(cr, text_int);
            }
            else {
                for (int s = 0; s < g; s++) {

                    int w = s + r * (int)g;
                    text_int[s] = ime2[w];
                }
                //   text_int[11] = '\0';
                cairo_show_text(cr, text_int);
            }

        }

    }


//return cr;
}*/
void ispis_interrupta2(cairo_t *cr, double font_size, double duzina, int i, const gchar *ime1, const gchar *ime2) {


    size_t j;
    double broj = floor(duzina);

    size_t g = 0;//toliko slova moze da stane u jedan red
    g = (size_t) broj - 2;
    int q = 0;//koliko redova
    j = strlen(ime1);
    printf("ime1 %s \n", ime1);
    int brojac = 0;
    while (g < j) {

        j -= g;
        q++;//povecavamo broj redova
    }
    if (q == 0) {

        cairo_move_to(cr, 5 * font_size + 5 * duzina * i, font_size);//pomerimo ga na pocetnu poziciju

        /*   gchar text_int[j];
           memset(text_int, 0, j);
           for (int s = 0; s < j; s++) {

               text_int[s] = ime1[s];
           }*/
        printf("1[%s]\n", ime1);
        /*  printf("1[%s]\n",text_int);
          cairo_show_text(cr,text_int);*/
        cairo_show_text(cr, ime1);
    }
    if (q >= 1) {

        for (int r = 0; r <= q; r++) {
            //pomeramo ga u zavisnosti od koliko redova nam treba
            cairo_move_to(cr, 5 * font_size + 5 * duzina * i, font_size + r * font_size);
            size_t y = g;
            j = strlen(ime1);

            if (g > j) {

                y = j;

            }

            printf("J[%d]\n", (int) j);
            printf("G[%d]\n", (int) g);
            printf("Y[%d]\n", (int) y);
            if (r == q) {
                gchar text_int[y];
                memset(text_int, 0, y);
                for (int s = 0; s < y; s++) {


                    text_int[s] = ime1[s];
                }
                printf("2[%s]\n", text_int);
                printf("size of buffer %d\n", (int) sizeof(text_int));
                cairo_show_text(cr, ime1);
            } else {
                //char text_int[y];
                char *text_int = (char *) calloc(y, sizeof(char));

                printf("size of buffer %d\n", (int) sizeof(text_int));

                memset(text_int, 0, y);
                for (int s = 0; s < y; s++) {


                    text_int[s] = ime1[s];

                }
                brojac = (int) y;
                for (int c = 0; c < brojac; c++) {
                    ime1++;
                }
                printf("3[%s]\n", text_int);
                cairo_show_text(cr, text_int);
                free(text_int);

            }


        }
    }

    int pomeraj = q;
    q = 0;
    if (ime2 != NULL) {
        j = strlen(ime2);
        printf("%s\n", ime2);
        while (g < j) {

            j -= g;
            q++;//povecavamo broj redova
        }
        if (q == 0) {

            cairo_move_to(cr, 5 * font_size + 5 * duzina * i,
                          2 * font_size + pomeraj * font_size);//pomerimo ga na pocetnu poziciju


            gchar text_int[j];
            memset(text_int, 0, j);
            for (int s = 0; s < j; s++) {

                text_int[s] = ime2[s];
            }
            cairo_show_text(cr, ime2);
        } else {

            for (int r = 0; r <= q; r++) {
                //pomeramo ga u zavisnosti od koliko redova nam treba
                cairo_move_to(cr, 5 * font_size + 5 * duzina * i, 2 * font_size + pomeraj * font_size + r * font_size);
                size_t y = g;
                j = strlen(ime2);
                if (g > j) {

                    y = j;

                }
                printf("2J[%d]\n", (int) j);
                printf("2G[%d]\n", (int) g);
                printf("2Y[%d]\n", (int) y);
                if (r == q) {


                    cairo_show_text(cr, ime2);
                    printf("2[%s]\n", ime2);
                } else {
                    char *text_int = (char *) calloc(y, sizeof(char));

                    memset(text_int, 0, y);
                    strncpy(text_int, ime2, y);
                    brojac = (int) y;
                    for (int c = 0; c < brojac; c++) {
                        ime2++;
                    }
                    cairo_show_text(cr, text_int);
                    printf("3[%s]\n", text_int);
                    free(text_int);
                }


            }

        }
    }


}

/*void ispis_interrupta_real(cairo_t *cr,double font_size,double duzina,int i,gchar *ime1,gchar *ime2){

    size_t j;
    double broj =floor(duzina);

    size_t g=0;//toliko slova moze da stane u jedan red
    g=(size_t)broj-1;
    int q=0;//koliko redova
   j=strlen(ime1);
    printf("%s\n",ime1);

    if(g<j){

        j-=g;
        q++;
    }
    if(q==0){

//        gchar text_int[g];
//        memset(text_int, 0, g);
        gchar text_int[j];
        memset(text_int, 0, j);
        cairo_move_to(cr,5 * font_size+5*duzina*i,font_size);//pomerimo ga na pocetnu poziciju

        for(int s=0 ;s<j;s++){

            text_int[s]=ime1[s];
        }
        //  text_int[11]='\0';
        cairo_show_text(cr,text_int);
    }
    if(q>=1){

        for (int r = 0; r <= q; r++) {
            //pomeramo ga u zavisnosti od koliko redova nam treba
            cairo_move_to(cr, 5 * font_size + 5 * duzina * i, font_size + r * font_size);
*//*
            gchar text_int[g];
            memset(text_int, 0, g);*//*
            gchar text_int[j];
            memset(text_int, 0, j);

            if(r==q){
                for (int s = 0; s <= j; s++) {

                    int w = s + r *(int)g;
                    text_int[s] = ime1[w];
                }
                // text_int[11] = '\0';
                cairo_show_text(cr, text_int);
            }
            else {
                for (int s = 0; s < g; s++) {

                    int w = s + r *(int) g;
                    text_int[s] = ime1[w];
                }
                //   text_int[11] = '\0';
                printf("[%s]\n",text_int);
                cairo_show_text(cr, text_int);
            }

        }

    }
    int pomeraj=q;
    q=0;
    if(ime2!=NULL){
        j=strlen(ime2);
        printf("%s\n",ime2);
        if(g<j){

            j-=g;
            q++;
        }
        if(q==0){

//            gchar text_int[g];
//            memset(text_int, 0, g);
            gchar text_int[j];
            memset(text_int, 0, j);
            //ako ima ime4 ima i ime3
            cairo_move_to(cr,5 * font_size+5*duzina*i,2*font_size+pomeraj*font_size);//pomerimo ga na pocetnu poziciju

            for(int s=0 ;s<j;s++){

                text_int[s]=ime2[s];
            }
            // text_int[g-1]='\0';
            printf("[%s]\n",text_int);
            cairo_show_text(cr,text_int);
        }
        else  *//*if(q>=1)*//*{

            for (int r = 0; r <= q; r++) {
                //pomeramo ga u zavisnosti od koliko redova nam treba
                cairo_move_to(cr, 5 * font_size + 5 * duzina * i,2*font_size+pomeraj*font_size+r*font_size);

            *//*    gchar text_int[g];
                memset(text_int, 0, g);*//*
                char text_int[j];
                memset(text_int, 0, j);
                if(r==q){
                    for (int s = 0; s <= j; s++) {

                        int w = s + r *(int)g;
                        text_int[s] = ime2[w];
                    }
                    // text_int[11] = '\0';.
                    printf("[%s]\n",text_int);
                    cairo_show_text(cr, text_int);
                }
                else {
                    for (int s = 0; s < g; s++) {

                        int w = s + r * (int)g;
                        text_int[s] = ime2[w];
                    }
                    //   text_int[11] = '\0';
                    printf("[%s]\n",text_int);
                    cairo_show_text(cr, text_int);
                }

            }

        }
    }



//return cr;
}*/
void ispis_interrupta(cairo_t *cr, double font_size, double duzina, int i, gchar *ime1, gchar *ime2, gchar *ime3,
                      gchar *ime4) {


    if (ime4[0] != '\0') {

        /* cr=*/ ispis_interrupta2(cr, font_size, duzina, i, ime3, ime4);
    }

    if (ime4[0] == '\0') {

        if (ime3[0] != '\0') {
            /*  cr=*/ ispis_interrupta2(cr, font_size, duzina, i, ime2, ime3);

        }

        if (ime3[0] == '\0') {

            if (ime2[0] != '\0') {
                ispis_interrupta2(cr, font_size, duzina, i, ime1, ime2);


            }


            if (ime2[0] == '\0') {

                if (ime1[0] != '\0') {

                    ispis_interrupta2(cr, font_size, duzina, i, ime1, NULL);
                }

            }
        }
    }









    //  return cr;

};

void crtaj_sekunde(cairo_t *cr, double width, double height, double font_size, int i, int j) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr, i * font_size, height);
    cairo_show_text(cr, "0 sec");
    cairo_move_to(cr, (width - j * font_size) / 6 + i * font_size, height);
    cairo_show_text(cr, "10 sec");
    cairo_move_to(cr, (width - j * font_size) / 6 * 2 + i * font_size, height);
    cairo_show_text(cr, "20 sec");
    cairo_move_to(cr, (width - j * font_size) / 6 * 3 + i * font_size, height);
    cairo_show_text(cr, "30 sec");
    cairo_move_to(cr, (width - j * font_size) / 6 * 4 + i * font_size, height);
    cairo_show_text(cr, "40 sec");
    cairo_move_to(cr, (width - j * font_size) / 6 * 5 + i * font_size, height);
    cairo_show_text(cr, "50 sec");
    cairo_move_to(cr, width - i * font_size, height);
    cairo_show_text(cr, "60 s");
    cairo_stroke(cr);

    cairo_set_source_rgba(cr, .7, .7, .7, 0.5);
    for (int g = 1; g <= 5; g++) {
        cairo_move_to(cr, (width - 2 * i * font_size) / 6 * g + i * font_size, height - font_size);
        cairo_line_to(cr, (width - 2 * i * font_size) / 6 * g + i * font_size, 0);
    }
    cairo_stroke(cr);
    // return cr;

}

void crtaj_okvir(cairo_t *cr, double width, double height, double font_size, int i) {



    //okvir
    cairo_set_source_rgb(cr, 0, 0, 0);
    /*  cairo_move_to(cr,i*font_size,0);
      cairo_line_to(cr,width-i*font_size,0);
      cairo_move_to(cr,i*font_size,0);
      cairo_line_to(cr,i*font_size,height-font_size);
      //   cairo_move_to(cr,3*font_size,height-font_size);
      cairo_line_to(cr,width-i*font_size,height-font_size);
      cairo_move_to(cr,width-i*font_size,height-font_size);
      cairo_line_to(cr,width-i*font_size,0);*/
    cairo_rectangle(cr, i * font_size, height - font_size, width - 2 * i * font_size, -height + font_size);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgba(cr, 1.0, 0.43, 0.0, 0.3);
    cairo_fill(cr);
    //procent linije
    cairo_set_source_rgba(cr, .7, .7, .7, 0.5);
    cairo_move_to(cr, i * font_size, (height - font_size) / 4);//75%
    cairo_line_to(cr, width - i * font_size, (height - font_size) / 4);
    cairo_move_to(cr, i * font_size, (height - font_size) / 4 * 2);//50
    cairo_line_to(cr, width - i * font_size, (height - font_size) / 4 * 2);
    cairo_move_to(cr, i * font_size, (height - font_size) / 4 * 3);//25
    cairo_line_to(cr, width - i * font_size, (height - font_size) / 4 * 3);
    cairo_stroke(cr);
    //  return cr;


};

void crtaj_procente(cairo_t *cr, double height, double font_size) {

    //  cairo_set_source_rgb(cr,0,0,0);
    cairo_set_font_size(cr, font_size);
    cairo_move_to(cr, 0, font_size);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_show_text(cr, "100%");
    cairo_move_to(cr, 0, (height - font_size) / 4);
    cairo_show_text(cr, "75%");
    cairo_move_to(cr, 0, (height - font_size) / 4 * 2);
    cairo_show_text(cr, "50%");
    cairo_move_to(cr, 0, (height - font_size) / 4 * 3);
    cairo_show_text(cr, "25%");
    cairo_move_to(cr, 0, height - font_size);
    cairo_show_text(cr, "0%");
    cairo_stroke(cr);
    // return cr;
};

/*cairo_surface_t *crtaj_surface(cairo_t *cr,int width, int height){
    cairo_surface_t *graph_surface;


    graph_surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, width, height);
    *//*cr =*//*// cairo_create (graph_surface);


    //cairo_destroy(cr);
    return graph_surface;

}*/
void crtaj_interrupte(cairo_t *cr, int i, Interrupts *peak, double height, double font_size, __uint64_t max_broj,
                      double duzina) {

    double procent = 0;

    cairo_set_line_width(cr, 1);


    //  cairo_set_font_size(cr,9);
    procent = ((height - font_size) / max_broj) * peak->CPU0;


    ispis_interrupta(cr, font_size, duzina, i, peak->ime1, peak->ime2, peak->ime3, peak->ime4);


    cairo_rectangle(cr, 5 * font_size + 5 * duzina * i, height - font_size, duzina - 1, -procent);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgba(cr, .7, .7, .7, 0.5);
    cairo_move_to(cr, 5 * font_size + 5 * duzina * i, height - font_size);
    cairo_line_to(cr, 5 * font_size + 5 * duzina * i, 0);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_fill(cr);
    procent = ((height - font_size) / max_broj) * peak->CPU1;
    cairo_rectangle(cr, 5 * font_size + duzina * (5 * i + 1), height - font_size, duzina - 1, -procent);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, 0, 1, 0);
    cairo_fill(cr);
    procent = ((height - font_size) / max_broj) * peak->CPU2;
    cairo_rectangle(cr, 5 * font_size + duzina * (5 * i + 2), height - font_size, duzina - 1, -procent);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_fill(cr);
    procent = ((height - font_size) / max_broj) * peak->CPU3;
    cairo_rectangle(cr, 5 * font_size + duzina * (5 * i + 3), height - font_size, duzina - 1, -procent);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_stroke_preserve(cr);
    cairo_set_source_rgb(cr, 1, .5, 0);
    cairo_fill(cr);

    // return cr;

}


void crtanje_graph(cairo_t *cr, GArray *history, int r, int y, int i, double height, double font_size, double step,
                   float max_broj3) {


    double prev = height - font_size; //nula


    if (r == 0 || r == 5)

        cairo_set_source_rgb(cr, 1, 0, 0);
    else if (r == 1)
        cairo_set_source_rgb(cr, 0, 1, 0);
    else if (r == 2 || r == 4)
        cairo_set_source_rgb(cr, 0, 0, 1); //rgb
    else /*(r == 3)*/
        cairo_set_source_rgb(cr, 1, .5, 0);

    //  printf("size of array %d\n",history->len);
    for (int j = 0; j < y; j++) {


        cairo_move_to(cr, i * font_size, prev);
        //cairo_move_to(cr, 3 * font_size, prev[r]);
        gfloat *peak;
        // peak = &g_array_index(history[r], gfloat, j);
        peak = &g_array_index(history, gfloat, j);


        // int height_temp=height;
        double procent = 0;// = *peak;
        if (r == 4 || r == 5) {
            procent = ((height - font_size) / max_broj3) * *peak;
        } else {
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

    cairo_translate(cr, -step * y, 0);



    // return cr;
};

void do_drawing_mem(GtkWidget *widget, cairo_t *cr, int bjorg, guint time_step) {
    double width, height;
    height = (double) gtk_widget_get_allocated_height(widget);
    width = (double) gtk_widget_get_allocated_width(widget);

    cairo_surface_t *graph_surface;
    graph_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, (int) width, (int) height);

    //   cairo_set_source_rgb(cr,1,.05,1);
    cairo_set_line_width(cr, 1);
    double font_size = 10;
    double step = (width - 3 * font_size - 3 * font_size) / time_step;

    cairo_set_font_size(cr, font_size);

    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
    //  cairo_set_antialias (cr, CAIRO_ANTIALIAS_DEFAULT);


//    gfloat *peak;
//    gfloat procent;
//    double prev[2]={height-font_size};


    cairo_set_font_size(cr, font_size);



    //secund linije
    // graph_surface= crtaj_surface(cr,width,height);


    //  cairo_stroke(cr);
    //okvir
    crtaj_okvir(cr, width, height, font_size, 3);

//procent linije
    //  crtaj_procent_linije(cr, width,height, font_size, 3);

    //procenti
    crtaj_procente(cr, height, font_size);

    //sekunde
    crtaj_sekunde(cr, width, height, font_size, 3, 6);


    crtanje_graph(cr, history[6], 0, bjorg, 3, height, font_size, step, 0);
    crtanje_graph(cr, history[7], 2, bjorg, 3, height, font_size, step, 0);


    if (graph_surface != NULL) {
        cairo_set_source_surface(cr, graph_surface, 0.0, 0.0);
        cairo_paint(cr);
        cairo_surface_destroy(graph_surface);
    }


}

void do_drawing_int(GtkWidget *widget, cairo_t *cr) {
//void do_drawing_int(GtkWidget *widget,cairo_t *cr,GArray *interrupts_array){
//void do_drawing_int(GtkWidget *widget,cairo_t *cr){
    double width, height;

    gchar ime2[3];
    __uint64_t max_broj = 0;
    __uint64_t temp = 0;
    double duzina = 0;
    Interrupts *peak;
    gchar broj[5];
    cairo_surface_t *graph_surface;


    height = (double) gtk_widget_get_allocated_height(widget);
    width = (double) gtk_widget_get_allocated_width(widget);
    double font_size = 10;
//    if(width>height)  {
//        font_size=(float)width/height;
//
//    }
//    if(width<height){
//        font_size=(float)height/width;
//
//    }
//    if(font_size>2){
//        font_size-=1;
//        font_size*=5;
//    } else
//        font_size*=5;




//    if(width>height) {
//        printf("font %f width %d, height  %d ration  %f\n", font_size, width, height, (float) width / height);
//    }
//    if(height>width) {
//        printf("font %f width %d, height  %d ration  %f\n", font_size, width, height, (float) height / width);
//    }

    cairo_set_line_width(cr, 1);
    cairo_set_font_size(cr, font_size);

    graph_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, (int) width, (int) height);
    //   crtaj_procent_linije(cr, width,height, font_size, 5);

    crtaj_okvir(cr, width, height, font_size, 5);
    cairo_set_source_rgb(cr, 0, 0, 0);


    for (int i = 0; i <= 9; i++) {

        cairo_move_to(cr, 5 * font_size, height);
        peak = &g_array_index(interrupt_array_d, Interrupts, i);
        //   peak = &g_array_index(interrupts_array, Interrupts, i);
        if (max_broj <= peak->CPU0) {

            max_broj = peak->CPU0;
        }
        if (max_broj <= peak->CPU1) {

            max_broj = peak->CPU1;
        }
        if (max_broj <= peak->CPU2) {

            max_broj = peak->CPU2;
        }
        if (max_broj <= peak->CPU3) {

            max_broj = peak->CPU3;
        }

    }

    max_broj = max_broj * 5 / 4;
    cairo_move_to(cr, 0, font_size);
    sprintf(broj, "%"PRIu64, max_broj);
    cairo_show_text(cr, broj);
    for (int i = 1; i <= 3; i++) {


        temp = max_broj / 4 * i;

        cairo_move_to(cr, 0, (height - font_size) / 4 * (4 - i));
        sprintf(broj, "%"PRIu64, temp);
        cairo_show_text(cr, broj);
        // cairo_show_text(cr,track);


    }

    cairo_move_to(cr, 0, height - font_size);
    cairo_show_text(cr, "0");
    duzina = (width - (5 * font_size * 2)) / 5 / 10;
    for (int i = 0; i <= 9; i++) {

        // cairo_move_to(cr, 5 * font_size, height);
        peak = &g_array_index(interrupt_array_d, Interrupts, i);
//        peak = &g_array_index(interrupts_array, Interrupts, i);
//
        cairo_move_to(cr, 5 * font_size + 5 * duzina * (i), height);
        sprintf(ime2, "%s", peak->name);
        // ime2 = g_strdup_printf("%3s", peak->name);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_show_text(cr, ime2);

        crtaj_interrupte(cr, i, peak, height, font_size, max_broj, duzina);

    }

    if (graph_surface != NULL) {
        cairo_set_source_surface(cr, graph_surface, 0.0, 0.0);
        cairo_paint(cr);
        cairo_surface_destroy(graph_surface);
    }


};

void do_drawing_net(GtkWidget *widget, cairo_t *cr, int bjorg2, guint time_step) {
    double width, height;
    // gchar *rec;
    gchar broj[5];
    gchar *track;

    float rec_bytes = 0;

    gchar *kb = "KB/s";
    gchar *mb = "MB/s";
    gchar *b = "bytes/s";
    gfloat max_broj = 0;
    gfloat max_broj2 = 0;
    static gfloat max_broj3 = 0;

    gfloat *peak = 0;
    float font_size = 10;
    height = (double) gtk_widget_get_allocated_height(widget);
    width = (double) gtk_widget_get_allocated_width(widget);


    float temp;
    double step = (width - 5 * font_size - 5 * font_size) / time_step;
    // double step =(width-5*font_size-5*font_size)/60;


    cairo_surface_t *graph_surface;
    // graph_surface= crtaj_surface(cr,width,height);
    graph_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, (int) width, (int) height);

    cairo_set_line_width(cr, 1);


    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);


    cairo_set_font_size(cr, font_size);

//    crtaj_procent_linije(cr, width,height, font_size, 5);
    crtaj_okvir(cr, width, height, font_size, 5);
    //secund linije
    //sekunde



    crtaj_sekunde(cr, width, height, font_size, 5, 10);
    cairo_stroke(cr);
    //okvir



    // rec=g_strdup_printf("%s",net.network_size_rc);


    for (int j = 4; j <= 5; j++) {
        for (int i = 0; i < bjorg2; i++) {

            peak = &g_array_index(history[j],
            float, i);// kb
            if (max_broj2 <= *peak) {

                max_broj2 = *peak;
            }
        }
    }
    if (max_broj <= max_broj2) {

        max_broj = max_broj2;

    }


    cairo_set_source_rgb(cr, 0, 0, 0);

    if (max_broj > 1024) {
        //   if(max_broj>1000){


        rec_bytes = max_broj / 1024;//mb
        // rec_bytes = max_broj / 1000;//mb
        rec_bytes += 1;
        track = mb;
        //   max_broj3=max_broj+1000;
        max_broj3 = max_broj + 1024;

    }
        //  else if(max_broj<=1000 && max_broj >1){
    else if (max_broj <= 1024 && max_broj > 1) {

        rec_bytes = max_broj;//kb

        rec_bytes += 100;
        track = kb;
        max_broj3 = max_broj + 100;


    } else /*if(max_broj<=1)*/{

        // rec_bytes= max_broj*1000;//bytes
        rec_bytes = max_broj * 1024;//bytes

        //  track=rec;
        track = b;
        max_broj3 = max_broj + 1024;
        //  max_broj3=max_broj+100;

    }


    cairo_move_to(cr, 0, font_size);//najveci broj
    sprintf(broj, "%.1f", rec_bytes);

    cairo_show_text(cr, broj);

    cairo_show_text(cr, track);
    for (int i = 1; i <= 3; i++) {


        temp = rec_bytes / 4 * i;

        cairo_move_to(cr, 0, (height - font_size) / 4 * (4 - i));
        sprintf(broj, "%.1f", temp);
        cairo_show_text(cr, broj);
        cairo_show_text(cr, track);


    }
    cairo_move_to(cr, 0, (height - font_size));
    cairo_show_text(cr, "0");
    cairo_show_text(cr, track);

    //g_free(rec);




    crtanje_graph(cr, history[4], 4, bjorg2, 5, height, font_size, step, max_broj3);
    crtanje_graph(cr, history[5], 5, bjorg2, 5, height, font_size, step, max_broj3);

    if (graph_surface != NULL) {
        cairo_set_source_surface(cr, graph_surface, 0.0, 0.0);
        cairo_paint(cr);
        cairo_surface_destroy(graph_surface);
    }


}

void do_drawing_cpu(GtkWidget *widget, cairo_t *cr, int bjorg, guint time_step, gboolean CPU0_line, gboolean CPU1_line,
                    gboolean CPU2_line, gboolean CPU3_line) {
    double width, height;
    double font_size = 12;
    double step;
    cairo_surface_t *graph_surface;

    height = (double) gtk_widget_get_allocated_height(widget);
    width = (double) gtk_widget_get_allocated_width(widget);




    //  cairo_set_line_width(cr, 1);

    step = (width - 3 * font_size - 3 * font_size) / time_step;

    cairo_set_font_size(cr, font_size);

    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);


    graph_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, (int) width, (int) height);

    //okvir
    //   crtaj_procent_linije(cr, width,height, font_size, 3);
    crtaj_okvir(cr, width, height, font_size, 3);
    cairo_set_source_rgba(cr, .7, .7, .7, 0.5);
    cairo_stroke(cr);

    //procenti
    crtaj_procente(cr, height, font_size);
    //sekunde //secund linije
    crtaj_sekunde(cr, width, height, font_size, 3, 6);


/*    printf("CPU0 LINE %s\n", CPU0_line==TRUE ? "TRUE" : "FALSE");
    printf("CPU1 LINE %s\n", CPU1_line==TRUE ? "TRUE" : "FALSE");
    printf("CPU2 LINE %s\n", CPU2_line==TRUE ? "TRUE" : "FALSE");
    printf("CPU3 LINE %s\n", CPU3_line==TRUE ? "TRUE" : "FALSE");*/
    if (CPU0_line == TRUE) {


        crtanje_graph(cr, history[0], 0, bjorg, 3, height, font_size, step, 0);
    }
    if (CPU1_line == TRUE) {
        crtanje_graph(cr, history[1], 1, bjorg, 3, height, font_size, step, 0);
    }
    if (CPU2_line == TRUE) {
        crtanje_graph(cr, history[2], 2, bjorg, 3, height, font_size, step, 0);
    }
    if (CPU3_line == TRUE) {
        crtanje_graph(cr, history[3], 3, bjorg, 3, height, font_size, step, 0);
    }


    if (graph_surface != NULL) {
        cairo_set_source_surface(cr, graph_surface, 0.0, 0.0);
        cairo_paint(cr);
        cairo_surface_destroy(graph_surface);
    }
};

