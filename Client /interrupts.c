//
// Created by dushn on 31.8.17..
//

#include "interrupts.h"


#include"string.h"


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

//GArray * poredjenje(GArray *array,GArray *array2){//array novi array2 stari


/*
Interrupts * interrupt_usage(int info ) {
//GArray * interrupt_usage(Interrupts *array,guint *j ) {


        FILE *file;
        gchar *filename = "/proc/interrupts";
        gchar buffer[1024];


  GArray * ginterrupts=g_array_new(FALSE,FALSE,sizeof(Interrupts));
        Interrupts *array, *temp;
    array=malloc(sizeof(Interrupts));
    static  guint g=0;
    if (array == NULL) {
        fprintf(stderr, "malloc failed\n");
    }
        if ((file = fopen(filename, "r")) == NULL || fgets(buffer, 1024, file) == NULL)
            exit(1);


        while (fgets(buffer, 1024, file) != NULL) {
            guint i = 0;
            Interrupts interrupts={0};


            sscanf(buffer, "%s %li %li %li %li %255s %255s %255s %255s",interrupts.name, &interrupts.CPU0, &interrupts.CPU1,
                   &interrupts.CPU2,
                   &interrupts.CPU3,
                   interrupts.ime1,
                   interrupts.ime2,
                   interrupts.ime3,
                   interrupts.ime4 );
       *//*     sscanf(buffer, "%s %li %li %li %li %255s %255s %255s %255s",array->name, &array->CPU0, &array->CPU1,
                   &array->CPU2,
                   &array->CPU3,
                   array->ime1,
                   array->ime2,
                   array->ime3,
                   array->ime4 );*//*
            for(int n=0;n<sizeof(array->name);n++){

                array[*j].name[n]='\0';
            }
            array[*j].CPU0=0;
            array[*j].CPU1=0;
            array[*j].CPU2=0;
            array[*j].CPU3=0;
            for(int n=0;n<sizeof(array->ime1);n++){

                array[*j].ime1[n]='\0';
                array[*j].ime2[n]='\0';
                array[*j].ime3[n]='\0';
                array[*j].ime4[n]='\0';
            }

            sscanf(buffer,"%s %li %li %li %li %s %s %s %s",array[*j].name, &array[*j].CPU0, &array[*j].CPU1,
                   &array[*j].CPU2,
                   &array[*j].CPU3,
                   array[*j].ime1,
                   array[*j].ime2,
                   array[*j].ime3,
                   array[*j].ime4 );



            while(interrupts.name[i] != ':'){


                i++;

            }
            interrupts.name[i]='\0';
            while(array[*j].name[i] != ':'){


                i++;

            }
            array[*j].name[i]='\0';


         //   printf("j %d\t",j);
            printf("PRvi[%s %li %li %li %li %s %s %s %s]\n",array[*j].name, array[*j].CPU0, array[*j].CPU1,
                   array[*j].CPU2,
                   array[*j].CPU3,
                   array[*j].ime1,
                   array[*j].ime2,
                   array[*j].ime3,
                   array[*j].ime4 );

           *//* printf("[%s %li %li %li %li %s %s %s %s]\n",array->name, array->CPU0, array->CPU1,
                   array->CPU2,
                   array->CPU3,
                   array->ime1,
                   array->ime2,
                   array->ime3,
                   array->ime4 );*//*

         //   array=(Interrupts *) realloc(array,(j+1)*sizeof(Interrupts)); //mora da se inicijalizuje
            temp=realloc(array,(*j+2)*sizeof(Interrupts)); *//* give the pointer some memory *//*
            if ( temp != NULL ) {
                array=temp;
            } else {
                free(array);
            }
            g++;
            *j=g;








            g_array_append_val(ginterrupts,interrupts);



        }
    g=0;


        fclose(file);
  //  free(array);





//return ginterrupts;
return array;
}*/



void interrupt_usage2(Interrupts * *array2,int *j ) {


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



        for(int n=0;n<sizeof(array->name);n++){

            array[*j].name[n]='\0';
        }
        array[*j].CPU0=0;
        array[*j].CPU1=0;
        array[*j].CPU2=0;
        array[*j].CPU3=0;
        for(int n=0;n<sizeof(array->ime1);n++){

            array[*j].ime1[n]='\0';
            array[*j].ime2[n]='\0';
            array[*j].ime3[n]='\0';
            array[*j].ime4[n]='\0';
        }

        sscanf(buffer,"%s %li %li %li %li %s %s %s %s",array[*j].name, &array[*j].CPU0, &array[*j].CPU1,
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
        i=0;

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
        temp=realloc(array,( /**j*/ g+2)*sizeof(Interrupts));
        if ( temp != NULL ) {
            array=temp;
        } else {
            free(array);
        }


        g++;
        *j=g;








        //g_array_append_val(ginterrupts,interrupts);



    }
    //j=0;

    fclose(file);
    *array2=array;
    g=0;
    //  free(array);



}