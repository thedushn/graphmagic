//
// Created by dushn on 31.8.17..
//

#include "interrupts.h"

#include"sys/socket.h"
#include"string.h"
gint sortiranje(gconstpointer a,gconstpointer b){
    Interrupts *interrupts1= (Interrupts *)a;
    Interrupts *interrupts2=(Interrupts *)b;

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



};

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

void upis(GArray *array,GArray *array2){


//   for (int r = 0; r <= ginterrupts->len; r++) {//// staviti samo manje
   for (guint r = 0; r < array->len; r++) {
        //Interrupts interrupts3={0};
        Interrupts interrupts3={0};
        Interrupts *interrupts1;
    //    interrupts1 = &g_array_index(array, Interrupts, r);
        interrupts1 = &g_array_index(array, Interrupts, r);
        //  printf("%lu %lu %lu %lu   ime: %s\n", interrupts1->CPU0, interrupts1->CPU1, interrupts1->CPU2, interrupts1->CPU3,interrupts1->name);
        interrupts3.name[0]=interrupts1->name[0];
        interrupts3.name[1]=interrupts1->name[1];
        interrupts3.name[2]=interrupts1->name[2];
        interrupts3.name[3]=interrupts1->name[3];

        interrupts3.CPU0=interrupts1->CPU0;
        interrupts3.CPU1=interrupts1->CPU1;
        interrupts3.CPU2=interrupts1->CPU2;
        interrupts3.CPU3=interrupts1->CPU3;

       upis_imena( interrupts1 , &interrupts3);

        g_array_insert_val(array2,r,interrupts3);
       // g_array_append_val(array2,interrupts3);
     //  printf("lenght %d\n ",array2->len);
//       if (array2->len > 1)
//           g_array_remove_index (array2, array2->len - 1);
    }
   // printf("lenght %d\n ",array2->len);

};
//GArray * poredjenje(GArray *array,GArray *array2){//array novi array2 stari
void poredjenje(GArray *array,GArray *array2,GArray *array3){//array novi array2 stari
//

    while(array3->len>0){

        g_array_remove_index(array3, 0);
    }
    for (int r = 0; r < array->len; r++) {
        Interrupts interrupts3={0};
        Interrupts *interrupts1=&g_array_index(array,Interrupts,r);

        Interrupts *interrupts2=&g_array_index(array2,Interrupts,r);

       interrupts3.CPU0=interrupts1->CPU0 - interrupts2->CPU0;
        interrupts3.CPU1=interrupts1->CPU1 - interrupts2->CPU1;
        interrupts3.CPU2=interrupts1->CPU2 - interrupts2->CPU2;
        interrupts3.CPU3=interrupts1->CPU3 - interrupts2->CPU3;

            interrupts3.name[0] = interrupts1->name[0];
            interrupts3.name[1] = interrupts1->name[1];
            interrupts3.name[2] = interrupts1->name[2];
            interrupts3.name[3] = interrupts1->name[3];



         upis_imena(interrupts1,&interrupts3);

        g_array_append_val(array3,interrupts3);


    }
   // printf("Before sorting %d\n",array3->len);
//    for(int i=0 ;i<array3->len;i++){
//        Interrupts *interrupts5;
//        interrupts5=&g_array_index(array3,Interrupts,i);
//        printf("name[%s] CPU0[%lu] CPU1[%lu] CPU2[%lu] CPU3[%lu] ime1[%s],ime2 [%s] ime3 [%s] ime4[%s]\n",interrupts5->name,interrupts5->CPU0,interrupts5->CPU1,interrupts5->CPU2,interrupts5->CPU3,interrupts5->ime1,interrupts5->ime2,interrupts5->ime3,interrupts5->ime4);
//    }

    g_array_sort(array3,(GCompareFunc)sortiranje);



           while (array3->len > 10) {
                g_array_remove_index(array3, array3->len - 11);

            }

//return array3;

};

