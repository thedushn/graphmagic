//
// Created by dushn on 31.8.17..
//

#include "interrupts.h"
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>


#include <math.h>
#include <sys/stat.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <syslog.h>
#include <ctype.h>

#include<stdio.h>

struct _Interrupts interrupts;
struct _Interrupts interrupts_temp;

//struct _Interrupts sortiranje (gpointer *a,gpointer *b){
gint sortiranje(gconstpointer a,gconstpointer b){
    Interrupts *interrupts1= (Interrupts *)a;
    Interrupts *interrupts2=(Interrupts *)b;
    Interrupts interrupts3;
     long CPU0a = 0;
     long CPU1a = 0;
     long CPU2a = 0;
     long CPU3a = 0;
     long CPU0b = 0;
     long CPU1b = 0;
     long CPU2b = 0;
     long CPU3b = 0;
     int CPUa= 0;
     int CPUb= 0;

    CPU0a=interrupts1->CPU0;
    CPU1a=interrupts1->CPU1;
    CPU2a=interrupts1->CPU2;
    CPU3a=interrupts1->CPU3;

    CPU0b=interrupts2->CPU0;
    CPU1b=interrupts2->CPU1;
    CPU2b=interrupts2->CPU2;
    CPU3b=interrupts2->CPU3;
    CPUa=(int)(CPU0a+CPU1a+CPU2a+CPU3a);
    CPUb=(int)(CPU0b+CPU1b+CPU2b+CPU3b);

    /*printf(" PRVi %lu %lu %lu %lu   ime: %s\n", interrupts1->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);
    printf(" DRUGI %lu %lu %lu %lu   ime: %s\n", interrupts2->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);*/

    return CPUa - CPUb;
    /*if (CPUa >CPUb){
        interrupts3.name[0]=interrupts1->name[0];
        interrupts3.name[1]=interrupts1->name[1];
        interrupts3.name[2]=interrupts1->name[2];

        interrupts3.CPU0=interrupts1->CPU0;
        interrupts3.CPU1=interrupts1->CPU1;
        interrupts3.CPU2=interrupts1->CPU2;
        interrupts3.CPU3=interrupts1->CPU3;
        return ;
    }
    if(CPUb>CPUa){

        interrupts3.name[0]=interrupts2->name[0];
        interrupts3.name[1]=interrupts2->name[1];
        interrupts3.name[2]=interrupts2->name[2];

        interrupts3.CPU0=interrupts2->CPU0;
        interrupts3.CPU1=interrupts2->CPU1;
        interrupts3.CPU2=interrupts2->CPU2;
        interrupts3.CPU3=interrupts2->CPU3;
        return interrupts3;
    }*/


};
void array_interrupts (){
int j=0;
    ginterrupts=g_array_new(FALSE,TRUE,sizeof(Interrupts));
 //   g_array_set_size(ginterrupts,30);

    ginterrupts_temp=g_array_new(FALSE,TRUE,sizeof(Interrupts));
    //g_array_set_size(ginterrupts_temp,ginterrupts->len);
    ginterrupts_main=g_array_new(FALSE,TRUE,sizeof(Interrupts));
    ginterrupts_final=g_array_new(FALSE,TRUE,sizeof(Interrupts));
   // g_array_set_size(ginterrupts_main,ginterrupts->len);*/
}

