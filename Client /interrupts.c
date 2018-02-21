//
// Created by dushn on 31.8.17..
//

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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



        memset(  &array[g],0,sizeof(array[g]));


        sscanf(buffer,"%s %" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64 " %s %s %s %s"
                ,array[g].name
                ,&array[g].CPU0
                , &array[g].CPU1
                , &array[g].CPU2,
               &array[g].CPU3,
               array[g].ime1,
               array[g].ime2,
               array[g].ime3,
               array[g].ime4 );




        i=0;
        while(array[g].name[i] != ':'){


            i++;

        }
        array[g].name[i]='\0';

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



    }


    fclose(file);
    *array2=array;
    *j=g;
    g=0;



    return 0;
}

static int myCompare(const void *a, const void *b) {

    Interrupts interrupts1 = *(Interrupts *) a;
    Interrupts interrupts2 = *(Interrupts *) b;

    __uint64_t CPU0a = 0;
    __uint64_t CPU1a = 0;
    __uint64_t CPU2a = 0;
    __uint64_t CPU3a = 0;
    __uint64_t CPU0b = 0;
    __uint64_t CPU1b = 0;
    __uint64_t CPU2b = 0;
    __uint64_t CPU3b = 0;
    int CPUa = 0;
    int CPUb = 0;

    CPU0a = interrupts1.CPU0;
    CPU1a = interrupts1.CPU1;
    CPU2a = interrupts1.CPU2;
    CPU3a = interrupts1.CPU3;

    CPU0b = interrupts2.CPU0;
    CPU1b = interrupts2.CPU1;
    CPU2b = interrupts2.CPU2;
    CPU3b = interrupts2.CPU3;


    CPUa = (int) (CPU0a + CPU1a + CPU2a + CPU3a);
    CPUb = (int) (CPU0b + CPU1b + CPU2b + CPU3b);



    return CPUa - CPUb;

}

void sort2(Interrupts *array, Interrupts *array2, Interrupts **array3, int n) {

    Interrupts *interrupts_send = NULL;
    interrupts_send = calloc((size_t) n, sizeof(Interrupts));
    for (int i = 0; i < n; i++) {

        Interrupts interrupts3;
        memset(&interrupts3, 0, sizeof(Interrupts));
        strcpy(interrupts3.name, array[i].name);

        __int64_t temp = array[i].CPU0 - array2[i].CPU0;
        if(temp<0){
            temp=0;
        }
        interrupts3.CPU0 = (__uint64_t)temp;

        temp = array[i].CPU1 - array2[i].CPU1;
        if(temp<0){
            temp=0;
        }
        interrupts3.CPU1 = (__uint64_t)temp;


        temp = array[i].CPU2 - array2[i].CPU2;
        if(temp<0){
            temp=0;
        }
        interrupts3.CPU2 = (__uint64_t)temp;

        temp = array[i].CPU3 - array2[i].CPU3;
        if(temp<0){
            temp=0;
        }
        interrupts3.CPU3 =(__uint64_t)temp;





        strcpy(interrupts3.ime1, array[i].ime1);
        strcpy(interrupts3.ime2, array[i].ime2);
        strcpy(interrupts3.ime3, array[i].ime3);
        strcpy(interrupts3.ime4, array[i].ime4);
        interrupts_send[i] = interrupts3;

    }

    *array3 = interrupts_send;


}

void sort(Interrupts *array, int n) {

    qsort(array,(size_t) n, sizeof(Interrupts), myCompare);
}