void interrupt_usage(int info ) {
//GArray * interrupt_usage(Interrupts *array,guint *j ) {


    FILE *file;
    gchar *filename = "/proc/interrupts";
    gchar buffer[1024];


 //   GArray * ginterrupts=g_array_new(FALSE,FALSE,sizeof(Interrupts));
    Interrupts *array, *temp;
    array=malloc(sizeof(Interrupts));
    static  guint g=0;
    static guint j=0;
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
        /*     sscanf(buffer, "%s %li %li %li %li %255s %255s %255s %255s",array->name, &array->CPU0, &array->CPU1,
                    &array->CPU2,
                    &array->CPU3,
                    array->ime1,
                    array->ime2,
                    array->ime3,
                    array->ime4 );*/
        for(int n=0;n<sizeof(array->name);n++){

            array[j].name[n]='\0';
        }
        array[j].CPU0=0;
        array[j].CPU1=0;
        array[j].CPU2=0;
        array[j].CPU3=0;
        for(int n=0;n<sizeof(array->ime1);n++){

            array[j].ime1[n]='\0';
            array[j].ime2[n]='\0';
            array[j].ime3[n]='\0';
            array[j].ime4[n]='\0';
        }

        sscanf(buffer,"%s %li %li %li %li %s %s %s %s",array[j].name, &array[j].CPU0, &array[j].CPU1,
               &array[j].CPU2,
               &array[j].CPU3,
               array[j].ime1,
               array[j].ime2,
               array[j].ime3,
               array[j].ime4 );



        while(interrupts.name[i] != ':'){


            i++;

        }
        interrupts.name[i]='\0';
        while(array[j].name[i] != ':'){


            i++;

        }
        array[j].name[i]='\0';


        //   printf("j %d\t",j);
        printf("[%s %li %li %li %li %s %s %s %s]\n",array[j].name, array[j].CPU0, array[j].CPU1,
               array[j].CPU2,
               array[j].CPU3,
               array[j].ime1,
               array[j].ime2,
               array[j].ime3,
               array[j].ime4 );
/*
        printf("[%s %li %li %li %li %s %s %s %s]\n",array->name, array->CPU0, array->CPU1,
                array->CPU2,
                array->CPU3,
                array->ime1,
                array->ime2,
                array->ime3,
                array->ime4 );*/

                                      //   array=(Interrupts *) realloc(array,(j+1)*sizeof(Interrupts)); //mora da se inicijalizuje
                                      temp=realloc(array,(j+2)*sizeof(Interrupts)); /* give the pointer some memory */
        if ( temp != NULL ) {
            array=temp;
        } else {
            free(array);
        }
        j++;








     //   g_array_append_val(ginterrupts,interrupts);



    }
    g=0;
  //  j=0;
int ret;
    data_s data;
    ret = (int) send(info, &j, sizeof(guint), 0);
    if (ret < 0) {
        printf("Error sending num_packets!\n\t");
        //  break;
        exit(1);
    }
    for (int i = 0; i < j; i++) {

        Interrupts *interrupts1;
        interrupts1 = &array[i];
        data.interrupts.CPU0 = interrupts1->CPU0;
        data.interrupts.CPU1 = interrupts1->CPU1;
        data.interrupts.CPU2 = interrupts1->CPU2;
        data.interrupts.CPU3 = interrupts1->CPU3;
        for (int n = 0; n < sizeof(interrupts1->name); n++) {
            data.interrupts.name[n] = interrupts1->name[n];
        }

        upis_imena(interrupts1, &data.interrupts);
    printf(" sending data!\n\t %lu %lu %lu %lu %s %s %s %s %s  \n", data.interrupts.CPU0,data.interrupts.CPU1,data.interrupts.CPU2,
                    data.interrupts.CPU3,  data.interrupts.name,data.interrupts.ime1,data.interrupts.ime2,data.interrupts.ime3,data.interrupts.ime4);
        ret = (int) send(info, &data, sizeof(data_s), 0);

        if (ret < 0) {
            printf("Error sending data!\n\t");
            //  break;
            exit(1);
        }
    }
    fclose(file);
        j=0;
      free(array);





//return ginterrupts;

}
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
    Interrupts /**array,*/ *temp;
    Interrupts *array, *temp2;
    array=malloc(sizeof(Interrupts));

    static  int g=0;
    if (array == NULL) {
        fprintf(stderr, "malloc failed\n");
    }
    if ((file = fopen(filename, "r")) == NULL || fgets(buffer, 1024, file) == NULL)
        exit(1);


    while (fgets(buffer, 1024, file) != NULL) {
        int i = 0;
        Interrupts interrupts={0};

/*
        sscanf(buffer, "%s %li %li %li %li %255s %255s %255s %255s",interrupts.name, &interrupts.CPU0, &interrupts.CPU1,
               &interrupts.CPU2,
               &interrupts.CPU3,
               interrupts.ime1,
               interrupts.ime2,
               interrupts.ime3,
               interrupts.ime4 );*/
        /*    sscanf(buffer, "%s %li %li %li %li %255s %255s %255s %255s",array->name, &array->CPU0, &array->CPU1,
                   &array->CPU2,
                   &array->CPU3,
                   array->ime1,
                   array->ime2,
                   array->ime3,
                   array->ime4 );*/
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



        /*    while(interrupts.name[i] != ':'){


                i++;

            }*/
        interrupts.name[i]='\0';
        i=0;
        while(array[*j].name[i] != ':'){


            i++;

        }
        array[*j].name[i]='\0';
        i=0;

        //   printf("j %d\t",j);
        printf("PRvi[%s %li %li %li %li %s %s %s %s]\n",array[*j].name, array[*j].CPU0, array[*j].CPU1,
               array[*j].CPU2,
               array[*j].CPU3,
               array[*j].ime1,
               array[*j].ime2,
               array[*j].ime3,
               array[*j].ime4 );

        /*printf("[%s %li %li %li %li %s %s %s %s]\n",array->name, array->CPU0, array->CPU1,
                 array->CPU2,
                 array->CPU3,
                 array->ime1,
                 array->ime2,
                 array->ime3,
                 array->ime4 );*/

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