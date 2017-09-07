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
void array_interrupts (){

    ginterrupts=g_array_new(FALSE,TRUE,sizeof(Interrupts));
    g_array_set_size(ginterrupts,30);
}

/*void sortiranje(){

    Interrupts interrupts={0};
    if(interrupt_usage(&interrupts)) {
        g_array_append_val (ginterrupts, interrupts);
    }
}*/
void printanje() {

    printf("[%d] lenght\n",ginterrupts->len);
    for (int j = 0; j < ginterrupts->len; j++) {

        Interrupts *interrupts1 = &g_array_index(ginterrupts, Interrupts, j);
        printf("%d %d %d %d  ime: %s\n", interrupts1->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);
    }
}
void interrupt_usage() {


        // Interrupts *interrupts={0};

        FILE *file;
        gchar *filename = "/proc/interrupts";
        gchar buffer[1024];
        gchar buffer2[1024];
        gchar buffer3[1024];
        gchar *temp;
        //  char  *razmak=' ';
        gchar name[3];
        int CPU0 = 0;
        int CPU1 = 0;
        int CPU2 = 0;
        int CPU3 = 0;
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
            sscanf(buffer, "%3s %d %d %d %d %s %s %s", name, &CPU0, &CPU1, &CPU2,
                   &CPU3,
                   ime1,
                   ime2,
                   ime3);
            /* CPU0_oldj=CPU0;
             CPU1_oldj=CPU1;
             CPU2_oldj=CPU2;
             CPU3_oldj=CPU3;*/

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


            g_array_remove_index(ginterrupts,i);
            g_array_insert_val(ginterrupts,i, interrupts);
            i++;
          /*  if (ginterrupts->len > 1)
                g_array_remove_index (ginterrupts, ginterrupts->len - 1);*/

        printf("%s :",name);
        printf("sta on to pise%s\n",interrupts.name);
       //     printf("ime interupta : %s\n", name);
        }
        fclose(file);
        printf("Koliko interrupta : %d", i);



        printanje();



}




