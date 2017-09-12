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
void array_interrupts (){
int j=0;
    ginterrupts=g_array_new(FALSE,TRUE,sizeof(Interrupts));
 //   g_array_set_size(ginterrupts,30);

    ginterrupts_temp=g_array_new(FALSE,TRUE,sizeof(Interrupts));
    //g_array_set_size(ginterrupts_temp,ginterrupts->len);
    ginterrupts_main=g_array_new(FALSE,TRUE,sizeof(Interrupts));
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
        interrupts1=&g_array_index(ginterrupts,Interrupts,j);
        interrupts2=&g_array_index(ginterrupts_temp,Interrupts,j);
     //   printf("%lu\n",interrupts1->CPU0);
        CPU0=interrupts1->CPU0 - interrupts2->CPU0;
        CPU1=interrupts1->CPU0 - interrupts2->CPU0;
        CPU2=interrupts1->CPU0 - interrupts2->CPU0;
        CPU3=interrupts1->CPU0 - interrupts2->CPU0;
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

        printf("%lu %lu %lu %lu   ime: %s\n", interrupts1->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);

    }



};
void printanje(GArray *array) {

    printf("[%d] lenght\n",array->len);
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


            /*  CPU0_old=CPU0_oldj;
              CPU1_old=CPU1_oldj;
              CPU2_old=CPU2_oldj;
              CPU3_old=CPU3_oldj;*/
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
        printf("Koliko interrupta : %d", i);



        printanje(ginterrupts);




}




