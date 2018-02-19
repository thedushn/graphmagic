//
// Created by dushn on 31.8.17..
//

#include <errno.h>
#include <inttypes.h>
#include "interrupts.h"








int interrupt_usage2(Interrupts **array2, __int32_t *j) {


    FILE *file;
    char *filename = "/proc/interrupts";
    char buffer[1024];



    Interrupts  *temp;
    Interrupts *array;
    array=malloc(sizeof(Interrupts));

    static  int g=0;
    if (array == NULL) {
        fprintf(stderr, "malloc failed\n");
        return 1;

    }
    if ((file = fopen(filename, "r")) == NULL || fgets(buffer, 1024, file) == NULL)
        return 1;


    while (fgets(buffer, 1024, file) != NULL) {
        int i = 0;



        memset(  &array[*j],0,sizeof(array[*j]));


        sscanf(buffer,"%s %" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64 " %s %s %s %s"
                ,array[*j].name
                ,&array[*j].CPU0
                , &array[*j].CPU1
                , &array[*j].CPU2,
               &array[*j].CPU3,
               array[*j].ime1,
               array[*j].ime2,
               array[*j].ime3,
               array[*j].ime4 );




        i=0;
        while(array[*j].name[i] != ':'){


            i++;

        }
        array[*j].name[i]='\0';

        g++;
        temp=realloc(array,(g+1)*sizeof(Interrupts));
        if ( temp != NULL ) {
            array=temp;
        } else {
            free(array);
            fclose(file);
            printf("relloc error %d",errno);
            return 1;

        }



        *j=g;





    }


    fclose(file);
    *array2=array;
    g=0;



    return 0;
}