void upis(GArray *array){


    for (int j = 0; j < array->len; j++) {
        Interrupts interrupts3;
        Interrupts *interrupts1;
        interrupts1 = &g_array_index(array, Interrupts, j);
        //  printf("%lu %lu %lu %lu   ime: %s\n", interrupts1->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);
        interrupts3.name[0]=interrupts1->name[0];
        interrupts3.name[1]=interrupts1->name[1];
        interrupts3.name[2]=interrupts1->name[2];

        interrupts3.CPU0=interrupts1->CPU0;
        interrupts3.CPU1=interrupts1->CPU1;
        interrupts3.CPU2=interrupts1->CPU2;
        interrupts3.CPU3=interrupts1->CPU3;

        g_array_append_val(ginterrupts_temp,interrupts3);


    }


};
void poredjenje(GArray *array){
    Interrupts *interrupts2;
    Interrupts *interrupts1;
    Interrupts interrupts3;
    unsigned long CPU0 = 0;
    unsigned long CPU1 = 0;
    unsigned long CPU2 = 0;
    unsigned long CPU3 = 0;
    for (int j = 0; j < array->len; j++) {
        interrupts1=&g_array_index(array,Interrupts,j);
        interrupts2=&g_array_index(ginterrupts_temp,Interrupts,j);
     //   printf("%lu\n",interrupts1->CPU0);
        CPU0=interrupts1->CPU0 - interrupts2->CPU0;
        CPU1=interrupts1->CPU1 - interrupts2->CPU1;
        CPU2=interrupts1->CPU2 - interrupts2->CPU2;
        CPU3=interrupts1->CPU3 - interrupts2->CPU3;
       // printf("%lu\n",CPU0);
        if(interrupts1->name[0]==interrupts2->name[0] && interrupts1->name[1]==interrupts2->name[1] && interrupts1->name[2]==interrupts2->name[2] ) {
            interrupts3.name[0] = interrupts1->name[0];
            interrupts3.name[1] = interrupts1->name[1];
            interrupts3.name[2] = interrupts1->name[2];
        }
        interrupts3.CPU0=CPU0;
        interrupts3.CPU1=CPU1;
        interrupts3.CPU2=CPU2;
        interrupts3.CPU3=CPU3;

        g_array_append_val(ginterrupts_main,interrupts3);


    }
    for (int j = 0; j < array->len; j++) {

        interrupts1=&g_array_index(ginterrupts_main,Interrupts,j);

      // printf(" PRE %lu %lu %lu %lu   ime: %s\n", interrupts1->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);

    }
    g_array_sort(ginterrupts_main,(GCompareFunc)sortiranje);
    // sortiranje(ginterrupts_main);

    for (int j = 0; j < array->len; j++) {

        interrupts1=&g_array_index(ginterrupts_main,Interrupts,j);
        if(j>=array->len-5 && j<array->len){
            Interrupts interrupts4;

            interrupts4.CPU0=interrupts1->CPU0;
            interrupts4.CPU1=interrupts1->CPU1;
            interrupts4.CPU2=interrupts1->CPU2;
            interrupts4.CPU3=interrupts1->CPU3;
            interrupts4.name[0]=interrupts1->name[0];
            interrupts4.name[1]=interrupts1->name[1];
            interrupts4.name[2]=interrupts1->name[2];
            printf("Posle sortiranja%lu %lu %lu %lu   ime: %s\n", interrupts1->CPU0, interrupts1->CPU1,
                   interrupts1->CPU2, interrupts1->CPU3, interrupts1->name);
        //    printf("Posle sortiranja%lu %lu %lu %lu   ime: %s\n", interrupts4.CPU0, interrupts4.CPU1,
           //        interrupts4.CPU2, interrupts4.CPU3, interrupts4.name);
            g_array_append_val(ginterrupts_final,interrupts4);
            if (ginterrupts_final->len > 5) {
                g_array_remove_index(ginterrupts_final, ginterrupts_final->len - 6);
            }
        }
    }

    for (int j = 0; j < ginterrupts_final->len; j++) {
        interrupts1=&g_array_index(ginterrupts_final,Interrupts,j);
        printf("%lu %lu %lu %lu   ime: %s\n", interrupts1->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);
    }
    printf("U poredjenju niz ima ginterupts : [%d] niz ima ginterupts_temp : [%d]niz ima ginterupts_main : [%d] niz ima ginterupts_final: [%d]\n",
           ginterrupts->len,ginterrupts_temp->len,ginterrupts_main->len,ginterrupts_final->len);
    g_array_free(ginterrupts_temp,TRUE);
    ginterrupts_temp=g_array_new(FALSE,TRUE,sizeof(Interrupts));
    upis(array);




};
void printanje(GArray *array) {

   // printf("[%d] lenght\n",array->len);
    int i=0;
    gchar name[3];
    gchar name_temp[3];
   // for (int j = 0; j < array->len; j++) {

      //  Interrupts *interrupts1 = &g_array_index(array, Interrupts, j);
       // printf("%lu %lu %lu %lu   ime: %s\n", interrupts1->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);
       Interrupts *interrupts2 = &g_array_index(ginterrupts_temp,Interrupts,i);//uzmemo vrednost
       // g_array_remove_index(ginterrupts_temp,i);//izbacimo tu vrednost pomerimo sve za jedan


       /* name[0]=interrupts1->name[0];
        name[1]=interrupts1->name[1];
        name[2]=interrupts1->name[2];*/
       // printf("NAME FOR THE LOVE OF GOD : [%c%c%c]",name[0],name[1],name[2]);
        if(interrupts2==NULL){
            upis(array);

        }
        poredjenje(array);


        /*interrupts3=&g_array_index(ginterrupts_temp,Interrupts,j);
        printf("temp len: %d name of interupt [%s]%lu %lu %lu %lu \n",ginterrupts_temp->len,interrupts3->name,interrupts3->CPU0, interrupts3->CPU1, interrupts3->CPU2, interrupts3->CPU3);

*/

/*
       interrupts3->CPU0= interrupts1->CPU0 - interrupts2->CPU0;
        interrupts2->CPU0=interrupts1->CPU0;
        interrupts3->CPU1= interrupts1->CPU1- interrupts2->CPU1;
        interrupts2->CPU1=interrupts1->CPU1;
        interrupts3->CPU2= interrupts1->CPU2- interrupts2->CPU2;
        interrupts2->CPU2=interrupts1->CPU2;
        interrupts3->CPU3= interrupts1->CPU3- interrupts2->CPU3;
        interrupts2->CPU3=interrupts1->CPU3;*/


/*

       g_array_prepend_val(ginterrupts_temp,interrupts2);// dodamo element na kraj niza
        g_array_append_val(ginterrupts_main,interrupts3);
    }
    for(int j = 0; j < array->len; j++){

        Interrupts *interrupts1 = &g_array_index(ginterrupts_main, Interrupts, j);
  //      printf("%lu %lu %lu %lu   ime: %s\n", interrupts1->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);

*/

    //}
    g_array_free(ginterrupts,TRUE);
    g_array_free(ginterrupts_main,TRUE);
    ginterrupts_main=g_array_new(FALSE,TRUE,sizeof(Interrupts));
    ginterrupts=g_array_new(FALSE,TRUE,sizeof(Interrupts));
}
void interrupt_usage() {


        // Interrupts *interrupts={0};

        FILE *file;
        gchar *filename = "/proc/interrupts";
        gchar buffer[1024];
      /*  gchar buffer2[1024];
        gchar buffer3[1024];*/
        gchar *temp;
        //  char  *razmak=' ';
        gchar name[4];
    unsigned long CPU0 = 0;
    unsigned long CPU1 = 0;
    unsigned long CPU2 = 0;
    unsigned long CPU3 = 0;
        static int CPU0_old = 0;
        static int CPU1_old = 0;
        static int CPU2_old = 0;
        static int CPU3_old = 0;
        static int CPU1_oldj = 0;
        static int CPU2_oldj = 0;
        static int CPU0_oldj = 0;
        static int CPU3_oldj = 0;

        char ime2[30];
        char ime3[30];
        char ime1[30];
        char prazno[1]="";
       guint i = 0;

        if ((file = fopen(filename, "r")) == NULL || fgets(buffer, 1024, file) == NULL)
            exit(1);

        //   printf("buffer from inetrupts : %s\n", buffer);
        while (fgets(buffer, 1024, file) != NULL) {
            i++;


            sscanf(buffer, "%4s %lu %lu %lu %lu %s %s %s", name, &CPU0, &CPU1, &CPU2,
                   &CPU3,
                   ime1,
                   ime2,
                   ime3);


            if(name[0]=='E' && name[1]=='R' && name[2]=='R'){

                CPU1=0;
                CPU2=0;
                CPU3=0;

            }

         //   memset(&buffer[0], 0, sizeof(buffer));
            if(name[0]==':' ){

                //interrupts.name[0]= name[0];
            }
            if(name[1]==':'){

                interrupts.name[0]= name[0];
                interrupts.name[1]=prazno[0];
                interrupts.name[2]=prazno[0];
            }
            if(name[2]==':'){

                interrupts.name[0]= name[0];
                interrupts.name[1] = name[1];
                interrupts.name[2] = prazno[0];

            }

             if(name[0]!=':' && name[1]!=':' && name[2]!=':' ) {
                interrupts.name[0]= name[0];
                interrupts.name[1] = name[1];
                interrupts.name[2] = name[2];

            }



                interrupts.CPU0 = CPU0;
                interrupts.CPU1 = CPU1;
                interrupts.CPU2 = CPU2;
                interrupts.CPU3 = CPU3;









            g_array_append_val(ginterrupts,interrupts);


/*
            g_array_remove_index(ginterrupts,i);
            g_array_insert_val(ginterrupts,i, interrupts);
            i++;*/
          /*  if (ginterrupts->len > 1)
                g_array_remove_index (ginterrupts, ginterrupts->len - 1);*/

      //  printf("%s :",name);
     //   printf("sta on to pise [%s]\n",interrupts.name);
       //     printf("ime interupta : %s\n", name);
        }
        fclose(file);
        printf("Koliko interrupta : %d\n", i);



        printanje(ginterrupts);




}




