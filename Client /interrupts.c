//
// Created by dushn on 31.8.17..
//

#include <errno.h>
#include <inttypes.h>
#include "interrupts.h"





void upis_imena(Interrupts *interrupts1,Interrupts *interrupts3){

    size_t j=strlen(interrupts1->ime1);
    for (int t = 0; t <= j; t++) {

        interrupts3->ime1[t] = interrupts1->ime1[t];


    }
    j=strlen(interrupts1->ime2);
    for (int t = 0; t <= j; t++) {

        interrupts3->ime2[t] = interrupts1->ime2[t];


    }
    j=strlen(interrupts1->ime3);
    for (int t = 0; t <= j; t++) {

        interrupts3->ime3[t] = interrupts1->ime3[t];


    }
    j=strlen(interrupts1->ime4);
    for (int t = 0; t <= j; t++) {

        interrupts3->ime4[t] = interrupts1->ime4[t];


    }


//    return interrupts3;
};




void interrupt_usage2(Interrupts * *array2,__int32_t *j ) {


    FILE *file;
    char *filename = "/proc/interrupts";
    char buffer[1024];


    //   GArray * ginterrupts=g_array_new(FALSE,FALSE,sizeof(Interrupts));
    Interrupts  *temp;
    Interrupts *array;
    array=malloc(sizeof(Interrupts));

    static  int g=0;
    if (array == NULL) {
        fprintf(stderr, "malloc failed\n");
    }
    if ((file = fopen(filename, "r")) == NULL || fgets(buffer, 1024, file) == NULL)
        exit(1);


    while (fgets(buffer, 1024, file) != NULL) {
        int i = 0;



      /*  for(int n=0;n<sizeof(array->name);n++){

            array[*j].name[n]='\0';
        }*/
        memset(  array[*j].name,0,sizeof(array[*j].name));
        array[*j].CPU0=0;
        array[*j].CPU1=0;
        array[*j].CPU2=0;
        array[*j].CPU3=0;
        memset(  array[*j].ime1,0,sizeof(array[*j].ime1));
        memset(  array[*j].ime2,0,sizeof(array[*j].ime2));
        memset(  array[*j].ime3,0,sizeof(array[*j].ime3));
        memset(  array[*j].ime4,0,sizeof(array[*j].ime4));
      /*  for(int n=0;n<sizeof(array->ime1);n++){

            array[*j].ime1[n]='\0';
            array[*j].ime2[n]='\0';
            array[*j].ime3[n]='\0';
            array[*j].ime4[n]='\0';
        }*/

        sscanf(buffer,"%s %" SCNu64 " %" SCNu64 " %" SCNu64 " %" SCNu64 " %s %s %s %s",array[*j].name, &array[*j].CPU0, &array[*j].CPU1,
               &array[*j].CPU2,
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
      //  i=0;

        //   printf("j %d\t",j);
     /*   printf("PRvi[%s %li %li %li %li %s %s %s %s]\n",array[*j].name, array[*j].CPU0, array[*j].CPU1,
               array[*j].CPU2,
               array[*j].CPU3,
               array[*j].ime1,
               array[*j].ime2,
               array[*j].ime3,
               array[*j].ime4 );
*/


        //   array=(Interrupts *) realloc(array,(j+1)*sizeof(Interrupts)); //mora da se inicijalizuje
        g++;
        temp=realloc(array,( /**j*/ g+1)*sizeof(Interrupts));
        if ( temp != NULL ) {
            array=temp;
        } else {
            free(array);
            free(temp);
            printf("relloc error %d",errno);
        }



        *j=g;





    }
    //j=0;

    fclose(file);
    *array2=array;
    g=0;
    //  free(array);



}