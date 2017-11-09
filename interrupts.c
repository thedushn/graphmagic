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



void interrupt_usage(){





    FILE *file;
    gchar *filename = "/proc/interrupts";
    gchar buffer[1024];
    gchar buffer2[1024];
    gchar buffer3[1024];
    gchar *temp;
  //  char  *razmak=' ';
    int name;
   int prom=0;
   int prom1=1;
   int prom2=1;
  int prom3=1;
    char ime2[30];
    char ime3[30];
    char ime4[30];
int i=0;
    if ((file = fopen (filename, "r")) == NULL || fgets (buffer, 1024, file) == NULL)
        exit(1);

        printf("buffer from inetrupts : %s\n", buffer);
        while( fgets (buffer, 1024, file) !=NULL){
                i++;
            sscanf(buffer,"%d: %d %d %d %d %s %s %s",&name,&prom,&prom1,&prom2,&prom3,ime2,ime3,ime4);
        }
        printf("Koliko interrupta : %d",i);




    fclose(file);
}




